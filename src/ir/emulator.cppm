export module iremu;

import std;
import ir;
using namespace std;

export {
  class emulator {
  public:
    ifstream source;
    vector<instruction> text;

  private:
    size_t program_counter = 0;
    long long clock = 0;

    struct register_list {
      unordered_map<uint32_t, uint32_t> registers;
      unordered_map<uint32_t, bool> phi_table;
    };
    register_list infinite_registers;

    class reader {
      map<string, opcode> translate{
          {"setcsu", opcode::setcsu},   {"copyusu", opcode::copyusu},
          {"jmpnni", opcode::jmpnni},   {"phiuuu", opcode::phiuuu},
          {"castisf", opcode::castisf}, {"notisi", opcode::notisi},
          {"divfff", opcode::divfff},   {"diviif", opcode::diviii},
          {"diviii", opcode::diviii},   {"modiii", opcode::modiii},
          {"mulfff", opcode::mulfff},   {"muliii", opcode::muliii},
          {"addfff", opcode::addfff},   {"addiii", opcode::addiii},
          {"subfff", opcode::subfff},   {"subiii", opcode::subiii},
          {"eqffi", opcode::eqffi},     {"eqiii", opcode::eqiii},
          {"ltffi", opcode::ltffi},     {"ltiii", opcode::ltiii},
          {"leffi", opcode::leffi},     {"leiii", opcode::leiii},
          {"andiii", opcode::andiii},   {"oriii", opcode::oriii},
          {"xoriii", opcode::xoriii},
      };

      void read(emulator &iremu) {
        string operation;
        uint32_t arg1, arg2, arg3;
        while (iremu.source >> operation >> arg1 >> arg2 >> arg3)
          iremu.text.emplace_back(translate[operation], arg1, arg2, arg3);
      }
    };

    void execute() {
      instruction instruction;
      try {
        instruction = text.at(program_counter);
      } catch (const out_of_range &exception) {
        throw runtime_error("No instruction in text at address " +
                            to_string(program_counter) + ".\n" +
                            exception.what());
      }

      auto &registers = infinite_registers.registers;
      auto &table = infinite_registers.phi_table;
      table[instruction.arg3] = true;

      uint32_t increment = 1;

      switch (instruction.code) {
      case opcode::setcsu: {
        clock += 1;
        registers[instruction.arg3] = instruction.arg1;
      }
      case opcode::copyusu: {
        clock += 1;
        registers[instruction.arg3] = registers[instruction.arg1];
      }
      case opcode::jmpnni: {
        clock += 1;
        if (registers[instruction.arg3] != 0)
          increment = instruction.arg1;
        else
          increment = instruction.arg2;
      }
      case opcode::phiuuu: {
        clock += 0;
        if (table[instruction.arg1])
          registers[instruction.arg3] = registers[instruction.arg1];
        else if (table[instruction.arg2])
          registers[instruction.arg3] = registers[instruction.arg2];
        else
          throw runtime_error("Phi function has not explored either paths at " +
                              to_string(program_counter) + ".\n");
      }
      case opcode::castisf: {
        clock += 3;
        int val1 = bit_cast<int>(registers[instruction.arg1]);
        float cast = static_cast<float>(val1);
        registers[instruction.arg3] = bit_cast<uint32_t>(cast);
      }
      case opcode::notisi: {
        int val1 = bit_cast<int>(registers[instruction.arg1]);
        int val3 = static_cast<int>(!val1);
        registers[instruction.arg3] = bit_cast<uint32_t>(val3);
      }

      case opcode::divfff: {
        clock += 11;
        float val1 = bit_cast<float>(registers[instruction.arg1]);
        float val2 = bit_cast<float>(registers[instruction.arg1]);
        registers[instruction.arg3] = bit_cast<uint32_t>(val1 / val2);
      }
      case opcode::diviif: {
        clock += 17;
        int val1 = bit_cast<int>(registers[instruction.arg1]);
        int val2 = bit_cast<int>(registers[instruction.arg2]);
        float val3 = static_cast<float>(val1) / static_cast<float>(val2);
        registers[instruction.arg3] = bit_cast<uint32_t>(val3);
      }
      case opcode::diviii: {
        clock += 12;
        int val1 = bit_cast<int>(registers[instruction.arg1]);
        int val2 = bit_cast<int>(registers[instruction.arg1]);
        registers[instruction.arg3] = bit_cast<uint32_t>(val1 / val2);
      }
      case opcode::modiii: {
        clock += 12;
        int val1 = bit_cast<int>(registers[instruction.arg1]);
        int val2 = bit_cast<int>(registers[instruction.arg1]);
        registers[instruction.arg3] = bit_cast<uint32_t>(val1 % val2);
      }
      case opcode::mulfff: {
        clock += 3;
        float val1 = bit_cast<float>(registers[instruction.arg1]);
        float val2 = bit_cast<float>(registers[instruction.arg1]);
        registers[instruction.arg3] = bit_cast<uint32_t>(val1 * val2);
      }
      case opcode::muliii: {
        clock += 3;
        int val1 = bit_cast<int>(registers[instruction.arg1]);
        int val2 = bit_cast<int>(registers[instruction.arg1]);
        registers[instruction.arg3] = bit_cast<uint32_t>(val1 * val2);
      }
      case opcode::addfff: {
        clock += 3;
        float val1 = bit_cast<float>(registers[instruction.arg1]);
        float val2 = bit_cast<float>(registers[instruction.arg1]);
        registers[instruction.arg3] = bit_cast<uint32_t>(val1 + val2);
      }
      case opcode::addiii: {
        clock += 1;
        int val1 = bit_cast<int>(registers[instruction.arg1]);
        int val2 = bit_cast<int>(registers[instruction.arg1]);
        registers[instruction.arg3] = bit_cast<uint32_t>(val1 + val2);
      }
      case opcode::subfff: {
        clock += 3;
        float val1 = bit_cast<float>(registers[instruction.arg1]);
        float val2 = bit_cast<float>(registers[instruction.arg1]);
        registers[instruction.arg3] = bit_cast<uint32_t>(val1 - val2);
      }
      case opcode::subiii: {
        clock += 1;
        int val1 = bit_cast<int>(registers[instruction.arg1]);
        int val2 = bit_cast<int>(registers[instruction.arg1]);
        registers[instruction.arg3] = bit_cast<uint32_t>(val1 - val2);
      }
      case opcode::eqffi: {
        clock += 1;
        float val1 = bit_cast<float>(registers[instruction.arg1]);
        float val2 = bit_cast<float>(registers[instruction.arg1]);
        int cmp = static_cast<int>(val1 == val2);
        registers[instruction.arg3] = bit_cast<uint32_t>(cmp);
      }
      case opcode::eqiii: {
        clock += 1;
        int val1 = bit_cast<int>(registers[instruction.arg1]);
        int val2 = bit_cast<int>(registers[instruction.arg1]);
        int cmp = static_cast<int>(val1 == val2);
        registers[instruction.arg3] = bit_cast<uint32_t>(cmp);
      }
      case opcode::ltffi: {
        clock += 1;
        float val1 = bit_cast<float>(registers[instruction.arg1]);
        float val2 = bit_cast<float>(registers[instruction.arg1]);
        int cmp = static_cast<int>(val1 < val2);
        registers[instruction.arg3] = bit_cast<uint32_t>(cmp);
      }
      case opcode::ltiii: {
        clock += 1;
        int val1 = bit_cast<int>(registers[instruction.arg1]);
        int val2 = bit_cast<int>(registers[instruction.arg1]);
        int cmp = static_cast<int>(val1 < val2);
        registers[instruction.arg3] = bit_cast<uint32_t>(cmp);
      }
      case opcode::leffi: {
        clock += 1;
        float val1 = bit_cast<float>(registers[instruction.arg1]);
        float val2 = bit_cast<float>(registers[instruction.arg1]);
        int cmp = static_cast<int>(val1 <= val2);
        registers[instruction.arg3] = bit_cast<uint32_t>(cmp);
      }
      case opcode::leiii: {
        clock += 1;
        int val1 = bit_cast<int>(registers[instruction.arg1]);
        int val2 = bit_cast<int>(registers[instruction.arg1]);
        int cmp = static_cast<int>(val1 <= val2);
        registers[instruction.arg3] = bit_cast<uint32_t>(cmp);
      }
      case opcode::andiii: {
        clock += 1;
        int val1 = bit_cast<int>(registers[instruction.arg1]);
        int val2 = bit_cast<int>(registers[instruction.arg1]);
        int cmp = static_cast<int>(val1 and val2);
        registers[instruction.arg3] = bit_cast<uint32_t>(cmp);
      }
      case opcode::oriii: {
        clock += 1;
        int val1 = bit_cast<int>(registers[instruction.arg1]);
        int val2 = bit_cast<int>(registers[instruction.arg1]);
        int cmp = static_cast<int>(val1 or val2);
        registers[instruction.arg3] = bit_cast<uint32_t>(cmp);
      }
      case opcode::xoriii: {
        clock += 1;
        int val1 = bit_cast<int>(registers[instruction.arg1]);
        int val2 = bit_cast<int>(registers[instruction.arg1]);
        bool bool1 = static_cast<int>(val1);
        bool bool2 = static_cast<int>(val2);
        int cmp = static_cast<int>(bool1 != bool2);
        registers[instruction.arg3] = bit_cast<uint32_t>(cmp);
      }
      }
      program_counter += increment;
    }
  };
}
