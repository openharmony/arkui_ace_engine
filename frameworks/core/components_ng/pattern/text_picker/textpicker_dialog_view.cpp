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
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_column_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_event_hub.h"
#include "core/components_ng/pattern/text_picker/textpicker_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/base/view_abstract_model.h"

namespace OHOS::Ace::NG {
    
RefPtr<FrameNode> TextPickerDialogView::dialogNode_ = nullptr;

RefPtr<FrameNode> TextPickerDialogView::Show(const DialogProperties& dialogProperties,
    const TextPickerSettingData& settingData,
    std::map<std::string, NG::DialogTextEvent> dialogEvent,
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent)
{
    if (settingData.rangeVector.empty() && settingData.options.empty()) {
        LOGI("Dialog input parameter range vector is empty, not display dialog.");
        return dialogNode_;
    }
    if (settingData.options.empty()) {
        return RangeShow(dialogProperties, settingData, dialogEvent, dialogCancelEvent);
    } else {
        return OptionsShow(dialogProperties, settingData, dialogEvent, dialogCancelEvent);
    }
}

RefPtr<FrameNode> TextPickerDialogView::RangeShow(const DialogProperties& dialogProperties,
    const TextPickerSettingData& settingData, std::map<std::string, NG::DialogTextEvent>& dialogEvent,
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
    uint32_t showCount = pickerTheme->GetShowOptionCount();
    OptionsCreateNode(textPickerPattern, settingData, textPickerNode, showCount, 1, pickerTheme);
    SetDefaultPickerItemHeight(settingData.height);
    SetTextProperties(pickerTheme, settingData.properties);
    auto changeEvent = dialogEvent["changeId"];
    SetDialogChange(textPickerNode, std::move(changeEvent));
    ViewStackProcessor::GetInstance()->Finish();
    textPickerNode->MountToParent(contentColumn);
    auto dialogNode = DialogView::CreateDialogNode(dialogProperties, contentColumn);
    CHECK_NULL_RETURN(dialogNode, nullptr);
    auto closeCallback = [dialogNode](const GestureEvent& /* info */) {
        auto pipeline = PipelineContext::GetCurrentContext();
        auto overlayManager = pipeline->GetOverlayManager();
        overlayManager->CloseDialog(dialogNode);
    };
    auto contentRow = CreateButtonNode(textPickerNode, dialogEvent, std::move(dialogCancelEvent), closeCallback);
    contentRow->AddChild(CreateDividerNode(textPickerNode), 1);
    contentRow->MountToParent(contentColumn);
    auto focusHub = contentColumn->GetFocusHub();
    CHECK_NULL_RETURN(focusHub, nullptr);
    InitOnKeyEvent(focusHub);
    dialogNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    dialogNode_ = dialogNode;
    return dialogNode;
}

void TextPickerDialogView::OptionsCreateNode(
    const RefPtr<TextPickerPattern>& textPickerPattern, const TextPickerSettingData& settingData,
    const RefPtr<FrameNode>& textPickerNode, uint32_t showCount, uint32_t columnCount, RefPtr<PickerTheme> pickerTheme)
{
    if (textPickerNode->GetChildren().empty()) {
        for (size_t i = 0; i < columnCount; i++) {
            auto columnNode = CreateColumnNode(settingData.columnKind, showCount, pickerTheme);
            auto stackNode = CreateStackNode();
            auto buttonNode = CreateButtonNode();
            buttonNode->MountToParent(stackNode);
            columnNode->MountToParent(stackNode);
            columnNode->MarkModifyDone();
            columnNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            auto layoutProperty = stackNode->GetLayoutProperty<LayoutProperty>();
            layoutProperty->UpdateAlignment(Alignment::CENTER);
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

void TextPickerDialogView::OptionsShowInternal(
    const RefPtr<TextPickerPattern>& textPickerPattern, const TextPickerSettingData& settingData,
    const RefPtr<FrameNode>& textPickerNode, uint32_t showCount, RefPtr<PickerTheme> pickerTheme)
{
    textPickerPattern->SetIsCascade(settingData.attr.isCascade);
    textPickerPattern->SetHasSelectAttr(settingData.attr.isHasSelectAttr);
    textPickerPattern->SetColumnsKind(settingData.columnKind);
    if (settingData.attr.isCascade) {
        std::vector<NG::TextCascadePickerOptions> reOptions;
        uint32_t columnCount = settingData.options.empty()? 0 : 1;
        // Caculate max depth
        for (size_t i = 0; i < settingData.options.size(); i++) {
            size_t tmp  = textPickerPattern->ProcessCascadeOptionDepth(settingData.options[i]);
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
        OptionsCreateNode(textPickerPattern, settingData, textPickerNode,
            showCount, settingData.options.size(), pickerTheme);
        textPickerPattern->SetCascadeOptions(settingData.options, settingData.options);
    }
}

RefPtr<FrameNode> TextPickerDialogView::OptionsShow(const DialogProperties& dialogProperties,
    const TextPickerSettingData& settingData,
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
    uint32_t showCount = pickerTheme->GetShowOptionCount();
    OptionsShowInternal(textPickerPattern, settingData, textPickerNode, showCount, pickerTheme);
    SetDefaultPickerItemHeight(settingData.height);
    SetTextProperties(pickerTheme, settingData.properties);
    auto changeEvent = dialogEvent["changeId"];
    SetDialogChange(textPickerNode, std::move(changeEvent));

    ViewStackProcessor::GetInstance()->Finish();
    textPickerNode->MountToParent(contentColumn);
    auto dialogNode = DialogView::CreateDialogNode(dialogProperties, contentColumn);
    CHECK_NULL_RETURN(dialogNode, nullptr);
    
    auto closeCallBack = [dialogNode](const GestureEvent& /* info */) {
        auto pipeline = PipelineContext::GetCurrentContext();
        auto overlayManager = pipeline->GetOverlayManager();
        overlayManager->CloseDialog(dialogNode);
    };
    auto contentRow = CreateButtonNode(textPickerNode, dialogEvent, std::move(dialogCancelEvent), closeCallBack);
    contentRow->AddChild(CreateDividerNode(textPickerNode), 1);
    contentRow->MountToParent(contentColumn);
    dialogNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    return dialogNode;
}

RefPtr<FrameNode> TextPickerDialogView::CreateIconItemNode(RefPtr<PickerTheme> pickerTheme)
{
    auto row = FrameNode::CreateFrameNode(
        V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
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
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<ImagePattern>());
    CHECK_NULL_RETURN(imageNode, nullptr);
    imageNode->MountToParent(row);

    return row;
}
RefPtr<FrameNode> TextPickerDialogView::CreateTextItemNode(RefPtr<PickerTheme> pickerTheme)
{
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<TextPattern>());
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
    auto row = FrameNode::CreateFrameNode(
        V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    CHECK_NULL_RETURN(row, nullptr);

    auto rowProperty = row->GetLayoutProperty<LinearLayoutProperty>();
    MarginProperty marginProperty;
    marginProperty.left = CalcLength(pickerTheme->GetPaddingHorizontal());
    marginProperty.right = CalcLength(pickerTheme->GetPaddingHorizontal());
    rowProperty->UpdateMargin(marginProperty);

    auto imageNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<ImagePattern>());
    CHECK_NULL_RETURN(imageNode, nullptr);
    imageNode->MountToParent(row);

    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textNode, nullptr);
    textNode->MountToParent(row);

    return row;
}

RefPtr<FrameNode> TextPickerDialogView::CreateColumnNode(uint32_t columnKind, uint32_t showCount,
    RefPtr<PickerTheme> pickerTheme)
{
    auto columnNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPickerColumnPattern>(); });

        auto columnLayout = columnNode->GetLayoutProperty<LayoutProperty>();
        MarginProperty marginProperty;
        marginProperty.top = CalcLength(pickerTheme->GetContentMarginVertical());
        marginProperty.bottom = CalcLength(pickerTheme->GetContentMarginVertical());
        columnLayout->UpdateMargin(marginProperty);

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

RefPtr<FrameNode> TextPickerDialogView::CreateStackNode()
{
    auto stackId = ElementRegister::GetInstance()->MakeUniqueId();
    return FrameNode::GetOrCreateFrameNode(
        V2::STACK_ETS_TAG, stackId, []() { return AceType::MakeRefPtr<StackPattern>(); });
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
    auto dividerRenderContext = dividerNode->GetRenderContext();
    CHECK_NULL_RETURN(dividerRenderContext, nullptr);
    dividerRenderContext->UpdateBackgroundColor(dialogTheme->GetDividerColor());

    MarginProperty margin;
    margin.top = CalcLength(dialogTheme->GetDividerHeight());
    margin.bottom = CalcLength(dialogTheme->GetDividerPadding().Bottom());
    dividerNode->GetLayoutProperty()->UpdateMargin(margin);
    dividerNode->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(dialogTheme->GetDividerWidth()), CalcLength(dialogTheme->GetDividerHeight())));

