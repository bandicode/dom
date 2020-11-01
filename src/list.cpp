// Copyright (C) 2019-2020 Vincent Chambrin
// This file is part of the 'dom' project
// For conditions of distribution and use, see copyright notice in LICENSE

#include "dom/list.h"

#include <algorithm>

namespace dom
{

const std::string List::TypeId = "list";
const std::string ListItem::TypeId = "listitem";

const std::string& ListItem::className() const
{
  return TypeId;
}

const std::string& List::className() const
{
  return TypeId;
}

ListItem::ListItem()
{

}

const NodeList& ListItem::childNodes() const
{
  return content;
}

void ListItem::appendChild(std::shared_ptr<Node> n)
{
  removeFromParent(n);
  append(content, n);
  registerChild(n);
}

void ListItem::removeChild(std::shared_ptr<Node> n)
{
  remove(content, n);
}

GenericMetaObject<ListItem, std::string, int> ListItem::staticMetaObject = {
  {
    {"marker", &ListItem::marker},
    {"value", &ListItem::value},
  }, &Element::staticMetaObject
};

MetaObject* ListItem::metaObject() const
{
  return &staticMetaObject;
}


List::List(std::string mark)
  : marker(mark)
{

}

GenericMetaObject<List, std::string, bool, bool> List::staticMetaObject = {
  {
    {"marker", &List::marker},
    {"ordered", &List::ordered},
    {"reversed", &List::reversed},
  }, &Element::staticMetaObject
};

MetaObject* List::metaObject() const
{
  return &staticMetaObject;
}

const NodeList& List::childNodes() const
{
  return items;
}

void List::appendChild(std::shared_ptr<Node> n)
{
  if (!n->is<ListItem>())
  {
    // @TODO: throw
    return;
  }

  removeFromParent(n);
  append(items, n);
  registerChild(n);
}

void List::removeChild(std::shared_ptr<Node> n)
{
  remove(items, n);
}

void List::removeItem(const std::shared_ptr<ListItem>& item)
{
  auto it = std::find(items.begin(), items.end(), item);

  if (it != items.end())
    items.erase(it);
}

} // namespace dom
