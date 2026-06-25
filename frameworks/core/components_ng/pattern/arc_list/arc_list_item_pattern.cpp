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

#include "core/components_ng/pattern/arc_list/arc_list_item_pattern.h"

#include "base/geometry/axis.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components/common/properties/color.h"
#include "core/components/list/arc_list_item_theme.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/pattern/arc_list/arc_list_item_layout_property.h"
#include "core/components_ng/pattern/arc_list/arc_list_pattern.h"
#include "core/components_ng/pattern/list/list_item_event_hub.h"
#include "core/components_ng/pattern/list/list_item_layout_algorithm.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {

FocusPattern ArcListItemPattern::GetFocusPattern() const
{
    if (listItemStyle_ == V2::ListItemStyle::CARD) {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, FocusPattern());
        auto listItemTheme = host->GetTheme<ArcListItemTheme>(true);
        CHECK_NULL_RETURN(listItemTheme, FocusPattern());
        FocusPaintParam paintParam;
        paintParam.SetPaintColor(listItemTheme->GetItemFocusBorderColor());
        paintParam.SetPaintWidth(listItemTheme->GetItemFocusBorderWidth());
        return { FocusType::SCOPE, true, FocusStyleType::INNER_BORDER, paintParam };
    }
    return { FocusType::SCOPE, true };
}

void ArcListItemPattern::ApplyListItemDefaultAttributes(const RefPtr<FrameNode>& listItemNode)
{
    auto renderContext = listItemNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto layoutProperty = listItemNode->GetLayoutProperty<ArcListItemLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto listItemTheme = host->GetTheme<ArcListItemTheme>(true);
    CHECK_NULL_VOID(listItemTheme);

    renderContext->UpdateBackgroundColor(listItemTheme->GetItemDefaultColor());

    PaddingProperty itemPadding;
    itemPadding.left = CalcLength(listItemTheme->GetItemDefaultLeftPadding());
    itemPadding.right = CalcLength(listItemTheme->GetItemDefaultRightPadding());
    layoutProperty->UpdatePadding(itemPadding);

    layoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(1.0, DimensionUnit::PERCENT), CalcLength(listItemTheme->GetItemDefaultHeight())));
    renderContext->UpdateBorderRadius(listItemTheme->GetItemDefaultBorderRadius());
    auto focusHub = listItemNode->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    std::unique_ptr<FocusPaintParam> paintParams = std::make_unique<FocusPaintParam>();
    paintParams->SetPaintColor(listItemTheme->GetItemFocusBorderColor());
    paintParams->SetPaintWidth(listItemTheme->GetItemFocusBorderWidth());
    focusHub->SetFocusPaintParamsPtr(paintParams);
}

bool ArcListItemPattern::OnThemeScopeUpdate(int32_t themeScopeId)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    if (listItemStyle_ != V2::ListItemStyle::CARD ||
        !host->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_SIX)) {
        return false;
    }
    auto layoutProperty = host->GetLayoutProperty<ArcListItemLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto listItemTheme = host->GetTheme<ArcListItemTheme>(true);
    CHECK_NULL_RETURN(listItemTheme, false);

    auto focusHub = host->GetFocusHub();
    if (focusHub) {
        std::unique_ptr<FocusPaintParam> paintParams = std::make_unique<FocusPaintParam>();
        paintParams->SetPaintColor(listItemTheme->GetItemFocusBorderColor());
        paintParams->SetPaintWidth(listItemTheme->GetItemFocusBorderWidth());
        focusHub->SetFocusPaintParamsPtr(paintParams);
    }

    auto renderContext = host->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    if (!layoutProperty->GetIsUserSetBackgroundColor()) {
        renderContext->UpdateBackgroundColor(listItemTheme->GetItemDefaultColor());
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    return false;
}

Color ArcListItemPattern::GetBlendGgColor()
{
    Color color = Color::TRANSPARENT;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, color);
    auto theme = host->GetTheme<ArcListItemTheme>(true);
    CHECK_NULL_RETURN(theme, color);
    if (isPressed_) {
        color = color.BlendColor(theme->GetItemPressColor());
    } else if (isHover_) {
        color = color.BlendColor(theme->GetItemHoverColor());
    }
    return color;
}

void ArcListItemPattern::HandleHoverEvent(bool isHover, const RefPtr<NG::FrameNode>& itemNode)
{
    auto renderContext = itemNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<ArcListItemTheme>();
    CHECK_NULL_VOID(theme);

    isHover_ = isHover;
    auto hoverColor = GetBlendGgColor();
    AnimationUtils::BlendBgColorAnimation(
        renderContext, hoverColor, theme->GetHoverAnimationDuration(), Curves::FRICTION);
}

void ArcListItemPattern::HandlePressEvent(bool isPressed, const RefPtr<NG::FrameNode>& itemNode)
{
    auto renderContext = itemNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<ArcListItemTheme>();
    CHECK_NULL_VOID(theme);
    auto duration = isHover_ ? theme->GetHoverToPressAnimationDuration() : theme->GetHoverAnimationDuration();
    isPressed_ = isPressed;
    Color color = GetBlendGgColor();
    AnimationUtils::BlendBgColorAnimation(renderContext, color, duration, Curves::SHARP);
}

void ArcListItemPattern::InitDisableEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<ListItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<ArcListItemTheme>();
    CHECK_NULL_VOID(theme);
    auto userDefineOpacity = renderContext->GetOpacityValue(1.0);
    auto disabledOpacity = theme->GetItemDisabledAlpha();

    if (!eventHub->IsDeveloperEnabled()) {
        if (!NearEqual(userDefineOpacity, disabledOpacity)) {
            enableOpacity_ = userDefineOpacity;
            renderContext->UpdateOpacity(disabledOpacity);
        }
    } else {
        if (enableOpacity_.has_value() && NearEqual(userDefineOpacity, disabledOpacity)) {
            renderContext->UpdateOpacity(enableOpacity_.value());
        }
        enableOpacity_.reset();
    }
}

} // namespace OHOS::Ace::NG
