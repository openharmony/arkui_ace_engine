
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
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

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
#include "core/components_ng/pattern/side_bar/side_bar_container_paint_method.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_paint_property.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_v2/inspector/inspector_constants.h"
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
constexpr float MAX_PARENT_WIDTH = 50.0f;
constexpr float DEFAULT_REAL_SIDEBAR = 15.0f;
constexpr float DEFAULT_MIN_SIDEBAR = 10.0f;
constexpr float DEFAULT_MAX_SIDEBAR = 20.0f;
constexpr float DEFAULT_MIN_CONTENT = 20.0f;
constexpr float UNDEFINE_VALUE = -1.0f;
constexpr static int32_t TEST_VALUE = 12;
constexpr Dimension DEFAULT_MIN_SIDE_BAR_WIDTH = 290.0_vp;
constexpr Dimension DEFAULT_MAX_SIDE_BAR_WIDTH = 200.0_vp;
constexpr Dimension DEFAULT_MIN = 0.0_vp;
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
const SizeF CONTAINER_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
constexpr Dimension DEFAULT_CONTROL_BUTTON_LEFT = 16.0_vp;
} // namespace

class SideBarLayoutTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void SideBarLayoutTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void SideBarLayoutTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
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
    RefPtr<LayoutWrapperNode> sideBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
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
    RefPtr<LayoutWrapperNode> sideBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
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
    RefPtr<LayoutWrapperNode> sideBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
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
    RefPtr<LayoutWrapperNode> sideBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
    EXPECT_FALSE(sideBarLayoutWrapper == nullptr);
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    EXPECT_FALSE(sideBarPattern == nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<SideBarContainerLayoutAlgorithm>();
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    sideBarPattern->sideBarStatus_ = SideBarStatus::SHOW;
    SideBarContainerModelInstance.SetSideBarContainerType(SideBarContainerType::EMBED);
    layoutAlgorithm->LayoutSideBarContent(AccessibilityManager::RawPtr(sideBarLayoutWrapper), sideBarLayoutWrapper);
    EXPECT_NE(layoutAlgorithm->realSideBarWidth_, 0);
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
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
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
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
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
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
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
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
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
    layoutAlgorithm->typeUpdateWidth_ = 10.0f;
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
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
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

/**
 * @tc.name: SideBarLayoutTestNg010
 * @tc.desc: Test SideBar MeasureTypeUpdateWidth();
 * @tc.type: FUNC
 */
HWTEST_F(SideBarLayoutTestNg, SideBarLayoutTestNg010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SideBar and frameNode.
     */
    auto sideBarFrameNode =
        FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 0, AceType::MakeRefPtr<SideBarContainerPattern>());
    EXPECT_FALSE(sideBarFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
    EXPECT_FALSE(layoutWrapper == nullptr);
    auto layoutProperty = AceType::DynamicCast<SideBarContainerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<SideBarContainerLayoutAlgorithm>();
    EXPECT_NE(layoutAlgorithm, nullptr);
    layoutAlgorithm->defaultMinSideBarWidth_ = DEFAULT_MIN_SIDEBAR;
    layoutAlgorithm->defaultMinContentWidth_ = DEFAULT_MIN_CONTENT;
    layoutAlgorithm->MeasureTypeUpdateWidth();
    EXPECT_EQ(layoutAlgorithm->typeUpdateWidth_, 30.0f);

    /**
     * @tc.steps: step2. minSideBarWidth >= 0.0f && minContentWidth >= 0.0f
     * @tc.expected:typeUpdateWidth_ = minSideBarWidth_ + minContentWidth_
     */
    layoutAlgorithm->minContentWidth_ = 2.0f;
    layoutAlgorithm->minSideBarWidth_ = 2.0f;
    layoutAlgorithm->MeasureTypeUpdateWidth();
    EXPECT_EQ(layoutAlgorithm->typeUpdateWidth_, 4.0f);

    /**
     * @tc.steps: step3. minSideBarWidth < 0.0f && minContentWidth >= 0.0f
     * @tc.expected:typeUpdateWidth_ = defaultMinSideBarWidth+ minContentWidth_
     */
    layoutAlgorithm->minContentWidth_ = 2.0f;
    layoutAlgorithm->minSideBarWidth_ = UNDEFINE_VALUE;
    layoutAlgorithm->MeasureTypeUpdateWidth();
    EXPECT_EQ(layoutAlgorithm->typeUpdateWidth_, 30.0f);

    /**
     * @tc.steps: step4. minSideBarWidth >= 0.0f && minContentWidth < 0.0f
     * @tc.expected:typeUpdateWidth_ = minSideBarWidth_ + defaultMinContentWidth_;
     */
    layoutAlgorithm->minContentWidth_ = UNDEFINE_VALUE;
    layoutAlgorithm->minSideBarWidth_ = 2.0f;
    layoutAlgorithm->MeasureTypeUpdateWidth();
    EXPECT_EQ(layoutAlgorithm->typeUpdateWidth_, 30.0f);

    /**
     * @tc.steps: step5. minSideBarWidth < 0.0f && minContentWidth < 0.0f
     * @tc.expected:typeUpdateWidth_ = defaultMinSideBarWidth_ + defaultMinContentWidth_;
     */
    layoutAlgorithm->minContentWidth_ = UNDEFINE_VALUE;
    layoutAlgorithm->minSideBarWidth_ = UNDEFINE_VALUE;
    layoutAlgorithm->MeasureTypeUpdateWidth();
    EXPECT_EQ(layoutAlgorithm->typeUpdateWidth_, 30.0f);
}

/**
 * @tc.name: SideBarLayoutTestNg011
 * @tc.desc: Test SideBar InitSideBarWidth(parentWidth);
 * @tc.type: FUNC
 */
HWTEST_F(SideBarLayoutTestNg, SideBarLayoutTestNg011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SideBar and frameNode.
     */
    auto layoutAlgorithm = AceType::MakeRefPtr<SideBarContainerLayoutAlgorithm>();
    EXPECT_NE(layoutAlgorithm, nullptr);
    auto parentWidth = MAX_PARENT_WIDTH;
    layoutAlgorithm->defaultRealSideBarWidth_ = DEFAULT_REAL_SIDEBAR;
    layoutAlgorithm->defaultMinSideBarWidth_ = DEFAULT_MIN_SIDEBAR;
    layoutAlgorithm->defaultMaxSideBarWidth_ = DEFAULT_MAX_SIDEBAR;
    layoutAlgorithm->defaultMinContentWidth_ = DEFAULT_MIN_CONTENT;
    layoutAlgorithm->InitSideBarWidth(parentWidth);
    layoutAlgorithm->MeasureRealSideBarWidth(parentWidth);
    EXPECT_EQ(layoutAlgorithm->minSideBarWidth_, DEFAULT_MIN_SIDEBAR);

    /**
     * @tc.steps: step2. minSideBarWidth_ >= parentWidth
     * @tc.expected:minSideBarWidth_ = parentWidth;
     */
    parentWidth = PARENT_WIDTH;
    layoutAlgorithm->realSideBarWidth_ = UNDEFINE_VALUE;
    layoutAlgorithm->minSideBarWidth_ = DEFAULT_MIN_SIDEBAR;
    layoutAlgorithm->maxSideBarWidth_ = UNDEFINE_VALUE;
    layoutAlgorithm->InitSideBarWidth(parentWidth);
    layoutAlgorithm->MeasureRealSideBarWidth(parentWidth);
    EXPECT_EQ(layoutAlgorithm->minSideBarWidth_, parentWidth);

    /**
     * @tc.steps: step3. maxSideBarWidth_ >= parentWidth
     * @tc.expected:maxSideBarWidth_ = parentWidth;
     */
    layoutAlgorithm->realSideBarWidth_ = UNDEFINE_VALUE;
    layoutAlgorithm->minSideBarWidth_ = UNDEFINE_VALUE;
    layoutAlgorithm->maxSideBarWidth_ = DEFAULT_MAX_SIDEBAR;
    layoutAlgorithm->InitSideBarWidth(parentWidth);
    layoutAlgorithm->MeasureRealSideBarWidth(parentWidth);
    EXPECT_EQ(layoutAlgorithm->maxSideBarWidth_, parentWidth);

    /**
     * @tc.steps: step4. realSideBarWidth_ >= parentWidth
     * @tc.expected:realSideBarWidth_ = parentWidth;
     */
    layoutAlgorithm->realSideBarWidth_ = DEFAULT_MAX_SIDEBAR;
    layoutAlgorithm->minSideBarWidth_ = UNDEFINE_VALUE;
    layoutAlgorithm->maxSideBarWidth_ = UNDEFINE_VALUE;
    layoutAlgorithm->InitSideBarWidth(parentWidth);
    layoutAlgorithm->MeasureRealSideBarWidth(parentWidth);
    EXPECT_EQ(layoutAlgorithm->maxSideBarWidth_, parentWidth);

    /**
     * @tc.steps: step5. minSideBarWidth_ >= maxSideBarWidth_
     * @tc.expected:minSideBarWidth_ == maxSideBarWidth_
     */
    parentWidth = MAX_PARENT_WIDTH;
    layoutAlgorithm->realSideBarWidth_ = UNDEFINE_VALUE;
    layoutAlgorithm->minSideBarWidth_ = DEFAULT_MAX_SIDEBAR;
    layoutAlgorithm->maxSideBarWidth_ = DEFAULT_MIN_SIDEBAR;
    layoutAlgorithm->InitSideBarWidth(parentWidth);
    layoutAlgorithm->MeasureRealSideBarWidth(parentWidth);
    EXPECT_EQ(layoutAlgorithm->maxSideBarWidth_, layoutAlgorithm->minSideBarWidth_);

    /**
     * @tc.steps: step6. realSideBarWidth_ >= parentWidth
     * @tc.expected:realSideBarWidth_ == parentWidth
     */
    parentWidth = PARENT_WIDTH;
    layoutAlgorithm->realSideBarWidth_ = DEFAULT_REAL_SIDEBAR;
    layoutAlgorithm->minSideBarWidth_ = UNDEFINE_VALUE;
    layoutAlgorithm->maxSideBarWidth_ = UNDEFINE_VALUE;
    layoutAlgorithm->InitSideBarWidth(parentWidth);
    layoutAlgorithm->MeasureRealSideBarWidth(parentWidth);
    EXPECT_EQ(layoutAlgorithm->realSideBarWidth_, parentWidth);
}

/**
 * @tc.name: SideBarLayoutTestNg012
 * @tc.desc: Test SideBar MeasureRealSideBarWidth(parentWidth);
 * @tc.type: FUNC
 */
HWTEST_F(SideBarLayoutTestNg, SideBarLayoutTestNg012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SideBar and frameNode.
     */
    auto layoutAlgorithm = AceType::MakeRefPtr<SideBarContainerLayoutAlgorithm>();
    EXPECT_NE(layoutAlgorithm, nullptr);
    auto parentWidth = MAX_PARENT_WIDTH;
    layoutAlgorithm->defaultRealSideBarWidth_ = DEFAULT_REAL_SIDEBAR;
    layoutAlgorithm->defaultMinSideBarWidth_ = DEFAULT_MIN_SIDEBAR;
    layoutAlgorithm->defaultMaxSideBarWidth_ = DEFAULT_MAX_SIDEBAR;
    layoutAlgorithm->MeasureRealSideBarWidth(parentWidth);

    /**
     * @tc.steps: step2. undefine minSideBarWidth and define maxSideBarWidth
     * @tc.expected:minSideBarWidth = defaultMinSideBarWidth_;
     */
    layoutAlgorithm->realSideBarWidth_ = UNDEFINE_VALUE;
    layoutAlgorithm->minSideBarWidth_ = UNDEFINE_VALUE;
    layoutAlgorithm->maxSideBarWidth_ = DEFAULT_MAX_SIDEBAR;
    layoutAlgorithm->MeasureRealSideBarWidth(parentWidth);
    EXPECT_EQ(layoutAlgorithm->minSideBarWidth_, layoutAlgorithm->defaultMinSideBarWidth_);

    /**
     * @tc.steps: step3. undefine maxSideBarWidth and define sideBarWidth
     * @tc.expected:maxSideBarWidth_ = defaultMaxSideBarWidth_;
     */
    layoutAlgorithm->realSideBarWidth_ = DEFAULT_MAX_SIDEBAR;
    layoutAlgorithm->minSideBarWidth_ = UNDEFINE_VALUE;
    layoutAlgorithm->maxSideBarWidth_ = UNDEFINE_VALUE;
    layoutAlgorithm->MeasureRealSideBarWidth(parentWidth);
    EXPECT_EQ(layoutAlgorithm->maxSideBarWidth_, layoutAlgorithm->defaultMaxSideBarWidth_);

    /**
     * @tc.steps: step4. undefine maxSideBarWidth and define minSideBarWidth
     * @tc.expected:maxSideBarWidth_ = defaultMaxSideBarWidth_;
     */
    layoutAlgorithm->realSideBarWidth_ = UNDEFINE_VALUE;
    layoutAlgorithm->minSideBarWidth_ = DEFAULT_MAX_SIDEBAR;
    layoutAlgorithm->maxSideBarWidth_ = UNDEFINE_VALUE;
    layoutAlgorithm->MeasureRealSideBarWidth(parentWidth);
    EXPECT_EQ(layoutAlgorithm->maxSideBarWidth_, layoutAlgorithm->defaultMaxSideBarWidth_);

    /**
     * @tc.steps: step5. undefine sideBarWidth and define minSideBarWidth
     * @tc.expected:sideBarWidth = defaultRealSideBarWidth_;
     */
    layoutAlgorithm->realSideBarWidth_ = UNDEFINE_VALUE;
    layoutAlgorithm->minSideBarWidth_ = DEFAULT_REAL_SIDEBAR;
    layoutAlgorithm->maxSideBarWidth_ = UNDEFINE_VALUE;
    layoutAlgorithm->MeasureRealSideBarWidth(parentWidth);
    EXPECT_EQ(layoutAlgorithm->realSideBarWidth_, layoutAlgorithm->defaultRealSideBarWidth_);

    /**
     * @tc.steps: step6. undefine sideBarWidth and define maxSideBarWidth
     * @tc.expected:sideBarWidth = defaultRealSideBarWidth_;
     */
    layoutAlgorithm->realSideBarWidth_ = UNDEFINE_VALUE;
    layoutAlgorithm->minSideBarWidth_ = UNDEFINE_VALUE;
    layoutAlgorithm->maxSideBarWidth_ = DEFAULT_REAL_SIDEBAR;
    layoutAlgorithm->MeasureRealSideBarWidth(parentWidth);
    EXPECT_EQ(layoutAlgorithm->realSideBarWidth_, layoutAlgorithm->defaultRealSideBarWidth_);

    /**
     * @tc.steps: step7. realSideBarWidth_ < minSideBarWidth_
     * @tc.expected:realSideBarWidth_ == minSideBarWidth_
     */
    parentWidth = MAX_PARENT_WIDTH;
    layoutAlgorithm->realSideBarWidth_ = DEFAULT_MIN_SIDEBAR;
    layoutAlgorithm->minSideBarWidth_ = DEFAULT_REAL_SIDEBAR;
    layoutAlgorithm->maxSideBarWidth_ = UNDEFINE_VALUE;
    layoutAlgorithm->InitSideBarWidth(parentWidth);
    layoutAlgorithm->MeasureRealSideBarWidth(parentWidth);
    EXPECT_EQ(layoutAlgorithm->realSideBarWidth_, layoutAlgorithm->minSideBarWidth_);

    /**
     * @tc.steps: step8. realSideBarWidth_ > maxSideBarWidth_
     * @tc.expected:realSideBarWidth_ == maxSideBarWidth_
     */
    parentWidth = DEFAULT_REAL_SIDEBAR;
    layoutAlgorithm->maxSideBarWidth_ = DEFAULT_REAL_SIDEBAR;
    layoutAlgorithm->minSideBarWidth_ = DEFAULT_MIN_SIDEBAR;
    layoutAlgorithm->realSideBarWidth_ = DEFAULT_MAX_SIDEBAR;
    layoutAlgorithm->InitSideBarWidth(parentWidth);
    layoutAlgorithm->MeasureRealSideBarWidth(parentWidth);
    EXPECT_EQ(layoutAlgorithm->realSideBarWidth_, layoutAlgorithm->maxSideBarWidth_);
}

/**
 * @tc.name: SideBarLayoutTestNg013
 * @tc.desc: Test SideBar GetAllPropertyValue
 * @tc.type: FUNC
 */
HWTEST_F(SideBarLayoutTestNg, SideBarLayoutTestNg013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SideBar and frameNode.
     */
    auto sideBarFrameNode =
        FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 0, AceType::MakeRefPtr<SideBarContainerPattern>());
    EXPECT_FALSE(sideBarFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
    EXPECT_FALSE(layoutWrapper == nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<SideBarContainerLayoutAlgorithm>();
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    auto layoutProperty = AceType::DynamicCast<SideBarContainerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    auto sideBarContainerPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(sideBarContainerPattern, nullptr);
    auto parentWidth = MAX_PARENT_WIDTH;
    layoutAlgorithm->defaultRealSideBarWidth_ = DEFAULT_REAL_SIDEBAR;
    layoutAlgorithm->defaultMinSideBarWidth_ = DEFAULT_MIN_SIDEBAR;
    layoutAlgorithm->defaultMaxSideBarWidth_ = DEFAULT_MAX_SIDEBAR;
    layoutAlgorithm->SetPattern(AceType::WeakClaim(AceType::RawPtr(sideBarContainerPattern)));
    layoutAlgorithm->GetAllPropertyValue(layoutProperty, parentWidth);

    /**
     * @tc.steps: step2. realSideBarWidth_ > maxSideBarWidth_
     * @tc.expected:realSideBarWidth_ == maxSideBarWidth_
     */
    layoutAlgorithm->maxSideBarWidth_ = DEFAULT_REAL_SIDEBAR;
    layoutAlgorithm->minSideBarWidth_ = DEFAULT_MIN_SIDEBAR;
    layoutAlgorithm->realSideBarWidth_ = DEFAULT_MAX_SIDEBAR;
    layoutAlgorithm->InitSideBarWidth(parentWidth);
    layoutAlgorithm->MeasureRealSideBarWidth(parentWidth);
    EXPECT_EQ(layoutAlgorithm->realSideBarWidth_, layoutAlgorithm->maxSideBarWidth_);
}

/**
 * @tc.name: SideBarLayoutTestNg014
 * @tc.desc: Test SideBar AdjustMinAndMaxSideBarWidth
 * @tc.type: FUNC
 */
HWTEST_F(SideBarLayoutTestNg, SideBarLayoutTestNg014, TestSize.Level1)
{
    auto sideBarFrameNode =
        FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 0, AceType::MakeRefPtr<SideBarContainerPattern>());
    EXPECT_FALSE(sideBarFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    auto layoutWrapper = LayoutWrapperNode(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    EXPECT_FALSE(sideBarPattern == nullptr);
    auto sideBarLayoutProperty = sideBarPattern->GetLayoutProperty<SideBarContainerLayoutProperty>();
    EXPECT_FALSE(sideBarLayoutProperty == nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<SideBarContainerLayoutAlgorithm>();
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    auto tempFrame =
        FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 0, AceType::MakeRefPtr<SideBarContainerPattern>());
    EXPECT_FALSE(tempFrame == nullptr);
    auto tempLayoutWrapper = tempFrame->CreateLayoutWrapper();
    EXPECT_FALSE(tempLayoutWrapper == nullptr);
    layoutWrapper.cachedList_ = std::list<RefPtr<LayoutWrapper>>();
    layoutAlgorithm->GetSideBarLayoutWrapper(&layoutWrapper);
    layoutWrapper.cachedList_.push_back(tempLayoutWrapper);
    layoutWrapper.cachedList_.push_back(tempLayoutWrapper);
    layoutWrapper.cachedList_.push_back(tempLayoutWrapper);
    layoutWrapper.cachedList_.push_back(tempLayoutWrapper);
    layoutAlgorithm->GetSideBarLayoutWrapper(&layoutWrapper);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->minPlatformVersion_ = 12;
    layoutAlgorithm->UpdateDefaultValueByVersion();
    sideBarLayoutProperty->UpdateMinSideBarWidth(DEFAULT_MIN_SIDE_BAR_WIDTH);
    sideBarLayoutProperty->UpdateMaxSideBarWidth(DEFAULT_MAX_SIDE_BAR_WIDTH);
    layoutAlgorithm->AdjustMinAndMaxSideBarWidth(&layoutWrapper);
    EXPECT_EQ(layoutAlgorithm->minSideBarWidth_, layoutAlgorithm->maxSideBarWidth_);
}

/**
 * @tc.name: SideBarLayoutTestNg015
 * @tc.desc: Test SideBar MeasureSideBar
 * @tc.type: FUNC
 */
HWTEST_F(SideBarLayoutTestNg, SideBarLayoutTestNg015, TestSize.Level1)
{
    auto sideBarFrameNode =
        FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 0, AceType::MakeRefPtr<SideBarContainerPattern>());
    EXPECT_FALSE(sideBarFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
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
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->minPlatformVersion_ = TEST_VALUE;
    layoutAlgorithm->MeasureSideBar(sideBarLayoutProperty, layoutWrapper);
    EXPECT_NE(layoutAlgorithm->realSideBarHeight_, 0);
    EXPECT_NE(layoutWrapper->layoutProperty_, nullptr);
    EXPECT_NE(layoutWrapper->geometryNode_, nullptr);
    layoutWrapper->layoutProperty_ = AceType::MakeRefPtr<LayoutProperty>();
    layoutWrapper->layoutProperty_->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutWrapper->layoutProperty_->calcLayoutConstraint_->maxSize =
        CalcSize(CalcLength(SIDE_BAR_SIZE), CalcLength(SIZEF_WIDTH));
    layoutWrapper->layoutProperty_->calcLayoutConstraint_->minSize =
        CalcSize(CalcLength(SIDE_BAR_SIZE), CalcLength(SIZEF_WIDTH));
    layoutAlgorithm->MeasureSideBar(sideBarLayoutProperty, layoutWrapper);
    sideBarLayoutProperty->UpdateMaxSideBarWidth(Dimension(SIZEF_HEIGHT));
    sideBarLayoutProperty->UpdateMinSideBarWidth(Dimension(SIDE_BAR_SIZE));
    layoutAlgorithm->MeasureSideBar(sideBarLayoutProperty, layoutWrapper);
    EXPECT_NE(layoutAlgorithm->realSideBarHeight_, 0);
    EXPECT_NE(layoutWrapper->layoutProperty_, nullptr);
    EXPECT_NE(layoutWrapper->geometryNode_, nullptr);
}

/**
 * @tc.name: SideBarLayoutTestNg016
 * @tc.desc: Test SideBar GetSideBarPositionWithRtl
 * @tc.type: FUNC
 */
HWTEST_F(SideBarLayoutTestNg, SideBarLayoutTestNg016, TestSize.Level1)
{
    auto sideBarFrameNode =
        FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 0, AceType::MakeRefPtr<SideBarContainerPattern>());
    EXPECT_FALSE(sideBarFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
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
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->minPlatformVersion_ = TEST_VALUE;
    layoutWrapper->layoutProperty_ = AceType::MakeRefPtr<LayoutProperty>();
    layoutWrapper->layoutProperty_->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    sideBarLayoutProperty->UpdateMaxSideBarWidth(Dimension(SIZEF_HEIGHT));
    sideBarLayoutProperty->UpdateMinSideBarWidth(Dimension(SIDE_BAR_SIZE));
    layoutAlgorithm->MeasureSideBar(sideBarLayoutProperty, layoutWrapper);
    EXPECT_NE(layoutAlgorithm->realSideBarHeight_, 0);
    EXPECT_NE(layoutWrapper->layoutProperty_, nullptr);
    EXPECT_NE(layoutWrapper->geometryNode_, nullptr);
    sideBarLayoutProperty->layoutDirection_ = TextDirection::RTL;
    layoutAlgorithm->GetSideBarPositionWithRtl(sideBarLayoutProperty);
    EXPECT_NE(layoutWrapper->layoutProperty_, nullptr);
}

/**
 * @tc.name: SideBarLayoutTestNg017
 * @tc.desc: Test SideBar MeasureDivider
 * @tc.type: FUNC
 */
HWTEST_F(SideBarLayoutTestNg, SideBarLayoutTestNg017, TestSize.Level1)
{
    auto sideBarFrameNode =
        FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 0, AceType::MakeRefPtr<SideBarContainerPattern>());
    EXPECT_FALSE(sideBarFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
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
    auto parentWidth = MAX_PARENT_WIDTH;
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->minPlatformVersion_ = TEST_VALUE;
    layoutAlgorithm->MeasureDivider(sideBarLayoutProperty, layoutWrapper, parentWidth);
    EXPECT_NE(layoutWrapper->layoutProperty_, nullptr);
    EXPECT_NE(layoutWrapper->geometryNode_, nullptr);
}

/**
 * @tc.name: SideBarLayoutTestNg018
 * @tc.desc: Test SideBar MeasureSideBarContent
 * @tc.type: FUNC
 */
HWTEST_F(SideBarLayoutTestNg, SideBarLayoutTestNg018, TestSize.Level1)
{
    SideBarContainerModelNG SideBarContainerModelInstance;
    auto sideBarFrameNode =
        FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 0, AceType::MakeRefPtr<SideBarContainerPattern>());
    EXPECT_FALSE(sideBarFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
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
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->minPlatformVersion_ = TEST_VALUE;
    sideBarPattern->sideBarStatus_ = SideBarStatus::SHOW;
    layoutAlgorithm->type_ = SideBarContainerType::AUTO;
    layoutAlgorithm->MeasureSideBarContent(sideBarLayoutProperty, layoutWrapper, parentWidth);
    EXPECT_NE(layoutWrapper->layoutProperty_, nullptr);
    EXPECT_NE(layoutWrapper->geometryNode_, nullptr);
}

/**
 * @tc.name: SideBarLayoutTestNg019
 * @tc.desc: Test SideBar InitSideBarWidth(parentWidth);
 * @tc.type: FUNC
 */
HWTEST_F(SideBarLayoutTestNg, SideBarLayoutTestNg019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SideBar and frameNode.
     */
    auto layoutAlgorithm = AceType::MakeRefPtr<SideBarContainerLayoutAlgorithm>();
    EXPECT_NE(layoutAlgorithm, nullptr);
    auto parentWidth = MAX_PARENT_WIDTH;
    layoutAlgorithm->defaultRealSideBarWidth_ = DEFAULT_REAL_SIDEBAR;
    layoutAlgorithm->defaultMinSideBarWidth_ = DEFAULT_MIN_SIDEBAR;
    layoutAlgorithm->defaultMaxSideBarWidth_ = DEFAULT_MAX_SIDEBAR;
    layoutAlgorithm->defaultMinContentWidth_ = DEFAULT_MIN_CONTENT;
    layoutAlgorithm->InitSideBarWidth(parentWidth);
    layoutAlgorithm->MeasureRealSideBarWidth(parentWidth);
    EXPECT_EQ(layoutAlgorithm->minSideBarWidth_, DEFAULT_MIN_SIDEBAR);

    /**
     * @tc.steps: step2. realSideBarWidth_ < maxSideBarWidth_
     * @tc.expected:realSideBarWidth_ == maxSideBarWidth_
     */
    parentWidth = DEFAULT_MAX_SIDEBAR;
    layoutAlgorithm->realSideBarWidth_ = DEFAULT_REAL_SIDEBAR;
    layoutAlgorithm->minSideBarWidth_ = DEFAULT_MIN_SIDEBAR;
    layoutAlgorithm->maxSideBarWidth_ = DEFAULT_MAX_SIDEBAR;
    layoutAlgorithm->InitSideBarWidth(parentWidth);
    layoutAlgorithm->MeasureRealSideBarWidth(parentWidth);
    EXPECT_EQ(layoutAlgorithm->maxSideBarWidth_, DEFAULT_MAX_SIDEBAR);

    parentWidth = MAX_PARENT_WIDTH;
    layoutAlgorithm->realSideBarWidth_ = DEFAULT_REAL_SIDEBAR;
    layoutAlgorithm->minSideBarWidth_ = DEFAULT_MIN_SIDEBAR;
    layoutAlgorithm->maxSideBarWidth_ = DEFAULT_MAX_SIDEBAR;
    layoutAlgorithm->InitSideBarWidth(parentWidth);
    layoutAlgorithm->MeasureRealSideBarWidth(parentWidth);
    EXPECT_EQ(layoutAlgorithm->maxSideBarWidth_, DEFAULT_MAX_SIDEBAR);
}

/**
 * @tc.name: SideBarLayoutTestNg020
 * @tc.desc: Test SideBar LayoutSideBar
 * @tc.type: FUNC
 */
HWTEST_F(SideBarLayoutTestNg, SideBarLayoutTestNg020, TestSize.Level1)
{
    SideBarContainerModelNG SideBarContainerModelInstance;
    auto sideBarFrameNode =
        FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 0, AceType::MakeRefPtr<SideBarContainerPattern>());
    EXPECT_FALSE(sideBarFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> sideBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
    EXPECT_FALSE(sideBarLayoutWrapper == nullptr);
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    SizeF size(SIDE_BAR_SIZE, 0.0);
    sideBarLayoutWrapper->GetGeometryNode()->SetFrameSize(size);
    EXPECT_FALSE(sideBarPattern == nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<SideBarContainerLayoutAlgorithm>();
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    layoutAlgorithm->sideBarStatus_ = SideBarStatus::AUTO;
    SideBarContainerModelInstance.SetSideBarContainerType(SideBarContainerType::EMBED);
    layoutAlgorithm->LayoutSideBar(AccessibilityManager::RawPtr(sideBarLayoutWrapper), sideBarLayoutWrapper);
    EXPECT_EQ(layoutAlgorithm->sideBarOffset_.GetX(), 0);
}

/**
 * @tc.name: SideBarLayoutTestNg021
 * @tc.desc: Test SideBar AdjustMinAndMaxSideBarWidth
 * @tc.type: FUNC
 */
HWTEST_F(SideBarLayoutTestNg, SideBarLayoutTestNg021, TestSize.Level1)
{
    auto sideBarFrameNode =
        FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 0, AceType::MakeRefPtr<SideBarContainerPattern>());
    EXPECT_FALSE(sideBarFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    auto layoutWrapper = LayoutWrapperNode(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    EXPECT_FALSE(sideBarPattern == nullptr);
    auto sideBarLayoutProperty = sideBarPattern->GetLayoutProperty<SideBarContainerLayoutProperty>();
    EXPECT_FALSE(sideBarLayoutProperty == nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<SideBarContainerLayoutAlgorithm>();
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    auto tempFrame =
        FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 0, AceType::MakeRefPtr<SideBarContainerPattern>());
    EXPECT_FALSE(tempFrame == nullptr);
    auto tempLayoutWrapper = tempFrame->CreateLayoutWrapper();
    EXPECT_FALSE(tempLayoutWrapper == nullptr);
    layoutWrapper.cachedList_ = std::list<RefPtr<LayoutWrapper>>();
    layoutWrapper.cachedList_.push_back(tempLayoutWrapper);
    layoutWrapper.cachedList_.push_back(tempLayoutWrapper);
    layoutWrapper.cachedList_.push_back(tempLayoutWrapper);
    layoutWrapper.cachedList_.push_back(tempLayoutWrapper);
    layoutAlgorithm->GetSideBarLayoutWrapper(&layoutWrapper);
    layoutAlgorithm->UpdateDefaultValueByVersion();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->minPlatformVersion_ = 7;
    sideBarLayoutProperty->UpdateMinSideBarWidth(DEFAULT_MIN_SIDE_BAR_WIDTH);
    sideBarLayoutProperty->UpdateMaxSideBarWidth(DEFAULT_MAX_SIDE_BAR_WIDTH);
    layoutAlgorithm->AdjustMinAndMaxSideBarWidth(&layoutWrapper);
    EXPECT_EQ(layoutAlgorithm->minSideBarWidth_, layoutAlgorithm->maxSideBarWidth_);
}

/**
 * @tc.name: SideBarLayoutTestNg022
 * @tc.desc: Test SideBar GetAllPropertyValue
 * @tc.type: FUNC
 */
HWTEST_F(SideBarLayoutTestNg, SideBarLayoutTestNg022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SideBar and frameNode.
     */
    auto sideBarFrameNode =
        FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 0, AceType::MakeRefPtr<SideBarContainerPattern>());
    EXPECT_FALSE(sideBarFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
    EXPECT_FALSE(layoutWrapper == nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<SideBarContainerLayoutAlgorithm>();
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    auto layoutProperty = AceType::DynamicCast<SideBarContainerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    auto sideBarContainerPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(sideBarContainerPattern, nullptr);
    auto parentWidth = MAX_PARENT_WIDTH;
    layoutAlgorithm->defaultRealSideBarWidth_ = DEFAULT_REAL_SIDEBAR;
    layoutAlgorithm->defaultMinSideBarWidth_ = DEFAULT_MIN_SIDEBAR;
    layoutAlgorithm->defaultMaxSideBarWidth_ = DEFAULT_MAX_SIDEBAR;
    layoutAlgorithm->SetPattern(AceType::WeakClaim(AceType::RawPtr(sideBarContainerPattern)));
    layoutAlgorithm->preSideBarWidth_ = Dimension(1.0f, DimensionUnit::PX);
    layoutAlgorithm->GetAllPropertyValue(layoutProperty, parentWidth);
}

/**
 * @tc.name: SideBarLayoutTestNg0023
 * @tc.desc: Test SideBar Measure
 * @tc.type: FUNC
 */
HWTEST_F(SideBarLayoutTestNg, SideBarLayoutTestNg0023, TestSize.Level1)
{
    auto sideBarFrameNode =
        FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 0, AceType::MakeRefPtr<SideBarContainerPattern>());
    EXPECT_FALSE(sideBarFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    auto layoutWrapper = LayoutWrapperNode(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
    auto layoutWrapper1 =
        AceType::MakeRefPtr<LayoutWrapperNode>(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
    auto layoutWrapper2 =
        AceType::MakeRefPtr<LayoutWrapperNode>(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
    auto layoutWrapper3 =
        AceType::MakeRefPtr<LayoutWrapperNode>(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    EXPECT_FALSE(sideBarPattern == nullptr);
    auto sideBarLayoutProperty = sideBarPattern->GetLayoutProperty<SideBarContainerLayoutProperty>();
    EXPECT_FALSE(sideBarLayoutProperty == nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<SideBarContainerLayoutAlgorithm>();
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    auto tempFrame =
        FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 0, AceType::MakeRefPtr<SideBarContainerPattern>());
    EXPECT_FALSE(tempFrame == nullptr);
    auto tempLayoutWrapper = tempFrame->CreateLayoutWrapper();
    EXPECT_FALSE(tempLayoutWrapper == nullptr);
    layoutWrapper.cachedList_.emplace_back(layoutWrapper1);
    layoutWrapper.cachedList_.emplace_back(layoutWrapper2);
    layoutWrapper.cachedList_.emplace_back(layoutWrapper3);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.percentReference = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    auto layoutProperty = AceType::DynamicCast<SideBarContainerLayoutProperty>(layoutWrapper.GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->contentConstraint_ = layoutProperty->CreateContentConstraint();
    layoutAlgorithm->Measure(&layoutWrapper);
    auto sideBarContainerPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(sideBarContainerPattern, nullptr);
    auto parentWidth = MAX_PARENT_WIDTH;
    layoutAlgorithm->defaultRealSideBarWidth_ = DEFAULT_REAL_SIDEBAR;
    layoutAlgorithm->defaultMinSideBarWidth_ = DEFAULT_MIN_SIDEBAR;
    layoutAlgorithm->defaultMaxSideBarWidth_ = DEFAULT_MAX_SIDEBAR;
    layoutAlgorithm->SetPattern(AceType::WeakClaim(AceType::RawPtr(sideBarContainerPattern)));
    layoutAlgorithm->preSideBarWidth_ = DEFAULT_MIN;
    layoutAlgorithm->GetAllPropertyValue(layoutProperty, parentWidth);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->minPlatformVersion_ = 12;
    layoutAlgorithm->Measure(&layoutWrapper);
    layoutAlgorithm->type_ = SideBarContainerType::OVERLAY;
    layoutAlgorithm->realSideBarWidthDimension_ = Dimension(5.0f, DimensionUnit::PERCENT);
    layoutAlgorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: SideBarLayoutTestNg0024
 * @tc.desc: Test SideBar LayoutDivider
 * @tc.type: FUNC
 */
HWTEST_F(SideBarLayoutTestNg, SideBarLayoutTestNg0024, TestSize.Level1)
{
    SideBarContainerModelNG SideBarContainerModelInstance;
    auto sideBarFrameNode =
        FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 0, AceType::MakeRefPtr<SideBarContainerPattern>());
    EXPECT_FALSE(sideBarFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> sideBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
    EXPECT_FALSE(sideBarLayoutWrapper == nullptr);
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    SizeF size(SIDE_BAR_SIZE, 0.0);
    sideBarLayoutWrapper->GetGeometryNode()->SetFrameSize(size);
    EXPECT_FALSE(sideBarPattern == nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<SideBarContainerLayoutAlgorithm>();
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    layoutAlgorithm->sideBarStatus_ = SideBarStatus::AUTO;
    auto layoutProperty =
        AceType::DynamicCast<SideBarContainerLayoutProperty>(sideBarLayoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    auto layoutConstraint = LayoutConstraintF();
    layoutConstraint.selfIdealSize.SetWidth(20);
    layoutConstraint.selfIdealSize.SetHeight(20);
    layoutProperty->layoutConstraint_ = layoutConstraint;
    SideBarContainerModelInstance.SetSideBarContainerType(SideBarContainerType::EMBED);
    layoutAlgorithm->LayoutDivider(AccessibilityManager::RawPtr(sideBarLayoutWrapper), sideBarLayoutWrapper);
}

/**
 * @tc.name: SideBarLayoutTestNg025
 * @tc.desc: Test SideBar AdjustMinAndMaxSideBarWidth
 * @tc.type: FUNC
 */
HWTEST_F(SideBarLayoutTestNg, SideBarLayoutTestNg025, TestSize.Level1)
{
    auto sideBarFrameNode =
        FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 0, AceType::MakeRefPtr<SideBarContainerPattern>());
    EXPECT_FALSE(sideBarFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    auto layoutWrapper = LayoutWrapperNode(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    EXPECT_FALSE(sideBarPattern == nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<SideBarContainerLayoutAlgorithm>();
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    auto tempFrame =
        FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 0, AceType::MakeRefPtr<SideBarContainerPattern>());
    EXPECT_FALSE(tempFrame == nullptr);
    auto tempLayoutWrapper = tempFrame->CreateLayoutWrapper();
    EXPECT_FALSE(tempLayoutWrapper == nullptr);
    layoutWrapper.cachedList_ = std::list<RefPtr<LayoutWrapper>>();
    layoutWrapper.cachedList_.push_back(tempLayoutWrapper);
    layoutWrapper.cachedList_.push_back(tempLayoutWrapper);
    layoutWrapper.cachedList_.push_back(tempLayoutWrapper);
    layoutWrapper.cachedList_.push_back(tempLayoutWrapper);
    layoutAlgorithm->GetSideBarLayoutWrapper(&layoutWrapper);
    layoutAlgorithm->UpdateDefaultValueByVersion();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->minPlatformVersion_ = 12;
    auto sideBarLayoutWrapper = layoutAlgorithm->GetSideBarLayoutWrapper(&layoutWrapper);
    ASSERT_NE(sideBarLayoutWrapper, nullptr);
    auto sideBarLayoutProperty = sideBarLayoutWrapper->GetLayoutProperty();
    EXPECT_FALSE(sideBarLayoutProperty == nullptr);
    sideBarLayoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    sideBarLayoutProperty->calcLayoutConstraint_->maxSize =
        CalcSize(CalcLength(SIDE_BAR_SIZE), CalcLength(SIZEF_WIDTH));
    sideBarLayoutProperty->calcLayoutConstraint_->minSize =
        CalcSize(CalcLength(SIDE_BAR_SIZE), CalcLength(SIZEF_WIDTH));
    sideBarLayoutProperty->calcLayoutConstraint_->minSize->width_ = CalcLength(SIDE_BAR_SIZE);
    layoutAlgorithm->AdjustMinAndMaxSideBarWidth(&layoutWrapper);
    EXPECT_EQ(layoutAlgorithm->minSideBarWidth_, layoutAlgorithm->maxSideBarWidth_);
}

/**
 * @tc.name: SideBarLayoutTestNg026
 * @tc.desc: Test SideBar LayoutControlButton
 * @tc.type: FUNC
 */
HWTEST_F(SideBarLayoutTestNg, SideBarLayoutTestNg026, TestSize.Level1)
{
    auto sideBarFrameNode =
        FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 0, AceType::MakeRefPtr<SideBarContainerPattern>());
    EXPECT_FALSE(sideBarFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    auto layoutWrapper = LayoutWrapperNode(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    EXPECT_FALSE(sideBarPattern == nullptr);
    auto sideBarLayoutProperty = sideBarPattern->GetLayoutProperty<SideBarContainerLayoutProperty>();
    EXPECT_FALSE(sideBarLayoutProperty == nullptr);
    SizeF value(SIZEF_WIDTH, SIZEF_HEIGHT);
    sideBarLayoutProperty->UpdateMarginSelfIdealSize(value);
    sideBarLayoutProperty->UpdateContentConstraint();
    auto layoutAlgorithm = AceType::MakeRefPtr<SideBarContainerLayoutAlgorithm>();
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->minPlatformVersion_ = TEST_VALUE;
    auto buttonLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
    auto layoutProperty = AceType::DynamicCast<SideBarContainerLayoutProperty>(layoutWrapper.GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateControlButtonLeft(Dimension(-1.0f));
    layoutProperty->UpdateControlButtonTop(Dimension(-1.0f));
    layoutAlgorithm->LayoutControlButton(&layoutWrapper, buttonLayoutWrapper);
    ASSERT_TRUE(
        LessNotEqual(layoutProperty->GetControlButtonLeft().value_or(DEFAULT_CONTROL_BUTTON_LEFT).Value(), 0.0));
}

/**
 * @tc.name: SideBarLayoutTestNg027
 * @tc.desc: Test SideBar container ClipPadding
 * @tc.type: FUNC
 */
HWTEST_F(SideBarLayoutTestNg, SideBarLayoutTestNg027, TestSize.Level1)
{
    SideBarContainerPaintMethod SideBarContainerPaintMethodInstance;
    auto frameNode =
        FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 0, AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto indicatorNode =
        FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 0, AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    Testing::MockCanvas canvas;
    SideBarContainerPaintMethodInstance.ClipPadding(&paintWrapper, canvas);
    EXPECT_EQ(SideBarContainerPaintMethodInstance.needClipPadding_, false);
    SideBarContainerPaintMethodInstance.needClipPadding_ = true;
    SideBarContainerPaintMethodInstance.ClipPadding(&paintWrapper, canvas);
    EXPECT_EQ(SideBarContainerPaintMethodInstance.needClipPadding_, true);
    paintWrapper.renderContext_ = nullptr;
    SideBarContainerPaintMethodInstance.ClipPadding(&paintWrapper, canvas);
    EXPECT_EQ(SideBarContainerPaintMethodInstance.needClipPadding_, true);
    paintWrapper.renderContext_ = renderContext;
    renderContext->UpdateClipEdge(false);
    SideBarContainerPaintMethodInstance.ClipPadding(&paintWrapper, canvas);
    EXPECT_EQ(SideBarContainerPaintMethodInstance.needClipPadding_, true);
}

/**
 * @tc.name: SideBarLayoutTestNg028
 * @tc.desc: Test SideBar LayoutSideBarContent
 * @tc.type: FUNC
 */
HWTEST_F(SideBarLayoutTestNg, SideBarLayoutTestNg028, TestSize.Level1)
{
    SideBarContainerModelNG SideBarContainerModelInstance;
    auto sideBarFrameNode =
        FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 0, AceType::MakeRefPtr<SideBarContainerPattern>());
    EXPECT_FALSE(sideBarFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> sideBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
    EXPECT_FALSE(sideBarLayoutWrapper == nullptr);
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    EXPECT_FALSE(sideBarPattern == nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<SideBarContainerLayoutAlgorithm>();
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    sideBarPattern->sideBarStatus_ = SideBarStatus::SHOW;
    SideBarContainerModelInstance.SetSideBarContainerType(SideBarContainerType::OVERLAY);
    layoutAlgorithm->type_ = SideBarContainerType::AUTO;
    layoutAlgorithm->LayoutSideBarContent(AccessibilityManager::RawPtr(sideBarLayoutWrapper), sideBarLayoutWrapper);
    EXPECT_NE(layoutAlgorithm->realSideBarWidth_, 0);
}

/**
 * @tc.name: SideBarLayoutTestNg029
 * @tc.desc: Test SideBar AdjustMinAndMaxSideBarWidth
 * @tc.type: FUNC
 */
HWTEST_F(SideBarLayoutTestNg, SideBarLayoutTestNg029, TestSize.Level1)
{
    auto sideBarFrameNode =
        FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 0, AceType::MakeRefPtr<SideBarContainerPattern>());
    EXPECT_FALSE(sideBarFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    auto layoutWrapper = LayoutWrapperNode(sideBarFrameNode, geometryNode, sideBarFrameNode->GetLayoutProperty());
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    EXPECT_FALSE(sideBarPattern == nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<SideBarContainerLayoutAlgorithm>();
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    auto tempFrame =
        FrameNode::CreateFrameNode(V2::SIDE_BAR_ETS_TAG, 0, AceType::MakeRefPtr<SideBarContainerPattern>());
    EXPECT_FALSE(tempFrame == nullptr);
    auto tempLayoutWrapper = tempFrame->CreateLayoutWrapper();
    EXPECT_FALSE(tempLayoutWrapper == nullptr);
    layoutWrapper.cachedList_ = std::list<RefPtr<LayoutWrapper>>();
    layoutWrapper.cachedList_.push_back(tempLayoutWrapper);
    layoutWrapper.cachedList_.push_back(tempLayoutWrapper);
    layoutWrapper.cachedList_.push_back(tempLayoutWrapper);
    layoutWrapper.cachedList_.push_back(tempLayoutWrapper);
    layoutAlgorithm->GetSideBarLayoutWrapper(&layoutWrapper);
    layoutAlgorithm->UpdateDefaultValueByVersion();
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->minPlatformVersion_ = 12;
    auto sideBarLayoutWrapper = layoutAlgorithm->GetSideBarLayoutWrapper(&layoutWrapper);
    ASSERT_NE(sideBarLayoutWrapper, nullptr);
    auto sideBarLayoutProperty = sideBarLayoutWrapper->GetLayoutProperty();
    EXPECT_FALSE(sideBarLayoutProperty == nullptr);
    sideBarLayoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutAlgorithm->AdjustMinAndMaxSideBarWidth(&layoutWrapper);
    EXPECT_EQ(layoutAlgorithm->minSideBarWidth_, layoutAlgorithm->maxSideBarWidth_);
}
} // namespace OHOS::Ace::NG
