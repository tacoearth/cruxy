import std;
import syntax;
import token;
import expression;
import statement;
import conditional;
import solver;
using namespace std;

class builder {
  vector<unique_ptr<token>> &token_list;
  // check for lvalue rvalue (real ez)
  // make statements (long but slop work)
  // handle subexpressions (we doin this today baby)

  /*

  so like
  if first thing identifier
  then its gonna be assignment aint it
  if ts a symbol then like there will be flags for handling depths and scope
  only two types of lvalues one is name and other has declarattion

  if its during
  then go to do shit
  if its taking
  if its wonder

   */

  // create a copy of tokens
  // create a bracket depth priority queue which tracks only the left
  // bracket. on this priority queue do precedence until its one element,
  // then remove bracket. replace a binary op or unary op with
  // subexp_placeholder in token copy. pop the queue and do until its empty
  // thing moves left to right per operator, O*N, until its just one fake
  // token left. early skipping would be nice.

  builder(vector<unique_ptr<token>> &token_list) : token_list(token_list) {
    // check for lvalue rvalue
    size_t i = 0;
    statement_block block;

    unique_ptr<token> &ptr = token_list[i];
    auto &current_token = *ptr;

    if (typeid(current_token) == typeid(identifier)) {
      auto &declaration = dynamic_cast<identifier &>(current_token);
      if (declaration.underlying_type == type::UNKNOWN) {
        // a decl

        auto &which_type = dynamic_cast<type_selector &>(*token_list[i + 2]);
        type type = which_type.selection;
        declaration.underlying_type = type;

        unique_ptr<variable> new_var = make_unique<variable>(declaration);

        // replace this with simple typeid check
        auto *next_token =
            dynamic_cast<assignment_operator_token *>(token_list[i + 3].get());
        if (next_token != nullptr and
            next_token->op == assignment_operator::ASSIGN) {

          auto first_token = token_list.begin() + 4;
          auto it = first_token;
          while ((**it).word != word::SEMICOLON)
            it++;
          span<unique_ptr<token>> expression_tokens{first_token, next(it)};

          statement statement_params(current_token.line_number);
          solver solve(expression_tokens, block);
          auto statement = make_unique<assigning_statement>(
              assignment_operator::ASSIGN, *new_var, solve.solution,
              statement_params);
          block.add(std::move(statement));

          // do shi
        }
        block.variable_scope[declaration.name] = std::move(new_var);

      } else {


        
      }

    } else if (typeid(token) == typeid(keyword_token)) {
      auto &key = dynamic_cast<keyword_token &>(current_token);
      if (key.keyword == keyword::WONDER) {

      } else if (key.keyword == keyword::DURING) {

      } else if (key.keyword == keyword::TAKING) {

      } else {
        throw runtime_error("An unexpected error occurred.\n");
      }

    } else {
      throw runtime_error("An unexpected error occurred.\n");
    }
  }
};
