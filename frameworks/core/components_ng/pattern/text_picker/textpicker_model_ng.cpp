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

#include "core/components_ng/pattern/text_picker/textpicker_model_ng.h"

#include <securec.h>

#include "base/geometry/ng/size_t.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_column_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_event_hub.h"
#include "core/components_ng/pattern/text_picker/textpicker_layout_property.h"
#include "core/components_ng/pattern/text_picker/textpicker_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
void SetDialogProperties(DialogProperties& properties, TextPickerDialog& textPickerDialog,
                         const RefPtr<DialogTheme>& theme)
{
    if (SystemProperties::GetDeviceType() == DeviceType::PHONE) {
        properties.alignment = DialogAlignment::BOTTOM;
    } else {
        properties.alignment = DialogAlignment::CENTER;
    }
    if (textPickerDialog.alignment.has_value()) {
        properties.alignment = textPickerDialog.alignment.value();
    }
    properties.customStyle = false;
    properties.offset = DimensionOffset(Offset(0, -theme->GetMarginBottom().ConvertToPx()));
    if (textPickerDialog.offset.has_value()) {
        properties.offset = textPickerDialog.offset.value();
    }

    properties.maskRect = textPickerDialog.maskRect;
}
}

void TextPickerModelNG::Create(RefPtr<PickerTheme> pickerTheme, uint32_t columnKind)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto textPickerNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_PICKER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TextPickerPattern>(); });
    auto textPickerPattern = textPickerNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->SetColumnsKind(columnKind);
    textPickerPattern->SetPickerTag(true);
    CHECK_NULL_VOID(pickerTheme);
    uint32_t showCount = pickerTheme->GetShowOptionCount();

    if (textPickerNode->GetChildren().empty()) {
        auto columnNode = CreateColumnNode(columnKind, showCount);
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
    stack->Push(textPickerNode);
    options_.clear();
}

void TextPickerModelNG::SetDefaultAttributes(const RefPtr<PickerTheme>& pickerTheme)
{
    CHECK_NULL_VOID(pickerTheme);
    auto selectedStyle = pickerTheme->GetOptionStyle(true, false);
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedFontSize, selectedStyle.GetFontSize());
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedColor, selectedStyle.GetTextColor());
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedWeight, selectedStyle.GetFontWeight());
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedFontFamily, selectedStyle.GetFontFamilies());
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedFontStyle, selectedStyle.GetFontStyle());

    auto disappearStyle = pickerTheme->GetDisappearOptionStyle();
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DisappearFontSize, disappearStyle.GetFontSize());
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DisappearColor, disappearStyle.GetTextColor());
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DisappearWeight, disappearStyle.GetFontWeight());
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DisappearFontFamily, disappearStyle.GetFontFamilies());
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DisappearFontStyle, disappearStyle.GetFontStyle());

    auto normalStyle = pickerTheme->GetOptionStyle(false, false);
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, FontSize, normalStyle.GetFontSize());
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, Color, normalStyle.GetTextColor());
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, Weight, normalStyle.GetFontWeight());
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, FontFamily, normalStyle.GetFontFamilies());
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, FontStyle, normalStyle.GetFontStyle());

    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, CanLoop, true);
}

