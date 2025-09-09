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
#include "list_test_ng.h"
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/common/mock_resource_adapter_v2.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "ui/base/geometry/ng/offset_t.h"

#include "core/components_ng/pattern/list/list_position_controller.h"
#include "core/components_v2/list/list_properties.h"

namespace OHOS::Ace::NG {
constexpr char SCROLLBAR_COLOR_BLUE[] = "#FF0000FF";

class ListModelTestNg : public ListTestNg {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};

void ListModelTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    ResetMockResourceData();
    g_isConfigChangePerform = false;
}

void ListModelTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
    ResetMockResourceData();
    g_isConfigChangePerform = false;
}

void ListModelTestNg::SetUp()
{
    ResetMockResourceData();
    g_isConfigChangePerform = false;
}

void ListModelTestNg::TearDown()
{
    ResetMockResourceData();
    g_isConfigChangePerform = false;
}

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
    model.SetScrollBarColor(Color::BLUE);
    model.SetScrollBarColor(std::nullopt);
    auto scrollBarColor = paintProperty->GetScrollBarColor();
    EXPECT_EQ(scrollBarColor, std::nullopt);
    model.SetScrollBarColor(SCROLLBAR_COLOR_BLUE);
    EXPECT_EQ(paintProperty->GetScrollBarColor()->GetValue(), Color::FromString(SCROLLBAR_COLOR_BLUE).GetValue());
    model.SetScrollBarColor(std::nullopt);
    CreateDone();

    scrollBarColor = paintProperty->GetScrollBarColor();
    EXPECT_EQ(scrollBarColor, std::nullopt);
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

/**
 * @tc.name: GetEdgeEffect
 * @tc.desc: Test ListModelNG GetEdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, GetEdgeEffect, TestSize.Level1)
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
    model.SetEdgeEffect(listNode, static_cast<int32_t>(EdgeEffect::FADE), true, EffectEdge::START);

    /**
     * @tc.steps: step3. Calling the GetEdgeEffect function
     * @tc.expected: The result be 1
     */
    auto result = model.GetEdgeEffect(listNode);
    EXPECT_EQ(result, 1);
    CreateDone();
}

/**
 * @tc.name: Set_GetListStackFromEnd
 * @tc.desc: Test ListModelNG::SetListStackFromEnd and ListModelNG::GetListStackFromEnd
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, Set_GetListStackFromEnd, TestSize.Level1)
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
     * @tc.steps: step2. Calling the SetListStackFromEnd function
     * @tc.expected: Calling the GetListStackFromEnd function returns true
     */
    model.SetListStackFromEnd(listNode, true);

    /**
     * @tc.steps: step3. Calling the GetListStackFromEnd function
     * @tc.expected: The result returns true
     */
    auto result = model.GetListStackFromEnd(listNode);
    EXPECT_TRUE(result);
    CreateDone();
}

/**
 * @tc.name: GetEdgeEffectAlways
 * @tc.desc: Test ListModelNG GetEdgeEffectAlways
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, GetEdgeEffectAlways, TestSize.Level1)
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
     * @tc.steps: step2. Set the EdgeEffectAlways to true
     * @tc.expected: Calling the GetEdgeEffectAlways function returns true
     */
    pattern->SetEdgeEffect(EdgeEffect::FADE, true, EffectEdge::ALL);

    /**
     * @tc.steps: step3. Calling the GetEdgeEffectAlways function
     * @tc.expected: The result returns 1
     */
    auto result = model.GetEdgeEffectAlways(listNode);
    EXPECT_EQ(result, 1);
    CreateDone();
}

/**
 * @tc.name: SetChainAnimationOptions_TwoParameters
 * @tc.desc: Test ListModelNG SetChainAnimationOptions
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, SetChainAnimationOptions_TwoParameters, TestSize.Level1)
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
     * @tc.steps: step2. Set the minSpace of chainAnimationOptions_ to 2.0_vp
     * and set the minSpace of chainAnimationOptions_ to 4.0_vp
     */
    ChainAnimationOptions options;
    options.minSpace = 2.0_vp;
    options.maxSpace = 4.0_vp;

    /**
     * @tc.steps: step3. Calling the SetChainAnimationOptions function
     * @tc.expected: The minSpace of chainAnimationOptions_ returns 2.0vp
     */
    model.SetChainAnimationOptions(listNode, options);
    EXPECT_EQ(pattern->chainAnimationOptions_.value().minSpace, 2.0_vp);
    CreateDone();
}

