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

#include "core/components_ng/pattern/badge/badge_layout_algorithm.h"

#include "core/components/badge/badge_theme.h"
#include "core/components_ng/pattern/badge/badge_layout_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float PERCENT_HALF = 0.5f;
const double AGE_FONT_SIZE_SCALE = 1.75;
} // namespace

void BadgeLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto children = host->GetChildren();
    if (children.empty()) {
        return;
    }
    auto childrenSize = children.size();
    auto layoutProperty = AceType::DynamicCast<BadgeLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();

    auto textFirstLayoutConstraint = childLayoutConstraint;
    textFirstLayoutConstraint.maxSize = { Infinity<float>(), Infinity<float>() };

    auto textWrapper = layoutWrapper->GetOrCreateChildByIndex(childrenSize - 1);
    CHECK_NULL_VOID(textWrapper);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(textWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(textLayoutProperty);
    auto textGeometryNode = textWrapper->GetGeometryNode();
    CHECK_NULL_VOID(textGeometryNode);

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();
    CHECK_NULL_VOID(badgeTheme);

    double fontSizeInit = 0.0;
    double badgeSizeInit = 0.0;
    auto fontSizeScale = pipeline->GetFontScale();
    auto isDefaultFontSize = layoutProperty->GetFontSizeIsDefault();
    auto isDefaultBadgeSize = layoutProperty->GetBadgeSizeIsDefault();
    auto badgeFontSize = layoutProperty->GetBadgeFontSize();
    auto badgeCircleSize = layoutProperty->GetBadgeCircleSize();

    if (badgeFontSize.has_value() && GreatOrEqual(badgeFontSize.value().ConvertToPx(), 0)) {
        hasFontSize_ = true;
    } else {
        hasFontSize_ = false;
    }

    if (fontSizeScale >= AGE_FONT_SIZE_SCALE) {
        if (isDefaultFontSize) {
            fontSizeInit = badgeTheme->GetBadgeAgeFontSize().ConvertToVp();
        } else {
            fontSizeInit = GetFontSizeInit(badgeFontSize);
        }

        if (isDefaultBadgeSize) {
            badgeSizeInit = badgeTheme->GetBadgeAgeCircleSize().ConvertToVp();
        } else {
            badgeSizeInit = GetBadgeSizeInit(badgeCircleSize);
        }
    } else {
        if (isDefaultFontSize) {
            fontSizeInit = badgeTheme->GetBadgeFontSize().ConvertToVp();
        } else {
            fontSizeInit = GetFontSizeInit(badgeFontSize);
        }

        if (isDefaultBadgeSize) {
            badgeSizeInit = badgeTheme->GetBadgeCircleSize().ConvertToVp();
        } else {
            badgeSizeInit = GetBadgeSizeInit(badgeCircleSize);
        }
    }
    
    if (layoutProperty->GetBadgeCount().has_value()) {
        textLayoutProperty->UpdateLayoutDirection(TextDirection::LTR);
    }
    textLayoutProperty->UpdateFontSize(Dimension(fontSizeInit, DimensionUnit::VP));
    auto circleSize = std::make_optional(Dimension(badgeSizeInit, DimensionUnit::VP));
    auto badgeCircleDiameter = Dimension(badgeSizeInit, DimensionUnit::VP).ConvertToPx();

    if (textWrapper) {
        textWrapper->Measure(textFirstLayoutConstraint);
    }

    auto badgeWidth = 0.0;
    auto badgeHeight = badgeCircleDiameter;
    auto countLimit =
        layoutProperty->HasBadgeMaxCount() ? layoutProperty->GetBadgeMaxCountValue() : badgeTheme->GetMaxCount();

    std::u16string textData;
    if (textLayoutProperty->HasContent()) {
        textData = textLayoutProperty->GetContentValue();
    }

    auto messageCount = textData.size();
    auto textSize = textGeometryNode->GetContentSize();
    if (!textData.empty() || messageCount > 0) {
        if ((textData.size() <= 1 && !textData.empty()) ||
            ((messageCount < 10 && messageCount <= static_cast<size_t>(countLimit)) && textData.empty())) {
            if (hasFontSize_) {
                badgeCircleDiameter = std::max(static_cast<double>(textSize.Height()), badgeCircleDiameter);
                badgeHeight = std::max(badgeCircleDiameter, badgeHeight);
            }
            badgeWidth = badgeCircleDiameter;
        } else if (textData.size() > 1 || messageCount > static_cast<size_t>(countLimit)) {
            if (hasFontSize_) {
                badgeCircleDiameter = std::max(static_cast<double>(textSize.Height()), badgeCircleDiameter);
                badgeHeight =
                    fontSizeScale >= AGE_FONT_SIZE_SCALE
                        ? std::max(badgeCircleDiameter, badgeHeight) + badgeTheme->GetBadgeAgeAddPadding().ConvertToVp()
                        : std::max(badgeCircleDiameter, badgeHeight);
            }
            badgeWidth = textSize.Width() + badgeTheme->GetNumericalBadgePadding().ConvertToPx() * 2;
            badgeWidth = badgeCircleDiameter > badgeWidth ? badgeCircleDiameter : badgeWidth;
        }
    }
    if (LessOrEqual(circleSize->ConvertToPx(), 0)) {
        badgeWidth = 0;
        badgeHeight = 0;
    }
    textLayoutProperty->UpdateMarginSelfIdealSize(SizeF(badgeWidth, badgeHeight));
    auto textLayoutConstraint = textFirstLayoutConstraint;
    textLayoutConstraint.selfIdealSize = OptionalSize<float>(badgeWidth, badgeHeight);

    textWrapper->Measure(textLayoutConstraint);
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(childrenSize - 2);
    CHECK_NULL_VOID(childWrapper);
    childWrapper->Measure(childLayoutConstraint);

    PerformMeasureSelf(layoutWrapper);
}

