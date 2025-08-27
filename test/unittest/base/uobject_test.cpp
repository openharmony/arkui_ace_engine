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

/**
 * @tc.name: EstimateBufferSizeTest001
 * @tc.desc: test empty UObject
 * @tc.type: FUNC
 */
HWTEST_F(UObjectTest, EstimateBufferSizeTest001, TestSize.Level1)
{
    UObject uObject;
    int32_t ret = uObject.EstimateBufferSize();
    EXPECT_EQ(ret, static_cast<int32_t>(0));
}

/**
 * @tc.name: EstimateBufferSizeTest002
 * @tc.desc: test string items
 * @tc.type: FUNC
 */
HWTEST_F(UObjectTest, EstimateBufferSizeTest002, TestSize.Level1)
{
    UObject uObject;
    uObject.stringItems_["key"] = "value";
    size_t expectedSize = sizeof(uint8_t) + sizeof(int32_t) + strlen("key") + sizeof(int32_t) + strlen("value");
    EXPECT_EQ(uObject.EstimateBufferSize(), static_cast<int32_t>(expectedSize));
    uObject.stringItems_["key2"] = "value222";
    expectedSize += sizeof(uint8_t) + sizeof(int32_t) + strlen("key2") + sizeof(int32_t) + strlen("value222");
    EXPECT_EQ(uObject.EstimateBufferSize(), static_cast<int32_t>(expectedSize));
}

/**
 * @tc.name: EstimateBufferSizeTest003
 * @tc.desc: test sizet items
 * @tc.type: FUNC
 */
HWTEST_F(UObjectTest, EstimateBufferSizeTest003, TestSize.Level1)
{
    UObject uObject;
    uObject.sizetItems_["size"] = 100;
    size_t expectedSize = sizeof(uint8_t) + sizeof(int32_t) + strlen("size") + sizeof(size_t);
    EXPECT_EQ(uObject.EstimateBufferSize(), static_cast<int32_t>(expectedSize));
    uObject.sizetItems_["sizeItem"] = 101;
    expectedSize += sizeof(uint8_t) + sizeof(int32_t) + strlen("sizeItem") + sizeof(size_t);
    EXPECT_EQ(uObject.EstimateBufferSize(), static_cast<int32_t>(expectedSize));
}

/**
 * @tc.name: EstimateBufferSizeTest004
 * @tc.desc: test int32 items
 * @tc.type: FUNC
 */
HWTEST_F(UObjectTest, EstimateBufferSizeTest004, TestSize.Level1)
{
    UObject uObject;
    uObject.int32Items_["int32"] = -42;
    size_t expectedSize = sizeof(uint8_t) + sizeof(int32_t) + strlen("int32") + sizeof(int32_t);
    EXPECT_EQ(uObject.EstimateBufferSize(), static_cast<int32_t>(expectedSize));
    uObject.int32Items_["int32Item"] = -43;
    expectedSize += sizeof(uint8_t) + sizeof(int32_t) + strlen("int32Item") + sizeof(int32_t);
    EXPECT_EQ(uObject.EstimateBufferSize(), static_cast<int32_t>(expectedSize));
}

/**
 * @tc.name: EstimateBufferSizeTest005
 * @tc.desc: test int64 items
 * @tc.type: FUNC
 */
HWTEST_F(UObjectTest, EstimateBufferSizeTest005, TestSize.Level1)
{
    UObject uObject;
    uObject.int64Items_["int64"] = 1LL << 40;
    size_t expectedSize = sizeof(uint8_t) + sizeof(int32_t) + strlen("int64") + sizeof(int64_t);
    EXPECT_EQ(uObject.EstimateBufferSize(), static_cast<int32_t>(expectedSize));
    uObject.int64Items_["int64Item"] = 1LL << 41;
    expectedSize += sizeof(uint8_t) + sizeof(int32_t) + strlen("int64Item") + sizeof(int64_t);
    EXPECT_EQ(uObject.EstimateBufferSize(), static_cast<int32_t>(expectedSize));
}

/**
 * @tc.name: EstimateBufferSizeTest006
 * @tc.desc: test double items
 * @tc.type: FUNC
 */
HWTEST_F(UObjectTest, EstimateBufferSizeTest006, TestSize.Level1)
{
    UObject uObject;
    uObject.doubleItems_["pi"] = 3.14159;
    size_t expectedSize = sizeof(uint8_t) + sizeof(int32_t) + strlen("pi") + sizeof(double);
    EXPECT_EQ(uObject.EstimateBufferSize(), static_cast<int32_t>(expectedSize));
    uObject.doubleItems_["e"] = 2.71828;
    expectedSize += sizeof(uint8_t) + sizeof(int32_t) + strlen("e") + sizeof(double);
    EXPECT_EQ(uObject.EstimateBufferSize(), static_cast<int32_t>(expectedSize));
}

/**
 * @tc.name: EstimateBufferSizeTest007
 * @tc.desc: test bool items
 * @tc.type: FUNC
 */
HWTEST_F(UObjectTest, EstimateBufferSizeTest007, TestSize.Level1)
{
    UObject uObject;
    uObject.boolItems_["flagTrue"] = true;
    size_t expectedSize = sizeof(uint8_t) + sizeof(int32_t) + strlen("flagTrue") + sizeof(bool);
    EXPECT_EQ(uObject.EstimateBufferSize(), static_cast<int32_t>(expectedSize));
    uObject.boolItems_["flagFalse"] = false;
    expectedSize += sizeof(uint8_t) + sizeof(int32_t) + strlen("flagFalse") + sizeof(bool);
    EXPECT_EQ(uObject.EstimateBufferSize(), static_cast<int32_t>(expectedSize));
}

