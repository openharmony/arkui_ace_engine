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

#include "core/components_ng/pattern/text_picker/textpicker_dialog_view.h"

#include <securec.h>

#include "base/i18n/localization.h"
#include "base/utils/utils.h"
#include "core/common/recorder/event_recorder.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_column_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_event_hub.h"

namespace OHOS::Ace::NG {
namespace {
const int32_t BUFFER_NODE_NUMBER = 2;
const int32_t SECOND_DIVEDER_NODE_INDEX = 3;
const int32_t THIRD_DIVEDER_NODE_INDEX = 5;
const int32_t BACKWARD_BUTTON_DIVEDER_INDEX = 2;
const int32_t FORWAED_BUTTON_DIVEDER_INDEX = 4;
const int32_t CONFIRM_BUTTON_DIVEDER_INDEX = 6;
constexpr size_t ACCEPT_BUTTON_INDEX = 0;
constexpr size_t CANCEL_BUTTON_INDEX = 1;
constexpr size_t BACKWARD_BUTTON_INDEX = 2;
constexpr size_t FORWAED_BUTTON_INDEX = 3;
} // namespace

WeakPtr<FrameNode> TextPickerDialogView::dialogNode_ = nullptr;
uint32_t dialogNodePage = 0;
uint32_t totalPageNum_ = 0;
Dimension TextPickerDialogView::selectedTextStyleFont_ = 40.0_fp;
Dimension TextPickerDialogView::normalTextStyleFont_ = 32.0_fp;
Dimension TextPickerDialogView::disappearTextStyleFont_ = 28.0_fp;

RefPtr<FrameNode> TextPickerDialogView::Show(const DialogProperties& dialogProperties,
    const TextPickerSettingData& settingData, const std::vector<ButtonInfo>& buttonInfos,
    std::map<std::string, NG::DialogTextEvent> dialogEvent,
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent)
{
    if (settingData.rangeVector.empty() && settingData.options.empty()) {
        return nullptr;
    }
    GetUserSettingLimit();
    if (settingData.options.empty()) {
        return RangeShow(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    } else {
        return OptionsShow(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    }
}

RefPtr<FrameNode> TextPickerDialogView::RangeShow(const DialogProperties& dialogProperties,
    const TextPickerSettingData& settingData, const std::vector<ButtonInfo>& buttonInfos,
    std::map<std::string, NG::DialogTextEvent>& dialogEvent,
    std::map<std::string, NG::DialogGestureEvent>& dialogCancelEvent)
{
    auto contentColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto textNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textPickerNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_PICKER_ETS_TAG, textNodeId, []() { return AceType::MakeRefPtr<TextPickerPattern>(); });
    ViewStackProcessor::GetInstance()->Push(textPickerNode);
    auto textPickerPattern = textPickerNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_RETURN(textPickerPattern, nullptr);
    textPickerPattern->SetColumnsKind(settingData.columnKind);
    textPickerPattern->SetIsShowInDialog(true);
    textPickerPattern->SetPickerTag(false);
    textPickerPattern->SetTextProperties(settingData.properties);
    auto context = textPickerNode->GetContext();
    CHECK_NULL_RETURN(context, nullptr);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    auto dialogTheme = themeManager->GetTheme<DialogTheme>();
    CHECK_NULL_RETURN(dialogTheme, nullptr);
    textPickerPattern->SetBackgroundColor(dialogTheme->GetBackgroundColor());
    auto pickerTheme = themeManager->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, nullptr);
    auto pickerNodeLayout = textPickerNode->GetLayoutProperty<TextPickerLayoutProperty>();
    CHECK_NULL_RETURN(pickerNodeLayout, nullptr);
    pickerNodeLayout->UpdateUserDefinedIdealSize(
        CalcSize(NG::CalcLength(Dimension(1.0, DimensionUnit::PERCENT)), std::nullopt));
    pickerNodeLayout->UpdateCanLoop(settingData.canLoop);
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    OptionsCreateNode(textPickerPattern, settingData, textPickerNode, showCount, 1, pickerTheme);
    SetDefaultPickerItemHeight(settingData.height);
    SetTextProperties(pickerTheme, settingData.properties);
    auto changeEvent = dialogEvent["changeId"];
    SetDialogChange(textPickerNode, std::move(changeEvent));
    ViewStackProcessor::GetInstance()->Finish();
    textPickerNode->MountToParent(contentColumn);
    auto dialogNode = DialogView::CreateDialogNode(dialogProperties, contentColumn);
    CHECK_NULL_RETURN(dialogNode, nullptr);
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    CHECK_NULL_RETURN(dialogPattern, nullptr);
    dialogPattern->SetIsPickerDiaglog(true);
    auto closeDiaglogEvent = CloseDiaglogEvent(textPickerPattern, dialogNode);
    auto closeCallback = [func = std::move(closeDiaglogEvent)](const GestureEvent& /* info */) {
        func();
    };

    auto contentRow =
        CreateButtonNode(textPickerNode, buttonInfos, dialogEvent, std::move(dialogCancelEvent), closeCallback);
    textPickerPattern->SetContentRowNode(contentRow);
    contentRow->SetNeedCallChildrenUpdate(false);
    contentRow->AddChild(CreateDividerNode(textPickerNode), 1);
    contentRow->MountToParent(contentColumn);
    auto focusHub = contentColumn->GetFocusHub();
    CHECK_NULL_RETURN(focusHub, nullptr);
    InitOnKeyEvent(focusHub);
    dialogNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    dialogNode_ = dialogNode;
    return dialogNode;
}

std::function<void()> TextPickerDialogView::CloseDiaglogEvent(const RefPtr<TextPickerPattern>& textPickerPattern,
    const RefPtr<FrameNode>& dialogNode)
{
    auto event = [weak = WeakPtr<FrameNode>(dialogNode),
        weakPattern = WeakPtr<TextPickerPattern>(textPickerPattern)]() {
        auto dialogNode = weak.Upgrade();
        CHECK_NULL_VOID(dialogNode);
        auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
        CHECK_NULL_VOID(dialogPattern);
        dialogPattern->SetIsPickerDiaglog(false);
        auto textPickerPattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(textPickerPattern);
        if (textPickerPattern->GetIsShowInDialog()) {
            auto pipeline = PipelineContext::GetCurrentContext();
            auto overlayManager = pipeline->GetOverlayManager();
            overlayManager->CloseDialog(dialogNode);
            textPickerPattern->SetIsShowInDialog(false);
        }
    };
    textPickerPattern->updateFontConfigurationEvent(event);
    return event;
}

void TextPickerDialogView::OptionsCreateNode(const RefPtr<TextPickerPattern>& textPickerPattern,
    const TextPickerSettingData& settingData, const RefPtr<FrameNode>& textPickerNode, uint32_t showCount,
    uint32_t columnCount, RefPtr<PickerTheme> pickerTheme)
{
    totalPageNum_ = columnCount;
    if (textPickerNode->GetChildren().empty()) {
        for (size_t i = 0; i < columnCount; i++) {
            auto columnNode = CreateColumnNode(settingData.columnKind,
                showCount, pickerTheme);
            auto stackNode = CreateStackNode(pickerTheme);
            auto buttonNode = CreateButtonNode();
            auto columnBlendNode = CreateColumnNode();
            buttonNode->MountToParent(stackNode);
            columnNode->MountToParent(columnBlendNode);
            columnBlendNode->MountToParent(stackNode);
            columnNode->MarkModifyDone();
            columnNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            auto layoutProperty = stackNode->GetLayoutProperty<LayoutProperty>();
            layoutProperty->UpdateAlignment(Alignment::CENTER);
            layoutProperty->UpdateLayoutWeight(1);
            stackNode->MountToParent(textPickerNode);
        }
    }
    if (settingData.options.size() > 0) {
        SetSelectedValues(textPickerPattern, settingData.selectedValues);
        SetValues(textPickerPattern, settingData.values);
    } else {
        SetRange(textPickerPattern, settingData.rangeVector);
        SetSelected(textPickerPattern, settingData.selected);
    }
}

void TextPickerDialogView::OptionsShowInternal(const RefPtr<TextPickerPattern>& textPickerPattern,
    const TextPickerSettingData& settingData, const RefPtr<FrameNode>& textPickerNode, uint32_t showCount,
    RefPtr<PickerTheme> pickerTheme)
{
    textPickerPattern->SetIsCascade(settingData.attr.isCascade);
    textPickerPattern->SetHasSelectAttr(settingData.attr.isHasSelectAttr);
    textPickerPattern->SetColumnsKind(settingData.columnKind);
    if (settingData.attr.isCascade) {
        std::vector<NG::TextCascadePickerOptions> reOptions;
        uint32_t columnCount = settingData.options.empty() ? 0 : 1;
        // Caculate max depth
        for (size_t i = 0; i < settingData.options.size(); i++) {
            size_t tmp = textPickerPattern->ProcessCascadeOptionDepth(settingData.options[i]);
            if (tmp > columnCount) {
                columnCount = tmp;
            }
        }
        OptionsCreateNode(textPickerPattern, settingData, textPickerNode, showCount, columnCount, pickerTheme);
        textPickerPattern->ProcessCascadeOptions(settingData.options, reOptions, 0);
        if (reOptions.size() < columnCount) {
            auto differ = columnCount - reOptions.size();
            for (uint32_t i = 0; i < differ; i++) {
                NG::TextCascadePickerOptions differOption;
                memset_s(&differOption, sizeof(differOption), 0, sizeof(differOption));
                reOptions.emplace_back(differOption);
            }
        }
        textPickerPattern->SetCascadeOptions(settingData.options, reOptions);
    } else {
        OptionsCreateNode(
            textPickerPattern, settingData, textPickerNode, showCount, settingData.options.size(), pickerTheme);
        textPickerPattern->SetCascadeOptions(settingData.options, settingData.options);
    }
}

RefPtr<FrameNode> TextPickerDialogView::OptionsShow(const DialogProperties& dialogProperties,
    const TextPickerSettingData& settingData, const std::vector<ButtonInfo>& buttonInfos,
    std::map<std::string, NG::DialogTextEvent>& dialogEvent,
    std::map<std::string, NG::DialogGestureEvent>& dialogCancelEvent)
{
    auto contentColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto textNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textPickerNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_PICKER_ETS_TAG, textNodeId, []() { return AceType::MakeRefPtr<TextPickerPattern>(); });
    ViewStackProcessor::GetInstance()->Push(textPickerNode);
    auto textPickerPattern = textPickerNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_RETURN(textPickerPattern, nullptr);
    textPickerPattern->SetIsShowInDialog(true);
    textPickerPattern->SetPickerTag(false);
    textPickerPattern->SetTextProperties(settingData.properties);
    auto context = textPickerNode->GetContext();
    CHECK_NULL_RETURN(context, nullptr);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    auto dialogTheme = themeManager->GetTheme<DialogTheme>();
    CHECK_NULL_RETURN(dialogTheme, nullptr);
    textPickerPattern->SetBackgroundColor(dialogTheme->GetBackgroundColor());
    auto pickerTheme = themeManager->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, nullptr);
    auto pickerNodeLayout = textPickerNode->GetLayoutProperty<TextPickerLayoutProperty>();
    CHECK_NULL_RETURN(pickerNodeLayout, nullptr);
    pickerNodeLayout->UpdateUserDefinedIdealSize(
        CalcSize(NG::CalcLength(Dimension(1.0, DimensionUnit::PERCENT)), std::nullopt));
    pickerNodeLayout->UpdateCanLoop(settingData.canLoop);
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    OptionsShowInternal(textPickerPattern, settingData, textPickerNode, showCount, pickerTheme);
    SetDefaultPickerItemHeight(settingData.height);
    SetTextProperties(pickerTheme, settingData.properties);
    auto changeEvent = dialogEvent["changeId"];
    SetDialogChange(textPickerNode, std::move(changeEvent));

    ViewStackProcessor::GetInstance()->Finish();
    textPickerNode->MountToParent(contentColumn);
    auto dialogNode = DialogView::CreateDialogNode(dialogProperties, contentColumn);
    CHECK_NULL_RETURN(dialogNode, nullptr);
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    CHECK_NULL_RETURN(dialogPattern, nullptr);
    dialogPattern->SetIsPickerDiaglog(true);

    auto closeDiaglogEvent = CloseDiaglogEvent(textPickerPattern, dialogNode);
    auto closeCallBack = [func = std::move(closeDiaglogEvent)](const GestureEvent& /* info */) {
        func();
    };

    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipeline, nullptr);
    float scale = pipeline->GetFontScale();
    if (NeedAdaptForAging()) {
        dialogNode = SeparatedOptionsShow(contentColumn, textPickerNode, buttonInfos, settingData,
            dialogEvent, dialogCancelEvent, scale, closeCallBack, dialogNode);
        return dialogNode;
    }

    auto contentRow =
        CreateButtonNode(textPickerNode, buttonInfos, dialogEvent, std::move(dialogCancelEvent), closeCallBack);
    contentRow->AddChild(CreateDividerNode(textPickerNode), 1);
    contentRow->MountToParent(contentColumn);
    dialogNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    return dialogNode;
}

