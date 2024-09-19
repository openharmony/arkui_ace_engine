/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "tabs_test_ng.h"

#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class TabBarLayoutTestNg : public TabsTestNg {
public:
};

/**
 * @tc.name: TabBarPatternOnDirtyLayoutWrapperSwap001
 * @tc.desc: test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarPatternOnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetFadingEdge(true);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
    DirtySwapConfig config;
    tabBarPattern_->OnDirtyLayoutWrapperSwap(frameNode_, config);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
    /**
     * @tc.steps: step2. creat different conditions and invoke OnDirtyLayoutWrapperSwap.
     * @tc.expected: step2. expect The function is run ok.
     */
    config.skipMeasure = true;
    EXPECT_FALSE(tabBarPattern_->OnDirtyLayoutWrapperSwap(frameNode_, config));

    config.skipLayout = true;
    EXPECT_FALSE(tabBarPattern_->OnDirtyLayoutWrapperSwap(frameNode_, config));

    config.skipMeasure = false;
    EXPECT_FALSE(tabBarPattern_->OnDirtyLayoutWrapperSwap(frameNode_, config));

    tabBarPattern_->isAnimating_ = true;
    EXPECT_FALSE(tabBarPattern_->OnDirtyLayoutWrapperSwap(frameNode_, config));
    EXPECT_EQ(tabBarPattern_->isAnimating_, true);
}

/**
 * @tc.name: TabBarLayoutAlgorithmLayoutMask001
 * @tc.desc: test LayoutMask
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmLayoutMask001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call UpdateSelectedMask and UpdateUnselectedMask.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    TabsItemDivider divider;
    model.SetDivider(divider);
    CreateTabsDone(model);

    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    tabBarLayoutProperty_->UpdateSelectedMask(0);
    tabBarLayoutProperty_->UpdateUnselectedMask(1);
    std::map<int32_t, OffsetF> childOffsetDelta;
    childOffsetDelta[0] = OffsetF();
    childOffsetDelta[1] = OffsetF();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarLayoutProperty_);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));

    /**
     * @tc.steps: step2. build selectedMaskNode and unselectedMaskNode.
     */
    auto selectedmaskPosition = tabBarNode_->GetChildren().size() - TEST_SELECTED_MASK_COUNT;
    auto selectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(selectedmaskPosition));
    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> selectedMaskLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(selectedMaskNode, geometryNode1, selectedMaskNode->GetLayoutProperty());
    layoutWrapper.AppendChild(selectedMaskLayoutWrapper);

    auto unselectedmaskPosition = tabBarNode_->GetChildren().size() - TEST_UNSELECTED_MASK_COUNT;
    auto unselectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(unselectedmaskPosition));
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    auto unselectedProperty = unselectedMaskNode->GetLayoutProperty();
    RefPtr<LayoutWrapperNode> unselectedMaskLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(unselectedMaskNode, geometryNode2, unselectedProperty);
    layoutWrapper.AppendChild(unselectedMaskLayoutWrapper);

    /**
     * @tc.steps: step3. call LayoutMask function.
     * @tc.expected: step3. expect The function is run ok.
     */
    tabBarLayoutAlgorithm->LayoutMask(&layoutWrapper, childOffsetDelta);
    EXPECT_EQ(tabBarLayoutProperty_->GetSelectedMask().value_or(-1), 0);
    EXPECT_EQ(tabBarLayoutProperty_->GetUnselectedMask().value_or(-1), 1);
}

/**
 * @tc.name: TabBarLayoutAlgorithmLayoutMask002
 * @tc.desc: test LayoutMask
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmLayoutMask002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    TabsItemDivider divider;
    model.SetDivider(divider);
    CreateTabsDone(model);

    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));

    auto selectedmaskPosition = tabBarNode_->GetChildren().size() - TEST_SELECTED_MASK_COUNT;
    auto selectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(selectedmaskPosition));
    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> selectedMaskLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(selectedMaskNode, geometryNode1, selectedMaskNode->GetLayoutProperty());
    layoutWrapper.AppendChild(selectedMaskLayoutWrapper);

    auto unselectedmaskPosition = tabBarNode_->GetChildren().size() - TEST_UNSELECTED_MASK_COUNT;
    auto unselectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(unselectedmaskPosition));
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    auto unselectedProperty = unselectedMaskNode->GetLayoutProperty();
    RefPtr<LayoutWrapperNode> unselectedMaskLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(unselectedMaskNode, geometryNode2, unselectedProperty);
    layoutWrapper.AppendChild(unselectedMaskLayoutWrapper);

    /**
     * @tc.steps: step2. call LayoutMask function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarLayoutAlgorithm->LayoutMask(&layoutWrapper, {});
    EXPECT_EQ(tabBarLayoutProperty_->GetSelectedMask().value_or(-1), -1);
    EXPECT_EQ(tabBarLayoutProperty_->GetUnselectedMask().value_or(-1), -1);
}

/**
 * @tc.name: TabBarLayoutAlgorithmLayoutMask004
 * @tc.desc: Test the LayoutMask function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmLayoutMask004, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    TabsItemDivider divider;
    model.SetDivider(divider);
    CreateTabsDone(model);
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    tabBarLayoutProperty_->UpdateSelectedMask(0);
    tabBarLayoutProperty_->UpdateUnselectedMask(1);
    std::map<int32_t, OffsetF> childOffsetDelta;
    childOffsetDelta[0] = OffsetF();
    childOffsetDelta[1] = OffsetF();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarLayoutProperty_);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));

    /**
     * @tc.steps: step2. build selectedMaskNode and unselectedMaskNode.
     */
    auto selectedmaskPosition = tabBarNode_->GetChildren().size() - TEST_SELECTED_MASK_COUNT;
    auto selectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(selectedmaskPosition));
    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> selectedMaskLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(selectedMaskNode, geometryNode1, selectedMaskNode->GetLayoutProperty());
    layoutWrapper.AppendChild(selectedMaskLayoutWrapper);

    auto unselectedmaskPosition = tabBarNode_->GetChildren().size() - TEST_UNSELECTED_MASK_COUNT;
    auto unselectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(unselectedmaskPosition));
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    auto unselectedProperty = unselectedMaskNode->GetLayoutProperty();
    RefPtr<LayoutWrapperNode> unselectedMaskLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(unselectedMaskNode, geometryNode2, unselectedProperty);
    layoutWrapper.AppendChild(unselectedMaskLayoutWrapper);

    /**
     * @tc.steps: steps3. Create a child named imageLayoutWrapper for currentWrapper.
     */
    auto currentWrapper = selectedMaskLayoutWrapper;
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    RefPtr<GeometryNode> geometryNode5 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> imageLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(imageNode, geometryNode5, imageNode->GetLayoutProperty());
    auto imageLayoutProperty = AceType::DynamicCast<ImageLayoutProperty>(imageLayoutWrapper->GetLayoutProperty());
    selectedMaskLayoutWrapper->AppendChild(imageLayoutWrapper);

    /**
     * @tc.steps: step4. call LayoutMask function.
     * @tc.expected: step4. expect The function is run ok.
     */
    tabBarLayoutAlgorithm->LayoutMask(&layoutWrapper, childOffsetDelta);
    EXPECT_EQ(tabBarLayoutProperty_->GetSelectedMask().value_or(-1), 0);
    EXPECT_EQ(tabBarLayoutProperty_->GetUnselectedMask().value_or(-1), 1);
}

