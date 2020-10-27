// Copyright (C) 2020 Vincent Chambrin
// This file is part of the 'dom' project
// For conditions of distribution and use, see copyright notice in LICENSE

#include "dom/element.h"

#include <stdexcept>

namespace dom
{

GenericMetaObject<Element, std::string> Element::staticMetaObject = {
  {{"id", &Element::id}}, nullptr
};

MetaProperty::MetaProperty(std::string n)
  : name(std::move(n))
{

}

MetaProperty::~MetaProperty()
{

}

bool MetaProperty::read_bool(bool val)
{
  return val;
}

bool MetaProperty::read_bool(int val)
{
  throw std::runtime_error{ "dom get attribute error" };
}

bool MetaProperty::read_bool(double val)
{
  throw std::runtime_error{ "dom get attribute error" };
}

bool MetaProperty::read_bool(const std::string& val)
{
  throw std::runtime_error{ "dom get attribute error" };
}


int MetaProperty::read_int(bool val)
{
  throw std::runtime_error{ "dom get attribute error" };
}

int MetaProperty::read_int(int val)
{
  return val;
}

int MetaProperty::read_int(double val)
{
  throw std::runtime_error{ "dom get attribute error" };
}

int MetaProperty::read_int(const std::string& val)
{
  throw std::runtime_error{ "dom get attribute error" };
}


double MetaProperty::read_double(bool val)
{
  throw std::runtime_error{ "dom get attribute error" };
}

double MetaProperty::read_double(int val)
{
  throw std::runtime_error{ "dom get attribute error" };
}

double MetaProperty::read_double(double val)
{
  return val;
}

double MetaProperty::read_double(const std::string& val)
{
  throw std::runtime_error{ "dom get attribute error" };
}


std::string MetaProperty::read_string(bool val)
{
  throw std::runtime_error{ "dom get attribute error" };
}

std::string MetaProperty::read_string(int val)
{
  throw std::runtime_error{ "dom get attribute error" };
}

std::string MetaProperty::read_string(double val)
{
  throw std::runtime_error{ "dom get attribute error" };
}

std::string MetaProperty::read_string(const std::string& val)
{
  return val;
}


void MetaProperty::set_property(bool& p, bool val)
{
  p = val;
}

void MetaProperty::set_property(bool& p, const std::string& val)
{
  p = (val == "true" || val == "True" || val == "TRUE");
}

void MetaProperty::set_property(int& p, int val)
{
  p = val;
}

void MetaProperty::set_property(int& p, const std::string& val)
{
  p = std::stoi(val);
}

void MetaProperty::set_property(double& p, double val)
{
  p = val;
}

void MetaProperty::set_property(double& p, const std::string& val)
{
  p = std::stod(val);
}

void MetaProperty::set_property(std::string& p, bool val)
{
  p = val ? "true" : "false";
}

void MetaProperty::set_property(std::string& p, int val)
{
  p = std::to_string(val);
}

void MetaProperty::set_property(std::string& p, double val)
{
  p = std::to_string(val);
}

void MetaProperty::set_property(std::string& p, std::string val)
{
  p = val;
}

bool MetaProperty::read(const Node& n, Selector<bool>) const
{
  return readBool(n);
}

int MetaProperty::read(const Node& n, Selector<int>) const 
{
  return readInt(n);
}

double MetaProperty::read(const Node& n, Selector<double>) const 
{
  return readDouble(n);
}

std::string MetaProperty::read(const Node& n, Selector<std::string>) const
{
  return readString(n);
}

MetaObject::MetaObject(MetaObject* b)
  : base(b)
{

}

MetaObject::~MetaObject()
{

}

MetaProperty* MetaObject::at(size_t index) const
{
  if (base)
  {
    size_t s = base->size();

    if (index < s)
      return base->at(index);
    else
      index -= s;
  }

  if (index < properties.size())
    return properties.at(index);
  else
    return nullptr;
}

MetaProperty* MetaObject::find(const std::string& name) const
{
  if (base)
  {
    auto result = base->find(name);

    if (result)
      return result;
  }

  for (MetaProperty* p : properties)
  {
    if (p->name == name)
      return p;
  }

  return nullptr;
}

size_t MetaObject::size() const
{
  if (base)
    return base->size() + properties.size();
  else
    return properties.size();
}

bool Element::isElement() const
{
  return true;
}

AttributeList Element::attributes() const
{
  return AttributeList(*this, metaObject());
}

void Element::setAttribute(const std::string& name, bool value)
{
  MetaProperty* p = metaObject()->find(name);

  if (p)
  {
    p->set(*this, value);
  }
}

void Element::setAttribute(const std::string& name, int value)
{
  MetaProperty* p = metaObject()->find(name);

  if (p)
  {
    p->set(*this, value);
  }
}

void Element::setAttribute(const std::string& name, double value)
{
  MetaProperty* p = metaObject()->find(name);

  if (p)
  {
    p->set(*this, value);
  }
}

void Element::setAttribute(const std::string& name, std::string value)
{
  MetaProperty* p = metaObject()->find(name);

  if (p)
  {
    p->set(*this, value);
  }
}

MetaObject* Element::metaObject() const
{
  return &staticMetaObject;
}

} // namespace dom
