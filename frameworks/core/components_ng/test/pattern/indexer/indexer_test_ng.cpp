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
const std::vector<std::string> CREATE_ARRAY_VALUE = {
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
    LayoutConstraint.selfIdealSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
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
 * @tc.name: IndexerPattern001
 * @tc.desc: Test indexer pattern OnDirtyLayoutWrapperSwap function. include special value.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerPattern001, TestSize.Level1)
{
    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY_VALUE, 0);
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
 * @tc.desc: Test indexer pattern InitPanEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerPattern002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create indexer frameNode, get pattern_ and indexerWrapper.
     * @tc.steps: case1: no panEvent
     * @tc.expected: step1. get pattern_ success.
     */
    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY_VALUE, 0);
    GetInstance();
    RunMeasureAndLayout();
    ASSERT_NE(pattern_->panEvent_, nullptr);
    /**
     * @tc.steps: step2. carry actions.
     * @tc.steps: case1: AXIS, mainDelta is 0
     * @tc.expected: step2. get pattern_ success.
     */
    GestureEvent gestureEvent1;
    gestureEvent1.inputEventType_ = InputEventType::AXIS;
    gestureEvent1.mainDelta_ = 0;
    pattern_->panEvent_->actionStart_(gestureEvent1);
    pattern_->panEvent_->actionUpdate_(gestureEvent1);
    ASSERT_NE(pattern_->panEvent_, nullptr);

    /**
     * @tc.steps: step2. carry actions.
     * @tc.steps: case2: AXIS, mainDelta is 1
     * @tc.expected: step2. get pattern_ success.
     */
    gestureEvent1.inputEventType_ = InputEventType::AXIS;
    gestureEvent1.mainDelta_ = 1;
    pattern_->panEvent_->actionStart_(gestureEvent1);
    pattern_->panEvent_->actionUpdate_(gestureEvent1);
    ASSERT_NE(pattern_->panEvent_, nullptr);

    /**
     * @tc.steps: step2. carry actions.
     * @tc.steps: case3: AXIS, mainDelta is -1
     * @tc.expected: step2. get pattern_ success.
     */
    gestureEvent1.inputEventType_ = InputEventType::AXIS;
    gestureEvent1.mainDelta_ = -1;
    pattern_->panEvent_->actionStart_(gestureEvent1);
    pattern_->panEvent_->actionUpdate_(gestureEvent1);
    ASSERT_NE(pattern_->panEvent_, nullptr);

    /**
     * @tc.steps: step2. carry actions.
     * @tc.steps: case4: KEYBOARD
     * @tc.expected: step2. get pattern_ success.
     */
    gestureEvent1.inputEventType_ = InputEventType::KEYBOARD;
    pattern_->panEvent_->actionStart_(gestureEvent1);
    pattern_->panEvent_->actionUpdate_(gestureEvent1);
    ASSERT_NE(pattern_->panEvent_, nullptr);
}

/**
 * @tc.name: IndexerPattern003
 * @tc.desc: Test indexer pattern OnChildHover function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerPattern003, TestSize.Level1)
{
    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY_VALUE, 0);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. create indexer frameNode, get pattern_ and indexerWrapper.
     * @tc.steps: case1: isHover
     * @tc.expected: step1. get pattern_ success.
     */
    pattern_->OnChildHover(1, true);
    EXPECT_EQ(pattern_->childHoverIndex_, 1);

    /**
     * @tc.steps: step1. create indexer frameNode, get pattern_ and indexerWrapper.
     * @tc.steps: case2: !isHover
     * @tc.expected: step1. get pattern_ success.
     */
    pattern_->OnChildHover(1, false);
    EXPECT_EQ(pattern_->childHoverIndex_, -1);
}

/**
 * @tc.name: IndexerPattern004
 * @tc.desc: Test indexer pattern InitInputEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerPattern004, TestSize.Level1)
{
    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY_VALUE, 0);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. create indexer frameNode, get pattern_ and indexerWrapper.
     * @tc.steps: case1: isInputEventRegisted_ = false
     * @tc.expected: step1. get pattern_ success.
     */
    pattern_->isInputEventRegisted_ = false;
    pattern_->InitInputEvent();
    EXPECT_EQ(pattern_->isInputEventRegisted_, true);

    /**
     * @tc.steps: step1. create indexer frameNode, get pattern_ and indexerWrapper.
     * @tc.steps: case2: isInputEventRegisted_ = true
     * @tc.expected: step1. get pattern_ success.
     */
    pattern_->InitInputEvent();
    EXPECT_EQ(pattern_->isInputEventRegisted_, true);
}

