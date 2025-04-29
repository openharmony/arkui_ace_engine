/**
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_UTF_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_UTF_H

#include <cstddef>
#include <cstdint>
#include <utility>
#include <string>

namespace OHOS::Ace {

/*
 * https://en.wikipedia.org/wiki/UTF-8
 *
 * N  Bits for     First        Last        Byte 1      Byte 2      Byte 3      Byte 4
 *    code point   code point   code point
 * 1  7            U+0000       U+007F      0xxxxxxx
 * 2  11           U+0080       U+07FF      110xxxxx    10xxxxxx
 * 3  16           U+0800       U+FFFF      1110xxxx    10xxxxxx    10xxxxxx
 * 4  21           U+10000      U+10FFFF    11110xxx    10xxxxxx    10xxxxxx    10xxxxxx
 */
constexpr size_t MASK1 = 0x80;
constexpr size_t MASK2 = 0x20;
constexpr size_t MASK3 = 0x10;

constexpr size_t MASK_4BIT = 0x0f;
constexpr size_t MASK_5BIT = 0x1f;
constexpr size_t MASK_6BIT = 0x3f;
constexpr size_t MASK_10BIT = 0x03ff;
constexpr size_t MASK_16BIT = 0xffff;

constexpr size_t DATA_WIDTH = 6;
constexpr size_t PAIR_ELEMENT_WIDTH = 16;

constexpr size_t HI_SURROGATE_MIN = 0xd800;
constexpr size_t HI_SURROGATE_MAX = 0xdbff;
constexpr size_t LO_SURROGATE_MIN = 0xdc00;
constexpr size_t LO_SURROGATE_MAX = 0xdfff;

constexpr size_t LO_SUPPLEMENTS_MIN = 0x10000;

constexpr size_t U16_LEAD = 0xd7c0;
constexpr size_t U16_TAIL = 0xdc00;

constexpr uint8_t MUTF8_1B_MAX = 0x7f;

constexpr uint16_t MUTF8_2B_MAX = 0x7ff;
constexpr uint8_t MUTF8_2B_FIRST = 0xc0;
constexpr uint8_t MUTF8_2B_SECOND = 0x80;

constexpr uint8_t MUTF8_3B_FIRST = 0xe0;
constexpr uint8_t MUTF8_3B_SECOND = 0x80;
constexpr uint8_t MUTF8_3B_THIRD = 0x80;

constexpr uint8_t MUTF8_4B_FIRST = 0xf0;
constexpr uint8_t MUTF8_4B_FIRST_MASK = 0xf8;

constexpr size_t MAX_U16 = 0xffff;
constexpr size_t CONST_2 = 2;
constexpr size_t CONST_3 = 3;
constexpr size_t CONST_4 = 4;
constexpr size_t CONST_6 = 6;
constexpr size_t CONST_12 = 12;

constexpr uint16_t DECODE_LEAD_LOW = 0xD800;
constexpr uint16_t DECODE_LEAD_HIGH = 0xDBFF;
constexpr uint16_t DECODE_TRAIL_LOW = 0xDC00;
constexpr uint16_t DECODE_TRAIL_HIGH = 0xDFFF;
constexpr uint32_t DECODE_FIRST_FACTOR = 0x400;
constexpr uint32_t DECODE_SECOND_FACTOR = 0x10000;
constexpr uint32_t UTF8_OFFSET = 6;
constexpr uint32_t UTF16_OFFSET = 10;
constexpr uint16_t SURROGATE_MASK = 0xF800;
constexpr uint16_t UTF16_REPLACEMENT_CHARACTER = 0xFFFD;

constexpr uint8_t UTF8_1B_MAX = 0x7f;

constexpr uint16_t UTF8_2B_MAX = 0x7ff;
constexpr uint8_t UTF8_2B_FIRST = 0xc0;
constexpr uint8_t UTF8_2B_SECOND = 0x80;
constexpr uint8_t UTF8_2B_THIRD = 0x3f;
constexpr uint8_t UTF8_2B_FIRST_MIN = 0xc2; // the minimum for 2 bytes is 128, which is 0xc280

constexpr uint16_t UTF8_3B_MAX = 0xffff;
constexpr uint8_t UTF8_3B_FIRST = 0xe0;
constexpr uint8_t UTF8_3B_SECOND = 0x80;
constexpr uint8_t UTF8_3B_THIRD = 0x80;
constexpr uint8_t UTF8_3B_SECOND_MIN = 0xa0; // the minimum for 3 bytes is 2048, which is 0xe0a080

constexpr uint8_t UTF8_4B_FIRST = 0xf0;
constexpr uint8_t UTF8_4B_SECOND_MIN = 0x90; // the minimum for 4 bytes is 65536, which is 0xf0908080

constexpr uint8_t BYTE_MASK = 0xbf;
constexpr uint8_t BYTE_MARK = 0x80;

enum UTF8BytePatterns {
    UTF8_TWO_BYTE_MASK = 0xE0,
    UTF8_TWO_BYTE_PATTERN = 0xC0,
    UTF8_THREE_BYTE_MASK = 0xF0,
    UTF8_THREE_BYTE_PATTERN = 0xE0,
    UTF8_FOUR_BYTE_MASK = 0xF8,
    UTF8_FOUR_BYTE_PATTERN = 0xF0,
    UTF8_MULTIBYTE_FOLLOWER = 0x80,
    UTF8_HIGH_BIT = 0x80
};

enum UTF16LEPatterns {
    UTF16LE_BOM_FF = 0xFF,
    UTF16LE_BOM_FE = 0xFE,
    UTF16LE_ZERO_BYTE = 0x00
};

enum INDEX {
    INDEX_ONE = 1,
    INDEX_TWO = 2,
    INDEX_THREE = 3
};

enum UtfLength : uint8_t { ONE = 1, TWO = 2, THREE = 3, FOUR = 4 };

const unsigned char FIRST_BYTE_MARK[7] = { 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };

std::pair<uint32_t, size_t> ConvertMUtf8ToUtf16Pair(const uint8_t* data, size_t maxBytes = 4);

size_t MUtf8ToUtf16Size(const uint8_t* mutf8, size_t mutf8Len);

size_t ConvertRegionUtf8ToUtf16(
    const uint8_t* utf8In, uint16_t* utf16Out, size_t utf8Len, size_t utf16Len, size_t start);

size_t DebuggerConvertRegionUtf16ToUtf8(const uint16_t* utf16In, uint8_t* utf8Out, size_t utf16Len, size_t utf8Len,
    size_t start);

void ConvertIllegalStr(std::string& str);

bool IsUTF8(std::string& data);

inline std::pair<uint16_t, uint16_t> SplitUtf16Pair(uint32_t pair)
{
    constexpr size_t P1_MASK = 0xffff;
    constexpr size_t P2_SHIFT = 16;
    return { pair >> P2_SHIFT, pair & P1_MASK };
}

} // namespace OHOS::Ace

#endif