    return dividerNode;
}

RefPtr<FrameNode> TextPickerDialogView::CreateButtonNode(const RefPtr<FrameNode>& frameNode,
    std::map<std::string, NG::DialogTextEvent> dialogEvent,
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent,
    GestureEventFunc callback)
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

    auto buttonCancelNode = CreateCancelNode(cancelEvent, frameNode);
    auto buttonConfirmNode = CreateConfirmNode(frameNode, frameNode, acceptEvent);

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

RefPtr<FrameNode> TextPickerDialogView::CreateConfirmNode(const RefPtr<FrameNode>& dateNode,
    const RefPtr<FrameNode>& textPickerNode,
    DialogEvent& acceptEvent)
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
    auto textLayoutProperty = textConfirmNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateContent(Localization::GetInstance()->GetEntryLetters("common.ok"));
    textLayoutProperty->UpdateTextColor(pickerTheme->GetOptionStyle(true, false).GetTextColor());
    textLayoutProperty->UpdateFontSize(pickerTheme->GetOptionStyle(false, false).GetFontSize());
    textLayoutProperty->UpdateFontWeight(pickerTheme->GetOptionStyle(true, false).GetFontWeight());
    auto textPattern = textPickerNode->GetPattern<TextPickerPattern>();
    textPattern->SetConfirmNode(buttonConfirmNode);
    auto buttonConfirmEventHub = buttonConfirmNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_RETURN(buttonConfirmEventHub, nullptr);
    buttonConfirmEventHub->SetStateEffect(true);

    auto buttonConfirmLayoutProperty = buttonConfirmNode->GetLayoutProperty<ButtonLayoutProperty>();
    buttonConfirmLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
    buttonConfirmLayoutProperty->UpdateType(ButtonType::CAPSULE);
    buttonConfirmLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(pickerTheme->GetButtonWidth()), CalcLength(pickerTheme->GetButtonHeight())));
    auto buttonConfirmRenderContext = buttonConfirmNode->GetRenderContext();
    buttonConfirmRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);

    MarginProperty margin;
    margin.right = CalcLength(dialogTheme->GetDividerPadding().Right());
    margin.top = CalcLength(dialogTheme->GetDividerHeight());
    margin.bottom = CalcLength(dialogTheme->GetDividerPadding().Bottom());
    buttonConfirmNode->GetLayoutProperty()->UpdateMargin(margin);

    textConfirmNode->MountToParent(buttonConfirmNode);
    auto eventConfirmHub = buttonConfirmNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(eventConfirmHub, nullptr);
    CHECK_NULL_RETURN(dateNode, nullptr);
    SetDialogAcceptEvent(dateNode, std::move(acceptEvent));
    auto clickCallback = [dateNode](const GestureEvent& /* info */) {
        auto pickerPattern = dateNode->GetPattern<TextPickerPattern>();
        CHECK_NULL_VOID(pickerPattern);
        auto str = pickerPattern->GetSelectedObject(false);
        auto textPickerEventHub = pickerPattern->GetEventHub<TextPickerEventHub>();
        CHECK_NULL_VOID(textPickerEventHub);
        textPickerEventHub->FireDialogAcceptEvent(str);
    };
    eventConfirmHub->AddClickEvent(AceType::MakeRefPtr<NG::ClickEvent>(clickCallback));
    buttonConfirmNode->MarkModifyDone();
    return buttonConfirmNode;
}

