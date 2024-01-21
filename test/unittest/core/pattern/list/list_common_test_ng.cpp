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

#include "list_test_ng.h"

namespace OHOS::Ace::NG {

namespace {
const Offset LEFT_TOP = Offset(120.f, 150.f);
const Offset LEFT_BOTTOM = Offset(120.f, 250.f);
const Offset RIGHT_TOP = Offset(360.f, 150.f);
const Offset RIGHT_BOTTOM = Offset(360.f, 250.f);
} // namespace

class ListCommonTestNg : public ListTestNg {
public:
    void MouseSelect(Offset start, Offset end);
    AssertionResult IsEqualNextFocusNode(FocusStep step, int32_t currentIndex, int32_t expectNextIndex);
};

void ListCommonTestNg::MouseSelect(Offset start, Offset end)
{
    GestureEvent info;
    info.SetInputEventType(InputEventType::MOUSE_BUTTON);
    info.SetLocalLocation(start);
    info.SetGlobalLocation(start);
    pattern_->HandleDragStart(info);
    if (start != end) {
        info.SetLocalLocation(end);
        info.SetGlobalLocation(end);
        pattern_->HandleDragUpdate(info);
    }
    pattern_->HandleDragEnd(info);
}

AssertionResult ListCommonTestNg::IsEqualNextFocusNode(FocusStep step, int32_t currentIndex, int32_t expectNextIndex)
{
    std::vector<RefPtr<FrameNode>> listItems = GetALLItem();
    RefPtr<FocusHub> currentFocusNode = listItems[currentIndex]->GetOrCreateFocusHub();
    currentFocusNode->RequestFocusImmediately();
    RefPtr<FocusHub> nextFocusNode = pattern_->GetNextFocusNode(step, currentFocusNode).Upgrade();
    if (expectNextIndex != NULL_VALUE && nextFocusNode == nullptr) {
        return AssertionFailure() << "Next FocusNode is null.";
    }
    int32_t nextIndex = findFocusNodeIndex(nextFocusNode);
    return IsEqual(nextIndex, expectNextIndex);
}

/**
 * @tc.name: FocusStep001
 * @tc.desc: Test GetNextFocusNode func with VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, FocusStep001, TestSize.Level1)
{
    Create([](ListModelNG model) { CreateItem(VIEW_LINE_NUMBER, Axis::VERTICAL); });

    /**
     * @tc.steps: step1. GetNextFocusNode from top.
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_VALUE));

    /**
     * @tc.steps: step2. GetNextFocusNode from middle.
     */
    currentIndex = 4;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 3));

    /**
     * @tc.steps: step3. GetNextFocusNode from bottom.
     */
    currentIndex = 7;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 6));
}

/**
 * @tc.name: FocusStep002
 * @tc.desc: Test GetNextFocusNode func width HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, FocusStep002, TestSize.Level1)
{
    Create([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        CreateItem(VIEW_LINE_NUMBER, Axis::HORIZONTAL);
    });

    /**
     * @tc.steps: step1. GetNextFocusNode from left.
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_VALUE));

    /**
     * @tc.steps: step2. GetNextFocusNode from middle.
     */
    currentIndex = 4;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 3));

    /**
     * @tc.steps: step3. GetNextFocusNode from right.
     */
    currentIndex = 7;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 6));
}

/**
 * @tc.name: FocusStep003
 * @tc.desc: Test GetNextFocusNode when List has ListItemGroup with VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, FocusStep003, TestSize.Level1)
{
    Create([](ListModelNG model) { CreateGroup(2); });

    /**
     * @tc.steps: step1. GetNextFocusNode from top.
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_VALUE));

    /**
     * @tc.steps: step2. GetNextFocusNode from middle of first ListItemGroup.
     */
    currentIndex = 2;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 1));

    /**
     * @tc.steps: step3. GetNextFocusNode from bottom of first ListItemGroup.
     */
    currentIndex = 3;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 2));

    /**
     * @tc.steps: step4. GetNextFocusNode from top of second ListItemGroup.
     */
    currentIndex = 4;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 3));

    /**
     * @tc.steps: step5. GetNextFocusNode from bottom.
     */
    currentIndex = 7;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 6));
}

