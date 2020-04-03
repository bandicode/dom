// Copyright (C) 2019 Vincent Chambrin
// This file is part of the 'dom' project
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef DOM_DOCUMENT_H
#define DOM_DOCUMENT_H

#include "dom/element.h"

#include <memory>
#include <vector>

namespace dom
{

class DOM_API Document : public Element
{
public:
  ~Document() = default;

  static const std::string Type;
  const std::string& type() const override;

  explicit Document(std::string title = "");

  const std::string& title() const;
  const std::string& author() const;
  const std::string& date() const;
  int revision() const;
  const std::vector<std::shared_ptr<Node>>& nodes() const;

  void setTitle(std::string str);
  void setAuthor(std::string str);
  void setDate(std::string str);
  void setRevision(int rev);

  void addNode(std::shared_ptr<Node> n);
  void insertNode(size_t index, std::shared_ptr<Node> n);
  void removeNode(const std::shared_ptr<Node>& n);
  void removeAt(size_t index);

  void swap(size_t i, size_t j);

private:
  std::string m_title;
  std::string m_author;
  std::string m_date;
  int m_revision = -1;
  std::vector<std::shared_ptr<Node>> m_nodes;
};

} // namespace dom

namespace dom
{

Document::Document(std::string title)
  : m_title(std::move(title))
{

}

inline const std::string& Document::title() const
{
  return m_title;
}

inline const std::string& Document::author() const
{
  return m_author;
}

inline const std::string& Document::date() const
{
  return m_date;
}

inline int Document::revision() const
{
  return m_revision;
}

inline const std::vector<std::shared_ptr<Node>>& Document::nodes() const
{
  return m_nodes;
}

inline void Document::setTitle(std::string str)
{
  m_title = std::move(str);
}

inline void Document::setAuthor(std::string str)
{
  m_author = std::move(str);
}

inline void Document::setDate(std::string str)
{
  m_date = std::move(str);
}

inline void Document::setRevision(int rev)
{
  m_revision = rev;
}

} // namespace dom

#endif // DOM_DOCUMENT_H
