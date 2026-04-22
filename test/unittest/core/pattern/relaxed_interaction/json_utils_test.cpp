/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "base/json/json_util.h"
#include "core/components_ng/relaxed_interaction/utils/json_utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class JsonUtilsTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
};

class JsonUtilsIsUintTest : public JsonUtilsTest {};

HWTEST_F(JsonUtilsIsUintTest, IsUint_NullJson, TestSize.Level1)
{
    auto json = JsonUtil::Create(true);
    EXPECT_FALSE(JsonUtils::IsUint(json));
}

HWTEST_F(JsonUtilsIsUintTest, IsUint_StringJson, TestSize.Level1)
{
    auto json = JsonUtil::ParseJsonString("\"test_string\"");
    EXPECT_FALSE(JsonUtils::IsUint(json));
}

HWTEST_F(JsonUtilsIsUintTest, IsUint_ObjectJson, TestSize.Level1)
{
    auto json = JsonUtil::ParseJsonString("{\"key\": \"value\"}");
    EXPECT_FALSE(JsonUtils::IsUint(json));
}

HWTEST_F(JsonUtilsIsUintTest, IsUint_ArrayJson, TestSize.Level1)
{
    auto json = JsonUtil::ParseJsonString("[1, 2, 3]");
    EXPECT_FALSE(JsonUtils::IsUint(json));
}

HWTEST_F(JsonUtilsIsUintTest, IsUint_IntegerJson, TestSize.Level1)
{
    auto json = JsonUtil::ParseJsonString("42");
    EXPECT_TRUE(JsonUtils::IsUint(json));
}

HWTEST_F(JsonUtilsIsUintTest, IsUint_NegativeIntegerJson, TestSize.Level1)
{
    auto json = JsonUtil::ParseJsonString("-42");
    EXPECT_FALSE(JsonUtils::IsUint(json));
}

HWTEST_F(JsonUtilsIsUintTest, IsUint_ZeroJson, TestSize.Level1)
{
    auto json = JsonUtil::ParseJsonString("0");
    EXPECT_TRUE(JsonUtils::IsUint(json));
}

HWTEST_F(JsonUtilsIsUintTest, IsUint_LargeIntegerJson, TestSize.Level1)
{
    auto json = JsonUtil::ParseJsonString("999999999");
    EXPECT_TRUE(JsonUtils::IsUint(json));
}

HWTEST_F(JsonUtilsIsUintTest, IsUint_FloatJson, TestSize.Level1)
{
    auto json = JsonUtil::ParseJsonString("3.14159");
    EXPECT_FALSE(JsonUtils::IsUint(json));
}

HWTEST_F(JsonUtilsIsUintTest, IsUint_NegativeFloatJson, TestSize.Level1)
{
    auto json = JsonUtil::ParseJsonString("-3.14159");
    EXPECT_FALSE(JsonUtils::IsUint(json));
}

HWTEST_F(JsonUtilsIsUintTest, IsUint_SmallFloatJson, TestSize.Level1)
{
    auto json = JsonUtil::ParseJsonString("0.0001");
    EXPECT_FALSE(JsonUtils::IsUint(json));
}

HWTEST_F(JsonUtilsIsUintTest, IsUint_BoolTrueJson, TestSize.Level1)
{
    auto json = JsonUtil::ParseJsonString("true");
    EXPECT_FALSE(JsonUtils::IsUint(json));
}

HWTEST_F(JsonUtilsIsUintTest, IsUint_BoolFalseJson, TestSize.Level1)
{
    auto json = JsonUtil::ParseJsonString("false");
    EXPECT_FALSE(JsonUtils::IsUint(json));
}

HWTEST_F(JsonUtilsIsUintTest, IsUint_NullLiteralJson, TestSize.Level1)
{
    auto json = JsonUtil::ParseJsonString("null");
    EXPECT_FALSE(JsonUtils::IsUint(json));
}

HWTEST_F(JsonUtilsIsUintTest, IsUint_NearIntegerJson, TestSize.Level1)
{
    auto json = JsonUtil::ParseJsonString("42.000000001");
    EXPECT_FALSE(JsonUtils::IsUint(json));
}

HWTEST_F(JsonUtilsIsUintTest, IsUint_VeryNearIntegerJson, TestSize.Level1)
{
    auto json = JsonUtil::ParseJsonString("42.00000000001");
    EXPECT_TRUE(JsonUtils::IsUint(json));
}

HWTEST_F(JsonUtilsIsUintTest, IsUint_ExactIntegerFromFloat, TestSize.Level1)
{
    auto json = JsonUtil::ParseJsonString("42.0");
    EXPECT_TRUE(JsonUtils::IsUint(json));
}

HWTEST_F(JsonUtilsIsUintTest, IsUint_NegativeExactIntegerFromFloat, TestSize.Level1)
{
    auto json = JsonUtil::ParseJsonString("-42.0");
    EXPECT_FALSE(JsonUtils::IsUint(json));
}

HWTEST_F(JsonUtilsIsUintTest, IsUint_PointerNull, TestSize.Level1)
{
    EXPECT_FALSE(JsonUtils::IsUint(nullptr));
}

HWTEST_F(JsonUtilsIsUintTest, IsUint_ValidPointer, TestSize.Level1)
{
    auto json = JsonUtil::ParseJsonString("123");
    EXPECT_TRUE(JsonUtils::IsUint(json.get()));
}

HWTEST_F(JsonUtilsIsUintTest, IsUint_InvalidPointer, TestSize.Level1)
{
    auto json = JsonUtil::ParseJsonString("\"string\"");
    EXPECT_FALSE(JsonUtils::IsUint(json.get()));
}

} // namespace OHOS::Ace::NG