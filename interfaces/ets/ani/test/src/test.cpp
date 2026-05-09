/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include <ani.h>
#include <chrono>
#include <cstdint>
#include "frameworks/base/log/log_wrapper.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace {
const char ANI_TEST_NS[] = "@ohos.arkui.Test.ETSGLOBAL";
}

namespace OHOS::Ace {
//utils
bool CheckIsUndefined(ani_env* env, ani_object obj)
{
    ani_boolean isUndefined;
    if (ANI_OK != env->Reference_IsUndefined(obj, &isUndefined)) {
        return true;
    }
    return static_cast<bool>(isUndefined);
}

bool GetEnumByName(ani_env* env, ani_object obj, const std::string& name, int32_t& value)
{
    ani_ref aniValueRef;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(obj, name.c_str(), &aniValueRef)) {
        return false;
    }
    if (CheckIsUndefined(env, static_cast<ani_object>(aniValueRef))) {
        return false;
    }
    ani_int aniValue;
    if (ANI_OK != env->EnumItem_GetValue_Int(static_cast<ani_enum_item>(aniValueRef), &aniValue)) {
        return false;
    }
    value = static_cast<int32_t>(aniValue);
    return true;
}

bool GetIntByName(ani_env* env, ani_object obj, const std::string& name, int32_t& value)
{
    ani_int aniValue;
    if (ANI_OK != env->Object_GetPropertyByName_Int(obj, name.c_str(), &aniValue)) {
        return false;
    }
    value = static_cast<int32_t>(aniValue);
    return true;
}

bool GetFloatByName(ani_env* env, ani_object obj, const std::string& name, float& value)
{
    ani_double valueDouble;
    if (ANI_OK != env->Object_GetPropertyByName_Double(obj, name.c_str(), &valueDouble)) {
        return false;
    }
    value = static_cast<float>(valueDouble);
    return true;
}

bool GetLongByName(ani_env* env, ani_object obj, const std::string& name, int64_t& value)
{
    ani_long aniValue;
    if (ANI_OK != env->Object_GetPropertyByName_Long(obj, name.c_str(), &aniValue)) {
        return false;
    }
    value = static_cast<int64_t>(aniValue);
    return true;
}

//parse param
KeyEvent GetKeyEvent(ani_env* env, ani_object obj)
{
    CHECK_NULL_RETURN(env, KeyEvent());
    int32_t action;
    int32_t code;
    if (!GetEnumByName(env, obj, "type", action)) {
        return KeyEvent();
    }
    if (!GetIntByName(env, obj, "keyCode", code)) {
        return KeyEvent();
    }
    KeyEvent keyEvent(static_cast<KeyCode>(code), static_cast<KeyAction>(action));
    int32_t keySource;
    if (GetEnumByName(env, obj, "keySource", keySource)) {
        keyEvent.sourceType = static_cast<SourceType>(keySource);
    }
    int32_t deviceId;
    if (GetIntByName(env, obj, "deviceId", deviceId)) {
        keyEvent.deviceId = deviceId;
    }
    GetIntByName(env, obj, "metaKey", keyEvent.metaKey);
    int64_t timestamp;
    if (GetLongByName(env, obj, "timestamp", timestamp)) {
        keyEvent.SetTimeStamp(timestamp);
    }
    ani_ref aniValueRef;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(obj, "unicode", &aniValueRef)) {
        return keyEvent;
    }
    ani_object aniValueObject = static_cast<ani_object>(aniValueRef);
    if (CheckIsUndefined(env, aniValueObject)) {
        return keyEvent;
    }
    ani_long aniValue;
    if (ANI_OK == env->Object_CallMethodByName_Long(aniValueObject, "toLong", nullptr, &aniValue)) {
        keyEvent.unicode = static_cast<int64_t>(aniValue);
    }
    return keyEvent;
}

TouchEvent GetTouchEvent(ani_env* env, ani_object obj)
{
    TouchEvent touchEvent;
    CHECK_NULL_RETURN(env, touchEvent);
    int32_t type;
    if (GetEnumByName(env, obj, "type", type)) {
        touchEvent.type = static_cast<TouchType>(type);
    }
    GetIntByName(env, obj, "id", touchEvent.id);
    GetFloatByName(env, obj, "x", touchEvent.x);
    GetFloatByName(env, obj, "y", touchEvent.y);
    touchEvent.time = std::chrono::high_resolution_clock::now();
    return touchEvent;
}

