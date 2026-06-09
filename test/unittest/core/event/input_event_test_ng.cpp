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
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

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
constexpr int32_t DOUBLE = 2;
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
    inputEventHub->SetFrameNodeCommonOnMouseEvent(std::move(onMouse1));
    OnMouseEventFunc onMouse2 = onMouse;
    inputEventHub->SetMouseEvent(std::move(onMouse2));
    inputEventHub->CreateMouseEventActuator();

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
    OnHoverFunc onHoverEventFunc = [](bool, HoverInfo& info) {};
    OnHoverFunc onHoverEventFunc2 = [](bool, HoverInfo& info) {};
    inputEventHub->SetFrameNodeCommonOnHoverEvent(std::move(onHoverEventFunc));
    inputEventHub->SetHoverEvent(std::move(onHoverEventFunc2));
    inputEventHub->CreateHoverEventActuator();
    ASSERT_NE(inputEventHub->hoverEventActuator_, nullptr);

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
    OnHoverFunc onHoverEventFunc = [](bool, HoverInfo& info) {};
    inputEventHub->SetHoverEvent(std::move(onHoverEventFunc));
    inputEventHub->CreateHoverEventActuator();

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
    OnHoverFunc onHoverEventFunc = [](bool, HoverInfo& info) {};
    inputEventHub->SetFrameNodeCommonOnHoverEvent(std::move(onHoverEventFunc));
    inputEventHub->CreateHoverEventActuator();
    ASSERT_NE(inputEventHub->hoverEventActuator_, nullptr);

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
    inputEventHub->CreateAxisEventActuator();

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
    inputEventHub->CreateAxisEventActuator();

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
    inputEventHub->CreateMouseEventActuator();
    inputEventHub->mouseEventActuator_->OnCollectMouseEventForTips(COORDINATE_OFFSET, getEventTargetImpl, result);
    inputEventHub->mouseEventActuator_->mouseEventTarget_->onMouseCallback_(mouse);
    EXPECT_EQ(count, 1);

    auto mouseEvent2 = AceType::MakeRefPtr<InputEvent>(mouseTask);
    mouseEvent2->SetIstips(true);
    inputEventHub->mouseEventActuator_->inputEvents_.clear();
    inputEventHub->AddOnMouseEvent(std::move(mouseEvent2));
    inputEventHub->CreateMouseEventActuator();
    inputEventHub->mouseEventActuator_->OnCollectMouseEventForTips(COORDINATE_OFFSET, getEventTargetImpl, result);
    inputEventHub->mouseEventActuator_->mouseEventTarget_->onMouseCallback_(mouse);
    EXPECT_EQ(count, 1);

    auto mouseEvent3 = AceType::MakeRefPtr<InputEvent>(mouseTask);
    mouseEvent3->SetTipsFollowCursor(true);
    inputEventHub->mouseEventActuator_->inputEvents_.clear();
    inputEventHub->AddOnMouseEvent(std::move(mouseEvent3));
    inputEventHub->CreateMouseEventActuator();
    inputEventHub->mouseEventActuator_->OnCollectMouseEventForTips(COORDINATE_OFFSET, getEventTargetImpl, result);
    inputEventHub->mouseEventActuator_->mouseEventTarget_->onMouseCallback_(mouse);
    EXPECT_EQ(count, 1);

    inputEventHub->mouseEventActuator_->inputEvents_.clear();
    inputEventHub->AddOnMouseEvent(nullptr);
    inputEventHub->CreateMouseEventActuator();
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
    inputEventHub->SetFrameNodeCommonOnHoverEvent(std::move(onHoverEventFunc));

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
    inputEventHub->SetFrameNodeCommonOnHoverEvent(std::move(onHoverEventFunc));
    
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
    inputEventHub->SetFrameNodeCommonOnHoverEvent(std::move(onHoverEventFunc));
    
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
 * @tc.name: OnCollectCoastingAxisEvent001
 * @tc.desc: test InputEvent
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, OnCollectCoastingAxisEvent001, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);

    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    inputEventHub->coastingAxisEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));
    AxisTestResult result;
    inputEventHub->coastingAxisEventActuator_->OnCollectCoastingAxisEvent(result);
    EXPECT_EQ(result.size(), 0);
    OnCoastingAxisEventFunc onCoastingAxis = [](CoastingAxisInfo& info) {info.SetHorizontalAxis(100);};
    auto onCoastingAxisEvent = AceType::MakeRefPtr<InputEvent>(std::move(onCoastingAxis));
    inputEventHub->coastingAxisEventActuator_->userCallback_ = onCoastingAxisEvent;

    inputEventHub->coastingAxisEventActuator_->OnCollectCoastingAxisEvent(result);
    EXPECT_EQ(result.size(), 1);
    inputEventHub->coastingAxisEventActuator_->inputEvents_.emplace_back(onCoastingAxisEvent);

    inputEventHub->coastingAxisEventActuator_->OnCollectCoastingAxisEvent(result);
    EXPECT_EQ(result.size(), 2);
    inputEventHub->coastingAxisEventActuator_->userCallback_ = onCoastingAxisEvent;
    inputEventHub->coastingAxisEventActuator_->OnCollectCoastingAxisEvent(result);
    EXPECT_EQ(result.size(), 3);

    CoastingAxisInfo info;
    EXPECT_EQ(info.GetHorizontalAxis(), 0);
    inputEventHub->coastingAxisEventActuator_->coastingAxisEventTarget_->onCoastingAxisCallback_(info);
    EXPECT_EQ(info.GetHorizontalAxis(), 100);
    info.SetHorizontalAxis(0);
    inputEventHub->coastingAxisEventActuator_->userCallback_ = nullptr;
    inputEventHub->coastingAxisEventActuator_->coastingAxisEventTarget_->onCoastingAxisCallback_(info);
    EXPECT_EQ(info.GetHorizontalAxis(), 0);
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

