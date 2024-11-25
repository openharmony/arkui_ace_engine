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

#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"

using namespace std::literals;
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
using std::literals::string_literals::operator""s;

class ReverseConvertorTest : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name:
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ReverseConvertorTest, SimpleTypes, TestSize.Level1)
{
    auto booleanResult = Converter::ArkValue<Ark_Boolean>(true);
    EXPECT_TRUE(booleanResult);

    booleanResult = Converter::ArkValue<Ark_Boolean>(false);
    EXPECT_FALSE(booleanResult);

    auto str = "abcd";
    auto stringResult = Converter::ArkValue<Ark_String>(str);
    EXPECT_EQ(stringResult.chars, str);
    EXPECT_EQ(stringResult.length, 4);

    auto strObj = "abcd"s;
    stringResult = Converter::ArkValue<Ark_String>(strObj);
    EXPECT_EQ(stringResult.chars, strObj.c_str());
    EXPECT_EQ(stringResult.length, 4);

    auto strView = "abcd"sv;
    stringResult = Converter::ArkValue<Ark_String>(strView);
    EXPECT_EQ(stringResult.chars, strView.data());
    EXPECT_EQ(stringResult.length, 4);

    stringResult = Converter::ArkValue<Ark_String>("abcd");
    EXPECT_EQ(stringResult.chars, "abcd"sv);
    EXPECT_EQ(stringResult.length, 4);

    auto numberResult = Converter::ArkValue<Ark_Number>(123);
    EXPECT_EQ(numberResult.tag, ARK_TAG_INT32);
    EXPECT_EQ(numberResult.i32, 123);

    numberResult = Converter::ArkValue<Ark_Number>(-123);
    EXPECT_EQ(numberResult.tag, ARK_TAG_INT32);
    EXPECT_EQ(numberResult.i32, -123);

    numberResult = Converter::ArkValue<Ark_Number>(123u);
    EXPECT_EQ(numberResult.tag, ARK_TAG_INT32);
    EXPECT_EQ(numberResult.i32, 123);

    numberResult = Converter::ArkValue<Ark_Number>(123.f);
    EXPECT_EQ(numberResult.tag, ARK_TAG_FLOAT32);
    EXPECT_EQ(numberResult.f32, 123.f);

    auto ptrResult = Converter::ArkValue<Ark_NativePointer>(&numberResult);
    EXPECT_EQ(ptrResult, &numberResult);

    auto funcResult = Converter::ArkValue<Ark_Function>(123);
    EXPECT_EQ(funcResult.id, 123);
}

