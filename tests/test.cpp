// Copyright (C) 2019 Vincent Chambrin
// This file is part of the dom project
// For conditions of distribution and use, see copyright notice in LICENSE

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "dom/paragraph.h"
#include "dom/paragraph/iterator.h"
#include "dom/paragraph/textstyle.h"

TEST_CASE("Paragraph iterators (simple)", "[paragraph-iterator]") 
{
  auto par = std::make_shared<dom::Paragraph>("Hello there!");

  REQUIRE(par->text() == "Hello there!");

  par->add<dom::TextStyle>(par->range(0, 5), "bold");
  par->add<dom::TextStyle>(par->range(6, 11), "italic");

  auto it = par->begin();

  REQUIRE(*it != nullptr);
  REQUIRE(it.range() == par->range(0, 5));
  REQUIRE((*it)->is<dom::TextStyle>());

  ++it;

  REQUIRE(*it == nullptr);
  REQUIRE(it.range() == par->range(5, 6));

  ++it;

  REQUIRE(it.range() == par->range(6, 11));
  REQUIRE((*it)->is<dom::TextStyle>());

  ++it;

  REQUIRE(it.range() == par->range(11, 12));
  REQUIRE(*it == nullptr);

  ++it;

  REQUIRE(it == par->end());
}

TEST_CASE("Paragraph iterators (nested)", "[paragraph-iterator]")
{
  auto par = std::make_shared<dom::Paragraph>("I am the test case!");

  par->add<dom::TextStyle>(par->range(1, 4), "1");
  par->add<dom::TextStyle>(par->range(1, 2), "2");
  par->add<dom::TextStyle>(par->range(2, 4), "3");

  auto it = par->begin();

  REQUIRE(it.isText());
  REQUIRE(it.range() == par->range(0, 1));

  ++it;

  REQUIRE(it.hasChild());
  REQUIRE(it.range() == par->range(1, 4));

  {
    auto child_it = it.begin();

    REQUIRE(!child_it.isText());
    REQUIRE(child_it.range() == par->range(1, 2));

    ++child_it;

    REQUIRE(!child_it.isText());
    REQUIRE(child_it.range() == par->range(2, 4));

    ++child_it;

    REQUIRE(child_it == it.end());
  }

  ++it;

  REQUIRE(it.range() == par->range(4, 19));

  ++it;

  REQUIRE(it == par->end());
}

TEST_CASE("Read / Write attributes", "[attributes]")
{
  auto elem = std::make_shared<dom::Paragraph>("I am the test case!");

  elem->setAttribute("id", std::string("foo"));

  auto attrs = elem->attributes();
  REQUIRE(attrs.size() == 1);
  REQUIRE(attrs.at(0).get<std::string>() == "foo");

  elem->id = "bar";
  REQUIRE(elem->getAttribute<std::string>("id") == "bar");
}
