/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include "test/unittest/core/event/event_manager_test_ng.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/input_event.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/mouse_event.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float WIDTH = 400.0f;
constexpr float HEIGHT = 400.0f;
const OffsetF COORDINATE_OFFSET(WIDTH, HEIGHT);
const std::string RESULT_SUCCESS_ONE = "sucess1";
const std::string RESULT_SUCCESS_TWO = "sucess2";
} // namespace

class InputEventTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};

void InputEventTestNg::SetUpTestSuite()
{
    GTEST_LOG_(INFO) << "InputEventTestNg SetUpTestCase";
}

void InputEventTestNg::TearDownTestSuite()
{
    GTEST_LOG_(INFO) << "InputEventTestNg TearDownTestCase";
}

void InputEventTestNg::SetUp()
{
    MockPipelineContext::SetUp();
}

void InputEventTestNg::TearDown()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: InputEventTest001
 * @tc.desc: test InputEvent
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, InputEventTest001, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    inputEventHub->mouseEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));
    inputEventHub->hoverEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));
    const OnMouseEventFunc onMouse = [](MouseInfo& info) {};
    OnMouseEventFunc onMouse1 = onMouse;
    inputEventHub->SetJSFrameNodeOnMouseEvent(std::move(onMouse1));
    OnMouseEventFunc onMouse2 = onMouse;
    inputEventHub->SetMouseEvent(std::move(onMouse2));

    TouchTestResult Result;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    inputEventHub->mouseEventActuator_->OnCollectMouseEvent(COORDINATE_OFFSET, getEventTargetImpl, Result);
    MouseInfo mouse;
    inputEventHub->mouseEventActuator_->mouseEventTarget_->onMouseCallback_(mouse);
    EXPECT_NE(inputEventHub, nullptr);
}

