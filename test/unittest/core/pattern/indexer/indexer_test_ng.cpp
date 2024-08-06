/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

namespace OHOS::Ace::NG {
namespace {
std::vector<std::string> CREATE_ARRAY = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O",
    "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
std::vector<std::string> CREATE_ARRAY_1 = { "A", "B", "C", "D", "E", "F", "G", "H", "I"};
std::vector<std::string> CREATE_ARRAY_2 = { "#", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L"};
const float INDEXER_WIDTH = 40.0f;
std::vector<std::string> GetPopupData(int32_t)
{
    return { "白", "别" };
}
std::vector<std::string> GetMorePopupData(int32_t)
{
    return { "白", "别", "吧", "不", "被" };
}
std::vector<std::string> GetMorePopupData2(int32_t)
{
    return { "白", "别", "吧", "不", "被", "包", "毕" };
}
} // namespace

void IndexerTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_INDEXER);
    auto indexerTheme = IndexerTheme::Builder().Build(themeConstants);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(indexerTheme));
}

void IndexerTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void IndexerTestNg::SetUp() {}

void IndexerTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    paintProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
    ClearOldNodes(); // Each testCase will create new list at begin
}

IndexerModelNG IndexerTestNg::CreateIndexer(std::vector<std::string> arrayValue, int32_t selected)
{
    ResetElmtId();
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    IndexerModelNG model;
    model.Create(arrayValue, selected);
    model.SetAutoCollapse(false);
    GetIndexer();
    return model;
}

void IndexerTestNg::GetIndexer()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<IndexerPattern>();
    eventHub_ = frameNode_->GetEventHub<IndexerEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<IndexerLayoutProperty>();
    paintProperty_ = frameNode_->GetPaintProperty<IndexerPaintProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<IndexerAccessibilityProperty>();
}

AssertionResult IndexerTestNg::Selected(int32_t expectSelected)
{
    return IsEqual(pattern_->GetSelected(), expectSelected);
}

void IndexerTestNg::MoveIndex(GestureEvent gestureEvent)
{
    auto start = pattern_->panEvent_->GetActionStartEventFunc();
    auto update = pattern_->panEvent_->GetActionUpdateEventFunc();
    start(gestureEvent);
    update(gestureEvent);
}

AssertionResult IndexerTestNg::Touch(TouchType touchType, float locationY, int32_t expectSelected)
{
    float firstOffsetY = 0.f;
    if (pattern_->itemCount_ > 0) {
        firstOffsetY = GetChildY(frameNode_, 0);
    }
    TouchEventInfo touchEventInfo = CreateTouchEventInfo(touchType, Offset(0.f, locationY + firstOffsetY));
    auto touchFuc = pattern_->touchListener_->GetTouchEventCallback();
    touchFuc(touchEventInfo);
    return Selected(expectSelected);
}

/**
 * @tc.name: IndexerMoveIndex001
 * @tc.desc: Test panEvent_ MoveIndexByStep func.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerMoveIndex001, TestSize.Level1)
{
    CreateIndexer(CREATE_ARRAY, 0);
    CreateDone();
    ASSERT_NE(pattern_->panEvent_, nullptr);
    GestureEvent gestureEvent;
    gestureEvent.SetInputEventType(InputEventType::AXIS);

    /**
     * @tc.steps: step1. Delta is 0.
     * @tc.expected: Selected unchanged.
     */
    gestureEvent.SetMainDelta(0.f);
    MoveIndex(gestureEvent);
    EXPECT_TRUE(Selected(0));

    /**
     * @tc.steps: step2. Delta is 1.
     * @tc.expected: Selected unchanged.
     */
    gestureEvent.SetMainDelta(1.f);
    MoveIndex(gestureEvent);
    EXPECT_TRUE(Selected(0));

    /**
     * @tc.steps: step3. Delta is -1.
     * @tc.expected: Selected += 1.
     */
    gestureEvent.SetMainDelta(-1.f);
    MoveIndex(gestureEvent);

    /**
     * @tc.steps: step4. Delta is 1, selected_ is itemCount-1.
     * @tc.expected: Selected unchanged.
     */
    pattern_->selected_ = pattern_->itemCount_ - 1;
    gestureEvent.SetMainDelta(-1.f);
    MoveIndex(gestureEvent);
    EXPECT_TRUE(Selected(pattern_->itemCount_ - 1));
}

/**
 * @tc.name: IndexerMoveIndex002
 * @tc.desc: Test panEvent_ MoveIndexByOffset func.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerMoveIndex002, TestSize.Level1)
{
    CreateIndexer(CREATE_ARRAY, 0);
    CreateDone();
    ASSERT_NE(pattern_->panEvent_, nullptr);
    GestureEvent gestureEvent;
    gestureEvent.SetInputEventType(InputEventType::KEYBOARD);

    /**
     * @tc.steps: step1. Location is (0, 50).
     * @tc.expected: Selected change to correct index.
     */
    float locationY = 50.f + GetChildY(frameNode_, 0);
    gestureEvent.SetLocalLocation(Offset(0.f, locationY));
    MoveIndex(gestureEvent);

    /**
     * @tc.steps: step2. Location is (0, 50).
     * @tc.expected: Selected unchanged.
     */
    gestureEvent.SetLocalLocation(Offset(0.f, locationY));
    MoveIndex(gestureEvent);
}

/**
 * @tc.name: IndexerMoveIndex003
 * @tc.desc: Test panEvent_ MoveIndexByOffset func in other condition.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerMoveIndex003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test with empty array.
     * @tc.expected: Selected unchanged.
     */
    IndexerModelNG model = CreateIndexer(std::vector<std::string>(), 0);
    model.SetUsingPopup(true);
    CreateDone();
    ASSERT_NE(pattern_->panEvent_, nullptr);
    GestureEvent gestureEvent;
    gestureEvent.SetInputEventType(InputEventType::KEYBOARD);
    gestureEvent.SetLocalLocation(Offset(0.f, 50.f));
    MoveIndex(gestureEvent);
    EXPECT_TRUE(Selected(0));
}

/**
 * @tc.name: IndexerTouch001
 * @tc.desc: Test touchListener_ func with hover.
 * @tc.desc: and touchDown touchUp in different location.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerTouch001, TestSize.Level1)
{
    CreateIndexer(CREATE_ARRAY, 0);
    CreateDone();
    ASSERT_NE(pattern_->touchListener_, nullptr);

    /**
     * @tc.steps: step1. OnTouchDown.
     * @tc.expected: Selected index is correct.
     */
    pattern_->OnHover(true);
    EXPECT_TRUE(Touch(TouchType::DOWN, 50.f, static_cast<int32_t>(50.f / pattern_->itemHeight_)));

    /**
     * @tc.steps: step2. OnTouchUp, different location.
     * @tc.expected: Selected index is correct.
     */
    EXPECT_TRUE(Touch(TouchType::UP, 20.f, static_cast<int32_t>(50.f / pattern_->itemHeight_)));
}

/**
 * @tc.name: IndexerTouch002
 * @tc.desc: Test touchListener_ func with no hover,
 * @tc.desc: and touchDown touchUp in same location.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerTouch002, TestSize.Level1)
{
    CreateIndexer(CREATE_ARRAY, 0);
    CreateDone();
    ASSERT_NE(pattern_->touchListener_, nullptr);

    /**
     * @tc.steps: step1. OnTouchDown.
     * @tc.expected: Selected index is correct.
     */
    pattern_->OnHover(false);
    EXPECT_TRUE(Touch(TouchType::DOWN, 50.f, static_cast<int32_t>(50.f / pattern_->itemHeight_)));

    /**
     * @tc.steps: step2. OnTouchUp, same location.
     * @tc.expected: Selected index is correct.
     */
    EXPECT_TRUE(Touch(TouchType::UP, 50.f, static_cast<int32_t>(50.f / pattern_->itemHeight_)));
}

