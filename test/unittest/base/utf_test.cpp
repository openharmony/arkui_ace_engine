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

#include "base/utils/utf.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
class UtfTestNg : public Test {
    void SetUp() override
    {
        index = 0;
    }

public:
    size_t index;
};

/**
 * @tc.name:IsUTF8_001
 * @tc.desc: Test utf IsUTF8
 * @tc.type: FUNC
 */
HWTEST_F(UtfTestNg, IsUTF8_001, TestSize.Level1)
{
    std::string str = "";
    EXPECT_EQ(IsUTF8(str), false);
    std::string key = "hello";
    EXPECT_EQ(IsUTF8(key), true);
    std::string twoByteStr = "é";
    EXPECT_TRUE(IsUTF8(twoByteStr));
    std::string threeByteStr = "中";
    EXPECT_TRUE(IsUTF8(threeByteStr));

    std::string invalidTwoByteStr = "\xC3";
    EXPECT_FALSE(IsUTF8(invalidTwoByteStr));
    std::string invalidContinuationStr = "\xE4\xB8\x41";
    EXPECT_FALSE(IsUTF8(invalidContinuationStr));
    std::string mixedStr = "Hello\xC3\x28World";
    EXPECT_FALSE(IsUTF8(mixedStr));
}

/**
 * @tc.name:MUtf8ToUtf16Size_001
 * @tc.desc: Test utf MUtf8ToUtf16Size
 * @tc.type: FUNC
 */
HWTEST_F(UtfTestNg, MUtf8ToUtf16Size_001, TestSize.Level1)
{
    uint8_t utf8[3] = { 0xd8 + 1, 0xdc - 1, 0xd8 + 1 };
    size_t len = sizeof(utf8) / sizeof(utf8[0]);
    EXPECT_EQ(MUtf8ToUtf16Size(utf8, len), 2);
    const uint8_t mutf8[] = { 0xC2 };
    size_t mutf8Len = 1;
    EXPECT_EQ(MUtf8ToUtf16Size(mutf8, mutf8Len), 1);
}

/**
 * @tc.name:ConvertMUtf8ToUtf16Pair_001
 * @tc.desc: Test utf ConvertMUtf8ToUtf16Pair
 * @tc.type: FUNC
 */
HWTEST_F(UtfTestNg, ConvertMUtf8ToUtf16Pair_001, TestSize.Level1)
{
    uint32_t utf8Res;
    size_t byte;
    uint8_t utf8[3] = { 0xd8 + 1, 0xdc - 1, 0xd8 + 1 };
    size_t maxBytes = sizeof(utf8) / sizeof(utf8[0]);
    std::pair<uint32_t, size_t> result;
    result = ConvertMUtf8ToUtf16Pair(utf8, maxBytes);
    utf8Res = result.first;
    byte = result.second;
    EXPECT_EQ(utf8Res, 1627);
    EXPECT_EQ(byte, 2);
}

/**
 * @tc.name:ConvertRegionUtf8ToUtf16_001
 * @tc.desc: Test utf ConvertRegionUtf8ToUtf16
 * @tc.type: FUNC
 */
HWTEST_F(UtfTestNg, ConvertRegionUtf8ToUtf16_001, TestSize.Level1)
{
    uint8_t mutf8In[] = {0x48, 0x65, 0x6C, 0x6C, 0x6F};
    uint16_t utf16Out[5] = {0};
    size_t result = ConvertRegionUtf8ToUtf16(mutf8In, utf16Out, sizeof(mutf8In), sizeof(utf16Out)/sizeof(uint16_t), 0);
    
    EXPECT_EQ(result, 5);
    EXPECT_EQ(utf16Out[0], 0x0048);
    EXPECT_EQ(utf16Out[1], 0x0065);
    EXPECT_EQ(utf16Out[2], 0x006C);
    EXPECT_EQ(utf16Out[3], 0x006C);
    EXPECT_EQ(utf16Out[4], 0x006F);
}

/**
 * @tc.name: DebuggerConvertRegionUtf16ToUtf8_001
 * @tc.desc: Test utf DebuggerConvertRegionUtf16ToUtf8
 * @tc.type: FUNC
 */
