/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include <optional>

#include "gtest/gtest.h"

#include "base/geometry/dimension.h"

#define protected public
#define private public
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/indexer/indexer_layout_property.h"
#include "core/components_ng/pattern/indexer/indexer_model_ng.h"
#include "core/components_ng/pattern/indexer/indexer_paint_property.h"
#include "core/components_ng/pattern/indexer/indexer_pattern.h"
#include "core/components_ng/pattern/indexer/indexer_theme.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float DEFAULT_ROOT_WIDTH = 720.f;
constexpr float DEFAULT_ROOT_HEIGHT = 1136.f;
std::vector<std::string> CREATE_ARRAY = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O",
    "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
std::vector<std::string> GetPopupData(int32_t)
{
    return { "白", "别" };
}
std::vector<std::string> GetMorePopupData(int32_t)
{
    return { "白", "别", "吧", "不", "被" };
}
} // namespace

class IndexerTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();
    void RunMeasureAndLayout();

    RefPtr<FrameNode> frameNode_;
    RefPtr<IndexerPattern> pattern_;
    RefPtr<IndexerEventHub> eventHub_;
    RefPtr<IndexerLayoutProperty> layoutProperty_;
    RefPtr<IndexerPaintProperty> paintProperty_;
    RefPtr<IndexerAccessibilityProperty> accessibilityProperty_;
};

void IndexerTestNg::SetUpTestSuite()
{
    MockPipelineBase::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    PipelineContext::GetCurrentContext()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<IndexerTheme>()));
}

void IndexerTestNg::TearDownTestSuite()
{
    MockPipelineBase::TearDown();
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
}

void IndexerTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<IndexerPattern>();
    eventHub_ = frameNode_->GetEventHub<IndexerEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<IndexerLayoutProperty>();
    paintProperty_ = frameNode_->GetPaintProperty<IndexerPaintProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<IndexerAccessibilityProperty>();
}

void IndexerTestNg::RunMeasureAndLayout()
{
    RefPtr<LayoutWrapper> layoutWrapper = frameNode_->CreateLayoutWrapper(false, false);
    layoutWrapper->SetActive();
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.parentIdealSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.percentReference = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.maxSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    layoutWrapper->Measure(LayoutConstraint);
    layoutWrapper->Layout();
    layoutWrapper->MountToHostOnMainThread();
}

/**
 * @tc.name: IndexerMoveIndex001
 * @tc.desc: Test panEvent_ MoveIndexByStep func.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerMoveIndex001, TestSize.Level1)
{
    IndexerModelNG IndexerModelNG;
    IndexerModelNG.Create(CREATE_ARRAY, 0);
    GetInstance();
    RunMeasureAndLayout();
    ASSERT_NE(pattern_->panEvent_, nullptr);

    /**
     * @tc.steps: step1. Delta is 0.
     * @tc.expected: Selected unchanged.
     */
    auto start = pattern_->panEvent_->GetActionStartEventFunc();
    auto update = pattern_->panEvent_->GetActionUpdateEventFunc();
    GestureEvent gestureEvent;
    gestureEvent.SetInputEventType(InputEventType::AXIS);

    gestureEvent.SetMainDelta(0.f);
    start(gestureEvent);
    update(gestureEvent);
    EXPECT_EQ(pattern_->GetSelected(), 0);

    /**
     * @tc.steps: step2. Delta is 1.
     * @tc.expected: Selected unchanged.
     */
    gestureEvent.SetMainDelta(1.f);
    start(gestureEvent);
    update(gestureEvent);
    EXPECT_EQ(pattern_->GetSelected(), 0);

    /**
     * @tc.steps: step3. Delta is -1.
     * @tc.expected: Selected += 1.
     */
    gestureEvent.SetMainDelta(-1.f);
    start(gestureEvent);
    update(gestureEvent);
    EXPECT_EQ(pattern_->GetSelected(), 1);

    /**
     * @tc.steps: step4. Delta is 1, selected_ is itemCount-1.
     * @tc.expected: Selected unchanged.
     */
    pattern_->selected_ = pattern_->itemCount_ - 1;
    gestureEvent.SetMainDelta(-1.f);
    start(gestureEvent);
    update(gestureEvent);
    EXPECT_EQ(pattern_->GetSelected(), pattern_->itemCount_ - 1);
}

