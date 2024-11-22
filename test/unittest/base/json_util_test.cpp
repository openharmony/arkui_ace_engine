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
    double doubleNum = -1;

    /**
     * @tc.steps: step2. get JsonValue and check results of IsValid, IsNull, IsNumber, GetInt, GetUInt and GetDouble.
     * @@tc.expected: step2. get the JsonValue unsuccessfully and the results are 0
     */
    std::unique_ptr<JsonValue> intValue = JsonUtil::ParseJsonString(testJson);
    ASSERT_TRUE(intValue);
    EXPECT_TRUE(intValue->IsValid());
    EXPECT_FALSE(intValue->IsNull());
    EXPECT_TRUE(intValue->IsNumber());
    EXPECT_TRUE(intValue->GetInt() == intNum);
    EXPECT_FALSE(intValue->GetUInt() == -1);
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

/**
 * @tc.name: JsonUtilTest014
 * @tc.desc: Check json util function Put(const char* key, const char* value) for nullptr key or value
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the nullptr key.
     */
    const char* key = nullptr;
    const char* value = nullptr;
    JsonValue jsonValue;
    /**
     * @tc.steps: step2. get results
     * @tc.expected: step2.  the results are correct.
     */
    bool ret = jsonValue.Put(key, value);
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step3. construct the nullptr value.
     */
    char c = '5';
    const char* key2 = &c;
    const char* value2 = nullptr;
    /**
     * @tc.steps: step4. get results
     * @tc.expected: step4.  the results are correct.
     */
    bool ret2 = jsonValue.Put(key2, value2);
    EXPECT_FALSE(ret2);

    /**
     * @tc.steps: step5. construct value not null
     */
    char c2 = 'v';
    const char* value3 = &c2;
    bool ret3 = jsonValue.Put(key2, value3);
    EXPECT_TRUE(ret3);
    bool ret4 = jsonValue.Put(key, value3);
    EXPECT_FALSE(ret4);
}

/**
 * @tc.name: JsonUtilTest015
 * @tc.desc: Check json util function Put(const char* key, bool value) for nullptr key
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the nullptr key.
     */
    const char* key = nullptr;
    bool value = true;
    JsonValue jsonValue;
    /**
     * @tc.steps: step2. get  results
     * @tc.expected: step2.  the results are correct.
     */
    bool ret = jsonValue.Put(key, value);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: JsonUtilTest016
 * @tc.desc: Check json util function Put(const char* key, const std::unique_ptr<JsonValue>& value)
 * for nullptr key or nullptr value
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the nullptr key.
     */
    const char* key = nullptr;
    const std::unique_ptr<JsonValue>& value = nullptr;
    JsonValue jsonValue;
    /**
     * @tc.steps: step2. get  results
     * @tc.expected: step2.  the results are correct.
     */
    bool ret = jsonValue.Put(key, value);
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step1. construct the nullptr value.
     */
    char c = '5';
    const char* key2 = &c;
    const std::unique_ptr<JsonValue>& value2 = nullptr;
    /**
     * @tc.steps: step2. get  results
     * @tc.expected: step2.  the results are correct.
     */
    bool ret2 = jsonValue.Put(key2, value2);
    EXPECT_FALSE(ret2);

    /**
     * @tc.steps: step3. construct the value not null
     */
    char valueStr = '5';
    const char* valueTemp = &valueStr;
    bool ret3 = jsonValue.Put(key2, valueTemp);
    EXPECT_TRUE(ret3);
    bool ret4 = jsonValue.Put(key, valueTemp);
    EXPECT_FALSE(ret4);
}

/**
 * @tc.name: JsonUtilTest017
 * @tc.desc: Check json util function Put(const char* key, size_t value) for nullptr key
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the nullptr key.
     */
    const char* key = nullptr;
    size_t value = 8;
    JsonValue jsonValue;
    /**
     * @tc.steps: step2. get  results
     * @tc.expected: step2.  the results are correct.
     */
    bool ret = jsonValue.Put(key, value);
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step1. construct the nullptr value.
     */
    char c = '5';
    const char* key2 = &c;
    /**
     * @tc.steps: step2. get  results
     * @tc.expected: step2.  the results are correct.
     */
    bool ret2 = jsonValue.Put(key2, value);
    EXPECT_TRUE(ret2);
}

