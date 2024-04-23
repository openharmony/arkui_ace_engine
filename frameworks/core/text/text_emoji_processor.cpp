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

#include "core/text/text_emoji_processor.h"

#include <unicode/uchar.h>

#include "base/utils/string_utils.h"
#include "base/utils/utils.h"

namespace OHOS::Ace {
namespace {

constexpr int32_t LINE_FEED = 0x0A;
constexpr int32_t CARRIAGE_RETURN = 0x0D;
constexpr int32_t COMBINING_ENCLOSING_KEYCAP = 0x20E3;
constexpr int32_t ZERO_WIDTH_JOINER = 0x200D;
constexpr int32_t CANCEL_TAG = 0xE007F;
constexpr int32_t STATE_BEGIN = 0;
constexpr int32_t STATE_SECOND = 1;
constexpr int32_t STATE_EM = 2;
constexpr int32_t STATE_VS_AND_KEYCAP = 3;
constexpr int32_t STATE_ZWJ = 4;
constexpr int32_t STATE_KEYCAP = 5;
constexpr int32_t STATE_EMOJI = 6;
constexpr int32_t STATE_VS_AND_EM = 7;
constexpr int32_t STATE_VS = 8;
constexpr int32_t STATE_VS_AND_ZWJ = 9;
constexpr int32_t STATE_LF = 10;
constexpr int32_t STATE_CR = 11;
constexpr int32_t STATE_IN_TAG_QUEUE = 12;
constexpr int32_t STATE_EVEN_RIS = 13;
constexpr int32_t STATE_ODD_RIS = 14;
constexpr int32_t STATE_FINISHED = 20;

} // namespace

int32_t TextEmojiProcessor::Delete(int32_t startIndex, int32_t length, std::string& content, bool isBackward)
{
    std::u16string u16 = StringUtils::Str8ToStr16(content);
    // startIndex from selectController_->GetCaretIndex() is an utf-16 index
    // so we need an u16string to get the correct index
    std::u16string remainString = u"";
    std::u32string u32ContentToDelete;
    if (isBackward) {
        if (startIndex == u16.length()) {
            u32ContentToDelete = StringUtils::ToU32string(content);
        } else {
            remainString = u16.substr(startIndex, u16.length() - startIndex);
            std::u16string temp = u16.substr(0, startIndex);
            u32ContentToDelete = StringUtils::ToU32string(StringUtils::Str16ToStr8(temp));
        }
        if (u32ContentToDelete.length() == 0) {
            return 0;
        }
        for (int32_t i = 0; i < length; i++) {
            if (!BackwardDelete(u32ContentToDelete)) {
                break;
            }
        }
        content = StringUtils::U32StringToString(u32ContentToDelete) + StringUtils::Str16ToStr8(remainString);
    } else {
        if (startIndex == 0) {
            u32ContentToDelete = StringUtils::ToU32string(content);
        } else {
            remainString = u16.substr(0, startIndex);
            std::u16string temp = u16.substr(startIndex, u16.length() - startIndex);
            u32ContentToDelete = StringUtils::ToU32string(StringUtils::Str16ToStr8(temp));
        }
        if (u32ContentToDelete.length() == 0) {
            return 0;
        }
        for (int32_t i = 0; i < length; i++) {
            if (!ForwardDelete(u32ContentToDelete)) {
                break;
            }
        }
        content = StringUtils::Str16ToStr8(remainString) + StringUtils::U32StringToString(u32ContentToDelete);
    }
    int32_t deletedLength = u16.length() - StringUtils::Str8ToStr16(content).length();
    //we need length to update the cursor
    return deletedLength;
}

bool TextEmojiProcessor::IsIndexInEmoji(int32_t index, std::string content, int32_t& startIndex, int32_t& endIndex)
{
    endIndex = index;
    startIndex = index;
    std::u16string u16Content = StringUtils::Str8ToStr16(content);
    if (index <= 0 || index >= u16Content.length()) {
        return false;
    }
    std::u32string u32Content;
    int32_t backwardLen = GetEmojiLengthBackward(u32Content, index, u16Content);
    if (backwardLen == 0) {
        // no emoji before, startIndex is not in the middle of emoji
        TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "IsIndexInEmoji backwardLen is 0");
        return false;
    }
    int32_t u32Length = u32Content.length();
    int32_t emojiBackwardLengthU16 = U32ToU16string(u32Content.substr(u32Length - backwardLen, u32Length)).length();
    index -= emojiBackwardLengthU16;
    emojiBackwardLengthU16 = endIndex - index; // calculate length of the part of emoji

