#include <assert.h>
#include <string.h>
#include "../src/insn.h"
#include "../src/vm.h"

static unsigned char test0[] = {VM_INSN_MOVB_IMM8_TO_R1, 0xfa, 0x0a, 0x00};

static unsigned char test1[] = {VM_INSN_MOVB_IMM8_TO_R1, 0xff, 0x0a, 0x00};

static void test_movb_imm8_to_r1__micro_test0(void) {
  vm_t *vm = vm_init(test0, strlen(test0));
  vm_run(vm);
  assert(VM_REGS_GET_R1_VAL(vm) == 10);
  vm_destroy(vm);
}

static void test_movb_imm8_to_r1__micro_test1(void) {
  vm_t *vm = vm_init(test1, strlen(test1));
  vm_run(vm);
  assert(VM_REGS_GET_R1_VAL(vm) == -10);
  vm_destroy(vm);
}

void test_movb_imm8_to_r1(void) {
  test_movb_imm8_to_r1__micro_test0();
  test_movb_imm8_to_r1__micro_test1();
}
