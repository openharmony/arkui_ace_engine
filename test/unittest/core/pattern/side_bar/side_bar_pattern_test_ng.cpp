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
#include "base/memory/ref_counter.h"
#include "base/memory/referenced.h"
#include "core/animation/animator.h"
#include "core/animation/curve_animation.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/progress/progress_paint_property.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_paint_method.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_layout_property.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_model_ng.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_pattern.h"
#include "core/components_ng/pattern/side_bar/side_bar_theme.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_v2/extensions/extension.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "core/components_ng/property/measure_utils.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr SideBarContainerType SIDE_BAR_CONTAINER_TYPE = SideBarContainerType::EMBED;
constexpr bool IS_SHOW = true;
constexpr bool SHOW_CONTROL_BUTTON = true;
constexpr Dimension SIDE_BAR_WIDTH = 50.0_vp;
constexpr Dimension MIN_SIDE_BAR_WIDTH = 50.0_vp;
constexpr Dimension MAX_SIDE_BAR_WIDTH = 50.0_vp;
constexpr Dimension MIN_CONTENT_WIDTH = 50.0_vp;
constexpr Dimension DEFAULT_MIN_SIDE_BAR_WIDTH = 200.0_vp;
constexpr Dimension DEFAULT_MAX_SIDE_BAR_WIDTH = 280.0_vp;
constexpr bool AUTO_HIDE = true;
constexpr SideBarPosition SIDE_BAR_POSITION = SideBarPosition::START;
constexpr Dimension WIDTH = 150.0_vp;
constexpr Dimension HEIGHT = 150.0_vp;
constexpr Dimension LEFT = 50.0_vp;
constexpr Dimension TOP = 50.0_vp;
constexpr float UPDATE_SIDE_BAR_POSITION_VALUE = 1.0f;
constexpr Dimension REAL_SIDE_BAR_WIDTH_VALUE = 1.0_px;
constexpr float CURRENT_OFFSET_VALUE = 1.0f;
constexpr float UPDATE_SIDE_BAR_WIDTH = 240.0f;
const std::string SHOW_ICON_STR = "123";
const std::string HIDDEN_ICON_STR = "123";
const std::string SWITCHING_ICON_STR = "123";
constexpr Dimension IMAGE_WIDTH = 10.0_vp;
constexpr Dimension IMAGE_HEIGHT = 10.0_vp;
constexpr Dimension DEFAULT_IMAGE_WIDTH_V10 = 24.0_vp;
constexpr Dimension DEFAULT_IMAGE_HEIGHT_V10 = 24.0_vp;
constexpr static int32_t TEST_VALUE = 12;
constexpr float MAX_SIDE_BAR = 20.0f;
constexpr float MIN_SIDE_BAR = -10.0f;
constexpr Dimension DIVIDER_STROKE_WIDTH = 5.0_vp;
constexpr Dimension DIVIDER_START_MARGIN = 2.0_vp;
constexpr Dimension DIVIDER_END_MARGIN = 3.0_vp;
constexpr static int32_t DEFAULT_CONTROL_BUTTON_ZINDEX = 3;
constexpr static int32_t DEFAULT_SIDE_BAR_ZINDEX_EMBED = 0;
constexpr static int32_t DEFAULT_DIVIDER_ZINDEX_EMBED = 1;
constexpr static int32_t DEFAULT_CONTENT_ZINDEX_EMBED = 2;
constexpr static int32_t DEFAULT_SIDE_BAR_ZINDEX_OVERLAY = 2;
constexpr static int32_t DEFAULT_DIVIDER_ZINDEX_OVERLAY = 1;
constexpr static int32_t DEFAULT_CONTENT_ZINDEX_OVERLAY = 0;
} // namespace

class SideBarPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void SideBarPatternTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void SideBarPatternTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: SideBarPatternTestNg001
 * @tc.desc: Test SideBar Create
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar and get frameNode.
     */
    SideBarContainerModelNG SideBarContainerModelInstance;
    SideBarContainerModelInstance.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
}

/**
 * @tc.name: SideBarPatternTestNg002
 * @tc.desc: Test SideBar Set Func
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar and set the properties ,and then get frameNode.
     */
    SideBarContainerModelNG SideBarContainerModelInstance;
    SideBarContainerModelInstance.Create();
    SideBarContainerModelInstance.SetSideBarContainerType(SIDE_BAR_CONTAINER_TYPE);
    SideBarContainerModelInstance.SetShowSideBar(IS_SHOW);
    SideBarContainerModelInstance.SetShowControlButton(SHOW_CONTROL_BUTTON);
    SideBarContainerModelInstance.SetSideBarWidth(SIDE_BAR_WIDTH);
    SideBarContainerModelInstance.SetMinSideBarWidth(MIN_SIDE_BAR_WIDTH);
    SideBarContainerModelInstance.SetMaxSideBarWidth(MAX_SIDE_BAR_WIDTH);
    SideBarContainerModelInstance.SetMinContentWidth(MIN_CONTENT_WIDTH);
    SideBarContainerModelInstance.SetAutoHide(AUTO_HIDE);
    SideBarContainerModelInstance.SetSideBarPosition(SIDE_BAR_POSITION);
    SideBarContainerModelInstance.SetControlButtonWidth(WIDTH);
    SideBarContainerModelInstance.SetControlButtonHeight(HEIGHT);
    SideBarContainerModelInstance.SetControlButtonLeft(LEFT);
    SideBarContainerModelInstance.SetControlButtonTop(TOP);
    SideBarContainerModelInstance.SetControlButtonShowIconInfo(SHOW_ICON_STR, false, nullptr);
    SideBarContainerModelInstance.SetControlButtonHiddenIconInfo(HIDDEN_ICON_STR, false, nullptr);
    SideBarContainerModelInstance.SetControlButtonSwitchingIconInfo(SWITCHING_ICON_STR, false, nullptr);
    ChangeEvent eventOnChange = [](const bool) {};
    SideBarContainerModelInstance.SetOnChange(std::move(eventOnChange));
    SideBarContainerModelInstance.MarkNeedInitRealSideBarWidth();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get the properties of all settings.
     * @tc.expected: step2. check whether the properties is correct.
     */
    auto sideBarLayoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    EXPECT_NE(sideBarLayoutProperty, nullptr);
    EXPECT_EQ(sideBarLayoutProperty->GetSideBarContainerType(), SIDE_BAR_CONTAINER_TYPE);
    EXPECT_EQ(sideBarLayoutProperty->GetShowSideBar(), IS_SHOW);
    EXPECT_EQ(sideBarLayoutProperty->GetShowControlButton(), SHOW_CONTROL_BUTTON);
    EXPECT_EQ(sideBarLayoutProperty->GetSideBarWidth(), SIDE_BAR_WIDTH);
    EXPECT_EQ(sideBarLayoutProperty->GetMinSideBarWidth(), MIN_SIDE_BAR_WIDTH);
    EXPECT_EQ(sideBarLayoutProperty->GetMaxSideBarWidth(), MAX_SIDE_BAR_WIDTH);
    EXPECT_EQ(sideBarLayoutProperty->GetMinContentWidth(), MIN_CONTENT_WIDTH);
    EXPECT_EQ(sideBarLayoutProperty->GetAutoHide(), AUTO_HIDE);
    EXPECT_EQ(sideBarLayoutProperty->GetSideBarPosition(), SIDE_BAR_POSITION);
    EXPECT_EQ(sideBarLayoutProperty->GetControlButtonWidth(), WIDTH);
    EXPECT_EQ(sideBarLayoutProperty->GetControlButtonHeight(), HEIGHT);
    EXPECT_EQ(sideBarLayoutProperty->GetControlButtonLeft(), LEFT);
    EXPECT_EQ(sideBarLayoutProperty->GetControlButtonTop(), TOP);
    EXPECT_EQ(sideBarLayoutProperty->GetControlButtonShowIconInfo()->GetSrc(), SHOW_ICON_STR);
    EXPECT_EQ(sideBarLayoutProperty->GetControlButtonHiddenIconInfo()->GetSrc(), HIDDEN_ICON_STR);
    EXPECT_EQ(sideBarLayoutProperty->GetControlButtonSwitchingIconInfo()->GetSrc(), SWITCHING_ICON_STR);
}

/**
 * @tc.name: SideBarPatternTestNg003
 * @tc.desc: Test SideBar OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg003, TestSize.Level1)
{
    SideBarContainerModelNG SideBarContainerModelInstance;
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->OnModifyDone();
    SideBarContainerModelInstance.SetShowSideBar(true);
    EXPECT_EQ(pattern->sideBarStatus_, SideBarStatus::SHOW);
    EXPECT_NE(pattern->dragEvent_, nullptr);
}

/**
 * @tc.name: SideBarPatternTestNg004
 * @tc.desc: Test SideBar CreateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg004, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->CreateAnimation();
    EXPECT_NE(pattern->controller_, nullptr);
    EXPECT_NE(pattern->rightToLeftAnimation_, nullptr);
    EXPECT_NE(pattern->leftToRightAnimation_, nullptr);
}

/**
 * @tc.name: SideBarPatternTestNg005
 * @tc.desc: Test SideBar CreateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg005, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->CreateAnimation();
    EXPECT_NE(pattern->controller_, nullptr);
    EXPECT_NE(pattern->rightToLeftAnimation_, nullptr);
    EXPECT_NE(pattern->leftToRightAnimation_, nullptr);
    pattern->CreateAnimation();
    EXPECT_NE(pattern->controller_, nullptr);
    EXPECT_NE(pattern->rightToLeftAnimation_, nullptr);
    EXPECT_NE(pattern->leftToRightAnimation_, nullptr);
}

/**
 * @tc.name: SideBarPatternTestNg007
 * @tc.desc: Test SideBar UpdateSideBarPosition
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg007, TestSize.Level1)
{
    float value = 0.0f;
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->sideBarStatus_ = SideBarStatus::SHOW;
    pattern->UpdateSideBarPosition(value);
    EXPECT_EQ(pattern->sideBarStatus_, SideBarStatus::CHANGING);
    EXPECT_EQ(pattern->currentOffset_, 0);
}

/**
 * @tc.name: SideBarPatternTestNg008
 * @tc.desc: Test SideBar UpdateSideBarPosition
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg008, TestSize.Level1)
{
    float value = UPDATE_SIDE_BAR_POSITION_VALUE;
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->sideBarStatus_ = SideBarStatus::SHOW;
    pattern->realSideBarWidth_ = REAL_SIDE_BAR_WIDTH_VALUE;
    pattern->UpdateSideBarPosition(value);
    EXPECT_EQ(pattern->sideBarStatus_, SideBarStatus::CHANGING);
    EXPECT_EQ(pattern->currentOffset_, CURRENT_OFFSET_VALUE);
}

/**
 * @tc.name: SideBarPatternTestNg009
 * @tc.desc: Test SideBar UpdateSideBarPosition
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg009, TestSize.Level1)
{
    float value = UPDATE_SIDE_BAR_POSITION_VALUE;
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->sideBarStatus_ = SideBarStatus::HIDDEN;
    pattern->realSideBarWidth_ = REAL_SIDE_BAR_WIDTH_VALUE;
    pattern->UpdateSideBarPosition(value);
    EXPECT_EQ(pattern->sideBarStatus_, SideBarStatus::CHANGING);
    EXPECT_EQ(pattern->currentOffset_, CURRENT_OFFSET_VALUE);
}
/**
 * @tc.name: SideBarPatternTestNg010
 * @tc.desc: Test SideBar UpdateSideBarPosition
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg010, TestSize.Level1)
{
    float value = UPDATE_SIDE_BAR_POSITION_VALUE;
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    EXPECT_FALSE(pattern == nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->sideBarStatus_ = SideBarStatus::AUTO;
    pattern->realSideBarWidth_ = REAL_SIDE_BAR_WIDTH_VALUE;
    pattern->UpdateSideBarPosition(value);
    EXPECT_EQ(pattern->sideBarStatus_, SideBarStatus::CHANGING);
    EXPECT_EQ(pattern->currentOffset_, CURRENT_OFFSET_VALUE);
}

/**
 * @tc.name: SideBarPatternTestNg011
 * @tc.desc: Test SideBar UpdateControlButtonIcon
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBarContainer,controlButton node,then mount controlButton node to its parent
     * frameNode.
     * @tc.expected: check whether the sideBarContainer node's children is not empty.
     */
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    auto themeManagerOne = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerOne);
    EXPECT_CALL(*themeManagerOne, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SideBarTheme>()));
    EXPECT_CALL(*themeManagerOne, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SideBarTheme>()));

    pattern->CreateAndMountControlButton(frameNode);

    auto children = frameNode->GetChildren();
    ASSERT_FALSE(children.empty());

    /**
     * @tc.steps: step2. get the default color of controlButton from sidebar theme, then execute UpdateControlButtonIcon
     * method.
     * @tc.expected: check whether the controlButton's fillColor is same as the default color.
     */
    auto sideBarTheme = AceType::MakeRefPtr<SideBarTheme>();
    ASSERT_NE(sideBarTheme, nullptr);
    Color controlButtonColor = sideBarTheme->GetControlImageColor();
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(children.front());
    ASSERT_NE(buttonFrameNode, nullptr);
    auto buttonChildren = buttonFrameNode->GetChildren();
    ASSERT_FALSE(buttonChildren.empty());
    auto imgFrameNode = AceType::DynamicCast<FrameNode>(buttonChildren.front());
    ASSERT_NE(imgFrameNode, nullptr);
    auto imageLayoutProperty = imgFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);

    pattern->sideBarStatus_ = SideBarStatus::SHOW;
    pattern->UpdateControlButtonIcon();
    auto imgSourceInfo = imageLayoutProperty->GetImageSourceInfoValue();
    EXPECT_EQ(imgSourceInfo.GetFillColor()->GetValue(), controlButtonColor.GetValue());

    pattern->sideBarStatus_ = SideBarStatus::HIDDEN;
    pattern->UpdateControlButtonIcon();
    imgSourceInfo = imageLayoutProperty->GetImageSourceInfoValue();
    EXPECT_EQ(imgSourceInfo.GetFillColor()->GetValue(), controlButtonColor.GetValue());

    pattern->sideBarStatus_ = SideBarStatus::CHANGING;
    pattern->UpdateControlButtonIcon();
    imgSourceInfo = imageLayoutProperty->GetImageSourceInfoValue();
    EXPECT_EQ(imgSourceInfo.GetFillColor()->GetValue(), controlButtonColor.GetValue());
}

