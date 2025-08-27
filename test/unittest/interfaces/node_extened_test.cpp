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

#include "animate_impl.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "error_code.h"
#include "event_converter.h"
#include "gtest/gtest.h"
#include "native_animate.h"
#include "native_interface.h"
#include "native_node.h"
#include "node_extened.h"
#include "node_model.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::NodeModel;

class NodeExtenedTest : public testing::Test {
public:
    static void SetUpTestCase()
    {
        InitialFullImpl();
    };
    static void TearDownTestCase() {};
};

void EventReceiverHandle(ArkUI_NodeCustomEvent* event) {}
/**
 * @tc.name: NodeExtenedTest001
 * @tc.desc: Test NodeAddExtraData function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeExtenedTest, NodeExtenedTest001, TestSize.Level1)
{
    ArkUI_NodeHandle nodeHandle = CreateNode(ArkUI_NodeType::ARKUI_NODE_SWIPER);
    ASSERT_NE(nodeHandle, nullptr);

    void* userData = nullptr;
    NodeAddExtraData(nodeHandle, ArkUI_NodeCustomEventType::ARKUI_NODE_CUSTOM_EVENT_ON_MEASURE, 0, userData);
    ASSERT_NE(nodeHandle->extraCustomData, nullptr);
    DisposeNode(nodeHandle);
    nodeHandle = nullptr;
}

/**
 * @tc.name: NodeExtenedTest002
 * @tc.desc: Test RegisterNodeCustomEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeExtenedTest, NodeExtenedTest002, TestSize.Level1)
{
    void* userData = nullptr;
    int32_t ret = RegisterNodeCustomEvent(nullptr, ArkUI_NodeCustomEventType::ARKUI_NODE_CUSTOM_EVENT_ON_MEASURE,
                                          0, userData);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NodeExtenedTest003
 * @tc.desc: Test RegisterNodeCustomEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeExtenedTest, NodeExtenedTest003, TestSize.Level1)
{
    ArkUI_NodeHandle nodeHandle = CreateNode(ArkUI_NodeType::ARKUI_NODE_SWIPER);
    ASSERT_NE(nodeHandle, nullptr);

    void* userData = nullptr;
    int32_t ret = RegisterNodeCustomEvent(nodeHandle, static_cast<ArkUI_NodeCustomEventType>(-1), 0, userData);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED);

    DisposeNode(nodeHandle);
    nodeHandle = nullptr;
}

/**
 * @tc.name: NodeExtenedTest004
 * @tc.desc: Test RegisterNodeCustomEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeExtenedTest, NodeExtenedTest004, TestSize.Level1)
{
    ArkUI_NodeHandle nodeHandle = CreateNode(ArkUI_NodeType::ARKUI_NODE_SWIPER);
    ASSERT_NE(nodeHandle, nullptr);

    void* userData = nullptr;
    int32_t ret = RegisterNodeCustomEvent(nodeHandle, ArkUI_NodeCustomEventType::ARKUI_NODE_CUSTOM_EVENT_ON_MEASURE,
                                          0, userData);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED);

    DisposeNode(nodeHandle);
    nodeHandle = nullptr;
}

/**
 * @tc.name: NodeExtenedTest005
 * @tc.desc: Test RegisterNodeCustomEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeExtenedTest, NodeExtenedTest005, TestSize.Level1)
{
    ArkUI_NodeHandle nodeHandle = CreateNode(ArkUI_NodeType::ARKUI_NODE_SWIPER);
    ASSERT_NE(nodeHandle, nullptr);
    nodeHandle->type = ArkUI_NodeType::ARKUI_NODE_CUSTOM;
    void* userData = nullptr;
    int32_t ret = RegisterNodeCustomEvent(nodeHandle, ArkUI_NodeCustomEventType::ARKUI_NODE_CUSTOM_EVENT_ON_MEASURE,
                                          0, userData);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    UnregisterNodeCustomEvent(nodeHandle, ArkUI_NodeCustomEventType::ARKUI_NODE_CUSTOM_EVENT_ON_MEASURE);
    ASSERT_EQ(nodeHandle->extraCustomData, nullptr);
    DisposeNode(nodeHandle);
    nodeHandle = nullptr;
}

/**
 * @tc.name: NodeExtenedTest006
 * @tc.desc: Test RegisterNodeCustomEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeExtenedTest, NodeExtenedTest006, TestSize.Level1)
{
    ArkUI_NodeHandle nodeHandle = CreateNode(ArkUI_NodeType::ARKUI_NODE_SWIPER);
    ASSERT_NE(nodeHandle, nullptr);

    void* userData = nullptr;
    int32_t ret = RegisterNodeCustomEvent(nodeHandle, ArkUI_NodeCustomEventType::ARKUI_NODE_CUSTOM_EVENT_ON_LAYOUT,
                                          0, userData);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED);

    DisposeNode(nodeHandle);
    nodeHandle = nullptr;
}

/**
 * @tc.name: NodeExtenedTest007
 * @tc.desc: Test RegisterNodeCustomEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeExtenedTest, NodeExtenedTest007, TestSize.Level1)
{
    ArkUI_NodeHandle nodeHandle = CreateNode(ArkUI_NodeType::ARKUI_NODE_SWIPER);
    ASSERT_NE(nodeHandle, nullptr);
    nodeHandle->type = ArkUI_NodeType::ARKUI_NODE_CUSTOM;
    void* userData = nullptr;
    int32_t ret = RegisterNodeCustomEvent(nodeHandle, ArkUI_NodeCustomEventType::ARKUI_NODE_CUSTOM_EVENT_ON_LAYOUT,
                                          0, userData);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    UnregisterNodeCustomEvent(nodeHandle, ArkUI_NodeCustomEventType::ARKUI_NODE_CUSTOM_EVENT_ON_LAYOUT);
    ASSERT_EQ(nodeHandle->extraCustomData, nullptr);
    DisposeNode(nodeHandle);
    nodeHandle = nullptr;
}

/**
 * @tc.name: NodeExtenedTest008
 * @tc.desc: Test RegisterNodeCustomEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeExtenedTest, NodeExtenedTest008, TestSize.Level1)
{
    ArkUI_NodeHandle nodeHandle = CreateNode(ArkUI_NodeType::ARKUI_NODE_SWIPER);
    ASSERT_NE(nodeHandle, nullptr);
    nodeHandle->type = ArkUI_NodeType::ARKUI_NODE_CUSTOM;
    void* userData = nullptr;
    int32_t ret = RegisterNodeCustomEvent(nodeHandle, ArkUI_NodeCustomEventType::ARKUI_NODE_CUSTOM_EVENT_ON_DRAW,
                                          0, userData);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    UnregisterNodeCustomEvent(nodeHandle, ArkUI_NodeCustomEventType::ARKUI_NODE_CUSTOM_EVENT_ON_DRAW);
    ASSERT_EQ(nodeHandle->extraCustomData, nullptr);
    DisposeNode(nodeHandle);
    nodeHandle = nullptr;
}

/**
 * @tc.name: NodeExtenedTest009
 * @tc.desc: Test RegisterNodeCustomEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeExtenedTest, NodeExtenedTest009, TestSize.Level1)
{
    ArkUI_NodeHandle nodeHandle = CreateNode(ArkUI_NodeType::ARKUI_NODE_SWIPER);
    ASSERT_NE(nodeHandle, nullptr);
    nodeHandle->type = ArkUI_NodeType::ARKUI_NODE_CUSTOM;
    void* userData = nullptr;
    int32_t ret = RegisterNodeCustomEvent(nodeHandle,
        ArkUI_NodeCustomEventType::ARKUI_NODE_CUSTOM_EVENT_ON_FOREGROUND_DRAW, 0, userData);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    UnregisterNodeCustomEvent(nodeHandle, ArkUI_NodeCustomEventType::ARKUI_NODE_CUSTOM_EVENT_ON_FOREGROUND_DRAW);
    ASSERT_EQ(nodeHandle->extraCustomData, nullptr);
    DisposeNode(nodeHandle);
    nodeHandle = nullptr;
}

/**
 * @tc.name: NodeExtenedTest010
 * @tc.desc: Test RegisterNodeCustomEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeExtenedTest, NodeExtenedTest010, TestSize.Level1)
{
    ArkUI_NodeHandle nodeHandle = CreateNode(ArkUI_NodeType::ARKUI_NODE_SWIPER);
    ASSERT_NE(nodeHandle, nullptr);
    nodeHandle->type = ArkUI_NodeType::ARKUI_NODE_CUSTOM;
    void* userData = nullptr;
    int32_t ret = RegisterNodeCustomEvent(nodeHandle,
        ArkUI_NodeCustomEventType::ARKUI_NODE_CUSTOM_EVENT_ON_OVERLAY_DRAW, 0, userData);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    UnregisterNodeCustomEvent(nodeHandle, ArkUI_NodeCustomEventType::ARKUI_NODE_CUSTOM_EVENT_ON_OVERLAY_DRAW);
    ASSERT_EQ(nodeHandle->extraCustomData, nullptr);
    DisposeNode(nodeHandle);
    nodeHandle = nullptr;
}

/**
 * @tc.name: NodeExtenedTest011
 * @tc.desc: Test NodeRemoveExtraData function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeExtenedTest, NodeExtenedTest011, TestSize.Level1)
{
    ArkUI_NodeHandle nodeHandle = CreateNode(ArkUI_NodeType::ARKUI_NODE_SWIPER);
    ASSERT_NE(nodeHandle, nullptr);

    void* userData = nullptr;
    NodeAddExtraData(nodeHandle, ArkUI_NodeCustomEventType::ARKUI_NODE_CUSTOM_EVENT_ON_MEASURE, 0, userData);
    ASSERT_NE(nodeHandle->extraCustomData, nullptr);
    NodeRemoveExtraData(nodeHandle, ArkUI_NodeCustomEventType::ARKUI_NODE_CUSTOM_EVENT_ON_MEASURE);
    ASSERT_EQ(nodeHandle->extraCustomData, nullptr);
    DisposeNode(nodeHandle);
    nodeHandle = nullptr;
}

/**
 * @tc.name: NodeExtenedTest012
 * @tc.desc: Test NodeRemoveExtraData function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeExtenedTest, NodeExtenedTest012, TestSize.Level1)
{
    ArkUI_NodeHandle nodeHandle = CreateNode(ArkUI_NodeType::ARKUI_NODE_SWIPER);
    ASSERT_NE(nodeHandle, nullptr);

    void* userData = nullptr;
    NodeAddExtraData(nodeHandle, ArkUI_NodeCustomEventType::ARKUI_NODE_CUSTOM_EVENT_ON_MEASURE, 0, userData);
    NodeRemoveExtraData(nodeHandle, ArkUI_NodeCustomEventType::ARKUI_NODE_CUSTOM_EVENT_ON_OVERLAY_DRAW);
    ASSERT_NE(nodeHandle->extraCustomData, nullptr);
    DisposeNode(nodeHandle);
    nodeHandle = nullptr;
}

/**
 * @tc.name: NodeExtenedTest013
 * @tc.desc: Test UnregisterNodeCustomEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeExtenedTest, NodeExtenedTest013, TestSize.Level1)
{
    UnregisterNodeCustomEvent(nullptr, ArkUI_NodeCustomEventType::ARKUI_NODE_CUSTOM_EVENT_ON_MEASURE);
    ArkUI_NodeHandle nodeHandle = CreateNode(ArkUI_NodeType::ARKUI_NODE_SWIPER);
    ASSERT_NE(nodeHandle, nullptr);
    nodeHandle->type = ArkUI_NodeType::ARKUI_NODE_CUSTOM;
    void* userData = nullptr;
    int32_t ret = RegisterNodeCustomEvent(nodeHandle, ArkUI_NodeCustomEventType::ARKUI_NODE_CUSTOM_EVENT_ON_MEASURE,
                                          0, userData);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    UnregisterNodeCustomEvent(nodeHandle, ArkUI_NodeCustomEventType::ARKUI_NODE_CUSTOM_EVENT_ON_MEASURE);
    ASSERT_EQ(nodeHandle->extraCustomData, nullptr);
    DisposeNode(nodeHandle);
    nodeHandle = nullptr;
}

/**
 * @tc.name: NodeExtenedTest014
 * @tc.desc: Test UnregisterNodeCustomEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeExtenedTest, NodeExtenedTest014, TestSize.Level1)
{
    ArkUI_NodeHandle nodeHandle = CreateNode(ArkUI_NodeType::ARKUI_NODE_SWIPER);
    ASSERT_NE(nodeHandle, nullptr);
    nodeHandle->type = ArkUI_NodeType::ARKUI_NODE_CUSTOM;
    void* userData = nullptr;
    int32_t ret = RegisterNodeCustomEvent(nodeHandle, ArkUI_NodeCustomEventType::ARKUI_NODE_CUSTOM_EVENT_ON_MEASURE,
                                          0, userData);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    UnregisterNodeCustomEvent(nodeHandle, ArkUI_NodeCustomEventType::ARKUI_NODE_CUSTOM_EVENT_ON_OVERLAY_DRAW);
    ASSERT_NE(nodeHandle->extraCustomData, nullptr);
    DisposeNode(nodeHandle);
    nodeHandle = nullptr;
}

/**
 * @tc.name: NodeExtenedTest015
 * @tc.desc: Test HandleCustomEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeExtenedTest, NodeExtenedTest015, TestSize.Level1)
{
    HandleCustomEvent(nullptr);
    ArkUI_NodeHandle nodeHandle = CreateNode(ArkUI_NodeType::ARKUI_NODE_SWIPER);
    ASSERT_NE(nodeHandle, nullptr);
    nodeHandle->customEventListeners = new std::set<void (*)(ArkUI_NodeCustomEvent*)>();
    ArkUI_NodeCustomEvent event;
    event.node = nodeHandle;
    RegisterNodeCustomReceiver(EventReceiverHandle);
    HandleCustomEvent(&event);

    int32_t ret = SetMeasuredSize(nullptr, 0, 0);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    ret = SetMeasuredSize(nodeHandle, 1, 1);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    ArkUI_IntSize size = GetMeasuredSize(nodeHandle);
    ASSERT_EQ(size.width, 1);
    ASSERT_EQ(size.height, 1);
    DisposeNode(nodeHandle);
    nodeHandle = nullptr;
}

/**
 * @tc.name: NodeExtenedTest016
 * @tc.desc: Test HandleCustomEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeExtenedTest, NodeExtenedTest016, TestSize.Level1)
{
    ArkUI_NodeHandle nodeHandle = CreateNode(ArkUI_NodeType::ARKUI_NODE_SWIPER);
    ASSERT_NE(nodeHandle, nullptr);
    nodeHandle->customEventListeners = new std::set<void (*)(ArkUI_NodeCustomEvent*)>();
    ArkUI_NodeCustomEvent event;
    event.node = nodeHandle;
    UnregisterNodeCustomEventReceiver();
    HandleCustomEvent(&event);

    int32_t ret = SetLayoutPosition(nullptr, 0, 0);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    ret = SetLayoutPosition(nodeHandle, 1, 1);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    ArkUI_IntOffset offset = GetLayoutPosition(nodeHandle);
    ASSERT_EQ(offset.x, 1);
    ASSERT_EQ(offset.y, 1);
    DisposeNode(nodeHandle);
    nodeHandle = nullptr;
}

/**
 * @tc.name: NodeExtenedTest017
 * @tc.desc: Test HandleInnerCustomEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeExtenedTest, NodeExtenedTest017, TestSize.Level1)
{
    HandleInnerCustomEvent(nullptr);
    struct ArkUICustomNodeEvent* arkUICustomNodeEvent = new ArkUICustomNodeEvent();
    ASSERT_NE(arkUICustomNodeEvent, nullptr);
    HandleInnerCustomEvent(arkUICustomNodeEvent);
}

/**
 * @tc.name: NodeExtenedTest018
 * @tc.desc: Test AddNodeCustomEventReceiver function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeExtenedTest, NodeExtenedTest018, TestSize.Level1)
{
    int32_t ret = AddNodeCustomEventReceiver(nullptr, nullptr);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NodeExtenedTest019
 * @tc.desc: Test AddNodeCustomEventReceiver function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeExtenedTest, NodeExtenedTest019, TestSize.Level1)
{
    ArkUI_NodeHandle nodeHandle = CreateNode(ArkUI_NodeType::ARKUI_NODE_SWIPER);
    ASSERT_NE(nodeHandle, nullptr);
    int32_t ret = AddNodeCustomEventReceiver(nodeHandle, EventReceiverHandle);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    DisposeNode(nodeHandle);
    nodeHandle = nullptr;
}

/**
 * @tc.name: NodeExtenedTest020
 * @tc.desc: Test AddNodeCustomEventReceiver function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeExtenedTest, NodeExtenedTest020, TestSize.Level1)
{
    ArkUI_NodeHandle nodeHandle = CreateNode(ArkUI_NodeType::ARKUI_NODE_SWIPER);
    ASSERT_NE(nodeHandle, nullptr);
    nodeHandle->customEventListeners = new std::set<void (*)(ArkUI_NodeCustomEvent*)>();
    int32_t ret = AddNodeCustomEventReceiver(nodeHandle, EventReceiverHandle);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    DisposeNode(nodeHandle);
    nodeHandle = nullptr;
}

/**
 * @tc.name: NodeExtenedTest021
 * @tc.desc: Test RemoveNodeCustomEventReceiver function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeExtenedTest, NodeExtenedTest021, TestSize.Level1)
{
    int32_t ret = RemoveNodeCustomEventReceiver(nullptr, nullptr);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NodeExtenedTest022
 * @tc.desc: Test RemoveNodeCustomEventReceiver function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeExtenedTest, NodeExtenedTest022, TestSize.Level1)
{
    ArkUI_NodeHandle nodeHandle = CreateNode(ArkUI_NodeType::ARKUI_NODE_SWIPER);
    ASSERT_NE(nodeHandle, nullptr);
    nodeHandle->customEventListeners = new std::set<void (*)(ArkUI_NodeCustomEvent*)>();
    int32_t ret = RemoveNodeCustomEventReceiver(nodeHandle, EventReceiverHandle);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    DisposeNode(nodeHandle);
    nodeHandle = nullptr;
}

/**
 * @tc.name: NodeExtenedTest023
 * @tc.desc: Test GetLayoutConstraint function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeExtenedTest, NodeExtenedTest023, TestSize.Level1)
{
    int32_t ret = GetLayoutConstraint(nullptr, nullptr);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    ArkUI_NodeHandle nodeHandle = CreateNode(ArkUI_NodeType::ARKUI_NODE_SWIPER);
    ASSERT_NE(nodeHandle, nullptr);
    struct ArkUI_LayoutConstraint layoutConstraint = {0, 0, 0, 0, 0, 0};
    ret = GetLayoutConstraint(nodeHandle, &layoutConstraint);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    DisposeNode(nodeHandle);
    nodeHandle = nullptr;
}

/**
 * @tc.name: NodeExtenedTest024
 * @tc.desc: Test MeasureNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeExtenedTest, NodeExtenedTest024, TestSize.Level1)
{
    int32_t ret = MeasureNode(nullptr, nullptr);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NodeExtenedTest025
 * @tc.desc: Test MeasureNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeExtenedTest, NodeExtenedTest025, TestSize.Level1)
{
    ArkUI_NodeHandle nodeHandle = CreateNode(ArkUI_NodeType::ARKUI_NODE_SWIPER);
    ASSERT_NE(nodeHandle, nullptr);
    struct ArkUI_LayoutConstraint layoutConstraint = {0, 0, 0, 0, 0, 0};
    int32_t ret = MeasureNode(nodeHandle, &layoutConstraint);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    DisposeNode(nodeHandle);
    nodeHandle = nullptr;
}

/**
 * @tc.name: NodeExtenedTest026
 * @tc.desc: Test LayoutNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeExtenedTest, NodeExtenedTest026, TestSize.Level1)
{
    int32_t ret = LayoutNode(nullptr, 0, 0);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    ArkUI_NodeHandle nodeHandle = CreateNode(ArkUI_NodeType::ARKUI_NODE_SWIPER);
    ASSERT_NE(nodeHandle, nullptr);
    ret = LayoutNode(nodeHandle, 0, 0);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    DisposeNode(nodeHandle);
    nodeHandle = nullptr;
}

/**
 * @tc.name: NodeExtenedTest027
 * @tc.desc: Test GetTotalChildCount function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeExtenedTest, NodeExtenedTest027, TestSize.Level1)
{
    int32_t ret = GetTotalChildCount(nullptr);
    ASSERT_EQ(ret, 0);
    ArkUI_NodeHandle nodeHandle = CreateNode(ArkUI_NodeType::ARKUI_NODE_SWIPER);
    ASSERT_NE(nodeHandle, nullptr);
    ret = GetTotalChildCount(nodeHandle);
    ASSERT_EQ(ret, 0);
    DisposeNode(nodeHandle);
    nodeHandle = nullptr;
}

/**
 * @tc.name: NodeExtenedTest028
 * @tc.desc: Test GetChildAt function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeExtenedTest, NodeExtenedTest028, TestSize.Level1)
{
    ArkUI_NodeHandle node = GetChildAt(nullptr, 0);
    ASSERT_EQ(node, nullptr);
    ArkUI_NodeHandle nodeHandle = CreateNode(ArkUI_NodeType::ARKUI_NODE_SWIPER);
    ASSERT_NE(nodeHandle, nullptr);
    node = GetChildAt(nodeHandle, 0);
    ASSERT_EQ(node, nullptr);
    DisposeNode(nodeHandle);
    nodeHandle = nullptr;
}

/**
 * @tc.name: NodeExtenedTest029
 * @tc.desc: Test GetFirstChild function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeExtenedTest, NodeExtenedTest029, TestSize.Level1)
{
    ArkUI_NodeHandle node = GetFirstChild(nullptr);
    ASSERT_EQ(node, nullptr);
    ArkUI_NodeHandle nodeHandle = CreateNode(ArkUI_NodeType::ARKUI_NODE_SWIPER);
    ASSERT_NE(nodeHandle, nullptr);
    node = GetFirstChild(nodeHandle);
    ASSERT_EQ(node, nullptr);
    DisposeNode(nodeHandle);
    nodeHandle = nullptr;
}

/**
 * @tc.name: NodeExtenedTest030
 * @tc.desc: Test GetLastChild function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeExtenedTest, NodeExtenedTest030, TestSize.Level1)
{
    ArkUI_NodeHandle node = GetLastChild(nullptr);
    ASSERT_EQ(node, nullptr);
    ArkUI_NodeHandle nodeHandle = CreateNode(ArkUI_NodeType::ARKUI_NODE_SWIPER);
    ASSERT_NE(nodeHandle, nullptr);
    node = GetLastChild(nodeHandle);
    ASSERT_EQ(node, nullptr);
    DisposeNode(nodeHandle);
    nodeHandle = nullptr;
}

/**
 * @tc.name: NodeExtenedTest031
 * @tc.desc: Test GetNextSibling function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeExtenedTest, NodeExtenedTest031, TestSize.Level1)
{
    ArkUI_NodeHandle node = GetNextSibling(nullptr);
    ASSERT_EQ(node, nullptr);
    ArkUI_NodeHandle nodeHandle = CreateNode(ArkUI_NodeType::ARKUI_NODE_SWIPER);
    ASSERT_NE(nodeHandle, nullptr);
    node = GetNextSibling(nodeHandle);
    ASSERT_EQ(node, nullptr);
    DisposeNode(nodeHandle);
    nodeHandle = nullptr;
}

/**
 * @tc.name: NodeExtenedTest032
 * @tc.desc: Test GetParent function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeExtenedTest, NodeExtenedTest032, TestSize.Level1)
{
    ArkUI_NodeHandle node = GetParent(nullptr);
    ASSERT_EQ(node, nullptr);
    ArkUI_NodeHandle nodeHandle = CreateNode(ArkUI_NodeType::ARKUI_NODE_SWIPER);
    ASSERT_NE(nodeHandle, nullptr);
    node = GetParent(nodeHandle);
    ASSERT_EQ(node, nullptr);
    DisposeNode(nodeHandle);
    nodeHandle = nullptr;
}

/**
 * @tc.name: NodeExtenedTest033
 * @tc.desc: Test GetParent function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeExtenedTest, NodeExtenedTest033, TestSize.Level1)
{
    ArkUI_NodeHandle nodeHandle = CreateNode(ArkUI_NodeType::ARKUI_NODE_SWIPER);
    ASSERT_NE(nodeHandle, nullptr);
    int32_t ret = RemoveAllChildren(nodeHandle);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    DisposeNode(nodeHandle);
    nodeHandle = nullptr;
}

/**
 * @tc.name: NodeExtenedTest034
 * @tc.desc: Test RegisterNodeCustomEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeExtenedTest, NodeExtenedTest034, TestSize.Level1)
{
    ArkUI_NodeHandle nodeHandle = CreateNode(ArkUI_NodeType::ARKUI_NODE_SWIPER);
    ASSERT_NE(nodeHandle, nullptr);
    nodeHandle->type = ArkUI_NodeType::ARKUI_NODE_CUSTOM;
    void* userData = nullptr;
    int32_t ret = RegisterNodeCustomEvent(nodeHandle, ArkUI_NodeCustomEventType::ARKUI_NODE_CUSTOM_EVENT_ON_DRAW_FRONT,
                                          0, userData);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    UnregisterNodeCustomEvent(nodeHandle, ArkUI_NodeCustomEventType::ARKUI_NODE_CUSTOM_EVENT_ON_DRAW_FRONT);
    ASSERT_EQ(nodeHandle->extraCustomData, nullptr);
    DisposeNode(nodeHandle);
    nodeHandle = nullptr;
}

/**
 * @tc.name: NodeExtenedTest035
 * @tc.desc: Test RegisterNodeCustomEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeExtenedTest, NodeExtenedTest035, TestSize.Level1)
{
    ArkUI_NodeHandle nodeHandle = CreateNode(ArkUI_NodeType::ARKUI_NODE_SWIPER);
    ASSERT_NE(nodeHandle, nullptr);
    nodeHandle->type = ArkUI_NodeType::ARKUI_NODE_CUSTOM;
    void* userData = nullptr;
    int32_t ret = RegisterNodeCustomEvent(nodeHandle, ArkUI_NodeCustomEventType::ARKUI_NODE_CUSTOM_EVENT_ON_DRAW_BEHIND,
                                          0, userData);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    UnregisterNodeCustomEvent(nodeHandle, ArkUI_NodeCustomEventType::ARKUI_NODE_CUSTOM_EVENT_ON_DRAW_BEHIND);
    ASSERT_EQ(nodeHandle->extraCustomData, nullptr);
    DisposeNode(nodeHandle);
    nodeHandle = nullptr;
}