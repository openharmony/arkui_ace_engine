/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text_field/text_field_model_ng.h"

#include <cstddef>

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/common/ime/text_edit_controller.h"
#include "core/common/ime/text_input_type.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_paint_property.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"

namespace OHOS::Ace::NG {
namespace {
const std::string DROP_TYPE_STYLED_STRING = "ApplicationDefinedType";
const std::string DROP_TYPE_PLAIN_TEXT = "general.plain-text";
const std::string DROP_TYPE_HYPERLINK = "general.hyperlink";
}
void TextFieldModelNG::CreateNode(
    const std::optional<std::u16string>& placeholder, const std::optional<std::u16string>& value, bool isTextArea)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", isTextArea ? V2::TEXTAREA_ETS_TAG : V2::TEXTINPUT_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(isTextArea ? V2::TEXTAREA_ETS_TAG : V2::TEXTINPUT_ETS_TAG, nodeId,
        []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    stack->Push(frameNode);
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    auto textfieldPaintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(textfieldPaintProperty);
    std::set<std::string> allowDropSet({ DROP_TYPE_PLAIN_TEXT, DROP_TYPE_HYPERLINK, DROP_TYPE_STYLED_STRING });
    frameNode->SetAllowDrop(allowDropSet);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    pattern->SetModifyDoneStatus(false);
    pattern->ResetContextAttr();
    auto textValue = pattern->GetTextUtf16Value();
    if (value.has_value() && value.value() != textValue) {
        auto changed = pattern->InitValueText(value.value());
        pattern->SetTextChangedAtCreation(changed);
    }
    if (!pattern->HasOperationRecords()) {
        pattern->UpdateEditingValueToRecord(); // record initial status
    }
    textFieldLayoutProperty->UpdatePlaceholder(placeholder.value_or(u""));
    if (!isTextArea) {
        textFieldLayoutProperty->UpdateMaxLines(1);
        textFieldLayoutProperty->UpdatePlaceholderMaxLines(1);
        pattern->SetTextInputFlag(true);
    } else {
        textFieldLayoutProperty->UpdatePlaceholderMaxLines(Infinity<uint32_t>());
    }
    pattern->SetTextFieldController(AceType::MakeRefPtr<TextFieldController>());
    pattern->GetTextFieldController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(pattern)));
    pattern->SetTextEditController(AceType::MakeRefPtr<TextEditController>());
    pattern->InitSurfaceChangedCallback();
    pattern->RegisterWindowSizeCallback();
    pattern->InitSurfacePositionChangedCallback();
    pattern->InitTheme();
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto colorMode = pipeline->GetColorMode();
    pattern->SetOriginCursorColor(colorMode == ColorMode::DARK ? Color(0x4DFFFFFF) : Color(0x4D000000));
    if (pipeline->GetHasPreviewTextOption()) {
        pattern->SetSupportPreviewText(pipeline->GetSupportPreviewText());
    }
    auto textFieldTheme = pattern->GetTheme();
    CHECK_NULL_VOID(textFieldTheme);
    textfieldPaintProperty->UpdatePressBgColor(textFieldTheme->GetPressColor());
    textfieldPaintProperty->UpdateHoverBgColor(textFieldTheme->GetHoverColor());
    pattern->SetHoverPressBgColorEnabled(textFieldTheme->GetHoverAndPressBgColorEnabled());
    textfieldPaintProperty->UpdateCursorColor(textFieldTheme->GetCursorColor());
    CaretStyle caretStyle;
    caretStyle.caretWidth = textFieldTheme->GetCursorWidth();
    SetCaretStyle(caretStyle);
    AddDragFrameNodeToManager();
    if (frameNode->IsFirstBuilding()) {
        auto draggable = pipeline->GetDraggable<TextFieldTheme>();
        SetDraggable(draggable);
        auto gestureHub = frameNode->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        gestureHub->SetTextDraggable(true);
    }
}

RefPtr<FrameNode> TextFieldModelNG::CreateFrameNode(int32_t nodeId, const std::optional<std::u16string>& placeholder,
    const std::optional<std::u16string>& value, bool isTextArea)
{
    auto frameNode = FrameNode::CreateFrameNode(
        isTextArea ? V2::TEXTAREA_ETS_TAG : V2::TEXTINPUT_ETS_TAG, nodeId, AceType::MakeRefPtr<TextFieldPattern>());
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(textFieldLayoutProperty, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    pattern->SetModifyDoneStatus(false);
    auto textValue = pattern->GetTextUtf16Value();
    if (value.has_value() && value.value() != textValue) {
        pattern->InitEditingValueText(value.value());
    }
    if (!pattern->HasOperationRecords()) {
        pattern->UpdateEditingValueToRecord(); // record initial status
    }
    textFieldLayoutProperty->UpdatePlaceholder(placeholder.value_or(u""));
    if (!isTextArea) {
        textFieldLayoutProperty->UpdateMaxLines(1);
        textFieldLayoutProperty->UpdatePlaceholderMaxLines(1);
        pattern->SetTextInputFlag(true);
    } else {
        textFieldLayoutProperty->UpdatePlaceholderMaxLines(Infinity<uint32_t>());
    }
    pattern->SetTextFieldController(AceType::MakeRefPtr<TextFieldController>());
    pattern->GetTextFieldController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(pattern)));
    pattern->SetTextEditController(AceType::MakeRefPtr<TextEditController>());
    pattern->InitSurfaceChangedCallback();
    pattern->InitSurfacePositionChangedCallback();
    pattern->RegisterWindowSizeCallback();
    pattern->InitTheme();
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    if (pipeline->GetHasPreviewTextOption()) {
        pattern->SetSupportPreviewText(pipeline->GetSupportPreviewText());
    }
    ProcessDefaultStyleAndBehaviors(frameNode);
    return frameNode;
}

void TextFieldModelNG::SetDraggable(bool draggable)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    frameNode->SetDraggable(draggable);
}

void TextFieldModelNG::SetShowUnderline(bool showUnderLine)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ShowUnderline, showUnderLine);
}

void TextFieldModelNG::SetFontFeature(const FONT_FEATURES_LIST& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, FontFeature, value);
}

void TextFieldModelNG::SetFontFeature(FrameNode* frameNode, const FONT_FEATURES_LIST& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, FontFeature, value, frameNode);
}

void TextFieldModelNG::SetAutoWidth(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, WidthAuto, true, frameNode);
    ViewAbstract::ClearWidthOrHeight(frameNode, true);
}

void TextFieldModelNG::SetWidth(FrameNode* frameNode, const std::string& value)
{
    if (value == "auto") {
        SetAutoWidth(frameNode);
        return;
    }
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, WidthAuto, false, frameNode);
    CalcDimension result;
    StringUtils::StringToCalcDimensionNG(value, result, false, DimensionUnit::VP);
    ViewAbstract::SetWidth(frameNode, NG::CalcLength(result));
}

void TextFieldModelNG::ClearWidth(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, WidthAuto, false, frameNode);
    ViewAbstract::ClearWidthOrHeight(frameNode, true);
}

void TextFieldModelNG::SetUserUnderlineColor(UserUnderlineColor userColor)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetUserUnderlineColor(userColor);
}

void TextFieldModelNG::SetNormalUnderlineColor(const Color& normalColor)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNormalUnderlineColor(normalColor);
}

void TextFieldModelNG::ProcessDefaultStyleAndBehaviors(const RefPtr<FrameNode>& frameNode)
{
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>(frameNode->GetThemeScopeId());
    CHECK_NULL_VOID(textFieldTheme);
    auto textfieldPaintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(textfieldPaintProperty);
    std::set<std::string> allowDropSet({ DROP_TYPE_PLAIN_TEXT, DROP_TYPE_HYPERLINK, DROP_TYPE_STYLED_STRING });
    frameNode->SetAllowDrop(allowDropSet);
    textfieldPaintProperty->UpdatePressBgColor(textFieldTheme->GetPressColor());
    textfieldPaintProperty->UpdateHoverBgColor(textFieldTheme->GetHoverColor());
    auto renderContext = frameNode->GetRenderContext();
    renderContext->UpdateBackgroundColor(textFieldTheme->GetBgColor());
    auto radius = textFieldTheme->GetBorderRadius();
    textfieldPaintProperty->UpdateCursorColor(textFieldTheme->GetCursorColor());
    BorderRadiusProperty borderRadius { radius.GetX(), radius.GetY(), radius.GetY(), radius.GetX() };
    renderContext->UpdateBorderRadius(borderRadius);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->AddTextFieldDragFrameNode(frameNode->GetId(), AceType::WeakClaim(AceType::RawPtr(frameNode)));
    PaddingProperty paddings;
    auto themePadding = textFieldTheme->GetPadding();
    paddings.top = NG::CalcLength(themePadding.Top().ConvertToPx());
    paddings.bottom = NG::CalcLength(themePadding.Bottom().ConvertToPx());
    paddings.left = NG::CalcLength(themePadding.Left().ConvertToPx());
    paddings.right = NG::CalcLength(themePadding.Right().ConvertToPx());
    auto layoutProperty = frameNode->GetLayoutProperty<LayoutProperty>();
    layoutProperty->UpdatePadding(paddings);
    if (frameNode->IsFirstBuilding()) {
        auto draggable = pipeline->GetDraggable<TextFieldTheme>();
        frameNode->SetDraggable(draggable);
        auto gestureHub = frameNode->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        gestureHub->SetTextDraggable(true);
    }
}

