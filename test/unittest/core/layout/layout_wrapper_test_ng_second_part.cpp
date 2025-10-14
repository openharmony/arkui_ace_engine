/*
 * Copyright (c) 2025 iSoftStone Information Technology (Group) Co.,Ltd.
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

#include "test/unittest/core/layout/layout_wrapper_test_ng.h"

namespace OHOS::Ace::NG {

/**
 * @tc.name: LayoutWrapperTest020
 * @tc.desc: Test Measure.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest020, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create layoutwrapper.
     */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, NODE_ID_0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. set layoutWrapper->layoutAlgorithm_ is not null.
     */
    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    /**
     * @tc.steps: step3. call UpdateParentConstraint update parentLayoutConstraint.
     */
    LayoutConstraintF parentLayoutConstraint;
    UpdateParentConstraint(layoutWrapper, parentLayoutConstraint);

    /**
     * @tc.steps: step3. call Measure and set layoutAlgorithm_->skipMeasure_ is TEST_TRUE.
     * @tc.expected: FRAME_SIZE is the same as TEST_FRAME_SIZE.
     */
    layoutWrapper->layoutAlgorithm_->skipMeasure_ = TEST_TRUE;
    layoutWrapper->Measure(parentLayoutConstraint);
    FRAME_SIZE = layoutWrapper->geometryNode_->GetFrameSize();
    EXPECT_EQ(FRAME_SIZE, TEST_FRAME_SIZE);
}

/**
 * @tc.name: LayoutWrapperTest021
 * @tc.desc: Test Measure.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest021, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create a layoutwrapper pointer.
     */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, NODE_ID_0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. set layoutWrapper->layoutAlgorithm_ is not null.
     */
    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    /**
     * @tc.steps: step3. call UpdateParentConstraint update parentLayoutConstraint.
     */
    LayoutConstraintF parentLayoutConstraint;
    UpdateParentConstraint(layoutWrapper, parentLayoutConstraint);

    /**
     * @tc.steps: step3. call Measure.
     * @tc.expected: FRAME_SIZE.Width() is RK356_WIDTH and FRAME_SIZE.Height() is ROW_HEIGHT.
     */
    layoutWrapper->Measure(parentLayoutConstraint);
    FRAME_SIZE = layoutWrapper->geometryNode_->GetFrameSize();
    EXPECT_EQ(FRAME_SIZE.width_, RK356_WIDTH);
    EXPECT_EQ(FRAME_SIZE.height_, ROW_HEIGHT);

    /**
     * @tc.steps: step4. UpdateAspectRatio and UpdateLayoutWeight.
     */

    layoutWrapper->layoutProperty_->magicItemProperty_.UpdateAspectRatio(0.5);
    layoutWrapper->layoutProperty_->magicItemProperty_.UpdateLayoutWeight(0.5);
    /**
     * @tc.steps: step5. call Measure.
     * @tc.expected: FRAME_SIZE.Height() is twice as much RK356_WIDTH.
     */
    layoutWrapper->Measure(parentLayoutConstraint);
    FRAME_SIZE = layoutWrapper->geometryNode_->GetFrameSize();
    EXPECT_EQ(FRAME_SIZE.width_, RK356_WIDTH);
    EXPECT_EQ(FRAME_SIZE.height_, RK356_WIDTH * 2);

    /**
     * @tc.steps: step6. call Measure and set layoutProperty_->calcLayoutConstraint_is not null.
     * @tc.expected: SELF_IDEAL_SIZE.Height() is twice as much RK356_WIDTH.
     */
    layoutWrapper->layoutProperty_->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutWrapper->Measure(parentLayoutConstraint);
    IDEAL_SIZE.width_ = layoutWrapper->layoutProperty_->layoutConstraint_->selfIdealSize.Width();
    IDEAL_SIZE.height_ = layoutWrapper->layoutProperty_->layoutConstraint_->selfIdealSize.Height();
    EXPECT_EQ(IDEAL_SIZE.width_, RK356_WIDTH);
    EXPECT_EQ(IDEAL_SIZE.height_, RK356_WIDTH * 2);
}