RefPtr<FrameNode> TextPickerDialogView::CreateIconItemNode(RefPtr<PickerTheme> pickerTheme)
{
    auto row = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    CHECK_NULL_RETURN(row, nullptr);
    auto layoutProps = row->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(layoutProps, nullptr);
    layoutProps->UpdateMainAxisAlign(FlexAlign::CENTER);
    layoutProps->UpdateCrossAxisAlign(FlexAlign::CENTER);

    MarginProperty marginProperty;
    marginProperty.left = CalcLength(pickerTheme->GetPaddingHorizontal());
    marginProperty.right = CalcLength(pickerTheme->GetPaddingHorizontal());
    layoutProps->UpdateMargin(marginProperty);

    auto imageNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    CHECK_NULL_RETURN(imageNode, nullptr);
    imageNode->MountToParent(row);

    return row;
}
RefPtr<FrameNode> TextPickerDialogView::CreateTextItemNode(RefPtr<PickerTheme> pickerTheme)
{
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textNode, nullptr);
    auto textLayout = textNode->GetLayoutProperty<TextLayoutProperty>();
    MarginProperty marginProperty;
    marginProperty.left = CalcLength(pickerTheme->GetPaddingHorizontal());
    marginProperty.right = CalcLength(pickerTheme->GetPaddingHorizontal());
    textLayout->UpdateMargin(marginProperty);
    return textNode;
}
RefPtr<FrameNode> TextPickerDialogView::CreateMixtureItemNode(RefPtr<PickerTheme> pickerTheme)
{
    auto row = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    CHECK_NULL_RETURN(row, nullptr);

    auto rowProperty = row->GetLayoutProperty<LinearLayoutProperty>();
    MarginProperty marginProperty;
    marginProperty.left = CalcLength(pickerTheme->GetPaddingHorizontal());
    marginProperty.right = CalcLength(pickerTheme->GetPaddingHorizontal());
    rowProperty->UpdateMargin(marginProperty);

    auto imageNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    CHECK_NULL_RETURN(imageNode, nullptr);
    imageNode->MountToParent(row);

    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textNode, nullptr);
    textNode->MountToParent(row);

    return row;
}

RefPtr<FrameNode> TextPickerDialogView::CreateColumnNode(
    uint32_t columnKind, uint32_t showCount, RefPtr<PickerTheme> pickerTheme)
{
    auto columnNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<TextPickerColumnPattern>(); });

    if (columnKind == ICON) {
        for (uint32_t index = 0; index < showCount; index++) {
            auto row = CreateIconItemNode(pickerTheme);
            CHECK_NULL_RETURN(row, nullptr);
            row->MountToParent(columnNode);
        }
    } else if (columnKind == TEXT) {
        for (uint32_t index = 0; index < showCount; index++) {
            auto textNode = CreateTextItemNode(pickerTheme);
            CHECK_NULL_RETURN(textNode, nullptr);
            textNode->MountToParent(columnNode);
        }
    } else if (columnKind == MIXTURE) {
        for (uint32_t index = 0; index < showCount; index++) {
            auto row = CreateMixtureItemNode(pickerTheme);
            CHECK_NULL_RETURN(row, nullptr);
            row->MountToParent(columnNode);
        }
    }
    return columnNode;
}

RefPtr<FrameNode> TextPickerDialogView::CreateStackNode(RefPtr<PickerTheme> pickerTheme)
{
    auto stackId = ElementRegister::GetInstance()->MakeUniqueId();
    auto stackNode = FrameNode::GetOrCreateFrameNode(
        V2::STACK_ETS_TAG, stackId, []() { return AceType::MakeRefPtr<StackPattern>(); });

    auto stackLayout = stackNode->GetLayoutProperty<LayoutProperty>();
    MarginProperty marginProperty;
    marginProperty.top = CalcLength(pickerTheme->GetContentMarginVertical());
    marginProperty.bottom = CalcLength(pickerTheme->GetContentMarginVertical());
    stackLayout->UpdateMargin(marginProperty);
    return stackNode;
}

RefPtr<FrameNode> TextPickerDialogView::CreateColumnNode()
{
    auto columnId = ElementRegister::GetInstance()->MakeUniqueId();
    return FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, columnId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
}

RefPtr<FrameNode> TextPickerDialogView::CreateButtonNode()
{
    auto buttonId = ElementRegister::GetInstance()->MakeUniqueId();
    return FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, buttonId, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
}

