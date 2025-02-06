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
class UtfHelperTestOneNg : public Test {
    void SetUp() override
    {
        index = 0;
    }

public:
    size_t index;
};

/**
 * @tc.name: DebuggerConvertRegionUtf16ToUtf8_001
 * @tc.desc: test DebuggerConvertRegionUtf16ToUtf8
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, DebuggerConvertRegionUtf16ToUtf8_001, TestSize.Level1)
{
    uint16_t utf16String[] = { 0x0048, 0x0065, 0x006C, 0x006C, 0x006F, 0x002C, 0x0020, 0x4E16, 0x754C };
    size_t utf16Len = sizeof(utf16String) / sizeof(utf16String[0]);
    uint8_t utf8Buffer[100];
    size_t res = DebuggerConvertRegionUtf16ToUtf8(utf16String, utf8Buffer, utf16Len, sizeof(utf8Buffer), 0);
    EXPECT_NE(res, 0);
}

/**
 * @tc.name: DebuggerConvertRegionUtf16ToUtf8_002
 * @tc.desc: test DebuggerConvertRegionUtf16ToUtf8
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, DebuggerConvertRegionUtf16ToUtf8_002, TestSize.Level1)
{
    uint16_t utf16String[] = { 0x0048, 0x0065, 0x006C, 0x006C, 0x006F };
    size_t utf16Len = sizeof(utf16String) / sizeof(utf16String[0]);
    uint8_t utf8Buffer[1];
    size_t utf8Len = 0;
    size_t res = DebuggerConvertRegionUtf16ToUtf8(utf16String, utf8Buffer, utf16Len, utf8Len, 0);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: DebuggerConvertRegionUtf16ToUtf8_003
 * @tc.desc: test DebuggerConvertRegionUtf16ToUtf8
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, DebuggerConvertRegionUtf16ToUtf8_003, TestSize.Level1)
{
    uint16_t utf16String[] = { 0x0048, 0x0065, 0x006C, 0x006C, 0x006F };
    size_t utf16Len = sizeof(utf16String) / sizeof(utf16String[0]);
    uint8_t* utf8Buffer = nullptr;
    size_t utf8Len = 100;
    size_t res = DebuggerConvertRegionUtf16ToUtf8(utf16String, utf8Buffer, utf16Len, utf8Len, 0);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: DebuggerConvertRegionUtf16ToUtf8_004
 * @tc.desc: test DebuggerConvertRegionUtf16ToUtf8
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, DebuggerConvertRegionUtf16ToUtf8_004, TestSize.Level1)
{
    const uint16_t* utf16String = nullptr;
    uint8_t utf8Buffer[100];
    size_t utf8Len = 100;
    size_t utf16Len = 5;
    size_t res = DebuggerConvertRegionUtf16ToUtf8(utf16String, utf8Buffer, utf16Len, utf8Len, 0);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: DebuggerConvertRegionUtf16ToUtf8_005
 * @tc.desc: null string
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, DebuggerConvertRegionUtf16ToUtf8_005, TestSize.Level1)
{
    const uint16_t* emptyInput = nullptr;
    uint8_t output[10] = { 0 };
    size_t result = DebuggerConvertRegionUtf16ToUtf8(emptyInput, output, 0, 10, 0);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: DebuggerConvertRegionUtf16ToUtf8_006
 * @tc.desc: singlebyte string
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, DebuggerConvertRegionUtf16ToUtf8_006, TestSize.Level1)
{
    const uint16_t input[] = { 0x0061 };
    uint8_t output[10] = { 0 };
    size_t result = DebuggerConvertRegionUtf16ToUtf8(input, output, 1, 10, 0);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(output[0], 0x61);
}

/**
 * @tc.name: DebuggerConvertRegionUtf16ToUtf8_007
 * @tc.desc: twobyte string
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, DebuggerConvertRegionUtf16ToUtf8_007, TestSize.Level1)
{
    const uint16_t input[] = { 0xD800, 0xDC00 };
    uint8_t output[10] = { 0 };
    size_t result = DebuggerConvertRegionUtf16ToUtf8(input, output, 2, 10, 0);
    EXPECT_EQ(result, 4);
}

/**
 * @tc.name: DebuggerConvertRegionUtf16ToUtf8_008
 * @tc.desc: twobyte string
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, DebuggerConvertRegionUtf16ToUtf8_008, TestSize.Level1)
{
    const uint16_t input[] = { 0xD800, 0xD800 };
    uint8_t output[10] = { 0 };
    size_t result = DebuggerConvertRegionUtf16ToUtf8(input, output, 2, 10, 0);
    EXPECT_EQ(result, 6);
}

/**
 * @tc.name: Str8DebugToStr16_001
 * @tc.desc: test Str8DebugToStr16
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, Str8DebugToStr16_001, TestSize.Level1)
{
    std::string emptyStr = "";
    std::u16string result = Str8DebugToStr16(emptyStr);
    EXPECT_EQ(result, u"");
}

/**
 * @tc.name: Str8DebugToStr16_002
 * @tc.desc: test Str8DebugToStr16
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, Str8DebugToStr16_002, TestSize.Level1)
{
    std::string str = "Hello";
    std::u16string result = Str8DebugToStr16(str);
    EXPECT_EQ(result, u"Hello");
}

/**
 * @tc.name: Str8DebugToStr16_003
 * @tc.desc: test Str8DebugToStr16
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, Str8DebugToStr16_003, TestSize.Level1)
{
    std::string str = DEFAULT_STR;
    std::u16string result = Str8DebugToStr16(str);
    EXPECT_EQ(result, DEFAULT_U16STR);
}

/**
 * @tc.name: Str8DebugToStr16_004
 * @tc.desc: test Str8DebugToStr16
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, Str8DebugToStr16_004, TestSize.Level1)
{
    std::string str = "Word";
    std::u16string result = Str8DebugToStr16(str);
    EXPECT_NE(result, DEFAULT_U16STR);
}

/**
 * @tc.name: Str16DebugToStr8_001
 * @tc.desc: test Str16DebugToStr8
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, Str16DebugToStr8_001, TestSize.Level1)
{
    std::u16string emptyStr = u"";
    std::string result = Str16DebugToStr8(emptyStr);
    EXPECT_EQ(result, "");
}

/**
 * @tc.name: Str16DebugToStr8_002
 * @tc.desc: test Str16DebugToStr8
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, Str16DebugToStr8_002, TestSize.Level1)
{
    std::u16string str = u"Hello";
    std::string result = Str16DebugToStr8(str);
    EXPECT_EQ(result, "Hello");
}

/**
 * @tc.name: Str16DebugToStr8_003
 * @tc.desc: test Str16DebugToStr8
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, Str16DebugToStr8_003, TestSize.Level1)
{
    std::u16string str = DEFAULT_U16STR;
    std::string result = Str16DebugToStr8(str);
    EXPECT_EQ(result, DEFAULT_STR);
}

/**
 * @tc.name: Str16DebugToStr8_004
 * @tc.desc: test Str16DebugToStr8
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, Str16DebugToStr8_004, TestSize.Level1)
{
    std::u16string str = u"Word";
    std::string result = Str16DebugToStr8(str);
    EXPECT_NE(result, DEFAULT_STR);
}

/**
 * @tc.name: Str16DebugToStr8_005
 * @tc.desc: test Str16DebugToStr8
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, Str16DebugToStr8_005, TestSize.Level1)
{
    std::u16string str = u"Word";
    std::string result = Str16DebugToStr8(str);
    EXPECT_EQ(result, "Word");
}

/**
 * @tc.name: Utf8ToUtf16Size_001
 * @tc.desc: test Utf8ToUtf16Size
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, Utf8ToUtf16Size_001, TestSize.Level1)
{
    uint8_t utf8[] = { 0xF0, 0x9F, 0x98, 0x80 };
    size_t utf8Len = sizeof(utf8) / sizeof(uint8_t);
    size_t result = Utf8ToUtf16Size(utf8, utf8Len);
    EXPECT_EQ(result, 2);
}

/**
 * @tc.name: Utf8ToUtf16Size_002
 * @tc.desc: test Utf8ToUtf16Size
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, Utf8ToUtf16Size_002, TestSize.Level1)
{
    uint8_t utf8[] = { 0xF0, 0x80, 0x80, 0x80 };
    size_t utf8Len = sizeof(utf8) / sizeof(uint8_t);
    size_t result = Utf8ToUtf16Size(utf8, utf8Len);
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: Utf8ToUtf16Size_003
 * @tc.desc: test Utf8ToUtf16Size
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, Utf8ToUtf16Size_003, TestSize.Level1)
{
    uint8_t utf8[] = { 0xC3, 0x82 };
    size_t utf8Len = sizeof(utf8) / sizeof(uint8_t);
    size_t result = Utf8ToUtf16Size(utf8, utf8Len);
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: ConvertRegionUtf8ToUtf16_001
 * @tc.desc: test ConvertRegionUtf8ToUtf16
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, ConvertRegionUtf8ToUtf16_001, TestSize.Level1)
{
    uint8_t utf8[] = { 0xF0, 0x9F, 0x98, 0x80 };
    size_t utf8Len = sizeof(utf8) / sizeof(uint8_t);
    uint16_t utf16[2];
    size_t utf16Len = sizeof(utf16) / sizeof(uint16_t);
    size_t result = ConvertRegionUtf8ToUtf16(utf8, utf16, utf8Len, utf16Len);
    EXPECT_EQ(result, 2);
}

/**
 * @tc.name: ConvertRegionUtf8ToUtf16_002
 * @tc.desc: test ConvertRegionUtf8ToUtf16
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, ConvertRegionUtf8ToUtf16_002, TestSize.Level1)
{
    uint8_t utf8[] = { 0xF0, 0x80, 0x80, 0x80 };
    size_t utf8Len = sizeof(utf8) / sizeof(uint8_t);
    uint16_t utf16[1];
    size_t utf16Len = sizeof(utf16) / sizeof(uint16_t);
    size_t result = ConvertRegionUtf8ToUtf16(utf8, utf16, utf8Len, utf16Len);
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: ConvertRegionUtf8ToUtf16_003
 * @tc.desc: test ConvertRegionUtf8ToUtf16
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, ConvertRegionUtf8ToUtf16_003, TestSize.Level1)
{
    uint8_t utf8[] = { 0xC3, 0x81 };
    size_t utf8Len = sizeof(utf8) / sizeof(uint8_t);
    uint16_t utf16[1];
    size_t utf16Len = sizeof(utf16) / sizeof(uint16_t);
    size_t result = ConvertRegionUtf8ToUtf16(utf8, utf16, utf8Len, utf16Len);
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: ConvertRegionUtf8ToUtf16_004
 * @tc.desc: test ConvertRegionUtf8ToUtf16
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, ConvertRegionUtf8ToUtf16_004, TestSize.Level1)
{
    const uint8_t utf8Data[] = { 0xF0, 0x90 };
    size_t utf8Len = sizeof(utf8Data) / sizeof(utf8Data[0]);
    uint16_t utf16Data[10] = { 0 };
    size_t utf16Len = sizeof(utf16Data) / sizeof(utf16Data[0]);
    size_t result = ConvertRegionUtf8ToUtf16(utf8Data, utf16Data, utf8Len, utf16Len);
    EXPECT_EQ(result, 2);
}

/**
 * @tc.name: ConvertRegionUtf8ToUtf16_005
 * @tc.desc: test ConvertRegionUtf8ToUtf16
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, ConvertRegionUtf8ToUtf16_005, TestSize.Level1)
{
    uint8_t utf8[] = {};
    size_t utf8Len = sizeof(utf8) / sizeof(uint8_t);
    uint16_t utf16[10];
    size_t utf16Len = sizeof(utf16) / sizeof(uint16_t);
    size_t result = ConvertRegionUtf8ToUtf16(utf8, utf16, utf8Len, utf16Len);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: FixUtf8Len_001
 * @tc.desc: test FixUtf8Len
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, FixUtf8Len_001, TestSize.Level1)
{
    const uint8_t utf8Data[] = { 0xC2 };
    size_t utf8Len = sizeof(utf8Data) / sizeof(utf8Data[0]);
    uint16_t utf16Data[10] = { 0 };
    size_t utf16Len = sizeof(utf16Data) / sizeof(utf16Data[0]);
    size_t result = ConvertRegionUtf8ToUtf16(utf8Data, utf16Data, utf8Len, utf16Len);
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: FixUtf8Len_002
 * @tc.desc: test FixUtf8Len
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, FixUtf8Len_002, TestSize.Level1)
{
    const uint8_t utf8Data[] = { 0xF0, 0x90 };
    size_t utf8Len = sizeof(utf8Data) / sizeof(utf8Data[0]);
    uint16_t utf16Data[10] = { 0 };
    size_t utf16Len = sizeof(utf16Data) / sizeof(utf16Data[0]);
    size_t result = ConvertRegionUtf8ToUtf16(utf8Data, utf16Data, utf8Len, utf16Len);
    EXPECT_EQ(result, 2);
}

/**
 * @tc.name: FixUtf8Len_003
 * @tc.desc: test FixUtf8Len
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, FixUtf8Len_003, TestSize.Level1)
{
    const uint8_t utf8Data[] = { 0xF0, 0x90, 0x80 };
    size_t utf8Len = sizeof(utf8Data) / sizeof(utf8Data[0]);
    uint16_t utf16Data[10] = { 0 };
    size_t utf16Len = sizeof(utf16Data) / sizeof(utf16Data[0]);
    size_t result = ConvertRegionUtf8ToUtf16(utf8Data, utf16Data, utf8Len, utf16Len);
    EXPECT_EQ(result, 3);
}

/**
 * @tc.name: FixUtf8Len_004
 * @tc.desc: test FixUtf8Len
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, FixUtf8Len_004, TestSize.Level1)
{
    const uint8_t utf8Data[] = { 0x48 };
    size_t utf8Len = sizeof(utf8Data) / sizeof(utf8Data[0]);
    uint16_t utf16Data[10] = { 0 };
    size_t utf16Len = sizeof(utf16Data) / sizeof(utf16Data[0]);
    size_t result = ConvertRegionUtf8ToUtf16(utf8Data, utf16Data, utf8Len, utf16Len);
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: FixUtf8Len_005
 * @tc.desc: test FixUtf8Len
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, FixUtf8Len_005, TestSize.Level1)
{
    const uint8_t utf8Data[] = { 0x48, 0xC2 };
    size_t utf8Len = sizeof(utf8Data) / sizeof(utf8Data[0]);
    uint16_t utf16Data[10] = { 0 };
    size_t utf16Len = sizeof(utf16Data) / sizeof(utf16Data[0]);
    size_t result = ConvertRegionUtf8ToUtf16(utf8Data, utf16Data, utf8Len, utf16Len);
    EXPECT_NE(result, 1);
}

/**
 * @tc.name: FixUtf8Len_006
 * @tc.desc: test FixUtf8Len
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, FixUtf8Len_006, TestSize.Level1)
{
    const uint8_t utf8Data[] = { 0x48, 0x65, 0xC2 };
    size_t utf8Len = sizeof(utf8Data) / sizeof(utf8Data[0]);
    uint16_t utf16Data[10] = { 0 };
    size_t utf16Len = sizeof(utf16Data) / sizeof(utf16Data[0]);
    size_t result = ConvertRegionUtf8ToUtf16(utf8Data, utf16Data, utf8Len, utf16Len);
    EXPECT_EQ(result, 3);
}

/**
 * @tc.name: FixUtf8Len_007
 * @tc.desc: empty string
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, FixUtf8Len_007, TestSize.Level1)
{
    const uint8_t* emptyInput = nullptr;
    uint16_t output[10] = { 0 };
    size_t result = ConvertRegionUtf8ToUtf16(emptyInput, output, 0, 10);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: FixUtf8Len_008
 * @tc.desc: singleByte string
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, FixUtf8Len_008, TestSize.Level1)
{
    const uint8_t* input = reinterpret_cast<const uint8_t*>(u8"a");
    uint16_t output[10] = { 0 };
    size_t result = ConvertRegionUtf8ToUtf16(input, output, 1, 10);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(output[0], 'a');
}

/**
 * @tc.name: FixUtf8Len_009
 * @tc.desc: mixed string
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, FixUtf8Len_009, TestSize.Level1)
{
    const uint8_t* input = reinterpret_cast<const uint8_t*>(u8"Hello, 世界!");
    uint16_t output[50] = { 0 };
    size_t result = ConvertRegionUtf8ToUtf16(input, output, strlen(reinterpret_cast<const char*>(input)), 50);
    EXPECT_EQ(result, 10);
}

/**
 * @tc.name: FixUtf8Len_010
 * @tc.desc: invalid string
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, FixUtf8Len_010, TestSize.Level1)
{
    const uint8_t* input = reinterpret_cast<const uint8_t*>(u8"XXXX");
    uint16_t output[10] = { 0 };
    size_t result = ConvertRegionUtf8ToUtf16(input, output, 4, 10);
    EXPECT_EQ(result, 4);
}

/**
 * @tc.name: ConvertRegionUtf16ToUtf8_001
 * @tc.desc: test ConvertRegionUtf16ToUtf8
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, ConvertRegionUtf16ToUtf8_001, TestSize.Level1)
{
    uint16_t utf16String[] = { 0x0048, 0x0065, 0x006C, 0x006C, 0x006F };
    size_t utf16Len = sizeof(utf16String) / sizeof(utf16String[0]);
    uint8_t utf8Buffer[1];
    size_t utf8Len = 0;
    size_t res = ConvertRegionUtf16ToUtf8(utf16String, utf8Buffer, utf16Len, utf8Len, 0);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: Utf16ToUtf8Size001
 * @tc.desc: Test utf_helper Utf16ToUtf8Size
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, Utf16ToUtf8Size_001, TestSize.Level1)
{
    uint16_t utf16[1] = { 0xd800 + 1 };
    size_t len = sizeof(utf16) / sizeof(utf16[0]);
    EXPECT_EQ(Utf16ToUtf8Size(utf16, len), 4);
}

/**
 * @tc.name: Utf16ToUtf8Size_002
 * @tc.desc: Test utf_helper Utf16ToUtf8Size
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, Utf16ToUtf8Size_002, TestSize.Level1)
{
    uint16_t utf16[1] = { 0 };
    size_t len = sizeof(utf16) / sizeof(utf16[0]);
    EXPECT_EQ(Utf16ToUtf8Size(utf16, len), 1);
}

/**
 * @tc.name: Utf16ToUtf8Size_003
 * @tc.desc: Test utf_helper Utf16ToUtf8Size
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, Utf16ToUtf8Size_003, TestSize.Level1)
{
    uint16_t utf16[1] = { 0x7ff - 1 };
    size_t len = sizeof(utf16) / sizeof(utf16[0]);
    EXPECT_EQ(Utf16ToUtf8Size(utf16, len), 3);
}

/**
 * @tc.name: Utf16ToUtf8Size_004
 * @tc.desc: Test utf_helper Utf16ToUtf8Size
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, Utf16ToUtf8Size_004, TestSize.Level1)
{
    uint16_t utf16[1] = { 0xd800 + 1 };
    size_t len = sizeof(utf16) / sizeof(utf16[0]);
    EXPECT_EQ(Utf16ToUtf8Size(utf16, len), 4);
}

/**
 * @tc.name: Utf16ToUtf8Size_005
 * @tc.desc: Test utf_helper Utf16ToUtf8Size
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, Utf16ToUtf8Size_005, TestSize.Level1)
{
    uint16_t utf16[2] = { 0xd800 + 1, 0xdc00 + 1 };
    size_t len = sizeof(utf16) / sizeof(utf16[0]);
    EXPECT_EQ(Utf16ToUtf8Size(utf16, len), 5);
}

/**
 * @tc.name: Utf16ToUtf8Size_006
 * @tc.desc: Test utf_helper Utf16ToUtf8Size
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, Utf16ToUtf8Size_006, TestSize.Level1)
{
    uint16_t utf16[2] = { 0xd800 + 1, 0xdc00 - 1 };
    size_t len = sizeof(utf16) / sizeof(utf16[0]);
    EXPECT_EQ(Utf16ToUtf8Size(utf16, len), 7);
}

/**
 * @tc.name: Utf16ToUtf8Size_007
 * @tc.desc: Test utf_helper Utf16ToUtf8Size
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, Utf16ToUtf8Size_007, TestSize.Level1)
{
    uint16_t utf16[2] = { 0xd800 + 1, 0xdfff + 1 };
    size_t len = sizeof(utf16) / sizeof(utf16[0]);
    EXPECT_EQ(Utf16ToUtf8Size(utf16, len), 7);
}

/**
 * @tc.name: IsIndexInPairedSurrogates_001
 * @tc.desc: test utf_helper.cpp: justify that index is in paired surrogates
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, IsIndexInPairedSurrogates_001, TestSize.Level1)
{
    std::u16string emojiStr = u"";
    ASSERT_EQ(UtfUtils::IsIndexInPairedSurrogates(-1, emojiStr), false);
    ASSERT_EQ(UtfUtils::IsIndexInPairedSurrogates(0, emojiStr), false);
    ASSERT_EQ(UtfUtils::IsIndexInPairedSurrogates(1, emojiStr), false);
    ASSERT_EQ(UtfUtils::IsIndexInPairedSurrogates(2, emojiStr), false);
}

/**
 * @tc.name: IsIndexInPairedSurrogates_002
 * @tc.desc: test utf_helper.cpp: justify that index is in paired surrogates
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, IsIndexInPairedSurrogates_002, TestSize.Level1)
{
    std::u16string emojiStr = u"哈哈😁";
    int32_t len = static_cast<int32_t>(emojiStr.length());
    ASSERT_EQ(UtfUtils::IsIndexInPairedSurrogates(-1, emojiStr), false);
    ASSERT_EQ(UtfUtils::IsIndexInPairedSurrogates(0, emojiStr), false);
    ASSERT_EQ(UtfUtils::IsIndexInPairedSurrogates(1, emojiStr), false);
    ASSERT_EQ(UtfUtils::IsIndexInPairedSurrogates(2, emojiStr), false);
    ASSERT_EQ(UtfUtils::IsIndexInPairedSurrogates(len - 1, emojiStr), true);
    ASSERT_EQ(UtfUtils::IsIndexInPairedSurrogates(len, emojiStr), false);
    ASSERT_EQ(UtfUtils::IsIndexInPairedSurrogates(len + 1, emojiStr), false);
}

/**
 * @tc.name: IsIndexInPairedSurrogates_003
 * @tc.desc: test utf_helper.cpp: justify that index is in paired surrogates when a emoji is truncated
 * @tc.type: FUNC
 */
HWTEST_F(UtfHelperTestOneNg, IsIndexInPairedSurrogates_003, TestSize.Level1)
{
    std::u16string emojiStr = u"哈哈😁😁";
    int32_t len = static_cast<int32_t>(emojiStr.length());
    std::u16string subEmojiStr = emojiStr.substr(0, len - 1);
    ASSERT_EQ(UtfUtils::IsIndexInPairedSurrogates(0, subEmojiStr), false);
    ASSERT_EQ(UtfUtils::IsIndexInPairedSurrogates(1, subEmojiStr), false);
    ASSERT_EQ(UtfUtils::IsIndexInPairedSurrogates(2, subEmojiStr), false);
    ASSERT_EQ(UtfUtils::IsIndexInPairedSurrogates(3, subEmojiStr), true);
    ASSERT_EQ(UtfUtils::IsIndexInPairedSurrogates(len - 1, subEmojiStr), false);
    ASSERT_EQ(UtfUtils::IsIndexInPairedSurrogates(len, subEmojiStr), false);
    ASSERT_EQ(UtfUtils::IsIndexInPairedSurrogates(len + 1, subEmojiStr), false);
}

} // namespace OHOS::Ace::UtfUtils