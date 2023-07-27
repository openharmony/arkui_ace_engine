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
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/layout/layout_wrapper_builder.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/property/property.h"
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

RefPtr<LayoutWrapperNode> CreatlayoutWrapper()
{
    auto rowFrameNode = FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());
    return layoutWrapper;
}

RefPtr<LayoutWrapperNode> CreatChildlayoutWrapper()
{
    auto firstFrameNode = FrameNode::CreateFrameNode("one", 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstFrameNode, firstGeometryNode, firstFrameNode->GetLayoutProperty());
    return firstLayoutWrapper;
}
} // namespace

class BoxLayoutAlgorithmTestNg : public testing::Test {
public:
    static void SetUpTestCase()
    {
        MockPipelineBase::SetUp();
    }
    static void TearDownTestCase()
    {
        MockPipelineBase::TearDown();
    }
};

/**
 * @tc.name: BoxLayoutAlgorithmTest_Measure001
 * @tc.desc: Set one index value into BoxLayoutAlgorithmTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTestNg, BoxLayoutAlgorithmTest_Measure001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat a layoutwrapper and SetLayoutAlgorithm for it.
     */
    auto layoutWrapper = CreatlayoutWrapper();

    auto rowFrameNode = FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    ASSERT_NE(rowLayoutPattern, nullptr);
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    ASSERT_NE(rowLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    /**
     * @tc.steps: step2. layout parameter initialization.
     */
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(RK356_WIDTH, ROW_HEIGHT));
    PaddingProperty noPadding;
    noPadding.left = CalcLength(NOPADDING);
    noPadding.right = CalcLength(NOPADDING);
    noPadding.top = CalcLength(NOPADDING);
    noPadding.bottom = CalcLength(NOPADDING);

    /**
     * @tc.steps: step3. Perform element updates.
     */
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    /**
     * @tc.steps: step4. creat a childLayoutWrapper and add to layoutWrapper.
     */
    auto childLayoutWrapper = CreatChildlayoutWrapper();
    layoutWrapper->AppendChild(childLayoutWrapper);
    BoxLayoutAlgorithm boxLayoutAlgorithm;

    boxLayoutAlgorithm.Measure(AccessibilityManager::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step5. call SetIsLayoutFullScreen.
     * @tc.expected: expect the pipe is return true.
     */
    PipelineBase::GetCurrentContext()->SetIsLayoutFullScreen(true);
    auto pipe = PipelineContext::GetCurrentContext()->safeAreaManager_->isFullScreen_;
    boxLayoutAlgorithm.Measure(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_TRUE(pipe);
}

/**
 * @tc.name: BoxLayoutAlgorithmTest_Measure002
 * @tc.desc: Set one index value into BoxLayoutAlgorithmTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTestNg, BoxLayoutAlgorithmTest_Measure002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat a layoutwrapper and SetLayoutAlgorithm for it.
     */
    auto layoutWrapper = CreatlayoutWrapper();

    auto rowFrameNode = FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    ASSERT_NE(rowLayoutPattern, nullptr);
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    ASSERT_NE(rowLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    /**
     * @tc.steps: step2. layout parameter initialization.
     */
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(RK356_WIDTH, ROW_HEIGHT));
    PaddingProperty noPadding;
    noPadding.left = CalcLength(NOPADDING);
    noPadding.right = CalcLength(NOPADDING);
    noPadding.top = CalcLength(NOPADDING);
    noPadding.bottom = CalcLength(NOPADDING);

    /**
     * @tc.steps: step3. Perform element updates.
     */
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    BoxLayoutAlgorithm boxLayoutAlgorithm;

    /**
     * @tc.steps: step4. call SetIsLayoutFullScreen and SetIsAppWindow.
     * @tc.expected: expect the pipe and pipe1 is return false.
     */
    PipelineBase::GetCurrentContext()->SetIsLayoutFullScreen(false);
    PipelineBase::GetCurrentContext()->SetIsAppWindow(false);
    auto pipe = PipelineContext::GetCurrentContext()->safeAreaManager_->isFullScreen_;
    auto pipe1 = PipelineBase::GetCurrentContext()->isAppWindow_;
    boxLayoutAlgorithm.Measure(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_FALSE(pipe);
    EXPECT_FALSE(pipe1);
}

/**
 * @tc.name: BoxLayoutAlgorithmTest_Layout003
 * @tc.desc: Set one index value into BoxLayoutAlgorithmTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTestNg, BoxLayoutAlgorithmTest_Layout003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat a layoutwrapper and SetLayoutAlgorithm for it.
     */
    auto layoutWrapper = CreatlayoutWrapper();

    auto rowFrameNode = FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    ASSERT_NE(rowLayoutPattern, nullptr);
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    ASSERT_NE(rowLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    /**
     * @tc.steps: step2. layout parameter initialization.
     */
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(RK356_WIDTH, ROW_HEIGHT));
    PaddingProperty noPadding;
    noPadding.left = CalcLength(NOPADDING);
    noPadding.right = CalcLength(NOPADDING);
    noPadding.top = CalcLength(NOPADDING);
    noPadding.bottom = CalcLength(NOPADDING);

    /**
     * @tc.steps: step3. Perform element updates.
     */
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    /**
     * @tc.steps: step4. creat a childLayoutWrapper and add to layoutWrapper.
     */
    auto childLayoutWrapper = CreatChildlayoutWrapper();
    layoutWrapper->AppendChild(childLayoutWrapper);
    BoxLayoutAlgorithm boxLayoutAlgorithm;
    boxLayoutAlgorithm.Layout(AccessibilityManager::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step5. call SetIsLayoutFullScreen and SetIsAppWindow.
     * @tc.expected: expect the AppWindow and LayoutFullScreen is true.
     */
    PipelineBase::GetCurrentContext()->SetIsAppWindow(true);
    PipelineBase::GetCurrentContext()->SetIsLayoutFullScreen(true);
    auto LayoutFullScreen = PipelineContext::GetCurrentContext()->safeAreaManager_->isFullScreen_;
    auto AppWindow = PipelineBase::GetCurrentContext()->isAppWindow_;
    boxLayoutAlgorithm.PerformLayout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_TRUE(LayoutFullScreen);
    EXPECT_TRUE(AppWindow);
}

/**
 * @tc.name: BoxLayoutAlgorithmTest_Layout004
 * @tc.desc: Set one index value into BoxLayoutAlgorithmTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTestNg, BoxLayoutAlgorithmTest_Layout004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat a layoutwrapper and SetLayoutAlgorithm for it.
     */
    auto layoutWrapper = CreatlayoutWrapper();

    auto rowFrameNode = FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    ASSERT_NE(rowLayoutPattern, nullptr);
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    ASSERT_NE(rowLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    /**
     * @tc.steps: step2. layout parameter initialization.
     */
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(RK356_WIDTH, ROW_HEIGHT));
    PaddingProperty noPadding;
    noPadding.left = CalcLength(NOPADDING);
    noPadding.right = CalcLength(NOPADDING);
    noPadding.top = CalcLength(NOPADDING);
    noPadding.bottom = CalcLength(NOPADDING);

    /**
     * @tc.steps: step3. Perform element updates.
     */
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    /**
     * @tc.steps: step4. creat a childLayoutWrapper and add to layoutWrapper.
     */
    auto childLayoutWrapper = CreatChildlayoutWrapper();
    layoutWrapper->AppendChild(childLayoutWrapper);
    BoxLayoutAlgorithm boxLayoutAlgorithm;

    /**
     * @tc.steps: step5. call SetIsLayoutFullScreen and SetIsAppWindow.
     * @tc.expected: expect the pipe and pipe1 is return false.
     */
    PipelineBase::GetCurrentContext()->SetIsLayoutFullScreen(false);
    PipelineBase::GetCurrentContext()->SetIsAppWindow(false);
    boxLayoutAlgorithm.Layout(AccessibilityManager::RawPtr(layoutWrapper));
    auto pipe = PipelineContext::GetCurrentContext()->safeAreaManager_->isFullScreen_;
    auto pipe1 = PipelineBase::GetCurrentContext()->isAppWindow_;
    EXPECT_FALSE(pipe);
    EXPECT_FALSE(pipe1);

    PipelineBase::GetCurrentContext()->SetIsLayoutFullScreen(true);
    PipelineBase::GetCurrentContext()->SetIsAppWindow(false);
    boxLayoutAlgorithm.PerformLayout(AccessibilityManager::RawPtr(layoutWrapper));
    auto pipe2 = PipelineContext::GetCurrentContext()->safeAreaManager_->isFullScreen_;
    EXPECT_TRUE(pipe2);
}

