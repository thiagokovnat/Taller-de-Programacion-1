#ifndef __PARSER_H__
#define __PARSER_H__
#include <string>

#include "instruction.h"

class Parser {
 public:
  void parseLine(std::string line, Instruction& instruction);
};

#endif
