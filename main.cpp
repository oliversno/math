#include<string>
#include<iostream>
class ElementTree;

class Element {
public:
  virtual ~Element() {}
 virtual  bool appendLeft(const ElementTree& other) { return false; }
 virtual  bool appendRight(const ElementTree& other) { return false; }
  virtual void parse() const {};
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

  void parse() { // in-order traversal
    root->parse();
  }
};

class Variable : public Element {
public:
  std::string name;

  Variable(const std::string& name_) : name{ name_ } {}
  void parse() const {
    std::cout << name;
  }
};

class Constant : public Element {
public:
  const double value;

  Constant(const double value_) : value{ value_ } {}
  void parse() const{
    std::cout << value;
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

  void parse() const{
    lhs->parse();
    switch (op) {
    case type::add:
      std::cout << '+';
      break;
    case type::div:
      std::cout << '/';
      break;
    case type::mult:
      std::cout << '*';
      break;
    case type::sub:
      std::cout << '-';
      break;
    }
    rhs->parse();
    std::cout << '\n';
  }
};


int main() {
  // 3 * x
  Operator one{ type::mult, new Constant{ 3 }, new Variable{ "x" } } ;
  ElementTree eq2{ new Operator{ type::sub, new Constant{ 20.5 }, &one } };
  eq2.parse();
}