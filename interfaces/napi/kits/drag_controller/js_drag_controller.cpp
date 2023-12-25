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

#include "adapter/ohos/capability/interaction/start_drag_listener_impl.h"
#include "base/log/log_wrapper.h"
#include "base/memory/referenced.h"
#include "base/msdp/device_status/interfaces/innerkits/interaction/include/interaction_manager.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/engine/functions/js_drag_function.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.h"
#include "bridge/js_frontend/engine/jsi/ark_js_runtime.h"
#include "core/common/ace_engine.h"
#include "core/common/container_scope.h"
#include "core/common/udmf/udmf_client.h"
#include "core/event/ace_events.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "drag_preview.h"
#endif
namespace OHOS::Ace::Napi {
class DragAction;
#if defined(ENABLE_DRAG_FRAMEWORK) && defined(PIXEL_MAP_SUPPORTED)
namespace {
constexpr float PIXELMAP_WIDTH_RATE = -0.5f;
constexpr float PIXELMAP_HEIGHT_RATE = -0.2f;
constexpr size_t STR_BUFFER_SIZE = 1024;

constexpr int32_t argCount3 = 3;

using DragNotifyMsg = Msdp::DeviceStatus::DragNotifyMsg;
using DragRet = OHOS::Ace::DragRet;
using OnDragCallback = std::function<void(const DragNotifyMsg&)>;
using StopDragCallback = std::function<void()>;
using PixelMapNapiEntry = void* (*)(void*, void*);

enum class DragState { PENDING, SENDING, REJECT, SUCCESS };
enum class DragStatus { STARTED, ENDED };
enum class ParameterType { CUSTOMBUILDER, DRAGITEMINFO, DRAGITEMINFO_ARRAY, MIX, ERROR };

// the context of drag controller
struct DragControllerAsyncCtx {
    napi_env env = nullptr;
    size_t argc = 3;
    napi_value argv[3] { nullptr };
    napi_ref callbackRef = nullptr;
    napi_deferred deferred = nullptr;
    std::shared_ptr<Media::PixelMap> pixelMap = nullptr;
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMapList;
    bool isArray = false;
    napi_value customBuilder;
    std::vector<napi_ref> customBuilderList;
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
    int parseBuilderCount = 0;
    std::mutex dragStateMutex;
    DragState dragState = DragState::PENDING;
    DimensionOffset touchPoint = DimensionOffset(0.0_vp, 0.0_vp);
    bool hasTouchPoint = false;
    DragAction *dragAction = nullptr;
    ~DragControllerAsyncCtx();
};
} // namespace

void OnMultipleComplete(DragControllerAsyncCtx* asyncCtx);
void OnComplete(DragControllerAsyncCtx* asyncCtx);
bool GetPixelMapByCustom(DragControllerAsyncCtx* asyncCtx);
bool GetPixelMapArrayByCustom(DragControllerAsyncCtx* asyncCtx, napi_value customBuilder, int arrayLength);
ParameterType getParameterType(DragControllerAsyncCtx* asyncCtx);

class DragAction {
public:
    DragAction(DragControllerAsyncCtx* asyncCtx) : asyncCtx_(asyncCtx) {}
    ~DragAction()
    {
        CHECK_NULL_VOID(env_);
        for (auto& item : cbList_) {
            napi_delete_reference(env_, item);
        }
    }

    void OnNapiCallback(napi_value resultArg, const DragStatus dragStatus)
    {
        for (auto& cbRef : cbList_) {
            napi_value cb = nullptr;
            napi_get_reference_value(env_, cbRef, &cb);
            napi_call_function(env_, nullptr, cb, 1, &resultArg, nullptr);
        }
    }

    void NapiSerializer(napi_env& env, napi_value& result)
    {
        napi_wrap(
            env, result, this,
            [](napi_env env, void* data, void* hint) {
                DragAction* dragAction = static_cast<DragAction*>(data);
                if (dragAction != nullptr) {
                    if (dragAction->asyncCtx_ != nullptr) {
                        delete dragAction->asyncCtx_->dragAction;
                        dragAction->asyncCtx_->dragAction = nullptr;
                    }
                    dragAction->DeleteRef();
                    delete dragAction;
                }
            },
            nullptr, nullptr);

        /* insert callback functions */
        const char* funName = "on";
        napi_value funcValue = nullptr;
        napi_create_function(env, funName, NAPI_AUTO_LENGTH, On, nullptr, &funcValue);
        napi_set_named_property(env, result, funName, funcValue);

        funName = "off";
        napi_create_function(env, funName, NAPI_AUTO_LENGTH, Off, nullptr, &funcValue);
        napi_set_named_property(env, result, funName, funcValue);

        funName = "startDrag";
        napi_create_function(env, funName, NAPI_AUTO_LENGTH, StartDrag, nullptr, &funcValue);
        napi_set_named_property(env, result, funName, funcValue);
    }

    void DeleteRef()
    {
        CHECK_NULL_VOID(asyncCtx_);
        for (auto customBuilderValue : asyncCtx_->customBuilderList) {
            if (customBuilderValue == nullptr) {
                continue;
            }
            napi_delete_reference(asyncCtx_->env, customBuilderValue);
        }
        delete asyncCtx_;
        asyncCtx_ = nullptr;
    }

    static napi_value On(napi_env env, napi_callback_info info)
    {
        LOGI("NAPI DragAction On called");
        auto jsEngine = EngineHelper::GetCurrentEngine();
        CHECK_NULL_RETURN(jsEngine, nullptr);

        napi_handle_scope scope = nullptr;
        napi_open_handle_scope(env, &scope);
        CHECK_NULL_RETURN(scope, nullptr);
        napi_value thisVar = nullptr;
        napi_value cb = nullptr;
        size_t argc = ParseArgs(env, info, thisVar, cb);
        NAPI_ASSERT(env, (argc == 2 && thisVar != nullptr && cb != nullptr), "Invalid arguments");
        napi_valuetype valueType = napi_undefined;
        napi_typeof(env, cb, &valueType);
        if (valueType != napi_function) {
            NapiThrow(env, "Check param failed", Framework::ERROR_CODE_PARAM_INVALID);
            return nullptr;
        }
        DragAction* dragAction = ConvertDragAction(env, thisVar);
        if (!dragAction) {
            napi_close_handle_scope(env, scope);
            return nullptr;
        }
        auto iter = dragAction->FindCbList(cb);
        if (iter != dragAction->cbList_.end()) {
            napi_close_handle_scope(env, scope);
            return nullptr;
        }
        napi_ref ref = nullptr;
        napi_create_reference(env, cb, 1, &ref);
        dragAction->cbList_.emplace_back(ref);
        napi_close_handle_scope(env, scope);
        return nullptr;
    }

