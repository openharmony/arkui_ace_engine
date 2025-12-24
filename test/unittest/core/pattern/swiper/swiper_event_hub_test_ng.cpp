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
} // namespace OHOS::Ace::NG