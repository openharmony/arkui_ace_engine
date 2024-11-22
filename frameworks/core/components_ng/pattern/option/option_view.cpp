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
#include "core/components_ng/pattern/option/option_view.h"

#include "base/i18n/localization.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/option/option_row_pattern.h"
#include "core/components_ng/pattern/security_component/paste_button/paste_button_common.h"
#include "core/components_ng/pattern/security_component/paste_button/paste_button_model_ng.h"
#include "core/components_ng/pattern/security_component/security_component_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/image/image_source_info.h"

namespace OHOS::Ace::NG {

namespace {

RefPtr<FrameNode> Create(int32_t index)
{
    auto Id = ElementRegister::GetInstance()->MakeUniqueId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::OPTION_ETS_TAG, Id);
    auto node = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, Id, AceType::MakeRefPtr<MenuItemPattern>(true, index));

    // set border radius
    auto renderContext = node->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(theme, nullptr);
    BorderRadiusProperty border;
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        border.SetRadius(theme->GetMenuDefaultInnerRadius());
    } else {
        border.SetRadius(theme->GetInnerBorderRadius());
    }
    renderContext->UpdateBorderRadius(border);

    auto props = node->GetPaintProperty<OptionPaintProperty>();
    CHECK_NULL_RETURN(props, nullptr);
    props->UpdateHover(false);
    props->UpdatePress(false);
    return node;
}
} // namespace

RefPtr<FrameNode> OptionView::CreateText(const std::string& value, const RefPtr<FrameNode>& parent)
{
    // create child text node
    auto textId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, textId, AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textNode, nullptr);

    auto textProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textProperty, nullptr);

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(theme, nullptr);

    textProperty->UpdateMaxLines(1);
    textProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textProperty->UpdateFontSize(theme->GetMenuFontSize());
    textProperty->UpdateFontWeight(FontWeight::REGULAR);
    textProperty->UpdateTextColor(theme->GetMenuFontColor());
    // set default foregroundColor
    auto textRenderContext = textNode->GetRenderContext();
    textRenderContext->UpdateForegroundColor(theme->GetMenuFontColor());
    textProperty->UpdateContent(value);
    textNode->MountToParent(parent);
    textNode->MarkModifyDone();

    return textNode;
}

RefPtr<FrameNode> OptionView::CreateIcon(const std::string& icon, const RefPtr<FrameNode>& parent,
    const RefPtr<FrameNode>& child)
{
    auto iconNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    CHECK_NULL_RETURN(iconNode, nullptr);
    auto props = iconNode->GetLayoutProperty<ImageLayoutProperty>();
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(theme, nullptr);
    if (!icon.empty()) {
        ImageSourceInfo info(icon);
        props->UpdateImageSourceInfo(info);
    }
    props->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(theme->GetIconSideLength()), CalcLength(theme->GetIconSideLength())));
    props->UpdateAlignment(Alignment::CENTER_LEFT);

    if (child) {
        parent->ReplaceChild(child, iconNode);
    } else {
        iconNode->MountToParent(parent, 0);
    }
    iconNode->MarkModifyDone();
    return iconNode;
}

RefPtr<FrameNode> OptionView::CreateSymbol(const std::function<void(WeakPtr<NG::FrameNode>)>& symbolApply,
    const RefPtr<FrameNode>& parent, const RefPtr<FrameNode>& child,
    const std::optional<Dimension>& symbolUserDefinedIdealFontSize)
{
    auto iconNode = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    CHECK_NULL_RETURN(iconNode, nullptr);
    auto props = iconNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(props, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(theme, nullptr);
    props->UpdateFontSize(theme->GetEndIconWidth());
    props->UpdateSymbolColorList({theme->GetMenuIconColor()});
    props->UpdateAlignment(Alignment::CENTER_LEFT);
    MarginProperty margin;
    margin.right = CalcLength(theme->GetIconContentPadding());
    props->UpdateMargin(margin);
    if (symbolApply != nullptr) {
        symbolApply(AccessibilityManager::WeakClaim(AccessibilityManager::RawPtr(iconNode)));
    }
    if (symbolUserDefinedIdealFontSize.has_value()) {
        props->UpdateFontSize(symbolUserDefinedIdealFontSize.value());
    }
    if (child) {
        parent->ReplaceChild(child, iconNode);
    } else {
        iconNode->MountToParent(parent, 0);
    }
    iconNode->MarkModifyDone();
    return iconNode;
}

void OptionView::CreatePasteButton(bool optionsHasIcon, const RefPtr<FrameNode>& option, const RefPtr<FrameNode>& row,
    const std::function<void()>& onClickFunc, const std::string& icon)
{
    RefPtr<FrameNode> pasteNode;
    if (optionsHasIcon) {
        pasteNode =
            PasteButtonModelNG::GetInstance()->CreateNode(static_cast<int32_t>(PasteButtonPasteDescription::PASTE),
                static_cast<int32_t>(PasteButtonIconStyle::ICON_LINE), static_cast<int32_t>(ButtonType::NORMAL), true);
    } else {
        pasteNode =
            PasteButtonModelNG::GetInstance()->CreateNode(static_cast<int32_t>(PasteButtonPasteDescription::PASTE),
                static_cast<int32_t>(PasteButtonIconStyle::ICON_NULL), static_cast<int32_t>(ButtonType::NORMAL), true);
    }
    CHECK_NULL_VOID(pasteNode);
    auto pattern = option->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(pattern);

    auto pasteLayoutProperty = pasteNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    CHECK_NULL_VOID(pasteLayoutProperty);
    auto pastePaintProperty = pasteNode->GetPaintProperty<SecurityComponentPaintProperty>();
    CHECK_NULL_VOID(pastePaintProperty);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);

    pasteLayoutProperty->UpdateFontSize(theme->GetMenuFontSize());
    pasteLayoutProperty->UpdateFontWeight(FontWeight::REGULAR);
    pastePaintProperty->UpdateFontColor(theme->GetMenuFontColor());
    pastePaintProperty->UpdateBackgroundColor(Color::TRANSPARENT);
    pasteLayoutProperty->UpdateBackgroundBorderRadius(theme->GetInnerBorderRadius());
    pasteLayoutProperty->UpdateIconSize(theme->GetIconSideLength());
    pastePaintProperty->UpdateIconColor(theme->GetMenuIconColor());
    pasteLayoutProperty->UpdateStateEffect(false);
    pasteLayoutProperty->UpdateHoverEffect(HoverEffectType::NONE);
    if (optionsHasIcon) {
        pasteLayoutProperty->UpdateTextIconSpace(theme->GetIconContentPadding());
    }
    pasteNode->MountToParent(row);
    pasteNode->MarkModifyDone();

    row->MountToParent(option);
    row->MarkModifyDone();
    auto eventHub = option->GetEventHub<OptionEventHub>();
    CHECK_NULL_VOID(eventHub);
    pasteNode->GetOrCreateGestureEventHub()->SetUserOnClick([onClickFunc](GestureEvent& info) {
        if (!PasteButtonModelNG::GetInstance()->IsClickResultSuccess(info)) {
            return;
        }
        if (onClickFunc) {
            onClickFunc();
        }
    });
    pattern->SetPasteButton(pasteNode);
}

