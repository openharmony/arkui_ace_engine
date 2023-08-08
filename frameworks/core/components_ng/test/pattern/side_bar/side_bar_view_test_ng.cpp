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

#include "gtest/gtest.h"
#define private public
#define protected public
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/divider/divider_layout_property.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/flex/flex_layout_algorithm.h"
#include "core/components_ng/pattern/flex/flex_layout_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_layout_algorithm.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_layout_property.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_model_ng.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr Dimension STROKE_WIDTH = 10.0_vp;
constexpr Dimension START_MARGIN = 5.0_vp;
constexpr Dimension END_MARGIN = 5.0_vp;
constexpr Dimension NONE_WIDTH = 0.0_vp;
const SizeF FIRST_ITEM_SIZE(5.0f, 5.0f);
const SizeF SELF_SIZE(50.0f, 50.0f);
const float REAL_WIDTH = 10.0f;
} // namespace

class SideBarViewTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void SideBarViewTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void SideBarViewTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: SideBarViewTestNg001
 * @tc.desc: Test SideBar devider
 * @tc.type: FUNC
 */
HWTEST_F(SideBarViewTestNg, SideBarViewTestNg001, TestSize.Level1)
{
    SideBarContainerModelNG SideBarContainerModelInstance;
    Dimension width = 10.0_vp;
    Dimension abnormalWidth = -10.0_vp;
    SideBarContainerModelInstance.Create();
    SideBarContainerModelInstance.SetDividerStrokeWidth(STROKE_WIDTH);
    SideBarContainerModelInstance.SetDividerColor(Color::BLUE);
    SideBarContainerModelInstance.SetDividerStartMargin(START_MARGIN);
    SideBarContainerModelInstance.SetDividerEndMargin(END_MARGIN);
    SideBarContainerModelInstance.ParseAndSetWidth(WidthType::SIDEBAR_WIDTH, width);
    SideBarContainerModelInstance.ParseAndSetWidth(WidthType::MIN_SIDEBAR_WIDTH, width);
    SideBarContainerModelInstance.ParseAndSetWidth(WidthType::MAX_SIDEBAR_WIDTH, width);
    SideBarContainerModelInstance.ParseAndSetWidth(WidthType::SIDEBAR_WIDTH, abnormalWidth);
    SideBarContainerModelInstance.ParseAndSetWidth(WidthType::MIN_SIDEBAR_WIDTH, abnormalWidth);
    SideBarContainerModelInstance.ParseAndSetWidth(WidthType::MAX_SIDEBAR_WIDTH, abnormalWidth);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto sideBarLayoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    EXPECT_NE(sideBarLayoutProperty, nullptr);
    EXPECT_EQ(sideBarLayoutProperty->GetDividerStrokeWidth(), STROKE_WIDTH);
    EXPECT_EQ(sideBarLayoutProperty->GetDividerColor(), Color::BLUE);
    EXPECT_EQ(sideBarLayoutProperty->GetDividerStartMargin(), START_MARGIN);
    EXPECT_EQ(sideBarLayoutProperty->GetDividerEndMargin(), END_MARGIN);
}

/**
 * @tc.name: SideBarViewTestNg002
 * @tc.desc: Test SideBar OnUpdateShowDivider
 * @tc.type: FUNC
 */
