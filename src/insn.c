#include "insn.h"
#include "util.h"
#include "value.h"
#include "vm.h"
#include <stdio.h>

static unsigned short vm_insn_read_byte(vm_t *vm) {
  return (unsigned short)(vm->buf[++vm->ip] & 0xff);
}

static unsigned short vm_insn_read_word(vm_t *vm) {
  unsigned short msb = (vm->buf[++vm->ip] & 0xff) << 8;
  unsigned short lsb = (vm->buf[++vm->ip] & 0xff);
  return (msb | lsb);
}

void vm_insn_movb_imm8_to_r0(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_IMM8_TO_R0);
  vm->regs->gp->r0->is_negative = vm_insn_read_byte(vm) == 0xff ? 1 : 0;
  vm->regs->gp->r0->val = vm_insn_read_byte(vm);
}

void vm_insn_movb_imm8_to_r1(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_IMM8_TO_R1);
  vm->regs->gp->r1->is_negative = vm_insn_read_byte(vm) == 0xff ? 1 : 0;
  vm->regs->gp->r1->val = vm_insn_read_byte(vm);
}

void vm_insn_movb_imm8_to_r2(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_IMM8_TO_R2);
  vm->regs->gp->r2->is_negative = vm_insn_read_byte(vm) == 0xff ? 1 : 0;
  vm->regs->gp->r2->val = vm_insn_read_byte(vm);
}

void vm_insn_movb_imm8_to_r3(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_IMM8_TO_R3);
  vm->regs->gp->r3->is_negative = vm_insn_read_byte(vm) == 0xff ? 1 : 0;
  vm->regs->gp->r3->val = vm_insn_read_byte(vm);
}

void vm_insn_movb_r0_to_r0(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_R0_TO_R0);
}

void vm_insn_movb_r1_to_r0(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_R1_TO_R0);
  vm->regs->gp->r0->is_negative = vm->regs->gp->r1->is_negative;
  vm->regs->gp->r0->val = VM_ALIGN_TO_BYTE(vm->regs->gp->r1->val);
}

void vm_insn_movb_r2_to_r0(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_R2_TO_R0);
  vm->regs->gp->r0->is_negative = vm->regs->gp->r2->is_negative;
  vm->regs->gp->r0->val = VM_ALIGN_TO_BYTE(vm->regs->gp->r2->val);
}

void vm_insn_movb_r3_to_r0(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_R3_TO_R0);
  vm->regs->gp->r0->is_negative = vm->regs->gp->r3->is_negative;
  vm->regs->gp->r0->val = VM_ALIGN_TO_BYTE(vm->regs->gp->r3->val);
}

void vm_insn_movb_r0_to_r1(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_R0_TO_R1);
  vm->regs->gp->r1->is_negative = vm->regs->gp->r0->is_negative;
  vm->regs->gp->r1->val = VM_ALIGN_TO_BYTE(vm->regs->gp->r0->val);
}

void vm_insn_movb_r1_to_r1(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_R1_TO_R1);
}

void vm_insn_movb_r2_to_r1(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_R2_TO_R1);
  vm->regs->gp->r1->is_negative = vm->regs->gp->r2->is_negative;
  vm->regs->gp->r1->val = VM_ALIGN_TO_BYTE(vm->regs->gp->r2->val);
}

void vm_insn_movb_r3_to_r1(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_R3_TO_R1);
  vm->regs->gp->r1->is_negative = vm->regs->gp->r3->is_negative;
  vm->regs->gp->r1->val = VM_ALIGN_TO_BYTE(vm->regs->gp->r3->val);
}

void vm_insn_movb_r0_to_r2(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_R0_TO_R2);
  vm->regs->gp->r2->is_negative = vm->regs->gp->r0->is_negative;
  vm->regs->gp->r2->val = VM_ALIGN_TO_BYTE(vm->regs->gp->r0->val);
}

void vm_insn_movb_r1_to_r2(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_R1_TO_R2);
  vm->regs->gp->r2->is_negative = vm->regs->gp->r1->is_negative;
  vm->regs->gp->r2->val = VM_ALIGN_TO_BYTE(vm->regs->gp->r1->val);
}

void vm_insn_movb_r2_to_r2(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_R2_TO_R2);
}

