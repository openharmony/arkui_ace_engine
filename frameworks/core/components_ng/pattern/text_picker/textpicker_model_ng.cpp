/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/picker/picker_type_define.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_column_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_event_hub.h"
#include "core/components_ng/pattern/text_picker/textpicker_layout_property.h"
#include "core/components_ng/pattern/text_picker/textpicker_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/common/resource/resource_object.h"
#include "core/common/resource/resource_parse_utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float PICKER_MAXFONTSCALE = 1.0f;
constexpr bool DEFAULT_ENABLE_HAPTIC_FEEDBACK = true;
const int32_t BUFFER_NODE_NUMBER = 2;

void SetDialogProperties(DialogProperties& properties, TextPickerDialog& textPickerDialog,
                         const RefPtr<DialogTheme>& theme)
{
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        properties.alignment = theme->GetAlignment();
    }
    if (textPickerDialog.alignment.has_value()) {
        properties.alignment = textPickerDialog.alignment.value();
    }

    if (textPickerDialog.backgroundColor.has_value()) {
        properties.backgroundColor = textPickerDialog.backgroundColor.value();
    }
    if (textPickerDialog.backgroundBlurStyle.has_value()) {
        properties.backgroundBlurStyle = textPickerDialog.backgroundBlurStyle.value();
    }
    if (textPickerDialog.blurStyleOption.has_value()) {
        properties.blurStyleOption = textPickerDialog.blurStyleOption.value();
    }
    if (textPickerDialog.effectOption.has_value()) {
        properties.effectOption = textPickerDialog.effectOption.value();
    }
    if (textPickerDialog.shadow.has_value()) {
        properties.shadow = textPickerDialog.shadow.value();
    }
    properties.customStyle = false;
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        properties.offset = DimensionOffset(Offset(0, -theme->GetMarginBottom().ConvertToPx()));
    }
    if (textPickerDialog.offset.has_value()) {
        properties.offset = textPickerDialog.offset.value();
    }

    properties.maskRect = textPickerDialog.maskRect;
    properties.enableHoverMode = textPickerDialog.enableHoverMode;
    if (textPickerDialog.hoverModeArea.has_value()) {
        properties.hoverModeArea = textPickerDialog.hoverModeArea.value();
    }
}

using TextPickerGetTextStyleFunc = const std::unique_ptr<FontStyle>& (TextPickerLayoutProperty::*)() const;
void ResetTextPickerTextStyleColor(FrameNode* frameNode, TextPickerGetTextStyleFunc getTextStyleFunc)
{
    CHECK_NULL_VOID(frameNode);
    auto property = frameNode->GetLayoutPropertyPtr<TextPickerLayoutProperty>();
    CHECK_NULL_VOID(property);
    auto& textStyle = (property->*getTextStyleFunc)();
    CHECK_NULL_VOID(textStyle);
    if (textStyle->HasTextColor()) {
        textStyle->ResetTextColor();
        property->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE_SELF);
    }
}
}

void TextPickerModelNG::Create(RefPtr<PickerTheme> pickerTheme, uint32_t columnKind)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::TEXT_PICKER_ETS_TAG, nodeId);
    auto textPickerNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_PICKER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TextPickerPattern>(); });
    auto textPickerPattern = textPickerNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->SetColumnsKind(columnKind);
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(dialogTheme);
    textPickerPattern->SetBackgroundColor(dialogTheme->GetBackgroundColor());
    CHECK_NULL_VOID(pickerTheme);
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;

    if (textPickerNode->GetChildren().empty()) {
        auto columnNode = CreateColumnNode(columnKind, showCount);
        auto stackNode = CreateStackNode();
        auto buttonNode = CreateButtonNode();
        auto columnBlendNode = CreateColumnNode();
        buttonNode->MountToParent(stackNode);
        columnNode->MountToParent(columnBlendNode);
        columnBlendNode->MountToParent(stackNode);
        columnNode->MarkModifyDone();
        columnNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        auto layoutProperty = stackNode->GetLayoutProperty<LayoutProperty>();
        layoutProperty->UpdateAlignment(Alignment::CENTER);
        stackNode->MountToParent(textPickerNode);
    }
    stack->Push(textPickerNode);
    if (pickerTheme->IsCircleDial()) {
        auto renderContext = textPickerNode->GetRenderContext();
        renderContext->UpdateBackgroundColor(pickerTheme->GetBackgroundColor());
    }
}

void TextPickerModelNG::InitialSetupSinglePicker(FrameNode* frameNode, uint32_t columnKind)
{
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->SetColumnsKind(columnKind);

    if (frameNode->GetChildren().empty()) {
        auto columnNode = CreateColumnNode(columnKind, showCount_);
        auto stackNode = CreateStackNode();
        auto buttonNode = CreateButtonNode();
        auto columnBlendNode = CreateColumnNode();
        buttonNode->MountToParent(stackNode);
        columnNode->MountToParent(columnBlendNode);
        columnBlendNode->MountToParent(stackNode);
        columnNode->MarkModifyDone();
        columnNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        auto layoutProperty = stackNode->GetLayoutProperty<LayoutProperty>();
        layoutProperty->UpdateAlignment(Alignment::CENTER);
        stackNode->MountToParent(AceType::Claim(frameNode));
    }
    textPickerPattern->ClearOption();
}

void TextPickerModelNG::SetDefaultAttributes(const RefPtr<PickerTheme>& pickerTheme)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(pickerTheme);
    auto selectedStyle = pickerTheme->GetOptionStyle(true, false);
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedFontSize,
        ConvertFontScaleValue(selectedStyle.GetFontSize()));
    ResetTextPickerTextStyleColor(frameNode, &TextPickerLayoutProperty::GetSelectedTextStyle);
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedWeight, selectedStyle.GetFontWeight());
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedFontFamily, selectedStyle.GetFontFamilies());
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedFontStyle, selectedStyle.GetFontStyle());

    auto disappearStyle = pickerTheme->GetDisappearOptionStyle();
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DisappearFontSize,
        ConvertFontScaleValue(disappearStyle.GetFontSize()));
    ResetTextPickerTextStyleColor(frameNode, &TextPickerLayoutProperty::GetDisappearTextStyle);
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DisappearWeight, disappearStyle.GetFontWeight());
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DisappearFontFamily, disappearStyle.GetFontFamilies());
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DisappearFontStyle, disappearStyle.GetFontStyle());

    auto normalStyle = pickerTheme->GetOptionStyle(false, false);
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, FontSize,
        ConvertFontScaleValue(normalStyle.GetFontSize()));
    ResetTextPickerTextStyleColor(frameNode, &TextPickerLayoutProperty::GetTextStyle);
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, Weight, normalStyle.GetFontWeight());
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, FontFamily, normalStyle.GetFontFamilies());
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, FontStyle, normalStyle.GetFontStyle());
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, CanLoop, true);
    ACE_UPDATE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, DigitalCrownSensitivity, pickerTheme->GetDigitalCrownSensitivity());
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

RefPtr<FrameNode> TextPickerModelNG::CreateColumnNode()
{
    auto columnId = ElementRegister::GetInstance()->MakeUniqueId();
    return FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, columnId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
}

RefPtr<FrameNode> TextPickerModelNG::CreateButtonNode()
{
    auto buttonId = ElementRegister::GetInstance()->MakeUniqueId();
    return FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, buttonId, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
}

RefPtr<FrameNode> TextPickerModelNG::CreateFrameNode(int32_t nodeId)
{
    auto textPickerNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_PICKER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TextPickerPattern>(); });
    auto pipeline = PipelineBase::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipeline, textPickerNode);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>(textPickerNode->GetThemeScopeId());
    CHECK_NULL_RETURN(pickerTheme, textPickerNode);
    std::lock_guard<std::shared_mutex> lock(showCountMutex_);
    showCount_ = BUFFER_NODE_NUMBER + pickerTheme->GetShowOptionCount();
    SetDefaultAttributes(textPickerNode, pickerTheme);
    return textPickerNode;
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

void TextPickerModelNG::SetColumnWidths(const std::vector<Dimension>& widths)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->SetColumnWidths(widths);
}

void TextPickerModelNG::SetColumnWidths(FrameNode* frameNode, const std::vector<Dimension>& widths)
{
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->SetColumnWidths(widths);
}

std::vector<Dimension> TextPickerModelNG::GetColumnWidths(FrameNode* frameNode)
{
    std::vector<Dimension> columnWidths;
    CHECK_NULL_RETURN(frameNode, columnWidths);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    columnWidths = textPickerPattern->GetColumnWidths();
    return columnWidths;
}

