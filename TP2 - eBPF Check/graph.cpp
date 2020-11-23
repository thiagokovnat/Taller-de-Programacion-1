#include "graph.h"

#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <string>

Graph::Graph() { this->nodeAmount = 0; }

// Agrega un nodo al grafo.
int Graph::addNode(unsigned int number) {
  Node newNode(number);

  this->nodes.insert({this->nodeAmount, newNode});
  this->nodeAmount++;

  return 0;
}

// Agrega un vertce entre dos nodos del grafo
// Pre: tanto from como to son nodos insertados previamente en el grafo.
int Graph::addEdges(unsigned int from, unsigned int to) {
  if ((!this->nodes.count(from)) || (!this->nodes.count(to))) {
    return 1;
  }

  this->nodes[from].addAdjacent(to);
  return 0;
}

// Funcion de utilidad interna para detectar ciclos en un grafo.
// Pre: visited y recursive no son nulos.
int Graph::cycleCheck(unsigned int node, int* visited, int* recursive) {
  if (visited[node] == 0) {
    visited[node] = 1;
    recursive[node] = 1;

    std::list<int>::iterator it;
    std::list<int> adj = this->nodes[node].getAdjacents();
    for (it = adj.begin(); it != adj.end(); it++) {
      if (!visited[*it] && this->cycleCheck(*it, visited, recursive)) {
        return 1;
      } else if (recursive[*it]) {
        return 1;
      }
    }
  }
  recursive[node] = 0;
  return 0;
}

// Devuelve 1 si encuentra un ciclo en el grafo.
int Graph::hasCycle() {
  int hasCycle = 0;
  int* visited = new int[this->nodeAmount];
  int* recursive = new int[this->nodeAmount];
  for (unsigned int i = 0; i < this->nodeAmount; i++) {
    visited[i] = 0;
    recursive[i] = 0;
  }

  for (unsigned int i = 0; i < this->nodeAmount; i++) {
    if (this->cycleCheck(i, visited, recursive)) {
      hasCycle = 1;
      break;
    };
  }

  delete[] visited;
  delete[] recursive;

  return hasCycle;
  ;
}

// Performa DFS sobre el grafo, dejando los nodos visitados en visited.
void Graph::DFS(unsigned int node, std::list<int>& visited) {
  visited.push_back(node);

  std::list<int>::iterator it;
  std::list<int> adj = this->nodes[node].getAdjacents();

  for (it = adj.begin(); it != adj.end(); it++) {
    if (std::find(visited.begin(), visited.end(), (*it)) == visited.end()) {
      this->DFS((*it), visited);
    }
  }
}

// Devuelve 1 si hay nodos no conectados en el grafo.
int Graph::hasUnconnectedNodes() {
  std::list<int> visited;

  this->DFS(0, visited);

  for (unsigned int i = 0; i < this->nodeAmount; i++) {
    if (std::find(visited.begin(), visited.end(), i) == visited.end()) {
      return 1;
    }
  }

  return 0;
}

void Graph::printStatus() {
  std::cout << "Node amount";
  std::cout << this->nodeAmount << std::endl;
  ;

  for (auto m : this->nodes) {
    std::cout << m.first << std::endl;
    ;
    std::cout << "Adjacent to: " << std::endl;
    for (auto n : m.second.getAdjacents()) {
      this->nodes[n].printNumber();
    }
    std::cout << "" << std::endl;
  }
}
Graph::~Graph() {}
