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

#include "grid_test_ng.h"
#include "test/mock/core/animation/mock_animation_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/unittest/core/pattern/scrollable/scrollable_test_utils.h"

#include "core/components_ng/pattern/button/button_model_ng.h"
#include "core/components_ng/pattern/grid/grid_item_pattern.h"

namespace OHOS::Ace::NG {

namespace {
const Offset LEFT_TOP = Offset(ITEM_WIDTH * 0.5, ITEM_HEIGHT * 0.5);     // (60, 100)
const Offset LEFT_BOTTOM = Offset(ITEM_WIDTH * 0.5, ITEM_HEIGHT * 1.5);  // (60, 300)
const Offset RIGHT_TOP = Offset(ITEM_WIDTH * 1.5, ITEM_HEIGHT * 0.5);    // (180, 100)
const Offset RIGHT_BOTTOM = Offset(ITEM_WIDTH * 1.5, ITEM_HEIGHT * 1.5); // (180, 300)
void OnItemDragStartEvent(const ItemDragInfo&, int32_t)
{
    ButtonModelNG buttonModelNG;
    buttonModelNG.CreateWithLabel("label");
};
} // namespace

class GridCommonTestNg : public GridTestNg {
public:
    void MouseSelect(Offset start, Offset end);
    int32_t FindFocusNodeIndex(RefPtr<FocusHub>& focusNode);
    AssertionResult IsEqualNextFocusNode(FocusStep step, int32_t currentIndex, int32_t expectNextIndex);
};

void GridCommonTestNg::MouseSelect(Offset start, Offset end)
{
    GestureEvent info;
    info.SetInputEventType(InputEventType::MOUSE_BUTTON);
    info.SetLocalLocation(start);
    info.SetGlobalLocation(start);
    info.SetRawGlobalLocation(start);
    pattern_->HandleDragStart(info);
    if (start != end) {
        info.SetLocalLocation(end);
        info.SetGlobalLocation(end);
        info.SetRawGlobalLocation(end);
        pattern_->HandleDragUpdate(info);
    }
    pattern_->HandleDragEnd();
}

int32_t GridCommonTestNg::FindFocusNodeIndex(RefPtr<FocusHub>& focusNode)
{
    auto children = frameNode_->GetChildren();
    int32_t size = static_cast<int32_t>(children.size());
    for (int32_t index = 0; index < size; index++) {
        if (focusNode == GetChildFocusHub(frameNode_, index)) {
            return index;
        }
    }
    return NULL_VALUE;
}

AssertionResult GridCommonTestNg::IsEqualNextFocusNode(FocusStep step, int32_t currentIndex, int32_t expectNextIndex)
{
    RefPtr<FocusHub> currentFocusNode = GetChildFocusHub(frameNode_, currentIndex);
    currentFocusNode->RequestFocusImmediately();
    RefPtr<FocusHub> nextFocusNode = pattern_->GetNextFocusNode(step, currentFocusNode).Upgrade();
    if (expectNextIndex != NULL_VALUE && nextFocusNode == nullptr) {
        return AssertionFailure() << "Next FocusNode is null";
    }
    int32_t nextIndex = FindFocusNodeIndex(nextFocusNode);
    return IsEqual(nextIndex, expectNextIndex);
}

/**
 * @tc.name: KeyEvent001
 * @tc.desc: Test OnKeyEvent func, will trigger ScrollPage
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, KeyEvent001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(20);
    CreateDone(frameNode_);

    /**
     * @tc.cases: Test invalid args KeyAction::UNKNOWN.
     * @tc.expected: No scroll
     */
    pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_UNKNOWN, KeyAction::UNKNOWN));
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 0.f);

    /**
     * @tc.cases: Test invalid args KeyAction::DOWN KeyCode::KEY_UNKNOWN
     * @tc.expected: No scroll
     */
    pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_PAGE_UP, KeyAction::DOWN));
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 0.f);
}

/**
 * @tc.name: KeyEvent002
 * @tc.desc: Test OnKeyEvent func, will trigger ScrollPage
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, KeyEvent002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(20);
    CreateDone(frameNode_);

    /**
     * @tc.cases: KeyAction::DOWN KeyCode::KEY_PAGE_DOWN.
     * @tc.expected: Page jump down with Grid height.
     */
    pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_PAGE_DOWN, KeyAction::DOWN));
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 200.f);

    /**
     * @tc.cases: KeyAction::DOWN KeyCode::KEY_PAGE_UP.
     * @tc.expected: Page jump up with Grid height.
     */
    pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_PAGE_UP, KeyAction::DOWN));
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 0.f);
}

/**
 * @tc.name: KeyEvent003
 * @tc.desc: Test HandleDirectionKey func
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, KeyEvent003, TestSize.Level1)
{
    /**
     * @tc.cases: Test HandleDirectionKey
     * @tc.expected: Only KEY_DPAD_UP/KEY_DPAD_DOWN will return true
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(20);
    CreateDone(frameNode_);
    EXPECT_FALSE(pattern_->HandleDirectionKey(KeyCode::KEY_UNKNOWN));
    EXPECT_TRUE(pattern_->HandleDirectionKey(KeyCode::KEY_DPAD_UP));
    EXPECT_TRUE(pattern_->HandleDirectionKey(KeyCode::KEY_DPAD_DOWN));
}

/**
 * @tc.name: MouseSelect001
 * @tc.desc: Test mouse select
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, MouseSelect001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetMultiSelectable(true);
    CreateFixedItems(8);
    CreateDone(frameNode_);

    /**
     * @tc.steps: step1. Select item(index:0)
     * @tc.expected: The item(index:0) is selected
     */
    MouseSelect(Offset(0.f, 0.f), Offset(10.f, 10.f));
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 0)->IsSelected());

    /**
     * @tc.steps: step2. Select from selected item(index:0) to item(index:1)
     * @tc.expected: Selected items unchanged, item(index:0) is selected, item(index:1) is unselected
     */
    MouseSelect(Offset(0.f, 0.f), Offset(ITEM_WIDTH * 1.5, 10.f));
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 0)->IsSelected());
    EXPECT_FALSE(GetChildPattern<GridItemPattern>(frameNode_, 1)->IsSelected());

    /**
     * @tc.steps: step3. Select from unselected item(index:1) to item(index:1)
     * @tc.expected: Selected items changed, item(index:0) is unselected, item(index:1) is selected
     */
    MouseSelect(Offset(ITEM_WIDTH * 1.5, 0.f), Offset(ITEM_WIDTH * 1.5 + 10.f, 10.f));
    EXPECT_FALSE(GetChildPattern<GridItemPattern>(frameNode_, 0)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 1)->IsSelected());

    /**
     * @tc.steps: step4. Click selected item(index:1)
     * @tc.expected: Selected items unchanged, item(index:1) is selected
     */
    MouseSelect(Offset(ITEM_WIDTH * 1.5, 10.f), Offset(ITEM_WIDTH * 1.5, 10.f));
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 1)->IsSelected());

    /**
     * @tc.steps: step5. Click unselected items(index:0)
     * @tc.expected: Each item not selected, item(index:0) item(index:1) are unselected
     */
    MouseSelect(Offset(10.f, 10.f), Offset(10.f, 10.f));
    EXPECT_FALSE(GetChildPattern<GridItemPattern>(frameNode_, 0)->IsSelected());
    EXPECT_FALSE(GetChildPattern<GridItemPattern>(frameNode_, 1)->IsSelected());
}