/**
 * @tc.name: TabBarLayoutAlgorithmGetGridWidth001
 * @tc.desc: Test the GetGridWidth function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmGetGridWidth001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    tabBarPattern_->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode_->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());

    /**
     * @tc.steps: steps2. Create different conditions for GetGridWidth.
     */
    int32_t columns = -10;
    auto frameSize = SizeF(1.0f, 1.0f);
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(tabBarNode_->GetLayoutProperty());
    BarGridColumnOptions option;
    float resultWidth1 = tabbarLayoutAlgorithm->GetGridWidth(option, frameSize, columns);
    columns = 10;
    float resultWidth2 = tabbarLayoutAlgorithm->GetGridWidth(option, frameSize, columns);

    /**
     * @tc.steps: steps3. GetGridWidth.
     * @tc.expected: steps3. expect The function is run ok.
     */
    EXPECT_EQ(resultWidth1, 0.0f);
    EXPECT_EQ(resultWidth2, columns * frameSize.Width() / XS_COLUMN_NUM);
}

/**
 * @tc.name: TabBarLayoutAlgorithmApplyBarGridAlign001
 * @tc.desc: Test the ApplyBarGridAlign function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmApplyBarGridAlign001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    tabBarPattern_->tabBarStyle_ = TabBarStyle::BOTTOMTABBATSTYLE;
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode_->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());
    auto tabBarProperty = tabBarLayoutProperty_;

    /**
     * @tc.steps: steps2. Create different conditions for ApplyBarGridAlign.
     */
    BarGridColumnOptions option;
    option.sm = 6;
    tabBarLayoutProperty_->UpdateBarGridAlign(option);
    auto frameSize = SizeF(400.0f, 400.0f);
    float result1 = tabbarLayoutAlgorithm->ApplyBarGridAlign(tabBarProperty, frameSize);
    option.md = 10;
    tabBarLayoutProperty_->UpdateBarGridAlign(option);
    frameSize = SizeF(800.0f, 800.0f);
    float result2 = tabbarLayoutAlgorithm->ApplyBarGridAlign(tabBarProperty, frameSize);
    option.lg = 16;
    tabBarLayoutProperty_->UpdateBarGridAlign(option);
    frameSize = SizeF(1000.0f, 1000.0f);
    float result3 = tabbarLayoutAlgorithm->ApplyBarGridAlign(tabBarProperty, frameSize);
    option.lg = -2;
    tabBarLayoutProperty_->UpdateBarGridAlign(option);
    float result4 = tabbarLayoutAlgorithm->ApplyBarGridAlign(tabBarProperty, frameSize);
    option.lg = 2;
    tabBarLayoutProperty_->UpdateBarGridAlign(option);
    float result5 = tabbarLayoutAlgorithm->ApplyBarGridAlign(tabBarProperty, frameSize);

    /**
     * @tc.steps: steps3. ApplyBarGridAlign.
     * @tc.expected: steps3. Cexpect The function is run ok.
     */
    EXPECT_EQ(result1, 0.0f);
    EXPECT_EQ(result2, 0.0f);
    EXPECT_EQ(result3, 0.0f);
    EXPECT_EQ(result4, 0.0f);
    float columnWidth = frameSize.Width() / LG_COLUMN_NUM;
    float expectedWidth = (LG_COLUMN_NUM - option.lg) * columnWidth / 2;
    EXPECT_EQ(NearEqual(result5, expectedWidth), true);
}

/**
 * @tc.name: TabBarLayoutAlgorithmApplyLayoutMode001
 * @tc.desc: Test the ApplyLayoutMode function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmApplyLayoutMode001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode_->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);
    auto bottomTabBarStyle = tabBarPattern_->GetBottomTabBarStyle(0);

    /**
     * @tc.steps: steps2. Create two children named columnLayoutWrapper and columnLayoutWrapper1 for layoutWrapper.
     */
    auto columnNode1 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> columnLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode1, geometryNode3, columnNode1->GetLayoutProperty());
    columnLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    columnLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(columnLayoutWrapper);
    auto columnNode2 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<GeometryNode> geometryNode4 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> columnLayoutWrapper1 =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode2, geometryNode4, columnNode2->GetLayoutProperty());
    columnLayoutWrapper1->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    columnLayoutWrapper1->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(columnLayoutWrapper1);
    auto linearLayoutProperty = AceType::DynamicCast<LinearLayoutProperty>(columnLayoutWrapper->GetLayoutProperty());

    /**
     * @tc.steps: steps3. Using a loop to create two children named textLayoutWrapper for columnLayoutWrapper.
     */
    for (int32_t i = 0; i < 2; i++) {
        auto textId = ElementRegister::GetInstance()->MakeUniqueId();
        auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, textId, AceType::MakeRefPtr<TextPattern>());
        RefPtr<GeometryNode> geometryNode5 = AceType::MakeRefPtr<GeometryNode>();
        RefPtr<LayoutWrapperNode> textLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(textNode, geometryNode5, textNode->GetLayoutProperty());
        columnLayoutWrapper->AppendChild(textLayoutWrapper);
    }
    float allocatedWidth = 0.0f;
    tabbarLayoutAlgorithm->childCount_ = 2;

    /**
     * @tc.steps: steps4. ApplyLayoutMode.
     * @tc.expected: steps4. Create different conditions and check the result of ApplyLayoutMode.
     */
    bottomTabBarStyle.layoutMode = LayoutMode::VERTICAL;
    tabBarPattern_->SetBottomTabBarStyle(bottomTabBarStyle, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabbarLayoutAlgorithm->ApplyLayoutMode(&layoutWrapper, allocatedWidth);
    bottomTabBarStyle.layoutMode = LayoutMode::AUTO;
    tabBarPattern_->SetBottomTabBarStyle(bottomTabBarStyle, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 1);
    tabbarLayoutAlgorithm->ApplyLayoutMode(&layoutWrapper, allocatedWidth);
    allocatedWidth = 200000.0f;
    tabbarLayoutAlgorithm->ApplyLayoutMode(&layoutWrapper, allocatedWidth);
    EXPECT_FALSE(linearLayoutProperty->IsVertical());
}

