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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_PICKER_CONTAINER_PICKER_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_PICKER_CONTAINER_PICKER_UTILS_H

#include <optional>

#include "base/geometry/axis.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/container_picker/container_picker_layout_property.h"
#include "core/components_ng/property/measure_utils.h"
namespace OHOS::Ace::NG {

struct PickerItemInfo {
    float startPos = 0.0f;
    float endPos = 0.0f;
    RefPtr<FrameNode> node = nullptr;
};

namespace {
const float PICKER_ITEM_DEFAULT_HEIGHT = 130.0f;
} // namespace
class ContainerPickerUtils {
public:
    ContainerPickerUtils() = delete;
    ~ContainerPickerUtils() = delete;
    using PositionMap = std::map<int32_t, PickerItemInfo>;

    static LayoutConstraintF CreateChildConstraint(
        const RefPtr<ContainerPickerLayoutProperty>& property, const OptionalSizeF& idealSize)
    {
        CHECK_NULL_RETURN(property, {});
        auto layoutConstraint = property->CreateChildConstraint();
        layoutConstraint.parentIdealSize = idealSize;
        auto childSelfIdealSize = idealSize;
        auto width = idealSize.CrossSize(Axis::VERTICAL);
        childSelfIdealSize.SetWidth(width);
        childSelfIdealSize.SetHeight(PICKER_ITEM_DEFAULT_HEIGHT);
        layoutConstraint.selfIdealSize = childSelfIdealSize;
        return layoutConstraint;
    }

    static int32_t GetLoopIndex(int32_t originalIndex, int32_t totalItemCount)
    {
        if (totalItemCount <= 0) {
            return originalIndex;
        }
        auto loopIndex = originalIndex;
        while (loopIndex < 0) {
            loopIndex = loopIndex + totalItemCount;
        }
        loopIndex %= totalItemCount;
        return loopIndex;
    }

    static std::pair<int32_t, PickerItemInfo> CalcCurrentMiddleItem(
        const PositionMap& itemPosition, float height, int32_t totalItemCount, bool isLoop)
    {
        if (itemPosition.empty()) {
            return std::make_pair(0, PickerItemInfo {});
        }
        auto middlePos = height / 2;
        for (const auto& item : itemPosition) {
            auto index = GetLoopIndex(item.first, totalItemCount);
            auto startPos = item.second.startPos;
            auto endPos = item.second.endPos;
            if (LessOrEqual(startPos, middlePos) && GreatOrEqual(endPos, middlePos)) {
                return std::make_pair(index, PickerItemInfo { item.second.startPos, endPos });
            }
            if (LessOrEqual(startPos, middlePos) && LessOrEqual(endPos, middlePos) && !isLoop &&
                index == totalItemCount - 1) {
                return std::make_pair(index, PickerItemInfo { item.second.startPos, endPos });
            }
            if (GreatOrEqual(startPos, middlePos) && GreatOrEqual(endPos, middlePos) && !isLoop && index == 0) {
                return std::make_pair(index, PickerItemInfo { item.second.startPos, endPos });
            }
        }
        return std::make_pair(itemPosition.begin()->first,
            PickerItemInfo { itemPosition.begin()->second.startPos, itemPosition.begin()->second.endPos });
    }
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_PICKER_CONTAINER_PICKER_UTILS_H