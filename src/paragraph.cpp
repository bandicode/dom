// Copyright (C) 2019 Vincent Chambrin
// This file is part of the 'dom' project
// For conditions of distribution and use, see copyright notice in LICENSE

#include "dom/paragraph.h"

#include "dom/paragraph/paragraph-metadata.h"

#include <algorithm>

namespace dom
{

const std::string Paragraph::TypeId = "paragraph";

const std::string& Paragraph::type() const
{
  return TypeId;
}

ParagraphRange::ParagraphRange(const Paragraph& p, size_t begin, size_t end)
  : m_par(&p),
    m_begin(begin),
    m_end(end)
{
  if (m_end == std::numeric_limits<size_t>::max())
  {
    m_end = p.text().size();
  }
}

const Paragraph& ParagraphRange::paragraph() const
{
  return *m_par;
}

size_t ParagraphRange::begin() const
{
  return m_begin;
}

size_t ParagraphRange::end() const
{
  return m_end;
}

std::string ParagraphRange::text() const
{
  return std::string(paragraph().text().begin() + begin(), paragraph().text().begin() + end());
}

ParagraphMetaData::ParagraphMetaData(const ParagraphRange& parrange)
  : m_range(parrange)
{

}

const ParagraphRange& ParagraphMetaData::range() const
{
  return m_range;
}

void Paragraph::setText(std::string text)
{
  m_metadata.clear();

  m_text = std::move(text);
}

void Paragraph::addChar(char c)
{
  m_text.push_back(c);
}

void Paragraph::addText(const std::string& text)
{
  m_text.insert(m_text.end(), text.begin(), text.end());
}

void Paragraph::addMetaData(const std::shared_ptr<ParagraphMetaData>& md)
{
  using PMD = std::shared_ptr<ParagraphMetaData>;

  auto it = std::upper_bound(m_metadata.begin(), m_metadata.end(), md, [](const PMD& lhs, const PMD& rhs) {
    return lhs->range().begin() < rhs->range().begin() ||
      (lhs->range().begin() == rhs->range().begin() && lhs->range().end() < rhs->range().end());
    });

  m_metadata.insert(it, md);
}

} // namespace dom
