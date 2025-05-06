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
#include "core/components_ng/pattern/text_field/content_controller.h"

#include <algorithm>
#include <cstdint>
#include <string>

#include "base/utils/string_utils.h"
#include "base/utils/utf_helper.h"
#include "base/utils/utils.h"
#include "core/text/text_emoji_processor.h"
#include "core/components_ng/pattern/text/typed_text.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"

namespace OHOS::Ace::NG {
namespace {
const std::u16string DIGIT_WHITE_LIST = u"[0-9]";
const std::u16string DIGIT_DECIMAL_WHITE_LIST = u"[0-9.]";
const std::u16string PHONE_WHITE_LIST = uR"([0-9 \+\-\*\#\(\)])";
const std::u16string EMAIL_WHITE_LIST = uR"([a-zA-Z0-9.!#$%&'*+/=?^_`{|}~@"-])";
// when do ai analaysis, we should list the left and right of the string
constexpr static int32_t AI_TEXT_RANGE_LEFT = 50;
constexpr static int32_t AI_TEXT_RANGE_RIGHT = 50;
constexpr static int32_t EMOJI_RANGE_LEFT = 150;
constexpr static int32_t EMOJI_RANGE_RIGHT = 150;

inline std::wstring ContentToWstring(const std::u16string& str)
{
    auto utf16Len = str.length();
    std::unique_ptr<wchar_t[]> pBuf16 = std::make_unique<wchar_t[]>(utf16Len);
    wchar_t *wBuf = pBuf16.get();
    for (uint32_t i = 0; i < utf16Len; i++) {
        wBuf[i] = static_cast<wchar_t>(str[i]);
    }

    return std::wstring(wBuf, utf16Len);
}

inline std::u16string ContentToU16string(const std::wstring& str)
{
    auto utf16Len = str.length();
    std::unique_ptr<char16_t[]> pBuf16 = std::make_unique<char16_t[]>(utf16Len);
    char16_t *buf16 = pBuf16.get();
    for (uint32_t i = 0; i < utf16Len; i++) {
        buf16[i] = static_cast<char16_t>(str[i]);
    }

    return std::u16string(buf16, utf16Len);
}
} // namespace

std::u16string ContentController::PreprocessString(int32_t startIndex, int32_t endIndex, const std::u16string& value)
{
    auto tmp = value;
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, value);
    auto textField = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_RETURN(textField, value);
    if (textField->GetIsPreviewText()) {
        return tmp;
    }
    auto property = textField->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(property, value);
    auto selectValue = GetSelectedValue(startIndex, endIndex);
    bool hasInputFilter =
        property->GetInputFilter().has_value() && !property->GetInputFilter().value().empty() && !content_.empty();
    if (!hasInputFilter && property->GetTextInputType().has_value() &&
        (property->GetTextInputType().value() == TextInputType::NUMBER_DECIMAL ||
            property->GetTextInputType().value() == TextInputType::EMAIL_ADDRESS)) {
        char16_t specialChar = property->GetTextInputType().value() == TextInputType::NUMBER_DECIMAL ? u'.' : u'@';
        if (content_.find(specialChar) != std::u16string::npos && value.find(specialChar) != std::u16string::npos &&
            GetSelectedValue(startIndex, endIndex).find(specialChar) == std::u16string::npos) {
            tmp.erase(std::remove_if(tmp.begin(), tmp.end(), [&specialChar](char16_t c) { return c == specialChar; }),
                tmp.end());
        }
    }
    FilterValueType(tmp);
    auto maxLength = static_cast<uint32_t>(textField->GetMaxLength());
    auto curLength = static_cast<uint32_t>(content_.length());
    auto addLength = static_cast<uint32_t>(tmp.length());
    auto delLength = static_cast<uint32_t>(std::abs(endIndex - startIndex));
    addLength = std::min(addLength, maxLength - curLength + delLength);
    tmp = TextEmojiProcessor::SubU16string(0, addLength, tmp); // clamp emoji
    return tmp;
}