static OffsetF GetTextDataOffset(const RefPtr<BadgeLayoutProperty> layoutProperty, float badgeCircleDiameter,
                                 float badgeCircleRadius, const RefPtr<GeometryNode>& geometryNode, bool textIsSpace)
{
    auto offset = geometryNode->GetFrameOffset();
    auto parentSize = geometryNode->GetFrameSize();
    auto width = parentSize.Width();
    auto height = parentSize.Height();
    auto badgePosition = layoutProperty->GetBadgePosition();
    auto layoutDirection = layoutProperty->GetNonAutoLayoutDirection();
    OffsetF textOffset;
    if (badgePosition == BadgePosition::RIGHT_TOP) {
        if (layoutDirection == TextDirection::RTL) {
            textOffset = OffsetF(offset.GetX(), offset.GetY());
        } else {
            textOffset = OffsetF(offset.GetX() + width - badgeCircleDiameter, offset.GetY());
        }
        if (!textIsSpace) {
            textOffset += OffsetF(Dimension(2.0_vp).ConvertToPx(), -Dimension(2.0_vp).ConvertToPx());
        }
    } else if (badgePosition == BadgePosition::RIGHT) {
        if (layoutDirection == TextDirection::RTL) {
            textOffset = OffsetF(offset.GetX(), offset.GetY() + height * PERCENT_HALF - badgeCircleRadius);
        } else {
            textOffset = OffsetF(
                offset.GetX() + width - badgeCircleDiameter, offset.GetY() + height * PERCENT_HALF - badgeCircleRadius);
        }
    } else if (badgePosition == BadgePosition::LEFT) {
        if (layoutDirection == TextDirection::RTL) {
            textOffset = OffsetF(
                offset.GetX() + width - badgeCircleDiameter, offset.GetY() + height * PERCENT_HALF - badgeCircleRadius);
        } else {
            textOffset = OffsetF(offset.GetX(), offset.GetY() + height * PERCENT_HALF - badgeCircleRadius);
        }
    } else {
        textOffset = OffsetF(offset.GetX(), offset.GetY());
    }
    return textOffset;
}

