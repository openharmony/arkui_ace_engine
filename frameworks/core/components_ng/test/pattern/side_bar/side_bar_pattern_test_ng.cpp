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
#include "core/components_ng/pattern/side_bar/side_bar_container_layout_property.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_view.h"
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
} // namespace OHOS::Ace::NG
