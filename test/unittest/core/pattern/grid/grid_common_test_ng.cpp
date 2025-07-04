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
#include "core/common/resource/resource_parse_utils.h"

namespace OHOS::Ace::NG {

namespace {
const Offset LEFT_TOP = Offset(ITEM_MAIN_SIZE * 0.5, ITEM_MAIN_SIZE * 0.5);     // (60, 100)
const Offset LEFT_BOTTOM = Offset(ITEM_MAIN_SIZE * 0.5, ITEM_MAIN_SIZE * 1.5);  // (60, 300)
const Offset RIGHT_TOP = Offset(ITEM_MAIN_SIZE * 1.5, ITEM_MAIN_SIZE * 0.5);    // (180, 100)
const Offset RIGHT_BOTTOM = Offset(ITEM_MAIN_SIZE * 1.5, ITEM_MAIN_SIZE * 1.5); // (180, 300)
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
    RefPtr<FocusHub> nextFocusNode = pattern_->focusHandler_.GetNextFocusNode(step, currentFocusNode).Upgrade();
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
    CreateDone();

    /**
     * @tc.cases: Test invalid args KeyAction::UNKNOWN.
     * @tc.expected: No scroll
     */
    pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_UNKNOWN, KeyAction::UNKNOWN));
    FlushUITasks();
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);

    /**
     * @tc.cases: Test invalid args KeyAction::DOWN KeyCode::KEY_UNKNOWN
     * @tc.expected: No scroll
     */
    pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_PAGE_UP, KeyAction::DOWN));
    FlushUITasks();
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);
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
    CreateDone();

    /**
     * @tc.cases: KeyAction::DOWN KeyCode::KEY_PAGE_DOWN.
     * @tc.expected: Page jump down with Grid height.
     */
    pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_PAGE_DOWN, KeyAction::DOWN));
    FlushUITasks();
    EXPECT_EQ(pattern_->GetTotalOffset(), 100);

    /**
     * @tc.cases: KeyAction::DOWN KeyCode::KEY_PAGE_UP.
     * @tc.expected: Page jump up with Grid height.
     */
    pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_PAGE_UP, KeyAction::DOWN));
    FlushUITasks();
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);
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
    CreateDone();

    /**
     * @tc.steps: step1. Select item(index:0)
     * @tc.expected: The item(index:0) is selected
     */
    MouseSelect(Offset(0, 0), Offset(10.f, 10.f));
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 0)->IsSelected());

    /**
     * @tc.steps: step2. Select from selected item(index:0) to item(index:1)
     * @tc.expected: Selected items unchanged, item(index:0) is selected, item(index:1) is unselected
     */
    MouseSelect(Offset(0, 0), Offset(100, 10.f));
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 0)->IsSelected());
    EXPECT_FALSE(GetChildPattern<GridItemPattern>(frameNode_, 1)->IsSelected());

    /**
     * @tc.steps: step3. Select from unselected item(index:1) to item(index:1)
     * @tc.expected: Selected items changed, item(index:0) is unselected, item(index:1) is selected
     */
    MouseSelect(Offset(100, 0), Offset(110, 10.f));
    EXPECT_FALSE(GetChildPattern<GridItemPattern>(frameNode_, 0)->IsSelected());
    EXPECT_TRUE(GetChildPattern<GridItemPattern>(frameNode_, 1)->IsSelected());

    /**
     * @tc.steps: step4. Click selected item(index:1)
     * @tc.expected: Selected items unchanged, item(index:1) is selected
     */
    MouseSelect(Offset(100, 10.f), Offset(100, 10.f));
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
    CreateDone();
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
    CreateDone();
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
    CreateDone();
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
    CreateDone();
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
    CreateDone();
    bool isSixthItemSelected = false;
    auto selectCallback = [&isSixthItemSelected](bool) { isSixthItemSelected = true; };
    GetChildPattern<GridItemPattern>(frameNode_, 1)->SetSelectable(false);
    GetChildEventHub<GridItemEventHub>(frameNode_, 2)->SetEnabled(false);
    GetChildEventHub<GridItemEventHub>(frameNode_, 5)->SetOnSelect(std::move(selectCallback));
    FlushUITasks();

    /**
     * @tc.steps: step2. Select zone, include items(index:1,2,5,6).
     * @tc.expected: The item(index:1) and item(index:2) are not selected, item(index:5) is selected,
     *               selectCallback is called.
     */
    MouseSelect(Offset(100.0f, 100.0f), Offset(150.0f, 100.0f));
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
    CreateDone();
    MouseSelect(Offset(0, 0), Offset(1.f, 1.f));
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
    CreateDone();
    auto gestureEventHub = eventHub_->GetOrCreateGestureEventHub();
    auto userCallback = gestureEventHub->dragEventActuator_->userCallback_;
    auto HandleOnItemDragStart = userCallback->GetActionStartEventFunc();
    auto HandleOnItemDragUpdate = userCallback->GetActionUpdateEventFunc();
    auto HandleOnItemDragEnd = userCallback->GetActionEndEventFunc();
    auto HandleOnItemDragCancel = userCallback->GetActionCancelEventFunc();
    GestureEvent info;
    auto secondItem = GetChildFrameNode(frameNode_, 1);
    Point secondItemPoint = Point(100, ITEM_MAIN_SIZE / 2);
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
    CreateDone();
    GestureEvent info;
    Point secondItemPoint = Point(ITEM_MAIN_SIZE * 1.5, ITEM_MAIN_SIZE / 2);
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
    CreateDone();

    GestureEvent info;
    Point globalPoint = Point(270.f, 50.f);
    info.SetGlobalPoint(globalPoint);
    eventHub_->HandleOnItemDragStart(info);

    /**
     * @tc.steps: step1. Drag 1st item to out of Grid.
     * @tc.expected: GetOriginalIndex unchange.
     */
    ItemDragInfo dragInfo;
    dragInfo.SetX(0);
    dragInfo.SetY(0);
    eventHub_->FireOnItemDragEnter(dragInfo);
    eventHub_->FireOnItemDragLeave(dragInfo, 0);
    EXPECT_EQ(pattern_->GetOriginalIndex(), -1);
    FlushUITasks();

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
    FlushUITasks();

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
    FlushUITasks();

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
    FlushUITasks();
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
    model.SetCellLength(ITEM_MAIN_SIZE);
    model.SetMinCount(2);
    model.SetMaxCount(4);
    model.SetSupportAnimation(true);
    CreateFixedItems(itemCount);
    CreateDone();

    GestureEvent info;
    Point globalPoint = Point(270.f, 50.f);
    info.SetGlobalPoint(globalPoint);
    eventHub_->HandleOnItemDragStart(info);

    /**
     * @tc.steps: step1. Drag 1st item to out of Grid.
     * @tc.expected: GetOriginalIndex unchange.
     */
    ItemDragInfo dragInfo;
    dragInfo.SetX(0);
    dragInfo.SetY(0);
    eventHub_->FireOnItemDragEnter(dragInfo);
    eventHub_->FireOnItemDragLeave(dragInfo, 0);
    EXPECT_EQ(pattern_->GetOriginalIndex(), -1);
    FlushUITasks();

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
    FlushUITasks();

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
    FlushUITasks();

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
    FlushUITasks();
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
    CreateDone();

    GestureEvent info;
    Point globalPoint = Point(270.f, 50.f);
    info.SetGlobalPoint(globalPoint);
    eventHub_->HandleOnItemDragStart(info);

    /**
     * @tc.steps: step1. Drag 2nd item to 3rd item, Drag 3 item to 2 item.
     * @tc.expected: GetOriginalIndex changed.
     */
    ItemDragInfo dragInfo;
    dragInfo.SetX(0);
    dragInfo.SetY(0);
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
    FlushUITasks();
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
    CreateFocusableGridItems(10, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateDone();
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
    CreateFocusableGridItems(10, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateDone();
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
    CreateFocusableGridItems(10, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateDone();
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
    CreateDone();
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
    CreateFocusableGridItems(7, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateDone();
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
    CreateDone();
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
    CreateFocusableGridItems(10, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateDone();

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
    CreateFocusableGridItems(24, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateDone();

    /**
     * @tc.steps: step1. Scroll to second row
     */
    pattern_->UpdateCurrentOffset(-ITEM_MAIN_SIZE - 1.f, SCROLL_FROM_UPDATE);
    FlushUITasks();

    /**
     * @tc.steps: step2. UP
     */
    int32_t currentIndex = 4;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 0));
    EXPECT_EQ(pattern_->info_.jumpIndex_, 0);
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
    CreateFocusableGridItems(24, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateDone();

    /**
     * @tc.steps: step1. Scroll to first row
     */
    pattern_->UpdateCurrentOffset(-ITEM_MAIN_SIZE + 1.f, SCROLL_FROM_UPDATE);
    FlushUITasks();

    /**
     * @tc.steps: step2. DOWN
     */
    int32_t currentIndex = 19;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 23));
    EXPECT_EQ(pattern_->info_.jumpIndex_, 23);
}

/**
 * @tc.name: FocusWrapMode001
 * @tc.desc: Test GetNextFocusNode func in the rule grid for line wrapping and focusing scenes with directional keys
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, FocusWrapMode001, TestSize.Level1)
{
    /**
     * 0: [0], [1], [2], [3]
     * 1: [4], [5], [6], [7]
     * 2: [8], [9]
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFocusableGridItems(10, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateDone();

    /**
     * @tc.steps: step1. Set the focusWrapMode property to non wrap directional keys
     */
    model.SetFocusWrapMode(AceType::RawPtr(frameNode_), FocusWrapMode::DEFAULT);
    FlushUITasks();

    /**
     * @tc.steps: step2. Press the right arrow key from the node with index 3
     */
    int32_t currentIndex = 3;
    EXPECT_FALSE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 4));

    /**
     * @tc.steps: step3. Set the focusWrapMode property to allow directional key wrapping
     */
    model.SetFocusWrapMode(AceType::RawPtr(frameNode_), FocusWrapMode::WRAP_WITH_ARROW);
    FlushUITasks();

    /**
     * @tc.steps: step4. Press the right arrow key from the node with index 3
     */
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 4));
}

