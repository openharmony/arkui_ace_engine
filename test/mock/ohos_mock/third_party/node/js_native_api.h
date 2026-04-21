/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MOCK_OHOS_THIRD_PARTY_NODE_JS_NATIVE_API_H
#define MOCK_OHOS_THIRD_PARTY_NODE_JS_NATIVE_API_H

#include <cstdint>
#include <cstring>

// Minimal napi types for ace_kit_test
enum napi_status {
    napi_ok = 0,
    napi_invalid_arg = 1,
    napi_object_expected = 2,
    napi_string_expected = 3,
    napi_name_expected = 4,
    napi_function_expected = 5,
    napi_number_expected = 6,
    napi_boolean_expected = 7,
    napi_array_expected = 8,
    napi_generic_failure = 9,
    napi_pending_exception = 10,
    napi_cancelled = 11,
    napi_escape_called_twice = 12,
    napi_escape_not_empty = 13,
};

enum napi_valuetype {
    napi_undefined = 0,
    napi_null = 1,
    napi_boolean = 2,
    napi_number = 3,
    napi_string = 4,
    napi_symbol = 5,
    napi_object = 6,
    napi_function = 7,
    napi_external = 8,
};

struct napi_env__;
typedef struct napi_env__* napi_env;

struct napi_value__;
typedef struct napi_value__* napi_value;

struct napi_ref__;
typedef struct napi_ref__* napi_ref;

struct napi_handle_scope__;
typedef struct napi_handle_scope__* napi_handle_scope;

struct napi_escapable_handle_scope__;
typedef struct napi_escapable_handle_scope__* napi_escapable_handle_scope;

typedef void (*napi_finalize)(void* data, void* hint);

enum napi_typedarray_type {
    napi_int8_array = 0,
    napi_uint8_array = 1,
    napi_uint8_clamped_array = 2,
    napi_int16_array = 3,
    napi_uint16_array = 4,
    napi_int32_array = 5,
    napi_uint32_array = 6,
    napi_float32_array = 7,
    napi_float64_array = 8,
    napi_bigint64_array = 9,
};