/**
 * @tc.name: IndexerTouch003
 * @tc.desc: Test touchListener_ func with other condition.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerTouch003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. TouchType::MOVE.
     * @tc.expected: Selected unchanged.
     */
    CreateIndexer(CREATE_ARRAY, 0);
    CreateDone();
    ASSERT_NE(pattern_->touchListener_, nullptr);
    EXPECT_TRUE(Touch(TouchType::MOVE, 20.f, 0));

    /**
     * @tc.steps: step2. Empty array
     * @tc.expected: Selected unchanged.
     */
    ClearOldNodes();
    CreateIndexer(std::vector<std::string>(), 0);
    CreateDone();
    EXPECT_TRUE(Touch(TouchType::DOWN, 20.f, 0));
    EXPECT_TRUE(Touch(TouchType::UP, 20.f, 0));

    /**
     * @tc.steps: step3. Touch -1.f
     * @tc.expected: Selected index 0.
     */
    ClearOldNodes();
    CreateIndexer(CREATE_ARRAY, 0);
    CreateDone();
    EXPECT_TRUE(Touch(TouchType::DOWN, -1.f, 0));
    EXPECT_TRUE(Touch(TouchType::UP, -1.f, 0));
}

/**
 * @tc.name: IndexerKeyEvent001
 * @tc.desc: Test OnKeyEvent func about KeyIndexByStep.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerKeyEvent001, TestSize.Level1)
{
    CreateIndexer(CREATE_ARRAY, 0);
    CreateDone();

    /**
     * @tc.steps: step1. UNKNOWN keyEvent.
     * @tc.expected: Selected unchanged.
     */
    KeyEvent keyEvent = KeyEvent();
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_TRUE(Selected(0));

    /**
     * @tc.steps: step2. KEY_UNKNOWN from 0.
     * @tc.expected: Selected unchanged.
     */
    keyEvent.action = KeyAction::DOWN;
    keyEvent.code = KeyCode::KEY_UNKNOWN;
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_TRUE(Selected(0));

    /**
     * @tc.steps: step3. KEY_DPAD_UP from 0.
     * @tc.expected: Selected unchanged.
     */
    keyEvent.code = KeyCode::KEY_DPAD_UP;
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_TRUE(Selected(0));

    /**
     * @tc.steps: step4. KEY_DPAD_DOWN from 0.
     * @tc.expected: Selected += 1.
     */
    keyEvent.code = KeyCode::KEY_DPAD_DOWN;
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_TRUE(Selected(1));

    /**
     * @tc.steps: step5. KEY_DPAD_DOWN from itemCount_-1.
     * @tc.expected: Selected unchanged.
     */
    pattern_->selected_ = pattern_->itemCount_ - 1;
    keyEvent.code = KeyCode::KEY_DPAD_DOWN;
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_TRUE(Selected(pattern_->itemCount_ - 1));
}

/**
 * @tc.name: IndexerKeyEvent002
 * @tc.desc: Test OnKeyEvent func about MoveIndexBySearch.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerKeyEvent002, TestSize.Level1)
{
    CreateIndexer(CREATE_ARRAY, 0);
    CreateDone();

    /**
     * @tc.steps: step1. IsCombinationKey && KEY_UNKNOWN.
     * @tc.expected: Selected unchanged.
     */
    KeyEvent keyEvent = KeyEvent();
    keyEvent.action = KeyAction::DOWN;
    keyEvent.code = KeyCode::KEY_UNKNOWN;
    keyEvent.pressedCodes = { KeyCode::KEY_A, KeyCode::KEY_B };
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_TRUE(Selected(0));

    /**
     * @tc.steps: step2. IsCombinationKey && IsLetterKey.
     * @tc.expected: Selected unchanged.
     */
    keyEvent.code = KeyCode::KEY_B;
    keyEvent.pressedCodes = { KeyCode::KEY_A, KeyCode::KEY_B };
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_TRUE(Selected(0));

    /**
     * @tc.steps: step3. !IsCombinationKey && IsLetterKey.
     * @tc.expected: Selected changed.
     */
    keyEvent.code = KeyCode::KEY_B;
    keyEvent.pressedCodes = {};
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_TRUE(Selected(1));

    /**
     * @tc.steps: step4. Move to KEY_B again.
     * @tc.expected: Selected unchanged.
     */
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_TRUE(Selected(1));

    /**
     * @tc.steps: step5. Move to front Index.
     * @tc.expected: Selected changed.
     */
    keyEvent.code = KeyCode::KEY_A;
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_TRUE(Selected(0));

    /**
     * @tc.steps: step6. Move to back Index.
     * @tc.expected: Selected changed.
     */
    keyEvent.code = KeyCode::KEY_C;
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_TRUE(Selected(2));

    /**
     * @tc.steps: step7. !IsCombinationKey && IsNumberKey.
     * @tc.expected: Selected unchanged.
     */
    keyEvent.code = KeyCode::KEY_5;
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_TRUE(Selected(2));
}

/**
 * @tc.name: IndexerHover001
 * @tc.desc: Test Hover
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerHover001, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetUsingPopup(true);
    CreateDone();

    pattern_->OnChildHover(1, true);
    EXPECT_EQ(pattern_->childHoverIndex_, 1);
    pattern_->OnChildHover(1, false);
    EXPECT_EQ(pattern_->childHoverIndex_, -1);

    pattern_->OnHover(false);
    EXPECT_FALSE(pattern_->isHover_);
    pattern_->OnHover(true);
    EXPECT_TRUE(pattern_->isHover_);
    pattern_->OnHover(false);
    EXPECT_FALSE(pattern_->isHover_);

    /**
     * @tc.steps: step1. Set empty arrayValue and trigger OnHover
     * @tc.expected: isHover_ is still be false
     */
    ClearOldNodes();
    model = CreateIndexer(std::vector<std::string>(), 0);
    model.SetUsingPopup(true);
    CreateDone();
    pattern_->OnHover(true);
    EXPECT_FALSE(pattern_->isHover_);
}

/**
 * @tc.name: IndexerPattern001
 * @tc.desc: Test indexer pattern OnDirtyLayoutWrapperSwap function. include special value.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerPattern001, TestSize.Level1)
{
    IndexerModelNG IndexerModelNG;
    IndexerModelNG.Create(CREATE_ARRAY, 0);
    GetIndexer();

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = true;
    dirtySwapConfig.skipLayout = true;
    EXPECT_FALSE(pattern_->OnDirtyLayoutWrapperSwap(frameNode_, dirtySwapConfig));

    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    EXPECT_TRUE(pattern_->OnDirtyLayoutWrapperSwap(frameNode_, dirtySwapConfig));

    dirtySwapConfig.skipMeasure = true;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(frameNode_, dirtySwapConfig);
    EXPECT_TRUE(pattern_->OnDirtyLayoutWrapperSwap(frameNode_, dirtySwapConfig));

    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = true;
    pattern_->OnDirtyLayoutWrapperSwap(frameNode_, dirtySwapConfig);
    EXPECT_TRUE(pattern_->OnDirtyLayoutWrapperSwap(frameNode_, dirtySwapConfig));
}

/**
 * @tc.name: IndexerPattern002
 * @tc.desc: Test indexer pattern InitBubbleList function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerPattern002, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 2);
    model.SetUsingPopup(true);
    model.SetAlignStyle(0);
    model.SetPopupUnselectedColor(Color(0x00000000));
    model.SetOnRequestPopupData(GetPopupData);
    CreateDone();

    pattern_->MoveIndexByStep(1);
    ASSERT_NE(pattern_->popupNode_, nullptr);
    auto listNode = pattern_->popupNode_->GetLastChild()->GetFirstChild();
    auto listItemNode = AceType::DynamicCast<FrameNode>(listNode->GetFirstChild());
    auto textNode = AceType::DynamicCast<FrameNode>(listItemNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetTextColor().value(), Color(0x00000000));
}

/**
 * @tc.name: IndexerPattern003
 * @tc.desc: Test indexer pattern ChangeListItemsSelectedStyle function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerPattern003, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 2);
    model.SetUsingPopup(true);
    model.SetPopupSelectedColor(Color(0x00000000));
    model.SetPopupUnselectedColor(Color(0x00000000));
    model.SetPopupItemBackground(Color(0x00000000));
    model.SetOnRequestPopupData(GetPopupData);
    CreateDone();
    pattern_->MoveIndexByStep(1);
    ASSERT_NE(pattern_->popupNode_, nullptr);

    /**
     * @tc.steps: step1. TouchType::DOWN
     * @tc.expected: trigger OnListItemClick.
     */
    auto listNode = pattern_->popupNode_->GetLastChild()->GetFirstChild();
    auto listItemNode = AceType::DynamicCast<FrameNode>(listNode->GetFirstChild());
    auto gesture = listItemNode->GetOrCreateGestureEventHub();
    auto touchCallback = gesture->touchEventActuator_->touchEvents_.front()->GetTouchEventCallback();
    TouchEventInfo touchEventInfo = CreateTouchEventInfo(TouchType::DOWN, Offset());
    touchCallback(touchEventInfo);
    auto textNode = AceType::DynamicCast<FrameNode>(listItemNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetTextColor().value(), Color(0x00000000));

    /**
     * @tc.steps: step1. TouchType::UP
     * @tc.expected: trigger ClearClickStatus.
     */
    touchEventInfo = CreateTouchEventInfo(TouchType::UP, Offset());
    touchCallback(touchEventInfo);
    EXPECT_EQ(textLayoutProperty->GetTextColor().value(), Color(0x00000000));
}