    static napi_value Off(napi_env env, napi_callback_info info)
    {
        LOGI("NAPI DragAction off called");
        napi_value thisVar = nullptr;
        napi_value cb = nullptr;
        size_t argc = ParseArgs(env, info, thisVar, cb);
        DragAction* dragAction = ConvertDragAction(env, thisVar);
        CHECK_NULL_RETURN(dragAction, nullptr);
        if (argc == 1) {
            for (const auto& item : dragAction->cbList_) {
                napi_delete_reference(dragAction->env_, item);
            }
            dragAction->cbList_.clear();
        } else {
            NAPI_ASSERT(env, (argc == 2 && dragAction != nullptr && cb != nullptr), "Invalid arguments");
            napi_valuetype valueType = napi_undefined;
            napi_typeof(env, cb, &valueType);
            if (valueType != napi_function) {
                NapiThrow(env, "Check param failed", Framework::ERROR_CODE_PARAM_INVALID);
                return nullptr;
            }
            auto iter = dragAction->FindCbList(cb);
            if (iter != dragAction->cbList_.end()) {
                napi_delete_reference(dragAction->env_, *iter);
                dragAction->cbList_.erase(iter);
            }
        }
        return nullptr;
    }

    static napi_value StartDrag(napi_env env, napi_callback_info info)
    {
        LOGI("NAPI DragAction StartDrag called");
        auto jsEngine = EngineHelper::GetCurrentEngine();
        CHECK_NULL_RETURN(jsEngine, nullptr);

        napi_escapable_handle_scope scope = nullptr;
        napi_open_escapable_handle_scope(env, &scope);
        CHECK_NULL_RETURN(scope, nullptr);
        napi_value thisVar = nullptr;
        napi_value cb = nullptr;
        size_t argc = ParseArgs(env, info, thisVar, cb);
        NAPI_ASSERT(env, (argc == 0 && thisVar != nullptr), "Invalid arguments");
        DragAction* dragAction = ConvertDragAction(env, thisVar);
        if (!dragAction) {
            napi_close_escapable_handle_scope(env, scope);
            return nullptr;
        }
        if (dragAction->asyncCtx_ == nullptr) {
            NapiThrow(env, "dragaction must be recreated for each dragging", Framework::ERROR_CODE_INTERNAL_ERROR);
            return nullptr;
        }
        napi_value promiseResult = nullptr;
        napi_status status = napi_create_promise(env, &dragAction->asyncCtx_->deferred, &promiseResult);
        if (status != napi_ok) {
            NapiThrow(env, "ace engine delegate is null", Framework::ERROR_CODE_INTERNAL_ERROR);
            napi_close_escapable_handle_scope(env, scope);
            return nullptr;
        }

        dragAction->StartDragInternal(dragAction->asyncCtx_);
        napi_escape_handle(env, scope, promiseResult, &promiseResult);
        napi_close_escapable_handle_scope(env, scope);
        return promiseResult;
    }

    std::list<napi_ref>::iterator FindCbList(napi_value cb)
    {
        return std::find_if(cbList_.begin(), cbList_.end(), [env = env_, cb](const napi_ref& item) -> bool {
            bool result = false;
            napi_value refItem;
            napi_get_reference_value(env, item, &refItem);
            napi_strict_equals(env, refItem, cb, &result);
            return result;
        });
    }

private:
    void Initialize(napi_env env, napi_value thisVar)
    {
        env_ = env;
    }

    static size_t ParseArgs(napi_env& env, napi_callback_info& info, napi_value& thisVar, napi_value& cb)
    {
        size_t argc = 2;
        napi_value argv[argCount2] = { 0 };
        void* data = nullptr;
        napi_get_cb_info(env, info, &argc, argv, &thisVar, &data);
        if (argc == 0) {
            return argc;
        }
        NAPI_ASSERT_BASE(env, argc > 0, "too few parameter", 0);

        napi_valuetype napiType;
        NAPI_CALL_BASE(env, napi_typeof(env, argv[0], &napiType), 0);
        NAPI_ASSERT_BASE(env, napiType == napi_string, "parameter 1 should be string", 0);
        char type[STR_BUFFER_SIZE] = { 0 };
        size_t len = 0;
        napi_get_value_string_utf8(env, argv[0], type, STR_BUFFER_SIZE, &len);
        NAPI_ASSERT_BASE(env, len < STR_BUFFER_SIZE, "condition string too long", 0);
        NAPI_ASSERT_BASE(env, strcmp("statusChange", type) == 0, "type mismatch('change')", 0);
        if (argc <= 1) {
            return argc;
        }
        NAPI_CALL_BASE(env, napi_typeof(env, argv[1], &napiType), 0);
        NAPI_ASSERT_BASE(env, napiType == napi_function, "type mismatch for parameter 2", 0);
        cb = argv[1];
        return argc;
    }

    static DragAction* ConvertDragAction(napi_env env, napi_value thisVar)
    {
        DragAction* dragAction = nullptr;
        napi_unwrap(env, thisVar, (void**)&dragAction);
        if (dragAction) {
            dragAction->Initialize(env, thisVar);
        }
        return dragAction;
    }

