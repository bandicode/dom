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

class DOM_API Document : public Node
{
public:
  std::string title;
  std::string doctype = "document";

public:
  ~Document() = default;

  static const std::string Type;
  const std::string& type() const override;

  explicit Document(std::string title = "");

  const std::vector<std::shared_ptr<Node>>& nodes() const;

  void addNode(std::shared_ptr<Node> n);
  void insertNode(size_t index, std::shared_ptr<Node> n);
  void removeNode(const std::shared_ptr<Node>& n);
  void removeAt(size_t index);

  const NodeList& childNodes() const override;
  void appendChild(std::shared_ptr<Node> n) override;
  void removeChild(std::shared_ptr<Node> n) override;

  void swap(size_t i, size_t j);

  std::shared_ptr<Element> getElementById(const std::string& id) const;

private:
  std::vector<std::shared_ptr<Node>> m_nodes;
};

} // namespace dom

namespace dom
{

inline Document::Document(std::string tt)
  : title(std::move(tt))
{

}

inline const std::vector<std::shared_ptr<Node>>& Document::nodes() const
{
  return m_nodes;
}

} // namespace dom

#endif // DOM_DOCUMENT_H