RefPtr<TextFieldControllerBase> TextFieldModelNG::CreateTextInput(
    const std::optional<std::u16string>& placeholder, const std::optional<std::u16string>& value)
{
    CreateNode(placeholder, value, false);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    auto focusHub = pattern->GetFocusHub();
    CHECK_NULL_RETURN(focusHub, nullptr);
    focusHub->SetFocusType(FocusType::NODE);
    focusHub->SetFocusStyleType(FocusStyleType::CUSTOM_REGION);
    return pattern->GetTextFieldController();
};

RefPtr<TextFieldControllerBase> TextFieldModelNG::CreateTextArea(
    const std::optional<std::u16string>& placeholder, const std::optional<std::u16string>& value)
{
    CreateNode(placeholder, value, true);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetTextFieldController();
}

void TextFieldModelNG::SetWidthAuto(bool isAuto)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, WidthAuto, isAuto);
}

void TextFieldModelNG::RequestKeyboardOnFocus(bool needToRequest)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    pattern->SetNeedToRequestKeyboardOnFocus(needToRequest);
}

void TextFieldModelNG::SetType(TextInputType value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    if (layoutProperty->HasTextInputType() && layoutProperty->GetTextInputTypeValue() != value) {
        layoutProperty->UpdateTypeChanged(true);
        auto pattern = frameNode->GetPattern<TextFieldPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetIsFilterChanged(true);
    }
    if (layoutProperty) {
        layoutProperty->UpdateTextInputType(value);
    }
}

void TextFieldModelNG::SetPlaceholderColor(const Color& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PlaceholderTextColor, value);
    ACE_UPDATE_PAINT_PROPERTY(TextFieldPaintProperty, PlaceholderColorFlagByUser, true);
}

void TextFieldModelNG::ResetPlaceholderColor()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetPlaceholderFontStyle()) {
        layoutProperty->GetPlaceholderFontStyle()->ResetTextColor();
    }
    ACE_RESET_PAINT_PROPERTY(TextFieldPaintProperty, PlaceholderColorFlagByUser);
}

void TextFieldModelNG::SetContentType(const TextContentType& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->HasTextContentType() && layoutProperty->GetTextContentTypeValue() != value) {
        layoutProperty->UpdateTextContentTypeChanged(true);
    }
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextContentType, value);
}

void TextFieldModelNG::SetPlaceholderFont(const Font& value)
{
    if (value.fontSize.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PlaceholderFontSize, value.fontSize.value());
    }
    if (value.fontStyle) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PlaceholderItalicFontStyle, value.fontStyle.value());
    }
    if (value.fontWeight) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PlaceholderFontWeight, value.fontWeight.value());
    }
    if (!value.fontFamilies.empty()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PlaceholderFontFamily, value.fontFamilies);
    }
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PreferredPlaceholderLineHeightNeedToUpdate, true);
}

void TextFieldModelNG::SetEnterKeyType(TextInputAction value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    if (value == TextInputAction::UNSPECIFIED) {
        value = pattern->IsTextArea() ? TextInputAction::NEW_LINE : TextInputAction::DONE;
    }
    pattern->UpdateTextInputAction(value);
}

void TextFieldModelNG::SetCapitalizationMode(AutoCapitalizationMode value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateAutoCapitalizationMode(value);
}

void TextFieldModelNG::SetCaretColor(const Color& value)
{
    ACE_UPDATE_PAINT_PROPERTY(TextFieldPaintProperty, CursorColor, value);
    ACE_UPDATE_PAINT_PROPERTY(TextFieldPaintProperty, CaretColorFlagByUser, true);
}

void TextFieldModelNG::ResetCaretColor()
{
    ACE_RESET_PAINT_PROPERTY(TextFieldPaintProperty, CursorColor);
    ACE_RESET_PAINT_PROPERTY(TextFieldPaintProperty, CaretColorFlagByUser);
}

void TextFieldModelNG::SetCaretStyle(const CaretStyle& value)
{
    if (value.caretWidth.has_value()) {
        ACE_UPDATE_PAINT_PROPERTY(TextFieldPaintProperty, CursorWidth, value.caretWidth.value());
    }
}

void TextFieldModelNG::SetCaretPosition(const int32_t& value)
{
    auto frameNode = ViewStackProcessor ::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    pattern->SetCaretPosition(value);
}

void TextFieldModelNG::SetSelectedBackgroundColor(const Color& value)
{
    ACE_UPDATE_PAINT_PROPERTY(TextFieldPaintProperty, SelectedBackgroundColor, value);
}

void TextFieldModelNG::SetTextAlign(TextAlign value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    TextAlign newValue = value;
    if (!pattern->IsTextArea() && newValue == TextAlign::JUSTIFY) {
        newValue = TextAlign::START;
    }
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    if (layoutProperty->GetTextAlignValue(TextAlign::START) != newValue) {
        layoutProperty->UpdateTextAlignChanged(true);
    }
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextAlign, newValue);
}

void TextFieldModelNG::SetLineBreakStrategy(LineBreakStrategy value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, LineBreakStrategy, value);
}

void TextFieldModelNG::SetMaxLength(uint32_t value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    uint32_t preMaxLength = GetMaxLength(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, MaxLength, value, frameNode);
    if (preMaxLength != value) {
        auto pattern = frameNode->GetPattern<TextFieldPattern>();
        CHECK_NULL_VOID(pattern);
        CHECK_NULL_VOID(pattern->HasFocus());
        pattern->UpdateShowCountBorderStyle();
    }
}

void TextFieldModelNG::ResetMaxLength()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    if (textFieldLayoutProperty) {
        textFieldLayoutProperty->ResetMaxLength();
    }
}
void TextFieldModelNG::SetMaxLines(uint32_t value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, MaxLines, value);
}
void TextFieldModelNG::SetFontSize(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, FontSize, value);
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PreferredTextLineHeightNeedToUpdate, true);
}
void TextFieldModelNG::SetFontWeight(FontWeight value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, FontWeight, value);
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PreferredTextLineHeightNeedToUpdate, true);
}
void TextFieldModelNG::SetTextColor(const Color& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextColor, value);
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColor, value);
    ACE_RESET_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy);
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColorFlag, true);
    ACE_UPDATE_PAINT_PROPERTY(TextFieldPaintProperty, TextColorFlagByUser, value);
}
void TextFieldModelNG::ResetTextColor()
{
    ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(TextFieldLayoutProperty, TextColor, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_RESET_PAINT_PROPERTY_WITH_FLAG(TextFieldPaintProperty, TextColorFlagByUser, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_RESET_RENDER_CONTEXT(RenderContext, ForegroundColor);
    ACE_RESET_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy);
    ACE_RESET_RENDER_CONTEXT(RenderContext, ForegroundColorFlag);
}
void TextFieldModelNG::SetWordBreak(Ace::WordBreak value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, WordBreak, value);
}
void TextFieldModelNG::SetFontStyle(Ace::FontStyle value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ItalicFontStyle, value);
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PreferredTextLineHeightNeedToUpdate, true);
}
void TextFieldModelNG::SetFontFamily(const std::vector<std::string>& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, FontFamily, value);
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PreferredTextLineHeightNeedToUpdate, true);
}

void TextFieldModelNG::SetMinFontScale(const float value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, MinFontScale, value);
}

void TextFieldModelNG::SetMaxFontScale(const float value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, MaxFontScale, value);
}

void TextFieldModelNG::SetMinFontScale(FrameNode* frameNode, const float value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, MinFontScale, value, frameNode);
}

void TextFieldModelNG::SetMaxFontScale(FrameNode* frameNode, const float value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, MaxFontScale, value, frameNode);
}

void TextFieldModelNG::SetInputFilter(const std::string& value,
    const std::function<void(const std::u16string&)>&& func)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, InputFilter, value);
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnInputFilterError(std::move(func));
}

void TextFieldModelNG::SetInputStyle(InputStyle value)
{
    ACE_UPDATE_PAINT_PROPERTY(TextFieldPaintProperty, InputStyle, value);
}

void TextFieldModelNG::SetShowPasswordIcon(bool value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ShowPasswordIcon, value);
}

void TextFieldModelNG::SetShowPasswordText(bool value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ShowPasswordText, value);
}

void TextFieldModelNG::SetOnEditChanged(std::function<void(bool)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnEditChanged(std::move(func));
}

void TextFieldModelNG::SetOnSubmit(std::function<void(int32_t, NG::TextFieldCommonEvent&)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSubmit(std::move(func));
}

void TextFieldModelNG::SetOnChange(std::function<void(const ChangeValueInfo&)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(func));
}

void TextFieldModelNG::SetOnTextSelectionChange(std::function<void(int32_t, int32_t)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSelectionChange(std::move(func));
}

void TextFieldModelNG::SetOnTextSelectionChange(FrameNode* frameNode, std::function<void(int32_t, int32_t)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSelectionChange(std::move(func));
}

void TextFieldModelNG::SetOnSecurityStateChange(std::function<void(bool)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSecurityStateChange(std::move(func));
}

void TextFieldModelNG::SetOnContentScroll(std::function<void(float, float)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollChangeEvent(std::move(func));
}

void TextFieldModelNG::SetOnCopy(std::function<void(const std::u16string&)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnCopy(std::move(func));
}

