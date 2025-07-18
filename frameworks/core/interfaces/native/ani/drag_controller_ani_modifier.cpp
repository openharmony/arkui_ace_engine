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

#include "drag_controller_ani_modifier.h"

#include "drag_controller_utils.h"
#include "drag_preview.h"
#include "interaction_manager.h"
// #include "pixel_map_taihe_ani.h"
// #include "udmf_ani_converter_utils.h"

#include "adapter/ohos/capability/interaction/start_drag_listener_impl.h"
#include "adapter/ohos/capability/udmf/udmf_impl.h"
#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/common/resource/resource_manager.h"
#include "core/common/resource/resource_wrapper.h"
#include "core/common/udmf/udmf_client.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/manager/drag_drop/drag_drop_controller_func_wrapper.h"
#include "core/components_ng/manager/drag_drop/drag_drop_func_wrapper.h"
#include "core/interfaces/native/implementation/drag_event_peer.h"
#include "core/pipeline/pipeline_base.h"
#include "frameworks/base/error/error_code.h"
#include "frameworks/bridge/common/utils/engine_helper.h"

namespace OHOS::Ace::NG {
class DragAction;
namespace {
constexpr int32_t PARAMETER_NUM = 2;
constexpr int32_t SOURCE_TYPE_MOUSE = 1;
constexpr int32_t MOUSE_POINTER_ID = 1001;
constexpr int32_t SOURCE_TOOL_PEN = 1;
constexpr int32_t SOURCE_TYPE_TOUCH = 2;
constexpr int32_t PEN_POINTER_ID = 102;
constexpr int32_t CREATE_PIXELMAP_DELAY_TIME = 80;
constexpr int32_t TWO_ARGS = 2;
constexpr int32_t MAX_ESCAPE_NUM = 1;

using DragNotifyMsg = Msdp::DeviceStatus::DragNotifyMsg;
using OnDragCallback = std::function<void(const DragNotifyMsg&)>;

enum class DragState { PENDING, SENDING, REJECT, SUCCESS };
enum class DragStatus { STARTED, ENDED };
enum class ParameterType { DRAG_CUSTOM_BUILDER, DRAG_PIXEL, DRAG_PIXEL_ARRAY, DRAG_MIX_ARRYA, ERROR };

// the context of drag controller
struct DragControllerAsyncCtx {
    ani_env* env = nullptr;
    std::shared_ptr<Media::PixelMap> pixelMap = nullptr;
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMapList;
    bool isArray = false;
    bool isSwitchedToSubWindow = false;
    ani_fn_object asyncCallback = nullptr;
    ani_resolver deferred = nullptr;
    ArkUINodeHandle customBuilderNode = nullptr;
    std::vector<ArkUINodeHandle> customBuilderNodeList;
    RefPtr<OHOS::Ace::UnifiedData> unifiedData;
    std::string extraParams;
    int32_t instanceId = -1;
    int32_t errCode = -1;
    int32_t badgeNumber = 1;
    std::mutex mutex;
    bool hasHandle = false;
    DragPointerEvent dragPointerEvent;
    float windowScale = 1.0f;
    float dipScale = 0.0;
    int parseBuilderCount = 0;
    std::mutex dragStateMutex;
    DragState dragState = DragState::PENDING;
    std::optional<DimensionOffset> touchPoint = DimensionOffset(0.0_vp, 0.0_vp);
    DragAction *dragAction = nullptr;
    NG::DragPreviewOption dragPreviewOption;
    ~DragControllerAsyncCtx();
};
} // namespace
void OnMultipleComplete(std::shared_ptr<DragControllerAsyncCtx> asyncCtx);
void CreatePixelMapArrayByCustom(
    std::shared_ptr<DragControllerAsyncCtx> asyncCtx, ArkUINodeHandle customBuilder, int arrayLength);
ParameterType GetParameterType(std::shared_ptr<DragControllerAsyncCtx> asyncCtx);

class DragAction {
public:
    DragAction(std::shared_ptr<DragControllerAsyncCtx> asyncCtx) : asyncCtx_(asyncCtx) {}
    ~DragAction()
    {
        if (asyncCtx_) {
            asyncCtx_->dragAction = nullptr;
        }
        CHECK_NULL_VOID(env_);
        for (auto& item : cbList_) {
            env_->GlobalReference_Delete(item);
        }
    }

    void OnANICallback(ani_ref resultRef)
    {
        std::vector<ani_ref> cbList;
        for (auto& cbRef : cbList_) {
            ani_wref cbWref;
            env_->WeakReference_Create(cbRef, &cbWref);
            ani_ref ref;
            ani_boolean wasReleased;
            env_->WeakReference_GetReference(cbWref, &wasReleased, &ref);
            cbList.emplace_back(ref);
        }
        LOGI("AceDrag, OnANICallback start cbList.size() = %{public}u.", cbList.size());
        for (auto& callbackRef : cbList) {
            ani_ref fnReturnVal;
            env_->FunctionalObject_Call(static_cast<ani_fn_object>(callbackRef), 1, &resultRef, &fnReturnVal);
        }
    }

    void AniSerializer([[maybe_unused]] ani_env* env, ani_object& result, ani_long dragActionPtr)
    {
        ani_status status = ANI_OK;
        static const char* className = "@ohos.arkui.dragController.dragController.DragActionInner";
        ani_class cls;
        if ((status = env->FindClass(className, &cls)) != ANI_OK) {
            LOGE("AceDrag, find DragAction calss fail. status = %{public}d", status);
            return;
        }
        ani_method method;
        if ((status = env->Class_FindMethod(cls, "<ctor>", "J:V", &method)) != ANI_OK) {
            LOGE("AceDrag, find constructor method failed. status = %{public}d", status);
            return;
        }
        if ((status = env->Object_New(cls, method, &result, dragActionPtr)) != ANI_OK) {
            LOGE("AceDrag, create DragAction object failed. status = %{public}d", status);
            return;
        }
    }

