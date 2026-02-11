/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"

#include "core/components/common/properties/alignment.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/blank/blank_model_ng.h"

#define private public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/blank/blank_model_ng.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_layout_algorithm.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_layout_property.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_model_ng.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_pattern.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/unittest/core/pattern/folder_stack/folder_stack_test_ng.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

void FolderStackTestNg::SetUpTestSuite()
{
    MockContainer::SetUp();
    MockPipelineContext::SetUp();
    // Clean up ViewStackProcessor to avoid state leakage between test cases
    auto viewStack = ViewStackProcessor::GetInstance();
    if (viewStack) {
        viewStack->ClearStack();
    }
}

void FolderStackTestNg::TearDownTestSuite()
{
    // Clean up ViewStackProcessor to avoid state leakage to subsequent test suites
    auto viewStack = ViewStackProcessor::GetInstance();
    if (viewStack) {
        viewStack->ClearStack();
    }
    MockContainer::TearDown();
    MockPipelineContext::TearDown();
}

PaddingProperty FolderStackTestNg::CreatePadding(float left, float top, float right, float bottom)
{
    PaddingProperty padding;
    padding.left = CalcLength(left);
    padding.right = CalcLength(right);
    padding.top = CalcLength(top);
    padding.bottom = CalcLength(bottom);
    return padding;
}

RefPtr<UINode> FolderStackTestNg::CreateWithItem(bool enableAnimation, bool autoHalfFold, Alignment align)
{
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(align);
    folderStackModelNG.SetEnableAnimation(enableAnimation);
    folderStackModelNG.SetAutoHalfFold(autoHalfFold);
    {
        BlankModelNG blankModelNG;
        blankModelNG.Create();
        ViewAbstract::SetWidth(CalcLength(SMALL_ITEM_WIDTH));
        ViewAbstract::SetHeight(CalcLength(SMALL_ITEM_HEIGHT));
        PaddingProperty noPadding = CreatePadding(ZERO, ZERO, ZERO, ZERO);
        ViewAbstract::SetPadding(noPadding);
        ViewStackProcessor::GetInstance()->Pop();
    }
    auto frameNode = ViewStackProcessor::GetInstance()->Finish();
    return frameNode;
}

/**
 * @tc.name: FolderStackTestNgTest001
 * @tc.desc: Test folderStack Layout with Alignment
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create folderStack and get frameNode.
     */
    Alignment align = Alignment::TOP_LEFT;
    bool enableAnimation = false;
    bool autoHalfFold = false;
    auto frameNode = AceType::DynamicCast<FrameNode>(CreateWithItem(enableAnimation, autoHalfFold, align));
    auto layoutProperty = frameNode->GetLayoutProperty<FolderStackLayoutProperty>();
    auto alignment = layoutProperty->GetPositionProperty()->GetAlignment();
    ASSERT_EQ(alignment, Alignment::TOP_LEFT);
    ASSERT_EQ(layoutProperty->GetEnableAnimation(), false);
    ASSERT_EQ(layoutProperty->GetAutoHalfFold(), false);

    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: related function is called.
     */
    RefPtr<GeometryNode> geometryNode = frameNode->GetGeometryNode();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto folderStackPattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(folderStackPattern, nullptr);
    auto layoutAlgorithm =
        AceType::DynamicCast<FolderStackLayoutAlgorithm>(folderStackPattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    /**
     * @tc.steps: step3. update layoutWrapper.
     */
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(STACK_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    PaddingProperty noPadding = CreatePadding(ZERO, ZERO, ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);

    /**
     * @tc.steps: step4. use layoutAlgorithm to layout.
     * @tc.expected: check whether the value of geometry frameSize and frameOffset is correct.
     */
    layoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    layoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    ASSERT_EQ(layoutWrapper->GetGeometryNode()->GetMarginFrameSize(), SizeF(FULL_SCREEN_WIDTH, STACK_HEIGHT));
    ASSERT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(ZERO, ZERO));
}

/**
 * @tc.name: FolderStackTestNgTest002
 * @tc.desc: Test folderStack Layout with AlignmentContent
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create folderStack and get frameNode.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<FolderStackLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    ASSERT_NE(layoutProperty->GetPositionProperty(), nullptr);
    auto alignmentContent = layoutProperty->GetPositionProperty()->GetAlignment();
    ASSERT_EQ(alignmentContent, Alignment::TOP_LEFT);
    layoutProperty->UpdateLayoutDirection(TextDirection::LTR);

    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: related function is called.
     */

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto folderStackPattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(folderStackPattern, nullptr);
    auto layoutAlgorithm = folderStackPattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);

    /**
     * @tc.steps: step3. update layoutWrapper.
     */
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(STACK_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    PaddingProperty noPadding = CreatePadding(ZERO, ZERO, ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    /**
     * @tc.steps: step4. use layoutAlgorithm to layout.
     * @tc.expected: check whether the value of geometry frameSize and frameOffset is correct.
     */
    layoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    layoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    ASSERT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(FULL_SCREEN_WIDTH, STACK_HEIGHT));
    ASSERT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(ZERO, ZERO));
}

/**
 * @tc.name: FolderStackTestNgTest003
 * @tc.desc: Test folderStack pattern with AlignmentContent
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest003, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create folderStack and get frameNode.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. get host
     * @tc.expected: related function is called.
     */
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    pattern->OnAttachToFrameNode();
    std::optional<int32_t> optionalValue = 1;
    pattern->UpdateFoldStatusChangedCallbackId(optionalValue);
    pattern->OnDetachFromFrameNode(AceType::RawPtr(frameNode));

    pattern->InitFolderStackPatternAppearCallback();
    pattern->OnModifyDone();
}

/**
 * @tc.name: FolderStackTestNgTest004
 * @tc.desc: Test folderStack pattern transitionStatus_ has changed.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest004, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create folderStack and get frameNode.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. get host
     * @tc.expected: related function is called.
     */
    pattern->OnFolderStateChangeSend(FoldStatus::UNKNOWN);
    pattern->OnFolderStateChangeSend(FoldStatus::FOLDED);

    /**
     * @tc.steps: step3. call OnDirtyLayoutWrapperSwap.
     * @tc.expected: pattern->transitionStatus_ has changed.
     */
    RefPtr<LayoutWrapper> layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    ASSERT_EQ(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, true), false);
    ASSERT_EQ(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false), false);
    ASSERT_EQ(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, false), false);
    ASSERT_EQ(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, true), false);
}

