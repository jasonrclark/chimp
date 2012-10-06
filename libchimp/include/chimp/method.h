#ifndef _CHIMP_METHOD_H_INCLUDED_
#define _CHIMP_METHOD_H_INCLUDED_

#include <chimp/gc.h>
#include <chimp/any.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum _ChimpMethodType {
    CHIMP_METHOD_NATIVE,
    CHIMP_METHOD_BYTECODE
} ChimpMethodType;

typedef ChimpRef *(*ChimpNativeMethodFunc)(ChimpRef *, ChimpRef *);

typedef struct _ChimpMethod {
    ChimpAny         base;
    ChimpRef        *self; /* NULL for unbound/function */
    ChimpMethodType  type;
    union {
        struct {
            ChimpNativeMethodFunc func;
        } native;
        struct {
            /* TODO */
        } bytecode;
    };
} ChimpMethod;

chimp_bool_t
chimp_method_class_bootstrap (ChimpGC *gc);

ChimpRef *
chimp_method_new_native (ChimpGC *gc, ChimpNativeMethodFunc func);

ChimpRef *
chimp_method_new_bound (ChimpRef *unbound, ChimpRef *self);

#define CHIMP_METHOD(ref) CHIMP_CHECK_CAST(ChimpMethod, (ref), CHIMP_VALUE_TYPE_METHOD)

#define CHIMP_NATIVE_METHOD(ref) (&(CHIMP_METHOD(ref)->native))

CHIMP_EXTERN_CLASS(method);

#ifdef __cplusplus
};
#endif

#endif
