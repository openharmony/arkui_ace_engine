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
    CreateWithItem([](TabsModelNG model) {
        model.SetFadingEdge(true);
    });
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
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });

    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    tabBarLayoutProperty_->UpdateSelectedMask(0);
    tabBarLayoutProperty_->UpdateUnselectedMask(1);
    std::vector<OffsetF> childOffsetDelta = { OffsetF(), OffsetF() };
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
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });

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
 * @tc.name: TabBarLayoutAlgorithmLayoutMask003
 * @tc.desc: test LayoutMask
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmLayoutMask003, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));

    /**
     * @tc.steps: step2. call LayoutMask function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarLayoutAlgorithm->LayoutMask(&layoutWrapper, {});
}

/**
 * @tc.name: TabBarLayoutAlgorithmUpdateChildConstraint001
 * @tc.desc: test UpdateChildConstraint
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmUpdateChildConstraint001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build tabBarNode_ and ideaSize.
     */
    CreateWithItem([](TabsModelNG model) {});
    LayoutConstraintF childConstraint = LayoutConstraintF();
    std::optional<int32_t> tabBarTestId_(frameNode_->GetTabBarId());
    auto tabBarNode = GroupNode::GetFrameNode(V2::TAB_BAR_ETS_TAG, tabBarTestId_.value());
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());

    float width = 1.0;
    float height = 2.0;
    auto ideaSize = SizeF(width, height);
    int32_t childCount = 1;
    auto axis = Axis::HORIZONTAL;
    tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;

    /**
     * @tc.steps: step2. call UpdateChildConstraint function.
     * @tc.expected: The function is run ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarLayoutAlgorithm->UpdateChildConstraint(
                    childConstraint, tabBarLayoutProperty_, ideaSize, childCount, axis);
                axis = Axis::VERTICAL;
            }
            tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::BOTTOMTABBATSTYLE;
            axis = Axis::HORIZONTAL;
        }
        tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
        tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    }
}

/**
 * @tc.name: TabBarLayoutAlgorithmMeasureMaxHeight002
 * @tc.desc: test MeasureMaxHeight
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmMeasureMaxHeight002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty<TabBarLayoutProperty>());
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode_, geometryNode1, swiperNode_->GetLayoutProperty());
    swiperLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(swiperLayoutWrapper);

    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    SizeF frameSize(SizeF(0.0f, 0.0f));

    /**
     * @tc.steps: step2. call MeasureMaxHeight function.
     * @tc.expected: The function is run ok.
     */
    tabBarLayoutAlgorithm->MeasureMaxHeight(&layoutWrapper, 5);
    tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarLayoutAlgorithm->MeasureMaxHeight(&layoutWrapper, 5);
}

/**
 * @tc.name: TabBarLayoutAlgorithmMeasureItemWidths002
 * @tc.desc: test MeasureItemWidths
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmMeasureItemWidths002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty<TabBarLayoutProperty>());
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode_, geometryNode1, swiperNode_->GetLayoutProperty());
    swiperLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(swiperLayoutWrapper);
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());

    /**
     * @tc.steps: step2. call MeasureItemWidths function.
     * @tc.expected: The function is run ok.
     */
    tabBarLayoutAlgorithm->MeasureItemWidths(&layoutWrapper, 5);

    tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarLayoutAlgorithm->MeasureItemWidths(&layoutWrapper, 5);
    EXPECT_EQ(tabBarLayoutAlgorithm->maxHeight_, 0);
}

/**
 * @tc.name: TabBarLayoutAlgorithmGetGridSizeType002
 * @tc.desc: test GetGridSizeType
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmGetGridSizeType002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    CreateWithItem([](TabsModelNG model) {});
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(tabBarNode_, geometryNode, tabBarLayoutProperty_);
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    /**
     * @tc.steps: step2. call GetGridSizeType function.
     * @tc.expected: The function is run ok.
     */
    tabBarLayoutAlgorithm->GetGridSizeType(FIRST_ITEM_SIZE);
    tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarLayoutAlgorithm->GetGridSizeType(FIRST_ITEM_SIZE);
}