/**
 * @tc.name: InputEventTest002
 * @tc.desc: test InputEvent
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, InputEventTest002, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    inputEventHub->hoverEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));
    OnHoverFunc onHoverEventFunc;
    OnHoverFunc onHoverEventFunc2;
    inputEventHub->SetJSFrameNodeOnHoverEvent(std::move(onHoverEventFunc));
    inputEventHub->SetHoverEvent(std::move(onHoverEventFunc2));

    const OnHoverFunc onHover = [](bool, HoverInfo) {};
    OnHoverFunc onHover1 = onHover;
    auto onHoverEvent = AceType::MakeRefPtr<InputEvent>(std::move(onHover1));
    inputEventHub->AddOnHoverEvent(onHoverEvent);
    inputEventHub->AddOnHoverEvent(nullptr);

    TouchTestResult hoverResult;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    inputEventHub->hoverEventActuator_->OnCollectHoverEvent(COORDINATE_OFFSET, getEventTargetImpl, hoverResult);
    HoverInfo hover;
    inputEventHub->hoverEventActuator_->hoverEventTarget_->onHoverEventCallback_(true, hover);
    EXPECT_NE(inputEventHub, nullptr);
}

/**
 * @tc.name: InputEventTest003
 * @tc.desc: test InputEvent
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, InputEventTest003, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    inputEventHub->hoverEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));
    OnHoverFunc onHoverEventFunc;
    inputEventHub->SetHoverEvent(std::move(onHoverEventFunc));

    TouchTestResult hoverResult;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    inputEventHub->hoverEventActuator_->OnCollectHoverEvent(COORDINATE_OFFSET, getEventTargetImpl, hoverResult);
    HoverInfo hover;
    inputEventHub->hoverEventActuator_->hoverEventTarget_->onHoverEventCallback_(true, hover);
    EXPECT_NE(inputEventHub, nullptr);
}

/**
 * @tc.name: InputEventTest004
 * @tc.desc: test InputEvent
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, InputEventTest004, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    inputEventHub->hoverEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));
    OnHoverFunc onHoverEventFunc;
    inputEventHub->SetJSFrameNodeOnHoverEvent(std::move(onHoverEventFunc));

    TouchTestResult hoverResult;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    inputEventHub->hoverEventActuator_->OnCollectHoverEvent(COORDINATE_OFFSET, getEventTargetImpl, hoverResult);
    HoverInfo hover;
    inputEventHub->hoverEventActuator_->hoverEventTarget_->onHoverEventCallback_(true, hover);
    EXPECT_NE(inputEventHub, nullptr);
}

/**
 * @tc.name: InputEventTest005
 * @tc.desc: test InputEvent
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, InputEventTest005, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    inputEventHub->hoverEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));

    TouchTestResult hoverResult;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    inputEventHub->hoverEventActuator_->OnCollectHoverEvent(COORDINATE_OFFSET, getEventTargetImpl, hoverResult);
    EXPECT_NE(inputEventHub, nullptr);
}

/**
 * @tc.name: InputEventTest006
 * @tc.desc: test InputEvent
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, InputEventTest006, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    inputEventHub->axisEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));

    OnMouseEventFunc onAxis = [](MouseInfo& info) {};
    auto onAxisEvent = AceType::MakeRefPtr<InputEvent>(std::move(onAxis));
    inputEventHub->AddOnAxisEvent(onAxisEvent);
    inputEventHub->AddOnAxisEvent(nullptr);
    inputEventHub->axisEventActuator_->userCallback_ = onAxisEvent;

    AxisTestResult Result;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    inputEventHub->axisEventActuator_->OnCollectAxisEvent(COORDINATE_OFFSET, getEventTargetImpl, Result);
    AxisInfo axisInfo;
    inputEventHub->axisEventActuator_->axisEventTarget_->onAxisCallback_(axisInfo);
    EXPECT_NE(inputEventHub, nullptr);
}

/**
 * @tc.name: InputEventTest007
 * @tc.desc: test InputEvent
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, InputEventTest007, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    inputEventHub->axisEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));

    OnMouseEventFunc onAxis = [](MouseInfo& info) {};
    auto onAxisEvent = AceType::MakeRefPtr<InputEvent>(std::move(onAxis));
    inputEventHub->axisEventActuator_->userCallback_ = onAxisEvent;

    AxisTestResult Result;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    inputEventHub->axisEventActuator_->OnCollectAxisEvent(COORDINATE_OFFSET, getEventTargetImpl, Result);
    AxisInfo axisInfo;
    inputEventHub->axisEventActuator_->axisEventTarget_->onAxisCallback_(axisInfo);
    EXPECT_NE(inputEventHub, nullptr);
}

/**
 * @tc.name: InputEventTest008
 * @tc.desc: test InputEvent
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, InputEventTest008, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    inputEventHub->axisEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));

    OnMouseEventFunc onAxis = [](MouseInfo& info) {};
    auto onAxisEvent = AceType::MakeRefPtr<InputEvent>(std::move(onAxis));
    inputEventHub->AddOnAxisEvent(onAxisEvent);
    inputEventHub->AddOnAxisEvent(nullptr);

    AxisTestResult Result;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    inputEventHub->axisEventActuator_->OnCollectAxisEvent(COORDINATE_OFFSET, getEventTargetImpl, Result);
    AxisInfo axisInfo;
    inputEventHub->axisEventActuator_->axisEventTarget_->onAxisCallback_(axisInfo);
    EXPECT_NE(inputEventHub, nullptr);
}

/**
 * @tc.name: InputEventTest009
 * @tc.desc: test InputEvent
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, InputEventTest009, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    inputEventHub->axisEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));

    AxisTestResult Result;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    inputEventHub->axisEventActuator_->OnCollectAxisEvent(COORDINATE_OFFSET, getEventTargetImpl, Result);
    EXPECT_NE(inputEventHub, nullptr);
}

/**
 * @tc.name: InputEventTest010
 * @tc.desc: test InputEvent
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, InputEventTest010, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    EXPECT_NE(inputEventHub, nullptr);
    inputEventHub->mouseEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));
    int32_t count = 0;
    MouseInfo mouse;
    TouchTestResult result;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    inputEventHub->mouseEventActuator_->OnCollectMouseEventForTips(COORDINATE_OFFSET, getEventTargetImpl, result);

    auto mouseTask = [&count](MouseInfo& info) { count++; };
    auto mouseEvent1 = AceType::MakeRefPtr<InputEvent>(mouseTask);
    mouseEvent1->SetIstips(true);
    mouseEvent1->SetTipsFollowCursor(true);
    inputEventHub->mouseEventActuator_->inputEvents_.clear();
    inputEventHub->AddOnMouseEvent(std::move(mouseEvent1));
    inputEventHub->mouseEventActuator_->OnCollectMouseEventForTips(COORDINATE_OFFSET, getEventTargetImpl, result);
    inputEventHub->mouseEventActuator_->mouseEventTarget_->onMouseCallback_(mouse);
    EXPECT_EQ(count, 1);

    auto mouseEvent2 = AceType::MakeRefPtr<InputEvent>(mouseTask);
    mouseEvent2->SetIstips(true);
    inputEventHub->mouseEventActuator_->inputEvents_.clear();
    inputEventHub->AddOnMouseEvent(std::move(mouseEvent2));
    inputEventHub->mouseEventActuator_->OnCollectMouseEventForTips(COORDINATE_OFFSET, getEventTargetImpl, result);
    inputEventHub->mouseEventActuator_->mouseEventTarget_->onMouseCallback_(mouse);
    EXPECT_EQ(count, 1);

    auto mouseEvent3 = AceType::MakeRefPtr<InputEvent>(mouseTask);
    mouseEvent3->SetTipsFollowCursor(true);
    inputEventHub->mouseEventActuator_->inputEvents_.clear();
    inputEventHub->AddOnMouseEvent(std::move(mouseEvent3));
    inputEventHub->mouseEventActuator_->OnCollectMouseEventForTips(COORDINATE_OFFSET, getEventTargetImpl, result);
    inputEventHub->mouseEventActuator_->mouseEventTarget_->onMouseCallback_(mouse);
    EXPECT_EQ(count, 1);

    inputEventHub->mouseEventActuator_->inputEvents_.clear();
    inputEventHub->AddOnMouseEvent(nullptr);
    inputEventHub->mouseEventActuator_->OnCollectMouseEventForTips(COORDINATE_OFFSET, getEventTargetImpl, result);
    inputEventHub->mouseEventActuator_->mouseEventTarget_->onMouseCallback_(mouse);
    EXPECT_EQ(count, 1);
}

/**
 * @tc.name: OnCollectPenHoverEventTest001
 * @tc.desc: test InputEvent
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, OnCollectPenHoverEventTest001, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    inputEventHub->hoverEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));

    TouchTestResult hoverResult;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    inputEventHub->hoverEventActuator_->OnCollectPenHoverEvent(
        COORDINATE_OFFSET, getEventTargetImpl, hoverResult, frameNode);
    EXPECT_NE(inputEventHub, nullptr);
}

/**
 * @tc.name: OnCollectPenHoverEventTest002
 * @tc.desc: test InputEvent
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, OnCollectPenHoverEventTest002, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto hoverEventActuator =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));
    OnHoverFunc onHoverEventFunc;
    inputEventHub->SetJSFrameNodeOnHoverEvent(std::move(onHoverEventFunc));

    TouchTestResult hoverResult;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    OnMouseEventFunc onHoverEventFunc1 = [](MouseInfo& info) {};
    std::list<RefPtr<InputEvent>> inputEvents = {AceType::MakeRefPtr<InputEvent>(std::move(onHoverEventFunc1))};
    hoverEventActuator->inputEvents_ = inputEvents;
    hoverEventActuator->OnCollectPenHoverEvent(COORDINATE_OFFSET, getEventTargetImpl, hoverResult, frameNode);

    OnMouseEventFunc onAxis = [](MouseInfo& info) {};
    auto onAxisEvent = AceType::MakeRefPtr<InputEvent>(std::move(onAxis));
    hoverEventActuator->userCallback_ = onAxisEvent;
    OnMouseEventFunc onAxis2 = [](MouseInfo& info) {};
    auto onAxisEvent2 = AceType::MakeRefPtr<InputEvent>(std::move(onAxis2));
    hoverEventActuator->userJSFrameNodeCallback_ = onAxisEvent2;
    hoverEventActuator->OnCollectPenHoverEvent(COORDINATE_OFFSET, getEventTargetImpl, hoverResult, frameNode);

    HoverInfo hover;
    hoverEventActuator->penHoverEventTarget_->onPenHoverEventCallback_(true, hover);
    hoverEventActuator->userCallback_ = nullptr;
    hoverEventActuator->userJSFrameNodeCallback_ = nullptr;
    hoverEventActuator->penHoverEventTarget_->onPenHoverEventCallback_(true, hover);

    hoverEventActuator->inputEvents_.pop_back();
    hoverEventActuator->OnCollectPenHoverEvent(COORDINATE_OFFSET, getEventTargetImpl, hoverResult, frameNode);

    hoverEventActuator->userJSFrameNodeCallback_ = onAxisEvent2;
    hoverEventActuator->OnCollectPenHoverEvent(COORDINATE_OFFSET, getEventTargetImpl, hoverResult, frameNode);
    
    EXPECT_NE(inputEventHub, nullptr);
}

/**
 * @tc.name: OnCollectPenHoverMoveEvent001
 * @tc.desc: test InputEvent
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, OnCollectPenHoverMoveEvent001, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    inputEventHub->hoverEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));

    TouchTestResult hoverResult;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    inputEventHub->hoverEventActuator_->
		OnCollectPenHoverMoveEvent(COORDINATE_OFFSET, getEventTargetImpl, hoverResult, frameNode);
    EXPECT_NE(inputEventHub, nullptr);
}

/**
 * @tc.name: OnCollectPenHoverMoveEvent002
 * @tc.desc: test InputEvent
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, OnCollectPenHoverMoveEvent002, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto hoverEventActuator =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));
    OnHoverFunc onHoverEventFunc;
    inputEventHub->SetJSFrameNodeOnHoverEvent(std::move(onHoverEventFunc));
    
    TouchTestResult hoverResult;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    OnMouseEventFunc onHoverEventFunc1 = [](MouseInfo& info) {};
    std::list<RefPtr<InputEvent>> inputEvents = {AceType::MakeRefPtr<InputEvent>(std::move(onHoverEventFunc1))};
    hoverEventActuator->inputEvents_ = inputEvents;
    hoverEventActuator->OnCollectPenHoverMoveEvent(COORDINATE_OFFSET, getEventTargetImpl, hoverResult, frameNode);
    EXPECT_NE(inputEventHub, nullptr);
}

/**
 * @tc.name: OnCollectPenHoverMoveEvent003
 * @tc.desc: Test InputEvent
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, OnCollectPenHoverMoveEvent003, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto hoverEventActuator =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));
    TouchTestResult hoverResult;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    OnMouseEventFunc onAxis = [](MouseInfo& info) {};
    auto userEvent = AceType::MakeRefPtr<InputEvent>(std::move(onAxis));
    hoverEventActuator->userCallback_ = userEvent;
    inputEventHub->AddOnAxisEvent(userEvent);
    hoverEventActuator->OnCollectPenHoverMoveEvent(COORDINATE_OFFSET, getEventTargetImpl, hoverResult, frameNode);
    EXPECT_NE(inputEventHub, nullptr);
}

/**
 * @tc.name: OnCollectPenHoverMoveEvent004
 * @tc.desc: Test InputEvent
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, OnCollectPenHoverMoveEvent004, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    inputEventHub->accessibilityHoverEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));

    TouchTestResult result;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    inputEventHub->accessibilityHoverEventActuator_->OnCollectPenHoverMoveEvent(
        COORDINATE_OFFSET, getEventTargetImpl, result, frameNode);
    EXPECT_TRUE(result.empty());
}
/**
 * @tc.name: OnCollectAccessibilityHoverEvent001
 * @tc.desc: test InputEvent
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, OnCollectAccessibilityHoverEvent001, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    inputEventHub->hoverEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));

    TouchTestResult hoverResult;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    inputEventHub->hoverEventActuator_->
        OnCollectAccessibilityHoverEvent(COORDINATE_OFFSET, getEventTargetImpl, hoverResult, frameNode);
    EXPECT_NE(inputEventHub, nullptr);
}

/**
 * @tc.name: OnCollectAccessibilityHoverEvent002
 * @tc.desc: test InputEvent
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, OnCollectAccessibilityHoverEvent002, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto hoverEventActuator =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));
    OnHoverFunc onHoverEventFunc;
    inputEventHub->SetJSFrameNodeOnHoverEvent(std::move(onHoverEventFunc));
    
    TouchTestResult hoverResult;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    OnMouseEventFunc onHoverEventFunc1 = [](MouseInfo& info) {};
    std::list<RefPtr<InputEvent>> inputEvents = {AceType::MakeRefPtr<InputEvent>(std::move(onHoverEventFunc1))};
    hoverEventActuator->inputEvents_ = inputEvents;
    hoverEventActuator->OnCollectAccessibilityHoverEvent(COORDINATE_OFFSET, getEventTargetImpl, hoverResult, frameNode);
    EXPECT_NE(inputEventHub, nullptr);
}

/**
 * @tc.name: OnCollectAccessibilityHoverEvent003
 * @tc.desc: Test InputEvent
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, OnCollectAccessibilityHoverEvent003, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto hoverEventActuator =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));
    TouchTestResult hoverResult;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    OnMouseEventFunc onAxis = [](MouseInfo& info) {};
    auto userEvent = AceType::MakeRefPtr<InputEvent>(std::move(onAxis));
    hoverEventActuator->userCallback_ = userEvent;
    inputEventHub->AddOnAxisEvent(userEvent);
    hoverEventActuator->OnCollectAccessibilityHoverEvent(COORDINATE_OFFSET, getEventTargetImpl, hoverResult, frameNode);
    EXPECT_NE(inputEventHub, nullptr);
}

/**
 * @tc.name: OnCollectAccessibilityHoverEvent004
 * @tc.desc: Test InputEvent
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, OnCollectAccessibilityHoverEvent004, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    inputEventHub->accessibilityHoverEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));

    TouchTestResult result;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    inputEventHub->accessibilityHoverEventActuator_->OnCollectAccessibilityHoverEvent(
        COORDINATE_OFFSET, getEventTargetImpl, result, frameNode);
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: OnCollectAxisEvent001
 * @tc.desc: test InputEvent
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, OnCollectAxisEvent001, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);

    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    inputEventHub->axisEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));
    OnMouseEventFunc onAxis = [](MouseInfo& info) {};
    auto onAxisEvent = AceType::MakeRefPtr<InputEvent>(std::move(onAxis));
    inputEventHub->axisEventActuator_->userCallback_ = onAxisEvent;

    AxisTestResult Result;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();

    inputEventHub->axisEventActuator_->OnCollectAxisEvent(COORDINATE_OFFSET, getEventTargetImpl, Result);
    inputEventHub->axisEventActuator_->inputEvents_.emplace_back(onAxisEvent);

    inputEventHub->axisEventActuator_->OnCollectAxisEvent(COORDINATE_OFFSET, getEventTargetImpl, Result);
    inputEventHub->axisEventActuator_->userCallback_ = onAxisEvent;
    inputEventHub->axisEventActuator_->OnCollectAxisEvent(COORDINATE_OFFSET, getEventTargetImpl, Result);

    AxisInfo axisInfo;
    inputEventHub->axisEventActuator_->axisEventTarget_->onAxisCallback_(axisInfo);
    EXPECT_NE(inputEventHub, nullptr);
}

/**
 * @tc.name: ProcessTipsMouseTestHit001
 * @tc.desc: test ProcessTipsMouseTestHit
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, ProcessTipsMouseTestHit001, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);

    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    EXPECT_NE(inputEventHub, nullptr);
    inputEventHub->mouseEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));

    TouchTestResult result;
    inputEventHub->ProcessTipsMouseTestHit(COORDINATE_OFFSET, result);
    EXPECT_EQ(result.size(), 0);
}
} // namespace OHOS::Ace::NG