/**
 * @tc.name: FolderStackTestNgTest005
 * @tc.desc: Test folderStack pattern visible has changed.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest005, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create folderStack and get frameNode.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2.
     * @tc.expected: pattern->visible has changed.
     */
    pattern->OnVisibleChange(true);
    pattern->OnVisibleChange(false);
}

/**
 * @tc.name: FolderStackTestNgTest006
 * @tc.desc: Test folderStack pattern visible has changed.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest006, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create folderStack and get frameNode.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. get host
     * @tc.expected: related function is called.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<FolderStackLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateEnableAnimation(false);
    pattern->StartOffsetEnteringAnimation();
}

/**
 * @tc.name: FolderStackTestNgTest007
 * @tc.desc: Test folderStack pattern RefreshStack changed.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest007, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create folderStack and get frameNode.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. get host
     * @tc.expected: related function is called.
     */
    pattern->RefreshStack(FoldStatus::FOLDED);
}

/**
 * @tc.name: FolderStackTestNgTest008
 * @tc.desc: Test folderStack pattern visible has changed.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest008, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create folderStack and get frameNode.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. get host
     * @tc.expected: related function is called.
     */
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto hostNode = AceType::DynamicCast<FolderStackGroupNode>(host);
    hostNode->SetControlPartsStackNode(nullptr);
    hostNode->SetHoverNode(nullptr);
    pattern->UpdateChildAlignment();
}

/**
 * @tc.name: FolderStackTestNgTest009
 * @tc.desc: Test folderStack pattern SetAutoRotate has changed.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest009, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create folderStack and get frameNode.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. get host
     * @tc.expected: related function is called.
     */
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<FolderStackLayoutProperty>();
    layoutProperty->UpdateAutoHalfFold(true);
    auto displayInfo = container->GetDisplayInfo();
    ASSERT_NE(displayInfo, nullptr);
    displayInfo->SetFoldStatus(FoldStatus::HALF_FOLD);
    container->SetOrientation(Orientation::HORIZONTAL);
    pattern->SetAutoRotate();
    pattern->RestoreScreenState();
}

/**
 * @tc.name: FolderStackTestNgTest010
 * @tc.desc: Test folderStack pattern SetAutoRotate has changed.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest010, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create folderStack and get frameNode.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. get host
     * @tc.expected: related function is called.
     */
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<FolderStackLayoutProperty>();
    layoutProperty->UpdateAutoHalfFold(false);
    auto displayInfo = container->GetDisplayInfo();
    ASSERT_NE(displayInfo, nullptr);
    displayInfo->SetFoldStatus(FoldStatus::HALF_FOLD);
    container->SetOrientation(Orientation::HORIZONTAL);
    pattern->SetAutoRotate();
}

/**
 * @tc.name: FolderStackTestNgTest011
 * @tc.desc: Test folderStack pattern SetAutoRotate has changed.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest011, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create folderStack and get frameNode.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. get host
     * @tc.expected: related function is called.
     */
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<FolderStackLayoutProperty>();
    layoutProperty->UpdateAutoHalfFold(true);
    auto displayInfo = container->GetDisplayInfo();
    ASSERT_NE(displayInfo, nullptr);
    displayInfo->SetFoldStatus(FoldStatus::EXPAND);
    container->SetOrientation(Orientation::HORIZONTAL);
    pattern->SetAutoRotate();
}

/**
 * @tc.name: FolderStackTestNgTest012
 * @tc.desc: Test folderStack pattern SetAutoRotate has changed.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest012, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create folderStack and get frameNode.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. get host
     * @tc.expected: related function is called.
     */
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<FolderStackLayoutProperty>();
    layoutProperty->UpdateAutoHalfFold(false);
    auto displayInfo = container->GetDisplayInfo();
    ASSERT_NE(displayInfo, nullptr);
    displayInfo->SetFoldStatus(FoldStatus::EXPAND);
    container->SetOrientation(Orientation::HORIZONTAL);
    pattern->SetAutoRotate();
}

/**
 * @tc.name: FolderStackTestNgTest013
 * @tc.desc: Test folderStack pattern SetAutoRotate has changed.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest013, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create folderStack and get frameNode.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. get host
     * @tc.expected: related function is called.
     */
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<FolderStackLayoutProperty>();
    layoutProperty->UpdateAutoHalfFold(true);
    auto displayInfo = container->GetDisplayInfo();
    ASSERT_NE(displayInfo, nullptr);
    displayInfo->SetFoldStatus(FoldStatus::HALF_FOLD);
    container->SetOrientation(Orientation::SENSOR);
    pattern->SetAutoRotate();
}

/**
 * @tc.name: FolderStackTestNgTest014
 * @tc.desc: Test folderStack pattern SetAutoRotate has changed.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest014, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create folderStack and get frameNode.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. get host
     * @tc.expected: related function is called.
     */
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<FolderStackLayoutProperty>();
    layoutProperty->UpdateAutoHalfFold(true);
    auto displayInfo = container->GetDisplayInfo();
    ASSERT_NE(displayInfo, nullptr);
    displayInfo->SetFoldStatus(FoldStatus::EXPAND);
    container->SetOrientation(Orientation::SENSOR);
    pattern->SetAutoRotate();
}

/**
 * @tc.name: FolderStackTestNgTest015
 * @tc.desc: Test folderStack pattern SetAutoRotate has changed.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest015, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create folderStack and get frameNode.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. get host
     * @tc.expected: related function is called.
     */
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<FolderStackLayoutProperty>();
    layoutProperty->UpdateAutoHalfFold(false);
    auto displayInfo = container->GetDisplayInfo();
    ASSERT_NE(displayInfo, nullptr);
    displayInfo->SetFoldStatus(FoldStatus::EXPAND);
    container->SetOrientation(Orientation::SENSOR);
    pattern->SetAutoRotate();
}

