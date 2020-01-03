// Copyright (C) 2019 Vincent Chambrin
// This file is part of the 'dom' project
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef DOM_PARAGRAPH_RANGE_H
#define DOM_PARAGRAPH_RANGE_H

#include "dom/defs.h"

#include <limits>
#include <string>

namespace dom
{

class Paragraph;

class DOM_API ParagraphRange
{
private:
  const Paragraph* m_par;
  size_t m_begin;
  size_t m_end;

public:
  ParagraphRange(const ParagraphRange&) = default;

  explicit ParagraphRange(const Paragraph& p, size_t begin = 0, size_t end = std::numeric_limits<size_t>::max());

  const Paragraph& paragraph() const;
  size_t begin() const;
  size_t end() const;

  std::string text() const;
};

inline bool operator==(const ParagraphRange& lhs, const ParagraphRange& rhs)
{
  return lhs.begin() == rhs.begin() && rhs.end() == lhs.end();
}

inline bool operator!=(const ParagraphRange& lhs, const ParagraphRange& rhs)
{
  return !(lhs == rhs);
}

} // namespace dom

#endif // DOM_PARAGRAPH_RANGE_H
