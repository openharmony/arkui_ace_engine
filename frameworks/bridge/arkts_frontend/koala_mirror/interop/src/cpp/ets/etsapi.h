/**
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef PANDA_RUNTIME_INTEROP_ETS_NAPI_H
#define PANDA_RUNTIME_INTEROP_ETS_NAPI_H

// NOLINTBEGIN(modernize-use-using, readability-identifier-naming, cppcoreguidelines-pro-type-vararg)

#ifdef __cplusplus
#include <cstdint>
#include <cstdarg>
#else
#include <stdint.h>
#include <stdarg.h>
#endif

// NOLINTBEGIN(cppcoreguidelines-macro-usage)

// Version Constants
#define ETS_NAPI_VERSION_1_0 0x00010000

// General return value constants
#define ETS_OK 0            // success
#define ETS_ERR (-1)        // unknown error
#define ETS_ERR_VER (-2)    // ETS version error
#define ETS_ERR_NOMEM (-3)  // not enough memory
#define ETS_ERR_EXIST (-4)  // VM already created
#define ETS_ERR_INVAL (-5)  // invalid arguments

// Boolean Constants
#define ETS_FALSE 0
#define ETS_TRUE 1

// Mode Constants
#define ETS_COMMIT 1
#define ETS_ABORT 2

// NOLINTEND(cppcoreguidelines-macro-usage)

// Primitive Types
typedef uint8_t ets_boolean;
typedef int8_t ets_byte;
typedef uint16_t ets_char;
typedef int16_t ets_short;
typedef int32_t ets_int;
typedef int64_t ets_long;
typedef float ets_float;
typedef double ets_double;
typedef ets_int ets_size;

// Reference Types
#ifdef __cplusplus
class __ets_object {};
class __ets_class : public __ets_object {};
class __ets_string : public __ets_object {};
class __ets_array : public __ets_object {};
class __ets_objectArray : public __ets_array {};
class __ets_booleanArray : public __ets_array {};
class __ets_byteArray : public __ets_array {};
class __ets_charArray : public __ets_array {};
class __ets_shortArray : public __ets_array {};
class __ets_intArray : public __ets_array {};
class __ets_longArray : public __ets_array {};
class __ets_floatArray : public __ets_array {};
class __ets_doubleArray : public __ets_array {};
class __ets_error : public __ets_object {};

typedef __ets_object *ets_object;
typedef __ets_class *ets_class;
typedef __ets_string *ets_string;
typedef __ets_array *ets_array;
typedef __ets_objectArray *ets_objectArray;
typedef __ets_booleanArray *ets_booleanArray;
typedef __ets_byteArray *ets_byteArray;
typedef __ets_charArray *ets_charArray;
typedef __ets_shortArray *ets_shortArray;
typedef __ets_intArray *ets_intArray;
typedef __ets_longArray *ets_longArray;
typedef __ets_floatArray *ets_floatArray;
typedef __ets_doubleArray *ets_doubleArray;
typedef __ets_error *ets_error;
typedef __ets_object *ets_weak;

#else   // __cplusplus

struct __ets_object;
typedef struct __ets_object *ets_object;
typedef ets_object ets_class;
typedef ets_object ets_string;
typedef ets_object ets_error;
typedef ets_object ets_weak;
typedef ets_object ets_array;
typedef ets_array ets_objectArray;
typedef ets_array ets_booleanArray;
typedef ets_array ets_byteArray;
typedef ets_array ets_charArray;
typedef ets_array ets_shortArray;
typedef ets_array ets_intArray;
typedef ets_array ets_longArray;
typedef ets_array ets_floatArray;
typedef ets_array ets_doubleArray;
#endif  // __cplusplus

struct __ets_deferred;
typedef struct __ets_deferred *ets_deferred;

// Field and Method IDs
struct __ets_method;
struct __ets_field;
typedef struct __ets_method *ets_method;
typedef struct __ets_field *ets_field;

// The Value Type
typedef union ets_value {
    ets_boolean z;
    ets_byte b;
    ets_char c;
    ets_short s;
    ets_int i;
    ets_long j;
    ets_float f;
    ets_double d;
    ets_object l;
} ets_value;

// Describe native method by name, signature and function pointer
typedef struct {
    const char *name;
    const char *signature;
    void *func;
} EtsNativeMethod;

// The object reference types
typedef enum {
    ETS_INVALID_REF_TYPE = 0,
    ETS_LOCAL_REF_TYPE = 1,
    ETS_GLOBAL_REF_TYPE = 2,
    ETS_WEAK_GLOBAL_REF_TYPE = 3
} ets_objectRefType;

#ifdef __cplusplus
typedef struct __EtsVM EtsVM;
typedef struct __EtsEnv ets_env;
#else
typedef const struct ETS_InvokeInterface *EtsVM;
typedef const struct ETS_NativeInterface *ets_env;
#endif

// Deprecated types:
typedef ets_env EtsEnv;

typedef enum {
    ETS_OKAY,
    ETS_INVALID_ARG,
    ETS_GENERIC_FAILURE,
    ETS_PENDING_EXCEPTION,
    ETS_INVALID_VERSION,  // NOTE(v.cherkashin): This status code doesn't match to napi interface.
                          //                     Should we probably delete this status code?
} ets_status;

// clang-format off
// Interface Function Table
struct ETS_NativeInterface {
    // NOTE(a.urakov): solve the "Array" naming problem
    ets_int (*GetVersion)(EtsEnv *env);
#ifdef ETS_NAPI_DESIGN_FINISHED
    ets_class (*DefineClass)(EtsEnv *env, const char *name, ets_object loader, const ets_byte *buf, ets_size bufLen);
#endif
    ets_class (*FindClass)(EtsEnv *env, const char *name);
#ifdef ETS_NAPI_DESIGN_FINISHED
    ets_method (*FromReflectedMethod)(EtsEnv *env, ets_object method);
    ets_field (*FromReflectedField)(EtsEnv *env, ets_object field);
    ets_object (*ToReflectedMethod)(EtsEnv *env, ets_class cls, ets_method p_method, ets_boolean isStatic);
#endif
    ets_class (*GetSuperclass)(EtsEnv *env, ets_class cls);
    ets_boolean (*IsAssignableFrom)(EtsEnv *env, ets_class cls1, ets_class cls2);
#ifdef ETS_NAPI_DESIGN_FINISHED
    ets_object (*ToReflectedField)(EtsEnv *env, ets_class cls, ets_field p_field, ets_boolean isStatic);
#endif
    ets_int (*ThrowError)(EtsEnv *env, ets_error obj);
    ets_int (*ThrowErrorNew)(EtsEnv *env, ets_class cls, const char *message);
    ets_error (*ErrorOccurred)(EtsEnv *env);
    void (*ErrorDescribe)(EtsEnv *env);
    void (*ErrorClear)(EtsEnv *env);
    void (*FatalError)(EtsEnv *env, const char *message);
    ets_int (*PushLocalFrame)(EtsEnv *env, ets_int capacity);
    ets_object (*PopLocalFrame)(EtsEnv *env, ets_object result);
    ets_object (*NewGlobalRef)(EtsEnv *env, ets_object obj);
    void (*DeleteGlobalRef)(EtsEnv *env, ets_object globalRef);
    void (*DeleteLocalRef)(EtsEnv *env, ets_object localRef);
    ets_boolean (*IsSameObject)(EtsEnv *env, ets_object ref1, ets_object ref2);
    ets_object (*NewLocalRef)(EtsEnv *env, ets_object ref);
    ets_int (*EnsureLocalCapacity)(EtsEnv *env, ets_int capacity);
    ets_object (*AllocObject)(EtsEnv *env, ets_class cls);
    ets_object (*NewObject)(EtsEnv *env, ets_class cls, ets_method p_method, ...);
    ets_object (*NewObjectList)(EtsEnv *env, ets_class cls, ets_method p_method, va_list args);
    ets_object (*NewObjectArray)(EtsEnv *env, ets_class cls, ets_method p_method, const ets_value *args);
    ets_class (*GetObjectClass)(EtsEnv *env, ets_object obj);
    ets_boolean (*IsInstanceOf)(EtsEnv *env, ets_object obj, ets_class cls);
    ets_method (*Getp_method)(EtsEnv *env, ets_class cls, const char *name, const char *sig);
    ets_object (*CallObjectMethod)(EtsEnv *env, ets_object obj, ets_method p_method, ...);
    ets_object (*CallObjectMethodList)(EtsEnv *env, ets_object obj, ets_method p_method, va_list args);
    ets_object (*CallObjectMethodArray)(EtsEnv *env, ets_object obj, ets_method p_method, const ets_value *args);
    ets_boolean (*CallBooleanMethod)(EtsEnv *env, ets_object obj, ets_method p_method, ...);
    ets_boolean (*CallBooleanMethodList)(EtsEnv *env, ets_object obj, ets_method p_method, va_list args);
    ets_boolean (*CallBooleanMethodArray)(EtsEnv *env, ets_object obj, ets_method p_method, const ets_value *args);
    ets_byte (*CallByteMethod)(EtsEnv *env, ets_object obj, ets_method p_method, ...);
    ets_byte (*CallByteMethodList)(EtsEnv *env, ets_object obj, ets_method p_method, va_list args);
    ets_byte (*CallByteMethodArray)(EtsEnv *env, ets_object obj, ets_method p_method, const ets_value *args);
    ets_char (*CallCharMethod)(EtsEnv *env, ets_object obj, ets_method p_method, ...);
    ets_char (*CallCharMethodList)(EtsEnv *env, ets_object obj, ets_method p_method, va_list args);
    ets_char (*CallCharMethodArray)(EtsEnv *env, ets_object obj, ets_method p_method, const ets_value *args);
    ets_short (*CallShortMethod)(EtsEnv *env, ets_object obj, ets_method p_method, ...);
    ets_short (*CallShortMethodList)(EtsEnv *env, ets_object obj, ets_method p_method, va_list args);
    ets_short (*CallShortMethodArray)(EtsEnv *env, ets_object obj, ets_method p_method, const ets_value *args);
    ets_int (*CallIntMethod)(EtsEnv *env, ets_object obj, ets_method p_method, ...);
    ets_int (*CallIntMethodList)(EtsEnv *env, ets_object obj, ets_method p_method, va_list args);
    ets_int (*CallIntMethodArray)(EtsEnv *env, ets_object obj, ets_method p_method, const ets_value *args);
    ets_long (*CallLongMethod)(EtsEnv *env, ets_object obj, ets_method p_method, ...);
    ets_long (*CallLongMethodList)(EtsEnv *env, ets_object obj, ets_method p_method, va_list args);
    ets_long (*CallLongMethodArray)(EtsEnv *env, ets_object obj, ets_method p_method, const ets_value *args);
    ets_float (*CallFloatMethod)(EtsEnv *env, ets_object obj, ets_method p_method, ...);
    ets_float (*CallFloatMethodList)(EtsEnv *env, ets_object obj, ets_method p_method, va_list args);
    ets_float (*CallFloatMethodArray)(EtsEnv *env, ets_object obj, ets_method p_method, const ets_value *args);
    ets_double (*CallDoubleMethod)(EtsEnv *env, ets_object obj, ets_method p_method, ...);
    ets_double (*CallDoubleMethodList)(EtsEnv *env, ets_object obj, ets_method p_method, va_list args);
    ets_double (*CallDoubleMethodArray)(EtsEnv *env, ets_object obj, ets_method p_method, const ets_value *args);
    void (*CallVoidMethod)(EtsEnv *env, ets_object obj, ets_method p_method, ...);
    void (*CallVoidMethodList)(EtsEnv *env, ets_object obj, ets_method p_method, va_list args);
    void (*CallVoidMethodArray)(EtsEnv *env, ets_object obj, ets_method p_method, const ets_value *args);

    ets_object (*CallNonvirtualObjectMethod)(EtsEnv *env, ets_object obj, ets_class cls, ets_method p_method, ...);
    ets_object (*CallNonvirtualObjectMethodList)(EtsEnv *env, ets_object obj, ets_class cls, ets_method p_method,
                                                 va_list args);
    ets_object (*CallNonvirtualObjectMethodArray)(EtsEnv *env, ets_object obj, ets_class cls, ets_method p_method,
                                                  const ets_value *args);
    ets_boolean (*CallNonvirtualBooleanMethod)(EtsEnv *env, ets_object obj, ets_class cls, ets_method p_method, ...);
    ets_boolean (*CallNonvirtualBooleanMethodList)(EtsEnv *env, ets_object obj, ets_class cls, ets_method p_method,
                                                   va_list args);
    ets_boolean (*CallNonvirtualBooleanMethodArray)(EtsEnv *env, ets_object obj, ets_class cls, ets_method p_method,
                                                    const ets_value *args);
    ets_byte (*CallNonvirtualByteMethod)(EtsEnv *env, ets_object obj, ets_class cls, ets_method p_method, ...);
    ets_byte (*CallNonvirtualByteMethodList)(EtsEnv *env, ets_object obj, ets_class cls, ets_method p_method,
                                             va_list args);
    ets_byte (*CallNonvirtualByteMethodArray)(EtsEnv *env, ets_object obj, ets_class cls, ets_method p_method,
                                              const ets_value *args);
    ets_char (*CallNonvirtualCharMethod)(EtsEnv *env, ets_object obj, ets_class cls, ets_method p_method, ...);
    ets_char (*CallNonvirtualCharMethodList)(EtsEnv *env, ets_object obj, ets_class cls, ets_method p_method,
                                             va_list args);
    ets_char (*CallNonvirtualCharMethodArray)(EtsEnv *env, ets_object obj, ets_class cls, ets_method p_method,
                                              const ets_value *args);
    ets_short (*CallNonvirtualShortMethod)(EtsEnv *env, ets_object obj, ets_class cls, ets_method p_method, ...);
    ets_short (*CallNonvirtualShortMethodList)(EtsEnv *env, ets_object obj, ets_class cls, ets_method p_method,
                                               va_list args);
    ets_short (*CallNonvirtualShortMethodArray)(EtsEnv *env, ets_object obj, ets_class cls, ets_method p_method,
                                                const ets_value *args);
    ets_int (*CallNonvirtualIntMethod)(EtsEnv *env, ets_object obj, ets_class cls, ets_method p_method, ...);
    ets_int (*CallNonvirtualIntMethodList)(EtsEnv *env, ets_object obj, ets_class cls, ets_method p_method,
                                           va_list args);
    ets_int (*CallNonvirtualIntMethodArray)(EtsEnv *env, ets_object obj, ets_class cls, ets_method p_method,
                                            const ets_value *args);
    ets_long (*CallNonvirtualLongMethod)(EtsEnv *env, ets_object obj, ets_class cls, ets_method p_method, ...);
    ets_long (*CallNonvirtualLongMethodList)(EtsEnv *env, ets_object obj, ets_class cls, ets_method p_method,
                                             va_list args);
    ets_long (*CallNonvirtualLongMethodArray)(EtsEnv *env, ets_object obj, ets_class cls, ets_method p_method,
                                              const ets_value *args);
    ets_float (*CallNonvirtualFloatMethod)(EtsEnv *env, ets_object obj, ets_class cls, ets_method p_method, ...);
    ets_float (*CallNonvirtualFloatMethodList)(EtsEnv *env, ets_object obj, ets_class cls, ets_method p_method,
                                               va_list args);
    ets_float (*CallNonvirtualFloatMethodArray)(EtsEnv *env, ets_object obj, ets_class cls, ets_method p_method,
                                                const ets_value *args);
    ets_double (*CallNonvirtualDoubleMethod)(EtsEnv *env, ets_object obj, ets_class cls, ets_method p_method, ...);
    ets_double (*CallNonvirtualDoubleMethodList)(EtsEnv *env, ets_object obj, ets_class cls, ets_method p_method,
                                                 va_list args);
    ets_double (*CallNonvirtualDoubleMethodArray)(EtsEnv *env, ets_object obj, ets_class cls, ets_method p_method,
                                                  const ets_value *args);
    void (*CallNonvirtualVoidMethod)(EtsEnv *env, ets_object obj, ets_class cls, ets_method p_method, ...);
    void (*CallNonvirtualVoidMethodList)(EtsEnv *env, ets_object obj, ets_class cls, ets_method p_method, va_list args);
    void (*CallNonvirtualVoidMethodArray)(EtsEnv *env, ets_object obj, ets_class cls, ets_method p_method,
                                          const ets_value *args);
    ets_field (*Getp_field)(EtsEnv *env, ets_class cls, const char *name, const char *sig);
    ets_object (*GetObjectField)(EtsEnv *env, ets_object obj, ets_field p_field);
    ets_boolean (*GetBooleanField)(EtsEnv *env, ets_object obj, ets_field p_field);
    ets_byte (*GetByteField)(EtsEnv *env, ets_object obj, ets_field p_field);
    ets_char (*GetCharField)(EtsEnv *env, ets_object obj, ets_field p_field);
    ets_short (*GetShortField)(EtsEnv *env, ets_object obj, ets_field p_field);
    ets_int (*GetIntField)(EtsEnv *env, ets_object obj, ets_field p_field);
    ets_long (*GetLongField)(EtsEnv *env, ets_object obj, ets_field p_field);
    ets_float (*GetFloatField)(EtsEnv *env, ets_object obj, ets_field p_field);
    ets_double (*GetDoubleField)(EtsEnv *env, ets_object obj, ets_field p_field);
    void (*SetObjectField)(EtsEnv *env, ets_object obj, ets_field p_field, ets_object value);
    void (*SetBooleanField)(EtsEnv *env, ets_object obj, ets_field p_field, ets_boolean value);
    void (*SetByteField)(EtsEnv *env, ets_object obj, ets_field p_field, ets_byte value);
    void (*SetCharField)(EtsEnv *env, ets_object obj, ets_field p_field, ets_char value);
    void (*SetShortField)(EtsEnv *env, ets_object obj, ets_field p_field, ets_short value);
    void (*SetIntField)(EtsEnv *env, ets_object obj, ets_field p_field, ets_int value);
    void (*SetLongField)(EtsEnv *env, ets_object obj, ets_field p_field, ets_long value);
    void (*SetFloatField)(EtsEnv *env, ets_object obj, ets_field p_field, ets_float value);
    void (*SetDoubleField)(EtsEnv *env, ets_object obj, ets_field p_field, ets_double value);
    ets_method (*GetStaticp_method)(EtsEnv *env, ets_class cls, const char *name, const char *sig);
    ets_object (*CallStaticObjectMethod)(EtsEnv *env, ets_class cls, ets_method p_method, ...);
    ets_object (*CallStaticObjectMethodList)(EtsEnv *env, ets_class cls, ets_method p_method, va_list args);
    ets_object (*CallStaticObjectMethodArray)(EtsEnv *env, ets_class cls, ets_method p_method, ets_value *args);
    ets_boolean (*CallStaticBooleanMethod)(EtsEnv *env, ets_class cls, ets_method p_method, ...);
    ets_boolean (*CallStaticBooleanMethodList)(EtsEnv *env, ets_class cls, ets_method p_method, va_list args);
    ets_boolean (*CallStaticBooleanMethodArray)(EtsEnv *env, ets_class cls, ets_method p_method, ets_value *args);
    ets_byte (*CallStaticByteMethod)(EtsEnv *env, ets_class cls, ets_method p_method, ...);
    ets_byte (*CallStaticByteMethodList)(EtsEnv *env, ets_class cls, ets_method p_method, va_list args);
    ets_byte (*CallStaticByteMethodArray)(EtsEnv *env, ets_class cls, ets_method p_method, ets_value *args);
    ets_char (*CallStaticCharMethod)(EtsEnv *env, ets_class cls, ets_method p_method, ...);
    ets_char (*CallStaticCharMethodList)(EtsEnv *env, ets_class cls, ets_method p_method, va_list args);
    ets_char (*CallStaticCharMethodArray)(EtsEnv *env, ets_class cls, ets_method p_method, ets_value *args);
    ets_short (*CallStaticShortMethod)(EtsEnv *env, ets_class cls, ets_method p_method, ...);
    ets_short (*CallStaticShortMethodList)(EtsEnv *env, ets_class cls, ets_method p_method, va_list args);
    ets_short (*CallStaticShortMethodArray)(EtsEnv *env, ets_class cls, ets_method p_method, ets_value *args);
    ets_int (*CallStaticIntMethod)(EtsEnv *env, ets_class cls, ets_method p_method, ...);
    ets_int (*CallStaticIntMethodList)(EtsEnv *env, ets_class cls, ets_method p_method, va_list args);
    ets_int (*CallStaticIntMethodArray)(EtsEnv *env, ets_class cls, ets_method p_method, ets_value *args);
    ets_long (*CallStaticLongMethod)(EtsEnv *env, ets_class cls, ets_method p_method, ...);
    ets_long (*CallStaticLongMethodList)(EtsEnv *env, ets_class cls, ets_method p_method, va_list args);
    ets_long (*CallStaticLongMethodArray)(EtsEnv *env, ets_class cls, ets_method p_method, ets_value *args);
    ets_float (*CallStaticFloatMethod)(EtsEnv *env, ets_class cls, ets_method p_method, ...);
    ets_float (*CallStaticFloatMethodList)(EtsEnv *env, ets_class cls, ets_method p_method, va_list args);
    ets_float (*CallStaticFloatMethodArray)(EtsEnv *env, ets_class cls, ets_method p_method, ets_value *args);
    ets_double (*CallStaticDoubleMethod)(EtsEnv *env, ets_class cls, ets_method p_method, ...);
    ets_double (*CallStaticDoubleMethodList)(EtsEnv *env, ets_class cls, ets_method p_method, va_list args);
    ets_double (*CallStaticDoubleMethodArray)(EtsEnv *env, ets_class cls, ets_method p_method, ets_value *args);
    void (*CallStaticVoidMethod)(EtsEnv *env, ets_class cls, ets_method p_method, ...);
    void (*CallStaticVoidMethodList)(EtsEnv *env, ets_class cls, ets_method p_method, va_list args);
    void (*CallStaticVoidMethodArray)(EtsEnv *env, ets_class cls, ets_method p_method, ets_value *args);
    ets_field (*GetStaticp_field)(EtsEnv *env, ets_class cls, const char *name, const char *sig);
    ets_object (*GetStaticObjectField)(EtsEnv *env, ets_class cls, ets_field p_field);
    ets_boolean (*GetStaticBooleanField)(EtsEnv *env, ets_class cls, ets_field p_field);
    ets_byte (*GetStaticByteField)(EtsEnv *env, ets_class cls, ets_field p_field);
    ets_char (*GetStaticCharField)(EtsEnv *env, ets_class cls, ets_field p_field);
    ets_short (*GetStaticShortField)(EtsEnv *env, ets_class cls, ets_field p_field);
    ets_int (*GetStaticIntField)(EtsEnv *env, ets_class cls, ets_field p_field);
    ets_long (*GetStaticLongField)(EtsEnv *env, ets_class cls, ets_field p_field);
    ets_float (*GetStaticFloatField)(EtsEnv *env, ets_class cls, ets_field p_field);
    ets_double (*GetStaticDoubleField)(EtsEnv *env, ets_class cls, ets_field p_field);
    void (*SetStaticObjectField)(EtsEnv *env, ets_class cls, ets_field p_field, ets_object value);
    void (*SetStaticBooleanField)(EtsEnv *env, ets_class cls, ets_field p_field, ets_boolean value);
    void (*SetStaticByteField)(EtsEnv *env, ets_class cls, ets_field p_field, ets_byte value);
    void (*SetStaticCharField)(EtsEnv *env, ets_class cls, ets_field p_field, ets_char value);
    void (*SetStaticShortField)(EtsEnv *env, ets_class cls, ets_field p_field, ets_short value);
    void (*SetStaticIntField)(EtsEnv *env, ets_class cls, ets_field p_field, ets_int value);
    void (*SetStaticLongField)(EtsEnv *env, ets_class cls, ets_field p_field, ets_long value);
    void (*SetStaticFloatField)(EtsEnv *env, ets_class cls, ets_field p_field, ets_float value);
    void (*SetStaticDoubleField)(EtsEnv *env, ets_class cls, ets_field p_field, ets_double value);
    ets_string (*NewString)(EtsEnv *env, const ets_char *unicodeChars, ets_size len);
    ets_size (*GetStringLength)(EtsEnv *env, ets_string string);
    const ets_char *(*GetStringChars)(EtsEnv *env, ets_string string, ets_boolean *isCopy);
    void (*ReleaseStringChars)(EtsEnv *env, ets_string string, const ets_char *chars);
    ets_string (*NewStringUTF)(EtsEnv *env, const char *bytes);
    ets_size (*GetStringUTFLength)(EtsEnv *env, ets_string string);
    const char *(*GetStringUTFChars)(EtsEnv *env, ets_string string, ets_boolean *isCopy);
    void (*ReleaseStringUTFChars)(EtsEnv *env, ets_string string, const char *utf);
    ets_size (*GetArrayLength)(EtsEnv *env, ets_array array);
    ets_objectArray (*NewObjectsArray)(EtsEnv *env, ets_size length, ets_class element_class,
                                      ets_object initial_element);
    ets_object (*GetObjectArrayElement)(EtsEnv *env, ets_objectArray array, ets_size index);
    void (*SetObjectArrayElement)(EtsEnv *env, ets_objectArray array, ets_size index, ets_object value);
    ets_booleanArray (*NewBooleanArray)(EtsEnv *env, ets_size length);
    ets_byteArray (*NewByteArray)(EtsEnv *env, ets_size length);
    ets_charArray (*NewCharArray)(EtsEnv *env, ets_size length);
    ets_shortArray (*NewShortArray)(EtsEnv *env, ets_size length);
    ets_intArray (*NewIntArray)(EtsEnv *env, ets_size length);
    ets_longArray (*NewLongArray)(EtsEnv *env, ets_size length);
    ets_floatArray (*NewFloatArray)(EtsEnv *env, ets_size length);
    ets_doubleArray (*NewDoubleArray)(EtsEnv *env, ets_size length);
    ets_boolean *(*PinBooleanArray)(EtsEnv *env, ets_booleanArray array);
    ets_byte *(*PinByteArray)(EtsEnv *env, ets_byteArray array);
    ets_char *(*PinCharArray)(EtsEnv *env, ets_charArray array);
    ets_short *(*PinShortArray)(EtsEnv *env, ets_shortArray array);
    ets_int *(*PinIntArray)(EtsEnv *env, ets_intArray array);
    ets_long *(*PinLongArray)(EtsEnv *env, ets_longArray array);
    ets_float *(*PinFloatArray)(EtsEnv *env, ets_floatArray array);
    ets_double *(*PinDoubleArray)(EtsEnv *env, ets_doubleArray array);
    void (*UnpinBooleanArray)(EtsEnv *env, ets_booleanArray array);
    void (*UnpinByteArray)(EtsEnv *env, ets_byteArray array);
    void (*UnpinCharArray)(EtsEnv *env, ets_charArray array);
    void (*UnpinShortArray)(EtsEnv *env, ets_shortArray array);
    void (*UnpinIntArray)(EtsEnv *env, ets_intArray array);
    void (*UnpinLongArray)(EtsEnv *env, ets_longArray array);
    void (*UnpinFloatArray)(EtsEnv *env, ets_floatArray array);
    void (*UnpinDoubleArray)(EtsEnv *env, ets_doubleArray array);
    void (*GetBooleanArrayRegion)(EtsEnv *env, ets_booleanArray array, ets_size start, ets_size len, ets_boolean *buf);
    void (*GetByteArrayRegion)(EtsEnv *env, ets_byteArray array, ets_size start, ets_size len, ets_byte *buf);
    void (*GetCharArrayRegion)(EtsEnv *env, ets_charArray array, ets_size start, ets_size len, ets_char *buf);
    void (*GetShortArrayRegion)(EtsEnv *env, ets_shortArray array, ets_size start, ets_size len, ets_short *buf);
    void (*GetIntArrayRegion)(EtsEnv *env, ets_intArray array, ets_size start, ets_size len, ets_int *buf);
    void (*GetLongArrayRegion)(EtsEnv *env, ets_longArray array, ets_size start, ets_size len, ets_long *buf);
    void (*GetFloatArrayRegion)(EtsEnv *env, ets_floatArray array, ets_size start, ets_size len, ets_float *buf);
    void (*GetDoubleArrayRegion)(EtsEnv *env, ets_doubleArray array, ets_size start, ets_size len, ets_double *buf);
    void (*SetBooleanArrayRegion)(EtsEnv *env, ets_booleanArray array, ets_size start, ets_size len,
                                  const ets_boolean *buf);
    void (*SetByteArrayRegion)(EtsEnv *env, ets_byteArray array, ets_size start, ets_size len, const ets_byte *buf);
    void (*SetCharArrayRegion)(EtsEnv *env, ets_charArray array, ets_size start, ets_size len, const ets_char *buf);
    void (*SetShortArrayRegion)(EtsEnv *env, ets_shortArray array, ets_size start, ets_size len, const ets_short *buf);
    void (*SetIntArrayRegion)(EtsEnv *env, ets_intArray array, ets_size start, ets_size len, const ets_int *buf);
    void (*SetLongArrayRegion)(EtsEnv *env, ets_longArray array, ets_size start, ets_size len, const ets_long *buf);
    void (*SetFloatArrayRegion)(EtsEnv *env, ets_floatArray array, ets_size start, ets_size len, const ets_float *buf);
    void (*SetDoubleArrayRegion)(EtsEnv *env, ets_doubleArray array, ets_size start, ets_size len,
                                 const ets_double *buf);
    ets_int (*RegisterNatives)(EtsEnv *env, ets_class cls, const EtsNativeMethod *methods, ets_int nMethods);
    ets_int (*UnregisterNatives)(EtsEnv *env, ets_class cls);
    ets_int (*GetEtsVM)(EtsEnv *env, EtsVM **vm);
    void (*GetStringRegion)(EtsEnv *env, ets_string str, ets_size start, ets_size len, ets_char *buf);
    void (*GetStringUTFRegion)(EtsEnv *env, ets_string str, ets_size start, ets_size len, char *buf);
    ets_weak (*NewWeakGlobalRef)(EtsEnv *env, ets_object obj);
    void (*DeleteWeakGlobalRef)(EtsEnv *env, ets_weak obj);
    ets_boolean (*ErrorCheck)(EtsEnv *env);
#ifdef ETS_NAPI_DESIGN_FINISHED
    ets_object (*NewDirectByteBuffer)(EtsEnv *env, void *address, ets_long capacity);
    void *(*GetDirectBufferAddress)(EtsEnv *env, ets_object buf);
    ets_long (*GetDirectBufferCapacity)(EtsEnv *env, ets_object buf);
#endif
    ets_objectRefType (*GetObjectRefType)(EtsEnv *env, ets_object obj);

    /* 227 methods */

    // Promise API
    ets_status (*PromiseCreate)(EtsEnv *env, ets_deferred *deferred, ets_object *promise);
    ets_status (*DeferredResolve)(EtsEnv *env, ets_deferred deferred, ets_object resolution);
    ets_status (*DeferredReject)(EtsEnv *env, ets_deferred deferred, ets_object rejection);
};
// clang-format on

