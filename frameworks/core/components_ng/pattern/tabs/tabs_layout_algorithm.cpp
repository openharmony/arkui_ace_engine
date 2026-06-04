/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/tabs/tabs_layout_algorithm.h"

#include "core/components/common/properties/color.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/tabs/tabs_pattern.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t COUNT_2 = 2;
constexpr int32_t COUNT_3 = 3;
constexpr int32_t COUNT_4 = 4;

const Dimension FLOATING_BAR_HEIGHT = Dimension(56, Ace::DimensionUnit::VP);
const Dimension FLOATING_BAR_BOTTOM_MARGIN = Dimension(28, Ace::DimensionUnit::VP);
const Dimension BG_MASK_OVER_BAR = Dimension(16, Ace::DimensionUnit::VP);

const Dimension FLOATING_BAR_MARGIN_16 = Dimension(16, Ace::DimensionUnit::VP);
const Dimension FLOATING_BAR_MARGIN_24 = Dimension(24, Ace::DimensionUnit::VP);
const Dimension FLOATING_BAR_MARGIN_32 = Dimension(32, Ace::DimensionUnit::VP);
const Dimension FLOATING_BAR_SPACING_12 = Dimension(12, Ace::DimensionUnit::VP);

const Dimension BREAKPOINT_440 = Dimension(440, Ace::DimensionUnit::VP);
const Dimension BREAKPOINT_600 = Dimension(600, Ace::DimensionUnit::VP);
const Dimension BREAKPOINT_840 = Dimension(840, Ace::DimensionUnit::VP);
const Dimension BREAKPOINT_1140 = Dimension(1140, Ace::DimensionUnit::VP);

const Dimension COUNT_2_MINIMUM = Dimension(168, Ace::DimensionUnit::VP);
const Dimension COUNT_2_MAXIMUM = Dimension(184, Ace::DimensionUnit::VP);
const Dimension COUNT_3_MINIMUM = Dimension(248, Ace::DimensionUnit::VP);
const Dimension COUNT_3_MAXIMUM = Dimension(272, Ace::DimensionUnit::VP);
const Dimension COUNT_4_MAXIMUM = Dimension(328, Ace::DimensionUnit::VP);
const Dimension COUNT_5_MAXIMUM = Dimension(360, Ace::DimensionUnit::VP);

const Dimension FLOATING_BAR_PADDING_4 = Dimension(4, Ace::DimensionUnit::VP);
const Dimension FLOATING_BAR_PADDING_12 = Dimension(12, Ace::DimensionUnit::VP);
} // namespace

void TabsLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto axis = layoutProperty->GetAxis().value_or(Axis::HORIZONTAL);
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto tabsIdealSize = CreateIdealSizeByPercentRef(constraint.value(), Axis::HORIZONTAL,
        layoutProperty->GetMeasureType(MeasureType::MATCH_PARENT));
    auto layoutPolicy = layoutProperty->GetLayoutPolicyProperty();
    if (layoutPolicy.has_value()) {
        widthLayoutPolicy_ = layoutPolicy.value().widthLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);
        heightLayoutPolicy_ = layoutPolicy.value().heightLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);

        // When the width or height parameter is MATCH_PARENT, set its value to the parent's value.
        if (widthLayoutPolicy_ == LayoutCalPolicy::MATCH_PARENT
            || heightLayoutPolicy_ == LayoutCalPolicy::MATCH_PARENT) {
            auto layoutPolicySize = ConstrainIdealSizeByLayoutPolicy(constraint.value(),
            widthLayoutPolicy_, heightLayoutPolicy_, axis);
            tabsIdealSize.UpdateIllegalSizeWithCheck(layoutPolicySize);
        }
    }
    auto idealSize = tabsIdealSize.ConvertToSizeT();
    if (GreaterOrEqualToInfinity(idealSize.Width()) || GreaterOrEqualToInfinity(idealSize.Height())) {
        geometryNode->SetFrameSize(SizeF());
        return;
    }
    geometryNode->SetFrameSize(idealSize);
    MinusPaddingToSize(layoutProperty->CreatePaddingAndBorder(), idealSize);
    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    childLayoutConstraint.parentIdealSize = OptionalSizeF(idealSize);
    float dividerStrokeWidth = 0.0f;

    // Measure tab bar.
    SizeF tabBarSize = MeasureTabBar(layoutWrapper, childLayoutConstraint);

    // Measure effect node.
    auto effectWrapper = layoutWrapper->GetOrCreateChildByIndex(itemIndex_.effectIndex);
    if (effectWrapper) {
        MeasureEffectNode(layoutProperty, effectWrapper, idealSize);
    }

    // Measure backgroundMask node.
    MeasureBackgroundMask(layoutWrapper, idealSize, tabBarSize);

    // Measure divider.
    auto dividerWrapper = layoutWrapper->GetOrCreateChildByIndex(itemIndex_.dividerIndex);
    if (dividerWrapper) {
        dividerStrokeWidth = MeasureDivider(layoutProperty, dividerWrapper, idealSize);
    }

    auto barOverlap = layoutProperty->GetBarOverlap().value_or(false);

    // Measure swiper.
    auto swiperWrapper = layoutWrapper->GetOrCreateChildByIndex(itemIndex_.swiperIndex);
    if (swiperWrapper) {
        swiperWrapper->GetLayoutProperty()->UpdateLayoutDirection(layoutProperty->GetNonAutoLayoutDirection());
    }
    SizeF swiperSize;
    if (swiperWrapper && swiperWrapper->GetHostNode() && swiperWrapper->GetHostNode()->TotalChildCount() > 0) {
        swiperSize = MeasureSwiper(layoutProperty, swiperWrapper, idealSize, tabBarSize, dividerStrokeWidth);
    } else if (swiperWrapper && swiperWrapper->GetGeometryNode()) {
        swiperWrapper->GetGeometryNode()->SetFrameSize(SizeF());
    }

    auto paddingH = layoutProperty->CreatePaddingAndBorder().Width();
    auto paddingV = layoutProperty->CreatePaddingAndBorder().Height();
    bool isWidthNeedSetFrameWidth =
        layoutProperty->GetWidthAutoValue(false) ||
        widthLayoutPolicy_ == LayoutCalPolicy::FIX_AT_IDEAL_SIZE ||
        widthLayoutPolicy_ == LayoutCalPolicy::WRAP_CONTENT;
    bool isHeightNeedSetFrameWidth =
        layoutProperty->GetHeightAutoValue(false) ||
        heightLayoutPolicy_ == LayoutCalPolicy::FIX_AT_IDEAL_SIZE ||
        heightLayoutPolicy_ == LayoutCalPolicy::WRAP_CONTENT;
    // If the width or height is set to auto/FIX_AT_IDEAL_SIZE/WRAP_CONTENT, tabs need to reset frame size.
    if ((axis == Axis::VERTICAL) && isWidthNeedSetFrameWidth) {
        if (!barOverlap) {
            geometryNode->SetFrameWidth(tabBarSize.Width() + dividerStrokeWidth + swiperSize.Width() + paddingH);
        } else {
            geometryNode->SetFrameWidth(dividerStrokeWidth + swiperSize.Width() + paddingH);
        }
    } else if ((axis == Axis::HORIZONTAL) && isHeightNeedSetFrameWidth) {
        if (!barOverlap) {
            geometryNode->SetFrameHeight(tabBarSize.Height() + dividerStrokeWidth + swiperSize.Height() + paddingV);
        } else {
            geometryNode->SetFrameHeight(dividerStrokeWidth + swiperSize.Height() + paddingV);
        }
    }
}

void TabsLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSize = geometryNode->GetFrameSize();

    auto layoutProperty = AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto tabBarWrapper = layoutWrapper->GetChildByIndex(itemIndex_.tabBarIndex);
    auto dividerWrapper = layoutWrapper->GetOrCreateChildByIndex(itemIndex_.dividerIndex);
    auto effectWrapper = layoutWrapper->GetChildByIndex(itemIndex_.effectIndex);
    auto swiperWrapper = layoutWrapper->GetOrCreateChildByIndex(itemIndex_.swiperIndex);
    if (!tabBarWrapper || !dividerWrapper || !swiperWrapper) {
        return;
    }

    std::vector<OffsetF> offsetList = { OffsetF(), OffsetF(), OffsetF(), OffsetF() };
    if (frameSize.IsPositive()) {
        MinusPaddingToSize(layoutProperty->CreatePaddingAndBorder(), frameSize);
        offsetList = LayoutOffsetList(layoutWrapper, tabBarWrapper, effectWrapper, frameSize);
    }
    if (layoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL) {
        auto tabsWidth = geometryNode->GetFrameSize().Width();
        auto swiperWidth = swiperWrapper->GetGeometryNode()->GetFrameSize().Width();
        auto& swiperOffset = offsetList[itemIndex_.swiperIndex];
        swiperOffset = OffsetF((tabsWidth - swiperOffset.GetX() - swiperWidth), swiperOffset.GetY());
        auto dividerWidth = dividerWrapper->GetGeometryNode()->GetFrameSize().Width();
        auto& dividerOffset = offsetList[itemIndex_.dividerIndex];
        dividerOffset = OffsetF((tabsWidth - dividerOffset.GetX() - dividerWidth), dividerOffset.GetY());
        if (effectWrapper) {
            auto effectWidth = effectWrapper->GetGeometryNode()->GetMarginFrameSize().Width();
            auto& effectOffset = offsetList[itemIndex_.effectIndex];
            effectOffset = OffsetF((tabsWidth - effectOffset.GetX() - effectWidth), effectOffset.GetY());
        }
        auto tabBarWidth = tabBarWrapper->GetGeometryNode()->GetMarginFrameSize().Width();
        auto& tabBarOffset = offsetList[itemIndex_.tabBarIndex];
        tabBarOffset = OffsetF((tabsWidth - tabBarOffset.GetX() - tabBarWidth), tabBarOffset.GetY());
    }
    swiperWrapper->GetGeometryNode()->SetMarginFrameOffset(offsetList[itemIndex_.swiperIndex]);
    swiperWrapper->Layout();

    dividerWrapper->GetGeometryNode()->SetMarginFrameOffset(offsetList[itemIndex_.dividerIndex]);
    dividerWrapper->Layout();

    if (effectWrapper) {
        effectWrapper->GetGeometryNode()->SetMarginFrameOffset(offsetList[itemIndex_.effectIndex]);
        effectWrapper->Layout();
    }

    tabBarWrapper->GetGeometryNode()->SetMarginFrameOffset(offsetList[itemIndex_.tabBarIndex]);
    tabBarWrapper->Layout();

    LayoutBackgroundMask(layoutWrapper);
}