    static void On([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object, const char* type,
        ani_object callback, ani_long dragActionPtr)
    {
        LOGI("AceDrag, drag action On function has been called.");
        CHECK_NULL_VOID(env);
        if (ANI_OK != env->CreateLocalScope(Ani::SPECIFIED_CAPACITY)) {
            return;
        }
        auto argc = ParseArgs(env, type, callback);
        if (argc != TWO_ARGS) {
            Ani::AniThrow(env, "check param failed.", ERROR_CODE_PARAM_INVALID);
            LOGE("AceDrag, check param failed.");
            env->DestroyLocalScope();
            return;
        }
        DragAction* dragAction = reinterpret_cast<DragAction*>(dragActionPtr);
        if (!dragAction) {
            Ani::AniThrow(env, "convert drag action failed.", ERROR_CODE_PARAM_INVALID);
            LOGE("AceDrag, convert drag action failed.");
            env->DestroyLocalScope();
            return;
        }
        dragAction->Initialize(env);
        auto iter = dragAction->FindCbList(callback);
        if (iter != dragAction->cbList_.end()) {
            Ani::AniThrow(env, "js callback function already registered.", ERROR_CODE_PARAM_INVALID);
            LOGE("AceDrag, js callback function already registered.");
            env->DestroyLocalScope();
            return;
        }
        ani_ref fnObjGlobalRef = nullptr;
        env->GlobalReference_Create(callback, &fnObjGlobalRef);
        dragAction->cbList_.emplace_back(fnObjGlobalRef);
        LOGI("AceDrag, registered On function number is %{public}d.", static_cast<int>(dragAction->cbList_.size()));
        env->DestroyLocalScope();
    }

    static void Off([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object, const char* type,
        [[maybe_unused]] ani_object callback, ani_long dragActionPtr)
    {
        LOGI("AceDrag, drag action Off function has been called.");
        CHECK_NULL_VOID(env);
        if (ANI_OK != env->CreateLocalScope(Ani::SPECIFIED_CAPACITY)) {
            return;
        }
        DragAction* dragAction = reinterpret_cast<DragAction*>(dragActionPtr);
        if (!dragAction) {
            LOGE("AceDrag, convert drag action failed.");
            Ani::AniThrow(env, "convert drag action failed.", ERROR_CODE_PARAM_INVALID);
            env->DestroyLocalScope();
            return;
        }
        dragAction->Initialize(env);
        auto argc = ParseArgs(env, type, callback);
        if (argc == 1) {
            for (const auto& item : dragAction->cbList_) {
                dragAction->env_->GlobalReference_Delete(item);
            }
            dragAction->cbList_.clear();
        } else if (argc == TWO_ARGS) {
            auto iter = dragAction->FindCbList(callback);
            if (iter != dragAction->cbList_.end()) {
                if (ANI_OK != dragAction->env_->GlobalReference_Delete(*iter)) {
                    LOGE("AceDrag, GlobalReference_Delete failed.");
                }
                dragAction->cbList_.erase(iter);
            }
        } else {
            Ani::AniThrow(env, "check param failed.", ERROR_CODE_PARAM_INVALID);
            LOGE("AceDrag, check param failed.");
        }
        env->DestroyLocalScope();
    }

    static ani_object StartDrag(
        [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object, ani_long dragActionPtr)
    {
        LOGI("AceDrag, drag action StartDrag function has been called.");
        CHECK_NULL_RETURN(env, nullptr);
        if (ANI_OK != env->CreateEscapeLocalScope(MAX_ESCAPE_NUM)) {
            return nullptr;
        }
        ani_ref escapedObj;
        DragAction* dragAction = reinterpret_cast<DragAction*>(dragActionPtr);
        if (!dragAction) {
            Ani::AniThrow(env, "convert drag action failed.", ERROR_CODE_PARAM_INVALID);
            LOGE("AceDrag, convert drag action failed.");
            env->DestroyEscapeLocalScope(nullptr, &escapedObj);
            return nullptr;
        }
        if (dragAction->asyncCtx_ == nullptr) {
            Ani::AniThrow(env, "drag action must be recreated for each dragging.", ERROR_CODE_INTERNAL_ERROR);
            LOGE("AceDrag, drag action must be recreated for each dragging.");
            env->DestroyEscapeLocalScope(nullptr, &escapedObj);
            return nullptr;
        }
        ani_object promise;
        if (ANI_OK != env->Promise_New(&dragAction->asyncCtx_->deferred, &promise)) {
            Ani::AniThrow(env, "create promise object failed!", ERROR_CODE_INTERNAL_ERROR);
            LOGE("AceDrag, create promise object failed!");
            env->DestroyEscapeLocalScope(nullptr, &escapedObj);
            return nullptr;
        }
        dragAction->StartDragInternal(dragAction->asyncCtx_);
        env->DestroyEscapeLocalScope(promise, &escapedObj);
        return promise;
    }

    std::list<ani_ref>::iterator FindCbList(ani_object cb)
    {
        return std::find_if(cbList_.begin(), cbList_.end(), [env = env_, cb](const ani_ref& item) -> bool {
            ani_boolean result = false;
            ani_wref cbWref;
            env->WeakReference_Create(item, &cbWref);
            ani_ref ref;
            ani_boolean wasReleased;
            env->WeakReference_GetReference(cbWref, &wasReleased, &ref);
            env->Reference_StrictEquals(ref, cb, &result);
            return static_cast<bool>(result);
        });
    }

private:
    void Initialize(ani_env* env)
    {
        env_ = env;
    }

    static size_t ParseArgs(ani_env* env, const char* type, ani_object callback)
    {
        CHECK_NULL_RETURN(env, 0);
        std::string aniType = type;
        if (aniType != "statusChange") {
            LOGE("AceDrag, type mismatch('statusChange').");
            return 0;
        }
        ani_boolean isUndefinedResponse;
        env->Reference_IsUndefined(callback, &isUndefinedResponse);
        if (isUndefinedResponse) {
            return 1;
        }
        return TWO_ARGS;
    }

    static DragAction* ConvertDragAction(ani_env* env, ani_object object)
    {
        CHECK_NULL_RETURN(env, nullptr);
        ani_long serializer;
        ani_status status = ANI_OK;
        if ((status = env->Object_GetFieldByName_Long(object, "dragAction", &serializer)) != ANI_OK) {
            return nullptr;
        }
        return reinterpret_cast<DragAction*>(serializer);
    }

    void StartDragInternal(std::shared_ptr<DragControllerAsyncCtx> asyncCtx)
    {
        CHECK_NULL_VOID(asyncCtx);
        CHECK_NULL_VOID(asyncCtx->env);
        ParameterType parameterType = GetParameterType(asyncCtx);
        if (parameterType == ParameterType::DRAG_PIXEL_ARRAY) {
            LOGI("AceDrag, drag preview is pixelMap.");
            OnMultipleComplete(asyncCtx);
        } else if (parameterType == ParameterType::DRAG_MIX_ARRYA) {
            LOGI("AceDrag, drag preview is custom builder.");
            int32_t arrayLenth = static_cast<int32_t>(asyncCtx->customBuilderNodeList.size());
            for (auto customBuilderNodeValue : asyncCtx->customBuilderNodeList) {
                CreatePixelMapArrayByCustom(asyncCtx, customBuilderNodeValue, arrayLenth);
            }
        } else {
            LOGE("AceDrag, parameter parsing failed.");
            Ani::AniThrow(asyncCtx->env, "parameter parsing failed.", ERROR_CODE_PARAM_INVALID);
        }
    }

    ani_env* env_ = nullptr;
    std::list<ani_ref> cbList_;
    std::shared_ptr<DragControllerAsyncCtx> asyncCtx_;
};

DragControllerAsyncCtx::~DragControllerAsyncCtx()
{
    if (!dragAction) {
        dragAction = nullptr;
    }
}

static bool CheckDragging(const RefPtr<Container>& container)
{
    CHECK_NULL_RETURN(container, false);
    auto pipelineContext = container->GetPipelineContext();
    if (!pipelineContext || !pipelineContext->IsDragging()) {
        return false;
    }
    return true;
}

ParameterType GetParameterType(std::shared_ptr<DragControllerAsyncCtx> asyncCtx)
{
    CHECK_NULL_RETURN(asyncCtx, ParameterType::ERROR);
    if (asyncCtx->pixelMap != nullptr) {
        return ParameterType::DRAG_PIXEL;
    }
    if (asyncCtx->customBuilderNode != nullptr) {
        return ParameterType::DRAG_CUSTOM_BUILDER;
    }
    if (!asyncCtx->pixelMapList.empty() && asyncCtx->customBuilderNodeList.empty()) {
        return ParameterType::DRAG_PIXEL_ARRAY;
    }
    if (!asyncCtx->customBuilderNodeList.empty() || !asyncCtx->pixelMapList.empty()) {
        return ParameterType::DRAG_MIX_ARRYA;
    }
    return ParameterType::ERROR;
}

double ConvertToPx(std::shared_ptr<DragControllerAsyncCtx> asyncCtx, const Dimension& dimension, double size)
{
    auto unit = dimension.Unit();
    auto value = dimension.Value();
    if (unit == DimensionUnit::PERCENT) {
        return value * size;
    }
    if (unit == DimensionUnit::NONE || unit == DimensionUnit::PX) {
        return value;
    }

    auto container = Ace::AceEngine::Get().GetContainer(asyncCtx->instanceId);
    CHECK_NULL_RETURN(container, 0.0);
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

void SetDragResult(
    const DragNotifyMsg& notifyMessage, const RefPtr<OHOS::Ace::DragEvent>& dragEvent)
{
    DragRet result = DragRet::DRAG_FAIL;
    switch (notifyMessage.result) {
        case Msdp::DeviceStatus::DragResult::DRAG_SUCCESS:
            result = DragRet::DRAG_SUCCESS;
            break;
        case Msdp::DeviceStatus::DragResult::DRAG_FAIL:
            result = DragRet::DRAG_FAIL;
            break;
        case Msdp::DeviceStatus::DragResult::DRAG_CANCEL:
            result = DragRet::DRAG_CANCEL;
            break;
        default:
            break;
    }
    CHECK_NULL_VOID(dragEvent);
    dragEvent->SetResult(result);
}

void SetDragBehavior(
    const DragNotifyMsg& notifyMessage, const RefPtr<OHOS::Ace::DragEvent>& dragEvent)
{
    DragBehavior dragBehavior = DragBehavior::UNKNOWN;
    switch (notifyMessage.dragBehavior) {
        case Msdp::DeviceStatus::DragBehavior::COPY:
            dragBehavior = DragBehavior::COPY;
            break;
        case Msdp::DeviceStatus::DragBehavior::MOVE:
            dragBehavior = DragBehavior::MOVE;
            break;
        default:
            break;
    }
    CHECK_NULL_VOID(dragEvent);
    dragEvent->SetDragBehavior(dragBehavior);
}

ani_object CreateDragEventObject(ani_env* env, const DragNotifyMsg& dragNotifyMsg)
{
    ani_object dragEventObj = {};
    CHECK_NULL_RETURN(env, dragEventObj);
    ani_status status = ANI_OK;
    static const char* className = "Larkui/component/common/DragEventInternal;";
    ani_class cls;
    if ((status = env->FindClass(className, &cls)) != ANI_OK) {
        LOGE("AceDrag, find DragEventInner calss fail. status = %{public}d", status);
        return dragEventObj;
    }

    ani_method ctor;
    if ((status = env->Class_FindMethod(cls, "<ctor>", ":V", &ctor)) != ANI_OK) {
        LOGE("AceDrag, find constructor method fail. status = %{public}d", status);
        return dragEventObj;
    }

    if ((status = env->Object_New(cls, ctor, &dragEventObj)) != ANI_OK) {
        LOGE("AceDrag, create dragEvent fail. status = %{public}d", status);
        return dragEventObj;
    }

    ani_static_method getEventFromPeer;
    if ((status = env->Class_FindStaticMethod(
        cls, "fromPtr", "l:C{arkui.component.common.DragEventInternal}", &getEventFromPeer)) != ANI_OK) {
        LOGE("AceDrag, find fromPtr method fail. status = %{public}d", status);
        return dragEventObj;
    }

    RefPtr<OHOS::Ace::DragEvent> dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    SetDragResult(dragNotifyMsg, dragEvent);
    SetDragBehavior(dragNotifyMsg, dragEvent);
    auto arkDragInfo = DragEventPeer::Create(dragEvent);

    ani_ref commonDragEvent;
    if ((status = env->Class_CallStaticMethod_Ref(
        cls, getEventFromPeer, &commonDragEvent, reinterpret_cast<ani_long>(arkDragInfo))) != ANI_OK) {
        LOGE("AceDrag, call fromPtr method failed. status = %{public}d", status);
        delete arkDragInfo;
        return dragEventObj;
    }
    return static_cast<ani_object>(commonDragEvent);
}

void TriggerJsCallback(std::shared_ptr<DragControllerAsyncCtx> asyncCtx, ani_ref result)
{
    LOGI("AceDrag, TriggerJsCallback enter.");
    CHECK_NULL_VOID(asyncCtx);
    CHECK_NULL_VOID(asyncCtx->env);
    ani_status status = ANI_OK;
    if (asyncCtx->isArray && asyncCtx->dragAction) {
        asyncCtx->dragAction->OnANICallback(result);
        if (asyncCtx->deferred != nullptr) {
            LOGI("AceDrag, PromiseResolver_Resolve start");
            ani_ref promiseResult = nullptr;
            asyncCtx->env->GetUndefined(&promiseResult);
            asyncCtx->env->PromiseResolver_Resolve(asyncCtx->deferred, promiseResult);
        }
    } else {
        if (asyncCtx->asyncCallback) { // asyncCallback
            LOGI("AceDrag, asyncCallback start");
            std::vector<ani_ref> resultRef(PARAMETER_NUM);
            asyncCtx->env->GetUndefined(&resultRef[0]);
            auto errObj = Ani::GetErrorObject(asyncCtx->env, "", ERROR_CODE_NO_ERROR);
            resultRef[0] = errObj;
            resultRef[1] = result;
            ani_ref fnReturnVal;
            if ((status = asyncCtx->env->FunctionalObject_Call(
                asyncCtx->asyncCallback, resultRef.size(), resultRef.data(), &fnReturnVal)) != ANI_OK) {
                LOGE("AceDrag, FunctionalObject_Call failed, status = %{public}d", status);
            }
            asyncCtx->env->GlobalReference_Delete(asyncCtx->asyncCallback);
        } else { // promise
            if ((status = asyncCtx->env->PromiseResolver_Resolve(asyncCtx->deferred, result)) != ANI_OK) {
                LOGE("AceDrag, PromiseResolver_Resolve failed, status = %{public}d", status);
            }
        }
    }
    asyncCtx->deferred = nullptr;
    asyncCtx->hasHandle = false;
}

void CallBackJsFunction(
    std::shared_ptr<DragControllerAsyncCtx> asyncCtx, const DragNotifyMsg& dragNotifyMsg, const DragStatus dragStatus)
{
    CHECK_NULL_VOID(asyncCtx);
    CHECK_NULL_VOID(asyncCtx->env);
    ani_status status = ANI_OK;
    if ((status = asyncCtx->env->CreateLocalScope(Ani::SPECIFIED_CAPACITY)) != ANI_OK) {
        LOGE("AceDrag, CreateLocalScope fail. status = %{public}d", status);
        return;
    }
    static const char* namespaceName = "@ohos.arkui.dragController.dragController";
    ani_namespace nns;
    if ((status = asyncCtx->env->FindNamespace(namespaceName, &nns)) != ANI_OK) {
        LOGE("AceDrag, find dragController namespace fail. status = %{public}d", status);
        asyncCtx->env->DestroyLocalScope();
        return;
    }

    ani_object dragEventObj = CreateDragEventObject(asyncCtx->env, dragNotifyMsg);
    ani_string extraParamsObj;
    if ((status = asyncCtx->env->String_NewUTF8(
        asyncCtx->extraParams.c_str(), asyncCtx->extraParams.size(), &extraParamsObj)) != ANI_OK) {
        LOGE("AceDrag, covert extraParams to ani object failed. status = %{public}d", status);
        asyncCtx->env->DestroyLocalScope();
        return;
    }
    const std::string className1 = std::string(namespaceName).append(".DragEventParamInner");
    const std::string className2 = std::string(namespaceName).append(".DragAndDropInfoInner");
    ani_class cls;
    ani_method ctor;
    ani_object dragObj;
    if (asyncCtx->isArray) {
        LOGI("AceDrag, LDragAndDropInfoInner;");
        ani_enum_item dragStatusItem;
        if (!Ani::GetEnumItem(asyncCtx->env, ani_size(dragStatus), "LDragStatus;", dragStatusItem)) {
            LOGE("AceDrag, get dragStatus enum item failed.");
            asyncCtx->env->DestroyLocalScope();
            return;
        }
        if (ANI_OK != asyncCtx->env->FindClass(className2.c_str(), &cls)) {
            LOGE("AceDrag, find LDragAndDropInfoInner calss fail.");
            asyncCtx->env->DestroyLocalScope();
            return;
        }
        if (ANI_OK != asyncCtx->env->Class_FindMethod(cls, "<ctor>",
            "C{@ohos.arkui.dragController.dragController.DragStatus}C{arkui.component.common.DragEvent}"
            "C{std.core.String}:", &ctor)) {
            LOGE("AceDrag, find LDragAndDropInfoInner constructor method failed.");
            asyncCtx->env->DestroyLocalScope();
            return;
        }
        if (ANI_OK != asyncCtx->env->Object_New(cls, ctor, &dragObj, dragStatusItem, dragEventObj, extraParamsObj)) {
            LOGE("AceDrag, create LDragAndDropInfoInner object failed.");
            asyncCtx->env->DestroyLocalScope();
            return;
        }
    } else {
        LOGI("AceDrag, LDragEventParamInner;");
        if (ANI_OK != asyncCtx->env->FindClass(className1.c_str(), &cls)) {
            LOGE("AceDrag, find DragEventParamInner calss fail.");
            asyncCtx->env->DestroyLocalScope();
            return;
        }
        if (ANI_OK != asyncCtx->env->Class_FindMethod(cls, "<ctor>",
            "C{arkui.component.common.DragEvent}C{std.core.String}:", &ctor)) {
            LOGE("AceDrag, find LDragEventParamInner constructor method failed.");
            asyncCtx->env->DestroyLocalScope();
            return;
        }
        if (ANI_OK != asyncCtx->env->Object_New(cls, ctor, &dragObj, dragEventObj, extraParamsObj)) {
            LOGE("AceDrag, create DragEventParamInner object failed.");
            asyncCtx->env->DestroyLocalScope();
            return;
        }
    }
    TriggerJsCallback(asyncCtx, dragObj);
    asyncCtx->env->DestroyLocalScope();
}

void HandleSuccess(
    std::shared_ptr<DragControllerAsyncCtx> asyncCtx, const DragNotifyMsg& dragNotifyMsg, const DragStatus dragStatus)
{
    LOGI("AceDrag, drag notify message result is %{public}d.", dragNotifyMsg.result);
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
    auto container = Ace::AceEngine::Get().GetContainer(asyncCtx->instanceId);
    CHECK_NULL_VOID(container);
    if (dragStatus == DragStatus::ENDED) {
        auto pipelineContext = container->GetPipelineContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->ResetDragging();
    }
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostSyncTask(
        [asyncCtx, dragNotifyMsg, dragStatus]() {
            CHECK_NULL_VOID(asyncCtx);
            CallBackJsFunction(asyncCtx, dragNotifyMsg, dragStatus);
        },
        TaskExecutor::TaskType::JS, "ArkUIDragHandleSuccess");
}

void HandleFail(std::shared_ptr<DragControllerAsyncCtx> asyncCtx, int32_t errCode, const std::string& errMsg)
{
    CHECK_NULL_VOID(asyncCtx);
    CHECK_NULL_VOID(asyncCtx->env);
    bool hasHandle = false;
    {
        std::lock_guard<std::mutex> lock(asyncCtx->mutex);
        hasHandle = asyncCtx->hasHandle;
        asyncCtx->hasHandle = true;
    }
    if (hasHandle) {
        return;
    }
    if (ANI_OK != asyncCtx->env->CreateLocalScope(Ani::SPECIFIED_CAPACITY)) {
        return;
    }
    auto errObj = Ani::GetErrorObject(asyncCtx->env, errMsg, errCode);
    if (errObj == nullptr) {
        LOGE("AceDrag, get error object failed!");
        asyncCtx->env->DestroyLocalScope();
        return;
    }
    if (asyncCtx->asyncCallback) { // asyncCallback
        std::vector<ani_ref> resultRef(PARAMETER_NUM);
        resultRef[0] = reinterpret_cast<ani_ref>(errObj);
        asyncCtx->env->GetUndefined(&resultRef[1]);
        ani_ref fnReturnVal;
        asyncCtx->env->FunctionalObject_Call(asyncCtx->asyncCallback, resultRef.size(), resultRef.data(), &fnReturnVal);
        asyncCtx->env->GlobalReference_Delete(asyncCtx->asyncCallback);
    } else { // promise
        asyncCtx->env->PromiseResolver_Reject(asyncCtx->deferred, errObj);
    }
    asyncCtx->env->DestroyLocalScope();
}

void LogDragInfoInner(std::shared_ptr<DragControllerAsyncCtx> asyncCtx, const Msdp::DeviceStatus::DragData& dragData)
{
    auto pixelMap = dragData.shadowInfos[0].pixelMap;
    std::string summarys = DragDropFuncWrapper::GetSummaryString(dragData.summarys);
    LOGI("dragData, pixelMap width %{public}d height %{public}d, udkey %{public}s, recordSize %{public}d, "
        "extraParams length %{public}d, pointerId %{public}d, toolType %{public}d, summary %{public}s, "
        "eventId %{public}d",
        pixelMap->GetWidth(), pixelMap->GetHeight(),
        DragDropFuncWrapper::GetAnonyString(dragData.udKey).c_str(), dragData.dragNum,
        static_cast<int32_t>(asyncCtx->extraParams.length()), asyncCtx->dragPointerEvent.pointerId,
        static_cast<int32_t>(asyncCtx->dragPointerEvent.sourceTool), summarys.c_str(),
        asyncCtx->dragPointerEvent.pointerEventId);
}

std::shared_ptr<Media::PixelMap> CopyMediaPixelMap(const RefPtr<PixelMap>& pixelMap)
{
    CHECK_NULL_RETURN(pixelMap, nullptr);
    OHOS::Media::InitializationOptions opts;
    auto mediaPixelMap = pixelMap->GetPixelMapSharedPtr();
    std::unique_ptr<Media::PixelMap> uniquePixelMap = Media::PixelMap::Create(*mediaPixelMap, opts);
    CHECK_NULL_RETURN(uniquePixelMap, nullptr);
    Media::PixelMap* pixelMapRelease = uniquePixelMap.release();
    CHECK_NULL_RETURN(pixelMapRelease, nullptr);
    std::shared_ptr<Media::PixelMap> newPixelMap(pixelMapRelease);
    CHECK_NULL_RETURN(newPixelMap, nullptr);
    return newPixelMap;
}

bool GetShadowInfo(std::shared_ptr<DragControllerAsyncCtx> asyncCtx, Msdp::DeviceStatus::ShadowInfo& shadowInfo,
    RefPtr<PixelMap> refPixelMap, float scale)
{
    CHECK_NULL_RETURN(asyncCtx, false);
    auto pixelMapDuplicated = CopyMediaPixelMap(refPixelMap);
    if (!pixelMapDuplicated) {
        LOGE("AceDrag, duplicate PixelMap failed!");
        pixelMapDuplicated = asyncCtx->pixelMap;
    }
    CHECK_NULL_RETURN(pixelMapDuplicated, false);
    pixelMapDuplicated->scale(scale, scale, Media::AntiAliasingOption::HIGH);
    int32_t width = pixelMapDuplicated->GetWidth();
    int32_t height = pixelMapDuplicated->GetHeight();
    CHECK_NULL_RETURN(pixelMapDuplicated, false);
    double x = ConvertToPx(asyncCtx, asyncCtx->touchPoint->GetX(), width);
    double y = ConvertToPx(asyncCtx, asyncCtx->touchPoint->GetY(), height);
    if (!asyncCtx->touchPoint.has_value()) {
        x = -width * PIXELMAP_WIDTH_RATE;
        y = -height * PIXELMAP_HEIGHT_RATE;
    } else if (x < 0 || y < 0 || x > static_cast<double>(width) || y > static_cast<double>(height)) {
        HandleFail(asyncCtx, ERROR_CODE_PARAM_INVALID, "touchPoint's coordinate out of range");
        return false;
    }
    shadowInfo = { pixelMapDuplicated, -x, -y };
    return true;
}
bool CreatePreviewNodeAndScale(std::shared_ptr<DragControllerAsyncCtx> asyncCtx,
    NG::PreparedInfoForDrag& data, NG::PreparedAsyncCtxForAnimate& asyncCtxData,
    Msdp::DeviceStatus::ShadowInfo& shadowInfo, std::shared_ptr<Media::PixelMap> pixelMap)
{
    CHECK_NULL_RETURN(asyncCtx, false);
    auto container = AceEngine::Get().GetContainer(asyncCtx->instanceId);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto dragNodePipeline = AceType::DynamicCast<NG::PipelineContext>(pipeline);
    CHECK_NULL_RETURN(dragNodePipeline, false);
    auto scaleData =
        NG::DragControllerFuncWrapper::GetScaleInfo(asyncCtx->instanceId, pixelMap->GetWidth(), pixelMap->GetHeight());
    CHECK_NULL_RETURN(scaleData, false);
    auto scale = asyncCtx->windowScale;
    CHECK_NULL_RETURN(pixelMap, false);
    RefPtr<PixelMap> refPixelMap = PixelMap::CreatePixelMap(reinterpret_cast<void*>(&pixelMap));
    CHECK_NULL_RETURN(refPixelMap, false);
    auto badgeNumber = asyncCtx->dragPreviewOption.GetCustomerBadgeNumber();
    if (badgeNumber.has_value()) {
        asyncCtx->badgeNumber = badgeNumber.value();
    }
    data = { false, asyncCtx->badgeNumber, 1.0f, false,
        NG::OffsetF(), NG::DragControllerFuncWrapper::GetUpdateDragMovePosition(asyncCtx->instanceId), refPixelMap };
    NG::DragControllerFuncWrapper::ResetContextMenuDragPosition(asyncCtx->instanceId);
    if (scaleData->isNeedScale && asyncCtx->dragPreviewOption.isScaleEnabled) {
        auto overlayManager = dragNodePipeline->GetOverlayManager();
        auto imageNode = overlayManager->GetPixelMapContentNode();
        scale = scaleData->scale * asyncCtx->windowScale;
        data.previewScale = scale;
        NG::DragControllerFuncWrapper::CreatePreviewNode(imageNode, data, asyncCtxData);
        CHECK_NULL_RETURN(imageNode, false);
        data.imageNode = imageNode;
        data.dragPreviewOffsetToScreen = NG::DragControllerFuncWrapper::GetOriginNodeOffset(data, asyncCtxData);
    }
    if (!GetShadowInfo(asyncCtx, shadowInfo, refPixelMap, scale)) {
        return false;
    }
    asyncCtxData = {asyncCtx->instanceId, asyncCtx->touchPoint.has_value(), asyncCtx->dragPointerEvent,
        asyncCtx->dragPreviewOption, asyncCtx->touchPoint.value(), asyncCtx->pixelMapList};
    return true;
}

void HandleOnDragStart(std::shared_ptr<DragControllerAsyncCtx> asyncCtx)
{
    ContainerScope scope(asyncCtx->instanceId);
    auto container = Ace::AceEngine::Get().GetContainer(Ace::Container::CurrentIdSafely());
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [ctx = asyncCtx, context = pipelineContext]() {
            context->OnDragEvent({ ctx->dragPointerEvent.displayX, ctx->dragPointerEvent.displayY },
                DragEventAction::DRAG_EVENT_START_FOR_CONTROLLER);
            DragDropFuncWrapper::DecideWhetherToStopDragging(
                { ctx->dragPointerEvent.displayX, ctx->dragPointerEvent.displayY }, ctx->extraParams,
                ctx->dragPointerEvent.pointerId, ctx->instanceId);
        },
        TaskExecutor::TaskType::UI, "ArkUIDragHandleDragEventStart", PriorityType::VIP);
}

void ExecuteHandleOnDragStart(std::shared_ptr<DragControllerAsyncCtx> asyncCtx)
{
    CHECK_NULL_VOID(asyncCtx);
    std::lock_guard<std::mutex> lock(asyncCtx->dragStateMutex);
    if (asyncCtx->dragState == DragState::SENDING) {
        asyncCtx->dragState = DragState::SUCCESS;
        if (!asyncCtx->isSwitchedToSubWindow) {
            Msdp::DeviceStatus::InteractionManager::GetInstance()->SetDragWindowVisible(true);
        }
        HandleOnDragStart(asyncCtx);
    }
}

static void SetIsDragging(const RefPtr<Container>& container, bool isDragging)
{
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->SetIsDragging(isDragging);
}

void HideDragPreviewWindow(std::shared_ptr<DragControllerAsyncCtx> asyncCtx)
{
    auto container = Ace::AceEngine::Get().GetContainer(Ace::Container::CurrentIdSafely());
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [asyncCtx]() {
            DragControllerFuncWrapper::HideDragPreviewWindow(asyncCtx->instanceId);
        },
        TaskExecutor::TaskType::UI, "ArkUIHideDragPreviewWindow", PriorityType::VIP);
}

int32_t SetUnifiedData(
    std::shared_ptr<DragControllerAsyncCtx> asyncCtx, std::string& udKey, std::map<std::string, int64_t>& summary)
{
    int32_t dataSize = 1;
    CHECK_NULL_RETURN(asyncCtx, dataSize);
    if (asyncCtx->unifiedData) {
        // int32_t ret =
        //     UdmfClient::GetInstance()->SetData(asyncCtx->unifiedData, udKey);
        // if (ret != 0) {
        //     LOGE("AceDrag, udmf set data failed, return value is %{public}d", ret);
        // } else {
        //     ret = UdmfClient::GetInstance()->GetSummary(udKey, summary);
        //     if (ret != 0) {
        //         LOGE("AceDrag, get summary failed, return value is %{public}d", ret);
        //     }
        // }
        // dataSize = static_cast<int32_t>(asyncCtx->unifiedData->GetSize());
    }
    auto badgeNumber = asyncCtx->dragPreviewOption.GetCustomerBadgeNumber();
    if (badgeNumber.has_value()) {
        dataSize = badgeNumber.value();
    }
    return dataSize;
}

bool EnvelopedDragData(std::shared_ptr<DragControllerAsyncCtx> asyncCtx,
    std::optional<Msdp::DeviceStatus::DragData>& dragData, std::vector<Msdp::DeviceStatus::ShadowInfo>& shadowInfos)
{
    if (shadowInfos.empty()) {
        LOGE("AceDrag, shadowInfo array is empty");
        return false;
    }
    
    auto container = Ace::AceEngine::Get().GetContainer(asyncCtx->instanceId);
    CHECK_NULL_RETURN(container, false);
    if (!container->GetLastMovingPointerPosition(asyncCtx->dragPointerEvent)) {
        HandleFail(asyncCtx, ERROR_CODE_INTERNAL_ERROR, "can not find current pointerId or not in press");
        return false;
    }
    std::string udKey;
    std::map<std::string, int64_t> summary;
    int32_t dataSize = SetUnifiedData(asyncCtx, udKey, summary);
    int32_t recordSize = (dataSize != 0 ? dataSize : static_cast<int32_t>(shadowInfos.size()));
    auto windowId = container->GetWindowId();
    auto arkExtraInfoJson = JsonUtil::Create(true);
    arkExtraInfoJson->Put("dip_scale", asyncCtx->dipScale);
    arkExtraInfoJson->Put("event_id", asyncCtx->dragPointerEvent.pointerEventId);
    DragDropFuncWrapper::UpdateExtraInfo(arkExtraInfoJson, asyncCtx->dragPreviewOption);
    // dragData = { shadowInfos, {}, udKey, asyncCtx->extraParams, arkExtraInfoJson->ToString(),
    //     asyncCtx->dragPointerEvent.sourceType, recordSize, asyncCtx->dragPointerEvent.pointerId,
    //     static_cast<int32_t>(asyncCtx->dragPointerEvent.sourceTool), asyncCtx->dragPointerEvent.displayX,
    //     asyncCtx->dragPointerEvent.displayY, asyncCtx->dragPointerEvent.displayId, windowId, true, false, summary };
    return true;
}

bool StartDragService(std::shared_ptr<DragControllerAsyncCtx> asyncCtx)
{
    CHECK_NULL_RETURN(asyncCtx, false);
    auto container = Ace::AceEngine::Get().GetContainer(asyncCtx->instanceId);
    CHECK_NULL_RETURN(container, false);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipeline, false);
    NG::PreparedInfoForDrag data;
    NG::PreparedAsyncCtxForAnimate asyncCtxData;
    std::vector<Msdp::DeviceStatus::ShadowInfo> shadowInfos;
    Msdp::DeviceStatus::ShadowInfo shadowInfo;
    asyncCtxData = {asyncCtx->instanceId, asyncCtx->touchPoint.has_value(), asyncCtx->dragPointerEvent,
        asyncCtx->dragPreviewOption, asyncCtx->touchPoint.value(), asyncCtx->pixelMapList};
    for (auto& pixelMap : asyncCtx->pixelMapList) {
        if (!pixelMap) {
            LOGE("AceDrag, skip null pixelMap");
            continue;
        }
        if (!CreatePreviewNodeAndScale(asyncCtx, data, asyncCtxData, shadowInfo, pixelMap)) {
            return false;
        }
        shadowInfos.push_back(shadowInfo);
    }
    // auto subWindow = DragControllerFuncWrapper::SubWindowShow(pipeline);
    std::optional<Msdp::DeviceStatus::DragData> dragData;
    if (!EnvelopedDragData(asyncCtx, dragData, shadowInfos)) {
        return false;
    }
    data.badgeNumber = dragData->dragNum;
    OnDragCallback callback = [asyncCtx](const DragNotifyMsg& dragNotifyMsg) {
        HideDragPreviewWindow(asyncCtx);
        HandleSuccess(asyncCtx, dragNotifyMsg, DragStatus::ENDED);
    };
    DragDropFuncWrapper::SetDraggingPointerAndPressedState(
        asyncCtx->dragPointerEvent.pointerId, asyncCtx->instanceId);
    DragDropFuncWrapper::SetExtraInfo(asyncCtx->instanceId, asyncCtx->extraParams);
    LogDragInfoInner(asyncCtx, dragData.value());
    auto result = Msdp::DeviceStatus::InteractionManager::GetInstance()->StartDrag(
        dragData.value(), std::make_shared<OHOS::Ace::StartDragListenerImpl>(callback));
    if (result != 0) {
        HandleFail(asyncCtx, ERROR_CODE_INTERNAL_ERROR, "msdp start drag failed.");
        return false;
    }
    // if (DragControllerFuncWrapper::TryDoDragStartAnimation(subWindow, data, asyncCtxData)) {
    //     asyncCtx->isSwitchedToSubWindow = true;
    // }
    return true;
}

void OnMultipleComplete(std::shared_ptr<DragControllerAsyncCtx> asyncCtx)
{
    CHECK_NULL_VOID(asyncCtx);
    
    auto container = Ace::AceEngine::Get().GetContainer(asyncCtx->instanceId);
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto windowScale = container->GetWindowScale();
    asyncCtx->windowScale = windowScale;
    taskExecutor->PostTask(
        [asyncCtx]() {
            LOGI("AceDrag, try to start msdp drag.");
            CHECK_NULL_VOID(asyncCtx);
            ContainerScope scope(asyncCtx->instanceId);
            DragState dragState = DragState::PENDING;
            {
                std::lock_guard<std::mutex> lock(asyncCtx->dragStateMutex);
                if (asyncCtx->dragState == DragState::PENDING) {
                    asyncCtx->dragState = DragState::SENDING;
                }
                dragState = asyncCtx->dragState;
            }
            if (dragState == DragState::REJECT) {
                HandleFail(asyncCtx, ERROR_CODE_INTERNAL_ERROR, "drag state is reject.");
                return;
            }
            if (!StartDragService(asyncCtx)) {
                LOGE("AceDrag, msdp start drag failed.");
                return;
            }
            HandleSuccess(asyncCtx, DragNotifyMsg {}, DragStatus::STARTED);
            
            auto container = Ace::AceEngine::Get().GetContainer(asyncCtx->instanceId);
            CHECK_NULL_VOID(container);
            SetIsDragging(container, true);
            LOGI("AceDrag, msdp start drag successfully");
            ExecuteHandleOnDragStart(asyncCtx);
        },
        TaskExecutor::TaskType::JS, "ArkUIDragMultipleComplete", PriorityType::VIP);
}

void CreatePixelMapArrayByCustom(
    std::shared_ptr<DragControllerAsyncCtx> asyncCtx, ArkUINodeHandle customBuilder, int arrayLength)
{
    CHECK_NULL_VOID(asyncCtx);
    
    auto callback = [asyncCtx, arrayLength](std::shared_ptr<Media::PixelMap> pixelMap, int32_t errCode,
                        std::function<void()> finishCallback) {
        CHECK_NULL_VOID(asyncCtx);
        auto container = Ace::AceEngine::Get().GetContainer(asyncCtx->instanceId);
        CHECK_NULL_VOID(container);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [finishCallback]() {
                CHECK_NULL_VOID(finishCallback);
                finishCallback();
            },
            TaskExecutor::TaskType::JS, "ArkUICreatePixelMapArrayByCustom");
        asyncCtx->parseBuilderCount++;
        CHECK_NULL_VOID(pixelMap);
        asyncCtx->pixelMapList.push_back(std::move(pixelMap));
        if (asyncCtx->parseBuilderCount == arrayLength) {
            OnMultipleComplete(asyncCtx);
        }
    };
    NG::SnapshotParam param;
    param.delay = CREATE_PIXELMAP_DELAY_TIME;
    param.checkImageStatus = true;
    param.options.waitUntilRenderFinished = true;
    auto uinode = AceType::Claim(reinterpret_cast<UINode *>(customBuilder));
    CHECK_NULL_VOID(uinode);
    ComponentSnapshot::Create(uinode, std::move(callback), true, param);
}

std::optional<Dimension> ConvertDimensionType(ani_env* env, ani_ref touchPoint)
{
    if (Ani::IsUndefinedObject(env, touchPoint)) {
        return std::nullopt;
    }
    Dimension parameter;
    if (Ani::IsNumberObject(env, touchPoint)) {
        ani_double numberValue;
        env->Object_CallMethodByName_Double(static_cast<ani_object>(touchPoint), "unboxed", ":D", &numberValue);
        parameter.SetValue(static_cast<double>(numberValue));
        parameter.SetUnit(DimensionUnit::VP);
        return parameter;
    }
    if (Ani::IsStringObject(env, touchPoint)) {
        auto parameterStr = Ani::ANIUtils_ANIStringToStdString(env, static_cast<ani_string>(touchPoint));
        parameter = StringUtils::StringToDimensionWithUnit(parameterStr, DimensionUnit::VP);
        return parameter;
    }
    return std::nullopt;
}

bool SetDragPreviewOptionMode(
    ani_env* env, std::shared_ptr<DragControllerAsyncCtx> asyncCtx, ani_object dragPreviewMode, bool& isAuto)
{
    CHECK_NULL_RETURN(asyncCtx, false);
    if (isAuto) {
        return true;
    }
    ani_int dragPreviewModeAni;
    env->EnumItem_GetValue_Int(static_cast<ani_enum_item>(dragPreviewMode), &dragPreviewModeAni);
    auto mode = static_cast<NG::DragPreviewMode>(dragPreviewModeAni);
    switch (mode) {
        case NG::DragPreviewMode::AUTO:
            asyncCtx->dragPreviewOption.ResetDragPreviewMode();
            isAuto = true;
            break;
        case NG::DragPreviewMode::DISABLE_SCALE:
            asyncCtx->dragPreviewOption.isScaleEnabled = false;
            break;
        case NG::DragPreviewMode::ENABLE_DEFAULT_SHADOW:
            asyncCtx->dragPreviewOption.isDefaultShadowEnabled = true;
            break;
        case NG::DragPreviewMode::ENABLE_DEFAULT_RADIUS:
            asyncCtx->dragPreviewOption.isDefaultRadiusEnabled = true;
            break;
        default:
            break;
    }
    return true;
}

bool ParseDragPreviewMode(ani_env* env, std::shared_ptr<DragControllerAsyncCtx> asyncCtx,
    ani_object previewModeObj)
{
    if (Ani::IsUndefinedObject(env, previewModeObj)) {
        return true;
    }
    bool isAuto = false;
    if (Ani::IsArrayObject(env, previewModeObj)) {
        ani_double lengthAni;
        if (ANI_OK != env->Object_GetPropertyByName_Double(previewModeObj, "length", &lengthAni)) {
            LOGE("AceDrag, Object_GetPropertyByName_Double failed.");
        }
        for (int32_t i = 0; i < int32_t(lengthAni); i++) {
            ani_ref modeRef;
            if (ANI_OK != env->Object_CallMethodByName_Ref(
                previewModeObj, "$_get", "I:Lstd/core/Object;", &modeRef, (ani_int)i)) {
                LOGE("AceDrag, Object_CallMethodByName_Ref failed.");
            }
            if (Ani::IsUndefinedObject(env, modeRef)) {
                continue;
            }
            if (!SetDragPreviewOptionMode(env, asyncCtx, static_cast<ani_object>(modeRef), isAuto)) {
                LOGE("AceDrag, SetDragPreviewOptionMode failed.");
                return false;
            }
        }
    } else if (!SetDragPreviewOptionMode(env, asyncCtx, previewModeObj, isAuto)) {
        LOGE("AceDrag, SetDragPreviewOptionMode failed.");
        return false;
    }
    NG::DragDropFuncWrapper::UpdatePreviewOptionDefaultAttr(asyncCtx->dragPreviewOption);
    return true;
}

bool ParseNumberBadge(ani_env* env, std::shared_ptr<DragControllerAsyncCtx> asyncCtx, ani_object numberBadgeAni)
{
    CHECK_NULL_RETURN(asyncCtx, false);
    ani_status status = ANI_OK;
    if (Ani::IsBooleanObject(env, numberBadgeAni)) {
        ani_boolean aniValue;
        env->Object_CallMethodByName_Boolean(numberBadgeAni, "booleanValue", nullptr, &aniValue);
        asyncCtx->dragPreviewOption.isNumber = false;
        asyncCtx->dragPreviewOption.isShowBadge = static_cast<bool>(aniValue);
    } else if (Ani::IsNumberObject(env, numberBadgeAni)) {
        ani_double numberValue;
        if ((status = env->Object_CallMethodByName_Double(
            static_cast<ani_object>(numberBadgeAni), "unboxed", ":D", &numberValue)) != ANI_OK) {
            LOGE("AceDrag, Object_CallMethodByName_Double failed. status = %{public}d", status);
        }
        auto number = static_cast<double>(numberValue);
        if (number < 0 || number > INT_MAX) {
            asyncCtx->dragPreviewOption.isNumber = false;
            asyncCtx->dragPreviewOption.isShowBadge = true;
        } else {
            asyncCtx->dragPreviewOption.isNumber = true;
            asyncCtx->dragPreviewOption.badgeNumber = static_cast<int32_t>(number);
        }
    } else if (!Ani::IsUndefinedObject(env, numberBadgeAni)) {
        LOGE("AceDrag, numberBadge type is wrong.");
        return false;
    }
    return true;
}

bool ParseModifier(ani_env* env, std::shared_ptr<DragControllerAsyncCtx> asyncCtx, ani_object modifierObj)
{
    if (Ani::IsUndefinedObject(env, modifierObj)) {
        return true;
    }

    ani_ref modifierFunc;
    env->Object_GetPropertyByName_Ref(modifierObj, "applyImageModifierToNode", &modifierFunc);
    // modifierFunc may have two args
    if (!Ani::IsFunctionObjectWith2Param(env, modifierFunc)) {
        LOGE("AceDrag, applyImageModifierToNode is not a function object.");
        return false;
    }

    auto applyOnNodeSync =
        [modifierObj, modifierFunc, asyncCtx](WeakPtr<NG::FrameNode> frameNode) {
            // convert nodeptr to js value
            LOGE("AceDrag, modifier has not been implemented yet.");
        };
    NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, asyncCtx->dragPreviewOption);
    return true;
}

