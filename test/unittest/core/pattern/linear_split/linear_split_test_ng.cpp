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

#include <cstdint>
#include <optional>

#include "gtest/gtest.h"

#include "core/components_ng/pattern/linear_split/linear_split_layout_property.h"

#define private public
#define protected public
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "core/components_ng/pattern/linear_split/linear_split_model.h"
#include "core/components_ng/pattern/linear_split/linear_split_pattern.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension WIDTH = 500.0_vp;
constexpr Dimension HEIGHT = 500.0_vp;
constexpr std::size_t DEFAULT_DRAG_INDEX = -1;
const float RK356_WIDTH = 720.0f;
const float RK356_HEIGHT = 1136.0f;
const float NO_PADDING = 0.0f;
const float ZERO = 0.0f;
const float SMALL_ITEM_HEIGHT = 50.0f;
const float SMALL_ITEM_WIDTH = 50.0f;
const float COLUMN_HEIGHT = 150.0f;
const float DEFAULT_SPLIT_WIDTH = 2.0f;
const float DEFAULT_SPLIT_HEIGHT = 2.0f;
const int32_t FIVE_ITEM_SIZE = 5;
const SizeF CONTAINER_SIZE(RK356_WIDTH, RK356_HEIGHT);
const OffsetF OFFSET_TOP_LEFT = OffsetF(ZERO, ZERO);
constexpr int32_t PLATFORM_VERSION_10 = 10;
constexpr int32_t PLATFORM_VERSION_9 = 9;
} // namespace

class LinearSplitTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    RefPtr<FrameNode> CreateLinearSplit(SplitType splitType, const std::function<void(LinearSplitModelNG)>& callback)
    {
        LinearSplitModelNG model;
        model.Create(splitType);
        if (callback) {
            callback(model);
        }
        RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
        ViewStackProcessor::GetInstance()->PopContainer();
        return AceType::DynamicCast<FrameNode>(element);
    }

    RefPtr<FrameNode> CreateColumn(const std::function<void(ColumnModelNG)>& callback)
    {
        ColumnModelNG model;
        model.Create(std::nullopt, nullptr, "");
        if (callback) {
            callback(model);
        }
        RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
        ViewStackProcessor::GetInstance()->PopContainer();
        return AceType::DynamicCast<FrameNode>(element);
    }
};
void LinearSplitTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
}

void LinearSplitTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void LinearSplitTestNg::SetUp()
{
    ViewStackProcessor::GetInstance()->ClearStack();
}

/**
 * @tc.name: LinearSplitCreatorTest001
 * @tc.desc: Test all the property of split
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, LinearSplitCreatorTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create split and initialize related properties.
     */
    LinearSplitModelNG model;
    model.Create(SplitType::COLUMN_SPLIT);
    model.SetResizable(SplitType::COLUMN_SPLIT, true);

    /**
     * @tc.steps: step2. Get split frameNode.
     */
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. Get layoutProperty
     * @tc.expected: Confirm that the properties are correct.
     */
    auto renderProperty = frameNode->GetLayoutProperty<LinearSplitLayoutProperty>();
    EXPECT_NE(renderProperty, nullptr);
    EXPECT_EQ(renderProperty->GetResizableValue(), true);
}

/**
 * @tc.name: LinearSplitPatternTest001
 * @tc.desc: Test linearSplit pattern OnDirtyLayoutWrapperSwap function.
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, LinearSplitPatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create split and initialize related properties.
     */
    LinearSplitModelNG model;
    model.Create(SplitType::COLUMN_SPLIT);
    model.SetResizable(SplitType::COLUMN_SPLIT, true);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. Get linearSplitPattern and linearSplitWrapper.
     */
    RefPtr<LinearSplitPattern> linearSPlitPattern = frameNode->GetPattern<LinearSplitPattern>();
    EXPECT_NE(linearSPlitPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));
    frameNode->SetGeometryNode(geometryNode);
    auto linearSplitLayoutProperty = frameNode->GetLayoutProperty<LinearSplitLayoutProperty>();
    EXPECT_NE(linearSplitLayoutProperty, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, linearSplitLayoutProperty);
    EXPECT_NE(layoutWrapper, nullptr);
    layoutWrapper->skipMeasureContent_ = false;
    std::vector<float> dragSplitOffset;
    std::vector<float> childrenDragPos;
    RefPtr<LinearSplitLayoutAlgorithm> linearLayoutAlgorithm = AceType::MakeRefPtr<LinearSplitLayoutAlgorithm>(
        SplitType::COLUMN_SPLIT, dragSplitOffset, childrenDragPos, false);

    /**
     * @tc.steps: step3. call linearSplitPattern OnDirtyLayoutWrapperSwap function, compare result.
     * @tc.expected: OnDirtyLayoutWrapperSwap success and result correct.
     */

    /**
     *     case 1: LayoutWrapperNode::SkipMeasureContent = false , skipMeasure = true;
     */
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(linearLayoutAlgorithm, true);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    bool firstCase = linearSPlitPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, false);
    EXPECT_FALSE(firstCase);

    /**
     *     case 2: LayoutWrapperNode::SkipMeasureContent = false , skipMeasure = false;
     */

    layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(linearLayoutAlgorithm, false);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    bool secondCase = linearSPlitPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false);
    EXPECT_TRUE(secondCase);
}

/**
 * @tc.name: LinearSplitPatternTest002
 * @tc.desc: Test linearSplit pattern OnModifyDone function.
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, LinearSplitPatternTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create split and initialize related properties.
     */
    LinearSplitModelNG model;
    model.Create(SplitType::COLUMN_SPLIT);
    model.SetResizable(SplitType::COLUMN_SPLIT, true);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Get linearSplitPattern and.
     */
    RefPtr<LinearSplitPattern> linearSPlitPattern = frameNode->GetPattern<LinearSplitPattern>();
    EXPECT_NE(linearSPlitPattern, nullptr);

    /**
     * @tc.steps: step3. call linearSplitPattern OnModifyDone function, compare result.
     * @tc.expected: OnModifyDone success and result correct.
     */
    linearSPlitPattern->OnModifyDone();
    EXPECT_TRUE(linearSPlitPattern->resizable_);
    EXPECT_NE(linearSPlitPattern->panEvent_, nullptr);
    EXPECT_NE(linearSPlitPattern->mouseEvent_, nullptr);
}