/**
 * @tc.name: LayoutWrapperTest022
 * @tc.desc: Test Measure.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest022, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create a layoutwrapper pointer.
     */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, NODE_ID_0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. set layoutWrapper->layoutAlgorithm_ is not null.
     */
    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    /**
     * @tc.steps: step3. call UpdateParentConstraint update parentLayoutConstraint.
     */
    LayoutConstraintF parentLayoutConstraint;
    UpdateParentConstraint(layoutWrapper, parentLayoutConstraint);

    /**
     * @tc.steps: step4. call Measure and set layoutWrapper->needForceMeasureAndLayout_ is TEST_FALSE.
     * @tc.expected: layoutWrapper->skipMeasureContent_ is true.
     */
    layoutWrapper->needForceMeasureAndLayout_ = std::make_optional(TEST_FALSE);
    layoutWrapper->Measure(parentLayoutConstraint);
    EXPECT_TRUE(layoutWrapper->skipMeasureContent_);
}

/**
 * @tc.name: LayoutWrapperTest023
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest023, TestSize.Level0)
{
    /**
     * @tc.steps: step1. call CreateLayoutWrapper create a layoutwrapper pointer.
     */
    RefPtr<LayoutWrapperNode> layoutWrapper = CreateLayoutWrapper(ROW_FRAME_NODE, NODE_ID_0);

    /**
     * @tc.steps: step2. call UpdateParentConstraint update parentLayoutConstraint.
     */
    LayoutConstraintF parentLayoutConstraint;
    UpdateParentConstraint(layoutWrapper, parentLayoutConstraint);

    /**
     * @tc.steps: step3. call Layout and set layoutWrapper->layoutProperty_ is null.
     * @tc.expected: FRAME_SIZE is the same as TEST_FRAME_SIZE.
     */
    layoutWrapper->layoutProperty_ = nullptr;
    layoutWrapper->Layout();
    FRAME_SIZE = layoutWrapper->geometryNode_->GetFrameSize();
    EXPECT_EQ(FRAME_SIZE, TEST_FRAME_SIZE);
}

/**
 * @tc.name: LayoutWrapperTest024
 * @tc.desc: Test Layout.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest024, TestSize.Level0)
{
    /**
     * @tc.steps: step1. call CreateLayoutWrapper create a layoutwrapper pointer.
     */
    RefPtr<LayoutWrapperNode> layoutWrapper = CreateLayoutWrapper(ROW_FRAME_NODE, NODE_ID_0);

    /**
     * @tc.steps: step2. call UpdateParentConstraint update parentLayoutConstraint.
     */
    LayoutConstraintF parentLayoutConstraint;
    UpdateParentConstraint(layoutWrapper, parentLayoutConstraint);

    /**
     * @tc.steps: step3. call Layout and set layoutWrapper->geometryNode_ is null.
     * @tc.expected: FRAME_SIZE is the default value.
     */
    layoutWrapper->geometryNode_ = nullptr;
    layoutWrapper->Layout();
    EXPECT_EQ(layoutWrapper->geometryNode_, nullptr);
}

/**
 * @tc.name: LayoutWrapperTest025
 * @tc.desc: Test Layout.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest025, TestSize.Level0)
{
    /**
     * @tc.steps: step1. call CreateLayoutWrapper create a layoutwrapper pointer.
     */
    RefPtr<LayoutWrapperNode> layoutWrapper = CreateLayoutWrapper(ROW_FRAME_NODE, NODE_ID_0);

    /**
     * @tc.steps: step2. call UpdateParentConstraint update parentLayoutConstraint.
     */
    LayoutConstraintF parentLayoutConstraint;
    UpdateParentConstraint(layoutWrapper, parentLayoutConstraint);

    /**
     * @tc.steps: step3. call Layout and set layoutWrapper->hostNode_ is null.
     * @tc.expected: FRAME_SIZE is the same as TEST_FRAME_SIZE.
     */
    layoutWrapper->hostNode_ = nullptr;
    layoutWrapper->Layout();
    FRAME_SIZE = layoutWrapper->geometryNode_->GetFrameSize();
    EXPECT_EQ(FRAME_SIZE, TEST_FRAME_SIZE);
}