void OptionView::CreateOption(bool optionsHasIcon, std::vector<OptionParam>& params, int32_t index,
    const RefPtr<FrameNode>& row, const RefPtr<FrameNode>& option)
{
    auto pattern = option->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(pattern);
    if (optionsHasIcon) {
        auto iconNode = CreateSymbol(params[index].symbol, row, nullptr, params[index].symbolUserDefinedIdealFontSize);
        pattern->SetIconNode(iconNode);
    }
    auto textNode = CreateText(params[index].value, row);
    row->MountToParent(option);
    row->MarkModifyDone();
    pattern->SetTextNode(textNode);
    pattern->SetBlockClick(params[index].disableSystemClick);

    auto eventHub = option->GetEventHub<OptionEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetMenuOnClick(params[index].action);
}

void OptionView::CreateOption(bool optionsHasIcon, const std::string& value, const std::string& icon,
    const RefPtr<FrameNode>& row, const RefPtr<FrameNode>& option, const std::function<void()>& onClickFunc)
{
    auto pattern = option->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(pattern);
    if (optionsHasIcon) {
        auto iconNode = CreateIcon(icon, row);
        pattern->SetIconNode(iconNode);
        pattern->SetIcon(icon);
    }
    auto textNode = CreateText(value, row);
    row->MountToParent(option);
    row->MarkModifyDone();
    pattern->SetTextNode(textNode);

    auto eventHub = option->GetEventHub<OptionEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetMenuOnClick(onClickFunc);
}

RefPtr<FrameNode> OptionView::CreateMenuOption(bool optionsHasIcon, std::vector<OptionParam>& params, int32_t index)
{
    auto option = Create(index);
    CHECK_NULL_RETURN(option, nullptr);
    auto row = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<OptionRowPattern>());

#ifdef OHOS_PLATFORM
    constexpr char BUTTON_PASTE[] = "textoverlay.paste";
    if (params[index].value == Localization::GetInstance()->GetEntryLetters(BUTTON_PASTE)) {
        CreatePasteButton(optionsHasIcon, option, row, params[index].action);
    } else {
        CreateOption(optionsHasIcon, params, index, row, option);
    }
#else
    CreateOption(optionsHasIcon, params, index, row, option);
#endif
    return option;
}

RefPtr<FrameNode> OptionView::CreateMenuOption(bool optionsHasIcon, const OptionValueInfo& value,
    const std::function<void()>& onClickFunc, int32_t index, const std::string& icon)
{
    auto option = Create(index);
    CHECK_NULL_RETURN(option, nullptr);
    auto row = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<OptionRowPattern>());

#ifdef OHOS_PLATFORM
    constexpr char BUTTON_PASTE[] = "textoverlay.paste";
    if (value.value == Localization::GetInstance()->GetEntryLetters(BUTTON_PASTE)) {
        CreatePasteButton(optionsHasIcon, option, row, onClickFunc, icon);
    } else {
        CreateOption(optionsHasIcon, value.value, icon, row, option, onClickFunc);
    }
#else
    CreateOption(optionsHasIcon, value.value, icon, row, option, onClickFunc);
#endif
    return option;
}

RefPtr<FrameNode> OptionView::CreateSelectOption(const SelectParam& param, int32_t index)
{
    LOGI("create option value = %s", param.text.c_str());
    auto option = Create(index);
    auto row = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<OptionRowPattern>());
    row->MountToParent(option);

    auto pattern = option->GetPattern<MenuItemPattern>();
    CHECK_NULL_RETURN(pattern, option);
    // create icon node
    RefPtr<FrameNode> iconNode;
    if (param.symbolIcon != nullptr) {
        iconNode = CreateSymbol(param.symbolIcon, row);
    } else if (!param.icon.empty()) {
        iconNode = CreateIcon(param.icon, row);
        pattern->SetIcon(param.icon);
    }
    pattern->SetIconNode(iconNode);

    auto text = CreateText(param.text, row);
    pattern->SetTextNode(text);
    return option;
}

} // namespace OHOS::Ace::NG
