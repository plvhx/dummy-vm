```
Dummy bytecode VM implementation.

1. How to compile:
	- make

After compiling, there was 2 executable file named 'compiler'
and 'dispatcher'. 'compiler' executable file are used to compile
source file, and source file must ended by '.dasm' extension. 'dispatcher'
executable file are used to run compiled bytecode from associated source file.

Assuming you have source file named 'sample.dasm'. after compile that file,
it's result must be 'sample.cplx'. you can run it's result file with 'dispatcher'
executable file.

Example:
$ compiler -c sample.dasm
$ dispatcher -f sample.cplx

There was 4 general purpose register available in this bytecode (r0, r1, r2, r3).
And integer value allowed in this bytecode are max. 16-bit size.

2. Instruction reference:

- movb r0, <imm8>
	Move immediate 8-bit integer value to r0 register.

- movb r1, <imm8>
	Move immediate 8-bit integer value to r1 register.

- movb r2, <imm8>
	Move immediate 8-bit integer value to r2 register.

- movb r3, <imm8>
	Move immediate 8-bit integer value to r3 register.

- movb r0, <regs>
	Move 8-bit integer value from any register (r0, r1, r2, r3) to r0 register.

- movb r1, <regs>
	Move 8-bit integer value from any register (r0, r1, r2, r3) to r1 register.

- movb r2, <regs>
	Move 8-bit integer value from any register (r0, r1, r2, r3) to r2 register.

- movb r3, <regs>
	Move 8-bit integer value from any register (r0, r1, r2, r3) to r3 register.
```
