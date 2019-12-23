// Copyright (C) 2019 Vincent Chambrin
// This file is part of the 'dom' project
// For conditions of distribution and use, see copyright notice in LICENSE

#include "dom/paragraph/note.h"

namespace dom
{

const std::string Note::TypeId = "note";

const std::string& Note::type() const
{
  return TypeId;
}

} // namespace dom