/**
 * @tc.name: JsonUtilTest018
 * @tc.desc: Check json util function Put(const char* key, int32_t value) for nullptr key
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the nullptr key.
     */
    const char* key = nullptr;
    int32_t value = 8;
    JsonValue jsonValue;
    /**
     * @tc.steps: step2. get  results
     * @tc.expected: step2.  the results are correct.
     */
    bool ret = jsonValue.Put(key, value);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: JsonUtilTest019
 * @tc.desc: Check json util function Put(const char* key, double value) for nullptr key
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the nullptr key.
     */
    const char* key = nullptr;
    double value = 8;
    JsonValue jsonValue;
    /**
     * @tc.steps: step2. get  results
     * @tc.expected: step2.  the results are correct.
     */
    bool ret = jsonValue.Put(key, value);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: JsonUtilTest020
 * @tc.desc: Check json util function Replace(const char* key, double value) for nullptr key
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the nullptr key.
     */
    const char* key = nullptr;
    double value = 8.0;
    std::unique_ptr<JsonValue> jsonValue = JsonUtil::Create(false);

    /**
     * @tc.steps: step2. get  results
     * @tc.expected: step2.  the results are correct.
     */
    bool ret = jsonValue->Replace(key, value);
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step3. construct key(not exist) and value
     * @tc.expected: step3. true
     */
    key = "aaa";
    bool ret3 = jsonValue->Replace(key, value);
    EXPECT_FALSE(ret3);

    /**
     * @tc.steps: step4. construct key(exist) and value
     * @tc.expected: step3. true
     */
    double valueTmp = 8.0;
    key = "aaa";
    bool putRet = jsonValue->Put(key, valueTmp);
    EXPECT_TRUE(putRet);
    bool ret4 = jsonValue->Replace(key, value);
    EXPECT_TRUE(ret4);
}

/**
 * @tc.name: JsonUtilTest021
 * @tc.desc: Check json util function Replace(const char* key, bool value) for nullptr key
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the nullptr key.
     */
    const char* key = nullptr;
    bool value = true;
    std::unique_ptr<JsonValue> jsonValue = JsonUtil::Create(false);
    /**
     * @tc.steps: step2. get  results
     * @tc.expected: step2.  the results are correct.
     */
    bool ret = jsonValue->Replace(key, value);
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step3. construct key(not exist) and value
     * @tc.expected: step3. true
     */
    key = "aaa";
    bool ret3 = jsonValue->Replace(key, value);
    EXPECT_FALSE(ret3);

    /**
     * @tc.steps: step4. construct key(exist) and value
     * @tc.expected: step3. true
     */
    jsonValue->Put(key, false);
    bool ret4 = jsonValue->Replace(key, value);
    EXPECT_TRUE(ret4);
}

/**
 * @tc.name: JsonUtilTest022
 * @tc.desc: Check json util function Replace(const char* key, const char* value) for nullptr key
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the nullptr key.
     */
    const char* key = nullptr;
    const char* value = nullptr;
    std::unique_ptr<JsonValue> jsonValue = JsonUtil::Create(false);
    /**
     * @tc.steps: step2. get  results
     * @tc.expected: step2.  the results are correct.
     */
    bool ret = jsonValue->Replace(key, value);
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step3. construct the nullptr value.
     */
    char c = '5';
    const char* value2 = &c;
    const char* key2 = nullptr;
    /**
     * @tc.steps: step4. get  results
     * @tc.expected: step4.  the results are correct.
     */
    bool ret2 = jsonValue->Replace(key2, value2);
    EXPECT_FALSE(ret2);

    /**
     * @tc.steps: step5. repalce key(not exist) and value
     * @tc.expected: step5. repalce fail
     */
    const char* key3 = "aaa";
    bool ret3 = jsonValue->Replace(key3, value2);
    EXPECT_FALSE(ret3);
    bool putRet = jsonValue->Put(key3, value2);
    EXPECT_TRUE(putRet);
    bool ret4 = jsonValue->Replace(key3, value2);
    EXPECT_TRUE(ret4);
}

