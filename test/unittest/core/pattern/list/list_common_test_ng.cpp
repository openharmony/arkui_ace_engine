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
#include "test/mock/core/animation/mock_animation_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/syntax/mock_lazy_for_each_actuator.h"
#include "test/unittest/core/syntax/mock_lazy_for_each_builder.h"

#include "core/components/common/properties/shadow_config.h"
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "core/components_ng/syntax/for_each_model_ng.h"
#include "core/components_ng/syntax/for_each_node.h"
#include "core/components_ng/syntax/lazy_for_each_model_ng.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"
#include "core/components_ng/syntax/lazy_layout_wrapper_builder.h"
#include "core/components_ng/syntax/syntax_item.h"

namespace OHOS::Ace::NG {

namespace {
const Offset LEFT_TOP = Offset(120.f, 150.f);
const Offset LEFT_BOTTOM = Offset(120.f, 250.f);
const Offset RIGHT_TOP = Offset(360.f, 150.f);
const Offset RIGHT_BOTTOM = Offset(360.f, 250.f);
} // namespace

class ListCommonTestNg : public ListTestNg {
public:
    void CreateFocusableListItems(int32_t itemNumber);
    void CreateFocusableListItemGroups(int32_t groupNumber);
    void MouseSelect(Offset start, Offset end);
    AssertionResult IsEqualNextFocusNode(FocusStep step, int32_t currentIndex, int32_t expectNextIndex);
    int32_t FindFocusNodeIndex(RefPtr<FocusHub>& focusNode);
    std::vector<RefPtr<FrameNode>> GetFlatListItems();
    void CreateForEachList(int32_t itemNumber, int32_t lanes, std::function<void(int32_t, int32_t)> onMove);
    void CreateLazyForEachList(int32_t itemNumber, int32_t lanes, std::function<void(int32_t, int32_t)> onMove);
    AssertionResult VerifyForEachItemsOrder(std::list<std::string> expectKeys);
    AssertionResult VerifyLazyForEachItemsOrder(std::list<std::string> expectKeys);
    RefPtr<ListItemDragManager> GetForEachItemDragManager(int32_t itemIndex);
    RefPtr<ListItemDragManager> GetLazyForEachItemDragManager(int32_t itemIndex);
};

void ListCommonTestNg::CreateFocusableListItems(int32_t itemNumber)
{
    for (int32_t index = 0; index < itemNumber; index++) {
        CreateListItem();
        {
            ButtonModelNG buttonModelNG;
            buttonModelNG.CreateWithLabel("label");
            ViewStackProcessor::GetInstance()->GetMainElementNode()->onMainTree_ = true;
            ViewStackProcessor::GetInstance()->Pop();
        }
        ViewStackProcessor::GetInstance()->GetMainElementNode()->onMainTree_ = true;
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
}

void ListCommonTestNg::CreateFocusableListItemGroups(int32_t groupNumber)
{
    for (int32_t index = 0; index < groupNumber; index++) {
        CreateListItemGroup();
        CreateFocusableListItems(GROUP_ITEM_NUMBER);
        ViewStackProcessor::GetInstance()->GetMainElementNode()->onMainTree_ = true;
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
}

void ListCommonTestNg::MouseSelect(Offset start, Offset end)
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

AssertionResult ListCommonTestNg::IsEqualNextFocusNode(FocusStep step, int32_t currentIndex, int32_t expectNextIndex)
{
    std::vector<RefPtr<FrameNode>> listItems = GetFlatListItems();
    RefPtr<FocusHub> currentFocusNode = listItems[currentIndex]->GetOrCreateFocusHub();
    currentFocusNode->RequestFocusImmediately();
    RefPtr<FocusHub> nextFocusNode = pattern_->GetNextFocusNode(step, currentFocusNode).Upgrade();
    if (expectNextIndex != NULL_VALUE && nextFocusNode == nullptr) {
        return AssertionFailure() << "Next FocusNode is null.";
    }
    int32_t nextIndex = FindFocusNodeIndex(nextFocusNode);
    return IsEqual(nextIndex, expectNextIndex);
}

int32_t ListCommonTestNg::FindFocusNodeIndex(RefPtr<FocusHub>& focusNode)
{
    std::vector<RefPtr<FrameNode>> listItems = GetFlatListItems();
    int32_t size = static_cast<int32_t>(listItems.size());
    for (int32_t index = 0; index < size; index++) {
        if (focusNode == listItems[index]->GetOrCreateFocusHub()) {
            return index;
        }
    }
    return NULL_VALUE;
}

// Get all listItem that in or not in listItemGroup
std::vector<RefPtr<FrameNode>> ListCommonTestNg::GetFlatListItems()
{
    std::vector<RefPtr<FrameNode>> listItems;
    auto children = frameNode_->GetChildren();
    for (auto child : children) {
        auto childFrameNode = AceType::DynamicCast<FrameNode>(child);
        if (childFrameNode->GetTag() == V2::LIST_ITEM_GROUP_ETS_TAG) {
            auto group = child->GetChildren();
            for (auto item : group) {
                auto itemFrameNode = AceType::DynamicCast<FrameNode>(item);
                if (itemFrameNode->GetTag() == V2::LIST_ITEM_ETS_TAG) {
                    listItems.emplace_back(itemFrameNode);
                }
            }
        } else if (childFrameNode->GetTag() == V2::LIST_ITEM_ETS_TAG) {
            listItems.emplace_back(childFrameNode);
        }
    }
    return listItems;
}

void ListCommonTestNg::CreateForEachList(
    int32_t itemNumber, int32_t lanes, std::function<void(int32_t, int32_t)> onMove)
{
    ListModelNG model = CreateList();
    model.SetLanes(lanes);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto weakList = AceType::WeakClaim(AceType::RawPtr(listNode));
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    ForEachModelNG forEachModelNG;
    forEachModelNG.Create();
    auto forEachNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    forEachNode->SetParent(weakList); // for InitAllChildrenDragManager
    std::list<std::string> newIds;
    for (int32_t index = 0; index < itemNumber; index++) {
        newIds.emplace_back(std::to_string(index));
    }
    std::list<int32_t> removedElmtId;
    forEachModelNG.SetNewIds(std::move(newIds));
    forEachModelNG.SetRemovedElmtIds(removedElmtId);
    forEachModelNG.OnMove(std::move(onMove));
    for (int32_t index = 0; index < itemNumber; index++) {
        // key is 0,1,2,3...
        forEachModelNG.CreateNewChildStart(std::to_string(index));
        CreateListItems(1);
        forEachModelNG.CreateNewChildFinish(std::to_string(index));
    }
}

void ListCommonTestNg::CreateLazyForEachList(
    int32_t itemNumber, int32_t lanes, std::function<void(int32_t, int32_t)> onMove)
{
    ListModelNG model = CreateList();
    model.SetLanes(lanes);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto weakList = AceType::WeakClaim(AceType::RawPtr(listNode));
    const RefPtr<LazyForEachActuator> lazyForEachActuator = AceType::MakeRefPtr<Framework::MockLazyForEachBuilder>();
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    LazyForEachModelNG lazyForEachModelNG;
    lazyForEachModelNG.Create(lazyForEachActuator);
    auto node = ViewStackProcessor::GetInstance()->GetMainElementNode();
    node->SetParent(weakList); // for InitAllChildrenDragManager
    lazyForEachModelNG.OnMove(std::move(onMove));
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(node);
    for (int32_t index = 0; index < itemNumber; index++) {
        CreateListItem();
        auto listItemNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
        lazyForEachNode->builder_->cachedItems_.try_emplace(
            index, LazyForEachChild(std::to_string(index), listItemNode));
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
}

AssertionResult ListCommonTestNg::VerifyForEachItemsOrder(std::list<std::string> expectKeys)
{
    auto forEachNode = AceType::DynamicCast<ForEachNode>(frameNode_->GetChildAtIndex(0));
    auto& children = forEachNode->ModifyChildren();
    std::string childrenKeysStr;
    std::string expectKeysStr;
    auto childIter = children.begin();
    for (auto keyIter = expectKeys.begin(); keyIter != expectKeys.end(); keyIter++) {
        expectKeysStr += *keyIter + ", ";
        auto& child = *childIter;
        auto syntaxItem = AceType::DynamicCast<SyntaxItem>(child);
        childrenKeysStr += syntaxItem->GetKey() + ", ";
        childIter++;
    }
    return IsEqual(childrenKeysStr, expectKeysStr);
}

AssertionResult ListCommonTestNg::VerifyLazyForEachItemsOrder(std::list<std::string> expectKeys)
{
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(frameNode_->GetChildAtIndex(0));
    auto cachedItems = lazyForEachNode->builder_->cachedItems_;
    std::string childrenKeysStr;
    std::string expectKeysStr;
    auto childIter = cachedItems.begin();
    for (auto keyIter = expectKeys.begin(); keyIter != expectKeys.end(); keyIter++) {
        expectKeysStr += *keyIter + ", ";
        childrenKeysStr += childIter->second.first + ", ";
        childIter++;
    }
    return IsEqual(childrenKeysStr, expectKeysStr);
}

RefPtr<ListItemDragManager> ListCommonTestNg::GetForEachItemDragManager(int32_t itemIndex)
{
    auto forEachNode = AceType::DynamicCast<ForEachNode>(frameNode_->GetChildAtIndex(0));
    auto syntaxItem = AceType::DynamicCast<SyntaxItem>(forEachNode->GetChildAtIndex(itemIndex));
    auto listItem = AceType::DynamicCast<FrameNode>(syntaxItem->GetChildAtIndex(0));
    auto listItemPattern = listItem->GetPattern<ListItemPattern>();
    return listItemPattern->dragManager_;
}

RefPtr<ListItemDragManager> ListCommonTestNg::GetLazyForEachItemDragManager(int32_t itemIndex)
{
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(frameNode_->GetChildAtIndex(0));
    auto listItem = AceType::DynamicCast<FrameNode>(lazyForEachNode->GetChildAtIndex(itemIndex));
    auto listItemPattern = listItem->GetPattern<ListItemPattern>();
    return listItemPattern->dragManager_;
}

/**
 * @tc.name: FocusStep001
 * @tc.desc: Test GetNextFocusNode func
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, FocusStep001, TestSize.Level1)
{
    CreateList();
    CreateFocusableListItems(4);
    CreateDone();

    /**
     * @tc.steps: step1. GetNextFocusNode from first item
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_VALUE));
}

/**
 * @tc.name: FocusStep002
 * @tc.desc: Test GetNextFocusNode func with HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, FocusStep002, TestSize.Level1)
{
    ListModelNG model = CreateList();
    ViewAbstract::SetWidth(CalcLength(400));
    model.SetListDirection(Axis::HORIZONTAL);
    CreateFocusableListItems(4);
    CreateDone();

    /**
     * @tc.steps: step1. GetNextFocusNode from middle item
     */
    int32_t currentIndex = 2;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 1));

    /**
     * @tc.steps: step2. GetNextFocusNode from last item
     */
    currentIndex = 3;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 2));
}