/**
 * @tc.name: TabBarLayoutAlgorithmCalculateBackChildrenMainSize001
 * @tc.desc: test CalculateBackChildrenMainSize
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmCalculateBackChildrenMainSize001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    tabBarLayoutProperty_->UpdateSelectedMask(0);
    tabBarLayoutProperty_->UpdateUnselectedMask(1);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarLayoutProperty_);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));
    int32_t indicator = -2;
    auto axis = Axis::HORIZONTAL;

    /**
     * @tc.steps: step2. build selectedMaskNode.
     */
    for (int i = 0; i <= 2; i++) {
        auto selectedmaskPosition = tabBarNode_->GetChildren().size() - TEST_SELECTED_MASK_COUNT;
        auto selectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(selectedmaskPosition));
            RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
        RefPtr<LayoutWrapperNode> selectedMaskLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
            selectedMaskNode, geometryNode1, selectedMaskNode->GetLayoutProperty());
        layoutWrapper.AppendChild(selectedMaskLayoutWrapper);
    }

    /**
     * @tc.steps: step3. call CalculateBackChildrenMainSize function.
     * @tc.expected: The function is run ok.
     */
    for (int i = 0; i <= 1; i++) {
        ASSERT_FLOAT_EQ(tabBarLayoutAlgorithm->CalculateBackChildrenMainSize(&layoutWrapper, indicator, axis), 0.0f);
        indicator = -1;
    }
}

/**
 * @tc.name: TabBarLayoutAlgorithmLayout002
 * @tc.desc: Test Divider Layout.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmLayout002, TestSize.Level1)
{
    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call Layout function.
     * @tc.expected: Related function is called.
     */
    CreateWithItem([](TabsModelNG model) {});
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(tabBarNode_, geometryNode, tabBarLayoutProperty_);
    AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())->UpdateTabBarMode(TabBarMode::FIXED);
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::BOTTOMTABBATSTYLE;
    AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())->UpdateAxis(Axis::VERTICAL);
    tabBarLayoutAlgorithm->Layout(&layoutWrapper);
}

/**
 * @tc.name: TabBarLayoutAlgorithmLayout003
 * @tc.desc: Test Divider Layout.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmLayout003, TestSize.Level1)
{
    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call Layout function.
     * @tc.expected: Related function is called.
     */
    CreateWithItem([](TabsModelNG model) {});
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(tabBarNode_, geometryNode, tabBarLayoutProperty_);
    auto layoutWrapper1 = AceType::MakeRefPtr<LayoutWrapperNode>(
        tabBarNode_, geometryNode, tabBarLayoutProperty_);
    auto layoutWrapper2 = AceType::MakeRefPtr<LayoutWrapperNode>(
        tabBarNode_, geometryNode, tabBarLayoutProperty_);
    auto layoutWrapper3 = AceType::MakeRefPtr<LayoutWrapperNode>(
        tabBarNode_, geometryNode, tabBarLayoutProperty_);
    auto layoutWrapper4 = AceType::MakeRefPtr<LayoutWrapperNode>(
        tabBarNode_, geometryNode, tabBarLayoutProperty_);
    auto layoutWrapper5 = AceType::MakeRefPtr<LayoutWrapperNode>(
        tabBarNode_, geometryNode, tabBarLayoutProperty_);
    AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())->UpdateAxis(Axis::HORIZONTAL);
    AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())->UpdateIndicator(1);
    tabBarLayoutAlgorithm->indicator_ = 0;
    layoutWrapper.GetGeometryNode()->SetFrameSize(SizeF(0.1f, 0.2f));
    tabBarLayoutAlgorithm->childrenMainSize_ = 0.3f;
    layoutWrapper.AppendChild(layoutWrapper1);
    layoutWrapper.AppendChild(layoutWrapper2);
    layoutWrapper.AppendChild(layoutWrapper3);
    layoutWrapper.AppendChild(layoutWrapper4);
    layoutWrapper.AppendChild(layoutWrapper5);
    layoutWrapper1->GetGeometryNode()->SetFrameSize(SizeF(0.0f, 0.0f));
    layoutWrapper3->GetGeometryNode()->SetFrameSize(SizeF(0.0f, 0.0f));

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarLayoutAlgorithm->Layout(&layoutWrapper);
                tabBarLayoutAlgorithm->indicator_ = 2;
                tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::BOTTOMTABBATSTYLE;
            }
            layoutWrapper.GetGeometryNode()->SetFrameSize(SizeF(1.0f, 1.0f));
            layoutWrapper1->GetGeometryNode()->SetFrameSize(SizeF(2.0f, 2.0f));
            layoutWrapper2->GetGeometryNode()->SetFrameSize(SizeF(0.0f, 0.0f));
        }
        AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())->UpdateAxis(Axis::VERTICAL);
    }

    layoutWrapper3->GetGeometryNode()->SetFrameSize(SizeF(2.0f, 2.0f));
    for (int i = 0; i <= 1; i++) {
        tabBarLayoutAlgorithm->Layout(&layoutWrapper);
        AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())->UpdateAxis(Axis::HORIZONTAL);
    }
}