/**
 * @tc.name: RemoveAllTipsEvents001
 * @tc.desc: test RemoveAllTipsEvents
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, RemoveAllTipsEvents001, TestSize.Level1)
{
    auto actuator = AceType::MakeRefPtr<InputEventActuator>(nullptr);
    auto hoverTask1 = [](bool isHover) {};
    auto hoverTask2 = [](bool isHover) {};
    auto hoverEvent1 = AceType::MakeRefPtr<InputEvent>(std::move(hoverTask1));
    auto hoverEvent2 = AceType::MakeRefPtr<InputEvent>(std::move(hoverTask2));
    hoverEvent1->SetIstips(true);
    hoverEvent2->SetIstips(true);
    actuator->AddInputEvent(hoverEvent1);
    actuator->AddInputEvent(hoverEvent2);
    EXPECT_EQ(actuator->inputEvents_.size(), DOUBLE);
    actuator->RemoveAllTipsEvents();
    EXPECT_EQ(actuator->inputEvents_.size(), 0);
}

/**
 * @tc.name: InputEventTest011
 * @tc.desc: Test OnCollectMouseEvent with userJSFrameNodeCallback_
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, InputEventTest011, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    inputEventHub->mouseEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));

    OnMouseEventFunc onJSFrameNode = [](MouseInfo& info) {};
    auto onJSFrameNodeEvent = AceType::MakeRefPtr<InputEvent>(std::move(onJSFrameNode));
    inputEventHub->mouseEventActuator_->userJSFrameNodeCallback_ = onJSFrameNodeEvent;

    TouchTestResult result;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    inputEventHub->mouseEventActuator_->OnCollectMouseEvent(COORDINATE_OFFSET, getEventTargetImpl, result);
    EXPECT_EQ(result.size(), 1);

    MouseInfo mouse;
    inputEventHub->mouseEventActuator_->mouseEventTarget_->onMouseCallback_(mouse);
    EXPECT_NE(inputEventHub, nullptr);
}

/**
 * @tc.name: OnCollectHoverEventForTips001
 * @tc.desc: Test OnCollectHoverEventForTips with empty inputEvents_
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, OnCollectHoverEventForTips001, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    inputEventHub->hoverEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));

    // Clear inputEvents_ to test early return
    inputEventHub->hoverEventActuator_->inputEvents_.clear();

    TouchTestResult result;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    inputEventHub->hoverEventActuator_->OnCollectHoverEventForTips(COORDINATE_OFFSET, getEventTargetImpl, result);
    EXPECT_EQ(result.size(), 0);
    EXPECT_NE(inputEventHub, nullptr);
}

/**
 * @tc.name: OnCollectHoverEventForTips002
 * @tc.desc: Test OnCollectHoverEventForTips with callback->GetIstips() true
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, OnCollectHoverEventForTips002, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    inputEventHub->hoverEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));

    int32_t callCount = 0;
    auto hoverTask = [&callCount](bool, HoverInfo& info) { callCount++; };
    auto hoverEvent = AceType::MakeRefPtr<InputEvent>(std::move(hoverTask));
    hoverEvent->SetIstips(true);
    inputEventHub->hoverEventActuator_->inputEvents_.clear();
    inputEventHub->hoverEventActuator_->inputEvents_.emplace_back(hoverEvent);

    TouchTestResult result;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    inputEventHub->hoverEventActuator_->OnCollectHoverEventForTips(COORDINATE_OFFSET, getEventTargetImpl, result);

    HoverInfo hover;
    inputEventHub->hoverEventActuator_->hoverEventTarget_->onHoverEventCallback_(true, hover);
    EXPECT_EQ(callCount, 1);
    EXPECT_NE(inputEventHub, nullptr);
}

/**
 * @tc.name: OnCollectPenHoverMoveEvent005
 * @tc.desc: Test OnCollectPenHoverMoveEvent with userJSCallback
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, OnCollectPenHoverMoveEvent005, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto hoverEventActuator =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));

    OnMouseEventFunc onJSFrameNode = [](MouseInfo& info) {};
    auto onJSFrameNodeEvent = AceType::MakeRefPtr<InputEvent>(std::move(onJSFrameNode));
    hoverEventActuator->userJSFrameNodeCallback_ = onJSFrameNodeEvent;

    TouchTestResult hoverResult;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    hoverEventActuator->OnCollectPenHoverMoveEvent(COORDINATE_OFFSET, getEventTargetImpl, hoverResult, frameNode);
    EXPECT_EQ(hoverResult.size(), 1);

    HoverInfo hover;
    hoverEventActuator->penHoverMoveEventTarget_->onPenHoverMoveEventCallback_(hover);
    EXPECT_NE(inputEventHub, nullptr);
}

/**
 * @tc.name: InputEventOperatorTest001
 * @tc.desc: Test InputEvent operator() overloads with valid callbacks.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, InputEventOperatorTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. operator()(MouseInfo&) with callback.
     * @tc.expected: callback is invoked.
     */
    int32_t mouseCount = 0;
    OnMouseEventFunc onMouse = [&mouseCount](MouseInfo& info) { mouseCount++; };
    auto mouseEvent = AceType::MakeRefPtr<InputEvent>(std::move(onMouse));
    MouseInfo mouseInfo;
    (*mouseEvent)(mouseInfo);
    EXPECT_EQ(mouseCount, 1);

    /**
     * @tc.steps: step2. operator()(bool, HoverInfo&) with callback.
     * @tc.expected: callback is invoked.
     */
    int32_t hoverCount = 0;
    OnHoverFunc onHover = [&hoverCount](bool, HoverInfo&) { hoverCount++; };
    auto hoverEvent = AceType::MakeRefPtr<InputEvent>(std::move(onHover));
    HoverInfo hoverInfo;
    (*hoverEvent)(true, hoverInfo);
    EXPECT_EQ(hoverCount, 1);

    /**
     * @tc.steps: step3. operator()(bool) with OnHoverEventFunc callback.
     * @tc.expected: callback is invoked.
     */
    int32_t hoverEventCount = 0;
    OnHoverEventFunc onHoverEvent = [&hoverEventCount](bool) {
        hoverEventCount++;
        return true;
    };
    auto hoverEventInput = AceType::MakeRefPtr<InputEvent>(std::move(onHoverEvent));
    (*hoverEventInput)(true);
    EXPECT_EQ(hoverEventCount, 1);

    /**
     * @tc.steps: step4. operator()(AxisInfo&) with callback.
     * @tc.expected: callback is invoked.
     */
    int32_t axisCount = 0;
    OnAxisEventFunc onAxis = [&axisCount](AxisInfo& info) { axisCount++; };
    auto axisEvent = AceType::MakeRefPtr<InputEvent>(std::move(onAxis));
    AxisInfo axisInfo;
    (*axisEvent)(axisInfo);
    EXPECT_EQ(axisCount, 1);

    /**
     * @tc.steps: step5. operator()(CoastingAxisInfo&) with callback.
     * @tc.expected: callback is invoked.
     */
    int32_t coastingCount = 0;
    OnCoastingAxisEventFunc onCoasting = [&coastingCount](CoastingAxisInfo& info) { coastingCount++; };
    auto coastingEvent = AceType::MakeRefPtr<InputEvent>(std::move(onCoasting));
    CoastingAxisInfo coastingInfo;
    (*coastingEvent)(coastingInfo);
    EXPECT_EQ(coastingCount, 1);

    /**
     * @tc.steps: step6. operator()(HoverInfo&) with OnHoverMoveFunc callback.
     * @tc.expected: callback is invoked.
     */
    int32_t hoverMoveCount = 0;
    OnHoverMoveFunc onHoverMove = [&hoverMoveCount](HoverInfo& info) { hoverMoveCount++; };
    auto hoverMoveEvent = AceType::MakeRefPtr<InputEvent>(std::move(onHoverMove));
    HoverInfo hoverMoveInfo;
    (*hoverMoveEvent)(hoverMoveInfo);
    EXPECT_EQ(hoverMoveCount, 1);
}

