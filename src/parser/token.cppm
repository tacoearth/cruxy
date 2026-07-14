export module token;

import std;
import syntax;
using namespace std;

export {
  // Base token class
  class token {
  public:
    uint32_t id;
    int line_number;
    word word;

    token(uint32_t id, int line_number, enum word word);
    virtual ~token() = default;
    
    virtual type result_type();
    virtual binary_operator is_binary_operator();
    virtual unary_operator is_unary_operator();
  };

  // Symbol
  struct symbol_token : public token {
    symbol which;
    symbol_token(uint32_t id, int line_number, enum word word, symbol which);
  };

  // Identifier
  struct identifier : public token {
    type underlying_type;
    string name;
    uint32_t name_id;
    identifier(uint32_t id, int line_number, enum word word,
               type underlying_type, string name, uint32_t name_id);

    type result_type() override;
  };

  // Integer constants like 123
  struct integer_constant : public token {
    int value;
    integer_constant(uint32_t id, int line_number, enum word word, int value);
    type result_type() override;
  };

  // Floating constants like 420.69
  struct floating_point_constant : public token {
    float value;
    floating_point_constant(uint32_t id, int line_number, enum word word,
                            float value);
    type result_type() override;
  };

  // Boolean constants true and false
  struct boolean_constant : public token {
    boolean value;
    type result_type() override;
    boolean_constant(uint32_t id, int line_number, enum word word,
                     enum boolean value);
  };

  // Type selectors like int float etc
  struct type_selector : public token {
    type selection;
    type_selector(uint32_t id, int line_number, enum word word, type selection);
  };

  struct unary_operator_token : public token {
    unary_operator op;
    unary_operator_token(uint32_t id, int line_number, enum word word,
                         unary_operator op);
    unary_operator is_unary_operator() override;
  };

  struct binary_operator_token : public token {
    binary_operator op;
    binary_operator_token(uint32_t id, int line_number, enum word word,
                          binary_operator op);
    binary_operator is_binary_operator() override;
  };

  struct assignment_operator_token : public token {
    assignment_operator op;
    assignment_operator_token(uint32_t id, int line_number, enum word word,
                              assignment_operator op);
  };

  struct keyword_token : public token {
    keyword keyword;
    keyword_token(uint32_t id, int line_number, enum word word,
                  enum keyword keyword);
  };

  struct placeholder : public token {
    token* op;
    token* left = nullptr;
    token* right = nullptr;
    placeholder(token *op, token* left, token* right = nullptr);
  };

}