RefPtr<FrameNode> TextPickerDialogView::CreateDividerNode(const RefPtr<FrameNode>& dateNode)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    auto dividerNode = FrameNode::GetOrCreateFrameNode(V2::DIVIDER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<DividerPattern>(); });
    CHECK_NULL_RETURN(dividerNode, nullptr);

    auto dividerPaintProps = dividerNode->GetPaintProperty<DividerRenderProperty>();
    CHECK_NULL_RETURN(dividerPaintProps, nullptr);
    dividerPaintProps->UpdateDividerColor(dialogTheme->GetDividerColor());

    auto dividerLayoutProps = dividerNode->GetLayoutProperty<DividerLayoutProperty>();
    CHECK_NULL_RETURN(dividerLayoutProps, nullptr);
    dividerLayoutProps->UpdateVertical(true);
    dividerLayoutProps->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(dialogTheme->GetDividerWidth()), CalcLength(dialogTheme->GetDividerHeight())));
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        MarginProperty margin;
        margin.top = CalcLength(dialogTheme->GetDividerHeight());
        margin.bottom = CalcLength(dialogTheme->GetDividerPadding().Bottom());
        dividerLayoutProps->UpdateMargin(margin);
        dividerLayoutProps->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(dialogTheme->GetDividerWidth()), CalcLength(dialogTheme->GetDividerHeight())));
    } else {
        auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
        auto dividerWrapper = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(false));
        CHECK_NULL_RETURN(dividerWrapper, nullptr);
        auto layoutProps = dividerWrapper->GetLayoutProperty<LinearLayoutProperty>();
        CHECK_NULL_RETURN(layoutProps, nullptr);
        MarginProperty margin;
        margin.top = CalcLength(dialogTheme->GetActionsPadding().Top());
        margin.bottom = CalcLength(dialogTheme->GetActionsPadding().Bottom());
        layoutProps->UpdateMargin(margin);
        layoutProps->UpdateMainAxisAlign(FlexAlign::SPACE_AROUND);
        layoutProps->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
        layoutProps->UpdateUserDefinedIdealSize(CalcSize(
            CalcLength(dialogTheme->GetActionsPadding().Bottom()), CalcLength(buttonTheme->GetHeight())));
        dividerNode->MountToParent(dividerWrapper);
        return dividerWrapper;
    }

    return dividerNode;
}

RefPtr<FrameNode> TextPickerDialogView::CreateButtonNode(const RefPtr<FrameNode>& frameNode,
    const std::vector<ButtonInfo>& buttonInfos, std::map<std::string, NG::DialogTextEvent> dialogEvent,
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent, GestureEventFunc callback)
{
    auto acceptEvent = dialogEvent["acceptId"];
    auto cancelEvent = dialogCancelEvent["cancelId"];
    auto contentRow = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    CHECK_NULL_RETURN(contentRow, nullptr);
    auto layoutProps = contentRow->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(layoutProps, nullptr);
    layoutProps->UpdateMainAxisAlign(FlexAlign::SPACE_AROUND);
    layoutProps->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);

    auto buttonCancelNode = CreateCancelNode(cancelEvent, frameNode, buttonInfos);
    auto buttonConfirmNode = CreateConfirmNode(frameNode, frameNode, buttonInfos, acceptEvent);

    buttonCancelNode->MountToParent(contentRow);
    buttonConfirmNode->MountToParent(contentRow);

    auto onClick = AceType::MakeRefPtr<NG::ClickEvent>(std::move(callback));
    for (const auto& child : contentRow->GetChildren()) {
        auto childNode = AceType::DynamicCast<FrameNode>(child);
        CHECK_NULL_RETURN(childNode, nullptr);
        auto gestureHub = childNode->GetOrCreateGestureEventHub();
        CHECK_NULL_RETURN(gestureHub, nullptr);
        gestureHub->AddClickEvent(onClick);
    }

    return contentRow;
}

void TextPickerDialogView::UpdateButtonConfirmLayoutProperty(const RefPtr<FrameNode>& buttonConfirmNode,
    RefPtr<PickerTheme> pickerTheme)
{
    auto buttonConfirmLayoutProperty = buttonConfirmNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(buttonConfirmLayoutProperty);
    buttonConfirmLayoutProperty->UpdateLabel(Localization::GetInstance()->GetEntryLetters("common.ok"));
    buttonConfirmLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_THIRTEEN)) {
        buttonConfirmLayoutProperty->UpdateType(ButtonType::ROUNDED_RECTANGLE);
    } else {
        buttonConfirmLayoutProperty->UpdateType(ButtonType::CAPSULE);
    }
    buttonConfirmLayoutProperty->UpdateFlexShrink(1.0);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(dialogTheme);
    UpdateConfirmButtonMargin(buttonConfirmNode, dialogTheme);
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        buttonConfirmLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(pickerTheme->GetButtonWidth()), CalcLength(pickerTheme->GetButtonHeight())));
    } else {
        auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
        CHECK_NULL_VOID(buttonTheme);
        buttonConfirmLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(1.0, DimensionUnit::PERCENT), CalcLength(buttonTheme->GetHeight())));
    }
}

RefPtr<FrameNode> TextPickerDialogView::CreateConfirmNode(const RefPtr<FrameNode>& dateNode,
    const RefPtr<FrameNode>& textPickerNode, const std::vector<ButtonInfo>& buttonInfos, DialogEvent& acceptEvent)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(buttonConfirmNode, nullptr);
    CHECK_NULL_RETURN(textConfirmNode, nullptr);
    UpdateConfirmButtonTextLayoutProperty(textConfirmNode, pickerTheme);
    auto textPattern = textPickerNode->GetPattern<TextPickerPattern>();
    textPattern->SetConfirmNode(buttonConfirmNode);
    auto buttonConfirmEventHub = buttonConfirmNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_RETURN(buttonConfirmEventHub, nullptr);
    buttonConfirmEventHub->SetStateEffect(true);
    UpdateButtonConfirmLayoutProperty(buttonConfirmNode, pickerTheme);
    auto buttonConfirmRenderContext = buttonConfirmNode->GetRenderContext();
    buttonConfirmRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    auto buttonConfirmLayoutProperty = buttonConfirmNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_RETURN(buttonConfirmLayoutProperty, nullptr);
    UpdateButtonStyles(buttonInfos, ACCEPT_BUTTON_INDEX, buttonConfirmLayoutProperty, buttonConfirmRenderContext);
    UpdateButtonDefaultFocus(buttonInfos, buttonConfirmNode, true);

    textConfirmNode->MountToParent(buttonConfirmNode);
    auto eventConfirmHub = buttonConfirmNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(eventConfirmHub, nullptr);
    CHECK_NULL_RETURN(dateNode, nullptr);
    SetDialogAcceptEvent(dateNode, std::move(acceptEvent));
    auto clickCallback = [weak = WeakPtr<FrameNode>(dateNode)](const GestureEvent& /* info */) {
        auto dateNode = weak.Upgrade();
        CHECK_NULL_VOID(dateNode);
        auto pickerPattern = dateNode->GetPattern<TextPickerPattern>();
        CHECK_NULL_VOID(pickerPattern);
        auto str = pickerPattern->GetSelectedObject(false);
        auto textPickerEventHub = pickerPattern->GetEventHub<TextPickerEventHub>();
        CHECK_NULL_VOID(textPickerEventHub);
        textPickerEventHub->FireDialogAcceptEvent(str);
        if (Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
            Recorder::EventParamsBuilder builder;
            builder.SetType(dateNode->GetTag()).SetEventType(Recorder::EventType::DIALOG_ACCEPT).SetText(str);
            Recorder::EventRecorder::Get().OnEvent(std::move(builder));
        }
    };
    eventConfirmHub->AddClickEvent(AceType::MakeRefPtr<NG::ClickEvent>(clickCallback));
    buttonConfirmNode->MarkModifyDone();
    return buttonConfirmNode;
}

void TextPickerDialogView::UpdateConfirmButtonTextLayoutProperty(
    const RefPtr<FrameNode>& textConfirmNode, const RefPtr<PickerTheme>& pickerTheme)
{
    auto textLayoutProperty = textConfirmNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateContent(Localization::GetInstance()->GetEntryLetters("common.ok"));
    textLayoutProperty->UpdateTextColor(pickerTheme->GetOptionStyle(true, false).GetTextColor());
    if (!NeedAdaptForAging()) {
        textLayoutProperty->UpdateMaxFontScale(pickerTheme->GetNormalFontScale());
    }
    textLayoutProperty->UpdateFontSize(
        ConvertFontScaleValue(pickerTheme->GetOptionStyle(false, false).GetFontSize()));
    textLayoutProperty->UpdateFontWeight(pickerTheme->GetOptionStyle(true, false).GetFontWeight());
}

void TextPickerDialogView::UpdateCancelButtonTextLayoutProperty(
    const RefPtr<FrameNode>& textCancelNode, const RefPtr<PickerTheme>& pickerTheme)
{
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textCancelLayoutProperty);
    textCancelLayoutProperty->UpdateContent(Localization::GetInstance()->GetEntryLetters("common.cancel"));
    textCancelLayoutProperty->UpdateTextColor(pickerTheme->GetOptionStyle(true, false).GetTextColor());
    if (!NeedAdaptForAging()) {
        textCancelLayoutProperty->UpdateMaxFontScale(pickerTheme->GetNormalFontScale());
    }
    textCancelLayoutProperty->UpdateFontSize(
        ConvertFontScaleValue(pickerTheme->GetOptionStyle(false, false).GetFontSize()));
    textCancelLayoutProperty->UpdateFontWeight(pickerTheme->GetOptionStyle(true, false).GetFontWeight());
}

void TextPickerDialogView::UpdateForwardButtonTextLayoutProperty(
    const RefPtr<FrameNode>& textForwardNode, const RefPtr<PickerTheme>& pickerTheme)
{
    auto textForwardLayoutProperty = textForwardNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textForwardLayoutProperty);
    auto pickerThemeOptionStyle = pickerTheme->GetOptionStyle(true, false);
    textForwardLayoutProperty->UpdateContent(Localization::GetInstance()->GetEntryLetters("common.next"));
    textForwardLayoutProperty->UpdateTextColor(pickerThemeOptionStyle.GetTextColor());
    textForwardLayoutProperty->UpdateFontSize(
        ConvertFontScaleValue(pickerTheme->GetOptionStyle(false, false).GetFontSize()));
    textForwardLayoutProperty->UpdateFontWeight(pickerThemeOptionStyle.GetFontWeight());
}

