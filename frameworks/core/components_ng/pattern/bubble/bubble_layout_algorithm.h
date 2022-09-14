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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BUBBLE_BUBBLE_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BUBBLE_BUBBLE_LAYOUT_ALGORITHM_H

#include <string>

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "core/components/common/properties/border.h"
#include "core/components/common/properties/edge.h"
#include "core/components/common/properties/placement.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/pattern/bubble/bubble_layout_property.h"

namespace OHOS::Ace::NG {
// BubbleLayoutAlgorithm uses for Popup Node.
class ACE_EXPORT BubbleLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(BubbleLayoutAlgorithm, LayoutAlgorithm);

public:
    BubbleLayoutAlgorithm() = default;
    BubbleLayoutAlgorithm(int32_t id, const std::string& tag) : targetNodeId_(id), targetTag_(tag) {}
    ~BubbleLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;

    void Layout(LayoutWrapper* layoutWrapper) override;

    SizeF GetTargetSize() const
    {
        return targetSize_;
    }

    OffsetF GetTargetOffset() const
    {
        return targetOffset_;
    }

    SizeF GetChildSize() const
    {
        return childSize_;
    }

    OffsetF GetChildOffset() const
    {
        return childOffset_;
    }

    bool ShowBottomArrow() const
    {
        return showBottomArrow_;
    }

    bool ShowTopArrow() const
    {
        return showTopArrow_;
    }

    bool ShowCustomArrow() const
    {
        return showCustomArrow_;
    }

    OffsetF GetArrowPosition() const
    {
        return arrowPosition_;
    }

    RectF GetTouchRegion() const
    {
        return touchRegion_;
    }

private:
    enum class ErrorPositionType {
        NORMAL = 0,
        TOP_LEFT_ERROR,
        BOTTOM_RIGHT_ERROR,
    };

    void InitTargetSizeAndPosition();

    OffsetF GetChildPosition(const SizeF& childSize, const RefPtr<BubbleLayoutProperty>& layoutProp);
    void InitArrowState(const RefPtr<BubbleLayoutProperty>& layoutProp);

    void InitArrowTopAndBottomPosition(OffsetF& topArrowPosition, OffsetF& bottomArrowPosition, OffsetF& topPosition,
        OffsetF& bottomPosition, const SizeF& childSize);
    OffsetF GetPositionWithPlacement(const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition,
        const OffsetF& topArrowPosition, const OffsetF& bottomArrowPosition);
    ErrorPositionType GetErrorPositionType(const OffsetF& childOffset, const SizeF& childSize);
    OffsetF FitToScreen(const OffsetF& fitPosition, const SizeF& childSize);

    void UpdateCustomChildPosition(const RefPtr<BubbleLayoutProperty>& layoutProp);
    void UpdateTouchRegion();

    int32_t targetNodeId_ = -1;
    std::string targetTag_;

    SizeF targetSize_;
    OffsetF targetOffset_;
    SizeF childSize_;
    OffsetF childOffset_;
    OffsetF arrowPosition_;
    SizeF selfSize_;
    RectF touchRegion_;

    Edge padding_;
    Border border_;
    Placement arrowPlacement_ = Placement::BOTTOM;
    Placement placement_ = Placement::BOTTOM;
    Dimension targetSpace_;

    bool showBottomArrow_ = false;
    bool showTopArrow_ = false;
    bool showCustomArrow_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(BubbleLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BUBBLE_BUBBLE_LAYOUT_ALGORITHM_H