/**
 * @tc.name: SideBarPatternTestNg012
 * @tc.desc: Test SideBar InitControlButtonTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg012, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    pattern->AttachToFrameNode(frameNode);
    int32_t imgNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto imgNode = FrameNode::GetOrCreateFrameNode(
        OHOS::Ace::V2::IMAGE_ETS_TAG, imgNodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    EXPECT_FALSE(imgNode == nullptr);
    auto imgHub = imgNode->GetEventHub<EventHub>();
    EXPECT_FALSE(imgHub == nullptr);
    auto gestureHub = imgHub->GetOrCreateGestureEventHub();
    EXPECT_FALSE(gestureHub == nullptr);
    pattern->SetHasControlButton(true);
    EXPECT_EQ(pattern->controlButtonClickEvent_, nullptr);
    pattern->InitControlButtonTouchEvent(gestureHub);
    EXPECT_NE(pattern->controlButtonClickEvent_, nullptr);
}

/**
 * @tc.name: SideBarPatternTestNg013
 * @tc.desc: Test SideBar DoAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg013, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->DoAnimation();
    EXPECT_EQ(pattern->animDir_, SideBarAnimationDirection::RTL);
    EXPECT_EQ(pattern->sideBarStatus_, SideBarStatus::CHANGING);
    pattern->animDir_ = SideBarAnimationDirection::LTR;
    EXPECT_EQ(pattern->currentOffset_, 0.0f);
}

/**
 * @tc.name: SideBarPatternTestNg014
 * @tc.desc: Test SideBar DoAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg014, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->DoAnimation();
    EXPECT_EQ(pattern->animDir_, SideBarAnimationDirection::RTL);
    EXPECT_EQ(pattern->sideBarStatus_, SideBarStatus::CHANGING);
    pattern->animDir_ = SideBarAnimationDirection::RTL;
    EXPECT_EQ(pattern->currentOffset_, 0.0f);
}

/**
 * @tc.name: SideBarPatternTestNg015
 * @tc.desc: Test SideBar DoAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg015, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->DoAnimation();
    EXPECT_EQ(pattern->animDir_, SideBarAnimationDirection::RTL);
    EXPECT_EQ(pattern->sideBarStatus_, SideBarStatus::CHANGING);
    pattern->realSideBarWidth_ = REAL_SIDE_BAR_WIDTH_VALUE;
    pattern->animDir_ = SideBarAnimationDirection::RTL;
    EXPECT_EQ(pattern->currentOffset_, 0.0f);
}

/**
 * @tc.name: SideBarPatternTestNg016
 * @tc.desc: Test SideBar UpdateAnimDir
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg016, TestSize.Level1)
{
    SideBarContainerModelNG SideBarContainerModelInstance;
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    pattern->AttachToFrameNode(frameNode);
    stack->Push(frameNode);
    pattern->sideBarStatus_ = SideBarStatus::SHOW;
    SideBarContainerModelInstance.SetSideBarPosition(SideBarPosition::START);
    pattern->UpdateAnimDir();
    EXPECT_EQ(pattern->animDir_, SideBarAnimationDirection::RTL);
}

/**
 * @tc.name: SideBarPatternTestNg017
 * @tc.desc: Test SideBar UpdateAnimDir
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg017, TestSize.Level1)
{
    SideBarContainerModelNG SideBarContainerModelInstance;
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    pattern->AttachToFrameNode(frameNode);
    stack->Push(frameNode);
    pattern->sideBarStatus_ = SideBarStatus::HIDDEN;
    SideBarContainerModelInstance.SetSideBarPosition(SideBarPosition::END);
    pattern->UpdateAnimDir();
    EXPECT_EQ(pattern->animDir_, SideBarAnimationDirection::RTL);
}

/**
 * @tc.name: SideBarPatternTestNg018
 * @tc.desc: Test SideBar UpdateAnimDir
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg018, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    pattern->AttachToFrameNode(frameNode);
    stack->Push(frameNode);
    pattern->sideBarStatus_ = SideBarStatus::CHANGING;
    pattern->UpdateAnimDir();
    EXPECT_EQ(pattern->animDir_, SideBarAnimationDirection::LTR);
}

/**
 * @tc.name: SideBarPatternTestNg019
 * @tc.desc: Test SideBar UpdateAnimDir
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg019, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    pattern->AttachToFrameNode(frameNode);
    stack->Push(frameNode);
    pattern->sideBarStatus_ = SideBarStatus::AUTO;
    pattern->UpdateAnimDir();
    EXPECT_EQ(pattern->animDir_, SideBarAnimationDirection::LTR);
}

/**
 * @tc.name: SideBarPatternTestNg020
 * @tc.desc: Test SideBar UpdateAnimDir
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg020, TestSize.Level1)
{
    SideBarContainerModelNG SideBarContainerModelInstance;
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    pattern->AttachToFrameNode(frameNode);
    stack->Push(frameNode);
    pattern->sideBarStatus_ = SideBarStatus::SHOW;
    SideBarContainerModelInstance.SetSideBarPosition(SideBarPosition::END);
    pattern->UpdateAnimDir();
    EXPECT_EQ(pattern->animDir_, SideBarAnimationDirection::LTR);
}

/**
 * @tc.name: SideBarPatternTestNg021
 * @tc.desc: Test SideBar UpdateAnimDir
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg021, TestSize.Level1)
{
    SideBarContainerModelNG SideBarContainerModelInstance;
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    pattern->AttachToFrameNode(frameNode);
    stack->Push(frameNode);
    SideBarContainerModelInstance.SetSideBarPosition(SideBarPosition::START);
    pattern->sideBarStatus_ = SideBarStatus::HIDDEN;
    pattern->UpdateAnimDir();
    EXPECT_EQ(pattern->animDir_, SideBarAnimationDirection::LTR);
}

/**
 * @tc.name: SideBarSetOnChangeEvent001
 * @tc.desc: Test SideBar Set Func
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarSetOnChangeEvent001, TestSize.Level1)
{
    SideBarContainerModelNG sideBarContainerModelInstance;
    sideBarContainerModelInstance.Create();
    ChangeEvent eventOnChange = [](const bool isShow) { EXPECT_TRUE(isShow); };
    sideBarContainerModelInstance.SetOnChangeEvent(std::move(eventOnChange));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto sideBarContainerEventHub = frameNode->GetEventHub<NG::SideBarContainerEventHub>();
    ASSERT_NE(sideBarContainerEventHub, nullptr);
    sideBarContainerEventHub->SetOnChangeEvent(std::move(eventOnChange));
    sideBarContainerEventHub->FireChangeEvent(true);
    sideBarContainerEventHub->SetOnChangeEvent(nullptr);
    ASSERT_EQ(sideBarContainerEventHub->isShowChangeEvent_, nullptr);
}

/**
 * @tc.name: SideBarPatternTestNg022
 * @tc.desc: Test SideBar OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar ,then get pattern, frameNode, sideBarLayoutProperty
        layoutWrapper .
     * @tc.expected: check whether the pattern->needInitRealSideBarWidth_ is correct.
     */
    SideBarContainerModelNG sideBarContainerModelInstance;
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto sideBarLayoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(sideBarLayoutProperty, nullptr);

    WeakPtr<FrameNode> hostNode = frameNode;
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(
        AceType::MakeRefPtr<SideBarContainerLayoutAlgorithm>());
    ASSERT_NE(layoutAlgorithmWrapper, nullptr);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    auto algorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(layoutWrapper->GetLayoutAlgorithm());
    ASSERT_NE(algorithmWrapper, nullptr);
    auto algorithm = AceType::DynamicCast<SideBarContainerLayoutAlgorithm>(algorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(algorithm, nullptr);

    DirtySwapConfig config;
    EXPECT_TRUE(pattern->needInitRealSideBarWidth_);
    pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(pattern->needInitRealSideBarWidth_);
}

/**
 * @tc.name: SideBarPatternTestNg023
 * @tc.desc: Test SideBar HandleDragStart
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar ,then get pattern.
     * @tc.expected: check whether the pattern->sideBarStatus_ is correct.
     */
    SideBarContainerModelNG sideBarContainerModelInstance;
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->HandleDragStart();
    EXPECT_EQ(pattern->sideBarStatus_, SideBarStatus::SHOW);
}

/**
 * @tc.name: SideBarPatternTestNg024
 * @tc.desc: Test SideBar HandleDragStart
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar ,then get pattern.
     * @tc.expected: check whether the pattern->sideBarStatus_ is correct.
     */
    SideBarContainerModelNG sideBarContainerModelInstance;
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->sideBarStatus_, SideBarStatus::SHOW);
    /**
     * @tc.steps: step2. change pattern->sideBarStatus_.
     * @tc.expected: step2. check whether the pattern->sideBarStatus_ is correct.
     */
    pattern->sideBarStatus_ = SideBarStatus::HIDDEN;
    pattern->HandleDragStart();
    EXPECT_NE(pattern->sideBarStatus_, SideBarStatus::SHOW);
}

/**
 * @tc.name: SideBarPatternTestNg025
 * @tc.desc: Test SideBar HandleDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar ,then get pattern and frameNode.
     * @tc.expected: check whether the pattern->sideBarStatus_ is correct.
     */
    SideBarContainerModelNG sideBarContainerModelInstance;
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    pattern->frameNode_ = frameNode;

    pattern->sideBarStatus_ = SideBarStatus::SHOW;
    EXPECT_EQ(pattern->sideBarStatus_, SideBarStatus::SHOW);
    pattern->HandleDragUpdate(UPDATE_SIDE_BAR_WIDTH);
    EXPECT_EQ(pattern->sideBarStatus_, SideBarStatus::CHANGING);
    /**
     * @tc.steps: step2. change pattern->sideBarStatus_.
     * @tc.expected: check whether the pattern->sideBarStatus_ is correct.
     */
    pattern->sideBarStatus_ = SideBarStatus::HIDDEN;
    pattern->HandleDragUpdate(UPDATE_SIDE_BAR_WIDTH);
    EXPECT_NE(pattern->sideBarStatus_, SideBarStatus::SHOW);
}

/**
 * @tc.name: SideBarPatternTestNg026
 * @tc.desc: Test SideBar HandleDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar ,then get pattern.
     * @tc.expected: check whether the pattern->sideBarStatus_ is correct.
     */
    SideBarContainerModelNG sideBarContainerModelInstance;
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->HandleDragEnd();
    EXPECT_EQ(pattern->sideBarStatus_, SideBarStatus::SHOW);
    /**
     * @tc.steps: step2. change pattern->sideBarStatus_.
     * @tc.expected: check whether the sideBarContainerEventHub is correct.
     */
    pattern->sideBarStatus_ = SideBarStatus::HIDDEN;
    pattern->HandleDragEnd();
    EXPECT_NE(pattern->sideBarStatus_, SideBarStatus::SHOW);
}

/**
 * @tc.name: SideBarPatternTestNg027
 * @tc.desc: Test SideBar FireChangeEvent
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar ,then get pattern frameNode.
     * @tc.expected: check whether the sideBarContainerEventHub is correct.
     */
    SideBarContainerModelNG sideBarContainerModelInstance;
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    pattern->frameNode_ = frameNode;
    auto sideBarContainerEventHub = pattern->GetEventHub<SideBarContainerEventHub>();
    pattern->FireChangeEvent(false);
    EXPECT_NE(sideBarContainerEventHub, nullptr);
}