// napi functions used by ace_kit_test
#ifdef __cplusplus
extern "C" {
#endif
napi_status napi_typeof(napi_env env, napi_value value, napi_valuetype* result);
napi_status napi_get_value_string_utf8(napi_env env, napi_value value, char* buf, size_t bufsize, size_t* result);
napi_status napi_get_value_int32(napi_env env, napi_value value, int32_t* result);
napi_status napi_get_named_property(napi_env env, napi_value object, const char* utf8name, napi_value* result);
napi_status napi_set_named_property(napi_env env, napi_value object, const char* utf8name, napi_value value);
napi_status napi_create_string_utf8(napi_env env, const char* str, size_t length, napi_value* result);
napi_status napi_create_object(napi_env env, napi_value* result);
napi_status napi_create_number(napi_env env, double value, napi_value* result);
napi_status napi_create_int32(napi_env env, int32_t value, napi_value* result);
napi_status napi_create_uint32(napi_env env, uint32_t value, napi_value* result);
napi_status napi_get_undefined(napi_env env, napi_value* result);
napi_status napi_get_null(napi_env env, napi_value* result);
napi_status napi_get_boolean(napi_env env, bool value, napi_value* result);
napi_status napi_coerce_to_bool(napi_env env, napi_value value, napi_value* result);
napi_status napi_coerce_to_number(napi_env env, napi_value value, napi_value* result);
napi_status napi_coerce_to_string(napi_env env, napi_value value, napi_value* result);
napi_status napi_coerce_to_object(napi_env env, napi_value value, napi_value* result);
napi_status napi_strict_equals(napi_env env, napi_value lhs, napi_value rhs, bool* result);
napi_status napi_get_property(napi_env env, napi_value object, napi_value key, napi_value* result);
napi_status napi_set_property(napi_env env, napi_value object, napi_value key, napi_value value);
napi_status napi_has_property(napi_env env, napi_value object, napi_value key, bool* result);
napi_status napi_get_prototype(napi_env env, napi_value object, napi_value* result);
napi_status napi_is_array(napi_env env, napi_value value, bool* result);
napi_status napi_get_array_length(napi_env env, napi_value value, uint32_t* result);
napi_status napi_create_array_with_length(napi_env env, size_t length, napi_value* result);
napi_status napi_create_array(napi_env env, napi_value* result);
napi_status napi_get_element(napi_env env, napi_value object, uint32_t index, napi_value* result);
napi_status napi_set_element(napi_env env, napi_value object, uint32_t index, napi_value value);
napi_status napi_has_element(napi_env env, napi_value object, uint32_t index, bool* result);
napi_status napi_delete_element(napi_env env, napi_value object, uint32_t index, bool* result);
napi_status napi_is_error(napi_env env, napi_value value, bool* result);
napi_status napi_throw(napi_env env, napi_value error);
napi_status napi_throw_error(napi_env env, const char* code, const char* msg);
napi_status napi_create_error(napi_env env, napi_value code, napi_value msg, napi_value* result);
napi_status napi_create_type_error(napi_env env, napi_value code, napi_value msg, napi_value* result);
napi_status napi_create_range_error(napi_env env, napi_value code, napi_value msg, napi_value* result);
napi_status napi_get_and_clear_last_exception(napi_env env, napi_value* result);
napi_status napi_is_exception_pending(napi_env env, bool* result);
napi_status napi_create_reference(napi_env env, napi_value value, uint32_t initial_refcount, napi_ref* result);
napi_status napi_delete_reference(napi_env env, napi_ref ref);
napi_status napi_reference_ref(napi_env env, napi_ref ref, uint32_t* result);
napi_status napi_reference_unref(napi_env env, napi_ref ref, uint32_t* result);
napi_status napi_get_reference_value(napi_env env, napi_ref ref, napi_value* result);
napi_status napi_open_handle_scope(napi_env env, napi_handle_scope* result);
napi_status napi_close_handle_scope(napi_env env, napi_handle_scope scope);
napi_status napi_open_escapable_handle_scope(napi_env env, napi_escapable_handle_scope* result);
napi_status napi_close_escapable_handle_scope(napi_env env, napi_escapable_handle_scope scope);
napi_status napi_escape_handle(napi_env env, napi_escapable_handle_scope scope, napi_value escapee, napi_value* result);
napi_status napi_wrap(napi_env env, napi_value js_object, void* native_object, napi_finalize finalize_cb,
    void* finalize_hint, napi_ref* result);
napi_status napi_unwrap(napi_env env, napi_value js_object, void** result);
napi_status napi_remove_wrap(napi_env env, napi_value js_object, void** result);
napi_status napi_create_external(
    napi_env env, void* data, napi_finalize finalize_cb, void* finalize_hint, napi_value* result);
napi_status napi_get_value_external(napi_env env, napi_value value, void** result);
napi_status napi_is_arraybuffer(napi_env env, napi_value value, bool* result);
napi_status napi_create_arraybuffer(napi_env env, size_t byte_length, void** data, napi_value* result);
napi_status napi_get_arraybuffer_info(napi_env env, napi_value arraybuffer, void** data, size_t* byte_length);
napi_status napi_create_typedarray(napi_env env, napi_typedarray_type type, size_t length, napi_value arraybuffer,
    size_t byte_offset, napi_value* result);
napi_status napi_is_typedarray(napi_env env, napi_value value, bool* result);
napi_status napi_get_typedarray_info(napi_env env, napi_value typedarray, napi_typedarray_type* type, size_t* length,
    void** data, napi_value* arraybuffer, size_t* byte_offset);
#ifdef __cplusplus
}
#endif

#endif // MOCK_OHOS_THIRD_PARTY_NODE_JS_NATIVE_API_H
