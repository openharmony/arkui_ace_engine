/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components/text_field/textfield_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::NG {
constexpr uint32_t TWINKLING_INTERVAL_MS = 500;
TextFieldPattern::TextFieldPattern() : twinklingInterval_(TWINKLING_INTERVAL_MS) {}

TextFieldPattern::~TextFieldPattern() {}

void TextFieldPattern::SetCaretPosition(int32_t position) {}

const TextEditingValueNG& TextFieldPattern::GetEditingValue() const
{
    return textEditingValue_;
}

void TextFieldPattern::InitEditingValueText(std::string content)
{
    textEditingValue_.text = std::move(content);
    textEditingValue_.caretPosition = textEditingValue_.GetWideText().length();
}

void TextFieldPattern::SearchRequestKeyboard() {}

void TextFieldPattern::BeforeCreateLayoutWrapper() {}

void TextFieldPattern::InitCaretPosition(std::string content)
{
    textEditingValue_.caretPosition = static_cast<int32_t>(StringUtils::ToWstring(content).length());
}

void TextFieldPattern::OnModifyDone() {}

bool TextFieldPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    return false;
}

void TextFieldPattern::OnAreaChangedInner() {}

void TextFieldPattern::OnVisibleChange(bool isVisible) {}

void TextFieldPattern::OnDetachFromFrameNode(FrameNode*) {}

void TextFieldPattern::OnValueChanged(bool needFireChangeEvent, bool needFireSelectChangeEvent) {}

bool TextFieldPattern::OnKeyEvent(const KeyEvent& event)
{
    return false;
}

std::string TextFieldPattern::GetFontSize() const
{
    return "string";
}

Ace::FontStyle TextFieldPattern::GetItalicFontStyle() const
{
    return Ace::FontStyle::NORMAL;
}

FontWeight TextFieldPattern::GetFontWeight() const
{
    return FontWeight::NORMAL;
}

std::string TextFieldPattern::GetFontFamily() const
{
    return "string";
}

TextAlign TextFieldPattern::GetTextAlign() const
{
    return TextAlign::START;
}

std::string TextFieldPattern::GetPlaceHolder() const
{
    return "string";
}

std::string TextFieldPattern::GetPlaceholderColor() const
{
    return "string";
}

std::string TextFieldPattern::GetPlaceholderFont() const
{
    return "string";
}

void TextFieldPattern::SetSelectionFlag(int32_t selectionStart, int32_t selectionEnd) {}

void TextFieldPattern::ToJsonValue(std::unique_ptr<JsonValue>& json) const {}

void TextFieldPattern::FromJson(const std::unique_ptr<JsonValue>& json) {}

bool TextFieldPattern::OnScrollCallback(float offset, int32_t source)
{
    return true;
}
void TextFieldPattern::OnScrollEndCallback() {}

void TextFieldPattern::UpdateScrollBarOffset() {}

void TextFieldPattern::HandleBlurEvent() {}
void TextFieldPattern::HandleFocusEvent() {}

void TextFieldPattern::InitSurfaceChangedCallback() {}
void TextFieldPattern::InitSurfacePositionChangedCallback() {}

void TextFieldPattern::HandleClickEvent(GestureEvent& info) {}

void TextFieldPattern::PerformAction(TextInputAction action, bool forceCloseKeyboard) {}
void TextFieldPattern::UpdateEditingValue(const std::shared_ptr<TextEditingValue>& value, bool needFireChangeEvent) {}
void TextFieldPattern::UpdateInputFilterErrorText(const std::string& errorText) {}
int32_t TextFieldPattern::ConvertTouchOffsetToCaretPosition(const Offset& localOffset)
{
    return {};
}
bool TextFieldPattern::CloseKeyboard(bool forceClose)
{
    return {};
}
void TextFieldPattern::CloseSelectOverlay() {}
bool TextFieldPattern::IsTextArea() const
{
    return {};
}
void TextFieldPattern::CreateHandles() {}
void TextFieldPattern::StopEditing() {}
void TextFieldPattern::TextIsEmptyRect(RectF& rect) {}
void TextFieldPattern::TextAreaInputRectUpdate(RectF& rect) {}
void TextFieldPattern::UpdateRectByAlignment(RectF& rect) {}

bool TextFieldPattern::RequestCustomKeyboard()
{
    return true;
}
bool TextFieldPattern::CloseCustomKeyboard()
{
    return true;
}
OffsetF TextFieldPattern::GetDragUpperLeftCoordinates()
{
    return {};
}
void TextFieldPattern::DumpInfo() {}
void TextFieldPattern::OnColorConfigurationUpdate() {}
} // namespace OHOS::Ace::NG
