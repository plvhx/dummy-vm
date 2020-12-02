#include "src/vm.h"

int main(void)
{
	/**
	 * Bytecode representation (see in src/insn.h)
	 *
	 * STORE 10
	 * STORE 20
	 * LOAD
	 * LOAD
	 * ADD_OP
	 * DISPLAY
	 * STORE 11
	 * STORE 11
	 * LOAD
	 * LOAD
	 * MUL_OP
	 * DISPLAY
	 *
	 * ----- EOF -----
	 */
	vm_repl("\x01\x31\x30\x01\x32\x30\x02\x02\x10\x20\x01\x31\x31\x01\x31\x31\x02\x02\x12\x20");
	return 0;
}