    void StartDragInternal(DragControllerAsyncCtx *dragCtx)
    {
        CHECK_NULL_VOID(dragCtx);
        ParameterType parameterType = getParameterType(dragCtx);
        LOGI("NAPI DragAction StartDragInternal parameterType:%{public}d", static_cast<int32_t>(parameterType));
        if (parameterType == ParameterType::DRAGITEMINFO_ARRAY) {
            OnMultipleComplete(dragCtx);
        } else if (parameterType == ParameterType::MIX) {
            int32_t arrayLenth = static_cast<int32_t>(dragCtx->customBuilderList.size());
            for (auto customBuilderValue: dragCtx->customBuilderList) {
                napi_value cb = nullptr;
                napi_get_reference_value(dragCtx->env, customBuilderValue, &cb);
                GetPixelMapArrayByCustom(dragCtx, cb, arrayLenth);
            }
        } else {
            LOGE("Parameter data is failed.");
        }
    }

    napi_env env_ = nullptr;
    std::list<napi_ref> cbList_;
    DragControllerAsyncCtx* asyncCtx_;
};

DragControllerAsyncCtx::~DragControllerAsyncCtx()
{
    if (!dragAction) {
        dragAction = nullptr;
    }
}

bool IsExecutingWithDragAction(DragControllerAsyncCtx* asyncCtx)
{
    CHECK_NULL_RETURN(asyncCtx, false);
    return (asyncCtx->isArray && asyncCtx->argc == 2);
}

napi_value CreateCallbackErrorValue(napi_env env, int32_t errCode, const std::string& errMsg = "")
{
    napi_value code = nullptr;
    std::string strCode = std::to_string(errCode);
    napi_create_string_utf8(env, strCode.c_str(), strCode.length(), &code);
    napi_value msg = nullptr;
    napi_create_string_utf8(env, errMsg.c_str(), errMsg.length(), &msg);
    napi_value error = nullptr;
    napi_create_error(env, code, msg, &error);
    return error;
}

double ConvertToPx(DragControllerAsyncCtx* asyncCtx, const Dimension& dimension, double size)
{
    auto unit = dimension.Unit();
    auto value = dimension.Value();
    if (unit == DimensionUnit::PERCENT) {
        return value * size;
    }
    if (unit == DimensionUnit::NONE || unit == DimensionUnit::PX) {
        return value;
    }
    auto container = AceEngine::Get().GetContainer(asyncCtx->instanceId);
    if (!container) {
        return 0.0;
    }
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipeline, 0.0);
    if (unit == DimensionUnit::VP) {
        return value * pipeline->GetDipScale();
    }
    if (unit == DimensionUnit::FP) {
        return value * pipeline->GetDipScale() * pipeline->GetFontScale();
    }
    if (unit == DimensionUnit::LPX) {
        return value * pipeline->GetLogicScale();
    }
    return 0.0;
}

static std::optional<Dimension> HandleDimensionType(napi_value parameterNapi, napi_env env)
{
    size_t ret = 0;
    std::string parameterStr;
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, parameterNapi, &valueType);
    Dimension parameter;
    if (valueType == napi_number) {
        double parameterValue;
        napi_get_value_double(env, parameterNapi, &parameterValue);
        parameter.SetValue(parameterValue);
        parameter.SetUnit(DimensionUnit::VP);
    } else if (valueType == napi_string) {
        size_t parameterLen = GetParamLen(env, parameterNapi) + 1;
        std::unique_ptr<char[]> parameterTemp = std::make_unique<char[]>(parameterLen);
        napi_get_value_string_utf8(env, parameterNapi, parameterTemp.get(), parameterLen, &ret);
        parameterStr = parameterTemp.get();
        parameter = StringUtils::StringToDimensionWithUnit(parameterStr, DimensionUnit::VP);
    } else if (valueType == napi_object) {
        ResourceInfo recv;
        if (!ParseResourceParam(env, parameterNapi, recv)) {
            return std::nullopt;
        }
        if (!ParseString(recv, parameterStr)) {
            return std::nullopt;
        }
        parameter = StringUtils::StringToDimensionWithUnit(parameterStr, DimensionUnit::VP);
    } else {
        return std::nullopt;
    }
    return parameter;
}

void CallBackForJs(DragControllerAsyncCtx* asyncCtx, napi_value result, const DragStatus dragStatus)
{
    CHECK_NULL_VOID(asyncCtx);
    CHECK_NULL_VOID(result);

    if (IsExecutingWithDragAction(asyncCtx) && asyncCtx->dragAction) {
        asyncCtx->dragAction->OnNapiCallback(result, dragStatus);
        if (asyncCtx->deferred != nullptr) {
            napi_resolve_deferred(asyncCtx->env, asyncCtx->deferred, nullptr);
            asyncCtx->deferred = nullptr;
        }
        asyncCtx->hasHandle = false;
    } else {
        LOGE("Check param failed or dragAction is nullptr");
    }
}

void GetCallBackDataForJs(DragControllerAsyncCtx* asyncCtx, const DragNotifyMsg& dragNotifyMsg,
    const DragStatus dragStatus, napi_value& result)
{
    CHECK_NULL_VOID(asyncCtx);
    napi_handle_scope scope = nullptr;
    napi_open_handle_scope(asyncCtx->env, &scope);
    napi_get_undefined(asyncCtx->env, &result);
    auto resultCode = dragNotifyMsg.result;
    LOGI("DragController resultCode = %{public}d", static_cast<int32_t>(resultCode));
    napi_create_object(asyncCtx->env, &result);
    napi_value eventNapi = nullptr;
    napi_value globalObj = nullptr;
    napi_value customDragEvent = nullptr;
    napi_create_object(asyncCtx->env, &customDragEvent);
    napi_get_global(asyncCtx->env, &globalObj);
    napi_get_named_property(asyncCtx->env, globalObj, "DragEvent", &customDragEvent);
    napi_status status = napi_new_instance(asyncCtx->env, customDragEvent, 0, nullptr, &eventNapi);
    if (status != napi_ok) {
        LOGE("status = %{public}d", status);
        napi_close_handle_scope(asyncCtx->env, scope);
        return;
    }
    auto localRef = NapiValueToLocalValue(eventNapi);
    if (localRef->IsNull()) {
        LOGE("localRef is null");
        napi_close_handle_scope(asyncCtx->env, scope);
        return;
    }
    auto* jsDragEvent =
        static_cast<Framework::JsDragEvent*>(Local<panda::ObjectRef>(localRef)->GetNativePointerField(0));
    CHECK_NULL_VOID(jsDragEvent);
    auto dragEvent = AceType::MakeRefPtr<DragEvent>();
    CHECK_NULL_VOID(dragEvent);
    dragEvent->SetResult(static_cast<DragRet>(resultCode));
    jsDragEvent->SetDragEvent(dragEvent);
    status = napi_set_named_property(asyncCtx->env, result, "event", eventNapi);

    napi_value extraParamsNapi = nullptr;
    napi_create_string_utf8(
        asyncCtx->env, asyncCtx->extraParams.c_str(), asyncCtx->extraParams.length(), &extraParamsNapi);
    napi_set_named_property(asyncCtx->env, result, "extraParams", extraParamsNapi);

    napi_value dragStatusValue = nullptr;
    napi_create_int32(asyncCtx->env, static_cast<int32_t>(dragStatus), &dragStatusValue);
    napi_set_named_property(asyncCtx->env, result, "status", dragStatusValue);

    if (result == nullptr) {
        LOGE("result is null");
        napi_close_handle_scope(asyncCtx->env, scope);
        return;
    }
    CallBackForJs(asyncCtx, result, dragStatus);
    napi_close_handle_scope(asyncCtx->env, scope);
}