/**
 * @tc.name: MouseSelect002
 * @tc.desc: Test mouse box selection in different direction and in VERTICAL layout
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, MouseSelect002, TestSize.Level1)
{
    /**
     * @tc.cases: Select from the item(index:0 LEFT_TOP) to the item(index:5 RIGHT_BOTTOM).
     * @tc.expected: The items(index:0,1,4,5) are selected.
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetMultiSelectable(true);
    CreateFixedItems(8);
    CreateDone(frameNode_);
    MouseSelect(LEFT_TOP, RIGHT_BOTTOM);
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 0)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 1)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 4)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 5)->IsSelected());
}

/**
 * @tc.name: MouseSelect003
 * @tc.desc: Test mouse box selection in different direction and in HORIZONTAL layout
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, MouseSelect003, TestSize.Level1)
{
    /**
     * @tc.cases: Select from the item(index:4 RIGHT_TOP) to the item(index:1 LEFT_BOTTOM).
     * @tc.expected: The items(index:0,1,4,5) are selected.
     */
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr 1fr 1fr");
    model.SetMultiSelectable(true);
    CreateFixedItems(8);
    CreateDone(frameNode_);
    MouseSelect(RIGHT_TOP, LEFT_BOTTOM);
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 0)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 1)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 4)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 5)->IsSelected());
}

/**
 * @tc.name: MouseSelect004
 * @tc.desc: Test mouse box selection in different direction and in BigItem layout
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, MouseSelect004, TestSize.Level1)
{
    /**
     * @tc.cases: Select from the item(index:3 LEFT_BOTTOM) to the item(index:1 RIGHT_TOP).
     * @tc.expected: The items(index:0,1,3) are selected.
     */
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr 1fr 1fr");
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateBigItem(1, 2, 1, 2);
    CreateBigItem(NULL_VALUE, NULL_VALUE, 1, 3);
    CreateBigItem(1, 3, NULL_VALUE, NULL_VALUE);
    CreateGridItems(7);
    CreateDone(frameNode_);
    MouseSelect(LEFT_BOTTOM, RIGHT_TOP);
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 0)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 1)->IsSelected());
    EXPECT_FALSE(GetChildPattern<GridItemPattern>(frameNode_, 2)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 3)->IsSelected());
}

/**
 * @tc.name: MouseSelect005
 * @tc.desc: Test mouse box selection in different direction and in LayoutOptions layout
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, MouseSelect005, TestSize.Level1)
{
    /**
     * @tc.cases: Select from the item(index:1 RIGHT_BOTTOM) to the item(index:0 LEFT_TOP).
     * @tc.expected: The items(index:0,1) are selected.
     */
    GridLayoutOptions option;
    option.irregularIndexes = { 6, 1, 3, 4, 5, 0 };
    GetSizeByIndex onGetIrregularSizeByIndex = [](int32_t index) {
        if (index == 3) {
            return GridItemSize { 1, 2 };
        }
        return GridItemSize { 1, 4 };
    };
    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetLayoutOptions(option);
    CreateFixedItems(10);
    CreateDone(frameNode_);
    MouseSelect(RIGHT_BOTTOM, LEFT_TOP);
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 0)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 1)->IsSelected());
    EXPECT_FALSE(GetChildPattern<GridItemPattern>(frameNode_, 2)->IsSelected());
    EXPECT_FALSE(GetChildPattern<GridItemPattern>(frameNode_, 3)->IsSelected());
}

/**
 * @tc.name: MouseSelect006
 * @tc.desc: Test gridItem selectable property and onSelect callback
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, MouseSelect006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set item(index:1) unselectable, set item(index:2) unenabled,
     *                   set selectCallback for item(index:5)
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetMultiSelectable(true);
    CreateFixedItems(10);
    CreateDone(frameNode_);
    bool isSixthItemSelected = false;
    auto selectCallback = [&isSixthItemSelected](bool) { isSixthItemSelected = true; };
    GetChildPattern<GridItemPattern>(frameNode_, 1)->SetSelectable(false);
    GetChildEventHub<GridItemEventHub>(frameNode_, 2)->SetEnabled(false);
    GetChildEventHub<GridItemEventHub>(frameNode_, 5)->SetOnSelect(std::move(selectCallback));
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Select zone, include items(index:1,2,5,6).
     * @tc.expected: The item(index:1) and item(index:2) are not selected, item(index:5) is selected,
     *               selectCallback is called.
     */
    MouseSelect(Offset(ITEM_WIDTH * 1.5, ITEM_HEIGHT * 1.5), Offset(ITEM_WIDTH * 2.5, ITEM_HEIGHT * 1.5));
    EXPECT_FALSE(GetChildPattern<GridItemPattern>(frameNode_, 1)->IsSelected());
    EXPECT_FALSE(GetChildPattern<GridItemPattern>(frameNode_, 2)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 5)->IsSelected());
    EXPECT_TRUE(isSixthItemSelected);
}