HWTEST_F(SideBarViewTestNg, SideBarViewTestNg002, TestSize.Level1)
{
    SideBarContainerModelNG SideBarContainerModelInstance;
    SideBarContainerModelInstance.Create();
    SideBarContainerModelInstance.SetDividerStrokeWidth(STROKE_WIDTH);
    SideBarContainerModelInstance.SetDividerColor(Color::BLUE);
    SideBarContainerModelInstance.SetDividerStartMargin(START_MARGIN);
    SideBarContainerModelInstance.SetDividerEndMargin(END_MARGIN);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto row = FrameNode::CreateFrameNode(
        V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_NE(row, nullptr);
    auto row2 = FrameNode::CreateFrameNode(
        V2::SIDE_BAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SideBarContainerPattern>());
    EXPECT_NE(row2, nullptr);
    row->MountToParent(frameNode);
    row2->MountToParent(frameNode);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    SideBarContainerModelInstance.Pop();
    frameNode->MarkModifyDone();
}

/**
 * @tc.name: SideBarViewTestNg003
 * @tc.desc: Test SideBar OnUpdateShowDivider
 * @tc.type: FUNC
 */
HWTEST_F(SideBarViewTestNg, SideBarViewTestNg003, TestSize.Level1)
{
    SideBarContainerModelNG SideBarContainerModelInstance;
    SideBarContainerModelInstance.Create();
    SideBarContainerModelInstance.SetDividerStrokeWidth(STROKE_WIDTH);
    SideBarContainerModelInstance.SetDividerColor(Color::BLUE);
    SideBarContainerModelInstance.SetDividerStartMargin(START_MARGIN);
    SideBarContainerModelInstance.SetDividerEndMargin(END_MARGIN);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto row = FrameNode::CreateFrameNode(
        V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_NE(row, nullptr);
    auto row2 = FrameNode::CreateFrameNode(
        V2::SIDE_BAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SideBarContainerPattern>());
    EXPECT_NE(row2, nullptr);
    row->MountToParent(frameNode);
    row2->MountToParent(frameNode);
    auto dividerNode = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<DividerPattern>(); });
    EXPECT_NE(dividerNode, nullptr);
    dividerNode->MountToParent(frameNode);

    int32_t imgNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto imgNode = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, imgNodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    EXPECT_NE(imgNode, nullptr);
    imgNode->MountToParent(frameNode);
    frameNode->MarkModifyDone();
}

/**
 * @tc.name: SideBarViewTestNg004
 * @tc.desc: Test SideBar Measure and layout
 * @tc.type: SideBar Measure
 */
