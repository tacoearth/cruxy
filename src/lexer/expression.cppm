export module expression;

import std;
import syntax;
import token;
using namespace std;

export {
  // Forward declarations
  struct unary_expression;
  struct binary_expression;

  struct variable {
    uint32_t name_id;
    type underlying_type;
    type result_type();
    variable(identifier &declaration_token);
  };

  // Subexpressions like a + 10, !true, 5 etc, recursive in nature
  struct subexpression {
    // Stores a reference to any kind of token children
    variant<reference_wrapper<binary_expression>,       // Binary expression
            reference_wrapper<unary_expression>,        // Unary expression
            reference_wrapper<integer_constant>,        // Integer constant
            reference_wrapper<floating_point_constant>, // Floating Points
            reference_wrapper<boolean_constant>,        // true or false
            reference_wrapper<variable>>              // Variable
        variant_expression;

    // Get the result type on evaluation of the expression
    type get_type() const;

    // If the type is TYPE_SELECTOR, gets the value
    // Otherwise, null
    type selector_type() const;
  };

  // Unary expressions like !true involving a single operator and subexpression
  struct unary_expression {
    unary_operator op;
    subexpression operand;
    unary_expression(unary_operator op, subexpression operand);

    type result_type();
  };

  // Binary expressions like b % 30 involving a left and right subexpression
  // with one operator
  struct binary_expression {
    binary_operator op;
    subexpression left_operand;
    subexpression right_operand;
    binary_expression(binary_operator op, subexpression left_operand,
                      subexpression right_operand);
    type result_type();
  };
}