void TextPickerModelNG::SetRange(const std::vector<NG::RangeContent>& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->SetRange(value);
}

void TextPickerModelNG::SetDefaultPickerItemHeight(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DefaultPickerItemHeight, value);
}

void TextPickerModelNG::SetGradientHeight(const Dimension& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->SetGradientHeight(value);
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, GradientHeight, value);
}

void TextPickerModelNG::SetCanLoop(const bool value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->SetCanLoop(value);
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

void TextPickerModelNG::SetDisableTextStyleAnimation(const bool value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->SetDisableTextStyleAnimation(value);
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DisableTextStyleAnimation, value);
}

void TextPickerModelNG::SetDisappearTextStyle(const RefPtr<PickerTheme>& pickerTheme, const NG::PickerTextStyle& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(pickerTheme);
    if (SystemProperties::ConfigChangePerform()) {
        ParseDisappearTextStyleResObj(value);
    }

    auto disappearStyle = pickerTheme->GetDisappearOptionStyle();
    if (value.fontSize.has_value() && value.fontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DisappearFontSize,
            ConvertFontScaleValue(value.fontSize.value()));
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DisappearFontSize,
            ConvertFontScaleValue(disappearStyle.GetFontSize()));
    }
    if (value.textColor.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DisappearColor, value.textColor.value());
    } else {
        ResetTextPickerTextStyleColor(frameNode, &TextPickerLayoutProperty::GetDisappearTextStyle);
    }
    ACE_UPDATE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, DisappearWeight, value.fontWeight.value_or(disappearStyle.GetFontWeight()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, DisappearFontFamily, value.fontFamily.value_or(disappearStyle.GetFontFamilies()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, DisappearFontStyle, value.fontStyle.value_or(disappearStyle.GetFontStyle()));

    if (value.minFontSize.has_value() && value.minFontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DisappearMinFontSize,
            ConvertFontScaleValue(value.minFontSize.value()));
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DisappearMinFontSize, Dimension());
    }
    if (value.maxFontSize.has_value() && value.maxFontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DisappearMaxFontSize,
            ConvertFontScaleValue(value.maxFontSize.value()));
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DisappearMaxFontSize, Dimension());
    }
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DisappearTextOverflow,
        value.textOverflow.value_or(TextOverflow::CLIP));
    ACE_UPDATE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, DisappearTextColorSetByUser, value.textColorSetByUser);
}

void TextPickerModelNG::SetNormalTextStyle(const RefPtr<PickerTheme>& pickerTheme, const NG::PickerTextStyle& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(pickerTheme);
    if (SystemProperties::ConfigChangePerform()) {
        ParseNormalTextStyleResObj(value);
    }

    auto normalStyle = pickerTheme->GetOptionStyle(false, false);
    if (value.fontSize.has_value() && value.fontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, FontSize,
            ConvertFontScaleValue(value.fontSize.value()));
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, FontSize,
            ConvertFontScaleValue(normalStyle.GetFontSize()));
    }
    if (value.textColor.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, Color, value.textColor.value());
    } else {
        ResetTextPickerTextStyleColor(frameNode, &TextPickerLayoutProperty::GetTextStyle);
    }
    ACE_UPDATE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, Weight, value.fontWeight.value_or(normalStyle.GetFontWeight()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, FontFamily, value.fontFamily.value_or(normalStyle.GetFontFamilies()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, FontStyle, value.fontStyle.value_or(normalStyle.GetFontStyle()));

    if (value.minFontSize.has_value() && value.minFontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, MinFontSize,
            ConvertFontScaleValue(value.minFontSize.value()));
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, MinFontSize, Dimension());
    }
    if (value.maxFontSize.has_value() && value.maxFontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, MaxFontSize,
            ConvertFontScaleValue(value.maxFontSize.value()));
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, MaxFontSize, Dimension());
    }
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, TextOverflow,
        value.textOverflow.value_or(TextOverflow::CLIP));
    ACE_UPDATE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, NormalTextColorSetByUser, value.textColorSetByUser);
}

void TextPickerModelNG::SetSelectedTextStyle(const RefPtr<PickerTheme>& pickerTheme, const NG::PickerTextStyle& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(pickerTheme);
    if (SystemProperties::ConfigChangePerform()) {
        ParseSelectedTextStyleResObj(value);
    }

    auto selectedStyle = pickerTheme->GetOptionStyle(true, false);
    if (value.fontSize.has_value() && value.fontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedFontSize,
            ConvertFontScaleValue(value.fontSize.value()));
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedFontSize,
            ConvertFontScaleValue(selectedStyle.GetFontSize()));
    }
    if (value.textColor.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedColor, value.textColor.value());
    } else {
        ResetTextPickerTextStyleColor(frameNode, &TextPickerLayoutProperty::GetSelectedTextStyle);
    }
    ACE_UPDATE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, SelectedWeight, value.fontWeight.value_or(selectedStyle.GetFontWeight()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, SelectedFontFamily, value.fontFamily.value_or(selectedStyle.GetFontFamilies()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, SelectedFontStyle, value.fontStyle.value_or(selectedStyle.GetFontStyle()));

    if (value.minFontSize.has_value() && value.minFontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedMinFontSize,
            ConvertFontScaleValue(value.minFontSize.value()));
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedMinFontSize, Dimension());
    }
    if (value.maxFontSize.has_value() && value.maxFontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedMaxFontSize,
            ConvertFontScaleValue(value.maxFontSize.value()));
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedMaxFontSize, Dimension());
    }
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedTextOverflow,
        value.textOverflow.value_or(TextOverflow::CLIP));
    ACE_UPDATE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, SelectedTextColorSetByUser, value.textColorSetByUser);
}

void TextPickerModelNG::SetDefaultTextStyle(const RefPtr<TextTheme>& textTheme, const NG::PickerTextStyle& value)
{
    CHECK_NULL_VOID(textTheme);
    if (SystemProperties::ConfigChangePerform()) {
        ParseDefaultTextStyleResObj(value);
    }
    auto textStyle = textTheme->GetTextStyle();

    if (value.fontSize.has_value() && value.fontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DefaultFontSize,
            ConvertFontScaleValue(value.fontSize.value()));
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DefaultFontSize,
            ConvertFontScaleValue(textStyle.GetFontSize()));
    }
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DefaultColor,
        value.textColor.value_or(textStyle.GetTextColor()));
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DefaultWeight,
        value.fontWeight.value_or(textStyle.GetFontWeight()));
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DefaultFontFamily,
        value.fontFamily.value_or(textStyle.GetFontFamilies()));
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DefaultFontStyle,
        value.fontStyle.value_or(textStyle.GetFontStyle()));
    if (value.minFontSize.has_value() && value.minFontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DefaultMinFontSize,
            ConvertFontScaleValue(value.minFontSize.value()));
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DefaultMinFontSize, Dimension());
    }
    if (value.maxFontSize.has_value() && value.maxFontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DefaultMaxFontSize,
            ConvertFontScaleValue(value.maxFontSize.value()));
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DefaultMaxFontSize, Dimension());
    }
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DefaultTextOverflow,
        value.textOverflow.value_or(textStyle.GetTextOverflow()));
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DefaultTextColorSetByUser, value.textColorSetByUser);
}

void TextPickerModelNG::HasUserDefinedDisappearFontFamily(bool isUserDefined)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->HasUserDefinedDisappearFontFamily(isUserDefined);
}

void TextPickerModelNG::HasUserDefinedNormalFontFamily(bool isUserDefined)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->HasUserDefinedNormalFontFamily(isUserDefined);
}

void TextPickerModelNG::HasUserDefinedSelectedFontFamily(bool isUserDefined)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->HasUserDefinedSelectedFontFamily(isUserDefined);
}

void TextPickerModelNG::SetOnCascadeChange(TextCascadeChangeEvent&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<TextPickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

void TextPickerModelNG::SetOnScrollStop(TextCascadeChangeEvent&& onScrollStop)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<TextPickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollStop(std::move(onScrollStop));
}

void TextPickerModelNG::SetOnEnterSelectedArea(TextCascadeChangeEvent&& onEnterSelectedArea)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<TextPickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnEnterSelectedArea(std::move(onEnterSelectedArea));
}

void TextPickerModelNG::SetOnEnterSelectedArea(FrameNode* frameNode, TextCascadeChangeEvent&& onEnterSelectedArea)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<TextPickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnEnterSelectedArea(std::move(onEnterSelectedArea));
}

void TextPickerModelNG::SetValue(const std::string& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, Value, value);
}