/**
 * @tc.name: TabBarLayoutAlgorithmLayoutChildren001
 * @tc.desc: Test the LayoutChildren function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmLayoutChildren001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));

    for (int32_t i = 0; i < 2; i++) {
        auto columnNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
            RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
        RefPtr<LayoutWrapperNode> columnLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(columnNode, geometryNode2, columnNode->GetLayoutProperty());
        columnLayoutWrapper->GetGeometryNode()->SetFrameSize(FIRST_ITEM_SIZE);
        layoutWrapper.AppendChild(columnLayoutWrapper);
    }

    /**
     * @tc.steps: steps2. LayoutChildren.
     * @tc.expected: steps2. Verify childOffset under LayoutChildren Value of.
     */
    tabbarLayoutAlgorithm->axis_ = Axis::HORIZONTAL;
    tabbarLayoutAlgorithm->visibleItemPosition_[0] = { 0.0f, FIRST_ITEM_WIDTH };
    tabbarLayoutAlgorithm->visibleItemPosition_[1] = { FIRST_ITEM_WIDTH, FIRST_ITEM_WIDTH * 2 };
    auto frameSize = SizeF(0.0f, 0.0f);

    OffsetF childOffset(0.0f, 0.0f);
    tabbarLayoutAlgorithm->LayoutChildren(&layoutWrapper, frameSize, childOffset);
    EXPECT_EQ(childOffset.GetX(), FIRST_ITEM_WIDTH * 2);
}

/**
 * @tc.name: TabBarLayoutAlgorithmLayoutChildren002
 * @tc.desc: Test the LayoutChildren function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmLayoutChildren002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));

    for (int32_t i = 0; i < 2; i++) {
        auto columnNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
            RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
        RefPtr<LayoutWrapperNode> columnLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(columnNode, geometryNode2, columnNode->GetLayoutProperty());
        columnLayoutWrapper->GetGeometryNode()->SetFrameSize(FIRST_ITEM_SIZE);
        layoutWrapper.AppendChild(columnLayoutWrapper);
    }

    /**
     * @tc.steps: steps2. LayoutChildren.
     * @tc.expected: steps2. Verify childOffset under LayoutChildren Value of.
     */
    tabbarLayoutAlgorithm->axis_ = Axis::HORIZONTAL;
    tabbarLayoutAlgorithm->isRTL_ = true;
    tabbarLayoutAlgorithm->visibleItemPosition_[0] = { 0.0f, FIRST_ITEM_WIDTH };
    tabbarLayoutAlgorithm->visibleItemPosition_[1] = { FIRST_ITEM_WIDTH, FIRST_ITEM_WIDTH * 2 };
    auto frameSize = SizeF(0.0f, 0.0f);
    OffsetF childOffset(FIRST_ITEM_WIDTH * 2, 0.0f);
    tabbarLayoutAlgorithm->LayoutChildren(&layoutWrapper, frameSize, childOffset);
    EXPECT_EQ(childOffset.GetX(), 0.0f);
}

/**
 * @tc.name: TabBarLayoutAlgorithmGetContentMainSize001
 * @tc.desc: Test the GetContentMainSize function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmGetContentMainSize001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    tabBarPattern_->tabBarStyle_ = TabBarStyle::BOTTOMTABBATSTYLE;
    auto tabBarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));
    auto frameSize = SizeF(1200.0f, 1200.0f);

    /**
     * @tc.steps: steps2. Create padding by UpdateBarGridAlign.
     */
    BarGridColumnOptions option;
    option.lg = 2;
    tabBarLayoutProperty_->UpdateBarGridAlign(option);

    /**
     * @tc.steps: steps3. GetContentMainSize.
     * @tc.expected: steps3. Check the result of GetContentMainSize.
     */
    tabBarLayoutAlgorithm->axis_ = Axis::HORIZONTAL;
    float resultWidth = tabBarLayoutAlgorithm->GetContentMainSize(&layoutWrapper, frameSize);
    float columnWidth = frameSize.Width() / LG_COLUMN_NUM;
    float padding = (LG_COLUMN_NUM - option.lg) * columnWidth / 2;
    EXPECT_EQ(resultWidth, frameSize.Width() - padding * 2);

    tabBarLayoutAlgorithm->axis_ = Axis::VERTICAL;
    resultWidth = tabBarLayoutAlgorithm->GetContentMainSize(&layoutWrapper, frameSize);
    EXPECT_EQ(resultWidth, frameSize.Height());
}

/**
 * @tc.name: TabBarLayoutAlgorithmApplySymmetricExtensible001
 * @tc.desc: Test the ApplySymmetricExtensible function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmApplySymmetricExtensible001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    TabsItemDivider divider;
    model.SetDivider(divider);
    CreateTabsDone(model);
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    /**
     * @tc.steps: steps2. Create three children named columnLayoutWrapper1, columnLayoutWrapper2,
     *                    and columnLayoutWrapper3 for layoutWrapper in sequence.
     */
    auto columnNode1 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> columnLayoutWrapper1 =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode1, geometryNode2, columnNode1->GetLayoutProperty());
    columnLayoutWrapper1->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    columnLayoutWrapper1->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(columnLayoutWrapper1);
    auto linearLayoutProperty = AceType::DynamicCast<LinearLayoutProperty>(columnLayoutWrapper1->GetLayoutProperty());
    auto columnNode2 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> columnLayoutWrapper2 =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode2, geometryNode3, columnNode2->GetLayoutProperty());
    columnLayoutWrapper2->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    columnLayoutWrapper2->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(columnLayoutWrapper2);
    auto columnNode3 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<GeometryNode> geometryNode7 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> columnLayoutWrapper3 =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode3, geometryNode7, columnNode3->GetLayoutProperty());
    columnLayoutWrapper3->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    columnLayoutWrapper3->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(columnLayoutWrapper3);

    /**
     * @tc.steps: steps3. Test ApplySymmetricExtensible by using different conditions.
     */
    float allocatedWidth = 0.0f;
    tabBarLayoutAlgorithm->childCount_ = 1;
    tabBarLayoutAlgorithm->visibleItemLength_.clear();
    tabBarLayoutAlgorithm->visibleItemLength_[0] = 1000.0f;
    tabBarLayoutAlgorithm->visibleItemLength_[1] = 2000.0f;
    tabBarLayoutAlgorithm->visibleItemLength_[2] = 3000.0f;
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth);
    EXPECT_NE(tabBarLayoutAlgorithm->visibleItemLength_.size(), 1);
    tabBarLayoutAlgorithm->visibleItemLength_.clear();
    tabBarLayoutAlgorithm->visibleItemLength_[0] = 1000.0f;
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth);
    EXPECT_EQ(tabBarLayoutAlgorithm->visibleItemLength_.size(), 1);
    tabBarLayoutAlgorithm->childCount_ = 3;
    tabBarLayoutAlgorithm->visibleItemLength_.clear();
    tabBarLayoutAlgorithm->visibleItemLength_[0] = 1000.0f;
    tabBarLayoutAlgorithm->visibleItemLength_[1] = 2000.0f;
    tabBarLayoutAlgorithm->visibleItemLength_[2] = 3000.0f;
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth);
    EXPECT_EQ(tabBarLayoutAlgorithm->visibleItemLength_.size(), 3);
    tabBarLayoutAlgorithm->visibleItemLength_.clear();
    tabBarLayoutAlgorithm->visibleItemLength_[0] = 1000.0f;
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth);
    EXPECT_EQ(tabBarLayoutAlgorithm->visibleItemLength_.size(), 1);
    tabBarLayoutAlgorithm->visibleItemLength_.clear();
    tabBarLayoutAlgorithm->visibleItemLength_[0] = 1000.0f;
    tabBarLayoutAlgorithm->visibleItemLength_[1] = 2000.0f;
    tabBarLayoutAlgorithm->visibleItemLength_[2] = 3000.0f;

    /**
     * @tc.steps: steps4. ApplySymmetricExtensible.
     * @tc.expected: steps4. Check the result of ApplySymmetricExtensible.
     */
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    linearLayoutProperty->UpdateFlexDirection(FlexDirection::ROW_REVERSE);
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    linearLayoutProperty->UpdateFlexDirection(FlexDirection::COLUMN);
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth);
    allocatedWidth = 100000.0f;
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    linearLayoutProperty->UpdateFlexDirection(FlexDirection::COLUMN);
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth);
    EXPECT_EQ(tabBarLayoutAlgorithm->visibleItemLength_[0], allocatedWidth);
}