/**
 * @tc.name: MouseSelect007
 * @tc.desc: Test select in other condition
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, MouseSelect007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Move distance < DEFAULT_PAN_DISTANCE
     * @tc.expected: The item is not Selected
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetMultiSelectable(true);
    CreateFixedItems(8);
    CreateDone(frameNode_);
    MouseSelect(Offset(0.f, 0.f), Offset(1.f, 1.f));
    EXPECT_FALSE(GetChildPattern<GridItemPattern>(frameNode_, 0)->IsSelected());
}

/**
 * @tc.name: HandleDrag001
 * @tc.desc: Verify drag func
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, HandleDrag001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetEditable(true);
    model.SetOnItemDragStart(std::move(OnItemDragStartEvent));
    CreateFixedItems(8);
    CreateDone(frameNode_);
    auto gestureEventHub = eventHub_->GetOrCreateGestureEventHub();
    auto userCallback = gestureEventHub->dragEventActuator_->userCallback_;
    auto HandleOnItemDragStart = userCallback->GetActionStartEventFunc();
    auto HandleOnItemDragUpdate = userCallback->GetActionUpdateEventFunc();
    auto HandleOnItemDragEnd = userCallback->GetActionEndEventFunc();
    auto HandleOnItemDragCancel = userCallback->GetActionCancelEventFunc();
    GestureEvent info;
    auto secondItem = GetChildFrameNode(frameNode_, 1);
    Point secondItemPoint = Point(ITEM_WIDTH * 1.5, ITEM_HEIGHT / 2);
    info.SetGlobalPoint(secondItemPoint);

    /**
     * @tc.steps: step1. HandleDrag item(index:1)
     * @tc.expected: Verify some values of the drag.
     */
    HandleOnItemDragStart(info);
    EXPECT_EQ(eventHub_->draggedIndex_, 1);
    ASSERT_NE(eventHub_->dragDropProxy_, nullptr);
    EXPECT_EQ(eventHub_->draggingItem_, secondItem);
    HandleOnItemDragUpdate(info);
    HandleOnItemDragEnd(info);
    EXPECT_EQ(eventHub_->draggedIndex_, 0);
    EXPECT_EQ(eventHub_->dragDropProxy_, nullptr);
    EXPECT_EQ(eventHub_->draggingItem_, nullptr);

    /**
     * @tc.steps: step1. HandleDrag to cancel
     * @tc.expected: Verify some values of the drag.
     */
    HandleOnItemDragStart(info);
    HandleOnItemDragUpdate(info);
    HandleOnItemDragCancel();
    EXPECT_EQ(eventHub_->draggedIndex_, 0);
    EXPECT_EQ(eventHub_->dragDropProxy_, nullptr);
    EXPECT_EQ(eventHub_->draggingItem_, nullptr);
}

/**
 * @tc.name: HandleDrag002
 * @tc.desc: Verify drag func with Editable false
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, HandleDrag002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetEditable(false); // set false
    model.SetOnItemDragStart(OnItemDragStartEvent);
    CreateFixedItems(8);
    CreateDone(frameNode_);
    GestureEvent info;
    Point secondItemPoint = Point(ITEM_WIDTH * 1.5, ITEM_HEIGHT / 2);
    info.SetGlobalPoint(secondItemPoint);

    /**
     * @tc.steps: step1. Trigger HandleOnItemDragStart, HandleOnItemDragUpdate, HandleOnItemDragEnd.
     * @tc.expected: Do nothing
     */
    eventHub_->HandleOnItemDragStart(info);
    EXPECT_EQ(eventHub_->draggedIndex_, 0);
    EXPECT_EQ(eventHub_->dragDropProxy_, nullptr);
    EXPECT_EQ(eventHub_->draggingItem_, nullptr);
    eventHub_->HandleOnItemDragUpdate(info);
    eventHub_->HandleOnItemDragEnd(info);
    EXPECT_EQ(eventHub_->draggedIndex_, 0);
    EXPECT_EQ(eventHub_->dragDropProxy_, nullptr);
    EXPECT_EQ(eventHub_->draggingItem_, nullptr);

    /**
     * @tc.steps: step2. Trigger HandleOnItemDragStart, HandleOnItemDragUpdate, HandleOnItemDragCancel.
     * @tc.expected: Do nothing
     */
    eventHub_->HandleOnItemDragStart(info);
    eventHub_->HandleOnItemDragUpdate(info);
    eventHub_->HandleOnItemDragCancel();
    EXPECT_EQ(eventHub_->draggedIndex_, 0);
    EXPECT_EQ(eventHub_->dragDropProxy_, nullptr);
    EXPECT_EQ(eventHub_->draggingItem_, nullptr);
}

