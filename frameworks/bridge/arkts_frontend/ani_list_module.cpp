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

#include "bridge/arkts_frontend/ani_list_module.h"

#include <ani.h>
#include <optional>
#include <vector>

#include "base/geometry/calc_dimension.h"
#include "base/log/log.h"
#include "base/utils/string_utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::Framework {

bool ParseChange(ani_env* env, const ani_ref& change, const float defaultSize, int32_t& start,
    int32_t& deleteCount, std::vector<float>& newChildrenSize)
{
    if (env->Object_GetPropertyByName_Int(static_cast<ani_object>(change), "start", &start) != ANI_OK || start < 0) {
        return false;
    }
    if (env->Object_GetPropertyByName_Int(static_cast<ani_object>(change), "deleteCount", &deleteCount) != ANI_OK) {
        // If only input one parameter, set -1 to deleteCount for deleting elements after index 'start' in the array.
        deleteCount = -1;
    } else if (deleteCount < 0) {
        deleteCount = 0;
    }
    ani_ref childrenSize;
    env->Object_GetPropertyByName_Ref(static_cast<ani_object>(change), "childrenSize", &childrenSize);

    ani_size childrenSizeCount;
    if (env->Array_GetLength(static_cast<ani_array_ref>(childrenSize), &childrenSizeCount) != ANI_OK) {
        return true;
    } 
    for (size_t j = 0; j < childrenSizeCount; ++j) {
        // -1.0: represent default size.
        ani_double childSize = -1.0;
        ani_ref itemSize;
        ani_boolean isUndefined = false;
        if (env->Array_Get_Ref(static_cast<ani_array_ref>(childrenSize), j, &itemSize) != ANI_OK ||
            env->Reference_IsUndefined(itemSize, &isUndefined) != ANI_OK || isUndefined || ANI_OK !=
            env->Object_CallMethodByName_Double(static_cast<ani_object>(itemSize), "unboxed", ":d", &childSize) ||
            Negative(childSize)) {
            newChildrenSize.emplace_back(-1.0f);
        } else {
            newChildrenSize.emplace_back(Dimension(childSize, DimensionUnit::VP).ConvertToPx());
        }
    }
    return true;
}

void SyncChildrenSize(ani_env* env, const ani_object& obj, RefPtr<NG::ListChildrenMainSize> childrenSize)
{
    ani_ref sizeArray;
    if (env->Object_GetPropertyByName_Ref(static_cast<ani_object>(obj), "sizeArray", &sizeArray) != ANI_OK) {
        return;
    }
    ani_size aniLength;
    if (env->Array_GetLength(static_cast<ani_array_ref>(sizeArray), &aniLength) != ANI_OK) {
        return;
    }
    childrenSize->ResizeChildrenSize(0);
    for (ani_size i = 0; i < aniLength; ++i) {
        // -1.0: represent default size.
        ani_double childSize = -1.0;
        ani_ref itemSize;
        ani_boolean isUndefined = false;
        if (env->Array_Get_Ref(static_cast<ani_array_ref>(sizeArray), i, &itemSize) != ANI_OK ||
            env->Reference_IsUndefined(itemSize, &isUndefined) != ANI_OK || isUndefined) {
            childrenSize->SyncChildrenSize(-1.0f);
            continue;
        }
        env->Object_CallMethodByName_Double(static_cast<ani_object>(itemSize), "unboxed", ":d", &childSize);
        if (Negative(childSize)) {
            childrenSize->SyncChildrenSize(-1.0f);
        } else {
            childrenSize->SyncChildrenSize(Dimension(childSize, DimensionUnit::VP).ConvertToPx());
        }
    }
    childrenSize->SyncChildrenSizeOver();
}

void AniListModule::SetListChildrenMainSize(ani_env* env, ani_long ptr, ani_object obj)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(ptr);
    CHECK_NULL_VOID(frameNode);
    const auto& nodeTag = frameNode->GetHostTag();
    if (V2::LIST_ETS_TAG != nodeTag && V2::LIST_ITEM_GROUP_ETS_TAG != nodeTag) {
        TAG_LOGW(AceLogTag::ACE_LIST, "input FrameNode inValid.");
        return;
    }
    ani_class listChildrenMainSize;
    if (env->FindClass("arkui.component.common.ChildrenMainSize", &listChildrenMainSize) != ANI_OK) {
        TAG_LOGW(AceLogTag::ACE_LIST, "no class ListChildrenMainSize be found.");
        return;
    }
    ani_boolean isExpectedType = ANI_FALSE;
    env->Object_InstanceOf(obj, listChildrenMainSize, &isExpectedType);
    if (isExpectedType) {
        SetChildrenMainSize(env, obj, frameNode, V2::LIST_ETS_TAG == nodeTag);
    }
}

void AniListModule::SetChildrenMainSize(
    ani_env* env, const ani_object& obj, NG::FrameNode* node, bool isList)
{
    ani_double defaultSize = 0.0;
    if (env->Object_GetPropertyByName_Double(obj, "childDefaultSize", &defaultSize) != ANI_OK ||
        !NonNegative(defaultSize)) {
        TAG_LOGW(AceLogTag::ACE_LIST, "AniListModule input parameter defaultSize check failed.");
        return;
    }
    auto listChildrenMainSize = isList ? NG::ListModelStatic::GetOrCreateListChildrenMainSize(node) :
        NG::ListItemGroupModelStatic::GetOrCreateListChildrenMainSize(node);
    CHECK_NULL_VOID(listChildrenMainSize);
    listChildrenMainSize->UpdateDefaultSize(Dimension(defaultSize, DimensionUnit::VP).ConvertToPx());

    if (listChildrenMainSize->NeedSync()) {
        SyncChildrenSize(env, obj, listChildrenMainSize);
    } else {
        ani_ref changes;
        if (env->Object_GetPropertyByName_Ref(static_cast<ani_object>(obj), "changeArray", &changes) != ANI_OK) {
            TAG_LOGI(AceLogTag::ACE_LIST, "AniListModule changeArray parse fail.");
            return;
        }
        ani_size length;
        if (env->Array_GetLength(static_cast<ani_array_ref>(changes), &length) != ANI_OK) {
            return;
        }
        ani_class childrenSizeInfo;
        if (env->FindClass("arkui.component.common.ChildrenSizeChangeInfo", &childrenSizeInfo) != ANI_OK) {
            return;
        }
        for (ani_size i = 0; i < length; ++i) {
            ani_ref change;
            if (env->Array_Get_Ref(static_cast<ani_array_ref>(changes), i, &change) != ANI_OK) {
                continue;
            }
            ani_boolean isChildrenSizeInfo;
            env->Object_InstanceOf(static_cast<ani_object>(change), childrenSizeInfo, &isChildrenSizeInfo);
            if (!isChildrenSizeInfo) {
                continue;
            }
            int32_t start = 0;
            int32_t deleteCount = 0;
            std::vector<float> newChildrenSize;
            if (!ParseChange(env, change, defaultSize, start, deleteCount, newChildrenSize)) {
                SyncChildrenSize(env, obj, listChildrenMainSize);
                break;
            }
            listChildrenMainSize->ChangeData(start, deleteCount, newChildrenSize);
        }
    }
}
} // namespace OHOS::Ace::Framework