/**
 * @tc.name: IndexerPattern005
 * @tc.desc: Test indexer pattern InitChildInputEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerPattern005, TestSize.Level1)
{
    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY_VALUE, 0);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. create indexer frameNode, get pattern_ and indexerWrapper.
     * @tc.steps: case1: isInputEventRegisted_ = false
     * @tc.expected: step1. get pattern_ success.
     */
    pattern_->itemCount_ = CREATE_ARRAY_VALUE.size();
    pattern_->InitChildInputEvent();
    EXPECT_EQ(pattern_->itemCount_, CREATE_ARRAY_VALUE.size());
}

/**
 * @tc.name: IndexerPattern006
 * @tc.desc: Test indexer pattern MoveIndexByOffset function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerPattern006, TestSize.Level1)
{
    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY_VALUE, 0);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. call pattern_ MoveIndexByOffset function, compare result.
     * @tc.steps: case1: itemSizeRender is 0, return
     * @tc.expected: step1. MoveIndexByOffset success and result correct.
     */
    pattern_->itemSizeRender_ = 0;
    pattern_->MoveIndexByOffset(Offset(0, 50.f));
    EXPECT_EQ(pattern_->childPressIndex_, -1);

    /**
     * @tc.steps: step1. call pattern_ MoveIndexByOffset function, compare result.
     * @tc.steps: case2: itemSizeRender is 1, itemCount is 0, return
     * @tc.expected: step1. MoveIndexByOffset success and result correct.
     */
    pattern_->itemSizeRender_ = 1;
    pattern_->itemCount_ = 0;
    pattern_->MoveIndexByOffset(Offset(0, 50.f));
    EXPECT_EQ(pattern_->childPressIndex_, -1);

    /**
     * @tc.steps: step1. call pattern_ MoveIndexByOffset function, compare result.
     * @tc.steps: case3: itemSizeRender > 0, itemCount > 0, isRepeatCalled true, next != child
     * @tc.expected: step1. MoveIndexByOffset success and result correct.
     */
    pattern_->itemSizeRender_ = 24.f;
    pattern_->itemCount_ = CREATE_ARRAY_VALUE.size();
    pattern_->MoveIndexByOffset(Offset(0, 50.f));
    int32_t expectedIndex = static_cast<int32_t>(50.f / 24.f);
    EXPECT_EQ(expectedIndex, pattern_->childPressIndex_);

    /**
     * @tc.steps: step1. call pattern_ MoveIndexByOffset function, compare result.
     * @tc.steps: case4: itemSizeRender > 0, itemCount > 0, isRepeatCalled true, next == child
     * @tc.expected: step1. MoveIndexByOffset success and result correct.
     */
    pattern_->MoveIndexByOffset(Offset(0, 0));
    EXPECT_EQ(pattern_->childPressIndex_, 0);

    /**
     * @tc.steps: step1. call pattern_ MoveIndexByOffset function, compare result.
     * @tc.steps: case5: itemSizeRender > 0, itemCount > 0, isRepeatCalled false, next == child
     * @tc.expected: step1. MoveIndexByOffset success and result correct.
     */
    pattern_->MoveIndexByOffset(Offset(0, 0));
    EXPECT_EQ(pattern_->childPressIndex_, 0);

    /**
     * @tc.steps: step1. call pattern_ MoveIndexByOffset function, compare result.
     * @tc.steps: case5: itemSizeRender > 0, itemCount > 0, isRepeatCalled false, next != child
     * @tc.expected: step1. MoveIndexByOffset success and result correct.
     */
    pattern_->MoveIndexByOffset(Offset(0, 50.f));
    EXPECT_EQ(expectedIndex, pattern_->childPressIndex_);
}