/**
 * @tc.name: TabBarLayoutAlgorithmLayoutMask004
 * @tc.desc: Test the LayoutMask function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmLayoutMask004, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    tabBarLayoutProperty_->UpdateSelectedMask(0);
    tabBarLayoutProperty_->UpdateUnselectedMask(1);
    std::vector<OffsetF> childOffsetDelta = { OffsetF(), OffsetF() };
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
    CreateWithItem([](TabsModelNG model) {});
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
    CreateWithItem([](TabsModelNG model) {});
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
 * @tc.name: TabBarLayoutAlgorithmConfigHorizontal001
 * @tc.desc: Test the ConfigHorizontal function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmConfigHorizontal001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode_->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty());

    /**
     * @tc.steps: steps2. Create different input parameters.
     */
    layoutProperty->UpdateTabBarMode(TabBarMode::FIXED);
    int32_t childCount = 0;
    BarGridColumnOptions option;
    option.lg = 2;
    tabBarLayoutProperty_->UpdateBarGridAlign(option);
    auto frameSize = SizeF(1000.0f, 1000.0f);

    /**
     * @tc.steps: steps3. ConfigHorizontal.
     * @tc.expected: steps3. Check the results of ConfigHorizontal under different conditions.
     */
    tabbarLayoutAlgorithm->ConfigHorizontal(&layoutWrapper, frameSize, childCount);
    childCount = 1;
    layoutProperty->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    ScrollableBarModeOptions options;
    options.margin = 0.0_vp;
    options.nonScrollableLayoutStyle = LayoutStyle::ALWAYS_AVERAGE_SPLIT;
    tabBarLayoutProperty_->UpdateScrollableBarModeOptions(options);
    tabbarLayoutAlgorithm->ConfigHorizontal(&layoutWrapper, frameSize, childCount);
    options.nonScrollableLayoutStyle = LayoutStyle::SPACE_BETWEEN_OR_CENTER;
    tabBarLayoutProperty_->UpdateScrollableBarModeOptions(options);
    tabbarLayoutAlgorithm->ConfigHorizontal(&layoutWrapper, frameSize, childCount);
    options.nonScrollableLayoutStyle = LayoutStyle::ALWAYS_CENTER;
    tabBarLayoutProperty_->UpdateScrollableBarModeOptions(options);
    tabbarLayoutAlgorithm->childrenMainSize_ = 0.0f;
    tabbarLayoutAlgorithm->ConfigHorizontal(&layoutWrapper, frameSize, childCount);
    layoutProperty->UpdateBarAdaptiveHeight(true);
    tabbarLayoutAlgorithm->ConfigHorizontal(&layoutWrapper, frameSize, childCount);
    EXPECT_EQ(tabbarLayoutAlgorithm->scrollMargin_, 0.0f);
}