void TabsLayoutAlgorithm::UpdateBarMargin(LayoutWrapper* layoutWrapper, OffsetF& barOffset) const
{
    auto layoutProperty = AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto tabGeometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(tabGeometryNode);
    float barBottomMargin = FLOATING_BAR_BOTTOM_MARGIN.ConvertToPx();
    if (layoutProperty->HasBarFloatingStyle()) {
        auto barFloatingStyle = layoutProperty->GetBarFloatingStyleValue();
        if (barFloatingStyle.barBottomMargin.has_value() && barFloatingStyle.barBottomMargin->IsNonNegative()) {
            auto tabHeight = tabGeometryNode->GetFrameSize().Height();
            barBottomMargin = barFloatingStyle.barBottomMargin.value().ConvertToPxWithSize(tabHeight);
        }
    }
    auto tabWidth = tabGeometryNode->GetFrameSize().Width();
    auto floatingScaleEnabled = GreatOrEqual(tabWidth, BREAKPOINT_1140.ConvertToPx());
    if (floatingScaleEnabled) {
        auto tabBarWrapper = layoutWrapper->GetChildByIndex(itemIndex_.tabBarIndex);
        CHECK_NULL_VOID(tabBarWrapper);
        auto barGeometryNode = tabBarWrapper->GetGeometryNode();
        CHECK_NULL_VOID(barGeometryNode);
        auto barHeight = barGeometryNode->GetFrameSize().Height();
        barBottomMargin += (barHeight * (FLOATING_BAR_SCALE_ENLARGED - 1.0f) / COUNT_2);
    }

    barOffset -= OffsetF(0.0f, barBottomMargin);

    auto hostNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(hostNode);
    auto tabsPattern = hostNode->GetPattern<TabsPattern>();
    CHECK_NULL_VOID(tabsPattern);
    float margin = 0.0f;
    if (GreatOrEqual(tabWidth, BREAKPOINT_600.ConvertToPx())) {
        auto tabBarWrapper = layoutWrapper->GetChildByIndex(itemIndex_.tabBarIndex);
        CHECK_NULL_VOID(tabBarWrapper);
        auto barGeometryNode = tabBarWrapper->GetGeometryNode();
        CHECK_NULL_VOID(barGeometryNode);
        auto barWidth = barGeometryNode->GetFrameSize().Width();
        margin = std::min(floatingBarMargin_.value_or(margin), (tabWidth - barWidth) / COUNT_2);
        if (floatingScaleEnabled) {
            margin += (barWidth * (FLOATING_BAR_SCALE_ENLARGED - 1.0f) / COUNT_2);
        }
        tabsPattern->SetFloatingBarMargin(margin);
    } else {
        tabsPattern->SetFloatingBarMargin(std::nullopt);
    }

    tabsPattern->SetFloatingScaleEnabled(floatingScaleEnabled);
}

void TabsLayoutAlgorithm::LayoutBackgroundMask(LayoutWrapper* layoutWrapper)
{
    if (!isFloatingBar_) {
        return;
    }
    auto backgroundMaskWrapper = layoutWrapper->GetOrCreateChildByIndex(itemIndex_.bgMaskIndex);
    CHECK_NULL_VOID(backgroundMaskWrapper);
    auto layoutProperty = AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSize = geometryNode->GetFrameSize();
    auto paddingOffset = layoutProperty->CreatePaddingAndBorder().Offset();
    auto axis = GetAxis(layoutWrapper);
    auto backgroundMaskGeometryNode =
        backgroundMaskWrapper ? backgroundMaskWrapper->GetGeometryNode() : RefPtr<GeometryNode>();
    auto backgroundMaskFrameSize =
        backgroundMaskGeometryNode ? backgroundMaskGeometryNode->GetMarginFrameSize() : SizeF();
    auto offset =
        OffsetF(0.0f, frameSize.CrossSize(axis) - backgroundMaskFrameSize.CrossSize(axis) + paddingOffset.GetY());
    backgroundMaskGeometryNode->SetMarginFrameOffset(offset);
    backgroundMaskWrapper->Layout();
}