/**
 * @tc.name: GetDisplayMode
 * @tc.desc: Test ListModelNG GetDisplayMode
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, GetDisplayMode, TestSize.Level1)
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
     * @tc.steps: step2. Calling the GetDisplayMode function
     * @tc.expected: The result returns OFF
     */
    auto result = model.GetDisplayMode();
    EXPECT_EQ(result, DisplayMode::OFF);
    CreateDone();
}

/**
 * @tc.name: SetOnScroll_TwoParameters
 * @tc.desc: Test ListModelNG SetOnScroll
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, SetOnScroll_TwoParameters, TestSize.Level1)
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
     * @tc.steps: step2. Set the OnScrollEvent
     * and set isScroll to false
     */
    bool isScroll = false;
    OnScrollEvent scrollHandler = [&isScroll](Dimension offset, ScrollState state) { isScroll = true; };

    /**
     * @tc.steps: step3. Calling the SetOnScroll function
     * @tc.expected: The isScroll from false to true
     */
    model.SetOnScroll(listNode, std::move(scrollHandler));
    auto onScroll = eventHub->GetOnDidScroll();
    onScroll(10.0_vp, ScrollState::SCROLL);
    EXPECT_TRUE(isScroll);
    CreateDone();
}

/**
 * @tc.name: SetOnScrollFrameBegin_TwoParameters
 * @tc.desc: Test ListModelNG SetOnScrollFrameBegin
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, SetOnScrollFrameBegin_TwoParameters, TestSize.Level1)
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
     * @tc.steps: step2. Set the OnScrollEvent
     * and set isScroll to false
     */
    auto scrollHandler = [](Dimension delta, ScrollState state) -> ScrollFrameResult {
        Dimension newOffset;

        switch (state) {
            case ScrollState::IDLE:
                newOffset.SetValue(0.0);
                break;

            case ScrollState::SCROLL:
                newOffset.SetValue(delta.Value());
                break;

            case ScrollState::FLING:
                newOffset.SetValue(delta.Value() * 0.8);
                break;
        }

        return { newOffset };
    };

    /**
     * @tc.steps: step3. Calling the SetOnScrollFrameBegin function
     * @tc.expected: The isScroll from false to true
     */
    model.SetOnScrollFrameBegin(listNode, std::move(scrollHandler));
    auto onScrollFrameBeginEvent = eventHub->GetOnScrollFrameBegin();
    auto onScrollFrameBegin = onScrollFrameBeginEvent(Dimension(10.0), ScrollState::FLING);
    EXPECT_EQ(onScrollFrameBegin.offset.Value(), 8.0);
    CreateDone();
}

/**
 * @tc.name: SetListChildrenMainSize
 * @tc.desc: Test ListModelNG SetListChildrenMainSize
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, SetListChildrenMainSize, TestSize.Level1)
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
    RefPtr<PipelineContext> context = AceType::MakeRefPtr<PipelineContext>();
    context->SetPixelRoundMode(PixelRoundMode::PIXEL_ROUND_AFTER_MEASURE);
    listNode->context_ = AceType::RawPtr(context);
    std::vector<float> mainSize = { 2.0f, 4.0f };
    pattern->childrenSize_ = AceType::MakeRefPtr<ListChildrenMainSize>(mainSize, 2.0f);
    pattern->childrenSize_->isRoundingMode_ = false;

    /**
     * @tc.steps: step2. Calling the SetListChildrenMainSize function
     * @tc.expected: The isRoundingMode_ be true
     */
    model.SetListChildrenMainSize(listNode, 2.0f, mainSize);
    listNode->context_ = nullptr;
    EXPECT_TRUE(pattern->childrenSize_->isRoundingMode_);
    CreateDone();
}