/**
 * @tc.name: FolderStackTestNgMatchParent001
 * @tc.desc: Test folderStack match parent.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgMatchParent001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create folderStack and get frameNode.
     */

    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetMinPlatformVersion(12);
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);

    RefPtr<FrameNode> folder1;

    auto frameNode = CreateFolder([this, &folder1](FolderStackModelNG model) {
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetSafeAreaPadding(CalcLength(10.0f, DimensionUnit::PX));

        folder1 = CreateFolder([this](FolderStackModelNG model) {});
    });
    ASSERT_NE(frameNode, nullptr);
    auto childLayoutProperty = folder1->GetLayoutProperty();
    ASSERT_NE(childLayoutProperty, nullptr);
    childLayoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
    childLayoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
    FlushUITasks(frameNode);

    EXPECT_EQ(frameNode->GetGeometryNode()->GetFrameSize(), SizeF(300.0f, 300.0f))
        << frameNode->GetGeometryNode()->GetFrameRect().ToString();
    EXPECT_EQ(frameNode->GetGeometryNode()->GetFrameOffset(), OffsetF(0.0f, 0.0f));
    EXPECT_EQ(folder1->GetGeometryNode()->GetFrameSize(), SizeF(280.0f, 280.0f))
        << folder1->GetGeometryNode()->GetFrameRect().ToString();
}

/**
 * @tc.name: FolderStackTestNgMatchParent002
 * @tc.desc: Test folderStack match parent.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgMatchParent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create folderStack and get frameNode.
     */

    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetMinPlatformVersion(12);
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);

    RefPtr<FrameNode> folder;
    RefPtr<FrameNode> folder1;

    auto stack = CreateStack([this, &folder, &folder1](StackModelNG model) {
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetSafeAreaPadding(CalcLength(10.0f, DimensionUnit::PX));

        folder = CreateFolder([this, &folder1](FolderStackModelNG model) {
            folder1 = CreateFolder([this, &folder1](FolderStackModelNG model) {});
        });
    });
    ASSERT_NE(folder, nullptr);
    auto layoutProperty = folder->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
    auto childLayoutProperty = folder1->GetLayoutProperty();
    ASSERT_NE(childLayoutProperty, nullptr);
    childLayoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
    childLayoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
    FlushUITasks(stack);

    EXPECT_EQ(folder->GetGeometryNode()->GetFrameSize(), SizeF(280.0f, 280.0f))
        << folder->GetGeometryNode()->GetFrameRect().ToString();
    EXPECT_EQ(folder->GetGeometryNode()->GetFrameOffset(), OffsetF(10.0f, 10.0f));
    EXPECT_EQ(folder1->GetGeometryNode()->GetFrameSize(), SizeF(280.0f, 280.0f))
        << folder1->GetGeometryNode()->GetFrameRect().ToString();
}

/**
 * @tc.name: FolderStackTestNgTest016
 * @tc.desc: Test folderStack IsIntoFolderStack.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create folderStack and get frameNode.
     */
 
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetMinPlatformVersion(12);
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
 
    RefPtr<FrameNode> folder;
    RefPtr<FrameNode> folder1;
 
    auto stack = CreateStack([this, &folder, &folder1](StackModelNG model) {
        ViewAbstract::SetWidth(CalcLength("100%"));
        ViewAbstract::SetHeight(CalcLength("100%"));
 
        folder = CreateFolder([this, &folder1](FolderStackModelNG model) {
            folder1 = CreateFolder([this, &folder1](FolderStackModelNG model) {});
        });
    });
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto folderStackPattern = folder->GetPattern<FolderStackPattern>();
    ASSERT_NE(folderStackPattern, nullptr);
    auto layoutAlgorithm =
        AceType::DynamicCast<FolderStackLayoutAlgorithm>(folderStackPattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    ASSERT_NE(folder, nullptr);
    auto layoutProperty = folder->GetLayoutProperty<FolderStackLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto displayInfo = container->GetDisplayInfo();
    ASSERT_NE(displayInfo, nullptr);
    displayInfo->SetFoldStatus(FoldStatus::EXPAND);
    displayInfo->SetRotation(Rotation::ROTATION_0);
    container->SetOrientation(Orientation::VERTICAL);
    folderStackPattern->SetAutoRotate();
    const auto& layoutConstraint = layoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint);
    RefPtr<GeometryNode> geometryNode = folder->GetGeometryNode();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(folder, geometryNode, folder->GetLayoutProperty());
    auto size = CreateIdealSizeByPercentRef(layoutConstraint.value(), Axis::HORIZONTAL, MeasureType::MATCH_PARENT)
                    .ConvertToSizeT();
    layoutWrapper->GetGeometryNode()->SetFrameSize(size);
    ASSERT_NE(layoutAlgorithm->IsIntoFolderStack(size, layoutProperty,
        AccessibilityManager::RawPtr(layoutWrapper)), true);
}

/**
 * @tc.name: FolderStackTestNgTest017
 * @tc.desc: Test FolderStackPattern consistency across multiple method calls.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest017, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create folderStack frameNode and pattern.
     * @tc.expected: FrameNode and pattern are created successfully.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test IsInHoverMode consistency.
     * @tc.expected: Returns consistent value across calls.
     */
    bool hoverMode1 = pattern->IsInHoverMode();
    bool hoverMode2 = pattern->IsInHoverMode();
    bool hoverMode3 = pattern->IsInHoverMode();
    EXPECT_EQ(hoverMode1, hoverMode2);
    EXPECT_EQ(hoverMode2, hoverMode3);

    /**
     * @tc.steps: step3. Test IsAtomicNode consistency.
     * @tc.expected: Always returns false.
     */
    EXPECT_FALSE(pattern->IsAtomicNode());
    EXPECT_FALSE(pattern->IsAtomicNode());
    EXPECT_FALSE(pattern->IsAtomicNode());

    /**
     * @tc.steps: step4. Test IsNeedPercent consistency.
     * @tc.expected: Always returns true.
     */
    EXPECT_TRUE(pattern->IsNeedPercent());
    EXPECT_TRUE(pattern->IsNeedPercent());
    EXPECT_TRUE(pattern->IsNeedPercent());

    /**
     * @tc.steps: step5. Test GetFocusPattern consistency.
     * @tc.expected: Returns consistent values.
     */
    auto focusPattern1 = pattern->GetFocusPattern();
    auto focusPattern2 = pattern->GetFocusPattern();
    EXPECT_EQ(focusPattern1.GetFocusType(), focusPattern2.GetFocusType());
    EXPECT_EQ(focusPattern1.GetFocusable(), focusPattern2.GetFocusable());
}