RefPtr<FrameNode> TextPickerDialogView::CreateCancelNode(NG::DialogGestureEvent& cancelEvent,
    const RefPtr<FrameNode>& textPickerNode)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_RETURN(buttonCancelNode, nullptr);
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textCancelNode, nullptr);
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textCancelLayoutProperty, nullptr);
    textCancelLayoutProperty->UpdateContent(Localization::GetInstance()->GetEntryLetters("common.cancel"));
    textCancelLayoutProperty->UpdateTextColor(pickerTheme->GetOptionStyle(true, false).GetTextColor());
    textCancelLayoutProperty->UpdateFontSize(pickerTheme->GetOptionStyle(false, false).GetFontSize());
    textCancelLayoutProperty->UpdateFontWeight(pickerTheme->GetOptionStyle(true, false).GetFontWeight());
    auto textPattern = textPickerNode->GetPattern<TextPickerPattern>();
    textPattern->SetCancelNode(buttonCancelNode);
    textCancelNode->MountToParent(buttonCancelNode);
    auto eventCancelHub = buttonCancelNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(eventCancelHub, nullptr);
    eventCancelHub->AddClickEvent(AceType::MakeRefPtr<NG::ClickEvent>(std::move(cancelEvent)));

    auto buttonCancelEventHub = buttonCancelNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_RETURN(buttonCancelEventHub, nullptr);
    buttonCancelEventHub->SetStateEffect(true);

    MarginProperty margin;
    margin.left = CalcLength(dialogTheme->GetDividerPadding().Left());
    margin.top = CalcLength(dialogTheme->GetDividerHeight());
    margin.bottom = CalcLength(dialogTheme->GetDividerPadding().Bottom());
    buttonCancelNode->GetLayoutProperty()->UpdateMargin(margin);

    auto buttonCancelLayoutProperty = buttonCancelNode->GetLayoutProperty<ButtonLayoutProperty>();
    buttonCancelLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
    buttonCancelLayoutProperty->UpdateType(ButtonType::CAPSULE);
    buttonCancelLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(pickerTheme->GetButtonWidth()), CalcLength(pickerTheme->GetButtonHeight())));

    auto buttonCancelRenderContext = buttonCancelNode->GetRenderContext();
    buttonCancelRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    buttonCancelNode->MarkModifyDone();
    return buttonCancelNode;
}