void TextFieldModelNG::SetOnCut(std::function<void(const std::u16string&)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnCut(std::move(func));
}

void TextFieldModelNG::SetOnPaste(std::function<void(const std::u16string&)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnPaste(std::move(func));
}

void TextFieldModelNG::SetOnPasteWithEvent(std::function<void(const std::u16string&, NG::TextCommonEvent&)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnPasteWithEvent(std::move(func));
}

void TextFieldModelNG::SetCopyOption(CopyOptions copyOption)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, CopyOptions, copyOption);
}

void TextFieldModelNG::AddDragFrameNodeToManager() const
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->AddTextFieldDragFrameNode(frameNode->GetId(), AceType::WeakClaim(frameNode));
}

void TextFieldModelNG::SetForegroundColor(const Color& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextColor, value);
}

void TextFieldModelNG::SetPasswordIcon(const PasswordIcon& passwordIcon)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    // when not call SetPasswordIcon() and api >= 13, use symbol format image, else use image format.
    pattern->SetIsPasswordSymbol(false);
    if (passwordIcon.showResult != "") {
        ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ShowPasswordSourceInfo,
            ImageSourceInfo(passwordIcon.showResult, passwordIcon.showBundleName, passwordIcon.showModuleName));
    } else {
        ImageSourceInfo showSystemSourceInfo;
        showSystemSourceInfo.SetResourceId(InternalResource::ResourceId::SHOW_PASSWORD_SVG);
        ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ShowPasswordSourceInfo, showSystemSourceInfo);
    }
    if (passwordIcon.hideResult != "") {
        ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, HidePasswordSourceInfo,
            ImageSourceInfo(passwordIcon.hideResult, passwordIcon.hideBundleName, passwordIcon.hideModuleName));
    } else {
        ImageSourceInfo hideSystemSourceInfo;
        hideSystemSourceInfo.SetResourceId(InternalResource::ResourceId::HIDE_PASSWORD_SVG);
        ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, HidePasswordSourceInfo, hideSystemSourceInfo);
    }
}

void TextFieldModelNG::SetShowUnit(std::function<void()>&& unitFunction)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    RefPtr<NG::UINode> unitNode;
    if (unitFunction) {
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        unitFunction();
        unitNode = NG::ViewStackProcessor::GetInstance()->Finish();
    }
    pattern->SetUnitNode(unitNode);
}

void TextFieldModelNG::SetShowError(const std::u16string& errorText, bool visible)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ErrorText, errorText);
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ShowErrorText, visible);
}

void TextFieldModelNG::SetShowCounter(bool value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetCounterState(false);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (value && !pattern->IsNormalInlineState() && !pattern->IsInPasswordMode() &&
        layoutProperty->HasMaxLength()) {
        pattern->AddCounterNode();
    } else {
        pattern->CleanCounterNode();
    }
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ShowCounter, value);
}

void TextFieldModelNG::SetCounterType(int32_t value)
{
    auto frameNode = ViewStackProcessor ::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, SetCounter, value);
}

void TextFieldModelNG::SetShowCounterBorder(bool value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetCounterState(false);
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ShowHighlightBorder, value);
}

void TextFieldModelNG::SetShowCounterBorder(FrameNode* frameNode, bool value)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetCounterState(false);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ShowHighlightBorder, value, frameNode);
}

void TextFieldModelNG::SetBarState(OHOS::Ace::DisplayMode value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, DisplayMode, value);
}

void TextFieldModelNG::SetMaxViewLines(uint32_t value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, MaxViewLines, value);
}

void TextFieldModelNG::SetNormalMaxViewLines(uint32_t value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, NormalMaxViewLines, value);
}

void TextFieldModelNG::SetMinLines(uint32_t value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, MinLines, value);
}

void TextFieldModelNG::SetOverflowMode(OverflowMode value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, OverflowMode, value);
}

void TextFieldModelNG::SetBackgroundColor(const Color& color, bool tmp)
{
    Color backgroundColor = color;
    if (tmp) {
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        CHECK_NULL_VOID(frameNode);
        auto pipeline = frameNode->GetContextRefPtr();
        CHECK_NULL_VOID(pipeline);
        auto themeManager = pipeline->GetThemeManager();
        CHECK_NULL_VOID(themeManager);
        auto theme = themeManager->GetTheme<TextFieldTheme>(frameNode->GetThemeScopeId());
        CHECK_NULL_VOID(theme);
        backgroundColor = theme->GetBgColor();
    }
    NG::ViewAbstract::SetBackgroundColor(backgroundColor);
    ACE_UPDATE_PAINT_PROPERTY(TextFieldPaintProperty, BackgroundColor, backgroundColor);
}

void TextFieldModelNG::ResetBackgroundColor()
{
    ACE_RESET_PAINT_PROPERTY_WITH_FLAG(TextFieldPaintProperty, BackgroundColor, PROPERTY_UPDATE_RENDER);
}

void TextFieldModelNG::SetBackgroundColor(FrameNode* frameNode, const Color& color)
{
    CHECK_NULL_VOID(frameNode);
    NG::ViewAbstract::SetBackgroundColor(frameNode, color);
    ACE_UPDATE_NODE_PAINT_PROPERTY(TextFieldPaintProperty, BackgroundColor, color, frameNode);
}

void TextFieldModelNG::ResetBackgroundColor(FrameNode* frameNode)
{
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(TextFieldPaintProperty, BackgroundColor, PROPERTY_UPDATE_RENDER, frameNode);
}

void TextFieldModelNG::SetHeight(const Dimension& value) {}

void TextFieldModelNG::SetMargin()
{
    auto frameNode = ViewStackProcessor ::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    const auto& margin = layoutProperty->GetMarginProperty();
    CHECK_NULL_VOID(margin);
    bool isRTL = layoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;

    MarginProperty userMargin;
    userMargin.top = margin->top;
    userMargin.bottom = margin->bottom;
    userMargin.left = margin->left.has_value() ? margin->left :
        (isRTL ? margin->end : margin->start);
    userMargin.right = margin->right.has_value() ? margin->right :
        (isRTL ? margin->start : margin->end);
    ACE_UPDATE_PAINT_PROPERTY(TextFieldPaintProperty, MarginByUser, userMargin);
}

void TextFieldModelNG::SetPadding(const NG::PaddingProperty& newPadding, Edge oldPadding, bool tmp)
{
    if (tmp) {
        SetDefaultPadding();
        return;
    }
    NG::ViewAbstract::SetPadding(newPadding);
    ACE_UPDATE_PAINT_PROPERTY(TextFieldPaintProperty, PaddingByUser, newPadding);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetIsInitTextRect(false);
}

void TextFieldModelNG::SetDefaultPadding()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    auto theme = pattern->GetTheme();
    CHECK_NULL_VOID(theme);
    auto themePadding = theme->GetPadding();
    PaddingProperty paddings;
    paddings.top = NG::CalcLength(themePadding.Top().ConvertToPx());
    paddings.bottom = NG::CalcLength(themePadding.Bottom().ConvertToPx());
    paddings.left = NG::CalcLength(themePadding.Left().ConvertToPx());
    paddings.right = NG::CalcLength(themePadding.Right().ConvertToPx());
    ViewAbstract::SetPadding(paddings);
    ACE_UPDATE_PAINT_PROPERTY(TextFieldPaintProperty, PaddingByUser, paddings);
    pattern->SetIsInitTextRect(false);
}

void TextFieldModelNG::SetHoverEffect(HoverEffectType hoverEffect)
{
    NG::ViewAbstract::SetHoverEffect(hoverEffect);
}

void TextFieldModelNG::SetOnWillChangeEvent(std::function<bool(const ChangeValueInfo&)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnWillChangeEvent(std::move(func));
}

void TextFieldModelNG::SetOnChangeEvent(std::function<void(const std::u16string&)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChangeEvent(std::move(func));
}

void TextFieldModelNG::SetSelectionMenuHidden(bool selectionMenuHidden)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, SelectionMenuHidden, selectionMenuHidden);
}

void TextFieldModelNG::SetCustomKeyboard(const std::function<void()>&& buildFunc, bool supportAvoidance)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    if (pattern) {
        pattern->SetCustomKeyboardOption(supportAvoidance);
        pattern->SetCustomKeyboard(std::move(buildFunc));
    }
}

void TextFieldModelNG::SetPasswordRules(const std::string& passwordRules)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PasswordRules, passwordRules);
}

void TextFieldModelNG::SetEnableAutoFill(bool enableAutoFill)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, EnableAutoFill, enableAutoFill);
}

void TextFieldModelNG::SetEnableAutoFillAnimation(bool enableAutoFillAnimation)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, EnableAutoFillAnimation, enableAutoFillAnimation);
}

void TextFieldModelNG::SetAdaptMinFontSize(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, AdaptMinFontSize, value);
}

void TextFieldModelNG::SetAdaptMaxFontSize(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, AdaptMaxFontSize, value);
}

void TextFieldModelNG::SetHeightAdaptivePolicy(TextHeightAdaptivePolicy value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, HeightAdaptivePolicy, value);
}

void TextFieldModelNG::SetCleanNodeStyle(CleanNodeStyle cleanNodeStyle)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, CleanNodeStyle, cleanNodeStyle);
}

void TextFieldModelNG::SetCancelIconSize(const CalcDimension& iconSize)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, IconSize, iconSize);
}