void TextPickerDialogView::UpdateBackwardButtonTextLayoutProperty(
    const RefPtr<FrameNode>& textBackwardNode, const RefPtr<PickerTheme>& pickerTheme)
{
    auto textBackwardLayoutProperty = textBackwardNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textBackwardLayoutProperty);
    auto pickerThemeOptionStyle = pickerTheme->GetOptionStyle(true, false);
    textBackwardLayoutProperty->UpdateContent(Localization::GetInstance()->GetEntryLetters("common.prev"));
    textBackwardLayoutProperty->UpdateTextColor(pickerThemeOptionStyle.GetTextColor());
    textBackwardLayoutProperty->UpdateFontSize(
        ConvertFontScaleValue(pickerTheme->GetOptionStyle(false, false).GetFontSize()));
    textBackwardLayoutProperty->UpdateFontWeight(pickerThemeOptionStyle.GetFontWeight());
}

void TextPickerDialogView::UpdateConfirmButtonMargin(
    const RefPtr<FrameNode>& buttonConfirmNode, const RefPtr<DialogTheme>& dialogTheme)
{
    MarginProperty margin;
    bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        margin.top = CalcLength(dialogTheme->GetDividerHeight());
        margin.bottom = CalcLength(dialogTheme->GetDividerPadding().Bottom());
        if (isRtl) {
            margin.right = CalcLength(0.0_vp);
            margin.left = CalcLength(dialogTheme->GetDividerPadding().Left());
        } else {
            margin.right = CalcLength(dialogTheme->GetDividerPadding().Right());
            margin.left = CalcLength(0.0_vp);
        }

    } else {
        margin.top = CalcLength(dialogTheme->GetActionsPadding().Top());
        margin.bottom = CalcLength(dialogTheme->GetActionsPadding().Bottom());
        if (isRtl) {
            margin.right = CalcLength(0.0_vp);
            margin.left = CalcLength(dialogTheme->GetActionsPadding().Left());
        } else {
            margin.right = CalcLength(dialogTheme->GetActionsPadding().Right());
            margin.left = CalcLength(0.0_vp);
        }
    }
    buttonConfirmNode->GetLayoutProperty()->UpdateMargin(margin);
}

void TextPickerDialogView::UpdateCancelButtonMargin(
    const RefPtr<FrameNode>& buttonCancelNode, const RefPtr<DialogTheme>& dialogTheme)
{
    MarginProperty margin;
    bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        margin.top = CalcLength(dialogTheme->GetDividerHeight());
        margin.bottom = CalcLength(dialogTheme->GetDividerPadding().Bottom());
        if (isRtl) {
            margin.right = CalcLength(dialogTheme->GetDividerPadding().Right());
            margin.left = CalcLength(0.0_vp);
        } else {
            margin.right = CalcLength(0.0_vp);
            margin.left = CalcLength(dialogTheme->GetDividerPadding().Left());
        }
    } else {
        margin.top = CalcLength(dialogTheme->GetActionsPadding().Top());
        margin.bottom = CalcLength(dialogTheme->GetActionsPadding().Bottom());
        if (isRtl) {
            margin.right = CalcLength(dialogTheme->GetActionsPadding().Right());
            margin.left = CalcLength(0.0_vp);
        } else {
            margin.right = CalcLength(0.0_vp);
            margin.left = CalcLength(dialogTheme->GetActionsPadding().Left());
        }
    }
    buttonCancelNode->GetLayoutProperty()->UpdateMargin(margin);
}

void TextPickerDialogView::UpdateForwardButtonMargin(
    const RefPtr<FrameNode>& buttonForwardNode, const RefPtr<DialogTheme>& dialogTheme)
{
    MarginProperty margin;
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        margin.right = CalcLength(dialogTheme->GetDividerPadding().Right());
        margin.top = CalcLength(dialogTheme->GetDividerHeight());
        margin.bottom = CalcLength(dialogTheme->GetDividerPadding().Bottom());
        margin.left = CalcLength(0.0_vp);
    } else {
        margin.right = CalcLength(dialogTheme->GetDividerPadding().Right());
        margin.top = CalcLength(dialogTheme->GetActionsPadding().Top());
        margin.bottom = CalcLength(dialogTheme->GetActionsPadding().Bottom());
        margin.left = CalcLength(0.0_vp);
    }
    buttonForwardNode->GetLayoutProperty()->UpdateMargin(margin);
}

void TextPickerDialogView::UpdateBackwardButtonMargin(
    const RefPtr<FrameNode>& buttonBackwardNode, const RefPtr<DialogTheme>& dialogTheme)
{
    MarginProperty margin;
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        margin.left = CalcLength(dialogTheme->GetDividerPadding().Left());
        margin.top = CalcLength(dialogTheme->GetDividerHeight());
        margin.bottom = CalcLength(dialogTheme->GetDividerPadding().Bottom());
        margin.right = CalcLength(0.0_vp);
    } else {
        margin.left = CalcLength(dialogTheme->GetActionsPadding().Left());
        margin.top = CalcLength(dialogTheme->GetActionsPadding().Top());
        margin.bottom = CalcLength(dialogTheme->GetActionsPadding().Bottom());
        margin.right = CalcLength(0.0_vp);
    }
    buttonBackwardNode->GetLayoutProperty()->UpdateMargin(margin);
}

void TextPickerDialogView::UpdateButtonStyles(const std::vector<ButtonInfo>& buttonInfos, size_t index,
    const RefPtr<ButtonLayoutProperty>& buttonLayoutProperty, const RefPtr<RenderContext>& buttonRenderContext)
{
    if (index >= buttonInfos.size()) {
        return;
    }
    CHECK_NULL_VOID(buttonLayoutProperty);
    CHECK_NULL_VOID(buttonRenderContext);
    auto buttonTheme = PipelineBase::GetCurrentContext()->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(buttonTheme);
    if (buttonInfos[index].type.has_value()) {
        buttonLayoutProperty->UpdateType(buttonInfos[index].type.value());
    }
    UpdateButtonStyleAndRole(buttonInfos, index, buttonLayoutProperty, buttonRenderContext, buttonTheme);
    if (buttonInfos[index].fontSize.has_value()) {
        buttonLayoutProperty->UpdateFontSize(ConvertFontScaleValue(buttonInfos[index].fontSize.value()));
    }
    if (buttonInfos[index].fontColor.has_value()) {
        buttonLayoutProperty->UpdateFontColor(buttonInfos[index].fontColor.value());
    }
    if (buttonInfos[index].fontWeight.has_value()) {
        buttonLayoutProperty->UpdateFontWeight(buttonInfos[index].fontWeight.value());
    }
    if (buttonInfos[index].fontStyle.has_value()) {
        buttonLayoutProperty->UpdateFontStyle(buttonInfos[index].fontStyle.value());
    }
    if (buttonInfos[index].fontFamily.has_value()) {
        buttonLayoutProperty->UpdateFontFamily(buttonInfos[index].fontFamily.value());
    }
    if (buttonInfos[index].borderRadius.has_value()) {
        buttonLayoutProperty->UpdateBorderRadius(buttonInfos[index].borderRadius.value());
    }
    if (buttonInfos[index].backgroundColor.has_value()) {
        buttonRenderContext->UpdateBackgroundColor(buttonInfos[index].backgroundColor.value());
    }
}

void TextPickerDialogView::UpdateButtonStyleAndRole(const std::vector<ButtonInfo>& buttonInfos, size_t index,
    const RefPtr<ButtonLayoutProperty>& buttonLayoutProperty, const RefPtr<RenderContext>& buttonRenderContext,
    const RefPtr<ButtonTheme>& buttonTheme)
{
    if (index >= buttonInfos.size()) {
        return;
    }
    CHECK_NULL_VOID(buttonLayoutProperty);
    CHECK_NULL_VOID(buttonRenderContext);
    CHECK_NULL_VOID(buttonTheme);
    if (buttonInfos[index].role.has_value()) {
        buttonLayoutProperty->UpdateButtonRole(buttonInfos[index].role.value());
        ButtonStyleMode buttonStyleMode;
        if (buttonInfos[index].buttonStyle.has_value()) {
            buttonStyleMode = buttonInfos[index].buttonStyle.value();
        } else {
            buttonStyleMode = buttonLayoutProperty->GetButtonStyle().value_or(ButtonStyleMode::EMPHASIZE);
        }
        auto bgColor = buttonTheme->GetBgColor(buttonStyleMode, buttonInfos[index].role.value());
        auto textColor = buttonTheme->GetTextColor(buttonStyleMode, buttonInfos[index].role.value());
        buttonRenderContext->UpdateBackgroundColor(bgColor);
        buttonLayoutProperty->UpdateFontColor(textColor);
    }
    if (buttonInfos[index].buttonStyle.has_value()) {
        buttonLayoutProperty->UpdateButtonStyle(buttonInfos[index].buttonStyle.value());
        ButtonRole buttonRole = buttonLayoutProperty->GetButtonRole().value_or(ButtonRole::NORMAL);
        auto bgColor = buttonTheme->GetBgColor(buttonInfos[index].buttonStyle.value(), buttonRole);
        auto textColor = buttonTheme->GetTextColor(buttonInfos[index].buttonStyle.value(), buttonRole);
        buttonRenderContext->UpdateBackgroundColor(bgColor);
        buttonLayoutProperty->UpdateFontColor(textColor);
    }
}