/**
 * @tc.name: GetInitialIndex
 * @tc.desc: Test ListModelNG GetInitialIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, GetInitialIndex, TestSize.Level1)
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
     * @tc.steps: step2. Set the InitialIndex to 2
     * @tc.expected: Calling the GetInitialIndex function returns 2
     */
    model.SetInitialIndex(listNode, 2);

    /**
     * @tc.steps: step3. Calling the GetInitialIndex function
     * @tc.expected: The result return 2
     */
    auto result = model.GetInitialIndex(listNode);
    EXPECT_EQ(result, 2);
    CreateDone();
}

/**
 * @tc.name: GetDivider
 * @tc.desc: Test ListModelNG GetDivider
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, GetDivider, TestSize.Level1)
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
     * @tc.steps: step2. Set the divider
     */
    V2::ItemDivider divider = { 6.0_vp, 2.0_vp, 8.0_vp, Color::RED };
    model.SetDivider(divider);

    /**
     * @tc.steps: step3. Calling the GetDivider function
     * @tc.expected: The diver is set successfully, and the obtained diver is the same as the setting
     */
    auto result = model.GetDivider(listNode);
    EXPECT_EQ(result, divider);
    CreateDone();
}

/**
 * @tc.name: CreateWithResourceObjScrollBarColor00
 * @tc.desc: Test ListModelNG CreateWithResourceObjScrollBarColor
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, CreateWithResourceObjScrollBarColor00, TestSize.Level1)
{
    ResetMockResourceData();
    g_isConfigChangePerform = true;

    const int32_t resId = 0;
    const int32_t resType = static_cast<int32_t>(ResourceType::COLOR);
    const Color resData = Color::RED;
    AddMockResourceData(0, resData);

    /**
     * @tc.steps: step1. Construct the objects for test
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
     * @tc.steps: step2. test
     */
    model.CreateWithResourceObjScrollBarColor(nullptr);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_SCROLL_BAR);
    auto scrollBarTheme = ScrollBarTheme::Builder().Build(themeConstants);
    scrollBarTheme->foregroundColor_ = Color::RED;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(scrollBarTheme));

    std::vector<ResourceObjectParams> params;
    auto resObj = AceType::MakeRefPtr<ResourceObject>(resId, resType, params, "", "", Container::CurrentIdSafely());
    model.CreateWithResourceObjScrollBarColor(resObj);
    ASSERT_NE(pattern->resourceMgr_, nullptr);
    pattern->resourceMgr_->ReloadResources();

    auto currentColor = ListModelNG::GetScrollBarColor(listNode);

    EXPECT_EQ(resData.GetValue(), currentColor);
    CreateDone();

    ResetMockResourceData();
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetScroller_ThreeParameters
 * @tc.desc: Test ListModelNG SetScroller
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, SetScroller_ThreeParameters, TestSize.Level1)
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

    /**
     * @tc.steps: step2. Set the proxy and scroller
     */
    RefPtr<ScrollBarProxy> proxy = AceType::MakeRefPtr<ScrollBarProxy>();
    RefPtr<ListPositionController> scroller = AceType::MakeRefPtr<ListPositionController>();

    /**
     * @tc.steps: step3. Calling the SetScroller function
     * @tc.expected: The scrollBarProxy_ and positionController_ of pattern are set successfully
     */
    model.SetScroller(listNode, scroller, proxy);
    EXPECT_EQ(pattern->GetScrollBarProxy(), proxy);
    EXPECT_EQ(pattern->GetOrCreatePositionController()->GetScrollPattern(), pattern);
    CreateDone();
}

