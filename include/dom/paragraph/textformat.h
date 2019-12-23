// Copyright (C) 2019 Vincent Chambrin
// This file is part of the 'dom' project
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef DOM_PARAGRAPH_TEXTFORMAT_H
#define DOM_PARAGRAPH_TEXTFORMAT_H

#include "dom/paragraph/paragraph-metadata.h"

#include <string>

namespace dom
{

class DOM_API TextFormat
{
public:
  TextFormat() = default;
  TextFormat(const TextFormat&) = default;
  TextFormat(TextFormat&&) = default;
  ~TextFormat() = default;

  enum Style {
    Normal = 0,
    Bold = 1,
    Italic = 2,
  };

  const std::string& font() const;
  int size() const;
  Style style() const;
  bool underline() const;
  bool strikethrough() const;

  void setFont(std::string str);
  void setSize(int s);
  void setStyle(Style s);
  void setUnderline(bool on = true);
  void setStrikethrough(bool on = true);

  TextFormat& operator=(const TextFormat&) = default;
  TextFormat& operator=(TextFormat&&) = default;

private:
  std::string m_font;
  int m_size = -1;
  Style m_style = Normal;
  bool m_underline = false;
  bool m_strikethrough = false;
};

class DOM_API ParagraphFormat : public ParagraphMetaData
{
private:
  TextFormat m_format;

public:
  ParagraphFormat(const ParagraphRange& pr, const TextFormat& fmt);

  static const std::string TypeId;
  const std::string& type() const override;

  const TextFormat& format() const;
};

} // namespace dom

namespace dom
{

inline const std::string& TextFormat::font() const
{
  return m_font;
}

inline int TextFormat::size() const
{
  return m_size;
}

inline TextFormat::Style TextFormat::style() const
{
  return m_style;
}

inline bool TextFormat::underline() const
{
  return m_underline;
}

inline bool TextFormat::strikethrough() const
{
  return m_strikethrough;
}

inline void TextFormat::setFont(std::string str)
{
  m_font = std::move(str);
}

inline void TextFormat::setSize(int s)
{
  m_size = s;
}

inline void TextFormat::setStyle(Style s)
{
  m_style = s;
}

inline void TextFormat::setUnderline(bool on)
{
  m_underline = on;
}

inline void TextFormat::setStrikethrough(bool on)
{
  m_strikethrough = on;
}

} // namespace dom

#endif // DOM_PARAGRAPH_TEXTFORMAT_H
