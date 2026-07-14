module token;

import syntax;
using namespace std;

token::token(uint32_t id, int line_number, enum word word)
    : id(id), line_number(line_number), word(word) {}

type token::result_type() { return type::INVALID; }

binary_operator token::is_binary_operator() { return binary_operator::NONE; }
unary_operator token::is_unary_operator() { return unary_operator::NONE; }

symbol_token::symbol_token(uint32_t id, int line_number, enum word word,
                           symbol which)
    : token(id, line_number, word), which(which) {}

identifier::identifier(uint32_t id, int line_number, enum word word,
                       type underlying_type, string name, uint32_t name_id)
    : token(id, line_number, word), underlying_type(underlying_type),
      name(name), name_id(name_id) {}

// Identifier result type
type identifier::result_type() { return underlying_type; }

integer_constant::integer_constant(uint32_t id, int line_number, enum word word,
                                   int value)
    : token(id, line_number, word), value(value) {}

// Integer constants result type
type integer_constant::result_type() { return type::INT; }

floating_point_constant::floating_point_constant(uint32_t id, int line_number,
                                                 enum word word, float value)
    : token(id, line_number, word), value(value) {}
// Floating constant result type
type floating_point_constant::result_type() { return type::FLOAT; }

// Boolean constant result type
type boolean_constant::result_type() { return type::BOOL; }
boolean_constant::boolean_constant(uint32_t id, int line_number, enum word word,
                                   enum boolean value)
    : token(id, line_number, word), value(value) {}

type_selector::type_selector(uint32_t id, int line_number, enum word word,
                             type selection)
    : token(id, line_number, word), selection(selection) {}

unary_operator_token::unary_operator_token(uint32_t id, int line_number,
                                           enum word word, unary_operator op)
    : token(id, line_number, word), op(op) {}

unary_operator unary_operator_token::is_unary_operator() { return op; }

binary_operator_token::binary_operator_token(uint32_t id, int line_number,
                                             enum word word, binary_operator op)
    : token(id, line_number, word), op(op) {}

binary_operator binary_operator_token::is_binary_operator() { return op; }

assignment_operator_token::assignment_operator_token(uint32_t id,
                                                     int line_number,
                                                     enum word word,
                                                     assignment_operator op)
    : token(id, line_number, word), op(op) {}

keyword_token::keyword_token(uint32_t id, int line_number, enum word word,
                             enum keyword keyword)
    : token(id, line_number, word), keyword(keyword) {}

placeholder::placeholder(token *op, token *left, token *right)
    : token(*left), op(op), left(left), right(right) {}