    // get the whole emoji from the new start
    int32_t forwardLen = GetEmojiLengthForward(u32Content, index, u16Content);
    if (forwardLen == 0) {
        TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "IsIndexInEmoji forwardLen is 0");
        return false;
    }
    int32_t emojiForwardLengthU16 = U32ToU16string(u32Content.substr(0, forwardLen)).length();
    if (emojiForwardLengthU16 > emojiBackwardLengthU16) {
        // forward length is larget than backward one, which means the startIndex is in the middle of one emoji
        TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "IsIndexInEmoji index=%{public}d emojiBackwardLengthU16=%{public}d"
            " emojiForwardLengthU16=%{public}d forwardLen=%{public}d backwardLen=%{public}d",
            index, emojiBackwardLengthU16, emojiForwardLengthU16, forwardLen, backwardLen);
        endIndex = index + emojiForwardLengthU16;
        startIndex = index;
        return true;
    }
    return false;
}

std::u16string TextEmojiProcessor::U32ToU16string(const std::u32string& u32str)
{
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> u8ToU16converter;
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> u32ToU8converter;
    return u8ToU16converter.from_bytes(u32ToU8converter.to_bytes(u32str));
}

int32_t TextEmojiProcessor::GetEmojiLengthBackward(std::u32string& u32Content,
    int32_t& startIndex, std::u16string u16Content)
{
    if (startIndex <= 0 || startIndex > u16Content.length()) {
        return 0;
    }
    do {
        // U32 string may be failed to tranfer for spliting. Try to enlarge string scope to get transferred u32 string.
        std::u16string temp = u16Content.substr(0, startIndex);
        u32Content = StringUtils::ToU32string(StringUtils::Str16ToStr8(temp));
    } while (u32Content.length() == 0 && ++startIndex <= u16Content.length());
    if (u32Content.length() == 0) {
        TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "GetEmojiLengthBackward u32Content is 0");
        return 0;
    }
    return GetEmojiLengthAtEnd(u32Content, false);
}

int32_t TextEmojiProcessor::GetEmojiLengthForward(std::u32string& u32Content,
    int32_t& startIndex, std::u16string u16Content)
{
    if (startIndex >= u16Content.length()) {
        return 0;
    }
    do {
        // U32 string may be failed to tranfer for spliting. Try to enlarge string scope to get transferred u32 string.
        std::u16string temp = u16Content.substr(startIndex, u16Content.length() - startIndex);
        u32Content = StringUtils::ToU32string(StringUtils::Str16ToStr8(temp));
    } while (u32Content.length() == 0 && --startIndex >= 0);
    if (u32Content.length() == 0) {
        TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "GetEmojiLengthForward u32Content is 0");
        return 0;
    }
    return GetEmojiLengthAtFront(u32Content, false);
}

bool TextEmojiProcessor::IsEmojiModifierBase(uint32_t codePoint)
{
    // according to the https://unicode.org/Public/emoji/4.0/emoji-data.txt
    // emoji 4.0 removed 0x1F91D(HANDSHAKE) and 0x1F93C(WRESTLERS) from the emoji modifier base
    // to handle with the compatibility, we need to add them back
    if (codePoint == 0x1F91D || codePoint == 0x1F93C) {
        return true;
    }
    return u_hasBinaryProperty(static_cast<UChar32>(codePoint), UCHAR_EMOJI_MODIFIER_BASE);
}

bool TextEmojiProcessor::IsVariationSelector(uint32_t codePoint)
{
    return u_hasBinaryProperty(static_cast<UChar32>(codePoint), UCHAR_VARIATION_SELECTOR);
}

bool TextEmojiProcessor::IsRegionalIndicatorSymbol(uint32_t codePoint)
{
    return u_hasBinaryProperty(codePoint, UCHAR_REGIONAL_INDICATOR);
}

bool TextEmojiProcessor::IsEmoji(uint32_t codePoint)
{
    return u_hasBinaryProperty(static_cast<UChar32>(codePoint), UCHAR_EMOJI);
}

bool TextEmojiProcessor::IsEmojiModifier(uint32_t codePoint)
{
    return u_hasBinaryProperty(static_cast<UChar32>(codePoint), UCHAR_EMOJI_MODIFIER);
}

bool TextEmojiProcessor::IsTagSpec(uint32_t codePoint)
{
    // according to the https://www.unicode.org/charts/PDF/U0000.pdf
    // 0xE0020 - 0xE007E are the visible tag specs.
    // 0xE007F is CANCEL_TAG, not in here.
    return 0xE0020 <= codePoint && codePoint <= 0xE007E;
}

