#define _DEFAULT_SOURCE
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "insn.h"

static vm_ast_t *vm_ast_alloc(size_t size) {
  vm_ast_t *ret = malloc(size);
  assert(ret != NULL);
  memset(ret, 0, size);
  return ret;
}

static vm_ast_t *vm_ast_realloc(vm_ast_t *ast, size_t old_size,
                                size_t new_size) {
  assert(new_size > old_size);
  vm_ast_t *ret = realloc(ast, new_size);
  assert(ret != NULL);
  memset(ret + old_size, 0, new_size - old_size);
  return ret;
}

static size_t vm_ast_calculate_child(size_t num_child) {
  return (sizeof(vm_ast_t) - sizeof(vm_ast_t *)) +
         (sizeof(vm_ast_t *) * num_child);
}

static vm_ast_t *vm_ast_create_from_va_list(unsigned short kind_type,
                                            const void *ast_value,
                                            va_list args) {
  vm_ast_t *node = vm_ast_create(kind_type, ast_value);
  vm_ast_t *child;

  while ((child = (vm_ast_t *)va_arg(args, vm_ast_t *)) != NULL) {
    node = vm_ast_add_child(node, child);
  }

  return node;
}

vm_ast_t *vm_ast_create(unsigned short kind_type, const void *ast_value) {
  vm_ast_t *ret = vm_ast_alloc(vm_ast_calculate_child(4));

  ret->kind_type = kind_type;
  ret->num_childs = 0;
  ret->num_childs_alloc_size = 4;

  switch (ret->kind_type) {
  case VM_AST_REGISTER:
    ret->regs.name = (unsigned char *)ast_value;
    break;
  case VM_AST_MNEMONIC:
    ret->mnemonic.name = (unsigned char *)ast_value;
    break;
  case VM_AST_INTEGER_VALUE:
    ret->number.val = (unsigned char *)ast_value;
    break;
  }

  return ret;
}

vm_ast_t *vm_ast_create_multi_ex(unsigned short kind_type,
                                 const void *ast_value, ...) {
  va_list ap;
  vm_ast_t *ret;

  va_start(ap, ast_value);
  ret = vm_ast_create_from_va_list(kind_type, ast_value, ap);
  va_end(ap);

  return ret;
}

vm_ast_t *vm_ast_add_child(vm_ast_t *ast, vm_ast_t *child) {
  if (ast->num_childs >= ast->num_childs_alloc_size) {
    ast =
        vm_ast_realloc(ast, vm_ast_calculate_child(ast->num_childs_alloc_size),
                       vm_ast_calculate_child(ast->num_childs_alloc_size + 4));

    ast->num_childs_alloc_size += 4;
  }

  ast->childs[ast->num_childs++] = child;
  return ast;
}

static void vm_ast_process_ternary_addb_imm8_imm8_instruction(
    vm_ast_t *ast, FILE *file, void (*visitor)(FILE *file, int opcode)) {
  if (VM_AST_GET_NUM_CHILDS(ast) != 4) {
    return;
  }

  unsigned int is_negated;

  if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]), "r0")) {
    visitor(file, VM_INSN_ADDB_IMM8_IMM8_TO_R0);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]),
                         "r1")) {
    visitor(file, VM_INSN_ADDB_IMM8_IMM8_TO_R1);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]),
                         "r2")) {
    visitor(file, VM_INSN_ADDB_IMM8_IMM8_TO_R2);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]),
                         "r3")) {
    visitor(file, VM_INSN_ADDB_IMM8_IMM8_TO_R3);
  }

  is_negated = VM_AST_GET_NUMBER_VAL(ast->childs[2])[0] == '-' ? 0xff : 0xfa;

  visitor(file, is_negated);
  visitor(file, is_negated == 0xfa
                    ? atoi((char *)VM_AST_GET_NUMBER_VAL(ast->childs[2]))
                    : atoi((char *)VM_AST_GET_NUMBER_VAL(ast->childs[2]) + 1));

  is_negated = VM_AST_GET_NUMBER_VAL(ast->childs[3])[0] == '-' ? 0xff : 0xfa;

  visitor(file, is_negated);
  visitor(file, is_negated == 0xfa
                    ? atoi((char *)VM_AST_GET_NUMBER_VAL(ast->childs[3]))
                    : atoi((char *)VM_AST_GET_NUMBER_VAL(ast->childs[3]) + 1));
}