bool ContentController::InsertValue(int32_t index, const std::u16string& value)
{
    return ReplaceSelectedValue(index, index, value);
}

bool ContentController::ReplaceSelectedValue(int32_t startIndex, int32_t endIndex, const std::u16string& value)
{
    FormatIndex(startIndex, endIndex);
    auto tmp = PreprocessString(startIndex, endIndex, value);
    auto str = content_;
    endIndex = std::clamp(endIndex, 0, static_cast<int32_t>(content_.length()));
    content_ = content_.substr(0, startIndex) + tmp +
               content_.substr(endIndex, static_cast<int32_t>(content_.length()) - endIndex);
    auto len = content_.length();
    FilterValue();
    insertValue_ = tmp;
    if (value.length() == 1 && content_.length() < len) {
        content_ = str;
        insertValue_ = u"";
    }
    return !tmp.empty();
}

std::u16string ContentController::GetSelectedValue(int32_t startIndex, int32_t endIndex)
{
    FormatIndex(startIndex, endIndex);
    startIndex = std::clamp(startIndex, 0, static_cast<int32_t>(content_.length()));
    auto selectedValue = content_.substr(startIndex, endIndex - startIndex);
    if (selectedValue.empty()) {
        selectedValue = TextEmojiProcessor::SubU16string(startIndex, endIndex - startIndex, content_);
    }
    return selectedValue;
}

void ContentController::FormatIndex(int32_t& startIndex, int32_t& endIndex)
{
    startIndex = std::min(startIndex, endIndex);
    endIndex = std::max(startIndex, endIndex);
    startIndex = std::clamp(startIndex, 0, static_cast<int32_t>(content_.length()));
    endIndex = std::clamp(endIndex, 0, static_cast<int32_t>(content_.length()));
}

void ContentController::FilterTextInputStyle(bool& textChanged, std::u16string& result)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textField = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textField);
    auto property = textField->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(property);
    if (!property->GetTextInputType().has_value()) {
        return;
    }
    switch (property->GetTextInputType().value()) {
        case TextInputType::NUMBER: {
            textChanged |= FilterWithEvent(DIGIT_WHITE_LIST, result);
            break;
        }
        case TextInputType::PHONE: {
            textChanged |= FilterWithEvent(PHONE_WHITE_LIST, result);
            break;
        }
        case TextInputType::EMAIL_ADDRESS: {
            textChanged |= FilterWithEvent(EMAIL_WHITE_LIST, result);
            textChanged |= FilterWithEmail(result);
            break;
        }
        case TextInputType::VISIBLE_PASSWORD:
            break;
        case TextInputType::NEW_PASSWORD:
            break;
        case TextInputType::NUMBER_PASSWORD: {
            textChanged |= FilterWithEvent(DIGIT_WHITE_LIST, result);
            break;
        }
        case TextInputType::SCREEN_LOCK_PASSWORD: {
            textChanged |= FilterWithAscii(result);
            break;
        }
        case TextInputType::NUMBER_DECIMAL: {
            textChanged |= FilterWithEvent(DIGIT_DECIMAL_WHITE_LIST, result);
            textChanged |= FilterWithDecimal(result);
            break;
        }
        default: {
            break;
        }
    }
}

bool ContentController::FilterValue()
{
    bool textChanged = false;
    auto result = content_;
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto textField = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_RETURN(textField, false);
    if (textField->GetIsPreviewText()) {
        return false;
    }

    auto property = textField->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(property, false);

    bool hasInputFilter =
        property->GetInputFilter().has_value() && !property->GetInputFilter().value().empty() && !content_.empty();
    if (!hasInputFilter) {
        FilterTextInputStyle(textChanged, result);
    } else {
        textChanged |= FilterWithEvent(StringUtils::Str8ToStr16(property->GetInputFilter().value()), result);
        if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
            FilterTextInputStyle(textChanged, result);
        }
    }
    if (textChanged) {
        content_ = result;
    }
    auto maxLength =
        property->HasMaxLength() ? property->GetMaxLengthValue(Infinity<uint32_t>()) : Infinity<uint32_t>();
    auto textWidth = static_cast<int32_t>(content_.length());
    if (GreatNotEqual(textWidth, maxLength)) {
        // clamp emoji
        content_ = TextEmojiProcessor::SubU16string(0, maxLength, content_);
        return true;
    }
    return textChanged;
}