/**
 * @tc.name: IndexerMoveIndex002
 * @tc.desc: Test panEvent_ MoveIndexByOffset func.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerMoveIndex002, TestSize.Level1)
{
    IndexerModelNG IndexerModelNG;
    IndexerModelNG.Create(CREATE_ARRAY, 0);
    GetInstance();
    RunMeasureAndLayout();
    ASSERT_NE(pattern_->panEvent_, nullptr);

    /**
     * @tc.steps: step1. Location is (0, 50).
     * @tc.expected: Selected change to correct index.
     */
    auto start = pattern_->panEvent_->GetActionStartEventFunc();
    auto update = pattern_->panEvent_->GetActionUpdateEventFunc();
    GestureEvent gestureEvent;
    gestureEvent.SetInputEventType(InputEventType::KEYBOARD);

    gestureEvent.SetLocalLocation(Offset(0.f, 50.f));
    start(gestureEvent);
    update(gestureEvent);
    EXPECT_EQ(pattern_->GetSelected(), static_cast<int32_t>(50.f / pattern_->itemSizeRender_));

    /**
     * @tc.steps: step2. Location is (0, 50).
     * @tc.expected: Selected unchanged.
     */
    gestureEvent.SetLocalLocation(Offset(0.f, 50.f));
    start(gestureEvent);
    update(gestureEvent);
    EXPECT_EQ(pattern_->GetSelected(), static_cast<int32_t>(50.f / pattern_->itemSizeRender_));
}

/**
 * @tc.name: IndexerMoveIndex003
 * @tc.desc: Test panEvent_ MoveIndexByOffset func with empty array.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerMoveIndex003, TestSize.Level1)
{
    std::vector<std::string> arrayValue;
    IndexerModelNG IndexerModelNG;
    IndexerModelNG.Create(arrayValue, 0); // empty array
    GetInstance();
    RunMeasureAndLayout();
    ASSERT_NE(pattern_->panEvent_, nullptr);

    /**
     * @tc.steps: step1. itemSizeRender_ is 0.
     * @tc.expected: Selected unchanged.
     */
    auto start = pattern_->panEvent_->GetActionStartEventFunc();
    auto update = pattern_->panEvent_->GetActionUpdateEventFunc();
    GestureEvent gestureEvent;
    gestureEvent.SetInputEventType(InputEventType::KEYBOARD);
    gestureEvent.SetLocalLocation(Offset(0.f, 0.f));
    start(gestureEvent);
    update(gestureEvent);
    EXPECT_EQ(pattern_->GetSelected(), 0);
}

/**
 * @tc.name: IndexerTouch001
 * @tc.desc: Test touchListener_ func with hover.
 * @tc.desc: and touchDown touchUp in differrnt location.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerTouch001, TestSize.Level1)
{
    IndexerModelNG IndexerModelNG;
    IndexerModelNG.Create(CREATE_ARRAY, 0);
    GetInstance();
    RunMeasureAndLayout();
    ASSERT_NE(pattern_->touchListener_, nullptr);

    /**
     * @tc.steps: step1. OnTouchDown.
     * @tc.expected: Selected index is correct.
     */
    pattern_->OnHover(true);
    TouchLocationInfo touchLocationInfo1(1);
    touchLocationInfo1.SetTouchType(TouchType::DOWN);
    touchLocationInfo1.SetLocalLocation(Offset(0.f, 50.f));
    TouchEventInfo touchEventInfo1("onTouchDown");
    touchEventInfo1.AddTouchLocationInfo(std::move(touchLocationInfo1));
    auto touch = pattern_->touchListener_->GetTouchEventCallback();
    touch(touchEventInfo1);
    EXPECT_EQ(pattern_->GetSelected(), static_cast<int32_t>(50.f / pattern_->itemSizeRender_));

    /**
     * @tc.steps: step2. OnTouchUp, differrnt location.
     * @tc.expected: Selected index is correct.
     */
    TouchLocationInfo touchLocationInfo2(1);
    touchLocationInfo2.SetTouchType(TouchType::UP);
    touchLocationInfo2.SetLocalLocation(Offset(0.f, 20.f));
    TouchEventInfo touchEventInfo2("onTouchUp");
    touchEventInfo2.AddTouchLocationInfo(std::move(touchLocationInfo2));
    touch(touchEventInfo2);
    EXPECT_EQ(pattern_->GetSelected(), static_cast<int32_t>(20.f / pattern_->itemSizeRender_));
}