/**
 * @tc.name: FocusStep003
 * @tc.desc: Test List focusing ability with lanes mode
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, FocusStep003, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetLanes(2);
    CreateFocusableListItems(6);
    CreateDone();

    /**
     * @tc.steps: step1. GetNextFocusNode from left item.
     */
    int32_t currentIndex = 2;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 1));

    /**
     * @tc.steps: step2. GetNextFocusNode from middle.
     */
    currentIndex = 3;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 2));
}

/**
 * @tc.name: FocusStep004
 * @tc.desc: Test List focusing ability with lanes mode and HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, FocusStep004, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetLanes(2);
    model.SetListDirection(Axis::HORIZONTAL);
    CreateFocusableListItems(6);
    CreateDone();

    /**
     * @tc.steps: step1. GetNextFocusNode from middle.
     */
    int32_t currentIndex = 3;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 2));
}

/**
 * @tc.name: FocusStep005
 * @tc.desc: Test GetNextFocusNode when List has ListItemGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, FocusStep005, TestSize.Level1)
{
    CreateList();
    CreateFocusableListItemGroups(2);
    CreateDone();

    /**
     * @tc.steps: step1. GetNextFocusNode in same group.
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_VALUE));
}

/**
 * @tc.name: FocusStep006
 * @tc.desc: Test List focusing ability with ListItemGroup and lanes mode
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, FocusStep006, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetLanes(2);
    CreateFocusableListItemGroups(2);
    CreateDone();

    /**
     * @tc.steps: step1. GetNextFocusNode with left item.
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_VALUE));

    /**
     * @tc.steps: step2. GetNextFocusNode in diff group.
     */
    currentIndex = 1;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 0));
}

/**
 * @tc.name: FocusStep007
 * @tc.desc: Test GetNextFocusNode other condition
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, FocusStep007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. when List has unFocusable item
     * @tc.expected: The unFocusable item would be skiped.
     */
    CreateList();
    CreateFocusableListItems(4);
    CreateDone();
    GetChildFocusHub(frameNode_, 1)->SetFocusable(false);
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, 0, 2));
}

/**
 * @tc.name: FocusStep008
 * @tc.desc: Test GetNextFocusNode other condition
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, FocusStep008, TestSize.Level1)
{
    /**
     * @tc.steps: step2. GetNextFocusNode func from top boundary item
     * @tc.expected: Scroll to last item
     */
    CreateList();
    CreateFocusableListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    UpdateCurrentOffset(-ITEM_MAIN_SIZE - 1.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_MAIN_SIZE + 1.f);
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, 1, 0));
    FlushUITasks();
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);

    /**
     * @tc.steps: step3. GetNextFocusNode func from bottom boundary item
     * @tc.expected: Scroll to next item
     */
    ClearOldNodes();
    CreateList();
    CreateFocusableListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, 3, 4));
    FlushUITasks();
    EXPECT_EQ(pattern_->GetTotalOffset(), 100);
}

