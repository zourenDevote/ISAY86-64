lexer grammar Token;

options{language = Cpp;}

POS:  '.pos';
FILL: '.fill';
MAIN: '.main';
QUAD: '.quad';
STACK: '.stack';

// 汇编指令
MHALT: 'halt';
MNOP:  'nop';
MRRMOVQ: 'rrmovq';
MIRMOVQ: 'irmovq';
MRMMOVQ: 'rmmovq';
MMRMOVQ: 'mrmovq';
MADDQ:   'addq';
MSUBQ:   'subq';
MANDQ:   'andq';
MXORQ:   'xorq';
MJMP:    'jmp';
MJLE:    'jle';
MJL:     'jl';
MJE:     'je';
MJNE:    'jne';
MJQE:    'jqe';
MJQ:     'jq';
MCMOVLE: 'cmovle';
MCMOVL:  'cmovl';
MCMOVE:  'cmove';
MCMOVNE: 'cmovne';
MCMOVGE: 'cmovge';
MCMOVG:  'cmovg';
MCALL:   'call';
MRET:    'ret';
MPUSHQ:  'pushq';
MPOPQ:   'popq';

// 寄存器
MRAX:    'rax';
MRCX:    'rcx';
MRBX:    'rbx';
MRSP:    'rsp';
MRBP:    'rbp';
MRSI:    'rsi';
MRDI:    'rdi';
MR8:     'r8';
MR9:     'r9';
MR10:    'r10';
MR11:    'r11';
MR12:    'r12';
MR13:    'r13';
MR14:    'r14';

// 数字
NUMBER: [1-9][0-9]*
      | '0'
      | '0'('x'|'X')[0-9a-fA-F]+;

// 标号
LABEL:  [a-zA-Z][a-zA-Z0-9]*;

// 空格
WS:     [ \r\n\t]+ -> skip;

// 注释
COMMENT: '//' ~[\r\n]* -> skip;