/**
 * @tc.name: FireDrag001
 * @tc.desc: Verify drag func
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, FireDrag001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetEditable(true);
    model.SetSupportAnimation(true);
    CreateBigColItem(2, 3);
    CreateBigColItem(0, 2);
    CreateBigColItem(2, 1);
    CreateFixedItems(8);
    CreateDone(frameNode_);

    GestureEvent info;
    Point globalPoint = Point(270.f, 50.f);
    info.SetGlobalPoint(globalPoint);
    eventHub_->HandleOnItemDragStart(info);

    /**
     * @tc.steps: step1. Drag 1st item to out of Grid.
     * @tc.expected: GetOriginalIndex return number of GridItem.
     */
    ItemDragInfo dragInfo;
    dragInfo.SetX(0.f);
    dragInfo.SetY(0.f);
    eventHub_->FireOnItemDragEnter(dragInfo);
    eventHub_->FireOnItemDragLeave(dragInfo, NULL_VALUE);
    EXPECT_EQ(pattern_->GetOriginalIndex(), 11);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Drag 2nd item to 3rd item, Drag 3 item to 2 item.
     * @tc.expected: GetOriginalIndex changed.
     */
    eventHub_->FireOnItemDragEnter(dragInfo);
    eventHub_->FireOnItemDragMove(dragInfo, 1, 2);
    EXPECT_EQ(pattern_->GetOriginalIndex(), 2);
    eventHub_->FireOnItemDragLeave(dragInfo, NULL_VALUE);
    eventHub_->FireOnItemDragEnter(dragInfo);
    // 3 to 2
    eventHub_->FireOnItemDragMove(dragInfo, 2, 1);
    EXPECT_EQ(pattern_->GetOriginalIndex(), 1);
    // SupportAnimation, ClearDragState
    eventHub_->FireOnItemDrop(dragInfo, 0, 1, true);
    EXPECT_EQ(pattern_->GetOriginalIndex(), NULL_VALUE);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step3. Move something to 3rd item.
     * @tc.expected: GetOriginalIndex changed.
     */
    eventHub_->FireOnItemDragEnter(dragInfo);
    eventHub_->FireOnItemDragLeave(dragInfo, NULL_VALUE);
    eventHub_->FireOnItemDragMove(dragInfo, NULL_VALUE, 2);
    EXPECT_EQ(pattern_->GetOriginalIndex(), 2);
    // SupportAnimation, ClearDragState
    eventHub_->FireOnItemDrop(dragInfo, NULL_VALUE, 1, true);
    EXPECT_EQ(pattern_->GetOriginalIndex(), NULL_VALUE);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step4. Move one item to wrong insertIndex.
     * @tc.expected: GetOriginalIndex unchanged.
     */
    // insertIndex < 0
    eventHub_->FireOnItemDragEnter(dragInfo);
    eventHub_->FireOnItemDragMove(dragInfo, 1, NULL_VALUE);
    EXPECT_EQ(pattern_->GetOriginalIndex(), NULL_VALUE);
    // insertIndex >= itemCount
    eventHub_->FireOnItemDragMove(dragInfo, 1, 11);
    EXPECT_EQ(pattern_->GetOriginalIndex(), NULL_VALUE);
    FlushLayoutTask(frameNode_);
}

/**
 * @tc.name: FireDrag002
 * @tc.desc: Verify drag func with SetLayoutDirection
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, FireDrag002, TestSize.Level1)
{
    const int32_t itemCount = 8;
    GridModelNG model = CreateGrid();
    model.SetLayoutDirection(FlexDirection::ROW);
    model.SetEditable(true);
    model.SetCellLength(ITEM_HEIGHT);
    model.SetMinCount(2);
    model.SetMaxCount(4);
    model.SetSupportAnimation(true);
    CreateFixedItems(itemCount);
    CreateDone(frameNode_);

    GestureEvent info;
    Point globalPoint = Point(270.f, 50.f);
    info.SetGlobalPoint(globalPoint);
    eventHub_->HandleOnItemDragStart(info);

    /**
     * @tc.steps: step1. Drag 1st item to out of Grid.
     * @tc.expected: GetOriginalIndex return number of GridItem.
     */
    ItemDragInfo dragInfo;
    dragInfo.SetX(0.f);
    dragInfo.SetY(0.f);
    eventHub_->FireOnItemDragEnter(dragInfo);
    eventHub_->FireOnItemDragLeave(dragInfo, NULL_VALUE);
    EXPECT_EQ(pattern_->GetOriginalIndex(), itemCount);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Drag 2nd item to 3rd item, Drag 3 item to 2 item.
     * @tc.expected: GetOriginalIndex changed.
     */
    eventHub_->FireOnItemDragEnter(dragInfo);
    eventHub_->FireOnItemDragMove(dragInfo, 1, 2);
    EXPECT_EQ(pattern_->GetOriginalIndex(), 2);
    eventHub_->FireOnItemDragLeave(dragInfo, NULL_VALUE);
    eventHub_->FireOnItemDragEnter(dragInfo);
    // 3 to 2
    eventHub_->FireOnItemDragMove(dragInfo, 2, 1);
    EXPECT_EQ(pattern_->GetOriginalIndex(), 1);
    // SupportAnimation, ClearDragState
    eventHub_->FireOnItemDrop(dragInfo, 0, 1, true);
    EXPECT_EQ(pattern_->GetOriginalIndex(), NULL_VALUE);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step3. Move something to 3rd item.
     * @tc.expected: GetOriginalIndex changed.
     */
    eventHub_->FireOnItemDragEnter(dragInfo);
    eventHub_->FireOnItemDragLeave(dragInfo, NULL_VALUE);
    eventHub_->FireOnItemDragMove(dragInfo, NULL_VALUE, 2);
    EXPECT_EQ(pattern_->GetOriginalIndex(), 2);
    // SupportAnimation, ClearDragState
    eventHub_->FireOnItemDrop(dragInfo, NULL_VALUE, 1, true);
    EXPECT_EQ(pattern_->GetOriginalIndex(), NULL_VALUE);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step4. Move one item to wrong insertIndex.
     * @tc.expected: GetOriginalIndex unchanged.
     */
    // insertIndex < 0
    eventHub_->FireOnItemDragEnter(dragInfo);
    eventHub_->FireOnItemDragMove(dragInfo, 1, NULL_VALUE);
    EXPECT_EQ(pattern_->GetOriginalIndex(), NULL_VALUE);
    // insertIndex >= itemCount
    eventHub_->FireOnItemDragMove(dragInfo, 1, itemCount);
    EXPECT_EQ(pattern_->GetOriginalIndex(), NULL_VALUE);
    FlushLayoutTask(frameNode_);
}

