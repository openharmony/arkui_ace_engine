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

#include "core/interfaces/arkoala/arkoala_api.h"
#include "error_code.h"
#include "gtest/gtest.h"
#include "node_model.h"
#include "node_model_safely.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::NodeModel;

class NodeModelSafelyTest : public testing::Test {
public:
    static void SetUpTestCase()
    {
        InitialFullImpl();
    };
    static void TearDownTestCase() {};
};

/**
 * @tc.name: NodeModelSafelyTest001
 * @tc.desc: Test CreateNodeSafely function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeModelSafelyTest, NodeModelSafelyTest001, TestSize.Level1)
{
    ArkUI_NodeHandle nodeHandle = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_SWIPER);
    ASSERT_NE(nodeHandle, nullptr);
    EXPECT_EQ(nodeHandle->threadSafeNode, true);

    bool isValid = IsValidArkUINodeMultiThread(nodeHandle);
    EXPECT_EQ(isValid, true);
    DisposeNodeSafely(nodeHandle);
    isValid = IsValidArkUINodeMultiThread(nodeHandle);
    EXPECT_EQ(isValid, false);
}

/**
 * @tc.name: NodeModelSafelyTest002
 * @tc.desc: Test DisposeNodeSafely function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeModelSafelyTest, NodeModelSafelyTest002, TestSize.Level1)
{
    ArkUI_NodeHandle nodeHandle = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_SWIPER);
    ASSERT_NE(nodeHandle, nullptr);
    EXPECT_EQ(nodeHandle->threadSafeNode, true);

    bool isValid = IsValidArkUINodeMultiThread(nodeHandle);
    EXPECT_EQ(isValid, true);
    DisposeNodeSafely(nodeHandle);
    isValid = IsValidArkUINodeMultiThread(nodeHandle);
    EXPECT_EQ(isValid, false);
}

/**
 * @tc.name: NodeModelSafelyTest003
 * @tc.desc: Test AddChildSafely function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeModelSafelyTest, NodeModelSafelyTest003, TestSize.Level1)
{
    ArkUI_NodeHandle parent = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(parent, nullptr);
    ArkUI_NodeHandle child = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(child, nullptr);

    int32_t ret = AddChildSafely(nullptr, child);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);

    ret = AddChildSafely(parent, nullptr);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);

    ret = AddChildSafely(parent, child);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    EXPECT_EQ(GetTotalChildCountSafely(parent), 1);

    RemoveChildSafely(parent, child);
    DisposeNodeSafely(parent);
    DisposeNodeSafely(child);
}

/**
 * @tc.name: NodeModelSafelyTest004
 * @tc.desc: Test RemoveChildSafely function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeModelSafelyTest, NodeModelSafelyTest004, TestSize.Level1)
{
    ArkUI_NodeHandle parent = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(parent, nullptr);
    ArkUI_NodeHandle child = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(child, nullptr);
    AddChildSafely(parent, child);

    int32_t ret = RemoveChildSafely(nullptr, child);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);

    ret = RemoveChildSafely(parent, nullptr);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    
    ret = RemoveChildSafely(parent, child);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    EXPECT_EQ(GetTotalChildCountSafely(parent), 0);

    DisposeNodeSafely(parent);
    DisposeNodeSafely(child);
}

/**
 * @tc.name: NodeModelSafelyTest005
 * @tc.desc: Test InsertChildAfterSafely function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeModelSafelyTest, NodeModelSafelyTest005, TestSize.Level1)
{
    ArkUI_NodeHandle parent = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(parent, nullptr);
    ArkUI_NodeHandle child1 = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(child1, nullptr);
    ArkUI_NodeHandle child2 = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(child2, nullptr);
    AddChildSafely(parent, child1);

    int32_t ret = InsertChildAfterSafely(nullptr, child2, child1);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);

    ret = InsertChildAfterSafely(parent, nullptr, child1);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    
    ret = InsertChildAfterSafely(parent, child2, child1);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    EXPECT_EQ(GetTotalChildCountSafely(parent), 2);

    RemoveChildSafely(parent, child1);
    RemoveChildSafely(parent, child2);
    DisposeNodeSafely(parent);
    DisposeNodeSafely(child1);
    DisposeNodeSafely(child2);
}

/**
 * @tc.name: NodeModelSafelyTest006
 * @tc.desc: Test InsertChildAfterSafely function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeModelSafelyTest, NodeModelSafelyTest006, TestSize.Level1)
{
    ArkUI_NodeHandle parent = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(parent, nullptr);
    ArkUI_NodeHandle child1 = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(child1, nullptr);
    ArkUI_NodeHandle child2 = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(child2, nullptr);
    AddChildSafely(parent, child1);

    int32_t ret = InsertChildAfterSafely(nullptr, child2, child1);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);

    ret = InsertChildAfterSafely(parent, nullptr, child1);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    
    ret = InsertChildAfterSafely(parent, child2, child1);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    EXPECT_EQ(GetTotalChildCountSafely(parent), 2);

    RemoveChildSafely(parent, child1);
    RemoveChildSafely(parent, child2);
    DisposeNodeSafely(parent);
    DisposeNodeSafely(child1);
    DisposeNodeSafely(child2);
}

/**
 * @tc.name: NodeModelSafelyTest007
 * @tc.desc: Test InsertChildBeforeSafely function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeModelSafelyTest, NodeModelSafelyTest007, TestSize.Level1)
{
    ArkUI_NodeHandle parent = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(parent, nullptr);
    ArkUI_NodeHandle child1 = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(child1, nullptr);
    ArkUI_NodeHandle child2 = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(child2, nullptr);
    AddChildSafely(parent, child1);

    int32_t ret = InsertChildBeforeSafely(nullptr, child2, child1);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);

    ret = InsertChildBeforeSafely(parent, nullptr, child1);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    
    ret = InsertChildBeforeSafely(parent, child2, child1);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    EXPECT_EQ(GetTotalChildCountSafely(parent), 2);

    RemoveChildSafely(parent, child1);
    RemoveChildSafely(parent, child2);
    DisposeNodeSafely(parent);
    DisposeNodeSafely(child1);
    DisposeNodeSafely(child2);
}

/**
 * @tc.name: NodeModelSafelyTest008
 * @tc.desc: Test InsertChildAtSafely function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeModelSafelyTest, NodeModelSafelyTest008, TestSize.Level1)
{
    ArkUI_NodeHandle parent = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(parent, nullptr);
    ArkUI_NodeHandle child1 = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(child1, nullptr);

    int32_t ret = InsertChildAtSafely(nullptr, child1, 0);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);

    ret = InsertChildAtSafely(parent, nullptr, 0);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    
    ret = InsertChildBeforeSafely(parent, child1, 0);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    EXPECT_EQ(GetTotalChildCountSafely(parent), 1);

    RemoveChildSafely(parent, child1);
    DisposeNodeSafely(parent);
    DisposeNodeSafely(child1);
}

/**
 * @tc.name: NodeModelSafelyTest009
 * @tc.desc: Test SetAttributeSafely function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeModelSafelyTest, NodeModelSafelyTest009, TestSize.Level1)
{
    ArkUI_NodeHandle node = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(node, nullptr);

    ArkUI_NumberValue value[] = {{.f32 = 100.0f}};
    ArkUI_AttributeItem item = {value, 1};
    int32_t ret = SetAttributeSafely(nullptr, NODE_WIDTH, &item);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);

    ret = SetAttributeSafely(node, NODE_WIDTH, &item);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    const ArkUI_AttributeItem* nodeAttr = GetAttributeSafely(node, NODE_WIDTH);
    ASSERT_NE(nodeAttr, nullptr);
    EXPECT_NE(nodeAttr->value[0].f32, 0.0f);

    ret = ResetAttributeSafely(nullptr, NODE_WIDTH);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);

    ret = ResetAttributeSafely(node, NODE_WIDTH);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    nodeAttr = GetAttributeSafely(node, NODE_WIDTH);
    EXPECT_NE(nodeAttr->value[0].f32, 100.0f);

    nodeAttr = GetAttributeSafely(nullptr, NODE_WIDTH);
    EXPECT_EQ(nodeAttr, nullptr);

    DisposeNodeSafely(node);
}

/**
 * @tc.name: NodeModelSafelyTest010
 * @tc.desc: Test RegisterNodeEventSafely function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeModelSafelyTest, NodeModelSafelyTest010, TestSize.Level1)
{
    ArkUI_NodeHandle node = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(node, nullptr);

    int32_t ret = RegisterNodeEventSafely(nullptr, ArkUI_NodeEventType::NODE_TOUCH_EVENT, 0, nullptr);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);

    ret = RegisterNodeEventSafely(node, ArkUI_NodeEventType::NODE_TOUCH_EVENT, 0, nullptr);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    ASSERT_NE(node->extraData, nullptr);
    ASSERT_NE(reinterpret_cast<ExtraData*>(node->extraData)->eventMap.size(), 0);

    UnregisterNodeEventSafely(nullptr, ArkUI_NodeEventType::NODE_TOUCH_EVENT);
    UnregisterNodeEventSafely(node, ArkUI_NodeEventType::NODE_TOUCH_EVENT);
    EXPECT_EQ(node->extraData, nullptr);

    DisposeNodeSafely(node);
}

/**
 * @tc.name: NodeModelSafelyTest011
 * @tc.desc: Test SetUserDataSafely function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeModelSafelyTest, NodeModelSafelyTest011, TestSize.Level1)
{
    ArkUI_NodeHandle node = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(node, nullptr);

    int32_t ret = SetUserDataSafely(nullptr, nullptr);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);

    int userData = 1;
    ret = SetUserDataSafely(node, &userData);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    ASSERT_NE(GetUserDataSafely(node), nullptr);
    ASSERT_EQ(*reinterpret_cast<int*>(GetUserDataSafely(node)), 1);

    EXPECT_EQ(GetUserDataSafely(nullptr), nullptr);

    DisposeNodeSafely(node);
}

/**
 * @tc.name: NodeModelSafelyTest012
 * @tc.desc: Test SetLengthMetricUnitSafely function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeModelSafelyTest, NodeModelSafelyTest012, TestSize.Level1)
{
    ArkUI_NodeHandle node = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(node, nullptr);

    int32_t ret = SetLengthMetricUnitSafely(nullptr, ARKUI_LENGTH_METRIC_UNIT_DEFAULT);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);

    ret = SetLengthMetricUnitSafely(node, ARKUI_LENGTH_METRIC_UNIT_DEFAULT);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);

    DisposeNodeSafely(node);
}

/**
 * @tc.name: NodeModelSafelyTest013
 * @tc.desc: Test AddNodeEventReceiverSafely function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeModelSafelyTest, NodeModelSafelyTest013, TestSize.Level1)
{
    ArkUI_NodeHandle node = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(node, nullptr);

    int32_t ret = AddNodeEventReceiverSafely(nullptr, nullptr);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);

    auto eventReceiver = [](ArkUI_NodeEvent* event) {};
    ret = AddNodeEventReceiverSafely(node, eventReceiver);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    EXPECT_NE(node->eventListeners, nullptr);

    ret = RemoveNodeEventReceiverSafely(nullptr, nullptr);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);

    ret = RemoveNodeEventReceiverSafely(node, eventReceiver);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    EXPECT_EQ(node->eventListeners, nullptr);

    DisposeNodeSafely(node);
}


/**
 * @tc.name: NodeModelSafelyTest014
 * @tc.desc: Test RegisterNodeCustomEventSafely function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeModelSafelyTest, NodeModelSafelyTest014, TestSize.Level1)
{
    ArkUI_NodeHandle node = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(node, nullptr);

    int32_t ret = RegisterNodeCustomEventSafely(nullptr,
        ArkUI_NodeCustomEventType::ARKUI_NODE_CUSTOM_EVENT_ON_DRAW, 0, nullptr);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);

    ret = RegisterNodeCustomEventSafely(node,
        ArkUI_NodeCustomEventType::ARKUI_NODE_CUSTOM_EVENT_ON_DRAW, 0, nullptr);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    ASSERT_NE(node->extraCustomData, nullptr);
    ASSERT_NE(reinterpret_cast<ExtraData*>(node->extraCustomData)->eventMap.size(), 0);

    UnregisterNodeCustomEventSafely(nullptr, ArkUI_NodeCustomEventType::ARKUI_NODE_CUSTOM_EVENT_ON_DRAW);
    UnregisterNodeCustomEventSafely(node, ArkUI_NodeCustomEventType::ARKUI_NODE_CUSTOM_EVENT_ON_DRAW);
    EXPECT_EQ(node->extraCustomData, nullptr);

    DisposeNodeSafely(node);
}

/**
 * @tc.name: NodeModelSafelyTest015
 * @tc.desc: Test AddNodeCustomEventReceiverSafely function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeModelSafelyTest, NodeModelSafelyTest015, TestSize.Level1)
{
    ArkUI_NodeHandle node = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(node, nullptr);

    int32_t ret = AddNodeCustomEventReceiverSafely(nullptr, nullptr);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);

    auto eventReceiver = [](ArkUI_NodeCustomEvent* event) {};
    ret = AddNodeCustomEventReceiverSafely(node, eventReceiver);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    EXPECT_NE(node->customEventListeners, nullptr);

    ret = RemoveNodeCustomEventReceiverSafely(nullptr, nullptr);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);

    ret = RemoveNodeCustomEventReceiverSafely(node, eventReceiver);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    EXPECT_EQ(node->customEventListeners, nullptr);

    DisposeNodeSafely(node);
}

/**
 * @tc.name: NodeModelSafelyTest016
 * @tc.desc: Test SetMeasuredSizeSafely function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeModelSafelyTest, NodeModelSafelyTest016, TestSize.Level1)
{
    ArkUI_NodeHandle node = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(node, nullptr);

    int32_t ret = SetMeasuredSizeSafely(nullptr, 100, 100);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);

    ret = SetMeasuredSizeSafely(node, 100, 100);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_NODE_ON_INVALID_THREAD);
    EXPECT_EQ(GetMeasuredSizeSafely(node).width, 0);

    EXPECT_EQ(GetMeasuredSizeSafely(nullptr).width, 0);

    DisposeNodeSafely(node);
}

/**
 * @tc.name: NodeModelSafelyTest017
 * @tc.desc: Test SetLayoutPositionSafely function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeModelSafelyTest, NodeModelSafelyTest017, TestSize.Level1)
{
    ArkUI_NodeHandle node = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(node, nullptr);

    int32_t ret = SetLayoutPositionSafely(nullptr, 100, 100);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);

    ret = SetLayoutPositionSafely(node, 100, 100);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_NODE_ON_INVALID_THREAD);
    EXPECT_EQ(GetLayoutPositionSafely(node).x, 0);

    EXPECT_EQ(GetLayoutPositionSafely(nullptr).x, 0);

    DisposeNodeSafely(node);
}

/**
 * @tc.name: NodeModelSafelyTest018
 * @tc.desc: Test SetLayoutPositionSafely function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeModelSafelyTest, NodeModelSafelyTest018, TestSize.Level1)
{
    ArkUI_NodeHandle node = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(node, nullptr);

    int32_t ret = MeasureNodeSafely(nullptr, nullptr);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);

    DisposeNodeSafely(node);
}

/**
 * @tc.name: NodeModelSafelyTest019
 * @tc.desc: Test SetLayoutPositionSafely function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeModelSafelyTest, NodeModelSafelyTest019, TestSize.Level1)
{
    ArkUI_NodeHandle node = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(node, nullptr);

    int32_t ret = LayoutNodeSafely(nullptr, 0, 0);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);

    ret = LayoutNodeSafely(node, 0, 0);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_NODE_ON_INVALID_THREAD);

    DisposeNodeSafely(node);
}

/**
 * @tc.name: NodeModelSafelyTest020
 * @tc.desc: Test GetChildAtSafely function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeModelSafelyTest, NodeModelSafelyTest020, TestSize.Level1)
{
    ArkUI_NodeHandle parent = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(parent, nullptr);
    ArkUI_NodeHandle child1 = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(child1, nullptr);
    ArkUI_NodeHandle child2 = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(child2, nullptr);
    AddChildSafely(parent, child1);
    AddChildSafely(parent, child2);

    ArkUI_NodeHandle ret = GetChildAtSafely(nullptr, 0);
    EXPECT_EQ(ret, nullptr);

    ret = GetChildAtSafely(parent, 0);
    EXPECT_EQ(ret, child1);

    RemoveChildSafely(parent, child1);
    RemoveChildSafely(parent, child2);
    DisposeNodeSafely(parent);
    DisposeNodeSafely(child1);
    DisposeNodeSafely(child2);
}

/**
 * @tc.name: NodeModelSafelyTest021
 * @tc.desc: Test GetFirstChildSafely function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeModelSafelyTest, NodeModelSafelyTest021, TestSize.Level1)
{
    ArkUI_NodeHandle parent = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(parent, nullptr);
    ArkUI_NodeHandle child1 = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(child1, nullptr);
    ArkUI_NodeHandle child2 = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(child2, nullptr);
    AddChildSafely(parent, child1);
    AddChildSafely(parent, child2);

    ArkUI_NodeHandle ret = GetFirstChildSafely(nullptr);
    EXPECT_EQ(ret, nullptr);

    ret = GetFirstChildSafely(parent);
    EXPECT_EQ(ret, child1);

    RemoveChildSafely(parent, child1);
    RemoveChildSafely(parent, child2);
    DisposeNodeSafely(parent);
    DisposeNodeSafely(child1);
    DisposeNodeSafely(child2);
}

/**
 * @tc.name: NodeModelSafelyTest022
 * @tc.desc: Test GetPreviousSiblingSafely function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeModelSafelyTest, NodeModelSafelyTest022, TestSize.Level1)
{
    ArkUI_NodeHandle parent = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(parent, nullptr);
    ArkUI_NodeHandle child1 = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(child1, nullptr);
    ArkUI_NodeHandle child2 = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(child2, nullptr);
    AddChildSafely(parent, child1);
    AddChildSafely(parent, child2);

    ArkUI_NodeHandle ret = GetLastChildSafely(nullptr);
    EXPECT_EQ(ret, nullptr);

    ret = GetLastChildSafely(parent);
    EXPECT_EQ(ret, child2);

    RemoveChildSafely(parent, child1);
    RemoveChildSafely(parent, child2);
    DisposeNodeSafely(parent);
    DisposeNodeSafely(child1);
    DisposeNodeSafely(child2);
}

/**
 * @tc.name: NodeModelSafelyTest023
 * @tc.desc: Test GetNextSiblingSafely function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeModelSafelyTest, NodeModelSafelyTest023, TestSize.Level1)
{
    ArkUI_NodeHandle parent = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(parent, nullptr);
    ArkUI_NodeHandle child1 = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(child1, nullptr);
    ArkUI_NodeHandle child2 = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(child2, nullptr);
    AddChildSafely(parent, child1);
    AddChildSafely(parent, child2);

    ArkUI_NodeHandle ret = GetNextSiblingSafely(nullptr);
    EXPECT_EQ(ret, nullptr);

    ret = GetNextSiblingSafely(child1);
    EXPECT_EQ(ret, child2);

    RemoveChildSafely(parent, child1);
    RemoveChildSafely(parent, child2);
    DisposeNodeSafely(parent);
    DisposeNodeSafely(child1);
    DisposeNodeSafely(child2);
}

/**
 * @tc.name: NodeModelSafelyTest024
 * @tc.desc: Test GetNextSiblingSafely function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeModelSafelyTest, NodeModelSafelyTest024, TestSize.Level1)
{
    ArkUI_NodeHandle parent = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(parent, nullptr);
    ArkUI_NodeHandle child1 = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(child1, nullptr);
    ArkUI_NodeHandle child2 = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(child2, nullptr);
    AddChildSafely(parent, child1);
    AddChildSafely(parent, child2);

    ArkUI_NodeHandle ret = GetParentSafely(nullptr);
    EXPECT_EQ(ret, nullptr);

    ret = GetParentSafely(child1);
    EXPECT_EQ(ret, parent);

    RemoveChildSafely(parent, child1);
    RemoveChildSafely(parent, child2);
    DisposeNodeSafely(parent);
    DisposeNodeSafely(child1);
    DisposeNodeSafely(child2);
}

/**
 * @tc.name: NodeModelSafelyTest025
 * @tc.desc: Test RemoveAllChildrenSafely function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeModelSafelyTest, NodeModelSafelyTest025, TestSize.Level1)
{
    ArkUI_NodeHandle parent = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(parent, nullptr);
    ArkUI_NodeHandle child1 = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(child1, nullptr);
    ArkUI_NodeHandle child2 = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(child2, nullptr);
    AddChildSafely(parent, child1);
    AddChildSafely(parent, child2);

    int32_t ret = RemoveAllChildrenSafely(nullptr);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);

    ret = RemoveAllChildrenSafely(parent);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    ret = GetTotalChildCountSafely(parent);
    EXPECT_EQ(ret, 0);

    RemoveChildSafely(parent, child1);
    RemoveChildSafely(parent, child2);
    DisposeNodeSafely(parent);
    DisposeNodeSafely(child1);
    DisposeNodeSafely(child2);
}

/**
 * @tc.name: NodeModelSafelyTest026
 * @tc.desc: Test IsValidArkUINodeMultiThread function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeModelSafelyTest, NodeModelSafelyTest026, TestSize.Level1)
{
    ArkUI_NodeHandle parent = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(parent, nullptr);
    ArkUI_NodeHandle child1 = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(child1, nullptr);
    ArkUI_NodeHandle child2 = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(child2, nullptr);
    AddChildSafely(parent, child1);
    AddChildSafely(parent, child2);

    bool ret = IsValidArkUINodeMultiThread(nullptr);
    EXPECT_EQ(ret, false);

    ret = IsValidArkUINodeMultiThread(parent);
    EXPECT_EQ(ret, true);
    ret = IsValidArkUINodeMultiThread(child1);
    EXPECT_EQ(ret, true);
    ret = IsValidArkUINodeMultiThread(child2);
    EXPECT_EQ(ret, true);

    RemoveChildSafely(parent, child1);
    RemoveChildSafely(parent, child2);
    DisposeNodeSafely(parent);
    DisposeNodeSafely(child1);
    DisposeNodeSafely(child2);

    ret = IsValidArkUINodeMultiThread(parent);
    EXPECT_EQ(ret, false);
    ret = IsValidArkUINodeMultiThread(child1);
    EXPECT_EQ(ret, false);
    ret = IsValidArkUINodeMultiThread(child2);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: NodeModelSafelyTest027
 * @tc.desc: Test GetUserDataSafely function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeModelSafelyTest, NodeModelSafelyTest027, TestSize.Level1)
{
    ArkUI_NodeHandle node = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_COLUMN);
    ASSERT_NE(node, nullptr);

    int userData = 1;
    bool ret = SetUserDataSafely(node, &userData);
    EXPECT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    ASSERT_NE(GetUserDataSafely(node), nullptr);
    EXPECT_EQ(*reinterpret_cast<int*>(GetUserDataSafely(node)), 1);

    DisposeNodeSafely(node);
}

/**
 * @tc.name: NodeModelSafelyTest028
 * @tc.desc: Test GetUserDataSafely function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeModelSafelyTest, NodeModelSafelyTest028, TestSize.Level1)
{
    ArkUI_NodeHandle node = CreateNodeSafely(ArkUI_NodeType::ARKUI_NODE_UNDEFINED);
    ASSERT_EQ(node, nullptr);
    DisposeNodeSafely(node);
}