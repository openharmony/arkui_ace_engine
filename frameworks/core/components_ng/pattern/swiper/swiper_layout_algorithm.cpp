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

#include "core/components_ng/pattern/swiper/swiper_layout_algorithm.h"

#include <algorithm>
#include <cstdint>

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/ace_trace.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_utils.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

namespace {
constexpr Dimension INDICATOR_PADDING = 8.0_vp;
constexpr uint32_t INDICATOR_HAS_CHILD = 2;
} // namespace

void SwiperLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(swiperLayoutProperty);
    auto childLayoutConstraint = swiperLayoutProperty->CreateChildConstraint();
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);

    MeasureOneself(layoutWrapper, childLayoutConstraint);
    // Measure child
    childLayoutConstraint.parentIdealSize = OptionalSizeF(geometryNode->GetFrameSize());
    MeasurePages(layoutWrapper, childLayoutConstraint);
    MeasureIndicator(layoutWrapper, childLayoutConstraint);
    MeasureArrow(layoutWrapper, childLayoutConstraint);
    layoutWrapper->SetCacheCount(swiperLayoutProperty->GetCachedCount().value_or(1));
}

float SwiperLayoutAlgorithm::GetPrevAndNextMarginMontage(
    const RefPtr<SwiperLayoutProperty>& property, float childCalcIdealLength)
{
    CHECK_NULL_RETURN(property, 0.0f);
    auto prevMargin = property->GetPrevMarginValue(0.0_px).ConvertToPx();
    auto nextMargin = property->GetNextMarginValue(0.0_px).ConvertToPx();
    if (GreatNotEqual(prevMargin, childCalcIdealLength) ||
        GreatNotEqual(nextMargin, childCalcIdealLength)) {
        property->UpdatePrevMargin(0.0_px);
        property->UpdateNextMargin(0.0_px);
        return 0.0f;
    }
    bool isStretch = property->GetDisplayCount().has_value() ||
                     property->GetDisplayMode().value_or(SwiperDisplayMode::STRETCH) == SwiperDisplayMode::STRETCH;
    auto itemSpace = static_cast<float>(property->GetItemSpace().value_or(0.0_px).ConvertToPx());
    auto prevMarginMontage = Positive(prevMargin) && isStretch ? prevMargin + itemSpace : 0.0f;
    auto nextMarginMontage = Positive(nextMargin) && isStretch ? nextMargin + itemSpace : 0.0f;
    return prevMarginMontage + nextMarginMontage;
}

