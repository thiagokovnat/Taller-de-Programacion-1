#ifndef __EBPFCHECK_H__
#define __EBPFCHECK_H__
#include <fstream>
#include <string>

#include "graph.h"
#include "protectedFileCenter.h"
#include "protectedResultCenter.h"
#include "thread.h"

class eBPFCheck : public Thread {
 private:
  ProtectedFileCenter& fileCenter;
  ProtectedResultCenter& resultCenter;

  std::string fileName;
  std::ifstream stream;
  void fillLabels(std::map<std::string, std::list<int>>& referenceToLabel,
                  std::map<std::string, int>& labelPosition, Graph& graph);

 public:
  eBPFCheck(ProtectedFileCenter& fileCenter,
            ProtectedResultCenter& resultCenter);
  void constructGraphAndStoreResult();
  void storeResult(Graph& graph);
  void run();
};

#endif