/**
 * @tc.name: FocusStep004
 * @tc.desc: Test GetNextFocusNode when List has ListItemGroup with HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, FocusStep004, TestSize.Level1)
{
    Create([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        CreateGroup(2, Axis::HORIZONTAL);
    });

    /**
     * @tc.steps: step1. GetNextFocusNode from left.
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_VALUE));

    /**
     * @tc.steps: step2. GetNextFocusNode from middle of first ListItemGroup.
     */
    currentIndex = 2;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 1));

    /**
     * @tc.steps: step3. GetNextFocusNode from right of first ListItemGroup.
     */
    currentIndex = 3;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 2));

    /**
     * @tc.steps: step4. GetNextFocusNode from left of second ListItemGroup.
     */
    currentIndex = 4;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 3));

    /**
     * @tc.steps: step5. GetNextFocusNode from right.
     */
    currentIndex = 7;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 6));
}

/**
 * @tc.name: FocusStep005
 * @tc.desc: Test GetNextFocusNode other condition
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, FocusStep005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. when List has unfocuseable item
     * @tc.expected: The unfocuseable item would be skiped.
     */
    Create([](ListModelNG model) { CreateItem(VIEW_LINE_NUMBER, Axis::VERTICAL); });
    GetChildFocusHub(frameNode_, 1)->SetFocusable(false);
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, 0, 2));

    /**
     * @tc.steps: step2. GetNextFocusNode func from top boundary item
     * @tc.expected: Scroll to last item
     */
    Create([](ListModelNG model) { CreateItem(TOTAL_LINE_NUMBER, Axis::VERTICAL); });
    UpdateCurrentOffset(-ITEM_HEIGHT - 1.f);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT + 1.f));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, 1, 0));
    EXPECT_TRUE(IsEqualTotalOffset(0));

    /**
     * @tc.steps: step3. GetNextFocusNode func from bottom boundary item
     * @tc.expected: Scroll to next item
     */
    Create([](ListModelNG model) { CreateItem(TOTAL_LINE_NUMBER, Axis::VERTICAL); });
    ScrollDown();
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, 8, NULL_VALUE));
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT * 2));

    /**
     * @tc.steps: step4. GetNextFocusNode func from bottom boundary item
     * @tc.expected: Scroll to next item
     */
    // change focus between different group
    const float groupHeight = ITEM_HEIGHT * GROUP_LINE_NUMBER;
    int32_t groupNumber = 3; // create scrollable List
    Create([groupNumber](ListModelNG model) { CreateGroup(groupNumber, Axis::VERTICAL); });
    EXPECT_TRUE(IsEqualTotalOffset(0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, 7, NULL_VALUE));
    EXPECT_TRUE(IsEqualTotalOffset(groupHeight));
    // change focus in same group
    groupNumber = 3; // create scrollable List
    Create([groupNumber](ListModelNG model) { CreateGroup(groupNumber, Axis::VERTICAL); });
    ScrollDown(2);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT * 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, 10, NULL_VALUE));
    EXPECT_TRUE(IsEqualTotalOffset(groupHeight / 2));

    /**
     * @tc.steps: step5. GetNextFocusNode func from top boundary item
     * @tc.expected: Scroll to next item
     */
    // change focus between different group
    groupNumber = 3; // create scrollable List
    Create([groupNumber](ListModelNG model) { CreateGroup(groupNumber, Axis::VERTICAL); });
    ScrollDown(GROUP_LINE_NUMBER);
    EXPECT_TRUE(IsEqualTotalOffset(groupHeight));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, 3, 2));
    EXPECT_FALSE(IsEqualTotalOffset(0));
    // change focus in same group
    groupNumber = 3; // create scrollable List
    Create([groupNumber](ListModelNG model) { CreateGroup(groupNumber, Axis::VERTICAL); });
    ScrollDown(3);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT * 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, 2, 1));
    EXPECT_FALSE(IsEqualTotalOffset(0));
}

/**
 * @tc.name: FocusStep006
 * @tc.desc: Test List focusing ability with lanes mode and VERTICAL.
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, FocusStep006, TestSize.Level1)
{
    Create([](ListModelNG model) {
        model.SetLanes(4);
        CreateItem(10, Axis::VERTICAL);
    });

    /**
     * @tc.steps: step1. GetNextFocusNode from left_top.
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_VALUE));

    /**
     * @tc.steps: step2. GetNextFocusNode from right_top.
     */
    currentIndex = 3;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 2));

    /**
     * @tc.steps: step3. GetNextFocusNode from left_bottom.
     */
    currentIndex = 8;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 7));

    /**
     * @tc.steps: step4. GetNextFocusNode from right_bottom.
     */
    currentIndex = 9;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 8));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 8));

    /**
     * @tc.steps: step5. GetNextFocusNode from middle.
     */
    currentIndex = 5;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 4));
}