/**
 * @tc.name: EstimateBufferSizeTest008
 * @tc.desc: test child
 * @tc.type: FUNC
 */
HWTEST_F(UObjectTest, EstimateBufferSizeTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init UObject, child and expected size
     * @tc.expected: step1. children not empty
     */
    UObject uObject;
    auto childUObject1 = std::make_shared<UObject>();
    EXPECT_NE(childUObject1, nullptr);
    auto childUObject2 = std::make_shared<UObject>();
    EXPECT_NE(childUObject2, nullptr);

    /**
     * @tc.steps: step2. test children themselves
     */
    childUObject1->int32Items_["c"] = 30;
    size_t expectedChildSize1 = sizeof(uint8_t) + sizeof(int32_t) + strlen("c") + sizeof(int32_t);
    EXPECT_EQ(childUObject1->EstimateBufferSize(), static_cast<int32_t>(expectedChildSize1));
    childUObject1->int32Items_["de"] = 31;
    expectedChildSize1 += sizeof(uint8_t) + sizeof(int32_t) + strlen("de") + sizeof(int32_t);
    EXPECT_EQ(childUObject1->EstimateBufferSize(), static_cast<int32_t>(expectedChildSize1));
    childUObject1->int32Items_["fgh"] = 32;
    expectedChildSize1 += sizeof(uint8_t) + sizeof(int32_t) + strlen("fgh") + sizeof(int32_t);
    EXPECT_EQ(childUObject1->EstimateBufferSize(), static_cast<int32_t>(expectedChildSize1));
    
    childUObject2->doubleItems_["e"] = 2.71828;
    size_t expectedChildSize2 = sizeof(uint8_t) + sizeof(int32_t) + strlen("e") + sizeof(double);
    EXPECT_EQ(childUObject2->EstimateBufferSize(), static_cast<int32_t>(expectedChildSize2));
    
    /**
     * @tc.steps: step3. test children
     */
    uObject.children_["obj01"] = childUObject1;
    size_t expectedSize = sizeof(uint8_t) + sizeof(int32_t) + strlen("obj01") + sizeof(int32_t) + expectedChildSize1;
    uObject.children_["obj2"] = childUObject2;
    expectedSize += sizeof(uint8_t) + sizeof(int32_t) + strlen("obj2") + sizeof(int32_t) + expectedChildSize2;
    EXPECT_EQ(uObject.EstimateBufferSize(), static_cast<int32_t>(expectedSize));
}

/**
 * @tc.name: EstimateBufferSizeTest009
 * @tc.desc: test different data types
 * @tc.type: FUNC
 */
HWTEST_F(UObjectTest, EstimateBufferSizeTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init UObject and expected size
     */
    UObject uObject;
    size_t expectedSize = 0;
    EXPECT_EQ(uObject.EstimateBufferSize(), static_cast<int32_t>(expectedSize));

    /**
     * @tc.steps: step2. test string
     */
    uObject.stringItems_["name"] = "Alice";
    expectedSize += sizeof(uint8_t) + sizeof(int32_t) + strlen("name") + sizeof(int32_t) + strlen("Alice");
    EXPECT_EQ(uObject.EstimateBufferSize(), static_cast<int32_t>(expectedSize));

    /**
     * @tc.steps: step3. test number
     */
    uObject.sizetItems_["size"] = 100;
    expectedSize += sizeof(uint8_t) + sizeof(int32_t) + strlen("size") + sizeof(size_t);
    EXPECT_EQ(uObject.EstimateBufferSize(), static_cast<int32_t>(expectedSize));
    uObject.int32Items_["int32"] = -42;
    expectedSize += sizeof(uint8_t) + sizeof(int32_t) + strlen("int32") + sizeof(int32_t);
    EXPECT_EQ(uObject.EstimateBufferSize(), static_cast<int32_t>(expectedSize));
    uObject.int64Items_["int64"] = 1LL << 40;
    expectedSize += sizeof(uint8_t) + sizeof(int32_t) + strlen("int64") + sizeof(int64_t);
    EXPECT_EQ(uObject.EstimateBufferSize(), static_cast<int32_t>(expectedSize));
    uObject.doubleItems_["pi"] = 3.14159;
    expectedSize += sizeof(uint8_t) + sizeof(int32_t) + strlen("pi") + sizeof(double);
    EXPECT_EQ(uObject.EstimateBufferSize(), static_cast<int32_t>(expectedSize));

    /**
     * @tc.steps: step4. test bool
     */
    uObject.boolItems_["flag"] = true;
    expectedSize += sizeof(uint8_t) + sizeof(int32_t) + strlen("flag") + sizeof(bool);
    EXPECT_EQ(uObject.EstimateBufferSize(), static_cast<int32_t>(expectedSize));

    /**
     * @tc.steps: step5. test child
     */
    auto childUObject = std::make_shared<UObject>();
    EXPECT_NE(childUObject, nullptr);
    childUObject->int32Items_["c"] = 30;
    size_t expectedChildSize = sizeof(uint8_t) + sizeof(int32_t) + strlen("c") + sizeof(int32_t);
    EXPECT_EQ(childUObject->EstimateBufferSize(), static_cast<int32_t>(expectedChildSize));
    uObject.children_["obj"] = childUObject;
    expectedSize += sizeof(uint8_t) + sizeof(int32_t) + strlen("obj") + sizeof(int32_t) + expectedChildSize;
    EXPECT_EQ(uObject.EstimateBufferSize(), static_cast<int32_t>(expectedSize));
}
} // namespace OHOS::Ace