PickerTextStyle TextPickerModelNG::getDisappearTextStyle(FrameNode* frameNode)
{
    PickerTextStyle pickerTextStyle;
    CHECK_NULL_RETURN(frameNode, pickerTextStyle);
    auto context = frameNode->GetContext();
    CHECK_NULL_RETURN(context, pickerTextStyle);
    auto theme = context->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(theme, pickerTextStyle);
    auto style = theme->GetDisappearOptionStyle();
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        TextPickerLayoutProperty, DisappearFontSize, pickerTextStyle.fontSize, frameNode, style.GetFontSize());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        TextPickerLayoutProperty, DisappearColor, pickerTextStyle.textColor, frameNode, style.GetTextColor());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        TextPickerLayoutProperty, DisappearWeight, pickerTextStyle.fontWeight, frameNode, style.GetFontWeight());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextPickerLayoutProperty, DisappearFontFamily,
        pickerTextStyle.fontFamily, frameNode, style.GetFontFamilies());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextPickerLayoutProperty, DisappearFontStyle,
        pickerTextStyle.fontStyle, frameNode, style.GetFontStyle());
    return pickerTextStyle;
}

PickerTextStyle TextPickerModelNG::getNormalTextStyle(FrameNode* frameNode)
{
    PickerTextStyle pickerTextStyle;
    CHECK_NULL_RETURN(frameNode, pickerTextStyle);
    auto context = frameNode->GetContext();
    CHECK_NULL_RETURN(context, pickerTextStyle);
    auto theme = context->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(theme, pickerTextStyle);
    auto style = theme->GetOptionStyle(false, false);
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        TextPickerLayoutProperty, FontSize, pickerTextStyle.fontSize, frameNode, style.GetFontSize());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        TextPickerLayoutProperty, Color, pickerTextStyle.textColor, frameNode, style.GetTextColor());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        TextPickerLayoutProperty, Weight, pickerTextStyle.fontWeight, frameNode, style.GetFontWeight());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextPickerLayoutProperty, FontFamily,
        pickerTextStyle.fontFamily, frameNode, style.GetFontFamilies());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextPickerLayoutProperty, FontStyle,
        pickerTextStyle.fontStyle, frameNode, style.GetFontStyle());
    return pickerTextStyle;
}

PickerTextStyle TextPickerModelNG::getSelectedTextStyle(FrameNode* frameNode)
{
    PickerTextStyle pickerTextStyle;
    CHECK_NULL_RETURN(frameNode, pickerTextStyle);
    auto context = frameNode->GetContext();
    CHECK_NULL_RETURN(context, pickerTextStyle);
    auto theme = context->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(theme, pickerTextStyle);
    auto style = theme->GetOptionStyle(true, false);
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        TextPickerLayoutProperty, SelectedFontSize, pickerTextStyle.fontSize, frameNode, style.GetFontSize());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        TextPickerLayoutProperty, SelectedColor, pickerTextStyle.textColor, frameNode, style.GetTextColor());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        TextPickerLayoutProperty, SelectedWeight, pickerTextStyle.fontWeight, frameNode, style.GetFontWeight());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextPickerLayoutProperty, SelectedFontFamily,
        pickerTextStyle.fontFamily, frameNode, style.GetFontFamilies());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextPickerLayoutProperty, SelectedFontStyle,
        pickerTextStyle.fontStyle, frameNode, style.GetFontStyle());
    return pickerTextStyle;
}

int32_t TextPickerModelNG::getTextPickerSelectedIndex(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    return frameNode->GetLayoutProperty<TextPickerLayoutProperty>()->GetSelectedValue(0);
}

void TextPickerModelNG::MultiInit(const RefPtr<PickerTheme> pickerTheme)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto textPickerNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_PICKER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TextPickerPattern>(); });
    auto textPickerPattern = textPickerNode->GetPattern<TextPickerPattern>();

    CHECK_NULL_VOID(pickerTheme);
    std::lock_guard<std::shared_mutex> lock(showCountMutex_);
    showCount_ = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    stack->Push(textPickerNode);

    if (pickerTheme->IsCircleDial()) {
        auto renderContext = textPickerNode->GetRenderContext();
        renderContext->UpdateBackgroundColor(pickerTheme->GetBackgroundColor());
    }
}

void TextPickerModelNG::SetIsCascade(bool isCascade)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->SetIsCascade(isCascade);
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
        std::lock_guard<std::shared_mutex> lock(showCountMutex_);
        for (uint32_t i = 0; i < options.size(); i++) {
            auto columnNode = CreateColumnNode(NG::TEXT, showCount_);
            auto stackNode = CreateStackNode();
            auto buttonNode = CreateButtonNode();
            auto columnBlendNode = CreateColumnNode();
            buttonNode->MountToParent(stackNode);
            columnNode->MountToParent(columnBlendNode);
            columnBlendNode->MountToParent(stackNode);
            columnNode->MarkModifyDone();
            columnNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            auto layoutProperty = stackNode->GetLayoutProperty<LayoutProperty>();
            layoutProperty->UpdateAlignment(Alignment::CENTER);
            stackNode->MountToParent(AceType::Claim(frameNode));
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
        std::lock_guard<std::shared_mutex> lock(showCountMutex_);
        for (size_t i = 0; i < columnCount; i++) {
            auto columnNode = CreateColumnNode(NG::TEXT, showCount_);
            auto stackNode = CreateStackNode();
            auto buttonNode = CreateButtonNode();
            auto columnBlendNode = CreateColumnNode();
            buttonNode->MountToParent(stackNode);
            columnNode->MountToParent(columnBlendNode);
            columnBlendNode->MountToParent(stackNode);
            columnNode->MarkModifyDone();
            columnNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            auto layoutProperty = stackNode->GetLayoutProperty<LayoutProperty>();
            layoutProperty->UpdateAlignment(Alignment::CENTER);
            stackNode->MountToParent(AceType::Claim<NG::FrameNode>(frameNode));
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
    if (!IsCascade()) {
        SetUnCascadeColumns(options);
    } else {
        SetCascadeColumns(options);
    }
}

bool TextPickerModelNG::IsSingle()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_RETURN(textPickerPattern, false);
    return textPickerPattern->GetRange().size() > 0;
}

bool TextPickerModelNG::IsSingle(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_RETURN(textPickerPattern, false);
    return textPickerPattern->GetRange().size() > 0;
}

bool TextPickerModelNG::GetSingleRange(std::vector<NG::RangeContent>& rangeValue)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_RETURN(textPickerPattern, false);
    rangeValue = textPickerPattern->GetRange();
    return true;
}

bool TextPickerModelNG::GetSingleRange(FrameNode* frameNode, std::vector<NG::RangeContent>& rangeValue)
{
    rangeValue.clear();
    CHECK_NULL_RETURN(frameNode, false);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_RETURN(textPickerPattern, false);
    for (auto& item : textPickerPattern->GetRange()) {
        rangeValue.emplace_back(std::move(item));
    }
    return true;
}

bool TextPickerModelNG::IsCascade(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_RETURN(textPickerPattern, false);
    return textPickerPattern->GetIsCascade();
}

bool TextPickerModelNG::GetMultiOptions(std::vector<NG::TextCascadePickerOptions>& options)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_RETURN(textPickerPattern, false);
    options = textPickerPattern->GetMultiOptions();
    return true;
}

bool TextPickerModelNG::GetMultiOptions(FrameNode* frameNode, std::vector<NG::TextCascadePickerOptions>& options)
{
    options.clear();
    CHECK_NULL_RETURN(frameNode, false);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_RETURN(textPickerPattern, false);
    for (auto& item : textPickerPattern->GetMultiOptions()) {
        options.emplace_back(std::move(item));
    }
    return true;
}

uint32_t TextPickerModelNG::GetMaxCount(FrameNode* frameNode)
{
    return 1;
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
    auto eventHub = frameNode->GetOrCreateEventHub<TextPickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnValueChangeEvent(std::move(onValueChangeEvent));
}