/**
 * @tc.name: FocusStep007
 * @tc.desc: Test List focusing ability with lanes mode and HORIZONTAL.
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, FocusStep007, TestSize.Level1)
{
    Create([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        model.SetLanes(4);
        CreateItem(10, Axis::HORIZONTAL);
    });

    /**
     * @tc.steps: step1. GetNextFocusNode from left_top.
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_VALUE));

    /**
     * @tc.steps: step2. GetNextFocusNode from right_top.
     */
    currentIndex = 8;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 7));

    /**
     * @tc.steps: step3. GetNextFocusNode from left_bottom.
     */
    currentIndex = 3;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 2));

    /**
     * @tc.steps: step4. GetNextFocusNode from right_bottom.
     */
    currentIndex = 9;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 8));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 8));

    /**
     * @tc.steps: step5. GetNextFocusNode from middle.
     */
    currentIndex = 5;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 4));
}

/**
 * @tc.name: FocusStep008
 * @tc.desc: Test List focusing ability with ListItemGroup and lanes mode and VERTICAL.
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, FocusStep008, TestSize.Level1)
{
    Create([](ListModelNG model) {
        model.SetLanes(2);
        CreateGroup(2, Axis::VERTICAL);
    });

    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_VALUE));

    currentIndex = 3;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 2));

    currentIndex = 4;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 3));

    currentIndex = 7;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 6));
}

/**
 * @tc.name: FocusStep009
 * @tc.desc: Test List focusing ability with ListItemGroup and lanes mode and HORIZONTAL.
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, FocusStep009, TestSize.Level1)
{
    Create([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        model.SetLanes(2);
        CreateGroup(2, Axis::HORIZONTAL);
    });

    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_VALUE));

    currentIndex = 3;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 2));

    currentIndex = 4;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 3));

    currentIndex = 7;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 6));
}

/**
 * @tc.name: KeyEvent001
 * @tc.desc: Test list_pattern OnKeyEvent function
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, KeyEvent001, TestSize.Level1)
{
    CreateWithItem([](ListModelNG model) {});

    /**
     * @tc.steps: step1. Test other KeyEvent.
     * @tc.expected: CurrentOffset unchanged.
     */
    pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_UNKNOWN, KeyAction::UNKNOWN));
    EXPECT_TRUE(IsEqualTotalOffset(0));
    pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_UNKNOWN, KeyAction::DOWN));
    EXPECT_TRUE(IsEqualTotalOffset(0));

    /**
     * @tc.steps: step2. Test active KeyEvent.
     * @tc.expected: CurrentOffset changed.
     */
    pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_PAGE_DOWN, KeyAction::DOWN));
    EXPECT_TRUE(IsEqualTotalOffset(200.f));
    pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_PAGE_UP, KeyAction::DOWN));
    EXPECT_TRUE(IsEqualTotalOffset(0));
}

