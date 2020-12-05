#include <assert.h>

#ifdef DEBUG
# include <stdio.h>
#endif

#include "src/insn.h"
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

static char imm8_to_r0[] = {
	VM_INSN_MOVB_IMM8_TO_R0, 0x20, /* movb 32, r0 */
	0x00
};

static char imm8_to_r1[] = {
	VM_INSN_MOVB_IMM8_TO_R1, 0x20, /* movb 32, r1 */
	0x00
};

static char imm8_to_r2[] = {
	VM_INSN_MOVB_IMM8_TO_R2, 0x20, /* movb 32, r2 */
	0x00
};

static char imm8_to_r3[] = {
	VM_INSN_MOVB_IMM8_TO_R3, 0x20, /* movb 32, r3 */
	0x00
};

static char r0_to_r0[] = {
	VM_INSN_MOVB_IMM8_TO_R0, 0x20, /* movb 32, r0 */
	VM_INSN_MOVB_R0_TO_R0, /* movb r0, r0 */
	0x00
};

static char r1_to_r0[] = {
	VM_INSN_MOVB_IMM8_TO_R1, 0x20, /* movb 32, r1 */
	VM_INSN_MOVB_R1_TO_R0, /* movb r1, r0 */
	0x00
};

static char r2_to_r0[] = {
	VM_INSN_MOVB_IMM8_TO_R2, 0x20, /* movb 32, r2 */
	VM_INSN_MOVB_R2_TO_R0, /* movb r2, r0 */
	0x00
};

static char r3_to_r0[] = {
	VM_INSN_MOVB_IMM8_TO_R3, 0x20, /* movb 32, r3 */
	VM_INSN_MOVB_R3_TO_R0, /* movb r3, r0 */
	0x00
};

static char r0_to_r1[] = {
	VM_INSN_MOVB_IMM8_TO_R0, 0x20, /* movb 32, r0 */
	VM_INSN_MOVB_R0_TO_R1, /* movb r0, r1 */
	0x00
};

static char r1_to_r1[] = {
	VM_INSN_MOVB_IMM8_TO_R1, 0x20, /* movb 32, r1 */
	VM_INSN_MOVB_R1_TO_R1, /* movb r1, r1 */
	0x00
};

static char r2_to_r1[] = {
	VM_INSN_MOVB_IMM8_TO_R2, 0x20, /* movb 32, r2 */
	VM_INSN_MOVB_R2_TO_R1, /* movb r2, r1 */
	0x00
};

static char r3_to_r1[] = {
	VM_INSN_MOVB_IMM8_TO_R3, 0x20, /* movb 32, r3 */
	VM_INSN_MOVB_R3_TO_R1, /* movb r3, r1 */
	0x00
};

static char r0_to_r2[] = {
	VM_INSN_MOVB_IMM8_TO_R0, 0x20, /* movb 32, r0 */
	VM_INSN_MOVB_R0_TO_R2, /* movb r0, r2 */
	0x00
};

