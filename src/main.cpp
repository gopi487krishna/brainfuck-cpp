#include "brainfuck.hpp"
#include <cassert>
#include <cstdio>
#include <sstream>

void runTests();

int main() { runTests(); }

void test1() {
  const std::string program = "++++";
  BrainFuckInterpreter brainfuck_interpreter(program);
  brainfuck_interpreter.execute();
  assert(brainfuck_interpreter.getByteAt(0) == 4 && "Result not 4");
}

void test2() {
  std::istringstream input_stream;
  std::ostringstream output_stream;
  const std::string program =
      "++++++++[>+>++>+++>++++>+++++>++++++>+++++++>++++++++>+++++++++>++++++++"
      "++>+++++++++++>++++++++++++>+++++++++++++>++++++++++++++>+++++++++++++++"
      ">++++++++++++++++<<<<<<<<<<<<<<<<-]>>>>>>>>>>>>>.";
  BrainFuckInterpreter brainfuck_interpreter(program, output_stream,
                                             input_stream);

  brainfuck_interpreter.execute();
  assert(output_stream.str() == "h");
}

void test3() {
  const std::string input(1, 5);
  std::istringstream input_stream(input);
  std::ostringstream output_stream;
  // Program to echo back the byte
  // const std::string program = "+++++[>+<-].";
  const std::string program = ",[>+<-]>.";
  BrainFuckInterpreter brainfuck_interpreter(program, output_stream,
                                             input_stream);
  brainfuck_interpreter.execute();
  assert(output_stream.str()[0] == (char)5);
}

void test4() {
  const std::string input(1, 5);
  std::istringstream input_stream(input);
  std::ostringstream output_stream;
  // Program to echo back the byte
  const std::string program = "[+++++].";
  BrainFuckInterpreter brainfuck_interpreter(program, output_stream,
                                             input_stream);
  brainfuck_interpreter.execute();
  assert(output_stream.str()[0] == (char)0);
}

void test5() {
  const std::string input(1, 5);
  std::istringstream input_stream(input);
  std::ostringstream output_stream;
  // Program to echo back the byte
  const std::string program = ",>[<+++++].";
  BrainFuckInterpreter brainfuck_interpreter(program, output_stream,
                                             input_stream);
  brainfuck_interpreter.execute();
  assert(output_stream.str()[0] == (char)0);
}
void runTests() {
  test1();
  test2();
  test3();
  test4();
  test5();
  std::cout << "All Tests successful \n";
}