/**
 * @tc.name: MouseSelect001
 * @tc.desc: Test mouse select
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, MouseSelect001, TestSize.Level1)
{
    CreateWithItem([](ListModelNG model) { model.SetMultiSelectable(true); });

    /**
     * @tc.steps: step1. Select item(index:0)
     * @tc.expected: The item(index:0) is selected
     */
    MouseSelect(Offset(0.f, 0.f), Offset(LIST_WIDTH, 50.f));
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 0)->IsSelected());

    /**
     * @tc.steps: step2. Select from selected item(index:0) to item(index:1)
     * @tc.expected: Selected items unchanged, item(index:0) is selected, item(index:1) is unselected
     */
    MouseSelect(Offset(0.f, 50.f), Offset(LIST_WIDTH, 150.f));
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 0)->IsSelected());
    EXPECT_FALSE(GetChildPattern<ListItemPattern>(frameNode_, 1)->IsSelected());

    /**
     * @tc.steps: step3. Select from unselected item(index:1) to item(index:1)
     * @tc.expected: Selected items changed, item(index:0) is unselected, item(index:1) is selected
     */
    MouseSelect(Offset(0.f, 150.f), Offset(LIST_WIDTH, 170.f));
    EXPECT_FALSE(GetChildPattern<ListItemPattern>(frameNode_, 0)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 1)->IsSelected());

    /**
     * @tc.steps: step4. Click selected item(index:1)
     * @tc.expected: Selected items unchanged, item(index:1) is selected
     */
    MouseSelect(Offset(LIST_WIDTH / 2, 150.f), Offset(LIST_WIDTH / 2, 150.f));
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 1)->IsSelected());

    /**
     * @tc.steps: step5. Click unselected items(index:0)
     * @tc.expected: Each item not selected, item(index:0) item(index:1) are unselected
     */
    MouseSelect(Offset(LIST_WIDTH / 2, 50.f), Offset(LIST_WIDTH / 2, 50.f));
    EXPECT_FALSE(GetChildPattern<ListItemPattern>(frameNode_, 0)->IsSelected());
    EXPECT_FALSE(GetChildPattern<ListItemPattern>(frameNode_, 1)->IsSelected());
}

/**
 * @tc.name: MouseSelect002
 * @tc.desc: Test mouse box selection in different direction and in VERTICAL layout
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, MouseSelect002, TestSize.Level1)
{
    /**
     * @tc.cases: Select from the item(index:1 LEFT_TOP) to the item(index:2 RIGHT_BOTTOM).
     * @tc.expected: The items(index:1,2) are selected.
     */
    CreateWithItem([](ListModelNG model) { model.SetMultiSelectable(true); });
    MouseSelect(LEFT_TOP, RIGHT_BOTTOM);
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 1)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 2)->IsSelected());
}

/**
 * @tc.name: MouseSelect003
 * @tc.desc: Test mouse box selection in different direction and in HORIZONTAL layout
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, MouseSelect003, TestSize.Level1)
{
    /**
     * @tc.cases: Select from the item(index:6 RIGHT_TOP) to the item(index:1 LEFT_BOTTOM).
     * @tc.expected: The items(index:1,2,3,4,5,6) are selected.
     */
    Create([](ListModelNG model) {
        model.SetMultiSelectable(true);
        model.SetListDirection(Axis::HORIZONTAL);
        CreateItem(VIEW_LINE_NUMBER, Axis::HORIZONTAL);
    });
    MouseSelect(RIGHT_TOP, LEFT_BOTTOM);
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 1)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 2)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 3)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 4)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 5)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 6)->IsSelected());
}

/**
 * @tc.name: MouseSelect004
 * @tc.desc: Test mouse box selection in different direction and in two lanes layout
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, MouseSelect004, TestSize.Level1)
{
    /**
     * @tc.cases: Select from the item(index:4 LEFT_BOTTOM) to the item(index:3 RIGHT_TOP).
     * @tc.expected: The items(index:2,3,4,5) are selected.
     */
    Create([](ListModelNG model) {
        model.SetLanes(2);
        CreateItem(10, Axis::VERTICAL);
    });
    MouseSelect(LEFT_BOTTOM, RIGHT_TOP);
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 2)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 3)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 4)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 5)->IsSelected());
}

/**
 * @tc.name: MouseSelect005
 * @tc.desc: Test mouse box selection in different direction and in itemGroup lanes layout and between two itemGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, MouseSelect005, TestSize.Level1)
{
    /**
     * @tc.cases: Select from the item(index:5 RIGHT_BOTTOM) to the item(index:2 LEFT_TOP).
     * @tc.expected: The items(index:0,1,2,3,4,5) are selected.
     */
    Create([](ListModelNG model) {
        model.SetLanes(2);
        CreateGroup(2, Axis::VERTICAL);
    });
    MouseSelect(RIGHT_BOTTOM, LEFT_TOP);
    std::vector<RefPtr<FrameNode>> listItems = GetALLItem(); // flat items
    EXPECT_TRUE(listItems[2]->GetPattern<ListItemPattern>()->IsSelected());
    EXPECT_TRUE(listItems[3]->GetPattern<ListItemPattern>()->IsSelected());
    EXPECT_TRUE(listItems[4]->GetPattern<ListItemPattern>()->IsSelected());
    EXPECT_TRUE(listItems[5]->GetPattern<ListItemPattern>()->IsSelected());
}