void TextPickerModelNG::SetOnSelectedChangeEvent(TextCascadeSelectedChangeEvent&& onSelectedChangeEvent)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<TextPickerEventHub>();
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
    std::function<void(const std::string&)>&& onScrollStop,
    std::function<void(const std::string&)>&& onEnterSelectedArea, TextPickerDialog& textPickerDialog,
    TextPickerDialogEvent& textPickerDialogEvent, const std::vector<ButtonInfo>& buttonInfos)
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
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(theme);

    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent;
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogEvent["acceptId"] = onAccept;
    dialogEvent["changeId"] = onChange;
    dialogEvent["scrollStopId"] = onScrollStop;
    dialogEvent["enterSelectedAreaId"] = onEnterSelectedArea;
    auto func = [onCancel](const GestureEvent& /* info */) {
        if (onCancel) {
            onCancel();
        }
    };
    dialogCancelEvent["cancelId"] = func;
    dialogLifeCycleEvent["didAppearId"] = textPickerDialogEvent.onDidAppear;
    dialogLifeCycleEvent["didDisappearId"] = textPickerDialogEvent.onDidDisappear;
    dialogLifeCycleEvent["willAppearId"] = textPickerDialogEvent.onWillAppear;
    dialogLifeCycleEvent["willDisappearId"] = textPickerDialogEvent.onWillDisappear;
    DialogProperties properties;
    SetDialogProperties(properties, textPickerDialog, theme);

    auto context = AccessibilityManager::DynamicCast<NG::PipelineContext>(pipelineContext);
    auto overlayManager = context ? context->GetOverlayManager() : nullptr;
    executor->PostTask(
        [properties, settingData, dialogEvent, dialogCancelEvent, dialogLifeCycleEvent, buttonInfos,
            weak = WeakPtr<NG::OverlayManager>(overlayManager)] {
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->ShowTextDialog(
                properties, settingData, dialogEvent, dialogCancelEvent, dialogLifeCycleEvent, buttonInfos);
        },
        TaskExecutor::TaskType::UI, "ArkUITextPickerShowTextDialog",
        TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
}

void TextPickerModelNG::SetCanLoop(FrameNode* frameNode, const bool value)
{
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->SetCanLoop(value);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, CanLoop, value, frameNode);
}

int32_t TextPickerModelNG::GetCanLoop(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 1);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_RETURN(textPickerPattern, 1);
    return textPickerPattern->GetCanLoop();
}

void TextPickerModelNG::SetDigitalCrownSensitivity(int32_t crownSensitivity)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetDigitalCrownSensitivity(frameNode, crownSensitivity);
}

void TextPickerModelNG::SetDigitalCrownSensitivity(FrameNode* frameNode, int32_t crownSensitivity)
{
    if (crownSensitivity < CROWN_SENSITIVITY_MIN || crownSensitivity > CROWN_SENSITIVITY_MAX) {
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->SetDigitalCrownSensitivity(crownSensitivity);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DigitalCrownSensitivity, crownSensitivity, frameNode);
}

void TextPickerModelNG::SetDigitalCrownSensitivity(FrameNode* frameNode, std::optional<int32_t>& valueOpt)
{
    if (valueOpt) {
        if (valueOpt.value() < CROWN_SENSITIVITY_MIN || valueOpt.value() > CROWN_SENSITIVITY_MAX) {
            return;
        }
        CHECK_NULL_VOID(frameNode);
        auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
        CHECK_NULL_VOID(textPickerPattern);
        textPickerPattern->SetDigitalCrownSensitivity(valueOpt.value());
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DigitalCrownSensitivity, valueOpt.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DigitalCrownSensitivity, frameNode);
    }
}

void TextPickerModelNG::SetSelecteds(FrameNode* frameNode, const std::vector<uint32_t>& values)
{
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->SetSelecteds(values);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, Selecteds, values, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedIndex, values, frameNode);
}
void TextPickerModelNG::SetSelected(FrameNode* frameNode, uint32_t value)
{
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->SetSelected(value);
    std::vector<uint32_t> values;
    values.emplace_back(value);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, Selected, value, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedIndex, values, frameNode);
}
void TextPickerModelNG::SetHasSelectAttr(FrameNode* frameNode, bool value)
{
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->SetHasSelectAttr(value);
}

void TextPickerModelNG::SetIsCascade(FrameNode* frameNode, bool isCascade)
{
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->SetIsCascade(isCascade);
}

void TextPickerModelNG::SetColumnKind(FrameNode* frameNode, uint32_t columnKind)
{
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    columnKind_ = columnKind;
    textPickerPattern->SetColumnsKind(columnKind);
}

void TextPickerModelNG::SetNormalTextStyle(
    FrameNode* frameNode, const RefPtr<PickerTheme>& pickerTheme, const NG::PickerTextStyle& value)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(pickerTheme);
    if (SystemProperties::ConfigChangePerform()) {
        ParseNormalTextStyleResObj(value);
    }

    auto normalStyle = pickerTheme->GetOptionStyle(false, false);
    if (value.fontSize.has_value() && value.fontSize->IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, FontSize,
            ConvertFontScaleValue(value.fontSize.value()), frameNode);
    } else {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, FontSize,
            ConvertFontScaleValue(normalStyle.GetFontSize()), frameNode);
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, Color, value.textColor.value_or(normalStyle.GetTextColor()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, Weight, value.fontWeight.value_or(normalStyle.GetFontWeight()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, FontFamily, value.fontFamily.value_or(normalStyle.GetFontFamilies()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, FontStyle, value.fontStyle.value_or(normalStyle.GetFontStyle()), frameNode);

    if (value.minFontSize.has_value() && value.minFontSize->IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, MinFontSize,
            ConvertFontScaleValue(value.minFontSize.value()), frameNode);
    } else {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, MinFontSize, Dimension(), frameNode);
    }
    if (value.maxFontSize.has_value() && value.maxFontSize->IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, MaxFontSize,
            ConvertFontScaleValue(value.maxFontSize.value()), frameNode);
    } else {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, MaxFontSize, Dimension(), frameNode);
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, TextOverflow,
        value.textOverflow.value_or(TextOverflow::CLIP), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, NormalTextColorSetByUser, value.textColorSetByUser, frameNode);
}

void TextPickerModelNG::SetSelectedTextStyle(
    FrameNode* frameNode, const RefPtr<PickerTheme>& pickerTheme, const NG::PickerTextStyle& value)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(pickerTheme);
    if (SystemProperties::ConfigChangePerform()) {
        ParseSelectedTextStyleResObj(value);
    }

    auto selectedStyle = pickerTheme->GetOptionStyle(true, false);
    if (value.fontSize.has_value() && value.fontSize->IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            TextPickerLayoutProperty, SelectedFontSize,
            ConvertFontScaleValue(value.fontSize.value()), frameNode);
    } else {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            TextPickerLayoutProperty, SelectedFontSize,
            ConvertFontScaleValue(selectedStyle.GetFontSize()), frameNode);
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, SelectedColor,
        value.textColor.value_or(selectedStyle.GetTextColor()), frameNode);

    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, SelectedWeight,
        value.fontWeight.value_or(selectedStyle.GetFontWeight()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, SelectedFontFamily,
        value.fontFamily.value_or(selectedStyle.GetFontFamilies()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, SelectedFontStyle, value.fontStyle.value_or(selectedStyle.GetFontStyle()), frameNode);

    if (value.minFontSize.has_value() && value.minFontSize->IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedMinFontSize,
            ConvertFontScaleValue(value.minFontSize.value()), frameNode);
    } else {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedMinFontSize, Dimension(), frameNode);
    }
    if (value.maxFontSize.has_value() && value.maxFontSize->IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedMaxFontSize,
            ConvertFontScaleValue(value.maxFontSize.value()), frameNode);
    } else {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedMaxFontSize, Dimension(), frameNode);
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedTextOverflow,
        value.textOverflow.value_or(TextOverflow::CLIP), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, SelectedTextColorSetByUser, value.textColorSetByUser, frameNode);
}

void TextPickerModelNG::SetDisappearTextStyle(
    FrameNode* frameNode, const RefPtr<PickerTheme>& pickerTheme, const NG::PickerTextStyle& value)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(pickerTheme);
    if (SystemProperties::ConfigChangePerform()) {
        ParseDisappearTextStyleResObj(value);
    }
    auto disappearStyle = pickerTheme->GetDisappearOptionStyle();
    if (value.fontSize.has_value() && value.fontSize->IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            TextPickerLayoutProperty, DisappearFontSize,
            ConvertFontScaleValue(value.fontSize.value()), frameNode);
    } else {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            TextPickerLayoutProperty, DisappearFontSize,
            ConvertFontScaleValue(disappearStyle.GetFontSize()), frameNode);
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, DisappearColor, value.textColor.value_or(disappearStyle.GetTextColor()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, DisappearWeight,
        value.fontWeight.value_or(disappearStyle.GetFontWeight()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, DisappearFontFamily,
        value.fontFamily.value_or(disappearStyle.GetFontFamilies()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, DisappearFontStyle,
        value.fontStyle.value_or(disappearStyle.GetFontStyle()), frameNode);

    if (value.minFontSize.has_value() && value.minFontSize->IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DisappearMinFontSize,
            ConvertFontScaleValue(value.minFontSize.value()), frameNode);
    } else {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DisappearMinFontSize, Dimension(), frameNode);
    }
    if (value.maxFontSize.has_value() && value.maxFontSize->IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DisappearMaxFontSize,
            ConvertFontScaleValue(value.maxFontSize.value()), frameNode);
    } else {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DisappearMaxFontSize, Dimension(), frameNode);
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DisappearTextOverflow,
        value.textOverflow.value_or(TextOverflow::CLIP), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, DisappearTextColorSetByUser, value.textColorSetByUser, frameNode);
}

