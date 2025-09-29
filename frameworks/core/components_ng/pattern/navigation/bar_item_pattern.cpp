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

#include "base/utils/utf_helper.h"
#include "core/components_ng/pattern/navigation/bar_item_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {

void BarItemPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    CHECK_NULL_VOID(!clickListener_);
    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& /* info */) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto eventHub = pattern->GetEventHub<BarItemEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->FireItemAction();
        pattern->UpdateBarItemActiveStatusResource();
    };
    if (clickListener_) {
        gesture->RemoveClickEvent(clickListener_);
    }
    clickListener_ = MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gesture->AddClickEvent(clickListener_);
}

void UpdateSymbolDefaultEffect(RefPtr<TextLayoutProperty> symbolProperty, bool isActive)
{
    CHECK_NULL_VOID(symbolProperty);
    auto symbolEffectOptions = SymbolEffectOptions(SymbolEffectType::BOUNCE);
    symbolEffectOptions.SetIsTxtActive(isActive);
    symbolEffectOptions.SetIsTxtActiveSource(0);
    symbolProperty->UpdateSymbolEffectOptions(symbolEffectOptions);
}

void UpdateSymbolBarButton(const RefPtr<BarItemNode>& barItemNode, const RefPtr<FrameNode>& iconNode,
    const Color& iconColor, std::function<void(WeakPtr<NG::FrameNode>)>& symbol, ImageSourceInfo& info)
{
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    auto iconSize = theme->GetToolbarIconSize();
    if (symbol != nullptr) {
        // symbol -> symbol
        auto symbolProperty = iconNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(symbolProperty);
        symbolProperty->UpdateSymbolColorList({iconColor});
        // User-defined color overrides the default color of the theme
        symbol(AccessibilityManager::WeakClaim(AccessibilityManager::RawPtr(iconNode)));
        UpdateSymbolDefaultEffect(symbolProperty, false);
        symbolProperty->UpdateFontSize(iconSize);
        iconNode->MarkModifyDone();
        iconNode->MarkDirtyNode();
    } else {
        // symbol -> image
        barItemNode->RemoveChild(iconNode);
        auto iconNodeNew = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
        auto imageLayoutProperty = iconNodeNew->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        imageLayoutProperty->UpdateImageSourceInfo(info);
        imageLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(iconSize), CalcLength(iconSize)));
        iconNodeNew->MarkModifyDone();
        iconNodeNew->MarkDirtyNode();
        barItemNode->SetIconNode(iconNodeNew);
        barItemNode->AddChild(iconNodeNew);
    }
}

void UpdateImageBarButton(const RefPtr<BarItemNode>& barItemNode, const RefPtr<FrameNode>& iconNode,
    const Color& iconColor, std::function<void(WeakPtr<NG::FrameNode>)>& symbol, ImageSourceInfo& info)
{
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    auto iconSize = theme->GetToolbarIconSize();
    if (symbol != nullptr) {
        // image -> symbol
        barItemNode->RemoveChild(iconNode);
        auto iconNodeNew = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        CHECK_NULL_VOID(iconNodeNew);
        auto symbolProperty = iconNodeNew->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(symbolProperty);
        auto symbolEffectOptions = symbolProperty->GetSymbolEffectOptionsValue(SymbolEffectOptions());
        symbolEffectOptions.SetEffectType(SymbolEffectType::BOUNCE);
        symbolEffectOptions.SetIsTxtActive(true);
        symbolEffectOptions.SetIsTxtActiveSource(0);
        symbolProperty->UpdateSymbolEffectOptions(symbolEffectOptions);
        symbolProperty->UpdateSymbolColorList({ iconColor });
        symbol(AccessibilityManager::WeakClaim(AccessibilityManager::RawPtr(iconNodeNew)));
        symbolProperty->UpdateFontSize(iconSize);
        UpdateSymbolDefaultEffect(symbolProperty, false);
        iconNodeNew->MarkModifyDone();
        iconNodeNew->MarkDirtyNode();
        barItemNode->SetIconNode(iconNodeNew);
        barItemNode->AddChild(iconNodeNew);
    } else {
        // image -> image
        auto imageLayoutProperty = iconNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        imageLayoutProperty->UpdateImageSourceInfo(info);
        iconNode->MarkModifyDone();
        iconNode->MarkDirtyNode();
    }
}

