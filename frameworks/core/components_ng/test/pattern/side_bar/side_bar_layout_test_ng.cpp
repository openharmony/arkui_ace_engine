
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
#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "core/components/common/layout/constants.h"
#include "core/components/side_bar/side_bar_container_component.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_layout_algorithm.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_layout_property.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_model_ng.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_pattern.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
#include "frameworks/base/geometry/ng/size_t.h"
#include "frameworks/core/components_ng/property/property.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr double SIDE_BAR_SIZE = 1.0;
constexpr float SIZEF_WIDTH = 2.0f;
constexpr float SIZEF_HEIGHT = 3.0f;
constexpr float PARENT_WIDTH = 4.0f;
constexpr float MIN_PARENT_WIDTH = 0.0f;
} // namespace

class SideBarLayoutTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void SideBarLayoutTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void SideBarLayoutTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: SideBarLayoutTestNg001
 * @tc.desc: Test SideBar LayoutSideBar
 * @tc.type: FUNC
 */
HWTEST_F(SideBarLayoutTestNg, SideBarLayoutTestNg001, TestSize.Level1)
{
    SideBarContainerModelNG SideBarContainerModelInstance;
    auto sideBarFrameNode =
        FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 0, AceType::MakeRefPtr<SideBarContainerPattern>());
    EXPECT_FALSE(sideBarFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapper> sideBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
    EXPECT_FALSE(sideBarLayoutWrapper == nullptr);
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    SizeF size(SIDE_BAR_SIZE, 0.0);
    sideBarLayoutWrapper->GetGeometryNode()->SetFrameSize(size);
    EXPECT_FALSE(sideBarPattern == nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<SideBarContainerLayoutAlgorithm>();
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    sideBarPattern->sideBarStatus_ = SideBarStatus::SHOW;
    SideBarContainerModelInstance.SetSideBarContainerType(SideBarContainerType::EMBED);
    layoutAlgorithm->LayoutSideBar(AccessibilityManager::RawPtr(sideBarLayoutWrapper), sideBarLayoutWrapper);
    EXPECT_EQ(layoutAlgorithm->sideBarOffset_.GetX(), 0);
}

/**
 * @tc.name: SideBarLayoutTestNg002
 * @tc.desc: Test SideBar LayoutSideBar
 * @tc.type: FUNC
 */
HWTEST_F(SideBarLayoutTestNg, SideBarLayoutTestNg002, TestSize.Level1)
{
    SideBarContainerModelNG SideBarContainerModelInstance;
    auto sideBarFrameNode =
        FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 0, AceType::MakeRefPtr<SideBarContainerPattern>());
    EXPECT_FALSE(sideBarFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapper> sideBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
    EXPECT_FALSE(sideBarLayoutWrapper == nullptr);
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    SizeF size(SIDE_BAR_SIZE, 0.0);
    sideBarLayoutWrapper->GetGeometryNode()->SetFrameSize(size);
    EXPECT_FALSE(sideBarPattern == nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<SideBarContainerLayoutAlgorithm>();
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    sideBarPattern->sideBarStatus_ = SideBarStatus::HIDDEN;
    SideBarContainerModelInstance.SetSideBarContainerType(SideBarContainerType::EMBED);
    layoutAlgorithm->LayoutSideBar(AccessibilityManager::RawPtr(sideBarLayoutWrapper), sideBarLayoutWrapper);
    EXPECT_EQ(layoutAlgorithm->sideBarOffset_.GetX(), 0);
}

/**
 * @tc.name: SideBarLayoutTestNg003
 * @tc.desc: Test SideBar LayoutSideBar
 * @tc.type: FUNC
 */
HWTEST_F(SideBarLayoutTestNg, SideBarLayoutTestNg003, TestSize.Level1)
{
    SideBarContainerModelNG SideBarContainerModelInstance;
    auto sideBarFrameNode =
        FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 0, AceType::MakeRefPtr<SideBarContainerPattern>());
    EXPECT_FALSE(sideBarFrameNode == nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapper> sideBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
    EXPECT_FALSE(sideBarLayoutWrapper == nullptr);
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    SizeF size(SIDE_BAR_SIZE, 0.0);
    sideBarLayoutWrapper->GetGeometryNode()->SetFrameSize(size);
    EXPECT_FALSE(sideBarPattern == nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<SideBarContainerLayoutAlgorithm>();
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    sideBarPattern->sideBarStatus_ = SideBarStatus::CHANGING;
    SideBarContainerModelInstance.SetSideBarContainerType(SideBarContainerType::EMBED);
    layoutAlgorithm->LayoutSideBar(AccessibilityManager::RawPtr(sideBarLayoutWrapper), sideBarLayoutWrapper);
    EXPECT_EQ(layoutAlgorithm->sideBarOffset_.GetX(), 0);
}

/**
 * @tc.name: SideBarLayoutTestNg004
 * @tc.desc: Test SideBar LayoutSideBarContent
 * @tc.type: FUNC
 */
HWTEST_F(SideBarLayoutTestNg, SideBarLayoutTestNg004, TestSize.Level1)
{
    SideBarContainerModelNG SideBarContainerModelInstance;
    auto sideBarFrameNode =
        FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 0, AceType::MakeRefPtr<SideBarContainerPattern>());
    EXPECT_FALSE(sideBarFrameNode == nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapper> sideBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
    EXPECT_FALSE(sideBarLayoutWrapper == nullptr);
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    EXPECT_FALSE(sideBarPattern == nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<SideBarContainerLayoutAlgorithm>();
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    sideBarPattern->sideBarStatus_ = SideBarStatus::SHOW;
    SideBarContainerModelInstance.SetSideBarContainerType(SideBarContainerType::EMBED);
    layoutAlgorithm->LayoutSideBarContent(AccessibilityManager::RawPtr(sideBarLayoutWrapper), sideBarLayoutWrapper);
    EXPECT_EQ(layoutAlgorithm->realSideBarWidth_, 0);
}

/**
 * @tc.name: SideBarLayoutTestNg005
 * @tc.desc: Test SideBar MeasureSideBarContent
 * @tc.type: FUNC
 */
HWTEST_F(SideBarLayoutTestNg, SideBarLayoutTestNg005, TestSize.Level1)
{
    SideBarContainerModelNG SideBarContainerModelInstance;
    auto sideBarFrameNode =
        FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 0, AceType::MakeRefPtr<SideBarContainerPattern>());
    EXPECT_FALSE(sideBarFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
    EXPECT_FALSE(layoutWrapper == nullptr);
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    EXPECT_FALSE(sideBarPattern == nullptr);
    auto sideBarLayoutProperty = sideBarPattern->GetLayoutProperty<SideBarContainerLayoutProperty>();
    EXPECT_FALSE(sideBarLayoutProperty == nullptr);
    SizeF value(SIZEF_WIDTH, SIZEF_HEIGHT);
    sideBarLayoutProperty->UpdateMarginSelfIdealSize(value);
    sideBarLayoutProperty->UpdateContentConstraint();
    float parentWidth = PARENT_WIDTH;
    auto layoutAlgorithm = AceType::MakeRefPtr<SideBarContainerLayoutAlgorithm>();
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    sideBarPattern->sideBarStatus_ = SideBarStatus::SHOW;
    SideBarContainerModelInstance.SetSideBarContainerType(SideBarContainerType::EMBED);
    layoutAlgorithm->MeasureSideBarContent(sideBarLayoutProperty, layoutWrapper, parentWidth);
    EXPECT_NE(layoutWrapper->layoutProperty_, nullptr);
    EXPECT_NE(layoutWrapper->geometryNode_, nullptr);
}

/**
 * @tc.name: SideBarLayoutTestNg006
 * @tc.desc: Test SideBar MeasureSideBarContent
 * @tc.type: FUNC
 */
HWTEST_F(SideBarLayoutTestNg, SideBarLayoutTestNg006, TestSize.Level1)
{
    SideBarContainerModelNG SideBarContainerModelInstance;
    auto sideBarFrameNode =
        FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 0, AceType::MakeRefPtr<SideBarContainerPattern>());
    EXPECT_FALSE(sideBarFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
    EXPECT_FALSE(layoutWrapper == nullptr);
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    EXPECT_FALSE(sideBarPattern == nullptr);
    auto sideBarLayoutProperty = sideBarPattern->GetLayoutProperty<SideBarContainerLayoutProperty>();
    EXPECT_FALSE(sideBarLayoutProperty == nullptr);

    SizeF value(SIZEF_WIDTH, SIZEF_HEIGHT);
    sideBarLayoutProperty->UpdateMarginSelfIdealSize(value);
    sideBarLayoutProperty->UpdateContentConstraint();
    float parentWidth = PARENT_WIDTH;
    auto layoutAlgorithm = AceType::MakeRefPtr<SideBarContainerLayoutAlgorithm>();
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    sideBarPattern->sideBarStatus_ = SideBarStatus::CHANGING;
    SideBarContainerModelInstance.SetSideBarContainerType(SideBarContainerType::EMBED);
    layoutAlgorithm->MeasureSideBarContent(sideBarLayoutProperty, layoutWrapper, parentWidth);
    EXPECT_NE(layoutWrapper->layoutProperty_, nullptr);
    EXPECT_NE(layoutWrapper->geometryNode_, nullptr);
}

/**
 * @tc.name: SideBarLayoutTestNg007
 * @tc.desc: Test SideBar MeasureSideBar
 * @tc.type: FUNC
 */
HWTEST_F(SideBarLayoutTestNg, SideBarLayoutTestNg007, TestSize.Level1)
{
    auto sideBarFrameNode =
        FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 0, AceType::MakeRefPtr<SideBarContainerPattern>());
    EXPECT_FALSE(sideBarFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
    EXPECT_FALSE(layoutWrapper == nullptr);
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    EXPECT_FALSE(sideBarPattern == nullptr);
    auto sideBarLayoutProperty = sideBarPattern->GetLayoutProperty<SideBarContainerLayoutProperty>();
    EXPECT_FALSE(sideBarLayoutProperty == nullptr);
    SizeF value(SIZEF_WIDTH, SIZEF_HEIGHT);
    sideBarLayoutProperty->UpdateMarginSelfIdealSize(value);
    sideBarLayoutProperty->UpdateContentConstraint();
    auto layoutAlgorithm = AceType::MakeRefPtr<SideBarContainerLayoutAlgorithm>();
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    layoutAlgorithm->MeasureSideBar(sideBarLayoutProperty, layoutWrapper);
    EXPECT_NE(layoutAlgorithm->realSideBarHeight_, 0);
    EXPECT_NE(layoutWrapper->layoutProperty_, nullptr);
    EXPECT_NE(layoutWrapper->geometryNode_, nullptr);
}

/**
 * @tc.name: SideBarLayoutTestNg008
 * @tc.desc: Test SideBar AutoMode
 * @tc.type: FUNC
 */
HWTEST_F(SideBarLayoutTestNg, SideBarLayoutTestNg008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SideBar and frameNode.
     */
    auto sideBarFrameNode =
        FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 0, AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(sideBarFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<SideBarContainerLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    auto layoutProperty = AceType::DynamicCast<SideBarContainerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. set parentWidth > (minSidebarWidth + minContentWidth)
     * @tc.expected: SideBarContainerType == EMBED
     */
    float parentWidth = PARENT_WIDTH;
    layoutAlgorithm->AutoMode(layoutProperty, parentWidth);
    EXPECT_EQ(layoutAlgorithm->type_, SideBarContainerType::EMBED);

    /**
     * @tc.steps: step3. set parentWidth < (minSidebarWidth + minContentWidth)
     * @tc.expected: SideBarContainerType == OVERLAY
     */
    parentWidth = MIN_PARENT_WIDTH;
    layoutAlgorithm->minContentWidth_ = 1.0f;
    layoutAlgorithm->AutoMode(layoutProperty, parentWidth);
    EXPECT_EQ(layoutAlgorithm->type_, SideBarContainerType::OVERLAY);
}

/**
 * @tc.name: SideBarLayoutTestNg009
 * @tc.desc: Test SideBar AutoChangeSideBarWidth
 * @tc.type: FUNC
 */
HWTEST_F(SideBarLayoutTestNg, SideBarLayoutTestNg009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SideBar and frameNode.
     */
    auto sideBarFrameNode =
        FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 0, AceType::MakeRefPtr<SideBarContainerPattern>());
    EXPECT_FALSE(sideBarFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
    EXPECT_FALSE(layoutWrapper == nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<SideBarContainerLayoutAlgorithm>();
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    auto layoutProperty = AceType::DynamicCast<SideBarContainerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. set parentWidth < (realSidebarWidth + minContentWidth)
     * @tc.expected: realSidebarWidth change
     */
    auto parentWidth = MIN_PARENT_WIDTH;
    layoutAlgorithm->minContentWidth_ = 2.0f;
    layoutAlgorithm->realSideBarWidth_ = 2.0f;
    layoutAlgorithm->minSideBarWidth_ = 1.0f;
    layoutAlgorithm->AutoChangeSideBarWidth(layoutProperty, parentWidth);
    EXPECT_NE(layoutAlgorithm->realSideBarWidth_, 2.0f);
}
} // namespace OHOS::Ace::NG