/**
 * @tc.name: IndexerPattern007
 * @tc.desc: Test indexer pattern KeyIndexByStep function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerPattern007, TestSize.Level1)
{
    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY_VALUE, 0);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. create indexer frameNode, get pattern_ and indexerWrapper.
     * @tc.expected: step1. get pattern_ success.
     */
    pattern_->selected_ = 1;

    /**
     * @tc.steps: step2. call pattern_ KeyIndexByStep function, compare result.
     * @tc.expected: step2. KeyIndexByStep success and result correct.
     */
    bool result = false;
    pattern_->itemCount_ = 0;
    result = pattern_->KeyIndexByStep(1);
    EXPECT_EQ(result, false);

    pattern_->itemCount_ = CREATE_ARRAY_VALUE.size();
    pattern_->selected_ = 1;
    result = pattern_->KeyIndexByStep(1);
    EXPECT_EQ(pattern_->selected_, 1 + 1);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: IndexerPattern008
 * @tc.desc: Test indexer pattern GetSkipChildIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerPattern008, TestSize.Level1)
{
    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY_VALUE, 0);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. call pattern_ GetSkipChildIndex function, compare result.
     * @tc.steps: case1: nextSelected < 0
     * @tc.expected: step1. GetSkipChildIndex success and result correct.
     */
    pattern_->selected_ = 0;
    auto result = pattern_->GetSkipChildIndex(-1);
    EXPECT_EQ(result, -1);

    /**
     * @tc.steps: step1. call pattern_ GetSkipChildIndex function, compare result.
     * @tc.steps: case1: nextSelected > 0, nextSelected < itemCount
     * @tc.expected: step1. GetSkipChildIndex success and result correct.
     */
    pattern_->selected_ = 0;
    pattern_->itemCount_ = CREATE_ARRAY_VALUE.size();
    result = pattern_->GetSkipChildIndex(1);
    EXPECT_EQ(result, 1);

    /**
     * @tc.steps: step1. call pattern_ GetSkipChildIndex function, compare result.
     * @tc.steps: case1: nextSelected > itemCount
     * @tc.expected: step1. GetSkipChildIndex success and result correct.
     */
    pattern_->selected_ = 0;
    pattern_->itemCount_ = CREATE_ARRAY_VALUE.size();
    result = pattern_->GetSkipChildIndex(pattern_->itemCount_ + 1);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: IndexerPattern009
 * @tc.desc: Test indexer pattern MoveIndexByStep function. include special case.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerPattern009, TestSize.Level1)
{
    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY_VALUE, 0);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. create indexer frameNode, get pattern_ and indexerWrapper.
     * @tc.expected: step1. get pattern_ success.
     */
    pattern_->selected_ = 1;

    /**
     * @tc.steps: step2. call pattern_ MoveIndexByStep function, compare result.
     * @tc.expected: step2. MoveIndexByStep success and result correct.
     */
    bool result = false;
    pattern_->itemCount_ = 0;
    result = pattern_->MoveIndexByStep(1);
    EXPECT_EQ(result, false);

    pattern_->itemCount_ = CREATE_ARRAY_VALUE.size();
    pattern_->selected_ = 1;
    result = pattern_->MoveIndexByStep(1);
    EXPECT_EQ(pattern_->selected_, 1 + 1);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: IndexerPattern010
 * @tc.desc: Test indexer pattern MoveIndexBySearch function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerPattern010, TestSize.Level1)
{
    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY_VALUE, 0);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. create indexer frameNode, get pattern_ and indexerWrapper.
     * @tc.expected: step1. get pattern_ success.
     */
    pattern_->selected_ = 1;
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step2. call pattern_ MoveIndexBySearch function, compare result.
     * @tc.steps: case1: search Move_index_search
     * @tc.expected: step2. MoveIndexBySearch success and result correct.
     */
    pattern_->MoveIndexBySearch(CREATE_ARRAY_VALUE[1]);
    EXPECT_EQ(pattern_->selected_, 1);

    /**
     * @tc.steps: step2. call pattern_ MoveIndexBySearch function, compare result.
     * @tc.steps: case2: search Move_index_search + 1
     * @tc.expected: step2. MoveIndexBySearch success and result correct.
     */
    pattern_->MoveIndexBySearch(CREATE_ARRAY_VALUE[2]);
    EXPECT_EQ(pattern_->selected_, 1 + 1);

    /**
     * @tc.steps: step2. call pattern_ MoveIndexBySearch function, compare result.
     * @tc.steps: case2: search Move_index_search - 1
     * @tc.expected: step2. MoveIndexBySearch success and result correct.
     */
    pattern_->MoveIndexBySearch(CREATE_ARRAY_VALUE[0]);
    EXPECT_EQ(pattern_->selected_, 0);
}

