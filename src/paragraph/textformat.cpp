// Copyright (C) 2019 Vincent Chambrin
// This file is part of the 'dom' project
// For conditions of distribution and use, see copyright notice in LICENSE

#include "dom/paragraph/textformat.h"

namespace dom
{

const std::string ParagraphFormat::TypeId = "textformat";

const std::string& ParagraphFormat::type() const
{
  return TypeId;
}

ParagraphFormat::ParagraphFormat(const ParagraphRange& pr, const TextFormat& fmt)
  : ParagraphMetaData(pr),
    m_format(fmt)
{

}

const TextFormat& ParagraphFormat::format() const
{
  return m_format;
}

} // namespace dom
