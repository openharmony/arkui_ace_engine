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
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/render/paint_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float DIGIT_SIDE_DISTANCE = 8.0f;
constexpr float DIGIT_TOTAL_DISTANCE  = 16.0f;
constexpr float HALF = 0.5f;
} // namespace

void DigitIndicatorLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    CalculateTextContent(frameNode);
    auto layoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    indicatorWidth_ = DIGIT_TOTAL_DISTANCE;
    indicatorHeight_ = 0.0f;
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Measure(layoutConstraint);
        auto textGeometryNode = child->GetGeometryNode();
        CHECK_NULL_VOID(textGeometryNode);
        auto textFrameSize = textGeometryNode->GetFrameSize();
        indicatorWidth_ += textFrameSize.Width();
        if (indicatorHeight_ < textFrameSize.Height()) {
            indicatorHeight_ = textFrameSize.Height();
        }
    }

    auto layoutProperty = frameNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    const auto& frameNodeLayoutConstraint = layoutProperty->GetLayoutConstraint();
    const auto& minSize = frameNodeLayoutConstraint->minSize;
    const auto& maxSize = frameNodeLayoutConstraint->maxSize;
    SizeF frameSize = { -1.0f, -1.0f };
    do {
        frameSize.SetSizeT(SizeF { indicatorWidth_, indicatorHeight_ });
        if (frameSize.IsNonNegative()) {
            break;
        }
        frameSize.Constrain(minSize, maxSize);
    } while (false);

    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize);
}

void DigitIndicatorLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto swiperNode = DynamicCast<FrameNode>(frameNode->GetParent());
    CHECK_NULL_VOID(swiperNode);

    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto direction = swiperPattern->GetDirection();
    auto layoutProperty = frameNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    auto left = layoutProperty->GetLeft();
    auto right = layoutProperty->GetRight();
    auto top = layoutProperty->GetTop();
    auto bottom = layoutProperty->GetBottom();

    const auto& layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    auto swiperWidth = layoutConstraint->parentIdealSize.Width().value();
    auto swiperHeight = layoutConstraint->parentIdealSize.Height().value();

    Offset position;
    if (left.has_value()) {
        auto leftValue = GetValidEdgeLength(swiperWidth, indicatorWidth_, Dimension(left->Value()));
        position.SetX(leftValue);
    } else if (right.has_value()) {
        auto rightValue = GetValidEdgeLength(swiperWidth, indicatorWidth_, Dimension(right->Value()));
        position.SetX(swiperWidth - indicatorWidth_ - rightValue);
    } else {
        position.SetX(
            direction == Axis::HORIZONTAL ? (swiperWidth - indicatorWidth_) * HALF : swiperWidth - indicatorWidth_);
    }
    if (top.has_value()) {
        auto topValue = GetValidEdgeLength(swiperHeight, indicatorHeight_, Dimension(top->Value()));
        position.SetY(topValue);
    } else if (bottom.has_value()) {
        auto bottomValue = GetValidEdgeLength(swiperHeight, indicatorHeight_, Dimension(bottom->Value()));
        position.SetY(swiperHeight - indicatorHeight_ - bottomValue);
    } else {
        if (direction == Axis::HORIZONTAL) {
            position.SetY(swiperHeight - indicatorHeight_);
        } else {
            position.SetY((swiperHeight - indicatorHeight_) * HALF);
        }
    }
    auto layoutGeometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(layoutGeometryNode);
    auto currentOffset = OffsetF{ static_cast<float>(position.GetX()), static_cast<float>(position.GetY()) };
    CalculateTextFrameSize(frameNode, layoutWrapper);
    layoutGeometryNode->SetMarginFrameOffset(currentOffset);
}

double DigitIndicatorLayoutAlgorithm::GetValidEdgeLength(
    float swiperLength, float indicatorLength, const Dimension& edge)
{
    double edgeLength = edge.Unit() == DimensionUnit::PERCENT ? swiperLength * edge.Value() : edge.ConvertToPx();
    if (!NearZero(edgeLength) && edgeLength > swiperLength - indicatorLength) {
        edgeLength = swiperLength - indicatorLength;
    }
    if (edgeLength < 0.0) {
        edgeLength = 0.0;
    }
    return edgeLength;
}