/**
 * @tc.name: IndexerPattern011
 * @tc.desc: Test indexer pattern InitOnKeyEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerPattern011, TestSize.Level1)
{
    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY_VALUE, 0);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. call pattern_ InitOnKeyEvent function, compare result.
     * @tc.expected: step1. InitOnKeyEvent success and result correct.
     */
    RefPtr<FocusHub> focusHub = frameNode_->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    pattern_->InitOnKeyEvent();
    ASSERT_NE(focusHub->onKeyEventInternal_, nullptr);
}

/**
 * @tc.name: IndexerPattern012
 * @tc.desc: Test indexer pattern OnKeyEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerPattern012, TestSize.Level1)
{
    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY_VALUE, 0);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. create indexer frameNode, get pattern_ and indexerWrapper.
     * @tc.expected: step1. get pattern_ success.
     */
    pattern_->selected_ = 1;

    /**
     * @tc.steps: step2. call pattern_ OnKeyEvent function, compare result.
     * @tc.expected: step2. OnKeyEvent success and result correct.
     */
    KeyEvent keyEvent = KeyEvent(KeyCode::KEY_DPAD_UP, KeyAction::DOWN);
    EXPECT_EQ(pattern_->OnKeyEvent(keyEvent), true);

    keyEvent = KeyEvent(KeyCode::KEY_DPAD_DOWN, KeyAction::DOWN);
    EXPECT_EQ(pattern_->OnKeyEvent(keyEvent), true);

    keyEvent = KeyEvent(KeyCode::KEY_UNKNOWN, KeyAction::DOWN);
    EXPECT_EQ(pattern_->OnKeyEvent(keyEvent), false);

    keyEvent = KeyEvent(KeyCode::KEY_UNKNOWN, KeyAction::UNKNOWN);
    EXPECT_EQ(pattern_->OnKeyEvent(keyEvent), false);

    keyEvent = KeyEvent(KeyCode::KEY_1, KeyAction::DOWN);
    EXPECT_EQ(pattern_->OnKeyEvent(keyEvent), false);

    keyEvent = KeyEvent(KeyCode::KEY_B, KeyAction::DOWN);
    EXPECT_EQ(pattern_->OnKeyEvent(keyEvent), false);

    keyEvent = KeyEvent(KeyCode::KEY_B, KeyAction::DOWN);
    keyEvent.pressedCodes = { KeyCode::KEY_A, KeyCode::KEY_B };
    EXPECT_EQ(pattern_->OnKeyEvent(keyEvent), false);

    keyEvent = KeyEvent(KeyCode::KEY_UNKNOWN, KeyAction::DOWN);
    keyEvent.pressedCodes = { KeyCode::KEY_A, KeyCode::KEY_B };
    EXPECT_EQ(pattern_->OnKeyEvent(keyEvent), false);
}

/**
 * @tc.name: IndexerPattern013
 * @tc.desc: Test indexer pattern ApplyIndexChange function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerPattern013, TestSize.Level1)
{
    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY_VALUE, 0);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. call pattern_ ApplyIndexChange function, compare result.
     * @tc.steps: case1: have onSelected, onRequestPopupData, onPopupSelected, selected < 0
     * @tc.expected: step1. OnKeyEvent success and result correct.
     */
    eventHub_->SetOnSelected([](int32_t) {});
    eventHub_->SetOnRequestPopupData([](int32_t) { return std::vector<std::string>(); });
    eventHub_->SetOnPopupSelected([](int32_t) {});
    pattern_->selected_ = -1;
    pattern_->itemCount_ = CREATE_ARRAY_VALUE.size();
    pattern_->ApplyIndexChanged();
    EXPECT_EQ(pattern_->selected_, -1);

    /**
     * @tc.steps: step1. call pattern_ ApplyIndexChange function, compare result.
     * @tc.steps: case2: have onSelected, onRequestPopupData, onPopupSelected, selected = 1
     * @tc.expected: step1. OnKeyEvent success and result correct.
     */
    pattern_->selected_ = 1;
    pattern_->itemCount_ = CREATE_ARRAY_VALUE.size();
    pattern_->ApplyIndexChanged();
    EXPECT_EQ(pattern_->selected_, 1);

    /**
     * @tc.steps: step1. call pattern_ ApplyIndexChange function, compare result.
     * @tc.steps: case3: have onSelected, onRequestPopupData, onPopupSelected, selected > size
     * @tc.expected: step1. OnKeyEvent success and result correct.
     */
    pattern_->selected_ = CREATE_ARRAY_VALUE.size() + 1;
    pattern_->itemCount_ = CREATE_ARRAY_VALUE.size();
    pattern_->ApplyIndexChanged();
    EXPECT_NE(pattern_->selected_, 1);
}