void HandleSuccess(DragControllerAsyncCtx* asyncCtx, const DragNotifyMsg& dragNotifyMsg,
    const DragStatus dragStatus)
{
    LOGI("Enter HandleSuccess start");
    CHECK_NULL_VOID(asyncCtx);
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
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostSyncTask(
        [asyncCtx, dragNotifyMsg, dragStatus]() {
            CHECK_NULL_VOID(asyncCtx);
            napi_value dragAndDropInfoValue;
            GetCallBackDataForJs(asyncCtx, dragNotifyMsg, dragStatus, dragAndDropInfoValue);
        },
        TaskExecutor::TaskType::JS);
}

void HandleFail(DragControllerAsyncCtx* asyncCtx, int32_t errorCode, const std::string& errMsg = "")
{
    CHECK_NULL_VOID(asyncCtx);
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
    result[0] = CreateCallbackErrorValue(asyncCtx->env, errorCode, errMsg);
    if (asyncCtx->callbackRef) {
        napi_value ret = nullptr;
        napi_value napiCallback = nullptr;
        napi_get_reference_value(asyncCtx->env, asyncCtx->callbackRef, &napiCallback);
        napi_create_object(asyncCtx->env, &result[1]);
        napi_call_function(asyncCtx->env, nullptr, napiCallback, 2, result, &ret);
        napi_delete_reference(asyncCtx->env, asyncCtx->callbackRef);
    } else {
        napi_reject_deferred(asyncCtx->env, asyncCtx->deferred, result[0]);
    }
}

void HandleOnDragStart(DragControllerAsyncCtx* asyncCtx)
{
    ContainerScope scope(asyncCtx->instanceId);
    auto container = Container::Current();
    if (!container) {
        LOGW("container is null");
        return;
    }
    auto pipelineContext = container->GetPipelineContext();
    if (!pipelineContext) {
        LOGW("pipelineContext is null!");
        return;
    }
    auto taskExecutor = container->GetTaskExecutor();
    if (!taskExecutor) {
        LOGW("taskExecutor is null!");
        return;
    }
    taskExecutor->PostTask(
        [globalX = asyncCtx->globalX, globalY = asyncCtx->globalY, context = pipelineContext]() {
            context->OnDragEvent({ globalX, globalY }, DragEventAction::DRAG_EVENT_START_FOR_CONTROLLER);
        },
        TaskExecutor::TaskType::UI);
}

void GetShadowInfoArray(DragControllerAsyncCtx* asyncCtx,
    std::vector<Msdp::DeviceStatus::ShadowInfo>& shadowInfos)
{
    for (const auto& pixelMap: asyncCtx->pixelMapList) {
        int32_t width = pixelMap->GetWidth();
        int32_t height = pixelMap->GetHeight();
        double x = ConvertToPx(asyncCtx, asyncCtx->touchPoint.GetX(), width);
        double y = ConvertToPx(asyncCtx, asyncCtx->touchPoint.GetY(), height);
        if (!asyncCtx->hasTouchPoint) {
            x = -width * PIXELMAP_WIDTH_RATE;
            y = -height * PIXELMAP_HEIGHT_RATE;
        }
        Msdp::DeviceStatus::ShadowInfo shadowInfo { pixelMap, -x, -y  };
        shadowInfos.push_back(shadowInfo);
    }
}

static void SetIsDragging(const RefPtr<Container>& container, bool isDragging)
{
    if (!container) {
        return;
    }
    auto pipelineContext = container->GetPipelineContext();
    if (!pipelineContext) {
        return;
    }
    pipelineContext->SetIsDragging(isDragging);
}

bool JudgeCoordinateCanDrag(Msdp::DeviceStatus::ShadowInfo& shadowInfo)
{
    if (!shadowInfo.pixelMap) {
        return false;
    }
    int32_t x = -shadowInfo.x;
    int32_t y = -shadowInfo.y;
    int32_t width = shadowInfo.pixelMap->GetWidth();
    int32_t height = shadowInfo.pixelMap->GetHeight();
    if (x < 0 || y < 0 || x > width || y > height) {
        return false;
    }
    return true;
}

