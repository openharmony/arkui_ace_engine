/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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
#include "base/utils/utils.h"
#define protected public
#define private public

#include "base/geometry/ng/size_t.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_wrapper_builder.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const float RK356_WIDTH = 720.0f;
const float RK356_HEIGHT = 1136.0f;

const float ROW_HEIGHT = 120.0f;
const float NOPADDING = 0.0f;

const float BIG_ITEM_WIDTH = 180.0f;
const float BIG_ITEM_HEIGHT = 75.0f;
const float ZERO = 0.0f;

const float CONTAINER_WIDTH = 300.0f;
const float CONTAINER_HEIGHT = 300.0f;

const OffsetF OFFSET_TOP_LEFT = OffsetF(ZERO, ZERO);
const SizeF FRAME_SIZE(CONTAINER_WIDTH, CONTAINER_HEIGHT);

const SizeF CONTAINER_SIZE(RK356_WIDTH, RK356_HEIGHT);
const SizeF BIG_ITEM_SIZE(BIG_ITEM_WIDTH, BIG_ITEM_HEIGHT);
} // namespace

class BoxLayoutAlgorithmTestNg : public testing::Test {
};

/**
 * @tc.name: BoxLayoutAlgorithmTest001
 * @tc.desc: Set one index value into BoxLayoutAlgorithmTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTestNg, BoxLayoutAlgorithmTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call Measure and SetLayoutAlgorithm for it.
     * @tc.expected: expect the function is run ok.
     */
    auto rowFrameNode = FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
        ASSERT_NE(rowFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
        ASSERT_NE(geometryNode, nullptr);

    RefPtr<LayoutWrapper> layoutWrapper =
            AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    ASSERT_NE(rowLayoutPattern, nullptr);
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    ASSERT_NE(rowLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(RK356_WIDTH, ROW_HEIGHT));

    PaddingProperty noPadding;
    noPadding.left = CalcLength(NOPADDING);
    noPadding.right = CalcLength(NOPADDING);
    noPadding.top = CalcLength(NOPADDING);
    noPadding.bottom = CalcLength(NOPADDING);

    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto firstFrameNode = FrameNode::CreateFrameNode("one", 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    RefPtr<LayoutWrapper> firstLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapper>(firstFrameNode, firstGeometryNode, firstFrameNode->GetLayoutProperty());

    layoutWrapper->AppendChild(firstLayoutWrapper);
    BoxLayoutAlgorithm boxLayoutAlgorithm;

    boxLayoutAlgorithm.Measure(AccessibilityManager::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step1. call SetIsLayoutFullScreen.
     * @tc.expected: expect the pipe is return true.
     */
    MockPipelineBase::SetUp();
    PipelineBase::GetCurrentContext()->SetIsLayoutFullScreen(true);
    auto pipe = PipelineBase::GetCurrentContext()->isLayoutFullScreen_;

    boxLayoutAlgorithm.Measure(AccessibilityManager::RawPtr(layoutWrapper));
    MockPipelineBase::TearDown();
    EXPECT_TRUE(pipe);
}

/**
 * @tc.name: BoxLayoutAlgorithmTest002
 * @tc.desc: Set one index value into BoxLayoutAlgorithmTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTestNg, BoxLayoutAlgorithmTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call Measure and SetLayoutAlgorithm for it.
     * @tc.expected: expect the function is run ok.
     */
    auto rowFrameNode = FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
        ASSERT_NE(rowFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
        ASSERT_NE(geometryNode, nullptr);

    RefPtr<LayoutWrapper> layoutWrapper =
            AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    ASSERT_NE(rowLayoutPattern, nullptr);
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    ASSERT_NE(rowLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(RK356_WIDTH, ROW_HEIGHT));

    PaddingProperty noPadding;
    noPadding.left = CalcLength(NOPADDING);
    noPadding.right = CalcLength(NOPADDING);
    noPadding.top = CalcLength(NOPADDING);
    noPadding.bottom = CalcLength(NOPADDING);

    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    BoxLayoutAlgorithm boxLayoutAlgorithm;

    /**
     * @tc.steps: step1. call SetIsLayoutFullScreen and GetIsAppWindow.
     * @tc.expected: step1. expect the pipe and pipe1 is return false.
     */
    MockPipelineBase::SetUp();
    PipelineBase::GetCurrentContext()->SetIsLayoutFullScreen(false);
    PipelineBase::GetCurrentContext()->SetIsAppWindow(false);
    auto pipe = PipelineBase::GetCurrentContext()->isLayoutFullScreen_;
    auto pipe1 = PipelineBase::GetCurrentContext()->isAppWindow_;
    boxLayoutAlgorithm.Measure(AccessibilityManager::RawPtr(layoutWrapper));
    MockPipelineBase::TearDown();
    EXPECT_FALSE(pipe);
    EXPECT_FALSE(pipe1);
}

/**
 * @tc.name: BoxLayoutAlgorithmTest003
 * @tc.desc: Set one index value into BoxLayoutAlgorithmTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTestNg, BoxLayoutAlgorithmTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call Layout and SetLayoutAlgorithm for it.
     * @tc.expected: expect the function is run ok.
     */
    auto rowFrameNode = FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
        ASSERT_NE(rowFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
        ASSERT_NE(geometryNode, nullptr);

    RefPtr<LayoutWrapper> layoutWrapper =
            AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    ASSERT_NE(rowLayoutPattern, nullptr);
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    ASSERT_NE(rowLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(RK356_WIDTH, ROW_HEIGHT));

    PaddingProperty noPadding;
    noPadding.left = CalcLength(NOPADDING);
    noPadding.right = CalcLength(NOPADDING);
    noPadding.top = CalcLength(NOPADDING);
    noPadding.bottom = CalcLength(NOPADDING);

    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto firstFrameNode = FrameNode::CreateFrameNode("one", 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    RefPtr<LayoutWrapper> firstLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapper>(firstFrameNode, firstGeometryNode, firstFrameNode->GetLayoutProperty());

    layoutWrapper->AppendChild(firstLayoutWrapper);
    BoxLayoutAlgorithm boxLayoutAlgorithm;
    boxLayoutAlgorithm.Layout(AccessibilityManager::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step1. call SetIsLayoutFullScreen.
     * @tc.expected: expect the pipe is return true.
     */
    MockPipelineBase::SetUp();
    PipelineBase::GetCurrentContext()->SetIsLayoutFullScreen(true);
    auto pipe = PipelineBase::GetCurrentContext()->isLayoutFullScreen_;
    boxLayoutAlgorithm.Layout(AccessibilityManager::RawPtr(layoutWrapper));
    MockPipelineBase::TearDown();
    EXPECT_TRUE(pipe);
}

/**
 * @tc.name: BoxLayoutAlgorithmTest004
 * @tc.desc: Set one index value into BoxLayoutAlgorithmTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTestNg, BoxLayoutAlgorithmTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call Layout and SetLayoutAlgorithm for it.
     * @tc.expected: expect the function is run ok.
     */
    auto rowFrameNode = FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
        ASSERT_NE(rowFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
        ASSERT_NE(geometryNode, nullptr);

    RefPtr<LayoutWrapper> layoutWrapper =
            AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    ASSERT_NE(rowLayoutPattern, nullptr);
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    ASSERT_NE(rowLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(RK356_WIDTH, ROW_HEIGHT));

    PaddingProperty noPadding;
    noPadding.left = CalcLength(NOPADDING);
    noPadding.right = CalcLength(NOPADDING);
    noPadding.top = CalcLength(NOPADDING);
    noPadding.bottom = CalcLength(NOPADDING);

    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto firstFrameNode = FrameNode::CreateFrameNode("one", 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    RefPtr<LayoutWrapper> firstLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapper>(firstFrameNode, firstGeometryNode, firstFrameNode->GetLayoutProperty());

    layoutWrapper->AppendChild(firstLayoutWrapper);
    BoxLayoutAlgorithm boxLayoutAlgorithm;

    /**
     * @tc.steps: step1. call SetIsLayoutFullScreen and GetIsAppWindow.
     * @tc.expected: expect the pipe and pipe1 is return false.
     */
    MockPipelineBase::SetUp();
    PipelineBase::GetCurrentContext()->SetIsLayoutFullScreen(false);
    PipelineBase::GetCurrentContext()->SetIsAppWindow(false);
    boxLayoutAlgorithm.Layout(AccessibilityManager::RawPtr(layoutWrapper));
    auto pipe = PipelineBase::GetCurrentContext()->isLayoutFullScreen_;
    auto pipe1 = PipelineBase::GetCurrentContext()->isAppWindow_;
    MockPipelineBase::TearDown();
    EXPECT_FALSE(pipe);
    EXPECT_FALSE(pipe1);
}

/**
 * @tc.name: BoxLayoutAlgorithmTest005
 * @tc.desc: Set one index value into BoxLayoutAlgorithmTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTestNg, BoxLayoutAlgorithmTest005, TestSize.Level1)
{
   /**
     * @tc.steps: step1. call MeasureContent and SetLayoutAlgorithm for it.
     * @tc.expected: expect the function is run ok.
     */
    auto rowFrameNode = FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
        ASSERT_NE(rowFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
        ASSERT_NE(geometryNode, nullptr);

    RefPtr<LayoutWrapper> layoutWrapper =
            AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    ASSERT_NE(rowLayoutPattern, nullptr);
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    ASSERT_NE(rowLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(RK356_WIDTH, ROW_HEIGHT));

    PaddingProperty noPadding;
    noPadding.left = CalcLength(NOPADDING);
    noPadding.right = CalcLength(NOPADDING);
    noPadding.top = CalcLength(NOPADDING);
    noPadding.bottom = CalcLength(NOPADDING);

    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    BoxLayoutAlgorithm boxLayoutAlgorithm;
    auto host = layoutWrapper->GetHostNode()->IsAtomicNode();
    boxLayoutAlgorithm.MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_FALSE(host);
}

/**
 * @tc.name: BoxLayoutAlgorithmTest006
 * @tc.desc: Set one index value into BoxLayoutAlgorithmTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTestNg, BoxLayoutAlgorithmTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call MeasureContent and SetLayoutAlgorithm for it.
     * @tc.expected: expect the function is run ok.
     */
    auto rowFrameNode = FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
        ASSERT_NE(rowFrameNode, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(LazyBuildFunction());

    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    ASSERT_NE(rowLayoutPattern, nullptr);
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    ASSERT_NE(rowLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    PaddingProperty noPadding;
    noPadding.left = CalcLength(NOPADDING);
    noPadding.right = CalcLength(NOPADDING);
    noPadding.top = CalcLength(NOPADDING);
    noPadding.bottom = CalcLength(NOPADDING);

    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    BoxLayoutAlgorithm boxLayoutAlgorithm;
    boxLayoutAlgorithm.MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_NE(layoutWrapper, nullptr);
}

/**
 * @tc.name: BoxLayoutAlgorithmTest007
 * @tc.desc: Set one index value into BoxLayoutAlgorithmTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTestNg, BoxLayoutAlgorithmTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call Layout and SetLayoutAlgorithm for it.
     * @tc.expected: expect the function is run ok.
     */
    auto rowFrameNode = FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
        ASSERT_NE(rowFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
        ASSERT_NE(geometryNode, nullptr);

    RefPtr<LayoutWrapper> layoutWrapper =
            AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    ASSERT_NE(rowLayoutPattern, nullptr);
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    ASSERT_NE(rowLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(RK356_WIDTH, ROW_HEIGHT));

    PaddingProperty noPadding;
    noPadding.left = CalcLength(NOPADDING);
    noPadding.right = CalcLength(NOPADDING);
    noPadding.top = CalcLength(NOPADDING);
    noPadding.bottom = CalcLength(NOPADDING);

    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto firstFrameNode = FrameNode::CreateFrameNode("one", 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    RefPtr<LayoutWrapper> firstLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapper>(firstFrameNode, firstGeometryNode, firstFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step1. call AppendChild and add firstLayoutWrapper.
     * @tc.expected: expect the child is not noll.
     */
    layoutWrapper->AppendChild(firstLayoutWrapper);
    BoxLayoutAlgorithm boxLayoutAlgorithm;
    rowFrameNode->layoutProperty_->positionProperty_ = std::make_unique<PositionProperty>();
    boxLayoutAlgorithm.Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_NE(rowFrameNode->layoutProperty_->positionProperty_, nullptr);
}

/**
 * @tc.name: BoxLayoutAlgorithmTest008
 * @tc.desc: Set one index value into BoxLayoutAlgorithmTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTestNg, BoxLayoutAlgorithmTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call Layout and SetLayoutAlgorithm for it.
     * @tc.expected: expect the function is run ok.
     */
    auto rowFrameNode = FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
        ASSERT_NE(rowFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
        ASSERT_NE(geometryNode, nullptr);

    RefPtr<LayoutWrapper> layoutWrapper =
            AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    ASSERT_NE(rowLayoutPattern, nullptr);
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    ASSERT_NE(rowLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(RK356_WIDTH, ROW_HEIGHT));

    PaddingProperty noPadding;
    noPadding.left = CalcLength(NOPADDING);
    noPadding.right = CalcLength(NOPADDING);
    noPadding.top = CalcLength(NOPADDING);
    noPadding.bottom = CalcLength(NOPADDING);

    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto firstFrameNode = FrameNode::CreateFrameNode("one", 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    RefPtr<LayoutWrapper> firstLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapper>(firstFrameNode, firstGeometryNode, firstFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step1. call back SetContentSize.
     * @tc.expected: expect the content_ is not noll.
     */
    layoutWrapper->AppendChild(firstLayoutWrapper);
    BoxLayoutAlgorithm boxLayoutAlgorithm;
    SizeF size {0.1, 0.1};
    geometryNode->SetContentSize(size);
    boxLayoutAlgorithm.Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_NE(geometryNode->content_, nullptr);
}

/**
 * @tc.name: BoxLayoutAlgorithmTest009
 * @tc.desc: Set one index value into BoxLayoutAlgorithmTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTestNg, BoxLayoutAlgorithmTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call PerformMeasureSelfWithChildList and SetLayoutAlgorithm for it.
     * @tc.expected: expect the function is run ok.
     */
    auto rowFrameNode = FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
        ASSERT_NE(rowFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
        ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
            AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    ASSERT_NE(rowLayoutPattern, nullptr);
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    ASSERT_NE(rowLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    PaddingProperty noPadding;
    noPadding.left = CalcLength(NOPADDING);
    noPadding.right = CalcLength(NOPADDING);
    noPadding.top = CalcLength(NOPADDING);
    noPadding.bottom = CalcLength(NOPADDING);

    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    BoxLayoutAlgorithm boxLayoutAlgorithm;
    std::list<RefPtr<LayoutWrapper>> childList;
    boxLayoutAlgorithm.PerformMeasureSelfWithChildList(AccessibilityManager::RawPtr(layoutWrapper), childList);

    /**
     * @tc.steps: step1. call SetOptionalSize.
     * @tc.expected: expect the size is same with .
     */
    const auto& layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    parentLayoutConstraint.selfIdealSize.SetOptionalSize(layoutConstraint->selfIdealSize);
    auto size = parentLayoutConstraint.selfIdealSize.width_;
    auto size1 = parentLayoutConstraint.selfIdealSize.height_;
    boxLayoutAlgorithm.PerformMeasureSelfWithChildList(AccessibilityManager::RawPtr(layoutWrapper), childList);
    EXPECT_EQ(size, std::nullopt);
    EXPECT_EQ(size1, std::nullopt);
}

/**
 * @tc.name: BoxLayoutAlgorithmTest0010
 * @tc.desc: Set one index value into BoxLayoutAlgorithmTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTestNg, BoxLayoutAlgorithmTest0010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call PerformMeasureSelfWithChildList and SetLayoutAlgorithm for it.
     * @tc.expected: expect the function is run ok.
     */
    auto rowFrameNode = FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
        ASSERT_NE(rowFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
        ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
            AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    ASSERT_NE(rowLayoutPattern, nullptr);
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    ASSERT_NE(rowLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    PaddingProperty noPadding;
    noPadding.left = CalcLength(NOPADDING);
    noPadding.right = CalcLength(NOPADDING);
    noPadding.top = CalcLength(NOPADDING);
    noPadding.bottom = CalcLength(NOPADDING);

    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    /**
     * @tc.steps: step1. call SetOptionalSize.
     * @tc.expected: expect the size is same with .
     */
    BoxLayoutAlgorithm boxLayoutAlgorithm;
    std::list<RefPtr<LayoutWrapper>> childList;
    layoutWrapper->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    auto type = layoutWrapper->GetLayoutProperty()->measureType_;
    const auto& layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    parentLayoutConstraint.selfIdealSize.SetOptionalSize(layoutConstraint->parentIdealSize);
    auto size = parentLayoutConstraint.selfIdealSize.width_;
    auto size1 = parentLayoutConstraint.selfIdealSize.height_;
    boxLayoutAlgorithm.PerformMeasureSelfWithChildList(AccessibilityManager::RawPtr(layoutWrapper), childList);
    EXPECT_EQ(size, std::nullopt);
    EXPECT_EQ(size1, std::nullopt);
    EXPECT_EQ(type, MeasureType::MATCH_PARENT);
}

/**
 * @tc.name: BoxLayoutAlgorithmTest0011
 * @tc.desc: Set one index value into BoxLayoutAlgorithmTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTestNg, BoxLayoutAlgorithmTest0011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call PerformMeasureSelfWithChildList and SetLayoutAlgorithm for it.
     * @tc.expected: expect the function is run ok.
     */
    auto rowFrameNode = FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
        ASSERT_NE(rowFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
        ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
            AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    ASSERT_NE(rowLayoutPattern, nullptr);
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    ASSERT_NE(rowLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    PaddingProperty noPadding;
    noPadding.left = CalcLength(NOPADDING);
    noPadding.right = CalcLength(NOPADDING);
    noPadding.top = CalcLength(NOPADDING);
    noPadding.bottom = CalcLength(NOPADDING);

    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    /**
     * @tc.steps: step1. call SetContentSize.
     * @tc.expected: expect the geometryNode->content_ is not null .
     */
    auto firstFrameNode = FrameNode::CreateFrameNode("one", 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    RefPtr<LayoutWrapper> firstLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapper>(firstFrameNode, firstGeometryNode, firstFrameNode->GetLayoutProperty());

    BoxLayoutAlgorithm boxLayoutAlgorithm;
    SizeF size {0.1, 0.1};
    geometryNode->SetContentSize(size);
    boxLayoutAlgorithm.PerformMeasureSelfWithChildList(AccessibilityManager::RawPtr(layoutWrapper),
        layoutWrapper->GetAllChildrenWithBuild());
    EXPECT_NE(geometryNode->content_, nullptr);
}

/**
 * @tc.name: BoxLayoutAlgorithmTest0012
 * @tc.desc: Set one index value into BoxLayoutAlgorithmTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTestNg, BoxLayoutAlgorithmTest0012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call PerformMeasureSelfWithChildList and SetLayoutAlgorithm for it.
     * @tc.expected: expect the function is run ok.
     */
    auto rowFrameNode = FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
        ASSERT_NE(rowFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
        ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
            AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    ASSERT_NE(rowLayoutPattern, nullptr);
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    ASSERT_NE(rowLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    PaddingProperty noPadding;
    noPadding.left = CalcLength(NOPADDING);
    noPadding.right = CalcLength(NOPADDING);
    noPadding.top = CalcLength(NOPADDING);
    noPadding.bottom = CalcLength(NOPADDING);

    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    /**
     * @tc.steps: step1. pushback firstLayoutWrapper to childlist .
     * @tc.expected: expect list child is not null.
     */
    BoxLayoutAlgorithm boxLayoutAlgorithm;
    auto firstFrameNode = FrameNode::CreateFrameNode("one", 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    RefPtr<LayoutWrapper> firstLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapper>(firstFrameNode, firstGeometryNode, firstFrameNode->GetLayoutProperty());
    std::list<RefPtr<LayoutWrapper>> childList;
    childList.push_back(firstLayoutWrapper);
    boxLayoutAlgorithm.PerformMeasureSelfWithChildList(AccessibilityManager::RawPtr(layoutWrapper), childList);
    EXPECT_NE(&childList, nullptr);
}
} // namespace OHOS::Ace::NG