HWTEST_F(UtfTestNg, DebuggerConvertRegionUtf16ToUtf8_001, TestSize.Level1)
{
    uint16_t utf16In[] = {0x0048, 0x0065, 0x006C, 0x006C, 0x006F};
    uint8_t utf8Out[10] = {0};
    size_t result = DebuggerConvertRegionUtf16ToUtf8(utf16In, utf8Out, 5, 10, 0);

    EXPECT_EQ(result, 5);
    EXPECT_EQ(utf8Out[0], 0x48);
    EXPECT_EQ(utf8Out[1], 0x65);
    EXPECT_EQ(utf8Out[2], 0x6C);
    EXPECT_EQ(utf8Out[3], 0x6C);
    EXPECT_EQ(utf8Out[4], 0x6F);
}

/**
 * @tc.name: DebuggerConvertRegionUtf16ToUtf8_002
 * @tc.desc: Test utf DebuggerConvertRegionUtf16ToUtf8
 * @tc.type: FUNC
 */
HWTEST_F(UtfTestNg, DebuggerConvertRegionUtf16ToUtf8_002, TestSize.Level1)
{
    uint16_t utf16In[] = {0xD83D, 0xDE00};
    uint8_t utf8Out[5] = {0};
    size_t result = DebuggerConvertRegionUtf16ToUtf8(utf16In, utf8Out, 2, 5, 0);

    EXPECT_EQ(result, 4);
    EXPECT_EQ(utf8Out[0], 0xF0);
    EXPECT_EQ(utf8Out[1], 0x9F);
    EXPECT_EQ(utf8Out[2], 0x98);
    EXPECT_EQ(utf8Out[3], 0x80);
}

/**
 * @tc.name: DebuggerConvertRegionUtf16ToUtf8_003
 * @tc.desc: Test utf DebuggerConvertRegionUtf16ToUtf8
 * @tc.type: FUNC
 */
HWTEST_F(UtfTestNg, DebuggerConvertRegionUtf16ToUtf8_003, TestSize.Level1)
{
    uint16_t utf16In[] = {0x0048, 0x0065};
    uint8_t utf8Out[5] = {0};

    size_t nullResult1 = DebuggerConvertRegionUtf16ToUtf8(nullptr, utf8Out, 2, 5, 0);
    EXPECT_EQ(nullResult1, 0);

    size_t nullResult2 = DebuggerConvertRegionUtf16ToUtf8(utf16In, nullptr, 2, 0, 0);
    EXPECT_EQ(nullResult2, 0);
}

/**
 * @tc.name: ConvertIllegalStr_001
 * @tc.desc: Test utf ConvertIllegalStr
 * @tc.type: FUNC
 */
HWTEST_F(UtfTestNg, ConvertIllegalStr_001, TestSize.Level1)
{
    std::string str = "Hello世界";
    std::string originalStr = str;
    ConvertIllegalStr(str);
    
    EXPECT_EQ(str, originalStr);
}

/**
 * @tc.name: ConvertIllegalStr_002
 * @tc.desc: Test utf ConvertIllegalStr
 * @tc.type: FUNC
 */
HWTEST_F(UtfTestNg, ConvertIllegalStr_002, TestSize.Level1)
{
    std::string str = "Hello\xC3\x28";
    ConvertIllegalStr(str);
    
    EXPECT_TRUE(IsUTF8(str));
    EXPECT_NE(str, "Hello\xC3\x28");
}

/**
 * @tc.name: ConvertIllegalStr_003
 * @tc.desc: Test utf ConvertIllegalStr
 * @tc.type: FUNC
 */
HWTEST_F(UtfTestNg, ConvertIllegalStr_003, TestSize.Level1)
{
    std::string str = "";
    ConvertIllegalStr(str);
    
    EXPECT_TRUE(str.empty());
}

/**
 * @tc.name: SplitUtf16Pair_001
 * @tc.desc: Test utf SplitUtf16Pair
 * @tc.type: FUNC
 */
HWTEST_F(UtfTestNg, SplitUtf16Pair_001, TestSize.Level1)
{
    uint32_t pair = 0xD83DDE00;
    auto result = SplitUtf16Pair(pair);
    
    EXPECT_EQ(result.first, 0xD83D);
    EXPECT_EQ(result.second, 0xDE00);
}

/**
 * @tc.name: SplitUtf16Pair_002
 * @tc.desc: Test utf SplitUtf16Pair
 * @tc.type: FUNC
 */
HWTEST_F(UtfTestNg, SplitUtf16Pair_002, TestSize.Level1)
{
    uint32_t pair = 0x00410042;
    auto result = SplitUtf16Pair(pair);
    
    EXPECT_EQ(result.first, 0x0041);
    EXPECT_EQ(result.second, 0x0042);
}
}