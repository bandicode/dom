// Copyright (C) 2019 Vincent Chambrin
// This file is part of the 'dom' project
// For conditions of distribution and use, see copyright notice in LICENSE

#include "dom/image.h"

namespace dom
{

const std::string Image::TypeId = "image";

const std::string& Image::type() const
{
  return TypeId;
}

GenericMetaObject<Image, std::string, int, int> Image::staticMetaObject = {
  {
    {"src", &Image::src},
    {"width", &Image::width},
    {"height", &Image::height},
  }, &Element::staticMetaObject
};

MetaObject* Image::metaObject() const
{
  return &staticMetaObject;
}

} // namespace dom