void UpdateSymbolEffect(const RefPtr<FrameNode>& iconNode)
{
    auto symbolProperty = iconNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(symbolProperty);
    auto symbolEffectOptions = symbolProperty->GetSymbolEffectOptionsValue(SymbolEffectOptions());
    symbolEffectOptions.SetEffectType(SymbolEffectType::BOUNCE);
    symbolEffectOptions.SetIsTxtActive(true);
    symbolEffectOptions.SetIsTxtActiveSource(0);
    symbolProperty->UpdateSymbolEffectOptions(symbolEffectOptions);
    iconNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void BarItemPattern::UpdateBarItemTextAndIconStatusResource(const RefPtr<BarItemNode>& barItemNode,
    const RefPtr<FrameNode>& iconNode)
{
    CHECK_NULL_VOID(barItemNode);
    CHECK_NULL_VOID(iconNode);
    auto theme = GetNavigationBarTheme();
    CHECK_NULL_VOID(theme);
    ImageSourceInfo info;
    ToolbarIconStatus barIconStatus;
    Color textColor;
    Color iconColor;
    auto status = GetToolbarItemStatus();
    auto iconStatus = GetCurrentIconStatus();
    std::function<void(WeakPtr<NG::FrameNode>)> symbol;
    if (iconStatus == ToolbarIconStatus::INITIAL) {
        info = GetActiveIconImageSourceInfo();
        barIconStatus = ToolbarIconStatus::ACTIVE;
        textColor = theme->GetToolBarItemActiveFontColor();
        symbol = GetActiveIconSymbol();
        iconColor = theme->GetToolbarActiveIconColor();
    }
    if (iconStatus == ToolbarIconStatus::ACTIVE) {
        info = GetInitialIconImageSourceInfo();
        barIconStatus = ToolbarIconStatus::INITIAL;
        textColor = theme->GetToolBarItemFontColor();
        symbol = GetInitialIconSymbol();
        iconColor = theme->GetToolbarIconColor();
    }

    if (status == NavToolbarItemStatus::ACTIVE) {
        if (iconNode->GetTag() == V2::SYMBOL_ETS_TAG) {
            UpdateSymbolBarButton(barItemNode, iconNode, iconColor, symbol, info);
        } else {
            UpdateImageBarButton(barItemNode, iconNode, iconColor, symbol, info);
        }
        barItemNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        barItemNode->MarkDirtyNode();
        if (!barItemNode->IsHideText()) {
            auto textNode = DynamicCast<FrameNode>(barItemNode->GetTextNode());
            CHECK_NULL_VOID(textNode);
            auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
            CHECK_NULL_VOID(textLayoutProperty);
            textLayoutProperty->UpdateTextColor(textColor);
            textNode->MarkModifyDone();
            textNode->MarkDirtyNode();
        } else {
            if (barItemNode->GetTextNode()) {
                barItemNode->RemoveChild(barItemNode->GetTextNode());
            }
        }
        SetCurrentIconStatus(barIconStatus);
    }
}

void BarItemPattern::UpdateBarItemActiveStatusResource()
{
    auto barItemNode = AceType::DynamicCast<BarItemNode>(GetHost());
    CHECK_NULL_VOID(barItemNode);
    auto iconNode = DynamicCast<FrameNode>(barItemNode->GetIconNode());
    CHECK_NULL_VOID(iconNode);

    if (iconNode->GetTag() == V2::SYMBOL_ETS_TAG) {
        UpdateSymbolEffect(iconNode);
    }
    UpdateBarItemTextAndIconStatusResource(barItemNode, iconNode);
}

void BarItemPattern::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    Pattern::ToJsonValue(json, filter);
    
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }

    auto barItemNode = AceType::DynamicCast<BarItemNode>(GetHost());
    CHECK_NULL_VOID(barItemNode);
    auto textNode = AceType::DynamicCast<FrameNode>(barItemNode->GetTextNode());
    CHECK_NULL_VOID(textNode);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    json->PutExtAttr("label", (UtfUtils::Str16ToStr8(textLayoutProperty->GetContentValue(u""))).c_str(), filter);
}

bool BarItemPattern::OnThemeScopeUpdate(int32_t themeScopeId)
{
    auto theme = NavigationGetTheme(themeScopeId);
    CHECK_NULL_RETURN(theme, false);
    auto barItemNode = AceType::DynamicCast<BarItemNode>(GetHost());
    CHECK_NULL_RETURN(barItemNode, false);
    auto textNode = DynamicCast<FrameNode>(barItemNode->GetTextNode());
    CHECK_NULL_RETURN(textNode, false);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, false);
    auto iconNode = DynamicCast<FrameNode>(barItemNode->GetIconNode());
    CHECK_NULL_RETURN(iconNode, false);

    Color textColor;
    Color iconColor;
    auto iconStatus = GetCurrentIconStatus();
    if (iconStatus == ToolbarIconStatus::ACTIVE) {
        textColor = theme->GetToolBarItemActiveFontColor();
        iconColor = theme->GetToolbarActiveIconColor();
    }
    if (iconStatus == ToolbarIconStatus::INITIAL) {
        textColor = theme->GetToolBarItemFontColor();
        iconColor = theme->GetToolbarIconColor();
    }

    if (iconNode->GetTag() == V2::SYMBOL_ETS_TAG) {
        auto symbolProperty = iconNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_RETURN(symbolProperty, false);
        symbolProperty->UpdateSymbolColorList({ iconColor });
        iconNode->MarkDirtyNode();
    }

    textLayoutProperty->UpdateTextColor(textColor);
    textNode->MarkDirtyNode();

    return false;
}

RefPtr<NavigationBarTheme> BarItemPattern::GetNavigationBarTheme()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    return NavigationGetTheme(host->GetThemeScopeId());
}

} // namespace OHOS::Ace::NG
