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
#include <optional>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/i18n/localization.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components/custom_paint/rosen_render_custom_paint.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/property.h"
#include "core/gestures/gesture_info.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {

constexpr char BUTTON_COPY_ALL[] = "textoverlay.select_all";
constexpr char BUTTON_CUT[] = "textoverlay.cut";
constexpr char BUTTON_COPY[] = "textoverlay.copy";
constexpr char BUTTON_PASTE[] = "textoverlay.paste";

RefPtr<FrameNode> BuildButton(
    const std::string& data, const std::function<void()>& callback, int32_t overlayId, bool isSelectAll = false)
{
    auto button = FrameNode::GetOrCreateFrameNode("SelectMenuButton", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto text = FrameNode::GetOrCreateFrameNode("SelectMenuButtonText", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto textLayoutProperty = text->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateContent(data);
    text->MountToParent(button);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, button);
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_RETURN(textOverlayTheme, button);
    auto textStyle = textOverlayTheme->GetMenuButtonTextStyle();
    textLayoutProperty->UpdateFontSize(textStyle.GetFontSize());
    textLayoutProperty->UpdateTextColor(textStyle.GetTextColor());
    textLayoutProperty->UpdateFontWeight(textStyle.GetFontWeight());
    text->MarkModifyDone();

    auto buttonLayoutProperty = button->GetLayoutProperty<ButtonLayoutProperty>();
    const auto& padding = textOverlayTheme->GetMenuButtonPadding();
    auto left = CalcLength(padding.Left().ConvertToPx());
    auto right = CalcLength(padding.Right().ConvertToPx());
    auto top = CalcLength(padding.Top().ConvertToPx());
    auto bottom = CalcLength(padding.Bottom().ConvertToPx());
    buttonLayoutProperty->UpdatePadding({ left, right, top, bottom });
    buttonLayoutProperty->UpdateUserDefinedIdealSize(
        { std::nullopt, CalcLength(textOverlayTheme->GetMenuButtonHeight()) });
    button->GetRenderContext()->UpdateBackgroundColor(textOverlayTheme->GetMenuBackgroundColor());

    button->GetOrCreateGestureEventHub()->SetUserOnClick([callback, overlayId, isSelectAll](GestureEvent& /*info*/) {
        if (callback) {
            callback();
        }
        // close text overlay.
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto overlayManager = pipeline->GetSelectOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        if (!isSelectAll) {
            overlayManager->DestroySelectOverlay(overlayId);
        }
    });
    button->MarkModifyDone();
    return button;
}

RefPtr<FrameNode> BuildButton(
    const std::string& data, const std::function<void(std::string&)>& callback, int32_t overlayId, float& contentWidth)
{
    auto button = FrameNode::GetOrCreateFrameNode("SelectMenuButton", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto text = FrameNode::GetOrCreateFrameNode("SelectMenuButtonText", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });

    // Update text property and mount to button.
    auto textLayoutProperty = text->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateContent(data);
    text->MountToParent(button);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, button);
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_RETURN(textOverlayTheme, button);
    auto textStyle = textOverlayTheme->GetMenuButtonTextStyle();
    textLayoutProperty->UpdateFontSize(textStyle.GetFontSize());
    textLayoutProperty->UpdateTextColor(textStyle.GetTextColor());
    textLayoutProperty->UpdateFontWeight(textStyle.GetFontWeight());
    text->MarkModifyDone();

    // Calculate the width of entension option include button padding.
    MeasureContext content;
    content.textContent = data;
    content.fontSize = textStyle.GetFontSize();
#ifdef ENABLE_ROSEN_BACKEND
    contentWidth = static_cast<float>(RosenRenderCustomPaint::MeasureTextSizeInner(content).Width());
#else
    contentWidth = 0.0;
#endif
    const auto& padding = textOverlayTheme->GetMenuButtonPadding();
    auto left = CalcLength(padding.Left().ConvertToPx());
    auto right = CalcLength(padding.Right().ConvertToPx());
    auto top = CalcLength(padding.Top().ConvertToPx());
    auto bottom = CalcLength(padding.Bottom().ConvertToPx());
    contentWidth = contentWidth + padding.Left().ConvertToPx() + padding.Right().ConvertToPx();

    // Update button property.
    auto buttonLayoutProperty = button->GetLayoutProperty<ButtonLayoutProperty>();
    buttonLayoutProperty->UpdatePadding({ left, right, top, bottom });
    buttonLayoutProperty->UpdateUserDefinedIdealSize(
        { std::nullopt, CalcLength(textOverlayTheme->GetMenuButtonHeight()) });
    button->GetRenderContext()->UpdateBackgroundColor(textOverlayTheme->GetMenuBackgroundColor());
    button->GetOrCreateGestureEventHub()->SetUserOnClick([callback, overlayId](GestureEvent& /*info*/) {
        auto pipeline = PipelineContext::GetCurrentContext();
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
        // close text overlay.
        overlayManager->DestroySelectOverlay(overlayId);
    });
    button->MarkModifyDone();
    return button;
}

