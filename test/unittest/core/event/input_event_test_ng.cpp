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
} // namespace OHOS::Ace::NG