bool TextEmojiProcessor::IsKeycapBase(uint32_t codePoint)
{
    return ('0' <= codePoint && codePoint <= '9') || codePoint == '#' || codePoint == '*';
}

void TextEmojiProcessor::OnBeginState(uint32_t codePoint, int32_t& state, int32_t& deleteCount, bool isBackward)
{
    deleteCount = 1;
    if (codePoint == LINE_FEED) {
        state = STATE_LF;
    } else if (IsVariationSelector(codePoint)) { // only backward
        state = STATE_VS;
    } else if (codePoint == CARRIAGE_RETURN) { // only forward
        state = STATE_CR;
    } else if (IsRegionalIndicatorSymbol(codePoint)) {
        state = isBackward ? STATE_ODD_RIS : STATE_EVEN_RIS;
    } else if (IsEmojiModifier(codePoint)) {
        state = STATE_EM;
    } else if (codePoint == COMBINING_ENCLOSING_KEYCAP) {
        state = STATE_KEYCAP;
    } else if (IsEmoji(codePoint)) {
        state = STATE_EMOJI;
    } else if (codePoint == CANCEL_TAG) {
        state = STATE_IN_TAG_QUEUE;
    } else {
        state = isBackward ? STATE_FINISHED : STATE_SECOND;
    }
}

void TextEmojiProcessor::OnRISState(uint32_t codePoint, int32_t& state, int32_t& deleteCount, bool isBackward)
{
    if (isBackward) {
        switch (state) {
            case STATE_ODD_RIS:
                if (IsRegionalIndicatorSymbol(codePoint)) {
                    ++deleteCount;
                    state = STATE_EVEN_RIS;
                } else {
                    state = STATE_FINISHED;
                }
                break;
            case STATE_EVEN_RIS:
                if (IsRegionalIndicatorSymbol(codePoint)) {
                    state = STATE_FINISHED;
                }
                break;
        }
    } else {
        switch (state) {
            case STATE_ODD_RIS:
                state = STATE_FINISHED;
                break;
            case STATE_EVEN_RIS:
                if (IsRegionalIndicatorSymbol(codePoint)) {
                    ++deleteCount;
                    state = STATE_ODD_RIS;
                } else {
                    state = STATE_FINISHED;
                }
                break;
        }
    }
}

void TextEmojiProcessor::OnCRLFState(uint32_t codePoint, int32_t& state, int32_t& deleteCount, bool isBackward)
{
    if (isBackward) {
        if (codePoint == CARRIAGE_RETURN) {
            ++deleteCount;
        }
        state = STATE_FINISHED;
    } else {
        switch (state) {
            case STATE_CR:
                if (codePoint == LINE_FEED) {
                    ++deleteCount;
                }
                state = STATE_FINISHED;
                break;
            case STATE_LF:
                state = STATE_FINISHED;
                break;
        }
    }
}

void TextEmojiProcessor::OnZWJState(uint32_t codePoint, int32_t& state, int32_t& deleteCount, int32_t& lastVSCount,
    bool isBackward)
{
    if (isBackward) {
        switch (state) {
            case STATE_ZWJ:
                if (IsEmoji(codePoint)) {
                    ++deleteCount; // delete zwj
                    ++deleteCount; // delete emoji
                    state = IsEmojiModifier(codePoint) ? STATE_EM : STATE_EMOJI;
                } else if (IsVariationSelector(codePoint)) {
                    lastVSCount = 1;
                    state = STATE_VS_AND_ZWJ;
                } else {
                    state = STATE_FINISHED;
                }
                break;
            case STATE_VS_AND_ZWJ:
                if (IsEmoji(codePoint)) {
                    ++deleteCount; // delete zwj
                    ++deleteCount; // delete emoji
                    deleteCount += lastVSCount;
                    lastVSCount = 0;
                    state = STATE_EMOJI;
                } else {
                    state = STATE_FINISHED;
                }
                break;
        }
    } else {
        if (IsEmoji(codePoint)) {
            ++deleteCount;
            state = STATE_EMOJI;
        } else {
            state = STATE_FINISHED;
        }
    }
}

void TextEmojiProcessor::OnVSState(uint32_t codePoint, int32_t& state, int32_t& deleteCount, bool isBackward)
{
    if (isBackward) {
        if (IsEmoji(codePoint)) {
            ++deleteCount;
            state = STATE_EMOJI;
            return;
        }
        if (!IsVariationSelector(codePoint) &&
            u_getCombiningClass(codePoint) == 0) {
            ++deleteCount;
        }
        state = STATE_FINISHED;
    } else {
        if (codePoint == ZERO_WIDTH_JOINER) {
            ++deleteCount;
            state = STATE_ZWJ;
            return;
        } else if (codePoint == COMBINING_ENCLOSING_KEYCAP) {
            ++deleteCount;
            state = STATE_KEYCAP;
            return;
        }
        state = STATE_FINISHED;
    }
}