/**
 * @tc.name: BoxLayoutAlgorithmTest_MeasureContent005
 * @tc.desc: Set one index value into BoxLayoutAlgorithmTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTestNg, BoxLayoutAlgorithmTest_MeasureContent005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat a layoutwrapper and SetLayoutAlgorithm for it.
     */
    auto layoutWrapper = CreatlayoutWrapper();

    auto rowFrameNode = FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    ASSERT_NE(rowLayoutPattern, nullptr);
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    ASSERT_NE(rowLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    /**
     * @tc.steps: step2. layout parameter initialization.
     */
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(RK356_WIDTH, ROW_HEIGHT));
    PaddingProperty noPadding;
    noPadding.left = CalcLength(NOPADDING);
    noPadding.right = CalcLength(NOPADDING);
    noPadding.top = CalcLength(NOPADDING);
    noPadding.bottom = CalcLength(NOPADDING);

    /**
     * @tc.steps: step3. Perform element updates.
     */
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    /**
     * @tc.steps: step5. call MeasureContent.
     * @tc.expected: expect the host is null.
     */
    BoxLayoutAlgorithm boxLayoutAlgorithm;
    auto host = layoutWrapper->GetHostNode();
    boxLayoutAlgorithm.MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(host, nullptr);

    /**
     * @tc.steps: step6. call MeasureContent.
     * @tc.expected: expect the host1 is not null.
     */
    layoutWrapper->hostNode_ = rowFrameNode;
    boxLayoutAlgorithm.MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    auto host1 = layoutWrapper->GetHostNode();
    ASSERT_NE(host1, nullptr);
}

