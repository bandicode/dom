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

static std::shared_ptr<Element> get_element_by_id(const std::shared_ptr<Node>& node, const std::string& id)
{
  if (node->isElement() && std::static_pointer_cast<Element>(node)->id == id)
    return std::static_pointer_cast<Element>(node);

  for (auto child : node->childNodes())
  {
    auto result = get_element_by_id(child, id);

    if (result)
      return result;
  }

  return nullptr;
}

std::shared_ptr<Element> Document::getElementById(const std::string& id) const
{
  for (auto child : childNodes())
  {
    auto result = get_element_by_id(child, id);

    if (result)
      return result;
  }

  return nullptr;
}

} // namespace dom
