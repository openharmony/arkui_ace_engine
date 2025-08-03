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
#include "drag_controller_module.h"
#include "load.h"
#include "log/log.h"
#include "pixel_map_taihe_ani.h"
#include "udmf_ani_converter_utils.h"
#include "utils/ani_utils.h"

#include "core/common/ace_engine.h"
#include "core/interfaces/native/implementation/drag_event_peer.h"

namespace OHOS::Ace::Ani {
namespace {
constexpr int32_t PARAMETER_NUM = 2;
constexpr int32_t TWO_ARGS = 2;
constexpr int32_t MAX_ESCAPE_NUM = 1;
constexpr int32_t SPECIFIED_CAPACITY = 16;
}

class DragAction {
public:
    explicit DragAction(ArkUIDragControllerAsync& asyncCtx) : asyncCtx_(asyncCtx) {}
    ~DragAction()
    {
        asyncCtx_.dragAction = nullptr;
        CHECK_NULL_VOID(env_);
        for (auto& item : cbList_) {
            if (ANI_OK != env_->GlobalReference_Delete(item)) {
                HILOGE("AceDrag, GlobalReference_Delete failed.");
            }
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
            if (ref != nullptr) {
                cbList.emplace_back(ref);
            }
        }
        HILOGI("AceDrag, OnANICallback start cbList.size() = %{public}u.", cbList.size());
        for (auto& callbackRef : cbList) {
            ani_ref fnReturnVal;
            env_->FunctionalObject_Call(static_cast<ani_fn_object>(callbackRef), 1, &resultRef, &fnReturnVal);
        }
    }

    void AniSerializer([[maybe_unused]] ani_env* env, ani_object& result, ani_long dragActionPtr)
    {
        ani_status status = ANI_OK;
        ani_class cls;
        auto fullClassName = std::string("@ohos.arkui.dragController.dragController.DragActionInner");
        if ((status = env->FindClass(fullClassName.c_str(), &cls)) != ANI_OK) {
            HILOGE("AceDrag, find DragAction calss fail. status = %{public}d", status);
            return;
        }
        ani_method method;
        if ((status = env->Class_FindMethod(cls, "<ctor>", "J:V", &method)) != ANI_OK) {
            HILOGE("AceDrag, find constructor method failed. status = %{public}d", status);
            return;
        }
        if ((status = env->Object_New(cls, method, &result, dragActionPtr)) != ANI_OK) {
            HILOGE("AceDrag, create DragAction object failed. status = %{public}d", status);
            return;
        }
    }