/**
 * @tc.name: FocusStep009
 * @tc.desc: Test GetNextFocusNode other condition
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, FocusStep009, TestSize.Level1)
{
    /**
     * @tc.steps: step4. GetNextFocusNode func from bottom boundary item
     * @tc.expected: Scroll to next item
     */
    // change focus between different group
    const float groupHeight = ITEM_MAIN_SIZE * GROUP_ITEM_NUMBER;
    CreateList();
    CreateFocusableListItemGroups(3);
    CreateDone();
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, 3, 4));
    FlushUITasks();
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_MAIN_SIZE);
    // change focus in same group
    ClearOldNodes();
    CreateList();
    CreateFocusableListItemGroups(3);
    CreateDone();
    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_MAIN_SIZE);
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, 4, 5));
    FlushUITasks();
    EXPECT_EQ(pattern_->GetTotalOffset(), groupHeight / 2);

    /**
     * @tc.steps: step5. GetNextFocusNode func from top boundary item
     * @tc.expected: Scroll to next item
     */
    // change focus between different group
    ClearOldNodes();
    CreateList();
    CreateFocusableListItemGroups(3);
    CreateDone();
    ScrollTo(GROUP_ITEM_NUMBER * ITEM_MAIN_SIZE);
    EXPECT_EQ(pattern_->GetTotalOffset(), groupHeight);
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, 2, 1));
    FlushUITasks();
    EXPECT_EQ(pattern_->GetTotalOffset(), 100);
    // change focus in same group
    ClearOldNodes();
    CreateList();
    CreateFocusableListItemGroups(3);
    CreateDone();
    ScrollTo(ITEM_MAIN_SIZE);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_MAIN_SIZE);
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, 1, 0));
}

/**
 * @tc.name: KeyEvent001
 * @tc.desc: Test list_pattern OnKeyEvent function
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, KeyEvent001, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step1. Test other KeyEvent.
     * @tc.expected: CurrentOffset unchanged.
     */
    pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_UNKNOWN, KeyAction::UNKNOWN));
    FlushUITasks();
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);
    pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_UNKNOWN, KeyAction::DOWN));
    FlushUITasks();
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);

    /**
     * @tc.steps: step2. Test active KeyEvent.
     * @tc.expected: CurrentOffset changed.
     */
    pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_PAGE_DOWN, KeyAction::DOWN));
    FlushUITasks();
    EXPECT_EQ(pattern_->GetTotalOffset(), 400);
    pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_PAGE_UP, KeyAction::DOWN));
    FlushUITasks();
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);
}

/**
 * @tc.name: MouseSelect001
 * @tc.desc: Test mouse select
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, MouseSelect001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetMultiSelectable(true);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step1. Select item(index:0)
     * @tc.expected: The item(index:0) is selected
     */
    MouseSelect(Offset(0.f, 0.f), Offset(LIST_WIDTH, 50.f));
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 0)->IsSelected());
    std::vector<RefPtr<FrameNode>> expectSelectItems = { GetChildFrameNode(frameNode_, 0) };
    EXPECT_EQ(pattern_->GetVisibleSelectedItems(), expectSelectItems);

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
    std::vector<RefPtr<FrameNode>> expectSelectItems2 = { GetChildFrameNode(frameNode_, 1) };
    EXPECT_EQ(pattern_->GetVisibleSelectedItems(), expectSelectItems2);

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
    ListModelNG model = CreateList();
    model.SetMultiSelectable(true);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
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
    ListModelNG model = CreateList();
    model.SetListDirection(Axis::HORIZONTAL);
    model.SetMultiSelectable(true);
    CreateListItems(4);
    CreateDone();
    MouseSelect(RIGHT_TOP, LEFT_BOTTOM);
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 1)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 2)->IsSelected());
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
    ListModelNG model = CreateList();
    model.SetLanes(2);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
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
    ListModelNG model = CreateList();
    model.SetLanes(2);
    CreateListItemGroups(2);
    CreateDone();
    MouseSelect(RIGHT_BOTTOM, LEFT_TOP);
    std::vector<RefPtr<FrameNode>> listItems = GetFlatListItems(); // flat items
    EXPECT_TRUE(listItems[2]->GetPattern<ListItemPattern>()->IsSelected());
    EXPECT_TRUE(listItems[3]->GetPattern<ListItemPattern>()->IsSelected());
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
    ListModelNG model = CreateList();
    model.SetMultiSelectable(true);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    bool isSelected = false;
    auto selectCallback = [&isSelected](bool) { isSelected = true; };
    GetChildPattern<ListItemPattern>(frameNode_, 1)->SetSelectable(false);
    GetChildEventHub<ListItemEventHub>(frameNode_, 2)->SetEnabled(false);
    GetChildEventHub<ListItemEventHub>(frameNode_, 3)->SetOnSelect(std::move(selectCallback));

    /**
     * @tc.steps: step2. Select zone, include items(index:1,2,3).
     * @tc.expected: The item(index:1) is not selected, item(index:2) is selected,
     *               item(index:3) is selected, selectCallback is called.
     */
    MouseSelect(Offset(120.f, 150.f), Offset(360.f, 350.f));
    EXPECT_FALSE(GetChildPattern<ListItemPattern>(frameNode_, 1)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 2)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 3)->IsSelected());
    EXPECT_TRUE(isSelected);
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
    ListModelNG model = CreateList();
    model.SetMultiSelectable(true);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    MouseSelect(Offset(0.f, 0.f), Offset(1.f, 1.f));
    EXPECT_FALSE(GetChildPattern<ListItemPattern>(frameNode_, 0)->IsSelected());
}

