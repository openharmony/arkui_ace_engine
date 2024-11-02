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

#include "base/utils/utf_helper.h"
#include "unicode/unistr.h"

namespace OHOS::Ace::UtfUtils {

const std::string DEFAULT_STR = "error";
const std::u16string DEFAULT_U16STR = u"error";
const std::u32string DEFAULT_U32STR = U"error";

constexpr size_t HI_SURROGATE_MIN = 0xd800;
constexpr size_t HI_SURROGATE_MAX = 0xdbff;
constexpr size_t LO_SURROGATE_MIN = 0xdc00;
constexpr size_t LO_SURROGATE_MAX = 0xdfff;

static constexpr size_t CONST_2 = 2;
static constexpr size_t CONST_3 = 3;
static constexpr size_t LOW_3BITS = 0x7;
static constexpr size_t LOW_4BITS = 0xF;
static constexpr size_t LOW_5BITS = 0x1F;
static constexpr size_t LOW_6BITS = 0x3F;
static constexpr size_t L_SURROGATE_START = 0xDC00;
static constexpr size_t H_SURROGATE_START = 0xD800;
static constexpr size_t SURROGATE_RAIR_START = 0x10000;
static constexpr size_t OFFSET_18POS = 18;
static constexpr size_t OFFSET_12POS = 12;
static constexpr size_t OFFSET_10POS = 10;
static constexpr size_t OFFSET_6POS = 6;
static constexpr uint16_t DECODE_LEAD_LOW = 0xD800;
static constexpr uint16_t DECODE_LEAD_HIGH = 0xDBFF;
static constexpr uint16_t DECODE_TRAIL_LOW = 0xDC00;
static constexpr uint16_t DECODE_TRAIL_HIGH = 0xDFFF;
static constexpr uint32_t DECODE_SECOND_FACTOR = 0x10000;
static constexpr uint32_t UTF8_OFFSET = 6;
static constexpr uint32_t UTF16_OFFSET = 10;
static constexpr uint16_t SURROGATE_MASK = 0xF800;
static constexpr uint16_t UTF16_REPLACEMENT_CHARACTER = 0xFFFD;

static constexpr uint8_t UTF8_1B_MAX = 0x7f;
static constexpr uint16_t UTF8_2B_MAX = 0x7ff;
static constexpr uint16_t UTF8_3B_MAX = 0xffff;

static constexpr uint8_t BYTE_MASK = 0xbf;
static constexpr uint8_t BYTE_MARK = 0x80;

enum UtfLength : uint8_t { ONE = 1, TWO = 2, THREE = 3, FOUR = 4 };

static const unsigned char FIRST_BYTE_MARK[7] = {0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC};

bool IsUTF16HighSurrogate(uint16_t ch)
{
    return DECODE_LEAD_LOW <= ch && ch <= DECODE_LEAD_HIGH;
}

bool IsUTF16LowSurrogate(uint16_t ch)
{
    return DECODE_TRAIL_LOW <= ch && ch <= DECODE_TRAIL_HIGH;
}

// Methods for decode utf16 to unicode
uint32_t DecodeUTF16(uint16_t const *utf16, size_t len, size_t *index)
{
    uint16_t high = utf16[*index];
    if ((high & SURROGATE_MASK) != DECODE_LEAD_LOW || !IsUTF16HighSurrogate(high) || *index == len - 1) {
        return high;
    }
    uint16_t low = utf16[*index + 1];
    if (!IsUTF16LowSurrogate(low)) {
        return high;
    }
    (*index)++;
    return ((high - DECODE_LEAD_LOW) << UTF16_OFFSET) + (low - DECODE_TRAIL_LOW) + DECODE_SECOND_FACTOR;
}

uint32_t HandleAndDecodeInvalidUTF16(uint16_t const *utf16, size_t len, size_t *index)
{
    uint16_t first = utf16[*index];
    // A valid surrogate pair should always start with a High Surrogate
    if (IsUTF16LowSurrogate(first)) {
        return UTF16_REPLACEMENT_CHARACTER;
    }
    if (IsUTF16HighSurrogate(first) || (first & SURROGATE_MASK) == DECODE_LEAD_LOW) {
        if (*index == len - 1) {
            // A High surrogate not paired with another surrogate
            return UTF16_REPLACEMENT_CHARACTER;
        }
        uint16_t second = utf16[*index + 1];
        if (!IsUTF16LowSurrogate(second)) {
            // A High surrogate not followed by a low surrogate
            return UTF16_REPLACEMENT_CHARACTER;
        }
        // A valid surrogate pair, decode normally
        (*index)++;
        return ((first - DECODE_LEAD_LOW) << UTF16_OFFSET) + (second - DECODE_TRAIL_LOW) + DECODE_SECOND_FACTOR;
    }
    // A unicode not fallen into the range of representing by surrogate pair, return as it is
    return first;
}

static void RepalceUnpairedSurrogates(uint16_t *utf16, size_t end, size_t *index)
{
    uint16_t first = utf16[*index];
    // A valid surrogate pair should always start with a High Surrogate
    if (IsUTF16LowSurrogate(first)) {
        utf16[*index] = UTF16_REPLACEMENT_CHARACTER;
        return;
    }
    if (IsUTF16HighSurrogate(first) || (first & SURROGATE_MASK) == DECODE_LEAD_LOW) {
        if (*index == end - 1) {
            // A High surrogate not paired with another surrogate
            utf16[*index] = UTF16_REPLACEMENT_CHARACTER;
            return;
        }
        uint16_t second = utf16[*index + 1];
        if (!IsUTF16LowSurrogate(second)) {
            // A High surrogate not followed by a low surrogate
            utf16[*index] = UTF16_REPLACEMENT_CHARACTER;
            return;
        }
        // A valid surrogate pair, decode normally
        (*index)++;
        return;
    }
    // A unicode not fallen into the range of representing by surrogate pair, return as it is
    return;
}

void HandleInvalidUTF16(uint16_t* utf16In, size_t utf16Len, size_t start)
{
    if (utf16In == nullptr) {
        return;
    }
    size_t end = start + utf16Len;
    for (size_t i = start; i < end; ++i) {
        RepalceUnpairedSurrogates(utf16In, end, &i);
    }
}

inline size_t UTF8Length(uint32_t codepoint)
{
    if (codepoint <= UTF8_1B_MAX) {
        return UtfLength::ONE;
    }
    if (codepoint <= UTF8_2B_MAX) {
        return UtfLength::TWO;
    }
    if (codepoint <= UTF8_3B_MAX) {
        return UtfLength::THREE;
    }
    return UtfLength::FOUR;
}

// Methods for encode unicode to unicode
size_t EncodeUTF8(uint32_t codepoint, uint8_t* utf8, size_t len, size_t index)
{
    size_t size = UTF8Length(codepoint);
    if (index + size > len) {
        return 0;
    }
    for (size_t j = size - 1; j > 0; j--) {
        uint8_t cont = ((codepoint | BYTE_MARK) & BYTE_MASK);
        utf8[index + j] = cont;
        codepoint >>= UTF8_OFFSET;
    }
    utf8[index] = codepoint | FIRST_BYTE_MARK[size];
    return size;
}

size_t Utf16ToUtf8Size(const uint16_t *utf16, uint32_t length)
{
    size_t res = 1;  // zero byte
    // when utf16 data length is only 1 and code in 0xd800-0xdfff,
    // means that is a single code point, it needs to be represented by three UTF8 code.
    if (length == 1 && utf16[0] >= HI_SURROGATE_MIN &&
        utf16[0] <= LO_SURROGATE_MAX) {
        res += UtfLength::THREE;
        return res;
    }

    for (uint32_t i = 0; i < length; ++i) {
        if (utf16[i] == 0) {
            // do nothing
        } else if (utf16[i] <= UTF8_1B_MAX) {
            res += 1;
        } else if (utf16[i] <= UTF8_2B_MAX) {
            res += UtfLength::TWO;
            // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        } else if (utf16[i] < HI_SURROGATE_MIN || utf16[i] > HI_SURROGATE_MAX) {
            res += UtfLength::THREE;
        } else {
            if (i < length - 1 &&
                utf16[i + 1] >= LO_SURROGATE_MIN &&
                utf16[i + 1] <= LO_SURROGATE_MAX) {
                res += UtfLength::FOUR;
                ++i;
            } else {
                res += UtfLength::THREE;
            }
        }
    }
    return res;
}

size_t ConvertRegionUtf16ToUtf8(const uint16_t *utf16In, uint8_t *utf8Out, size_t utf16Len, size_t utf8Len,
    size_t start)
{
    if (utf16In == nullptr || utf8Out == nullptr || utf8Len == 0) {
        return 0;
    }
    size_t utf8Pos = 0;
    size_t end = start + utf16Len;
    for (size_t i = start; i < end; ++i) {
        uint32_t codepoint = DecodeUTF16(utf16In, end, &i);
        if (codepoint == 0) {
            continue;
        }
        utf8Pos += EncodeUTF8(codepoint, utf8Out, utf8Len, utf8Pos);
    }
    return utf8Pos;
}

size_t DebuggerConvertRegionUtf16ToUtf8(const uint16_t* utf16In, uint8_t* utf8Out, size_t utf16Len, size_t utf8Len,
    size_t start)
{
    if (utf16In == nullptr || utf8Out == nullptr || utf8Len == 0) {
        return 0;
    }
    size_t utf8Pos = 0;
    size_t end = start + utf16Len;
    for (size_t i = start; i < end; ++i) {
        uint32_t codepoint = HandleAndDecodeInvalidUTF16(utf16In, end, &i);
        if (codepoint == 0) {
            continue;
        }
        utf8Pos += EncodeUTF8(codepoint, utf8Out, utf8Len, utf8Pos);
    }
    return utf8Pos;
}

// drop the tail bytes if the remain length can't fill the length it represents.
static size_t FixUtf8Len(const uint8_t* utf8, size_t utf8Len)
{
    size_t trimSize = 0;
    if (utf8Len >= 1 && utf8[utf8Len - 1] >= 0xC0) {
        // The last one char claim there are more than 1 byte next to it, it's invalid, so drop the last one.
        trimSize = 1;
    }
    if (utf8Len >= CONST_2 && utf8[utf8Len - CONST_2] >= 0xE0) {
        // The second to last char claim there are more than 2 bytes next to it, it's invalid, so drop the last two.
        trimSize = CONST_2;
    }
    if (utf8Len >= CONST_3 && utf8[utf8Len - CONST_3] >= 0xF0) {
        // The third to last char claim there are more than 3 bytes next to it, it's invalid, so drop the last three.
        trimSize = CONST_3;
    }
    return utf8Len - trimSize;
}

size_t Utf8ToUtf16Size(const uint8_t *utf8, size_t utf8Len)
{
    size_t safeUtf8Len = FixUtf8Len(utf8, utf8Len);
    size_t in_pos = 0;
    size_t res = 0;
    while (in_pos < safeUtf8Len) {
        uint8_t src = utf8[in_pos];
        switch (src & 0xF0) {
            case 0xF0: {
                const uint8_t c2 = utf8[++in_pos];
                const uint8_t c3 = utf8[++in_pos];
                const uint8_t c4 = utf8[++in_pos];
                uint32_t codePoint = ((src & LOW_3BITS) << OFFSET_18POS) | ((c2 & LOW_6BITS) << OFFSET_12POS) |
                    ((c3 & LOW_6BITS) << OFFSET_6POS) | (c4 & LOW_6BITS);
                if (codePoint >= SURROGATE_RAIR_START) {
                    res += CONST_2;
                } else {
                    res++;
                }
                in_pos++;
                break;
            }
            case 0xE0: {
                in_pos += CONST_3;
                res++;
                break;
            }
            case 0xD0:
            case 0xC0: {
                in_pos += CONST_2;
                res++;
                break;
            }
            default:
                do {
                    in_pos++;
                    res++;
                } while (in_pos < safeUtf8Len && utf8[in_pos] < 0x80);
                break;
        }
    }
    // The remain chars should be treated as single byte char.
    res += utf8Len - in_pos;
    return res;
}

#define CHECK_OUT_POS_RETURN(out_pos, utf16Len)     \
    do {                                            \
        if ((out_pos) >= (utf16Len) - 1) {          \
            return out_pos;                         \
        }                                           \
    } while (0)

size_t ConvertRegionUtf8ToUtf16(const uint8_t *utf8In, uint16_t *utf16Out, size_t utf8Len, size_t utf16Len)
{
    size_t safeUtf8Len = FixUtf8Len(utf8In, utf8Len);
    size_t in_pos = 0;
    size_t out_pos = 0;
    while (in_pos < safeUtf8Len && out_pos < utf16Len) {
        uint8_t src = utf8In[in_pos];
        switch (src & 0xF0) {
            case 0xF0: {
                const uint8_t c2 = utf8In[++in_pos];
                const uint8_t c3 = utf8In[++in_pos];
                const uint8_t c4 = utf8In[++in_pos];
                uint32_t codePoint = ((src & LOW_3BITS) << OFFSET_18POS) | ((c2 & LOW_6BITS) << OFFSET_12POS) |
                    ((c3 & LOW_6BITS) << OFFSET_6POS) | (c4 & LOW_6BITS);
                if (codePoint >= SURROGATE_RAIR_START) {
                    CHECK_OUT_POS_RETURN(out_pos, utf16Len);
                    codePoint -= SURROGATE_RAIR_START;
                    utf16Out[out_pos++] = static_cast<uint16_t>((codePoint >> OFFSET_10POS) | H_SURROGATE_START);
                    utf16Out[out_pos++] = static_cast<uint16_t>((codePoint & 0x3FF) | L_SURROGATE_START);
                } else {
                    utf16Out[out_pos++] = static_cast<uint16_t>(codePoint);
                }
                in_pos++;
                break;
            }
            case 0xE0: {
                const uint8_t c2 = utf8In[++in_pos];
                const uint8_t c3 = utf8In[++in_pos];
                utf16Out[out_pos++] = static_cast<uint16_t>(((src & LOW_4BITS) << OFFSET_12POS) |
                    ((c2 & LOW_6BITS) << OFFSET_6POS) | (c3 & LOW_6BITS));
                in_pos++;
                break;
            }
            case 0xD0:
            case 0xC0: {
                const uint8_t c2 = utf8In[++in_pos];
                utf16Out[out_pos++] = static_cast<uint16_t>(((src & LOW_5BITS) << OFFSET_6POS) | (c2 & LOW_6BITS));
                in_pos++;
                break;
            }
            default:
                do {
                    utf16Out[out_pos++] = static_cast<uint16_t>(utf8In[in_pos++]);
                } while (in_pos < safeUtf8Len && out_pos < utf16Len && utf8In[in_pos] < 0x80);
                break;
        }
    }
    // The remain chars should be treated as single byte char.
    while (in_pos < utf8Len && out_pos < utf16Len) {
        utf16Out[out_pos++] = static_cast<uint16_t>(utf8In[in_pos++]);
    }
    return out_pos;
}

std::u16string Str8ToStr16(const std::string& str)
{
    if (str.empty()) {
        return u"";
    }
    if (str == DEFAULT_STR) {
        return DEFAULT_U16STR;
    }
    const uint8_t* buf8 = reinterpret_cast<const uint8_t*>(str.c_str());
    size_t utf8Len = str.size();
    auto utf16Len = Utf8ToUtf16Size(buf8, utf8Len);
    std::unique_ptr<uint16_t[]> pBuf16 = std::make_unique<uint16_t[]>(utf16Len);
    uint16_t *buf16 = pBuf16.get();
    auto resultLen = ConvertRegionUtf8ToUtf16(buf8, buf16, utf8Len, utf16Len);
    if (resultLen == utf16Len) {
        return std::u16string(reinterpret_cast<const char16_t*>(buf16), utf16Len);
    }
    return u"";
}

// Illegal bytes are replaced with U+FFFD
std::u16string Str8DebugToStr16(const std::string& str)
{
    if (str.empty()) {
        return u"";
    }
    if (str == DEFAULT_STR) {
        return DEFAULT_U16STR;
    }
    icu::UnicodeString ustring = icu::UnicodeString::fromUTF8(str);
    return std::u16string(ustring.getBuffer(), static_cast<size_t>(ustring.length()));
}

std::string Str16ToStr8(const std::u16string& str)
{
    if (str.empty()) {
        return "";
    }
    if (str == DEFAULT_U16STR) {
        return DEFAULT_STR;
    }
    const uint16_t* buf16 = reinterpret_cast<const uint16_t*>(str.c_str());
    size_t utf16Len = str.size();
    auto utf8Len = Utf16ToUtf8Size(buf16, utf16Len) - 1;
    std::unique_ptr<uint8_t[]> pBuf8 = std::make_unique<uint8_t[]>(utf8Len);
    uint8_t *buf8 = pBuf8.get();
    auto resultLen = ConvertRegionUtf16ToUtf8(buf16, buf8, utf16Len, utf8Len, 0);
    if (resultLen == utf8Len) {
        return std::string(reinterpret_cast<const char*>(buf8), utf8Len);
    }
    return "";
}

// Unpaired surrogates are replace with U+FFFD
std::string Str16DebugToStr8(const std::u16string& str)
{
    if (str.empty()) {
        return "";
    }
    if (str == DEFAULT_U16STR) {
        return DEFAULT_STR;
    }
    const uint16_t* buf16 = reinterpret_cast<const uint16_t*>(str.c_str());
    size_t utf16Len = str.size();
    auto utf8Len = Utf16ToUtf8Size(buf16, utf16Len) - 1;
    std::unique_ptr<uint8_t[]> pBuf8 = std::make_unique<uint8_t[]>(utf8Len);
    uint8_t *buf8 = pBuf8.get();
    auto resultLen = DebuggerConvertRegionUtf16ToUtf8(buf16, buf8, utf16Len, utf8Len, 0);
    if (resultLen == utf8Len) {
        return std::string(reinterpret_cast<const char*>(buf8), utf8Len);
    }
    return "";
}
}  // namespace OHOS::Ace::UtfUtils
