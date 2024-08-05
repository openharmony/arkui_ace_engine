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

#include "core/components_ng/pattern/search/search_overlay_modifier.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/search/search_pattern.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
SearchOverlayModifier::SearchOverlayModifier(const WeakPtr<OHOS::Ace::NG::Pattern>& pattern, const SizeF& buttonSize)
    : pattern_(pattern), buttonSize_(buttonSize)
{
    InitModifierProperty();
    AttachModifierProperty();
}

void SearchOverlayModifier::SetDividerHorizontalOffset(float value)
{
    dividerHorizontalOffset_->Set(value);
}

void SearchOverlayModifier::SetDividerVerticalOffset(float value)
{
    dividerVerticalOffset_->Set(value);
}

void SearchOverlayModifier::SetDividerHeight(float value)
{
    dividerHeight_->Set(value);
}

void SearchOverlayModifier::SetIsSearchButtonEnabled(bool value)
{
    isSearchButtonEnabled_->Set(value);
}

void SearchOverlayModifier::SetSearchDividerColor(Color value)
{
    searchDividerColor_->Set(value);
}

void SearchOverlayModifier::SetSearchDividerWidth(double value)
{
    searchDividerWidth_ = value;
}

void SearchOverlayModifier::InitModifierProperty()
{
    auto searchPattern = DynamicCast<SearchPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(searchPattern);
    auto host = searchPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto isRTL = layoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto searchTheme = pipeline->GetTheme<SearchTheme>();
    CHECK_NULL_VOID(searchTheme);

    auto [iconHeight, dividerSpace, searchSpace, searchDividerWidth, searchDividerColor] =
        GetThemeAttributes(searchTheme);
    auto searchSize = host->GetGeometryNode()->GetFrameSize();
    auto [rightOffset, leftOffset, topPadding, bottomPadding] = GetPaddingOffsets();

    SearchDividerOffsetsParams params = { isRTL, searchSize, iconHeight, dividerSpace, searchSpace, searchDividerWidth,
        rightOffset, leftOffset, topPadding, bottomPadding };
    auto [dividerHorizontalOffset, dividerVerticalOffset, dividerHeight] = CalculateDividerOffsets(params);

    dividerHorizontalOffset_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(dividerHorizontalOffset);
    dividerVerticalOffset_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(dividerVerticalOffset);
    dividerHeight_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(dividerHeight);
    auto isSearchButtonEnabled = searchPattern->GetIsSearchButtonEnabled();
    isSearchButtonEnabled_ = AceType::MakeRefPtr<PropertyBool>(isSearchButtonEnabled);
    searchDividerColor_ = AceType::MakeRefPtr<PropertyColor>(searchDividerColor);
    SetSearchDividerWidth(searchDividerWidth);
}

void SearchOverlayModifier::AttachModifierProperty()
{
    AttachProperty(dividerHorizontalOffset_);
    AttachProperty(dividerVerticalOffset_);
    AttachProperty(dividerHeight_);
    AttachProperty(isSearchButtonEnabled_);
    AttachProperty(searchDividerColor_);
}

std::tuple<OHOS::Ace::Dimension, double, double, double, OHOS::Ace::Color> SearchOverlayModifier::GetThemeAttributes(
    const RefPtr<OHOS::Ace::SearchTheme>& searchTheme) const
{
    OHOS::Ace::Dimension iconHeight = searchTheme->GetIconHeight();
    auto dividerSpace = searchTheme->GetDividerSideSpace().ConvertToPx();
    auto searchSpace = searchTheme->GetSearchButtonSpace().ConvertToPx();
    auto searchDividerWidth = searchTheme->GetSearchDividerWidth().ConvertToPx();
    OHOS::Ace::Color searchDividerColor = searchTheme->GetSearchDividerColor();
    return { iconHeight, dividerSpace, searchSpace, searchDividerWidth, searchDividerColor };
}