std::vector<OffsetF> TabsLayoutAlgorithm::LayoutOffsetList(
    LayoutWrapper* layoutWrapper, const RefPtr<LayoutWrapper>& tabBarWrapper,
    const RefPtr<LayoutWrapper>& effectNodeWrapper, const SizeF& frameSize) const
{
    std::vector<OffsetF> offsetList;
    OffsetF tabBarOffset;
    OffsetF dividerOffset;
    OffsetF swiperOffset;
    OffsetF effectOffset;
    auto axis = GetAxis(layoutWrapper);
    auto barPosition = GetBarPosition(layoutWrapper);
    auto divider = GetDivider(layoutWrapper);
    auto tabBarGeometryNode = tabBarWrapper->GetGeometryNode();
    auto effectNodeGeometryNode = effectNodeWrapper ? effectNodeWrapper->GetGeometryNode() : RefPtr<GeometryNode>();
    CHECK_NULL_RETURN(tabBarGeometryNode, offsetList);
    auto tabBarFrameSize = tabBarGeometryNode->GetMarginFrameSize();
    auto effectNodeFrameSize = effectNodeGeometryNode ? effectNodeGeometryNode->GetMarginFrameSize() : SizeF();
    auto dividerStrokeWidth = divider.isNull ? 0.0f : divider.strokeWidth.ConvertToPx();
    auto dividerStartMargin = divider.startMargin.ConvertToPx();
    auto layoutProperty = DynamicCast<TabsLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, offsetList);
    auto paddingOffset = layoutProperty->CreatePaddingAndBorder().Offset();
    auto barOverlap = layoutProperty->GetBarOverlap().value_or(false);

    if (axis == Axis::HORIZONTAL) {
        float barPosX = (frameSize.MainSize(axis) - tabBarFrameSize.MainSize(axis)) / 2 + paddingOffset.GetX();
        float effectPosX = (frameSize.MainSize(axis) - effectNodeFrameSize.MainSize(axis)) / 2 + paddingOffset.GetX();
        if (barPosition == BarPosition::START) {
            tabBarOffset = OffsetF(barPosX, paddingOffset.GetY());
            effectOffset = OffsetF(effectPosX, paddingOffset.GetY());
            dividerOffset = OffsetF(dividerStartMargin + paddingOffset.GetX(),
                tabBarFrameSize.CrossSize(axis) + paddingOffset.GetY());
            swiperOffset = barOverlap ? paddingOffset : OffsetF(paddingOffset.GetX(),
                tabBarFrameSize.CrossSize(axis) + dividerStrokeWidth + paddingOffset.GetY());
        } else {
            tabBarOffset = OffsetF(barPosX, frameSize.CrossSize(axis) -
                tabBarFrameSize.CrossSize(axis) + paddingOffset.GetY());
            effectOffset = OffsetF(effectPosX, frameSize.CrossSize(axis) -
                effectNodeFrameSize.CrossSize(axis) + paddingOffset.GetY());
            dividerOffset = OffsetF(dividerStartMargin + paddingOffset.GetX(), frameSize.CrossSize(axis) -
                tabBarFrameSize.CrossSize(axis) + paddingOffset.GetY() - dividerStrokeWidth);
            swiperOffset = paddingOffset;
        }
    } else {
        float barPosY = (frameSize.MainSize(axis) - tabBarFrameSize.MainSize(axis)) / 2 + paddingOffset.GetY();
        float effectPosY = (frameSize.MainSize(axis) - effectNodeFrameSize.MainSize(axis)) / 2 + paddingOffset.GetY();
        if (barPosition == BarPosition::START) {
            tabBarOffset = OffsetF(paddingOffset.GetX(), barPosY);
            effectOffset = OffsetF(paddingOffset.GetX(), effectPosY);
            dividerOffset = OffsetF(tabBarFrameSize.CrossSize(axis) + paddingOffset.GetX(),
                dividerStartMargin + paddingOffset.GetY());
            swiperOffset = barOverlap ? paddingOffset : OffsetF(tabBarFrameSize.CrossSize(axis) +
                paddingOffset.GetX() + dividerStrokeWidth, paddingOffset.GetY());
        } else {
            tabBarOffset = OffsetF(frameSize.CrossSize(axis) - tabBarFrameSize.CrossSize(axis) +
                paddingOffset.GetX(), barPosY);
            effectOffset = OffsetF(frameSize.CrossSize(axis) - effectNodeFrameSize.CrossSize(axis) +
                paddingOffset.GetX(), effectPosY);
            dividerOffset = OffsetF(frameSize.CrossSize(axis) - tabBarFrameSize.CrossSize(axis) +
                paddingOffset.GetX() - dividerStrokeWidth, dividerStartMargin + paddingOffset.GetY());
            swiperOffset = paddingOffset;
        }
    }
    offsetList.emplace_back(swiperOffset);
    if (itemIndex_.bgMaskIndex > 0) {
        offsetList.emplace_back(OffsetF());
    }
    offsetList.emplace_back(dividerOffset);
    if (isFloatingBar_) {
        UpdateBarMargin(layoutWrapper, tabBarOffset);
    }
    offsetList.emplace_back(tabBarOffset);
    offsetList.emplace_back(effectOffset);
    return offsetList;
}

BarPosition TabsLayoutAlgorithm::GetBarPosition(LayoutWrapper* layoutWrapper) const
{
    auto layoutProperty = AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, BarPosition::START);
    return layoutProperty->GetTabBarPosition().value_or(BarPosition::START);
}

