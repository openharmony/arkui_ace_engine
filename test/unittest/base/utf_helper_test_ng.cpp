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
} // namespace OHOS::Ace::UtfUtils