/**
 * @tc.name: InputEventOperatorNullTest001
 * @tc.desc: Test InputEvent operator() overloads with null callbacks.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, InputEventOperatorNullTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. operator()(MouseInfo&) with null callback.
     * @tc.expected: callback is nullptr, operator() returns without crash.
     */
    OnMouseEventFunc onMouse = nullptr;
    auto mouseEvent = AceType::MakeRefPtr<InputEvent>(std::move(onMouse));
    ASSERT_NE(mouseEvent, nullptr);
    EXPECT_FALSE(mouseEvent->GetOnMouseEventFunc());
    MouseInfo mouseInfo;
    (*mouseEvent)(mouseInfo);

    /**
     * @tc.steps: step2. operator()(bool, HoverInfo&) with null callback.
     * @tc.expected: callback is nullptr, operator() returns without crash.
     */
    OnHoverFunc onHover = nullptr;
    auto hoverEvent = AceType::MakeRefPtr<InputEvent>(std::move(onHover));
    ASSERT_NE(hoverEvent, nullptr);
    EXPECT_FALSE(hoverEvent->GetOnHoverFunc());
    HoverInfo hoverInfo;
    (*hoverEvent)(true, hoverInfo);

    /**
     * @tc.steps: step3. operator()(bool) with null OnHoverEventFunc.
     * @tc.expected: callback is nullptr, operator() returns without crash.
     */
    OnHoverEventFunc onHoverEvent = nullptr;
    auto hoverEventInput = AceType::MakeRefPtr<InputEvent>(std::move(onHoverEvent));
    ASSERT_NE(hoverEventInput, nullptr);
    EXPECT_FALSE(hoverEventInput->GetOnHoverEventFunc());
    (*hoverEventInput)(true);

    /**
     * @tc.steps: step4. operator()(AxisInfo&) with null callback.
     * @tc.expected: callback is nullptr, operator() returns without crash.
     */
    OnAxisEventFunc onAxis = nullptr;
    auto axisEvent = AceType::MakeRefPtr<InputEvent>(std::move(onAxis));
    ASSERT_NE(axisEvent, nullptr);
    EXPECT_FALSE(axisEvent->GetOnAxisEventFunc());
    AxisInfo axisInfo;
    (*axisEvent)(axisInfo);

    /**
     * @tc.steps: step5. operator()(CoastingAxisInfo&) with null callback.
     * @tc.expected: no crash (no getter for CoastingAxisEventFunc).
     */
    OnCoastingAxisEventFunc onCoasting = nullptr;
    auto coastingEvent = AceType::MakeRefPtr<InputEvent>(std::move(onCoasting));
    ASSERT_NE(coastingEvent, nullptr);
    CoastingAxisInfo coastingInfo;
    (*coastingEvent)(coastingInfo);

    /**
     * @tc.steps: step6. operator()(HoverInfo&) with null OnHoverMoveFunc.
     * @tc.expected: callback is nullptr, operator() returns without crash.
     */
    OnHoverMoveFunc onHoverMove = nullptr;
    auto hoverMoveEvent = AceType::MakeRefPtr<InputEvent>(std::move(onHoverMove));
    ASSERT_NE(hoverMoveEvent, nullptr);
    EXPECT_FALSE(hoverMoveEvent->GetOnHoverMoveEventFunc());
    HoverInfo hoverMoveInfo;
    (*hoverMoveEvent)(hoverMoveInfo);
}