// Invocation API Functions
typedef enum {
    ETS_LOG_LEVEL,
    ETS_MOBILE_LOG,
    ETS_BOOT_FILE,
    ETS_AOT_FILE,
    ETS_ARK_FILE,
    ETS_JIT,
    ETS_NO_JIT,
    ETS_AOT,
    ETS_NO_AOT,
    ETS_GC_TRIGGER_TYPE,
    ETS_GC_TYPE,
    ETS_RUN_GC_IN_PLACE,
    ETS_INTERPRETER_TYPE,
    ETS_NATIVE_LIBRARY_PATH,
    ETS_VERIFICATION_MODE
} EtsOptionType;

typedef struct EtsVMOption {
    EtsOptionType option;
    const void *extraInfo;
} EtsVMOption;

typedef struct EtsVMInitArgs {
    ets_int version;
    ets_int nOptions;
    EtsVMOption *options;
} EtsVMInitArgs;

typedef enum {
    ETS_MOBILE_LOG_LEVEL_UNKNOWN = 0,
    ETS_MOBILE_LOG_LEVEL_DEFAULT,
    ETS_MOBILE_LOG_LEVEL_VERBOSE,
    ETS_MOBILE_LOG_LEVEL_DEBUG,
    ETS_MOBILE_LOG_LEVEL_INFO,
    ETS_MOBILE_LOG_LEVEL_WARN,
    ETS_MOBILE_LOG_LEVEL_ERROR,
    ETS_MOBILE_LOG_LEVEL_FATAL,
    ETS_MOBILE_LOG_LEVEL_SILENT
} EtsMobileLogggerLevel;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _MSC_VER
#define ETS_EXPORT  __declspec(dllexport)
#else
#define ETS_EXPORT __attribute__((visibility("default")))
#endif
#define ETS_IMPORT
#define ETS_CALL

