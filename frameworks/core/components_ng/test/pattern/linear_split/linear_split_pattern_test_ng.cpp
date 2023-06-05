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
#include "core/components_ng/pattern/linear_split/linear_split_model.h"
#include "core/components_ng/pattern/linear_split/linear_split_pattern.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension WIDTH = 500.0_vp;
constexpr Dimension HEIGHT = 500.0_vp;
constexpr std::size_t DEFAULT_DRAG_INDEX = -1;
} // namespace

class LinearSplitPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};
void LinearSplitPatternTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void LinearSplitPatternTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}
void LinearSplitPatternTestNg::SetUp() {}

void LinearSplitPatternTestNg::TearDown() {}

/**
 * @tc.name: LinearSplitCreatorTest001
 * @tc.desc: Test all the property of split
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitPatternTestNg, LinearSplitCreatorTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create split and initialize related properties.
     */
    LinearSplitModelNG model;
    model.Create(SplitType::COLUMN_SPLIT);
    model.SetResizeable(SplitType::COLUMN_SPLIT, true);

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
    EXPECT_EQ(renderProperty->GetResizeableValue(), true);
}

/**
 * @tc.name: LinearSplitPatternTest001
 * @tc.desc: Test linearSplit pattern OnDirtyLayoutWrapperSwap function.
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitPatternTestNg, LinearSplitPatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create split and initialize related properties.
     */
    LinearSplitModelNG model;
    model.Create(SplitType::COLUMN_SPLIT);
    model.SetResizeable(SplitType::COLUMN_SPLIT, true);

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
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, linearSplitLayoutProperty);
    EXPECT_NE(layoutWrapper, nullptr);
    layoutWrapper->skipMeasureContent_ = false;
    std::vector<float> dragSplitOffset;
    RefPtr<LinearSplitLayoutAlgorithm> linearLayoutAlgorithm =
        AceType::MakeRefPtr<LinearSplitLayoutAlgorithm>(SplitType::COLUMN_SPLIT, dragSplitOffset, false);

    /**
     * @tc.steps: step3. call linearSplitPattern OnDirtyLayoutWrapperSwap function, compare result.
     * @tc.expected: OnDirtyLayoutWrapperSwap success and result correct.
     */

    /**
     *     case 1: LayoutWrapper::SkipMeasureContent = false , skipMeasure = true;
     */
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(linearLayoutAlgorithm, true);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    bool firstCase = linearSPlitPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, false);
    EXPECT_FALSE(firstCase);

    /**
     *     case 2: LayoutWrapper::SkipMeasureContent = false , skipMeasure = false;
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
HWTEST_F(LinearSplitPatternTestNg, LinearSplitPatternTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create split and initialize related properties.
     */
    LinearSplitModelNG model;
    model.Create(SplitType::COLUMN_SPLIT);
    model.SetResizeable(SplitType::COLUMN_SPLIT, true);

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
    EXPECT_TRUE(linearSPlitPattern->resizeable_);
    EXPECT_NE(linearSPlitPattern->panEvent_, nullptr);
    EXPECT_NE(linearSPlitPattern->mouseEvent_, nullptr);
}

/**
 * @tc.name: LinearSplitPatternTest003
 * @tc.desc: Test linerSplit pattern OnDirtyLayoutWrapperSwap function.
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitPatternTestNg, LinearSplitPatternTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create split and initialize related properties.
     */
    LinearSplitModelNG model;
    model.Create(SplitType::COLUMN_SPLIT);
    model.SetResizeable(SplitType::COLUMN_SPLIT, true);

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
    RefPtr<LayoutWrapper> linearLayoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    linearSplitPattern->OnDirtyLayoutWrapperSwap(linearLayoutWrapper, true, true);
    EXPECT_EQ(linearSplitPattern->splitLength_, 0.0f);
    EXPECT_EQ(linearSplitPattern->isOverParent_, false);
}
/**
 * @tc.name: LinearSplitPatternTest004
 * @tc.desc: Test linerSplit pattern HandlePanEvent  when resizeable is false.
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitPatternTestNg, LinearSplitPatternTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create split and initialize related properties.
     */
    LinearSplitModelNG model;
    model.Create(SplitType::COLUMN_SPLIT);
    model.SetResizeable(SplitType::COLUMN_SPLIT, false);

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
}
/**
 * @tc.name: LinearSplitPatternTest005
 * @tc.desc: Test linerSplit pattern HandlePanEvent  when resizeable is true.
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitPatternTestNg, LinearSplitPatternTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create split and initialize related properties.
     */
    LinearSplitModelNG model;
    model.Create(SplitType::COLUMN_SPLIT);
    model.SetResizeable(SplitType::COLUMN_SPLIT, true);

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
HWTEST_F(LinearSplitPatternTestNg, LinearSplitPatternTest006, TestSize.Level1)
{
    std::vector<SplitType> splitType = { SplitType::COLUMN_SPLIT, SplitType::ROW_SPLIT };
    for (int turn = 0; turn < splitType.size(); turn++) {
        /**
         * @tc.steps: step1. Create split and initialize related properties.
         */
        LinearSplitModelNG model;
        model.Create(splitType[turn]);
        model.SetResizeable(splitType[turn], true);

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
        LayoutWrapper* layoutWrapper = new LayoutWrapper(frameNode, geometryNode, linearSplitLayoutProperty);
        ASSERT_NE(layoutWrapper, nullptr);
        std::vector<float> dragSplitOffset = { 0.0f, 2.0f };
        RefPtr<LinearSplitLayoutAlgorithm> linearLayoutAlgorithm =
            AceType::MakeRefPtr<LinearSplitLayoutAlgorithm>(splitType[turn], dragSplitOffset, false);
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
} // namespace OHOS::Ace::NG