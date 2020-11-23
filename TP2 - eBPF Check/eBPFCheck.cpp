#include "eBPFCheck.h"

#include <list>
#include <map>

#include "graph.h"
#include "instruction.h"
#include "parser.h"

eBPFCheck::eBPFCheck(ProtectedFileCenter& fc, ProtectedResultCenter& rc)
    : fileCenter(fc), resultCenter(rc) {}

void eBPFCheck::run() {
  while ((this->fileName = fileCenter.popIfNotEmpty()).compare("") != 0) {
    this->stream.open(this->fileName, std::ifstream::in);
    this->constructGraphAndStoreResult();
    this->stream.close();
  }
}
void eBPFCheck::constructGraphAndStoreResult() {
  Graph graph;
  unsigned int instructionNo = 0;
  Parser myParser;
  Instruction currentInstruction;
  std::map<std::string, std::list<int>> referenceToLabel;
  std::map<std::string, int> labelPosition;
  unsigned int isLastInstructionValid = 0;

  while (this->stream.good()) {
    std::string line;
    std::getline(this->stream, line, '\n');

    myParser.parseLine(line, currentInstruction);

    if (!currentInstruction.isEmpty()) {
      graph.addNode(instructionNo);
      currentInstruction.fillInfo(referenceToLabel, labelPosition,
                                  instructionNo);

      instructionNo++;
    } else {
      continue;
    }

    if (isLastInstructionValid) {
      graph.addEdges(instructionNo - 2, instructionNo - 1);
    }

    if (currentInstruction.isConnectableInstruction()) {
      isLastInstructionValid = 1;
    } else {
      isLastInstructionValid = 0;
    }

    currentInstruction.reset();
  }

  this->fillLabels(referenceToLabel, labelPosition, graph);
  this->storeResult(graph);
}

void eBPFCheck::storeResult(Graph& graph) {
  if (graph.hasCycle()) {
    this->resultCenter.addAlphabetically(this->fileName,
                                         "FAIL: cycle detected");
  } else if (graph.hasUnconnectedNodes()) {
    this->resultCenter.addAlphabetically(this->fileName,
                                         "FAIL: unused instructions detected");
  } else {
    this->resultCenter.addAlphabetically(this->fileName, "GOOD");
  }
}

void eBPFCheck::fillLabels(
    std::map<std::string, std::list<int>>& referenceToLabel,
    std::map<std::string, int>& labelPosition, Graph& graph) {
  for (auto it : labelPosition) {
    for (auto listIt : referenceToLabel[it.first]) {
      graph.addEdges(listIt, it.second);
    }
  }
}