void EnvelopedDragData(DragControllerAsyncCtx* asyncCtx, std::optional<Msdp::DeviceStatus::DragData>& dragData)
{
    std::vector<Msdp::DeviceStatus::ShadowInfo> shadowInfos;
    GetShadowInfoArray(asyncCtx, shadowInfos);
    if (shadowInfos.empty()) {
        LOGE("shadowInfo array is empty");
        return;
    }
    if (!JudgeCoordinateCanDrag(shadowInfos[0])) {
        HandleFail(asyncCtx, Framework::ERROR_CODE_PARAM_INVALID, "touchPoint's coordinate out of range");
        return;
    }
    auto pointerId = asyncCtx->pointerId;
    std::string udKey;
    std::map<std::string, int64_t> summary;
    int32_t dataSize = 1;
    if (asyncCtx->unifiedData) {
        int32_t ret = UdmfClient::GetInstance()->SetData(asyncCtx->unifiedData, udKey);
        if (ret != 0) {
            LOGW("Udmf set data fail, error code is %{public}d", ret);
        } else {
            ret = UdmfClient::GetInstance()->GetSummary(udKey, summary);
            if (ret != 0) {
                LOGW("GetSummary fail, error code is %{public}d", ret);
            }
        }
        dataSize = static_cast<int32_t>(asyncCtx->unifiedData->GetSize());
    }
    dragData = { shadowInfos, {}, udKey, asyncCtx->extraParams, "", asyncCtx->sourceType,
        dataSize != 0 ? dataSize : shadowInfos.size(), pointerId, asyncCtx->globalX, asyncCtx->globalY, 0, true, false,
        summary };
}

void StartDragService(DragControllerAsyncCtx* asyncCtx)
{
    std::optional<Msdp::DeviceStatus::DragData> dragData;
    EnvelopedDragData(asyncCtx, dragData);
    if (!dragData) {
        LOGE("did not has any drag data");
        return;
    }
    OnDragCallback callback = [asyncCtx](const DragNotifyMsg& dragNotifyMsg) {
        LOGI("DragController start on callback %{pubic}d", dragNotifyMsg.result);
        napi_handle_scope scope = nullptr;
        napi_open_handle_scope(asyncCtx->env, &scope);
        HandleSuccess(asyncCtx, dragNotifyMsg, DragStatus::ENDED);
        napi_close_handle_scope(asyncCtx->env, scope);
    };

    int32_t ret = Msdp::DeviceStatus::InteractionManager::GetInstance()->StartDrag(dragData.value(),
        std::make_shared<OHOS::Ace::StartDragListenerImpl>(callback));
    napi_handle_scope scope = nullptr;
    napi_open_handle_scope(asyncCtx->env, &scope);
    HandleSuccess(asyncCtx, DragNotifyMsg {}, DragStatus::STARTED);
    napi_close_handle_scope(asyncCtx->env, scope);
    if (ret != 0) {
        LOGE("DragController drag start error");
        napi_handle_scope scope = nullptr;
        napi_open_handle_scope(asyncCtx->env, &scope);
        HandleFail(asyncCtx, ret);
        napi_close_handle_scope(asyncCtx->env, scope);
        return;
    }
    auto container = AceEngine::Get().GetContainer(asyncCtx->instanceId);
    SetIsDragging(container, true);
    LOGI("DragController start success");
    std::lock_guard<std::mutex> lock(asyncCtx->dragStateMutex);
    if (asyncCtx->dragState == DragState::SENDING) {
        asyncCtx->dragState = DragState::SUCCESS;
        Msdp::DeviceStatus::InteractionManager::GetInstance()->SetDragWindowVisible(true);
    }
}

void OnMultipleComplete(DragControllerAsyncCtx* asyncCtx)
{
    auto container = AceEngine::Get().GetContainer(asyncCtx->instanceId);
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [asyncCtx]() {
            CHECK_NULL_VOID(asyncCtx);
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
            StartDragService(asyncCtx);
        },
        TaskExecutor::TaskType::JS);
}

void OnComplete(DragControllerAsyncCtx* asyncCtx)
{
    auto container = AceEngine::Get().GetContainer(asyncCtx->instanceId);
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [asyncCtx]() {
            CHECK_NULL_VOID(asyncCtx);
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
            CHECK_NULL_VOID(asyncCtx->pixelMap);
            int32_t dataSize = 1;
            auto pointerId = asyncCtx->pointerId;
            std::string udKey;
            std::map<std::string, int64_t> summary;
            if (asyncCtx->unifiedData) {
                int32_t ret = UdmfClient::GetInstance()->SetData(asyncCtx->unifiedData, udKey);
                if (ret != 0) {
                    LOGW("Udmf set data fail, error code is %{public}d", ret);
                } else {
                    ret = UdmfClient::GetInstance()->GetSummary(udKey, summary);
                    if (ret != 0) {
                        LOGW("GetSummary fail, error code is %{public}d", ret);
                    }
                }
                dataSize = static_cast<int32_t>(asyncCtx->unifiedData->GetSize());
            }
            int32_t width = asyncCtx->pixelMap->GetWidth();
            int32_t height = asyncCtx->pixelMap->GetHeight();
            double x = ConvertToPx(asyncCtx, asyncCtx->touchPoint.GetX(), width);
            double y = ConvertToPx(asyncCtx, asyncCtx->touchPoint.GetY(), height);
            if (!asyncCtx->hasTouchPoint) {
                x = -width * PIXELMAP_WIDTH_RATE;
                y = -height * PIXELMAP_HEIGHT_RATE;
            } else if (x < 0 || y < 0 || x > static_cast<double>(width) || y > static_cast<double>(height)) {
                HandleFail(asyncCtx, Framework::ERROR_CODE_PARAM_INVALID, "touchPoint's coordinate out of range");
                return;
            }
            Msdp::DeviceStatus::ShadowInfo shadowInfo { asyncCtx->pixelMap, -x, -y };
            Msdp::DeviceStatus::DragData dragData { { shadowInfo }, {}, udKey, asyncCtx->extraParams, "",
                asyncCtx->sourceType, dataSize, pointerId, asyncCtx->globalX, asyncCtx->globalY, 0, true, false,
                summary };

            OnDragCallback callback = [asyncCtx](const DragNotifyMsg& dragNotifyMsg) {
                LOGI("DragController start on callback %{pubic}d", dragNotifyMsg.result);
                napi_handle_scope scope = nullptr;
                napi_open_handle_scope(asyncCtx->env, &scope);
                HandleSuccess(asyncCtx, dragNotifyMsg, DragStatus::ENDED);
                napi_close_handle_scope(asyncCtx->env, scope);
            };

            int32_t ret = Msdp::DeviceStatus::InteractionManager::GetInstance()->StartDrag(dragData,
                std::make_shared<OHOS::Ace::StartDragListenerImpl>(callback));
            if (ret != 0) {
                LOGE("drag start error");
                napi_handle_scope scope = nullptr;
                napi_open_handle_scope(asyncCtx->env, &scope);
                HandleFail(asyncCtx, ret);
                napi_close_handle_scope(asyncCtx->env, scope);
                return;
            }
            auto container = AceEngine::Get().GetContainer(asyncCtx->instanceId);
            SetIsDragging(container, true);
            LOGI("drag start success");
            {
                std::lock_guard<std::mutex> lock(asyncCtx->dragStateMutex);
                if (asyncCtx->dragState == DragState::SENDING) {
                    asyncCtx->dragState = DragState::SUCCESS;
                    Msdp::DeviceStatus::InteractionManager::GetInstance()->SetDragWindowVisible(true);
                    napi_handle_scope scope = nullptr;
                    napi_open_handle_scope(asyncCtx->env, &scope);
                    HandleOnDragStart(asyncCtx);
                    napi_close_handle_scope(asyncCtx->env, scope);
                }
            }
        },
        TaskExecutor::TaskType::JS);
}