/**
 * @tc.name: SideBarPatternTestNg028
 * @tc.desc: Test SideBar HandleDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar ,then get pattern frameNode layoutProperty.
     * @tc.expected: check whether the showSideBar_ is correct.
     */
    SideBarContainerModelNG sideBarContainerModelInstance;
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    pattern->frameNode_ = frameNode;

    auto layoutProperty = pattern->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step2. get minSideBarWidth, host, geometryNode .
     * @tc.expected: check whether objects is correct.
     */
    auto minSideBarWidth = layoutProperty->GetMinSideBarWidth().value_or(DEFAULT_MIN_SIDE_BAR_WIDTH);
    auto maxSideBarWidth = layoutProperty->GetMaxSideBarWidth().value_or(DEFAULT_MAX_SIDE_BAR_WIDTH);
    EXPECT_EQ(DEFAULT_MIN_SIDE_BAR_WIDTH.unit_, DimensionUnit::VP);

    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto geometryNode = host->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);

    auto frameSize = geometryNode->GetFrameSize();
    auto parentWidth = frameSize.Width();
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto scaleProperty = constraint->scaleProperty;
    scaleProperty.vpScale = 1.0;
    auto minSideBarWidthPx = ConvertToPx(minSideBarWidth, scaleProperty, parentWidth).value_or(0);
    auto maxSideBarWidthPx = ConvertToPx(maxSideBarWidth, scaleProperty, parentWidth).value_or(0);

    auto sideBarPosition = layoutProperty->GetSideBarPosition().value_or(SideBarPosition::START);
    bool isSideBarStart = sideBarPosition == SideBarPosition::START;
    EXPECT_TRUE(isSideBarStart);

    auto preSidebarWidthPx = pattern->DimensionConvertToPx(pattern->preSidebarWidth_).value_or(0.0);
    auto sideBarLine = preSidebarWidthPx + (isSideBarStart ? UPDATE_SIDE_BAR_WIDTH : -UPDATE_SIDE_BAR_WIDTH);
    EXPECT_EQ(sideBarLine, UPDATE_SIDE_BAR_WIDTH);
    EXPECT_EQ(200, minSideBarWidthPx);
    EXPECT_EQ(280, maxSideBarWidthPx);

    pattern->HandleDragUpdate(UPDATE_SIDE_BAR_WIDTH);
    /**
     * @tc.steps: step3. change pattern->dragRect_.width_ and param.
     * @tc.expected: check whether halfDragRegionWidth is correct.
     */
    pattern->dragRect_.width_ = 100.0f;
    pattern->HandleDragUpdate(-20.0f);
    auto halfDragRegionWidth = pattern->dragRect_.Width() / 2;
    EXPECT_EQ(halfDragRegionWidth, 50.0);
    /**
     * @tc.steps: step4. change param.
     * @tc.expected: check whether autoHide_ is correct.
     */
    auto autoHide_ = layoutProperty->GetAutoHide().value_or(true);
    pattern->HandleDragUpdate(-60.0f);
    EXPECT_TRUE(autoHide_);
}

/**
 * @tc.name: SideBarPatternTestNg029
 * @tc.desc: Test SideBar OnUpdateShowSideBar
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar ,then get pattern frameNode layoutProperty and newShowSideBar,
     *  modify showSideBar_.
     * @tc.expected: check whether the showSideBar_ is correct.
     */
    SideBarContainerModelNG sideBarContainerModelInstance;
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    pattern->frameNode_ = frameNode;

    auto layoutProperty = pattern->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto newShowSideBar = layoutProperty->GetShowSideBar().value_or(true);
    EXPECT_TRUE(newShowSideBar);

    auto backButton = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<SideBarContainerPattern>());
    auto backButton1 = FrameNode::CreateFrameNode("BackButton", 34, AceType::MakeRefPtr<SideBarContainerPattern>());
    auto backButton2 = FrameNode::CreateFrameNode("BackButton", 35, AceType::MakeRefPtr<SideBarContainerPattern>());
    auto backButton3 = FrameNode::CreateFrameNode("BackButton", 36, AceType::MakeRefPtr<SideBarContainerPattern>());
    frameNode->children_.push_back(backButton);
    frameNode->children_.push_back(backButton1);
    frameNode->children_.push_back(backButton2);
    frameNode->children_.push_back(backButton3);
    EXPECT_TRUE(pattern->showSideBar_);
    pattern->showSideBar_ = false;
    EXPECT_FALSE(pattern->showSideBar_);
    pattern->OnUpdateShowSideBar(layoutProperty);
    EXPECT_FALSE(pattern->showSideBar_);
}

/**
 * @tc.name: SideBarPatternTestNg031
 * @tc.desc: Test SideBar CreateAndMountControlButton
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBarContainer node, and set the state of ShowSideBar to false.
     * Then execute CreateAndMountControlButton method.
     * @tc.expected: check whether the controlButton's fillColor is same as the default color.
     */
    SideBarContainerModelNG SideBarContainerModelInstance;
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    pattern->AttachToFrameNode(frameNode);

    auto themeManagerOne = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerOne);
    EXPECT_CALL(*themeManagerOne, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SideBarTheme>()));
    EXPECT_CALL(*themeManagerOne, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SideBarTheme>()));

    SideBarContainerModelInstance.SetShowSideBar(false);
    pattern->CreateAndMountControlButton(frameNode);

    auto children = frameNode->GetChildren();
    ASSERT_FALSE(children.empty());

    auto sideBarTheme = AceType::MakeRefPtr<SideBarTheme>();
    ASSERT_NE(sideBarTheme, nullptr);
    Color controlButtonColor = sideBarTheme->GetControlImageColor();

    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(children.front());
    ASSERT_NE(buttonFrameNode, nullptr);
    auto buttonChildren = buttonFrameNode->GetChildren();
    ASSERT_FALSE(buttonChildren.empty());
    auto imgFrameNode = AceType::DynamicCast<FrameNode>(buttonChildren.front());
    ASSERT_NE(imgFrameNode, nullptr);
    auto imageLayoutProperty = imgFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto imgSourceInfo = imageLayoutProperty->GetImageSourceInfoValue();
    EXPECT_EQ(imgSourceInfo.GetFillColor()->GetValue(), controlButtonColor.GetValue());
}

/**
 * @tc.name: SideBarPatternTestNg032
 * @tc.desc: Test SideBar OnUpdateShowControlButton
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create control button.
     */
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    pattern->AttachToFrameNode(frameNode);

    auto themeManagerOne = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerOne);
    EXPECT_CALL(*themeManagerOne, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SideBarTheme>()));
    EXPECT_CALL(*themeManagerOne, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SideBarTheme>()));
    pattern->CreateAndMountControlButton(frameNode);

    /**
     * @tc.steps: step2. Set showControlButton's value to false, then execute OnUpdateShowControlButton.
     * @tc.expected: button is not visible.
     */
    auto layoutProperty = pattern->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateShowControlButton(false);
    pattern->OnUpdateShowControlButton(layoutProperty, frameNode);

    auto children = frameNode->GetChildren();
    ASSERT_FALSE(children.empty());
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(children.front());
    ASSERT_NE(buttonFrameNode, nullptr);
    auto buttonLayoutProperty = buttonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonLayoutProperty, nullptr);
    auto visibility = buttonLayoutProperty->GetVisibility();
    EXPECT_EQ(visibility, VisibleType::GONE);

    /**
     * @tc.steps: step3. Set showControlButton's value to true, then execute OnUpdateShowControlButton.
     * @tc.expected: button is visible.
     */
    layoutProperty->UpdateShowControlButton(true);
    pattern->OnUpdateShowControlButton(layoutProperty, frameNode);
    buttonLayoutProperty = buttonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    visibility = buttonLayoutProperty->GetVisibility();
    EXPECT_EQ(visibility, VisibleType::VISIBLE);
}

/**
 * @tc.name: SideBarPatternTestNg033
 * @tc.desc: Test SideBar GetControlImageSize
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sidebarContainer frame node.
     */
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    pattern->AttachToFrameNode(frameNode);

    /**
     * @tc.steps: step2. Set platform version to 10, then execute GetControlImageSize.
     * @tc.expected: image's width is 24vp, and height is 24vp.
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    Dimension width;
    Dimension height;
    pattern->GetControlImageSize(width, height);
    EXPECT_EQ(width, DEFAULT_IMAGE_WIDTH_V10);
    EXPECT_EQ(height, DEFAULT_IMAGE_HEIGHT_V10);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);

    /**
     * @tc.steps: step3. Set image's width and height to 10vp, then execute GetControlImageSize.
     * @tc.expected: image's width is 10vp, and height is 10vp.
     */
    auto layoutProperty = pattern->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateControlButtonWidth(IMAGE_WIDTH);
    layoutProperty->UpdateControlButtonHeight(IMAGE_HEIGHT);
    pattern->GetControlImageSize(width, height);
    EXPECT_EQ(width, IMAGE_WIDTH);
    EXPECT_EQ(height, IMAGE_HEIGHT);
}

/**
 * @tc.name: SideBarPatternTestNg034
 * @tc.desc: Test SideBar AttachToFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg034, TestSize.Level1)
{
    SideBarContainerModelNG SideBarContainerModelInstance;
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->minPlatformVersion_ = 12;
    pattern->AttachToFrameNode(frameNode);
    pattern->OnModifyDone();
    SideBarContainerModelInstance.SetShowSideBar(true);
    EXPECT_EQ(pattern->sideBarStatus_, SideBarStatus::SHOW);
    EXPECT_NE(pattern->dragEvent_, nullptr);
}

/**
 * @tc.name: SideBarPatternTestNg035
 * @tc.desc: Test SideBar OnUpdateSideBarAndContent
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg035, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    auto backButton = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<SideBarContainerPattern>());
    auto backButton1 = FrameNode::CreateFrameNode("BackButton", 34, AceType::MakeRefPtr<SideBarContainerPattern>());
    auto backButton2 = FrameNode::CreateFrameNode("BackButton", 35, AceType::MakeRefPtr<SideBarContainerPattern>());
    auto backButton3 = FrameNode::CreateFrameNode("BackButton", 36, AceType::MakeRefPtr<SideBarContainerPattern>());
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    frameNode->children_.push_back(backButton);
    pattern->GetContentNode(host);
    frameNode->children_.push_back(backButton1);
    frameNode->children_.push_back(backButton2);
    frameNode->children_.push_back(backButton3);
    auto sideBarNode = pattern->GetSideBarNode(host);
    ASSERT_NE(sideBarNode, nullptr);
    auto sideBarContext = sideBarNode->GetRenderContext();
    ASSERT_NE(sideBarContext, nullptr);
    auto contentNode = pattern->GetContentNode(host);
    ASSERT_NE(contentNode, nullptr);
    contentNode->renderContext_ = AceType::MakeRefPtr<RenderContext>();
    auto contentContext = contentNode->GetRenderContext();
    ASSERT_NE(contentContext, nullptr);
    pattern->OnUpdateSideBarAndContent(host);
    EXPECT_NE(sideBarNode->renderContext_, nullptr);
    sideBarContext->UpdateClipEdge(true);
    contentContext->UpdateClipEdge(true);
    pattern->OnUpdateSideBarAndContent(host);
    EXPECT_NE(sideBarNode->renderContext_, nullptr);
}

/**
 * @tc.name: SideBarPatternTestNg036
 * @tc.desc: Test SideBar DoAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg036, TestSize.Level1)
{
    SideBarContainerModelNG SideBarContainerModelInstance;
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    pattern->AttachToFrameNode(frameNode);
    stack->Push(frameNode);
    pattern->sideBarStatus_ = SideBarStatus::SHOW;
    SideBarContainerModelInstance.SetSideBarPosition(SideBarPosition::START);
    pattern->UpdateAnimDir();
    auto layoutProperty = pattern->GetLayoutProperty<SideBarContainerLayoutProperty>();
    layoutProperty->layoutDirection_ = TextDirection::RTL;
    pattern->GetSideBarPositionWithRtl(layoutProperty);
    pattern->DoAnimation();
    EXPECT_EQ(pattern->animDir_, SideBarAnimationDirection::LTR);
    EXPECT_EQ(pattern->sideBarStatus_, SideBarStatus::CHANGING);
    pattern->animDir_ = SideBarAnimationDirection::RTL;
    EXPECT_EQ(pattern->currentOffset_, 0.0f);
    pattern->DoAnimation();
    EXPECT_EQ(pattern->animDir_, SideBarAnimationDirection::RTL);
    EXPECT_EQ(pattern->sideBarStatus_, SideBarStatus::CHANGING);
    pattern->animDir_ = SideBarAnimationDirection::RTL;
    EXPECT_EQ(pattern->currentOffset_, 0.0f);
}

/**
 * @tc.name: SideBarPatternTestNg037
 * @tc.desc: Test SideBar InitDividerMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg037, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar and controlbutton node,then register inputEvent to InitDividerMouseEvent.
     * @tc.expected: check whether the controlButtonHoverEvent_ is nullptr.
     */
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    int32_t imgNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto imgNode = FrameNode::GetOrCreateFrameNode(
        OHOS::Ace::V2::IMAGE_ETS_TAG, imgNodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(imgNode, nullptr);
    auto imgHub = imgNode->GetEventHub<EventHub>();
    ASSERT_NE(imgHub, nullptr);
    auto gestureHub = imgHub->GetOrCreateInputEventHub();
    ASSERT_NE(gestureHub, nullptr);
    pattern->SetHasControlButton(true);
    EXPECT_EQ(pattern->controlButtonHoverEvent_, nullptr);
    pattern->InitDividerMouseEvent(gestureHub);
    EXPECT_EQ(pattern->controlButtonClickEvent_, nullptr);
}

