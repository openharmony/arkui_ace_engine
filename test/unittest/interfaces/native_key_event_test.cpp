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
#include <cstdint>
#include <iostream>

#include "gtest/gtest.h"
#define private public
#define protected public
#include "native_key_event.h"
#include "event_converter.h"
#include "native_interface.h"
#include "native_node.h"
#include "native_type.h"
#include "node_model.h"
#include "ui_input_event.h"
#include "event/ui_input_event_impl.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace {
namespace {
constexpr uint32_t ARKUI_UNICODE = 98;
constexpr int32_t ARKUI_DEVICE_ID = 1;
constexpr uint64_t ARKUI_TIME = 20;
const char* ARKUI_KEY_TEXT = "k";
} // namespace
class NativeKeyEventTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        NG::MockPipelineContext::SetUp();
        MockContainer::SetUp();
        MockContainer::Current()->pipelineContext_ = NG::MockPipelineContext::GetCurrent();
        MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
        MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        PipelineBase::GetCurrentContext()->SetThemeManager(themeManager);
    }
    static void TearDownTestSuite()
    {
        NG::MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }
    void SetUp() {}
    void TearDown() {}
};

/**
 * @tc.name: NativeKeyEventTest001
 * @tc.desc: test NODE_ON_KEY_EVENT;
 * @tc.type: FUNC
 */