Axis TabsLayoutAlgorithm::GetAxis(LayoutWrapper* layoutWrapper) const
{
    auto layoutProperty = AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, Axis::HORIZONTAL);
    return layoutProperty->GetAxis().value_or(Axis::HORIZONTAL);
}

TabsItemDivider TabsLayoutAlgorithm::GetDivider(LayoutWrapper* layoutWrapper) const
{
    auto layoutProperty = AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper->GetLayoutProperty());
    TabsItemDivider divider;
    CHECK_NULL_RETURN(layoutProperty, divider);
    return layoutProperty->GetDivider().value_or(divider);
}

float TabsLayoutAlgorithm::MeasureDivider(const RefPtr<TabsLayoutProperty>& layoutProperty,
    const RefPtr<LayoutWrapper>& dividerWrapper, const SizeF& idealSize)
{
    auto constraint = layoutProperty->GetLayoutConstraint();
    
    auto dividerIdealSize = CreateIdealSize(
        constraint.value(), Axis::HORIZONTAL, layoutProperty->GetMeasureType(MeasureType::MATCH_PARENT), true);
    TabsItemDivider defaultDivider;
    auto axis = layoutProperty->GetAxis().value_or(Axis::HORIZONTAL);
    auto parentWidth = idealSize.Width();
    auto parentHeight = idealSize.Height();
    auto divider = layoutProperty->GetDivider().value_or(defaultDivider);
    auto dividerStrokeWidth = divider.strokeWidth.ConvertToPx();
    auto dividerStartMargin = divider.startMargin.ConvertToPx();
    auto dividerEndMargin = divider.endMargin.ConvertToPx();

    if (axis == Axis::VERTICAL) {
        dividerIdealSize.SetWidth(dividerStrokeWidth);
        dividerIdealSize.SetHeight(parentHeight - dividerStartMargin - dividerEndMargin);
    } else if (axis == Axis::HORIZONTAL) {
        dividerIdealSize.SetWidth(parentWidth - dividerStartMargin - dividerEndMargin);
        dividerIdealSize.SetHeight(dividerStrokeWidth);
    }

    auto dividerLayoutConstraint = layoutProperty->CreateChildConstraint();
    dividerLayoutConstraint.selfIdealSize = OptionalSizeF(dividerIdealSize);
    dividerWrapper->Measure(dividerLayoutConstraint);

    return divider.isNull ? 0.0f : dividerStrokeWidth;
}

void TabsLayoutAlgorithm::MeasureEffectNode(const RefPtr<TabsLayoutProperty>& layoutProperty,
    const RefPtr<LayoutWrapper>& effectNodeWrapper, const SizeF& idealSize)
{
    auto constraint = layoutProperty->GetLayoutConstraint();
    
    auto effectNodeIdealSize = CreateIdealSize(
        constraint.value(), Axis::HORIZONTAL, layoutProperty->GetMeasureType(MeasureType::MATCH_PARENT), true);
    TabsEffectNodeOption defaultEffectNodeOption;
    auto axis = layoutProperty->GetAxis().value_or(Axis::HORIZONTAL);
    auto parentWidth = idealSize.Width();
    auto parentHeight = idealSize.Height();
    auto effectNodeOption = layoutProperty->GetEffectNodeOption().value_or(defaultEffectNodeOption);
    auto effectNodeWidth = effectNodeOption.strokeWidth.ConvertToPx();
    
    if (axis == Axis::VERTICAL) {
        effectNodeIdealSize.SetWidth(effectNodeWidth);
        effectNodeIdealSize.SetHeight(parentHeight);
    } else if (axis == Axis::HORIZONTAL) {
        effectNodeIdealSize.SetWidth(parentWidth);
        effectNodeIdealSize.SetHeight(effectNodeWidth);
    }
    
    auto effectNodeLayoutConstraint = layoutProperty->CreateChildConstraint();
    effectNodeLayoutConstraint.selfIdealSize = OptionalSizeF(effectNodeIdealSize);
    effectNodeWrapper->Measure(effectNodeLayoutConstraint);
}