/**
 * @tc.name: LayoutWrapperTest026
 * @tc.desc: Test Layout.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest026, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create a layoutwrapper pointer.
     */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, NODE_ID_0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step3. call UpdateParentConstraint update parentLayoutConstraint.
     */
    LayoutConstraintF parentLayoutConstraint;
    UpdateParentConstraint(layoutWrapper, parentLayoutConstraint);

    /**
     * @tc.steps: step3. call Layout and set layoutWrapper->layoutAlgorithm_ is not null.
     * @tc.expected: FRAME_SIZE is the same as TEST_FRAME_SIZE.
     */
    layoutWrapper->Layout();
    FRAME_SIZE = layoutWrapper->geometryNode_->GetFrameSize();
    EXPECT_EQ(FRAME_SIZE, TEST_FRAME_SIZE);
}

/**
 * @tc.name: LayoutWrapperTest027
 * @tc.desc: Test Layout.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest027, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create a layoutwrapper pointer.
     */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, NODE_ID_0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. set layoutWrapper->layoutAlgorithm_ is not null.
     */
    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    /**
     * @tc.steps: step3. call UpdateParentConstraint update parentLayoutConstraint.
     */
    LayoutConstraintF parentLayoutConstraint;
    UpdateParentConstraint(layoutWrapper, parentLayoutConstraint);

    /**
     * @tc.steps: step4. call Layout and set layoutWrapper->layoutAlgorithm_->skipLayout_ is TEST_TRUE.
     * @tc.expected: FRAME_SIZE is the same as TEST_FRAME_SIZE.
     */
    layoutWrapper->layoutAlgorithm_->skipLayout_ = TEST_TRUE;
    layoutWrapper->Layout();
    FRAME_SIZE = layoutWrapper->geometryNode_->GetFrameSize();
    EXPECT_EQ(FRAME_SIZE, TEST_FRAME_SIZE);
}

/**
 * @tc.name: LayoutWrapperTest028
 * @tc.desc: Test Layout.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest028, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create a layoutwrapper pointer.
     */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, NODE_ID_0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. set layoutWrapper->layoutAlgorithm_ is not null.
     */
    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    /**
     * @tc.steps: step3. call UpdateParentConstraint update parentLayoutConstraint.
     */
    LayoutConstraintF parentLayoutConstraint;
    UpdateParentConstraint(layoutWrapper, parentLayoutConstraint);

    /**
     * @tc.steps: step4. call Layout and set layoutWrapper->skipMeasureContent_ is default value.
     * @tc.expected: FRAME_SIZE is the same as TEST_FRAME_SIZE.
     */
    layoutWrapper->Layout();
    FRAME_SIZE = layoutWrapper->geometryNode_->GetFrameSize();
    EXPECT_EQ(FRAME_SIZE, TEST_FRAME_SIZE);

    /**
     * @tc.steps: step5. call Layout and set layoutWrapper->skipMeasureContent_ is TEST_TRUE.
     * @tc.expected: FRAME_SIZE is the same as TEST_FRAME_SIZE.
     */
    layoutWrapper->skipMeasureContent_ = TEST_TRUE;
    layoutWrapper->Layout();
    FRAME_SIZE = layoutWrapper->geometryNode_->GetFrameSize();
    EXPECT_EQ(FRAME_SIZE, TEST_FRAME_SIZE);
}