/**
 * @tc.name: SideBarPatternTestNg038
 * @tc.desc: Test SideBar OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg038, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar ,then get pattern, frameNode, sideBarLayoutProperty
        layoutWrapper .
     * @tc.expected: check whether the pattern->needInitRealSideBarWidth_ is correct.
     */
    SideBarContainerModelNG sideBarContainerModelInstance;
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto sideBarLayoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(sideBarLayoutProperty, nullptr);

    WeakPtr<FrameNode> hostNode = frameNode;
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(AceType::MakeRefPtr<SideBarContainerLayoutAlgorithm>());
    ASSERT_NE(layoutAlgorithmWrapper, nullptr);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    auto algorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(layoutWrapper->GetLayoutAlgorithm());
    ASSERT_NE(algorithmWrapper, nullptr);
    auto algorithm = AceType::DynamicCast<SideBarContainerLayoutAlgorithm>(algorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(algorithm, nullptr);

    DirtySwapConfig config;
    pattern->needInitRealSideBarWidth_ = false;
    pattern->isControlButtonClick_ = true;
    EXPECT_FALSE(pattern->needInitRealSideBarWidth_);
    pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(pattern->needInitRealSideBarWidth_);
}

/**
 * @tc.name: SideBarPatternTestNg039
 * @tc.desc: Test SideBar UpdateSideBarPosition
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg039, TestSize.Level1)
{
    float value = UPDATE_SIDE_BAR_POSITION_VALUE;
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    EXPECT_FALSE(pattern == nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->sideBarStatus_ = SideBarStatus::CHANGING;
    pattern->realSideBarWidth_ = REAL_SIDE_BAR_WIDTH_VALUE;
    pattern->UpdateSideBarPosition(value);
    EXPECT_EQ(pattern->sideBarStatus_, SideBarStatus::CHANGING);
    EXPECT_EQ(pattern->currentOffset_, CURRENT_OFFSET_VALUE);
}

/**
 * @tc.name: SideBarPatternTestNg040
 * @tc.desc: Test SideBar HandleDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg040, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar ,then get pattern and frameNode.
     * @tc.expected: check whether the pattern->sideBarStatus_ is correct.
     */
    SideBarContainerModelNG sideBarContainerModelInstance;
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    pattern->frameNode_ = frameNode;

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pattern->sideBarStatus_ = SideBarStatus::SHOW;
    EXPECT_EQ(pattern->sideBarStatus_, SideBarStatus::SHOW);
    pattern->maxSideBarWidth_ = MAX_SIDE_BAR;
    pattern->minSideBarWidth_ = MIN_SIDE_BAR;
    pipeline->minPlatformVersion_ = TEST_VALUE;
    pattern->HandleDragUpdate(CURRENT_OFFSET_VALUE);
    EXPECT_EQ(pattern->sideBarStatus_, SideBarStatus::SHOW);
}

/**
 * @tc.name: SideBarPatternTestNg041
 * @tc.desc: Test SideBar UpdateControlButtonIcon
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg041, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto themeManagerOne = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerOne);
    EXPECT_CALL(*themeManagerOne, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SideBarTheme>()));
    EXPECT_CALL(*themeManagerOne, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SideBarTheme>()));
    pattern->CreateAndMountControlButton(frameNode);
    auto children = frameNode->GetChildren();
    ASSERT_FALSE(children.empty());
    auto sideBarTheme = AceType::MakeRefPtr<SideBarTheme>();
    ASSERT_NE(sideBarTheme, nullptr);
    Color controlButtonColor = sideBarTheme->GetControlImageColor();
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(children.front());
    ASSERT_NE(buttonFrameNode, nullptr);
    auto buttonChildren = buttonFrameNode->GetChildren();
    ASSERT_FALSE(buttonChildren.empty());
    auto imgFrameNode = AceType::DynamicCast<FrameNode>(buttonChildren.front());
    ASSERT_NE(imgFrameNode, nullptr);
    auto imageLayoutProperty = imgFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    pattern->sideBarStatus_ = SideBarStatus::AUTO;
    pattern->UpdateControlButtonIcon();
    auto imgSourceInfo = imageLayoutProperty->GetImageSourceInfoValue();
    EXPECT_EQ(imgSourceInfo.GetFillColor()->GetValue(), controlButtonColor.GetValue());
}

/**
 * @tc.name: SideBarPatternTestNg042
 * @tc.desc: Test SideBar ConvertPxToPercent
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg042, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar ,then get pattern and frameNode.
     * @tc.expected: check whether the pattern->sideBarStatus_ is correct.
     */
    SideBarContainerModelNG sideBarContainerModelInstance;
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    pattern->frameNode_ = frameNode;

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pattern->sideBarStatus_ = SideBarStatus::SHOW;
    EXPECT_EQ(pattern->sideBarStatus_, SideBarStatus::SHOW);
    pattern->maxSideBarWidth_ = MAX_SIDE_BAR;
    pattern->minSideBarWidth_ = MIN_SIDE_BAR;
    pipeline->minPlatformVersion_ = TEST_VALUE;
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto geometryNode = host->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    pattern->ConvertPxToPercent(CURRENT_OFFSET_VALUE);
    geometryNode->SetFrameSize(SizeF(1.0f, 1.0f));
    pattern->ConvertPxToPercent(CURRENT_OFFSET_VALUE);
    EXPECT_EQ(pattern->sideBarStatus_, SideBarStatus::SHOW);
}

/**
 * @tc.name: SideBarPatternTestNg043
 * @tc.desc: Test SideBar InitDividerMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg043, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar and controlbutton node,then register inputEvent to InitDividerMouseEvent.
     * @tc.expected: check whether the controlButtonHoverEvent_ is nullptr.
     */
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    int32_t imgNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto imgNode = FrameNode::GetOrCreateFrameNode(
        OHOS::Ace::V2::IMAGE_ETS_TAG, imgNodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(imgNode, nullptr);
    auto imgHub = imgNode->GetEventHub<EventHub>();
    ASSERT_NE(imgHub, nullptr);
    auto gestureHub = imgHub->GetOrCreateInputEventHub();
    ASSERT_NE(gestureHub, nullptr);
    pattern->SetHasControlButton(true);
    EXPECT_EQ(pattern->controlButtonHoverEvent_, nullptr);
    pattern->InitDividerMouseEvent(gestureHub);
    EXPECT_EQ(pattern->controlButtonClickEvent_, nullptr);
    pattern->hoverEvent_->onHoverCallback_(true);
}

/**
 * @tc.name: SideBarPatternTestNg044
 * @tc.desc: Test SideBar OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg044, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar ,then get pattern, frameNode, sideBarLayoutProperty
        layoutWrapper .
     * @tc.expected: check whether the pattern->needInitRealSideBarWidth_ is correct.
     */
    SideBarContainerModelNG sideBarContainerModelInstance;
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto sideBarLayoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(sideBarLayoutProperty, nullptr);

    WeakPtr<FrameNode> hostNode = frameNode;
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(AceType::MakeRefPtr<SideBarContainerLayoutAlgorithm>());
    ASSERT_NE(layoutAlgorithmWrapper, nullptr);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    auto algorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(layoutWrapper->GetLayoutAlgorithm());
    ASSERT_NE(algorithmWrapper, nullptr);
    auto algorithm = AceType::DynamicCast<SideBarContainerLayoutAlgorithm>(algorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(algorithm, nullptr);

    DirtySwapConfig config;
    pattern->needInitRealSideBarWidth_ = false;
    pattern->isControlButtonClick_ = true;
    EXPECT_FALSE(pattern->needInitRealSideBarWidth_);
    pattern->autoHide_ = true;
    pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(pattern->needInitRealSideBarWidth_);
}

/**
 * @tc.name: SideBarPatternTestNg046
 * @tc.desc: Test SideBar DoAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg046, TestSize.Level1)
{
    SideBarContainerModelNG SideBarContainerModelInstance;
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    pattern->AttachToFrameNode(frameNode);
    stack->Push(frameNode);
    pattern->sideBarStatus_ = SideBarStatus::SHOW;
    SideBarContainerModelInstance.SetSideBarPosition(SideBarPosition::START);
    pattern->UpdateAnimDir();
    auto layoutProperty = pattern->GetLayoutProperty<SideBarContainerLayoutProperty>();
    layoutProperty->layoutDirection_ = TextDirection::RTL;
    pattern->GetSideBarPositionWithRtl(layoutProperty);
    pattern->autoHide_ = true;
    pattern->DoAnimation();
    EXPECT_EQ(pattern->sideBarStatus_, SideBarStatus::CHANGING);
    pattern->animDir_ = SideBarAnimationDirection::RTL;
    EXPECT_EQ(pattern->currentOffset_, 0.0f);
}

/**
 * @tc.name: SideBarPatternTestNg047
 * @tc.desc: Test SideBar OnUpdateSideBarAndContent
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg047, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    auto backButton = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<SideBarContainerPattern>());
    auto backButton1 = FrameNode::CreateFrameNode("BackButton", 34, AceType::MakeRefPtr<SideBarContainerPattern>());
    auto backButton2 = FrameNode::CreateFrameNode("BackButton", 35, AceType::MakeRefPtr<SideBarContainerPattern>());
    auto backButton3 = FrameNode::CreateFrameNode("BackButton", 36, AceType::MakeRefPtr<SideBarContainerPattern>());
    auto customNode = CustomNode::CreateCustomNode(1, "CustomNode");
    frameNode->children_.push_back(backButton);
    frameNode->children_.push_back(backButton1);
    frameNode->children_.push_back(backButton2);
    frameNode->children_.push_back(backButton3);
    pattern->CreateAndMountNodes();
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto children = host->GetChildren();
    auto sideBarNode = children.front();
    ASSERT_NE(sideBarNode, nullptr);
    auto sideBarFrameNode = AceType::DynamicCast<FrameNode>(sideBarNode);
    ASSERT_NE(sideBarFrameNode, nullptr);
    auto renderContext = sideBarFrameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    pattern->CreateAndMountNodes();
    pattern->hasControlButton_ = false;
    auto color = Color();
    renderContext->UpdateBackgroundColor(color);
    ASSERT_TRUE(renderContext->HasBackgroundColor());
    pattern->CreateAndMountNodes();
}

/**
 * @tc.name: SideBarPatternTestNg048
 * @tc.desc: Test SideBar CreateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg048, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get pattern and frameNode, modify sideBarStatus_.
     * @tc.expected: check whether the showSideBar_ is correct.
     */
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->rightToLeftAnimation_ = nullptr;
    pattern->CreateAnimation();
    pattern->rightToLeftAnimation_->callbacks_.begin()->second(1.0f);
    pattern->leftToRightAnimation_ = nullptr;
    pattern->CreateAnimation();
    pattern->leftToRightAnimation_->callbacks_.begin()->second(1.0f);
}

/**
 * @tc.name: SideBarPatternTestNg049
 * @tc.desc: Test SideBar GetDividerNode
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg049, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    auto backButton = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<SideBarContainerPattern>());
    auto backButton1 = FrameNode::CreateFrameNode("BackButton", 34, AceType::MakeRefPtr<SideBarContainerPattern>());
    auto backButton2 = FrameNode::CreateFrameNode("BackButton", 35, AceType::MakeRefPtr<SideBarContainerPattern>());
    auto backButton3 = FrameNode::CreateFrameNode("BackButton", 36, AceType::MakeRefPtr<SideBarContainerPattern>());
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    pattern->GetDividerNode();
    frameNode->children_.push_back(backButton);
    frameNode->children_.push_back(backButton1);
    frameNode->children_.push_back(backButton2);
    frameNode->children_.push_back(backButton3);
    auto sideBarNode = pattern->GetSideBarNode(host);
    ASSERT_NE(sideBarNode, nullptr);
    auto sideBarContext = sideBarNode->GetRenderContext();
    ASSERT_NE(sideBarContext, nullptr);
    pattern->GetDividerNode();
    ASSERT_FALSE(pattern->GetDividerNode());
}

/**
 * @tc.name: SideBarPatternTestNg050
 * @tc.desc: Test SideBar OnUpdateShowSideBar
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg050, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar ,then get pattern frameNode layoutProperty and newShowSideBar,
     *  modify showSideBar_.
     * @tc.expected: check whether the showSideBar_ is correct.
     */
    SideBarContainerModelNG sideBarContainerModelInstance;
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    pattern->frameNode_ = frameNode;
    auto layoutProperty = pattern->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto backButton = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<SideBarContainerPattern>());
    auto backButton1 = FrameNode::CreateFrameNode("BackButton", 34, AceType::MakeRefPtr<SideBarContainerPattern>());
    auto backButton2 = FrameNode::CreateFrameNode("BackButton", 35, AceType::MakeRefPtr<SideBarContainerPattern>());
    auto backButton3 = FrameNode::CreateFrameNode("BackButton", 36, AceType::MakeRefPtr<SideBarContainerPattern>());
    frameNode->children_.push_back(backButton);
    frameNode->children_.push_back(backButton1);
    frameNode->children_.push_back(backButton2);
    frameNode->children_.push_back(backButton3);
    auto newShowSideBar = layoutProperty->GetShowSideBar().value_or(true);
    EXPECT_TRUE(newShowSideBar);
    EXPECT_TRUE(pattern->showSideBar_);
    pattern->showSideBar_ = false;
    EXPECT_FALSE(pattern->showSideBar_);
    pattern->hasInit_ = true;
    pattern->sideBarStatus_ = SideBarStatus::HIDDEN;
    pattern->OnUpdateShowSideBar(layoutProperty);
    EXPECT_FALSE(pattern->showSideBar_);
}

