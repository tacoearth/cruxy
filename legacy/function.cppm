export module function;

import std;
import token;
import syntax;
import expression;
import statement;
import function_interface;

using namespace std;

export {
  struct function_definition : public function_interface {
    type return_type;
    type argument_type;
    statement_block body;
  };

  struct function_statement : public statement {
    function_call &call;
  };
}
