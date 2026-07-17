# cruxy
Cruxy is a compiler which implements the syntax described as per the [task's syntax document](https://docs.google.com/document/d/1lspI5sjKNNX2B6Klwa1xXW3xZfhlVVEYI7inJrpKaNs/edit?usp=sharing), using modern C++26 features and modules maintaining a good level of source code readability and an intuitive overall structure. The implementation also does many things differently from other major compilers, by my algorithms being written in such a way that they almost mimic how humans parse and "lex" code instead of fancy algorithms, making it very accessible even for people new to computer science in general.

Why? Because good code is code that everybody can read and understand.

# Parsing and lexing approach
Cruxy features its own parser and lexer, and does not depend on libraries like YACC (I deeply regret not using YACC to save time tho), and instead uses its own predictive parser for checking structure, with zero lookahead. It does this with the concept of "expectation" which is basically what I do myself when reading code.

For example, a '{' expects a '}' at some point in the future, an operator expects a expression, and so on. This is stored as a stack of a set of acceptable tokens in memory. Now, a parser like this cannot guarantee perfect syntax, but it can enforce a certain layout of the program (and also deal with scoping of variable names) which the lexer can then check for using assumptions which it can safely make thanks to the parser pass right before it.

Another example of a "human" approach in the compiler is how it deals with resolving expressions. Instead of using any fancy algorithms which even by offering probable performance upgrades (since expressions in source code are almost never that big anyways) cruxy does exactly what us non-clankers do: sort by the depth of the brackets, search for the operator with higher precedence, replace it with its result (a placeholder, since we don't really know the result at compile time), and build the right tree for it in the AST.

There also is type-checking, which simply defines legal operations and resulting types from a type, operator, type tuple. Anything undefined is an invalid type that propagates throughout the expression.

On an off-note hope when C++29 is out and stable, we get native pattern matching, which reduces the redundant and annoying parts of LUT and enums and so much code.

# The CFG/IR
Converting the AST to CFG (in this case, the IR directly because the IR is made such that it natively provides a CFG-like structure for future optimizations) is the most soul crushing part of every compiler, but not cruxy, because I haven't written it yet. This makes it rival tfab in how very disappointingly useless it can be. I initially wanted to start committing after I atleast got a commit that just does the bare minimum, because thats what commits in real reputable pull requests look like, but I overlooked that programming it would feel like fighting a Destiny 2 boss. Which means it's not difficult, but so long and sloppy and grindy and tiring, and so the previous attempts to doing this are gone.

But that's not the crux of it (ba-dum-tss). The core IR was pre-decided by me at the starting days of the task, and unlike the big boys like LLVM and GIMPLE, the IR is intentionally made to be very small and extremely barebones, like those example turing machines you see in youtube videos. This makes a breeze to apply compiler optimizations in the future, and a lot of optimizations like the Wegman-Zadeck algorithm (which removes dead code and find compile time constants simultaneously)  and and Loop Invariant Code Motion much, much easier to implement, and Copy Propagation and Common Subexpression elimination becomes trivial.

In general, the way the IR basically works is that, almost everything is an assigment that does x = y op z, with each assignment done only once (SSA). And there is only one `jmpnni` instruction which can create branching, making it trivial to isolate basic blocks (aka the guaranteed to be sequential instructions). There is also only one way to push constants from compile time: `setcsu`, so that you can track the assignments ever since this point to check for constants.

# AI Usage
No part of the code is AI-generated. AI usage is at best used for searching up things because in general LLMs are better search engines than search engines are search engines. Also there is some basic human decency shown from my end by not plagiarizing other's work without credit which includes copying things from an LLM. All the work is my own and written by me based on my understanding of things.