void SwiperLayoutAlgorithm::MeasureOneself(LayoutWrapper* layoutWrapper, LayoutConstraintF childLayoutConstraint)
{
    if (onlyNeedMeasurePages_) {
        return;
    }
    CHECK_NULL_VOID(layoutWrapper);
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(swiperLayoutProperty);
    const auto& constraint = swiperLayoutProperty->GetLayoutConstraint();
    auto axis = swiperLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL);
    auto idealSize = CreateIdealSize(
        constraint.value(), axis, displayCount_ == 1 ? MeasureType::MATCH_PARENT : MeasureType::MATCH_CONTENT, true);
    auto padding = swiperLayoutProperty->CreatePaddingAndBorder();

    if (displayCount_ == 1 && (constraint == std::nullopt || constraint->selfIdealSize.Width() == std::nullopt ||
        constraint->selfIdealSize.Height() == std::nullopt)) {
        childLayoutConstraint.parentIdealSize = OptionalSizeF(idealSize);
        MeasureAllPagesToGetMaxChildSize(layoutWrapper, childLayoutConstraint);
        idealSize = maxChildSize_;
        float prevAndNextMarginMontage =
            GetPrevAndNextMarginMontage(swiperLayoutProperty, maxChildSize_.MainSize(axis));
        idealSize.SetMainSize(idealSize.MainSize(axis) + prevAndNextMarginMontage, axis);
        idealSize.AddPadding(padding.left, padding.right, padding.top, padding.bottom);
    }

    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    geometryNode->SetFrameSize(idealSize);

    auto itemSpace = static_cast<float>(swiperLayoutProperty->GetItemSpace().value_or(0.0_px).ConvertToPx());
    bool isStretch =
        swiperLayoutProperty->GetDisplayCount().has_value() ||
        swiperLayoutProperty->GetDisplayMode().value_or(SwiperDisplayMode::STRETCH) == SwiperDisplayMode::STRETCH;
    auto prevMargin = static_cast<float>(swiperLayoutProperty->GetPrevMarginValue(0.0_px).ConvertToPx());
    auto prevMarginMontage = Positive(prevMargin) && isStretch ? prevMargin + itemSpace : 0.0f;
    auto nextMargin = static_cast<float>(swiperLayoutProperty->GetNextMarginValue(0.0_px).ConvertToPx());
    auto nextMarginMontage = Positive(nextMargin) && isStretch ? nextMargin + itemSpace : 0.0f;
    // Calculate maxChildSize_
    maxChildSize_ = idealSize;
    maxChildSize_.MinusPadding(padding.left, padding.right, padding.top, padding.bottom);
    maxChildSize_.SetMainSize(maxChildSize_.MainSize(axis) - itemSpace * (displayCount_ - 1), axis);
    float prevAndNextMarginMontage = GetPrevAndNextMarginMontage(
        swiperLayoutProperty, (maxChildSize_.MainSize(axis) - prevMarginMontage - nextMarginMontage) / displayCount_);
    maxChildSize_.SetMainSize(maxChildSize_.MainSize(axis) - prevAndNextMarginMontage, axis);
    maxChildSize_.SetMainSize(maxChildSize_.MainSize(axis) / displayCount_, axis);
}

void SwiperLayoutAlgorithm::MeasureAllPagesToGetMaxChildSize(
    LayoutWrapper* layoutWrapper, LayoutConstraintF childLayoutConstraint)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(swiperLayoutProperty);
    int32_t cachedCount = swiperLayoutProperty->GetCachedCount().value_or(1);
    maxChildSize_ = { 0, 0 };

    int32_t beginIndex = static_cast<int32_t>(std::floor(currentOffsetTimes_)) - cachedCount;
    int32_t endIndex = static_cast<int32_t>(std::floor(currentOffsetTimes_)) + cachedCount;
    if (endIndex - beginIndex >= totalCount_) {
        beginIndex = 0;
        endIndex = totalCount_ - 1;
    }
    for (int32_t index = beginIndex; index <= endIndex; ++index) {
        auto pagesWrapper = layoutWrapper->GetOrCreateChildByIndex((index + totalCount_) % totalCount_);
        if (!pagesWrapper) {
            continue;
        }
        pagesWrapper->Measure(childLayoutConstraint);
        itemRange_.insert((index + totalCount_) % totalCount_);
        auto childGeometryNode = pagesWrapper->GetGeometryNode();
        if (!childGeometryNode) {
            continue;
        }
        auto childFrameSize = childGeometryNode->GetFrameSize();
        maxChildSize_.SetWidth(std::max(maxChildSize_.Width(), childFrameSize.Width()));
        maxChildSize_.SetHeight(std::max(maxChildSize_.Height(), childFrameSize.Height()));
    }
}

void SwiperLayoutAlgorithm::CalculatePrevCountAndNextCount(const RefPtr<SwiperLayoutProperty>& property)
{
    auto axis = property->GetDirection().value_or(Axis::HORIZONTAL);
    GetPrevAndNextMarginMontage(property, maxChildSize_.MainSize(axis));
    bool isStretch =
        property->GetDisplayCount().has_value() ||
        property->GetDisplayMode().value_or(SwiperDisplayMode::STRETCH) == SwiperDisplayMode::STRETCH;
    auto prevMargin = static_cast<float>(property->GetPrevMarginValue(0.0_px).ConvertToPx());
    auto nextMargin = static_cast<float>(property->GetNextMarginValue(0.0_px).ConvertToPx());
    prevCount_ = Positive(prevMargin) && isStretch ? 1 : 0;
    nextCount_ = Positive(nextMargin) && isStretch ? 1 : 0;
}

