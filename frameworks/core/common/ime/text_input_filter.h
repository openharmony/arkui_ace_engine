/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_IME_TEXT_INPUT_FILTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_IME_TEXT_INPUT_FILTER_H

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <functional>
#include <memory>
#include <regex>
#include <string>

#include "base/log/log_wrapper.h"
#include "base/utils/utf_helper.h"
#include "core/common/ime/text_input_type.h"

namespace OHOS::Ace {

static inline std::wstring ContentToWstring(const std::u16string& str)
{
    auto utf16Len = str.length();
    std::unique_ptr<wchar_t[]> pBuf16 = std::make_unique<wchar_t[]>(utf16Len);
    wchar_t *wBuf = pBuf16.get();
    for (uint32_t i = 0; i < utf16Len; i++) {
        wBuf[i] = static_cast<wchar_t>(str[i]);
    }
    return std::wstring(wBuf, utf16Len);
}

static inline std::u16string ContentToU16string(const std::wstring& str)
{
    auto utf16Len = str.length();
    std::unique_ptr<char16_t[]> pBuf16 = std::make_unique<char16_t[]>(utf16Len);
    char16_t *buf16 = pBuf16.get();
    for (uint32_t i = 0; i < utf16Len; i++) {
        buf16[i] = static_cast<char16_t>(str[i]);
    }
    return std::u16string(buf16, utf16Len);
}

/**
 * @brief Pure string filtering utility extracted from ContentController.
 *
 * No Pattern/Property/Theme dependency. Shared by TextField and RichEditor.
 */
class TextInputFilter {
public:
    /**
     * @brief Filter result string by TextInputType rules.
     *
     * Modifies result in place, removing characters not allowed by the input type.
     * @param type The TextInputType to filter by.
     * @param result The string to filter (modified in place).
     * @param onError Optional error callback returning whether the error was handled.
     *                When false, the filtering result is treated as not applied.
     * @return True if text was changed and the error (if any) was handled.
     */
    static inline bool FilterByInputType(TextInputType type, std::u16string& result,
        const std::function<bool(const std::u16string&)>& onError = nullptr)
    {
        bool textChanged = false;
        switch (type) {
            case TextInputType::ONE_TIME_CODE_NUMBER:
            case TextInputType::NUMBER:
            case TextInputType::NUMBER_PASSWORD: {
                textChanged |= FilterWithEvent(DIGIT_WHITE_LIST, result, onError);
                break;
            }
            case TextInputType::PHONE: {
                textChanged |= FilterWithEvent(PHONE_WHITE_LIST, result, onError);
                break;
            }
            case TextInputType::EMAIL_ADDRESS: {
                textChanged |= FilterWithEvent(EMAIL_WHITE_LIST, result, onError);
                textChanged |= FilterWithEmail(result);
                break;
            }
            case TextInputType::VISIBLE_PASSWORD:
            case TextInputType::NEW_PASSWORD:
                break;
            case TextInputType::SCREEN_LOCK_PASSWORD: {
                textChanged |= FilterWithAscii(result);
                break;
            }
            case TextInputType::NUMBER_DECIMAL: {
                textChanged |= FilterWithEvent(DIGIT_DECIMAL_WHITE_LIST, result, onError);
                textChanged |= FilterWithDecimal(result);
                break;
            }
            default: {
                break;
            }
        }
        return textChanged;
    }

    /**
     * @brief Preprocess insert value for dedup of special chars (@ and .).
     *
     * If existing content already contains the special char and the insert also
     * contains it, but the selected text does not, the special char is removed
     * from the insert value.
     * @param type The TextInputType (only NUMBER_DECIMAL and EMAIL_ADDRESS apply).
     * @param existing The existing content string.
     * @param insert The insert value to preprocess.
     * @param selected The currently selected text.
     * @return The preprocessed insert value.
     */
    static inline std::u16string PreprocessValue(TextInputType type, const std::u16string& existing,
        const std::u16string& insert, const std::u16string& selected)
    {
        auto tmp = insert;
        if (type == TextInputType::NUMBER_DECIMAL || type == TextInputType::EMAIL_ADDRESS) {
            char16_t specialChar = type == TextInputType::NUMBER_DECIMAL ? u'.' : u'@';
            if (existing.find(specialChar) != std::u16string::npos &&
                insert.find(specialChar) != std::u16string::npos &&
                selected.find(specialChar) == std::u16string::npos) {
                tmp.erase(std::remove_if(tmp.begin(), tmp.end(),
                    [&specialChar](char16_t c) { return c == specialChar; }), tmp.end());
            }
        }
        return tmp;
    }

    /**
     * @brief Remove error text characters from value, preserving order.
     * @param value The original value.
     * @param errorText The characters to remove (in order of appearance).
     * @return The value with error text removed.
     */
    static inline std::u16string RemoveErrorTextFromValue(
        const std::u16string& value, const std::u16string& errorText)
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

