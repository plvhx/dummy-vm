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

static char addition_with_16bit_operand_both[] = {
	0x02, 0x05, 0x39, /* STORE16 1337 */
	0x02, 0x05, 0x78, /* STORE16 1400 */
	0x10, /* ADD */
	0x20, /* DISPLAY */
	0x00
};

static char subtraction[] = {
	0x01, 0x0a, /* STORE 10 */
	0x01, 0x14, /* STORE 20 */
	0x11, /* SUB */
	0x20, /* DISPLAY */
	0x00
};

static char subtraction_with_first_16bit_operand[] = {
	0x02, 0x05, 0x39, /* STORE16 1337 */
	0x01, 0x20, /* STORE 32 */
	0x11, /* SUB */
	0x20, /* DISPLAY */
	0x00
};

static char subtraction_with_second_16bit_operand[] = {
	0x01, 0x20, /* STORE 32 */
	0x02, 0x05, 0x39, /* STORE16 1337 */
	0x11, /* SUB */
	0x20, /* DISPLAY */
	0x00
};

static char subtraction_with_16bit_operand_both[] = {
	0x02, 0x05, 0x39, /* STORE16 1337 */
	0x02, 0x05, 0x78, /* STORE16 1400 */
	0x11, /* SUB */
	0x20, /* DISPLAY */
	0x00
};

static char multiplication[] = {
	0x01, 0x0a, /* STORE 10 */
	0x01, 0x14, /* STORE 20 */
	0x12, /* MUL */
	0x20, /* DISPLAY */
	0x00
};

static char multiplication_with_first_16bit_operand[] = {
	0x02, 0x05, 0x39, /* STORE16 1337 */
	0x01, 0x02, /* STORE 2 */
	0x12, /* MUL */
	0x20, /* DISPLAY */
	0x00
};

static char multiplication_with_second_16bit_operand[] = {
	0x01, 0x02, /* STORE 2 */
	0x02, 0x05, 0x39, /* STORE16 1337 */
	0x12, /* MUL */
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

static void test_addition_with_16bit_operand_both(void)
{
	vm_t *vm = vm_init(addition_with_16bit_operand_both);
	vm_run(vm);
	vm_destroy(vm);
}

static void test_subtraction(void)
{
	vm_t *vm = vm_init(subtraction);
	vm_run(vm);
	vm_destroy(vm);
}

static void test_subtraction_with_first_16bit_operand(void)
{
	vm_t *vm = vm_init(subtraction_with_first_16bit_operand);
	vm_run(vm);
	vm_destroy(vm);
}

static void test_subtraction_with_second_16bit_operand(void)
{
	vm_t *vm = vm_init(subtraction_with_second_16bit_operand);
	vm_run(vm);
	vm_destroy(vm);
}

static void test_subtraction_with_16bit_operand_both(void)
{
	vm_t *vm = vm_init(subtraction_with_16bit_operand_both);
	vm_run(vm);
	vm_destroy(vm);
}

static void test_multiplication(void)
{
	vm_t *vm = vm_init(multiplication);
	vm_run(vm);
	vm_destroy(vm);
}

static void test_multiplication_with_first_16bit_operand(void)
{
	vm_t *vm = vm_init(multiplication_with_first_16bit_operand);
	vm_run(vm);
	vm_destroy(vm);
}

static void test_multiplication_with_second_16bit_operand(void)
{
	vm_t *vm = vm_init(multiplication_with_second_16bit_operand);
	vm_run(vm);
	vm_destroy(vm);
}

int main(void)
{
	test_addition();
	test_addition_with_first_16bit_operand();
	test_addition_with_second_16bit_operand();
	test_addition_with_16bit_operand_both();

	test_subtraction();
	test_subtraction_with_first_16bit_operand();
	test_subtraction_with_second_16bit_operand();
	test_subtraction_with_16bit_operand_both();

	test_multiplication();
	test_multiplication_with_first_16bit_operand();
	test_multiplication_with_second_16bit_operand();

	return 0;
}