void TextEmojiProcessor::OnKeyCapState(uint32_t codePoint, int32_t& state, int32_t& deleteCount, int32_t& lastVSCount,
    bool isBackward)
{
    if (isBackward) {
        switch (state) {
            case STATE_KEYCAP:
                if (IsVariationSelector(codePoint)) {
                    lastVSCount = 1;
                    state = STATE_VS_AND_KEYCAP;
                    return;
                }
                if (IsEmojiModifierBase(codePoint)) {
                    ++deleteCount;
                    state = STATE_FINISHED;
                }
                break;
            case STATE_VS_AND_KEYCAP:
                if (IsKeycapBase(codePoint)) {
                    deleteCount += lastVSCount + 1;
                }
                state = STATE_FINISHED;
                break;
        }
    } else {
        state = STATE_FINISHED;
    }
}

void TextEmojiProcessor::OnEMState(uint32_t codePoint, int32_t& state, int32_t& deleteCount, int32_t& lastVSCount,
    bool isBackward)
{
    if (isBackward) {
        switch (state) {
            case STATE_EM:
                if (IsVariationSelector(codePoint)) {
                    lastVSCount = 1;
                    state = STATE_VS_AND_EM;
                    return;
                } else if (IsEmojiModifierBase(codePoint)) {
                    ++deleteCount;
                }
                state = STATE_FINISHED;
                break;
            case STATE_VS_AND_EM:
                if (IsEmojiModifierBase(codePoint)) {
                    deleteCount += lastVSCount + 1;
                }
                state = STATE_FINISHED;
                break;
        }
    } else {
        if (IsEmoji(codePoint)) {
            ++deleteCount;
            state = STATE_EMOJI;
            return;
        } else if (IsVariationSelector(codePoint)) {
            ++deleteCount;
            state = STATE_VS;
            return;
        } else if (codePoint == ZERO_WIDTH_JOINER) {
            ++deleteCount;
            state = STATE_ZWJ;
            return;
        } else if (IsEmojiModifierBase(codePoint)) {
            ++deleteCount;
        }
        state = STATE_FINISHED;
    }
}

void TextEmojiProcessor::OnEmojiState(uint32_t codePoint, int32_t& state, int32_t& deleteCount, bool isBackward)
{
    if (isBackward) {
        if (codePoint == ZERO_WIDTH_JOINER) {
            state = STATE_ZWJ;
        } else {
            state = STATE_FINISHED;
        }
    } else {
        if (codePoint == ZERO_WIDTH_JOINER) {
            ++deleteCount;
            state = STATE_ZWJ;
        } else if (IsVariationSelector(codePoint)) {
            ++deleteCount;
            state = STATE_VS;
        } else if (IsEmojiModifier(codePoint)) {
            ++deleteCount;
            state = STATE_EM;
        } else if (IsTagSpec(codePoint)) {
            ++deleteCount;
            state = STATE_IN_TAG_QUEUE;
        } else {
            state = STATE_FINISHED;
        }
    }
}

void TextEmojiProcessor::OnForwardSecondState(uint32_t codePoint, int32_t& state, int32_t& deleteCount)
{
    if (IsVariationSelector(codePoint)) {
        ++deleteCount;
        state = STATE_VS;
    } else if (codePoint == COMBINING_ENCLOSING_KEYCAP) {
        ++deleteCount;
        state = STATE_KEYCAP;
    } else {
        state = STATE_FINISHED;
    }
}

void TextEmojiProcessor::OnTagQueueState(uint32_t codePoint, int32_t& state, int32_t& deleteCount, bool isBackward)
{
    if (isBackward) {
        if (!IsTagSpec(codePoint)) {
            state = STATE_FINISHED;
        }
        ++deleteCount;
    } else {
        if (IsTagSpec(codePoint)) {
            ++deleteCount;
        } else if (IsEmoji(codePoint)) {
            state = STATE_FINISHED;
        } else if (codePoint == CANCEL_TAG) {
            ++deleteCount;
            state = STATE_FINISHED;
        } else {
            ++deleteCount;
            state = STATE_FINISHED;
        }
    }
}

