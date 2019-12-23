// Copyright (C) 2019 Vincent Chambrin
// This file is part of the 'dom' project
// For conditions of distribution and use, see copyright notice in LICENSE

#include "dom/image.h"

namespace dom
{

const std::string Image::Type = "image";

const std::string& Image::type() const
{
  return Type;
}

} // namespace dom
