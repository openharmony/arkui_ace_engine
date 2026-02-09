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
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "core/components_ng/pattern/linear_split/linear_split_model.h"
#include "core/components_ng/pattern/linear_split/linear_split_pattern.h"
#include "test/mock/base/mock_system_properties.h"
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
HWTEST_F(LinearSplitTestNg, LinearSplitCreatorTest001, TestSize.Level0)
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
HWTEST_F(LinearSplitTestNg, LinearSplitPatternTest001, TestSize.Level0)
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
HWTEST_F(LinearSplitTestNg, LinearSplitPatternTest002, TestSize.Level0)
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
HWTEST_F(LinearSplitTestNg, LinearSplitPatternTest003, TestSize.Level0)
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
HWTEST_F(LinearSplitTestNg, LinearSplitPatternTest004, TestSize.Level0)
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
HWTEST_F(LinearSplitTestNg, LinearSplitPatternTest005, TestSize.Level0)
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
HWTEST_F(LinearSplitTestNg, LinearSplitPatternTest006, TestSize.Level0)
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
HWTEST_F(LinearSplitTestNg, LinearSplitPatternTest007, TestSize.Level0)
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
HWTEST_F(LinearSplitTestNg, LinearSplitPatternTest008, TestSize.Level0)
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
HWTEST_F(LinearSplitTestNg, LinearSplitPatternTest009, TestSize.Level0)
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
HWTEST_F(LinearSplitTestNg, LinearSplitPatternTest010, TestSize.Level0)
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
HWTEST_F(LinearSplitTestNg, LinearSplitPatternTest011, TestSize.Level0)
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
HWTEST_F(LinearSplitTestNg, LinearSplitPatternTest012, TestSize.Level0)
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
HWTEST_F(LinearSplitTestNg, MeasureSelfByLayoutPolicyTest01, TestSize.Level0)
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
HWTEST_F(LinearSplitTestNg, IgnoreLayoutSafeArea001, TestSize.Level0)
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
    layoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(300.0f, DimensionUnit::PX), CalcLength(350.0f, DimensionUnit::PX)));
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
    childLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(100.0f, DimensionUnit::PX), CalcLength(100.0f, DimensionUnit::PX)));
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    frameNode->CreateLayoutTask();
    EXPECT_EQ(frameNode->GetGeometryNode()->GetFrameSize(), SizeF(300.0f, 350.0f))
        << frameNode->GetGeometryNode()->GetFrameRect().ToString();
    EXPECT_EQ(frameNode->GetGeometryNode()->GetFrameOffset(), OffsetF(0.0f, 0.0f));
    EXPECT_EQ(column->GetGeometryNode()->GetFrameSize(), SizeF(100.0f, 100.0f));
    EXPECT_EQ(column->GetGeometryNode()->GetFrameOffset(), OffsetF(100.0f, 0.0f))
        << column->GetGeometryNode()->GetFrameRect().ToString();
}