/**
 * @tc.name: IndexerPattern004
 * @tc.desc: Test indexer pattern.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerPattern004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create indexer when apiTargetVersion is PlatformVersion::VERSION_TWELVE
     * @tc.expected: BorderRadiusValue is Dimension(INDEXER_DEFAULT_RADIUS, DimensionUnit::VP)
     */
    int32_t apiTargetVersion = Container::Current()->GetApiTargetVersion();
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetUsingPopup(true);
    CreateDone();
    auto indexerRenderContext = frameNode_->GetRenderContext();
    auto indexerRadius = Dimension(INDEXER_DEFAULT_RADIUS, DimensionUnit::VP);
    BorderRadiusProperty expectValue = { indexerRadius, indexerRadius, indexerRadius, indexerRadius };
    EXPECT_TRUE(indexerRenderContext->HasBorderRadius());
    EXPECT_EQ(indexerRenderContext->GetBorderRadiusValue(expectValue), expectValue);

    /**
     * @tc.steps: step2. UpdateIndexerBorderRadius
     * @tc.expected: indexerRenderContext BorderRadiusValue is Dimension(16)
     */
    paintProperty_->UpdateIndexerBorderRadius(Dimension(16));
    pattern_->OnChildHover(1, true);
    FlushLayoutTask(frameNode_);
    expectValue = { Dimension(16), Dimension(16), Dimension(16), Dimension(16) };
    EXPECT_TRUE(indexerRenderContext->HasBorderRadius());
    EXPECT_EQ(indexerRenderContext->GetBorderRadiusValue(expectValue), expectValue);
    auto radius = Dimension(BUBBLE_RADIUS, DimensionUnit::VP);
    auto columnRenderContext = pattern_->popupNode_->GetRenderContext();
    expectValue = { radius, radius, radius, radius };
    EXPECT_TRUE(columnRenderContext->HasBorderRadius());
    EXPECT_EQ(columnRenderContext->GetBorderRadiusValue(expectValue), expectValue);
    BlurStyleOption styleOption;
    styleOption.blurStyle = BlurStyle::COMPONENT_REGULAR;
    EXPECT_EQ(columnRenderContext->GetBackBlurStyle().value(), styleOption);

    /**
     * @tc.steps: step3. UpdatePopupBorderRadius
     * @tc.expected: columnRenderContext BorderRadiusValue is Dimension(28)
     */
    styleOption.blurStyle = BlurStyle::REGULAR;
    paintProperty_->UpdatePopupBorderRadius(Dimension(28));
    paintProperty_->UpdatePopupBackgroundBlurStyle(styleOption);
    pattern_->OnChildHover(2, true);
    FlushLayoutTask(frameNode_);
    expectValue = { Dimension(28), Dimension(28), Dimension(28), Dimension(28) };
    EXPECT_TRUE(columnRenderContext->HasBorderRadius());
    EXPECT_EQ(columnRenderContext->GetBorderRadiusValue(expectValue), expectValue);
    EXPECT_EQ(columnRenderContext->GetBackBlurStyle().value(), styleOption);
    Container::Current()->SetApiTargetVersion(apiTargetVersion);
}

/**
 * @tc.name: IndexerPattern005
 * @tc.desc: Test indexer pattern.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerPattern005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create indexer when apiTargetVersion is PlatformVersion::VERSION_TWELVE
     * @tc.expected: Colors.size is 3
     */
    int32_t apiTargetVersion = Container::Current()->GetApiTargetVersion();
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetUsingPopup(true);
    model.SetOnRequestPopupData(GetMorePopupData2);
    CreateDone();
    pattern_->MoveIndexByOffset(Offset(0, 10));
    FlushLayoutTask(frameNode_);
    auto listNode = AceType::DynamicCast<FrameNode>(pattern_->popupNode_->GetLastChild()->GetFirstChild());
    auto listPattern = listNode->GetPattern<ListPattern>();
    auto listEventHub = listNode->GetEventHub<ListEventHub>();
    auto onScrollCallback = listEventHub->GetOnScroll();
    auto stackNode = AceType::DynamicCast<FrameNode>(pattern_->popupNode_->GetLastChild());
    auto stackRenderContext = stackNode->GetRenderContext();
    EXPECT_EQ(stackRenderContext->GetLinearGradientValue(Gradient()).GetColors().size(), 3);

    /**
     * @tc.steps: step2. list at top
     * @tc.expected: Colors.size is 3
     */

    EXPECT_TRUE(listPattern->IsAtTop());
    onScrollCallback(Dimension(0), ScrollState::SCROLL);
    EXPECT_EQ(stackRenderContext->GetLinearGradientValue(Gradient()).GetColors().size(), 3);

    /**
     * @tc.steps: step3. list scroll to 20
     * @tc.expected: Colors.size is 4
     */
    listPattern->ScrollTo(20);
    FlushLayoutTask(listNode);
    EXPECT_FALSE(listPattern->IsAtTop());
    EXPECT_FALSE(listPattern->IsAtBottom());
    onScrollCallback(Dimension(0), ScrollState::SCROLL);
    EXPECT_EQ(stackRenderContext->GetLinearGradientValue(Gradient()).GetColors().size(), 4);

    /**
     * @tc.steps: step4. list scroll to bottom
     * @tc.expected: Colors.size is 3
     */
    listPattern->ScrollTo(100);
    FlushLayoutTask(listNode);
    EXPECT_TRUE(listPattern->IsAtBottom());
    onScrollCallback(Dimension(0), ScrollState::SCROLL);
    EXPECT_EQ(stackRenderContext->GetLinearGradientValue(Gradient()).GetColors().size(), 3);
    Container::Current()->SetApiTargetVersion(apiTargetVersion);
}

/**
 * @tc.name: IndexerUpdateBubble001
 * @tc.desc: Test UpdateBubbleSize function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerUpdateBubble001, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetUsingPopup(true);
    model.SetOnRequestPopupData(GetPopupData);
    CreateDone();

    /**
     * @tc.steps: step1. has popListData.
     * @tc.expected: verify size.
     */
    pattern_->MoveIndexBySearch("C");
    pattern_->UpdateBubbleSize();
    ASSERT_NE(pattern_->popupNode_, nullptr);
    auto columnLayoutProperty = pattern_->popupNode_->GetLayoutProperty<LinearLayoutProperty>();
    ASSERT_NE(columnLayoutProperty, nullptr);
    ASSERT_NE(columnLayoutProperty->calcLayoutConstraint_, nullptr);
    auto bubbleSize = Dimension(BUBBLE_BOX_SIZE, DimensionUnit::VP).ConvertToPx();
    auto columnCalcSize =
        Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)
            ? CalcSize(CalcLength(bubbleSize), CalcLength(BUBBLE_ITEM_SIZE * 3 + BUBBLE_DIVIDER_SIZE * 4))
            : CalcSize(CalcLength(bubbleSize), CalcLength(bubbleSize * 3));
    EXPECT_EQ(columnLayoutProperty->calcLayoutConstraint_->selfIdealSize, columnCalcSize);
}

/**
 * @tc.name: IndexerUpdateBubble002
 * @tc.desc: Test UpdateBubbleSize function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerUpdateBubble002, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetUsingPopup(true);
    model.SetOnRequestPopupData(GetPopupData);
    CreateDone();

    /**
     * @tc.steps: step1. childPressIndex_ less than 0.
     * @tc.expected: verify size.
     */
    pattern_->MoveIndexByStep(1);
    pattern_->UpdateBubbleSize();
    ASSERT_NE(pattern_->popupNode_, nullptr);
    auto columnLayoutProperty = pattern_->popupNode_->GetLayoutProperty<LinearLayoutProperty>();
    ASSERT_NE(columnLayoutProperty, nullptr);
    ASSERT_NE(columnLayoutProperty->calcLayoutConstraint_, nullptr);
    auto bubbleSize = Dimension(BUBBLE_BOX_SIZE, DimensionUnit::VP).ConvertToPx();
    auto columnCalcSize =
        Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)
            ? CalcSize(CalcLength(bubbleSize), CalcLength(BUBBLE_ITEM_SIZE * 3 + BUBBLE_DIVIDER_SIZE * 4))
            : CalcSize(CalcLength(bubbleSize), CalcLength(bubbleSize * 3));
    EXPECT_EQ(columnLayoutProperty->calcLayoutConstraint_->selfIdealSize, columnCalcSize);
}

