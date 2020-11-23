#ifndef __NODE_H__
#define __NODE_H__
#include <iostream>
#include <list>
#include <string>

class Node {
 private:
  std::list<int> adjacents;
  int number;

 public:
  Node();
  Node(int number);

  // Agrega un vertice como adyacente al nodo actual
  // Pre: adjacent es un nodo dentro del grafo.
  int addAdjacent(int adjacent);

  // Devuelve la lista de adyacencia del nodo.
  std::list<int> getAdjacents();

  // DEBUG Function
  void printNumber();
};

#endif