SizeF TabsLayoutAlgorithm::MeasureSwiper(const RefPtr<TabsLayoutProperty>& layoutProperty,
    RefPtr<LayoutWrapper>& swiperWrapper, const SizeF& idealSize, const SizeF& tabBarSize, const float dividerWidth)
{
    auto axis = layoutProperty->GetAxis().value_or(Axis::HORIZONTAL);
    auto barOverlap = layoutProperty->GetBarOverlap().value_or(false);

    /*
     * When the width or height of tabs are set to auto, WRAP_CONTENT, FIX_AT_IDEAL_SIZE,
     * the size of the tabs adaptive child nodes is required, but the constraints are different.
     *
     * 1. When set to auto, the maxSize of tabcontent is the idealsize of the tabs,
     *    and the maxSize of tabs will exceed the parent node size.
     *
     * 2. When set to WRAP_CONTENT,
     *    the maxSize of tabcontent should be tabs size minus the rest of the tabs node size,
     *    the maxSize of tabs is equal to the size of the parent node;
     *
     * 3. When set to FIX_AT_IDEAL_SIZE, there is no limit to the maxSize of tabcontent/tabs.
     */
    bool autoWidth = layoutProperty->GetWidthAutoValue(false) || IsWidthFixOrWrap();
    bool autoHeight = layoutProperty->GetHeightAutoValue(false) || IsHeightFixOrWrap();
    SizeF parentIdealSize = idealSize;
    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    childLayoutConstraint.parentIdealSize = OptionalSizeF(idealSize);

    // If the width or height is set to FIX_AT_IDEAL_SIZE, the maxSize should be set to infinite.
    SetFixAtIdealSizeMaxSize(childLayoutConstraint);

    /*
     * If the width or height is set to WRAP_CONTENT,
     * the maxSize of tabs should be idealsize,
     * and the maxSize of tabcontent should be tabs size minus the rest of the tabs node size.
     */
    auto paddingWidth = layoutProperty->CreatePaddingAndBorder().Width();
    auto paddingHeight = layoutProperty->CreatePaddingAndBorder().Height();
    if (axis == Axis::HORIZONTAL) {
        if (!barOverlap) {
            auto idealHeight = idealSize.Height() - tabBarSize.Height() - dividerWidth;
            SetWrapContentMaxHeight(childLayoutConstraint, (idealHeight - paddingHeight));
            if (!autoHeight) {
                childLayoutConstraint.selfIdealSize.SetHeight(idealHeight);
            }
            childLayoutConstraint.selfIdealSize.SetWidth(idealSize.Width());
            parentIdealSize.SetHeight(idealHeight);
        } else {
            SetWrapContentMaxHeight(childLayoutConstraint, (idealSize.Height() - paddingHeight));
            if (!autoHeight) {
                childLayoutConstraint.selfIdealSize.SetHeight(idealSize.Height());
            }
            childLayoutConstraint.selfIdealSize.SetWidth(idealSize.Width());
            parentIdealSize.SetHeight(idealSize.Height());
        }
    } else if (axis == Axis::VERTICAL) {
        if (!barOverlap) {
            auto idealWidth = idealSize.Width() - tabBarSize.Width() - dividerWidth;
            SetWrapContentMaxWidth(childLayoutConstraint, (idealWidth - paddingWidth));
            if (!autoWidth) {
                childLayoutConstraint.selfIdealSize.SetWidth(idealWidth);
            }
            childLayoutConstraint.selfIdealSize.SetHeight(idealSize.Height());
            parentIdealSize.SetWidth(idealWidth);
        } else {
            SetWrapContentMaxWidth(childLayoutConstraint, (idealSize.Width() - paddingWidth));
            if (!autoWidth) {
                childLayoutConstraint.selfIdealSize.SetWidth(idealSize.Width());
            }
            childLayoutConstraint.selfIdealSize.SetHeight(idealSize.Height());
            parentIdealSize.SetWidth(idealSize.Width());
        }
    }
    childLayoutConstraint.parentIdealSize = OptionalSizeF(parentIdealSize);
    swiperWrapper->Measure(childLayoutConstraint);

    return swiperWrapper->GetGeometryNode()->GetMarginFrameSize();
}

void TabsLayoutAlgorithm::MeasureBackgroundMask(
    LayoutWrapper* layoutWrapper, const SizeF& idealSize, const SizeF& tabBarSize)
{
    if (!isFloatingBar_) {
        return;
    }
    auto backgroundMaskWrapper = layoutWrapper->GetOrCreateChildByIndex(itemIndex_.bgMaskIndex);
    CHECK_NULL_VOID(backgroundMaskWrapper);

    auto layoutProperty = AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto MaskNodeIdealSize = CreateIdealSize(
        constraint.value(), Axis::HORIZONTAL, layoutProperty->GetMeasureType(MeasureType::MATCH_PARENT), true);
    auto parentWidth = idealSize.Width();
    MaskNodeIdealSize.SetWidth(parentWidth);

    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    float tabWidth = geometryNode->GetMarginFrameSize().Width();
    float tabBarHeight = tabBarSize.Height();
    if (GreatOrEqual(tabWidth, BREAKPOINT_1140.ConvertToPx())) {
        tabBarHeight *= FLOATING_BAR_SCALE_ENLARGED;
    }
    float maskHeight = FLOATING_BAR_BOTTOM_MARGIN.ConvertToPx() + tabBarHeight + BG_MASK_OVER_BAR.ConvertToPx();
    if (layoutProperty->HasBarFloatingStyle()) {
        auto tabGeometryNode = layoutWrapper->GetGeometryNode();
        CHECK_NULL_VOID(tabGeometryNode);
        auto tabHeight = tabGeometryNode->GetFrameSize().Height();
        auto barFloatingStyle = layoutProperty->GetBarFloatingStyleValue();
        if (barFloatingStyle.maskHeight.has_value() && barFloatingStyle.maskHeight->IsNonNegative()) {
            maskHeight = barFloatingStyle.maskHeight.value().ConvertToPxWithSize(tabHeight);
        } else {
            if (barFloatingStyle.barBottomMargin.has_value() && barFloatingStyle.barBottomMargin->IsNonNegative()) {
                float barbottomMargin = barFloatingStyle.barBottomMargin.value().ConvertToPxWithSize(tabHeight);
                maskHeight = barbottomMargin + tabBarHeight + BG_MASK_OVER_BAR.ConvertToPx();
            }
        }
    }

    maskHeight = std::min(maskHeight, idealSize.Height());
    MaskNodeIdealSize.SetHeight(maskHeight);

    auto MaskNodeIdealSizeLayoutConstraint = layoutProperty->CreateChildConstraint();
    MaskNodeIdealSizeLayoutConstraint.selfIdealSize = OptionalSizeF(MaskNodeIdealSize);
    backgroundMaskWrapper->Measure(MaskNodeIdealSizeLayoutConstraint);
}

