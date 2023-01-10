grammar Parser;

import Token;

options{language = Cpp;}

code: stmt*;

stmt: (assemblyinst | quaddecl | filldecl |
          posdecl | maindecl | stackdecl | labeldecl);

assemblyinst: inst
            | inst operand
            | inst operand ',' operand;

inst: MHALT | MNOP | MRRMOVQ | MIRMOVQ | MMRMOVQ | MRMMOVQ |
    MADDQ | MSUBQ | MANDQ | MXORQ | MJMP | MJLE | MJL | MJE |
    MJNE | MJQE | MJQ | MCMOVLE | MCMOVL | MCMOVE | MCMOVNE |
    MCMOVGE | MCMOVG | MCALL | MRET | MPUSHQ | MPOPQ;

operand: MRAX | MRCX | MRBX | MRSP | MRBP | MRSI | MRDI | MR8 |
         MR9 | MR10 | MR11 | MR12 | MR13 | MR14 | LABEL | NUMBER;

quaddecl: QUAD NUMBER (',' NUMBER)*;

filldecl: FILL NUMBER NUMBER;

posdecl: POS NUMBER;

maindecl: MAIN;

stackdecl: STACK NUMBER NUMBER;

labeldecl: LABEL ':';
