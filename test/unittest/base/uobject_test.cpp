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

#include "gtest/gtest.h"

#define private public
#define protected public
#include "base/json/uobject.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {} // namespace

class UObjectTest : public testing::Test {};

/**
 * @tc.name: UObjectTest001
 * @tc.desc: AddItemToObject()
 * @tc.type: FUNC
 */
HWTEST_F(UObjectTest, UObjectTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a UOObject.
     */
    UObject uObject;

    /**
     * @tc.steps: step2. Save value through AdditemToObject.
     * @tc.expected: step2. Asserting values through the get method.
     */
    char* value = nullptr;
    uObject.AddItemToObject("char", value);
    EXPECT_EQ(uObject.stringItems_.size(), 0);
    std::string stringValue = "test";
    uObject.AddItemToObject("char", const_cast<char*>(stringValue.c_str()));
    EXPECT_EQ(uObject.GetString("char"), "test");

    stringValue = "test1";
    uObject.AddItemToObject("string", stringValue);
    EXPECT_EQ(uObject.GetString("invalidKey"), "");
    EXPECT_EQ(uObject.GetString("string"), "test1");

    double doubleValue = 1.0;
    uObject.AddItemToObject("double", doubleValue);
    EXPECT_EQ(uObject.GetDouble("invalidKey"), 0);
    EXPECT_EQ(uObject.GetDouble("double"), 1.0);

    size_t sizeValue = 10;
    uObject.AddItemToObject("size_t", sizeValue);
    EXPECT_EQ(uObject.GetSizeT("invalidKey"), 0);
    EXPECT_EQ(uObject.GetSizeT("size_t"), 10);
    EXPECT_EQ(uObject.GetSizeT("double"), 1);

    int32_t int32Value = 5;
    uObject.AddItemToObject("int32_t", int32Value);
    EXPECT_EQ(uObject.GetInt32("invalidKey"), 0);
    EXPECT_EQ(uObject.GetInt32("int32_t"), 5);
    EXPECT_EQ(uObject.GetInt32("double"), 1);

    int64_t int64Value = 1;
    uObject.AddItemToObject("int64_t", int64Value);
    EXPECT_EQ(uObject.GetInt64("invalidKey"), 0);
    EXPECT_EQ(uObject.GetInt64("int64_t"), 1);
    EXPECT_EQ(uObject.GetInt64("double"), 1);

    bool boolValue = false;
    uObject.AddItemToObject("bool", boolValue);
    EXPECT_EQ(uObject.GetBool("invalidKey"), false);
    EXPECT_EQ(uObject.GetBool("bool"), false);

    std::shared_ptr<UObject> sharedUObject = std::make_shared<UObject>();
    uObject.AddItemToObject("shared_ptr", sharedUObject);
    EXPECT_TRUE(uObject.GetObject("invalidKey"));
    EXPECT_TRUE(uObject.GetObject("shared_ptr"));

    /**
     * @tc.steps: step3. Contains() test.
     * @tc.expected: step3. Asserting return bool.
     */
    EXPECT_FALSE(uObject.Contains("invalidKey"));
    EXPECT_TRUE(uObject.Contains("string"));
    EXPECT_TRUE(uObject.Contains("double"));
    EXPECT_TRUE(uObject.Contains("size_t"));
    EXPECT_TRUE(uObject.Contains("int32_t"));
    EXPECT_TRUE(uObject.Contains("int64_t"));
    EXPECT_TRUE(uObject.Contains("bool"));
    EXPECT_TRUE(uObject.Contains("shared_ptr"));
}

/**
 * @tc.name: UObjectTest002
 * @tc.desc: Serialize()
 * @tc.type: FUNC
 */
HWTEST_F(UObjectTest, UObjectTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a UOObject.
     */
    UObject uObject;
    std::string stringValue = "test";
    uObject.AddItemToObject("char", const_cast<char*>(stringValue.c_str()));
    stringValue = "test1";
    uObject.AddItemToObject("string", stringValue);
    double doubleValue = 1.0;
    uObject.AddItemToObject("double", doubleValue);
    size_t sizeValue = 10;
    uObject.AddItemToObject("size_t", sizeValue);
    int32_t int32Value = 5;
    uObject.AddItemToObject("int32_t", int32Value);
    int64_t int64Value = 1;
    uObject.AddItemToObject("int64_t", int64Value);
    bool boolValue = false;
    uObject.AddItemToObject("bool", boolValue);
    std::shared_ptr<UObject> sharedUObject = std::make_shared<UObject>();
    uObject.AddItemToObject("shared_ptr", sharedUObject);

    /**
     * @tc.steps: step2. Serialize()
     * @tc.expected: step2. Asserting values through the get method.
     */
    uObject.Hash();

    char* buffer = nullptr;
    uObject.Serialize(buffer, 0);
    EXPECT_EQ(uObject.offset_, 0);
    buffer = new char[136];
    uObject.Serialize(buffer, 136);
    EXPECT_EQ(uObject.offset_, 136);

    /**
     * @tc.steps: step3. Deserialize() test.
     * @tc.expected: step3. Asserting offset_.
     */
    uObject.Deserialize(buffer, 136);
    EXPECT_EQ(uObject.offset_, 136);

    /**
     * @tc.steps: step4. delete buffer.
     */
    delete[] buffer;
    buffer = nullptr;
}

/**
 * @tc.name: UObjectTest003
 * @tc.desc: Serialize()
 * @tc.type: FUNC
 */
HWTEST_F(UObjectTest, UObjectTest003, TestSize.Level1)
{
    UObject uObject;
    std::string value = "";
    uObject.WriteString(value);
    const char* buffer = nullptr;
    int32_t bufferLen = 100;
    uObject.Deserialize(buffer, bufferLen);
    EXPECT_EQ(uObject.offset_, 0);
}
} // namespace OHOS::Ace