/**
 * @tc.name: MouseSelect008
 * @tc.desc: Test mouse box selection start on Group Header
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, MouseSelect008, TestSize.Level1)
{
    /**
     * @tc.cases: Select from the item(index:5 RIGHT_BOTTOM) to the item(index:2 LEFT_TOP).
     * @tc.expected: The items(index:0,1,2,3,4,5) are selected.
     */
    ListModelNG model = CreateList();
    model.SetLanes(2);
    CreateGroupWithSetting(2, V2::ListItemGroupStyle::NONE);
    CreateDone();
    MouseSelect(Offset(0.f, 0.f), Offset(240.f, 150.f));           // start on header
    std::vector<RefPtr<FrameNode>> listItems = GetFlatListItems(); // flat items
    EXPECT_TRUE(listItems[0]->GetPattern<ListItemPattern>()->IsSelected());
    EXPECT_TRUE(listItems[1]->GetPattern<ListItemPattern>()->IsSelected());
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
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    EXPECT_TRUE(accessibilityProperty_->IsScrollable());
    EXPECT_EQ(accessibilityProperty_->GetBeginIndex(), 0);
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), 3);
    EXPECT_EQ(accessibilityProperty_->GetCollectionItemCounts(), TOTAL_ITEM_NUMBER);

    /**
     * @tc.steps: step2. scroll to second item
     */
    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_EQ(accessibilityProperty_->GetBeginIndex(), 1);
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), 4);

    /**
     * @tc.steps: step3. unScrollable List
     */
    ClearOldNodes();
    CreateList();
    CreateListItems(2);
    CreateDone();
    EXPECT_FALSE(accessibilityProperty_->IsScrollable());
    EXPECT_EQ(accessibilityProperty_->GetBeginIndex(), 0);
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), 1);
    EXPECT_EQ(accessibilityProperty_->GetCollectionItemCounts(), 2);
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
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    accessibilityProperty_->ResetSupportAction();
    uint64_t exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions);

    /**
     * @tc.steps: step2. Scroll to middle.
     */
    ScrollTo(ITEM_MAIN_SIZE);
    accessibilityProperty_->ResetSupportAction();
    exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions);

    /**
     * @tc.steps: step3. Scroll to bottom.
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    accessibilityProperty_->ResetSupportAction();
    exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions);

    /**
     * @tc.steps: step4. UnScrollable List.
     */
    ClearOldNodes();
    CreateList();
    CreateListItems(2);
    CreateDone();
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
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
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
    CreateList();
    CreateGroupWithSetting(GROUP_NUMBER, V2::ListItemGroupStyle::NONE);
    CreateDone();
    auto groupAccessibilityProperty =
        GetChildFrameNode(frameNode_, 0)->GetAccessibilityProperty<ListItemGroupAccessibilityProperty>();
    EXPECT_EQ(groupAccessibilityProperty->GetBeginIndex(), 0);
    EXPECT_EQ(groupAccessibilityProperty->GetEndIndex(), 1);

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
    CreateList();
    CreateListItems(2);
    CreateDone();
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
     * @tc.expected: can not scrollPage
     */
    CreateList();
    CreateListItems(2);
    CreateDone();
    accessibilityProperty_->ActActionScrollForward();
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);
    accessibilityProperty_->ActActionScrollBackward();
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);

    /**
     * @tc.steps: step2. When list is Scrollable
     * @tc.expected: can scrollPage
     */
    ClearOldNodes();
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    accessibilityProperty_->ActActionScrollForward();
    EXPECT_TRUE(TickPosition(-200));
    EXPECT_TRUE(TickPosition(-400));
    accessibilityProperty_->ActActionScrollBackward();
    EXPECT_TRUE(TickPosition(-200));
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: FRCCallback001
 * @tc.desc: Test FRC callback
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, FRCCallback001, TestSize.Level1)
{
    CreateList();
    CreateDone();
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
     * @tc.steps: step1. EXPECT_CALL GetWindowId, HandleOnItemDragStart will trigger it
     */
    auto container = Container::GetContainer(CONTAINER_ID_DIVIDE_SIZE);
    EXPECT_CALL(*(AceType::DynamicCast<MockContainer>(container)), GetWindowId()).Times(AnyNumber());

    /**
     * @tc.steps: step2. Run List GetDragExtraParams func.
     * @tc.expected: Would call pattern->GetItemIndexByPosition
     */
    auto onItemDragStart = [](const ItemDragInfo&, int32_t) {
        auto dragItem = AceType::MakeRefPtr<FrameNode>("test", 0, AceType::MakeRefPtr<Pattern>());
        return AceType::DynamicCast<UINode>(dragItem);
    };
    ListModelNG model = CreateList();
    model.SetOnItemDragStart(onItemDragStart);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
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
     * @tc.steps: step4. HandleOnItemDrag to cancel
     */
    eventHub_->HandleOnItemDragStart(info);
    EXPECT_EQ(eventHub_->draggedIndex_, 2);
    eventHub_->HandleOnItemDragUpdate(info);
    eventHub_->HandleOnItemDragCancel();
    EXPECT_EQ(eventHub_->draggedIndex_, 0);

    /**
     * @tc.steps: step5. Not drag on listItem
     * @tc.expected: Will not take effect
     */
    info.SetGlobalPoint(Point(LIST_WIDTH + 1.f, LIST_HEIGHT));
    eventHub_->HandleOnItemDragStart(info);
    EXPECT_EQ(eventHub_->draggedIndex_, -1);
}

/**
 * @tc.name: EventHub002
 * @tc.desc: Test ListItem Event hub
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, EventHub002, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
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
    ListModelNG model = CreateList();
    model.SetMultiSelectable(true);
    ListItemGroupModelNG groupModel;
    groupModel.Create(V2::ListItemGroupStyle::CARD);
    CreateListItems(GROUP_ITEM_NUMBER, V2::ListItemStyle::CARD);
    ViewStackProcessor::GetInstance()->Pop();
    CreateDone();
    RefPtr<FrameNode> group = GetChildFrameNode(frameNode_, 0);

    /**
     * @tc.steps: step1. Select zone.
     * @tc.expected: The item(index:0) was selected.
     */
    MouseSelect(Offset(0.f, 0.f), Offset(200.f, 50.f));
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(group, 0)->IsSelected());
    pattern_->ClearMultiSelect();

    /**
     * @tc.steps: step2. Change select zone.
     * @tc.expected: Selected items changed.
     */
    MouseSelect(Offset(0.f, 200.f), Offset(200.f, 150.f));
    EXPECT_FALSE(GetChildPattern<ListItemPattern>(group, 0)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(group, 1)->IsSelected());
    pattern_->ClearMultiSelect();

    /**
     * @tc.steps: step3. Click first item.
     * @tc.expected: Each item not selected.
     */
    MouseSelect(Offset(0.f, 10.f), Offset(0.f, 10.f));
    for (int32_t index = 0; index < GROUP_ITEM_NUMBER; index++) {
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
    ListModelNG model = CreateList();
    model.SetMultiSelectable(true);
    ListItemGroupModelNG groupModel;
    groupModel.Create(V2::ListItemGroupStyle::CARD);
    CreateListItems(GROUP_ITEM_NUMBER, V2::ListItemStyle::CARD);
    ViewStackProcessor::GetInstance()->Pop();
    CreateDone();
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
    ListModelNG model = CreateList();
    model.SetMultiSelectable(true);
    ListItemGroupModelNG groupModel;
    groupModel.Create(V2::ListItemGroupStyle::CARD);
    CreateListItems(5, V2::ListItemStyle::CARD);
    ViewStackProcessor::GetInstance()->Pop();
    CreateDone();
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
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

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

/**
 * @tc.name: ForEachDrag001
 * @tc.desc: Drag small delta to no change order
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, ForEachDrag001, TestSize.Level1)
{
    int32_t actualFrom = -1;
    int32_t actualTo = -1;
    auto onMoveEvent = [&actualFrom, &actualTo](int32_t from, int32_t to) {
        actualFrom = from;
        actualTo = to;
    };
    CreateForEachList(3, 1, onMoveEvent);
    CreateDone();

    /**
     * @tc.steps: step1. Drag item(index:0)
     */
    auto dragManager = GetForEachItemDragManager(0);
    GestureEvent info;
    dragManager->HandleOnItemDragStart(info);
    EXPECT_EQ(dragManager->fromIndex_, 0);

    /**
     * @tc.steps: step2. Drag dwon, delta <= ITEM_MAIN_SIZE/2
     * @tc.expected: No change of order
     */
    info.SetOffsetX(0.0);
    info.SetOffsetY(50.0);
    info.SetGlobalPoint(Point(0.f, 50.f));
    dragManager->HandleOnItemDragUpdate(info);
    FlushUITasks();
    EXPECT_TRUE(VerifyForEachItemsOrder({ "0", "1", "2" }));

    /**
     * @tc.steps: step3. Drag end
     * @tc.expected: No trigger onMoveEvent
     */
    dragManager->HandleOnItemDragEnd(info);
    EXPECT_EQ(actualFrom, -1);
    EXPECT_EQ(actualTo, -1);

    /**
     * @tc.steps: step4. Drag item(index:1)
     */
    dragManager = GetForEachItemDragManager(1);
    dragManager->HandleOnItemDragStart(info);
    EXPECT_EQ(dragManager->fromIndex_, 1);

    /**
     * @tc.steps: step5. Drag up, delta <= ITEM_MAIN_SIZE/2
     * @tc.expected: No change of order
     */
    info.SetOffsetX(0.0);
    info.SetOffsetY(-50.0);
    info.SetGlobalPoint(Point(0.f, 50.f));
    dragManager->HandleOnItemDragUpdate(info);
    FlushUITasks();
    EXPECT_TRUE(VerifyForEachItemsOrder({ "0", "1", "2" }));

    /**
     * @tc.steps: step6. Drag end
     * @tc.expected: No trigger onMoveEvent
     */
    dragManager->HandleOnItemDragEnd(info);
    EXPECT_EQ(actualFrom, -1);
    EXPECT_EQ(actualTo, -1);
}