/**
 * @tc.name: IgnoreLayoutSafeArea002
 * @tc.desc: Test MeasureSelfByLayoutPolicy function
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, IgnoreLayoutSafeArea002, TestSize.Level0)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetMinPlatformVersion(PLATFORM_VERSION_10);
    RefPtr<FrameNode> column;
    auto frameNode = CreateLinearSplit(SplitType::COLUMN_SPLIT,
        [this, &column](LinearSplitModelNG model) { column = CreateColumn([this](ColumnModelNG model) {}); });
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(300.0f, DimensionUnit::PX), CalcLength(300.0f, DimensionUnit::PX)));
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
    childLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(100.0f, DimensionUnit::PX), CalcLength(100.0f, DimensionUnit::PX)));
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    frameNode->CreateLayoutTask();
    EXPECT_EQ(frameNode->GetGeometryNode()->GetFrameSize(), SizeF(300.0f, 300.0f))
        << frameNode->GetGeometryNode()->GetFrameRect().ToString();
    EXPECT_EQ(frameNode->GetGeometryNode()->GetFrameOffset(), OffsetF(0.0f, 0.0f));
    EXPECT_EQ(column->GetGeometryNode()->GetFrameSize(), SizeF(100.0f, 100.0f));
    EXPECT_EQ(column->GetGeometryNode()->GetFrameOffset(), OffsetF(0.0f, 100.0f))
        << column->GetGeometryNode()->GetFrameRect().ToString();
}

/**
 * @tc.name: RegisterResObj
 * @tc.desc: Test RegisterResObj of linear_split
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, RegisterResObj, TestSize.Level0)
{
    g_isConfigChangePerform = true;
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    NG::ColumnSplitDivider divider;
    LinearSplitModelNG::RegisterResObj(resObj, divider, "columnSplit.divider.startMargin");
    divider.ReloadResources();
    EXPECT_EQ(divider.resMap_.size(), 1);
    LinearSplitModelNG::RegisterResObj(resObj, divider, "columnSplit.divider.endMargin");
    divider.ReloadResources();
    g_isConfigChangePerform = false;
    EXPECT_EQ(divider.resMap_.size(), 2);
}

/**
 * @tc.name: IsRootSizeUnValidTest
 * @tc.desc: Test IsRootSizeUnValid() function
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, IsRootSizeUnValidTest, TestSize.Level0)
{
    auto frameNode = CreateLinearSplit(SplitType::ROW_SPLIT, [this](LinearSplitModelNG model) {});
    ASSERT_NE(frameNode, nullptr);
    LinearSplitLayoutAlgorithm algorithm(SplitType::ROW_SPLIT, {}, {}, false);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    context->rootWidth_ = 100;
    context->rootHeight_ = 100;
    /**
     * @tc.expected: rootSize is valid, so IsRootSizeUnvalid() returns false
     */
    EXPECT_FALSE(algorithm.IsRootSizeUnValid(AceType::RawPtr(frameNode)));
    context->rootWidth_ = 0;
    context->rootHeight_ = 0;
    /**
     * @tc.expected: rootSize is unvalid, so IsRootSizeUnvalid() returns true
     */
    EXPECT_TRUE(algorithm.IsRootSizeUnValid(AceType::RawPtr(frameNode)));
}

/**
 * @tc.name: IsDynamicComponentEnvTest
 * @tc.desc: Test IsDynamicComponentEnv() function
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, IsDynamicComponentEnvTest, TestSize.Level0)
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    LinearSplitLayoutAlgorithm algorithm(SplitType::ROW_SPLIT, {}, {}, false);
    container->SetIsDynamicRender(true);
    container->SetUIContentType(UIContentType::DYNAMIC_COMPONENT);
    /**
     * @tc.expected: linearsplit components is displayed in DC
     */
    EXPECT_TRUE(algorithm.IsDynamicComponentEnv());
    container->SetIsDynamicRender(false);
    container->SetUIContentType(UIContentType::NORMA);
    /**
     * @tc.expected: linearsplit components is not displayed in DC
     */
    EXPECT_FALSE(algorithm.IsDynamicComponentEnv());
}

/**
 * @tc.name: GetItemMinSizeTest001
 * @tc.desc: Test GetItemMinSize with null layoutProperty
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, GetItemMinSizeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create split and layoutWrapper
     */
    auto frameNode = CreateLinearSplit(SplitType::ROW_SPLIT, [](LinearSplitModelNG model) {});
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);

    LinearSplitLayoutAlgorithm algorithm(SplitType::ROW_SPLIT, {}, {}, false);

    /**
     * @tc.steps: step2. Create item wrapper with null layoutProperty
     * @tc.expected: GetItemMinSize returns theme default value
     */
    auto itemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto itemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    itemGeometryNode->Reset();
    
    auto minSize =
        algorithm.GetItemMinSize(itemFrameNode, AceType::RawPtr(frameNode));
    EXPECT_GT(minSize, 0.0f);
}