void vm_insn_movb_r3_to_r2(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_R3_TO_R2);
  vm->regs->gp->r2->is_negative = vm->regs->gp->r3->is_negative;
  vm->regs->gp->r2->val = VM_ALIGN_TO_BYTE(vm->regs->gp->r3->val);
}

void vm_insn_movb_r0_to_r3(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_R0_TO_R3);
  vm->regs->gp->r3->is_negative = vm->regs->gp->r0->is_negative;
  vm->regs->gp->r3->val = VM_ALIGN_TO_BYTE(vm->regs->gp->r0->val);
}

void vm_insn_movb_r1_to_r3(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_R1_TO_R3);
  vm->regs->gp->r3->is_negative = vm->regs->gp->r1->is_negative;
  vm->regs->gp->r3->val = VM_ALIGN_TO_BYTE(vm->regs->gp->r1->val);
}

void vm_insn_movb_r2_to_r3(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_R2_TO_R3);
  vm->regs->gp->r3->is_negative = vm->regs->gp->r2->is_negative;
  vm->regs->gp->r3->val = VM_ALIGN_TO_BYTE(vm->regs->gp->r2->val);
}

void vm_insn_movb_r3_to_r3(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_R3_TO_R3);
}

void vm_insn_addb_imm8_imm8_to_r0(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_ADDB_IMM8_IMM8_TO_R0);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short res = op1 + op2;

  vm->regs->gp->r0->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r0->val =
      !vm->regs->gp->r0->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_addb_imm8_imm8_to_r1(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_ADDB_IMM8_IMM8_TO_R1);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short res = op1 + op2;

  vm->regs->gp->r1->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r1->val =
      !vm->regs->gp->r1->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_addb_imm8_imm8_to_r2(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_ADDB_IMM8_IMM8_TO_R2);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short res = op1 + op2;

  vm->regs->gp->r2->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r2->val =
      !vm->regs->gp->r2->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_addb_imm8_imm8_to_r3(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_ADDB_IMM8_IMM8_TO_R3);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short res = op1 + op2;

  vm->regs->gp->r3->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r3->val =
      !vm->regs->gp->r3->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_subb_imm8_imm8_to_r0(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_SUBB_IMM8_IMM8_TO_R0);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short res = op1 - op2;

  vm->regs->gp->r0->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r0->val =
      !vm->regs->gp->r0->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_subb_imm8_imm8_to_r1(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_SUBB_IMM8_IMM8_TO_R1);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short res = op1 - op2;

  vm->regs->gp->r1->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r1->val =
      !vm->regs->gp->r1->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_subb_imm8_imm8_to_r2(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_SUBB_IMM8_IMM8_TO_R2);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short res = op1 - op2;

  vm->regs->gp->r2->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r2->val =
      !vm->regs->gp->r2->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_subb_imm8_imm8_to_r3(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_SUBB_IMM8_IMM8_TO_R3);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short res = op1 - op2;

  vm->regs->gp->r3->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r3->val =
      !vm->regs->gp->r3->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_mulb_imm8_imm8_to_r0(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_MULB_IMM8_IMM8_TO_R0);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short res = op1 * op2;

  vm->regs->gp->r0->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r0->val =
      !vm->regs->gp->r0->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_mulb_imm8_imm8_to_r1(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_MULB_IMM8_IMM8_TO_R1);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short res = op1 * op2;

  vm->regs->gp->r1->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r1->val =
      !vm->regs->gp->r1->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_mulb_imm8_imm8_to_r2(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_MULB_IMM8_IMM8_TO_R2);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short res = op1 * op2;

  vm->regs->gp->r2->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r2->val =
      !vm->regs->gp->r2->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_mulb_imm8_imm8_to_r3(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_MULB_IMM8_IMM8_TO_R3);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short res = op1 * op2;

  vm->regs->gp->r3->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r3->val =
      !vm->regs->gp->r3->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_divb_imm8_imm8_to_r0(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_DIVB_IMM8_IMM8_TO_R0);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  if (!op2) {
    fprintf(stderr, "Division by zero.\n");
    return;
  }

  short res = op1 / op2;

  vm->regs->gp->r0->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r0->val =
      !vm->regs->gp->r0->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_divb_imm8_imm8_to_r1(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_DIVB_IMM8_IMM8_TO_R1);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  if (!op2) {
    fprintf(stderr, "Division by zero.\n");
    return;
  }

  short res = op1 / op2;

  vm->regs->gp->r1->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r1->val =
      !vm->regs->gp->r1->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_divb_imm8_imm8_to_r2(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_DIVB_IMM8_IMM8_TO_R2);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  if (!op2) {
    fprintf(stderr, "Division by zero.\n");
    return;
  }

  short res = op1 / op2;

  vm->regs->gp->r2->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r2->val =
      !vm->regs->gp->r2->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_divb_imm8_imm8_to_r3(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_DIVB_IMM8_IMM8_TO_R3);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  if (!op2) {
    fprintf(stderr, "Division by zero.\n");
    return;
  }

  short res = op1 / op2;

  vm->regs->gp->r3->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r3->val =
      !vm->regs->gp->r3->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_addb_imm8_r0_to_r0(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_ADDB_IMM8_R0_TO_R0);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm->regs->gp->r0->is_negative
                  ? VM_NEGATE_BYTE(vm->regs->gp->r0->val)
                  : vm->regs->gp->r0->val;

  short res = op1 + op2;

  vm->regs->gp->r0->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r0->val =
      !vm->regs->gp->r0->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_addb_imm8_r0_to_r1(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_ADDB_IMM8_R0_TO_R1);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm->regs->gp->r0->is_negative
                  ? VM_NEGATE_BYTE(vm->regs->gp->r0->val)
                  : vm->regs->gp->r0->val;

  short res = op1 + op2;

  vm->regs->gp->r1->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r1->val =
      !vm->regs->gp->r1->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_addb_imm8_r0_to_r2(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_ADDB_IMM8_R0_TO_R2);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm->regs->gp->r0->is_negative
                  ? VM_NEGATE_BYTE(vm->regs->gp->r0->val)
                  : vm->regs->gp->r0->val;

  short res = op1 + op2;

  vm->regs->gp->r2->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r2->val =
      !vm->regs->gp->r2->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_addb_imm8_r0_to_r3(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_ADDB_IMM8_R0_TO_R3);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm->regs->gp->r0->is_negative
                  ? VM_NEGATE_BYTE(vm->regs->gp->r0->val)
                  : vm->regs->gp->r0->val;

  short res = op1 + op2;

  vm->regs->gp->r3->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r3->val =
      !vm->regs->gp->r3->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_subb_imm8_r0_to_r0(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_SUBB_IMM8_R0_TO_R0);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm->regs->gp->r0->is_negative
                  ? VM_NEGATE_BYTE(vm->regs->gp->r0->val)
                  : vm->regs->gp->r0->val;

  short res = op1 - op2;

  vm->regs->gp->r0->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r0->val =
      !vm->regs->gp->r0->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_subb_imm8_r0_to_r1(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_SUBB_IMM8_R0_TO_R1);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm->regs->gp->r0->is_negative
                  ? VM_NEGATE_BYTE(vm->regs->gp->r0->val)
                  : vm->regs->gp->r0->val;

  short res = op1 - op2;

  vm->regs->gp->r1->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r1->val =
      !vm->regs->gp->r1->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_subb_imm8_r0_to_r2(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_SUBB_IMM8_R0_TO_R2);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm->regs->gp->r0->is_negative
                  ? VM_NEGATE_BYTE(vm->regs->gp->r0->val)
                  : vm->regs->gp->r0->val;

  short res = op1 - op2;

  vm->regs->gp->r2->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r2->val =
      !vm->regs->gp->r2->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_subb_imm8_r0_to_r3(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_SUBB_IMM8_R0_TO_R3);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm->regs->gp->r0->is_negative
                  ? VM_NEGATE_BYTE(vm->regs->gp->r0->val)
                  : vm->regs->gp->r0->val;

  short res = op1 - op2;

  vm->regs->gp->r3->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r3->val =
      !vm->regs->gp->r3->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_mulb_imm8_r0_to_r0(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_MULB_IMM8_R0_TO_R0);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm->regs->gp->r0->is_negative
                  ? VM_NEGATE_BYTE(vm->regs->gp->r0->val)
                  : vm->regs->gp->r0->val;

  short res = op1 * op2;

  vm->regs->gp->r0->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r0->val =
      !vm->regs->gp->r0->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_mulb_imm8_r0_to_r1(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_MULB_IMM8_R0_TO_R1);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm->regs->gp->r0->is_negative
                  ? VM_NEGATE_BYTE(vm->regs->gp->r0->val)
                  : vm->regs->gp->r0->val;

  short res = op1 * op2;

  vm->regs->gp->r1->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r1->val =
      !vm->regs->gp->r1->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_mulb_imm8_r0_to_r2(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_MULB_IMM8_R0_TO_R2);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm->regs->gp->r0->is_negative
                  ? VM_NEGATE_BYTE(vm->regs->gp->r0->val)
                  : vm->regs->gp->r0->val;

  short res = op1 * op2;

  vm->regs->gp->r2->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r2->val =
      !vm->regs->gp->r2->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_mulb_imm8_r0_to_r3(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_MULB_IMM8_R0_TO_R3);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm->regs->gp->r0->is_negative
                  ? VM_NEGATE_BYTE(vm->regs->gp->r0->val)
                  : vm->regs->gp->r0->val;

  short res = op1 * op2;

  vm->regs->gp->r3->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r3->val =
      !vm->regs->gp->r3->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_divb_imm8_r0_to_r0(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_DIVB_IMM8_R0_TO_R0);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm->regs->gp->r0->is_negative
                  ? VM_NEGATE_BYTE(vm->regs->gp->r0->val)
                  : vm->regs->gp->r0->val;

  if (!op2) {
    fprintf(stderr, "Division by zero.\n");
    return;
  }

  short res = op1 / op2;

  vm->regs->gp->r0->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r0->val =
      !vm->regs->gp->r0->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_divb_imm8_r0_to_r1(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_DIVB_IMM8_R0_TO_R1);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm->regs->gp->r0->is_negative
                  ? VM_NEGATE_BYTE(vm->regs->gp->r0->val)
                  : vm->regs->gp->r0->val;

  if (!op2) {
    fprintf(stderr, "Division by zero.\n");
    return;
  }

  short res = op1 / op2;

  vm->regs->gp->r1->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r1->val =
      !vm->regs->gp->r1->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_divb_imm8_r0_to_r2(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_DIVB_IMM8_R0_TO_R2);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm->regs->gp->r0->is_negative
                  ? VM_NEGATE_BYTE(vm->regs->gp->r0->val)
                  : vm->regs->gp->r0->val;

  if (!op2) {
    fprintf(stderr, "Division by zero.\n");
    return;
  }

  short res = op1 / op2;

  vm->regs->gp->r2->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r2->val =
      !vm->regs->gp->r2->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_divb_imm8_r0_to_r3(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_DIVB_IMM8_R0_TO_R3);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm->regs->gp->r0->is_negative
                  ? VM_NEGATE_BYTE(vm->regs->gp->r0->val)
                  : vm->regs->gp->r0->val;

  if (!op2) {
    fprintf(stderr, "Division by zero.\n");
    return;
  }

  short res = op1 / op2;

  vm->regs->gp->r3->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r3->val =
      !vm->regs->gp->r3->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_addb_imm8_r1_to_r0(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_ADDB_IMM8_R1_TO_R0);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm->regs->gp->r1->is_negative
                  ? VM_NEGATE_BYTE(vm->regs->gp->r1->val)
                  : vm->regs->gp->r1->val;

  short res = op1 + op2;

  vm->regs->gp->r0->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r0->val =
      !vm->regs->gp->r0->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_addb_imm8_r1_to_r1(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_ADDB_IMM8_R1_TO_R1);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm->regs->gp->r1->is_negative
                  ? VM_NEGATE_BYTE(vm->regs->gp->r1->val)
                  : vm->regs->gp->r1->val;

  short res = op1 + op2;

  vm->regs->gp->r1->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r1->val =
      !vm->regs->gp->r1->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_addb_imm8_r1_to_r2(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_ADDB_IMM8_R1_TO_R2);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm->regs->gp->r1->is_negative
                  ? VM_NEGATE_BYTE(vm->regs->gp->r1->val)
                  : vm->regs->gp->r1->val;

  short res = op1 + op2;

  vm->regs->gp->r2->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r2->val =
      !vm->regs->gp->r2->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_addb_imm8_r1_to_r3(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_ADDB_IMM8_R1_TO_R3);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm->regs->gp->r1->is_negative
                  ? VM_NEGATE_BYTE(vm->regs->gp->r1->val)
                  : vm->regs->gp->r1->val;

  short res = op1 + op2;

  vm->regs->gp->r3->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r3->val =
      !vm->regs->gp->r3->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_subb_imm8_r1_to_r0(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_SUBB_IMM8_R1_TO_R0);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm->regs->gp->r1->is_negative
                  ? VM_NEGATE_BYTE(vm->regs->gp->r1->val)
                  : vm->regs->gp->r1->val;

  short res = op1 - op2;

  vm->regs->gp->r0->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r0->val =
      !vm->regs->gp->r0->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_subb_imm8_r1_to_r1(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_SUBB_IMM8_R1_TO_R1);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm->regs->gp->r1->is_negative
                  ? VM_NEGATE_BYTE(vm->regs->gp->r1->val)
                  : vm->regs->gp->r1->val;

  short res = op1 - op2;

  vm->regs->gp->r1->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r1->val =
      !vm->regs->gp->r1->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_subb_imm8_r1_to_r2(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_SUBB_IMM8_R1_TO_R2);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm->regs->gp->r1->is_negative
                  ? VM_NEGATE_BYTE(vm->regs->gp->r1->val)
                  : vm->regs->gp->r1->val;

  short res = op1 - op2;

  vm->regs->gp->r2->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r2->val =
      !vm->regs->gp->r2->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_subb_imm8_r1_to_r3(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_SUBB_IMM8_R1_TO_R3);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm->regs->gp->r1->is_negative
                  ? VM_NEGATE_BYTE(vm->regs->gp->r1->val)
                  : vm->regs->gp->r1->val;

  short res = op1 - op2;

  vm->regs->gp->r3->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r3->val =
      !vm->regs->gp->r3->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_mulb_imm8_r1_to_r0(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_MULB_IMM8_R1_TO_R0);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm->regs->gp->r1->is_negative
                  ? VM_NEGATE_BYTE(vm->regs->gp->r1->val)
                  : vm->regs->gp->r1->val;

  short res = op1 * op2;

  vm->regs->gp->r0->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r0->val =
      !vm->regs->gp->r0->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_mulb_imm8_r1_to_r1(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_MULB_IMM8_R1_TO_R1);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm->regs->gp->r1->is_negative
                  ? VM_NEGATE_BYTE(vm->regs->gp->r1->val)
                  : vm->regs->gp->r1->val;

  short res = op1 * op2;

  vm->regs->gp->r1->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r1->val =
      !vm->regs->gp->r1->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_mulb_imm8_r1_to_r2(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_MULB_IMM8_R1_TO_R2);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm->regs->gp->r1->is_negative
                  ? VM_NEGATE_BYTE(vm->regs->gp->r1->val)
                  : vm->regs->gp->r1->val;

  short res = op1 * op2;

  vm->regs->gp->r2->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r2->val =
      !vm->regs->gp->r2->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_mulb_imm8_r1_to_r3(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_MULB_IMM8_R1_TO_R3);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm->regs->gp->r1->is_negative
                  ? VM_NEGATE_BYTE(vm->regs->gp->r1->val)
                  : vm->regs->gp->r1->val;

  short res = op1 * op2;

  vm->regs->gp->r3->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r3->val =
      !vm->regs->gp->r3->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_divb_imm8_r1_to_r0(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_DIVB_IMM8_R1_TO_R0);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm->regs->gp->r1->is_negative
                  ? VM_NEGATE_BYTE(vm->regs->gp->r1->val)
                  : vm->regs->gp->r1->val;

  if (!op2) {
    fprintf(stderr, "Division by zero.\n");
    return;
  }

  short res = op1 / op2;

  vm->regs->gp->r0->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r0->val =
      !vm->regs->gp->r0->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_divb_imm8_r1_to_r1(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_DIVB_IMM8_R1_TO_R1);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm->regs->gp->r1->is_negative
                  ? VM_NEGATE_BYTE(vm->regs->gp->r1->val)
                  : vm->regs->gp->r1->val;

  if (!op2) {
    fprintf(stderr, "Division by zero.\n");
    return;
  }

  short res = op1 / op2;

  vm->regs->gp->r1->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r1->val =
      !vm->regs->gp->r1->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_divb_imm8_r1_to_r2(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_DIVB_IMM8_R1_TO_R2);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm->regs->gp->r1->is_negative
                  ? VM_NEGATE_BYTE(vm->regs->gp->r1->val)
                  : vm->regs->gp->r1->val;

  if (!op2) {
    fprintf(stderr, "Division by zero.\n");
    return;
  }

  short res = op1 / op2;

  vm->regs->gp->r2->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r2->val =
      !vm->regs->gp->r2->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_divb_imm8_r1_to_r3(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_DIVB_IMM8_R1_TO_R3);

  short op1 = vm_insn_read_byte(vm) == 0xff
                  ? VM_NEGATE_BYTE(vm_insn_read_byte(vm))
                  : vm_insn_read_byte(vm);

  short op2 = vm->regs->gp->r1->is_negative
                  ? VM_NEGATE_BYTE(vm->regs->gp->r1->val)
                  : vm->regs->gp->r1->val;

  if (!op2) {
    fprintf(stderr, "Division by zero.\n");
    return;
  }

  short res = op1 / op2;

  vm->regs->gp->r3->is_negative = ((short)res < 0) ? 1 : 0;
  vm->regs->gp->r3->val =
      !vm->regs->gp->r3->is_negative
          ? VM_ALIGN_TO_BYTE((unsigned short)res)
          : 0xff - (VM_ALIGN_TO_BYTE((unsigned short)res) - 1);
}