    static void On([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object, const char* type,
        ani_object callback, ani_long dragActionPtr)
    {
        HILOGI("AceDrag, drag action On function has been called.");
        CHECK_NULL_VOID(env);
        if (ANI_OK != env->CreateLocalScope(SPECIFIED_CAPACITY)) {
            return;
        }
        auto argc = ParseArgs(env, type, callback);
        if (argc != TWO_ARGS) {
            AniUtils::AniThrow(env, "check param failed.", ERROR_CODE_PARAM_INVALID);
            HILOGE("AceDrag, check param failed.");
            env->DestroyLocalScope();
            return;
        }
        DragAction* dragAction = reinterpret_cast<DragAction*>(dragActionPtr);
        if (!dragAction) {
            AniUtils::AniThrow(env, "convert drag action failed.", ERROR_CODE_PARAM_INVALID);
            HILOGE("AceDrag, convert drag action failed.");
            env->DestroyLocalScope();
            return;
        }
        dragAction->Initialize(env);
        auto iter = dragAction->FindCbList(callback);
        if (iter != dragAction->cbList_.end()) {
            AniUtils::AniThrow(env, "js callback function already registered.", ERROR_CODE_PARAM_INVALID);
            HILOGE("AceDrag, js callback function already registered.");
            env->DestroyLocalScope();
            return;
        }
        ani_ref fnObjGlobalRef = nullptr;
        if (ANI_OK != env->GlobalReference_Create(callback, &fnObjGlobalRef)) {
            return;
        }
        dragAction->cbList_.emplace_back(fnObjGlobalRef);
        HILOGI("AceDrag, registered On function number is %{public}d.", static_cast<int>(dragAction->cbList_.size()));
        env->DestroyLocalScope();
    }

    static void Off([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object, const char* type,
        [[maybe_unused]] ani_object callback, ani_long dragActionPtr)
    {
        HILOGI("AceDrag, drag action Off function has been called.");
        CHECK_NULL_VOID(env);
        if (ANI_OK != env->CreateLocalScope(SPECIFIED_CAPACITY)) {
            return;
        }
        DragAction* dragAction = reinterpret_cast<DragAction*>(dragActionPtr);
        if (!dragAction) {
            HILOGE("AceDrag, convert drag action failed.");
            AniUtils::AniThrow(env, "convert drag action failed.", ERROR_CODE_PARAM_INVALID);
            env->DestroyLocalScope();
            return;
        }
        dragAction->Initialize(env);
        auto argc = ParseArgs(env, type, callback);
        if (argc == 1) {
            for (const auto& item : dragAction->cbList_) {
                if (ANI_OK != dragAction->env_->GlobalReference_Delete(item)) {
                    HILOGE("AceDrag, GlobalReference_Delete failed.");
                }
            }
            dragAction->cbList_.clear();
        } else if (argc == TWO_ARGS) {
            auto iter = dragAction->FindCbList(callback);
            if (iter != dragAction->cbList_.end()) {
                if (ANI_OK != dragAction->env_->GlobalReference_Delete(*iter)) {
                    HILOGE("AceDrag, GlobalReference_Delete failed.");
                }
                dragAction->cbList_.erase(iter);
            }
        } else {
            AniUtils::AniThrow(env, "check param failed.", ERROR_CODE_PARAM_INVALID);
            HILOGE("AceDrag, check param failed.");
        }
        env->DestroyLocalScope();
    }

    static ani_object StartDrag(
        [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object, ani_long dragActionPtr)
    {
        HILOGI("AceDrag, drag action StartDrag function has been called.");
        CHECK_NULL_RETURN(env, nullptr);
        if (ANI_OK != env->CreateEscapeLocalScope(MAX_ESCAPE_NUM)) {
            return nullptr;
        }
        ani_ref escapedObj;
        DragAction* dragAction = reinterpret_cast<DragAction*>(dragActionPtr);
        if (!dragAction) {
            AniUtils::AniThrow(env, "convert drag action failed.", ERROR_CODE_PARAM_INVALID);
            HILOGE("AceDrag, convert drag action failed.");
            env->DestroyEscapeLocalScope(nullptr, &escapedObj);
            return nullptr;
        }
        ani_object promise;
        if (ANI_OK != env->Promise_New(&dragAction->asyncCtx_.deferred, &promise)) {
            AniUtils::AniThrow(env, "create promise object failed!", ERROR_CODE_INTERNAL_ERROR);
            HILOGE("AceDrag, create promise object failed!");
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

    void SetAsyncCtx(ArkUIDragControllerAsync newCtx)
    {
        asyncCtx_ = newCtx;
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
            HILOGE("AceDrag, type mismatch('statusChange').");
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

    void StartDragInternal(ArkUIDragControllerAsync& asyncCtx)
    {
        const auto* modifier = GetNodeAniModifier();
        if (!modifier || !modifier->getDragControllerAniModifier()) {
            return;
        }
        if (!modifier->getDragControllerAniModifier()->aniHandleDragActionStartDrag(asyncCtx)) {
            HILOGE("AceDrag, ani HandleDragActionStartDrag failed.");
            AniUtils::AniThrow(asyncCtx.env, "ani HandleDragActionStartDrag failed.", ERROR_CODE_PARAM_INVALID);
        }
    }

    ani_env* env_ = nullptr;
    std::list<ani_ref> cbList_;
    ArkUIDragControllerAsync asyncCtx_;
};

ani_object CreateDragEventObject(ani_env* env, const ArkUIDragNotifyMessage& dragNotifyMsg)
{
    ani_object dragEventObj = {};
    CHECK_NULL_RETURN(env, dragEventObj);
    ani_status status = ANI_OK;
    static const char* className = "Larkui/component/common/DragEventInternal;";
    ani_class cls;
    if ((status = env->FindClass(className, &cls)) != ANI_OK) {
        HILOGE("AceDrag, find DragEventInner calss fail. status = %{public}d", status);
        return dragEventObj;
    }

    ani_method ctor;
    if ((status = env->Class_FindMethod(cls, "<ctor>", ":V", &ctor)) != ANI_OK) {
        HILOGE("AceDrag, find constructor method fail. status = %{public}d", status);
        return dragEventObj;
    }

    if ((status = env->Object_New(cls, ctor, &dragEventObj)) != ANI_OK) {
        HILOGE("AceDrag, create dragEvent fail. status = %{public}d", status);
        return dragEventObj;
    }

    ani_static_method getEventFromPeer;
    if ((status = env->Class_FindStaticMethod(
        cls, "fromPtr", "l:C{arkui.component.common.DragEventInternal}", &getEventFromPeer)) != ANI_OK) {
        HILOGE("AceDrag, find fromPtr method fail. status = %{public}d", status);
        return dragEventObj;
    }

    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragControllerAniModifier()) {
        return dragEventObj;
    }
    ani_long dragEventPeer;
    modifier->getDragControllerAniModifier()->createDragEventPeer(dragNotifyMsg, dragEventPeer);

    ani_ref commonDragEvent;
    if ((status = env->Class_CallStaticMethod_Ref(cls, getEventFromPeer, &commonDragEvent, dragEventPeer)) != ANI_OK) {
        HILOGE("AceDrag, call fromPtr method failed. status = %{public}d", status);
        DragEventPeer* arkDragInfo = reinterpret_cast<DragEventPeer*>(dragEventPeer);
        delete arkDragInfo;
        return dragEventObj;
    }
    return static_cast<ani_object>(commonDragEvent);
}

void TriggerJsCallback(std::shared_ptr<ArkUIDragControllerAsync> asyncCtx, ani_ref result)
{
    CHECK_NULL_VOID(asyncCtx);
    CHECK_NULL_VOID(asyncCtx->env);
    ani_status status = ANI_OK;
    if (asyncCtx->isArray && asyncCtx->dragAction) {
        asyncCtx->dragAction->OnANICallback(result);
        if (asyncCtx->deferred != nullptr) {
            HILOGI("AceDrag, PromiseResolver_Resolve start");
            ani_ref promiseResult = nullptr;
            if ((status = asyncCtx->env->GetUndefined(&promiseResult)) != ANI_OK) {
                HILOGE("AceDrag, get undefined value failed, status = %{public}d", status);
                return;
            }
            if ((status = asyncCtx->env->PromiseResolver_Resolve(asyncCtx->deferred, promiseResult)) != ANI_OK) {
                HILOGE("AceDrag, PromiseResolver_Resolve failed, status = %{public}d", status);
                return;
            }
        }
    } else {
        if (asyncCtx->asyncCallback) { // asyncCallback
            std::vector<ani_ref> resultRef(PARAMETER_NUM);
            auto errObj = AniUtils::CreateBusinessError(asyncCtx->env, "", ERROR_CODE_NO_ERROR);
            resultRef[0] = errObj;
            resultRef[1] = result;
            ani_ref fnReturnVal;
            if ((status = asyncCtx->env->FunctionalObject_Call(
                asyncCtx->asyncCallback, resultRef.size(), resultRef.data(), &fnReturnVal)) != ANI_OK) {
                HILOGE("AceDrag, FunctionalObject_Call failed, status = %{public}d", status);
            }
            if ((status = asyncCtx->env->GlobalReference_Delete(asyncCtx->asyncCallback)) != ANI_OK) {
                HILOGE("AceDrag, GlobalReference_Delete failed, status = %{public}d", status);
                return;
            }
        } else { // promise
            if ((status = asyncCtx->env->PromiseResolver_Resolve(asyncCtx->deferred, result)) != ANI_OK) {
                HILOGE("AceDrag, PromiseResolver_Resolve failed, status = %{public}d", status);
            }
        }
    }
    HILOGI("AceDrag, TriggerJsCallback end.");
    asyncCtx->deferred = nullptr;
    asyncCtx->hasHandle = false;
}

ani_object GetDragAndDropInfo(
    ani_env* env, const ArkUIDragStatus dragStatus, ani_object dragEventObj, ani_string extraParams)
{
    HILOGI("AceDrag, Get dragEvent obj from DragAndDropInfo");
    CHECK_NULL_RETURN(env, nullptr);
    ani_class cls;
    ani_method ctor;
    ani_object dragObj = nullptr;
    ani_enum_item dragStatusItem;
    static const std::string fullEnumName = std::string("@ohos.arkui.dragController.dragController.DragStatus");
    if (!AniUtils::GetEnumItem(env, ani_size(dragStatus), fullEnumName.c_str(), dragStatusItem)) {
        HILOGE("AceDrag, get dragStatus enum item failed.");
        env->DestroyLocalScope();
        return dragObj;
    }
    auto fullClassName = std::string("@ohos.arkui.dragController.dragController.DragAndDropInfoInner");
    if (ANI_OK != env->FindClass(fullClassName.c_str(), &cls)) {
        HILOGE("AceDrag, find LDragAndDropInfoInner calss fail.");
        env->DestroyLocalScope();
        return dragObj;
    }
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>",
        "C{@ohos.arkui.dragController.dragController.DragStatus}C{arkui.component.common.DragEvent}"
        "C{std.core.String}:", &ctor)) {
        HILOGE("AceDrag, find LDragAndDropInfoInner constructor method failed.");
        env->DestroyLocalScope();
        return dragObj;
    }
    if (ANI_OK != env->Object_New(cls, ctor, &dragObj, dragStatusItem, dragEventObj, extraParams)) {
        HILOGE("AceDrag, create LDragAndDropInfoInner object failed.");
        env->DestroyLocalScope();
        return dragObj;
    }
    return dragObj;
}

ani_object GetDragEventParam(ani_env* env, ani_object dragEventObj, ani_string extraParams)
{
    HILOGI("AceDrag, Get dragEvent obj from DragEventParam");
    CHECK_NULL_RETURN(env, nullptr);
    ani_status status = ANI_OK;
    ani_object dragObj = nullptr;
    ani_class cls;
    auto fullClassName = std::string("@ohos.arkui.dragController.dragController.DragEventParamInner");
    if ((status = env->FindClass(fullClassName.c_str(), &cls)) != ANI_OK) {
        HILOGE("AceDrag, find DragEventParamInner calss fail. status = %{public}d", status);
        env->DestroyLocalScope();
        return dragObj;
    }
    ani_method ctor;
    if ((status = env->Class_FindMethod(cls, "<ctor>",
        "C{arkui.component.common.DragEvent}C{std.core.String}:", &ctor)) != ANI_OK) {
        HILOGE("AceDrag, find LDragEventParamInner constructor method failed. status = %{public}d", status);
        env->DestroyLocalScope();
        return dragObj;
    }
    if ((status = env->Object_New(cls, ctor, &dragObj, dragEventObj, extraParams)) != ANI_OK) {
        HILOGE("AceDrag, create DragEventParamInner object failed. status = %{public}d", status);
        env->DestroyLocalScope();
        return dragObj;
    }
    return dragObj;
}

void CallBackJsFunction(std::shared_ptr<ArkUIDragControllerAsync> asyncCtx, const ArkUIDragNotifyMessage& dragNotifyMsg,
    const ArkUIDragStatus dragStatus)
{
    CHECK_NULL_VOID(asyncCtx);
    CHECK_NULL_VOID(asyncCtx->env);
    ani_status status = ANI_OK;
    if ((status = asyncCtx->env->CreateLocalScope(SPECIFIED_CAPACITY)) != ANI_OK) {
        HILOGE("AceDrag, CreateLocalScope fail. status = %{public}d", status);
        return;
    }
    ani_object dragEventObj = CreateDragEventObject(asyncCtx->env, dragNotifyMsg);
    ani_string extraParamsObj;
    if ((status = asyncCtx->env->String_NewUTF8(
        asyncCtx->extraParams, strlen(asyncCtx->extraParams), &extraParamsObj)) != ANI_OK) {
        HILOGE("AceDrag, covert extraParams to ani object failed. status = %{public}d", status);
        asyncCtx->env->DestroyLocalScope();
        return;
    }
    ani_object dragObj;
    if (asyncCtx->isArray) {
        dragObj = GetDragAndDropInfo(asyncCtx->env, dragStatus, dragEventObj, extraParamsObj);
    } else {
        dragObj = GetDragEventParam(asyncCtx->env, dragEventObj, extraParamsObj);
    }
    TriggerJsCallback(asyncCtx, dragObj);
    asyncCtx->env->DestroyLocalScope();
}

bool ParseDragItemInfoParam(ani_env* env, ArkUIDragControllerAsync& asyncCtx, ani_object dragItemInfo)
{
    CHECK_NULL_RETURN(env, false);
    ani_ref pixelMapAni;
    ani_ref extraInfoAni;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(dragItemInfo, "pixelMap", &pixelMapAni)) {
        HILOGE("AceDrag, get pixelMap failed.");
        return false;
    }
    if (ANI_OK != env->Object_GetPropertyByName_Ref(dragItemInfo, "extraInfo", &extraInfoAni)) {
        HILOGE("AceDrag, get extraInfo failed.");
        return false;
    }
    if (AniUtils::IsClassObject(env, extraInfoAni, "Lstd/core/String;")) {
        std::string extraParamsStr = AniUtils::ANIStringToStdString(env, static_cast<ani_string>(extraInfoAni));
        std::string extraInfoLimited = extraParamsStr.size() > EXTRA_INFO_MAX_LENGTH
                                    ? extraParamsStr.substr(0, EXTRA_INFO_MAX_LENGTH)
                                    : extraParamsStr;
        asyncCtx.extraParams = extraInfoLimited.c_str();
    }
    if (!AniUtils::IsUndefined(env, static_cast<ani_object>(pixelMapAni))) {
        auto nativePixelMap =
            OHOS::Media::PixelMapTaiheAni::GetNativePixelMap(env, reinterpret_cast<ani_object>(pixelMapAni));
        if (nativePixelMap) {
            if (asyncCtx.isArray) {
                asyncCtx.pixelMapList.emplace_back(SharedPointerWrapper(nativePixelMap));
            } else {
                asyncCtx.pixelMap = SharedPointerWrapper(nativePixelMap);
            }
        } else {
            HILOGE("AceDrag, get native pixelMap from taiheAni is null.");
            return false;
        }
    }
    return true;
}

bool ParseDragMixParam(ani_env* env, ArkUIDragControllerAsync& asyncCtx, ani_object dragItemInfo,
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
                HILOGE("AceDrag, get builder node from array fail. status = %{public}d", status);
                isParseSucess = false;
                break;
            }
            if (AniUtils::IsUndefined(env, static_cast<ani_object>(itemRef))) {
                HILOGE("AceDrag, get builder node from array is undefined.");
                isParseSucess = false;
                break;
            }
            ani_long builderPtr;
            if (!AniUtils::GetBigIntValue(env, static_cast<ani_object>(itemRef), builderPtr)) {
                HILOGE("AceDrag, get builder node value from array fail.");
                isParseSucess = false;
                break;
            }
            asyncCtx.customBuilderNodeList.emplace_back(reinterpret_cast<ArkUINodeHandle>(builderPtr));
        }
        for (int32_t i = 0; i < dragItemInfoArrayLengthInt; i++) {
            ani_ref itemRef;
            if ((status = env->Object_CallMethodByName_Ref(
                dragItemInfo, "$_get", "i:C{std.core.Object}", &itemRef, (ani_int)i)) != ANI_OK) {
                HILOGE("AceDrag, get dragItemInfo from array fail. status = %{public}d", status);
                isParseSucess = false;
                break;
            }
            if (AniUtils::IsUndefined(env, static_cast<ani_object>(itemRef))) {
                HILOGE("AceDrag, get dragItemInfo from array is undefined.");
                isParseSucess = false;
                break;
            }
            if (!ParseDragItemInfoParam(env, asyncCtx, static_cast<ani_object>(itemRef))) {
                HILOGE("AceDrag, parse dragItemInfo value from array fail.");
                isParseSucess = false;
                break;
            }
        }
    } else {
        isParseSucess = false;
    }
    return isParseSucess;
}