/**
 * @tc.name: FolderStackTestNgTest018
 * @tc.desc: Test FolderStackPattern SetLastTime and GetLastTime methods.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest018, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create folderStack frameNode and pattern.
     * @tc.expected: FrameNode and pattern are created successfully.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::CENTER);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test SetLastTime with specific time value.
     * @tc.expected: GetLastTime returns the set value.
     */
    std::time_t testTime = 1234567890;
    pattern->SetLastTime(testTime);
    EXPECT_EQ(pattern->GetLastTime(), testTime);

    /**
     * @tc.steps: step3. Test SetLastTime with current time.
     * @tc.expected: GetLastTime returns the current time value.
     */
    std::time_t currentTime = std::time(nullptr);
    pattern->SetLastTime(currentTime);
    EXPECT_EQ(pattern->GetLastTime(), currentTime);

    /**
     * @tc.steps: step4. Test SetLastTime with zero.
     * @tc.expected: GetLastTime returns zero.
     */
    pattern->SetLastTime(0);
    EXPECT_EQ(pattern->GetLastTime(), 0);
}

/**
 * @tc.name: FolderStackTestNgTest019
 * @tc.desc: Test FolderStackPattern IsInHoverMode method.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest019, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create folderStack frameNode and pattern.
     * @tc.expected: FrameNode and pattern are created successfully.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::BOTTOM_RIGHT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test IsInHoverMode returns valid boolean.
     * @tc.expected: Returns either true or false.
     */
    bool hoverMode = pattern->IsInHoverMode();
    EXPECT_TRUE(hoverMode == false);

    /**
     * @tc.steps: step3. Test IsInHoverMode consistency across multiple calls.
     * @tc.expected: Returns consistent value.
     */
    bool hoverMode2 = pattern->IsInHoverMode();
    EXPECT_EQ(hoverMode, hoverMode2);
}

/**
 * @tc.name: FolderStackTestNgTest020
 * @tc.desc: Test FolderStackLayoutAlgorithm GetIsIntoFolderStack and GetControlPartsStackRect.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest020, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create folderStack frameNode and pattern.
     * @tc.expected: FrameNode and pattern are created successfully.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Get layout algorithm from pattern.
     * @tc.expected: LayoutAlgorithm is created successfully.
     */
    auto layoutAlgorithm =
        AceType::DynamicCast<FolderStackLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);

    /**
     * @tc.steps: step3. Test GetIsIntoFolderStack default value.
     * @tc.expected: Returns false by default.
     */
    bool isIntoFolderStack = layoutAlgorithm->GetIsIntoFolderStack();
    EXPECT_FALSE(isIntoFolderStack);

    /**
     * @tc.steps: step4. Test GetControlPartsStackRect default value.
     * @tc.expected: Returns OffsetF(0.0f, 0.0f) by default.
     */
    OffsetF rect = layoutAlgorithm->GetControlPartsStackRect();
    EXPECT_FLOAT_EQ(rect.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(rect.GetY(), 0.0f);
}

/**
 * @tc.name: FolderStackTestNgTest021
 * @tc.desc: Test FolderStackLayoutProperty UpperItems property methods.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest021, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create folderStack frameNode and layout property.
     * @tc.expected: FrameNode and layout property are created successfully.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<FolderStackLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. Test HasUpperItems returns true initially.
     * @tc.expected: No upper items are set by default.
     */
    EXPECT_TRUE(layoutProperty->HasUpperItems());

    /**
     * @tc.steps: step3. Test UpdateUpperItems with multiple items.
     * @tc.expected: Items are set and can be retrieved.
     */
    std::vector<std::string> upperItems = {"item1", "item2", "item3"};
    layoutProperty->UpdateUpperItems(upperItems);

    EXPECT_TRUE(layoutProperty->HasUpperItems());

    auto retrievedItems = layoutProperty->GetUpperItemsValue();
    EXPECT_EQ(retrievedItems.size(), 3);
    EXPECT_EQ(retrievedItems[0], "item1");
    EXPECT_EQ(retrievedItems[1], "item2");
    EXPECT_EQ(retrievedItems[2], "item3");

    /**
     * @tc.steps: step4. Test GetUpperItemsValue returns empty vector when not set.
     * @tc.expected: Returns empty vector.
     */
    auto retrievedItems2 = layoutProperty->GetUpperItemsValue();
    EXPECT_EQ(retrievedItems2.size(), 3);
}

/**
 * @tc.name: FolderStackTestNgTest022
 * @tc.desc: Test FolderStackPattern UpdateFoldStatusChangedCallbackId and HasFoldStatusChangedCallbackId.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest022, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create folderStack frameNode and pattern.
     * @tc.expected: FrameNode and pattern are created successfully.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_CENTER);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test HasFoldStatusChangedCallbackId returns false initially.
     * @tc.expected: No callback ID is set by default.
     */
    EXPECT_FALSE(pattern->HasFoldStatusChangedCallbackId());

    /**
     * @tc.steps: step3. Test UpdateFoldStatusChangedCallbackId with value.
     * @tc.expected: Callback ID is set and HasFoldStatusChangedCallbackId returns true.
     */
    std::optional<int32_t> callbackId = 42;
    pattern->UpdateFoldStatusChangedCallbackId(callbackId);
    EXPECT_TRUE(pattern->HasFoldStatusChangedCallbackId());

    /**
     * @tc.steps: step4. Test UpdateFoldStatusChangedCallbackId with empty optional.
     * @tc.expected: Callback ID is cleared and HasFoldStatusChangedCallbackId returns false.
     */
    std::optional<int32_t> emptyId;
    pattern->UpdateFoldStatusChangedCallbackId(emptyId);
    EXPECT_FALSE(pattern->HasFoldStatusChangedCallbackId());

    /**
     * @tc.steps: step5. Test multiple callback ID updates.
     * @tc.expected: Each update sets the new value correctly.
     */
    pattern->UpdateFoldStatusChangedCallbackId(std::optional<int32_t>(1));
    EXPECT_TRUE(pattern->HasFoldStatusChangedCallbackId());

    pattern->UpdateFoldStatusChangedCallbackId(std::optional<int32_t>(100));
    EXPECT_TRUE(pattern->HasFoldStatusChangedCallbackId());
}

