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

// Logger interface:
//   typedef void (*ani_logger)(FILE *stream, int log_level, const char *component, const char *message);
//   ani_option:
//     'option': "--logger"
//     'extra': ani_logger
//   where 'log_level' can have the following values:
#define ANI_LOGLEVEL_FATAL 0
#define ANI_LOGLEVEL_ERROR 1
#define ANI_LOGLEVEL_WARNING 2
#define ANI_LOGLEVEL_INFO 3
#define ANI_LOGLEVEL_DEBUG 4

typedef size_t ani_size;

// Primitive types:
typedef uint8_t ani_boolean;
typedef uint16_t ani_char;
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
class __ani_enum_item : public __ani_object {};
class __ani_error : public __ani_object {};
class __ani_tuple_value : public __ani_object {};
class __ani_type : public __ani_object {};
class __ani_arraybuffer : public __ani_object {};
class __ani_string : public __ani_object {};
class __ani_class : public __ani_type {};
class __ani_enum : public __ani_type {};
class __ani_array : public __ani_object {};
class __ani_array_boolean : public __ani_array {};
class __ani_array_char : public __ani_array {};
class __ani_array_byte : public __ani_array {};
class __ani_array_short : public __ani_array {};
class __ani_array_int : public __ani_array {};
class __ani_array_long : public __ani_array {};
class __ani_array_float : public __ani_array {};
class __ani_array_double : public __ani_array {};
class __ani_array_ref : public __ani_array {};
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
typedef __ani_enum_item *ani_enum_item;
typedef __ani_error *ani_error;
typedef __ani_tuple_value *ani_tuple_value;
typedef __ani_type *ani_type;
typedef __ani_arraybuffer *ani_arraybuffer;
typedef __ani_string *ani_string;
typedef __ani_class *ani_class;
typedef __ani_enum *ani_enum;
typedef __ani_array *ani_array;
typedef __ani_array_boolean *ani_array_boolean;
typedef __ani_array_char *ani_array_char;
typedef __ani_array_byte *ani_array_byte;
typedef __ani_array_short *ani_array_short;
typedef __ani_array_int *ani_array_int;
typedef __ani_array_long *ani_array_long;
typedef __ani_array_float *ani_array_float;
typedef __ani_array_double *ani_array_double;
typedef __ani_array_ref *ani_array_ref;
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
typedef ani_object ani_enum_item;
typedef ani_object ani_error;
typedef ani_object ani_tuple_value;
typedef ani_object ani_type;
typedef ani_object ani_arraybuffer;
typedef ani_object ani_string;
typedef ani_type ani_class;
typedef ani_type ani_enum;
typedef ani_object ani_array;
typedef ani_array ani_array_boolean;
typedef ani_array ani_array_char;
typedef ani_array ani_array_byte;
typedef ani_array ani_array_short;
typedef ani_array ani_array_int;
typedef ani_array ani_array_long;
typedef ani_array ani_array_float;
typedef ani_array ani_array_double;
typedef ani_array ani_array_ref;
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

struct __ani_method;
typedef struct __ani_method *ani_method;

struct __ani_static_method;
typedef struct __ani_static_method *ani_static_method;

struct __ani_resolver;
typedef struct __ani_resolver *ani_resolver;

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
    ANI_INCORRECT_REF,
    ANI_PENDING_ERROR,
    ANI_NOT_FOUND,
    ANI_ALREADY_BINDED,
    ANI_OUT_OF_REF,
    ANI_OUT_OF_MEMORY,
    ANI_OUT_OF_RANGE,
    ANI_BUFFER_TO_SMALL,
    ANI_INVALID_VERSION,
    ANI_AMBIGUOUS,
    // NOTE: Add necessary status codes
} ani_status;

typedef struct {
    const char *option;
    void *extra;
} ani_option;

typedef struct {
    size_t nr_options;
    const ani_option *options;
} ani_options;

struct __ani_vm_api {
    void *reserved0;
    void *reserved1;
    void *reserved2;
    void *reserved3;

    ani_status (*DestroyVM)(ani_vm *vm);
    ani_status (*GetEnv)(ani_vm *vm, uint32_t version, ani_env **result);
    ani_status (*AttachCurrentThread)(ani_vm *vm, const ani_options *options, uint32_t version, ani_env **result);
    ani_status (*DetachCurrentThread)(ani_vm *vm);
};

#define ANI_EXPORT __attribute__((visibility("default")))