void ContentController::FilterValueType(std::u16string& value)
{
    bool textChanged = false;
    auto result = value;
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textField = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textField);
    auto property = textField->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(property);

    bool hasInputFilter = property->GetInputFilter().has_value() && !property->GetInputFilter().value().empty();
    if (!hasInputFilter) {
        FilterTextInputStyle(textChanged, result);
    } else {
        textChanged = FilterWithEvent(StringUtils::Str8ToStr16(property->GetInputFilter().value()), result) ||
            textChanged;
        if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
            FilterTextInputStyle(textChanged, result);
        }
    }
    if (textChanged) {
        value = result;
    }
}

std::u16string ContentController::RemoveErrorTextFromValue(const std::u16string& value, const std::u16string& errorText)
{
    std::u16string result;
    int32_t valuePtr = 0;
    int32_t errorTextPtr = 0;
    auto valueSize = static_cast<int32_t>(value.length());
    auto errorTextSize = static_cast<int32_t>(errorText.length());
    while (errorTextPtr < errorTextSize) {
        while (value[valuePtr] != errorText[errorTextPtr] && valuePtr < valueSize) {
            result += value[valuePtr];
            valuePtr++;
        }
        // no more text left to remove in value
        if (valuePtr >= valueSize) {
            return result;
        }
        // increase both value ptr and error text ptr if char in value is removed
        valuePtr++;
        errorTextPtr++;
    }
    valuePtr = std::clamp(valuePtr, 0, static_cast<int32_t>(value.length()));
    result += value.substr(valuePtr);
    return result;
}

std::u16string ContentController::FilterWithRegex(const std::u16string& filter, std::u16string& result)
{
    // convert wstring for processing unicode characters
    std::wstring wFilter = ContentToWstring(filter);
    std::wstring wResult = ContentToWstring(result);
    std::wregex wFilterRegex(wFilter);
    std::wstring wErrorText = std::regex_replace(wResult, wFilterRegex, L"");
    std::u16string errorText = ContentToU16string(wErrorText);
    result = RemoveErrorTextFromValue(result, errorText);
    return errorText;
}

bool ContentController::FilterWithEmail(std::u16string& result)
{
    auto valueToUpdate = result;
    bool first = true;
    std::replace_if(
        result.begin(), result.end(),
        [&first](const char16_t c) {
            if (c == u'@' && !first) {
                return true;
            }
            if (c == u'@') {
                first = false;
            }
            return false;
        },
        u' ');

    // remove the spaces
    result.erase(std::remove(result.begin(), result.end(), u' '), result.end());
    return result != valueToUpdate;
}

bool ContentController::FilterWithAscii(std::u16string& result)
{
    if (result.empty()) {
        return false;
    }
    auto valueToUpdate = result;
    bool textChange = true;
    std::u16string errorText;
    result.clear();
    for (char16_t valuePtr : valueToUpdate) {
        if (isascii(valuePtr)) {
            result += valuePtr;
        } else {
            errorText += valuePtr;
        }
    }
    if (errorText.empty()) {
        textChange = false;
    } else {
        LOGI("FilterWithAscii Error text size %{public}zu", UtfUtils::Str16DebugToStr8(errorText).size());
    }
    return textChange;
}