/**
 * @tc.name: LayoutWrapperTest029
 * @tc.desc: Test Layout.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest029, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create a layoutwrapper pointer.
     */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, NODE_ID_0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. set layoutWrapper->layoutAlgorithm_ is not null.
     */
    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    /**
     * @tc.steps: step3. call UpdateParentConstraint update parentLayoutConstraint.
     */
    LayoutConstraintF parentLayoutConstraint;
    UpdateParentConstraint(layoutWrapper, parentLayoutConstraint);

    /**
     * @tc.steps: step4. call Layout and set layoutWrapper->skipMeasureContent_ is default value.
     * @tc.expected: FRAME_SIZE is the same as TEST_FRAME_SIZE.
     */
    layoutWrapper->Layout();
    FRAME_SIZE = layoutWrapper->geometryNode_->GetFrameSize();
    EXPECT_EQ(FRAME_SIZE, TEST_FRAME_SIZE);
}

/**
 * @tc.name: LayoutWrapperTest030
 * @tc.desc: Test SkipMeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest030, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create a layoutwrapper pointer.
     */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, NODE_ID_0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. set layoutWrapper->layoutAlgorithm_ is not null.
     */
    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    /**
     * @tc.steps: step3. call SkipMeasureContent.
     * @tc.expected: the return value is false.
     */
    bool retSkipMeasureContent = layoutWrapper->SkipMeasureContent();
    EXPECT_FALSE(retSkipMeasureContent);

    /**
     * @tc.steps: step4. call SkipMeasureContent and set layoutWrapper->skipMeasureContent_ is true.
     * @tc.expected: the return value is true.
     */
    layoutWrapper->skipMeasureContent_ = std::make_optional(TEST_TRUE);
    retSkipMeasureContent = layoutWrapper->SkipMeasureContent();
    EXPECT_TRUE(retSkipMeasureContent);
}

/**
 * @tc.name: LayoutWrapperTest031
 * @tc.desc: Test CheckNeedForceMeasureAndLayout.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest031, TestSize.Level0)
{
    /**
     * @tc.steps: step1. call CreateLayoutWrapper create a layoutwrapper pointer.
     */
    RefPtr<LayoutWrapperNode> layoutWrapper = CreateLayoutWrapper(ROW_FRAME_NODE, NODE_ID_0);

    /**
     * @tc.steps: step2. call CheckNeedForceMeasureAndLayout.
     * @tc.expected: the return retCheck is true.
     */
    bool retCheck = layoutWrapper->CheckNeedForceMeasureAndLayout();
    EXPECT_TRUE(retCheck);

    /**
     * @tc.steps: step3. call CheckNeedForceMeasureAndLayout again.
     * @tc.expected: the return retCheck is true.
     */
    retCheck = layoutWrapper->CheckNeedForceMeasureAndLayout();
    EXPECT_TRUE(retCheck);
}

/**
 * @tc.name: LayoutWrapperTest032
 * @tc.desc: Test CheckNeedForceMeasureAndLayout.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest032, TestSize.Level0)
{
    /**
     * @tc.steps: step1. call CreateLayoutWrapper create a layoutwrapper pointer.
     */
    RefPtr<LayoutWrapperNode> layoutWrapper = CreateLayoutWrapper(ROW_FRAME_NODE, NODE_ID_0);

    /**
     * @tc.steps: step2. call CheckNeedForceMeasureAndLayout again.
     * @tc.expected: the return retCheck is false.
     */
    layoutWrapper->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;
    bool retCheck = layoutWrapper->CheckNeedForceMeasureAndLayout();
    EXPECT_FALSE(retCheck);
}

/**
 * @tc.name: LayoutWrapperTest033
 * @tc.desc: Test CheckNeedForceMeasureAndLayout.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest033, TestSize.Level0)
{
    /**
     * @tc.steps: step1. call CreateLayoutWrapper create a layoutwrapper pointer.
     */
    RefPtr<LayoutWrapperNode> layoutWrapper = CreateLayoutWrapper(ROW_FRAME_NODE, NODE_ID_0);

    /**
     * @tc.steps: step2. create firstChildLayoutWrapper and append it to layoutWrapper.
     */
    RefPtr<LayoutWrapperNode> firstChildLayoutWrapper = CreateChildLayoutWrapper(FIRST_CHILD_FRAME_NODE, NODE_ID_1);
    layoutWrapper->AppendChild(firstChildLayoutWrapper);

    /**
     * @tc.steps: step3. call CheckChildNeedForceMeasureAndLayout.
     * @tc.expected: the return retCheck is true.
     */
    bool retCheck = layoutWrapper->CheckChildNeedForceMeasureAndLayout();
    EXPECT_TRUE(retCheck);
}