/**
 * @tc.name: FocusWrapMode002
 * @tc.desc: Test GetNextFocusNode func in the rule grid for line wrapping and focusing scenes with directional keys
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, FocusWrapMode002, TestSize.Level1)
{
    /**
     * 0: [0], [1], [2], [3]
     * 1: [4], [5], [6], [7]
     * 2: [8], [9]
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFocusableGridItems(10, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateDone();

    /**
     * @tc.steps: step1. Set the focusWrapMode property to non wrap directional keys
     */
    model.SetFocusWrapMode(AceType::RawPtr(frameNode_), FocusWrapMode::DEFAULT);
    FlushUITasks();

    /**
     * @tc.steps: step2. Press the left arrow key from the node with index 4
     */
    int32_t currentIndex = 4;
    EXPECT_FALSE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 3));

    /**
     * @tc.steps: step3. Set the focusWrapMode property to allow directional key wrapping
     */
    model.SetFocusWrapMode(AceType::RawPtr(frameNode_), FocusWrapMode::WRAP_WITH_ARROW);
    FlushUITasks();

    /**
     * @tc.steps: step4. Press the left arrow key from the node with index 4
     */
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 3));
}

/**
 * @tc.name: FocusWrapMode003
 * @tc.desc: Test GetNextFocusNode func in the irregular grid for line wrapping and focusing scenes with directional
 * keys
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, FocusWrapMode003, TestSize.Level1)
{
    /**
     * 0: [0], [1], [1], [2]
     * 1: [3], [1], [1], [4]
     * 2: [5], [6]
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFocusableBigItem(0, 0, 0, 0);
    CreateFocusableBigItem(0, 1, 1, 2);
    CreateFocusableBigItem(0, 0, 3, 3);
    CreateFocusableBigItem(1, 1, 0, 0);
    CreateFocusableBigItem(1, 1, 3, 3);
    CreateFocusableBigItem(2, 2, 0, 0);
    CreateFocusableBigItem(2, 2, 1, 1);

    /**
     * @tc.steps: step1. Set the focusWrapMode property to allow wrap directional keys
     */
    model.SetFocusWrapMode(AceType::RawPtr(frameNode_), FocusWrapMode::WRAP_WITH_ARROW);
    CreateDone();
    FlushUITasks();

    /**
     * @tc.steps: step2. Press the right arrow key from the node with index 0
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 1));

    /**
     * @tc.steps: step3. Press the right arrow key from the node with index 1
     */
    currentIndex = 1;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 2));

    /**
     * @tc.steps: step4. Press the right arrow key from the node with index 2
     */
    currentIndex = 2;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 3));

    /**
     * @tc.steps: step5. Press the right arrow key from the node with index 3
     */
    currentIndex = 3;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 1));

    /**
     * @tc.steps: step6. Press the right arrow key from the node with index 1 
     */
    currentIndex = 1;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 2));
}