/**
 * @tc.name: ForEachDrag002
 * @tc.desc: Drag to reachEnd, will scroll
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, ForEachDrag002, TestSize.Level1)
{
    auto onMoveEvent = [](int32_t, int32_t) {};
    CreateForEachList(TOTAL_ITEM_NUMBER, 1, onMoveEvent);
    CreateDone();

    /**
     * @tc.steps: step1. Drag to the end of view
     * @tc.expected: Will scroll with animation
     */
    auto dragManager = GetForEachItemDragManager(1);
    GestureEvent info;
    dragManager->HandleOnItemDragStart(info);
    info.SetOffsetX(0.0);
    info.SetOffsetY(51.0);
    info.SetGlobalPoint(Point(0.f, 351.f));
    dragManager->HandleOnItemDragUpdate(info);
    dragManager->HandleScrollCallback();
    FlushUITasks();
    EXPECT_TRUE(dragManager->scrolling_);
    EXPECT_TRUE(pattern_->animator_->IsRunning());
    dragManager->HandleOnItemDragEnd(info);
    EXPECT_FALSE(dragManager->scrolling_);
    EXPECT_TRUE(pattern_->animator_->IsStopped());

    /**
     * @tc.steps: step2. Drag to the start of view
     * @tc.expected: Will scroll with animation
     */
    ScrollTo(200.f);
    dragManager = GetForEachItemDragManager(2);
    dragManager->HandleOnItemDragStart(info);
    info.SetOffsetX(0.0);
    info.SetOffsetY(-51.0);
    info.SetGlobalPoint(Point(0.f, 49.f));
    dragManager->HandleOnItemDragUpdate(info);
    dragManager->HandleScrollCallback();
    FlushUITasks();
    EXPECT_TRUE(dragManager->scrolling_);
    EXPECT_TRUE(pattern_->animator_->IsRunning());
    dragManager->HandleOnItemDragEnd(info);
    EXPECT_FALSE(dragManager->scrolling_);
    EXPECT_TRUE(pattern_->animator_->IsStopped());
}

/**
 * @tc.name: ForEachDrag003
 * @tc.desc: Drag big delta to change order
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, ForEachDrag003, TestSize.Level1)
{
    int32_t actualFrom = -1;
    int32_t actualTo = -1;
    auto onMoveEvent = [&actualFrom, &actualTo](int32_t from, int32_t to) {
        actualFrom = from;
        actualTo = to;
    };
    CreateForEachList(3, 1, onMoveEvent);
    CreateDone();

    /**
     * @tc.steps: step1. Drag item(index:0) without long press
     * @tc.expected: Item has scale
     */
    auto dragManager = GetForEachItemDragManager(0);
    GestureEvent info;
    dragManager->HandleOnItemDragStart(info);
    EXPECT_EQ(dragManager->fromIndex_, 0);
    auto host = dragManager->GetHost();
    auto renderContext = host->GetRenderContext();
    auto scale = renderContext->GetTransformScaleValue({ 1.0f, 1.0f });
    EXPECT_EQ(scale, VectorF(1.05f, 1.05f));

    /**
     * @tc.steps: step2. Drag down delta > ITEM_MAIN_SIZE/2
     * @tc.expected: Change of order
     */
    info.SetOffsetX(0.0);
    info.SetOffsetY(51.0);
    info.SetGlobalPoint(Point(0.f, 51.f));
    dragManager->HandleOnItemDragUpdate(info);
    FlushUITasks();
    EXPECT_TRUE(VerifyForEachItemsOrder({ "1", "0", "2" }));

    /**
     * @tc.steps: step3. Drag down delta > ITEM_MAIN_SIZE
     * @tc.expected: Continue change of order
     */
    info.SetOffsetX(0.0);
    info.SetOffsetY(151.0);
    info.SetGlobalPoint(Point(0.f, 151.f));
    dragManager->HandleOnItemDragUpdate(info);
    FlushUITasks();
    EXPECT_TRUE(VerifyForEachItemsOrder({ "1", "2", "0" }));

    /**
     * @tc.steps: step4. Drag end
     * @tc.expected: Trigger onMoveEvent
     */
    dragManager->HandleOnItemDragEnd(info);
    EXPECT_EQ(actualFrom, 0);
    EXPECT_EQ(actualTo, 2);

    /**
     * @tc.steps: step5. Drag item(index:2)
     */
    dragManager = GetForEachItemDragManager(2);
    dragManager->HandleOnItemDragStart(info);
    EXPECT_EQ(dragManager->fromIndex_, 2);

    /**
     * @tc.steps: step6. Drag up delta > ITEM_MAIN_SIZE/2
     * @tc.expected: Change of order
     */
    info.SetOffsetX(0.0);
    info.SetOffsetY(-51.0);
    info.SetGlobalPoint(Point(0.f, 149.f));
    dragManager->HandleOnItemDragUpdate(info);
    FlushUITasks();
    EXPECT_TRUE(VerifyForEachItemsOrder({ "1", "0", "2" }));

    /**
     * @tc.steps: step7. Drag up delta > ITEM_MAIN_SIZE
     * @tc.expected: Continue change of order
     */
    info.SetOffsetX(0.0);
    info.SetOffsetY(-151.0);
    info.SetGlobalPoint(Point(0.f, 49.f));
    dragManager->HandleOnItemDragUpdate(info);
    FlushUITasks();
    EXPECT_TRUE(VerifyForEachItemsOrder({ "0", "1", "2" }));

    /**
     * @tc.steps: step8. Drag end
     * @tc.expected: Trigger onMoveEvent
     */
    dragManager->HandleOnItemDragEnd(info);
    EXPECT_EQ(actualFrom, 2);
    EXPECT_EQ(actualTo, 0);
}

