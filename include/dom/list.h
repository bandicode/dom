// Copyright (C) 2019-2020 Vincent Chambrin
// This file is part of the 'dom' project
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef DOM_LIST_H
#define DOM_LIST_H

#include "dom/element.h"

namespace dom
{

class DOM_API ListItem : public Element
{
public:
  std::string marker;
  int value = -1;
  NodeList content; // @TODO: make private

public:
  ListItem();

  static const std::string TypeId;
  const std::string& className() const override;

  const NodeList& childNodes() const override;
  void appendChild(std::shared_ptr<Node> n) override;
  void removeChild(std::shared_ptr<Node> n) override;

protected:
  static GenericMetaObject<ListItem, std::string, int> staticMetaObject;
  MetaObject* metaObject() const override;
};

class DOM_API List : public Element
{
public:
  std::string marker;
  bool ordered = false;
  bool reversed = false;
  NodeList items; // @TODO: make private

public:
  explicit List(std::string mark = {});
  ~List() = default;

  static const std::string TypeId;
  const std::string& className() const override;

  const NodeList& childNodes() const override;
  void appendChild(std::shared_ptr<Node> n) override;
  void removeChild(std::shared_ptr<Node> n) override;

  void removeItem(const std::shared_ptr<ListItem>& item);

protected:
  static GenericMetaObject<List, std::string, bool, bool> staticMetaObject;
  MetaObject* metaObject() const override;
};

} // namespace dom

namespace dom
{

} // namespace dom

#endif // DOM_LIST_H
