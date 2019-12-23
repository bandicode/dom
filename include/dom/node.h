// Copyright (C) 2019 Vincent Chambrin
// This file is part of the 'dom' project
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef DOM_NODE_H
#define DOM_NODE_H

#include "dom/defs.h"

#include <string>

namespace dom
{

class DOM_API Node
{
public:
  Node() = default;
  Node(const Node &) = delete;
  virtual ~Node() = default;

  virtual const std::string& type() const = 0;

  template<typename T>
  bool is() const
  {
    return type() == T::TypeId;
  }

  Node& operator=(const Node&) = delete;
  Node& operator=(Node&&) = delete;
};

} // namespace dom

#endif // DOM_NODE_H
