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

#include "arc_list_test_ng.h"

namespace OHOS::Ace::NG {

namespace {
const Offset LEFT_TOP = Offset(120.f, 150.f);
const Offset LEFT_BOTTOM = Offset(120.f, 250.f);
const Offset RIGHT_TOP = Offset(360.f, 150.f);
const Offset RIGHT_BOTTOM = Offset(360.f, 250.f);
} // namespace

class ArcListCommonTestNg : public ArcListTestNg {
public:
    void CreateFocusableListItems(int32_t itemNumber);
    AssertionResult IsEqualNextFocusNode(FocusStep step, int32_t currentIndex, int32_t expectNextIndex);
    AssertionResult VerifyForEachItemsOrder(std::list<std::string> expectKeys);
    AssertionResult VerifyLazyForEachItemsOrder(std::list<std::string> expectKeys);
};

void ArcListCommonTestNg::CreateFocusableListItems(int32_t itemNumber)
{
    for (int32_t index = 0; index < itemNumber; index++) {
        CreateListItem();
        {
            ButtonModelNG buttonModelNG;
            buttonModelNG.CreateWithLabel("label");
            ViewStackProcessor::GetInstance()->Pop();
        }
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
}

AssertionResult ArcListCommonTestNg::IsEqualNextFocusNode(FocusStep step, int32_t currentIndex, int32_t expectNextIndex)
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

AssertionResult ArcListCommonTestNg::VerifyForEachItemsOrder(std::list<std::string> expectKeys)
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

AssertionResult ArcListCommonTestNg::VerifyLazyForEachItemsOrder(std::list<std::string> expectKeys)
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

/**
 * @tc.name: FocusStep001
 * @tc.desc: Test GetNextFocusNode func
 * @tc.type: FUNC
 */
HWTEST_F(ArcListCommonTestNg, FocusStep001, TestSize.Level1)
{
    CreateList();
    CreateFocusableListItems(VIEW_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step1. GetNextFocusNode from first item
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_VALUE));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_VALUE));
    EXPECT_FALSE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_VALUE));
    EXPECT_FALSE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 3));
    EXPECT_FALSE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_VALUE));
}

/**
 * @tc.name: FocusStep006
 * @tc.desc: Test GetNextFocusNode other condition
 * @tc.type: FUNC
 */
HWTEST_F(ArcListCommonTestNg, FocusStep006, TestSize.Level1)
{
    CreateList();
    CreateFocusableListItems(VIEW_ITEM_NUMBER);
    CreateDone();
    GetChildFocusHub(frameNode_, 1)->SetFocusable(false);
    EXPECT_FALSE(IsEqualNextFocusNode(FocusStep::DOWN, 0, 2));
}

/**
 * @tc.name: FocusStep007
 * @tc.desc: Test GetNextFocusNode other condition
 * @tc.type: FUNC
 */
HWTEST_F(ArcListCommonTestNg, FocusStep007, TestSize.Level1)
{
    CreateList();
    CreateFocusableListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    UpdateCurrentOffset(-(TOTAL_ITEM_NUMBER * ITEM_HEIGHT - ITEM_HEIGHT));

    EXPECT_TRUE(IsEqualTotalOffset(TOTAL_ITEM_NUMBER * ITEM_HEIGHT - (VIEW_ITEM_NUMBER + 1) * ITEM_HEIGHT / 2.f));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, 1, 0));
    EXPECT_TRUE(IsEqualTotalOffset(-(VIEW_ITEM_NUMBER - 1) * ITEM_HEIGHT / 2.f));

    ClearOldNodes();
    CreateList();
    CreateFocusableListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    EXPECT_TRUE(IsEqualTotalOffset(-(VIEW_ITEM_NUMBER - 1) * ITEM_HEIGHT / 2.f));
    EXPECT_FALSE(IsEqualNextFocusNode(FocusStep::DOWN, 3, 4));
    EXPECT_FALSE(IsEqualTotalOffset(ITEM_HEIGHT * 4 + ITEM_HEIGHT / 2.f - VIEW_ITEM_NUMBER * ITEM_HEIGHT / 2.f));
}

/**
 * @tc.name: AccessibilityProperty001
 * @tc.desc: Test Arc_list AccessibilityProperty func
 * @tc.type: FUNC
 */
HWTEST_F(ArcListCommonTestNg, AccessibilityProperty001, TestSize.Level1)
{
    CreateList();
    CreateListItems(VIEW_ITEM_NUMBER);
    CreateDone();
    EXPECT_TRUE(accessibilityProperty_->IsScrollable());
    EXPECT_EQ(accessibilityProperty_->GetBeginIndex(), -1);
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), -1);
    EXPECT_EQ(accessibilityProperty_->GetCollectionItemCounts(), 1);
}

/**
 * @tc.name: AccessibilityProperty002
 * @tc.desc: Test Arc_list SetSpecificSupportAction when scroll to middle
 * @tc.type: FUNC
 */
HWTEST_F(ArcListCommonTestNg, AccessibilityProperty002, TestSize.Level1)
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
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions * 3);

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
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions);

    /**
     * @tc.steps: step4. UnScrollable List.
     */
    ClearOldNodes();
    CreateList();
    CreateListItems(VIEW_ITEM_NUMBER);
    CreateDone();
    accessibilityProperty_->ResetSupportAction();
    exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions * 3);
}

/**
 * @tc.name: PerformActionTest002
 * @tc.desc: Arc_list Accessibility PerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(ArcListCommonTestNg, PerformActionTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. When arc_list is not Scrollable
     * @tc.expected: can not scrollpage
     */
    CreateList();
    CreateListItems(VIEW_ITEM_NUMBER);
    CreateDone();
    accessibilityProperty_->ActActionScrollForward();
    EXPECT_FALSE(IsEqualTotalOffset(150.f));
    accessibilityProperty_->ActActionScrollBackward();
    EXPECT_TRUE(IsEqualTotalOffset(-150.f));

    /**
     * @tc.steps: step2. When arc_list is Scrollable
     * @tc.expected: can scrollpage
     */
    ClearOldNodes();
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    accessibilityProperty_->ActActionScrollForward();
    EXPECT_FALSE(IsEqualTotalOffset(250.f));
    accessibilityProperty_->ActActionScrollBackward();
    EXPECT_TRUE(IsEqualTotalOffset(-150.f));
}

/**
 * @tc.name: FRCCallback001
 * @tc.desc: Test FRC callback
 * @tc.type: FUNC
 */
HWTEST_F(ArcListCommonTestNg, FRCCallback001, TestSize.Level1)
{
    CreateList();
    CreateDone();
    // CalcExpectedFrameRate will be called
    pattern_->NotifyFRCSceneInfo("", 0.0f, SceneStatus::START);
}

/**
 * @tc.name: EventHub002
 * @tc.desc: Test ArcListItem Event hub
 * @tc.type: FUNC
 */
HWTEST_F(ArcListCommonTestNg, EventHub002, TestSize.Level1)
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
} // namespace OHOS::Ace::NG
