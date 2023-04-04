/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#define private public
#define protected public
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/animation/animator.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
} // namespace

class SwiperPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: SwiperEvent001
 * @tc.desc: HandleTouchDown
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperEvent001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode = FrameNode::GetOrCreateFrameNode(
        "Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    std::list<TouchLocationInfo> infoList;
    infoList.emplace_back(touchLocationInfo);
    TouchEventInfo touchEventInfo("down");
    touchEventInfo.touches_ = infoList;
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    pattern->HandleTouchEvent(touchEventInfo);
    EXPECT_FALSE(pattern->indicatorDoingAnimation_);
    const char* name = "HandleTouchDown";
    pattern->controller_ = AceType::MakeRefPtr<Animator>(name);
    pattern->controller_->status_ = Animator::Status::RUNNING;
    pattern->springController_ = AceType::MakeRefPtr<Animator>(name);
    pattern->springController_->status_ = Animator::Status::RUNNING;
    pattern->HandleTouchEvent(touchEventInfo);
    EXPECT_FALSE(pattern->indicatorDoingAnimation_);

    touchLocationInfo.SetTouchType(TouchType::UP);
    pattern->HandleTouchEvent(touchEventInfo);
    pattern->controller_ = nullptr;
    pattern->springController_ = nullptr;
    touchLocationInfo.SetTouchType(TouchType::CANCEL);
    pattern->HandleTouchEvent(touchEventInfo);
    EXPECT_FALSE(pattern->indicatorDoingAnimation_);
}

/**
 * @tc.name: SwiperEvent002
 * @tc.desc: HandleTouchDown
 * @tc.type: FUNC
 */
HWTEST_F(SwiperPatternTestNg, SwiperEvent002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode = FrameNode::GetOrCreateFrameNode(
        "Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    pattern->InitPanEvent(gestureEventHub);
    EXPECT_EQ(pattern->direction_, Axis::HORIZONTAL);
}
} // namespace OHOS::Ace::NG