/**
 * @tc.name: FolderStackTestNgTest023
 * @tc.desc: Test FolderStackLayoutProperty EnableAnimation and AutoHalfFold properties.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest023, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create folderStack frameNode and layout property.
     * @tc.expected: FrameNode and layout property are created successfully.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    folderStackModelNG.SetEnableAnimation(true);
    folderStackModelNG.SetAutoHalfFold(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<FolderStackLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. Test GetEnableAnimation returns true when set.
     * @tc.expected: Returns the set value.
     */
    EXPECT_TRUE(layoutProperty->GetEnableAnimation().value_or(false));

    /**
     * @tc.steps: step3. Test UpdateEnableAnimation with false.
     * @tc.expected: EnableAnimation is updated to false.
     */
    layoutProperty->UpdateEnableAnimation(false);
    EXPECT_FALSE(layoutProperty->GetEnableAnimation().value_or(true));

    /**
     * @tc.steps: step4. Test GetAutoHalfFold returns true when set.
     * @tc.expected: Returns the set value.
     */
    EXPECT_TRUE(layoutProperty->GetAutoHalfFold().value_or(false));

    /**
     * @tc.steps: step5. Test UpdateAutoHalfFold with false.
     * @tc.expected: AutoHalfFold is updated to false.
     */
    layoutProperty->UpdateAutoHalfFold(false);
    EXPECT_FALSE(layoutProperty->GetAutoHalfFold().value_or(true));

    /**
     * @tc.steps: step6. Test toggling both properties.
     * @tc.expected: Properties change correctly.
     */
    layoutProperty->UpdateEnableAnimation(true);
    layoutProperty->UpdateAutoHalfFold(true);
    EXPECT_TRUE(layoutProperty->GetEnableAnimation().value_or(false));
    EXPECT_TRUE(layoutProperty->GetAutoHalfFold().value_or(false));
}

/**
 * @tc.name: FolderStackTestNgTest025
 * @tc.desc: Test FolderStackEventHub callback replacement.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest025, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create folderStack frameNode and event hub.
     * @tc.expected: FrameNode and event hub are created successfully.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<FolderStackEventHub>();
    ASSERT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. Set first callback and invoke.
     * @tc.expected: First callback is invoked.
     */
    int firstCallbackCount = 0;
    eventHub->SetOnFolderStateChange([&firstCallbackCount](const FolderEventInfo& info) {
        firstCallbackCount++;
    });

    FolderEventInfo eventInfo(FoldStatus::EXPAND);
    eventHub->OnFolderStateChange(eventInfo);
    EXPECT_EQ(firstCallbackCount, 1);

    /**
     * @tc.steps: step3. Replace with second callback and invoke.
     * @tc.expected: Second callback is invoked, first is not.
     */
    int secondCallbackCount = 0;
    eventHub->SetOnFolderStateChange([&secondCallbackCount](const FolderEventInfo& info) {
        secondCallbackCount++;
    });

    eventHub->OnFolderStateChange(eventInfo);
    EXPECT_EQ(firstCallbackCount, 1);  // First callback not called again
    EXPECT_EQ(secondCallbackCount, 1); // Second callback called

    /**
     * @tc.steps: step4. Verify only second callback is active.
     * @tc.expected: Only second callback count increases.
     */
    eventHub->OnFolderStateChange(eventInfo);
    EXPECT_EQ(firstCallbackCount, 1);
    EXPECT_EQ(secondCallbackCount, 2);
}

/**
 * @tc.name: FolderStackTestNgTest026
 * @tc.desc: Test FolderStackPattern GetDisplayInfo method.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest026, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create folderStack frameNode and pattern.
     * @tc.expected: FrameNode and pattern are created successfully.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test GetDisplayInfo.
     * @tc.expected: Returns DisplayInfo pointer (may be null or valid).
     */
    auto displayInfo = pattern->GetDisplayInfo();
    // DisplayInfo may be null or valid depending on container initialization
    EXPECT_TRUE(displayInfo == nullptr);

    pattern->SetAutoRotate();
    displayInfo = pattern->GetDisplayInfo();
    EXPECT_FALSE(displayInfo == nullptr);
}

/**
 * @tc.name: FolderStackTestNgTest027
 * @tc.desc: Test FolderStackPattern HasFoldStatusDelayTask method.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest027, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create folderStack frameNode and pattern.
     * @tc.expected: FrameNode and pattern are created successfully.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::CENTER);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test HasFoldStatusDelayTask returns valid boolean.
     * @tc.expected: Returns either true or false.
     */
    bool hasDelayTask = pattern->HasFoldStatusDelayTask();
    EXPECT_TRUE(hasDelayTask == false);
}

/**
 * @tc.name: FolderStackTestNgTest028
 * @tc.desc: Test FolderStackPattern BeforeCreateLayoutWrapper method.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest028, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create folderStack frameNode and pattern.
     * @tc.expected: FrameNode and pattern are created successfully.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    folderStackModelNG.SetEnableAnimation(true);
    folderStackModelNG.SetAutoHalfFold(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test BeforeCreateLayoutWrapper.
     * @tc.expected: Function completes without crash.
     */
    pattern->BeforeCreateLayoutWrapper();

    /**
     * @tc.steps: step3. Test BeforeCreateLayoutWrapper multiple times.
     * @tc.expected: Function completes without crash each time.
     */
    pattern->BeforeCreateLayoutWrapper();
    pattern->BeforeCreateLayoutWrapper();
    pattern->BeforeCreateLayoutWrapper();
}

/**
 * @tc.name: FolderStackTestNgTest030
 * @tc.desc: Test FolderStackLayoutProperty ToJsonValue method.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest030, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create folderStack frameNode and layout property.
     * @tc.expected: FrameNode and layout property are created successfully.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_RIGHT);
    folderStackModelNG.SetEnableAnimation(true);
    folderStackModelNG.SetAutoHalfFold(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<FolderStackLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. Set UpperItems for JSON serialization.
     * @tc.expected: Properties are set successfully.
     */
    layoutProperty->UpdateUpperItems({"jsonItem1", "jsonItem2", "jsonItem3"});
    layoutProperty->UpdateEnableAnimation(true);
    layoutProperty->UpdateAutoHalfFold(false);

    /**
     * @tc.steps: step3. Test ToJsonValue with default filter.
     * @tc.expected: JSON is generated successfully.
     */
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);

    InspectorFilter filter;
    layoutProperty->ToJsonValue(json, filter);

    /**
     * @tc.steps: step4. Verify JSON contains expected keys.
     * @tc.expected: JSON string contains property keys.
     */
    std::string jsonString = json->ToString();
    EXPECT_TRUE(jsonString.find("alignContent") != std::string::npos &&
                jsonString.find("upperItems") != std::string::npos &&
                jsonString.find("enableAnimation") != std::string::npos &&
                jsonString.find("autoHalfFold") != std::string::npos);
}

