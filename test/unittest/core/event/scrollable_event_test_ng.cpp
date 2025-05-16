/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include <clocale>
#include <cmath>
#include <cstdint>
#include <unistd.h>

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#define private public
#define protected public
#include "core/components_ng/pattern/scroll/scroll_edge_effect.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/scrollable_event.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr Axis SCROLLABLE_EVENT_AXIS = Axis::VERTICAL;
constexpr EdgeEffect SCROLLABLE_EVENT_EDGE_EFFECT = EdgeEffect::FADE;
constexpr uint32_t SCROLL_TEST_RESULT_SIZE_1 = 1;
constexpr uint32_t SCROLL_TEST_RESULT_SIZE = 0;
constexpr uint32_t SCROLL_EFFECTS_SIZE = 0;
constexpr uint32_t SCROLL_EFFECTS_SIZE_1 = 1;
const TouchRestrict SCROLL_RESTRICT = { TouchRestrict::LONG_PRESS };
constexpr uint32_t SCROLLABLE_EVENT_SIZE = 0;
constexpr uint32_t SCROLLABLE_EVENT_SIZE_1 = 1;
constexpr float WIDTH = 400.0f;
constexpr float HEIGHT = 400.0f;
const OffsetF COORDINATE_OFFSET(WIDTH, HEIGHT);
constexpr bool SCROLLABLE_EVENT_DISENABLED = false;
const PanDirection SCROLLABLE_EVENT_DIRECTION = { PanDirection::LEFT };
constexpr int32_t FINGERS_NUMBER = 2;
constexpr float DISTANCE = 10.5f;
const PointF LOCAL_POINT { 15.0f, 15.0f };
} // namespace

class ScrollableEventTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};

void ScrollableEventTestNg::SetUpTestSuite()
{
    GTEST_LOG_(INFO) << "ScrollableEventTestNg SetUpTestCase";
}

void ScrollableEventTestNg::TearDownTestSuite()
{
    GTEST_LOG_(INFO) << "ScrollableEventTestNg TearDownTestCase";
}

void ScrollableEventTestNg::SetUp()
{
    MockPipelineContext::SetUp();
}

void ScrollableEventTestNg::TearDown()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: ScrollableEventAddScrollEdgeEffectTest001
 * @tc.desc: Create ScrollableEvent and Add ScrollEdgeEffect.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableEventTestNg, ScrollableEventCreateTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ScrollableActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto scrollableActuator =
        AceType::MakeRefPtr<ScrollableActuator>((AceType::WeakClaim(AceType::RawPtr(gestureEventHub))));
    EXPECT_NE(scrollableActuator, nullptr);

    /**
     * @tc.steps: step2. Add ScrollEdgeEffect when ScrollEdgeEffect is nullptr.
     * @tc.expected: AddScrollEdgeEffect function will return directly, and scrollEffects_ size is 0.
     */
    RefPtr<ScrollEdgeEffect> edgeEffect;
    scrollableActuator->AddScrollEdgeEffect(SCROLLABLE_EVENT_AXIS, edgeEffect);
    EXPECT_EQ(scrollableActuator->scrollEffects_.size(), SCROLL_EFFECTS_SIZE);

    /**
     * @tc.steps: step3. Create ScrollEdgeEffect.
     * @tc.expected: scrollEdgeEffect is not nullptr.
     */
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(SCROLLABLE_EVENT_EDGE_EFFECT);
    EXPECT_NE(scrollEdgeEffect, nullptr);

    /**
     * @tc.steps: step4. Add ScrollEdgeEffect when ScrollEdgeEffect is not nullptr.
     * @tc.expected: Add ScrollEdgeEffect to scrollEffects_ which size will increased by one
     */
    auto scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(SCROLLABLE_EVENT_AXIS);
    scrollableActuator->AddScrollableEvent(scrollableEvent);
    scrollableActuator->AddScrollEdgeEffect(SCROLLABLE_EVENT_AXIS, scrollEdgeEffect);
    EXPECT_EQ(scrollableActuator->scrollEffects_.size(), SCROLL_EFFECTS_SIZE_1);
}