/**
 * @tc.name: TabBarLayoutAlgorithmCalculateItemWidthsForSymmetricExtensible001
 * @tc.desc: Test the CalculateItemWidthsForSymmetricExtensible function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmCalculateItemWidthsForSymmetricExtensible001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    TabsItemDivider divider;
    model.SetDivider(divider);
    CreateTabsDone(model);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    /**
     * @tc.steps: steps2. Create a child for layoutWrapper.
     */
    auto columnNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> columnLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode, geometryNode2, columnNode->GetLayoutProperty());
    columnLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    columnLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(columnLayoutWrapper);

    /**
     * @tc.steps: steps3. Create a first child named imageLayoutWrapper for columnLayoutWrapper.
     */
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    RefPtr<GeometryNode> geometryNode5 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> imageLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(imageNode, geometryNode5, imageNode->GetLayoutProperty());
    auto imageLayoutProperty = AceType::DynamicCast<ImageLayoutProperty>(imageLayoutWrapper->GetLayoutProperty());
    columnLayoutWrapper->AppendChild(imageLayoutWrapper);

    /**
     * @tc.steps: steps4. Create a second child named textLayoutWrapper for columnLayoutWrapper.
     */
    auto linearLayoutProperty = AceType::DynamicCast<LinearLayoutProperty>(columnLayoutWrapper->GetLayoutProperty());
    auto textId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, textId, AceType::MakeRefPtr<TextPattern>());
    RefPtr<GeometryNode> geometryNode4 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> textLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textNode, geometryNode4, textNode->GetLayoutProperty());
    columnLayoutWrapper->AppendChild(textLayoutWrapper);

    float allocatedWidth = 0.0f;
    tabBarLayoutAlgorithm->childCount_ = 2;

    /**
     * @tc.steps: steps5. Test CalculateItemWidthsForSymmetricExtensible by using different conditions.
     */
    tabBarLayoutAlgorithm->visibleItemLength_.clear();
    tabBarLayoutAlgorithm->visibleItemLength_[0] = 10.0f;
    std::vector<float> spaceRequests;
    spaceRequests.clear();
    spaceRequests.emplace_back(10.0f);
    std::vector<float> leftBuffers;
    leftBuffers.clear();
    leftBuffers.emplace_back(10.0f);
    std::vector<float> rightBuffers;
    rightBuffers.clear();
    rightBuffers.emplace_back(10.0f);
    tabBarLayoutAlgorithm->CalculateItemWidthsForSymmetricExtensible(
        &layoutWrapper, spaceRequests, leftBuffers, rightBuffers, allocatedWidth);
    tabBarLayoutAlgorithm->visibleItemLength_.clear();
    tabBarLayoutAlgorithm->visibleItemLength_[0] = 100.0f;
    tabBarLayoutAlgorithm->visibleItemLength_[1] = 100.0f;
    spaceRequests.clear();
    spaceRequests.emplace_back(100.0f);
    spaceRequests.emplace_back(100.0f);
    leftBuffers.clear();
    leftBuffers.emplace_back(100.0f);
    leftBuffers.emplace_back(100.0f);
    rightBuffers.clear();
    rightBuffers.emplace_back(100.0f);
    rightBuffers.emplace_back(100.0f);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarLayoutAlgorithm->CalculateItemWidthsForSymmetricExtensible(
        &layoutWrapper, spaceRequests, leftBuffers, rightBuffers, allocatedWidth);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 1);
    tabBarLayoutAlgorithm->CalculateItemWidthsForSymmetricExtensible(
        &layoutWrapper, spaceRequests, leftBuffers, rightBuffers, allocatedWidth);
    spaceRequests.clear();
    spaceRequests.emplace_back(0.0f);
    spaceRequests.emplace_back(0.0f);
    leftBuffers.clear();
    leftBuffers.emplace_back(100.0f);
    leftBuffers.emplace_back(100.0f);
    rightBuffers.clear();
    rightBuffers.emplace_back(100.0f);
    rightBuffers.emplace_back(100.0f);
    tabBarLayoutAlgorithm->CalculateItemWidthsForSymmetricExtensible(
        &layoutWrapper, spaceRequests, leftBuffers, rightBuffers, allocatedWidth);
    leftBuffers.clear();
    leftBuffers.emplace_back(0.0f);
    leftBuffers.emplace_back(0.0f);
    rightBuffers.clear();
    rightBuffers.emplace_back(0.0f);
    rightBuffers.emplace_back(0.0f);

    /**
     * @tc.steps: steps6. CalculateItemWidthsForSymmetricExtensible.
     * @tc.expected: steps6. erify itemWidths in CalculateItemWidthsForSymmetricExtensible Value of.
     */
    tabBarLayoutAlgorithm->CalculateItemWidthsForSymmetricExtensible(
        &layoutWrapper, spaceRequests, leftBuffers, rightBuffers, allocatedWidth);
    EXPECT_EQ(tabBarLayoutAlgorithm->visibleItemLength_[0], 0.0f);
}

