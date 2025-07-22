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

#include "utils/ani_utils.h"
#include "log/log.h"
#include "utils/convert_utils.h"
#include "core/gestures/drag_event.h"
#include "load.h"
#include "pixel_map_taihe_ani.h"
#include "udmf_ani_converter_utils.h"
#include "core/common/udmf/udmf_client.h"
#include "udmf_async_client.h"

namespace OHOS::Ace::Ani {
void DragEventSetData([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object data)
{
    auto dragEvent = reinterpret_cast<ani_ref>(pointer);
    auto dataValue = OHOS::UDMF::AniConverter::UnwrapUnifiedData(env, data);
    auto unifiedData = reinterpret_cast<void*>(dataValue.get());
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
    env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedData;", &dataClass);
    env->Object_InstanceOf(unifiedData_obj, dataClass, &isUnifiedData);
    if (!isUnifiedData) {
        return result_obj;
    }
    return unifiedData_obj;
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
    env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/Summary;", &summaryClass);
    env->Object_InstanceOf(summary_obj, summaryClass, &isSummary);
    if (!isSummary) {
        return result_obj;
    }
    return summary_obj;
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

void DragSetAllowDrop([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_array_ref array, [[maybe_unused]] ani_int length)
{
    auto* frameNode = reinterpret_cast<ArkUINodeHandle>(pointer);
    if (!frameNode || length < 0) {
        return;
    }

    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getDragAniModifier() || !env) {
        return;
    }
    if (length == 0) {
        modifier->getDragAniModifier()->setDragAllowDrop(frameNode, nullptr, 0);
        return;
    }
    ani_ref ref = nullptr;
    const char** allowDrops = new const char* [length];
    std::vector<std::string> allowDropsSave(length);
    for (int i = 0; i < length; i++) {
        if (ANI_OK == env->Array_Get_Ref(array, i, &ref)) {
            ani_string stringValue = static_cast<ani_string>(ref);
            std::string dataType = AniUtils::ANIStringToStdString(env, stringValue);
            allowDropsSave[i] = dataType;
            allowDrops[i] = dataType.c_str();
        }
    }
    modifier->getDragAniModifier()->setDragAllowDrop(frameNode, allowDrops, static_cast<ArkUI_Int32>(length));
    delete[] allowDrops;
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
            if (ANI_OK == env->Object_CallMethodByName_Boolean(value, "unboxed", ":z", &onlyForLiftingValue)) {
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
            if (ANI_OK == env->Object_CallMethodByName_Boolean(value, "unboxed", ":z", &delayCreatingValue)) {
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
} // namespace OHOS::Ace::Ani