bool ParseDragItemListInfoParam(ani_env* env, ArkUIDragControllerAsync& asyncCtx, ani_object dragItemInfo,
    ani_object builderObj)
{
    CHECK_NULL_RETURN(env, false);
    ani_double builderArrayLength;
    ani_double dragItemInfoArrayLength;
    ani_status status = ANI_OK;
    if ((status = env->Object_GetPropertyByName_Double(builderObj, "length", &builderArrayLength)) != ANI_OK) {
        HILOGE("AceDrag, get builder array length fail. status = %{public}d", status);
        return false;
    }
    if ((status = env->Object_GetPropertyByName_Double(dragItemInfo, "length", &dragItemInfoArrayLength)) != ANI_OK) {
        HILOGE("AceDrag, get dragItemInfo array length fail. status = %{public}d", status);
        return false;
    }
    return ParseDragMixParam(env, asyncCtx, dragItemInfo, builderObj, builderArrayLength, dragItemInfoArrayLength);
}

bool CheckAndParseFirstParams(ani_env* env, ArkUIDragControllerAsync& asyncCtx, ani_object dragItemInfo,
    ArkUINodeHandle builderNode, ani_object builderNodeArray)
{
    CHECK_NULL_RETURN(env, false);
    if (AniUtils::IsUndefined(env, dragItemInfo)) {
        return false;
    }
    if (builderNode) {
        asyncCtx.customBuilderNode = builderNode;
        return true;
    }
    if (AniUtils::IsClassObject(env, dragItemInfo, "Lescompat/Array;") ||
        AniUtils::IsClassObject(env, builderNodeArray, "Lescompat/Array;")) {
        asyncCtx.isArray = true;
        HILOGI("AceDrag, drag controller is multi object drag.");
        return ParseDragItemListInfoParam(env, asyncCtx, dragItemInfo, builderNodeArray);
    }
    asyncCtx.isArray = false;
    return ParseDragItemInfoParam(env, asyncCtx, dragItemInfo);
}

