#include "MLAPI_Error.h"
#include <string>
#include <iostream>
#include <vector>

namespace MLAPI {

static std::vector<StackEntry> StackData;

void StackPush_(std::string FuncName, std::string FileName, int line)
{
  StackEntry e;
  e.FuncName = FuncName;
  e.FileName = FileName;
  e.line = line;
  StackData.push_back(e);
}

void StackPop()
{
  StackData.pop_back();
}

void StackPrint()
{
  std::cout << std::endl;
  std::cout << "Recorded stack is:" << std::endl;
  std::cout << "==================" << std::endl << std::endl;
  for (unsigned int i = 0 ; i < StackData.size() ; ++i) {
    std::cout << "[" << i << "] " << StackData[i].FuncName << std::endl;
    std::cout << "[" << i << "] " << StackData[i].FileName 
              << ", line " << StackData[i].line << std::endl << std::endl;
  }

}

} // namespace MLAPI