HWTEST_F(SideBarViewTestNg, SideBarViewTestNg004, TestSize.Level1)
{
    SideBarContainerModelNG SideBarContainerModelInstance;
    SideBarContainerModelInstance.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    auto row = FrameNode::CreateFrameNode(
        V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_NE(row, nullptr);

    RefPtr<GeometryNode> rowGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    rowGeometryNode->Reset();
    RefPtr<LayoutWrapper> rowLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(row, rowGeometryNode, row->GetLayoutProperty());
    EXPECT_NE(rowLayoutWrapper, nullptr);
    auto rowPattern = row->GetPattern<LinearLayoutPattern>();
    EXPECT_NE(rowPattern, nullptr);

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    rowLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    auto rowLayoutAlgorithm = rowPattern->CreateLayoutAlgorithm();
    EXPECT_NE(rowLayoutAlgorithm, nullptr);

    rowLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));
    rowLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(5.0f), CalcLength(5.0f)));

    row->MountToParent(frameNode);
    layoutWrapper->AppendChild(rowLayoutWrapper);

    auto siderBar = FrameNode::CreateFrameNode(
        V2::SIDE_BAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SideBarContainerPattern>());
    EXPECT_NE(siderBar, nullptr);

    RefPtr<GeometryNode> siderBarGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    siderBarGeometryNode->Reset();
    RefPtr<LayoutWrapper> sideBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(siderBar, siderBarGeometryNode, siderBar->GetLayoutProperty());
    EXPECT_NE(sideBarLayoutWrapper, nullptr);
    auto siderBarPattern = siderBar->GetPattern<SideBarContainerPattern>();
    EXPECT_NE(siderBarPattern, nullptr);

    sideBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    auto sideBarLayoutAlgorithm = siderBarPattern->CreateLayoutAlgorithm();
    EXPECT_NE(sideBarLayoutAlgorithm, nullptr);

    sideBarLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(sideBarLayoutAlgorithm));
    sideBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(5.0f), CalcLength(5.0f)));

    siderBar->MountToParent(frameNode);
    layoutWrapper->AppendChild(sideBarLayoutWrapper);

    auto dividerNode = FrameNode::GetOrCreateFrameNode(
        V2::DIVIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<DividerPattern>(); });
    EXPECT_NE(dividerNode, nullptr);

    RefPtr<GeometryNode> dividerNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    dividerNodeGeometryNode->Reset();
    RefPtr<LayoutWrapper> dividerNodeLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(dividerNode, dividerNodeGeometryNode, dividerNode->GetLayoutProperty());
    EXPECT_NE(dividerNodeLayoutWrapper, nullptr);
    auto dividerNodePattern = dividerNode->GetPattern<DividerPattern>();
    EXPECT_NE(dividerNodePattern, nullptr);

    dividerNodeLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    auto dividerNodeLayoutAlgorithm = dividerNodePattern->CreateLayoutAlgorithm();
    EXPECT_NE(dividerNodeLayoutAlgorithm, nullptr);

    dividerNodeLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(dividerNodeLayoutAlgorithm));
    dividerNodeLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(5.0f), CalcLength(5.0f)));

    dividerNode->MountToParent(frameNode);
    layoutWrapper->AppendChild(dividerNodeLayoutWrapper);

    int32_t imgNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto imgNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, imgNodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    EXPECT_NE(imgNode, nullptr);

    RefPtr<GeometryNode> imgNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    imgNodeGeometryNode->Reset();
    RefPtr<LayoutWrapper> imgNodeLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(imgNode, imgNodeGeometryNode, imgNode->GetLayoutProperty());
    EXPECT_NE(imgNodeLayoutWrapper, nullptr);
    auto imgNodePattern = imgNode->GetPattern<ImagePattern>();
    EXPECT_NE(imgNodePattern, nullptr);

    imgNodeLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    auto imgNodeLayoutAlgorithm = imgNodePattern->CreateLayoutAlgorithm();
    EXPECT_NE(imgNodeLayoutAlgorithm, nullptr);

    imgNodeLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(imgNodeLayoutAlgorithm));
    imgNodeLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(5.0f), CalcLength(5.0f)));

    imgNode->MountToParent(frameNode);
    layoutWrapper->AppendChild(imgNodeLayoutWrapper);

    auto sideBarContainerPattern = AceType::DynamicCast<SideBarContainerPattern>(frameNode->GetPattern());
    EXPECT_NE(sideBarContainerPattern, nullptr);
    auto sideLayoutAlgorithm = sideBarContainerPattern->CreateLayoutAlgorithm();
    EXPECT_NE(sideLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sideLayoutAlgorithm));

    LayoutConstraintF LayoutConstraintVaildSize;
    LayoutConstraintVaildSize.selfIdealSize.SetSize(SizeF(1000000, 1000000));
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintVaildSize);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    sideLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    sideLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));

    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(layoutWrapper->GetLayoutAlgorithm());
    EXPECT_NE(layoutAlgorithmWrapper, nullptr);
    auto sideBarContainerLayoutAlgorithm = AceType::DynamicCast<SideBarContainerLayoutAlgorithm>
            (layoutAlgorithmWrapper->GetLayoutAlgorithm());
    EXPECT_NE(sideBarContainerLayoutAlgorithm, nullptr);
    sideBarContainerLayoutAlgorithm->SetRealDividerWidth(REAL_WIDTH);
    sideBarContainerLayoutAlgorithm->GetRealDividerWidth();
    sideBarContainerLayoutAlgorithm->SetSideBarStatus(SideBarStatus::SHOW);
    frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>()->UpdateSideBarPosition(SideBarPosition::END);
    sideLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    sideLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));

    sideBarContainerLayoutAlgorithm->SetSideBarStatus(SideBarStatus::HIDDEN);
    frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>()->UpdateSideBarPosition(SideBarPosition::START);
    sideLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    sideLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));

    sideBarContainerLayoutAlgorithm->SetSideBarStatus(SideBarStatus::CHANGING);
    frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>()->UpdateSideBarPosition(SideBarPosition::START);
    sideLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    sideLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));

    sideBarContainerLayoutAlgorithm->SetSideBarStatus(SideBarStatus::HIDDEN);
    frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>()->UpdateSideBarPosition(SideBarPosition::END);
    sideLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    sideLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));

    sideBarContainerLayoutAlgorithm->SetSideBarStatus(SideBarStatus::CHANGING);
    frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>()->UpdateSideBarPosition(SideBarPosition::END);
    sideLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    sideLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    
    frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>
        ()->UpdateSideBarContainerType(SideBarContainerType::AUTO);
    sideLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    sideLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
}