ETS_EXPORT ets_int ETS_GetDefaultVMInitArgs(EtsVMInitArgs *vmArgs);
ETS_EXPORT ets_int ETS_GetCreatedVMs(EtsVM **vmBuf, ets_size bufLen, ets_size *nVms);
ETS_EXPORT ets_int ETS_CreateVM(EtsVM **pVm, EtsEnv **pEnv, EtsVMInitArgs *vmArgs);

#ifdef __cplusplus
}
#endif

struct ETS_InvokeInterface {
    ets_int (*DestroyEtsVM)(EtsVM *vm);
    ets_int (*GetEnv)(EtsVM *vm, EtsEnv **pEnv, ets_int version);
};

struct __EtsVM {
    // NOLINTNEXTLINE(misc-non-private-member-variables-in-classes)
    const struct ETS_InvokeInterface *invoke_interface;

#ifdef __cplusplus
    ets_int DestroyEtsVM()
    {
        return invoke_interface->DestroyEtsVM(this);
    }

    ets_int GetEnv(EtsEnv **pEnv, ets_int version)
    {
        return invoke_interface->GetEnv(this, pEnv, version);
    }
#endif
};

struct __EtsEnv {
    // NOLINTNEXTLINE(misc-non-private-member-variables-in-classes)
    const struct ETS_NativeInterface *native_interface;

#ifdef __cplusplus

