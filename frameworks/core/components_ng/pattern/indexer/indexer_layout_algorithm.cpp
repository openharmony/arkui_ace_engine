/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/indexer/indexer_layout_algorithm.h"

#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {

void IndexerLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto indexerLayoutProperty = AceType::DynamicCast<IndexerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(indexerLayoutProperty);
    auto childCount = layoutWrapper->GetTotalChildCount();
    if (indexerLayoutProperty->GetIsPopupValue(false)) {
        MeasurePopup(layoutWrapper, childCount);
        childCount--;
    }

    LayoutConstraintF layoutConstraint;
    auto constraint = indexerLayoutProperty->GetLayoutConstraint();
    if (constraint.has_value()) {
        layoutConstraint = constraint.value();
    }
    OptionalSize<float> selfIdealSize = layoutConstraint.selfIdealSize;
    Dimension itemSize = indexerLayoutProperty->GetItemSize().value_or(Dimension(INDEXER_ITEM_SIZE, DimensionUnit::VP));
    itemSize_ = ConvertToPx(itemSize, layoutConstraint.scaleProperty, layoutConstraint.maxSize.Height())
                    .value_or(Dimension(INDEXER_ITEM_SIZE, DimensionUnit::VP).ConvertToPx());

    auto defaultHorizontalPadding = Dimension(INDEXER_PADDING_LEFT, DimensionUnit::VP).ConvertToPx();
    auto defaultVerticalPadding = Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)
                                      ? Dimension(INDEXER_PADDING_TOP_API_TWELVE, DimensionUnit::VP).ConvertToPx()
                                      : Dimension(INDEXER_PADDING_TOP, DimensionUnit::VP).ConvertToPx();
    const auto& padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorderWithDefault(
        static_cast<float>(defaultHorizontalPadding), static_cast<float>(defaultVerticalPadding), 0, 0);
    auto verticalPadding = (padding.top.value_or(0) + padding.bottom.value_or(0));
    auto horizontalPadding = padding.left.value_or(0.0f) + padding.right.value_or(0.0f);

    auto adaptiveWidth = indexerLayoutProperty->GetAdaptiveWidthValue(false);
    auto maxItemWidth = adaptiveWidth ? GetMaxItemWidth(layoutWrapper) : 0.0f;
    auto contentWidth = adaptiveWidth ? (GreatOrEqual(maxItemWidth, itemSize_) ? maxItemWidth : itemSize_) : itemSize_;
    auto frameWidth = selfIdealSize.Width().has_value()
                           ? selfIdealSize.Width().value()
                           : std::clamp(contentWidth + horizontalPadding, 0.0f, layoutConstraint.maxSize.Width());
    auto layoutPolicy = indexerLayoutProperty->GetLayoutPolicyProperty();
    LayoutCalPolicy widthLayoutPolicy = LayoutCalPolicy::NO_MATCH;
    LayoutCalPolicy heightLayoutPolicy = LayoutCalPolicy::NO_MATCH;
    if (layoutPolicy.has_value()) {
        widthLayoutPolicy = layoutPolicy.value().widthLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);
        heightLayoutPolicy = layoutPolicy.value().heightLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);
    }
    auto parentIdealSize = layoutConstraint.parentIdealSize;
    if (widthLayoutPolicy == LayoutCalPolicy::FIX_AT_IDEAL_SIZE) {
        // When the width parameter is FIX_AT_IDEAL_SIZE, reset the width adaptive content area
        frameWidth = contentWidth + horizontalPadding;
    }
    itemWidth_ = GreatNotEqual(frameWidth - horizontalPadding, 0.0f) ? frameWidth - horizontalPadding : 0.0f;

    auto contentHeight = childCount * itemSize_;
    float maxFrameHeight =
        selfIdealSize.Height().has_value() ? selfIdealSize.Height().value() : layoutConstraint.maxSize.Height();
    maxContentHeight_ = GreatNotEqual(maxFrameHeight - verticalPadding, 0.0f) ? maxFrameHeight - verticalPadding : 0.0f;
    bool isHeightFixAtIdealSize = heightLayoutPolicy == LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    if (!isHeightFixAtIdealSize) {
        // When the height setting is not FIX_AT_IDEAL_SIZE,
        // there is a maximum height restriction for the content area.
        contentHeight = GreatNotEqual(contentHeight, maxContentHeight_) ? maxContentHeight_ : contentHeight;
    }
    itemHeight_ = GreatNotEqual(contentHeight, 0.0f) && childCount > 0 ? contentHeight / childCount : 0.0f;
    float frameHeight = selfIdealSize.Height().has_value()
                            ? selfIdealSize.Height().value()
                            : std::clamp(contentHeight + verticalPadding, 0.0f, layoutConstraint.maxSize.Height());

    if (heightLayoutPolicy == LayoutCalPolicy::MATCH_PARENT && parentIdealSize.Height().has_value()) {
        // When the height parameter is MATCH_PARENT, set the height to be equal to the parent's height.
        frameHeight = layoutConstraint.parentIdealSize.Height().value();
    }
    if (isHeightFixAtIdealSize) {
        // When the height parameter is FIX_AT_IDEAL_SIZE, reset the height adaptive content area
        frameHeight = contentHeight + verticalPadding;
    }
    auto childLayoutConstraint = indexerLayoutProperty->CreateChildConstraint();
    for (int32_t index = 0; index < childCount; index++) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        CHECK_NULL_VOID(childWrapper);
        childLayoutConstraint.UpdateSelfMarginSizeWithCheck(OptionalSizeF(itemWidth_, itemHeight_));
        childWrapper->Measure(childLayoutConstraint);
    }

    layoutWrapper->GetGeometryNode()->SetFrameSize(SizeF(frameWidth, frameHeight));
}

void IndexerLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = DynamicCast<IndexerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto frameSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto defaultHorizontalPadding = Dimension(INDEXER_PADDING_LEFT, DimensionUnit::VP).ConvertToPx();
    auto defaultVerticalPadding = Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)
                                      ? Dimension(INDEXER_PADDING_TOP_API_TWELVE, DimensionUnit::VP).ConvertToPx()
                                      : Dimension(INDEXER_PADDING_TOP, DimensionUnit::VP).ConvertToPx();
    const auto& padding = layoutProperty->CreatePaddingAndBorderWithDefault(
        static_cast<float>(defaultHorizontalPadding), static_cast<float>(defaultVerticalPadding), 0, 0);
    auto size = frameSize;
    MinusPaddingToSize(padding, size);
    auto left = padding.left.value_or(0);
    auto top = padding.top.value_or(0);
    auto paddingOffset = OffsetF(left, top);
    auto align = Alignment::CENTER;
    if (layoutProperty->GetPositionProperty()) {
        align = layoutProperty->GetPositionProperty()->GetAlignment().value_or(align);
    }
    SizeF contentSize(itemWidth_, 0);
    auto childCount = layoutWrapper->GetTotalChildCount();
    if (layoutProperty->GetIsPopupValue(false)) {
        const auto& child = layoutWrapper->GetChildByIndex(childCount - 1);
        auto offset = GetPositionOfPopupNode(layoutProperty, frameSize.Width());
        child->GetHostNode()->GetRenderContext()->UpdatePosition(offset);
        child->Layout();
        childCount -= 1;
    }
    for (int32_t i = 0; i < childCount; i++) {
        const auto& child = layoutWrapper->GetChildByIndex(i);
        SizeF childSize = child->GetGeometryNode()->GetMarginFrameSize();
        contentSize.AddHeight(childSize.Height());
    }
    auto translate = Alignment::GetAlignPosition(size, contentSize, align);
    for (int32_t i = 0; i < childCount; i++) {
        const auto& child = layoutWrapper->GetChildByIndex(i);
        child->GetGeometryNode()->SetMarginFrameOffset(
            translate + paddingOffset + OffsetF(0, itemHeight_ * i));
        child->Layout();
    }
}

