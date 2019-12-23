// Copyright (C) 2019 Vincent Chambrin
// This file is part of the 'dom' project
// For conditions of distribution and use, see copyright notice in LICENSE

#include "dom/paragraph/link.h"

namespace dom
{

const std::string Link::TypeId = "link";

const std::string& Link::type() const
{
  return TypeId;
}

} // namespace dom
