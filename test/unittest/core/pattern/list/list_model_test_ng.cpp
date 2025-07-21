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

#include <cstdint>

#include "list_test_ng.h"

namespace OHOS::Ace::NG {
constexpr char SCROLLBAR_COLOR_BLUE[] = "#FF0000FF";

class ListModelTestNg : public ListTestNg {};

/**
 * @tc.name: SetScrollBarColor
 * @tc.desc: Test ListModelNG SetScrollBarColor
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, SetScrollBarColor, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<ScrollablePaintProperty> scrollablePaintProperty = AceType::MakeRefPtr<ScrollablePaintProperty>();
    listNode->paintProperty_ = scrollablePaintProperty;
    auto paintProperty = listNode->GetPaintProperty<ScrollablePaintProperty>();

    /**
     * @tc.steps: step2. Calling the SetScrollBarColor function
     * @tc.expected: The ScrollBarColor is updated
     */
    model.SetScrollBarColor(SCROLLBAR_COLOR_BLUE);
    EXPECT_EQ(paintProperty->GetScrollBarColor()->GetValue(), Color::FromString(SCROLLBAR_COLOR_BLUE).GetValue());
}

/**
 * @tc.name: SetScrollBarWidth
 * @tc.desc: Test ListModelNG SetScrollBarWidth
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, SetScrollBarWidth, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<ScrollablePaintProperty> scrollablePaintProperty = AceType::MakeRefPtr<ScrollablePaintProperty>();
    listNode->paintProperty_ = scrollablePaintProperty;
    auto paintProperty = listNode->GetPaintProperty<ScrollablePaintProperty>();

    /**
     * @tc.steps: step2. Calling the SetScrollBarWidth function
     * @tc.expected: The scrollBarWidth is set successfully
     */
    model.SetScrollBarWidth("2.0vp");
    EXPECT_EQ(paintProperty->GetScrollBarWidth(), 2.0_vp);
}

/**
 * @tc.name: SetLaneConstrain
 * @tc.desc: Test ListModelNG SetLaneConstrain
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, SetLaneConstrain, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    listNode->SetLayoutProperty(listLayoutProperty);
    auto layoutProperty = listNode->GetLayoutProperty<ListLayoutProperty>();

    /**
     * @tc.steps: step2. Set the laneMinLength and laneMaxLength
     */
    Dimension laneMinLength = 100.0_vp;
    Dimension laneMaxLength = 300.0_vp;

    /**
     * @tc.steps: step3. Calling the SetLaneConstrain function
     * @tc.expected: The scrollBarWidth is set successfully
     */
    model.SetLaneConstrain(laneMinLength, laneMaxLength);
    EXPECT_EQ(layoutProperty->GetLaneMinLength(), 100.0_vp);
    EXPECT_EQ(layoutProperty->GetLaneMaxLength(), 300.0_vp);
}

/**
 * @tc.name: GetSticky
 * @tc.desc: Test ListModelNG GetSticky
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, GetSticky, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    listNode->SetLayoutProperty(listLayoutProperty);
    auto layoutProperty = listNode->GetLayoutProperty<ListLayoutProperty>();

    /**
     * @tc.steps: step2. Set the StickyStyle to both
     */
    model.SetSticky(V2::StickyStyle::BOTH);

    /**
     * @tc.steps: step3. Calling the GetSticky function
     * @tc.expected: The sticky is set successfully
     */
    auto result = model.GetSticky(listNode);
    EXPECT_EQ(result, static_cast<int32_t>(layoutProperty->GetStickyStyleValue()));
}

/**
 * @tc.name: GetFocusWrapMode
 * @tc.desc: Test ListModelNG GetFocusWrapMode
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, GetFocusWrapMode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    listNode->SetLayoutProperty(listLayoutProperty);
    auto layoutProperty = listNode->GetLayoutProperty<ListLayoutProperty>();

    /**
     * @tc.steps: step2. Set the FocusWrapMode to WRAP_WITH_ARROW
     */
    model.SetFocusWrapMode(FocusWrapMode::WRAP_WITH_ARROW);

    /**
     * @tc.steps: step3. Calling the GetFocusWrapMode function
     * @tc.expected: The FocusWrapMode is set successfully
     */
    auto result = model.GetFocusWrapMode(listNode);
    EXPECT_EQ(result, FocusWrapMode::WRAP_WITH_ARROW);
}

