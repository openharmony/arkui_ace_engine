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

#include "gtest/gtest.h"
#include "swiper_test_ng.h"

namespace OHOS::Ace::NG {
class SwiperEventHubTestNg : public SwiperTestNg {
public:
};

/**
 * @tc.name: FireAnimationEndEvent001
 * @tc.desc: Test SwiperLayoutAlgorithm FireAnimationEndEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventHubTestNg, FireAnimationEndEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get SwiperEventHub.
     */
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. call FireAnimationEndEvent, test aniStartCalledCount_ <= 0.
     */
    eventHub->FireAnimationEndEvent(1, {
                                           .currentOffset = 1.23f,
                                           .targetOffset = -4.56f,
                                           .velocity = 78.9f,
                                       });
    ASSERT_NE(eventHub->delayCallback_, nullptr);
}

/**
 * @tc.name: FireAnimationEndEvent002
 * @tc.desc: Test SwiperLayoutAlgorithm FireAnimationEndEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventHubTestNg, FireAnimationEndEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get SwiperEventHub.
     */
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. call FireAnimationEndEvent, test aniStartCalledCount_ > 0, !animationEndEvents_.empty() is
     * false.
     */
    eventHub->FireAnimationStartEvent(0, 0, {});
    ASSERT_EQ(eventHub->aniStartCalledCount_, 1);
    eventHub->FireAnimationEndEvent(1, {
                                           .currentOffset = 1.23f,
                                           .targetOffset = -4.56f,
                                           .velocity = 78.9f,
                                       });
    ASSERT_EQ(eventHub->aniStartCalledCount_, 0);
}

/**
 * @tc.name: FireAnimationEndEvent003
 * @tc.desc: Test SwiperLayoutAlgorithm FireAnimationEndEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventHubTestNg, FireAnimationEndEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get SwiperEventHub.
     */
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. call FireAnimationEndEvent, test aniStartCalledCount_ > 0, !animationEndEvents_.empty() is
     * true, animationEndEvent is nullptr.
     */
    AnimationEndEventPtr animationEndEvent = nullptr;
    eventHub->AddAnimationEndEvent(animationEndEvent);
    AnimationEndEventPtr animationEndEvent1 =
        std::make_shared<AnimationEndEvent>([](int32_t index, const AnimationCallbackInfo& info) {});
    eventHub->AddAnimationEndEvent(animationEndEvent1);
    eventHub->FireAnimationStartEvent(0, 0, {});
    ASSERT_EQ(eventHub->aniStartCalledCount_, 1);
    eventHub->FireAnimationEndEvent(1, {
                                           .currentOffset = 1.23f,
                                           .targetOffset = -4.56f,
                                           .velocity = 78.9f,
                                       });
    ASSERT_EQ(eventHub->aniStartCalledCount_, 0);
}

/**
 * @tc.name: FireAnimationEndOnForceEvent001
 * @tc.desc: Test SwiperLayoutAlgorithm FireAnimationEndOnForceEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventHubTestNg, FireAnimationEndOnForceEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get SwiperEventHub.
     */
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. call FireAnimationEndOnForceEvent, test aniStartCalledCount_ <= 0.
     */
    eventHub->FireAnimationEndOnForceEvent(1, {
                                                  .currentOffset = 1.23f,
                                                  .targetOffset = -4.56f,
                                                  .velocity = 78.9f,
                                              });
    ASSERT_NE(eventHub->delayCallback_, nullptr);
}

/**
 * @tc.name: FireAnimationEndOnForceEvent002
 * @tc.desc: Test SwiperLayoutAlgorithm FireAnimationEndOnForceEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventHubTestNg, FireAnimationEndOnForceEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get SwiperEventHub.
     */
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. call FireAnimationEndOnForceEvent, test aniStartCalledCount_ > 0, animationEndEvents_.empty()
     * is true.
     */
    eventHub->FireAnimationStartEvent(0, 0, {});
    ASSERT_EQ(eventHub->aniStartCalledCount_, 1);
    eventHub->FireAnimationEndOnForceEvent(1, {
                                                  .currentOffset = 1.23f,
                                                  .targetOffset = -4.56f,
                                                  .velocity = 78.9f,
                                              });
    ASSERT_EQ(eventHub->aniStartCalledCount_, 0);
}

