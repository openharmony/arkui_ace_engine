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

#include "core/components_ng/pattern/select_overlay/select_overlay_node.h"

#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <securec.h>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/i18n/localization.h"
#include "base/utils/utils.h"
#include "core/animation/curves.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/placement.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/relative_container/relative_container_pattern.h"
#include "core/components_ng/pattern/security_component/paste_button/paste_button_common.h"
#include "core/components_ng/pattern/security_component/paste_button/paste_button_model_ng.h"
#include "core/components_ng/pattern/security_component/security_component_pattern.h"
#include "core/components_ng/pattern/select_content_overlay/select_content_overlay_pattern.h"
#include "core/components_ng/pattern/select_overlay/expanded_menu_plugin_loader.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_event_hub.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/pattern/symbol/symbol_model_ng.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/calc_length.h"
#ifdef ENABLE_ROSEN_BACKEND
#include "core/components/custom_paint/rosen_render_custom_paint.h"
#endif
#include "frameworks/base/utils/measure_util.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t OPTION_INDEX_CUT = 0;
constexpr int32_t OPTION_INDEX_COPY = 1;
constexpr int32_t OPTION_INDEX_PASTE = 2;
constexpr int32_t OPTION_INDEX_COPY_ALL = 3;
constexpr int32_t OPTION_INDEX_TRANSLATE = 4;
constexpr int32_t OPTION_INDEX_SEARCH = 5;
constexpr int32_t OPTION_INDEX_SHARE = 6;
constexpr int32_t OPTION_INDEX_CAMERA_INPUT = 7;
constexpr int32_t OPTION_INDEX_AI_WRITE = 8;
constexpr int32_t OPTION_INDEX_AI_MENU = 9;
constexpr int32_t ANIMATION_DURATION1 = 350;
constexpr int32_t ANIMATION_DURATION2 = 150;
constexpr int32_t SYMBOL_ANIMATION_DELAY = 50;

constexpr Dimension MORE_MENU_TRANSLATE = -7.5_vp;
constexpr Dimension MAX_DIAMETER = 3.5_vp;
constexpr Dimension MIN_DIAMETER = 1.5_vp;
constexpr Dimension MIN_ARROWHEAD_DIAMETER = 2.0_vp;
constexpr Dimension ANIMATION_TEXT_OFFSET = 12.0_vp;
constexpr Dimension OVERLAY_MAX_WIDTH = 280.0_vp;
constexpr Dimension MIN_HOTSPOT_WIDTH = 40.0_vp;
constexpr float AGING_MIN_SCALE = 1.75f;

std::unordered_map<TextDataDetectType, std::pair<std::string, std::function<bool()>>> AI_TYPE_ID_MAP = {
    { TextDataDetectType::PHONE_NUMBER, std::make_pair(OH_DEFAULT_AI_MENU_PHONE, &TextSystemMenu::IsShowAIPhone) },
    { TextDataDetectType::URL, std::make_pair(OH_DEFAULT_AI_MENU_URL, &TextSystemMenu::IsShowAIUrl) },
    { TextDataDetectType::EMAIL, std::make_pair(OH_DEFAULT_AI_MENU_EMAIL, &TextSystemMenu::IsShowAIEmail) },
    { TextDataDetectType::ADDRESS, std::make_pair(OH_DEFAULT_AI_MENU_ADDRESS, &TextSystemMenu::IsShowAIAddress) },
    { TextDataDetectType::DATE_TIME, std::make_pair(OH_DEFAULT_AI_MENU_DATETIME, &TextSystemMenu::IsShowAIDatetime) },
};

bool IsAIMenuOption(const std::string& id)
{
    return id == OH_DEFAULT_AI_MENU_PHONE || id == OH_DEFAULT_AI_MENU_URL || id == OH_DEFAULT_AI_MENU_EMAIL ||
            id == OH_DEFAULT_AI_MENU_ADDRESS || id == OH_DEFAULT_AI_MENU_DATETIME;
}

bool IsShowAIMenuOption(OHOS::Ace::TextDataDetectType type)
{
    auto isShowAIMenu = type != TextDataDetectType::INVALID;
    auto findIter = AI_TYPE_ID_MAP.find(type);
    isShowAIMenu = isShowAIMenu && (findIter != AI_TYPE_ID_MAP.end()) && findIter->second.second();
    return isShowAIMenu;
}

const std::unordered_map<std::string, std::function<bool(const SelectMenuInfo&)>> isMenuItemEnabledFuncMap = {
    { OH_DEFAULT_CUT, [](const SelectMenuInfo& info){ return info.showCut; } },
    { OH_DEFAULT_COPY, [](const SelectMenuInfo& info){ return info.showCopy; } },
    { OH_DEFAULT_SELECT_ALL, [](const SelectMenuInfo& info){ return info.showCopyAll; } },
    { OH_DEFAULT_PASTE, [](const SelectMenuInfo& info){ return info.showPaste; } },
    { OH_DEFAULT_TRANSLATE, [](const SelectMenuInfo& info){ return info.showTranslate; } },
    { OH_DEFAULT_SEARCH, [](const SelectMenuInfo& info){ return info.showSearch; } },
    { OH_DEFAULT_SHARE, [](const SelectMenuInfo& info){ return info.showShare; } },
    { OH_DEFAULT_AI_WRITE, [](const SelectMenuInfo& info){ return info.showAIWrite; } }
};

const std::unordered_map<std::string, std::function<uint32_t(RefPtr<OHOS::Ace::TextOverlayTheme>)>> getSymbolIdMap = {
    { OH_DEFAULT_CUT,
        [](const RefPtr<OHOS::Ace::TextOverlayTheme>& textOverlayTheme) { return textOverlayTheme->GetCutSymbolId();}
    },
    { OH_DEFAULT_COPY,
        [](const RefPtr<OHOS::Ace::TextOverlayTheme>& textOverlayTheme) { return textOverlayTheme->GetCopySymbolId();}
    },
    { OH_DEFAULT_SELECT_ALL, [](const RefPtr<OHOS::Ace::TextOverlayTheme>& textOverlayTheme)
        { return textOverlayTheme->GetCopyAllSymbolId();}
    },
    { OH_DEFAULT_PASTE,
        [](const RefPtr<OHOS::Ace::TextOverlayTheme>& textOverlayTheme) { return textOverlayTheme->GetPasteSymbolId();}
    },
    { OH_DEFAULT_CAMERA_INPUT, [](const RefPtr<OHOS::Ace::TextOverlayTheme>& textOverlayTheme)
        { return textOverlayTheme->GetCameraInputSymbolId();}
    },
    { OH_DEFAULT_AI_WRITE, [](const RefPtr<OHOS::Ace::TextOverlayTheme>& textOverlayTheme)
        { return textOverlayTheme->GetAIWriteSymbolId();}
    },
    { OH_DEFAULT_SEARCH, [](const RefPtr<OHOS::Ace::TextOverlayTheme>& textOverlayTheme)
        { return textOverlayTheme->GetSearchSymbolId();}
    },
    { OH_DEFAULT_TRANSLATE, [](const RefPtr<OHOS::Ace::TextOverlayTheme>& textOverlayTheme)
        { return textOverlayTheme->GetTranslateSymbolId();}
    },
    { OH_DEFAULT_AI_MENU_PHONE, [](const RefPtr<OHOS::Ace::TextOverlayTheme>& textOverlayTheme)
        { return textOverlayTheme->GetAIMenuSymbolId();}
    },
    { OH_DEFAULT_AI_MENU_URL, [](const RefPtr<OHOS::Ace::TextOverlayTheme>& textOverlayTheme)
        { return textOverlayTheme->GetAIMenuSymbolId();}
    },
    { OH_DEFAULT_AI_MENU_EMAIL, [](const RefPtr<OHOS::Ace::TextOverlayTheme>& textOverlayTheme)
        { return textOverlayTheme->GetAIMenuSymbolId();}
    },
    { OH_DEFAULT_AI_MENU_ADDRESS, [](const RefPtr<OHOS::Ace::TextOverlayTheme>& textOverlayTheme)
        { return textOverlayTheme->GetAIMenuSymbolId();}
    },
    { OH_DEFAULT_AI_MENU_DATETIME, [](const RefPtr<OHOS::Ace::TextOverlayTheme>& textOverlayTheme)
        { return textOverlayTheme->GetAIMenuSymbolId();}
    }
};

enum class SelectOverlayMenuButtonType {
    NORMAL,
    AIBUTTON
};

void SetMoreOrBackButtonResponse(RefPtr<FrameNode>& node)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    if (GreatOrEqual(pipeline->GetFontScale(), AGING_MIN_SCALE)) {
        return;
    }
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(textOverlayTheme);
    auto gestureHub = node->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    std::vector<DimensionRect> vector;
    auto menuPadding = textOverlayTheme->GetMenuPadding();
    auto buttonWidth = textOverlayTheme->GetMenuButtonWidth();
    auto top = menuPadding.Top();
    auto responseHeight = top.Value() + menuPadding.Bottom().Value() + textOverlayTheme->GetMenuButtonHeight().Value();
    auto responseWidth = std::max(buttonWidth, MIN_HOTSPOT_WIDTH);
    constexpr int32_t centerDivider = 2;
    vector.emplace_back(DimensionRect(responseWidth, Dimension(responseHeight, DimensionUnit::VP),
        DimensionOffset(
            Dimension(-(responseWidth - buttonWidth) / centerDivider), Dimension(-top.Value(), top.Unit()))));
    gestureHub->SetResponseRegion(vector);
}

void SetResponseRegion(RefPtr<FrameNode>& node)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    if (GreatOrEqual(pipeline->GetFontScale(), AGING_MIN_SCALE)) {
        return;
    }
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(textOverlayTheme);
    auto gestureHub = node->GetOrCreateGestureEventHub();
    std::vector<DimensionRect> vector;
    auto menuPadding = textOverlayTheme->GetMenuPadding();
    auto buttonHeight = textOverlayTheme->GetMenuButtonHeight();
    auto top = menuPadding.Top();
    auto responseHeight = top.Value() + menuPadding.Bottom().Value() + buttonHeight.Value();
    vector.emplace_back(
        DimensionRect(Dimension(1, DimensionUnit::PERCENT), Dimension(responseHeight, DimensionUnit::VP),
            DimensionOffset(Dimension(0), Dimension(-top.Value(), top.Unit()))));
    gestureHub->SetResponseRegion(vector);
}

#ifdef OHOS_PLATFORM
RefPtr<FrameNode> BuildPasteButton(
    const std::function<void()>& callback, int32_t overlayId, float& buttonWidth, bool isSelectAll = false)
{
    auto descriptionId = static_cast<int32_t>(PasteButtonPasteDescription::PASTE);
    auto pasteButton = PasteButtonModelNG::GetInstance()->CreateNode(descriptionId,
        static_cast<int32_t>(PasteButtonIconStyle::ICON_NULL), static_cast<int32_t>(ButtonType::CAPSULE),
        true, static_cast<int32_t>(PasteButtonIconStyle::ICON_NULL));
    CHECK_NULL_RETURN(pasteButton, nullptr);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, pasteButton);
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_RETURN(textOverlayTheme, pasteButton);
    auto textStyle = textOverlayTheme->GetMenuButtonTextStyle();

    auto buttonLayoutProperty = pasteButton->GetLayoutProperty<SecurityComponentLayoutProperty>();
    buttonLayoutProperty->UpdateFontSize(textStyle.GetFontSize());
    buttonLayoutProperty->UpdateFontWeight(textStyle.GetFontWeight());

    auto buttonPaintProperty = pasteButton->GetPaintProperty<SecurityComponentPaintProperty>();
    const auto& padding = textOverlayTheme->GetMenuButtonPadding();
    buttonLayoutProperty->UpdateBackgroundLeftPadding(padding.Left());
    buttonLayoutProperty->UpdateBackgroundRightPadding(padding.Right());
    std::string buttonContent;
    PasteButtonModelNG::GetInstance()->GetTextResource(descriptionId, buttonContent);
    buttonWidth = MeasureUtil::MeasureTextWidth(textStyle, buttonContent);
    buttonWidth = buttonWidth + padding.Left().ConvertToPx() + padding.Right().ConvertToPx();
    if (GreatOrEqual(pipeline->GetFontScale(), AGING_MIN_SCALE)) {
        buttonLayoutProperty->UpdateUserDefinedIdealSize({ CalcLength(buttonWidth), std::nullopt });
    } else {
        buttonLayoutProperty->UpdateUserDefinedIdealSize(
            { CalcLength(buttonWidth), CalcLength(textOverlayTheme->GetMenuButtonHeight()) });
    }
    buttonPaintProperty->UpdateBackgroundColor(Color::TRANSPARENT);
    if (callback) {
        buttonPaintProperty->UpdateFontColor(textStyle.GetTextColor());
        auto id = Container::CurrentIdSafelyWithCheck();
        pasteButton->GetOrCreateGestureEventHub()->SetUserOnClick([callback, id](GestureEvent& info) {
            ContainerScope scope(id);
            if (!PasteButtonModelNG::GetInstance()->IsClickResultSuccess(info)) {
                return;
            }
            if (callback) {
                callback();
            }
        });
    } else {
        buttonPaintProperty->UpdateFontColor(
            textStyle.GetTextColor().BlendOpacity(textOverlayTheme->GetAlphaDisabled()));
        auto buttonEventHub = pasteButton->GetOrCreateEventHub<MenuItemEventHub>();
        CHECK_NULL_RETURN(buttonEventHub, pasteButton);
        buttonEventHub->SetEnabled(false);
    }
    SetResponseRegion(pasteButton);
    pasteButton->MarkModifyDone();
    return pasteButton;
}

RefPtr<FrameNode> CreatePasteButtonForCreateMenu(
    const std::shared_ptr<SelectOverlayInfo>& info, int32_t overlayId, const MenuOptionsParam& item, float& buttonWidth)
{
    auto id = Container::CurrentIdSafelyWithCheck();
    auto onPaste = [onPaste = info->menuCallback.onPaste, onCreateCallback = info->onCreateCallback,
                       menuOptionsParam = item, id]() {
        ContainerScope scope(id);
        bool result = false;
        if (onCreateCallback.onMenuItemClick) {
            MenuItemParam menuItem;
            menuItem.menuOptionsParam = menuOptionsParam;
            int32_t start = -1;
            int32_t end = -1;
            if (onCreateCallback.textRangeCallback) {
                onCreateCallback.textRangeCallback(start, end);
            }
            menuItem.start = start;
            menuItem.end = end;
            result = onCreateCallback.onMenuItemClick(menuItem);
        }
        if (!result && onPaste) {
            onPaste();
        }
    };
    auto button = BuildPasteButton(onPaste, overlayId, buttonWidth);
    return button;
}
#endif

bool PrepareButtonTextProp(RefPtr<OHOS::Ace::NG::TextLayoutProperty>& textLayoutProperty,
                           bool hasCallback, float& buttonWidth, const std::string& data,
                           SelectOverlayMenuButtonType buttonType = SelectOverlayMenuButtonType::NORMAL)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, false);
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_RETURN(textOverlayTheme, false);
    auto textStyle = textOverlayTheme->GetMenuButtonTextStyle();
    textLayoutProperty->UpdateFontSize(textStyle.GetFontSize());
    textLayoutProperty->UpdateFontWeight(textStyle.GetFontWeight());
    textLayoutProperty->UpdateMaxLines(1);
    if (hasCallback) {
        textLayoutProperty->UpdateTextColor(textStyle.GetTextColor());
    } else {
        textLayoutProperty->UpdateTextColor(
            textStyle.GetTextColor().BlendOpacity(textOverlayTheme->GetAlphaDisabled()));
    }
    auto textSize = MeasureUtil::MeasureTextSize(textStyle, data);
    buttonWidth = std::max(static_cast<float>(textSize.Width()), 0.0f);
    if (buttonType == SelectOverlayMenuButtonType::AIBUTTON) {
        FontForegroudGradiantColor colorInfo;
        colorInfo.points = { NG::PointF(0, 0),
            NG::PointF(static_cast<float>(textSize.Width()), static_cast<float>(textSize.Height())) };
        colorInfo.colors = textOverlayTheme->GetAiMenuFontGradientColors();
        colorInfo.scalars = textOverlayTheme->GetAiMenuFontGradientScalars();
        textLayoutProperty->UpdateFontForegroudGradiantColor(colorInfo);
    }
    return true;
}

bool PrepareButtonProp(RefPtr<OHOS::Ace::NG::ButtonLayoutProperty>& buttonLayoutProperty,
                       float& buttonWidth, const RefPtr<OHOS::Ace::NG::FrameNode>& buttonNode)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, false);
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_RETURN(textOverlayTheme, false);
    if (buttonNode->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        buttonLayoutProperty->UpdateType(ButtonType::ROUNDED_RECTANGLE);
    } else {
        buttonLayoutProperty->UpdateType(ButtonType::CAPSULE);
    }
    const auto& padding = textOverlayTheme->GetMenuButtonPadding();
    auto left = CalcLength(padding.Left().ConvertToPx());
    auto right = CalcLength(padding.Right().ConvertToPx());
    auto top = CalcLength(padding.Top().ConvertToPx());
    auto bottom = CalcLength(padding.Bottom().ConvertToPx());
    buttonLayoutProperty->UpdatePadding({ left, right, top, bottom, std::nullopt, std::nullopt });
    // Calculate the width of default option include button padding.
    buttonWidth = buttonWidth + padding.Left().ConvertToPx() + padding.Right().ConvertToPx();
    if (GreatOrEqual(pipeline->GetFontScale(), AGING_MIN_SCALE)) {
        buttonLayoutProperty->UpdateUserDefinedIdealSize({ CalcLength(buttonWidth), std::nullopt });
    } else {
        buttonLayoutProperty->UpdateUserDefinedIdealSize(
            { CalcLength(buttonWidth), CalcLength(textOverlayTheme->GetMenuButtonHeight()) });
    }
    buttonLayoutProperty->UpdateFlexShrink(0);
    return true;
}