static void vm_ast_process_ternary_addb_imm8_regs_instruction(
    vm_ast_t *ast, FILE *file, void (*visitor)(FILE *file, int opcode)) {
  if (VM_AST_GET_NUM_CHILDS(ast) != 4) {
    return;
  }

  if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]), "r0") &&
      !strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[3]), "r0")) {
    visitor(file, VM_INSN_ADDB_IMM8_R0_TO_R0);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]),
                         "r1") &&
             !strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[3]),
                         "r0")) {
    visitor(file, VM_INSN_ADDB_IMM8_R0_TO_R1);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]),
                         "r2") &&
             !strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[3]),
                         "r0")) {
    visitor(file, VM_INSN_ADDB_IMM8_R0_TO_R2);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]),
                         "r3") &&
             !strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[3]),
                         "r0")) {
    visitor(file, VM_INSN_ADDB_IMM8_R0_TO_R3);
  }

  unsigned int is_negated =
      VM_AST_GET_NUMBER_VAL(ast->childs[2])[0] == '-' ? 0xff : 0xfa;

  visitor(file, is_negated);
  visitor(file, is_negated == 0xfa
                    ? atoi((char *)VM_AST_GET_NUMBER_VAL(ast->childs[2]))
                    : atoi((char *)VM_AST_GET_NUMBER_VAL(ast->childs[2]) + 1));
}

static void vm_ast_process_ternary_subb_imm8_imm8_instruction(
    vm_ast_t *ast, FILE *file, void (*visitor)(FILE *file, int opcode)) {
  if (VM_AST_GET_NUM_CHILDS(ast) != 4) {
    return;
  }

  unsigned int is_negated;

  if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]), "r0")) {
    visitor(file, VM_INSN_SUBB_IMM8_IMM8_TO_R0);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]),
                         "r1")) {
    visitor(file, VM_INSN_SUBB_IMM8_IMM8_TO_R1);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]),
                         "r2")) {
    visitor(file, VM_INSN_SUBB_IMM8_IMM8_TO_R2);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]),
                         "r3")) {
    visitor(file, VM_INSN_SUBB_IMM8_IMM8_TO_R3);
  }

  is_negated = VM_AST_GET_NUMBER_VAL(ast->childs[2])[0] == '-' ? 0xff : 0xfa;

  visitor(file, is_negated);
  visitor(file, is_negated == 0xfa
                    ? atoi((char *)VM_AST_GET_NUMBER_VAL(ast->childs[2]))
                    : atoi((char *)VM_AST_GET_NUMBER_VAL(ast->childs[2]) + 1));

  is_negated = VM_AST_GET_NUMBER_VAL(ast->childs[3])[0] == '-' ? 0xff : 0xfa;

  visitor(file, is_negated);
  visitor(file, is_negated == 0xfa
                    ? atoi((char *)VM_AST_GET_NUMBER_VAL(ast->childs[3]))
                    : atoi((char *)VM_AST_GET_NUMBER_VAL(ast->childs[3]) + 1));
}

static void vm_ast_process_ternary_subb_imm8_regs_instruction(
    vm_ast_t *ast, FILE *file, void (*visitor)(FILE *file, int opcode)) {
  if (VM_AST_GET_NUM_CHILDS(ast) != 4) {
    return;
  }

  if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]), "r0") &&
      !strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[3]), "r0")) {
    visitor(file, VM_INSN_SUBB_IMM8_R0_TO_R0);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]),
                         "r1") &&
             !strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[3]),
                         "r0")) {
    visitor(file, VM_INSN_SUBB_IMM8_R0_TO_R1);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]),
                         "r2") &&
             !strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[3]),
                         "r0")) {
    visitor(file, VM_INSN_SUBB_IMM8_R0_TO_R2);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]),
                         "r3") &&
             !strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[3]),
                         "r0")) {
    visitor(file, VM_INSN_SUBB_IMM8_R0_TO_R3);
  }

  unsigned int is_negated =
      VM_AST_GET_NUMBER_VAL(ast->childs[2])[0] == '-' ? 0xff : 0xfa;

  visitor(file, is_negated);
  visitor(file, is_negated == 0xfa
                    ? atoi((char *)VM_AST_GET_NUMBER_VAL(ast->childs[2]))
                    : atoi((char *)VM_AST_GET_NUMBER_VAL(ast->childs[2]) + 1));
}

