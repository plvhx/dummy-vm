#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "insn.h"
#include "vm.h"

vm_state_t *vm_state_create(void) {
  vm_state_t *ret = calloc(1, sizeof(vm_state_t));
  assert(ret != NULL);

  ret->opcode = -1;
  ret->next = NULL;
  return ret;
}

vm_state_t *vm_state_insert(vm_state_t *state, int opcode) {
  if (state == NULL) {
    return NULL;
  }

  vm_state_t *tmp = (vm_state_t *)state;
  vm_state_t *new;

  while (tmp->next != NULL) {
    tmp = tmp->next;
  }

  new = vm_state_create();
  new->opcode = opcode;
  new->next = tmp->next;
  tmp->next = new;
  return state;
}

void vm_state_destroy(vm_state_t *state) {
  if (state == NULL) {
    return;
  }

  vm_state_destroy(state->next);
  free(state);
}

vm_stack_t *vm_stack_create(void) {
  vm_stack_t *ret = calloc(1, sizeof(vm_stack_t));
  assert(ret != NULL);

  ret->value = NULL;
  ret->next = NULL;
  return ret;
}

vm_stack_t *vm_stack_push(vm_stack_t *stack, vm_value_t *value) {
  if (stack == NULL) {
    return NULL;
  }

  vm_stack_t *new = vm_stack_create();
  new->next = stack->next;
  new->value = value;
  stack->next = new;
  return stack;
}

int vm_stack_empty(vm_stack_t *stack) { return stack->next == NULL ? 1 : 0; }

vm_value_t *vm_stack_pop(vm_stack_t *stack) {
  vm_stack_t *tmp = stack->next;
  vm_value_t *rval = tmp->value;

  stack->next = stack->next->next == NULL ? NULL : stack->next->next;
  free(tmp);

  return rval;
}

void vm_stack_destroy(vm_stack_t *stack) { free(stack); }

vm_t *vm_init(char *buf, size_t len) {
  vm_t *vm = calloc(1, sizeof(vm_t));
  assert(vm != NULL);

  vm->buf = strdup(buf);
  vm->ip = -1;
  vm->is_error = 0;
  vm->buflen = len;
  vm->regs = vm_regs_init();
  vm->state = vm_state_create();
  vm->stack = vm_stack_create();
  return vm;
}

static void vm_movb_imm8_to_regs(vm_t *vm) {
  switch (vm->buf[vm->ip]) {
  case VM_INSN_MOVB_IMM8_TO_R0:
    vm_insn_movb_imm8_to_r0(vm);
    break;
  case VM_INSN_MOVB_IMM8_TO_R1:
    vm_insn_movb_imm8_to_r1(vm);
    break;
  case VM_INSN_MOVB_IMM8_TO_R2:
    vm_insn_movb_imm8_to_r2(vm);
    break;
  case VM_INSN_MOVB_IMM8_TO_R3:
    vm_insn_movb_imm8_to_r3(vm);
    break;
  }
}

static void vm_movb_regs_to_r0(vm_t *vm) {
  switch (vm->buf[vm->ip]) {
  case VM_INSN_MOVB_R0_TO_R0:
    vm_insn_movb_r0_to_r0(vm);
    break;
  case VM_INSN_MOVB_R1_TO_R0:
    vm_insn_movb_r1_to_r0(vm);
    break;
  case VM_INSN_MOVB_R2_TO_R0:
    vm_insn_movb_r2_to_r0(vm);
    break;
  case VM_INSN_MOVB_R3_TO_R0:
    vm_insn_movb_r3_to_r0(vm);
    break;
  }
}

static void vm_movb_regs_to_r1(vm_t *vm) {
  switch (vm->buf[vm->ip]) {
  case VM_INSN_MOVB_R0_TO_R1:
    vm_insn_movb_r0_to_r1(vm);
    break;
  case VM_INSN_MOVB_R1_TO_R1:
    vm_insn_movb_r1_to_r1(vm);
    break;
  case VM_INSN_MOVB_R2_TO_R1:
    vm_insn_movb_r2_to_r1(vm);
    break;
  case VM_INSN_MOVB_R3_TO_R1:
    vm_insn_movb_r3_to_r1(vm);
    break;
  }
}

