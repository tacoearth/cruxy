export module ir;

import std;
using namespace std;

export {
  enum class opcode {
    // i = int reg f = float reg, v = int const, c = float const
    // n = jump length, s = skipped
    castisf,
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
    neqffi,
    neqiii,
    gtffi,
    gtiii,
    ltffi,
    ltiii,
    geffi,
    geiii,
    leffi,
    leiii,
    andiii,
    oriii,
    xoriii,
    copyisi,
    setvi,
    setcf,
    phiiii,
    phifff,
    jmpinn
  };

  struct instruction {
    opcode code;
    uint32_t arg1;
    uint32_t arg2;
    uint32_t arg3;
  };
}