bool ParsePreviewOptions(ani_env* env, std::shared_ptr<DragControllerAsyncCtx> asyncCtx, ani_object previewOptions)
{
    CHECK_NULL_RETURN(env, false);
    CHECK_NULL_RETURN(asyncCtx, false);
    if (Ani::IsUndefinedObject(env, previewOptions)) {
        return true;
    }
    asyncCtx->dragPreviewOption.isNumber = false;
    asyncCtx->dragPreviewOption.isShowBadge = true;

    ani_ref modeAni;
    ani_ref numberBadgeAni;
    ani_ref modifierAni;
    env->Object_GetPropertyByName_Ref(previewOptions, "mode", &modeAni);
    env->Object_GetPropertyByName_Ref(previewOptions, "numberBadge", &numberBadgeAni);
    env->Object_GetPropertyByName_Ref(previewOptions, "modifier", &modifierAni);

    if (!ParseDragPreviewMode(env, asyncCtx, static_cast<ani_object>(modeAni))) {
        LOGE("AceDrag, parse mode parameter failed.");
        return false;
    }
    if (!ParseNumberBadge(env, asyncCtx, static_cast<ani_object>(numberBadgeAni))) {
        LOGE("AceDrag, parse numberBadge parameter failed.");
        return false;
    }
    if (!ParseModifier(env, asyncCtx, static_cast<ani_object>(modifierAni))) {
        LOGE("AceDrag, parse modifier parameter failed.");
        return false;
    }
    return true;
}