static void vm_movb_regs_to_r2(vm_t *vm) {
  switch (vm->buf[vm->ip]) {
  case VM_INSN_MOVB_R0_TO_R2:
    vm_insn_movb_r0_to_r2(vm);
    break;
  case VM_INSN_MOVB_R1_TO_R2:
    vm_insn_movb_r1_to_r2(vm);
    break;
  case VM_INSN_MOVB_R2_TO_R2:
    vm_insn_movb_r2_to_r2(vm);
    break;
  case VM_INSN_MOVB_R3_TO_R2:
    vm_insn_movb_r3_to_r2(vm);
    break;
  }
}

static void vm_movb_regs_to_r3(vm_t *vm) {
  switch (vm->buf[vm->ip]) {
  case VM_INSN_MOVB_R0_TO_R3:
    vm_insn_movb_r0_to_r3(vm);
    break;
  case VM_INSN_MOVB_R1_TO_R3:
    vm_insn_movb_r1_to_r3(vm);
    break;
  case VM_INSN_MOVB_R2_TO_R3:
    vm_insn_movb_r2_to_r3(vm);
    break;
  case VM_INSN_MOVB_R3_TO_R3:
    vm_insn_movb_r3_to_r3(vm);
    break;
  }
}

static void vm_addb_imm8_imm8_to_regs(vm_t *vm) {
  switch (vm->buf[vm->ip]) {
  case VM_INSN_ADDB_IMM8_IMM8_TO_R0:
    vm_insn_addb_imm8_imm8_to_r0(vm);
    break;
  case VM_INSN_ADDB_IMM8_IMM8_TO_R1:
    vm_insn_addb_imm8_imm8_to_r1(vm);
    break;
  case VM_INSN_ADDB_IMM8_IMM8_TO_R2:
    vm_insn_addb_imm8_imm8_to_r2(vm);
    break;
  case VM_INSN_ADDB_IMM8_IMM8_TO_R3:
    vm_insn_addb_imm8_imm8_to_r3(vm);
    break;
  }
}

static void vm_subb_imm8_imm8_to_regs(vm_t *vm) {
  switch (vm->buf[vm->ip]) {
  case VM_INSN_SUBB_IMM8_IMM8_TO_R0:
    vm_insn_subb_imm8_imm8_to_r0(vm);
    break;
  case VM_INSN_SUBB_IMM8_IMM8_TO_R1:
    vm_insn_subb_imm8_imm8_to_r1(vm);
    break;
  case VM_INSN_SUBB_IMM8_IMM8_TO_R2:
    vm_insn_subb_imm8_imm8_to_r2(vm);
    break;
  case VM_INSN_SUBB_IMM8_IMM8_TO_R3:
    vm_insn_subb_imm8_imm8_to_r3(vm);
    break;
  }
}

static void vm_mulb_imm8_imm8_to_regs(vm_t *vm) {
  switch (vm->buf[vm->ip]) {
  case VM_INSN_MULB_IMM8_IMM8_TO_R0:
    vm_insn_mulb_imm8_imm8_to_r0(vm);
    break;
  case VM_INSN_MULB_IMM8_IMM8_TO_R1:
    vm_insn_mulb_imm8_imm8_to_r1(vm);
    break;
  case VM_INSN_MULB_IMM8_IMM8_TO_R2:
    vm_insn_mulb_imm8_imm8_to_r2(vm);
    break;
  case VM_INSN_MULB_IMM8_IMM8_TO_R3:
    vm_insn_mulb_imm8_imm8_to_r3(vm);
    break;
  }
}

