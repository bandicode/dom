// Copyright (C) 2019 Vincent Chambrin
// This file is part of the 'dom' project
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef DOM_ELEMENT_H
#define DOM_ELEMENT_H

#include "dom/node.h"

#include <memory>
#include <map>

namespace dom
{

class DOM_API Element : public Node
{
public:
  std::string id;
  std::map<std::string, std::shared_ptr<Node>> attributes;

public:
  using Node::Node;

  bool isElement() const override;
};

} // namespace dom

#endif // DOM_ELEMENT_H
