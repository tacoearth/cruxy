module lookup;

import syntax;
import std;

// Constructor defintion
// Contains the table itself
lookup_table::lookup_table()
    : table{{"{", word::LEFT_BRACE},
            {"}", word::RIGHT_BRACE},
            {"(", word::LEFT_BRACKET},
            {")", word::RIGHT_BRACKET},
            {":", word::COLON},
            {";", word::SEMICOLON},

            {"int", word::INT},
            {"float", word::FLOAT},
            {"bool", word::BOOL},

            {"not", word::NOT},
            {"/", word::DIVIDE},
            {"//", word::FLOOR_DIVIDE},
            {"%", word::MODULO},
            {"*", word::MULTIPLY},
            {"+", word::ADD},
            {"-", word::SUBTRACT},
            {"^", word::POWER},
            {"~", word::COMPROMISE},

            {"==", word::EQUAL_TO},
            {"!=", word::NOT_EQUAL_TO},
            {"<", word::LESSER},
            {">", word::GREATER},
            {"<=", word::LESSER_EQUAL_TO},
            {">=", word::GREATER_EQUAL_TO},

            {"and", word::AND},
            {"or", word::OR},
            {"xor", word::XOR},

            {"=", word::ASSIGN},
            {"/=", word::ASSIGN_DIVIDE},
            {"//=", word::ASSIGN_FLOOR_DIVIDE},
            {"%=", word::ASSIGN_MODULO},
            {"*=", word::ASSIGN_MULTIPLY},
            {"+=", word::ASSIGN_ADD},
            {"-=", word::ASSIGN_SUBTRACT},

            {"wonder", word::WONDER},
            {"maybe", word::MAYBE},
            {"welp", word::WELP},
            {"awake", word::AWAKE},

            {"during", word::DURING},
            {"done", word::DONE},

            {"taking", word::TAKING},
            {"from", word::FROM},
            {"to", word::TO},
            {"step", word::STEP}} {};

lookup_table &lookup_table::get() {
  static lookup_table instance;
  return instance;
}

// Return unknown if token is new
word lookup_table::operator[](const string &operand) const {
  if (table.contains(operand))
    return table.at(operand);
  else
    return word::UNKNOWN;
}