RefPtr<FrameNode> BuildButton(const std::string& data, std::variant<const std::function<void()>,
    const std::function<void(std::string)>> callbackVariant, int32_t overlayId, float& buttonWidth,
    SelectOverlayMenuButtonType buttonType = SelectOverlayMenuButtonType::NORMAL)
{
    auto button = FrameNode::GetOrCreateFrameNode("SelectMenuButton", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto text = FrameNode::GetOrCreateFrameNode("SelectMenuButtonText", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto textLayoutProperty = text->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, button);
    textLayoutProperty->UpdateContent(data);
    text->MountToParent(button);
    auto hasCallback = false;
    if ((std::holds_alternative<const std::function<void()>>(callbackVariant) &&
         std::get<const std::function<void()>>(callbackVariant)) ||
        (std::holds_alternative<const std::function<void(std::string)>>(callbackVariant) &&
         std::get<const std::function<void(std::string)>>(callbackVariant))) {
        hasCallback = true;
    }

    auto retPrepare = PrepareButtonTextProp(textLayoutProperty, hasCallback, buttonWidth, data, buttonType);
    CHECK_NE_RETURN(retPrepare, true, button);
    text->MarkModifyDone();

    auto buttonLayoutProperty = button->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_RETURN(buttonLayoutProperty, button);
    retPrepare = PrepareButtonProp(buttonLayoutProperty, buttonWidth, button);
    CHECK_NE_RETURN(retPrepare, true, button);

    button->GetRenderContext()->UpdateBackgroundColor(Color::TRANSPARENT);

    if (hasCallback) {
        button->GetOrCreateGestureEventHub()->SetUserOnClick(
            [lableInfo = data, callbackVariant, overlayId,
             id = Container::CurrentIdSafelyWithCheck(), buttonType = buttonType]
                (GestureEvent& /* info */) {
                ContainerScope scope(id);
                auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
                CHECK_NULL_VOID(pipeline);
                auto overlayManager = pipeline->GetSelectOverlayManager();
                CHECK_NULL_VOID(overlayManager);
                auto selectOverlay = overlayManager->GetSelectOverlayNode(overlayId);
                CHECK_NULL_VOID(selectOverlay);
                auto isDoingAnimation = selectOverlay->GetAnimationStatus();
                CHECK_NULL_VOID(!isDoingAnimation);
                auto isExtensionMenu = selectOverlay->GetIsExtensionMenu();
                CHECK_NULL_VOID(!isExtensionMenu);
                if (std::holds_alternative<const std::function<void()>>(callbackVariant) &&
                    std::get<const std::function<void()>>(callbackVariant)) {
                    std::get<const std::function<void()>>(callbackVariant)();
                } else if (std::holds_alternative<const std::function<void(std::string)>>(callbackVariant) &&
                    std::get<const std::function<void(std::string)>>(callbackVariant)) {
                    std::get<const std::function<void(std::string)>>(callbackVariant)(lableInfo);
                }
            });
    } else {
        auto buttonEventHub = button->GetOrCreateEventHub<MenuItemEventHub>();
        CHECK_NULL_RETURN(buttonEventHub, button);
        buttonEventHub->SetEnabled(false);
    }
    SetResponseRegion(button);
    button->MarkModifyDone();
    return button;
}

void BindButtonClickEvent(const RefPtr<FrameNode>& button, const MenuOptionsParam& menuOption, int32_t overlayId)
{
    auto callback = menuOption.action;
    auto id = Container::CurrentIdSafelyWithCheck();
    button->GetOrCreateGestureEventHub()->SetUserOnClick([callback, overlayId, id](GestureEvent& /*info*/) {
        ContainerScope scope(id);
        auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(pipeline);
        auto overlayManager = pipeline->GetSelectOverlayManager();
        CHECK_NULL_VOID(overlayManager);

        auto selectOverlay = overlayManager->GetSelectOverlayNode(overlayId);
        CHECK_NULL_VOID(selectOverlay);
        auto pattern = selectOverlay->GetPattern<SelectOverlayPattern>();
        auto selectInfo = pattern->GetSelectInfo();
        if (callback) {
            callback(selectInfo);
        }
    });
}

RefPtr<FrameNode> BuildButton(const MenuOptionsParam& menuOption, int32_t overlayId, float& contentWidth)
{
    auto button = FrameNode::GetOrCreateFrameNode("SelectMenuButton", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto text = FrameNode::GetOrCreateFrameNode("SelectMenuButtonText", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });

    // Update text property and mount to button.
    auto textLayoutProperty = text->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, button);
    auto data = menuOption.content.value_or("");
    textLayoutProperty->UpdateContent(data);
    text->MountToParent(button);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, button);
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_RETURN(textOverlayTheme, button);
    auto textStyle = textOverlayTheme->GetMenuButtonTextStyle();
    textLayoutProperty->UpdateFontSize(textStyle.GetFontSize());
    textLayoutProperty->UpdateTextColor(textStyle.GetTextColor());
    textLayoutProperty->UpdateFontWeight(textStyle.GetFontWeight());
    text->MarkModifyDone();
    // Calculate the width of entension option include button padding.
    contentWidth = static_cast<float>(MeasureUtil::MeasureTextWidth(textStyle, data));
    const auto& padding = textOverlayTheme->GetMenuButtonPadding();
    auto left = CalcLength(padding.Left().ConvertToPx());
    auto right = CalcLength(padding.Right().ConvertToPx());
    auto top = CalcLength(padding.Top().ConvertToPx());
    auto bottom = CalcLength(padding.Bottom().ConvertToPx());
    contentWidth = contentWidth + padding.Left().ConvertToPx() + padding.Right().ConvertToPx();

    // Update button property.
    auto buttonLayoutProperty = button->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_RETURN(buttonLayoutProperty, button);
    buttonLayoutProperty->UpdatePadding({ left, right, top, bottom, std::nullopt, std::nullopt });
    if (GreatOrEqual(pipeline->GetFontScale(), AGING_MIN_SCALE)) {
        buttonLayoutProperty->UpdateUserDefinedIdealSize({ CalcLength(contentWidth), std::nullopt });
    } else {
        buttonLayoutProperty->UpdateUserDefinedIdealSize(
            { CalcLength(contentWidth), CalcLength(textOverlayTheme->GetMenuButtonHeight()) });
    }
    buttonLayoutProperty->UpdateFlexShrink(0);
    button->GetRenderContext()->UpdateBackgroundColor(Color::TRANSPARENT);
    BindButtonClickEvent(button, menuOption, overlayId);
    SetResponseRegion(button);
    button->MarkModifyDone();
    return button;
}

void BindCreateMenuItemClickEvent(const RefPtr<FrameNode>& button, const MenuOptionsParam& menuOptionsParam,
    int32_t overlayId, const std::function<void()>& systemCallback, const OnMenuItemCallback& onCreateCallback)
{
    auto id = Container::CurrentIdSafelyWithCheck();
    button->GetOrCreateGestureEventHub()->SetUserOnClick(
        [menuOptionsParam, systemCallback, onCreateCallback, id](GestureEvent& /*info*/) {
            ContainerScope scope(id);
            auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
            CHECK_NULL_VOID(pipeline);
            auto overlayManager = pipeline->GetSelectOverlayManager();
            CHECK_NULL_VOID(overlayManager);
            auto newOverlayManager = overlayManager->GetSelectContentOverlayManager();
            CHECK_NULL_VOID(newOverlayManager);
            bool result = false;
            if (onCreateCallback.onMenuItemClick) {
                MenuItemParam menuItem;
                menuItem.menuOptionsParam = menuOptionsParam;
                int32_t start = -1;
                int32_t end = -1;
                if (onCreateCallback.textRangeCallback) {
                    onCreateCallback.textRangeCallback(start, end);
                }
                menuItem.start = start;
                menuItem.end = end;
                result = onCreateCallback.onMenuItemClick(menuItem);
            }
            if (!result && systemCallback) {
                systemCallback();
            }
            if (!systemCallback && !result) {
                newOverlayManager->HideOptionMenu(true);
            }
        });
}

RefPtr<FrameNode> BuildCreateMenuItemButton(const MenuOptionsParam& menuOptionsParam,
    const std::function<void()>& systemCallback, const OnMenuItemCallback& menuItemCallback, int32_t overlayId,
    float& remainderWidth)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_RETURN(textOverlayTheme, nullptr);
    auto textStyle = textOverlayTheme->GetMenuButtonTextStyle();
    auto data = menuOptionsParam.content.value_or("");
    auto contentWidth = 0.0f;

    auto button = FrameNode::GetOrCreateFrameNode("SelectMenuButton", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto text = FrameNode::GetOrCreateFrameNode("SelectMenuButtonText", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    // Update text property and mount to button.
    auto textLayoutProperty = text->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, button);
    textLayoutProperty->UpdateContent(data);
    auto buttonType = IsAIMenuOption(menuOptionsParam.id) ?
                      SelectOverlayMenuButtonType::AIBUTTON : SelectOverlayMenuButtonType::NORMAL;
    PrepareButtonTextProp(textLayoutProperty, true, contentWidth, data, buttonType);
    textLayoutProperty->UpdateWordBreak(WordBreak::BREAK_ALL);
    text->MountToParent(button);

    // Calculate the width of entension option include button padding.
    const auto& padding = textOverlayTheme->GetMenuButtonPadding();
    auto left = CalcLength(padding.Left().ConvertToPx());
    auto right = CalcLength(padding.Right().ConvertToPx());
    auto top = CalcLength(padding.Top().ConvertToPx());
    auto bottom = CalcLength(padding.Bottom().ConvertToPx());
    contentWidth = contentWidth + padding.Left().ConvertToPx() + padding.Right().ConvertToPx();
    auto isOverWidth = GreatOrEqual(remainderWidth, contentWidth);
    CHECK_NULL_RETURN(isOverWidth || menuOptionsParam.isFirstOption, nullptr);
    contentWidth = std::min(contentWidth, remainderWidth);

    if (!isOverWidth && menuOptionsParam.isFirstOption) {
        textLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    }
    text->MarkModifyDone();

    // Update button property.
    auto buttonLayoutProperty = button->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_RETURN(buttonLayoutProperty, button);
    buttonLayoutProperty->UpdatePadding({ left, right, top, bottom, std::nullopt, std::nullopt });
    if (GreatOrEqual(pipeline->GetFontScale(), AGING_MIN_SCALE)) {
        buttonLayoutProperty->UpdateUserDefinedIdealSize({ CalcLength(contentWidth), std::nullopt });
    } else {
        buttonLayoutProperty->UpdateUserDefinedIdealSize(
            { CalcLength(contentWidth), CalcLength(textOverlayTheme->GetMenuButtonHeight()) });
    }
    buttonLayoutProperty->UpdateFlexShrink(0);
    button->GetRenderContext()->UpdateBackgroundColor(Color::TRANSPARENT);
    BindCreateMenuItemClickEvent(button, menuOptionsParam, overlayId, systemCallback, menuItemCallback);
    SetResponseRegion(button);
    button->MarkModifyDone();
    remainderWidth -= contentWidth;
    return button;
}

void UpdateBackButtonPadding(
    const RefPtr<FrameNode>& button, const CalcLength& sideWidth, const Edge& padding, int32_t overlayId)
{
    CHECK_NULL_VOID(button);
    auto buttonLayoutProperty = button->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(buttonLayoutProperty);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    buttonLayoutProperty->UpdateUserDefinedIdealSize({ sideWidth, sideWidth });
    auto left = CalcLength(padding.Left().ConvertToPx());
    auto right = CalcLength(padding.Right().ConvertToPx());
    auto top = CalcLength(padding.Top().ConvertToPx());
    auto bottom = CalcLength(padding.Bottom().ConvertToPx());
    if (GreatOrEqual(pipeline->GetFontScale(), AGING_MIN_SCALE)) {
        auto overlayManager = pipeline->GetSelectOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        auto selectOverlay = overlayManager->GetSelectOverlayNode(overlayId);
        if (selectOverlay) {
            auto selectMenu = AceType::DynamicCast<FrameNode>(selectOverlay->GetFirstChild());
            CHECK_NULL_VOID(selectMenu);
            auto geometryNode = selectMenu->GetGeometryNode();
            CHECK_NULL_VOID(geometryNode);
            auto selectMenuHeight = geometryNode->GetFrameSize().Height();
            top = CalcLength((selectMenuHeight - sideWidth.GetDimension().Value()) / 2.0f);
            bool isSymbol = Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE);
            top = isSymbol ? CalcLength(padding.Top().ConvertToPx()) : top;
        }
    }
    buttonLayoutProperty->UpdatePadding({ left, right, top, bottom, std::nullopt, std::nullopt });
}

RefPtr<FrameNode> BuildMoreOrBackButton(int32_t overlayId, bool isMoreButton)
{
    auto button = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, button);
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_RETURN(textOverlayTheme, button);

    // Update property.
    auto buttonLayoutProperty = button->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_RETURN(buttonLayoutProperty, button);

    const auto& padding = textOverlayTheme->GetMenuPadding();

    auto accessibilityProperty = button->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, button);

    if (isMoreButton) {
        auto sideWidth = CalcLength(textOverlayTheme->GetMenuToolbarHeight().ConvertToPx() -
                                    padding.Top().ConvertToPx() - padding.Bottom().ConvertToPx());
        buttonLayoutProperty->UpdateUserDefinedIdealSize({ sideWidth, sideWidth });
        accessibilityProperty->SetAccessibilityText(textOverlayTheme->GetMoreAccessibilityText());
    } else {
        auto sideWidth = CalcLength(textOverlayTheme->GetMenuToolbarHeight().ConvertToPx());
        UpdateBackButtonPadding(button, sideWidth, padding, overlayId);
        accessibilityProperty->SetAccessibilityText(textOverlayTheme->GetBackAccessibilityText());
    }
    auto id = Container::CurrentIdSafelyWithCheck();
    button->GetOrCreateGestureEventHub()->SetUserOnClick([overlayId, isMoreButton, id](GestureEvent& /*info*/) {
        auto container = Container::GetContainer(id);
        CHECK_NULL_VOID(container);
        auto pipeline = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
        CHECK_NULL_VOID(pipeline);
        auto overlayManager = pipeline->GetSelectOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        auto selectOverlay = overlayManager->GetSelectOverlayNode(overlayId);
        CHECK_NULL_VOID(selectOverlay);
        // When click button , change to extensionMenu or change to the default menu(selectMenu_).
        selectOverlay->MoreOrBackAnimation(isMoreButton);
    });

    button->GetRenderContext()->UpdateBackgroundColor(Color::TRANSPARENT);
    button->MarkModifyDone();
    SetMoreOrBackButtonResponse(button);
    return button;
}

RefPtr<FrameNode> BuildMoreOrBackSymbol()
{
    auto symbol = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    CHECK_NULL_RETURN(symbol, nullptr);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, symbol);
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_RETURN(textOverlayTheme, symbol);
    auto layoutProperty = symbol->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, symbol);
    layoutProperty->UpdateSymbolSourceInfo(SymbolSourceInfo(textOverlayTheme->GetMoreSymbolId()));
    layoutProperty->UpdateFontSize(textOverlayTheme->GetSymbolSize());
    layoutProperty->UpdateFontWeight(FontWeight::MEDIUM);
    layoutProperty->UpdateSymbolColorList({textOverlayTheme->GetSymbolColor()});
    auto symbolEffectOptions = layoutProperty->GetSymbolEffectOptionsValue(SymbolEffectOptions());
    symbolEffectOptions.SetEffectType(SymbolEffectType::REPLACE);
    symbolEffectOptions.SetScopeType(Ace::ScopeType::WHOLE);
    symbolEffectOptions.SetIsTxtActive(false);
    layoutProperty->UpdateSymbolEffectOptions(symbolEffectOptions);
    symbol->MarkModifyDone();
    return symbol;
}

OffsetF GetPageOffset()
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, OffsetF());
    auto stageManager = pipeline->GetStageManager();
    CHECK_NULL_RETURN(stageManager, OffsetF());
    auto page = stageManager->GetLastPage();
    CHECK_NULL_RETURN(page, OffsetF());
    return page->GetOffsetRelativeToWindow();
}

std::function<void()> GetMenuCallbackWithContainerId(std::function<void()> callback)
{
    auto optionCallback = [func = std::move(callback), mainId = Container::CurrentIdSafelyWithCheck()]() {
        ContainerScope scope(mainId);
        func();
    };
    return optionCallback;
}

std::function<void()> GetMenuCallbackWithContainerId(
    std::function<void(std::string)> callback, const std::string& info)
{
    auto optionCallback = [func = std::move(callback), mainId = Container::CurrentIdSafelyWithCheck(), info]() {
        ContainerScope scope(mainId);
        func(info);
    };
    return optionCallback;
}

std::function<void()> ConvertToVoidFunction(std::function<void(std::string)> funcWithArg, const std::string& arg)
{
    return [funcWithArg, arg]() {
        funcWithArg(arg);
    };
}

std::vector<OptionParam> GetOptionsParams(const std::shared_ptr<SelectOverlayInfo>& info)
{
    std::vector<OptionParam> params;
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, params);
    auto theme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_RETURN(theme, params);
    if (theme->GetShowShortcut()) {
        params.emplace_back(theme->GetCutLabel(), GetMenuCallbackWithContainerId(info->menuCallback.onCut),
            theme->GetCutLabelInfo(), info->menuInfo.showCut, theme->GetCutSymbolId());
        params.emplace_back(theme->GetCopyLabel(), GetMenuCallbackWithContainerId(info->menuCallback.onCopy),
            theme->GetCopyLabelInfo(), info->menuInfo.showCopy, theme->GetCopySymbolId());
        params.emplace_back(theme->GetPasteLabel(), GetMenuCallbackWithContainerId(info->menuCallback.onPaste),
            theme->GetPasteLabelInfo(), info->menuInfo.showPaste, theme->GetPasteSymbolId());
        params.emplace_back(theme->GetSelectAllLabel(), GetMenuCallbackWithContainerId(info->menuCallback.onSelectAll),
            theme->GetSelectAllLabelInfo(), info->menuInfo.showCopyAll, theme->GetCopyAllSymbolId());
    } else {
        params.emplace_back(theme->GetCutLabel(), GetMenuCallbackWithContainerId(info->menuCallback.onCut),
            theme->GetCutLabelInfo(), info->menuInfo.showCut);
        params.emplace_back(theme->GetCopyLabel(), GetMenuCallbackWithContainerId(info->menuCallback.onCopy),
            theme->GetCopyLabelInfo(), info->menuInfo.showCopy);
        params.emplace_back(theme->GetPasteLabel(), GetMenuCallbackWithContainerId(info->menuCallback.onPaste),
            theme->GetPasteLabelInfo(), info->menuInfo.showPaste);
        params.emplace_back(theme->GetSelectAllLabel(), GetMenuCallbackWithContainerId(info->menuCallback.onSelectAll),
            theme->GetSelectAllLabelInfo(), info->menuInfo.showCopyAll);
    }

    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_FIFTEEN) &&
        TextSystemMenu::IsShowTranslate()) {
        params.emplace_back(theme->GetTranslateLabel(),
            GetMenuCallbackWithContainerId(info->menuCallback.onTranslate), "", info->menuInfo.showTranslate);
    }
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        if (TextSystemMenu::IsShowShare()) {
            params.emplace_back(theme->GetShareLabel(), GetMenuCallbackWithContainerId(info->menuCallback.onShare), "",
                info->menuInfo.showShare);
        }
        if (TextSystemMenu::IsShowSearch()) {
            params.emplace_back(theme->GetSearchLabel(), GetMenuCallbackWithContainerId(info->menuCallback.onSearch),
                "", info->menuInfo.showSearch);
        }
    }

    if (IsShowAIMenuOption(info->menuInfo.aiMenuOptionType)) {
        auto inheritFunc = ConvertToVoidFunction(info->menuCallback.onAIMenuOption, "From_Right_Click");
        params.emplace_back(theme->GetAiMenuOptionName(info->menuInfo.aiMenuOptionType),
            GetMenuCallbackWithContainerId(inheritFunc), "", true);
        params.back().isAIMenuOption = true;
    }

    return params;
}

