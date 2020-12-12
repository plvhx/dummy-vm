#ifndef __VALUE_H__
#define __VALUE_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct vm_value {
  unsigned short val;
  unsigned int is_negative;
} vm_value_t;

vm_value_t *vm_value_create(void);
void vm_value_destroy(vm_value_t *value);

#ifdef __cplusplus
}
#endif

#endif /* __VALUE_H__ */