/**
 * @tc.name: TabBarLayoutAlgorithmApplySymmetricExtensible002
 * @tc.desc: Test the ApplySymmetricExtensible function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmApplySymmetricExtensible002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));
    tabBarLayoutAlgorithm->visibleItemLength_.clear();
    tabBarLayoutAlgorithm->visibleItemLength_[0] = 1000.0f;
    tabBarLayoutAlgorithm->visibleItemLength_[1] = 12000.0f;
    tabBarLayoutAlgorithm->visibleItemLength_[2] = 13000.0f;
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    /**
     * @tc.steps: steps2. Create three children for layoutWrapper in sequence.
     */
    auto columnNode1 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> columnLayoutWrapper1 =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode1, geometryNode2, columnNode1->GetLayoutProperty());
    columnLayoutWrapper1->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    columnLayoutWrapper1->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(columnLayoutWrapper1);
    auto columnNode2 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> columnLayoutWrapper2 =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode2, geometryNode3, columnNode2->GetLayoutProperty());
    columnLayoutWrapper2->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    columnLayoutWrapper2->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(columnLayoutWrapper2);
    auto columnNode3 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<GeometryNode> geometryNode7 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> columnLayoutWrapper3 =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode3, geometryNode7, columnNode3->GetLayoutProperty());
    columnLayoutWrapper3->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    columnLayoutWrapper3->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(columnLayoutWrapper3);
    auto linearLayoutProperty = AceType::DynamicCast<LinearLayoutProperty>(columnLayoutWrapper1->GetLayoutProperty());

    /**
     * @tc.steps: steps3. ApplySymmetricExtensible.
     * @tc.expected: steps3. Check the value of itemWidths under the ApplySymmetricExtensible function.
     */
    float allocatedWidth = 0.0f;
    tabBarLayoutAlgorithm->childCount_ = 3;
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth);
    EXPECT_EQ(tabBarLayoutAlgorithm->visibleItemLength_[0], 0.0f);
}

/**
 * @tc.name: TabBarLayoutAlgorithmCalculateItemWidthsForSymmetricExtensible002
 * @tc.desc: Test the CalculateItemWidthsForSymmetricExtensible function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmCalculateItemWidthsForSymmetricExtensible002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    TabsItemDivider divider;
    model.SetDivider(divider);
    CreateTabsDone(model);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    /**
     * @tc.steps: steps2. Create a child for layoutWrapper.
     */
    auto columnNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> columnLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode, geometryNode2, columnNode->GetLayoutProperty());
    columnLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    columnLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(columnLayoutWrapper);

    /**
     * @tc.steps: steps3. Create a first child named imageLayoutWrapper for columnLayoutWrapper.
     */
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    RefPtr<GeometryNode> geometryNode5 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> imageLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(imageNode, geometryNode5, imageNode->GetLayoutProperty());
    auto imageLayoutProperty = AceType::DynamicCast<ImageLayoutProperty>(imageLayoutWrapper->GetLayoutProperty());
    columnLayoutWrapper->AppendChild(imageLayoutWrapper);

    /**
     * @tc.steps: steps4. Create a second child named textLayoutWrapper for columnLayoutWrapper.
     */
    auto linearLayoutProperty = AceType::DynamicCast<LinearLayoutProperty>(columnLayoutWrapper->GetLayoutProperty());
    auto textId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, textId, AceType::MakeRefPtr<TextPattern>());
    RefPtr<GeometryNode> geometryNode4 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> textLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textNode, geometryNode4, textNode->GetLayoutProperty());
    columnLayoutWrapper->AppendChild(textLayoutWrapper);

    /**
     * @tc.steps: steps5. Test CalculateItemWidthsForSymmetricExtensible by using different conditions.
     */
    float allocatedWidth = 100.0f;
    tabBarLayoutAlgorithm->childCount_ = 2;
    std::vector<float> spaceRequests;
    std::vector<float> leftBuffers;
    std::vector<float> rightBuffers;
    tabBarLayoutAlgorithm->visibleItemLength_.clear();
    tabBarLayoutAlgorithm->visibleItemLength_[0] = 100.0f;
    tabBarLayoutAlgorithm->visibleItemLength_[1] = 100.0f;
    spaceRequests.clear();
    spaceRequests.emplace_back(100.0f);
    spaceRequests.emplace_back(100.0f);
    leftBuffers.clear();
    leftBuffers.emplace_back(100.0f);
    leftBuffers.emplace_back(100.0f);
    rightBuffers.clear();
    rightBuffers.emplace_back(100.0f);
    rightBuffers.emplace_back(100.0f);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 1);
    tabBarLayoutAlgorithm->CalculateItemWidthsForSymmetricExtensible(
        &layoutWrapper, spaceRequests, leftBuffers, rightBuffers, allocatedWidth);
    spaceRequests.clear();
    spaceRequests.emplace_back(0.0f);
    spaceRequests.emplace_back(0.0f);
    leftBuffers.clear();
    leftBuffers.emplace_back(10.0f);
    leftBuffers.emplace_back(10.0f);
    rightBuffers.clear();
    rightBuffers.emplace_back(30.0f);
    rightBuffers.emplace_back(30.0f);
    linearLayoutProperty->UpdateFlexDirection(FlexDirection::ROW);

    /**
     * @tc.steps: steps6. CalculateItemWidthsForSymmetricExtensible.
     * @tc.expected: steps6. Check the value of itemWidths in the CalculateItemWidthsForSymmetricExtensible function.
     */
    tabBarLayoutAlgorithm->CalculateItemWidthsForSymmetricExtensible(
        &layoutWrapper, spaceRequests, leftBuffers, rightBuffers, allocatedWidth);
    EXPECT_EQ(tabBarLayoutAlgorithm->visibleItemLength_[0], 60.0f);
}

/**
 * @tc.name: TabBarPatternOnDirtyLayoutWrapperSwap002
 * @tc.desc: test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarPatternOnDirtyLayoutWrapperSwap002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetFadingEdge(true);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    auto layoutAlgorithm = tabBarPattern_->CreateLayoutAlgorithm();
    DirtySwapConfig config;
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode_, tabBarNode_->GetGeometryNode(), tabBarLayoutProperty_);
    auto algorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm, false, false);
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper->GetLayoutProperty());

    layoutWrapper->SetLayoutAlgorithm(algorithmWrapper);
    EXPECT_EQ(layoutWrapper->layoutAlgorithm_, algorithmWrapper);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);

    /**
     * @tc.steps: step2. creat different conditions and invoke OnDirtyLayoutWrapperSwap.
     * @tc.expected: step2. expect The function is run ok.
     */
    config.skipMeasure = false;
    tabBarPattern_->isTouchingSwiper_ = true;
    layoutProperty->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarPattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_TRUE(tabBarPattern_->isTouchingSwiper_);
}