RefPtr<FrameNode> TextPickerModelNG::CreateColumnNode(uint32_t columnKind, uint32_t showCount)
{
    auto columnNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPickerColumnPattern>(); });
    if (columnKind == ICON) {
        for (uint32_t index = 0; index < showCount; index++) {
            auto row = FrameNode::CreateFrameNode(
                V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                AceType::MakeRefPtr<LinearLayoutPattern>(false));
            CHECK_NULL_RETURN(row, nullptr);
            auto layoutProps = row->GetLayoutProperty<LinearLayoutProperty>();
            CHECK_NULL_RETURN(layoutProps, nullptr);
            layoutProps->UpdateMainAxisAlign(FlexAlign::CENTER);
            layoutProps->UpdateCrossAxisAlign(FlexAlign::CENTER);

            auto imageNode = FrameNode::CreateFrameNode(
                V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                AceType::MakeRefPtr<ImagePattern>());
            CHECK_NULL_RETURN(imageNode, nullptr);
            imageNode->MountToParent(row);
            row->MountToParent(columnNode);
        }
    } else if (columnKind == TEXT) {
        for (uint32_t index = 0; index < showCount; index++) {
            auto textNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                AceType::MakeRefPtr<TextPattern>());
            CHECK_NULL_RETURN(textNode, nullptr);
            textNode->MountToParent(columnNode);
        }
    } else if (columnKind == MIXTURE) {
        for (uint32_t index = 0; index < showCount; index++) {
            auto row = FrameNode::CreateFrameNode(
                V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                AceType::MakeRefPtr<LinearLayoutPattern>(false));
            CHECK_NULL_RETURN(row, nullptr);

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
            row->MountToParent(columnNode);
        }
    }
    return columnNode;
}

RefPtr<FrameNode> TextPickerModelNG::CreateStackNode()
{
    auto stackId = ElementRegister::GetInstance()->MakeUniqueId();
    return FrameNode::GetOrCreateFrameNode(
        V2::STACK_ETS_TAG, stackId, []() { return AceType::MakeRefPtr<StackPattern>(); });
}

RefPtr<FrameNode> TextPickerModelNG::CreateButtonNode()
{
    auto buttonId = ElementRegister::GetInstance()->MakeUniqueId();
    return FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, buttonId, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
}

void TextPickerModelNG::SetSelected(uint32_t value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->SetSelected(value);
    std::vector<uint32_t> values;
    values.emplace_back(value);
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, Selected, value);
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedIndex, values);
}

void TextPickerModelNG::SetRange(const std::vector<NG::RangeContent>& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->SetRange(value);
    for (auto& range : value) {
        rangeValue_.emplace_back(std::move(range));
    }
}

void TextPickerModelNG::SetDefaultPickerItemHeight(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DefaultPickerItemHeight, value);
}

void TextPickerModelNG::SetCanLoop(const bool value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, CanLoop, value);
}

void TextPickerModelNG::SetBackgroundColor(const Color& color)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->SetBackgroundColor(color);
}