/**
 * @tc.name: FocusWrapMode004
 * @tc.desc: Test GetNextFocusNode func in the irregular grid for line wrapping and focusing scenes with directional
 * keys
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, FocusWrapMode004, TestSize.Level1)
{
    /**
     * 0: [0], [1], [2], [3]
     * 1: [4], [5], [6], [3]
     * 2: [7]
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFocusableBigItem(0, 0, 0, 0);
    CreateFocusableBigItem(0, 0, 1, 1);
    CreateFocusableBigItem(0, 0, 2, 2);
    CreateFocusableBigItem(0, 1, 3, 3);
    CreateFocusableBigItem(1, 1, 0, 0);
    CreateFocusableBigItem(1, 1, 1, 1);
    CreateFocusableBigItem(1, 1, 2, 2);
    CreateFocusableBigItem(2, 2, 0, 0);

    /**
     * @tc.steps: step1. Set the focusWrapMode property to allow wrap directional keys
     */
    model.SetFocusWrapMode(AceType::RawPtr(frameNode_), FocusWrapMode::WRAP_WITH_ARROW);
    CreateDone();
    FlushUITasks();

    /**
     * @tc.steps: step2. Press the right arrow key from the node with index 0
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 1));

    /**
     * @tc.steps: step3. Press the right arrow key from the node with index 1
     */
    currentIndex = 1;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 2));

    /**
     * @tc.steps: step4. Press the right arrow key from the node with index 2
     */
    currentIndex = 2;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 3));

    /**
     * @tc.steps: step5. Press the right arrow key from the node with index 3
     */
    currentIndex = 3;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 4));

    /**
     * @tc.steps: step6. Press the right arrow key from the node with index 4
     */
    currentIndex = 4;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 5));

    /**
     * @tc.steps: step7. Press the right arrow key from the node with index 5
     */
    currentIndex = 5;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 6));

    /**
     * @tc.steps: step8. Press the right arrow key from the node with index 6
     */
    currentIndex = 6;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 3));

    /**
     * @tc.steps: step9. Press the right arrow key from the node with index 3 
     */
    currentIndex = 3;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 4));
}

