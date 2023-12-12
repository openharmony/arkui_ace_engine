/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include <memory>
#include <sys/types.h>

#include "gtest/gtest.h"

#include "base/json/json_util.h"
#include "base/utils/utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
const std::string TEST_STRING = "Ace Unittest";
const std::string TEST_KEY = "JsonObjectTypeTest";
const std::string TEST_FALSE_KEY = "FalseKey";
} // namespace

class JsonUtilTest : public testing::Test {};

/**
 * @tc.name: JsonUtilTest001
 * @tc.desc: Check json util function for bool type value
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the test string with bool value.
     */
    std::string testJson = "true";

    /**
     * @tc.steps: step2. get JsonValue and check results of IsValid, IsNull, IsBool and GetBool.
     * @tc.expected: step2. get the JsonValue successfully and the results are correct.
     */
    std::unique_ptr<JsonValue> boolValue = JsonUtil::ParseJsonString(testJson);
    ASSERT_TRUE(boolValue);
    EXPECT_TRUE(boolValue->IsValid());
    EXPECT_FALSE(boolValue->IsNull());
    EXPECT_TRUE(boolValue->IsBool());
    EXPECT_TRUE(boolValue->GetBool());
}

/**
 * @tc.name: JsonUtilTest002
 * @tc.desc: Check json util function for bool type value
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the test string with bool value.
     */
    std::string testJson = "false";

    /**
     * @tc.steps: step2. get JsonValue and check results of IsValid, IsNull, IsBool and GetBool.
     * @tc.expected: step2. get the JsonValue successfully and the results are correct.
     */
    std::unique_ptr<JsonValue> boolValue = JsonUtil::ParseJsonString(testJson);
    ASSERT_TRUE(boolValue);
    EXPECT_TRUE(boolValue->IsValid());
    EXPECT_FALSE(boolValue->IsNull());
    EXPECT_TRUE(boolValue->IsBool());
    EXPECT_FALSE(boolValue->GetBool());
}

/**
 * @tc.name: JsonUtilTest003
 * @tc.desc: Check json util function for signed integer
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the test string with signed integer.
     */
    std::string testJson = "-1";
    int32_t intNum = -1;
    uint32_t uintNum = 0;
    double doubleNum = -1;

    /**
     * @tc.steps: step2. get JsonValue and check results of IsValid, IsNull, IsNumber, GetInt, GetUInt and GetDouble.
     * @tc.expected: step2. get the JsonValue successfully and the results are correct.
     */
    std::unique_ptr<JsonValue> intValue = JsonUtil::ParseJsonString(testJson);
    ASSERT_TRUE(intValue);
    EXPECT_TRUE(intValue->IsValid());
    EXPECT_FALSE(intValue->IsNull());
    EXPECT_TRUE(intValue->IsNumber());
    EXPECT_TRUE(intValue->GetInt() == intNum);
    EXPECT_TRUE(intValue->GetUInt() == uintNum) << "Actual:" << intValue->GetUInt() << " Expected: " << uintNum;
    EXPECT_TRUE(NearEqual(intValue->GetDouble(), doubleNum));
}

/**
 * @tc.name: JsonUtilTest004
 * @tc.desc: Check json util function for unsigned integer
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the test string with unsigned integer.
     */
    std::string testJson = "1";
    int32_t intNum = 1;
    uint32_t uintNum = 1;
    double doubleNum = 1;

    /**
     * @tc.steps: step2. get JsonValue and check results of IsValid, IsNull, IsNumber, GetInt, GetUInt and GetDouble.
     * @tc.expected: step2. get the JsonValue successfully and the results are correct.
     */
    std::unique_ptr<JsonValue> uintValue = JsonUtil::ParseJsonString(testJson);
    ASSERT_TRUE(uintValue);
    EXPECT_TRUE(uintValue->IsValid());
    EXPECT_FALSE(uintValue->IsNull());
    EXPECT_TRUE(uintValue->IsNumber());
    EXPECT_TRUE(uintValue->GetInt() == intNum);
    EXPECT_TRUE(uintValue->GetUInt() == uintNum);
    EXPECT_TRUE(NearEqual(uintValue->GetDouble(), doubleNum));
}