void TextPickerModelNG::SetDefaultPickerItemHeight(FrameNode* frameNode, std::optional<Dimension> valueOpt)
{
    CHECK_NULL_VOID(frameNode);
    if (valueOpt) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DefaultPickerItemHeight, valueOpt.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DefaultPickerItemHeight, frameNode);
    }
}

Dimension TextPickerModelNG::GetDefaultPickerItemHeight(FrameNode* frameNode)
{
    Dimension value = Dimension(0.0f);
    CHECK_NULL_RETURN(frameNode, value);
    auto layoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, value);
    return layoutProperty->HasDefaultPickerItemHeight() ? layoutProperty->GetDefaultPickerItemHeightValue() : value;
}

void TextPickerModelNG::SetBackgroundColor(FrameNode* frameNode, const Color& color)
{
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->SetBackgroundColor(color);
}

void TextPickerModelNG::SetRange(FrameNode* frameNode, const std::vector<NG::RangeContent>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GetChildren().empty()) {
        std::lock_guard<std::shared_mutex> lock(showCountMutex_);
        RefPtr<FrameNode> columnNode = nullptr;
        if (columnKind_ == TEXT) {
            columnNode = CreateColumnNode(TEXT, showCount_);
        } else if (columnKind_ == MIXTURE) {
            columnNode = CreateColumnNode(MIXTURE, showCount_);
        }
        auto stackNode = CreateStackNode();
        auto buttonNode = CreateButtonNode();
        auto columnBlendNode = CreateColumnNode();
        buttonNode->MountToParent(stackNode);
        columnNode->MountToParent(columnBlendNode);
        columnBlendNode->MountToParent(stackNode);
        columnNode->MarkModifyDone();
        columnNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        auto layoutProperty = stackNode->GetLayoutProperty<LayoutProperty>();
        layoutProperty->UpdateAlignment(Alignment::CENTER);
        stackNode->MountToParent(AceType::Claim(frameNode));
    }
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->SetRange(value);
}

void TextPickerModelNG::SetColumns(FrameNode* frameNode, const std::vector<NG::TextCascadePickerOptions>& options)
{
    if (!IsCascade(frameNode)) {
        SetUnCascadeColumnsNode(frameNode, options);
    } else {
        SetCascadeColumnsNode(frameNode, options);
    }
}

void TextPickerModelNG::SetUnCascadeColumnsNode(FrameNode* frameNode,
    const std::vector<NG::TextCascadePickerOptions>& options)
{
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GetChildren().empty()) {
        std::lock_guard<std::shared_mutex> lock(showCountMutex_);
        for (uint32_t i = 0; i < options.size(); i++) {
            auto columnNode = CreateColumnNode(TEXT, showCount_);
            auto stackNode = CreateStackNode();
            auto buttonNode = CreateButtonNode();
            auto columnBlendNode = CreateColumnNode();
            buttonNode->MountToParent(stackNode);
            columnNode->MountToParent(columnBlendNode);
            columnBlendNode->MountToParent(stackNode);
            columnNode->MarkModifyDone();
            columnNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            auto layoutProperty = stackNode->GetLayoutProperty<LayoutProperty>();
            layoutProperty->UpdateAlignment(Alignment::CENTER);
            stackNode->MountToParent(AceType::Claim(frameNode));
        }
    }

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->SetCascadeOptions(options, options);
}

void TextPickerModelNG::SetCascadeColumnsNode(FrameNode* frameNode,
    const std::vector<NG::TextCascadePickerOptions>& options)
{
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
        std::lock_guard<std::shared_mutex> lock(showCountMutex_);
        for (size_t i = 0; i < columnCount; i++) {
            auto columnNode = CreateColumnNode(NG::TEXT, showCount_);
            auto stackNode = CreateStackNode();
            auto buttonNode = CreateButtonNode();
            auto columnBlendNode = CreateColumnNode();
            buttonNode->MountToParent(stackNode);
            columnNode->MountToParent(columnBlendNode);
            columnBlendNode->MountToParent(stackNode);
            columnNode->MarkModifyDone();
            columnNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            auto layoutProperty = stackNode->GetLayoutProperty<LayoutProperty>();
            layoutProperty->UpdateAlignment(Alignment::CENTER);
            stackNode->MountToParent(AceType::Claim(frameNode));
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

void TextPickerModelNG::SetValue(FrameNode* frameNode, const std::string& value)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, Value, value, frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    auto rangeValue = textPickerPattern->GetRange();
    auto valueIterator = std::find_if(rangeValue.begin(), rangeValue.end(),
        [&value](const NG::RangeContent& range) { return range.text_ == value; });
    if (valueIterator != rangeValue.end()) {
        TextPickerModelNG::SetSelected(frameNode, std::distance(rangeValue.begin(), valueIterator));
    }
}

void TextPickerModelNG::ValidateData(
    NG::TextCascadePickerOptions& options, const std::vector<std::string>& values, uint32_t index,
    std::vector<std::string>& selectedValues, std::vector<uint32_t>& valuesIndex)
{
    if (values.size() < index + 1) {
        if (options.rangeResult.size() > 0) {
            selectedValues.emplace_back(options.rangeResult[0]);
        } else {
            selectedValues.emplace_back("");
        }
        valuesIndex.emplace_back(0);
    } else {
        auto valueIterator =
            std::find(options.rangeResult.begin(), options.rangeResult.end(), values[index]);
        if (valueIterator == options.rangeResult.end()) {
            selectedValues.emplace_back(options.rangeResult.front());
            valuesIndex.emplace_back(0);
        } else {
            selectedValues.emplace_back(values[index]);
            valuesIndex.emplace_back(std::distance(options.rangeResult.begin(), valueIterator));
        }
    }
}

void TextPickerModelNG::SetValues(FrameNode* frameNode, const std::vector<std::string>& values)
{
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    std::vector<std::string> selectedValues;
    std::vector<uint32_t> valuesIndex;
    auto options = textPickerPattern->GetMultiOptions();
    if (!IsCascade(frameNode)) {
        for (uint32_t i = 0; i < options.size(); i++) {
            ValidateData(options[i], values, i, selectedValues, valuesIndex);
        }
        TextPickerModelNG::SetSelecteds(frameNode, valuesIndex);
    } else {
        for (uint32_t i = 0; i < values.size(); i++) {
            selectedValues.emplace_back(values[i]);
        }
    }
    textPickerPattern->SetValues(selectedValues);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, Values, selectedValues, frameNode);
}

void TextPickerModelNG::SetDefaultAttributes(RefPtr<FrameNode>& frameNode, const RefPtr<PickerTheme>& pickerTheme)
{
    auto selectedStyle = pickerTheme->GetOptionStyle(true, false);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedFontSize,
        ConvertFontScaleValue(selectedStyle.GetFontSize()), frameNode);
    ResetTextPickerTextStyleColor(Referenced::RawPtr(frameNode), &TextPickerLayoutProperty::GetSelectedTextStyle);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedWeight, selectedStyle.GetFontWeight(), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, SelectedFontFamily, selectedStyle.GetFontFamilies(), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, SelectedFontStyle, selectedStyle.GetFontStyle(), frameNode);

    auto disappearStyle = pickerTheme->GetDisappearOptionStyle();
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, DisappearFontSize,
        ConvertFontScaleValue(disappearStyle.GetFontSize()), frameNode);
    ResetTextPickerTextStyleColor(Referenced::RawPtr(frameNode), &TextPickerLayoutProperty::GetDisappearTextStyle);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, DisappearWeight, disappearStyle.GetFontWeight(), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, DisappearFontFamily, disappearStyle.GetFontFamilies(), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, DisappearFontStyle, disappearStyle.GetFontStyle(), frameNode);

    auto normalStyle = pickerTheme->GetOptionStyle(false, false);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, FontSize,
        ConvertFontScaleValue(normalStyle.GetFontSize()), frameNode);
    ResetTextPickerTextStyleColor(Referenced::RawPtr(frameNode), &TextPickerLayoutProperty::GetTextStyle);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, Weight, normalStyle.GetFontWeight(), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, FontFamily, normalStyle.GetFontFamilies(), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, FontStyle, normalStyle.GetFontStyle(), frameNode);

    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, CanLoop, true, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, DigitalCrownSensitivity, pickerTheme->GetDigitalCrownSensitivity(), frameNode);
}

