#include "test_ast.h"
#include <stdio.h>

static void test_ast_movb_imm8_to_regs(void) {
  test_ast_movb_imm8_to_r0();
  test_ast_movb_imm8_to_r1();
  test_ast_movb_imm8_to_r2();
}

int main(void) {
  test_ast_movb_imm8_to_regs();
  return 0;
}
