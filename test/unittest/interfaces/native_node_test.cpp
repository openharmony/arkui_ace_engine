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
#include "native_interface.h"
#include "native_node.h"
#include "event_converter.h"

using namespace testing;
using namespace testing::ext;

class NativeNodeTest : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: NativeNodeTest001
 * @tc.desc: Test OH_ArkUI_NodeEvent_GetEventType function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTest, NativeNodeTest001, TestSize.Level1)
{
    ArkUI_NodeEvent event = { 0, -1 };
    auto eventType = OH_ArkUI_NodeEvent_GetEventType(&event);
    EXPECT_EQ(eventType, ArkUI_NodeEventType::NODE_TOUCH_EVENT);
}

/**
 * @tc.name: NativeNodeTest002
 * @tc.desc: Test OH_ArkUI_NodeEvent_GetEventType function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTest, NativeNodeTest002, TestSize.Level1)
{
    auto eventType = OH_ArkUI_NodeEvent_GetEventType(nullptr);
    EXPECT_EQ(eventType, ArkUI_NodeEventType::NODE_TOUCH_EVENT);
}

/**
 * @tc.name: NativeNodeTest003
 * @tc.desc: Test OH_ArkUI_NodeEvent_GetTargetId function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTest, NativeNodeTest003, TestSize.Level1)
{
    auto targetId = OH_ArkUI_NodeEvent_GetTargetId(nullptr);
    EXPECT_EQ(targetId, -1);
}

/**
 * @tc.name: NativeNodeTest004
 * @tc.desc: Test OH_ArkUI_NodeEvent_GetNodeHandle function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTest, NativeNodeTest004, TestSize.Level1)
{
    auto handle = OH_ArkUI_NodeEvent_GetNodeHandle(nullptr);
    EXPECT_EQ(handle, nullptr);
}