/**
 * @tc.name: SetOnItemMove_TwoParameters
 * @tc.desc: Test ListModelNG SetOnItemMove
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, SetOnItemMove_TwoParameters, TestSize.Level1)
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
     * @tc.steps: step2. Set the onItemMoveEvent
     */
    auto onItemMoveEvent = [](int32_t fromIndex, int32_t toIndex) {
        if (fromIndex < 0 || toIndex < 0 || fromIndex == toIndex) {
            return false;
        }
        return true;
    };

    /**
     * @tc.steps: step3. Calling the SetOnItemMove function
     * @tc.expected: Calling onItemMove returns true
     */
    model.SetOnItemMove(listNode, std::move(onItemMoveEvent));
    auto onItemMove = eventHub->GetOnItemMove();
    auto result = onItemMove(2, 4);
    EXPECT_TRUE(result);
    CreateDone();
}

/**
 * @tc.name: SetOnItemDragStart_TwoParameters
 * @tc.desc: Test ListModelNG SetOnItemDragStart
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, SetOnItemDragStart_TwoParameters, TestSize.Level1)
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
     * @tc.steps: step2. Set the SetOnItemDragStart
     */
    auto gesture = listNode->GetOrCreateGestureEventHub();
    ItemDragInfo dragInfo;
    dragInfo.SetX(2.0);
    dragInfo.SetY(4.0);

    auto onItemDragStartEvent = [](const ItemDragInfo& dragInfo, int32_t itemIndex) {
        auto startFunc = [](GestureEvent& event) {};
        auto updateFunc = [](GestureEvent& event) {};
        auto endFunc = [](GestureEvent& event) {};
        auto cancelFunc = []() {};
        std::vector<KeyCode> pressedKeyCodes = { KeyCode::KEY_A, KeyCode::KEY_B };

        RefPtr<DragEvent> preview = AceType::MakeRefPtr<DragEvent>(
            std::move(startFunc), std::move(updateFunc), std::move(endFunc), std::move(cancelFunc));
        preview->SetPressedKeyCodes(pressedKeyCodes);
        return preview;
    };

    /**
     * @tc.steps: step3. Calling the SetOnItemDragStart function
     * @tc.expected: Calling PressedKeyCodes.size() of result returns 2
     */
    model.SetOnItemDragStart(listNode, std::move(onItemDragStartEvent));
    auto onDragStart = eventHub->GetOnItemDragStart();
    auto aceType = onDragStart(dragInfo, 2);
    auto result = AceType::DynamicCast<DragEvent>(aceType);
    EXPECT_EQ(result->GetPressedKeyCodes().size(), 2);
    EXPECT_EQ(gesture->dragEventActuator_->GetFingers(), DEFAULT_PAN_FINGER);
    EXPECT_EQ(gesture->dragEventActuator_->GetDirection().type, PanDirection::ALL);
    CreateDone();
}

/**
 * @tc.name: SetOnItemDragEnter_TwoParameters
 * @tc.desc: Test ListModelNG SetOnItemDragEnter
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, SetOnItemDragEnter_TwoParameters, TestSize.Level1)
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
     * @tc.steps: step2. Set the onItemMoveEvent
     */
    ItemDragInfo dragInfo;
    dragInfo.SetX(2.0);
    dragInfo.SetY(4.0);
    bool enter = false;
    auto onDragEnterEvent = [&enter](const ItemDragInfo& dragInfo) { enter = true; };

    /**
     * @tc.steps: step3. Calling the SetOnItemDragEnter function
     * @tc.expected: The enter returns true
     */
    model.SetOnItemDragEnter(listNode, std::move(onDragEnterEvent));
    auto onDragEnter = eventHub->GetOnItemDragEnter();
    onDragEnter(dragInfo);
    EXPECT_TRUE(enter);
    CreateDone();
}

/**
 * @tc.name: SetOnItemDragLeave_TwoParameters
 * @tc.desc: Test ListModelNG SetOnItemDragLeave
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, SetOnItemDragLeave_TwoParameters, TestSize.Level1)
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
     * @tc.steps: step2. Set the onItemDragLeaveEvent
     */
    ItemDragInfo dragInfo;
    dragInfo.SetX(2.0);
    dragInfo.SetY(4.0);
    bool leave = false;
    auto onItemDragLeaveEvent = [&leave](const ItemDragInfo& dragInfo, int32_t targetIndex) { leave = true; };

    /**
     * @tc.steps: step3. Calling the SetOnItemDragLeave function
     * @tc.expected: The leave returns true
     */
    model.SetOnItemDragLeave(listNode, std::move(onItemDragLeaveEvent));
    auto onItemDragLeave = eventHub->GetOnItemDragLeave();
    onItemDragLeave(dragInfo, 2);
    EXPECT_TRUE(leave);
    CreateDone();
}