void SwiperLayoutAlgorithm::MeasurePages(LayoutWrapper* layoutWrapper, LayoutConstraintF childLayoutConstraint)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(swiperLayoutProperty);
    auto axis = swiperLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL);
    childLayoutConstraint.maxSize = maxChildSize_;
    if (swiperLayoutProperty->GetDisplayCount().has_value() ||
        swiperLayoutProperty->GetDisplayMode().value_or(SwiperDisplayMode::STRETCH) == SwiperDisplayMode::STRETCH) {
        childLayoutConstraint.selfIdealSize.SetMainSize(maxChildSize_.MainSize(axis), axis);
    }

    CalculatePrevCountAndNextCount(swiperLayoutProperty);

    for (int32_t index = std::floor(currentOffsetTimes_) - prevCount_;
         static_cast<float>(index) < (currentOffsetTimes_ + displayCount_ + nextCount_); ++index) {
        auto pagesWrapper = layoutWrapper->GetOrCreateChildByIndex((index + totalCount_) % totalCount_);
        if (pagesWrapper) {
            itemRange_.insert((index + totalCount_) % totalCount_);
            pagesWrapper->Measure(childLayoutConstraint);
        }
    }
}

void SwiperLayoutAlgorithm::MeasureIndicator(LayoutWrapper* layoutWrapper, LayoutConstraintF childLayoutConstraint)
{
    if (onlyNeedMeasurePages_) {
        return;
    }
    CHECK_NULL_VOID(layoutWrapper);
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(swiperLayoutProperty);
    if (!swiperLayoutProperty->GetShowIndicator().value_or(true)) {
        return;
    }
    auto hostNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(hostNode);
    auto swiperPattern = hostNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto indicatorWrapper = GetNodeLayoutWrapperByTag(layoutWrapper, V2::SWIPER_INDICATOR_ETS_TAG);
    CHECK_NULL_VOID(indicatorWrapper);
    indicatorWrapper->Measure(childLayoutConstraint);
}

void SwiperLayoutAlgorithm::MeasureArrow(LayoutWrapper* layoutWrapper, LayoutConstraintF childLayoutConstraint) const
{
    if (onlyNeedMeasurePages_) {
        return;
    }
    CHECK_NULL_VOID(layoutWrapper);
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(swiperLayoutProperty);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID_NOLOG(pipelineContext);
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID_NOLOG(swiperIndicatorTheme);

    if (!swiperLayoutProperty->GetDisplayArrow().value_or(false)) {
        return;
    }
    auto hostNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(hostNode);
    auto swiperPattern = hostNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    if (!swiperPattern->HasLeftButtonNode() || !swiperPattern->HasRightButtonNode()) {
        return;
    }
    auto leftArrowWrapper = GetNodeLayoutWrapperByTag(layoutWrapper, V2::SWIPER_LEFT_ARROW_ETS_TAG);
    CHECK_NULL_VOID(leftArrowWrapper);
    auto rightArrowWrapper = GetNodeLayoutWrapperByTag(layoutWrapper, V2::SWIPER_RIGHT_ARROW_ETS_TAG);
    CHECK_NULL_VOID(rightArrowWrapper);
    if (leftArrowWrapper->GetHostTag() != V2::SWIPER_LEFT_ARROW_ETS_TAG ||
        rightArrowWrapper->GetHostTag() != V2::SWIPER_RIGHT_ARROW_ETS_TAG) {
        return;
    }
    auto leftArrowGeometryNode = leftArrowWrapper->GetGeometryNode();
    CHECK_NULL_VOID(leftArrowGeometryNode);
    auto rightArrowGeometryNode = rightArrowWrapper->GetGeometryNode();
    CHECK_NULL_VOID(rightArrowGeometryNode);

    SizeF arrowFrameSize = {
        static_cast<float>(
            swiperLayoutProperty->GetBoardSizeValue(swiperIndicatorTheme->GetBigArrowBoardSize()).ConvertToPx()),
        static_cast<float>(
            swiperLayoutProperty->GetBoardSizeValue(swiperIndicatorTheme->GetBigArrowBoardSize()).ConvertToPx()) };
    leftArrowGeometryNode->SetFrameSize(arrowFrameSize);
    leftArrowWrapper->Measure(childLayoutConstraint);
    rightArrowGeometryNode->SetFrameSize(arrowFrameSize);
    rightArrowWrapper->Measure(childLayoutConstraint);
}

void SwiperLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(swiperLayoutProperty);
    auto itemSpace = static_cast<float>(swiperLayoutProperty->GetItemSpace().value_or(0.0_px).ConvertToPx());
    auto axis = swiperLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL);
    float unitSize = maxChildSize_.MainSize(axis) + itemSpace;
    auto padding = swiperLayoutProperty->CreatePaddingAndBorder();
    bool isStretch =
        swiperLayoutProperty->GetDisplayCount().has_value() ||
        swiperLayoutProperty->GetDisplayMode().value_or(SwiperDisplayMode::STRETCH) == SwiperDisplayMode::STRETCH;
    auto prevMargin = static_cast<float>(swiperLayoutProperty->GetPrevMarginValue(0.0_px).ConvertToPx());
    auto prevMarginMontage = Positive(prevMargin) && isStretch ? prevMargin + itemSpace : 0.0f;
    OffsetF contentOffset = { padding.left.value_or(0.0f), padding.top.value_or(0.0f) };
    contentOffset += axis == Axis::HORIZONTAL ? OffsetF(prevMarginMontage, 0.0f) : OffsetF(0.0f, prevMarginMontage);

    CalculatePrevCountAndNextCount(swiperLayoutProperty);
    for (int32_t index = std::floor(currentOffsetTimes_) - prevCount_;
         static_cast<float>(index) < (currentOffsetTimes_ + displayCount_ - nextCount_); ++index) {
        layoutWrapper->GetOrCreateChildByIndex((index + totalCount_) % totalCount_);
    }
    auto iterItemRange = itemRange_.begin();
    while (iterItemRange != itemRange_.end()) {
        int32_t index = *iterItemRange;
        auto pagesWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        if (!pagesWrapper) {
            iterItemRange = itemRange_.erase(iterItemRange);
            continue;
        }
        if (!IsVisiblePages(index)) {
            layoutWrapper->RemoveChildInRenderTree(index);
            iterItemRange = itemRange_.erase(iterItemRange);
            continue;
        }
        // Layout Pages
        OffsetF pagesOffset =
            contentOffset + (axis == Axis::HORIZONTAL ? OffsetF(GetPagesOffsetTimes(index) * unitSize, 0)
                                                      : OffsetF(0, GetPagesOffsetTimes(index) * unitSize));
        pagesWrapper->GetGeometryNode()->SetMarginFrameOffset(pagesOffset);
        pagesWrapper->Layout();
        ++iterItemRange;
    }

    // Layout swiper indicator
    if (swiperLayoutProperty->GetShowIndicatorValue(true)) {
        auto hostNode = layoutWrapper->GetHostNode();
        CHECK_NULL_VOID(hostNode);
        auto swiperPattern = hostNode->GetPattern<SwiperPattern>();
        CHECK_NULL_VOID(swiperPattern);
        auto indicatorWrapper = GetNodeLayoutWrapperByTag(layoutWrapper, V2::SWIPER_INDICATOR_ETS_TAG);
        if (indicatorWrapper) {
            if (swiperLayoutProperty->GetIndicatorTypeValue(SwiperIndicatorType::DOT) == SwiperIndicatorType::DIGIT) {
                PlaceDigitChild(indicatorWrapper, swiperLayoutProperty);
            }
            indicatorWrapper->Layout();
        }
    }

    // Layout swiper arrow
    if (swiperLayoutProperty->GetDisplayArrowValue(false)) {
        auto hostNode = layoutWrapper->GetHostNode();
        CHECK_NULL_VOID(hostNode);
        auto swiperPattern = hostNode->GetPattern<SwiperPattern>();
        CHECK_NULL_VOID(swiperPattern);

        if (swiperPattern->HasLeftButtonNode() && swiperPattern->HasRightButtonNode()) {
            auto leftArrowWrapper = GetNodeLayoutWrapperByTag(layoutWrapper, V2::SWIPER_LEFT_ARROW_ETS_TAG);
            auto rightArrowWrapper = GetNodeLayoutWrapperByTag(layoutWrapper, V2::SWIPER_RIGHT_ARROW_ETS_TAG);
            CHECK_NULL_VOID(leftArrowWrapper);
            CHECK_NULL_VOID(rightArrowWrapper);
            if (leftArrowWrapper->GetHostTag() == V2::SWIPER_LEFT_ARROW_ETS_TAG &&
                rightArrowWrapper->GetHostTag() == V2::SWIPER_RIGHT_ARROW_ETS_TAG) {
                ArrowLayout(layoutWrapper, leftArrowWrapper);
                ArrowLayout(layoutWrapper, rightArrowWrapper);
            }
        }
    }
}

