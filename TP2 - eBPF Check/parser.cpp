#include "parser.h"

#include <iostream>
#include <string>

#include "instruction.h"
#define WHITESPACE " "

static std::string removePrecedingSpaces(const std::string& s) {
  size_t start = s.find_first_not_of(WHITESPACE);
  return (start == std::string::npos) ? "" : s.substr(start);
}

static std::string removeProcedingSpaces(const std::string& s) {
  size_t end = s.find_last_not_of(WHITESPACE);
  return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

static std::string removeExtraSpaces(const std::string& s) {
  return removeProcedingSpaces(removePrecedingSpaces(s));
}

static void insertLabel(std::string& line, Instruction& instruction) {
  size_t pos = 0;
  if ((pos = line.find_first_of(":")) != line.npos) {
    instruction.setLabel(line.substr(0, pos));
    line.erase(0, pos + 1);
  }

  line = removeExtraSpaces(line);
}

static void insertType(std::string& line, Instruction& instruction) {
  size_t pos = line.find_first_of(" ");
  std::string type = line.substr(0, pos);
  instruction.setType(type);

  line.erase(0, pos + 1);
  line = removeExtraSpaces(line);
}

static void insertLabelReferences(std::string& line, Instruction& instruction) {
  size_t pos = 0;
  if (instruction.isUnconditionalJump()) {
    instruction.addReference(line);
    return;
  }

  pos = line.find_first_of(",");
  if (pos == line.npos) {
    return;
  }

  line.erase(0, pos + 1);
  line = removeExtraSpaces(line);
  pos = line.find_first_of(",");

  if (pos == line.npos) {
    instruction.addReference(line);
    return;
  } else {
    instruction.addReference(line.substr(0, pos));
    line.erase(0, pos + 1);
  }
  line = removeExtraSpaces(line);
  instruction.addReference(line);
}

void Parser::parseLine(std::string line, Instruction& instruction) {
  insertLabel(line, instruction);
  insertType(line, instruction);
  insertLabelReferences(line, instruction);
}
