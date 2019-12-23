// Copyright (C) 2019 Vincent Chambrin
// This file is part of the 'dom' project
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef DOM_PARAGRAPH_METADATA_H
#define DOM_PARAGRAPH_METADATA_H

#include "dom/node.h"

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

class DOM_API ParagraphMetaData : public Node
{
private:
  ParagraphRange m_range;

protected:
  ParagraphMetaData(const ParagraphRange& parrange);

public:
  const ParagraphRange& range() const;

  template<typename T>
  const T& get() const;
};

template<typename T>
class GenericParagraphMetaData : public ParagraphMetaData
{
private:
  T m_value;

public:
  GenericParagraphMetaData(const ParagraphRange& pr, T value)
    : ParagraphMetaData(pr),
      m_value(std::move(value))
  {

  }

  const std::string& type() const override
  {
    return T::TypeId;
  }

  T& value() { return m_value;  }
  const T& value() const { return m_value; }
};

} // namespace dom

namespace dom
{

template<typename T>
inline const T& ParagraphMetaData::get() const
{
  return static_cast<const GenericParagraphMetaData<T>*>(this)->value();
}

} // namespace dom

#endif // DOM_PARAGRAPH_METADATA_H