/**
 * @tc.name: LayoutWrapperTest034
 * @tc.desc: Test BuildLazyItem.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest034, TestSize.Level0)
{
    /**
     * @tc.steps: step1. call CreateLayoutWrapper create a layoutwrapper pointer.
     */
    RefPtr<LayoutWrapperNode> layoutWrapper = CreateLayoutWrapper(ROW_FRAME_NODE, NODE_ID_0);

    /**
     * @tc.steps: step2. set layoutWrapper->lazyBuildFunction_ is not null.
     */
    auto lazyBuildFunction = [](RefPtr<LayoutWrapperNode> testLayoutWrapper) { testLayoutWrapper = nullptr; };
    layoutWrapper->lazyBuildFunction_ = lazyBuildFunction;

    /**
     * @tc.steps: step3. call GetLazyBuildRange.
     * @tc.expected: the return retRange.first is -1 and retRange.second is 0.
     */
    layoutWrapper->BuildLazyItem();
    EXPECT_EQ(layoutWrapper->lazyBuildFunction_, nullptr);
}

/**
 * @tc.name: LayoutWrapperTest035
 * @tc.desc: Test GetLazyBuildRange.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest035, TestSize.Level0)
{
    /**
     * @tc.steps: step1. call CreateLayoutWrapper create a layoutwrapper pointer.
     */
    RefPtr<LayoutWrapperNode> layoutWrapper = CreateLayoutWrapper(ROW_FRAME_NODE, NODE_ID_0);

    /**
     * @tc.steps: step2. call GetLazyBuildRange.
     * @tc.expected: the return value is the same as RANGE.
     */
    std::pair<int32_t, int32_t> retRange = layoutWrapper->GetLazyBuildRange();
    EXPECT_EQ(retRange, RANGE);

    /**
     * @tc.steps: step3. create wrapperBuilder and set it to layoutWrapper->layoutWrapperBuilder_.
     */
    RefPtr<LazyLayoutWrapperBuilder> wrapperBuilder = CreateLayoutWrapperBuilder();
    layoutWrapper->layoutWrapperBuilder_ = wrapperBuilder;

    /**
     * @tc.steps: step4. call GetLazyBuildRange.
     * @tc.expected: the return value is the same as RANGE_0.
     */
    retRange = layoutWrapper->GetLazyBuildRange();
    EXPECT_EQ(retRange, RANGE_0);
}