/**
 * @tc.name: TabBarLayoutAlgorithmMeasureItemWidths001
 * @tc.desc: Test the MeasureItemWidths function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmMeasureItemWidths001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode_->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());

    /**
     * @tc.steps: steps2. Create a child for layoutWrapper.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty());
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);
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
    int32_t childCount = 3;
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 1);
    tabbarLayoutAlgorithm->scrollMargin_ = 0.0f;

    /**
     * @tc.steps: steps5.MeasureItemWidths.
     * @tc.expected: steps5. Testing childrenMainSize under MeasureItemWidths Value of.
     */
    tabbarLayoutAlgorithm->MeasureItemWidths(&layoutWrapper, childCount);
    EXPECT_EQ(tabbarLayoutAlgorithm->childrenMainSize_, 0.0f);
}

/**
 * @tc.name: TabBarLayoutAlgorithmMeasureMaxHeight001
 * @tc.desc: Test the MeasureMaxHeight function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmMeasureMaxHeight001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode_->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty());
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);
    tabbarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;

    /**
     * @tc.steps: steps2. Set itemWidths_ Clear and reassign and
     *                    Create two children named columnLayoutWrapper using a loop for layoutWrapper.
     */
    tabbarLayoutAlgorithm->itemWidths_.clear();
    tabbarLayoutAlgorithm->itemWidths_.emplace_back(10.0f);
    for (int32_t i = 0; i < 2; i++) {
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
    }

    /**
     * @tc.steps: steps3.MeasureMaxHeight.
     * @tc.expected: steps3. Test itemWidths under MeasureMaxHeight Value of.
     */
    int32_t childCount = 2;
    tabbarLayoutAlgorithm->itemWidths_.emplace_back(2.0f);
    tabbarLayoutAlgorithm->MeasureMaxHeight(&layoutWrapper, childCount);
    EXPECT_EQ(tabbarLayoutAlgorithm->itemWidths_[0], 10.0f);
}

/**
 * @tc.name: TabBarLayoutAlgorithmApplyLayoutMode001
 * @tc.desc: Test the ApplyLayoutMode function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmApplyLayoutMode001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
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
    int32_t childCount = 2;

    /**
     * @tc.steps: steps4. ApplyLayoutMode.
     * @tc.expected: steps4. Create different conditions and check the result of ApplyLayoutMode.
     */
    bottomTabBarStyle.layoutMode = LayoutMode::VERTICAL;
    tabBarPattern_->SetBottomTabBarStyle(bottomTabBarStyle, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabbarLayoutAlgorithm->ApplyLayoutMode(&layoutWrapper, allocatedWidth, childCount);
    bottomTabBarStyle.layoutMode = LayoutMode::AUTO;
    tabBarPattern_->SetBottomTabBarStyle(bottomTabBarStyle, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 1);
    tabbarLayoutAlgorithm->ApplyLayoutMode(&layoutWrapper, allocatedWidth, childCount);
    allocatedWidth = 200000.0f;
    tabbarLayoutAlgorithm->ApplyLayoutMode(&layoutWrapper, allocatedWidth, childCount);
    EXPECT_FALSE(linearLayoutProperty->IsVertical());
}