void TextPickerModelNG::SetDefaultTextStyle(
    FrameNode* frameNode, const RefPtr<TextTheme>& textTheme, const NG::PickerTextStyle& value)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(textTheme);
    if (SystemProperties::ConfigChangePerform()) {
        ParseDefaultTextStyleResObj(value);
    }

    auto textStyle = textTheme->GetTextStyle();
    if (value.fontSize.has_value() && value.fontSize->IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DefaultFontSize,
            ConvertFontScaleValue(value.fontSize.value()), frameNode);
    } else {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DefaultFontSize,
            ConvertFontScaleValue(textStyle.GetFontSize()), frameNode);
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DefaultColor,
        value.textColor.value_or(textStyle.GetTextColor()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DefaultWeight,
        value.fontWeight.value_or(textStyle.GetFontWeight()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DefaultFontFamily,
        value.fontFamily.value_or(textStyle.GetFontFamilies()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DefaultFontStyle,
        value.fontStyle.value_or(textStyle.GetFontStyle()), frameNode);
    if (value.minFontSize.has_value() && value.minFontSize->IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DefaultMinFontSize,
            ConvertFontScaleValue(value.minFontSize.value()), frameNode);
    } else {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DefaultMinFontSize, Dimension(), frameNode);
    }
    if (value.maxFontSize.has_value() && value.maxFontSize->IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DefaultMaxFontSize,
            ConvertFontScaleValue(value.maxFontSize.value()), frameNode);
    } else {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DefaultMaxFontSize, Dimension(), frameNode);
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DefaultTextOverflow,
        value.textOverflow.value_or(textStyle.GetTextOverflow()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DefaultTextColorSetByUser,
        value.textColorSetByUser, frameNode);
}

void TextPickerModelNG::SetDefaultTextStyle(FrameNode* frameNode, const NG::PickerTextStyle& value)
{
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto textTheme = context->GetTheme<TextTheme>();
    CHECK_NULL_VOID(textTheme);
    SetDefaultTextStyle(frameNode, textTheme, value);
}

std::string TextPickerModelNG::getTextPickerValue(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, "");
    return frameNode->GetLayoutProperty<TextPickerLayoutProperty>()->GetValueValue("");
}

std::string TextPickerModelNG::getTextPickerRange(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, "");
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_RETURN(textPickerPattern, "");
    return textPickerPattern->GetTextPickerRange();
}

void TextPickerModelNG::SetDivider(const ItemDivider& divider)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    ParseDividerResObj(frameNode, divider);
    textPickerPattern->SetDivider(divider);
    textPickerPattern->SetCustomDividerFlag(true);
    ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, Divider, divider);
}

void TextPickerModelNG::SetDivider(FrameNode* frameNode, const ItemDivider& divider)
{
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    ParseDividerResObj(frameNode, divider);
    textPickerPattern->SetDivider(divider);
    textPickerPattern->SetCustomDividerFlag(true);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, Divider, divider, frameNode);
}

void TextPickerModelNG::SetGradientHeight(FrameNode* frameNode, std::optional<Dimension> valueOpt)
{
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    auto value = valueOpt.value_or(theme->GetGradientHeight());
    textPickerPattern->SetGradientHeight(value);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, GradientHeight, value, frameNode);
}

void TextPickerModelNG::SetDisableTextStyleAnimation(FrameNode* frameNode, const bool value)
{
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->SetDisableTextStyleAnimation(value);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DisableTextStyleAnimation, value, frameNode);
}

void TextPickerModelNG::SetOnCascadeChange(FrameNode* frameNode, TextCascadeChangeEvent&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<TextPickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

void TextPickerModelNG::SetOnScrollStop(FrameNode* frameNode, TextCascadeChangeEvent&& onScrollStop)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<TextPickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollStop(std::move(onScrollStop));
}

int32_t TextPickerModelNG::GetSelectedSize(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_RETURN(textPickerPattern, 0);
    return textPickerPattern->GetSelecteds().size();
}

int32_t TextPickerModelNG::GetColumnWidthsSize(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_RETURN(textPickerPattern, 0);
    return textPickerPattern->GetColumnWidths().size();
}

std::string TextPickerModelNG::getTextPickerValues(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, "");
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_RETURN(textPickerPattern, "");
    auto values = textPickerPattern->GetValues();
    std::string result;
    for (auto& valueRet : values) {
        result.append(valueRet + ';');
    }
    const size_t length = result.length();
    result = result.substr(0, length > 0 ? length - 1 : 0);
    return result;
}

std::vector<uint32_t> TextPickerModelNG::getTextPickerSelecteds(FrameNode* frameNode)
{
    std::vector<uint32_t> defaultValue = { 0 };
    CHECK_NULL_RETURN(frameNode, defaultValue);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_RETURN(textPickerPattern, defaultValue);
    return textPickerPattern->GetSelecteds();
}

void TextPickerModelNG::SetTextPickerRangeType(FrameNode* frameNode, int32_t rangeType)
{
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->SetRangeType(rangeType);
}

int32_t TextPickerModelNG::GetTextPickerRangeType(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_RETURN(textPickerPattern, 0);
    return textPickerPattern->GetRangeType();
}

const Dimension TextPickerModelNG::ConvertFontScaleValue(const Dimension& fontSizeValue)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, fontSizeValue);
    auto maxAppFontScale = pipeline->GetMaxAppFontScale();
    auto follow = pipeline->IsFollowSystem();
    float fontScale = pipeline->GetFontScale();
    if (NearZero(fontScale) || (fontSizeValue.Unit() == DimensionUnit::VP)) {
        return fontSizeValue;
    }
    if (GreatOrEqualCustomPrecision(fontScale, PICKER_MAXFONTSCALE) && follow) {
        fontScale = std::clamp(fontScale, 0.0f, maxAppFontScale);
        if (fontScale != 0.0f) {
            return Dimension(fontSizeValue / fontScale);
        }
    }
    return fontSizeValue;
}

const std::string TextPickerModelNG::GetSelectedObjectStr(FrameNode* frameNode,
    const std::string value, const uint32_t index)
{
    CHECK_NULL_RETURN(frameNode, "framenode null");
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_RETURN(textPickerPattern, "pattern null");
    return textPickerPattern->GetSelectedObjectStr(value, index);
}

void TextPickerModelNG::HasUserDefinedOpacity()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    textPickerPattern->SetUserDefinedOpacity(renderContext->GetOpacityValue(1.0));
}

void TextPickerModelNG::SetOnValueChangeEvent(FrameNode* frameNode, TextCascadeValueChangeEvent&& onValueChangeEvent)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<TextPickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnValueChangeEvent(std::move(onValueChangeEvent));
}

void TextPickerModelNG::SetOnSelectedChangeEvent(FrameNode* frameNode,
    TextCascadeSelectedChangeEvent&& onSelectedChangeEvent)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<TextPickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSelectedChangeEvent(std::move(onSelectedChangeEvent));
}

void TextPickerModelNG::SetEnableHapticFeedback(bool isEnableHapticFeedback)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    SetEnableHapticFeedback(frameNode, isEnableHapticFeedback);
}

void TextPickerModelNG::SetEnableHapticFeedback(FrameNode* frameNode, const std::optional<bool>& valueOpt)
{
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    bool isEnableHapticFeedback = DEFAULT_ENABLE_HAPTIC_FEEDBACK;
    if (valueOpt) {
        isEnableHapticFeedback = valueOpt.value();
    }
    textPickerPattern->SetIsEnableHaptic(isEnableHapticFeedback);
}

bool TextPickerModelNG::GetEnableHapticFeedback(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, DEFAULT_ENABLE_HAPTIC_FEEDBACK);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_RETURN(textPickerPattern, DEFAULT_ENABLE_HAPTIC_FEEDBACK);
    return textPickerPattern->GetIsEnableHaptic();
}

void TextPickerModelNG::SetSelectedBackgroundStyle(const NG::PickerBackgroundStyle& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    ParseBackgroundStyleColorResObj(frameNode, value);
    ParseBackgroundStyleRadiusResObj(frameNode, value);
    if (value.color.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedBackgroundColor,
            value.color.value());
    }
    if (value.borderRadius.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedBorderRadius,
            value.borderRadius.value());
    }
}