void TextFieldModelNG::SetAdaptMinFontSize(FrameNode* frameNode, const Dimension& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, AdaptMinFontSize, value, frameNode);
}

void TextFieldModelNG::SetAdaptMaxFontSize(FrameNode* frameNode, const Dimension& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, AdaptMaxFontSize, value, frameNode);
}

void TextFieldModelNG::SetHeightAdaptivePolicy(FrameNode* frameNode, TextHeightAdaptivePolicy value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, HeightAdaptivePolicy, value, frameNode);
}

void TextFieldModelNG::SetCanacelIconSrc(
    const std::string& iconSrc, const std::string& bundleName, const std::string& moduleName)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, IconSrc, iconSrc);
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, BundleName, bundleName);
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ModuleName, moduleName);
}

void TextFieldModelNG::SetCancelIconColor(const Color& iconColor)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, IconColor, iconColor);
}

void TextFieldModelNG::SetCancelButtonSymbol(bool isShowSymbol)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, IsShowSymbol, isShowSymbol);
}

void TextFieldModelNG::SetCancelSymbolIcon(const std::function<void(WeakPtr<NG::FrameNode>)>& iconSymbol)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->SetCancelIconSymbol(iconSymbol);
}

void TextFieldModelNG::SetIsShowCancelButton(bool isShowCancelButton)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, IsShowCancelButton, isShowCancelButton);
}

void TextFieldModelNG::SetSelectAllValue(bool isSelectAllValue)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, SelectAllValue, isSelectAllValue);
}

void TextFieldModelNG::SetKeyboardAppearance(KeyboardAppearance value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetKeyboardAppearance(value);
}

void TextFieldModelNG::SetLetterSpacing(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, LetterSpacing, value);
}

Dimension TextFieldModelNG::GetLetterSpacing(FrameNode* frameNode)
{
    Dimension value;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        TextFieldLayoutProperty, LetterSpacing, value, frameNode, value);
    return value;
}

void TextFieldModelNG::SetLineHeight(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, LineHeight, value);
}

void TextFieldModelNG::SetHalfLeading(bool value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, HalfLeading, value);
}

void TextFieldModelNG::SetLineSpacing(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, LineSpacing, value);
}

void TextFieldModelNG::SetIsOnlyBetweenLines(bool isOnlyBetweenLines)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, IsOnlyBetweenLines, isOnlyBetweenLines);
}

void TextFieldModelNG::SetTextDecoration(Ace::TextDecoration value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextDecoration, {value});
}

void TextFieldModelNG::SetTextDecorationColor(const Color& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextDecorationColor, value);
}

void TextFieldModelNG::SetTextDecorationStyle(Ace::TextDecorationStyle value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextDecorationStyle, value);
}

void TextFieldModelNG::SetBackBorderRadius()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    CHECK_NULL_VOID(renderContext->GetBorderRadius());

    bool isRTL = layoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
    auto optRadius = renderContext->GetBorderRadius();
    CHECK_NULL_VOID(optRadius);
    auto radius = optRadius.value();

    radius.radiusTopLeft = radius.radiusTopLeft.has_value() ? radius.radiusTopLeft :
        (isRTL ? radius.radiusTopEnd : radius.radiusTopStart);
    radius.radiusTopRight = radius.radiusTopRight.has_value() ? radius.radiusTopRight :
        (isRTL ? radius.radiusTopStart : radius.radiusTopEnd);
    radius.radiusBottomLeft = radius.radiusBottomLeft.has_value() ? radius.radiusBottomLeft :
        (isRTL ? radius.radiusBottomEnd : radius.radiusBottomStart);
    radius.radiusBottomRight = radius.radiusBottomRight.has_value() ? radius.radiusBottomRight :
        (isRTL ? radius.radiusBottomStart : radius.radiusBottomEnd);

    ACE_UPDATE_PAINT_PROPERTY(TextFieldPaintProperty, BorderRadiusFlagByUser, radius);
}

void TextFieldModelNG::SetBackBorder()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (renderContext->HasBorderRadius()) {
        SetBackBorderRadius();
    }
    if (renderContext->HasBorderColor()) {
        ACE_UPDATE_PAINT_PROPERTY(
            TextFieldPaintProperty, BorderColorFlagByUser, renderContext->GetBorderColor().value());
    }
    if (renderContext->HasBorderWidth()) {
        ACE_UPDATE_PAINT_PROPERTY(
            TextFieldPaintProperty, BorderWidthFlagByUser, renderContext->GetBorderWidth().value());
    }
    if (renderContext->HasBorderStyle()) {
        ACE_UPDATE_PAINT_PROPERTY(
            TextFieldPaintProperty, BorderStyleFlagByUser, renderContext->GetBorderStyle().value());
    }
}

void TextFieldModelNG::SetTextOverflow(Ace::TextOverflow value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextOverflow, value);
}

void TextFieldModelNG::SetTextIndent(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextIndent, value);
}

void TextFieldModelNG::SetTextOverflow(FrameNode* frameNode, Ace::TextOverflow value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextOverflow, value, frameNode);
}

void TextFieldModelNG::SetTextIndent(FrameNode* frameNode, const Dimension& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextIndent, value, frameNode);
}

void TextFieldModelNG::SetInputStyle(FrameNode* frameNode, InputStyle value)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(TextFieldPaintProperty, InputStyle, value, frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    if (pattern->GetTextInputFlag() && value == InputStyle::DEFAULT) {
        auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
        CHECK_NULL_VOID(textFieldLayoutProperty);
        textFieldLayoutProperty->UpdateMaxLines(1);
        textFieldLayoutProperty->UpdatePlaceholderMaxLines(1);
    }
}

void TextFieldModelNG::RequestKeyboardOnFocus(FrameNode* frameNode, bool needToRequest)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    pattern->SetNeedToRequestKeyboardOnFocus(needToRequest);
}

void TextFieldModelNG::SetBarState(FrameNode* frameNode, OHOS::Ace::DisplayMode value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, DisplayMode, value, frameNode);
}

void TextFieldModelNG::SetPasswordIcon(FrameNode* frameNode, const PasswordIcon& passwordIcon)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    // when not call SetPasswordIcon() and api >= 13, use symbol format image, else use image format.
    pattern->SetIsPasswordSymbol(false);
    if (passwordIcon.showResult != "") {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ShowPasswordSourceInfo,
            ImageSourceInfo(passwordIcon.showResult,
                passwordIcon.showBundleName, passwordIcon.showModuleName), frameNode);
    } else {
        ImageSourceInfo showSystemSourceInfo;
        showSystemSourceInfo.SetResourceId(InternalResource::ResourceId::SHOW_PASSWORD_SVG);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ShowPasswordSourceInfo,
            showSystemSourceInfo, frameNode);
    }
    if (passwordIcon.hideResult != "") {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, HidePasswordSourceInfo,
            ImageSourceInfo(passwordIcon.hideResult,
                passwordIcon.hideBundleName, passwordIcon.hideModuleName), frameNode);
    } else {
        ImageSourceInfo hideSystemSourceInfo;
        hideSystemSourceInfo.SetResourceId(InternalResource::ResourceId::HIDE_PASSWORD_SVG);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, HidePasswordSourceInfo,
            hideSystemSourceInfo, frameNode);
    }
}

void TextFieldModelNG::SetSelectedBackgroundColor(FrameNode* frameNode, const Color& value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(TextFieldPaintProperty, SelectedBackgroundColor, value, frameNode);
}

void TextFieldModelNG::SetMaxViewLines(FrameNode* frameNode, uint32_t value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, MaxViewLines, value, frameNode);
}

void TextFieldModelNG::SetNormalMaxViewLines(FrameNode* frameNode, uint32_t value)
{
    auto normalMaxViewLines = value <= 0 ? Infinity<uint32_t>() : value;
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, NormalMaxViewLines, normalMaxViewLines, frameNode);
}

void TextFieldModelNG::SetMinLines(FrameNode* frameNode, uint32_t value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, MinLines, value, frameNode);
}

void TextFieldModelNG::SetOverflowMode(FrameNode* frameNode, OverflowMode value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, OverflowMode, value, frameNode);
}

void TextFieldModelNG::SetType(FrameNode* frameNode, TextInputType value)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    if (layoutProperty->HasTextInputType() && layoutProperty->GetTextInputTypeValue() != value) {
        auto pattern = frameNode->GetPattern<TextFieldPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetIsFilterChanged(true);
        layoutProperty->UpdateTypeChanged(true);
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextInputType, value, frameNode);
}

void TextFieldModelNG::SetContentType(const FrameNode* frameNode, const TextContentType& value)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->HasTextContentType() && layoutProperty->GetTextContentTypeValue() != value) {
        layoutProperty->UpdateTextContentTypeChanged(true);
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextContentType, value, frameNode);
}

void TextFieldModelNG::SetCopyOption(FrameNode* frameNode, CopyOptions copyOption)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, CopyOptions, copyOption, frameNode);
}

void TextFieldModelNG::SetShowPasswordIcon(FrameNode* frameNode, bool value)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ShowPasswordIcon, value, frameNode);
}

void TextFieldModelNG::SetShowPassword(FrameNode* frameNode, bool value)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ShowPasswordText, value, frameNode);
}

