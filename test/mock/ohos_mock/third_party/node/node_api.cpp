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

#include "node_api.h"
// Mock implementations for napi functions - outside namespace for C compatibility
napi_status napi_typeof(napi_env env, napi_value value, napi_valuetype* result)
{
    if (result) {
        *result = napi_undefined;
    }
    return napi_ok;
}

napi_status napi_get_value_string_utf8(napi_env env, napi_value value, char* buf, size_t bufsize, size_t* result)
{
    if (result) {
        *result = 0;
    }
    if (buf && bufsize > 0) {
        buf[0] = '\0';
    }
    return napi_ok;
}

napi_status napi_get_value_int32(napi_env env, napi_value value, int32_t* result)
{
    if (result) {
        *result = 0;
    }
    return napi_ok;
}

napi_status napi_get_named_property(napi_env env, napi_value object, const char* utf8name, napi_value* result)
{
    if (result) {
        *result = nullptr;
    }
    return napi_ok;
}

napi_status napi_set_named_property(napi_env env, napi_value object, const char* utf8name, napi_value value)
{
    return napi_ok;
}

napi_status napi_create_string_utf8(napi_env env, const char* str, size_t length, napi_value* result)
{
    if (result) {
        *result = nullptr;
    }
    return napi_ok;
}

napi_status napi_create_object(napi_env env, napi_value* result)
{
    if (result) {
        *result = nullptr;
    }
    return napi_ok;
}

napi_status napi_create_number(napi_env env, double value, napi_value* result)
{
    if (result) {
        *result = nullptr;
    }
    return napi_ok;
}

napi_status napi_create_int32(napi_env env, int32_t value, napi_value* result)
{
    if (result) {
        *result = nullptr;
    }
    return napi_ok;
}

napi_status napi_create_uint32(napi_env env, uint32_t value, napi_value* result)
{
    if (result) {
        *result = nullptr;
    }
    return napi_ok;
}

napi_status napi_get_undefined(napi_env env, napi_value* result)
{
    if (result) {
        *result = nullptr;
    }
    return napi_ok;
}

napi_status napi_get_null(napi_env env, napi_value* result)
{
    if (result) {
        *result = nullptr;
    }
    return napi_ok;
}

napi_status napi_get_boolean(napi_env env, bool value, napi_value* result)
{
    if (result) {
        *result = nullptr;
    }
    return napi_ok;
}

napi_status napi_coerce_to_bool(napi_env env, napi_value value, napi_value* result)
{
    if (result) {
        *result = nullptr;
    }
    return napi_ok;
}

napi_status napi_coerce_to_number(napi_env env, napi_value value, napi_value* result)
{
    if (result) {
        *result = nullptr;
    }
    return napi_ok;
}

napi_status napi_coerce_to_string(napi_env env, napi_value value, napi_value* result)
{
    if (result) {
        *result = nullptr;
    }
    return napi_ok;
}

napi_status napi_coerce_to_object(napi_env env, napi_value value, napi_value* result)
{
    if (result) {
        *result = nullptr;
    }
    return napi_ok;
}

napi_status napi_strict_equals(napi_env env, napi_value lhs, napi_value rhs, bool* result)
{
    if (result) {
        *result = false;
    }
    return napi_ok;
}

napi_status napi_get_property(napi_env env, napi_value object, napi_value key, napi_value* result)
{
    if (result) {
        *result = nullptr;
    }
    return napi_ok;
}

napi_status napi_set_property(napi_env env, napi_value object, napi_value key, napi_value value)
{
    return napi_ok;
}

napi_status napi_has_property(napi_env env, napi_value object, napi_value key, bool* result)
{
    if (result) {
        *result = false;
    }
    return napi_ok;
}

napi_status napi_get_prototype(napi_env env, napi_value object, napi_value* result)
{
    if (result) {
        *result = nullptr;
    }
    return napi_ok;
}

napi_status napi_is_array(napi_env env, napi_value value, bool* result)
{
    if (result) {
        *result = false;
    }
    return napi_ok;
}

napi_status napi_get_array_length(napi_env env, napi_value value, uint32_t* result)
{
    if (result) {
        *result = 0;
    }
    return napi_ok;
}

napi_status napi_create_array_with_length(napi_env env, size_t length, napi_value* result)
{
    if (result) {
        *result = nullptr;
    }
    return napi_ok;
}

napi_status napi_create_array(napi_env env, napi_value* result)
{
    if (result) {
        *result = nullptr;
    }
    return napi_ok;
}

napi_status napi_get_element(napi_env env, napi_value object, uint32_t index, napi_value* result)
{
    if (result) {
        *result = nullptr;
    }
    return napi_ok;
}

napi_status napi_set_element(napi_env env, napi_value object, uint32_t index, napi_value value)
{
    return napi_ok;
}

napi_status napi_has_element(napi_env env, napi_value object, uint32_t index, bool* result)
{
    if (result) {
        *result = false;
    }
    return napi_ok;
}

napi_status napi_delete_element(napi_env env, napi_value object, uint32_t index, bool* result)
{
    if (result) {
        *result = false;
    }
    return napi_ok;
}

napi_status napi_is_error(napi_env env, napi_value value, bool* result)
{
    if (result) {
        *result = false;
    }
    return napi_ok;
}

