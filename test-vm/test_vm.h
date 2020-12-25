#ifndef __TEST_VM_H__
#define __TEST_VM_H__

#ifdef __cplusplus
extern "C" {
#endif

void test_movb_imm8_to_r0(void);
void test_movb_imm8_to_r1(void);
void test_movb_imm8_to_r2(void);
void test_movb_imm8_to_r3(void);

void test_movb_r0_to_r0(void);
void test_movb_r1_to_r0(void);
void test_movb_r2_to_r0(void);
void test_movb_r3_to_r0(void);

void test_movb_r0_to_r1(void);
void test_movb_r1_to_r1(void);
void test_movb_r2_to_r1(void);
void test_movb_r3_to_r1(void);

void test_movb_r0_to_r2(void);
void test_movb_r1_to_r2(void);
void test_movb_r2_to_r2(void);
void test_movb_r3_to_r2(void);

void test_movb_r0_to_r3(void);
void test_movb_r1_to_r3(void);
void test_movb_r2_to_r3(void);
void test_movb_r3_to_r3(void);

void test_addb_imm8_imm8_to_r0(void);
void test_addb_imm8_imm8_to_r1(void);
void test_addb_imm8_imm8_to_r2(void);
void test_addb_imm8_imm8_to_r3(void);

void test_subb_imm8_imm8_to_r0(void);
void test_subb_imm8_imm8_to_r1(void);
void test_subb_imm8_imm8_to_r2(void);
void test_subb_imm8_imm8_to_r3(void);

void test_mulb_imm8_imm8_to_r0(void);
void test_mulb_imm8_imm8_to_r1(void);
void test_mulb_imm8_imm8_to_r2(void);
void test_mulb_imm8_imm8_to_r3(void);

void test_divb_imm8_imm8_to_r0(void);
void test_divb_imm8_imm8_to_r1(void);
void test_divb_imm8_imm8_to_r2(void);
void test_divb_imm8_imm8_to_r3(void);

void test_addb_imm8_r0_to_r0(void);
void test_addb_imm8_r0_to_r1(void);
void test_addb_imm8_r0_to_r2(void);
void test_addb_imm8_r0_to_r3(void);

void test_subb_imm8_r0_to_r0(void);
void test_subb_imm8_r0_to_r1(void);
void test_subb_imm8_r0_to_r2(void);
void test_subb_imm8_r0_to_r3(void);

#ifdef __cplusplus
}
#endif

#endif /* __TEST_VM_H__ */