static OffsetF GetTextOffsetByPosition(const RefPtr<BadgeLayoutProperty> layoutProperty,
                                       const RefPtr<GeometryNode>&geometryNode)
{
    auto offset = geometryNode->GetFrameOffset();
    auto badgePositionX = layoutProperty->GetBadgePositionX();
    auto badgePositionY = layoutProperty->GetBadgePositionY();
    OffsetF textOffset =
        OffsetF(offset.GetX() + badgePositionX->ConvertToPx(), offset.GetY() + badgePositionY->ConvertToPx());
    return textOffset;
}

void BadgeLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto children = host->GetChildren();
    if (children.empty()) {
        return;
    }
    auto childrenSize = children.size();

    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);

    auto layoutProperty = DynamicCast<BadgeLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();
    CHECK_NULL_VOID(badgeTheme);

    double badgeSizeInit;
    auto fontSizeScale = pipeline->GetFontScale();
    auto isDefaultBadgeSize = layoutProperty->GetBadgeSizeIsDefault();
    auto badgeCircleSize = layoutProperty->GetBadgeCircleSize();

    if (fontSizeScale >= AGE_FONT_SIZE_SCALE) {
        if (isDefaultBadgeSize) {
            badgeSizeInit = badgeTheme->GetBadgeAgeCircleSize().ConvertToVp();
        } else {
            badgeSizeInit = GetBadgeSizeInit(badgeCircleSize);
        }
    } else {
        if (isDefaultBadgeSize) {
            badgeSizeInit = badgeTheme->GetBadgeCircleSize().ConvertToVp();
        } else {
            badgeSizeInit = GetBadgeSizeInit(badgeCircleSize);
        }
    }

    auto circleSize = std::make_optional(Dimension(badgeSizeInit, DimensionUnit::VP));
    auto badgeCircleDiameter = Dimension(badgeSizeInit, DimensionUnit::VP).ConvertToPx();

    auto badgeWidth = 0.0;
    auto badgeCircleRadius = badgeCircleDiameter / 2;
    auto countLimit =
        layoutProperty->HasBadgeMaxCount() ? layoutProperty->GetBadgeMaxCountValue() : badgeTheme->GetMaxCount();

    auto textWrapper = layoutWrapper->GetOrCreateChildByIndex(childrenSize - 1);
    CHECK_NULL_VOID(textWrapper);
    auto textLayoutProperty = DynamicCast<TextLayoutProperty>(textWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(textLayoutProperty);
    auto textGeometryNode = textWrapper->GetGeometryNode();
    CHECK_NULL_VOID(textGeometryNode);

    std::u16string textData;
    if (textLayoutProperty->HasContent()) {
        textData = textLayoutProperty->GetContentValue();
    }

    auto messageCount = textData.size();
    auto textSize = textGeometryNode->GetContentSize();

    if (!textData.empty() || messageCount > 0) {
        if ((textData.size() <= 1 && !textData.empty()) ||
            ((messageCount < 10 && messageCount <= static_cast<size_t>(countLimit)) && textData.empty())) {
            if (hasFontSize_) {
                badgeCircleDiameter = std::max(static_cast<double>(textSize.Height()), badgeCircleDiameter);
            }
            badgeCircleRadius = badgeCircleDiameter / 2;
            badgeWidth = badgeCircleDiameter;
        } else if (textData.size() > 1 || messageCount > static_cast<size_t>(countLimit)) {
            if (hasFontSize_) {
                badgeCircleDiameter = std::max(static_cast<double>(textSize.Height()), badgeCircleDiameter);
            }
            badgeWidth = textSize.Width() + badgeTheme->GetNumericalBadgePadding().ConvertToPx() * 2;
            badgeWidth = badgeCircleDiameter > badgeWidth ? badgeCircleDiameter : badgeWidth;
            badgeCircleRadius = badgeCircleDiameter / 2;
        }
    }

    BorderRadiusProperty radius;
    auto borderWidth = layoutProperty->GetBadgeBorderWidthValue(badgeTheme->GetBadgeBorderWidth());
    OffsetF borderOffset(borderWidth.ConvertToPx(), borderWidth.ConvertToPx());
    radius.SetRadius(Dimension(badgeCircleRadius + borderWidth.ConvertToPx()));
    auto textFrameNode = textWrapper->GetHostNode();
    CHECK_NULL_VOID(textFrameNode);
    auto textRenderContext = textFrameNode->GetRenderContext();
    CHECK_NULL_VOID(textRenderContext);
    textRenderContext->UpdateBorderRadius(radius);

    textLayoutProperty->UpdateAlignment(Alignment::CENTER);

    OffsetF textOffset;
    if (layoutProperty->GetIsPositionXy().has_value() && !layoutProperty->GetIsPositionXy().value()) {
        textOffset = GetTextDataOffset(layoutProperty, badgeCircleDiameter, badgeCircleRadius,
            geometryNode, textData == u" ");
    } else {
        textOffset = GetTextOffsetByPosition(layoutProperty, geometryNode);
    }
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        textGeometryNode->SetMarginFrameOffset(textOffset - geometryNode->GetFrameOffset());
    } else {
        textGeometryNode->SetMarginFrameOffset(textOffset - geometryNode->GetFrameOffset() - borderOffset);
    }
    auto textFrameSize = textGeometryNode->GetFrameSize();
    if (GreatNotEqual(circleSize->ConvertToPx(), 0) && Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        textFrameSize += SizeF(borderWidth.ConvertToPx() * 2, borderWidth.ConvertToPx() * 2);
    }
    textGeometryNode->SetFrameSize(textFrameSize);
    textWrapper->Layout();

    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(childrenSize - 2);
    CHECK_NULL_VOID(childWrapper);
    auto childGeometryNode = childWrapper->GetGeometryNode();
    CHECK_NULL_VOID(childGeometryNode);
    // the child node needs to use its own margin
    auto layoutDirection = layoutWrapper->GetLayoutProperty()->GetNonAutoLayoutDirection();
    if (layoutDirection == TextDirection::RTL) {
        auto parentSize = geometryNode->GetFrameSize();
        auto width = parentSize.Width();
        auto childSize = childGeometryNode->GetMarginFrameSize();
        childGeometryNode->SetMarginFrameOffset(OffsetF(width - childSize.Width(), 0.0f));
    } else {
        childGeometryNode->SetMarginFrameOffset(OffsetF());
    }
    childWrapper->Layout();
}

void BadgeLayoutAlgorithm::PerformMeasureSelf(LayoutWrapper* layoutWrapper)
{
    const auto& layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    const auto& minSize = layoutConstraint->minSize;
    const auto& maxSize = layoutConstraint->maxSize;
    const auto& padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    OptionalSizeF frameSize;
    do {
        // Use idea size first if it is valid.
        frameSize.UpdateSizeWithCheck(layoutConstraint->selfIdealSize);
        if (frameSize.IsValid()) {
            break;
        }
        // use the last child size.
        auto host = layoutWrapper->GetHostNode();
        CHECK_NULL_VOID(host);
        auto children = host->GetChildren();
        auto childrenSize = children.size();
        auto childFrame =
            layoutWrapper->GetOrCreateChildByIndex(childrenSize - 2)->GetGeometryNode()->GetMarginFrameSize();
        AddPaddingToSize(padding, childFrame);
        frameSize.UpdateIllegalSizeWithCheck(childFrame);
        frameSize.Constrain(minSize, maxSize);
        frameSize.UpdateIllegalSizeWithCheck(SizeF { 0.0f, 0.0f });
    } while (false);

    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize.ConvertToSizeT());
}

} // namespace OHOS::Ace::NG