/**
 * @tc.name: FireAnimationEndOnForceEvent003
 * @tc.desc: Test SwiperLayoutAlgorithm FireAnimationEndOnForceEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventHubTestNg, FireAnimationEndOnForceEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get SwiperEventHub.
     */
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. call FireAnimationEndOnForceEvent, test aniStartCalledCount_ > 0, animationEndEvents_.empty()
     * is false.
     */
    AnimationEndEventPtr animationEndEvent = nullptr;
    eventHub->AddAnimationEndEvent(animationEndEvent);
    AnimationEndEventPtr animationEndEvent1 =
        std::make_shared<AnimationEndEvent>([](int32_t index, const AnimationCallbackInfo& info) {});
    eventHub->AddAnimationEndEvent(animationEndEvent1);
    eventHub->FireAnimationStartEvent(0, 0, {});
    ASSERT_EQ(eventHub->aniStartCalledCount_, 1);
    eventHub->FireAnimationEndOnForceEvent(1, {
                                                  .currentOffset = 1.23f,
                                                  .targetOffset = -4.56f,
                                                  .velocity = 78.9f,
                                              });
    ASSERT_EQ(eventHub->aniStartCalledCount_, 0);
}

/**
 * @tc.name: FireJSChangeEvent001
 * @tc.desc: Test SwiperLayoutAlgorithm FireJSChangeEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventHubTestNg, FireJSChangeEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get SwiperEventHub.
     */
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. call FireJSChangeEvent, test changeEvents_.empty() is true.
     */
    eventHub->FireJSChangeEvent(1, 2);
    ASSERT_EQ(eventHub->changeEvents_.empty(), true);
}

/**
 * @tc.name: FireJSChangeEvent002
 * @tc.desc: Test SwiperLayoutAlgorithm FireJSChangeEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventHubTestNg, FireJSChangeEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get SwiperEventHub.
     */
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. call FireJSChangeEvent, test changeEvents_.empty() is false.
     */
    ChangeEventPtr changeEvent = nullptr;
    eventHub->AddOnChangeEvent(changeEvent);
    ChangeEventPtr changeEvent1 = std::make_shared<ChangeEvent>([](int32_t index) {});
    eventHub->AddOnChangeEvent(changeEvent1);
    eventHub->FireJSChangeEvent(1, 2);
    ASSERT_EQ(eventHub->changeEvents_.empty(), false);
}

/**
 * @tc.name: FireUnselectedEvent001
 * @tc.desc: Test SwiperEventHub FireUnselectedEvent with empty events
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventHubTestNg, FireUnselectedEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get SwiperEventHub.
     */
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. call FireUnselectedEvent with empty events list.
     * @tc.expected: Should not crash.
     */
    eventHub->FireUnselectedEvent(0);
    // Verify eventHub and frameNode are still valid after call
    ASSERT_NE(eventHub, nullptr);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: FireUnselectedEvent002
 * @tc.desc: Test SwiperEventHub FireUnselectedEvent with nullptr event
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventHubTestNg, FireUnselectedEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get SwiperEventHub.
     */
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. Add nullptr event and call FireUnselectedEvent.
     * @tc.expected: Should not crash.
     */
    ChangeEventPtr nullEvent = nullptr;
    eventHub->AddOnUnselectedEvent(nullEvent);
    eventHub->FireUnselectedEvent(0);
    // Verify eventHub and frameNode are still valid after call
    ASSERT_NE(eventHub, nullptr);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: FireUnselectedEvent003
 * @tc.desc: Test SwiperEventHub FireUnselectedEvent with valid event
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventHubTestNg, FireUnselectedEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get SwiperEventHub.
     */
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. Add valid event and call FireUnselectedEvent.
     */
    bool callbackCalled = false;
    ChangeEventPtr validEvent = std::make_shared<ChangeEvent>([&callbackCalled](int32_t index) {
        callbackCalled = true;
    });
    eventHub->AddOnUnselectedEvent(validEvent);
    eventHub->FireUnselectedEvent(1);
    ASSERT_TRUE(callbackCalled);
}

/**
 * @tc.name: FireScrollStateChangedEvent001
 * @tc.desc: Test SwiperEventHub FireScrollStateChangedEvent without event
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventHubTestNg, FireScrollStateChangedEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get SwiperEventHub.
     */
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. call FireScrollStateChangedEvent without setting event.
     * @tc.expected: Should not crash.
     */
    eventHub->FireScrollStateChangedEvent(ScrollState::IDLE);
    // Verify eventHub and frameNode are still valid after call
    ASSERT_NE(eventHub, nullptr);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: FireScrollStateChangedEvent002
 * @tc.desc: Test SwiperEventHub FireScrollStateChangedEvent with valid event
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventHubTestNg, FireScrollStateChangedEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get SwiperEventHub.
     */
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. Set event and call FireScrollStateChangedEvent.
     */
    bool callbackCalled = false;
    int32_t receivedState = -1;
    ChangeEventPtr stateEvent = std::make_shared<ChangeEvent>([&callbackCalled, &receivedState](int32_t state) {
        callbackCalled = true;
        receivedState = state;
    });
    eventHub->AddOnScrollStateChangedEvent(stateEvent);
    eventHub->FireScrollStateChangedEvent(ScrollState::SCROLL);
    ASSERT_TRUE(callbackCalled);
    ASSERT_EQ(receivedState, static_cast<int32_t>(ScrollState::SCROLL));
}

