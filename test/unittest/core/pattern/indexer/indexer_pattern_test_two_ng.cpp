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
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/list/list_event_hub.h"

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
} // namespace OHOS::Ace::NG