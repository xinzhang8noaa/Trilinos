#ifndef stk_adapt_UniformRefinerPattern_Quad4_Quad8_1_sierra_hpp
#define stk_adapt_UniformRefinerPattern_Quad4_Quad8_1_sierra_hpp


//#include "UniformRefinerPattern.hpp"
#include <stk_adapt/sierra_element/RefinementTopology.hpp>
#include <stk_adapt/sierra_element/StdMeshObjTopologies.hpp>

#include <stk_percept/PerceptBoostArray.hpp>

#define EDGE_BREAKER_Q4_Q8_1 1
#if EDGE_BREAKER_Q4_Q8_1
#include "UniformRefinerPattern_Line2_Line3_1_sierra.hpp"
#endif

namespace stk {
  namespace adapt {

    template <>
    class UniformRefinerPattern< shards::Quadrilateral<4>, shards::Quadrilateral<8>, 1, SierraPort > : public URP<shards::Quadrilateral<4> , shards::Quadrilateral<8> >
    {

#if EDGE_BREAKER_Q4_Q8_1
      UniformRefinerPattern<shards::Line<2>, shards::Line<3>, 1, SierraPort > * m_edge_breaker;
#endif

    public:

      UniformRefinerPattern(percept::PerceptMesh& eMesh, BlockNamesType block_names = BlockNamesType()) : URP<shards::Quadrilateral<4> , shards::Quadrilateral<8> >(eMesh)
      {
        m_primaryEntityRank = m_eMesh.face_rank();
        if (m_eMesh.get_spatial_dim() == 2)
          m_primaryEntityRank = stk::mesh::MetaData::ELEMENT_RANK;

        setNeededParts(eMesh, block_names, false);
        Elem::StdMeshObjTopologies::bootstrap();
#if EDGE_BREAKER_Q4_Q8_1

        m_edge_breaker =  new UniformRefinerPattern<shards::Line<2>, shards::Line<3>, 1, SierraPort > (eMesh, block_names) ;
#endif

      }


      ~UniformRefinerPattern()
      {
        if (m_edge_breaker) delete m_edge_breaker;
      }

      virtual void doBreak() {}

      void setSubPatterns( std::vector<UniformRefinerPatternBase *>& bp, percept::PerceptMesh& eMesh )
      {
        EXCEPTWATCH;
        bp = std::vector<UniformRefinerPatternBase *>(2u, 0);

        if (eMesh.get_spatial_dim() == 2)
          {
            bp[0] = this;
#if EDGE_BREAKER_Q4_Q8_1
            bp[1] = m_edge_breaker;
#endif
          }
        else if (eMesh.get_spatial_dim() == 3)
          {
          }

      }

      void fillNeededEntities(std::vector<NeededEntityType>& needed_entities)
      {
        needed_entities.resize(1);
        needed_entities[0].first = m_eMesh.edge_rank();   
        setToOne(needed_entities);
      }

      virtual unsigned getNumNewElemPerElem() { return 1; }

      void 
      createNewElements(percept::PerceptMesh& eMesh, NodeRegistry& nodeRegistry, 
                        stk::mesh::Entity& element,  NewSubEntityNodesType& new_sub_entity_nodes, vector<stk::mesh::Entity *>::iterator& element_pool,
                        stk::mesh::FieldBase *proc_rank_field=0)
      {
        genericEnrich_createNewElements(eMesh, nodeRegistry,
                                        element, new_sub_entity_nodes, element_pool,
                                        proc_rank_field);
      }      
    };

  }
}
#endif