/**
 * @tc.name: FocusWrapMode005
 * @tc.desc: Test GetNextFocusNode func in the irregular grid for line wrapping and focusing scenes with directional
 * keys
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, FocusWrapMode005, TestSize.Level1)
{
    /**
     * 0: [0], [1], [2], [3]
     * 1: [4], [5], [6], [7]
     * 2: [4], [8]
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFocusableBigItem(0, 0, 0, 0);
    CreateFocusableBigItem(0, 0, 1, 1);
    CreateFocusableBigItem(0, 0, 2, 2);
    CreateFocusableBigItem(0, 0, 3, 3);
    CreateFocusableBigItem(1, 2, 0, 0);
    CreateFocusableBigItem(1, 1, 1, 1);
    CreateFocusableBigItem(1, 1, 2, 2);
    CreateFocusableBigItem(1, 1, 3, 3);
    CreateFocusableBigItem(2, 2, 1, 1);

    /**
     * @tc.steps: step1. Set the focusWrapMode property to allow wrap directional keys
     */
    model.SetFocusWrapMode(AceType::RawPtr(frameNode_), FocusWrapMode::WRAP_WITH_ARROW);
    CreateDone();
    FlushUITasks();

    /**
     * @tc.steps: step2. Press the right arrow key from the node with index 0
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 1));

    /**
     * @tc.steps: step3. Press the right arrow key from the node with index 1
     */
    currentIndex = 1;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 2));

    /**
     * @tc.steps: step4. Press the right arrow key from the node with index 2
     */
    currentIndex = 2;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 3));

    /**
     * @tc.steps: step5. Press the right arrow key from the node with index 3
     */
    currentIndex = 3;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 4));

    /**
     * @tc.steps: step6. Press the right arrow key from the node with index 4
     */
    currentIndex = 4;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 5));

    /**
     * @tc.steps: step7. Press the right arrow key from the node with index 5
     */
    currentIndex = 5;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 6));

    /**
     * @tc.steps: step8. Press the right arrow key from the node with index 6
     */
    currentIndex = 6;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 7));

    /**
     * @tc.steps: step9. Press the right arrow key from the node with index 7
     */
    currentIndex = 7;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 4));
}

/**
 * @tc.name: FocusWrapMode006
 * @tc.desc: Test GetNextFocusNode func in the rule grid for line wrapping and focusing scenes with directional keys
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, FocusWrapMode006, TestSize.Level1)
{
    /**
     * 0: [3], [2], [1], [0]
     * 1: [7], [6], [5], [4]
     * 2: [9], [8]
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetIsRTL(TextDirection::RTL);
    CreateFocusableGridItems(10, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateDone();

    /**
     * @tc.steps: step1. Set the focusWrapMode property to non wrap directional keys
     */
    model.SetFocusWrapMode(AceType::RawPtr(frameNode_), FocusWrapMode::DEFAULT);
    FlushUITasks();

    /**
     * @tc.steps: step2. Press the right arrow key from the node with index 5
     */
    int32_t currentIndex = 5;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 4));

    /**
     * @tc.steps: step3. Press the right arrow key from the node with index 4
     */
    currentIndex = 4;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_VALUE));

    /**
     * @tc.steps: step4. Set the focusWrapMode property to allow wrap directional keys
     */
    model.SetFocusWrapMode(AceType::RawPtr(frameNode_), FocusWrapMode::WRAP_WITH_ARROW);
    FlushUITasks();

    /**
     * @tc.steps: step5. Press the right arrow key from the node with index 5
     */
    currentIndex = 5;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 4));

    /**
     * @tc.steps: step6. Press the right arrow key from the node with index 4
     */
    currentIndex = 4;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 3));
}

