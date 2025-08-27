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

#include "test/mock/core/pipeline/mock_pipeline_context.h"

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

class BoxLayoutAlgorithmTestOld : public testing::Test {
public:
    static void SetUpTestCase()
    {
        MockPipelineContext::SetUp();
    }
    static void TearDownTestCase()
    {
        MockPipelineContext::TearDown();
    }
};

/**
 * @tc.name: BoxLayoutAlgorithmTestOld_Measure001
 * @tc.desc: Set one index value into BoxLayoutAlgorithmTestOld and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTestOld, BoxLayoutAlgorithmTestOld_Measure001, TestSize.Level0)
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
    EXPECT_FALSE(pipe);
}

/**
 * @tc.name: BoxLayoutAlgorithmTestOld_Measure002
 * @tc.desc: Set one index value into BoxLayoutAlgorithmTestOld and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTestOld, BoxLayoutAlgorithmTestOld_Measure002, TestSize.Level0)
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
 * @tc.name: BoxLayoutAlgorithmTestOld_Layout003
 * @tc.desc: Set one index value into BoxLayoutAlgorithmTestOld and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTestOld, BoxLayoutAlgorithmTestOld_Layout003, TestSize.Level0)
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
    EXPECT_FALSE(LayoutFullScreen);
    EXPECT_TRUE(AppWindow);
}

/**
 * @tc.name: BoxLayoutAlgorithmTestOld_Layout004
 * @tc.desc: Set one index value into BoxLayoutAlgorithmTestOld and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTestOld, BoxLayoutAlgorithmTestOld_Layout004, TestSize.Level0)
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
    EXPECT_FALSE(pipe2);
}

/**
 * @tc.name: BoxLayoutAlgorithmTestOld_MeasureContent005
 * @tc.desc: Set one index value into BoxLayoutAlgorithmTestOld and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTestOld, BoxLayoutAlgorithmTestOld_MeasureContent005, TestSize.Level0)
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
 * @tc.name: BoxLayoutAlgorithmTestOld_PerformLayout006
 * @tc.desc: Set one index value into BoxLayoutAlgorithmTestOld and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTestOld, BoxLayoutAlgorithmTestOld_PerformLayout006, TestSize.Level0)
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
 * @tc.name: BoxLayoutAlgorithmTestOld_PerformMeasureSelfWithChildList007
 * @tc.desc: Set one index value into BoxLayoutAlgorithmTestOld and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTestOld, BoxLayoutAlgorithmTestOld_PerformMeasureSelfWithChildList007, TestSize.Level0)
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
 * @tc.name: BoxLayoutAlgorithmTestOld_PerformMeasureSelfWithChildList008
 * @tc.desc: Set one index value into BoxLayoutAlgorithmTestOld and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTestOld, BoxLayoutAlgorithmTestOld_PerformMeasureSelfWithChildList008, TestSize.Level0)
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
 * @tc.name: BoxLayoutAlgorithmTestOld_PerformMeasureSelfWithChildList009
 * @tc.desc: Set one index value into BoxLayoutAlgorithmTestOld and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTestOld, BoxLayoutAlgorithmTestOld_PerformMeasureSelfWithChildList009, TestSize.Level0)
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

/**
 * @tc.name: BoxLayoutAlgorithmTestOld_PerformMeasureSelfWithChildList010
 * @tc.desc: Set one index value into BoxLayoutAlgorithmTestOld and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTestOld, BoxLayoutAlgorithmTestOld_PerformMeasureSelfWithChildList010, TestSize.Level0)
{
    /**
     * @tc.steps: step1. creat a layoutwrapper and SetLayoutAlgorithm for it.
     */
    auto layoutWrapper = CreatlayoutWrapper();

    auto rowFrameNode = FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    /**
     * @tc.steps: step2. layout parameter initialization.
     */
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.parentIdealSize.SetSize(SizeF(RK356_WIDTH, ROW_HEIGHT));

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
     * @tc.steps: step4. parentIdealSize is Valid.
     * @tc.expected: expect the size is same with parentIdealSize .
     */
    BoxLayoutAlgorithm boxLayoutAlgorithm;
    std::list<RefPtr<LayoutWrapper>> childList;
    layoutWrapper->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    auto type = layoutWrapper->GetLayoutProperty()->measureType_;
    boxLayoutAlgorithm.PerformMeasureSelfWithChildList(AccessibilityManager::RawPtr(layoutWrapper), childList);
    EXPECT_EQ(type, MeasureType::MATCH_PARENT);
}