bool ParseTouchPoint(DragControllerAsyncCtx* asyncCtx, napi_valuetype& valueType)
{
    napi_value touchPointNapi = nullptr;
    napi_get_named_property(asyncCtx->env, asyncCtx->argv[1], "touchPoint", &touchPointNapi);
    napi_typeof(asyncCtx->env, touchPointNapi, &valueType);
    if (valueType == napi_object) {
        napi_value xNapi = nullptr;
        napi_get_named_property(asyncCtx->env, touchPointNapi, "x", &xNapi);
        std::optional<Dimension> dx = HandleDimensionType(xNapi, asyncCtx->env);
        if (dx == std::nullopt) {
            return false;
        }
        napi_value yNapi = nullptr;
        napi_get_named_property(asyncCtx->env, touchPointNapi, "y", &yNapi);
        std::optional<Dimension> dy = HandleDimensionType(yNapi, asyncCtx->env);
        if (dy == std::nullopt) {
            return false;
        }
        asyncCtx->touchPoint = DimensionOffset(dx.value(), dy.value());
    } else {
        return false;
    }
    return true;
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
            asyncCtx->pixelMap = *(reinterpret_cast<std::shared_ptr<Media::PixelMap>*>(pixmapPtrAddr));
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

bool GetPixelMapByCustom(DragControllerAsyncCtx* asyncCtx)
{
    CHECK_NULL_RETURN(asyncCtx, false);
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(asyncCtx->env, &scope);
    auto delegate = EngineHelper::GetCurrentDelegate();
    if (!delegate) {
        NapiThrow(asyncCtx->env, "ace engine delegate is null", Framework::ERROR_CODE_INTERNAL_ERROR);
        napi_close_escapable_handle_scope(asyncCtx->env, scope);
        return false;
    }
    auto callback = [asyncCtx](std::shared_ptr<Media::PixelMap> pixelMap, int32_t errCode,
        std::function<void()>) {
        CHECK_NULL_VOID(pixelMap);
        CHECK_NULL_VOID(asyncCtx);
        asyncCtx->errCode = errCode;
        asyncCtx->pixelMap = std::move(pixelMap);
        OnComplete(asyncCtx);
    };
    auto builder = [build = asyncCtx->customBuilder, env = asyncCtx->env] {
        napi_call_function(env, nullptr, build, 0, nullptr, nullptr);
    };
    delegate->CreateSnapshot(builder, callback, false);
    napi_close_escapable_handle_scope(asyncCtx->env, scope);
    return true;
}

bool GetPixelMapArrayByCustom(DragControllerAsyncCtx* asyncCtx, napi_value customBuilder, int arrayLength)
{
    CHECK_NULL_RETURN(asyncCtx, false);
    asyncCtx->parseBuilderCount++;
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(asyncCtx->env, &scope);

    auto delegate = EngineHelper::GetCurrentDelegate();
    if (!delegate) {
        NapiThrow(asyncCtx->env, "ace engine delegate is null", Framework::ERROR_CODE_INTERNAL_ERROR);
        napi_close_escapable_handle_scope(asyncCtx->env, scope);
        return false;
    }
    auto callback = [asyncCtx, arrayLength, count = asyncCtx->parseBuilderCount](
        std::shared_ptr<Media::PixelMap> pixelMap, int32_t errCode, std::function<void()>) {
        CHECK_NULL_VOID(pixelMap);
        CHECK_NULL_VOID(asyncCtx);
        asyncCtx->errCode = errCode;
        asyncCtx->pixelMapList.push_back(std::move(pixelMap));
        if (count == arrayLength) {
            OnMultipleComplete(asyncCtx);
        }
    };
    auto builder = [build = customBuilder, env = asyncCtx->env] {
        napi_call_function(env, nullptr, build, 0, nullptr, nullptr);
    };
    delegate->CreateSnapshot(builder, callback, false);
    napi_close_escapable_handle_scope(asyncCtx->env, scope);
    return true;
}

bool ParseExtraInfo(DragControllerAsyncCtx* asyncCtx, std::string& errMsg, napi_value element)
{
    CHECK_NULL_RETURN(asyncCtx, false);
    napi_value extraInfoValue;
    napi_get_named_property(asyncCtx->env, element, "extraInfo", &extraInfoValue);
    napi_valuetype valueType = napi_undefined;
    napi_typeof(asyncCtx->env, extraInfoValue, &valueType);
    if (valueType != napi_string) {
        errMsg = "The type of extraInfo of the first parameter is incorrect.";
        return false;
    }
    GetNapiString(asyncCtx->env, extraInfoValue, asyncCtx->extraParams, valueType);
    return true;
}

bool ParsePixelMapAndBuilder(DragControllerAsyncCtx* asyncCtx, std::string& errMsg, napi_value element)
{
    CHECK_NULL_RETURN(asyncCtx, false);
    napi_value pixelMapValue;
    napi_get_named_property(asyncCtx->env, element, "pixelMap", &pixelMapValue);
    PixelMapNapiEntry pixelMapNapiEntry = Framework::JsEngine::GetPixelMapNapiEntry();
    if (pixelMapNapiEntry == nullptr) {
        LOGW("DragController failed to parse pixelMap from the first argument.");
        napi_value customBuilderValue;
        napi_get_named_property(asyncCtx->env, element, "builder", &customBuilderValue);
        napi_valuetype valueType = napi_undefined;
        napi_typeof(asyncCtx->env, customBuilderValue, &valueType);
        if (valueType != napi_function) {
            errMsg = "The type of customBuilder of the first parameter is incorrect.";
            return false;
        }
        napi_ref ref = nullptr;
        napi_create_reference(asyncCtx->env, customBuilderValue, 1, &ref);
        asyncCtx->customBuilderList.push_back(ref);
    } else {
        void* pixmapPtrAddr = pixelMapNapiEntry(asyncCtx->env, pixelMapValue);
        if (pixmapPtrAddr == nullptr) {
            LOGW("DragController The pixelMap parsed from the first argument is null");
            return false;
        } else {
            asyncCtx->pixelMapList.push_back(*(reinterpret_cast<std::shared_ptr<Media::PixelMap>*>(pixmapPtrAddr)));
        }
    }
    return true;
}

bool ParseDragItemListInfoParam(DragControllerAsyncCtx* asyncCtx, std::string& errMsg)
{
    if (!asyncCtx) {
        LOGE("DragControllerAsyncContext is null");
        errMsg = "DragControllerAsyncContext is null";
        return false;
    }
    bool isParseSucess;
    uint32_t arrayLength = 0;
    napi_get_array_length(asyncCtx->env, asyncCtx->argv[0], &arrayLength);
    for (size_t i = 0; i < arrayLength; i++) {
        bool hasElement = false;
        napi_has_element(asyncCtx->env, asyncCtx->argv[0], i, &hasElement);
        napi_value element = nullptr;
        napi_get_element(asyncCtx->env, asyncCtx->argv[0], i, &element);
        napi_valuetype valueType = napi_undefined;
        napi_typeof(asyncCtx->env, element, &valueType);
        if (valueType == napi_function) {
            napi_ref ref = nullptr;
            napi_create_reference(asyncCtx->env, element, 1, &ref);
            asyncCtx->customBuilderList.push_back(ref);
            isParseSucess = true;
            continue;
        }
        if (valueType != napi_object) {
            errMsg = "The type of first parameter is incorrect";
            isParseSucess = false;
            break;
        }
        if (!ParseExtraInfo(asyncCtx, errMsg, element)) {
            errMsg = "The type of first parameter is incorrect by extraInfo";
            isParseSucess = false;
            break;
        }
        if (!ParsePixelMapAndBuilder(asyncCtx, errMsg, element)) {
            errMsg = "The type of first parameter is incorrect by pixelMap or builder";
            isParseSucess = false;
            break;
        }
        isParseSucess = true;
        continue;
    }
    return isParseSucess;
}

bool ParseDragParam(DragControllerAsyncCtx* asyncCtx, std::string& errMsg)
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
    
    bool isArray = false;
    napi_is_array(asyncCtx->env, asyncCtx->argv[0], &isArray);
    if (isArray) {
        LOGI("DragController multiple elements");
        asyncCtx->isArray = true;
        return ParseDragItemListInfoParam(asyncCtx, errMsg);
    }
    asyncCtx->isArray = false;
    return ParseDragItemInfoParam(asyncCtx, errMsg);
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

    napi_value previewOptionsNApi = nullptr;
    napi_get_named_property(asyncCtx->env, asyncCtx->argv[1], "previewOptions", &previewOptionsNApi);
    
    napi_value modeNApi = nullptr;
    napi_get_named_property(asyncCtx->env, previewOptionsNApi, "mode", &modeNApi);
    int32_t dragviewMode = 0;
    napi_get_value_int32(asyncCtx->env, modeNApi, &dragviewMode);
    asyncCtx->hasTouchPoint = ParseTouchPoint(asyncCtx, valueType);
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
    if ((asyncCtx->argc != 2) && (asyncCtx->argc != argCount3)) {
        errMsg = "The number of parameters must be 2 or 3.";
        return false;
    }

    // Check and parse the first parameter
    if (!ParseDragParam(asyncCtx, errMsg)) {
        return false;
    }

    // Check and parse the second parameter
    return ParseDragInfoParam(asyncCtx, errMsg);
}