void TextPickerModelNG::SetDisappearTextStyle(const RefPtr<PickerTheme>& pickerTheme, const NG::PickerTextStyle& value)
{
    CHECK_NULL_VOID(pickerTheme);
    auto disappearStyle = pickerTheme->GetDisappearOptionStyle();
    if (value.fontSize.has_value() && value.fontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DisappearFontSize, value.fontSize.value());
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DisappearFontSize, disappearStyle.GetFontSize());
    }
    ACE_UPDATE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, DisappearColor, value.textColor.value_or(disappearStyle.GetTextColor()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, DisappearWeight, value.fontWeight.value_or(disappearStyle.GetFontWeight()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, DisappearFontFamily, value.fontFamily.value_or(disappearStyle.GetFontFamilies()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, DisappearFontStyle, value.fontStyle.value_or(disappearStyle.GetFontStyle()));
}

void TextPickerModelNG::SetNormalTextStyle(const RefPtr<PickerTheme>& pickerTheme, const NG::PickerTextStyle& value)
{
    CHECK_NULL_VOID(pickerTheme);
    auto normalStyle = pickerTheme->GetOptionStyle(false, false);
    if (value.fontSize.has_value() && value.fontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, FontSize, value.fontSize.value());
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, FontSize, normalStyle.GetFontSize());
    }
    ACE_UPDATE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, Color, value.textColor.value_or(normalStyle.GetTextColor()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, Weight, value.fontWeight.value_or(normalStyle.GetFontWeight()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, FontFamily, value.fontFamily.value_or(normalStyle.GetFontFamilies()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, FontStyle, value.fontStyle.value_or(normalStyle.GetFontStyle()));
}

void TextPickerModelNG::SetSelectedTextStyle(const RefPtr<PickerTheme>& pickerTheme, const NG::PickerTextStyle& value)
{
    CHECK_NULL_VOID(pickerTheme);
    auto selectedStyle = pickerTheme->GetOptionStyle(true, false);
    if (value.fontSize.has_value() && value.fontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedFontSize, value.fontSize.value());
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedFontSize, selectedStyle.GetFontSize());
    }
    ACE_UPDATE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, SelectedColor, value.textColor.value_or(selectedStyle.GetTextColor()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, SelectedWeight, value.fontWeight.value_or(selectedStyle.GetFontWeight()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, SelectedFontFamily, value.fontFamily.value_or(selectedStyle.GetFontFamilies()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, SelectedFontStyle, value.fontStyle.value_or(selectedStyle.GetFontStyle()));
}

void TextPickerModelNG::SetOnCascadeChange(TextCascadeChangeEvent&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<TextPickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

void TextPickerModelNG::SetValue(const std::string& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, Value, value);
}

void TextPickerModelNG::MultiInit(const RefPtr<PickerTheme> pickerTheme)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto textPickerNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_PICKER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TextPickerPattern>(); });
    auto textPickerPattern = textPickerNode->GetPattern<TextPickerPattern>();

    CHECK_NULL_VOID(pickerTheme);
    showCount_ = pickerTheme->GetShowOptionCount();
    stack->Push(textPickerNode);
    rangeValue_.clear();
}

void TextPickerModelNG::SetIsCascade(bool isCascade)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    isCascade_ = isCascade;
    textPickerPattern->SetIsCascade(isCascade_);
}

void TextPickerModelNG::SetHasSelectAttr(bool value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->SetHasSelectAttr(value);
}

void TextPickerModelNG::SetUnCascadeColumns(const std::vector<NG::TextCascadePickerOptions>& options)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GetChildren().empty()) {
        for (uint32_t i = 0; i < options.size(); i++) {
            auto columnNode = CreateColumnNode(NG::TEXT, showCount_);
            auto stackNode = CreateStackNode();
            auto buttonNode = CreateButtonNode();
            buttonNode->MountToParent(stackNode);
            columnNode->MountToParent(stackNode);
            columnNode->MarkModifyDone();
            columnNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            auto layoutProperty = stackNode->GetLayoutProperty<LayoutProperty>();
            layoutProperty->UpdateAlignment(Alignment::CENTER);
            stackNode->MountToParent(frameNode);
        }
    }

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->SetCascadeOptions(options, options);
}

void TextPickerModelNG::SetCascadeColumns(const std::vector<NG::TextCascadePickerOptions>& options)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    std::vector<NG::TextCascadePickerOptions> reOptions;
    // Caculate max depth
    size_t columnCount = options.empty()? 0 : 1;
    for (size_t i = 0; i < options.size(); i++) {
        size_t tmp  = textPickerPattern->ProcessCascadeOptionDepth(options[i]);
        if (tmp > columnCount) {
            columnCount = tmp;
        }
    }

    // Create Node
    if (frameNode->GetChildren().empty()) {
        for (size_t i = 0; i < columnCount; i++) {
            auto columnNode = CreateColumnNode(NG::TEXT, showCount_);
            auto stackNode = CreateStackNode();
            auto buttonNode = CreateButtonNode();
            buttonNode->MountToParent(stackNode);
            columnNode->MountToParent(stackNode);
            columnNode->MarkModifyDone();
            columnNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            auto layoutProperty = stackNode->GetLayoutProperty<LayoutProperty>();
            layoutProperty->UpdateAlignment(Alignment::CENTER);
            stackNode->MountToParent(frameNode);
        }
    }

    textPickerPattern->ProcessCascadeOptions(options, reOptions, 0);
    if (reOptions.size() < columnCount) {
        auto differ = columnCount - reOptions.size();
        for (uint32_t i = 0; i < differ; i++) {
            NG::TextCascadePickerOptions differOption;
            memset_s(&differOption, sizeof(differOption), 0, sizeof(differOption));
            reOptions.emplace_back(differOption);
        }
    }
    textPickerPattern->SetCascadeOptions(options, reOptions);
}