/**
 * @tc.name: ScrollableEventRemoveScrollEdgeEffectTest002
 * @tc.desc: Create ScrollableEvent and remove ScrollEdgeEffect.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableEventTestNg, ScrollableEventRemoveScrollEdgeEffectTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ScrollableActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto scrollableActuator =
        AceType::MakeRefPtr<ScrollableActuator>((AceType::WeakClaim(AceType::RawPtr(gestureEventHub))));
    EXPECT_NE(scrollableActuator, nullptr);

    /**
     * @tc.steps: step2. Remove ScrollEdgeEffect when ScrollEdgeEffect is nullptr.
     * @tc.expected: RemoveScrollEdgeEffect function will return false directly.
     */
    EXPECT_FALSE(scrollableActuator->RemoveScrollEdgeEffect(nullptr));

    /**
     * @tc.steps: step3. Create ScrollEdgeEffect.
     * @tc.expected: scrollEdgeEffect is not nullptr.
     */
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(SCROLLABLE_EVENT_EDGE_EFFECT);
    EXPECT_NE(scrollEdgeEffect, nullptr);

    /**
     * @tc.steps: step4. Add ScrollEdgeEffect.
     * @tc.expected: Add ScrollEdgeEffect to scrollEffects_ which size will not be empty.
     */
    auto scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(SCROLLABLE_EVENT_AXIS);
    scrollableActuator->AddScrollableEvent(scrollableEvent);
    scrollableActuator->AddScrollEdgeEffect(SCROLLABLE_EVENT_AXIS, scrollEdgeEffect);
    EXPECT_EQ(scrollableActuator->scrollEffects_.size(), SCROLL_EFFECTS_SIZE_1);

    /**
     * @tc.steps: step5. Remove ScrollEdgeEffect when ScrollEdgeEffect is not nullptr and can be found in
     * scrollEffects_.
     * @tc.expected: RemoveScrollEdgeEffect function will remove effect in scrollEffects_ and return true.
     */
    EXPECT_TRUE(scrollableActuator->RemoveScrollEdgeEffect(scrollEdgeEffect));
    EXPECT_EQ(scrollableActuator->scrollEffects_.size(), SCROLL_EFFECTS_SIZE);
}

/**
 * @tc.name: ScrollableEventOnCollectTouchTargetTest003
 * @tc.desc: Create ScrollableEvent and invoke OnCollectTouchTarget.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableEventTestNg, ScrollableEventOnCollectTouchTargetTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ScrollableActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto scrollableActuator =
        AceType::MakeRefPtr<ScrollableActuator>((AceType::WeakClaim(AceType::RawPtr(gestureEventHub))));
    EXPECT_NE(scrollableActuator, nullptr);

    /**
     * @tc.steps: step2. CollectTouchTarget when initialized_ is false.
     * @tc.expected: Invoke InitializeScrollable. when scrollableEvents_ is empty return directly.
     */
    TouchTestResult result;
    ResponseLinkResult responseLinkResult;
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    scrollableActuator->CollectTouchTarget(COORDINATE_OFFSET, SCROLL_RESTRICT, eventHub->CreateGetEventTargetImpl(),
        result, LOCAL_POINT, frameNode, nullptr, responseLinkResult);
    EXPECT_EQ(result.size(), SCROLL_TEST_RESULT_SIZE);
    EXPECT_EQ(scrollableActuator->scrollableEvents_.size(), SCROLLABLE_EVENT_SIZE);

    /**
     * @tc.steps: step3. Add ScrollableEvent.
     * @tc.expected: scrollableEvent will be added in scrollableEvents_.
     */
    auto scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(SCROLLABLE_EVENT_AXIS);
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    auto panRecognizerNG = AceType::MakeRefPtr<PanRecognizer>(FINGERS_NUMBER, SCROLLABLE_EVENT_DIRECTION, DISTANCE);
    scrollable->panRecognizerNG_ = panRecognizerNG;
    scrollableEvent->SetScrollable(scrollable);
    scrollableActuator->AddScrollableEvent(scrollableEvent);
    EXPECT_EQ(scrollableActuator->scrollableEvents_.size(), SCROLLABLE_EVENT_SIZE_1);

    /**
     * @tc.steps: step4. CollectTouchTarget when initialized_ is false and scrollableEvents_ is not empty.
     * @tc.expected: gestureEventHub cannot GetFrameNode, InitializeScrollable fuction will return directly.
     */
    scrollableActuator->CollectTouchTarget(COORDINATE_OFFSET, SCROLL_RESTRICT, eventHub->CreateGetEventTargetImpl(),
        result, LOCAL_POINT, frameNode, nullptr, responseLinkResult);
    EXPECT_EQ(result.size(), SCROLL_TEST_RESULT_SIZE_1);
    auto coordinateOffset = scrollableEvent->GetScrollable()->panRecognizerNG_->GetCoordinateOffset();
    EXPECT_EQ(coordinateOffset, Offset(WIDTH, HEIGHT)) <<
        "coordinateOffset: " << coordinateOffset.ToString() <<
        "Offset(WIDTH, HEIGHT)" << Offset(WIDTH, HEIGHT).ToString();

    /**
     * @tc.steps: step5. Add frameNode to gestureEventHub, and Add ScrollEdgeEffect whose axis is same with the
     * scrollableEvent.
     */
    eventHub->AttachHost(frameNode);
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(SCROLLABLE_EVENT_EDGE_EFFECT);
    scrollableActuator->AddScrollEdgeEffect(SCROLLABLE_EVENT_AXIS, scrollEdgeEffect);
    EXPECT_EQ(scrollableActuator->scrollEffects_.size(), SCROLL_EFFECTS_SIZE_1);

    /**
     * @tc.steps: step6. CollectTouchTarget when initialized_ is false, scrollableEvents_ is not empty,
     * gestureEventHub has frameNode and scrollEffects_ shares the same axis with scrollableEvent.
     * @tc.expected: The loop will be continued when scrollableEvent is not enabled.
     */
    scrollableEvent->SetEnabled(SCROLLABLE_EVENT_DISENABLED);
    scrollableActuator->CollectTouchTarget(COORDINATE_OFFSET, SCROLL_RESTRICT, eventHub->CreateGetEventTargetImpl(),
        result, LOCAL_POINT, frameNode, nullptr, responseLinkResult);
    EXPECT_EQ(result.size(), SCROLL_TEST_RESULT_SIZE_1);
}

