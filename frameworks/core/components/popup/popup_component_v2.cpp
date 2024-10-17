/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components/popup/popup_component_v2.h"

#include "core/components/button/button_component.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components/flex/flex_component.h"
#include "core/components/padding/padding_component.h"
#include "core/components/popup/popup_element_v2.h"
#include "core/components/text/text_component_v2.h"

namespace OHOS::Ace {
namespace {

constexpr Dimension DEFAULT_FONT_SIZE = 14.0_fp;
constexpr Dimension BUTTON_ZERO_PADDING = 0.0_vp;
constexpr Dimension BUTTON_ROW_PADDING = 4.0_vp;
constexpr Dimension MESSAGE_HORIZONTAL_PADDING = 16.0_vp;
constexpr Dimension MESSAGE_TOP_PADDING = 12.0_vp;
constexpr Dimension MESSAGE_ZERO_PADDING = 0.0_vp;

constexpr Color POPUP_BUTTON_HOVER_COLOR = Color(0x19FFFFFF);
constexpr Color POPUP_BUTTON_CLICKED_COLOR = Color(0x26FFFFFF);

} // namespace

RefPtr<Element> PopupComponentV2::CreateElement()
{
    return AceType::MakeRefPtr<PopupElementV2>(GetId());
}

void PopupComponentV2::Initialization(const RefPtr<ThemeManager>& themeManager, const WeakPtr<PipelineContext>& context)
{
    if (hasInitialization_) {
        return;
    }

    if (!themeManager) {
        LOGE("themeManager is null.");
        return;
    }

    themeManager_ = themeManager;
    context_ = context;
    auto popupTheme = themeManager_->GetTheme<PopupTheme>();
    if (!popupTheme) {
        LOGE("popupTheme is null.");
        return;
    }

    RefPtr<Component> child;
    if (customComponent_) {
        child = customComponent_;
    } else if (primaryButtonProperties_.showButton || secondaryButtonProperties_.showButton) {
        child = CreateChild();
        GetPopupParam()->SetHasAction(true);
    } else {
        child = CreateMessage();
    }

    auto box = CreateBox(popupTheme);
    box->SetChild(child);
    SetChild(box);
    hasInitialization_ = true;
}

const RefPtr<Component> PopupComponentV2::CreateChild()
{
    RefPtr<ColumnComponent> child;
    std::list<RefPtr<Component>> columnChildren;
    columnChildren.emplace_back(SetPadding(CreateMessage(),
        Edge(MESSAGE_HORIZONTAL_PADDING, MESSAGE_TOP_PADDING, MESSAGE_HORIZONTAL_PADDING, MESSAGE_ZERO_PADDING)));
    columnChildren.emplace_back(SetPadding(
        CreateButtons(), Edge(BUTTON_ROW_PADDING, BUTTON_ZERO_PADDING, BUTTON_ROW_PADDING, BUTTON_ROW_PADDING)));
    child = AceType::MakeRefPtr<ColumnComponent>(FlexAlign::FLEX_START, FlexAlign::FLEX_END, columnChildren);
    child->SetMainAxisSize(MainAxisSize::MIN);
    child->SetCrossAxisSize(CrossAxisSize::MIN);
    return child;
}

const RefPtr<Component> PopupComponentV2::CreateMessage()
{
    auto text = AceType::MakeRefPtr<TextComponentV2>(message_);
    auto textStyle = text->GetTextStyle();
    textStyle.SetAllowScale(false);
    textStyle.SetFontSize(DEFAULT_FONT_SIZE);
    textStyle.SetTextColor(Color::WHITE);
    text->SetTextStyle(std::move(textStyle));
    return text;
}

const RefPtr<Component> PopupComponentV2::CreateButtons()
{
    std::list<RefPtr<Component>> rowChildren;
    rowChildren.emplace_back(SetPadding(CreateButton(primaryButtonProperties_),
        Edge(BUTTON_ZERO_PADDING)));
    rowChildren.emplace_back(SetPadding(CreateButton(secondaryButtonProperties_),
        Edge(BUTTON_ROW_PADDING, BUTTON_ZERO_PADDING, BUTTON_ZERO_PADDING, BUTTON_ZERO_PADDING)));
    auto row = AceType::MakeRefPtr<RowComponent>(FlexAlign::FLEX_END, FlexAlign::CENTER, rowChildren);
    row->SetMainAxisSize(MainAxisSize::MIN);
    auto box = AceType::MakeRefPtr<BoxComponent>();
    box->SetChild(row);
    return box;
}

const RefPtr<Component> PopupComponentV2::CreateButton(const ButtonProperties& buttonProperties)
{
    if (!buttonProperties.showButton) {
        return nullptr;
    }

    auto text = AceType::MakeRefPtr<TextComponent>(buttonProperties.value);
    if (!themeManager_) {
        LOGE("themeManager is null.");
        return nullptr;
    }

    auto buttonTheme = themeManager_->GetTheme<ButtonTheme>();
    if (!buttonTheme) {
        LOGE("buttonTheme is null.");
        return nullptr;
    }

    auto textStyle = text->GetTextStyle();
    textStyle.SetAllowScale(false);
    textStyle.SetFontSize(DEFAULT_FONT_SIZE);
    textStyle.SetTextColor(Color::WHITE);
    text->SetTextStyle(std::move(textStyle));
    std::list<RefPtr<Component>> buttonChildren;
    buttonChildren.emplace_back(SetPadding(text, buttonTheme->GetPadding()));
    auto buttonComponent = AceType::MakeRefPtr<ButtonComponent>(buttonChildren);
    buttonComponent->SetType(ButtonType::CAPSULE);
    buttonComponent->SetDeclarativeFlag(true);
    buttonComponent->SetHeight(buttonTheme->GetHeight());
    buttonComponent->SetBackgroundColor(Color::TRANSPARENT);
    buttonComponent->SetIsPopupButton(true);
    buttonComponent->SetClickedColor(POPUP_BUTTON_CLICKED_COLOR);
    buttonComponent->SetHoverColor(POPUP_BUTTON_HOVER_COLOR);
    buttonComponent->SetMouseAnimationType(HoverAnimationType::NONE);
    buttonComponent->SetClickFunction([action = buttonProperties.actionId, context = context_]() {
        auto func = AceAsyncEvent<void()>::Create(action, context);
        if (func) {
            func();
        }
    });
    return buttonComponent;
}

const RefPtr<Component> PopupComponentV2::SetPadding(const RefPtr<Component>& component, const Edge& edge)
{
    auto paddingComponent = AceType::MakeRefPtr<PaddingComponent>();
    paddingComponent->SetPadding(edge);
    paddingComponent->SetChild(component);
    return paddingComponent;
}

const RefPtr<BoxComponent> PopupComponentV2::CreateBox(const RefPtr<PopupTheme>& popupTheme)
{
    auto box = AceType::MakeRefPtr<BoxComponent>();
    auto decoration = box->GetBackDecoration();
    if (!decoration) {
        decoration = AceType::MakeRefPtr<Decoration>();
        box->SetBackDecoration(decoration);
    }
    decoration->SetBorderRadius(popupTheme->GetRadius());

    if (!customComponent_ && !primaryButtonProperties_.showButton && !secondaryButtonProperties_.showButton) {
        auto padding = popupTheme->GetPadding();
        box->SetPadding(padding);
        GetPopupParam()->SetPadding(padding);
    }

    GetPopupParam()->SetBorder(decoration->GetBorder());
    GetPopupParam()->SetTargetSpace(popupTheme->GetTargetSpace());
    if (!GetPopupParam()->IsMaskColorSetted()) {
        GetPopupParam()->SetMaskColor(popupTheme->GetMaskColor());
    }
    if (!GetPopupParam()->IsBackgroundColorSetted()) {
        GetPopupParam()->SetBackgroundColor(popupTheme->GetBackgroundColor());
    }
    if (placementOnTop_) {
        GetPopupParam()->SetPlacement(Placement::TOP);
    }

    RefPtr<GridColumnInfo> columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::BUBBLE_TYPE);
    if (columnInfo->GetParent()) {
        columnInfo->GetParent()->BuildColumnWidth();
    }
    auto gridSizeType = GridSystemManager::GetInstance().GetCurrentSize();
    double maxWidth = columnInfo->GetWidth(columnInfo->GetColumns(gridSizeType));
    box->SetMaxWidth(Dimension(maxWidth, DimensionUnit::PX));

    return box;
}

} // namespace OHOS::Ace