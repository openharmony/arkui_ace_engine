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

#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/test_ng.h"
#define protected public
#define private public
#include "test/unittest/core/pattern/scrollable/mock_scrollable.h"

#include "frameworks/core/components_ng/pattern/scrollable/scrollable_event_hub.h"
#include "frameworks/core/components_ng/pattern/scrollable/scrollable_model_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class ScrollableEventTest : public TestNG {
public:
    void SetUp() override;
    void TearDown() override;

private:
    RefPtr<FrameNode> node_;
    RefPtr<FullyMockedScrollable> pattern_;
};

constexpr int32_t SCROLL_FROM_UPDATE = 1;
constexpr float SCROLL_SET_PARAMINIT = 0.0f;
constexpr float SCROLL_SET_EXPECTED_FIRST = 10.0f;
constexpr float SCROLL_SET_EXPECTED_SECOND = 30.0f;
constexpr float SCROLL_SET_PARAMOTHER = 0.001f;

void ScrollableEventTest::SetUp()
{
    MockPipelineContext::SetUp();
    ResetElmtId();
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    pattern_ = AceType::MakeRefPtr<FullyMockedScrollable>();
    node_ = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, nodeId, pattern_);
    pattern_->SetEdgeEffect();
    pattern_->AddScrollEvent();
    stack->Push(node_);
}

void ScrollableEventTest::TearDown()
{
    node_.Reset();
    pattern_.Reset();
}

/**
 * @tc.name: OnScrollEnd001
 * @tc.desc: Test HandleOverScroll -> ProcessSpringEffect -> OnScrollEnd
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableEventTest, OnScrollEnd001, TestSize.Level1)
{
    EXPECT_CALL(*pattern_, OnScrollEndCallback).Times(1);
    EXPECT_CALL(*pattern_, OutBoundaryCallback).Times(1).WillOnce(Return(false));

    pattern_->edgeEffect_ = EdgeEffect::SPRING;
    pattern_->SetEdgeEffect(EdgeEffect::SPRING);
    pattern_->SetCanOverScroll(false);

    EXPECT_TRUE(pattern_->HandleOverScroll(5.0f));
}

/**
 * @tc.name: SetOnScroll001
 * @tc.desc: Test ScrollableModelNG::SetOnScroll and FireOnScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableEventTest, SetOnScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Define expected values for offset and state
     */
    float offsetExpected = SCROLL_SET_EXPECTED_FIRST;
    ScrollState stateExpected = ScrollState::SCROLL;

    /**
     * @tc.steps: step2. Initialize test variables for offset and state
     */
    float offsetTest = SCROLL_SET_PARAMINIT;
    ScrollState stateTest = ScrollState::IDLE;
    /**
     * @tc.steps: step3. Define a callback function for onScroll event
     * @tc.expected: The callback function updates offsetTest and stateTest with the provided values
     */
    auto onScrollCallback = [&offsetTest, &stateTest](const Dimension& offset, ScrollState state) {
        offsetTest = offset.Value();
        stateTest = state;
    };

    /**
     * @tc.steps: step4. Set onScroll callback to the ScrollableModelNG
     */
    ScrollableModelNG::SetOnScroll(AceType::RawPtr(node_), std::move(onScrollCallback));
    pattern_->scrollSource_ = SCROLL_FROM_UPDATE;
    auto eventHub = node_->GetOrCreateEventHub<ScrollableEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onScrollEvent = eventHub->GetOnScroll();
    pattern_->FireOnScroll(offsetExpected, onScrollEvent);

    /**
     * @tc.steps: step5. Verify that the callback function was triggered and updated the test variables
     * @tc.expected: offsetTest and stateTest match the expected values
     */
    EXPECT_EQ(offsetTest, offsetExpected);
    EXPECT_EQ(stateTest, stateExpected);
}