napi_status napi_throw(napi_env env, napi_value error)
{
    return napi_ok;
}

napi_status napi_throw_error(napi_env env, const char* code, const char* msg)
{
    return napi_ok;
}

napi_status napi_create_error(napi_env env, napi_value code, napi_value msg, napi_value* result)
{
    if (result) {
        *result = nullptr;
    }
    return napi_ok;
}

napi_status napi_create_type_error(napi_env env, napi_value code, napi_value msg, napi_value* result)
{
    if (result) {
        *result = nullptr;
    }
    return napi_ok;
}

napi_status napi_create_range_error(napi_env env, napi_value code, napi_value msg, napi_value* result)
{
    if (result) {
        *result = nullptr;
    }
    return napi_ok;
}

napi_status napi_get_and_clear_last_exception(napi_env env, napi_value* result)
{
    if (result) {
        *result = nullptr;
    }
    return napi_ok;
}

napi_status napi_is_exception_pending(napi_env env, bool* result)
{
    if (result) {
        *result = false;
    }
    return napi_ok;
}

napi_status napi_create_reference(napi_env env, napi_value value, uint32_t initial_refcount, napi_ref* result)
{
    if (result) {
        *result = nullptr;
    }
    return napi_ok;
}

napi_status napi_delete_reference(napi_env env, napi_ref ref)
{
    return napi_ok;
}

napi_status napi_reference_ref(napi_env env, napi_ref ref, uint32_t* result)
{
    if (result) {
        *result = 0;
    }
    return napi_ok;
}

napi_status napi_reference_unref(napi_env env, napi_ref ref, uint32_t* result)
{
    if (result) {
        *result = 0;
    }
    return napi_ok;
}

napi_status napi_get_reference_value(napi_env env, napi_ref ref, napi_value* result)
{
    if (result) {
        *result = nullptr;
    }
    return napi_ok;
}

napi_status napi_open_handle_scope(napi_env env, napi_handle_scope* result)
{
    if (result) {
        *result = nullptr;
    }
    return napi_ok;
}

napi_status napi_close_handle_scope(napi_env env, napi_handle_scope scope)
{
    return napi_ok;
}

napi_status napi_open_escapable_handle_scope(napi_env env, napi_escapable_handle_scope* result)
{
    if (result) {
        *result = nullptr;
    }
    return napi_ok;
}

napi_status napi_close_escapable_handle_scope(napi_env env, napi_escapable_handle_scope scope)
{
    return napi_ok;
}

napi_status napi_escape_handle(napi_env env, napi_escapable_handle_scope scope, napi_value escapee, napi_value* result)
{
    if (result) {
        *result = nullptr;
    }
    return napi_ok;
}

napi_status napi_wrap(napi_env env, napi_value js_object, void* native_object, napi_finalize finalize_cb,
    void* finalize_hint, napi_ref* result)
{
    if (result) {
        *result = nullptr;
    }
    return napi_ok;
}

napi_status napi_unwrap(napi_env env, napi_value js_object, void** result)
{
    if (result) {
        *result = nullptr;
    }
    return napi_ok;
}

napi_status napi_remove_wrap(napi_env env, napi_value js_object, void** result)
{
    if (result) {
        *result = nullptr;
    }
    return napi_ok;
}

napi_status napi_create_external(
    napi_env env, void* data, napi_finalize finalize_cb, void* finalize_hint, napi_value* result)
{
    if (result) {
        *result = nullptr;
    }
    return napi_ok;
}

napi_status napi_get_value_external(napi_env env, napi_value value, void** result)
{
    if (result) {
        *result = nullptr;
    }
    return napi_ok;
}

napi_status napi_is_arraybuffer(napi_env env, napi_value value, bool* result)
{
    if (result) {
        *result = false;
    }
    return napi_ok;
}

napi_status napi_create_arraybuffer(napi_env env, size_t byte_length, void** data, napi_value* result)
{
    if (data) {
        *data = nullptr;
    }
    if (result) {
        *result = nullptr;
    }
    return napi_ok;
}

napi_status napi_get_arraybuffer_info(napi_env env, napi_value arraybuffer, void** data, size_t* byte_length)
{
    if (data) {
        *data = nullptr;
    }
    if (byte_length) {
        *byte_length = 0;
    }
    return napi_ok;
}

napi_status napi_create_typedarray(napi_env env, napi_typedarray_type type, size_t length, napi_value arraybuffer,
    size_t byte_offset, napi_value* result)
{
    if (result) {
        *result = nullptr;
    }
    return napi_ok;
}

napi_status napi_is_typedarray(napi_env env, napi_value value, bool* result)
{
    if (result) {
        *result = false;
    }
    return napi_ok;
}

napi_status napi_get_typedarray_info(napi_env env, napi_value typedarray, napi_typedarray_type* type, size_t* length,
    void** data, napi_value* arraybuffer, size_t* byte_offset)
{
    if (type) {
        *type = napi_int8_array;
    }
    if (length) {
        *length = 0;
    }
    if (data) {
        *data = nullptr;
    }
    if (arraybuffer) {
        *arraybuffer = nullptr;
    }
    if (byte_offset) {
        *byte_offset = 0;
    }
    return napi_ok;
}