/**
 * @tc.name: FireDrag003
 * @tc.desc: Test drag enter, mover, leave, drop event
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, FireDrag003, TestSize.Level1)
{
    bool isEnter = false;
    bool isMove = false;
    bool isLeave = false;
    bool isDrop = false;
    auto onItemDragEnter = [&isEnter](const ItemDragInfo&) { isEnter = true; };
    auto onItemDragMove = [&isMove](const ItemDragInfo&, int32_t, int32_t) { isMove = true; };
    auto onItemDragLeave = [&isLeave](const ItemDragInfo&, int32_t) { isLeave = true; };
    auto onItemDragDrop = [&isDrop](const ItemDragInfo&, int32_t, int32_t, bool) { isDrop = true; };
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetEditable(true);
    model.SetSupportAnimation(false);
    model.SetOnItemDragEnter(onItemDragEnter);
    model.SetOnItemDragMove(onItemDragMove);
    model.SetOnItemDragLeave(onItemDragLeave);
    model.SetOnItemDrop(onItemDragDrop);
    CreateBigColItem(2, 3);
    CreateBigColItem(0, 2);
    CreateBigColItem(2, 1);
    CreateFixedItems(8);
    CreateDone(frameNode_);

    GestureEvent info;
    Point globalPoint = Point(270.f, 50.f);
    info.SetGlobalPoint(globalPoint);
    eventHub_->HandleOnItemDragStart(info);

    /**
     * @tc.steps: step1. Drag 2nd item to 3rd item, Drag 3 item to 2 item.
     * @tc.expected: GetOriginalIndex changed.
     */
    ItemDragInfo dragInfo;
    dragInfo.SetX(0.f);
    dragInfo.SetY(0.f);
    eventHub_->FireOnItemDragEnter(dragInfo);
    EXPECT_TRUE(isEnter);
    eventHub_->FireOnItemDragMove(dragInfo, 1, 2);
    EXPECT_TRUE(isMove);
    EXPECT_EQ(pattern_->GetOriginalIndex(), -1); // Not SupportAnimation
    eventHub_->FireOnItemDragLeave(dragInfo, NULL_VALUE);
    EXPECT_TRUE(isLeave);
    eventHub_->FireOnItemDragEnter(dragInfo);
    // 3 to 2
    eventHub_->FireOnItemDragMove(dragInfo, 2, 1);
    EXPECT_EQ(pattern_->GetOriginalIndex(), -1); // Not SupportAnimation
    // SupportAnimation, ClearDragState
    eventHub_->FireOnItemDrop(dragInfo, 0, 1, true);
    EXPECT_TRUE(isDrop);
    EXPECT_EQ(pattern_->GetOriginalIndex(), NULL_VALUE);
    FlushLayoutTask(frameNode_);
}

/**
 * @tc.name:FocusStep001
 * @tc.desc: Test GetNextFocusNode in ColumnsTemplate Grid
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, FocusStep001, TestSize.Level1)
{
    /**
     * @tc.cases: Set ColumnsTemplate, GetNextFocusNode from left_top.
     * @tc.expected: Verify all condition of FocusStep.
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFocusableGridItems(10, ITEM_WIDTH, ITEM_HEIGHT);
    CreateDone(frameNode_);
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_VALUE));
}

/**
 * @tc.name:FocusStep002
 * @tc.desc: Test GetNextFocusNode in RowsTemplate Grid
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, FocusStep002, TestSize.Level1)
{
    /**
     * @tc.cases: Set RowsTemplate, GetNextFocusNode from right_top.
     * @tc.expected: Verify all condition of FocusStep.
     */
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr 1fr 1fr");
    CreateFocusableGridItems(10, ITEM_WIDTH, ITEM_HEIGHT);
    CreateDone(frameNode_);
    int32_t currentIndex = 8; // In RowsTemplate grid, item(index:8) is right_top
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 7));
}

/**
 * @tc.name:FocusStep003
 * @tc.desc: Test GetNextFocusNode in RowsTemplate Grid
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, FocusStep003, TestSize.Level1)
{
    /**
     * @tc.cases: Set RowsTemplate, GetNextFocusNode from last item.
     * @tc.expected: Verify all condition of FocusStep.
     */
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr 1fr 1fr");
    CreateFocusableGridItems(10, ITEM_WIDTH, ITEM_HEIGHT);
    CreateDone(frameNode_);
    int32_t currentIndex = 9;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 8));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 8));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 8));
}

/**
 * @tc.name:FocusStep004
 * @tc.desc: Test GetNextFocusNode with colTemplate and rowTemplate
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, FocusStep004, TestSize.Level1)
{
    /**
     * @tc.cases: Set RowsTemplate and ColumnsTemplate, GetNextFocusNode from left_bottom.
     * @tc.expected: Verify all condition of FocusStep.
     */
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr 1fr 1fr");
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFocusableGridItems(10, NULL_VALUE, NULL_VALUE); // Grid calculate its own size
    CreateDone(frameNode_);
    int32_t currentIndex = 8;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 7));
}

/**
 * @tc.name: FocusStep005
 * @tc.desc: Test GetNextFocusNode func when exist big item
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, FocusStep005, TestSize.Level1)
{
    /**
     * @tc.cases: GetNextFocusNode from BigItem.
     * @tc.expected: Verify all condition of FocusStep.
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateBigColItem(2, 3);
    CreateBigColItem(0, 2);
    CreateBigColItem(2, 1);
    CreateFocusableGridItems(7, ITEM_WIDTH, ITEM_HEIGHT);
    CreateDone(frameNode_);
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_VALUE));
}

/**
 * @tc.name: FocusStep006
 * @tc.desc: Test GetNextFocusNode func when exist big item with colTemplate/rowTemplate
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, FocusStep006, TestSize.Level1)
{
    /**
     * @tc.cases: Set RowsTemplate and ColumnsTemplate, GetNextFocusNode from BigItem.
     * @tc.expected: Verify all condition of FocusStep.
     */
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr 1fr 1fr");
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateBigItem(1, 2, 1, 2);
    CreateBigItem(NULL_VALUE, NULL_VALUE, 1, 3);
    CreateBigItem(1, 3, NULL_VALUE, NULL_VALUE);
    CreateFocusableGridItems(7, NULL_VALUE, NULL_VALUE);
    CreateDone(frameNode_);
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 8));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 3));
}

