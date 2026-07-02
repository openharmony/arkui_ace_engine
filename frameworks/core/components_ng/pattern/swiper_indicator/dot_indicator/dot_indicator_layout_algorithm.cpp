/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_layout_algorithm.h"

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_paint_property.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float SMALLEST_POINT_RATIO = 1.0f / 3.0f;
constexpr float SECOND_SMALLEST_POINT_RATIO = 2.0f / 3.0f;
constexpr int32_t OVERLONG_SMALL_COUNT = 2;
constexpr float HALF_FLOAT = 0.5f;
} // namespace
SizeF DotIndicatorLayoutAlgorithm::CalcIndicatorFrameSize(
    LayoutWrapper* layoutWrapper, float indicatorWidth, float indicatorHeight)
{
    SizeF frameSize = { -1.0f, -1.0f };
    CHECK_NULL_RETURN(layoutWrapper, frameSize);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, frameSize);
    const auto& layoutConstraint = layoutProperty->GetLayoutConstraint();
    CHECK_NULL_RETURN(layoutConstraint, frameSize);

    const auto& calcLayoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    if (isSingle_ && calcLayoutConstraint && calcLayoutConstraint->selfIdealSize) {
        auto idealSize =
            CreateIdealSize(layoutConstraint.value(), Axis::HORIZONTAL, layoutProperty->GetMeasureType(), true);
        auto width = calcLayoutConstraint->selfIdealSize->Width();
        auto height = calcLayoutConstraint->selfIdealSize->Height();
        if (width) {
            indicatorWidth_ = std::max(indicatorWidth_, idealSize.Width());
        }

        if (height) {
            indicatorHeight_ = std::max(indicatorHeight_, idealSize.Height());
        }
    }

    do {
        frameSize.SetSizeT(SizeF { indicatorWidth_, indicatorHeight_ });
        if (frameSize.IsNonNegative()) {
            break;
        }
        frameSize.Constrain(layoutConstraint->minSize, layoutConstraint->maxSize);
    } while (false);

    return frameSize;
}

void DotIndicatorLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    const auto& layoutConstraint = layoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint);
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto indicatorPattern = frameNode->GetPattern<SwiperIndicatorPattern>();
    CHECK_NULL_VOID(indicatorPattern);
    auto direction = indicatorPattern->GetDirection();
    auto paintProperty = frameNode->GetPaintProperty<DotIndicatorPaintProperty>();
    CHECK_NULL_VOID(paintProperty);

    auto theme = frameNode->GetTheme<SwiperIndicatorTheme>(true);
    CHECK_NULL_VOID(theme);

    // Diameter of a single indicator circle, item or selected-item width and height
    auto userItemWidth = paintProperty->GetItemWidthValue(theme->GetSize()).ConvertToPx();
    auto userItemHeight = paintProperty->GetItemHeightValue(theme->GetSize()).ConvertToPx();
    auto userSelectedItemWidth = paintProperty->GetSelectedItemWidthValue(theme->GetSize()).ConvertToPx();
    auto userSelectedItemHeight = paintProperty->GetSelectedItemHeightValue(theme->GetSize()).ConvertToPx();
    if (LessNotEqual(userItemWidth, 0.0) || LessNotEqual(userItemHeight, 0.0) ||
        LessNotEqual(userSelectedItemWidth, 0.0) || LessNotEqual(userSelectedItemHeight, 0.0)) {
        userItemWidth = theme->GetSize().ConvertToPx();
        userItemHeight = theme->GetSize().ConvertToPx();
        userSelectedItemWidth = theme->GetSize().ConvertToPx();
        userSelectedItemHeight = theme->GetSize().ConvertToPx();
    }

    // To the size of the hover after the layout, in order to prevent the components after the hover draw boundaries
    float indicatorScale = theme->GetIndicatorScale();
    if (maxDisplayCount_ > 0 || (!indicatorInteractive_ && isBindIndicator_)) {
        indicatorScale = 1.0f;
    }
    userItemWidth *= indicatorScale;
    userItemHeight *= indicatorScale;
    userSelectedItemWidth *= indicatorScale;
    userSelectedItemHeight *= indicatorScale;

    // The width and height of the entire indicator.
    Dimension indicatorHeightPadding = theme->GetIndicatorBgHeight();
    auto indicatorHeight =
        static_cast<float>(((userItemHeight > userSelectedItemHeight) ?
            userItemHeight : userSelectedItemHeight) + indicatorHeightPadding.ConvertToPx() * 2);
    auto noPaddingIndicatorHeight = indicatorHeight - indicatorHeightPadding.ConvertToPx();
    auto allPointDiameterSum = userItemWidth * (indicatorDisplayCount_ + 1);
    if (paintProperty->GetIsCustomSizeValue(false)) {
        allPointDiameterSum = userItemWidth * (indicatorDisplayCount_ - 1) + userSelectedItemWidth;
    }
    
    auto indicatorDotItemSpace = paintProperty->GetSpaceValue(theme->GetIndicatorDotItemSpace());
    auto allPointSpaceSum = static_cast<float>(indicatorDotItemSpace.ConvertToPx()) * (indicatorDisplayCount_ - 1);
    if (maxDisplayCount_ > 0) {
        allPointSpaceSum = static_cast<float>(indicatorDotItemSpace.ConvertToPx()) * (maxDisplayCount_ - 1);
        allPointDiameterSum = userItemWidth * (maxDisplayCount_ - OVERLONG_SMALL_COUNT - 1) + userSelectedItemWidth +
                              userItemWidth * SECOND_SMALLEST_POINT_RATIO + userItemWidth * SMALLEST_POINT_RATIO;
    }
    auto paddingSide = theme->GetIndicatorPaddingDot().ConvertToPx();
    
    auto indicatorWidth = paddingSide + allPointDiameterSum + allPointSpaceSum + paddingSide;
    auto noPaddingIndicatorWidth = indicatorWidth - paddingSide * 1.5;
    auto ignoreSize = paintProperty->GetIgnoreSizeValue(false);
    if (direction == Axis::HORIZONTAL) {
        indicatorWidth_ = indicatorWidth;
        indicatorHeight_ = indicatorHeight;
        ignorSizeIndicatorWidth_ = indicatorWidth;
        ignorSizeIndicatorHeight_ = ignoreSize ? noPaddingIndicatorHeight : indicatorHeight;
    } else {
        indicatorWidth_ = indicatorHeight;
        indicatorHeight_ = indicatorWidth;
        ignorSizeIndicatorWidth_ = indicatorHeight;
        ignorSizeIndicatorHeight_ = ignoreSize ? noPaddingIndicatorWidth : indicatorWidth;
    }

    auto frameSize = CalcIndicatorFrameSize(layoutWrapper, indicatorWidth, indicatorHeight);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    geometryNode->SetFrameSize(frameSize);
    if (!indicatorPattern->NeedCustomDotIndicatorLayout()) {
        return;
    }
    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    childLayoutConstraint.maxSize = frameSize;
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        CHECK_NULL_VOID(child);
        child->Measure(childLayoutConstraint);
    }
}

void DotIndicatorLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto indicatorPattern = frameNode->GetPattern<SwiperIndicatorPattern>();
    CHECK_NULL_VOID(indicatorPattern);
    OffsetF currentOffset = OffsetF(0.0f, 0.0f);
    bool needCustomIconLayout = indicatorPattern->NeedCustomDotIndicatorLayout();
    auto offsetWidth = needCustomIconLayout ? indicatorWidth_ : ignorSizeIndicatorWidth_;
    auto offsetHeight = needCustomIconLayout ? indicatorHeight_ : ignorSizeIndicatorHeight_;
    auto needSet = indicatorPattern->GetDotCurrentOffset(currentOffset, offsetWidth, offsetHeight);
    if (needSet) {
        auto geometryNode = layoutWrapper->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        geometryNode->SetMarginFrameOffset(currentOffset);
    }

    if (!needCustomIconLayout) {
        return;
    }

    CustomIconLayoutContext context;
    if (!InitCustomIconLayoutContext(layoutWrapper, indicatorPattern, context)) {
        return;
    }
    LayoutCustomIconChildren(layoutWrapper, context);
}

bool DotIndicatorLayoutAlgorithm::InitCustomIconLayoutContext(
    LayoutWrapper* layoutWrapper, const RefPtr<SwiperIndicatorPattern>& indicatorPattern,
    CustomIconLayoutContext& context) const
{
    CHECK_NULL_RETURN(layoutWrapper, false);
    CHECK_NULL_RETURN(indicatorPattern, false);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);

    context.direction = indicatorPattern->GetDirection();
    context.frameSize = geometryNode->GetFrameSize();
    context.crossSize = context.direction == Axis::HORIZONTAL
        ? context.frameSize.Height() : context.frameSize.Width();
    context.pointCenters = indicatorPattern->GetCustomIconCenterX();
    const auto& activeInfos = indicatorPattern->GetActiveCustomIconInfos();
    context.items.reserve(activeInfos.size());
    for (const auto& info : activeInfos) {
        context.items.push_back({ info.wrapperId, info.slotIndex });
    }
    return true;
}

void DotIndicatorLayoutAlgorithm::LayoutCustomIconChildren(
    LayoutWrapper* layoutWrapper, const CustomIconLayoutContext& context) const
{
    CHECK_NULL_VOID(layoutWrapper);
    auto children = layoutWrapper->GetAllChildrenWithBuild();
    std::unordered_map<int32_t, RefPtr<LayoutWrapper>> childWrapperById;
    childWrapperById.reserve(children.size());
    for (const auto& child : children) {
        CHECK_NULL_VOID(child);
        auto hostNode = child->GetHostNode();
        CHECK_NULL_VOID(hostNode);
        childWrapperById[hostNode->GetId()] = child;
    }
    for (const auto& item : context.items) {
        if (item.slotIndex < 0 || static_cast<size_t>(item.slotIndex) >= context.pointCenters.size()) {
            continue;
        }
        auto childIter = childWrapperById.find(item.wrapperId);
        if (childIter == childWrapperById.end()) {
            continue;
        }
        auto child = childIter->second;
        if (!child) {
            continue;
        }
        auto childGeometry = child->GetGeometryNode();
        CHECK_NULL_VOID(childGeometry);
        auto childSize = childGeometry->GetMarginFrameSize();
        float pointCenter = context.pointCenters[item.slotIndex];
        OffsetF childOffset;
        if (context.direction == Axis::HORIZONTAL) {
            childOffset = OffsetF(pointCenter - childSize.Width() * HALF_FLOAT,
                (context.crossSize - childSize.Height()) * HALF_FLOAT);
        } else {
            childOffset = OffsetF((context.frameSize.Width() - childSize.Width()) * HALF_FLOAT,
                pointCenter - childSize.Height() * HALF_FLOAT);
        }
        childGeometry->SetMarginFrameOffset(childOffset);
        child->Layout();
    }
}

double DotIndicatorLayoutAlgorithm::GetValidEdgeLength(float swiperLength, float indicatorLength, const Dimension& edge)
{
    return SwiperIndicatorUtils::GetValidEdgeLength(swiperLength, indicatorLength, edge);
}
} // namespace OHOS::Ace::NG