/**
 * @tc.name: ForEachDrag004
 * @tc.desc: Drag with 2 lanes list
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, ForEachDrag004, TestSize.Level1)
{
    int32_t actualFrom = -1;
    int32_t actualTo = -1;
    auto onMoveEvent = [&actualFrom, &actualTo](int32_t from, int32_t to) {
        actualFrom = from;
        actualTo = to;
    };
    CreateForEachList(4, 2, onMoveEvent); // 2 lanes
    CreateDone();

    /**
     * @tc.steps: step1. Drag item(index:0)
     */
    auto dragManager = GetForEachItemDragManager(0);
    GestureEvent info;
    dragManager->HandleOnItemDragStart(info);
    EXPECT_EQ(dragManager->fromIndex_, 0);

    /**
     * @tc.steps: step2. Drag down delta > ITEM_MAIN_SIZE/2
     * @tc.expected: Change of order
     */
    info.SetOffsetX(0.0);
    info.SetOffsetY(51.0);
    info.SetGlobalPoint(Point(0.f, 51.f));
    dragManager->HandleOnItemDragUpdate(info);
    FlushUITasks();
    EXPECT_TRUE(VerifyForEachItemsOrder({ "1", "2", "0" }));

    /**
     * @tc.steps: step3. Drag right-up delta > half size
     * @tc.expected: Continue change of order
     */
    info.SetOffsetX(121.0);
    info.SetOffsetY(0.0);
    info.SetGlobalPoint(Point(121.f, 0.f));
    dragManager->HandleOnItemDragUpdate(info);
    FlushUITasks();
    EXPECT_TRUE(VerifyForEachItemsOrder({ "1", "0", "2" }));

    /**
     * @tc.steps: step4. Drag left delta > itemWidth/2
     * @tc.expected: Continue change of order
     */
    info.SetOffsetX(0.0);
    info.SetOffsetY(0.0);
    info.SetGlobalPoint(Point(0.f, 0.f));
    dragManager->HandleOnItemDragUpdate(info);
    FlushUITasks();
    EXPECT_TRUE(VerifyForEachItemsOrder({ "0", "1", "2" }));

    /**
     * @tc.steps: step5. Drag end
     * @tc.expected: No trigger onMoveEvent
     */
    dragManager->HandleOnItemDragEnd(info);
    EXPECT_EQ(actualFrom, -1);
    EXPECT_EQ(actualTo, -1);
}

/**
 * @tc.name: ForEachDrag005
 * @tc.desc: Drag with 2 lanes list, but items number is 3, test oblique drag direction
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, ForEachDrag005, TestSize.Level1)
{
    auto onMoveEvent = [](int32_t, int32_t) {};
    CreateForEachList(3, 2, onMoveEvent); // 2 lanes but 3 items
    CreateDone();

    /**
     * @tc.steps: step1. Drag item(index:1)
     */
    auto dragManager = GetForEachItemDragManager(1);
    GestureEvent info;
    dragManager->HandleOnItemDragStart(info);
    EXPECT_EQ(dragManager->fromIndex_, 1);

    /**
     * @tc.steps: step2. Drag left-down delta > half size
     * @tc.expected: Will change left order, than change down order
     */
    info.SetOffsetX(-121.0);
    info.SetOffsetY(51.0);
    info.SetGlobalPoint(Point(119.f, 51.f));
    dragManager->HandleOnItemDragUpdate(info);
    FlushUITasks();
    EXPECT_TRUE(VerifyForEachItemsOrder({ "1", "0", "2" }));

    dragManager->HandleOnItemDragUpdate(info);
    FlushUITasks();
    EXPECT_TRUE(VerifyForEachItemsOrder({ "0", "2", "1" }));
}

/**
 * @tc.name: ForEachDrag006
 * @tc.desc: Do not set onMoveEvent, could not drag
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, ForEachDrag006, TestSize.Level1)
{
    CreateForEachList(1, 1, nullptr);
    CreateDone();
    auto forEachNode = AceType::DynamicCast<ForEachNode>(frameNode_->GetChildAtIndex(0));
    auto syntaxItem = AceType::DynamicCast<SyntaxItem>(forEachNode->GetChildAtIndex(0));
    auto listItem = AceType::DynamicCast<FrameNode>(syntaxItem->GetChildAtIndex(0));
    auto listItemEventHub = listItem->GetEventHub<ListItemEventHub>();
    auto gestureHub = listItemEventHub->GetOrCreateGestureEventHub();
    EXPECT_EQ(gestureHub->GetDragEventActuator(), nullptr);
}

/**
 * @tc.name: ForEachDrag007
 * @tc.desc: Remove onMove event, can not drag
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, ForEachDrag007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set onMoveEvent
     * @tc.expected: dragEvent init
     */
    auto onMoveEvent = [](int32_t, int32_t) {};
    CreateForEachList(3, 2, onMoveEvent);
    CreateDone();
    auto forEachNode = AceType::DynamicCast<ForEachNode>(frameNode_->GetChildAtIndex(0));
    auto syntaxItem = AceType::DynamicCast<SyntaxItem>(forEachNode->GetChildAtIndex(0));
    auto listItem = AceType::DynamicCast<FrameNode>(syntaxItem->GetChildAtIndex(0));
    auto listItemEventHub = listItem->GetEventHub<ListItemEventHub>();
    auto gestureHub = listItemEventHub->GetOrCreateGestureEventHub();
    EXPECT_NE(gestureHub->GetDragEventActuator()->userCallback_, nullptr);

    /**
     * @tc.steps: step2. Set onMoveEvent to null
     * @tc.expected: dragEvent uninit
     */
    CreateForEachList(3, 2, nullptr);
    CreateDone();
    forEachNode = AceType::DynamicCast<ForEachNode>(frameNode_->GetChildAtIndex(0));
    syntaxItem = AceType::DynamicCast<SyntaxItem>(forEachNode->GetChildAtIndex(0));
    listItem = AceType::DynamicCast<FrameNode>(syntaxItem->GetChildAtIndex(0));
    listItemEventHub = listItem->GetEventHub<ListItemEventHub>();
    gestureHub = listItemEventHub->GetOrCreateGestureEventHub();
    EXPECT_NE(gestureHub->GetDragEventActuator()->userCallback_, nullptr);
}