bool SetDragPreviewOptionMode(
    ani_env* env, ArkUIDragControllerAsync& asyncCtx, ani_object dragPreviewMode, bool& isAuto)
{
    if (isAuto) {
        return true;
    }
    ani_int dragPreviewModeAni;
    ani_status status = ANI_OK;
    if ((status = env->EnumItem_GetValue_Int(static_cast<ani_enum_item>(dragPreviewMode), &dragPreviewModeAni)) !=
        ANI_OK) {
        HILOGE("AceDrag, get dragPreviewMode enum failed. status = %{public}d", status);
        return false;
    }
    auto mode = static_cast<NG::DragPreviewMode>(dragPreviewModeAni);
    switch (mode) {
        case NG::DragPreviewMode::AUTO:
            asyncCtx.dragPreviewOption.ResetDragPreviewMode();
            isAuto = true;
            break;
        case NG::DragPreviewMode::DISABLE_SCALE:
            asyncCtx.dragPreviewOption.isScaleEnabled = false;
            break;
        case NG::DragPreviewMode::ENABLE_DEFAULT_SHADOW:
            asyncCtx.dragPreviewOption.isDefaultShadowEnabled = true;
            break;
        case NG::DragPreviewMode::ENABLE_DEFAULT_RADIUS:
            asyncCtx.dragPreviewOption.isDefaultRadiusEnabled = true;
            break;
        default:
            HILOGW("AceDrag, invalid dragPreviewMode value: %{public}d", mode);
            break;
    }
    return true;
}