#ifdef __cplusplus
extern "C" {
#endif

ANI_EXPORT ani_status ANI_CreateVM(const ani_options *options, uint32_t version, ani_vm **result);
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
     * @param[in] name The name of the function to find.
     * @param[in] signature The signature of the function to find.
     * @param[out] result A pointer to the function object.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Module_FindFunction)(ani_env *env, ani_module module, const char *name, const char *signature,
                                      ani_function *result);

    /**
     * @brief Finds a variable within a module by its name.
     *
     * This function locates a variable within the specified module based on its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] module The module to search within.
     * @param[in] name The name of the variable to find.
     * @param[out] result A pointer to the variable object.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Module_FindVariable)(ani_env *env, ani_module module, const char *name, ani_variable *result);

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
     * @param[in] name The name of the function to find.
     * @param[in] signature The signature of the function to find.
     * @param[out] result A pointer to the function object.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Namespace_FindFunction)(ani_env *env, ani_namespace ns, const char *name, const char *signature,
                                         ani_function *result);

    /**
     * @brief Finds a variable within a namespace by its name.
     *
     * This function locates a variable within the specified namespace based on its name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] ns The namespace to search within.
     * @param[in] name The name of the variable to find.
     * @param[out] result A pointer to the variable object.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Namespace_FindVariable)(ani_env *env, ani_namespace ns, const char *name, ani_variable *result);

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
     * @brief Retrieves the length of an array.
     *
     * This function retrieves the length of the specified array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The array whose length is to be retrieved.
     * @param[out] result A pointer to store the length of the array.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Array_GetLength)(ani_env *env, ani_array array, ani_size *result);

    /**
     * @brief Creates a new array of booleans.
     *
     * This function creates a new array of the specified length for boolean values.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] length The length of the array to be created.
     * @param[out] result A pointer to store the created array.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Array_New_Boolean)(ani_env *env, ani_size length, ani_array_boolean *result);

    /**
     * @brief Creates a new array of characters.
     *
     * This function creates a new array of the specified length for character values.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] length The length of the array to be created.
     * @param[out] result A pointer to store the created array.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Array_New_Char)(ani_env *env, ani_size length, ani_array_char *result);

    /**
     * @brief Creates a new array of bytes.
     *
     * This function creates a new array of the specified length for byte values.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] length The length of the array to be created.
     * @param[out] result A pointer to store the created array.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Array_New_Byte)(ani_env *env, ani_size length, ani_array_byte *result);

    /**
     * @brief Creates a new array of shorts.
     *
     * This function creates a new array of the specified length for short integer values.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] length The length of the array to be created.
     * @param[out] result A pointer to store the created array.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Array_New_Short)(ani_env *env, ani_size length, ani_array_short *result);

    /**
     * @brief Creates a new array of integers.
     *
     * This function creates a new array of the specified length for integer values.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] length The length of the array to be created.
     * @param[out] result A pointer to store the created array.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Array_New_Int)(ani_env *env, ani_size length, ani_array_int *result);

    /**
     * @brief Creates a new array of long integers.
     *
     * This function creates a new array of the specified length for long integer values.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] length The length of the array to be created.
     * @param[out] result A pointer to store the created array.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Array_New_Long)(ani_env *env, ani_size length, ani_array_long *result);

    /**
     * @brief Creates a new array of floats.
     *
     * This function creates a new array of the specified length for float values.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] length The length of the array to be created.
     * @param[out] result A pointer to store the created array.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Array_New_Float)(ani_env *env, ani_size length, ani_array_float *result);

    /**
     * @brief Creates a new array of doubles.
     *
     * This function creates a new array of the specified length for double values.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] length The length of the array to be created.
     * @param[out] result A pointer to store the created array.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Array_New_Double)(ani_env *env, ani_size length, ani_array_double *result);

    /**
     * @brief Retrieves a region of boolean values from an array.
     *
     * This function retrieves a portion of the specified boolean array into a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The array to retrieve values from.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to retrieve.
     * @param[out] native_buffer A buffer to store the retrieved boolean values.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Array_GetRegion_Boolean)(ani_env *env, ani_array_boolean array, ani_size offset, ani_size length,
                                          ani_boolean *native_buffer);

    /**
     * @brief Retrieves a region of character values from an array.
     *
     * This function retrieves a portion of the specified character array into a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The array to retrieve values from.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to retrieve.
     * @param[out] native_buffer A buffer to store the retrieved character values.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Array_GetRegion_Char)(ani_env *env, ani_array_char array, ani_size offset, ani_size length,
                                       ani_char *native_buffer);

    /**
     * @brief Retrieves a region of byte values from an array.
     *
     * This function retrieves a portion of the specified byte array into a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The array to retrieve values from.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to retrieve.
     * @param[out] native_buffer A buffer to store the retrieved byte values.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Array_GetRegion_Byte)(ani_env *env, ani_array_byte array, ani_size offset, ani_size length,
                                       ani_byte *native_buffer);

    /**
     * @brief Retrieves a region of short values from an array.
     *
     * This function retrieves a portion of the specified short array into a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The array to retrieve values from.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to retrieve.
     * @param[out] native_buffer A buffer to store the retrieved short values.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Array_GetRegion_Short)(ani_env *env, ani_array_short array, ani_size offset, ani_size length,
                                        ani_short *native_buffer);

    /**
     * @brief Retrieves a region of integer values from an array.
     *
     * This function retrieves a portion of the specified integer array into a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The array to retrieve values from.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to retrieve.
     * @param[out] native_buffer A buffer to store the retrieved integer values.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Array_GetRegion_Int)(ani_env *env, ani_array_int array, ani_size offset, ani_size length,
                                      ani_int *native_buffer);

    /**
     * @brief Retrieves a region of long integer values from an array.
     *
     * This function retrieves a portion of the specified long integer array into a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The array to retrieve values from.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to retrieve.
     * @param[out] native_buffer A buffer to store the retrieved long integer values.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Array_GetRegion_Long)(ani_env *env, ani_array_long array, ani_size offset, ani_size length,
                                       ani_long *native_buffer);

    /**
     * @brief Retrieves a region of float values from an array.
     *
     * This function retrieves a portion of the specified float array into a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The array to retrieve values from.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to retrieve.
     * @param[out] native_buffer A buffer to store the retrieved float values.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Array_GetRegion_Float)(ani_env *env, ani_array_float array, ani_size offset, ani_size length,
                                        ani_float *native_buffer);

    /**
     * @brief Retrieves a region of double values from an array.
     *
     * This function retrieves a portion of the specified double array into a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The array to retrieve values from.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to retrieve.
     * @param[out] native_buffer A buffer to store the retrieved double values.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Array_GetRegion_Double)(ani_env *env, ani_array_double array, ani_size offset, ani_size length,
                                         ani_double *native_buffer);

    /**
     * @brief Sets a region of boolean values in an array.
     *
     * This function sets a portion of the specified boolean array using a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The array to set values in.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to set.
     * @param[in] native_buffer A buffer containing the boolean values to set.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Array_SetRegion_Boolean)(ani_env *env, ani_array_boolean array, ani_size offset, ani_size length,
                                          const ani_boolean *native_buffer);

    /**
     * @brief Sets a region of character values in an array.
     *
     * This function sets a portion of the specified character array using a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The array to set values in.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to set.
     * @param[in] native_buffer A buffer containing the character values to set.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Array_SetRegion_Char)(ani_env *env, ani_array_char array, ani_size offset, ani_size length,
                                       const ani_char *native_buffer);

    /**
     * @brief Sets a region of byte values in an array.
     *
     * This function sets a portion of the specified byte array using a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The array to set values in.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to set.
     * @param[in] native_buffer A buffer containing the byte values to set.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Array_SetRegion_Byte)(ani_env *env, ani_array_byte array, ani_size offset, ani_size length,
                                       const ani_byte *native_buffer);

    /**
     * @brief Sets a region of short values in an array.
     *
     * This function sets a portion of the specified short array using a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The array to set values in.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to set.
     * @param[in] native_buffer A buffer containing the short values to set.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Array_SetRegion_Short)(ani_env *env, ani_array_short array, ani_size offset, ani_size length,
                                        const ani_short *native_buffer);

    /**
     * @brief Sets a region of integer values in an array.
     *
     * This function sets a portion of the specified integer array using a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The array to set values in.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to set.
     * @param[in] native_buffer A buffer containing the integer values to set.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Array_SetRegion_Int)(ani_env *env, ani_array_int array, ani_size offset, ani_size length,
                                      const ani_int *native_buffer);

    /**
     * @brief Sets a region of long integer values in an array.
     *
     * This function sets a portion of the specified long integer array using a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The array to set values in.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to set.
     * @param[in] native_buffer A buffer containing the long integer values to set.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Array_SetRegion_Long)(ani_env *env, ani_array_long array, ani_size offset, ani_size length,
                                       const ani_long *native_buffer);

    /**
     * @brief Sets a region of float values in an array.
     *
     * This function sets a portion of the specified float array using a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The array to set values in.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to set.
     * @param[in] native_buffer A buffer containing the float values to set.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Array_SetRegion_Float)(ani_env *env, ani_array_float array, ani_size offset, ani_size length,
                                        const ani_float *native_buffer);

    /**
     * @brief Sets a region of double values in an array.
     *
     * This function sets a portion of the specified double array using a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The array to set values in.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to set.
     * @param[in] native_buffer A buffer containing the double values to set.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Array_SetRegion_Double)(ani_env *env, ani_array_double array, ani_size offset, ani_size length,
                                         const ani_double *native_buffer);

    /**
     * @brief Creates a new array of references.
     *
     * This function creates a new array of references, optionally initializing it with an array of references.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] type The type of the elements of the array.
     * @param[in] length The length of the array to be created.
     * @param[in] initial_element An optional reference to initialize the array. Can be null.
     * @param[out] result A pointer to store the created array of references.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Array_New_Ref)(ani_env *env, ani_type type, ani_size length, ani_ref initial_element,
                                ani_array_ref *result);

    /**
     * @brief Sets a reference at a specific index in an array.
     *
     * This function sets the value of a reference at the specified index in the array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The array of references to modify.
     * @param[in] index The index at which to set the reference.
     * @param[in] ref The reference to set at the specified index.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Array_Set_Ref)(ani_env *env, ani_array_ref array, ani_size index, ani_ref ref);

    /**
     * @brief Retrieves a reference from a specific index in an array.
     *
     * This function retrieves the value of a reference at the specified index in the array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The array of references to query.
     * @param[in] index The index from which to retrieve the reference.
     * @param[out] result A pointer to store the retrieved reference.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Array_Get_Ref)(ani_env *env, ani_array_ref array, ani_size index, ani_ref *result);

    /**
     * @brief Creates a new array
     *
     * This function creates a new array of the specified length.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] length The length of the array to be created.
     * @param[in] initial_element Element the array will be initialized with
     * @param[out] result A pointer to store the created array.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Array_New)(ani_env *env, ani_size length, ani_ref initial_element, ani_array *result);

    /**
     * @brief Sets a value to an array.
     *
     * This function sets a value to array from an ani_ref value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The array to retrieve values from.
     * @param[in] index The index of element to retrieve.
     * @param[in] ref Value to set
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Array_Set)(ani_env *env, ani_array array, ani_size index, ani_ref ref);

    /**
     * @brief Retrieves a value from an array.
     *
     * This function retrieves a value from array into an ani_ref pointer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The array to retrieve values from.
     * @param[in] index The index of element to retrieve.
     * @param[out] result A pointer to store the retrieved value.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Array_Get)(ani_env *env, ani_array array, ani_size index, ani_ref *result);

    /**
     * @brief Push a value to the end of array.
     *
     * This function pushes value from an ani_ref to the end of array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The array to retrieve values from.
     * @param[in] ref Value to set
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Array_Push)(ani_env *env, ani_array array, ani_ref ref);

    /**
     * @brief Retrieves the last element and erases it from array.
     *
     * This function retrieves the last element and erases it from array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The array whose last element is to be retrieved.
     * @param[out] result A pointer to store the last element of the array.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Array_Pop)(ani_env *env, ani_array array, ani_ref *result);

    /**
     * @brief Retrieves the length of an fixedarray.
     *
     * This function retrieves the length of the specified array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixedarray whose length is to be retrieved.
     * @param[out] result A pointer to store the length of the fixedarray.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_GetLength)(ani_env *env, ani_fixedarray array, ani_size *result);

    /**
     * @brief Creates a new fixedarray of booleans.
     *
     * This function creates a new fixedarray of the specified length for boolean values.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] length The length of the fixedarray to be created.
     * @param[out] result A pointer to store the created fixedarray.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_New_Boolean)(ani_env *env, ani_size length, ani_fixedarray_boolean *result);

    /**
     * @brief Creates a new fixedarray of characters.
     *
     * This function creates a new fixedarray of the specified length for character values.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] length The length of the fixedarray to be created.
     * @param[out] result A pointer to store the created fixedarray.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_New_Char)(ani_env *env, ani_size length, ani_fixedarray_char *result);

    /**
     * @brief Creates a new fixedarray of bytes.
     *
     * This function creates a new fixedarray of the specified length for byte values.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] length The length of the fixedarray to be created.
     * @param[out] result A pointer to store the created fixedarray.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_New_Byte)(ani_env *env, ani_size length, ani_fixedarray_byte *result);

    /**
     * @brief Creates a new fixedarray of shorts.
     *
     * This function creates a new fixedarray of the specified length for short integer values.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] length The length of the fixedarray to be created.
     * @param[out] result A pointer to store the created fixedarray.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_New_Short)(ani_env *env, ani_size length, ani_fixedarray_short *result);

    /**
     * @brief Creates a new fixedarray of integers.
     *
     * This function creates a new fixedarray of the specified length for integer values.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] length The length of the fixedarray to be created.
     * @param[out] result A pointer to store the created fixedarray.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_New_Int)(ani_env *env, ani_size length, ani_fixedarray_int *result);

    /**
     * @brief Creates a new fixedarray of long integers.
     *
     * This function creates a new fixedarray of the specified length for long integer values.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] length The length of the fixedarray to be created.
     * @param[out] result A pointer to store the created fixedarray.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_New_Long)(ani_env *env, ani_size length, ani_fixedarray_long *result);

    /**
     * @brief Creates a new fixedarray of floats.
     *
     * This function creates a new fixedarray of the specified length for float values.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] length The length of the fixedarray to be created.
     * @param[out] result A pointer to store the created fixedarray.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_New_Float)(ani_env *env, ani_size length, ani_fixedarray_float *result);

    /**
     * @brief Creates a new fixedarray of doubles.
     *
     * This function creates a new fixedarray of the specified length for double values.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] length The length of the fixedarray to be created.
     * @param[out] result A pointer to store the created fixedarray.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_New_Double)(ani_env *env, ani_size length, ani_fixedarray_double *result);

    /**
     * @brief Retrieves a region of boolean values from an fixedarray.
     *
     * This function retrieves a portion of the specified boolean fixedarray into a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixedarray to retrieve values from.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to retrieve.
     * @param[out] native_buffer A buffer to store the retrieved boolean values.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_GetRegion_Boolean)(ani_env *env, ani_fixedarray_boolean array, ani_size offset,
                                               ani_size length, ani_boolean *native_buffer);

    /**
     * @brief Retrieves a region of character values from an fixedarray.
     *
     * This function retrieves a portion of the specified character fixedarray into a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixedarray to retrieve values from.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to retrieve.
     * @param[out] native_buffer A buffer to store the retrieved character values.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_GetRegion_Char)(ani_env *env, ani_fixedarray_char array, ani_size offset, ani_size length,
                                            ani_char *native_buffer);

    /**
     * @brief Retrieves a region of byte values from an fixedarray.
     *
     * This function retrieves a portion of the specified byte fixedarray into a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixedarray to retrieve values from.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to retrieve.
     * @param[out] native_buffer A buffer to store the retrieved byte values.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_GetRegion_Byte)(ani_env *env, ani_fixedarray_byte array, ani_size offset, ani_size length,
                                            ani_byte *native_buffer);

    /**
     * @brief Retrieves a region of short values from an fixedarray.
     *
     * This function retrieves a portion of the specified short fixedarray into a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixedarray to retrieve values from.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to retrieve.
     * @param[out] native_buffer A buffer to store the retrieved short values.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_GetRegion_Short)(ani_env *env, ani_fixedarray_short array, ani_size offset, ani_size length,
                                             ani_short *native_buffer);

    /**
     * @brief Retrieves a region of integer values from an fixedarray.
     *
     * This function retrieves a portion of the specified integer fixedarray into a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixedarray to retrieve values from.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to retrieve.
     * @param[out] native_buffer A buffer to store the retrieved integer values.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_GetRegion_Int)(ani_env *env, ani_fixedarray_int array, ani_size offset, ani_size length,
                                           ani_int *native_buffer);

    /**
     * @brief Retrieves a region of long integer values from an fixedarray.
     *
     * This function retrieves a portion of the specified long integer fixedarray into a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixedarray to retrieve values from.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to retrieve.
     * @param[out] native_buffer A buffer to store the retrieved long integer values.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_GetRegion_Long)(ani_env *env, ani_fixedarray_long array, ani_size offset, ani_size length,
                                            ani_long *native_buffer);

    /**
     * @brief Retrieves a region of float values from an fixedarray.
     *
     * This function retrieves a portion of the specified float fixedarray into a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixedarray to retrieve values from.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to retrieve.
     * @param[out] native_buffer A buffer to store the retrieved float values.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_GetRegion_Float)(ani_env *env, ani_fixedarray_float array, ani_size offset, ani_size length,
                                             ani_float *native_buffer);

    /**
     * @brief Retrieves a region of double values from an fixedarray.
     *
     * This function retrieves a portion of the specified double fixedarray into a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixedarray to retrieve values from.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to retrieve.
     * @param[out] native_buffer A buffer to store the retrieved double values.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_GetRegion_Double)(ani_env *env, ani_fixedarray_double array, ani_size offset,
                                              ani_size length, ani_double *native_buffer);

    /**
     * @brief Sets a region of boolean values in an fixedarray.
     *
     * This function sets a portion of the specified boolean fixedarray using a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixedarray to set values in.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to set.
     * @param[in] native_buffer A buffer containing the boolean values to set.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_SetRegion_Boolean)(ani_env *env, ani_fixedarray_boolean array, ani_size offset,
                                               ani_size length, const ani_boolean *native_buffer);

    /**
     * @brief Sets a region of character values in an fixedarray.
     *
     * This function sets a portion of the specified character fixedarray using a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixedarray to set values in.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to set.
     * @param[in] native_buffer A buffer containing the character values to set.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_SetRegion_Char)(ani_env *env, ani_fixedarray_char array, ani_size offset, ani_size length,
                                            const ani_char *native_buffer);

    /**
     * @brief Sets a region of byte values in an fixedarray.
     *
     * This function sets a portion of the specified byte fixedarray using a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixedarray to set values in.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to set.
     * @param[in] native_buffer A buffer containing the byte values to set.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_SetRegion_Byte)(ani_env *env, ani_fixedarray_byte array, ani_size offset, ani_size length,
                                            const ani_byte *native_buffer);

    /**
     * @brief Sets a region of short values in an fixedarray.
     *
     * This function sets a portion of the specified short fixedarray using a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixedarray to set values in.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to set.
     * @param[in] native_buffer A buffer containing the short values to set.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_SetRegion_Short)(ani_env *env, ani_fixedarray_short array, ani_size offset, ani_size length,
                                             const ani_short *native_buffer);

    /**
     * @brief Sets a region of integer values in an fixedarray.
     *
     * This function sets a portion of the specified integer fixedarray using a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixedarray to set values in.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to set.
     * @param[in] native_buffer A buffer containing the integer values to set.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_SetRegion_Int)(ani_env *env, ani_fixedarray_int array, ani_size offset, ani_size length,
                                           const ani_int *native_buffer);

    /**
     * @brief Sets a region of long integer values in an fixedarray.
     *
     * This function sets a portion of the specified long integer fixedarray using a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixedarray to set values in.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to set.
     * @param[in] native_buffer A buffer containing the long integer values to set.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_SetRegion_Long)(ani_env *env, ani_fixedarray_long array, ani_size offset, ani_size length,
                                            const ani_long *native_buffer);

    /**
     * @brief Sets a region of float values in an fixedarray.
     *
     * This function sets a portion of the specified float fixedarray using a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixedarray to set values in.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to set.
     * @param[in] native_buffer A buffer containing the float values to set.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_SetRegion_Float)(ani_env *env, ani_fixedarray_float array, ani_size offset, ani_size length,
                                             const ani_float *native_buffer);

    /**
     * @brief Sets a region of double values in an fixedarray.
     *
     * This function sets a portion of the specified double fixedarray using a native buffer.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixedarray to set values in.
     * @param[in] offset The starting offset of the region.
     * @param[in] length The number of elements to set.
     * @param[in] native_buffer A buffer containing the double values to set.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_SetRegion_Double)(ani_env *env, ani_fixedarray_double array, ani_size offset,
                                              ani_size length, const ani_double *native_buffer);

    /**
     * @brief Creates a new fixedarray of references.
     *
     * This function creates a new fixedarray of references, optionally initializing it with an initial_element ref.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] type The type of the elements of the fixedarray.
     * @param[in] length The length of the fixedarray to be created.
     * @param[in] initial_element An optional reference to initialize the fixedarray. Can be null.
     * @param[out] result A pointer to store the created fixedarray of references.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_New_Ref)(ani_env *env, ani_type type, ani_size length, ani_ref initial_element,
                                     ani_fixedarray_ref *result);

    /**
     * @brief Sets a reference at a specific index in an fixedarray.
     *
     * This function sets the value of a reference at the specified index in the fixedarray.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The array of references to modify.
     * @param[in] index The index at which to set the reference.
     * @param[in] ref The reference to set at the specified index.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_Set_Ref)(ani_env *env, ani_fixedarray_ref array, ani_size index, ani_ref ref);

    /**
     * @brief Retrieves a reference from a specific index in an fixedarray.
     *
     * This function retrieves the value of a reference at the specified index in the fixedarray.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] array The fixedarray of references to query.
     * @param[in] index The index from which to retrieve the reference.
     * @param[out] result A pointer to store the retrieved reference.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*FixedArray_Get_Ref)(ani_env *env, ani_fixedarray_ref array, ani_size index, ani_ref *result);

    /**
     * @brief Retrieves an enum item by its name.
     *
     * This function retrieves an enum item associated with the specified name.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] enm The enum to search within.
     * @param[in] name The name of the enum item to retrieve.
     * @param[out] result A pointer to store the retrieved enum item.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Enum_GetEnumItemByName)(ani_env *env, ani_enum enm, const char *name, ani_enum_item *result);

    /**
     * @brief Retrieves an enum item by its index.
     *
     * This function retrieves an enum item located at the specified index.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] enm The enum to search within.
     * @param[in] index The index of the enum item to retrieve.
     * @param[out] result A pointer to store the retrieved enum item.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Enum_GetEnumItemByIndex)(ani_env *env, ani_enum enm, ani_size index, ani_enum_item *result);

    /**
     * @brief Retrieves the enum associated with an enum item.
     *
     * This function retrieves the enum to which the specified enum item belongs.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] enum_item The enum item whose associated enum is to be retrieved.
     * @param[out] result A pointer to store the retrieved enum.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*EnumItem_GetEnum)(ani_env *env, ani_enum_item enum_item, ani_enum *result);

    /**
     * @brief Retrieves the integer value of an enum item.
     *
     * This function retrieves the integer representing the value of the specified enum item.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] enum_item The enum item whose underlying value is to be retrieved.
     * @param[out] result A pointer to store the retrieved integer.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*EnumItem_GetValue_Int)(ani_env *env, ani_enum_item enum_item, ani_int *result);

    /**
     * @brief Retrieves the string value of an enum item.
     *
     * This function retrieves the string representing the value of the specified enum item.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] enum_item The enum item whose underlying value is to be retrieved.
     * @param[out] result A pointer to store the retrieved string.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*EnumItem_GetValue_String)(ani_env *env, ani_enum_item enum_item, ani_string *result);

    /**
     * @brief Retrieves the name of an enum item.
     *
     * This function retrieves the name associated with the specified enum item.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] enum_item The enum item whose name is to be retrieved.
     * @param[out] result A pointer to store the retrieved name.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*EnumItem_GetName)(ani_env *env, ani_enum_item enum_item, ani_string *result);

    /**
     * @brief Retrieves the index of an enum item.
     *
     * This function retrieves the index of the specified enum item within its enum.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] enum_item The enum item whose index is to be retrieved.
     * @param[out] result A pointer to store the retrieved index.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*EnumItem_GetIndex)(ani_env *env, ani_enum_item enum_item, ani_size *result);

    /**
     * @brief Invokes a functional object.
     *
     * This function invokes a functional object (e.g., a function or callable object) with the specified arguments.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] fn The functional object to invoke.
     * @param[in] argc The number of arguments being passed to the functional object.
     * @param[in] argv A pointer to an array of references representing the arguments. Can be null if `argc` is 0.
     * @param[out] result A pointer to store the result of the invocation. Must be non null.
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
     * @brief Finds a field from by its name.
     *
     * This function locates a field based on its name and stores it in the result parameter.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class to query.
     * @param[in] name The name of the field to find.
     * @param[out] result A pointer to the field to be populated.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_FindField)(ani_env *env, ani_class cls, const char *name, ani_field *result);

    /**
     * @brief Finds a static field by its name.
     *
     * This function locates a static field based on its name and stores it in the result parameter.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class to query.
     * @param[in] name The name of the static field to find.
     * @param[out] result A pointer to the static field to be populated.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_FindStaticField)(ani_env *env, ani_class cls, const char *name, ani_static_field *result);

    /**
     * @brief Finds a method from by its name and signature.
     *
     * This function locates a method based on its name and signature and stores it in the result parameter.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class to query.
     * @param[in] name The name of the method to find.
     * @param[in] signature The signature of the method to find.
     * @param[out] result A pointer to the method to be populated.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_FindMethod)(ani_env *env, ani_class cls, const char *name, const char *signature,
                                   ani_method *result);

    /**
     * @brief Finds a static method from by its name and signature.
     *
     * This function locates a static method based on its name and signature and stores it in the result parameter.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class to query.
     * @param[in] name The name of the static method to find.
     * @param[in] signature The signature of the static method to find.
     * @param[out] result A pointer to the static method to be populated.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_FindStaticMethod)(ani_env *env, ani_class cls, const char *name, const char *signature,
                                         ani_static_method *result);

    /**
     * @brief Finds a setter method from by its name.
     *
     * This function locates a setter method based on its name and stores it in the result parameter.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class to query.
     * @param[in] name The name of the property whose setter is to be found.
     * @param[out] result A pointer to the method to be populated.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_FindSetter)(ani_env *env, ani_class cls, const char *name, ani_method *result);

    /**
     * @brief Finds a getter method from by its name.
     *
     * This function locates a getter method based on its name and stores it in the result parameter.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class to query.
     * @param[in] name The name of the property whose getter is to be found.
     * @param[out] result A pointer to the method to be populated.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_FindGetter)(ani_env *env, ani_class cls, const char *name, ani_method *result);

    /**
     * @brief Finds an indexable getter method from by its signature.
     *
     * This function locates an indexable getter method based on its signature and stores it in the result parameter.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class to query.
     * @param[in] signature The signature of the indexable getter to find.
     * @param[out] result A pointer to the method to be populated.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_FindIndexableGetter)(ani_env *env, ani_class cls, const char *signature, ani_method *result);

    /**
     * @brief Finds an indexable setter method from by its signature.
     *
     * This function locates an indexable setter method based on its signature and stores it in the result parameter.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class to query.
     * @param[in] signature The signature of the indexable setter to find.
     * @param[out] result A pointer to the method to be populated.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_FindIndexableSetter)(ani_env *env, ani_class cls, const char *signature, ani_method *result);

    /**
     * @brief Finds an iterator method.
     *
     * This function locates an iterator method
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class to query.
     * @param[out] result A pointer to the method to be populated.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_FindIterator)(ani_env *env, ani_class cls, ani_method *result);

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
     * @param[in] signature The signature of the static method to call.
     * @param[out] result A pointer to store the boolean result.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Boolean)(ani_env *env, ani_class cls, const char *name,
                                                       const char *signature, ani_boolean *result, ...);

    /**
     * @brief Calls a static method by name with a boolean return type (array-based).
     *
     * This function calls the specified static method of a class by its name and retrieves a boolean result using
     * arguments from an array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[in] signature The signature of the static method to call.
     * @param[out] result A pointer to store the boolean result.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Boolean_A)(ani_env *env, ani_class cls, const char *name,
                                                         const char *signature, ani_boolean *result,
                                                         const ani_value *args);

    /**
     * @brief Calls a static method by name with a boolean return type (variadic arguments).
     *
     * This function calls the specified static method of a class by its name and retrieves a boolean result using a
     * `va_list`.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[in] signature The signature of the static method to call.
     * @param[out] result A pointer to store the boolean result.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Boolean_V)(ani_env *env, ani_class cls, const char *name,
                                                         const char *signature, ani_boolean *result, va_list args);

    /**
     * @brief Calls a static method by name with a char return type.
     *
     * This function calls the specified static method of a class by its name and retrieves a char result using variadic
     * arguments.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[in] signature The signature of the static method to call.
     * @param[out] result A pointer to store the char result.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Char)(ani_env *env, ani_class cls, const char *name,
                                                    const char *signature, ani_char *result, ...);

    /**
     * @brief Calls a static method by name with a char return type (array-based).
     *
     * This function calls the specified static method of a class by its name and retrieves a char result using
     * arguments from an array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[in] signature The signature of the static method to call.
     * @param[out] result A pointer to store the char result.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Char_A)(ani_env *env, ani_class cls, const char *name,
                                                      const char *signature, ani_char *result, const ani_value *args);

    /**
     * @brief Calls a static method by name with a char return type (variadic arguments).
     *
     * This function calls the specified static method of a class by its name and retrieves a char result using a
     * `va_list`.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[in] signature The signature of the static method to call.
     * @param[out] result A pointer to store the char result.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Char_V)(ani_env *env, ani_class cls, const char *name,
                                                      const char *signature, ani_char *result, va_list args);

    /**
     * @brief Calls a static method by name with a byte return type.
     *
     * This function calls the specified static method of a class by its name and retrieves a byte result using variadic
     * arguments.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[in] signature The signature of the static method to call.
     * @param[out] result A pointer to store the byte result.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Byte)(ani_env *env, ani_class cls, const char *name,
                                                    const char *signature, ani_byte *result, ...);

    /**
     * @brief Calls a static method by name with a byte return type (array-based).
     *
     * This function calls the specified static method of a class by its name and retrieves a byte result using
     * arguments from an array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[in] signature The signature of the static method to call.
     * @param[out] result A pointer to store the byte result.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Byte_A)(ani_env *env, ani_class cls, const char *name,
                                                      const char *signature, ani_byte *result, const ani_value *args);

    /**
     * @brief Calls a static method by name with a byte return type (variadic arguments).
     *
     * This function calls the specified static method of a class by its name and retrieves a byte result using a
     * `va_list`.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[in] signature The signature of the static method to call.
     * @param[out] result A pointer to store the byte result.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Byte_V)(ani_env *env, ani_class cls, const char *name,
                                                      const char *signature, ani_byte *result, va_list args);

    /**
     * @brief Calls a static method by name with a short return type.
     *
     * This function calls the specified static method of a class by its name and retrieves a short result using
     * variadic arguments.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[in] signature The signature of the static method to call.
     * @param[out] result A pointer to store the short result.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Short)(ani_env *env, ani_class cls, const char *name,
                                                     const char *signature, ani_short *result, ...);

    /**
     * @brief Calls a static method by name with a short return type (array-based).
     *
     * This function calls the specified static method of a class by its name and retrieves a short result using
     * arguments from an array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[in] signature The signature of the static method to call.
     * @param[out] result A pointer to store the short result.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Short_A)(ani_env *env, ani_class cls, const char *name,
                                                       const char *signature, ani_short *result, const ani_value *args);

    /**
     * @brief Calls a static method by name with a short return type (variadic arguments).
     *
     * This function calls the specified static method of a class by its name and retrieves a short result using a
     * `va_list`.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[in] signature The signature of the static method to call.
     * @param[out] result A pointer to store the short result.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Short_V)(ani_env *env, ani_class cls, const char *name,
                                                       const char *signature, ani_short *result, va_list args);

    /**
     * @brief Calls a static method by name with a integer return type.
     *
     * This function calls the specified static method of a class by its name and retrieves a integer result using
     * variadic arguments.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[in] signature The signature of the static method to call.
     * @param[out] result A pointer to store the integer result.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Int)(ani_env *env, ani_class cls, const char *name, const char *signature,
                                                   ani_int *result, ...);

    /**
     * @brief Calls a static method by name with a integer return type (array-based).
     *
     * This function calls the specified static method of a class by its name and retrieves a integer result using
     * arguments from an array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[in] signature The signature of the static method to call.
     * @param[out] result A pointer to store the integer result.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Int_A)(ani_env *env, ani_class cls, const char *name,
                                                     const char *signature, ani_int *result, const ani_value *args);

    /**
     * @brief Calls a static method by name with a integer return type (variadic arguments).
     *
     * This function calls the specified static method of a class by its name and retrieves a integer result using a
     * `va_list`.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[in] signature The signature of the static method to call.
     * @param[out] result A pointer to store the integer result.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Int_V)(ani_env *env, ani_class cls, const char *name,
                                                     const char *signature, ani_int *result, va_list args);

    /**
     * @brief Calls a static method by name with a long return type.
     *
     * This function calls the specified static method of a class by its name and retrieves a long result using variadic
     * arguments.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[in] signature The signature of the static method to call.
     * @param[out] result A pointer to store the long result.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Long)(ani_env *env, ani_class cls, const char *name,
                                                    const char *signature, ani_long *result, ...);

    /**
     * @brief Calls a static method by name with a long return type (array-based).
     *
     * This function calls the specified static method of a class by its name and retrieves a long result using
     * arguments from an array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[in] signature The signature of the static method to call.
     * @param[out] result A pointer to store the long result.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Long_A)(ani_env *env, ani_class cls, const char *name,
                                                      const char *signature, ani_long *result, const ani_value *args);

    /**
     * @brief Calls a static method by name with a long return type (variadic arguments).
     *
     * This function calls the specified static method of a class by its name and retrieves a long result using a
     * `va_list`.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[in] signature The signature of the static method to call.
     * @param[out] result A pointer to store the long result.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Long_V)(ani_env *env, ani_class cls, const char *name,
                                                      const char *signature, ani_long *result, va_list args);

    /**
     * @brief Calls a static method by name with a float return type.
     *
     * This function calls the specified static method of a class by its name and retrieves a float result using
     * variadic arguments.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[in] signature The signature of the static method to call.
     * @param[out] result A pointer to store the float result.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Float)(ani_env *env, ani_class cls, const char *name,
                                                     const char *signature, ani_float *result, ...);

    /**
     * @brief Calls a static method by name with a float return type (array-based).
     *
     * This function calls the specified static method of a class by its name and retrieves a float result using
     * arguments from an array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[in] signature The signature of the static method to call.
     * @param[out] result A pointer to store the float result.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Float_A)(ani_env *env, ani_class cls, const char *name,
                                                       const char *signature, ani_float *result, const ani_value *args);

    /**
     * @brief Calls a static method by name with a float return type (variadic arguments).
     *
     * This function calls the specified static method of a class by its name and retrieves a float result using a
     * `va_list`.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[in] signature The signature of the static method to call.
     * @param[out] result A pointer to store the float result.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Float_V)(ani_env *env, ani_class cls, const char *name,
                                                       const char *signature, ani_float *result, va_list args);

    /**
     * @brief Calls a static method by name with a double return type.
     *
     * This function calls the specified static method of a class by its name and retrieves a double result using
     * variadic arguments.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[in] signature The signature of the static method to call.
     * @param[out] result A pointer to store the double result.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Double)(ani_env *env, ani_class cls, const char *name,
                                                      const char *signature, ani_double *result, ...);

    /**
     * @brief Calls a static method by name with a double return type (array-based).
     *
     * This function calls the specified static method of a class by its name and retrieves a double result using
     * arguments from an array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[in] signature The signature of the static method to call.
     * @param[out] result A pointer to store the double result.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Double_A)(ani_env *env, ani_class cls, const char *name,
                                                        const char *signature, ani_double *result,
                                                        const ani_value *args);

    /**
     * @brief Calls a static method by name with a double return type (variadic arguments).
     *
     * This function calls the specified static method of a class by its name and retrieves a double result using a
     * `va_list`.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[in] signature The signature of the static method to call.
     * @param[out] result A pointer to store the double result.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Double_V)(ani_env *env, ani_class cls, const char *name,
                                                        const char *signature, ani_double *result, va_list args);

    /**
     * @brief Calls a static method by name with a reference return type.
     *
     * This function calls the specified static method of a class by its name and retrieves a reference result using
     * variadic arguments.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[in] signature The signature of the static method to call.
     * @param[out] result A pointer to store the reference result.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Ref)(ani_env *env, ani_class cls, const char *name, const char *signature,
                                                   ani_ref *result, ...);

    /**
     * @brief Calls a static method by name with a reference return type (array-based).
     *
     * This function calls the specified static method of a class by its name and retrieves a reference result using
     * arguments from an array.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[in] signature The signature of the static method to call.
     * @param[out] result A pointer to store the reference result.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Ref_A)(ani_env *env, ani_class cls, const char *name,
                                                     const char *signature, ani_ref *result, const ani_value *args);

    /**
     * @brief Calls a static method by name with a reference return type (variadic arguments).
     *
     * This function calls the specified static method of a class by its name and retrieves a reference result using a
     * `va_list`.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[in] signature The signature of the static method to call.
     * @param[out] result A pointer to store the reference result.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Ref_V)(ani_env *env, ani_class cls, const char *name,
                                                     const char *signature, ani_ref *result, va_list args);

    /**
     * @brief Calls a static method by name with no return value.
     *
     * This function calls the specified static method of a class by its name using variadic arguments. The method does
     * not return a value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[in] signature The signature of the static method to call.
     * @param[in] ... Variadic arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Void)(ani_env *env, ani_class cls, const char *name,
                                                    const char *signature, ...);

    /**
     * @brief Calls a static method by name with no return value (array-based).
     *
     * This function calls the specified static method of a class by its name using arguments from an array. The method
     * does not return a value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[in] signature The signature of the static method to call.
     * @param[in] args An array of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Void_A)(ani_env *env, ani_class cls, const char *name,
                                                      const char *signature, const ani_value *args);

    /**
     * @brief Calls a static method by name with no return value (variadic arguments).
     *
     * This function calls the specified static method of a class by its name using a `va_list`. The method does not
     * return a value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] cls The class containing the static method.
     * @param[in] name The name of the static method to call.
     * @param[in] signature The signature of the static method to call.
     * @param[in] args A `va_list` of arguments to pass to the method.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Class_CallStaticMethodByName_Void_V)(ani_env *env, ani_class cls, const char *name,
                                                      const char *signature, va_list args);

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
     * @brief Retrieves the number of items in a tuple value.
     *
     * This function retrieves the total number of items in the specified tuple value.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] tuple_value The tuple value whose number of items is to be retrieved.
     * @param[out] result A pointer to store the number of items.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*TupleValue_GetNumberOfItems)(ani_env *env, ani_tuple_value tuple_value, ani_size *result);

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
    ani_status (*GlobalReference_Create)(ani_env *env, ani_ref ref, ani_ref *result);

    /**
     * @brief Deletes a global reference.
     *
     * This function deletes the specified global reference, releasing all associated resources.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] gref The global reference to delete.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*GlobalReference_Delete)(ani_env *env, ani_ref gref);

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
     * @param[out] was_released_result A pointer to boolean flag which indicates that wref is GC collected.
     * @param[out] ref_result A pointer to store the retrieved local reference.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*WeakReference_GetReference)(ani_env *env, ani_wref wref, ani_boolean *was_released_result,
                                             ani_ref *ref_result);

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
     * @brief Creates a new Promise.
     *
     * This function creates a new promise and a resolver to manage it.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[out] result_resolver A pointer to store the created resolver.
     * @param[out] result_promise A pointer to store the created promise.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     */
    ani_status (*Promise_New)(ani_env *env, ani_resolver *result_resolver, ani_object *result_promise);

    /**
     * @brief Resolves a promise.
     *
     * This function resolves a promise by way of the resolver with which it is associated
     * and queues promise `then` callbacks.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] resolver A resolver whose associated promise to resolve.
     * @param[in] resolution A reference with which to resolve the promise.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     * The `resolver` is freed upon successful completion.
     */
    ani_status (*PromiseResolver_Resolve)(ani_env *env, ani_resolver resolver, ani_ref resolution);

    /**
     * @brief Rejects a promise.
     *
     * This function rejects a promise by way of the resolver with which it is associated
     * and queues promise `catch` callbacks.
     *
     * @param[in] env A pointer to the environment structure.
     * @param[in] resolver A resolver whose associated promise to resolve.
     * @param[in] rejection An error with which to reject the promise.
     * @return Returns a status code of type `ani_status` indicating success or failure.
     * The `resolver` is freed upon successful completion.
     */
    ani_status (*PromiseResolver_Reject)(ani_env *env, ani_resolver resolver, ani_error rejection);
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
    ani_status AttachCurrentThread(const ani_options *options, uint32_t version, ani_env **result)
    {
        return c_api->AttachCurrentThread(this, options, version, result);
    }
    ani_status DetachCurrentThread()
    {
        return c_api->DetachCurrentThread(this);
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
    ani_status Module_FindVariable(ani_module module, const char *name, ani_variable *result)
    {
        return c_api->Module_FindVariable(this, module, name, result);
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
    ani_status Namespace_FindVariable(ani_namespace ns, const char *name, ani_variable *result)
    {
        return c_api->Namespace_FindVariable(this, ns, name, result);
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
    ani_status Array_GetLength(ani_array array, ani_size *result)
    {
        return c_api->Array_GetLength(this, array, result);
    }
    ani_status Array_New_Boolean(ani_size length, ani_array_boolean *result)
    {
        return c_api->Array_New_Boolean(this, length, result);
    }
    ani_status Array_New_Char(ani_size length, ani_array_char *result)
    {
        return c_api->Array_New_Char(this, length, result);
    }
    ani_status Array_New_Byte(ani_size length, ani_array_byte *result)
    {
        return c_api->Array_New_Byte(this, length, result);
    }
    ani_status Array_New_Short(ani_size length, ani_array_short *result)
    {
        return c_api->Array_New_Short(this, length, result);
    }
    ani_status Array_New_Int(ani_size length, ani_array_int *result)
    {
        return c_api->Array_New_Int(this, length, result);
    }
    ani_status Array_New_Long(ani_size length, ani_array_long *result)
    {
        return c_api->Array_New_Long(this, length, result);
    }
    ani_status Array_New_Float(ani_size length, ani_array_float *result)
    {
        return c_api->Array_New_Float(this, length, result);
    }
    ani_status Array_New_Double(ani_size length, ani_array_double *result)
    {
        return c_api->Array_New_Double(this, length, result);
    }
    ani_status Array_GetRegion_Boolean(ani_array_boolean array, ani_size offset, ani_size length,
                                       ani_boolean *native_buffer)
    {
        return c_api->Array_GetRegion_Boolean(this, array, offset, length, native_buffer);
    }
    ani_status Array_GetRegion_Char(ani_array_char array, ani_size offset, ani_size length, ani_char *native_buffer)
    {
        return c_api->Array_GetRegion_Char(this, array, offset, length, native_buffer);
    }
    ani_status Array_GetRegion_Byte(ani_array_byte array, ani_size offset, ani_size length, ani_byte *native_buffer)
    {
        return c_api->Array_GetRegion_Byte(this, array, offset, length, native_buffer);
    }
    ani_status Array_GetRegion_Short(ani_array_short array, ani_size offset, ani_size length, ani_short *native_buffer)
    {
        return c_api->Array_GetRegion_Short(this, array, offset, length, native_buffer);
    }
    ani_status Array_GetRegion_Int(ani_array_int array, ani_size offset, ani_size length, ani_int *native_buffer)
    {
        return c_api->Array_GetRegion_Int(this, array, offset, length, native_buffer);
    }
    ani_status Array_GetRegion_Long(ani_array_long array, ani_size offset, ani_size length, ani_long *native_buffer)
    {
        return c_api->Array_GetRegion_Long(this, array, offset, length, native_buffer);
    }
    ani_status Array_GetRegion_Float(ani_array_float array, ani_size offset, ani_size length, ani_float *native_buffer)
    {
        return c_api->Array_GetRegion_Float(this, array, offset, length, native_buffer);
    }
    ani_status Array_GetRegion_Double(ani_array_double array, ani_size offset, ani_size length,
                                      ani_double *native_buffer)
    {
        return c_api->Array_GetRegion_Double(this, array, offset, length, native_buffer);
    }
    ani_status Array_SetRegion_Boolean(ani_array_boolean array, ani_size offset, ani_size length,
                                       const ani_boolean *native_buffer)
    {
        return c_api->Array_SetRegion_Boolean(this, array, offset, length, native_buffer);
    }
    ani_status Array_SetRegion_Char(ani_array_char array, ani_size offset, ani_size length,
                                    const ani_char *native_buffer)
    {
        return c_api->Array_SetRegion_Char(this, array, offset, length, native_buffer);
    }
    ani_status Array_SetRegion_Byte(ani_array_byte array, ani_size offset, ani_size length,
                                    const ani_byte *native_buffer)
    {
        return c_api->Array_SetRegion_Byte(this, array, offset, length, native_buffer);
    }
    ani_status Array_SetRegion_Short(ani_array_short array, ani_size offset, ani_size length,
                                     const ani_short *native_buffer)
    {
        return c_api->Array_SetRegion_Short(this, array, offset, length, native_buffer);
    }
    ani_status Array_SetRegion_Int(ani_array_int array, ani_size offset, ani_size length, const ani_int *native_buffer)
    {
        return c_api->Array_SetRegion_Int(this, array, offset, length, native_buffer);
    }
    ani_status Array_SetRegion_Long(ani_array_long array, ani_size offset, ani_size length,
                                    const ani_long *native_buffer)
    {
        return c_api->Array_SetRegion_Long(this, array, offset, length, native_buffer);
    }
    ani_status Array_SetRegion_Float(ani_array_float array, ani_size offset, ani_size length,
                                     const ani_float *native_buffer)
    {
        return c_api->Array_SetRegion_Float(this, array, offset, length, native_buffer);
    }
    ani_status Array_SetRegion_Double(ani_array_double array, ani_size offset, ani_size length,
                                      const ani_double *native_buffer)
    {
        return c_api->Array_SetRegion_Double(this, array, offset, length, native_buffer);
    }
    ani_status Array_New_Ref(ani_type type, ani_size length, ani_ref initial_element, ani_array_ref *result)
    {
        return c_api->Array_New_Ref(this, type, length, initial_element, result);
    }
    ani_status Array_Set_Ref(ani_array_ref array, ani_size index, ani_ref ref)
    {
        return c_api->Array_Set_Ref(this, array, index, ref);
    }
    ani_status Array_Get_Ref(ani_array_ref array, ani_size index, ani_ref *result)
    {
        return c_api->Array_Get_Ref(this, array, index, result);
    }
    ani_status Array_New(ani_size length, ani_ref initial_element, ani_array *result)
    {
        return c_api->Array_New(this, length, initial_element, result);
    }
    ani_status Array_Set(ani_array array, ani_size index, ani_ref ref)
    {
        return c_api->Array_Set(this, array, index, ref);
    }
    ani_status Array_Get(ani_array array, ani_size index, ani_ref *result)
    {
        return c_api->Array_Get(this, array, index, result);
    }
    ani_status Array_Push(ani_array array, ani_ref ref)
    {
        return c_api->Array_Push(this, array, ref);
    }
    ani_status Array_Pop(ani_array array, ani_ref *result)
    {
        return c_api->Array_Pop(this, array, result);
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
    ani_status FixedArray_New_Ref(ani_type type, ani_size length, ani_ref initial_element, ani_fixedarray_ref *result)
    {
        return c_api->FixedArray_New_Ref(this, type, length, initial_element, result);
    }
    ani_status FixedArray_Set_Ref(ani_fixedarray_ref array, ani_size index, ani_ref ref)
    {
        return c_api->FixedArray_Set_Ref(this, array, index, ref);
    }
    ani_status FixedArray_Get_Ref(ani_fixedarray_ref array, ani_size index, ani_ref *result)
    {
        return c_api->FixedArray_Get_Ref(this, array, index, result);
    }
    ani_status Enum_GetEnumItemByName(ani_enum enm, const char *name, ani_enum_item *result)
    {
        return c_api->Enum_GetEnumItemByName(this, enm, name, result);
    }
    ani_status Enum_GetEnumItemByIndex(ani_enum enm, ani_size index, ani_enum_item *result)
    {
        return c_api->Enum_GetEnumItemByIndex(this, enm, index, result);
    }
    ani_status EnumItem_GetEnum(ani_enum_item enum_item, ani_enum *result)
    {
        return c_api->EnumItem_GetEnum(this, enum_item, result);
    }
    ani_status EnumItem_GetValue_Int(ani_enum_item enum_item, ani_int *result)
    {
        return c_api->EnumItem_GetValue_Int(this, enum_item, result);
    }
    ani_status EnumItem_GetValue_String(ani_enum_item enum_item, ani_string *result)
    {
        return c_api->EnumItem_GetValue_String(this, enum_item, result);
    }
    ani_status EnumItem_GetName(ani_enum_item enum_item, ani_string *result)
    {
        return c_api->EnumItem_GetName(this, enum_item, result);
    }
    ani_status EnumItem_GetIndex(ani_enum_item enum_item, ani_size *result)
    {
        return c_api->EnumItem_GetIndex(this, enum_item, result);
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
    ani_status Class_FindField(ani_class cls, const char *name, ani_field *result)
    {
        return c_api->Class_FindField(this, cls, name, result);
    }
    ani_status Class_FindStaticField(ani_class cls, const char *name, ani_static_field *result)
    {
        return c_api->Class_FindStaticField(this, cls, name, result);
    }
    ani_status Class_FindMethod(ani_class cls, const char *name, const char *signature, ani_method *result)
    {
        return c_api->Class_FindMethod(this, cls, name, signature, result);
    }
    ani_status Class_FindStaticMethod(ani_class cls, const char *name, const char *signature, ani_static_method *result)
    {
        return c_api->Class_FindStaticMethod(this, cls, name, signature, result);
    }
    ani_status Class_FindSetter(ani_class cls, const char *name, ani_method *result)
    {
        return c_api->Class_FindSetter(this, cls, name, result);
    }
    ani_status Class_FindGetter(ani_class cls, const char *name, ani_method *result)
    {
        return c_api->Class_FindGetter(this, cls, name, result);
    }
    ani_status Class_FindIndexableGetter(ani_class cls, const char *signature, ani_method *result)
    {
        return c_api->Class_FindIndexableGetter(this, cls, signature, result);
    }
    ani_status Class_FindIndexableSetter(ani_class cls, const char *signature, ani_method *result)
    {
        return c_api->Class_FindIndexableSetter(this, cls, signature, result);
    }
    ani_status Class_FindIterator(ani_class cls, ani_method *result)
    {
        return c_api->Class_FindIterator(this, cls, result);
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
    ani_status Class_CallStaticMethodByName_Boolean(ani_class cls, const char *name, const char *signature,
                                                    ani_boolean *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Class_CallStaticMethodByName_Boolean_V(this, cls, name, signature, result, args);
        va_end(args);
        return status;
    }
    ani_status Class_CallStaticMethodByName_Boolean_A(ani_class cls, const char *name, const char *signature,
                                                      ani_boolean *result, const ani_value *args)
    {
        return c_api->Class_CallStaticMethodByName_Boolean_A(this, cls, name, signature, result, args);
    }
    ani_status Class_CallStaticMethodByName_Boolean_V(ani_class cls, const char *name, const char *signature,
                                                      ani_boolean *result, va_list args)
    {
        return c_api->Class_CallStaticMethodByName_Boolean_V(this, cls, name, signature, result, args);
    }
    ani_status Class_CallStaticMethodByName_Char(ani_class cls, const char *name, const char *signature,
                                                 ani_char *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Class_CallStaticMethodByName_Char_V(this, cls, name, signature, result, args);
        va_end(args);
        return status;
    }
    ani_status Class_CallStaticMethodByName_Char_A(ani_class cls, const char *name, const char *signature,
                                                   ani_char *result, const ani_value *args)
    {
        return c_api->Class_CallStaticMethodByName_Char_A(this, cls, name, signature, result, args);
    }
    ani_status Class_CallStaticMethodByName_Char_V(ani_class cls, const char *name, const char *signature,
                                                   ani_char *result, va_list args)
    {
        return c_api->Class_CallStaticMethodByName_Char_V(this, cls, name, signature, result, args);
    }
    ani_status Class_CallStaticMethodByName_Byte(ani_class cls, const char *name, const char *signature,
                                                 ani_byte *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Class_CallStaticMethodByName_Byte_V(this, cls, name, signature, result, args);
        va_end(args);
        return status;
    }
    ani_status Class_CallStaticMethodByName_Byte_A(ani_class cls, const char *name, const char *signature,
                                                   ani_byte *result, const ani_value *args)
    {
        return c_api->Class_CallStaticMethodByName_Byte_A(this, cls, name, signature, result, args);
    }
    ani_status Class_CallStaticMethodByName_Byte_V(ani_class cls, const char *name, const char *signature,
                                                   ani_byte *result, va_list args)
    {
        return c_api->Class_CallStaticMethodByName_Byte_V(this, cls, name, signature, result, args);
    }
    ani_status Class_CallStaticMethodByName_Short(ani_class cls, const char *name, const char *signature,
                                                  ani_short *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Class_CallStaticMethodByName_Short_V(this, cls, name, signature, result, args);
        va_end(args);
        return status;
    }
    ani_status Class_CallStaticMethodByName_Short_A(ani_class cls, const char *name, const char *signature,
                                                    ani_short *result, const ani_value *args)
    {
        return c_api->Class_CallStaticMethodByName_Short_A(this, cls, name, signature, result, args);
    }
    ani_status Class_CallStaticMethodByName_Short_V(ani_class cls, const char *name, const char *signature,
                                                    ani_short *result, va_list args)
    {
        return c_api->Class_CallStaticMethodByName_Short_V(this, cls, name, signature, result, args);
    }
    ani_status Class_CallStaticMethodByName_Int(ani_class cls, const char *name, const char *signature, ani_int *result,
                                                ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Class_CallStaticMethodByName_Int_V(this, cls, name, signature, result, args);
        va_end(args);
        return status;
    }
    ani_status Class_CallStaticMethodByName_Int_A(ani_class cls, const char *name, const char *signature,
                                                  ani_int *result, const ani_value *args)
    {
        return c_api->Class_CallStaticMethodByName_Int_A(this, cls, name, signature, result, args);
    }
    ani_status Class_CallStaticMethodByName_Int_V(ani_class cls, const char *name, const char *signature,
                                                  ani_int *result, va_list args)
    {
        return c_api->Class_CallStaticMethodByName_Int_V(this, cls, name, signature, result, args);
    }
    ani_status Class_CallStaticMethodByName_Long(ani_class cls, const char *name, const char *signature,
                                                 ani_long *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Class_CallStaticMethodByName_Long_V(this, cls, name, signature, result, args);
        va_end(args);
        return status;
    }
    ani_status Class_CallStaticMethodByName_Long_A(ani_class cls, const char *name, const char *signature,
                                                   ani_long *result, const ani_value *args)
    {
        return c_api->Class_CallStaticMethodByName_Long_A(this, cls, name, signature, result, args);
    }
    ani_status Class_CallStaticMethodByName_Long_V(ani_class cls, const char *name, const char *signature,
                                                   ani_long *result, va_list args)
    {
        return c_api->Class_CallStaticMethodByName_Long_V(this, cls, name, signature, result, args);
    }
    ani_status Class_CallStaticMethodByName_Float(ani_class cls, const char *name, const char *signature,
                                                  ani_float *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Class_CallStaticMethodByName_Float_V(this, cls, name, signature, result, args);
        va_end(args);
        return status;
    }
    ani_status Class_CallStaticMethodByName_Float_A(ani_class cls, const char *name, const char *signature,
                                                    ani_float *result, const ani_value *args)
    {
        return c_api->Class_CallStaticMethodByName_Float_A(this, cls, name, signature, result, args);
    }
    ani_status Class_CallStaticMethodByName_Float_V(ani_class cls, const char *name, const char *signature,
                                                    ani_float *result, va_list args)
    {
        return c_api->Class_CallStaticMethodByName_Float_V(this, cls, name, signature, result, args);
    }
    ani_status Class_CallStaticMethodByName_Double(ani_class cls, const char *name, const char *signature,
                                                   ani_double *result, ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Class_CallStaticMethodByName_Double_V(this, cls, name, signature, result, args);
        va_end(args);
        return status;
    }
    ani_status Class_CallStaticMethodByName_Double_A(ani_class cls, const char *name, const char *signature,
                                                     ani_double *result, const ani_value *args)
    {
        return c_api->Class_CallStaticMethodByName_Double_A(this, cls, name, signature, result, args);
    }
    ani_status Class_CallStaticMethodByName_Double_V(ani_class cls, const char *name, const char *signature,
                                                     ani_double *result, va_list args)
    {
        return c_api->Class_CallStaticMethodByName_Double_V(this, cls, name, signature, result, args);
    }
    ani_status Class_CallStaticMethodByName_Ref(ani_class cls, const char *name, const char *signature, ani_ref *result,
                                                ...)
    {
        va_list args;
        va_start(args, result);
        ani_status status = c_api->Class_CallStaticMethodByName_Ref_V(this, cls, name, signature, result, args);
        va_end(args);
        return status;
    }
    ani_status Class_CallStaticMethodByName_Ref_A(ani_class cls, const char *name, const char *signature,
                                                  ani_ref *result, const ani_value *args)
    {
        return c_api->Class_CallStaticMethodByName_Ref_A(this, cls, name, signature, result, args);
    }
    ani_status Class_CallStaticMethodByName_Ref_V(ani_class cls, const char *name, const char *signature,
                                                  ani_ref *result, va_list args)
    {
        return c_api->Class_CallStaticMethodByName_Ref_V(this, cls, name, signature, result, args);
    }
    ani_status Class_CallStaticMethodByName_Void(ani_class cls, const char *name, const char *signature, ...)
    {
        va_list args;
        va_start(args, signature);
        ani_status status = c_api->Class_CallStaticMethodByName_Void_V(this, cls, name, signature, args);
        va_end(args);
        return status;
    }
    ani_status Class_CallStaticMethodByName_Void_A(ani_class cls, const char *name, const char *signature,
                                                   const ani_value *args)
    {
        return c_api->Class_CallStaticMethodByName_Void_A(this, cls, name, signature, args);
    }
    ani_status Class_CallStaticMethodByName_Void_V(ani_class cls, const char *name, const char *signature, va_list args)
    {
        return c_api->Class_CallStaticMethodByName_Void_V(this, cls, name, signature, args);
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
    ani_status TupleValue_GetNumberOfItems(ani_tuple_value tuple_value, ani_size *result)
    {
        return c_api->TupleValue_GetNumberOfItems(this, tuple_value, result);
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
    ani_status GlobalReference_Create(ani_ref ref, ani_ref *result)
    {
        return c_api->GlobalReference_Create(this, ref, result);
    }
    ani_status GlobalReference_Delete(ani_ref ref)
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
    ani_status WeakReference_GetReference(ani_wref wref, ani_boolean *was_released_result, ani_ref *ref_result)
    {
        return c_api->WeakReference_GetReference(this, wref, was_released_result, ref_result);
    }
    ani_status CreateArrayBuffer(size_t length, void **data_result, ani_arraybuffer *arraybuffer_result)
    {
        return c_api->CreateArrayBuffer(this, length, data_result, arraybuffer_result);
    }
    ani_status ArrayBuffer_GetInfo(ani_arraybuffer arraybuffer, void **data_result, size_t *length_result)
    {
        return c_api->ArrayBuffer_GetInfo(this, arraybuffer, data_result, length_result);
    }
    ani_status Promise_New(ani_resolver *result_resolver, ani_object *result_promise)
    {
        return c_api->Promise_New(this, result_resolver, result_promise);
    }
    ani_status PromiseResolver_Resolve(ani_resolver resolver, ani_ref resolution)
    {
        return c_api->PromiseResolver_Resolve(this, resolver, resolution);
    }
    ani_status PromiseResolver_Reject(ani_resolver resolver, ani_error rejection)
    {
        return c_api->PromiseResolver_Reject(this, resolver, rejection);
    }
#endif  // __cplusplus
};

// NOLINTEND
#endif  // __ANI_H__
