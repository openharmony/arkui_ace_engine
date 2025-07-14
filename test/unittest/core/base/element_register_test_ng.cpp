/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include <cstdint>

#include "gtest/gtest.h"

#include "core/pipeline/base/element_register.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const int32_t INITIAL_ID = 0;
const int32_t ID_CAPACITY = 10;
const int32_t UNINITIALIZE_CURSOR = -1;

class MockNode {
public:
    static int32_t NextId()
    {
        if (cursor == UNINITIALIZE_CURSOR || currentId >= cursor + ID_CAPACITY) {
            cursor = ElementRegister::GetInstance()->RequireArkoalaNodeId(ID_CAPACITY);
            currentId = cursor;
        }
        return currentId++;
    }

private:
    static int32_t currentId;
    static int32_t cursor;
};
int32_t MockNode::currentId = INITIAL_ID;
int32_t MockNode::cursor = UNINITIALIZE_CURSOR;

} // namespace
class ElementRegisterTestNg : public testing::Test {};

/**
 * @tc.name: ElementRegisterTestNg001
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(ElementRegisterTestNg, ElementRegisterTestNg001, TestSize.Level1)
{
    EXPECT_EQ(ElementRegister::GetInstance()->MakeUniqueId(), 0);
    EXPECT_EQ(ElementRegister::GetInstance()->MakeUniqueId(), 1);
    EXPECT_EQ(ElementRegister::GetInstance()->MakeUniqueId(), 2);
    EXPECT_EQ(MockNode::NextId(), 3);
    EXPECT_EQ(MockNode::NextId(), 4);
    EXPECT_EQ(MockNode::NextId(), 5);
    EXPECT_EQ(MockNode::NextId(), 6);
    EXPECT_EQ(ElementRegister::GetInstance()->MakeUniqueId(), 13);
    EXPECT_EQ(ElementRegister::GetInstance()->MakeUniqueId(), 14);
    EXPECT_EQ(MockNode::NextId(), 7);
    EXPECT_EQ(MockNode::NextId(), 8);
    EXPECT_EQ(MockNode::NextId(), 9);
    EXPECT_EQ(MockNode::NextId(), 10);
    EXPECT_EQ(MockNode::NextId(), 11);
    EXPECT_EQ(MockNode::NextId(), 12);
    EXPECT_EQ(MockNode::NextId(), 15);
    EXPECT_EQ(ElementRegister::GetInstance()->MakeUniqueId(), 25);
}
} // namespace OHOS::Ace::NG