/**
 * @tc.name: SetOnWillScroll001
 * @tc.desc: Test ScrollableModelNG::SetOnWillScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableEventTest, SetOnWillScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Define test variables for willScroll event
     */
    Dimension willScrollOffset;
    ScrollState willScrollState = ScrollState::IDLE;
    bool isOnWillScrollCallBack = false;

    /**
     * @tc.steps: step2. Define a callback function for onWillScroll event
     * @tc.expected: The callback function updates willScrollOffset, willScrollState, and isOnWillScrollCallBack
     */
    auto onWillScroll = [&willScrollOffset, &willScrollState, &isOnWillScrollCallBack](
                            Dimension offset, ScrollState state, ScrollSource source) {
        willScrollOffset = offset;
        willScrollState = state;
        isOnWillScrollCallBack = true;
        ScrollFrameResult result;
        result.offset = offset;
        return result;
    };

    /**
     * @tc.steps: step3. Set onWillScroll callback to the ScrollableModelNG
     */
    ScrollableModelNG::SetOnWillScroll(std::move(onWillScroll));
    auto eventHub = node_->GetOrCreateEventHub<ScrollableEventHub>();
    ASSERT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step4. Trigger the onWillScroll event by calling FireOnWillScroll
     * @tc.expected: The onWillScroll callback function is triggered, and the returned offset is normalized
     */
    float offsetExpected = SCROLL_SET_EXPECTED_FIRST;
    auto scrollRes = pattern_->FireOnWillScroll(offsetExpected);
    EXPECT_TRUE(isOnWillScrollCallBack);
    EXPECT_EQ(willScrollOffset.Value(), offsetExpected);
    EXPECT_EQ(willScrollState, pattern_->GetScrollState());
    EXPECT_NEAR(scrollRes, offsetExpected, SCROLL_SET_PARAMOTHER);

    /**
     * @tc.steps: step5. Set onWillScroll callback to the ScrollableModelNG
     */
    ScrollableModelNG::SetOnWillScroll(OnWillScrollEvent());
    auto cleared = eventHub->GetOnWillScroll();
    EXPECT_FALSE(static_cast<bool>(cleared));
    isOnWillScrollCallBack = false;
    ScrollableModelNG::SetOnWillScroll(AceType::RawPtr(node_), std::move(onWillScroll));
    eventHub = node_->GetOrCreateEventHub<ScrollableEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step6. Trigger the onWillScroll event by calling FireOnWillScroll
     * @tc.expected: The onWillScroll callback function is triggered, and the returned offset is normalized
     */
    offsetExpected = SCROLL_SET_EXPECTED_SECOND;
    scrollRes = pattern_->FireOnWillScroll(offsetExpected);
    EXPECT_TRUE(isOnWillScrollCallBack);
    EXPECT_EQ(willScrollOffset.Value(), offsetExpected);
    EXPECT_EQ(willScrollState, pattern_->GetScrollState());
    EXPECT_NEAR(scrollRes, offsetExpected, SCROLL_SET_PARAMOTHER);
}

/**
 * @tc.name: SetOnDidScroll001
 * @tc.desc: Test ScrollableModelNG::SetOnDidScroll and FireOnScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableEventTest, SetOnDidScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize expected and test variables for onDidScroll event
     */
    Dimension didScrollOffset;
    ScrollState didScrollState = ScrollState::IDLE;
    bool isOnDidScrollCallBack = false;

    auto onDidScroll = [&didScrollOffset, &didScrollState, &isOnDidScrollCallBack](
                           Dimension offset, ScrollState state) {
        didScrollOffset = offset;
        didScrollState = state;
        isOnDidScrollCallBack = true;
    };

    /**
     * @tc.steps: step2. Set onDidScroll callback to the ScrollableModelNG
     */
    ScrollableModelNG::SetOnDidScroll(std::move(onDidScroll));
    pattern_->scrollSource_ = SCROLL_FROM_UPDATE;
    auto eventHub = node_->GetOrCreateEventHub<ScrollableEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onDidScrollEvent = eventHub->GetOnDidScroll();

    /**
     * @tc.steps: step3. Trigger the FireOnScroll method with the expected values
     */
    float offsetExpected = SCROLL_SET_EXPECTED_FIRST;
    pattern_->FireOnScroll(offsetExpected, onDidScrollEvent);

    /**
     * @tc.steps: step4. Verify that the callback function was triggered and updated the test variables
     * @tc.expected: didScrollOffset and didScrollState match the expected values
     */
    EXPECT_TRUE(isOnDidScrollCallBack);
    EXPECT_EQ(didScrollOffset.Value(), offsetExpected);
    EXPECT_EQ(didScrollState, pattern_->GetScrollState());

     /**
     * @tc.steps: step5. Set onDidScroll callback to the ScrollableModelNG
     */
    ScrollableModelNG::SetOnDidScroll(OnScrollEvent());
    auto cleared = eventHub->GetOnDidScroll();
    EXPECT_FALSE(static_cast<bool>(cleared));
    ScrollableModelNG::SetOnDidScroll(AceType::RawPtr(node_), std::move(onDidScroll));
    pattern_->scrollSource_ = SCROLL_FROM_UPDATE;
    eventHub = node_->GetOrCreateEventHub<ScrollableEventHub>();
    ASSERT_NE(eventHub, nullptr);
    onDidScrollEvent = eventHub->GetOnDidScroll();
    offsetExpected = SCROLL_SET_EXPECTED_SECOND;
    pattern_->FireOnScroll(offsetExpected, onDidScrollEvent);

    /**
     * @tc.steps: step6. Verify that the callback function was triggered and updated the test variables
     * @tc.expected: didScrollOffset and didScrollState match the expected values
     */
    EXPECT_TRUE(isOnDidScrollCallBack);
    EXPECT_EQ(didScrollOffset.Value(), offsetExpected);
    EXPECT_EQ(didScrollState, pattern_->GetScrollState());
}

