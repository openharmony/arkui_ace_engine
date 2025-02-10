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

#include "core/components/picker/picker_base_component.h"

#include "base/i18n/localization.h"
#include "core/components/picker/picker_base_element.h"
#include "core/components/picker/render_picker_base.h"
#include "core/components/triangle/triangle_component.h"

namespace OHOS::Ace {

const char PickerBaseComponent::PICKER_YEAR_COLUMN[] = "year";
const char PickerBaseComponent::PICKER_MONTH_COLUMN[] = "month";
const char PickerBaseComponent::PICKER_DAY_COLUMN[] = "day";
const char PickerBaseComponent::PICKER_HOUR_COLUMN[] = "hour";
const char PickerBaseComponent::PICKER_MINUTE_COLUMN[] = "minute";
const char PickerBaseComponent::PICKER_SECOND_COLUMN[] = "second";
const char PickerBaseComponent::PICKER_TEXT_COLUMN[] = "text";
const char PickerBaseComponent::PICKER_MONTHDAY_COLUMN[] = "monthDay";
const char PickerBaseComponent::PICKER_AMPM_COLUMN[] = "amPm";

RefPtr<RenderNode> PickerBaseComponent::CreateRenderNode()
{
    return RenderPickerBase::Create();
}

RefPtr<Element> PickerBaseComponent::CreateElement()
{
    auto element = AceType::MakeRefPtr<PickerBaseElement>();
    element->SetAutoAccessibility(false);
    return element;
}

void PickerBaseComponent::ClearColumns()
{
    auto accessibilityManager = accessibilityManager_.Upgrade();
    if (accessibilityManager) {
        for (const auto& column : columns_) {
            accessibilityManager->RemoveAccessibilityNodeById(column->GetNodeId());
            column->SetNodeId(-1); // reset to invalidate id.
        }
    } else {
        LOGE("accessibility manager is null.");
    }
    columns_.clear();
}

void PickerBaseComponent::AppendColumn(const RefPtr<PickerColumnComponent>& column)
{
    columns_.emplace_back(column);
}

void PickerBaseComponent::SetNeedVibrate(bool needVibrate)
{
    if (needVibrate_ == needVibrate) {
        return;
    }
    needVibrate_ = needVibrate;
    for (auto& column : columns_) {
        column->SetNeedVibrate(needVibrate_);
    }
}

RefPtr<PickerColumnComponent> PickerBaseComponent::GetColumn(const std::string& tag) const
{
    auto iter = std::find_if(columns_.begin(), columns_.end(),
        [&tag](const RefPtr<PickerColumnComponent>& column) { return column->GetColumnTag() == tag; });
    return (iter == columns_.end()) ? nullptr : *iter;
}

void PickerBaseComponent::RemoveColumn(const std::string& tag)
{
    auto column = GetColumn(tag);
    auto accessibilityManager = accessibilityManager_.Upgrade();
    if (accessibilityManager && column) {
        accessibilityManager->RemoveAccessibilityNodeById(column->GetNodeId());
        column->SetNodeId(-1); // reset to invalidate id.
    } else {
        LOGE("accessibility manager is null or can not get the column.");
    }
    columns_.erase(std::remove_if(
        columns_.begin(),
        columns_.end(),
        [tag](const RefPtr<PickerColumnComponent>& col) { return col->GetColumnTag() == tag; }),
        columns_.end());
}

void PickerBaseComponent::SetFinishCallback(const ColumnFinishCallback& value)
{
    for (const auto& column : columns_) {
        column->SetFinishCallback(value);
    }
}

void PickerBaseComponent::SetChangeCallback(const ColumnChangeCallback& value)
{
    for (const auto& column : columns_) {
        column->SetChangeCallback(value);
    }
}

void PickerBaseComponent::ShowDialog(const RefPtr<StackElement>& stack, bool disableTouchEvent)
{
    if (!isDialog_) {
        return;
    }

    if (dialogShowed_) {
        LOGW("dialog is showed already.");
        return;
    }

    if (!stack) {
        LOGE("stack is null.");
        return;
    }

    stack_ = stack;
    if (!stack_->PushDialog(AceType::Claim(this), disableTouchEvent)) {
        LOGE("push dialog failed!");
        return;
    }
    dialogShowed_ = true;
}

bool PickerBaseComponent::HideDialog()
{
    CloseDialog();
    if (!isDialog_) {
        return false;
    }

    if (!dialogShowed_) {
        LOGW("dialog not show.");
        return false;
    }

    if (!stack_) {
        LOGE("stack is null.");
        return false;
    }

    if (!stack_->PopDialog()) {
        LOGE("pop dialog failed!");
        return false;
    }
    dialogShowed_ = false;
    ClearAccessibilityNodes();
    return true;
}

void PickerBaseComponent::OpenDialog(const DialogProperties& properties)
{
    if (!isCreateDialogComponent_) {
        return;
    }

    auto container = Container::Current();
    if (!container) {
        return;
    }
    auto context = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
    if (!context) {
        return;
    }

    auto executor = context->GetTaskExecutor();
    if (!executor) {
        return;
    }

    executor->PostTask(
        [context, dialogProperties = properties, weak = WeakClaim(this)]() mutable {
            const auto& picker = weak.Upgrade();
            if (context && picker) {
                picker->dialogComponent_ = context->ShowDialog(dialogProperties, false, picker->GetDialogName());
            }
        },
        TaskExecutor::TaskType::UI, "ArkUIDialogShowPicker", TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
}

void PickerBaseComponent::CloseDialog()
{
    if (!isCreateDialogComponent_) {
        return;
    }

    auto container = Container::Current();
    if (!container) {
        return;
    }
    auto context = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
    if (!context) {
        return;
    }
    const auto& lastStack = context->GetLastStack();
    if (!lastStack) {
        return;
    }
    auto executor = context->GetTaskExecutor();
    if (!executor) {
        return;
    }
    executor->PostTask(
        [lastStack, dialogComponent = dialogComponent_]() {
            if (!lastStack || !dialogComponent) {
                return;
            }
            auto dialogId = dialogComponent->GetDialogId();
            lastStack->PopDialog(dialogId);
        },
        TaskExecutor::TaskType::UI, "ArkUIDialogClosePicker",
        TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
}

void PickerBaseComponent::OnTitleBuilding()
{
    SetHasLunar(false);

    auto theme = GetTheme();
    if (!theme) {
        LOGE("theme is null.");
        return;
    }
    SetHasTitle(theme->GetShowButtons());
    SetHasButtons(theme->GetShowButtons());
}

void PickerBaseComponent::InitializeTitle(std::list<RefPtr<Component>>& outChildren)
{
    if (!theme_) {
        LOGE("theme is null.");
        return;
    }
    if ((isDialog_ || isCreateDialogComponent_) && hasTitle_) {
        auto triangle = AceType::MakeRefPtr<TriangleComponent>();
        triangle->SetPadding(8.0_vp); // all padding
        triangle->SetWidth(25.0_vp); // left padding + it width + right padding = 8dp + 9dp + 8dp
        triangle->SetHeight(22.0_vp); // top padding + it height + bottom padding = 8dp + 6dp + 8dp
        triangle->SetColor(theme_->GetTitleStyle().GetTextColor());
        RefPtr<RowComponent> row = AceType::MakeRefPtr<RowComponent>(FlexAlign::CENTER,
            FlexAlign::CENTER, std::list<RefPtr<Component>>());
        title_->SetTextStyle(theme_->GetTitleStyle());
        RefPtr<BoxComponent> titleBox = AceType::MakeRefPtr<BoxComponent>();
        titleBox->SetChild(title_);
        if (!GetHasTriangle()) {
            row->AppendChild(AceType::MakeRefPtr<FlexItemComponent>(0.0, 1.0, 0.0, titleBox));
        } else if (GetTextDirection() != TextDirection::RTL) {
            row->AppendChild(AceType::MakeRefPtr<FlexItemComponent>(0.0, 1.0, 0.0, titleBox));
            row->AppendChild(triangle);
        } else {
            row->AppendChild(triangle);
            row->AppendChild(AceType::MakeRefPtr<FlexItemComponent>(0.0, 1.0, 0.0, titleBox));
        }
        auto titleComposed = GenerateAccessibilityComposed("picker-title", row, titleAccessibility_);
        outChildren.emplace_back(titleComposed);

        RefPtr<BoxComponent> spaceBox = AceType::MakeRefPtr<BoxComponent>();
        spaceBox->SetWidth(theme_->GetTitleBottomPadding().Value(), theme_->GetTitleBottomPadding().Unit());
        spaceBox->SetHeight(theme_->GetTitleBottomPadding().Value(), theme_->GetTitleBottomPadding().Unit());
        outChildren.emplace_back(spaceBox);
    }
}

void PickerBaseComponent::InitializeColumns(
    std::list<RefPtr<Component>>& outChildren, const RefPtr<AccessibilityManager>& accessibilityManager)
{
    if (!theme_) {
        LOGE("theme is null.");
        return;
    }

    std::list<RefPtr<Component>> columns;
    for (const auto& column : columns_) {
        column->SetTheme(theme_->clone());
        column->SetTextDirection(GetTextDirection());
        column->SetInDialog(isDialog_);
        column->SetFixHeight(GetColumnHeight());
        column->SetDefaultHeight(GetDefaultHeight());
        auto id = column->GetNodeId();
        if (id < 0) {
            id = accessibilityManager->GenerateNextAccessibilityId();
            // picker and picker-view accessibility parentNode different.
            static const char* tag = "picker-column";
            if (isDialog_) {
                accessibilityManager->CreateSpecializedNode(tag, id, rootAccessibilityId_);
            } else {
                accessibilityManager->CreateSpecializedNode(tag, id, GetNodeId());
            }
            column->SetNodeId(id);
        }
        columns.emplace_back(column);
    }
    RefPtr<RowComponent> row = AceType::MakeRefPtr<RowComponent>(FlexAlign::FLEX_START, FlexAlign::FLEX_START, columns);
    outChildren.emplace_back(row);
}

void PickerBaseComponent::InitializeChildAccessibility(const RefPtr<AccessibilityManager>& accessibilityManager)
{
    if (!hasLunar_) {
        if (lunarAccessibility_) {
            accessibilityManager->RemoveAccessibilityNodes(lunarAccessibility_);
            lunarAccessibility_ = nullptr;
        }
        if (switchAccessibility_) {
            accessibilityManager->RemoveAccessibilityNodes(switchAccessibility_);
            switchAccessibility_ = nullptr;
        }
        return;
    }
}

void PickerBaseComponent::ClearAccessibilityNodes()
{
    auto accessibilityManager = accessibilityManager_.Upgrade();
    if (!accessibilityManager) {
        LOGE("accessibilityManager is null");
        return;
    }

    if (rootAccessibility_) {
        accessibilityManager->RemoveAccessibilityNodes(rootAccessibility_);
        rootAccessibility_ = nullptr;
        lunarAccessibility_ = nullptr;
        switchAccessibility_ = nullptr;
        titleAccessibility_ = nullptr;
        cancelAccessibility_ = nullptr;
        okAccessibility_ = nullptr;
    }

    for (const auto& column : columns_) {
        column->SetNodeId(-1); // reset id.
    }
#if defined(PREVIEW)
    if (accessibilityManager) {
        auto node = accessibilityManager->GetAccessibilityNodeById(GetPickerBaseId());
        if (node) {
            node->SetZIndexToChild(0);
        }
    }
#endif
}

RefPtr<Component> PickerBaseComponent::GenerateAccessibilityComposed(
    const std::string& name, const RefPtr<Component>& child, RefPtr<AccessibilityNode>& node)
{
    auto accessibilityManager = accessibilityManager_.Upgrade();
    if (!accessibilityManager) {
        return child;
    }

    if (!node) {
        int32_t parentNodeId = -1;
        int32_t composedId = accessibilityManager->GenerateNextAccessibilityId();
        if (isDialog_) {
            parentNodeId = rootAccessibilityId_;
        } else {
            parentNodeId = GetNodeId();
        }
        node = accessibilityManager->CreateSpecializedNode(name, composedId, parentNodeId);
    }
    return child;
}

void PickerBaseComponent::InitializeLunar(
    std::list<RefPtr<Component>>& outChildren, const RefPtr<ThemeManager>& themeManager)
{
    if (!theme_) {
        LOGE("theme is null");
        return;
    }

    if (hasLunar_) {
        RefPtr<BoxComponent> spaceBox = AceType::MakeRefPtr<BoxComponent>();
        spaceBox->SetWidth(theme_->GetButtonTopPadding().Value(), theme_->GetButtonTopPadding().Unit());
        spaceBox->SetHeight(theme_->GetButtonTopPadding().Value(), theme_->GetButtonTopPadding().Unit());
        outChildren.emplace_back(spaceBox);
        std::wstring lunarString { 0x663E, 0x793A, 0x519C, 0x5386 }; // the unicode encoding of chinese string of lunar.
        RefPtr<TextComponent> lunarText = AceType::MakeRefPtr<TextComponent>(StringUtils::ToString(lunarString));
        auto lunarStyle = theme_->GetOptionStyle(false, false);
        if (GetIsDialog()) {
            lunarStyle.SetLineHeight(theme_->GetLunarHeight());
        }
        lunarText->SetTextStyle(lunarStyle);
        auto checkboxTheme = themeManager->GetTheme<CheckboxTheme>();
        lunar_ = AceType::MakeRefPtr<CheckboxComponent>(checkboxTheme);
        lunar_->SetHorizontalPadding(Dimension(0.0));
        lunar_->SetHotZoneVerticalPadding(Dimension(0.0));
        auto lunarSwitchComposed = GenerateAccessibilityComposed("lunar-switch", lunar_, switchAccessibility_);
        RefPtr<BoxComponent> lunarBox = AceType::MakeRefPtr<BoxComponent>();
        lunarBox->SetChild(lunarSwitchComposed);
        lunarBox->SetWidth(theme_->GetLunarWidth().Value(), theme_->GetLunarWidth().Unit());
        lunarBox->SetHeight(theme_->GetLunarHeight().Value(), theme_->GetLunarHeight().Unit());

        std::list<RefPtr<Component>> lunarChildren;
        FlexAlign mainAlign = FlexAlign::AUTO;
        if (GetTextDirection() == TextDirection::RTL) {
            mainAlign = FlexAlign::FLEX_END;
            lunarChildren.emplace_back(lunarText);
            lunarChildren.emplace_back(lunarBox);
        } else {
            mainAlign = FlexAlign::FLEX_START;
            lunarChildren.emplace_back(lunarBox);
            lunarChildren.emplace_back(lunarText);
        }
        RefPtr<RowComponent> lunarRow =
            AceType::MakeRefPtr<RowComponent>(mainAlign, FlexAlign::CENTER, lunarChildren);
        RefPtr<DisplayComponent> display = AceType::MakeRefPtr<DisplayComponent>();
        display->SetChild(lunarRow);
        outChildren.emplace_back(display);
    }

    if (GetSubsidiary() && GetMasterHasLunar()) {
        RefPtr<BoxComponent> spaceBox = AceType::MakeRefPtr<BoxComponent>();
        spaceBox->SetWidth(theme_->GetButtonTopPadding().Value(), theme_->GetButtonTopPadding().Unit());
        spaceBox->SetHeight(theme_->GetButtonTopPadding().Value() + theme_->GetLunarHeight().Value(),
            theme_->GetButtonTopPadding().Unit());
        outChildren.emplace_back(spaceBox);
    }
}

void PickerBaseComponent::InitializeButtons(
    std::list<RefPtr<Component>>& outChildren, const RefPtr<ThemeManager>& themeManager)
{
    auto dialogTheme = themeManager->GetTheme<DialogTheme>();
    if (!theme_ || !dialogTheme) {
        LOGE("theme is null.");
        return;
    }

    auto buttonTheme = AceType::DynamicCast<ButtonTheme>(themeManager->GetTheme(ButtonTheme::TypeId()));
    if (!buttonTheme) {
        return;
    }
    auto buttonTextStyle = buttonTheme->GetTextStyle();
    auto buttonFocusColor = theme_->GetFocusColor();
    buttonTextStyle.SetTextColor(buttonFocusColor);

    if (isDialog_ || isCreateDialogComponent_) {
        RefPtr<BoxComponent> topPaddingBox = AceType::MakeRefPtr<BoxComponent>();
        topPaddingBox->SetWidth(theme_->GetButtonTopPadding().Value(), theme_->GetButtonTopPadding().Unit());
        topPaddingBox->SetHeight(theme_->GetButtonTopPadding().Value(), theme_->GetButtonTopPadding().Unit());
        outChildren.emplace_back(topPaddingBox);

        auto cancelButton = ButtonBuilder::Build(themeManager,
            Localization::GetInstance()->GetEntryLetters("common.cancel"), buttonTextStyle, buttonFocusColor, true);
        cancelButton->SetBackgroundColor(dialogTheme->GetButtonBackgroundColor());
        cancelButton->SetClickedColor(dialogTheme->GetButtonClickedColor());
        cancelButton->SetClickedEventId(onCancelClickId_);
        cancelButton->SetType(ButtonType::CAPSULE);
        cancelButton->SetHeight(theme_->GetButtonHeight());
        auto cancelComposed = GenerateAccessibilityComposed("picker-button", cancelButton, cancelAccessibility_);
        if (cancelAccessibility_) {
            cancelAccessibility_->SetText(Localization::GetInstance()->GetEntryLetters("common.cancel"));
        }

        auto okButton = ButtonBuilder::Build(themeManager, Localization::GetInstance()->GetEntryLetters("common.ok"),
            buttonTextStyle, buttonFocusColor, true);
        okButton->SetBackgroundColor(dialogTheme->GetButtonBackgroundColor());
        okButton->SetClickedColor(dialogTheme->GetButtonClickedColor());
        okButton->SetClickedEventId(onOkClickId_);
        okButton->SetType(ButtonType::CAPSULE);
        okButton->SetHeight(theme_->GetButtonHeight());
        auto okComposed = GenerateAccessibilityComposed("picker-button", okButton, okAccessibility_);
        if (okAccessibility_) {
            okAccessibility_->SetText(Localization::GetInstance()->GetEntryLetters("common.ok"));
        }

        auto dividerBox = AceType::MakeRefPtr<BoxComponent>();
        dividerBox->SetWidth(dialogTheme->GetDividerWidth().Value(), dialogTheme->GetDividerWidth().Unit());
        dividerBox->SetHeight(dialogTheme->GetDividerHeight().Value(), dialogTheme->GetDividerHeight().Unit());
        auto backDecoration = AceType::MakeRefPtr<Decoration>();
        backDecoration->SetBackgroundColor(dialogTheme->GetDividerColor());
        dividerBox->SetBackDecoration(backDecoration);
        dividerBox->SetMargin(dialogTheme->GetDividerPadding());

        std::list<RefPtr<Component>> buttons;
        RefPtr<RowComponent> row =
            AceType::MakeRefPtr<RowComponent>(FlexAlign::SPACE_AROUND, FlexAlign::FLEX_START, buttons);
        row->SetTextDirection(GetTextDirection());
        row->AppendChild(AceType::MakeRefPtr<FlexItemComponent>(1.0, 1.0, 0.0, cancelComposed));
        row->AppendChild(AceType::MakeRefPtr<FlexItemComponent>(0.0, 0.0, 0.0, dividerBox));
        row->AppendChild(AceType::MakeRefPtr<FlexItemComponent>(1.0, 1.0, 0.0, okComposed));
        row->SetStretchToParent(true);

        auto display = AceType::MakeRefPtr<DisplayComponent>();
        display->SetChild(row);
        outChildren.emplace_back(display);
    }
}

void PickerBaseComponent::InitializeContainer(const std::list<RefPtr<Component>>& outChildren)
{
    if (!theme_) {
        LOGE("theme is null.");
        return;
    }

    RefPtr<ColumnComponent> outColumn =
        AceType::MakeRefPtr<ColumnComponent>(FlexAlign::CENTER, FlexAlign::FLEX_START, outChildren);
    RefPtr<BoxComponent> box = AceType::MakeRefPtr<BoxComponent>();
    box->SetDeliverMinToChild(false);
    box->SetAlignment(Alignment::CENTER);
    if (GetIsDialog()) {
        RefPtr<FocusCollaborationComponent> collaboration = AceType::MakeRefPtr<FocusCollaborationComponent>();
        collaboration->InsertChild(0, outColumn);
        box->SetChild(collaboration);
    } else {
        box->SetChild(outColumn);
    }

    RefPtr<BoxComponent> outBox = AceType::MakeRefPtr<BoxComponent>();
    outBox->SetDeliverMinToChild(false);
    outBox->SetAlignment(Alignment::CENTER);
    outBox->SetChild(box);
    if (GetTextDirection() == TextDirection::RTL) {
        outColumn->SetCrossAxisAlign(FlexAlign::FLEX_END);
        box->SetAlignment(Alignment::CENTER_RIGHT);
    }
    // picker need build outer composed component but picker-view don't need.
    if (isDialog_) {
        if (GetSubsidiary()) {
            auto edge = theme_->GetPopupEdge();
            edge.SetTop(0.0_vp);
            edge.SetBottom(0.0_vp);
            auto temp = AceType::MakeRefPtr<Decoration>();
            temp->SetBackgroundColor(Color::TRANSPARENT);
            box->SetBackDecoration(temp);
            box->SetPadding(edge);
            outBox->SetBackDecoration(temp);
        } else {
            box->SetBackDecoration(theme_->GetPopupDecoration(false));
            box->SetPadding(theme_->GetPopupEdge());
            outBox->SetBackDecoration(theme_->GetPopupDecoration(true));
        }
        SetChild(outBox);
    } else {
        SetChild(outBox);
    }
}

void PickerBaseComponent::Initialize(
    const RefPtr<AccessibilityManager>& accessibilityManager, const RefPtr<ThemeManager>& themeManager)
{
    if (!themeManager) {
        return;
    }

    if (!theme_) {
        theme_ = themeManager->GetTheme<PickerTheme>();
    }
    accessibilityManager_ = accessibilityManager;
    OnColumnsBuilding();
    OnTitleBuilding();

    // picker need build rootAccessibilityNode but picker-view don't need.
    if (!rootAccessibility_ && isDialog_) {
        rootAccessibilityId_ = accessibilityManager->GenerateNextAccessibilityId();
#if defined(PREVIEW)
        rootAccessibility_ = accessibilityManager->CreateAccessibilityNode(
            "picker-dialog", rootAccessibilityId_, GetPickerBaseId(), -1);
#else
        rootAccessibility_ = accessibilityManager->CreateSpecializedNode("picker-dialog", rootAccessibilityId_, -1);
#endif
    }
    std::list<RefPtr<Component>> outChildren;
    InitializeTitle(outChildren);
    InitializeColumns(outChildren, accessibilityManager);
    InitializeLunar(outChildren, themeManager);
    InitializeButtons(outChildren, themeManager);
    InitializeContainer(outChildren);
    InitializeChildAccessibility(accessibilityManager);
}

} // namespace OHOS::Ace
