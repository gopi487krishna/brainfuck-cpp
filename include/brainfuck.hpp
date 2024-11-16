#pragma once

#include <cstdint>
#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

enum TOKENS {
  BYTE_INC = '+',
  BYTE_DEC = '-',
  DATAPTR_INC = '>',
  DATAPTR_DEC = '<',
  INPUT = ',',
  OUTPUT = '.',
  LOOP_BEG = '[',
  LOOP_END = ']'
};

class BrainFuckInterpreter {
public:
  BrainFuckInterpreter(const std::string &program, std::ostream &os = std::cout,
                       std::istream &is = std::cin)
      : program_(program), data_arr_(TAPE_SIZE, 0), ostream_(os), istream_(is) {
  }
  bool execute();
  std::int8_t getByteAt(std::uint64_t index) { return data_arr_[index]; }

private:
  const std::uint32_t TAPE_SIZE = 1024;
  const std::string program_;
  std::vector<std::int8_t> data_arr_;
  std::unordered_map<std::uint64_t, std::uint64_t> jump_loc_map;
  std::uint64_t d_index_ = 0;
  std::ostream &ostream_;
  std::istream &istream_;
  void compile();
  std::uint64_t handleOpenBracket(std::uint64_t curr_pc);
  std::uint64_t handleCloseBracket(std::uint64_t curr_pc);
  std::uint64_t handleIgnoreMode(std::uint64_t curr_pc, const char token);
  void create_jump_location(std::uint64_t jump_index, std::uint64_t curr_pc);
  std::stack<std::uint64_t> open_brace_indexes_;
  bool ignore_mode = false;
};
