/*
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

#include "native_drag_drop_global.h"
#include <cstdint>
#include <memory>

#include "core/common/udmf/udmf_client.h"
#include "core/gestures/drag_event.h"
#include "load.h"
#include "log/log.h"
#include "pixel_map_taihe_ani.h"
#include "securec.h"
#include "udmf_ani_converter_utils.h"
#include "udmf_async_client.h"
#include "utils/ani_utils.h"
#include "utils/convert_utils.h"

namespace OHOS::Ace::Ani {
namespace {
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr int NUM_6 = 6;
constexpr int NUM_7 = 7;
}
void DragEventSetData([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object data)
{
    auto dragEvent = reinterpret_cast<ani_ref>(pointer);
    auto dataValue = OHOS::UDMF::AniConverter::UnwrapUnifiedData(env, data);
    auto unifiedData = reinterpret_cast<void*>(&dataValue);
    if (!dragEvent || !unifiedData) {
        return;
    }
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragAniModifier() || !env) {
        return;
    }
    modifier->getDragAniModifier()->setDragData(dragEvent, reinterpret_cast<ani_ref>(unifiedData));
}

ani_object DragEventGetData([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer)
{
    ani_object result_obj = {};
    auto dragEvent = reinterpret_cast<ani_ref>(pointer);
    if (!dragEvent) {
        return result_obj;
    }
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragAniModifier() || !env) {
        return result_obj;
    }
    auto unifiedDataPtr = reinterpret_cast<OHOS::UDMF::UnifiedData*>(
        modifier->getDragAniModifier()->getDragData(dragEvent));
    if (!unifiedDataPtr) {
        return result_obj;
    }
    std::shared_ptr<OHOS::UDMF::UnifiedData> unifiedData(unifiedDataPtr);
    auto unifiedData_obj = OHOS::UDMF::AniConverter::WrapUnifiedData(env, unifiedData);
    ani_boolean isUnifiedData;
    ani_class dataClass;
    env->FindClass("@ohos.data.unifiedDataChannel.unifiedDataChannel.UnifiedData", &dataClass);
    env->Object_InstanceOf(unifiedData_obj, dataClass, &isUnifiedData);
    if (!isUnifiedData) {
        return result_obj;
    }
    return unifiedData_obj;
    return {};
}

ani_object DragEventGetSummary([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer)
{
    ani_object result_obj = {};
    auto dragEvent = reinterpret_cast<ani_ref>(pointer);
    if (!dragEvent) {
        return result_obj;
    }
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragAniModifier() || !env) {
        return result_obj;
    }
    auto summary = std::make_shared<OHOS::UDMF::Summary>();
    modifier->getDragAniModifier()->getDragSummary(dragEvent, reinterpret_cast<ani_ref>(summary.get()));

    auto summary_obj = OHOS::UDMF::AniConverter::WrapSummary(env, summary);
    ani_boolean isSummary;
    ani_class summaryClass;
    env->FindClass("@ohos.data.unifiedDataChannel.unifiedDataChannel.Summary", &summaryClass);
    env->Object_InstanceOf(summary_obj, summaryClass, &isSummary);
    if (!isSummary) {
        return result_obj;
    }
    return summary_obj;
    return {};
}

ani_string DragEveStartDataLoading([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object dataSyncOptions)
{
    ani_string value = {};
    auto dragEvent = reinterpret_cast<ani_ref>(pointer);
    const auto* modifier = GetNodeAniModifier();
    if (!dragEvent || !modifier || !modifier->getDragAniModifier() || !env) {
        return value;
    }
    const char* ptr = modifier->getDragAniModifier()->getUdKey(dragEvent);
    std::string key = ptr ? ptr : "";
    if (key.empty()) {
        AniUtils::AniThrow(env, "Operation not allowed for current phase.", ERROR_CODE_DRAG_DATA_NOT_ONDROP);
        env->DestroyLocalScope();
        return value;
    }
    auto getDataParams = OHOS::UDMF::AniConverter::UnwrapGetDataParams(env, dataSyncOptions, key);
    getDataParams.query.key = key;
    getDataParams.query.intention = UDMF::Intention::UD_INTENTION_DRAG;
    int32_t status = OHOS::UDMF::UdmfAsyncClient::GetInstance().StartAsyncDataRetrieval(getDataParams);
    if (status != 0) {
        return value;
    }
    auto result = AniUtils::StdStringToANIString(env, key);
    return result.value_or(value);
    return value;
}

void DragEventEnableInternalDropAnimation([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_string configuration)
{
    auto dragEvent = reinterpret_cast<ani_ref>(pointer);
    const auto* modifier = GetNodeAniModifier();
    if (!dragEvent || !modifier || !modifier->getDragAniModifier() || !env) {
        return;
    }

    auto isOnDrop = modifier->getDragAniModifier()->isOnDropPhase();
    if (!isOnDrop) {
        AniUtils::AniThrow(env, "Operation not allowed for current phase.", ERROR_CODE_DRAG_DATA_NOT_ONDROP);
        return;
    }

    auto configStr = AniUtils::ANIStringToStdString(env, configuration);
    int32_t ret;
    modifier->getDragAniModifier()->enableInternalDropAnimation(dragEvent, configStr, ret);
    switch (ret) {
        case ERROR_CODE_NO_ERROR:
            break;
        case ERROR_CODE_PARAM_INVALID:
            AniUtils::AniThrow(env, "Invalid input parameter.", ERROR_CODE_PARAM_INVALID);
            break;
        case ERROR_CODE_VERIFICATION_FAILED:
            AniUtils::AniThrow(env, "Permission verification failed.", ERROR_CODE_VERIFICATION_FAILED);
            break;
        case ERROR_CODE_SYSTEMCAP_ERROR:
            AniUtils::AniThrow(env, "Capability not supported.", ERROR_CODE_SYSTEMCAP_ERROR);
            break;
        default:
            HILOGE("AceDrag Enable internal drop animation failed, return value is %{public}d", ret);
    }
}

void DragEventSetPixelMap([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object pixelMap)
{
    auto dragEvent = reinterpret_cast<ani_ref>(pointer);
    auto pixelMapValue = OHOS::Media::PixelMapTaiheAni::GetNativePixelMap(env, pixelMap);
    if (!dragEvent || !pixelMapValue) {
        return;
    }
    auto pixelMapPtr = reinterpret_cast<void*>(&pixelMapValue);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragAniModifier() || !env) {
        return;
    }
    modifier->getDragAniModifier()->setDragDropInfoPixelMap(dragEvent, reinterpret_cast<ani_ref>(pixelMapPtr));
}

void DragEventSetExtraInfo([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_string extraInfo)
{
    auto dragEvent = reinterpret_cast<ani_ref>(pointer);
    if (!dragEvent) {
        return;
    }
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragAniModifier() || !env) {
        return;
    }
    std::string aniExtraInfo = AniUtils::ANIStringToStdString(env, extraInfo);
    modifier->getDragAniModifier()->setDragDropInfoExtraInfo(dragEvent, aniExtraInfo.c_str());
}

void DragEventSetCustomNode([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_long node)
{
    auto dragEvent = reinterpret_cast<ani_ref>(pointer);
    auto* customNode = reinterpret_cast<ArkUINodeHandle>(node);
    if (!dragEvent || !customNode) {
        return;
    }
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragAniModifier() || !env) {
        return;
    }
    modifier->getDragAniModifier()->setDragDropInfoCustomNode(dragEvent, customNode);
}

void DragSetAllowDropNull([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer)
{
    auto* frameNode = reinterpret_cast<ArkUINodeHandle>(pointer);
    if (!frameNode) {
        return;
    }
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragAniModifier() || !env) {
        return;
    }
    modifier->getDragAniModifier()->setDragAllowDropNull(frameNode);
}

std::string GetAniStringEnum(ani_env* env, ani_array array, ani_int index, bool& isSuccess)
{
    ani_ref modeRef;
    if (ANI_OK != env->Object_CallMethodByName_Ref(
        array, "$_get", "i:C{std.core.Object}", &modeRef, index)) {
        isSuccess = false;
        return "";
    }
    if (AniUtils::IsUndefined(env, static_cast<ani_object>(modeRef))) {
        isSuccess = false;
        return "";
    }
    ani_string dataTypeAni;
    if (AniUtils::IsString(env, static_cast<ani_object>(modeRef))) {
        dataTypeAni = static_cast<ani_string>(modeRef);
    } else {
        if ((ANI_OK != env->EnumItem_GetValue_String(static_cast<ani_enum_item>(modeRef), &dataTypeAni))) {
            isSuccess = false;
            return "";
        }
    }
    return AniUtils::ANIStringToStdString(env, dataTypeAni);
}

void DragSetAllowDrop([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_array array)
{
    auto* frameNode = reinterpret_cast<ArkUINodeHandle>(pointer);
    CHECK_NULL_VOID(frameNode);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragAniModifier() || !env) {
        return;
    }

    if (!AniUtils::IsClassObject(env, array, "std.core.Array")) {
        modifier->getDragAniModifier()->setDragAllowDrop(frameNode, nullptr, 0);
        return;
    }
    ani_size length;
    ani_array arrayObj = static_cast<ani_array>(array);
    if (ANI_OK != env->Array_GetLength(arrayObj, &length)) {
        return;
    }
    int32_t lengthInt = static_cast<int32_t>(length);

    if (length <= 0) {
        modifier->getDragAniModifier()->setDragAllowDrop(frameNode, nullptr, 0);
        return;
    }

    char** allowDrops = new char* [lengthInt];
    bool isSuccess = true;
    int32_t count = 0;
    for (int32_t i = 0; i < lengthInt; i++) {
        auto dataType = GetAniStringEnum(env, array, static_cast<ani_int>(i), isSuccess);
        if (!isSuccess) {
            break;
        }
        auto size = dataType.length() + 1;
        allowDrops[i] = new char[size];
        auto errCode = strcpy_s(allowDrops[i], size, dataType.c_str());
        if (errCode != 0) {
            isSuccess = false;
            break;
        }
        count++;
    }
    if (isSuccess) {
        modifier->getDragAniModifier()->setDragAllowDrop(frameNode, allowDrops, static_cast<ArkUI_Int32>(length));
    }
    for (int32_t i = 0; i < lengthInt && i < count; i++) {
        delete[] allowDrops[i];
        allowDrops[i] = nullptr;
    }
    delete[] allowDrops;
    allowDrops = nullptr;
}

void DragSetDragPreview([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object dragInfo)
{
    auto* frameNode = reinterpret_cast<ArkUINodeHandle>(pointer);
    if (!frameNode || !dragInfo) {
        return;
    }
    ani_boolean isUndef = ANI_FALSE;
    ArkUIDragInfo info;
    ani_ref pixelMap;
    std::shared_ptr<Media::PixelMap> pixelMapValue = nullptr;
    if (ANI_OK == env->Object_GetFieldByName_Ref(dragInfo, "pixelMap", &pixelMap)) {
        env->Reference_IsUndefined(pixelMap, &isUndef);
        if (isUndef != ANI_TRUE) {
            ani_object value = static_cast<ani_object>(pixelMap);
            pixelMapValue = OHOS::Media::PixelMapTaiheAni::GetNativePixelMap(env, value);
            if (pixelMapValue) {
                info.pixelMap = reinterpret_cast<void*>(&pixelMapValue);
            }
        }
    }

    ani_ref onlyForLifting;
    if (ANI_OK == env->Object_GetFieldByName_Ref(dragInfo, "onlyForLifting", &onlyForLifting)) {
        env->Reference_IsUndefined(onlyForLifting, &isUndef);
        if (isUndef != ANI_TRUE) {
            ani_object value = static_cast<ani_object>(onlyForLifting);
            ani_boolean onlyForLiftingValue;
            if (ANI_OK == env->Object_CallMethodByName_Boolean(value, "toBoolean", ":z", &onlyForLiftingValue)) {
                info.onlyForLifting = static_cast<bool>(onlyForLiftingValue);
            }
        }
    }

    ani_ref delayCreating;
    if (ANI_OK == env->Object_GetFieldByName_Ref(dragInfo, "onlyForLifting", &delayCreating)) {
        env->Reference_IsUndefined(delayCreating, &isUndef);
        if (isUndef != ANI_TRUE) {
            ani_object value = static_cast<ani_object>(delayCreating);
            ani_boolean delayCreatingValue;
            if (ANI_OK == env->Object_CallMethodByName_Boolean(value, "toBoolean", ":z", &delayCreatingValue)) {
                info.delayCreating = static_cast<bool>(delayCreatingValue);
            }
        }
    }

    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragAniModifier() || !env) {
        return;
    }
    modifier->getDragAniModifier()->setDragPreview(frameNode, info);
}

bool ParsePreviewOptionMode(
    ani_env* env, ArkUIDragPreviewOption& previewOptions, ani_object dragPreviewMode, bool& isAuto)
{
    CHECK_NULL_RETURN(env, false);
    if (isAuto) {
        return true;
    }
    ani_int dragPreviewModeAni;
    if ((ANI_OK != env->EnumItem_GetValue_Int(static_cast<ani_enum_item>(dragPreviewMode), &dragPreviewModeAni))) {
        return false;
    }
    auto mode = static_cast<int32_t>(dragPreviewModeAni);
    switch (mode) {
        case NUM_1:
            previewOptions.ResetDragPreviewMode();
            isAuto = true;
            break;
        case NUM_2:
            previewOptions.isScaleEnabled = false;
            break;
        case NUM_3:
            previewOptions.isDefaultShadowEnabled = true;
            break;
        case NUM_4:
            previewOptions.isDefaultRadiusEnabled = true;
            break;
        case NUM_5:
            previewOptions.isDefaultDragItemGrayEffectEnabled = true;
            break;
        case NUM_6:
            previewOptions.isMultiTiled = true;
            break;
        case NUM_7:
            previewOptions.isTouchPointCalculationBasedOnFinalPreviewEnable = true;
            break;
        default:
            break;
    }
    return true;
}

bool ParseDragPreviewMode(ani_env* env, ArkUIDragPreviewOption& previewOptions, ani_object value)
{
    CHECK_NULL_RETURN(env, false);
    ani_ref modeAni;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(value, "mode", &modeAni)) {
        return false;
    }
    ani_object modeObj = static_cast<ani_object>(modeAni);
    if (AniUtils::IsUndefined(env, modeObj)) {
        return true;
    }
    bool isAuto = false;
    if (AniUtils::IsClassObject(env, modeObj, "std.core.Array")) {
        ani_size length;
        ani_array arrayObj = static_cast<ani_array>(modeObj);
        if (ANI_OK != env->Array_GetLength(arrayObj, &length)) {
            return false;
        }
        int32_t lengthInt = static_cast<int32_t>(length);
        for (int32_t i = 0; i < lengthInt; i++) {
            ani_ref modeRef;
            if (ANI_OK != env->Object_CallMethodByName_Ref(
                modeObj, "$_get", "i:C{std.core.Object}", &modeRef, (ani_int)i)) {
                return false;
            }
            if (AniUtils::IsUndefined(env, static_cast<ani_object>(modeRef))) {
                continue;
            }
            if (!ParsePreviewOptionMode(env, previewOptions, static_cast<ani_object>(modeRef), isAuto)) {
                return false;
            }
        }
    } else {
        if (!ParsePreviewOptionMode(env, previewOptions, modeObj, isAuto)) {
            return false;
        }
    }
    return true;
}

void ApplyModifierToNode(ani_env* env, ani_object modifier, ani_long node)
{
    CHECK_NULL_VOID(env);
    CHECK_NULL_VOID(node);
    ani_module module;
    auto status = env->FindModule("arkui.ApplyModifierToNode", &module);
    if (ANI_OK != status) {
        HILOGE("AceDrag: find ApplyModifierToNode module failed status = %{public}d", static_cast<int32_t>(status));
        return;
    }
    ani_function applyModifierFunc;
    status = env->Module_FindFunction(module, "applyImageModifierToNode", "C{arkui.ImageModifier.ImageModifier}l:",
        &applyModifierFunc);
    if (ANI_OK != status) {
        HILOGE("AceDrag: find applyImageModifierToNode failed status = %{public}d", static_cast<int32_t>(status));
        return;
    }

    status = env->Function_Call_Void(applyModifierFunc, modifier, node);
    if (ANI_OK != status) {
        HILOGE("AceDrag: ApplyModifier failed status = %{public}d", static_cast<int32_t>(status));
    }
}

bool ParseDragPreviewModifier(ani_env* env, ArkUIDragPreviewOption& previewOptions, ani_object value)
{
    CHECK_NULL_RETURN(env, false);
    ani_ref modifierAni;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(value, "modifier", &modifierAni)) {
        return false;
    }
    ani_object modifier = static_cast<ani_object>(modifierAni);
    if (AniUtils::IsUndefined(env, modifier)) {
        return true;
    }

    ani_vm* vm = nullptr;
    env->GetVM(&vm);
    std::shared_ptr<ani_wref> weakRef(new ani_wref, [vm](ani_wref* wref) {
        ani_env* env = nullptr;
        vm->GetEnv(ANI_VERSION_1, &env);
        env->WeakReference_Delete(*wref);
    });
    env->WeakReference_Create(modifier, weakRef.get());

    previewOptions.modifier = [vm, weakRef](void* ptr) {
        CHECK_NULL_VOID(vm);
        ani_env* env = nullptr;
        if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
            return;
        }
        CHECK_NULL_VOID(env);
        ani_boolean released;
        ani_ref localRef;
        env->WeakReference_GetReference(*weakRef, &released, &localRef);
        if (!released) {
            ApplyModifierToNode(env, static_cast<ani_object>(localRef), reinterpret_cast<ani_long>(ptr));
        }
    };
    return true;
}

bool ParseNumberBadge(ani_env* env, ArkUIDragPreviewOption& previewOptions, ani_object value)
{
    CHECK_NULL_RETURN(env, false);
    ani_ref numberBadgeAni;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(value, "numberBadge", &numberBadgeAni)) {
        return false;
    }
    ani_object numberBadgeObj = static_cast<ani_object>(numberBadgeAni);
    if (AniUtils::IsUndefined(env, numberBadgeObj)) {
        return true;
    }
    if (AniUtils::IsClassObject(env, numberBadgeObj, "std.core.Boolean")) {
        previewOptions.isNumber = false;
        ani_boolean aniValue;
        if (ANI_OK == env->Object_CallMethodByName_Boolean(numberBadgeObj, "toBoolean", ":z", &aniValue)) {
            previewOptions.isShowBadge = static_cast<bool>(aniValue);
        }
        return true;
    }
    if (!AniUtils::IsClassObject(env, numberBadgeObj, "std.core.Long")) {
        return false;
    }
    ani_long numberValue;
    if (ANI_OK != env->Object_CallMethodByName_Long(numberBadgeObj, "toLong", ":l", &numberValue)) {
        return false;
    }
    auto number = static_cast<int64_t>(numberValue);
    if (number < 0 || number > INT_MAX) {
        previewOptions.isNumber = false;
        previewOptions.isShowBadge = true;
    } else {
        previewOptions.isNumber = true;
        previewOptions.badgeNumber = static_cast<int32_t>(number);
    }
    return true;
}

bool ParseSizeChangeEffect(ani_env* env, ArkUIDragPreviewOption& previewOptions, ani_object value)
{
    CHECK_NULL_RETURN(env, false);
    ani_ref sizeChangeEffectAni;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(value, "sizeChangeEffect", &sizeChangeEffectAni)) {
        return false;
    }
    ani_object sizeChangeEffect = static_cast<ani_object>(sizeChangeEffectAni);
    if (AniUtils::IsUndefined(env, sizeChangeEffect)) {
        return true;
    }
    ani_int sizeChangeEffectInt;
    if ((ANI_OK != env->EnumItem_GetValue_Int(static_cast<ani_enum_item>(sizeChangeEffect), &sizeChangeEffectInt))) {
        return false;
    }
    previewOptions.sizeChangeEffect = static_cast<int32_t>(sizeChangeEffectInt);
    return true;
}

void ParseDragPreviewOptions(ani_env* env, ArkUIDragPreviewOption& previewOptions, ani_object value)
{
    CHECK_NULL_VOID(env);
    if (AniUtils::IsUndefined(env, value)) {
        return;
    }
    ParseDragPreviewMode(env, previewOptions, value);
    ParseDragPreviewModifier(env, previewOptions, value);
    ParseNumberBadge(env, previewOptions, value);
    ParseSizeChangeEffect(env, previewOptions, value);
}

void SetPropertyValueByName(ani_env* env, ani_object obj, std::string name, bool& target)
{
    CHECK_NULL_VOID(env);
    ani_ref value;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(obj, name.c_str(), &value)) {
        return;
    }
    ani_object valueObj = static_cast<ani_object>(value);
    if (AniUtils::IsUndefined(env, valueObj)) {
        return;
    }
    ani_boolean aniValue;
    if (ANI_OK != env->Object_CallMethodByName_Boolean(valueObj, "toBoolean", ":z", &aniValue)) {
        return;
    }
    target = static_cast<bool>(aniValue);
}

void ParseDragInteractionOptions(ani_env* env, ArkUIDragPreviewOption& previewOptions,
    ani_object dragInteractionOptions)
{
    CHECK_NULL_VOID(env);
    if (AniUtils::IsUndefined(env, dragInteractionOptions)) {
        return;
    }
    SetPropertyValueByName(env, dragInteractionOptions, "isMultiSelectionEnabled",
        previewOptions.isMultiSelectionEnabled);
    SetPropertyValueByName(env, dragInteractionOptions, "defaultAnimationBeforeLifting",
        previewOptions.defaultAnimationBeforeLifting);
    SetPropertyValueByName(env, dragInteractionOptions, "enableHapticFeedback", previewOptions.enableHapticFeedback);
    SetPropertyValueByName(env, dragInteractionOptions, "enableEdgeAutoScroll", previewOptions.enableEdgeAutoScroll);
    SetPropertyValueByName(env, dragInteractionOptions, "isLiftingDisabled", previewOptions.isLiftingDisabled);
}

void DragSetDragPreviewOptions([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object value, [[maybe_unused]] ani_object options)
{
    auto* frameNode = reinterpret_cast<ArkUINodeHandle>(pointer);
    CHECK_NULL_VOID(frameNode);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragAniModifier() || !env) {
        return;
    }

    ArkUIDragPreviewOption previewOptions;
    ParseDragPreviewOptions(env, previewOptions, value);
    ParseDragInteractionOptions(env, previewOptions, options);
    modifier->getDragAniModifier()->setDragPreviewOptions(frameNode, previewOptions);
}

ani_long ExtractorFromUnifiedDataToPtr(ani_env* env, [[maybe_unused]] ani_object object, ani_object data)
{
    auto dataValue = OHOS::UDMF::AniConverter::UnwrapUnifiedData(env, data);
    auto peer = reinterpret_cast<void*>(&dataValue);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragAniModifier() || !env) {
        return 0;
    }
    return modifier->getDragAniModifier()->createUnifiedDataPeer(peer);
}

ani_object ExtractorFromPtrToUnifiedData(ani_env* env, [[maybe_unused]] ani_object object, ani_long pointer)
{
    ani_object result_obj = {};
        const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragAniModifier() || !env) {
        return result_obj;
    }
    auto unifiedDataPtr = modifier->getDragAniModifier()->getUnifiedData(pointer).GetSharedPtr();
    if (!unifiedDataPtr) {
        return result_obj;
    }
    std::shared_ptr<OHOS::UDMF::UnifiedData> unifiedData =
        std::static_pointer_cast<OHOS::UDMF::UnifiedData>(unifiedDataPtr);
    auto unifiedData_obj = OHOS::UDMF::AniConverter::WrapUnifiedData(env, unifiedData);
    ani_boolean isUnifiedData;
    ani_class dataClass;
    env->FindClass("@ohos.data.unifiedDataChannel.unifiedDataChannel.UnifiedData", &dataClass);
    env->Object_InstanceOf(unifiedData_obj, dataClass, &isUnifiedData);
    if (!isUnifiedData) {
        return result_obj;
    }
    return unifiedData_obj;
}
} // namespace OHOS::Ace::Ani