/**
 * @tc.name: LayoutWrapperTest036
 * @tc.desc: Test Apply SafeArea constraint for Popup nodes.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest036, TestSize.Level0)
{
    auto [parentHost, parent] = CreateNodeAndWrapper(V2::ROOT_ETS_TAG, 0);
    auto [stageHost, stage] = CreateNodeAndWrapper(V2::STAGE_ETS_TAG, 1);
    auto [popupHost, popup] = CreateNodeAndWrapper(V2::MENU_WRAPPER_ETS_TAG, 2);
    parentHost->AddChild(stageHost);
    parentHost->AddChild(popupHost);
    popupHost->layoutProperty_->UpdateSafeAreaInsets(SafeAreaInsets({}, { 0, 1 }, {}, {}));

    LayoutConstraintF constraint;
    UpdateParentConstraint(parent, constraint);
    stage->ApplyConstraint(constraint);
    popup->ApplyConstraint(constraint);

    EXPECT_EQ(stage->layoutProperty_->layoutConstraint_, constraint);
    // popup is restricted by safeArea
    EXPECT_EQ(popup->geometryNode_->parentLayoutConstraint_, constraint);
    EXPECT_TRUE(popup->layoutProperty_->layoutConstraint_);
    EXPECT_NE(popup->layoutProperty_->layoutConstraint_, constraint);
}

/**
 * @tc.name: LayoutWrapperTest037
 * @tc.desc: Test OffsetNodeToSafeArea.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest037, TestSize.Level0)
{
    auto layoutWrapper = CreateLayoutWrapper(ROW_FRAME_NODE, NODE_ID_0);
    layoutWrapper->layoutProperty_->UpdateSafeAreaInsets(
        SafeAreaInsets({}, { 0, 1 }, {}, { RK356_HEIGHT - 1, RK356_HEIGHT }));
    layoutWrapper->geometryNode_->SetFrameSize({ RK356_WIDTH, RK356_HEIGHT - 2 });

    layoutWrapper->geometryNode_->SetFrameOffset({ 0, 1 });
    layoutWrapper->OffsetNodeToSafeArea();
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameOffset(), OffsetF(0, 1));

    layoutWrapper->geometryNode_->SetFrameOffset({ 0, 5 });
    layoutWrapper->OffsetNodeToSafeArea();
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameOffset(), OffsetF(0, 1));

    layoutWrapper->geometryNode_->SetFrameOffset({ 0, 0 });
    layoutWrapper->OffsetNodeToSafeArea();
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameOffset(), OffsetF(0, 1));

    layoutWrapper->layoutProperty_->UpdateSafeAreaInsets(
        SafeAreaInsets({ 0, 5 }, { 0, 1 }, {}, { RK356_HEIGHT - 1, RK356_HEIGHT }));
    layoutWrapper->geometryNode_->SetFrameOffset({ 0, 0 });
    layoutWrapper->OffsetNodeToSafeArea();
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameOffset(), OffsetF(0, 1));

    // set right and bottom again
    layoutWrapper->geometryNode_->SetFrameOffset({ 1, 1 });
    layoutWrapper->layoutProperty_->UpdateSafeAreaInsets(
        SafeAreaInsets({ 0, 0 }, { 0, 0 }, { RK356_HEIGHT, RK356_HEIGHT + 1 }, { RK356_HEIGHT, RK356_HEIGHT + 1 }));
    layoutWrapper->OffsetNodeToSafeArea();
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameOffset().x_, 1);
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameOffset().y_, 1);
}

/**
 * @tc.name: LayoutWrapperTest038
 * @tc.desc: Test ExpandIntoKeyboard.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest038, TestSize.Level0)
{
    auto [parent, layoutWrapper] = CreateNodeAndWrapper(ROW_FRAME_NODE, NODE_ID_0);
    layoutWrapper->layoutProperty_->UpdateSafeAreaExpandOpts({ SAFE_AREA_TYPE_ALL, SAFE_AREA_EDGE_ALL });

    auto [child, childWrapper] = CreateNodeAndWrapper(FIRST_CHILD_FRAME_NODE, NODE_ID_1);
    child->layoutProperty_->UpdateSafeAreaExpandOpts({ SAFE_AREA_TYPE_ALL, SAFE_AREA_EDGE_ALL });
    child->MountToParent(parent);

    auto safeAreaManager = PipelineContext::GetCurrentContext()->safeAreaManager_;
    // ExpandIntoKeyboard(): use page offset judge if expand intoKeyboard
    // no page node, return OffsetF(0, 0)
    safeAreaManager->UpdateKeyboardOffset(50.0f);
    EXPECT_EQ(parent->ExpandIntoKeyboard(), OffsetF(0, 0));

    // parent already expanded
    child->ExpandIntoKeyboard();
    EXPECT_EQ(child->ExpandIntoKeyboard(), OffsetF(0, 0));

    layoutWrapper->layoutProperty_->UpdateSafeAreaExpandOpts({ SAFE_AREA_TYPE_NONE, SAFE_AREA_EDGE_ALL });
    child->ExpandIntoKeyboard();
    // no page node, return OffsetF(0, 0)
    EXPECT_EQ(child->ExpandIntoKeyboard(), OffsetF(0, 0));
}

/**
 * @tc.name: LayoutWrapperTest039
 * @tc.desc: Test CreateRootConstraint.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest039, TestSize.Level0)
{
    auto context = PipelineContext::GetCurrentContext();
    context->rootHeight_ = RK356_HEIGHT;
    context->rootWidth_ = RK356_WIDTH;

    auto [node, layoutWrapper] = CreateNodeAndWrapper(ROW_FRAME_NODE, NODE_ID_0);
    layoutWrapper->geometryNode_->SetFrameSize({ RK356_WIDTH, RK356_HEIGHT });
    layoutWrapper->layoutProperty_->UpdateAspectRatio(2.0);
    layoutWrapper->CreateRootConstraint();
    EXPECT_EQ(layoutWrapper->layoutProperty_->layoutConstraint_->percentReference.Height(), RK356_HEIGHT / 2);
}

/**
 * @tc.name: LayoutWrapperTest040
 * @tc.desc: Test AvoidKeyboard.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest040, TestSize.Level0)
{
    auto [parent, layoutWrapper] = CreateNodeAndWrapper(OHOS::Ace::V2::FLEX_ETS_TAG, NODE_ID_0);

    /**
     * @tc.steps: step1. call AddNodeFlexLayouts on a frame with parent JS_VIEW_ETS_TAG.
     * @tc.expected:
     */
    auto [node1, nodeLayoutWrapper1] = CreateNodeAndWrapper(OHOS::Ace::V2::JS_VIEW_ETS_TAG, NODE_ID_1);
    node1->MountToParent(parent);

    auto [child, childWrapper] = CreateNodeAndWrapper(FIRST_CHILD_FRAME_NODE, NODE_ID_2);
    child->MountToParent(node1);
    childWrapper->AddNodeFlexLayouts();
    EXPECT_EQ(node1->GetFlexLayouts(), 0);

    /**
     * @tc.steps: step2. call AddNodeFlexLayouts on a frame with parent COMMON_VIEW_ETS_TAG.
     * @tc.expected:
     */
    auto [child2, childWrapper2] = CreateNodeAndWrapper(FIRST_CHILD_FRAME_NODE, NODE_ID_3);
    child2->MountToParent(child);
    node1->tag_ = OHOS::Ace::V2::COMMON_VIEW_ETS_TAG;
    childWrapper->AddNodeFlexLayouts();
    EXPECT_EQ(child2->GetFlexLayouts(), 0);

    /**
     * @tc.steps: step3. call AddNodeFlexLayouts on a frame with parent ROW_FRAME_NODE.
     * @tc.expected:
     */
    node1->tag_ = ROW_FRAME_NODE;
    childWrapper->AddNodeFlexLayouts();
    EXPECT_EQ(child->GetFlexLayouts(), 0);
}