SizeF TabsLayoutAlgorithm::MeasureTabBar(LayoutWrapper* layoutWrapper, LayoutConstraintF childLayoutConstraint)
{
    SizeF tabBarSize;
    auto tabBarWrapper = layoutWrapper->GetOrCreateChildByIndex(itemIndex_.tabBarIndex);
    CHECK_NULL_RETURN(tabBarWrapper, tabBarSize);
    auto layoutProperty = AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, tabBarSize);
    auto tabBarNode = tabBarWrapper->GetHostNode();
    CHECK_NULL_RETURN(tabBarNode, tabBarSize);
    auto tabBarRenderContext = tabBarNode->GetRenderContext();
    CHECK_NULL_RETURN(tabBarRenderContext, tabBarSize);

    if (!isFloatingBar_) {
        tabBarWrapper->Measure(childLayoutConstraint);
        auto geometryNode = tabBarWrapper->GetGeometryNode();
        CHECK_NULL_RETURN(geometryNode, tabBarSize);
        tabBarSize = geometryNode->GetMarginFrameSize();
        // Clear the corresponding attributes when the floating state is disabled.
        if (lastFloatingBar_) {
            auto barLayoutProperty = tabBarNode->GetLayoutProperty();
            if (barLayoutProperty) {
                PaddingProperty padding;
                barLayoutProperty->UpdatePadding(padding);
            }
            BorderRadiusProperty radius;
            tabBarRenderContext->UpdateBorderRadius(radius);
            tabBarRenderContext->ResetBorderRadius();
            tabBarRenderContext->UpdateClipEdge(false);
        }
        return tabBarSize;
    }
    if (layoutWrapper->ConstraintChanged()) {
        auto hostNode = layoutWrapper->GetHostNode();
        CHECK_NULL_RETURN(hostNode, tabBarSize);
        auto tabsPattern = hostNode->GetPattern<TabsPattern>();
        CHECK_NULL_RETURN(tabsPattern, tabBarSize);
        tabsPattern->ResetTabBarFollowHandPosition();
    }

    auto barLayoutProperty = tabBarWrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(barLayoutProperty, tabBarSize);
    auto constraint = barLayoutProperty->GetLayoutConstraint();
    float barHeight = FLOATING_BAR_HEIGHT.ConvertToPx();
    if (!constraint || !constraint->selfIdealSize.Height().has_value()) {
        childLayoutConstraint.selfIdealSize.SetHeight(FLOATING_BAR_HEIGHT.ConvertToPx());
    } else {
        barHeight = constraint->selfIdealSize.Height().value();
    }

    if (barLayoutProperty && GreatNotEqual(barHeight, FLOATING_BAR_PADDING_4.ConvertToPx() * COUNT_2)) {
        PaddingProperty padding;
        padding.SetEdges(CalcLength(FLOATING_BAR_PADDING_12), CalcLength(FLOATING_BAR_PADDING_12),
            CalcLength(FLOATING_BAR_PADDING_4), CalcLength(FLOATING_BAR_PADDING_4));
        barLayoutProperty->UpdatePadding(padding);
    }

    if (layoutProperty->HasBarWidth() && layoutProperty->GetBarWidthValue().IsNonNegative()) {
        tabBarWrapper->Measure(childLayoutConstraint);
    } else {
        std::optional<float> calcBarWidth = CalcFloatingBarWidth(layoutWrapper, barHeight);
        if (calcBarWidth.has_value()) {
            childLayoutConstraint.selfIdealSize.SetWidth(calcBarWidth.value());
        }
        tabBarWrapper->Measure(childLayoutConstraint);
    }
    auto geometryNode = tabBarWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, tabBarSize);
    tabBarSize = geometryNode->GetMarginFrameSize();

    BorderRadiusProperty radius;
    radius.SetRadius(Dimension(tabBarSize.Height() / COUNT_2));
    tabBarRenderContext->UpdateBorderRadius(radius);
    tabBarRenderContext->UpdateClipEdge(true);

    return tabBarSize;
}

