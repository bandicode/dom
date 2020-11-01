// Copyright (C) 2019 Vincent Chambrin
// This file is part of the 'dom' project
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef DOM_PARAGRAPH_LINK_H
#define DOM_PARAGRAPH_LINK_H

#include "dom/paragraph/paragraph-metadata.h"

#include <string>

namespace dom
{

class DOM_API Link : public ParagraphMetaData
{
public:
  ~Link() = default;

  Link(const ParagraphRange& pr, std::string url);

  static const std::string TypeId;
  const std::string& className() const override;

  const std::string& url() const;
  void setUrl(std::string url);

private:
  std::string m_url;
};

} // namespace dom

namespace dom
{

inline Link::Link(const ParagraphRange& pr, std::string url)
  : ParagraphMetaData(pr),
    m_url(std::move(url))
{

}

inline const std::string& Link::url() const
{
  return m_url;
}

inline void Link::setUrl(std::string url)
{
  m_url = std::move(url);
}

} // namespace dom

#endif // DOM_PARAGRAPH_LINK_H