/**
 * @tc.name: TabBarLayoutAlgorithmLayoutChildren001
 * @tc.desc: Test the LayoutChildren function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmLayoutChildren001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();

    /**
     * @tc.steps: steps2. Create padding and assign initial values to it.
     */
    PaddingProperty padding;
    padding.left = CalcLength(200.0_vp);
    padding.right = CalcLength(200.0_vp);
    padding.top = CalcLength(200.0_vp);
    padding.bottom = CalcLength(200.0_vp);
    tabBarLayoutProperty_->UpdatePadding(padding);
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));
    layoutWrapper.currentChildCount_ = 5;
    auto frameSize = SizeF(0.0f, 0.0f);
    auto axis = Axis::HORIZONTAL;
    tabbarLayoutAlgorithm->childrenMainSize_ = 10000.0f;
    OffsetF childOffset(0.0f, 0.0f);
    tabbarLayoutAlgorithm->LayoutChildren(&layoutWrapper, frameSize, axis, childOffset);

    /**
     * @tc.steps: steps3. LayoutChildren.
     * @tc.expected: steps3. Verify childrenMainSize under LayoutChildren Value of.
     */
    EXPECT_EQ(tabbarLayoutAlgorithm->tabItemOffset_[0].GetX(), childOffset.GetX());
    EXPECT_EQ(tabbarLayoutAlgorithm->tabItemOffset_[0].GetY(), childOffset.GetY());
}

/**
 * @tc.name: TabBarLayoutAlgorithmGetContentWidth001
 * @tc.desc: Test the GetContentWidth function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmGetContentWidth001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    tabBarPattern_->tabBarStyle_ = TabBarStyle::BOTTOMTABBATSTYLE;
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    auto layoutProperty = tabBarLayoutProperty_;
    auto frameSize = SizeF(0.0f, 0.0f);

    /**
     * @tc.steps: steps2. Create padding and assign initial values to it.
     */
    PaddingProperty padding;
    padding.left = CalcLength(200.0_vp);
    padding.right = CalcLength(200.0_vp);
    padding.top = CalcLength(200.0_vp);
    padding.bottom = CalcLength(200.0_vp);

    /**
     * @tc.steps: steps3. GetContentWidth.
     * @tc.expected: steps3. Check the result of GetContentWidth.
     */
    layoutProperty->UpdatePadding(padding);
    float resultWidth = tabbarLayoutAlgorithm->GetContentWidth(layoutProperty, frameSize);
    EXPECT_EQ(resultWidth, 0.0f);
}

/**
 * @tc.name: TabBarLayoutAlgorithmApplySymmetricExtensible001
 * @tc.desc: Test the ApplySymmetricExtensible function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmApplySymmetricExtensible001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });
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
    int32_t childCount = 1;
    tabBarLayoutAlgorithm->itemWidths_.clear();
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(1000.0f);
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(2000.0f);
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(3000.0f);
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth, childCount);
    EXPECT_NE(tabBarLayoutAlgorithm->itemWidths_.size(), 1);
    tabBarLayoutAlgorithm->itemWidths_.clear();
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(1000.0f);
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth, childCount);
    EXPECT_EQ(tabBarLayoutAlgorithm->itemWidths_.size(), 1);
    childCount = 3;
    tabBarLayoutAlgorithm->itemWidths_.clear();
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(1000.0f);
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(2000.0f);
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(3000.0f);
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth, childCount);
    EXPECT_EQ(tabBarLayoutAlgorithm->itemWidths_.size(), 3);
    tabBarLayoutAlgorithm->itemWidths_.clear();
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(1000.0f);
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth, childCount);
    EXPECT_EQ(tabBarLayoutAlgorithm->itemWidths_.size(), 1);
    tabBarLayoutAlgorithm->itemWidths_.clear();
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(1000.0f);
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(2000.0f);
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(3000.0f);

    /**
     * @tc.steps: steps4. ApplySymmetricExtensible.
     * @tc.expected: steps4. Check the result of ApplySymmetricExtensible.
     */
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth, childCount);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    linearLayoutProperty->UpdateFlexDirection(FlexDirection::ROW_REVERSE);
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth, childCount);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    linearLayoutProperty->UpdateFlexDirection(FlexDirection::COLUMN);
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth, childCount);
    allocatedWidth = 100000.0f;
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth, childCount);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    linearLayoutProperty->UpdateFlexDirection(FlexDirection::COLUMN);
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth, childCount);
    EXPECT_EQ(tabBarLayoutAlgorithm->itemWidths_[0], allocatedWidth);
}

