#include "../src/insn.h"
#include "../src/vm.h"
#include <assert.h>
#include <string.h>

static unsigned char test0[] = {
    VM_INSN_DIVB_IMM8_IMM8_TO_R0, 0xfa, 0x0a, 0xfa, 0x14, 0x00};

static unsigned char test1[] = {
    VM_INSN_DIVB_IMM8_IMM8_TO_R0, 0xfa, 0x0a, 0xff, 0x14, 0x00};

static unsigned char test2[] = {
    VM_INSN_DIVB_IMM8_IMM8_TO_R0, 0xff, 0x0a, 0xfa, 0x14, 0x00};

static unsigned char test3[] = {
    VM_INSN_DIVB_IMM8_IMM8_TO_R0, 0xff, 0x0a, 0xff, 0x14, 0x00};

static void test_divb_imm8_imm8_to_r0__micro_test0(void) {
  vm_t *vm = vm_init(test0, strlen(test0));
  vm_run(vm);
  assert(VM_REGS_GET_R0_VAL(vm) == 0);
  vm_destroy(vm);
}

static void test_divb_imm8_imm8_to_r0__micro_test1(void) {
  vm_t *vm = vm_init(test1, strlen(test1));
  vm_run(vm);
  assert(VM_REGS_GET_R0_VAL(vm) == 0);
  vm_destroy(vm);
}

static void test_divb_imm8_imm8_to_r0__micro_test2(void) {
  vm_t *vm = vm_init(test2, strlen(test2));
  vm_run(vm);
  assert(VM_REGS_GET_R0_VAL(vm) == 0);
  vm_destroy(vm);
}

static void test_divb_imm8_imm8_to_r0__micro_test3(void) {
  vm_t *vm = vm_init(test3, strlen(test3));
  vm_run(vm);
  assert(VM_REGS_GET_R0_VAL(vm) == 0);
  vm_destroy(vm);
}

void test_divb_imm8_imm8_to_r0(void) {
  test_divb_imm8_imm8_to_r0__micro_test0();
  test_divb_imm8_imm8_to_r0__micro_test1();
  test_divb_imm8_imm8_to_r0__micro_test2();
  test_divb_imm8_imm8_to_r0__micro_test3();
}