void TextFieldModelNG::SetTextAlign(FrameNode* frameNode, TextAlign value)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    TextAlign newValue = value;
    if (!pattern->IsTextArea() && newValue == TextAlign::JUSTIFY) {
        newValue = TextAlign::START;
    }
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    if (layoutProperty->GetTextAlignValue(TextAlign::START) != newValue) {
        layoutProperty->UpdateTextAlignChanged(true);
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextAlign, newValue, frameNode);
}

void TextFieldModelNG::SetTextColor(FrameNode* frameNode, const Color& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextColor, value, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColor, value, frameNode);
    ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColorFlag, true, frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(TextFieldPaintProperty, TextColorFlagByUser, value, frameNode);
}

void TextFieldModelNG::ResetTextColor(FrameNode* frameNode)
{
    ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextColor, frameNode);
    ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColor, frameNode);
    ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColorFlag, frameNode);
    ACE_RESET_NODE_PAINT_PROPERTY(TextFieldPaintProperty, TextColorFlagByUser, frameNode);
}

void TextFieldModelNG::SetCaretPosition(FrameNode* frameNode, const int32_t& value)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    pattern->SetCaretPosition(value);
}

void TextFieldModelNG::SetFontStyle(FrameNode* frameNode, Ace::FontStyle value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ItalicFontStyle, value, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PreferredTextLineHeightNeedToUpdate, true, frameNode);
}

void TextFieldModelNG::SetMaxLength(FrameNode* frameNode, uint32_t value)
{
    CHECK_NULL_VOID(frameNode);
    uint32_t preMaxLength = GetMaxLength(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, MaxLength, value, frameNode);
    if (preMaxLength != value) {
        auto pattern = frameNode->GetPattern<TextFieldPattern>();
        CHECK_NULL_VOID(pattern);
        CHECK_NULL_VOID(pattern->HasFocus());
        pattern->UpdateShowCountBorderStyle();
    }
}

void TextFieldModelNG::ResetMaxLength(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    if (textFieldLayoutProperty) {
        textFieldLayoutProperty->ResetMaxLength();
    }
}

void TextFieldModelNG::SetCaretStyle(FrameNode* frameNode, const CaretStyle& value)
{
    if (value.caretWidth.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(TextFieldPaintProperty, CursorWidth, value.caretWidth.value(), frameNode);
    }
}

void TextFieldModelNG::SetPlaceholderColor(FrameNode* frameNode, const Color& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PlaceholderTextColor, value, frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(TextFieldPaintProperty, PlaceholderColorFlagByUser, true, frameNode);
}

void TextFieldModelNG::ResetPlaceholderColor(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetPlaceholderFontStyle()) {
        layoutProperty->GetPlaceholderFontStyle()->ResetTextColor();
    }
    ACE_RESET_NODE_PAINT_PROPERTY(TextFieldPaintProperty, PlaceholderColorFlagByUser, frameNode);
}

void TextFieldModelNG::SetFontWeight(FrameNode* frameNode, FontWeight value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, FontWeight, value, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PreferredTextLineHeightNeedToUpdate, true, frameNode);
}

void TextFieldModelNG::SetShowUnderline(FrameNode* frameNode, bool showUnderLine)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ShowUnderline, showUnderLine, frameNode);
}

void TextFieldModelNG::SetUserUnderlineColor(FrameNode* frameNode, UserUnderlineColor userColor)
{
    auto pattern = AceType::DynamicCast<TextFieldPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(pattern);
    pattern->SetUserUnderlineColor(userColor);
}

void TextFieldModelNG::SetNormalUnderlineColor(FrameNode* frameNode, const Color& normalColor)
{
    auto pattern = AceType::DynamicCast<TextFieldPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(pattern);
    pattern->SetNormalUnderlineColor(normalColor);
}

void TextFieldModelNG::SetEnterKeyType(FrameNode* frameNode, TextInputAction value)
{
    auto pattern = AceType::DynamicCast<TextFieldPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(pattern);
    if (value == TextInputAction::UNSPECIFIED) {
        value = pattern->IsTextArea() ? TextInputAction::NEW_LINE : TextInputAction::DONE;
    }
    pattern->UpdateTextInputAction(value);
}

void TextFieldModelNG::SetAutoCapitalizationMode(FrameNode* frameNode, AutoCapitalizationMode value)
{
    auto pattern = AceType::DynamicCast<TextFieldPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(pattern);
    pattern->UpdateAutoCapitalizationMode(value);
}

void TextFieldModelNG::SetFontFamily(FrameNode* frameNode, const std::vector<std::string>& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, FontFamily, value, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PreferredTextLineHeightNeedToUpdate, true, frameNode);
}

void TextFieldModelNG::SetMaxLines(FrameNode* frameNode, uint32_t value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, MaxLines, value, frameNode);
}

void TextFieldModelNG::SetPlaceholderFont(FrameNode* frameNode, const Font& value)
{
    if (value.fontSize.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            TextFieldLayoutProperty, PlaceholderFontSize, value.fontSize.value(), frameNode);
    }
    if (value.fontStyle) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            TextFieldLayoutProperty, PlaceholderItalicFontStyle, value.fontStyle.value(), frameNode);
    }
    if (value.fontWeight) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            TextFieldLayoutProperty, PlaceholderFontWeight, value.fontWeight.value(), frameNode);
    }
    if (!value.fontFamilies.empty()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PlaceholderFontFamily, value.fontFamilies, frameNode);
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TextFieldLayoutProperty, PreferredPlaceholderLineHeightNeedToUpdate, true, frameNode);
}

void TextFieldModelNG::SetFontSize(FrameNode* frameNode, const Dimension& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, FontSize, value, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PreferredTextLineHeightNeedToUpdate, true, frameNode);
}

void TextFieldModelNG::SetCaretColor(FrameNode* frameNode, const Color& value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(TextFieldPaintProperty, CursorColor, value, frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(TextFieldPaintProperty, CaretColorFlagByUser, true, frameNode);
}

void TextFieldModelNG::ResetCaretColor(FrameNode* frameNode)
{
    ACE_RESET_NODE_PAINT_PROPERTY(TextFieldPaintProperty, CursorColor, frameNode);
    ACE_RESET_NODE_PAINT_PROPERTY(TextFieldPaintProperty, CaretColorFlagByUser, frameNode);
}

void TextFieldModelNG::SetSelectionMenuHidden(FrameNode* frameNode, bool selectionMenuHidden)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, SelectionMenuHidden, selectionMenuHidden, frameNode);
}

bool TextFieldModelNG::GetSelectionMenuHidden(FrameNode* frameNode)
{
    bool value = false;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        TextFieldLayoutProperty, SelectionMenuHidden, value, frameNode, value);
    return value;
}

void TextFieldModelNG::SetPasswordRules(FrameNode* frameNode, const std::string& passwordRules)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, PasswordRules, passwordRules, frameNode);
}

void TextFieldModelNG::SetEnableAutoFill(FrameNode* frameNode, bool enableAutoFill)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, EnableAutoFill, enableAutoFill, frameNode);
}

void TextFieldModelNG::SetEnableAutoFillAnimation(FrameNode* frameNode, bool enableAutoFillAnimation)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TextFieldLayoutProperty, EnableAutoFillAnimation, enableAutoFillAnimation, frameNode);
}

void TextFieldModelNG::SetShowCounter(FrameNode* frameNode, bool value)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetCounterState(false);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ShowCounter, value, frameNode);
    if (value && !pattern->IsNormalInlineState() && !pattern->IsInPasswordMode() &&
        layoutProperty->HasMaxLength()) {
        pattern->AddCounterNode();
    } else {
        pattern->CleanCounterNode();
    }
}

void TextFieldModelNG::SetShowError(FrameNode* frameNode, const std::u16string& errorText, bool visible)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ErrorText, errorText, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, ShowErrorText, visible, frameNode);
}

void TextFieldModelNG::SetCounterType(FrameNode* frameNode, int32_t value)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, SetCounter, value, frameNode);
}

void TextFieldModelNG::SetOnWillChangeEvent(FrameNode* frameNode, std::function<bool(const ChangeValueInfo&)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnWillChangeEvent(std::move(func));
}

void TextFieldModelNG::SetOnChange(FrameNode* frameNode, std::function<void(const ChangeValueInfo&)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(func));
}

void TextFieldModelNG::SetOnContentSizeChange(FrameNode* frameNode, std::function<void(float, float)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnContentSizeChange(std::move(func));
}

void TextFieldModelNG::SetTextFieldText(FrameNode* frameNode, const std::u16string& value)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    auto textValue = pattern->GetTextUtf16Value();
    if (value != textValue) {
        pattern->InitEditingValueText(value);
    }
}

void TextFieldModelNG::SetTextFieldPlaceHolder(FrameNode* frameNode, const std::u16string& placeholder)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    textFieldLayoutProperty->UpdatePlaceholder(placeholder);
}

void TextFieldModelNG::StopTextFieldEditing(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    if (pattern) {
        pattern->StopEditing();
    }
}

void TextFieldModelNG::SetOnSubmit(FrameNode* frameNode, std::function<void(int32_t, NG::TextFieldCommonEvent&)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSubmit(std::move(func));
}

void TextFieldModelNG::SetOnCut(FrameNode* frameNode, std::function<void(const std::u16string&)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnCut(std::move(func));
}

void TextFieldModelNG::SetOnPasteWithEvent(
    FrameNode* frameNode, std::function<void(const std::u16string&, NG::TextCommonEvent&)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnPasteWithEvent(std::move(func));
}