void CreateCallback(DragControllerAsyncCtx* asyncCtx, napi_value* result)
{
    CHECK_NULL_VOID(asyncCtx);
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
    CHECK_NULL_VOID(asyncCtx);
    napi_value thisVar = nullptr;
    void* data = nullptr;
    asyncCtx->instanceId = Container::CurrentId();
    asyncCtx->env = env;
    // get arguments from JS
    napi_get_cb_info(asyncCtx->env, info, &(asyncCtx->argc), asyncCtx->argv, &thisVar, &data);
}

ParameterType getParameterType(DragControllerAsyncCtx* asyncCtx)
{
    CHECK_NULL_RETURN(asyncCtx, ParameterType::ERROR);
    if (asyncCtx->pixelMap != nullptr) {
        return ParameterType::DRAGITEMINFO;
    }
    if (asyncCtx->customBuilder != nullptr) {
        return ParameterType::CUSTOMBUILDER;
    }
    if (!asyncCtx->pixelMapList.empty() && asyncCtx->customBuilderList.empty()) {
        return ParameterType::DRAGITEMINFO_ARRAY;
    }
    if (!asyncCtx->customBuilderList.empty() || !asyncCtx->pixelMapList.empty()) {
        return ParameterType::MIX;
    } else {
        return ParameterType::ERROR;
    }
}