/**
 * @tc.name: SideBarViewTestNg005
 * @tc.desc: Test SideBar AddDividerHotZoneRect
 * @tc.type: FUNC
 */
HWTEST_F(SideBarViewTestNg, SideBarViewTestNg005, TestSize.Level1)
{
    SideBarContainerModelNG SideBarContainerModelInstance;
    SideBarContainerModelInstance.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    auto row = FrameNode::CreateFrameNode(
        V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_NE(row, nullptr);
    row->MountToParent(frameNode);

    auto siderBar = FrameNode::CreateFrameNode(
        V2::SIDE_BAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SideBarContainerPattern>());
    EXPECT_NE(siderBar, nullptr);
    siderBar->MountToParent(frameNode);

    auto dividerNode = FrameNode::GetOrCreateFrameNode(
        V2::DIVIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<DividerPattern>(); });
    EXPECT_NE(dividerNode, nullptr);
    dividerNode->MountToParent(frameNode);

    int32_t imgNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto imgNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, imgNodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    EXPECT_NE(imgNode, nullptr);
    imgNode->MountToParent(frameNode);

    auto sideBarContainerPattern = AceType::DynamicCast<SideBarContainerPattern>(frameNode->GetPattern());
    EXPECT_NE(sideBarContainerPattern, nullptr);
    auto sideLayoutAlgorithm = sideBarContainerPattern->CreateLayoutAlgorithm();
    EXPECT_NE(sideLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sideLayoutAlgorithm));

    LayoutConstraintF LayoutConstraintVaildSize;
    LayoutConstraintVaildSize.selfIdealSize.SetSize(SizeF(1000000, 1000000));
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintVaildSize);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(layoutWrapper->GetLayoutAlgorithm());
    EXPECT_NE(layoutAlgorithmWrapper, nullptr);
    auto sideBarContainerLayoutAlgorithm = AceType::DynamicCast<SideBarContainerLayoutAlgorithm>
            (layoutAlgorithmWrapper->GetLayoutAlgorithm());
    EXPECT_NE(sideBarContainerLayoutAlgorithm, nullptr);
    sideBarContainerLayoutAlgorithm->SetRealDividerWidth(REAL_WIDTH);
    sideBarContainerLayoutAlgorithm->GetRealDividerWidth();
    sideBarContainerPattern->AddDividerHotZoneRect(sideBarContainerLayoutAlgorithm);
}

/**
 * @tc.name: SideBarViewTestNg006
 * @tc.desc: Test SideBar AddDividerHotZoneRect
 * @tc.type: FUNC
 */
HWTEST_F(SideBarViewTestNg, SideBarViewTestNg006, TestSize.Level1)
{
    SideBarContainerModelNG SideBarContainerModelInstance;
    SideBarContainerModelInstance.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    auto row = FrameNode::CreateFrameNode(
        V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_NE(row, nullptr);
    row->MountToParent(frameNode);

    auto siderBar = FrameNode::CreateFrameNode(
        V2::SIDE_BAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SideBarContainerPattern>());
    EXPECT_NE(siderBar, nullptr);
    siderBar->MountToParent(frameNode);

    auto dividerNode = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<DividerPattern>(); });
    EXPECT_NE(dividerNode, nullptr);
    dividerNode->MountToParent(frameNode);

    int32_t imgNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto imgNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, imgNodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    EXPECT_NE(imgNode, nullptr);
    imgNode->MountToParent(frameNode);

    auto sideBarContainerPattern = AceType::DynamicCast<SideBarContainerPattern>(frameNode->GetPattern());
    EXPECT_NE(sideBarContainerPattern, nullptr);
    auto sideLayoutAlgorithm = sideBarContainerPattern->CreateLayoutAlgorithm();
    EXPECT_NE(sideLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sideLayoutAlgorithm));

    LayoutConstraintF LayoutConstraintVaildSize;
    LayoutConstraintVaildSize.selfIdealSize.SetSize(SizeF(1000000, 1000000));
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintVaildSize);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(layoutWrapper->GetLayoutAlgorithm());
    EXPECT_NE(layoutAlgorithmWrapper, nullptr);
    auto sideBarContainerLayoutAlgorithm = AceType::DynamicCast<SideBarContainerLayoutAlgorithm>
            (layoutAlgorithmWrapper->GetLayoutAlgorithm());
    EXPECT_NE(sideBarContainerLayoutAlgorithm, nullptr);
    sideBarContainerLayoutAlgorithm->SetRealDividerWidth(REAL_WIDTH);
    sideBarContainerLayoutAlgorithm->GetRealDividerWidth();
    sideBarContainerPattern->AddDividerHotZoneRect(sideBarContainerLayoutAlgorithm);
}

