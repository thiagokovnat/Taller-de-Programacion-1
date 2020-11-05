#include "node.h"

#include <algorithm>
#include <iostream>
#include <list>
#include <string>

Node::Node() {}
Node::Node(int number) { this->number = number; }

// Agrega un vertice como adyacente al nodo actual
// Pre: adjacent es un nodo dentro del grafo.
int Node::addAdjacent(int node) {
  if (std::find(this->adjacents.begin(), this->adjacents.end(), node) !=
      this->adjacents.end()) {
    return 0;
  }

  this->adjacents.push_back(node);
  return 0;
}

// Devuelve la lista de adyacencia del nodo.
std::list<int> Node::getAdjacents() { return this->adjacents; }

// DEBUG Function
void Node::printNumber() { std::cout << this->number << std::endl; }