/**
 * @tc.name: JsonUtilTest005
 * @tc.desc: Check json util function for decimal number
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the test string with decimal number.
     */
    std::string testJson = "6.66";
    int32_t intNum = 6;
    uint32_t uintNum = 6;
    double doubleNum = 6.66;

    /**
     * @tc.steps: step2. get JsonValue and check results of IsValid, IsNull, IsNumber, GetInt, GetUInt and GetDouble.
     * @tc.expected: step2. get the JsonValue successfully and the results are correct.
     */
    std::unique_ptr<JsonValue> doubleValue = JsonUtil::ParseJsonString(testJson);
    ASSERT_TRUE(doubleValue);
    EXPECT_TRUE(doubleValue->IsValid());
    EXPECT_FALSE(doubleValue->IsNull());
    EXPECT_TRUE(doubleValue->IsNumber());
    EXPECT_TRUE(doubleValue->GetInt() == intNum);
    EXPECT_TRUE(doubleValue->GetUInt() == uintNum);
    EXPECT_TRUE(NearEqual(doubleValue->GetDouble(), doubleNum));
}

/**
 * @tc.name: JsonUtilTest006
 * @tc.desc: Check json util function for string
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the test string with string.
     */
    std::string testJson = "\"Ace Unittest\"";

    /**
     * @tc.steps: step2. get JsonValue and check results of IsValid, IsNull, IsString and GetString.
     * @tc.expected: step2. get the JsonValue successfully and the results are correct.
     */
    std::unique_ptr<JsonValue> stringValue = JsonUtil::ParseJsonString(testJson);
    ASSERT_TRUE(stringValue);
    EXPECT_TRUE(stringValue->IsValid());
    EXPECT_FALSE(stringValue->IsNull());
    EXPECT_TRUE(stringValue->IsString());
    EXPECT_TRUE(stringValue->GetString() == TEST_STRING);
}

/**
 * @tc.name: JsonUtilTest007
 * @tc.desc: Check json util function for empty string
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the test string with empty string.
     */
    std::string testJson = "\"\"";

    /**
     * @tc.steps: step2. get JsonValue and check results of IsValid, IsNull, IsString and GetString.
     * @tc.expected: step2. get the JsonValue successfully and the results are correct.
     */
    std::unique_ptr<JsonValue> emptyStringValue = JsonUtil::ParseJsonString(testJson);
    ASSERT_TRUE(emptyStringValue);
    EXPECT_TRUE(emptyStringValue->IsValid());
    EXPECT_FALSE(emptyStringValue->IsNull());
    EXPECT_TRUE(emptyStringValue->IsString());
    EXPECT_TRUE(emptyStringValue->GetString().empty());
}

/**
 * @tc.name: JsonUtilTest008
 * @tc.desc: Check json util function for JsonObject
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the test string with JsonObject.
     */
    std::string testJson = R"({"JsonObjectTypeTest": "Ace Unittest"})";

    /**
     * @tc.steps: step2. get JsonValue and check results of IsValid, IsNull, IsObject, Contains and GetValue.
     * @tc.expected: step2. get the JsonValue successfully and the results are correct.
     */
    std::unique_ptr<JsonValue> objectValue = JsonUtil::ParseJsonString(testJson);
    ASSERT_TRUE(objectValue);
    EXPECT_TRUE(objectValue->IsValid());
    EXPECT_FALSE(objectValue->IsNull());
    EXPECT_TRUE(objectValue->IsObject());
    EXPECT_TRUE(objectValue->Contains(TEST_KEY));
    EXPECT_FALSE(objectValue->Contains(TEST_FALSE_KEY));
    EXPECT_TRUE(objectValue->GetValue(TEST_KEY)->GetString() == TEST_STRING);
    EXPECT_TRUE(objectValue->GetValue(TEST_FALSE_KEY)->GetString().empty());
}