/**
 * @tc.name: FocusStep007
 * @tc.desc: Test GetNextFocusNode func when has unfocuseable item
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, FocusStep007, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFocusableGridItems(10, ITEM_WIDTH, ITEM_HEIGHT);
    CreateDone(frameNode_);

    /**
     * @tc.steps: step1. GetNextFocusNode from 1st item and FocusStep::RIGHT.
     * @tc.expected: The 3rd item is focused.
     */
    GetChildFocusHub(frameNode_, 1)->SetFocusable(false); // The 2nd item can not focus.
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 2));
}

/**
 * @tc.name: FocusStep008
 * @tc.desc: Test GetNextFocusNode func from top boundary item in Scrollable Grid
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, FocusStep008, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFocusableGridItems(24, ITEM_WIDTH, ITEM_HEIGHT);
    CreateDone(frameNode_);

    /**
     * @tc.steps: step1. Scroll to second row
     */
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT - 1.f, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. UP
     */
    int32_t currentIndex = 4;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_EQ(pattern_->gridLayoutInfo_.jumpIndex_, 3);
}

/**
 * @tc.name: FocusStep009
 * @tc.desc: Test GetNextFocusNode func from bottom boundary item in Scrollable Grid
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, FocusStep009, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFocusableGridItems(24, ITEM_WIDTH, ITEM_HEIGHT);
    CreateDone(frameNode_);

    /**
     * @tc.steps: step1. Scroll to first row
     */
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT + 1.f, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. DOWN
     */
    int32_t currentIndex = 19;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_VALUE));
    EXPECT_EQ(pattern_->gridLayoutInfo_.jumpIndex_, 20);
}

/**
 * @tc.name: Focus001
 * @tc.desc: Test Foucus
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, Focus001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFocusableGridItems(18, ITEM_WIDTH, ITEM_HEIGHT);
    CreateDone(frameNode_);

    /**
     * @tc.steps: step1. When focus grid from the outside
     * @tc.expected: Will focus first child
     */
    auto gridFocusNode = frameNode_->GetOrCreateFocusHub();
    gridFocusNode->RequestFocusImmediately();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(GetChildFocusHub(frameNode_, 0)->IsCurrentFocus());

    /**
     * @tc.steps: step2. When grid IsCurrentFocus and has lastFocus child
     * @tc.expected: Will focus last child
     */
    GetChildFocusHub(frameNode_, 1)->RequestFocusImmediately();
    gridFocusNode->RequestFocusImmediately();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(GetChildFocusHub(frameNode_, 1)->IsCurrentFocus());

    /**
     * @tc.steps: step3. Scroll to second row
     * @tc.expected: Would change startMainLineIndex_, focus last child.
     */
    gridFocusNode->RequestFocusImmediately();
    ScrollTo(ITEM_HEIGHT + 1.f);
    EXPECT_TRUE(GetChildFocusHub(frameNode_, 1)->IsCurrentFocus());
}

/**
 * @tc.name: GridAccessibilityTest001
 * @tc.desc: Test AccessibilityFunc
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, GridAccessibilityTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Run accessibilityfunc.
     * @tc.expected: The return_value is correct.
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetMultiSelectable(true);
    model.SetEditable(true);
    CreateFixedItems(14);
    CreateDone(frameNode_);
    EXPECT_TRUE(accessibilityProperty_->IsScrollable());
    EXPECT_TRUE(accessibilityProperty_->IsEditable());
    EXPECT_EQ(accessibilityProperty_->GetBeginIndex(), 0);
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), 13);
    EXPECT_EQ(accessibilityProperty_->GetCollectionItemCounts(), 14);
    AceCollectionInfo info = accessibilityProperty_->GetCollectionInfo();
    EXPECT_EQ(info.rows, 4);
    EXPECT_EQ(info.columns, 4);
    EXPECT_EQ(info.selectMode, 1);
}

/**
 * @tc.name: GetCollectionInfo001
 * @tc.desc: Test AccessibilityGetCollectionInfo func with non-scrollable Grid
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, GetCollectionInfo001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateGridItems(8, ITEM_WIDTH, ITEM_HEIGHT, GridItemStyle::NONE);
    CreateDone(frameNode_);

    /**
     * @tc.steps: step1. Run GetCollectionInfo Func.
     * @tc.expected: Verify return value.
     */
    AceCollectionInfo info = accessibilityProperty_->GetCollectionInfo();
    EXPECT_EQ(info.rows, 2);
    EXPECT_EQ(info.columns, 4);
    EXPECT_EQ(info.selectMode, 0);
}

/**
 * @tc.name: GetCollectionInfo002
 * @tc.desc: Test AccessibilityGetCollectionInfo func with empty GridItem
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, GetCollectionInfo002, TestSize.Level1)
{
    /**
     * @tc.cases: Create with empty items
     * @tc.expected: columns is zero
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateDone(frameNode_);
    AceCollectionInfo info = accessibilityProperty_->GetCollectionInfo();
    EXPECT_EQ(info.rows, 0);
    EXPECT_EQ(info.columns, 0);
    EXPECT_EQ(info.selectMode, 0);
}

/**
 * @tc.name: SetSpecificSupportAction001
 * @tc.desc: Test SetSpecificSupportAction
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, SetSpecificSupportAction001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    CreateFixedItems(6);
    CreateDone(frameNode_);

    /**
     * @tc.steps: step1. Grid is at top.
     * @tc.expected: Check actions value
     */
    EXPECT_TRUE(pattern_->IsAtTop());
    EXPECT_FALSE(pattern_->IsAtBottom());
    accessibilityProperty_->ResetSupportAction();
    uint64_t exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions);

    /**
     * @tc.steps: step2. Grid is at middle.
     * @tc.expected: Check actions value
     */
    ScrollTo(ITEM_HEIGHT);
    EXPECT_FALSE(pattern_->IsAtTop());
    EXPECT_FALSE(pattern_->IsAtBottom());
    accessibilityProperty_->ResetSupportAction();
    exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions);

    /**
     * @tc.steps: step3. Grid is at bottom.
     * @tc.expected: Check actions value
     */
    ScrollTo(ITEM_HEIGHT * 2);
    EXPECT_FALSE(pattern_->IsAtTop());
    EXPECT_TRUE(pattern_->IsAtBottom());
    accessibilityProperty_->ResetSupportAction();
    exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions);

    /**
     * @tc.steps: step4. Grid is unscrollable.
     * @tc.expected: Check actions value
     */
    ClearOldNodes();
    CreateGrid();
    model.SetRowsTemplate("1fr");
    model.SetColumnsTemplate("1fr");
    CreateDone(frameNode_);
    EXPECT_FALSE(accessibilityProperty_->IsScrollable());
    accessibilityProperty_->ResetSupportAction();
    exptectActions = 0;
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions);
}

