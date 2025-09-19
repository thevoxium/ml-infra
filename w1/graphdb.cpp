#include <algorithm>
#include <cstddef>
#include <iostream>
#include <memory>
#include <queue>
#include <stack>
#include <stdexcept>
#include <string>
#include <sys/_types/_ssize_t.h>
#include <unordered_map>
#include <variant>
#include <vector>

class Node;
class Edge;
class Graph;

using PropertyValue = std::variant<int, std::string, bool>;
using NodePtr = std::shared_ptr<Node>;
using EdgePtr = std::shared_ptr<Edge>;
using NodeId = size_t;
using EdgeId = size_t;

class Node {
private:
  NodeId id;
  std::string label;
  std::unordered_map<std::string, PropertyValue> properties;

public:
  Node(NodeId id, std::string label) {
    this->id = id;
    this->label = label;
  }

  Node(Node &other) = delete;
  Node &operator=(Node &other) = delete;
  Node(Node &&other) = default;
  Node &operator=(Node &&other) = default;
  ~Node() = default;

  NodeId getId() const;
  const std::string &getLabel() const;
  const std::unordered_map<std::string, PropertyValue> &getMap() const;

  void setProperty(const std::string &key, PropertyValue value);
  bool hasProperty(const std::string &key) const;
  const PropertyValue &getProperty(const std::string &key) const;
};

NodeId Node::getId() const { return this->id; }
const std::string &Node::getLabel() const { return this->label; }
const std::unordered_map<std::string, PropertyValue> &Node::getMap() const {
  return this->properties;
}

void Node::setProperty(const std::string &key, PropertyValue value) {
  this->properties[key] = std::move(value);
}
bool Node::hasProperty(const std::string &key) const {
  return this->properties.find(key) == this->properties.end() ? false : true;
}

const PropertyValue &Node::getProperty(const std::string &key) const {
  auto it = this->properties.find(key);
  if (it == this->properties.end()) {
    throw std::runtime_error("Property '" + key + "' not found");
  }
  return it->second;
}

class Edge {
private:
  EdgeId id;
  std::string label;
  NodePtr from, to;

public:
  Edge(EdgeId id, std::string label, NodePtr from, NodePtr to) {
    this->id = id;
    this->label = label;
    this->from = from;
    this->to = to;
  }

  Edge(Edge &other) = delete;
  Edge &operator=(Edge &other) = delete;
  Edge(Edge &&other) = default;
  Edge &operator=(Edge &&other) = default;
  ~Edge() = default;

  EdgeId getId() const;
  const std::string &getLabel() const;
  const NodePtr &getFrom() const;
  const NodePtr &getTo() const;
};

EdgeId Edge::getId() const { return this->id; }
const std::string &Edge::getLabel() const { return this->label; }
const NodePtr &Edge::getFrom() const { return this->from; }
const NodePtr &Edge::getTo() const { return this->to; }

class Graph {
private:
  NodeId nextNodeId = 0;
  EdgeId nextEdgeId = 0;
  std::unordered_map<NodeId, NodePtr> nodes;
  std::unordered_map<EdgeId, EdgePtr> edges;

public:
  Graph() = default;
  Graph(const Graph &) = delete;
  Graph &operator=(const Graph &) = delete;
  Graph(Graph &&) = default;
  Graph &operator=(Graph &&) = default;

  NodePtr createNode(std::string &label);
  NodePtr getNode(NodeId id) const;
  EdgePtr createEdge(std::string &label);
  EdgePtr getEdge(EdgeId id) const;
};

NodePtr Graph::createNode(std::string &label) {
  NodePtr newNode = std::make_shared<Node>(this->nextNodeId, label);
  this->nodes[this->nextNodeId++] = newNode;
  return newNode;
}
NodePtr Graph::getNode(NodeId id) const {
  auto it = this->nodes.find(id);
  if (it == this->nodes.end()) {
    return nullptr;
  }
  return it->second;
}

EdgePtr Graph::createEdge(std::string &label) {
  EdgePtr newEdge = std::make_shared<Edge>(this->nextEdgeId, label);
  this->edges[this->nextEdgeId++] = newEdge;
  return newEdge;
}
EdgePtr Graph::getEdge(EdgeId id) const {
  auto it = this->edges.find(id);
  if (it == this->edges.end()) {
    return nullptr;
  }
  return it->second;
}
int main() {
  NodePtr nodeA = std::make_shared<Node>(1, "anshul");
  nodeA->setProperty("age", 24);

  NodePtr nodeB = std::make_shared<Node>(1, "batman");
  nodeB->setProperty("age", 45);

  EdgePtr edgeAtoB = std::make_shared<Edge>(1, "AtoB", nodeA, nodeB);
  return 0;
}