/**
* @tc.name: TabBarPatternBeforeCreateLayoutWrapper003
* @tc.desc: test Measure
* @tc.type: FUNC
*/
HWTEST_F(TabBarLayoutTestNg, TabBarPatternBeforeCreateLayoutWrapper003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    TabsItemDivider divider;
    model.SetDivider(divider);
    CreateTabsDone(model);
    tabBarPattern_->BeforeCreateLayoutWrapper();
}

/**
 * @tc.name: TabBarLayoutAlgorithmMeasureScrollableMode001
 * @tc.desc: test Measure
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmMeasureScrollableMode001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContentsWithBuilder(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);

    /**
     * @tc.steps: steps2. Set layoutStyle to LayoutStyle::ALWAYS_AVERAGE_SPLIT.
     * @tc.expected: steps2. Verify visibleItemPosition.
     */
    auto margin = 100.0f;
    ScrollableBarModeOptions option;
    option.margin = Dimension(margin);
    option.nonScrollableLayoutStyle = LayoutStyle::ALWAYS_AVERAGE_SPLIT;
    tabBarLayoutProperty_->UpdateScrollableBarModeOptions(option);
    tabBarPattern_->visibleItemPosition_.clear();
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(tabBarNode_);

    auto itemWidth = (TABS_WIDTH - margin * 2) / TABCONTENT_NUMBER;
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->first, 0);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, margin);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.endPos, margin + itemWidth);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->first, TABCONTENT_NUMBER - 1);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.startPos, TABS_WIDTH - margin - itemWidth);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.endPos, TABS_WIDTH - margin);

    /**
     * @tc.steps: steps3. Set layoutStyle to LayoutStyle::SPACE_BETWEEN_OR_CENTER.
     * @tc.expected: steps3. Verify visibleItemPosition.
     */
    option.nonScrollableLayoutStyle = LayoutStyle::SPACE_BETWEEN_OR_CENTER;
    tabBarLayoutProperty_->UpdateScrollableBarModeOptions(option);
    tabBarPattern_->visibleItemPosition_.clear();
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(tabBarNode_);
    itemWidth = TABS_WIDTH / 2 / TABCONTENT_NUMBER;
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->first, 0);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, TABS_WIDTH / TABCONTENT_NUMBER);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.endPos, TABS_WIDTH / TABCONTENT_NUMBER + itemWidth);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->first, TABCONTENT_NUMBER - 1);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.startPos,
        TABS_WIDTH / TABCONTENT_NUMBER * 3 - itemWidth);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.endPos, TABS_WIDTH / TABCONTENT_NUMBER * 3);

    /**
     * @tc.steps: steps4. Set layoutStyle to LayoutStyle::ALWAYS_CENTER.
     * @tc.expected: steps4. Verify visibleItemPosition.
     */
    option.nonScrollableLayoutStyle = LayoutStyle::ALWAYS_CENTER;
    tabBarLayoutProperty_->UpdateScrollableBarModeOptions(option);
    tabBarPattern_->visibleItemPosition_.clear();
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(tabBarNode_);
    auto startPos = (TABS_WIDTH - BARITEM_SIZE * TABCONTENT_NUMBER) / 2;
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->first, 0);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, startPos);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.endPos, startPos + BARITEM_SIZE);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->first, TABCONTENT_NUMBER - 1);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.startPos, startPos + BARITEM_SIZE * 3);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.endPos, startPos + BARITEM_SIZE * 4);
}

/**
 * @tc.name: TabBarLayoutAlgorithmMeasureScrollableMode002
 * @tc.desc: test Measure
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmMeasureScrollableMode002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContentsWithBuilder(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);

    /**
     * @tc.steps: steps2. Set axis to horizontal, init child width and margin.
     * @tc.expected: steps2. Verify visibleItemPosition.
     */
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    auto itemWidth = 200.0f;
    for (int32_t index = 0; index < TABCONTENT_NUMBER; index++) {
        auto child = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(index));
        ViewAbstract::SetWidth(AceType::RawPtr(child), CalcLength(itemWidth));
    }
    auto margin = 200.0f;
    ScrollableBarModeOptions option;
    option.margin = Dimension(200.0f);
    tabBarLayoutProperty_->UpdateScrollableBarModeOptions(option);
    tabBarPattern_->visibleItemPosition_.clear();
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(tabBarNode_);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->first, 0);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, margin);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->first, 2);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.endPos, margin + itemWidth * 3);

    /**
     * @tc.steps: steps3. Set barAdaptiveHeight to true.
     * @tc.expected: steps3. Verify height of child node.
     */
    tabBarLayoutProperty_->UpdateBarAdaptiveHeight(true);
    auto child1 = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(0));
    auto child2 = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(1));
    ViewAbstract::SetHeight(AceType::RawPtr(child1), CalcLength(60.0f));
    ViewAbstract::SetHeight(AceType::RawPtr(child2), CalcLength(70.0f));
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(tabBarNode_);
    EXPECT_EQ(child1->GetGeometryNode()->GetMarginFrameSize().CrossSize(Axis::HORIZONTAL), 70.0f);

    /**
     * @tc.steps: steps4. Set axis to vertical.
     * @tc.expected: steps4. Verify visibleItemPosition.
     */
    tabBarLayoutProperty_->UpdateAxis(Axis::VERTICAL);
    auto itemHeight = 200.0f;
    for (int32_t index = 0; index < TABCONTENT_NUMBER; index++) {
        auto child = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(index));
        ViewAbstract::SetHeight(AceType::RawPtr(child), CalcLength(itemHeight));
    }
    tabBarPattern_->visibleItemPosition_.clear();
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(tabBarNode_);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->first, 0);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, 0.0f);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->first, 1);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.endPos, itemWidth * 2);
}