static char r1_to_r2[] = {
	VM_INSN_MOVB_IMM8_TO_R1, 0x20, /* movb 32, r1 */
	VM_INSN_MOVB_R1_TO_R2, /* movb r1, r2 */
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

static void test_imm8_to_r0(void)
{
	vm_t *vm = vm_init(imm8_to_r0);
	vm_run(vm);
	assert(VM_REGS_GET_GP_R0(vm) == 0x20);
#ifdef DEBUG
	printf("r0: %d\n", VM_REGS_GET_GP_R0(vm));
#endif
	vm_destroy(vm);
}

static void test_imm8_to_r1(void)
{
	vm_t *vm = vm_init(imm8_to_r1);
	vm_run(vm);
	assert(VM_REGS_GET_GP_R1(vm) == 0x20);
#ifdef DEBUG
	printf("r1: %d\n", VM_REGS_GET_GP_R1(vm));
#endif
	vm_destroy(vm);
}

static void test_imm8_to_r2(void)
{
	vm_t *vm = vm_init(imm8_to_r2);
	vm_run(vm);
	assert(VM_REGS_GET_GP_R2(vm) == 0x20);
#ifdef DEBUG
	printf("r2: %d\n", VM_REGS_GET_GP_R2(vm));
#endif
	vm_destroy(vm);
}

static void test_imm8_to_r3(void)
{
	vm_t *vm = vm_init(imm8_to_r3);
	vm_run(vm);
	assert(VM_REGS_GET_GP_R3(vm) == 0x20);
#ifdef DEBUG
	printf("r3: %d\n", VM_REGS_GET_GP_R3(vm));
#endif
	vm_destroy(vm);
}

static void test_r0_to_r0(void)
{
	vm_t *vm = vm_init(r0_to_r0);
	vm_run(vm);
	assert(VM_REGS_GET_GP_R0(vm) == 0x20);
#ifdef DEBUG
	printf("r0: %d\n", VM_REGS_GET_GP_R0(vm));
#endif
	vm_destroy(vm);
}

static void test_r1_to_r0(void)
{
	vm_t *vm = vm_init(r1_to_r0);
	vm_run(vm);
	assert(VM_REGS_GET_GP_R1(vm) == 0x20);
	assert(VM_REGS_GET_GP_R0(vm) == 0x20);
#ifdef DEBUG
	printf("r1: %d, r0: %d\n", VM_REGS_GET_GP_R1(vm), VM_REGS_GET_GP_R0(vm));
#endif
	vm_destroy(vm);
}

static void test_r2_to_r0(void)
{
	vm_t *vm = vm_init(r2_to_r0);
	vm_run(vm);
	assert(VM_REGS_GET_GP_R2(vm) == 0x20);
	assert(VM_REGS_GET_GP_R0(vm) == 0x20);
#ifdef DEBUG
	printf("r2: %d, r0: %d\n", VM_REGS_GET_GP_R2(vm), VM_REGS_GET_GP_R0(vm));
#endif
	vm_destroy(vm);
}

static void test_r3_to_r0(void)
{
	vm_t *vm = vm_init(r3_to_r0);
	vm_run(vm);
	assert(VM_REGS_GET_GP_R3(vm) == 0x20);
	assert(VM_REGS_GET_GP_R0(vm) == 0x20);
#ifdef DEBUG
	printf("r3: %d, r0: %d\n", VM_REGS_GET_GP_R3(vm), VM_REGS_GET_GP_R0(vm));
#endif
	vm_destroy(vm);
}

static void test_r0_to_r1(void)
{
	vm_t *vm = vm_init(r0_to_r1);
	vm_run(vm);
	assert(VM_REGS_GET_GP_R0(vm) == 0x20);
	assert(VM_REGS_GET_GP_R1(vm) == 0x20);
#ifdef DEBUG
	printf("r0: %d, r1: %d\n", VM_REGS_GET_GP_R0(vm), VM_REGS_GET_GP_R1(vm));
#endif
	vm_destroy(vm);
}

static void test_r1_to_r1(void)
{
	vm_t *vm = vm_init(r1_to_r1);
	vm_run(vm);
	assert(VM_REGS_GET_GP_R1(vm) == 0x20);
#ifdef DEBUG
	printf("r1: %d\n", VM_REGS_GET_GP_R1(vm));
#endif
	vm_destroy(vm);
}

static void test_r2_to_r1(void)
{
	vm_t *vm = vm_init(r2_to_r1);
	vm_run(vm);
	assert(VM_REGS_GET_GP_R2(vm) == 0x20);
	assert(VM_REGS_GET_GP_R1(vm) == 0x20);
#ifdef DEBUG
	printf("r2: %d, r1: %d\n", VM_REGS_GET_GP_R2(vm), VM_REGS_GET_GP_R1(vm));
#endif
	vm_destroy(vm);
}

static void test_r3_to_r1(void)
{
	vm_t *vm = vm_init(r3_to_r1);
	vm_run(vm);
	assert(VM_REGS_GET_GP_R3(vm) == 0x20);
	assert(VM_REGS_GET_GP_R1(vm) == 0x20);
#ifdef DEBUG
	printf("r3: %d, r1: %d\n", VM_REGS_GET_GP_R3(vm), VM_REGS_GET_GP_R1(vm));
#endif
	vm_destroy(vm);
}

static void test_r0_to_r2(void)
{
	vm_t *vm = vm_init(r0_to_r2);
	vm_run(vm);
	assert(VM_REGS_GET_GP_R0(vm) == 0x20);
	assert(VM_REGS_GET_GP_R2(vm) == 0x20);
#ifdef DEBUG
	printf("r0: %d, r2: %d\n", VM_REGS_GET_GP_R0(vm), VM_REGS_GET_GP_R2(vm));
#endif
	vm_destroy(vm);
}

static void test_r1_to_r2(void)
{
	vm_t *vm = vm_init(r1_to_r2);
	vm_run(vm);
	assert(VM_REGS_GET_GP_R1(vm) == 0x20);
	assert(VM_REGS_GET_GP_R2(vm) == 0x20);
#ifdef DEBUG
	printf("r1: %d, r2: %d\n", VM_REGS_GET_GP_R1(vm), VM_REGS_GET_GP_R2(vm));
#endif
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

	// imm8 -> gp reg.
	test_imm8_to_r0();
	test_imm8_to_r1();
	test_imm8_to_r2();
	test_imm8_to_r3();

	// gp reg -> r0
	test_r0_to_r0();
	test_r1_to_r0();
	test_r2_to_r0();
	test_r3_to_r0();

	// gp reg -> r1
	test_r0_to_r1();
	test_r1_to_r1();
	test_r2_to_r1();
	test_r3_to_r1();

	// gp reg -> r2
	test_r0_to_r2();
	test_r1_to_r2();

	return 0;
}
