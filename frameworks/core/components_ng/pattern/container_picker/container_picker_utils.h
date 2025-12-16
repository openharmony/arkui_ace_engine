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
const Dimension PICKER_DEFAULT_HEIGHT = 200.0_vp;
const Dimension PICKER_HEIGHT_BEFORE_ROTATE = 280.0_vp;
const Dimension PICKER_ITEM_HEIGHT = 40.0_vp;
const Dimension FIRST_ADJACENT_ITEM_HEIGHT = 36.3_vp;
const Dimension SECOND_ADJACENT_ITEM_HEIGHT = 24.9_vp;
const Dimension THIRD_ADJACENT_ITEM_HEIGHT = 11.4_vp;
const Dimension MAX_OVERSCROLL_OFFSET = 120.0_vp;
const Dimension FOCUS_DEFAULT_STROCK_WIDTH = 2.0_vp;
const Dimension DEFAULT_RADIUS = 12.0_vp;
const float HALF = 2.0;
const float FADE_OPACITY = 0.4f;
const float DISABLE_ALPHA = 0.6f;
const float REAL_K = 2.5f; // Control the relationship between scroll distance and speed.
const int32_t DISPLAY_COUNT = 7;
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

        auto layoutPolicy = property->GetLayoutPolicyProperty();
        if (layoutPolicy.has_value() && layoutPolicy->IsWidthMatch()) {
            auto widthOpt = childSelfIdealSize.Width();
            if (widthOpt.has_value()) {
                layoutConstraint.maxSize.SetWidth(widthOpt.value());
            }
        }
        auto maxHeight = static_cast<float>(PICKER_ITEM_HEIGHT.ConvertToPx());
        layoutConstraint.maxSize.SetHeight(maxHeight);
        childSelfIdealSize.Reset();
        childSelfIdealSize.SetHeight(maxHeight);
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
            // find middle index
            auto index = GetLoopIndex(item.first, totalItemCount);
            auto startPos = item.second.startPos;
            auto endPos = item.second.endPos;
            if (LessOrEqual(startPos, middlePos) && GreatOrEqual(endPos, middlePos)) {
                return std::make_pair(index, PickerItemInfo { item.second.startPos, endPos });
            }
        }
        for (const auto& item : itemPosition) {
            // find middle index when loop is false and overscrolled middle index
            auto index = GetLoopIndex(item.first, totalItemCount);
            auto startPos = item.second.startPos;
            auto endPos = item.second.endPos;
            if (LessOrEqual(endPos, middlePos) && !isLoop && index == totalItemCount - 1) {
                return std::make_pair(index, PickerItemInfo { item.second.startPos, endPos });
            }
            if (GreatOrEqual(startPos, middlePos) && !isLoop && index == 0) {
                return std::make_pair(index, PickerItemInfo { item.second.startPos, endPos });
            }
        }
        return std::make_pair(GetLoopIndex(itemPosition.begin()->first, totalItemCount),
            PickerItemInfo { itemPosition.begin()->second.startPos, itemPosition.begin()->second.endPos });
    }

    static float CalculateFriction(float gamma)
    {
        if (LessOrEqual(gamma, 0.0f)) {
            return 1.0f;
        }
        if (GreatOrEqual(gamma, 1.0f)) {
            gamma = 1.0f;
        }
        constexpr float scrollRatio = 0.72f;
        const float coefficient = ACE_E / (1.0f - ACE_E);
        auto fx = (gamma + coefficient) * (log(ACE_E - (ACE_E - 1.0f) * gamma) - 1.0f);
        return scrollRatio * fx / gamma;
    }
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_PICKER_CONTAINER_PICKER_UTILS_H
