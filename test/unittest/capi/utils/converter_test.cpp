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

#include <algorithm>

#include "gtest/gtest.h"

#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class ConvertorTest : public testing::Test {
};

/**
 * @tc.name:
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ConvertorTest, ArrayConversion, TestSize.Level1)
{
    std::vector<std::string> testArray = { "123", "abc", "%^&" };
    Converter::ArkArrayHolder<Array_String> holder(testArray);

    auto input = holder.ArkValue();
    auto result = Converter::Convert<std::vector<std::string>>(input);
    EXPECT_EQ(result, testArray);

    auto optInput = holder.OptValue<Opt_Array_String>();
    auto optResult = Converter::OptConvert<std::vector<std::string>>(optInput);
    EXPECT_TRUE(optResult.has_value());
    EXPECT_EQ(optResult.value(), testArray);
}

/**
 * @tc.name:
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ConvertorTest, OptArrayConversion, TestSize.Level1)
{
    std::vector<uint32_t> inputArray = { 0xFF000123, 0xFF000456, 0xFF000789 };
    std::vector<std::optional<Color>> testArray;
    std::transform(inputArray.begin(), inputArray.end(), std::back_inserter(testArray),
        [](auto val) {return Color(val);});
    Converter::ArkArrayHolder<Array_ResourceColor, Ark_Int32> holder(inputArray);

    auto input = holder.ArkValue();
    auto result = Converter::Convert<std::vector<std::optional<Color>>>(input);
    EXPECT_EQ(result, testArray);

    auto optInput = holder.OptValue<Opt_Array_ResourceColor>();
    auto optResult = Converter::OptConvert<std::vector<std::optional<Color>>>(optInput);
    EXPECT_TRUE(optResult.has_value());
    EXPECT_EQ(optResult.value(), testArray);
}

/**
 * @tc.name:
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ConvertorTest, ListConversion, TestSize.Level1)
{
    std::vector<std::string> testArray = { "123", "abc", "%^&" };
    Converter::ArkArrayHolder<Array_String> holder(testArray);

    auto input = holder.ArkValue();
    auto result = Converter::Convert<std::list<std::string>>(input);
    EXPECT_EQ(result.size(), testArray.size());
    auto iter = result.begin();
    for (size_t i = 0; i < testArray.size(); ++i) {
        EXPECT_EQ(testArray[i], *iter);
        iter++;
    }
}

/**
 * @tc.name:
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ConvertorTest, ListOptionalConversion, TestSize.Level1)
{
    std::vector<std::string> testArray = { "123", "abc", "%^&" };
    Converter::ArkArrayHolder<Array_String> holder(testArray);

    auto optInput = holder.OptValue<Opt_Array_String>();
    auto optResult = Converter::OptConvert<std::list<std::string>>(optInput);
    EXPECT_TRUE(optResult.has_value());
    const auto& result = optResult.value();
    EXPECT_EQ(result.size(), testArray.size());
    auto iter = result.begin();
    for (size_t i = 0; i < testArray.size(); ++i) {
        EXPECT_EQ(testArray[i], *iter);
        iter++;
    }
}

/**
 * @tc.name:
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ConvertorTest, GetOptTestValue, TestSize.Level1)
{
    auto unionValue = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(5.2f);
    auto value = Converter::ArkValue<Opt_Union_Number_String>(unionValue);
    std::optional<Ark_Union_Number_String> result = Converter::GetOpt(value);
    ASSERT_TRUE(result);
    auto convValue = Converter::OptConvert<Dimension>(result.value());
    ASSERT_TRUE(convValue);
    EXPECT_FLOAT_EQ(convValue.value().Value(), 5.2);
}

/**
 * @tc.name:
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ConvertorTest, GetOptTestEmpty, TestSize.Level1)
{
    auto value = Converter::ArkValue<Opt_Union_Number_String>();
    std::optional<Ark_Union_Number_String> result = Converter::GetOpt(value);
    ASSERT_FALSE(result);
}
} // namespace OHOS::Ace::NG
