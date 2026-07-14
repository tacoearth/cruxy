module statement;

import expression;
import std;
import token;
import syntax;
using namespace std;

statement::statement(int line) : line_number(line) {}

assigning_statement::assigning_statement(assignment_operator op, variable &var,
                                         subexpression value,
                                         statement statement_parameters)
    : statement(statement_parameters), op(op), var(var), value(value) {
  if (var.underlying_type == type::INVALID) {
    throw runtime_error("Subexpression is not assignable to type at line " +
                        to_string(line_number) + "\nStop.");
  }
  if (var.underlying_type != value.get_type()) {
    throw runtime_error("Cannot assign type to function call at line " +
                        to_string(line_number) + "\nStop.");
  }
}

void statement_block::add(unique_ptr<statement> &&ptr_to_statement) {
  body.emplace_back(std::move(ptr_to_statement));
}

variable &statement_block::get_variable(const string &name) {

  statement_block *block = this;
  while (!block->variable_scope.contains(name)) {
    if (block == nullptr)
      throw runtime_error("Unable to resolve variable name.\n");
    block = block->parent;
  }
  return *(block->variable_scope[name]);
}