/**
 * @tc.name: MouseSelect006
 * @tc.desc: Test listItem selectable property and onSelect callback
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, MouseSelect006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set item(index:1) unselectable, set item(index:2) unenabled,
     *                   set selectCallback for item(index:5)
     */
    CreateWithItem([](ListModelNG model) { model.SetMultiSelectable(true); });
    bool isSixthItemSelected = false;
    auto selectCallback = [&isSixthItemSelected](bool) { isSixthItemSelected = true; };
    GetChildPattern<ListItemPattern>(frameNode_, 1)->SetSelectable(false);
    GetChildEventHub<ListItemEventHub>(frameNode_, 2)->SetEnabled(false);
    GetChildEventHub<ListItemEventHub>(frameNode_, 5)->SetOnSelect(std::move(selectCallback));

    /**
     * @tc.steps: step2. Select zone, include items(index:1,2,3,4,5).
     * @tc.expected: The item(index:1) is not selected, item(index:2) is selected,
     *               item(index:5) is selected, selectCallback is called.
     */
    MouseSelect(Offset(120.f, 150.f), Offset(360.f, 550.f));
    EXPECT_FALSE(GetChildPattern<ListItemPattern>(frameNode_, 1)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 2)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 5)->IsSelected());
    EXPECT_TRUE(isSixthItemSelected);
}

/**
 * @tc.name: MouseSelect007
 * @tc.desc: Test select in other condition
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, MouseSelect007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Move distance < DEFAULT_PAN_DISTANCE
     * @tc.expected: The item is not Selected
     */
    CreateWithItem([](ListModelNG model) { model.SetMultiSelectable(true); });
    MouseSelect(Offset(0.f, 0.f), Offset(1.f, 1.f));
    EXPECT_FALSE(GetChildPattern<ListItemPattern>(frameNode_, 0)->IsSelected());
}

/**
 * @tc.name: AccessibilityProperty001
 * @tc.desc: Test List AccessibilityProperty func
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, AccessibilityProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Scrollable List
     */
    CreateWithItem([](ListModelNG model) {});
    EXPECT_TRUE(accessibilityProperty_->IsScrollable());
    EXPECT_EQ(accessibilityProperty_->GetBeginIndex(), 0);
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), VIEW_LINE_NUMBER - 1);
    EXPECT_EQ(accessibilityProperty_->GetCollectionItemCounts(), TOTAL_LINE_NUMBER);

    /**
     * @tc.steps: step2. scroll to second item
     */
    ScrollDown();
    EXPECT_EQ(accessibilityProperty_->GetBeginIndex(), 1);
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), VIEW_LINE_NUMBER);

    /**
     * @tc.steps: step3. unScrollable List
     */
    Create([](ListModelNG model) { CreateItem(VIEW_LINE_NUMBER); });
    EXPECT_FALSE(accessibilityProperty_->IsScrollable());
    EXPECT_EQ(accessibilityProperty_->GetBeginIndex(), 0);
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), VIEW_LINE_NUMBER - 1);
    EXPECT_EQ(accessibilityProperty_->GetCollectionItemCounts(), VIEW_LINE_NUMBER);
}

/**
 * @tc.name: AccessibilityProperty002
 * @tc.desc: Test List SetSpecificSupportAction when scroll to middle
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, AccessibilityProperty002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Scroll to Top.
     */
    CreateWithItem([](ListModelNG model) {});
    accessibilityProperty_->ResetSupportAction();
    uint64_t exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions);

    /**
     * @tc.steps: step2. Scroll to middle.
     */
    ScrollDown();
    accessibilityProperty_->ResetSupportAction();
    exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions);

    /**
     * @tc.steps: step3. Scroll to bottom.
     */
    ScrollDown();
    accessibilityProperty_->ResetSupportAction();
    exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions);

    /**
     * @tc.steps: step4. UnScrollable List.
     */
    Create([](ListModelNG model) { CreateItem(VIEW_LINE_NUMBER); });
    accessibilityProperty_->ResetSupportAction();
    EXPECT_EQ(GetActions(accessibilityProperty_), 0);
}