/**
 * @tc.name: SideBarPatternTestNg051
 * @tc.desc: Test SideBar AddDividerHotZoneRect
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg051, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar ,then get pattern, frameNode, sideBarLayoutProperty
        layoutWrapper .
     * @tc.expected: check whether the pattern->needInitRealSideBarWidth_ is correct.
     */
    SideBarContainerModelNG sideBarContainerModelInstance;
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto sideBarLayoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(sideBarLayoutProperty, nullptr);
    WeakPtr<FrameNode> hostNode = frameNode;
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(AceType::MakeRefPtr<SideBarContainerLayoutAlgorithm>());
    ASSERT_NE(layoutAlgorithmWrapper, nullptr);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    auto algorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(layoutWrapper->GetLayoutAlgorithm());
    ASSERT_NE(algorithmWrapper, nullptr);
    auto algorithm = AceType::DynamicCast<SideBarContainerLayoutAlgorithm>(algorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(algorithm, nullptr);
    pattern->realDividerWidth_ = 1.0f;
    pattern->AddDividerHotZoneRect(algorithm);
    EXPECT_TRUE(pattern->realDividerWidth_);
}

/**
 * @tc.name: SideBarPatternTestNg052
 * @tc.desc: Test SideBar GetSideBarNodeOrFirstChild
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg052, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    auto backButton = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<SideBarContainerPattern>());
    frameNode->children_.push_back(backButton);
    auto sideBarNode = pattern->GetSideBarNodeOrFirstChild();
    EXPECT_EQ(sideBarNode, nullptr);
}

/**
 * @tc.name: SideBarPatternTestNg053
 * @tc.desc: Test SideBar GetSideBarNodeOrFirstChild
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg053, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    auto backButton = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<SideBarContainerPattern>());
    auto backButton1 = FrameNode::CreateFrameNode("BackButton", 34, AceType::MakeRefPtr<SideBarContainerPattern>());
    auto backButton2 = FrameNode::CreateFrameNode("BackButton", 35, AceType::MakeRefPtr<SideBarContainerPattern>());
    auto backButton3 = FrameNode::CreateFrameNode("BackButton", 36, AceType::MakeRefPtr<SideBarContainerPattern>());
    frameNode->children_.push_back(backButton);
    frameNode->children_.push_back(backButton1);
    frameNode->children_.push_back(backButton2);
    frameNode->children_.push_back(backButton3);
    auto sideBarNode = pattern->GetSideBarNodeOrFirstChild();
    EXPECT_NE(sideBarNode, nullptr);
}

/**
 * @tc.name: SideBarPatternTestNg054
 * @tc.desc: Test SideBar GetControlButtonNode
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg054, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    auto sideBarNode = pattern->GetControlButtonNode();
    EXPECT_EQ(sideBarNode, nullptr);
}

/**
 * @tc.name: SideBarPatternTestNg055
 * @tc.desc: Test SideBar GetControlButtonNode
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg055, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    auto backButton = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<SideBarContainerPattern>());
    auto backButton1 = FrameNode::CreateFrameNode("BackButton", 34, AceType::MakeRefPtr<SideBarContainerPattern>());
    frameNode->children_.push_back(backButton);
    frameNode->children_.push_back(backButton1);
    auto sideBarNode = pattern->GetControlButtonNode();
    EXPECT_EQ(sideBarNode, nullptr);
}

/**
 * @tc.name: SideBarPatternTestNg056
 * @tc.desc: Test SideBar GetControlButtonNode
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg056, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    auto uINode = AceType::DynamicCast<UINode>(frameNode);
    frameNode->children_.push_back(uINode);
    auto sideBarNode = pattern->GetControlButtonNode();
    EXPECT_EQ(sideBarNode, nullptr);
}

/**
 * @tc.name: SideBarPatternTestNg057
 * @tc.desc: Test SideBar OnLanguageConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg057, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    /**
     * @tc.steps: step1. set to RightToLeft mode, call OnLanguageConfigurationUpdate, then get current isRightToLeft_.
     * @tc.expected: check whether the pattern->isRightToLeft_ is correct.
     */
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    pattern->OnLanguageConfigurationUpdate();
    EXPECT_EQ(pattern->isRightToLeft_, true);

    /**
     * @tc.steps: step2. set to LeftToRight mode, call OnLanguageConfigurationUpdate, then get current isRightToLeft_.
     * @tc.expected: check whether the pattern->isRightToLeft_ is correct.
     */
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    pattern->OnLanguageConfigurationUpdate();
    EXPECT_EQ(pattern->isRightToLeft_, false);
}

/**
 * @tc.name: SideBarPatternTestNg058
 * @tc.desc: Test SideBar InitLongPressEvent
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg058, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto context = PipelineBase::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto sideBarTheme = context->GetTheme<SideBarTheme>();
    ASSERT_NE(sideBarTheme, nullptr);
    auto buttonNode = pattern->CreateControlButton(sideBarTheme);
    ASSERT_NE(buttonNode, nullptr);

    pattern->InitLongPressEvent(buttonNode);
    EXPECT_NE(pattern->longPressEvent_, nullptr);
    EXPECT_NE(pattern->longPressActionEnd_, nullptr);
}

/**
 * @tc.name: SideBarPatternTestNg059
 * @tc.desc: Test SideBar HandleLongPressActionEnd
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg059, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->HandleLongPressActionEnd();
    EXPECT_EQ(pattern->dialogNode_, nullptr);
    EXPECT_FALSE(pattern->isDialogShow_);
}

/**
 * @tc.name: SideBarPatternTestNg060
 * @tc.desc: Test SideBar GetFirstFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg060, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    auto backButton = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<SideBarContainerPattern>());
    auto backButton1 = FrameNode::CreateFrameNode("BackButton", 34, AceType::MakeRefPtr<SideBarContainerPattern>());
    auto backButton2 = FrameNode::CreateFrameNode("BackButton", 35, AceType::MakeRefPtr<SideBarContainerPattern>());
    auto backButton3 = FrameNode::CreateFrameNode("BackButton", 36, AceType::MakeRefPtr<SideBarContainerPattern>());
    frameNode->children_.push_back(backButton);
    frameNode->children_.push_back(backButton1);
    frameNode->children_.push_back(backButton2);
    frameNode->children_.push_back(backButton3);
    pattern->CreateAndMountNodes();
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto uINode = AceType::DynamicCast<UINode>(host);
    ASSERT_NE(uINode, nullptr);
    auto firstChildNode = pattern->GetFirstFrameNode(uINode);
    EXPECT_NE(firstChildNode, nullptr);
}

/**
 * @tc.name: SideBarPatternTestNg061
 * @tc.desc: Test SideBar GetControlButtonNode
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg061, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    auto backButton = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, 33, AceType::MakeRefPtr<SideBarContainerPattern>());
    auto backButton1 = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, 34, AceType::MakeRefPtr<SideBarContainerPattern>());
    frameNode->children_.push_back(backButton);
    frameNode->children_.push_back(backButton1);
    auto sideBarNode = pattern->GetControlButtonNode();
    EXPECT_NE(sideBarNode, nullptr);
}

/**
 * @tc.name: SideBarPatternTestNg062
 * @tc.desc: Test SideBar property set function with frameNode.
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg062, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar and set the properties ,and then get frameNode.
     */
    auto sideBarNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::SIDE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(sideBarNode, nullptr);
    SideBarContainerModelNG sideBarContainerModelInstance;
    sideBarContainerModelInstance.SetSideBarWidth(AceType::RawPtr(sideBarNode), SIDE_BAR_WIDTH);
    sideBarContainerModelInstance.SetMinSideBarWidth(AceType::RawPtr(sideBarNode), MIN_SIDE_BAR_WIDTH);
    sideBarContainerModelInstance.SetMaxSideBarWidth(AceType::RawPtr(sideBarNode), MAX_SIDE_BAR_WIDTH);
    sideBarContainerModelInstance.SetControlButtonWidth(AceType::RawPtr(sideBarNode), WIDTH);
    sideBarContainerModelInstance.SetControlButtonHeight(AceType::RawPtr(sideBarNode), HEIGHT);
    sideBarContainerModelInstance.SetControlButtonLeft(AceType::RawPtr(sideBarNode), LEFT);
    sideBarContainerModelInstance.SetControlButtonTop(AceType::RawPtr(sideBarNode), TOP);
    sideBarContainerModelInstance.SetControlButtonShowIconInfo(AceType::RawPtr(sideBarNode),
        SHOW_ICON_STR, false, nullptr);
    sideBarContainerModelInstance.SetControlButtonHiddenIconInfo(AceType::RawPtr(sideBarNode),
        HIDDEN_ICON_STR, false, nullptr);
    sideBarContainerModelInstance.SetControlButtonSwitchingIconInfo(AceType::RawPtr(sideBarNode),
        SWITCHING_ICON_STR, false, nullptr);
    sideBarContainerModelInstance.SetShowControlButton(AceType::RawPtr(sideBarNode), SHOW_CONTROL_BUTTON);
    sideBarContainerModelInstance.SetAutoHide(AceType::RawPtr(sideBarNode), AUTO_HIDE);
    sideBarContainerModelInstance.SetMinContentWidth(AceType::RawPtr(sideBarNode), MIN_CONTENT_WIDTH);
    sideBarContainerModelInstance.SetSideBarPosition(AceType::RawPtr(sideBarNode), SIDE_BAR_POSITION);
    sideBarContainerModelInstance.SetShowSideBar(AceType::RawPtr(sideBarNode), IS_SHOW);
    sideBarContainerModelInstance.SetDividerStrokeWidth(AceType::RawPtr(sideBarNode), DIVIDER_STROKE_WIDTH);
    sideBarContainerModelInstance.SetDividerColor(AceType::RawPtr(sideBarNode), Color::BLUE);
    sideBarContainerModelInstance.SetDividerStartMargin(AceType::RawPtr(sideBarNode), DIVIDER_START_MARGIN);
    sideBarContainerModelInstance.SetDividerEndMargin(AceType::RawPtr(sideBarNode), DIVIDER_END_MARGIN);
    sideBarContainerModelInstance.MarkNeedInitRealSideBarWidth(AceType::RawPtr(sideBarNode));
    
    /**
     * @tc.steps: step2. get the properties of all settings.
     * @tc.expected: step2. check whether the properties is correct.
     */
    auto sideBarLayoutProperty = sideBarNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(sideBarLayoutProperty, nullptr);
    EXPECT_EQ(sideBarLayoutProperty->GetShowSideBar(), IS_SHOW);
    EXPECT_EQ(sideBarLayoutProperty->GetShowControlButton(), SHOW_CONTROL_BUTTON);
    EXPECT_EQ(sideBarLayoutProperty->GetSideBarWidth(), SIDE_BAR_WIDTH);
    EXPECT_EQ(sideBarLayoutProperty->GetMinSideBarWidth(), MIN_SIDE_BAR_WIDTH);
    EXPECT_EQ(sideBarLayoutProperty->GetMaxSideBarWidth(), MAX_SIDE_BAR_WIDTH);
    EXPECT_EQ(sideBarLayoutProperty->GetMinContentWidth(), MIN_CONTENT_WIDTH);
    EXPECT_EQ(sideBarLayoutProperty->GetAutoHide(), AUTO_HIDE);
    EXPECT_EQ(sideBarLayoutProperty->GetSideBarPosition(), SIDE_BAR_POSITION);
    EXPECT_EQ(sideBarLayoutProperty->GetControlButtonWidth(), WIDTH);
    EXPECT_EQ(sideBarLayoutProperty->GetControlButtonHeight(), HEIGHT);
    EXPECT_EQ(sideBarLayoutProperty->GetControlButtonLeft(), LEFT);
    EXPECT_EQ(sideBarLayoutProperty->GetControlButtonTop(), TOP);
    EXPECT_EQ(sideBarLayoutProperty->GetControlButtonShowIconInfo()->GetSrc(), SHOW_ICON_STR);
    EXPECT_EQ(sideBarLayoutProperty->GetControlButtonHiddenIconInfo()->GetSrc(), HIDDEN_ICON_STR);
    EXPECT_EQ(sideBarLayoutProperty->GetControlButtonSwitchingIconInfo()->GetSrc(), SWITCHING_ICON_STR);
    EXPECT_EQ(sideBarLayoutProperty->GetDividerStrokeWidth(), DIVIDER_STROKE_WIDTH);
    EXPECT_EQ(sideBarLayoutProperty->GetDividerColor(), Color::BLUE);
    EXPECT_EQ(sideBarLayoutProperty->GetDividerStartMargin(), DIVIDER_START_MARGIN);
    EXPECT_EQ(sideBarLayoutProperty->GetDividerEndMargin(), DIVIDER_END_MARGIN);
    sideBarContainerModelInstance.ResetControlButtonLeft(AceType::RawPtr(sideBarNode));
    sideBarContainerModelInstance.ResetControlButtonIconInfo();
    sideBarContainerModelInstance.ResetControlButtonIconInfo(AceType::RawPtr(sideBarNode));
}

