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

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t SWIPER_INDEX = 0;
constexpr int32_t DIVIDER_INDEX = 1;
constexpr int32_t TAB_BAR_INDEX = 2;
constexpr int32_t EFFECT_INDEX = 3;
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
    auto tabBarWrapper = layoutWrapper->GetOrCreateChildByIndex(TAB_BAR_INDEX);
    SizeF tabBarSize;
    if (tabBarWrapper) {
        tabBarWrapper->Measure(childLayoutConstraint);
        tabBarSize = tabBarWrapper->GetGeometryNode()->GetMarginFrameSize();
    }
    
    // Measure effect node.
    auto effectWrapper = layoutWrapper->GetOrCreateChildByIndex(EFFECT_INDEX);
    if (effectWrapper) {
        MeasureEffectNode(layoutProperty, effectWrapper, idealSize);
    }

    // Measure divider.
    auto dividerWrapper = layoutWrapper->GetOrCreateChildByIndex(DIVIDER_INDEX);
    if (dividerWrapper) {
        dividerStrokeWidth = MeasureDivider(layoutProperty, dividerWrapper, idealSize);
    }

    auto barOverlap = layoutProperty->GetBarOverlap().value_or(false);

    // Measure swiper.
    auto swiperWrapper = layoutWrapper->GetOrCreateChildByIndex(SWIPER_INDEX);
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
    auto tabBarWrapper = layoutWrapper->GetChildByIndex(TAB_BAR_INDEX);
    auto dividerWrapper = layoutWrapper->GetOrCreateChildByIndex(DIVIDER_INDEX);
    auto effectWrapper = layoutWrapper->GetChildByIndex(EFFECT_INDEX);
    auto swiperWrapper = layoutWrapper->GetOrCreateChildByIndex(SWIPER_INDEX);
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
        auto& swiperOffset = offsetList[SWIPER_INDEX];
        swiperOffset = OffsetF((tabsWidth - swiperOffset.GetX() - swiperWidth), swiperOffset.GetY());
        auto dividerWidth = dividerWrapper->GetGeometryNode()->GetFrameSize().Width();
        auto& dividerOffset = offsetList[DIVIDER_INDEX];
        dividerOffset = OffsetF((tabsWidth - dividerOffset.GetX() - dividerWidth), dividerOffset.GetY());
        if (effectWrapper) {
            auto effectWidth = effectWrapper->GetGeometryNode()->GetMarginFrameSize().Width();
            auto& effectOffset = offsetList[EFFECT_INDEX];
            effectOffset = OffsetF((tabsWidth - effectOffset.GetX() - effectWidth), effectOffset.GetY());
        }
        auto tabBarWidth = tabBarWrapper->GetGeometryNode()->GetMarginFrameSize().Width();
        auto& tabBarOffset = offsetList[TAB_BAR_INDEX];
        tabBarOffset = OffsetF((tabsWidth - tabBarOffset.GetX() - tabBarWidth), tabBarOffset.GetY());
    }
    swiperWrapper->GetGeometryNode()->SetMarginFrameOffset(offsetList[SWIPER_INDEX]);
    swiperWrapper->Layout();

    dividerWrapper->GetGeometryNode()->SetMarginFrameOffset(offsetList[DIVIDER_INDEX]);
    dividerWrapper->Layout();

    if (effectWrapper) {
        effectWrapper->GetGeometryNode()->SetMarginFrameOffset(offsetList[EFFECT_INDEX]);
        effectWrapper->Layout();
    }

    tabBarWrapper->GetGeometryNode()->SetMarginFrameOffset(offsetList[TAB_BAR_INDEX]);
    tabBarWrapper->Layout();
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
    offsetList.emplace_back(dividerOffset);
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
} // namespace OHOS::Ace::NG
