/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <optional>

#include "interfaces/napi/kits/utils/napi_utils.h"
#include "js_native_api.h"
#include "js_native_api_types.h"
#include "napi/native_common.h"
#include "native_engine/impl/ark/ark_native_engine.h"
#include "native_value.h"
#include "node_api.h"

#if defined(ENABLE_DRAG_FRAMEWORK) && defined(PIXEL_MAP_SUPPORTED)
#include "jsnapi.h"
#include "pixel_map.h"
#include "pixel_map_napi.h"

#include "base/log/log_wrapper.h"
#include "base/memory/referenced.h"
#include "base/msdp/device_status/interfaces/innerkits/interaction/include/interaction_manager.h"
#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/engine/functions/js_drag_function.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.h"
#include "bridge/js_frontend/engine/jsi/ark_js_runtime.h"
#include "core/common/ace_engine.h"
#include "core/common/udmf/udmf_client.h"
#include "core/event/ace_events.h"
#include "core/gestures/gesture_info.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#endif

namespace OHOS::Ace::Napi {
#if defined(ENABLE_DRAG_FRAMEWORK) && defined(PIXEL_MAP_SUPPORTED)
namespace {
constexpr float PIXELMAP_WIDTH_RATE = -0.5f;
constexpr float PIXELMAP_HEIGHT_RATE = -0.2f;

constexpr int32_t argCount2 = 2;
constexpr int32_t argCount3 = 3;

using DragNotifyMsg = Msdp::DeviceStatus::DragNotifyMsg;
using OnDragCallback = std::function<void(const DragNotifyMsg&)>;
using StopDragCallback = std::function<void()>;
using PixelMapNapiEntry = void* (*)(void*, void*);

enum class DragState { PENDING, SENDING, REJECT, SUCCESS };

// the context of drag controller
struct DragControllerAsyncCtx {
    napi_env env = nullptr;
    size_t argc = 3;
    napi_value argv[3] { nullptr };
    napi_ref callbackRef = nullptr;
    napi_deferred deferred = nullptr;
    std::shared_ptr<Media::PixelMap> pixmap = nullptr;
    napi_value customBuilder;
    int32_t pointerId = -1;
    RefPtr<OHOS::Ace::UnifiedData> unifiedData;
    std::string extraParams;
    int32_t instanceId = -1;
    int32_t errCode = -1;
    std::mutex mutex;
    bool hasHandle = false;
    int32_t globalX = -1;
    int32_t globalY = -1;
    int32_t sourceType = 0;
    std::mutex dragStateMutex;
    DragState dragState = DragState::PENDING;
};
} // namespace

napi_value CreateCallbackErrorValue(napi_env env, int32_t errCode)
{
    napi_value jsObject = nullptr;
    napi_value jsValue = nullptr;
    NAPI_CALL(env, napi_create_int32(env, errCode, &jsValue));
    NAPI_CALL(env, napi_create_object(env, &jsObject));
    NAPI_CALL(env, napi_set_named_property(env, jsObject, "code", jsValue));
    return jsObject;
}

void HandleSuccess(DragControllerAsyncCtx* asyncCtx, const DragNotifyMsg& dragNotifyMsg)
{
    if (!asyncCtx) {
        LOGE("DragControllerAsyncContext is null");
        return;
    }
    bool hasHandle = false;
    {
        std::lock_guard<std::mutex> lock(asyncCtx->mutex);
        hasHandle = asyncCtx->hasHandle;
        asyncCtx->hasHandle = true;
    }
    if (hasHandle) {
        return;
    }
    auto container = AceEngine::Get().GetContainer(asyncCtx->instanceId);
    if (!container) {
        LOGW("container is null. %{public}d", asyncCtx->instanceId);
        return;
    }
    auto taskExecutor = container->GetTaskExecutor();
    if (!taskExecutor) {
        LOGW("taskExecutor is null.");
        return;
    }
    taskExecutor->PostSyncTask(
        [asyncCtx, dragNotifyMsg]() {
            // callback result format: {DragEvent, ExtraParams}
            if (!asyncCtx) {
                LOGE("DragControllerAsyncContext is null");
                return;
            }
            napi_value result[2] = { nullptr };
            napi_get_undefined(asyncCtx->env, &result[1]);
            auto resultCode = dragNotifyMsg.result;
            LOGI("resultCode = %{public}d", static_cast<int32_t>(resultCode));
            // do success thing
            napi_create_object(asyncCtx->env, &result[1]);
            napi_value eventNapi = nullptr;
            napi_value globalObj = nullptr;
            napi_value customDragEvent = nullptr;
            napi_create_object(asyncCtx->env, &customDragEvent);
            napi_get_global(asyncCtx->env, &globalObj);
            if (!globalObj) {
                LOGE("globalObj is null");
                return;
            }
            napi_get_named_property(asyncCtx->env, globalObj, "DragEvent", &customDragEvent);
            if (!customDragEvent) {
                LOGE("customDragEvent is null");
                return;
            }
            napi_status status = napi_new_instance(asyncCtx->env, customDragEvent, 0, nullptr, &eventNapi);
            if (status != napi_ok) {
                LOGE("status = %{public}d", status);
                return;
            }
            auto localRef = NapiValueToLocalValue(eventNapi);
            if (localRef->IsNull()) {
                LOGE("localRef is null");
                return;
            }
            auto* jsDragEvent =
                static_cast<Framework::JsDragEvent*>(Local<panda::ObjectRef>(localRef)->GetNativePointerField(0));
            if (!jsDragEvent) {
                LOGE("jsDragEvent is null");
                return;
            }
            auto dragEvent = AceType::MakeRefPtr<DragEvent>();
            if (!dragEvent) {
                LOGE("dragEvent is null");
                return;
            }
            dragEvent->SetResult(static_cast<DragRet>(resultCode));
            jsDragEvent->SetDragEvent(dragEvent);
            status = napi_set_named_property(asyncCtx->env, result[1], "event", eventNapi);

            napi_value extraParamsNapi = nullptr;
            napi_create_string_utf8(
                asyncCtx->env, asyncCtx->extraParams.c_str(), asyncCtx->extraParams.length(), &extraParamsNapi);
            napi_set_named_property(asyncCtx->env, result[1], "extraParams", extraParamsNapi);
            if (asyncCtx->callbackRef) {
                napi_value ret = nullptr;
                napi_value napiCallback = nullptr;
                napi_get_reference_value(asyncCtx->env, asyncCtx->callbackRef, &napiCallback);
                result[0] = CreateCallbackErrorValue(asyncCtx->env, 0);
                napi_call_function(asyncCtx->env, nullptr, napiCallback, argCount2, result, &ret);
                napi_delete_reference(asyncCtx->env, asyncCtx->callbackRef);
            } else {
                napi_resolve_deferred(asyncCtx->env, asyncCtx->deferred, result[1]);
            }
        },
        TaskExecutor::TaskType::JS);
}

void HandleFail(DragControllerAsyncCtx* asyncCtx, int32_t errorCode)
{
    if (!asyncCtx) {
        LOGE("DragControllerAsyncContext is null");
        return;
    }
    bool hasHandle = false;
    {
        std::lock_guard<std::mutex> lock(asyncCtx->mutex);
        hasHandle = asyncCtx->hasHandle;
        asyncCtx->hasHandle = true;
    }
    if (hasHandle) {
        return;
    }
    napi_value result[2] = { nullptr };
    result[0] = CreateCallbackErrorValue(asyncCtx->env, errorCode);
    if (asyncCtx->callbackRef) {
        napi_value ret = nullptr;
        napi_value napiCallback = nullptr;
        napi_get_reference_value(asyncCtx->env, asyncCtx->callbackRef, &napiCallback);
        napi_create_object(asyncCtx->env, &result[1]);
        napi_call_function(asyncCtx->env, nullptr, napiCallback, argCount2, result, &ret);
        napi_delete_reference(asyncCtx->env, asyncCtx->callbackRef);
    } else {
        napi_reject_deferred(asyncCtx->env, asyncCtx->deferred, result[0]);
    }
}

void OnComplete(DragControllerAsyncCtx* asyncCtx)
{
    auto container = AceEngine::Get().GetContainer(asyncCtx->instanceId);
    if (!container) {
        LOGW("container is null. %{public}d", asyncCtx->instanceId);
        return;
    }
    auto taskExecutor = container->GetTaskExecutor();
    if (!taskExecutor) {
        LOGW("taskExecutor is null.");
        return;
    }
    taskExecutor->PostTask(
        [asyncCtx]() {
            if (!asyncCtx) {
                LOGE("DragControllerAsyncContext is null");
                return;
            }
            DragState dragState = DragState::PENDING;
            {
                std::lock_guard<std::mutex> lock(asyncCtx->dragStateMutex);
                if (asyncCtx->dragState == DragState::PENDING) {
                    asyncCtx->dragState = DragState::SENDING;
                }
                dragState = asyncCtx->dragState;
            }
            if (dragState == DragState::REJECT) {
                napi_handle_scope scope = nullptr;
                napi_open_handle_scope(asyncCtx->env, &scope);
                HandleFail(asyncCtx, -1);
                napi_close_handle_scope(asyncCtx->env, scope);
                return;
            }
            if (!asyncCtx->pixmap) {
                LOGE("The pixmap is null");
                return;
            }
            int32_t dataSize = 1;
            auto pointerId = asyncCtx->pointerId;
            std::string udKey;
            if (asyncCtx->unifiedData) {
                int32_t ret = UdmfClient::GetInstance()->SetData(asyncCtx->unifiedData, udKey);
                if (ret != 0) {
                    LOGW("Udmf set data fail, error code is %{public}d", ret);
                }
                dataSize = static_cast<int32_t>(asyncCtx->unifiedData->GetSize());
            }
            int32_t width = asyncCtx->pixmap->GetWidth();
            int32_t height = asyncCtx->pixmap->GetHeight();

            Msdp::DeviceStatus::DragData dragData {
                { asyncCtx->pixmap, width * PIXELMAP_WIDTH_RATE, height * PIXELMAP_HEIGHT_RATE }, {}, udKey, "", "",
                asyncCtx->sourceType, dataSize, pointerId, asyncCtx->globalX, asyncCtx->globalY, 0, true
            };

            OnDragCallback callback = [asyncCtx](const DragNotifyMsg& dragNotifyMsg) {
                napi_handle_scope scope = nullptr;
                napi_open_handle_scope(asyncCtx->env, &scope);
                HandleSuccess(asyncCtx, dragNotifyMsg);
                napi_close_handle_scope(asyncCtx->env, scope);
            };

            int32_t ret = Msdp::DeviceStatus::InteractionManager::GetInstance()->StartDrag(dragData, callback);
            if (ret != 0) {
                LOGE("drag start error");
                napi_handle_scope scope = nullptr;
                napi_open_handle_scope(asyncCtx->env, &scope);
                HandleFail(asyncCtx, ret);
                napi_close_handle_scope(asyncCtx->env, scope);
                return;
            }
            LOGI("drag start success");
            {
                std::lock_guard<std::mutex> lock(asyncCtx->dragStateMutex);
                if (asyncCtx->dragState == DragState::SENDING) {
                    asyncCtx->dragState = DragState::SUCCESS;
                    Msdp::DeviceStatus::InteractionManager::GetInstance()->SetDragWindowVisible(true);
                }
            }
        },
        TaskExecutor::TaskType::JS);
}

bool ParseDragItemInfoParam(DragControllerAsyncCtx* asyncCtx, std::string& errMsg)
{
    if (!asyncCtx) {
        LOGE("DragControllerAsyncContext is null");
        errMsg = "DragControllerAsyncContext is null";
        return false;
    }
    napi_valuetype valueType = napi_undefined;
    napi_typeof(asyncCtx->env, asyncCtx->argv[0], &valueType);
    if (valueType == napi_function) {
        asyncCtx->customBuilder = asyncCtx->argv[0];
        return true;
    }

    if (valueType != napi_object) {
        errMsg = "The type of first parameter is incorrect.";
        return false;
    }
    // Parse the DragItemInfo
    napi_value pixelMapValue;
    napi_get_named_property(asyncCtx->env, asyncCtx->argv[0], "pixelMap", &pixelMapValue);
    PixelMapNapiEntry pixelMapNapiEntry = Framework::JsEngine::GetPixelMapNapiEntry();
    if (pixelMapNapiEntry == nullptr) {
        LOGW("Failed to parse pixelMap from the first argument.");
    } else {
        void* pixmapPtrAddr = pixelMapNapiEntry(asyncCtx->env, pixelMapValue);
        if (pixmapPtrAddr == nullptr) {
            LOGW("The pixelMap parsed from the first argument is null");
        } else {
            asyncCtx->pixmap = *(reinterpret_cast<std::shared_ptr<Media::PixelMap>*>(pixmapPtrAddr));
        }
    }

    napi_get_named_property(asyncCtx->env, asyncCtx->argv[0], "builder", &(asyncCtx->customBuilder));
    napi_typeof(asyncCtx->env, asyncCtx->customBuilder, &valueType);
    if (valueType != napi_function) {
        errMsg = "The type of customBuilder of the first parameter is incorrect.";
        return false;
    }

    napi_value extraInfoValue;
    napi_get_named_property(asyncCtx->env, asyncCtx->argv[0], "extraInfo", &extraInfoValue);
    napi_typeof(asyncCtx->env, extraInfoValue, &valueType);
    if (valueType != napi_string) {
        errMsg = "The type of extraInfo of the first parameter is incorrect.";
        return false;
    }
    GetNapiString(asyncCtx->env, extraInfoValue, asyncCtx->extraParams, valueType);
    return true;
}

bool ParseDragInfoParam(DragControllerAsyncCtx* asyncCtx, std::string& errMsg)
{
    if (!asyncCtx) {
        LOGE("DragControllerAsyncContext is null");
        errMsg = "DragControllerAsyncContext is null";
        return false;
    }
    napi_valuetype valueType = napi_undefined;
    napi_typeof(asyncCtx->env, asyncCtx->argv[1], &valueType);
    if (valueType != napi_object) {
        errMsg = "The type of second parameter is incorrect.";
        return false;
    }
    napi_value pointerIdNApi = nullptr;
    napi_status status = napi_ok;
    napi_get_named_property(asyncCtx->env, asyncCtx->argv[1], "pointerId", &pointerIdNApi);
    napi_typeof(asyncCtx->env, pointerIdNApi, &valueType);
    if (valueType != napi_number) {
        errMsg = "pointerId which type is number must be given";
        return false;
    }
    status = napi_get_value_int32(asyncCtx->env, pointerIdNApi, &asyncCtx->pointerId);
    if (status != napi_ok) {
        errMsg = "parse pointerId fail";
        return false;
    }

    napi_value dataNApi = nullptr;
    napi_get_named_property(asyncCtx->env, asyncCtx->argv[1], "data", &dataNApi);
    napi_typeof(asyncCtx->env, dataNApi, &valueType);
    if (valueType == napi_object) {
        asyncCtx->unifiedData = UdmfClient::GetInstance()->TransformUnifiedData(dataNApi);
    } else if (valueType != napi_undefined) {
        errMsg = "data's type is wrong";
        return false;
    }

    napi_value extraParamsNApi = nullptr;
    napi_get_named_property(asyncCtx->env, asyncCtx->argv[1], "extraParams", &extraParamsNApi);
    napi_typeof(asyncCtx->env, extraParamsNApi, &valueType);
    if (valueType == napi_string) {
        GetNapiString(asyncCtx->env, extraParamsNApi, asyncCtx->extraParams, valueType);
    } else if (valueType != napi_undefined) {
        errMsg = "extraParams's type is wrong";
        return false;
    }
    return true;
}

bool CheckAndParseParams(DragControllerAsyncCtx* asyncCtx, std::string& errMsg)
{
    // Check the number of the argument
    if (!asyncCtx) {
        LOGE("DragControllerAsyncContext is null");
        errMsg = "DragControllerAsyncContext is null";
        return false;
    }
    if ((asyncCtx->argc != argCount2) && (asyncCtx->argc != argCount3)) {
        errMsg = "The number of parameters must be 2 or 3.";
        return false;
    }

    // Check and parse the first parameter
    if (!ParseDragItemInfoParam(asyncCtx, errMsg)) {
        return false;
    }

    // Check and parse the second parameter
    return ParseDragInfoParam(asyncCtx, errMsg);
}

void CreateCallback(DragControllerAsyncCtx* asyncCtx, napi_value* result)
{
    if (!asyncCtx) {
        LOGE("DragControllerAsyncContext is null");
        return;
    }
    if (asyncCtx->argc == argCount3) {
        // Create the JsCallback
        napi_create_reference(asyncCtx->env, asyncCtx->argv[2], 1, &asyncCtx->callbackRef);
    }
    if (!asyncCtx->callbackRef) {
        // Create the promise
        napi_create_promise(asyncCtx->env, &asyncCtx->deferred, result);
    } else {
        napi_get_undefined(asyncCtx->env, result);
    }
}

void InitializeDragControllerCtx(napi_env env, napi_callback_info info, DragControllerAsyncCtx* asyncCtx)
{
    if (!asyncCtx) {
        LOGE("DragControllerAsyncContext is null");
        return;
    }
    napi_value thisVar = nullptr;
    void* data = nullptr;
    asyncCtx->instanceId = Container::CurrentId();
    asyncCtx->env = env;
    // get arguments from JS
    napi_get_cb_info(asyncCtx->env, info, &(asyncCtx->argc), asyncCtx->argv, &thisVar, &data);
}

static napi_value JSExecuteDrag(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);