/**
 * @tc.name: SideBarPatternTestNg063
 * @tc.desc: Test SideBar pattern OnUpdateShowSideBar function.
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg063, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar, get pattern and layoutProperty.
     */
    auto sideBarFrameNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::SIDE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(sideBarFrameNode, nullptr);
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(sideBarPattern, nullptr);
    auto sideBarLayoutProperty = sideBarFrameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(sideBarLayoutProperty, nullptr);
    sideBarPattern->hasInit_ = true;
    sideBarLayoutProperty->UpdateShowSideBar(true);
    sideBarPattern->sideBarStatus_ = SideBarStatus::SHOW;
    sideBarPattern->OnUpdateShowSideBar(sideBarLayoutProperty);
    sideBarPattern->sideBarStatus_ = SideBarStatus::HIDDEN;
    sideBarPattern->OnUpdateShowSideBar(sideBarLayoutProperty);
    sideBarPattern->hasInit_ = false;
    sideBarPattern->OnUpdateShowSideBar(sideBarLayoutProperty);
    sideBarPattern->sideBarStatus_ = SideBarStatus::SHOW;
    sideBarPattern->OnUpdateShowSideBar(sideBarLayoutProperty);

    /**
     * @tc.steps: step2. call OnUpdateShowSideBar function.
     * @tc.expected: step2. sideBarNode active status is set.
     */
    auto contentNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto sideBarNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto dividerNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::DIVIDER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<DividerPattern>());
    auto controlBtnNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    sideBarFrameNode->children_.push_back(contentNode);
    sideBarFrameNode->children_.push_back(sideBarNode);
    sideBarFrameNode->children_.push_back(dividerNode);
    sideBarFrameNode->children_.push_back(controlBtnNode);
    sideBarNode = sideBarPattern->GetSideBarNode(sideBarFrameNode);
    ASSERT_NE(sideBarNode, nullptr);
    sideBarLayoutProperty->UpdateShowSideBar(false);
    sideBarPattern->OnUpdateShowSideBar(sideBarLayoutProperty);
    EXPECT_FALSE(sideBarNode->IsActive());
    sideBarPattern->hasInit_ = true;
    sideBarPattern->OnUpdateShowSideBar(sideBarLayoutProperty);
    EXPECT_FALSE(sideBarNode->IsActive());
    sideBarPattern->sideBarStatus_ = SideBarStatus::HIDDEN;
    sideBarPattern->OnUpdateShowSideBar(sideBarLayoutProperty);
    EXPECT_FALSE(sideBarNode->IsActive());
    sideBarPattern->hasInit_ = false;
    sideBarPattern->OnUpdateShowSideBar(sideBarLayoutProperty);
    EXPECT_FALSE(sideBarNode->IsActive());
    sideBarNode->MarkBuildDone();
    sideBarPattern->OnUpdateShowSideBar(sideBarLayoutProperty);
    EXPECT_FALSE(sideBarNode->IsActive());
    sideBarLayoutProperty->UpdateShowSideBar(true);
    sideBarPattern->OnUpdateShowSideBar(sideBarLayoutProperty);
    EXPECT_FALSE(sideBarNode->IsActive());
}

/**
 * @tc.name: SideBarPatternTestNg064
 * @tc.desc: Test SideBar pattern OnUpdateShowDivider function.
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg064, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar, get pattern and layoutProperty.
     */
    auto sideBarFrameNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::SIDE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(sideBarFrameNode, nullptr);
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(sideBarPattern, nullptr);
    auto sideBarLayoutProperty = sideBarFrameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(sideBarLayoutProperty, nullptr);
    auto contentNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(contentNode, nullptr);
    auto sideBarNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(sideBarNode, nullptr);
    auto dividerNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::DIVIDER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<DividerPattern>());
    ASSERT_NE(dividerNode, nullptr);
    auto controlBtnNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(controlBtnNode, nullptr);
    sideBarFrameNode->children_.push_back(contentNode);
    sideBarFrameNode->children_.push_back(sideBarNode);
    sideBarFrameNode->children_.push_back(dividerNode);
    sideBarFrameNode->children_.push_back(controlBtnNode);

    /**
     * @tc.steps: step2. call OnUpdateShowDivider function.
     * @tc.expected: step2. divider's color and width is set.
     */
    sideBarLayoutProperty->UpdateDividerColor(Color::BLUE);
    sideBarLayoutProperty->UpdateDividerStrokeWidth(DIVIDER_STROKE_WIDTH);
    sideBarPattern->OnUpdateShowDivider(sideBarLayoutProperty, sideBarFrameNode);
    auto dividerRenderProperty = dividerNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(dividerRenderProperty, nullptr);
    EXPECT_EQ(dividerRenderProperty->GetDividerColor(), Color::BLUE);
    auto dividerLayoutProperty = dividerNode->GetLayoutProperty<DividerLayoutProperty>();
    ASSERT_NE(dividerLayoutProperty, nullptr);
    EXPECT_EQ(dividerLayoutProperty->GetStrokeWidth(), DIVIDER_STROKE_WIDTH);
}

/**
 * @tc.name: SideBarPatternTestNg065
 * @tc.desc: Test SideBar pattern UpdateDividerShadow function.
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg065, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar, get pattern and layoutProperty.
     */
    auto sideBarFrameNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::SIDE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(sideBarFrameNode, nullptr);
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(sideBarPattern, nullptr);
    auto sideBarLayoutProperty = sideBarFrameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(sideBarLayoutProperty, nullptr);
    auto context = PipelineBase::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto sideBarTheme = context->GetTheme<SideBarTheme>();
    ASSERT_NE(sideBarTheme, nullptr);
    sideBarTheme->dividerShadowEnable_ = true;
    auto contentNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(contentNode, nullptr);
    auto sideBarNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(sideBarNode, nullptr);
    auto dividerNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::DIVIDER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<DividerPattern>());
    ASSERT_NE(dividerNode, nullptr);
    auto controlBtnNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(controlBtnNode, nullptr);
    sideBarFrameNode->children_.push_back(contentNode);
    sideBarFrameNode->children_.push_back(sideBarNode);
    sideBarFrameNode->children_.push_back(dividerNode);
    sideBarFrameNode->children_.push_back(controlBtnNode);

    /**
     * @tc.steps: step2. call UpdateDividerShadow function.
     * @tc.expected: step2. SideBar component's ZIndex is changed.
     */
    sideBarLayoutProperty->UpdateSideBarContainerType(SideBarContainerType::EMBED);
    auto sideBarRenderContext = sideBarNode->GetRenderContext();
    ASSERT_NE(sideBarRenderContext, nullptr);
    auto dividerRenderContext = dividerNode->GetRenderContext();
    ASSERT_NE(dividerRenderContext, nullptr);
    auto contentRenderContext = contentNode->GetRenderContext();
    ASSERT_NE(contentRenderContext, nullptr);
    auto controlBtnRenderContext = controlBtnNode->GetRenderContext();
    ASSERT_NE(controlBtnRenderContext, nullptr);
    sideBarPattern->UpdateDividerShadow();
    EXPECT_EQ(sideBarRenderContext->GetZIndexValue(-1), DEFAULT_SIDE_BAR_ZINDEX_EMBED);
    EXPECT_EQ(dividerRenderContext->GetZIndexValue(-1), DEFAULT_DIVIDER_ZINDEX_EMBED);
    EXPECT_EQ(contentRenderContext->GetZIndexValue(-1), DEFAULT_CONTENT_ZINDEX_EMBED);
    EXPECT_EQ(controlBtnRenderContext->GetZIndexValue(-1), DEFAULT_CONTROL_BUTTON_ZINDEX);

    sideBarLayoutProperty->UpdateSideBarContainerType(SideBarContainerType::OVERLAY);
    sideBarPattern->UpdateDividerShadow();
    EXPECT_EQ(sideBarRenderContext->GetZIndexValue(-1), DEFAULT_SIDE_BAR_ZINDEX_OVERLAY);
    EXPECT_EQ(dividerRenderContext->GetZIndexValue(-1), DEFAULT_DIVIDER_ZINDEX_OVERLAY);
    EXPECT_EQ(contentRenderContext->GetZIndexValue(-1), DEFAULT_CONTENT_ZINDEX_OVERLAY);
    EXPECT_EQ(controlBtnRenderContext->GetZIndexValue(-1), DEFAULT_CONTROL_BUTTON_ZINDEX);
}

/**
 * @tc.name: SideBarPatternTestNg066
 * @tc.desc: Test SideBar pattern UpdateDividerShadow function.
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg066, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar, get pattern and layoutProperty.
     */
    auto sideBarFrameNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::SIDE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(sideBarFrameNode, nullptr);
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(sideBarPattern, nullptr);

    /**
     * @tc.steps: step2. call CreateNodePaintMethod function.
     * @tc.expected: step2. Get paintMethod.
     */
    auto paintMethod = AceType::DynamicCast<SideBarContainerPaintMethod>(sideBarPattern->CreateNodePaintMethod());
    EXPECT_NE(paintMethod, nullptr);
    EXPECT_FALSE(paintMethod->needClipPadding_);
}

/**
 * @tc.name: SideBarPatternTestNg067
 * @tc.desc: Test SideBar pattern ShowDialogWithNode function.
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg067, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar, get pattern and layoutProperty.
     */
    auto sideBarFrameNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::SIDE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(sideBarFrameNode, nullptr);
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(sideBarPattern, nullptr);
    auto contentNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(contentNode, nullptr);
    auto sideBarNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(sideBarNode, nullptr);
    auto dividerNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::DIVIDER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<DividerPattern>());
    ASSERT_NE(dividerNode, nullptr);
    auto controlBtnNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(controlBtnNode, nullptr);
    sideBarFrameNode->children_.push_back(contentNode);
    sideBarFrameNode->children_.push_back(sideBarNode);
    sideBarFrameNode->children_.push_back(dividerNode);
    sideBarFrameNode->children_.push_back(controlBtnNode);

    /**
     * @tc.steps: step2. call ShowDialogWithNode function.
     * @tc.expected: step2. isDialogShow_ is set.
     */
    sideBarPattern->isDialogShow_ = true;
    sideBarPattern->ShowDialogWithNode();
    sideBarPattern->isDialogShow_ = false;
    sideBarPattern->ShowDialogWithNode();
    EXPECT_TRUE(sideBarPattern->isDialogShow_);
}

/**
 * @tc.name: SideBarPatternTestNg068
 * @tc.desc: Test SideBar GetContentNode with contentNode is customNode.
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg068, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar with contentNode is a customNode, get pattern.
     */
    auto sideBarFrameNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::SIDE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(sideBarFrameNode, nullptr);
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(sideBarPattern, nullptr);
    auto viewId = NG::ViewStackProcessor::GetInstance()->ClaimNodeId();
    auto viewIdStr = std::to_string(viewId);
    auto key = NG::ViewStackProcessor::GetInstance()->ProcessViewId(viewIdStr);
    auto customContentNode = NG::CustomNode::CreateCustomNode(viewId, key);
    ASSERT_NE(customContentNode, nullptr);
    auto sideBarNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(sideBarNode, nullptr);
    auto dividerNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::DIVIDER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<DividerPattern>());
    ASSERT_NE(dividerNode, nullptr);
    auto controlBtnNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(controlBtnNode, nullptr);
    sideBarFrameNode->children_.push_back(customContentNode);
    sideBarFrameNode->children_.push_back(sideBarNode);
    sideBarFrameNode->children_.push_back(dividerNode);
    sideBarFrameNode->children_.push_back(controlBtnNode);
    auto childID = ElementRegister::GetInstance()->MakeUniqueId();
    auto contentChildNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::COLUMN_ETS_TAG,
        childID, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    customContentNode->children_.push_back(contentChildNode);

    /**
     * @tc.steps: step2. call GetContentNode function.
     * @tc.expected: step2. get child node of contentNode.
     */
    auto resultNode = sideBarPattern->GetContentNode(sideBarFrameNode);
    ASSERT_NE(resultNode, nullptr);
    EXPECT_EQ(resultNode->GetId(), childID);
}