void TextFieldModelNG::SetCleanNodeStyle(FrameNode* frameNode, CleanNodeStyle cleanNodeStyle)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, CleanNodeStyle, cleanNodeStyle, frameNode);
}

void TextFieldModelNG::SetIsShowCancelButton(FrameNode* frameNode, bool isShowCancelButton)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, IsShowCancelButton, isShowCancelButton, frameNode);
}

void TextFieldModelNG::SetCancelIconSize(FrameNode* frameNode, const CalcDimension& iconSize)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, IconSize, iconSize, frameNode);
}

void TextFieldModelNG::SetCanacelIconSrc(FrameNode* frameNode, const std::string& iconSrc)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, IconSrc, iconSrc, frameNode);
}

void TextFieldModelNG::SetCancelIconColor(FrameNode* frameNode, const Color& iconColor)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, IconColor, iconColor, frameNode);
}

void TextFieldModelNG::SetCancelButtonSymbol(FrameNode* frameNode, bool isShowSymbol)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, IsShowSymbol, isShowSymbol, frameNode);
}

void TextFieldModelNG::SetCancelSymbolIcon(FrameNode* frameNode,
    const std::function<void(WeakPtr<NG::FrameNode>)>& iconSymbol)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->SetCancelIconSymbol(iconSymbol);
}

std::u16string TextFieldModelNG::GetPlaceholderText(FrameNode* frameNode)
{
    std::u16string value;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextFieldLayoutProperty, Placeholder, value, frameNode, value);
    return value;
}

std::u16string TextFieldModelNG::GetTextFieldText(FrameNode* frameNode)
{
    std::u16string value;
    CHECK_NULL_RETURN(frameNode, value);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    return pattern->GetTextUtf16Value();
}

Color TextFieldModelNG::GetCaretColor(FrameNode* frameNode)
{
    Color value;
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(TextFieldPaintProperty, CursorColor, value, frameNode, value);
    return value;
}

Dimension TextFieldModelNG::GetCaretStyle(FrameNode* frameNode)
{
    Dimension value;
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(TextFieldPaintProperty, CursorWidth, value, frameNode, value);
    return value;
}

bool TextFieldModelNG::GetShowUnderline(FrameNode* frameNode)
{
    bool value = false;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextFieldLayoutProperty, ShowUnderline, value, frameNode, value);
    return value;
}

uint32_t TextFieldModelNG::GetMaxLength(FrameNode* frameNode)
{
    uint32_t value = 0;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextFieldLayoutProperty, MaxLength, value, frameNode, value);
    return value;
}

TextInputAction TextFieldModelNG::GetEnterKeyType(FrameNode* frameNode)
{
    TextInputAction value = TextInputAction::UNSPECIFIED;
    CHECK_NULL_RETURN(frameNode, value);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    return pattern->GetTextInputActionValue(
        frameNode->GetTag() == V2::TEXTAREA_ETS_TAG ? TextInputAction::NEW_LINE : TextInputAction::DONE);
}

Color TextFieldModelNG::GetPlaceholderColor(FrameNode* frameNode)
{
    Color value;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        TextFieldLayoutProperty, PlaceholderTextColor, value, frameNode, value);
    return value;
}

Font TextFieldModelNG::GetPlaceholderFont(FrameNode* frameNode)
{
    std::vector<std::string> fontFamilies;
    Dimension fontSize;
    Ace::FontStyle fontStyle = Ace::FontStyle::NORMAL;
    Ace::FontWeight fontWeight = Ace::FontWeight::NORMAL;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        TextFieldLayoutProperty, PlaceholderFontSize, fontSize, frameNode, Dimension());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        TextFieldLayoutProperty, PlaceholderItalicFontStyle, fontStyle, frameNode, fontStyle);
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        TextFieldLayoutProperty, PlaceholderFontWeight, fontWeight, frameNode, fontWeight);
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        TextFieldLayoutProperty, PlaceholderFontFamily, fontFamilies, frameNode, fontFamilies);
    Font value { fontWeight, fontSize, fontStyle, fontFamilies, std::nullopt, std::nullopt, std::nullopt };
    return value;
}

bool TextFieldModelNG::GetRequestKeyboardOnFocus(FrameNode* frameNode)
{
    bool value = false;
    CHECK_NULL_RETURN(frameNode, value);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    return pattern->NeedToRequestKeyboardOnFocus();
}

TextInputType TextFieldModelNG::GetType(FrameNode* frameNode)
{
    TextInputType value = TextInputType::UNSPECIFIED;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextFieldLayoutProperty, TextInputType, value, frameNode, value);
    return value;
}

Color TextFieldModelNG::GetSelectedBackgroundColor(FrameNode* frameNode)
{
    Color value;
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(
        TextFieldPaintProperty, SelectedBackgroundColor, value, frameNode, value);
    return value;
}

bool TextFieldModelNG::GetShowPasswordIcon(FrameNode* frameNode)
{
    bool value = false;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextFieldLayoutProperty, ShowPasswordIcon, value, frameNode, value);
    return value;
}

bool TextFieldModelNG::GetShowPassword(FrameNode* frameNode)
{
    bool value = false;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextFieldLayoutProperty, ShowPasswordText, value, frameNode, value);
    return value;
}

bool TextFieldModelNG::GetTextFieldEditing(FrameNode* frameNode)
{
    bool value = false;
    CHECK_NULL_RETURN(frameNode, value);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    return pattern->HasFocus();
}

bool TextFieldModelNG::GetShowCancelButton(FrameNode* frameNode)
{
    bool value = false;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        TextFieldLayoutProperty, IsShowCancelButton, value, frameNode, value);
    return value;
}

CalcDimension TextFieldModelNG::GetCancelIconSize(FrameNode* frameNode)
{
    CalcDimension value;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextFieldLayoutProperty, IconSize, value, frameNode, value);
    return value;
}

std::string TextFieldModelNG::GetCanacelIconSrc(FrameNode* frameNode)
{
    std::string value;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextFieldLayoutProperty, IconSrc, value, frameNode, value);
    return value;
}

Color TextFieldModelNG::GetCancelIconColor(FrameNode* frameNode)
{
    Color value;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextFieldLayoutProperty, IconColor, value, frameNode, value);
    return value;
}

TextAlign TextFieldModelNG::GetTextAlign(FrameNode* frameNode)
{
    TextAlign value = TextAlign::START;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextFieldLayoutProperty, TextAlign, value, frameNode, value);
    return value;
}
Color TextFieldModelNG::GetTextColor(FrameNode* frameNode)
{
    Color value;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextFieldLayoutProperty, TextColor, value, frameNode, value);
    return value;
}
Ace::FontStyle TextFieldModelNG::GetFontStyle(FrameNode* frameNode)
{
    Ace::FontStyle value = Ace::FontStyle::NORMAL;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextFieldLayoutProperty, ItalicFontStyle, value, frameNode, value);
    return value;
}
FontWeight TextFieldModelNG::GetFontWeight(FrameNode* frameNode)
{
    FontWeight value = FontWeight::NORMAL;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextFieldLayoutProperty, FontWeight, value, frameNode, value);
    return value;
}
Dimension TextFieldModelNG::GetFontSize(FrameNode* frameNode)
{
    Dimension value;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextFieldLayoutProperty, FontSize, value, frameNode, Dimension());
    return value;
}
CleanNodeStyle TextFieldModelNG::GetCleanNodeStyle(FrameNode* frameNode)
{
    CleanNodeStyle value = CleanNodeStyle::INPUT;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextFieldLayoutProperty, CleanNodeStyle, value, frameNode, value);
    return value;
}
bool TextFieldModelNG::GetShowCounter(FrameNode* frameNode)
{
    bool value = false;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextFieldLayoutProperty, ShowCounter, value, frameNode, value);
    return static_cast<int>(value);
}

uint32_t TextFieldModelNG::GetMinLines(FrameNode* frameNode)
{
    uint32_t value = false;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextFieldLayoutProperty, MinLines, value, frameNode, value);
    return value;
}

int TextFieldModelNG::GetCounterType(FrameNode* frameNode)
{
    int value = -1;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextFieldLayoutProperty, SetCounter, value, frameNode, value);
    return value;
}
bool TextFieldModelNG::GetShowCounterBorder(FrameNode* frameNode)
{
    bool value = true;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        TextFieldLayoutProperty, ShowHighlightBorder, value, frameNode, value);
    return value;
}

void TextFieldModelNG::SetTextSelection(FrameNode* frameNode, int32_t start, int32_t end)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    auto wideText = pattern->GetTextUtf16Value();
    int32_t length = static_cast<int32_t>(wideText.length());
    start = std::clamp(start, 0, length);
    end = std::clamp(end, 0, length);
    pattern->SetSelectionFlag(start, end);
}

int32_t TextFieldModelNG::GetTextSelectionIndex(FrameNode* frameNode, bool isEnd)
{
    int32_t defaultValue = 0;
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, defaultValue);
    auto selectController = pattern->GetTextSelectController();
    if (isEnd) {
        return selectController->GetEndIndex();
    }
    return selectController->GetStartIndex();
}

void TextFieldModelNG::ResetTextInputPadding(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(textFieldTheme);
    auto themePadding = textFieldTheme->GetPadding();
    PaddingProperty paddings;
    paddings.top = NG::CalcLength(themePadding.Top().ConvertToPx());
    paddings.bottom = NG::CalcLength(themePadding.Bottom().ConvertToPx());
    paddings.left = NG::CalcLength(themePadding.Left().ConvertToPx());
    paddings.right = NG::CalcLength(themePadding.Right().ConvertToPx());
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, Padding, paddings, frameNode);
}