/**
 * @tc.name: SideBarViewTestNg007
 * @tc.desc: Test SideBar AddDividerHotZoneRect
 * @tc.type: FUNC
 */
HWTEST_F(SideBarViewTestNg, SideBarViewTestNg007, TestSize.Level1)
{
    SideBarContainerModelNG SideBarContainerModelInstance;
    SideBarContainerModelInstance.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    auto sideBarContainerPattern = AceType::DynamicCast<SideBarContainerPattern>(frameNode->GetPattern());
    EXPECT_NE(sideBarContainerPattern, nullptr);
    auto sideLayoutAlgorithm = sideBarContainerPattern->CreateLayoutAlgorithm();
    EXPECT_NE(sideLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sideLayoutAlgorithm));

    LayoutConstraintF LayoutConstraintVaildSize;
    LayoutConstraintVaildSize.selfIdealSize.SetSize(SizeF(1000000, 1000000));
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintVaildSize);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(layoutWrapper->GetLayoutAlgorithm());
    EXPECT_NE(layoutAlgorithmWrapper, nullptr);
    auto sideBarContainerLayoutAlgorithm = AceType::DynamicCast<SideBarContainerLayoutAlgorithm>
            (layoutAlgorithmWrapper->GetLayoutAlgorithm());
    EXPECT_NE(sideBarContainerLayoutAlgorithm, nullptr);
    sideBarContainerLayoutAlgorithm->SetRealDividerWidth(REAL_WIDTH);
    sideBarContainerLayoutAlgorithm->GetRealDividerWidth();
    sideBarContainerPattern->AddDividerHotZoneRect(sideBarContainerLayoutAlgorithm);
}

/**
 * @tc.name: SideBarViewTestNg008
 * @tc.desc: Test SideBar OnHover
 * @tc.type: FUNC
 */
HWTEST_F(SideBarViewTestNg, SideBarViewTestNg008, TestSize.Level1)
{
    SideBarContainerModelNG SideBarContainerModelInstance;
    SideBarContainerModelInstance.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto sideBarContainerPattern = AceType::DynamicCast<SideBarContainerPattern>(frameNode->GetPattern());
    EXPECT_NE(sideBarContainerPattern, nullptr);
    sideBarContainerPattern->OnHover(true);
    sideBarContainerPattern->OnHover(false);
}

/**
 * @tc.name: SideBarViewTestNg009
 * @tc.desc: Test SideBar OnHover
 * @tc.type: FUNC
 */
HWTEST_F(SideBarViewTestNg, SideBarViewTestNg009, TestSize.Level1)
{
    SideBarContainerModelNG SideBarContainerModelInstance;
    SideBarContainerModelInstance.Create();
    SideBarContainerModelInstance.SetDividerStrokeWidth(NONE_WIDTH);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto sideBarContainerPattern = AceType::DynamicCast<SideBarContainerPattern>(frameNode->GetPattern());
    EXPECT_NE(sideBarContainerPattern, nullptr);
    sideBarContainerPattern->OnHover(true);
    sideBarContainerPattern->OnHover(false);
}

