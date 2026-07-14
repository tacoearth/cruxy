export module statement;

import expression;
import std;
import token;
import syntax;
using namespace std;

export {
  struct statement {
    int line_number;
    statement(int line);
    virtual ~statement() = default;
  };

  struct assigning_statement : public statement {
    assignment_operator op;
    variable &var;
    subexpression value;

    assigning_statement(assignment_operator op, variable &var,
                        subexpression value, statement statement_parameters);
  };

  using scope = unordered_map<string, unique_ptr<variable>>;

  struct statement_block {
    statement_block *parent = nullptr;
    vector<unique_ptr<statement>> body;

    scope variable_scope;
    variable &get_variable(const string &name);

    void add(unique_ptr<statement> &&ptr_to_statement);
  };
}
