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
#include "base/utils/utils.h"
#include "core/text/text_emoji_processor.h"
#include "core/components_ng/pattern/text/typed_text.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"

namespace OHOS::Ace::NG {
namespace {
const std::string DIGIT_WHITE_LIST = "[0-9]";
const std::string DIGIT_DECIMAL_WHITE_LIST = "[0-9.]";
const std::string PHONE_WHITE_LIST = R"([0-9 \+\-\*\#\(\)])";
const std::string EMAIL_WHITE_LIST = R"([a-zA-Z0-9.!#$%&'*+/=?^_`{|}~@-])";
// when do ai analaysis, we should list the left and right of the string
constexpr static int32_t AI_TEXT_RANGE_LEFT = 50;
constexpr static int32_t AI_TEXT_RANGE_RIGHT = 50;
constexpr static int32_t EMOJI_RANGE_LEFT = 150;
constexpr static int32_t EMOJI_RANGE_RIGHT = 150;
} // namespace

std::string ContentController::PreprocessString(int32_t startIndex, int32_t endIndex, const std::string& value)
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
    auto selectValue = GetSelectedValue(startIndex, endIndex);
    bool hasInputFilter =
        property->GetInputFilter().has_value() && !property->GetInputFilter().value().empty() && !content_.empty();
    if (!hasInputFilter && property->GetTextInputType().has_value() &&
        (property->GetTextInputType().value() == TextInputType::NUMBER_DECIMAL ||
            property->GetTextInputType().value() == TextInputType::EMAIL_ADDRESS)) {
        char specialChar = property->GetTextInputType().value() == TextInputType::NUMBER_DECIMAL ? '.' : '@';
        if (content_.find(specialChar) != std::string::npos && value.find(specialChar) != std::string::npos &&
            GetSelectedValue(startIndex, endIndex).find(specialChar) == std::string::npos) {
            tmp.erase(
                std::remove_if(tmp.begin(), tmp.end(), [&specialChar](char c) { return c == specialChar; }), tmp.end());
        }
    }
    FilterValueType(tmp);
    auto wideText = GetWideText();
    auto wideTmp = StringUtils::ToWstring(tmp);
    auto maxLength = static_cast<uint32_t>(textField->GetMaxLength());
    auto curLength = static_cast<uint32_t>(wideText.length());
    auto addLength = static_cast<uint32_t>(wideTmp.length());
    auto delLength = static_cast<uint32_t>(std::abs(endIndex - startIndex));
    addLength = std::min(addLength, maxLength - curLength + delLength);
    wideTmp = TextEmojiProcessor::SubWstring(0, addLength, wideTmp); // clamp emoji
    tmp = StringUtils::ToString(wideTmp);
    return tmp;
}

bool ContentController::InsertValue(int32_t index, const std::string& value)
{
    return ReplaceSelectedValue(index, index, value);
}

bool ContentController::ReplaceSelectedValue(int32_t startIndex, int32_t endIndex, const std::string& value)
{
    FormatIndex(startIndex, endIndex);
    auto tmp = PreprocessString(startIndex, endIndex, value);
    auto wideText = GetWideText();
    auto str = content_;
    content_ = StringUtils::ToString(wideText.substr(0, startIndex)) + tmp +
               StringUtils::ToString(wideText.substr(endIndex, static_cast<int32_t>(wideText.length()) - endIndex));
    auto len = content_.length();
    FilterValue();
    insertValue_ = tmp;
    if (value.length() == 1 && content_.length() < len) {
        content_ = str;
        insertValue_ = "";
    }
    return !tmp.empty();
}

std::string ContentController::GetSelectedValue(int32_t startIndex, int32_t endIndex)
{
    FormatIndex(startIndex, endIndex);
    auto wideText = GetWideText();
    auto selectedValue = StringUtils::ToString(wideText.substr(startIndex, endIndex - startIndex));
    if (selectedValue.empty()) {
        selectedValue = StringUtils::ToString(
            TextEmojiProcessor::SubWstring(startIndex, endIndex - startIndex, wideText));
    }
    return selectedValue;
}

void ContentController::FormatIndex(int32_t& startIndex, int32_t& endIndex)
{
    startIndex = std::min(startIndex, endIndex);
    endIndex = std::max(startIndex, endIndex);
    auto wideText = GetWideText();
    startIndex = std::clamp(startIndex, 0, static_cast<int32_t>(wideText.length()));
    endIndex = std::clamp(endIndex, 0, static_cast<int32_t>(wideText.length()));
}

void ContentController::FilterTextInputStyle(bool& textChanged, std::string& result)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textField = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textField);
    auto property = textField->GetLayoutProperty<TextFieldLayoutProperty>();
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
        case TextInputType::NEW_PASSWORD: {
            textChanged |= FilterWithAscii(result);
            break;
        }
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

void ContentController::FilterValue()
{
    bool textChanged = false;
    auto result = content_;
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textField = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textField);
    if (textField->GetIsPreviewText()) {
        return;
    }

    auto property = textField->GetLayoutProperty<TextFieldLayoutProperty>();

    bool hasInputFilter =
        property->GetInputFilter().has_value() && !property->GetInputFilter().value().empty() && !content_.empty();
    if (!hasInputFilter) {
        FilterTextInputStyle(textChanged, result);
    } else {
        textChanged |= FilterWithEvent(property->GetInputFilter().value(), result);
        if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
            FilterTextInputStyle(textChanged, result);
        }
    }
    if (textChanged) {
        content_ = result;
    }
    auto maxLength =
        property->HasMaxLength() ? property->GetMaxLengthValue(Infinity<uint32_t>()) : Infinity<uint32_t>();
    auto textWidth = static_cast<int32_t>(GetWideText().length());
    if (GreatNotEqual(textWidth, maxLength)) {
        // clamp emoji
        auto subWstring = TextEmojiProcessor::SubWstring(0, maxLength, GetWideText());
        content_ = StringUtils::ToString(subWstring);
    }
}