/**
 * @tc.name: TabBarLayoutAlgorithmMeasureTargetIndex001
 * @tc.desc: test Measure
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmMeasureTargetIndex001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContentsWithBuilder(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: steps2. Set tabBarMode to scrollable and axis to horizontal, init child item width.
     * @tc.expected: steps2. Verify visibleItemPosition.
     */
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    auto itemWidth = 300.0f;
    for (int32_t index = 0; index < TABCONTENT_NUMBER; index++) {
        auto child = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(index));
        ViewAbstract::SetWidth(AceType::RawPtr(child), CalcLength(itemWidth));
    }
    /**
     * @tc.steps: steps3. Set targetIndex to 3.
     * @tc.expected: steps3. Verify visibleItemPosition.
     */
    tabBarPattern_->visibleItemPosition_.clear();
    tabBarPattern_->visibleItemPosition_[0] = { 0.0f, itemWidth };
    tabBarPattern_->visibleItemPosition_[1] = { itemWidth, itemWidth * 2 };
    tabBarPattern_->visibleItemPosition_[2] = { itemWidth * 2, itemWidth * 3 };
    tabBarPattern_->targetIndex_ = 3;
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(tabBarNode_);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->first, 0);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, 0.0f);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->first, 3);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.endPos, itemWidth * 4);

    /**
     * @tc.steps: steps4. Set targetIndex to 0.
     * @tc.expected: steps4. Verify visibleItemPosition.
     */
    tabBarPattern_->visibleItemPosition_.clear();
    tabBarPattern_->visibleItemPosition_[1] = { TABS_WIDTH - itemWidth * 3, TABS_WIDTH - itemWidth * 2 };
    tabBarPattern_->visibleItemPosition_[2] = { TABS_WIDTH - itemWidth * 2, TABS_WIDTH - itemWidth };
    tabBarPattern_->visibleItemPosition_[3] = { TABS_WIDTH - itemWidth, TABS_WIDTH };
    tabBarPattern_->targetIndex_ = 0;
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(tabBarNode_);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->first, 0);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, TABS_WIDTH - itemWidth * 4);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->first, 3);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.endPos, TABS_WIDTH);
}

/**
 * @tc.name: TabBarLayoutAlgorithmMeasureJumpIndex001
 * @tc.desc: test Measure
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmMeasureJumpIndex001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContentsWithBuilder(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: steps2. Set tabBarMode to scrollable and axis to horizontal, init child item width.
     */
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    auto itemWidth = 300.0f;
    for (int32_t index = 0; index < TABCONTENT_NUMBER; index++) {
        auto child = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(index));
        ViewAbstract::SetWidth(AceType::RawPtr(child), CalcLength(itemWidth));
    }

    /**
     * @tc.steps: steps3. Jump to index 0.
     * @tc.expected: steps3. Verify visibleItemPosition.
     */
    tabBarPattern_->jumpIndex_ = 0;
    tabBarPattern_->visibleItemPosition_.clear();
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(tabBarNode_);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->first, 0);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, 0.0f);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->first, 2);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.endPos, itemWidth * 3);

    /**
     * @tc.steps: steps4. Jump to index 1.
     * @tc.expected: steps4. Verify visibleItemPosition.
     */
    tabBarPattern_->jumpIndex_ = 1;
    tabBarPattern_->visibleItemPosition_.clear();
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    FlushLayoutTask(tabBarNode_);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->first, 0);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, (TABS_WIDTH - itemWidth) / 2 - itemWidth);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->first, 2);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.endPos,
        TABS_WIDTH + itemWidth - (TABS_WIDTH - itemWidth) / 2);

    /**
     * @tc.steps: steps5. Jump to index 3.
     * @tc.expected: steps5. Verify visibleItemPosition.
     */
    tabBarPattern_->jumpIndex_ = 3;
    tabBarPattern_->visibleItemPosition_.clear();
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(tabBarNode_);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->first, 1);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, TABS_WIDTH - itemWidth * 3);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->first, 3);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.endPos, TABS_WIDTH);
}

/**
 * @tc.name: TabBarLayoutAlgorithmMeasureWithOffset001
 * @tc.desc: test Measure
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmMeasureWithOffset001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContentsWithBuilder(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: steps2. Set tabBarMode to scrollable and axis to horizontal, init child item width.
     */
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    auto itemWidth = 300.0f;
    for (int32_t index = 0; index < TABCONTENT_NUMBER; index++) {
        auto child = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(index));
        ViewAbstract::SetWidth(AceType::RawPtr(child), CalcLength(itemWidth));
    }

    tabBarPattern_->visibleItemPosition_.clear();
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(tabBarNode_);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->first, 0);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, 0.0f);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->first, 2);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.endPos, itemWidth * 3);

    /**
     * @tc.steps: steps3. Set different currentDelta_.
     * @tc.expected: steps3. Verify visibleItemPosition.
     */
    tabBarPattern_->canOverScroll_ = true;
    auto currentDelta1 = 100.0f;
    tabBarPattern_->currentDelta_ = currentDelta1;
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(tabBarNode_);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->first, 0);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, currentDelta1);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->first, 2);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.endPos, itemWidth * 3 + currentDelta1);

    tabBarPattern_->canOverScroll_ = true;
    auto currentDelta2 = -300.0f;
    tabBarPattern_->currentDelta_ = currentDelta2;
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(tabBarNode_);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->first, 0);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, currentDelta1 + currentDelta2);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->first, 3);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.endPos,
        itemWidth * 4 + currentDelta1 + currentDelta2);

    tabBarPattern_->canOverScroll_ = true;
    auto currentDelta3 = -300.0f;
    tabBarPattern_->currentDelta_ = currentDelta3;
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(tabBarNode_);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->first, 1);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos,
        itemWidth + currentDelta1 + currentDelta2 + currentDelta3);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->first, 3);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.endPos,
        itemWidth * 4 + currentDelta1 + currentDelta2 + currentDelta3);
}

/**
 * @tc.name: TabBarLayoutAlgorithmMeasureWithOffset002
 * @tc.desc: test Measure
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmMeasureWithOffset002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContentsWithBuilder(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: steps2. Set tabBarMode to scrollable and axis to horizontal, init child item width.
     */
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    auto itemWidth = 300.0f;
    for (int32_t index = 0; index < TABCONTENT_NUMBER; index++) {
        auto child = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(index));
        ViewAbstract::SetWidth(AceType::RawPtr(child), CalcLength(itemWidth));
    }

    tabBarPattern_->visibleItemPosition_.clear();
    tabBarPattern_->visibleItemPosition_[0] = { 0.0f, itemWidth };
    tabBarPattern_->visibleItemPosition_[1] = { itemWidth, itemWidth * 2 };
    tabBarPattern_->visibleItemPosition_[2] = { itemWidth * 2, itemWidth * 3 };

    tabBarPattern_->canOverScroll_ = false;
    auto currentDelta1 = 100.0f;
    tabBarPattern_->currentDelta_ = currentDelta1;
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(tabBarNode_);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->first, 0);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, 0.0f);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->first, 2);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.endPos, itemWidth * 3);

    tabBarPattern_->canOverScroll_ = false;
    auto currentDelta2 = -500.0f;
    tabBarPattern_->currentDelta_ = currentDelta2;
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(tabBarNode_);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->first, 1);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, TABS_WIDTH - itemWidth * 3);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->first, 3);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.endPos, TABS_WIDTH);

    tabBarPattern_->canOverScroll_ = true;
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    tabBarPattern_->currentDelta_ = currentDelta1;
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(tabBarNode_);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->first, 1);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos,
        TABS_WIDTH - itemWidth * 3 - currentDelta1);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->first, 3);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.endPos, TABS_WIDTH - currentDelta1);
}