float SwiperLayoutAlgorithm::GetPagesOffsetTimes(int32_t index) const
{
    float pagesOffsetTimes = index - currentOffsetTimes_;
    if (isLoop_) {
        float frontPagesOffsetTimes = pagesOffsetTimes - totalCount_;
        float backPagesOffsetTimes = pagesOffsetTimes + totalCount_;
        float middleSwiperOffsetTimes = static_cast<float>(displayCount_ - 1) / 2;
        pagesOffsetTimes = std::fabs(pagesOffsetTimes - middleSwiperOffsetTimes) <
                                   std::fabs(frontPagesOffsetTimes - middleSwiperOffsetTimes)
                               ? pagesOffsetTimes
                               : frontPagesOffsetTimes;
        pagesOffsetTimes = std::fabs(pagesOffsetTimes - middleSwiperOffsetTimes) <
                                   std::fabs(backPagesOffsetTimes - middleSwiperOffsetTimes)
                               ? pagesOffsetTimes
                               : backPagesOffsetTimes;
    }
    return pagesOffsetTimes;
}

bool SwiperLayoutAlgorithm::IsVisiblePages(int32_t index) const
{
    float pagesOffsetTimes = GetPagesOffsetTimes(index);
    float minPagesOffsetTimes = static_cast<float>(-1 - prevCount_);
    float maxPagesOffsetTimes = static_cast<float>(displayCount_ + nextCount_);
    return minPagesOffsetTimes < pagesOffsetTimes && pagesOffsetTimes < maxPagesOffsetTimes;
}

