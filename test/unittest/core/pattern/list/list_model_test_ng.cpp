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
#include "ui/base/geometry/ng/offset_t.h"

#include "core/components_v2/list/list_properties.h"

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
    CreateDone();
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
    CreateDone();
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
    CreateDone();
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
    CreateDone();
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
    CreateDone();
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
    CreateDone();
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
    CreateDone();
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
    CreateDone();
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
    CreateDone();
}

/**
 * @tc.name: SetOnReachEnd_TwoParameters
 * @tc.desc: Test ListModelNG SetOnReachEnd
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, SetOnReachEnd_TwoParameters, TestSize.Level1)
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
    bool onEnd = false;
    auto onReachEnd = [&onEnd]() { onEnd = true; };

    /**
     * @tc.steps: step2. Calling the SetOnReachEnd function
     * @tc.expected: The onEnd from false to true
     */
    model.SetOnReachEnd(listNode, std::move(onReachEnd));
    auto onReachEndEvent = eventHub->GetOnReachEnd();
    onReachEndEvent();
    EXPECT_TRUE(onEnd);
    CreateDone();
}

/**
 * @tc.name: SetOnItemMove_OneParameter
 * @tc.desc: Test ListModelNG SetOnItemMove
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, SetOnItemMove_OneParameter, TestSize.Level1)
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
    auto onItemMove = [](int32_t from, int32_t to) {
        if (from == 0 || to == 0) {
            return false;
        }
        return true;
    };

    /**
     * @tc.steps: step2. Calling the SetOnItemMove function
     * @tc.expected: The onItemMoveEvent return true
     */
    model.SetOnItemMove(std::move(onItemMove));
    auto onItemMoveEvent = eventHub->GetOnItemMove();
    auto result = onItemMoveEvent(2, 4);
    EXPECT_TRUE(result);
    CreateDone();
}

/**
 * @tc.name: SetOnItemDragEnter_OneParameter
 * @tc.desc: Test ListModelNG SetOnItemDragEnter
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, SetOnItemDragEnter_OneParameter, TestSize.Level1)
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

    /**
     * @tc.steps: step2. Set the ItemDragInfo and onItemDragEnter
     */
    ItemDragInfo info;
    info.SetX(8.0);
    info.SetY(10.0);
    OffsetT<double> offset(2.0, 4.0);
    auto onItemDragEnter = [&offset](const ItemDragInfo& info) {
        offset.SetX(info.GetX());
        offset.SetY(info.GetY());
    };

    /**
     * @tc.steps: step3. Calling the SetOnItemDragEnter function
     * @tc.expected: The onItemDragEnterEvent from {2.0 4.0} to {8.0, 10.0}
     */
    model.SetOnItemDragEnter(std::move(onItemDragEnter));
    auto onItemDragEnterEvent = eventHub->GetOnItemDragEnter();
    onItemDragEnterEvent(info);
    EXPECT_EQ(offset.GetX(), 8.0);
    EXPECT_EQ(offset.GetY(), 10.0);
    CreateDone();
}

/**
 * @tc.name: SetOnItemDragLeave_OneParameter
 * @tc.desc: Test ListModelNG SetOnItemDragLeave
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, SetOnItemDragLeave_OneParameter, TestSize.Level1)
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

    /**
     * @tc.steps: step2. Set the ItemDragInfo and onItemDragLeave
     */
    ItemDragInfo info;
    info.SetX(8.0);
    info.SetY(10.0);
    OffsetT<double> offset(2.0, 4.0);
    auto onItemDragLeave = [&offset](const ItemDragInfo& info, int32_t targetId) {
        offset.SetX(info.GetX() * targetId);
        offset.SetY(info.GetY() * targetId);
    };

    /**
     * @tc.steps: step3. Calling the SetOnItemDragLeave function
     * @tc.expected: The onItemDragLeaveEvent from {2.0 4.0} to {16.0, 20.0}
     */
    model.SetOnItemDragLeave(std::move(onItemDragLeave));
    auto onItemDragLeaveEvent = eventHub->GetOnItemDragLeave();
    onItemDragLeaveEvent(info, 2);
    EXPECT_EQ(offset.GetX(), 16.0);
    EXPECT_EQ(offset.GetY(), 20.0);
    CreateDone();
}

/**
 * @tc.name: SetOnItemDragMove_OneParameter
 * @tc.desc: Test ListModelNG SetOnItemDragMove
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, SetOnItemDragMove_OneParameter, TestSize.Level1)
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

    /**
     * @tc.steps: step2. Set the ItemDragInfo and onItemDragMove
     */
    ItemDragInfo info;
    info.SetX(8.0);
    info.SetY(10.0);
    OffsetT<double> offset(2.0, 4.0);
    auto onItemDragMove = [&offset](const ItemDragInfo& info, int32_t fromIndex, int32_t toIndex) {
        offset.SetX(info.GetX() * fromIndex);
        offset.SetY(info.GetY() * toIndex);
    };

    /**
     * @tc.steps: step3. Calling the SetOnItemDragMove function
     * @tc.expected: The onItemDragMoveEvent from {2.0 4.0} to {8.0, 20.0}
     */
    model.SetOnItemDragMove(std::move(onItemDragMove));
    auto onItemDragMoveEvent = eventHub->GetOnItemDragMove();
    onItemDragMoveEvent(info, 1, 2);
    EXPECT_EQ(offset.GetX(), 8.0);
    EXPECT_EQ(offset.GetY(), 20.0);
    CreateDone();
}