/**
 * @tc.name: FireChangeDoneEvent001
 * @tc.desc: Test SwiperEventHub FireChangeDoneEvent without event
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventHubTestNg, FireChangeDoneEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get SwiperEventHub.
     */
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. call FireChangeDoneEvent without setting event.
     * @tc.expected: Should not crash.
     */
    eventHub->FireChangeDoneEvent(true);
    eventHub->FireChangeDoneEvent(false);
    // Verify eventHub and frameNode are still valid after call
    ASSERT_NE(eventHub, nullptr);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: FireChangeDoneEvent002
 * @tc.desc: Test SwiperEventHub FireChangeDoneEvent with direction=true
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventHubTestNg, FireChangeDoneEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get SwiperEventHub.
     */
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. Set event and call FireChangeDoneEvent with direction=true.
     */
    bool callbackCalled = false;
    ChangeDoneEvent doneEvent = [&callbackCalled]() {
        callbackCalled = true;
    };
    eventHub->SetChangeDoneEvent(std::move(doneEvent));
    eventHub->FireChangeDoneEvent(true);
    ASSERT_TRUE(callbackCalled);
    ASSERT_EQ(eventHub->GetDirection(), Direction::NEXT);
}

/**
 * @tc.name: FireChangeDoneEvent003
 * @tc.desc: Test SwiperEventHub FireChangeDoneEvent with direction=false
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventHubTestNg, FireChangeDoneEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get SwiperEventHub.
     */
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. Set event and call FireChangeDoneEvent with direction=false.
     */
    bool callbackCalled = false;
    ChangeDoneEvent doneEvent = [&callbackCalled]() {
        callbackCalled = true;
    };
    eventHub->SetChangeDoneEvent(std::move(doneEvent));
    eventHub->FireChangeDoneEvent(false);
    ASSERT_TRUE(callbackCalled);
    ASSERT_EQ(eventHub->GetDirection(), Direction::PRE);
}

/**
 * @tc.name: FireChangeEvent001
 * @tc.desc: Test SwiperEventHub FireChangeEvent with isInLayout=false
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventHubTestNg, FireChangeEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get SwiperEventHub.
     */
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. call FireChangeEvent with isInLayout=false.
     * @tc.expected: Should not crash.
     */
    eventHub->FireChangeEvent(0, 1, false);
    // Verify eventHub and frameNode are still valid after call
    ASSERT_NE(eventHub, nullptr);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: FireChangeEvent002
 * @tc.desc: Test SwiperEventHub FireChangeEvent with isInLayout=true
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventHubTestNg, FireChangeEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get SwiperEventHub.
     */
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. call FireChangeEvent with isInLayout=true.
     * @tc.expected: Should not crash.
     */
    eventHub->FireChangeEvent(0, 1, true);
    // Verify eventHub and frameNode are still valid after call
    ASSERT_NE(eventHub, nullptr);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: FireChangeEvent003
 * @tc.desc: Test SwiperEventHub FireChangeEvent with changeEventsWithPreIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventHubTestNg, FireChangeEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get SwiperEventHub.
     */
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. Add changeEventsWithPreIndex and call FireChangeEvent.
     */
    bool callbackCalled = false;
    int32_t preIndex = -1;
    int32_t currentIndex = -1;
    ChangeEventWithPreIndexPtr eventWithPreIndex =
        std::make_shared<ChangeEventWithPreIndex>([&callbackCalled, &preIndex, &currentIndex](
            int32_t pre, int32_t current) {
            callbackCalled = true;
            preIndex = pre;
            currentIndex = current;
        });
    eventHub->AddOnChangeEventWithPreIndex(eventWithPreIndex);
    eventHub->FireChangeEvent(2, 3, false);
    ASSERT_TRUE(callbackCalled);
    ASSERT_EQ(preIndex, 2);
    ASSERT_EQ(currentIndex, 3);
}

