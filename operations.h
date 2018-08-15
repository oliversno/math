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

  void recursiveParse(std::ostream& stream) { // in-order traversal
    if (!lhs || !rhs) { // If leaf node only interpret then move back up the recursion ladder
      root->parse(stream);
    }
    else {
      lhs->recursiveParse(stream);
      root->parse(stream);
      rhs->recursiveParse(stream);
    }
  }
public:
  ElementTree(Element* root_) : root{ root_ } {}
  ~ElementTree() {
    if(!lhs)
      delete(lhs);
    if (!rhs)
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
    recursiveParse(stream);
    stream << '\n';
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
  const std::string MD = "*/";
  const std::string AS = "+-";
  template<typename T>
  ElementTree* formFrom(T startIt, T endIt) {
    ElementTree* treePtr = nullptr;
    T symPos = find_first_of(startIt, endIt, MD.begin(), MD.end()); // M and D of same importance
    if (*symPos == '*') {
      treePtr = new ElementTree{ new Operator{type::mult} };
      treePtr->appendLeft(formFrom(startIt, symPos));
      treePtr->appendRight(formFrom(++symPos, endIt));
    }
    else if (*symPos == '/') {
      treePtr = new ElementTree{ new Operator{ type::div } };
      treePtr->appendLeft(formFrom(startIt, symPos));
      treePtr->appendRight(formFrom(++symPos, endIt));
    }
    else {
      T symPos = find_first_of(startIt, endIt, AS.begin(), AS.end()); // A and S of same importance
      if (*symPos == '+') {
        treePtr = new ElementTree{ new Operator{ type::add } };
        treePtr->appendLeft(formFrom(startIt, symPos));
        treePtr->appendRight(formFrom(++symPos, endIt));
      }
      else if (*symPos == '-') {
        treePtr = new ElementTree{ new Operator{ type::sub } };
        treePtr->appendLeft(formFrom(startIt, symPos));
        treePtr->appendRight(formFrom(++symPos, endIt));
      }
    }
    return treePtr;
  }
public:
  EquationFormer(const std::string& in) : equationTxt{ in } {}
  ElementTree form() {
    return *formFrom(equationTxt.begin(), equationTxt.end());
  }
};

#endif //OPERATIONS_H