bool CreateCallbackFunc(
    ani_env* env, std::shared_ptr<DragControllerAsyncCtx> asyncCtx, ani_object callback, ani_object& result)
{
    CHECK_NULL_RETURN(asyncCtx, false);
    if (Ani::IsFunctionObjectWith2Param(env, callback)) {
        LOGI("AceDrag, Create async callback");
        ani_ref fnObjGlobalRef = nullptr;
        env->GlobalReference_Create(callback, &fnObjGlobalRef);
        asyncCtx->asyncCallback = static_cast<ani_fn_object>(fnObjGlobalRef);
        return true;
    } else if (callback == nullptr) {
        LOGI("AceDrag, create promise object");
        if (ANI_OK != env->Promise_New(&asyncCtx->deferred, &result)) {
            LOGE("AceDrag, create promise object failed!");
            return false;
        }
    } else {
        LOGE("AceDrag, third parameter is not function.");
        return false;
    }
    return true;
}

RefPtr<OHOS::Ace::UnifiedData> TransformUnifiedDataFormANI(ani_env* env, ani_object dataObj)
{
    // CHECK_NULL_RETURN(env, nullptr);
    // auto unifiedData = OHOS::UDMF::AniConverter::UnwrapUnifiedData(env, dataObj);
    // if (!unifiedData) {
    //     return nullptr;
    // }
    // auto udData = AceType::MakeRefPtr<UnifiedDataImpl>();
    // udData->SetUnifiedData(unifiedData);
    // return udData;
    return nullptr;
}