/**
 * @tc.name: BoxLayoutAlgorithmTest_PerformLayout006
 * @tc.desc: Set one index value into BoxLayoutAlgorithmTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTestNg, BoxLayoutAlgorithmTest_PerformLayout006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat a layoutwrapper and SetLayoutAlgorithm for it.
     */
    auto layoutWrapper = CreatlayoutWrapper();

    auto rowFrameNode = FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    ASSERT_NE(rowLayoutPattern, nullptr);
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    ASSERT_NE(rowLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    /**
     * @tc.steps: step2. layout parameter initialization.
     */
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(RK356_WIDTH, ROW_HEIGHT));
    PaddingProperty noPadding;
    noPadding.left = CalcLength(NOPADDING);
    noPadding.right = CalcLength(NOPADDING);
    noPadding.top = CalcLength(NOPADDING);
    noPadding.bottom = CalcLength(NOPADDING);

    /**
     * @tc.steps: step3. Perform element updates.
     */
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    /**
     * @tc.steps: step4. creat a childLayoutWrapper and add to layoutWrapper.
     */
    auto childLayoutWrapper = CreatChildlayoutWrapper();
    layoutWrapper->AppendChild(childLayoutWrapper);

    /**
     * @tc.steps: step5. call PerformLayout.
     * @tc.expected: expect the positionProperty_ is not null.
     */
    BoxLayoutAlgorithm boxLayoutAlgorithm;
    layoutWrapper->GetLayoutProperty()->positionProperty_ = std::make_unique<PositionProperty>();
    boxLayoutAlgorithm.PerformLayout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_NE(layoutWrapper->GetLayoutProperty()->positionProperty_, nullptr);

    /**
     * @tc.steps: step6. call PerformLayout.
     * @tc.expected: expect the content_ is not null.
     */
    SizeF size { 0.1, 0.1 };
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    layoutWrapper->GetGeometryNode()->SetContentSize(size);
    boxLayoutAlgorithm.PerformLayout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_NE(layoutWrapper->GetGeometryNode()->content_, nullptr);
}