/**
 * @tc.name: ScrollableEventRemoveScrollEdgeEffectTest003
 * @tc.desc: Create ScrollableEvent and remove ScrollEdgeEffect.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableEventTestNg, ScrollableEventRemoveScrollEdgeEffectTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ScrollableActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto scrollableActuator =
        AceType::MakeRefPtr<ScrollableActuator>((AceType::WeakClaim(AceType::RawPtr(gestureEventHub))));
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(SCROLLABLE_EVENT_EDGE_EFFECT);
    auto scrollEdgeEffect2 = AceType::MakeRefPtr<ScrollEdgeEffect>(SCROLLABLE_EVENT_EDGE_EFFECT);
    auto scrollEdgeEffect3 = AceType::MakeRefPtr<ScrollEdgeEffect>(SCROLLABLE_EVENT_EDGE_EFFECT);
    auto scrollEdgeEffect4 = AceType::MakeRefPtr<ScrollEdgeEffect>(SCROLLABLE_EVENT_EDGE_EFFECT);
    auto scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(SCROLLABLE_EVENT_AXIS);
    scrollableActuator->AddScrollableEvent(scrollableEvent);
    scrollableActuator->AddScrollEdgeEffect(SCROLLABLE_EVENT_AXIS, scrollEdgeEffect);
    scrollableActuator->AddScrollEdgeEffect(SCROLLABLE_EVENT_AXIS, scrollEdgeEffect2);
    scrollableActuator->AddScrollEdgeEffect(SCROLLABLE_EVENT_AXIS, scrollEdgeEffect3);
    scrollableActuator->AddScrollEdgeEffect(SCROLLABLE_EVENT_AXIS, scrollEdgeEffect4);
    EXPECT_FALSE(scrollableActuator->RemoveScrollEdgeEffect(scrollEdgeEffect2));
}

/**
 * @tc.name: ScrollableEventOnCollectTouchTargetTest004
 * @tc.desc: Create ScrollableEvent and test CollectTouchTarget
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableEventTestNg, ScrollableEventOnCollectTouchTargetTest004, TestSize.Level1)
{
    bool results = false;
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto scrollableActuator =
        AceType::MakeRefPtr<ScrollableActuator>((AceType::WeakClaim(AceType::RawPtr(gestureEventHub))));
    auto scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(SCROLLABLE_EVENT_AXIS);
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    auto panRecognizerNG = AceType::MakeRefPtr<PanRecognizer>(FINGERS_NUMBER, SCROLLABLE_EVENT_DIRECTION, DISTANCE);
    scrollable->panRecognizerNG_ = panRecognizerNG;
    scrollableEvent->SetScrollable(scrollable);
    scrollableEvent->SetInBarRegionCallback([](const PointF& point, SourceType source) { return true; });
    scrollableEvent->SetBarCollectTouchTargetCallback(
        [](const OffsetF& coordinateOffset, const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result,
            const RefPtr<FrameNode>& frameNode, const RefPtr<TargetComponent>& targetComponent,
            ResponseLinkResult& responseLinkResult) { return true; });
    scrollableActuator->AddScrollableEvent(scrollableEvent);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    TouchTestResult result;
    ResponseLinkResult responseLinkResult;
    scrollableActuator->CollectTouchTarget(COORDINATE_OFFSET, SCROLL_RESTRICT, eventHub->CreateGetEventTargetImpl(),
        result, LOCAL_POINT, frameNode, nullptr, responseLinkResult);
    EXPECT_FALSE(results);
}

/**
 * @tc.name: ScrollableEventOnCollectTouchTargetTest005
 * @tc.desc: Create ScrollableEvent and test CollectTouchTarget
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableEventTestNg, ScrollableEventOnCollectTouchTargetTest005, TestSize.Level1)
{
    bool results = false;
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto scrollableActuator =
        AceType::MakeRefPtr<ScrollableActuator>((AceType::WeakClaim(AceType::RawPtr(gestureEventHub))));
    auto scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(SCROLLABLE_EVENT_AXIS);
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    auto panRecognizerNG = AceType::MakeRefPtr<PanRecognizer>(FINGERS_NUMBER, SCROLLABLE_EVENT_DIRECTION, DISTANCE);
    scrollable->panRecognizerNG_ = panRecognizerNG;
    scrollableEvent->SetScrollable(scrollable);
    scrollableActuator->clickRecognizer_ = AceType::MakeRefPtr<ClickRecognizer>();
    scrollableEvent->SetInBarRectRegionCallback([](const PointF& point, SourceType source) { return true; });
    scrollableEvent->SetBarCollectClickAndLongPressTargetCallback(
        [](const OffsetF& coordinateOffset, const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result,
            const RefPtr<FrameNode>& frameNode, const RefPtr<TargetComponent>& targetComponent,
            ResponseLinkResult& responseLinkResult) { return true; });
    scrollableActuator->AddScrollableEvent(scrollableEvent);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    TouchTestResult result;
    ResponseLinkResult responseLinkResult;
    scrollableActuator->CollectTouchTarget(COORDINATE_OFFSET, SCROLL_RESTRICT, eventHub->CreateGetEventTargetImpl(),
        result, LOCAL_POINT, frameNode, nullptr, responseLinkResult);
    EXPECT_FALSE(results);
}

/**
 * @tc.name: ScrollableEventOnCollectTouchTargetTest006
 * @tc.desc: Create ScrollableEvent and test CollectTouchTarget
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableEventTestNg, ScrollableEventOnCollectTouchTargetTest006, TestSize.Level1)
{
    bool results = false;
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto scrollableActuator =
        AceType::MakeRefPtr<ScrollableActuator>((AceType::WeakClaim(AceType::RawPtr(gestureEventHub))));
    auto scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(SCROLLABLE_EVENT_AXIS);
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    auto panRecognizerNG = AceType::MakeRefPtr<PanRecognizer>(FINGERS_NUMBER, SCROLLABLE_EVENT_DIRECTION, DISTANCE);
    scrollable->panRecognizerNG_ = panRecognizerNG;
    scrollableEvent->SetScrollable(scrollable);
    scrollableEvent->SetEnabled(false);
    scrollableActuator->clickRecognizer_ = AceType::MakeRefPtr<ClickRecognizer>();
    scrollableEvent->SetClickJudgeCallback([](const PointF& localPoint) { return true; });
    scrollableActuator->AddScrollableEvent(scrollableEvent);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    TouchTestResult result;
    ResponseLinkResult responseLinkResult;
    scrollableActuator->CollectTouchTarget(COORDINATE_OFFSET, SCROLL_RESTRICT, eventHub->CreateGetEventTargetImpl(),
        result, LOCAL_POINT, frameNode, nullptr, responseLinkResult);
    scrollableEvent->SetEnabled(true);
    scrollableActuator->CollectTouchTarget(COORDINATE_OFFSET, SCROLL_RESTRICT, eventHub->CreateGetEventTargetImpl(),
        result, LOCAL_POINT, frameNode, nullptr, responseLinkResult);
    EXPECT_FALSE(results);
}
} // namespace OHOS::Ace::NG