/**
 * @tc.name: IndexerUpdateBubble003
 * @tc.desc: Test UpdateBubbleSize function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerUpdateBubble003, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetUsingPopup(true);
    model.SetOnRequestPopupData(GetMorePopupData); // GetMorePopupData.
    CreateDone();

    /**
     * @tc.steps: step1. has popListData and popListData size equal INDEXER_BUBBLE_MAXSIZE.
     * @tc.expected: verify size.
     */
    pattern_->MoveIndexBySearch("C");
    pattern_->UpdateBubbleSize();
    ASSERT_NE(pattern_->popupNode_, nullptr);
    auto columnLayoutProperty = pattern_->popupNode_->GetLayoutProperty<LinearLayoutProperty>();
    ASSERT_NE(columnLayoutProperty, nullptr);
    ASSERT_NE(columnLayoutProperty->calcLayoutConstraint_, nullptr);
    auto bubbleSize = Dimension(BUBBLE_BOX_SIZE, DimensionUnit::VP).ConvertToPx();
    auto columnCalcSize =
        Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)
            ? CalcSize(CalcLength(bubbleSize), CalcLength(BUBBLE_ITEM_SIZE * 6 + BUBBLE_DIVIDER_SIZE * 7))
            : CalcSize(CalcLength(bubbleSize), CalcLength(bubbleSize * 6));
    EXPECT_EQ(columnLayoutProperty->calcLayoutConstraint_->selfIdealSize, columnCalcSize);
}

/**
 * @tc.name: IndexerPopupTouchDown001
 * @tc.desc: Test OnPopupTouchDown.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerPopupTouchDown001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ShowBubble
     */
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetUsingPopup(true);
    CreateDone(); // NeedShowPopupView is true.
    pattern_->MoveIndexByStep(1);                                    // ShowBubble
    ASSERT_NE(pattern_->popupNode_, nullptr);
    auto gesture = pattern_->popupNode_->GetOrCreateGestureEventHub();
    auto onPopupTouchDown = gesture->touchEventActuator_->touchEvents_.front()->GetTouchEventCallback();

    /**
     * @tc.steps: step2. Create touchEventInfo, set TouchType::DOWN.
     * @tc.expected: isTouch_ is true.
     */
    TouchEventInfo touchEventInfo = CreateTouchEventInfo(TouchType::DOWN, Offset());
    onPopupTouchDown(touchEventInfo); // trigger OnPopupTouchDown
    EXPECT_TRUE(pattern_->isTouch_);

    /**
     * @tc.steps: step3. Create touchEventInfo, set TouchType::UP
     * @tc.expected: isTouch_ is false.
     */
    touchEventInfo = CreateTouchEventInfo(TouchType::UP, Offset());
    onPopupTouchDown(touchEventInfo);
    EXPECT_FALSE(pattern_->isTouch_);
}

/**
 * @tc.name: Event001
 * @tc.desc: Test SetOnPopupSelected.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, Event001, TestSize.Level1)
{
    bool isTrigger = false;
    OnPopupSelectedEvent event = [&isTrigger](int32_t) { isTrigger = true; };
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY_2, 2);
    model.SetUsingPopup(true);
    model.SetOnRequestPopupData(GetPopupData);
    model.SetOnPopupSelected(std::move(event));
    CreateDone();

    /**
     * @tc.steps: step1. Trigger OnPopupSelected callback.
     * @tc.expected: OnPopupSelected is called.
     */
    pattern_->MoveIndexByStep(1);
    pattern_->OnListItemClick(0);
    EXPECT_TRUE(isTrigger);
}

/**
 * @tc.name: Event002
 * @tc.desc: Test SetOnSelected.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, Event002, TestSize.Level1)
{
    bool isTrigger = false;
    OnSelectedEvent event = [&isTrigger](int32_t) { isTrigger = true; };
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetOnSelected(std::move(event));
    CreateDone();

    /**
     * @tc.steps: step1. Trigger OnSelected callback.
     * @tc.expected: OnSelected is called.
     */
    Touch(TouchType::UP, 20.f, 0);
    EXPECT_TRUE(isTrigger);
}

/**
 * @tc.name: Event003
 * @tc.desc: Test SetChangeEvent.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, Event003, TestSize.Level1)
{
    bool isTrigger = false;
    OnSelectedEvent event = [&isTrigger](int32_t) { isTrigger = true; };
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetChangeEvent(std::move(event));
    CreateDone();

    /**
     * @tc.steps: step1. Trigger OnSelected callback.
     * @tc.expected: OnSelected is called.
     */
    Touch(TouchType::UP, 20.f, 0);
    EXPECT_TRUE(isTrigger);
}

/**
 * @tc.name: Event004
 * @tc.desc: Test SetCreatChangeEvent.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, Event004, TestSize.Level1)
{
    bool isTrigger = false;
    OnSelectedEvent event = [&isTrigger](int32_t) { isTrigger = true; };
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetCreatChangeEvent(std::move(event));
    CreateDone();

    /**
     * @tc.steps: step1. Trigger OnSelected callback.
     * @tc.expected: OnSelected is called.
     */
    Touch(TouchType::UP, 20.f, 0);
    EXPECT_TRUE(isTrigger);
}

/**
 * @tc.name: IndexerModelNGTest001
 * @tc.desc: Test Create func with special arg
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerModelNGTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create with normal arg.
     */
    CreateIndexer(CREATE_ARRAY, 5);
    CreateDone();
    EXPECT_EQ(layoutProperty_->GetArrayValueValue(), CREATE_ARRAY);
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 5);

    /**
     * @tc.steps: step2. Set selected < 0.
     * @tc.expected: The selected would be 0.
     */
    ClearOldNodes();
    CreateIndexer(CREATE_ARRAY, -1);
    CreateDone();
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);

    /**
     * @tc.steps: step3. Set selected > array size.
     * @tc.expected: The selected would be 0.
     */
    ClearOldNodes();
    CreateIndexer(CREATE_ARRAY, CREATE_ARRAY.size() + 11);
    CreateDone();
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);
}