/**
 * @tc.name: LazyForEachDrag001
 * @tc.desc: Drag big delta to change order
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, LazyForEachDrag001, TestSize.Level1)
{
    int32_t actualFrom = -1;
    int32_t actualTo = -1;
    auto onMoveEvent = [&actualFrom, &actualTo](int32_t from, int32_t to) {
        actualFrom = from;
        actualTo = to;
    };
    CreateLazyForEachList(3, 1, onMoveEvent);
    CreateDone();

    /**
     * @tc.steps: step1. Drag item(index:0)
     */
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(frameNode_->GetChildAtIndex(0));
    auto dragManager = GetLazyForEachItemDragManager(0);
    GestureEvent info;
    dragManager->HandleOnItemDragStart(info);
    EXPECT_EQ(dragManager->fromIndex_, 0);

    /**
     * @tc.steps: step2. Drag down delta > ITEM_MAIN_SIZE/2
     * @tc.expected: Change of order
     */
    info.SetOffsetX(0.0);
    info.SetOffsetY(51.0);
    info.SetGlobalPoint(Point(0.f, 51.f));
    dragManager->HandleOnItemDragUpdate(info);
    FlushUITasks();
    EXPECT_TRUE(VerifyLazyForEachItemsOrder({ "1", "0", "2" }));

    /**
     * @tc.steps: step3. Drag down delta > ITEM_MAIN_SIZE
     * @tc.expected: Continue change of order
     */
    info.SetOffsetX(0.0);
    info.SetOffsetY(151.0);
    info.SetGlobalPoint(Point(0.f, 151.f));
    dragManager->HandleOnItemDragUpdate(info);
    FlushUITasks();
    EXPECT_TRUE(VerifyLazyForEachItemsOrder({ "1", "2", "0" }));

    /**
     * @tc.steps: step4. Drag end
     * @tc.expected: Trigger onMoveEvent
     */
    dragManager->HandleOnItemDragEnd(info);
    EXPECT_EQ(actualFrom, 0);
    EXPECT_EQ(actualTo, 2);

    /**
     * @tc.steps: step5. Drag item(index:2)
     */
    dragManager = GetLazyForEachItemDragManager(2);
    dragManager->HandleOnItemDragStart(info);
    EXPECT_EQ(dragManager->fromIndex_, 2);

    /**
     * @tc.steps: step6. Drag up delta > ITEM_MAIN_SIZE/2
     * @tc.expected: Change of order
     */
    info.SetOffsetX(0.0);
    info.SetOffsetY(-51.0);
    info.SetGlobalPoint(Point(0.f, 149.f));
    dragManager->HandleOnItemDragUpdate(info);
    FlushUITasks();
    EXPECT_TRUE(VerifyLazyForEachItemsOrder({ "1", "0", "2" }));

    /**
     * @tc.steps: step7. Drag up delta > ITEM_MAIN_SIZE
     * @tc.expected: Continue change of order
     */
    info.SetOffsetX(0.0);
    info.SetOffsetY(-151.0);
    info.SetGlobalPoint(Point(0.f, 49.f));
    dragManager->HandleOnItemDragUpdate(info);
    FlushUITasks();
    EXPECT_TRUE(VerifyLazyForEachItemsOrder({ "0", "1", "2" }));

    /**
     * @tc.steps: step8. Drag end
     * @tc.expected: Trigger onMoveEvent
     */
    dragManager->HandleOnItemDragEnd(info);
    EXPECT_EQ(actualFrom, 2);
    EXPECT_EQ(actualTo, 0);
}

/**
 * @tc.name: LazyForEachDrag002
 * @tc.desc: Drag with 2 lanes list
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, LazyForEachDrag002, TestSize.Level1)
{
    int32_t actualFrom = -1;
    int32_t actualTo = -1;
    auto onMoveEvent = [&actualFrom, &actualTo](int32_t from, int32_t to) {
        actualFrom = from;
        actualTo = to;
    };
    CreateLazyForEachList(4, 2, onMoveEvent); // 2 lanes
    CreateDone();

    /**
     * @tc.steps: step1. Drag item(index:0)
     */
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(frameNode_->GetChildAtIndex(0));
    auto dragManager = GetLazyForEachItemDragManager(0);
    GestureEvent info;
    dragManager->HandleOnItemDragStart(info);
    EXPECT_EQ(dragManager->fromIndex_, 0);

    /**
     * @tc.steps: step2. Drag down delta > ITEM_MAIN_SIZE/2
     * @tc.expected: Change of order
     */
    info.SetOffsetX(0.0);
    info.SetOffsetY(51.0);
    info.SetGlobalPoint(Point(0.f, 51.f));
    dragManager->HandleOnItemDragUpdate(info);
    FlushUITasks();
    EXPECT_TRUE(VerifyLazyForEachItemsOrder({ "1", "2", "0" }));

    /**
     * @tc.steps: step3. Drag right-up delta > half size
     * @tc.expected: Continue change of order
     */
    info.SetOffsetX(121.0);
    info.SetOffsetY(0.0);
    info.SetGlobalPoint(Point(121.f, 0.f));
    dragManager->HandleOnItemDragUpdate(info);
    FlushUITasks();
    EXPECT_TRUE(VerifyLazyForEachItemsOrder({ "1", "0", "2" }));

    /**
     * @tc.steps: step4. Drag left delta > itemWidth/2
     * @tc.expected: Continue change of order
     */
    info.SetOffsetX(0.0);
    info.SetOffsetY(0.0);
    info.SetGlobalPoint(Point(0.f, 0.f));
    dragManager->HandleOnItemDragUpdate(info);
    FlushUITasks();
    EXPECT_TRUE(VerifyLazyForEachItemsOrder({ "0", "1", "2" }));

    /**
     * @tc.steps: step5. Drag end
     * @tc.expected: No trigger onMoveEvent
     */
    dragManager->HandleOnItemDragEnd(info);
    EXPECT_EQ(actualFrom, -1);
    EXPECT_EQ(actualTo, -1);
}

/**
 * @tc.name: InitDragDropEvent001
 * @tc.desc: Test InitDragDropEvent, if already init, will not create dragEvent again
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, InitDragDropEvent001, TestSize.Level1)
{
    auto onMoveEvent = [](int32_t from, int32_t to) {};
    CreateForEachList(3, 1, onMoveEvent);
    CreateDone();

    /**
     * @tc.steps: step1. InitDragDropEvent, if already init, will not create dragEvent again
     */
    auto forEachNode = AceType::DynamicCast<ForEachNode>(frameNode_->GetChildAtIndex(0));
    auto syntaxItem = AceType::DynamicCast<SyntaxItem>(forEachNode->GetChildAtIndex(0));
    auto listItem = AceType::DynamicCast<FrameNode>(syntaxItem->GetChildAtIndex(0));
    auto listItemPattern = listItem->GetPattern<ListItemPattern>();
    auto dragManager = listItemPattern->dragManager_;
    auto listItemEventHub = listItem->GetEventHub<ListItemEventHub>();
    auto gestureHub = listItemEventHub->GetOrCreateGestureEventHub();
    // InitDragDropEvent
    auto dragEvent = gestureHub->dragEventActuator_->userCallback_;
    dragManager->InitDragDropEvent();
    EXPECT_EQ(dragEvent, gestureHub->dragEventActuator_->userCallback_);
}

