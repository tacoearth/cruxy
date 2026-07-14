export module syntax;
import std;

export {
  // Symbols for identifying blocks
  enum class symbol {
    // Braces
    LEFT_BRACE,
    RIGHT_BRACE,
    COLON,

    // Brackets
    LEFT_BRACKET,
    RIGHT_BRACKET,

    // Misc
    SEMICOLON
  };

  // Static types
  enum class type {
    // Primitive types
    INT,
    FLOAT,
    BOOL,

    // Functions are inlined
    FUNCTION,

    // Type that holds a type
    TYPE_SELECTOR,

    // Function return type only
    VOID,

    // Identifiers
    UNKNOWN,
    KNOWN,

    // Throwing errors
    INVALID
  };

  // Operators with only a right operand
  enum class unary_operator { NONE, NOT };

  // Operators which have an operand on the left and right
  enum class binary_operator {
    NONE,

    // Arithmetic
    DIVIDE,
    FLOOR_DIVIDE,
    MODULO,
    MULTIPLY,
    ADD,
    SUBTRACT,

    // Functions disguised as operators
    POWER,
    COMPROMISE,

    // Comparision
    EQUAL_TO,
    NOT_EQUAL_TO,
    LESSER,
    GREATER,
    LESSER_EQUAL_TO,
    GREATER_EQUAL_TO, // Logical
    AND,
    OR,
    XOR
  };

  // Assignment Operator
  enum class assignment_operator {
    // Standard assignment operator
    ASSIGN,

    // Text
    ASSIGN_DIVIDE,
    ASSIGN_FLOOR_DIVIDE,
    ASSIGN_MODULO,
    ASSIGN_MULTIPLY,
    ASSIGN_ADD,
    ASSIGN_SUBTRACT,
  };

  // Reserved keywords
  enum class keyword {
    WONDER,
    MAYBE,
    WELP,
    AWAKE,

    DURING,
    DONE,

    TAKING,
    FROM,
    TO,
    STEP
  };

  // Boolean constants
  enum class boolean { TRUE, FALSE };

  // Everything for the tokenizer
  enum class word {
    LEFT_BRACE,
    RIGHT_BRACE,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    COLON,
    SEMICOLON,
    INT,
    FLOAT,
    BOOL,
    UNKNOWN,
    NOT,
    DIVIDE,
    FLOOR_DIVIDE,
    MODULO,
    MULTIPLY,
    ADD,
    SUBTRACT,
    POWER,
    COMPROMISE,
    EQUAL_TO,
    NOT_EQUAL_TO,
    LESSER,
    GREATER,
    LESSER_EQUAL_TO,
    GREATER_EQUAL_TO,
    AND,
    OR,
    XOR,
    ASSIGN,
    ASSIGN_DIVIDE,
    ASSIGN_FLOOR_DIVIDE,
    ASSIGN_MODULO,
    ASSIGN_MULTIPLY,
    ASSIGN_ADD,
    ASSIGN_SUBTRACT,
    WONDER,
    MAYBE,
    WELP,
    AWAKE,
    DURING,
    DONE,
    TAKING,
    FROM,
    TO,
    STEP
  };
}

export std::set<word> all = {word::LEFT_BRACE,
                             word::RIGHT_BRACE,
                             word::LEFT_BRACKET,
                             word::RIGHT_BRACKET,
                             word::SEMICOLON,           // done
                             word::COLON,               // done
                             word::INT,                 // done
                             word::FLOAT,               // done
                             word::BOOL,                // done
                             word::UNKNOWN,             // done
                             word::NOT,                 // done
                             word::DIVIDE,              // done
                             word::FLOOR_DIVIDE,        // done
                             word::MODULO,              // done
                             word::MULTIPLY,            // done
                             word::ADD,                 // done
                             word::SUBTRACT,            // done
                             word::POWER,               // done
                             word::COMPROMISE,          // done
                             word::EQUAL_TO,            // done
                             word::NOT_EQUAL_TO,        // done
                             word::LESSER,              // done
                             word::GREATER,             // done
                             word::LESSER_EQUAL_TO,     // done
                             word::GREATER_EQUAL_TO,    // done
                             word::AND,                 // done
                             word::OR,                  // done
                             word::XOR,                 // done
                             word::ASSIGN,              // done
                             word::ASSIGN_DIVIDE,       // done
                             word::ASSIGN_FLOOR_DIVIDE, // done
                             word::ASSIGN_MODULO,       // done
                             word::ASSIGN_MULTIPLY,     // done
                             word::ASSIGN_ADD,          // done
                             word::ASSIGN_SUBTRACT,     // done
                             word::WONDER,
                             word::MAYBE,
                             word::WELP,
                             word::AWAKE,
                             word::DURING,
                             word::DONE,
                             word::TAKING,
                             word::FROM,
                             word::TO,
                             word::STEP};

// excluding declaration
//
export std::set<word> unary_ops = {word::NOT};

export std::set<word> binary_ops = {word::DIVIDE,
                                    word::FLOOR_DIVIDE,
                                    word::MODULO,
                                    word::MULTIPLY,
                                    word::ADD,
                                    word::SUBTRACT,
                                    word::POWER,
                                    word::COMPROMISE,
                                    word::EQUAL_TO,
                                    word::NOT_EQUAL_TO,
                                    word::LESSER,
                                    word::GREATER,
                                    word::LESSER_EQUAL_TO,
                                    word::GREATER_EQUAL_TO,
                                    word::AND,
                                    word::OR,
                                    word::XOR};

export std::set<word> assignment_ops = {
    word::ASSIGN,         word::ASSIGN_DIVIDE,   word::ASSIGN_FLOOR_DIVIDE,
    word::ASSIGN_MODULO,  word::ASSIGN_MULTIPLY, word::ASSIGN_ADD,
    word::ASSIGN_SUBTRACT};

export std::set<word> typenames = {word::INT, word::FLOAT, word::BOOL};

export std::set<word> statement_starters = {word::UNKNOWN, word::WONDER,
                                            word::DURING, word::TAKING};

export std::array<unary_operator, 1> unary_precedence = {unary_operator::NOT};

export std::array<binary_operator, 17> binary_precedence = {
    // Arithmetic
    binary_operator::DIVIDE, binary_operator::FLOOR_DIVIDE,
    binary_operator::MODULO, binary_operator::MULTIPLY, binary_operator::ADD,
    binary_operator::SUBTRACT,

    // Functions disguised as operators
    binary_operator::POWER, binary_operator::COMPROMISE,

    // Comparision
    binary_operator::EQUAL_TO, binary_operator::NOT_EQUAL_TO,
    binary_operator::LESSER, binary_operator::GREATER,
    binary_operator::LESSER_EQUAL_TO,
    binary_operator::GREATER_EQUAL_TO, // Logical
    binary_operator::AND, binary_operator::OR, binary_operator::XOR};