void TextPickerModelNG::SetSelectedBackgroundStyle(FrameNode* frameNode, const NG::PickerBackgroundStyle& value)
{
    CHECK_NULL_VOID(frameNode);
    ParseBackgroundStyleColorResObj(frameNode, value);
    ParseBackgroundStyleRadiusResObj(frameNode, value);
    if (value.color.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedBackgroundColor,
            value.color.value(), frameNode);
    }
    if (value.borderRadius.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedBorderRadius,
            value.borderRadius.value(), frameNode);
    }
}

PickerBackgroundStyle TextPickerModelNG::GetSelectedBackgroundStyle(FrameNode* frameNode)
{
    PickerBackgroundStyle pickerBgStyle;
    CHECK_NULL_RETURN(frameNode, pickerBgStyle);
    auto context = frameNode->GetContext();
    CHECK_NULL_RETURN(context, pickerBgStyle);
    auto theme = context->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(theme, pickerBgStyle);
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextPickerLayoutProperty, SelectedBackgroundColor,
        pickerBgStyle.color, frameNode, theme->GetSelectedBackgroundColor());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextPickerLayoutProperty, SelectedBorderRadius,
        pickerBgStyle.borderRadius, frameNode, theme->GetSelectedBorderRadius());
    return pickerBgStyle;
}

bool TextPickerModelNG::IsCascade()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_RETURN(textPickerPattern, false);
    return textPickerPattern->GetIsCascade();
}

void TextPickerModelNG::SetSingleRange(bool isSingleRange)
{
    std::lock_guard<std::shared_mutex> lock(isSingleMutex_);
    isSingleRange_ = isSingleRange;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->SetSingleRange(isSingleRange);
}

void TextPickerModelNG::UpdateUserSetSelectColor()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->UpdateUserSetSelectColor();
}

void TextPickerModelNG::ParseGradientHeight(const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(resObj);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    ParseGradientHeight(frameNode, resObj);
}

void TextPickerModelNG::ParseGradientHeight(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }

    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(resObj);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);

    auto&& updateFunc = [frameNode](const RefPtr<ResourceObject>& resObj) {
        CalcDimension height;
        if (!resObj || !ResourceParseUtils::ParseResDimensionFp(resObj, height)) {
            return;
        }
        auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
        CHECK_NULL_VOID(textPickerPattern);
        textPickerPattern->SetGradientHeight(height);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, GradientHeight, height, frameNode);
    };
    textPickerPattern->AddResObj("textPicker.gradientHeight", resObj, std::move(updateFunc));
}

void TextPickerModelNG::ParseDividerResObj(FrameNode* frameNode, const NG::ItemDivider& divider)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }

    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);

    if (!divider.strokeWidthResObj && !divider.colorResObj && !divider.startMarginResObj && !divider.endMarginResObj) {
        textPickerPattern->RemoveResObj("textPicker.divider");
        return;
    }

    auto&& updateFunc = [frameNode, divider](const RefPtr<ResourceObject>& resObj) {
        auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
        CHECK_NULL_VOID(textPickerPattern);
        auto context = frameNode->GetContext();
        CHECK_NULL_VOID(context);
        auto pickerTheme = context->GetTheme<PickerTheme>();
        CHECK_NULL_VOID(pickerTheme);

        NG::ItemDivider& curDivider = const_cast<NG::ItemDivider&>(divider);
        CalcDimension strokeWidth = pickerTheme->GetDividerThickness();
        curDivider.strokeWidth = strokeWidth;
        if (curDivider.strokeWidthResObj &&
            ResourceParseUtils::ParseResDimensionFpNG(curDivider.strokeWidthResObj, strokeWidth)) {
            curDivider.strokeWidth = strokeWidth;
        }

        Color color = pickerTheme->GetDividerColor();
        curDivider.color = color;
        if (curDivider.colorResObj && ResourceParseUtils::ParseResColor(curDivider.colorResObj, color)) {
            curDivider.color = color;
        }

        CalcDimension startMargin = 0.0_vp;
        curDivider.startMargin = startMargin;
        if (curDivider.startMarginResObj &&
            ResourceParseUtils::ParseResDimensionFpNG(curDivider.startMarginResObj, startMargin)) {
            curDivider.startMargin = startMargin;
        }

        CalcDimension endMargin = 0.0_vp;
        curDivider.endMargin = endMargin;
        if (curDivider.endMarginResObj &&
            ResourceParseUtils::ParseResDimensionFpNG(curDivider.endMarginResObj, endMargin)) {
            curDivider.endMargin = endMargin;
        }

        textPickerPattern->SetDivider(curDivider);
        textPickerPattern->SetCustomDividerFlag(true);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, Divider, curDivider, frameNode);
    };
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    textPickerPattern->RemoveResObj("textPicker.divider");
    textPickerPattern->AddResObj("textPicker.divider", resObj, std::move(updateFunc));
}

void TextPickerModelNG::ParseResTextStyle(const PickerTextStyle& textStyleOpt, const std::string& textStyleType,
    std::function<void(const PickerTextStyle&)> updateTextStyleFunc)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(pickerPattern);

    if (!textStyleOpt.textColorResObj && !textStyleOpt.fontSizeResObj && !textStyleOpt.fontFamilyResObj &&
        !textStyleOpt.minFontSizeResObj && !textStyleOpt.maxFontSizeResObj) {
        pickerPattern->RemoveResObj(textStyleType);
        return;
    }

    auto&& updateFunc = [textStyleOpt, frameNode, updateTextStyleFunc](const RefPtr<ResourceObject> resObj) {
        PickerTextStyle textStyle;
        Color color;
        CalcDimension fontSize;
        std::vector<std::string> families;

        if (textStyleOpt.textColorResObj &&
            ResourceParseUtils::ParseResColor(textStyleOpt.textColorResObj, color)) {
            textStyle.textColor = color;
        }

        if (textStyleOpt.fontSizeResObj &&
            ResourceParseUtils::ParseResDimensionFp(textStyleOpt.fontSizeResObj, fontSize)) {
            textStyle.fontSize = fontSize;
        }

        if (textStyleOpt.fontFamilyResObj &&
            ResourceParseUtils::ParseResFontFamilies(textStyleOpt.fontFamilyResObj, families)) {
            textStyle.fontFamily = families;
        }

        CalcDimension minFontSize;
        if (textStyleOpt.minFontSizeResObj &&
            ResourceParseUtils::ParseResDimensionFp(textStyleOpt.minFontSizeResObj, minFontSize)) {
            textStyle.minFontSize = minFontSize;
        }

        CalcDimension maxFontSize;
        if (textStyleOpt.maxFontSizeResObj &&
            ResourceParseUtils::ParseResDimensionFp(textStyleOpt.maxFontSizeResObj, maxFontSize)) {
            textStyle.maxFontSize = maxFontSize;
        }

        updateTextStyleFunc(textStyle);
    };
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    pickerPattern->AddResObj(textStyleType, resObj, std::move(updateFunc));
}

void TextPickerModelNG::ParseDisappearTextStyleResObj(const PickerTextStyle& textStyleOpt)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(pickerPattern);

    ParseResTextStyle(
        textStyleOpt,
        "TextPickerDisappearTextStyle",
        [pickerPattern](const PickerTextStyle& textStyle) { pickerPattern->UpdateDisappearTextStyle(textStyle); }
    );
}

void TextPickerModelNG::ParseSelectedTextStyleResObj(const PickerTextStyle& textStyleOpt)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(pickerPattern);

    ParseResTextStyle(
        textStyleOpt,
        "TextPickerSelectedTextStyle",
        [pickerPattern](const PickerTextStyle& textStyle) { pickerPattern->UpdateSelectedTextStyle(textStyle); }
    );
}

void TextPickerModelNG::ParseNormalTextStyleResObj(const PickerTextStyle& textStyleOpt)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(pickerPattern);

    ParseResTextStyle(
        textStyleOpt,
        "TextPickerNormalTextStyle",
        [pickerPattern](const PickerTextStyle& textStyle) { pickerPattern->UpdateNormalTextStyle(textStyle); }
    );
}

void TextPickerModelNG::ParseDefaultTextStyleResObj(const PickerTextStyle& textStyleOpt)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(pickerPattern);

    ParseResTextStyle(
        textStyleOpt,
        "TextPickerDefaultTextStyle",
        [pickerPattern](const PickerTextStyle& textStyle) { pickerPattern->UpdateDefaultTextStyle(textStyle); }
    );
}