/**
 * @tc.name: GetItemMinSizeTest002
 * @tc.desc: Test GetItemMinSize with calcConstraint minSize
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, GetItemMinSizeTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create split and layoutWrapper
     */
    auto frameNode = CreateLinearSplit(SplitType::ROW_SPLIT, [](LinearSplitModelNG model) {});
    ASSERT_NE(frameNode, nullptr);

    LinearSplitLayoutAlgorithm algorithm(SplitType::ROW_SPLIT, {}, {}, false);

    /**
     * @tc.steps: step2. Create item wrapper with calcLayoutConstraint
     * @tc.expected: GetItemMinSize returns calc minSize
     */
    auto itemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto itemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    itemGeometryNode->Reset();
    auto itemLayoutProperty = itemFrameNode->GetLayoutProperty();
    ASSERT_NE(itemLayoutProperty, nullptr);

    // Set calc min size using UpdateCalcMinSize
    itemLayoutProperty->UpdateCalcMinSize(CalcSize(CalcLength(100.0f), CalcLength(50.0f)));

    // Also set layout constraint minSize
    LayoutConstraintF layoutConstraint;
    layoutConstraint.minSize = SizeF(100.0f, 50.0f);
    itemLayoutProperty->UpdateLayoutConstraint(layoutConstraint);

    RefPtr<LayoutWrapperNode> itemLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(itemFrameNode, itemGeometryNode, itemLayoutProperty);

    auto minSize = algorithm.GetItemMinSize(itemLayoutWrapper, AceType::RawPtr(frameNode));
    EXPECT_EQ(minSize, 100.0f); // ROW_SPLIT uses Width()
}