/**
 * @tc.name: IndexerTouch002
 * @tc.desc: Test touchListener_ func with no hover,
 * @tc.desc: and touchDown touchUp in same location.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerTouch002, TestSize.Level1)
{
    IndexerModelNG IndexerModelNG;
    IndexerModelNG.Create(CREATE_ARRAY, 0);
    GetInstance();
    RunMeasureAndLayout();
    ASSERT_NE(pattern_->touchListener_, nullptr);

    /**
     * @tc.steps: step1. OnTouchDown.
     * @tc.expected: Selected index is correct.
     */
    pattern_->OnHover(false);
    TouchLocationInfo touchLocationInfo1(1);
    touchLocationInfo1.SetTouchType(TouchType::DOWN);
    touchLocationInfo1.SetLocalLocation(Offset(0.f, 50.f));
    TouchEventInfo touchEventInfo1("onTouchDown");
    touchEventInfo1.AddTouchLocationInfo(std::move(touchLocationInfo1));
    auto touch = pattern_->touchListener_->GetTouchEventCallback();
    touch(touchEventInfo1);
    EXPECT_EQ(pattern_->GetSelected(), static_cast<int32_t>(50.f / pattern_->itemSizeRender_));

    /**
     * @tc.steps: step2. OnTouchUp, same location.
     * @tc.expected: Selected index is correct.
     */
    TouchLocationInfo touchLocationInfo2(1);
    touchLocationInfo2.SetTouchType(TouchType::UP);
    touchLocationInfo2.SetLocalLocation(Offset(0.f, 50.f));
    TouchEventInfo touchEventInfo2("onTouchUp");
    touchEventInfo2.AddTouchLocationInfo(std::move(touchLocationInfo2));
    touch(touchEventInfo2);
    EXPECT_EQ(pattern_->GetSelected(), static_cast<int32_t>(50.f / pattern_->itemSizeRender_));
}

/**
 * @tc.name: IndexerTouch003
 * @tc.desc: Test touchListener_ func with other TouchType.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerTouch003, TestSize.Level1)
{
    IndexerModelNG IndexerModelNG;
    IndexerModelNG.Create(CREATE_ARRAY, 0);
    GetInstance();
    RunMeasureAndLayout();
    ASSERT_NE(pattern_->touchListener_, nullptr);

    /**
     * @tc.steps: step1. TouchType::MOVE.
     * @tc.expected: Selected unchanged.
     */
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::MOVE);
    touchLocationInfo.SetLocalLocation(Offset(0.f, 20.f));
    TouchEventInfo touchEventInfo("touch");
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    auto touch = pattern_->touchListener_->GetTouchEventCallback();
    touch(touchEventInfo);
    EXPECT_EQ(pattern_->GetSelected(), 0);
}

/**
 * @tc.name: IndexerKeyEvent001
 * @tc.desc: Test OnKeyEvent func about KeyIndexByStep.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerKeyEvent001, TestSize.Level1)
{
    IndexerModelNG IndexerModelNG;
    IndexerModelNG.Create(CREATE_ARRAY, 0);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. UNKNOWN keyEvent.
     * @tc.expected: Selected unchanged.
     */
    KeyEvent keyEvent = KeyEvent();
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern_->GetSelected(), 0);

    /**
     * @tc.steps: step2. KEY_UNKNOWN from 0.
     * @tc.expected: Selected unchanged.
     */
    keyEvent.action = KeyAction::DOWN;
    keyEvent.code = KeyCode::KEY_UNKNOWN;
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern_->GetSelected(), 0);

    /**
     * @tc.steps: step3. KEY_DPAD_UP from 0.
     * @tc.expected: Selected unchanged.
     */
    keyEvent.code = KeyCode::KEY_DPAD_UP;
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern_->GetSelected(), 0);

    /**
     * @tc.steps: step4. KEY_DPAD_DOWN from 0.
     * @tc.expected: Selected += 1.
     */
    keyEvent.code = KeyCode::KEY_DPAD_DOWN;
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern_->GetSelected(), 1);

    /**
     * @tc.steps: step5. KEY_DPAD_DOWN from itemCount_-1.
     * @tc.expected: Selected unchanged.
     */
    pattern_->selected_ = pattern_->itemCount_ - 1;
    keyEvent.code = KeyCode::KEY_DPAD_DOWN;
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern_->GetSelected(), pattern_->itemCount_ - 1);
}