/**
 * @tc.name: AccessibilityProperty003
 * @tc.desc: Test ListItem AccessibilityProperty func
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, AccessibilityProperty003, TestSize.Level1)
{
    CreateWithItem([](ListModelNG model) {});
    auto listItem = GetChildFrameNode(frameNode_, 0);
    auto itemAccessibilityProperty = listItem->GetAccessibilityProperty<ListItemAccessibilityProperty>();
    EXPECT_FALSE(itemAccessibilityProperty->IsSelected());

    itemAccessibilityProperty->ResetSupportAction();
    uint64_t exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SELECT);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_CLEAR_SELECTION);
    EXPECT_EQ(GetActions(itemAccessibilityProperty), exptectActions);
}

/**
 * @tc.name: AccessibilityProperty004
 * @tc.desc: Test ListItemGroup AccessibilityProperty func
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, AccessibilityProperty004, TestSize.Level1)
{
    Create(
        [](ListModelNG model) { CreateGroupWithSetting(GROUP_NUMBER, Axis::VERTICAL, V2::ListItemGroupStyle::NONE); });
    auto groupAccessibilityProperty =
        GetChildFrameNode(frameNode_, 0)->GetAccessibilityProperty<ListItemGroupAccessibilityProperty>();
    EXPECT_EQ(groupAccessibilityProperty->GetBeginIndex(), 0);
    EXPECT_EQ(groupAccessibilityProperty->GetEndIndex(), 3);

    groupAccessibilityProperty =
        GetChildFrameNode(frameNode_, 3)->GetAccessibilityProperty<ListItemGroupAccessibilityProperty>();
    EXPECT_EQ(groupAccessibilityProperty->GetBeginIndex(), -1);
    EXPECT_EQ(groupAccessibilityProperty->GetEndIndex(), -1);
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: ListItem Accessibility PerformAction test Select and ClearSelection.
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, PerformActionTest001, TestSize.Level1)
{
    Create([](ListModelNG model) { CreateItem(VIEW_LINE_NUMBER); });
    auto listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, 0);
    auto listItemAccessibilityProperty = GetChildAccessibilityProperty<ListItemAccessibilityProperty>(frameNode_, 0);

    /**
     * @tc.steps: step1. When listItem is unSelectable
     * @tc.expected: can not be selected
     */
    listItemPattern->SetSelectable(false);
    listItemAccessibilityProperty->ActActionSelect();
    EXPECT_FALSE(listItemPattern->IsSelected());
    listItemAccessibilityProperty->ActActionClearSelection();
    EXPECT_FALSE(listItemPattern->IsSelected());

    /**
     * @tc.steps: step2. When listItem is Selectable
     * @tc.expected: can be selected
     */
    listItemPattern->SetSelectable(true);
    listItemAccessibilityProperty->ActActionSelect();
    EXPECT_TRUE(listItemPattern->IsSelected());
    listItemAccessibilityProperty->ActActionClearSelection();
    EXPECT_FALSE(listItemPattern->IsSelected());
}

/**
 * @tc.name: PerformActionTest002
 * @tc.desc: List Accessibility PerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, PerformActionTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. When list is not Scrollable
     * @tc.expected: can not scrollpage
     */
    Create([](ListModelNG model) { CreateItem(VIEW_LINE_NUMBER); });
    accessibilityProperty_->ActActionScrollForward();
    EXPECT_TRUE(IsEqualTotalOffset(0));
    accessibilityProperty_->ActActionScrollBackward();
    EXPECT_TRUE(IsEqualTotalOffset(0));

    /**
     * @tc.steps: step2. When list is Scrollable
     * @tc.expected: can scrollpage
     */
    CreateWithItem([](ListModelNG model) {});
    accessibilityProperty_->ActActionScrollForward();
    EXPECT_TRUE(IsEqualTotalOffset(200.f));
    accessibilityProperty_->ActActionScrollBackward();
    EXPECT_TRUE(IsEqualTotalOffset(0));
}

