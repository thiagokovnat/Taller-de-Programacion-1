#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <iostream>
#include <map>
#include <string>

#include "node.h"

class Graph {
 private:
  unsigned int nodeAmount;
  std::map<int, Node> nodes;

  // Funcion de utilidad interna para detectar ciclos en un grafo.
  // Pre: visited y recursive no son nulos.
  int cycleCheck(unsigned int node, int* visited, int* recursive);

  // Performa DFS sobre el grafo, dejando los nodos visitados en visited.
  void DFS(unsigned int node, std::list<int>& visited);

 public:
  Graph();

  void printStatus();

  // Devuelve 1 si hay nodos no conectados en el grafo.
  int hasUnconnectedNodes();

  // Agrega un nodo al grafo.
  int addNode(unsigned int number);

  // Agrega un vertce entre dos nodos del grafo
  // Pre: tanto from como to son nodos insertados previamente en el grafo.
  int addEdges(unsigned int from, unsigned int to);

  // Devuelve 1 si encuentra un ciclo en el grafo.
  int hasCycle();

  ~Graph();
};

#endif