std::optional<float> TabsLayoutAlgorithm::CalcFloatingBarWidth(LayoutWrapper* layoutWrapper, float barHeight)
{
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, std::nullopt);
    float tabsWidth = geometryNode->GetMarginFrameSize().Width();
    float tabsHeight = geometryNode->GetMarginFrameSize().Height();

    auto ret = ParseBarWidthAndMargin(layoutWrapper, tabsWidth, tabsHeight);
    if (ret.has_value()) {
        return ret;
    }

    float breakpoint600 = BREAKPOINT_600.ConvertToPx();
    float breakpoint840 = BREAKPOINT_840.ConvertToPx();
    // Default rule calulation.
    if (barItemSize_ <= COUNT_2) {
        if (LessNotEqual(tabsWidth, breakpoint600)) {
            return COUNT_2_MINIMUM.ConvertToPx();
        } else {
            return COUNT_2_MAXIMUM.ConvertToPx();
        }
    }

    if (barItemSize_ == COUNT_3) {
        if (LessNotEqual(tabsWidth, breakpoint600)) {
            return COUNT_3_MINIMUM.ConvertToPx();
        } else {
            return COUNT_3_MAXIMUM.ConvertToPx();
        }
    }

    barHeight = std::min(barHeight, tabsHeight);
    float sideMargin = floatingBarMargin_.value_or(0.0f);
    if (barItemSize_ >= COUNT_4) {
        float width = 0.0f;
        if (LessNotEqual(tabsWidth, breakpoint600)) {
            width = tabsWidth - COUNT_2 * sideMargin;
        } else if (LessNotEqual(tabsWidth, breakpoint840)) {
            width = tabsWidth - COUNT_2 * (sideMargin + FLOATING_BAR_SPACING_12.ConvertToPx() + barHeight);
        } else {
            width = (tabsWidth / COUNT_2 - COUNT_2 * sideMargin) * COUNT_2;
        }
        if (barItemSize_ == COUNT_4) {
            return std::clamp(width, 0.0f, static_cast<float>(COUNT_4_MAXIMUM.ConvertToPx()));
        } else {
            return std::clamp(width, 0.0f, static_cast<float>(COUNT_5_MAXIMUM.ConvertToPx()));
        }
    }

    return std::nullopt;
}

std::optional<float> TabsLayoutAlgorithm::ParseBarWidthAndMargin(
    LayoutWrapper* layoutWrapper, float tabsWidth, float tabsHeight)
{
    auto layoutProperty = AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, std::nullopt);
    auto barFloatingStyle = layoutProperty->GetBarFloatingStyle();

    float breakpoint440 = BREAKPOINT_440.ConvertToPx();
    float breakpoint600 = BREAKPOINT_600.ConvertToPx();
    float breakpoint840 = BREAKPOINT_840.ConvertToPx();
    // Margin calculate.
    if (LessNotEqual(tabsWidth, breakpoint600)) {
        floatingBarMargin_ = FLOATING_BAR_MARGIN_16.ConvertToPx();
    } else if (LessNotEqual(tabsWidth, breakpoint840)) {
        floatingBarMargin_ = FLOATING_BAR_MARGIN_24.ConvertToPx();
    } else {
        floatingBarMargin_ = FLOATING_BAR_MARGIN_32.ConvertToPx();
    }

    if (!barFloatingStyle.has_value()) {
        return std::nullopt;
    }
    // The values actively set by the interface take priority in taking effect.
    if (barFloatingStyle->barSideMargin.has_value() && barFloatingStyle->barSideMargin->IsNonNegative()) {
        floatingBarMargin_ = barFloatingStyle->barSideMargin.value().ConvertToPxWithSize(tabsWidth);
    }

    if (LessNotEqual(tabsWidth, breakpoint440) && barFloatingStyle->smallBarWidth.has_value() &&
        barFloatingStyle->smallBarWidth->IsNonNegative()) {
        return barFloatingStyle->smallBarWidth.value().ConvertToPxWithSize(tabsWidth);
    }

    bool displayRatioGreaterThan08 = NearZero(tabsWidth) ? true : GreatNotEqual(tabsHeight / tabsWidth, 0.8);
    bool isMediumWidth = (GreatOrEqual(tabsWidth, breakpoint440) && LessNotEqual(tabsWidth, breakpoint600)) ||
                         (!displayRatioGreaterThan08 && GreatOrEqual(tabsWidth, breakpoint600) &&
                             LessNotEqual(tabsWidth, breakpoint840));
    if (isMediumWidth && barFloatingStyle->mediumBarWidth.has_value() &&
        barFloatingStyle->mediumBarWidth->IsNonNegative()) {
        return barFloatingStyle->mediumBarWidth.value().ConvertToPxWithSize(tabsWidth);
    }

    bool isLargeWidth =
        GreatOrEqual(tabsWidth, breakpoint840) ||
        (displayRatioGreaterThan08 && GreatOrEqual(tabsWidth, breakpoint600) && LessNotEqual(tabsWidth, breakpoint840));
    if (isLargeWidth && barFloatingStyle->largeBarWidth.has_value() &&
        barFloatingStyle->largeBarWidth->IsNonNegative()) {
        return barFloatingStyle->largeBarWidth.value().ConvertToPxWithSize(tabsWidth);
    }

    return std::nullopt;
}
} // namespace OHOS::Ace::NG