bool ContentController::FilterWithDecimal(std::u16string& result)
{
    auto valueToUpdate = result;
    bool first = true;
    std::replace_if(
        result.begin(), result.end(),
        [&first](const char16_t c) {
            if (c == u'.' && !first) {
                return true;
            }
            if (c == u'.') {
                first = false;
            }
            return false;
        },
        u' ');
    result.erase(std::remove(result.begin(), result.end(), u' '), result.end());
    return result != valueToUpdate;
}

bool ContentController::FilterWithEvent(const std::u16string& filter, std::u16string& result)
{
    auto errorValue = FilterWithRegex(filter, result);
    if (!errorValue.empty()) {
        auto pattern = pattern_.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        auto textField = DynamicCast<TextFieldPattern>(pattern);
        CHECK_NULL_RETURN(textField, false);
        auto host = textField->GetHost();
        CHECK_NULL_RETURN(host, false);
        auto eventHub = host->GetOrCreateEventHub<TextFieldEventHub>();
        CHECK_NULL_RETURN(eventHub, false);
        eventHub->FireOnInputFilterError(errorValue);
        auto textFieldAccessibilityProperty = host->GetAccessibilityProperty<TextFieldAccessibilityProperty>();
        CHECK_NULL_RETURN(textFieldAccessibilityProperty, false);
        textFieldAccessibilityProperty->SetErrorText(UtfUtils::Str16DebugToStr8(errorValue));
    }
    return !errorValue.empty();
}

void ContentController::erase(int32_t startIndex, int32_t length)
{
    if (startIndex < 0 || startIndex >= static_cast<int32_t>(content_.length())) {
        return;
    }
    content_.erase(startIndex, length);
}

int32_t ContentController::Delete(int32_t startIndex, int32_t length, bool isBackward)
{
    int32_t result = TextEmojiProcessor::Delete(startIndex, length, content_, isBackward);
    if (length > 0 && result == 0) {
        // try delete whole emoji
        if (isBackward) {
            TextEmojiSubStringRange range = TextEmojiProcessor::CalSubU16stringRange(
                startIndex - length, length, content_, true, true);
            result = TextEmojiProcessor::Delete(range.endIndex,
                length, content_, true);
        } else {
            TextEmojiSubStringRange range = TextEmojiProcessor::CalSubU16stringRange(
                startIndex, length, content_, true, true);
            result = TextEmojiProcessor::Delete(range.startIndex,
                length, content_, true);
        }
    }
    return result;
}

int32_t ContentController::GetDeleteLength(int32_t startIndex, int32_t length, bool isBackward)
{
    auto content = content_;
    return TextEmojiProcessor::Delete(startIndex, length, content, isBackward);
}

bool ContentController::IsIndexBeforeOrInEmoji(int32_t index)
{
    int32_t startIndex = index - EMOJI_RANGE_LEFT;
    int32_t endIndex = index + EMOJI_RANGE_RIGHT;
    FormatIndex(startIndex, endIndex);
    index = index - startIndex;
    return TextEmojiProcessor::IsIndexBeforeOrInEmoji(index, GetSelectedValue(startIndex, endIndex));
}

std::u16string ContentController::GetValueBeforeIndex(int32_t index)
{
    index = std::clamp(index, 0, static_cast<int32_t>(content_.length()));
    return content_.substr(0, index);
}

std::u16string ContentController::GetValueAfterIndex(int32_t index)
{
    index = std::clamp(index, 0, static_cast<int32_t>(content_.length()));
    return content_.substr(index, content_.length() - index);
}

std::string ContentController::GetSelectedLimitValue(int32_t& index, int32_t& startIndex)
{
    startIndex = index - AI_TEXT_RANGE_LEFT;
    int32_t endIndex = index + AI_TEXT_RANGE_RIGHT;
    FormatIndex(startIndex, endIndex);
    index = index - startIndex;
    return UtfUtils::Str16DebugToStr8(GetSelectedValue(startIndex, endIndex));
}

} // namespace OHOS::Ace::NG