std::unordered_map<std::string, std::function<void()>> GetSystemCallback(
    const std::shared_ptr<SelectOverlayInfo>& info, bool isCallbackWithParam = false)
{
    CHECK_NULL_RETURN(info, {});
    std::unordered_map<std::string, std::function<void()>> systemCallback = {
        { OH_DEFAULT_CUT, info->menuCallback.onCut }, { OH_DEFAULT_COPY, info->menuCallback.onCopy },
        { OH_DEFAULT_SELECT_ALL, info->menuCallback.onSelectAll }, { OH_DEFAULT_PASTE, info->menuCallback.onPaste },
        { OH_DEFAULT_TRANSLATE, info->menuCallback.onTranslate },
        { OH_DEFAULT_SEARCH, info->menuCallback.onSearch },
        { OH_DEFAULT_SHARE, info->menuCallback.onShare },
        { OH_DEFAULT_CAMERA_INPUT, info->menuCallback.onCameraInput },
        { OH_DEFAULT_AI_WRITE, info->menuCallback.onAIWrite },
        { OH_DEFAULT_AI_MENU_PHONE, ConvertToVoidFunction(
            info->menuCallback.onAIMenuOption, OH_DEFAULT_AI_MENU_PHONE) },
        { OH_DEFAULT_AI_MENU_URL, ConvertToVoidFunction(
            info->menuCallback.onAIMenuOption, OH_DEFAULT_AI_MENU_URL) },
        { OH_DEFAULT_AI_MENU_EMAIL, ConvertToVoidFunction(
            info->menuCallback.onAIMenuOption, OH_DEFAULT_AI_MENU_EMAIL) },
        { OH_DEFAULT_AI_MENU_ADDRESS, ConvertToVoidFunction(
            info->menuCallback.onAIMenuOption, OH_DEFAULT_AI_MENU_ADDRESS) },
        { OH_DEFAULT_AI_MENU_DATETIME, ConvertToVoidFunction(
            info->menuCallback.onAIMenuOption, OH_DEFAULT_AI_MENU_DATETIME) },
    };
    return systemCallback;
}

bool IsSystemMenuItemEnabled(const std::shared_ptr<SelectOverlayInfo>& info, const std::string& id)
{
    CHECK_NULL_RETURN(info, true);
    auto isEnabledFunc = isMenuItemEnabledFuncMap.find(id);
    return isEnabledFunc == isMenuItemEnabledFuncMap.end() ? true : (isEnabledFunc->second)(info->menuInfo);
}

std::string GetSystemIconPath(const std::string& id, const std::string& iconPath)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, iconPath);
    auto iconTheme = pipeline->GetTheme<IconTheme>();
    CHECK_NULL_RETURN(iconTheme, iconPath);
    if (id == OH_DEFAULT_CUT) {
        return iconTheme->GetIconPath(InternalResource::ResourceId::IC_CUT_SVG);
    }
    if (id == OH_DEFAULT_COPY) {
        return iconTheme->GetIconPath(InternalResource::ResourceId::IC_COPY_SVG);
    }
    if (id == OH_DEFAULT_SELECT_ALL) {
        return iconTheme->GetIconPath(InternalResource::ResourceId::IC_SELECT_ALL_SVG);
    }
    if (id == OH_DEFAULT_TRANSLATE) {
        return iconTheme->GetIconPath(InternalResource::ResourceId::IC_TRANSLATE_SVG);
    }
    if (id == OH_DEFAULT_SEARCH) {
        return iconTheme->GetIconPath(InternalResource::ResourceId::IC_SEARCH_SVG);
    }
    if (id == OH_DEFAULT_SHARE) {
        return iconTheme->GetIconPath(InternalResource::ResourceId::IC_SHARE_SVG);
    }
    if (id == OH_DEFAULT_CAMERA_INPUT) {
        return iconTheme->GetIconPath(InternalResource::ResourceId::IC_TAKEPHOTO_SVG);
    }
    if (id == OH_DEFAULT_AI_WRITE) {
        return iconTheme->GetIconPath(InternalResource::ResourceId::IC_AI_WRITE_SVG);
    }
    return iconPath;
}

std::string GetItemContent(const std::string& id, const std::string& content,
                           const std::shared_ptr<SelectOverlayInfo>& info = nullptr)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, content);
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_RETURN(textOverlayTheme, content);
    if (id == OH_DEFAULT_CUT) {
        return textOverlayTheme->GetCutLabel();
    }
    if (id == OH_DEFAULT_COPY) {
        return textOverlayTheme->GetCopyLabel();
    }
    if (id == OH_DEFAULT_SELECT_ALL) {
        return textOverlayTheme->GetSelectAllLabel();
    }
    if (id == OH_DEFAULT_PASTE) {
        return textOverlayTheme->GetPasteLabel();
    }
    if (id == OH_DEFAULT_TRANSLATE) {
        return textOverlayTheme->GetTranslateLabel();
    }
    if (id == OH_DEFAULT_SEARCH) {
        return textOverlayTheme->GetSearchLabel();
    }
    if (id == OH_DEFAULT_SHARE) {
        return textOverlayTheme->GetShareLabel();
    }
    if (id == OH_DEFAULT_AI_WRITE) {
        return textOverlayTheme->GetAIWrite();
    }
    if (id == OH_DEFAULT_CAMERA_INPUT) {
        return textOverlayTheme->GetCameraInput();
    }
    if (IsAIMenuOption(id)) {
        CHECK_NULL_RETURN(info, content);
        return textOverlayTheme->GetAiMenuOptionName(info->menuInfo.aiMenuOptionType);
    }
    return content;
}

void CloseOverlayIfNecessary(const RefPtr<SelectOverlayManager>& overlayManager)
{
    CHECK_NULL_VOID(overlayManager);
    overlayManager->DestroySelectOverlay(true);
    auto contentOverlayManager = overlayManager->GetSelectContentOverlayManager();
    CHECK_NULL_VOID(contentOverlayManager);
    contentOverlayManager->CloseCurrent(true, CloseReason::CLOSE_REASON_TOOL_BAR);
}

std::vector<OptionParam> GetCreateMenuOptionsParams(const std::vector<MenuOptionsParam>& menuOptionItems,
    const std::shared_ptr<SelectOverlayInfo>& info, int32_t startIndex)
{
    auto id = Container::CurrentIdSafelyWithCheck();
    std::vector<OptionParam> params;
    const auto systemCallback = GetSystemCallback(info);
    int32_t itemNum = 0;
    for (auto item : menuOptionItems) {
        if (itemNum < startIndex) {
            itemNum++;
            continue;
        }
        std::function<void()> systemEvent;
        auto clickCallback = systemCallback.find(item.id);
        if (clickCallback != systemCallback.end()) {
            systemEvent = clickCallback->second;
        }
        auto callback = [onCreateCallback = info->onCreateCallback, systemEvent, item, id]() {
            ContainerScope scope(id);
            auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
            CHECK_NULL_VOID(pipeline);
            auto overlayManager = pipeline->GetSelectOverlayManager();
            CHECK_NULL_VOID(overlayManager);
            bool result = false;
            if (onCreateCallback.onMenuItemClick) {
                MenuItemParam menuItem;
                menuItem.menuOptionsParam = item;
                int32_t start = -1;
                int32_t end = -1;
                if (onCreateCallback.textRangeCallback) {
                    onCreateCallback.textRangeCallback(start, end);
                }
                menuItem.start = start;
                menuItem.end = end;
                result = onCreateCallback.onMenuItemClick(menuItem);
            }
            if (!result && systemEvent) {
                systemEvent();
            }
            if (!systemEvent && !result) {
                CloseOverlayIfNecessary(overlayManager);
            }
        };
        if (item.symbolId.has_value()) {
            params.emplace_back(
                GetItemContent(item.id, item.content.value_or("")), "", item.labelInfo.value_or(""), callback, item.symbolId.value_or(0));
        } else {
            params.emplace_back(
                GetItemContent(item.id, item.content.value_or("")), "", item.labelInfo.value_or(""), callback);
        }
        params.back().enabled = IsSystemMenuItemEnabled(info, item.id);
        params.back().disableSystemClick = true;
        params.back().isAIMenuOption = IsAIMenuOption(item.id);
        itemNum++;
    }
    return params;
}

#ifdef OHOS_PLATFORM
RefPtr<FrameNode> CreateMenuTextNode(const std::string& value, const RefPtr<FrameNode>& parent,
    bool isAIMenuEnabled = false)
{
    auto textId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, textId, AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textNode, nullptr);
    auto textProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textProperty, nullptr);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(theme, nullptr);
    textProperty->UpdateMaxLines(1);
    textProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textProperty->UpdateFontSize(theme->GetMenuFontSize());
    textProperty->UpdateFontWeight(FontWeight::REGULAR);
    textProperty->UpdateTextColor(Color::TRANSPARENT);
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    if (isAIMenuEnabled == true && textOverlayTheme) {
        TextStyle textStyle;
        textStyle.SetFontSize(theme->GetMenuFontSize());
        textStyle.SetFontWeight(FontWeight::REGULAR);
        auto textSize = MeasureUtil::MeasureTextSize(textStyle, value);
        FontForegroudGradiantColor colorInfo;
        colorInfo.points = { NG::PointF(0, 0),
            NG::PointF(static_cast<float>(textSize.Width()), static_cast<float>(textSize.Height())) };
        colorInfo.colors = textOverlayTheme->GetAiMenuFontGradientColors();
        colorInfo.scalars = textOverlayTheme->GetAiMenuFontGradientScalars();
        textProperty->UpdateFontForegroudGradiantColor(colorInfo);
    }
    auto textRenderContext = textNode->GetRenderContext();
    CHECK_NULL_RETURN(textRenderContext, nullptr);
    textRenderContext->UpdateForegroundColor(theme->GetMenuFontColor());
    textProperty->UpdateContent(value);
    textNode->MountToParent(parent);
    textNode->MarkModifyDone();
    return textNode;
}

void SetPasteNodeProperties(const RefPtr<FrameNode>& pasteNode, const RefPtr<SelectTheme>& theme, bool enabled)
{
    CHECK_NULL_VOID(pasteNode);
    CHECK_NULL_VOID(theme);
    auto pasteLayoutProperty = pasteNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    CHECK_NULL_VOID(pasteLayoutProperty);
    auto pastePaintProperty = pasteNode->GetPaintProperty<SecurityComponentPaintProperty>();
    CHECK_NULL_VOID(pastePaintProperty);
    pastePaintProperty->UpdateBackgroundColor(Color::TRANSPARENT);
    pasteLayoutProperty->UpdateBackgroundBorderRadius(BorderRadiusProperty(theme->GetInnerBorderRadius()));
    pasteLayoutProperty->UpdateFontSize(theme->GetMenuFontSize());
    pasteLayoutProperty->UpdateFontWeight(FontWeight::REGULAR);
    pastePaintProperty->UpdateFontColor(theme->GetMenuFontColor());
    pasteLayoutProperty->UpdateStateEffect(true);
    auto horInterval = static_cast<float>(theme->GetMenuIconPadding().ConvertToPx()) -
                       static_cast<float>(theme->GetOutPadding().ConvertToPx());
    auto pasteButtonRenderContext = pasteNode->GetRenderContext();
    CHECK_NULL_VOID(pasteButtonRenderContext);
    pasteLayoutProperty->UpdateBackgroundLeftPadding(Dimension(horInterval));
    pasteLayoutProperty->UpdateTextIconSpace(Dimension(theme->GetIconContentPadding().ConvertToPx() * 2));
    pasteButtonRenderContext->UpdateOpacity(1.0);
}

void UpdatePasteOpacityFont(bool isPaste, RefPtr<FrameNode>& leftRowNode, const OptionParam& param,
    const RefPtr<SelectTheme>& theme, const RefPtr<FrameNode>& menuItem)
{
    CHECK_NULL_VOID(leftRowNode);
    auto leftRowRenderContext = leftRowNode->GetRenderContext();
    CHECK_NULL_VOID(leftRowRenderContext);
    if (isPaste) {
        if (!param.enabled) {
            leftRowRenderContext->UpdateOpacity(theme->GetDisabledFontColorAlpha());
            leftRowNode->MarkModifyDone();
        }
    }
    auto menuItemPattern = menuItem->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    auto eventHub = menuItemPattern->GetOrCreateEventHub<MenuItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetSelectedChangeEvent([action = param.action](bool isSelected) {
        if (isSelected) {
            action();
        }
    });
    eventHub->SetEnabled(param.enabled);
    auto focusHub = menuItem->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetEnabled(param.enabled);
    if (menuItemPattern->IsDisabled()) {
        leftRowRenderContext->UpdateOpacity(theme->GetDisabledFontColorAlpha());
        leftRowNode->MarkModifyDone();
    }
    menuItemPattern->SetBlockClick(param.disableSystemClick);
}

void SetMenuItemIcon(const RefPtr<FrameNode>& menuItem, const OptionParam& param, RefPtr<FrameNode>& leftRow)
{
    auto symbol = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    CHECK_NULL_VOID(symbol);
    auto layoutProperty = symbol->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    layoutProperty->UpdateFontSize(theme->GetEndIconWidth());
    layoutProperty->UpdateSymbolColorList({ theme->GetMenuIconColor() });
    layoutProperty->UpdateAlignment(Alignment::CENTER_LEFT);
    layoutProperty->UpdateSymbolSourceInfo(SymbolSourceInfo(param.symbolId));
    MarginProperty margin;
    margin.right = CalcLength(theme->GetIconContentPadding());
    layoutProperty->UpdateMargin(margin);
    symbol->MountToParent(leftRow);
}

void SetupMenuItemChildrenAndFocus(const RefPtr<FrameNode>& menuItem, const std::string& content,
    const std::string& labelInfo, const RefPtr<SelectTheme>& theme, const OptionParam& param, bool isPaste)
{
    auto leftRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    CHECK_NULL_VOID(leftRow);
    auto leftRowLayoutProps = leftRow->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(leftRowLayoutProps);
    leftRowLayoutProps->UpdateMainAxisAlign(FlexAlign::FLEX_START);
    leftRowLayoutProps->UpdateCrossAxisAlign(FlexAlign::CENTER);
    leftRowLayoutProps->UpdateSpace(theme->GetIconContentPadding());
    if (!isPaste && param.symbolId != 0) {
        SetMenuItemIcon(menuItem, param, leftRow);
    }
    auto leftTextNode = CreateMenuTextNode(content, leftRow, param.isAIMenuOption);
    CHECK_NULL_VOID(leftTextNode);
    leftRow->MountToParent(menuItem);
    leftRow->MarkModifyDone();
    auto rightRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    CHECK_NULL_VOID(rightRow);
    auto rightRowLayoutProps = rightRow->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(rightRowLayoutProps);
    rightRowLayoutProps->UpdateMainAxisAlign(FlexAlign::CENTER);
    rightRowLayoutProps->UpdateCrossAxisAlign(FlexAlign::CENTER);
    rightRowLayoutProps->UpdateSpace(theme->GetIconContentPadding());
    auto rightTextNode = CreateMenuTextNode(labelInfo, rightRow, param.isAIMenuOption);
    CHECK_NULL_VOID(rightTextNode);
    rightRow->MountToParent(menuItem);
    auto rightTextRenderContext = rightTextNode->GetRenderContext();
    CHECK_NULL_VOID(rightTextRenderContext);
    auto menuItemPattern = menuItem->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    UpdatePasteOpacityFont(isPaste, leftRow, param, theme, menuItem);
    rightTextRenderContext->UpdateOpacity(theme->GetDisabledFontColorAlpha());
    rightTextNode->MarkModifyDone();
}

void SetPasteMenuItemEvent(const RefPtr<FrameNode>& menuItem, const RefPtr<FrameNode>& pasteNode,
    const OptionParam& param, const RefPtr<SelectTheme>& theme)
{
    auto eventHub = menuItem->GetOrCreateEventHub<MenuItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(false);
    auto focusHub = menuItem->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetEnabled(false);
    auto pasteEventHub = pasteNode->GetOrCreateEventHub<EventHub>();
    CHECK_NULL_VOID(pasteEventHub);
    pasteEventHub->SetEnabled(param.enabled);
    auto pasteFocusHub = pasteNode->GetFocusHub();
    CHECK_NULL_VOID(pasteFocusHub);
    pasteFocusHub->SetEnabled(param.enabled);
    auto id = Container::CurrentIdSafelyWithCheck();
    pasteNode->GetOrCreateGestureEventHub()->SetUserOnClick([action = param.action, id](GestureEvent& info) {
        ContainerScope scope(id);
        if (!PasteButtonModelNG::GetInstance()->IsClickResultSuccess(info)) {
            return;
        }
        if (action) {
            action();
        }
    });
    auto menuItemPattern = menuItem->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->SetBlockClick(param.disableSystemClick);
    menuItemPattern->SetPasteButton(pasteNode);
}