void TextFieldModelNG::SetTextDecoration(FrameNode* frameNode, TextDecoration value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextDecoration, {value}, frameNode);
}

void TextFieldModelNG::SetTextDecorationColor(FrameNode* frameNode, const Color& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextDecorationColor, value, frameNode);
}

void TextFieldModelNG::SetTextDecorationStyle(FrameNode* frameNode, TextDecorationStyle value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, TextDecorationStyle, value, frameNode);
}

void TextFieldModelNG::SetLetterSpacing(FrameNode* frameNode, const Dimension& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, LetterSpacing, value, frameNode);
}

void TextFieldModelNG::SetLineHeight(FrameNode* frameNode, const Dimension& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, LineHeight, value, frameNode);
}

void TextFieldModelNG::SetHalfLeading(FrameNode* frameNode, const bool& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, HalfLeading, value, frameNode);
}

void TextFieldModelNG::SetLineSpacing(FrameNode* frameNode, const Dimension& value, bool isOnlyBetweenLines)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, LineSpacing, value, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TextFieldLayoutProperty, IsOnlyBetweenLines, isOnlyBetweenLines, frameNode);
}

float TextFieldModelNG::GetLineSpacing(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0.0f);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, 0.0f);
    Dimension defaultLineSpacing(0);
    auto value = layoutProperty->GetLineSpacing().value_or(defaultLineSpacing);
    return static_cast<float>(value.Value());
}

void TextFieldModelNG::TextFieldModelNG::SetWordBreak(FrameNode* frameNode, Ace::WordBreak value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, WordBreak, value, frameNode);
}

void TextFieldModelNG::SetLineBreakStrategy(FrameNode* frameNode, LineBreakStrategy value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, LineBreakStrategy, value, frameNode);
}

void TextFieldModelNG::SetSelectAllValue(FrameNode* frameNode, bool isSelectAllValue)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, SelectAllValue, isSelectAllValue, frameNode);
}

void TextFieldModelNG::SetBlurOnSubmit(FrameNode* frameNode, bool blurOnSubmit)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    return pattern->SetBlurOnSubmit(blurOnSubmit);
}

bool TextFieldModelNG::GetBlurOnSubmit(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, true);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, true);
    return pattern->GetBlurOnSubmit();
}

void TextFieldModelNG::SetKeyboardAppearance(FrameNode* frameNode, KeyboardAppearance value)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetKeyboardAppearance(value);
}

int32_t TextFieldModelNG::GetKeyboardAppearance(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, false);
    return static_cast<int32_t>(pattern->GetKeyboardAppearance());
}

void TextFieldModelNG::SetOnEditChange(FrameNode* frameNode, std::function<void(bool)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnEditChanged(std::move(func));
}

void TextFieldModelNG::SetInputFilter(FrameNode* frameNode,
    const std::string& value, const std::function<void(const std::u16string&)>& onError)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, InputFilter, value, frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnInputFilterError(onError);
}

void TextFieldModelNG::SetOnContentScroll(FrameNode* frameNode, std::function<void(float, float)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollChangeEvent(std::move(func));
}

void TextFieldModelNG::SetOnCopy(FrameNode* frameNode, std::function<void(const std::u16string&)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnCopy(std::move(func));
}

void TextFieldModelNG::SetOnEditChanged(FrameNode* frameNode, std::function<void(bool)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnEditChanged(std::move(func));
}

void TextFieldModelNG::SetCustomKeyboard(FrameNode* frameNode, FrameNode* customKeyboard, bool supportAvoidance)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    if (pattern) {
        pattern->SetCustomKeyboardWithNode(AceType::Claim<UINode>(customKeyboard));
        pattern->SetCustomKeyboardOption(supportAvoidance);
    }
}

void TextFieldModelNG::SetInputFilter(FrameNode* frameNode, const std::string& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, InputFilter, value, frameNode);
}

void TextFieldModelNG::SetInputFilterError(FrameNode* frameNode,
    const std::function<void(const std::u16string&)>& onError)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnInputFilterError(onError);
}

Ace::WordBreak TextFieldModelNG::GetWordBreak(FrameNode* frameNode)
{
    Ace::WordBreak value = Ace::WordBreak::BREAK_WORD;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextFieldLayoutProperty, WordBreak, value, frameNode, value);
    return value;
}

bool TextFieldModelNG::GetEnableAutoFill(FrameNode* frameNode)
{
    bool value = true;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextFieldLayoutProperty, EnableAutoFill, value, frameNode, value);
    return value;
}

bool TextFieldModelNG::GetEnableAutoFillAnimation(FrameNode* frameNode)
{
    bool value = true;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        TextFieldLayoutProperty, EnableAutoFillAnimation, value, frameNode, value);
    return value;
}

TextContentType TextFieldModelNG::GetContentType(FrameNode* frameNode)
{
    TextContentType value = TextContentType::UNSPECIFIED;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextFieldLayoutProperty, TextContentType, value, frameNode, value);
    return value;
}

UserUnderlineColor TextFieldModelNG::GetUnderLineColor(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, UserUnderlineColor());
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, UserUnderlineColor());
    return pattern->GetUserUnderlineColor();
}

std::string TextFieldModelNG::GetPasswordRules(FrameNode* frameNode)
{
    std::string value;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextFieldLayoutProperty, PasswordRules, value, frameNode, value);
    return value;
}

bool TextFieldModelNG::GetSelectAllValue(FrameNode* frameNode)
{
    bool value = false;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextFieldLayoutProperty, SelectAllValue, value, frameNode, value);
    return value;
}

std::string TextFieldModelNG::GetInputFilter(FrameNode* frameNode)
{
    std::string value;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextFieldLayoutProperty, InputFilter, value, frameNode, value);
    return value;
}

RefPtr<TextFieldControllerBase> TextFieldModelNG::GetOrCreateController(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    if (!pattern->GetTextFieldController()) {
        auto controller = AceType::MakeRefPtr<NG::TextFieldController>();
        pattern->SetTextFieldController(controller);
        controller->SetPattern(AceType::WeakClaim(AceType::RawPtr(pattern)));
    }
    return pattern->GetTextFieldController();
}

InputStyle TextFieldModelNG::GetInputStyle(FrameNode* frameNode)
{
    InputStyle value = InputStyle::DEFAULT;
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(TextFieldPaintProperty, InputStyle, value, frameNode, value);
    return value;
}

FONT_FEATURES_LIST TextFieldModelNG::GetFontFeature(FrameNode* frameNode)
{
    FONT_FEATURES_LIST value;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextFieldLayoutProperty, FontFeature, value, frameNode, value);
    return value;
}

Dimension TextFieldModelNG::GetAdaptMinFontSize(FrameNode* frameNode)
{
    Dimension value;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextFieldLayoutProperty, AdaptMinFontSize, value, frameNode, value);
    return value;
}

void TextFieldModelNG::SetOnWillInsertValueEvent(std::function<bool(const InsertValueInfo&)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnWillInsertValueEvent(std::move(func));
}

void TextFieldModelNG::SetOnDidInsertValueEvent(std::function<void(const InsertValueInfo&)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDidInsertValueEvent(std::move(func));
}

void TextFieldModelNG::SetOnWillDeleteEvent(std::function<bool(const DeleteValueInfo&)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnWillDeleteEvent(std::move(func));
}

void TextFieldModelNG::SetOnDidDeleteEvent(std::function<void(const DeleteValueInfo&)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDidDeleteEvent(std::move(func));
}

void TextFieldModelNG::SetSelectionMenuOptions(
    const NG::OnCreateMenuCallback&& onCreateMenuCallback, const NG::OnMenuItemClickCallback&& onMenuItemClick)
{
    auto textFieldPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    textFieldPattern->OnSelectionMenuOptionsUpdate(std::move(onCreateMenuCallback), std::move(onMenuItemClick));
}

void TextFieldModelNG::SetEnablePreviewText(bool enablePreviewText)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSupportPreviewText(enablePreviewText);
}

bool TextFieldModelNG::GetEnablePreviewText(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, false);
    return pattern->GetSupportPreviewText();
}

void TextFieldModelNG::SetEnableHapticFeedback(bool state)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetEnableHapticFeedback(state);
}

void TextFieldModelNG::SetEllipsisMode(EllipsisMode value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, EllipsisMode, value);
}

Dimension TextFieldModelNG::GetAdaptMaxFontSize(FrameNode* frameNode)
{
    Dimension value;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextFieldLayoutProperty, AdaptMaxFontSize, value, frameNode, value);
    return value;
}

Dimension TextFieldModelNG::GetLineHeight(FrameNode* frameNode)
{
    Dimension value;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextFieldLayoutProperty, LineHeight, value, frameNode, value);
    return value;
}

uint32_t TextFieldModelNG::GetMaxLines(FrameNode* frameNode)
{
    uint32_t value = 3;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextFieldLayoutProperty, MaxLines, value, frameNode, value);
    return value;
}

