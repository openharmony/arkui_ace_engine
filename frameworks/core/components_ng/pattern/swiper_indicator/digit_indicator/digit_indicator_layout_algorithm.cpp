/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/swiper_indicator/digit_indicator/digit_indicator_layout_algorithm.h"

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_paint_property.h"
namespace OHOS::Ace::NG {
namespace {
constexpr Dimension INDICATOR_PADDING = 8.0_vp;
} // namespace

void DigitIndicatorLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutPropertyConstraint = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutPropertyConstraint);
    auto layoutConstraint = layoutPropertyConstraint->CreateChildConstraint();
    auto indicatorWidth = INDICATOR_PADDING.ConvertToPx() * 2;
    auto indicatorHeight = 0.0f;
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Measure(layoutConstraint);
        auto textGeometryNode = child->GetGeometryNode();
        CHECK_NULL_VOID(textGeometryNode);
        auto textFrameSize = textGeometryNode->GetFrameSize();
        indicatorWidth += textFrameSize.Width();
        if (indicatorHeight < textFrameSize.Height()) {
            indicatorHeight = textFrameSize.Height();
        }
    }

    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(swiperIndicatorTheme);

    if (LessNotEqual(indicatorHeight, swiperIndicatorTheme->GetIndicatorDigitHeight().ConvertToPx())) {
        indicatorHeight = swiperIndicatorTheme->GetIndicatorDigitHeight().ConvertToPx();
    }

    SizeF frameSize = { indicatorWidth, indicatorHeight };
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    geometryNode->SetFrameSize(frameSize);
}

void DigitIndicatorLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);

    auto children = frameNode->GetChildren();
    if (children.empty()) {
        return;
    }
    auto textWrapperList = layoutWrapper->GetAllChildrenWithBuild();
    auto frontTextWrapper = textWrapperList.front();
    CHECK_NULL_VOID(frontTextWrapper);
    auto frontTextGeometryNode = frontTextWrapper->GetGeometryNode();
    CHECK_NULL_VOID(frontTextGeometryNode);
    auto layoutGeometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(layoutGeometryNode);
    auto frontCurrentOffset = OffsetF { INDICATOR_PADDING.ConvertToPx(),
        (layoutGeometryNode->GetMarginFrameSize().Height() - frontTextGeometryNode->GetMarginFrameSize().Height()) *
            0.5 };
    frontTextGeometryNode->SetMarginFrameOffset(frontCurrentOffset);
    frontTextWrapper->Layout();
    auto backTextWrapper = textWrapperList.back();
    CHECK_NULL_VOID(backTextWrapper);
    auto backTextGeometryNode = backTextWrapper->GetGeometryNode();
    CHECK_NULL_VOID(backTextGeometryNode);
    auto backTextCurrentOffset = OffsetF {
        layoutGeometryNode->GetMarginFrameSize().Width() - backTextGeometryNode->GetMarginFrameSize().Width() -
            INDICATOR_PADDING.ConvertToPx(),
        (layoutGeometryNode->GetMarginFrameSize().Height() - backTextGeometryNode->GetMarginFrameSize().Height()) * 0.5
    };
    backTextGeometryNode->SetMarginFrameOffset(backTextCurrentOffset);
    backTextWrapper->Layout();
}
} // namespace OHOS::Ace::NG