    auto* asyncCtx = new DragControllerAsyncCtx();
    InitializeDragControllerCtx(env, info, asyncCtx);

    std::string errMsg;
    if (!CheckAndParseParams(asyncCtx, errMsg)) {
        NapiThrow(asyncCtx->env, errMsg, Framework::ERROR_CODE_INTERNAL_ERROR);
        return nullptr;
    }

    napi_value result = nullptr;
    CreateCallback(asyncCtx, &result);
    auto container = AceEngine::Get().GetContainer(asyncCtx->instanceId);
    if (!container) {
        NapiThrow(asyncCtx->env, "container is null", Framework::ERROR_CODE_INTERNAL_ERROR);
        return nullptr;
    }
    StopDragCallback stopDragCallback = [asyncCtx, container]() {
        if (!asyncCtx) {
            LOGE("DragControllerAsyncContext is null");
            return;
        }
        if (!container) {
            LOGE("container is null");
            return;
        }
        bool needPostStopDrag = false;
        {
            std::lock_guard<std::mutex> lock(asyncCtx->dragStateMutex);
            needPostStopDrag = (asyncCtx->dragState == DragState::SENDING);
            asyncCtx->dragState = DragState::REJECT;
        }
        if (needPostStopDrag) {
            auto taskExecutor = container->GetTaskExecutor();
            if (!taskExecutor) {
                LOGE("taskExecutor is null.");
                return;
            }
            auto windowId = container->GetWindowId();
            taskExecutor->PostTask(
                [asyncCtx, windowId]() {
                    if (!asyncCtx) {
                        LOGE("DragControllerAsyncContext is null");
                        return;
                    }
                    napi_handle_scope scope = nullptr;
                    napi_open_handle_scope(asyncCtx->env, &scope);
                    HandleFail(asyncCtx, -1);
                    napi_close_handle_scope(asyncCtx->env, scope);
                    if (SystemProperties::GetDebugEnabled()) {
                        LOGI("JSExecuteDrag, windowId is %{public}d.", windowId);
                    }
                    Msdp::DeviceStatus::DragDropResult dropResult {
                        Msdp::DeviceStatus::DragResult::DRAG_CANCEL, false, windowId };
                    Msdp::DeviceStatus::InteractionManager::GetInstance()->StopDrag(dropResult);
                    Msdp::DeviceStatus::InteractionManager::GetInstance()->SetDragWindowVisible(false);
                },
                TaskExecutor::TaskType::JS);
        }
    };
    auto getPointSuccess = container->GetCurPointerEventInfo(
        asyncCtx->pointerId, asyncCtx->globalX, asyncCtx->globalY, asyncCtx->sourceType, std::move(stopDragCallback));
    if (!getPointSuccess) {
        HandleFail(asyncCtx, -1);
        napi_escape_handle(env, scope, result, &result);
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }

    if (asyncCtx && asyncCtx->pixmap != nullptr) {
        OnComplete(asyncCtx);
    } else {
        auto delegate = EngineHelper::GetCurrentDelegate();
        if (!delegate) {
            NapiThrow(env, "ace engine delegate is null", Framework::ERROR_CODE_INTERNAL_ERROR);
            napi_close_escapable_handle_scope(env, scope);
            return nullptr;
        }
        auto callback = [asyncCtx](std::shared_ptr<Media::PixelMap> pixmap, int32_t errCode, std::function<void()>) {
            if (!asyncCtx) {
                LOGE("DragControllerAsyncContext is null");
                return;
            }
            asyncCtx->pixmap = std::move(pixmap);
            asyncCtx->errCode = errCode;
            OnComplete(asyncCtx);
        };
        auto builder = [build = asyncCtx->customBuilder, env] {
            napi_call_function(env, nullptr, build, 0, nullptr, nullptr);
        };
        delegate->CreateSnapshot(builder, callback, false);
    }

    napi_escape_handle(env, scope, result, &result);
    napi_close_escapable_handle_scope(env, scope);
    return result;
}
#else
static napi_value JSExecuteDrag(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);
    NapiThrow(env, "The current environment does not enable drag framework or does not support pixmap.",
        Framework::ERROR_CODE_INTERNAL_ERROR);
    napi_close_escapable_handle_scope(env, scope);
    return nullptr;
}
#endif

static napi_value DragControllerExport(napi_env env, napi_value exports)
{
    napi_property_descriptor dragControllerDesc[] = {
        DECLARE_NAPI_FUNCTION("executeDrag", JSExecuteDrag),
    };
    NAPI_CALL(env, napi_define_properties(
                       env, exports, sizeof(dragControllerDesc) / sizeof(dragControllerDesc[0]), dragControllerDesc));
    return exports;
}

static napi_module dragControllerModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = DragControllerExport,
    .nm_modname = "arkui.dragController",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void DragControllerRegister()
{
    napi_module_register(&dragControllerModule);
}
} // namespace OHOS::Ace::Napi