/**
 * @tc.name: TabBarLayoutAlgorithmCalculateItemWidthsForSymmetricExtensible001
 * @tc.desc: Test the CalculateItemWidthsForSymmetricExtensible function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmCalculateItemWidthsForSymmetricExtensible001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });
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
    int32_t childCount = 2;

    /**
     * @tc.steps: steps5. Test CalculateItemWidthsForSymmetricExtensible by using different conditions.
     */
    tabBarLayoutAlgorithm->itemWidths_.clear();
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(10.0f);
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
        &layoutWrapper, childCount, spaceRequests, leftBuffers, rightBuffers, allocatedWidth);
    tabBarLayoutAlgorithm->itemWidths_.clear();
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(100.0f);
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(100.0f);
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
        &layoutWrapper, childCount, spaceRequests, leftBuffers, rightBuffers, allocatedWidth);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 1);
    tabBarLayoutAlgorithm->CalculateItemWidthsForSymmetricExtensible(
        &layoutWrapper, childCount, spaceRequests, leftBuffers, rightBuffers, allocatedWidth);
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
        &layoutWrapper, childCount, spaceRequests, leftBuffers, rightBuffers, allocatedWidth);
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
        &layoutWrapper, childCount, spaceRequests, leftBuffers, rightBuffers, allocatedWidth);
    EXPECT_EQ(tabBarLayoutAlgorithm->itemWidths_[0], 0.0f);
}

/**
 * @tc.name: TabBarLayoutAlgorithmApplySymmetricExtensible002
 * @tc.desc: Test the ApplySymmetricExtensible function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmApplySymmetricExtensible002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));
    tabBarLayoutAlgorithm->itemWidths_.clear();
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(1000.0f);
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(2000.0f);
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(3000.0f);
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
    int32_t childCount = 3;
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth, childCount);
    EXPECT_EQ(tabBarLayoutAlgorithm->itemWidths_[0], 0.0f);
}

/**
 * @tc.name: TabBarLayoutAlgorithmAdjustFixedItem001
 * @tc.desc: Test the AdjustFixedItem function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmAdjustFixedItem001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);
    auto axis = Axis::HORIZONTAL;
    auto frameSize = OptionalSizeF(0.0f, 0.0f);

    /**
     * @tc.steps: step2. Create a child named childwrapper for layoutWrapper.
     */
    auto columnNode1 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> childWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode1, geometryNode2, columnNode1->GetLayoutProperty());
    childWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    childWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(childWrapper);

    /**
     * @tc.steps: steps3. AdjustFixedItem.
     * @tc.expected: steps3. Check the result of AdjustFixedItem.
     */
    childWrapper->GetGeometryNode()->SetFrameSize(SizeF(10000.0f, 10000.0f));
    tabBarLayoutAlgorithm->AdjustFixedItem(childWrapper, frameSize, axis);
    axis = Axis::VERTICAL;
    tabBarLayoutAlgorithm->AdjustFixedItem(childWrapper, frameSize, axis);
    EXPECT_EQ(childWrapper->GetGeometryNode()->GetFrameSize(), SizeF(0.0f, 0.0f));
}

