// Copyright (C) 2019 Vincent Chambrin
// This file is part of the 'dom' project
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef DOM_PARAGRAPH_TEXTSTYLE_H
#define DOM_PARAGRAPH_TEXTSTYLE_H

#include "dom/paragraph/paragraph-metadata.h"

#include <string>

namespace dom
{

class DOM_API TextStyle : public ParagraphMetaData
{
public:
  TextStyle(const ParagraphRange& pr, std::string style);

  static const std::string TypeId;
  const std::string& type() const override;

  const std::string& style() const;
  void setStyle(std::string str);

private:
  std::string m_style;
};

} // namespace dom

namespace dom
{

inline TextStyle::TextStyle(const ParagraphRange& pr, std::string style)
  : ParagraphMetaData(pr),
    m_style(std::move(style))
{

}

inline const std::string& TextStyle::style() const
{
  return m_style;
}

inline void TextStyle::setStyle(std::string str)
{
  m_style = std::move(str);
}

} // namespace dom

#endif // DOM_PARAGRAPH_TEXTSTYLE_H