static void vm_ast_process_ternary_mulb_imm8_imm8_instruction(
    vm_ast_t *ast, FILE *file, void (*visitor)(FILE *file, int opcode)) {
  if (VM_AST_GET_NUM_CHILDS(ast) != 4) {
    return;
  }

  unsigned int is_negated;

  if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]), "r0")) {
    visitor(file, VM_INSN_MULB_IMM8_IMM8_TO_R0);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]),
                         "r1")) {
    visitor(file, VM_INSN_MULB_IMM8_IMM8_TO_R1);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]),
                         "r2")) {
    visitor(file, VM_INSN_MULB_IMM8_IMM8_TO_R2);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]),
                         "r3")) {
    visitor(file, VM_INSN_MULB_IMM8_IMM8_TO_R3);
  }

  is_negated = VM_AST_GET_NUMBER_VAL(ast->childs[2])[0] == '-' ? 0xff : 0xfa;

  visitor(file, is_negated);
  visitor(file, is_negated == 0xfa
                    ? atoi((char *)VM_AST_GET_NUMBER_VAL(ast->childs[2]))
                    : atoi((char *)VM_AST_GET_NUMBER_VAL(ast->childs[2]) + 1));

  is_negated = VM_AST_GET_NUMBER_VAL(ast->childs[3])[0] == '-' ? 0xff : 0xfa;

  visitor(file, is_negated);
  visitor(file, is_negated == 0xfa
                    ? atoi((char *)VM_AST_GET_NUMBER_VAL(ast->childs[3]))
                    : atoi((char *)VM_AST_GET_NUMBER_VAL(ast->childs[3]) + 1));
}

static void vm_ast_process_ternary_mulb_imm8_regs_instruction(
    vm_ast_t *ast, FILE *file, void (*visitor)(FILE *file, int opcode)) {
  if (VM_AST_GET_NUM_CHILDS(ast) != 4) {
    return;
  }

  if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]), "r0") &&
      !strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[3]), "r0")) {
    visitor(file, VM_INSN_MULB_IMM8_R0_TO_R0);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]),
                         "r1") &&
             !strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[3]),
                         "r0")) {
    visitor(file, VM_INSN_MULB_IMM8_R0_TO_R1);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]),
                         "r2") &&
             !strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[3]),
                         "r0")) {
    visitor(file, VM_INSN_MULB_IMM8_R0_TO_R2);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]),
                         "r3") &&
             !strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[3]),
                         "r0")) {
    visitor(file, VM_INSN_MULB_IMM8_R0_TO_R3);
  }

  unsigned int is_negated =
      VM_AST_GET_NUMBER_VAL(ast->childs[2])[0] == '-' ? 0xff : 0xfa;

  visitor(file, is_negated);
  visitor(file, is_negated == 0xfa
                    ? atoi((char *)VM_AST_GET_NUMBER_VAL(ast->childs[2]))
                    : atoi((char *)VM_AST_GET_NUMBER_VAL(ast->childs[2]) + 1));
}

static void vm_ast_process_ternary_divb_imm8_imm8_instruction(
    vm_ast_t *ast, FILE *file, void (*visitor)(FILE *file, int opcode)) {
  if (VM_AST_GET_NUM_CHILDS(ast) != 4) {
    return;
  }

  unsigned int is_negated;

  if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]), "r0")) {
    visitor(file, VM_INSN_DIVB_IMM8_IMM8_TO_R0);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]),
                         "r1")) {
    visitor(file, VM_INSN_DIVB_IMM8_IMM8_TO_R1);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]),
                         "r2")) {
    visitor(file, VM_INSN_DIVB_IMM8_IMM8_TO_R2);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]),
                         "r3")) {
    visitor(file, VM_INSN_DIVB_IMM8_IMM8_TO_R3);
  }

  is_negated = VM_AST_GET_NUMBER_VAL(ast->childs[2])[0] == '-' ? 0xff : 0xfa;

  visitor(file, is_negated);
  visitor(file, is_negated == 0xfa
                    ? atoi((char *)VM_AST_GET_NUMBER_VAL(ast->childs[2]))
                    : atoi((char *)VM_AST_GET_NUMBER_VAL(ast->childs[2]) + 1));

  is_negated = VM_AST_GET_NUMBER_VAL(ast->childs[3])[0] == '-' ? 0xff : 0xfa;

  visitor(file, is_negated);
  visitor(file, is_negated == 0xfa
                    ? atoi((char *)VM_AST_GET_NUMBER_VAL(ast->childs[3]))
                    : atoi((char *)VM_AST_GET_NUMBER_VAL(ast->childs[3]) + 1));
}