/**
 * @tc.name: JsonUtilTest023
 * @tc.desc: Check json util function Replace(const char* key, int32_t value) for nullptr key
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the nullptr key.
     */
    const char* key = nullptr;
    int32_t value = 5;
    std::unique_ptr<JsonValue> jsonValue = JsonUtil::Create(false);
    /**
     * @tc.steps: step2. get  results
     * @tc.expected: step2.  the results are correct.
     */
    bool ret = jsonValue->Replace(key, value);
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step3. repalce key(not exist) and value
     * @tc.expected: step3. repalce fail
     */
    const char* key3 = "aaa";
    bool ret3 = jsonValue->Replace(key3, value);
    EXPECT_FALSE(ret3);
    bool putRet = jsonValue->Put(key3, value);
    EXPECT_TRUE(putRet);
    std::string objStr = jsonValue->ToString();
    EXPECT_TRUE(objStr.find("\"aaa\":5") != std::string::npos);
    bool ret4 = jsonValue->Replace(key3, value);
    EXPECT_TRUE(ret4);
}

/**
 * @tc.name: JsonUtilTest024
 * @tc.desc: Check json util Replace(const char* key, const std::unique_ptr<JsonValue>& value) for nullptr key
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the nullptr key.
     */
    const char* key = nullptr;
    const std::unique_ptr<JsonValue>& value = nullptr;
    std::unique_ptr<JsonValue> jsonValue = JsonUtil::Create(false);
    /**
     * @tc.steps: step2. get  results
     * @tc.expected: step2.  the results are correct.
     */
    bool ret = jsonValue->Replace(key, value);
    EXPECT_FALSE(ret);
    std::unique_ptr<JsonValue> valueTmp = JsonUtil::Create(false);
    bool ret2 = jsonValue->Replace(key, valueTmp);
    EXPECT_FALSE(ret2);

    /**
     * @tc.steps: step3. construct key(not exist) and value
     * @tc.expected: step3. true
     */
    key = "aaa";
    bool ret3 = jsonValue->Replace(key, valueTmp);
    EXPECT_FALSE(ret3);

    /**
     * @tc.steps: step4. construct key(exist) and value
     * @tc.expected: step3. true
     */
    jsonValue->Put(key, valueTmp);
    bool ret4 = jsonValue->Replace(key, valueTmp);
    EXPECT_TRUE(ret4);
}

/**
 * @tc.name: JsonUtilTest025
 * @tc.desc: Check json util bool Delete(const char* key) for nullptr key
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the nullptr key.
     */
    const char* key = nullptr;
    JsonValue jsonValue;
    /**
     * @tc.steps: step2. get  results
     * @tc.expected: step2.  the results are correct.
     */
    bool ret = jsonValue.Delete(key);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: JsonUtilTest026
 * @tc.desc: Check json util int64_t GetInt64()
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the nullptr object_.
     */
    std::unique_ptr<JsonValue> jsonValue = JsonUtil::Create(false);
    /**
     * @tc.steps: step2. get  results
     * @tc.expected: step2.  the results are correct.
     */
    int64_t ret = jsonValue->GetInt64();
    ASSERT_EQ(ret, 0);

    /**
     * @tc.steps: step3. get key(not exist)
     * @tc.expected: step3. reture defalut value 0
     */
    const std::string key = "key-aaa";
    int64_t ret3 = jsonValue->GetInt64(key, 0);
    ASSERT_EQ(ret3, 0);

    /**
     * @tc.steps: step4. get key(exist) but value not a number
     * @tc.expected: step4. reture defalut value 0
     */
    const char* keyPut = "key-aaa";
    const char* value = "value-bbb";
    jsonValue->Put(keyPut, value);
    int64_t ret4 = jsonValue->GetInt64(key, 0);
    ASSERT_EQ(ret4, 0);

    /**
     * @tc.steps: step5. get key(exist) and value is a number
     * @tc.expected: step5. reture value
     */
    keyPut = "key-number";
    jsonValue->Put(keyPut, 100);
    int64_t ret5 = jsonValue->GetInt64(keyPut, 0);
    ASSERT_EQ(ret5, 100);
}