/**
 * @tc.name: GridItemAccessibilityTest001
 * @tc.desc: Test GridItem Accessibilityfunc
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, GridItemAccessibilityTest001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(20);
    CreateDone(frameNode_);
    auto itemAccessibility = GetChildAccessibilityProperty<GridItemAccessibilityProperty>(frameNode_, 1);

    /**
     * @tc.steps: step2. Run itemAccessibility func.
     * @tc.expected: Verify return value.
     */
    EXPECT_FALSE(itemAccessibility->IsSelected());
    AceCollectionItemInfo info = itemAccessibility->GetCollectionItemInfo();
    EXPECT_EQ(info.row, 0);
    EXPECT_EQ(info.column, 1);
    EXPECT_EQ(info.rowSpan, 1);
    EXPECT_EQ(info.columnSpan, 1);
    EXPECT_FALSE(info.heading);

    /**
     * @tc.steps: step3. Run SetSpecificSupportAction func.
     * @tc.expected: Verify return value.
     */
    itemAccessibility->ResetSupportAction();
    uint64_t exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SELECT);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_CLEAR_SELECTION);
    EXPECT_EQ(GetActions(itemAccessibility), exptectActions);
}

/**
 * @tc.name: GridItemAccessibilityTest002
 * @tc.desc: Test GridItem AccessibilityGetCollectionItemInfo func with has heading GridItem
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, GridItemAccessibilityTest002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    GridItemModelNG itemModel;
    itemModel.Create(GridItemStyle::NONE);
    itemModel.SetColumnStart(0);
    itemModel.SetColumnEnd(3);
    ViewAbstract::SetHeight(CalcLength(Dimension(ITEM_HEIGHT)));
    ViewStackProcessor::GetInstance()->Pop();
    CreateFixedItems(10);
    CreateDone(frameNode_);

    /**
     * @tc.steps: step2. Run GetCollectionItemInfo func.
     * @tc.expected: Verify return value.
     */
    auto itemAccessibility = GetChildAccessibilityProperty<GridItemAccessibilityProperty>(frameNode_, 0);
    AceCollectionItemInfo info = itemAccessibility->GetCollectionItemInfo();
    EXPECT_EQ(info.row, 0);
    EXPECT_EQ(info.column, 0);
    EXPECT_EQ(info.rowSpan, 1);
    EXPECT_EQ(info.columnSpan, 4);
    EXPECT_TRUE(info.heading);
}

/**
 * @tc.name: EventHub001
 * @tc.desc: Test GetInsertPosition func
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, EventHub001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(8);
    CreateDone(frameNode_);
    auto mockRenderContext = AceType::DynamicCast<MockRenderContext>(frameNode_->GetRenderContext());
    mockRenderContext->rect_ = RectF(0.f, 0.f, GRID_WIDTH, GRID_HEIGHT);

    /**
     * @tc.cases: case1. Position out of grid
     * @tc.expected: Return -1
     */
    EXPECT_EQ(eventHub_->GetInsertPosition(GRID_WIDTH + 1.f, GRID_HEIGHT), NULL_VALUE);

    /**
     * @tc.cases: case2. Position in item
     * @tc.expected: Return item index
     */
    EXPECT_EQ(eventHub_->GetInsertPosition(ITEM_WIDTH / 2, ITEM_HEIGHT / 2), 0);

    /**
     * @tc.cases: case3. Position in grid but not in item
     * @tc.expected: Return items count:8
     */
    EXPECT_EQ(eventHub_->GetInsertPosition(ITEM_WIDTH, GRID_HEIGHT), 8);

    /**
     * @tc.cases: case4. Position in grid but not in item and in currentRect_
     * @tc.expected: Return -1
     */
    pattern_->gridLayoutInfo_.currentRect_ = RectF(0.f, 0.f, GRID_WIDTH, GRID_HEIGHT);
    EXPECT_EQ(eventHub_->GetInsertPosition(ITEM_WIDTH, GRID_HEIGHT), NULL_VALUE);
}

/**
 * @tc.name: EventHub002
 * @tc.desc: Test GetFrameNodeChildSize
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, EventHub002, TestSize.Level1)
{
    /**
     * @tc.cases: Create 8 items
     * @tc.expected: Has 8 items
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(8);
    CreateDone(frameNode_);
    EXPECT_EQ(eventHub_->GetFrameNodeChildSize(), 8);
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: GridItem AccessibilityPerformAction test Select and ClearSelection.
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, PerformActionTest001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(20);
    CreateDone(frameNode_);
    auto gridItemPattern = GetChildPattern<GridItemPattern>(frameNode_, 0);
    auto gridItemAccessibilityProperty = GetChildAccessibilityProperty<GridItemAccessibilityProperty>(frameNode_, 0);

    /**
     * @tc.steps: step1. When gridItem is unSelectable
     * @tc.expected: can not be selected
     */
    gridItemPattern->SetSelectable(false);
    gridItemAccessibilityProperty->ActActionSelect();
    EXPECT_FALSE(gridItemPattern->IsSelected());
    gridItemAccessibilityProperty->ActActionClearSelection();
    EXPECT_FALSE(gridItemPattern->IsSelected());

    /**
     * @tc.steps: step2. When gridItem is Selectable
     * @tc.expected: can be selected
     */
    gridItemPattern->SetSelectable(true);
    gridItemAccessibilityProperty->ActActionSelect();
    EXPECT_TRUE(gridItemPattern->IsSelected());
    gridItemAccessibilityProperty->ActActionClearSelection();
    EXPECT_FALSE(gridItemPattern->IsSelected());
}