RefPtr<FrameNode> CreateRelativeContainer(const RefPtr<FrameNode>& menuItem, const RefPtr<FrameNode>& pasteNode)
{
    auto relativeContainer =
        FrameNode::GetOrCreateFrameNode(V2::RELATIVE_CONTAINER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<OHOS::Ace::NG::RelativeContainerPattern>(); });
    CHECK_NULL_RETURN(relativeContainer, nullptr);
    auto relativeContainerLayoutProperty = relativeContainer->GetLayoutProperty();
    CHECK_NULL_RETURN(relativeContainerLayoutProperty, nullptr);
    relativeContainerLayoutProperty->UpdateUserDefinedIdealSize(
        { CalcLength(0.0, DimensionUnit::AUTO), CalcLength(0.0, DimensionUnit::AUTO) });
    auto menuItemRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    CHECK_NULL_RETURN(menuItemRow, nullptr);
    auto buttonRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    CHECK_NULL_RETURN(buttonRow, nullptr);
    std::string menuItemRowId = "__menuItemRow__";
    menuItemRow->UpdateInspectorId(menuItemRowId);
    auto buttonRowLayoutProperty = buttonRow->GetLayoutProperty();
    CHECK_NULL_RETURN(buttonRowLayoutProperty, nullptr);
    buttonRowLayoutProperty->UpdateAlignRules(
        { { AlignDirection::LEFT, { .anchor = menuItemRowId, .horizontal = HorizontalAlign::START } },
            { AlignDirection::TOP, { .anchor = menuItemRowId, .vertical = VerticalAlign::TOP } },
            { AlignDirection::RIGHT, { .anchor = menuItemRowId, .horizontal = HorizontalAlign::END } },
            { AlignDirection::BOTTOM, { .anchor = menuItemRowId, .vertical = VerticalAlign::BOTTOM } } });
    auto menuItemLayoutProperty = menuItem->GetLayoutProperty();
    CHECK_NULL_RETURN(menuItemLayoutProperty, nullptr);
    menuItemLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    menuItem->MountToParent(menuItemRow);
    pasteNode->MountToParent(buttonRow);
    relativeContainer->AddChild(menuItemRow);
    relativeContainer->AddChild(buttonRow);
    return relativeContainer;
}

RefPtr<FrameNode> CreateMenuItemPaste(
    const std::string& labelInfo, RefPtr<FrameNode> innerMenuNode, const OptionParam& param, size_t index)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(theme, nullptr);
    auto pasteNode = PasteButtonModelNG::GetInstance()->CreateNode(
        static_cast<int32_t>(PasteButtonPasteDescription::PASTE), static_cast<int32_t>(PasteButtonIconStyle::ICON_NULL),
        static_cast<int32_t>(ButtonType::NORMAL), true, param.symbolId);
    CHECK_NULL_RETURN(pasteNode, nullptr);
    SetPasteNodeProperties(pasteNode, theme, param.enabled);
    auto menuItem =
        FrameNode::GetOrCreateFrameNode(V2::MENU_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            [index]() { return AceType::MakeRefPtr<MenuItemPattern>(false, index); });
    CHECK_NULL_RETURN(menuItem, nullptr);
    BorderRadiusProperty border;
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        border.SetRadius(theme->GetMenuDefaultInnerRadius());
    } else {
        border.SetRadius(theme->GetInnerBorderRadius());
    }
    auto renderContext = menuItem->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    renderContext->UpdateBorderRadius(border);
    SetupMenuItemChildrenAndFocus(menuItem, "", labelInfo, theme, param, true);

    SetPasteMenuItemEvent(menuItem, pasteNode, param, theme);
    auto relativeContainer = CreateRelativeContainer(menuItem, pasteNode);
    CHECK_NULL_RETURN(relativeContainer, nullptr);
    menuItem->MarkModifyDone();
    pasteNode->MarkModifyDone();
    relativeContainer->MountToParent(innerMenuNode);
    relativeContainer->MarkModifyDone();
    return relativeContainer;
}

RefPtr<FrameNode> CreateMenuItem(const std::string& content, const std::string& labelInfo,
    RefPtr<FrameNode> innerMenuNode, const OptionParam& param, size_t index)
{
    CHECK_NULL_RETURN(innerMenuNode, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_RETURN(stack, nullptr);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto menuItem =
        FrameNode::GetOrCreateFrameNode(V2::MENU_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            [index]() { return AceType::MakeRefPtr<MenuItemPattern>(false, index); });
    CHECK_NULL_RETURN(menuItem, nullptr);
    auto renderContext = menuItem->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(theme, nullptr);
    BorderRadiusProperty border;
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        border.SetRadius(theme->GetMenuDefaultInnerRadius());
    } else {
        border.SetRadius(theme->GetInnerBorderRadius());
    }
    renderContext->UpdateBorderRadius(border);
    SetupMenuItemChildrenAndFocus(menuItem, content, labelInfo, theme, param, false);
    menuItem->MountToParent(innerMenuNode);
    menuItem->MarkModifyDone();
    return menuItem;
}
#endif

RefPtr<FrameNode> GetMenuWrapper(std::vector<OptionParam>& params, const RefPtr<TextOverlayTheme>& textOverlayTheme)
{
    CHECK_NULL_RETURN(textOverlayTheme, nullptr);
    RefPtr<FrameNode> menuWrapper = nullptr;
    auto showShortcut = textOverlayTheme->GetShowShortcut();
    if (showShortcut) {
        auto* stack = ViewStackProcessor::GetInstance();
        CHECK_NULL_RETURN(stack, nullptr);
        auto innerMenuNode = FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG, stack->ClaimNodeId(),
            []() { return AceType::MakeRefPtr<InnerMenuPattern>(-1, V2::MENU_ETS_TAG, MenuType::MULTI_MENU); });
        CHECK_NULL_RETURN(innerMenuNode, nullptr);
#ifdef OHOS_PLATFORM
        RefPtr<FrameNode> menuItem = nullptr;
        for (size_t i = 0; i < params.size(); i++) {
            if (params[i].value == textOverlayTheme->GetPasteLabel()) {
                menuItem = CreateMenuItemPaste(params[i].labelInfo, innerMenuNode, params[i], i);
            } else {
                menuItem = CreateMenuItem(params[i].value, params[i].labelInfo, innerMenuNode, params[i], i);
            }
            if (!menuItem) {
                continue;
            }
        }
        menuWrapper = MenuView::Create(innerMenuNode, -1, "SelectOverlayMenuByRightClick",
            { .isShowInSubWindow = false, .type = MenuType::SELECT_OVERLAY_RIGHT_CLICK_MENU });
        menuWrapper->UpdateInspectorId("select_overlay_right_click_menuWrapper");
#else
        menuWrapper = MenuView::Create(std::move(params), -1, "SelectOverlayMenuByRightClick",
            MenuType::SELECT_OVERLAY_RIGHT_CLICK_MENU, { .isShowInSubWindow = false });
#endif
    } else {
        menuWrapper = MenuView::Create(std::move(params), -1, "SelectOverlayMenuByRightClick",
            MenuType::SELECT_OVERLAY_RIGHT_CLICK_MENU, { .isShowInSubWindow = false });
    }
    return menuWrapper;
}
} // namespace

SelectOverlayNode::SelectOverlayNode(const RefPtr<Pattern>& pattern)
    : FrameNode(V2::SELECT_OVERLAY_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), pattern)
{
    stateFuncs_[FrameNodeStatus::VISIBLE] = &SelectOverlayNode::DispatchVisibleState;
    stateFuncs_[FrameNodeStatus::VISIBLETOGONE] = &SelectOverlayNode::DispatchVisibleToGoneState;
    stateFuncs_[FrameNodeStatus::GONE] = &SelectOverlayNode::DispatchGoneState;
    stateFuncs_[FrameNodeStatus::GONETOVISIBLE] = &SelectOverlayNode::DispatchGoneToVisibleState;
}

void SelectOverlayNode::DispatchVisibleState(FrameNodeType type, FrameNodeTrigger trigger)
{
    AnimationOption option;
    option.SetDuration(MENU_HIDE_ANIMATION_DURATION);
    option.SetCurve(Curves::SHARP);

    switch (trigger) {
        case FrameNodeTrigger::HIDE:
            SetFrameNodeStatus(type, FrameNodeStatus::VISIBLETOGONE);
            AnimationUtils::Animate(
                option,
                [weak = WeakClaim(this), type, id = Container::CurrentId()]() {
                    ContainerScope scope(id);
                    auto node = weak.Upgrade();
                    CHECK_NULL_VOID(node);
                    node->SetFrameNodeOpacity(type, 0.0);
                },
                [weak = WeakClaim(this), type, id = Container::CurrentId()]() {
                    ContainerScope scope(id);
                    auto node = weak.Upgrade();
                    CHECK_NULL_VOID(node);
                    node->ExecuteOverlayStatus(type, FrameNodeTrigger::HIDDEN);
                });
            break;
        case FrameNodeTrigger::SHOW:
        case FrameNodeTrigger::SHOWN:
        case FrameNodeTrigger::HIDDEN:
        default:
            break;
    }
}

void SelectOverlayNode::DispatchVisibleToGoneState(FrameNodeType type, FrameNodeTrigger trigger)
{
    AnimationOption option;
    option.SetDuration(MENU_SHOW_ANIMATION_DURATION);
    option.SetCurve(Curves::SHARP);

    switch (trigger) {
        case FrameNodeTrigger::SHOW:
            SetFrameNodeStatus(type, FrameNodeStatus::GONETOVISIBLE);
            SetFrameNodeVisibility(type, VisibleType::VISIBLE);
            AnimationUtils::Animate(
                option,
                [weak = WeakClaim(this), type, id = Container::CurrentId()]() {
                    ContainerScope scope(id);
                    auto node = weak.Upgrade();
                    CHECK_NULL_VOID(node);
                    node->SetFrameNodeOpacity(type, 1.0);
                },
                [weak = WeakClaim(this), type, id = Container::CurrentId()]() {
                    ContainerScope scope(id);
                    auto node = weak.Upgrade();
                    CHECK_NULL_VOID(node);
                    node->ExecuteOverlayStatus(type, FrameNodeTrigger::SHOWN);
                });
            break;
        case FrameNodeTrigger::HIDDEN:
            SetFrameNodeStatus(type, FrameNodeStatus::GONE);
            SetFrameNodeVisibility(type, VisibleType::GONE);
            break;
        case FrameNodeTrigger::SHOWN:
        case FrameNodeTrigger::HIDE:
        default:
            break;
    }
}

void SelectOverlayNode::DispatchGoneState(FrameNodeType type, FrameNodeTrigger trigger)
{
    AnimationOption option;
    option.SetDuration(MENU_SHOW_ANIMATION_DURATION);
    option.SetCurve(Curves::SHARP);

    switch (trigger) {
        case FrameNodeTrigger::SHOW:
            SetFrameNodeStatus(type, FrameNodeStatus::GONETOVISIBLE);
            SetFrameNodeVisibility(type, VisibleType::VISIBLE);
            AnimationUtils::Animate(
                option,
                [weak = WeakClaim(this), type, id = Container::CurrentId()]() {
                    ContainerScope scope(id);
                    auto node = weak.Upgrade();
                    CHECK_NULL_VOID(node);
                    node->SetFrameNodeOpacity(type, 1.0);
                },
                [weak = WeakClaim(this), type, id = Container::CurrentId()]() {
                    ContainerScope scope(id);
                    auto node = weak.Upgrade();
                    CHECK_NULL_VOID(node);
                    node->ExecuteOverlayStatus(type, FrameNodeTrigger::SHOWN);
                });
            break;
        case FrameNodeTrigger::SHOWN:
        case FrameNodeTrigger::HIDE:
        case FrameNodeTrigger::HIDDEN:
        default:
            break;
    }
}

void SelectOverlayNode::DispatchGoneToVisibleState(FrameNodeType type, FrameNodeTrigger trigger)
{
    AnimationOption option;
    option.SetDuration(MENU_HIDE_ANIMATION_DURATION);
    option.SetCurve(Curves::SHARP);

    switch (trigger) {
        case FrameNodeTrigger::SHOWN:
            SetFrameNodeStatus(type, FrameNodeStatus::VISIBLE);
            break;
        case FrameNodeTrigger::HIDE:
            SetFrameNodeStatus(type, FrameNodeStatus::VISIBLETOGONE);
            AnimationUtils::Animate(
                option,
                [weak = WeakClaim(this), type, id = Container::CurrentId()]() {
                    ContainerScope scope(id);
                    auto node = weak.Upgrade();
                    CHECK_NULL_VOID(node);
                    node->SetFrameNodeOpacity(type, 0.0);
                },
                [weak = WeakClaim(this), type, id = Container::CurrentId()]() {
                    ContainerScope scope(id);
                    auto node = weak.Upgrade();
                    CHECK_NULL_VOID(node);
                    node->ExecuteOverlayStatus(type, FrameNodeTrigger::HIDDEN);
                });
            break;
        case FrameNodeTrigger::SHOW:
        case FrameNodeTrigger::HIDDEN:
            break;
        default:
            break;
    }
}

RefPtr<UINode> CreateCustomSelectMenu(const std::shared_ptr<SelectOverlayInfo>& info)
{
    CHECK_NULL_RETURN(info, nullptr);
    CHECK_NULL_RETURN(info->menuInfo.menuBuilder, nullptr);
    NG::ScopedViewStackProcessor builderViewStackProcessor;
    info->menuInfo.menuBuilder();
    auto customNode = NG::ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_RETURN(customNode, nullptr);
    return customNode;
}

RefPtr<FrameNode> SelectOverlayNode::CreateSelectOverlayNode(
    const std::shared_ptr<SelectOverlayInfo>& info, SelectOverlayMode mode)
{
    auto isShowHandleOnly = (mode == SelectOverlayMode::HANDLE_ONLY);
    if (info->isUsingMouse && !info->menuInfo.menuBuilder && !isShowHandleOnly) {
        return CreateMenuNode(info);
    }
    RefPtr<Pattern> selectOverlayPattern;
    if (info->isUseOverlayNG) {
        selectOverlayPattern = AceType::MakeRefPtr<SelectContentOverlayPattern>(info, mode);
    } else {
        selectOverlayPattern = AceType::MakeRefPtr<SelectOverlayPattern>(info, mode);
    }
    auto selectOverlayNode = AceType::MakeRefPtr<SelectOverlayNode>(selectOverlayPattern);
    selectOverlayNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(selectOverlayNode);
    selectOverlayNode->CreateToolBar();
    selectOverlayNode->UpdateToolBar(true);
    auto selectContext = selectOverlayNode->GetRenderContext();
    selectContext->UpdateUseShadowBatching(true);

    auto accessibilityProperty = selectOverlayNode->GetAccessibilityProperty<AccessibilityProperty>();
    if (accessibilityProperty) {
        accessibilityProperty->SetAccessibilityLevel("no");
    }
    return selectOverlayNode;
}

void SelectOverlayNode::CreateCustomSelectOverlay(const std::shared_ptr<SelectOverlayInfo>& info)
{
    selectMenu_ = FrameNode::GetOrCreateFrameNode(
        V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), [id = GetId()]() {
            return AceType::MakeRefPtr<MenuPattern>(id, V2::MENU_ETS_TAG, MenuType::SELECT_OVERLAY_CUSTOM_MENU);
        });
    selectMenu_->MountToParent(Claim(this));
    TAG_LOGI(AceLogTag::ACE_SELECT_OVERLAY, "CreateCustomSelectOverlay by menu:%{public}d", selectMenu_->GetId());
    AddCustomMenuCallbacks(info);
    auto renderContext = selectMenu_->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateClipEdge(false);
    renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    renderContext->UpdateBackShadow(ShadowConfig::NoneShadow);
    auto layoutProperty = selectMenu_->GetLayoutProperty<MenuLayoutProperty>();
    auto customMenu = CreateCustomSelectMenu(info);
    CHECK_NULL_VOID(selectMenu_);
    CHECK_NULL_VOID(customMenu);
    customMenu->MountToParent(selectMenu_);
    auto pattern = GetPattern<SelectOverlayPattern>();
    CHECK_NULL_VOID(pattern);
    InitSelectMenuStatus(pattern->GetMode(), info, false);
    selectMenu_->MarkModifyDone();
}

void SelectOverlayNode::MoreOrBackAnimation(bool isMore, bool noAnimation)
{
    CHECK_NULL_VOID(!isDoingAnimation_);
    CHECK_NULL_VOID(selectMenu_);
    CHECK_NULL_VOID(selectMenuInner_);
    CHECK_NULL_VOID(extensionMenu_);
    CHECK_NULL_VOID(backButton_);
    if (isMore && !isExtensionMenu_) {
        MoreAnimation(noAnimation);
    } else if (!isMore && isExtensionMenu_) {
        BackAnimation(noAnimation);
    }
}

void SelectOverlayNode::MoreAnimation(bool noAnimation)
{
    auto extensionContext = extensionMenu_->GetRenderContext();
    CHECK_NULL_VOID(extensionContext);
    auto selectMenuInnerContext = selectMenuInner_->GetRenderContext();
    CHECK_NULL_VOID(selectMenuInnerContext);

    auto extensionProperty = extensionMenu_->GetLayoutProperty();
    CHECK_NULL_VOID(extensionProperty);
    auto selectProperty = selectMenu_->GetLayoutProperty();
    CHECK_NULL_VOID(selectProperty);
    auto selectMenuInnerProperty = selectMenuInner_->GetLayoutProperty();
    CHECK_NULL_VOID(selectMenuInnerProperty);
    auto backButtonProperty = backButton_->GetLayoutProperty();
    CHECK_NULL_VOID(backButtonProperty);

    auto pattern = GetPattern<SelectOverlayPattern>();
    CHECK_NULL_VOID(pattern);
    auto modifier = pattern->GetOverlayModifier();
    CHECK_NULL_VOID(modifier);

    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);

    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(textOverlayTheme);

    auto shadowTheme = pipeline->GetTheme<ShadowTheme>();
    CHECK_NULL_VOID(shadowTheme);

    isExtensionMenu_ = true;

    extensionProperty->UpdateVisibility(VisibleType::VISIBLE);
    backButtonProperty->UpdateVisibility(VisibleType::VISIBLE);
    extensionMenuStatus_ = FrameNodeStatus::VISIBLE;
    UpdateMoreOrBackSymbolOptions(false, true);
    AnimationOption extensionOption;
    extensionOption.SetDuration(ANIMATION_DURATION2);
    extensionOption.SetCurve(Curves::FAST_OUT_SLOW_IN);
    auto toolbarHeight = textOverlayTheme->GetMenuToolbarHeight();
    auto frameSize = CalcSize(CalcLength(toolbarHeight.ConvertToPx()), CalcLength(toolbarHeight.ConvertToPx()));
    auto containerId = pipeline->GetInstanceId();
    AnimationUtils::Animate(
        extensionOption, [extensionContext, selectMenuInnerContext, id = containerId, shadowTheme]() {
            ContainerScope scope(id);
            if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
                extensionContext->UpdateOpacity(1.0);
            }
            extensionContext->UpdateTransformTranslate({ 0.0f, 0.0f, 0.0f });
            auto colorMode = Container::CurrentColorMode();
            extensionContext->UpdateBackShadow(shadowTheme->GetShadow(ShadowStyle::OuterDefaultMD, colorMode));
            selectMenuInnerContext->UpdateOpacity(0.0);
        });
    modifier->SetOtherPointRadius(MIN_DIAMETER / 2.0f, noAnimation);
    modifier->SetHeadPointRadius(MIN_ARROWHEAD_DIAMETER / 2.0f, noAnimation);
    modifier->SetLineEndOffset(true, noAnimation);
    auto menuPattern = extensionMenu_->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->SetMenuShow();
    FinishCallback callback = [selectMenuInnerProperty, extensionProperty, backButtonProperty, id = containerId,
                                  weak = WeakClaim(this), weakExtensionMenu = WeakClaim(RawPtr(extensionMenu_))]() {
        ContainerScope scope(id);
        selectMenuInnerProperty->UpdateVisibility(VisibleType::GONE);
        extensionProperty->UpdateVisibility(VisibleType::VISIBLE);
        auto selectOverlay = weak.Upgrade();
        CHECK_NULL_VOID(selectOverlay);
        selectOverlay->SetAnimationStatus(false);
        auto extensionMenu = weakExtensionMenu.Upgrade();
        CHECK_NULL_VOID(extensionMenu);
        auto child = extensionMenu->GetFirstChild();
        while (child) {
            if (child->GetTag() == V2::OPTION_ETS_TAG) {
                auto target = AceType::DynamicCast<FrameNode>(child);
                CHECK_NULL_VOID(target);
                target->OnAccessibilityEvent(AccessibilityEventType::REQUEST_FOCUS);
                break;
            }
            child = child->GetFirstChild();
        }
    };
    AnimationOption selectOption;
    selectOption.SetDuration(ANIMATION_DURATION1);
    selectOption.SetCurve(Curves::FRICTION);
    pipeline->FlushUITasks();
    extensionMenu_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    pipeline->FlushUITasks();
    AnimationUtils::OpenImplicitAnimation(selectOption, Curves::FRICTION, callback);
    selectProperty->UpdateUserDefinedIdealSize(frameSize);
    selectMenuInnerContext->UpdateTransformTranslate({ ANIMATION_TEXT_OFFSET.ConvertToPx(), 0.0f, 0.0f });
    selectMenu_->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    pipeline->FlushUITasks();
    AnimationUtils::CloseImplicitAnimation();
    isDoingAnimation_ = true;
}