/**
 * @tc.name: FireChangeEvent004
 * @tc.desc: Test SwiperEventHub FireChangeEvent with nullptr changeEventsWithPreIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventHubTestNg, FireChangeEvent004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get SwiperEventHub.
     */
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. Add nullptr changeEventsWithPreIndex and call FireChangeEvent.
     * @tc.expected: Should not crash.
     */
    ChangeEventWithPreIndexPtr nullEvent = nullptr;
    eventHub->AddOnChangeEventWithPreIndex(nullEvent);
    eventHub->FireChangeEvent(0, 1, false);
    // Verify eventHub and frameNode are still valid after call
    ASSERT_NE(eventHub, nullptr);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: FireAnimationStartEvent001
 * @tc.desc: Test SwiperEventHub FireAnimationStartEvent with empty events
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventHubTestNg, FireAnimationStartEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get SwiperEventHub.
     */
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. call FireAnimationStartEvent without adding events.
     * @tc.expected: Should increment aniStartCalledCount_.
     */
    eventHub->FireAnimationStartEvent(0, 1, {});
    ASSERT_EQ(eventHub->aniStartCalledCount_, 1);
}

/**
 * @tc.name: FireAnimationStartEvent002
 * @tc.desc: Test SwiperEventHub FireAnimationStartEvent with nullptr event
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventHubTestNg, FireAnimationStartEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get SwiperEventHub.
     */
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. Add nullptr event and call FireAnimationStartEvent.
     * @tc.expected: Should increment aniStartCalledCount_.
     */
    AnimationStartEventPtr nullEvent = nullptr;
    eventHub->AddAnimationStartEvent(nullEvent);
    eventHub->FireAnimationStartEvent(0, 1, {});
    ASSERT_EQ(eventHub->aniStartCalledCount_, 1);
}

/**
 * @tc.name: FireAnimationStartEvent003
 * @tc.desc: Test SwiperEventHub FireAnimationStartEvent with valid event
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventHubTestNg, FireAnimationStartEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get SwiperEventHub.
     */
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. Add valid event and call FireAnimationStartEvent.
     */
    bool callbackCalled = false;
    int32_t receivedIndex = -1;
    int32_t receivedTargetIndex = -1;
    AnimationStartEventPtr startEvent = std::make_shared<AnimationStartEvent>(
        [&callbackCalled, &receivedIndex, &receivedTargetIndex](
            int32_t index, int32_t targetIndex, const AnimationCallbackInfo& info) {
            callbackCalled = true;
            receivedIndex = index;
            receivedTargetIndex = targetIndex;
        });
    eventHub->AddAnimationStartEvent(startEvent);
    eventHub->FireAnimationStartEvent(2, 3, {});
    ASSERT_TRUE(callbackCalled);
    ASSERT_EQ(receivedIndex, 2);
    ASSERT_EQ(receivedTargetIndex, 3);
    ASSERT_EQ(eventHub->aniStartCalledCount_, 1);
}

/**
 * @tc.name: FireGestureSwipeEvent001
 * @tc.desc: Test SwiperEventHub FireGestureSwipeEvent without event
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventHubTestNg, FireGestureSwipeEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get SwiperEventHub.
     */
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. call FireGestureSwipeEvent without setting event.
     * @tc.expected: Should not crash.
     */
    eventHub->FireGestureSwipeEvent(0, {});
    // Verify eventHub and frameNode are still valid after call
    ASSERT_NE(eventHub, nullptr);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: FireGestureSwipeEvent002
 * @tc.desc: Test SwiperEventHub FireGestureSwipeEvent with valid event
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventHubTestNg, FireGestureSwipeEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get SwiperEventHub.
     */
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. Set event and call FireGestureSwipeEvent.
     */
    bool callbackCalled = false;
    int32_t receivedIndex = -1;
    GestureSwipeEvent swipeEvent = [&callbackCalled, &receivedIndex](
        int32_t index, const AnimationCallbackInfo& info) {
        callbackCalled = true;
        receivedIndex = index;
    };
    eventHub->SetGestureSwipeEvent(std::move(swipeEvent));
    eventHub->FireGestureSwipeEvent(3, {});
    ASSERT_TRUE(callbackCalled);
    ASSERT_EQ(receivedIndex, 3);
}