/**
 * @tc.name: SideBarViewTestNg010
 * @tc.desc: Test SideBar HandlePanEventEnd
 * @tc.type: FUNC
 */
HWTEST_F(SideBarViewTestNg, SideBarViewTestNg010, TestSize.Level1)
{
    SideBarContainerModelNG SideBarContainerModelInstance;
    SideBarContainerModelInstance.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto sideBarContainerPattern = AceType::DynamicCast<SideBarContainerPattern>(frameNode->GetPattern());
    EXPECT_NE(sideBarContainerPattern, nullptr);
    sideBarContainerPattern->SetSideBarStatus(SideBarStatus::HIDDEN);
    sideBarContainerPattern->HandlePanEventEnd();
    sideBarContainerPattern->SetSideBarStatus(SideBarStatus::AUTO);
    sideBarContainerPattern->HandlePanEventEnd();
}

/**
 * @tc.name: SideBarViewTestNg011
 * @tc.desc: Test SideBar json
 * @tc.type: FUNC
 */
HWTEST_F(SideBarViewTestNg, SideBarViewTestNg011, TestSize.Level1)
{
    SideBarContainerModelNG SideBarContainerModelInstance;
    SideBarContainerModelInstance.Create();
    SideBarContainerModelInstance.SetControlButtonWidth(STROKE_WIDTH);
    SideBarContainerModelInstance.SetDividerStrokeWidth(STROKE_WIDTH);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    auto clone = layoutProperty->Clone();
    clone.Reset();
    auto json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json);
}

/**
 * @tc.name: SideBarViewTestNg012
 * @tc.desc: Test SideBar Pop
 * @tc.type: FUNC
 */
HWTEST_F(SideBarViewTestNg, SideBarViewTestNg012, TestSize.Level1)
{
     /**
     * @tc.steps: step1. create sideBar ,then get sideBarContainerNode.
     * @tc.expected: check whether the children.empty() is true.
     */
    SideBarContainerModelNG SideBarContainerModelInstance;
    SideBarContainerModelInstance.Create();
    SideBarContainerModelInstance.SetDividerStrokeWidth(STROKE_WIDTH);
    SideBarContainerModelInstance.SetDividerColor(Color::BLUE);
    SideBarContainerModelInstance.SetDividerStartMargin(START_MARGIN);
    SideBarContainerModelInstance.SetDividerEndMargin(END_MARGIN);
    
    auto sideBarContainerNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(sideBarContainerNode, nullptr);
    auto children = sideBarContainerNode->GetChildren();
    SideBarContainerModelInstance.Pop();
    EXPECT_TRUE(children.empty());
}

/**
 * @tc.name: SideBarViewTestNg013
 * @tc.desc: Test SideBar Pop_2
 * @tc.type: FUNC
 */
HWTEST_F(SideBarViewTestNg, SideBarViewTestNg013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar ,then get frameNode and pattern.
     */
    SideBarContainerModelNG SideBarContainerModelInstance;
    SideBarContainerModelInstance.Create();
    SideBarContainerModelInstance.SetDividerStrokeWidth(STROKE_WIDTH);
    SideBarContainerModelInstance.SetDividerColor(Color::BLUE);
    SideBarContainerModelInstance.SetDividerStartMargin(START_MARGIN);
    SideBarContainerModelInstance.SetDividerEndMargin(END_MARGIN);
    
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto row = FrameNode::CreateFrameNode(
        V2::SIDE_BAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(row, nullptr);
    row->MountToParent(frameNode);
    ViewStackProcessor::GetInstance()->Push(frameNode);

    auto sideBarContainerNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(sideBarContainerNode, nullptr);
    auto pattern = sideBarContainerNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. make pattern->SetHasControlButton(true).
     * @tc.expected: check whether the pattern->HasControlButton() is true.
     */
    pattern->SetHasControlButton(true);
    SideBarContainerModelInstance.Pop();
    EXPECT_TRUE(pattern->HasControlButton());
}
} // namespace OHOS::Ace::NG