HWTEST_F(NativeKeyEventTest, NativeKeyEventTest001, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto node = nodeAPI->createNode(ARKUI_NODE_STACK);
    EXPECT_EQ(nodeAPI->registerNodeEvent(nullptr, NODE_ON_KEY_EVENT, 0, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(nodeAPI->registerNodeEvent(node, static_cast<ArkUI_NodeEventType>(-1), 0, nullptr),
        ARKUI_ERROR_CODE_ATTRIBUTE_OR_EVENT_NOT_SUPPORTED);
    nodeAPI->unregisterNodeEvent(nullptr, NODE_ON_KEY_EVENT);
    nodeAPI->unregisterNodeEvent(node, NODE_ON_KEY_EVENT);
    nodeAPI->disposeNode(node);
}

/**
 * @tc.name: NativeKeyEventTest002
 * @tc.desc: test NODE_ON_KEY_PRE_IME;
 * @tc.type: FUNC
 */
HWTEST_F(NativeKeyEventTest, NativeKeyEventTest002, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto node = nodeAPI->createNode(ARKUI_NODE_STACK);
    EXPECT_EQ(nodeAPI->registerNodeEvent(nullptr, NODE_ON_KEY_EVENT, 0, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(nodeAPI->registerNodeEvent(node, static_cast<ArkUI_NodeEventType>(-1), 0, nullptr),
        ARKUI_ERROR_CODE_ATTRIBUTE_OR_EVENT_NOT_SUPPORTED);
    nodeAPI->unregisterNodeEvent(nullptr, NODE_ON_KEY_PRE_IME);
    nodeAPI->unregisterNodeEvent(node, NODE_ON_KEY_PRE_IME);
    nodeAPI->disposeNode(node);
}

/**
 * @tc.name: NativeKeyEventTest003
 * @tc.desc: Test OH_ArkUI_KeyEvent_GetType function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeKeyEventTest, NativeKeyEventTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent event = { 1, 0 };
    event.origin = nullptr;
    auto uiInputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&event);
    auto type = OH_ArkUI_KeyEvent_GetType(uiInputEvent);
    EXPECT_EQ(type, ArkUI_KeyEventType::ARKUI_KEY_EVENT_UNKNOWN);
}

/**
 * @tc.name: NativeKeyEventTest004
 * @tc.desc: Test the KeyEvent property functions.
 * @tc.type: FUNC
 */
HWTEST_F(NativeKeyEventTest, NativeKeyEventTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    event.kind = ArkUIEventCategory::KEY_INPUT_EVENT;
    event.keyEvent.subKind = ArkUIEventSubKind::ON_KEY_EVENT;
    event.keyEvent.type = static_cast<ArkUI_Int32>(OHOS::Ace::KeyAction::UP);
    event.keyEvent.keyCode = static_cast<ArkUI_Int32>(OHOS::Ace::KeyCode::KEY_VOLUME_UP);
    event.keyEvent.keySource = static_cast<ArkUI_Int32>(OHOS::Ace::SourceType::MOUSE);
    event.keyEvent.intentionCode = static_cast<ArkUI_Int32>(OHOS::Ace::KeyIntention::INTENTION_UP);
    event.keyEvent.unicode = ARKUI_UNICODE;
    event.keyEvent.deviceId = ARKUI_DEVICE_ID;
    event.keyEvent.timestamp = ARKUI_TIME;
    event.keyEvent.keyText = ARKUI_KEY_TEXT;
    uiInputEvent.inputEvent = &event.keyEvent;
    uiInputEvent.eventTypeId = C_KEY_EVENT_ID;
    nodeEvent.origin = &uiInputEvent;
    nodeEvent.category = NodeEventCategory::NODE_EVENT_CATEGORY_INPUT_EVENT;
    auto inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(&nodeEvent);

    /**
     * @tc.steps: step2. call functions.
     */
    auto type = OH_ArkUI_KeyEvent_GetType(inputEvent);
    auto code = OH_ArkUI_KeyEvent_GetKeyCode(inputEvent);
    auto keySource = OH_ArkUI_KeyEvent_GetKeySource(inputEvent);
    auto intensionCode = OH_ArkUI_KeyEvent_GetKeyIntensionCode(inputEvent);
    auto unicode = OH_ArkUI_KeyEvent_GetUnicode(inputEvent);
    auto diviceId = OH_ArkUI_UIInputEvent_GetDeviceId(inputEvent);
    auto time = OH_ArkUI_UIInputEvent_GetEventTime(inputEvent);
    auto keyText = OH_ArkUI_KeyEvent_GetKeyText(inputEvent);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(type, ArkUI_KeyEventType::ARKUI_KEY_EVENT_UP);
    EXPECT_EQ(code, ArkUI_KeyCode::ARKUI_KEYCODE_VOLUME_UP);
    EXPECT_EQ(keySource, ArkUI_KeySourceType::ARKUI_KEY_SOURCE_TYPE_MOUSE);
    EXPECT_EQ(intensionCode, ArkUI_KeyIntension::ARKUI_KEY_INTENSION_UP);
    EXPECT_EQ(unicode, ARKUI_UNICODE);
    EXPECT_EQ(diviceId, ARKUI_DEVICE_ID);
    EXPECT_EQ(time, ARKUI_TIME);
    EXPECT_NE(keyText, nullptr);
}

/**
 * @tc.name: NativeKeyEventTest005
 * @tc.desc: test NODE_DISPATCH_KEY_EVENT;
 * @tc.type: FUNC
 */
HWTEST_F(NativeKeyEventTest, NativeKeyEventTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_NodeEvent, related function is called.
     */
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto node = nodeAPI->createNode(ARKUI_NODE_STACK);

    /**
     * @tc.steps: step2. call functions.
     */
    EXPECT_EQ(nodeAPI->registerNodeEvent(nullptr, NODE_ON_KEY_EVENT, 0, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(nodeAPI->registerNodeEvent(node, static_cast<ArkUI_NodeEventType>(-1), 0, nullptr),
        ARKUI_ERROR_CODE_ATTRIBUTE_OR_EVENT_NOT_SUPPORTED);
    nodeAPI->unregisterNodeEvent(nullptr, NODE_DISPATCH_KEY_EVENT);
    nodeAPI->unregisterNodeEvent(node, NODE_DISPATCH_KEY_EVENT);
    nodeAPI->disposeNode(node);
}

/**
 * @tc.name: NativeKeyEventTest006
 * @tc.desc: Test OH_ArkUI_KeyEvent_Dispatch function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeKeyEventTest, NativeKeyEventTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node.
     */
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto node = nodeAPI->createNode(ARKUI_NODE_STACK);

    /**
     * @tc.steps: step2. create ArkUI_NodeEvent, related function is called.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent event;
    ArkUI_UIInputEvent uiInputEvent;
    event.kind = ArkUIEventCategory::KEY_INPUT_EVENT;
    event.keyEvent.subKind = ArkUIEventSubKind::ON_KEY_EVENT;
    event.keyEvent.type = static_cast<ArkUI_Int32>(OHOS::Ace::KeyAction::UP);
    event.keyEvent.keyCode = static_cast<ArkUI_Int32>(OHOS::Ace::KeyCode::KEY_SPACE);
    event.keyEvent.keySource = static_cast<ArkUI_Int32>(OHOS::Ace::SourceType::KEYBOARD);
    event.keyEvent.intentionCode = static_cast<ArkUI_Int32>(OHOS::Ace::KeyIntention::INTENTION_UP);
    event.keyEvent.unicode = ARKUI_UNICODE;
    event.keyEvent.deviceId = ARKUI_DEVICE_ID;
    event.keyEvent.timestamp = ARKUI_TIME;
    event.keyEvent.keyText = ARKUI_KEY_TEXT;
    uiInputEvent.inputEvent = &event.keyEvent;
    nodeEvent.origin = &uiInputEvent;
    nodeEvent.node = node;

    /**
     * @tc.steps: step3. call functions.
     */
    bool flag = false;
    nodeAPI->registerNodeEvent(node, NODE_DISPATCH_KEY_EVENT, 0, &flag);
    NodeModel::AddNodeEventReceiver(node, [](ArkUI_NodeEvent* event) {
        auto userData = reinterpret_cast<bool*>(event->userData);
        *userData = true;
    });
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node->uiNodeHandle);
    frameNode->GetOrCreateFocusHub()->currentFocus_ = true;
    OH_ArkUI_KeyEvent_Dispatch(node, &uiInputEvent);
    nodeAPI->unregisterNodeEvent(node, NODE_DISPATCH_KEY_EVENT);
    NodeModel::DisposeNode(node);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(flag, true);
}
} // namespace OHOS::Ace