/**
 * @tc.name: SetOnItemDrop_OneParameter
 * @tc.desc: Test ListModelNG SetOnItemDrop
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, SetOnItemDrop_OneParameter, TestSize.Level1)
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

    /**
     * @tc.steps: step2. Set the ItemDragInfo and onItemDrop
     */
    ItemDragInfo info;
    info.SetX(10.0);
    info.SetY(20.0);
    OffsetT<double> offset(2.0, 4.0);
    auto onItemDrop = [&offset](const ItemDragInfo& info, int32_t fromIndex, int32_t toIndex, bool success) {
        if (success) {
            offset.SetX(info.GetX() / fromIndex);
            offset.SetY(info.GetY() / toIndex);
        } else {
            offset.SetX(info.GetX());
            offset.SetY(info.GetY());
        }
    };

    /**
     * @tc.steps: step3. Calling the SetOnItemDrop function
     * @tc.expected: The onItemDropEvent from {10.0 20.0} to {5.0, 5.0}
     */
    model.SetOnItemDrop(std::move(onItemDrop));
    auto onItemDropEvent = eventHub->GetOnItemDrop();
    onItemDropEvent(info, 2, 4, true);
    EXPECT_EQ(offset.GetX(), 5.0);
    EXPECT_EQ(offset.GetY(), 5.0);
    CreateDone();
}

/**
 * @tc.name: SetEditMode_TwoParameters
 * @tc.desc: Test ListModelNG SetEditMode
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, SetEditMode_TwoParameters, TestSize.Level1)
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
     * @tc.steps: step2. Set the editMode to true
     * @tc.expected: The value of result is true
     */
    model.SetEditMode(listNode, true);
    auto result = layoutProperty->GetEditMode();
    EXPECT_TRUE(result.value());
    CreateDone();
}

/**
 * @tc.name: SetMultiSelectable_TwoParameters
 * @tc.desc: Test ListModelNG SetMultiSelectable
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, SetMultiSelectable_TwoParameters, TestSize.Level1)
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
    pattern->SetMultiSelectable(false);

    /**
     * @tc.steps: step2. Set the selectable to true
     * @tc.expected: The multiSelectable_ of pattern is true
     */
    model.SetMultiSelectable(listNode, true);
    EXPECT_TRUE(pattern->multiSelectable_);
    CreateDone();
}

/**
 * @tc.name: SetChainAnimation_TwoParameters
 * @tc.desc: Test ListModelNG SetChainAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, SetChainAnimation_TwoParameters, TestSize.Level1)
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
     * @tc.steps: step2. Set the chainAnimation to true
     * @tc.expected: The value of result is true
     */
    model.SetChainAnimation(listNode, true);
    auto result = layoutProperty->GetChainAnimation();
    EXPECT_TRUE(result.value());
    CreateDone();
}

/**
 * @tc.name: SetSticky_TwoParameters
 * @tc.desc: Test ListModelNG SetSticky
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, SetSticky_TwoParameters, TestSize.Level1)
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
     * @tc.steps: step2. Set the StickyStyle to 3
     * @tc.expected: The sticky is set BOTH
     */
    model.SetSticky(listNode, 3);
    auto result = model.GetSticky(listNode);
    EXPECT_EQ(static_cast<V2::StickyStyle>(result), V2::StickyStyle::BOTH);
    CreateDone();
}

/**
 * @tc.name: SetEdgeEffect_FourParameters
 * @tc.desc: Test ListModelNG SetEdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, SetEdgeEffect_FourParameters, TestSize.Level1)
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
     * @tc.steps: step2. Set the edgeEffectAlwaysEnabled_ to false
     * Set the effectEdge_ to ALL
     */
    pattern->edgeEffectAlwaysEnabled_ = false;
    pattern->effectEdge_ = EffectEdge::ALL;

    /**
     * @tc.steps: step3. Set the SetEdgeEffect to 1
     * @tc.expected: The edgeEffectAlwaysEnabled_ be true and the effectEdge_ be START
     * and the sticky is set FADE
     */
    model.SetEdgeEffect(listNode, 1, true, EffectEdge::START);
    auto result = model.GetEdgeEffect(listNode);
    EXPECT_TRUE(pattern->edgeEffectAlwaysEnabled_);
    EXPECT_EQ(pattern->effectEdge_, EffectEdge::START);
    EXPECT_EQ(static_cast<EdgeEffect>(result), EdgeEffect::FADE);
    CreateDone();
}