void GetCurrentDipScale(std::shared_ptr<DragControllerAsyncCtx> asyncCtx)
{
    auto container = AceEngine::Get().GetContainer(asyncCtx->instanceId);
    CHECK_NULL_VOID(container);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_VOID(pipeline);
    asyncCtx->dipScale = pipeline->GetDipScale();
}

bool CheckAndParseSecondParams(ani_env* env, std::shared_ptr<DragControllerAsyncCtx> asyncCtx, ani_object dragInfo)
{
    CHECK_NULL_RETURN(asyncCtx, false);
    if (Ani::IsUndefinedObject(env, dragInfo)) {
        return false;
    }
    ani_double pointerIdAni;
    ani_ref extraParamsAni;
    ani_ref dataAni;
    ani_ref touchPointAni;
    ani_ref previewOptionsAni;
    if (ANI_OK != env->Object_GetPropertyByName_Double(dragInfo, "pointerId", &pointerIdAni)) {
        LOGE("AceDrag, get pointerId failed.");
        return false;
    }
    if (ANI_OK != env->Object_GetPropertyByName_Ref(dragInfo, "extraParams", &extraParamsAni)) {
        LOGE("AceDrag, get extraParams failed.");
        return false;
    }
    if (ANI_OK != env->Object_GetPropertyByName_Ref(dragInfo, "data", &dataAni)) {
        LOGE("AceDrag, get data failed.");
        return false;
    }
    if (ANI_OK != env->Object_GetPropertyByName_Ref(dragInfo, "touchPoint", &touchPointAni)) {
        LOGE("AceDrag, get touchPoint failed.");
        return false;
    }
    if (ANI_OK != env->Object_GetPropertyByName_Ref(dragInfo, "previewOptions", &previewOptionsAni)) {
        LOGE("AceDrag, get previewOptions failed.");
        return false;
    }

    asyncCtx->dragPointerEvent.pointerId = static_cast<int32_t>(pointerIdAni);
    LOGI("AceDrag, pointerId = %{public}d", asyncCtx->dragPointerEvent.pointerId);
    if (Ani::IsStringObject(env, extraParamsAni)) {
        asyncCtx->extraParams = Ani::ANIUtils_ANIStringToStdString(env, static_cast<ani_string>(extraParamsAni));
    }
    if (!Ani::IsUndefinedObject(env, dataAni)) {
        asyncCtx->unifiedData = TransformUnifiedDataFormANI(env, static_cast<ani_object>(dataAni));
    }

    ani_ref pointXAni;
    ani_ref pointYAni;
    env->Object_GetPropertyByName_Ref(static_cast<ani_object>(touchPointAni), "x", &pointXAni);
    env->Object_GetPropertyByName_Ref(static_cast<ani_object>(touchPointAni), "y", &pointYAni);

    std::optional<Dimension> dx = ConvertDimensionType(env, pointXAni);
    std::optional<Dimension> dy = ConvertDimensionType(env, pointYAni);
    if (dx.has_value() && dy.has_value()) {
        asyncCtx->touchPoint = DimensionOffset(dx.value(), dy.value());
    }
    if (!ParsePreviewOptions(env, asyncCtx, static_cast<ani_object>(previewOptionsAni))) {
        LOGE("AceDrag, parse previewOptions failed.");
        return false;
    }
    GetCurrentDipScale(asyncCtx);
    return true;
}