bool ParseNumberBadge(ani_env* env, ArkUIDragControllerAsync& asyncCtx, ani_object numberBadgeAni)
{
    ani_status status = ANI_OK;
    if (AniUtils::IsClassObject(env, numberBadgeAni, "Lstd/core/Boolean;")) {
        asyncCtx.dragPreviewOption.isNumber = false;
        ani_boolean aniValue;
        if (env->Object_CallMethodByName_Boolean(numberBadgeAni, "unboxed", nullptr, &aniValue) == ANI_OK) {
            asyncCtx.dragPreviewOption.isShowBadge = static_cast<bool>(aniValue);
        }
    } else if (AniUtils::IsClassObject(env, numberBadgeAni, "Lstd/core/Numeric;")) {
        ani_double numberValue;
        if ((status = env->Object_CallMethodByName_Double(
            static_cast<ani_object>(numberBadgeAni), "unboxed", ":D", &numberValue)) != ANI_OK) {
            HILOGE("AceDrag, Object_CallMethodByName_Double failed. status = %{public}d", status);
        }
        auto number = static_cast<double>(numberValue);
        if (number < 0 || number > INT_MAX) {
            asyncCtx.dragPreviewOption.isNumber = false;
            asyncCtx.dragPreviewOption.isShowBadge = true;
        } else {
            asyncCtx.dragPreviewOption.isNumber = true;
            asyncCtx.dragPreviewOption.badgeNumber = static_cast<int32_t>(number);
        }
    } else if (!AniUtils::IsUndefined(env, numberBadgeAni)) {
        HILOGE("AceDrag, numberBadge type is wrong.");
        return false;
    }
    return true;
}

bool ParseModifier(ani_env* env, ArkUIDragControllerAsync& asyncCtx, ani_object modifierObj)
{
    if (AniUtils::IsUndefined(env, modifierObj)) {
        return true;
    }

    ani_ref modifierFunc;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(modifierObj, "applyImageModifierToNode", &modifierFunc)) {
        return false;
    }
    // modifierFunc may have two args
    if (!AniUtils::IsClassObject(env, modifierFunc, "Lstd/core/Function2;")) {
        HILOGE("AceDrag, applyImageModifierToNode is not a function object.");
        return false;
    }
    //to do imageModifier
    return true;
}

bool ParseDragPreviewMode(ani_env* env, ArkUIDragControllerAsync& asyncCtx, ani_object previewModeObj)
{
    if (AniUtils::IsUndefined(env, previewModeObj)) {
        return true;
    }
    bool isAuto = false;
    if (AniUtils::IsClassObject(env, previewModeObj, "Lescompat/Array;")) {
        ani_double lengthAni;
        if (ANI_OK != env->Object_GetPropertyByName_Double(previewModeObj, "length", &lengthAni)) {
            HILOGE("AceDrag, Object_GetPropertyByName_Double failed.");
            return false;
        }
        int32_t lengthInt = static_cast<int32_t>(lengthAni);
        for (int32_t i = 0; i < lengthInt; i++) {
            ani_ref modeRef;
            if (ANI_OK != env->Object_CallMethodByName_Ref(
                previewModeObj, "$_get", "I:Lstd/core/Object;", &modeRef, (ani_int)i)) {
                HILOGE("AceDrag, Object_CallMethodByName_Ref failed.");
                return false;
            }
            if (AniUtils::IsUndefined(env, static_cast<ani_object>(modeRef))) {
                continue;
            }
            if (!SetDragPreviewOptionMode(env, asyncCtx, static_cast<ani_object>(modeRef), isAuto)) {
                HILOGE("AceDrag, SetDragPreviewOptionMode failed.");
                return false;
            }
        }
    } else if (!SetDragPreviewOptionMode(env, asyncCtx, previewModeObj, isAuto)) {
        HILOGE("AceDrag, SetDragPreviewOptionMode failed.");
        return false;
    }
    return true;
}