/**
 * @tc.name: LinearSplitPatternTest003
 * @tc.desc: Test linerSplit pattern OnDirtyLayoutWrapperSwap function.
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, LinearSplitPatternTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create split and initialize related properties.
     */
    LinearSplitModelNG model;
    model.Create(SplitType::COLUMN_SPLIT);
    model.SetResizable(SplitType::COLUMN_SPLIT, true);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Get linearSplitPattern.
     */
    RefPtr<LinearSplitPattern> linearSplitPattern = frameNode->GetPattern<LinearSplitPattern>();
    ASSERT_NE(linearSplitPattern, nullptr);

    /**
     * @tc.steps: step3. call linearSplitPattern OnDirtyLayoutWrapperSwap function, compare result.
     * @tc.expected: the properties of linearSplitPattern are updated rightly
     */
    RefPtr<LayoutWrapperNode> linearLayoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    linearSplitPattern->OnDirtyLayoutWrapperSwap(linearLayoutWrapper, true, true);
    EXPECT_EQ(linearSplitPattern->splitLength_, 0.0f);
    EXPECT_EQ(linearSplitPattern->isOverParent_, false);
}
/**
 * @tc.name: LinearSplitPatternTest004
 * @tc.desc: Test linerSplit pattern HandlePanEvent  when resizable is false.
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, LinearSplitPatternTest004, TestSize.Level1)
{
    std::vector<int32_t> platformVersions = { PLATFORM_VERSION_10, PLATFORM_VERSION_9 };
    for (int32_t turn = 0; turn < platformVersions.size(); turn++) {
        PipelineBase::GetCurrentContext()->SetMinPlatformVersion(platformVersions[turn]);
        /**
         * @tc.steps: step1. Create split and initialize related properties.
         */
        LinearSplitModelNG model;
        model.Create(SplitType::COLUMN_SPLIT);
        model.SetResizable(SplitType::COLUMN_SPLIT, false);

        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        ASSERT_NE(frameNode, nullptr);

        /**
         * @tc.steps: step2. Get linearSplitPattern.
         */
        RefPtr<LinearSplitPattern> linearSplitPattern = frameNode->GetPattern<LinearSplitPattern>();
        ASSERT_NE(linearSplitPattern, nullptr);

        /**
         * @tc.steps: step3. Construct GestureEvent and Call HandlePanStart, HandlePanUpdate.
         * @tc.expected: functions exit normally
         */
        GestureEvent info;
        linearSplitPattern->HandlePanStart(info);
        linearSplitPattern->HandlePanUpdate(info);
        EXPECT_FALSE(linearSplitPattern->isDraged_);

        /**
         * @tc.steps: step4. Construct MouseEvent and Call HandleMouseEvent.
         * @tc.expected: functions exit normally
         */
        MouseInfo info2;
        linearSplitPattern->HandleMouseEvent(info2);
        EXPECT_FALSE(linearSplitPattern->isDraged_);
    }
}
/**
 * @tc.name: LinearSplitPatternTest005
 * @tc.desc: Test linerSplit pattern HandlePanEvent  when resizable is true.
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, LinearSplitPatternTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create split and initialize related properties.
     */
    LinearSplitModelNG model;
    model.Create(SplitType::COLUMN_SPLIT);
    model.SetResizable(SplitType::COLUMN_SPLIT, true);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Get linearSplitPattern.
     */
    RefPtr<LinearSplitPattern> linearSplitPattern = frameNode->GetPattern<LinearSplitPattern>();
    ASSERT_NE(linearSplitPattern, nullptr);

    /**
     * @tc.steps: step3. Construct GestureEvent and Call HandlePanEvent function.
     * @tc.expected: functions exit normally when spiltRects is null
     */
    GestureEvent info;
    Offset globalLocation(1, 1);
    info.SetGlobalLocation(globalLocation);
    linearSplitPattern->HandlePanStart(info);
    EXPECT_TRUE(linearSplitPattern->isDraged_);
    linearSplitPattern->HandlePanUpdate(info);
    EXPECT_EQ(linearSplitPattern->preOffset_, info.GetOffsetY());
    linearSplitPattern->HandlePanEnd(info);
    EXPECT_EQ(linearSplitPattern->dragedSplitIndex_, DEFAULT_DRAG_INDEX);
}
/**
 * @tc.name: LinearSplitPatternTest006
 * @tc.desc: Test LinearSplit Layout.
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, LinearSplitPatternTest006, TestSize.Level1)
{
    std::vector<SplitType> splitType = { SplitType::COLUMN_SPLIT, SplitType::ROW_SPLIT };
    for (int turn = 0; turn < splitType.size(); turn++) {
        /**
         * @tc.steps: step1. Create split and initialize related properties.
         */
        LinearSplitModelNG model;
        model.Create(splitType[turn]);
        model.SetResizable(splitType[turn], true);

        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        ASSERT_NE(frameNode, nullptr);

        /**
         * @tc.steps: step2. Get linearSplitPattern and layoutWrapper.
         */
        RefPtr<LinearSplitPattern> linearSplitPattern = frameNode->GetPattern<LinearSplitPattern>();
        ASSERT_NE(linearSplitPattern, nullptr);
        RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
        ASSERT_NE(geometryNode, nullptr);
        geometryNode->SetContentSize(SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));
        frameNode->SetGeometryNode(geometryNode);
        auto linearSplitLayoutProperty = frameNode->GetLayoutProperty<LinearSplitLayoutProperty>();
        ASSERT_NE(linearSplitLayoutProperty, nullptr);
        LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(frameNode, geometryNode, linearSplitLayoutProperty);
        ASSERT_NE(layoutWrapper, nullptr);
        std::vector<float> dragSplitOffset = { 0.0f, 2.0f };
        std::vector<float> childrenDragPos;
        RefPtr<LinearSplitLayoutAlgorithm> linearLayoutAlgorithm =
            AceType::MakeRefPtr<LinearSplitLayoutAlgorithm>(splitType[turn], dragSplitOffset, childrenDragPos, false);
        RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
            AceType::MakeRefPtr<LayoutAlgorithmWrapper>(linearLayoutAlgorithm, false);
        layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
        /**
         * @tc.steps: steps3. Call  LinearSplitLayoutAlgorithm Layout without children.
         * @tc.expected: SplitRects is empty.
         */
        linearLayoutAlgorithm->Layout(layoutWrapper);
        EXPECT_TRUE(linearSplitPattern->splitRects_.empty());
        /**
         * @tc.steps: step4. Call  LinearSplitLayoutAlgorithm Measure without children.
         * @tc.expected: frameSize is right.
         */
        linearLayoutAlgorithm->Measure(layoutWrapper);
        EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize().Width(), 0);
    }
}
/**
 * @tc.name: LinearSplitPatternTest007
 * @tc.desc: Test ColumnSplit Layout with children nodes.
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, LinearSplitPatternTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create columnSplit and initialize related properties.
     */
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(PLATFORM_VERSION_10);
    LinearSplitModelNG model;
    model.Create(SplitType::COLUMN_SPLIT);
    model.SetResizable(SplitType::COLUMN_SPLIT, true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. Get linearSplitPattern and layoutWrapper.
     */
    RefPtr<LinearSplitPattern> linearSplitPattern = frameNode->GetPattern<LinearSplitPattern>();
    ASSERT_NE(linearSplitPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    frameNode->SetGeometryNode(geometryNode);
    auto linearSplitLayoutProperty = frameNode->GetLayoutProperty<LinearSplitLayoutProperty>();
    ASSERT_NE(linearSplitLayoutProperty, nullptr);
    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(frameNode, geometryNode, linearSplitLayoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    std::vector<float> dragSplitOffset;
    std::vector<float> childrenDragPos;
    RefPtr<LinearSplitLayoutAlgorithm> linearLayoutAlgorithm = AceType::MakeRefPtr<LinearSplitLayoutAlgorithm>(
        SplitType::COLUMN_SPLIT, dragSplitOffset, childrenDragPos, false);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(linearLayoutAlgorithm, false);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(RK356_WIDTH), CalcLength(RK356_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    PaddingProperty noPadding;
    noPadding.left = CalcLength(NO_PADDING);
    noPadding.right = CalcLength(NO_PADDING);
    noPadding.top = CalcLength(NO_PADDING);
    noPadding.bottom = CalcLength(NO_PADDING);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    /**
     * @tc.steps: step3. Create childFrameNode and Get childLayoutWrapper.
     */
    /* corresponding ets code:
        ColumnSplit(){
            Text('1').height(50).backgroundColor(0xF5DEB3).textAlign(TextAlign.Center).width('100%')
            Text('2').height(50).backgroundColor(0xD2B48C).textAlign(TextAlign.Center).width('100%')
            Text('3').height(50).backgroundColor(0xF5DEB3).textAlign(TextAlign.Center).width('100%')
            Text('4').height(50).backgroundColor(0xD2B48C).textAlign(TextAlign.Center).width('100%')
            Text('5').height(50).backgroundColor(0xF5DEB3).textAlign(TextAlign.Center).width('100%')
        }
        .backgroundColor(Color.Pink)
        .resizeable(true)
        .width('100%')
        .height('100%')
    */
    for (int32_t i = 0; i < FIVE_ITEM_SIZE; i++) {
        auto itemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, i + 1, AceType::MakeRefPtr<Pattern>());
        RefPtr<GeometryNode> itemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeometryNode->Reset();
        RefPtr<LayoutWrapperNode> itemLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(itemFrameNode, itemGeometryNode, itemFrameNode->GetLayoutProperty());
        itemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
        itemLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(RK356_WIDTH), CalcLength(SMALL_ITEM_HEIGHT)));
        itemLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
        auto boxLayoutAlgorithm = itemFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
        EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
        itemLayoutWrapper->SetLayoutAlgorithm(
            AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
        frameNode->AddChild(itemFrameNode);
        layoutWrapper->AppendChild(itemLayoutWrapper);
    }
    /**
     * @tc.steps: step4. Call Measure and Layout.
     * @tc.expected: size and offset are right
     */
    linearLayoutAlgorithm->Measure(layoutWrapper);
    linearLayoutAlgorithm->Layout(layoutWrapper);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(RK356_WIDTH, RK356_HEIGHT));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);

    auto verticalRemaining =
        RK356_HEIGHT - SMALL_ITEM_HEIGHT * FIVE_ITEM_SIZE - DEFAULT_SPLIT_HEIGHT * (FIVE_ITEM_SIZE - 1);
    for (int32_t i = 0; i < FIVE_ITEM_SIZE; i++) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(i);
        auto childSize = childWrapper->GetGeometryNode()->GetFrameSize();
        auto childOffset = childWrapper->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(childSize, SizeF(RK356_WIDTH, SMALL_ITEM_HEIGHT));
        EXPECT_EQ(childOffset, OffsetF(ZERO, verticalRemaining / 2 + i * (SMALL_ITEM_HEIGHT + DEFAULT_SPLIT_HEIGHT)));
    }
    linearSplitPattern->splitRects_ = linearLayoutAlgorithm->GetSplitRects();
    linearSplitPattern->childrenDragPos_ = linearLayoutAlgorithm->GetChildrenDragPos();
    linearSplitPattern->childrenConstrains_ = linearLayoutAlgorithm->GetChildrenConstrains();

    /**
     * @tc.steps: step5. Construct GestureEvent and Call HandlePanEvent function.
     * @tc.expected: functions exit normally when gestureEventInfo is not in splitRects region
     */
    GestureEvent info;
    Offset globalLocation(0, 500);
    info.SetGlobalLocation(globalLocation);
    linearSplitPattern->HandlePanStart(info);
    EXPECT_TRUE(linearSplitPattern->isDraged_);
    linearSplitPattern->HandlePanUpdate(info);
    EXPECT_EQ(linearSplitPattern->preOffset_, info.GetOffsetY());

    /**
     * @tc.steps: step6. Construct MouseInfo and Call HandleMouseEvent function.
     * @tc.expected: return normally when isDraged is true
     */
    MouseInfo mouseInfo;
    mouseInfo.SetGlobalLocation(globalLocation);
    linearSplitPattern->HandleMouseEvent(mouseInfo);
    EXPECT_EQ(linearSplitPattern->mouseDragedSplitIndex_, DEFAULT_DRAG_INDEX);

    /**
     * @tc.steps: step7. Update GestureEvent info and Start dragging.
     */
    Offset localLocation2(10, 541);
    info.SetLocalLocation(localLocation2);
    info.SetOffsetY(2);

    /**
     * @tc.steps: step8. Set IsOverParent and Call HandlePanEvent function.
     * @tc.expected: PanStart and PanUpdate return normally when IsOverParent is true
     * check the value is right when gestureEventInfo is in splitRects[1] region
     */
    bool isOverParent[2] = { true, false };
    for (int i = 0; i < 2; i++) {
        linearSplitPattern->isOverParent_ = isOverParent[i];
        linearSplitPattern->HandlePanStart(info);
        linearSplitPattern->HandlePanUpdate(info);
        EXPECT_EQ(linearSplitPattern->preOffset_, 2.0f);
        EXPECT_EQ(linearSplitPattern->dragedSplitIndex_, 1);

        /**
         * @tc.steps: step9. Stop Dragging and Call HandlePanEnd, HandleMouseEvent.
         * @tc.expected: check isDraged is false
         */
        linearSplitPattern->HandlePanEnd(info);
        EXPECT_FALSE(linearSplitPattern->isDraged_);
        linearSplitPattern->HandlePanUpdate(info);
        EXPECT_FALSE(linearSplitPattern->isDraged_);
        EXPECT_TRUE(linearSplitPattern->isDragedMoving_);
        MouseInfo mouseInfo2;
        mouseInfo2.SetLocalLocation(localLocation2);
        linearSplitPattern->HandleMouseEvent(mouseInfo2);
        EXPECT_EQ(linearSplitPattern->mouseDragedSplitIndex_, 1);
        mouseInfo2.SetButton(MouseButton::LEFT_BUTTON);
        mouseInfo2.SetAction(MouseAction::PRESS);
        linearSplitPattern->HandleMouseEvent(mouseInfo2);
        EXPECT_TRUE(linearSplitPattern->isDragedMoving_);
    }

    /**
     * @tc.steps: step10. Dragging back and Call HandlePanEvent function.
     * @tc.expected: check the value is right
     */
    info.SetOffsetY(-2);
    for (int i = 0; i < 2; i++) {
        linearSplitPattern->isOverParent_ = isOverParent[i];
        linearSplitPattern->HandlePanStart(info);
        EXPECT_EQ(linearSplitPattern->dragedSplitIndex_, 1);
        info.SetOffsetY(-3);
        linearSplitPattern->HandlePanUpdate(info);
        EXPECT_EQ(linearSplitPattern->childrenDragPos_[1], 491.0f);

        /**
         * @tc.steps: step11. Stop Dragging and Call HandlePanEnd, HandleMouseEvent.
         * @tc.expected: check isDraged is false
         */
        linearSplitPattern->HandlePanEnd(info);
        EXPECT_FALSE(linearSplitPattern->isDraged_);
        MouseInfo mouseInfo2;
        mouseInfo2.SetLocalLocation(localLocation2);
        linearSplitPattern->HandleMouseEvent(mouseInfo2);
        EXPECT_EQ(linearSplitPattern->mouseDragedSplitIndex_, 1);
    }
}
/**
 * @tc.name: LinearSplitPatternTest008
 * @tc.desc: Test RowSplit Layout with children nodes.
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, LinearSplitPatternTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create rowSplit and initialize related properties.
     */
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(PLATFORM_VERSION_10);
    LinearSplitModelNG model;
    model.Create(SplitType::ROW_SPLIT);
    model.SetResizable(SplitType::ROW_SPLIT, true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. Get linearSplitPattern and layoutWrapper.
     */
    RefPtr<LinearSplitPattern> linearSplitPattern = frameNode->GetPattern<LinearSplitPattern>();
    ASSERT_NE(linearSplitPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    frameNode->SetGeometryNode(geometryNode);
    auto linearSplitLayoutProperty = frameNode->GetLayoutProperty<LinearSplitLayoutProperty>();
    ASSERT_NE(linearSplitLayoutProperty, nullptr);
    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(frameNode, geometryNode, linearSplitLayoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    std::vector<float> dragSplitOffset;
    std::vector<float> childrenDragPos;
    RefPtr<LinearSplitLayoutAlgorithm> linearLayoutAlgorithm =
        AceType::MakeRefPtr<LinearSplitLayoutAlgorithm>(SplitType::ROW_SPLIT, dragSplitOffset, childrenDragPos, false);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(linearLayoutAlgorithm, false);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(RK356_WIDTH), CalcLength(COLUMN_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    PaddingProperty noPadding;
    noPadding.left = CalcLength(NO_PADDING);
    noPadding.right = CalcLength(NO_PADDING);
    noPadding.top = CalcLength(NO_PADDING);
    noPadding.bottom = CalcLength(NO_PADDING);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    /**
     * @tc.steps: step3. Create childFrameNode and Get childLayoutWrapper.
     */
    /* corresponding ets code:
        RowSplit(){
            Text('1').width(50).backgroundColor(0xD2B48C).textAlign(TextAlign.Center).height('100%')
            Text('2').width(50).backgroundColor(0xD2B48C).textAlign(TextAlign.Center).height('100%')
            Text('3').width(50).backgroundColor(0xD2B48C).textAlign(TextAlign.Center).height('100%')
            Text('4').width(50).backgroundColor(0xD2B48C).textAlign(TextAlign.Center).height('100%')
            Text('5').width(50).backgroundColor(0xF5DEB3).textAlign(TextAlign.Center).height('100%')
        }
        .resizeable(true)
        .width('100%')
        .height(150)
        .backgroundColor(Color.Pink)
    */
    for (int32_t i = 0; i < FIVE_ITEM_SIZE; i++) {
        auto itemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, i + 1, AceType::MakeRefPtr<Pattern>());
        RefPtr<GeometryNode> itemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeometryNode->Reset();
        RefPtr<LayoutWrapperNode> itemLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(itemFrameNode, itemGeometryNode, itemFrameNode->GetLayoutProperty());
        itemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
        itemLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(SMALL_ITEM_WIDTH), CalcLength(COLUMN_HEIGHT)));
        itemLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
        auto boxLayoutAlgorithm = itemFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
        EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
        itemLayoutWrapper->SetLayoutAlgorithm(
            AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
        frameNode->AddChild(itemFrameNode);
        layoutWrapper->AppendChild(itemLayoutWrapper);
    }
    /**
     * @tc.steps: step4. Call Measure and Layout.
     * @tc.expected: size and offset are right
     */
    linearLayoutAlgorithm->Measure(layoutWrapper);
    linearLayoutAlgorithm->Layout(layoutWrapper);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(RK356_WIDTH, COLUMN_HEIGHT));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);

    auto horizontalRemaining =
        RK356_WIDTH - FIVE_ITEM_SIZE * SMALL_ITEM_WIDTH - DEFAULT_SPLIT_HEIGHT * (FIVE_ITEM_SIZE - 1);
    for (int32_t i = 0; i < FIVE_ITEM_SIZE; i++) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(i);
        auto childSize = childWrapper->GetGeometryNode()->GetFrameSize();
        auto childOffset = childWrapper->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(childSize, SizeF(SMALL_ITEM_WIDTH, COLUMN_HEIGHT));
        EXPECT_EQ(childOffset, OffsetF(horizontalRemaining / 2 + i * (SMALL_ITEM_WIDTH + DEFAULT_SPLIT_WIDTH), ZERO));
    }

    linearSplitPattern->splitRects_ = linearLayoutAlgorithm->GetSplitRects();
    linearSplitPattern->childrenDragPos_ = linearLayoutAlgorithm->GetChildrenDragPos();
    linearSplitPattern->childrenConstrains_ = linearLayoutAlgorithm->GetChildrenConstrains();
    /**
     * @tc.steps: step5. Construct GestureEvent info and Start dragging.
     */
    GestureEvent info;
    Offset localLocation(333, 10);
    info.SetLocalLocation(localLocation);
    info.SetOffsetX(2);
    /**
     * @tc.steps: step6. Set IsOverParent and Call HandlePanEvent function.
     * @tc.expected: PanStart and PanUpdate return normally when IsOverParent is true
     * check the value is right when gestureEventInfo is in splitRects[1] region
     */
    bool isOverParent[2] = { true, false };
    for (int i = 0; i < 2; i++) {
        linearSplitPattern->isOverParent_ = isOverParent[i];
        linearSplitPattern->HandlePanStart(info);
        linearSplitPattern->HandlePanUpdate(info);
        EXPECT_EQ(linearSplitPattern->preOffset_, 2.0f);
        EXPECT_EQ(linearSplitPattern->dragedSplitIndex_, 1);

        /**
         * @tc.steps: step7. Stop Dragging and Call HandlePanEnd, HandleMouseEvent.
         * @tc.expected: check isDraged is false
         */
        linearSplitPattern->HandlePanEnd(info);
        EXPECT_FALSE(linearSplitPattern->isDraged_);
        linearSplitPattern->HandlePanUpdate(info);
        EXPECT_FALSE(linearSplitPattern->isDraged_);
        EXPECT_TRUE(linearSplitPattern->isDragedMoving_);
        MouseInfo mouseInfo2;
        mouseInfo2.SetLocalLocation(localLocation);
        linearSplitPattern->HandleMouseEvent(mouseInfo2);
        EXPECT_EQ(linearSplitPattern->mouseDragedSplitIndex_, 1);
        mouseInfo2.SetButton(MouseButton::LEFT_BUTTON);
        mouseInfo2.SetAction(MouseAction::PRESS);
        linearSplitPattern->HandleMouseEvent(mouseInfo2);
        EXPECT_TRUE(linearSplitPattern->isDragedMoving_);
    }

    /**
     * @tc.steps: step8. Dragging back and Call HandlePanEvent function.
     * @tc.expected: check the value is right
     */
    info.SetOffsetX(-2);
    for (int i = 0; i < 2; i++) {
        linearSplitPattern->isOverParent_ = isOverParent[i];
        linearSplitPattern->HandlePanStart(info);
        EXPECT_EQ(linearSplitPattern->dragedSplitIndex_, 1);
        info.SetOffsetX(-3);
        linearSplitPattern->HandlePanUpdate(info);
        EXPECT_EQ(linearSplitPattern->childrenDragPos_[1], 283.0f);

        /**
         * @tc.steps: step9. Stop Dragging and Call HandlePanEnd, HandleMouseEvent.
         * @tc.expected: check isDraged is false
         */
        linearSplitPattern->HandlePanEnd(info);
        EXPECT_FALSE(linearSplitPattern->isDraged_);
        MouseInfo mouseInfo2;
        mouseInfo2.SetLocalLocation(localLocation);
        linearSplitPattern->HandleMouseEvent(mouseInfo2);
        EXPECT_EQ(linearSplitPattern->mouseDragedSplitIndex_, 1);
    }

    /**
     * @tc.steps: step10. Construct GestureEvent and Call HandlePanEvent function.
     * @tc.expected: function exits normally when gestureEventInfo is not in splitRects region
     */
    GestureEvent info2;
    Offset globalLocation2(300, 10);
    info2.SetGlobalLocation(globalLocation2);
    linearSplitPattern->HandlePanUpdate(info2);
    EXPECT_EQ(linearSplitPattern->preOffset_, info2.GetOffsetX());
}
/**
 * @tc.name: LinearSplitPatternTest009
 * @tc.desc: Test linerSplit pattern HandleMouseEvent  when resizable is true.
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, LinearSplitPatternTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create columnSplit and initialize related properties.
     */
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(PLATFORM_VERSION_10);
    LinearSplitModelNG model;
    model.Create(SplitType::COLUMN_SPLIT);
    model.SetResizable(SplitType::COLUMN_SPLIT, true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. Get linearSplitPattern.
     */
    RefPtr<LinearSplitPattern> linearSplitPattern = frameNode->GetPattern<LinearSplitPattern>();
    ASSERT_NE(linearSplitPattern, nullptr);
    linearSplitPattern->HandleHoverEvent(true);
    /**
     * @tc.steps: step3. Construct MouseEvent and Call HandleMouseEvent function.
     * @tc.expected: function exits normally when splitRects is empty
     */
    MouseInfo info;
    Offset globalLocation(0, 500);
    info.SetGlobalLocation(globalLocation);
    linearSplitPattern->HandleHoverEvent(false);
    linearSplitPattern->HandleMouseEvent(info);
    EXPECT_EQ(linearSplitPattern->mouseDragedSplitIndex_, DEFAULT_DRAG_INDEX);
    /**
     * @tc.steps: step4. Construct GestureEvent and Call HandlePanEnd function.
     * @tc.expected: function exits normally when sourceDevice is SourceType::MOUSE
     */
    GestureEvent gestureInfo;
    gestureInfo.SetSourceDevice(SourceType::MOUSE);
    gestureInfo.SetGlobalLocation(globalLocation);
    linearSplitPattern->HandlePanEnd(gestureInfo);
    EXPECT_EQ(linearSplitPattern->dragedSplitIndex_, DEFAULT_DRAG_INDEX);
}
/**
 * @tc.name: LinearSplitPatternTest010
 * @tc.desc: Test RowSplit Layout with children nodes with API9.
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, LinearSplitPatternTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create rowSplit and initialize related properties.
     */
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(PLATFORM_VERSION_9);
    LinearSplitModelNG model;
    model.Create(SplitType::ROW_SPLIT);
    model.SetResizable(SplitType::ROW_SPLIT, true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. Get linearSplitPattern and layoutWrapper.
     */
    RefPtr<LinearSplitPattern> linearSplitPattern = frameNode->GetPattern<LinearSplitPattern>();
    ASSERT_NE(linearSplitPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    frameNode->SetGeometryNode(geometryNode);
    auto linearSplitLayoutProperty = frameNode->GetLayoutProperty<LinearSplitLayoutProperty>();
    ASSERT_NE(linearSplitLayoutProperty, nullptr);
    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(frameNode, geometryNode, linearSplitLayoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    std::vector<float> dragSplitOffset;
    std::vector<float> childrenDragPos;
    RefPtr<LinearSplitLayoutAlgorithm> linearLayoutAlgorithm =
        AceType::MakeRefPtr<LinearSplitLayoutAlgorithm>(SplitType::ROW_SPLIT, dragSplitOffset, childrenDragPos, false);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(linearLayoutAlgorithm, false);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(RK356_WIDTH), CalcLength(COLUMN_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    PaddingProperty noPadding;
    noPadding.left = CalcLength(NO_PADDING);
    noPadding.right = CalcLength(NO_PADDING);
    noPadding.top = CalcLength(NO_PADDING);
    noPadding.bottom = CalcLength(NO_PADDING);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    /**
     * @tc.steps: step3. Create childFrameNode and Get childLayoutWrapper.
     */
    /* corresponding ets code:
        RowSplit(){
            Text('1').width(50).backgroundColor(0xD2B48C).textAlign(TextAlign.Center).height('100%')
            Text('2').width(50).backgroundColor(0xD2B48C).textAlign(TextAlign.Center).height('100%')
            Text('3').width(50).backgroundColor(0xD2B48C).textAlign(TextAlign.Center).height('100%')
            Text('4').width(50).backgroundColor(0xD2B48C).textAlign(TextAlign.Center).height('100%')
            Text('5').width(50).backgroundColor(0xF5DEB3).textAlign(TextAlign.Center).height('100%')
        }
        .resizeable(true)
        .width('100%')
        .height(150)
        .backgroundColor(Color.Pink)
    */
    for (int32_t i = 0; i < FIVE_ITEM_SIZE; i++) {
        auto itemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, i + 1, AceType::MakeRefPtr<Pattern>());
        RefPtr<GeometryNode> itemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeometryNode->Reset();
        RefPtr<LayoutWrapperNode> itemLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(itemFrameNode, itemGeometryNode, itemFrameNode->GetLayoutProperty());
        itemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
        itemLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(SMALL_ITEM_WIDTH), CalcLength(COLUMN_HEIGHT)));
        itemLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
        auto boxLayoutAlgorithm = itemFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
        EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
        itemLayoutWrapper->SetLayoutAlgorithm(
            AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
        frameNode->AddChild(itemFrameNode);
        layoutWrapper->AppendChild(itemLayoutWrapper);
    }
    /**
     * @tc.steps: step4. Call Measure and Layout.
     * @tc.expected: size and offset are right
     */
    linearLayoutAlgorithm->Measure(layoutWrapper);
    linearLayoutAlgorithm->Layout(layoutWrapper);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(RK356_WIDTH, COLUMN_HEIGHT));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);

    auto horizontalRemaining = RK356_WIDTH - FIVE_ITEM_SIZE * SMALL_ITEM_WIDTH;
    for (int32_t i = 0; i < FIVE_ITEM_SIZE; i++) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(i);
        auto childSize = childWrapper->GetGeometryNode()->GetFrameSize();
        auto childOffset = childWrapper->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(childSize, SizeF(SMALL_ITEM_WIDTH, COLUMN_HEIGHT));
        EXPECT_EQ(childOffset, OffsetF(horizontalRemaining / 2 + i * (SMALL_ITEM_WIDTH + DEFAULT_SPLIT_WIDTH), ZERO));
    }

    linearSplitPattern->splitRects_ = linearLayoutAlgorithm->GetSplitRects();
    EXPECT_TRUE(linearSplitPattern->splitRects_[1].IsInRegion(Point(335, 10)));
    /**
     * @tc.steps: step5. Construct GestureEvent info and Start dragging.
     */
    GestureEvent info;
    Offset localLocation(335, 10);
    info.SetLocalLocation(localLocation);
    info.SetOffsetX(2);
    linearSplitPattern->dragSplitOffset_ = { ZERO, ZERO, ZERO, ZERO, ZERO };
    /**
     * @tc.steps: step6. Set IsOverParent and Call HandlePanEvent function.
     * @tc.expected: PanStart and PanUpdate return normally when IsOverParent is true
     * check the value is right when gestureEventInfo is in splitRects[1] region
     */
    bool isOverParent[2] = { true, false };
    for (int i = 0; i < 2; i++) {
        linearSplitPattern->isOverParent_ = isOverParent[i];
        linearSplitPattern->HandlePanStart(info);
        linearSplitPattern->HandlePanUpdate(info);
        EXPECT_EQ(linearSplitPattern->preOffset_, 2.0f);
        EXPECT_EQ(linearSplitPattern->dragedSplitIndex_, 1);

        /**
         * @tc.steps: step7. Stop Dragging and Call HandlePanEnd, HandleMouseEvent.
         * @tc.expected: check isDraged is false
         */
        linearSplitPattern->HandlePanEnd(info);
        EXPECT_FALSE(linearSplitPattern->isDraged_);
        linearSplitPattern->HandlePanUpdate(info);
        EXPECT_FALSE(linearSplitPattern->isDraged_);
        EXPECT_TRUE(linearSplitPattern->isDragedMoving_);
        MouseInfo mouseInfo2;
        mouseInfo2.SetLocalLocation(localLocation);
        linearSplitPattern->HandleMouseEvent(mouseInfo2);
        EXPECT_EQ(linearSplitPattern->mouseDragedSplitIndex_, 1);
        mouseInfo2.SetButton(MouseButton::LEFT_BUTTON);
        mouseInfo2.SetAction(MouseAction::PRESS);
        linearSplitPattern->HandleMouseEvent(mouseInfo2);
        EXPECT_TRUE(linearSplitPattern->isDragedMoving_);
    }
    /**
     * @tc.steps: step8. Dragging back and Call HandlePanEvent function.
     * @tc.expected: check the value is right
     */
    info.SetOffsetX(-2);
    for (int i = 0; i < 2; i++) {
        linearSplitPattern->isOverParent_ = isOverParent[i];
        linearSplitPattern->HandlePanStart(info);
        EXPECT_EQ(linearSplitPattern->dragedSplitIndex_, 1);
        info.SetOffsetX(-3);
        linearSplitPattern->HandlePanUpdate(info);
        EXPECT_EQ(linearSplitPattern->dragSplitOffset_[1], 0.0f);

        /**
         * @tc.steps: step9. Stop Dragging and Call HandlePanEnd, HandleMouseEvent.
         * @tc.expected: check isDraged is false
         */
        linearSplitPattern->HandlePanEnd(info);
        EXPECT_FALSE(linearSplitPattern->isDraged_);
        MouseInfo mouseInfo2;
        mouseInfo2.SetLocalLocation(localLocation);
        linearSplitPattern->HandleMouseEvent(mouseInfo2);
        EXPECT_EQ(linearSplitPattern->mouseDragedSplitIndex_, 1);
    }
    /**
     * @tc.steps: step10. Construct GestureEvent and Call HandlePanEvent function.
     * @tc.expected: function exits normally when gestureEventInfo is not in splitRects region
     */
    GestureEvent info2;
    Offset localLocation2(300, 10);
    info2.SetLocalLocation(localLocation2);
    linearSplitPattern->HandlePanUpdate(info2);
    EXPECT_EQ(linearSplitPattern->preOffset_, info2.GetOffsetX());
}
/**
 * @tc.name: LinearSplitPatternTest011
 * @tc.desc: Test ColumnSplit Layout with children nodes with API9.
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, LinearSplitPatternTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create columnSplit and initialize related properties.
     */
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(PLATFORM_VERSION_9);
    LinearSplitModelNG model;
    model.Create(SplitType::COLUMN_SPLIT);
    model.SetResizable(SplitType::COLUMN_SPLIT, true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. Get linearSplitPattern and layoutWrapper.
     */
    RefPtr<LinearSplitPattern> linearSplitPattern = frameNode->GetPattern<LinearSplitPattern>();
    ASSERT_NE(linearSplitPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    frameNode->SetGeometryNode(geometryNode);
    auto linearSplitLayoutProperty = frameNode->GetLayoutProperty<LinearSplitLayoutProperty>();
    ASSERT_NE(linearSplitLayoutProperty, nullptr);
    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(frameNode, geometryNode, linearSplitLayoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    std::vector<float> dragSplitOffset;
    std::vector<float> childrenDragPos;
    RefPtr<LinearSplitLayoutAlgorithm> linearLayoutAlgorithm = AceType::MakeRefPtr<LinearSplitLayoutAlgorithm>(
        SplitType::COLUMN_SPLIT, dragSplitOffset, childrenDragPos, false);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(linearLayoutAlgorithm, false);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(RK356_WIDTH), CalcLength(RK356_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    PaddingProperty noPadding;
    noPadding.left = CalcLength(NO_PADDING);
    noPadding.right = CalcLength(NO_PADDING);
    noPadding.top = CalcLength(NO_PADDING);
    noPadding.bottom = CalcLength(NO_PADDING);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    /**
     * @tc.steps: step3. Create childFrameNode and Get childLayoutWrapper.
     */
    /* corresponding ets code:
        ColumnSplit(){
            Text('1').height(50).backgroundColor(0xF5DEB3).textAlign(TextAlign.Center).width('100%')
            Text('2').height(50).backgroundColor(0xD2B48C).textAlign(TextAlign.Center).width('100%')
            Text('3').height(50).backgroundColor(0xF5DEB3).textAlign(TextAlign.Center).width('100%')
            Text('4').height(50).backgroundColor(0xD2B48C).textAlign(TextAlign.Center).width('100%')
            Text('5').height(50).backgroundColor(0xF5DEB3).textAlign(TextAlign.Center).width('100%')
        }
        .backgroundColor(Color.Pink)
        .resizeable(true)
        .width('100%')
        .height('100%')
    */
    for (int32_t i = 0; i < FIVE_ITEM_SIZE; i++) {
        auto itemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, i + 1, AceType::MakeRefPtr<Pattern>());
        RefPtr<GeometryNode> itemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeometryNode->Reset();
        RefPtr<LayoutWrapperNode> itemLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(itemFrameNode, itemGeometryNode, itemFrameNode->GetLayoutProperty());
        itemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
        itemLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(RK356_WIDTH), CalcLength(SMALL_ITEM_HEIGHT)));
        itemLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
        auto boxLayoutAlgorithm = itemFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
        EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
        itemLayoutWrapper->SetLayoutAlgorithm(
            AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
        frameNode->AddChild(itemFrameNode);
        layoutWrapper->AppendChild(itemLayoutWrapper);
    }
    /**
     * @tc.steps: step4. Call Measure and Layout.
     * @tc.expected: size and offset are right
     */
    linearLayoutAlgorithm->Measure(layoutWrapper);
    linearLayoutAlgorithm->Layout(layoutWrapper);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(RK356_WIDTH, RK356_HEIGHT));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);

    auto verticalRemaining = RK356_HEIGHT - SMALL_ITEM_HEIGHT * FIVE_ITEM_SIZE;
    for (int32_t i = 0; i < FIVE_ITEM_SIZE; i++) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(i);
        auto childSize = childWrapper->GetGeometryNode()->GetFrameSize();
        auto childOffset = childWrapper->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(childSize, SizeF(RK356_WIDTH, SMALL_ITEM_HEIGHT));
        EXPECT_EQ(childOffset, OffsetF(ZERO, verticalRemaining / 2 + i * (SMALL_ITEM_HEIGHT + DEFAULT_SPLIT_HEIGHT)));
    }
    linearSplitPattern->splitRects_ = linearLayoutAlgorithm->GetSplitRects();

    /**
     * @tc.steps: step5. Construct GestureEvent and Call HandlePanEvent function.
     * @tc.expected: functions exit normally when gestureEventInfo is not in splitRects region
     */
    GestureEvent info;
    Offset globalLocation(0, 500);
    info.SetGlobalLocation(globalLocation);
    linearSplitPattern->HandlePanStart(info);
    EXPECT_TRUE(linearSplitPattern->isDraged_);
    linearSplitPattern->HandlePanUpdate(info);
    EXPECT_EQ(linearSplitPattern->preOffset_, info.GetOffsetY());

    /**
     * @tc.steps: step6. Construct MouseInfo and Call HandleMouseEvent function.
     * @tc.expected: return normally when isDraged is true
     */
    MouseInfo mouseInfo;
    mouseInfo.SetGlobalLocation(globalLocation);
    linearSplitPattern->HandleMouseEvent(mouseInfo);
    EXPECT_EQ(linearSplitPattern->mouseDragedSplitIndex_, DEFAULT_DRAG_INDEX);

    /**
     * @tc.steps: step7. Update GestureEvent info and Start dragging.
     */
    Offset localLocation2(10, 543);
    info.SetLocalLocation(localLocation2);
    info.SetOffsetY(2);
    linearSplitPattern->dragSplitOffset_ = { ZERO, ZERO, ZERO, ZERO, ZERO };
    /**
     * @tc.steps: step8. Set IsOverParent and Call HandlePanEvent function.
     * @tc.expected: PanStart and PanUpdate return normally when IsOverParent is true
     * check the value is right when gestureEventInfo is in splitRects[1] region
     */
    bool isOverParent[2] = { true, false };
    for (int i = 0; i < 2; i++) {
        linearSplitPattern->isOverParent_ = isOverParent[i];
        linearSplitPattern->HandlePanStart(info);
        linearSplitPattern->HandlePanUpdate(info);
        EXPECT_EQ(linearSplitPattern->preOffset_, 2.0f);
        EXPECT_EQ(linearSplitPattern->dragedSplitIndex_, 1);

        /**
         * @tc.steps: step9. Stop Dragging and Call HandlePanEnd, HandleMouseEvent.
         * @tc.expected: check isDraged is false
         */
        linearSplitPattern->HandlePanEnd(info);
        EXPECT_FALSE(linearSplitPattern->isDraged_);
        linearSplitPattern->HandlePanUpdate(info);
        EXPECT_FALSE(linearSplitPattern->isDraged_);
        EXPECT_TRUE(linearSplitPattern->isDragedMoving_);
        MouseInfo mouseInfo2;
        mouseInfo2.SetLocalLocation(localLocation2);
        linearSplitPattern->HandleMouseEvent(mouseInfo2);
        EXPECT_EQ(linearSplitPattern->mouseDragedSplitIndex_, 1);
        mouseInfo2.SetButton(MouseButton::LEFT_BUTTON);
        mouseInfo2.SetAction(MouseAction::PRESS);
        linearSplitPattern->HandleMouseEvent(mouseInfo2);
        EXPECT_TRUE(linearSplitPattern->isDragedMoving_);
    }

    /**
     * @tc.steps: step10. Dragging back and Call HandlePanEvent function.
     * @tc.expected: check the value is right
     */
    info.SetOffsetY(-2);
    for (int i = 0; i < 2; i++) {
        linearSplitPattern->isOverParent_ = isOverParent[i];
        linearSplitPattern->HandlePanStart(info);
        EXPECT_EQ(linearSplitPattern->dragedSplitIndex_, 1);
        info.SetOffsetY(-3);
        linearSplitPattern->HandlePanUpdate(info);
        EXPECT_EQ(linearSplitPattern->dragSplitOffset_[1], 0.0f);

        /**
         * @tc.steps: step11. Stop Dragging and Call HandlePanEnd, HandleMouseEvent.
         * @tc.expected: check isDraged is false
         */
        linearSplitPattern->HandlePanEnd(info);
        EXPECT_FALSE(linearSplitPattern->isDraged_);
        MouseInfo mouseInfo2;
        mouseInfo2.SetLocalLocation(localLocation2);
        linearSplitPattern->HandleMouseEvent(mouseInfo2);
        EXPECT_EQ(linearSplitPattern->mouseDragedSplitIndex_, 1);
    }
}
/**
 * @tc.name: LinearSplitPatternTest012
 * @tc.desc: Test FRC callback
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, LinearSplitPatternTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create columnSplit and initialize related properties.
     */
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(PLATFORM_VERSION_9);
    LinearSplitModelNG model;
    model.Create(SplitType::COLUMN_SPLIT);
    model.SetResizable(SplitType::COLUMN_SPLIT, true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    
    /**
     * @tc.steps: step2. Test FRC.
     */
    RefPtr<LinearSplitPattern> linearSplitPattern = frameNode->GetPattern<LinearSplitPattern>();
    ASSERT_NE(linearSplitPattern, nullptr);
    linearSplitPattern->isDragedMoving_ = true;
    auto info = GestureEvent();
    linearSplitPattern->HandlePanEnd(info);
}