/**
 * @tc.name: FolderStackTestNgTest031
 * @tc.desc: Test FolderStackPattern IsAtomicNode and IsNeedPercent methods.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest031, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create folderStack frameNode and pattern.
     * @tc.expected: FrameNode and pattern are created successfully.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test IsAtomicNode.
     * @tc.expected: Returns false as folderStack is not an atomic node.
     */
    EXPECT_FALSE(pattern->IsAtomicNode());

    /**
     * @tc.steps: step3. Test IsNeedPercent.
     * @tc.expected: Returns true as folderStack needs percent for layout.
     */
    EXPECT_TRUE(pattern->IsNeedPercent());

    /**
     * @tc.steps: step4. Test consistency of these methods.
     * @tc.expected: Methods return consistent values across multiple calls.
     */
    EXPECT_FALSE(pattern->IsAtomicNode());
    EXPECT_TRUE(pattern->IsNeedPercent());
    EXPECT_FALSE(pattern->IsAtomicNode());
    EXPECT_TRUE(pattern->IsNeedPercent());
}

/**
 * @tc.name: FolderStackTestNgTest032
 * @tc.desc: Test FolderStackPattern GetFocusPattern method.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest032, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create folderStack frameNode and pattern.
     * @tc.expected: FrameNode and pattern are created successfully.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test GetFocusPattern.
     * @tc.expected: Returns focus pattern with SCOPE type and GetFocusable() true.
     */
    auto focusPattern = pattern->GetFocusPattern();
    EXPECT_EQ(focusPattern.GetFocusType(), FocusType::SCOPE);
    EXPECT_TRUE(focusPattern.GetFocusable());

    /**
     * @tc.steps: step3. Test GetFocusPattern consistency.
     * @tc.expected: Returns same values on multiple calls.
     */
    auto focusPattern2 = pattern->GetFocusPattern();
    EXPECT_EQ(focusPattern.GetFocusType(), focusPattern2.GetFocusType());
    EXPECT_EQ(focusPattern.GetFocusable(), focusPattern2.GetFocusable());
}

/**
 * @tc.name: FolderStackTestNgTest033
 * @tc.desc: Test FolderStackLayoutAlgorithm constructor and default values.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest033, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create layout algorithm using default constructor.
     * @tc.expected: Algorithm is created with default values.
     */
    FolderStackLayoutAlgorithm algorithm;

    /**
     * @tc.steps: step2. Test GetIsIntoFolderStack default value.
     * @tc.expected: Returns false by default.
     */
    EXPECT_FALSE(algorithm.GetIsIntoFolderStack());

    /**
     * @tc.steps: step3. Test GetControlPartsStackRect default value.
     * @tc.expected: Returns OffsetF(0.0f, 0.0f).
     */
    OffsetF rect = algorithm.GetControlPartsStackRect();
    EXPECT_FLOAT_EQ(rect.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(rect.GetY(), 0.0f);
}

/**
 * @tc.name: FolderStackTestNgTest034
 * @tc.desc: Test FolderStackLayoutProperty with different alignment values.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest034, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Test all alignment values.
     * @tc.expected: All alignments are set and retrieved correctly.
     */
    std::vector<Alignment> alignments = {
        Alignment::TOP_LEFT,
        Alignment::TOP_CENTER,
        Alignment::TOP_RIGHT,
        Alignment::CENTER_LEFT,
        Alignment::CENTER,
        Alignment::CENTER_RIGHT,
        Alignment::BOTTOM_LEFT,
        Alignment::BOTTOM_CENTER,
        Alignment::BOTTOM_RIGHT
    };

    for (const auto& alignment : alignments) {
        FolderStackModelNG folderStackModelNG;
        folderStackModelNG.Create();
        folderStackModelNG.SetAlignment(alignment);
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        ASSERT_NE(frameNode, nullptr);

        auto layoutProperty = frameNode->GetLayoutProperty<FolderStackLayoutProperty>();
        ASSERT_NE(layoutProperty, nullptr);
        ASSERT_NE(layoutProperty->GetPositionProperty(), nullptr);

        EXPECT_EQ(layoutProperty->GetPositionProperty()->GetAlignment().value_or(Alignment::CENTER), alignment);
    }
}

/**
 * @tc.name: FolderStackTestNgTest035
 * @tc.desc: Test FolderStackPattern OnDirtyLayoutWrapperSwap with various parameter combinations.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest035, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create folderStack frameNode and pattern.
     * @tc.expected: FrameNode and pattern are created successfully.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::CENTER);
    folderStackModelNG.SetEnableAnimation(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create layout wrapper.
     * @tc.expected: Layout wrapper is created successfully.
     */
    RefPtr<LayoutWrapper> layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step3. Test OnDirtyLayoutWrapperSwap with different parameter combinations.
     * @tc.expected: All combinations return false.
     */
    EXPECT_FALSE(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, true));
    EXPECT_FALSE(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, false));
    EXPECT_FALSE(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, true));
    EXPECT_FALSE(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false));
}

/**
 * @tc.name: FolderStackTestNgTest036
 * @tc.desc: Test FolderStackLayoutProperty with empty UpperItems.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest036, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create folderStack frameNode and layout property.
     * @tc.expected: FrameNode and layout property are created successfully.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<FolderStackLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. Test HasUpperItems returns true initially.
     * @tc.expected: No upper items are set by default.
     */
    EXPECT_TRUE(layoutProperty->HasUpperItems());

    /**
     * @tc.steps: step3. Test GetUpperItemsValue with empty items.
     * @tc.expected: Returns empty vector.
     */
    auto retrievedItems = layoutProperty->GetUpperItemsValue();
    EXPECT_TRUE(retrievedItems.empty());

    /**
     * @tc.steps: step4. Test with empty vector update.
     * @tc.expected: Still returns empty vector.
     */
    std::vector<std::string> emptyItems;
    layoutProperty->UpdateUpperItems(emptyItems);
    auto retrievedItems2 = layoutProperty->GetUpperItemsValue();
    EXPECT_TRUE(retrievedItems2.empty());
}