/**
 * @tc.name: IndexerModelNGTest002
 * @tc.desc: Test all the properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerModelNGTest002, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetSelectedColor(Color(0x00000000));
    model.SetColor(Color(0x00000000));
    model.SetPopupColor(Color(0x00000000));
    model.SetSelectedBackgroundColor(Color(0x00000000));
    model.SetPopupBackground(Color(0x00000000));
    model.SetUsingPopup(true);
    model.SetItemSize(Dimension(24));
    model.SetAlignStyle(0);
    model.SetPopupHorizontalSpace(Dimension(50));
    model.SetSelected(0);
    model.SetPopupPositionX(Dimension(-96.f, DimensionUnit::VP));
    model.SetPopupPositionY(Dimension(48.f, DimensionUnit::VP));
    model.SetPopupItemBackground(Color(0x00000000));
    model.SetPopupSelectedColor(Color(0x00000000));
    model.SetPopupUnselectedColor(Color(0x00000000));
    model.SetFontSize(Dimension(24));
    model.SetFontWeight(FontWeight::MEDIUM);
    CreateDone();

    /**
     * @tc.steps: step1. Get properties.
     * @tc.expected: Properties are correct.
     */
    EXPECT_EQ(layoutProperty_->GetArrayValueValue(), CREATE_ARRAY);
    EXPECT_EQ(layoutProperty_->GetSelectedColorValue(), Color(0x00000000));
    EXPECT_EQ(layoutProperty_->GetColorValue(), Color(0x00000000));
    EXPECT_EQ(layoutProperty_->GetPopupColorValue(), Color(0x00000000));
    EXPECT_EQ(paintProperty_->GetSelectedBackgroundColorValue(), Color(0x00000000));
    EXPECT_EQ(paintProperty_->GetPopupBackgroundValue(), Color(0x00000000));
    EXPECT_TRUE(layoutProperty_->GetUsingPopupValue());
    EXPECT_EQ(layoutProperty_->GetItemSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetAlignStyleValue(), AlignStyle::LEFT);
    EXPECT_EQ(layoutProperty_->GetPopupHorizontalSpaceValue(), Dimension(50));
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);
    EXPECT_EQ(layoutProperty_->GetPopupPositionXValue(), Dimension(-96.f, DimensionUnit::VP));
    EXPECT_EQ(layoutProperty_->GetPopupPositionYValue(), Dimension(48.f, DimensionUnit::VP));
    EXPECT_EQ(paintProperty_->GetPopupItemBackgroundValue(), Color(0x00000000));
    EXPECT_EQ(paintProperty_->GetPopupSelectedColorValue(), Color(0x00000000));
    EXPECT_EQ(paintProperty_->GetPopupUnselectedColorValue(), Color(0x00000000));
    EXPECT_EQ(layoutProperty_->GetFontSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetFontWeightValue(), FontWeight::MEDIUM);
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: IndexerModelNGTest003
 * @tc.desc: Test newly added properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerModelNGTest003, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetSelectedColor(std::nullopt);
    model.SetColor(std::nullopt);
    model.SetPopupColor(std::nullopt);
    model.SetItemSize(Dimension(-1));
    model.SetSelected(-1);
    model.SetPopupPositionX(std::nullopt);
    model.SetPopupPositionY(std::nullopt);
    model.SetSelectedBackgroundColor(std::nullopt);
    model.SetPopupBackground(std::nullopt);
    model.SetPopupSelectedColor(std::nullopt);
    model.SetPopupUnselectedColor(std::nullopt);
    model.SetPopupItemBackground(std::nullopt);
    model.SetPopupHorizontalSpace(Dimension(-1));
    model.SetFontSize(Dimension());
    CreateDone();

    /**
     * @tc.steps: step1. Get properties.
     * @tc.expected: Properties are correct.
     */
    EXPECT_FALSE(layoutProperty_->GetSelectedColor().has_value());
    EXPECT_FALSE(layoutProperty_->GetColor().has_value());
    EXPECT_FALSE(layoutProperty_->GetPopupColor().has_value());
    EXPECT_EQ(layoutProperty_->GetItemSizeValue(), Dimension(INDEXER_ITEM_SIZE, DimensionUnit::VP));
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);
    EXPECT_FALSE(layoutProperty_->GetPopupPositionX().has_value());
    EXPECT_FALSE(layoutProperty_->GetPopupPositionY().has_value());
    EXPECT_FALSE(paintProperty_->GetSelectedBackgroundColor().has_value());
    EXPECT_FALSE(paintProperty_->GetPopupBackground().has_value());
    EXPECT_FALSE(paintProperty_->GetPopupSelectedColor().has_value());
    EXPECT_FALSE(paintProperty_->GetPopupUnselectedColor().has_value());
    EXPECT_FALSE(paintProperty_->GetPopupItemBackground().has_value());
    EXPECT_FALSE(layoutProperty_->GetPopupHorizontalSpace().has_value());
    EXPECT_FALSE(layoutProperty_->GetFontSize().has_value());
}

/**
 * @tc.name: IndexerModelNGTest004
 * @tc.desc: Test newly added properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerModelNGTest004, TestSize.Level1)
{
    BlurStyleOption indexerBlurStyle;
    indexerBlurStyle.blurStyle = BlurStyle::COMPONENT_REGULAR;
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetPopupItemBorderRadius(Dimension(24));
    model.SetPopupBorderRadius(Dimension(28));
    model.SetItemBorderRadius(Dimension(12));
    model.SetIndexerBorderRadius(Dimension(16));
    model.SetPopupBackgroundBlurStyle(indexerBlurStyle);
    model.SetPopupTitleBackground(Color(0x00000000));
    CreateDone();

    /**
     * @tc.steps: step1. Get properties.
     * @tc.expected: Properties are correct.
     */
    EXPECT_EQ(paintProperty_->GetPopupItemBorderRadiusValue(), Dimension(24));
    EXPECT_EQ(paintProperty_->GetPopupBorderRadiusValue(), Dimension(28));
    EXPECT_EQ(paintProperty_->GetItemBorderRadiusValue(), Dimension(12));
    EXPECT_EQ(paintProperty_->GetIndexerBorderRadiusValue(), Dimension(16));
    EXPECT_EQ(paintProperty_->GetPopupBackgroundBlurStyleValue(), indexerBlurStyle);
    EXPECT_EQ(paintProperty_->GetPopupTitleBackgroundValue(), Color(0x00000000));
}

/**
 * @tc.name: IndexerModelNGTest005
 * @tc.desc: Test newly added properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerModelNGTest005, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetPopupTitleBackground(std::nullopt);
    CreateDone();

    /**
     * @tc.steps: step1. Get properties.
     * @tc.expected: Properties are correct.
     */
    EXPECT_FALSE(paintProperty_->GetPopupTitleBackground().has_value());
}

/**
 * @tc.name: IndexerModelNGTest006
 * @tc.desc: Test newly added properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerModelNGTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create indexer.
     */
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    CreateDone();
    model.SetFontSize(AceType::RawPtr(frameNode_), Dimension());
    model.SetPopupHorizontalSpace(AceType::RawPtr(frameNode_), Dimension(-1));
    model.SetPopupUnselectedColor(AceType::RawPtr(frameNode_), std::nullopt);
    model.SetPopupItemBackground(AceType::RawPtr(frameNode_), std::nullopt);
    model.SetColor(AceType::RawPtr(frameNode_), std::nullopt);
    model.SetPopupColor(AceType::RawPtr(frameNode_), std::nullopt);
    model.SetSelectedColor(AceType::RawPtr(frameNode_), std::nullopt);
    model.SetPopupBackground(AceType::RawPtr(frameNode_), std::nullopt);
    model.SetSelectedBackgroundColor(AceType::RawPtr(frameNode_), std::nullopt);
    model.SetPopupHorizontalSpace(AceType::RawPtr(frameNode_), Dimension(-1));
    model.SetSelected(AceType::RawPtr(frameNode_), -1);
    model.SetPopupSelectedColor(AceType::RawPtr(frameNode_), std::nullopt);
    model.SetItemSize(AceType::RawPtr(frameNode_), Dimension(-1));
    model.SetPopupPositionX(AceType::RawPtr(frameNode_), std::nullopt);
    model.SetPopupPositionY(AceType::RawPtr(frameNode_), std::nullopt);

    EXPECT_FALSE(layoutProperty_->GetSelectedColor().has_value());
    EXPECT_FALSE(layoutProperty_->GetColor().has_value());
    EXPECT_FALSE(layoutProperty_->GetPopupColor().has_value());
    EXPECT_EQ(layoutProperty_->GetItemSizeValue(), Dimension(INDEXER_ITEM_SIZE, DimensionUnit::VP));
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);
    EXPECT_FALSE(layoutProperty_->GetPopupPositionX().has_value());
    EXPECT_FALSE(layoutProperty_->GetPopupPositionY().has_value());
    EXPECT_FALSE(paintProperty_->GetSelectedBackgroundColor().has_value());
    EXPECT_FALSE(paintProperty_->GetPopupBackground().has_value());
    EXPECT_FALSE(paintProperty_->GetPopupSelectedColor().has_value());
    EXPECT_FALSE(paintProperty_->GetPopupUnselectedColor().has_value());
    EXPECT_FALSE(paintProperty_->GetPopupItemBackground().has_value());
    EXPECT_FALSE(layoutProperty_->GetPopupHorizontalSpace().has_value());
    EXPECT_FALSE(layoutProperty_->GetFontSize().has_value());
}