/**
 * @tc.name: FocusWrapMode007
 * @tc.desc: Test GetNextFocusNode func in irregular grid for line wrapping and focusing scenes with directional keys
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, FocusWrapMode007, TestSize.Level1)
{
    /**
     * 0: [0], [1], [2], [3]
     * 1: [0], [4], [5], [6]
     * 2: [7]
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFocusableBigItem(0, 1, 0, 0);
    CreateFocusableBigItem(0, 0, 1, 1);
    CreateFocusableBigItem(0, 0, 2, 2);
    CreateFocusableBigItem(0, 0, 3, 3);
    CreateFocusableBigItem(1, 1, 1, 1);
    CreateFocusableBigItem(1, 1, 2, 2);
    CreateFocusableBigItem(1, 1, 3, 3);
    CreateFocusableBigItem(2, 2, 0, 0);

    /**
     * @tc.steps: step1. Set the focusWrapMode property to allow wrap directional keys
     */
    model.SetFocusWrapMode(AceType::RawPtr(frameNode_), FocusWrapMode::WRAP_WITH_ARROW);
    CreateDone();
    FlushUITasks();

    /**
     * @tc.steps: step2. Press the right arrow key from the node with index 6
     */
    int32_t currentIndex = 6;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 7));

    /**
     * @tc.steps: step3. Press the left arrow key from the node with index 7
     */
    currentIndex = 7;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 6));
}

