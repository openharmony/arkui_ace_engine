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

#include "interfaces/napi/kits/application_shortcut/js_application_shortcut.h"

#include "base/log/log_wrapper.h"
#include "core/common/ace_application_info.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/common/frontend.h"

namespace OHOS::Ace::Napi {
namespace {
constexpr size_t ARGC_REGISTER = 3;
constexpr size_t ARGC_UNREGISTER = 2;
constexpr size_t ARG_INDEX_ZERO = 0;
constexpr size_t ARG_INDEX_ONE = 1;
constexpr size_t ARG_INDEX_TWO = 2;
constexpr size_t STR_BUFFER_SIZE = 1024;
constexpr const char* PROPERTY_UICONTEXT = "uiContext";
constexpr const char* CALLBACK_TAG = "ArkUIAppShortcut";
} // namespace

ApplicationShortcutCallback::ApplicationShortcutCallback(napi_env env, napi_value callback)
    : env_(env), callback_(nullptr)
{
    if (env != nullptr && callback != nullptr) {
        napi_create_reference(env, callback, 1, &callback_);
    }
}

ApplicationShortcutCallback::~ApplicationShortcutCallback()
{
    if (callback_ != nullptr && env_ != nullptr) {
        napi_delete_reference(env_, callback_);
        callback_ = nullptr;
    }
}

bool ApplicationShortcutCallback::NapiEqual(napi_env env, napi_value cb)
{
    CHECK_NULL_RETURN(callback_, false);
    CHECK_NULL_RETURN(cb, false);
    napi_value stored = nullptr;
    napi_get_reference_value(env_, callback_, &stored);
    if (stored == nullptr) {
        return false;
    }
    bool isEqual = false;
    napi_strict_equals(env, cb, stored, &isEqual);
    return isEqual;
}

void ApplicationShortcutCallback::Execute(int32_t triggerInstanceId)
{
    // UI thread and JS thread are the same in declarative frontends
    // (ace_container.cpp sets jsRunner_ = uiRunner_ via InitJsThread(false)),
    // so Execute() is already on the trigger instance's JS thread when invoked
    // from KeyEventManager::DispatchKeyboardShortcut. We only need to switch
    // the thread-local container scope so Container::CurrentSafely() returns
    // the trigger instance and GetContextValue() yields its UIContext.
    ContainerScope scope(triggerInstanceId);
    ExecuteInner(triggerInstanceId);
}

void ApplicationShortcutCallback::ExecuteInner(int32_t triggerInstanceId)
{
    CHECK_NULL_VOID(callback_);
    CHECK_NULL_VOID(env_);

    napi_handle_scope scope = nullptr;
    napi_open_handle_scope(env_, &scope);

    // 1) Obtain trigger instance UIContext JS object (mirrors UIObserver::GetContextValue)
    napi_value uiContext = nullptr;
    auto container = Container::CurrentSafely();
    if (container != nullptr) {
        auto frontend = container->GetFrontend();
        if (frontend != nullptr) {
            uiContext = frontend->GetContextValue();
        }
    }

    // 2) Build ApplicationShortcutCallbackInfo = { uiContext }
    napi_value infoObj = nullptr;
    napi_create_object(env_, &infoObj);
    if (uiContext != nullptr) {
        napi_set_named_property(env_, infoObj, PROPERTY_UICONTEXT, uiContext);
    } else {
        napi_value undefined = nullptr;
        napi_get_undefined(env_, &undefined);
        napi_set_named_property(env_, infoObj, PROPERTY_UICONTEXT, undefined);
    }

    // 3) Invoke JS callback
    napi_value undefined = nullptr;
    napi_get_undefined(env_, &undefined);
    napi_value callback = nullptr;
    napi_get_reference_value(env_, callback_, &callback);
    if (callback == nullptr) {
        napi_close_handle_scope(env_, scope);
        return;
    }
    napi_value result = nullptr;
    (void)napi_call_function(env_, undefined, callback, 1, &infoObj, &result);

    bool hasPending = false;
    napi_is_exception_pending(env_, &hasPending);
    if (hasPending) {
        napi_value exception = nullptr;
        napi_get_and_clear_last_exception(env_, &exception);
        LOGW("%{public}s: JS callback threw an exception", CALLBACK_TAG);
    }

    napi_close_handle_scope(env_, scope);
}

static bool ParseShortcutValue(napi_env env, napi_value arg, std::string& outValue)
{
    CHECK_NULL_RETURN(arg, false);
    napi_valuetype type = napi_undefined;
    napi_typeof(env, arg, &type);
    if (type != napi_string) {
        return false;
    }
    char buffer[STR_BUFFER_SIZE] = { 0 };
    size_t outSize = 0;
    napi_get_value_string_utf8(env, arg, buffer, STR_BUFFER_SIZE, &outSize);
    outValue.assign(buffer, outSize);
    return true;
}

// ModifierKey values are defined as a bitmask directly: CTRL=1, SHIFT=2, ALT=4.
// The JS-side array is OR-combined to form the final modifier bitmask.
static bool ParseModifierKeys(napi_env env, napi_value arg, uint8_t& outKeys)
{
    CHECK_NULL_RETURN(arg, false);
    napi_valuetype type = napi_undefined;
    napi_typeof(env, arg, &type);
    if (type != napi_object) {
        return false;
    }
    bool isArray = false;
    napi_is_array(env, arg, &isArray);
    if (!isArray) {
        return false;
    }
    uint32_t length = 0;
    napi_get_array_length(env, arg, &length);
    uint8_t keys = 0;
    for (uint32_t i = 0; i < length; ++i) {
        napi_value element = nullptr;
        napi_get_element(env, arg, i, &element);
        CHECK_NULL_RETURN(element, false);
        napi_valuetype elementType = napi_undefined;
        napi_typeof(env, element, &elementType);
        if (elementType != napi_number) {
            return false;
        }
        int32_t value = 0;
        napi_get_value_int32(env, element, &value);
        keys |= static_cast<uint8_t>(value);
    }
    outKeys = keys;
    return true;
}

static napi_value JSRegisterApplicationShortcut(napi_env env, napi_callback_info info)
{
    size_t argc = ARGC_REGISTER;
    napi_value argv[ARGC_REGISTER] = { nullptr };
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, argv, &thisVar, &data);
    if (argc != ARGC_REGISTER) {
        NapiThrow(env, "registerApplicationShortcut requires 3 parameters.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }

    std::string value;
    if (!ParseShortcutValue(env, argv[ARG_INDEX_ZERO], value)) {
        NapiThrow(env, "The first parameter must be a string.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }

    uint8_t keys = 0;
    if (!ParseModifierKeys(env, argv[ARG_INDEX_ONE], keys)) {
        NapiThrow(env, "The second parameter must be an array of ModifierKey.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }

    napi_valuetype callbackType = napi_undefined;
    napi_typeof(env, argv[ARG_INDEX_TWO], &callbackType);
    if (callbackType != napi_function) {
        NapiThrow(env, "The third parameter must be a function.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }

    auto callback = std::make_shared<ApplicationShortcutCallback>(env, argv[ARG_INDEX_TWO]);
    AceApplicationInfo::GetInstance().RegisterApplicationShortcut(
        value, keys, [callback](int32_t triggerInstanceId) { callback->Execute(triggerInstanceId); });

    napi_value result = nullptr;
    napi_get_undefined(env, &result);
    return result;
}

static napi_value JSUnregisterApplicationShortcut(napi_env env, napi_callback_info info)
{
    size_t argc = ARGC_UNREGISTER;
    napi_value argv[ARGC_UNREGISTER] = { nullptr };
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, argv, &thisVar, &data);
    if (argc != ARGC_UNREGISTER) {
        NapiThrow(env, "unregisterApplicationShortcut requires 2 parameters.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }

    std::string value;
    if (!ParseShortcutValue(env, argv[ARG_INDEX_ZERO], value)) {
        NapiThrow(env, "The first parameter must be a string.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }

    uint8_t keys = 0;
    if (!ParseModifierKeys(env, argv[ARG_INDEX_ONE], keys)) {
        NapiThrow(env, "The second parameter must be an array of ModifierKey.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }

    AceApplicationInfo::GetInstance().UnregisterApplicationShortcut(value, keys);

    napi_value result = nullptr;
    napi_get_undefined(env, &result);
    return result;
}

static napi_value registerFunc(napi_env env, napi_value exports)
{
    napi_property_descriptor desc[] = {
        DECLARE_NAPI_FUNCTION("registerApplicationShortcut", JSRegisterApplicationShortcut),
        DECLARE_NAPI_FUNCTION("unregisterApplicationShortcut", JSUnregisterApplicationShortcut),
    };
    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));
    return exports;
}

static napi_module applicationShortcutModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = registerFunc,
    .nm_modname = "arkui.applicationShortcut",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void ApplicationShortcutRegister()
{
    napi_module_register(&applicationShortcutModule);
}
} // namespace OHOS::Ace::Napi