void SelectOverlayNode::BackAnimation(bool noAnimation)
{
    auto selectContext = selectMenu_->GetRenderContext();
    CHECK_NULL_VOID(selectContext);
    auto extensionContext = extensionMenu_->GetRenderContext();
    CHECK_NULL_VOID(extensionContext);
    auto selectMenuInnerContext = selectMenuInner_->GetRenderContext();
    CHECK_NULL_VOID(selectMenuInnerContext);

    auto extensionProperty = extensionMenu_->GetLayoutProperty();
    CHECK_NULL_VOID(extensionProperty);
    auto selectProperty = selectMenu_->GetLayoutProperty();
    CHECK_NULL_VOID(selectProperty);
    auto selectMenuInnerProperty = selectMenuInner_->GetLayoutProperty();
    CHECK_NULL_VOID(selectMenuInnerProperty);
    auto backButtonProperty = backButton_->GetLayoutProperty();
    CHECK_NULL_VOID(backButtonProperty);

    auto pattern = GetPattern<SelectOverlayPattern>();
    CHECK_NULL_VOID(pattern);
    auto modifier = pattern->GetOverlayModifier();
    CHECK_NULL_VOID(modifier);

    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);

    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(textOverlayTheme);

    isExtensionMenu_ = false;
    auto menuWidth = pattern->GetMenuWidth();

    selectMenuInnerProperty->UpdateVisibility(VisibleType::VISIBLE);

    auto menuPattern = extensionMenu_->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->ShowMenuDisappearAnimation();
    AnimationOption extensionOption;
    extensionOption.SetDuration(ANIMATION_DURATION2);
    extensionOption.SetCurve(Curves::FAST_OUT_SLOW_IN);
    auto containerId = pipeline->GetInstanceId();
    AnimationUtils::Animate(extensionOption, [extensionContext, selectMenuInnerContext, id = containerId]() {
        ContainerScope scope(id);
        if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            extensionContext->UpdateOpacity(0.0);
        }
        extensionContext->UpdateTransformTranslate({ 0.0f, MORE_MENU_TRANSLATE.ConvertToPx(), 0.0f });
        selectMenuInnerContext->UpdateOpacity(1.0);
    });

    modifier->SetOtherPointRadius(MAX_DIAMETER / 2.0f, noAnimation);
    modifier->SetHeadPointRadius(MAX_DIAMETER / 2.0f, noAnimation);
    modifier->SetLineEndOffset(false, noAnimation);

    auto toolbarHeight = textOverlayTheme->GetMenuToolbarHeight();
    auto frameSize =
        CalcSize(CalcLength(menuWidth.value_or(toolbarHeight.ConvertToPx())), CalcLength(toolbarHeight.ConvertToPx()));

    FinishCallback callback = [selectMenuInnerProperty, extensionProperty, backButtonProperty, id = containerId,
                                  weak = WeakClaim(this)]() {
        ContainerScope scope(id);
        selectMenuInnerProperty->UpdateVisibility(VisibleType::VISIBLE);
        extensionProperty->UpdateVisibility(VisibleType::GONE);
        backButtonProperty->UpdateVisibility(VisibleType::GONE);
        auto selectOverlay = weak.Upgrade();
        CHECK_NULL_VOID(selectOverlay);
        selectOverlay->UpdateMoreOrBackSymbolOptions(true, false);
        selectOverlay->SetAnimationStatus(false);
        auto child = selectOverlay->GetFirstChild();
        while (child) {
            if (child->GetTag() == "SelectMenuButton") {
                auto target = AceType::DynamicCast<FrameNode>(child);
                CHECK_NULL_VOID(target);
                target->OnAccessibilityEvent(AccessibilityEventType::REQUEST_FOCUS);
                break;
            }
            child = child->GetFirstChild();
        }
    };

    AnimationOption selectOption;
    selectOption.SetDuration(ANIMATION_DURATION1);
    selectOption.SetCurve(Curves::FRICTION);
    pipeline->FlushUITasks();
    AnimationUtils::OpenImplicitAnimation(selectOption, Curves::FRICTION, callback);
    UpdateMoreOrBackSymbolOptionsWithDelay();
    if (GreatOrEqual(pipeline->GetFontScale(), AGING_MIN_SCALE)) {
        auto geometryNode = selectMenu_->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        auto selectMenuHeight = geometryNode->GetFrameSize().Height();
        auto menuHeight = pattern->GetMenuHeight();
        frameSize = CalcSize(
            CalcLength(menuWidth.value_or(selectMenuHeight)), CalcLength(menuHeight.value_or(selectMenuHeight)));
    }
    selectProperty->UpdateUserDefinedIdealSize(frameSize);
    selectMenuInnerContext->UpdateTransformTranslate({ 0.0f, 0.0f, 0.0f });
    selectContext->UpdateOffset(OffsetT<Dimension>(0.0_px, 0.0_px));
    selectMenu_->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    pipeline->FlushUITasks();
    AnimationUtils::CloseImplicitAnimation();
    isDoingAnimation_ = true;
}

void SelectOverlayNode::UpdateMoreOrBackSymbolOptions(bool isAttachToMoreButton, bool isReplaceEffectEnable)
{
    if (!isMoreOrBackSymbolIcon_) {
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(textOverlayTheme);
    if (!moreOrBackSymbol_) {
        moreOrBackSymbol_ = BuildMoreOrBackSymbol();
    }
    auto button = isAttachToMoreButton ? backButton_ : moreButton_;
    if (button) {
        button->RemoveChild(moreOrBackSymbol_);
    }
    moreOrBackSymbol_->MountToParent(isAttachToMoreButton ? moreButton_ : backButton_);
    auto layoutProperty = moreOrBackSymbol_->GetLayoutProperty<TextLayoutProperty>();
    layoutProperty->UpdateSymbolSourceInfo(SymbolSourceInfo(
        isAttachToMoreButton ? textOverlayTheme->GetMoreSymbolId() : textOverlayTheme->GetBackSymbolId()
    ));
    auto symbolEffectOptions = layoutProperty->GetSymbolEffectOptionsValue(SymbolEffectOptions());
    symbolEffectOptions.SetIsTxtActive(isReplaceEffectEnable);
    layoutProperty->UpdateSymbolEffectOptions(symbolEffectOptions);
    moreOrBackSymbol_->MarkModifyDone();
    moreOrBackSymbol_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SelectOverlayNode::UpdateMoreOrBackSymbolOptionsWithDelay()
{
    if (!isMoreOrBackSymbolIcon_) {
        return;
    }
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(context);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto textOverlayTheme = context->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(textOverlayTheme);
    CancelableCallback<void()> symbolReplaceTask_;
    auto moreSymbolId = textOverlayTheme->GetMoreSymbolId();
    symbolReplaceTask_.Reset([moreSymbolId, weak = WeakClaim(this)] {
        auto selectOverlay = weak.Upgrade();
        CHECK_NULL_VOID(selectOverlay);
        if (!selectOverlay->moreOrBackSymbol_) {
            selectOverlay->moreOrBackSymbol_ = BuildMoreOrBackSymbol();
        }
        auto layoutProperty = selectOverlay->moreOrBackSymbol_->GetLayoutProperty<TextLayoutProperty>();
        layoutProperty->UpdateSymbolSourceInfo(SymbolSourceInfo(moreSymbolId));
        auto symbolEffectOptions = layoutProperty->GetSymbolEffectOptionsValue(SymbolEffectOptions());
        symbolEffectOptions.SetIsTxtActive(true);
        layoutProperty->UpdateSymbolEffectOptions(symbolEffectOptions);
        selectOverlay->moreOrBackSymbol_->MarkModifyDone();
        selectOverlay->moreOrBackSymbol_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    });
    taskExecutor->PostDelayedTask(
        symbolReplaceTask_, TaskExecutor::TaskType::UI, SYMBOL_ANIMATION_DELAY, "ArkUISelectOverlaySymbolReplace");
}

std::function<void()> SelectOverlayNode::GetDefaultOptionCallback()
{
    auto id = GetId();
    auto defaultOptionCallback = [overlayId = id, mainId = Container::CurrentIdSafelyWithCheck()]() {
        ContainerScope scope(mainId);
        auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(pipeline);
        auto overlayManager = pipeline->GetSelectOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        overlayManager->DestroySelectOverlay(overlayId);
        overlayManager->CloseSelectContentOverlay(overlayId, CloseReason::CLOSE_REASON_TOOL_BAR, false);
    };
    return defaultOptionCallback;
}

std::function<void(WeakPtr<NG::FrameNode>)> SelectOverlayNode::GetSymbolFunc(const std::string& symbolId)
{
    std::function<void(WeakPtr<NG::FrameNode>)> symbol = nullptr;
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, symbol);
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_RETURN(textOverlayTheme, symbol);

    auto symbolIdFunc = getSymbolIdMap.find(symbolId);
    if (symbolIdFunc != getSymbolIdMap.end()) {
        auto symbolId = (symbolIdFunc->second)(textOverlayTheme);
        auto symbolSize = textOverlayTheme->GetSymbolSize();
        symbol = [symbolId, symbolSize](WeakPtr<NG::FrameNode> weak) {
            auto node = weak.Upgrade();
            CHECK_NULL_VOID(node);
            auto symbolNode = Referenced::RawPtr(node);
            SymbolModelNG::InitialSymbol(symbolNode, symbolId);
            SymbolModelNG::SetFontSize(symbolNode, symbolSize);
        };
    }
    return symbol;
}

std::vector<OptionParam> SelectOverlayNode::GetDefaultOptionsParams(const std::shared_ptr<SelectOverlayInfo>& info)
{
    std::vector<OptionParam> params;
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, params);
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_RETURN(textOverlayTheme, params);
    auto iconTheme = pipeline->GetTheme<IconTheme>();
    auto defaultOptionCallback = GetDefaultOptionCallback();
    if (!isShowInDefaultMenu_[OPTION_INDEX_CUT]) {
        auto iconPath = iconTheme ? iconTheme->GetIconPath(InternalResource::ResourceId::IC_CUT_SVG) : "";
        params.emplace_back(textOverlayTheme->GetCutLabel(), iconPath,
            GetMenuCallbackWithContainerId(info->menuCallback.onCut), GetSymbolFunc(OH_DEFAULT_CUT));
    }
    if (!isShowInDefaultMenu_[OPTION_INDEX_COPY]) {
        auto iconPath = iconTheme ? iconTheme->GetIconPath(InternalResource::ResourceId::IC_COPY_SVG) : "";
        params.emplace_back(textOverlayTheme->GetCopyLabel(), iconPath,
            GetMenuCallbackWithContainerId(info->menuCallback.onCopy), GetSymbolFunc(OH_DEFAULT_COPY));
    }
    if (!isShowInDefaultMenu_[OPTION_INDEX_PASTE]) {
        auto iconPath = iconTheme ? iconTheme->GetIconPath(InternalResource::ResourceId::IC_PASTE_SVG) : "";
        params.emplace_back(textOverlayTheme->GetPasteLabel(), iconPath,
            GetMenuCallbackWithContainerId(info->menuCallback.onPaste), GetSymbolFunc(OH_DEFAULT_PASTE));
    }
    if (!isShowInDefaultMenu_[OPTION_INDEX_COPY_ALL]) {
        auto iconPath = iconTheme ? iconTheme->GetIconPath(InternalResource::ResourceId::IC_SELECT_ALL_SVG) : "";
        params.emplace_back(textOverlayTheme->GetSelectAllLabel(), iconPath,
            GetMenuCallbackWithContainerId(info->menuCallback.onSelectAll), GetSymbolFunc(OH_DEFAULT_SELECT_ALL));
    }
    if (!isShowInDefaultMenu_[OPTION_INDEX_TRANSLATE]) {
        auto iconPath = iconTheme ? iconTheme->GetIconPath(InternalResource::ResourceId::IC_TRANSLATE_SVG) : "";
        params.emplace_back(textOverlayTheme->GetTranslateLabel(), iconPath,
            GetMenuCallbackWithContainerId(info->menuCallback.onTranslate), GetSymbolFunc(OH_DEFAULT_TRANSLATE));
    }
    if (!isShowInDefaultMenu_[OPTION_INDEX_SHARE]) {
        auto iconPath = iconTheme ? iconTheme->GetIconPath(InternalResource::ResourceId::IC_SHARE_SVG) : "";
        params.emplace_back(textOverlayTheme->GetShareLabel(), iconPath,
            GetMenuCallbackWithContainerId(info->menuCallback.onShare), GetSymbolFunc(OH_DEFAULT_SHARE));
    }
    if (!isShowInDefaultMenu_[OPTION_INDEX_SEARCH]) {
        auto iconPath = iconTheme ? iconTheme->GetIconPath(InternalResource::ResourceId::IC_SEARCH_SVG) : "";
        params.emplace_back(textOverlayTheme->GetSearchLabel(), iconPath,
            GetMenuCallbackWithContainerId(info->menuCallback.onSearch), GetSymbolFunc(OH_DEFAULT_SEARCH));
    }
    GetFlexibleOptionsParams(info, params);
    return params;
}

void SelectOverlayNode::GetFlexibleOptionsParams(
    const std::shared_ptr<SelectOverlayInfo>& info, std::vector<OptionParam>& params)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto iconTheme = pipeline->GetTheme<IconTheme>();
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    if (!isShowInDefaultMenu_[OPTION_INDEX_CAMERA_INPUT]) {
        auto iconPath = iconTheme ? iconTheme->GetIconPath(InternalResource::ResourceId::IC_TAKEPHOTO_SVG) : "";
        auto iconName = textOverlayTheme ? textOverlayTheme->GetCameraInput() : "";
        params.emplace_back(iconName, iconPath, GetMenuCallbackWithContainerId(info->menuCallback.onCameraInput),
            GetSymbolFunc(OH_DEFAULT_CAMERA_INPUT));
    }
    if (!isShowInDefaultMenu_[OPTION_INDEX_AI_WRITE]) {
        auto iconPath = iconTheme ? iconTheme->GetIconPath(InternalResource::ResourceId::IC_AI_WRITE_SVG) : "";
        auto iconName = textOverlayTheme ? textOverlayTheme->GetAIWrite() : "";
        params.emplace_back(iconName, iconPath, GetMenuCallbackWithContainerId(info->menuCallback.onAIWrite),
            GetSymbolFunc(OH_DEFAULT_AI_WRITE));
    }
    if (!isShowInDefaultMenu_[OPTION_INDEX_AI_MENU]) {
        // use AI write, replace correct icon and symbolFunc according to needed
        auto iconPath = iconTheme ? iconTheme->GetIconPath(InternalResource::ResourceId::IC_AI_WRITE_SVG) : "";
        std::function<void(WeakPtr<NG::FrameNode>)> symbolFunc = GetSymbolFunc(OH_DEFAULT_AI_MENU_PHONE);
        auto iconName = textOverlayTheme ?
            textOverlayTheme->GetAiMenuOptionName(info->menuInfo.aiMenuOptionType) : "";
        params.emplace_back(iconName, iconPath, GetMenuCallbackWithContainerId(
            info->menuCallback.onAIMenuOption, iconName), symbolFunc);
        params.back().isAIMenuOption = true;
    }
}

void SelectOverlayNode::addMenuOptionItemsParams(
    std::vector<OptionParam>& params, const std::shared_ptr<SelectOverlayInfo>& info, int32_t index)
{
    auto mainId = Container::CurrentIdSafelyWithCheck();
    auto id = GetId();
    int32_t itemNum = 0;
    for (auto item : info->menuOptionItems) {
        if (itemNum >= index) {
            auto callback = [overlayId = id, func = std::move(item.action), mainId]() {
                ContainerScope scope(mainId);
                auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
                CHECK_NULL_VOID(pipeline);
                auto overlayManager = pipeline->GetSelectOverlayManager();
                CHECK_NULL_VOID(overlayManager);

                auto selectOverlay = overlayManager->GetSelectOverlayNode(overlayId);
                auto pattern = selectOverlay->GetPattern<SelectOverlayPattern>();
                auto selectInfo = pattern->GetSelectInfo();
                func(selectInfo);
                overlayManager->DestroySelectOverlay(overlayId);
                overlayManager->CloseSelectContentOverlay(overlayId, CloseReason::CLOSE_REASON_TOOL_BAR, false);
            };
            params.emplace_back(item.content.value_or("null"), item.icon.value_or(" "), callback);
        }
        itemNum++;
    }
}

void SelectOverlayNode::AddExtensionMenuOptions(const std::shared_ptr<SelectOverlayInfo>& info, int32_t index)
{
    CHECK_NULL_VOID(!extensionMenu_);
    std::vector<OptionParam> params = GetDefaultOptionsParams(info);
    addMenuOptionItemsParams(params, info, index);
    CreatExtensionMenu(std::move(params));
}

