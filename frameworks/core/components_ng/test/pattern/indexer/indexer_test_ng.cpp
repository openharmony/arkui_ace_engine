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
#include "core/components_ng/pattern/indexer/indexer_paint_property.h"
#include "core/components_ng/pattern/indexer/indexer_pattern.h"
#include "core/components_ng/pattern/indexer/indexer_theme.h"
#include "core/components_ng/pattern/indexer/indexer_view.h"
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
const std::vector<std::string> CREATE_ARRAY = {
    "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
    "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
std::vector<std::string> GetPopupData(int32_t)
{
    return { "白", "别" };
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
    RefPtr<FrameNode> GetChildFrameNode(int32_t index);

    RefPtr<FrameNode> frameNode_;
    RefPtr<IndexerPattern> pattern_;
    RefPtr<IndexerEventHub> eventHub_;
    RefPtr<IndexerLayoutProperty> layoutProperty_;
    RefPtr<IndexerPaintProperty> paintProperty_;
    RefPtr<IndexerAccessibilityProperty> accessibility_;
};

void IndexerTestNg::SetUpTestSuite()
{
    MockPipelineBase::SetUp();
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
    accessibility_ = nullptr;
}

void IndexerTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<IndexerPattern>();
    eventHub_ = frameNode_->GetEventHub<IndexerEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<IndexerLayoutProperty>();
    paintProperty_ = frameNode_->GetPaintProperty<IndexerPaintProperty>();
    accessibility_ = frameNode_->GetAccessibilityProperty<IndexerAccessibilityProperty>();
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

RefPtr<FrameNode> IndexerTestNg::GetChildFrameNode(int32_t index)
{
    auto item = frameNode_->GetChildAtIndex(index);
    return AceType::DynamicCast<FrameNode>(item);
}

/**
 * @tc.name: IndexerMoveIndex001
 * @tc.desc: Test panEvent_ MoveIndexByStep func.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerMoveIndex001, TestSize.Level1)
{
    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY, 0);
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
    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY, 0);
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
    IndexerView indexerView;
    indexerView.Create(arrayValue, 0); // empty array
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
 * @tc.desc: Test touchListener_ func.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerTouch001, TestSize.Level1)
{
    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY, 0);
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
     * @tc.steps: step2. OnTouchUp.
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
 * @tc.desc: Test touchListener_ func.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerTouch002, TestSize.Level1)
{
    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY, 0);
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
 * @tc.name: IndexerTouch003
 * @tc.desc: Test touchListener_ func.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerTouch003, TestSize.Level1)
{
    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY, 0);
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
     * @tc.steps: step2. OnTouchUp.
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
 * @tc.name: IndexerKeyEvent001
 * @tc.desc: Test OnKeyEvent func.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerKeyEvent001, TestSize.Level1)
{
    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY, 0);
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

    /**
     * @tc.steps: step6. IsCombinationKey && KEY_UNKNOWN.
     * @tc.expected: Selected unchanged.
     */
    keyEvent.code = KeyCode::KEY_UNKNOWN;
    keyEvent.pressedCodes = { KeyCode::KEY_A, KeyCode::KEY_B };
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern_->GetSelected(), pattern_->itemCount_ - 1);

    /**
     * @tc.steps: step7. IsCombinationKey && IsLetterKey.
     * @tc.expected: Selected unchanged.
     */
    keyEvent.code = KeyCode::KEY_B;
    keyEvent.pressedCodes = { KeyCode::KEY_A, KeyCode::KEY_B };
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern_->GetSelected(), pattern_->itemCount_ - 1);

    /**
     * @tc.steps: step8. !IsCombinationKey && IsLetterKey.
     * @tc.expected: Selected change to 1.
     */
    keyEvent.code = KeyCode::KEY_B;
    keyEvent.pressedCodes = {};
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern_->GetSelected(), 1);

    /**
     * @tc.steps: step9. !IsCombinationKey && IsNumberKey.
     * @tc.expected: Selected unchanged.
     */
    keyEvent.code = KeyCode::KEY_5;
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern_->GetSelected(), 1);
}

