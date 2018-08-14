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

void runAllTests() {
  testSingleMult();
  testSingleDiv();
  testSingleAdd();
  testSingleSub();
}