RefPtr<FrameNode> TextPickerDialogView::CreateCancelNode(NG::DialogGestureEvent& cancelEvent,
    const RefPtr<FrameNode>& textPickerNode, const std::vector<ButtonInfo>& buttonInfos)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_RETURN(buttonCancelNode, nullptr);
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textCancelNode, nullptr);
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    UpdateCancelButtonTextLayoutProperty(textCancelNode, pickerTheme);
    auto textPattern = textPickerNode->GetPattern<TextPickerPattern>();
    textPattern->SetCancelNode(buttonCancelNode);
    textCancelNode->MountToParent(buttonCancelNode);
    auto eventCancelHub = buttonCancelNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(eventCancelHub, nullptr);
    eventCancelHub->AddClickEvent(AceType::MakeRefPtr<NG::ClickEvent>(std::move(cancelEvent)));
    auto recordEvent = [](GestureEvent& info) {
        if (Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
            Recorder::EventParamsBuilder builder;
            builder.SetType("TextPickerDialog").SetEventType(Recorder::EventType::DIALOG_CANCEL);
            Recorder::EventRecorder::Get().OnEvent(std::move(builder));
        }
    };
    auto recordEventPtr = AceType::MakeRefPtr<ClickEvent>(std::move(recordEvent));
    eventCancelHub->AddClickEvent(recordEventPtr);

    auto buttonCancelEventHub = buttonCancelNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_RETURN(buttonCancelEventHub, nullptr);
    buttonCancelEventHub->SetStateEffect(true);

    UpdateButtonCancelLayoutProperty(buttonCancelNode, pipeline);
    
    auto buttonCancelRenderContext = buttonCancelNode->GetRenderContext();
    buttonCancelRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    auto buttonCancelLayoutProperty = buttonCancelNode->GetLayoutProperty<ButtonLayoutProperty>();
    UpdateButtonStyles(buttonInfos, CANCEL_BUTTON_INDEX, buttonCancelLayoutProperty, buttonCancelRenderContext);
    UpdateButtonDefaultFocus(buttonInfos, buttonCancelNode, false);

    buttonCancelNode->MarkModifyDone();
    return buttonCancelNode;
}


void TextPickerDialogView::UpdateButtonCancelLayoutProperty(
    const RefPtr<FrameNode>& buttonCancelNode, const RefPtr<PipelineContext>& pipeline)
{
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    UpdateCancelButtonMargin(buttonCancelNode, dialogTheme);
    auto buttonCancelLayoutProperty = buttonCancelNode->GetLayoutProperty<ButtonLayoutProperty>();
    buttonCancelLayoutProperty->UpdateLabel(Localization::GetInstance()->GetEntryLetters("common.cancel"));
    buttonCancelLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_THIRTEEN)) {
        buttonCancelLayoutProperty->UpdateType(ButtonType::ROUNDED_RECTANGLE);
    } else {
        buttonCancelLayoutProperty->UpdateType(ButtonType::CAPSULE);
    }
    buttonCancelLayoutProperty->UpdateFlexShrink(1.0);
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        buttonCancelLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(pickerTheme->GetButtonWidth()), CalcLength(pickerTheme->GetButtonHeight())));
    } else {
        buttonCancelLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(1.0, DimensionUnit::PERCENT), CalcLength(buttonTheme->GetHeight())));
    }
}

void TextPickerDialogView::UpdateButtonForwardLayoutProperty(
    const RefPtr<FrameNode>& buttonForwardNode, const RefPtr<PipelineContext>& pipeline)
{
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(buttonTheme);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    UpdateForwardButtonMargin(buttonForwardNode, dialogTheme);
    auto buttonForwardLayoutProperty = buttonForwardNode->GetLayoutProperty<ButtonLayoutProperty>();
    buttonForwardLayoutProperty->UpdateLabel(Localization::GetInstance()->GetEntryLetters("common.next"));
    buttonForwardLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_THIRTEEN)) {
        buttonForwardLayoutProperty->UpdateType(ButtonType::ROUNDED_RECTANGLE);
    } else {
        buttonForwardLayoutProperty->UpdateType(ButtonType::CAPSULE);
    }
    buttonForwardLayoutProperty->UpdateFlexShrink(1.0);
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        buttonForwardLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(pickerTheme->GetButtonWidth()), CalcLength(pickerTheme->GetButtonHeight())));
    } else {
        buttonForwardLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(1.0, DimensionUnit::PERCENT), CalcLength(buttonTheme->GetHeight())));
    }
}

void TextPickerDialogView::UpdateButtonBackwardLayoutProperty(
    const RefPtr<FrameNode>& buttonBackwardNode, const RefPtr<PipelineContext>& pipeline)
{
    CHECK_NULL_VOID(pipeline);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(buttonTheme);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    UpdateBackwardButtonMargin(buttonBackwardNode, dialogTheme);
    auto buttonBackwardLayoutProperty = buttonBackwardNode->GetLayoutProperty<ButtonLayoutProperty>();
    buttonBackwardLayoutProperty->UpdateLabel(Localization::GetInstance()->GetEntryLetters("common.prev"));
    buttonBackwardLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_THIRTEEN)) {
        buttonBackwardLayoutProperty->UpdateType(ButtonType::ROUNDED_RECTANGLE);
    } else {
        buttonBackwardLayoutProperty->UpdateType(ButtonType::CAPSULE);
    }
    buttonBackwardLayoutProperty->UpdateFlexShrink(1.0);
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        buttonBackwardLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(pickerTheme->GetButtonWidth()), CalcLength(pickerTheme->GetButtonHeight())));
    } else {
        buttonBackwardLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(1.0, DimensionUnit::PERCENT), CalcLength(buttonTheme->GetHeight())));
    }
}

void TextPickerDialogView::SetSelected(const RefPtr<TextPickerPattern>& textPickerPattern, uint32_t value)
{
    textPickerPattern->SetSelected(value);
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, Selected, value);
}

void TextPickerDialogView::SetSelectedValues(
    const RefPtr<TextPickerPattern>& textPickerPattern, const std::vector<uint32_t>& values)
{
    textPickerPattern->SetSelecteds(values);
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, Selecteds, values);
}

void TextPickerDialogView::SetValues(
    const RefPtr<TextPickerPattern>& textPickerPattern, const std::vector<std::string>& values)
{
    textPickerPattern->SetValues(values);
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, Values, values);
}

void TextPickerDialogView::SetRange(
    const RefPtr<TextPickerPattern>& textPickerPattern, const std::vector<NG::RangeContent>& value)
{
    textPickerPattern->SetRange(value);
}

void TextPickerDialogView::SetTextProperties(
    const RefPtr<PickerTheme>& pickerTheme, const PickerTextProperties& properties)
{
    CHECK_NULL_VOID(pickerTheme);
    auto selectedStyle = pickerTheme->GetOptionStyle(true, false);
    auto normalStyle = pickerTheme->GetOptionStyle(false, false);

    SetTextDisappearProperties(pickerTheme, properties);

    if (properties.normalTextStyle_.fontSize.has_value() && properties.normalTextStyle_.fontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, FontSize,
            ConvertFontScaleValue(properties.normalTextStyle_.fontSize.value(), normalTextStyleFont_, true));
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, FontSize,
            ConvertFontScaleValue(normalStyle.GetFontSize()));
    }
    ACE_UPDATE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, Color, properties.normalTextStyle_.textColor.value_or(normalStyle.GetTextColor()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, Weight, properties.normalTextStyle_.fontWeight.value_or(normalStyle.GetFontWeight()));
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, FontFamily,
        properties.normalTextStyle_.fontFamily.value_or(normalStyle.GetFontFamilies()));
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, FontStyle,
        properties.normalTextStyle_.fontStyle.value_or(normalStyle.GetFontStyle()));

    if (properties.selectedTextStyle_.fontSize.has_value() && properties.selectedTextStyle_.fontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(
            TextPickerLayoutProperty, SelectedFontSize,
            ConvertFontScaleValue(properties.selectedTextStyle_.fontSize.value(), selectedTextStyleFont_, true));
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedFontSize,
            ConvertFontScaleValue(selectedStyle.GetFontSize()));
    }
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedColor,
        properties.selectedTextStyle_.textColor.value_or(selectedStyle.GetTextColor()));
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedWeight,
        properties.selectedTextStyle_.fontWeight.value_or(selectedStyle.GetFontWeight()));
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedFontFamily,
        properties.selectedTextStyle_.fontFamily.value_or(selectedStyle.GetFontFamilies()));
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedFontStyle,
        properties.selectedTextStyle_.fontStyle.value_or(selectedStyle.GetFontStyle()));
}

void TextPickerDialogView::SetTextDisappearProperties(
    const RefPtr<PickerTheme>& pickerTheme, const PickerTextProperties& properties)

