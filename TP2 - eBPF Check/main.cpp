#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "eBPFCheck.h"
#include "graph.h"
#include "instruction.h"
#include "node.h"
#include "parser.h"
#include "thread.h"

int main(int argc, char** argv) {
  if (argc < 3) {
    return 0;
  }

  int threadCount = std::stoi(argv[1]);

  std::list<std::string> fileList;
  for (int i = 2; i < argc; i++) {
    fileList.push_back(argv[i]);
  }

  ProtectedFileCenter fc(fileList);
  ProtectedResultCenter rc;

  std::vector<Thread*> threads;
  for (int i = 0; i < threadCount; i++) {
    threads.push_back(new eBPFCheck(fc, rc));
  }

  for (int i = 0; i < threadCount; i++) {
    threads[i]->start();
  }

  for (int i = 0; i < threadCount; i++) {
    threads[i]->join();
    delete threads[i];
  }

  rc.printResult();
}