bool ParsePreviewOptions(ani_env* env, ArkUIDragControllerAsync& asyncCtx, ani_object previewOptions)
{
    CHECK_NULL_RETURN(env, false);
    if (AniUtils::IsUndefined(env, previewOptions)) {
        return true;
    }
    asyncCtx.dragPreviewOption.isNumber = false;
    asyncCtx.dragPreviewOption.isShowBadge = true;

    ani_ref modeAni;
    ani_ref numberBadgeAni;
    ani_ref modifierAni;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(previewOptions, "mode", &modeAni)) {
        HILOGE("AceDrag, get mode parameter failed.");
        return false;
    }
    if (ANI_OK != env->Object_GetPropertyByName_Ref(previewOptions, "numberBadge", &numberBadgeAni)) {
        HILOGE("AceDrag, get numberBadge parameter failed.");
        return false;
    }
    if (ANI_OK != env->Object_GetPropertyByName_Ref(previewOptions, "modifier", &modifierAni)) {
        HILOGE("AceDrag, get modifier parameter failed.");
        return false;
    }

    if (!ParseDragPreviewMode(env, asyncCtx, static_cast<ani_object>(modeAni))) {
        HILOGE("AceDrag, parse mode parameter failed.");
        return false;
    }
    if (!ParseNumberBadge(env, asyncCtx, static_cast<ani_object>(numberBadgeAni))) {
        HILOGE("AceDrag, parse numberBadge parameter failed.");
        return false;
    }
    if (!ParseModifier(env, asyncCtx, static_cast<ani_object>(modifierAni))) {
        HILOGE("AceDrag, parse modifier parameter failed.");
        return false;
    }
    return true;
}

std::optional<Dimension> ConvertDimensionType(ani_env* env, ani_ref touchPoint)
{
    if (AniUtils::IsUndefined(env, static_cast<ani_object>(touchPoint))) {
        return std::nullopt;
    }
    Dimension parameter;
    if (AniUtils::IsClassObject(env, touchPoint, "Lstd/core/Numeric;")) {
        ani_double numberValue;
        if (ANI_OK !=
            env->Object_CallMethodByName_Double(static_cast<ani_object>(touchPoint), "unboxed", ":D", &numberValue)) {
            HILOGW("Failed to call unboxed method on Numeric object");
        }
        parameter.SetValue(static_cast<double>(numberValue));
        parameter.SetUnit(DimensionUnit::VP);
        return parameter;
    }
    if (AniUtils::IsClassObject(env, touchPoint, "Lstd/core/String;")) {
        auto parameterStr = AniUtils::ANIStringToStdString(env, static_cast<ani_string>(touchPoint));
        parameter = StringUtils::StringToDimensionWithUnit(parameterStr, DimensionUnit::VP);
        return parameter;
    }
    return std::nullopt;
}

bool CheckAndParseSecondParams(ani_env* env, ArkUIDragControllerAsync& asyncCtx, ani_object dragInfo)
{
    if (AniUtils::IsUndefined(env, dragInfo)) {
        return false;
    }
    ani_double pointerIdAni;
    ani_ref extraParamsAni;
    ani_ref dataAni;
    ani_ref touchPointAni;
    ani_ref previewOptionsAni;
    if (ANI_OK != env->Object_GetPropertyByName_Double(dragInfo, "pointerId", &pointerIdAni)) {
        HILOGE("AceDrag, get pointerId failed.");
        return false;
    }
    if (ANI_OK != env->Object_GetPropertyByName_Ref(dragInfo, "extraParams", &extraParamsAni)) {
        HILOGE("AceDrag, get extraParams failed.");
        return false;
    }
    if (ANI_OK != env->Object_GetPropertyByName_Ref(dragInfo, "data", &dataAni)) {
        HILOGE("AceDrag, get data failed.");
        return false;
    }
    if (ANI_OK != env->Object_GetPropertyByName_Ref(dragInfo, "touchPoint", &touchPointAni)) {
        HILOGE("AceDrag, get touchPoint failed.");
        return false;
    }
    if (ANI_OK != env->Object_GetPropertyByName_Ref(dragInfo, "previewOptions", &previewOptionsAni)) {
        HILOGE("AceDrag, get previewOptions failed.");
        return false;
    }

    asyncCtx.dragPointerEvent.pointerId = static_cast<int32_t>(pointerIdAni);
    HILOGI("AceDrag, pointerId = %{public}d", asyncCtx.dragPointerEvent.pointerId);
    if (AniUtils::IsClassObject(env, extraParamsAni, "Lstd/core/String;")) {
        std::string extraParamsStr = AniUtils::ANIStringToStdString(env, static_cast<ani_string>(extraParamsAni));
        std::string extraInfoLimited = extraParamsStr.size() > EXTRA_INFO_MAX_LENGTH
                                    ? extraParamsStr.substr(0, EXTRA_INFO_MAX_LENGTH)
                                    : extraParamsStr;
        asyncCtx.extraParams = extraInfoLimited.c_str();
    }
    if (!AniUtils::IsUndefined(env, static_cast<ani_object>(dataAni))) {
        auto dataValue = OHOS::UDMF::AniConverter::UnwrapUnifiedData(env, static_cast<ani_object>(dataAni));
        if (dataValue) {
            asyncCtx.unifiedData = SharedPointerWrapper(dataValue);
        }
    }

    std::shared_ptr<DimensionOffset> dimensionPtr = nullptr;
    if (!AniUtils::IsUndefined(env, static_cast<ani_object>(touchPointAni))) {
        ani_ref pointXAni = nullptr;
        ani_ref pointYAni = nullptr;
        if (ANI_OK != env->Object_GetPropertyByName_Ref(static_cast<ani_object>(touchPointAni), "x", &pointXAni)) {
            HILOGE("AceDrag, get touchPoint x value failed.");
            return false;
        }
        if (ANI_OK != env->Object_GetPropertyByName_Ref(static_cast<ani_object>(touchPointAni), "y", &pointYAni)) {
            HILOGE("AceDrag, get touchPoint y value failed.");
            return false;
        }

        std::optional<Dimension> dx = ConvertDimensionType(env, pointXAni);
        std::optional<Dimension> dy = ConvertDimensionType(env, pointYAni);
        if (dx.has_value() && dy.has_value()) {
            dimensionPtr = std::make_shared<DimensionOffset>(dx.value(), dy.value());
            asyncCtx.touchPoint = SharedPointerWrapper(dimensionPtr);
        }
    } else {
        dimensionPtr = std::make_shared<DimensionOffset>(OHOS::Ace::NG::OffsetF(0.0f, 0.0f));
        asyncCtx.touchPoint = SharedPointerWrapper(dimensionPtr);
    }
    
    if (!ParsePreviewOptions(env, asyncCtx, static_cast<ani_object>(previewOptionsAni))) {
        HILOGE("AceDrag, parse previewOptions failed.");
        return false;
    }
    return true;
}