void DigitIndicatorLayoutAlgorithm::CalculateTextContent(const RefPtr<FrameNode>& frameNode)
{
    auto swiperNode = DynamicCast<FrameNode>(frameNode->GetParent());
    CHECK_NULL_VOID(swiperNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SwiperIndicatorTheme>();
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto currentIndex = swiperPattern->GetCurrentIndex();
    auto itemCount = swiperPattern->TotalCount();
    auto lastFrameNode = AceType::DynamicCast<FrameNode>(swiperNode->GetLastChild());
    CHECK_NULL_VOID(lastFrameNode);
    auto firstTextFrameNode = AceType::DynamicCast<FrameNode>(lastFrameNode->GetFirstChild());
    CHECK_NULL_VOID(firstTextFrameNode);
    auto firstTextLayoutProperty = DynamicCast<TextLayoutProperty>(firstTextFrameNode->GetLayoutProperty());
    CHECK_NULL_VOID(firstTextLayoutProperty);
    auto layoutProperty = frameNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto selectedFontColor = layoutProperty->GetSelectedFontColorValue(
        theme->GetDigitalIndicatorTextStyle().GetTextColor());
    auto selectedFontSize = layoutProperty->GetSelectedFontSizeValue(
        theme->GetDigitalIndicatorTextStyle().GetFontSize());
    if (!selectedFontSize.IsValid()) {
        selectedFontSize = theme->GetDigitalIndicatorTextStyle().GetFontSize();
    }
    auto selectedFontWeight = layoutProperty->GetSelectedFontWeightValue(
        theme->GetDigitalIndicatorTextStyle().GetFontWeight());
    firstTextLayoutProperty->UpdateTextColor(selectedFontColor);
    firstTextLayoutProperty->UpdateFontSize(selectedFontSize);
    firstTextLayoutProperty->UpdateFontWeight(selectedFontWeight);
    currentIndex += 1;
    if (currentIndex > itemCount) {
        currentIndex = currentIndex % itemCount;
    }
    firstTextLayoutProperty->UpdateContent(std::to_string(currentIndex));

    auto lastTextFrameNode = AceType::DynamicCast<FrameNode>(lastFrameNode->GetLastChild());
    auto lastTextLayoutProperty = DynamicCast<TextLayoutProperty>(lastTextFrameNode->GetLayoutProperty());
    auto fontColor = layoutProperty->GetFontColorValue(theme->GetDigitalIndicatorTextStyle().GetTextColor());
    auto fontSize = layoutProperty->GetFontSizeValue(theme->GetDigitalIndicatorTextStyle().GetFontSize());
    if (!fontSize.IsValid()) {
        fontSize = theme->GetDigitalIndicatorTextStyle().GetFontSize();
    }
    auto fontWeight = layoutProperty->GetFontWeightValue(theme->GetDigitalIndicatorTextStyle().GetFontWeight());
    lastTextLayoutProperty->UpdateTextColor(fontColor);
    lastTextLayoutProperty->UpdateFontSize(fontSize);
    lastTextLayoutProperty->UpdateFontWeight(fontWeight);
    lastTextLayoutProperty->UpdateContent("/" + std::to_string(itemCount));

    firstTextFrameNode->MarkModifyDone();
    firstTextFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    lastTextFrameNode->MarkModifyDone();
    lastTextFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}
void DigitIndicatorLayoutAlgorithm::CalculateTextFrameSize(const RefPtr<FrameNode>& frameNode,
    LayoutWrapper* layoutWrapper)
{
    auto children = frameNode->GetChildren();
    if (children.empty()) {
        LOGW("text has no child node.");
        return;
    }
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        auto textGeometryNode = child->GetGeometryNode();
        CHECK_NULL_VOID(textGeometryNode);
    }
    auto textWrapperList = layoutWrapper->GetAllChildrenWithBuild();
    auto frontTextWrapper = textWrapperList.front();
    CHECK_NULL_VOID(frontTextWrapper);
    auto frontTextGeometryNode = frontTextWrapper->GetGeometryNode();
    CHECK_NULL_VOID(frontTextGeometryNode);
    auto layoutGeometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(layoutGeometryNode);
    auto frontCurrentOffset = OffsetF{ DIGIT_SIDE_DISTANCE, (layoutGeometryNode->GetMarginFrameSize().Height() -
        frontTextGeometryNode->GetMarginFrameSize().Height()) * HALF };
    frontTextGeometryNode->SetMarginFrameOffset(frontCurrentOffset);
    frontTextWrapper->Layout();

    auto backTextWrapper = textWrapperList.back();
    CHECK_NULL_VOID(backTextWrapper);
    auto backTextGeometryNode = backTextWrapper->GetGeometryNode();
    CHECK_NULL_VOID(backTextGeometryNode);
    auto backTextCurrentOffset = OffsetF{ layoutGeometryNode->GetMarginFrameSize().Width() -
        backTextGeometryNode->GetMarginFrameSize().Width() - DIGIT_SIDE_DISTANCE,
        (layoutGeometryNode->GetMarginFrameSize().Height() -
        backTextGeometryNode->GetMarginFrameSize().Height()) * HALF };
    backTextGeometryNode->SetMarginFrameOffset(backTextCurrentOffset);
    backTextWrapper->Layout();
}
} // namespace OHOS::Ace::NG
