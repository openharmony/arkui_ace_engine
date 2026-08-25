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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_IME_TEXT_INPUT_OBSCURE_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_IME_TEXT_INPUT_OBSCURE_UTILS_H

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <string>

#include "base/i18n/localization.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/common/ime/text_input_type.h"

namespace OHOS::Ace {

/**
 * @brief Password obscuration rendering utility extracted from TextFieldPattern.
 *
 * Provides shared obscuration characters and text generation logic.
 */
class TextInputObscureUtils {
public:
    static constexpr char16_t OBSCURING_CHARACTER = u'\u2022'; // bullet
    static constexpr char16_t OBSCURING_CHARACTER_FOR_AR = u'*'; // Arabic
    static constexpr uint32_t OBSCURE_SHOW_TICKS = 1; // 500ms (one caret twinkling tick)

    /**
     * @brief Create a fully obscured string of the given length.
     * @param len The length of the obscured string.
     * @return Obscured string using bullet (or * for Arabic locale).
     */
    static inline std::u16string CreateObscuredText(int32_t len)
    {
        return std::u16string(len, GetObscuringCharacter());
    }

    /**
     * @brief Create display text with optional obscuration and last-char reveal.
     * @param content The original content.
     * @param nakedCharPosition Position of the briefly visible char (-1 if none).
     * @param needObscureText Whether obscuration is active.
     * @param showPasswordDirectly Whether to suppress last-char reveal (API >= 12).
     * @return The display text (obscured or original).
     */
    static inline std::u16string CreateDisplayText(
        const std::u16string& content, int32_t nakedCharPosition, bool needObscureText, bool showPasswordDirectly)
    {
        if (!content.empty() && needObscureText) {
            auto text = CreateObscuredText(static_cast<int32_t>(content.length()));
            if (nakedCharPosition >= 0 && nakedCharPosition < static_cast<int32_t>(content.length())) {
                if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE) || !showPasswordDirectly) {
                    text[nakedCharPosition] = content[nakedCharPosition];
                }
            }
            return text;
        }
        return content;
    }

    /**
     * @brief Get the obscuring character for the current locale.
     * @return OBSCURING_CHARACTER_FOR_AR for Arabic, OBSCURING_CHARACTER otherwise.
     */
    static inline char16_t GetObscuringCharacter()
    {
        return Localization::GetInstance()->GetLanguage() == "ar" ? OBSCURING_CHARACTER_FOR_AR : OBSCURING_CHARACTER;
    }

    /**
     * @brief Calculate obscure reveal state after a character insertion.
     *
     * Mirrors the core algorithm shared by TextFieldPattern::UpdateObscure and
     * RichEditorPattern::UpdateObscure. Both callers obtain content and caret
     * position differently, so those are passed in as parameters.
     */
    struct ObscureUpdateResult {
        int32_t tickCountDown = 0;
        int32_t nakedCharPosition = -1;
    };

    static inline ObscureUpdateResult UpdateObscureState(
        TextInputType inputType, const std::u16string& insertValue, bool hasInsert,
        const std::u16string& content, int32_t caretPosition)
    {
        ObscureUpdateResult result;
        if (insertValue.length() == 1 &&
            (inputType != TextInputType::NUMBER_PASSWORD || std::isdigit(insertValue[0])) && hasInsert) {
            auto insertIndex = std::clamp(caretPosition - 1, 0, static_cast<int32_t>(content.length()));
            auto strBeforeCaret = content.empty() ? u"" : content.substr(insertIndex, 1);
            bool match = (strBeforeCaret == insertValue);
            result.tickCountDown = match ? static_cast<int32_t>(OBSCURE_SHOW_TICKS) : 0;
            result.nakedCharPosition = match ? insertIndex : -1;
        }
        return result;
    }

    /**
     * @brief Check whether the naked (briefly visible) char should be revealed.
     *
     * Pure guard condition shared by TextFieldPattern::GetNakedCharPosition and
     * RichEditorPattern::GetNakedCharPosition. Callers should check this BEFORE
     * accessing content, so that content/property acquisition is skipped when
     * the guards fail (avoiding unnecessary null dereference risk).
     */
    static inline bool ShouldRevealNakedChar(
        bool isSingleLine, bool isInPasswordMode, bool isObscured, int32_t tickCountDown)
    {
        return isSingleLine && isInPasswordMode && isObscured && tickCountDown > 0;
    }
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_IME_TEXT_INPUT_OBSCURE_UTILS_H
