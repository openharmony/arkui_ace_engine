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
#include "core/components_ng/pattern/text_field/text_field_pattern.h"

namespace OHOS::Ace::NG {
namespace {
const std::string DIGIT_WHITE_LIST = "[0-9]";
const std::string PHONE_WHITE_LIST = R"([\d\-\+\*\#]+)";
const std::string EMAIL_WHITE_LIST = "[\\w.\\@]";
const std::string URL_WHITE_LIST = "[a-zA-z]+://[^\\s]*";
} // namespace

void ContentController::InsertValue(int32_t index, const std::string& value)
{
    ReplaceSelectedValue(index, index, value);
}

void ContentController::ReplaceSelectedValue(int32_t startIndex, int32_t endIndex, const std::string& value)
{
    FormatIndex(startIndex, endIndex);
    auto wideText = GetWideText();
    content_ = StringUtils::ToString(wideText.substr(0, startIndex)) + value +
               StringUtils::ToString(wideText.substr(endIndex, static_cast<int32_t>(wideText.length()) - endIndex));
    FilterValue();
}

std::string ContentController::GetSelectedValue(int32_t startIndex, int32_t endIndex)
{
    FormatIndex(startIndex, endIndex);
    auto wideText = GetWideText();
    return StringUtils::ToString(wideText.substr(startIndex, endIndex - startIndex));
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
        case TextInputType::URL: {
            textChanged |= FilterWithEvent(URL_WHITE_LIST, result);
            break;
        }
        case TextInputType::VISIBLE_PASSWORD: {
            textChanged |= FilterWithAscii(result);
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
    auto property = textField->GetLayoutProperty<TextFieldLayoutProperty>();
    if (property->GetInputFilter().has_value() && !content_.empty()) {
        textChanged |= FilterWithEvent(property->GetInputFilter().value(), result);
    }
    FilterTextInputStyle(textChanged, result);
    if (textChanged) {
        content_ = result;
    }
    auto maxLength =
        property->HasMaxLength() ? property->GetMaxLengthValue(Infinity<uint32_t>()) : Infinity<uint32_t>();
    auto textWidth = static_cast<int32_t>(GetWideText().length());
    if (GreatNotEqual(textWidth, maxLength)) {
        content_ = StringUtils::ToString(GetWideText().substr(0, maxLength));
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
    std::regex filterRegex(filter);
    auto errorText = regex_replace(result, filterRegex, "");
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
        LOGD("Text is empty or filter is empty");
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

std::string ContentController::GetValueBeforeIndex(int32_t index)
{
    return StringUtils::ToString(GetWideText().substr(0, index));
}

std::string ContentController::GetValueAfterIndex(int32_t index)
{
    return StringUtils::ToString(GetWideText().substr(index, GetWideText().length() - index));
}

} // namespace OHOS::Ace::NG