/**
 * @tc.name: IndexerHover001
 * @tc.desc: Test Hover
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerHover001, TestSize.Level1)
{
    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY, 0);
    GetInstance();
    RunMeasureAndLayout();

    pattern_->OnChildHover(1, true);
    EXPECT_EQ(pattern_->childHoverIndex_, 1);
    pattern_->OnChildHover(1, false);
    EXPECT_EQ(pattern_->childHoverIndex_, -1);
    pattern_->OnChildHover(CREATE_ARRAY.size(), true);
    EXPECT_EQ(pattern_->childHoverIndex_, CREATE_ARRAY.size());

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
    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY, 0);
    GetInstance();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(
        frameNode_, geometryNode, layoutProperty_);
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
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    PipelineContext::GetCurrentContext()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<IndexerTheme>()));

    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY, 2);
    indexerView.SetUsingPopup(true);
    indexerView.SetAlignStyle(AlignStyle::LEFT);
    indexerView.SetPopupUnselectedColor(Color(0x00000000));
    indexerView.SetOnRequestPopupData(GetPopupData);
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
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    PipelineContext::GetCurrentContext()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<IndexerTheme>()));

    IndexerView indexerView1;
    indexerView1.Create(CREATE_ARRAY, 2);
    indexerView1.SetUsingPopup(true);
    indexerView1.SetPopupHorizontalSpace(Dimension(50));
    indexerView1.SetOnRequestPopupData(GetPopupData);
    GetInstance();
    RunMeasureAndLayout();

    pattern_->MoveIndexByStep(1);

    ASSERT_NE(pattern_->popupNode_, nullptr);
    auto renderContext = pattern_->popupNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto rightValue = renderContext->GetPosition().value();

    IndexerView indexerView2;
    indexerView2.Create(CREATE_ARRAY, 2);
    indexerView2.SetUsingPopup(true);
    indexerView2.SetAlignStyle(AlignStyle::LEFT);
    indexerView2.SetPopupHorizontalSpace(Dimension(50));
    indexerView2.SetOnRequestPopupData(GetPopupData);
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
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    PipelineContext::GetCurrentContext()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<IndexerTheme>()));

    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY, 2);
    indexerView.SetUsingPopup(true);
    indexerView.SetPopupSelectedColor(Color(0x00000000));
    indexerView.SetPopupUnselectedColor(Color(0x00000000));
    indexerView.SetPopupItemBackground(Color(0x00000000));
    indexerView.SetOnRequestPopupData(GetPopupData);
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
 * @tc.name: IndexerPattern005
 * @tc.desc: Test OnPopupTouchDown.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerPattern005, TestSize.Level1)
{
    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY, 0);
    GetInstance();
    RunMeasureAndLayout();

    pattern_->MoveIndexByStep(1);
    TouchEventInfo touchEventInfo("onTouchDown");
    pattern_->OnPopupTouchDown(touchEventInfo);
}

/**
 * @tc.name: IndexerCallback001
 * @tc.desc: Test Callback SetOnPopupSelected.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerCallback001, TestSize.Level1)
{
    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY, 2);
    indexerView.SetUsingPopup(true);
    indexerView.SetOnRequestPopupData(GetPopupData);
    bool isOnPopupSelectedCalled = false;
    OnPopupSelectedEvent event = [&isOnPopupSelectedCalled](int32_t) { isOnPopupSelectedCalled = true; };
    indexerView.SetOnPopupSelected(std::move(event));
    GetInstance();
    RunMeasureAndLayout();

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
    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY, 0);
    bool isOnSelectedCalled = false;
    OnSelectedEvent event = [&isOnSelectedCalled](int32_t) { isOnSelectedCalled = true; };
    indexerView.SetOnSelected(std::move(event));
    GetInstance();
    RunMeasureAndLayout();

    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::UP);
    touchLocationInfo.SetLocalLocation(Offset(0.f, 20.f));
    TouchEventInfo touchEventInfo("onTouchUp");
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    pattern_->OnTouchUp(touchEventInfo);
    EXPECT_TRUE(isOnSelectedCalled);
}

/**
 * @tc.name: IndexerViewTest001
 * @tc.desc: Test all the properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerViewTest001, TestSize.Level1)
{
    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY, 0);
    indexerView.SetColor(Color(0x00000000));
    indexerView.SetSelectedColor(Color(0x00000000));
    indexerView.SetPopupColor(Color(0x00000000));
    indexerView.SetSelectedBackgroundColor(Color(0x00000000));
    indexerView.SetPopupBackground(Color(0x00000000));
    indexerView.SetUsingPopup(true);
    indexerView.SetSelectedFont(TextStyle());
    indexerView.SetPopupFont(TextStyle());
    indexerView.SetFont(TextStyle());
    indexerView.SetItemSize(Dimension(24));
    indexerView.SetAlignStyle(AlignStyle::LEFT);
    indexerView.SetSelected(0);
    indexerView.SetPopupPositionX(Dimension(-96.f, DimensionUnit::VP));
    indexerView.SetPopupPositionY(Dimension(48.f, DimensionUnit::VP));
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_EQ(layoutProperty_->GetArrayValueValue(), CREATE_ARRAY);
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);
    EXPECT_EQ(layoutProperty_->GetColorValue(), Color(0x00000000));
    EXPECT_EQ(layoutProperty_->GetSelectedColorValue(), Color(0x00000000));
    EXPECT_EQ(layoutProperty_->GetPopupColorValue(), Color(0x00000000));
    EXPECT_EQ(paintProperty_->GetSelectedBackgroundColorValue(), Color(0x00000000));
    EXPECT_EQ(paintProperty_->GetPopupBackgroundValue(), Color(0x00000000));
    EXPECT_EQ(layoutProperty_->GetUsingPopupValue(), true);
    EXPECT_EQ(layoutProperty_->GetSelectedFontValue(), TextStyle());
    EXPECT_EQ(layoutProperty_->GetPopupFontValue(), TextStyle());
    EXPECT_EQ(layoutProperty_->GetFontValue(), TextStyle());
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
 * @tc.name: IndexerViewTest002
 * @tc.desc: Test special value properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerViewTest002, TestSize.Level1)
{
    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY, 0);
    indexerView.SetSelected(-1);
    indexerView.SetItemSize(Dimension(-1));
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);
    EXPECT_EQ(layoutProperty_->GetItemSizeValue(), Dimension(INDEXER_ITEM_SIZE, DimensionUnit::VP));
}

/**
 * @tc.name: IndexerViewTest003
 * @tc.desc: Test newly added properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerViewTest003, TestSize.Level1)
{
    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY, 0);
    indexerView.SetPopupSelectedColor(Color(0x00000000));
    indexerView.SetPopupUnselectedColor(Color(0x00000000));
    indexerView.SetPopupItemBackground(Color(0x00000000));
    indexerView.SetPopupHorizontalSpace(Dimension(50));
    indexerView.SetFontSize(Dimension(24));
    indexerView.SetFontWeight(FontWeight::MEDIUM);
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_EQ(paintProperty_->GetPopupSelectedColorValue(), Color(0x00000000));
    EXPECT_EQ(paintProperty_->GetPopupUnselectedColorValue(), Color(0x00000000));
    EXPECT_EQ(paintProperty_->GetPopupItemBackgroundValue(), Color(0x00000000));
    EXPECT_EQ(paintProperty_->GetPopupHorizontalSpaceValue(), Dimension(50));
    EXPECT_EQ(layoutProperty_->GetFontSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetFontWeightValue(), FontWeight::MEDIUM);
}

/**
 * @tc.name: IndexerViewTest004
 * @tc.desc: Test newly added properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerViewTest004, TestSize.Level1)
{
    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY, 0);
    indexerView.SetPopupSelectedColor(std::nullopt);
    indexerView.SetPopupUnselectedColor(std::nullopt);
    indexerView.SetPopupItemBackground(std::nullopt);
    indexerView.SetPopupHorizontalSpace(Dimension(-1));
    indexerView.SetFontSize(Dimension());
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_FALSE(paintProperty_->GetPopupSelectedColor().has_value());
    EXPECT_FALSE(paintProperty_->GetPopupUnselectedColor().has_value());
    EXPECT_FALSE(paintProperty_->GetPopupItemBackground().has_value());
    EXPECT_FALSE(paintProperty_->GetPopupHorizontalSpace().has_value());
    EXPECT_FALSE(layoutProperty_->GetFontSize().has_value());
}

/**
 * @tc.name: IndexerViewTest005
 * @tc.desc: Test Create func with special arg
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerViewTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create with normal arg.
     * @tc.expected: LayoutProperty is correct.
     */
    IndexerView indexerView1;
    indexerView1.Create(CREATE_ARRAY, 5);
    GetInstance();
    EXPECT_EQ(layoutProperty_->GetArrayValueValue(), CREATE_ARRAY);
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 5);

    /**
     * @tc.steps: step2. Create with special arg.
     * @tc.expected: LayoutProperty is correct.
     */
    std::vector<std::string> arrayValue;
    IndexerView indexerView2;
    indexerView2.Create(arrayValue, -1);
    GetInstance();
    EXPECT_TRUE(layoutProperty_->GetArrayValueValue().empty());
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);

    /**
     * @tc.steps: step3. Create with special arg.
     * @tc.expected: LayoutProperty is correct.
     */
    IndexerView indexerView3;
    indexerView3.Create(arrayValue, CREATE_ARRAY.size() + 1);
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
    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY, 0);
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_EQ(accessibility_->GetEndIndex(), CREATE_ARRAY.size() - 1);
    EXPECT_EQ(accessibility_->GetText(), CREATE_ARRAY.at(0));
}
} // namespace OHOS::Ace::NG
