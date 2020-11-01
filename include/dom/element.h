// Copyright (C) 2019 Vincent Chambrin
// This file is part of the 'dom' project
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef DOM_ELEMENT_H
#define DOM_ELEMENT_H

#include "dom/node.h"

#include <map>

namespace dom
{

enum class AttributeType
{
  None,
  Bool,
  Int,
  Double,
  String,
};

class DOM_API MetaProperty
{
public: 
  std::string name;

public:
  explicit MetaProperty(std::string name);
  virtual ~MetaProperty();

  virtual AttributeType type() const = 0;

  virtual bool readBool(const Node& n) const = 0;
  virtual int readInt(const Node& n) const = 0;
  virtual double readDouble(const Node& n) const = 0;
  virtual std::string readString(const Node& n) const = 0;

  static bool read_bool(bool val);
  static bool read_bool(int val);
  static bool read_bool(double val);
  static bool read_bool(const std::string& val);

  static int read_int(bool val);
  static int read_int(int val);
  static int read_int(double val);
  static int read_int(const std::string& val);

  static double read_double(bool val);
  static double read_double(int val);
  static double read_double(double val);
  static double read_double(const std::string& val);

  static std::string read_string(bool val);
  static std::string read_string(int val);
  static std::string read_string(double val);
  static std::string read_string(const std::string& val);

  virtual void set(Node& n, bool val) = 0;
  virtual void set(Node& n, int val) = 0;
  virtual void set(Node& n, double val) = 0;
  virtual void set(Node& n, std::string val) = 0;

  static void set_property(bool& p, bool val);
  static void set_property(bool& p, const std::string& val);

  static void set_property(int& p, int val);
  static void set_property(int& p, const std::string& val);

  static void set_property(double& p, double val);
  static void set_property(double& p, const std::string& val);

  static void set_property(std::string& p, bool val);
  static void set_property(std::string& p, int val);
  static void set_property(std::string& p, double val);
  static void set_property(std::string& p, std::string val);

  template<typename T>
  struct Selector
  {

  };

  bool read(const Node& n, Selector<bool>) const;
  int read(const Node& n, Selector<int>) const;
  double read(const Node& n, Selector<double>) const;
  std::string read(const Node& n, Selector<std::string>) const;
};

class DOM_API MetaObject
{
public:
  MetaObject* base;
  std::vector<MetaProperty*> properties;

public:
  explicit MetaObject(MetaObject* b = nullptr);
  virtual ~MetaObject();

  MetaProperty* at(size_t index) const;
  MetaProperty* find(const std::string& name) const;

  size_t size() const;
};

template<typename C, typename T>
struct GenericMetaProperty : public MetaProperty
{
  T C::* pointer = nullptr;

  GenericMetaProperty(std::string n, T C::* ptr)
    : MetaProperty(std::move(n)),
      pointer(ptr)
  {

  }

  AttributeType type() const override
  {
    if (std::is_same<T, bool>::value)
      return AttributeType::Bool;
    else if (std::is_same<T, int>::value)
      return AttributeType::Int;
    else if (std::is_same<T, double>::value)
      return AttributeType::Double;
    else if (std::is_same<T, std::string>::value)
      return AttributeType::String;
    else
      return AttributeType::None;
  }

  bool readBool(const Node& n) const override
  {
    return read_bool((static_cast<const C&>(n)).*pointer);
  }

  int readInt(const Node& n) const override
  {
    return read_int((static_cast<const C&>(n)).*pointer);
  }

  double readDouble(const Node& n) const override
  {
    return read_double((static_cast<const C&>(n)).*pointer);
  }

  std::string readString(const Node& n) const override
  {
    return read_string((static_cast<const C&>(n)).*pointer);
  }

  void set(Node& n, bool val) override
  {
    set_property((static_cast<C&>(n)).*pointer, val);
  }

  void set(Node& n, int val) override
  {
    set_property((static_cast<C&>(n)).*pointer, val);
  }

  void set(Node& n, double val) override
  {
    set_property((static_cast<C&>(n)).*pointer, val);
  }

  void set(Node& n, std::string val) override
  {
    set_property((static_cast<C&>(n)).*pointer, val);
  }
};

inline void fill_property_vec_impl(std::vector<MetaProperty*>&)
{

}

template<typename T, typename... Args>
void fill_property_vec_impl(std::vector<MetaProperty*>& list, T& prop, Args&... rest)
{
  list.push_back(&prop);
  fill_property_vec_impl(list, rest...);
}

template<typename Tuple, std::size_t... Is>
void fill_property_vec_impl_index_seq(std::vector<MetaProperty*>& list, Tuple& t, std::index_sequence<Is...>)
{
  fill_property_vec_impl(list, std::get<Is>(t)...);
}

template<typename... Args>
void fill_property_vec(std::vector<MetaProperty*>& list, std::tuple<Args...>& t)
{
  fill_property_vec_impl_index_seq(list, t, std::index_sequence_for<Args...>{});
}

template<typename T, typename... Args>
class GenericMetaObject : public MetaObject
{
public:
  std::tuple<GenericMetaProperty<T, Args>...> property_tuple;

  GenericMetaObject(std::tuple<GenericMetaProperty<T, Args>...> props, MetaObject* p = nullptr)
    : MetaObject(p),
      property_tuple(props)
  {
    fill_property_vec(properties, property_tuple);
  }
};

class AttributeList;

class DOM_API Element : public Node
{
public:
  std::string id;

public:
  using Node::Node;

  bool isElement() const override;

  AttributeList attributes() const;

  template<typename T>
  T getAttribute(const std::string& name) const
  {
    MetaProperty* prop = metaObject()->find(name);
    
    if (prop)
      return prop->read(*this, MetaProperty::Selector<T>());
    return T();
  }

  // C++17
  // std::variant<bool, int, double, std::string> getAttribute(const std::string& name);

  void setAttribute(const std::string& name, bool value);
  void setAttribute(const std::string& name, int value);
  void setAttribute(const std::string& name, double value);
  void setAttribute(const std::string& name, std::string value);

protected:
  friend class AttributeList;
  static GenericMetaObject<Element, std::string> staticMetaObject;
  virtual MetaObject* metaObject() const;
};

class DOM_API Attribute
{
public:
  explicit Attribute(const Element& e, MetaProperty* prop)
    : element(e),
      property(prop)
  {

  }

  AttributeType type() const
  {
    if (!property)
      return AttributeType::None;

    return property->type();
  }

  std::string name() const
  {
    if (property)
      return property->name;
    else
      return std::string();
  }

  template<typename T>
  T get() const
  {
    if (property)
      return property->read(element, MetaProperty::Selector<T>());
    else
      return T();
  }

private:
  const Element& element;
  MetaProperty* property;
};

class DOM_API AttributeList
{
public:
  explicit AttributeList(const Element& e, MetaObject* mo)
    : element(e),
      metaobject(mo)
  {

  }

  Attribute at(size_t index) const
  {
    MetaProperty* prop = element.metaObject()->at(index);
    return Attribute(element, prop);
  }

  size_t size() const
  {
    return metaobject->size();
  }

private:
  const Element& element;
  MetaObject* metaobject;
};

} // namespace dom

#endif // DOM_ELEMENT_H
