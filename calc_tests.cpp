#include<sstream>
#include<cassert>
#include "operations.h"

void runAllTests();

int main() {
  runAllTests();
  return 0;
}

void testSingleMult() {
  // 3*5
  ElementTree tree{ new Operator{type::mult} };
  tree.appendLeft( new ElementTree{ new Constant{ 3 } } );
  tree.appendRight( new ElementTree{ new Constant{ 5 } } );
  std::ostringstream os;
  tree.parse(os);
  std::ostringstream correct;
  correct << "3*5\n";
  assert(os.str() == correct.str());
}
void testSingleDiv() {
  // 3/5
  ElementTree tree{ new Operator{ type::div } };
  tree.appendLeft(new ElementTree{ new Constant{ 3 } });
  tree.appendRight(new ElementTree{ new Constant{ 5 } });
  std::ostringstream os;
  tree.parse(os);
  std::ostringstream correct;
  correct << "3/5\n";
  assert(os.str() == correct.str());
}
void testSingleAdd() {
  // 3+5
  ElementTree tree{ new Operator{ type::add } };
  tree.appendLeft(new ElementTree{ new Constant{ 3 } });
  tree.appendRight(new ElementTree{ new Constant{ 5 } });
  std::ostringstream os;
  tree.parse(os);
  std::ostringstream correct;
  correct << "3+5\n";
  assert(os.str() == correct.str());
}
void testSingleSub() {
  // 3-5
  ElementTree tree{ new Operator{ type::sub } };
  tree.appendLeft(new ElementTree{ new Constant{ 3 } });
  tree.appendRight(new ElementTree{ new Constant{ 5 } });
  std::ostringstream os;
  tree.parse(os);
  std::ostringstream correct;
  correct << "3-5\n";
  assert(os.str() == correct.str());
}
void testComplex() {
  // 3-5*4+2.2
  ElementTree mult{ new Operator{ type::mult } };
  mult.appendLeft(new ElementTree{ new Constant{ 5 } });
  mult.appendRight(new ElementTree{ new Constant{ 4 } });
  ElementTree add{ new Operator{ type::add } };
  add.appendLeft(&mult);
  add.appendRight(new ElementTree{ new Constant{ 2.2 } });
  ElementTree sub{ new Operator{ type::sub } };
  sub.appendLeft( new ElementTree{ new Constant{ 3 } });
  sub.appendRight(&add);
  std::ostringstream os;
  sub.parse(os);
  std::ostringstream correct;
  correct << "3-5*4+2.2\n";
  assert(os.str() == correct.str());
}

void runAllTests() {
  testSingleMult();
  testSingleDiv();
  testSingleAdd();
  testSingleSub();
  testComplex();
}