bool ParseDragItemInfoParam(ani_env* env, std::shared_ptr<DragControllerAsyncCtx> asyncCtx, ani_object dragItemInfo)
{
    CHECK_NULL_RETURN(env, false);
    CHECK_NULL_RETURN(asyncCtx, false);
    ani_ref pixelMapAni;
    ani_ref extraInfoAni;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(dragItemInfo, "pixelMap", &pixelMapAni)) {
        LOGE("AceDrag, get pixelMap failed.");
        return false;
    }
    if (ANI_OK != env->Object_GetPropertyByName_Ref(dragItemInfo, "extraInfo", &extraInfoAni)) {
        LOGE("AceDrag, get extraInfo failed.");
        return false;
    }
    if (Ani::IsStringObject(env, extraInfoAni)) {
        asyncCtx->extraParams = Ani::ANIUtils_ANIStringToStdString(env, static_cast<ani_string>(extraInfoAni));
    }
    if (!Ani::IsUndefinedObject(env, pixelMapAni)) {
        // auto nativePixelMap =
        //     OHOS::Media::PixelMapTaiheAni::GetNativePixelMap(env, reinterpret_cast<ani_object>(pixelMapAni));
        // if (nativePixelMap) {
        //     if (asyncCtx->isArray) {
        //         asyncCtx->pixelMapList.emplace_back(nativePixelMap);
        //     } else {
        //         asyncCtx->pixelMap = nativePixelMap;
        //     }
        // } else {
        //     LOGE("AceDrag, get native pixelMap from taiheAni is null.");
        //     return false;
        // }
        return false;
    }
    return true;
}

bool ParseDragMixParam(ani_env* env, std::shared_ptr<DragControllerAsyncCtx> asyncCtx, ani_object dragItemInfo,
    ani_object builderObj, ani_double builderArrayLength, ani_double dragItemInfoArrayLength)
{
    bool isParseSucess = true;
    ani_status status = ANI_OK;
    int32_t dragItemInfoArrayLengthInt = static_cast<int32_t>(std::ceil(dragItemInfoArrayLength));
    int32_t builderArrayLengthInt = static_cast<int32_t>(std::ceil(builderArrayLength));
    if (dragItemInfoArrayLengthInt > 0 || builderArrayLengthInt > 0) {
        for (int32_t i = 0; i < builderArrayLengthInt; i++) {
            ani_ref itemRef;
            if ((status = env->Object_CallMethodByName_Ref(static_cast<ani_object>(builderObj), "$_get",
                "i:C{std.core.Object}", &itemRef, (ani_int)i)) != ANI_OK) {
                LOGE("AceDrag, get builder node from array fail. status = %{public}d", status);
                isParseSucess = false;
                break;
            }
            if (Ani::IsUndefinedObject(env, itemRef)) {
                LOGE("AceDrag, get builder node from array is undefined.");
                isParseSucess = false;
                break;
            }
            ani_long builderPtr;
            if (!Ani::GetBigIntValue(env, static_cast<ani_object>(itemRef), builderPtr)) {
                LOGE("AceDrag, get builder node value from array fail.");
                isParseSucess = false;
                break;
            }
            asyncCtx->customBuilderNodeList.emplace_back(reinterpret_cast<ArkUINodeHandle>(builderPtr));
        }
        for (int32_t i = 0; i < dragItemInfoArrayLengthInt; i++) {
            ani_ref itemRef;
            if ((status = env->Object_CallMethodByName_Ref(
                dragItemInfo, "$_get", "I:Lstd/core/Object;", &itemRef, (ani_int)i)) != ANI_OK) {
                LOGE("AceDrag, get dragItemInfo from array fail. status = %{public}d", status);
                isParseSucess = false;
                break;
            }
            if (Ani::IsUndefinedObject(env, itemRef)) {
                LOGE("AceDrag, get dragItemInfo from array is undefined.");
                isParseSucess = false;
                break;
            }
            if (!ParseDragItemInfoParam(env, asyncCtx, static_cast<ani_object>(itemRef))) {
                LOGE("AceDrag, parse dragItemInfo value from array fail.");
                isParseSucess = false;
                break;
            }
        }
    } else {
        isParseSucess = false;
    }
    return isParseSucess;
}

bool ParseDragItemListInfoParam(ani_env* env, std::shared_ptr<DragControllerAsyncCtx> asyncCtx, ani_object dragItemInfo,
    ani_object builderObj)
{
    CHECK_NULL_RETURN(env, false);
    CHECK_NULL_RETURN(asyncCtx, false);
    ani_double builderArrayLength;
    ani_double dragItemInfoArrayLength;
    ani_status status = ANI_OK;
    if ((status = env->Object_GetPropertyByName_Double(builderObj, "length", &builderArrayLength)) != ANI_OK) {
        LOGE("AceDrag, get builder array length fail. status = %{public}d", status);
        return false;
    }
    if ((status = env->Object_GetPropertyByName_Double(dragItemInfo, "length", &dragItemInfoArrayLength)) != ANI_OK) {
        LOGE("AceDrag, get dragItemInfo array length fail. status = %{public}d", status);
        return false;
    }
    return ParseDragMixParam(env, asyncCtx, dragItemInfo, builderObj, builderArrayLength, dragItemInfoArrayLength);
}