/**
 * @tc.name: GetItemMinSizeTest003
 * @tc.desc: Test GetItemMinSize with COLUMN_SPLIT
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, GetItemMinSizeTest003, TestSize.Level1)
{
    auto frameNode = CreateLinearSplit(SplitType::COLUMN_SPLIT, [](LinearSplitModelNG model) {});
    ASSERT_NE(frameNode, nullptr);

    LinearSplitLayoutAlgorithm algorithm(SplitType::COLUMN_SPLIT, {}, {}, false);

    auto itemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto itemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    itemGeometryNode->Reset();
    auto itemLayoutProperty = itemFrameNode->GetLayoutProperty();
    ASSERT_NE(itemLayoutProperty, nullptr);

    // Set calc min size using UpdateCalcMinSize
    itemLayoutProperty->UpdateCalcMinSize(CalcSize(CalcLength(100.0f), CalcLength(50.0f)));

    // Also set layout constraint minSize
    LayoutConstraintF layoutConstraint;
    layoutConstraint.minSize = SizeF(100.0f, 50.0f);
    itemLayoutProperty->UpdateLayoutConstraint(layoutConstraint);

    RefPtr<LayoutWrapperNode> itemLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(itemFrameNode, itemGeometryNode, itemLayoutProperty);

    auto minSize = algorithm.GetItemMinSize(itemLayoutWrapper, AceType::RawPtr(frameNode));
    EXPECT_EQ(minSize, 50.0f); // COLUMN_SPLIT uses Height()
}

/**
 * @tc.name: GetDividerMarginTest001
 * @tc.desc: Test GetDividerMargin with null layoutProperty
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, GetDividerMarginTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create wrapper with null layoutProperty
     * @tc.expected: GetDividerMargin returns empty pair
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->Reset();
    RefPtr<LayoutWrapperNode> layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, nullptr);

    LinearSplitLayoutAlgorithm algorithm(SplitType::ROW_SPLIT, {}, {}, false);
    auto [startMargin, endMargin] = algorithm.GetDividerMargin(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(startMargin, 0.0f);
    EXPECT_EQ(endMargin, 0.0f);
}

/**
 * @tc.name: GetDividerMarginTest002
 * @tc.desc: Test GetDividerMargin without divider set
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, GetDividerMarginTest002, TestSize.Level1)
{
    auto frameNode = CreateLinearSplit(SplitType::COLUMN_SPLIT, [](LinearSplitModelNG model) {});
    ASSERT_NE(frameNode, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->Reset();
    frameNode->SetGeometryNode(geometryNode);
    auto linearSplitLayoutProperty = frameNode->GetLayoutProperty<LinearSplitLayoutProperty>();
    ASSERT_NE(linearSplitLayoutProperty, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper
        = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, linearSplitLayoutProperty);

    LinearSplitLayoutAlgorithm algorithm(SplitType::COLUMN_SPLIT, {}, {}, false);

    // HasDivider() returns false, should use default values
    auto [startMargin, endMargin] = algorithm.GetDividerMargin(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(startMargin, 0.0f);
    EXPECT_EQ(endMargin, 0.0f);
}

/**
 * @tc.name: GetDividerMarginTest003
 * @tc.desc: Test GetDividerMargin with custom divider
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, GetDividerMarginTest003, TestSize.Level1)
{
    LinearSplitModelNG model;
    model.Create(SplitType::COLUMN_SPLIT);

    ColumnSplitDivider divider;
    divider.startMargin = 10.0_vp;
    divider.endMargin = 20.0_vp;
    model.SetDivider(SplitType::COLUMN_SPLIT, divider);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->Reset();
    frameNode->SetGeometryNode(geometryNode);
    auto linearSplitLayoutProperty = frameNode->GetLayoutProperty<LinearSplitLayoutProperty>();
    ASSERT_NE(linearSplitLayoutProperty, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper
        = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, linearSplitLayoutProperty);

    LinearSplitLayoutAlgorithm algorithm(SplitType::COLUMN_SPLIT, {}, {}, false);

    auto [startMargin, endMargin] = algorithm.GetDividerMargin(AceType::RawPtr(layoutWrapper));
    EXPECT_FLOAT_EQ(startMargin, 10.0f);
    EXPECT_FLOAT_EQ(endMargin, 20.0f);
}

/**
 * @tc.name: GetLinearSplitChildMinSizeTest002
 * @tc.desc: Test GetLinearSplitChildMinSize with null context
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, GetLinearSplitChildMinSizeTest002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->Reset();
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper
        = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);

    // Mock context is null at this point
    LinearSplitLayoutAlgorithm algorithm(SplitType::ROW_SPLIT, {}, {}, false);
    auto minSize = algorithm.GetLinearSplitChildMinSize(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(minSize, 20.0f); // DEFAULT_MIN_CHILD_SIZE when pipeline is null
}

/**
 * @tc.name: UpdateChildPositionWidthIgnoreLayoutSafeAreaTest001
 * @tc.desc: Test UpdateChildPositionWidthIgnoreLayoutSafeArea with null childNode
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, UpdateChildPositionWidthIgnoreLayoutSafeAreaTest001, TestSize.Level1)
{
    auto frameNode = CreateLinearSplit(SplitType::ROW_SPLIT, [](LinearSplitModelNG model) {});
    ASSERT_NE(frameNode, nullptr);

    auto itemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto itemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    itemGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> itemLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(itemFrameNode, itemGeometryNode, nullptr);

    LinearSplitLayoutAlgorithm algorithm(SplitType::ROW_SPLIT, {}, {}, false);

    // Should not crash with null layoutProperty
    algorithm.UpdateChildPositionWidthIgnoreLayoutSafeArea(itemLayoutWrapper, OffsetF(10.0f, 20.0f));
}

/**
 * @tc.name: UpdateChildPositionWidthIgnoreLayoutSafeAreaTest002
 * @tc.desc: Test UpdateChildPositionWidthIgnoreLayoutSafeArea with invalid opts
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, UpdateChildPositionWidthIgnoreLayoutSafeAreaTest002, TestSize.Level1)
{
    auto frameNode = CreateLinearSplit(SplitType::ROW_SPLIT, [](LinearSplitModelNG model) {});
    ASSERT_NE(frameNode, nullptr);

    auto itemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto itemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    itemGeometryNode->Reset();
    auto itemLayoutProperty = itemFrameNode->GetLayoutProperty();
    ASSERT_NE(itemLayoutProperty, nullptr);

    // IsIgnoreOptsValid() should return false by default
    RefPtr<LayoutWrapperNode> itemLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(itemFrameNode, itemGeometryNode, itemLayoutProperty);

    LinearSplitLayoutAlgorithm algorithm(SplitType::ROW_SPLIT, {}, {}, false);

    OffsetF originOffset(10.0f, 20.0f);
    itemGeometryNode->SetMarginFrameOffset(originOffset);

    algorithm.UpdateChildPositionWidthIgnoreLayoutSafeArea(itemLayoutWrapper, originOffset);

    // Offset should remain unchanged when IsIgnoreOptsValid() is false
    EXPECT_EQ(itemGeometryNode->GetMarginFrameOffset(), originOffset);
}

/**
 * @tc.name: IsChildMatchParentTest001
 * @tc.desc: Test IsChildMatchParent with null child
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, IsChildMatchParentTest001, TestSize.Level1)
{
    LinearSplitLayoutAlgorithm algorithm(SplitType::ROW_SPLIT, {}, {}, false);

    RefPtr<LayoutWrapper> child = nullptr;
    EXPECT_FALSE(algorithm.IsChildMatchParent(child));
}

/**
 * @tc.name: IsChildMatchParentTest002
 * @tc.desc: Test IsChildMatchParent with null layoutProperty
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, IsChildMatchParentTest002, TestSize.Level1)
{
    auto childFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    childGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(childFrameNode, childGeometryNode, nullptr);

    LinearSplitLayoutAlgorithm algorithm(SplitType::ROW_SPLIT, {}, {}, false);
    EXPECT_FALSE(algorithm.IsChildMatchParent(childLayoutWrapper));
}

/**
 * @tc.name: DisableLayoutPolicyTest001
 * @tc.desc: Test DisableLayoutPolicy with null child
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, DisableLayoutPolicyTest001, TestSize.Level1)
{
    LinearSplitLayoutAlgorithm algorithm(SplitType::ROW_SPLIT, {}, {}, false);

    // Should not crash with null child
    algorithm.DisableLayoutPolicy(nullptr);
}

/**
 * @tc.name: DisableLayoutPolicyTest002
 * @tc.desc: Test DisableLayoutPolicy with ROW_SPLIT
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, DisableLayoutPolicyTest002, TestSize.Level1)
{
    auto frameNode = CreateLinearSplit(SplitType::ROW_SPLIT, [](LinearSplitModelNG model) {});
    ASSERT_NE(frameNode, nullptr);

    auto childFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    childGeometryNode->Reset();
    auto childLayoutProperty = childFrameNode->GetLayoutProperty();
    ASSERT_NE(childLayoutProperty, nullptr);

    // Set widthLayoutPolicy
    childLayoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);

    RefPtr<LayoutWrapperNode> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(childFrameNode, childGeometryNode, childLayoutProperty);

    LinearSplitLayoutAlgorithm algorithm(SplitType::ROW_SPLIT, {}, {}, false);
    algorithm.DisableLayoutPolicy(childLayoutWrapper);

    // widthLayoutPolicy should be reset to NO_MATCH
    auto layoutPolicy = childLayoutProperty->GetLayoutPolicyProperty();
    ASSERT_TRUE(layoutPolicy.has_value());
    EXPECT_EQ(layoutPolicy.value().widthLayoutPolicy_, LayoutCalPolicy::NO_MATCH);
}

/**
 * @tc.name: DisableLayoutPolicyTest003
 * @tc.desc: Test DisableLayoutPolicy with COLUMN_SPLIT
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, DisableLayoutPolicyTest003, TestSize.Level1)
{
    auto frameNode = CreateLinearSplit(SplitType::COLUMN_SPLIT, [](LinearSplitModelNG model) {});
    ASSERT_NE(frameNode, nullptr);

    auto childFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    childGeometryNode->Reset();
    auto childLayoutProperty = childFrameNode->GetLayoutProperty();
    ASSERT_NE(childLayoutProperty, nullptr);

    // Set heightLayoutPolicy
    childLayoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);

    RefPtr<LayoutWrapperNode> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(childFrameNode, childGeometryNode, childLayoutProperty);

    LinearSplitLayoutAlgorithm algorithm(SplitType::COLUMN_SPLIT, {}, {}, false);
    algorithm.DisableLayoutPolicy(childLayoutWrapper);

    // heightLayoutPolicy should be reset to NO_MATCH
    auto layoutPolicy = childLayoutProperty->GetLayoutPolicyProperty();
    ASSERT_TRUE(layoutPolicy.has_value());
    EXPECT_EQ(layoutPolicy.value().heightLayoutPolicy_, LayoutCalPolicy::NO_MATCH);
}

/**
 * @tc.name: ColumnSplitChildConstrainTest001
 * @tc.desc: Test ColumnSplitChildConstrain with index out of bounds
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, ColumnSplitChildConstrainTest001, TestSize.Level1)
{
    auto frameNode = CreateLinearSplit(SplitType::COLUMN_SPLIT, [](LinearSplitModelNG model) {});
    ASSERT_NE(frameNode, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->Reset();
    frameNode->SetGeometryNode(geometryNode);
    auto linearSplitLayoutProperty = frameNode->GetLayoutProperty<LinearSplitLayoutProperty>();
    ASSERT_NE(linearSplitLayoutProperty, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper
        = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, linearSplitLayoutProperty);

    auto itemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto itemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    itemGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> itemLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(itemFrameNode, itemGeometryNode, itemFrameNode->GetLayoutProperty());

    LinearSplitLayoutAlgorithm algorithm(SplitType::COLUMN_SPLIT, {}, {}, false);
    algorithm.visibleChildCount_ = 0;

    // index >= childrenConstrains_.size(), should return early
    algorithm.ColumnSplitChildConstrain(AceType::RawPtr(layoutWrapper), itemLayoutWrapper, 0);

    // Should not crash and childrenConstrains_ should still be empty
    EXPECT_TRUE(algorithm.childrenConstrains_.empty());
}

/**
 * @tc.name: MeasureWithInvalidDragPosTest001
 * @tc.desc: Test Measure with invalid childrenDragPos size
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, MeasureWithInvalidDragPosTest001, TestSize.Level1)
{
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(PLATFORM_VERSION_10);

    auto frameNode = CreateLinearSplit(SplitType::COLUMN_SPLIT, [](LinearSplitModelNG model) {
        model.SetResizable(SplitType::COLUMN_SPLIT, true);
    });
    ASSERT_NE(frameNode, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->Reset();
    frameNode->SetGeometryNode(geometryNode);
    auto linearSplitLayoutProperty = frameNode->GetLayoutProperty<LinearSplitLayoutProperty>();
    ASSERT_NE(linearSplitLayoutProperty, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper
        = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, linearSplitLayoutProperty);

    // Set invalid childrenDragPos size (size != visibleChildCount_ + 1)
    std::vector<float> invalidDragPos = { 0.0f, 100.0f }; // Only 2 elements
    LinearSplitLayoutAlgorithm algorithm(SplitType::COLUMN_SPLIT, {}, invalidDragPos, false);

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    // Add children so visibleChildCount_ is 2, making childrenDragPos_ size (2) != visibleChildCount_ + 1 (3)
    for (int32_t i = 0; i < 2; i++) {
        auto itemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, i + 1, AceType::MakeRefPtr<Pattern>());
        frameNode->AddChild(itemFrameNode);
    }

    // Measure should clear invalid childrenDragPos_
    algorithm.Measure(AceType::RawPtr(layoutWrapper));
}

/**
 * @tc.name: LayoutWithEmptyChildrenTest001
 * @tc.desc: Test Layout with empty children and invalid root size in DC
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, LayoutWithEmptyChildrenTest001, TestSize.Level1)
{
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(PLATFORM_VERSION_10);

    auto frameNode = CreateLinearSplit(SplitType::ROW_SPLIT, [](LinearSplitModelNG model) {
        model.SetResizable(SplitType::ROW_SPLIT, true);
    });
    ASSERT_NE(frameNode, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->Reset();
    frameNode->SetGeometryNode(geometryNode);
    auto linearSplitLayoutProperty = frameNode->GetLayoutProperty<LinearSplitLayoutProperty>();
    ASSERT_NE(linearSplitLayoutProperty, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper
        = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, linearSplitLayoutProperty);

    // Set root size to 0
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    context->rootWidth_ = 0.0f;
    context->rootHeight_ = 0.0f;

    // Set dynamic component environment
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    container->SetIsDynamicRender(true);
    container->SetUIContentType(UIContentType::DYNAMIC_COMPONENT);

    std::vector<float> dragSplitOffset;
    std::vector<float> childrenDragPos;
    LinearSplitLayoutAlgorithm algorithm(SplitType::ROW_SPLIT, dragSplitOffset, childrenDragPos, false);

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    // Layout should return early when IsRootSizeUnValid() && IsDynamicComponentEnv()
    algorithm.Layout(AceType::RawPtr(layoutWrapper));

    // Reset environment
    container->SetIsDynamicRender(false);
    container->SetUIContentType(UIContentType::NORMA);
}

/**
 * @tc.name: MeasureWithMatchParentTest001
 * @tc.desc: Test Measure with MATCH_PARENT measure type
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, MeasureWithMatchParentTest001, TestSize.Level1)
{
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(PLATFORM_VERSION_10);

    auto frameNode = CreateLinearSplit(SplitType::ROW_SPLIT, [](LinearSplitModelNG model) {});
    ASSERT_NE(frameNode, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->Reset();
    frameNode->SetGeometryNode(geometryNode);
    auto linearSplitLayoutProperty = frameNode->GetLayoutProperty<LinearSplitLayoutProperty>();
    ASSERT_NE(linearSplitLayoutProperty, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper
        = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, linearSplitLayoutProperty);

    // Set measure type to MATCH_PARENT
    linearSplitLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.parentIdealSize = OptionalSizeF(RK356_WIDTH, RK356_HEIGHT);
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    std::vector<float> dragSplitOffset;
    std::vector<float> childrenDragPos;
    LinearSplitLayoutAlgorithm algorithm(SplitType::ROW_SPLIT, dragSplitOffset, childrenDragPos, false);

    // Measure should use parentIdealSize
    algorithm.Measure(AceType::RawPtr(layoutWrapper));
}

/**
 * @tc.name: MeasureBeforeAPI10WithMatchParentTest001
 * @tc.desc: Test MeasureBeforeAPI10 with MATCH_PARENT measure type
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, MeasureBeforeAPI10WithMatchParentTest001, TestSize.Level1)
{
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(PLATFORM_VERSION_9);

    auto frameNode = CreateLinearSplit(SplitType::COLUMN_SPLIT, [](LinearSplitModelNG model) {});
    ASSERT_NE(frameNode, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->Reset();
    frameNode->SetGeometryNode(geometryNode);
    auto linearSplitLayoutProperty = frameNode->GetLayoutProperty<LinearSplitLayoutProperty>();
    ASSERT_NE(linearSplitLayoutProperty, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper
        = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, linearSplitLayoutProperty);

    // Set measure type to MATCH_PARENT
    linearSplitLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.parentIdealSize = OptionalSizeF(RK356_WIDTH, RK356_HEIGHT);
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    std::vector<float> dragSplitOffset;
    std::vector<float> childrenDragPos;
    LinearSplitLayoutAlgorithm algorithm(SplitType::COLUMN_SPLIT, dragSplitOffset, childrenDragPos, false);

    // MeasureBeforeAPI10 should use parentIdealSize
    algorithm.MeasureBeforeAPI10(AceType::RawPtr(layoutWrapper));
}

/**
 * @tc.name: MeasureWithSelfIdealSizeTest001
 * @tc.desc: Test Measure with valid selfIdealSize
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, MeasureWithSelfIdealSizeTest001, TestSize.Level1)
{
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(PLATFORM_VERSION_10);

    auto frameNode = CreateLinearSplit(SplitType::ROW_SPLIT, [](LinearSplitModelNG model) {});
    ASSERT_NE(frameNode, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->Reset();
    frameNode->SetGeometryNode(geometryNode);
    auto linearSplitLayoutProperty = frameNode->GetLayoutProperty<LinearSplitLayoutProperty>();
    ASSERT_NE(linearSplitLayoutProperty, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper
        = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, linearSplitLayoutProperty);

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.selfIdealSize = OptionalSizeF(RK356_WIDTH, COLUMN_HEIGHT);
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    std::vector<float> dragSplitOffset;
    std::vector<float> childrenDragPos;
    LinearSplitLayoutAlgorithm algorithm(SplitType::ROW_SPLIT, dragSplitOffset, childrenDragPos, false);

    // Measure should use selfIdealSize when IsValid() returns true
    algorithm.Measure(AceType::RawPtr(layoutWrapper));
    auto frameSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    EXPECT_EQ(frameSize.Width(), RK356_WIDTH);
    EXPECT_EQ(frameSize.Height(), COLUMN_HEIGHT);
}

/**
 * @tc.name: LayoutWithGoneChildTest001
 * @tc.desc: Test Layout with GONE visibility child
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, LayoutWithGoneChildTest001, TestSize.Level1)
{
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(PLATFORM_VERSION_10);

    auto frameNode = CreateLinearSplit(SplitType::COLUMN_SPLIT, [](LinearSplitModelNG model) {
        model.SetResizable(SplitType::COLUMN_SPLIT, true);
    });
    ASSERT_NE(frameNode, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->Reset();
    frameNode->SetGeometryNode(geometryNode);
    auto linearSplitLayoutProperty = frameNode->GetLayoutProperty<LinearSplitLayoutProperty>();
    ASSERT_NE(linearSplitLayoutProperty, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, linearSplitLayoutProperty);

    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(RK356_WIDTH), CalcLength(RK356_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);

    // Add 3 children, make middle one GONE
    for (int32_t i = 0; i < 3; i++) {
        auto itemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, i + 1, AceType::MakeRefPtr<Pattern>());
        RefPtr<GeometryNode> itemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeometryNode->Reset();
        RefPtr<LayoutWrapperNode> itemLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(itemFrameNode, itemGeometryNode, itemFrameNode->GetLayoutProperty());
        itemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
        itemLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(RK356_WIDTH), CalcLength(SMALL_ITEM_HEIGHT)));
        if (i == 1) {
            // Make middle child GONE
            itemLayoutWrapper->GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);
        }
        auto boxLayoutAlgorithm = itemFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
        itemLayoutWrapper->SetLayoutAlgorithm(
            AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
        frameNode->AddChild(itemFrameNode);
        layoutWrapper->AppendChild(itemLayoutWrapper);
    }

    std::vector<float> dragSplitOffset;
    std::vector<float> childrenDragPos;
    LinearSplitLayoutAlgorithm algorithm(SplitType::COLUMN_SPLIT, dragSplitOffset, childrenDragPos, false);

    algorithm.Measure(AceType::RawPtr(layoutWrapper));
    algorithm.Layout(AceType::RawPtr(layoutWrapper));

    // visibleChildCount_ should be 2 (GONE child excluded)
    EXPECT_EQ(algorithm.visibleChildCount_, 2);
    // splitRects should have only 1 rect (between 2 visible children)
    EXPECT_EQ(algorithm.GetSplitRects().size(), 1u);
}

/**
 * @tc.name: GetChildConstrainWithEmptyDragPosTest001
 * @tc.desc: Test GetChildConstrain with empty childrenDragPos
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitTestNg, GetChildConstrainWithEmptyDragPosTest001, TestSize.Level1)
{
    auto frameNode = CreateLinearSplit(SplitType::ROW_SPLIT, [](LinearSplitModelNG model) {});
    ASSERT_NE(frameNode, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->Reset();
    frameNode->SetGeometryNode(geometryNode);
    auto linearSplitLayoutProperty = frameNode->GetLayoutProperty<LinearSplitLayoutProperty>();
    ASSERT_NE(linearSplitLayoutProperty, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper
        = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, linearSplitLayoutProperty);

    std::vector<float> dragSplitOffset;
    std::vector<float> childrenDragPos; // Empty
    LinearSplitLayoutAlgorithm algorithm(SplitType::ROW_SPLIT, dragSplitOffset, childrenDragPos, false);
    algorithm.visibleChildCount_ = 2;

    LayoutConstraintF childConstrain;
    childConstrain.maxSize = SizeF(1000.0f, 1000.0f);

    // When childrenDragPos is empty, should return original constrain
    auto result = algorithm.GetChildConstrain(AceType::RawPtr(layoutWrapper), childConstrain, 0);
    EXPECT_EQ(result.maxSize, childConstrain.maxSize);
}
} // namespace OHOS::Ace::NG