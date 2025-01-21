/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/swiper_indicator/circle_dot_indicator/circle_dot_indicator_layout_algorithm.h"

#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"

namespace OHOS::Ace::NG {
void CircleDotIndicatorLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto indicatorlayoutProperty = frameNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    CHECK_NULL_VOID(indicatorlayoutProperty);

    const auto& indicatorLayoutConstraint = indicatorlayoutProperty->GetLayoutConstraint();
    float swiperWidthIndicator = 0.0f;
    float swiperHeightIndicator = 0.0f;
    if (indicatorLayoutConstraint.has_value()) {
        swiperWidthIndicator = indicatorLayoutConstraint->parentIdealSize.Width().value_or(0.0f);
        swiperHeightIndicator = indicatorLayoutConstraint->parentIdealSize.Height().value_or(0.0f);
    }

    SizeF frameSize = { -1.0f, -1.0f };
    frameSize.SetSizeT(SizeF { swiperWidthIndicator, swiperHeightIndicator });
    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize);
}

void CircleDotIndicatorLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    OffsetF currentOffset = { 0.0, 0.0 };

    layoutWrapper->GetGeometryNode()->SetMarginFrameOffset(currentOffset);
}
} // namespace OHOS::Ace::NG