bool ConfirmCurPointerEventInfo(DragControllerAsyncCtx *asyncCtx, const RefPtr<Container>& container)
{
    CHECK_NULL_RETURN(asyncCtx, false);
    CHECK_NULL_RETURN(container, false);
    StopDragCallback stopDragCallback = [asyncCtx, container]() {
        CHECK_NULL_VOID(asyncCtx);
        CHECK_NULL_VOID(container);
        bool needPostStopDrag = false;
        {
            std::lock_guard<std::mutex> lock(asyncCtx->dragStateMutex);
            needPostStopDrag = (asyncCtx->dragState == DragState::SENDING);
            asyncCtx->dragState = DragState::REJECT;
        }
        if (needPostStopDrag) {
            auto taskExecutor = container->GetTaskExecutor();
            CHECK_NULL_VOID(taskExecutor);
            auto windowId = container->GetWindowId();
            taskExecutor->PostTask(
                [asyncCtx, windowId]() {
                    CHECK_NULL_VOID(asyncCtx);
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
    bool getPointSuccess = container->GetCurPointerEventInfo(
        asyncCtx->pointerId, asyncCtx->globalX, asyncCtx->globalY, asyncCtx->sourceType, std::move(stopDragCallback));
    return getPointSuccess;
}

static bool CheckDragging(const RefPtr<Container>& container)
{
    if (!container) {
        return false;
    }
    auto pipelineContext = container->GetPipelineContext();
    if (!pipelineContext || !pipelineContext->IsDragging()) {
        return false;
    }
    return true;
}

static napi_value JSExecuteDrag(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);

    auto dragAsyncContext = new (std::nothrow) DragControllerAsyncCtx();
    if (dragAsyncContext == nullptr) {
        LOGE("DragControllerAsyncContext is null");
        return nullptr;
    }
    InitializeDragControllerCtx(env, info, dragAsyncContext);

    std::string errMsg;
    if (!CheckAndParseParams(dragAsyncContext, errMsg)) {
        NapiThrow(env, errMsg, Framework::ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }
    napi_value result = nullptr;
    CreateCallback(dragAsyncContext, &result);
    auto container = AceEngine::Get().GetContainer(dragAsyncContext->instanceId);
    if (!container) {
        NapiThrow(env, "container is null", Framework::ERROR_CODE_INTERNAL_ERROR);
        return nullptr;
    }
    if (CheckDragging(container)) {
        NapiThrow(env, "only one drag is allowed at the same time", Framework::ERROR_CODE_INTERNAL_ERROR);
        return nullptr;
    }
    auto getPointSuccess = ConfirmCurPointerEventInfo(dragAsyncContext, container);
    if (!getPointSuccess) {
        HandleFail(dragAsyncContext, -1);
        napi_escape_handle(env, scope, result, &result);
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }
    ParameterType parameterType = getParameterType(dragAsyncContext);
    if (parameterType == ParameterType::DRAGITEMINFO) {
        OnComplete(dragAsyncContext);
    } else if (parameterType == ParameterType::CUSTOMBUILDER) {
        GetPixelMapByCustom(dragAsyncContext);
    } else {
        LOGE("Parameter data is failed.");
    }
    napi_escape_handle(env, scope, result, &result);
    napi_close_escapable_handle_scope(env, scope);
    return result;
}

static napi_value JSCreateDragAction(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);

    auto dragAsyncContext = new (std::nothrow) DragControllerAsyncCtx();
    if (dragAsyncContext == nullptr) {
        LOGE("DragControllerAsyncContext is null");
        return nullptr;
    }
    InitializeDragControllerCtx(env, info, dragAsyncContext);

    std::string errMsg;
    if (!CheckAndParseParams(dragAsyncContext, errMsg)) {
        NapiThrow(env, errMsg, Framework::ERROR_CODE_PARAM_INVALID);
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }

    auto container = AceEngine::Get().GetContainer(dragAsyncContext->instanceId);
    if (!container) {
        NapiThrow(env, "container is null", Framework::ERROR_CODE_INTERNAL_ERROR);
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }

    if (CheckDragging(container)) {
        NapiThrow(env, "only one dragAction is allowed at the same time", Framework::ERROR_CODE_INTERNAL_ERROR);
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }

    auto getPointSuccess = ConfirmCurPointerEventInfo(dragAsyncContext, container);
    if (!getPointSuccess) {
        NapiThrow(env, "confirm pointer info failed", Framework::ERROR_CODE_PARAM_INVALID);
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }

    napi_value result = nullptr;
    napi_get_cb_info(env, info, nullptr, nullptr, &result, nullptr);
    DragAction* dragAction = new (std::nothrow) DragAction(dragAsyncContext);
    dragAction->NapiSerializer(env, result);
    dragAsyncContext->dragAction = dragAction;
    napi_escape_handle(env, scope, result, &result);
    napi_close_escapable_handle_scope(env, scope);
    return result;
}

static napi_value JSGetDragPreview(napi_env env, napi_callback_info info)
{
    DragPreview* dragPreview = new DragPreview();
    napi_value result = nullptr;
    napi_get_cb_info(env, info, nullptr, nullptr, &result, nullptr);
    dragPreview->NapiSerializer(env, result);
    return result;
}
#else

static napi_value JSGetDragPreview(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);
    NapiThrow(env, "The current environment does not enable drag framework or does not support drag preview.",
        Framework::ERROR_CODE_INTERNAL_ERROR);
    napi_close_escapable_handle_scope(env, scope);
    return nullptr;
}

static napi_value JSExecuteDrag(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);
    NapiThrow(env, "The current environment does not enable drag framework or does not support pixelMap.",
        Framework::ERROR_CODE_INTERNAL_ERROR);
    napi_close_escapable_handle_scope(env, scope);
    return nullptr;
}

static napi_value JSCreateDragAction(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);
    NapiThrow(env, "The current environment does not enable drag framework or does not support pixelMap.",
        Framework::ERROR_CODE_INTERNAL_ERROR);
    napi_close_escapable_handle_scope(env, scope);
    return nullptr;
}
#endif

static napi_value DragControllerExport(napi_env env, napi_value exports)
{
    napi_property_descriptor dragControllerDesc[] = {
        DECLARE_NAPI_FUNCTION("executeDrag", JSExecuteDrag),
        DECLARE_NAPI_FUNCTION("getDragPreview", JSGetDragPreview),
        DECLARE_NAPI_FUNCTION("createDragAction", JSCreateDragAction),
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
