/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/text_field/text_field_component.h"

#include "core/components/text_field/render_text_field.h"
#include "core/components/text_field/text_field_element.h"

namespace OHOS::Ace {

RefPtr<RenderNode> TextFieldComponent::CreateRenderNode()
{
    return RenderTextField::Create();
}

RefPtr<Element> TextFieldComponent::CreateElement()
{
    return AceType::MakeRefPtr<TextFieldElement>();
}

const std::string& TextFieldComponent::GetValue() const
{
    return value_;
}

void TextFieldComponent::SetValue(const std::string& value)
{
    value_ = value;
    isValueUpdated_ = true;
}

bool TextFieldComponent::IsValueUpdated() const
{
    return isValueUpdated_;
}

const std::string& TextFieldComponent::GetPlaceholder() const
{
    return placeholder_;
}

void TextFieldComponent::SetPlaceholder(const std::string& placeholder)
{
    placeholder_ = placeholder;
}

const Color& TextFieldComponent::GetPlaceholderColor() const
{
    return placeholderColor_;
}

void TextFieldComponent::SetPlaceholderColor(const Color& placeholderColor)
{
    placeholderColor_ = placeholderColor;
}

void TextFieldComponent::SetTextMaxLines(uint32_t textMaxLines)
{
    textMaxLines_ = textMaxLines;
}

TextAlign TextFieldComponent::GetTextAlign() const
{
    return textAlign_;
}

void TextFieldComponent::SetTextAlign(TextAlign textAlign)
{
    textAlign_ = textAlign;
}

uint32_t TextFieldComponent::GetTextMaxLines() const
{
    return textMaxLines_;
}

const TextStyle& TextFieldComponent::GetTextStyle() const
{
    return textStyle_;
}

void TextFieldComponent::SetTextStyle(const TextStyle& textStyle)
{
    textStyle_ = textStyle;
}

const TextStyle& TextFieldComponent::GetErrorTextStyle() const
{
    return errorTextStyle_;
}

void TextFieldComponent::SetErrorTextStyle(const TextStyle& errorTextStyle)
{
    errorTextStyle_ = errorTextStyle;
}

const Dimension& TextFieldComponent::GetErrorSpacing() const
{
    return errorSpacing_;
}

void TextFieldComponent::SetErrorSpacing(const Dimension& errorSpacing)
{
    errorSpacing_ = errorSpacing;
}

bool TextFieldComponent::GetErrorIsInner() const
{
    return errorIsInner_;
}

void TextFieldComponent::SetErrorIsInner(bool errorIsInner)
{
    errorIsInner_ = errorIsInner;
}

const Dimension& TextFieldComponent::GetErrorBorderWidth() const
{
    return errorBorderWidth_;
}

void TextFieldComponent::SetErrorBorderWidth(const Dimension& errorBorderWidth)
{
    errorBorderWidth_ = errorBorderWidth;
}

const Color& TextFieldComponent::GetErrorBorderColor() const
{
    return errorBorderColor_;
}

void TextFieldComponent::SetErrorBorderColor(const Color& errorBorderColor)
{
    errorBorderColor_ = errorBorderColor;
}

bool TextFieldComponent::NeedFade() const
{
    return needFade_;
}

void TextFieldComponent::SetNeedFade(bool needFade)
{
    needFade_ = needFade;
}

RefPtr<Decoration> TextFieldComponent::GetDecoration() const
{
    return decoration_;
}

void TextFieldComponent::SetDecoration(const RefPtr<Decoration>& decoration)
{
    decoration_ = decoration;
}

void TextFieldComponent::SetOriginBorder(const Border& originBorder)
{
    originBorder_ = originBorder;
}

const Border& TextFieldComponent::GetOriginBorder() const
{
    return originBorder_;
}

bool TextFieldComponent::ShowCursor() const
{
    return showCursor_;
}

void TextFieldComponent::SetShowCursor(bool show)
{
    showCursor_ = show;
}

bool TextFieldComponent::NeedObscure() const
{
    return obscure_;
}

void TextFieldComponent::SetObscure(bool obscure)
{
    obscure_ = obscure;
}

bool TextFieldComponent::IsEnabled() const
{
    return enabled_;
}

void TextFieldComponent::SetEnabled(bool enable)
{
    enabled_ = enable;
}

TextInputType TextFieldComponent::GetTextInputType() const
{
    return keyboard_;
}

void TextFieldComponent::SetTextInputType(TextInputType type)
{
    keyboard_ = type;
}

TextInputAction TextFieldComponent::GetAction() const
{
    return action_;
}

void TextFieldComponent::SetAction(TextInputAction action)
{
    action_ = action;
}

void TextFieldComponent::SetCursorColor(const Color& color)
{
    cursorColor_ = color;
    cursorColorIsSet_ = true;
}

const Color& TextFieldComponent::GetCursorColor()
{
    return cursorColor_;
}

void TextFieldComponent::SetCursorRadius(const Dimension& radius)
{
    cursorRadius_ = radius;
}

const Dimension& TextFieldComponent::GetCursorRadius() const
{
    return cursorRadius_;
}

bool TextFieldComponent::IsCursorColorSet() const
{
    return cursorColorIsSet_;
}

const std::string& TextFieldComponent::GetActionLabel() const
{
    return actionLabel_;
}

void TextFieldComponent::SetActionLabel(const std::string& actionLabel)
{
    actionLabel_ = actionLabel;
}

uint32_t TextFieldComponent::GetMaxLength() const
{
    return maxLength_;
}

void TextFieldComponent::SetMaxLength(uint32_t maxLength)
{
    maxLength_ = maxLength;
    lengthLimited_ = true;
}

bool TextFieldComponent::IsTextLengthLimited() const
{
    return lengthLimited_;
}

const Dimension& TextFieldComponent::GetHeight() const
{
    return height_;
}

void TextFieldComponent::SetHeight(const Dimension& height)
{
    height_ = height;
}

bool TextFieldComponent::GetAutoFocus() const
{
    return autoFocus_;
}

void TextFieldComponent::SetAutoFocus(bool autoFocus)
{
    autoFocus_ = autoFocus;
}

bool TextFieldComponent::IsExtend() const
{
    return extend_;
}

void TextFieldComponent::SetExtend(bool extend)
{
    extend_ = extend;
}

bool TextFieldComponent::ShowEllipsis() const
{
    return showEllipsis_;
}

void TextFieldComponent::SetShowEllipsis(bool showEllipsis)
{
    showEllipsis_ = showEllipsis;
}

const std::string& TextFieldComponent::GetIconImage() const
{
    return iconImage_;
}

void TextFieldComponent::SetIconImage(const std::string& iconImage)
{
    iconImage_ = iconImage;
}

const std::string& TextFieldComponent::GetShowIconImage() const
{
    return showImage_;
}

void TextFieldComponent::SetShowIconImage(const std::string& showImage)
{
    showImage_ = showImage;
}

const std::string& TextFieldComponent::GetHideIconImage() const
{
    return hideImage_;
}

void TextFieldComponent::SetHideIconImage(const std::string& hideImage)
{
    hideImage_ = hideImage;
}

const Dimension& TextFieldComponent::GetIconSize() const
{
    return iconSize_;
}

void TextFieldComponent::SetIconSize(const Dimension& iconSize)
{
    iconSize_ = iconSize;
}

const Dimension& TextFieldComponent::GetIconHotZoneSize() const
{
    return iconHotZoneSize_;
}

void TextFieldComponent::SetIconHotZoneSize(const Dimension& iconHotZoneSize)
{
    iconHotZoneSize_ = iconHotZoneSize;
}

const EventMarker& TextFieldComponent::GetOnTextChange() const
{
    return onTextChange_;
}

void TextFieldComponent::SetOnTextChange(const EventMarker& onTextChange)
{
    onTextChange_ = onTextChange;
}

const EventMarker& TextFieldComponent::GetOnFinishInput() const
{
    return onFinishInput_;
}

void TextFieldComponent::SetOnFinishInput(const EventMarker& onFinishInput)
{
    onFinishInput_ = onFinishInput;
}

const EventMarker& TextFieldComponent::GetOnTap() const
{
    return onTap_;
}

void TextFieldComponent::SetOnTap(const EventMarker& onTap)
{
    onTap_ = onTap;
}

const EventMarker& TextFieldComponent::GetOnLongPress() const
{
    return onLongPress_;
}

void TextFieldComponent::SetOnLongPress(const EventMarker& onLongPress)
{
    onLongPress_ = onLongPress;
}

const RefPtr<TextEditController>& TextFieldComponent::GetTextEditController() const
{
    return controller_;
}

void TextFieldComponent::SetTextEditController(const RefPtr<TextEditController>& controller)
{
    controller_ = controller;
}

const RefPtr<TextFieldController>& TextFieldComponent::GetTextFieldController() const
{
    return textFieldController_;
}

void TextFieldComponent::SetTextFieldController(const RefPtr<TextFieldController>& controller)
{
    textFieldController_ = controller;
}

void TextFieldComponent::SetFocusBgColor(const Color& focusBgColor)
{
    focusBgColor_ = focusBgColor;
}

const Color& TextFieldComponent::GetFocusBgColor()
{
    return focusBgColor_;
}

void TextFieldComponent::SetFocusPlaceholderColor(const Color& focusPlaceholderColor)
{
    focusPlaceholderColor_ = focusPlaceholderColor;
}

const Color& TextFieldComponent::GetFocusPlaceholderColor()
{
    return focusPlaceholderColor_;
}

void TextFieldComponent::SetFocusTextColor(const Color& focusTextColor)
{
    focusTextColor_ = focusTextColor;
}

const Color& TextFieldComponent::GetFocusTextColor()
{
    return focusTextColor_;
}

void TextFieldComponent::SetBgColor(const Color& bgColor)
{
    bgColor_ = bgColor;
}

const Color& TextFieldComponent::GetBgColor()
{
    return bgColor_;
}

void TextFieldComponent::SetTextColor(const Color& textColor)
{
    textColor_ = textColor;
}

const Color& TextFieldComponent::GetTextColor()
{
    return textColor_;
}

void TextFieldComponent::SetWidthReserved(const Dimension& widthReserved)
{
    widthReserved_ = widthReserved;
}

const Dimension& TextFieldComponent::GetWidthReserved() const
{
    return widthReserved_;
}

const Color& TextFieldComponent::GetSelectedColor() const
{
    return selectedColor_;
}

void TextFieldComponent::SetSelectedColor(const Color& selectedColor)
{
    selectedColor_ = selectedColor;
}

const Color& TextFieldComponent::GetHoverColor() const
{
    return hoverColor_;
}

void TextFieldComponent::SetHoverColor(const Color& hoverColor)
{
    hoverColor_ = hoverColor;
}

const Color& TextFieldComponent::GetPressColor() const
{
    return pressColor_;
}

void TextFieldComponent::SetPressColor(const Color& pressColor)
{
    pressColor_ = pressColor;
}

void TextFieldComponent::SetBlockRightShade(bool blockRightShade)
{
    blockRightShade_ = blockRightShade;
}

bool TextFieldComponent::GetBlockRightShade() const
{
    return blockRightShade_;
}

void TextFieldComponent::SetIsVisible(bool isVisible)
{
    isVisible_ = isVisible;
}

bool TextFieldComponent::IsVisible() const
{
    return isVisible_;
}

void TextFieldComponent::SetResetToStart(bool resetToStart)
{
    resetToStart_ = resetToStart;
}

bool TextFieldComponent::GetResetToStart() const
{
    return resetToStart_;
}

void TextFieldComponent::SetShowCounter(bool showCounter)
{
    showCounter_ = showCounter;
}

bool TextFieldComponent::ShowCounter() const
{
    return showCounter_;
}

void TextFieldComponent::SetCountTextStyle(const TextStyle& countTextStyle)
{
    countTextStyle_ = countTextStyle;
}

const TextStyle& TextFieldComponent::GetCountTextStyle() const
{
    return countTextStyle_;
}

void TextFieldComponent::SetOverCountStyle(const TextStyle& overCountStyle)
{
    overCountStyle_ = overCountStyle;
}

const TextStyle& TextFieldComponent::GetOverCountStyle() const
{
    return overCountStyle_;
}

void TextFieldComponent::SetCountTextStyleOuter(const TextStyle& countTextStyleOuter)
{
    countTextStyleOuter_ = countTextStyleOuter;
}

const TextStyle& TextFieldComponent::GetCountTextStyleOuter() const
{
    return countTextStyleOuter_;
}

void TextFieldComponent::SetOverCountStyleOuter(const TextStyle& overCountStyleOuter)
{
    overCountStyleOuter_ = overCountStyleOuter;
}

const TextStyle& TextFieldComponent::GetOverCountStyleOuter() const
{
    return overCountStyleOuter_;
}

void TextFieldComponent::SetInputOptions(const std::vector<Framework::InputOption>& inputOptions)
{
    inputOptions_ = inputOptions;
}

const std::vector<Framework::InputOption>& TextFieldComponent::GetInputOptions() const
{
    return inputOptions_;
}

const EventMarker& TextFieldComponent::GetOnOptionsClick() const
{
    return onOptionsClick_;
}

void TextFieldComponent::SetOnOptionsClick(const EventMarker& onOptionsClick)
{
    onOptionsClick_ = onOptionsClick;
}

const EventMarker& TextFieldComponent::GetOnTranslate() const
{
    return onTranslate_;
}

void TextFieldComponent::SetOnTranslate(const EventMarker& onTranslate)
{
    onTranslate_ = onTranslate;
}

const EventMarker& TextFieldComponent::GetOnShare() const
{
    return onShare_;
}

void TextFieldComponent::SetOnShare(const EventMarker& onShare)
{
    onShare_ = onShare;
}

const EventMarker& TextFieldComponent::GetOnSearch() const
{
    return onSearch_;
}

void TextFieldComponent::SetOnSearch(const EventMarker& onSearch)
{
    onSearch_ = onSearch;
}

} // namespace OHOS::Ace