/**
 * @tc.name: IndexerModelNGTest007
 * @tc.desc: Test newly added properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerModelNGTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create indexer.
     */
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    CreateDone();
    model.SetSelectedColor(AceType::RawPtr(frameNode_), Color::WHITE);
    model.SetColor(AceType::RawPtr(frameNode_), Color::WHITE);
    model.SetPopupColor(AceType::RawPtr(frameNode_), Color::WHITE);
    model.SetSelectedBackgroundColor(AceType::RawPtr(frameNode_), Color::WHITE);
    model.SetPopupBackground(AceType::RawPtr(frameNode_), Color::WHITE);
    model.SetUsingPopup(AceType::RawPtr(frameNode_), true);
    model.SetItemSize(AceType::RawPtr(frameNode_), Dimension(24));
    model.SetAlignStyle(AceType::RawPtr(frameNode_), 0);
    model.SetPopupHorizontalSpace(AceType::RawPtr(frameNode_), Dimension(50));
    model.SetSelected(AceType::RawPtr(frameNode_), 0);
    model.SetPopupPositionX(AceType::RawPtr(frameNode_), Dimension(-96.f, DimensionUnit::VP));
    model.SetPopupPositionY(AceType::RawPtr(frameNode_), Dimension(48.f, DimensionUnit::VP));
    model.SetPopupItemBackground(AceType::RawPtr(frameNode_), Color::WHITE);
    model.SetPopupSelectedColor(AceType::RawPtr(frameNode_), Color::WHITE);
    model.SetPopupUnselectedColor(AceType::RawPtr(frameNode_), Color::WHITE);
    model.SetFontSize(AceType::RawPtr(frameNode_), Dimension(24));
    model.SetFontWeight(AceType::RawPtr(frameNode_), FontWeight::MEDIUM);

    EXPECT_EQ(layoutProperty_->GetArrayValueValue(), CREATE_ARRAY);
    EXPECT_EQ(layoutProperty_->GetSelectedColorValue(), Color::WHITE);
    EXPECT_EQ(layoutProperty_->GetColorValue(), Color::WHITE);
    EXPECT_EQ(layoutProperty_->GetPopupColorValue(), Color::WHITE);
    EXPECT_EQ(paintProperty_->GetSelectedBackgroundColorValue(), Color::WHITE);
    EXPECT_EQ(paintProperty_->GetPopupBackgroundValue(), Color::WHITE);
    EXPECT_TRUE(layoutProperty_->GetUsingPopupValue());
    EXPECT_EQ(layoutProperty_->GetItemSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetAlignStyleValue(), AlignStyle::LEFT);
    EXPECT_EQ(layoutProperty_->GetPopupHorizontalSpaceValue(), Dimension(50));
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);
    EXPECT_EQ(layoutProperty_->GetPopupPositionXValue(), Dimension(-96.f, DimensionUnit::VP));
    EXPECT_EQ(layoutProperty_->GetPopupPositionYValue(), Dimension(48.f, DimensionUnit::VP));
    EXPECT_EQ(paintProperty_->GetPopupItemBackgroundValue(), Color::WHITE);
    EXPECT_EQ(paintProperty_->GetPopupSelectedColorValue(), Color::WHITE);
    EXPECT_EQ(paintProperty_->GetPopupUnselectedColorValue(), Color::WHITE);
    EXPECT_EQ(layoutProperty_->GetFontSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetFontWeightValue(), FontWeight::MEDIUM);
}

/**
 * @tc.name: IndexerModelNGTest008
 * @tc.desc: Test newly added properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerModelNGTest008, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetAdaptiveWidth(true);
    CreateDone();

    /**
     * @tc.steps: step1. Get properties.
     * @tc.expected: Properties are correct.
     */
    EXPECT_TRUE(layoutProperty_->GetAdaptiveWidthValue());
}

/**
 * @tc.name: OnModifyDone001
 * @tc.desc: Test OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, OnModifyDone001, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetUsingPopup(true);
    CreateDone();

    /**
     * @tc.steps: step1. change UsingPopup
     * @tc.expected: would trigger RemoveBubble
     */
    layoutProperty_->UpdateUsingPopup(false);
    pattern_->OnModifyDone();
    EXPECT_FALSE(pattern_->isPopup_);
}