/**
 * @tc.name: JsonUtilTest027
 * @tc.desc: Check json util std::unique_ptr<JsonValue> GetNext() for nullptr object_
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the nullptr object_.
     */
    JsonValue jsonValue(nullptr);
    /**
     * @tc.steps: step2. get  results
     * @tc.expected: step2.  the results are correct.
     */
    std::unique_ptr<JsonValue> ret = jsonValue.GetNext();
    EXPECT_TRUE(ret->IsNull());
}

/**
 * @tc.name: JsonUtilTest028
 * @tc.desc: Check json util std::unique_ptr<JsonValue> GetChild() for nullptr object_
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the nullptr object_.
     */
    JsonValue jsonValue(nullptr);
    /**
     * @tc.steps: step2. get  results
     * @tc.expected: step2.  the results are correct.
     */
    std::unique_ptr<JsonValue> ret = jsonValue.GetChild();
    EXPECT_TRUE(ret->IsNull());
}

/**
 * @tc.name: JsonUtilTest029
 * @tc.desc: Check json util bool Replace(const char* key, double value) for nullptr key
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the nullptr key.
     */
    const char* key = nullptr;
    double value = 5;
    JsonValue jsonValue;
    /**
     * @tc.steps: step2. get  results
     * @tc.expected: step2.  the results are correct.
     */
    bool ret = jsonValue.Replace(key, value);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: JsonUtilTest030
 * @tc.desc: Check json util bool Replace(const char* key, bool value) for nullptr key
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the nullptr key.
     */
    const char* key = nullptr;
    bool value = true;
    JsonValue jsonValue;
    /**
     * @tc.steps: step2. get  results
     * @tc.expected: step2.  the results are correct.
     */
    bool ret = jsonValue.Replace(key, value);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: JsonUtilTest031
 * @tc.desc: Check json util bool Replace(const char* key, const char* value) for nullptr key or nullptr value
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the nullptr value.
     */
    const char* key = nullptr;
    const char* value = nullptr;
    JsonValue jsonValue;
    /**
     * @tc.steps: step2. get  results
     * @tc.expected: step2.  the results are correct.
     */
    bool ret = jsonValue.Replace(key, value);
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step3. construct the nullptr key.
     */
    const char* key2 = nullptr;
    char c = '5';
    const char* value2 = &c;
    /**
     * @tc.steps: step4. get  results
     * @tc.expected: step4.  the results are correct.
     */
    bool ret2 = jsonValue.Replace(key2, value2);
    EXPECT_FALSE(ret2);
}