/**
 * @tc.name: TabBarLayoutAlgorithmCalculateItemWidthsForSymmetricExtensible002
 * @tc.desc: Test the CalculateItemWidthsForSymmetricExtensible function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmCalculateItemWidthsForSymmetricExtensible002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });
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
    int32_t childCount = 2;
    std::vector<float> spaceRequests;
    std::vector<float> leftBuffers;
    std::vector<float> rightBuffers;
    tabBarLayoutAlgorithm->itemWidths_.clear();
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(100.0f);
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(100.0f);
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
        &layoutWrapper, childCount, spaceRequests, leftBuffers, rightBuffers, allocatedWidth);
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
        &layoutWrapper, childCount, spaceRequests, leftBuffers, rightBuffers, allocatedWidth);
    EXPECT_EQ(tabBarLayoutAlgorithm->itemWidths_[0], 60.0f);
}

/**
 * @tc.name: TabBarPatternOnDirtyLayoutWrapperSwap002
 * @tc.desc: test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarPatternOnDirtyLayoutWrapperSwap002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        model.SetFadingEdge(true);
    });
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
 * @tc.name: TabBarLayoutAlgorithmUpdateChildConstraint002
 * @tc.desc: test UpdateChildConstraint
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmUpdateChildConstraint002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build tabBarNode_ and ideaSize.
     */
    CreateWithItem([](TabsModelNG model) {});
    LayoutConstraintF childConstraint = LayoutConstraintF();
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::FIXED);
    float width = 1.0;
    float height = 2.0;
    auto ideaSize = SizeF(width, height);
    int32_t childCount = 1;
    auto axis = Axis::FREE;
    tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;

    /**
     * @tc.steps: step2. call UpdateChildConstraint function.
     * @tc.expected: The function is run ok.
     */
    tabBarLayoutAlgorithm->UpdateChildConstraint(childConstraint, tabBarLayoutProperty_, ideaSize, childCount, axis);
    EXPECT_EQ(tabBarLayoutProperty_->GetTabBarMode().value(), TabBarMode::FIXED);
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarLayoutAlgorithm->UpdateChildConstraint(childConstraint, tabBarLayoutProperty_, ideaSize, childCount, axis);
    EXPECT_EQ(tabBarLayoutProperty_->GetTabBarMode().value(), TabBarMode::SCROLLABLE);
}

/**
 * @tc.name: TabBarLayoutAlgorithmCheckMarqueeForScrollable001
 * @tc.desc: Test the CheckMarqueeForScrollable function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmCheckMarqueeForScrollable001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty());

    /**
     * @tc.steps: steps2. Create different input parameters.
     */
    layoutProperty->UpdateTabBarMode(TabBarMode::FIXED);
    int32_t childCount = 0;
    BarGridColumnOptions option;
    option.lg = 2;
    tabBarLayoutProperty_->UpdateBarGridAlign(option);

    /**
     * @tc.steps: steps3. CheckMarqueeForScrollable.
     * @tc.expected: steps3. Check the results of CheckMarqueeForScrollable under different conditions.
     */
    tabbarLayoutAlgorithm->CheckMarqueeForScrollable(&layoutWrapper, childCount);
    EXPECT_NE(tabbarLayoutAlgorithm, nullptr);
    childCount = 1;
    tabbarLayoutAlgorithm->CheckMarqueeForScrollable(&layoutWrapper, childCount);
    EXPECT_NE(tabbarLayoutAlgorithm, nullptr);
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
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });
    tabBarPattern_->BeforeCreateLayoutWrapper();
}

/**
 * @tc.name: TabBarLayoutAlgorithmUpdateChildConstraint002
 * @tc.desc: test UpdateChildConstraint
 * @tc.type: FUNC
 */
HWTEST_F(TabBarLayoutTestNg, TabBarLayoutAlgorithmUpdateChildConstraint003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build tabBarNode_ and ideaSize.
     */
    LayoutConstraintF childConstraint = LayoutConstraintF();
    CreateWithItem([](TabsModelNG model) {});

    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::FIXED);

    /**
     * @tc.steps: step2. Set width and height
     */
    float width = 1.0;
    float height = 2.0;
    auto ideaSize = SizeF(width, height);
    int32_t childCount = 1;
    auto axis = Axis::FREE;
    tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;

    /**
     * @tc.steps: step2. call UpdateChildConstraint function.
     * @tc.expected: The function is run ok.
     */
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::FIXED_START);
    tabBarLayoutAlgorithm->UpdateChildConstraint(childConstraint, tabBarLayoutProperty_, ideaSize, childCount, axis);
    EXPECT_EQ(tabBarLayoutProperty_->GetTabBarMode().value(), TabBarMode::FIXED_START);
}
} // namespace OHOS::Ace::NG
