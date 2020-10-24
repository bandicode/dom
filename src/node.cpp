// Copyright (C) 2019-2020 Vincent Chambrin
// This file is part of the 'dom' project
// For conditions of distribution and use, see copyright notice in LICENSE

#include "dom/node.h"

namespace dom
{

Node::Node(std::shared_ptr<Node> parent)
  : m_parent(parent)
{

}

std::shared_ptr<Node> Node::parentNode() const
{
  return m_parent.lock();
}

const NodeList& Node::childNodes() const
{
  static const NodeList static_instance = {};
  return static_instance;
}

bool Node::hasChildNodes() const
{
  return !childNodes().empty();
}

void Node::appendChild(std::shared_ptr<Node> n)
{
  // @TODO: throw ?
}

void Node::removeChild(std::shared_ptr<Node> n)
{
  // @TODO: throw ?
}

void Node::removeFromParent(std::shared_ptr<Node> c)
{
  auto old_parent = c->parentNode();
  c->m_parent.reset();

  if (old_parent)
    old_parent->removeChild(c);
}

void Node::registerChild(std::shared_ptr<Node> c)
{
  c->m_parent = shared_from_this(); 
}

void Node::append(std::vector<std::shared_ptr<Node>>& vec, const std::shared_ptr<Node>& n)
{
  vec.push_back(n);
}

void Node::remove(std::vector<std::shared_ptr<Node>>& vec, const std::shared_ptr<Node>& n)
{
  auto it = std::find(vec.begin(), vec.end(), n);

  if (it != vec.end())
    vec.erase(it);
}

} // namespace dom