/**
 * @tc.name: IndexerKeyEvent002
 * @tc.desc: Test OnKeyEvent func about MoveIndexBySearch.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerKeyEvent002, TestSize.Level1)
{
    IndexerModelNG IndexerModelNG;
    IndexerModelNG.Create(CREATE_ARRAY, 0);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. IsCombinationKey && KEY_UNKNOWN.
     * @tc.expected: Selected unchanged.
     */
    KeyEvent keyEvent = KeyEvent();
    keyEvent.action = KeyAction::DOWN;
    keyEvent.code = KeyCode::KEY_UNKNOWN;
    keyEvent.pressedCodes = { KeyCode::KEY_A, KeyCode::KEY_B };
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern_->GetSelected(), 0);

    /**
     * @tc.steps: step2. IsCombinationKey && IsLetterKey.
     * @tc.expected: Selected unchanged.
     */
    keyEvent.code = KeyCode::KEY_B;
    keyEvent.pressedCodes = { KeyCode::KEY_A, KeyCode::KEY_B };
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern_->GetSelected(), 0);

    /**
     * @tc.steps: step3. !IsCombinationKey && IsLetterKey.
     * @tc.expected: Selected changed.
     */
    keyEvent.code = KeyCode::KEY_B;
    keyEvent.pressedCodes = {};
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern_->GetSelected(), 1);

    /**
     * @tc.steps: step4. Move to KEY_B again.
     * @tc.expected: Selected unchanged.
     */
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern_->GetSelected(), 1);

    /**
     * @tc.steps: step5. Move to front Index.
     * @tc.expected: Selected changed.
     */
    keyEvent.code = KeyCode::KEY_A;
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern_->GetSelected(), 0);

    /**
     * @tc.steps: step6. Move to back Index.
     * @tc.expected: Selected changed.
     */
    keyEvent.code = KeyCode::KEY_C;
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern_->GetSelected(), 2);

    /**
     * @tc.steps: step7. !IsCombinationKey && IsNumberKey.
     * @tc.expected: Selected unchanged.
     */
    keyEvent.code = KeyCode::KEY_5;
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern_->GetSelected(), 2);
}