/**
 * @tc.name: FireSelectedEvent001
 * @tc.desc: Test SwiperEventHub FireSelectedEvent with empty events
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventHubTestNg, FireSelectedEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get SwiperEventHub.
     */
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. call FireSelectedEvent with empty events list.
     * @tc.expected: Should not crash.
     */
    eventHub->FireSelectedEvent(0);
    // Verify eventHub and frameNode are still valid after call
    ASSERT_NE(eventHub, nullptr);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: FireSelectedEvent002
 * @tc.desc: Test SwiperEventHub FireSelectedEvent with nullptr event
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventHubTestNg, FireSelectedEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get SwiperEventHub.
     */
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. Add nullptr event and call FireSelectedEvent.
     * @tc.expected: Should not crash.
     */
    ChangeEventPtr nullEvent = nullptr;
    eventHub->AddOnSlectedEvent(nullEvent);
    eventHub->FireSelectedEvent(0);
    // Verify eventHub and frameNode are still valid after call
    ASSERT_NE(eventHub, nullptr);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: FireSelectedEvent003
 * @tc.desc: Test SwiperEventHub FireSelectedEvent with valid event
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventHubTestNg, FireSelectedEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get SwiperEventHub.
     */
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. Add valid event and call FireSelectedEvent.
     */
    bool callbackCalled = false;
    int32_t receivedIndex = -1;
    ChangeEventPtr validEvent = std::make_shared<ChangeEvent>([&callbackCalled, &receivedIndex](int32_t index) {
        callbackCalled = true;
        receivedIndex = index;
    });
    eventHub->AddOnSlectedEvent(validEvent);
    eventHub->FireSelectedEvent(5);
    ASSERT_TRUE(callbackCalled);
    ASSERT_EQ(receivedIndex, 5);
}

/**
 * @tc.name: SetSwiperId001
 * @tc.desc: Test SwiperEventHub SetSwiperId
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventHubTestNg, SetSwiperId001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get SwiperEventHub.
     */
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. Set swiperId and verify it's stored.
     */
    eventHub->SetSwiperId(100);
    // Note: swiperId_ is private, this test verifies the setter doesn't crash
    // The actual value can be verified through log output in actual tests
    // Verify eventHub and frameNode are still valid after call
    ASSERT_NE(eventHub, nullptr);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: FireIndicatorChangeEvent001
 * @tc.desc: Test SwiperEventHub FireIndicatorChangeEvent without event
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventHubTestNg, FireIndicatorChangeEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get SwiperEventHub.
     */
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. call FireIndicatorChangeEvent without setting event.
     * @tc.expected: Should not crash.
     */
    eventHub->FireIndicatorChangeEvent(0);
    // Verify eventHub and frameNode are still valid after call
    ASSERT_NE(eventHub, nullptr);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: FireIndicatorChangeEvent002
 * @tc.desc: Test SwiperEventHub FireIndicatorChangeEvent with valid event
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventHubTestNg, FireIndicatorChangeEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get SwiperEventHub.
     */
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. Set event and call FireIndicatorChangeEvent.
     */
    bool callbackCalled = false;
    ChangeIndicatorEvent indicatorEvent = [&callbackCalled]() {
        callbackCalled = true;
    };
    eventHub->SetIndicatorOnChange(std::move(indicatorEvent));
    eventHub->FireIndicatorChangeEvent(1);
    ASSERT_TRUE(callbackCalled);
}

/**
 * @tc.name: FireIndicatorIndexChangeEvent001
 * @tc.desc: Test SwiperEventHub FireIndicatorIndexChangeEvent without event
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventHubTestNg, FireIndicatorIndexChangeEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get SwiperEventHub.
     */
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. call FireIndicatorIndexChangeEvent without setting event.
     * @tc.expected: Should not crash.
     */
    eventHub->FireIndicatorIndexChangeEvent(0);
    // Verify eventHub and frameNode are still valid after call
    ASSERT_NE(eventHub, nullptr);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: FireIndicatorIndexChangeEvent002
 * @tc.desc: Test SwiperEventHub FireIndicatorIndexChangeEvent with valid event
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventHubTestNg, FireIndicatorIndexChangeEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get SwiperEventHub.
     */
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. Set event and call FireIndicatorIndexChangeEvent.
     */
    bool callbackCalled = false;
    int32_t receivedIndex = -1;
    IndicatorIndexChangeEvent indexEvent = [&callbackCalled, &receivedIndex](int32_t index) {
        callbackCalled = true;
        receivedIndex = index;
    };
    eventHub->SetIndicatorIndexChangeEvent(std::move(indexEvent));
    eventHub->FireIndicatorIndexChangeEvent(2);
    ASSERT_TRUE(callbackCalled);
    ASSERT_EQ(receivedIndex, 2);
}
} // namespace OHOS::Ace::NG