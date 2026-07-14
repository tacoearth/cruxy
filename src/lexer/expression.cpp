module expression;

import syntax;
import token;
using namespace std;

variable::variable(identifier &declaration_token)
    : name_id(declaration_token.name_id),
      underlying_type(declaration_token.underlying_type) {}

type variable::result_type() { return underlying_type; }

// get_type Implementation
type subexpression::get_type() const {
  type return_type;
  variant_expression.visit([&return_type](const auto &expression) {
    return_type = expression.get().result_type();
  });
  return return_type;
}

unary_expression::unary_expression(unary_operator op, subexpression operand)
    : op(op), operand(operand) {}

binary_expression::binary_expression(binary_operator op,
                                     subexpression left_operand,
                                     subexpression right_operand)
    : op(op), left_operand(left_operand), right_operand(right_operand) {}

// unary_expression's result_type Implementation
type unary_expression::result_type() {
  // Currently the only unary expression is NOT and it doesn't change the type
  switch (op) {
  case unary_operator::NOT:
    return operand.get_type();
  case unary_operator::NONE:
    return operand.get_type();
  }
}

// binary_expression's result_type Implementation
type binary_expression::result_type() {
  // Types of the left and right expressions
  type left_type = left_operand.get_type();
  type right_type = right_operand.get_type();

  switch (op) {
  case binary_operator::NONE:
    return type::INVALID;

  // Division operator
  case binary_operator::DIVIDE:
    // float / float = float
    // int / int = float
    if ((left_type == type::FLOAT and right_type == type::FLOAT) or
        (left_type == type::INT and right_type == type::INT))
      return left_type;
    // float / int = float
    // int / float = float
    else if ((left_type == type::FLOAT and right_type == type::INT) or
             (left_type == type::INT and right_type == type::FLOAT))
      return type::FLOAT;
    else
      return type::INVALID;

  // Floor division operator
  case binary_operator::FLOOR_DIVIDE:
    // int // int = int
    if (left_type == type::INT and right_type == type::INT)
      return type::INT;
    else
      return type::INVALID;

  // Remainder operator
  case binary_operator::MODULO:
    // int % int = int
    if (left_type == type::INT and right_type == type::INT)
      return type::INT;
    else
      return type::INVALID;

  // Multiplication operator
  case binary_operator::MULTIPLY:
    // float * float = float
    // int * int = float
    if ((left_type == type::FLOAT and right_type == type::FLOAT) or
        (left_type == type::INT and right_type == type::INT))
      return left_type;
    // float * int = float
    // int * float = float
    else if ((left_type == type::FLOAT and right_type == type::INT) or
             (left_type == type::INT and right_type == type::FLOAT))
      return type::FLOAT;
    else
      return type::INVALID;

  // Addition operator
  case binary_operator::ADD:
    // float + float = float
    // int + int = int
    if ((left_type == type::FLOAT and right_type == type::FLOAT) or
        (left_type == type::INT and right_type == type::INT))
      return left_type;
    // float + int = float
    // int + float = float
    else if ((left_type == type::FLOAT and right_type == type::INT) or
             (left_type == type::INT and right_type == type::FLOAT))
      return type::FLOAT;
    else
      return type::INVALID;

  // Subtraction operator
  case binary_operator::SUBTRACT:
    // float - float = float
    // int - int = int
    if ((left_type == type::FLOAT and right_type == type::FLOAT) or
        (left_type == type::INT and right_type == type::INT))
      return left_type;
    // float - int = float
    // int - float = float
    else if ((left_type == type::FLOAT and right_type == type::INT) or
             (left_type == type::INT and right_type == type::FLOAT))
      return type::FLOAT;
    else
      return type::INVALID;

  // Power operator
  case binary_operator::POWER:
    // float ^ int = float
    // int ^ int = int
    if ((left_type == type::FLOAT and right_type == type::INT) or
        (left_type == type::INT and right_type == type::INT))
      return left_type;
    else
      return type::INVALID;

  // Compromise operator
  case binary_operator::COMPROMISE:
    // float ~ float = float
    if (left_type == type::FLOAT and right_type == type::FLOAT)
      return left_type;
    // float ~ int = float
    // int ~ float = float
    // int ~ int = float
    else if ((left_type == type::FLOAT and right_type == type::INT) or
             (left_type == type::INT and right_type == type::FLOAT) or
             (left_type == type::INT and right_type == type::INT))
      return type::FLOAT;
    else
      return type::INVALID;

  // Equality operator
  case binary_operator::EQUAL_TO:
    // float == float
    // int == int
    if ((left_type == type::FLOAT or left_type == type::INT) and
        (left_type == right_type))
      return type::BOOL;
    else
      return type::INVALID;

  // Inequality operator
  case binary_operator::NOT_EQUAL_TO:
    // float != float
    // int != int
    if ((left_type == type::FLOAT or left_type == type::INT) and
        (left_type == right_type))
      return type::BOOL;
    else
      return type::INVALID;

  // Lesser than comparision
  case binary_operator::LESSER:
    // float < float = bool
    // float < int = bool
    // int < float = bool
    // int < int = bool
    if ((left_type == type::FLOAT or left_type == type::INT) and
        (right_type == type::FLOAT or right_type == type::INT))
      return type::BOOL;
    else
      return type::INVALID;

  // Greater than comparision
  case binary_operator::GREATER:
    // float < float = bool
    // float < int = bool
    // int < float = bool
    // int < int = bool
    if ((left_type == type::FLOAT or left_type == type::INT) and
        (right_type == type::FLOAT or right_type == type::INT))
      return type::BOOL;
    else
      return type::INVALID;

  // Lesser than or equal to comparision
  case binary_operator::LESSER_EQUAL_TO:
    // float < float = bool
    // float < int = bool
    // int < float = bool
    // int < int = bool
    if ((left_type == type::FLOAT or left_type == type::INT) and
        (right_type == type::FLOAT or right_type == type::INT))
      return type::BOOL;
    else
      return type::INVALID;

  // Greater than or equal to comparision
  case binary_operator::GREATER_EQUAL_TO:
    // float < float = bool
    // float < int = bool
    // int < float = bool
    // int < int = bool
    if ((left_type == type::FLOAT or left_type == type::INT) and
        (right_type == type::FLOAT or right_type == type::INT))
      return type::BOOL;
    else
      return type::INVALID;

  // Logical AND operator
  case binary_operator::AND:
    // bool and bool = bool
    if (left_type == type::BOOL and right_type == type::BOOL)
      return type::BOOL;
    else
      return type::INVALID;

  // Logical OR operator
  case binary_operator::OR:
    // bool or bool = bool
    if (left_type == type::BOOL and right_type == type::BOOL)
      return type::BOOL;
    else
      return type::INVALID; // Logical XOR operator
  case binary_operator::XOR:
    // bool xor bool = bool
    if (left_type == type::BOOL and right_type == type::BOOL)
      return type::BOOL;
    else
      return type::INVALID;
  }
}