static void vm_ast_process_binary_movb_imm8_to_regs_instruction(
    vm_ast_t *ast, FILE *file, void (*visitor)(FILE *file, int opcode)) {
  if (VM_AST_GET_NUM_CHILDS(ast) != 3) {
    return;
  }

  if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]), "r0")) {
    visitor(file, VM_INSN_MOVB_IMM8_TO_R0);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]),
                         "r1")) {
    visitor(file, VM_INSN_MOVB_IMM8_TO_R1);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]),
                         "r2")) {
    visitor(file, VM_INSN_MOVB_IMM8_TO_R2);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]),
                         "r3")) {
    visitor(file, VM_INSN_MOVB_IMM8_TO_R3);
  }

  unsigned int is_negated =
      VM_AST_GET_NUMBER_VAL(ast->childs[2])[0] == '-' ? 0xff : 0xfa;

  visitor(file, is_negated);
  visitor(file, is_negated == 0xfa
                    ? atoi((char *)VM_AST_GET_NUMBER_VAL(ast->childs[2]))
                    : atoi((char *)VM_AST_GET_NUMBER_VAL(ast->childs[2]) + 1));
}

static void vm_ast_process_binary_movb_regs_to_r0_instruction(
    vm_ast_t *ast, FILE *file, void (*visitor)(FILE *file, int opcode)) {
  if (VM_AST_GET_NUM_CHILDS(ast) != 3) {
    return;
  }

  if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[2]), "r0")) {
    visitor(file, VM_INSN_MOVB_R0_TO_R0);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[2]),
                         "r1")) {
    visitor(file, VM_INSN_MOVB_R1_TO_R0);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[2]),
                         "r2")) {
    visitor(file, VM_INSN_MOVB_R2_TO_R0);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[2]),
                         "r3")) {
    visitor(file, VM_INSN_MOVB_R3_TO_R0);
  }
}

static void vm_ast_process_binary_movb_regs_to_r1_instruction(
    vm_ast_t *ast, FILE *file, void (*visitor)(FILE *file, int opcode)) {
  if (VM_AST_GET_NUM_CHILDS(ast) != 3) {
    return;
  }

  if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[2]), "r0")) {
    visitor(file, VM_INSN_MOVB_R0_TO_R1);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[2]),
                         "r1")) {
    visitor(file, VM_INSN_MOVB_R1_TO_R1);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[2]),
                         "r2")) {
    visitor(file, VM_INSN_MOVB_R2_TO_R1);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[2]),
                         "r3")) {
    visitor(file, VM_INSN_MOVB_R3_TO_R1);
  }
}

static void vm_ast_process_binary_movb_regs_to_r2_instruction(
    vm_ast_t *ast, FILE *file, void (*visitor)(FILE *file, int opcode)) {
  if (VM_AST_GET_NUM_CHILDS(ast) != 3) {
    return;
  }

  if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[2]), "r0")) {
    visitor(file, VM_INSN_MOVB_R0_TO_R2);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[2]),
                         "r1")) {
    visitor(file, VM_INSN_MOVB_R1_TO_R2);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[2]),
                         "r2")) {
    visitor(file, VM_INSN_MOVB_R2_TO_R2);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[2]),
                         "r3")) {
    visitor(file, VM_INSN_MOVB_R3_TO_R2);
  }
}

