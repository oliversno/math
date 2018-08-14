#ifndef OPERATIONS_H
#define OPERATIONS_H


#include<string>
#include<iostream>
#include<algorithm>
class ElementTree;

class Element {
public:
  virtual void parse(std::ostream& stream) const {};
};
enum class type { add, sub, mult, div };
class ElementTree {
private:
  Element* root = nullptr;
  ElementTree* lhs = nullptr;
  ElementTree* rhs = nullptr;
public:
  ElementTree(Element* root_) : root{ root_ } {}
  ~ElementTree() {
    delete(lhs);
    delete(rhs);
    lhs = nullptr;
    rhs = nullptr;
    delete root;
  }
  bool appendLeft(ElementTree* other) {
    return lhs = other;
  }
  bool appendRight(ElementTree* other) {
    return rhs = other;
  }

  void parse(std::ostream& stream) { // in-order traversal
    if (!lhs || !rhs) { // If leaf node only interpret then move back up the recursion ladder
      root->parse(stream);
    }
    else {
      lhs->parse(stream);
      root->parse(stream);
      rhs->parse(stream);
      stream << '\n';
    }
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

  Operator(const type op_) : op{ op_ } {}

  void parse(std::ostream& stream) const {
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