/**
 * @tc.name: FocusWrapMode008
 * @tc.desc: Test the tab key focusing rule of GetNextFocusNode func in horizontal layout RTL mode
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, FocusWrapMode008, TestSize.Level1)
{
    /**
     * 0: [9], [6], [3], [0]
     * 1:      [7], [4], [1]
     * 2:      [8], [5], [2]
     */
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr 1fr");
    model.SetIsRTL(TextDirection::RTL);
    CreateFocusableGridItems(10, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateDone();

    /**
     * @tc.steps: step1. Press the tab key from the node with index 1
     */
    int32_t currentIndex = 1;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 2));

    /**
     * @tc.steps: step2. Press the tab key from the node with index 2
     */
    currentIndex = 2;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 3));

    /**
     * @tc.steps: step3. Press the shift+tab key from the node with index 3
     */
    currentIndex = 3;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 2));

    /**
     * @tc.steps: step4. Press the up key from the node with index 3
     */
    currentIndex = 3;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));

    /**
     * @tc.steps: step5. Press the up key from the node with index 2
     */
    currentIndex = 2;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 1));

    /**
     * @tc.steps: step6. Press the down key from the node with index 2
     */
    currentIndex = 2;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_VALUE));
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
    CreateFocusableGridItems(18, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateDone();

    /**
     * @tc.steps: step1. When focus grid from the outside
     * @tc.expected: Will focus first child
     */
    auto gridFocusNode = frameNode_->GetOrCreateFocusHub();
    gridFocusNode->RequestFocusImmediately();
    FlushUITasks();
    EXPECT_TRUE(GetChildFocusHub(frameNode_, 0)->IsCurrentFocus());

    /**
     * @tc.steps: step2. When grid IsCurrentFocus and has lastFocus child
     * @tc.expected: Will focus last child
     */
    GetChildFocusHub(frameNode_, 1)->RequestFocusImmediately();
    gridFocusNode->RequestFocusImmediately();
    FlushUITasks();
    EXPECT_TRUE(GetChildFocusHub(frameNode_, 1)->IsCurrentFocus());

    /**
     * @tc.steps: step3. Scroll to second row
     * @tc.expected: item 1 scroll out of viewport, lost focus
     */
    gridFocusNode->RequestFocusImmediately();
    ScrollTo(ITEM_MAIN_SIZE + 1.f);
    EXPECT_FALSE(GetChildFocusHub(frameNode_, 1)->IsCurrentFocus());
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
    CreateDone();
    auto mockRenderContext = AceType::DynamicCast<MockRenderContext>(frameNode_->GetRenderContext());
    mockRenderContext->rect_ = RectF(0, 0, WIDTH, HEIGHT);

    /**
     * @tc.cases: case1. Position out of grid
     * @tc.expected: Return -1
     */
    EXPECT_EQ(eventHub_->GetInsertPosition(WIDTH + 1.f, HEIGHT), NULL_VALUE);

    /**
     * @tc.cases: case2. Position in item
     * @tc.expected: Return item index
     */
    EXPECT_EQ(eventHub_->GetInsertPosition(ITEM_MAIN_SIZE / 2, ITEM_MAIN_SIZE / 2), 0);

    /**
     * @tc.cases: case3. Position in grid but not in item
     * @tc.expected: Return items count:8
     */
    EXPECT_EQ(eventHub_->GetInsertPosition(ITEM_MAIN_SIZE, HEIGHT), 8);

    /**
     * @tc.cases: case4. Position in grid but not in item and in currentRect_
     * @tc.expected: Return -1
     */
    pattern_->info_.currentRect_ = RectF(0, 0, WIDTH, HEIGHT);
    EXPECT_EQ(eventHub_->GetInsertPosition(ITEM_MAIN_SIZE, HEIGHT), NULL_VALUE);
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
    CreateDone();
    EXPECT_EQ(eventHub_->GetFrameNodeChildSize(), 8);
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
    CreateDone();

    /**
     * @tc.steps: step1. get pattern .
     * @tc.expected: function ProvideRestoreInfo is called.
     */
    pattern_->info_.startIndex_ = 1;
    std::string ret = pattern_->ProvideRestoreInfo();

    /**
     * @tc.steps: step2. function OnRestoreInfo is called.
     * @tc.expected: Passing JSON format.
     */
    pattern_->OnRestoreInfo(ret);
    EXPECT_EQ(pattern_->info_.jumpIndex_, 1);
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
    CreateDone();

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
    CreateGridItems(10, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions({});
    ViewAbstract::SetMargin(CalcLength(10.0f));
    ViewAbstract::SetPadding(CalcLength(1.0f));
    CreateDone();

    auto ctx = AceType::DynamicCast<MockRenderContext>(frameNode_->GetRenderContext());
    ASSERT_TRUE(ctx);
    auto props = frameNode_->GetPaintProperty<ScrollablePaintProperty>();
    ASSERT_TRUE(AceType::InstanceOf<GridPaintProperty>(props));

    auto rect = AceType::MakeRefPtr<ShapeRect>();
    rect->SetWidth(Dimension(200.0f));
    rect->SetHeight(Dimension(200.0f));
    EXPECT_CALL(*ctx, SetContentClip(ClipRectEq(rect))).Times(1);
    props->UpdateContentClip({ ContentClipMode::CUSTOM, rect });
    FlushUITasks();

    EXPECT_TRUE(IsEqual(frameNode_->GetGeometryNode()->GetPaddingSize(true), SizeF(238, 398)));
    auto gridRect = frameNode_->GetGeometryNode()->GetPaddingRect();
    gridRect.SetOffset(gridRect.GetOffset() - frameNode_->GetGeometryNode()->GetFrameOffset());
    EXPECT_CALL(*ctx, SetContentClip(ClipRectEq(gridRect))).Times(1);
    props->UpdateContentClip({ ContentClipMode::CONTENT_ONLY, nullptr });
    FlushUITasks();

    gridRect = frameNode_->GetGeometryNode()->GetFrameRect();
    gridRect.SetOffset({ 0.0f, 0.0f });
    EXPECT_CALL(*ctx, SetContentClip(ClipRectEq(gridRect))).Times(2);
    props->UpdateContentClip({ ContentClipMode::BOUNDARY, nullptr });
    FlushUITasks();

    props->UpdateContentClip({ ContentClipMode::DEFAULT, nullptr });
    EXPECT_EQ(props->GetDefaultContentClip(), ContentClipMode::BOUNDARY);
    FlushUITasks();
}

/**
 * @tc.name: Focus002
 * @tc.desc: Test Focus with Scroll
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, Focus002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFocusableGridItems(18, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateDone();

    /**
     * @tc.steps: step1. When focus grid from the outside
     * @tc.expected: Will focus first child
     */
    auto gridFocusNode = frameNode_->GetOrCreateFocusHub();
    gridFocusNode->RequestFocusImmediately();
    FlushUITasks();
    EXPECT_TRUE(GetChildFocusHub(frameNode_, 0)->IsCurrentFocus());

    /**
     * @tc.steps: step2. Scroll to third row
     * @tc.expected: item 0 scroll out of viewport, lost focus
     */
    pattern_->UpdateCurrentOffset(-ITEM_MAIN_SIZE * 2, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_FALSE(GetChildFocusHub(frameNode_, 0)->IsCurrentFocus());

    /**
     * @tc.steps: step3. Scroll to top
     * @tc.expected: item 0 scroll into viewport, request focus
     */
    pattern_->UpdateCurrentOffset(ITEM_MAIN_SIZE * 2, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_TRUE(GetChildFocusHub(frameNode_, 0)->IsCurrentFocus());
}

/**
 * @tc.name: Focus003
 * @tc.desc: Test Focus with Scroll
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, Focus003, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(2, true);
    CreateFocusableGridItems(28, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateDone();

    /**
     * @tc.steps: step1. When focus grid from the outside
     * @tc.expected: Will focus first child
     */
    auto gridFocusNode = frameNode_->GetOrCreateFocusHub();
    gridFocusNode->RequestFocusImmediately();
    FlushUITasks();
    EXPECT_TRUE(GetChildFocusHub(frameNode_, 0)->IsCurrentFocus());

    /**
     * @tc.steps: step2. Scroll to third row
     * @tc.expected: item 0 is in cache, keep focus
     */
    pattern_->UpdateCurrentOffset(-ITEM_MAIN_SIZE * 2, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_TRUE(GetChildFocusHub(frameNode_, 0)->IsCurrentFocus());

    /**
     * @tc.steps: step3. Scroll to forth row
     * @tc.expected: item 0 scroll out of cache, lost focus
     */
    pattern_->UpdateCurrentOffset(-ITEM_MAIN_SIZE * 1, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_FALSE(GetChildFocusHub(frameNode_, 0)->IsCurrentFocus());

    /**
     * @tc.steps: step3. Scroll to third row
     * @tc.expected: item 0 scroll into cache, request focus
     */
    pattern_->UpdateCurrentOffset(ITEM_MAIN_SIZE * 1, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_TRUE(GetChildFocusHub(frameNode_, 0)->IsCurrentFocus());
}

/**
 * @tc.name: IsInViewPort001
 * @tc.desc: Test Focus with Scroll
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, IsInViewPort001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(2, true);
    CreateFocusableGridItems(28, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateDone();

    /**
     * @tc.steps: step1. Check is in view port
     * @tc.expected: item 0 is in view port
     */
    EXPECT_TRUE(pattern_->focusHandler_.IsInViewport(0, true));
    EXPECT_TRUE(pattern_->focusHandler_.IsInViewport(0, false));

    /**
     * @tc.steps: step2. Scroll to third row
     * @tc.expected: item 0 is in cache, not in view port
     */
    pattern_->UpdateCurrentOffset(-ITEM_MAIN_SIZE * 2, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_TRUE(pattern_->focusHandler_.IsInViewport(0, true));
    EXPECT_FALSE(pattern_->focusHandler_.IsInViewport(0, false));

    /**
     * @tc.steps: step2. Scroll to fifth row
     * @tc.expected: item 0 is not cache, not in view port
     */
    pattern_->UpdateCurrentOffset(-ITEM_MAIN_SIZE * 1, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_FALSE(pattern_->focusHandler_.IsInViewport(0, true));
    EXPECT_FALSE(pattern_->focusHandler_.IsInViewport(0, false));
}

/**
 * @tc.name: FireDrag004
 * @tc.desc: Drag an item which is from another Grid, test layout.
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, FireDrag004, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEditable(true);
    model.SetSupportAnimation(true);
    CreateFixedItems(4);
    CreateDone();

    GestureEvent info;
    Point globalPoint = Point(270.f, 50.f);
    info.SetGlobalPoint(globalPoint);
    eventHub_->HandleOnItemDragStart(info);

    ItemDragInfo dragInfo;
    dragInfo.SetX(0);
    dragInfo.SetY(0);
    eventHub_->FireOnItemDragEnter(dragInfo);
    // drag an extraneous item to [3] in this Grid.
    eventHub_->FireOnItemDragMove(dragInfo, -1, 3);
    FlushUITasks();

    const decltype(pattern_->info_.gridMatrix_) cmp = { { 0, { { 0, 0 }, { 1, 1 } } }, { 1, { { 0, 2 }, { 1, -1 } } },
        { 2, { { 0, 3 }, { 1, 3 } } } };
    EXPECT_EQ(pattern_->info_.gridMatrix_, cmp);
    /*
     *  0 1
     *  2
     *  3
     */
    EXPECT_TRUE(IsEqual(GetItemRect(0), Rect(0, 0, WIDTH / 2, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(IsEqual(GetItemRect(1), Rect(120, 0, WIDTH / 2, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(IsEqual(GetItemRect(2), Rect(0, 100, WIDTH / 2, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(IsEqual(GetItemRect(3), Rect(0, 200, WIDTH / 2, ITEM_MAIN_SIZE)));

    // drag the item out of this Grid.
    eventHub_->FireOnItemDragLeave(dragInfo, -1);
    FlushUITasks();
    /*
     *  0 1
     *  2 3
     */
    EXPECT_TRUE(IsEqual(GetItemRect(0), Rect(0, 0, WIDTH / 2, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(IsEqual(GetItemRect(1), Rect(120, 0, WIDTH / 2, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(IsEqual(GetItemRect(2), Rect(0, 100, WIDTH / 2, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(IsEqual(GetItemRect(3), Rect(120, 100, WIDTH / 2, ITEM_MAIN_SIZE)));

    // drag item [1] in this grid to [0]
    eventHub_->FireOnItemDragMove(dragInfo, 1, 0);
    FlushUITasks();

    /*
     *  1 0
     *  2 3
     */
    EXPECT_TRUE(IsEqual(GetItemRect(0), Rect(120, 0, WIDTH / 2, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(IsEqual(GetItemRect(1), Rect(0, 0, WIDTH / 2, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(IsEqual(GetItemRect(2), Rect(0, 100, WIDTH / 2, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(IsEqual(GetItemRect(3), Rect(120, 100, WIDTH / 2, ITEM_MAIN_SIZE)));
}

/**
 * @tc.name: CreateWithResourceObjFriction
 * @tc.desc: Test CreateWithResourceObjFriction in GridModelNG
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, CreateWithResourceObjFriction001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(pattern_, nullptr);
    ASSERT_EQ(pattern_->resourceMgr_, nullptr);

    const double defaultiction = 10000000.0f;
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);

    // remove callback function
    model.CreateWithResourceObjFriction(nullptr);
    EXPECT_EQ(pattern_->resourceMgr_, nullptr);

    // add callback function
    model.CreateWithResourceObjFriction(resObj);
    ASSERT_NE(pattern_->resourceMgr_, nullptr);
    EXPECT_NE(pattern_->resourceMgr_->resMap_.size(), 0);

    pattern_->friction_ = defaultiction;
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_NE(pattern_->friction_, defaultiction);

    // remove callback function
    model.CreateWithResourceObjFriction(nullptr);
    EXPECT_EQ(pattern_->resourceMgr_, nullptr);

    resObj->id_ = 0;
    resObj->type_ = static_cast<int32_t>(ResourceType::INTEGER);

    // add callback function
    model.CreateWithResourceObjFriction(resObj);
    ASSERT_NE(pattern_->resourceMgr_, nullptr);
    EXPECT_NE(pattern_->resourceMgr_->resMap_.size(), 0);

    pattern_->friction_ = defaultiction;
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_NE(pattern_->friction_, defaultiction);

    // remove callback function
    model.CreateWithResourceObjFriction(nullptr);
    EXPECT_EQ(pattern_->resourceMgr_, nullptr);
}

/**
 * @tc.name: CreateWithResourceObjFriction
 * @tc.desc: Test CreateWithResourceObjFriction in GridModelNG
 * @tc.type: FUNC
 */
HWTEST_F(GridCommonTestNg, CreateWithResourceObjFriction002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(pattern_, nullptr);
    ASSERT_EQ(pattern_->resourceMgr_, nullptr);

    const double defaultiction = 10000000.0f;
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);

    GridModelNG::CreateWithResourceObjFriction(nullptr, nullptr);
    EXPECT_EQ(pattern_->resourceMgr_, nullptr);

    GridModelNG::CreateWithResourceObjFriction(AceType::RawPtr(frameNode_), nullptr);
    EXPECT_EQ(pattern_->resourceMgr_, nullptr);

    // add callback function
    GridModelNG::CreateWithResourceObjFriction(nullptr, resObj);
    EXPECT_EQ(pattern_->resourceMgr_, nullptr);

    GridModelNG::CreateWithResourceObjFriction(AceType::RawPtr(frameNode_), resObj);
    ASSERT_NE(pattern_->resourceMgr_, nullptr);
    EXPECT_NE(pattern_->resourceMgr_->resMap_.size(), 0);
    pattern_->friction_ = defaultiction;
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_NE(pattern_->friction_, defaultiction);

    // remove callback function
    GridModelNG::CreateWithResourceObjFriction(nullptr, nullptr);
    EXPECT_NE(pattern_->resourceMgr_, nullptr);
    GridModelNG::CreateWithResourceObjFriction(AceType::RawPtr(frameNode_), nullptr);
    EXPECT_EQ(pattern_->resourceMgr_, nullptr);

    resObj->id_ = 0;
    resObj->type_ = static_cast<int32_t>(ResourceType::INTEGER);

    GridModelNG::CreateWithResourceObjFriction(nullptr, resObj);
    EXPECT_EQ(pattern_->resourceMgr_, nullptr);

    // add callback function
    GridModelNG::CreateWithResourceObjFriction(AceType::RawPtr(frameNode_), resObj);
    ASSERT_NE(pattern_->resourceMgr_, nullptr);
    EXPECT_NE(pattern_->resourceMgr_->resMap_.size(), 0);
    pattern_->friction_ = defaultiction;
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_NE(pattern_->friction_, defaultiction);

    // remove callback function
    GridModelNG::CreateWithResourceObjFriction(nullptr, nullptr);
    EXPECT_NE(pattern_->resourceMgr_, nullptr);
    GridModelNG::CreateWithResourceObjFriction(AceType::RawPtr(frameNode_), nullptr);
    EXPECT_EQ(pattern_->resourceMgr_, nullptr);
}
} // namespace OHOS::Ace::NG