void TextPickerModelNG::SetColumns(const std::vector<NG::TextCascadePickerOptions>& options)
{
    options_.clear();
    for (auto& option : options) {
        options_.emplace_back(std::move(option));
    }
    if (!isCascade_) {
        SetUnCascadeColumns(options);
    } else {
        SetCascadeColumns(options);
    }
}

bool TextPickerModelNG::IsSingle()
{
    return rangeValue_.size() > 0;
}

bool TextPickerModelNG::GetSingleRange(std::vector<NG::RangeContent>& rangeValue)
{
    rangeValue.clear();
    for (auto& item : rangeValue_) {
        rangeValue.emplace_back(std::move(item));
    }
    return true;
}

bool TextPickerModelNG::GetMultiOptions(std::vector<NG::TextCascadePickerOptions>& options)
{
    options.clear();
    for (auto& item : options_) {
        options.emplace_back(std::move(item));
    }
    return true;
}

void TextPickerModelNG::SetValues(const std::vector<std::string>& values)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->SetValues(values);
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, Values, values);
}

void TextPickerModelNG::SetSelecteds(const std::vector<uint32_t>& values)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->SetSelecteds(values);
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, Selecteds, values);
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedIndex, values);
}

void TextPickerModelNG::SetOnValueChangeEvent(TextCascadeValueChangeEvent&& onValueChangeEvent)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<TextPickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnValueChangeEvent(std::move(onValueChangeEvent));
}

void TextPickerModelNG::SetOnSelectedChangeEvent(TextCascadeSelectedChangeEvent&& onSelectedChangeEvent)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<TextPickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSelectedChangeEvent(std::move(onSelectedChangeEvent));
}

RefPtr<AceType> TextPickerDialogModelNG::CreateObject()
{
    return nullptr;
}

void TextPickerDialogModelNG::SetTextPickerDialogShow(RefPtr<AceType>& PickerText,
    NG::TextPickerSettingData& settingData, std::function<void()>&& onCancel,
    std::function<void(const std::string&)>&& onAccept, std::function<void(const std::string&)>&& onChange,
    TextPickerDialog& textPickerDialog)
{
    auto container = Container::Current();
    if (!container) {
        return;
    }
    auto pipelineContext = AccessibilityManager::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    if (!pipelineContext) {
        return;
    }
    auto executor = pipelineContext->GetTaskExecutor();
    if (!executor) {
        return;
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<DialogTheme>();
    if (!theme) {
        LOGE("DialogTheme is null");
        return;
    }

    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogEvent["acceptId"] = onAccept;
    dialogEvent["changeId"] = onChange;
    auto func = [onCancel](const GestureEvent& /* info */) {
        if (onCancel) {
            onCancel();
        }
    };
    dialogCancelEvent["cancelId"] = func;
    DialogProperties properties;
    ButtonInfo buttonInfo;
    SetDialogProperties(properties, textPickerDialog, theme);

    auto context = AccessibilityManager::DynamicCast<NG::PipelineContext>(pipelineContext);
    auto overlayManager = context ? context->GetOverlayManager() : nullptr;
    executor->PostTask(
        [properties, settingData, dialogEvent, dialogCancelEvent, weak = WeakPtr<NG::OverlayManager>(overlayManager)] {
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->ShowTextDialog(properties, settingData, dialogEvent, dialogCancelEvent);
        },
        TaskExecutor::TaskType::UI);
}
} // namespace OHOS::Ace::NG
