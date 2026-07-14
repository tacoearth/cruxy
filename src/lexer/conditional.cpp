module conditional;

import expression;
import std;
import token;
import syntax;
import statement;
using namespace std;

taking_statement::taking_statement(string iterator_name, type iterator_type,
                                   subexpression &initial_value,
                                   subexpression &final_value,
                                   subexpression &step_size,
                                   unique_ptr<statement_block> &&body_block,
                                   statement statement_parameters)
    : statement(statement_parameters), iterator_name(iterator_name),
      iterator_type(iterator_type), initial_value(initial_value),
      final_value(final_value), step_size(step_size),
      body(std::move(body_block)) {

  if (iterator_type == type::INT) {
    throw runtime_error("Initialized variable must be an integer at line " +
                        to_string(line_number) + "\nStop.");
  }
  type initial_value_type = initial_value.get_type();
  if (initial_value_type != type::INT) {
    throw runtime_error(
        "Initial value is not the same type same final value at line " +
        to_string(line_number) + "\nStop.");
  }
  type final_value_type = final_value.get_type();
  if (final_value_type != type::INT) {
    throw runtime_error(
        "Final value is not the same type same final value at line " +
        to_string(line_number) + "\nStop.");
  }
  type step_size_type = step_size.get_type();
  if (step_size_type != type::INT) {
    throw runtime_error(
        "Step size is not the same type same final value at line " +
        to_string(line_number) + "\nStop.");
  }
}

during_statement::during_statement(conditional_block &&conditional_block,
                                   statement statement_parameters)
    : statement(statement_parameters), block(std::move(conditional_block)) {
  if (not(block.condition.get_type() == type::BOOL or
          block.condition.get_type() == type::INT)) {
    throw runtime_error("Condition passed to during block must be a boolean "
                        "or integer at line " +
                        to_string(line_number) + "\nStop.");
  }
}

wonder_statement::wonder_statement(vector<conditional_block> &&block_list,
                                   bool has_welp,
                                   statement statement_parameters)
    : statement(statement_parameters) {
  auto blocks = std::move(block_list);
  if (has_welp) {
    for (auto it = blocks.begin(); it != prev(blocks.end()); it++) {
      if (not(it->condition.get_type() == type::BOOL or
              it->condition.get_type() == type::INT)) {
        throw runtime_error(
            "Condition passed to conditional block must be a boolean "
            "or integer at line " +
            to_string(line_number) + "\nStop.");
      }
    }
  } else {
    for (auto it = blocks.begin(); it != blocks.end(); it++) {
      if (not(it->condition.get_type() == type::BOOL or
              it->condition.get_type() == type::INT)) {
        throw runtime_error(
            "Condition passed to conditional block must be a boolean "
            "or integer at line " +
            to_string(line_number) + "\nStop.");
      }
    }
  }
}