static void vm_divb_imm8_imm8_to_regs(vm_t *vm) {
  switch (vm->buf[vm->ip]) {
  case VM_INSN_DIVB_IMM8_IMM8_TO_R0:
    vm_insn_divb_imm8_imm8_to_r0(vm);
    break;
  case VM_INSN_DIVB_IMM8_IMM8_TO_R1:
    vm_insn_divb_imm8_imm8_to_r1(vm);
    break;
  case VM_INSN_DIVB_IMM8_IMM8_TO_R2:
    vm_insn_divb_imm8_imm8_to_r2(vm);
    break;
  case VM_INSN_DIVB_IMM8_IMM8_TO_R3:
    vm_insn_divb_imm8_imm8_to_r3(vm);
    break;
  }
}

static void vm_addb_imm8_r0_to_regs(vm_t *vm) {
  switch (vm->buf[vm->ip]) {
  case VM_INSN_ADDB_IMM8_R0_TO_R0:
    vm_insn_addb_imm8_r0_to_r0(vm);
    break;
  case VM_INSN_ADDB_IMM8_R0_TO_R1:
    vm_insn_addb_imm8_r0_to_r1(vm);
    break;
  case VM_INSN_ADDB_IMM8_R0_TO_R2:
    vm_insn_addb_imm8_r0_to_r2(vm);
    break;
  case VM_INSN_ADDB_IMM8_R0_TO_R3:
    vm_insn_addb_imm8_r0_to_r3(vm);
    break;
  }
}

static void vm_subb_imm8_r0_to_regs(vm_t *vm) {
  switch (vm->buf[vm->ip]) {
  case VM_INSN_SUBB_IMM8_R0_TO_R0:
    vm_insn_subb_imm8_r0_to_r0(vm);
    break;
  case VM_INSN_SUBB_IMM8_R0_TO_R1:
    vm_insn_subb_imm8_r0_to_r1(vm);
    break;
  case VM_INSN_SUBB_IMM8_R0_TO_R2:
    vm_insn_subb_imm8_r0_to_r2(vm);
    break;
  case VM_INSN_SUBB_IMM8_R0_TO_R3:
    vm_insn_subb_imm8_r0_to_r3(vm);
    break;
  }
}

static void vm_mulb_imm8_r0_to_regs(vm_t *vm) {
  switch (vm->buf[vm->ip]) {
  case VM_INSN_MULB_IMM8_R0_TO_R0:
    vm_insn_mulb_imm8_r0_to_r0(vm);
    break;
  case VM_INSN_MULB_IMM8_R0_TO_R1:
    vm_insn_mulb_imm8_r0_to_r1(vm);
    break;
  case VM_INSN_MULB_IMM8_R0_TO_R2:
    vm_insn_mulb_imm8_r0_to_r2(vm);
    break;
  case VM_INSN_MULB_IMM8_R0_TO_R3:
    vm_insn_mulb_imm8_r0_to_r3(vm);
    break;
  }
}

static void vm_divb_imm8_r0_to_regs(vm_t *vm) {
  switch (vm->buf[vm->ip]) {
  case VM_INSN_DIVB_IMM8_R0_TO_R0:
    vm_insn_divb_imm8_r0_to_r0(vm);
    break;
  case VM_INSN_DIVB_IMM8_R0_TO_R1:
    vm_insn_divb_imm8_r0_to_r1(vm);
    break;
  case VM_INSN_DIVB_IMM8_R0_TO_R2:
    vm_insn_divb_imm8_r0_to_r2(vm);
    break;
  case VM_INSN_DIVB_IMM8_R0_TO_R3:
    vm_insn_divb_imm8_r0_to_r3(vm);
    break;
  }
}

static void vm_addb_imm8_r1_to_regs(vm_t *vm) {
  switch (vm->buf[vm->ip]) {
  case VM_INSN_ADDB_IMM8_R1_TO_R0:
    vm_insn_addb_imm8_r1_to_r0(vm);
    break;
  case VM_INSN_ADDB_IMM8_R1_TO_R1:
    vm_insn_addb_imm8_r1_to_r1(vm);
    break;
  case VM_INSN_ADDB_IMM8_R1_TO_R2:
    vm_insn_addb_imm8_r1_to_r2(vm);
    break;
  case VM_INSN_ADDB_IMM8_R1_TO_R3:
    vm_insn_addb_imm8_r1_to_r3(vm);
    break;
  }
}