/**
 * @tc.name: IndexerPattern014
 * @tc.desc: Test indexer pattern InitBubbleList function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerPattern014, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    PipelineContext::GetCurrentContext()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<IndexerTheme>()));

    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY_VALUE, 0);
    indexerView.SetUsingPopup(true);
    indexerView.SetAlignStyle(AlignStyle::LEFT);
    indexerView.SetPopupUnselectedColor(Color(0x00000000));
    GetInstance();
    RunMeasureAndLayout();

    eventHub_->SetOnRequestPopupData(GetPopupData);
    pattern_->selected_ = 2;
    pattern_->OnModifyDone();
    pattern_->ApplyIndexChanged(true);
    pattern_->UpdateBubbleView();

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
 * @tc.name: IndexerPattern015
 * @tc.desc: Test indexer pattern SetPositionOfPopupNode function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerPattern015, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    PipelineContext::GetCurrentContext()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<IndexerTheme>()));

    IndexerView indexerView1;
    indexerView1.Create(CREATE_ARRAY_VALUE, 0);
    indexerView1.SetUsingPopup(true);
    indexerView1.SetPopupHorizontalSpace(Dimension(50));
    GetInstance();
    RunMeasureAndLayout();

    eventHub_->SetOnRequestPopupData(GetPopupData);
    pattern_->selected_ = 2;
    pattern_->OnModifyDone();
    pattern_->ApplyIndexChanged(true);
    pattern_->UpdateBubbleView();

    ASSERT_NE(pattern_->popupNode_, nullptr);
    auto renderContext = pattern_->popupNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto rightValue = renderContext->GetPosition().value();

    IndexerView indexerView2;
    indexerView2.Create(CREATE_ARRAY_VALUE, 0);
    indexerView2.SetUsingPopup(true);
    indexerView2.SetAlignStyle(AlignStyle::LEFT);
    indexerView2.SetPopupHorizontalSpace(Dimension(50));
    GetInstance();
    RunMeasureAndLayout();

    eventHub_->SetOnRequestPopupData(GetPopupData);
    pattern_->selected_ = 2;
    pattern_->OnModifyDone();
    pattern_->ApplyIndexChanged(true);
    pattern_->UpdateBubbleView();

    ASSERT_NE(pattern_->popupNode_, nullptr);
    auto renderContext2 = pattern_->popupNode_->GetRenderContext();
    ASSERT_NE(renderContext2, nullptr);
    auto leftValue = renderContext2->GetPosition().value();
    EXPECT_NE(rightValue, leftValue);
}

/**
 * @tc.name: IndexerPattern016
 * @tc.desc: Test indexer pattern ChangeListItemsSelectedStyle function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerPattern016, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    PipelineContext::GetCurrentContext()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<IndexerTheme>()));

    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY_VALUE, 0);
    indexerView.SetUsingPopup(true);
    indexerView.SetPopupSelectedColor(Color(0x00000000));
    indexerView.SetPopupUnselectedColor(Color(0x00000000));
    indexerView.SetPopupItemBackground(Color(0x00000000));
    GetInstance();
    RunMeasureAndLayout();

    eventHub_->SetOnRequestPopupData(GetPopupData);
    pattern_->selected_ = 2;
    pattern_->OnModifyDone();
    pattern_->ApplyIndexChanged(true);
    pattern_->UpdateBubbleView();
    pattern_->ChangeListItemsSelectedStyle(0);

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
 * @tc.name: IndexerViewTest001
 * @tc.desc: Test all the properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerViewTest001, TestSize.Level1)
{
    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY_VALUE, 0);
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

    EXPECT_EQ(layoutProperty_->GetArrayValueValue(), CREATE_ARRAY_VALUE);
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
    indexerView.Create(CREATE_ARRAY_VALUE, 0);
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
    indexerView.Create(CREATE_ARRAY_VALUE, 0);
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
    indexerView.Create(CREATE_ARRAY_VALUE, 0);
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
 * @tc.name: IndexerAccessibilityTest001
 * @tc.desc: Test accessibility func.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerAccessibilityTest001, TestSize.Level1)
{
    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY_VALUE, 0);
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_EQ(accessibility_->GetEndIndex(), CREATE_ARRAY_VALUE.size() - 1);
    EXPECT_EQ(accessibility_->GetText(), CREATE_ARRAY_VALUE.at(0));
}
} // namespace OHOS::Ace::NG