/**
 * @tc.name: OnModifyDone002
 * @tc.desc: Test OnModifyDone when autoCollapse is close
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, OnModifyDone002, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetAutoCollapse(false);
    CreateDone();

    pattern_->OnModifyDone();
    EXPECT_EQ(pattern_->fullArrayValue_.size(), CREATE_ARRAY.size());
    EXPECT_EQ(pattern_->arrayValue_.size(), CREATE_ARRAY.size());
    for (auto value : pattern_->arrayValue_) {
        EXPECT_FALSE(value.second);
    }
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::INVALID);
    EXPECT_FALSE(pattern_->autoCollapse_);
}

/**
 * @tc.name: OnModifyDone003
 * @tc.desc: Test OnModifyDone when autoCollapse is open, and mode is 5+1
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, OnModifyDone003, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetAutoCollapse(true);
    model.SetItemSize(Dimension(10, DimensionUnit::VP));
    pattern_->maxContentHeight_ = 100.f;
    CreateDone();

    std::vector<std::pair<std::string, bool>> arrayValueRst;
    arrayValueRst.push_back(std::pair("A", false));
    arrayValueRst.push_back(std::pair("B", true));
    arrayValueRst.push_back(std::pair("G", false));
    arrayValueRst.push_back(std::pair("H", true));
    arrayValueRst.push_back(std::pair("M", false));
    arrayValueRst.push_back(std::pair("N", true));
    arrayValueRst.push_back(std::pair("S", false));
    arrayValueRst.push_back(std::pair("T", true));
    arrayValueRst.push_back(std::pair("Z", false));

    EXPECT_TRUE(pattern_->autoCollapse_);
    EXPECT_EQ(pattern_->fullArrayValue_.size(), CREATE_ARRAY.size());
    EXPECT_EQ(pattern_->arrayValue_.size(), arrayValueRst.size());
    for (int32_t index = 0; index < arrayValueRst.size(); index++) {
        EXPECT_EQ(arrayValueRst[index].first, pattern_->arrayValue_[index].first);
        EXPECT_EQ(arrayValueRst[index].second, pattern_->arrayValue_[index].second);
    }
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
}

/**
 * @tc.name: OnModifyDone004
 * @tc.desc: Test OnModifyDone when autoCollapse is open, and mode is 7+1
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, OnModifyDone004, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetAutoCollapse(true);
    model.SetItemSize(Dimension(6, DimensionUnit::VP));
    pattern_->maxContentHeight_ = 60.f;
    CreateDone();

    std::vector<std::pair<std::string, bool>> arrayValueRst;
    arrayValueRst.push_back(std::pair("A", false));
    arrayValueRst.push_back(std::pair("B", true));
    arrayValueRst.push_back(std::pair("G", false));
    arrayValueRst.push_back(std::pair("H", true));
    arrayValueRst.push_back(std::pair("M", false));
    arrayValueRst.push_back(std::pair("N", true));
    arrayValueRst.push_back(std::pair("S", false));
    arrayValueRst.push_back(std::pair("T", true));
    arrayValueRst.push_back(std::pair("Z", false));

    EXPECT_TRUE(pattern_->autoCollapse_);
    EXPECT_EQ(pattern_->fullArrayValue_.size(), CREATE_ARRAY.size());
    EXPECT_EQ(pattern_->arrayValue_.size(), arrayValueRst.size());
    for (int32_t index = 0; index < arrayValueRst.size(); index++) {
        EXPECT_EQ(arrayValueRst[index].first, pattern_->arrayValue_[index].first);
        EXPECT_EQ(arrayValueRst[index].second, pattern_->arrayValue_[index].second);
    }
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
}

/**
 * @tc.name: OnModifyDone005
 * @tc.desc: Test OnModifyDone when autoCollapse is open, item size is larger than pattern height
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, OnModifyDone005, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetAutoCollapse(true);
    model.SetItemSize(Dimension(2000, DimensionUnit::VP));
    pattern_->maxContentHeight_ = 100.f;
    CreateDone();

    std::vector<std::pair<std::string, bool>> arrayValueRst;
    arrayValueRst.push_back(std::pair("A", false));
    arrayValueRst.push_back(std::pair("B", true));
    arrayValueRst.push_back(std::pair("G", false));
    arrayValueRst.push_back(std::pair("H", true));
    arrayValueRst.push_back(std::pair("M", false));
    arrayValueRst.push_back(std::pair("N", true));
    arrayValueRst.push_back(std::pair("S", false));
    arrayValueRst.push_back(std::pair("T", true));
    arrayValueRst.push_back(std::pair("Z", false));

    EXPECT_TRUE(pattern_->autoCollapse_);
    EXPECT_EQ(pattern_->fullArrayValue_.size(), CREATE_ARRAY.size());
    EXPECT_EQ(pattern_->arrayValue_.size(), arrayValueRst.size());
    for (int32_t index = 0; index < arrayValueRst.size(); index++) {
        EXPECT_EQ(arrayValueRst[index].first, pattern_->arrayValue_[index].first);
        EXPECT_EQ(arrayValueRst[index].second, pattern_->arrayValue_[index].second);
    }
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
}

/**
 * @tc.name: OnModifyDone006
 * @tc.desc: Test OnModifyDone when autoCollapse is open, and created arrayValue size is less than 9
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, OnModifyDone006, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY_1, 0);
    model.SetAutoCollapse(true);
    model.SetItemSize(Dimension(10, DimensionUnit::VP));
    CreateDone();

    EXPECT_FALSE(pattern_->autoCollapse_);
    EXPECT_EQ(pattern_->fullArrayValue_.size(), CREATE_ARRAY_1.size());
    EXPECT_EQ(pattern_->arrayValue_.size(), CREATE_ARRAY_1.size());
    for (auto value : pattern_->arrayValue_) {
        EXPECT_FALSE(value.second);
    }
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::NONE);
}

/**
 * @tc.name: OnModifyDone007
 * @tc.desc: Test OnModifyDone when autoCollapse is open, and arrayValue size is more than 9,
 *           pattern height is enough to contain all items
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, OnModifyDone007, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY_1, 0);
    model.SetAutoCollapse(true);
    model.SetItemSize(Dimension(10, DimensionUnit::VP));
    CreateDone();

    EXPECT_FALSE(pattern_->autoCollapse_);
    EXPECT_EQ(pattern_->fullArrayValue_.size(), CREATE_ARRAY_1.size());
    EXPECT_EQ(pattern_->arrayValue_.size(), CREATE_ARRAY_1.size());
    for (auto value : pattern_->arrayValue_) {
        EXPECT_FALSE(value.second);
    }
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::NONE);
}

/**
 * @tc.name: OnModifyDone008
 * @tc.desc: Test OnModifyDone when autoCollapse is open, and arrayValue size is more than 9,
 *           pattern height is not enough to contain all items
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, OnModifyDone008, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY_2, 0);
    model.SetAutoCollapse(true);
    model.SetItemSize(Dimension(10, DimensionUnit::VP));
    pattern_->maxContentHeight_ = 100.f;
    CreateDone();

    std::vector<std::pair<std::string, bool>> arrayValueRst;
    arrayValueRst.push_back(std::pair("#", false));
    arrayValueRst.push_back(std::pair("A", false));
    arrayValueRst.push_back(std::pair("B", true));
    arrayValueRst.push_back(std::pair("C", false));
    arrayValueRst.push_back(std::pair("D", true));
    arrayValueRst.push_back(std::pair("F", false));
    arrayValueRst.push_back(std::pair("G", true));
    arrayValueRst.push_back(std::pair("I", false));
    arrayValueRst.push_back(std::pair("J", true));
    arrayValueRst.push_back(std::pair("L", false));

    EXPECT_TRUE(pattern_->autoCollapse_);
    EXPECT_EQ(pattern_->fullArrayValue_.size(), CREATE_ARRAY_2.size());
    EXPECT_EQ(pattern_->arrayValue_.size(), arrayValueRst.size());
    for (int32_t index = 0; index < arrayValueRst.size(); index++) {
        EXPECT_EQ(arrayValueRst[index].first, pattern_->arrayValue_[index].first);
        EXPECT_EQ(arrayValueRst[index].second, pattern_->arrayValue_[index].second);
    }
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
}

/**
 * @tc.name: IndexerLayoutAlgorithm001
 * @tc.desc: Test indexer layoutAlgorithm GetPositionOfPopupNode function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerLayoutAlgorithm001, TestSize.Level1)
{
    /**
     * @tc.case: case1: popup position is default.
     */
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 2);
    model.SetUsingPopup(true);
    model.SetOnRequestPopupData(GetPopupData);
    CreateDone();

    auto indexerLayoutAlgorithm = AceType::DynamicCast<IndexerLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indexerLayoutProperty1 = pattern_->GetLayoutProperty<IndexerLayoutProperty>();
    auto offset = indexerLayoutAlgorithm->GetPositionOfPopupNode(indexerLayoutProperty1, 40);
    EXPECT_EQ(offset, OffsetT<Dimension>(Dimension(-96), Dimension(48)));

    /**
     * @tc.case: case2: popup position is custom.
     */
    std::optional<Dimension> xOpt = Dimension(30);
    std::optional<Dimension> yOpt = Dimension(20);
    model = CreateIndexer(CREATE_ARRAY, 2);
    model.SetUsingPopup(true);
    model.SetPopupPositionX(xOpt);
    model.SetPopupPositionY(yOpt);
    model.SetOnRequestPopupData(GetPopupData);
    CreateDone();

    auto indexerLayoutProperty2 = pattern_->GetLayoutProperty<IndexerLayoutProperty>();
    offset = indexerLayoutAlgorithm->GetPositionOfPopupNode(indexerLayoutProperty2, 40);
    EXPECT_EQ(offset, OffsetT<Dimension>(Dimension(-66), Dimension(20)));

    /**
     * @tc.case: case3: popup horizontal space is custom.
     */
    ClearOldNodes();
    xOpt = Dimension(30);
    yOpt = Dimension(20);
    model = CreateIndexer(CREATE_ARRAY, 2);
    model.SetPopupHorizontalSpace(Dimension(50));
    model.SetUsingPopup(true);
    model.SetPopupPositionX(xOpt);
    model.SetPopupPositionY(yOpt);
    model.SetOnRequestPopupData(GetPopupData);
    CreateDone();

    auto indexerLayoutProperty3 = pattern_->GetLayoutProperty<IndexerLayoutProperty>();
    offset = indexerLayoutAlgorithm->GetPositionOfPopupNode(indexerLayoutProperty3, 40);
    EXPECT_EQ(offset, OffsetT<Dimension>(Dimension(-106), Dimension(20)));

    /**
     * @tc.case: case4: align is left.
     */
    ClearOldNodes();
    xOpt = Dimension(30);
    yOpt = Dimension(-20);
    model = CreateIndexer(CREATE_ARRAY, 2);
    model.SetAlignStyle(0);
    model.SetUsingPopup(true);
    model.SetPopupPositionX(xOpt);
    model.SetPopupPositionY(yOpt);
    model.SetOnRequestPopupData(GetPopupData);
    CreateDone();

    auto indexerLayoutProperty4 = pattern_->GetLayoutProperty<IndexerLayoutProperty>();
    ASSERT_NE(indexerLayoutProperty4, nullptr);
    offset = indexerLayoutAlgorithm->GetPositionOfPopupNode(indexerLayoutProperty4, 40);
    EXPECT_EQ(offset, OffsetT<Dimension>(Dimension(50), Dimension(-20)));
}

/**
 * @tc.name: IndexerLayoutAlgorithm002
 * @tc.desc: Test indexer layoutAlgorithm GetPositionOfPopupNode function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerLayoutAlgorithm002, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 2);
    model.SetUsingPopup(true);
    model.SetOnRequestPopupData(GetPopupData);
    CreateDone();

    auto indexerLayoutAlgorithm = AceType::DynamicCast<IndexerLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indexerLayoutProperty1 = pattern_->GetLayoutProperty<IndexerLayoutProperty>();
    auto userDefinePositionX = Dimension(NG::BUBBLE_POSITION_X, DimensionUnit::VP).ConvertToPx();
    auto userDefinePositionRightX = userDefinePositionX + INDEXER_WIDTH / 2;
    auto bubbleSize = Dimension(BUBBLE_BOX_SIZE, DimensionUnit::VP).ConvertToPx();
    auto userDefinePositionLeftX = -userDefinePositionX + INDEXER_WIDTH / 2 - bubbleSize;

    /**
     * case: case1: popup position is left.
     */
    indexerLayoutProperty1->UpdateAlignStyle(NG::AlignStyle::LEFT);
    auto offset = indexerLayoutAlgorithm->GetPositionOfPopupNode(indexerLayoutProperty1, INDEXER_WIDTH);
    EXPECT_EQ(offset.GetX(), Dimension(userDefinePositionRightX));

    /**
     * case: case2: popup position is right.
     */
    indexerLayoutProperty1->UpdateAlignStyle(NG::AlignStyle::RIGHT);
    offset = indexerLayoutAlgorithm->GetPositionOfPopupNode(indexerLayoutProperty1, INDEXER_WIDTH);
    EXPECT_EQ(offset.GetX(), Dimension(userDefinePositionLeftX));
}