/**
 * @tc.name: SetFocusWrapMode_TwoParameters
 * @tc.desc: Test ListModelNG SetFocusWrapMode
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, SetFocusWrapMode_TwoParameters, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    listNode->SetLayoutProperty(listLayoutProperty);
    auto layoutProperty = listNode->GetLayoutProperty<ListLayoutProperty>();

    /**
     * @tc.steps: step2. Set the FocusWrapMode to WRAP_WITH_ARROW
     * @tc.expected: The FocusWrapMode is set successfully
     */
    model.SetFocusWrapMode(listNode, FocusWrapMode::WRAP_WITH_ARROW);
    EXPECT_EQ(model.GetFocusWrapMode(listNode), FocusWrapMode::WRAP_WITH_ARROW);
}

/**
 * @tc.name: SetOnScrollBegin
 * @tc.desc: Test ListModelNG SetOnScrollBegin
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, SetOnScrollBegin, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    listNode->SetLayoutProperty(listLayoutProperty);
    auto layoutProperty = listNode->GetLayoutProperty<ListLayoutProperty>();
    RefPtr<ListEventHub> listEventHub = AceType::MakeRefPtr<ListEventHub>();
    listNode->eventHub_ = listEventHub;
    auto eventHub = listNode->GetEventHub<ListEventHub>();
    auto scrollBeginHandler = [](Dimension initialDeltaX, Dimension initialDeltaY) -> ScrollInfo {
        return { initialDeltaX, initialDeltaY };
    };

    /**
     * @tc.steps: step2. Calling the SetOnScrollBegin function
     * @tc.expected: Calling the onScrollBeginEvent returns {10.0, 5.0}
     */
    model.SetOnScrollBegin(std::move(scrollBeginHandler));
    auto onScrollBeginEvent = eventHub->GetOnScrollBegin();
    auto onScrollBegin = onScrollBeginEvent(Dimension(10.0), Dimension(5.0));
    EXPECT_EQ(onScrollBegin.dx.Value(), 10.0);
    EXPECT_EQ(onScrollBegin.dy.Value(), 5.0);
}

/**
 * @tc.name: SetOnScrollIndex
 * @tc.desc: Test ListModelNG SetOnScrollIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, SetOnScrollIndex, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<ListEventHub> listEventHub = AceType::MakeRefPtr<ListEventHub>();
    listNode->eventHub_ = listEventHub;
    auto eventHub = listNode->GetEventHub<ListEventHub>();
    int32_t data = 2;
    auto scrollIndexHandler = [&data](int32_t first, int32_t last, int32_t total) {
        if (last >= total - 5) {
            data += 5;
        }
    };

    /**
     * @tc.steps: step2. Calling the SetOnScrollIndex function
     * @tc.expected: The data from 2 to 7
     */
    model.SetOnScrollIndex(listNode, std::move(scrollIndexHandler));
    auto onScrollIndexEvent = eventHub->GetOnScrollIndex();
    onScrollIndexEvent(0, 8, 10);
    EXPECT_EQ(data, 7);
}

/**
 * @tc.name: SetOnReachStart_OneParameter
 * @tc.desc: Test ListModelNG SetOnReachStart
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, SetOnReachStart_OneParameter, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListModelNG model;
    model.Create(false);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<ListEventHub> listEventHub = AceType::MakeRefPtr<ListEventHub>();
    listNode->eventHub_ = listEventHub;
    auto eventHub = listNode->GetEventHub<ListEventHub>();
    bool onStart = false;
    auto onReachStart = [&onStart]() { onStart = true; };

    /**
     * @tc.steps: step2. Calling the SetOnReachStart function
     * @tc.expected: The onStart from false to true
     */
    model.SetOnReachStart(std::move(onReachStart));
    auto onReachStartEvent = eventHub->GetOnReachStart();
    onReachStartEvent();
    EXPECT_TRUE(onStart);
}
} // namespace OHOS::Ace::NG