static void vm_ast_process_binary_movb_regs_to_r3_instruction(
    vm_ast_t *ast, FILE *file, void (*visitor)(FILE *file, int opcode)) {
  if (VM_AST_GET_NUM_CHILDS(ast) != 3) {
    return;
  }

  if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[2]), "r0")) {
    visitor(file, VM_INSN_MOVB_R0_TO_R3);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[2]),
                         "r1")) {
    visitor(file, VM_INSN_MOVB_R1_TO_R3);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[2]),
                         "r2")) {
    visitor(file, VM_INSN_MOVB_R2_TO_R3);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[2]),
                         "r3")) {
    visitor(file, VM_INSN_MOVB_R3_TO_R3);
  }
}

static void vm_ast_process_unary_print_imm8_instruction(
    vm_ast_t *ast, FILE *file, void (*visitor)(FILE *file, int opcode)) {
  if (VM_AST_GET_NUM_CHILDS(ast) != 2) {
    return;
  }

  visitor(file, VM_INSN_PRINT_IMM8);

  unsigned int is_negated =
      VM_AST_GET_NUMBER_VAL(ast->childs[1])[0] == '-' ? 0xff : 0xfa;

  visitor(file, is_negated);
  visitor(file, is_negated == 0xfa
                    ? atoi((char *)VM_AST_GET_NUMBER_VAL(ast->childs[1]))
                    : atoi((char *)VM_AST_GET_NUMBER_VAL(ast->childs[1]) + 1));
}

static void vm_ast_process_unary_print_regs_instruction(
    vm_ast_t *ast, FILE *file, void (*visitor)(FILE *file, int opcode)) {
  if (VM_AST_GET_NUM_CHILDS(ast) != 2) {
    return;
  }

  if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]), "r0")) {
    visitor(file, VM_INSN_PRINT_R0);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]),
                         "r1")) {
    visitor(file, VM_INSN_PRINT_R1);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]),
                         "r2")) {
    visitor(file, VM_INSN_PRINT_R2);
  } else if (!strcasecmp((const char *)VM_AST_GET_REGS_NAME(ast->childs[1]),
                         "r3")) {
    visitor(file, VM_INSN_PRINT_R3);
  }
}