/**
 * @tc.name: SetOnScrollStart001
 * @tc.desc: Test ScrollableModelNG::SetOnScrollStart and FireOnScrollStart
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableEventTest, SetOnScrollStart001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize isScrollStartCalled flag and scrollStart callback function
     */
    bool isScrollStartCalled = false;
    auto scrollStart = [&isScrollStartCalled]() {
        isScrollStartCalled = true;
    };

    /**
     * @tc.steps: step2. Set onScrollStart callback to the ScrollableModelNG
     */
    ScrollableModelNG::SetOnScrollStart(AceType::RawPtr(node_), std::move(scrollStart));
    auto eventHub = node_->GetOrCreateEventHub<ScrollableEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onScrollStartEvent = eventHub->GetOnScrollStart();

    /**
     * @tc.steps: step3. Verify that the callback function was triggered
     * @tc.expected: isScrollStartCalled is true
     */
    pattern_->FireOnScrollStart();
    EXPECT_TRUE(isScrollStartCalled);
}

/**
 * @tc.name: SetOnScrollStop001
 * @tc.desc: Test ScrollableModelNG::SetOnScrollStop and trigger OnScrollStop
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableEventTest, SetOnScrollStop001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize variables and callback
     * @tc.expected: Variables initialized successfully.
     */
    bool isScrollStopCalled = false;
    auto scrollStop = [&isScrollStopCalled]() { isScrollStopCalled = true; };

    /**
     * @tc.steps: step2. Set OnScrollStop callback using ScrollableModelNG::SetOnScrollStop
     * @tc.expected: Callback set successfully.
     */
    ScrollableModelNG::SetOnScrollStop(AceType::RawPtr(node_), std::move(scrollStop));
    auto eventHub = node_->GetOrCreateEventHub<ScrollableEventHub>();
    ASSERT_NE(eventHub, nullptr);
    pattern_->scrollStop_ = true;

    /**
     * @tc.steps: step3. Trigger OnScrollStop event and verify callback is called
     * @tc.expected: isScrollStopCalled should be true.
     */
    pattern_->OnScrollStop(eventHub->GetOnScrollStop(), nullptr);
    EXPECT_TRUE(isScrollStopCalled);
}