/**
 * @tc.name: SideBarPatternTestNg069
 * @tc.desc: Test SideBar GetSideBarNode with sideBarNode is customNode.
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg069, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar with few child node, get pattern.
     */
    auto sideBarFrameNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::SIDE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(sideBarFrameNode, nullptr);
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(sideBarPattern, nullptr);
    auto contentNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(contentNode, nullptr);
    auto viewId = NG::ViewStackProcessor::GetInstance()->ClaimNodeId();
    auto viewIdStr = std::to_string(viewId);
    auto key = NG::ViewStackProcessor::GetInstance()->ProcessViewId(viewIdStr);
    auto customSideBarNode = NG::CustomNode::CreateCustomNode(viewId, key);
    ASSERT_NE(customSideBarNode, nullptr);
    auto dividerNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::DIVIDER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<DividerPattern>());
    ASSERT_NE(dividerNode, nullptr);
    auto controlBtnNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(controlBtnNode, nullptr);
    sideBarFrameNode->children_.push_back(contentNode);
    sideBarFrameNode->children_.push_back(customSideBarNode);

    /**
     * @tc.steps: step2. call GetSideBarNode function.
     * @tc.expected: step2. get nullptr.
     */
    auto resultNode = sideBarPattern->GetSideBarNode(sideBarFrameNode);
    EXPECT_EQ(resultNode, nullptr);

    /**
     * @tc.steps: step3. set a child node to sideBarNode.
     */
    auto childID = ElementRegister::GetInstance()->MakeUniqueId();
    auto sideBarChildNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::COLUMN_ETS_TAG,
        childID, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    customSideBarNode->children_.push_back(sideBarChildNode);
    sideBarFrameNode->Clean();
    sideBarFrameNode->children_.push_back(contentNode);
    sideBarFrameNode->children_.push_back(customSideBarNode);
    sideBarFrameNode->children_.push_back(dividerNode);
    sideBarFrameNode->children_.push_back(controlBtnNode);

    /**
     * @tc.steps: step4. call GetSideBarNode function.
     * @tc.expected: step4. get child node of sideBarNode.
     */
    resultNode = sideBarPattern->GetSideBarNode(sideBarFrameNode);
    ASSERT_NE(resultNode, nullptr);
    EXPECT_EQ(resultNode->GetId(), childID);
}

/**
 * @tc.name: SideBarPatternTestNg070
 * @tc.desc: Test SideBar GetFirstFrameNode with first node is customNode.
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg070, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar with no child node, get pattern.
     */
    auto sideBarFrameNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::SIDE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(sideBarFrameNode, nullptr);
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(sideBarPattern, nullptr);

    /**
     * @tc.steps: step2. call GetFirstFrameNode function.
     * @tc.expected: step2. get nullptr.
     */
    auto resultNode = sideBarPattern->GetFirstFrameNode(sideBarFrameNode);
    EXPECT_EQ(resultNode, nullptr);

    /**
     * @tc.steps: step3. set a customNode child to sideBar.
     */
    auto viewId = NG::ViewStackProcessor::GetInstance()->ClaimNodeId();
    auto viewIdStr = std::to_string(viewId);
    auto key = NG::ViewStackProcessor::GetInstance()->ProcessViewId(viewIdStr);
    auto customContentNode = NG::CustomNode::CreateCustomNode(viewId, key);
    ASSERT_NE(customContentNode, nullptr);
    sideBarFrameNode->children_.push_back(customContentNode);

    /**
     * @tc.steps: step4. call GetFirstFrameNode function.
     * @tc.expected: step4. get nullptr.
     */
    resultNode = sideBarPattern->GetFirstFrameNode(sideBarFrameNode);
    EXPECT_EQ(resultNode, nullptr);

    /**
     * @tc.steps: step5. set a FrameNode child to childNode.
     */
    sideBarFrameNode->Clean();
    auto childID = ElementRegister::GetInstance()->MakeUniqueId();
    auto contentNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::COLUMN_ETS_TAG,
        childID, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(contentNode, nullptr);
    customContentNode->children_.push_back(contentNode);
    sideBarFrameNode->children_.push_back(customContentNode);

    /**
     * @tc.steps: step6. call GetFirstFrameNode function.
     * @tc.expected: step6. get child node of child node.
     */
    resultNode = sideBarPattern->GetFirstFrameNode(sideBarFrameNode);
    ASSERT_NE(resultNode, nullptr);
    EXPECT_EQ(resultNode->GetId(), childID);
}

/**
 * @tc.name: SideBarPatternTestNg071
 * @tc.desc: Test SideBar GetSideBarNodeOrFirstChild with sideBarNode is customNode.
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg071, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar with few child node, get pattern.
     */
    auto sideBarFrameNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::SIDE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(sideBarFrameNode, nullptr);
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(sideBarPattern, nullptr);
    auto contentNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(contentNode, nullptr);
    auto viewId = NG::ViewStackProcessor::GetInstance()->ClaimNodeId();
    auto viewIdStr = std::to_string(viewId);
    auto key = NG::ViewStackProcessor::GetInstance()->ProcessViewId(viewIdStr);
    auto customSideBarNode = NG::CustomNode::CreateCustomNode(viewId, key);
    ASSERT_NE(customSideBarNode, nullptr);
    auto dividerNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::DIVIDER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<DividerPattern>());
    ASSERT_NE(dividerNode, nullptr);
    auto controlBtnNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(controlBtnNode, nullptr);
    sideBarFrameNode->children_.push_back(contentNode);
    sideBarFrameNode->children_.push_back(customSideBarNode);

    /**
     * @tc.steps: step2. call GetSideBarNodeOrFirstChild function.
     * @tc.expected: step2. get nullptr.
     */
    auto resultNode = sideBarPattern->GetSideBarNodeOrFirstChild();
    EXPECT_EQ(resultNode, nullptr);

    /**
     * @tc.steps: step3. set a empty customNode child to sideBar.
     */
    sideBarFrameNode->children_.push_back(dividerNode);
    sideBarFrameNode->children_.push_back(controlBtnNode);

    /**
     * @tc.steps: step4. call GetSideBarNodeOrFirstChild function.
     * @tc.expected: step4. get nullptr.
     */
    resultNode = sideBarPattern->GetSideBarNodeOrFirstChild();
    EXPECT_EQ(resultNode, nullptr);

    /**
     * @tc.steps: step5. set a child node to customNode.
     */
    auto childID = ElementRegister::GetInstance()->MakeUniqueId();
    auto sideBarChildNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::COLUMN_ETS_TAG,
        childID, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    sideBarFrameNode->Clean();
    customSideBarNode->children_.push_back(sideBarChildNode);
    sideBarFrameNode->children_.push_back(contentNode);
    sideBarFrameNode->children_.push_back(customSideBarNode);
    sideBarFrameNode->children_.push_back(dividerNode);
    sideBarFrameNode->children_.push_back(controlBtnNode);

    /**
     * @tc.steps: step6. call GetSideBarNodeOrFirstChild function.
     * @tc.expected: step6. get child node of sideBar node.
     */
    resultNode = sideBarPattern->GetSideBarNodeOrFirstChild();
    ASSERT_NE(resultNode, nullptr);
    EXPECT_EQ(resultNode->GetId(), childID);
}

/**
 * @tc.name: SideBarPatternTestNg072
 * @tc.desc: Test SideBar GetControlButtonNode with controlButtonNode is customNode.
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg072, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar with no child node, get pattern.
     */
    auto sideBarFrameNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::SIDE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(sideBarFrameNode, nullptr);
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(sideBarPattern, nullptr);

    /**
     * @tc.steps: step2. call GetControlButtonNode function.
     * @tc.expected: step2. get nullptr.
     */
    auto resultNode = sideBarPattern->GetControlButtonNode();
    EXPECT_EQ(resultNode, nullptr);

    /**
     * @tc.steps: step3. set controlButtonNode without BUTTON_ETS_TAG.
     */
    auto contentNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(contentNode, nullptr);
    auto sideBarNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(sideBarNode, nullptr);
    auto dividerNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::DIVIDER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<DividerPattern>());
    ASSERT_NE(dividerNode, nullptr);
    auto errorControlBtnNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(errorControlBtnNode, nullptr);
    sideBarFrameNode->children_.push_back(contentNode);
    sideBarFrameNode->children_.push_back(sideBarNode);
    sideBarFrameNode->children_.push_back(dividerNode);
    sideBarFrameNode->children_.push_back(errorControlBtnNode);

    /**
     * @tc.steps: step4. call GetControlButtonNode function.
     * @tc.expected: step4. get nullptr.
     */
    resultNode = sideBarPattern->GetControlButtonNode();
    EXPECT_EQ(resultNode, nullptr);

    /**
     * @tc.steps: step5. set controlButtonNode which is customNode.
     */
    auto viewId = NG::ViewStackProcessor::GetInstance()->ClaimNodeId();
    auto viewIdStr = std::to_string(viewId);
    auto key = NG::ViewStackProcessor::GetInstance()->ProcessViewId(viewIdStr);
    auto customControlBtnNode = NG::CustomNode::CreateCustomNode(viewId, key);
    ASSERT_NE(customControlBtnNode, nullptr);
    sideBarFrameNode->Clean();
    sideBarFrameNode->children_.push_back(contentNode);
    sideBarFrameNode->children_.push_back(sideBarNode);
    sideBarFrameNode->children_.push_back(dividerNode);
    sideBarFrameNode->children_.push_back(customControlBtnNode);

    /**
     * @tc.steps: step6. call GetControlButtonNode function.
     * @tc.expected: step6. get nullptr.
     */
    resultNode = sideBarPattern->GetControlButtonNode();
    EXPECT_EQ(resultNode, nullptr);

    /**
     * @tc.steps: step7. set controlButtonNode.
     */
    auto childID = ElementRegister::GetInstance()->MakeUniqueId();
    auto controlBtnNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::BUTTON_ETS_TAG,
        childID, AceType::MakeRefPtr<ButtonPattern>());
    sideBarFrameNode->Clean();
    sideBarFrameNode->children_.push_back(contentNode);
    sideBarFrameNode->children_.push_back(sideBarNode);
    sideBarFrameNode->children_.push_back(dividerNode);
    sideBarFrameNode->children_.push_back(controlBtnNode);

    /**
     * @tc.steps: step8. call GetControlButtonNode function.
     * @tc.expected: step8. get controlButtonNode.
     */
    resultNode = sideBarPattern->GetControlButtonNode();
    ASSERT_NE(resultNode, nullptr);
    EXPECT_EQ(resultNode->GetId(), childID);
}

/**
 * @tc.name: SideBarPatternTestNg073
 * @tc.desc: Test SideBar GetControlImageNode with controlButtonNode is customNode.
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg073, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar with no child node, get pattern.
     */
    auto sideBarFrameNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::SIDE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(sideBarFrameNode, nullptr);
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(sideBarPattern, nullptr);

    /**
     * @tc.steps: step2. call GetControlImageNode function.
     * @tc.expected: step2. get nullptr.
     */
    auto resultNode = sideBarPattern->GetControlImageNode();
    EXPECT_EQ(resultNode, nullptr);

    /**
     * @tc.steps: step3. set controlButtonNode without BUTTON_ETS_TAG.
     */
    auto contentNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(contentNode, nullptr);
    auto sideBarNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(sideBarNode, nullptr);
    auto dividerNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::DIVIDER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<DividerPattern>());
    ASSERT_NE(dividerNode, nullptr);
    auto errorControlBtnNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(errorControlBtnNode, nullptr);
    sideBarFrameNode->children_.push_back(contentNode);
    sideBarFrameNode->children_.push_back(sideBarNode);
    sideBarFrameNode->children_.push_back(dividerNode);
    sideBarFrameNode->children_.push_back(errorControlBtnNode);

    /**
     * @tc.steps: step4. call GetControlImageNode function.
     * @tc.expected: step4. get nullptr.
     */
    resultNode = sideBarPattern->GetControlImageNode();
    EXPECT_EQ(resultNode, nullptr);

    /**
     * @tc.steps: step5. set controlButtonNode which is customNode.
     */
    auto viewId = NG::ViewStackProcessor::GetInstance()->ClaimNodeId();
    auto viewIdStr = std::to_string(viewId);
    auto key = NG::ViewStackProcessor::GetInstance()->ProcessViewId(viewIdStr);
    auto customControlBtnNode = NG::CustomNode::CreateCustomNode(viewId, key);
    ASSERT_NE(customControlBtnNode, nullptr);
    sideBarFrameNode->Clean();
    sideBarFrameNode->children_.push_back(contentNode);
    sideBarFrameNode->children_.push_back(sideBarNode);
    sideBarFrameNode->children_.push_back(dividerNode);
    sideBarFrameNode->children_.push_back(customControlBtnNode);

    /**
     * @tc.steps: step6. call GetControlImageNode function.
     * @tc.expected: step6. get nullptr.
     */
    resultNode = sideBarPattern->GetControlImageNode();
    EXPECT_EQ(resultNode, nullptr);
}

