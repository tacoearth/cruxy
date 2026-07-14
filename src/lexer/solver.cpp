module solver;

import std;
import syntax;
import token;
import expression;
import statement;
using namespace std;

auto bracket::operator<=>(const bracket &other) const {
  if (depth != other.depth)
    return depth <=> other.depth;
  else
    return other.order <=> order;
}

void solver::populate_queue(span<unique_ptr<token>> tokens) {
  working_list = tokens |
                 views::transform([](auto &ptr) { return ptr.get(); }) |
                 ranges::to<list>();

  token *left_bracket =
      new symbol_token(0, 0, word::LEFT_BRACKET, symbol::LEFT_BRACKET);
  token *right_bracket =
      new symbol_token(0, 0, word::LEFT_BRACKET, symbol::LEFT_BRACKET);

  working_list.push_front(left_bracket);
  working_list.push_back(right_bracket);

  int depth = 0, order = 0;
  stack<list<token *>::iterator> left_stack;
  for (auto it = working_list.begin(); it != working_list.end(); it++) {
    token *ptr = *it;
    if (ptr->word == word::LEFT_BRACKET) {
      depth++;
      order++;
      left_stack.push(it);
    } else if (ptr->word == word::RIGHT_BRACKET) {
      bracket_queue.emplace(bracket{left_stack.top(), next(it), depth, order});
      left_stack.pop();
      depth--;
    }
  }
}

void solver::solve_bracket(const bracket &bracket) {

  for (unary_operator preceding : unary_precedence) {
    for (auto it = bracket.begin; it != bracket.end; it++) {
      auto token = *it;
      auto op = token->is_unary_operator();
      if (op == preceding) {
        placeholder replacement(*it, *prev(it));
        replacements.push_back(replacement);
        auto next_it = working_list.erase(it, next(it, 2));
        it = working_list.insert(next_it, &replacements.back());
      }
    }

    if (distance(bracket.begin, bracket.end) == 3) {
      working_list.erase(bracket.begin);
      working_list.erase(prev(bracket.end));
      return;
    }
  }

  for (binary_operator preceding : binary_precedence) {
    for (auto it = bracket.begin; it != bracket.end; it++) {
      auto token = *it;
      auto op = token->is_binary_operator();
      if (op == preceding) {
        placeholder replacement(*it, *prev(it), *next(it));
        replacements.push_back(replacement);
        auto next_it = working_list.erase(prev(it), next(it, 2));
        it = working_list.insert(next_it, &replacements.back());
      }
    }

    if (distance(bracket.begin, bracket.end) == 3) {
      working_list.erase(bracket.begin);
      working_list.erase(prev(bracket.end));
      return;
    }
  }
}

subexpression solver::expand(token *root) {
  auto expandable = dynamic_cast<placeholder *>(root);
  if (expandable != nullptr) {
    token *op = expandable->op;
    if (op->is_binary_operator() != binary_operator::NONE) {
      auto token = dynamic_cast<binary_operator_token *>(op);
      auto exp = new binary_expression(token->op, expand(expandable->left),
                                       expand(expandable->right));
      return {ref(*exp)};
    } else if (op->is_unary_operator() != unary_operator::NONE) {
      auto token = dynamic_cast<unary_operator_token *>(expandable->op);
      auto exp = new unary_expression(token->op, expand(expandable->left));
      return {ref(*exp)};
    } else {
      throw runtime_error("Unexpected error. \n");
    }
  } else {
    auto var = dynamic_cast<identifier *>(root);
    if (var != nullptr) {
      return {ref(*block.variable_scope[var->name])};
    } else {
      type result = root->result_type();
      switch (result) {
      case type::INT: {
        auto constant = dynamic_cast<integer_constant *>(root);
        return {ref(*constant)};
      }
      case type::FLOAT: {
        auto constant = dynamic_cast<floating_point_constant *>(root);
        return {ref(*constant)};
      }
      case type::BOOL: {
        auto constant = dynamic_cast<boolean_constant *>(root);
        return {ref(*constant)};
      }
      default: {
        throw runtime_error("Unexpected error [weird constant]\n");
      }
      }
    }
  }
}

subexpression solver::make_subexpression(span<unique_ptr<token>> expression) {
  populate_queue(expression);
  while (!bracket_queue.empty()) {
    solve_bracket(bracket_queue.top());
    bracket_queue.pop();
  }
  if (working_list.size() == 1) {
    return expand(*working_list.begin());

  } else {
    throw runtime_error("Unexpected error while parsing expression.\n");
  }
}

solver::solver(span<unique_ptr<token>> tokens, statement_block &block)
    : block(block), solution(make_subexpression(tokens)) {}