static void vm_subb_imm8_r1_to_regs(vm_t *vm) {
  switch (vm->buf[vm->ip]) {
  case VM_INSN_SUBB_IMM8_R1_TO_R0:
    vm_insn_subb_imm8_r1_to_r0(vm);
    break;
  case VM_INSN_SUBB_IMM8_R1_TO_R1:
    vm_insn_subb_imm8_r1_to_r1(vm);
    break;
  case VM_INSN_SUBB_IMM8_R1_TO_R2:
    vm_insn_subb_imm8_r1_to_r2(vm);
    break;
  case VM_INSN_SUBB_IMM8_R1_TO_R3:
    vm_insn_subb_imm8_r1_to_r3(vm);
    break;
  }
}

static void vm_mulb_imm8_r1_to_regs(vm_t *vm) {
  switch (vm->buf[vm->ip]) {
  case VM_INSN_MULB_IMM8_R1_TO_R0:
    vm_insn_mulb_imm8_r1_to_r0(vm);
    break;
  case VM_INSN_MULB_IMM8_R1_TO_R1:
    vm_insn_mulb_imm8_r1_to_r1(vm);
    break;
  case VM_INSN_MULB_IMM8_R1_TO_R2:
    vm_insn_mulb_imm8_r1_to_r2(vm);
    break;
  case VM_INSN_MULB_IMM8_R1_TO_R3:
    vm_insn_mulb_imm8_r1_to_r3(vm);
    break;
  }
}

static void vm_divb_imm8_r1_to_regs(vm_t *vm) {
  switch (vm->buf[vm->ip]) {
  case VM_INSN_DIVB_IMM8_R1_TO_R0:
    vm_insn_divb_imm8_r1_to_r0(vm);
    break;
  case VM_INSN_DIVB_IMM8_R1_TO_R1:
    vm_insn_divb_imm8_r1_to_r1(vm);
    break;
  case VM_INSN_DIVB_IMM8_R1_TO_R2:
    vm_insn_divb_imm8_r1_to_r2(vm);
    break;
  case VM_INSN_DIVB_IMM8_R1_TO_R3:
    vm_insn_divb_imm8_r1_to_r3(vm);
    break;
  }
}

static void vm_addb_imm8_r2_to_regs(vm_t *vm) {
  switch (vm->buf[vm->ip]) {
  case VM_INSN_ADDB_IMM8_R2_TO_R0:
    vm_insn_addb_imm8_r2_to_r0(vm);
    break;
  case VM_INSN_ADDB_IMM8_R2_TO_R1:
    vm_insn_addb_imm8_r2_to_r1(vm);
    break;
  case VM_INSN_ADDB_IMM8_R2_TO_R2:
    vm_insn_addb_imm8_r2_to_r2(vm);
    break;
  case VM_INSN_ADDB_IMM8_R2_TO_R3:
    vm_insn_addb_imm8_r2_to_r3(vm);
    break;
  }
}

static void vm_print_regs(vm_t *vm) {
  switch (vm->buf[vm->ip]) {
  case VM_INSN_PRINT_R0:
    vm_insn_print_r0(vm);
    break;
  case VM_INSN_PRINT_R1:
    vm_insn_print_r1(vm);
    break;
  case VM_INSN_PRINT_R2:
    vm_insn_print_r2(vm);
    break;
  case VM_INSN_PRINT_R3:
    vm_insn_print_r3(vm);
    break;
  }
}