void TextPickerModelNG::ParseSingleRangeResourceObj(const RefPtr<ResourceObject>& resultResObj,
    const RefPtr<ResourceObject>& valueResObj)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);

    auto&& updateFunc = [frameNode, resultResObj, valueResObj](const RefPtr<ResourceObject> resObj) {
        auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
        CHECK_NULL_VOID(pickerPattern);

        std::vector<NG::RangeContent> rangeVector = pickerPattern->GetRange();
        std::vector<std::string> getRangeVector;

        if (resultResObj && ResourceParseUtils::ParseResStrArray(resultResObj, getRangeVector)) {
            rangeVector.clear();
            for (const auto& text : getRangeVector) {
                NG::RangeContent content;
                content.icon_ = "";
                content.text_ = text;
                rangeVector.emplace_back(content);
            }
            pickerPattern->SetRange(rangeVector);
        }

        if (pickerPattern->GetHasSelectAttr()) {
            return;
        }

        std::string result;
        if (!valueResObj || !ResourceParseUtils::ParseResString(valueResObj, result)) {
            return;
        }
        for (uint32_t index = 0; index < rangeVector.size(); index++) {
            if (rangeVector[index].text_ == result) {
                pickerPattern->SetSelected(index);
                std::vector<uint32_t> values;
                values.emplace_back(index);
                ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, Value, result);
                ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, Selected, index);
                ACE_UPDATE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedIndex, values);
                break;
            }
        }
    };
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    textPickerPattern->AddResObj("TextPicker.singleRange", resObj, std::move(updateFunc));
}

void TextPickerModelNG::ParseColumnWidthsResourceObj(const std::vector<RefPtr<ResourceObject>>& widthResObjs)
{
    if (!SystemProperties::ConfigChangePerform() || (widthResObjs.size() <= 0)) {
        return;
    }

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);

    auto&& updateFunc = [frameNode, textPickerPattern, widthResObjs](const RefPtr<ResourceObject> resObj) {
        std::vector<Dimension> widths;
        for (auto& widthResObj : widthResObjs) {
            CalcDimension calc;
            ResourceParseUtils::ParseResDimensionVpNG(widthResObj, calc);
            widths.emplace_back(calc);
        }
        textPickerPattern->SetColumnWidths(widths);
    };
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    textPickerPattern->AddResObj("TextPicker.columnWidths", resObj, std::move(updateFunc));
}

void TextPickerModelNG::ParseSingleIconTextResourceObj(const std::vector<NG::RangeContent>& value)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);

    auto&& updateFunc = [frameNode, value](const RefPtr<ResourceObject> resObj) {
        auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
        CHECK_NULL_VOID(textPickerPattern);
        std::vector<NG::RangeContent> rangeVector;
        std::vector<NG::RangeContent> oldRangeVector = textPickerPattern->GetRange();
        uint32_t index = 0;
        rangeVector.clear();
        for (auto& item : value) {
            std::string icon;
            std::string text;
            NG::RangeContent content;
            if (item.iconResObj_) {
                ResourceParseUtils::ParseResMedia(item.iconResObj_, icon);
                content.icon_ = icon;
            } else {
                content.icon_ = index < oldRangeVector.size() ? oldRangeVector[index].icon_ : "";
            }

            if (item.textResObj_) {
                ResourceParseUtils::ParseResString(item.textResObj_, text);
                content.text_ = text;
            } else {
                content.text_ = index < oldRangeVector.size() ? oldRangeVector[index].text_ : "";
            }

            rangeVector.emplace_back(content);
            index++;
        }
        uint32_t selectedIndex = textPickerPattern->GetSelected();
        textPickerPattern->SetSelected(selectedIndex);
        textPickerPattern->SetRange(rangeVector);
        textPickerPattern->UpdateMeasureOnColorModeChange();
    };
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    textPickerPattern->AddResObj("TextPicker.singleIconText", resObj, std::move(updateFunc));
}

void TextPickerModelNG::ParseCascadeResourceObj(const std::vector<NG::TextCascadePickerOptions>& options,
    const std::vector<RefPtr<ResourceObject>>& valueArrResObj)
{
    if (!SystemProperties::ConfigChangePerform() || (options.size() <= 0)) {
        return;
    }

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);

    auto&& updateFunc = [frameNode, options, valueArrResObj](const RefPtr<ResourceObject> resObj) {
        auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
        CHECK_NULL_VOID(textPickerPattern);

        std::vector<NG::TextCascadePickerOptions>& rangeOptions =
            const_cast<std::vector<NG::TextCascadePickerOptions>&>(options);
        textPickerPattern->GetAndUpdateRealSelectedArr(rangeOptions, valueArrResObj);

        // Calcalate max depth
        size_t depth = rangeOptions.empty() ? 0 : 1;
        for (size_t i = 0; i < rangeOptions.size(); i++) {
            size_t tmp = textPickerPattern->ProcessCascadeOptionDepth(rangeOptions[i]);
            if (tmp > depth) {
                depth = tmp;
            }
        }

        std::vector<NG::TextCascadePickerOptions> reOptions;
        textPickerPattern->ProcessCascadeOptions(rangeOptions, reOptions, 0);
        if (reOptions.size() < depth) {
            auto differ = depth - reOptions.size();
            for (uint32_t i = 0; i < differ; i++) {
                NG::TextCascadePickerOptions differOption;
                memset_s(&differOption, sizeof(differOption), 0, sizeof(differOption));
                reOptions.emplace_back(differOption);
            }
        }
        textPickerPattern->SetCascadeOptions(rangeOptions, reOptions);
    };
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    textPickerPattern->AddResObj("TextPicker.CascadeRange", resObj, std::move(updateFunc));
}

void TextPickerModelNG::TextPickerRemoveResObj(FrameNode* frameNode, const std::string& key)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }

    CHECK_NULL_VOID(frameNode);
    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(pickerPattern);
    pickerPattern->RemoveResObj(key);
}

void TextPickerModelNG::ParseBackgroundStyleColorResObj(FrameNode* frameNode, const NG::PickerBackgroundStyle& value)
{
    if (!SystemProperties::ConfigChangePerform() || !frameNode) {
        return;
    }

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->RemoveResObj("TextPicker.BackgroundStyle.color");

    auto&& updateColorFunc = [value, weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto node = weak.Upgrade();
        CHECK_NULL_VOID(node);

        NG::PickerBackgroundStyle& backgroundValue = const_cast<NG::PickerBackgroundStyle&>(value);
        Color color = backgroundValue.color.value();
        if (value.colorResObj && ResourceParseUtils::ParseResColor(backgroundValue.colorResObj, color)) {
            ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedBackgroundColor, color, node);
        } else if (!value.textColorSetByUser) {
            auto context = node->GetContext();
            CHECK_NULL_VOID(context);
            auto theme = context->GetTheme<PickerTheme>();
            if (theme) {
                color = theme->GetSelectedBackgroundColor();
                ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedBackgroundColor, color, node);
            }
        }
    };
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    textPickerPattern->AddResObj("TextPicker.BackgroundStyle.color", resObj, std::move(updateColorFunc));
}

void TextPickerModelNG::ParseBackgroundStyleRadiusResObj(FrameNode* frameNode, const NG::PickerBackgroundStyle& value)
{
    if (!SystemProperties::ConfigChangePerform() || !frameNode) {
        return;
    }

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->RemoveResObj("TextPicker.BackgroundStyle.borderRadius");

    if (!value.borderRadiusResObj && !value.borderRadius->HasResources()) {
        return;
    }

    auto&& updateRadiusFunc = [value, weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto node = weak.Upgrade();
        CHECK_NULL_VOID(node);

        NG::PickerBackgroundStyle& backgroundValue = const_cast<NG::PickerBackgroundStyle&>(value);
        if (backgroundValue.borderRadius->HasResources()) {
            backgroundValue.borderRadius->ReloadResources();
            NG::BorderRadiusProperty& borderRadiusValue = backgroundValue.borderRadius.value();
            ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedBorderRadius, borderRadiusValue, node);
        } else if (backgroundValue.borderRadiusResObj) {
            CalcDimension calcDimension;
            ResourceParseUtils::ParseResDimensionVpNG(backgroundValue.borderRadiusResObj, calcDimension);
            if (GreatOrEqual(calcDimension.Value(), 0.0f)) {
                NG::BorderRadiusProperty borderRadiusValue = NG::BorderRadiusProperty(calcDimension);
                ACE_UPDATE_NODE_LAYOUT_PROPERTY(
                    TextPickerLayoutProperty, SelectedBorderRadius, borderRadiusValue, node);
            }
        }
    };
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    textPickerPattern->AddResObj("TextPicker.BackgroundStyle.borderRadius", resObj, std::move(updateRadiusFunc));
}

} // namespace OHOS::Ace::NG