RefPtr<FrameNode> BuildMoreOrBackButton(int32_t overlayId, bool isMoreButton)
{
    auto button = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto imageNode = FrameNode::CreateFrameNode(
        "SelectMoreOrBackImage", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, button);
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_RETURN(textOverlayTheme, button);

    // Update property.
    auto buttonLayoutProperty = button->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_RETURN(buttonLayoutProperty, button);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(imageLayoutProperty, button);

    ImageSourceInfo imageSourceInfo;
    imageSourceInfo.SetFillColor(Color::BLACK);
    if (isMoreButton) {
        imageSourceInfo.SetResourceId(textOverlayTheme->GetMoreResourceId());
        buttonLayoutProperty->UpdateUserDefinedIdealSize(
            { std::nullopt, CalcLength(textOverlayTheme->GetMenuButtonHeight()) });
    } else {
        imageSourceInfo.SetResourceId(textOverlayTheme->GetBackResourceId());
        const auto& padding = textOverlayTheme->GetMenuPadding();
        auto left = CalcLength(padding.Left().ConvertToPx());
        auto right = CalcLength(padding.Right().ConvertToPx());
        auto top = CalcLength(padding.Top().ConvertToPx());
        auto bottom = CalcLength(padding.Bottom().ConvertToPx());
        buttonLayoutProperty->UpdateUserDefinedIdealSize({ CalcLength(textOverlayTheme->GetMenuToolbarHeight()),
            CalcLength(textOverlayTheme->GetMenuToolbarHeight()) });
        buttonLayoutProperty->UpdatePadding({ left, right, top, bottom });
        button->GetRenderContext()->UpdateBackShadow(ShadowConfig::DefaultShadowM);
    }

    imageLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(
        CalcLength(textOverlayTheme->GetMoreButtonHeight()), CalcLength(textOverlayTheme->GetMoreButtonHeight())));
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    imageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);

    imageNode->MountToParent(button);
    imageNode->MarkModifyDone();

    button->GetRenderContext()->UpdateBackgroundColor(textOverlayTheme->GetMenuBackgroundColor());
    button->GetOrCreateGestureEventHub()->SetUserOnClick([overlayId, isMore = isMoreButton](GestureEvent& /*info*/) {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto overlayManager = pipeline->GetSelectOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        auto selectOverlay = overlayManager->GetSelectOverlayNode(overlayId);
        CHECK_NULL_VOID(selectOverlay);
        // When click back button , change the extensionMenu to selectMenu.
        selectOverlay->ChangeToolBar(isMore);
    });

    return button;
}

OffsetF GetPageOffset()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, OffsetF());
    auto stageManager = pipeline->GetStageManager();
    CHECK_NULL_RETURN(stageManager, OffsetF());
    auto page = stageManager->GetLastPage();
    CHECK_NULL_RETURN(page, OffsetF());
    return page->GetOffsetRelativeToWindow();
}

} // namespace

SelectOverlayNode::SelectOverlayNode(const std::shared_ptr<SelectOverlayInfo>& info)
    : FrameNode("SelectOverlay", ElementRegister::GetInstance()->MakeUniqueId(), MakeRefPtr<SelectOverlayPattern>(info))
{}

