// Copyright (C) 2019 Vincent Chambrin
// This file is part of the 'dom' project
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef DOM_IMAGE_H
#define DOM_IMAGE_H

#include "dom/node.h"

namespace dom
{

class DOM_API Image : public Node
{
public:
  virtual ~Image() = default;

  static const std::string Type;
  const std::string& type() const override;

  explicit Image(std::string src);

  const std::string& source() const;
  int width() const;
  int height() const;

  void setSource(std::string src);
  void setWidth(int w);
  void setHeight(int h);

private:
  std::string m_source;
  int m_width = -1;
  int m_height = -1;
};

} // namespace dom

namespace dom
{

inline Image::Image(std::string src)
  : m_source(std::move(src))
{

}

inline const std::string& Image::source() const
{
  return m_source;
}

inline int Image::width() const
{
  return m_width;
}

inline int Image::height() const
{
  return m_height;
}

inline void Image::setSource(std::string src)
{
  m_source = std::move(src);
}

inline void Image::setWidth(int w)
{
  m_width = w;
}

inline void Image::setHeight(int h)
{
  m_height = h;
}

} // namespace dom

#endif // DOM_IMAGE_H
