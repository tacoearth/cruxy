export module solver;

import std;
import syntax;
import token;
import expression;
import statement;
using namespace std;

export {
  struct bracket {
    list<token *>::iterator begin;
    list<token *>::iterator end;
    int depth;
    int order;

    auto operator<=>(const bracket &other) const;
  };

  class solver {
    list<token *> working_list;
    list<placeholder> replacements;
    priority_queue<bracket> bracket_queue;
    statement_block &block;

  public:
    subexpression solution;

  private:
    void populate_queue(span<unique_ptr<token>> tokens);
    void solve_bracket(const bracket &bracket);

    subexpression expand(token *root);
    subexpression make_subexpression(span<unique_ptr<token>> expression);

  public:
    solver(span<unique_ptr<token>> tokens, statement_block &block);
  };
}
