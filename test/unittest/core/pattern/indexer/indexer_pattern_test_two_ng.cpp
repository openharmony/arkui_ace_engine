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

#include "indexer_test_ng.h"

#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/indexer/arc_indexer_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/list/list_event_hub.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
class IndexerPatternTestTwoNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void IndexerPatternTestTwoNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
}

void IndexerPatternTestTwoNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: GetCurrentIndex001
 * @tc.desc: Test GetCurrentIndex
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, GetCurrentIndex001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<IndexerAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    pattern->selected_ = 10;
    auto index = accessibilityProperty->GetCurrentIndex();
    EXPECT_EQ(index, 10);
}

/**
 * @tc.name: SetActionClearSelection001
 * @tc.desc: Test SetActionClearSelection
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, SetActionClearSelection001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    auto count = 0;
    auto callback = [&count]() { count++; };
    accessibilityProperty->SetActionClearSelection(callback);

    pattern->SetActionClearSelection(frameNode, accessibilityProperty);

    EXPECT_EQ(count, 1);
}

/**
 * @tc.name: SetActionSelect001
 * @tc.desc: Test SetActionSelect
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, SetActionSelect001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    auto count = 0;
    auto callback = [&count]() { count++; };
    accessibilityProperty->SetActionSelect(callback);

    pattern->SetActionSelect(frameNode, accessibilityProperty);

    EXPECT_EQ(count, 1);
}

/**
 * @tc.name: GenerateAnimationId001
 * @tc.desc: Test GenerateAnimationId
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, GenerateAnimationId001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto index = pattern->GenerateAnimationId();

    EXPECT_EQ(index, 1);
}

/**
 * @tc.name: NeedShowPopupView001
 * @tc.desc: Test NeedShowPopupView
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, NeedShowPopupView001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->popupNode_ = FrameNode::CreateFrameNode("popup", 1, AceType::MakeRefPtr<IndexerPattern>());

    auto res = pattern->NeedShowPopupView();

    EXPECT_TRUE(res);
}

/**
 * @tc.name: NeedShowPopupView002
 * @tc.desc: Test NeedShowPopupView
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, NeedShowPopupView002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto res = pattern->NeedShowPopupView();

    EXPECT_FALSE(res);
}

/**
 * @tc.name: NeedShowPopupView003
 * @tc.desc: Test NeedShowPopupView
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, NeedShowPopupView003, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->popupNode_ = FrameNode::CreateFrameNode("popup", 1, AceType::MakeRefPtr<IndexerPattern>());
    auto layoutProperty = pattern->popupNode_->GetLayoutProperty<LinearLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
    auto res = pattern->NeedShowPopupView();
    EXPECT_FALSE(res);
}

/**
 * @tc.name: StartCollapseDelayTask001
 * @tc.desc: Test StartCollapseDelayTask
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, StartCollapseDelayTask001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto count = 0;
    auto callback = [&count]() { count++; };
    uint32_t duration = 1;
    pipeline->GetTaskExecutor()->PostDelayedTask(
        callback, TaskExecutor::TaskType::UI, duration, "ArkUIAlphabetIndexerCollapse");

    pattern->StartCollapseDelayTask(frameNode, duration);
    EXPECT_EQ(count, 1);
}

/**
 * @tc.name: StartDelayTask001
 * @tc.desc: Test StartDelayTask
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, StartDelayTask001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto count = 0;
    auto callback = [&count]() { count++; };
    uint32_t duration = 1;
    pipeline->GetTaskExecutor()->PostDelayedTask(
        callback, TaskExecutor::TaskType::UI, duration, "ArkUIAlphabetIndexerCollapse");

    pattern->StartDelayTask(duration);
    EXPECT_EQ(count, 1);
}

/**
 * @tc.name: StartBubbleAppearAnimation001
 * @tc.desc: Test StartBubbleAppearAnimation
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, StartBubbleAppearAnimation001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    AnimationOption option;
    auto count = 0;
    auto callback = [&count]() { count++; };
    AnimationUtils::Animate(option, callback);

    pattern->StartBubbleAppearAnimation();
    EXPECT_EQ(count, 1);
}

/**
 * @tc.name: InitOnKeyEvent001
 * @tc.desc: Test InitOnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, InitOnKeyEvent001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);

    pattern->isKeyEventRegisted_ = false;
    bool keyEventHandled = false;
    auto callback = [&keyEventHandled](const KeyEvent& event) -> bool {
        keyEventHandled = true;
        return true;
    };
    focusHub->SetOnKeyEventInternal(callback);

    pattern->InitOnKeyEvent();
    EXPECT_TRUE(keyEventHandled);
}

/**
 * @tc.name: InitOnKeyEvent002
 * @tc.desc: Test InitOnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, InitOnKeyEvent002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);

    pattern->isKeyEventRegisted_ = true;
    bool keyEventHandled = false;
    auto callback = [&keyEventHandled](const KeyEvent& event) -> bool {
        keyEventHandled = true;
        return true;
    };
    focusHub->SetOnKeyEventInternal(callback);

    pattern->InitOnKeyEvent();
    EXPECT_FALSE(keyEventHandled);
}

/**
 * @tc.name: IfSelectIndexValid001
 * @tc.desc: Test IfSelectIndexValid
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, IfSelectIndexValid001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->arrayValue_ = { { "item1", true }, { "item2", false }, { "item3", true } };
    pattern->selected_ = 1;
    auto res = pattern->IfSelectIndexValid();
    EXPECT_TRUE(res);
}

/**
 * @tc.name: IfSelectIndexValid002
 * @tc.desc: Test IfSelectIndexValid
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, IfSelectIndexValid002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->arrayValue_ = { { "item1", true }, { "item2", false }, { "item3", true } };
    pattern->selected_ = 4;
    auto res = pattern->IfSelectIndexValid();
    EXPECT_FALSE(res);
}

/**
 * @tc.name: AddListItemClickListener001
 * @tc.desc: Test AddListItemClickListener
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, AddListItemClickListener001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    int32_t index = 1;

    bool touchEventTriggered = false;
    auto callback = AceType::MakeRefPtr<TouchEventImpl>(
        [&touchEventTriggered](const TouchEventInfo& info) { touchEventTriggered = true; });
    gestureHub->AddTouchEvent(callback);
    pattern->AddListItemClickListener(frameNode, index);
    EXPECT_TRUE(touchEventTriggered);
}

/**
 * @tc.name: AddPopupTouchListener001
 * @tc.desc: Test AddPopupTouchListener
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, AddPopupTouchListener001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    bool touchEventTriggered = false;
    auto callback = AceType::MakeRefPtr<TouchEventImpl>(
        [&touchEventTriggered](const TouchEventInfo& info) { touchEventTriggered = true; });
    gestureHub->AddTouchEvent(callback);
    pattern->AddPopupTouchListener(frameNode);
    EXPECT_TRUE(touchEventTriggered);
}

/**
 * @tc.name: CalcBubbleListSize001
 * @tc.desc: Test CalcBubbleListSize
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, CalcBubbleListSize001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    int32_t popupSize = 10;
    int32_t maxItemsSize = 10;
    auto listCalcSize = pattern->CalcBubbleListSize(popupSize, maxItemsSize);

    EXPECT_NEAR(listCalcSize.Width().value().GetDimension().ConvertToPx(), 56.0f, 0.001f);
}

/**
 * @tc.name: CalcBubbleListSize002
 * @tc.desc: Test CalcBubbleListSize
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, CalcBubbleListSize002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    int32_t popupSize = 20;
    int32_t maxItemsSize = 10;
    auto listCalcSize = pattern->CalcBubbleListSize(popupSize, maxItemsSize);
    ASSERT_TRUE(listCalcSize.Width().has_value());
    EXPECT_NEAR(listCalcSize.Width().value().GetDimension().ConvertToPx(), 56.0f, 0.001f);
}

/**
 * @tc.name: CalcBubbleListSize003
 * @tc.desc: Test CalcBubbleListSize
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, CalcBubbleListSize003, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    int32_t popupSize = 20;
    int32_t maxItemsSize = 10;
    pattern->autoCollapse_ = false;
    auto listCalcSize = pattern->CalcBubbleListSize(popupSize, maxItemsSize);
    ASSERT_TRUE(listCalcSize.Width().has_value());

    EXPECT_NEAR(listCalcSize.Width().value().GetDimension().ConvertToPx(), 56.0f, 0.001f);
}

/**
 * @tc.name: UpdatePopupListGradientView001
 * @tc.desc: Test UpdatePopupListGradientView
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, UpdatePopupListGradientView001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto firstNode  = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto lastNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    frameNode->AddChild(firstNode);
    firstNode->AddChild(lastNode);

    pattern->popupNode_ = frameNode;

    auto listNode = AceType::DynamicCast<FrameNode>(pattern->popupNode_->GetLastChild()->GetFirstChild());
    CHECK_NULL_VOID(listNode);
    auto listEventHub = listNode->GetOrCreateEventHub<ListEventHub>();
    ASSERT_NE(listEventHub, nullptr);
    bool scrollTriggered = false;
    auto scrollCallback = [&scrollTriggered](Dimension offset, ScrollState state) {
        scrollTriggered = true;
    };
    int32_t popupSize = 20;
    int32_t maxItemsSize = 10;
    listEventHub->SetOnScroll(scrollCallback);
    pattern->UpdatePopupListGradientView(popupSize, maxItemsSize);

    EXPECT_TRUE(scrollTriggered);
}

/**
 * @tc.name: UpdatePopupListGradientView002
 * @tc.desc: Test UpdatePopupListGradientView
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, UpdatePopupListGradientView002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto firstNode  = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto lastNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    frameNode->AddChild(firstNode);
    firstNode->AddChild(lastNode);
    
    pattern->popupNode_ = frameNode;

    auto listNode = AceType::DynamicCast<FrameNode>(pattern->popupNode_->GetLastChild()->GetFirstChild());
    CHECK_NULL_VOID(listNode);
    auto listEventHub = listNode->GetOrCreateEventHub<ListEventHub>();
    ASSERT_NE(listEventHub, nullptr);
    bool scrollTriggered = false;
    auto scrollCallback = [&scrollTriggered](Dimension offset, ScrollState state) {
        scrollTriggered = true;
    };
    int32_t popupSize = 20;
    int32_t maxItemsSize = 10;
    listEventHub->SetOnScroll(scrollCallback);
    pattern->UpdatePopupListGradientView(popupSize, maxItemsSize);

    EXPECT_FALSE(scrollTriggered);
}

/**
 * @tc.name: UpdateBubbleListSize001
 * @tc.desc: Test UpdateBubbleListSize
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, UpdateBubbleListSize001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->popupNode_ = frameNode;
    pattern->childPressIndex_ = 10;
    auto container = Container::Current();
    int32_t apiTargetVersion = 12;
    container->SetApiTargetVersion(apiTargetVersion);

    pattern->UpdateBubbleListSize();

    EXPECT_EQ(pattern->lastPopupIndex_, 10);
}

/**
 * @tc.name: UpdateBubbleListSize002
 * @tc.desc: Test UpdateBubbleListSize
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, UpdateBubbleListSize002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->popupNode_ = frameNode;
    pattern->childPressIndex_ = 10;
    pattern->autoCollapse_ = true;
    pattern->lastPopupSize_ = 4;
    pattern->currentListData_.push_back("X");
    pattern->currentListData_.push_back("Y");

    auto container = Container::Current();
    int32_t apiTargetVersion = 13;
    container->SetApiTargetVersion(apiTargetVersion);

    pattern->UpdateBubbleListSize();

    EXPECT_EQ(pattern->lastPopupSize_, 3);
}

/**
 * @tc.name: UpdateBubbleListSize003
 * @tc.desc: Test UpdateBubbleListSize
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, UpdateBubbleListSize003, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->popupNode_ = frameNode;
    pattern->childPressIndex_ = 10;
    pattern->autoCollapse_ = true;
    pattern->lastPopupSize_ = 4;
    pattern->lastPopupIndex_ = 5;
    pattern->currentListData_.push_back("X");
    pattern->currentListData_.push_back("Y");

    auto container = Container::Current();
    int32_t apiTargetVersion = 11;
    container->SetApiTargetVersion(apiTargetVersion);

    pattern->UpdateBubbleListSize();

    EXPECT_EQ(pattern->lastPopupSize_, 10);
}

/**
 * @tc.name: GetAutoCollapseLetterNode001
 * @tc.desc: Test GetAutoCollapseLetterNode
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, GetAutoCollapseLetterNode001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto frameNode1 = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode1, nullptr);
    auto frameNode2 = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode2, nullptr);
    auto frameNode3 = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode3, nullptr);
    auto frameNode4 = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode4, nullptr);
    auto pattern = frameNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    frameNode->AddChild(frameNode1);
    frameNode1->AddChild(frameNode2);
    frameNode2->AddChild(frameNode3);
    frameNode3->AddChild(frameNode4);

    pattern->popupNode_ = frameNode;
    auto childNode = pattern->GetAutoCollapseLetterNode();

    EXPECT_NE(childNode, nullptr);
}

/**
 * @tc.name: InitializeAccessibility001
 * @tc.desc: Test InitializeAccessibility
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, InitializeAccessibility001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<IndexerAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    pattern->InitializeAccessibility();

    EXPECT_TRUE(accessibilityProperty->accessibilityGroup_);
}

/**
 * @tc.name: InitTouchEvent001
 * @tc.desc: Test InitTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, InitTouchEvent001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    bool touchEventTriggered = false;
    auto callback = AceType::MakeRefPtr<TouchEventImpl>(
        [&touchEventTriggered](const TouchEventInfo& info) { touchEventTriggered = true; });
    gestureHub->AddTouchEvent(callback);

    pattern->InitTouchEvent();

    EXPECT_TRUE(touchEventTriggered);
}

/**
 * @tc.name: GetFocusIndex001
 * @tc.desc: Test GetFocusIndex
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, GetFocusIndex001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    int32_t selected = 20;
    pattern->focusIndex_ = 10;
    pattern->currectCollapsingMode_ = ArcIndexerCollapsingMode::INVALID;
    auto focusIndex = pattern->GetFocusIndex(selected);

    EXPECT_EQ(focusIndex, 10);
}

/**
 * @tc.name: GetFocusIndex002
 * @tc.desc: Test GetFocusIndex
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, GetFocusIndex002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    int32_t selected = 20;
    pattern->focusIndex_ = 10;
    pattern->currectCollapsingMode_ = ArcIndexerCollapsingMode::NONE;
    auto focusIndex = pattern->GetFocusIndex(selected);

    EXPECT_EQ(focusIndex, 20);
}

/**
 * @tc.name: ItemSelectedInAnimation001
 * @tc.desc: Test ItemSelectedInAnimation
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, ItemSelectedInAnimation001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto listNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(listNode, nullptr);
    auto pattern = frameNode->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    AnimationOption option;
    auto count = 0;
    auto callback = [&count]() { count++; };
    AnimationUtils::Animate(option, callback);
    pattern->ItemSelectedInAnimation(listNode);

    EXPECT_EQ(count, 1);
}

/**
 * @tc.name: SetFocusIndexStyle001
 * @tc.desc: Test SetFocusIndexStyle
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, SetFocusIndexStyle001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto listNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(listNode, nullptr);
    auto pattern = frameNode->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    int32_t index = 0;
    std::string nodeStr = "SetFocusIndexStyle";
    bool isTextNodeInTree = false;
    pattern->isClickActionFire_ = true;
    pattern->childFocusIndex_ = 0;
    pattern->SetFocusIndexStyle(index, nodeStr, isTextNodeInTree);

    EXPECT_FALSE(pattern->isClickActionFire_);
}

/**
 * @tc.name: NeedShowBubble001
 * @tc.desc: Test NeedShowBubble
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, NeedShowBubble001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto listNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(listNode, nullptr);
    auto pattern = frameNode->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    EXPECT_FALSE(pattern->NeedShowBubble());
}

/**
 * @tc.name: NeedShowBubble002
 * @tc.desc: Test NeedShowBubble
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, NeedShowBubble002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ArcIndexerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    layoutProperty->propUsingPopup_ = true;
    EXPECT_FALSE(pattern->NeedShowBubble());
}

/**
 * @tc.name: NeedShowBubble003
 * @tc.desc: Test NeedShowBubble
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, NeedShowBubble003, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ArcIndexerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    pattern->fullCount_ = 30;
    pattern->selected_ = 10;
    layoutProperty->propUsingPopup_ = true;
    EXPECT_TRUE(pattern->NeedShowBubble());
}

/**
 * @tc.name: ArcIndexerPatternIfSelectIndexValid001
 * @tc.desc: Test IfSelectIndexValid
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, ArcIndexerPatternIfSelectIndexValid001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto listNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(listNode, nullptr);
    auto pattern = frameNode->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->fullCount_ = 0;
    pattern->selected_ = 10;
    EXPECT_FALSE(pattern->IfSelectIndexValid());
}

/**
 * @tc.name: ArcIndexerPatternIfSelectIndexValid002
 * @tc.desc: Test IfSelectIndexValid
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, ArcIndexerPatternIfSelectIndexValid002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto listNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(listNode, nullptr);
    auto pattern = frameNode->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->fullCount_ = 10;
    pattern->selected_ = -1;
    EXPECT_FALSE(pattern->IfSelectIndexValid());
}

/**
 * @tc.name: ArcIndexerPatternIfSelectIndexValid003
 * @tc.desc: Test IfSelectIndexValid
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, ArcIndexerPatternIfSelectIndexValid003, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto listNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(listNode, nullptr);
    auto pattern = frameNode->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->fullCount_ = 10;
    pattern->selected_ = 1;
    EXPECT_TRUE(pattern->IfSelectIndexValid());
}

/**
 * @tc.name: ArcIndexerPressInAnimation001
 * @tc.desc: Test ArcIndexerPressInAnimation
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, ArcIndexerPressInAnimation001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto listNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(listNode, nullptr);
    auto pattern = frameNode->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    AnimationOption option;
    auto count = 0;
    auto callback = [&count]() { count++; };
    AnimationUtils::Animate(option, callback);
    pattern->ArcIndexerPressInAnimation();

    EXPECT_EQ(count, 1);
}

/**
 * @tc.name: ArcIndexerPatternStartBubbleAppearAnimation001
 * @tc.desc: Test StartBubbleAppearAnimation
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, ArcIndexerPatternStartBubbleAppearAnimation001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto listNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(listNode, nullptr);
    auto pattern = frameNode->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    AnimationOption option;
    auto count = 0;
    auto callback = [&count]() { count++; };
    AnimationUtils::Animate(option, callback);
    pattern->StartBubbleAppearAnimation();

    EXPECT_EQ(count, 1);
}

/**
 * @tc.name: ArcIndexerPatternStartDelayTask001
 * @tc.desc: Test StartDelayTask
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, ArcIndexerPatternStartDelayTask001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern1 = frameNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern1, nullptr);
    auto pattern2 = frameNode->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(pattern2, nullptr);

    auto count = 0;
    auto callback = [&count]() { count++; };
    pattern1->delayTask_.Reset(callback);
    pattern2->StartDelayTask();

    EXPECT_EQ(count, 1);
}

/**
 * @tc.name: IsMeasureBoundary001
 * @tc.desc: Test IsMeasureBoundary
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, IsMeasureBoundary001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ArcIndexerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    layoutProperty->SetHost(nullptr);
    auto res = pattern->IsMeasureBoundary();

    EXPECT_FALSE(res);
}

/**
 * @tc.name: IsMeasureBoundary002
 * @tc.desc: Test IsMeasureBoundary
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, IsMeasureBoundary002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(pattern, nullptr);
    frameNode->layoutProperty_ = nullptr;

    auto res = pattern->IsMeasureBoundary();

    EXPECT_FALSE(res);
}

/**
 * @tc.name: IsMeasureBoundary003
 * @tc.desc: Test IsMeasureBoundary
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, IsMeasureBoundary003, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ArcIndexerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    layoutProperty->propertyChangeFlag_ = PROPERTY_UPDATE_MEASURE_SELF;
    auto res = pattern->IsMeasureBoundary();

    EXPECT_TRUE(res);
}

/**
 * @tc.name: IsMeasureBoundary004
 * @tc.desc: Test IsMeasureBoundary
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, IsMeasureBoundary004, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ArcIndexerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    layoutProperty->propertyChangeFlag_ = PROPERTY_UPDATE_LAYOUT;
    auto res = pattern->IsMeasureBoundary();

    EXPECT_FALSE(res);
}

/**
 * @tc.name: IsMeasureBoundary005
 * @tc.desc: Test IsMeasureBoundary
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, IsMeasureBoundary005, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ArcIndexerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    layoutProperty->propertyChangeFlag_ = PROPERTY_UPDATE_MEASURE_SELF | PROPERTY_UPDATE_LAYOUT;
    auto res = pattern->IsMeasureBoundary();

    EXPECT_TRUE(res);
}

/**
 * @tc.name: UpdateChildBoundary001
 * @tc.desc: Test UpdateChildBoundary
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, UpdateChildBoundary001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto frameNode1 = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode1, nullptr);
    auto pattern = frameNode->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ArcIndexerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    layoutProperty->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;

    frameNode1->tag_ = V2::TEXT_ETS_TAG;
    auto pattern1 = frameNode1->GetPattern<TextPattern>();
    ASSERT_NE(pattern1, nullptr);
    pattern->UpdateChildBoundary(frameNode1);
    EXPECT_TRUE(pattern1->isMeasureBoundary_);
}

/**
 * @tc.name: UpdateChildBoundary002
 * @tc.desc: Test UpdateChildBoundary
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, UpdateChildBoundary002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ArcIndexerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto frameNode1 = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode1, nullptr);
    layoutProperty->propertyChangeFlag_ = PROPERTY_UPDATE_MEASURE;

    frameNode1->tag_ = V2::TEXT_ETS_TAG;
    auto pattern1 = frameNode1->GetPattern<TextPattern>();
    ASSERT_NE(pattern1, nullptr);

    pattern->UpdateChildBoundary(frameNode1);

    EXPECT_FALSE(pattern1->isMeasureBoundary_);
}

/**
 * @tc.name: CalcArcItemAngle001
 * @tc.desc: Test CalcArcItemAngle
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, CalcArcItemAngle001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(pattern, nullptr);
    int32_t index = 10;
    pattern->startAngle_ = 10;
    pattern->stepAngle_ = 10;
    auto itemAngle = pattern->CalcArcItemAngle(index);
    EXPECT_EQ(itemAngle, 110);
}

/**
 * @tc.name: CalcArcItemPosition001
 * @tc.desc: Test CalcArcItemPosition
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, CalcArcItemPosition001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);

    int32_t index = 0;
    auto arcindexerLayoutAlgorithm = AceType::DynamicCast<ArcIndexerLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    EXPECT_NE(arcindexerLayoutAlgorithm, nullptr);

    arcindexerLayoutAlgorithm->startAngle_ = 1.0f;
    arcindexerLayoutAlgorithm->stepAngle_ = 1.0f;
    auto result  = arcindexerLayoutAlgorithm->CalcArcItemPosition(layoutWrapper, index);
    EXPECT_NEAR(result.GetX().Value(), 135.0f, 0.001f);
    EXPECT_NEAR(result.GetY().Value(), 85.0f, 0.001f);
}

/**
 * @tc.name: MeasureArc001
 * @tc.desc: Test MeasureArc
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, MeasureArc001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);

    layoutWrapper->GetGeometryNode()->GetFrameSize().SetWidth(50.0f);
    layoutWrapper->GetGeometryNode()->GetFrameSize().SetHeight(100.0f);
    auto arcindexerLayoutAlgorithm = AceType::DynamicCast<ArcIndexerLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    EXPECT_NE(arcindexerLayoutAlgorithm, nullptr);
    arcindexerLayoutAlgorithm->itemSize_ = 10.f;

    arcindexerLayoutAlgorithm->MeasureArc(layoutWrapper);
    EXPECT_EQ(arcindexerLayoutAlgorithm->arcRadius_, 45.0f);
}

/**
 * @tc.name: MeasureArc002
 * @tc.desc: Test MeasureArc
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, MeasureArc002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);

    layoutWrapper->GetGeometryNode()->GetFrameSize().SetWidth(100.0f);
    layoutWrapper->GetGeometryNode()->GetFrameSize().SetHeight(50.0f);
    auto arcindexerLayoutAlgorithm = AceType::DynamicCast<ArcIndexerLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    EXPECT_NE(arcindexerLayoutAlgorithm, nullptr);
    arcindexerLayoutAlgorithm->itemSize_ = 10.f;

    arcindexerLayoutAlgorithm->MeasureArc(layoutWrapper);
    EXPECT_EQ(arcindexerLayoutAlgorithm->arcRadius_, 45.0f);
}

/**
 * @tc.name: MeasureArc003
 * @tc.desc: Test MeasureArc
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, MeasureArc003, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);

    layoutWrapper->GetGeometryNode()->GetFrameSize().SetWidth(100.0f);
    layoutWrapper->GetGeometryNode()->GetFrameSize().SetHeight(50.0f);
    auto arcindexerLayoutAlgorithm = AceType::DynamicCast<ArcIndexerLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    EXPECT_NE(arcindexerLayoutAlgorithm, nullptr);
    arcindexerLayoutAlgorithm->itemSize_ = 10.f;

    arcindexerLayoutAlgorithm->fullCount_ = 5;
    arcindexerLayoutAlgorithm->MeasureArc(layoutWrapper);
    EXPECT_EQ(arcindexerLayoutAlgorithm->fullCount_, 6);
}

/**
 * @tc.name: MeasureArc004
 * @tc.desc: Test MeasureArc
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, MeasureArc004, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);

    layoutWrapper->GetGeometryNode()->GetFrameSize().SetWidth(100.0f);
    layoutWrapper->GetGeometryNode()->GetFrameSize().SetHeight(50.0f);
    auto arcindexerLayoutAlgorithm = AceType::DynamicCast<ArcIndexerLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    EXPECT_NE(arcindexerLayoutAlgorithm, nullptr);
    arcindexerLayoutAlgorithm->itemSize_ = 10.f;

    arcindexerLayoutAlgorithm->fullCount_ = 3;
    arcindexerLayoutAlgorithm->MeasureArc(layoutWrapper);
    EXPECT_EQ(arcindexerLayoutAlgorithm->fullCount_, 3);
}

/**
 * @tc.name: MeasureArc005
 * @tc.desc: Test MeasureArc
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, MeasureArc005, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);

    layoutWrapper->GetGeometryNode()->GetFrameSize().SetWidth(100.0f);
    layoutWrapper->GetGeometryNode()->GetFrameSize().SetHeight(50.0f);
    auto arcindexerLayoutAlgorithm = AceType::DynamicCast<ArcIndexerLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    EXPECT_NE(arcindexerLayoutAlgorithm, nullptr);
    arcindexerLayoutAlgorithm->itemSize_ = 10.f;

    auto layoutProperty = frameNode->GetLayoutProperty<ArcIndexerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->propAutoCollapse_ = false;
    arcindexerLayoutAlgorithm->fullCount_ = 5;
    arcindexerLayoutAlgorithm->MeasureArc(layoutWrapper);
    EXPECT_EQ(arcindexerLayoutAlgorithm->fullCount_, 5);
}

/**
 * @tc.name: MeasureArc006
 * @tc.desc: Test MeasureArc
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, MeasureArc006, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);

    layoutWrapper->GetGeometryNode()->GetFrameSize().SetWidth(100.0f);
    layoutWrapper->GetGeometryNode()->GetFrameSize().SetHeight(50.0f);
    auto arcindexerLayoutAlgorithm = AceType::DynamicCast<ArcIndexerLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    EXPECT_NE(arcindexerLayoutAlgorithm, nullptr);
    arcindexerLayoutAlgorithm->itemSize_ = 10.f;

    auto layoutProperty = frameNode->GetLayoutProperty<ArcIndexerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->propAutoCollapse_ = false;
    arcindexerLayoutAlgorithm->fullCount_ = 30;
    arcindexerLayoutAlgorithm->MeasureArc(layoutWrapper);
    EXPECT_EQ(arcindexerLayoutAlgorithm->fullCount_, 31);
}

/**
 * @tc.name: MeasureArc007
 * @tc.desc: Test MeasureArc
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestTwoNg, MeasureArc007, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);

    layoutWrapper->GetGeometryNode()->GetFrameSize().SetWidth(100.0f);
    layoutWrapper->GetGeometryNode()->GetFrameSize().SetHeight(50.0f);
    auto arcindexerLayoutAlgorithm = AceType::DynamicCast<ArcIndexerLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    EXPECT_NE(arcindexerLayoutAlgorithm, nullptr);
    arcindexerLayoutAlgorithm->itemSize_ = 10.f;

    auto layoutProperty = frameNode->GetLayoutProperty<ArcIndexerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->propAutoCollapse_ = false;
    arcindexerLayoutAlgorithm->fullCount_ = 5;
    arcindexerLayoutAlgorithm->stepAngle_ = 100.0f;
    arcindexerLayoutAlgorithm->MeasureArc(layoutWrapper);
    EXPECT_EQ(arcindexerLayoutAlgorithm->stepAngle_, 72);
}
} // namespace OHOS::Ace::NG