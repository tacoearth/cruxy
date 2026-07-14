export module conditional;

import expression;
import std;
import token;
import syntax;
import statement;
using namespace std;

export {
  struct conditional_block {
    subexpression condition;
    unique_ptr<statement_block> block;
  };

  struct taking_statement : public statement {
    string iterator_name;
    type iterator_type;
    subexpression &initial_value;
    subexpression &final_value;
    subexpression &step_size;
    const unique_ptr<statement_block> body;
    taking_statement(string iterator_name, type iterator_type,
                     subexpression &initial_value, subexpression &final_value,
                     subexpression &step_size,
                     unique_ptr<statement_block> &&body_block,
                     statement statement_parameters);
  };

  struct during_statement : public statement {
    conditional_block block;
    during_statement(conditional_block &&conditional_block,
                     statement statement_parameters);
  };

  struct wonder_statement : public statement {
    vector<conditional_block> ladder;
    optional<unique_ptr<statement_block>> welp_block;

    wonder_statement(vector<conditional_block> &&block_list, bool has_welp,
                     statement statement_parameters);
  };
}