/**
 * @tc.name: PerformActionTest002
 * @tc.desc: Grid AccessibilityPerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, PerformActionTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. When grid is not Scrollable
     * @tc.expected: can not scrollpage
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(10);
    CreateDone(frameNode_);
    accessibilityProperty_->ActActionScrollForward();
    MockAnimationManager::GetInstance().Tick();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentHeight_, 0.f);
    accessibilityProperty_->ActActionScrollBackward();
    MockAnimationManager::GetInstance().Tick();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentHeight_, 0.f);

    /**
     * @tc.steps: step2. When grid is Scrollable
     * @tc.expected: can scrollpage
     */
    ClearOldNodes();
    model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(40);
    CreateDone(frameNode_);
    accessibilityProperty_->ActActionScrollForward();
    MockAnimationManager::GetInstance().Tick();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(-pattern_->GetGridLayoutInfo().currentHeight_, -GRID_HEIGHT);
    accessibilityProperty_->ActActionScrollBackward();
    MockAnimationManager::GetInstance().Tick();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(-pattern_->GetGridLayoutInfo().currentHeight_, 0.f);
}

/**
 * @tc.name: GridDistributed001
 * @tc.desc: Test the distributed capability of Grid.
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, GridDistributed001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateDone(frameNode_);

    /**
     * @tc.steps: step1. get pattern .
     * @tc.expected: function ProvideRestoreInfo is called.
     */
    pattern_->gridLayoutInfo_.startIndex_ = 1;
    std::string ret = pattern_->ProvideRestoreInfo();

    /**
     * @tc.steps: step2. function OnRestoreInfo is called.
     * @tc.expected: Passing JSON format.
     */
    pattern_->OnRestoreInfo(ret);
    EXPECT_EQ(pattern_->gridLayoutInfo_.jumpIndex_, 1);
}

/**
 * @tc.name: GridModelNg001
 * @tc.desc: Test Grid property.
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, GridModelNg001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateDone(frameNode_);

    /**
     * @tc.steps: step1. InitScroller.
     * @tc.
     */
    auto scrollController = AceType::MakeRefPtr<ScrollControllerBase>();
    ASSERT_NE(scrollController, nullptr);
    auto proxy = AceType::MakeRefPtr<ScrollProxy>();
    ASSERT_NE(proxy, nullptr);
    auto frameNode = AceType::RawPtr(frameNode_);
    ASSERT_NE(frameNode, nullptr);
    GridModelNG::InitScroller(frameNode, scrollController, proxy);
    auto pattern = frameNode->GetPattern<GridPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_NE(pattern->GetScrollBarProxy(), nullptr);
    EXPECT_NE(pattern->GetOrCreatePositionController(), nullptr);

    /**
     * @tc.steps: step2. SetLayoutOptions.
     * @tc.
     */
    GridLayoutOptions gridlayoutoptions;
    GridModelNG::SetLayoutOptions(frameNode, gridlayoutoptions);
    auto property = frameNode->GetLayoutPropertyPtr<GridLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetLayoutOptionsValue(), gridlayoutoptions);
}

/**
 * @tc.name: GridItemModelNg001
 * @tc.desc: Test GridItem property.
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, GridItemModelNg001, TestSize.Level1)
{
    auto node = GridItemModelNG::CreateFrameNode(-1);
    ASSERT_NE(node, nullptr);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step1. SetGridItemStyle.
     * @tc.
     */
    GridItemStyle griditemstyle = GridItemStyle::PLAIN;
    GridItemModelNG::SetGridItemStyle(AceType::RawPtr(node), griditemstyle);
    auto renderContext = node->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto radius = renderContext->GetBorderRadiusValue(BorderRadiusProperty());
    auto themeManager = MockPipelineContext::GetCurrent()->GetThemeManager();
    ASSERT_NE(themeManager, nullptr);
    auto theme = themeManager->GetTheme<GridItemTheme>();
    ASSERT_NE(theme, nullptr);
    EXPECT_EQ(theme->GetGridItemBorderRadius(), radius);
}

/**
 * @tc.name: ClipContent001
 * @tc.desc: Test Grid contentClip.
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, ClipContent001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    CreateGridItems(10, ITEM_WIDTH, ITEM_HEIGHT);
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions({});
    ViewAbstract::SetMargin(CalcLength(10.0f));
    ViewAbstract::SetPadding(CalcLength(1.0f));
    CreateDone(frameNode_);

    auto ctx = AceType::DynamicCast<MockRenderContext>(frameNode_->GetRenderContext());
    ASSERT_TRUE(ctx);
    auto props = frameNode_->GetPaintProperty<ScrollablePaintProperty>();

    auto rect = AceType::MakeRefPtr<ShapeRect>();
    rect->SetWidth(Dimension(200.0f));
    rect->SetHeight(Dimension(200.0f));
    EXPECT_CALL(*ctx, SetContentClip(ClipRectEq(rect))).Times(1);
    props->UpdateContentClip({ ContentClipMode::CUSTOM, rect });
    FlushLayoutTask(frameNode_);

    EXPECT_EQ(frameNode_->GetGeometryNode()->GetPaddingSize(true), SizeF(478.0f, 798.0f));
    EXPECT_CALL(*ctx, SetContentClip(ClipRectEq(frameNode_->GetGeometryNode()->GetPaddingRect()))).Times(1);
    props->UpdateContentClip({ ContentClipMode::CONTENT_ONLY, nullptr });
    FlushLayoutTask(frameNode_);

    EXPECT_CALL(*ctx, SetContentClip(ClipRectEq(frameNode_->GetGeometryNode()->GetFrameRect()))).Times(1);
    props->UpdateContentClip({ ContentClipMode::BOUNDARY, nullptr });
    FlushLayoutTask(frameNode_);
}
} // namespace OHOS::Ace::NG