void ContentController::FilterValueType(std::string& value)
{
    bool textChanged = false;
    auto result = value;
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textField = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textField);
    auto property = textField->GetLayoutProperty<TextFieldLayoutProperty>();

    bool hasInputFilter = property->GetInputFilter().has_value() && !property->GetInputFilter().value().empty();
    if (!hasInputFilter) {
        FilterTextInputStyle(textChanged, result);
    } else {
        textChanged = FilterWithEvent(property->GetInputFilter().value(), result) || textChanged;
        if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
            FilterTextInputStyle(textChanged, result);
        }
    }
    if (textChanged) {
        value = result;
    }
}

std::string ContentController::RemoveErrorTextFromValue(const std::string& value, const std::string& errorText)
{
    std::string result;
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
    result += value.substr(valuePtr);
    return result;
}

std::string ContentController::FilterWithRegex(const std::string& filter, std::string& result)
{
    // convert wstring for processing unicode characters
    std::wstring wFilter = StringUtils::ToWstring(filter);
    std::wstring wResult = StringUtils::ToWstring(result);
    std::wregex wFilterRegex(wFilter);
    std::wstring wErrorText = std::regex_replace(wResult, wFilterRegex, L"");
    std::string errorText = StringUtils::ToString(wErrorText);
    result = RemoveErrorTextFromValue(result, errorText);
    return errorText;
}

bool ContentController::FilterWithEmail(std::string& result)
{
    auto valueToUpdate = result;
    bool first = true;
    std::replace_if(
        result.begin(), result.end(),
        [&first](const char c) {
            if (c == '@' && !first) {
                return true;
            }
            if (c == '@') {
                first = false;
            }
            return false;
        },
        ' ');

    // remove the spaces
    result.erase(std::remove(result.begin(), result.end(), ' '), result.end());
    return result != valueToUpdate;
}

bool ContentController::FilterWithAscii(std::string& result)
{
    if (result.empty()) {
        return false;
    }
    auto valueToUpdate = result;
    bool textChange = true;
    std::string errorText;
    result.clear();
    for (char valuePtr : valueToUpdate) {
        if (isascii(valuePtr)) {
            result += valuePtr;
        } else {
            errorText += valuePtr;
        }
    }
    if (errorText.empty()) {
        textChange = false;
    } else {
        LOGI("FilterWithAscii Error text %{private}s", errorText.c_str());
    }
    return textChange;
}

bool ContentController::FilterWithDecimal(std::string& result)
{
    auto valueToUpdate = result;
    bool first = true;
    std::replace_if(
        result.begin(), result.end(),
        [&first](const char c) {
            if (c == '.' && !first) {
                return true;
            }
            if (c == '.') {
                first = false;
            }
            return false;
        },
        ' ');
    result.erase(std::remove(result.begin(), result.end(), ' '), result.end());
    return result != valueToUpdate;
}

bool ContentController::FilterWithEvent(const std::string& filter, std::string& result)
{
    auto errorValue = FilterWithRegex(filter, result);
    if (!errorValue.empty()) {
        auto pattern = pattern_.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        auto textField = DynamicCast<TextFieldPattern>(pattern);
        CHECK_NULL_RETURN(textField, false);
        auto host = textField->GetHost();
        CHECK_NULL_RETURN(host, false);
        auto eventHub = host->GetEventHub<TextFieldEventHub>();
        eventHub->FireOnInputFilterError(errorValue);
        auto textFieldAccessibilityProperty = host->GetAccessibilityProperty<TextFieldAccessibilityProperty>();
        CHECK_NULL_RETURN(textFieldAccessibilityProperty, false);
        textFieldAccessibilityProperty->SetErrorText(errorValue);
    }
    return !errorValue.empty();
}

void ContentController::erase(int32_t startIndex, int32_t length)
{
    auto wideText = GetWideText().erase(startIndex, length);
    content_ = StringUtils::ToString(wideText);
}

int32_t ContentController::Delete(int32_t startIndex, int32_t length, bool isBackward)
{
    int32_t result = TextEmojiProcessor::Delete(startIndex, length, content_, isBackward);
    if (length > 0 && result == 0) {
        // try delete whole emoji
        if (isBackward) {
            TextEmojiSubStringRange range = TextEmojiProcessor::CalSubWstringRange(
                startIndex - length, length, GetWideText(), true);
            result = TextEmojiProcessor::Delete(range.endIndex,
                length, content_, true);
        } else {
            TextEmojiSubStringRange range = TextEmojiProcessor::CalSubWstringRange(
                startIndex, length, GetWideText(), true);
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

std::string ContentController::GetValueBeforeIndex(int32_t index)
{
    return StringUtils::ToString(GetWideText().substr(0, index));
}

std::string ContentController::GetValueAfterIndex(int32_t index)
{
    return StringUtils::ToString(GetWideText().substr(index, GetWideText().length() - index));
}

std::string ContentController::GetSelectedLimitValue(int32_t& index, int32_t& startIndex)
{
    startIndex = index - AI_TEXT_RANGE_LEFT;
    int32_t endIndex = index + AI_TEXT_RANGE_RIGHT;
    FormatIndex(startIndex, endIndex);
    index = index - startIndex;
    return GetSelectedValue(startIndex, endIndex);
}

} // namespace OHOS::Ace::NG