RefPtr<FrameNode> SelectOverlayNode::CreateSelectOverlayNode(const std::shared_ptr<SelectOverlayInfo>& info)
{
    if (info->isUsingMouse) {
        return CreateMenuNode(info);
    }
    auto selectOverlayNode = AceType::MakeRefPtr<SelectOverlayNode>(info);
    selectOverlayNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(selectOverlayNode);
    selectOverlayNode->CreateToolBar();
    selectOverlayNode->UpdateToolBar(true);
    return selectOverlayNode;
}

void SelectOverlayNode::CreateExtensionToolBar(const std::vector<MenuOptionsParam>& menuOptionItems, int32_t index)
{
    extensionMenu_ = FrameNode::GetOrCreateFrameNode("SelectMoreMenu", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    extensionMenu_->GetLayoutProperty<LinearLayoutProperty>()->UpdateCrossAxisAlign(FlexAlign::FLEX_END);
    auto id = GetId();

    auto button = BuildMoreOrBackButton(id, false);
    button->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    button->MountToParent(extensionMenu_);

    std::vector<OptionParam> params;
    int32_t itemNum = 0;
    for (auto item : menuOptionItems) {
        if (itemNum >= index) {
            auto callback = [overlayId = id, func = std::move(item.action)]() {
                auto pipeline = PipelineContext::GetCurrentContext();
                CHECK_NULL_VOID(pipeline);
                auto overlayManager = pipeline->GetSelectOverlayManager();
                CHECK_NULL_VOID(overlayManager);

                auto selectOverlay = overlayManager->GetSelectOverlayNode(overlayId);
                auto pattern = selectOverlay->GetPattern<SelectOverlayPattern>();
                auto selectInfo = pattern->GetSelectInfo();
                func(selectInfo);
                overlayManager->DestroySelectOverlay(overlayId);
            };
            params.emplace_back(item.content.value_or("null"), callback);
        }
        itemNum++;
    }

    auto menuWrapper = MenuView::Create(std::move(params), -1);
    auto menu = DynamicCast<FrameNode>(menuWrapper->GetChildAtIndex(0));
    menuWrapper->RemoveChild(menu);
    menuWrapper.Reset();

    // set click position to menu
    auto props = menu->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(props);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    auto offsetY = textOverlayTheme->GetMenuToolbarHeight().ConvertToPx();
    props->UpdateMenuOffset(OffsetF(0.0f, offsetY));
    menu->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    ElementRegister::GetInstance()->AddUINode(menu);
    menu->MountToParent(extensionMenu_);

    extensionMenu_->MarkModifyDone();
}

void SelectOverlayNode::ChangeToolBar(bool isUseExtensionMenu)
{
    auto weak = Claim(this);
    if (isUseExtensionMenu) {
        weak->RemoveChild(selectMenu_);
        extensionMenu_->MountToParent(weak);
        MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    } else {
        weak->RemoveChild(extensionMenu_);
        selectMenu_->MountToParent(weak);
        MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void SelectOverlayNode::CreateToolBar()
{
    auto info = GetPattern<SelectOverlayPattern>()->GetSelectOverlayInfo();
    selectMenu_ = FrameNode::GetOrCreateFrameNode("SelectMenu", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    selectMenu_->GetLayoutProperty<LinearLayoutProperty>()->UpdateMainAxisAlign(FlexAlign::SPACE_AROUND);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(textOverlayTheme);
    selectMenu_->GetRenderContext()->UpdateBackgroundColor(textOverlayTheme->GetMenuBackgroundColor());

    const auto& border = textOverlayTheme->GetMenuBorder();
    auto borderWidth = Dimension(border.Left().GetWidth().ConvertToPx());
    selectMenu_->GetLayoutProperty()->UpdateBorderWidth({ borderWidth, borderWidth, borderWidth, borderWidth });
    auto borderRadius = textOverlayTheme->GetMenuToolbarHeight() / 2.0f;
    selectMenu_->GetRenderContext()->UpdateBorderRadius({ borderRadius, borderRadius, borderRadius, borderRadius });
    auto borderColor = border.Left().GetColor();
    selectMenu_->GetRenderContext()->UpdateBorderColor({ borderColor, borderColor, borderColor, borderColor });
    auto borderStyle = border.Left().GetBorderStyle();
    selectMenu_->GetRenderContext()->UpdateBorderStyle({ borderStyle, borderStyle, borderStyle, borderStyle });

    const auto& padding = textOverlayTheme->GetMenuPadding();
    auto left = CalcLength(padding.Left().ConvertToPx());
    auto right = CalcLength(padding.Right().ConvertToPx());
    auto top = CalcLength(padding.Top().ConvertToPx());
    auto bottom = CalcLength(padding.Bottom().ConvertToPx());
    selectMenu_->GetLayoutProperty()->UpdatePadding({ left, right, top, bottom });

    selectMenu_->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        { std::nullopt, CalcLength(textOverlayTheme->GetMenuToolbarHeight()) });

    if (info->menuInfo.menuIsShow) {
        selectMenu_->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
    } else {
        selectMenu_->GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);
    }
    selectMenu_->GetRenderContext()->UpdateBackShadow(ShadowConfig::DefaultShadowM);
    selectMenu_->MountToParent(Claim(this));
    selectMenu_->GetOrCreateGestureEventHub()->MarkResponseRegion(true);
    selectMenu_->MarkModifyDone();
}

void SelectOverlayNode::GetDefaultButtonAndMenuWidth(float& defaultOptionWidth, float& maxWidth)
{
    MeasureContext content;
    content.textContent = Localization::GetInstance()->GetEntryLetters(BUTTON_COPY);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(textOverlayTheme);
    auto selectOverlayMaxWidth = textOverlayTheme->GetSelectOverlayMaxWidth().ConvertToPx();

    const auto& menuPadding = textOverlayTheme->GetMenuPadding();

    maxWidth = selectOverlayMaxWidth - menuPadding.Left().ConvertToPx() - menuPadding.Right().ConvertToPx() -
               textOverlayTheme->GetMoreButtonHeight().ConvertToPx();

    auto textStyle = textOverlayTheme->GetMenuButtonTextStyle();
    content.fontSize = textStyle.GetFontSize();
#ifdef ENABLE_ROSEN_BACKEND
    auto size = RosenRenderCustomPaint::MeasureTextSizeInner(content);
#else
    auto size = Size(0.0, 0.0);
#endif
    auto fontWidth = size.Width();
    const auto& buttonPadding = textOverlayTheme->GetMenuButtonPadding();
    defaultOptionWidth = fontWidth + buttonPadding.Left().ConvertToPx() + buttonPadding.Right().ConvertToPx();
}

void SelectOverlayNode::UpdateToolBar(bool menuItemChanged)
{
    auto info = GetPattern<SelectOverlayPattern>()->GetSelectOverlayInfo();
    if (menuItemChanged) {
        selectMenu_->Clean();

        float defaultOptionWidth = 0.0f;
        float maxWidth = 0.0f;
        float allocatedSize = 0.0f;

        GetDefaultButtonAndMenuWidth(defaultOptionWidth, maxWidth);

        if (info->menuInfo.showCopy) {
            auto button = BuildButton(
                Localization::GetInstance()->GetEntryLetters(BUTTON_COPY), info->menuCallback.onCopy, GetId());
            button->MountToParent(selectMenu_);
            allocatedSize += defaultOptionWidth;
        }
        if (info->menuInfo.showCopyAll) {
            auto button = BuildButton(Localization::GetInstance()->GetEntryLetters(BUTTON_COPY_ALL),
                info->menuCallback.onSelectAll, GetId(), true);
            button->MountToParent(selectMenu_);
            allocatedSize += defaultOptionWidth;
        }
        if (info->menuInfo.showCut) {
            auto button = BuildButton(
                Localization::GetInstance()->GetEntryLetters(BUTTON_CUT), info->menuCallback.onCut, GetId());
            button->MountToParent(selectMenu_);
            allocatedSize += defaultOptionWidth;
        }
        if (info->menuInfo.showPaste) {
            auto button = BuildButton(
                Localization::GetInstance()->GetEntryLetters(BUTTON_PASTE), info->menuCallback.onPaste, GetId());
            button->MountToParent(selectMenu_);
            allocatedSize += defaultOptionWidth;
        }

        auto itemNum = -1;
        auto extensionOptionStartIndex = -1;
        if (!info->menuOptionItems.empty()) {
            for (auto item : info->menuOptionItems) {
                itemNum++;
                float extensionOptionWidth = 0.0f;
                auto button = BuildButton(item.content.value_or("null"), item.action, GetId(), extensionOptionWidth);
                allocatedSize += extensionOptionWidth;
                if (allocatedSize > maxWidth) {
                    button.Reset();
                    extensionOptionStartIndex = itemNum;
                    break;
                }
                button->MountToParent(selectMenu_);
            }
        }

        if (extensionOptionStartIndex != -1) {
            auto backButton = BuildMoreOrBackButton(GetId(), true);
            backButton->MountToParent(selectMenu_);
            CreateExtensionToolBar(info->menuOptionItems, extensionOptionStartIndex);
        }
    }
    if (info->menuInfo.menuDisable) {
        selectMenu_->GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);
    } else if (info->menuInfo.menuIsShow) {
        selectMenu_->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
    } else {
        selectMenu_->GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);
    }
    selectMenu_->MarkModifyDone();
    MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

RefPtr<FrameNode> SelectOverlayNode::CreateMenuNode(const std::shared_ptr<SelectOverlayInfo>& info)
{
    std::vector<OptionParam> params;
    params.emplace_back(Localization::GetInstance()->GetEntryLetters(BUTTON_CUT), info->menuCallback.onCut);
    params.emplace_back(Localization::GetInstance()->GetEntryLetters(BUTTON_COPY), info->menuCallback.onCopy);
    params.emplace_back(Localization::GetInstance()->GetEntryLetters(BUTTON_PASTE), info->menuCallback.onPaste);
    params.emplace_back(Localization::GetInstance()->GetEntryLetters(BUTTON_COPY_ALL), info->menuCallback.onSelectAll);

    auto menuWrapper = MenuView::Create(std::move(params), -1);
    auto menu = DynamicCast<FrameNode>(menuWrapper->GetChildAtIndex(0));
    menuWrapper->RemoveChild(menu);
    menuWrapper.Reset();
    // set click position to menu
    auto props = menu->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_RETURN(props, nullptr);
    props->UpdateMenuOffset(info->rightClickOffset + GetPageOffset());

    if (!info->menuInfo.showCut) {
        auto cutOption = DynamicCast<FrameNode>(menu->GetChildAtIndex(0));
        auto optionEventHub = cutOption->GetEventHub<OptionEventHub>();
        if (optionEventHub) {
            optionEventHub->SetEnabled(false);
        }
    }
    if (!info->menuInfo.showCopy) {
        auto copyOption = DynamicCast<FrameNode>(menu->GetChildAtIndex(1));
        auto optionEventHub = copyOption->GetEventHub<OptionEventHub>();
        if (optionEventHub) {
            optionEventHub->SetEnabled(false);
        }
    }
    if (!info->menuInfo.showPaste) {
        auto pasteOption = DynamicCast<FrameNode>(menu->GetChildAtIndex(2));
        auto optionEventHub = pasteOption->GetEventHub<OptionEventHub>();
        if (optionEventHub) {
            optionEventHub->SetEnabled(false);
        }
    }
    if (!info->menuInfo.showCopyAll) {
        auto selectAllOption = DynamicCast<FrameNode>(menu->GetChildAtIndex(3));
        auto optionEventHub = selectAllOption->GetEventHub<OptionEventHub>();
        if (optionEventHub) {
            optionEventHub->SetEnabled(false);
        }
    }
    menu->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    ElementRegister::GetInstance()->AddUINode(menu);

    return menu;
}

} // namespace OHOS::Ace::NG