/**
 * @tc.name:
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ReverseConvertorTest, ArrayTypes, TestSize.Level1)
{
    std::vector<std::string> vec{"abc", "1234"};
    Converter::ArkArrayHolder<Array_String> vecHolder(vec);
    auto stringArrayResult = vecHolder.ArkValue();
    EXPECT_EQ(stringArrayResult.length, 2);
    EXPECT_EQ(stringArrayResult.array[0].chars, "abc"sv);
    EXPECT_EQ(stringArrayResult.array[0].length, 3);
    EXPECT_EQ(stringArrayResult.array[1].chars, "1234"sv);
    EXPECT_EQ(stringArrayResult.array[1].length, 4);

    Converter::ArkArrayHolder<Array_String> listHolder({"def", "5678"});
    stringArrayResult = listHolder.ArkValue();
    EXPECT_EQ(stringArrayResult.length, 2);
    EXPECT_EQ(stringArrayResult.array[0].chars, "def"sv);
    EXPECT_EQ(stringArrayResult.array[0].length, 3);
    EXPECT_EQ(stringArrayResult.array[1].chars, "5678"sv);
    EXPECT_EQ(stringArrayResult.array[1].length, 4);

    std::string_view svArray[] = {"ghi", "9012"};
    Converter::ArkArrayHolder<Array_String> arrayHolder(svArray, 2);
    stringArrayResult = arrayHolder.ArkValue();
    EXPECT_EQ(stringArrayResult.length, 2);
    EXPECT_EQ(stringArrayResult.array[0].chars, "ghi"sv);
    EXPECT_EQ(stringArrayResult.array[0].length, 3);
    EXPECT_EQ(stringArrayResult.array[1].chars, "9012"sv);
    EXPECT_EQ(stringArrayResult.array[1].length, 4);

    auto asArray = std::array{Converter::ArkValue<Ark_String>("jkl"), Converter::ArkValue<Ark_String>("3456")};
    Converter::ArkArrayHolder<Array_String> arrayHolder1(asArray);
    stringArrayResult = arrayHolder1.ArkValue();
    EXPECT_EQ(stringArrayResult.length, 2);
    EXPECT_EQ(stringArrayResult.array[0].chars, "jkl"sv);
    EXPECT_EQ(stringArrayResult.array[0].length, 3);
    EXPECT_EQ(stringArrayResult.array[1].chars, "3456"sv);
    EXPECT_EQ(stringArrayResult.array[1].length, 4);

    // Check optional version
    auto optResult = listHolder.OptValue<Opt_Array_String>();
    EXPECT_EQ(optResult.tag, ARK_TAG_OBJECT);
    EXPECT_EQ(optResult.value.length, 2);
    EXPECT_EQ(optResult.value.array[0].chars, "def"sv);
    EXPECT_EQ(optResult.value.array[0].length, 3);
    EXPECT_EQ(optResult.value.array[1].chars, "5678"sv);
    EXPECT_EQ(optResult.value.array[1].length, 4);

    // Should be impossible to use temporary version
    static_assert(std::is_void_v<decltype(Converter::ArkArrayHolder<Array_String>({"Error!"}).ArkValue())>);
    static_assert(std::is_void_v<decltype(
        Converter::ArkArrayHolder<Array_String>({"Error!"}).OptValue<Opt_Array_String>())>);
}

/**
 * @tc.name:
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ReverseConvertorTest, OptionalTypes, TestSize.Level1)
{
    auto optNumber = Converter::ArkValue<Opt_Number>(std::optional<int>{});
    EXPECT_EQ(optNumber.tag, ARK_TAG_UNDEFINED);

    optNumber = Converter::ArkValue<Opt_Number>();
    EXPECT_EQ(optNumber.tag, ARK_TAG_UNDEFINED);

    optNumber = Converter::ArkValue<Opt_Number>(Ark_Empty());
    EXPECT_EQ(optNumber.tag, ARK_TAG_UNDEFINED);

    optNumber = Converter::ArkValue<Opt_Number>(std::nullopt);
    EXPECT_EQ(optNumber.tag, ARK_TAG_UNDEFINED);

    optNumber = Converter::ArkValue<Opt_Number>(std::optional(123));
    EXPECT_NE(optNumber.tag, ARK_TAG_UNDEFINED);
    EXPECT_EQ(optNumber.value.tag, ARK_TAG_INT32);
    EXPECT_EQ(optNumber.value.i32, 123);

    optNumber = Converter::ArkValue<Opt_Number>(123);
    EXPECT_NE(optNumber.tag, ARK_TAG_UNDEFINED);
    EXPECT_EQ(optNumber.value.tag, ARK_TAG_INT32);
    EXPECT_EQ(optNumber.value.i32, 123);

    optNumber = Converter::ArkValue<Opt_Number>(12.3f);
    EXPECT_NE(optNumber.tag, ARK_TAG_UNDEFINED);
    EXPECT_EQ(optNumber.value.tag, ARK_TAG_FLOAT32);
    EXPECT_EQ(optNumber.value.f32, 12.3f);

    auto ark = Converter::ArkValue<Ark_Number>(123);
    optNumber = Converter::ArkValue<Opt_Number>(ark);
    EXPECT_NE(optNumber.tag, ARK_TAG_UNDEFINED);
    EXPECT_EQ(optNumber.value.tag, ARK_TAG_INT32);
    EXPECT_EQ(optNumber.value.i32, 123);

    std::string testStr = "abc";
    auto optString = Converter::ArkValue<Opt_String>(testStr);
    EXPECT_NE(optString.tag, ARK_TAG_UNDEFINED);
    EXPECT_EQ(optString.value.chars, testStr.data());
    EXPECT_EQ(optString.value.length, 3);

    std::optional<std::string> testStrOpt = testStr;
    auto optString1 = Converter::ArkValue<Opt_String>(testStrOpt);
    EXPECT_NE(optString1.tag, ARK_TAG_UNDEFINED);
    EXPECT_EQ(optString1.value.chars, testStrOpt->data());
    EXPECT_EQ(optString1.value.length, 3);
}

/**
 * @tc.name:
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ReverseConvertorTest, UnionTypes, TestSize.Level1)
{
    auto unionResult = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(123);
    EXPECT_EQ(unionResult.selector, 0);
    EXPECT_EQ(unionResult.value0.tag, ARK_TAG_INT32);
    EXPECT_EQ(unionResult.value0.i32, 123);

    unionResult = Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("abc");
    EXPECT_EQ(unionResult.selector, 1);
    EXPECT_EQ(unionResult.value1.chars, "abc"s);

    auto optUnionResult = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(123);
    EXPECT_NE(optUnionResult.tag, ARK_TAG_UNDEFINED);
    EXPECT_EQ(optUnionResult.value.selector, 0);
    EXPECT_EQ(optUnionResult.value.value0.tag, ARK_TAG_INT32);
    EXPECT_EQ(optUnionResult.value.value0.i32, 123);

    std::string testStr = "abc";
    optUnionResult = Converter::ArkUnion<Opt_Union_Number_String, Ark_String>(testStr);
    EXPECT_NE(optUnionResult.tag, ARK_TAG_UNDEFINED);
    EXPECT_EQ(optUnionResult.value.selector, 1);
    EXPECT_EQ(optUnionResult.value.value1.chars, testStr.data());

    optUnionResult = Converter::ArkUnion<Opt_Union_Number_String>(Ark_Empty());
    EXPECT_EQ(optUnionResult.tag, ARK_TAG_UNDEFINED);
}
} // namespace OHOS::Ace::NG