{
    CHECK_NULL_VOID(pickerTheme);
    auto disappearStyle = pickerTheme->GetDisappearOptionStyle();
    if (properties.disappearTextStyle_.fontSize.has_value() && properties.disappearTextStyle_.fontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(
            TextPickerLayoutProperty, DisappearFontSize,
            ConvertFontScaleValue(properties.disappearTextStyle_.fontSize.value(), disappearTextStyleFont_, true));
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DisappearFontSize,
            ConvertFontScaleValue(disappearStyle.GetFontSize()));
    }
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DisappearColor,
        properties.disappearTextStyle_.textColor.value_or(disappearStyle.GetTextColor()));
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DisappearWeight,
        properties.disappearTextStyle_.fontWeight.value_or(disappearStyle.GetFontWeight()));
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DisappearFontFamily,
        properties.disappearTextStyle_.fontFamily.value_or(disappearStyle.GetFontFamilies()));
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DisappearFontStyle,
        properties.disappearTextStyle_.fontStyle.value_or(disappearStyle.GetFontStyle()));
}

void TextPickerDialogView::SetDialogChange(const RefPtr<FrameNode>& frameNode, DialogTextEvent&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<TextPickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetDialogChange(std::move(onChange));
}

void TextPickerDialogView::SetDefaultPickerItemHeight(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DefaultPickerItemHeight, value);
}

void TextPickerDialogView::SetDialogAcceptEvent(const RefPtr<FrameNode>& frameNode, DialogTextEvent&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<TextPickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetDialogAcceptEvent(std::move(onChange));
}

void TextPickerDialogView::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    auto onKeyEvent = [](const KeyEvent& event) -> bool { return TextPickerDialogView::OnKeyEvent(event); };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));
}
bool TextPickerDialogView::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }

    if (event.code == KeyCode::KEY_ESCAPE) {
        auto pipeline = PipelineContext::GetCurrentContext();
        auto overlayManager = pipeline->GetOverlayManager();
        auto dialogNode = dialogNode_.Upgrade();
        CHECK_NULL_RETURN(dialogNode, false);
        overlayManager->CloseDialog(dialogNode);
        return true;
    }

    return false;
}

void TextPickerDialogView::UpdateButtonDefaultFocus(const std::vector<ButtonInfo>& buttonInfos,
    const RefPtr<FrameNode>& buttonNode, bool isConfirm)
{
    bool setDefaultFocus = false;
    if (buttonInfos.size() > CANCEL_BUTTON_INDEX) {
        if (buttonInfos[ACCEPT_BUTTON_INDEX].isPrimary && buttonInfos[CANCEL_BUTTON_INDEX].isPrimary) {
            return;
        }
        auto index = isConfirm ? ACCEPT_BUTTON_INDEX : CANCEL_BUTTON_INDEX;
        if (buttonInfos[index].isPrimary) {
            setDefaultFocus = true;
        }
    } else if (buttonInfos.size() == CANCEL_BUTTON_INDEX) {
        bool isAcceptButtonPrimary = (buttonInfos[0].isAcceptButton && isConfirm && buttonInfos[0].isPrimary);
        bool isCancelButtonPrimary = (!buttonInfos[0].isAcceptButton && !isConfirm && buttonInfos[0].isPrimary);
        if (isAcceptButtonPrimary || isCancelButtonPrimary) {
            setDefaultFocus = true;
        }
    }
    if (setDefaultFocus && buttonNode) {
        auto focusHub = buttonNode->GetOrCreateFocusHub();
        if (focusHub) {
            focusHub->SetIsDefaultFocus(true);
        }
    }
}

RefPtr<FrameNode> TextPickerDialogView::CreateForwardNode(NG::DialogGestureEvent& moveForwardEvent,
    const RefPtr<FrameNode>& textPickerNode, const std::vector<ButtonInfo>& buttonInfos)
{
    CHECK_NULL_RETURN(textPickerNode, nullptr);
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, nullptr);
    auto buttonForwardNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_RETURN(buttonForwardNode, nullptr);
    auto textForwardNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textForwardNode, nullptr);
    UpdateForwardButtonTextLayoutProperty(textForwardNode, pickerTheme);
    auto textPattern = textPickerNode->GetPattern<TextPickerPattern>();
    textPattern->SetForwardNode(buttonForwardNode);
    textForwardNode->MountToParent(buttonForwardNode);
    auto eventForwardHub = buttonForwardNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(eventForwardHub, nullptr);
    eventForwardHub->AddClickEvent(AceType::MakeRefPtr<NG::ClickEvent>(std::move(moveForwardEvent)));
    auto recordEvent = [](GestureEvent& info) {
        if (Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
            Recorder::EventParamsBuilder builder;
            builder.SetType("TextPickerDialog").SetEventType(Recorder::EventType::STEPPER_NEXT);
            Recorder::EventRecorder::Get().OnEvent(std::move(builder));
        }
    };
    auto recordEventPtr = AceType::MakeRefPtr<ClickEvent>(std::move(recordEvent));
    eventForwardHub->AddClickEvent(recordEventPtr);

    auto buttonForwardEventHub = buttonForwardNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_RETURN(buttonForwardEventHub, nullptr);
    buttonForwardEventHub->SetStateEffect(true);

    UpdateButtonForwardLayoutProperty(buttonForwardNode, pipeline);
    
    const auto& buttonForwardRenderContext = buttonForwardNode->GetRenderContext();
    buttonForwardRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    auto buttonForwardLayoutProperty = buttonForwardNode->GetLayoutProperty<ButtonLayoutProperty>();
    UpdateButtonStyles(buttonInfos, ACCEPT_BUTTON_INDEX, buttonForwardLayoutProperty, buttonForwardRenderContext);
    UpdateButtonDefaultFocus(buttonInfos, buttonForwardNode, false);

    buttonForwardNode->MarkModifyDone();
    return buttonForwardNode;
}

RefPtr<FrameNode> TextPickerDialogView::CreateBackwardNode(NG::DialogGestureEvent& moveBackwardEvent,
    const RefPtr<FrameNode>& textPickerNode, const std::vector<ButtonInfo>& buttonInfos)
{
    CHECK_NULL_RETURN(textPickerNode, nullptr);
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, nullptr);
    auto buttonBackwardNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_RETURN(buttonBackwardNode, nullptr);
    auto textBackwardNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textBackwardNode, nullptr);
    UpdateBackwardButtonTextLayoutProperty(textBackwardNode, pickerTheme);
    auto textPattern = textPickerNode->GetPattern<TextPickerPattern>();
    textPattern->SetBackwardNode(buttonBackwardNode);
    textBackwardNode->MountToParent(buttonBackwardNode);
    auto eventBackwardHub = buttonBackwardNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(eventBackwardHub, nullptr);
    eventBackwardHub->AddClickEvent(AceType::MakeRefPtr<NG::ClickEvent>(std::move(moveBackwardEvent)));
    auto recordEvent = [](GestureEvent& info) {
        if (Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
            Recorder::EventParamsBuilder builder;
            builder.SetType("TextPickerDialog").SetEventType(Recorder::EventType::STEPPER_NEXT);
            Recorder::EventRecorder::Get().OnEvent(std::move(builder));
        }
    };
    auto recordEventPtr = AceType::MakeRefPtr<ClickEvent>(std::move(recordEvent));
    eventBackwardHub->AddClickEvent(recordEventPtr);

    auto buttonBackwardEventHub = buttonBackwardNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_RETURN(buttonBackwardEventHub, nullptr);
    buttonBackwardEventHub->SetStateEffect(true);

    UpdateButtonBackwardLayoutProperty(buttonBackwardNode, pipeline);
    
    const auto& buttonBackwardRenderContext = buttonBackwardNode->GetRenderContext();
    buttonBackwardRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    auto buttonBackwardLayoutProperty = buttonBackwardNode->GetLayoutProperty<ButtonLayoutProperty>();
    UpdateButtonStyles(buttonInfos, CANCEL_BUTTON_INDEX, buttonBackwardLayoutProperty, buttonBackwardRenderContext);
    UpdateButtonDefaultFocus(buttonInfos, buttonBackwardNode, false);

    buttonBackwardNode->MarkModifyDone();
    return buttonBackwardNode;
}

void TextPickerDialogView::SetFirstDialogButtonActive(RefPtr<UINode>& contentRow)
{
    CHECK_NULL_VOID(contentRow);
    auto buttonCancel = contentRow->GetFirstChild();
    auto buttonCancelNode = AceType::DynamicCast<FrameNode>(buttonCancel);
    CHECK_NULL_VOID(buttonCancelNode);
    auto buttonCancelLayoutProperty = buttonCancelNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(buttonCancelLayoutProperty);
    buttonCancelLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);

    auto buttonForward = contentRow->GetChildAtIndex(FORWAED_BUTTON_DIVEDER_INDEX);
    auto buttonForwardNode = AceType::DynamicCast<FrameNode>(buttonForward);
    CHECK_NULL_VOID(buttonForwardNode);
    auto buttonForwardLayoutProperty = buttonForwardNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(buttonForwardLayoutProperty);
    buttonForwardLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);

    auto buttonBackward = contentRow->GetChildAtIndex(BACKWARD_BUTTON_DIVEDER_INDEX);
    auto buttonBackwardNode = AceType::DynamicCast<FrameNode>(buttonBackward);
    CHECK_NULL_VOID(buttonBackwardNode);
    auto buttonBackwardLayoutProperty = buttonBackwardNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(buttonBackwardLayoutProperty);
    buttonBackwardLayoutProperty->UpdateVisibility(VisibleType::GONE);

    auto buttonConfirm = contentRow->GetChildAtIndex(CONFIRM_BUTTON_DIVEDER_INDEX);
    auto buttonConfirmNode = AceType::DynamicCast<FrameNode>(buttonConfirm);
    CHECK_NULL_VOID(buttonConfirmNode);
    auto buttonConfirmLayoutProperty = buttonConfirmNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(buttonConfirmLayoutProperty);
    buttonConfirmLayoutProperty->UpdateVisibility(VisibleType::GONE);
}

