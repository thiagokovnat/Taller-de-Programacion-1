#include "instruction.h"

#include <iostream>
#include <set>
#define EMPTY_STRING ""

Instruction::Instruction() {
  this->instructionType = EMPTY_STRING;
  this->label = EMPTY_STRING;
}

void Instruction::reset() {
  this->instructionType = EMPTY_STRING;
  this->label = EMPTY_STRING;
  this->labelsReferenced.clear();
}

void Instruction::setLabel(std::string label) { this->label = label; }

void Instruction::setType(std::string type) { this->instructionType = type; }

void Instruction::addReference(std::string reference) {
  this->labelsReferenced.push_back(reference);
}

void Instruction::printStatus() {
  std::cout << "Label: " + this->label << std::endl;
  std::cout << "Instruction Type: " + this->instructionType << std::endl;
  std::cout << "Labels referenced: " << std::endl;

  std::list<std::string>::iterator it;
  for (it = this->labelsReferenced.begin(); it != this->labelsReferenced.end();
       it++) {
    std::cout << (*it) << std::endl;
  }
}

int Instruction::isJumpInstruction() {
  std::set<std::string> jmpInstructions;
  jmpInstructions.insert("ja");
  jmpInstructions.insert("jeq");
  jmpInstructions.insert("jneq");
  jmpInstructions.insert("jne");
  jmpInstructions.insert("jlt");
  jmpInstructions.insert("jle");
  jmpInstructions.insert("jgt");
  jmpInstructions.insert("jge");
  jmpInstructions.insert("jset");

  return jmpInstructions.find(this->instructionType) != jmpInstructions.end();
}

int Instruction::isConnectableInstruction() {
  if ((this->instructionType.compare("ret") == 0) ||
      (this->instructionType.compare("jmp") == 0)) {
    return 0;
  }

  if (this->instructionType.compare(EMPTY_STRING) == 0) {
    return 0;
  }

  if (this->isJumpInstruction() && this->labelsReferenced.size() == 2) {
    return 0;
  }

  return 1;
}

int Instruction::isEmpty() { return (this->instructionType.compare("") == 0); }

void Instruction::fillInfo(
    std::map<std::string, std::list<int>>& referenceToLabel,
    std::map<std::string, int>& labelPosition, unsigned int instructionNo) {
  if (this->label.compare(EMPTY_STRING) != 0) {
    labelPosition.insert({this->label, instructionNo});
  }

  std::list<std::string>::iterator it;
  for (it = this->labelsReferenced.begin(); it != this->labelsReferenced.end();
       it++) {
    referenceToLabel[(*it)].push_back(instructionNo);
  }
}

int Instruction::isUnconditionalJump() {
  return this->instructionType.compare("jmp") == 0;
}
