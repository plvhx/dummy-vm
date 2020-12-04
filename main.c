#include "src/vm.h"

static char addition[] = {
	0x01, 0x0a, /* STORE 10 */
	0x01, 0x14, /* STORE 20 */
	0x10, /* ADD */
	0x20, /* DISPLAY */
};

static void test_addition(void)
{
	vm_t *vm = vm_init(addition);
	vm_run(vm);
	vm_destroy(vm);
}

int main(void)
{
	test_addition();
	return 0;
}