/**
 * @tc.name: IndexerHover001
 * @tc.desc: Test Hover
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerHover001, TestSize.Level1)
{
    IndexerModelNG IndexerModelNG;
    IndexerModelNG.Create(CREATE_ARRAY, 0);
    IndexerModelNG.SetUsingPopup(true);
    GetInstance();
    RunMeasureAndLayout();

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
    GetInstance();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemSizeRender_ = 24.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = true;
    dirtySwapConfig.skipLayout = true;
    EXPECT_FALSE(pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig));

    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    EXPECT_TRUE(pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig));

    dirtySwapConfig.skipMeasure = true;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    EXPECT_TRUE(pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig));

    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = true;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    EXPECT_TRUE(pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig));
}

/**
 * @tc.name: IndexerPattern002
 * @tc.desc: Test indexer pattern InitBubbleList function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerPattern002, TestSize.Level1)
{
    IndexerModelNG IndexerModelNG;
    IndexerModelNG.Create(CREATE_ARRAY, 2);
    IndexerModelNG.SetUsingPopup(true);
    IndexerModelNG.SetAlignStyle(0);
    IndexerModelNG.SetPopupUnselectedColor(Color(0x00000000));
    IndexerModelNG.SetOnRequestPopupData(GetPopupData);
    GetInstance();
    RunMeasureAndLayout();

    pattern_->MoveIndexByStep(1);
    ASSERT_NE(pattern_->popupNode_, nullptr);
    auto listNode = pattern_->popupNode_->GetLastChild();
    auto listItemNode = AceType::DynamicCast<FrameNode>(listNode->GetFirstChild());
    auto textNode = AceType::DynamicCast<FrameNode>(listItemNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetTextColor().value(), Color(0x00000000));
}

/**
 * @tc.name: IndexerPattern003
 * @tc.desc: Test indexer pattern SetPositionOfPopupNode function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerPattern003, TestSize.Level1)
{
    IndexerModelNG IndexerModelNG1;
    IndexerModelNG1.Create(CREATE_ARRAY, 2);
    IndexerModelNG1.SetUsingPopup(true);
    IndexerModelNG1.SetPopupHorizontalSpace(Dimension(50));
    IndexerModelNG1.SetOnRequestPopupData(GetPopupData);
    GetInstance();
    RunMeasureAndLayout();

    pattern_->MoveIndexByStep(1);

    ASSERT_NE(pattern_->popupNode_, nullptr);
    auto renderContext = pattern_->popupNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto rightValue = renderContext->GetPosition().value();

    IndexerModelNG IndexerModelNG2;
    IndexerModelNG2.Create(CREATE_ARRAY, 2);
    IndexerModelNG2.SetUsingPopup(true);
    IndexerModelNG2.SetAlignStyle(0);
    IndexerModelNG2.SetPopupHorizontalSpace(Dimension(50));
    IndexerModelNG2.SetOnRequestPopupData(GetPopupData);
    GetInstance();
    RunMeasureAndLayout();

    pattern_->MoveIndexByStep(1);

    ASSERT_NE(pattern_->popupNode_, nullptr);
    auto renderContext2 = pattern_->popupNode_->GetRenderContext();
    ASSERT_NE(renderContext2, nullptr);
    auto leftValue = renderContext2->GetPosition().value();
    EXPECT_NE(rightValue, leftValue);
}

/**
 * @tc.name: IndexerPattern004
 * @tc.desc: Test indexer pattern ChangeListItemsSelectedStyle function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerPattern004, TestSize.Level1)
{
    IndexerModelNG IndexerModelNG;
    IndexerModelNG.Create(CREATE_ARRAY, 2);
    IndexerModelNG.SetUsingPopup(true);
    IndexerModelNG.SetPopupSelectedColor(Color(0x00000000));
    IndexerModelNG.SetPopupUnselectedColor(Color(0x00000000));
    IndexerModelNG.SetPopupItemBackground(Color(0x00000000));
    IndexerModelNG.SetOnRequestPopupData(GetPopupData);
    GetInstance();
    RunMeasureAndLayout();

    pattern_->MoveIndexByStep(1);
    pattern_->OnListItemClick(0);

    ASSERT_NE(pattern_->popupNode_, nullptr);
    auto listNode = pattern_->popupNode_->GetLastChild();
    auto listItemNode = AceType::DynamicCast<FrameNode>(listNode->GetFirstChild());
    auto textNode = AceType::DynamicCast<FrameNode>(listItemNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetTextColor().value(), Color(0x00000000));
}

/**
 * @tc.name: IndexerUpdateBubble001
 * @tc.desc: Test UpdateBubbleSize function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerUpdateBubble001, TestSize.Level1)
{
    IndexerModelNG IndexerModelNG;
    IndexerModelNG.Create(CREATE_ARRAY, 0);
    IndexerModelNG.SetUsingPopup(true);
    IndexerModelNG.SetOnRequestPopupData(GetPopupData);
    GetInstance();
    RunMeasureAndLayout();

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
    auto columnCalcSize = CalcSize(CalcLength(bubbleSize), CalcLength(bubbleSize * 3));
    EXPECT_EQ(columnLayoutProperty->calcLayoutConstraint_->selfIdealSize, columnCalcSize);
}

/**
 * @tc.name: IndexerUpdateBubble002
 * @tc.desc: Test UpdateBubbleSize function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerUpdateBubble002, TestSize.Level1)
{
    IndexerModelNG IndexerModelNG;
    IndexerModelNG.Create(CREATE_ARRAY, 0);
    IndexerModelNG.SetUsingPopup(true);
    IndexerModelNG.SetOnRequestPopupData(GetPopupData);
    GetInstance();
    RunMeasureAndLayout();

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
    auto columnCalcSize = CalcSize(CalcLength(bubbleSize), CalcLength(bubbleSize * 3));
    EXPECT_EQ(columnLayoutProperty->calcLayoutConstraint_->selfIdealSize, columnCalcSize);
}

/**
 * @tc.name: IndexerUpdateBubble003
 * @tc.desc: Test UpdateBubbleSize function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerUpdateBubble003, TestSize.Level1)
{
    IndexerModelNG IndexerModelNG;
    IndexerModelNG.Create(CREATE_ARRAY, 0);
    IndexerModelNG.SetUsingPopup(true);
    IndexerModelNG.SetOnRequestPopupData(GetMorePopupData); // GetMorePopupData.
    GetInstance();
    RunMeasureAndLayout();

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
    auto columnCalcSize = CalcSize(CalcLength(bubbleSize), CalcLength(bubbleSize * 6));
    EXPECT_EQ(columnLayoutProperty->calcLayoutConstraint_->selfIdealSize, columnCalcSize);
}

/**
 * @tc.name: IndexerPopupTouchDown001
 * @tc.desc: Test OnPopupTouchDown.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerPopupTouchDown001, TestSize.Level1)
{
    IndexerModelNG IndexerModelNG;
    IndexerModelNG.Create(CREATE_ARRAY, 0);
    IndexerModelNG.SetUsingPopup(true); // NeedShowPopupView is true.
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. NeedShowPopupView is true.
     * @tc.expected: verify VisibleType.
     */
    pattern_->MoveIndexByStep(1);
    TouchEventInfo touchEventInfo("onTouchDown");
    pattern_->OnPopupTouchDown(touchEventInfo);
    ASSERT_NE(pattern_->popupNode_, nullptr);
    auto columnLayoutProperty = pattern_->popupNode_->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_EQ(columnLayoutProperty->GetVisibility(), VisibleType::GONE);
}

