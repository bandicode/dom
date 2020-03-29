// Copyright (C) 2019-2020 Vincent Chambrin
// This file is part of the 'dom' project
// For conditions of distribution and use, see copyright notice in LICENSE

#include "dom/list.h"

#include <algorithm>

namespace dom
{

const std::string List::TypeId = "list";
const std::string ListItem::TypeId = "listitem";

const std::string& ListItem::type() const
{
  return TypeId;
}

const std::string& List::type() const
{
  return TypeId;
}

ListItem::ListItem(Content c)
  : content(std::move(c))
{

}

List::List(std::string mark)
  : marker(mark)
{

}

void List::removeItem(const std::shared_ptr<ListItem>& item)
{
  auto it = std::find(items.begin(), items.end(), item);

  if (it != items.end())
    items.erase(it);
}

} // namespace dom