void SwiperLayoutAlgorithm::PlaceDigitChild(
    const RefPtr<LayoutWrapper>& indicatorWrapper, const RefPtr<LayoutProperty>& layoutProperty)
{
    if (indicatorWrapper->GetTotalChildCount() != INDICATOR_HAS_CHILD) {
        return;
    }
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(layoutProperty);
    CHECK_NULL_VOID(swiperLayoutProperty);
    auto indicatorGeometryNode = indicatorWrapper->GetGeometryNode();
    CHECK_NULL_VOID(indicatorGeometryNode);
    auto indicatorWidth = INDICATOR_PADDING.ConvertToPx() * 2.0;
    auto indicatorHeight = 0.0f;
    for (auto&& child : indicatorWrapper->GetAllChildrenWithBuild()) {
        auto textGeometryNode = child->GetGeometryNode();
        CHECK_NULL_VOID(textGeometryNode);
        auto textFrameSize = textGeometryNode->GetFrameSize();
        indicatorWidth += textFrameSize.Width();
        if (indicatorHeight < textFrameSize.Height()) {
            indicatorHeight = textFrameSize.Height();
        }
    }
    auto layoutPropertyConstraint = indicatorWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutPropertyConstraint);
    const auto& layoutConstraint = layoutPropertyConstraint->GetLayoutConstraint();
    auto swiperWidth = layoutConstraint->parentIdealSize.Width().value();
    auto swiperHeight = layoutConstraint->parentIdealSize.Height().value();
    const auto& swiperPaddingProperty = swiperLayoutProperty->GetPaddingProperty();
    float swiperPaddingLeft = 0.0f;
    float swiperPaddingRight = 0.0f;
    float swiperPaddingTop = 0.0f;
    float swiperPaddingBottom = 0.0f;
    if (swiperPaddingProperty != nullptr) {
        swiperPaddingLeft =
            static_cast<float>(swiperPaddingProperty->left.value_or(CalcLength(0.0_vp)).GetDimension().ConvertToPx());
        swiperPaddingRight =
            static_cast<float>(swiperPaddingProperty->right.value_or(CalcLength(0.0_vp)).GetDimension().ConvertToPx());
        swiperPaddingTop =
            static_cast<float>(swiperPaddingProperty->top.value_or(CalcLength(0.0_vp)).GetDimension().ConvertToPx());
        swiperPaddingBottom =
            static_cast<float>(swiperPaddingProperty->bottom.value_or(CalcLength(0.0_vp)).GetDimension().ConvertToPx());
    }
    auto left = swiperLayoutProperty->GetLeft();
    auto right = swiperLayoutProperty->GetRight();
    auto top = swiperLayoutProperty->GetTop();
    auto bottom = swiperLayoutProperty->GetBottom();
    auto axis = swiperLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL);
    Offset position;
    Dimension indicatorPositionDefault = 0.0_vp;
    if (left.has_value() && !NearEqual(left->ConvertToPx(), indicatorPositionDefault.ConvertToPx())) {
        auto leftValue = GetValidEdgeLength(swiperWidth, indicatorWidth, Dimension(left->Value()));
        position.SetX(leftValue + swiperPaddingLeft);
    } else if (right.has_value() && !NearEqual(right->ConvertToPx(), indicatorPositionDefault.ConvertToPx())) {
        auto rightValue = GetValidEdgeLength(swiperWidth, indicatorWidth, Dimension(right->Value()));
        position.SetX(swiperWidth - indicatorWidth - rightValue - swiperPaddingRight);
    } else {
        position.SetX(axis == Axis::HORIZONTAL
                          ? (swiperWidth - swiperPaddingRight + swiperPaddingLeft - indicatorWidth) * 0.5
                          : swiperWidth - indicatorWidth - swiperPaddingRight);
    }
    if (top.has_value() && !NearEqual(top->ConvertToPx(), indicatorPositionDefault.ConvertToPx())) {
        auto topValue = GetValidEdgeLength(swiperHeight, indicatorHeight, Dimension(top->Value()));
        position.SetY(topValue + swiperPaddingTop);
    } else if (bottom.has_value() && !NearEqual(bottom->ConvertToPx(), indicatorPositionDefault.ConvertToPx())) {
        auto bottomValue = GetValidEdgeLength(swiperHeight, indicatorHeight, Dimension(bottom->Value()));
        position.SetY(swiperHeight - indicatorHeight - bottomValue - swiperPaddingBottom);
    } else {
        if (axis == Axis::HORIZONTAL) {
            position.SetY(swiperHeight - indicatorHeight - swiperPaddingBottom);
        } else {
            position.SetY((swiperHeight - swiperPaddingBottom + swiperPaddingTop - indicatorHeight) * 0.5);
        }
    }
    auto currentOffset = OffsetF { static_cast<float>(position.GetX()), static_cast<float>(position.GetY()) };
    indicatorGeometryNode->SetMarginFrameOffset(currentOffset);
}