void SelectOverlayNode::CreatExtensionMenu(std::vector<OptionParam>&& params)
{
    CHECK_NULL_VOID(!params.empty());
    CHECK_NULL_VOID(backButton_);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto buttonId = backButton_->GetId();
    MenuParam menuParam;
    menuParam.placement = Placement::BOTTOM_RIGHT;
    menuParam.isShowInSubWindow = false;
    auto menuWrapper = MenuView::Create(
        std::move(params), buttonId, "SelectMoreOrBackButton", MenuType::SELECT_OVERLAY_EXTENSION_MENU, menuParam);
    CHECK_NULL_VOID(menuWrapper);
    auto menu = DynamicCast<FrameNode>(menuWrapper->GetChildAtIndex(0));
    CHECK_NULL_VOID(menu);
    menuWrapper->RemoveChild(menu);
    menuWrapper.Reset();

    // set click position to menu
    auto props = menu->GetLayoutProperty<MenuLayoutProperty>();
    auto context = menu->GetRenderContext();
    CHECK_NULL_VOID(props);
    props->UpdateMenuOffset(GetPageOffset());
    context->UpdateBackShadow(ShadowConfig::NoneShadow);
    auto menuPattern = menu->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto options = menuPattern->GetOptions();
    ElementRegister::GetInstance()->AddUINode(menu);
    menu->MountToParent(Claim(this));

    extensionMenu_ = menu;
    auto extensionMenuContext = extensionMenu_->GetRenderContext();
    CHECK_NULL_VOID(extensionMenuContext);

    extensionMenu_->GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);
    extensionMenuStatus_ = FrameNodeStatus::GONE;
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        extensionMenuContext->UpdateOpacity(0.0);
    }
    extensionMenuContext->UpdateTransformTranslate({ 0.0f, MORE_MENU_TRANSLATE.ConvertToPx(), 0.0f });
    extensionMenu_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    extensionMenu_->MarkModifyDone();
    menuPattern->SetSelectOverlayExtensionMenuShow();
}

void SelectOverlayNode::AddCreateMenuExtensionMenuOptions(const std::vector<MenuOptionsParam>& menuOptionItems,
    const std::shared_ptr<SelectOverlayInfo>& info, int32_t startIndex)
{
    std::vector<OptionParam> params;
    AddCreateMenuExtensionMenuParams(menuOptionItems, info, startIndex, params);
    CreatExtensionMenu(std::move(params));
}

std::function<void()> SelectOverlayNode::CreateExtensionMenuOptionCallback(int32_t id,
    const OnMenuItemCallback& onCreateCallback, const std::function<void()>& systemEvent, const MenuOptionsParam& item)
{
    auto callback = [onCreateCallback = onCreateCallback, systemEvent, item,
                        mainId = Container::CurrentIdSafelyWithCheck()]() {
        ContainerScope scope(mainId);
        auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(pipeline);
        auto overlayManager = pipeline->GetSelectOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        auto newOverlayManager = overlayManager->GetSelectContentOverlayManager();
        CHECK_NULL_VOID(newOverlayManager);
        bool result = false;
        if (onCreateCallback.onMenuItemClick) {
            MenuItemParam menuItem;
            menuItem.menuOptionsParam = item;
            int32_t start = -1;
            int32_t end = -1;
            if (onCreateCallback.textRangeCallback) {
                onCreateCallback.textRangeCallback(start, end);
            }
            menuItem.start = start;
            menuItem.end = end;
            result = onCreateCallback.onMenuItemClick(menuItem);
        }
        if (!result && systemEvent) {
            systemEvent();
        }
        if (!systemEvent && !result) {
            newOverlayManager->HideOptionMenu(true);
        }
    };
    return callback;
}

void SelectOverlayNode::AddCreateMenuExtensionMenuParams(const std::vector<MenuOptionsParam>& menuOptionItems,
    const std::shared_ptr<SelectOverlayInfo>& info, int32_t startIndex, std::vector<OptionParam>& params)
{
    CHECK_NULL_VOID(!extensionMenu_);
    const auto systemCallback = GetSystemCallback(info);
    auto id = GetId();
    int32_t itemNum = 0;
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(textOverlayTheme);
    for (auto item : menuOptionItems) {
        if (itemNum < startIndex) {
            itemNum++;
            continue;
        }
        std::function<void()> systemEvent;
        auto clickCallback = systemCallback.find(item.id);
        if (clickCallback != systemCallback.end()) {
            systemEvent = clickCallback->second;
        }
        auto callback = CreateExtensionMenuOptionCallback(id, info->onCreateCallback, systemEvent, item);
        auto content = GetItemContent(item.id, item.content.value_or(""));
        std::function<void(WeakPtr<NG::FrameNode>)> symbol = nullptr;
        auto symbolIdFunc = getSymbolIdMap.find(item.id);
        if (symbolIdFunc != getSymbolIdMap.end()) {
            auto symbolId = (symbolIdFunc->second)(textOverlayTheme);
            auto symbolSize = textOverlayTheme->GetSymbolSize();
            symbol = [symbolId, symbolSize](WeakPtr<NG::FrameNode> weak) {
                auto symbolNode = weak.Upgrade();
                SymbolModelNG::InitialSymbol(RawPtr(symbolNode), symbolId);
                SymbolModelNG::SetFontSize(RawPtr(symbolNode), symbolSize);
            };
        }
        auto param = OptionParam(content, GetSystemIconPath(item.id, item.icon.value_or(" ")), callback, symbol);
        if (item.id == OH_DEFAULT_PASTE) {
            param.isPasteOption = true;
        } else if (IsAIMenuOption(item.id)) {
            param.isAIMenuOption = true;
        }
        params.emplace_back(param);
        itemNum++;
    }
}

void SelectOverlayNode::CreateToolBar()
{
    auto pattern = GetPattern<SelectOverlayPattern>();
    CHECK_NULL_VOID(pattern);
    if (!pattern->CheckIfNeedMenu()) {
        return;
    }
    auto info = pattern->GetSelectOverlayInfo();
    if (info->menuInfo.menuBuilder) {
        CreateCustomSelectOverlay(info);
        return;
    }

    selectMenu_ = FrameNode::GetOrCreateFrameNode("SelectMenu", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    // Increase the node to realize the animation effect of font transparency and offset.
    selectMenuInner_ =
        FrameNode::GetOrCreateFrameNode("SelectMenuInner", ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    TAG_LOGI(AceLogTag::ACE_SELECT_OVERLAY, "CreateSelectOverlay default, id:%{public}d", selectMenu_->GetId());
    SelectMenuAndInnerInitProperty();
    // Menu initial state.
    InitSelectMenuStatus(pattern->GetMode(), info);

    selectMenuInner_->MountToParent(selectMenu_);
    selectMenu_->MountToParent(Claim(this));
    selectMenu_->MarkModifyDone();
}

void SelectOverlayNode::SelectMenuAndInnerInitProperty()
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(textOverlayTheme);
    auto shadowTheme = pipeline->GetTheme<ShadowTheme>();
    CHECK_NULL_VOID(shadowTheme);
    selectMenu_->GetLayoutProperty<LinearLayoutProperty>()->UpdateMainAxisAlign(FlexAlign::FLEX_END);
    selectMenu_->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_CONTENT);

    auto colorMode = pipeline->GetColorMode();
    selectMenu_->GetRenderContext()->UpdateBackShadow(shadowTheme->GetShadow(ShadowStyle::OuterDefaultMD, colorMode));
    selectMenu_->GetRenderContext()->UpdateBackgroundColor(textOverlayTheme->GetMenuBackgroundColor());
    selectMenu_->GetRenderContext()->SetClipToFrame(true);

    const auto& border = textOverlayTheme->GetMenuBorder();
    auto borderWidth = Dimension(border.Left().GetWidth().ConvertToPx());
    selectMenu_->GetLayoutProperty()->UpdateBorderWidth({ borderWidth, borderWidth, borderWidth, borderWidth,
        std::nullopt, std::nullopt });
    auto borderRadius = textOverlayTheme->GetMenuToolbarHeight() / 2.0f;
    selectMenu_->GetRenderContext()->UpdateBorderRadius({ borderRadius, borderRadius, borderRadius, borderRadius });
    auto borderColor = border.Left().GetColor();
    selectMenu_->GetRenderContext()->UpdateBorderColor({ borderColor, borderColor, borderColor, borderColor,
        std::nullopt, std::nullopt });
    auto borderStyle = border.Left().GetBorderStyle();
    selectMenu_->GetRenderContext()->UpdateBorderStyle({ borderStyle, borderStyle, borderStyle, borderStyle });

    selectMenuInner_->GetLayoutProperty<LinearLayoutProperty>()->UpdateMainAxisAlign(FlexAlign::FLEX_END);
    selectMenuInner_->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_CONTENT);

    selectMenuInner_->GetRenderContext()->UpdateOpacity(1.0);
    selectMenuInner_->GetRenderContext()->UpdateTransformTranslate({ 0.0f, 0.0f, 0.0f });
    const auto& padding = textOverlayTheme->GetMenuPadding();
    auto left = CalcLength(padding.Left().ConvertToPx());
    auto right = CalcLength(padding.Right().ConvertToPx());
    auto top = CalcLength(padding.Top().ConvertToPx());
    auto bottom = CalcLength(padding.Bottom().ConvertToPx());
    selectMenuInner_->GetLayoutProperty()->UpdatePadding({ left, right, top, bottom, std::nullopt, std::nullopt });
    SetSelectMenuInnerSize();
}

void SelectOverlayNode::InitSelectMenuStatus(
    SelectOverlayMode mode, const std::shared_ptr<SelectOverlayInfo>& info, bool changeOpacity)
{
    if (mode == SelectOverlayMode::MENU_ONLY) {
        // In SelectOverlayMode::MENU_ONLY mode, SelectOverlay controls the animation by self.
        if (changeOpacity) {
            SetFrameNodeOpacity(FrameNodeType::MENUONLY, 0.0f);
        }
        if (info->menuInfo.menuIsShow) {
            GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
            menuOnlyStatus_ = FrameNodeStatus::VISIBLE;
        } else {
            GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);
            menuOnlyStatus_ = FrameNodeStatus::GONE;
        }
    } else {
        CHECK_NULL_VOID(selectMenu_);
        // In SelectOverlayMode::ALL mode, SelectOverlay controls the animation through the children individually.
        if (changeOpacity) {
            selectMenu_->GetRenderContext()->UpdateOpacity(0.0);
        }
        if (info->menuInfo.menuIsShow) {
            selectMenu_->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
            selectMenuStatus_ = FrameNodeStatus::VISIBLE;
        } else {
            selectMenu_->GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);
            selectMenuStatus_ = FrameNodeStatus::GONE;
        }
    }
}

void SelectOverlayNode::GetDefaultButtonAndMenuWidth(float& maxWidth)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(textOverlayTheme);
    auto selectOverlayMaxWidth = OVERLAY_MAX_WIDTH.ConvertToPx();
    auto container = Container::Current();
    if (container && container->IsUIExtensionWindow()) {
        auto curWindowRect = pipeline->GetCurrentWindowRect();
        selectOverlayMaxWidth = std::min(selectOverlayMaxWidth, curWindowRect.Width());
    }

    const auto& menuPadding = textOverlayTheme->GetMenuPadding();

    auto backButtonWidth = textOverlayTheme->GetMenuToolbarHeight().ConvertToPx() - menuPadding.Top().ConvertToPx() -
                           menuPadding.Bottom().ConvertToPx();

    maxWidth =
        selectOverlayMaxWidth - menuPadding.Left().ConvertToPx() - menuPadding.Right().ConvertToPx() - backButtonWidth;
}

bool SelectOverlayNode::AddSystemDefaultOptions(float maxWidth, float& allocatedSize)
{
    auto info = GetPattern<SelectOverlayPattern>()->GetSelectOverlayInfo();
    memset_s(isShowInDefaultMenu_, sizeof(isShowInDefaultMenu_), 0, sizeof(isShowInDefaultMenu_));

    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, false);
    auto theme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_RETURN(theme, false);
    ShowCut(maxWidth, allocatedSize, info, theme->GetCutLabel());
    ShowCopy(maxWidth, allocatedSize, info, theme->GetCopyLabel());
    ShowPaste(maxWidth, allocatedSize, info, theme->GetPasteLabel());
    ShowCopyAll(maxWidth, allocatedSize, info, theme->GetSelectAllLabel());
    ShowTranslate(maxWidth, allocatedSize, info, theme->GetTranslateLabel());
    ShowShare(maxWidth, allocatedSize, info, theme->GetShareLabel());
    ShowSearch(maxWidth, allocatedSize, info, theme->GetSearchLabel());
    ShowCamera(maxWidth, allocatedSize, info, theme->GetCameraInput());
    ShowAIWrite(maxWidth, allocatedSize, info, theme->GetAIWrite());
    ShowAIMenuOptions(maxWidth, allocatedSize, info, theme->GetAiMenuOptionName(info->menuInfo.aiMenuOptionType));
    if (isDefaultBtnOverMaxWidth_) {
        isDefaultBtnOverMaxWidth_ = false;
        return true;
    }

    return false;
}

void SelectOverlayNode::ShowCut(
    float maxWidth, float& allocatedSize, std::shared_ptr<SelectOverlayInfo>& info, const std::string& label)
{
    if (info->menuInfo.showCut) {
        float buttonWidth = 0.0f;
        auto button = BuildButton(label, info->menuCallback.onCut, GetId(), buttonWidth);
        CHECK_NULL_VOID(button);
        if (GreatOrEqual(maxWidth - allocatedSize, buttonWidth)) {
            button->MountToParent(selectMenuInner_);
            allocatedSize += buttonWidth;
            isShowInDefaultMenu_[OPTION_INDEX_CUT] = true;
        } else {
            button.Reset();
            isDefaultBtnOverMaxWidth_ = true;
        }
    } else {
        isShowInDefaultMenu_[OPTION_INDEX_CUT] = true;
    }
}

void SelectOverlayNode::ShowCopy(
    float maxWidth, float& allocatedSize, std::shared_ptr<SelectOverlayInfo>& info, const std::string& label)
{
    if (info->menuInfo.showCopy) {
        CHECK_EQUAL_VOID(isDefaultBtnOverMaxWidth_, true);
        float buttonWidth = 0.0f;
        auto button = BuildButton(label, info->menuCallback.onCopy, GetId(), buttonWidth);
        CHECK_NULL_VOID(button);
        if (GreatOrEqual(maxWidth - allocatedSize, buttonWidth)) {
            button->MountToParent(selectMenuInner_);
            allocatedSize += buttonWidth;
            isShowInDefaultMenu_[OPTION_INDEX_COPY] = true;
        } else {
            button.Reset();
            isDefaultBtnOverMaxWidth_ = true;
        }
    } else {
        isShowInDefaultMenu_[OPTION_INDEX_COPY] = true;
    }
}

void SelectOverlayNode::ShowPaste(
    float maxWidth, float& allocatedSize, std::shared_ptr<SelectOverlayInfo>& info, const std::string& label)
{
    if (info->menuInfo.showPaste) {
        CHECK_EQUAL_VOID(isDefaultBtnOverMaxWidth_, true);
        float buttonWidth = 0.0f;
#ifdef OHOS_PLATFORM
        auto button = BuildPasteButton(info->menuCallback.onPaste, GetId(), buttonWidth);
#else
        auto button = BuildButton(label, info->menuCallback.onPaste, GetId(), buttonWidth);
#endif
        CHECK_NULL_VOID(button);
        if (GreatOrEqual(maxWidth - allocatedSize, buttonWidth)) {
            button->MountToParent(selectMenuInner_);
            allocatedSize += buttonWidth;
            isShowInDefaultMenu_[OPTION_INDEX_PASTE] = true;
        } else {
            button.Reset();
            isDefaultBtnOverMaxWidth_ = true;
        }
    } else {
        isShowInDefaultMenu_[OPTION_INDEX_PASTE] = true;
    }
}

void SelectOverlayNode::ShowCopyAll(
    float maxWidth, float& allocatedSize, std::shared_ptr<SelectOverlayInfo>& info, const std::string& label)
{
    if (info->menuInfo.showCopyAll) {
        CHECK_EQUAL_VOID(isDefaultBtnOverMaxWidth_, true);
        float buttonWidth = 0.0f;
        auto button = BuildButton(label, info->menuCallback.onSelectAll, GetId(), buttonWidth);
        CHECK_NULL_VOID(button);
        if (GreatOrEqual(maxWidth - allocatedSize, buttonWidth)) {
            button->MountToParent(selectMenuInner_);
            allocatedSize += buttonWidth;
            isShowInDefaultMenu_[OPTION_INDEX_COPY_ALL] = true;
        } else {
            button.Reset();
            isDefaultBtnOverMaxWidth_ = true;
        }
    } else {
        isShowInDefaultMenu_[OPTION_INDEX_COPY_ALL] = true;
    }
}

void SelectOverlayNode::ShowTranslate(
    float maxWidth, float& allocatedSize, std::shared_ptr<SelectOverlayInfo>& info, const std::string& label)
{
    if (!IsShowTranslateOnTargetAPIVersion() || !TextSystemMenu::IsShowTranslate()) {
        isShowInDefaultMenu_[OPTION_INDEX_TRANSLATE] = true;
        return;
    }
    if (info->menuInfo.showTranslate) {
        CHECK_EQUAL_VOID(isDefaultBtnOverMaxWidth_, true);
        float buttonWidth = 0.0f;
        auto button = BuildButton(label, info->menuCallback.onTranslate, GetId(), buttonWidth);
        CHECK_NULL_VOID(button);
        if (GreatOrEqual(maxWidth - allocatedSize, buttonWidth)) {
            button->MountToParent(selectMenuInner_);
            allocatedSize += buttonWidth;
            isShowInDefaultMenu_[OPTION_INDEX_TRANSLATE] = true;
        } else {
            button.Reset();
            isDefaultBtnOverMaxWidth_ = true;
        }
    } else {
        isShowInDefaultMenu_[OPTION_INDEX_TRANSLATE] = true;
    }
}

void SelectOverlayNode::ShowSearch(
    float maxWidth, float& allocatedSize, std::shared_ptr<SelectOverlayInfo>& info, const std::string& label)
{
    if (!IsShowOnTargetAPIVersion() || !TextSystemMenu::IsShowSearch()) {
        isShowInDefaultMenu_[OPTION_INDEX_SEARCH] = true;
        return;
    }
    if (info->menuInfo.showSearch) {
        CHECK_EQUAL_VOID(isDefaultBtnOverMaxWidth_, true);
        float buttonWidth = 0.0f;
        auto button = BuildButton(label, info->menuCallback.onSearch, GetId(), buttonWidth);
        CHECK_NULL_VOID(button);
        if (GreatOrEqual(maxWidth - allocatedSize, buttonWidth)) {
            button->MountToParent(selectMenuInner_);
            allocatedSize += buttonWidth;
            isShowInDefaultMenu_[OPTION_INDEX_SEARCH] = true;
        } else {
            button.Reset();
            isDefaultBtnOverMaxWidth_ = true;
        }
    } else {
        isShowInDefaultMenu_[OPTION_INDEX_SEARCH] = true;
    }
}

