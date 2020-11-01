// Copyright (C) 2019-2020 Vincent Chambrin
// This file is part of the 'dom' project
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef DOM_NODE_H
#define DOM_NODE_H

#include "dom/defs.h"

#include <memory>
#include <string>
#include <type_traits>
#include <vector>

namespace dom
{

class Node;

typedef std::vector<std::shared_ptr<Node>> NodeList;

class DOM_API Node : public std::enable_shared_from_this<Node>
{
public:
  Node() = default;
  Node(const Node &) = delete;
  virtual ~Node() = default;

  explicit Node(std::shared_ptr<Node> parent);

  virtual const std::string& className() const = 0;

  template<typename T>
  bool is() const
  {
    return (className() == T::TypeId) || (!std::is_final<T>::value && dynamic_cast<const T*>(this) != nullptr);
  }

  virtual bool isElement() const;

  std::shared_ptr<Node> parentNode() const;

  virtual const NodeList& childNodes() const;
  bool hasChildNodes() const;
  virtual void appendChild(std::shared_ptr<Node> n);
  virtual void removeChild(std::shared_ptr<Node> n);

  Node& operator=(const Node&) = delete;
  Node& operator=(Node&&) = delete;

protected:
  static void removeFromParent(std::shared_ptr<Node> c);
  void registerChild(std::shared_ptr<Node> c);
  static void append(std::vector<std::shared_ptr<Node>>& vec, const std::shared_ptr<Node>& n);
  static void remove(std::vector<std::shared_ptr<Node>>& vec, const std::shared_ptr<Node>& n);

private:
  std::weak_ptr<Node> m_parent;
};

} // namespace dom

#endif // DOM_NODE_H