/**
 * @tc.name: MeasureSelfByLayoutPolicyTest01
 * @tc.desc: Test MeasureSelfByLayoutPolicy function
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, MeasureSelfByLayoutPolicyTest01, TestSize.Level1)
{
    auto frameNode = CreateLinearSplit(SplitType::ROW_SPLIT, [this](LinearSplitModelNG model) {});
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LinearSplitLayoutAlgorithm algorithm(SplitType::ROW_SPLIT, {}, {}, false);
    SizeF childTotalSize(100, 200);
    SizeF childMaxSize(150, 250);
    LayoutConstraintF layoutConstraint = {.parentIdealSize = {300, 350}};
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
    auto selfSize = algorithm.MeasureSelfByLayoutPolicy(Referenced::RawPtr(frameNode), childTotalSize, childMaxSize);
    EXPECT_EQ(selfSize, OptionalSizeF(300, 350)) << selfSize.ToString();

    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, false);
    selfSize = algorithm.MeasureSelfByLayoutPolicy(Referenced::RawPtr(frameNode), childTotalSize, childMaxSize);
    EXPECT_EQ(selfSize, OptionalSizeF(std::nullopt, std::nullopt));

    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, false);
    selfSize = algorithm.MeasureSelfByLayoutPolicy(Referenced::RawPtr(frameNode), childTotalSize, childMaxSize);
    EXPECT_EQ(selfSize, OptionalSizeF(std::nullopt, std::nullopt));
    
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, false);
    selfSize = algorithm.MeasureSelfByLayoutPolicy(Referenced::RawPtr(frameNode), childTotalSize, childMaxSize);
    EXPECT_EQ(selfSize, OptionalSizeF(100, 250));

    algorithm.splitType_ = SplitType::COLUMN_SPLIT;
    selfSize = algorithm.MeasureSelfByLayoutPolicy(Referenced::RawPtr(frameNode), childTotalSize, childMaxSize);
    EXPECT_EQ(selfSize, OptionalSizeF(150, 200));

    layoutProperty->UpdateCalcMaxSize(CalcSize(CalcLength(50), CalcLength(50)));
    selfSize = algorithm.MeasureSelfByLayoutPolicy(Referenced::RawPtr(frameNode), childTotalSize, childMaxSize);
    EXPECT_EQ(selfSize, OptionalSizeF(50, 50));
}

/**
 * @tc.name: IgnoreLayoutSafeArea001
 * @tc.desc: Test MeasureSelfByLayoutPolicy function
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, IgnoreLayoutSafeArea001, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetMinPlatformVersion(PLATFORM_VERSION_10);
    RefPtr<FrameNode> column;
    auto frameNode = CreateLinearSplit(SplitType::ROW_SPLIT, [this, &column](LinearSplitModelNG model) {
        column = CreateColumn([this](ColumnModelNG model) {
        });
    });
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(300.0f, DimensionUnit::PX), CalcLength(350.0f, DimensionUnit::PX)));
    PaddingProperty padding;
    padding.left = CalcLength(10.0f);
    padding.right = CalcLength(10.0f);
    padding.top = CalcLength(10.0f);
    padding.bottom = CalcLength(10.0f);
    layoutProperty->UpdateSafeAreaPadding(padding);
    auto childLayoutProperty = column->GetLayoutProperty();
    ASSERT_NE(childLayoutProperty, nullptr);
    IgnoreLayoutSafeAreaOpts opts = { .type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM,
        .edges = NG::LAYOUT_SAFE_AREA_EDGE_ALL };
    childLayoutProperty->UpdateIgnoreLayoutSafeAreaOpts(opts);
    childLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(100.0f, DimensionUnit::PX), CalcLength(100.0f, DimensionUnit::PX)));
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    frameNode->CreateLayoutTask();
    EXPECT_EQ(frameNode->GetGeometryNode()->GetFrameSize(), SizeF(300.0f, 350.0f))  << frameNode->GetGeometryNode()->GetFrameRect().ToString();
    EXPECT_EQ(frameNode->GetGeometryNode()->GetFrameOffset(), OffsetF(0.0f, 0.0f));
    EXPECT_EQ(column->GetGeometryNode()->GetFrameSize(), SizeF(100.0f, 100.0f));
    EXPECT_EQ(column->GetGeometryNode()->GetFrameOffset(), OffsetF(100.0f, 0.0f))  << column->GetGeometryNode()->GetFrameRect().ToString();
}
} // namespace OHOS::Ace::NG