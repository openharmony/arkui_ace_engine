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
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_layout_property.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_pattern.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_view.h"
#include "core/components_v2/extensions/extension.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

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
constexpr bool AUTO_HIDE = true;
constexpr SideBarPosition SIDE_BAR_POSITION = SideBarPosition::START;
constexpr Dimension WIDTH = 150.0_vp;
constexpr Dimension HEIGHT = 150.0_vp;
constexpr Dimension LEFT = 50.0_vp;
constexpr Dimension TOP = 50.0_vp;
constexpr float UPDATE_SIDE_BAR_POSITION_VALUE = 1.0f;
constexpr float REAL_SIDE_BAR_WIDTH_VALUE = 1.0f;
constexpr float CURRENT_OFFSET_VALUE = 1.0f;
const std::string SHOW_ICON_STR = "123";
const std::string HIDDEN_ICON_STR = "123";
const std::string SWITCHING_ICON_STR = "123";
} // namespace

class SideBarPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void SideBarPatternTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void SideBarPatternTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
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
    SideBarContainerView::Create();
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
    SideBarContainerView::Create();
    SideBarContainerView::SetSideBarContainerType(SIDE_BAR_CONTAINER_TYPE);
    SideBarContainerView::SetShowSideBar(IS_SHOW);
    SideBarContainerView::SetShowControlButton(SHOW_CONTROL_BUTTON);
    SideBarContainerView::SetSideBarWidth(SIDE_BAR_WIDTH);
    SideBarContainerView::SetMinSideBarWidth(MIN_SIDE_BAR_WIDTH);
    SideBarContainerView::SetMaxSideBarWidth(MAX_SIDE_BAR_WIDTH);
    SideBarContainerView::SetAutoHide(AUTO_HIDE);
    SideBarContainerView::SetSideBarPosition(SIDE_BAR_POSITION);
    SideBarContainerView::SetControlButtonWidth(WIDTH);
    SideBarContainerView::SetControlButtonHeight(HEIGHT);
    SideBarContainerView::SetControlButtonLeft(LEFT);
    SideBarContainerView::SetControlButtonTop(TOP);
    SideBarContainerView::SetControlButtonShowIconStr(SHOW_ICON_STR);
    SideBarContainerView::SetControlButtonHiddenIconStr(HIDDEN_ICON_STR);
    SideBarContainerView::SetControlButtonSwitchingIconStr(SWITCHING_ICON_STR);
    ChangeEvent eventOnChange = [](const bool) {};
    SideBarContainerView::SetOnChange(std::move(eventOnChange));
    SideBarContainerView::MarkNeedInitRealSideBarWidth();
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
    EXPECT_EQ(sideBarLayoutProperty->GetAutoHide(), AUTO_HIDE);
    EXPECT_EQ(sideBarLayoutProperty->GetSideBarPosition(), SIDE_BAR_POSITION);
    EXPECT_EQ(sideBarLayoutProperty->GetControlButtonWidth(), WIDTH);
    EXPECT_EQ(sideBarLayoutProperty->GetControlButtonHeight(), HEIGHT);
    EXPECT_EQ(sideBarLayoutProperty->GetControlButtonLeft(), LEFT);
    EXPECT_EQ(sideBarLayoutProperty->GetControlButtonTop(), TOP);
    EXPECT_EQ(sideBarLayoutProperty->GetControlButtonShowIconStr(), SHOW_ICON_STR);
    EXPECT_EQ(sideBarLayoutProperty->GetControlButtonHiddenIconStr(), HIDDEN_ICON_STR);
    EXPECT_EQ(sideBarLayoutProperty->GetControlButtonSwitchingIconStr(), SWITCHING_ICON_STR);
}

/**
 * @tc.name: SideBarPatternTestNg003
 * @tc.desc: Test SideBar OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg003, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->OnModifyDone();
    SideBarContainerView::SetShowSideBar(true);
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
 * @tc.name: SideBarPatternTestNg006
 * @tc.desc: Test SideBar DoSideBarAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SideBarPatternTestNg, SideBarPatternTestNg006, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->CreateAnimation();
    pattern->DoSideBarAnimation();
    EXPECT_EQ(pattern->showSideBar_, true);
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
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    pattern->AttachToFrameNode(frameNode);
    SideBarContainerView::CreateAndMountControlButton(frameNode);
    pattern->UpdateControlButtonIcon();
    EXPECT_EQ(pattern->sideBarStatus_, SideBarStatus::SHOW);
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
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    pattern->AttachToFrameNode(frameNode);
    stack->Push(frameNode);
    pattern->sideBarStatus_ = SideBarStatus::SHOW;
    SideBarContainerView::SetSideBarPosition(SideBarPosition::START);
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
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    pattern->AttachToFrameNode(frameNode);
    stack->Push(frameNode);
    pattern->sideBarStatus_ = SideBarStatus::HIDDEN;
    SideBarContainerView::SetSideBarPosition(SideBarPosition::END);
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
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    pattern->AttachToFrameNode(frameNode);
    stack->Push(frameNode);
    pattern->sideBarStatus_ = SideBarStatus::SHOW;
    SideBarContainerView::SetSideBarPosition(SideBarPosition::END);
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
    auto pattern = AceType::MakeRefPtr<SideBarContainerPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode("Test", nodeId, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    pattern->AttachToFrameNode(frameNode);
    stack->Push(frameNode);
    SideBarContainerView::SetSideBarPosition(SideBarPosition::START);
    pattern->sideBarStatus_ = SideBarStatus::HIDDEN;
    pattern->UpdateAnimDir();
    EXPECT_EQ(pattern->animDir_, SideBarAnimationDirection::LTR);
}
} // namespace OHOS::Ace::NG
