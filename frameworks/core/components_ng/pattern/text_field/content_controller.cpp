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
#include "core/common/container.h"

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
// when do ai analaysis, we should list the left and right of the string
constexpr static int32_t AI_TEXT_RANGE_LEFT = 50;
constexpr static int32_t AI_TEXT_RANGE_RIGHT = 50;
constexpr static int32_t EMOJI_RANGE_LEFT = 150;
constexpr static int32_t EMOJI_RANGE_RIGHT = 150;
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
    if (!hasInputFilter && property->GetTextInputType().has_value()) {
        tmp = TextInputFilter::PreprocessValue(
            property->GetTextInputType().value(), content_, tmp, selectValue);
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
    auto host = textField->GetHost();
    if (host) {
        ACE_UINODE_TRACE(host);
    }
    auto onError = [weak = WeakClaim(RawPtr(host))](const std::u16string& error) -> bool {
        auto host = weak.Upgrade();
        CHECK_NULL_RETURN(host, false);
        auto eventHub = host->GetEventHub<TextFieldEventHub>();
        CHECK_NULL_RETURN(eventHub, false);
        eventHub->FireOnInputFilterError(error);
        return true;
    };
    textChanged |= TextInputFilter::FilterByInputType(
        property->GetTextInputType().value(), result, onError);
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

void ContentController::FilterValue(std::u16string& value)
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
        textChanged |= FilterWithEvent(StringUtils::Str8ToStr16(property->GetInputFilter().value()), result);
        if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
            FilterTextInputStyle(textChanged, result);
        }
    }
    if (textChanged) {
        value = result;
    }
    auto maxLength =
        property->HasMaxLength() ? property->GetMaxLengthValue(Infinity<uint32_t>()) : Infinity<uint32_t>();
    auto textWidth = static_cast<int32_t>(value.length());
    if (GreatNotEqual(textWidth, maxLength)) {
        // clamp emoji
        value = TextEmojiProcessor::SubU16string(0, maxLength, value);
    }
}

bool ContentController::FilterWithEvent(const std::u16string& filter, std::u16string& result)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto textField = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_RETURN(textField, false);
    auto host = textField->GetHost();
    if (host) {
        ACE_UINODE_TRACE(host);
    }
    auto onError = [weak = WeakClaim(RawPtr(host))](const std::u16string& error) -> bool {
        auto host = weak.Upgrade();
        CHECK_NULL_RETURN(host, false);
        auto eventHub = host->GetEventHub<TextFieldEventHub>();
        CHECK_NULL_RETURN(eventHub, false);
        eventHub->FireOnInputFilterError(error);
        return true;
    };
    return TextInputFilter::FilterWithEvent(filter, result, onError);
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