    ets_int GetVersion()
    {
        return native_interface->GetVersion(this);
    }
    // DefineClass,
    ets_class FindClass(const char *name)
    {
        return native_interface->FindClass(this, name);
    }
    // FromReflectedMethod,
    // FromReflectedField,
    // ToReflectedMethod,
    ets_class GetSuperclass(ets_class cls)
    {
        return native_interface->GetSuperclass(this, cls);
    }
    ets_boolean IsAssignableFrom(ets_class cls1, ets_class cls2)
    {
        return native_interface->IsAssignableFrom(this, cls1, cls2);
    }
    // ToReflectedField,
    ets_int ThrowError(ets_error obj)
    {
        return native_interface->ThrowError(this, obj);
    }
    ets_int ThrowErrorNew(ets_class cls, const char *message)
    {
        return native_interface->ThrowErrorNew(this, cls, message);
    }
    ets_error ErrorOccurred()
    {
        return native_interface->ErrorOccurred(this);
    }
    void ErrorDescribe()
    {
        native_interface->ErrorDescribe(this);
    }
    void ErrorClear()
    {
        native_interface->ErrorClear(this);
    }
    void FatalError(const char *message)
    {
        native_interface->FatalError(this, message);
    }
    ets_int PushLocalFrame(ets_int capacity)
    {
        return native_interface->PushLocalFrame(this, capacity);
    }
    ets_object PopLocalFrame(ets_object result)
    {
        return native_interface->PopLocalFrame(this, result);
    }
    ets_object NewGlobalRef(ets_object obj)
    {
        return native_interface->NewGlobalRef(this, obj);
    }
    void DeleteGlobalRef(ets_object globalRef)
    {
        native_interface->DeleteGlobalRef(this, globalRef);
    }
    void DeleteLocalRef(ets_object localRef)
    {
        native_interface->DeleteLocalRef(this, localRef);
    }
    ets_boolean IsSameObject(ets_object ref1, ets_object ref2)
    {
        return native_interface->IsSameObject(this, ref1, ref2);
    }
    ets_object NewLocalRef(ets_object ref)
    {
        return native_interface->NewLocalRef(this, ref);
    }
    ets_int EnsureLocalCapacity(ets_int capacity)
    {
        return native_interface->EnsureLocalCapacity(this, capacity);
    }
    ets_object AllocObject(ets_class cls)
    {
        return native_interface->AllocObject(this, cls);
    }
    ets_object NewObject(ets_class cls, ets_method p_method, ...)
    {
        va_list args;
        va_start(args, p_method);
        ets_object ret = native_interface->NewObjectList(this, cls, p_method, args);
        va_end(args);
        return ret;
    }
    ets_object NewObjectList(ets_class cls, ets_method p_method, va_list args)
    {
        return native_interface->NewObjectList(this, cls, p_method, args);
    }
    ets_object NewObjectArray(ets_class cls, ets_method p_method, const ets_value *args)
    {
        return native_interface->NewObjectArray(this, cls, p_method, args);
    }
    ets_class GetObjectClass(ets_object obj)
    {
        return native_interface->GetObjectClass(this, obj);
    }
    ets_boolean IsInstanceOf(ets_object obj, ets_class cls)
    {
        return native_interface->IsInstanceOf(this, obj, cls);
    }
    ets_method Getp_method(ets_class cls, const char *name, const char *sig)
    {
        return native_interface->Getp_method(this, cls, name, sig);
    }
    ets_object CallObjectMethod(ets_object obj, ets_method method_id, ...)
    {
        va_list args;
        va_start(args, method_id);
        ets_object res = native_interface->CallObjectMethodList(this, obj, method_id, args);
        va_end(args);
        return res;
    }
    ets_object CallObjectMethodList(ets_object obj, ets_method method_id, va_list args)
    {
        return native_interface->CallObjectMethodList(this, obj, method_id, args);
    }
    ets_object CallObjectMethodArray(ets_object obj, ets_method method_id, const ets_value *args)
    {
        return native_interface->CallObjectMethodArray(this, obj, method_id, args);
    }
    ets_boolean CallBooleanMethod(ets_object obj, ets_method method_id, ...)
    {
        va_list args;
        va_start(args, method_id);
        ets_boolean res = native_interface->CallBooleanMethodList(this, obj, method_id, args);
        va_end(args);
        return res;
    }
    ets_boolean CallBooleanMethodList(ets_object obj, ets_method method_id, va_list args)
    {
        return native_interface->CallBooleanMethodList(this, obj, method_id, args);
    }
    ets_boolean CallBooleanMethodArray(ets_object obj, ets_method method_id, const ets_value *args)
    {
        return native_interface->CallBooleanMethodArray(this, obj, method_id, args);
    }
    ets_byte CallByteMethod(ets_object obj, ets_method method_id, ...)
    {
        va_list args;
        va_start(args, method_id);
        ets_byte res = native_interface->CallByteMethodList(this, obj, method_id, args);
        va_end(args);
        return res;
    }
    ets_byte CallByteMethodList(ets_object obj, ets_method method_id, va_list args)
    {
        return native_interface->CallByteMethodList(this, obj, method_id, args);
    }
    ets_byte CallByteMethodArray(ets_object obj, ets_method method_id, const ets_value *args)
    {
        return native_interface->CallByteMethodArray(this, obj, method_id, args);
    }
    ets_char CallCharMethod(ets_object obj, ets_method method_id, ...)
    {
        va_list args;
        va_start(args, method_id);
        ets_char res = native_interface->CallCharMethodList(this, obj, method_id, args);
        va_end(args);
        return res;
    }
    ets_char CallCharMethodList(ets_object obj, ets_method method_id, va_list args)
    {
        return native_interface->CallCharMethodList(this, obj, method_id, args);
    }
    ets_char CallCharMethodArray(ets_object obj, ets_method method_id, const ets_value *args)
    {
        return native_interface->CallCharMethodArray(this, obj, method_id, args);
    }
    ets_short CallShortMethod(ets_object obj, ets_method method_id, ...)
    {
        va_list args;
        va_start(args, method_id);
        ets_short res = native_interface->CallShortMethodList(this, obj, method_id, args);
        va_end(args);
        return res;
    }
    ets_short CallShortMethodList(ets_object obj, ets_method method_id, va_list args)
    {
        return native_interface->CallShortMethodList(this, obj, method_id, args);
    }
    ets_short CallShortMethodArray(ets_object obj, ets_method method_id, const ets_value *args)
    {
        return native_interface->CallShortMethodArray(this, obj, method_id, args);
    }
    ets_int CallIntMethod(ets_object obj, ets_method method_id, ...)
    {
        va_list args;
        va_start(args, method_id);
        ets_int res = native_interface->CallIntMethodList(this, obj, method_id, args);
        va_end(args);
        return res;
    }
    ets_int CallIntMethodList(ets_object obj, ets_method method_id, va_list args)
    {
        return native_interface->CallIntMethodList(this, obj, method_id, args);
    }
    ets_int CallIntMethodArray(ets_object obj, ets_method method_id, const ets_value *args)
    {
        return native_interface->CallIntMethodArray(this, obj, method_id, args);
    }
    ets_long CallLongMethod(ets_object obj, ets_method method_id, ...)
    {
        va_list args;
        va_start(args, method_id);
        ets_long res = native_interface->CallLongMethodList(this, obj, method_id, args);
        va_end(args);
        return res;
    }
    ets_long CallLongMethodList(ets_object obj, ets_method method_id, va_list args)
    {
        return native_interface->CallLongMethodList(this, obj, method_id, args);
    }
    ets_long CallLongMethodArray(ets_object obj, ets_method method_id, const ets_value *args)
    {
        return native_interface->CallLongMethodArray(this, obj, method_id, args);
    }
    ets_float CallFloatMethod(ets_object obj, ets_method method_id, ...)
    {
        va_list args;
        va_start(args, method_id);
        ets_float res = native_interface->CallFloatMethodList(this, obj, method_id, args);
        va_end(args);
        return res;
    }
    ets_float CallFloatMethodList(ets_object obj, ets_method method_id, va_list args)
    {
        return native_interface->CallFloatMethodList(this, obj, method_id, args);
    }
    ets_float CallFloatMethodArray(ets_object obj, ets_method method_id, const ets_value *args)
    {
        return native_interface->CallFloatMethodArray(this, obj, method_id, args);
    }
    ets_double CallDoubleMethod(ets_object obj, ets_method method_id, ...)
    {
        va_list args;
        va_start(args, method_id);
        ets_double res = native_interface->CallDoubleMethodList(this, obj, method_id, args);
        va_end(args);
        return res;
    }
    ets_double CallDoubleMethodList(ets_object obj, ets_method method_id, va_list args)
    {
        return native_interface->CallDoubleMethodList(this, obj, method_id, args);
    }
    ets_double CallDoubleMethodArray(ets_object obj, ets_method method_id, const ets_value *args)
    {
        return native_interface->CallDoubleMethodArray(this, obj, method_id, args);
    }
    void CallVoidMethod(ets_object obj, ets_method method_id, ...)
    {
        va_list args;
        va_start(args, method_id);
        native_interface->CallVoidMethodList(this, obj, method_id, args);
        va_end(args);
    }
    void CallVoidMethodList(ets_object obj, ets_method method_id, va_list args)
    {
        native_interface->CallVoidMethodList(this, obj, method_id, args);
    }
    void CallVoidMethodArray(ets_object obj, ets_method method_id, const ets_value *args)
    {
        native_interface->CallVoidMethodArray(this, obj, method_id, args);
    }
    ets_object CallNonvirtualObjectMethod(ets_object obj, ets_class cls, ets_method method_id, ...)
    {
        va_list args;
        va_start(args, method_id);
        ets_object res = native_interface->CallNonvirtualObjectMethodList(this, obj, cls, method_id, args);
        va_end(args);
        return res;
    }
    ets_object CallNonvirtualObjectMethodList(ets_object obj, ets_class cls, ets_method method_id, va_list args)
    {
        return native_interface->CallNonvirtualObjectMethodList(this, obj, cls, method_id, args);
    }
    ets_object CallNonvirtualObjectMethodArray(ets_object obj, ets_class cls, ets_method method_id,
                                               const ets_value *args)
    {
        return native_interface->CallNonvirtualObjectMethodArray(this, obj, cls, method_id, args);
    }
    ets_boolean CallNonvirtualBooleanMethod(ets_object obj, ets_class cls, ets_method method_id, ...)
    {
        va_list args;
        va_start(args, method_id);
        ets_boolean res = native_interface->CallNonvirtualBooleanMethodList(this, obj, cls, method_id, args);
        va_end(args);
        return res;
    }
    ets_boolean CallNonvirtualBooleanMethodList(ets_object obj, ets_class cls, ets_method method_id, va_list args)
    {
        return native_interface->CallNonvirtualBooleanMethodList(this, obj, cls, method_id, args);
    }
    ets_boolean CallNonvirtualBooleanMethodArray(ets_object obj, ets_class cls, ets_method method_id,
                                                 const ets_value *args)
    {
        return native_interface->CallNonvirtualBooleanMethodArray(this, obj, cls, method_id, args);
    }
    ets_byte CallNonvirtualByteMethod(ets_object obj, ets_class cls, ets_method method_id, ...)
    {
        va_list args;
        va_start(args, method_id);
        ets_byte res = native_interface->CallNonvirtualByteMethodList(this, obj, cls, method_id, args);
        va_end(args);
        return res;
    }
    ets_byte CallNonvirtualByteMethodList(ets_object obj, ets_class cls, ets_method method_id, va_list args)
    {
        return native_interface->CallNonvirtualByteMethodList(this, obj, cls, method_id, args);
    }
    ets_byte CallNonvirtualByteMethodArray(ets_object obj, ets_class cls, ets_method method_id, const ets_value *args)
    {
        return native_interface->CallNonvirtualByteMethodArray(this, obj, cls, method_id, args);
    }
    ets_char CallNonvirtualCharMethod(ets_object obj, ets_class cls, ets_method method_id, ...)
    {
        va_list args;
        va_start(args, method_id);
        ets_char res = native_interface->CallNonvirtualCharMethodList(this, obj, cls, method_id, args);
        va_end(args);
        return res;
    }
    ets_char CallNonvirtualCharMethodList(ets_object obj, ets_class cls, ets_method method_id, va_list args)
    {
        return native_interface->CallNonvirtualCharMethodList(this, obj, cls, method_id, args);
    }
    ets_char CallNonvirtualCharMethodArray(ets_object obj, ets_class cls, ets_method method_id, const ets_value *args)
    {
        return native_interface->CallNonvirtualCharMethodArray(this, obj, cls, method_id, args);
    }
    ets_short CallNonvirtualShortMethod(ets_object obj, ets_class cls, ets_method method_id, ...)
    {
        va_list args;
        va_start(args, method_id);
        ets_short res = native_interface->CallNonvirtualShortMethodList(this, obj, cls, method_id, args);
        va_end(args);
        return res;
    }
    ets_short CallNonvirtualShortMethodList(ets_object obj, ets_class cls, ets_method method_id, va_list args)
    {
        return native_interface->CallNonvirtualShortMethodList(this, obj, cls, method_id, args);
    }
    ets_short CallNonvirtualShortMethodArray(ets_object obj, ets_class cls, ets_method method_id, const ets_value *args)
    {
        return native_interface->CallNonvirtualShortMethodArray(this, obj, cls, method_id, args);
    }
    ets_int CallNonvirtualIntMethod(ets_object obj, ets_class cls, ets_method method_id, ...)
    {
        va_list args;
        va_start(args, method_id);
        ets_int res = native_interface->CallNonvirtualIntMethodList(this, obj, cls, method_id, args);
        va_end(args);
        return res;
    }
    ets_int CallNonvirtualIntMethodList(ets_object obj, ets_class cls, ets_method method_id, va_list args)
    {
        return native_interface->CallNonvirtualIntMethodList(this, obj, cls, method_id, args);
    }
    ets_int CallNonvirtualIntMethodArray(ets_object obj, ets_class cls, ets_method method_id, const ets_value *args)
    {
        return native_interface->CallNonvirtualIntMethodArray(this, obj, cls, method_id, args);
    }
    ets_long CallNonvirtualLongMethod(ets_object obj, ets_class cls, ets_method method_id, ...)
    {
        va_list args;
        va_start(args, method_id);
        ets_long res = native_interface->CallNonvirtualLongMethodList(this, obj, cls, method_id, args);
        va_end(args);
        return res;
    }
    ets_long CallNonvirtualLongMethodList(ets_object obj, ets_class cls, ets_method method_id, va_list args)
    {
        return native_interface->CallNonvirtualLongMethodList(this, obj, cls, method_id, args);
    }
    ets_long CallNonvirtualLongMethodArray(ets_object obj, ets_class cls, ets_method method_id, const ets_value *args)
    {
        return native_interface->CallNonvirtualLongMethodArray(this, obj, cls, method_id, args);
    }
    ets_float CallNonvirtualFloatMethod(ets_object obj, ets_class cls, ets_method method_id, ...)
    {
        va_list args;
        va_start(args, method_id);
        ets_float res = native_interface->CallNonvirtualFloatMethodList(this, obj, cls, method_id, args);
        va_end(args);
        return res;
    }
    ets_float CallNonvirtualFloatMethodList(ets_object obj, ets_class cls, ets_method method_id, va_list args)
    {
        return native_interface->CallNonvirtualFloatMethodList(this, obj, cls, method_id, args);
    }
    ets_float CallNonvirtualFloatMethodArray(ets_object obj, ets_class cls, ets_method method_id, const ets_value *args)
    {
        return native_interface->CallNonvirtualFloatMethodArray(this, obj, cls, method_id, args);
    }
    ets_double CallNonvirtualDoubleMethod(ets_object obj, ets_class cls, ets_method method_id, ...)
    {
        va_list args;
        va_start(args, method_id);
        ets_double res = native_interface->CallNonvirtualDoubleMethodList(this, obj, cls, method_id, args);
        va_end(args);
        return res;
    }
    ets_double CallNonvirtualDoubleMethodList(ets_object obj, ets_class cls, ets_method method_id, va_list args)
    {
        return native_interface->CallNonvirtualDoubleMethodList(this, obj, cls, method_id, args);
    }
    ets_double CallNonvirtualDoubleMethodArray(ets_object obj, ets_class cls, ets_method method_id,
                                               const ets_value *args)
    {
        return native_interface->CallNonvirtualDoubleMethodArray(this, obj, cls, method_id, args);
    }
    void CallNonvirtualVoidMethod(ets_object obj, ets_class cls, ets_method method_id, ...)
    {
        va_list args;
        va_start(args, method_id);
        native_interface->CallNonvirtualVoidMethodList(this, obj, cls, method_id, args);
        va_end(args);
    }
    void CallNonvirtualVoidMethodList(ets_object obj, ets_class cls, ets_method method_id, va_list args)
    {
        native_interface->CallNonvirtualVoidMethodList(this, obj, cls, method_id, args);
    }
    void CallNonvirtualVoidMethodArray(ets_object obj, ets_class cls, ets_method method_id, const ets_value *args)
    {
        native_interface->CallNonvirtualVoidMethodArray(this, obj, cls, method_id, args);
    }
    ets_field Getp_field(ets_class cls, const char *name, const char *sig)
    {
        return native_interface->Getp_field(this, cls, name, sig);
    }
    ets_object GetObjectField(ets_object obj, ets_field p_field)
    {
        return native_interface->GetObjectField(this, obj, p_field);
    }
    ets_boolean GetBooleanField(ets_object obj, ets_field p_field)
    {
        return native_interface->GetBooleanField(this, obj, p_field);
    }
    ets_byte GetByteField(ets_object obj, ets_field p_field)
    {
        return native_interface->GetByteField(this, obj, p_field);
    }
    ets_char GetCharField(ets_object obj, ets_field p_field)
    {
        return native_interface->GetCharField(this, obj, p_field);
    }
    ets_short GetShortField(ets_object obj, ets_field p_field)
    {
        return native_interface->GetShortField(this, obj, p_field);
    }
    ets_int GetIntField(ets_object obj, ets_field p_field)
    {
        return native_interface->GetIntField(this, obj, p_field);
    }
    ets_long GetLongField(ets_object obj, ets_field p_field)
    {
        return native_interface->GetLongField(this, obj, p_field);
    }
    ets_float GetFloatField(ets_object obj, ets_field p_field)
    {
        return native_interface->GetFloatField(this, obj, p_field);
    }
    ets_double GetDoubleField(ets_object obj, ets_field p_field)
    {
        return native_interface->GetDoubleField(this, obj, p_field);
    }
    void SetObjectField(ets_object obj, ets_field p_field, ets_object value)
    {
        return native_interface->SetObjectField(this, obj, p_field, value);
    }
    void SetBooleanField(ets_object obj, ets_field p_field, ets_boolean value)
    {
        return native_interface->SetBooleanField(this, obj, p_field, value);
    }
    void SetByteField(ets_object obj, ets_field p_field, ets_byte value)
    {
        return native_interface->SetByteField(this, obj, p_field, value);
    }
    void SetCharField(ets_object obj, ets_field p_field, ets_char value)
    {
        return native_interface->SetCharField(this, obj, p_field, value);
    }
    void SetShortField(ets_object obj, ets_field p_field, ets_short value)
    {
        return native_interface->SetShortField(this, obj, p_field, value);
    }
    void SetIntField(ets_object obj, ets_field p_field, ets_int value)
    {
        return native_interface->SetIntField(this, obj, p_field, value);
    }
    void SetLongField(ets_object obj, ets_field p_field, ets_long value)
    {
        return native_interface->SetLongField(this, obj, p_field, value);
    }
    void SetFloatField(ets_object obj, ets_field p_field, ets_float value)
    {
        return native_interface->SetFloatField(this, obj, p_field, value);
    }
    void SetDoubleField(ets_object obj, ets_field p_field, ets_double value)
    {
        return native_interface->SetDoubleField(this, obj, p_field, value);
    }
    ets_method GetStaticp_method(ets_class cls, const char *name, const char *sig)
    {
        return native_interface->GetStaticp_method(this, cls, name, sig);
    }
    ets_object CallStaticObjectMethod(ets_class cls, ets_method method_id, ...)
    {
        va_list args;
        va_start(args, method_id);
        ets_object res = native_interface->CallStaticObjectMethodList(this, cls, method_id, args);
        va_end(args);
        return res;
    }
    ets_object CallStaticObjectMethodList(ets_class cls, ets_method method_id, va_list args)
    {
        return native_interface->CallStaticObjectMethodList(this, cls, method_id, args);
    }
    ets_object CallStaticObjectMethodArray(ets_class cls, ets_method method_id, ets_value *args)
    {
        return native_interface->CallStaticObjectMethodArray(this, cls, method_id, args);
    }
    ets_boolean CallStaticBooleanMethod(ets_class cls, ets_method method_id, ...)
    {
        va_list args;
        va_start(args, method_id);
        ets_boolean res = native_interface->CallStaticBooleanMethodList(this, cls, method_id, args);
        va_end(args);
        return res;
    }
    ets_boolean CallStaticBooleanMethodList(ets_class cls, ets_method method_id, va_list args)
    {
        return native_interface->CallStaticBooleanMethodList(this, cls, method_id, args);
    }
    ets_boolean CallStaticBooleanMethodArray(ets_class cls, ets_method method_id, ets_value *args)
    {
        return native_interface->CallStaticBooleanMethodArray(this, cls, method_id, args);
    }
    ets_byte CallStaticByteMethod(ets_class cls, ets_method method_id, ...)
    {
        va_list args;
        va_start(args, method_id);
        ets_byte res = native_interface->CallStaticByteMethodList(this, cls, method_id, args);
        va_end(args);
        return res;
    }
    ets_byte CallStaticByteMethodList(ets_class cls, ets_method method_id, va_list args)
    {
        return native_interface->CallStaticByteMethodList(this, cls, method_id, args);
    }
    ets_byte CallStaticByteMethodArray(ets_class cls, ets_method method_id, ets_value *args)
    {
        return native_interface->CallStaticByteMethodArray(this, cls, method_id, args);
    }
    ets_char CallStaticCharMethod(ets_class cls, ets_method method_id, ...)
    {
        va_list args;
        va_start(args, method_id);
        ets_char res = native_interface->CallStaticCharMethodList(this, cls, method_id, args);
        va_end(args);
        return res;
    }
    ets_char CallStaticCharMethodList(ets_class cls, ets_method method_id, va_list args)
    {
        return native_interface->CallStaticCharMethodList(this, cls, method_id, args);
    }
    ets_char CallStaticCharMethodArray(ets_class cls, ets_method method_id, ets_value *args)
    {
        return native_interface->CallStaticCharMethodArray(this, cls, method_id, args);
    }
    ets_short CallStaticShortMethod(ets_class cls, ets_method method_id, ...)
    {
        va_list args;
        va_start(args, method_id);
        ets_short res = native_interface->CallStaticShortMethodList(this, cls, method_id, args);
        va_end(args);
        return res;
    }
    ets_short CallStaticShortMethodList(ets_class cls, ets_method method_id, va_list args)
    {
        return native_interface->CallStaticShortMethodList(this, cls, method_id, args);
    }
    ets_short CallStaticShortMethodArray(ets_class cls, ets_method method_id, ets_value *args)
    {
        return native_interface->CallStaticShortMethodArray(this, cls, method_id, args);
    }
    ets_int CallStaticIntMethod(ets_class cls, ets_method method_id, ...)
    {
        va_list args;
        va_start(args, method_id);
        ets_int res = native_interface->CallStaticIntMethodList(this, cls, method_id, args);
        va_end(args);
        return res;
    }
    ets_int CallStaticIntMethodList(ets_class cls, ets_method method_id, va_list args)
    {
        return native_interface->CallStaticIntMethodList(this, cls, method_id, args);
    }
    ets_int CallStaticIntMethodArray(ets_class cls, ets_method method_id, ets_value *args)
    {
        return native_interface->CallStaticIntMethodArray(this, cls, method_id, args);
    }
    ets_long CallStaticLongMethod(ets_class cls, ets_method method_id, ...)
    {
        va_list args;
        va_start(args, method_id);
        ets_long res = native_interface->CallStaticLongMethodList(this, cls, method_id, args);
        va_end(args);
        return res;
    }
    ets_long CallStaticLongMethodList(ets_class cls, ets_method method_id, va_list args)
    {
        return native_interface->CallStaticLongMethodList(this, cls, method_id, args);
    }
    ets_long CallStaticLongMethodArray(ets_class cls, ets_method method_id, ets_value *args)
    {
        return native_interface->CallStaticLongMethodArray(this, cls, method_id, args);
    }
    ets_float CallStaticFloatMethod(ets_class cls, ets_method method_id, ...)
    {
        va_list args;
        va_start(args, method_id);
        ets_float res = native_interface->CallStaticFloatMethodList(this, cls, method_id, args);
        va_end(args);
        return res;
    }
    ets_float CallStaticFloatMethodList(ets_class cls, ets_method method_id, va_list args)
    {
        return native_interface->CallStaticFloatMethodList(this, cls, method_id, args);
    }
    ets_float CallStaticFloatMethodArray(ets_class cls, ets_method method_id, ets_value *args)
    {
        return native_interface->CallStaticFloatMethodArray(this, cls, method_id, args);
    }
    ets_double CallStaticDoubleMethod(ets_class cls, ets_method method_id, ...)
    {
        va_list args;
        va_start(args, method_id);
        ets_double res = native_interface->CallStaticDoubleMethodList(this, cls, method_id, args);
        va_end(args);
        return res;
    }
    ets_double CallStaticDoubleMethodList(ets_class cls, ets_method method_id, va_list args)
    {
        return native_interface->CallStaticDoubleMethodList(this, cls, method_id, args);
    }
    ets_double CallStaticDoubleMethodArray(ets_class cls, ets_method method_id, ets_value *args)
    {
        return native_interface->CallStaticDoubleMethodArray(this, cls, method_id, args);
    }
    void CallStaticVoidMethod(ets_class cls, ets_method method_id, ...)
    {
        va_list args;
        va_start(args, method_id);
        native_interface->CallStaticVoidMethodList(this, cls, method_id, args);
        va_end(args);
    }
    void CallStaticVoidMethodList(ets_class cls, ets_method method_id, va_list args)
    {
        native_interface->CallStaticVoidMethodList(this, cls, method_id, args);
    }
    void CallStaticVoidMethodArray(ets_class cls, ets_method method_id, ets_value *args)
    {
        native_interface->CallStaticVoidMethodArray(this, cls, method_id, args);
    }
    ets_field GetStaticp_field(ets_class cls, const char *name, const char *sig)
    {
        return native_interface->GetStaticp_field(this, cls, name, sig);
    }
    ets_object GetStaticObjectField(ets_class cls, ets_field p_field)
    {
        return native_interface->GetStaticObjectField(this, cls, p_field);
    }
    ets_boolean GetStaticBooleanField(ets_class cls, ets_field p_field)
    {
        return native_interface->GetStaticBooleanField(this, cls, p_field);
    }
    ets_byte GetStaticByteField(ets_class cls, ets_field p_field)
    {
        return native_interface->GetStaticByteField(this, cls, p_field);
    }
    ets_char GetStaticCharField(ets_class cls, ets_field p_field)
    {
        return native_interface->GetStaticCharField(this, cls, p_field);
    }
    ets_short GetStaticShortField(ets_class cls, ets_field p_field)
    {
        return native_interface->GetStaticShortField(this, cls, p_field);
    }
    ets_int GetStaticIntField(ets_class cls, ets_field p_field)
    {
        return native_interface->GetStaticIntField(this, cls, p_field);
    }
    ets_long GetStaticLongField(ets_class cls, ets_field p_field)
    {
        return native_interface->GetStaticLongField(this, cls, p_field);
    }
    ets_float GetStaticFloatField(ets_class cls, ets_field p_field)
    {
        return native_interface->GetStaticFloatField(this, cls, p_field);
    }
    ets_double GetStaticDoubleField(ets_class cls, ets_field p_field)
    {
        return native_interface->GetStaticDoubleField(this, cls, p_field);
    }
    void SetStaticObjectField(ets_class cls, ets_field p_field, ets_object value)
    {
        return native_interface->SetStaticObjectField(this, cls, p_field, value);
    }
    void SetStaticBooleanField(ets_class cls, ets_field p_field, ets_boolean value)
    {
        return native_interface->SetStaticBooleanField(this, cls, p_field, value);
    }
    void SetStaticByteField(ets_class cls, ets_field p_field, ets_byte value)
    {
        return native_interface->SetStaticByteField(this, cls, p_field, value);
    }
    void SetStaticCharField(ets_class cls, ets_field p_field, ets_char value)
    {
        return native_interface->SetStaticCharField(this, cls, p_field, value);
    }
    void SetStaticShortField(ets_class cls, ets_field p_field, ets_short value)
    {
        return native_interface->SetStaticShortField(this, cls, p_field, value);
    }
    void SetStaticIntField(ets_class cls, ets_field p_field, ets_int value)
    {
        return native_interface->SetStaticIntField(this, cls, p_field, value);
    }
    void SetStaticLongField(ets_class cls, ets_field p_field, ets_long value)
    {
        return native_interface->SetStaticLongField(this, cls, p_field, value);
    }
    void SetStaticFloatField(ets_class cls, ets_field p_field, ets_float value)
    {
        return native_interface->SetStaticFloatField(this, cls, p_field, value);
    }
    void SetStaticDoubleField(ets_class cls, ets_field p_field, ets_double value)
    {
        return native_interface->SetStaticDoubleField(this, cls, p_field, value);
    }
    ets_string NewString(const ets_char *unicode_chars, ets_size len)
    {
        return native_interface->NewString(this, unicode_chars, len);
    }
    ets_size GetStringLength(ets_string string)
    {
        return native_interface->GetStringLength(this, string);
    }
    const ets_char *GetStringChars(ets_string string, ets_boolean *is_copy)
    {
        return native_interface->GetStringChars(this, string, is_copy);
    }
    void ReleaseStringChars(ets_string string, const ets_char *chars)
    {
        native_interface->ReleaseStringChars(this, string, chars);
    }
    ets_string NewStringUTF(const char *bytes)
    {
        return native_interface->NewStringUTF(this, bytes);
    }
    ets_size GetStringUTFLength(ets_string string)
    {
        return native_interface->GetStringUTFLength(this, string);
    }
    const char *GetStringUTFChars(ets_string string, ets_boolean *is_copy)
    {
        return native_interface->GetStringUTFChars(this, string, is_copy);
    }
    void ReleaseStringUTFChars(ets_string string, const char *chars)
    {
        native_interface->ReleaseStringUTFChars(this, string, chars);
    }
    ets_size GetArrayLength(ets_array array)
    {
        return native_interface->GetArrayLength(this, array);
    }
    ets_objectArray NewObjectsArray(ets_size length, ets_class element_class, ets_object initial_element)
    {
        return native_interface->NewObjectsArray(this, length, element_class, initial_element);
    }
    ets_object GetObjectArrayElement(ets_objectArray array, ets_size index)
    {
        return native_interface->GetObjectArrayElement(this, array, index);
    }