/**
 * @tc.name: LayoutWrapperTest041
 * @tc.desc: Test AdjustChildren.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest041, TestSize.Level0)
{
    /**
     * @tc.steps: step1. rowFrameNode addChildren .
     */
    auto rowFrameNode = FrameNode::CreateFrameNode(
        OHOS::Ace::V2::FLEX_ETS_TAG, NODE_ID_0, AceType::MakeRefPtr<LinearLayoutPattern>(false));

    auto rowFrameNode1 = FrameNode::CreateFrameNode(
        OHOS::Ace::V2::FLEX_ETS_TAG, NODE_ID_1, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<CustomNode> cusNodeTemp = AceType::MakeRefPtr<CustomNode>(NODE_ID_2, OHOS::Ace::V2::FLEX_ETS_TAG);
    rowFrameNode->AddChild(cusNodeTemp);
    rowFrameNode->AddChild(rowFrameNode1);

    /**
     * @tc.steps: step2. create LayoutWrapper.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step3. Call AdjustChildren().
     */
    layoutWrapper->AdjustChildren(OffsetF(0, 10), false);
    EXPECT_FALSE(rowFrameNode1->GetLayoutProperty()->GetSafeAreaExpandOpts());
}

/**
 * @tc.name: LayoutWrapperTest042
 * @tc.desc: Test AvoidKeyboard.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest042, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create LayoutWrapper.
     */
    auto node = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, NODE_ID_0, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(node, geometryNode, node->GetLayoutProperty());

    /**
     * @tc.steps: step2. Call AvoidKeyboard.
     * @tc.expected: GetHostTag() != V2::PAGE_ETS_TAG.
     */
    layoutWrapper->AvoidKeyboard();
    EXPECT_NE(layoutWrapper->GetHostTag(), V2::PAGE_ETS_TAG);
}