bool CheckAndParseFirstParams(ani_env* env, std::shared_ptr<DragControllerAsyncCtx> asyncCtx, ani_object dragItemInfo,
    ArkUINodeHandle builderNode, ani_object builderNodeArray)
{
    CHECK_NULL_RETURN(env, false);
    CHECK_NULL_RETURN(asyncCtx, false);
    if (Ani::IsUndefinedObject(env, dragItemInfo)) {
        return false;
    }
    if (builderNode) {
        asyncCtx->customBuilderNode = builderNode;
        return true;
    }
    if (Ani::IsArrayObject(env, dragItemInfo) || Ani::IsArrayObject(env, builderNodeArray)) {
        asyncCtx->isArray = true;
        LOGI("AceDrag, drag controller is multi object drag.");
        return ParseDragItemListInfoParam(env, asyncCtx, dragItemInfo, builderNodeArray);
    }
    asyncCtx->isArray = false;
    return ParseDragItemInfoParam(env, asyncCtx, dragItemInfo);
}

void HandleStopDragCallback(std::shared_ptr<DragControllerAsyncCtx> asyncCtx, const RefPtr<Container>& container)
{
    CHECK_NULL_VOID(asyncCtx);
    CHECK_NULL_VOID(container);
    bool needPostStopDrag = false;
    {
        std::lock_guard<std::mutex> lock(asyncCtx->dragStateMutex);
        needPostStopDrag = (asyncCtx->dragState == DragState::SENDING);
        asyncCtx->dragState = DragState::REJECT;
    }
    if (needPostStopDrag) {
        auto pipelineContext = container->GetPipelineContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->ResetDragging();
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        auto windowId = container->GetWindowId();
        taskExecutor->PostTask(
            [asyncCtx, windowId]() {
                CHECK_NULL_VOID(asyncCtx);
                HandleFail(asyncCtx, ERROR_CODE_PARAM_INVALID, "drag state is reject, stop drag.");
                LOGI("drag state is reject, stop drag, windowId is %{public}d.", windowId);
                Msdp::DeviceStatus::DragDropResult dropResult { Msdp::DeviceStatus::DragResult::DRAG_CANCEL, false,
                    windowId, Msdp::DeviceStatus::DragBehavior::UNKNOWN };
                Msdp::DeviceStatus::InteractionManager::GetInstance()->StopDrag(dropResult);
                Msdp::DeviceStatus::InteractionManager::GetInstance()->SetDragWindowVisible(false);
            },
            TaskExecutor::TaskType::JS, "ArkUIDragStop", PriorityType::VIP);
    }
}

bool ConfirmCurPointerEventInfo(std::shared_ptr<DragControllerAsyncCtx> asyncCtx, const RefPtr<Container>& container)
{
    CHECK_NULL_RETURN(asyncCtx, false);
    CHECK_NULL_RETURN(container, false);
    StopDragCallback stopDragCallback = [asyncCtx, container]() { HandleStopDragCallback(asyncCtx, container); };
    bool getPointSuccess = container->GetCurPointerEventInfo(asyncCtx->dragPointerEvent, std::move(stopDragCallback));
    if (asyncCtx->dragPointerEvent.sourceType == SOURCE_TYPE_MOUSE) {
        asyncCtx->dragPointerEvent.pointerId = MOUSE_POINTER_ID;
    } else if (asyncCtx->dragPointerEvent.sourceType == SOURCE_TYPE_TOUCH &&
               static_cast<int32_t>(asyncCtx->dragPointerEvent.sourceTool) == SOURCE_TOOL_PEN) {
        asyncCtx->dragPointerEvent.pointerId = PEN_POINTER_ID;
    }
    return getPointSuccess;
}

bool PrepareDragData(std::shared_ptr<DragControllerAsyncCtx> asyncCtx, Msdp::DeviceStatus::DragData& dragData,
    Msdp::DeviceStatus::ShadowInfo& shadowInfo)
{
    CHECK_NULL_RETURN(asyncCtx, false);
    CHECK_NULL_RETURN(asyncCtx->pixelMap, false);
    std::string udKey;
    std::map<std::string, int64_t> summary;
    int32_t dataSize = SetUnifiedData(asyncCtx, udKey, summary);
    
    auto container = Ace::AceEngine::Get().GetContainer(asyncCtx->instanceId);
    CHECK_NULL_RETURN(container, false);
    if (!container->GetLastMovingPointerPosition(asyncCtx->dragPointerEvent)) {
        HandleFail(asyncCtx, ERROR_CODE_INTERNAL_ERROR, "can not find current pointerId or not in press");
        LOGE("AceDrag, can not find current pointerId or not in press.");
        return false;
    }
    auto arkExtraInfoJson = JsonUtil::Create(true);
    arkExtraInfoJson->Put("dip_scale", asyncCtx->dipScale);
    arkExtraInfoJson->Put("event_id", asyncCtx->dragPointerEvent.pointerEventId);
    DragDropFuncWrapper::UpdateExtraInfo(arkExtraInfoJson, asyncCtx->dragPreviewOption);
    auto windowId = container->GetWindowId();
    // dragData = { { shadowInfo }, {}, udKey, asyncCtx->extraParams, arkExtraInfoJson->ToString(),
    //     asyncCtx->dragPointerEvent.sourceType, dataSize, asyncCtx->dragPointerEvent.pointerId,
    //     static_cast<int32_t>(asyncCtx->dragPointerEvent.sourceTool), asyncCtx->dragPointerEvent.displayX,
    //     asyncCtx->dragPointerEvent.displayY, asyncCtx->dragPointerEvent.displayId, windowId, true, false, summary };
    return true;
}

bool TryToStartDrag(std::shared_ptr<DragControllerAsyncCtx> asyncCtx)
{
    CHECK_NULL_RETURN(asyncCtx, false);
    auto container = Ace::AceEngine::Get().GetContainer(asyncCtx->instanceId);
    CHECK_NULL_RETURN(container, false);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipeline, false);
    NG::PreparedInfoForDrag data;
    NG::PreparedAsyncCtxForAnimate asyncCtxData;
    Msdp::DeviceStatus::ShadowInfo shadowInfo;
    asyncCtxData = {asyncCtx->instanceId, asyncCtx->touchPoint.has_value(), asyncCtx->dragPointerEvent,
        asyncCtx->dragPreviewOption, asyncCtx->touchPoint.value(), asyncCtx->pixelMapList};
    if (!CreatePreviewNodeAndScale(asyncCtx, data, asyncCtxData, shadowInfo, asyncCtx->pixelMap)) {
        LOGE("AceDrag, create preview node failed.");
        return false;
    }
    // auto subWindow = DragControllerFuncWrapper::SubWindowShow(pipeline);
    Msdp::DeviceStatus::DragData dragData;
    if (!PrepareDragData(asyncCtx, dragData, shadowInfo)) {
        LOGE("AceDrag, prepare drag data failed!");
        return false;
    }
    data.badgeNumber = dragData.dragNum;
    OnDragCallback callback = [asyncCtx](const DragNotifyMsg& dragNotifyMsg) {
        HideDragPreviewWindow(asyncCtx);
        HandleSuccess(asyncCtx, dragNotifyMsg, DragStatus::ENDED);
    };
    DragDropFuncWrapper::SetDraggingPointerAndPressedState(
        asyncCtx->dragPointerEvent.pointerId, asyncCtx->instanceId);
    LogDragInfoInner(asyncCtx, dragData);
    auto result = Msdp::DeviceStatus::InteractionManager::GetInstance()->StartDrag(
        dragData, std::make_shared<OHOS::Ace::StartDragListenerImpl>(callback));
    if (result != 0) {
        HandleFail(asyncCtx, ERROR_CODE_INTERNAL_ERROR, "msdp start drag failed.");
        return false;
    }
    // if (DragControllerFuncWrapper::TryDoDragStartAnimation(subWindow, data, asyncCtxData)) {
    //     asyncCtx->isSwitchedToSubWindow = true;
    // }
    return true;
}

void OnComplete(std::shared_ptr<DragControllerAsyncCtx> asyncCtx)
{
    LOGI("AceDrag, OnComplete start");
    
    auto container = Ace::AceEngine::Get().GetContainer(asyncCtx->instanceId);
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto windowScale = container->GetWindowScale();
    asyncCtx->windowScale = windowScale;
    auto displayInfo = container->GetDisplayInfo();
    CHECK_NULL_VOID(displayInfo);
    asyncCtx->dragPointerEvent.displayId = displayInfo->GetDisplayId();
    taskExecutor->PostTask(
        [asyncCtx]() {
            LOGI("AceDrag, try to start msdp drag.");
            CHECK_NULL_VOID(asyncCtx);
            ContainerScope scope(asyncCtx->instanceId);
            DragState dragState = DragState::PENDING;
            {
                std::lock_guard<std::mutex> lock(asyncCtx->dragStateMutex);
                if (asyncCtx->dragState == DragState::PENDING) {
                    asyncCtx->dragState = DragState::SENDING;
                }
                dragState = asyncCtx->dragState;
            }
            if (dragState == DragState::REJECT) {
                HandleFail(asyncCtx, ERROR_CODE_INTERNAL_ERROR, "drag state is reject.");
                return;
            }
            if (!TryToStartDrag(asyncCtx)) {
                LOGE("AceDrag, msdp start drag failed.");
                return;
            }
            
            auto container = Ace::AceEngine::Get().GetContainer(asyncCtx->instanceId);
            CHECK_NULL_VOID(container);
            SetIsDragging(container, true);
            LOGI("AceDrag, msdp start drag successfully");
            ExecuteHandleOnDragStart(asyncCtx);
        },
        TaskExecutor::TaskType::JS, "ArkUIDragComplete", PriorityType::VIP);
}

void CreatePixelMapByCustom(std::shared_ptr<DragControllerAsyncCtx> asyncCtx, ArkUINodeHandle builderNode)
{
    CHECK_NULL_VOID(asyncCtx);
    
    auto callback = [asyncCtx](std::shared_ptr<Media::PixelMap> pixelMap, int32_t errCode,
                        std::function<void()> finishCallback) {
        CHECK_NULL_VOID(asyncCtx);
        auto container = Ace::AceEngine::Get().GetContainer(asyncCtx->instanceId);
        CHECK_NULL_VOID(container);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [finishCallback]() {
                CHECK_NULL_VOID(finishCallback);
                finishCallback();
            },
            TaskExecutor::TaskType::JS, "ArkUICreatePixelMapByCustom");
        CHECK_NULL_VOID(pixelMap);
        asyncCtx->pixelMap = std::move(pixelMap);
        OnComplete(asyncCtx);
    };
    NG::SnapshotParam param;
    param.delay = CREATE_PIXELMAP_DELAY_TIME;
    param.checkImageStatus = true;
    param.options.waitUntilRenderFinished = true;
    if (builderNode) {
        auto uinode = AceType::Claim(reinterpret_cast<UINode *>(builderNode));
        CHECK_NULL_VOID(uinode);
        ComponentSnapshot::Create(uinode, std::move(callback), true, param);
    }
}