void TextPickerDialogView::SetSelected(const RefPtr<TextPickerPattern>& textPickerPattern, uint32_t value)
{
    textPickerPattern->SetSelected(value);
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, Selected, value);
}

void TextPickerDialogView::SetSelectedValues(const RefPtr<TextPickerPattern>& textPickerPattern,
    const std::vector<uint32_t>& values)
{
    textPickerPattern->SetSelecteds(values);
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, Selecteds, values);
}

void TextPickerDialogView::SetValues(const RefPtr<TextPickerPattern>& textPickerPattern,
    const std::vector<std::string>& values)
{
    textPickerPattern->SetValues(values);
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, Values, values);
}

void TextPickerDialogView::SetRange(
    const RefPtr<TextPickerPattern>& textPickerPattern, const std::vector<NG::RangeContent>& value)
{
    textPickerPattern->SetRange(value);
}

void TextPickerDialogView::SetTextProperties(const RefPtr<PickerTheme>& pickerTheme,
    const PickerTextProperties& properties)
{
    CHECK_NULL_VOID(pickerTheme);
    auto selectedStyle = pickerTheme->GetOptionStyle(true, false);
    auto disappearStyle = pickerTheme->GetDisappearOptionStyle();
    auto normalStyle = pickerTheme->GetOptionStyle(false, false);

    if (properties.disappearTextStyle_.fontSize.has_value() && properties.disappearTextStyle_.fontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(
            TextPickerLayoutProperty, DisappearFontSize, properties.disappearTextStyle_.fontSize.value());
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DisappearFontSize, disappearStyle.GetFontSize());
    }
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DisappearColor,
        properties.disappearTextStyle_.textColor.value_or(disappearStyle.GetTextColor()));
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DisappearWeight,
        properties.disappearTextStyle_.fontWeight.value_or(disappearStyle.GetFontWeight()));

    if (properties.normalTextStyle_.fontSize.has_value() && properties.normalTextStyle_.fontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(
            TextPickerLayoutProperty, FontSize, properties.normalTextStyle_.fontSize.value());
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, FontSize, normalStyle.GetFontSize());
    }
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, Color,
        properties.normalTextStyle_.textColor.value_or(normalStyle.GetTextColor()));
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, Weight,
        properties.normalTextStyle_.fontWeight.value_or(normalStyle.GetFontWeight()));

    if (properties.selectedTextStyle_.fontSize.has_value() && properties.selectedTextStyle_.fontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(
            TextPickerLayoutProperty, SelectedFontSize, properties.selectedTextStyle_.fontSize.value());
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedFontSize, selectedStyle.GetFontSize());
    }
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedColor,
        properties.selectedTextStyle_.textColor.value_or(selectedStyle.GetTextColor()));
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedWeight,
        properties.selectedTextStyle_.fontWeight.value_or(selectedStyle.GetFontWeight()));
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
    auto onKeyEvent = [](const KeyEvent& event) -> bool {
        return TextPickerDialogView::OnKeyEvent(event);
    };
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
        overlayManager->CloseDialog(dialogNode_);
        return true;
    }

    return false;
}
} // namespace OHOS::Ace::NG
