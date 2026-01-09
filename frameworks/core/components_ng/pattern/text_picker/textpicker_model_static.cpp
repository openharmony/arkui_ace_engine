/*
* Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text_picker/textpicker_model_static.h"

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

namespace OHOS::Ace::NG {
namespace {
constexpr float PICKER_MAXFONTSCALE = 1.0f;
constexpr bool DEFAULT_ENABLE_HAPTIC_FEEDBACK = true;
const int32_t BUFFER_NODE_NUMBER = 2;

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

void TextPickerModelStatic::InitialSetupSinglePicker(FrameNode* frameNode, uint32_t columnKind)
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

RefPtr<FrameNode> TextPickerModelStatic::CreateColumnNode(uint32_t columnKind, uint32_t showCount)
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

RefPtr<FrameNode> TextPickerModelStatic::CreateStackNode()
{
    auto stackId = ElementRegister::GetInstance()->MakeUniqueId();
    return FrameNode::GetOrCreateFrameNode(
        V2::STACK_ETS_TAG, stackId, []() { return AceType::MakeRefPtr<StackPattern>(); });
}

RefPtr<FrameNode> TextPickerModelStatic::CreateColumnNode()
{
    auto columnId = ElementRegister::GetInstance()->MakeUniqueId();
    return FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, columnId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
}

RefPtr<FrameNode> TextPickerModelStatic::CreateButtonNode()
{
    auto buttonId = ElementRegister::GetInstance()->MakeUniqueId();
    return FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, buttonId, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
}

RefPtr<FrameNode> TextPickerModelStatic::CreateFrameNode(int32_t nodeId)
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

void TextPickerModelStatic::SetColumnWidths(FrameNode* frameNode, const std::vector<Dimension>& widths)
{
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->SetColumnWidths(widths);
}

std::vector<Dimension> TextPickerModelStatic::GetColumnWidths(FrameNode* frameNode)
{
    std::vector<Dimension> columnWidths;
    CHECK_NULL_RETURN(frameNode, columnWidths);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    columnWidths = textPickerPattern->GetColumnWidths();
    return columnWidths;
}

void TextPickerModelStatic::SetOnEnterSelectedArea(FrameNode* frameNode, TextCascadeChangeEvent&& onEnterSelectedArea)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<TextPickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnEnterSelectedArea(std::move(onEnterSelectedArea));
}

PickerTextStyle TextPickerModelStatic::getDisappearTextStyle(FrameNode* frameNode)
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

PickerTextStyle TextPickerModelStatic::getNormalTextStyle(FrameNode* frameNode)
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

PickerTextStyle TextPickerModelStatic::getSelectedTextStyle(FrameNode* frameNode)
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

int32_t TextPickerModelStatic::getTextPickerSelectedIndex(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    return frameNode->GetLayoutProperty<TextPickerLayoutProperty>()->GetSelectedValue(0);
}

bool TextPickerModelStatic::IsSingle(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_RETURN(textPickerPattern, false);
    return textPickerPattern->GetRange().size() > 0;
}

bool TextPickerModelStatic::GetSingleRange(FrameNode* frameNode, std::vector<NG::RangeContent>& rangeValue)
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

bool TextPickerModelStatic::IsCascade(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_RETURN(textPickerPattern, false);
    return textPickerPattern->GetIsCascade();
}

bool TextPickerModelStatic::GetMultiOptions(FrameNode* frameNode, std::vector<NG::TextCascadePickerOptions>& options)
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

uint32_t TextPickerModelStatic::GetMaxCount(FrameNode* frameNode)
{
    return 1;
}

void TextPickerModelStatic::SetCanLoop(FrameNode* frameNode, const bool value)
{
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->SetCanLoop(value);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, CanLoop, value, frameNode);
}

int32_t TextPickerModelStatic::GetCanLoop(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 1);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_RETURN(textPickerPattern, 1);
    return textPickerPattern->GetCanLoop();
}

void TextPickerModelStatic::SetDigitalCrownSensitivity(FrameNode* frameNode, const std::optional<int32_t>& valueOpt)
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

void TextPickerModelStatic::SetSelecteds(FrameNode* frameNode, const std::vector<uint32_t>& values)
{
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->SetSelecteds(values);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, Selecteds, values, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedIndex, values, frameNode);
}
void TextPickerModelStatic::SetSelected(FrameNode* frameNode, uint32_t value)
{
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->SetSelected(value);
    std::vector<uint32_t> values;
    values.emplace_back(value);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, Selected, value, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedIndex, values, frameNode);
}
void TextPickerModelStatic::SetHasSelectAttr(FrameNode* frameNode, bool value)
{
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->SetHasSelectAttr(value);
}

void TextPickerModelStatic::SetIsCascade(FrameNode* frameNode, bool isCascade)
{
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->SetIsCascade(isCascade);
}

void TextPickerModelStatic::SetColumnKind(FrameNode* frameNode, uint32_t columnKind)
{
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    columnKind_ = columnKind;
    textPickerPattern->SetColumnsKind(columnKind);
}

void TextPickerModelStatic::SetNormalTextStyle(
    FrameNode* frameNode, const RefPtr<PickerTheme>& pickerTheme, const NG::PickerTextStyle& value)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(pickerTheme);
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
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            TextPickerLayoutProperty, MinFontSize, ConvertFontScaleValue(value.minFontSize.value()), frameNode);
    } else {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, MinFontSize, Dimension(), frameNode);
    }
    if (value.maxFontSize.has_value() && value.maxFontSize->IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            TextPickerLayoutProperty, MaxFontSize, ConvertFontScaleValue(value.maxFontSize.value()), frameNode);
    } else {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, MaxFontSize, Dimension(), frameNode);
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, TextOverflow, value.textOverflow.value_or(TextOverflow::CLIP), frameNode);
}

void TextPickerModelStatic::SetSelectedTextStyle(
    FrameNode* frameNode, const RefPtr<PickerTheme>& pickerTheme, const NG::PickerTextStyle& value)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(pickerTheme);
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
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            TextPickerLayoutProperty, SelectedMinFontSize, ConvertFontScaleValue(value.minFontSize.value()), frameNode);
    } else {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedMinFontSize, Dimension(), frameNode);
    }
    if (value.maxFontSize.has_value() && value.maxFontSize->IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            TextPickerLayoutProperty, SelectedMaxFontSize, ConvertFontScaleValue(value.maxFontSize.value()), frameNode);
    } else {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, SelectedMaxFontSize, Dimension(), frameNode);
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, SelectedTextOverflow, value.textOverflow.value_or(TextOverflow::CLIP), frameNode);
}

void TextPickerModelStatic::SetDisappearTextStyle(
    FrameNode* frameNode, const RefPtr<PickerTheme>& pickerTheme, const NG::PickerTextStyle& value)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(pickerTheme);
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
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TextPickerLayoutProperty, DisappearTextOverflow, value.textOverflow.value_or(TextOverflow::CLIP), frameNode);
}

void TextPickerModelStatic::SetSelectedBackgroundStyle(FrameNode* frameNode, const NG::PickerBackgroundStyle& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value.color.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            TextPickerLayoutProperty, SelectedBackgroundColor, value.color.value(), frameNode);
    }
    if (value.borderRadius.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            TextPickerLayoutProperty, SelectedBorderRadius, value.borderRadius.value(), frameNode);
    }
}

void TextPickerModelStatic::SetDefaultPickerItemHeight(FrameNode* frameNode, std::optional<Dimension> valueOpt)
{
    CHECK_NULL_VOID(frameNode);
    if (valueOpt) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DefaultPickerItemHeight, valueOpt.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DefaultPickerItemHeight, frameNode);
    }
}

Dimension TextPickerModelStatic::GetDefaultPickerItemHeight(FrameNode* frameNode)
{
    Dimension value = Dimension(0.0f);
    CHECK_NULL_RETURN(frameNode, value);
    auto layoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, value);
    return layoutProperty->HasDefaultPickerItemHeight() ? layoutProperty->GetDefaultPickerItemHeightValue() : value;
}

void TextPickerModelStatic::SetBackgroundColor(FrameNode* frameNode, const Color& color)
{
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->SetBackgroundColor(color);
}

void TextPickerModelStatic::SetRange(FrameNode* frameNode, const std::vector<NG::RangeContent>& value)
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

void TextPickerModelStatic::SetColumns(FrameNode* frameNode, const std::vector<NG::TextCascadePickerOptions>& options)
{
    if (!IsCascade(frameNode)) {
        SetUnCascadeColumnsNode(frameNode, options);
    } else {
        SetCascadeColumnsNode(frameNode, options);
    }
}

void TextPickerModelStatic::SetUnCascadeColumnsNode(FrameNode* frameNode,
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

void TextPickerModelStatic::SetCascadeColumnsNode(FrameNode* frameNode,
    const std::vector<NG::TextCascadePickerOptions>& options)
{
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    std::vector<NG::TextCascadePickerOptions> reOptions;
    // Calculate max depth
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
            reOptions.emplace_back(differOption);
        }
    }
    textPickerPattern->SetCascadeOptions(options, reOptions);
}

void TextPickerModelStatic::SetValue(FrameNode* frameNode, const std::string& value)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, Value, value, frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    auto rangeValue = textPickerPattern->GetRange();
    auto valueIterator = std::find_if(rangeValue.begin(), rangeValue.end(),
        [&value](const NG::RangeContent& range) { return range.text_ == value; });
    if (valueIterator != rangeValue.end()) {
        TextPickerModelStatic::SetSelected(frameNode, std::distance(rangeValue.begin(), valueIterator));
    }
}

void TextPickerModelStatic::ValidateData(
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

void TextPickerModelStatic::SetValues(FrameNode* frameNode, const std::vector<std::string>& values)
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
    } else {
        for (uint32_t i = 0; i < values.size(); i++) {
            selectedValues.emplace_back(values[i]);
        }
    }
    textPickerPattern->SetValues(selectedValues);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, Values, selectedValues, frameNode);
}

void TextPickerModelStatic::SetDefaultAttributes(RefPtr<FrameNode>& frameNode, const RefPtr<PickerTheme>& pickerTheme)
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

void TextPickerModelStatic::SetDefaultTextStyle(
    FrameNode* frameNode, const RefPtr<TextTheme>& textTheme, const NG::PickerTextStyle& value)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(textTheme);
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
}

void TextPickerModelStatic::SetDefaultTextStyle(FrameNode* frameNode, const NG::PickerTextStyle& value)
{
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto textTheme = context->GetTheme<TextTheme>();
    CHECK_NULL_VOID(textTheme);
    SetDefaultTextStyle(frameNode, textTheme, value);
}

std::string TextPickerModelStatic::getTextPickerValue(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, "");
    return frameNode->GetLayoutProperty<TextPickerLayoutProperty>()->GetValueValue("");
}

std::string TextPickerModelStatic::getTextPickerRange(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, "");
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_RETURN(textPickerPattern, "");
    return textPickerPattern->GetTextPickerRange();
}

void TextPickerModelStatic::SetDivider(FrameNode* frameNode, const ItemDivider& divider)
{
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->SetDivider(divider);
    textPickerPattern->SetCustomDividerFlag(true);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, Divider, divider, frameNode);
}

void TextPickerModelStatic::SetGradientHeight(FrameNode* frameNode, std::optional<Dimension> valueOpt)
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

void TextPickerModelStatic::SetDisableTextStyleAnimation(FrameNode* frameNode, const bool value)
{
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->SetDisableTextStyleAnimation(value);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextPickerLayoutProperty, DisableTextStyleAnimation, value, frameNode);
}

void TextPickerModelStatic::SetOnCascadeChange(FrameNode* frameNode, TextCascadeChangeEvent&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<TextPickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

void TextPickerModelStatic::SetOnScrollStop(FrameNode* frameNode, TextCascadeChangeEvent&& onScrollStop)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<TextPickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollStop(std::move(onScrollStop));
}

int32_t TextPickerModelStatic::GetSelectedSize(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_RETURN(textPickerPattern, 0);
    return textPickerPattern->GetSelecteds().size();
}

int32_t TextPickerModelStatic::GetColumnWidthsSize(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_RETURN(textPickerPattern, 0);
    return textPickerPattern->GetColumnWidths().size();
}

std::string TextPickerModelStatic::getTextPickerValues(FrameNode* frameNode)
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

std::vector<uint32_t> TextPickerModelStatic::getTextPickerSelecteds(FrameNode* frameNode)
{
    std::vector<uint32_t> defaultValue = { 0 };
    CHECK_NULL_RETURN(frameNode, defaultValue);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_RETURN(textPickerPattern, defaultValue);
    return textPickerPattern->GetSelecteds();
}

void TextPickerModelStatic::SetTextPickerRangeType(FrameNode* frameNode, int32_t rangeType)
{
    CHECK_NULL_VOID(frameNode);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->SetRangeType(rangeType);
}

int32_t TextPickerModelStatic::GetTextPickerRangeType(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_RETURN(textPickerPattern, 0);
    return textPickerPattern->GetRangeType();
}

const Dimension TextPickerModelStatic::ConvertFontScaleValue(const Dimension& fontSizeValue)
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
        if (!NearEqual(fontScale, 0.0f)) {
            return Dimension(fontSizeValue / fontScale);
        }
    }
    return fontSizeValue;
}

void TextPickerModelStatic::SetOnValueChangeEvent(FrameNode* frameNode,
    TextCascadeValueChangeEvent&& onValueChangeEvent)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<TextPickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnValueChangeEvent(std::move(onValueChangeEvent));
}

void TextPickerModelStatic::SetOnSelectedChangeEvent(FrameNode* frameNode,
    TextCascadeSelectedChangeEvent&& onSelectedChangeEvent)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<TextPickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSelectedChangeEvent(std::move(onSelectedChangeEvent));
}

void TextPickerModelStatic::SetEnableHapticFeedback(FrameNode* frameNode, const std::optional<bool>& valueOpt)
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

bool TextPickerModelStatic::GetEnableHapticFeedback(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, DEFAULT_ENABLE_HAPTIC_FEEDBACK);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_RETURN(textPickerPattern, DEFAULT_ENABLE_HAPTIC_FEEDBACK);
    return textPickerPattern->GetIsEnableHaptic();
}
} // namespace OHOS::Ace::NG
