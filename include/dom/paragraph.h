// Copyright (C) 2019 Vincent Chambrin
// This file is part of the 'dom' project
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef DOM_PARAGRAPH_H
#define DOM_PARAGRAPH_H

#include "dom/paragraph/paragraph-metadata.h"

#include <memory>
#include <vector>

namespace dom
{

class DOM_API Paragraph : public Node
{
public:
  Paragraph() = default;
  ~Paragraph() = default;

  explicit Paragraph(std::string text);

  static const std::string TypeId;
  const std::string& type() const override;

  const std::string& text() const;
  size_t length() const;

  void setText(std::string text);

  void addChar(char c);
  void addText(const std::string& text);

  const std::vector<std::shared_ptr<ParagraphMetaData>>& metadata() const;

  void addMetaData(const std::shared_ptr<ParagraphMetaData>& md);

  template<typename T, typename...Args>
  void add(ParagraphRange pr, Args&& ... args);

private:
  std::string m_text;
  std::vector<std::shared_ptr<ParagraphMetaData>> m_metadata;
};

} // namespace dom

namespace dom
{

inline Paragraph::Paragraph(std::string text)
  : m_text(std::move(text))
{

}

inline const std::string& Paragraph::text() const
{
  return m_text;
}

inline size_t Paragraph::length() const
{
  return text().length();
}

inline const std::vector<std::shared_ptr<ParagraphMetaData>>& Paragraph::metadata() const
{
  return m_metadata;
}

template<typename T, typename...Args>
inline void Paragraph::add(ParagraphRange pr, Args&& ... args)
{
  auto md = std::make_shared<GenericParagraphMetaData<T>>(pr, T(std::forward<Args>(args)...));
  addMetaData(md);
}


} // namespace dom

#endif // DOM_PARAGRAPH_H