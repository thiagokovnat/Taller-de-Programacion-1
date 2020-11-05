#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include <list>
#include <map>
#include <string>
class Instruction {
 private:
  std::string instructionType;
  std::string label;
  std::list<std::string> labelsReferenced;
  int isJumpInstruction();

 public:
  Instruction();

  // Reinicia todos los valores de la instruccion a sus valores default.
  void reset();

  int isEmpty();
  int isConnectableInstruction();
  void setLabel(std::string label);
  void setType(std::string type);
  void addReference(std::string reference);
  void fillInfo(std::map<std::string, std::list<int>>& referenceToLabel,
                std::map<std::string, int>& labelPosition,
                unsigned int instructionNo);
  void printStatus();
  int isUnconditionalJump();
};

#endif
