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

#include "list_children_main_size_module.h"

#include <memory>

#include "base/utils/utils.h"
#include "load.h"
#include "base/log/log.h"
#include "utils/ani_utils.h"

namespace OHOS::Ace::Ani {
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
    if (env->Array_GetLength(static_cast<ani_array>(childrenSize), &childrenSizeCount) != ANI_OK) {
        return true;
    }
    for (size_t j = 0; j < childrenSizeCount; ++j) {
        // -1.0: represent default size.
        ani_double childSize = -1.0;
        ani_ref itemSize;
        ani_boolean isUndefined = false;
        if (env->Array_Get(static_cast<ani_array>(childrenSize), j, &itemSize) != ANI_OK ||
            env->Reference_IsUndefined(itemSize, &isUndefined) != ANI_OK || isUndefined || ANI_OK !=
            env->Object_CallMethodByName_Double(static_cast<ani_object>(itemSize), "toDouble", ":d", &childSize) ||
            Negative(childSize)) {
            newChildrenSize.emplace_back(-1.0f);
        } else {
            newChildrenSize.emplace_back(childSize);
        }
    }
    return true;
}

void SyncChildrenSize(ani_env* env, const ani_object& obj, const ArkUIAniListModifier* modifier, ArkUINodeHandle node)
{
    ani_ref sizeArray;
    if (env->Object_GetPropertyByName_Ref(static_cast<ani_object>(obj), "sizeArray", &sizeArray) != ANI_OK) {
        return;
    }
    ani_size aniLength;
    if (env->Array_GetLength(static_cast<ani_array>(sizeArray), &aniLength) != ANI_OK) {
        return;
    }
    modifier->resizeChildrenSize(node, 0);
    for (ani_size i = 0; i < aniLength; ++i) {
        // -1.0: represent default size.
        ani_double childSize = -1.0;
        ani_ref itemSize;
        ani_boolean isUndefined = false;
        if (env->Array_Get(static_cast<ani_array>(sizeArray), i, &itemSize) != ANI_OK ||
            env->Reference_IsUndefined(itemSize, &isUndefined) != ANI_OK || isUndefined) {
            modifier->syncChildrenSize(node, -1.0f);
            continue;
        }
        env->Object_CallMethodByName_Double(static_cast<ani_object>(itemSize), "toDouble", ":d", &childSize);
        modifier->syncChildrenSize(node, childSize);
    }
    modifier->syncChildrenSizeOver(node);
}

void SetChildrenMainSize(
    ani_env* env, const ani_object& obj, ArkUINodeHandle node, const ArkUIAniListModifier* modifier)
{
    ani_double defaultSize = 0.0;
    if (env->Object_GetPropertyByName_Double(obj, "childDefaultSize", &defaultSize) != ANI_OK || defaultSize < 0.0) {
        return;
    }

    bool needSync = modifier->updateDefaultSizeAndGetNeedSync(node, defaultSize);
    if (needSync) {
        SyncChildrenSize(env, obj, modifier, node);
    } else {
        ani_ref changes;
        if (env->Object_GetPropertyByName_Ref(static_cast<ani_object>(obj), "changeArray", &changes) != ANI_OK) {
            return;
        }
        ani_size length;
        if (env->Array_GetLength(static_cast<ani_array>(changes), &length) != ANI_OK) {
            return;
        }
        ani_class childrenSizeInfo;
        if (env->FindClass("arkui.component.common.ChildrenSizeChangeInfo", &childrenSizeInfo) != ANI_OK) {
            return;
        }
        for (ani_size i = 0; i < length; ++i) {
            ani_ref change;
            if (env->Array_Get(static_cast<ani_array>(changes), i, &change) != ANI_OK) {
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
                SyncChildrenSize(env, obj, modifier, node);
                break;
            }
            modifier->notifyChange(node, start, deleteCount, newChildrenSize);
        }
    }
}

void SetListChildrenMainSize(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_object childrenSize)
{
    const auto* modifier = GetNodeAniModifier();
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(ptr);
    if (!modifier || !arkNode) {
        return;
    }
    const auto* listModifier = modifier->getArkUIAniListModifier();
    if (!listModifier) {
        return;
    }
    ani_boolean isUndefined;
    env->Reference_IsUndefined(childrenSize, &isUndefined);
    if (isUndefined) {
        listModifier->resetListChildrenMainSize(arkNode);
        return;
    }

    ani_class listChildrenMainSize;
    if (env->FindClass("arkui.component.common.ChildrenMainSize", &listChildrenMainSize) != ANI_OK) {
        return;
    }
    ani_boolean isExpectedType = ANI_FALSE;
    env->Object_InstanceOf(childrenSize, listChildrenMainSize, &isExpectedType);
    if (isExpectedType) {
        SetChildrenMainSize(env, childrenSize, arkNode, listModifier);
    }
}
} // namespace OHOS::Ace::Ani