/**
 * @tc.name: HandleOnItemLongPress001
 * @tc.desc: Test HandleOnItemLongPress
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, HandleOnItemLongPress001, TestSize.Level1)
{
    auto onMoveEvent = [](int32_t from, int32_t to) {};
    CreateForEachList(3, 1, onMoveEvent);
    CreateDone();

    auto dragManager = GetForEachItemDragManager(0);
    GestureEvent info;
    dragManager->HandleOnItemLongPress(info);
    EXPECT_EQ(dragManager->prevScale_, VectorF(1.f, 1.f));
    EXPECT_EQ(dragManager->prevShadow_, ShadowConfig::NoneShadow);

    auto listItem = dragManager->GetHost();
    auto renderContext = listItem->GetRenderContext();
    renderContext->UpdateTransformScale(VectorF(2.f, 2.f));
    renderContext->UpdateBackShadow(ShadowConfig::DefaultShadowXS);
    dragManager->HandleOnItemLongPress(info);
    EXPECT_EQ(dragManager->prevScale_, VectorF(2.f, 2.f));
    EXPECT_EQ(dragManager->prevShadow_, ShadowConfig::DefaultShadowXS);
}

/**
 * @tc.name: OnColorConfigurationUpdate001
 * @tc.desc: Test OnColorConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, OnColorConfigurationUpdate001, TestSize.Level1)
{
    CreateList();
    CreateListItemGroups(1, V2::ListItemGroupStyle::CARD);
    CreateListItemGroups(1, V2::ListItemGroupStyle::NONE);
    CreateDone();

    /**
     * @tc.steps: step1. CARD
     */
    auto firstGroup = GetChildFrameNode(frameNode_, 0);
    auto firstGroupRender = firstGroup->GetRenderContext();
    auto firstGroupPattern = firstGroup->GetPattern();
    auto firstGroupItem = GetChildFrameNode(firstGroup, 0);
    auto firstGroupItemRender = firstGroupItem->GetRenderContext();
    auto firstGroupItemPattern = firstGroupItem->GetPattern();
    EXPECT_EQ(firstGroupRender->GetBackgroundColor(), Color::WHITE);
    EXPECT_EQ(firstGroupItemRender->GetBackgroundColor(), Color::WHITE);
    auto listItemTheme = MockPipelineContext::pipeline_->GetTheme<ListItemTheme>();
    listItemTheme->defaultColor_ = Color::RED;
    listItemTheme->itemDefaultColor_ = Color::RED;
    firstGroupPattern->OnColorConfigurationUpdate();
    firstGroupItemPattern->OnColorConfigurationUpdate();
    EXPECT_EQ(firstGroupRender->GetBackgroundColor(), Color::RED);
    EXPECT_EQ(firstGroupItemRender->GetBackgroundColor(), Color::RED);

    /**
     * @tc.steps: step1. NONE
     */
    auto secondGroup = GetChildFrameNode(frameNode_, 1);
    auto secondGroupRender = secondGroup->GetRenderContext();
    auto secondGroupPattern = secondGroup->GetPattern();
    auto secondGroupItem = GetChildFrameNode(secondGroup, 0);
    auto secondGroupItemRender = secondGroupItem->GetRenderContext();
    auto secondGroupItemPattern = secondGroupItem->GetPattern();
    EXPECT_FALSE(secondGroupRender->GetBackgroundColor().has_value());
    EXPECT_FALSE(secondGroupItemRender->GetBackgroundColor().has_value());
    secondGroupPattern->OnColorConfigurationUpdate();
    secondGroupItemPattern->OnColorConfigurationUpdate();
    EXPECT_FALSE(secondGroupRender->GetBackgroundColor().has_value());
    EXPECT_FALSE(secondGroupItemRender->GetBackgroundColor().has_value());
    // reset theme
    listItemTheme->defaultColor_ = Color::WHITE;
    listItemTheme->itemDefaultColor_ = Color::WHITE;
}

/**
 * @tc.name: GetScrollIndexAbility001
 * @tc.desc: Test GetScrollIndexAbility
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, GetScrollIndexAbility001, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step1. FocusHub::SCROLL_TO_TAIL
     * @tc.expected: Scroll to end
     */
    auto scrollIndexAbility = pattern_->GetScrollIndexAbility();
    scrollIndexAbility(FocusHub::SCROLL_TO_TAIL);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetTotalOffset(), 600);

    /**
     * @tc.steps: step2. FocusHub::SCROLL_TO_HEAD
     * @tc.expected: Scroll to start
     */
    scrollIndexAbility(FocusHub::SCROLL_TO_HEAD);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetTotalOffset(), 0.f);

    /**
     * @tc.steps: step3. Other index
     * @tc.expected: Scroll to the item(index)
     */
    scrollIndexAbility(4);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_MAIN_SIZE);
}

/**
 * @tc.name: GetCurrentOffset001
 * @tc.desc: Test GetCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, GetCurrentOffset001, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step1. GetCurrentOffset
     */
    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_TRUE(IsEqual(pattern_->GetCurrentOffset(), Offset(0.0, ITEM_MAIN_SIZE)));

    /**
     * @tc.steps: step2. Set HORIZONTAL, GetCurrentOffset
     */
    ScrollTo(0.f); // reset position
    layoutProperty_->UpdateListDirection(Axis::HORIZONTAL);
    frameNode_->MarkModifyDone();
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_TRUE(IsEqual(pattern_->GetCurrentOffset(), Offset(ITEM_MAIN_SIZE, 0.0)));
}

/**
 * @tc.name: OnAnimateStop001
 * @tc.desc: Test OnAnimateStop
 * @tc.type: FUNC
 */
HWTEST_F(ListCommonTestNg, OnAnimateStop001, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    pattern_->scrollStop_ = false;
    pattern_->OnAnimateStop();
    EXPECT_TRUE(pattern_->scrollStop_);

    pattern_->scrollStop_ = false;
    pattern_->scrollableEvent_->GetScrollable()->isDragging_ = true;
    pattern_->OnAnimateStop();
    EXPECT_FALSE(pattern_->scrollStop_);

    pattern_->scrollStop_ = false;
    pattern_->scrollAbort_ = true;
    pattern_->OnAnimateStop();
    EXPECT_TRUE(pattern_->scrollStop_);

    pattern_->scrollStop_ = false;
    pattern_->scrollAbort_ = false;
    pattern_->OnAnimateStop();
    EXPECT_FALSE(pattern_->scrollStop_);
}
} // namespace OHOS::Ace::NG