/**
 * @tc.name: IndexerCallback001
 * @tc.desc: Test Callback SetOnPopupSelected.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerCallback001, TestSize.Level1)
{
    IndexerModelNG IndexerModelNG;
    IndexerModelNG.Create(CREATE_ARRAY, 2);
    IndexerModelNG.SetUsingPopup(true);
    IndexerModelNG.SetOnRequestPopupData(GetPopupData);
    bool isOnPopupSelectedCalled = false;
    OnPopupSelectedEvent event = [&isOnPopupSelectedCalled](int32_t) { isOnPopupSelectedCalled = true; };
    IndexerModelNG.SetOnPopupSelected(std::move(event));
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Trigger OnPopupSelected callback.
     * @tc.expected: OnPopupSelected is called.
     */
    pattern_->MoveIndexByStep(1);
    pattern_->OnListItemClick(0);
    EXPECT_TRUE(isOnPopupSelectedCalled);
}

/**
 * @tc.name: IndexerCallback002
 * @tc.desc: Test Callback SetOnSelected.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerCallback002, TestSize.Level1)
{
    IndexerModelNG IndexerModelNG;
    IndexerModelNG.Create(CREATE_ARRAY, 0);
    bool isOnSelectedCalled = false;
    OnSelectedEvent event = [&isOnSelectedCalled](int32_t) { isOnSelectedCalled = true; };
    IndexerModelNG.SetOnSelected(std::move(event));
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Trigger OnSelected callback.
     * @tc.expected: OnSelected is called.
     */
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::UP);
    touchLocationInfo.SetLocalLocation(Offset(0.f, 20.f));
    TouchEventInfo touchEventInfo("onTouchUp");
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    pattern_->OnTouchUp(touchEventInfo);
    EXPECT_TRUE(isOnSelectedCalled);
}

/**
 * @tc.name: IndexerModelNGTest001
 * @tc.desc: Test all the properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerModelNGTest001, TestSize.Level1)
{
    IndexerModelNG IndexerModelNG;
    IndexerModelNG.Create(CREATE_ARRAY, 0);
    IndexerModelNG.SetColor(Color(0x00000000));
    IndexerModelNG.SetSelectedColor(Color(0x00000000));
    IndexerModelNG.SetPopupColor(Color(0x00000000));
    IndexerModelNG.SetSelectedBackgroundColor(Color(0x00000000));
    IndexerModelNG.SetPopupBackground(Color(0x00000000));
    IndexerModelNG.SetUsingPopup(true);
    IndexerModelNG.SetItemSize(Dimension(24));
    IndexerModelNG.SetAlignStyle(0);
    IndexerModelNG.SetSelected(0);
    IndexerModelNG.SetPopupPositionX(Dimension(-96.f, DimensionUnit::VP));
    IndexerModelNG.SetPopupPositionY(Dimension(48.f, DimensionUnit::VP));
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Get properties.
     * @tc.expected: Properties are correct.
     */
    EXPECT_EQ(layoutProperty_->GetArrayValueValue(), CREATE_ARRAY);
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);
    EXPECT_EQ(layoutProperty_->GetColorValue(), Color(0x00000000));
    EXPECT_EQ(layoutProperty_->GetSelectedColorValue(), Color(0x00000000));
    EXPECT_EQ(layoutProperty_->GetPopupColorValue(), Color(0x00000000));
    EXPECT_EQ(paintProperty_->GetSelectedBackgroundColorValue(), Color(0x00000000));
    EXPECT_EQ(paintProperty_->GetPopupBackgroundValue(), Color(0x00000000));
    EXPECT_EQ(layoutProperty_->GetUsingPopupValue(), true);
    EXPECT_EQ(layoutProperty_->GetItemSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetAlignStyleValue(), AlignStyle::LEFT);
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);
    EXPECT_EQ(layoutProperty_->GetPopupPositionXValue(), Dimension(-96.f, DimensionUnit::VP));
    EXPECT_EQ(layoutProperty_->GetPopupPositionYValue(), Dimension(48.f, DimensionUnit::VP));
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: IndexerModelNGTest002
 * @tc.desc: Test special value properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerModelNGTest002, TestSize.Level1)
{
    IndexerModelNG IndexerModelNG;
    IndexerModelNG.Create(CREATE_ARRAY, 0);
    IndexerModelNG.SetSelected(-1);
    IndexerModelNG.SetItemSize(Dimension(-1));
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Get properties.
     * @tc.expected: Properties are correct.
     */
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);
    EXPECT_EQ(layoutProperty_->GetItemSizeValue(), Dimension(INDEXER_ITEM_SIZE, DimensionUnit::VP));
}

