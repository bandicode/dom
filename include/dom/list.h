// Copyright (C) 2019-2020 Vincent Chambrin
// This file is part of the 'dom' project
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef DOM_LIST_H
#define DOM_LIST_H

#include "dom/content.h"
#include "dom/element.h"

namespace dom
{

class DOM_API ListItem : public Node
{
public:
  std::string marker;
  int value = -1;
  Content content;

public:
  explicit ListItem(Content c = {});

  static const std::string TypeId;
  const std::string& type() const override;
};

class DOM_API List : public Element
{
public:
  std::string marker;
  bool ordered = false;
  bool reversed = false;
  std::vector<std::shared_ptr<ListItem>> items;

public:
  explicit List(std::string mark = {});
  ~List() = default;

  static const std::string TypeId;
  const std::string& type() const override;

  void removeItem(const std::shared_ptr<ListItem>& item);
};

} // namespace dom

namespace dom
{

} // namespace dom

#endif // DOM_LIST_H
