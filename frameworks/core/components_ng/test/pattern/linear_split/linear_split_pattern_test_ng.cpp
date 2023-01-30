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
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/linear_split/linear_split_model.h"
#include "core/components_ng/pattern/linear_split/linear_split_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension WIDTH = 500.0_vp;
constexpr Dimension HEIGHT = 500.0_vp;
} // namespace

class LinearSplitPatternTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
};

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
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. Confirm that the properties are correct.
     */
    auto renderProperty = frameNode->GetLayoutProperty<LinearSplitLayoutProperty>();
    EXPECT_NE(renderProperty, nullptr);
    EXPECT_EQ(renderProperty->GetResizeableValue(), true);
}

/**
 * @tc.name: LinearSplitPatternTest001
 * @tc.desc: Test lineatSplit pattern OnDirtyLayoutWrapperSwap function.
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
    EXPECT_NE(frameNode, nullptr);
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
     * @tc.expected: step3. OnDirtyLayoutWrapperSwap success and result correct.
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
 * @tc.desc: Test lineatSplit pattern OnModifyDone function.
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
     */
    linearSPlitPattern->OnModifyDone();
    EXPECT_TRUE(linearSPlitPattern->resizeable_);
    EXPECT_NE(linearSPlitPattern->panEvent_, nullptr);
    EXPECT_NE(linearSPlitPattern->mouseEvent_, nullptr);
}
} // namespace OHOS::Ace::NG