/**
 * @tc.name: InputEventActuatorInternalTest001
 * @tc.desc: Test InputEventActuator ClearUserCallback, ClearJSFrameNodeCallback, HasUserCallback.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, InputEventActuatorInternalTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create actuator with empty WeakPtr so constructor returns early.
     * @tc.expected: HasUserCallback returns false initially.
     */
    auto actuator = AceType::MakeRefPtr<InputEventActuator>(WeakPtr<InputEventHub>());
    EXPECT_FALSE(actuator->HasUserCallback());

    /**
     * @tc.steps: step2. Set user callback and verify.
     * @tc.expected: HasUserCallback returns true.
     */
    OnMouseEventFunc onMouse = [](MouseInfo& info) {};
    actuator->ReplaceInputEvent(std::move(onMouse));
    EXPECT_TRUE(actuator->HasUserCallback());

    /**
     * @tc.steps: step3. Clear user callback and verify.
     * @tc.expected: HasUserCallback returns false.
     */
    actuator->ClearUserCallback();
    EXPECT_FALSE(actuator->HasUserCallback());

    /**
     * @tc.steps: step4. Set JSFrameNode callback and clear it.
     * @tc.expected: ClearJSFrameNodeCallback works without crash.
     */
    OnMouseEventFunc onJSFrameNode = [](MouseInfo& info) {};
    actuator->ReplaceJSFrameNodeInputEvent(std::move(onJSFrameNode));
    actuator->ClearJSFrameNodeCallback();
    EXPECT_FALSE(actuator->HasUserCallback());

    /**
     * @tc.steps: step5. Call ClearUserCallback and ClearJSFrameNodeCallback on empty actuator.
     * @tc.expected: no crash.
     */
    actuator->ClearUserCallback();
    actuator->ClearJSFrameNodeCallback();
}