/**
 * @tc.name: JsonUtilTest009
 * @tc.desc: Check json util function for incorrect JsonObject
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the test string with incorrect JsonObject.
     */
    std::string testJson = R"({"JsonObjectTypeTest": ""})";

    /**
     * @tc.steps: step2. get JsonValue and check results of IsValid, IsNull, IsObject, Contains and GetValue.
     * @tc.expected: step2. get the JsonValue successfully and the results are correct.
     */
    std::unique_ptr<JsonValue> objectValue = JsonUtil::ParseJsonString(testJson);
    ASSERT_TRUE(objectValue);
    EXPECT_TRUE(objectValue->IsValid());
    EXPECT_FALSE(objectValue->IsNull());
    EXPECT_TRUE(objectValue->IsObject());
    EXPECT_TRUE(objectValue->Contains(TEST_KEY));
    EXPECT_TRUE(objectValue->GetValue(TEST_KEY)->GetString().empty());
}

/**
 * @tc.name: JsonUtilTest010
 * @tc.desc: Check json util function for array
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the test string with array.
     */
    std::string testJson = "[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]";
    int32_t testArraySize = 10;
    int32_t testArrayIndex = 5;
    int32_t testArrayValue = 5;

    /**
     * @tc.steps: step2. get JsonValue and check results of IsValid, IsNull, IsArray, GetArraySize and GetArrayItem.
     * @tc.expected: step2. get the JsonValue successfully and the results are correct.
     */
    std::unique_ptr<JsonValue> arrayValue = JsonUtil::ParseJsonString(testJson);
    ASSERT_TRUE(arrayValue);
    EXPECT_TRUE(arrayValue->IsValid());
    EXPECT_FALSE(arrayValue->IsNull());
    EXPECT_TRUE(arrayValue->IsArray());
    EXPECT_TRUE(arrayValue->GetArraySize() == testArraySize);
    EXPECT_TRUE(arrayValue->GetArrayItem(testArrayIndex)->GetInt() == testArrayValue);
}

/**
 * @tc.name: JsonUtilTest011
 * @tc.desc: Check json util function for empty array
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the test string with empty array.
     */
    std::string testJson = "[]";

    /**
     * @tc.steps: step2. get JsonValue and check results of IsValid, IsNull, IsArray, GetArraySize and GetArrayItem.
     * @tc.expected: step2. get the JsonValue successfully and the results are correct.
     */
    std::unique_ptr<JsonValue> arrayValue = JsonUtil::ParseJsonString(testJson);
    ASSERT_TRUE(arrayValue);
    EXPECT_TRUE(arrayValue->IsValid());
    EXPECT_FALSE(arrayValue->IsNull());
    EXPECT_TRUE(arrayValue->IsArray());
    EXPECT_TRUE(arrayValue->GetArraySize() == 0);
}

/**
 * @tc.name: JsonUtilTest012
 * @tc.desc: Check json util function for empty test string
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the empty test string.
     */
    std::string testJson;

    /**
     * @tc.steps: step2. get JsonValue and check results of IsValid, IsNull.
     * @tc.expected: step2. get the JsonValue successfully and the results are correct.
     */
    std::unique_ptr<JsonValue> emptyValue = JsonUtil::ParseJsonString(testJson);
    ASSERT_TRUE(emptyValue);
    EXPECT_FALSE(emptyValue->IsValid());
    EXPECT_TRUE(emptyValue->IsNull());
}

/**
 * @tc.name: JsonUtilTest013
 * @tc.desc: Check json util function for illegal type value
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the test string with illegal type value.
     */
    std::string testJson = "{Ace Unittest}";

    /**
     * @tc.steps: step2. get JsonValue and check results of IsValid, IsNull.
     * @tc.expected: step2. get the JsonValue successfully and the results are correct.
     */
    std::unique_ptr<JsonValue> illegalValue = JsonUtil::ParseJsonString(testJson);
    ASSERT_TRUE(illegalValue);
    EXPECT_FALSE(illegalValue->IsValid());
    EXPECT_TRUE(illegalValue->IsNull());
}
} // namespace OHOS::Ace