/**
 * @tc.name: TabBarLayoutAlgorithmMeasureOverLengthItem001
 * @tc.desc: test Measure
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmMeasureOverLengthItem001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContentsWithBuilder(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: steps2. Set tabBarMode to scrollable and axis to horizontal, init child item width.
     */
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    auto itemWidth = 800.0f;
    for (int32_t index = 0; index < TABCONTENT_NUMBER; index++) {
        auto child = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(index));
        ViewAbstract::SetWidth(AceType::RawPtr(child), CalcLength(itemWidth));
    }

    /**
     * @tc.steps: steps3. Jump to index 1.
     * @tc.expected: steps3. Verify visibleItemPosition.
     */
    tabBarPattern_->jumpIndex_ = 1;
    tabBarPattern_->visibleItemPosition_.clear();
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(tabBarNode_);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->first, 1);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, 0.0f);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.endPos, itemWidth);

    /**
     * @tc.steps: steps3. Set targetIndex to 2.
     * @tc.expected: steps3. Verify visibleItemPosition.
     */
    tabBarPattern_->targetIndex_ = 2;
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(tabBarNode_);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->first, 1);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, 0.0f);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.endPos, itemWidth);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->first, 2);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.startPos, itemWidth);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.endPos, itemWidth * 2);
}

/**
 * @tc.name: TabBarLayoutAlgorithmMeasureFixedMode001
 * @tc.desc: test Measure
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmMeasureFixedMode001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContentsWithBuilder(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::FIXED);

    /**
     * @tc.steps: steps2. Set axis to horizontal.
     * @tc.expected: steps2. Verify visibleItemPosition.
     */
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern_->visibleItemPosition_.clear();
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(tabBarNode_);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->first, 0);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, 0.0f);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.endPos, TABS_WIDTH / TABCONTENT_NUMBER);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->first, TABCONTENT_NUMBER - 1);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.startPos, TABS_WIDTH / TABCONTENT_NUMBER * 3);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.endPos, TABS_WIDTH);

    /**
     * @tc.steps: steps3. Set barAdaptiveHeight to true.
     * @tc.expected: steps3. Verify height of child node.
     */
    tabBarLayoutProperty_->UpdateBarAdaptiveHeight(true);
    auto child1 = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(0));
    auto child2 = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(1));
    ViewAbstract::SetHeight(AceType::RawPtr(child1), CalcLength(60.0f));
    ViewAbstract::SetHeight(AceType::RawPtr(child2), CalcLength(70.0f));
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(tabBarNode_);
    EXPECT_EQ(child1->GetGeometryNode()->GetMarginFrameSize().CrossSize(Axis::HORIZONTAL), 70.0f);

    /**
     * @tc.steps: steps4. Set axis to vertical.
     * @tc.expected: steps4. Verify visibleItemPosition.
     */
    tabBarLayoutProperty_->UpdateAxis(Axis::VERTICAL);
    tabBarPattern_->visibleItemPosition_.clear();
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(tabBarNode_);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->first, 0);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, 0.0f);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.endPos, TABS_HEIGHT / TABCONTENT_NUMBER);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->first, TABCONTENT_NUMBER - 1);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.startPos, TABS_HEIGHT / TABCONTENT_NUMBER * 3);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.endPos, TABS_HEIGHT);
}

/**
 * @tc.name: TabBarLayoutAlgorithmMeasureFixedMode002
 * @tc.desc: test Measure
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmMeasureFixedMode002, TestSize.Level1)
{
    auto childCount = 3;
    TabsModelNG model = CreateTabs();
    for (int32_t index = 0; index < childCount; index++) {
        CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    }
    CreateTabsDone(model);
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::FIXED);

    /**
     * @tc.steps: steps2. Set axis to horizontal, init bottomTabBarStyle.
     * @tc.expected: steps2. Verify visibleItemPosition.
     */
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    for (int32_t index = 0; index < childCount; index++) {
        tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, index);
        BottomTabBarStyle bottomTabBarStyle;
        bottomTabBarStyle.symmetricExtensible = true;
        tabBarPattern_->SetBottomTabBarStyle(bottomTabBarStyle, index);
    }
    auto child1 = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(0));
    auto child2 = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(1));
    auto child3 = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(2));
    ViewAbstract::SetWidth(AceType::RawPtr(child1), CalcLength(100.0f));
    ViewAbstract::SetWidth(AceType::RawPtr(child2), CalcLength(300.0f));
    ViewAbstract::SetWidth(AceType::RawPtr(child3), CalcLength(200.0f));

    tabBarPattern_->visibleItemPosition_.clear();
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(tabBarNode_);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->first, 0);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, 0.0f);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.endPos, 220.0f);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->first, 2);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.startPos, 500.0f);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.endPos, TABS_WIDTH);

    /**
     * @tc.steps: steps3. Set barAdaptiveHeight to true.
     * @tc.expected: steps3. Verify height of child node.
     */
    tabBarLayoutProperty_->UpdateBarAdaptiveHeight(true);
    ViewAbstract::SetHeight(AceType::RawPtr(child1), CalcLength(60.0f));
    ViewAbstract::SetHeight(AceType::RawPtr(child2), CalcLength(70.0f));
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(tabBarNode_);
    EXPECT_EQ(child1->GetGeometryNode()->GetMarginFrameSize().CrossSize(Axis::HORIZONTAL), 70.0f);

    /**
     * @tc.steps: steps4. Set axis to vertical.
     * @tc.expected: steps4. Verify visibleItemPosition.
     */
    tabBarLayoutProperty_->UpdateAxis(Axis::VERTICAL);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(TABS_WIDTH));
    tabBarPattern_->visibleItemPosition_.clear();
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(frameNode_);
    auto itemWidth = TABS_WIDTH / 2 / childCount;
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->first, 0);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, TABS_WIDTH / 4);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.endPos, TABS_WIDTH / 4 + itemWidth);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->first, childCount - 1);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.startPos, TABS_WIDTH / 4 * 3 - itemWidth);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.endPos, TABS_WIDTH / 4 * 3);
}
} // namespace OHOS::Ace::NG
