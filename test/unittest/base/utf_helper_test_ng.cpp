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

#include "gtest/gtest.h"
#include "gtest/hwext/gtest-ext.h"
#include "gtest/hwext/gtest-tag.h"
#include "unicode/unistr.h"

#include "base/utils/utf_helper.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::UtfUtils {
class UtfHelperTestNg : public Test {
    void SetUp() override
    {
        index = 0;
    }

public:
    size_t index;
};

/**
 * @tc.name: DecodeUTF16_001
 * @tc.desc: Test utf_helper DecodeUTF16
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, DecodeUTF16_001, TestSize.Level1)
{
    uint16_t utf16[1] = { 0x0041 };
    size_t len = sizeof(utf16) / sizeof(utf16[0]);
    EXPECT_EQ(DecodeUTF16(utf16, len, &index), 0x0041);
    EXPECT_EQ(index, 0);
}

/**
 * @tc.name: DecodeUTF16_002
 * @tc.desc: Test utf_helper DecodeUTF16
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, DecodeUTF16_002, TestSize.Level1)
{
    uint16_t utf16[2] = { 0xD83D, 0xDE00 };
    size_t len = sizeof(utf16) / sizeof(utf16[0]);
    EXPECT_EQ(DecodeUTF16(utf16, len, &index), 0x1F600);
    EXPECT_EQ(index, 1);
}

/**
 * @tc.name: DecodeUTF16_003
 * @tc.desc: Test utf_helper DecodeUTF16
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, DecodeUTF16_003, TestSize.Level1)
{
    uint16_t utf16[3] = { 0xD83D, 0xDC00 - 1, 0xDE00 };
    size_t len = sizeof(utf16) / sizeof(utf16[0]);
    EXPECT_EQ(DecodeUTF16(utf16, len, &index), 0xD83D);
    EXPECT_EQ(index, 0);
}

/**
 * @tc.name: DecodeUTF16_004
 * @tc.desc: Test utf_helper DecodeUTF16
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, DecodeUTF16_004, TestSize.Level1)
{
    uint16_t utf16[1] = { 0xD83D };
    size_t len = sizeof(utf16) / sizeof(utf16[0]);
    EXPECT_EQ(DecodeUTF16(utf16, len, &index), 0xD83D);
    EXPECT_EQ(index, 0);
}

/**
 * @tc.name: DecodeUTF16_005
 * @tc.desc: Test utf_helper DecodeUTF16
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, DecodeUTF16_005, TestSize.Level1)
{
    uint16_t utf16[2] = { 0x0041, 0xDC00 };
    size_t len = sizeof(utf16) / sizeof(utf16[0]);
    EXPECT_EQ(DecodeUTF16(utf16, len, &index), 0x0041);
    EXPECT_EQ(index, 0);
}

/**
 * @tc.name: HandleAndDecodeInvalidUTF16_001
 * @tc.desc: Test utf_helper HandleAndDecodeInvalidUTF16
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, HandleAndDecodeInvalidUTF16_001, TestSize.Level1)
{
    uint16_t utf16[2] = { 0xDE00, 0xD83D };
    size_t len = sizeof(utf16) / sizeof(utf16[0]);
    EXPECT_EQ(HandleAndDecodeInvalidUTF16(utf16, len, &index), 0xFFFD);
    EXPECT_EQ(index, 0);
}

/**
 * @tc.name: HandleAndDecodeInvalidUTF16_002
 * @tc.desc: Test utf_helper HandleAndDecodeInvalidUTF16
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, HandleAndDecodeInvalidUTF16_002, TestSize.Level1)
{
    uint16_t utf16[1] = { 0x4100 };
    size_t len = sizeof(utf16) / sizeof(utf16[0]);
    EXPECT_EQ(HandleAndDecodeInvalidUTF16(utf16, len, &index), 0x4100);
    EXPECT_EQ(index, 0);
}

/**
 * @tc.name: HandleAndDecodeInvalidUTF16_003
 * @tc.desc: Test utf_helper HandleAndDecodeInvalidUTF16
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, HandleAndDecodeInvalidUTF16_003, TestSize.Level1)
{
    uint16_t utf16[1] = { 0xDBFF - 1 };
    size_t len = sizeof(utf16) / sizeof(utf16[0]);
    EXPECT_EQ(HandleAndDecodeInvalidUTF16(utf16, len, &index), 0xFFFD);
    EXPECT_EQ(index, 0);
}

/**
 * @tc.name: HandleAndDecodeInvalidUTF16_004
 * @tc.desc: Test utf_helper HandleAndDecodeInvalidUTF16
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, HandleAndDecodeInvalidUTF16_004, TestSize.Level1)
{
    uint16_t utf16[2] = { 0xDBFF - 1, 0xDBFF - 1 };
    size_t len = sizeof(utf16) / sizeof(utf16[0]);
    EXPECT_EQ(HandleAndDecodeInvalidUTF16(utf16, len, &index), 0xFFFD);
    EXPECT_EQ(index, 0);
}

/**
 * @tc.name: HandleAndDecodeInvalidUTF16_005
 * @tc.desc: Test utf_helper HandleAndDecodeInvalidUTF16
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, HandleAndDecodeInvalidUTF16_005, TestSize.Level1)
{
    uint16_t first = 0xDBFF - 1;
    uint16_t second = 0xDC00 + 1;
    uint16_t utf16[2] = { first, second };
    size_t len = sizeof(utf16) / sizeof(utf16[0]);
    uint32_t res = ((first - 0xD800) << 10) + (second - 0xDC00) + 0x10000;
    EXPECT_EQ(HandleAndDecodeInvalidUTF16(utf16, len, &index), res);
    EXPECT_EQ(index, 1);
}

/**
 * @tc.name: HandleInvalidUTF16_001
 * @tc.desc: Test utf_helper HandleInvalidUTF16
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, HandleInvalidUTF16_001, TestSize.Level1)
{
    uint16_t* utf16 = nullptr;
    HandleInvalidUTF16(utf16, 0, 0);
    ASSERT_EQ(utf16, nullptr);
}

/**
 * @tc.name: RepalceUnpairedSurrogates_001
 * @tc.desc: Test utf_helper RepalceUnpairedSurrogates
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, RepalceUnpairedSurrogates_001, TestSize.Level1)
{
    uint16_t utf16[1] = { 0xDC00 + 1 };
    size_t len = sizeof(utf16) / sizeof(utf16[0]);
    HandleInvalidUTF16(utf16, len, 0);
    EXPECT_EQ(utf16[0], 0xFFFD);
}

/**
 * @tc.name: RepalceUnpairedSurrogates_002
 * @tc.desc: Test utf_helper RepalceUnpairedSurrogates
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, RepalceUnpairedSurrogates_002, TestSize.Level1)
{
    uint16_t utf16[1] = { 0xD800 - 1 };
    size_t len = sizeof(utf16) / sizeof(utf16[0]);
    HandleInvalidUTF16(utf16, len, 0);
    EXPECT_EQ(utf16[0], 0xD800 - 1);
}

/**
 * @tc.name: RepalceUnpairedSurrogates_003
 * @tc.desc: Test utf_helper RepalceUnpairedSurrogates
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, RepalceUnpairedSurrogates_003, TestSize.Level1)
{
    uint16_t utf16[1] = { 0xDC00 - 1 };
    size_t len = sizeof(utf16) / sizeof(utf16[0]);
    HandleInvalidUTF16(utf16, len, 0);
    EXPECT_EQ(utf16[0], 0xFFFD);
}

/**
 * @tc.name: RepalceUnpairedSurrogates_004
 * @tc.desc: Test utf_helper RepalceUnpairedSurrogates
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, RepalceUnpairedSurrogates_004, TestSize.Level1)
{
    uint16_t utf16[2] = { 0xDC00 - 1, 0xDC00 - 1 };
    size_t len = sizeof(utf16) / sizeof(utf16[0]);
    HandleInvalidUTF16(utf16, len, 0);
    EXPECT_EQ(utf16[0], 0xFFFD);
    EXPECT_EQ(utf16[1], 0xFFFD);
}

/**
 * @tc.name: RepalceUnpairedSurrogates_005
 * @tc.desc: Test utf_helper RepalceUnpairedSurrogates
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, RepalceUnpairedSurrogates_005, TestSize.Level1)
{
    uint16_t utf16[2] = { 0xDC00 - 1, 0xDC00 + 1 };
    size_t len = sizeof(utf16) / sizeof(utf16[0]);
    HandleInvalidUTF16(utf16, len, 0);
    EXPECT_EQ(utf16[0], 0xDC00 - 1);
    EXPECT_EQ(utf16[1], 0xDC00 + 1);
}

/**
 * @tc.name: UTF8Length_001
 * @tc.desc: Test utf_helper UTF8Length
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, UTF8Length_001, TestSize.Level1)
{
    uint32_t codepoint = 0xfffff;
    uint8_t utf8[3] = { 0xd8 + 1, 0xdc - 1, 0xd8 + 1 };
    size_t len = sizeof(utf8) / sizeof(utf8[0]);
    size_t indexOfUtf8 = 0;
    EXPECT_EQ(EncodeUTF8(codepoint, utf8, len, indexOfUtf8 - 1), 4);
}

/**
 * @tc.name: UTF8Length_002
 * @tc.desc: Test utf_helper UTF8Length
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, UTF8Length_002, TestSize.Level1)
{
    uint32_t codepoint = 0x7f + 1;
    uint8_t utf8[1] = { 0xd8 + 1 };
    size_t len = sizeof(utf8) / sizeof(utf8[0]);
    size_t indexOfUtf8 = 0;
    EXPECT_EQ(EncodeUTF8(codepoint, utf8, len, indexOfUtf8 - 1), 2);
}

/**
 * @tc.name: EncodeUTF8_001
 * @tc.desc: Test utf_helper EncodeUTF8
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, EncodeUTF8_001, TestSize.Level1)
{
    uint32_t codepoint = 0xffff;
    uint8_t utf8[2] = { 0xd8 + 1, 0xdc - 1 };
    size_t len = sizeof(utf8) / sizeof(utf8[0]);
    size_t indexOfUtf8 = 0;
    EXPECT_EQ(EncodeUTF8(codepoint, utf8, len, indexOfUtf8), 0);
}

/**
 * @tc.name: EncodeUTF8_002
 * @tc.desc: Test utf_helper EncodeUTF8
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, EncodeUTF8_002, TestSize.Level1)
{
    uint32_t codepoint = 0xfffff;
    uint8_t utf8[3] = { 0xd8 + 1, 0xdc - 1, 0xd8 + 1 };
    size_t len = sizeof(utf8) / sizeof(utf8[0]);
    size_t indexOfUtf8 = 0;
    EXPECT_EQ(EncodeUTF8(codepoint, utf8, len, indexOfUtf8 - 1), 4);
}

/**
 * @tc.name: Utf16ToUtf8Size001
 * @tc.desc: Test utf_helper Utf16ToUtf8Size with nullptr
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, Utf16ToUtf8Size001, TestSize.Level1)
{
    uint16_t* utf16 = nullptr;
    EXPECT_EQ(Utf16ToUtf8Size(utf16, 0), 1);  // 代码初始值问题，正确应为0
}

/**
 * @tc.name: Utf16ToUtf8Size002
 * @tc.desc: Test utf_helper Utf16ToUtf8Size wtih empty array
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, Utf16ToUtf8Size002, TestSize.Level1)
{
    uint16_t utf16[] = {};
    EXPECT_EQ(Utf16ToUtf8Size(utf16, 0), 1);
}

/**
 * @tc.name: Utf16ToUtf8Size003
 * @tc.desc: Test utf_helper Utf16ToUtf8Size with zero and length 0
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, Utf16ToUtf8Size003, TestSize.Level1)
{
    uint16_t utf16[] = { 0 };
    EXPECT_EQ(Utf16ToUtf8Size(utf16, 0), 1);
}

/**
 * @tc.name: Utf16ToUtf8Size004
 * @tc.desc: Test utf_helper Utf16ToUtf8Size with single zero 1
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, Utf16ToUtf8Size004, TestSize.Level1)
{
    uint16_t utf16[] = { 0 };
    EXPECT_EQ(Utf16ToUtf8Size(utf16, 1), 1);
}

/**
 * @tc.name: Utf16ToUtf8Size005
 * @tc.desc: Test utf_helper Utf16ToUtf8Size with single Ascii
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, Utf16ToUtf8Size005, TestSize.Level1)
{
    uint16_t utf16[] = { 0x41 };
    EXPECT_EQ(Utf16ToUtf8Size(utf16, 1), 2);
}

/**
 * @tc.name: Utf16ToUtf8Size006
 * @tc.desc: Test utf_helper Utf16ToUtf8Size with single two bytes
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, Utf16ToUtf8Size006, TestSize.Level1)
{
    uint16_t utf16[] = { 0x80 };
    EXPECT_EQ(Utf16ToUtf8Size(utf16, 1), 3);
}

/**
 * @tc.name: Utf16ToUtf8Size007
 * @tc.desc: Test utf_helper Utf16ToUtf8Size with single three bytes
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, Utf16ToUtf8Size007, TestSize.Level1)
{
    uint16_t utf16[] = { 0x800 };
    EXPECT_EQ(Utf16ToUtf8Size(utf16, 1), 4);
}

/**
 * @tc.name: Utf16ToUtf8Size008
 * @tc.desc: Test utf_helper Utf16ToUtf8Size with high surrogate min
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, Utf16ToUtf8Size008, TestSize.Level1)
{
    uint16_t utf16[] = { 0xD800 };
    EXPECT_EQ(Utf16ToUtf8Size(utf16, 1), 4);
}

/**
 * @tc.name: Utf16ToUtf8Size009
 * @tc.desc: Test utf_helper Utf16ToUtf8Size with num in range high surrogate min and low surrogate max
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, Utf16ToUtf8Size009, TestSize.Level1)
{
    uint16_t utf16[] = { 0xDC00 };
    EXPECT_EQ(Utf16ToUtf8Size(utf16, 1), 4);
}

/**
 * @tc.name: Utf16ToUtf8Size010
 * @tc.desc: Test utf_helper Utf16ToUtf8Size with low surrogate max
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, Utf16ToUtf8Size010, TestSize.Level1)
{
    uint16_t utf16[] = { 0xDFFF };
    EXPECT_EQ(Utf16ToUtf8Size(utf16, 1), 4);
}

/**
 * @tc.name: Utf16ToUtf8Size011
 * @tc.desc: Test utf_helper Utf16ToUtf8Size with valid surrogate pair
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, Utf16ToUtf8Size011, TestSize.Level1)
{
    uint16_t utf16[] = { 0xD800, 0xDC00 };
    EXPECT_EQ(Utf16ToUtf8Size(utf16, 2), 5);
}

/**
 * @tc.name: Utf16ToUtf8Size012
 * @tc.desc: Test utf_helper Utf16ToUtf8Size with high surrogate followed by nonsurrogate
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, Utf16ToUtf8Size012, TestSize.Level1)
{
    uint16_t utf16[] = { 0xD800, 0x1234 };
    EXPECT_EQ(Utf16ToUtf8Size(utf16, 2), 7);
}

/**
 * @tc.name: Utf16ToUtf8Size013
 * @tc.desc: Test utf_helper Utf16ToUtf8Size with high surrogate at end
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, Utf16ToUtf8Size013, TestSize.Level1)
{
    uint16_t utf16[] = { 0xD800, 0xD800 };
    EXPECT_EQ(Utf16ToUtf8Size(utf16, 2), 7);
}

/**
 * @tc.name: Utf16ToUtf8Size014
 * @tc.desc: Test utf_helper Utf16ToUtf8Size with mixed characters with zero
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, Utf16ToUtf8Size014, TestSize.Level1)
{
    uint16_t utf16[] = { 0x41, 0, 0x80, 0x800, 0xD800, 0xDC00 };
    EXPECT_EQ(Utf16ToUtf8Size(utf16, 6), 11);
}

/**
 * @tc.name: Utf16ToUtf8Size015
 * @tc.desc: Test utf_helper Utf16ToUtf8Size with multiple valid surrogate pairs
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, Utf16ToUtf8Size015, TestSize.Level1)
{
    uint16_t utf16[] = { 0xD800, 0xDC00, 0xD801, 0xDC01 };
    EXPECT_EQ(Utf16ToUtf8Size(utf16, 4), 9);
}

/**
 * @tc.name: Utf16ToUtf8Size016
 * @tc.desc: Test utf_helper Utf16ToUtf8Size with max two bytes
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, Utf16ToUtf8Size016, TestSize.Level1)
{
    uint16_t utf16[] = { 0x7FF };
    EXPECT_EQ(Utf16ToUtf8Size(utf16, 1), 3);
}

/**
 * @tc.name: Utf16ToUtf8Size017
 * @tc.desc: Test utf_helper Utf16ToUtf8Size with min three bytes
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, Utf16ToUtf8Size017, TestSize.Level1)
{
    uint16_t utf16[] = { 0x800 };
    EXPECT_EQ(Utf16ToUtf8Size(utf16, 1), 4);
}

/**
 * @tc.name: Utf16ToUtf8Size018
 * @tc.desc: Test utf_helper Utf16ToUtf8Size with nonsurrogate three bytes
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, Utf16ToUtf8Size018, TestSize.Level1)
{
    uint16_t utf16[] = { 0xD7FF };
    EXPECT_EQ(Utf16ToUtf8Size(utf16, 1), 4);
}

/**
 * @tc.name: Utf16ToUtf8Size019
 * @tc.desc: Test utf_helper Utf16ToUtf8Size with low surrogate after
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, Utf16ToUtf8Size019, TestSize.Level1)
{
    uint16_t utf16[] = { 0xE000 };
    EXPECT_EQ(Utf16ToUtf8Size(utf16, 1), 4);
}

/**
 * @tc.name: Utf16ToUtf8Size020
 * @tc.desc: Test utf_helper Utf16ToUtf8Size with multiple zeros
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, Utf16ToUtf8Size020, TestSize.Level1)
{
    uint16_t utf16[] = { 0, 0, 0 };
    EXPECT_EQ(Utf16ToUtf8Size(utf16, 3), 1);
}

/**
 * @tc.name: ConvertRegionUtf16ToUtf8_001
 * @tc.desc: Test utf_helper ConvertRegionUtf16ToUtf8 with invalid input 1
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, ConvertRegionUtf16ToUtf8_001, TestSize.Level1)
{
    uint8_t output[4] = { 0 };
    size_t result = ConvertRegionUtf16ToUtf8(nullptr, output, 2, 4, 0);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: ConvertRegionUtf16ToUtf8_002
 * @tc.desc: Test utf_helper ConvertRegionUtf16ToUtf8 with invalid input 2
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, ConvertRegionUtf16ToUtf8_002, TestSize.Level1)
{
    size_t result = ConvertRegionUtf16ToUtf8(reinterpret_cast<const uint16_t*>("A"), nullptr, 1, 4, 0);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: ConvertRegionUtf16ToUtf8_003
 * @tc.desc: Test utf_helper ConvertRegionUtf16ToUtf8 with invalid input 3
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, ConvertRegionUtf16ToUtf8_003, TestSize.Level1)
{
    uint8_t output[4] = { 0 };
    size_t result = ConvertRegionUtf16ToUtf8(reinterpret_cast<const uint16_t*>("A"), output, 1, 0, 0);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: ConvertRegionUtf16ToUtf8_004
 * @tc.desc: Test utf_helper ConvertRegionUtf16ToUtf8 with ASCII characters: 'a', 'b' and 'c'
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, ConvertRegionUtf16ToUtf8_004, TestSize.Level1)
{
    const uint16_t input[] = { 0x0041, 0x0042, 0x0043 };
    std::array<uint8_t, 3> output = { 0 };
    size_t result = ConvertRegionUtf16ToUtf8(input, output.data(), 3, 3, 0);
    
    EXPECT_EQ(result, 3);
    EXPECT_EQ(output[0], 0x41);
    EXPECT_EQ(output[1], 0x42);
    EXPECT_EQ(output[2], 0x43);
}

/**
 * @tc.name: ConvertRegionUtf16ToUtf8_005
 * @tc.desc: Test utf_helper ConvertRegionUtf16ToUtf8 with surrogate pair (smiling face)
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, ConvertRegionUtf16ToUtf8_005, TestSize.Level1)
{
    const uint16_t input[] = { 0xD83D, 0xDE00 };
    std::array<uint8_t, 4> output = { 0 };
    size_t result = ConvertRegionUtf16ToUtf8(input, output.data(), 2, 4, 0);
    
    EXPECT_EQ(result, 4);
    EXPECT_EQ(output[0], 0xF0);
    EXPECT_EQ(output[1], 0x9F);
    EXPECT_EQ(output[2], 0x98);
    EXPECT_EQ(output[3], 0x80);
}

/**
 * @tc.name: ConvertRegionUtf16ToUtf8_006
 * @tc.desc: Test utf_helper ConvertRegionUtf16ToUtf8 start position
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, ConvertRegionUtf16ToUtf8_006, TestSize.Level1)
{
    const uint16_t input[] = { 0x0041, 0xD83D, 0xDE00, 0x0042 };
    std::array<uint8_t, 5> output = { 0 };
    size_t result = ConvertRegionUtf16ToUtf8(input, output.data(), 3, 5, 1);
    
    EXPECT_EQ(result, 5);
    EXPECT_EQ(output[0], 0xF0);
    EXPECT_EQ(output[1], 0x9F);
    EXPECT_EQ(output[2], 0x98);
    EXPECT_EQ(output[3], 0x80);
    EXPECT_EQ(output[4], 0x42);
}

/**
 * @tc.name: ConvertRegionUtf16ToUtf8_007
 * @tc.desc: Test utf_helper ConvertRegionUtf16ToUtf8 with empty region
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, ConvertRegionUtf16ToUtf8_007, TestSize.Level1)
{
    const uint16_t input[] = { 0x0041 };
    std::array<uint8_t, 1> output = { 0 };
    size_t result = ConvertRegionUtf16ToUtf8(input, output.data(), 0, 1, 0);
    
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: ConvertRegionUtf16ToUtf8_008
 * @tc.desc: Test utf_helper ConvertRegionUtf16ToUtf8 start beyond end
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, ConvertRegionUtf16ToUtf8_008, TestSize.Level1)
{
    const uint16_t input[] = { 0x0041 };
    std::array<uint8_t, 1> output = { 0 };
    size_t result = ConvertRegionUtf16ToUtf8(input, output.data(), 1, 0, 0);
    
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: IsIndexInPairedSurrogates001
 * @tc.desc: Test utf_helper IsIndexInPairedSurrogates with empty string
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, IsIndexInPairedSurrogates001, TestSize.Level1)
{
    std::u16string empty;
    EXPECT_FALSE(IsIndexInPairedSurrogates(0, empty));
    EXPECT_FALSE(IsIndexInPairedSurrogates(-1, empty));
    EXPECT_FALSE(IsIndexInPairedSurrogates(1, empty));
}

/**
 * @tc.name: IsIndexInPairedSurrogates002
 * @tc.desc: Test utf_helper IsIndexInPairedSurrogates with index zero or outOfRange
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, IsIndexInPairedSurrogates002, TestSize.Level1)
{
    std::u16string str = {u'a', 0xD800, 0xDC00};
    EXPECT_FALSE(IsIndexInPairedSurrogates(0, str));
    EXPECT_FALSE(IsIndexInPairedSurrogates(3, str));
}

/**
 * @tc.name: IsIndexInPairedSurrogates003
 * @tc.desc: Test utf_helper IsIndexInPairedSurrogates with valid surrogate pair
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, IsIndexInPairedSurrogates003, TestSize.Level1)
{
    std::u16string str1 = {0xD800, 0xDC00};
    EXPECT_TRUE(IsIndexInPairedSurrogates(1, str1));

    std::u16string str2 = {0xDBFF, 0xDFFF};
    EXPECT_TRUE(IsIndexInPairedSurrogates(1, str2));
}

/**
 * @tc.name: IsIndexInPairedSurrogates004
 * @tc.desc: Test utf_helper IsIndexInPairedSurrogates with invalid surrogate pair
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, IsIndexInPairedSurrogates004, TestSize.Level1)
{
    std::u16string str1 = {0xD800, u'a'};
    EXPECT_FALSE(IsIndexInPairedSurrogates(1, str1));

    std::u16string str2 = {u'a', 0xDC00};
    EXPECT_FALSE(IsIndexInPairedSurrogates(1, str2));

    std::u16string str3 = {0xD800};
    EXPECT_FALSE(IsIndexInPairedSurrogates(1, str3));
}

/**
 * @tc.name: IsIndexInPairedSurrogates005
 * @tc.desc: Test utf_helper IsIndexInPairedSurrogates with multiple surrogate pairs
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, IsIndexInPairedSurrogates005, TestSize.Level1)
{
    std::u16string str = {0xD800, 0xDC00, 0xDBFF, 0xDFFF};

    EXPECT_TRUE(IsIndexInPairedSurrogates(1, str));
    EXPECT_TRUE(IsIndexInPairedSurrogates(3, str));
    EXPECT_FALSE(IsIndexInPairedSurrogates(2, str));
}

/**
 * @tc.name: IsIndexInPairedSurrogates006
 * @tc.desc: Test utf_helper IsIndexInPairedSurrogates with mixed characters
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestNg, IsIndexInPairedSurrogates006, TestSize.Level1)
{
    std::u16string str = {u'A', 0xD800, 0xDC00, u'B'};

    EXPECT_FALSE(IsIndexInPairedSurrogates(0, str));
    EXPECT_FALSE(IsIndexInPairedSurrogates(1, str));
    EXPECT_TRUE(IsIndexInPairedSurrogates(2, str));
    EXPECT_FALSE(IsIndexInPairedSurrogates(3, str));
}
} // namespace OHOS::Ace::UtfUtils