/**
 * @tc.name: OnCollectHoverEffectTest001
 * @tc.desc: Test OnCollectHoverEffect creates hoverEffectTarget_ and adds to result.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, OnCollectHoverEffectTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create InputEventHub and setup hoverEffectActuator_.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    inputEventHub->hoverEffectActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));

    /**
     * @tc.steps: step2. Call OnCollectHoverEffect.
     * @tc.expected: result size is 1, hoverEffectTarget_ is created.
     */
    TouchTestResult result;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    inputEventHub->hoverEffectActuator_->OnCollectHoverEffect(
        COORDINATE_OFFSET, getEventTargetImpl, result);
    EXPECT_EQ(result.size(), 1);
    EXPECT_NE(inputEventHub->hoverEffectActuator_->hoverEffectTarget_, nullptr);

    /**
     * @tc.steps: step3. Call OnCollectHoverEffect again.
     * @tc.expected: result size is 2, reuses existing hoverEffectTarget_.
     */
    inputEventHub->hoverEffectActuator_->OnCollectHoverEffect(
        COORDINATE_OFFSET, getEventTargetImpl, result);
    EXPECT_EQ(result.size(), 2);
}

/**
 * @tc.name: OnCollectMouseEventReuseTarget001
 * @tc.desc: Test OnCollectMouseEvent reuses existing mouseEventTarget_.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, OnCollectMouseEventReuseTarget001, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    inputEventHub->mouseEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));
    OnMouseEventFunc onMouse = [](MouseInfo& info) {};
    inputEventHub->mouseEventActuator_->userCallback_ = AceType::MakeRefPtr<InputEvent>(std::move(onMouse));

    TouchTestResult result;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();

    /**
     * @tc.steps: step1. First call creates mouseEventTarget_.
     */
    inputEventHub->mouseEventActuator_->OnCollectMouseEvent(
        COORDINATE_OFFSET, getEventTargetImpl, result);
    auto firstTarget = inputEventHub->mouseEventActuator_->mouseEventTarget_;
    EXPECT_NE(firstTarget, nullptr);
    EXPECT_EQ(result.size(), 1);

    /**
     * @tc.steps: step2. Second call reuses mouseEventTarget_.
     * @tc.expected: same target pointer, result size 2.
     */
    inputEventHub->mouseEventActuator_->OnCollectMouseEvent(
        COORDINATE_OFFSET, getEventTargetImpl, result);
    EXPECT_EQ(inputEventHub->mouseEventActuator_->mouseEventTarget_, firstTarget);
    EXPECT_EQ(result.size(), 2);
}

