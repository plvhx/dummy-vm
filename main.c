#include "src/vm.h"

static char addition[] = {
	0x01, 0x0a, /* STORE 10 */
	0x01, 0x14, /* STORE 20 */
	0x10, /* ADD */
	0x20, /* DISPLAY */
	0x00
};

static char addition_with_first_16bit_operand[] = {
	0x02, 0x05, 0x39, /* STORE16 1337 */
	0x01, 0x20, /* STORE 32 */
	0x10, /* ADD */
	0x20, /* DISPLAY */
	0x00
};

static char addition_with_second_16bit_operand[] = {
	0x01, 0x20, /* STORE 32 */
	0x02, 0x05, 0x78, /* STORE16 1400 */
	0x10, /* ADD */
	0x20, /* DISPLAY */
	0x00
};

static void test_addition(void)
{
	vm_t *vm = vm_init(addition);
	vm_run(vm);
	vm_destroy(vm);
}

static void test_addition_with_first_16bit_operand(void)
{
	vm_t *vm = vm_init(addition_with_first_16bit_operand);
	vm_run(vm);
	vm_destroy(vm);
}

static void test_addition_with_second_16bit_operand(void)
{
	vm_t *vm = vm_init(addition_with_second_16bit_operand);
	vm_run(vm);
	vm_destroy(vm);
}

int main(void)
{
	test_addition();
	test_addition_with_first_16bit_operand();
	test_addition_with_second_16bit_operand();
	return 0;
}