OffsetT<Dimension> IndexerLayoutAlgorithm::GetPositionOfPopupNode(
    const RefPtr<IndexerLayoutProperty>& layoutProperty, float indexerWidth)
{
    auto alignment = layoutProperty->GetAlignStyle().value_or(NG::AlignStyle::END);
    auto userDefinePositionX =
        layoutProperty->GetPopupPositionX().value_or(Dimension(NG::BUBBLE_POSITION_X, DimensionUnit::VP)).ConvertToPx();
    auto userDefinePositionY =
        layoutProperty->GetPopupPositionY().value_or(Dimension(NG::BUBBLE_POSITION_Y, DimensionUnit::VP)).ConvertToPx();
    auto userDefineSpace = layoutProperty->GetPopupHorizontalSpace();

    auto padding = layoutProperty->CreatePaddingWithoutBorder();
    auto left = padding.left.value_or(0);
    auto top = padding.top.value_or(0);
    if (IsPopupAtLeft(layoutProperty, alignment)) {
        userDefinePositionX = (userDefineSpace ? userDefineSpace.value().ConvertToPx() + indexerWidth
                                    : userDefinePositionX + indexerWidth / 2) - left;
    } else {
        auto bubbleSize = Dimension(BUBBLE_BOX_SIZE, DimensionUnit::VP).ConvertToPx();
        userDefinePositionX = (userDefineSpace ? -userDefineSpace.value().ConvertToPx()
                                    : -userDefinePositionX + indexerWidth / 2)  - left - bubbleSize;
    }
    userDefinePositionY -= top;
    return OffsetT<Dimension>(Dimension(userDefinePositionX), Dimension(userDefinePositionY));
}

bool IndexerLayoutAlgorithm::IsPopupAtLeft(
    const RefPtr<IndexerLayoutProperty>& layoutProperty, NG::AlignStyle alignment) const
{
    auto layoutDirection = layoutProperty->GetNonAutoLayoutDirection();
    bool isRtl = layoutDirection == TextDirection::RTL;
    if (alignment == NG::AlignStyle::LEFT || (alignment == NG::AlignStyle::START && (!isRtl)) ||
        (alignment == NG::AlignStyle::END && isRtl)) {
        return true;
    } else {
        return false;
    }
}

float IndexerLayoutAlgorithm::GetMaxItemWidth(LayoutWrapper* layoutWrapper)
{
    auto indexerLayoutProperty = AceType::DynamicCast<IndexerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(indexerLayoutProperty, INDEXER_ZERO_WIDTH);
    auto childLayoutConstraint = indexerLayoutProperty->CreateChildConstraint();
    auto maxItemWidth = INDEXER_ZERO_WIDTH;
    auto childCount = layoutWrapper->GetTotalChildCount();
    if (indexerLayoutProperty->GetIsPopupValue(false)) {
        childCount--;
    }
    for (int32_t index = 0; index < childCount; index++) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        CHECK_NULL_RETURN(childWrapper, INDEXER_ZERO_WIDTH);
        childWrapper->Measure(childLayoutConstraint);
        auto node = childWrapper->GetGeometryNode();
        auto size = node->GetFrameSize();
        if (size.Width() > maxItemWidth) {
            maxItemWidth = size.Width();
        }
    }
    return maxItemWidth;
}

void IndexerLayoutAlgorithm::MeasurePopup(LayoutWrapper* layoutWrapper, uint32_t childCount)
{
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(childCount - 1);
    CHECK_NULL_VOID(childWrapper);
    auto childLayoutProperty = AceType::DynamicCast<LinearLayoutProperty>(childWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(childLayoutProperty);
    auto layoutConstraint = childLayoutProperty->GetLayoutConstraint();
    layoutConstraint->Reset();
    childWrapper->Measure(layoutConstraint);
}
} // namespace OHOS::Ace::NG
