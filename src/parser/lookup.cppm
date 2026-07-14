export module lookup;

import std;
import syntax;
import token;
using namespace std;

export class lookup_table {
  // LUT
  map<string, word> table;

  // Private Constructor
private:
  lookup_table();

public:
  // Get the singleton LUT instance
  static lookup_table &get();

  // Overridden [] access
  word operator[](const string &operand) const;
};