/**
 * @tc.name: IndexerModelNGTest003
 * @tc.desc: Test newly added properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerModelNGTest003, TestSize.Level1)
{
    IndexerModelNG IndexerModelNG;
    IndexerModelNG.Create(CREATE_ARRAY, 0);
    IndexerModelNG.SetPopupSelectedColor(Color(0x00000000));
    IndexerModelNG.SetPopupUnselectedColor(Color(0x00000000));
    IndexerModelNG.SetPopupItemBackground(Color(0x00000000));
    IndexerModelNG.SetPopupHorizontalSpace(Dimension(50));
    IndexerModelNG.SetFontSize(Dimension(24));
    IndexerModelNG.SetFontWeight(FontWeight::MEDIUM);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Get properties.
     * @tc.expected: Properties are correct.
     */
    EXPECT_EQ(paintProperty_->GetPopupSelectedColorValue(), Color(0x00000000));
    EXPECT_EQ(paintProperty_->GetPopupUnselectedColorValue(), Color(0x00000000));
    EXPECT_EQ(paintProperty_->GetPopupItemBackgroundValue(), Color(0x00000000));
    EXPECT_EQ(paintProperty_->GetPopupHorizontalSpaceValue(), Dimension(50));
    EXPECT_EQ(layoutProperty_->GetFontSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetFontWeightValue(), FontWeight::MEDIUM);
}

/**
 * @tc.name: IndexerModelNGTest004
 * @tc.desc: Test newly added properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerModelNGTest004, TestSize.Level1)
{
    IndexerModelNG IndexerModelNG;
    IndexerModelNG.Create(CREATE_ARRAY, 0);
    IndexerModelNG.SetPopupSelectedColor(std::nullopt);
    IndexerModelNG.SetPopupUnselectedColor(std::nullopt);
    IndexerModelNG.SetPopupItemBackground(std::nullopt);
    IndexerModelNG.SetPopupHorizontalSpace(Dimension(-1));
    IndexerModelNG.SetFontSize(Dimension());
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Get properties.
     * @tc.expected: Properties are correct.
     */
    EXPECT_FALSE(paintProperty_->GetPopupSelectedColor().has_value());
    EXPECT_FALSE(paintProperty_->GetPopupUnselectedColor().has_value());
    EXPECT_FALSE(paintProperty_->GetPopupItemBackground().has_value());
    EXPECT_FALSE(paintProperty_->GetPopupHorizontalSpace().has_value());
    EXPECT_FALSE(layoutProperty_->GetFontSize().has_value());
}

/**
 * @tc.name: IndexerModelNGTest005
 * @tc.desc: Test Create func with special arg
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerModelNGTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create with normal arg.
     * @tc.expected: LayoutProperty is correct.
     */
    IndexerModelNG IndexerModelNG1;
    IndexerModelNG1.Create(CREATE_ARRAY, 5);
    GetInstance();
    EXPECT_EQ(layoutProperty_->GetArrayValueValue(), CREATE_ARRAY);
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 5);

    /**
     * @tc.steps: step2. Create with special arg.
     * @tc.expected: LayoutProperty is correct.
     */
    std::vector<std::string> arrayValue;
    IndexerModelNG IndexerModelNG2;
    IndexerModelNG2.Create(arrayValue, -1);
    GetInstance();
    EXPECT_TRUE(layoutProperty_->GetArrayValueValue().empty());
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);

    /**
     * @tc.steps: step3. Create with special arg.
     * @tc.expected: LayoutProperty is correct.
     */
    IndexerModelNG IndexerModelNG3;
    IndexerModelNG3.Create(arrayValue, CREATE_ARRAY.size() + 1);
    GetInstance();
    EXPECT_TRUE(layoutProperty_->GetArrayValueValue().empty());
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);
}

/**
 * @tc.name: IndexerAccessibilityTest001
 * @tc.desc: Test accessibility func.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerAccessibilityTest001, TestSize.Level1)
{
    IndexerModelNG IndexerModelNG;
    IndexerModelNG.Create(CREATE_ARRAY, 0);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Test GetEndIndex, GetText func.
     * @tc.expected: The return_value is correct.
     */
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), CREATE_ARRAY.size() - 1);
    EXPECT_EQ(accessibilityProperty_->GetText(), CREATE_ARRAY.at(0));
}