void vm_run(vm_t *vm) {
  while (vm->buf[++vm->ip] && !vm->is_error) {
    switch (vm->buf[vm->ip]) {
    // move imm8 to general-purpose register.
    case VM_INSN_MOVB_IMM8_TO_R0:
    case VM_INSN_MOVB_IMM8_TO_R1:
    case VM_INSN_MOVB_IMM8_TO_R2:
    case VM_INSN_MOVB_IMM8_TO_R3:
      vm_movb_imm8_to_regs(vm);
      break;
    // move general-purpose register value as
    // byte value to 'r0' general-purpose register.
    case VM_INSN_MOVB_R0_TO_R0:
    case VM_INSN_MOVB_R1_TO_R0:
    case VM_INSN_MOVB_R2_TO_R0:
    case VM_INSN_MOVB_R3_TO_R0:
      vm_movb_regs_to_r0(vm);
      break;
    // move general-purpose register value as
    // byte value to 'r1' general-purpose register.
    case VM_INSN_MOVB_R0_TO_R1:
    case VM_INSN_MOVB_R1_TO_R1:
    case VM_INSN_MOVB_R2_TO_R1:
    case VM_INSN_MOVB_R3_TO_R1:
      vm_movb_regs_to_r1(vm);
      break;
    // move general-purpose register value as
    // byte value to 'r2' general-purpose register.
    case VM_INSN_MOVB_R0_TO_R2:
    case VM_INSN_MOVB_R1_TO_R2:
    case VM_INSN_MOVB_R2_TO_R2:
    case VM_INSN_MOVB_R3_TO_R2:
      vm_movb_regs_to_r2(vm);
      break;
    // move general-purpose register value as
    // byte value to 'r3' general-purpose register.
    case VM_INSN_MOVB_R0_TO_R3:
    case VM_INSN_MOVB_R1_TO_R3:
    case VM_INSN_MOVB_R2_TO_R3:
    case VM_INSN_MOVB_R3_TO_R3:
      vm_movb_regs_to_r3(vm);
      break;
    // add imm8, imm8 and store its result to
    // general-purpose register
    case VM_INSN_ADDB_IMM8_IMM8_TO_R0:
    case VM_INSN_ADDB_IMM8_IMM8_TO_R1:
    case VM_INSN_ADDB_IMM8_IMM8_TO_R2:
    case VM_INSN_ADDB_IMM8_IMM8_TO_R3:
      vm_addb_imm8_imm8_to_regs(vm);
      break;
    // subtract imm8, imm8 and store its result to
    // general-purpose register
    case VM_INSN_SUBB_IMM8_IMM8_TO_R0:
    case VM_INSN_SUBB_IMM8_IMM8_TO_R1:
    case VM_INSN_SUBB_IMM8_IMM8_TO_R2:
    case VM_INSN_SUBB_IMM8_IMM8_TO_R3:
      vm_subb_imm8_imm8_to_regs(vm);
      break;
    // multiply imm8, imm8 and store its result to
    // general-purpose register.
    case VM_INSN_MULB_IMM8_IMM8_TO_R0:
    case VM_INSN_MULB_IMM8_IMM8_TO_R1:
    case VM_INSN_MULB_IMM8_IMM8_TO_R2:
    case VM_INSN_MULB_IMM8_IMM8_TO_R3:
      vm_mulb_imm8_imm8_to_regs(vm);
      break;
    // divide imm8, imm8 and store its result to
    // general-purpose register.
    case VM_INSN_DIVB_IMM8_IMM8_TO_R0:
    case VM_INSN_DIVB_IMM8_IMM8_TO_R1:
    case VM_INSN_DIVB_IMM8_IMM8_TO_R2:
    case VM_INSN_DIVB_IMM8_IMM8_TO_R3:
      vm_divb_imm8_imm8_to_regs(vm);
      break;
    // add imm8, r0 and store its result to
    // general-purpose register.
    case VM_INSN_ADDB_IMM8_R0_TO_R0:
    case VM_INSN_ADDB_IMM8_R0_TO_R1:
    case VM_INSN_ADDB_IMM8_R0_TO_R2:
    case VM_INSN_ADDB_IMM8_R0_TO_R3:
      vm_addb_imm8_r0_to_regs(vm);
      break;
    // subtract imm8, r0 and store its result to
    // general-purpose register.
    case VM_INSN_SUBB_IMM8_R0_TO_R0:
    case VM_INSN_SUBB_IMM8_R0_TO_R1:
    case VM_INSN_SUBB_IMM8_R0_TO_R2:
    case VM_INSN_SUBB_IMM8_R0_TO_R3:
      vm_subb_imm8_r0_to_regs(vm);
      break;
    // multiply imm8, r0 and store its result to
    // general-purpose register.
    case VM_INSN_MULB_IMM8_R0_TO_R0:
    case VM_INSN_MULB_IMM8_R0_TO_R1:
    case VM_INSN_MULB_IMM8_R0_TO_R2:
    case VM_INSN_MULB_IMM8_R0_TO_R3:
      vm_mulb_imm8_r0_to_regs(vm);
      break;
    // divide imm8, r0 and store its result to
    // general-purpose register.
    case VM_INSN_DIVB_IMM8_R0_TO_R0:
    case VM_INSN_DIVB_IMM8_R0_TO_R1:
    case VM_INSN_DIVB_IMM8_R0_TO_R2:
    case VM_INSN_DIVB_IMM8_R0_TO_R3:
      vm_divb_imm8_r0_to_regs(vm);
      break;
    // add imm8, r1 and store its result to
    // general-purpose register.
    case VM_INSN_ADDB_IMM8_R1_TO_R0:
    case VM_INSN_ADDB_IMM8_R1_TO_R1:
    case VM_INSN_ADDB_IMM8_R1_TO_R2:
    case VM_INSN_ADDB_IMM8_R1_TO_R3:
      vm_addb_imm8_r1_to_regs(vm);
      break;
    // subtract imm8, r1 and store its result to
    // general-purpose register.
    case VM_INSN_SUBB_IMM8_R1_TO_R0:
    case VM_INSN_SUBB_IMM8_R1_TO_R1:
    case VM_INSN_SUBB_IMM8_R1_TO_R2:
    case VM_INSN_SUBB_IMM8_R1_TO_R3:
      vm_subb_imm8_r1_to_regs(vm);
      break;
    // multiply imm8, r1 and store its result to
    // general-purpose register.
    case VM_INSN_MULB_IMM8_R1_TO_R0:
    case VM_INSN_MULB_IMM8_R1_TO_R1:
    case VM_INSN_MULB_IMM8_R1_TO_R2:
    case VM_INSN_MULB_IMM8_R1_TO_R3:
      vm_mulb_imm8_r1_to_regs(vm);
      break;
    // divide imm8, r1 and store its result to
    // general-purpose register.
    case VM_INSN_DIVB_IMM8_R1_TO_R0:
    case VM_INSN_DIVB_IMM8_R1_TO_R1:
    case VM_INSN_DIVB_IMM8_R1_TO_R2:
    case VM_INSN_DIVB_IMM8_R1_TO_R3:
      vm_divb_imm8_r1_to_regs(vm);
      break;
    // add imm8, r2 and store its result to
    // general-purpose register.
    case VM_INSN_ADDB_IMM8_R2_TO_R0:
    case VM_INSN_ADDB_IMM8_R2_TO_R1:
    case VM_INSN_ADDB_IMM8_R2_TO_R2:
    case VM_INSN_ADDB_IMM8_R2_TO_R3:
      vm_addb_imm8_r2_to_regs(vm);
      break;
    // print immediate 8-bit integer value.
    case VM_INSN_PRINT_IMM8:
      vm_insn_print_imm8(vm);
      break;
    // print integer value from associated
    // general-purpose register.
    case VM_INSN_PRINT_R0:
    case VM_INSN_PRINT_R1:
    case VM_INSN_PRINT_R2:
    case VM_INSN_PRINT_R3:
      vm_print_regs(vm);
      break;
    // invalid opcode handler.
    default:
      vm_insn_unknown_bytecode_handler(vm);
      break;
    }
  }
}

void vm_destroy(vm_t *vm) {
  vm_stack_destroy(vm->stack);
  vm_state_destroy(vm->state);
  vm_regs_destroy(vm->regs);

  vm->ip = -1;

  free(vm->buf);
  free(vm);
}