void TextPickerDialogView::SetSecondDialogButtonActive(RefPtr<UINode>& contentRow)
{
    CHECK_NULL_VOID(contentRow);
    auto buttonCancel = contentRow->GetFirstChild();
    auto buttonCancelNode = AceType::DynamicCast<FrameNode>(buttonCancel);
    CHECK_NULL_VOID(buttonCancelNode);
    auto buttonCancelLayoutProperty = buttonCancelNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(buttonCancelLayoutProperty);
    buttonCancelLayoutProperty->UpdateVisibility(VisibleType::GONE);

    auto buttonForward = contentRow->GetChildAtIndex(FORWAED_BUTTON_DIVEDER_INDEX);
    auto buttonForwardNode = AceType::DynamicCast<FrameNode>(buttonForward);
    CHECK_NULL_VOID(buttonForwardNode);
    auto buttonForwardLayoutProperty = buttonForwardNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(buttonForwardLayoutProperty);
    buttonForwardLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);

    auto buttonBackward = contentRow->GetChildAtIndex(BACKWARD_BUTTON_DIVEDER_INDEX);
    auto buttonBackwardNode = AceType::DynamicCast<FrameNode>(buttonBackward);
    CHECK_NULL_VOID(buttonBackwardNode);
    auto buttonBackwardLayoutProperty = buttonBackwardNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(buttonBackwardLayoutProperty);
    buttonBackwardLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);

    auto buttonConfirm = contentRow->GetChildAtIndex(CONFIRM_BUTTON_DIVEDER_INDEX);
    auto buttonConfirmNode = AceType::DynamicCast<FrameNode>(buttonConfirm);
    CHECK_NULL_VOID(buttonConfirmNode);
    auto buttonConfirmLayoutProperty = buttonConfirmNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(buttonConfirmLayoutProperty);
    buttonConfirmLayoutProperty->UpdateVisibility(VisibleType::GONE);
}

void TextPickerDialogView::SetThirdDialogButtonActive(RefPtr<UINode>& contentRow)
{
    CHECK_NULL_VOID(contentRow);
    auto buttonCancel = contentRow->GetFirstChild();
    auto buttonCancelNode = AceType::DynamicCast<FrameNode>(buttonCancel);
    CHECK_NULL_VOID(buttonCancelNode);
    auto buttonCancelLayoutProperty = buttonCancelNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(buttonCancelLayoutProperty);
    buttonCancelLayoutProperty->UpdateVisibility(VisibleType::GONE);

    auto buttonForward = contentRow->GetChildAtIndex(FORWAED_BUTTON_DIVEDER_INDEX);
    auto buttonForwardNode = AceType::DynamicCast<FrameNode>(buttonForward);
    CHECK_NULL_VOID(buttonForwardNode);
    auto buttonForwardLayoutProperty = buttonForwardNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(buttonForwardLayoutProperty);
    buttonForwardLayoutProperty->UpdateVisibility(VisibleType::GONE);

    auto buttonBackward = contentRow->GetChildAtIndex(BACKWARD_BUTTON_DIVEDER_INDEX);
    auto buttonBackwardNode = AceType::DynamicCast<FrameNode>(buttonBackward);
    CHECK_NULL_VOID(buttonBackwardNode);
    auto buttonBackwardLayoutProperty = buttonBackwardNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(buttonBackwardLayoutProperty);
    buttonBackwardLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);

    auto buttonConfirm = contentRow->GetChildAtIndex(CONFIRM_BUTTON_DIVEDER_INDEX);
    auto buttonConfirmNode = AceType::DynamicCast<FrameNode>(buttonConfirm);
    CHECK_NULL_VOID(buttonConfirmNode);
    auto buttonConfirmLayoutProperty = buttonConfirmNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(buttonConfirmLayoutProperty);
    buttonConfirmLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
}

void TextPickerDialogView::SetDialogButtonActive(RefPtr<FrameNode>& contentColumn,
    const uint32_t& dialogNodePage, const uint32_t& columnCount)
{
    CHECK_NULL_VOID(contentColumn);
    auto contentRow = contentColumn->GetLastChild();
    if (dialogNodePage == 0) {
        SetFirstDialogButtonActive(contentRow);
        SetDividerNodeActive(contentRow, true, false, false);
    } else if (columnCount > 0 && dialogNodePage != (columnCount - 1)) {
        SetSecondDialogButtonActive(contentRow);
        SetDividerNodeActive(contentRow, false, true, false);
    } else {
        SetThirdDialogButtonActive(contentRow);
        SetDividerNodeActive(contentRow, false, false, true);
    }
}

void TextPickerDialogView::SetDividerNodeActive(RefPtr<UINode>& contentRow, bool firstDividerActive,
    bool secondDividerActive, bool thirdDividerActive)
{
    CHECK_NULL_VOID(contentRow);
    auto firstDivider = contentRow->GetChildAtIndex(1);
    auto firstDividerNode = AceType::DynamicCast<FrameNode>(firstDivider);
    CHECK_NULL_VOID(firstDividerNode);
    auto secondDivider = contentRow->GetChildAtIndex(SECOND_DIVEDER_NODE_INDEX);
    auto secondDividerNode = AceType::DynamicCast<FrameNode>(secondDivider);
    CHECK_NULL_VOID(secondDividerNode);
    auto thirdDivider = contentRow->GetChildAtIndex(THIRD_DIVEDER_NODE_INDEX);
    auto thirdDividerNode = AceType::DynamicCast<FrameNode>(thirdDivider);
    CHECK_NULL_VOID(thirdDividerNode);

    SetSingleDividerNodeActive(firstDividerNode, firstDividerActive);
    SetSingleDividerNodeActive(secondDividerNode, secondDividerActive);
    SetSingleDividerNodeActive(thirdDividerNode, thirdDividerActive);
}

void TextPickerDialogView::SetSingleDividerNodeActive(RefPtr<FrameNode>& dividerNode, bool dividerActive)
{
    CHECK_NULL_VOID(dividerNode);
    auto dividerLayoutProperty = dividerNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(dividerLayoutProperty);
    if (dividerActive) {
        dividerLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    } else {
        dividerLayoutProperty->UpdateVisibility(VisibleType::GONE);
    }
}

void TextPickerDialogView::SetDialogNodePageActive(RefPtr<FrameNode>& contentColumn,
    RefPtr<FrameNode>& textPickerNode,
    const uint32_t& dialogNodePage, const uint32_t& columnCount)
{
    CHECK_NULL_VOID(textPickerNode);
    for (uint32_t i = 0; i < columnCount; i++) {
        auto selectedStackNode = AceType::DynamicCast<FrameNode>(textPickerNode->GetChildAtIndex(i));
        CHECK_NULL_VOID(selectedStackNode);
        if (i != dialogNodePage) {
            auto layoutProperty = selectedStackNode->GetLayoutProperty<LayoutProperty>();
            CHECK_NULL_VOID(layoutProperty);
            layoutProperty->UpdateLayoutWeight(0);
            for (auto& child : selectedStackNode->GetChildren()) {
                auto childNode = AceType::DynamicCast<FrameNode>(child);
                CHECK_NULL_VOID(childNode);
                auto childNodeProperty = childNode->GetLayoutProperty<LayoutProperty>();
                childNodeProperty->UpdateVisibility(VisibleType::GONE);
            }
        } else {
            auto layoutProperty = selectedStackNode->GetLayoutProperty<LayoutProperty>();
            CHECK_NULL_VOID(layoutProperty);
            layoutProperty->UpdateLayoutWeight(1);
            for (auto& child : selectedStackNode->GetChildren()) {
                auto childNode = AceType::DynamicCast<FrameNode>(child);
                CHECK_NULL_VOID(childNode);
                auto childNodeProperty = childNode->GetLayoutProperty<LayoutProperty>();
                childNodeProperty->UpdateVisibility(VisibleType::VISIBLE);
            }
        }
    }
    SetDialogButtonActive(contentColumn, dialogNodePage, columnCount);
}