/**
 * @tc.name: SetOnReachStart001
 * @tc.desc: Test ScrollableModelNG::SetOnReachStart001 and trigger event
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableEventTest, SetOnReachStart001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize variables and callback
     * @tc.expected: Variables initialized successfully.
     */
    bool isScrollOnReachStartCalled = false;
    auto scrollOnReachStart = [&isScrollOnReachStartCalled]() { isScrollOnReachStartCalled = true; };

    /**
     * @tc.steps: step2. Set OnReachStart callback using ScrollableModelNG::SetOnScrollStop
     * @tc.expected: Callback set successfully.
     */
    ScrollableModelNG::SetOnReachStart(AceType::RawPtr(node_), std::move(scrollOnReachStart));
    auto eventHub = node_->GetOrCreateEventHub<ScrollableEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step3. Trigger OnReachStart event and verify callback is called
     * @tc.expected: isScrollStopCalled should be true.
     */
    auto reachStart = eventHub->GetOnReachStart();
    reachStart();
    EXPECT_TRUE(isScrollOnReachStartCalled);
}

/**
 * @tc.name: SetOnScrollFrameBegin001
 * @tc.desc: Test ScrollableModelNG::SetOnScrollFrameBegin and FireOnScrollFrameBegin
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableEventTest, SetOnScrollFrameBegin001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize variables and callback
     * @tc.expected: Variables initialized successfully.
     */
    bool isOnScrollFrameBeginCalled = false;
    Dimension scrollOffset;
    ScrollState scrollState = ScrollState::IDLE;
    auto onScrollFrameBegin = [&isOnScrollFrameBeginCalled](Dimension, ScrollState) {
        isOnScrollFrameBeginCalled = true;
        return ScrollFrameResult();
    };
    
    /**
     * @tc.steps: step2. Set OnScrollFrameBegin callback using ScrollableModelNG::SetOnScrollFrameBegin
     * @tc.expected: Callback set successfully.
     */
    ScrollableModelNG::SetOnScrollFrameBegin(std::move(onScrollFrameBegin));
    auto eventHub = node_->GetOrCreateEventHub<ScrollableEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onScrollFrameBeginEvent = eventHub->GetOnScrollFrameBegin();
    onScrollFrameBeginEvent(scrollOffset, scrollState);
    EXPECT_TRUE(isOnScrollFrameBeginCalled);

    /**
     * @tc.steps: step3. Clear and Reset OnScrollFrameBegin callback using ScrollableModelNG::SetOnScrollFrameBegin
     * @tc.expected: Callback set successfully.
     */
    ScrollableModelNG::SetOnScrollFrameBegin(OnScrollFrameBeginEvent());
    auto cleared = eventHub->GetOnDidScroll();
    EXPECT_FALSE(static_cast<bool>(cleared));
    isOnScrollFrameBeginCalled = false;
    ScrollableModelNG::SetOnScrollFrameBegin(AceType::RawPtr(node_), std::move(onScrollFrameBegin));
    onScrollFrameBeginEvent = eventHub->GetOnScrollFrameBegin();
    onScrollFrameBeginEvent(scrollOffset, scrollState);
    EXPECT_TRUE(isOnScrollFrameBeginCalled);
}

/**
 * @tc.name: SetOnReachEnd001
 * @tc.desc: Test ScrollableModelNG::SetOnReachEnd and FireOnReachEnd
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableEventTest, SetOnReachEnd001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize variables and callback
     * @tc.expected: Variables initialized successfully.
     */
    bool isCalled = false;
    auto onReachEnd = [&isCalled]() {
        isCalled = true;
    };
    
    /**
     * @tc.steps: step2. Set SetOnReachEnd callback using ScrollableModelNG::SetOnReachEnd
     * @tc.expected: Callback set successfully.
     */
    ScrollableModelNG::SetOnReachEnd(AceType::RawPtr(node_), std::move(onReachEnd));
    auto eventHub = node_->GetOrCreateEventHub<ScrollableEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onReachEndEvent = eventHub->GetOnReachEnd();
    onReachEndEvent();
    EXPECT_TRUE(isCalled);
}

/**
 * @tc.name: BoxSelectTest001
 * @tc.desc: Test ScrollablePattern::HandleDragStart
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableEventTest, BoxSelectTest001, TestSize.Level1)
{
    GestureEvent info;
    info.SetRawGlobalLocation(Offset(50, 50));
    info.SetOffsetX(5);
    info.SetOffsetY(10);
    pattern_->HandleDragStart(info);
    EXPECT_EQ(pattern_->mouseStartOffset_, OffsetF(45, 40));
}
} // namespace OHOS::Ace::NG
