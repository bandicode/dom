// Copyright (C) 2019 Vincent Chambrin
// This file is part of the 'dom' project
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef DOM_PARAGRAPH_NOTE_H
#define DOM_PARAGRAPH_NOTE_H

#include "dom/paragraph/paragraph-metadata.h"

#include <memory>
#include <string>

namespace dom
{

class DOM_API Note : public ParagraphMetaData
{
public:
  ~Note() = default;

  enum Location
  {
    FootNote,
    SideNote,
  };

  Note(const ParagraphRange& pr, std::shared_ptr<Paragraph> par, Location loc = FootNote);

  static const std::string TypeId;
  const std::string& className() const override;

private:
  std::shared_ptr<Paragraph> m_content;
  Location m_location;
};

} // namespace dom

namespace dom
{

inline Note::Note(const ParagraphRange& pr, std::shared_ptr<Paragraph> par, Location loc)
  : ParagraphMetaData(pr),
    m_content(std::move(par)),
    m_location(loc)
{

}

} // namespace dom

#endif // DOM_PARAGRAPH_NOTE_H
