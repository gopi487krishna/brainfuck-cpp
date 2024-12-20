#include "brainfuck.hpp"
#include <cassert>
std::uint64_t BrainFuckInterpreter::handleOpenBracket(std::uint64_t curr_pc) {
  bool jmp_loc_available = true;

  if (!jump_loc_map.count(curr_pc)) {
    jmp_loc_available = false;
    open_brace_indexes_.push(curr_pc);
  }

  if (data_arr_[d_index_] == 0) {
    if (jmp_loc_available)
      return jump_loc_map[curr_pc] + 1;
    else
      ignore_mode = true;
  }

  return curr_pc + 1;
}

void BrainFuckInterpreter::create_jump_location(std::uint64_t jump_index,
                                                std::uint64_t curr_pc) {
  assert(jump_loc_map.count(jump_index) == 0 && "Program Error : Jump location already exist");
  assert(jump_loc_map.count(curr_pc) == 0 && "Program Error : Jump location already exist");
  jump_loc_map[jump_index] = curr_pc;
  jump_loc_map[curr_pc] = jump_index;
}

std::uint64_t BrainFuckInterpreter::handleCloseBracket(std::uint64_t curr_pc) {

  if (!jump_loc_map.count(curr_pc)) {
    assert(open_brace_indexes_.size() && "Program Error : Matching LOOP_BEG not found");
    auto jump_index = open_brace_indexes_.top();
    open_brace_indexes_.pop();
    create_jump_location(jump_index, curr_pc);
  }

  return data_arr_[d_index_] != 0 ? jump_loc_map[curr_pc] + 1 : curr_pc + 1;
}

std::uint64_t BrainFuckInterpreter::handleIgnoreMode(std::uint64_t curr_pc,
                                                     const char token) {
  switch (token) {
  case LOOP_BEG:
    open_brace_indexes_.push(curr_pc);
    break;
  case LOOP_END:
    assert(open_brace_indexes_.size() && "Program Error : Matching LOOP_BEG not found");
    auto jump_index = open_brace_indexes_.top();
    open_brace_indexes_.pop();
    create_jump_location(jump_index, curr_pc);
    if (open_brace_indexes_.empty()) {
      ignore_mode = false; /* Closing brace found */
    }
    break;
  }
  return curr_pc + 1;
}

void BrainFuckInterpreter::expandDataArr() { data_arr_.resize(d_index_ * 2, 0); }

bool BrainFuckInterpreter::execute() {
  for (auto pc = 0; pc < program_.size();) {
    auto curr_pc = pc;
    pc++;
    auto token = program_[curr_pc];
    if (ignore_mode) {
      pc = handleIgnoreMode(curr_pc, token);
      continue;
    }
    switch (token) {
    case BYTE_INC:
      data_arr_[d_index_]++;
      break;
    case BYTE_DEC:
      data_arr_[d_index_]--;
      break;
    case DATAPTR_INC:
      d_index_++;
      if (d_index_ >= data_arr_.size())
        expandDataArr();
      break;
    case DATAPTR_DEC:
      d_index_--;
      break;
    case OUTPUT:
      ostream_.put(data_arr_[d_index_]);
      break;
    case INPUT:
      data_arr_[d_index_] = istream_.get();
      break;
    case LOOP_BEG:
      pc = handleOpenBracket(curr_pc);
      break;
    case LOOP_END:
      pc = handleCloseBracket(curr_pc);
      break;
    }
  }
  assert(open_brace_indexes_.empty() && "Program Error : Loop end not found");
  return true;
}