/**
 * @tc.name: JsonUtilTest032
 * @tc.desc: Check json util bool Replace(const char* key, int32_t value) for nullptr key
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the nullptr key.
     */
    const char* key = nullptr;
    int32_t value = 5;
    JsonValue jsonValue;
    /**
     * @tc.steps: step2. get  results
     * @tc.expected: step2.  the results are correct.
     */
    bool ret = jsonValue.Replace(key, value);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: JsonUtilTest033
 * @tc.desc: Check json util func bool PutFixedAttr  with const char* value
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the filter object, add filter attr, construct the jsonValue object.
     */
    NG::InspectorFilter filter;
    JsonValue jsonValue;
    const std::string attr = "color";
    filter.AddFilterAttr(attr);
    /**
     * @tc.steps: step2. get  results
     * @tc.expected: step2.  the results are correct.
     */
    bool ret = jsonValue.PutFixedAttr("editable", "EditMode.None", filter, NG::FIXED_ATTR_EDITABLE);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: JsonUtilTest034
 * @tc.desc: Check json util bool PutExtAttr
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the filter object, add filter attr, construct the jsonValue object.
     */
    NG::InspectorFilter filter;
    JsonValue jsonValue;
    const std::string attr = "color";
    filter.AddFilterAttr(attr);
    /**
     * @tc.steps: step2. get  results
     * @tc.expected: step2.  the results are correct.
     */
    bool ret = jsonValue.PutExtAttr("editable", "EditMode.None", filter);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: JsonUtilTest035
 * @tc.desc: Check json util func bool PutFixedAttr with const std::unique_ptr<JsonValue>& value
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest035, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the filter object, add filter attr, construct the empty jsonValue object
     */
    NG::InspectorFilter filter;
    JsonValue jsonValue;
    JsonValue jsonValueTemp;
    const std::unique_ptr<JsonValue> value = std::make_unique<JsonValue>(jsonValueTemp);
    /**
     * @tc.steps: step2. get  results
     * @tc.expected: step2.  the results are correct.
     */
    bool ret = jsonValue.PutFixedAttr("editable", value, filter, NG::FIXED_ATTR_EDITABLE);
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step3. set the value to jsonValueTemp, construct the jsonValue object.
     * @tc.expected: step3.  the results are correct.
     */
    std::string testJson = "true";
    std::unique_ptr<JsonValue> boolValue = JsonUtil::ParseJsonString(testJson);
    bool ret2 = jsonValue.PutFixedAttr("editable", boolValue, filter, NG::FIXED_ATTR_EDITABLE);
    EXPECT_TRUE(ret2);

    /**
     * @tc.steps: step4. construct the filter object, add filter attr, construct the jsonValue object.
     */
    const std::string attr = "color";
    filter.AddFilterAttr(attr);
    /**
     * @tc.steps: step5. get  results
     * @tc.expected: step5.  the results are correct.
     */
    bool ret3 = jsonValue.PutFixedAttr("editable", value, filter, NG::FIXED_ATTR_EDITABLE);
    EXPECT_FALSE(ret3);
}

/**
 * @tc.name: JsonUtilTest036
 * @tc.desc: Check json util func bool PutExtAttr with size_t value/int32_t value/double value/bool value/int64_t
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest036, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the filter object, add filter attr, construct the jsonValue object.
     */
    NG::InspectorFilter filter;
    JsonValue jsonValue;
    size_t value = 5;
    int32_t value2 = 5;
    double value3 = 5.0;
    int64_t value4 = 5;
    bool value5 = true;
    bool ret = jsonValue.PutExtAttr("editable", value, filter);
    bool ret2 = jsonValue.PutExtAttr("editable", value2, filter);
    bool ret3 = jsonValue.PutExtAttr("editable", value3, filter);
    bool ret4 = jsonValue.PutExtAttr("editable", value4, filter);
    bool ret5 = jsonValue.PutExtAttr("editable", value5, filter);
    EXPECT_TRUE(ret);
    EXPECT_TRUE(ret2);
    EXPECT_TRUE(ret3);
    EXPECT_TRUE(ret4);
    EXPECT_TRUE(ret5);
    /**
     * @tc.steps: step2. make filterExt not empty
     */
    const std::string attr = "color";
    filter.AddFilterAttr(attr);
    /**
     * @tc.steps: step2. get  results
     * @tc.expected: step2.  the results are correct.
     */
    bool ret6 = jsonValue.PutExtAttr("editable", value, filter);
    bool ret7 = jsonValue.PutExtAttr("editable", value2, filter);
    bool ret8 = jsonValue.PutExtAttr("editable", value3, filter);
    bool ret9 = jsonValue.PutExtAttr("editable", value4, filter);
    bool ret10 = jsonValue.PutExtAttr("editable", value5, filter);
    EXPECT_FALSE(ret6);
    EXPECT_FALSE(ret7);
    EXPECT_FALSE(ret8);
    EXPECT_FALSE(ret9);
    EXPECT_FALSE(ret10);
}

