// Copyright (C) 2019 Vincent Chambrin
// This file is part of the 'dom' project
// For conditions of distribution and use, see copyright notice in LICENSE

#include "dom/paragraph/textstyle.h"

namespace dom
{

const std::string TextStyle::TypeId = "textstyle";

const std::string& TextStyle::className() const
{
  return TypeId;
}

} // namespace dom