bool CreateCallbackFunc(
    ani_env* env, ArkUIDragControllerAsync& asyncCtx, ani_object callback, ani_object& result)
{
    if (AniUtils::IsClassObject(env, callback, "Lstd/core/Function2;")) {
        HILOGI("AceDrag, Create async callback");
        ani_ref fnObjGlobalRef = nullptr;
        if (ANI_OK != env->GlobalReference_Create(callback, &fnObjGlobalRef)) {
            return false;
        }
        asyncCtx.asyncCallback = static_cast<ani_fn_object>(fnObjGlobalRef);
        return true;
    } else if (callback == nullptr) {
        HILOGI("AceDrag, create promise object");
        if (ANI_OK != env->Promise_New(&asyncCtx.deferred, &result)) {
            HILOGE("AceDrag, create promise object failed!");
            return false;
        }
    } else {
        HILOGE("AceDrag, third parameter is not function.");
        return false;
    }
    return true;
}

ani_object ANIExecuteDragWithCallback(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_object dragItemInfo,
    ani_long builderObj, ani_object destroyCallbackObj, ani_object dragInfo, ani_object callback)
{
    CHECK_NULL_RETURN(env, nullptr);
    if (ANI_OK != env->CreateEscapeLocalScope(MAX_ESCAPE_NUM)) {
        return nullptr;
    }
    ArkUIDragControllerAsync dragAsyncContext;
    ani_ref escapedObj;
    ani_object result = {};
    auto* builderNode = reinterpret_cast<ArkUINodeHandle>(builderObj);
    if (!CheckAndParseFirstParams(env, dragAsyncContext, dragItemInfo, builderNode, nullptr)) {
        AniUtils::AniThrow(env, "parse first params failed.", ERROR_CODE_PARAM_INVALID);
        HILOGE("AceDrag, parse first params failed.");
        env->DestroyEscapeLocalScope(result, &escapedObj);
        return result;
    }
    if (!CheckAndParseSecondParams(env, dragAsyncContext, dragInfo)) {
        AniUtils::AniThrow(env, "parse second params failed.", ERROR_CODE_PARAM_INVALID);
        HILOGE("AceDrag, parse second params failed.");
        env->DestroyEscapeLocalScope(result, &escapedObj);
        return result;
    }
    if (!CreateCallbackFunc(env, dragAsyncContext, callback, result)) {
        AniUtils::AniThrow(env, "parse third params failed.", ERROR_CODE_PARAM_INVALID);
        HILOGE("AceDrag, parse third params failed.");
        env->DestroyEscapeLocalScope(result, &escapedObj);
        return result;
    }
    dragAsyncContext.env = env;
    auto jsCallback =
        [=](std::shared_ptr<ArkUIDragControllerAsync> asyncCtx, const ArkUIDragNotifyMessage& dragNotifyMsg,
            const ArkUIDragStatus dragStatus) { CallBackJsFunction(asyncCtx, dragNotifyMsg, dragStatus); };
    dragAsyncContext.callBackJsFunction = jsCallback;

    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragControllerAniModifier()) {
        return result;
    }
    if (!modifier->getDragControllerAniModifier()->aniHandleExecuteDrag(dragAsyncContext)) {
        HILOGE("AceDrag, ani HandleExecuteDrag fail.");
        env->DestroyEscapeLocalScope(result, &escapedObj);
        return result;
    }
    env->DestroyEscapeLocalScope(result, &escapedObj);
    return result;
}