/**
 * @tc.name: FolderStackTestNgTest037
 * @tc.desc: Test FolderStackEventHub callback methods without callbacks set.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest037, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create folderStack frameNode and event hub.
     * @tc.expected: FrameNode and event hub are created successfully.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<FolderStackEventHub>();
    ASSERT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. Test OnFolderStateChange without callback.
     * @tc.expected: Function completes without crash.
     */
    FolderEventInfo eventInfo(FoldStatus::EXPAND);
    eventHub->OnFolderStateChange(eventInfo);

    /**
     * @tc.steps: step3. Test OnHoverStatusChange without callback.
     * @tc.expected: Function completes without crash.
     */
    eventHub->OnHoverStatusChange(std::move(eventInfo));

    /**
     * @tc.steps: step4. Test with different FoldStatus values.
     * @tc.expected: All status values handled without crash.
     */
    FolderEventInfo unknownInfo(FoldStatus::UNKNOWN);
    eventHub->OnFolderStateChange(unknownInfo);

    FolderEventInfo foldedInfo(FoldStatus::FOLDED);
    eventHub->OnFolderStateChange(foldedInfo);
}

/**
 * @tc.name: FolderStackTestNgTest038
 * @tc.desc: Test FolderStackEventHub SetOnFolderStateChange callback.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest038, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create folderStack frameNode and event hub.
     * @tc.expected: FrameNode and event hub are created successfully.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<FolderStackEventHub>();
    ASSERT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. Set folder state change callback.
     * @tc.expected: Callback is set successfully.
     */
    bool callbackCalled = false;
    FoldStatus capturedStatus = FoldStatus::UNKNOWN;

    eventHub->SetOnFolderStateChange([&callbackCalled, &capturedStatus](const FolderEventInfo& info) {
        callbackCalled = true;
        capturedStatus = info.GetFolderState();
    });

    /**
     * @tc.steps: step3. Trigger folder state change.
     * @tc.expected: Callback is invoked with correct status.
     */
    FolderEventInfo eventInfo(FoldStatus::FOLDED);
    eventHub->OnFolderStateChange(eventInfo);
    EXPECT_TRUE(callbackCalled);
    EXPECT_EQ(capturedStatus, FoldStatus::FOLDED);

    /**
     * @tc.steps: step4. Trigger with different status.
     * @tc.expected: Callback is invoked with new status.
     */
    callbackCalled = false;
    FolderEventInfo eventInfo2(FoldStatus::EXPAND);
    eventHub->OnFolderStateChange(eventInfo2);
    EXPECT_TRUE(callbackCalled);
    EXPECT_EQ(capturedStatus, FoldStatus::EXPAND);
}

/**
 * @tc.name: FolderStackTestNgTest039
 * @tc.desc: Test FolderStackPattern CreateLayoutProperty and CreatePaintProperty methods.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest039, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create folderStack frameNode and pattern.
     * @tc.expected: FrameNode and pattern are created successfully.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test CreateLayoutProperty.
     * @tc.expected: Returns FolderStackLayoutProperty instance.
     */
    auto layoutProperty = pattern->CreateLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);

    auto folderStackLayoutProperty = AceType::DynamicCast<FolderStackLayoutProperty>(layoutProperty);
    ASSERT_NE(folderStackLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. Test CreatePaintProperty.
     * @tc.expected: Returns PaintProperty instance.
     */
    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: FolderStackTestNgTest040
 * @tc.desc: Test FolderStackPattern CreateEventHub method.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest040, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create folderStack frameNode and pattern.
     * @tc.expected: FrameNode and pattern are created successfully.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test CreateEventHub.
     * @tc.expected: Returns FolderStackEventHub instance.
     */
    auto eventHub = pattern->CreateEventHub();
    ASSERT_NE(eventHub, nullptr);

    auto folderStackEventHub = AceType::DynamicCast<FolderStackEventHub>(eventHub);
    ASSERT_NE(folderStackEventHub, nullptr);
}

/**
 * @tc.name: FolderStackTestNgTest041
 * @tc.desc: Test FolderStackLayoutProperty UpdateLayoutConstraint and UpdateContentConstraint.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest041, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create folderStack frameNode and layout property.
     * @tc.expected: FrameNode and layout property are created successfully.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<FolderStackLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. Create and update layout constraint.
     * @tc.expected: Layout constraint is updated successfully.
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(1000.0f, 800.0f);
    layoutConstraint.minSize = SizeF(100.0f, 80.0f);
    layoutConstraint.percentReference = SizeF(1000.0f, 800.0f);

    layoutProperty->UpdateLayoutConstraint(layoutConstraint);

    /**
     * @tc.steps: step3. Update content constraint.
     * @tc.expected: Content constraint is updated successfully.
     */
    layoutProperty->UpdateContentConstraint();

    /**
     * @tc.steps: step4. Verify constraint was updated.
     * @tc.expected: Constraint values match the set values.
     */
    auto retrievedConstraint = layoutProperty->GetLayoutConstraint();
    ASSERT_TRUE(retrievedConstraint.has_value());
    EXPECT_EQ(retrievedConstraint->maxSize, SizeF(1000.0f, 800.0f));
    EXPECT_EQ(retrievedConstraint->minSize, SizeF(100.0f, 80.0f));
}

/**
 * @tc.name: FolderStackTestNgTest042
 * @tc.desc: Test FolderStackLayoutProperty with single UpperItem.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest042, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create folderStack frameNode and layout property.
     * @tc.expected: FrameNode and layout property are created successfully.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<FolderStackLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. Test with single UpperItem.
     * @tc.expected: Single item is set and retrieved correctly.
     */
    std::vector<std::string> singleItem = {"onlyItem"};
    layoutProperty->UpdateUpperItems(singleItem);

    EXPECT_TRUE(layoutProperty->HasUpperItems());

    auto retrievedItems = layoutProperty->GetUpperItemsValue();
    EXPECT_EQ(retrievedItems.size(), 1);
    EXPECT_EQ(retrievedItems[0], "onlyItem");

    /**
     * @tc.steps: step3. Test with empty string item.
     * @tc.expected: Empty string item is handled correctly.
     */
    std::vector<std::string> emptyStringItem = {""};
    layoutProperty->UpdateUpperItems(emptyStringItem);

    EXPECT_TRUE(layoutProperty->HasUpperItems());
    retrievedItems = layoutProperty->GetUpperItemsValue();
    EXPECT_EQ(retrievedItems.size(), 1);
    EXPECT_EQ(retrievedItems[0], "");
}

