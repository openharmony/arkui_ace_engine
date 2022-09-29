/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_LAYOUT_LINEAR_LAYOUT_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_LAYOUT_LINEAR_LAYOUT_UTILS_H

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/layout/layout_wrapper.h"

namespace OHOS::Ace::NG {
// used for linear measure and layout
struct LinearMeasureProperty {
    OptionalSizeF realSize;
    float crossSize = 0.0f;
    float allocatedSize = 0.0f;
    std::list<RefPtr<LayoutWrapper>> relativeNodes;
    std::list<RefPtr<LayoutWrapper>> weightNodes;
    float totalFlexWeight = 0.0f;
    float space = 0.0f;
};

struct LayoutConditions {
    LayoutWrapper* layoutWrapper = nullptr;
    bool isVertical = true;
    FlexAlign crossAlign = FlexAlign::FLEX_START;
    FlexAlign mainAlign = FlexAlign::FLEX_START;
    SizeF size { 0.0f, 0.0f };
    OffsetF paddingOffset { 0.0f, 0.0f };
    float space = 0.0f;
};

// BoxLayout is the class for box type measure, layout.
class LinearLayoutUtils {
public:
    LinearLayoutUtils() = delete;
    ~LinearLayoutUtils() = delete;

    // Called to perform measure current node and children.
    static void Measure(LayoutWrapper* layoutWrapper, bool isVertical);

    // Called to perform layout render node.
    static void Layout(LayoutWrapper* layoutWrapper, bool isVertical, FlexAlign crossAlign, FlexAlign mainAlign);

    static void LayoutCondition(
        const std::list<RefPtr<LayoutWrapper>>& children, TextDirection direction, LayoutConditions& layoutConditions);

    static OffsetF AdjustChildOnDirection(
        const RefPtr<LayoutWrapper>& child, const OffsetF& offset, TextDirection direction, float parentWidth);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_LAYOUT_LINEAR_LAYOUT_UTILS_H
