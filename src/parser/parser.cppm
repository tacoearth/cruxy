export module parser;

import std;
import syntax;
import token;

using namespace std;

export {

  template <typename T> set<T> make_union(initializer_list<set<T>> sets);

  class parser {
    ifstream source_file;

    char character;
    string name;
    int line_number = 1;
    word current_word;

    vector<tuple<string, type, uint32_t>> namestack;
    stack<size_t> name_counts;
    stack<set<word>> valid_words;

    uint32_t top_token_id = 1;
    uint32_t top_identifier_id = 1;

    unique_ptr<token> make_token(const string &complete_name);

    template <typename token_type, typename... pack>
    unique_ptr<token_type> create_token(pack &&...args);

    parser(const string &path, vector<unique_ptr<token>> &token_list);
  };
}