ani_object ANIExecuteDragWithPromise([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass,
    ani_object custom, ani_long builderObj, ani_object destroyCallbackObj, ani_object dragInfo)
{
    return ANIExecuteDragWithCallback(env, aniClass, custom, builderObj, destroyCallbackObj, dragInfo, nullptr);
}

ani_object ANICreateDragAction([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass,
    ani_object dragItemInfoArray, ani_object builderArray, ani_object destroyCallbackObj,
    [[maybe_unused]] ani_object dragInfoObj)
{
    CHECK_NULL_RETURN(env, nullptr);
    if (ANI_OK != env->CreateEscapeLocalScope(MAX_ESCAPE_NUM)) {
        return nullptr;
    }
    ArkUIDragControllerAsync dragAsyncContext;
    ani_ref escapedObj;
    ani_object dragActionObj = {};
    if (!CheckAndParseFirstParams(env, dragAsyncContext, dragItemInfoArray, nullptr, builderArray)) {
        AniUtils::AniThrow(env, "parse first params failed.", ERROR_CODE_PARAM_INVALID);
        HILOGE("AceDrag, parse first params failed.");
        env->DestroyEscapeLocalScope(dragActionObj, &escapedObj);
        return dragActionObj;
    }
    if (!CheckAndParseSecondParams(env, dragAsyncContext, dragInfoObj)) {
        AniUtils::AniThrow(env, "parse second params failed.", ERROR_CODE_PARAM_INVALID);
        HILOGE("AceDrag, parse second params failed.");
        env->DestroyEscapeLocalScope(dragActionObj, &escapedObj);
        return dragActionObj;
    }
    dragAsyncContext.env = env;
    auto jsCallback =
        [=](std::shared_ptr<ArkUIDragControllerAsync> asyncCtx, const ArkUIDragNotifyMessage& dragNotifyMsg,
            const ArkUIDragStatus dragStatus) { CallBackJsFunction(asyncCtx, dragNotifyMsg, dragStatus); };
    dragAsyncContext.callBackJsFunction = jsCallback;
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragControllerAniModifier()) {
        return dragActionObj;
    }
    if (!modifier->getDragControllerAniModifier()->aniHandleDragAction(dragAsyncContext)) {
        HILOGE("AceDrag, ani HandleCreateDragAction fail.");
        env->DestroyEscapeLocalScope(dragActionObj, &escapedObj);
    }
    DragAction* dragAction = new DragAction(dragAsyncContext);
    CHECK_NULL_RETURN(dragAction, nullptr);
    dragAsyncContext.dragAction = dragAction;
    dragAction->SetAsyncCtx(dragAsyncContext);
    dragAction->AniSerializer(env, dragActionObj, reinterpret_cast<ani_long>(dragAction));
    env->DestroyEscapeLocalScope(dragActionObj, &escapedObj);
    return dragActionObj;
}

ani_object ANIDragActionStartDrag(
    [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long dragActionPtr)
{
    return DragAction::StartDrag(env, aniClass, dragActionPtr);
}

void ANIDragActionOn([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, ani_string type,
    ani_object callback, ani_long dragActionPtr)
{
    std::string aniType = AniUtils::ANIStringToStdString(env, type);
    DragAction::On(env, aniClass, aniType.c_str(), callback, dragActionPtr);
}

void ANIDragActionOff([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, ani_string type,
    [[maybe_unused]] ani_object callback, ani_long dragActionPtr)
{
    std::string aniType = AniUtils::ANIStringToStdString(env, type);
    DragAction::Off(env, aniClass, aniType.c_str(), callback, dragActionPtr);
}

ani_object ANIGetDragPreview([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragControllerAniModifier()) {
        return nullptr;
    }
    return modifier->getDragControllerAniModifier()->aniGetDragPreview(env, aniClass);
}

void ANIDragPreviewSetForegroundColor([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass,
    ani_object color, ani_long dragPreviewPtr)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragControllerAniModifier()) {
        return;
    }
    modifier->getDragControllerAniModifier()->aniDragPreviewSetForegroundColor(env, aniClass, color, dragPreviewPtr);
}

void ANIDragPreviewAnimate([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, ani_object options,
    ani_object handler, ani_long dragPreviewPtr)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragControllerAniModifier()) {
        return;
    }
    modifier->getDragControllerAniModifier()->aniDragPreviewAnimate(env, aniClass, options, handler, dragPreviewPtr);
}

void ANIDragActionSetDragEventStrictReportingEnabled(
    [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, bool enable)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragControllerAniModifier()) {
        return;
    }
    modifier->getDragControllerAniModifier()->aniDragActionSetDragEventStrictReportingEnabled(env, aniClass, enable);
}

void ANIDragActionCancelDataLoading(
    [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, ani_string key)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragControllerAniModifier()) {
        return;
    }
    modifier->getDragControllerAniModifier()->aniDragActionCancelDataLoading(env, aniClass, key);
}

void ANIDragActionNotifyDragStartReques(
    [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, ani_enum_item requestStatus)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragControllerAniModifier()) {
        return;
    }
    modifier->getDragControllerAniModifier()->aniDragActionNotifyDragStartReques(env, aniClass, requestStatus);
}

void ANICleanDragAction([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long dragActionPtr)
{
    DragAction* ptr = reinterpret_cast<DragAction *>(dragActionPtr);
    delete ptr;
    ptr = nullptr;
    dragActionPtr = 0;
}

void ANICleanDragPreview([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long dragPreviewPtr)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragControllerAniModifier()) {
        return;
    }
    modifier->getDragControllerAniModifier()->aniCleanDragPreview(env, aniClass, dragPreviewPtr);
}
} // namespace OHOS::Ace::Ani