/**
 * @tc.name: BoxLayoutAlgorithmTest_PerformMeasureSelfWithChildList007
 * @tc.desc: Set one index value into BoxLayoutAlgorithmTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTestNg, BoxLayoutAlgorithmTest_PerformMeasureSelfWithChildList007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat a layoutwrapper and SetLayoutAlgorithm for it.
     */
    auto layoutWrapper = CreatlayoutWrapper();

    auto rowFrameNode = FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    ASSERT_NE(rowLayoutPattern, nullptr);
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    ASSERT_NE(rowLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    /**
     * @tc.steps: step2. layout parameter initialization.
     */
    LayoutConstraintF parentLayoutConstraint;
    PaddingProperty noPadding;
    noPadding.left = CalcLength(NOPADDING);
    noPadding.right = CalcLength(NOPADDING);
    noPadding.top = CalcLength(NOPADDING);
    noPadding.bottom = CalcLength(NOPADDING);

    /**
     * @tc.steps: step3. Perform element updates.
     */
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    BoxLayoutAlgorithm boxLayoutAlgorithm;
    std::list<RefPtr<LayoutWrapper>> childList;
    boxLayoutAlgorithm.PerformMeasureSelfWithChildList(AccessibilityManager::RawPtr(layoutWrapper), childList);

    /**
     * @tc.steps: step4. call SetOptionalSize.
     * @tc.expected: expect the size is nullopt.
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
 * @tc.name: BoxLayoutAlgorithmTest_PerformMeasureSelfWithChildList008
 * @tc.desc: Set one index value into BoxLayoutAlgorithmTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTestNg, BoxLayoutAlgorithmTest_PerformMeasureSelfWithChildList008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat a layoutwrapper and SetLayoutAlgorithm for it.
     */
    auto layoutWrapper = CreatlayoutWrapper();

    auto rowFrameNode = FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    ASSERT_NE(rowLayoutPattern, nullptr);
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    ASSERT_NE(rowLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    /**
     * @tc.steps: step2. layout parameter initialization.
     */
    LayoutConstraintF parentLayoutConstraint;
    PaddingProperty noPadding;
    noPadding.left = CalcLength(NOPADDING);
    noPadding.right = CalcLength(NOPADDING);
    noPadding.top = CalcLength(NOPADDING);
    noPadding.bottom = CalcLength(NOPADDING);

    /**
     * @tc.steps: step3. Perform element updates.
     */
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    /**
     * @tc.steps: step4. call SetOptionalSize.
     * @tc.expected: expect the size is same with .
     */
    BoxLayoutAlgorithm boxLayoutAlgorithm;
    std::list<RefPtr<LayoutWrapper>> childList;
    layoutWrapper->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    auto type = layoutWrapper->GetLayoutProperty()->measureType_;
    const auto& layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    parentLayoutConstraint.selfIdealSize.SetOptionalSize(layoutConstraint->parentIdealSize);
    boxLayoutAlgorithm.PerformMeasureSelfWithChildList(AccessibilityManager::RawPtr(layoutWrapper), childList);
    EXPECT_EQ(type, MeasureType::MATCH_PARENT);

    /**
     * @tc.steps: step5. call SetContentSize.
     * @tc.expected: expect the layoutWrapper->GetGeometryNode()->content_ is not null .
     */
    SizeF size { 0.1, 0.1 };
    layoutWrapper->GetGeometryNode()->SetContentSize(size);
    boxLayoutAlgorithm.PerformMeasureSelfWithChildList(
        AccessibilityManager::RawPtr(layoutWrapper), layoutWrapper->GetAllChildrenWithBuild());
    EXPECT_NE(layoutWrapper->GetGeometryNode()->content_, nullptr);
}

/**
 * @tc.name: BoxLayoutAlgorithmTest_PerformMeasureSelfWithChildList009
 * @tc.desc: Set one index value into BoxLayoutAlgorithmTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTestNg, BoxLayoutAlgorithmTest_PerformMeasureSelfWithChildList009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat a layoutwrapper and SetLayoutAlgorithm for it.
     */
    auto layoutWrapper = CreatlayoutWrapper();

    auto rowFrameNode = FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    ASSERT_NE(rowLayoutPattern, nullptr);
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    ASSERT_NE(rowLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    /**
     * @tc.steps: step2. layout parameter initialization.
     */
    LayoutConstraintF parentLayoutConstraint;
    PaddingProperty noPadding;
    noPadding.left = CalcLength(NOPADDING);
    noPadding.right = CalcLength(NOPADDING);
    noPadding.top = CalcLength(NOPADDING);
    noPadding.bottom = CalcLength(NOPADDING);

    /**
     * @tc.steps: step3. Perform element updates.
     */
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    /**
     * @tc.steps: step1. pushback firstLayoutWrapper to childlist .
     * @tc.expected: expect list child is not null.
     */
    BoxLayoutAlgorithm boxLayoutAlgorithm;
    auto childLayoutWrapper = CreatChildlayoutWrapper();

    std::list<RefPtr<LayoutWrapper>> childList;
    childList.push_back(childLayoutWrapper);
    boxLayoutAlgorithm.PerformMeasureSelfWithChildList(AccessibilityManager::RawPtr(layoutWrapper), childList);
    EXPECT_NE(&childList, nullptr);
}
} // namespace OHOS::Ace::NG