std::tuple<float, float, float, float> SearchOverlayModifier::GetPaddingOffsets() const
{
    auto rightOffset = 0.0f;
    auto leftOffset = 0.0f;
    auto topPadding = 0.0f;
    auto bottomPadding = 0.0f;
    auto searchPattern = DynamicCast<SearchPattern>(pattern_.Upgrade());
    if (!searchPattern) {
        return { rightOffset, leftOffset, topPadding, bottomPadding };
    }

    auto host = searchPattern->GetHost();
    if (!host) {
        return { rightOffset, leftOffset, topPadding, bottomPadding };
    }

    const auto& padding = host->GetGeometryNode()->GetPadding();
    if (padding) {
        rightOffset = padding->right.value_or(0.0f);
        topPadding = padding->top.value_or(0.0f);
        bottomPadding = padding->bottom.value_or(0.0f);
        leftOffset = padding->left.value_or(0.0f);
    }
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        rightOffset = 0.0f;
    }
    return { rightOffset, leftOffset, topPadding, bottomPadding };
}

std::tuple<float, float, float> SearchOverlayModifier::CalculateDividerOffsets(
    const SearchDividerOffsetsParams& params) const
{
    auto dividerVerticalOffset = (params.searchSize.Height() - params.iconHeight.ConvertToPx()) / 2.0f;
    auto dividerHorizontalOffset = 0.0f;
    if (params.isRTL) {
        dividerHorizontalOffset = params.leftOffset + buttonSize_.Width() + params.dividerSpace + params.searchSpace +
                                  params.searchDividerWidth / 2.0f;
    } else {
        dividerHorizontalOffset = params.searchSize.Width() - buttonSize_.Width() - params.dividerSpace -
                                  params.searchSpace - params.searchDividerWidth / 2.0f - params.rightOffset;
    }
    dividerHorizontalOffset = std::max(dividerHorizontalOffset, 0.0f);
    auto dividerHeight = std::min(params.searchSize.Height() - params.topPadding - params.bottomPadding,
        static_cast<float>(params.iconHeight.ConvertToPx()));
    dividerVerticalOffset = params.topPadding;
    if (NearEqual(params.iconHeight.ConvertToPx(), dividerHeight)) {
        auto dividerInterval = (params.searchSize.Height() - params.iconHeight.ConvertToPx()) / 2.0f;
        if (params.topPadding <= dividerInterval && params.bottomPadding <= dividerInterval) {
            dividerVerticalOffset = dividerInterval;
        } else if (params.topPadding <= dividerInterval && params.bottomPadding > dividerInterval) {
            dividerVerticalOffset = params.searchSize.Height() - (params.bottomPadding + dividerHeight);
        }
    }
    return { dividerHorizontalOffset, dividerVerticalOffset, dividerHeight };
}

void SearchOverlayModifier::onDraw(DrawingContext& drawingContext)
{
    DrawDivider(drawingContext);
}

void SearchOverlayModifier::DrawDivider(DrawingContext& drawingContext)
{
    if (!isSearchButtonEnabled_->Get()) {
        return;
    }

    auto dividerHorizontalOffset = dividerHorizontalOffset_->Get();
    auto dividerVerticalOffset = dividerVerticalOffset_->Get();
    auto dividerHeight = dividerHeight_->Get();
    auto searchDividerColor = searchDividerColor_->Get();

    // DrawDivider logic inlined here
    RSRect rect(dividerHorizontalOffset, dividerVerticalOffset, dividerHorizontalOffset + searchDividerWidth_,
        dividerVerticalOffset + dividerHeight);
    auto& canvas = drawingContext.canvas;
    canvas.Save();
    RSPen pen;
    pen.SetWidth(searchDividerWidth_);
    pen.SetColor(ToRSColor(searchDividerColor));
    canvas.AttachPen(pen);
    canvas.DrawRect(rect);
    canvas.DetachPen();
    canvas.Restore();
}
} // namespace OHOS::Ace::NG