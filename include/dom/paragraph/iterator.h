// Copyright (C) 2019 Vincent Chambrin
// This file is part of the 'dom' project
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef DOM_PARAGRAPH_ITERATOR_H
#define DOM_PARAGRAPH_ITERATOR_H

#include "dom/paragraph/range.h"

#include <memory>

namespace dom
{

class ParagraphMetaData;

class DOM_API ParagraphIterator
{
private:
  const Paragraph* m_par;
  size_t m_parent_index;
  size_t m_index;
  bool m_text;

public:
  ParagraphIterator(const ParagraphIterator&) = default;

  explicit ParagraphIterator(const Paragraph& p);
  ParagraphIterator(const Paragraph& p, size_t parent_index);
  ParagraphIterator(const Paragraph& p, size_t parent_index, size_t index, bool text);

  const Paragraph& paragraph() const;
  ParagraphRange range() const;

  bool isText() const;
  bool hasChild() const;

  bool isEnd() const;

  ParagraphIterator begin() const;
  ParagraphIterator end() const;

  ParagraphIterator& operator++();
  ParagraphIterator operator++(int);

  std::shared_ptr<ParagraphMetaData> operator*() const;

  bool operator==(const ParagraphIterator& other) const;
  bool operator!=(const ParagraphIterator& other) const;

protected:
  bool isChild() const;
};

} // namespace dom

#endif // DOM_PARAGRAPH_ITERATOR_H
