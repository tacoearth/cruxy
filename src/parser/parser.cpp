module parser;

import std;
import syntax;
import token;
import lookup;
using namespace std;

template <typename T> set<T> make_union(initializer_list<set<T>> sets) {
  set<T> result;
  for (auto set : sets)
    result.merge(set);
  return result;
}

template <typename token_type, typename... pack>
unique_ptr<token_type> parser::create_token(pack &&...args) {
  return make_unique<token_type>(top_token_id++, line_number, current_word,
                                 std::forward<pack>(args)...);
}

unique_ptr<token> parser::make_token(const string &complete_name) {
  auto &table = lookup_table::get();
  current_word = table[complete_name];
  if (valid_words.top().contains(current_word)) {
    if (statement_starters.contains(current_word))
      valid_words.pop();
  } else {
    throw runtime_error("Unexpected token at line " + to_string(line_number) +
                        ".\nStop.");
  }

  switch (current_word) {

  case word::UNKNOWN: {

    if (isdigit(complete_name.front())) {

      if (complete_name.find('.') != string::npos) {

        float numeric_value;
        try {
          numeric_value = stof(complete_name);
        } catch (const invalid_argument &error) {
          throw runtime_error("Invalid floating point received at line " +
                              to_string(line_number) + ".\nStop.");
        }
        valid_words.top().merge(make_union({binary_ops, {word::NOT}}));

        return create_token<floating_point_constant>(numeric_value);

      } else {

        int numeric_value;
        try {
          numeric_value = stoi(complete_name);
        } catch (const invalid_argument &error) {
          throw runtime_error("Invalid integer received at line " +
                              to_string(line_number) + ".\nStop.");
        }
        valid_words.top().merge(make_union({binary_ops, {word::NOT}}));

        return create_token<integer_constant>(numeric_value);
      }

    } else {
      if (complete_name == "true") {
        valid_words.top().merge(make_union({binary_ops, {word::NOT}}));
        return create_token<boolean_constant>(boolean::TRUE);
      } else if (complete_name == "false") {
        valid_words.top().merge(make_union({binary_ops, {word::NOT}}));
        return create_token<boolean_constant>(boolean::FALSE);
      }

      auto it = ranges::find_if(namestack, [complete_name](auto &entry) {
        return get<string>(entry) == complete_name;
      });
      if (it != namestack.end()) {
        valid_words.top().merge(
            make_union({binary_ops, assignment_ops, {word::NOT}}));

        return create_token<identifier>(get<type>(*it), complete_name,
                                        get<uint32_t>(*it));

      } else {
        valid_words.push({word::COLON});
        namestack.push_back(
            {complete_name, type::UNKNOWN, top_identifier_id++});
        name_counts.top()++;


        return create_token<identifier>(type::UNKNOWN, complete_name,
                                        top_identifier_id);
      }
    }
  }

  case word::COLON:

    valid_words.push(typenames);

    return create_token<symbol_token>(symbol::COLON);

  case word::INT:

    valid_words.push({word::ASSIGN, word::SEMICOLON, word::FROM});
    get<type>(namestack.back()) = type::INT;

    return create_token<type_selector>(type::INT);

  case word::FLOAT:

    valid_words.push({word::ASSIGN, word::SEMICOLON, word::FROM});
    get<type>(namestack.back()) = type::FLOAT;

    return create_token<type_selector>(type::FLOAT);

  case word::BOOL:

    valid_words.push({word::ASSIGN, word::SEMICOLON, word::FROM});
    get<type>(namestack.back()) = type::BOOL;

    return create_token<type_selector>(type::BOOL);

  case word::ASSIGN:

    valid_words.push({word::LEFT_BRACKET, word::UNKNOWN, word::NOT});
    return create_token<assignment_operator_token>(

        assignment_operator::ASSIGN);

  case word::ASSIGN_DIVIDE:

    valid_words.push({word::LEFT_BRACKET, word::UNKNOWN, word::NOT});
    return create_token<assignment_operator_token>(

        assignment_operator::ASSIGN_DIVIDE);

  case word::ASSIGN_FLOOR_DIVIDE:

    valid_words.push({word::LEFT_BRACKET, word::UNKNOWN, word::NOT});

    return create_token<assignment_operator_token>(
        assignment_operator::ASSIGN_FLOOR_DIVIDE);

  case word::ASSIGN_MODULO:

    valid_words.push({word::LEFT_BRACKET, word::UNKNOWN, word::NOT});

    return create_token<assignment_operator_token>(
        assignment_operator::ASSIGN_MODULO);

  case word::ASSIGN_MULTIPLY:

    valid_words.push({word::LEFT_BRACKET, word::UNKNOWN, word::NOT});

    return create_token<assignment_operator_token>(
        assignment_operator::ASSIGN_MULTIPLY);

  case word::ASSIGN_ADD:

    valid_words.push({word::LEFT_BRACKET, word::UNKNOWN, word::NOT});

    return create_token<assignment_operator_token>(
        assignment_operator::ASSIGN_ADD);

  case word::ASSIGN_SUBTRACT:

    valid_words.push({word::LEFT_BRACKET, word::UNKNOWN, word::NOT});

    return create_token<assignment_operator_token>(
        assignment_operator::ASSIGN_SUBTRACT);

  case word::NOT:

    valid_words.push({word::LEFT_BRACKET, word::UNKNOWN});

    return create_token<unary_operator_token>(unary_operator::NOT);

  case word::DIVIDE:

    valid_words.push({word::LEFT_BRACKET, word::UNKNOWN, word::NOT});

    return create_token<binary_operator_token>(binary_operator::DIVIDE);

  case word::FLOOR_DIVIDE:

    valid_words.push({word::LEFT_BRACKET, word::UNKNOWN, word::NOT});

    return create_token<binary_operator_token>(binary_operator::FLOOR_DIVIDE);

  case word::MODULO:

    valid_words.push({word::LEFT_BRACKET, word::UNKNOWN, word::NOT});

    return create_token<binary_operator_token>(binary_operator::MODULO);

  case word::MULTIPLY:

    valid_words.push({word::LEFT_BRACKET, word::UNKNOWN, word::NOT});

    return create_token<binary_operator_token>(binary_operator::MULTIPLY);

  case word::ADD:

    valid_words.push({word::LEFT_BRACKET, word::UNKNOWN, word::NOT});

    return create_token<binary_operator_token>(binary_operator::ADD);

  case word::SUBTRACT:

    valid_words.push({word::LEFT_BRACKET, word::UNKNOWN, word::NOT});

    return create_token<binary_operator_token>(binary_operator::SUBTRACT);

  case word::POWER:

    valid_words.push({word::LEFT_BRACKET, word::UNKNOWN, word::NOT});

    return create_token<binary_operator_token>(binary_operator::POWER);

  case word::COMPROMISE:

    valid_words.push({word::LEFT_BRACKET, word::UNKNOWN, word::NOT});

    return create_token<binary_operator_token>(binary_operator::COMPROMISE);

  case word::EQUAL_TO:

    valid_words.push({word::LEFT_BRACKET, word::UNKNOWN, word::NOT});

    return create_token<binary_operator_token>(binary_operator::EQUAL_TO);

  case word::NOT_EQUAL_TO:

    valid_words.push({word::LEFT_BRACKET, word::UNKNOWN, word::NOT});

    return create_token<binary_operator_token>(binary_operator::NOT_EQUAL_TO);

  case word::LESSER:

    valid_words.push({word::LEFT_BRACKET, word::UNKNOWN, word::NOT});

    return create_token<binary_operator_token>(binary_operator::LESSER);

  case word::GREATER:

    valid_words.push({word::LEFT_BRACKET, word::UNKNOWN, word::NOT});

    return create_token<binary_operator_token>(binary_operator::GREATER);

  case word::LESSER_EQUAL_TO:

    valid_words.push({word::LEFT_BRACKET, word::UNKNOWN, word::NOT});

    return create_token<binary_operator_token>(

        binary_operator::LESSER_EQUAL_TO);

  case word::GREATER_EQUAL_TO:

    valid_words.push({word::LEFT_BRACKET, word::UNKNOWN, word::NOT});

    return create_token<binary_operator_token>(
        binary_operator::GREATER_EQUAL_TO);

  case word::AND:

    valid_words.push({word::LEFT_BRACKET, word::UNKNOWN, word::NOT});

    return create_token<binary_operator_token>(binary_operator::AND);

  case word::OR:

    valid_words.push({word::LEFT_BRACKET, word::UNKNOWN, word::NOT});

    return create_token<binary_operator_token>(binary_operator::OR);

  case word::XOR:

    valid_words.push({word::LEFT_BRACKET, word::UNKNOWN, word::NOT});

    return create_token<binary_operator_token>(binary_operator::XOR);

  case word::WONDER:

    valid_words.push({word::AWAKE, word::MAYBE, word::WELP});
    valid_words.push({word::LEFT_BRACE});
    valid_words.push({word::LEFT_BRACKET});

    return create_token<keyword_token>(keyword::WONDER);

  case word::LEFT_BRACKET:

    valid_words.push({word::RIGHT_BRACKET});
    valid_words.push(set<word>{word::UNKNOWN});

    return create_token<symbol_token>(symbol::LEFT_BRACKET);

  case word::RIGHT_BRACKET:

    return create_token<symbol_token>(symbol::RIGHT_BRACKET);

  case word::LEFT_BRACE:

    valid_words.push({word::RIGHT_BRACE});
    valid_words.top().merge(set<word>{word::UNKNOWN});

    name_counts.push(0);


    return create_token<symbol_token>(symbol::LEFT_BRACE);

  case word::RIGHT_BRACE:

    namestack.resize(namestack.size() - name_counts.top());
    name_counts.pop();

    return create_token<symbol_token>(symbol::RIGHT_BRACE);

  case word::MAYBE:

    valid_words.push({word::AWAKE, word::MAYBE, word::WELP});
    valid_words.push({word::LEFT_BRACE});
    valid_words.push({word::LEFT_BRACKET});

    return create_token<keyword_token>(keyword::MAYBE);

  case word::WELP:

    valid_words.push({word::LEFT_BRACE});

    return create_token<keyword_token>(keyword::WELP);

  case word::AWAKE:

    valid_words.top().merge(statement_starters);

    return create_token<keyword_token>(keyword::AWAKE);

  case word::DURING:

    valid_words.push({word::DONE});
    valid_words.push({word::LEFT_BRACE});
    valid_words.push({word::LEFT_BRACKET});

    return create_token<keyword_token>(keyword::DURING);

  case word::DONE:

    valid_words.top().merge(statement_starters);

    return create_token<keyword_token>(keyword::DONE);

  case word::SEMICOLON:

    valid_words.top().merge(statement_starters);

    return create_token<symbol_token>(symbol::SEMICOLON);

  case word::TAKING:

    valid_words.push({word::DONE});
    valid_words.push({word::LEFT_BRACE});
    valid_words.push({word::STEP});
    valid_words.push({word::TO});
    valid_words.push({word::FROM});
    valid_words.push({word::UNKNOWN});

    return create_token<keyword_token>(keyword::TAKING);

  case word::FROM:

    valid_words.push({word::UNKNOWN});

    return create_token<keyword_token>(keyword::FROM);

  case word::TO:

    valid_words.push({word::UNKNOWN});

    return create_token<keyword_token>(keyword::TO);

  case word::STEP:

    valid_words.push({word::UNKNOWN});

    return create_token<keyword_token>(keyword::STEP);
  }
}

parser::parser(const string &path, vector<unique_ptr<token>> &token_list) {

  try {
    source_file.open(path);
  } catch (const ios::failure &exception) {
    throw runtime_error(exception.what());
  }

  valid_words.push({word::UNKNOWN, word::WONDER, word::DURING, word::TAKING});

  while (source_file.get(character)) {

    if (character == '\n')
      line_number++;

    if (isspace(character)) {

      if (name.empty()) {
        continue;
      } else {
        token_list.emplace_back(make_token(name));
        name.clear();
      }

    } else if (not(isalnum(character) or character == '.' or
                   character == '_')) {
      token_list.emplace_back(make_token(name));
      name.clear();
      name += character;
      token_list.emplace_back(make_token(name));
      name.clear();
    } else {
      name += character;
    }
  }
};
