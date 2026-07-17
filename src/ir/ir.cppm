export module ir;

import std;
using namespace std;

export {
  enum class opcode {
    // i = int reg f = float reg, c = constant, u = universal
    // n = jump length, s = skipped
    setcsu,
    copyusu,
    jmpnni,
    phiuuu,
    castisf,
    notisi,
    divfff,
    diviif,
    diviii,
    modiii,
    mulfff,
    muliii,
    addfff,
    addiii,
    subfff,
    subiii,
    eqffi,
    eqiii,
    ltffi,
    ltiii,
    leffi,
    leiii,
    andiii,
    oriii,
    xoriii
  };

  struct instruction {
    opcode code;
    uint32_t arg1;
    uint32_t arg2;
    uint32_t arg3;
  };
}