/**
 * @tc.name: JsonUtilTest037
 * @tc.desc: Check json util func bool PutFixedAttr with size_t value/int32_t value/double value/bool value/int64_t
 * value
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest037, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the filter object, add filter attr, construct the empty jsonValue object
     */
    NG::InspectorFilter filter;
    JsonValue jsonValue;
    size_t value = 5;
    int32_t value2 = 5;
    double value3 = 5.0;
    int64_t value4 = 5;
    bool value5 = true;
    /**
     * @tc.steps: step2. get  results
     * @tc.expected: step2.  the results are correct.
     */
    bool ret = jsonValue.PutFixedAttr("editable", value, filter, NG::FIXED_ATTR_EDITABLE);
    bool ret2 = jsonValue.PutFixedAttr("editable", value2, filter, NG::FIXED_ATTR_EDITABLE);
    bool ret3 = jsonValue.PutFixedAttr("editable", value3, filter, NG::FIXED_ATTR_EDITABLE);
    bool ret4 = jsonValue.PutFixedAttr("editable", value4, filter, NG::FIXED_ATTR_EDITABLE);
    bool ret5 = jsonValue.PutFixedAttr("editable", value5, filter, NG::FIXED_ATTR_EDITABLE);
    EXPECT_TRUE(ret);
    EXPECT_TRUE(ret2);
    EXPECT_TRUE(ret3);
    EXPECT_TRUE(ret4);
    EXPECT_TRUE(ret5);

    /**
     * @tc.steps: step3. construct the filter object, add filter attr
     */
    const std::string attr = "color";
    filter.AddFilterAttr(attr);
    /**
     * @tc.steps: step4. get  results
     * @tc.expected: step4.  the results are correct.
     */
    bool ret6 = jsonValue.PutFixedAttr("editable", value, filter, NG::FIXED_ATTR_EDITABLE);
    bool ret7 = jsonValue.PutFixedAttr("editable", value2, filter, NG::FIXED_ATTR_EDITABLE);
    bool ret8 = jsonValue.PutFixedAttr("editable", value3, filter, NG::FIXED_ATTR_EDITABLE);
    bool ret9 = jsonValue.PutFixedAttr("editable", value4, filter, NG::FIXED_ATTR_EDITABLE);
    bool ret10 = jsonValue.PutFixedAttr("editable", value5, filter, NG::FIXED_ATTR_EDITABLE);
    EXPECT_FALSE(ret6);
    EXPECT_FALSE(ret7);
    EXPECT_FALSE(ret8);
    EXPECT_FALSE(ret9);
    EXPECT_FALSE(ret10);
}

/**
 * @tc.name: JsonUtilTest038
 * @tc.desc: Check json util func bool PutExtAttr with const std::unique_ptr<JsonValue>& value
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest038, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the filter object, add filter attr, construct the empty jsonValue object
     */
    NG::InspectorFilter filter;
    JsonValue jsonValue;
    JsonValue jsonValueTemp;
    const std::unique_ptr<JsonValue> value = std::make_unique<JsonValue>(jsonValueTemp);
    /**
     * @tc.steps: step2. get  results
     * @tc.expected: step2.  the results are correct.
     */
    bool ret = jsonValue.PutExtAttr("editable", value, filter);
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step3. set the value to jsonValueTemp, construct the jsonValue object.
     * @tc.expected: step3.  the results are correct.
     */
    std::string testJson = "true";
    std::unique_ptr<JsonValue> boolValue = JsonUtil::ParseJsonString(testJson);
    bool ret2 = jsonValue.PutExtAttr("editable", boolValue, filter);
    EXPECT_TRUE(ret2);

    /**
     * @tc.steps: step4. construct the filter object, add filter attr, construct the jsonValue object.
     */
    const std::string attr = "color";
    filter.AddFilterAttr(attr);
    /**
     * @tc.steps: step5. get  results
     * @tc.expected: step5.  the results are correct.
     */
    bool ret3 = jsonValue.PutExtAttr("editable", value, filter);
    EXPECT_FALSE(ret3);
}