/**
 * @tc.name: OnCollectHoverEventReuseTarget001
 * @tc.desc: Test OnCollectHoverEvent reuses existing hoverEventTarget_.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, OnCollectHoverEventReuseTarget001, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    inputEventHub->hoverEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));
    OnHoverFunc onHover = [](bool, HoverInfo) {};
    inputEventHub->hoverEventActuator_->userCallback_ = AceType::MakeRefPtr<InputEvent>(std::move(onHover));

    TouchTestResult result;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();

    /**
     * @tc.steps: step1. First call creates hoverEventTarget_.
     */
    inputEventHub->hoverEventActuator_->OnCollectHoverEvent(
        COORDINATE_OFFSET, getEventTargetImpl, result);
    auto firstTarget = inputEventHub->hoverEventActuator_->hoverEventTarget_;
    EXPECT_NE(firstTarget, nullptr);
    EXPECT_EQ(result.size(), 1);

    /**
     * @tc.steps: step2. Second call reuses hoverEventTarget_.
     */
    inputEventHub->hoverEventActuator_->OnCollectHoverEvent(
        COORDINATE_OFFSET, getEventTargetImpl, result);
    EXPECT_EQ(inputEventHub->hoverEventActuator_->hoverEventTarget_, firstTarget);
    EXPECT_EQ(result.size(), 2);
}

/**
 * @tc.name: OnCollectPenHoverEventReuseTarget001
 * @tc.desc: Test OnCollectPenHoverEvent reuses existing penHoverEventTarget_.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, OnCollectPenHoverEventReuseTarget001, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    inputEventHub->hoverEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));
    OnHoverFunc onHover = [](bool, HoverInfo) {};
    inputEventHub->hoverEventActuator_->userCallback_ = AceType::MakeRefPtr<InputEvent>(std::move(onHover));

    TouchTestResult result;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();

    /**
     * @tc.steps: step1. First call creates penHoverEventTarget_.
     */
    inputEventHub->hoverEventActuator_->OnCollectPenHoverEvent(
        COORDINATE_OFFSET, getEventTargetImpl, result, frameNode);
    auto firstTarget = inputEventHub->hoverEventActuator_->penHoverEventTarget_;
    EXPECT_NE(firstTarget, nullptr);
    EXPECT_EQ(result.size(), 1);

    /**
     * @tc.steps: step2. Second call reuses penHoverEventTarget_.
     */
    inputEventHub->hoverEventActuator_->OnCollectPenHoverEvent(
        COORDINATE_OFFSET, getEventTargetImpl, result, frameNode);
    EXPECT_EQ(inputEventHub->hoverEventActuator_->penHoverEventTarget_, firstTarget);
    EXPECT_EQ(result.size(), 2);
}

