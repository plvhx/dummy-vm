#include "../src/ast.h"
#include <stdio.h>
#include <string.h>

static void vm_ast_compilation_visitor_callback(FILE *file, int opcode) {
  fputc(opcode, file);
}

void test_ast_movb_imm8_to_r1(void) {
  FILE *fp;
  vm_ast_t *ast;
  unsigned char opcode[4];
  int oplen = 0;

  if ((fp = tmpfile()) == NULL) {
    return;
  }

  memset(opcode, 0, 4);

  ast = vm_ast_create_single_ex_call(VM_AST_ROOT, NULL);
  ast = vm_ast_add_child(
      ast, vm_ast_create_multi_ex_call(
               VM_AST_INSTRUCTION_LINE, NULL,
               vm_ast_create_single_ex_call(VM_AST_MNEMONIC, "movb"),
               vm_ast_create_single_ex_call(VM_AST_REGISTER, "r1"),
               vm_ast_create_single_ex_call(VM_AST_INTEGER_VALUE, "10"), NULL));

  vm_ast_traverse(ast, fp, vm_ast_compilation_visitor_callback);
  rewind(fp);

  while (!feof(fp)) {
    opcode[oplen++] = fgetc(fp);
  }

  if (memcmp(opcode, "\x91\xfa\x0a", 3)) {
    fprintf(stderr, "[test_ast_movb_imm8_to_r1] Failed.\n");
    goto cleanup;
  }

  fprintf(stdout, "[test_ast_movb_imm8_to_r1] Success.\n");

cleanup:
  vm_ast_dtor(ast);
  fclose(fp);
  return;
}
