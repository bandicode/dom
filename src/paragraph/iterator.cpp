// Copyright (C) 2019 Vincent Chambrin
// This file is part of the 'dom' project
// For conditions of distribution and use, see copyright notice in LICENSE

#include "dom/paragraph/iterator.h"

#include "dom/paragraph.h"

#include <algorithm>
#include <cassert>
#include <stdexcept>

namespace dom
{

static size_t find_iterator_end(const Paragraph& p, size_t self_begin)
{
  const size_t par_metadata_end = p.metadata().at(self_begin)->range().end();
  size_t self_end = self_begin;

  while (self_end < p.metadata().size() && p.metadata().at(self_end)->range().end() <= par_metadata_end)
    ++self_end;

  return self_end;
}

ParagraphIterator::ParagraphIterator(const Paragraph& p)
  : m_par(&p),
    m_parent_index(p.metadata().size()),
    m_index(0)
{
  m_text = p.metadata().empty() || p.metadata().front()->range().begin() > 0;
}

ParagraphIterator::ParagraphIterator(const Paragraph& p, size_t parent_index)
  : m_par(&p),
    m_parent_index(parent_index),
    m_index(parent_index+1),
    m_text(true)
{
  const ParagraphRange r = range();
  m_text = (r.end() - r.begin()) > 0;
}

ParagraphIterator::ParagraphIterator(const Paragraph& p, size_t parent_index, size_t index, bool text)
  : m_par(&p),
    m_parent_index(parent_index),
    m_index(index),
    m_text(text)
{

}

const Paragraph& ParagraphIterator::paragraph() const
{
  return *m_par;
}

ParagraphRange ParagraphIterator::range() const
{
  if (paragraph().metadata().empty())
    return ParagraphRange{ paragraph() };

  if (!isChild())
  {
    if (m_text)
    {
      if (m_index == 0)
      {
        return ParagraphRange{ paragraph(), 0, paragraph().metadata().at(0)->range().begin() };
      }
      else if (m_index == paragraph().metadata().size())
      {
        const size_t begin = paragraph().metadata().at(m_index - 1)->range().end();
        const size_t end = paragraph().length();
        return ParagraphRange{ paragraph(), begin, end };
      }
      else
      {
        const size_t begin = paragraph().metadata().at(m_index - 1)->range().end();
        const size_t end = paragraph().metadata().at(m_index)->range().begin();
        return ParagraphRange{ paragraph(), begin, end };
      }
    }
    else
    {
      return paragraph().metadata().at(m_index)->range();
    }
  }
  else
  {
    if (m_text)
    {
      const size_t end_index = find_iterator_end(paragraph(), m_parent_index);

      if (m_index == m_parent_index + 1)
      {
        const size_t begin = paragraph().metadata().at(m_parent_index)->range().begin();
        const size_t end = paragraph().metadata().at(m_index)->range().begin();
        return ParagraphRange{ paragraph(), begin, end };
      }
      else if (m_index == end_index)
      {
        const size_t begin = paragraph().metadata().at(m_index - 1)->range().end();
        const size_t end = paragraph().metadata().at(m_parent_index)->range().end();;
        return ParagraphRange{ paragraph(), begin, end };
      }
      else
      {
        const size_t begin = paragraph().metadata().at(m_index - 1)->range().end();
        const size_t end = paragraph().metadata().at(m_index)->range().begin();
        return ParagraphRange{ paragraph(), begin, end };
      }
    }
    else
    {
      return paragraph().metadata().at(m_index)->range();
    }
  }
}

bool ParagraphIterator::isText() const
{
  return m_text;
}

bool ParagraphIterator::hasChild() const
{
  const size_t end_index = find_iterator_end(paragraph(), m_index);
  return (end_index - m_index) > 1;
}

bool ParagraphIterator::isChild() const
{
  return m_parent_index != paragraph().metadata().size();
}

bool ParagraphIterator::isEnd() const
{
  const size_t end_index = m_parent_index < paragraph().metadata().size() ?
    find_iterator_end(paragraph(), m_parent_index) : m_parent_index;

  return m_index == end_index && !m_text;
}

ParagraphIterator ParagraphIterator::begin() const
{
  return ParagraphIterator{ paragraph(), m_index };
}

ParagraphIterator ParagraphIterator::end() const
{
  ParagraphIterator it{ paragraph() };
  it.m_text = false;
  it.m_parent_index = m_index;
  it.m_index = find_iterator_end(paragraph(), m_index);
  return it;
}

ParagraphIterator& ParagraphIterator::operator++()
{
  assert(!isEnd());

  if (m_text)
  {
    m_text = false;
  }
  else
  {
    m_text = true;
    m_index = find_iterator_end(paragraph(), m_index);

    if (range().end() - range().begin() == 0)
    {
      ++(*this);
    }
  }

  return *this;
}

ParagraphIterator ParagraphIterator::operator++(int)
{
  ParagraphIterator copy = *(this);
  ++(*this);
  return copy;
}

std::shared_ptr<ParagraphMetaData> ParagraphIterator::operator*() const
{
  return m_text ? nullptr : paragraph().metadata().at(m_index);
}

bool ParagraphIterator::operator==(const ParagraphIterator& other) const
{
  return m_par == other.m_par
    && m_parent_index == other.m_parent_index
    && m_index == other.m_index
    && m_text == other.m_text;
}

bool ParagraphIterator::operator!=(const ParagraphIterator& other) const
{
  return !(*this == other);
}

} // namespace dom