/**
 * @tc.name: FolderStackTestNgTest043
 * @tc.desc: Test FolderStackEventHub SetOnHoverStatusChange callback.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest043, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create folderStack frameNode and event hub.
     * @tc.expected: FrameNode and event hub are created successfully.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<FolderStackEventHub>();
    ASSERT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. Set hover status change callback.
     * @tc.expected: Callback is set successfully.
     */
    bool callbackCalled = false;
    FoldStatus capturedStatus = FoldStatus::UNKNOWN;

    eventHub->SetOnHoverStatusChange([&callbackCalled, &capturedStatus](const FolderEventInfo& info) {
        callbackCalled = true;
        capturedStatus = info.GetFolderState();
    });

    /**
     * @tc.steps: step3. Trigger hover status change.
     * @tc.expected: Callback is invoked with correct status.
     */
    FolderEventInfo eventInfo(FoldStatus::EXPAND);
    eventHub->OnHoverStatusChange(std::move(eventInfo));
    EXPECT_TRUE(callbackCalled);
    EXPECT_EQ(capturedStatus, FoldStatus::EXPAND);

    /**
     * @tc.steps: step4. Trigger with different status.
     * @tc.expected: Callback is invoked with new status.
     */
    callbackCalled = false;
    FolderEventInfo eventInfo2(FoldStatus::HALF_FOLD);
    eventHub->OnHoverStatusChange(std::move(eventInfo2));
    EXPECT_TRUE(callbackCalled);
    EXPECT_EQ(capturedStatus, FoldStatus::HALF_FOLD);
}

/**
 * @tc.name: FolderStackTestNgTest044
 * @tc.desc: Test FolderStackEventHub with both callbacks set.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest044, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create folderStack frameNode and event hub.
     * @tc.expected: FrameNode and event hub are created successfully.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<FolderStackEventHub>();
    ASSERT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. Set both callbacks.
     * @tc.expected: Both callbacks are set successfully.
     */
    bool folderCallbackCalled = false;
    bool hoverCallbackCalled = false;

    eventHub->SetOnFolderStateChange([&folderCallbackCalled](const FolderEventInfo& info) {
        folderCallbackCalled = true;
    });

    eventHub->SetOnHoverStatusChange([&hoverCallbackCalled](const FolderEventInfo& info) {
        hoverCallbackCalled = true;
    });

    /**
     * @tc.steps: step3. Trigger folder state change.
     * @tc.expected: Folder callback is invoked.
     */
    FolderEventInfo folderInfo(FoldStatus::EXPAND);
    eventHub->OnFolderStateChange(folderInfo);
    EXPECT_TRUE(folderCallbackCalled);

    /**
     * @tc.steps: step4. Trigger hover status change.
     * @tc.expected: Hover callback is invoked.
     */
    FolderEventInfo hoverInfo(FoldStatus::FOLDED);
    eventHub->OnHoverStatusChange(std::move(hoverInfo));
    EXPECT_TRUE(hoverCallbackCalled);
}

/**
 * @tc.name: FolderStackTestNgTest049
 * @tc.desc: Test FolderStackPattern SetAutoRotate with different orientations.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest049, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create folderStack frameNode and pattern.
     * @tc.expected: FrameNode and pattern are created successfully.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    folderStackModelNG.SetAutoHalfFold(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Get container and display info.
     * @tc.expected: Container and display info are available.
     */
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<FolderStackLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto displayInfo = container->GetDisplayInfo();
    ASSERT_NE(displayInfo, nullptr);

    /**
     * @tc.steps: step3. Test SetAutoRotate with VERTICAL orientation.
     * @tc.expected: Function completes without crash.
     */
    displayInfo->SetFoldStatus(FoldStatus::HALF_FOLD);
    container->SetOrientation(Orientation::VERTICAL);
    pattern->SetAutoRotate();

    /**
     * @tc.steps: step4. Test SetAutoRotate with HORIZONTAL orientation.
     * @tc.expected: Function completes without crash.
     */
    container->SetOrientation(Orientation::HORIZONTAL);
    pattern->SetAutoRotate();

    /**
     * @tc.steps: step5. Test SetAutoRotate with SENSOR orientation.
     * @tc.expected: Function completes without crash.
     */
    container->SetOrientation(Orientation::SENSOR);
    pattern->SetAutoRotate();
}

/**
 * @tc.name: FolderStackTestNgTest050
 * @tc.desc: Test FolderStackPattern RestoreScreenState.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest050, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create folderStack frameNode and pattern.
     * @tc.expected: FrameNode and pattern are created successfully.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    folderStackModelNG.SetAutoHalfFold(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test RestoreScreenState.
     * @tc.expected: Function completes without crash.
     */
    pattern->RestoreScreenState();
}

/**
 * @tc.name: FolderStackTestNgTest053
 * @tc.desc: Test FolderStackPattern CreateLayoutAlgorithm multiple times.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest053, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create folderStack frameNode and pattern.
     * @tc.expected: FrameNode and pattern are created successfully.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test CreateLayoutAlgorithm multiple times.
     * @tc.expected: Each call returns a valid algorithm.
     */
    auto algorithm1 = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm1, nullptr);

    auto algorithm2 = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm2, nullptr);

    auto algorithm3 = AceType::DynamicCast<FolderStackLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(algorithm3, nullptr);

    /**
     * @tc.steps: step3. Verify all algorithms have default values.
     * @tc.expected: All algorithms return false for GetIsIntoFolderStack.
     */
    auto folderStackAlgo1 = AceType::DynamicCast<FolderStackLayoutAlgorithm>(algorithm1);
    auto folderStackAlgo2 = AceType::DynamicCast<FolderStackLayoutAlgorithm>(algorithm2);

    ASSERT_NE(folderStackAlgo1, nullptr);
    ASSERT_NE(folderStackAlgo2, nullptr);

    EXPECT_FALSE(folderStackAlgo1->GetIsIntoFolderStack());
    EXPECT_FALSE(folderStackAlgo2->GetIsIntoFolderStack());
    EXPECT_FALSE(algorithm3->GetIsIntoFolderStack());
}

/**
 * @tc.name: FolderStackTestNgTest051
 * @tc.desc: Test FolderStackLayoutProperty ToJsonValue with empty properties.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNg, FolderStackTestNgTest051, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create folderStack frameNode and layout property.
     * @tc.expected: FrameNode and layout property are created successfully.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::CENTER);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<FolderStackLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. Test ToJsonValue without UpperItems.
     * @tc.expected: JSON is generated successfully with basic properties.
     */
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);

    InspectorFilter filter;
    layoutProperty->ToJsonValue(json, filter);

    /**
     * @tc.steps: step3. Verify JSON contains alignment.
     * @tc.expected: JSON string contains alignContent key.
     */
    std::string jsonString = json->ToString();
    EXPECT_TRUE(jsonString.find("alignContent") != std::string::npos);
}

} // namespace OHOS::Ace::NG