/**
 * @tc.name: GetListDirection
 * @tc.desc: Test ListModelNG GetListDirection
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, GetListDirection, TestSize.Level1)
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
     * @tc.steps: step2. Set the Axis to HORIZONTAL
     * @tc.expected: The result is static_cast<Axis>(Axis::HORIZONTAL)
     */
    model.SetListDirection(listNode, static_cast<int32_t>(Axis::HORIZONTAL));
    auto result = model.GetListDirection(listNode);
    EXPECT_EQ(result, 1);
    CreateDone();
}

/**
 * @tc.name: GetListFriction
 * @tc.desc: Test ListModelNG GetListFriction
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, GetListFriction, TestSize.Level1)
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
     * @tc.steps: step2. Set the friction of pattern to 6.0
     */
    pattern->SetFriction(6.0);

    /**
     * @tc.steps: step3. Set the friction to 2.0
     * @tc.expected: The result is 2.0
     */
    model.SetListFriction(listNode, 2.0);
    auto result = model.GetListFriction(listNode);
    EXPECT_EQ(result, 2.0);
    CreateDone();
}

/**
 * @tc.name: SetAndGet_ListNestedScroll
 * @tc.desc: Test ListModelNG::SetListNestedScroll and ListModelNG::GetListNestedScroll
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, SetAndGet_ListNestedScroll, TestSize.Level1)
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
     * @tc.steps: step2. Set the nestedOpt
     */
    NestedScrollOptions nestedOpt;
    nestedOpt.backward = NestedScrollMode::PARENT_FIRST;
    nestedOpt.forward = NestedScrollMode::SELF_FIRST;

    /**
     * @tc.steps: step3. Calling the SetListNestedScroll function
     * @tc.expected: Calling the GetListNestedScroll function returns the set value
     */
    model.SetListNestedScroll(listNode, nestedOpt);
    auto result = model.GetListNestedScroll(listNode);
    EXPECT_EQ(result.backward, NestedScrollMode::PARENT_FIRST);
    EXPECT_EQ(result.forward, NestedScrollMode::SELF_FIRST);
    CreateDone();
}

/**
 * @tc.name: GetListScrollBar
 * @tc.desc: Test ListModelNG GetListScrollBar
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, GetListScrollBar, TestSize.Level1)
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
     * @tc.steps: step2. Set the barState to 2
     * @tc.expected: Calling the GetListScrollBar function returns static_cast<int32_t>(DisplayMode::ON)
     */
    model.SetListScrollBar(listNode, 2);
    auto result = model.GetListScrollBar(listNode);
    EXPECT_EQ(result, static_cast<int32_t>(DisplayMode::ON));
    CreateDone();
}

/**
 * @tc.name: SetListScrollBar_barStateLessZero
 * @tc.desc: Test ListModelNG SetListScrollBar
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, SetListScrollBar_barStateLessZero, TestSize.Level1)
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
     * @tc.steps: step2. Set the barState to -1
     * @tc.expected: Calling the GetListScrollBar function returns static_cast<int32_t>(DisplayMode::OFF)
     */
    model.SetListScrollBar(listNode, -1);
    auto result = model.GetListScrollBar(listNode);
    EXPECT_EQ(result, static_cast<int32_t>(DisplayMode::OFF));
    CreateDone();
}

/**
 * @tc.name: SetListScrollBarWidth
 * @tc.desc: Test ListModelNG SetListScrollBarWidth
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, SetListScrollBarWidth, TestSize.Level1)
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
     * @tc.steps: step2. Calling the SetListScrollBarWidth function
     * @tc.expected: The scrollBarWidth is set successfully
     */
    model.SetListScrollBarWidth(listNode, "2.0vp");
    EXPECT_EQ(paintProperty->GetScrollBarWidth(), 2.0_vp);
    CreateDone();
}

/**
 * @tc.name: SetAndGet_ListItemAlign
 * @tc.desc: Test ListModelNG::SetListItemAlign and ListModelNG::GetListItemAlign
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, SetAndGet_ListItemAlign, TestSize.Level1)
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

    /**
     * @tc.steps: step2. Calling the SetListItemAlign and GetListItemAlign function
     * @tc.expected: The ListItemAlign is updated
     */
    model.SetListItemAlign(listNode, V2::ListItemAlign::CENTER);
    auto result = model.GetListItemAlign(listNode);
    EXPECT_EQ(result, 1);
    CreateDone();
}

/**
 * @tc.name: GetListSpace
 * @tc.desc: Test ListModelNG GetListSpace
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, GetListSpace, TestSize.Level1)
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

    /**
     * @tc.steps: step2. Set the space to 10.0vp
     */
    Dimension space = 10.0_vp;
    model.SetListSpace(listNode, space);

    /**
     * @tc.steps: step3. Calling the GetListSpace function
     * @tc.expected: The ListSpace is updated
     */
    auto result = model.GetListSpace(listNode);
    EXPECT_EQ(result, 10.0);
    CreateDone();
}
} // namespace OHOS::Ace::NG
