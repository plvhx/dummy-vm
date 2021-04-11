#include "../src/insn.h"
#include "../src/vm.h"
#include <assert.h>
#include <string.h>

static unsigned char test0[] = {VM_INSN_MOVB_IMM8_TO_R3,
                                0xfa,
                                0x14,
                                VM_INSN_ADDB_IMM8_R3_TO_R1,
                                0xfa,
                                0x0a,
                                0x00};

static unsigned char test1[] = {VM_INSN_MOVB_IMM8_TO_R3,
                                0xfa,
                                0x14,
                                VM_INSN_ADDB_IMM8_R3_TO_R1,
                                0xff,
                                0x0a,
                                0x00};

static unsigned char test2[] = {VM_INSN_MOVB_IMM8_TO_R3,
                                0xff,
                                0x14,
                                VM_INSN_ADDB_IMM8_R3_TO_R1,
                                0xfa,
                                0x0a,
                                0x00};

static unsigned char test3[] = {VM_INSN_MOVB_IMM8_TO_R3,
                                0xff,
                                0x14,
                                VM_INSN_ADDB_IMM8_R3_TO_R1,
                                0xff,
                                0x0a,
                                0x00};

static unsigned char test4[] = {VM_INSN_ADDB_IMM8_R3_TO_R1, 0xfa, 0x64, 0x00};

static unsigned char test5[] = {VM_INSN_ADDB_IMM8_R3_TO_R1, 0xff, 0x64, 0x00};

static void test_addb_imm8_r3_to_r1__micro_test0(void) {
  vm_t *vm = vm_init(test0, strlen(test0));
  vm_run(vm);
  assert(VM_REGS_GET_R3_VAL(vm) == 20);
  assert(VM_REGS_GET_R1_VAL(vm) == 30);
  vm_destroy(vm);
}

static void test_addb_imm8_r3_to_r1__micro_test1(void) {
  vm_t *vm = vm_init(test1, strlen(test1));
  vm_run(vm);
  assert(VM_REGS_GET_R3_VAL(vm) == 20);
  assert(VM_REGS_GET_R1_VAL(vm) == 10);
  vm_destroy(vm);
}

static void test_addb_imm8_r3_to_r1__micro_test2(void) {
  vm_t *vm = vm_init(test2, strlen(test2));
  vm_run(vm);
  assert(VM_REGS_GET_R3_VAL(vm) == -20);
  assert(VM_REGS_GET_R1_VAL(vm) == -10);
  vm_destroy(vm);
}

static void test_addb_imm8_r3_to_r1__micro_test3(void) {
  vm_t *vm = vm_init(test3, strlen(test3));
  vm_run(vm);
  assert(VM_REGS_GET_R3_VAL(vm) == -20);
  assert(VM_REGS_GET_R1_VAL(vm) == -30);
  vm_destroy(vm);
}

static void test_addb_imm8_r3_to_r1__micro_test4(void) {
  vm_t *vm = vm_init(test4, strlen(test4));
  vm_run(vm);
  assert(!VM_REGS_GET_R3_VAL(vm));
  assert(VM_REGS_GET_R1_VAL(vm) == 100);
  vm_destroy(vm);
}

static void test_addb_imm8_r3_to_r1__micro_test5(void) {
  vm_t *vm = vm_init(test5, strlen(test5));
  vm_run(vm);
  assert(!VM_REGS_GET_R3_VAL(vm));
  assert(VM_REGS_GET_R1_VAL(vm) == -100);
  vm_destroy(vm);
}

void test_addb_imm8_r3_to_r1(void) {
  test_addb_imm8_r3_to_r1__micro_test0();
  test_addb_imm8_r3_to_r1__micro_test1();
  test_addb_imm8_r3_to_r1__micro_test2();
  test_addb_imm8_r3_to_r1__micro_test3();
  test_addb_imm8_r3_to_r1__micro_test4();
  test_addb_imm8_r3_to_r1__micro_test5();
}
