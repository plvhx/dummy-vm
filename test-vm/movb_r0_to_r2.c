#include <assert.h>
#include <string.h>
#include "../src/insn.h"
#include "../src/vm.h"

static unsigned char test0[] = {VM_INSN_MOVB_IMM8_TO_R0, 0xfa, 0x0a,
                                VM_INSN_MOVB_R0_TO_R2, 0x00};

static unsigned char test1[] = {VM_INSN_MOVB_IMM8_TO_R0, 0xff, 0x0a,
                                VM_INSN_MOVB_R0_TO_R2, 0x00};

static void test_movb_r0_to_r2__micro_test0(void) {
  vm_t *vm = vm_init(test0, strlen(test0));
  vm_run(vm);
  assert(VM_REGS_GET_R0_VAL(vm) == 10);
  assert(VM_REGS_GET_R2_VAL(vm) == 10);
  vm_destroy(vm);
}

static void test_movb_r0_to_r2__micro_test1(void) {
  vm_t *vm = vm_init(test1, strlen(test1));
  vm_run(vm);
  assert(VM_REGS_GET_R0_VAL(vm) == -10);
  assert(VM_REGS_GET_R2_VAL(vm) == -10);
  vm_destroy(vm);
}

void test_movb_r0_to_r2(void) {
  test_movb_r0_to_r2__micro_test0();
  test_movb_r0_to_r2__micro_test1();
}