    /**
     * @brief Regex whitelist filter. Removes non-matching characters from result.
     * @param filter The regex whitelist pattern.
     * @param result The string to filter (modified in place).
     * @return Error text (characters that were removed).
     */
    static inline std::u16string FilterWithRegex(const std::u16string& filter, std::u16string& result)
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

    /**
     * @brief Regex whitelist filter with error callback.
     *
     * Combines FilterWithRegex + onError + return bool, matching the
     * core logic of the original ContentController::FilterWithEvent.
     * @param filter The regex whitelist pattern.
     * @param result The string to filter (modified in place).
     * @param onError Error callback returning whether the error was handled.
     *                When false, the filtering result is treated as not applied.
     * @return True if any characters were removed and the error was handled.
     */
    static inline bool FilterWithEvent(const std::u16string& filter, std::u16string& result,
        const std::function<bool(const std::u16string&)>& onError)
    {
        auto errorValue = FilterWithRegex(filter, result);
        if (errorValue.empty()) {
            return false;
        }
        return onError ? onError(errorValue) : true;
    }

    /**
     * @brief Filter email: keep only the first @, remove duplicates.
     * @param result The string to filter (modified in place).
     * @return True if text was changed.
     */
    static inline bool FilterWithEmail(std::u16string& result)
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

    /**
     * @brief Filter to ASCII only: remove non-ASCII characters.
     * @param result The string to filter (modified in place).
     * @return True if text was changed.
     */
    static inline bool FilterWithAscii(std::u16string& result)
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

    /**
     * @brief Filter decimal: keep only the first ., remove duplicates.
     * @param result The string to filter (modified in place).
     * @return True if text was changed.
     */
    static inline bool FilterWithDecimal(std::u16string& result)
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

public:
    // Whitelist constants
    static constexpr char16_t DIGIT_WHITE_LIST[] = u"[0-9]";
    static constexpr char16_t DIGIT_DECIMAL_WHITE_LIST[] = u"[0-9.]";
    static constexpr char16_t PHONE_WHITE_LIST[] = uR"([0-9 \+\-\*\#\(\)])";
    static constexpr char16_t EMAIL_WHITE_LIST[] = uR"([a-zA-Z0-9.!#$%&'*+/=?^_`{|}~@"-])";

    /**
     * @brief Check if the placeholder text indicates a verification code (OTP) field.
     *
     * Shared by TextFieldPattern::CheckAndUpdateInputTypeForOTP and
     * RichEditorPattern::CheckAndUpdateInputTypeForOtp. Detects both Chinese
     * (验证码) and English (verification code) keywords.
     */
    static inline bool IsVerificationCodePlaceholder(const std::u16string& placeholder)
    {
        static constexpr std::u16string_view OTP_KEYWORD_CN = u"验证码";
        static constexpr std::string_view OTP_KEYWORD_EN = "verification code";
        if (placeholder.find(OTP_KEYWORD_CN) != std::u16string::npos) {
            return true;
        }
        auto placeholderLower = UtfUtils::Str16DebugToStr8(placeholder);
        std::transform(placeholderLower.begin(), placeholderLower.end(), placeholderLower.begin(),
            [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
        return placeholderLower.find(OTP_KEYWORD_EN) != std::string::npos;
    }
};

/**
 * @brief Attempt to upgrade TextInputType from NUMBER to ONE_TIME_CODE_NUMBER
 *        when the placeholder indicates a verification code field.
 *
 * Template so it works with both TextFieldLayoutProperty and RichEditorLayoutProperty.
 * Both types must support GetTextInputTypeValue, GetPlaceholderValue, UpdateTypeChanged,
 * UpdateTextInputType. Returns true if the upgrade was performed.
 */
template <typename LayoutPropT>
inline bool TryUpgradeToOtpType(LayoutPropT* prop, TextInputType& keyboard, bool& isFilterChanged)
{
    CHECK_NULL_RETURN(prop, false);
    auto currentType = prop->GetTextInputTypeValue(TextInputType::UNSPECIFIED);
    if (currentType != TextInputType::NUMBER || keyboard != TextInputType::NUMBER) {
        return false;
    }
    auto placeholder = prop->GetPlaceholderValue(u"");
    if (placeholder.empty() || !TextInputFilter::IsVerificationCodePlaceholder(placeholder)) {
        return false;
    }
    prop->UpdateTypeChanged(true);
    isFilterChanged = true;
    prop->UpdateTextInputType(TextInputType::ONE_TIME_CODE_NUMBER);
    keyboard = TextInputType::ONE_TIME_CODE_NUMBER;
    return true;
}

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_IME_TEXT_INPUT_FILTER_H