MouseEvent GetMouseEvent(ani_env* env, ani_object obj)
{
    MouseEvent mouseEvent;
    int32_t button;
    if (GetEnumByName(env, obj, "button", button)) {
        mouseEvent.button = static_cast<MouseButton>(button);
    }

    int32_t action;
    if (GetEnumByName(env, obj, "action", action)) {
        mouseEvent.action = static_cast<MouseAction>(action);
    }

    if (GetFloatByName(env, obj, "x", mouseEvent.x)) {
        mouseEvent.deltaX = mouseEvent.x;
    }

    if (GetFloatByName(env, obj, "y", mouseEvent.y)) {
        mouseEvent.deltaY = mouseEvent.y;
    }
    mouseEvent.time = std::chrono::high_resolution_clock::now();
    mouseEvent.sourceType = SourceType::MOUSE;
    return mouseEvent;
}

//interface
static ani_boolean ANI_SendTouchEvent(ani_env* env, ani_object obj)
{
    if (CheckIsUndefined(env, obj)) {
        return ANI_FALSE;
    }
    auto pipelineContext = NG::PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipelineContext, ANI_FALSE);
    auto taskExecutor = pipelineContext->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, ANI_FALSE);
    auto event = GetTouchEvent(env, obj);
    auto result = taskExecutor->PostTask(
        [pipelineContext, event]() { pipelineContext->OnTouchEvent(event); },
        TaskExecutor::TaskType::UI, "ArkUIAniSendTouchEvent");
    return static_cast<ani_boolean>(result);
}

static ani_boolean ANI_SendKeyEvent(ani_env* env, ani_object obj)
{
    if (CheckIsUndefined(env, obj)) {
        return ANI_FALSE;
    }
    auto pipelineContext = NG::PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipelineContext, ANI_FALSE);
    auto taskExecutor = pipelineContext->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, ANI_FALSE);
    auto event = GetKeyEvent(env, obj);
    auto result = taskExecutor->PostTask(
        [pipelineContext, event]() { pipelineContext->OnNonPointerEvent(event); },
        TaskExecutor::TaskType::UI, "ArkUIAniSendKeyEvent");
    return static_cast<ani_boolean>(result);
}

static ani_boolean ANI_SendMouseEvent(ani_env* env, ani_object obj)
{
    if (CheckIsUndefined(env, obj)) {
        return ANI_FALSE;
    }
    auto pipelineContext = NG::PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipelineContext, ANI_FALSE);
    auto taskExecutor = pipelineContext->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, ANI_FALSE);
    auto event = GetMouseEvent(env, obj);
    auto result = taskExecutor->PostTask(
        [pipelineContext, event]() { pipelineContext->OnMouseEvent(event); },
        TaskExecutor::TaskType::UI, "ArkUIAniSendMouseEvent");
    return static_cast<ani_boolean>(result);
}

} // namespace OHOS::Ace

ANI_EXPORT ani_status ANI_Constructor(ani_vm* vm, uint32_t* result)
{
    ani_env* env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        return ANI_ERROR;
    }
    ani_namespace ns;
    if (ANI_OK != env->FindNamespace(ANI_TEST_NS, &ns)) {
        return ANI_ERROR;
    }

    std::array methods = {
        ani_native_function { "sendTouchEvent", nullptr, reinterpret_cast<void*>(OHOS::Ace::ANI_SendTouchEvent) },
        ani_native_function { "sendKeyEvent", nullptr, reinterpret_cast<void*>(OHOS::Ace::ANI_SendKeyEvent) },
        ani_native_function { "sendMouseEvent", nullptr, reinterpret_cast<void*>(OHOS::Ace::ANI_SendMouseEvent) },
    };
    if (ANI_OK != env->Namespace_BindNativeFunctions(ns, methods.data(), methods.size())) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_GESTURE, "ANI BindNativeFunctions failed!");
        return ANI_ERROR;
    }
    *result = ANI_VERSION_1;
    return ANI_OK;
}