void HandleExecuteDrag(std::shared_ptr<DragControllerAsyncCtx> asyncCtx, ArkUINodeHandle builderNode)
{
    ParameterType parameterType = GetParameterType(asyncCtx);
    if (parameterType == ParameterType::DRAG_PIXEL) {
        LOGI("AceDrag, drag preview is pixelMap.");
        OnComplete(asyncCtx);
    } else if (parameterType == ParameterType::DRAG_CUSTOM_BUILDER) {
        LOGI("AceDrag, drag preview is custom builder.");
        CreatePixelMapByCustom(asyncCtx, builderNode);
    } else {
        LOGE("AceDrag, parameter parsing error");
        Ani::AniThrow(asyncCtx->env, "parameter parsing error.", ERROR_CODE_PARAM_INVALID);
    }
}

ani_object ANIExecuteDragWithCallback(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_object dragItemInfo,
    ani_long builderObj, ani_object destroyCallbackObj, ani_object dragInfo, ani_object callback)
{
    LOGI("AceDrag, ExecuteDrag function modifier has been called.");
    CHECK_NULL_RETURN(env, nullptr);
    if (ANI_OK != env->CreateEscapeLocalScope(MAX_ESCAPE_NUM)) {
        return nullptr;
    }
    auto dragAsyncContext = std::make_shared<DragControllerAsyncCtx>();
    CHECK_NULL_RETURN(dragAsyncContext, nullptr);
    dragAsyncContext->instanceId = Ace::Container::CurrentIdSafely();
    dragAsyncContext->env = env;

    ani_ref escapedObj;
    ani_object result = {};
    auto* builderNode = reinterpret_cast<ArkUINodeHandle>(builderObj);
    if (!CheckAndParseFirstParams(env, dragAsyncContext, dragItemInfo, builderNode, nullptr)) {
        Ani::AniThrow(env, "parse first params failed.", ERROR_CODE_PARAM_INVALID);
        LOGE("AceDrag, parse first params failed.");
        env->DestroyEscapeLocalScope(result, &escapedObj);
        return result;
    }
    if (!CheckAndParseSecondParams(env, dragAsyncContext, dragInfo)) {
        Ani::AniThrow(env, "parse second params failed.", ERROR_CODE_PARAM_INVALID);
        LOGE("AceDrag, parse second params failed.");
        env->DestroyEscapeLocalScope(result, &escapedObj);
        return result;
    }
    if (!CreateCallbackFunc(env, dragAsyncContext, callback, result)) {
        Ani::AniThrow(env, "parse third params failed.", ERROR_CODE_PARAM_INVALID);
        LOGE("AceDrag, parse third params failed.");
        env->DestroyEscapeLocalScope(result, &escapedObj);
        return result;
    }

    auto container = Ace::AceEngine::Get().GetContainer(dragAsyncContext->instanceId);
    CHECK_NULL_RETURN(container, result);
    if (CheckDragging(container)) {
        Ani::AniThrow(env, "only one drag is allowed at the same time", ERROR_CODE_INTERNAL_ERROR);
        LOGE("AceDrag, only one drag is allowed at the same time.");
        env->DestroyEscapeLocalScope(result, &escapedObj);
        return result;
    }
    auto getPointSuccess = ConfirmCurPointerEventInfo(dragAsyncContext, container);
    if (!getPointSuccess) {
        Ani::AniThrow(env, "confirm current point info failed.", ERROR_CODE_INTERNAL_ERROR);
        LOGE("AceDrag, confirm current point info failed.");
        env->DestroyEscapeLocalScope(result, &escapedObj);
        return result;
    }

    HandleExecuteDrag(dragAsyncContext, dragAsyncContext->customBuilderNode);
    env->DestroyEscapeLocalScope(result, &escapedObj);
    return result;
}

ani_object ANICreateDragAction([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass,
    ani_object dragItemInfoArray, ani_object builderArray, ani_object destroyCallbackObj,
    [[maybe_unused]] ani_object dragInfoObj)
{
    CHECK_NULL_RETURN(env, nullptr);
    if (ANI_OK != env->CreateEscapeLocalScope(MAX_ESCAPE_NUM)) {
        return nullptr;
    }
    auto dragAsyncContext = std::make_shared<DragControllerAsyncCtx>();
    CHECK_NULL_RETURN(dragAsyncContext, nullptr);
    dragAsyncContext->instanceId = Ace::Container::CurrentIdSafely();
    dragAsyncContext->env = env;

    ani_ref escapedObj;
    ani_object dragActionObj = {};
    if (!CheckAndParseFirstParams(env, dragAsyncContext, dragItemInfoArray, nullptr, builderArray)) {
        Ani::AniThrow(env, "parse first params failed.", ERROR_CODE_PARAM_INVALID);
        LOGE("AceDrag, parse first params failed.");
        env->DestroyEscapeLocalScope(dragActionObj, &escapedObj);
        return dragActionObj;
    }
    if (!CheckAndParseSecondParams(env, dragAsyncContext, dragInfoObj)) {
        Ani::AniThrow(env, "parse second params failed.", ERROR_CODE_PARAM_INVALID);
        LOGE("AceDrag, parse second params failed.");
        env->DestroyEscapeLocalScope(dragActionObj, &escapedObj);
        return dragActionObj;
    }
    
    auto container = Ace::AceEngine::Get().GetContainer(dragAsyncContext->instanceId);
    CHECK_NULL_RETURN(container, dragActionObj);
    if (CheckDragging(container)) {
        Ani::AniThrow(env, "only one drag is allowed at the same time", ERROR_CODE_INTERNAL_ERROR);
        LOGE("AceDrag, only one drag is allowed at the same time.");
        env->DestroyEscapeLocalScope(dragActionObj, &escapedObj);
        return dragActionObj;
    }
    auto getPointSuccess = ConfirmCurPointerEventInfo(dragAsyncContext, container);
    if (!getPointSuccess) {
        Ani::AniThrow(env, "confirm current point info failed.", ERROR_CODE_INTERNAL_ERROR);
        LOGE("AceDrag, confirm current point info failed.");
        env->DestroyEscapeLocalScope(dragActionObj, &escapedObj);
        return dragActionObj;
    }
    DragAction* dragAction = new DragAction(dragAsyncContext);
    CHECK_NULL_RETURN(dragAction, nullptr);
    dragAction->AniSerializer(env, dragActionObj, reinterpret_cast<ani_long>(dragAction));
    dragAsyncContext->dragAction = dragAction;
    env->DestroyEscapeLocalScope(dragActionObj, &escapedObj);
    return dragActionObj;
}

ani_object ANIDragActionStartDrag(
    [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long dragActionPtr)
{
    return DragAction::StartDrag(env, aniClass, dragActionPtr);
}

void ANIDragActionOn([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, const char* type,
    ani_object callback, ani_long dragActionPtr)
{
    DragAction::On(env, aniClass, type, callback, dragActionPtr);
}

void ANIDragActionOff([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, const char* type,
    [[maybe_unused]] ani_object callback, ani_long dragActionPtr)
{
    DragAction::Off(env, aniClass, type, callback, dragActionPtr);
}

static ani_object ANIGetDragPreview([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object obj)
{
    CHECK_NULL_RETURN(env, nullptr);
    if (ANI_OK != env->CreateEscapeLocalScope(MAX_ESCAPE_NUM)) {
        return nullptr;
    }
    ani_ref escapedObj;
    Ani::DragPreview* dragPreview = new Ani::DragPreview();
    CHECK_NULL_RETURN(dragPreview, nullptr);
    ani_object dragPreviewObj = {};
    dragPreview->AniSerializer(env, dragPreviewObj);
    env->DestroyEscapeLocalScope(dragPreviewObj, &escapedObj);
    return dragPreviewObj;
}

void ANIDragPreviewSetForegroundColor([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object,
    ani_object colorObj, ani_long dragPreviewPtr)
{
    Ani::DragPreview::SetForegroundColor(env, object, colorObj, dragPreviewPtr);
}

void ANIDragPreviewAnimate(
    [[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object optionsObj, ani_object handlerObj,
    ani_long dragPreviewPtr)
{
    Ani::DragPreview::Animate(env, object, optionsObj, handlerObj, dragPreviewPtr);
}

void ANIDragActionSetDragEventStrictReportingEnabled(
    [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, bool enable)
{
    ViewAbstractModel::GetInstance()->SetDragEventStrictReportingEnabled(enable);
}

void ANIDragActionCancelDataLoading(
    [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, ani_string key)
{
    auto keyStr = Ani::ANIUtils_ANIStringToStdString(env, key);
    ViewAbstractModel::GetInstance()->CancelDataLoading(keyStr);
}

void ANIDragActionNotifyDragStartReques(
    [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, ani_enum_item requestStatusObj)
{
    ani_int requestStatus;
    if (ANI_OK != env->EnumItem_GetValue_Int(requestStatusObj, &requestStatus)) {
        return;
    }
    ViewAbstractModel::GetInstance()->NotifyDragStartRequest(static_cast<Ace::DragStartRequestStatus>(requestStatus));
}

const ArkUIAniDragControllerModifier* GetDragControllerAniModifier()
{
    static const ArkUIAniDragControllerModifier impl = {
        .aniExecuteDragWithCallback = NG::ANIExecuteDragWithCallback,
        .aniCreateDragAction = NG::ANICreateDragAction,
        .aniDragActionStartDrag = NG::ANIDragActionStartDrag,
        .aniDragActionOn = NG::ANIDragActionOn,
        .aniDragActionOff = NG::ANIDragActionOff,
        .aniGetDragPreview = NG::ANIGetDragPreview,
        .aniDragPreviewSetForegroundColor = NG::ANIDragPreviewSetForegroundColor,
        .aniDragPreviewAnimate = NG::ANIDragPreviewAnimate,
        .aniDragActionSetDragEventStrictReportingEnabled = NG::ANIDragActionSetDragEventStrictReportingEnabled,
        .aniDragActionCancelDataLoading = NG::ANIDragActionCancelDataLoading,
        .aniDragActionNotifyDragStartReques = NG::ANIDragActionNotifyDragStartReques,
    };
    return &impl;
}
} // namespace OHOS:Ace::NG