/**
 * @tc.name: IndexerAlgorithmTest001
 * @tc.desc: Test Algorithm func.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerAlgorithmTest001, TestSize.Level1)
{
    IndexerModelNG IndexerModelNG;
    IndexerModelNG.Create(CREATE_ARRAY, 0);
    GetInstance();

    /**
     * @tc.steps: step1. selfIdealSize is (0, 0).
     * @tc.expected: The layoutAlgorithm value is correct.
     */
    RefPtr<LayoutWrapper> layoutWrapper = frameNode_->CreateLayoutWrapper(false, false);
    layoutWrapper->SetActive();
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.parentIdealSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.percentReference = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.selfIdealSize = { 0, 0 };
    LayoutConstraint.maxSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    layoutWrapper->Measure(LayoutConstraint);
    layoutWrapper->Layout();
    layoutWrapper->MountToHostOnMainThread();

    auto layoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(layoutWrapper->GetLayoutAlgorithm());
    EXPECT_EQ(layoutAlgorithm->itemWidth_, 0.f);
    EXPECT_EQ(layoutAlgorithm->itemSizeRender_, 0.f);
}

/**
 * @tc.name: IndexerPatternCoverage001
 * @tc.desc: For Coverage Rate, branches that are not normally covered.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerPatternCoverage001, TestSize.Level1)
{
    IndexerModelNG IndexerModelNG;
    IndexerModelNG.Create(CREATE_ARRAY, 0);
    IndexerModelNG.SetUsingPopup(true);
    GetInstance();
    RunMeasureAndLayout();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step1. Supplement MoveIndexByOffset branch,
     * the itemCount_ would not be 0 when itemSizeRender_ was not 0.
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
    pattern_->OnSelect(true);

    /**
     * @tc.steps: step5. Supplement OnSelect branch.
     * has no condition that selected_ less than 0 when OnTouchUp.
     */
    pattern_->selected_ = -1;
    pattern_->OnSelect(true);

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
    IndexerModelNG IndexerModelNG;
    IndexerModelNG.Create(CREATE_ARRAY, 0);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Supplement OnPopupTouchDown branch,
     * has no condition that NeedShowPopupView is false when showPopup.
     */
    TouchEventInfo touchEventInfo("onTouchDown");
    pattern_->OnPopupTouchDown(touchEventInfo);

    EXPECT_TRUE(true);
}

/**
 * @tc.name: IndexerAlgorithmCoverage001
 * @tc.desc: For Coverage Rate, branches that are not normally covered.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerAlgorithmCoverage001, TestSize.Level1)
{
    IndexerModelNG IndexerModelNG;
    IndexerModelNG.Create(CREATE_ARRAY, 0);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Supplement Measure branch,
     * has no condition that itemSize_ is 0.
     */
    layoutProperty_->UpdateItemSize(Dimension(0));
    RefPtr<LayoutWrapper> layoutWrapper = frameNode_->CreateLayoutWrapper(false, false);
    layoutWrapper->SetActive();
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.parentIdealSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.percentReference = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.maxSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    layoutWrapper->Measure(LayoutConstraint);
    layoutWrapper->Layout();
    layoutWrapper->MountToHostOnMainThread();

    auto layoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(layoutWrapper->GetLayoutAlgorithm());
    EXPECT_EQ(layoutAlgorithm->itemSize_, 0.f);

    EXPECT_TRUE(true);
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: Indexer Accessibility PerformAction test Select and ClearSelection.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, PerformActionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create indexer and initialize related properties.
     */
    IndexerModelNG IndexerModelNG;
    IndexerModelNG.Create(CREATE_ARRAY, 0);

    /**
     * @tc.steps: step2. Get indexer frameNode and child pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto indexerPattern = frameNode->GetPattern<IndexerPattern>();
    ASSERT_NE(indexerPattern, nullptr);
    auto firstTextNode = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    ASSERT_NE(firstTextNode, nullptr);
    auto lastTextNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild());
    ASSERT_NE(lastTextNode, nullptr);
    indexerPattern->SetAccessibilityAction();

    /**
     * @tc.steps: step3. Get text accessibilityProperty to call callback function.
     * @tc.expected: Related function is called.
     */
    auto firstTextaccessibilityProperty = firstTextNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(firstTextaccessibilityProperty, nullptr);
    auto lastTextaccessibilityProperty = lastTextNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(lastTextaccessibilityProperty, nullptr);

    /**
     * @tc.steps: step4. The first child call the callback function in textAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    EXPECT_TRUE(firstTextaccessibilityProperty->ActActionSelect());
    EXPECT_TRUE(firstTextaccessibilityProperty->ActActionClearSelection());

    /**
     * @tc.steps: step5. The last child call the callback function in textAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    EXPECT_TRUE(lastTextaccessibilityProperty->ActActionSelect());
    EXPECT_TRUE(lastTextaccessibilityProperty->ActActionClearSelection());

    /**
     * @tc.steps: step6. The last child is not selected, call the ClearSelection callback function in
     *                   textAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    indexerPattern->selected_ = 0;
    EXPECT_TRUE(lastTextaccessibilityProperty->ActActionClearSelection());
}
} // namespace OHOS::Ace::NG
