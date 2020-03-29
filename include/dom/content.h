// Copyright (C) 2020 Vincent Chambrin
// This file is part of the 'dom' project
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef DOM_CONTENT_H
#define DOM_CONTENT_H

#include "dom/node.h"

#include <memory>
#include <vector>

namespace dom
{

using Content = std::vector<std::shared_ptr<Node>>;

} // namespace dom

#endif // DOM_CONTENT_H