double SwiperLayoutAlgorithm::GetValidEdgeLength(float swiperLength, float indicatorLength, const Dimension& edge)
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

RefPtr<LayoutWrapper> SwiperLayoutAlgorithm::GetNodeLayoutWrapperByTag(
    LayoutWrapper* layoutWrapper, const std::string& tagName) const
{
    CHECK_NULL_RETURN(layoutWrapper, nullptr);
    auto hostNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(hostNode, nullptr);
    auto swiperPattern = hostNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, nullptr);
    auto indicatorIndex = -1;
    auto leftArrowIndex = -1;
    auto rightArrowIndex = -1;

    if (swiperPattern->HasIndicatorNode() && swiperPattern->HasLeftButtonNode() &&
        swiperPattern->HasRightButtonNode()) {
        indicatorIndex = totalCount_;
        leftArrowIndex = indicatorIndex + 1;
        rightArrowIndex = leftArrowIndex + 1;
    }
    if (swiperPattern->HasIndicatorNode() && !swiperPattern->HasLeftButtonNode() &&
        !swiperPattern->HasRightButtonNode()) {
        indicatorIndex = totalCount_;
    }
    if (!swiperPattern->HasIndicatorNode() && swiperPattern->HasLeftButtonNode() &&
        swiperPattern->HasRightButtonNode()) {
        leftArrowIndex = totalCount_;
        rightArrowIndex = leftArrowIndex + 1;
    }

    RefPtr<LayoutWrapper> nodeWrapper = nullptr;
    if (tagName == V2::SWIPER_INDICATOR_ETS_TAG) {
        nodeWrapper = layoutWrapper->GetOrCreateChildByIndex(indicatorIndex);
        CHECK_NULL_RETURN(nodeWrapper, nullptr);
    }
    if (tagName == V2::SWIPER_LEFT_ARROW_ETS_TAG) {
        nodeWrapper = layoutWrapper->GetOrCreateChildByIndex(leftArrowIndex);
        CHECK_NULL_RETURN(nodeWrapper, nullptr);
    }
    if (tagName == V2::SWIPER_RIGHT_ARROW_ETS_TAG) {
        nodeWrapper = layoutWrapper->GetOrCreateChildByIndex(rightArrowIndex);
        CHECK_NULL_RETURN(nodeWrapper, nullptr);
    }
    return nodeWrapper;
}