/**
 * @tc.name: LayoutWrapperTest043
 * @tc.desc: Test AvoidKeyboard.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest043, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create LayoutWrapper.
     */
    auto node = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, NODE_ID_0, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    RefPtr<FocusHub> focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusHub->currentFocus_ = false;
    node->focusHub_ = focusHub;
    node->eventHub_ = eventHub;

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(node, geometryNode, node->GetLayoutProperty());

    /**
     * @tc.steps: step2. create safeAreaManager_.
     */
    RefPtr<SafeAreaManager> safeAreamanager = AceType::MakeRefPtr<SafeAreaManager>();
    safeAreamanager->keyboardOffset_ = -1.0f;

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->safeAreaManager_ = safeAreamanager;

    /**
     * @tc.steps: step3. Call AvoidKeyboard.
     */
    layoutWrapper->AvoidKeyboard();
    EXPECT_TRUE(node->GetFocusHub());
    EXPECT_TRUE(!node->GetFocusHub()->IsCurrentFocus());
    EXPECT_TRUE(LessNotEqual(safeAreamanager->GetKeyboardOffset(), 0.0));
}

/**
 * @tc.name: LayoutWrapperTest044
 * @tc.desc: Test AddNodeFlexLayouts.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest044, TestSize.Level0)
{
    auto [parent, layoutWrapper] = CreateNodeAndWrapper(OHOS::Ace::V2::FLEX_ETS_TAG, NODE_ID_0);

    /**
     * @tc.steps: step1. call AddNodeFlexLayouts on a frame with parent JS_VIEW_ETS_TAG.
     * @tc.expected:
     */
    auto [node1, nodeLayoutWrapper1] = CreateNodeAndWrapper(OHOS::Ace::V2::JS_VIEW_ETS_TAG, NODE_ID_1);
    node1->MountToParent(parent);

    auto [child, childWrapper] = CreateNodeAndWrapper(FIRST_CHILD_FRAME_NODE, NODE_ID_2);
    child->MountToParent(node1);
    childWrapper->AddNodeFlexLayouts();
    EXPECT_EQ(node1->GetFlexLayouts(), 0);

    /**
     * @tc.steps: step2. call AddNodeFlexLayouts on a frame with parent COMMON_VIEW_ETS_TAG.
     * @tc.expected:
     */
    auto [child2, childWrapper2] = CreateNodeAndWrapper(FIRST_CHILD_FRAME_NODE, NODE_ID_3);
    child2->MountToParent(child);
    node1->tag_ = OHOS::Ace::V2::COMMON_VIEW_ETS_TAG;
    childWrapper->AddNodeFlexLayouts();
    EXPECT_EQ(child2->GetFlexLayouts(), 0);

    /**
     * @tc.steps: step3. call AddNodeFlexLayouts on a frame with parent ROW_FRAME_NODE.
     * @tc.expected:
     */
    node1->tag_ = ROW_FRAME_NODE;
    childWrapper->AddNodeFlexLayouts();
    EXPECT_EQ(child->GetFlexLayouts(), 0);
}
} // namespace OHOS::Ace::NG