void SelectOverlayNode::ShowShare(
    float maxWidth, float& allocatedSize, std::shared_ptr<SelectOverlayInfo>& info, const std::string& label)
{
    if (!IsShowOnTargetAPIVersion() || !TextSystemMenu::IsShowShare()) {
        isShowInDefaultMenu_[OPTION_INDEX_SHARE] = true;
        return;
    }
    if (info->menuInfo.showShare) {
        CHECK_EQUAL_VOID(isDefaultBtnOverMaxWidth_, true);
        float buttonWidth = 0.0f;
        auto button = BuildButton(label, info->menuCallback.onShare, GetId(), buttonWidth);
        CHECK_NULL_VOID(button);
        if (GreatOrEqual(maxWidth - allocatedSize, buttonWidth)) {
            button->MountToParent(selectMenuInner_);
            allocatedSize += buttonWidth;
            isShowInDefaultMenu_[OPTION_INDEX_SHARE] = true;
        } else {
            button.Reset();
            isDefaultBtnOverMaxWidth_ = true;
        }
    } else {
        isShowInDefaultMenu_[OPTION_INDEX_SHARE] = true;
    }
}

void SelectOverlayNode::ShowAIWrite(
    float maxWidth, float& allocatedSize, std::shared_ptr<SelectOverlayInfo>& info, const std::string& label)
{
    if (info->menuInfo.showAIWrite && TextSystemMenu::IsShowAIWriter()) {
        CHECK_EQUAL_VOID(isDefaultBtnOverMaxWidth_, true);
        float buttonWidth = 0.0f;
        auto button = BuildButton(label, info->menuCallback.onAIWrite, GetId(), buttonWidth);
        CHECK_NULL_VOID(button);
        if (GreatOrEqual(maxWidth - allocatedSize, buttonWidth)) {
            button->MountToParent(selectMenuInner_);
            allocatedSize += buttonWidth;
            isShowInDefaultMenu_[OPTION_INDEX_AI_WRITE] = true;
        } else {
            button.Reset();
            isDefaultBtnOverMaxWidth_ = true;
        }
    } else {
        isShowInDefaultMenu_[OPTION_INDEX_AI_WRITE] = true;
    }
}

void SelectOverlayNode::ShowCamera(
    float maxWidth, float& allocatedSize, std::shared_ptr<SelectOverlayInfo>& info, const std::string& label)
{
    if (info->menuInfo.showCameraInput && TextSystemMenu::IsShowCameraInput()) {
        CHECK_EQUAL_VOID(isDefaultBtnOverMaxWidth_, true);
        float buttonWidth = 0.0f;
        auto button = BuildButton(label, info->menuCallback.onCameraInput, GetId(), buttonWidth);
        CHECK_NULL_VOID(button);
        if (GreatOrEqual(maxWidth - allocatedSize, buttonWidth)) {
            button->MountToParent(selectMenuInner_);
            allocatedSize += buttonWidth;
            isShowInDefaultMenu_[OPTION_INDEX_CAMERA_INPUT] = true;
        } else {
            button.Reset();
            isDefaultBtnOverMaxWidth_ = true;
        }
    } else {
        isShowInDefaultMenu_[OPTION_INDEX_CAMERA_INPUT] = true;
    }
}

void SelectOverlayNode::ShowAIMenuOptions(
    float maxWidth, float& allocatedSize, std::shared_ptr<SelectOverlayInfo>& info, const std::string& label)
{
    if (IsShowAIMenuOption(info->menuInfo.aiMenuOptionType)) {
        CHECK_EQUAL_VOID(isDefaultBtnOverMaxWidth_, true);
        float buttonWidth = 0.0f;
        auto button = BuildButton(label, info->menuCallback.onAIMenuOption, GetId(), buttonWidth,
            SelectOverlayMenuButtonType::AIBUTTON);
        CHECK_NULL_VOID(button);
        if (GreatOrEqual(maxWidth - allocatedSize, buttonWidth)) {
            button->MountToParent(selectMenuInner_);
            allocatedSize += buttonWidth;
            isShowInDefaultMenu_[OPTION_INDEX_AI_MENU] = true;
        } else {
            button.Reset();
            isDefaultBtnOverMaxWidth_ = true;
        }
    } else {
        isShowInDefaultMenu_[OPTION_INDEX_AI_MENU] = true;
    }
}

bool SelectOverlayNode::IsShowOnTargetAPIVersion()
{
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) &&
        LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        return false;
    }
    return true;
}

bool SelectOverlayNode::IsShowTranslateOnTargetAPIVersion()
{
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) &&
        LessThanAPITargetVersion(PlatformVersion::VERSION_FIFTEEN)) {
        return false;
    }
    return true;
}

void SelectOverlayNode::AddMenuItemByCreateMenuCallback(const std::shared_ptr<SelectOverlayInfo>& info, float maxWidth)
{
    CHECK_NULL_VOID(info);
    CHECK_NULL_VOID(info->onCreateCallback.onCreateMenuCallback);
    auto systemItemParams = GetSystemMenuItemParams(info);
    auto createMenuItems = info->onCreateCallback.onCreateMenuCallback(systemItemParams);
    auto extensionOptionStartIndex = AddCreateMenuItems(createMenuItems, info, maxWidth) + 1;
    if (backButton_) {
        isExtensionMenu_ = false;
        RemoveChild(backButton_);
        backButton_.Reset();
    }
    if (extensionMenu_) {
        RemoveChild(extensionMenu_);
        extensionMenu_.Reset();
    }
    if (static_cast<size_t>(extensionOptionStartIndex) < createMenuItems.size()) {
        moreButton_ = BuildMoreOrBackButton(GetId(), true);
        moreButton_->MountToParent(selectMenuInner_);
        CHECK_NULL_VOID(moreButton_);
        isMoreOrBackSymbolIcon_ = Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE);
        if (isMoreOrBackSymbolIcon_) {
            moreOrBackSymbol_ = BuildMoreOrBackSymbol();
            moreOrBackSymbol_->MountToParent(moreButton_);
        }
        // add back button
        if (!backButton_) {
            backButton_ = BuildMoreOrBackButton(GetId(), false);
            CHECK_NULL_VOID(backButton_);
            backButton_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
            backButton_->GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);
            backButton_->MountToParent(Claim(this));
        }
    }
    AddCreateMenuExtensionMenuOptions(createMenuItems, info, extensionOptionStartIndex);
}

int32_t SelectOverlayNode::AddCreateMenuItems(
    const std::vector<NG::MenuOptionsParam>& menuItems, const std::shared_ptr<SelectOverlayInfo>& info, float maxWidth)
{
    auto id = GetId();
    const auto systemCallback = GetSystemCallback(info);
    float remainderWidth = maxWidth;
    int32_t index = -1;
    for (auto item : menuItems) {
        auto callback = systemCallback.find(item.id);
        RefPtr<FrameNode> button;
        if (item.id == "OH_DEFAULT_PASTE") {
#ifdef OHOS_PLATFORM
            float buttonWidth = 0.0f;
            button = CreatePasteButtonForCreateMenu(info, id, item, buttonWidth);
            if (!button) {
                continue;
            }
            if (GreatOrEqual(remainderWidth, buttonWidth)) {
                button->MountToParent(selectMenuInner_);
                remainderWidth -= buttonWidth;
                index++;
            } else {
                button.Reset();
                return index;
            }
#else
            button = BuildCreateMenuItemButton(item, callback != systemCallback.end() ? callback->second : nullptr,
                info->onCreateCallback, id, remainderWidth);
            if (button) {
                button->MountToParent(selectMenuInner_);
                index++;
            } else {
                break;
            }
#endif
        } else {
            item.isFirstOption = index == -1;
            item.content = GetItemContent(item.id, item.content.value_or(""), info);

            button = BuildCreateMenuItemButton(item, callback != systemCallback.end() ? callback->second : nullptr,
                info->onCreateCallback, id, remainderWidth);
            if (button) {
                button->MountToParent(selectMenuInner_);
                index++;
            } else {
                break;
            }
        }
    }
    return index;
}

const std::vector<MenuItemParam> SelectOverlayNode::GetSystemMenuItemParams(
    const std::shared_ptr<SelectOverlayInfo>& info)
{
    std::vector<MenuItemParam> systemItemParams;
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, systemItemParams);
    auto theme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_RETURN(theme, systemItemParams);
    auto isUsingMouse = info->isUsingMouse;
    auto menuInfo = info->menuInfo;
    AddMenuItemParamIf(
        menuInfo.showCopy || isUsingMouse, OH_DEFAULT_COPY, theme->GetCopyLabel(), systemItemParams);
    AddMenuItemParamIf(
        menuInfo.showPaste || isUsingMouse, OH_DEFAULT_PASTE, theme->GetPasteLabel(), systemItemParams);
    AddMenuItemParamIf(menuInfo.showCut || isUsingMouse, OH_DEFAULT_CUT, theme->GetCutLabel(), systemItemParams);
    AddMenuItemParamIf(menuInfo.showCopyAll || isUsingMouse, OH_DEFAULT_SELECT_ALL, theme->GetSelectAllLabel(),
        systemItemParams);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_FIFTEEN) &&
        TextSystemMenu::IsShowTranslate()) {
        AddMenuItemParamIf(menuInfo.showTranslate || isUsingMouse, OH_DEFAULT_TRANSLATE,
            theme->GetTranslateLabel(), systemItemParams);
    }
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        AddMenuItemParamIf((menuInfo.showShare || isUsingMouse) && TextSystemMenu::IsShowShare(),
            OH_DEFAULT_SHARE, theme->GetShareLabel(), systemItemParams);
        AddMenuItemParamIf((menuInfo.showSearch || isUsingMouse) && TextSystemMenu::IsShowSearch(),
            OH_DEFAULT_SEARCH, theme->GetSearchLabel(), systemItemParams);
    }
    AddMenuItemParamIf(menuInfo.showCameraInput && TextSystemMenu::IsShowCameraInput(),
        OH_DEFAULT_CAMERA_INPUT, theme->GetCameraInput(), systemItemParams);
    AddMenuItemParamIf(menuInfo.showAIWrite && TextSystemMenu::IsShowAIWriter(), OH_DEFAULT_AI_WRITE,
        theme->GetAIWrite(), systemItemParams);

    if (IsShowAIMenuOption(info->menuInfo.aiMenuOptionType)) {
        auto findIter = AI_TYPE_ID_MAP.find(info->menuInfo.aiMenuOptionType);
        AddMenuItemParamIf(true, findIter->second.first,
            theme->GetAiMenuOptionName(info->menuInfo.aiMenuOptionType), systemItemParams);
    }
    return systemItemParams;
}

void SelectOverlayNode::AddMenuItemParamIf(
    bool condition, const std::string& menuId, const std::string& menuButton, std::vector<MenuItemParam>& items)
{
    if (condition) {
        MenuOptionsParam menuOptionsParam;
        menuOptionsParam.id = menuId;
        menuOptionsParam.content = menuButton;
        MenuItemParam param;
        param.menuOptionsParam = menuOptionsParam;
        items.emplace_back(param);
    }
}

void SelectOverlayNode::MenuOnlyStatusChange(const std::shared_ptr<SelectOverlayInfo>& info, bool noAnimation)
{
    auto pattern = GetPattern<SelectOverlayPattern>();
    CHECK_NULL_VOID(pattern);
    bool isHideMenu = info->menuInfo.menuDisable || !info->menuInfo.menuIsShow;
    if (isHideMenu) {
        (noAnimation) ? HideMenuOnlyImmediately()
                      : ExecuteOverlayStatus(FrameNodeType::MENUONLY, FrameNodeTrigger::HIDE);
        if (pattern->GetIsMenuShowInSubWindow()) {
            pattern->DeleteHotAreas();
        }
    } else {
        ExecuteOverlayStatus(FrameNodeType::MENUONLY, FrameNodeTrigger::SHOW);
    }
    FireCustomMenuChangeEvent(!isHideMenu);
    if (pattern->GetIsMenuShowInSubWindow() && isExtensionMenu_ && extensionMenu_) {
        auto pipeline = extensionMenu_->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto containerId = pipeline->GetInstanceId();
        ContainerScope scope(containerId);
        extensionMenu_->MarkModifyDone();
        extensionMenu_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        pipeline->FlushUITasks();
    }
}

void SelectOverlayNode::HideMenuOnlyImmediately()
{
    SetFrameNodeStatus(FrameNodeType::MENUONLY, FrameNodeStatus::GONE);
    SetFrameNodeVisibility(FrameNodeType::MENUONLY, VisibleType::GONE);
    SetFrameNodeOpacity(FrameNodeType::MENUONLY, 0.0f);
}

void SelectOverlayNode::UpdateToolBar(bool menuItemChanged, bool noAnimation)
{
    auto pattern = GetPattern<SelectOverlayPattern>();
    CHECK_NULL_VOID(pattern);
    if (!pattern->CheckIfNeedMenu()) {
        NotifyUpdateToolBar(menuItemChanged, noAnimation);
        MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        return;
    }
    auto info = pattern->GetSelectOverlayInfo();
    if (menuItemChanged && info->menuInfo.menuBuilder == nullptr) {
        UpdateMenuInner(info, noAnimation);
    }
    selectMenu_->MarkModifyDone();
    MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    if (selectMenuInner_) {
        selectMenuInner_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
    auto mode = pattern->GetMode();
    // In SelectOverlayMode::MENU_ONLY mode, SelectOverlay controls the animation by self.
    if (mode == SelectOverlayMode::MENU_ONLY) {
        MenuOnlyStatusChange(info, noAnimation);
        return;
    }
    if (info->menuInfo.menuDisable || !info->menuInfo.menuIsShow) {
        (noAnimation) ? HideFrameNodeImmediately(FrameNodeType::SELECTMENU)
                      : ExecuteOverlayStatus(FrameNodeType::SELECTMENU, FrameNodeTrigger::HIDE);
        FireCustomMenuChangeEvent(false);
    } else {
        ExecuteOverlayStatus(FrameNodeType::SELECTMENU, FrameNodeTrigger::SHOW);
        FireCustomMenuChangeEvent(true);
    }

    if (isExtensionMenu_ && extensionMenu_) {
        auto nodeTrigger = FrameNodeTrigger::SHOW;
        if (info->menuInfo.menuDisable || !info->menuInfo.menuIsShow) {
            nodeTrigger = FrameNodeTrigger::HIDE;
        }
        ExecuteOverlayStatus(FrameNodeType::EXTENSIONMENU, nodeTrigger);
        if (backButton_) {
            ExecuteOverlayStatus(FrameNodeType::BACKBUTTON, nodeTrigger);
        }
        extensionMenu_->MarkModifyDone();
        if (backButton_) {
            backButton_->MarkModifyDone();
        }
    }
}

void SelectOverlayNode::UpdateMenuOptions(const std::shared_ptr<SelectOverlayInfo>& info)
{
    float maxWidth = 0.0f;
    GetDefaultButtonAndMenuWidth(maxWidth);
    if (info->onCreateCallback.onCreateMenuCallback) {
        AddMenuItemByCreateMenuCallback(info, maxWidth);
        return;
    }
    float allocatedSize = 0.0f;
    bool isDefaultOverMaxWidth = AddSystemDefaultOptions(maxWidth, allocatedSize);
    auto extensionOptionStartIndex = -1;
    LandscapeMenuAddMenuOptions(
        info->menuOptionItems, isDefaultOverMaxWidth, maxWidth, allocatedSize, extensionOptionStartIndex);

    if (backButton_) {
        isExtensionMenu_ = false;
        RemoveChild(backButton_);
        backButton_.Reset();
    }
    if (extensionMenu_) {
        RemoveChild(extensionMenu_);
        extensionMenu_.Reset();
    }
    if (extensionOptionStartIndex != -1 || isDefaultOverMaxWidth) {
        moreButton_ = BuildMoreOrBackButton(GetId(), true);
        CHECK_NULL_VOID(moreButton_);
        moreButton_->MountToParent(selectMenuInner_);
        isMoreOrBackSymbolIcon_ = Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE);
        if (isMoreOrBackSymbolIcon_) {
            moreOrBackSymbol_ = BuildMoreOrBackSymbol();
            moreOrBackSymbol_->MountToParent(moreButton_);
        }
        if (!backButton_) {
            backButton_ = BuildMoreOrBackButton(GetId(), false);
            CHECK_NULL_VOID(backButton_);
            backButton_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
            backButton_->GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);
            backButton_->MountToParent(Claim(this));
        }
    }
    AddExtensionMenuOptions(info, extensionOptionStartIndex);
}

void SelectOverlayNode::UpdateMenuInner(const std::shared_ptr<SelectOverlayInfo>& info, bool noAnimation)
{
    CHECK_NULL_VOID(selectMenuInner_);
    selectMenuInner_->Clean();
    auto selectMenuLayoutProperty = selectMenuInner_->GetLayoutProperty();
    CHECK_NULL_VOID(selectMenuLayoutProperty);
    selectMenuLayoutProperty->ClearUserDefinedIdealSize(true, true);
    SetSelectMenuInnerSize();
    selectMenuInner_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    if (isExtensionMenu_) {
        MoreOrBackAnimation(false, noAnimation);
    }
    auto selectProperty = selectMenu_->GetLayoutProperty();
    CHECK_NULL_VOID(selectProperty);
    auto pipeline = GetContext();
    bool clearIdealHeight = pipeline && GreatOrEqual(pipeline->GetFontScale(), AGING_MIN_SCALE);
    selectProperty->ClearUserDefinedIdealSize(true, clearIdealHeight);
    UpdateMenuOptions(info);
}

void SelectOverlayNode::SetSelectMenuInnerSize()
{
    CHECK_NULL_VOID(selectMenuInner_);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(textOverlayTheme);
    if (LessNotEqual(pipeline->GetFontScale(), AGING_MIN_SCALE)) {
        selectMenuInner_->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            { std::nullopt, CalcLength(textOverlayTheme->GetMenuToolbarHeight()) });
    } else {
        selectMenuInner_->GetLayoutProperty()->UpdateUserDefinedIdealSize({ std::nullopt, std::nullopt });
    }
}