/**
 * @tc.name: IndexerLayoutAlgorithm003
 * @tc.desc: Test indexer layoutAlgorithm GetPositionOfPopupNode function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerLayoutAlgorithm003, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 2);
    model.SetUsingPopup(true);
    model.SetOnRequestPopupData(GetPopupData);
    CreateDone();

    auto indexerLayoutAlgorithm = AceType::DynamicCast<IndexerLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indexerLayoutProperty1 = pattern_->GetLayoutProperty<IndexerLayoutProperty>();
    auto userDefinePositionX = Dimension(NG::BUBBLE_POSITION_X, DimensionUnit::VP).ConvertToPx();
    auto userDefinePositionRightX = userDefinePositionX + INDEXER_WIDTH / 2;
    auto bubbleSize = Dimension(BUBBLE_BOX_SIZE, DimensionUnit::VP).ConvertToPx();
    auto userDefinePositionLeftX = -userDefinePositionX + INDEXER_WIDTH / 2 - bubbleSize;
    
    /**
     * case: case1: popup position is default(END) and layoutDirection is RTL
     */
    indexerLayoutProperty1->UpdateLayoutDirection(TextDirection::RTL);
    auto offset = indexerLayoutAlgorithm->GetPositionOfPopupNode(indexerLayoutProperty1, INDEXER_WIDTH);
    EXPECT_EQ(offset.GetX(), Dimension(userDefinePositionRightX));

    /**
     * case: case2: popup position is default(END) and layoutDirection is LTR
     */
    indexerLayoutProperty1->UpdateLayoutDirection(TextDirection::LTR);
    offset = indexerLayoutAlgorithm->GetPositionOfPopupNode(indexerLayoutProperty1, INDEXER_WIDTH);
    EXPECT_EQ(offset.GetX(), Dimension(userDefinePositionLeftX));

    /**
     * case: case3: popup position is START and layoutDirection is RTL
     */
    indexerLayoutProperty1->UpdateAlignStyle(NG::AlignStyle::START);
    indexerLayoutProperty1->UpdateLayoutDirection(TextDirection::RTL);
    offset = indexerLayoutAlgorithm->GetPositionOfPopupNode(indexerLayoutProperty1, INDEXER_WIDTH);
    EXPECT_EQ(offset.GetX(), Dimension(userDefinePositionLeftX));

    /**
     * case: case4: popup position is START and layoutDirection is LTR
     */
    indexerLayoutProperty1->UpdateLayoutDirection(TextDirection::LTR);
    offset = indexerLayoutAlgorithm->GetPositionOfPopupNode(indexerLayoutProperty1, INDEXER_WIDTH);
    EXPECT_EQ(offset.GetX(), Dimension(userDefinePositionRightX));
}

/**
 * @tc.name: IndexerPatternCoverage001
 * @tc.desc: For Coverage Rate, branches that are not normally covered.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerPatternCoverage001, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetUsingPopup(true);
    CreateDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step1. Supplement MoveIndexByOffset branch,
     * the itemCount_ would not be 0 when itemHeight_ was not 0.
     */
    pattern_->itemCount_ = 0;
    pattern_->MoveIndexByOffset(Offset(0, 0));
    pattern_->itemCount_ = CREATE_ARRAY.size();

    /**
     * @tc.steps: step2. Supplement MoveIndexByStep branch,
     * has no condition that step is 0 when call panEvent_.
     */
    EXPECT_FALSE(pattern_->MoveIndexByStep(0));

    /**
     * @tc.steps: step3. Supplement GetFocusChildIndex branch,
     * has no condition that searchStr is ABC when MoveIndexBySearch.
     */
    pattern_->selected_ = 5;
    EXPECT_EQ(pattern_->GetFocusChildIndex("ABC"), -1);

    /**
     * @tc.steps: step4. Supplement OnSelect branch.
     * has no condition that selected_ more than itemCount_-1 when OnTouchUp.
     */
    pattern_->selected_ = CREATE_ARRAY.size();
    pattern_->OnSelect();

    /**
     * @tc.steps: step5. Supplement OnSelect branch.
     * has no condition that selected_ less than 0 when OnTouchUp.
     */
    pattern_->selected_ = -1;
    pattern_->OnSelect();

    /**
     * @tc.steps: step6. Supplement UpdateBubbleSize branch,
     * has no condition that has no popListData when showPopup.
     */
    pattern_->MoveIndexBySearch("C");
    pattern_->UpdateBubbleSize();

    EXPECT_TRUE(true);
}

/**
 * @tc.name: IndexerPatternCoverage002
 * @tc.desc: For Coverage Rate, branches that are not normally covered.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerPatternCoverage002, TestSize.Level1)
{
    CreateIndexer(CREATE_ARRAY, 0);
    CreateDone();

    /**
     * @tc.steps: step1. Supplement OnPopupTouchDown branch,
     * has no condition that NeedShowPopupView is false when showPopup.
     */
    TouchEventInfo touchEventInfo("onTouchDown");
    pattern_->OnPopupTouchDown(touchEventInfo);

    EXPECT_TRUE(true);
}

/**
 * @tc.name: AccessibilityTest001
 * @tc.desc: Test accessibility func.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, AccessibilityTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test GetEndIndex, GetText func.
     */
    CreateIndexer(CREATE_ARRAY, 0);
    CreateDone();
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), CREATE_ARRAY.size() - 1);
    EXPECT_EQ(accessibilityProperty_->GetText(), CREATE_ARRAY.at(0));

    /**
     * @tc.steps: step1. Create the arrayValue is empty
     */
    ClearOldNodes();
    CreateIndexer(std::vector<std::string>());
    CreateDone();
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), -1);
    EXPECT_EQ(accessibilityProperty_->GetText(), "");
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: Indexer Accessibility PerformAction test Select and ClearSelection.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, PerformActionTest001, TestSize.Level1)
{
    CreateIndexer(CREATE_ARRAY, 0);
    CreateDone();
    auto thirdTextAccessibilityProperty = GetChildAccessibilityProperty<AccessibilityProperty>(frameNode_, 2);
    auto fifthTextAccessibilityProperty = GetChildAccessibilityProperty<AccessibilityProperty>(frameNode_, 4);

    /**
     * @tc.steps: step1. select a text node
     */
    thirdTextAccessibilityProperty->ActActionSelect();
    EXPECT_EQ(pattern_->GetSelected(), 2);

    /**
     * @tc.steps: step2. Clear select
     */
    thirdTextAccessibilityProperty->ActActionClearSelection();
    EXPECT_EQ(pattern_->GetSelected(), 0);

    /**
     * @tc.steps: step3. Change select
     */
    fifthTextAccessibilityProperty->ActActionSelect();
    EXPECT_EQ(pattern_->GetSelected(), 4);

    /**
     * @tc.steps: step4. Clear select
     */
    fifthTextAccessibilityProperty->ActActionClearSelection();
    EXPECT_EQ(pattern_->GetSelected(), 0);

    /**
     * @tc.steps: step5. Clear select again
     */
    fifthTextAccessibilityProperty->ActActionClearSelection();
    EXPECT_EQ(pattern_->GetSelected(), 0);
}

/**
 * @tc.name: IndexerEnableHapticFeedback001
 * @tc.desc: Test property enableHapticFeedback by default
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerEnableHapticFeedback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test with empty array.
     * @tc.expected: Selected unchanged.
     */
    CreateIndexer(std::vector<std::string>());
    CreateDone();
    EXPECT_TRUE(pattern_->enableHapticFeedback_);
}

/**
 * @tc.name: IndexerEnableHapticFeedback002
 * @tc.desc: Test property enableHapticFeedback by Setter API
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerEnableHapticFeedback002, TestSize.Level1)
{
    std::vector<bool> testValues = { false, true, true, false, false };
    for (auto testValue : testValues) {
        IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 2);
        model.SetEnableHapticFeedback(testValue);
        CreateDone();
        ASSERT_NE(pattern_, nullptr);
        EXPECT_EQ(pattern_->enableHapticFeedback_, testValue);
    }
}

/**
 * @tc.name: IndexerEnableHapticFeedback003
 * @tc.desc: Test property enableHapticFeedback by Setter/Getter API
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerEnableHapticFeedback003, TestSize.Level1)
{
    std::vector<bool> testValues = { false, true, true, false, false };
    for (auto testValue : testValues) {
        IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 2);
        model.SetEnableHapticFeedback(testValue);
        CreateDone();
        ASSERT_NE(pattern_, nullptr);
        auto indexerLayoutProperty = pattern_->GetLayoutProperty<IndexerLayoutProperty>();
        ASSERT_NE(indexerLayoutProperty, nullptr);
        auto value = indexerLayoutProperty->GetEnableHapticFeedback().value_or(!testValue);
        EXPECT_EQ(value, testValue);
    }
}
} // namespace OHOS::Ace::NG
