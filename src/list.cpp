// Copyright (C) 2019 Vincent Chambrin
// This file is part of the 'dom' project
// For conditions of distribution and use, see copyright notice in LICENSE

#include "dom/list.h"

namespace dom
{

const std::string List::Type = "list";

const std::string& List::type() const
{
  return Type;
}

void List::addItem(std::shared_ptr<Node> n)
{
  m_items.push_back(std::move(n));
}

void List::insertItem(size_t index, std::shared_ptr<Node> n)
{
  m_items.insert(m_items.begin() + index, std::move(n));
}

void List::removeItem(const std::shared_ptr<Node>& n)
{
  auto it = std::find(m_items.begin(), m_items.end(), n);

  if (it != m_items.end())
  {
    removeAt(std::distance(m_items.begin(), it));
  }
}

void List::removeAt(size_t index)
{
  m_items.erase(m_items.begin() + index);
}

} // namespace dom
