// Copyright (C) 2019 Vincent Chambrin
// This file is part of the 'dom' project
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef DOM_LIST_H
#define DOM_LIST_H

#include "dom/node.h"

#include <memory>
#include <vector>

namespace dom
{

class DOM_API List : public Node
{
public:
  ~List() = default;

  static const std::string Type;
  const std::string& type() const override;

  const std::vector<std::shared_ptr<Node>>& items() const;

  void addItem(std::shared_ptr<Node> n);
  void insertItem(size_t index, std::shared_ptr<Node> n);
  void removeItem(const std::shared_ptr<Node>& n);
  void removeAt(size_t index);

private:
  std::vector<std::shared_ptr<Node>> m_items;
};

} // namespace dom

namespace dom
{

inline const std::vector<std::shared_ptr<Node>>& List::items() const
{
  return m_items;
}

} // namespace dom

#endif // DOM_LIST_H