static void vm_ast_process_instruction_line(vm_ast_t *ast, FILE *file,
                                            void (*visitor)(FILE *file,
                                                            int opcode)) {
  unsigned int skipped_index = VM_AST_GET_NUM_CHILDS(ast);

  if (!strcasecmp((char *)ast->childs[0]->mnemonic.name, "addb") &&
      ast->childs[1]->kind_type == VM_AST_REGISTER &&
      ast->childs[2]->kind_type == VM_AST_INTEGER_VALUE &&
      ast->childs[3]->kind_type == VM_AST_INTEGER_VALUE) {
    vm_ast_process_ternary_addb_imm8_imm8_instruction(ast, file, visitor);
  } else if (!strcasecmp((char *)ast->childs[0]->mnemonic.name, "subb") &&
             ast->childs[1]->kind_type == VM_AST_REGISTER &&
             ast->childs[2]->kind_type == VM_AST_INTEGER_VALUE &&
             ast->childs[3]->kind_type == VM_AST_INTEGER_VALUE) {
    vm_ast_process_ternary_subb_imm8_imm8_instruction(ast, file, visitor);
  } else if (!strcasecmp((char *)ast->childs[0]->mnemonic.name, "mulb") &&
             ast->childs[1]->kind_type == VM_AST_REGISTER &&
             ast->childs[2]->kind_type == VM_AST_INTEGER_VALUE &&
             ast->childs[3]->kind_type == VM_AST_INTEGER_VALUE) {
    vm_ast_process_ternary_mulb_imm8_imm8_instruction(ast, file, visitor);
  } else if (!strcasecmp((char *)ast->childs[0]->mnemonic.name, "divb") &&
             ast->childs[1]->kind_type == VM_AST_REGISTER &&
             ast->childs[2]->kind_type == VM_AST_INTEGER_VALUE &&
             ast->childs[3]->kind_type == VM_AST_INTEGER_VALUE) {
    vm_ast_process_ternary_divb_imm8_imm8_instruction(ast, file, visitor);
  }

  if (!strcasecmp((char *)ast->childs[0]->mnemonic.name, "addb") &&
      ast->childs[1]->kind_type == VM_AST_REGISTER &&
      ast->childs[2]->kind_type == VM_AST_INTEGER_VALUE &&
      ast->childs[3]->kind_type == VM_AST_REGISTER) {
    vm_ast_process_ternary_addb_imm8_regs_instruction(ast, file, visitor);
  } else if (!strcasecmp((char *)ast->childs[0]->mnemonic.name, "subb") &&
             ast->childs[1]->kind_type == VM_AST_REGISTER &&
             ast->childs[2]->kind_type == VM_AST_INTEGER_VALUE &&
             ast->childs[3]->kind_type == VM_AST_REGISTER) {
    vm_ast_process_ternary_subb_imm8_regs_instruction(ast, file, visitor);
  } else if (!strcasecmp((char *)ast->childs[0]->mnemonic.name, "mulb") &&
             ast->childs[1]->kind_type == VM_AST_REGISTER &&
             ast->childs[2]->kind_type == VM_AST_INTEGER_VALUE &&
             ast->childs[3]->kind_type == VM_AST_REGISTER) {
    vm_ast_process_ternary_mulb_imm8_regs_instruction(ast, file, visitor);
  }

  // process 'movb' imm8 to general-purpose register
  if (!strcasecmp((char *)ast->childs[0]->mnemonic.name, "movb") &&
      ast->childs[1]->kind_type == VM_AST_REGISTER &&
      ast->childs[2]->kind_type == VM_AST_INTEGER_VALUE) {
    vm_ast_process_binary_movb_imm8_to_regs_instruction(ast, file, visitor);
    // process 'movb' general-purpose register to r0
  } else if (!strcasecmp((char *)ast->childs[0]->mnemonic.name, "movb") &&
             !strcasecmp((char *)ast->childs[1]->regs.name, "r0") &&
             ast->childs[2]->kind_type == VM_AST_REGISTER) {
    vm_ast_process_binary_movb_regs_to_r0_instruction(ast, file, visitor);
    // process 'movb' general-purpose register to r1
  } else if (!strcasecmp((char *)ast->childs[0]->mnemonic.name, "movb") &&
             !strcasecmp((char *)ast->childs[1]->regs.name, "r1") &&
             ast->childs[2]->kind_type == VM_AST_REGISTER) {
    vm_ast_process_binary_movb_regs_to_r1_instruction(ast, file, visitor);
    // process 'movb' general-purpose register to r2
  } else if (!strcasecmp((char *)ast->childs[0]->mnemonic.name, "movb") &&
             !strcasecmp((char *)ast->childs[1]->regs.name, "r2") &&
             ast->childs[2]->kind_type == VM_AST_REGISTER) {
    vm_ast_process_binary_movb_regs_to_r2_instruction(ast, file, visitor);
    // process 'movb' general-purpose register to r3
  } else if (!strcasecmp((char *)ast->childs[0]->mnemonic.name, "movb") &&
             !strcasecmp((char *)ast->childs[1]->regs.name, "r3") &&
             ast->childs[2]->kind_type == VM_AST_REGISTER) {
    vm_ast_process_binary_movb_regs_to_r3_instruction(ast, file, visitor);
  }

  // process unary 'print' imm8
  if (!strcasecmp((char *)ast->childs[0]->mnemonic.name, "print") &&
      ast->childs[1]->kind_type == VM_AST_INTEGER_VALUE) {
    vm_ast_process_unary_print_imm8_instruction(ast, file, visitor);
    // process unary 'print' regs
  } else if (!strcasecmp((char *)ast->childs[0]->mnemonic.name, "print") &&
             ast->childs[1]->kind_type == VM_AST_REGISTER) {
    vm_ast_process_unary_print_regs_instruction(ast, file, visitor);
  }
}

void vm_ast_traverse(vm_ast_t *ast, FILE *file,
                     void (*visitor)(FILE *file, int opcode)) {
  if (ast == NULL) {
    return;
  }

  if (ast->kind_type == VM_AST_INSTRUCTION_LINE) {
    vm_ast_process_instruction_line(ast, file, visitor);
  }

  for (int i = 0; i < ast->num_childs; i++) {
    vm_ast_traverse(ast->childs[i], file, visitor);
  }
}
