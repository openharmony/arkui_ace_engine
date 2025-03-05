/**
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef __ANI_H__
#define __ANI_H__
// NOLINTBEGIN

#ifdef __cplusplus
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#else
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#endif

#define ANI_VERSION_1 1

#define ANI_FALSE 0
#define ANI_TRUE 1

typedef size_t ani_size;

// Primitive types:
typedef uint8_t ani_boolean;
typedef uint32_t ani_char;
typedef int8_t ani_byte;
typedef int16_t ani_short;
typedef int32_t ani_int;
typedef int64_t ani_long;
typedef float ani_float;
typedef double ani_double;

// Reference types:
#ifdef __cplusplus
class __ani_ref {};
class __ani_module : public __ani_ref {};
class __ani_namespace : public __ani_ref {};
class __ani_object : public __ani_ref {};
class __ani_fn_object : public __ani_object {};
class __ani_enum_value : public __ani_object {};
class __ani_error : public __ani_object {};
class __ani_promise : public __ani_object {};
class __ani_tuple_value : public __ani_object {};
class __ani_type : public __ani_object {};
class __ani_arraybuffer : public __ani_object {};
class __ani_string : public __ani_object {};
class __ani_stringliteral : public __ani_string {};
class __ani_class : public __ani_type {};
class __ani_enum : public __ani_type {};
class __ani_tuple : public __ani_type {};
class __ani_fixedarray : public __ani_object {};
class __ani_fixedarray_boolean : public __ani_fixedarray {};
class __ani_fixedarray_char : public __ani_fixedarray {};
class __ani_fixedarray_byte : public __ani_fixedarray {};
class __ani_fixedarray_short : public __ani_fixedarray {};
class __ani_fixedarray_int : public __ani_fixedarray {};
class __ani_fixedarray_long : public __ani_fixedarray {};
class __ani_fixedarray_float : public __ani_fixedarray {};
class __ani_fixedarray_double : public __ani_fixedarray {};
class __ani_fixedarray_ref : public __ani_fixedarray {};
typedef __ani_ref *ani_ref;
typedef __ani_module *ani_module;
typedef __ani_namespace *ani_namespace;
typedef __ani_object *ani_object;
typedef __ani_fn_object *ani_fn_object;
typedef __ani_enum_value *ani_enum_value;
typedef __ani_error *ani_error;
typedef __ani_promise *ani_promise;
typedef __ani_tuple_value *ani_tuple_value;
typedef __ani_type *ani_type;
typedef __ani_arraybuffer *ani_arraybuffer;
typedef __ani_string *ani_string;
typedef __ani_stringliteral *ani_stringliteral;
typedef __ani_class *ani_class;
typedef __ani_enum *ani_enum;
typedef __ani_tuple *ani_tuple;
typedef __ani_fixedarray *ani_fixedarray;
typedef __ani_fixedarray_boolean *ani_fixedarray_boolean;
typedef __ani_fixedarray_char *ani_fixedarray_char;
typedef __ani_fixedarray_byte *ani_fixedarray_byte;
typedef __ani_fixedarray_short *ani_fixedarray_short;
typedef __ani_fixedarray_int *ani_fixedarray_int;
typedef __ani_fixedarray_long *ani_fixedarray_long;
typedef __ani_fixedarray_float *ani_fixedarray_float;
typedef __ani_fixedarray_double *ani_fixedarray_double;
typedef __ani_fixedarray_ref *ani_fixedarray_ref;
#else   // __cplusplus
struct __ani_ref;
typedef struct __ani_ref *ani_ref;
typedef ani_ref ani_module;
typedef ani_ref ani_namespace;
typedef ani_ref ani_object;
typedef ani_object ani_fn_object;
typedef ani_object ani_enum_value;
typedef ani_object ani_error;
typedef ani_object ani_promise;
typedef ani_object ani_tuple_value;
typedef ani_object ani_type;
typedef ani_object ani_arraybuffer;
typedef ani_object ani_string;
typedef ani_string ani_stringliteral;
typedef ani_type ani_class;
typedef ani_type ani_enum;
typedef ani_type ani_tuple;
typedef ani_object ani_fixedarray;
typedef ani_fixedarray ani_fixedarray_boolean;
typedef ani_fixedarray ani_fixedarray_char;
typedef ani_fixedarray ani_fixedarray_byte;
typedef ani_fixedarray ani_fixedarray_short;
typedef ani_fixedarray ani_fixedarray_int;
typedef ani_fixedarray ani_fixedarray_long;
typedef ani_fixedarray ani_fixedarray_float;
typedef ani_fixedarray ani_fixedarray_double;
typedef ani_fixedarray ani_fixedarray_ref;
#endif  // __cplusplus

struct __ani_gref;
typedef struct __ani_gref *ani_gref;

struct __ani_wref;
typedef struct __ani_wref *ani_wref;

struct __ani_variable;
typedef struct __ani_variable *ani_variable;

struct __ani_function;
typedef struct __ani_function *ani_function;

struct __ani_field;
typedef struct __ani_field *ani_field;

struct __ani_static_field;
typedef struct __ani_satic_field *ani_static_field;

struct __ani_property;
typedef struct __ani_property *ani_property;

struct __ani_method;
typedef struct __ani_method *ani_method;

struct __ani_static_method;
typedef struct __ani_static_method *ani_static_method;

struct __ani_cls_slot;
typedef struct __ani_cls_slot *ani_cls_slot;

typedef void (*ani_finalizer)(void *data, void *hint);

typedef enum {
    ANI_KIND_BOOLEAN,
    ANI_KIND_CHAR,
    ANI_KIND_BYTE,
    ANI_KIND_SHORT,
    ANI_KIND_INT,
    ANI_KIND_LONG,
    ANI_KIND_FLOAT,
    ANI_KIND_DOUBLE,
    ANI_KIND_REF,
} ani_kind;

typedef union {
    ani_boolean z;
    ani_char c;
    ani_byte b;
    ani_short s;
    ani_int i;
    ani_long l;
    ani_float f;
    ani_double d;
    ani_ref r;
} ani_value;

typedef struct {
    const char *name;
    const char *signature;
    const void *pointer;
} ani_native_function;

#ifdef __cplusplus
typedef struct __ani_vm ani_vm;
typedef struct __ani_env ani_env;
#else
typedef const struct __ani_vm_api *ani_vm;
typedef const struct __ani_interaction_api *ani_env;
#endif

typedef enum {
    ANI_OK,
    ANI_ERROR,
    ANI_INVALID_ARGS,
    ANI_INVALID_TYPE,
    ANI_INVALID_DESCRIPTOR,
    ANI_PENDING_ERROR,
    ANI_NOT_FOUND,
    ANI_ALREADY_BINDED,
    ANI_OUT_OF_REF,
    ANI_OUT_OF_MEMORY,
    ANI_OUT_OF_RANGE,
    ANI_BUFFER_TO_SMALL,
    // NOTE: Add necessary status codes
} ani_status;

struct __ani_vm_api {
    void *reserved0;
    void *reserved1;
    void *reserved2;
    void *reserved3;

    ani_status (*DestroyVM)(ani_vm *vm);
    ani_status (*GetEnv)(ani_vm *vm, uint32_t version, ani_env **result);
    ani_status (*AttachThread)(ani_vm *vm, void *params, ani_env **result);
    ani_status (*DetachThread)(ani_vm *vm);
};

typedef struct {
    const char *option;
    void *option_data;
} ani_vm_option;

#define ANI_EXPORT __attribute__((visibility("default")))

#ifdef __cplusplus
extern "C" {
#endif

ANI_EXPORT ani_status ANI_CreateVM(uint32_t version, size_t nr_options, const ani_vm_option *options, ani_vm **result);
ANI_EXPORT ani_status ANI_GetCreatedVMs(ani_vm **vms_buffer, ani_size vms_buffer_length, ani_size *result);

// Prototypes of exported functions for a shared library.
ANI_EXPORT ani_status ANI_Constructor(ani_vm *vm, uint32_t *result);
ANI_EXPORT ani_status ANI_Destructor(ani_vm *vm);

#ifdef __cplusplus
}
#endif

struct __ani_interaction_api {
    void *reserved0;
    void *reserved1;
    void *reserved2;
    void *reserved3;

    /**
     * @brief Retrieves the version information.
     *
     * This function retrieves the version information and stores it in the result parameter.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[out] result A pointer to a variable where the version information will be stored.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*GetVersion)(ani_env *env, uint32_t *result);

    /**
     * @brief Retrieves the Virtual Machine (VM) instance.
     *
     * This function retrieves the VM instance and stores it in the result parameter.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[out] result A pointer to the VM instance to be populated.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*GetVM)(ani_env *env, ani_vm **result);

    /**
     * @brief Checks if a reference is an object.
     *
     * This function determines whether the specified reference represents an object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] ref The reference to check.
     * @param[out] result A pointer to store the boolean result (true if the reference is an object, false otherwise).
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Reference_IsObject)(ani_env *env, ani_ref ref, ani_boolean *result);

    /**
     * @brief Checks if a reference is a functional object.
     *
     * This function determines whether the specified reference represents a functional object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] ref The reference to check.
     * @param[out] result A pointer to store the boolean result (true if the reference is a functional object, false
     * otherwise).
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Reference_IsFunctionalObject)(ani_env *env, ani_ref ref, ani_boolean *result);

    /**
     * @brief Checks if a reference is an enum.
     *
     * This function determines whether the specified reference represents an enum.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] ref The reference to check.
     * @param[out] result A pointer to store the boolean result (true if the reference is an enum, false otherwise).
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Reference_IsEnum)(ani_env *env, ani_ref ref, ani_boolean *result);

    /**
     * @brief Checks if a reference is a tuple.
     *
     * This function determines whether the specified reference represents a tuple.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] ref The reference to check.
     * @param[out] result A pointer to store the boolean result (true if the reference is a tuple, false otherwise).
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Reference_IsTuple)(ani_env *env, ani_ref ref, ani_boolean *result);

    /**
     * @brief Checks if a reference is a string.
     *
     * This function determines whether the specified reference represents a string.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] ref The reference to check.
     * @param[out] result A pointer to store the boolean result (true if the reference is a string, false otherwise).
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Reference_IsString)(ani_env *env, ani_ref ref, ani_boolean *result);

    /**
     * @brief Checks if a reference is a string literal.
     *
     * This function determines whether the specified reference represents a string literal.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] ref The reference to check.
     * @param[out] result A pointer to store the boolean result (true if the reference is a string literal, false
     * otherwise).
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Reference_IsStringLiteral)(ani_env *env, ani_ref ref, ani_boolean *result);

    /**
     * @brief Checks if a reference is a fixed array.
     *
     * This function determines whether the specified reference represents a fixed array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] ref The reference to check.
     * @param[out] result A pointer to store the boolean result (true if the reference is a fixed array, false
     * otherwise).
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Reference_IsFixedArray)(ani_env *env, ani_ref ref, ani_boolean *result);

    /**
     * @brief Checks if a reference is a fixed array of booleans.
     *
     * This function determines whether the specified reference represents a fixed array of booleans.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] ref The reference to check.
     * @param[out] result A pointer to store the boolean result (true if the reference is a fixed array of booleans,
     * false otherwise).
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Reference_IsFixedArray_Boolean)(ani_env *env, ani_ref ref, ani_boolean *result);

    /**
     * @brief Checks if a reference is a fixed array of chars.
     *
     * This function determines whether the specified reference represents a fixed array of chars.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] ref The reference to check.
     * @param[out] result A pointer to store the char result (true if the reference is a fixed array of chars, false
     * otherwise).
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Reference_IsFixedArray_Char)(ani_env *env, ani_ref ref, ani_boolean *result);

    /**
     * @brief Checks if a reference is a fixed array of bytes.
     *
     * This function determines whether the specified reference represents a fixed array of bytes.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] ref The reference to check.
     * @param[out] result A pointer to store the byte result (true if the reference is a fixed array of bytes, false
     * otherwise).
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Reference_IsFixedArray_Byte)(ani_env *env, ani_ref ref, ani_boolean *result);

    /**
     * @brief Checks if a reference is a fixed array of shorts.
     *
     * This function determines whether the specified reference represents a fixed array of shorts.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] ref The reference to check.
     * @param[out] result A pointer to store the short result (true if the reference is a fixed array of shorts, false
     * otherwise).
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Reference_IsFixedArray_Short)(ani_env *env, ani_ref ref, ani_boolean *result);

    /**
     * @brief Checks if a reference is a fixed array of integers.
     *
     * This function determines whether the specified reference represents a fixed array of integers.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] ref The reference to check.
     * @param[out] result A pointer to store the integer result (true if the reference is a fixed array of integers,
     * false otherwise).
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Reference_IsFixedArray_Int)(ani_env *env, ani_ref ref, ani_boolean *result);

    /**
     * @brief Checks if a reference is a fixed array of longs.
     *
     * This function determines whether the specified reference represents a fixed array of longs.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] ref The reference to check.
     * @param[out] result A pointer to store the long result (true if the reference is a fixed array of longs, false
     * otherwise).
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Reference_IsFixedArray_Long)(ani_env *env, ani_ref ref, ani_boolean *result);

    /**
     * @brief Checks if a reference is a fixed array of floats.
     *
     * This function determines whether the specified reference represents a fixed array of floats.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] ref The reference to check.
     * @param[out] result A pointer to store the float result (true if the reference is a fixed array of floats, false
     * otherwise).
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Reference_IsFixedArray_Float)(ani_env *env, ani_ref ref, ani_boolean *result);

    /**
     * @brief Checks if a reference is a fixed array of doubles.
     *
     * This function determines whether the specified reference represents a fixed array of doubles.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] ref The reference to check.
     * @param[out] result A pointer to store the double result (true if the reference is a fixed array of doubles, false
     * otherwise).
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Reference_IsFixedArray_Double)(ani_env *env, ani_ref ref, ani_boolean *result);

    /**
     * @brief Checks if a reference is a fixed array of references.
     *
     * This function determines whether the specified reference represents a fixed array of references.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] ref The reference to check.
     * @param[out] result A pointer to store the boolean result (true if the reference is a fixed array of references,
     * false otherwise).
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Reference_IsFixedArray_Ref)(ani_env *env, ani_ref ref, ani_boolean *result);

    /**
     * @brief Creates a new object of a specified class using a constructor method.
     *
     * This function creates a new object of the given class and calls the specified constructor method with variadic
     * arguments.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class of the object to create.
     * @param[in] method The constructor method to invoke.
     * @param[in] ... Variadic arguments to pass to the constructor method.
     * @param[out] result A pointer to store the object return value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_New)(ani_env *env, ani_class cls, ani_method method, ani_object *result, ...);

    /**
     * @brief Creates a new object of a specified class using a constructor method (array-based).
     *
     * This function creates a new object of the given class and calls the specified constructor method with arguments
     * provided in an array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class of the object to create.
     * @param[in] method The constructor method to invoke.
     * @param[in] args An array of arguments to pass to the constructor method.
     * @param[out] result A pointer to store the object return value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_New_A)(ani_env *env, ani_class cls, ani_method method, ani_object *result,
                               const ani_value *args);

    /**
     * @brief Creates a new object of a specified class using a constructor method (variadic arguments).
     *
     * This function creates a new object of the given class and calls the specified constructor method with a `va_list`
     * of arguments.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class of the object to create.
     * @param[in] method The constructor method to invoke.
     * @param[in] args A `va_list` of arguments to pass to the constructor method.
     * @param[out] result A pointer to store the object return value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_New_V)(ani_env *env, ani_class cls, ani_method method, ani_object *result, va_list args);

    /**
     * @brief Retrieves the type of a given object.
     *
     * This function retrieves the type of the specified object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object whose type is to be retrieved.
     * @param[out] result A pointer to store the retrieved type.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetType)(ani_env *env, ani_object object, ani_type *result);

    /**
     * @brief Checks if an object is an instance of a specified type.
     *
     * This function checks whether the given object is an instance of the specified type.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object to check.
     * @param[in] type The type to compare against.
     * @param[out] result A pointer to store the boolean result (true if the object is an instance of the type, false
     * otherwise).
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_InstanceOf)(ani_env *env, ani_object object, ani_type type, ani_boolean *result);

    /**
     * @brief Checks if two objects are the same.
     *
     * This function compares two objects to determine if they refer to the same instance.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object1 The first object to compare.
     * @param[in] object2 The second object to compare.
     * @param[out] result A pointer to store the boolean result (true if the objects are the same, false otherwise).
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_IsSame)(ani_env *env, ani_object object1, ani_object object2, ani_boolean *result);

    /**
     * @brief Retrieves the superclass of a specified type.
     *
     * This function retrieves the superclass of a given type and stores it in the result parameter.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] type The type for which to retrieve the superclass.
     * @param[out] result A pointer to the superclass to be populated.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Type_GetSuperClass)(ani_env *env, ani_type type, ani_class *result);

    /**
     * @brief Determines if one type is assignable from another.
     *
     * This function checks if a type is assignable from another and stores the result in the output parameter.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] from_type The source type.
     * @param[in] to_type The target type.
     * @param[out] result A pointer to a boolean indicating assignability.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Type_IsAssignableFrom)(ani_env *env, ani_type from_type, ani_type to_type, ani_boolean *result);

    /**
     * @brief Finds a module by its descriptor.
     *
     * This function locates a module based on its descriptor and stores it in the result parameter.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] module_descriptor The descriptor of the module to find.
     * @param[out] result A pointer to the module to be populated.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FindModule)(ani_env *env, const char *module_descriptor, ani_module *result);

    /**
     * @brief Finds a namespace by its descriptor.
     *
     * This function locates a namespace based on its descriptor and stores it in the result parameter.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] namespace_descriptor The descriptor of the namespace to find.
     * @param[out] result A pointer to the namespace to be populated.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FindNamespace)(ani_env *env, const char *namespace_descriptor, ani_namespace *result);

    /**
     * @brief Finds a class by its descriptor.
     *
     * This function locates a class based on its descriptor and stores it in the result parameter.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] class_descriptor The descriptor of the class to find.
     * @param[out] result A pointer to the class to be populated.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FindClass)(ani_env *env, const char *class_descriptor, ani_class *result);

    /**
     * @brief Finds an enum by its descriptor.
     *
     * This function locates an enum based on its descriptor and stores it in the result parameter.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] enum_descriptor The descriptor of the enum to find.
     * @param[out] result A pointer to the enum to be populated.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FindEnum)(ani_env *env, const char *enum_descriptor, ani_enum *result);

    /**
     * @brief Finds a tuple by its descriptor.
     *
     * This function locates a tuple based on its descriptor and stores it in the result parameter.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] tuple_descriptor The descriptor of the tuple to find.
     * @param[out] result A pointer to the tuple to be populated.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FindTuple)(ani_env *env, const char *tuple_descriptor, ani_tuple *result);

    /**
     * @brief Finds a function by its descriptor.
     *
     * This function locates a function based on its descriptor and stores it in the result parameter.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] function_descriptor The descriptor of the function to find.
     * @param[out] result A pointer to the function to be populated.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FindFunction)(ani_env *env, const char *function_descriptor, ani_function *result);

    /**
     * @brief Finds a variable by its descriptor.
     *
     * This function locates a variable based on its descriptor and stores it in the result parameter.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] variable_descriptor The descriptor of the variable to find.
     * @param[out] result A pointer to the variable to be populated.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FindVariable)(ani_env *env, const char *variable_descriptor, ani_variable *result);

    /**
     * @brief Finds a namespace within a module by its descriptor.
     *
     * This function locates a namespace within the specified module based on its descriptor.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] module The module to search within.
     * @param[in] namespace_descriptor The descriptor of the namespace to find.
     * @param[out] result A pointer to the namespace object.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Module_FindNamespace)(ani_env *env, ani_module module, const char *namespace_descriptor,
                                       ani_namespace *result);

    /**
     * @brief Finds a class within a module by its descriptor.
     *
     * This function locates a class within the specified module based on its descriptor.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] module The module to search within.
     * @param[in] class_descriptor The descriptor of the class to find.
     * @param[out] result A pointer to the class object.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Module_FindClass)(ani_env *env, ani_module module, const char *class_descriptor, ani_class *result);

    /**
     * @brief Finds an enum within a module by its descriptor.
     *
     * This function locates an enum within the specified module based on its descriptor.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] module The module to search within.
     * @param[in] enum_descriptor The descriptor of the enum to find.
     * @param[out] result A pointer to the enum object.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Module_FindEnum)(ani_env *env, ani_module module, const char *enum_descriptor, ani_enum *result);

    /**
     * @brief Finds a function within a module by its name and signature.
     *
     * This function locates a function within the specified module based on its name and signature.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] module The module to search within.
     * @param[in] name The name of the function to retrieve.
     * @param[in] signature The signature of the function to retrieve.
     * @param[out] result A pointer to the function object.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Module_FindFunction)(ani_env *env, ani_module module, const char *name, const char *signature,
                                      ani_function *result);

    /**
     * @brief Finds a variable within a module by its descriptor.
     *
     * This function locates a variable within the specified module based on its descriptor.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] module The module to search within.
     * @param[in] variable_descriptor The descriptor of the variable to find.
     * @param[out] result A pointer to the variable object.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Module_FindVariable)(ani_env *env, ani_module module, const char *variable_descriptor,
                                      ani_variable *result);

    /**
     * @brief Finds a namespace within another namespace by its descriptor.
     *
     * This function locates a namespace within the specified parent namespace based on its descriptor.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] ns The parent namespace to search within.
     * @param[in] namespace_descriptor The descriptor of the namespace to find.
     * @param[out] result A pointer to the namespace object.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Namespace_FindNamespace)(ani_env *env, ani_namespace ns, const char *namespace_descriptor,
                                          ani_namespace *result);

    /**
     * @brief Finds a class within a namespace by its descriptor.
     *
     * This function locates a class within the specified namespace based on its descriptor.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] ns The namespace to search within.
     * @param[in] class_descriptor The descriptor of the class to find.
     * @param[out] result A pointer to the class object.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Namespace_FindClass)(ani_env *env, ani_namespace ns, const char *class_descriptor, ani_class *result);

    /**
     * @brief Finds an enum within a namespace by its descriptor.
     *
     * This function locates an enum within the specified namespace based on its descriptor.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] ns The namespace to search within.
     * @param[in] enum_descriptor The descriptor of the enum to find.
     * @param[out] result A pointer to the enum object.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Namespace_FindEnum)(ani_env *env, ani_namespace ns, const char *enum_descriptor, ani_enum *result);

    /**
     * @brief Finds a function within a namespace by its name and signature.
     *
     * This function locates a function within the specified namespace based on its name and signature.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] ns The namespace to search within.
     * @param[in] name The name of the function to retrieve.
     * @param[in] signature The signature of the function to retrieve.
     * @param[out] result A pointer to the function object.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Namespace_FindFunction)(ani_env *env, ani_namespace ns, const char *name, const char *signature,
                                         ani_function *result);

    /**
     * @brief Finds a variable within a namespace by its descriptor.
     *
     * This function locates a variable within the specified namespace based on its descriptor.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] ns The namespace to search within.
     * @param[in] variable_descriptor The descriptor of the variable to find.
     * @param[out] result A pointer to the variable object.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Namespace_FindVariable)(ani_env *env, ani_namespace ns, const char *variable_descriptor,
                                         ani_variable *result);

    /**
     * @brief Binds native functions to a module.
     *
     * This function binds an array of native functions to the specified module.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] module The module to which the native functions will be bound.
     * @param[in] functions A pointer to an array of native functions to bind.
     * @param[in] nr_functions The number of native functions in the array.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Module_BindNativeFunctions)(ani_env *env, ani_module module, const ani_native_function *functions,
                                             ani_size nr_functions);

    /**
     * @brief Binds native functions to a namespace.
     *
     * This function binds an array of native functions to the specified namespace.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] ns The namespace to which the native functions will be bound.
     * @param[in] functions A pointer to an array of native functions to bind.
     * @param[in] nr_functions The number of native functions in the array.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Namespace_BindNativeFunctions)(ani_env *env, ani_namespace ns, const ani_native_function *functions,
                                                ani_size nr_functions);

    /**
     * @brief Binds native methods to a class.
     *
     * This function binds an array of native methods to the specified class.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class to which the native methods will be bound.
     * @param[in] methods A pointer to an array of native methods to bind.
     * @param[in] nr_methods The number of native methods in the array.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_BindNativeMethods)(ani_env *env, ani_class cls, const ani_native_function *methods,
                                          ani_size nr_methods);

    /**
     * @brief Deletes a local reference.
     *
     * This function deletes a specified local reference to free up resources.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] ref The reference to be deleted.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Reference_Delete)(ani_env *env, ani_ref ref);

    /**
     * @brief Ensures enough local references are available.
     *
     * This function checks and ensures that the specified number of local references can be created.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] nr_refs The number of local references to ensure availability for.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*EnsureEnoughReferences)(ani_env *env, ani_size nr_refs);

    /**
     * @brief Creates a new local scope for references.
     *
     * This function creates a local scope for references with a specified capacity.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] nr_refs The maximum number of references that can be created in this scope.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*CreateLocalScope)(ani_env *env, ani_size nr_refs);

    /**
     * @brief Destroys the current local scope.
     *
     * This function destroys the current local scope and frees all references within it.
     *
     * @param[in] env A pointer to the environment structure.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*DestroyLocalScope)(ani_env *env);

    /**
     * @brief Creates a new escape local scope.
     *
     * This function creates a local scope for references with escape functionality, allowing objects to escape this
     * scope.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] nr_refs The maximum number of references that can be created in this scope.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*CreateEscapeLocalScope)(ani_env *env, ani_size nr_refs);

    /**
     * @brief Destroys the current escape local scope.
     *
     * This function destroys the current escape local scope and allows escaping references to be retrieved.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] ref The reference to be escaped from the current scope.
     * @param[out] result A pointer to the resulting reference that has escaped the scope.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*DestroyEscapeLocalScope)(ani_env *env, ani_ref ref, ani_ref *result);

    /**
     * @brief Throws an error.
     *
     * This function throws the specified error in the current environment.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] err The error to throw.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*ThrowError)(ani_env *env, ani_error err);

    /**
     * @brief Checks if there are unhandled errors.
     *
     * This function determines if there are unhandled errors in the current environment.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[out] result A pointer to a boolean indicating if unhandled errors exist.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*ExistUnhandledError)(ani_env *env, ani_boolean *result);

    /**
     * @brief Retrieves the current unhandled error.
     *
     * This function fetches the unhandled error in the environment.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[out] result A pointer to store the unhandled error.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*GetUnhandledError)(ani_env *env, ani_error *result);

    /**
     * @brief Resets the current error state.
     *
     * This function clears the error state in the current environment.
     *
     * @param[in] env A pointer to the environment structure.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*ResetError)(ani_env *env);

    /**
     * @brief Provides a description of the current error.
     *
     * This function prints the stack trace or other debug information for the current error.
     *
     * @param[in] env A pointer to the environment structure.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*DescribeError)(ani_env *env);  // NOTE: Print stacktrace for debugging?

    /**
     * @brief Aborts execution with a message.
     *
     * This function terminates execution with the specified error message.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] message The error message to display on termination.
     * @return Does not return; the process terminates.
     */
    ani_status (*Abort)(ani_env *env, const char *message);

    /**
     * @brief Retrieves a null reference.
     *
     * This function provides a null reference in the specified result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[out] result A pointer to store the null reference.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*GetNull)(ani_env *env, ani_ref *result);

    /**
     * @brief Retrieves an undefined reference.
     *
     * This function provides an undefined reference in the specified result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[out] result A pointer to store the undefined reference.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*GetUndefined)(ani_env *env, ani_ref *result);

    /**
     * @brief Checks if a reference is null.
     *
     * This function determines if the specified reference is null.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] ref The reference to check.
     * @param[out] result A pointer to a boolean indicating if the reference is null.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Reference_IsNull)(ani_env *env, ani_ref ref, ani_boolean *result);

    /**
     * @brief Checks if a reference is undefined.
     *
     * This function determines if the specified reference is undefined.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] ref The reference to check.
     * @param[out] result A pointer to a boolean indicating if the reference is undefined.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Reference_IsUndefined)(ani_env *env, ani_ref ref, ani_boolean *result);

    /**
     * @brief Checks if a reference is nullish value (null or undefined).
     *
     * This function determines if the specified reference is either null or undefined.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] ref The reference to check.
     * @param[out] result A pointer to a boolean indicating if the reference is nullish value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Reference_IsNullishValue)(ani_env *env, ani_ref ref, ani_boolean *result);

    /**
     * @brief Compares two references for equality.
     *
     * This function checks if two references are equal.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] ref0 The first reference to compare.
     * @param[in] ref1 The second reference to compare.
     * @param[out] result A pointer to a boolean indicating if the references are equal.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Reference_Equals)(ani_env *env, ani_ref ref0, ani_ref ref1, ani_boolean *result);

    /**
     * @brief Compares two references for strict equality.
     *
     * This function checks if two references are strictly equal.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] ref0 The first reference to compare.
     * @param[in] ref1 The second reference to compare.
     * @param[out] result A pointer to a boolean indicating if the references are strictly equal.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Reference_StrictEquals)(ani_env *env, ani_ref ref0, ani_ref ref1, ani_boolean *result);

    /**
     * @brief Creates a new UTF-16 string.
     *
     * This function creates a new string from the provided UTF-16 encoded data.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] utf16_string A pointer to the UTF-16 encoded string data.
     * @param[in] utf16_size The size of the UTF-16 string in code units.
     * @param[out] result A pointer to store the created string.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*String_NewUTF16)(ani_env *env, const uint16_t *utf16_string, ani_size utf16_size, ani_string *result);

    /**
     * @brief Retrieves the size of a UTF-16 string.
     *
     * This function retrieves the size (in code units) of the specified UTF-16 string.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] string The UTF-16 string to measure.
     * @param[out] result A pointer to store the size of the string.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*String_GetUTF16Size)(ani_env *env, ani_string string, ani_size *result);

    /**
     * @brief Retrieves the UTF-16 encoded data of a string.
     *
     * This function copies the UTF-16 encoded data of the string into the provided buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] string The string to retrieve data from.
     * @param[out] utf16_buffer A buffer to store the UTF-16 encoded data.
     * @param[in] utf16_buffer_size The size of the buffer in code units.
     * @param[out] result A pointer to store the number of code units written.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*String_GetUTF16)(ani_env *env, ani_string string, uint16_t *utf16_buffer, ani_size utf16_buffer_size,
                                  ani_size *result);

    /**
     * @brief Retrieves a substring of a UTF-16 string.
     *
     * This function copies a portion of the UTF-16 string into the provided buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] string The string to retrieve data from.
     * @param[in] substr_offset The starting offset of the substring.
     * @param[in] substr_size The size of the substring in code units.
     * @param[out] utf16_buffer A buffer to store the substring.
     * @param[in] utf16_buffer_size The size of the buffer in code units.
     * @param[out] result A pointer to store the number of code units written.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*String_GetUTF16SubString)(ani_env *env, ani_string string, ani_size substr_offset,
                                           ani_size substr_size, uint16_t *utf16_buffer, ani_size utf16_buffer_size,
                                           ani_size *result);

    /**
     * @brief Creates a new UTF-8 string.
     *
     * This function creates a new string from the provided UTF-8 encoded data.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] utf8_string A pointer to the UTF-8 encoded string data.
     * @param[in] utf8_size The size of the UTF-8 string in bytes.
     * @param[out] result A pointer to store the created string.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*String_NewUTF8)(ani_env *env, const char *utf8_string, ani_size utf8_size, ani_string *result);

    /**
     * @brief Retrieves the size of a UTF-8 string.
     *
     * This function retrieves the size (in bytes) of the specified UTF-8 string.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] string The UTF-8 string to measure.
     * @param[out] result A pointer to store the size of the string.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*String_GetUTF8Size)(ani_env *env, ani_string string, ani_size *result);

    /**
     * @brief Retrieves the UTF-8 encoded data of a string.
     *
     * This function copies the UTF-8 encoded data of the string into the provided buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] string The string to retrieve data from.
     * @param[out] utf8_buffer A buffer to store the UTF-8 encoded data.
     * @param[in] utf8_buffer_size The size of the buffer in bytes.
     * @param[out] result A pointer to store the number of bytes written.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*String_GetUTF8)(ani_env *env, ani_string string, char *utf8_buffer, ani_size utf8_buffer_size,
                                 ani_size *result);

    /**
     * @brief Retrieves a substring of a UTF-8 string.
     *
     * This function copies a portion of the UTF-8 string into the provided buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] string The string to retrieve data from.
     * @param[in] substr_offset The starting offset of the substring.
     * @param[in] substr_size The size of the substring in bytes.
     * @param[out] utf8_buffer A buffer to store the substring.
     * @param[in] utf8_buffer_size The size of the buffer in bytes.
     * @param[out] result A pointer to store the number of bytes written.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*String_GetUTF8SubString)(ani_env *env, ani_string string, ani_size substr_offset, ani_size substr_size,
                                          char *utf8_buffer, ani_size utf8_buffer_size, ani_size *result);

    /**
     * @brief Retrieves critical information about a string.
     *
     * This function retrieves the type and data of a string for critical operations.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] string The string to analyze.
     * @param[out] result_string_type A pointer to store the type of the string (e.g., UTF-16 or UTF-8).
     * @param[out] result_data A pointer to the raw string data.
     * @param[out] result_size A pointer to the size of the string data.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*String_GetCritical)(ani_env *env, ani_string string, uint32_t *result_string_type,
                                     const void **result_data,
                                     ani_size *result_size);  // result_string_type - string type utf16/utf8, etc?

    /**
     * @brief Releases critical string data.
     *
     * This function releases the raw string data retrieved using `String_GetCritical`.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] string The string whose data was retrieved.
     * @param[in] data A pointer to the raw data to release.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*String_ReleaseCritical)(ani_env *env, ani_string string, const void *data);

    /**
     * @brief Creates a new UTF-16 string literal.
     *
     * This function creates a new string literal from the provided UTF-16 encoded data.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] utf16_string A pointer to the UTF-16 encoded string data.
     * @param[in] utf16_size The size of the UTF-16 string in code units.
     * @param[out] result A pointer to store the created string literal.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*StringLiteral_NewUTF16)(ani_env *env, const uint16_t *utf16_string, ani_size utf16_size,
                                         ani_stringliteral *result);

    /**
     * @brief Retrieves the size of a UTF-16 string literal.
     *
     * This function retrieves the size (in code units) of the specified UTF-16 string literal.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] string The UTF-16 string literal to measure.
     * @param[out] result A pointer to store the size of the string literal.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*StringLiteral_GetUTF16Size)(ani_env *env, ani_stringliteral string, ani_size *result);

    /**
     * @brief Retrieves the UTF-16 encoded data of a string literal.
     *
     * This function copies the UTF-16 encoded data of the string literal into the provided buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] string The string literal to retrieve data from.
     * @param[out] utf16_buffer A buffer to store the UTF-16 encoded data.
     * @param[in] utf16_buffer_size The size of the buffer in code units.
     * @param[out] result A pointer to store the number of code units written.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*StringLiteral_GetUTF16)(ani_env *env, ani_stringliteral string, uint16_t *utf16_buffer,
                                         ani_size utf16_buffer_size, ani_size *result);

    /**
     * @brief Retrieves a substring of a UTF-16 string literal.
     *
     * This function copies a portion of the UTF-16 string literal into the provided buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] string The string literal to retrieve data from.
     * @param[in] substr_offset The starting offset of the substring.
     * @param[in] substr_size The size of the substring in code units.
     * @param[out] utf16_buffer A buffer to store the substring.
     * @param[in] utf16_buffer_size The size of the buffer in code units.
     * @param[out] result A pointer to store the number of code units written.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*StringLiteral_GetUTF16SubString)(ani_env *env, ani_stringliteral string, ani_size substr_offset,
                                                  ani_size substr_size, uint16_t *utf16_buffer,
                                                  ani_size utf16_buffer_size, ani_size *result);

    /**
     * @brief Creates a new UTF-8 string literal.
     *
     * This function creates a new string literal from the provided UTF-8 encoded data.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] utf8_string A pointer to the UTF-8 encoded string data.
     * @param[in] size The size of the UTF-8 string in bytes.
     * @param[out] result A pointer to store the created string literal.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*StringLiteral_NewUTF8)(ani_env *env, const char *utf8_string, ani_size size,
                                        ani_stringliteral *result);

    /**
     * @brief Retrieves the size of a UTF-8 string literal.
     *
     * This function retrieves the size (in bytes) of the specified UTF-8 string literal.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] string The UTF-8 string literal to measure.
     * @param[out] result A pointer to store the size of the string literal.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*StringLiteral_GetUTF8Size)(ani_env *env, ani_stringliteral string, ani_size *result);

    /**
     * @brief Retrieves the UTF-8 encoded data of a string literal.
     *
     * This function copies the UTF-8 encoded data of the string literal into the provided buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] string The string literal to retrieve data from.
     * @param[out] utf8_buffer A buffer to store the UTF-8 encoded data.
     * @param[in] utf8_buffer_size The size of the buffer in bytes.
     * @param[out] result A pointer to store the number of bytes written.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*StringLiteral_GetUTF8)(ani_env *env, ani_stringliteral string, char *utf8_buffer,
                                        ani_size utf8_buffer_size, ani_size *result);

    /**
     * @brief Retrieves a substring of a UTF-8 string literal.
     *
     * This function copies a portion of the UTF-8 string literal into the provided buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] string The string literal to retrieve data from.
     * @param[in] substr_offset The starting offset of the substring.
     * @param[in] substr_size The size of the substring in bytes.
     * @param[out] utf8_buffer A buffer to store the substring.
     * @param[in] utf8_buffer_size The size of the buffer in bytes.
     * @param[out] result A pointer to store the number of bytes written.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*StringLiteral_GetUTF8SubString)(ani_env *env, ani_stringliteral string, ani_size substr_offset,
                                                 ani_size substr_size, char *utf8_buffer, ani_size utf8_buffer_size,
                                                 ani_size *result);

    /**
     * @brief Retrieves critical information about a string literal.
     *
     * This function retrieves the type and data of a string literal for critical operations.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] string The string literal to analyze.
     * @param[out] result_string_type A pointer to store the type of the string literal (e.g., UTF-16 or UTF-8).
     * @param[out] result_data A pointer to the raw string literal data.
     * @param[out] result_size A pointer to the size of the string literal data.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*StringLiteral_GetCritical)(
        ani_env *env, ani_stringliteral string, uint32_t *result_string_type, const void **result_data,
        ani_size *result_size);  // result_string_type - string type utf16/utf8, etc?

    /**
     * @brief Releases critical string literal data.
     *
     * This function releases the raw string literal data retrieved using `StringLiteral_GetCritical`.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] string The string literal whose data was retrieved.
     * @param[in] data A pointer to the raw data to release.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*StringLiteral_ReleaseCritical)(ani_env *env, ani_stringliteral string, const void *data);

    /**
     * @brief Retrieves the length of a fixed array.
     *
     * This function retrieves the length of the specified fixed array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixed array whose length is to be retrieved.
     * @param[out] result A pointer to store the length of the array.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_GetLength)(ani_env *env, ani_fixedarray array, ani_size *result);

    /**
     * @brief Creates a new fixed array of booleans.
     *
     * This function creates a new fixed array of the specified length for boolean values.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] length The length of the array to be created.
     * @param[out] result A pointer to store the created fixed array.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_New_Boolean)(ani_env *env, ani_size length, ani_fixedarray_boolean *result);

    /**
     * @brief Creates a new fixed array of characters.
     *
     * This function creates a new fixed array of the specified length for character values.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] length The length of the array to be created.
     * @param[out] result A pointer to store the created fixed array.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_New_Char)(ani_env *env, ani_size length, ani_fixedarray_char *result);

    /**
     * @brief Creates a new fixed array of bytes.
     *
     * This function creates a new fixed array of the specified length for byte values.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] length The length of the array to be created.
     * @param[out] result A pointer to store the created fixed array.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_New_Byte)(ani_env *env, ani_size length, ani_fixedarray_byte *result);

    /**
     * @brief Creates a new fixed array of shorts.
     *
     * This function creates a new fixed array of the specified length for short integer values.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] length The length of the array to be created.
     * @param[out] result A pointer to store the created fixed array.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_New_Short)(ani_env *env, ani_size length, ani_fixedarray_short *result);

    /**
     * @brief Creates a new fixed array of integers.
     *
     * This function creates a new fixed array of the specified length for integer values.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] length The length of the array to be created.
     * @param[out] result A pointer to store the created fixed array.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_New_Int)(ani_env *env, ani_size length, ani_fixedarray_int *result);

    /**
     * @brief Creates a new fixed array of long integers.
     *
     * This function creates a new fixed array of the specified length for long integer values.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] length The length of the array to be created.
     * @param[out] result A pointer to store the created fixed array.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_New_Long)(ani_env *env, ani_size length, ani_fixedarray_long *result);

    /**
     * @brief Creates a new fixed array of floats.
     *
     * This function creates a new fixed array of the specified length for float values.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] length The length of the array to be created.
     * @param[out] result A pointer to store the created fixed array.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_New_Float)(ani_env *env, ani_size length, ani_fixedarray_float *result);

    /**
     * @brief Creates a new fixed array of doubles.
     *
     * This function creates a new fixed array of the specified length for double values.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] length The length of the array to be created.
     * @param[out] result A pointer to store the created fixed array.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_New_Double)(ani_env *env, ani_size length, ani_fixedarray_double *result);

    /**
     * @brief Retrieves a region of boolean values from a fixed array.
     *
     * This function retrieves a portion of the specified boolean fixed array into a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixed array to retrieve values from.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to retrieve.
     * @param[out] native_buffer A buffer to store the retrieved boolean values.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_GetRegion_Boolean)(ani_env *env, ani_fixedarray_boolean array, ani_size offset,
                                               ani_size length, ani_boolean *native_buffer);

    /**
     * @brief Retrieves a region of character values from a fixed array.
     *
     * This function retrieves a portion of the specified character fixed array into a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixed array to retrieve values from.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to retrieve.
     * @param[out] native_buffer A buffer to store the retrieved character values.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_GetRegion_Char)(ani_env *env, ani_fixedarray_char array, ani_size offset, ani_size length,
                                            ani_char *native_buffer);

    /**
     * @brief Retrieves a region of byte values from a fixed array.
     *
     * This function retrieves a portion of the specified byte fixed array into a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixed array to retrieve values from.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to retrieve.
     * @param[out] native_buffer A buffer to store the retrieved byte values.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_GetRegion_Byte)(ani_env *env, ani_fixedarray_byte array, ani_size offset, ani_size length,
                                            ani_byte *native_buffer);

    /**
     * @brief Retrieves a region of short values from a fixed array.
     *
     * This function retrieves a portion of the specified short fixed array into a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixed array to retrieve values from.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to retrieve.
     * @param[out] native_buffer A buffer to store the retrieved short values.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_GetRegion_Short)(ani_env *env, ani_fixedarray_short array, ani_size offset, ani_size length,
                                             ani_short *native_buffer);

    /**
     * @brief Retrieves a region of integer values from a fixed array.
     *
     * This function retrieves a portion of the specified integer fixed array into a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixed array to retrieve values from.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to retrieve.
     * @param[out] native_buffer A buffer to store the retrieved integer values.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_GetRegion_Int)(ani_env *env, ani_fixedarray_int array, ani_size offset, ani_size length,
                                           ani_int *native_buffer);

    /**
     * @brief Retrieves a region of long integer values from a fixed array.
     *
     * This function retrieves a portion of the specified long integer fixed array into a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixed array to retrieve values from.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to retrieve.
     * @param[out] native_buffer A buffer to store the retrieved long integer values.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_GetRegion_Long)(ani_env *env, ani_fixedarray_long array, ani_size offset, ani_size length,
                                            ani_long *native_buffer);

    /**
     * @brief Retrieves a region of float values from a fixed array.
     *
     * This function retrieves a portion of the specified float fixed array into a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixed array to retrieve values from.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to retrieve.
     * @param[out] native_buffer A buffer to store the retrieved float values.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_GetRegion_Float)(ani_env *env, ani_fixedarray_float array, ani_size offset, ani_size length,
                                             ani_float *native_buffer);

    /**
     * @brief Retrieves a region of double values from a fixed array.
     *
     * This function retrieves a portion of the specified double fixed array into a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixed array to retrieve values from.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to retrieve.
     * @param[out] native_buffer A buffer to store the retrieved double values.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_GetRegion_Double)(ani_env *env, ani_fixedarray_double array, ani_size offset,
                                              ani_size length, ani_double *native_buffer);

    /**
     * @brief Sets a region of boolean values in a fixed array.
     *
     * This function sets a portion of the specified boolean fixed array using a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixed array to set values in.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to set.
     * @param[in] native_buffer A buffer containing the boolean values to set.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_SetRegion_Boolean)(ani_env *env, ani_fixedarray_boolean array, ani_size offset,
                                               ani_size length, const ani_boolean *native_buffer);

    /**
     * @brief Sets a region of character values in a fixed array.
     *
     * This function sets a portion of the specified character fixed array using a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixed array to set values in.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to set.
     * @param[in] native_buffer A buffer containing the character values to set.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_SetRegion_Char)(ani_env *env, ani_fixedarray_char array, ani_size offset, ani_size length,
                                            const ani_char *native_buffer);

    /**
     * @brief Sets a region of byte values in a fixed array.
     *
     * This function sets a portion of the specified byte fixed array using a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixed array to set values in.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to set.
     * @param[in] native_buffer A buffer containing the byte values to set.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_SetRegion_Byte)(ani_env *env, ani_fixedarray_byte array, ani_size offset, ani_size length,
                                            const ani_byte *native_buffer);

    /**
     * @brief Sets a region of short values in a fixed array.
     *
     * This function sets a portion of the specified short fixed array using a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixed array to set values in.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to set.
     * @param[in] native_buffer A buffer containing the short values to set.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_SetRegion_Short)(ani_env *env, ani_fixedarray_short array, ani_size offset, ani_size length,
                                             const ani_short *native_buffer);

    /**
     * @brief Sets a region of integer values in a fixed array.
     *
     * This function sets a portion of the specified integer fixed array using a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixed array to set values in.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to set.
     * @param[in] native_buffer A buffer containing the integer values to set.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_SetRegion_Int)(ani_env *env, ani_fixedarray_int array, ani_size offset, ani_size length,
                                           const ani_int *native_buffer);

    /**
     * @brief Sets a region of long integer values in a fixed array.
     *
     * This function sets a portion of the specified long integer fixed array using a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixed array to set values in.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to set.
     * @param[in] native_buffer A buffer containing the long integer values to set.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_SetRegion_Long)(ani_env *env, ani_fixedarray_long array, ani_size offset, ani_size length,
                                            const ani_long *native_buffer);

    /**
     * @brief Sets a region of float values in a fixed array.
     *
     * This function sets a portion of the specified float fixed array using a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixed array to set values in.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to set.
     * @param[in] native_buffer A buffer containing the float values to set.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_SetRegion_Float)(ani_env *env, ani_fixedarray_float array, ani_size offset, ani_size length,
                                             const ani_float *native_buffer);

    /**
     * @brief Sets a region of double values in a fixed array.
     *
     * This function sets a portion of the specified double fixed array using a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixed array to set values in.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to set.
     * @param[in] native_buffer A buffer containing the double values to set.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_SetRegion_Double)(ani_env *env, ani_fixedarray_double array, ani_size offset,
                                              ani_size length, const ani_double *native_buffer);

    /**
     * @brief Pins a fixed array in memory.
     *
     * This function pins a fixed array of primitive types in memory to ensure it is not moved by the garbage collector.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] primitive_array The fixed array to pin.
     * @param[out] result A pointer to store the memory address of the pinned array.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_Pin)(ani_env *env, ani_fixedarray primitive_array, void **result);

    /**
     * @brief Unpins a fixed array in memory.
     *
     * This function unpins a previously pinned fixed array, allowing it to be moved by the garbage collector.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] primitive_array The fixed array to unpin.
     * @param[in] data A pointer to the pinned memory that was previously retrieved.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_Unpin)(ani_env *env, ani_fixedarray primitive_array, void *data);

    /**
     * @brief Creates a new fixed array of references.
     *
     * This function creates a new fixed array of references, optionally initializing it with an array of references.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] length The length of the array to be created.
     * @param[in] initial_array An optional array of references to initialize the fixed array. Can be null.
     * @param[out] result A pointer to store the created fixed array of references.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_New_Ref)(ani_env *env, ani_size length, ani_ref *initial_array, ani_fixedarray_ref *result);

    /**
     * @brief Sets a reference at a specific index in a fixed array.
     *
     * This function sets the value of a reference at the specified index in the fixed array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixed array of references to modify.
     * @param[in] index The index at which to set the reference.
     * @param[in] ref The reference to set at the specified index.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_Set_Ref)(ani_env *env, ani_fixedarray_ref array, ani_size index, ani_ref ref);

    /**
     * @brief Retrieves a reference from a specific index in a fixed array.
     *
     * This function retrieves the value of a reference at the specified index in the fixed array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixed array of references to query.
     * @param[in] index The index from which to retrieve the reference.
     * @param[out] result A pointer to store the retrieved reference.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_Get_Ref)(ani_env *env, ani_fixedarray_ref array, ani_size index, ani_ref *result);

    /**
     * @brief Retrieves an enum value by its name.
     *
     * This function retrieves an enum value associated with the specified name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] enm The enum to search within.
     * @param[in] name The name of the enum value to retrieve.
     * @param[out] result A pointer to store the retrieved enum value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Enum_GetEnumValueByName)(ani_env *env, ani_enum enm, const char *name, ani_enum_value *result);

    /**
     * @brief Retrieves an enum value by its index.
     *
     * This function retrieves an enum value located at the specified index.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] enm The enum to search within.
     * @param[in] index The index of the enum value to retrieve.
     * @param[out] result A pointer to store the retrieved enum value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Enum_GetEnumValueByIndex)(ani_env *env, ani_enum enm, ani_size index, ani_enum_value *result);

    /**
     * @brief Retrieves the enum associated with an enum value.
     *
     * This function retrieves the enum to which the specified enum value belongs.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] enum_value The enum value whose associated enum is to be retrieved.
     * @param[out] result A pointer to store the retrieved enum.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*EnumValue_GetEnum)(ani_env *env, ani_enum_value enum_value, ani_enum *result);

    /**
     * @brief Retrieves the underlying value of an enum value.
     *
     * This function retrieves the object representing the value of the specified enum value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] enum_value The enum value whose underlying value is to be retrieved.
     * @param[out] result A pointer to store the retrieved object.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*EnumValue_GetValue)(ani_env *env, ani_enum_value enum_value, ani_object *result);

    /**
     * @brief Retrieves the name of an enum value.
     *
     * This function retrieves the name associated with the specified enum value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] enum_value The enum value whose name is to be retrieved.
     * @param[out] result A pointer to store the retrieved name.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*EnumValue_GetName)(ani_env *env, ani_enum_value enum_value, ani_string *result);

    /**
     * @brief Retrieves the index of an enum value.
     *
     * This function retrieves the index of the specified enum value within its enum.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] enum_value The enum value whose index is to be retrieved.
     * @param[out] result A pointer to store the retrieved index.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*EnumValue_GetIndex)(ani_env *env, ani_enum_value enum_value, ani_size *result);

    /**
     * @brief Invokes a functional object.
     *
     * This function invokes a functional object (e.g., a function or callable object) with the specified arguments.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] fn The functional object to invoke.
     * @param[in] argc The number of arguments being passed to the functional object.
     * @param[in] argv A pointer to an array of references representing the arguments. Can be null if `argc` is 0.
     * @param[out] result A pointer to store the result of the invocation. Can be null if the functional object does not
     * return a value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FunctionalObject_Call)(ani_env *env, ani_fn_object fn, ani_size argc, ani_ref *argv, ani_ref *result);

    /**
     * @brief Sets a boolean value to a variable.
     *
     * This function assigns a boolean value to the specified variable.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] variable The variable to modify.
     * @param[in] value The boolean value to assign to the variable.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Variable_SetValue_Boolean)(ani_env *env, ani_variable variable, ani_boolean value);

    /**
     * @brief Sets a character value to a variable.
     *
     * This function assigns a character value to the specified variable.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] variable The variable to modify.
     * @param[in] value The character value to assign to the variable.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Variable_SetValue_Char)(ani_env *env, ani_variable variable, ani_char value);

    /**
     * @brief Sets a byte value to a variable.
     *
     * This function assigns a byte value to the specified variable.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] variable The variable to modify.
     * @param[in] value The byte value to assign to the variable.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Variable_SetValue_Byte)(ani_env *env, ani_variable variable, ani_byte value);

    /**
     * @brief Sets a short value to a variable.
     *
     * This function assigns a short integer value to the specified variable.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] variable The variable to modify.
     * @param[in] value The short integer value to assign to the variable.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Variable_SetValue_Short)(ani_env *env, ani_variable variable, ani_short value);

    /**
     * @brief Sets an integer value to a variable.
     *
     * This function assigns an integer value to the specified variable.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] variable The variable to modify.
     * @param[in] value The integer value to assign to the variable.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Variable_SetValue_Int)(ani_env *env, ani_variable variable, ani_int value);

    /**
     * @brief Sets a long value to a variable.
     *
     * This function assigns a long integer value to the specified variable.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] variable The variable to modify.
     * @param[in] value The long integer value to assign to the variable.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Variable_SetValue_Long)(ani_env *env, ani_variable variable, ani_long value);

    /**
     * @brief Sets a float value to a variable.
     *
     * This function assigns a float value to the specified variable.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] variable The variable to modify.
     * @param[in] value The float value to assign to the variable.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Variable_SetValue_Float)(ani_env *env, ani_variable variable, ani_float value);

    /**
     * @brief Sets a double value to a variable.
     *
     * This function assigns a double value to the specified variable.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] variable The variable to modify.
     * @param[in] value The double value to assign to the variable.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Variable_SetValue_Double)(ani_env *env, ani_variable variable, ani_double value);

    /**
     * @brief Sets a reference value to a variable.
     *
     * This function assigns a reference value to the specified variable.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] variable The variable to modify.
     * @param[in] value The reference value to assign to the variable.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Variable_SetValue_Ref)(ani_env *env, ani_variable variable, ani_ref value);

    /**
     * @brief Retrieves a boolean value from a variable.
     *
     * This function fetches a boolean value from the specified variable.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] variable The variable to query.
     * @param[out] result A pointer to store the retrieved boolean value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Variable_GetValue_Boolean)(ani_env *env, ani_variable variable, ani_boolean *result);

    /**
     * @brief Retrieves a character value from a variable.
     *
     * This function fetches a character value from the specified variable.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] variable The variable to query.
     * @param[out] result A pointer to store the retrieved character value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Variable_GetValue_Char)(ani_env *env, ani_variable variable, ani_char *result);

    /**
     * @brief Retrieves a byte value from a variable.
     *
     * This function fetches a byte value from the specified variable.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] variable The variable to query.
     * @param[out] result A pointer to store the retrieved byte value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Variable_GetValue_Byte)(ani_env *env, ani_variable variable, ani_byte *result);

    /**
     * @brief Retrieves a short value from a variable.
     *
     * This function fetches a short integer value from the specified variable.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] variable The variable to query.
     * @param[out] result A pointer to store the retrieved short integer value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Variable_GetValue_Short)(ani_env *env, ani_variable variable, ani_short *result);

    /**
     * @brief Retrieves an integer value from a variable.
     *
     * This function fetches an integer value from the specified variable.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] variable The variable to query.
     * @param[out] result A pointer to store the retrieved integer value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Variable_GetValue_Int)(ani_env *env, ani_variable variable, ani_int *result);

    /**
     * @brief Retrieves a long value from a variable.
     *
     * This function fetches a long integer value from the specified variable.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] variable The variable to query.
     * @param[out] result A pointer to store the retrieved long integer value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Variable_GetValue_Long)(ani_env *env, ani_variable variable, ani_long *result);

    /**
     * @brief Retrieves a float value from a variable.
     *
     * This function fetches a float value from the specified variable.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] variable The variable to query.
     * @param[out] result A pointer to store the retrieved float value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Variable_GetValue_Float)(ani_env *env, ani_variable variable, ani_float *result);

    /**
     * @brief Retrieves a double value from a variable.
     *
     * This function fetches a double value from the specified variable.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] variable The variable to query.
     * @param[out] result A pointer to store the retrieved double value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Variable_GetValue_Double)(ani_env *env, ani_variable variable, ani_double *result);

    /**
     * @brief Retrieves a reference value from a variable.
     *
     * This function fetches a reference value from the specified variable.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] variable The variable to query.
     * @param[out] result A pointer to store the retrieved reference value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Variable_GetValue_Ref)(ani_env *env, ani_variable variable, ani_ref *result);

    /**
     * @brief Calls a function and retrieves a boolean result.
     *
     * This function calls the specified function with variadic arguments and retrieves a boolean result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] fn The function to call.
     * @param[out] result A pointer to store the boolean result.
     * @param[in] ... Variadic arguments to pass to the function.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Function_Call_Boolean)(ani_env *env, ani_function fn, ani_boolean *result, ...);

    /**
     * @brief Calls a function and retrieves a boolean result (array-based).
     *
     * This function calls the specified function with arguments provided in an array and retrieves a boolean result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] fn The function to call.
     * @param[out] result A pointer to store the boolean result.
     * @param[in] args A pointer to an array of arguments to pass to the function.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Function_Call_Boolean_A)(ani_env *env, ani_function fn, ani_boolean *result, const ani_value *args);

    /**
     * @brief Calls a function and retrieves a boolean result (variadic arguments).
     *
     * This function calls the specified function with arguments provided in a `va_list` and retrieves a boolean result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] fn The function to call.
     * @param[out] result A pointer to store the boolean result.
     * @param[in] args A `va_list` containing the arguments to pass to the function.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Function_Call_Boolean_V)(ani_env *env, ani_function fn, ani_boolean *result, va_list args);

    /**
     * @brief Calls a function and retrieves a character result.
     *
     * This function calls the specified function with variadic arguments and retrieves a character result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] fn The function to call.
     * @param[out] result A pointer to store the character result.
     * @param[in] ... Variadic arguments to pass to the function.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Function_Call_Char)(ani_env *env, ani_function fn, ani_char *result, ...);

    /**
     * @brief Calls a function and retrieves a character result (array-based).
     *
     * This function calls the specified function with arguments provided in an array and retrieves a character result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] fn The function to call.
     * @param[out] result A pointer to store the character result.
     * @param[in] args A pointer to an array of arguments to pass to the function.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Function_Call_Char_A)(ani_env *env, ani_function fn, ani_char *result, const ani_value *args);

    /**
     * @brief Calls a function and retrieves a character result (variadic arguments).
     *
     * This function calls the specified function with arguments provided in a `va_list` and retrieves a character
     * result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] fn The function to call.
     * @param[out] result A pointer to store the character result.
     * @param[in] args A `va_list` containing the arguments to pass to the function.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Function_Call_Char_V)(ani_env *env, ani_function fn, ani_char *result, va_list args);

    /**
     * @brief Calls a function and retrieves a byte result.
     *
     * This function calls the specified function with variadic arguments and retrieves a byte result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] fn The function to call.
     * @param[out] result A pointer to store the byte result.
     * @param[in] ... Variadic arguments to pass to the function.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Function_Call_Byte)(ani_env *env, ani_function fn, ani_byte *result, ...);

    /**
     * @brief Calls a function and retrieves a byte result (array-based).
     *
     * This function calls the specified function with arguments provided in an array and retrieves a byte result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] fn The function to call.
     * @param[out] result A pointer to store the byte result.
     * @param[in] args A pointer to an array of arguments to pass to the function.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Function_Call_Byte_A)(ani_env *env, ani_function fn, ani_byte *result, const ani_value *args);

    /**
     * @brief Calls a function and retrieves a byte result (variadic arguments).
     *
     * This function calls the specified function with arguments provided in a `va_list` and retrieves a byte result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] fn The function to call.
     * @param[out] result A pointer to store the byte result.
     * @param[in] args A `va_list` containing the arguments to pass to the function.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Function_Call_Byte_V)(ani_env *env, ani_function fn, ani_byte *result, va_list args);

    /**
     * @brief Calls a function and retrieves a short result.
     *
     * This function calls the specified function with variadic arguments and retrieves a short result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] fn The function to call.
     * @param[out] result A pointer to store the short result.
     * @param[in] ... Variadic arguments to pass to the function.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Function_Call_Short)(ani_env *env, ani_function fn, ani_short *result, ...);

    /**
     * @brief Calls a function and retrieves a short result (array-based).
     *
     * This function calls the specified function with arguments provided in an array and retrieves a short result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] fn The function to call.
     * @param[out] result A pointer to store the short result.
     * @param[in] args A pointer to an array of arguments to pass to the function.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Function_Call_Short_A)(ani_env *env, ani_function fn, ani_short *result, const ani_value *args);

    /**
     * @brief Calls a function and retrieves a short result (variadic arguments).
     *
     * This function calls the specified function with arguments provided in a `va_list` and retrieves a short result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] fn The function to call.
     * @param[out] result A pointer to store the short result.
     * @param[in] args A `va_list` containing the arguments to pass to the function.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Function_Call_Short_V)(ani_env *env, ani_function fn, ani_short *result, va_list args);

    /**
     * @brief Calls a function and retrieves an integer result.
     *
     * This function calls the specified function with variadic arguments and retrieves an integer result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] fn The function to call.
     * @param[out] result A pointer to store the integer result.
     * @param[in] ... Variadic arguments to pass to the function.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Function_Call_Int)(ani_env *env, ani_function fn, ani_int *result, ...);

    /**
     * @brief Calls a function and retrieves an integer result (array-based).
     *
     * This function calls the specified function with arguments provided in an array and retrieves an integer result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] fn The function to call.
     * @param[out] result A pointer to store the integer result.
     * @param[in] args A pointer to an array of arguments to pass to the function.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Function_Call_Int_A)(ani_env *env, ani_function fn, ani_int *result, const ani_value *args);

    /**
     * @brief Calls a function and retrieves an integer result (variadic arguments).
     *
     * This function calls the specified function with arguments provided in a `va_list` and retrieves an integer
     * result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] fn The function to call.
     * @param[out] result A pointer to store the integer result.
     * @param[in] args A `va_list` containing the arguments to pass to the function.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Function_Call_Int_V)(ani_env *env, ani_function fn, ani_int *result, va_list args);

    /**
     * @brief Calls a function and retrieves a long result.
     *
     * This function calls the specified function with variadic arguments and retrieves a long result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] fn The function to call.
     * @param[out] result A pointer to store the long result.
     * @param[in] ... Variadic arguments to pass to the function.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Function_Call_Long)(ani_env *env, ani_function fn, ani_long *result, ...);

    /**
     * @brief Calls a function and retrieves a long result (array-based).
     *
     * This function calls the specified function with arguments provided in an array and retrieves a long result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] fn The function to call.
     * @param[out] result A pointer to store the long result.
     * @param[in] args A pointer to an array of arguments to pass to the function.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Function_Call_Long_A)(ani_env *env, ani_function fn, ani_long *result, const ani_value *args);

    /**
     * @brief Calls a function and retrieves a long result (variadic arguments).
     *
     * This function calls the specified function with arguments provided in a `va_list` and retrieves a long result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] fn The function to call.
     * @param[out] result A pointer to store the long result.
     * @param[in] args A `va_list` containing the arguments to pass to the function.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Function_Call_Long_V)(ani_env *env, ani_function fn, ani_long *result, va_list args);

    /**
     * @brief Calls a function and retrieves a float result.
     *
     * This function calls the specified function with variadic arguments and retrieves a float result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] fn The function to call.
     * @param[out] result A pointer to store the float result.
     * @param[in] ... Variadic arguments to pass to the function.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Function_Call_Float)(ani_env *env, ani_function fn, ani_float *result, ...);

    /**
     * @brief Calls a function and retrieves a float result (array-based).
     *
     * This function calls the specified function with arguments provided in an array and retrieves a float result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] fn The function to call.
     * @param[out] result A pointer to store the float result.
     * @param[in] args A pointer to an array of arguments to pass to the function.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Function_Call_Float_A)(ani_env *env, ani_function fn, ani_float *result, const ani_value *args);

    /**
     * @brief Calls a function and retrieves a float result (variadic arguments).
     *
     * This function calls the specified function with arguments provided in a `va_list` and retrieves a float result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] fn The function to call.
     * @param[out] result A pointer to store the float result.
     * @param[in] args A `va_list` containing the arguments to pass to the function.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Function_Call_Float_V)(ani_env *env, ani_function fn, ani_float *result, va_list args);

    /**
     * @brief Calls a function and retrieves a double result.
     *
     * This function calls the specified function with variadic arguments and retrieves a double result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] fn The function to call.
     * @param[out] result A pointer to store the double result.
     * @param[in] ... Variadic arguments to pass to the function.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Function_Call_Double)(ani_env *env, ani_function fn, ani_double *result, ...);

    /**
     * @brief Calls a function and retrieves a double result (array-based).
     *
     * This function calls the specified function with arguments provided in an array and retrieves a double result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] fn The function to call.
     * @param[out] result A pointer to store the double result.
     * @param[in] args A pointer to an array of arguments to pass to the function.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Function_Call_Double_A)(ani_env *env, ani_function fn, ani_double *result, const ani_value *args);

    /**
     * @brief Calls a function and retrieves a double result (variadic arguments).
     *
     * This function calls the specified function with arguments provided in a `va_list` and retrieves a double result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] fn The function to call.
     * @param[out] result A pointer to store the double result.
     * @param[in] args A `va_list` containing the arguments to pass to the function.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Function_Call_Double_V)(ani_env *env, ani_function fn, ani_double *result, va_list args);

    /**
     * @brief Calls a function and retrieves a reference result.
     *
     * This function calls the specified function with variadic arguments and retrieves a reference result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] fn The function to call.
     * @param[out] result A pointer to store the reference result.
     * @param[in] ... Variadic arguments to pass to the function.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Function_Call_Ref)(ani_env *env, ani_function fn, ani_ref *result, ...);

    /**
     * @brief Calls a function and retrieves a reference result (array-based).
     *
     * This function calls the specified function with arguments provided in an array and retrieves a reference result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] fn The function to call.
     * @param[out] result A pointer to store the reference result.
     * @param[in] args A pointer to an array of arguments to pass to the function.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Function_Call_Ref_A)(ani_env *env, ani_function fn, ani_ref *result, const ani_value *args);

    /**
     * @brief Calls a function and retrieves a reference result (variadic arguments).
     *
     * This function calls the specified function with arguments provided in a `va_list` and retrieves a reference
     * result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] fn The function to call.
     * @param[out] result A pointer to store the reference result.
     * @param[in] args A `va_list` containing the arguments to pass to the function.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Function_Call_Ref_V)(ani_env *env, ani_function fn, ani_ref *result, va_list args);

    /**
     * @brief Calls a function without returning a result.
     *
     * This function calls the specified function with variadic arguments and does not return a result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] fn The function to call.
     * @param[in] ... Variadic arguments to pass to the function.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Function_Call_Void)(ani_env *env, ani_function fn, ...);

    /**
     * @brief Calls a function without returning a result (array-based).
     *
     * This function calls the specified function with arguments provided in an array and does not return a result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] fn The function to call.
     * @param[in] args A pointer to an array of arguments to pass to the function.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Function_Call_Void_A)(ani_env *env, ani_function fn, const ani_value *args);

    /**
     * @brief Calls a function without returning a result (variadic arguments).
     *
     * This function calls the specified function with arguments provided in a `va_list` and does not return a result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] fn The function to call.
     * @param[in] args A `va_list` containing the arguments to pass to the function.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Function_Call_Void_V)(ani_env *env, ani_function fn, va_list args);

    /**
     * @brief Retrieves the partial class representation.
     *
     * This function retrieves the partial class representation of the specified class.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class to query.
     * @param[out] result A pointer to store the partial class representation.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_GetPartial)(ani_env *env, ani_class cls, ani_class *result);

    /**
     * @brief Retrieves the required class representation.
     *
     * This function retrieves the required class representation of the specified class.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class to query.
     * @param[out] result A pointer to store the required class representation.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_GetRequired)(ani_env *env, ani_class cls, ani_class *result);

    /**
     * @brief Retrieves a field from the class.
     *
     * This function retrieves the specified field by name from the given class.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class to query.
     * @param[in] name The name of the field to retrieve.
     * @param[out] result A pointer to store the retrieved field.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_GetField)(ani_env *env, ani_class cls, const char *name, ani_field *result);

    /**
     * @brief Retrieves a static field from the class.
     *
     * This function retrieves the specified static field by name from the given class.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class to query.
     * @param[in] name The name of the static field to retrieve.
     * @param[out] result A pointer to store the retrieved static field.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_GetStaticField)(ani_env *env, ani_class cls, const char *name, ani_static_field *result);

    /**
     * @brief Retrieves a method from the class.
     *
     * This function retrieves the specified method by name and signature from the given class.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class to query.
     * @param[in] name The name of the method to retrieve.
     * @param[in] signature The signature of the method to retrieve.
     * @param[out] result A pointer to store the retrieved method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_GetMethod)(ani_env *env, ani_class cls, const char *name, const char *signature,
                                  ani_method *result);

    /**
     * @brief Retrieves a static method from the class.
     *
     * This function retrieves the specified static method by name and signature from the given class.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class to query.
     * @param[in] name The name of the static method to retrieve.
     * @param[in] signature The signature of the static method to retrieve.
     * @param[out] result A pointer to store the retrieved static method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_GetStaticMethod)(ani_env *env, ani_class cls, const char *name, const char *signature,
                                        ani_static_method *result);

    /**
     * @brief Retrieves a property from the class.
     *
     * This function retrieves the specified property by name from the given class.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class to query.
     * @param[in] name The name of the property to retrieve.
     * @param[out] result A pointer to store the retrieved property.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_GetProperty)(ani_env *env, ani_class cls, const char *name, ani_property *result);

    /**
     * @brief Retrieves the setter method of a property from the class.
     *
     * This function retrieves the setter method for the specified property by name from the given class.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class to query.
     * @param[in] name The name of the property whose setter is to be retrieved.
     * @param[out] result A pointer to store the retrieved setter method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_GetSetter)(ani_env *env, ani_class cls, const char *name, ani_method *result);

    /**
     * @brief Retrieves the getter method of a property from the class.
     *
     * This function retrieves the getter method for the specified property by name from the given class.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class to query.
     * @param[in] name The name of the property whose getter is to be retrieved.
     * @param[out] result A pointer to store the retrieved getter method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_GetGetter)(ani_env *env, ani_class cls, const char *name, ani_method *result);

    /**
     * @brief Retrieves the indexable getter method from the class.
     *
     * This function retrieves the indexable getter method for the specified signature from the given class.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class to query.
     * @param[in] signature The signature of the indexable getter to retrieve.
     * @param[out] result A pointer to store the retrieved indexable getter method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_GetIndexableGetter)(ani_env *env, ani_class cls, const char *signature, ani_method *result);

    /**
     * @brief Retrieves the indexable setter method from the class.
     *
     * This function retrieves the indexable setter method for the specified signature from the given class.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class to query.
     * @param[in] signature The signature of the indexable setter to retrieve.
     * @param[out] result A pointer to store the retrieved indexable setter method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_GetIndexableSetter)(ani_env *env, ani_class cls, const char *signature, ani_method *result);

    /**
     * @brief Retrieves the iterator method from the class.
     *
     * This function retrieves the iterator method from the specified class.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class to query.
     * @param[out] result A pointer to store the retrieved iterator method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_GetIterator)(ani_env *env, ani_class cls, ani_method *result);

    /**
     * @brief Retrieves a boolean value from a static field of a class.
     *
     * This function retrieves the boolean value of the specified static field from the given class.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] field The static field to retrieve.
     * @param[out] result A pointer to store the retrieved boolean value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_GetStaticField_Boolean)(ani_env *env, ani_class cls, ani_static_field field,
                                               ani_boolean *result);

    /**
     * @brief Retrieves a character value from a static field of a class.
     *
     * This function retrieves the character value of the specified static field from the given class.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] field The static field to retrieve.
     * @param[out] result A pointer to store the retrieved character value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_GetStaticField_Char)(ani_env *env, ani_class cls, ani_static_field field, ani_char *result);

    /**
     * @brief Retrieves a byte value from a static field of a class.
     *
     * This function retrieves the byte value of the specified static field from the given class.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] field The static field to retrieve.
     * @param[out] result A pointer to store the retrieved byte value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_GetStaticField_Byte)(ani_env *env, ani_class cls, ani_static_field field, ani_byte *result);

    /**
     * @brief Retrieves a short value from a static field of a class.
     *
     * This function retrieves the short value of the specified static field from the given class.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] field The static field to retrieve.
     * @param[out] result A pointer to store the retrieved short value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_GetStaticField_Short)(ani_env *env, ani_class cls, ani_static_field field, ani_short *result);

    /**
     * @brief Retrieves an integer value from a static field of a class.
     *
     * This function retrieves the integer value of the specified static field from the given class.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] field The static field to retrieve.
     * @param[out] result A pointer to store the retrieved integer value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_GetStaticField_Int)(ani_env *env, ani_class cls, ani_static_field field, ani_int *result);

    /**
     * @brief Retrieves a long value from a static field of a class.
     *
     * This function retrieves the long value of the specified static field from the given class.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] field The static field to retrieve.
     * @param[out] result A pointer to store the retrieved long value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_GetStaticField_Long)(ani_env *env, ani_class cls, ani_static_field field, ani_long *result);

    /**
     * @brief Retrieves a float value from a static field of a class.
     *
     * This function retrieves the float value of the specified static field from the given class.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] field The static field to retrieve.
     * @param[out] result A pointer to store the retrieved float value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_GetStaticField_Float)(ani_env *env, ani_class cls, ani_static_field field, ani_float *result);

    /**
     * @brief Retrieves a double value from a static field of a class.
     *
     * This function retrieves the double value of the specified static field from the given class.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] field The static field to retrieve.
     * @param[out] result A pointer to store the retrieved double value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_GetStaticField_Double)(ani_env *env, ani_class cls, ani_static_field field, ani_double *result);

    /**
     * @brief Retrieves a reference value from a static field of a class.
     *
     * This function retrieves the reference value of the specified static field from the given class.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] field The static field to retrieve.
     * @param[out] result A pointer to store the retrieved reference value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_GetStaticField_Ref)(ani_env *env, ani_class cls, ani_static_field field, ani_ref *result);

    /**
     * @brief Sets a boolean value to a static field of a class.
     *
     * This function assigns a boolean value to the specified static field of the given class.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] field The static field to modify.
     * @param[in] value The boolean value to assign.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_SetStaticField_Boolean)(ani_env *env, ani_class cls, ani_static_field field, ani_boolean value);

    /**
     * @brief Sets a character value to a static field of a class.
     *
     * This function assigns a character value to the specified static field of the given class.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] field The static field to modify.
     * @param[in] value The character value to assign.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_SetStaticField_Char)(ani_env *env, ani_class cls, ani_static_field field, ani_char value);

    /**
     * @brief Sets a byte value to a static field of a class.
     *
     * This function assigns a byte value to the specified static field of the given class.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] field The static field to modify.
     * @param[in] value The byte value to assign.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_SetStaticField_Byte)(ani_env *env, ani_class cls, ani_static_field field, ani_byte value);

    /**
     * @brief Sets a short value to a static field of a class.
     *
     * This function assigns a short value to the specified static field of the given class.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] field The static field to modify.
     * @param[in] value The short value to assign.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_SetStaticField_Short)(ani_env *env, ani_class cls, ani_static_field field, ani_short value);

    /**
     * @brief Sets an integer value to a static field of a class.
     *
     * This function assigns an integer value to the specified static field of the given class.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] field The static field to modify.
     * @param[in] value The integer value to assign.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_SetStaticField_Int)(ani_env *env, ani_class cls, ani_static_field field, ani_int value);

    /**
     * @brief Sets a long value to a static field of a class.
     *
     * This function assigns a long value to the specified static field of the given class.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] field The static field to modify.
     * @param[in] value The long value to assign.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_SetStaticField_Long)(ani_env *env, ani_class cls, ani_static_field field, ani_long value);

    /**
     * @brief Sets a float value to a static field of a class.
     *
     * This function assigns a float value to the specified static field of the given class.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] field The static field to modify.
     * @param[in] value The float value to assign.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_SetStaticField_Float)(ani_env *env, ani_class cls, ani_static_field field, ani_float value);

    /**
     * @brief Sets a double value to a static field of a class.
     *
     * This function assigns a double value to the specified static field of the given class.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] field The static field to modify.
     * @param[in] value The double value to assign.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_SetStaticField_Double)(ani_env *env, ani_class cls, ani_static_field field, ani_double value);

    /**
     * @brief Sets a reference value to a static field of a class.
     *
     * This function assigns a reference value to the specified static field of the given class.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] field The static field to modify.
     * @param[in] value The reference value to assign.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_SetStaticField_Ref)(ani_env *env, ani_class cls, ani_static_field field, ani_ref value);

    /**
     * @brief Retrieves a boolean value from a static field of a class by its name.
     *
     * This function retrieves the boolean value of the specified static field from the given class by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] name The name of the static field to retrieve.
     * @param[out] result A pointer to store the retrieved boolean value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_GetStaticFieldByName_Boolean)(ani_env *env, ani_class cls, const char *name,
                                                     ani_boolean *result);

    /**
     * @brief Retrieves a character value from a static field of a class by its name.
     *
     * This function retrieves the character value of the specified static field from the given class by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] name The name of the static field to retrieve.
     * @param[out] result A pointer to store the retrieved character value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_GetStaticFieldByName_Char)(ani_env *env, ani_class cls, const char *name, ani_char *result);

    /**
     * @brief Retrieves a byte value from a static field of a class by its name.
     *
     * This function retrieves the byte value of the specified static field from the given class by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] name The name of the static field to retrieve.
     * @param[out] result A pointer to store the retrieved byte value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_GetStaticFieldByName_Byte)(ani_env *env, ani_class cls, const char *name, ani_byte *result);

    /**
     * @brief Retrieves a short value from a static field of a class by its name.
     *
     * This function retrieves the short value of the specified static field from the given class by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] name The name of the static field to retrieve.
     * @param[out] result A pointer to store the retrieved short value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_GetStaticFieldByName_Short)(ani_env *env, ani_class cls, const char *name, ani_short *result);

    /**
     * @brief Retrieves an integer value from a static field of a class by its name.
     *
     * This function retrieves the integer value of the specified static field from the given class by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] name The name of the static field to retrieve.
     * @param[out] result A pointer to store the retrieved integer value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_GetStaticFieldByName_Int)(ani_env *env, ani_class cls, const char *name, ani_int *result);

    /**
     * @brief Retrieves a long value from a static field of a class by its name.
     *
     * This function retrieves the long value of the specified static field from the given class by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] name The name of the static field to retrieve.
     * @param[out] result A pointer to store the retrieved long value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_GetStaticFieldByName_Long)(ani_env *env, ani_class cls, const char *name, ani_long *result);

    /**
     * @brief Retrieves a float value from a static field of a class by its name.
     *
     * This function retrieves the float value of the specified static field from the given class by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] name The name of the static field to retrieve.
     * @param[out] result A pointer to store the retrieved float value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_GetStaticFieldByName_Float)(ani_env *env, ani_class cls, const char *name, ani_float *result);

    /**
     * @brief Retrieves a double value from a static field of a class by its name.
     *
     * This function retrieves the double value of the specified static field from the given class by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] name The name of the static field to retrieve.
     * @param[out] result A pointer to store the retrieved double value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_GetStaticFieldByName_Double)(ani_env *env, ani_class cls, const char *name, ani_double *result);

    /**
     * @brief Retrieves a reference value from a static field of a class by its name.
     *
     * This function retrieves the reference value of the specified static field from the given class by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] name The name of the static field to retrieve.
     * @param[out] result A pointer to store the retrieved reference value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_GetStaticFieldByName_Ref)(ani_env *env, ani_class cls, const char *name, ani_ref *result);

    /**
     * @brief Sets a boolean value to a static field of a class by its name.
     *
     * This function assigns a boolean value to the specified static field of the given class by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] name The name of the static field to modify.
     * @param[in] value The boolean value to assign.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_SetStaticFieldByName_Boolean)(ani_env *env, ani_class cls, const char *name, ani_boolean value);

    /**
     * @brief Sets a character value to a static field of a class by its name.
     *
     * This function assigns a character value to the specified static field of the given class by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] name The name of the static field to modify.
     * @param[in] value The character value to assign.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_SetStaticFieldByName_Char)(ani_env *env, ani_class cls, const char *name, ani_char value);

    /**
     * @brief Sets a byte value to a static field of a class by its name.
     *
     * This function assigns a byte value to the specified static field of the given class by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] name The name of the static field to modify.
     * @param[in] value The byte value to assign.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_SetStaticFieldByName_Byte)(ani_env *env, ani_class cls, const char *name, ani_byte value);

    /**
     * @brief Sets a short value to a static field of a class by its name.
     *
     * This function assigns a short value to the specified static field of the given class by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] name The name of the static field to modify.
     * @param[in] value The short value to assign.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_SetStaticFieldByName_Short)(ani_env *env, ani_class cls, const char *name, ani_short value);

    /**
     * @brief Sets an integer value to a static field of a class by its name.
     *
     * This function assigns an integer value to the specified static field of the given class by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] name The name of the static field to modify.
     * @param[in] value The integer value to assign.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_SetStaticFieldByName_Int)(ani_env *env, ani_class cls, const char *name, ani_int value);

    /**
     * @brief Sets a long value to a static field of a class by its name.
     *
     * This function assigns a long value to the specified static field of the given class by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] name The name of the static field to modify.
     * @param[in] value The long value to assign.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_SetStaticFieldByName_Long)(ani_env *env, ani_class cls, const char *name, ani_long value);

    /**
     * @brief Sets a float value to a static field of a class by its name.
     *
     * This function assigns a float value to the specified static field of the given class by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] name The name of the static field to modify.
     * @param[in] value The float value to assign.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_SetStaticFieldByName_Float)(ani_env *env, ani_class cls, const char *name, ani_float value);

    /**
     * @brief Sets a double value to a static field of a class by its name.
     *
     * This function assigns a double value to the specified static field of the given class by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] name The name of the static field to modify.
     * @param[in] value The double value to assign.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_SetStaticFieldByName_Double)(ani_env *env, ani_class cls, const char *name, ani_double value);

    /**
     * @brief Sets a reference value to a static field of a class by its name.
     *
     * This function assigns a reference value to the specified static field of the given class by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] name The name of the static field to modify.
     * @param[in] value The reference value to assign.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_SetStaticFieldByName_Ref)(ani_env *env, ani_class cls, const char *name, ani_ref value);

    /**
     * @brief Calls a static method with a boolean return type.
     *
     * This function calls the specified static method of a class and retrieves a boolean result using variadic
     * arguments.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] method The static method to call.
     * @param[out] result A pointer to store the boolean result.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethod_Boolean)(ani_env *env, ani_class cls, ani_static_method method,
                                                 ani_boolean *result, ...);

    /**
     * @brief Calls a static method with a boolean return type (array-based).
     *
     * This function calls the specified static method of a class and retrieves a boolean result using arguments from an
     * array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] method The static method to call.
     * @param[out] result A pointer to store the boolean result.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethod_Boolean_A)(ani_env *env, ani_class cls, ani_static_method method,
                                                   ani_boolean *result, const ani_value *args);

    /**
     * @brief Calls a static method with a boolean return type (variadic arguments).
     *
     * This function calls the specified static method of a class and retrieves a boolean result using a `va_list`.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] method The static method to call.
     * @param[out] result A pointer to store the boolean result.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethod_Boolean_V)(ani_env *env, ani_class cls, ani_static_method method,
                                                   ani_boolean *result, va_list args);

    /**
     * @brief Calls a static method with a character return type.
     *
     * This function calls the specified static method of a class and retrieves a character result using variadic
     * arguments.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] method The static method to call.
     * @param[out] result A pointer to store the character result.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethod_Char)(ani_env *env, ani_class cls, ani_static_method method, ani_char *result,
                                              ...);

    /**
     * @brief Calls a static method with a character return type (array-based).
     *
     * This function calls the specified static method of a class and retrieves a character result using arguments from
     * an array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] method The static method to call.
     * @param[out] result A pointer to store the character result.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethod_Char_A)(ani_env *env, ani_class cls, ani_static_method method, ani_char *result,
                                                const ani_value *args);

    /**
     * @brief Calls a static method with a character return type (variadic arguments).
     *
     * This function calls the specified static method of a class and retrieves a character result using a `va_list`.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] method The static method to call.
     * @param[out] result A pointer to store the character result.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethod_Char_V)(ani_env *env, ani_class cls, ani_static_method method, ani_char *result,
                                                va_list args);

    /**
     * @brief Calls a static method with a byte return type.
     *
     * This function calls the specified static method of a class and retrieves a byte result using variadic arguments.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] method The static method to call.
     * @param[out] result A pointer to store the byte result.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethod_Byte)(ani_env *env, ani_class cls, ani_static_method method, ani_byte *result,
                                              ...);

    /**
     * @brief Calls a static method with a byte return type (array-based).
     *
     * This function calls the specified static method of a class and retrieves a byte result using arguments from an
     * array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] method The static method to call.
     * @param[out] result A pointer to store the byte result.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethod_Byte_A)(ani_env *env, ani_class cls, ani_static_method method, ani_byte *result,
                                                const ani_value *args);

    /**
     * @brief Calls a static method with a byte return type (variadic arguments).
     *
     * This function calls the specified static method of a class and retrieves a byte result using a `va_list`.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] method The static method to call.
     * @param[out] result A pointer to store the byte result.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethod_Byte_V)(ani_env *env, ani_class cls, ani_static_method method, ani_byte *result,
                                                va_list args);

    /**
     * @brief Calls a static method with a short return type.
     *
     * This function calls the specified static method of a class and retrieves a short result using variadic arguments.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] method The static method to call.
     * @param[out] result A pointer to store the short result.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethod_Short)(ani_env *env, ani_class cls, ani_static_method method, ani_short *result,
                                               ...);

    /**
     * @brief Calls a static method with a short return type (array-based).
     *
     * This function calls the specified static method of a class and retrieves a short result using arguments from an
     * array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] method The static method to call.
     * @param[out] result A pointer to store the short result.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethod_Short_A)(ani_env *env, ani_class cls, ani_static_method method,
                                                 ani_short *result, const ani_value *args);

    /**
     * @brief Calls a static method with a short return type (variadic arguments).
     *
     * This function calls the specified static method of a class and retrieves a short result using a `va_list`.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] method The static method to call.
     * @param[out] result A pointer to store the short result.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethod_Short_V)(ani_env *env, ani_class cls, ani_static_method method,
                                                 ani_short *result, va_list args);

    /**
     * @brief Calls a static method with an integer return type.
     *
     * This function calls the specified static method of a class and retrieves an integer result using variadic
     * arguments.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] method The static method to call.
     * @param[out] result A pointer to store the integer result.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethod_Int)(ani_env *env, ani_class cls, ani_static_method method, ani_int *result,
                                             ...);

    /**
     * @brief Calls a static method with an integer return type (array-based).
     *
     * This function calls the specified static method of a class and retrieves an integer result using arguments from
     * an array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] method The static method to call.
     * @param[out] result A pointer to store the integer result.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethod_Int_A)(ani_env *env, ani_class cls, ani_static_method method, ani_int *result,
                                               const ani_value *args);

    /**
     * @brief Calls a static method with an integer return type (variadic arguments).
     *
     * This function calls the specified static method of a class and retrieves an integer result using a `va_list`.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] method The static method to call.
     * @param[out] result A pointer to store the integer result.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethod_Int_V)(ani_env *env, ani_class cls, ani_static_method method, ani_int *result,
                                               va_list args);

    /**
     * @brief Calls a static method with a long return type.
     *
     * This function calls the specified static method of a class and retrieves a long result using variadic arguments.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] method The static method to call.
     * @param[out] result A pointer to store the long result.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethod_Long)(ani_env *env, ani_class cls, ani_static_method method, ani_long *result,
                                              ...);

    /**
     * @brief Calls a static method with a long return type (array-based).
     *
     * This function calls the specified static method of a class and retrieves a long result using arguments from an
     * array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] method The static method to call.
     * @param[out] result A pointer to store the long result.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethod_Long_A)(ani_env *env, ani_class cls, ani_static_method method, ani_long *result,
                                                const ani_value *args);

    /**
     * @brief Calls a static method with a long return type (variadic arguments).
     *
     * This function calls the specified static method of a class and retrieves a long result using a `va_list`.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] method The static method to call.
     * @param[out] result A pointer to store the long result.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethod_Long_V)(ani_env *env, ani_class cls, ani_static_method method, ani_long *result,
                                                va_list args);

    /**
     * @brief Calls a static method with a float return type.
     *
     * This function calls the specified static method of a class and retrieves a float result using variadic arguments.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] method The static method to call.
     * @param[out] result A pointer to store the float result.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethod_Float)(ani_env *env, ani_class cls, ani_static_method method, ani_float *result,
                                               ...);

    /**
     * @brief Calls a static method with a float return type (array-based).
     *
     * This function calls the specified static method of a class and retrieves a float result using arguments from an
     * array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] method The static method to call.
     * @param[out] result A pointer to store the float result.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethod_Float_A)(ani_env *env, ani_class cls, ani_static_method method,
                                                 ani_float *result, const ani_value *args);

    /**
     * @brief Calls a static method with a float return type (variadic arguments).
     *
     * This function calls the specified static method of a class and retrieves a float result using a `va_list`.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] method The static method to call.
     * @param[out] result A pointer to store the float result.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethod_Float_V)(ani_env *env, ani_class cls, ani_static_method method,
                                                 ani_float *result, va_list args);

    /**
     * @brief Calls a static method with a double return type.
     *
     * This function calls the specified static method of a class and retrieves a double result using variadic
     * arguments.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] method The static method to call.
     * @param[out] result A pointer to store the double result.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethod_Double)(ani_env *env, ani_class cls, ani_static_method method,
                                                ani_double *result, ...);

    /**
     * @brief Calls a static method with a double return type (array-based).
     *
     * This function calls the specified static method of a class and retrieves a double result using arguments from an
     * array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] method The static method to call.
     * @param[out] result A pointer to store the double result.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethod_Double_A)(ani_env *env, ani_class cls, ani_static_method method,
                                                  ani_double *result, const ani_value *args);

    /**
     * @brief Calls a static method with a double return type (variadic arguments).
     *
     * This function calls the specified static method of a class and retrieves a double result using a `va_list`.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] method The static method to call.
     * @param[out] result A pointer to store the double result.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethod_Double_V)(ani_env *env, ani_class cls, ani_static_method method,
                                                  ani_double *result, va_list args);

    /**
     * @brief Calls a static method with a reference return type.
     *
     * This function calls the specified static method of a class and retrieves a reference result using variadic
     * arguments.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] method The static method to call.
     * @param[out] result A pointer to store the reference result.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethod_Ref)(ani_env *env, ani_class cls, ani_static_method method, ani_ref *result,
                                             ...);

    /**
     * @brief Calls a static method with a reference return type (array-based).
     *
     * This function calls the specified static method of a class and retrieves a reference result using arguments from
     * an array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] method The static method to call.
     * @param[out] result A pointer to store the reference result.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethod_Ref_A)(ani_env *env, ani_class cls, ani_static_method method, ani_ref *result,
                                               const ani_value *args);

    /**
     * @brief Calls a static method with a reference return type (variadic arguments).
     *
     * This function calls the specified static method of a class and retrieves a reference result using a `va_list`.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] method The static method to call.
     * @param[out] result A pointer to store the reference result.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethod_Ref_V)(ani_env *env, ani_class cls, ani_static_method method, ani_ref *result,
                                               va_list args);

    /**
     * @brief Calls a static method with no return value.
     *
     * This function calls the specified static method of a class using variadic arguments. The method does not return a
     * value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] method The static method to call.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethod_Void)(ani_env *env, ani_class cls, ani_static_method method, ...);

    /**
     * @brief Calls a static method with no return value (array-based).
     *
     * This function calls the specified static method of a class using arguments from an array. The method does not
     * return a value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] method The static method to call.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethod_Void_A)(ani_env *env, ani_class cls, ani_static_method method,
                                                const ani_value *args);

    /**
     * @brief Calls a static method with no return value (variadic arguments).
     *
     * This function calls the specified static method of a class using a `va_list`. The method does not return a value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] method The static method to call.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethod_Void_V)(ani_env *env, ani_class cls, ani_static_method method, va_list args);

    /**
     * @brief Calls a static method by name with a boolean return type.
     *
     * This function calls the specified static method of a class by its name and retrieves a boolean result using
     * variadic arguments.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[out] result A pointer to store the boolean result.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Boolean)(ani_env *env, ani_class cls, const char *name,
                                                       ani_boolean *result, ...);

    /**
     * @brief Calls a static method by name with a boolean return type (array-based).
     *
     * This function calls the specified static method of a class by its name and retrieves a boolean result using
     * arguments from an array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[out] result A pointer to store the boolean result.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Boolean_A)(ani_env *env, ani_class cls, const char *name,
                                                         ani_boolean *result, const ani_value *args);

    /**
     * @brief Calls a static method by name with a boolean return type (variadic arguments).
     *
     * This function calls the specified static method of a class by its name and retrieves a boolean result using a
     * `va_list`.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[out] result A pointer to store the boolean result.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Boolean_V)(ani_env *env, ani_class cls, const char *name,
                                                         ani_boolean *result, va_list args);

    /**
     * @brief Calls a static method by name with a char return type.
     *
     * This function calls the specified static method of a class by its name and retrieves a char result using variadic
     * arguments.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[out] result A pointer to store the char result.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Char)(ani_env *env, ani_class cls, const char *name, ani_char *result,
                                                    ...);

    /**
     * @brief Calls a static method by name with a char return type (array-based).
     *
     * This function calls the specified static method of a class by its name and retrieves a char result using
     * arguments from an array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[out] result A pointer to store the char result.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Char_A)(ani_env *env, ani_class cls, const char *name, ani_char *result,
                                                      const ani_value *args);

    /**
     * @brief Calls a static method by name with a char return type (variadic arguments).
     *
     * This function calls the specified static method of a class by its name and retrieves a char result using a
     * `va_list`.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[out] result A pointer to store the char result.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Char_V)(ani_env *env, ani_class cls, const char *name, ani_char *result,
                                                      va_list args);

    /**
     * @brief Calls a static method by name with a byte return type.
     *
     * This function calls the specified static method of a class by its name and retrieves a byte result using variadic
     * arguments.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[out] result A pointer to store the byte result.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Byte)(ani_env *env, ani_class cls, const char *name, ani_byte *result,
                                                    ...);

    /**
     * @brief Calls a static method by name with a byte return type (array-based).
     *
     * This function calls the specified static method of a class by its name and retrieves a byte result using
     * arguments from an array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[out] result A pointer to store the byte result.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Byte_A)(ani_env *env, ani_class cls, const char *name, ani_byte *result,
                                                      const ani_value *args);

    /**
     * @brief Calls a static method by name with a byte return type (variadic arguments).
     *
     * This function calls the specified static method of a class by its name and retrieves a byte result using a
     * `va_list`.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[out] result A pointer to store the byte result.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Byte_V)(ani_env *env, ani_class cls, const char *name, ani_byte *result,
                                                      va_list args);

    /**
     * @brief Calls a static method by name with a short return type.
     *
     * This function calls the specified static method of a class by its name and retrieves a short result using
     * variadic arguments.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[out] result A pointer to store the short result.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Short)(ani_env *env, ani_class cls, const char *name, ani_short *result,
                                                     ...);

    /**
     * @brief Calls a static method by name with a short return type (array-based).
     *
     * This function calls the specified static method of a class by its name and retrieves a short result using
     * arguments from an array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[out] result A pointer to store the short result.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Short_A)(ani_env *env, ani_class cls, const char *name, ani_short *result,
                                                       const ani_value *args);

    /**
     * @brief Calls a static method by name with a short return type (variadic arguments).
     *
     * This function calls the specified static method of a class by its name and retrieves a short result using a
     * `va_list`.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[out] result A pointer to store the short result.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Short_V)(ani_env *env, ani_class cls, const char *name, ani_short *result,
                                                       va_list args);

    /**
     * @brief Calls a static method by name with a integer return type.
     *
     * This function calls the specified static method of a class by its name and retrieves a integer result using
     * variadic arguments.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[out] result A pointer to store the integer result.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Int)(ani_env *env, ani_class cls, const char *name, ani_int *result, ...);

    /**
     * @brief Calls a static method by name with a integer return type (array-based).
     *
     * This function calls the specified static method of a class by its name and retrieves a integer result using
     * arguments from an array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[out] result A pointer to store the integer result.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Int_A)(ani_env *env, ani_class cls, const char *name, ani_int *result,
                                                     const ani_value *args);

    /**
     * @brief Calls a static method by name with a integer return type (variadic arguments).
     *
     * This function calls the specified static method of a class by its name and retrieves a integer result using a
     * `va_list`.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[out] result A pointer to store the integer result.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Int_V)(ani_env *env, ani_class cls, const char *name, ani_int *result,
                                                     va_list args);

    /**
     * @brief Calls a static method by name with a long return type.
     *
     * This function calls the specified static method of a class by its name and retrieves a long result using variadic
     * arguments.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[out] result A pointer to store the long result.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Long)(ani_env *env, ani_class cls, const char *name, ani_long *result,
                                                    ...);

    /**
     * @brief Calls a static method by name with a long return type (array-based).
     *
     * This function calls the specified static method of a class by its name and retrieves a long result using
     * arguments from an array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[out] result A pointer to store the long result.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Long_A)(ani_env *env, ani_class cls, const char *name, ani_long *result,
                                                      const ani_value *args);

    /**
     * @brief Calls a static method by name with a long return type (variadic arguments).
     *
     * This function calls the specified static method of a class by its name and retrieves a long result using a
     * `va_list`.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[out] result A pointer to store the long result.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Long_V)(ani_env *env, ani_class cls, const char *name, ani_long *result,
                                                      va_list args);

    /**
     * @brief Calls a static method by name with a float return type.
     *
     * This function calls the specified static method of a class by its name and retrieves a float result using
     * variadic arguments.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[out] result A pointer to store the float result.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Float)(ani_env *env, ani_class cls, const char *name, ani_float *result,
                                                     ...);

    /**
     * @brief Calls a static method by name with a float return type (array-based).
     *
     * This function calls the specified static method of a class by its name and retrieves a float result using
     * arguments from an array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[out] result A pointer to store the float result.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Float_A)(ani_env *env, ani_class cls, const char *name, ani_float *result,
                                                       const ani_value *args);

    /**
     * @brief Calls a static method by name with a float return type (variadic arguments).
     *
     * This function calls the specified static method of a class by its name and retrieves a float result using a
     * `va_list`.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[out] result A pointer to store the float result.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Float_V)(ani_env *env, ani_class cls, const char *name, ani_float *result,
                                                       va_list args);

    /**
     * @brief Calls a static method by name with a double return type.
     *
     * This function calls the specified static method of a class by its name and retrieves a double result using
     * variadic arguments.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[out] result A pointer to store the double result.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Double)(ani_env *env, ani_class cls, const char *name, ani_double *result,
                                                      ...);

    /**
     * @brief Calls a static method by name with a double return type (array-based).
     *
     * This function calls the specified static method of a class by its name and retrieves a double result using
     * arguments from an array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[out] result A pointer to store the double result.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Double_A)(ani_env *env, ani_class cls, const char *name,
                                                        ani_double *result, const ani_value *args);

    /**
     * @brief Calls a static method by name with a double return type (variadic arguments).
     *
     * This function calls the specified static method of a class by its name and retrieves a double result using a
     * `va_list`.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[out] result A pointer to store the double result.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Double_V)(ani_env *env, ani_class cls, const char *name,
                                                        ani_double *result, va_list args);

    /**
     * @brief Calls a static method by name with a reference return type.
     *
     * This function calls the specified static method of a class by its name and retrieves a reference result using
     * variadic arguments.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[out] result A pointer to store the reference result.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Ref)(ani_env *env, ani_class cls, const char *name, ani_ref *result, ...);

    /**
     * @brief Calls a static method by name with a reference return type (array-based).
     *
     * This function calls the specified static method of a class by its name and retrieves a reference result using
     * arguments from an array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[out] result A pointer to store the reference result.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Ref_A)(ani_env *env, ani_class cls, const char *name, ani_ref *result,
                                                     const ani_value *args);

    /**
     * @brief Calls a static method by name with a reference return type (variadic arguments).
     *
     * This function calls the specified static method of a class by its name and retrieves a reference result using a
     * `va_list`.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[out] result A pointer to store the reference result.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Ref_V)(ani_env *env, ani_class cls, const char *name, ani_ref *result,
                                                     va_list args);

    /**
     * @brief Calls a static method by name with no return value.
     *
     * This function calls the specified static method of a class by its name using variadic arguments. The method does
     * not return a value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Void)(ani_env *env, ani_class cls, const char *name, ...);

    /**
     * @brief Calls a static method by name with no return value (array-based).
     *
     * This function calls the specified static method of a class by its name using arguments from an array. The method
     * does not return a value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Void_A)(ani_env *env, ani_class cls, const char *name,
                                                      const ani_value *args);

    /**
     * @brief Calls a static method by name with no return value (variadic arguments).
     *
     * This function calls the specified static method of a class by its name using a `va_list`. The method does not
     * return a value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Void_V)(ani_env *env, ani_class cls, const char *name, va_list args);

    /**
     * @brief Retrieves a boolean value from a field of an object.
     *
     * This function retrieves the boolean value of the specified field from the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] field The field to retrieve the boolean value from.
     * @param[out] result A pointer to store the retrieved boolean value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetField_Boolean)(ani_env *env, ani_object object, ani_field field, ani_boolean *result);

    /**
     * @brief Retrieves a char value from a field of an object.
     *
     * This function retrieves the char value of the specified field from the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] field The field to retrieve the char value from.
     * @param[out] result A pointer to store the retrieved char value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetField_Char)(ani_env *env, ani_object object, ani_field field, ani_char *result);

    /**
     * @brief Retrieves a byte value from a field of an object.
     *
     * This function retrieves the byte value of the specified field from the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] field The field to retrieve the byte value from.
     * @param[out] result A pointer to store the retrieved byte value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetField_Byte)(ani_env *env, ani_object object, ani_field field, ani_byte *result);

    /**
     * @brief Retrieves a short value from a field of an object.
     *
     * This function retrieves the short value of the specified field from the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] field The field to retrieve the short value from.
     * @param[out] result A pointer to store the retrieved short value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetField_Short)(ani_env *env, ani_object object, ani_field field, ani_short *result);

    /**
     * @brief Retrieves a integer value from a field of an object.
     *
     * This function retrieves the integer value of the specified field from the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] field The field to retrieve the integer value from.
     * @param[out] result A pointer to store the retrieved integer value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetField_Int)(ani_env *env, ani_object object, ani_field field, ani_int *result);

    /**
     * @brief Retrieves a long value from a field of an object.
     *
     * This function retrieves the long value of the specified field from the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] field The field to retrieve the long value from.
     * @param[out] result A pointer to store the retrieved long value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetField_Long)(ani_env *env, ani_object object, ani_field field, ani_long *result);

    /**
     * @brief Retrieves a float value from a field of an object.
     *
     * This function retrieves the float value of the specified field from the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] field The field to retrieve the float value from.
     * @param[out] result A pointer to store the retrieved float value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetField_Float)(ani_env *env, ani_object object, ani_field field, ani_float *result);

    /**
     * @brief Retrieves a double value from a field of an object.
     *
     * This function retrieves the double value of the specified field from the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] field The field to retrieve the double value from.
     * @param[out] result A pointer to store the retrieved double value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetField_Double)(ani_env *env, ani_object object, ani_field field, ani_double *result);

    /**
     * @brief Retrieves a reference value from a field of an object.
     *
     * This function retrieves the reference value of the specified field from the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] field The field to retrieve the reference value from.
     * @param[out] result A pointer to store the retrieved reference value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetField_Ref)(ani_env *env, ani_object object, ani_field field, ani_ref *result);

    /**
     * @brief Sets a boolean value to a field of an object.
     *
     * This function assigns a boolean value to the specified field of the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] field The field to set the boolean value to.
     * @param[in] value The boolean value to assign to the field.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetField_Boolean)(ani_env *env, ani_object object, ani_field field, ani_boolean value);

    /**
     * @brief Sets a char value to a field of an object.
     *
     * This function assigns a char value to the specified field of the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] field The field to set the char value to.
     * @param[in] value The char value to assign to the field.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetField_Char)(ani_env *env, ani_object object, ani_field field, ani_char value);

    /**
     * @brief Sets a byte value to a field of an object.
     *
     * This function assigns a byte value to the specified field of the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] field The field to set the byte value to.
     * @param[in] value The byte value to assign to the field.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetField_Byte)(ani_env *env, ani_object object, ani_field field, ani_byte value);

    /**
     * @brief Sets a short value to a field of an object.
     *
     * This function assigns a short value to the specified field of the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] field The field to set the short value to.
     * @param[in] value The short value to assign to the field.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetField_Short)(ani_env *env, ani_object object, ani_field field, ani_short value);

    /**
     * @brief Sets a integer value to a field of an object.
     *
     * This function assigns a integer value to the specified field of the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] field The field to set the integer value to.
     * @param[in] value The integer value to assign to the field.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetField_Int)(ani_env *env, ani_object object, ani_field field, ani_int value);

    /**
     * @brief Sets a long value to a field of an object.
     *
     * This function assigns a long value to the specified field of the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] field The field to set the long value to.
     * @param[in] value The long value to assign to the field.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetField_Long)(ani_env *env, ani_object object, ani_field field, ani_long value);

    /**
     * @brief Sets a float value to a field of an object.
     *
     * This function assigns a float value to the specified field of the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] field The field to set the float value to.
     * @param[in] value The float value to assign to the field.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetField_Float)(ani_env *env, ani_object object, ani_field field, ani_float value);

    /**
     * @brief Sets a double value to a field of an object.
     *
     * This function assigns a double value to the specified field of the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] field The field to set the double value to.
     * @param[in] value The double value to assign to the field.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetField_Double)(ani_env *env, ani_object object, ani_field field, ani_double value);

    /**
     * @brief Sets a reference value to a field of an object.
     *
     * This function assigns a reference value to the specified field of the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] field The field to set the reference value to.
     * @param[in] value The reference value to assign to the field.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetField_Ref)(ani_env *env, ani_object object, ani_field field, ani_ref value);

    /**
     * @brief Retrieves a boolean value from a field of an object by its name.
     *
     * This function retrieves the boolean value of the specified field from the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] name The name of the field to retrieve the boolean value from.
     * @param[out] result A pointer to store the retrieved boolean value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetFieldByName_Boolean)(ani_env *env, ani_object object, const char *name, ani_boolean *result);

    /**
     * @brief Retrieves a char value from a field of an object by its name.
     *
     * This function retrieves the char value of the specified field from the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] name The name of the field to retrieve the char value from.
     * @param[out] result A pointer to store the retrieved char value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetFieldByName_Char)(ani_env *env, ani_object object, const char *name, ani_char *result);

    /**
     * @brief Retrieves a byte value from a field of an object by its name.
     *
     * This function retrieves the byte value of the specified field from the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] name The name of the field to retrieve the byte value from.
     * @param[out] result A pointer to store the retrieved byte value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetFieldByName_Byte)(ani_env *env, ani_object object, const char *name, ani_byte *result);

    /**
     * @brief Retrieves a short value from a field of an object by its name.
     *
     * This function retrieves the short value of the specified field from the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] name The name of the field to retrieve the short value from.
     * @param[out] result A pointer to store the retrieved short value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetFieldByName_Short)(ani_env *env, ani_object object, const char *name, ani_short *result);

    /**
     * @brief Retrieves a integer value from a field of an object by its name.
     *
     * This function retrieves the integer value of the specified field from the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] name The name of the field to retrieve the integer value from.
     * @param[out] result A pointer to store the retrieved integer value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetFieldByName_Int)(ani_env *env, ani_object object, const char *name, ani_int *result);

    /**
     * @brief Retrieves a long value from a field of an object by its name.
     *
     * This function retrieves the long value of the specified field from the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] name The name of the field to retrieve the long value from.
     * @param[out] result A pointer to store the retrieved long value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetFieldByName_Long)(ani_env *env, ani_object object, const char *name, ani_long *result);

    /**
     * @brief Retrieves a float value from a field of an object by its name.
     *
     * This function retrieves the float value of the specified field from the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] name The name of the field to retrieve the float value from.
     * @param[out] result A pointer to store the retrieved float value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetFieldByName_Float)(ani_env *env, ani_object object, const char *name, ani_float *result);

    /**
     * @brief Retrieves a double value from a field of an object by its name.
     *
     * This function retrieves the double value of the specified field from the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] name The name of the field to retrieve the double value from.
     * @param[out] result A pointer to store the retrieved double value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetFieldByName_Double)(ani_env *env, ani_object object, const char *name, ani_double *result);

    /**
     * @brief Retrieves a reference value from a field of an object by its name.
     *
     * This function retrieves the reference value of the specified field from the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] name The name of the field to retrieve the reference value from.
     * @param[out] result A pointer to store the retrieved reference value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetFieldByName_Ref)(ani_env *env, ani_object object, const char *name, ani_ref *result);

    /**
     * @brief Sets a boolean value to a field of an object by its name.
     *
     * This function assigns a boolean value to the specified field of the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] name The name of the field to set the boolean value to.
     * @param[in] value The boolean value to assign to the field.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetFieldByName_Boolean)(ani_env *env, ani_object object, const char *name, ani_boolean value);

    /**
     * @brief Sets a char value to a field of an object by its name.
     *
     * This function assigns a char value to the specified field of the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] name The name of the field to set the char value to.
     * @param[in] value The char value to assign to the field.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetFieldByName_Char)(ani_env *env, ani_object object, const char *name, ani_char value);

    /**
     * @brief Sets a byte value to a field of an object by its name.
     *
     * This function assigns a byte value to the specified field of the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] name The name of the field to set the byte value to.
     * @param[in] value The byte value to assign to the field.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetFieldByName_Byte)(ani_env *env, ani_object object, const char *name, ani_byte value);

    /**
     * @brief Sets a short value to a field of an object by its name.
     *
     * This function assigns a short value to the specified field of the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] name The name of the field to set the short value to.
     * @param[in] value The short value to assign to the field.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetFieldByName_Short)(ani_env *env, ani_object object, const char *name, ani_short value);

    /**
     * @brief Sets a integer value to a field of an object by its name.
     *
     * This function assigns a integer value to the specified field of the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] name The name of the field to set the integer value to.
     * @param[in] value The integer value to assign to the field.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetFieldByName_Int)(ani_env *env, ani_object object, const char *name, ani_int value);

    /**
     * @brief Sets a long value to a field of an object by its name.
     *
     * This function assigns a long value to the specified field of the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] name The name of the field to set the long value to.
     * @param[in] value The long value to assign to the field.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetFieldByName_Long)(ani_env *env, ani_object object, const char *name, ani_long value);

    /**
     * @brief Sets a float value to a field of an object by its name.
     *
     * This function assigns a float value to the specified field of the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] name The name of the field to set the float value to.
     * @param[in] value The float value to assign to the field.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetFieldByName_Float)(ani_env *env, ani_object object, const char *name, ani_float value);

    /**
     * @brief Sets a double value to a field of an object by its name.
     *
     * This function assigns a double value to the specified field of the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] name The name of the field to set the double value to.
     * @param[in] value The double value to assign to the field.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetFieldByName_Double)(ani_env *env, ani_object object, const char *name, ani_double value);

    /**
     * @brief Sets a reference value to a field of an object by its name.
     *
     * This function assigns a reference value to the specified field of the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the field.
     * @param[in] name The name of the field to set the reference value to.
     * @param[in] value The reference value to assign to the field.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetFieldByName_Ref)(ani_env *env, ani_object object, const char *name, ani_ref value);

    /**
     * @brief Retrieves a boolean value from a property of an object.
     *
     * This function retrieves the boolean value of the specified property from the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] property The property to retrieve the boolean value from.
     * @param[out] result A pointer to store the retrieved boolean value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetProperty_Boolean)(ani_env *env, ani_object object, ani_property property,
                                             ani_boolean *result);

    /**
     * @brief Retrieves a char value from a property of an object.
     *
     * This function retrieves the char value of the specified property from the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] property The property to retrieve the char value from.
     * @param[out] result A pointer to store the retrieved char value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetProperty_Char)(ani_env *env, ani_object object, ani_property property, ani_char *result);

    /**
     * @brief Retrieves a byte value from a property of an object.
     *
     * This function retrieves the byte value of the specified property from the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] property The property to retrieve the byte value from.
     * @param[out] result A pointer to store the retrieved byte value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetProperty_Byte)(ani_env *env, ani_object object, ani_property property, ani_byte *result);

    /**
     * @brief Retrieves a short value from a property of an object.
     *
     * This function retrieves the short value of the specified property from the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] property The property to retrieve the short value from.
     * @param[out] result A pointer to store the retrieved short value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetProperty_Short)(ani_env *env, ani_object object, ani_property property, ani_short *result);

    /**
     * @brief Retrieves a integer value from a property of an object.
     *
     * This function retrieves the integer value of the specified property from the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] property The property to retrieve the integer value from.
     * @param[out] result A pointer to store the retrieved integer value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetProperty_Int)(ani_env *env, ani_object object, ani_property property, ani_int *result);

    /**
     * @brief Retrieves a long value from a property of an object.
     *
     * This function retrieves the long value of the specified property from the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] property The property to retrieve the long value from.
     * @param[out] result A pointer to store the retrieved long value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetProperty_Long)(ani_env *env, ani_object object, ani_property property, ani_long *result);

    /**
     * @brief Retrieves a float value from a property of an object.
     *
     * This function retrieves the float value of the specified property from the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] property The property to retrieve the float value from.
     * @param[out] result A pointer to store the retrieved float value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetProperty_Float)(ani_env *env, ani_object object, ani_property property, ani_float *result);

    /**
     * @brief Retrieves a double value from a property of an object.
     *
     * This function retrieves the double value of the specified property from the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] property The property to retrieve the double value from.
     * @param[out] result A pointer to store the retrieved double value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetProperty_Double)(ani_env *env, ani_object object, ani_property property, ani_double *result);

    /**
     * @brief Retrieves a reference value from a property of an object.
     *
     * This function retrieves the reference value of the specified property from the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] property The property to retrieve the reference value from.
     * @param[out] result A pointer to store the retrieved reference value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetProperty_Ref)(ani_env *env, ani_object object, ani_property property, ani_ref *result);

    /**
     * @brief Sets a boolean value to a property of an object.
     *
     * This function assigns a boolean value to the specified property of the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] property The property to set the boolean value to.
     * @param[in] value The boolean value to assign to the property.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetProperty_Boolean)(ani_env *env, ani_object object, ani_property property, ani_boolean value);

    /**
     * @brief Sets a char value to a property of an object.
     *
     * This function assigns a char value to the specified property of the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] property The property to set the char value to.
     * @param[in] value The char value to assign to the property.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetProperty_Char)(ani_env *env, ani_object object, ani_property property, ani_char value);

    /**
     * @brief Sets a byte value to a property of an object.
     *
     * This function assigns a byte value to the specified property of the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] property The property to set the byte value to.
     * @param[in] value The byte value to assign to the property.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetProperty_Byte)(ani_env *env, ani_object object, ani_property property, ani_byte value);

    /**
     * @brief Sets a short value to a property of an object.
     *
     * This function assigns a short value to the specified property of the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] property The property to set the short value to.
     * @param[in] value The short value to assign to the property.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetProperty_Short)(ani_env *env, ani_object object, ani_property property, ani_short value);

    /**
     * @brief Sets a integer value to a property of an object.
     *
     * This function assigns a integer value to the specified property of the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] property The property to set the integer value to.
     * @param[in] value The integer value to assign to the property.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetProperty_Int)(ani_env *env, ani_object object, ani_property property, ani_int value);

    /**
     * @brief Sets a long value to a property of an object.
     *
     * This function assigns a long value to the specified property of the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] property The property to set the long value to.
     * @param[in] value The long value to assign to the property.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetProperty_Long)(ani_env *env, ani_object object, ani_property property, ani_long value);

    /**
     * @brief Sets a float value to a property of an object.
     *
     * This function assigns a float value to the specified property of the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] property The property to set the float value to.
     * @param[in] value The float value to assign to the property.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetProperty_Float)(ani_env *env, ani_object object, ani_property property, ani_float value);

    /**
     * @brief Sets a double value to a property of an object.
     *
     * This function assigns a double value to the specified property of the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] property The property to set the double value to.
     * @param[in] value The double value to assign to the property.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetProperty_Double)(ani_env *env, ani_object object, ani_property property, ani_double value);

    /**
     * @brief Sets a reference value to a property of an object.
     *
     * This function assigns a reference value to the specified property of the given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] property The property to set the reference value to.
     * @param[in] value The reference value to assign to the property.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetProperty_Ref)(ani_env *env, ani_object object, ani_property property, ani_ref value);

    /**
     * @brief Retrieves a boolean value from a property of an object by its name.
     *
     * This function retrieves the boolean value of the specified property from the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] name The name of the property to retrieve the boolean value from.
     * @param[out] result A pointer to store the retrieved boolean value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetPropertyByName_Boolean)(ani_env *env, ani_object object, const char *name,
                                                   ani_boolean *result);

    /**
     * @brief Retrieves a char value from a property of an object by its name.
     *
     * This function retrieves the char value of the specified property from the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] name The name of the property to retrieve the char value from.
     * @param[out] result A pointer to store the retrieved char value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetPropertyByName_Char)(ani_env *env, ani_object object, const char *name, ani_char *result);

    /**
     * @brief Retrieves a byte value from a property of an object by its name.
     *
     * This function retrieves the byte value of the specified property from the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] name The name of the property to retrieve the byte value from.
     * @param[out] result A pointer to store the retrieved byte value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetPropertyByName_Byte)(ani_env *env, ani_object object, const char *name, ani_byte *result);

    /**
     * @brief Retrieves a short value from a property of an object by its name.
     *
     * This function retrieves the short value of the specified property from the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] name The name of the property to retrieve the short value from.
     * @param[out] result A pointer to store the retrieved short value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetPropertyByName_Short)(ani_env *env, ani_object object, const char *name, ani_short *result);

    /**
     * @brief Retrieves a integer value from a property of an object by its name.
     *
     * This function retrieves the integer value of the specified property from the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] name The name of the property to retrieve the integer value from.
     * @param[out] result A pointer to store the retrieved integer value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetPropertyByName_Int)(ani_env *env, ani_object object, const char *name, ani_int *result);

    /**
     * @brief Retrieves a long value from a property of an object by its name.
     *
     * This function retrieves the long value of the specified property from the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] name The name of the property to retrieve the long value from.
     * @param[out] result A pointer to store the retrieved long value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetPropertyByName_Long)(ani_env *env, ani_object object, const char *name, ani_long *result);

    /**
     * @brief Retrieves a float value from a property of an object by its name.
     *
     * This function retrieves the float value of the specified property from the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] name The name of the property to retrieve the float value from.
     * @param[out] result A pointer to store the retrieved float value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetPropertyByName_Float)(ani_env *env, ani_object object, const char *name, ani_float *result);

    /**
     * @brief Retrieves a double value from a property of an object by its name.
     *
     * This function retrieves the double value of the specified property from the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] name The name of the property to retrieve the double value from.
     * @param[out] result A pointer to store the retrieved double value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetPropertyByName_Double)(ani_env *env, ani_object object, const char *name,
                                                  ani_double *result);

    /**
     * @brief Retrieves a reference value from a property of an object by its name.
     *
     * This function retrieves the reference value of the specified property from the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] name The name of the property to retrieve the reference value from.
     * @param[out] result A pointer to store the retrieved reference value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_GetPropertyByName_Ref)(ani_env *env, ani_object object, const char *name, ani_ref *result);

    /**
     * @brief Sets a boolean value to a property of an object by its name.
     *
     * This function assigns a boolean value to the specified property of the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] name The name of the property to set the boolean value to.
     * @param[in] value The boolean value to assign to the property.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetPropertyByName_Boolean)(ani_env *env, ani_object object, const char *name,
                                                   ani_boolean value);

    /**
     * @brief Sets a char value to a property of an object by its name.
     *
     * This function assigns a char value to the specified property of the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] name The name of the property to set the char value to.
     * @param[in] value The char value to assign to the property.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetPropertyByName_Char)(ani_env *env, ani_object object, const char *name, ani_char value);

    /**
     * @brief Sets a byte value to a property of an object by its name.
     *
     * This function assigns a byte value to the specified property of the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] name The name of the property to set the byte value to.
     * @param[in] value The byte value to assign to the property.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetPropertyByName_Byte)(ani_env *env, ani_object object, const char *name, ani_byte value);

    /**
     * @brief Sets a short value to a property of an object by its name.
     *
     * This function assigns a short value to the specified property of the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] name The name of the property to set the short value to.
     * @param[in] value The short value to assign to the property.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetPropertyByName_Short)(ani_env *env, ani_object object, const char *name, ani_short value);

    /**
     * @brief Sets a integer value to a property of an object by its name.
     *
     * This function assigns a integer value to the specified property of the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] name The name of the property to set the integer value to.
     * @param[in] value The integer value to assign to the property.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetPropertyByName_Int)(ani_env *env, ani_object object, const char *name, ani_int value);

    /**
     * @brief Sets a long value to a property of an object by its name.
     *
     * This function assigns a long value to the specified property of the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] name The name of the property to set the long value to.
     * @param[in] value The long value to assign to the property.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetPropertyByName_Long)(ani_env *env, ani_object object, const char *name, ani_long value);

    /**
     * @brief Sets a float value to a property of an object by its name.
     *
     * This function assigns a float value to the specified property of the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] name The name of the property to set the float value to.
     * @param[in] value The float value to assign to the property.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetPropertyByName_Float)(ani_env *env, ani_object object, const char *name, ani_float value);

    /**
     * @brief Sets a double value to a property of an object by its name.
     *
     * This function assigns a double value to the specified property of the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] name The name of the property to set the double value to.
     * @param[in] value The double value to assign to the property.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetPropertyByName_Double)(ani_env *env, ani_object object, const char *name, ani_double value);

    /**
     * @brief Sets a reference value to a property of an object by its name.
     *
     * This function assigns a reference value to the specified property of the given object by its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object containing the property.
     * @param[in] name The name of the property to set the reference value to.
     * @param[in] value The reference value to assign to the property.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_SetPropertyByName_Ref)(ani_env *env, ani_object object, const char *name, ani_ref value);

    /**
     * @brief Calls a method on an object and retrieves a boolean return value.
     *
     * This function calls the specified method of an object using variadic arguments and retrieves a boolean result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] method The method to call.
     * @param[out] result A pointer to store the boolean return value.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethod_Boolean)(ani_env *env, ani_object object, ani_method method, ani_boolean *result,
                                            ...);

    /**
     * @brief Calls a method on an object and retrieves a boolean return value (array-based).
     *
     * This function calls the specified method of an object using arguments provided in an array and retrieves a
     * boolean result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] method The method to call.
     * @param[out] result A pointer to store the boolean return value.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethod_Boolean_A)(ani_env *env, ani_object object, ani_method method, ani_boolean *result,
                                              const ani_value *args);

    /**
     * @brief Calls a method on an object and retrieves a boolean return value (variadic arguments).
     *
     * This function calls the specified method of an object using a `va_list` and retrieves a boolean result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] method The method to call.
     * @param[out] result A pointer to store the boolean return value.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethod_Boolean_V)(ani_env *env, ani_object object, ani_method method, ani_boolean *result,
                                              va_list args);

    /**
     * @brief Calls a method on an object and retrieves a char return value.
     *
     * This function calls the specified method of an object using variadic arguments and retrieves a char result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] method The method to call.
     * @param[out] result A pointer to store the char return value.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethod_Char)(ani_env *env, ani_object object, ani_method method, ani_char *result, ...);

    /**
     * @brief Calls a method on an object and retrieves a char return value (array-based).
     *
     * This function calls the specified method of an object using arguments provided in an array and retrieves a char
     * result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] method The method to call.
     * @param[out] result A pointer to store the char return value.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethod_Char_A)(ani_env *env, ani_object object, ani_method method, ani_char *result,
                                           const ani_value *args);

    /**
     * @brief Calls a method on an object and retrieves a char return value (variadic arguments).
     *
     * This function calls the specified method of an object using a `va_list` and retrieves a char result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] method The method to call.
     * @param[out] result A pointer to store the char return value.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethod_Char_V)(ani_env *env, ani_object object, ani_method method, ani_char *result,
                                           va_list args);

    /**
     * @brief Calls a method on an object and retrieves a byte return value.
     *
     * This function calls the specified method of an object using variadic arguments and retrieves a byte result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] method The method to call.
     * @param[out] result A pointer to store the byte return value.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethod_Byte)(ani_env *env, ani_object object, ani_method method, ani_byte *result, ...);

    /**
     * @brief Calls a method on an object and retrieves a byte return value (array-based).
     *
     * This function calls the specified method of an object using arguments provided in an array and retrieves a byte
     * result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] method The method to call.
     * @param[out] result A pointer to store the byte return value.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethod_Byte_A)(ani_env *env, ani_object object, ani_method method, ani_byte *result,
                                           const ani_value *args);

    /**
     * @brief Calls a method on an object and retrieves a byte return value (variadic arguments).
     *
     * This function calls the specified method of an object using a `va_list` and retrieves a byte result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] method The method to call.
     * @param[out] result A pointer to store the byte return value.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethod_Byte_V)(ani_env *env, ani_object object, ani_method method, ani_byte *result,
                                           va_list args);

    /**
     * @brief Calls a method on an object and retrieves a short return value.
     *
     * This function calls the specified method of an object using variadic arguments and retrieves a short result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] method The method to call.
     * @param[out] result A pointer to store the short return value.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethod_Short)(ani_env *env, ani_object object, ani_method method, ani_short *result, ...);

    /**
     * @brief Calls a method on an object and retrieves a short return value (array-based).
     *
     * This function calls the specified method of an object using arguments provided in an array and retrieves a short
     * result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] method The method to call.
     * @param[out] result A pointer to store the short return value.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethod_Short_A)(ani_env *env, ani_object object, ani_method method, ani_short *result,
                                            const ani_value *args);

    /**
     * @brief Calls a method on an object and retrieves a short return value (variadic arguments).
     *
     * This function calls the specified method of an object using a `va_list` and retrieves a short result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] method The method to call.
     * @param[out] result A pointer to store the short return value.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethod_Short_V)(ani_env *env, ani_object object, ani_method method, ani_short *result,
                                            va_list args);

    /**
     * @brief Calls a method on an object and retrieves a integer return value.
     *
     * This function calls the specified method of an object using variadic arguments and retrieves a integer result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] method The method to call.
     * @param[out] result A pointer to store the integer return value.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethod_Int)(ani_env *env, ani_object object, ani_method method, ani_int *result, ...);

    /**
     * @brief Calls a method on an object and retrieves a integer return value (array-based).
     *
     * This function calls the specified method of an object using arguments provided in an array and retrieves a
     * integer result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] method The method to call.
     * @param[out] result A pointer to store the integer return value.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethod_Int_A)(ani_env *env, ani_object object, ani_method method, ani_int *result,
                                          const ani_value *args);

    /**
     * @brief Calls a method on an object and retrieves a integer return value (variadic arguments).
     *
     * This function calls the specified method of an object using a `va_list` and retrieves a integer result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] method The method to call.
     * @param[out] result A pointer to store the integer return value.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethod_Int_V)(ani_env *env, ani_object object, ani_method method, ani_int *result,
                                          va_list args);

    /**
     * @brief Calls a method on an object and retrieves a long return value.
     *
     * This function calls the specified method of an object using variadic arguments and retrieves a long result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] method The method to call.
     * @param[out] result A pointer to store the long return value.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethod_Long)(ani_env *env, ani_object object, ani_method method, ani_long *result, ...);

    /**
     * @brief Calls a method on an object and retrieves a long return value (array-based).
     *
     * This function calls the specified method of an object using arguments provided in an array and retrieves a long
     * result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] method The method to call.
     * @param[out] result A pointer to store the long return value.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethod_Long_A)(ani_env *env, ani_object object, ani_method method, ani_long *result,
                                           const ani_value *args);

    /**
     * @brief Calls a method on an object and retrieves a long return value (variadic arguments).
     *
     * This function calls the specified method of an object using a `va_list` and retrieves a long result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] method The method to call.
     * @param[out] result A pointer to store the long return value.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethod_Long_V)(ani_env *env, ani_object object, ani_method method, ani_long *result,
                                           va_list args);

    /**
     * @brief Calls a method on an object and retrieves a float return value.
     *
     * This function calls the specified method of an object using variadic arguments and retrieves a float result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] method The method to call.
     * @param[out] result A pointer to store the float return value.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethod_Float)(ani_env *env, ani_object object, ani_method method, ani_float *result, ...);

    /**
     * @brief Calls a method on an object and retrieves a float return value (array-based).
     *
     * This function calls the specified method of an object using arguments provided in an array and retrieves a float
     * result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] method The method to call.
     * @param[out] result A pointer to store the float return value.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethod_Float_A)(ani_env *env, ani_object object, ani_method method, ani_float *result,
                                            const ani_value *args);

    /**
     * @brief Calls a method on an object and retrieves a float return value (variadic arguments).
     *
     * This function calls the specified method of an object using a `va_list` and retrieves a float result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] method The method to call.
     * @param[out] result A pointer to store the float return value.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethod_Float_V)(ani_env *env, ani_object object, ani_method method, ani_float *result,
                                            va_list args);

    /**
     * @brief Calls a method on an object and retrieves a double return value.
     *
     * This function calls the specified method of an object using variadic arguments and retrieves a double result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] method The method to call.
     * @param[out] result A pointer to store the double return value.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethod_Double)(ani_env *env, ani_object object, ani_method method, ani_double *result, ...);

    /**
     * @brief Calls a method on an object and retrieves a double return value (array-based).
     *
     * This function calls the specified method of an object using arguments provided in an array and retrieves a double
     * result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] method The method to call.
     * @param[out] result A pointer to store the double return value.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethod_Double_A)(ani_env *env, ani_object object, ani_method method, ani_double *result,
                                             const ani_value *args);

    /**
     * @brief Calls a method on an object and retrieves a double return value (variadic arguments).
     *
     * This function calls the specified method of an object using a `va_list` and retrieves a double result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] method The method to call.
     * @param[out] result A pointer to store the double return value.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethod_Double_V)(ani_env *env, ani_object object, ani_method method, ani_double *result,
                                             va_list args);

    /**
     * @brief Calls a method on an object and retrieves a reference return value.
     *
     * This function calls the specified method of an object using variadic arguments and retrieves a reference result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] method The method to call.
     * @param[out] result A pointer to store the reference return value.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethod_Ref)(ani_env *env, ani_object object, ani_method method, ani_ref *result, ...);

    /**
     * @brief Calls a method on an object and retrieves a reference return value (array-based).
     *
     * This function calls the specified method of an object using arguments provided in an array and retrieves a
     * reference result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] method The method to call.
     * @param[out] result A pointer to store the reference return value.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethod_Ref_A)(ani_env *env, ani_object object, ani_method method, ani_ref *result,
                                          const ani_value *args);

    /**
     * @brief Calls a method on an object and retrieves a reference return value (variadic arguments).
     *
     * This function calls the specified method of an object using a `va_list` and retrieves a reference result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] method The method to call.
     * @param[out] result A pointer to store the reference return value.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethod_Ref_V)(ani_env *env, ani_object object, ani_method method, ani_ref *result,
                                          va_list args);

    /**
     * @brief Calls a method on an object with no return value.
     *
     * This function calls the specified method of an object using variadic arguments. The method does not return a
     * value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] method The method to call.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethod_Void)(ani_env *env, ani_object object, ani_method method, ...);

    /**
     * @brief Calls a method on an object with no return value (array-based).
     *
     * This function calls the specified method of an object using arguments provided in an array. The method does not
     * return a value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] method The method to call.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethod_Void_A)(ani_env *env, ani_object object, ani_method method, const ani_value *args);

    /**
     * @brief Calls a method on an object with no return value (variadic arguments).
     *
     * This function calls the specified method of an object using a `va_list`. The method does not return a value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] method The method to call.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethod_Void_V)(ani_env *env, ani_object object, ani_method method, va_list args);

    /**
     * @brief Calls a method by name on an object and retrieves a boolean return value.
     *
     * This function calls the specified method by its name and signature on an object using variadic arguments and
     * retrieves a boolean result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] name The name of the method to call.
     * @param[in] signature The signature of the method to call.
     * @param[out] result A pointer to store the boolean return value.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethodByName_Boolean)(ani_env *env, ani_object object, const char *name,
                                                  const char *signature, ani_boolean *result, ...);

    /**
     * @brief Calls a method by name on an object and retrieves a boolean return value (array-based).
     *
     * This function calls the specified method by its name and signature on an object using arguments provided in an
     * array and retrieves a boolean result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] name The name of the method to call.
     * @param[in] signature The signature of the method to call.
     * @param[out] result A pointer to store the boolean return value.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethodByName_Boolean_A)(ani_env *env, ani_object object, const char *name,
                                                    const char *signature, ani_boolean *result, const ani_value *args);

    /**
     * @brief Calls a method by name on an object and retrieves a boolean return value (variadic arguments).
     *
     * This function calls the specified method by its name and signature on an object using a `va_list` and retrieves a
     * boolean result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] name The name of the method to call.
     * @param[in] signature The signature of the method to call.
     * @param[out] result A pointer to store the boolean return value.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethodByName_Boolean_V)(ani_env *env, ani_object object, const char *name,
                                                    const char *signature, ani_boolean *result, va_list args);

    /**
     * @brief Calls a method by name on an object and retrieves a char return value.
     *
     * This function calls the specified method by its name and signature on an object using variadic arguments and
     * retrieves a char result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] name The name of the method to call.
     * @param[in] signature The signature of the method to call.
     * @param[out] result A pointer to store the char return value.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethodByName_Char)(ani_env *env, ani_object object, const char *name, const char *signature,
                                               ani_char *result, ...);

    /**
     * @brief Calls a method by name on an object and retrieves a char return value (array-based).
     *
     * This function calls the specified method by its name and signature on an object using arguments provided in an
     * array and retrieves a char result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] name The name of the method to call.
     * @param[in] signature The signature of the method to call.
     * @param[out] result A pointer to store the char return value.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethodByName_Char_A)(ani_env *env, ani_object object, const char *name,
                                                 const char *signature, ani_char *result, const ani_value *args);

    /**
     * @brief Calls a method by name on an object and retrieves a char return value (variadic arguments).
     *
     * This function calls the specified method by its name and signature on an object using a `va_list` and retrieves a
     * char result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] name The name of the method to call.
     * @param[in] signature The signature of the method to call.
     * @param[out] result A pointer to store the char return value.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethodByName_Char_V)(ani_env *env, ani_object object, const char *name,
                                                 const char *signature, ani_char *result, va_list args);

    /**
     * @brief Calls a method by name on an object and retrieves a byte return value.
     *
     * This function calls the specified method by its name and signature on an object using variadic arguments and
     * retrieves a byte result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] name The name of the method to call.
     * @param[in] signature The signature of the method to call.
     * @param[out] result A pointer to store the byte return value.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethodByName_Byte)(ani_env *env, ani_object object, const char *name, const char *signature,
                                               ani_byte *result, ...);

    /**
     * @brief Calls a method by name on an object and retrieves a byte return value (array-based).
     *
     * This function calls the specified method by its name and signature on an object using arguments provided in an
     * array and retrieves a byte result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] name The name of the method to call.
     * @param[in] signature The signature of the method to call.
     * @param[out] result A pointer to store the byte return value.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethodByName_Byte_A)(ani_env *env, ani_object object, const char *name,
                                                 const char *signature, ani_byte *result, const ani_value *args);

    /**
     * @brief Calls a method by name on an object and retrieves a byte return value (variadic arguments).
     *
     * This function calls the specified method by its name and signature on an object using a `va_list` and retrieves a
     * byte result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] name The name of the method to call.
     * @param[in] signature The signature of the method to call.
     * @param[out] result A pointer to store the byte return value.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethodByName_Byte_V)(ani_env *env, ani_object object, const char *name,
                                                 const char *signature, ani_byte *result, va_list args);

    /**
     * @brief Calls a method by name on an object and retrieves a short return value.
     *
     * This function calls the specified method by its name and signature on an object using variadic arguments and
     * retrieves a short result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] name The name of the method to call.
     * @param[in] signature The signature of the method to call.
     * @param[out] result A pointer to store the short return value.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethodByName_Short)(ani_env *env, ani_object object, const char *name,
                                                const char *signature, ani_short *result, ...);

    /**
     * @brief Calls a method by name on an object and retrieves a short return value (array-based).
     *
     * This function calls the specified method by its name and signature on an object using arguments provided in an
     * array and retrieves a short result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] name The name of the method to call.
     * @param[in] signature The signature of the method to call.
     * @param[out] result A pointer to store the short return value.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethodByName_Short_A)(ani_env *env, ani_object object, const char *name,
                                                  const char *signature, ani_short *result, const ani_value *args);

    /**
     * @brief Calls a method by name on an object and retrieves a short return value (variadic arguments).
     *
     * This function calls the specified method by its name and signature on an object using a `va_list` and retrieves a
     * short result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] name The name of the method to call.
     * @param[in] signature The signature of the method to call.
     * @param[out] result A pointer to store the short return value.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethodByName_Short_V)(ani_env *env, ani_object object, const char *name,
                                                  const char *signature, ani_short *result, va_list args);

    /**
     * @brief Calls a method by name on an object and retrieves a integer return value.
     *
     * This function calls the specified method by its name and signature on an object using variadic arguments and
     * retrieves a integer result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] name The name of the method to call.
     * @param[in] signature The signature of the method to call.
     * @param[out] result A pointer to store the integer return value.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethodByName_Int)(ani_env *env, ani_object object, const char *name, const char *signature,
                                              ani_int *result, ...);

    /**
     * @brief Calls a method by name on an object and retrieves a integer return value (array-based).
     *
     * This function calls the specified method by its name and signature on an object using arguments provided in an
     * array and retrieves a integer result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] name The name of the method to call.
     * @param[in] signature The signature of the method to call.
     * @param[out] result A pointer to store the integer return value.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethodByName_Int_A)(ani_env *env, ani_object object, const char *name,
                                                const char *signature, ani_int *result, const ani_value *args);

    /**
     * @brief Calls a method by name on an object and retrieves a integer return value (variadic arguments).
     *
     * This function calls the specified method by its name and signature on an object using a `va_list` and retrieves a
     * integer result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] name The name of the method to call.
     * @param[in] signature The signature of the method to call.
     * @param[out] result A pointer to store the integer return value.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethodByName_Int_V)(ani_env *env, ani_object object, const char *name,
                                                const char *signature, ani_int *result, va_list args);

    /**
     * @brief Calls a method by name on an object and retrieves a long return value.
     *
     * This function calls the specified method by its name and signature on an object using variadic arguments and
     * retrieves a long result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] name The name of the method to call.
     * @param[in] signature The signature of the method to call.
     * @param[out] result A pointer to store the long return value.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethodByName_Long)(ani_env *env, ani_object object, const char *name, const char *signature,
                                               ani_long *result, ...);

    /**
     * @brief Calls a method by name on an object and retrieves a long return value (array-based).
     *
     * This function calls the specified method by its name and signature on an object using arguments provided in an
     * array and retrieves a long result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] name The name of the method to call.
     * @param[in] signature The signature of the method to call.
     * @param[out] result A pointer to store the long return value.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethodByName_Long_A)(ani_env *env, ani_object object, const char *name,
                                                 const char *signature, ani_long *result, const ani_value *args);

    /**
     * @brief Calls a method by name on an object and retrieves a long return value (variadic arguments).
     *
     * This function calls the specified method by its name and signature on an object using a `va_list` and retrieves a
     * long result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] name The name of the method to call.
     * @param[in] signature The signature of the method to call.
     * @param[out] result A pointer to store the long return value.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethodByName_Long_V)(ani_env *env, ani_object object, const char *name,
                                                 const char *signature, ani_long *result, va_list args);

    /**
     * @brief Calls a method by name on an object and retrieves a float return value.
     *
     * This function calls the specified method by its name and signature on an object using variadic arguments and
     * retrieves a float result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] name The name of the method to call.
     * @param[in] signature The signature of the method to call.
     * @param[out] result A pointer to store the float return value.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethodByName_Float)(ani_env *env, ani_object object, const char *name,
                                                const char *signature, ani_float *result, ...);

    /**
     * @brief Calls a method by name on an object and retrieves a float return value (array-based).
     *
     * This function calls the specified method by its name and signature on an object using arguments provided in an
     * array and retrieves a float result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] name The name of the method to call.
     * @param[in] signature The signature of the method to call.
     * @param[out] result A pointer to store the float return value.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethodByName_Float_A)(ani_env *env, ani_object object, const char *name,
                                                  const char *signature, ani_float *result, const ani_value *args);

    /**
     * @brief Calls a method by name on an object and retrieves a float return value (variadic arguments).
     *
     * This function calls the specified method by its name and signature on an object using a `va_list` and retrieves a
     * float result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] name The name of the method to call.
     * @param[in] signature The signature of the method to call.
     * @param[out] result A pointer to store the float return value.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethodByName_Float_V)(ani_env *env, ani_object object, const char *name,
                                                  const char *signature, ani_float *result, va_list args);

    /**
     * @brief Calls a method by name on an object and retrieves a double return value.
     *
     * This function calls the specified method by its name and signature on an object using variadic arguments and
     * retrieves a double result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] name The name of the method to call.
     * @param[in] signature The signature of the method to call.
     * @param[out] result A pointer to store the double return value.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethodByName_Double)(ani_env *env, ani_object object, const char *name,
                                                 const char *signature, ani_double *result, ...);

    /**
     * @brief Calls a method by name on an object and retrieves a double return value (array-based).
     *
     * This function calls the specified method by its name and signature on an object using arguments provided in an
     * array and retrieves a double result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] name The name of the method to call.
     * @param[in] signature The signature of the method to call.
     * @param[out] result A pointer to store the double return value.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethodByName_Double_A)(ani_env *env, ani_object object, const char *name,
                                                   const char *signature, ani_double *result, const ani_value *args);

    /**
     * @brief Calls a method by name on an object and retrieves a double return value (variadic arguments).
     *
     * This function calls the specified method by its name and signature on an object using a `va_list` and retrieves a
     * double result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] name The name of the method to call.
     * @param[in] signature The signature of the method to call.
     * @param[out] result A pointer to store the double return value.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethodByName_Double_V)(ani_env *env, ani_object object, const char *name,
                                                   const char *signature, ani_double *result, va_list args);

    /**
     * @brief Calls a method by name on an object and retrieves a reference return value.
     *
     * This function calls the specified method by its name and signature on an object using variadic arguments and
     * retrieves a reference result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] name The name of the method to call.
     * @param[in] signature The signature of the method to call.
     * @param[out] result A pointer to store the reference return value.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethodByName_Ref)(ani_env *env, ani_object object, const char *name, const char *signature,
                                              ani_ref *result, ...);

    /**
     * @brief Calls a method by name on an object and retrieves a reference return value (array-based).
     *
     * This function calls the specified method by its name and signature on an object using arguments provided in an
     * array and retrieves a reference result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] name The name of the method to call.
     * @param[in] signature The signature of the method to call.
     * @param[out] result A pointer to store the reference return value.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethodByName_Ref_A)(ani_env *env, ani_object object, const char *name,
                                                const char *signature, ani_ref *result, const ani_value *args);

    /**
     * @brief Calls a method by name on an object and retrieves a reference return value (variadic arguments).
     *
     * This function calls the specified method by its name and signature on an object using a `va_list` and retrieves a
     * reference result.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] name The name of the method to call.
     * @param[in] signature The signature of the method to call.
     * @param[out] result A pointer to store the reference return value.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethodByName_Ref_V)(ani_env *env, ani_object object, const char *name,
                                                const char *signature, ani_ref *result, va_list args);

    /**
     * @brief Calls a method by name on an object with no return value.
     *
     * This function calls the specified method by its name and signature on an object using variadic arguments. The
     * method does not return a value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] name The name of the method to call.
     * @param[in] signature The signature of the method to call.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethodByName_Void)(ani_env *env, ani_object object, const char *name, const char *signature,
                                               ...);

    /**
     * @brief Calls a method by name on an object with no return value (array-based).
     *
     * This function calls the specified method by its name and signature on an object using arguments provided in an
     * array. The method does not return a value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] name The name of the method to call.
     * @param[in] signature The signature of the method to call.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethodByName_Void_A)(ani_env *env, ani_object object, const char *name,
                                                 const char *signature, const ani_value *args);

    /**
     * @brief Calls a method by name on an object with no return value (variadic arguments).
     *
     * This function calls the specified method by its name and signature on an object using a `va_list`. The method
     * does not return a value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] object The object on which the method is to be called.
     * @param[in] name The name of the method to call.
     * @param[in] signature The signature of the method to call.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Object_CallMethodByName_Void_V)(ani_env *env, ani_object object, const char *name,
                                                 const char *signature, va_list args);

    /**
     * @brief Creates a new tuple value.
     *
     * This function creates a new value for the specified tuple using variadic arguments.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] tuple The tuple for which to create a new value.
     * @param[out] result A pointer to store the new tuple value.
     * @param[in] ... Variadic arguments to initialize the tuple value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Tuple_NewTupleValue)(ani_env *env, ani_tuple tuple, ani_tuple_value *result, ...);

    /**
     * @brief Creates a new tuple value (array-based).
     *
     * This function creates a new value for the specified tuple using arguments provided in an array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] tuple The tuple for which to create a new value.
     * @param[out] result A pointer to store the new tuple value.
     * @param[in] args An array of arguments to initialize the tuple value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Tuple_NewTupleValue_A)(ani_env *env, ani_tuple tuple, ani_tuple_value *result, const ani_value *args);

    /**
     * @brief Creates a new tuple value (variadic arguments).
     *
     * This function creates a new value for the specified tuple using a `va_list`.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] tuple The tuple for which to create a new value.
     * @param[out] result A pointer to store the new tuple value.
     * @param[in] args A `va_list` of arguments to initialize the tuple value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Tuple_NewTupleValue_V)(ani_env *env, ani_tuple tuple, ani_tuple_value *result, va_list args);

    /**
     * @brief Retrieves the number of items in a tuple.
     *
     * This function retrieves the total number of items in the specified tuple.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] tuple The tuple whose number of items is to be retrieved.
     * @param[out] result A pointer to store the number of items.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Tuple_GetNumberOfItems)(ani_env *env, ani_tuple tuple, ani_size *result);

    /**
     * @brief Retrieves the kind of an item in a tuple.
     *
     * This function retrieves the kind of the item at the specified index in the tuple.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] tuple The tuple containing the item.
     * @param[in] index The index of the item.
     * @param[out] result A pointer to store the kind of the item.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Tuple_GetItemKind)(ani_env *env, ani_tuple tuple, ani_size index, ani_kind *result);

    /**
     * @brief Retrieves the type of an item in a tuple.
     *
     * This function retrieves the type of the item at the specified index in the tuple.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] tuple The tuple containing the item.
     * @param[in] index The index of the item.
     * @param[out] result A pointer to store the type of the item.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Tuple_GetItemType)(ani_env *env, ani_tuple tuple, ani_size index, ani_type *result);

    /**
     * @brief Retrieves the tuple associated with a tuple value.
     *
     * This function retrieves the tuple that corresponds to the specified tuple value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] value The tuple value to query.
     * @param[out] result A pointer to store the associated tuple.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*TupleValue_GetTuple)(ani_env *env, ani_tuple_value value, ani_tuple *result);

    /**
     * @brief Retrieves a boolean item from a tuple value.
     *
     * This function retrieves the boolean value of the item at the specified index in the tuple value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] tuple_value The tuple value containing the item.
     * @param[in] index The index of the item.
     * @param[out] result A pointer to store the boolean value of the item.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*TupleValue_GetItem_Boolean)(ani_env *env, ani_tuple_value tuple_value, ani_size index,
                                             ani_boolean *result);

    /**
     * @brief Retrieves a char item from a tuple value.
     *
     * This function retrieves the char value of the item at the specified index in the tuple value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] tuple_value The tuple value containing the item.
     * @param[in] index The index of the item.
     * @param[out] result A pointer to store the char value of the item.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*TupleValue_GetItem_Char)(ani_env *env, ani_tuple_value tuple_value, ani_size index, ani_char *result);

    /**
     * @brief Retrieves a byte item from a tuple value.
     *
     * This function retrieves the byte value of the item at the specified index in the tuple value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] tuple_value The tuple value containing the item.
     * @param[in] index The index of the item.
     * @param[out] result A pointer to store the byte value of the item.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*TupleValue_GetItem_Byte)(ani_env *env, ani_tuple_value tuple_value, ani_size index, ani_byte *result);

    /**
     * @brief Retrieves a short item from a tuple value.
     *
     * This function retrieves the short value of the item at the specified index in the tuple value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] tuple_value The tuple value containing the item.
     * @param[in] index The index of the item.
     * @param[out] result A pointer to store the short value of the item.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*TupleValue_GetItem_Short)(ani_env *env, ani_tuple_value tuple_value, ani_size index,
                                           ani_short *result);

    /**
     * @brief Retrieves a integer item from a tuple value.
     *
     * This function retrieves the integer value of the item at the specified index in the tuple value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] tuple_value The tuple value containing the item.
     * @param[in] index The index of the item.
     * @param[out] result A pointer to store the integer value of the item.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*TupleValue_GetItem_Int)(ani_env *env, ani_tuple_value tuple_value, ani_size index, ani_int *result);

    /**
     * @brief Retrieves a long item from a tuple value.
     *
     * This function retrieves the long value of the item at the specified index in the tuple value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] tuple_value The tuple value containing the item.
     * @param[in] index The index of the item.
     * @param[out] result A pointer to store the long value of the item.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*TupleValue_GetItem_Long)(ani_env *env, ani_tuple_value tuple_value, ani_size index, ani_long *result);

    /**
     * @brief Retrieves a float item from a tuple value.
     *
     * This function retrieves the float value of the item at the specified index in the tuple value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] tuple_value The tuple value containing the item.
     * @param[in] index The index of the item.
     * @param[out] result A pointer to store the float value of the item.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*TupleValue_GetItem_Float)(ani_env *env, ani_tuple_value tuple_value, ani_size index,
                                           ani_float *result);

    /**
     * @brief Retrieves a double item from a tuple value.
     *
     * This function retrieves the double value of the item at the specified index in the tuple value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] tuple_value The tuple value containing the item.
     * @param[in] index The index of the item.
     * @param[out] result A pointer to store the double value of the item.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*TupleValue_GetItem_Double)(ani_env *env, ani_tuple_value tuple_value, ani_size index,
                                            ani_double *result);

    /**
     * @brief Retrieves a reference item from a tuple value.
     *
     * This function retrieves the reference value of the item at the specified index in the tuple value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] tuple_value The tuple value containing the item.
     * @param[in] index The index of the item.
     * @param[out] result A pointer to store the reference value of the item.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*TupleValue_GetItem_Ref)(ani_env *env, ani_tuple_value tuple_value, ani_size index, ani_ref *result);

    /**
     * @brief Sets a boolean value to an item in a tuple value.
     *
     * This function assigns a boolean value to the item at the specified index in the tuple value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] tuple_value The tuple value containing the item.
     * @param[in] index The index of the item.
     * @param[in] value The boolean value to assign to the item.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*TupleValue_SetItem_Boolean)(ani_env *env, ani_tuple_value tuple_value, ani_size index,
                                             ani_boolean value);

    /**
     * @brief Sets a char value to an item in a tuple value.
     *
     * This function assigns a char value to the item at the specified index in the tuple value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] tuple_value The tuple value containing the item.
     * @param[in] index The index of the item.
     * @param[in] value The char value to assign to the item.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*TupleValue_SetItem_Char)(ani_env *env, ani_tuple_value tuple_value, ani_size index, ani_char value);

    /**
     * @brief Sets a byte value to an item in a tuple value.
     *
     * This function assigns a byte value to the item at the specified index in the tuple value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] tuple_value The tuple value containing the item.
     * @param[in] index The index of the item.
     * @param[in] value The byte value to assign to the item.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*TupleValue_SetItem_Byte)(ani_env *env, ani_tuple_value tuple_value, ani_size index, ani_byte value);

    /**
     * @brief Sets a short value to an item in a tuple value.
     *
     * This function assigns a short value to the item at the specified index in the tuple value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] tuple_value The tuple value containing the item.
     * @param[in] index The index of the item.
     * @param[in] value The short value to assign to the item.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*TupleValue_SetItem_Short)(ani_env *env, ani_tuple_value tuple_value, ani_size index, ani_short value);

    /**
     * @brief Sets a integer value to an item in a tuple value.
     *
     * This function assigns a integer value to the item at the specified index in the tuple value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] tuple_value The tuple value containing the item.
     * @param[in] index The index of the item.
     * @param[in] value The integer value to assign to the item.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*TupleValue_SetItem_Int)(ani_env *env, ani_tuple_value tuple_value, ani_size index, ani_int value);

    /**
     * @brief Sets a long value to an item in a tuple value.
     *
     * This function assigns a long value to the item at the specified index in the tuple value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] tuple_value The tuple value containing the item.
     * @param[in] index The index of the item.
     * @param[in] value The long value to assign to the item.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*TupleValue_SetItem_Long)(ani_env *env, ani_tuple_value tuple_value, ani_size index, ani_long value);

    /**
     * @brief Sets a float value to an item in a tuple value.
     *
     * This function assigns a float value to the item at the specified index in the tuple value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] tuple_value The tuple value containing the item.
     * @param[in] index The index of the item.
     * @param[in] value The float value to assign to the item.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*TupleValue_SetItem_Float)(ani_env *env, ani_tuple_value tuple_value, ani_size index, ani_float value);

    /**
     * @brief Sets a double value to an item in a tuple value.
     *
     * This function assigns a double value to the item at the specified index in the tuple value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] tuple_value The tuple value containing the item.
     * @param[in] index The index of the item.
     * @param[in] value The double value to assign to the item.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*TupleValue_SetItem_Double)(ani_env *env, ani_tuple_value tuple_value, ani_size index,
                                            ani_double value);

    /**
     * @brief Sets a reference value to an item in a tuple value.
     *
     * This function assigns a reference value to the item at the specified index in the tuple value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] tuple_value The tuple value containing the item.
     * @param[in] index The index of the item.
     * @param[in] value The reference value to assign to the item.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*TupleValue_SetItem_Ref)(ani_env *env, ani_tuple_value tuple_value, ani_size index, ani_ref value);

    /**
     * @brief Creates a global reference.
     *
     * This function creates a global reference from a local reference.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] ref The local reference to convert to a global reference.
     * @param[out] result A pointer to store the created global reference.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*GlobalReference_Create)(ani_env *env, ani_ref ref, ani_gref *result);

    /**
     * @brief Deletes a global reference.
     *
     * This function deletes the specified global reference, releasing all associated resources.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] gref The global reference to delete.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*GlobalReference_Delete)(ani_env *env, ani_gref gref);

    /**
     * @brief Creates a weak reference.
     *
     * This function creates a weak reference from a local reference.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] ref The local reference to convert to a weak reference.
     * @param[out] result A pointer to store the created weak reference.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*WeakReference_Create)(ani_env *env, ani_ref ref, ani_wref *result);

    /**
     * @brief Deletes a weak reference.
     *
     * This function deletes the specified weak reference, releasing all associated resources.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] wref The weak reference to delete.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*WeakReference_Delete)(ani_env *env, ani_wref wref);

    /**
     * @brief Retrieves the local reference associated with a weak reference.
     *
     * This function retrieves the local reference that corresponds to the specified weak reference.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] wref The weak reference to query.
     * @param[out] result A pointer to store the retrieved local reference.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*WeakReference_GetReference)(ani_env *env, ani_wref wref, ani_ref *result);

    /**
     * @brief Creates a new array buffer.
     *
     * This function creates a new array buffer with the specified length and returns a pointer to the allocated data.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] length The length of the array buffer in bytes.
     * @param[out] data_result A pointer to store the allocated data of the array buffer.
     * @param[out] arraybuffer_result A pointer to store the created array buffer object.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*CreateArrayBuffer)(ani_env *env, size_t length, void **data_result,
                                    ani_arraybuffer *arraybuffer_result);

    /**
     * @brief Creates a new array buffer using external data.
     *
     * This function creates an array buffer that uses external data. The provided finalizer will be called when the
     * array buffer is no longer needed.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] external_data A pointer to the external data to be used by the array buffer.
     * @param[in] length The length of the external data in bytes.
     * @param[in] finalizer A callback function to be called when the array buffer is finalized.
     * @param[in] hint A user-defined hint to be passed to the finalizer.
     * @param[out] result A pointer to store the created array buffer object.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*CreateArrayBufferExternal)(ani_env *env, void *external_data, size_t length, ani_finalizer finalizer,
                                            void *hint, ani_arraybuffer *result);

    /**
     * @brief Retrieves information about an array buffer.
     *
     * This function retrieves the data pointer and length of the specified array buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] arraybuffer The array buffer to query.
     * @param[out] data_result A pointer to store the data of the array buffer.
     * @param[out] length_result A pointer to store the length of the array buffer in bytes.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*ArrayBuffer_GetInfo)(ani_env *env, ani_arraybuffer arraybuffer, void **data_result,
                                      size_t *length_result);

    /**
     * @brief Converts an object to a method.
     *
     * This function extracts the method information from a given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] method The object representing the method.
     * @param[out] result A pointer to store the extracted method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Reflection_FromMethod)(ani_env *env, ani_object method, ani_method *result);

    /**
     * @brief Converts a method to an object.
     *
     * This function creates an object representing the specified method.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the method.
     * @param[in] method The method to convert.
     * @param[out] result A pointer to store the created object.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Reflection_ToMethod)(ani_env *env, ani_class cls, ani_method method, ani_object *result);

    /**
     * @brief Converts an object to a field.
     *
     * This function extracts the field information from a given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] field The object representing the field.
     * @param[out] result A pointer to store the extracted field.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Reflection_FromField)(ani_env *env, ani_object field, ani_field *result);

    /**
     * @brief Converts a field to an object.
     *
     * This function creates an object representing the specified field.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the field.
     * @param[in] field The field to convert.
     * @param[out] result A pointer to store the created object.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Reflection_ToField)(ani_env *env, ani_class cls, ani_field field, ani_object *result);

    /**
     * @brief Converts an object to a static method.
     *
     * This function extracts the static method information from a given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] method The object representing the static method.
     * @param[out] result A pointer to store the extracted static method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Reflection_FromStaticMethod)(ani_env *env, ani_object method, ani_static_method *result);

    /**
     * @brief Converts a static method to an object.
     *
     * This function creates an object representing the specified static method.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] method The static method to convert.
     * @param[out] result A pointer to store the created object.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Reflection_ToStaticMethod)(ani_env *env, ani_class cls, ani_static_method method, ani_object *result);

    /**
     * @brief Converts an object to a static field.
     *
     * This function extracts the static field information from a given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] field The object representing the static field.
     * @param[out] result A pointer to store the extracted static field.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Reflection_FromStaticField)(ani_env *env, ani_object field, ani_static_field *result);

    /**
     * @brief Converts a static field to an object.
     *
     * This function creates an object representing the specified static field.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static field.
     * @param[in] field The static field to convert.
     * @param[out] result A pointer to store the created object.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Reflection_ToStaticField)(ani_env *env, ani_class cls, ani_static_field field, ani_object *result);

    /**
     * @brief Converts an object to a function.
     *
     * This function extracts the function information from a given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] function The object representing the function.
     * @param[out] result A pointer to store the extracted function.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Reflection_FromFunction)(ani_env *env, ani_object function, ani_function *result);

    /**
     * @brief Converts a function to an object.
     *
     * This function creates an object representing the specified function.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] function The function to convert.
     * @param[out] result A pointer to store the created object.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Reflection_ToFunction)(ani_env *env, ani_function function, ani_object *result);

    /**
     * @brief Converts an object to a variable.
     *
     * This function extracts the variable information from a given object.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] variable The object representing the variable.
     * @param[out] result A pointer to store the extracted variable.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Reflection_FromVariable)(ani_env *env, ani_object variable, ani_variable *result);

    /**
     * @brief Converts a variable to an object.
     *
     * This function creates an object representing the specified variable.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] variable The variable to convert.
     * @param[out] result A pointer to store the created object.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Reflection_ToVariable)(ani_env *env, ani_variable variable, ani_object *result);

    /**
     * @brief Registers a new coroutine-local storage slot.
     *
     * This function registers a new coroutine-local storage (CLS) slot with an optional initial data, finalizer, and
     * hint.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] initial_data A pointer to the initial data to associate with the slot. Can be null.
     * @param[in] finalizer A callback function to finalize and clean up the data when it is no longer needed.
     * @param[in] hint A user-defined pointer that is passed to the finalizer. Can be null.
     * @param[out] result A pointer to store the created CLS slot.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*CLS_Register)(ani_env *env, void *initial_data, ani_finalizer finalizer, void *hint,
                               ani_cls_slot *result);

    /**
     * @brief Unregisters a coroutine-local storage slot.
     *
     * This function unregisters a previously registered CLS slot, releasing its resources.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] slot The CLS slot to unregister.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*CLS_Unregister)(ani_env *env, ani_cls_slot slot);

    /**
     * @brief Sets data for a CLS slot.
     *
     * This function associates the specified data with the given CLS slot.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] slot The CLS slot to set data for.
     * @param[in] data A pointer to the data to associate with the slot. Can be null.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*CLS_SetData)(ani_env *env, ani_cls_slot slot, void *data);

    /**
     * @brief Retrieves data from a CLS slot.
     *
     * This function retrieves the data associated with the given CLS slot.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] slot The CLS slot to retrieve data from.
     * @param[out] result A pointer to store the retrieved data. Can be null if no data is associated.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*CLS_GetData)(ani_env *env, ani_cls_slot slot, void **result);

    /**
     * @brief Launches a coroutine using a functional object.
     *
     * This function starts a coroutine that executes the specified functional object with the given arguments.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] fn The functional object to execute.
     * @param[in] argc The number of arguments to pass to the functional object.
     * @param[in] argv An array of arguments to pass to the functional object.
     * @param[out] result A pointer to store the promise representing the coroutine's result.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Coroutine_LaunchFunctionalObject)(ani_env *env, ani_fn_object fn, ani_size argc, ani_ref *argv,
                                                   ani_promise *result);

    /**
     * @brief Launches a coroutine using a function with variadic arguments.
     *
     * This function starts a coroutine that executes the specified function with the given arguments.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] function The function to execute.
     * @param[out] result A pointer to store the promise representing the coroutine's result.
     * @param[in] ... Variadic arguments to pass to the function.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Coroutine_LaunchFunction)(ani_env *env, ani_function function, ani_promise *result, ...);

    /**
     * @brief Launches a coroutine using a function with array-based arguments.
     *
     * This function starts a coroutine that executes the specified function using arguments provided in an array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] function The function to execute.
     * @param[out] result A pointer to store the promise representing the coroutine's result.
     * @param[in] args An array of arguments to pass to the function.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Coroutine_LaunchFunction_A)(ani_env *env, ani_function function, ani_promise *result,
                                             const ani_value *args);

    /**
     * @brief Launches a coroutine using a function with variadic arguments in a `va_list`.
     *
     * This function starts a coroutine that executes the specified function using arguments provided in a `va_list`.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] function The function to execute.
     * @param[out] result A pointer to store the promise representing the coroutine's result.
     * @param[in] args A `va_list` of arguments to pass to the function.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Coroutine_LaunchFunction_V)(ani_env *env, ani_function function, ani_promise *result, va_list args);

    /**
     * @brief Launches a coroutine using an object method with variadic arguments.
     *
     * This function starts a coroutine that executes the specified method on the given object with the provided
     * arguments.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] self The object on which the method is to be executed.
     * @param[in] function The method to execute.
     * @param[out] result A pointer to store the promise representing the coroutine's result.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Coroutine_LaunchMethod)(ani_env *env, ani_object self, ani_function function, ani_promise *result,
                                         ...);

    /**
     * @brief Launches a coroutine using an object method with array-based arguments.
     *
     * This function starts a coroutine that executes the specified method on the given object using arguments provided
     * in an array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] self The object on which the method is to be executed.
     * @param[in] function The method to execute.
     * @param[out] result A pointer to store the promise representing the coroutine's result.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Coroutine_LaunchMethod_A)(ani_env *env, ani_object self, ani_function function, ani_promise *result,
                                           const ani_value *args);

    /**
     * @brief Launches a coroutine using an object method with variadic arguments in a `va_list`.
     *
     * This function starts a coroutine that executes the specified method on the given object using arguments provided
     * in a `va_list`.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] self The object on which the method is to be executed.
     * @param[in] function The method to execute.
     * @param[out] result A pointer to store the promise representing the coroutine's result.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Coroutine_LaunchMethod_V)(ani_env *env, ani_object self, ani_function function, ani_promise *result,
                                           va_list args);

    /**
     * @brief Launches a coroutine using a static method with variadic arguments.
     *
     * This function starts a coroutine that executes the specified static method on the given class with the provided
     * arguments.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class on which the static method is to be executed.
     * @param[in] function The static method to execute.
     * @param[out] result A pointer to store the promise representing the coroutine's result.
     * @param[in] ... Variadic arguments to pass to the static method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Coroutine_LaunchStaticMethod)(ani_env *env, ani_class cls, ani_function function, ani_promise *result,
                                               ...);

    /**
     * @brief Launches a coroutine using a static method with array-based arguments.
     *
     * This function starts a coroutine that executes the specified static method on the given class using arguments
     * provided in an array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class on which the static method is to be executed.
     * @param[in] function The static method to execute.
     * @param[out] result A pointer to store the promise representing the coroutine's result.
     * @param[in] args An array of arguments to pass to the static method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Coroutine_LaunchStaticMethod_A)(ani_env *env, ani_class cls, ani_function function,
                                                 ani_promise *result, const ani_value *args);

    /**
     * @brief Launches a coroutine using a static method with variadic arguments in a `va_list`.
     *
     * This function starts a coroutine that executes the specified static method on the given class using arguments
     * provided in a `va_list`.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class on which the static method is to be executed.
     * @param[in] function The static method to execute.
     * @param[out] result A pointer to store the promise representing the coroutine's result.
     * @param[in] args A `va_list` of arguments to pass to the static method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Coroutine_LaunchStaticMethod_V)(ani_env *env, ani_class cls, ani_function function,
                                                 ani_promise *result, va_list args);

    /**
     * @brief Awaits the completion of a promise and retrieves a boolean result.
     *
     * This function waits for the specified promise to complete and retrieves its result as a boolean value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] promise The promise to await.
     * @param[out] value A pointer to store the boolean result of the promise.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Coroutine_Await_Boolean)(ani_env *env, ani_promise promise, ani_boolean value);

    /**
     * @brief Awaits the completion of a promise and retrieves a char result.
     *
     * This function waits for the specified promise to complete and retrieves its result as a char value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] promise The promise to await.
     * @param[out] value A pointer to store the char result of the promise.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Coroutine_Await_Char)(ani_env *env, ani_promise promise, ani_char value);

    /**
     * @brief Awaits the completion of a promise and retrieves a byte result.
     *
     * This function waits for the specified promise to complete and retrieves its result as a byte value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] promise The promise to await.
     * @param[out] value A pointer to store the byte result of the promise.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Coroutine_Await_Byte)(ani_env *env, ani_promise promise, ani_byte value);

    /**
     * @brief Awaits the completion of a promise and retrieves a short result.
     *
     * This function waits for the specified promise to complete and retrieves its result as a short value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] promise The promise to await.
     * @param[out] value A pointer to store the short result of the promise.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Coroutine_Await_Short)(ani_env *env, ani_promise promise, ani_short value);

    /**
     * @brief Awaits the completion of a promise and retrieves a integer result.
     *
     * This function waits for the specified promise to complete and retrieves its result as a integer value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] promise The promise to await.
     * @param[out] value A pointer to store the integer result of the promise.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Coroutine_Await_Int)(ani_env *env, ani_promise promise, ani_int value);

    /**
     * @brief Awaits the completion of a promise and retrieves a long result.
     *
     * This function waits for the specified promise to complete and retrieves its result as a long value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] promise The promise to await.
     * @param[out] value A pointer to store the long result of the promise.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Coroutine_Await_Long)(ani_env *env, ani_promise promise, ani_long value);

    /**
     * @brief Awaits the completion of a promise and retrieves a float result.
     *
     * This function waits for the specified promise to complete and retrieves its result as a float value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] promise The promise to await.
     * @param[out] value A pointer to store the float result of the promise.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Coroutine_Await_Float)(ani_env *env, ani_promise promise, ani_float value);

    /**
     * @brief Awaits the completion of a promise and retrieves a double result.
     *
     * This function waits for the specified promise to complete and retrieves its result as a double value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] promise The promise to await.
     * @param[out] value A pointer to store the double result of the promise.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Coroutine_Await_Double)(ani_env *env, ani_promise promise, ani_double value);

    /**
     * @brief Awaits the completion of a promise and retrieves a reference result.
     *
     * This function waits for the specified promise to complete and retrieves its result as a reference.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] promise The promise to await.
     * @param[out] value A pointer to store the reference result of the promise.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Coroutine_Await_Ref)(ani_env *env, ani_promise promise, ani_ref value);
};

// C++ API
struct __ani_vm {
    const struct __ani_vm_api *c_api;

#ifdef __cplusplus
    ani_status DestroyVM()
    {
        return c_api->DestroyVM(this);
    }
    ani_status GetEnv(uint32_t version, ani_env **result)
    {
        return c_api->GetEnv(this, version, result);
    }
    ani_status AttachThread(void *params, ani_env **result)
    {
        return c_api->AttachThread(this, params, result);
    }
    ani_status DetachThread()
    {
        return c_api->DetachThread(this);
    }
#endif  // __cplusplus
};

struct __ani_env {
    const struct __ani_interaction_api *c_api;

#ifdef __cplusplus
    ani_status GetVersion(uint32_t *result)
    {
        return c_api->GetVersion(this, result);
    }
    ani_status GetVM(ani_vm **result)
    {
        return c_api->GetVM(this, result);
    }
    ani_status Reference_IsObject(ani_ref ref, ani_boolean *result)
    {
        return c_api->Reference_IsObject(this, ref, result);
    }
    ani_status Reference_IsFunctionalObject(ani_ref ref, ani_boolean *result)
    {
        return c_api->Reference_IsFunctionalObject(this, ref, result);
    }
    ani_status Reference_IsEnum(ani_ref ref, ani_boolean *result)
    {
        return c_api->Reference_IsEnum(this, ref, result);
    }
    ani_status Reference_IsTuple(ani_ref ref, ani_boolean *result)
    {
        return c_api->Reference_IsTuple(this, ref, result);
    }
    ani_status Reference_IsString(ani_ref ref, ani_boolean *result)
    {
        return c_api->Reference_IsString(this, ref, result);
    }
    ani_status Reference_IsStringLiteral(ani_ref ref, ani_boolean *result)
    {
        return c_api->Reference_IsStringLiteral(this, ref, result);
    }
    ani_status Reference_IsFixedArray(ani_ref ref, ani_boolean *result)
    {
        return c_api->Reference_IsFixedArray(this, ref, result);
    }
    ani_status Reference_IsFixedArray_Boolean(ani_ref ref, ani_boolean *result)
    {
        return c_api->Reference_IsFixedArray_Boolean(this, ref, result);
    }
    ani_status Reference_IsFixedArray_Char(ani_ref ref, ani_boolean *result)
    {
        return c_api->Reference_IsFixedArray_Char(this, ref, result);
    }
    ani_status Reference_IsFixedArray_Byte(ani_ref ref, ani_boolean *result)
    {
        return c_api->Reference_IsFixedArray_Byte(this, ref, result);
    }
    ani_status Reference_IsFixedArray_Short(ani_ref ref, ani_boolean *result)
    {
        return c_api->Reference_IsFixedArray_Short(this, ref, result);
    }
    ani_status Reference_IsFixedArray_Int(ani_ref ref, ani_boolean *result)
    {
        return c_api->Reference_IsFixedArray_Int(this, ref, result);
    }
    ani_status Reference_IsFixedArray_Long(ani_ref ref, ani_boolean *result)
    {
        return c_api->Reference_IsFixedArray_Long(this, ref, result);
    }
    ani_status Reference_IsFixedArray_Float(ani_ref ref, ani_boolean *result)
    {
        return c_api->Reference_IsFixedArray_Float(this, ref, result);
    }
    ani_status Reference_IsFixedArray_Double(ani_ref ref, ani_boolean *result)
    {
        return c_api->Reference_IsFixedArray_Double(this, ref, result);
    }
    ani_status Reference_IsFixedArray_Ref(ani_ref ref, ani_boolean *result)
    {
        return c_api->Reference_IsFixedArray_Ref(this, ref, result);
    }
    ani_status Object_New(ani_class cls, ani_method method, ani_object *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Object_New_V(this, cls, method, result, args);
        va_end(args);
        return status;
    }
    ani_status Object_New_A(ani_class cls, ani_method method, ani_object *result, const ani_value *args)
    {
        return c_api->Object_New_A(this, cls, method, result, args);
    }
    ani_status Object_New_V(ani_class cls, ani_method method, ani_object *result, va_list args)
    {
        return c_api->Object_New_V(this, cls, method, result, args);
    }
    ani_status Object_GetType(ani_object object, ani_type *result)
    {
        return c_api->Object_GetType(this, object, result);
    }
    ani_status Object_InstanceOf(ani_object object, ani_type type, ani_boolean *result)
    {
        return c_api->Object_InstanceOf(this, object, type, result);
    }
    ani_status Object_IsSame(ani_object object1, ani_object object2, ani_boolean *result)
    {
        return c_api->Object_IsSame(this, object1, object2, result);
    }
    ani_status Type_GetSuperClass(ani_type type, ani_class *result)
    {
        return c_api->Type_GetSuperClass(this, type, result);
    }
    ani_status Type_IsAssignableFrom(ani_type from_type, ani_type to_type, ani_boolean *result)
    {
        return c_api->Type_IsAssignableFrom(this, from_type, to_type, result);
    }
    ani_status FindModule(const char *module_descriptor, ani_module *result)
    {
        return c_api->FindModule(this, module_descriptor, result);
    }
    ani_status FindNamespace(const char *namespace_descriptor, ani_namespace *result)
    {
        return c_api->FindNamespace(this, namespace_descriptor, result);
    }
    ani_status FindClass(const char *class_descriptor, ani_class *result)
    {
        return c_api->FindClass(this, class_descriptor, result);
    }
    ani_status FindEnum(const char *enum_descriptor, ani_enum *result)
    {
        return c_api->FindEnum(this, enum_descriptor, result);
    }
    ani_status FindTuple(const char *tuple_descriptor, ani_tuple *result)
    {
        return c_api->FindTuple(this, tuple_descriptor, result);
    }
    ani_status FindFunction(const char *function_descriptor, ani_function *result)
    {
        return c_api->FindFunction(this, function_descriptor, result);
    }
    ani_status FindVariable(const char *variable_descriptor, ani_variable *result)
    {
        return c_api->FindVariable(this, variable_descriptor, result);
    }
    ani_status Module_FindNamespace(ani_module module, const char *namespace_descriptor, ani_namespace *result)
    {
        return c_api->Module_FindNamespace(this, module, namespace_descriptor, result);
    }
    ani_status Module_FindClass(ani_module module, const char *class_descriptor, ani_class *result)
    {
        return c_api->Module_FindClass(this, module, class_descriptor, result);
    }
    ani_status Module_FindEnum(ani_module module, const char *enum_descriptor, ani_enum *result)
    {
        return c_api->Module_FindEnum(this, module, enum_descriptor, result);
    }
    ani_status Module_FindFunction(ani_module module, const char *name, const char *signature, ani_function *result)
    {
        return c_api->Module_FindFunction(this, module, name, signature, result);
    }
    ani_status Module_FindVariable(ani_module module, const char *variable_descriptor, ani_variable *result)
    {
        return c_api->Module_FindVariable(this, module, variable_descriptor, result);
    }
    ani_status Namespace_FindNamespace(ani_namespace ns, const char *namespace_descriptor, ani_namespace *result)
    {
        return c_api->Namespace_FindNamespace(this, ns, namespace_descriptor, result);
    }
    ani_status Namespace_FindClass(ani_namespace ns, const char *class_descriptor, ani_class *result)
    {
        return c_api->Namespace_FindClass(this, ns, class_descriptor, result);
    }
    ani_status Namespace_FindEnum(ani_namespace ns, const char *enum_descriptor, ani_enum *result)
    {
        return c_api->Namespace_FindEnum(this, ns, enum_descriptor, result);
    }
    ani_status Namespace_FindFunction(ani_namespace ns, const char *name, const char *signature, ani_function *result)
    {
        return c_api->Namespace_FindFunction(this, ns, name, signature, result);
    }
    ani_status Namespace_FindVariable(ani_namespace ns, const char *variable_descriptor, ani_variable *result)
    {
        return c_api->Namespace_FindVariable(this, ns, variable_descriptor, result);
    }
    ani_status Module_BindNativeFunctions(ani_module module, const ani_native_function *functions,
                                          ani_size nr_functions)
    {
        return c_api->Module_BindNativeFunctions(this, module, functions, nr_functions);
    }
    ani_status Namespace_BindNativeFunctions(ani_namespace ns, const ani_native_function *functions,
                                             ani_size nr_functions)
    {
        return c_api->Namespace_BindNativeFunctions(this, ns, functions, nr_functions);
    }
    ani_status Class_BindNativeMethods(ani_class cls, const ani_native_function *methods, ani_size nr_methods)
    {
        return c_api->Class_BindNativeMethods(this, cls, methods, nr_methods);
    }
    ani_status Reference_Delete(ani_ref ref)
    {
        return c_api->Reference_Delete(this, ref);
    }
    ani_status EnsureEnoughReferences(ani_size nr_refs)
    {
        return c_api->EnsureEnoughReferences(this, nr_refs);
    }
    ani_status CreateLocalScope(ani_size nr_refs)
    {
        return c_api->CreateLocalScope(this, nr_refs);
    }
    ani_status DestroyLocalScope()
    {
        return c_api->DestroyLocalScope(this);
    }
    ani_status CreateEscapeLocalScope(ani_size nr_refs)
    {
        return c_api->CreateEscapeLocalScope(this, nr_refs);
    }
    ani_status DestroyEscapeLocalScope(ani_ref ref, ani_ref *result)
    {
        return c_api->DestroyEscapeLocalScope(this, ref, result);
    }
    ani_status ThrowError(ani_error err)
    {
        return c_api->ThrowError(this, err);
    }
    ani_status ExistUnhandledError(ani_boolean *result)
    {
        return c_api->ExistUnhandledError(this, result);
    }
    ani_status GetUnhandledError(ani_error *result)
    {
        return c_api->GetUnhandledError(this, result);
    }
    ani_status ResetError()
    {
        return c_api->ResetError(this);
    }
    ani_status DescribeError()
    {
        return c_api->DescribeError(this);
    }
    ani_status Abort(const char *message)
    {
        return c_api->Abort(this, message);
    }
    ani_status GetNull(ani_ref *result)
    {
        return c_api->GetNull(this, result);
    }
    ani_status GetUndefined(ani_ref *result)
    {
        return c_api->GetUndefined(this, result);
    }
    ani_status Reference_IsNull(ani_ref ref, ani_boolean *result)
    {
        return c_api->Reference_IsNull(this, ref, result);
    }
    ani_status Reference_IsUndefined(ani_ref ref, ani_boolean *result)
    {
        return c_api->Reference_IsUndefined(this, ref, result);
    }
    ani_status Reference_IsNullishValue(ani_ref ref, ani_boolean *result)
    {
        return c_api->Reference_IsNullishValue(this, ref, result);
    }
    ani_status Reference_Equals(ani_ref ref0, ani_ref ref1, ani_boolean *result)
    {
        return c_api->Reference_Equals(this, ref0, ref1, result);
    }
    ani_status Reference_StrictEquals(ani_ref ref0, ani_ref ref1, ani_boolean *result)
    {
        return c_api->Reference_StrictEquals(this, ref0, ref1, result);
    }
    ani_status String_NewUTF16(const uint16_t *utf16_string, ani_size utf16_size, ani_string *result)
    {
        return c_api->String_NewUTF16(this, utf16_string, utf16_size, result);
    }
    ani_status String_GetUTF16Size(ani_string string, ani_size *result)
    {
        return c_api->String_GetUTF16Size(this, string, result);
    }
    ani_status String_GetUTF16(ani_string string, uint16_t *utf16_buffer, ani_size utf16_buffer_size, ani_size *result)
    {
        return c_api->String_GetUTF16(this, string, utf16_buffer, utf16_buffer_size, result);
    }
    ani_status String_GetUTF16SubString(ani_string string, ani_size substr_offset, ani_size substr_size,
                                        uint16_t *utf16_buffer, ani_size utf16_buffer_size, ani_size *result)
    {
        return c_api->String_GetUTF16SubString(this, string, substr_offset, substr_size, utf16_buffer,
                                               utf16_buffer_size, result);
    }
    ani_status String_NewUTF8(const char *utf8_string, ani_size utf8_size, ani_string *result)
    {
        return c_api->String_NewUTF8(this, utf8_string, utf8_size, result);
    }
    ani_status String_GetUTF8Size(ani_string string, ani_size *result)
    {
        return c_api->String_GetUTF8Size(this, string, result);
    }
    ani_status String_GetUTF8(ani_string string, char *utf8_buffer, ani_size utf8_buffer_size, ani_size *result)
    {
        return c_api->String_GetUTF8(this, string, utf8_buffer, utf8_buffer_size, result);
    }
    ani_status String_GetUTF8SubString(ani_string string, ani_size substr_offset, ani_size substr_size,
                                       char *utf8_buffer, ani_size utf8_buffer_size, ani_size *result)
    {
        return c_api->String_GetUTF8SubString(this, string, substr_offset, substr_size, utf8_buffer, utf8_buffer_size,
                                              result);
    }
    ani_status String_GetCritical(ani_string string, uint32_t *result_string_type, const void **result_data,
                                  ani_size *result_size)  // result_string_type - string type utf16/utf8, etc
    {
        return c_api->String_GetCritical(this, string, result_string_type, result_data, result_size);
    }
    ani_status String_ReleaseCritical(ani_string string, const void *data)
    {
        return c_api->String_ReleaseCritical(this, string, data);
    }
    ani_status StringLiteral_NewUTF16(const uint16_t *utf16_string, ani_size utf16_size, ani_stringliteral *result)
    {
        return c_api->StringLiteral_NewUTF16(this, utf16_string, utf16_size, result);
    }
    ani_status StringLiteral_GetUTF16Size(ani_stringliteral string, ani_size *result)
    {
        return c_api->StringLiteral_GetUTF16Size(this, string, result);
    }
    ani_status StringLiteral_GetUTF16(ani_stringliteral string, uint16_t *utf16_buffer, ani_size utf16_buffer_size,
                                      ani_size *result)
    {
        return c_api->StringLiteral_GetUTF16(this, string, utf16_buffer, utf16_buffer_size, result);
    }
    ani_status StringLiteral_GetUTF16SubString(ani_stringliteral string, ani_size substr_offset, ani_size substr_size,
                                               uint16_t *utf16_buffer, ani_size utf16_buffer_size, ani_size *result)
    {
        return c_api->StringLiteral_GetUTF16SubString(this, string, substr_offset, substr_size, utf16_buffer,
                                                      utf16_buffer_size, result);
    }
    ani_status StringLiteral_NewUTF8(const char *utf8_string, ani_size utf8_size, ani_stringliteral *result)
    {
        return c_api->StringLiteral_NewUTF8(this, utf8_string, utf8_size, result);
    }
    ani_status StringLiteral_GetUTF8Size(ani_stringliteral string, ani_size *result)
    {
        return c_api->StringLiteral_GetUTF8Size(this, string, result);
    }
    ani_status StringLiteral_GetUTF8(ani_stringliteral string, char *utf8_buffer, ani_size utf8_buffer_size,
                                     ani_size *result)
    {
        return c_api->StringLiteral_GetUTF8(this, string, utf8_buffer, utf8_buffer_size, result);
    }
    ani_status StringLiteral_GetUTF8SubString(ani_stringliteral string, ani_size substr_offset, ani_size substr_size,
                                              char *utf8_buffer, ani_size utf8_buffer_size, ani_size *result)
    {
        return c_api->StringLiteral_GetUTF8SubString(this, string, substr_offset, substr_size, utf8_buffer,
                                                     utf8_buffer_size, result);
    }
    ani_status StringLiteral_GetCritical(ani_stringliteral string, uint32_t *result_string_type,
                                         const void **result_data,
                                         ani_size *result_size)  // result_string_type - string type utf16/utf8, etc
    {
        return c_api->StringLiteral_GetCritical(this, string, result_string_type, result_data, result_size);
    }
    ani_status StringLiteral_ReleaseCritical(ani_stringliteral string, const void *data)
    {
        return c_api->StringLiteral_ReleaseCritical(this, string, data);
    }
    ani_status FixedArray_GetLength(ani_fixedarray array, ani_size *result)
    {
        return c_api->FixedArray_GetLength(this, array, result);
    }
    ani_status FixedArray_New_Boolean(ani_size length, ani_fixedarray_boolean *result)
    {
        return c_api->FixedArray_New_Boolean(this, length, result);
    }
    ani_status FixedArray_New_Char(ani_size length, ani_fixedarray_char *result)
    {
        return c_api->FixedArray_New_Char(this, length, result);
    }
    ani_status FixedArray_New_Byte(ani_size length, ani_fixedarray_byte *result)
    {
        return c_api->FixedArray_New_Byte(this, length, result);
    }
    ani_status FixedArray_New_Short(ani_size length, ani_fixedarray_short *result)
    {
        return c_api->FixedArray_New_Short(this, length, result);
    }
    ani_status FixedArray_New_Int(ani_size length, ani_fixedarray_int *result)
    {
        return c_api->FixedArray_New_Int(this, length, result);
    }
    ani_status FixedArray_New_Long(ani_size length, ani_fixedarray_long *result)
    {
        return c_api->FixedArray_New_Long(this, length, result);
    }
    ani_status FixedArray_New_Float(ani_size length, ani_fixedarray_float *result)
    {
        return c_api->FixedArray_New_Float(this, length, result);
    }
    ani_status FixedArray_New_Double(ani_size length, ani_fixedarray_double *result)
    {
        return c_api->FixedArray_New_Double(this, length, result);
    }
    ani_status FixedArray_GetRegion_Boolean(ani_fixedarray_boolean array, ani_size offset, ani_size length,
                                            ani_boolean *native_buffer)
    {
        return c_api->FixedArray_GetRegion_Boolean(this, array, offset, length, native_buffer);
    }
    ani_status FixedArray_GetRegion_Char(ani_fixedarray_char array, ani_size offset, ani_size length,
                                         ani_char *native_buffer)
    {
        return c_api->FixedArray_GetRegion_Char(this, array, offset, length, native_buffer);
    }
    ani_status FixedArray_GetRegion_Byte(ani_fixedarray_byte array, ani_size offset, ani_size length,
                                         ani_byte *native_buffer)
    {
        return c_api->FixedArray_GetRegion_Byte(this, array, offset, length, native_buffer);
    }
    ani_status FixedArray_GetRegion_Short(ani_fixedarray_short array, ani_size offset, ani_size length,
                                          ani_short *native_buffer)
    {
        return c_api->FixedArray_GetRegion_Short(this, array, offset, length, native_buffer);
    }
    ani_status FixedArray_GetRegion_Int(ani_fixedarray_int array, ani_size offset, ani_size length,
                                        ani_int *native_buffer)
    {
        return c_api->FixedArray_GetRegion_Int(this, array, offset, length, native_buffer);
    }
    ani_status FixedArray_GetRegion_Long(ani_fixedarray_long array, ani_size offset, ani_size length,
                                         ani_long *native_buffer)
    {
        return c_api->FixedArray_GetRegion_Long(this, array, offset, length, native_buffer);
    }
    ani_status FixedArray_GetRegion_Float(ani_fixedarray_float array, ani_size offset, ani_size length,
                                          ani_float *native_buffer)
    {
        return c_api->FixedArray_GetRegion_Float(this, array, offset, length, native_buffer);
    }
    ani_status FixedArray_GetRegion_Double(ani_fixedarray_double array, ani_size offset, ani_size length,
                                           ani_double *native_buffer)
    {
        return c_api->FixedArray_GetRegion_Double(this, array, offset, length, native_buffer);
    }
    ani_status FixedArray_SetRegion_Boolean(ani_fixedarray_boolean array, ani_size offset, ani_size length,
                                            const ani_boolean *native_buffer)
    {
        return c_api->FixedArray_SetRegion_Boolean(this, array, offset, length, native_buffer);
    }
    ani_status FixedArray_SetRegion_Char(ani_fixedarray_char array, ani_size offset, ani_size length,
                                         const ani_char *native_buffer)
    {
        return c_api->FixedArray_SetRegion_Char(this, array, offset, length, native_buffer);
    }
    ani_status FixedArray_SetRegion_Byte(ani_fixedarray_byte array, ani_size offset, ani_size length,
                                         const ani_byte *native_buffer)
    {
        return c_api->FixedArray_SetRegion_Byte(this, array, offset, length, native_buffer);
    }
    ani_status FixedArray_SetRegion_Short(ani_fixedarray_short array, ani_size offset, ani_size length,
                                          const ani_short *native_buffer)
    {
        return c_api->FixedArray_SetRegion_Short(this, array, offset, length, native_buffer);
    }
    ani_status FixedArray_SetRegion_Int(ani_fixedarray_int array, ani_size offset, ani_size length,
                                        const ani_int *native_buffer)
    {
        return c_api->FixedArray_SetRegion_Int(this, array, offset, length, native_buffer);
    }
    ani_status FixedArray_SetRegion_Long(ani_fixedarray_long array, ani_size offset, ani_size length,
                                         const ani_long *native_buffer)
    {
        return c_api->FixedArray_SetRegion_Long(this, array, offset, length, native_buffer);
    }
    ani_status FixedArray_SetRegion_Float(ani_fixedarray_float array, ani_size offset, ani_size length,
                                          const ani_float *native_buffer)
    {
        return c_api->FixedArray_SetRegion_Float(this, array, offset, length, native_buffer);
    }
    ani_status FixedArray_SetRegion_Double(ani_fixedarray_double array, ani_size offset, ani_size length,
                                           const ani_double *native_buffer)
    {
        return c_api->FixedArray_SetRegion_Double(this, array, offset, length, native_buffer);
    }
    ani_status FixedArray_Pin(ani_fixedarray primitive_array, void **result)
    {
        return c_api->FixedArray_Pin(this, primitive_array, result);
    }
    ani_status FixedArray_Unpin(ani_fixedarray primitive_array, void *data)
    {
        return c_api->FixedArray_Unpin(this, primitive_array, data);
    }
    ani_status FixedArray_New_Ref(ani_size length, ani_ref *initial_array, ani_fixedarray_ref *result)
    {
        return c_api->FixedArray_New_Ref(this, length, initial_array, result);
    }
    ani_status FixedArray_Set_Ref(ani_fixedarray_ref array, ani_size index, ani_ref ref)
    {
        return c_api->FixedArray_Set_Ref(this, array, index, ref);
    }
    ani_status FixedArray_Get_Ref(ani_fixedarray_ref array, ani_size index, ani_ref *result)
    {
        return c_api->FixedArray_Get_Ref(this, array, index, result);
    }
    ani_status Enum_GetEnumValueByName(ani_enum enm, const char *name, ani_enum_value *result)
    {
        return c_api->Enum_GetEnumValueByName(this, enm, name, result);
    }
    ani_status Enum_GetEnumValueByIndex(ani_enum enm, ani_size index, ani_enum_value *result)
    {
        return c_api->Enum_GetEnumValueByIndex(this, enm, index, result);
    }
    ani_status EnumValue_GetEnum(ani_enum_value enum_value, ani_enum *result)
    {
        return c_api->EnumValue_GetEnum(this, enum_value, result);
    }
    ani_status EnumValue_GetValue(ani_enum_value enum_value, ani_object *result)
    {
        return c_api->EnumValue_GetValue(this, enum_value, result);
    }
    ani_status EnumValue_GetName(ani_enum_value enum_value, ani_string *result)
    {
        return c_api->EnumValue_GetName(this, enum_value, result);
    }
    ani_status EnumValue_GetIndex(ani_enum_value enum_value, ani_size *result)
    {
        return c_api->EnumValue_GetIndex(this, enum_value, result);
    }
    ani_status FunctionalObject_Call(ani_fn_object fn, ani_size argc, ani_ref *argv, ani_ref *result)
    {
        return c_api->FunctionalObject_Call(this, fn, argc, argv, result);
    }
    ani_status Variable_SetValue_Boolean(ani_variable variable, ani_boolean value)
    {
        return c_api->Variable_SetValue_Boolean(this, variable, value);
    }
    ani_status Variable_SetValue_Char(ani_variable variable, ani_char value)
    {
        return c_api->Variable_SetValue_Char(this, variable, value);
    }
    ani_status Variable_SetValue_Byte(ani_variable variable, ani_byte value)
    {
        return c_api->Variable_SetValue_Byte(this, variable, value);
    }
    ani_status Variable_SetValue_Short(ani_variable variable, ani_short value)
    {
        return c_api->Variable_SetValue_Short(this, variable, value);
    }
    ani_status Variable_SetValue_Int(ani_variable variable, ani_int value)
    {
        return c_api->Variable_SetValue_Int(this, variable, value);
    }
    ani_status Variable_SetValue_Long(ani_variable variable, ani_long value)
    {
        return c_api->Variable_SetValue_Long(this, variable, value);
    }
    ani_status Variable_SetValue_Float(ani_variable variable, ani_float value)
    {
        return c_api->Variable_SetValue_Float(this, variable, value);
    }
    ani_status Variable_SetValue_Double(ani_variable variable, ani_double value)
    {
        return c_api->Variable_SetValue_Double(this, variable, value);
    }
    ani_status Variable_SetValue_Ref(ani_variable variable, ani_ref value)
    {
        return c_api->Variable_SetValue_Ref(this, variable, value);
    }
    ani_status Variable_GetValue_Boolean(ani_variable variable, ani_boolean *result)
    {
        return c_api->Variable_GetValue_Boolean(this, variable, result);
    }
    ani_status Variable_GetValue_Char(ani_variable variable, ani_char *result)
    {
        return c_api->Variable_GetValue_Char(this, variable, result);
    }
    ani_status Variable_GetValue_Byte(ani_variable variable, ani_byte *result)
    {
        return c_api->Variable_GetValue_Byte(this, variable, result);
    }
    ani_status Variable_GetValue_Short(ani_variable variable, ani_short *result)
    {
        return c_api->Variable_GetValue_Short(this, variable, result);
    }
    ani_status Variable_GetValue_Int(ani_variable variable, ani_int *result)
    {
        return c_api->Variable_GetValue_Int(this, variable, result);
    }
    ani_status Variable_GetValue_Long(ani_variable variable, ani_long *result)
    {
        return c_api->Variable_GetValue_Long(this, variable, result);
    }
    ani_status Variable_GetValue_Float(ani_variable variable, ani_float *result)
    {
        return c_api->Variable_GetValue_Float(this, variable, result);
    }
    ani_status Variable_GetValue_Double(ani_variable variable, ani_double *result)
    {
        return c_api->Variable_GetValue_Double(this, variable, result);
    }
    ani_status Variable_GetValue_Ref(ani_variable variable, ani_ref *result)
    {
        return c_api->Variable_GetValue_Ref(this, variable, result);
    }
    ani_status Function_Call_Boolean(ani_function fn, ani_boolean *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Function_Call_Boolean_V(this, fn, result, args);
        va_end(args);
        return status;
    }
    ani_status Function_Call_Boolean_A(ani_function fn, ani_boolean *result, const ani_value *args)
    {
        return c_api->Function_Call_Boolean_A(this, fn, result, args);
    }
    ani_status Function_Call_Boolean_V(ani_function fn, ani_boolean *result, va_list args)
    {
        return c_api->Function_Call_Boolean_V(this, fn, result, args);
    }
    ani_status Function_Call_Char(ani_function fn, ani_char *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Function_Call_Char_V(this, fn, result, args);
        va_end(args);
        return status;
    }
    ani_status Function_Call_Char_A(ani_function fn, ani_char *result, const ani_value *args)
    {
        return c_api->Function_Call_Char_A(this, fn, result, args);
    }
    ani_status Function_Call_Char_V(ani_function fn, ani_char *result, va_list args)
    {
        return c_api->Function_Call_Char_V(this, fn, result, args);
    }
    ani_status Function_Call_Byte(ani_function fn, ani_byte *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Function_Call_Byte_V(this, fn, result, args);
        va_end(args);
        return status;
    }
    ani_status Function_Call_Byte_A(ani_function fn, ani_byte *result, const ani_value *args)
    {
        return c_api->Function_Call_Byte_A(this, fn, result, args);
    }
    ani_status Function_Call_Byte_V(ani_function fn, ani_byte *result, va_list args)
    {
        return c_api->Function_Call_Byte_V(this, fn, result, args);
    }
    ani_status Function_Call_Short(ani_function fn, ani_short *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Function_Call_Short_V(this, fn, result, args);
        va_end(args);
        return status;
    }
    ani_status Function_Call_Short_A(ani_function fn, ani_short *result, const ani_value *args)
    {
        return c_api->Function_Call_Short_A(this, fn, result, args);
    }
    ani_status Function_Call_Short_V(ani_function fn, ani_short *result, va_list args)
    {
        return c_api->Function_Call_Short_V(this, fn, result, args);
    }
    ani_status Function_Call_Int(ani_function fn, ani_int *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Function_Call_Int_V(this, fn, result, args);
        va_end(args);
        return status;
    }
    ani_status Function_Call_Int_A(ani_function fn, ani_int *result, const ani_value *args)
    {
        return c_api->Function_Call_Int_A(this, fn, result, args);
    }
    ani_status Function_Call_Int_V(ani_function fn, ani_int *result, va_list args)
    {
        return c_api->Function_Call_Int_V(this, fn, result, args);
    }
    ani_status Function_Call_Long(ani_function fn, ani_long *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Function_Call_Long_V(this, fn, result, args);
        va_end(args);
        return status;
    }
    ani_status Function_Call_Long_A(ani_function fn, ani_long *result, const ani_value *args)
    {
        return c_api->Function_Call_Long_A(this, fn, result, args);
    }
    ani_status Function_Call_Long_V(ani_function fn, ani_long *result, va_list args)
    {
        return c_api->Function_Call_Long_V(this, fn, result, args);
    }
    ani_status Function_Call_Float(ani_function fn, ani_float *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Function_Call_Float_V(this, fn, result, args);
        va_end(args);
        return status;
    }
    ani_status Function_Call_Float_A(ani_function fn, ani_float *result, const ani_value *args)
    {
        return c_api->Function_Call_Float_A(this, fn, result, args);
    }
    ani_status Function_Call_Float_V(ani_function fn, ani_float *result, va_list args)
    {
        return c_api->Function_Call_Float_V(this, fn, result, args);
    }
    ani_status Function_Call_Double(ani_function fn, ani_double *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Function_Call_Double_V(this, fn, result, args);
        va_end(args);
        return status;
    }
    ani_status Function_Call_Double_A(ani_function fn, ani_double *result, const ani_value *args)
    {
        return c_api->Function_Call_Double_A(this, fn, result, args);
    }
    ani_status Function_Call_Double_V(ani_function fn, ani_double *result, va_list args)
    {
        return c_api->Function_Call_Double_V(this, fn, result, args);
    }
    ani_status Function_Call_Ref(ani_function fn, ani_ref *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Function_Call_Ref_V(this, fn, result, args);
        va_end(args);
        return status;
    }
    ani_status Function_Call_Ref_A(ani_function fn, ani_ref *result, const ani_value *args)
    {
        return c_api->Function_Call_Ref_A(this, fn, result, args);
    }
    ani_status Function_Call_Ref_V(ani_function fn, ani_ref *result, va_list args)
    {
        return c_api->Function_Call_Ref_V(this, fn, result, args);
    }
    ani_status Function_Call_Void(ani_function fn, ...)
    {
        va_list args;
        va_start(args, fn);
        ani_status status = c_api->Function_Call_Void_V(this, fn, args);
        va_end(args);
        return status;
    }
    ani_status Function_Call_Void_A(ani_function fn, const ani_value *args)
    {
        return c_api->Function_Call_Void_A(this, fn, args);
    }
    ani_status Function_Call_Void_V(ani_function fn, va_list args)
    {
        return c_api->Function_Call_Void_V(this, fn, args);
    }
    ani_status Class_GetPartial(ani_class cls, ani_class *result)
    {
        return c_api->Class_GetPartial(this, cls, result);
    }
    ani_status Class_GetRequired(ani_class cls, ani_class *result)
    {
        return c_api->Class_GetRequired(this, cls, result);
    }
    ani_status Class_GetField(ani_class cls, const char *name, ani_field *result)
    {
        return c_api->Class_GetField(this, cls, name, result);
    }
    ani_status Class_GetStaticField(ani_class cls, const char *name, ani_static_field *result)
    {
        return c_api->Class_GetStaticField(this, cls, name, result);
    }
    ani_status Class_GetMethod(ani_class cls, const char *name, const char *signature, ani_method *result)
    {
        return c_api->Class_GetMethod(this, cls, name, signature, result);
    }
    ani_status Class_GetStaticMethod(ani_class cls, const char *name, const char *signature, ani_static_method *result)
    {
        return c_api->Class_GetStaticMethod(this, cls, name, signature, result);
    }
    ani_status Class_GetProperty(ani_class cls, const char *name, ani_property *result)
    {
        return c_api->Class_GetProperty(this, cls, name, result);
    }
    ani_status Class_GetSetter(ani_class cls, const char *name, ani_method *result)
    {
        return c_api->Class_GetSetter(this, cls, name, result);
    }
    ani_status Class_GetGetter(ani_class cls, const char *name, ani_method *result)
    {
        return c_api->Class_GetGetter(this, cls, name, result);
    }
    ani_status Class_GetIndexableGetter(ani_class cls, const char *signature, ani_method *result)
    {
        return c_api->Class_GetIndexableGetter(this, cls, signature, result);
    }
    ani_status Class_GetIndexableSetter(ani_class cls, const char *signature, ani_method *result)
    {
        return c_api->Class_GetIndexableSetter(this, cls, signature, result);
    }
    ani_status Class_GetIterator(ani_class cls, ani_method *result)
    {
        return c_api->Class_GetIterator(this, cls, result);
    }
    ani_status Class_GetStaticField_Boolean(ani_class cls, ani_static_field field, ani_boolean *result)
    {
        return c_api->Class_GetStaticField_Boolean(this, cls, field, result);
    }
    ani_status Class_GetStaticField_Char(ani_class cls, ani_static_field field, ani_char *result)
    {
        return c_api->Class_GetStaticField_Char(this, cls, field, result);
    }
    ani_status Class_GetStaticField_Byte(ani_class cls, ani_static_field field, ani_byte *result)
    {
        return c_api->Class_GetStaticField_Byte(this, cls, field, result);
    }
    ani_status Class_GetStaticField_Short(ani_class cls, ani_static_field field, ani_short *result)
    {
        return c_api->Class_GetStaticField_Short(this, cls, field, result);
    }
    ani_status Class_GetStaticField_Int(ani_class cls, ani_static_field field, ani_int *result)
    {
        return c_api->Class_GetStaticField_Int(this, cls, field, result);
    }
    ani_status Class_GetStaticField_Long(ani_class cls, ani_static_field field, ani_long *result)
    {
        return c_api->Class_GetStaticField_Long(this, cls, field, result);
    }
    ani_status Class_GetStaticField_Float(ani_class cls, ani_static_field field, ani_float *result)
    {
        return c_api->Class_GetStaticField_Float(this, cls, field, result);
    }
    ani_status Class_GetStaticField_Double(ani_class cls, ani_static_field field, ani_double *result)
    {
        return c_api->Class_GetStaticField_Double(this, cls, field, result);
    }
    ani_status Class_GetStaticField_Ref(ani_class cls, ani_static_field field, ani_ref *result)
    {
        return c_api->Class_GetStaticField_Ref(this, cls, field, result);
    }
    ani_status Class_SetStaticField_Boolean(ani_class cls, ani_static_field field, ani_boolean value)
    {
        return c_api->Class_SetStaticField_Boolean(this, cls, field, value);
    }
    ani_status Class_SetStaticField_Char(ani_class cls, ani_static_field field, ani_char value)
    {
        return c_api->Class_SetStaticField_Char(this, cls, field, value);
    }
    ani_status Class_SetStaticField_Byte(ani_class cls, ani_static_field field, ani_byte value)
    {
        return c_api->Class_SetStaticField_Byte(this, cls, field, value);
    }
    ani_status Class_SetStaticField_Short(ani_class cls, ani_static_field field, ani_short value)
    {
        return c_api->Class_SetStaticField_Short(this, cls, field, value);
    }
    ani_status Class_SetStaticField_Int(ani_class cls, ani_static_field field, ani_int value)
    {
        return c_api->Class_SetStaticField_Int(this, cls, field, value);
    }
    ani_status Class_SetStaticField_Long(ani_class cls, ani_static_field field, ani_long value)
    {
        return c_api->Class_SetStaticField_Long(this, cls, field, value);
    }
    ani_status Class_SetStaticField_Float(ani_class cls, ani_static_field field, ani_float value)
    {
        return c_api->Class_SetStaticField_Float(this, cls, field, value);
    }
    ani_status Class_SetStaticField_Double(ani_class cls, ani_static_field field, ani_double value)
    {
        return c_api->Class_SetStaticField_Double(this, cls, field, value);
    }
    ani_status Class_SetStaticField_Ref(ani_class cls, ani_static_field field, ani_ref value)
    {
        return c_api->Class_SetStaticField_Ref(this, cls, field, value);
    }
    ani_status Class_GetStaticFieldByName_Boolean(ani_class cls, const char *name, ani_boolean *result)
    {
        return c_api->Class_GetStaticFieldByName_Boolean(this, cls, name, result);
    }
    ani_status Class_GetStaticFieldByName_Char(ani_class cls, const char *name, ani_char *result)
    {
        return c_api->Class_GetStaticFieldByName_Char(this, cls, name, result);
    }
    ani_status Class_GetStaticFieldByName_Byte(ani_class cls, const char *name, ani_byte *result)
    {
        return c_api->Class_GetStaticFieldByName_Byte(this, cls, name, result);
    }
    ani_status Class_GetStaticFieldByName_Short(ani_class cls, const char *name, ani_short *result)
    {
        return c_api->Class_GetStaticFieldByName_Short(this, cls, name, result);
    }
    ani_status Class_GetStaticFieldByName_Int(ani_class cls, const char *name, ani_int *result)
    {
        return c_api->Class_GetStaticFieldByName_Int(this, cls, name, result);
    }
    ani_status Class_GetStaticFieldByName_Long(ani_class cls, const char *name, ani_long *result)
    {
        return c_api->Class_GetStaticFieldByName_Long(this, cls, name, result);
    }
    ani_status Class_GetStaticFieldByName_Float(ani_class cls, const char *name, ani_float *result)
    {
        return c_api->Class_GetStaticFieldByName_Float(this, cls, name, result);
    }
    ani_status Class_GetStaticFieldByName_Double(ani_class cls, const char *name, ani_double *result)
    {
        return c_api->Class_GetStaticFieldByName_Double(this, cls, name, result);
    }
    ani_status Class_GetStaticFieldByName_Ref(ani_class cls, const char *name, ani_ref *result)
    {
        return c_api->Class_GetStaticFieldByName_Ref(this, cls, name, result);
    }
    ani_status Class_SetStaticFieldByName_Boolean(ani_class cls, const char *name, ani_boolean value)
    {
        return c_api->Class_SetStaticFieldByName_Boolean(this, cls, name, value);
    }
    ani_status Class_SetStaticFieldByName_Char(ani_class cls, const char *name, ani_char value)
    {
        return c_api->Class_SetStaticFieldByName_Char(this, cls, name, value);
    }
    ani_status Class_SetStaticFieldByName_Byte(ani_class cls, const char *name, ani_byte value)
    {
        return c_api->Class_SetStaticFieldByName_Byte(this, cls, name, value);
    }
    ani_status Class_SetStaticFieldByName_Short(ani_class cls, const char *name, ani_short value)
    {
        return c_api->Class_SetStaticFieldByName_Short(this, cls, name, value);
    }
    ani_status Class_SetStaticFieldByName_Int(ani_class cls, const char *name, ani_int value)
    {
        return c_api->Class_SetStaticFieldByName_Int(this, cls, name, value);
    }
    ani_status Class_SetStaticFieldByName_Long(ani_class cls, const char *name, ani_long value)
    {
        return c_api->Class_SetStaticFieldByName_Long(this, cls, name, value);
    }
    ani_status Class_SetStaticFieldByName_Float(ani_class cls, const char *name, ani_float value)
    {
        return c_api->Class_SetStaticFieldByName_Float(this, cls, name, value);
    }
    ani_status Class_SetStaticFieldByName_Double(ani_class cls, const char *name, ani_double value)
    {
        return c_api->Class_SetStaticFieldByName_Double(this, cls, name, value);
    }
    ani_status Class_SetStaticFieldByName_Ref(ani_class cls, const char *name, ani_ref value)
    {
        return c_api->Class_SetStaticFieldByName_Ref(this, cls, name, value);
    }
    ani_status Class_CallStaticMethod_Boolean(ani_class cls, ani_static_method method, ani_boolean *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Class_CallStaticMethod_Boolean_V(this, cls, method, result, args);
        va_end(args);
        return status;
    }
    ani_status Class_CallStaticMethod_Boolean_A(ani_class cls, ani_static_method method, ani_boolean *result,
                                                const ani_value *args)
    {
        return c_api->Class_CallStaticMethod_Boolean_A(this, cls, method, result, args);
    }
    ani_status Class_CallStaticMethod_Boolean_V(ani_class cls, ani_static_method method, ani_boolean *result,
                                                va_list args)
    {
        return c_api->Class_CallStaticMethod_Boolean_V(this, cls, method, result, args);
    }
    ani_status Class_CallStaticMethod_Char(ani_class cls, ani_static_method method, ani_char *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Class_CallStaticMethod_Char_V(this, cls, method, result, args);
        va_end(args);
        return status;
    }
    ani_status Class_CallStaticMethod_Char_A(ani_class cls, ani_static_method method, ani_char *result,
                                             const ani_value *args)
    {
        return c_api->Class_CallStaticMethod_Char_A(this, cls, method, result, args);
    }
    ani_status Class_CallStaticMethod_Char_V(ani_class cls, ani_static_method method, ani_char *result, va_list args)
    {
        return c_api->Class_CallStaticMethod_Char_V(this, cls, method, result, args);
    }
    ani_status Class_CallStaticMethod_Byte(ani_class cls, ani_static_method method, ani_byte *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Class_CallStaticMethod_Byte_V(this, cls, method, result, args);
        va_end(args);
        return status;
    }
    ani_status Class_CallStaticMethod_Byte_A(ani_class cls, ani_static_method method, ani_byte *result,
                                             const ani_value *args)
    {
        return c_api->Class_CallStaticMethod_Byte_A(this, cls, method, result, args);
    }
    ani_status Class_CallStaticMethod_Byte_V(ani_class cls, ani_static_method method, ani_byte *result, va_list args)
    {
        return c_api->Class_CallStaticMethod_Byte_V(this, cls, method, result, args);
    }
    ani_status Class_CallStaticMethod_Short(ani_class cls, ani_static_method method, ani_short *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Class_CallStaticMethod_Short_V(this, cls, method, result, args);
        va_end(args);
        return status;
    }
    ani_status Class_CallStaticMethod_Short_A(ani_class cls, ani_static_method method, ani_short *result,
                                              const ani_value *args)
    {
        return c_api->Class_CallStaticMethod_Short_A(this, cls, method, result, args);
    }
    ani_status Class_CallStaticMethod_Short_V(ani_class cls, ani_static_method method, ani_short *result, va_list args)
    {
        return c_api->Class_CallStaticMethod_Short_V(this, cls, method, result, args);
    }
    ani_status Class_CallStaticMethod_Int(ani_class cls, ani_static_method method, ani_int *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Class_CallStaticMethod_Int_V(this, cls, method, result, args);
        va_end(args);
        return status;
    }
    ani_status Class_CallStaticMethod_Int_A(ani_class cls, ani_static_method method, ani_int *result,
                                            const ani_value *args)
    {
        return c_api->Class_CallStaticMethod_Int_A(this, cls, method, result, args);
    }
    ani_status Class_CallStaticMethod_Int_V(ani_class cls, ani_static_method method, ani_int *result, va_list args)
    {
        return c_api->Class_CallStaticMethod_Int_V(this, cls, method, result, args);
    }
    ani_status Class_CallStaticMethod_Long(ani_class cls, ani_static_method method, ani_long *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Class_CallStaticMethod_Long_V(this, cls, method, result, args);
        va_end(args);
        return status;
    }
    ani_status Class_CallStaticMethod_Long_A(ani_class cls, ani_static_method method, ani_long *result,
                                             const ani_value *args)
    {
        return c_api->Class_CallStaticMethod_Long_A(this, cls, method, result, args);
    }
    ani_status Class_CallStaticMethod_Long_V(ani_class cls, ani_static_method method, ani_long *result, va_list args)
    {
        return c_api->Class_CallStaticMethod_Long_V(this, cls, method, result, args);
    }
    ani_status Class_CallStaticMethod_Float(ani_class cls, ani_static_method method, ani_float *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Class_CallStaticMethod_Float_V(this, cls, method, result, args);
        va_end(args);
        return status;
    }
    ani_status Class_CallStaticMethod_Float_A(ani_class cls, ani_static_method method, ani_float *result,
                                              const ani_value *args)
    {
        return c_api->Class_CallStaticMethod_Float_A(this, cls, method, result, args);
    }
    ani_status Class_CallStaticMethod_Float_V(ani_class cls, ani_static_method method, ani_float *result, va_list args)
    {
        return c_api->Class_CallStaticMethod_Float_V(this, cls, method, result, args);
    }
    ani_status Class_CallStaticMethod_Double(ani_class cls, ani_static_method method, ani_double *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Class_CallStaticMethod_Double_V(this, cls, method, result, args);
        va_end(args);
        return status;
    }
    ani_status Class_CallStaticMethod_Double_A(ani_class cls, ani_static_method method, ani_double *result,
                                               const ani_value *args)
    {
        return c_api->Class_CallStaticMethod_Double_A(this, cls, method, result, args);
    }
    ani_status Class_CallStaticMethod_Double_V(ani_class cls, ani_static_method method, ani_double *result,
                                               va_list args)
    {
        return c_api->Class_CallStaticMethod_Double_V(this, cls, method, result, args);
    }
    ani_status Class_CallStaticMethod_Ref(ani_class cls, ani_static_method method, ani_ref *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Class_CallStaticMethod_Ref_V(this, cls, method, result, args);
        va_end(args);
        return status;
    }
    ani_status Class_CallStaticMethod_Ref_A(ani_class cls, ani_static_method method, ani_ref *result,
                                            const ani_value *args)
    {
        return c_api->Class_CallStaticMethod_Ref_A(this, cls, method, result, args);
    }
    ani_status Class_CallStaticMethod_Ref_V(ani_class cls, ani_static_method method, ani_ref *result, va_list args)
    {
        return c_api->Class_CallStaticMethod_Ref_V(this, cls, method, result, args);
    }
    ani_status Class_CallStaticMethod_Void(ani_class cls, ani_static_method method, ...)
    {
        va_list args;
        va_start(args, method);
        ani_status status = c_api->Class_CallStaticMethod_Void_V(this, cls, method, args);
        va_end(args);
        return status;
    }
    ani_status Class_CallStaticMethod_Void_A(ani_class cls, ani_static_method method, const ani_value *args)
    {
        return c_api->Class_CallStaticMethod_Void_A(this, cls, method, args);
    }
    ani_status Class_CallStaticMethod_Void_V(ani_class cls, ani_static_method method, va_list args)
    {
        return c_api->Class_CallStaticMethod_Void_V(this, cls, method, args);
    }
    ani_status Class_CallStaticMethodByName_Boolean(ani_class cls, const char *name, ani_boolean *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Class_CallStaticMethodByName_Boolean_V(this, cls, name, result, args);
        va_end(args);
        return status;
    }
    ani_status Class_CallStaticMethodByName_Boolean_A(ani_class cls, const char *name, ani_boolean *result,
                                                      const ani_value *args)
    {
        return c_api->Class_CallStaticMethodByName_Boolean_A(this, cls, name, result, args);
    }
    ani_status Class_CallStaticMethodByName_Boolean_V(ani_class cls, const char *name, ani_boolean *result,
                                                      va_list args)
    {
        return c_api->Class_CallStaticMethodByName_Boolean_V(this, cls, name, result, args);
    }
    ani_status Class_CallStaticMethodByName_Char(ani_class cls, const char *name, ani_char *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Class_CallStaticMethodByName_Char_V(this, cls, name, result, args);
        va_end(args);
        return status;
    }
    ani_status Class_CallStaticMethodByName_Char_A(ani_class cls, const char *name, ani_char *result,
                                                   const ani_value *args)
    {
        return c_api->Class_CallStaticMethodByName_Char_A(this, cls, name, result, args);
    }
    ani_status Class_CallStaticMethodByName_Char_V(ani_class cls, const char *name, ani_char *result, va_list args)
    {
        return c_api->Class_CallStaticMethodByName_Char_V(this, cls, name, result, args);
    }
    ani_status Class_CallStaticMethodByName_Byte(ani_class cls, const char *name, ani_byte *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Class_CallStaticMethodByName_Byte_V(this, cls, name, result, args);
        va_end(args);
        return status;
    }
    ani_status Class_CallStaticMethodByName_Byte_A(ani_class cls, const char *name, ani_byte *result,
                                                   const ani_value *args)
    {
        return c_api->Class_CallStaticMethodByName_Byte_A(this, cls, name, result, args);
    }
    ani_status Class_CallStaticMethodByName_Byte_V(ani_class cls, const char *name, ani_byte *result, va_list args)
    {
        return c_api->Class_CallStaticMethodByName_Byte_V(this, cls, name, result, args);
    }
    ani_status Class_CallStaticMethodByName_Short(ani_class cls, const char *name, ani_short *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Class_CallStaticMethodByName_Short_V(this, cls, name, result, args);
        va_end(args);
        return status;
    }
    ani_status Class_CallStaticMethodByName_Short_A(ani_class cls, const char *name, ani_short *result,
                                                    const ani_value *args)
    {
        return c_api->Class_CallStaticMethodByName_Short_A(this, cls, name, result, args);
    }
    ani_status Class_CallStaticMethodByName_Short_V(ani_class cls, const char *name, ani_short *result, va_list args)
    {
        return c_api->Class_CallStaticMethodByName_Short_V(this, cls, name, result, args);
    }
    ani_status Class_CallStaticMethodByName_Int(ani_class cls, const char *name, ani_int *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Class_CallStaticMethodByName_Int_V(this, cls, name, result, args);
        va_end(args);
        return status;
    }
    ani_status Class_CallStaticMethodByName_Int_A(ani_class cls, const char *name, ani_int *result,
                                                  const ani_value *args)
    {
        return c_api->Class_CallStaticMethodByName_Int_A(this, cls, name, result, args);
    }
    ani_status Class_CallStaticMethodByName_Int_V(ani_class cls, const char *name, ani_int *result, va_list args)
    {
        return c_api->Class_CallStaticMethodByName_Int_V(this, cls, name, result, args);
    }
    ani_status Class_CallStaticMethodByName_Long(ani_class cls, const char *name, ani_long *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Class_CallStaticMethodByName_Long_V(this, cls, name, result, args);
        va_end(args);
        return status;
    }
    ani_status Class_CallStaticMethodByName_Long_A(ani_class cls, const char *name, ani_long *result,
                                                   const ani_value *args)
    {
        return c_api->Class_CallStaticMethodByName_Long_A(this, cls, name, result, args);
    }
    ani_status Class_CallStaticMethodByName_Long_V(ani_class cls, const char *name, ani_long *result, va_list args)
    {
        return c_api->Class_CallStaticMethodByName_Long_V(this, cls, name, result, args);
    }
    ani_status Class_CallStaticMethodByName_Float(ani_class cls, const char *name, ani_float *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Class_CallStaticMethodByName_Float_V(this, cls, name, result, args);
        va_end(args);
        return status;
    }
    ani_status Class_CallStaticMethodByName_Float_A(ani_class cls, const char *name, ani_float *result,
                                                    const ani_value *args)
    {
        return c_api->Class_CallStaticMethodByName_Float_A(this, cls, name, result, args);
    }
    ani_status Class_CallStaticMethodByName_Float_V(ani_class cls, const char *name, ani_float *result, va_list args)
    {
        return c_api->Class_CallStaticMethodByName_Float_V(this, cls, name, result, args);
    }
    ani_status Class_CallStaticMethodByName_Double(ani_class cls, const char *name, ani_double *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Class_CallStaticMethodByName_Double_V(this, cls, name, result, args);
        va_end(args);
        return status;
    }
    ani_status Class_CallStaticMethodByName_Double_A(ani_class cls, const char *name, ani_double *result,
                                                     const ani_value *args)
    {
        return c_api->Class_CallStaticMethodByName_Double_A(this, cls, name, result, args);
    }
    ani_status Class_CallStaticMethodByName_Double_V(ani_class cls, const char *name, ani_double *result, va_list args)
    {
        return c_api->Class_CallStaticMethodByName_Double_V(this, cls, name, result, args);
    }
    ani_status Class_CallStaticMethodByName_Ref(ani_class cls, const char *name, ani_ref *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Class_CallStaticMethodByName_Ref_V(this, cls, name, result, args);
        va_end(args);
        return status;
    }
    ani_status Class_CallStaticMethodByName_Ref_A(ani_class cls, const char *name, ani_ref *result,
                                                  const ani_value *args)
    {
        return c_api->Class_CallStaticMethodByName_Ref_A(this, cls, name, result, args);
    }
    ani_status Class_CallStaticMethodByName_Ref_V(ani_class cls, const char *name, ani_ref *result, va_list args)
    {
        return c_api->Class_CallStaticMethodByName_Ref_V(this, cls, name, result, args);
    }
    ani_status Class_CallStaticMethodByName_Void(ani_class cls, const char *name, ...)
    {
        va_list args;
        va_start(args, name);
        ani_status status = c_api->Class_CallStaticMethodByName_Void_V(this, cls, name, args);
        va_end(args);
        return status;
    }
    ani_status Class_CallStaticMethodByName_Void_A(ani_class cls, const char *name, const ani_value *args)
    {
        return c_api->Class_CallStaticMethodByName_Void_A(this, cls, name, args);
    }
    ani_status Class_CallStaticMethodByName_Void_V(ani_class cls, const char *name, va_list args)
    {
        return c_api->Class_CallStaticMethodByName_Void_V(this, cls, name, args);
    }
    ani_status Object_GetField_Boolean(ani_object object, ani_field field, ani_boolean *result)
    {
        return c_api->Object_GetField_Boolean(this, object, field, result);
    }
    ani_status Object_GetField_Char(ani_object object, ani_field field, ani_char *result)
    {
        return c_api->Object_GetField_Char(this, object, field, result);
    }
    ani_status Object_GetField_Byte(ani_object object, ani_field field, ani_byte *result)
    {
        return c_api->Object_GetField_Byte(this, object, field, result);
    }
    ani_status Object_GetField_Short(ani_object object, ani_field field, ani_short *result)
    {
        return c_api->Object_GetField_Short(this, object, field, result);
    }
    ani_status Object_GetField_Int(ani_object object, ani_field field, ani_int *result)
    {
        return c_api->Object_GetField_Int(this, object, field, result);
    }
    ani_status Object_GetField_Long(ani_object object, ani_field field, ani_long *result)
    {
        return c_api->Object_GetField_Long(this, object, field, result);
    }
    ani_status Object_GetField_Float(ani_object object, ani_field field, ani_float *result)
    {
        return c_api->Object_GetField_Float(this, object, field, result);
    }
    ani_status Object_GetField_Double(ani_object object, ani_field field, ani_double *result)
    {
        return c_api->Object_GetField_Double(this, object, field, result);
    }
    ani_status Object_GetField_Ref(ani_object object, ani_field field, ani_ref *result)
    {
        return c_api->Object_GetField_Ref(this, object, field, result);
    }
    ani_status Object_SetField_Boolean(ani_object object, ani_field field, ani_boolean value)
    {
        return c_api->Object_SetField_Boolean(this, object, field, value);
    }
    ani_status Object_SetField_Char(ani_object object, ani_field field, ani_char value)
    {
        return c_api->Object_SetField_Char(this, object, field, value);
    }
    ani_status Object_SetField_Byte(ani_object object, ani_field field, ani_byte value)
    {
        return c_api->Object_SetField_Byte(this, object, field, value);
    }
    ani_status Object_SetField_Short(ani_object object, ani_field field, ani_short value)
    {
        return c_api->Object_SetField_Short(this, object, field, value);
    }
    ani_status Object_SetField_Int(ani_object object, ani_field field, ani_int value)
    {
        return c_api->Object_SetField_Int(this, object, field, value);
    }
    ani_status Object_SetField_Long(ani_object object, ani_field field, ani_long value)
    {
        return c_api->Object_SetField_Long(this, object, field, value);
    }
    ani_status Object_SetField_Float(ani_object object, ani_field field, ani_float value)
    {
        return c_api->Object_SetField_Float(this, object, field, value);
    }
    ani_status Object_SetField_Double(ani_object object, ani_field field, ani_double value)
    {
        return c_api->Object_SetField_Double(this, object, field, value);
    }
    ani_status Object_SetField_Ref(ani_object object, ani_field field, ani_ref value)
    {
        return c_api->Object_SetField_Ref(this, object, field, value);
    }
    ani_status Object_GetFieldByName_Boolean(ani_object object, const char *name, ani_boolean *result)
    {
        return c_api->Object_GetFieldByName_Boolean(this, object, name, result);
    }
    ani_status Object_GetFieldByName_Char(ani_object object, const char *name, ani_char *result)
    {
        return c_api->Object_GetFieldByName_Char(this, object, name, result);
    }
    ani_status Object_GetFieldByName_Byte(ani_object object, const char *name, ani_byte *result)
    {
        return c_api->Object_GetFieldByName_Byte(this, object, name, result);
    }
    ani_status Object_GetFieldByName_Short(ani_object object, const char *name, ani_short *result)
    {
        return c_api->Object_GetFieldByName_Short(this, object, name, result);
    }
    ani_status Object_GetFieldByName_Int(ani_object object, const char *name, ani_int *result)
    {
        return c_api->Object_GetFieldByName_Int(this, object, name, result);
    }
    ani_status Object_GetFieldByName_Long(ani_object object, const char *name, ani_long *result)
    {
        return c_api->Object_GetFieldByName_Long(this, object, name, result);
    }
    ani_status Object_GetFieldByName_Float(ani_object object, const char *name, ani_float *result)
    {
        return c_api->Object_GetFieldByName_Float(this, object, name, result);
    }
    ani_status Object_GetFieldByName_Double(ani_object object, const char *name, ani_double *result)
    {
        return c_api->Object_GetFieldByName_Double(this, object, name, result);
    }
    ani_status Object_GetFieldByName_Ref(ani_object object, const char *name, ani_ref *result)
    {
        return c_api->Object_GetFieldByName_Ref(this, object, name, result);
    }
    ani_status Object_SetFieldByName_Boolean(ani_object object, const char *name, ani_boolean value)
    {
        return c_api->Object_SetFieldByName_Boolean(this, object, name, value);
    }
    ani_status Object_SetFieldByName_Char(ani_object object, const char *name, ani_char value)
    {
        return c_api->Object_SetFieldByName_Char(this, object, name, value);
    }
    ani_status Object_SetFieldByName_Byte(ani_object object, const char *name, ani_byte value)
    {
        return c_api->Object_SetFieldByName_Byte(this, object, name, value);
    }
    ani_status Object_SetFieldByName_Short(ani_object object, const char *name, ani_short value)
    {
        return c_api->Object_SetFieldByName_Short(this, object, name, value);
    }
    ani_status Object_SetFieldByName_Int(ani_object object, const char *name, ani_int value)
    {
        return c_api->Object_SetFieldByName_Int(this, object, name, value);
    }
    ani_status Object_SetFieldByName_Long(ani_object object, const char *name, ani_long value)
    {
        return c_api->Object_SetFieldByName_Long(this, object, name, value);
    }
    ani_status Object_SetFieldByName_Float(ani_object object, const char *name, ani_float value)
    {
        return c_api->Object_SetFieldByName_Float(this, object, name, value);
    }
    ani_status Object_SetFieldByName_Double(ani_object object, const char *name, ani_double value)
    {
        return c_api->Object_SetFieldByName_Double(this, object, name, value);
    }
    ani_status Object_SetFieldByName_Ref(ani_object object, const char *name, ani_ref value)
    {
        return c_api->Object_SetFieldByName_Ref(this, object, name, value);
    }
    ani_status Object_GetProperty_Boolean(ani_object object, ani_property property, ani_boolean *result)
    {
        return c_api->Object_GetProperty_Boolean(this, object, property, result);
    }
    ani_status Object_GetProperty_Char(ani_object object, ani_property property, ani_char *result)
    {
        return c_api->Object_GetProperty_Char(this, object, property, result);
    }
    ani_status Object_GetProperty_Byte(ani_object object, ani_property property, ani_byte *result)
    {
        return c_api->Object_GetProperty_Byte(this, object, property, result);
    }
    ani_status Object_GetProperty_Short(ani_object object, ani_property property, ani_short *result)
    {
        return c_api->Object_GetProperty_Short(this, object, property, result);
    }
    ani_status Object_GetProperty_Int(ani_object object, ani_property property, ani_int *result)
    {
        return c_api->Object_GetProperty_Int(this, object, property, result);
    }
    ani_status Object_GetProperty_Long(ani_object object, ani_property property, ani_long *result)
    {
        return c_api->Object_GetProperty_Long(this, object, property, result);
    }
    ani_status Object_GetProperty_Float(ani_object object, ani_property property, ani_float *result)
    {
        return c_api->Object_GetProperty_Float(this, object, property, result);
    }
    ani_status Object_GetProperty_Double(ani_object object, ani_property property, ani_double *result)
    {
        return c_api->Object_GetProperty_Double(this, object, property, result);
    }
    ani_status Object_GetProperty_Ref(ani_object object, ani_property property, ani_ref *result)
    {
        return c_api->Object_GetProperty_Ref(this, object, property, result);
    }
    ani_status Object_SetProperty_Boolean(ani_object object, ani_property property, ani_boolean value)
    {
        return c_api->Object_SetProperty_Boolean(this, object, property, value);
    }
    ani_status Object_SetProperty_Char(ani_object object, ani_property property, ani_char value)
    {
        return c_api->Object_SetProperty_Char(this, object, property, value);
    }
    ani_status Object_SetProperty_Byte(ani_object object, ani_property property, ani_byte value)
    {
        return c_api->Object_SetProperty_Byte(this, object, property, value);
    }
    ani_status Object_SetProperty_Short(ani_object object, ani_property property, ani_short value)
    {
        return c_api->Object_SetProperty_Byte(this, object, property, value);
    }
    ani_status Object_SetProperty_Int(ani_object object, ani_property property, ani_int value)
    {
        return c_api->Object_SetProperty_Int(this, object, property, value);
    }
    ani_status Object_SetProperty_Long(ani_object object, ani_property property, ani_long value)
    {
        return c_api->Object_SetProperty_Long(this, object, property, value);
    }
    ani_status Object_SetProperty_Float(ani_object object, ani_property property, ani_float value)
    {
        return c_api->Object_SetProperty_Float(this, object, property, value);
    }
    ani_status Object_SetProperty_Double(ani_object object, ani_property property, ani_double value)
    {
        return c_api->Object_SetProperty_Double(this, object, property, value);
    }
    ani_status Object_SetProperty_Ref(ani_object object, ani_property property, ani_ref value)
    {
        return c_api->Object_SetProperty_Ref(this, object, property, value);
    }
    ani_status Object_GetPropertyByName_Boolean(ani_object object, const char *name, ani_boolean *result)
    {
        return c_api->Object_GetPropertyByName_Boolean(this, object, name, result);
    }
    ani_status Object_GetPropertyByName_Char(ani_object object, const char *name, ani_char *result)
    {
        return c_api->Object_GetPropertyByName_Char(this, object, name, result);
    }
    ani_status Object_GetPropertyByName_Byte(ani_object object, const char *name, ani_byte *result)
    {
        return c_api->Object_GetPropertyByName_Byte(this, object, name, result);
    }
    ani_status Object_GetPropertyByName_Short(ani_object object, const char *name, ani_short *result)
    {
        return c_api->Object_GetPropertyByName_Short(this, object, name, result);
    }
    ani_status Object_GetPropertyByName_Int(ani_object object, const char *name, ani_int *result)
    {
        return c_api->Object_GetPropertyByName_Int(this, object, name, result);
    }
    ani_status Object_GetPropertyByName_Long(ani_object object, const char *name, ani_long *result)
    {
        return c_api->Object_GetPropertyByName_Long(this, object, name, result);
    }
    ani_status Object_GetPropertyByName_Float(ani_object object, const char *name, ani_float *result)
    {
        return c_api->Object_GetPropertyByName_Float(this, object, name, result);
    }
    ani_status Object_GetPropertyByName_Double(ani_object object, const char *name, ani_double *result)
    {
        return c_api->Object_GetPropertyByName_Double(this, object, name, result);
    }
    ani_status Object_GetPropertyByName_Ref(ani_object object, const char *name, ani_ref *result)
    {
        return c_api->Object_GetPropertyByName_Ref(this, object, name, result);
    }
    ani_status Object_SetPropertyByName_Boolean(ani_object object, const char *name, ani_boolean value)
    {
        return c_api->Object_SetPropertyByName_Boolean(this, object, name, value);
    }
    ani_status Object_SetPropertyByName_Char(ani_object object, const char *name, ani_char value)
    {
        return c_api->Object_SetPropertyByName_Char(this, object, name, value);
    }
    ani_status Object_SetPropertyByName_Byte(ani_object object, const char *name, ani_byte value)
    {
        return c_api->Object_SetPropertyByName_Byte(this, object, name, value);
    }
    ani_status Object_SetPropertyByName_Short(ani_object object, const char *name, ani_short value)
    {
        return c_api->Object_SetPropertyByName_Short(this, object, name, value);
    }
    ani_status Object_SetPropertyByName_Int(ani_object object, const char *name, ani_int value)
    {
        return c_api->Object_SetPropertyByName_Int(this, object, name, value);
    }
    ani_status Object_SetPropertyByName_Long(ani_object object, const char *name, ani_long value)
    {
        return c_api->Object_SetPropertyByName_Long(this, object, name, value);
    }
    ani_status Object_SetPropertyByName_Float(ani_object object, const char *name, ani_float value)
    {
        return c_api->Object_SetPropertyByName_Float(this, object, name, value);
    }
    ani_status Object_SetPropertyByName_Double(ani_object object, const char *name, ani_double value)
    {
        return c_api->Object_SetPropertyByName_Double(this, object, name, value);
    }
    ani_status Object_SetPropertyByName_Ref(ani_object object, const char *name, ani_ref value)
    {
        return c_api->Object_SetPropertyByName_Ref(this, object, name, value);
    }
    ani_status Object_CallMethod_Boolean(ani_object object, ani_method method, ani_boolean *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Object_CallMethod_Boolean_V(this, object, method, result, args);
        va_end(args);
        return status;
    }
    ani_status Object_CallMethod_Boolean_A(ani_object object, ani_method method, ani_boolean *result,
                                           const ani_value *args)
    {
        return c_api->Object_CallMethod_Boolean_A(this, object, method, result, args);
    }
    ani_status Object_CallMethod_Boolean_V(ani_object object, ani_method method, ani_boolean *result, va_list args)
    {
        return c_api->Object_CallMethod_Boolean_V(this, object, method, result, args);
    }
    ani_status Object_CallMethod_Char(ani_object object, ani_method method, ani_char *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Object_CallMethod_Char_V(this, object, method, result, args);
        va_end(args);
        return status;
    }
    ani_status Object_CallMethod_Char_A(ani_object object, ani_method method, ani_char *result, const ani_value *args)
    {
        return c_api->Object_CallMethod_Char_A(this, object, method, result, args);
    }
    ani_status Object_CallMethod_Char_V(ani_object object, ani_method method, ani_char *result, va_list args)
    {
        return c_api->Object_CallMethod_Char_V(this, object, method, result, args);
    }
    ani_status Object_CallMethod_Byte(ani_object object, ani_method method, ani_byte *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Object_CallMethod_Byte_V(this, object, method, result, args);
        va_end(args);
        return status;
    }
    ani_status Object_CallMethod_Byte_A(ani_object object, ani_method method, ani_byte *result, const ani_value *args)
    {
        return c_api->Object_CallMethod_Byte_A(this, object, method, result, args);
    }
    ani_status Object_CallMethod_Byte_V(ani_object object, ani_method method, ani_byte *result, va_list args)
    {
        return c_api->Object_CallMethod_Byte_V(this, object, method, result, args);
    }
    ani_status Object_CallMethod_Short(ani_object object, ani_method method, ani_short *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Object_CallMethod_Short_V(this, object, method, result, args);
        va_end(args);
        return status;
    }
    ani_status Object_CallMethod_Short_A(ani_object object, ani_method method, ani_short *result, const ani_value *args)
    {
        return c_api->Object_CallMethod_Short_A(this, object, method, result, args);
    }
    ani_status Object_CallMethod_Short_V(ani_object object, ani_method method, ani_short *result, va_list args)
    {
        return c_api->Object_CallMethod_Short_V(this, object, method, result, args);
    }
    ani_status Object_CallMethod_Int(ani_object object, ani_method method, ani_int *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Object_CallMethod_Int_V(this, object, method, result, args);
        va_end(args);
        return status;
    }
    ani_status Object_CallMethod_Int_A(ani_object object, ani_method method, ani_int *result, const ani_value *args)
    {
        return c_api->Object_CallMethod_Int_A(this, object, method, result, args);
    }
    ani_status Object_CallMethod_Int_V(ani_object object, ani_method method, ani_int *result, va_list args)
    {
        return c_api->Object_CallMethod_Int_V(this, object, method, result, args);
    }
    ani_status Object_CallMethod_Long(ani_object object, ani_method method, ani_long *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Object_CallMethod_Long_V(this, object, method, result, args);
        va_end(args);
        return status;
    }
    ani_status Object_CallMethod_Long_A(ani_object object, ani_method method, ani_long *result, const ani_value *args)
    {
        return c_api->Object_CallMethod_Long_A(this, object, method, result, args);
    }
    ani_status Object_CallMethod_Long_V(ani_object object, ani_method method, ani_long *result, va_list args)
    {
        return c_api->Object_CallMethod_Long_V(this, object, method, result, args);
    }
    ani_status Object_CallMethod_Float(ani_object object, ani_method method, ani_float *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Object_CallMethod_Float_V(this, object, method, result, args);
        va_end(args);
        return status;
    }
    ani_status Object_CallMethod_Float_A(ani_object object, ani_method method, ani_float *result, const ani_value *args)
    {
        return c_api->Object_CallMethod_Float_A(this, object, method, result, args);
    }
    ani_status Object_CallMethod_Float_V(ani_object object, ani_method method, ani_float *result, va_list args)
    {
        return c_api->Object_CallMethod_Float_V(this, object, method, result, args);
    }
    ani_status Object_CallMethod_Double(ani_object object, ani_method method, ani_double *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Object_CallMethod_Double_V(this, object, method, result, args);
        va_end(args);
        return status;
    }
    ani_status Object_CallMethod_Double_A(ani_object object, ani_method method, ani_double *result,
                                          const ani_value *args)
    {
        return c_api->Object_CallMethod_Double_A(this, object, method, result, args);
    }
    ani_status Object_CallMethod_Double_V(ani_object object, ani_method method, ani_double *result, va_list args)
    {
        return c_api->Object_CallMethod_Double_V(this, object, method, result, args);
    }
    ani_status Object_CallMethod_Ref(ani_object object, ani_method method, ani_ref *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Object_CallMethod_Ref_V(this, object, method, result, args);
        va_end(args);
        return status;
    }
    ani_status Object_CallMethod_Ref_A(ani_object object, ani_method method, ani_ref *result, const ani_value *args)
    {
        return c_api->Object_CallMethod_Ref_A(this, object, method, result, args);
    }
    ani_status Object_CallMethod_Ref_V(ani_object object, ani_method method, ani_ref *result, va_list args)
    {
        return c_api->Object_CallMethod_Ref_V(this, object, method, result, args);
    }
    ani_status Object_CallMethod_Void(ani_object object, ani_method method, ...)
    {
        va_list args;
        va_start(args, method);
        ani_status status = c_api->Object_CallMethod_Void_V(this, object, method, args);
        va_end(args);
        return status;
    }
    ani_status Object_CallMethod_Void_A(ani_object object, ani_method method, const ani_value *args)
    {
        return c_api->Object_CallMethod_Void_A(this, object, method, args);
    }
    ani_status Object_CallMethod_Void_V(ani_object object, ani_method method, va_list args)
    {
        return c_api->Object_CallMethod_Void_V(this, object, method, args);
    }
    ani_status Object_CallMethodByName_Boolean(ani_object object, const char *name, const char *signature,
                                               ani_boolean *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Object_CallMethodByName_Boolean_V(this, object, name, signature, result, args);
        va_end(args);
        return status;
    }
    ani_status Object_CallMethodByName_Boolean_A(ani_object object, const char *name, const char *signature,
                                                 ani_boolean *result, const ani_value *args)
    {
        return c_api->Object_CallMethodByName_Boolean_A(this, object, name, signature, result, args);
    }
    ani_status Object_CallMethodByName_Boolean_V(ani_object object, const char *name, const char *signature,
                                                 ani_boolean *result, va_list args)
    {
        return c_api->Object_CallMethodByName_Boolean_V(this, object, name, signature, result, args);
    }
    ani_status Object_CallMethodByName_Char(ani_object object, const char *name, const char *signature,
                                            ani_char *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Object_CallMethodByName_Char_V(this, object, name, signature, result, args);
        va_end(args);
        return status;
    }
    ani_status Object_CallMethodByName_Char_A(ani_object object, const char *name, const char *signature,
                                              ani_char *result, const ani_value *args)
    {
        return c_api->Object_CallMethodByName_Char_A(this, object, name, signature, result, args);
    }
    ani_status Object_CallMethodByName_Char_V(ani_object object, const char *name, const char *signature,
                                              ani_char *result, va_list args)
    {
        return c_api->Object_CallMethodByName_Char_V(this, object, name, signature, result, args);
    }
    ani_status Object_CallMethodByName_Byte(ani_object object, const char *name, const char *signature,
                                            ani_byte *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Object_CallMethodByName_Byte_V(this, object, name, signature, result, args);
        va_end(args);
        return status;
    }
    ani_status Object_CallMethodByName_Byte_A(ani_object object, const char *name, const char *signature,
                                              ani_byte *result, const ani_value *args)
    {
        return c_api->Object_CallMethodByName_Byte_A(this, object, name, signature, result, args);
    }
    ani_status Object_CallMethodByName_Byte_V(ani_object object, const char *name, const char *signature,
                                              ani_byte *result, va_list args)
    {
        return c_api->Object_CallMethodByName_Byte_V(this, object, name, signature, result, args);
    }
    ani_status Object_CallMethodByName_Short(ani_object object, const char *name, const char *signature,
                                             ani_short *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Object_CallMethodByName_Short_V(this, object, name, signature, result, args);
        va_end(args);
        return status;
    }
    ani_status Object_CallMethodByName_Short_A(ani_object object, const char *name, const char *signature,
                                               ani_short *result, const ani_value *args)
    {
        return c_api->Object_CallMethodByName_Short_A(this, object, name, signature, result, args);
    }
    ani_status Object_CallMethodByName_Short_V(ani_object object, const char *name, const char *signature,
                                               ani_short *result, va_list args)
    {
        return c_api->Object_CallMethodByName_Short_V(this, object, name, signature, result, args);
    }
    ani_status Object_CallMethodByName_Int(ani_object object, const char *name, const char *signature, ani_int *result,
                                           ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Object_CallMethodByName_Int_V(this, object, name, signature, result, args);
        va_end(args);
        return status;
    }
    ani_status Object_CallMethodByName_Int_A(ani_object object, const char *name, const char *signature,
                                             ani_int *result, const ani_value *args)
    {
        return c_api->Object_CallMethodByName_Int_A(this, object, name, signature, result, args);
    }
    ani_status Object_CallMethodByName_Int_V(ani_object object, const char *name, const char *signature,
                                             ani_int *result, va_list args)
    {
        return c_api->Object_CallMethodByName_Int_V(this, object, name, signature, result, args);
    }
    ani_status Object_CallMethodByName_Long(ani_object object, const char *name, const char *signature,
                                            ani_long *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Object_CallMethodByName_Long_V(this, object, name, signature, result, args);
        va_end(args);
        return status;
    }
    ani_status Object_CallMethodByName_Long_A(ani_object object, const char *name, const char *signature,
                                              ani_long *result, const ani_value *args)
    {
        return c_api->Object_CallMethodByName_Long_A(this, object, name, signature, result, args);
    }
    ani_status Object_CallMethodByName_Long_V(ani_object object, const char *name, const char *signature,
                                              ani_long *result, va_list args)
    {
        return c_api->Object_CallMethodByName_Long_V(this, object, name, signature, result, args);
    }
    ani_status Object_CallMethodByName_Float(ani_object object, const char *name, const char *signature,
                                             ani_float *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Object_CallMethodByName_Float_V(this, object, name, signature, result, args);
        va_end(args);
        return status;
    }
    ani_status Object_CallMethodByName_Float_A(ani_object object, const char *name, const char *signature,
                                               ani_float *result, const ani_value *args)
    {
        return c_api->Object_CallMethodByName_Float_A(this, object, name, signature, result, args);
    }
    ani_status Object_CallMethodByName_Float_V(ani_object object, const char *name, const char *signature,
                                               ani_float *result, va_list args)
    {
        return c_api->Object_CallMethodByName_Float_V(this, object, name, signature, result, args);
    }
    ani_status Object_CallMethodByName_Double(ani_object object, const char *name, const char *signature,
                                              ani_double *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Object_CallMethodByName_Double_V(this, object, name, signature, result, args);
        va_end(args);
        return status;
    }
    ani_status Object_CallMethodByName_Double_A(ani_object object, const char *name, const char *signature,
                                                ani_double *result, const ani_value *args)
    {
        return c_api->Object_CallMethodByName_Double_A(this, object, name, signature, result, args);
    }
    ani_status Object_CallMethodByName_Double_V(ani_object object, const char *name, const char *signature,
                                                ani_double *result, va_list args)
    {
        return c_api->Object_CallMethodByName_Double_V(this, object, name, signature, result, args);
    }
    ani_status Object_CallMethodByName_Ref(ani_object object, const char *name, const char *signature, ani_ref *result,
                                           ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Object_CallMethodByName_Ref_V(this, object, name, signature, result, args);
        va_end(args);
        return status;
    }
    ani_status Object_CallMethodByName_Ref_A(ani_object object, const char *name, const char *signature,
                                             ani_ref *result, const ani_value *args)
    {
        return c_api->Object_CallMethodByName_Ref_A(this, object, name, signature, result, args);
    }
    ani_status Object_CallMethodByName_Ref_V(ani_object object, const char *name, const char *signature,
                                             ani_ref *result, va_list args)
    {
        return c_api->Object_CallMethodByName_Ref_V(this, object, name, signature, result, args);
    }
    ani_status Object_CallMethodByName_Void(ani_object object, const char *name, const char *signature, ...)
    {
        va_list args;
        va_start(args, signature);
        ani_status status = c_api->Object_CallMethodByName_Void_V(this, object, name, signature, args);
        va_end(args);
        return status;
    }
    ani_status Object_CallMethodByName_Void_A(ani_object object, const char *name, const char *signature,
                                              const ani_value *args)
    {
        return c_api->Object_CallMethodByName_Void_A(this, object, name, signature, args);
    }
    ani_status Object_CallMethodByName_Void_V(ani_object object, const char *name, const char *signature, va_list args)
    {
        return c_api->Object_CallMethodByName_Void_V(this, object, name, signature, args);
    }
    ani_status Tuple_NewTupleValue(ani_tuple tuple, ani_tuple_value *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Tuple_NewTupleValue_V(this, tuple, result, args);
        va_end(args);
        return status;
    }
    ani_status Tuple_NewTupleValue_A(ani_tuple tuple, ani_tuple_value *result, const ani_value *args)
    {
        return c_api->Tuple_NewTupleValue_A(this, tuple, result, args);
    }
    ani_status Tuple_NewTupleValue_V(ani_tuple tuple, ani_tuple_value *result, va_list args)
    {
        return c_api->Tuple_NewTupleValue_V(this, tuple, result, args);
    }
    ani_status Tuple_GetNumberOfItems(ani_tuple tuple, ani_size *result)
    {
        return c_api->Tuple_GetNumberOfItems(this, tuple, result);
    }
    ani_status Tuple_GetItemKind(ani_tuple tuple, ani_size index, ani_kind *result)
    {
        return c_api->Tuple_GetItemKind(this, tuple, index, result);
    }
    ani_status Tuple_GetItemType(ani_tuple tuple, ani_size index, ani_type *result)
    {
        return c_api->Tuple_GetItemType(this, tuple, index, result);
    }
    ani_status TupleValue_GetTuple(ani_tuple_value value, ani_tuple *result)
    {
        return c_api->TupleValue_GetTuple(this, value, result);
    }
    ani_status TupleValue_GetItem_Boolean(ani_tuple_value tuple_value, ani_size index, ani_boolean *result)
    {
        return c_api->TupleValue_GetItem_Boolean(this, tuple_value, index, result);
    }
    ani_status TupleValue_GetItem_Char(ani_tuple_value tuple_value, ani_size index, ani_char *result)
    {
        return c_api->TupleValue_GetItem_Char(this, tuple_value, index, result);
    }
    ani_status TupleValue_GetItem_Byte(ani_tuple_value tuple_value, ani_size index, ani_byte *result)
    {
        return c_api->TupleValue_GetItem_Byte(this, tuple_value, index, result);
    }
    ani_status TupleValue_GetItem_Short(ani_tuple_value tuple_value, ani_size index, ani_short *result)
    {
        return c_api->TupleValue_GetItem_Short(this, tuple_value, index, result);
    }
    ani_status TupleValue_GetItem_Int(ani_tuple_value tuple_value, ani_size index, ani_int *result)
    {
        return c_api->TupleValue_GetItem_Int(this, tuple_value, index, result);
    }
    ani_status TupleValue_GetItem_Long(ani_tuple_value tuple_value, ani_size index, ani_long *result)
    {
        return c_api->TupleValue_GetItem_Long(this, tuple_value, index, result);
    }
    ani_status TupleValue_GetItem_Float(ani_tuple_value tuple_value, ani_size index, ani_float *result)
    {
        return c_api->TupleValue_GetItem_Float(this, tuple_value, index, result);
    }
    ani_status TupleValue_GetItem_Double(ani_tuple_value tuple_value, ani_size index, ani_double *result)
    {
        return c_api->TupleValue_GetItem_Double(this, tuple_value, index, result);
    }
    ani_status TupleValue_GetItem_Ref(ani_tuple_value tuple_value, ani_size index, ani_ref *result)
    {
        return c_api->TupleValue_GetItem_Ref(this, tuple_value, index, result);
    }
    ani_status TupleValue_SetItem_Boolean(ani_tuple_value tuple_value, ani_size index, ani_boolean value)
    {
        return c_api->TupleValue_SetItem_Boolean(this, tuple_value, index, value);
    }
    ani_status TupleValue_SetItem_Char(ani_tuple_value tuple_value, ani_size index, ani_char value)
    {
        return c_api->TupleValue_SetItem_Char(this, tuple_value, index, value);
    }
    ani_status TupleValue_SetItem_Byte(ani_tuple_value tuple_value, ani_size index, ani_byte value)
    {
        return c_api->TupleValue_SetItem_Byte(this, tuple_value, index, value);
    }
    ani_status TupleValue_SetItem_Short(ani_tuple_value tuple_value, ani_size index, ani_short value)
    {
        return c_api->TupleValue_SetItem_Short(this, tuple_value, index, value);
    }
    ani_status TupleValue_SetItem_Int(ani_tuple_value tuple_value, ani_size index, ani_int value)
    {
        return c_api->TupleValue_SetItem_Int(this, tuple_value, index, value);
    }
    ani_status TupleValue_SetItem_Long(ani_tuple_value tuple_value, ani_size index, ani_long value)
    {
        return c_api->TupleValue_SetItem_Long(this, tuple_value, index, value);
    }
    ani_status TupleValue_SetItem_Float(ani_tuple_value tuple_value, ani_size index, ani_float value)
    {
        return c_api->TupleValue_SetItem_Float(this, tuple_value, index, value);
    }
    ani_status TupleValue_SetItem_Double(ani_tuple_value tuple_value, ani_size index, ani_double value)
    {
        return c_api->TupleValue_SetItem_Double(this, tuple_value, index, value);
    }
    ani_status TupleValue_SetItem_Ref(ani_tuple_value tuple_value, ani_size index, ani_ref value)
    {
        return c_api->TupleValue_SetItem_Ref(this, tuple_value, index, value);
    }
    ani_status GlobalReference_Create(ani_ref ref, ani_gref *result)
    {
        return c_api->GlobalReference_Create(this, ref, result);
    }
    ani_status GlobalReference_Delete(ani_gref ref)
    {
        return c_api->GlobalReference_Delete(this, ref);
    }
    ani_status WeakReference_Create(ani_ref ref, ani_wref *result)
    {
        return c_api->WeakReference_Create(this, ref, result);
    }
    ani_status WeakReference_Delete(ani_wref wref)
    {
        return c_api->WeakReference_Delete(this, wref);
    }
    ani_status WeakReference_GetReference(ani_wref wref, ani_ref *result)
    {
        return c_api->WeakReference_GetReference(this, wref, result);
    }
    ani_status CreateArrayBuffer(size_t length, void **data_result, ani_arraybuffer *arraybuffer_result)
    {
        return c_api->CreateArrayBuffer(this, length, data_result, arraybuffer_result);
    }
    ani_status CreateArrayBufferExternal(void *external_data, size_t length, ani_finalizer finalizer, void *hint,
                                         ani_arraybuffer *result)
    {
        return c_api->CreateArrayBufferExternal(this, external_data, length, finalizer, hint, result);
    }
    ani_status ArrayBuffer_GetInfo(ani_arraybuffer arraybuffer, void **data_result, size_t *length_result)
    {
        return c_api->ArrayBuffer_GetInfo(this, arraybuffer, data_result, length_result);
    }
    ani_status Reflection_FromMethod(ani_object method, ani_method *result)
    {
        return c_api->Reflection_FromMethod(this, method, result);
    }
    ani_status Reflection_ToMethod(ani_class cls, ani_method method, ani_object *result)
    {
        return c_api->Reflection_ToMethod(this, cls, method, result);
    }
    ani_status Reflection_FromField(ani_object field, ani_field *result)
    {
        return c_api->Reflection_FromField(this, field, result);
    }
    ani_status Reflection_ToField(ani_class cls, ani_field field, ani_object *result)
    {
        return c_api->Reflection_ToField(this, cls, field, result);
    }
    ani_status Reflection_FromStaticMethod(ani_object method, ani_static_method *result)
    {
        return c_api->Reflection_FromStaticMethod(this, method, result);
    }
    ani_status Reflection_ToStaticMethod(ani_class cls, ani_static_method method, ani_object *result)
    {
        return c_api->Reflection_ToStaticMethod(this, cls, method, result);
    }
    ani_status Reflection_FromStaticField(ani_object field, ani_static_field *result)
    {
        return c_api->Reflection_FromStaticField(this, field, result);
    }
    ani_status Reflection_ToStaticField(ani_class cls, ani_static_field field, ani_object *result)
    {
        return c_api->Reflection_ToStaticField(this, cls, field, result);
    }
    ani_status Reflection_FromFunction(ani_object function, ani_function *result)
    {
        return c_api->Reflection_FromFunction(this, function, result);
    }
    ani_status Reflection_ToFunction(ani_function function, ani_object *result)
    {
        return c_api->Reflection_ToFunction(this, function, result);
    }
    ani_status Reflection_FromVariable(ani_object variable, ani_variable *result)
    {
        return c_api->Reflection_FromVariable(this, variable, result);
    }
    ani_status Reflection_ToVariable(ani_variable variable, ani_object *result)
    {
        return c_api->Reflection_ToVariable(this, variable, result);
    }
    ani_status CLS_Register(void *initial_data, ani_finalizer finalizer, void *hint, ani_cls_slot *result)
    {
        return c_api->CLS_Register(this, initial_data, finalizer, hint, result);
    }
    ani_status CLS_Unregister(ani_cls_slot slot)
    {
        return c_api->CLS_Unregister(this, slot);
    }
    ani_status CLS_SetData(ani_cls_slot slot, void *data)
    {
        return c_api->CLS_SetData(this, slot, data);
    }
    ani_status CLS_GetData(ani_cls_slot slot, void **result)
    {
        return c_api->CLS_GetData(this, slot, result);
    }
    ani_status Coroutine_LaunchFunctionalObject(ani_fn_object fn, ani_size argc, ani_ref *argv, ani_promise *result)
    {
        return c_api->Coroutine_LaunchFunctionalObject(this, fn, argc, argv, result);
    }
    ani_status Coroutine_LaunchFunction(ani_function function, ani_promise *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Coroutine_LaunchFunction_V(this, function, result, args);
        va_end(args);
        return status;
    }
    ani_status Coroutine_LaunchFunction_A(ani_function function, ani_promise *result, const ani_value *args)
    {
        return c_api->Coroutine_LaunchFunction_A(this, function, result, args);
    }
    ani_status Coroutine_LaunchFunction_V(ani_function function, ani_promise *result, va_list args)
    {
        return c_api->Coroutine_LaunchFunction_V(this, function, result, args);
    }
    ani_status Coroutine_LaunchMethod(ani_object self, ani_function function, ani_promise *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Coroutine_LaunchMethod_V(this, self, function, result, args);
        va_end(args);
        return status;
    }
    ani_status Coroutine_LaunchMethod_A(ani_object self, ani_function function, ani_promise *result,
                                        const ani_value *args)
    {
        return c_api->Coroutine_LaunchMethod_A(this, self, function, result, args);
    }
    ani_status Coroutine_LaunchMethod_V(ani_object self, ani_function function, ani_promise *result, va_list args)
    {
        return c_api->Coroutine_LaunchMethod_V(this, self, function, result, args);
    }
    ani_status Coroutine_LaunchStaticMethod(ani_class cls, ani_function function, ani_promise *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Coroutine_LaunchStaticMethod_V(this, cls, function, result, args);
        va_end(args);
        return status;
    }
    ani_status Coroutine_LaunchStaticMethod_A(ani_class cls, ani_function function, ani_promise *result,
                                              const ani_value *args)
    {
        return c_api->Coroutine_LaunchStaticMethod_A(this, cls, function, result, args);
    }
    ani_status Coroutine_LaunchStaticMethod_V(ani_class cls, ani_function function, ani_promise *result, va_list args)
    {
        return c_api->Coroutine_LaunchStaticMethod_V(this, cls, function, result, args);
    }
    ani_status Coroutine_Await_Boolean(ani_promise promise, ani_boolean value)
    {
        return c_api->Coroutine_Await_Boolean(this, promise, value);
    }
    ani_status Coroutine_Await_Char(ani_promise promise, ani_char value)
    {
        return c_api->Coroutine_Await_Char(this, promise, value);
    }
    ani_status Coroutine_Await_Byte(ani_promise promise, ani_byte value)
    {
        return c_api->Coroutine_Await_Byte(this, promise, value);
    }
    ani_status Coroutine_Await_Short(ani_promise promise, ani_short value)
    {
        return c_api->Coroutine_Await_Short(this, promise, value);
    }
    ani_status Coroutine_Await_Int(ani_promise promise, ani_int value)
    {
        return c_api->Coroutine_Await_Int(this, promise, value);
    }
    ani_status Coroutine_Await_Long(ani_promise promise, ani_long value)
    {
        return c_api->Coroutine_Await_Long(this, promise, value);
    }
    ani_status Coroutine_Await_Float(ani_promise promise, ani_float value)
    {
        return c_api->Coroutine_Await_Float(this, promise, value);
    }
    ani_status Coroutine_Await_Double(ani_promise promise, ani_double value)
    {
        return c_api->Coroutine_Await_Double(this, promise, value);
    }
    ani_status Coroutine_Await_Ref(ani_promise promise, ani_ref value)
    {
        return c_api->Coroutine_Await_Ref(this, promise, value);
    }
#endif  // __cplusplus
};

// NOLINTEND
#endif  // __ANI_H__
