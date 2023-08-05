/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_FIELD_TEXT_EDITING_VALUE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_FIELD_TEXT_EDITING_VALUE_H

#include <algorithm>
#include <functional>
#include <string>

#include "base/utils/string_utils.h"

namespace OHOS::Ace::NG {

struct TextEditingValueNG {
    bool operator==(const TextEditingValueNG& other) const
    {
        return text == other.text;
    }

    bool operator!=(const TextEditingValueNG& other) const
    {
        return !operator==(other);
    }

    bool Empty() const
    {
        return text.empty();
    }

    std::wstring GetWideText() const
    {
        return StringUtils::ToWstring(text);
    }

    void CursorMoveLeft()
    {
        caretPosition = std::max(0, caretPosition - 1);
    }

    void CursorMoveRight()
    {
        caretPosition = std::min(static_cast<int32_t>(GetWideText().length()), caretPosition + 1);
    }

    void CursorMoveToPosition(int32_t position)
    {
        caretPosition = std::clamp(position, 0, static_cast<int32_t>(GetWideText().length()));
    }

    std::string GetValueBeforeCursor() const
    {
        auto wideText = GetWideText();
        if (caretPosition > static_cast<int32_t>(wideText.length()) || caretPosition <= 0) {
            return "";
        }
        return StringUtils::ToString(wideText.substr(0, caretPosition));
    }

    std::string GetValueAfterCursor() const
    {
        auto wideText = GetWideText();
        if (caretPosition > static_cast<int32_t>(wideText.length()) || caretPosition < 0) {
            return "";
        }
        return StringUtils::ToString(wideText.substr(caretPosition));
    }

    std::string GetValueBeforePosition(int32_t position) const
    {
        auto wideText = GetWideText();
        position = std::clamp(position, 0, static_cast<int32_t>(wideText.length()));
        LOGI("GetValueBeforePosition %{public}d", position);
        return StringUtils::ToString(wideText.substr(0, position));
    }

    std::string GetValueAfterPosition(int32_t position) const
    {
        auto wideText = GetWideText();
        position = std::clamp(position, 0, static_cast<int32_t>(wideText.length()));
        LOGI("GetValueAfterPosition %{public}d", position);
        return StringUtils::ToString(wideText.substr(position));
    }

    std::string GetSelectedText(int32_t start, int32_t end) const
    {
        auto wideText = GetWideText();
        auto min = std::clamp(std::max(std::min(start, end), 0), 0, static_cast<int32_t>(wideText.length()));
        auto max = std::clamp(std::min(std::max(start, end), static_cast<int32_t>(wideText.length())), 0,
            static_cast<int32_t>(wideText.length()));
        return StringUtils::ToString(wideText.substr(min, max - min));
    }

    bool CaretAtLast() const
    {
        return static_cast<int32_t>(GetWideText().length()) == caretPosition;
    }

    char16_t LastChar() const
    {
        if (text.empty()) {
            return 0;
        }
        if (static_cast<size_t>(caretPosition) > text.length()) {
            return 0;
        }
        return text[std::max(0, caretPosition - 1)];
    }

    std::string ToString() const
    {
        return GetValueBeforeCursor() + "|" + GetValueAfterCursor();
    }

    void Reset()
    {
        text.clear();
        caretPosition = 0;
    }

    std::string text;
    int32_t caretPosition = 0;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_FIELD_TEXT_EDITING_VALUE_H
