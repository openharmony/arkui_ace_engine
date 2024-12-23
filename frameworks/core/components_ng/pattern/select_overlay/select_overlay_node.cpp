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
#include "core/components_ng/pattern/security_component/paste_button/paste_button_common.h"
#include "core/components_ng/pattern/security_component/paste_button/paste_button_model_ng.h"
#include "core/components_ng/pattern/security_component/security_component_pattern.h"
#include "core/components_ng/pattern/select_content_overlay/select_content_overlay_pattern.h"
#include "core/components_ng/pattern/select_overlay/expanded_menu_plugin_loader.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/calc_length.h"
#ifdef ENABLE_ROSEN_BACKEND
#include "core/components/custom_paint/rosen_render_custom_paint.h"
#endif

namespace OHOS::Ace::NG {
namespace {
constexpr char BUTTON_COPY_ALL[] = "textoverlay.select_all";
constexpr char BUTTON_CUT[] = "textoverlay.cut";
constexpr char BUTTON_COPY[] = "textoverlay.copy";
constexpr char BUTTON_PASTE[] = "textoverlay.paste";
constexpr char BUTTON_SHARE[] = "textoverlay.share";
constexpr char BUTTON_TRANSLATE[] = "textoverlay.translate";
constexpr char BUTTON_SEARCH[] = "textoverlay.search";

constexpr int32_t OPTION_INDEX_CUT = 0;
constexpr int32_t OPTION_INDEX_COPY = 1;
constexpr int32_t OPTION_INDEX_PASTE = 2;
constexpr int32_t OPTION_INDEX_COPY_ALL = 3;
constexpr int32_t OPTION_INDEX_SEARCH = 4;
constexpr int32_t OPTION_INDEX_TRANSLATE = 5;
constexpr int32_t OPTION_INDEX_SHARE = 6;
constexpr int32_t OPTION_INDEX_CAMERA_INPUT = 7;
constexpr int32_t OPTION_INDEX_AI_WRITE = 8;
constexpr int32_t ANIMATION_DURATION1 = 350;
constexpr int32_t ANIMATION_DURATION2 = 150;

constexpr Dimension MORE_MENU_TRANSLATE = -7.5_vp;
constexpr Dimension MAX_DIAMETER = 3.5_vp;
constexpr Dimension MIN_DIAMETER = 1.5_vp;
constexpr Dimension MIN_ARROWHEAD_DIAMETER = 2.0_vp;
constexpr Dimension ANIMATION_TEXT_OFFSET = 12.0_vp;
constexpr Dimension OVERLAY_MAX_WIDTH = 280.0_vp;
constexpr float AGING_MIN_SCALE = 1.75f;

const std::string OH_DEFAULT_CUT = "OH_DEFAULT_CUT";
const std::string OH_DEFAULT_COPY = "OH_DEFAULT_COPY";
const std::string OH_DEFAULT_PASTE = "OH_DEFAULT_PASTE";
const std::string OH_DEFAULT_SELECT_ALL = "OH_DEFAULT_SELECT_ALL";
const std::string OH_DEFAULT_SEARCH = "OH_DEFAULT_SEARCH";
const std::string OH_DEFAULT_CAMERA_INPUT = "OH_DEFAULT_CAMERA_INPUT";
const std::string OH_DEFAULT_AI_WRITE = "OH_DEFAULT_AI_WRITE";
const std::string OH_DEFAULT_COLLABORATION_SERVICE = "OH_DEFAULT_COLLABORATION_SERVICE";

const std::unordered_map<std::string, std::function<bool(const SelectMenuInfo&)>> isMenuItemEnabledFuncMap = {
    { OH_DEFAULT_CUT, [](const SelectMenuInfo& info){ return info.showCut; } },
    { OH_DEFAULT_COPY, [](const SelectMenuInfo& info){ return info.showCopy; } },
    { OH_DEFAULT_SELECT_ALL, [](const SelectMenuInfo& info){ return info.showCopyAll; } },
    { OH_DEFAULT_PASTE, [](const SelectMenuInfo& info){ return info.showPaste; } },
    { OH_DEFAULT_SEARCH, [](const SelectMenuInfo& info){ return info.showSearch; } },
    { OH_DEFAULT_AI_WRITE, [](const SelectMenuInfo& info){ return info.showAIWrite; } }
};

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

float MeasureTextWidth(const TextStyle& textStyle, const std::string& text)
{
#ifdef ENABLE_ROSEN_BACKEND
    MeasureContext content;
    content.textContent = text;
    content.fontSize = textStyle.GetFontSize();
    auto fontweight = StringUtils::FontWeightToString(textStyle.GetFontWeight());
    content.fontWeight = fontweight;
    content.isReturnActualWidth = true;
    content.maxlines = 1;
    return std::max(static_cast<float>(RosenRenderCustomPaint::MeasureTextSizeInner(content).Width()), 0.0f);
#else
    return 0.0f;
#endif
}

#ifdef OHOS_PLATFORM
RefPtr<FrameNode> BuildPasteButton(
    const std::function<void()>& callback, int32_t overlayId, float& buttonWidth, bool isSelectAll = false)
{
    auto descriptionId = static_cast<int32_t>(PasteButtonPasteDescription::PASTE);
    auto pasteButton = PasteButtonModelNG::GetInstance()->CreateNode(descriptionId,
        static_cast<int32_t>(PasteButtonIconStyle::ICON_NULL), static_cast<int32_t>(ButtonType::CAPSULE), true);
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
    if (callback) {
        buttonPaintProperty->UpdateFontColor(textStyle.GetTextColor());
    } else {
        buttonPaintProperty->UpdateFontColor(
            textStyle.GetTextColor().BlendOpacity(textOverlayTheme->GetAlphaDisabled()));
    }
    const auto& padding = textOverlayTheme->GetMenuButtonPadding();
    buttonLayoutProperty->UpdateBackgroundLeftPadding(padding.Left());
    buttonLayoutProperty->UpdateBackgroundRightPadding(padding.Right());
    std::string buttonContent;
    PasteButtonModelNG::GetInstance()->GetTextResource(descriptionId, buttonContent);
    buttonWidth = MeasureTextWidth(textStyle, buttonContent);
    buttonWidth = buttonWidth + padding.Left().ConvertToPx() + padding.Right().ConvertToPx();
    if (GreatOrEqual(pipeline->GetFontScale(), AGING_MIN_SCALE)) {
        buttonLayoutProperty->UpdateUserDefinedIdealSize({ CalcLength(buttonWidth), std::nullopt });
    } else {
        buttonLayoutProperty->UpdateUserDefinedIdealSize(
            { CalcLength(buttonWidth), CalcLength(textOverlayTheme->GetMenuButtonHeight()) });
    }
    buttonPaintProperty->UpdateBackgroundColor(Color::TRANSPARENT);
    if (callback) {
        pasteButton->GetOrCreateGestureEventHub()->SetUserOnClick([callback](GestureEvent& info) {
            if (!PasteButtonModelNG::GetInstance()->IsClickResultSuccess(info)) {
                return;
            }
            if (callback) {
                callback();
            }
        });
    } else {
        auto buttonEventHub = pasteButton->GetEventHub<MenuItemEventHub>();
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
    auto onPaste = [onPaste = info->menuCallback.onPaste, onCreateCallback = info->onCreateCallback,
                       menuOptionsParam = item]() {
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

RefPtr<FrameNode> BuildButton(const std::string& data, const std::function<void()>& callback, int32_t overlayId,
    float& buttonWidth, bool isSelectAll = false)
{
    auto button = FrameNode::GetOrCreateFrameNode("SelectMenuButton", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto text = FrameNode::GetOrCreateFrameNode("SelectMenuButtonText", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto textLayoutProperty = text->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, button);
    textLayoutProperty->UpdateContent(data);
    text->MountToParent(button);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, button);
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_RETURN(textOverlayTheme, button);
    auto textStyle = textOverlayTheme->GetMenuButtonTextStyle();
    textLayoutProperty->UpdateFontSize(textStyle.GetFontSize());
    textLayoutProperty->UpdateFontWeight(textStyle.GetFontWeight());
    textLayoutProperty->UpdateMaxLines(1);
    if (callback) {
        textLayoutProperty->UpdateTextColor(textStyle.GetTextColor());
    } else {
        textLayoutProperty->UpdateTextColor(
            textStyle.GetTextColor().BlendOpacity(textOverlayTheme->GetAlphaDisabled()));
    }
    text->MarkModifyDone();

    auto buttonLayoutProperty = button->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_RETURN(buttonLayoutProperty, button);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_FOURTEEN)) {
        buttonLayoutProperty->UpdateType(ButtonType::ROUNDED_RECTANGLE);
    } else {
        buttonLayoutProperty->UpdateType(ButtonType::CAPSULE);
    }
    const auto& padding = textOverlayTheme->GetMenuButtonPadding();
    auto left = CalcLength(padding.Left().ConvertToPx());
    auto right = CalcLength(padding.Right().ConvertToPx());
    auto top = CalcLength(padding.Top().ConvertToPx());
    auto bottom = CalcLength(padding.Bottom().ConvertToPx());
    buttonLayoutProperty->UpdatePadding({ left, right, top, bottom });
    buttonWidth = MeasureTextWidth(textStyle, data);
    // Calculate the width of default option include button padding.
    buttonWidth = buttonWidth + padding.Left().ConvertToPx() + padding.Right().ConvertToPx();
    if (GreatOrEqual(pipeline->GetFontScale(), AGING_MIN_SCALE)) {
        buttonLayoutProperty->UpdateUserDefinedIdealSize({ CalcLength(buttonWidth), std::nullopt });
    } else {
        buttonLayoutProperty->UpdateUserDefinedIdealSize(
            { CalcLength(buttonWidth), CalcLength(textOverlayTheme->GetMenuButtonHeight()) });
    }
    buttonLayoutProperty->UpdateFlexShrink(0);
    button->GetRenderContext()->UpdateBackgroundColor(Color::TRANSPARENT);

    if (callback) {
        button->GetOrCreateGestureEventHub()->SetUserOnClick(
            [callback, overlayId, isSelectAll](GestureEvent& /*info*/) {
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
                if (callback) {
                    callback();
                }
            });
    } else {
        auto buttonEventHub = button->GetEventHub<MenuItemEventHub>();
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
    button->GetOrCreateGestureEventHub()->SetUserOnClick([callback, overlayId](GestureEvent& /*info*/) {
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
    contentWidth = MeasureTextWidth(textStyle, data);
    const auto& padding = textOverlayTheme->GetMenuButtonPadding();
    auto left = CalcLength(padding.Left().ConvertToPx());
    auto right = CalcLength(padding.Right().ConvertToPx());
    auto top = CalcLength(padding.Top().ConvertToPx());
    auto bottom = CalcLength(padding.Bottom().ConvertToPx());
    contentWidth = contentWidth + padding.Left().ConvertToPx() + padding.Right().ConvertToPx();

    // Update button property.
    auto buttonLayoutProperty = button->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_RETURN(buttonLayoutProperty, button);
    buttonLayoutProperty->UpdatePadding({ left, right, top, bottom });
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
    button->GetOrCreateGestureEventHub()->SetUserOnClick(
        [menuOptionsParam, systemCallback, onCreateCallback, overlayId](GestureEvent& /*info*/) {
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

void UpdateTextProperty(const TextStyle& textStyle, const RefPtr<TextLayoutProperty>& textLayoutProperty)
{
    textLayoutProperty->UpdateFontSize(textStyle.GetFontSize());
    textLayoutProperty->UpdateTextColor(textStyle.GetTextColor());
    textLayoutProperty->UpdateFontWeight(textStyle.GetFontWeight());
    textLayoutProperty->UpdateMaxLines(1);
    textLayoutProperty->UpdateWordBreak(WordBreak::BREAK_ALL);
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
    auto contentWidth = MeasureTextWidth(textStyle, data);
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

    auto button = FrameNode::GetOrCreateFrameNode("SelectMenuButton", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto text = FrameNode::GetOrCreateFrameNode("SelectMenuButtonText", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    // Update text property and mount to button.
    auto textLayoutProperty = text->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, button);
    textLayoutProperty->UpdateContent(data);
    UpdateTextProperty(textStyle, textLayoutProperty);
    text->MountToParent(button);

    if (!isOverWidth && menuOptionsParam.isFirstOption) {
        textLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    }
    text->MarkModifyDone();

    // Update button property.
    auto buttonLayoutProperty = button->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_RETURN(buttonLayoutProperty, button);
    buttonLayoutProperty->UpdatePadding({ left, right, top, bottom });
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

    if (isMoreButton) {
        auto sideWidth = CalcLength(textOverlayTheme->GetMenuToolbarHeight().ConvertToPx() -
                                    padding.Top().ConvertToPx() - padding.Bottom().ConvertToPx());
        buttonLayoutProperty->UpdateUserDefinedIdealSize({ sideWidth, sideWidth });
    } else {
        auto sideWidth = CalcLength(textOverlayTheme->GetMenuToolbarHeight().ConvertToPx());
        buttonLayoutProperty->UpdateUserDefinedIdealSize({ sideWidth, sideWidth });
        auto left = CalcLength(padding.Left().ConvertToPx());
        auto right = CalcLength(padding.Right().ConvertToPx());
        auto top = CalcLength(padding.Top().ConvertToPx());
        auto bottom = CalcLength(padding.Bottom().ConvertToPx());
        if (GreatOrEqual(pipeline->GetFontScale(), AGING_MIN_SCALE)) {
            auto overlayManager = pipeline->GetSelectOverlayManager();
            CHECK_NULL_RETURN(overlayManager, button);
            auto selectOverlay = overlayManager->GetSelectOverlayNode(overlayId);
            if (selectOverlay) {
                auto selectMenu = AceType::DynamicCast<FrameNode>(selectOverlay->GetFirstChild());
                CHECK_NULL_RETURN(selectMenu, button);
                auto geometryNode = selectMenu->GetGeometryNode();
                CHECK_NULL_RETURN(geometryNode, button);
                auto selectMenuHeight = geometryNode->GetFrameSize().Height();
                top = CalcLength((selectMenuHeight - sideWidth.GetDimension().Value()) / 2.0f);
            }
        }
        buttonLayoutProperty->UpdatePadding({ left, right, top, bottom });
    }
    button->GetOrCreateGestureEventHub()->SetUserOnClick([overlayId, isMoreButton](GestureEvent& /*info*/) {
        auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
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
    return button;
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

std::vector<OptionParam> GetOptionsParams(const std::shared_ptr<SelectOverlayInfo>& info)
{
    std::vector<OptionParam> params;
    params.emplace_back(Localization::GetInstance()->GetEntryLetters(BUTTON_CUT), info->menuCallback.onCut);
    params.emplace_back(Localization::GetInstance()->GetEntryLetters(BUTTON_COPY), info->menuCallback.onCopy);
    params.emplace_back(Localization::GetInstance()->GetEntryLetters(BUTTON_PASTE), info->menuCallback.onPaste);
    params.emplace_back(Localization::GetInstance()->GetEntryLetters(BUTTON_COPY_ALL), info->menuCallback.onSelectAll);
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_SIXTEEN)) {
        params.emplace_back(Localization::GetInstance()->GetEntryLetters(BUTTON_SEARCH), info->menuCallback.onSearch);
    }
    return params;
}

std::unordered_map<std::string, std::function<void()>> GetSystemCallback(const std::shared_ptr<SelectOverlayInfo>& info)
{
    std::unordered_map<std::string, std::function<void()>> systemCallback = {
        { OH_DEFAULT_CUT, info->menuCallback.onCut }, { OH_DEFAULT_COPY, info->menuCallback.onCopy },
        { OH_DEFAULT_SELECT_ALL, info->menuCallback.onSelectAll }, { OH_DEFAULT_PASTE, info->menuCallback.onPaste },
        { OH_DEFAULT_SEARCH, info->menuCallback.onSearch },
        { OH_DEFAULT_CAMERA_INPUT, info->menuCallback.onCameraInput },
        { OH_DEFAULT_AI_WRITE, info->menuCallback.onAIWrite }
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
    if (id == OH_DEFAULT_SEARCH) {
        return iconTheme->GetIconPath(InternalResource::ResourceId::IC_SEARCH_SVG);
    }
    if (id == OH_DEFAULT_CAMERA_INPUT) {
        return iconTheme->GetIconPath(InternalResource::ResourceId::IC_TAKEPHOTO_SVG);
    }
    if (id == OH_DEFAULT_AI_WRITE) {
        return iconTheme->GetIconPath(InternalResource::ResourceId::IC_AI_WRITE_SVG);
    }
    return iconPath;
}

std::string GetItemContent(const std::string& id, const std::string& content)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, content);
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_RETURN(textOverlayTheme, content);
    if (id == OH_DEFAULT_CUT) {
        return Localization::GetInstance()->GetEntryLetters(BUTTON_CUT);
    }
    if (id == OH_DEFAULT_COPY) {
        return Localization::GetInstance()->GetEntryLetters(BUTTON_COPY);
    }
    if (id == OH_DEFAULT_SELECT_ALL) {
        return Localization::GetInstance()->GetEntryLetters(BUTTON_COPY_ALL);
    }
    if (id == OH_DEFAULT_PASTE) {
        return Localization::GetInstance()->GetEntryLetters(BUTTON_PASTE);
    }
    if (id == OH_DEFAULT_SEARCH) {
        return Localization::GetInstance()->GetEntryLetters(BUTTON_SEARCH);
    }
    if (id == OH_DEFAULT_AI_WRITE) {
        return textOverlayTheme->GetAIWrite();
    }
    if (id == OH_DEFAULT_CAMERA_INPUT) {
        return textOverlayTheme->GetCameraInput();
    }
    return content;
}

std::vector<OptionParam> GetCreateMenuOptionsParams(const std::vector<MenuOptionsParam>& menuOptionItems,
    const std::shared_ptr<SelectOverlayInfo>& info, int32_t startIndex)
{
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
        auto callback = [onCreateCallback = info->onCreateCallback, systemEvent, item]() {
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
                overlayManager->DestroySelectOverlay(true);
            }
        };
        params.emplace_back(GetItemContent(item.id, item.content.value_or("")), "", callback);
        params.back().enabled = IsSystemMenuItemEnabled(info, item.id);
        params.back().disableSystemClick = true;
        itemNum++;
    }
    return params;
}

void SetOptionDisable(const RefPtr<FrameNode>& option)
{
    CHECK_NULL_VOID(option);
    auto optionEventHub = option->GetEventHub<MenuItemEventHub>();
    CHECK_NULL_VOID(optionEventHub);
    optionEventHub->SetEnabled(false);
    option->MarkModifyDone();
}

void SetOptionsAction(const std::shared_ptr<SelectOverlayInfo>& info, const std::vector<RefPtr<FrameNode>>& options)
{
    if (options.empty()) {
        return;
    }
    if (!info->menuInfo.showCut) {
        SetOptionDisable(options[OPTION_INDEX_CUT]);
    }
    if (!info->menuInfo.showCopy) {
        SetOptionDisable(options[OPTION_INDEX_COPY]);
    }
    if (!info->menuInfo.showPaste) {
        SetOptionDisable(options[OPTION_INDEX_PASTE]);
    }
    if (!info->menuInfo.showCopyAll) {
        SetOptionDisable(options[OPTION_INDEX_COPY_ALL]);
    }
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_SIXTEEN)) {
        if (!info->menuInfo.showSearch) {
            SetOptionDisable(options[OPTION_INDEX_SEARCH]);
        }
    }
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
    auto eventHub = selectMenu_->GetEventHub<EventHub>();
    if (eventHub && info->menuCallback.onAppear) {
        eventHub->SetOnAppear(std::move(info->menuCallback.onAppear));
    }
    if (eventHub && info->menuCallback.onDisappear) {
        eventHub->SetOnDisappear(std::move(info->menuCallback.onDisappear));
    }
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

    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);

    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(textOverlayTheme);

    auto shadowTheme = pipeline->GetTheme<ShadowTheme>();
    CHECK_NULL_VOID(shadowTheme);

    isExtensionMenu_ = true;

    extensionProperty->UpdateVisibility(VisibleType::VISIBLE);
    backButtonProperty->UpdateVisibility(VisibleType::VISIBLE);
    extensionMenuStatus_ = FrameNodeStatus::VISIBLE;
    AnimationOption extensionOption;
    extensionOption.SetDuration(ANIMATION_DURATION2);
    extensionOption.SetCurve(Curves::FAST_OUT_SLOW_IN);
    auto toolbarHeight = textOverlayTheme->GetMenuToolbarHeight();
    auto frameSize = CalcSize(CalcLength(toolbarHeight.ConvertToPx()), CalcLength(toolbarHeight.ConvertToPx()));

    AnimationUtils::Animate(
        extensionOption, [extensionContext, selectMenuInnerContext, id = Container::CurrentId(), shadowTheme]() {
            ContainerScope scope(id);
            if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
                extensionContext->UpdateOpacity(1.0);
            }
            extensionContext->UpdateTransformTranslate({ 0.0f, 0.0f, 0.0f });
            auto colorMode = SystemProperties::GetColorMode();
            extensionContext->UpdateBackShadow(shadowTheme->GetShadow(ShadowStyle::OuterDefaultMD, colorMode));
            selectMenuInnerContext->UpdateOpacity(0.0);
        });
    modifier->SetOtherPointRadius(MIN_DIAMETER / 2.0f, noAnimation);
    modifier->SetHeadPointRadius(MIN_ARROWHEAD_DIAMETER / 2.0f, noAnimation);
    modifier->SetLineEndOffset(true, noAnimation);
    auto menuPattern = extensionMenu_->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->SetMenuShow();

    FinishCallback callback = [selectMenuInnerProperty, extensionProperty, backButtonProperty,
                                  id = Container::CurrentId(), weak = WeakClaim(this)]() {
        ContainerScope scope(id);
        selectMenuInnerProperty->UpdateVisibility(VisibleType::GONE);
        extensionProperty->UpdateVisibility(VisibleType::VISIBLE);
        auto selectOverlay = weak.Upgrade();
        CHECK_NULL_VOID(selectOverlay);
        selectOverlay->SetAnimationStatus(false);
        selectOverlay->OnAccessibilityEvent(AccessibilityEventType::PAGE_CHANGE);
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

    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
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

    AnimationUtils::Animate(extensionOption, [extensionContext, selectMenuInnerContext, id = Container::CurrentId()]() {
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

    FinishCallback callback = [selectMenuInnerProperty, extensionProperty, backButtonProperty,
                                  id = Container::CurrentId(), weak = WeakClaim(this)]() {
        ContainerScope scope(id);
        selectMenuInnerProperty->UpdateVisibility(VisibleType::VISIBLE);
        extensionProperty->UpdateVisibility(VisibleType::GONE);
        backButtonProperty->UpdateVisibility(VisibleType::GONE);
        auto selectOverlay = weak.Upgrade();
        CHECK_NULL_VOID(selectOverlay);
        selectOverlay->SetAnimationStatus(false);
        selectOverlay->OnAccessibilityEvent(AccessibilityEventType::PAGE_CHANGE);
    };

    AnimationOption selectOption;
    selectOption.SetDuration(ANIMATION_DURATION1);
    selectOption.SetCurve(Curves::FRICTION);
    pipeline->FlushUITasks();
    AnimationUtils::OpenImplicitAnimation(selectOption, Curves::FRICTION, callback);
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

std::function<void()> SelectOverlayNode::GetDefaultOptionCallback()
{
    auto id = GetId();
    auto defaultOptionCallback = [overlayId = id]() {
        auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(pipeline);
        auto overlayManager = pipeline->GetSelectOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        overlayManager->DestroySelectOverlay(overlayId);
        overlayManager->CloseSelectContentOverlay(overlayId, CloseReason::CLOSE_REASON_TOOL_BAR, false);
    };
    return defaultOptionCallback;
}

std::vector<OptionParam> SelectOverlayNode::GetDefaultOptionsParams(const std::shared_ptr<SelectOverlayInfo>& info)
{
    std::vector<OptionParam> params;
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, params);
    auto iconTheme = pipeline->GetTheme<IconTheme>();
    auto defaultOptionCallback = GetDefaultOptionCallback();
    if (!isShowInDefaultMenu_[OPTION_INDEX_CUT]) {
        auto iconPath = iconTheme ? iconTheme->GetIconPath(InternalResource::ResourceId::IC_CUT_SVG) : "";
        params.emplace_back(
            Localization::GetInstance()->GetEntryLetters(BUTTON_CUT), iconPath, info->menuCallback.onCut);
    }
    if (!isShowInDefaultMenu_[OPTION_INDEX_COPY]) {
        auto iconPath = iconTheme ? iconTheme->GetIconPath(InternalResource::ResourceId::IC_COPY_SVG) : "";
        params.emplace_back(
            Localization::GetInstance()->GetEntryLetters(BUTTON_COPY), iconPath, info->menuCallback.onCopy);
    }
    if (!isShowInDefaultMenu_[OPTION_INDEX_PASTE]) {
        auto iconPath = iconTheme ? iconTheme->GetIconPath(InternalResource::ResourceId::IC_PASTE_SVG) : "";
        params.emplace_back(
            Localization::GetInstance()->GetEntryLetters(BUTTON_PASTE), iconPath, info->menuCallback.onPaste);
    }
    if (!isShowInDefaultMenu_[OPTION_INDEX_COPY_ALL]) {
        auto iconPath = iconTheme ? iconTheme->GetIconPath(InternalResource::ResourceId::IC_SELECT_ALL_SVG) : "";
        params.emplace_back(
            Localization::GetInstance()->GetEntryLetters(BUTTON_COPY_ALL), iconPath, info->menuCallback.onSelectAll);
    }
    if (!isShowInDefaultMenu_[OPTION_INDEX_SEARCH]) {
        auto iconPath = iconTheme ? iconTheme->GetIconPath(InternalResource::ResourceId::IC_SEARCH_SVG) : "";
        params.emplace_back(
            Localization::GetInstance()->GetEntryLetters(BUTTON_SEARCH), iconPath, info->menuCallback.onSearch);
    }
    if (!isShowInDefaultMenu_[OPTION_INDEX_SHARE]) {
        auto iconPath = iconTheme ? iconTheme->GetIconPath(InternalResource::ResourceId::IC_SHARE_SVG) : "";
        params.emplace_back(
            Localization::GetInstance()->GetEntryLetters(BUTTON_SHARE), iconPath, defaultOptionCallback);
    }
    if (!isShowInDefaultMenu_[OPTION_INDEX_TRANSLATE]) {
        auto iconPath = iconTheme ? iconTheme->GetIconPath(InternalResource::ResourceId::IC_TRANSLATE_SVG) : "";
        params.emplace_back(
            Localization::GetInstance()->GetEntryLetters(BUTTON_TRANSLATE), iconPath, defaultOptionCallback);
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
        params.emplace_back(iconName, iconPath, info->menuCallback.onCameraInput);
    }
    if (!isShowInDefaultMenu_[OPTION_INDEX_AI_WRITE]) {
        auto iconPath = iconTheme ? iconTheme->GetIconPath(InternalResource::ResourceId::IC_AI_WRITE_SVG) : "";
        auto iconName = textOverlayTheme ? textOverlayTheme->GetAIWrite() : "";
        params.emplace_back(iconName, iconPath, info->menuCallback.onAIWrite);
    }
}

void SelectOverlayNode::addMenuOptionItemsParams(
    std::vector<OptionParam>& params, const std::shared_ptr<SelectOverlayInfo>& info, int32_t index)
{
    auto id = GetId();
    int32_t itemNum = 0;
    for (auto item : info->menuOptionItems) {
        if (itemNum >= index) {
            auto callback = [overlayId = id, func = std::move(item.action)]() {
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
    auto offsetY = 0.0f;
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    if (textOverlayTheme) {
        offsetY = textOverlayTheme->GetMenuToolbarHeight().ConvertToPx();
    }
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
    auto callback = [overlayId = id, onCreateCallback = onCreateCallback, systemEvent, item]() {
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
        auto param = OptionParam(content, GetSystemIconPath(item.id, item.icon.value_or(" ")), callback);
        if (item.id == OH_DEFAULT_PASTE) {
            param.isPasteOption = true;
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

    auto colorMode = SystemProperties::GetColorMode();
    selectMenu_->GetRenderContext()->UpdateBackShadow(shadowTheme->GetShadow(ShadowStyle::OuterDefaultMD, colorMode));
    selectMenu_->GetRenderContext()->UpdateBackgroundColor(textOverlayTheme->GetMenuBackgroundColor());
    selectMenu_->GetRenderContext()->SetClipToFrame(true);

    const auto& border = textOverlayTheme->GetMenuBorder();
    auto borderWidth = Dimension(border.Left().GetWidth().ConvertToPx());
    selectMenu_->GetLayoutProperty()->UpdateBorderWidth({ borderWidth, borderWidth, borderWidth, borderWidth });
    auto borderRadius = textOverlayTheme->GetMenuToolbarHeight() / 2.0f;
    selectMenu_->GetRenderContext()->UpdateBorderRadius({ borderRadius, borderRadius, borderRadius, borderRadius });
    auto borderColor = border.Left().GetColor();
    selectMenu_->GetRenderContext()->UpdateBorderColor({ borderColor, borderColor, borderColor, borderColor });
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
    selectMenuInner_->GetLayoutProperty()->UpdatePadding({ left, right, top, bottom });
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

    ShowCut(maxWidth, allocatedSize, info);
    ShowCopy(maxWidth, allocatedSize, info);
    ShowPaste(maxWidth, allocatedSize, info);
    ShowCopyAll(maxWidth, allocatedSize, info);
    ShowSearch(maxWidth, allocatedSize, info);
    ShowShare(maxWidth, allocatedSize, info);
    ShowCamera(maxWidth, allocatedSize, info);
    ShowAIWrite(maxWidth, allocatedSize, info);
    if (isDefaultBtnOverMaxWidth_) {
        isDefaultBtnOverMaxWidth_ = false;
        return true;
    }

    return false;
}

void SelectOverlayNode::ShowCut(float maxWidth, float& allocatedSize, std::shared_ptr<SelectOverlayInfo>& info)
{
    if (info->menuInfo.showCut) {
        float buttonWidth = 0.0f;
        auto button = BuildButton(
            Localization::GetInstance()->GetEntryLetters(BUTTON_CUT), info->menuCallback.onCut, GetId(), buttonWidth);
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

void SelectOverlayNode::ShowCopy(float maxWidth, float& allocatedSize, std::shared_ptr<SelectOverlayInfo>& info)
{
    if (info->menuInfo.showCopy) {
        CHECK_EQUAL_VOID(isDefaultBtnOverMaxWidth_, true);
        float buttonWidth = 0.0f;
        auto button = BuildButton(
            Localization::GetInstance()->GetEntryLetters(BUTTON_COPY), info->menuCallback.onCopy, GetId(), buttonWidth);
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

void SelectOverlayNode::ShowPaste(float maxWidth, float& allocatedSize, std::shared_ptr<SelectOverlayInfo>& info)
{
    if (info->menuInfo.showPaste) {
        CHECK_EQUAL_VOID(isDefaultBtnOverMaxWidth_, true);
        float buttonWidth = 0.0f;
#ifdef OHOS_PLATFORM
        auto button = BuildPasteButton(info->menuCallback.onPaste, GetId(), buttonWidth);
#else
        auto button = BuildButton(Localization::GetInstance()->GetEntryLetters(BUTTON_PASTE),
            info->menuCallback.onPaste, GetId(), buttonWidth);
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

void SelectOverlayNode::ShowCopyAll(float maxWidth, float& allocatedSize, std::shared_ptr<SelectOverlayInfo>& info)
{
    if (info->menuInfo.showCopyAll) {
        CHECK_EQUAL_VOID(isDefaultBtnOverMaxWidth_, true);
        float buttonWidth = 0.0f;
        auto button = BuildButton(Localization::GetInstance()->GetEntryLetters(BUTTON_COPY_ALL),
            info->menuCallback.onSelectAll, GetId(), buttonWidth, true);
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

void SelectOverlayNode::ShowSearch(float maxWidth, float& allocatedSize, std::shared_ptr<SelectOverlayInfo>& info)
{
    if (!IsShowOnTargetAPIVersion()) {
        isShowInDefaultMenu_[OPTION_INDEX_SEARCH] = true;
        return;
    }
    if (info->menuInfo.showSearch) {
        CHECK_EQUAL_VOID(isDefaultBtnOverMaxWidth_, true);
        float buttonWidth = 0.0f;
        auto button = BuildButton(Localization::GetInstance()->GetEntryLetters(BUTTON_SEARCH),
            info->menuCallback.onSearch, GetId(), buttonWidth);
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

void SelectOverlayNode::ShowAIWrite(float maxWidth, float& allocatedSize, std::shared_ptr<SelectOverlayInfo>& info)
{
    if (info->menuInfo.showAIWrite) {
        CHECK_EQUAL_VOID(isDefaultBtnOverMaxWidth_, true);
        float buttonWidth = 0.0f;
        auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetTheme<TextOverlayTheme>();
        CHECK_NULL_VOID(theme);
        auto button = BuildButton(theme->GetAIWrite(), info->menuCallback.onAIWrite, GetId(), buttonWidth, true);
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

void SelectOverlayNode::ShowShare(float maxWidth, float& allocatedSize, std::shared_ptr<SelectOverlayInfo>& info)
{
    bool enableMenuShare = true;
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        enableMenuShare = false;
    }
    if (info->menuInfo.showCopy && enableMenuShare) {
        CHECK_EQUAL_VOID(isDefaultBtnOverMaxWidth_, true);
        float buttonWidth = 0.0f;
        auto buttonShare = BuildButton(
            Localization::GetInstance()->GetEntryLetters(BUTTON_SHARE), nullptr, GetId(), buttonWidth, false);
        CHECK_NULL_VOID(buttonShare);
        if (GreatOrEqual(maxWidth - allocatedSize, buttonWidth)) {
            buttonShare->MountToParent(selectMenuInner_);
            allocatedSize += buttonWidth;
            isShowInDefaultMenu_[OPTION_INDEX_SHARE] = true;
        } else {
            buttonShare.Reset();
            isDefaultBtnOverMaxWidth_ = true;
        }
        CHECK_EQUAL_VOID(isDefaultBtnOverMaxWidth_, true);
        auto buttonTranslase = BuildButton(
            Localization::GetInstance()->GetEntryLetters(BUTTON_TRANSLATE), nullptr, GetId(), buttonWidth, false);
        CHECK_NULL_VOID(buttonTranslase);
        if (GreatOrEqual(maxWidth - allocatedSize, buttonWidth)) {
            buttonTranslase->MountToParent(selectMenuInner_);
            allocatedSize += buttonWidth;
            isShowInDefaultMenu_[OPTION_INDEX_TRANSLATE] = true;
        } else {
            buttonTranslase.Reset();
            isDefaultBtnOverMaxWidth_ = true;
        }
    } else {
        isShowInDefaultMenu_[OPTION_INDEX_SHARE] = true;
        isShowInDefaultMenu_[OPTION_INDEX_TRANSLATE] = true;
    }
}

void SelectOverlayNode::ShowCamera(float maxWidth, float& allocatedSize, std::shared_ptr<SelectOverlayInfo>& info)
{
    if (info->menuInfo.showCameraInput) {
        CHECK_EQUAL_VOID(isDefaultBtnOverMaxWidth_, true);
        float buttonWidth = 0.0f;
        auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetTheme<TextOverlayTheme>();
        CHECK_NULL_VOID(theme);
        auto button =
            BuildButton(theme->GetCameraInput(), info->menuCallback.onCameraInput, GetId(), buttonWidth, false);
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

bool SelectOverlayNode::IsShowOnTargetAPIVersion()
{
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE) &&
        !AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_SIXTEEN)) {
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
        auto moreButton = BuildMoreOrBackButton(GetId(), true);
        CHECK_NULL_VOID(moreButton);
        moreButton->MountToParent(selectMenuInner_);
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
            item.content = GetItemContent(item.id, item.content.value_or(""));
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
    if (info->menuInfo.showCopy || info->isUsingMouse) {
        MenuItemParam param = GetSystemMenuItemParam(OH_DEFAULT_COPY, BUTTON_COPY);
        systemItemParams.emplace_back(param);
    }

    if (info->menuInfo.showPaste || info->isUsingMouse) {
        MenuItemParam param = GetSystemMenuItemParam(OH_DEFAULT_PASTE, BUTTON_PASTE);
        systemItemParams.emplace_back(param);
    }

    if (info->menuInfo.showCut || info->isUsingMouse) {
        MenuItemParam param = GetSystemMenuItemParam(OH_DEFAULT_CUT, BUTTON_CUT);
        systemItemParams.emplace_back(param);
    }

    if (info->menuInfo.showCopyAll || info->isUsingMouse) {
        MenuItemParam param = GetSystemMenuItemParam(OH_DEFAULT_SELECT_ALL, BUTTON_COPY_ALL);
        systemItemParams.emplace_back(param);
    }
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_SIXTEEN)) {
        if (info->menuInfo.showSearch || info->isUsingMouse) {
            MenuItemParam param = GetSystemMenuItemParam(OH_DEFAULT_SEARCH, BUTTON_SEARCH);
            systemItemParams.emplace_back(param);
        }
    }

    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, systemItemParams);
    auto theme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_RETURN(theme, systemItemParams);
    if (info->menuInfo.showCameraInput) {
        MenuItemParam param;
        MenuOptionsParam menuOptionsParam;
        menuOptionsParam.id = OH_DEFAULT_CAMERA_INPUT;
        menuOptionsParam.content = theme->GetCameraInput();
        param.menuOptionsParam = menuOptionsParam;
        systemItemParams.emplace_back(param);
    }
    if (info->menuInfo.showAIWrite) {
        MenuItemParam param;
        MenuOptionsParam menuOptionsParam;
        menuOptionsParam.id = OH_DEFAULT_AI_WRITE;
        menuOptionsParam.content = theme->GetAIWrite();
        param.menuOptionsParam = menuOptionsParam;
        systemItemParams.emplace_back(param);
    }
    return systemItemParams;
}

const MenuItemParam SelectOverlayNode::GetSystemMenuItemParam(const std::string& menuId, const std::string& menuButton)
{
    MenuItemParam param;
    MenuOptionsParam menuOptionsParam;
    menuOptionsParam.id = menuId;
    menuOptionsParam.content = Localization::GetInstance()->GetEntryLetters(menuButton);
    param.menuOptionsParam = menuOptionsParam;
    return param;
}

void SelectOverlayNode::MenuOnlyStatusChange(const std::shared_ptr<SelectOverlayInfo>& info, bool noAnimation)
{
    if (info->menuInfo.menuDisable || !info->menuInfo.menuIsShow) {
        (noAnimation) ? HideMenuOnlyImmediately()
                      : ExecuteOverlayStatus(FrameNodeType::MENUONLY, FrameNodeTrigger::HIDE);
    } else {
        ExecuteOverlayStatus(FrameNodeType::MENUONLY, FrameNodeTrigger::SHOW);
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
        NotifyUpdateToolBar(menuItemChanged);
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
    } else {
        ExecuteOverlayStatus(FrameNodeType::SELECTMENU, FrameNodeTrigger::SHOW);
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

void SelectOverlayNode::UpdateMenuInner(const std::shared_ptr<SelectOverlayInfo>& info, bool noAnimation)
{
    CHECK_NULL_VOID(selectMenuInner_);
    selectMenuInner_->Clean();
    selectMenuInner_->GetLayoutProperty()->ClearUserDefinedIdealSize(true, true);
    SetSelectMenuInnerSize();
    selectMenuInner_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    if (isExtensionMenu_) {
        MoreOrBackAnimation(false, noAnimation);
    }
    auto selectProperty = selectMenu_->GetLayoutProperty();
    CHECK_NULL_VOID(selectProperty);
    selectProperty->ClearUserDefinedIdealSize(true, false);
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
        auto backButton = BuildMoreOrBackButton(GetId(), true);
        CHECK_NULL_VOID(backButton);
        backButton->MountToParent(selectMenuInner_);
        // add back button
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
    auto itemNum = -1;
    for (auto item : menuOptionItems) {
        itemNum++;
        if (isDefaultOverMaxWidth) {
            break;
        }
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
    RefPtr<FrameNode> menuWrapper;
    std::vector<OptionParam> params;
    if (info->onCreateCallback.onCreateMenuCallback) {
        auto systemItemParams = GetSystemMenuItemParams(info);
        auto createMenuItems = info->onCreateCallback.onCreateMenuCallback(systemItemParams);
        params = GetCreateMenuOptionsParams(createMenuItems, info, 0);
    } else {
        params = GetOptionsParams(info);
    }
    menuWrapper = MenuView::Create(std::move(params), -1, "SelectOverlayMenuByRightClick",
        MenuType::SELECT_OVERLAY_RIGHT_CLICK_MENU, { .isShowInSubWindow = false });
    CHECK_NULL_RETURN(menuWrapper, nullptr);
    ExpandedMenuPluginLoader::GetInstance().CreateServiceCollaborationMenu(menuWrapper, info);
    auto menu = DynamicCast<FrameNode>(menuWrapper->GetChildAtIndex(0));
    // set click position to menu
    CHECK_NULL_RETURN(menu, nullptr);
    auto props = menu->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_RETURN(props, nullptr);
    OffsetF pageOffset;
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto windowManager = pipeline->GetWindowManager();
    auto isContainerModal = pipeline->GetWindowModal() == WindowModal::CONTAINER_MODAL && windowManager &&
                            windowManager->GetWindowMode() == WindowMode::WINDOW_MODE_FLOATING;
    if (isContainerModal) {
        pageOffset = GetPageOffset();
    }
    props->UpdateMenuOffset(info->rightClickOffset + pageOffset);

    auto menuPattern = menu->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, nullptr);
    auto options = menuPattern->GetOptions();
    if (!info->onCreateCallback.onCreateMenuCallback) {
        SetOptionsAction(info, options);
    }

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
            selectMenu_->GetLayoutProperty()->UpdateVisibility(visibleType);
            break;
        case FrameNodeType::EXTENSIONMENU:
            extensionMenu_->GetLayoutProperty()->UpdateVisibility(visibleType);
            break;
        case FrameNodeType::BACKBUTTON:
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

void SelectOverlayNode::NotifyUpdateToolBar(bool itemChanged)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetSelectOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto newOverlayManager = overlayManager->GetSelectContentOverlayManager();
    CHECK_NULL_VOID(newOverlayManager);
    newOverlayManager->NotifyUpdateToolBar(itemChanged);
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
    auto colorMode = SystemProperties::GetColorMode();
    auto renderContext = selectMenu_->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateBackShadow(shadowTheme->GetShadow(ShadowStyle::OuterDefaultMD, colorMode));
    renderContext->UpdateBackgroundColor(textOverlayTheme->GetMenuBackgroundColor());
}
} // namespace OHOS::Ace::NG