/**
 * @tc.name: SideBarPatternTestNg074
 * @tc.desc: Test SideBar GetControlImageNode.
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg074, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar, get pattern.
     */
    auto sideBarFrameNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::SIDE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(sideBarFrameNode, nullptr);
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(sideBarPattern, nullptr);
    auto controlBtnNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(controlBtnNode, nullptr);
    auto contentNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(contentNode, nullptr);
    auto sideBarNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(sideBarNode, nullptr);
    auto dividerNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::DIVIDER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<DividerPattern>());
    ASSERT_NE(dividerNode, nullptr);
    sideBarFrameNode->children_.push_back(contentNode);
    sideBarFrameNode->children_.push_back(sideBarNode);
    sideBarFrameNode->children_.push_back(dividerNode);
    sideBarFrameNode->children_.push_back(controlBtnNode);

    /**
     * @tc.steps: step2. call GetControlImageNode function.
     * @tc.expected: step2. get nullptr.
     */
    auto resultNode = sideBarPattern->GetControlImageNode();
    EXPECT_EQ(resultNode, nullptr);

    /**
     * @tc.steps: step3. set controlImageNode without IMAGE_ETS_TAG and call GetControlImageNode function.
     * @tc.expected: step3. get nullptr.
     */
    auto errorControlBtnNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(errorControlBtnNode, nullptr);
    controlBtnNode->children_.push_back(errorControlBtnNode);
    resultNode = sideBarPattern->GetControlImageNode();
    EXPECT_EQ(resultNode, nullptr);

    /**
     * @tc.steps: step4. set controlImageNode which is customNode and call GetControlImageNode function.
     * @tc.expected: step4. get nullptr.
     */
    auto viewId = NG::ViewStackProcessor::GetInstance()->ClaimNodeId();
    auto viewIdStr = std::to_string(viewId);
    auto key = NG::ViewStackProcessor::GetInstance()->ProcessViewId(viewIdStr);
    auto customControlBtnNode = NG::CustomNode::CreateCustomNode(viewId, key);
    ASSERT_NE(customControlBtnNode, nullptr);
    controlBtnNode->Clean();
    controlBtnNode->children_.push_back(customControlBtnNode);
    resultNode = sideBarPattern->GetControlImageNode();
    EXPECT_EQ(resultNode, nullptr);

    /**
     * @tc.steps: step5. set controlImageNode and call GetControlImageNode function.
     * @tc.expected: step5. get controlImageNode.
     */
    auto childID = ElementRegister::GetInstance()->MakeUniqueId();
    auto controlImageNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::IMAGE_ETS_TAG,
        childID, AceType::MakeRefPtr<ImagePattern>());
    controlBtnNode->Clean();
    controlBtnNode->children_.push_back(controlImageNode);
    resultNode = sideBarPattern->GetControlImageNode();
    ASSERT_NE(resultNode, nullptr);
    EXPECT_EQ(resultNode->GetId(), childID);
}

/**
 * @tc.name: SideBarPatternTestNg075
 * @tc.desc: Test SideBar GetDividerNode.
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg075, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar with no child node, get pattern.
     */
    auto sideBarFrameNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::SIDE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(sideBarFrameNode, nullptr);
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(sideBarPattern, nullptr);

    /**
     * @tc.steps: step2. call GetDividerNode function.
     * @tc.expected: step2. get nullptr.
     */
    auto resultNode = sideBarPattern->GetDividerNode();
    EXPECT_EQ(resultNode, nullptr);

    /**
     * @tc.steps: step3. set dividerNode without DIVIDER_ETS_TAG.
     */
    auto contentNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(contentNode, nullptr);
    auto sideBarNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(sideBarNode, nullptr);
    auto errorDividerNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(errorDividerNode, nullptr);
    auto controlBtnNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(controlBtnNode, nullptr);
    sideBarFrameNode->children_.push_back(contentNode);
    sideBarFrameNode->children_.push_back(sideBarNode);
    sideBarFrameNode->children_.push_back(errorDividerNode);
    sideBarFrameNode->children_.push_back(controlBtnNode);

    /**
     * @tc.steps: step4. call GetDividerNode function.
     * @tc.expected: step4. get nullptr.
     */
    resultNode = sideBarPattern->GetDividerNode();
    EXPECT_EQ(resultNode, nullptr);

    /**
     * @tc.steps: step5. set dividerNode which is customNode.
     */
    auto viewId = NG::ViewStackProcessor::GetInstance()->ClaimNodeId();
    auto viewIdStr = std::to_string(viewId);
    auto key = NG::ViewStackProcessor::GetInstance()->ProcessViewId(viewIdStr);
    auto customDividerNode = NG::CustomNode::CreateCustomNode(viewId, key);
    ASSERT_NE(customDividerNode, nullptr);
    sideBarFrameNode->Clean();
    sideBarFrameNode->children_.push_back(contentNode);
    sideBarFrameNode->children_.push_back(sideBarNode);
    sideBarFrameNode->children_.push_back(customDividerNode);
    sideBarFrameNode->children_.push_back(controlBtnNode);

    /**
     * @tc.steps: step6. call GetDividerNode function.
     * @tc.expected: step6. get nullptr.
     */
    resultNode = sideBarPattern->GetDividerNode();
    EXPECT_EQ(resultNode, nullptr);

    /**
     * @tc.steps: step7. set dividerNode.
     */
    auto childID = ElementRegister::GetInstance()->MakeUniqueId();
    auto dividerNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::DIVIDER_ETS_TAG,
        childID, AceType::MakeRefPtr<DividerPattern>());
    sideBarFrameNode->Clean();
    sideBarFrameNode->children_.push_back(contentNode);
    sideBarFrameNode->children_.push_back(sideBarNode);
    sideBarFrameNode->children_.push_back(dividerNode);
    sideBarFrameNode->children_.push_back(controlBtnNode);

    /**
     * @tc.steps: step8. call GetDividerNode function.
     * @tc.expected: step8. get dividerNode.
     */
    resultNode = sideBarPattern->GetDividerNode();
    ASSERT_NE(resultNode, nullptr);
    EXPECT_EQ(resultNode->GetId(), childID);
}

/**
 * @tc.name: SideBarPatternTestNg076
 * @tc.desc: Test SideBar OnHover.
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg076, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar, get pattern and layoutProperty.
     */
    auto sideBarFrameNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::SIDE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(sideBarFrameNode, nullptr);
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(sideBarPattern, nullptr);
    auto sideBarLayoutProperty = sideBarFrameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(sideBarLayoutProperty, nullptr);
    auto contentNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(contentNode, nullptr);
    auto sideBarNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(sideBarNode, nullptr);
    auto dividerNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::DIVIDER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<DividerPattern>());
    ASSERT_NE(dividerNode, nullptr);
    auto controlBtnNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(controlBtnNode, nullptr);
    sideBarFrameNode->children_.push_back(contentNode);
    sideBarFrameNode->children_.push_back(sideBarNode);
    sideBarFrameNode->children_.push_back(dividerNode);
    sideBarFrameNode->children_.push_back(controlBtnNode);

    /**
     * @tc.steps: step2. call OnHover function with illegal and legal property.
     * @tc.expected: step2. isDividerDraggable_ is set.
     */
    sideBarPattern->isInDividerDrag_ = true;
    sideBarPattern->OnHover(true);
    sideBarPattern->isInDividerDrag_ = false;
    sideBarLayoutProperty->UpdateDividerStrokeWidth(-DIVIDER_STROKE_WIDTH);
    sideBarLayoutProperty->UpdateMinSideBarWidth(MIN_SIDE_BAR_WIDTH);
    sideBarLayoutProperty->UpdateMaxSideBarWidth(MAX_SIDE_BAR_WIDTH);
    sideBarPattern->OnHover(true);
    EXPECT_FALSE(sideBarPattern->isDividerDraggable_);
    sideBarLayoutProperty->UpdateDividerStrokeWidth(DIVIDER_STROKE_WIDTH);
    sideBarPattern->OnHover(true);
    EXPECT_FALSE(sideBarPattern->isDividerDraggable_);
    sideBarLayoutProperty->UpdateDividerStrokeWidth(-DIVIDER_STROKE_WIDTH);
    sideBarLayoutProperty->UpdateMinSideBarWidth(IMAGE_WIDTH);
    sideBarPattern->OnHover(true);
    EXPECT_FALSE(sideBarPattern->isDividerDraggable_);
    sideBarLayoutProperty->UpdateDividerStrokeWidth(DIVIDER_STROKE_WIDTH);
    sideBarPattern->OnHover(true);
    EXPECT_TRUE(sideBarPattern->isDividerDraggable_);
}

/**
 * @tc.name: SideBarPatternTestNg077
 * @tc.desc: Test SideBar ShowDialogWithNode.
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg077, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar, get pattern.
     */
    auto sideBarFrameNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::SIDE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(sideBarFrameNode, nullptr);
    auto sideBarPattern = sideBarFrameNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(sideBarPattern, nullptr);
    auto contentNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(contentNode, nullptr);
    auto sideBarNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(sideBarNode, nullptr);
    auto dividerNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::DIVIDER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<DividerPattern>());
    ASSERT_NE(dividerNode, nullptr);
    auto controlBtnNode = FrameNode::CreateFrameNode(OHOS::Ace::V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(controlBtnNode, nullptr);
    sideBarFrameNode->children_.push_back(contentNode);
    sideBarFrameNode->children_.push_back(sideBarNode);
    sideBarFrameNode->children_.push_back(dividerNode);
    sideBarFrameNode->children_.push_back(controlBtnNode);

    /**
     * @tc.steps: step2. call ShowDialogWithNode function.
     * @tc.expected: step2. isDialogShow_ is set.
     */
    sideBarPattern->isDialogShow_ = true;
    sideBarPattern->ShowDialogWithNode();
    sideBarPattern->isDialogShow_ = false;
    sideBarPattern->ShowDialogWithNode();
    EXPECT_TRUE(sideBarPattern->isDialogShow_);
}

/**
 * @tc.name: SideBarContainerPaintMethodNg001
 * @tc.desc: Test SideBarContainerPaintMethod ClipPadding
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarContainerPaintMethodNg001, TestSize.Level1)
{
    SideBarContainerPaintMethod sideBarContainerPaintMethod;
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, pickerPaintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    RSCanvas canvas;
    sideBarContainerPaintMethod.needClipPadding_ = false;
    sideBarContainerPaintMethod.ClipPadding(paintWrapper, canvas);
}

/**
 * @tc.name: SideBarContainerPaintMethodNg002
 * @tc.desc: Test SideBarContainerPaintMethod ClipPadding
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarContainerPaintMethodNg002, TestSize.Level1)
{
    SideBarContainerPaintMethod sideBarContainerPaintMethod;
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, pickerPaintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    RSCanvas canvas;
    sideBarContainerPaintMethod.needClipPadding_ = true;
    sideBarContainerPaintMethod.ClipPadding(paintWrapper, canvas);
}

/**
 * @tc.name: SideBarContainerPaintMethodNg003
 * @tc.desc: Test SideBarContainerPaintMethod ClipPadding
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarContainerPaintMethodNg003, TestSize.Level1)
{
    SideBarContainerPaintMethod sideBarContainerPaintMethod;
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    auto renderContext_ = AceType::MakeRefPtr<RenderContext>();
    WeakPtr<RenderContext> renderContext = AceType::WeakClaim(AceType::RawPtr(renderContext_));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, pickerPaintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    RSCanvas canvas;
    sideBarContainerPaintMethod.needClipPadding_ = true;
    sideBarContainerPaintMethod.ClipPadding(paintWrapper, canvas);
}

/**
 * @tc.name: SideBarContainerPattern001
 * @tc.desc: Test SideBarContainerPattern OnUpdateShowSideBar
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarContainerPattern001, TestSize.Level1)
{
    SideBarContainerModelNG sideBarContainerModelInstance;
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    auto sideBarLayoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(sideBarLayoutProperty, nullptr);
    pattern->hasInit_ = false;
    pattern->showSideBar_ = false;
    pattern->sideBarStatus_ = SideBarStatus::AUTO;
    pattern->OnUpdateShowSideBar(sideBarLayoutProperty);
}

/**
 * @tc.name: SideBarContainerPattern002
 * @tc.desc: Test SideBarContainerPattern OnUpdateShowSideBar
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarContainerPattern002, TestSize.Level1)
{
    SideBarContainerModelNG sideBarContainerModelInstance;
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    auto sideBarLayoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(sideBarLayoutProperty, nullptr);
    pattern->hasInit_ = true;
    pattern->showSideBar_ = false;
    pattern->sideBarStatus_ = SideBarStatus::HIDDEN;
    pattern->OnUpdateShowSideBar(sideBarLayoutProperty);
}

/**
 * @tc.name: SideBarContainerPattern003
 * @tc.desc: Test SideBarContainerPattern OnUpdateShowSideBar
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarContainerPattern003, TestSize.Level1)
{
    SideBarContainerModelNG sideBarContainerModelInstance;
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    auto sideBarLayoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(sideBarLayoutProperty, nullptr);
    pattern->hasInit_ = true;
    pattern->showSideBar_ = false;
    pattern->sideBarStatus_ = SideBarStatus::SHOW;
    pattern->OnUpdateShowSideBar(sideBarLayoutProperty);
}
} // namespace OHOS::Ace::NG