int32_t TextEmojiProcessor::GetEmojiLengthAtEnd(std::u32string u32Content, bool isCountNonEmoji)
{
    int32_t deleteCount = 0;
    int32_t lastVSCount = 0;
    int32_t state = STATE_BEGIN;
    int32_t tempOffset = u32Content.length() - 1;
    do {
        uint32_t codePoint = u32Content[tempOffset];
        tempOffset--;
        switch (state) {
            case STATE_BEGIN:
                OnBeginState(codePoint, state, deleteCount, true);
                if (!isCountNonEmoji && (state == STATE_FINISHED || state == STATE_SECOND)) {
                    // avoid non-emoji
                    return 0;
                }
                break;
            case STATE_LF:
                OnCRLFState(codePoint, state, deleteCount, true);
                break;
            case STATE_ODD_RIS:
            case STATE_EVEN_RIS:
                OnRISState(codePoint, state, deleteCount, true);
                break;
            case STATE_KEYCAP:
            case STATE_VS_AND_KEYCAP:
                OnKeyCapState(codePoint, state, deleteCount, lastVSCount, true);
                break;
            case STATE_EM:
            case STATE_VS_AND_EM:
                OnEMState(codePoint, state, deleteCount, lastVSCount, true);
                break;
            case STATE_VS:
                OnVSState(codePoint, state, deleteCount, true);
                break;
            case STATE_EMOJI:
                OnEmojiState(codePoint, state, deleteCount, true);
                break;
            case STATE_ZWJ:
            case STATE_VS_AND_ZWJ:
                OnZWJState(codePoint, state, deleteCount, lastVSCount, true);
                break;
            case STATE_IN_TAG_QUEUE:
                OnTagQueueState(codePoint, state, deleteCount, true);
                break;
            default:
                break;
        }
    } while (tempOffset >= 0 && state != STATE_FINISHED);
    return deleteCount;
}

bool TextEmojiProcessor::BackwardDelete(std::u32string& u32Content)
{
    int32_t deleteCount = GetEmojiLengthAtEnd(u32Content, true);
    return HandleDeleteAction(u32Content, deleteCount, true);
}

int32_t TextEmojiProcessor::GetEmojiLengthAtFront(std::u32string u32Content, bool isCountNonEmoji)
{
    int32_t deleteCount = 0;
    int32_t state = STATE_BEGIN;
    int32_t tempOffset = 0;
    do {
        int32_t codePoint = u32Content[tempOffset];
        tempOffset++;
        switch (state) {
            case STATE_BEGIN:
                OnBeginState(codePoint, state, deleteCount, false);
                if (!isCountNonEmoji && (state == STATE_FINISHED || state == STATE_SECOND)) {
                    return 0;
                }
                break;
            case STATE_SECOND:
                OnForwardSecondState(codePoint, state, deleteCount);
                break;
            case STATE_CR:
            case STATE_LF:
                OnCRLFState(codePoint, state, deleteCount, false);
                break;
            case STATE_ODD_RIS:
            case STATE_EVEN_RIS:
                OnRISState(codePoint, state, deleteCount, false);
                break;
            case STATE_KEYCAP:
                OnKeyCapState(codePoint, state, deleteCount, deleteCount, false);
                // in ForwardDelete, we dont need to care about lastVSCount.
                // "Borrowing" deleteCount to lastVSCount, to avoiding the use of std::optional.
                // same as above
                break;
            case STATE_EM:
                OnEMState(codePoint, state, deleteCount, deleteCount, false);
                break;
            case STATE_VS:
                OnVSState(codePoint, state, deleteCount, false);
                break;
            case STATE_EMOJI:
                OnEmojiState(codePoint, state, deleteCount, false);
                break;
            case STATE_ZWJ:
                OnZWJState(codePoint, state, deleteCount, deleteCount, false);
                break;
            case STATE_IN_TAG_QUEUE:
                OnTagQueueState(codePoint, state, deleteCount, false);
                break;
            default:
                break;
        }
    } while (tempOffset < u32Content.length() && state != STATE_FINISHED);
    return deleteCount;
}

bool TextEmojiProcessor::ForwardDelete(std::u32string& u32Content)
{
    int32_t deleteCount = GetEmojiLengthAtFront(u32Content, true);
    return HandleDeleteAction(u32Content, deleteCount, false);
}

bool TextEmojiProcessor::HandleDeleteAction(std::u32string& u32Content, int32_t deleteCount, bool isBackward)
{
    if (isBackward) {
        if (deleteCount > 0) {
            int32_t start = u32Content.length() - deleteCount;
            u32Content.erase(start, deleteCount);
            return true;
        }
    } else {
        if (deleteCount > 0) {
            u32Content.erase(0, deleteCount);
            return true;
        }
    }
    return false;
}

} // namespace OHOS::Ace