void SwiperLayoutAlgorithm::ArrowLayout(LayoutWrapper* layoutWrapper, const RefPtr<LayoutWrapper>& arrowWrapper) const
{
    CHECK_NULL_VOID(layoutWrapper);
    CHECK_NULL_VOID(arrowWrapper);
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(swiperLayoutProperty);
    auto axis = swiperLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL);
    auto arrowGeometryNode = arrowWrapper->GetGeometryNode();
    CHECK_NULL_VOID(arrowGeometryNode);
    auto arrowFrameSize = arrowGeometryNode->GetFrameSize();
    auto layoutGeometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(layoutGeometryNode);
    auto swiperFrameSize = layoutGeometryNode->GetFrameSize();
    auto isShowIndicatorArrow =
        (!swiperLayoutProperty->GetIsSiderMiddleValue(false) && swiperLayoutProperty->GetShowIndicatorValue(true));
    SizeF indicatorFrameSize;
    RectF indicatorFrameRect;
    if (isShowIndicatorArrow) {
        auto hostNode = layoutWrapper->GetHostNode();
        CHECK_NULL_VOID(hostNode);
        auto swiperPattern = hostNode->GetPattern<SwiperPattern>();
        CHECK_NULL_VOID(swiperPattern);
        auto indicatorWrapper = GetNodeLayoutWrapperByTag(layoutWrapper, V2::SWIPER_INDICATOR_ETS_TAG);
        CHECK_NULL_VOID(indicatorWrapper);
        auto indicatorGeometry = indicatorWrapper->GetGeometryNode();
        CHECK_NULL_VOID(indicatorGeometry);
        indicatorFrameSize = indicatorGeometry->GetFrameSize();
        indicatorFrameRect = indicatorGeometry->GetFrameRect();
    }
    auto isLeftArrow = arrowWrapper->GetHostTag() == V2::SWIPER_LEFT_ARROW_ETS_TAG;
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(swiperIndicatorTheme);
    OffsetF arrowOffset(0.0f, 0.0f);
    float startPoint = 0.0f;
    if (axis == Axis::HORIZONTAL && isShowIndicatorArrow) {
        startPoint =
            isLeftArrow
                ? (indicatorFrameRect.Left() - arrowFrameSize.Width() -
                      swiperIndicatorTheme->GetArrowScale().ConvertToPx() * hoverRatio_)
                : (indicatorFrameRect.Right() + swiperIndicatorTheme->GetArrowScale().ConvertToPx() * hoverRatio_);
        arrowOffset.SetX(startPoint);
        if (isLeftArrow && !NonNegative(arrowOffset.GetX())) {
            arrowOffset.SetX(0.0f);
        }
        if (GreatOrEqual(arrowOffset.GetX() + arrowFrameSize.Width(), swiperFrameSize.Width())) {
            arrowOffset.SetX(swiperFrameSize.Width() - arrowFrameSize.Width());
        }
        arrowOffset.SetY(indicatorFrameRect.Top() + (indicatorFrameSize.Height() - arrowFrameSize.Height()) * 0.5f);
        if (GreatOrEqual(arrowOffset.GetY() + arrowFrameSize.Height(), swiperFrameSize.Height())) {
            arrowOffset.SetY(swiperFrameSize.Height() - arrowFrameSize.Height());
        }
    } else if (axis == Axis::HORIZONTAL && !isShowIndicatorArrow) {
        startPoint = isLeftArrow ? swiperIndicatorTheme->GetArrowHorizontalMargin().ConvertToPx()
                                 : (swiperFrameSize.Width() - arrowFrameSize.Width() -
                                       swiperIndicatorTheme->GetArrowHorizontalMargin().ConvertToPx());
        arrowOffset.SetX(startPoint);
        arrowOffset.SetY((swiperFrameSize.Height() - arrowFrameSize.Height()) * 0.5f);

    } else if (axis != Axis::HORIZONTAL && isShowIndicatorArrow) {
        startPoint =
            isLeftArrow
                ? (indicatorFrameRect.Top() - arrowFrameSize.Height() -
                      swiperIndicatorTheme->GetArrowScale().ConvertToPx() * hoverRatio_)
                : (indicatorFrameRect.Bottom() + swiperIndicatorTheme->GetArrowScale().ConvertToPx() * hoverRatio_);
        arrowOffset.SetX(indicatorFrameRect.Left() + (indicatorFrameSize.Width() - arrowFrameSize.Width()) * 0.5f);
        arrowOffset.SetY(startPoint);
        if (isLeftArrow && !NonNegative(arrowOffset.GetY())) {
            arrowOffset.SetY(0.0f);
        }
        if (GreatOrEqual(arrowOffset.GetY() + arrowFrameSize.Height(), swiperFrameSize.Height())) {
            arrowOffset.SetY(swiperFrameSize.Height() - arrowFrameSize.Height());
        }
    } else {
        startPoint = isLeftArrow ? swiperIndicatorTheme->GetArrowVerticalMargin().ConvertToPx()
                                 : (swiperFrameSize.Height() - arrowFrameSize.Width() -
                                       swiperIndicatorTheme->GetArrowVerticalMargin().ConvertToPx());
        arrowOffset.SetX((swiperFrameSize.Width() - arrowFrameSize.Width()) * 0.5f);
        arrowOffset.SetY(startPoint);
    }
    arrowGeometryNode->SetMarginFrameOffset(arrowOffset);
    arrowWrapper->Layout();
}
} // namespace OHOS::Ace::NG
