#ifndef OPERATIONS_H
#define OPERATIONS_H


#include<string>
#include<iostream>
#include<algorithm>
class ElementTree;

class Element {
public:
  virtual ~Element() {}
  virtual  bool appendLeft(const ElementTree& other) { return false; }
  virtual  bool appendRight(const ElementTree& other) { return false; }
  virtual void parse(std::ostream& stream) const {};
};
enum class type { add, sub, mult, div };
class ElementTree {
  friend class Operator;
private:
  Element* root;
public:
  ElementTree(Element* root_) : root{ root_ } {}
  bool appendLeft(const ElementTree& other) {
    return root->appendLeft(other);
  }
  bool appendRight(const ElementTree& other) {
    return root->appendRight(other);
  }

  void parse(std::ostream& stream) { // in-order traversal
    root->parse(stream);
  }
};

class Variable : public Element {
public:
  std::string name;

  Variable(const std::string& name_) : name{ name_ } {}
  void parse(std::ostream& stream) const {
    stream << name;
  }
};

class Constant : public Element {
public:
  const double value;

  Constant(const double value_) : value{ value_ } {}
  void parse(std::ostream& stream) const {
    stream << value;
  }
};

class Operator : public Element {
public:
  const type op;
  const Element* lhs;
  const Element* rhs;

  Operator(const type op_, const Element* lhs_, const Element* rhs_) : op{ op_ }, lhs{ lhs_ }, rhs{ rhs_ } {}
  bool appendLeft(const ElementTree& other) {
    lhs = other.root;
    return true;
  }
  bool appendRight(const ElementTree& other) {
    rhs = other.root;
    return true;
  }

  void parse(std::ostream& stream) const {
    lhs->parse(stream);
    switch (op) {
    case type::add:
      stream << '+';
      break;
    case type::div:
      stream << '/';
      break;
    case type::mult:
      stream << '*';
      break;
    case type::sub:
      stream << '-';
      break;
    }
    rhs->parse(stream);
    stream << '\n';
  }
};

class EquationFormer {
private:
  std::string equationTxt;
  ElementTree formFrom(size_t pos) {
    size_t symPos = equationTxt.find("*/", pos); // M and D of same importance
    if (equationTxt[symPos] == '*') {

    }
    else if (equationTxt[symPos] == '/') {

    }
  }
public:
  EquationFormer(const std::string& in) : equationTxt{ in } {}
  ElementTree form() {

  }
};

#endif //OPERATIONS_H