    void SetObjectArrayElement(ets_objectArray array, ets_size index, ets_object value)
    {
        native_interface->SetObjectArrayElement(this, array, index, value);
    }

    // SetObjectArrayElement,
    ets_booleanArray NewBooleanArray(ets_size length)
    {
        return native_interface->NewBooleanArray(this, length);
    }
    ets_byteArray NewByteArray(ets_size length)
    {
        return native_interface->NewByteArray(this, length);
    }
    ets_charArray NewCharArray(ets_size length)
    {
        return native_interface->NewCharArray(this, length);
    }
    ets_shortArray NewShortArray(ets_size length)
    {
        return native_interface->NewShortArray(this, length);
    }
    ets_intArray NewIntArray(ets_size length)
    {
        return native_interface->NewIntArray(this, length);
    }
    ets_longArray NewLongArray(ets_size length)
    {
        return native_interface->NewLongArray(this, length);
    }
    ets_floatArray NewFloatArray(ets_size length)
    {
        return native_interface->NewFloatArray(this, length);
    }
    ets_doubleArray NewDoubleArray(ets_size length)
    {
        return native_interface->NewDoubleArray(this, length);
    }
    ets_boolean *PinBooleanArray(ets_booleanArray array)
    {
        return native_interface->PinBooleanArray(this, array);
    }
    ets_byte *PinByteArray(ets_byteArray array)
    {
        return native_interface->PinByteArray(this, array);
    }
    ets_char *PinCharArray(ets_charArray array)
    {
        return native_interface->PinCharArray(this, array);
    }
    ets_short *PinShortArray(ets_shortArray array)
    {
        return native_interface->PinShortArray(this, array);
    }
    ets_int *PinIntArray(ets_intArray array)
    {
        return native_interface->PinIntArray(this, array);
    }
    ets_long *PinLongArray(ets_longArray array)
    {
        return native_interface->PinLongArray(this, array);
    }
    ets_float *PinFloatArray(ets_floatArray array)
    {
        return native_interface->PinFloatArray(this, array);
    }
    ets_double *PinDoubleArray(ets_doubleArray array)
    {
        return native_interface->PinDoubleArray(this, array);
    }
    void UnpinBooleanArray(ets_booleanArray array)
    {
        return native_interface->UnpinBooleanArray(this, array);
    }
    void UnpinByteArray(ets_byteArray array)
    {
        return native_interface->UnpinByteArray(this, array);
    }
    void UnpinCharArray(ets_charArray array)
    {
        return native_interface->UnpinCharArray(this, array);
    }
    void UnpinShortArray(ets_shortArray array)
    {
        return native_interface->UnpinShortArray(this, array);
    }
    void UnpinIntArray(ets_intArray array)
    {
        return native_interface->UnpinIntArray(this, array);
    }
    void UnpinLongArray(ets_longArray array)
    {
        return native_interface->UnpinLongArray(this, array);
    }
    void UnpinFloatArray(ets_floatArray array)
    {
        return native_interface->UnpinFloatArray(this, array);
    }
    void UnpinDoubleArray(ets_doubleArray array)
    {
        return native_interface->UnpinDoubleArray(this, array);
    }
    void GetBooleanArrayRegion(ets_booleanArray array, ets_size start, ets_size len, ets_boolean *buf)
    {
        return native_interface->GetBooleanArrayRegion(this, array, start, len, buf);
    }
    void GetByteArrayRegion(ets_byteArray array, ets_size start, ets_size len, ets_byte *buf)
    {
        return native_interface->GetByteArrayRegion(this, array, start, len, buf);
    }
    void GetCharArrayRegion(ets_charArray array, ets_size start, ets_size len, ets_char *buf)
    {
        return native_interface->GetCharArrayRegion(this, array, start, len, buf);
    }
    void GetShortArrayRegion(ets_shortArray array, ets_size start, ets_size len, ets_short *buf)
    {
        return native_interface->GetShortArrayRegion(this, array, start, len, buf);
    }
    void GetIntArrayRegion(ets_intArray array, ets_size start, ets_size len, ets_int *buf)
    {
        return native_interface->GetIntArrayRegion(this, array, start, len, buf);
    }
    void GetLongArrayRegion(ets_longArray array, ets_size start, ets_size len, ets_long *buf)
    {
        return native_interface->GetLongArrayRegion(this, array, start, len, buf);
    }
    void GetFloatArrayRegion(ets_floatArray array, ets_size start, ets_size len, ets_float *buf)
    {
        return native_interface->GetFloatArrayRegion(this, array, start, len, buf);
    }
    void GetDoubleArrayRegion(ets_doubleArray array, ets_size start, ets_size len, ets_double *buf)
    {
        return native_interface->GetDoubleArrayRegion(this, array, start, len, buf);
    }
    void SetBooleanArrayRegion(ets_booleanArray array, ets_size start, ets_size length, const ets_boolean *buf)
    {
        native_interface->SetBooleanArrayRegion(this, array, start, length, buf);
    }
    void SetByteArrayRegion(ets_byteArray array, ets_size start, ets_size length, const ets_byte *buf)
    {
        native_interface->SetByteArrayRegion(this, array, start, length, buf);
    }
    void SetCharArrayRegion(ets_charArray array, ets_size start, ets_size length, const ets_char *buf)
    {
        native_interface->SetCharArrayRegion(this, array, start, length, buf);
    }
    void SetShortArrayRegion(ets_shortArray array, ets_size start, ets_size length, const ets_short *buf)
    {
        native_interface->SetShortArrayRegion(this, array, start, length, buf);
    }
    void SetIntArrayRegion(ets_intArray array, ets_size start, ets_size length, const ets_int *buf)
    {
        native_interface->SetIntArrayRegion(this, array, start, length, buf);
    }
    void SetLongArrayRegion(ets_longArray array, ets_size start, ets_size length, const ets_long *buf)
    {
        native_interface->SetLongArrayRegion(this, array, start, length, buf);
    }
    void SetFloatArrayRegion(ets_floatArray array, ets_size start, ets_size length, const ets_float *buf)
    {
        native_interface->SetFloatArrayRegion(this, array, start, length, buf);
    }
    void SetDoubleArrayRegion(ets_doubleArray array, ets_size start, ets_size length, const ets_double *buf)
    {
        native_interface->SetDoubleArrayRegion(this, array, start, length, buf);
    }
    ets_int RegisterNatives(ets_class cls, const EtsNativeMethod *methods, ets_int nMethods)
    {
        return native_interface->RegisterNatives(this, cls, methods, nMethods);
    }
    ets_int UnregisterNatives(ets_class cls)
    {
        return native_interface->UnregisterNatives(this, cls);
    }
    ets_int GetEtsVM(EtsVM **vm)
    {
        return native_interface->GetEtsVM(this, vm);
    }
    void GetStringRegion(ets_string str, ets_size start, ets_size len, ets_char *buf)
    {
        native_interface->GetStringRegion(this, str, start, len, buf);
    }
    void GetStringUTFRegion(ets_string str, ets_size start, ets_size len, char *buf)
    {
        native_interface->GetStringUTFRegion(this, str, start, len, buf);
    }
    ets_weak NewWeakGlobalRef(ets_object obj)
    {
        return native_interface->NewWeakGlobalRef(this, obj);
    }
    void DeleteWeakGlobalRef(ets_weak obj)
    {
        native_interface->DeleteWeakGlobalRef(this, obj);
    }
    ets_boolean ErrorCheck()
    {
        return native_interface->ErrorCheck(this);
    }
    // NewDirectByteBuffer,
    // GetDirectBufferAddress,
    // GetDirectBufferCapacity,
    ets_objectRefType GetObjectRefType(ets_object obj)
    {
        return native_interface->GetObjectRefType(this, obj);
    }

    // Promise
    ets_status PromiseCreate(ets_deferred *deferred, ets_object *promise)
    {
        return native_interface->PromiseCreate(this, deferred, promise);
    }
    ets_status DeferredResolve(ets_deferred deferred, ets_object resolution)
    {
        return native_interface->DeferredResolve(this, deferred, resolution);
    }
    ets_status DeferredReject(ets_deferred deferred, ets_object rejection)
    {
        return native_interface->DeferredReject(this, deferred, rejection);
    }
#endif
};

// NOLINTEND(modernize-use-using, readability-identifier-naming, cppcoreguidelines-pro-type-vararg)

#endif  // PANDA_RUNTIME_INTEROP_ETS_NAPI_H