/**
 * @tc.name: BoxLayoutAlgorithmTestOld_MeasureContent011
 * @tc.desc: Set one index value into BoxLayoutAlgorithmTestOld and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTestOld, BoxLayoutAlgorithmTestOld_MeasureContent011, TestSize.Level0)
{
    /**
     * @tc.steps: step1. creat a layoutwrapper and SetLayoutAlgorithm for it.
     */
    auto layoutWrapper = CreatlayoutWrapper();
    auto rowFrameNode = FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. layout parameter initialization.
     */
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
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
     * @tc.steps: step6. call MeasureContent and set measureType_ = MeasureType::MATCH_PARENT.
     * @tc.expected: expect the host1 is not null.
     */
    layoutWrapper->hostNode_ = rowFrameNode;
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    layoutProperty->measureType_ = MeasureType::MATCH_PARENT;
    boxLayoutAlgorithm.MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    auto host1 = layoutWrapper->GetHostNode();
    EXPECT_TRUE(host1->IsAtomicNode());

    /**
     * @tc.steps: step7. selfIdealSize is not Valid.
     * expected: return percentReference.
     */
    parentLayoutConstraint.percentReference.SetSizeT(SizeF(RK356_WIDTH, ROW_HEIGHT));
    std::optional<SizeF> sizeTemp =
        boxLayoutAlgorithm.MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));

    EXPECT_EQ(sizeTemp.value().width_, parentLayoutConstraint.percentReference.width_);
    EXPECT_EQ(sizeTemp.value().height_, parentLayoutConstraint.percentReference.height_);

    /**
     * @tc.steps: step8. set measureType_ other.
     * expected: return minSize.
     */
    parentLayoutConstraint.minSize.SetSizeT(SizeF(RK356_WIDTH + 1, ROW_HEIGHT + 1));
    layoutProperty->measureType_ = MeasureType::MATCH_CONTENT;
    sizeTemp = boxLayoutAlgorithm.MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(sizeTemp.value().width_, parentLayoutConstraint.minSize.width_);
    EXPECT_EQ(sizeTemp.value().height_, parentLayoutConstraint.minSize.height_);

    /**
     * @tc.steps: step9. set selfIdealSize valid.
     * expected: return selfIdealSize.
     */
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(RK356_WIDTH - 1, ROW_HEIGHT - 1));
    sizeTemp = boxLayoutAlgorithm.MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(sizeTemp.value().width_, parentLayoutConstraint.selfIdealSize.width_);
    EXPECT_EQ(sizeTemp.value().height_, parentLayoutConstraint.selfIdealSize.height_);
}

/**
 * @tc.name: BoxLayoutAlgorithmTestOld_PerformMeasureSelfWithChildList012
 * @tc.desc: Set one index value into BoxLayoutAlgorithmTestOld and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTestOld, BoxLayoutAlgorithmTestOld_PerformMeasureSelfWithChildList012, TestSize.Level0)
{
    /**
     * @tc.steps: step1. creat a layoutwrapper and SetLayoutAlgorithm for it.
     */
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::STACK_ETS_TAG, 0, []() { return AceType::MakeRefPtr<Pattern>(); });
    RefPtr<LayoutWrapper> layoutWrapper = frameNode->CreateLayoutWrapper(true, true);

    /**
     * @tc.steps: step2. layout parameter initialization.
     */
    PaddingProperty noPadding;
    noPadding.left = CalcLength(NOPADDING);
    noPadding.right = CalcLength(NOPADDING);
    noPadding.top = CalcLength(NOPADDING);
    noPadding.bottom = CalcLength(NOPADDING);

    /**
     * @tc.steps: step3. Perform element updates.
     */
    LayoutConstraintF parentLayoutConstraint;
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    /**
     * @tc.steps: step4. parentIdealSize is Valid.
     * @tc.expected: expect the size is same with layoutWrapper3 .
     */
    BoxLayoutAlgorithm boxLayoutAlgorithm;
    std::list<RefPtr<LayoutWrapper>> childList;
    childList = layoutWrapper->GetAllChildrenWithBuild();
    childList.push_front(nullptr);
    auto layoutWrapper2 = CreatlayoutWrapper();
    layoutWrapper2->GetLayoutProperty()->propVisibility_ = VisibleType::GONE;
    childList.push_front(layoutWrapper2);
    auto layoutWrapper3 = CreatChildlayoutWrapper();
    layoutWrapper3->GetGeometryNode()->frame_.rect_.SetSize(SizeF(RK356_WIDTH, ROW_HEIGHT));
    childList.push_front(layoutWrapper3);
    boxLayoutAlgorithm.PerformMeasureSelfWithChildList(AccessibilityManager::RawPtr(layoutWrapper), childList);
    EXPECT_FALSE(layoutWrapper->GetGeometryNode()->content_);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->frame_.rect_.height_, ROW_HEIGHT);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->frame_.rect_.width_, RK356_WIDTH);

    /**
     * @tc.steps: step4. selfIdealSize isn't Valid and height is true.
     * @tc.expected: expect the size is same with layoutWrapper3 .
     */
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(0.0, ROW_HEIGHT));
    layoutWrapper->GetLayoutProperty()->calcLayoutConstraint_ = nullptr;
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    boxLayoutAlgorithm.PerformMeasureSelfWithChildList(AccessibilityManager::RawPtr(layoutWrapper), childList);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->frame_.rect_.height_, ROW_HEIGHT);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->frame_.rect_.width_, 0);

    /**
     * @tc.steps: step4. parentIdealSize isn't Valid and width is true.
     * @tc.expected: expect the size is same with layoutWrapper3 .
     */
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(RK356_WIDTH, 0.0));
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    boxLayoutAlgorithm.PerformMeasureSelfWithChildList(AccessibilityManager::RawPtr(layoutWrapper), childList);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->frame_.rect_.height_, 0);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->frame_.rect_.width_, RK356_WIDTH);
}
} // namespace OHOS::Ace::NG
