#include "test_vm.h"
#include <stdio.h>

static void test_movb_imm8_to_regs(void) {
  test_movb_imm8_to_r0();
  test_movb_imm8_to_r1();
  test_movb_imm8_to_r2();
  test_movb_imm8_to_r3();
}

static void test_movb_regs_to_r0(void) {
  test_movb_r0_to_r0();
  test_movb_r1_to_r0();
  test_movb_r2_to_r0();
  test_movb_r3_to_r0();
}

static void test_movb_regs_to_r1(void) {
  test_movb_r0_to_r1();
  test_movb_r1_to_r1();
  test_movb_r2_to_r1();
  test_movb_r3_to_r1();
}

static void test_movb_regs_to_r2(void) {
  test_movb_r0_to_r2();
  test_movb_r1_to_r2();
  test_movb_r2_to_r2();
  test_movb_r3_to_r2();
}

static void test_movb_regs_to_r3(void) {
  test_movb_r0_to_r3();
  test_movb_r1_to_r3();
  test_movb_r2_to_r3();
  test_movb_r3_to_r3();
}

static void test_addb_imm8_imm8_to_regs(void) {
  test_addb_imm8_imm8_to_r0();
  test_addb_imm8_imm8_to_r1();
  test_addb_imm8_imm8_to_r2();
  test_addb_imm8_imm8_to_r3();
}

static void test_subb_imm8_imm8_to_regs(void) {
  test_subb_imm8_imm8_to_r0();
  test_subb_imm8_imm8_to_r1();
  test_subb_imm8_imm8_to_r2();
  test_subb_imm8_imm8_to_r3();
}

static void test_mulb_imm8_imm8_to_regs(void) {
  test_mulb_imm8_imm8_to_r0();
  test_mulb_imm8_imm8_to_r1();
  test_mulb_imm8_imm8_to_r2();
  test_mulb_imm8_imm8_to_r3();
}

static void test_divb_imm8_imm8_to_regs(void) {
  test_divb_imm8_imm8_to_r0();
  test_divb_imm8_imm8_to_r1();
  test_divb_imm8_imm8_to_r2();
  test_divb_imm8_imm8_to_r3();
}

static void test_addb_imm8_r0_to_regs(void) {
  test_addb_imm8_r0_to_r0();
  test_addb_imm8_r0_to_r1();
  test_addb_imm8_r0_to_r2();
  test_addb_imm8_r0_to_r3();
}

static void test_subb_imm8_r0_to_regs(void) {
  test_subb_imm8_r0_to_r0();
  test_subb_imm8_r0_to_r1();
  test_subb_imm8_r0_to_r2();
  test_subb_imm8_r0_to_r3();
}

static void test_mulb_imm8_r0_to_regs(void) {
  test_mulb_imm8_r0_to_r0();
  test_mulb_imm8_r0_to_r1();
  test_mulb_imm8_r0_to_r2();
  test_mulb_imm8_r0_to_r3();
}

static void test_divb_imm8_r0_to_regs(void) {
  test_divb_imm8_r0_to_r0();
  test_divb_imm8_r0_to_r1();
  test_divb_imm8_r0_to_r2();
  test_divb_imm8_r0_to_r3();
}

static void test_addb_imm8_r1_to_regs(void) {
  test_addb_imm8_r1_to_r0();
  test_addb_imm8_r1_to_r1();
  test_addb_imm8_r1_to_r2();
  test_addb_imm8_r1_to_r3();
}

static void test_subb_imm8_r1_to_regs(void) {
  test_subb_imm8_r1_to_r0();
  test_subb_imm8_r1_to_r1();
  test_subb_imm8_r1_to_r2();
  test_subb_imm8_r1_to_r3();
}

static void test_mulb_imm8_r1_to_regs(void) {
  test_mulb_imm8_r1_to_r0();
  test_mulb_imm8_r1_to_r1();
  test_mulb_imm8_r1_to_r2();
  test_mulb_imm8_r1_to_r3();
}

static void test_divb_imm8_r1_to_regs(void) {
  test_divb_imm8_r1_to_r0();
  test_divb_imm8_r1_to_r1();
  test_divb_imm8_r1_to_r2();
  test_divb_imm8_r1_to_r3();
}

int main(void) {
  test_movb_imm8_to_regs();

  test_movb_regs_to_r0();
  test_movb_regs_to_r1();
  test_movb_regs_to_r2();
  test_movb_regs_to_r3();

  test_addb_imm8_imm8_to_regs();
  test_subb_imm8_imm8_to_regs();
  test_mulb_imm8_imm8_to_regs();
  test_divb_imm8_imm8_to_regs();

  test_addb_imm8_r0_to_regs();
  test_subb_imm8_r0_to_regs();
  test_mulb_imm8_r0_to_regs();
  test_divb_imm8_r0_to_regs();

  test_addb_imm8_r1_to_regs();
  test_subb_imm8_r1_to_regs();
  test_mulb_imm8_r1_to_regs();
  test_divb_imm8_r1_to_regs();

  printf("All tests passed.\n");
  return 0;
}
