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

#include "base/json/json_util.h"
#include "base/json/node_object.h"
#include "base/json/uobject.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {} // namespace

class NodeObjectTest : public testing::Test {};

/**
 * @tc.name: NodeObjectTest001
 * @tc.desc: AddItemToObject()
 * @tc.type: FUNC
 */
HWTEST_F(NodeObjectTest, NodeObjectTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a NodeObject.
     */
    auto nodeObject = NodeObject::Create();

    /**
     * @tc.steps: step2. Save value through AdditemToObject.
     * @tc.expected: step2. Asserting values through the get method.
     */
    std::string stringValue = "test";
    double doubleValue = 1.0;
    size_t sizeValue = 10;
    int32_t int32Value = 5;
    int64_t int64Value = 1;
    bool boolValue = false;

    nodeObject->Put(nullptr, const_cast<char*>(stringValue.c_str()));
    nodeObject->Put(nullptr, nullptr);
    nodeObject->Put(nullptr, doubleValue);
    nodeObject->Put(nullptr, sizeValue);
    nodeObject->Put(nullptr, int32Value);
    nodeObject->Put(nullptr, int64Value);
    nodeObject->Put(nullptr, boolValue);

    std::string str = "string";
    nodeObject->Put(const_cast<char*>(str.c_str()), const_cast<char*>(stringValue.c_str()));
    EXPECT_EQ(nodeObject->GetString("string", ""), "test");
    EXPECT_EQ(nodeObject->GetString("", "test"), "test");
    str = "double";
    nodeObject->Put(const_cast<char*>(str.c_str()), doubleValue);
    EXPECT_EQ(nodeObject->GetDouble("double", 0), 1.0);
    EXPECT_EQ(nodeObject->GetDouble("", 0), 0);
    str = "int32_t";
    nodeObject->Put(const_cast<char*>(str.c_str()), int32Value);
    EXPECT_EQ(nodeObject->GetInt("int32_t", 0), 5);
    EXPECT_EQ(nodeObject->GetInt("", 0), 0);
    str = "int64_t";
    nodeObject->Put(const_cast<char*>(str.c_str()), int64Value);
    EXPECT_EQ(nodeObject->GetInt64("int64_t", 0), 1);
    EXPECT_EQ(nodeObject->GetInt64("", 0), 0);
    str = "bool";
    nodeObject->Put(const_cast<char*>(str.c_str()), boolValue);
    EXPECT_EQ(nodeObject->GetBool("bool", true), false);
    EXPECT_EQ(nodeObject->GetBool("", true), true);
}

/**
 * @tc.name: NodeObjectTest002
 * @tc.desc: Put(const char* key, size_t value)/GetUInt(const std::string& key, uint32_t defaultVal)
 * @tc.type: FUNC
 */
HWTEST_F(NodeObjectTest, NodeObjectTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a NodeObject.
     */
    auto nodeObject = NodeObject::Create();

    /**
     * @tc.steps: step2. Put(const char* key, size_t value)
     * @tc.expected: step2. Asserting put success.
     */
    const char* key = "key-string";
    size_t value = 5;
    bool ret = nodeObject->Put(key, value);
    EXPECT_EQ(ret, true);

    /**
     * @tc.steps: step3. GetUInt(const std::string& key, uint32_t defaultVal)
     * @tc.expected: step3. Asserting  success.
     */
    const std::string key2 = "aaaa";
    uint32_t defaultVal = 0;
    // key not exist
    uint32_t ret2 = nodeObject->GetUInt(key2, defaultVal);
    EXPECT_EQ(ret2, defaultVal);
    // key exist
    const char* key3 = "key-temp";
    nodeObject->Put(key3, 11);
    uint32_t ret3 = nodeObject->GetUInt(key3, defaultVal);
    EXPECT_EQ(ret3, 11);
}

/**
 * @tc.name: NodeObjectTest003
 * @tc.desc: Put(const char* key, const std::unique_ptr<NodeObject>& value)
 * @tc.type: FUNC
 */
HWTEST_F(NodeObjectTest, NodeObjectTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a NodeObject.
     */
    auto nodeObject = NodeObject::Create();

    // value is nullptr
    const std::unique_ptr<NodeObject> value = nullptr;
    const char* key = nullptr;
    bool ret = nodeObject->Put(key, value);
    EXPECT_EQ(ret, false);
    // value is not nullptr,key is nullptr
    auto value2 = NodeObject::Create();
    bool ret2 = nodeObject->Put(key, value2);
    EXPECT_EQ(ret2, false);
    const std::unique_ptr<JsonValue> value3 = std::make_unique<JsonValue>();
    bool ret3 = nodeObject->Put(key, value3);
    EXPECT_EQ(ret3, false);
}
} // namespace OHOS::Ace