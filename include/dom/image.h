// Copyright (C) 2019 Vincent Chambrin
// This file is part of the 'dom' project
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef DOM_IMAGE_H
#define DOM_IMAGE_H

#include "dom/element.h"

namespace dom
{

class DOM_API Image : public Element
{
public:
  std::string src;
  int width = -1;
  int height = -1;

public:
  ~Image() = default;

  static const std::string TypeId;
  const std::string& type() const override;

  explicit Image(std::string source);

protected:
  static GenericMetaObject<Image, std::string, int, int> staticMetaObject;
  MetaObject* metaObject() const override;
};

} // namespace dom

namespace dom
{

inline Image::Image(std::string source)
  : src(std::move(source))
{

}

} // namespace dom

#endif // DOM_IMAGE_H
