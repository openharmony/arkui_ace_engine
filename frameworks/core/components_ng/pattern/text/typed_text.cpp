/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text/typed_text.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint8_t UTF8_TO_UNICODE_SHIFT1 = 6;
constexpr uint8_t UTF8_TO_UNICODE_SHIFT2 = 12;
constexpr uint8_t UTF8_TO_UNICODE_SHIFT3 = 18;
} // namespace

uint8_t TypedText::GetUTF8OneCharacterSize(const char* str)
{
    if (str == nullptr) {
        return 0;
    }
    if ((str[0] & 0x80) == 0) {
        return 1;
    } else if ((str[0] & 0xE0) == 0xC0) {
        return 2; // 2: 2 bytes
    } else if ((str[0] & 0xF0) == 0xE0) {
        return 3; // 3: 3 bytes
    } else if ((str[0] & 0xF8) == 0xF0) {
        return 4; // 4: 4 bytes
    }
    return 0;
}

bool TypedText::IsEmoji(uint32_t codePoint)
{
    // Miscellaneous symbols and symbol fonts
    return (codePoint >= 0x2600 && codePoint <= 0x27BF) || codePoint == 0x303D || codePoint == 0x2049 ||
        codePoint == 0x203C || (codePoint >= 0x2000 && codePoint <= 0x200F) ||
        (codePoint >= 0x2028 && codePoint <= 0x202F) || codePoint == 0x205F ||
        // Area occupied by punctuation, Alphabetic symbol
        (codePoint >= 0x2065 && codePoint <= 0x206F) || (codePoint >= 0x2100 && codePoint <= 0x214F) ||
        // Various technical symbols, Arrow A
        (codePoint >= 0x2300 && codePoint <= 0x23FF) || (codePoint >= 0x2B00 && codePoint <= 0x2BFF) ||
        // Arrow B,Chinese symbols
        (codePoint >= 0x2900 && codePoint <= 0x297F) || (codePoint >= 0x3200 && codePoint <= 0x32FF) ||
        // High and low substitution reserved area, Private reserved area
        (codePoint >= 0xD800 && codePoint <= 0xDFFF) || (codePoint >= 0xE000 && codePoint <= 0xF8FF) ||
        // Mutation selector, Plane above the second plane，char can't be saved, all can be transferred
        (codePoint >= 0xFE00 && codePoint <= 0xFE0F) || codePoint >= 0x10000;
}

uint32_t TypedText::GetUTF8Next(const char* text, uint32_t i, uint32_t& j)
{
    uint32_t unicode = 0;
    if (text == nullptr) {
        return 0;
    }

    j = i;
    uint8_t lettetSize = GetUTF8OneCharacterSize(text + i);
    switch (lettetSize) {
        case 1:
            unicode = text[j];
            break;
        case 2: // 2: letter size
            unicode = static_cast<uint32_t>(text[j] & 0x1F) << UTF8_TO_UNICODE_SHIFT1;
            j++;
            if ((text[j] & 0xC0) != 0x80) {
                return 0;
            }
            unicode += (text[j] & 0x3F);
            break;
        case 3: // 3: letter size
            unicode = static_cast<uint32_t>(text[j] & 0x0F) << UTF8_TO_UNICODE_SHIFT2;
            unicode += static_cast<uint32_t>(text[++j] & 0x3F) << UTF8_TO_UNICODE_SHIFT1;
            unicode += (text[++j] & 0x3F);
            break;
        case 4: // 4: letter size
            unicode = static_cast<uint32_t>(text[j] & 0x07) << UTF8_TO_UNICODE_SHIFT3;
            unicode += static_cast<uint32_t>(text[++j] & 0x3F) << UTF8_TO_UNICODE_SHIFT2;
            unicode += static_cast<uint32_t>(text[++j] & 0x3F) << UTF8_TO_UNICODE_SHIFT1;
            unicode += text[++j] & 0x3F;
            break;
        default:
            break;
    }
    j++;
    return unicode;
}
} // namespace OHOS::Ace::NG