/**
 * @tc.name: FRCCallback001
 * @tc.desc: Test FRC callback
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, FRCCallback001, TestSize.Level1)
{
    Create([](ListModelNG model) {});
    // CalcExpectedFrameRate will be called
    pattern_->NotifyFRCSceneInfo("", 0.0f, SceneStatus::START);
}

/**
 * @tc.name: EventHub001
 * @tc.desc: Test Event hub
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, EventHub001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. EXPECT_CALL DrawFrameNode, HandleOnItemDragStart will trigger it
     */
    auto mockDragWindow = MockDragWindow::CreateDragWindow("", 0, 0, 0, 0);
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(mockDragWindow)), DrawFrameNode(_)).Times(2);

    /**
     * @tc.steps: step2. Run List GetDragExtraParams func.
     * @tc.expected: Would call pattern->GetItemIndexByPosition
     */
    auto onItemDragStart = [](const ItemDragInfo&, int32_t) {
        auto dragItem = AceType::MakeRefPtr<FrameNode>("test", 0, AceType::MakeRefPtr<Pattern>());
        return AceType::DynamicCast<UINode>(dragItem);
    };
    CreateWithItem([onItemDragStart](ListModelNG model) { model.SetOnItemDragStart(onItemDragStart); });
    auto jsonStr = eventHub_->GetDragExtraParams("", Point(0, 250), DragEventType::MOVE);
    EXPECT_EQ(jsonStr, "{\"insertIndex\":2}");

    /**
     * @tc.steps: step3. HandleOnItemDrag to end
     */
    GestureEvent info;
    info.SetGlobalPoint(Point(0, 250.f));
    eventHub_->HandleOnItemDragStart(info);
    EXPECT_EQ(eventHub_->draggedIndex_, 2);
    eventHub_->HandleOnItemDragUpdate(info);
    eventHub_->HandleOnItemDragEnd(info);
    EXPECT_EQ(eventHub_->draggedIndex_, 0);

    /**
     * @tc.steps: step3. HandleOnItemDrag to cancel
     */
    eventHub_->HandleOnItemDragStart(info);
    EXPECT_EQ(eventHub_->draggedIndex_, 2);
    eventHub_->HandleOnItemDragUpdate(info);
    eventHub_->HandleOnItemDragCancel();
    EXPECT_EQ(eventHub_->draggedIndex_, 0);
}

/**
 * @tc.name: EventHub002
 * @tc.desc: Test ListItem Event hub
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, EventHub002, TestSize.Level1)
{
    CreateWithItem([](ListModelNG model) {});
    auto itemEventHub = GetChildFrameNode(frameNode_, 0)->GetEventHub<ListItemEventHub>();
    auto jsonStr = itemEventHub->GetDragExtraParams("", Point(0, 250.f), DragEventType::START);
    EXPECT_EQ(jsonStr, "{\"selectedIndex\":0}");
    jsonStr = itemEventHub->GetDragExtraParams("info", Point(0, 250.f), DragEventType::MOVE);
    EXPECT_EQ(jsonStr, "{\"extraInfo\":\"info\"}");
}

/**
 * @tc.name: ListSelectForCardModeTest001
 * @tc.desc: Test the card mode for select.
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, ListSelectForCardModeTest001, TestSize.Level1)
{
    Create([](ListModelNG model) {
        model.SetMultiSelectable(true);
        ListItemGroupModelNG groupModel;
        groupModel.Create(V2::ListItemGroupStyle::CARD);
        CreateItem(GROUP_LINE_NUMBER, Axis::VERTICAL, V2::ListItemStyle::CARD);
        ViewStackProcessor::GetInstance()->Pop();
    });
    RefPtr<FrameNode> group = GetChildFrameNode(frameNode_, 0);

    /**
     * @tc.steps: step1. Select zone.
     * @tc.expected: The 1st and 2nd items are selected.
     */
    MouseSelect(Offset(0.f, 0.f), Offset(200.f, 100.f));
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(group, 0)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(group, 1)->IsSelected());
    pattern_->ClearMultiSelect();

    /**
     * @tc.steps: step2. Change select zone.
     * @tc.expected: Selected items changed.
     */
    MouseSelect(Offset(0.f, 200.f), Offset(200.f, 300.f));
    EXPECT_FALSE(GetChildPattern<ListItemPattern>(group, 0)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(group, 1)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(group, 2)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(group, 3)->IsSelected());
    pattern_->ClearMultiSelect();

    /**
     * @tc.steps: step3. Click first item.
     * @tc.expected: Each item not selected.
     */
    MouseSelect(Offset(0.f, 10.f), Offset(0.f, 10.f));
    for (int32_t index = 0; index < GROUP_LINE_NUMBER; index++) {
        EXPECT_FALSE(GetChildPattern<ListItemPattern>(group, index)->IsSelected()) << "Index: " << index;
    }
}