/**
 * @tc.name: SetOnItemDragMove_TwoParameters
 * @tc.desc: Test ListModelNG SetOnItemDragMove
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, SetOnItemDragMove_TwoParameters, TestSize.Level1)
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
     * @tc.steps: step2. Set the onItemDragMoveEvent
     */
    ItemDragInfo dragInfo;
    dragInfo.SetX(2.0);
    dragInfo.SetY(4.0);
    bool move = false;
    auto onItemDragMoveEvent = [&move](const ItemDragInfo& dragInfo, int32_t groupIndex, int32_t itemIndex) {
        move = true;
    };

    /**
     * @tc.steps: step3. Calling the SetOnItemDragMove function
     * @tc.expected: The move returns true
     */
    model.SetOnItemDragMove(listNode, std::move(onItemDragMoveEvent));
    auto onItemDragMove = eventHub->GetOnItemDragMove();
    onItemDragMove(dragInfo, 2, 1);
    EXPECT_TRUE(move);
    CreateDone();
}

/**
 * @tc.name: SetOnItemDrop_TwoParameters
 * @tc.desc: Test ListModelNG SetOnItemDrop
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, SetOnItemDrop_TwoParameters, TestSize.Level1)
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
     * @tc.steps: step2. Set the onItemDragMoveEvent
     */
    ItemDragInfo dragInfo;
    dragInfo.SetX(2.0);
    dragInfo.SetY(4.0);
    bool drop = false;
    auto onItemDropEvent = [&drop](const ItemDragInfo& dragInfo, int32_t targetGroup, int32_t targetPos, bool isMove) {
        drop = true;
    };

    /**
     * @tc.steps: step3. Calling the SetOnItemDrop function
     * @tc.expected: The move returns true
     */
    model.SetOnItemDrop(listNode, std::move(onItemDropEvent));
    auto onItemDrop = eventHub->GetOnItemDrop();
    onItemDrop(dragInfo, 2, 1, false);
    EXPECT_TRUE(drop);
    CreateDone();
}

/**
 * @tc.name: ScrollToItemInGroup001
 * @tc.desc: Test ListModelNG ScrollToItemInGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, ScrollToItemInGroup001, TestSize.Level1)
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

    /**
     * @tc.steps: step2. Set the scrollAlign_ to CENTER
     * @tc.expected: set he isInitialized_ to true
     */
    pattern->scrollAlign_ = ScrollAlign::CENTER;
    pattern->isInitialized_ = true;

    /**
     * @tc.steps: step3. Calling the ScrollToItemInGroup function
     * @tc.expected: The scrollAlign_ be START
     */
    model.ScrollToItemInGroup(listNode, 2, 3, false, ScrollAlign::NONE);
    EXPECT_EQ(pattern->scrollAlign_, ScrollAlign::START);
    CreateDone();
}

/**
 * @tc.name: ScrollToItemInGroup002
 * @tc.desc: Test ListModelNG ScrollToItemInGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListModelTestNg, ScrollToItemInGroup002, TestSize.Level1)
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

    /**
     * @tc.steps: step2. Set the scrollAlign_ to START
     * @tc.expected: set he isInitialized_ to false
     */
    pattern->scrollAlign_ = ScrollAlign::START;
    pattern->isInitialized_ = false;

    /**
     * @tc.steps: step3. Calling the ScrollToItemInGroup function
     * @tc.expected: The scrollAlign_ be END
     */
    model.ScrollToItemInGroup(listNode, 2, 3, false, ScrollAlign::AUTO);
    EXPECT_EQ(pattern->scrollAlign_, ScrollAlign::END);
    CreateDone();
}
} // namespace OHOS::Ace::NG