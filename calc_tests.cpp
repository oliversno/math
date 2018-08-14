#include<sstream>
#include<cassert>
#include "operations.h"

void runAllTests();

int main() {
  runAllTests();
  return 0;
}

void testSingleMult() {
  Operator times{ type::mult, new Constant{3}, new Constant{5} }; // 3*5
  ElementTree tree{ &times };
  std::ostringstream os;
  tree.parse(os);
  std::ostringstream correct;
  correct << "3*5\n";
  assert(os.str() == correct.str());
}
void testSingleDiv() {
  Operator divide{ type::div, new Constant{ 3 }, new Constant{ 5 } }; // 3/5
  ElementTree tree{ &divide };
  std::ostringstream os;
  tree.parse(os);
  std::ostringstream correct;
  correct << "3/5\n";
  assert(os.str() == correct.str());
}
void testSingleAdd() {
  Operator plus{ type::add, new Constant{ 3 }, new Constant{ 5 } }; // 3+5
  ElementTree tree{ &plus };
  std::ostringstream os;
  tree.parse(os);
  std::ostringstream correct;
  correct << "3+5\n";
  assert(os.str() == correct.str());
}
void testSingleSub() {
  Operator minus{ type::sub, new Constant{ 3 }, new Constant{ 5 } }; // 3-5
  ElementTree tree{ &minus };
  std::ostringstream os;
  tree.parse(os);
  std::ostringstream correct;
  correct << "3-5\n";
  assert(os.str() == correct.str());
}

void runAllTests() {
  testSingleMult();
  testSingleDiv();
  testSingleAdd();
  testSingleSub();
}