/**
 * @tc.name: ListSelectForCardModeTest002
 * @tc.desc: Test the card mode for select.
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, ListSelectForCardModeTest002, TestSize.Level1)
{
    const Offset LEFT_TOP = Offset(0.f, 0.f);
    const Offset LEFT_BOTTOM = Offset(0.f, 150.f);
    const Offset RIGHT_TOP = Offset(360.f, 0.f);
    const Offset RIGHT_BOTTOM = Offset(360.f, 150.f);
    Create([](ListModelNG model) {
        model.SetMultiSelectable(true);
        ListItemGroupModelNG groupModel;
        groupModel.Create(V2::ListItemGroupStyle::CARD);
        CreateItem(GROUP_LINE_NUMBER, Axis::VERTICAL, V2::ListItemStyle::CARD);
        ViewStackProcessor::GetInstance()->Pop();
    });
    RefPtr<FrameNode> group = GetChildFrameNode(frameNode_, 0);

    /**
     * @tc.steps: step1. Select from LEFT_TOP to RIGHT_BOTTOM
     */
    MouseSelect(LEFT_TOP, RIGHT_BOTTOM);
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(group, 0)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(group, 1)->IsSelected());
    pattern_->ClearMultiSelect();

    /**
     * @tc.steps: step2. Select from RIGHT_TOP to LEFT_BOTTOM
     */
    MouseSelect(RIGHT_TOP, LEFT_BOTTOM);
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(group, 0)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(group, 1)->IsSelected());
    pattern_->ClearMultiSelect();

    /**
     * @tc.steps: step3. Select from LEFT_BOTTOM to RIGHT_TOP
     */
    MouseSelect(LEFT_BOTTOM, RIGHT_TOP);
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(group, 0)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(group, 1)->IsSelected());
    pattern_->ClearMultiSelect();

    /**
     * @tc.steps: step4. Select from RIGHT_BOTTOM to LEFT_TOP
     */
    MouseSelect(RIGHT_BOTTOM, LEFT_TOP);
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(group, 0)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(group, 1)->IsSelected());
}

/**
 * @tc.name: ListSelectForCardModeTest003
 * @tc.desc: Test the card mode for select when the 'selectable' of listItem  is false.
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, ListSelectForCardModeTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List/ListItemGroup/ListItem and ListItem set to unselectable.
     * @tc.expected: step1. create a card style ListItemGroup success.
     */
    Create([](ListModelNG model) {
        model.SetMultiSelectable(true);
        ListItemGroupModelNG groupModel;
        groupModel.Create(V2::ListItemGroupStyle::CARD);
        CreateItem(5, Axis::VERTICAL, V2::ListItemStyle::CARD);
        ViewStackProcessor::GetInstance()->Pop();
    });
    auto group = GetChildFrameNode(frameNode_, 0);

    bool isFifthItemSelected = false;
    auto selectCallback = [&isFifthItemSelected](bool) { isFifthItemSelected = true; };
    GetChildPattern<ListItemPattern>(group, 3)->SetSelectable(false);
    GetChildFrameNode(group, 4)->GetEventHub<ListItemEventHub>()->SetOnSelect(std::move(selectCallback));

    /**
     * @tc.steps: step2. Select zone.
     * @tc.expected: The 4th item is not selected but 5th item is selected.
     */
    MouseSelect(Offset(0.f, 350.f), Offset(360.f, 450.f));
    EXPECT_FALSE(GetChildPattern<ListItemPattern>(group, 3)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(group, 4)->IsSelected());
    EXPECT_TRUE(isFifthItemSelected);
}

/**
 * @tc.name: ListPattern_Distributed001
 * @tc.desc: Test the distributed capability of List.
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, ListPattern_Distributed001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init List node
     */
    CreateWithItem([](ListModelNG model) {});

    /**
     * @tc.steps: step2. get pattern .
     * @tc.expected: function ProvideRestoreInfo is called.
     */
    pattern_->startIndex_ = 1;
    std::string ret = pattern_->ProvideRestoreInfo();

    /**
     * @tc.steps: step3. function OnRestoreInfo is called.
     * @tc.expected: Passing JSON format.
     */
    pattern_->OnRestoreInfo(ret);
    EXPECT_EQ(pattern_->jumpIndex_, 1);
}
} // namespace OHOS::Ace::NG