/**
 * @tc.name: OnCollectHoverEffect001
 * @tc.desc: Test OnCollectHoverEffect creates hoverEffectTarget and adds to result
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, OnCollectHoverEffect001, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    inputEventHub->hoverEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));

    TouchTestResult result;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    inputEventHub->hoverEventActuator_->OnCollectHoverEffect(COORDINATE_OFFSET, getEventTargetImpl, result);
    EXPECT_EQ(result.size(), 1);
    EXPECT_NE(inputEventHub->hoverEventActuator_->hoverEffectTarget_, nullptr);
}

/**
 * @tc.name: OnCollectHoverEffect002
 * @tc.desc: Test OnCollectHoverEffect reuses existing hoverEffectTarget_
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, OnCollectHoverEffect002, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    inputEventHub->hoverEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));

    TouchTestResult result1;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    inputEventHub->hoverEventActuator_->OnCollectHoverEffect(COORDINATE_OFFSET, getEventTargetImpl, result1);
    EXPECT_EQ(result1.size(), 1);
    auto savedTarget = inputEventHub->hoverEventActuator_->hoverEffectTarget_;

    TouchTestResult result2;
    inputEventHub->hoverEventActuator_->OnCollectHoverEffect(COORDINATE_OFFSET, getEventTargetImpl, result2);
    EXPECT_EQ(result2.size(), 1);
    EXPECT_EQ(inputEventHub->hoverEventActuator_->hoverEffectTarget_, savedTarget);
}

/**
 * @tc.name: OnCollectMouseEventEarlyReturn001
 * @tc.desc: Test OnCollectMouseEvent returns early when all empty
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, OnCollectMouseEventEarlyReturn001, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    inputEventHub->mouseEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));

    TouchTestResult result;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    inputEventHub->mouseEventActuator_->OnCollectMouseEvent(COORDINATE_OFFSET, getEventTargetImpl, result);
    EXPECT_EQ(result.size(), 0);
}

/**
 * @tc.name: OnCollectMouseEventWithInputEvents001
 * @tc.desc: Test OnCollectMouseEvent with inputEvents_ only, triggers inner callback
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, OnCollectMouseEventWithInputEvents001, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    inputEventHub->mouseEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));

    int32_t count = 0;
    OnMouseEventFunc onMouse = [&count](MouseInfo& info) { count++; };
    auto onMouseEvent = AceType::MakeRefPtr<InputEvent>(std::move(onMouse));
    inputEventHub->mouseEventActuator_->inputEvents_.emplace_back(onMouseEvent);

    TouchTestResult result;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    inputEventHub->mouseEventActuator_->OnCollectMouseEvent(COORDINATE_OFFSET, getEventTargetImpl, result);
    EXPECT_EQ(result.size(), 1);

    MouseInfo mouse;
    inputEventHub->mouseEventActuator_->mouseEventTarget_->onMouseCallback_(mouse);
    EXPECT_EQ(count, 1);
}

/**
 * @tc.name: OnCollectHoverEventJSFrameNode001
 * @tc.desc: Test OnCollectHoverEvent with userJSFrameNodeCallback_ triggers callback
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, OnCollectHoverEventJSFrameNode001, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    inputEventHub->hoverEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));

    int32_t jsFrameNodeCount = 0;
    OnHoverFunc onJSFrameNode = [&jsFrameNodeCount](bool, HoverInfo) { jsFrameNodeCount++; };
    auto onJSFrameNodeEvent = AceType::MakeRefPtr<InputEvent>(std::move(onJSFrameNode));
    inputEventHub->hoverEventActuator_->userJSFrameNodeCallback_ = onJSFrameNodeEvent;

    TouchTestResult result;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    inputEventHub->hoverEventActuator_->OnCollectHoverEvent(COORDINATE_OFFSET, getEventTargetImpl, result);
    EXPECT_EQ(result.size(), 1);

    HoverInfo hover;
    inputEventHub->hoverEventActuator_->hoverEventTarget_->onHoverEventCallback_(true, hover);
    EXPECT_EQ(jsFrameNodeCount, 1);
}

/**
 * @tc.name: OnCollectHoverEventForTipsNoTips001
 * @tc.desc: Test OnCollectHoverEventForTips with istips=false, callback not invoked
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, OnCollectHoverEventForTipsNoTips001, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    inputEventHub->hoverEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));

    int32_t callCount = 0;
    auto hoverTask = [&callCount](bool, HoverInfo& info) { callCount++; };
    auto hoverEvent = AceType::MakeRefPtr<InputEvent>(std::move(hoverTask));
    hoverEvent->SetIstips(false);
    inputEventHub->hoverEventActuator_->inputEvents_.clear();
    inputEventHub->hoverEventActuator_->inputEvents_.emplace_back(hoverEvent);

    TouchTestResult result;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    inputEventHub->hoverEventActuator_->OnCollectHoverEventForTips(COORDINATE_OFFSET, getEventTargetImpl, result);
    EXPECT_EQ(result.size(), 1);

    HoverInfo hover;
    inputEventHub->hoverEventActuator_->hoverEventTarget_->onHoverEventCallback_(true, hover);
    EXPECT_EQ(callCount, 0);
}

/**
 * @tc.name: OnCollectAccessibilityHoverEventJSFrameNode001
 * @tc.desc: Test OnCollectAccessibilityHoverEvent with userJSFrameNodeCallback_ prevents early return
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, OnCollectAccessibilityHoverEventJSFrameNode001, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto hoverEventActuator =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));

    OnHoverFunc onJSFrameNode = [](bool, HoverInfo) {};
    auto onJSFrameNodeEvent = AceType::MakeRefPtr<InputEvent>(std::move(onJSFrameNode));
    hoverEventActuator->userJSFrameNodeCallback_ = onJSFrameNodeEvent;

    TouchTestResult result;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    hoverEventActuator->OnCollectAccessibilityHoverEvent(
        COORDINATE_OFFSET, getEventTargetImpl, result, frameNode);
    EXPECT_EQ(result.size(), 1);
}

/**
 * @tc.name: OnCollectAccessibilityHoverEventReuseTarget001
 * @tc.desc: Test OnCollectAccessibilityHoverEvent reuses existing accessibilityHoverEventTarget_
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, OnCollectAccessibilityHoverEventReuseTarget001, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto hoverEventActuator =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));

    OnAccessibilityHoverFunc onAccessibilityHover = [](bool, AccessibilityHoverInfo&) {};
    auto userEvent = AceType::MakeRefPtr<InputEvent>(std::move(onAccessibilityHover));
    hoverEventActuator->userCallback_ = userEvent;

    TouchTestResult result1;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    hoverEventActuator->OnCollectAccessibilityHoverEvent(
        COORDINATE_OFFSET, getEventTargetImpl, result1, frameNode);
    EXPECT_EQ(result1.size(), 1);
    auto savedTarget = hoverEventActuator->accessibilityHoverEventTarget_;
    EXPECT_NE(savedTarget, nullptr);

    TouchTestResult result2;
    hoverEventActuator->OnCollectAccessibilityHoverEvent(
        COORDINATE_OFFSET, getEventTargetImpl, result2, frameNode);
    EXPECT_EQ(result2.size(), 1);
    EXPECT_EQ(hoverEventActuator->accessibilityHoverEventTarget_, savedTarget);
}

/**
 * @tc.name: OnCollectPenHoverMoveEventReuseTarget001
 * @tc.desc: Test OnCollectPenHoverMoveEvent reuses existing penHoverMoveEventTarget_
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, OnCollectPenHoverMoveEventReuseTarget001, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto hoverEventActuator =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));

    OnHoverMoveFunc onHoverMove = [](HoverInfo&) {};
    auto onHoverMoveEvent = AceType::MakeRefPtr<InputEvent>(std::move(onHoverMove));
    hoverEventActuator->userCallback_ = onHoverMoveEvent;

    TouchTestResult result1;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    hoverEventActuator->OnCollectPenHoverMoveEvent(COORDINATE_OFFSET, getEventTargetImpl, result1, frameNode);
    EXPECT_EQ(result1.size(), 1);
    auto savedTarget = hoverEventActuator->penHoverMoveEventTarget_;
    EXPECT_NE(savedTarget, nullptr);

    TouchTestResult result2;
    hoverEventActuator->OnCollectPenHoverMoveEvent(COORDINATE_OFFSET, getEventTargetImpl, result2, frameNode);
    EXPECT_EQ(result2.size(), 1);
    EXPECT_EQ(hoverEventActuator->penHoverMoveEventTarget_, savedTarget);
}

/**
 * @tc.name: OnCollectAxisEventReuseTarget001
 * @tc.desc: Test OnCollectAxisEvent reuses existing axisEventTarget_
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, OnCollectAxisEventReuseTarget001, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    inputEventHub->axisEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));

    OnAxisEventFunc onAxis = [](AxisInfo&) {};
    auto onAxisEvent = AceType::MakeRefPtr<InputEvent>(std::move(onAxis));
    inputEventHub->axisEventActuator_->userCallback_ = onAxisEvent;

    AxisTestResult result1;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    inputEventHub->axisEventActuator_->OnCollectAxisEvent(COORDINATE_OFFSET, getEventTargetImpl, result1);
    EXPECT_EQ(result1.size(), 1);
    auto savedTarget = inputEventHub->axisEventActuator_->axisEventTarget_;
    EXPECT_NE(savedTarget, nullptr);

    AxisTestResult result2;
    inputEventHub->axisEventActuator_->OnCollectAxisEvent(COORDINATE_OFFSET, getEventTargetImpl, result2);
    EXPECT_EQ(result2.size(), 1);
    EXPECT_EQ(inputEventHub->axisEventActuator_->axisEventTarget_, savedTarget);
}

/**
 * @tc.name: OnCollectAccessibilityHoverEventCallback001
 * @tc.desc: Test OnCollectAccessibilityHoverEvent callback invokes userCallback_
 * @tc.type: FUNC
 */
HWTEST_F(InputEventTestNg, OnCollectAccessibilityHoverEventCallback001, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto hoverEventActuator =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));

    int32_t callCount = 0;
    OnAccessibilityHoverFunc onAccessibilityHover = [&callCount](bool, AccessibilityHoverInfo&) {
        callCount++;
    };
    auto userEvent = AceType::MakeRefPtr<InputEvent>(std::move(onAccessibilityHover));
    hoverEventActuator->userCallback_ = userEvent;

    TouchTestResult result;
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    hoverEventActuator->OnCollectAccessibilityHoverEvent(
        COORDINATE_OFFSET, getEventTargetImpl, result, frameNode);
    EXPECT_EQ(result.size(), 1);

    AccessibilityHoverInfo accessibilityHoverInfo;
    hoverEventActuator->accessibilityHoverEventTarget_->onAccessibilityHoverCallback_(true, accessibilityHoverInfo);
    EXPECT_EQ(callCount, 1);
}
} // namespace OHOS::Ace::NG