void SelectOverlayNode::LandscapeMenuAddMenuOptions(const std::vector<MenuOptionsParam>& menuOptionItems,
    bool isDefaultOverMaxWidth, float maxWidth, float allocatedSize, int32_t& extensionOptionStartIndex)
{
    if (isDefaultOverMaxWidth) {
        return;
    }
    auto itemNum = -1;
    for (auto item : menuOptionItems) {
        itemNum++;
        float extensionOptionWidth = 0.0f;
        auto button = BuildButton(item, GetId(), extensionOptionWidth);
        CHECK_NULL_VOID(button);
        allocatedSize += extensionOptionWidth;
        if (GreatNotEqual(allocatedSize, maxWidth)) {
            button.Reset();
            extensionOptionStartIndex = itemNum;
            break;
        }
        button->MountToParent(selectMenuInner_);
    }
}

std::pair<std::vector<MenuOptionsParam>, bool> SelectOverlayNode::HandleCollaborationMenuItem(
    const std::vector<MenuOptionsParam>& params)
{
    std::vector<MenuOptionsParam> newParams;
    bool needCollaboration = false;
    for (const auto& item : params) {
        if (item.id == OH_DEFAULT_COLLABORATION_SERVICE) {
            needCollaboration = true;
            continue;
        }
        newParams.push_back(item);
    }
    return { newParams, needCollaboration };
}

RefPtr<FrameNode> SelectOverlayNode::CreateMenuNode(const std::shared_ptr<SelectOverlayInfo>& info)
{
    RefPtr<FrameNode> menuWrapper = nullptr;
    std::vector<OptionParam> params;
    if (info->onCreateCallback.onCreateMenuCallback) {
        auto systemItemParams = GetSystemMenuItemParams(info);
        auto createMenuItems = info->onCreateCallback.onCreateMenuCallback(systemItemParams);
        params = GetCreateMenuOptionsParams(createMenuItems, info, 0);
    } else {
        params = GetOptionsParams(info);
    }
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_RETURN(textOverlayTheme, nullptr);
    menuWrapper = GetMenuWrapper(params, textOverlayTheme);
    CHECK_NULL_RETURN(menuWrapper, nullptr);
    ExpandedMenuPluginLoader::GetInstance().CreateServiceCollaborationMenu(menuWrapper, info);
    auto menu = DynamicCast<FrameNode>(menuWrapper->GetChildAtIndex(0));
    // set click position to menu
    CHECK_NULL_RETURN(menu, nullptr);
    auto props = menu->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_RETURN(props, nullptr);
    OffsetF pageOffset;
    auto windowManager = pipeline->GetWindowManager();
    auto isContainerModal = pipeline->GetWindowModal() == WindowModal::CONTAINER_MODAL && windowManager &&
                            windowManager->GetWindowMode() == WindowMode::WINDOW_MODE_FLOATING;
    if (isContainerModal) {
        pageOffset = GetPageOffset();
        TAG_LOGD(AceLogTag::ACE_SELECT_OVERLAY, "CreateMenuNode pageOffset:%{public}s", pageOffset.ToString().c_str());
    }
    props->UpdateMenuOffset(info->rightClickOffset + pageOffset);

    menu->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    ElementRegister::GetInstance()->AddUINode(menu);

    auto gestureEventHub = menuWrapper->GetOrCreateGestureEventHub();
    if (gestureEventHub) {
        gestureEventHub->SetHitTestMode(HitTestMode::HTMDEFAULT);
    }
    return menuWrapper;
}

bool SelectOverlayNode::IsInSelectedOrSelectOverlayArea(const PointF& point)
{
    auto pattern = GetPattern<SelectOverlayPattern>();
    CHECK_NULL_RETURN(pattern, false);

    std::vector<RectF> rects;
    auto offset = GetGeometryNode() ? GetGeometryNode()->GetFrameOffset() : OffsetF();
    rects.emplace_back(pattern->GetHandleRegion(true) + offset);
    rects.emplace_back(pattern->GetHandleRegion(false) + offset);
    if (selectMenu_ && selectMenu_->GetGeometryNode()) {
        rects.emplace_back(selectMenu_->GetGeometryNode()->GetFrameRect() + offset);
    }
    if (extensionMenu_ && extensionMenu_->GetGeometryNode()) {
        rects.emplace_back(extensionMenu_->GetGeometryNode()->GetFrameRect() + offset);
    }

    if (pattern->IsCustomMenu()) {
        for (auto& child : pattern->GetHost()->GetChildren()) {
            auto childFrameNode = DynamicCast<FrameNode>(child);
            if (!childFrameNode) {
                continue;
            }
            rects.emplace_back(childFrameNode->GetGeometryNode()->GetFrameRect() + offset);
        }
    }

    for (const auto& rect : rects) {
        if (rect.IsInRegion(point)) {
            return true;
        }
    }
    return false;
}

void SelectOverlayNode::SetClosedByGlobalEvent(bool closedByGlobalEvent)
{
    auto selectOverlayPattern = GetPattern<SelectOverlayPattern>();
    CHECK_NULL_VOID(selectOverlayPattern);
    selectOverlayPattern->SetClosedByGlobalTouchEvent(closedByGlobalEvent);
}

void SelectOverlayNode::ShowSelectOverlay(bool animation)
{
    auto pattern = GetPattern<SelectOverlayPattern>();
    CHECK_NULL_VOID(pattern);

    // In SelectOverlayMode::MENU_ONLY mode, SelectOverlay controls the animation by self.
    if (pattern->GetMode() == SelectOverlayMode::MENU_ONLY) {
        if (animation) {
            AnimationOption option;
            option.SetDuration(MENU_SHOW_ANIMATION_DURATION);
            option.SetCurve(Curves::SHARP);
            AnimationUtils::Animate(option, [weak = WeakClaim(this), id = Container::CurrentId()]() {
                ContainerScope scope(id);
                auto node = weak.Upgrade();
                CHECK_NULL_VOID(node);
                node->SetFrameNodeOpacity(FrameNodeType::MENUONLY, 1.0f);
            });
        } else {
            SetFrameNodeOpacity(FrameNodeType::MENUONLY, 1.0f);
        }
        return;
    }
    if (animation) {
        AnimationOption option;
        option.SetDuration(MENU_SHOW_ANIMATION_DURATION);
        option.SetCurve(Curves::SHARP);

        AnimationUtils::Animate(option, [weak = WeakClaim(this), id = Container::CurrentId()]() {
            ContainerScope scope(id);
            auto node = weak.Upgrade();
            CHECK_NULL_VOID(node);
            node->SetSelectMenuOpacity(1.0);
            node->SetExtensionMenuOpacity(1.0);
            node->SetBackButtonOpacity(1.0);
        });
    } else {
        SetSelectMenuOpacity(1.0);
        SetExtensionMenuOpacity(1.0);
        SetBackButtonOpacity(1.0);
    }
    pattern->SetHasShowAnimation(animation);
}

void SelectOverlayNode::HideSelectOverlay(const std::function<void()>& callback)
{
    AnimationOption handleOption;
    handleOption.SetDuration(HANDLE_ANIMATION_DURATION);
    handleOption.SetCurve(Curves::SHARP);

    AnimationUtils::Animate(handleOption, [weak = WeakClaim(this), id = Container::CurrentId()]() {
        ContainerScope scope(id);
        auto node = weak.Upgrade();
        CHECK_NULL_VOID(node);
        auto pattern = node->GetPattern<SelectOverlayPattern>();
        CHECK_NULL_VOID(pattern);
        auto contentModifier = pattern->GetContentModifier();
        CHECK_NULL_VOID(contentModifier);
        contentModifier->SetHandleOpacity(0.0);
    });

    AnimationOption overlayOption;
    overlayOption.SetDuration(MENU_HIDE_ANIMATION_DURATION);
    overlayOption.SetCurve(Curves::SHARP);
    auto pattern = GetPattern<SelectOverlayPattern>();
    CHECK_NULL_VOID(pattern);

    // In SelectOverlayMode::MENU_ONLY mode, SelectOverlay controls the animation by self.
    if (pattern->GetMode() == SelectOverlayMode::MENU_ONLY) {
        AnimationUtils::Animate(
            overlayOption,
            [weak = WeakClaim(this), id = Container::CurrentId()]() {
                ContainerScope scope(id);
                auto node = weak.Upgrade();
                CHECK_NULL_VOID(node);
                node->SetFrameNodeOpacity(FrameNodeType::MENUONLY, 0.0f);
            },
            callback);
        return;
    }

    AnimationUtils::Animate(
        overlayOption,
        [weak = WeakClaim(this), id = Container::CurrentId()]() {
            ContainerScope scope(id);
            auto node = weak.Upgrade();
            CHECK_NULL_VOID(node);
            node->SetSelectMenuOpacity(0.0);
            node->SetExtensionMenuOpacity(0.0);
            node->SetBackButtonOpacity(0.0);
            auto pattern = node->GetPattern<SelectOverlayPattern>();
            CHECK_NULL_VOID(pattern);
            auto overlayModifier = pattern->GetOverlayModifier();
            CHECK_NULL_VOID(overlayModifier);
            overlayModifier->SetCirclesAndBackArrowOpacity(0.0);
        },
        callback);
}

void SelectOverlayNode::ExecuteOverlayStatus(FrameNodeType type, FrameNodeTrigger trigger)
{
    FrameNodeStatus status = FrameNodeStatus::VISIBLE;
    switch (type) {
        case FrameNodeType::SELECTMENU:
            status = selectMenuStatus_;
            break;
        case FrameNodeType::EXTENSIONMENU:
            status = extensionMenuStatus_;
            break;
        case FrameNodeType::BACKBUTTON:
            status = backButtonStatus_;
            break;
        case FrameNodeType::MENUONLY:
            status = menuOnlyStatus_;
            break;
        default:
            break;
    }

    auto stateFuncIter = stateFuncs_.find(status);
    if (stateFuncIter != stateFuncs_.end()) {
        auto stateFunc = stateFuncIter->second;
        CHECK_NULL_VOID(stateFunc);
        (this->*stateFunc)(type, trigger);
    }
}

void SelectOverlayNode::SetFrameNodeStatus(FrameNodeType type, FrameNodeStatus status)
{
    switch (type) {
        case FrameNodeType::SELECTMENU:
            selectMenuStatus_ = status;
            break;
        case FrameNodeType::EXTENSIONMENU:
            extensionMenuStatus_ = status;
            break;
        case FrameNodeType::BACKBUTTON:
            backButtonStatus_ = status;
            break;
        case FrameNodeType::MENUONLY:
            menuOnlyStatus_ = status;
            break;
        default:
            break;
    }
}

void SelectOverlayNode::SetFrameNodeVisibility(FrameNodeType type, VisibleType visibleType)
{
    switch (type) {
        case FrameNodeType::SELECTMENU:
            CHECK_NULL_VOID(selectMenu_);
            selectMenu_->GetLayoutProperty()->UpdateVisibility(visibleType);
            break;
        case FrameNodeType::EXTENSIONMENU:
            CHECK_NULL_VOID(extensionMenu_);
            extensionMenu_->GetLayoutProperty()->UpdateVisibility(visibleType);
            break;
        case FrameNodeType::BACKBUTTON:
            CHECK_NULL_VOID(backButton_);
            backButton_->GetLayoutProperty()->UpdateVisibility(visibleType);
            break;
        case FrameNodeType::MENUONLY:
            {
                auto layoutProperty = GetLayoutProperty();
                CHECK_NULL_VOID(layoutProperty);
                layoutProperty->UpdateVisibility(visibleType);
                break;
            }
        default:
            break;
    }
}

void SelectOverlayNode::SetFrameNodeOpacity(FrameNodeType type, float opacity)
{
    switch (type) {
        case FrameNodeType::SELECTMENU:
            SetSelectMenuOpacity(opacity);
            break;
        case FrameNodeType::EXTENSIONMENU:
            SetExtensionMenuOpacity(opacity);
            break;
        case FrameNodeType::BACKBUTTON:
            SetBackButtonOpacity(opacity);
            break;
        case FrameNodeType::MENUONLY:
            {
                auto renderContext = GetRenderContext();
                CHECK_NULL_VOID(renderContext);
                renderContext->UpdateOpacity(opacity);
                break;
            }
        default:
            break;
    }
}

void SelectOverlayNode::HideFrameNodeImmediately(FrameNodeType type)
{
    SetFrameNodeStatus(type, FrameNodeStatus::GONE);
    SetFrameNodeVisibility(type, VisibleType::GONE);
    SetFrameNodeOpacity(type, 0.0f);
    HideOrShowCirclesAndBackArrow(type, 0.0f);
}

void SelectOverlayNode::HideOrShowCirclesAndBackArrow(FrameNodeType type, float value)
{
    if (type == FrameNodeType::SELECTMENU) { // select menu
        auto pattern = GetPattern<SelectOverlayPattern>();
        CHECK_NULL_VOID(pattern);
        auto overlayModifier = pattern->GetOverlayModifier();
        CHECK_NULL_VOID(overlayModifier);
        overlayModifier->SetCirclesAndBackArrowOpacity(value);
    }
}

void SelectOverlayNode::SetSelectMenuOpacity(float value)
{
    CHECK_NULL_VOID(selectMenu_);
    CHECK_NULL_VOID(selectMenu_->GetRenderContext());
    selectMenu_->GetRenderContext()->UpdateOpacity(value);
    HideOrShowCirclesAndBackArrow(FrameNodeType::SELECTMENU, value);
}

void SelectOverlayNode::SetExtensionMenuOpacity(float value)
{
    CHECK_NULL_VOID(extensionMenu_);
    CHECK_NULL_VOID(extensionMenu_->GetRenderContext());
    extensionMenu_->GetRenderContext()->UpdateOpacity(value);
}

void SelectOverlayNode::SetBackButtonOpacity(float value)
{
    CHECK_NULL_VOID(backButton_);
    CHECK_NULL_VOID(backButton_->GetRenderContext());
    backButton_->GetRenderContext()->UpdateOpacity(value);
}

void SelectOverlayNode::NotifyUpdateToolBar(bool itemChanged, bool withoutAnimation)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetSelectOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto newOverlayManager = overlayManager->GetSelectContentOverlayManager();
    CHECK_NULL_VOID(newOverlayManager);
    newOverlayManager->NotifyUpdateToolBar(itemChanged, withoutAnimation);
}

void SelectOverlayNode::SwitchToOverlayMode()
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetSelectOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto newOverlayManager = overlayManager->GetSelectContentOverlayManager();
    CHECK_NULL_VOID(newOverlayManager);
    newOverlayManager->SwitchToHandleMode(HandleLevelMode::OVERLAY, false);
}

void SelectOverlayNode::UpdateSelectMenuBg()
{
    CHECK_NULL_VOID(selectMenu_);
    auto pipelineContext = GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto textOverlayTheme = pipelineContext->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(textOverlayTheme);
    auto shadowTheme = pipelineContext->GetTheme<ShadowTheme>();
    CHECK_NULL_VOID(shadowTheme);
    auto colorMode = pipelineContext->GetColorMode();
    auto renderContext = selectMenu_->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateBackShadow(shadowTheme->GetShadow(ShadowStyle::OuterDefaultMD, colorMode));
    renderContext->UpdateBackgroundColor(textOverlayTheme->GetMenuBackgroundColor());
}

void SelectOverlayNode::AddCustomMenuCallbacks(const std::shared_ptr<SelectOverlayInfo>& info)
{
    auto overlayEventHub = GetOrCreateEventHub<SelectOverlayEventHub>();
    CHECK_NULL_VOID(overlayEventHub);
    if (info->menuCallback.onMenuShow) {
        overlayEventHub->SetMenuShowCallback(std::move(info->menuCallback.onMenuShow));
    }
    if (info->menuCallback.onMenuHide) {
        overlayEventHub->SetMenuHideCallback(std::move(info->menuCallback.onMenuHide));
    }
    if (info->menuCallback.onAppear) {
        overlayEventHub->SetMenuAppearCallback(std::move(info->menuCallback.onAppear));
    }
    if (info->menuCallback.onDisappear) {
        overlayEventHub->SetMenuDisappearCallback(std::move(info->menuCallback.onDisappear));
    }
    CHECK_NULL_VOID(selectMenu_);
    auto eventHub = selectMenu_->GetOrCreateEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnAppear([weak = WeakClaim(this)]() {
        auto overlayNode = weak.Upgrade();
        CHECK_NULL_VOID(overlayNode);
        overlayNode->OnCustomSelectMenuAppear();
    });
    eventHub->SetOnDisappear([weakHub = WeakClaim(AceType::RawPtr(overlayEventHub))]() {
        auto overlayEventHub = weakHub.Upgrade();
        CHECK_NULL_VOID(overlayEventHub);
        overlayEventHub->FireDisappearEvent();
    });
}

void SelectOverlayNode::OnCustomSelectMenuAppear()
{
    isCustomMenuAppear_ = true;
    auto eventHub = GetOrCreateEventHub<SelectOverlayEventHub>();
    CHECK_NULL_VOID(eventHub);
    // fire appear event.
    eventHub->FireAppearEvent();
    // fire onMenuShow
    auto pattern = GetPattern<SelectOverlayPattern>();
    CHECK_NULL_VOID(pattern);
    auto info = pattern->GetSelectOverlayInfo();
    CHECK_NULL_VOID(info);
    bool isHideMenu = info->menuInfo.menuDisable || !info->menuInfo.menuIsShow;
    if (isHideMenu) {
        eventHub->FireMenuVisibilityChangeEvent(true);
    }
    eventHub->FireMenuVisibilityChangeEvent(!isHideMenu);
}

void SelectOverlayNode::FireCustomMenuChangeEvent(bool isMenuShow)
{
    if (isCustomMenuAppear_) {
        auto eventHub = GetOrCreateEventHub<SelectOverlayEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->FireMenuVisibilityChangeEvent(isMenuShow);
    }
}

void SelectOverlayNode::OnDetachFromMainTree(bool recursive, PipelineContext* context)
{
    FireCustomMenuChangeEvent(false);
    isCustomMenuAppear_ = false;
    FrameNode::OnDetachFromMainTree(recursive, context);
}

void SelectOverlayNode::UpdateToolBarFromMainWindow(bool menuItemChanged, bool noAnimation)
{
    auto pattern = GetPattern<SelectOverlayPattern>();
    CHECK_NULL_VOID(pattern);
    if (pattern->GetIsMenuShowInSubWindow()) {
        auto containerId = pattern->GetContainerId();
        if (containerId != -1) {
            ContainerScope scope(containerId);
            UpdateToolBar(menuItemChanged, noAnimation);
            return;
        }
    }

    UpdateToolBar(menuItemChanged, noAnimation);
}
} // namespace OHOS::Ace::NG
