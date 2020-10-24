// Copyright (C) 2019 Vincent Chambrin
// This file is part of the 'dom' project
// For conditions of distribution and use, see copyright notice in LICENSE

#include "dom/document.h"

#include <algorithm>

namespace dom
{

const std::string Document::Type = "document";

const std::string& Document::type() const
{
  return Type;
}

void Document::addNode(std::shared_ptr<Node> n)
{
  m_nodes.push_back(std::move(n));
}

void Document::insertNode(size_t index, std::shared_ptr<Node> n)
{
  m_nodes.insert(m_nodes.begin() + index, std::move(n));
}

void Document::removeNode(const std::shared_ptr<Node>& n)
{
  auto it = std::find(m_nodes.begin(), m_nodes.end(), n);

  if (it != m_nodes.end())
  {
    removeAt(std::distance(m_nodes.begin(), it));
  }
}

const NodeList& Document::childNodes() const
{
  return m_nodes;
}

void Document::appendChild(std::shared_ptr<Node> n)
{
  removeFromParent(n);
  append(m_nodes, n);
  registerChild(n);
}

void Document::removeChild(std::shared_ptr<Node> n)
{
  remove(m_nodes, n);
}

void Document::removeAt(size_t index)
{
  m_nodes.erase(m_nodes.begin() + index);
}

void Document::swap(size_t i, size_t j)
{
  std::swap(m_nodes[i], m_nodes[j]);
}

} // namespace dom