RefPtr<FrameNode> TextPickerDialogView::CreateAgingButtonNode(
    RefPtr<FrameNode>& frameNode,
    const std::vector<ButtonInfo>& buttonInfos,
    std::map<std::string, NG::DialogTextEvent> dialogEvent,
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent,
    std::map<std::string, NG::DialogGestureEvent> dialogMoveForwardEvent,
    std::map<std::string, NG::DialogGestureEvent> dialogMoveBackwardEvent,
    GestureEventFunc closeCallback, GestureEventFunc nextCallBack, GestureEventFunc previousCallBack)
{
    auto acceptEvent = dialogEvent["acceptId"];
    auto cancelEvent = dialogCancelEvent["cancelId"];
    auto moveForwardEvent = dialogMoveForwardEvent["moveForwardId"];
    auto moveBackwardEvent = dialogMoveBackwardEvent["moveBackwardId"];

    auto contentRow = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    CHECK_NULL_RETURN(contentRow, nullptr);
    auto layoutProps = contentRow->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(layoutProps, nullptr);
    layoutProps->UpdateMainAxisAlign(FlexAlign::CENTER);
    layoutProps->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);

    auto buttonCancelNode = CreateCancelNode(cancelEvent, frameNode, buttonInfos);
    CHECK_NULL_RETURN(buttonCancelNode, nullptr);
    auto buttonConfirmNode = CreateConfirmNode(frameNode, frameNode, buttonInfos, acceptEvent);
    CHECK_NULL_RETURN(buttonConfirmNode, nullptr);
    auto buttonForwardNode = CreateForwardNode(moveForwardEvent, frameNode, buttonInfos);
    CHECK_NULL_RETURN(buttonForwardNode, nullptr);
    auto buttonBackwardNode = CreateBackwardNode(moveBackwardEvent, frameNode, buttonInfos);
    CHECK_NULL_RETURN(buttonBackwardNode, nullptr);

    buttonCancelNode->MountToParent(contentRow);
    buttonBackwardNode->MountToParent(contentRow);
    buttonForwardNode->MountToParent(contentRow);
    buttonConfirmNode->MountToParent(contentRow);

    auto closeClick = AceType::MakeRefPtr<NG::ClickEvent>(std::move(closeCallback));
    auto nextClick = AceType::MakeRefPtr<NG::ClickEvent>(std::move(nextCallBack));
    auto previousClick = AceType::MakeRefPtr<NG::ClickEvent>(std::move(previousCallBack));

    for (size_t i = 0; i < contentRow->GetChildren().size(); i++) {
        auto child = contentRow->GetChildAtIndex(i);
        auto childNode = AceType::DynamicCast<FrameNode>(child);
        CHECK_NULL_RETURN(childNode, nullptr);
        if (i == 0 || i == FORWAED_BUTTON_INDEX) {
            auto gestureHub = childNode->GetOrCreateGestureEventHub();
            CHECK_NULL_RETURN(gestureHub, nullptr);
            gestureHub->AddClickEvent(closeClick);
        } else if (i == BACKWARD_BUTTON_INDEX) {
            auto gestureHub = childNode->GetOrCreateGestureEventHub();
            CHECK_NULL_RETURN(gestureHub, nullptr);
            gestureHub->AddClickEvent(nextClick);
        } else if (i == 1) {
            auto gestureHub = childNode->GetOrCreateGestureEventHub();
            CHECK_NULL_RETURN(gestureHub, nullptr);
            gestureHub->AddClickEvent(previousClick);
        }
    }
    return contentRow;
}

RefPtr<FrameNode> TextPickerDialogView::SeparatedOptionsShow(
    RefPtr<FrameNode>& contentColumn, RefPtr<FrameNode>& textPickerNode,
    const std::vector<ButtonInfo>& buttonInfos,
    const TextPickerSettingData& settingData,
    std::map<std::string, NG::DialogTextEvent>& dialogEvent,
    std::map<std::string, NG::DialogGestureEvent>& dialogCancelEvent,
    const float& scale, GestureEventFunc closeCallBack, RefPtr<FrameNode>& dialogNode)
{
    dialogNodePage = 0;
    auto moveForwardFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogMoveForwardEvent;
    dialogMoveForwardEvent["moveForwardId"] = moveForwardFunc;
    auto moveBackwardFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogMoveBackwardFunc;
    dialogMoveBackwardFunc["moveBackwardId"] = moveBackwardFunc;

    uint32_t columnCount = totalPageNum_;
    auto nextCallBack = [weak = WeakPtr<FrameNode>(dialogNode),
        weakText = WeakPtr<FrameNode>(textPickerNode),
        columnCount, weakColumn = WeakPtr<FrameNode>(contentColumn)](const GestureEvent& /* info */) {
    auto dialogNode = weak.Upgrade();
    auto textPickerNode = weakText.Upgrade();
    auto contentColumn = weakColumn.Upgrade();
    CHECK_NULL_VOID(dialogNode);
    if (dialogNodePage < (columnCount - 1)) {
        dialogNodePage++;
    }
    SetDialogNodePageActive(contentColumn, textPickerNode, dialogNodePage, columnCount);
    };
    auto previousCallBack = [weak = WeakPtr<FrameNode>(dialogNode),
        weakText = WeakPtr<FrameNode>(textPickerNode),
        columnCount, weakColumn = WeakPtr<FrameNode>(contentColumn)](const GestureEvent& /* info */) {
        auto dialogNode = weak.Upgrade();
        auto textPickerNode = weakText.Upgrade();
        auto contentColumn = weakColumn.Upgrade();
        CHECK_NULL_VOID(dialogNode);
        if (dialogNodePage > 0) {
            dialogNodePage--;
        }
        SetDialogNodePageActive(contentColumn, textPickerNode, dialogNodePage, columnCount);
    };
    auto contentRow =
        CreateAgingButtonNode(textPickerNode, buttonInfos, dialogEvent, std::move(dialogCancelEvent),
            std::move(dialogMoveForwardEvent), std::move(dialogMoveBackwardFunc),
            closeCallBack, nextCallBack, previousCallBack);
    CHECK_NULL_RETURN(contentRow, nullptr);
    contentRow->AddChild(CreateDividerNode(textPickerNode), 1);
    contentRow->AddChild(CreateDividerNode(textPickerNode), SECOND_DIVEDER_NODE_INDEX);
    contentRow->AddChild(CreateDividerNode(textPickerNode), THIRD_DIVEDER_NODE_INDEX);
    contentRow->MountToParent(contentColumn);
    SetDialogNodePageActive(contentColumn, textPickerNode, dialogNodePage, columnCount);
    dialogNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    return dialogNode;
}

bool TextPickerDialogView::NeedAdaptForAging()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, false);
    if (GreatOrEqual(pipeline->GetFontScale(), pickerTheme->GetMaxOneFontScale()) &&
        Dimension(pipeline->GetRootHeight()).ConvertToVp() > pickerTheme->GetDeviceHeightLimit()) {
        return true;
    }
    return false;
}

const Dimension TextPickerDialogView::AdjustFontSizeScale(const Dimension& fontSizeValue, double fontScale)
{
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipeline, fontSizeValue);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, fontSizeValue);

    auto adjustedScale = std::clamp(fontScale, pickerTheme->GetNormalFontScale(),
        pickerTheme->GetMaxTwoFontScale());
    return fontSizeValue * adjustedScale;
}

const Dimension TextPickerDialogView::ConvertFontScaleValue(
    const Dimension& fontSizeValue, const Dimension& fontSizeLimit, bool isUserSetFont)
{
    auto pipeline = PipelineContext::GetCurrentContextPtrSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, fontSizeValue);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, fontSizeValue);
    float fontSizeScale = pipeline->GetFontScale();
    Dimension fontSizeValueResult = fontSizeValue;
    Dimension fontSizeValueResultVp(fontSizeLimit.Value(), DimensionUnit::VP);

    if (fontSizeValue.Unit() == DimensionUnit::VP) {
        return isUserSetFont ? std::min(fontSizeValueResultVp, fontSizeValue) : fontSizeValue;
    }

    if (NeedAdaptForAging()) {
        if (isUserSetFont) {
            if (GreatOrEqualCustomPrecision(fontSizeValue.ConvertToPx() * fontSizeScale,
                fontSizeLimit.ConvertToPx()) && (!NearZero(fontSizeScale))) {
                fontSizeValueResult = fontSizeLimit / fontSizeScale;
            } else {
                fontSizeValueResult = fontSizeValue;
            }
        } else {
            if (GreatOrEqualCustomPrecision(fontSizeScale, pickerTheme->GetMaxThirdFontScale())) {
                fontSizeScale = pickerTheme->GetMaxTwoFontScale() / pickerTheme->GetMaxThirdFontScale();
                fontSizeValueResult = fontSizeValue * fontSizeScale;
            }
        }
    } else {
        if (isUserSetFont) {
            fontSizeValueResult = ConvertFontSizeLimit(fontSizeValueResult, fontSizeLimit, isUserSetFont);
        } else {
            if (GreatOrEqualCustomPrecision(fontSizeScale, pickerTheme->GetMaxOneFontScale()) &&
                 (!NearZero(fontSizeScale))) {
                fontSizeValueResult = fontSizeValueResult / fontSizeScale;
            }
        }
    }
    return fontSizeValueResult;
}

const Dimension TextPickerDialogView::ConvertFontSizeLimit(
    const Dimension& fontSizeValue, const Dimension& fontSizeLimit, bool isUserSetFont)
{
    if (isUserSetFont == false) {
        return fontSizeValue;
    }
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, fontSizeValue);
    auto fontScale = pipeline->GetFontScale();

    Dimension fontSizeValueResult = fontSizeValue;
    if (GreatOrEqualCustomPrecision(fontSizeValue.ConvertToPx() * fontScale, fontSizeLimit.ConvertToPx())) {
        if (!NearZero(fontScale)) {
            fontSizeValueResult = fontSizeLimit / fontScale;
        }
    }
    return fontSizeValueResult;
}

void TextPickerDialogView::GetUserSettingLimit()
{
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    selectedTextStyleFont_ = pickerTheme->GetUseSetSelectedTextStyle();
    normalTextStyleFont_ = pickerTheme->GetUserSetNormalTextStyle();
    disappearTextStyleFont_ = pickerTheme->GetUserSetDisappearTextStyle();
}

} // namespace OHOS::Ace::NG