/**
 * @tc.name: JsonUtilTest039
 * @tc.desc: Check json util bool bool PutRef(const char* key, std::unique_ptr<JsonValue>&& value)
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest039, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the nullptr key
     */
    JsonValue jsonValue;
    const char* key = nullptr;
    std::unique_ptr<JsonValue> value = std::make_unique<JsonValue>();
    /**
     * @tc.steps: step2. get  results
     * @tc.expected: step2.  the results are correct.
     */
    bool ret = jsonValue.PutRef(key, std::move(value));
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step3. construct the nullptr value
     */
    char a = 'a';
    const char* key2 = &a;
    std::unique_ptr<JsonValue> value2;
    /**
     * @tc.steps: step4. get  results
     * @tc.expected: step4.  the results are correct.
     */
    bool ret2 = jsonValue.PutRef(key2, std::move(value2));
    bool ret3 = jsonValue.PutRef(std::move(value2));
    EXPECT_FALSE(ret2);
    EXPECT_FALSE(ret3);
}

/**
 * @tc.name: JsonUtilTest040
 * @tc.desc: Check json util int64_t GetUInt/GetInt/GetString
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest040, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct jsonValue
     */
    std::unique_ptr<JsonValue> jsonValue = JsonUtil::Create(false);

    /**
     * @tc.steps: step2. get key(not exist)
     * @tc.expected: step2. reture defalut value 0
     */
    const std::string key = "key-aaa";
    int64_t ret3 = jsonValue->GetUInt(key, 0);
    ASSERT_EQ(ret3, 0);

    /**
     * @tc.steps: step3. get key(exist) but value not a number
     * @tc.expected: step3. reture defalut value 0
     */
    const char* keyPut = "key-aaa";
    const char* value = "value-bbb";
    jsonValue->Put(keyPut, value);
    int64_t ret4 = jsonValue->GetUInt(key, 0);
    int64_t ret42 = jsonValue->GetInt(key, 0);
    ASSERT_EQ(ret4, 0);
    ASSERT_EQ(ret42, 0);

    /**
     * @tc.steps: step5. get key(exist) and value is a number
     * @tc.expected: step5. reture value
     */
    keyPut = "key-number";
    jsonValue->Put(keyPut, 100);
    int64_t ret5 = jsonValue->GetUInt(keyPut, 0);
    ASSERT_EQ(ret5, 100);
    std::string ret52 = jsonValue->GetString(keyPut, "default");
    ASSERT_EQ(ret52, "default");
}

/**
 * @tc.name: JsonUtilTest041
 * @tc.desc: Check json util Put(const std::unique_ptr<JsonValue>& value)/ReleaseJsonObject
 * @tc.type: FUNC
 */
HWTEST_F(JsonUtilTest, JsonUtilTest041, TestSize.Level1)
{
    std::unique_ptr<JsonValue> value = nullptr;
    JsonValue jsonValue;
    ASSERT_FALSE(jsonValue.Put(value));

    // ReleaseJsonObject() isRoot_ false
    JsonObject* ret = jsonValue.ReleaseJsonObject();
    ASSERT_TRUE(ret == nullptr);
    // PutRef() isRoot_ true
    char keyChar = 'k';
    char* keyPtr = &keyChar;
    std::unique_ptr<JsonValue> value2 = JsonUtil::Create(true);
    bool ret2 = jsonValue.PutRef(keyPtr, std::move(value2));
    ASSERT_TRUE(ret2);
    bool ret3 = jsonValue.PutRef(std::move(value2));
    ASSERT_TRUE(ret3);
}
} // namespace OHOS::Ace