void vm_insn_print_imm8(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_PRINT_IMM8);

  vm_value_t *val = vm_value_create();
  val->is_negative = vm_insn_read_byte(vm) == 0xff ? 1 : 0;
  val->val = VM_ALIGN_TO_BYTE(vm_insn_read_byte(vm));

  printf("%d\n", !val->is_negative ? val->val : VM_NEGATE_BYTE(val->val));
  vm_value_destroy(val);
}

void vm_insn_print_r0(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_PRINT_R0);

  printf("%d\n", !vm->regs->gp->r0->is_negative
                     ? vm->regs->gp->r0->val
                     : (vm->regs->gp->r0->val <= 0xff)
                           ? VM_NEGATE_BYTE(vm->regs->gp->r0->val)
                           : VM_NEGATE_WORD(vm->regs->gp->r0->val));
}

void vm_insn_print_r1(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_PRINT_R1);

  printf("%d\n", !vm->regs->gp->r1->is_negative
                     ? vm->regs->gp->r1->val
                     : (vm->regs->gp->r1->val <= 0xff)
                           ? VM_NEGATE_BYTE(vm->regs->gp->r1->val)
                           : VM_NEGATE_WORD(vm->regs->gp->r1->val));
}

void vm_insn_print_r2(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_PRINT_R2);

  printf("%d\n", !vm->regs->gp->r2->is_negative
                     ? vm->regs->gp->r2->val
                     : (vm->regs->gp->r2->val <= 0xff)
                           ? VM_NEGATE_BYTE(vm->regs->gp->r2->val)
                           : VM_NEGATE_WORD(vm->regs->gp->r2->val));
}

void vm_insn_print_r3(vm_t *vm) {
  vm->state = vm_state_insert(vm->state, VM_INSN_PRINT_R3);

  printf("%d\n", !vm->regs->gp->r3->is_negative
                     ? vm->regs->gp->r3->val
                     : (vm->regs->gp->r3->val <= 0xff)
                           ? VM_NEGATE_BYTE(vm->regs->gp->r3->val)
                           : VM_NEGATE_WORD(vm->regs->gp->r3->val));
}

void vm_insn_unknown_bytecode_handler(vm_t *vm) {
  fprintf(stderr, "Unknown bytecode (%d).\n", vm->buf[vm->ip]);
  vm->is_error = 1;
}
