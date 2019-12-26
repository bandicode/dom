// Copyright (C) 2019 Vincent Chambrin
// This file is part of the dom project
// For conditions of distribution and use, see copyright notice in LICENSE

#include "dom/paragraph.h"
#include "dom/paragraph/iterator.h"
#include "dom/paragraph/textstyle.h"

#include <iostream>
#include <sstream>

void output(const dom::ParagraphIterator begin, const dom::ParagraphIterator end, std::stringstream& stream)
{
  for (auto it = begin; it != end; ++it)
  {
    if (it.isText())
    {
      stream << it.range().text();
    }
    else
    {
      const std::string& style = std::static_pointer_cast<dom::TextStyle>(*it)->style();
      stream << "<" << style << ">";

      if (it.hasChild())
      {
        output(it.begin(), it.end(), stream);
      }
      else
      {
        stream << it.range().text();
      }

      stream << "</" << style << ">";
    }
  }
}

void output(const dom::Paragraph& par, std::stringstream& stream)
{
  stream << "<p>";
  output(par.begin(), par.end(), stream);
  stream << "</p>";
}

int main()
{
  auto par = std::make_shared<dom::Paragraph>("This is a paragraph with bold text, italic text and a mix of both.");

  par->add<dom::TextStyle>(par->range(25, 34), "b");
  par->add<dom::TextStyle>(par->range(36, 47), "i");
  par->add<dom::TextStyle>(par->range(52, 65), "i");
  par->add<dom::TextStyle>(par->range(61, 65), "b");

  std::stringstream result;

  output(*par, result);

  std::cout << result.str() << std::endl;
}