void TextFieldModelNG::SetPadding(FrameNode* frameNode, NG::PaddingProperty& newPadding)
{
    CHECK_NULL_VOID(frameNode);
    NG::ViewAbstract::SetPadding(frameNode, newPadding);
    ACE_UPDATE_NODE_PAINT_PROPERTY(TextFieldPaintProperty, PaddingByUser, newPadding, frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetIsInitTextRect(false);
}

RefPtr<UINode> TextFieldModelNG::GetCustomKeyboard(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetCustomKeyboard();
}

bool TextFieldModelNG::GetCustomKeyboardOption(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, false);
    return pattern->GetCustomKeyboardOption();
}

void TextFieldModelNG::SetShowKeyBoardOnFocus(FrameNode* frameNode, bool value)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetShowKeyBoardOnFocus(value);
}
bool TextFieldModelNG::GetShowKeyBoardOnFocus(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, true);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, true);
    return pattern->GetShowKeyBoardOnFocus();
}

void TextFieldModelNG::SetNumberOfLines(FrameNode* frameNode, int32_t value)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, NumberOfLines, value, frameNode);
}

int32_t TextFieldModelNG::GetNumberOfLines(FrameNode* frameNode)
{
    int32_t value = -1;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextFieldLayoutProperty, NumberOfLines, value, frameNode, value);
    return value;
}

void TextFieldModelNG::ResetNumberOfLines(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    if (textFieldLayoutProperty) {
        textFieldLayoutProperty->ResetNumberOfLines();
    }
}

void TextFieldModelNG::SetBorderWidth(FrameNode* frameNode, NG::BorderWidthProperty borderWidth)
{
    CHECK_NULL_VOID(frameNode);
    NG::ViewAbstract::SetBorderWidth(frameNode, borderWidth);
    ACE_UPDATE_NODE_PAINT_PROPERTY(TextFieldPaintProperty, BorderWidthFlagByUser, borderWidth, frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetIsInitTextRect(false);
}

void TextFieldModelNG::SetBorderRadius(FrameNode* frameNode, NG::BorderRadiusProperty borderRadius)
{
    CHECK_NULL_VOID(frameNode);
    NG::ViewAbstract::SetBorderRadius(frameNode, borderRadius);
    ACE_UPDATE_NODE_PAINT_PROPERTY(TextFieldPaintProperty, BorderRadiusFlagByUser, borderRadius, frameNode);
}

void TextFieldModelNG::SetBorderColor(FrameNode* frameNode, NG::BorderColorProperty borderColors)
{
    CHECK_NULL_VOID(frameNode);
    NG::ViewAbstract::SetBorderColor(frameNode, borderColors);
    ACE_UPDATE_NODE_PAINT_PROPERTY(TextFieldPaintProperty, BorderColorFlagByUser, borderColors, frameNode);
}

void TextFieldModelNG::SetBorderStyle(FrameNode* frameNode, NG::BorderStyleProperty borderStyles)
{
    CHECK_NULL_VOID(frameNode);
    NG::ViewAbstract::SetBorderStyle(frameNode, borderStyles);
    ACE_UPDATE_NODE_PAINT_PROPERTY(TextFieldPaintProperty, BorderStyleFlagByUser, borderStyles, frameNode);
}

void TextFieldModelNG::SetMargin(FrameNode* frameNode, NG::PaddingProperty& margin)
{
    CHECK_NULL_VOID(frameNode);
    MarginProperty userMargin;
    userMargin.top = margin.top;
    userMargin.bottom = margin.bottom;
    userMargin.left = margin.left;
    userMargin.right = margin.right;
    ACE_UPDATE_NODE_PAINT_PROPERTY(TextFieldPaintProperty, MarginByUser, userMargin, frameNode);
}

PaddingProperty TextFieldModelNG::GetMargin(FrameNode* frameNode)
{
    CalcLength defaultDimen = CalcLength(0, DimensionUnit::VP);
    NG::PaddingProperty margins;
    margins.top = std::optional<CalcLength>(defaultDimen);
    margins.right = std::optional<CalcLength>(defaultDimen);
    margins.bottom = std::optional<CalcLength>(defaultDimen);
    margins.left = std::optional<CalcLength>(defaultDimen);
    auto textfieldPaintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_RETURN(textfieldPaintProperty, margins);
    if (textfieldPaintProperty->HasMarginByUser()) {
        const auto& property = textfieldPaintProperty->GetMarginByUserValue();
        margins.top = std::optional<CalcLength>(property.top);
        margins.right = std::optional<CalcLength>(property.right);
        margins.bottom = std::optional<CalcLength>(property.bottom);
        margins.left = std::optional<CalcLength>(property.left);
    }
    return margins;
}

void TextFieldModelNG::SetOnWillInsertValueEvent(FrameNode* frameNode,
    std::function<bool(const InsertValueInfo&)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnWillInsertValueEvent(std::move(func));
}

void TextFieldModelNG::SetOnDidInsertValueEvent(FrameNode* frameNode,
    std::function<void(const InsertValueInfo&)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDidInsertValueEvent(std::move(func));
}

void TextFieldModelNG::SetOnWillDeleteEvent(FrameNode* frameNode,
    std::function<bool(const DeleteValueInfo&)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnWillDeleteEvent(std::move(func));
}

void TextFieldModelNG::SetOnDidDeleteEvent(FrameNode* frameNode,
    std::function<void(const DeleteValueInfo&)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDidDeleteEvent(std::move(func));
}

void TextFieldModelNG::OnCreateMenuCallbackUpdate(
    FrameNode* frameNode, const NG::OnCreateMenuCallback&& onCreateMenuCallback)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    textFieldPattern->OnCreateMenuCallbackUpdate(std::move(onCreateMenuCallback));
}

void TextFieldModelNG::OnMenuItemClickCallbackUpdate(
    FrameNode* frameNode, const NG::OnMenuItemClickCallback&& onMenuItemClick)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    textFieldPattern->OnMenuItemClickCallbackUpdate(std::move(onMenuItemClick));
}

void TextFieldModelNG::SetEnablePreviewText(FrameNode* frameNode, bool enablePreviewText)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSupportPreviewText(enablePreviewText);
}

PaddingProperty TextFieldModelNG::GetPadding(FrameNode* frameNode)
{
    NG::PaddingProperty paddings = NG::ViewAbstract::GetPadding(frameNode);
    auto textfieldPaintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_RETURN(textfieldPaintProperty, paddings);
    if (textfieldPaintProperty->HasPaddingByUser()) {
        const auto& property = textfieldPaintProperty->GetPaddingByUserValue();
        paddings.top = std::optional<CalcLength>(property.top);
        paddings.right = std::optional<CalcLength>(property.right);
        paddings.bottom = std::optional<CalcLength>(property.bottom);
        paddings.left = std::optional<CalcLength>(property.left);
    }
    return paddings;
}

void TextFieldModelNG::SetJSTextEditableController(FrameNode* frameNode, const RefPtr<Referenced>& controller)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetJSTextEditableController(controller);
}

RefPtr<Referenced> TextFieldModelNG::GetJSTextEditableController(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetJSTextEditableController();
}

void TextFieldModelNG::SetEnableHapticFeedback(FrameNode* frameNode, bool state)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetEnableHapticFeedback(state);
}

void TextFieldModelNG::SetEllipsisMode(FrameNode* frameNode, EllipsisMode value)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, EllipsisMode, value, frameNode);
}

void TextFieldModelNG::SetStopBackPress(bool isStopBackPress)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, StopBackPress, isStopBackPress);
}

void TextFieldModelNG::SetStopBackPress(FrameNode* frameNode, bool isStopBackPress)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, StopBackPress, isStopBackPress, frameNode);
}

void TextFieldModelNG::SetStrokeWidth(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, StrokeWidth, value);
}

Dimension TextFieldModelNG::GetStrokeWidth(FrameNode* frameNode)
{
    Dimension value;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextFieldLayoutProperty, StrokeWidth, value, frameNode, value);
    return value;
}

void TextFieldModelNG::SetStrokeColor(const Color& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, StrokeColor, value);
}

Color TextFieldModelNG::GetStrokeColor(FrameNode* frameNode)
{
    Color value;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TextFieldLayoutProperty, StrokeColor, value, frameNode, value);
    return value;
}

void TextFieldModelNG::ResetStrokeColor()
{
    ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(TextFieldLayoutProperty, StrokeColor, PROPERTY_UPDATE_MEASURE);
}

void TextFieldModelNG::SetStrokeWidth(FrameNode* frameNode, const Dimension& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, StrokeWidth, value, frameNode);
}

void TextFieldModelNG::SetStrokeColor(FrameNode* frameNode, const Color& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, StrokeColor, value, frameNode);
}

void TextFieldModelNG::ResetStrokeColor(FrameNode* frameNode)
{
    ACE_RESET_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, StrokeColor, frameNode);
}

void TextFieldModelNG::SetEnableAutoSpacing(bool enabled)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextFieldLayoutProperty, EnableAutoSpacing, enabled);
}

void TextFieldModelNG::SetEnableAutoSpacing(FrameNode* frameNode, bool enabled)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextFieldLayoutProperty, EnableAutoSpacing, enabled, frameNode);
}

bool TextFieldModelNG::GetEnableAutoSpacing(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    bool value = false;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        TextFieldLayoutProperty, EnableAutoSpacing, value, frameNode, value);
    return value;
}

void TextFieldModelNG::SetOnSecurityStateChange(FrameNode* frameNode, std::function<void(bool)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSecurityStateChange(std::move(func));
}
} // namespace OHOS::Ace::NG
