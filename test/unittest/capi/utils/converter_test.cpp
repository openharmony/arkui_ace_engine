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

#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "../capi_gen140_compat.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr Ark_Int32 TEST_RESOURCE_ID = 17;
int32_t g_holdCount = 0;
int32_t g_releaseCount = 0;
int32_t g_syncCallCount = 0;
int32_t g_asyncCallCount = 0;
Ark_Int32 g_lastResourceId = 0;

void ResetCallbackState()
{
    g_holdCount = 0;
    g_releaseCount = 0;
    g_syncCallCount = 0;
    g_asyncCallCount = 0;
    g_lastResourceId = 0;
}

void HoldResource(Ark_Int32 resourceId)
{
    ++g_holdCount;
    g_lastResourceId = resourceId;
}

void ReleaseResource(Ark_Int32 resourceId)
{
    ++g_releaseCount;
    g_lastResourceId = resourceId;
}

void CallVoid(Ark_Int32 resourceId)
{
    ++g_asyncCallCount;
    g_lastResourceId = resourceId;
}

void CallVoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId)
{
    (void)vmContext;
    ++g_syncCallCount;
    g_lastResourceId = resourceId;
}

VoidCallback MakeVoidCallback()
{
    return {
        .resource = { .resourceId = TEST_RESOURCE_ID, .hold = HoldResource, .release = ReleaseResource },
        .call = CallVoid,
        .callSync = CallVoidSync,
    };
}
} // namespace

class ConvertorTest : public testing::Test {
};

/**
 * @tc.name:
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ConvertorTest, arrayConversionTest, TestSize.Level1)
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
HWTEST_F(ConvertorTest, optArrayConversionTest, TestSize.Level1)
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
HWTEST_F(ConvertorTest, listConversionTest, TestSize.Level1)
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
HWTEST_F(ConvertorTest, listOptionalConversionTest, TestSize.Level1)
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
HWTEST_F(ConvertorTest, getOptTestValue, TestSize.Level1)
{
    auto unionValue = Converter::ArkUnion<Ark_Union_Number_String, Ark_Float64>(5.2f);
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
HWTEST_F(ConvertorTest, getOptTestEmpty, TestSize.Level1)
{
    auto value = Converter::ArkValue<Opt_Union_Number_String>();
    std::optional<Ark_Union_Number_String> result = Converter::GetOpt(value);
    ASSERT_FALSE(result);
}

/**
 * @tc.name:
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ConvertorTest, callbackInvokerKeepsResourceAndInvokesCallbacks, TestSize.Level1)
{
    ResetCallbackState();
    {
        auto callback = MakeVoidCallback();
        auto syncInvoker = GetSyncInvoker(callback);
        auto asyncInvoker = GetAsyncInvoker(callback);

        EXPECT_EQ(g_holdCount, 2);
        syncInvoker();
        asyncInvoker();

        EXPECT_EQ(g_syncCallCount, 1);
        EXPECT_EQ(g_asyncCallCount, 1);
        EXPECT_EQ(g_lastResourceId, TEST_RESOURCE_ID);
    }
    EXPECT_EQ(g_releaseCount, 2);
}
} // namespace OHOS::Ace::NG
