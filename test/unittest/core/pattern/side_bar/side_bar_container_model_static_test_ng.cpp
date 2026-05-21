/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_event_hub.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_layout_property.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_model_static.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension TEST_SIDE_BAR_WIDTH = 200.0_vp;
constexpr Dimension TEST_MIN_SIDE_BAR_WIDTH = 100.0_vp;
constexpr Dimension TEST_MAX_SIDE_BAR_WIDTH = 300.0_vp;
constexpr Dimension TEST_CONTROL_BUTTON_WIDTH = 32.0_vp;
constexpr Dimension TEST_CONTROL_BUTTON_HEIGHT = 32.0_vp;
constexpr Dimension TEST_CONTROL_BUTTON_LEFT = 16.0_vp;
constexpr Dimension TEST_CONTROL_BUTTON_TOP = 48.0_vp;
constexpr Dimension TEST_DIVIDER_STROKE_WIDTH = 5.0_vp;
constexpr Dimension TEST_DIVIDER_START_MARGIN = 10.0_vp;
constexpr Dimension TEST_DIVIDER_END_MARGIN = 10.0_vp;
constexpr Dimension TEST_MIN_CONTENT_WIDTH = 360.0_vp;
constexpr Dimension TEST_NEGATIVE_WIDTH = -10.0_vp;
const std::string TEST_ICON_SRC = "icon.png";
const std::string TEST_ICON_SRC_2 = "icon2.png";
const std::string TEST_ICON_SRC_3 = "icon3.png";
} // namespace

class SideBarContainerModelStaticTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    FrameNode* CreateSideBarFrameNode();
    RefPtr<FrameNode> holder_;
};

void SideBarContainerModelStaticTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void SideBarContainerModelStaticTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

FrameNode* SideBarContainerModelStaticTestNg::CreateSideBarFrameNode()
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    holder_ = SideBarContainerModelStatic::CreateFrameNode(nodeId);
    return AceType::RawPtr(holder_);
}

/**
 * @tc.name: SideBarModelStaticCreateFrameNode001
 * @tc.desc: Test CreateFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModelStaticTestNg, SideBarModelStaticCreateFrameNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateFrameNode with valid nodeId.
     * @tc.expected: step1. frameNode is created with SideBarContainerPattern.
     */
    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = SideBarContainerModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);
}

/**
 * @tc.name: SideBarModelStaticCreateFrameNode002
 * @tc.desc: Test CreateFrameNode with same nodeId returns same node
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModelStaticTestNg, SideBarModelStaticCreateFrameNode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateFrameNode twice with same nodeId.
     * @tc.expected: step1. returns same frameNode instance.
     */
    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode1 = SideBarContainerModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode1, nullptr);
    auto frameNode2 = SideBarContainerModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode2, nullptr);
    EXPECT_EQ(frameNode1, frameNode2);
}

/**
 * @tc.name: SideBarModelStaticSetSideBarContainerType001
 * @tc.desc: Test SetSideBarContainerType with value and nullopt
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModelStaticTestNg, SideBarModelStaticSetSideBarContainerType001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = CreateSideBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. call SetSideBarContainerType with EMBED value.
     * @tc.expected: step2. property is set to EMBED.
     */
    SideBarContainerModelStatic::SetSideBarContainerType(frameNode, SideBarContainerType::EMBED);
    EXPECT_EQ(layoutProperty->GetSideBarContainerType(), SideBarContainerType::EMBED);

    /**
     * @tc.steps: step3. call SetSideBarContainerType with OVERLAY value.
     * @tc.expected: step3. property is set to OVERLAY.
     */
    SideBarContainerModelStatic::SetSideBarContainerType(frameNode, SideBarContainerType::OVERLAY);
    EXPECT_EQ(layoutProperty->GetSideBarContainerType(), SideBarContainerType::OVERLAY);

    /**
     * @tc.steps: step4. call SetSideBarContainerType with nullopt.
     * @tc.expected: step4. property is reset.
     */
    SideBarContainerModelStatic::SetSideBarContainerType(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetSideBarContainerType().has_value());
}

/**
 * @tc.name: SideBarModelStaticSetSideBarWidth001
 * @tc.desc: Test SetSideBarWidth with value and nullopt
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModelStaticTestNg, SideBarModelStaticSetSideBarWidth001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = CreateSideBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. call SetSideBarWidth with value.
     * @tc.expected: step2. property is set.
     */
    SideBarContainerModelStatic::SetSideBarWidth(frameNode, TEST_SIDE_BAR_WIDTH);
    EXPECT_EQ(layoutProperty->GetSideBarWidth(), TEST_SIDE_BAR_WIDTH);

    /**
     * @tc.steps: step3. call SetSideBarWidth with nullopt.
     * @tc.expected: step3. property is reset.
     */
    SideBarContainerModelStatic::SetSideBarWidth(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetSideBarWidth().has_value());
}

/**
 * @tc.name: SideBarModelStaticSetSideBarWidth002
 * @tc.desc: Test SetSideBarWidth with null frameNode
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModelStaticTestNg, SideBarModelStaticSetSideBarWidth002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call SetSideBarWidth with null frameNode.
     * @tc.expected: step1. no crash.
     */
    SideBarContainerModelStatic::SetSideBarWidth(nullptr, TEST_SIDE_BAR_WIDTH);
    SideBarContainerModelStatic::SetSideBarWidth(nullptr, std::nullopt);
}

/**
 * @tc.name: SideBarModelStaticSetSideBarWidth003
 * @tc.desc: Test SetSideBarWidth blocked by double bind
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModelStaticTestNg, SideBarModelStaticSetSideBarWidth003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode, set initial width.
     */
    auto frameNode = CreateSideBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SideBarContainerModelStatic::SetSideBarWidth(frameNode, TEST_SIDE_BAR_WIDTH);
    EXPECT_EQ(layoutProperty->GetSideBarWidth(), TEST_SIDE_BAR_WIDTH);

    /**
     * @tc.steps: step2. set double bind and drag state, then call SetSideBarWidth.
     * @tc.expected: step2. width not changed.
     */
    SideBarContainerModelStatic::sideBarWidthDoubleBind_ = true;
    pattern->isInDividerDrag_ = true;
    SideBarContainerModelStatic::SetSideBarWidth(frameNode, TEST_MIN_SIDE_BAR_WIDTH);
    EXPECT_EQ(layoutProperty->GetSideBarWidth(), TEST_SIDE_BAR_WIDTH);
    SideBarContainerModelStatic::sideBarWidthDoubleBind_ = false;
    pattern->isInDividerDrag_ = false;
}

/**
 * @tc.name: SideBarModelStaticSetMinSideBarWidth001
 * @tc.desc: Test SetMinSideBarWidth with value and nullopt
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModelStaticTestNg, SideBarModelStaticSetMinSideBarWidth001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = CreateSideBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. call SetMinSideBarWidth with value.
     * @tc.expected: step2. property is set.
     */
    SideBarContainerModelStatic::SetMinSideBarWidth(frameNode, TEST_MIN_SIDE_BAR_WIDTH);
    EXPECT_EQ(layoutProperty->GetMinSideBarWidth(), TEST_MIN_SIDE_BAR_WIDTH);

    /**
     * @tc.steps: step3. call SetMinSideBarWidth with nullopt.
     * @tc.expected: step3. property is reset.
     */
    SideBarContainerModelStatic::SetMinSideBarWidth(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetMinSideBarWidth().has_value());
}

/**
 * @tc.name: SideBarModelStaticSetMinSideBarWidth002
 * @tc.desc: Test SetMinSideBarWidth with null frameNode and double bind block
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModelStaticTestNg, SideBarModelStaticSetMinSideBarWidth002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call SetMinSideBarWidth with null frameNode.
     * @tc.expected: step1. no crash.
     */
    SideBarContainerModelStatic::SetMinSideBarWidth(nullptr, TEST_MIN_SIDE_BAR_WIDTH);

    /**
     * @tc.steps: step2. create frameNode, set double bind and drag state.
     * @tc.expected: step2. width not changed.
     */
    auto frameNode = CreateSideBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SideBarContainerModelStatic::SetMinSideBarWidth(frameNode, TEST_MIN_SIDE_BAR_WIDTH);
    EXPECT_EQ(layoutProperty->GetMinSideBarWidth(), TEST_MIN_SIDE_BAR_WIDTH);

    SideBarContainerModelStatic::sideBarWidthDoubleBind_ = true;
    pattern->isInDividerDrag_ = true;
    SideBarContainerModelStatic::SetMinSideBarWidth(frameNode, TEST_MAX_SIDE_BAR_WIDTH);
    EXPECT_EQ(layoutProperty->GetMinSideBarWidth(), TEST_MIN_SIDE_BAR_WIDTH);
    SideBarContainerModelStatic::sideBarWidthDoubleBind_ = false;
    pattern->isInDividerDrag_ = false;
}

/**
 * @tc.name: SideBarModelStaticSetMaxSideBarWidth001
 * @tc.desc: Test SetMaxSideBarWidth with value and nullopt
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModelStaticTestNg, SideBarModelStaticSetMaxSideBarWidth001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = CreateSideBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. call SetMaxSideBarWidth with value.
     * @tc.expected: step2. property is set.
     */
    SideBarContainerModelStatic::SetMaxSideBarWidth(frameNode, TEST_MAX_SIDE_BAR_WIDTH);
    EXPECT_EQ(layoutProperty->GetMaxSideBarWidth(), TEST_MAX_SIDE_BAR_WIDTH);

    /**
     * @tc.steps: step3. call SetMaxSideBarWidth with nullopt.
     * @tc.expected: step3. property is reset.
     */
    SideBarContainerModelStatic::SetMaxSideBarWidth(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetMaxSideBarWidth().has_value());
}

/**
 * @tc.name: SideBarModelStaticSetMaxSideBarWidth002
 * @tc.desc: Test SetMaxSideBarWidth with null frameNode and double bind block
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModelStaticTestNg, SideBarModelStaticSetMaxSideBarWidth002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call SetMaxSideBarWidth with null frameNode.
     * @tc.expected: step1. no crash.
     */
    SideBarContainerModelStatic::SetMaxSideBarWidth(nullptr, TEST_MAX_SIDE_BAR_WIDTH);

    /**
     * @tc.steps: step2. create frameNode, set double bind and drag state.
     * @tc.expected: step2. width not changed.
     */
    auto frameNode = CreateSideBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SideBarContainerModelStatic::SetMaxSideBarWidth(frameNode, TEST_MAX_SIDE_BAR_WIDTH);
    EXPECT_EQ(layoutProperty->GetMaxSideBarWidth(), TEST_MAX_SIDE_BAR_WIDTH);

    SideBarContainerModelStatic::sideBarWidthDoubleBind_ = true;
    pattern->isInDividerDrag_ = true;
    SideBarContainerModelStatic::SetMaxSideBarWidth(frameNode, TEST_MIN_SIDE_BAR_WIDTH);
    EXPECT_EQ(layoutProperty->GetMaxSideBarWidth(), TEST_MAX_SIDE_BAR_WIDTH);
    SideBarContainerModelStatic::sideBarWidthDoubleBind_ = false;
    pattern->isInDividerDrag_ = false;
}

/**
 * @tc.name: SideBarModelStaticSetControlButtonWidth001
 * @tc.desc: Test SetControlButtonWidth with value and nullopt
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModelStaticTestNg, SideBarModelStaticSetControlButtonWidth001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = CreateSideBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. call SetControlButtonWidth with value.
     * @tc.expected: step2. property is set.
     */
    SideBarContainerModelStatic::SetControlButtonWidth(frameNode, TEST_CONTROL_BUTTON_WIDTH);
    EXPECT_EQ(layoutProperty->GetControlButtonWidth(), TEST_CONTROL_BUTTON_WIDTH);

    /**
     * @tc.steps: step3. call SetControlButtonWidth with nullopt.
     * @tc.expected: step3. property is reset.
     */
    SideBarContainerModelStatic::SetControlButtonWidth(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetControlButtonWidth().has_value());
}

/**
 * @tc.name: SideBarModelStaticSetControlButtonHeight001
 * @tc.desc: Test SetControlButtonHeight with value and nullopt
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModelStaticTestNg, SideBarModelStaticSetControlButtonHeight001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = CreateSideBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. call SetControlButtonHeight with value.
     * @tc.expected: step2. property is set.
     */
    SideBarContainerModelStatic::SetControlButtonHeight(frameNode, TEST_CONTROL_BUTTON_HEIGHT);
    EXPECT_EQ(layoutProperty->GetControlButtonHeight(), TEST_CONTROL_BUTTON_HEIGHT);

    /**
     * @tc.steps: step3. call SetControlButtonHeight with nullopt.
     * @tc.expected: step3. property is reset.
     */
    SideBarContainerModelStatic::SetControlButtonHeight(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetControlButtonHeight().has_value());
}

/**
 * @tc.name: SideBarModelStaticSetControlButtonPosition001
 * @tc.desc: Test SetControlButtonLeft and SetControlButtonTop
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModelStaticTestNg, SideBarModelStaticSetControlButtonPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = CreateSideBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. call SetControlButtonLeft and SetControlButtonTop.
     * @tc.expected: step2. properties are set.
     */
    SideBarContainerModelStatic::SetControlButtonLeft(frameNode, TEST_CONTROL_BUTTON_LEFT);
    EXPECT_EQ(layoutProperty->GetControlButtonLeft(), TEST_CONTROL_BUTTON_LEFT);

    SideBarContainerModelStatic::SetControlButtonTop(frameNode, TEST_CONTROL_BUTTON_TOP);
    EXPECT_EQ(layoutProperty->GetControlButtonTop(), TEST_CONTROL_BUTTON_TOP);
}

/**
 * @tc.name: SideBarModelStaticSetControlButtonIconInfo001
 * @tc.desc: Test SetControlButtonShowIconInfo with valid and empty icon
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModelStaticTestNg, SideBarModelStaticSetControlButtonIconInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = CreateSideBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. call SetControlButtonShowIconInfo with valid icon src.
     * @tc.expected: step2. property is set with valid src.
     */
    SideBarContainerModelStatic::SetControlButtonShowIconInfo(frameNode, TEST_ICON_SRC, false, nullptr);
    EXPECT_EQ(layoutProperty->GetControlButtonShowIconInfo()->GetSrc(), TEST_ICON_SRC);

    /**
     * @tc.steps: step3. call SetControlButtonShowIconInfo with empty string.
     * @tc.expected: step3. property is overwritten with empty src.
     */
    SideBarContainerModelStatic::SetControlButtonShowIconInfo(frameNode, "", false, nullptr);
    EXPECT_EQ(layoutProperty->GetControlButtonShowIconInfo()->GetSrc(), "");
}

/**
 * @tc.name: SideBarModelStaticSetControlButtonIconInfo002
 * @tc.desc: Test SetControlButtonHiddenIconInfo with valid and empty icon
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModelStaticTestNg, SideBarModelStaticSetControlButtonIconInfo002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = CreateSideBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. call SetControlButtonHiddenIconInfo with valid icon src.
     * @tc.expected: step2. property is set with valid src.
     */
    SideBarContainerModelStatic::SetControlButtonHiddenIconInfo(frameNode, TEST_ICON_SRC_2, false, nullptr);
    EXPECT_EQ(layoutProperty->GetControlButtonHiddenIconInfo()->GetSrc(), TEST_ICON_SRC_2);

    /**
     * @tc.steps: step3. call SetControlButtonHiddenIconInfo with empty string.
     * @tc.expected: step3. property is overwritten with empty src.
     */
    SideBarContainerModelStatic::SetControlButtonHiddenIconInfo(frameNode, "", false, nullptr);
    EXPECT_EQ(layoutProperty->GetControlButtonHiddenIconInfo()->GetSrc(), "");
}

/**
 * @tc.name: SideBarModelStaticSetControlButtonIconInfo003
 * @tc.desc: Test SetControlButtonSwitchingIconInfo with valid and empty icon
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModelStaticTestNg, SideBarModelStaticSetControlButtonIconInfo003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = CreateSideBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. call SetControlButtonSwitchingIconInfo with valid icon src.
     * @tc.expected: step2. property is set with valid src.
     */
    SideBarContainerModelStatic::SetControlButtonSwitchingIconInfo(frameNode, TEST_ICON_SRC_3, false, nullptr);
    EXPECT_EQ(layoutProperty->GetControlButtonSwitchingIconInfo()->GetSrc(), TEST_ICON_SRC_3);

    /**
     * @tc.steps: step3. call SetControlButtonSwitchingIconInfo with empty string.
     * @tc.expected: step3. property is overwritten with empty src.
     */
    SideBarContainerModelStatic::SetControlButtonSwitchingIconInfo(frameNode, "", false, nullptr);
    EXPECT_EQ(layoutProperty->GetControlButtonSwitchingIconInfo()->GetSrc(), "");
}

/**
 * @tc.name: SideBarModelStaticSetShowControlButton001
 * @tc.desc: Test SetShowControlButton
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModelStaticTestNg, SideBarModelStaticSetShowControlButton001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = CreateSideBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. call SetShowControlButton with true and false.
     * @tc.expected: step2. property is set accordingly.
     */
    SideBarContainerModelStatic::SetShowControlButton(frameNode, false);
    EXPECT_EQ(layoutProperty->GetShowControlButton(), false);

    SideBarContainerModelStatic::SetShowControlButton(frameNode, true);
    EXPECT_EQ(layoutProperty->GetShowControlButton(), true);
}

/**
 * @tc.name: SideBarModelStaticSetShowSideBarWithGesture001
 * @tc.desc: Test SetShowSideBarWithGesture
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModelStaticTestNg, SideBarModelStaticSetShowSideBarWithGesture001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = CreateSideBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. call SetShowSideBarWithGesture with true and false.
     * @tc.expected: step2. property is set accordingly.
     */
    SideBarContainerModelStatic::SetShowSideBarWithGesture(frameNode, true);
    EXPECT_EQ(layoutProperty->GetShowSideBarWithGesture(), true);

    SideBarContainerModelStatic::SetShowSideBarWithGesture(frameNode, false);
    EXPECT_EQ(layoutProperty->GetShowSideBarWithGesture(), false);
}

/**
 * @tc.name: SideBarModelStaticSetAutoHide001
 * @tc.desc: Test SetAutoHide
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModelStaticTestNg, SideBarModelStaticSetAutoHide001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = CreateSideBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. call SetAutoHide with true and false.
     * @tc.expected: step2. property is set accordingly.
     */
    SideBarContainerModelStatic::SetAutoHide(frameNode, false);
    EXPECT_EQ(layoutProperty->GetAutoHide(), false);

    SideBarContainerModelStatic::SetAutoHide(frameNode, true);
    EXPECT_EQ(layoutProperty->GetAutoHide(), true);
}

/**
 * @tc.name: SideBarModelStaticSetMinContentWidth001
 * @tc.desc: Test SetMinContentWidth with positive, negative, and nullopt
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModelStaticTestNg, SideBarModelStaticSetMinContentWidth001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = CreateSideBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. call SetMinContentWidth with positive value.
     * @tc.expected: step2. property is set.
     */
    SideBarContainerModelStatic::SetMinContentWidth(frameNode, TEST_MIN_CONTENT_WIDTH);
    EXPECT_EQ(layoutProperty->GetMinContentWidth(), TEST_MIN_CONTENT_WIDTH);

    /**
     * @tc.steps: step3. call SetMinContentWidth with negative value.
     * @tc.expected: step3. property is set to default (0.0_vp).
     */
    SideBarContainerModelStatic::SetMinContentWidth(frameNode, TEST_NEGATIVE_WIDTH);
    EXPECT_EQ(layoutProperty->GetMinContentWidth(), Dimension(360.0_vp));

    /**
     * @tc.steps: step4. call SetMinContentWidth with nullopt.
     * @tc.expected: step4. property is reset.
     */
    SideBarContainerModelStatic::SetMinContentWidth(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetMinContentWidth().has_value());
}

/**
 * @tc.name: SideBarModelStaticSetSideBarPosition001
 * @tc.desc: Test SetSideBarPosition with value and nullopt
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModelStaticTestNg, SideBarModelStaticSetSideBarPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = CreateSideBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. call SetSideBarPosition with START.
     * @tc.expected: step2. property is set to START.
     */
    SideBarContainerModelStatic::SetSideBarPosition(frameNode, SideBarPosition::START);
    EXPECT_EQ(layoutProperty->GetSideBarPosition(), SideBarPosition::START);

    /**
     * @tc.steps: step3. call SetSideBarPosition with END.
     * @tc.expected: step3. property is set to END.
     */
    SideBarContainerModelStatic::SetSideBarPosition(frameNode, SideBarPosition::END);
    EXPECT_EQ(layoutProperty->GetSideBarPosition(), SideBarPosition::END);

    /**
     * @tc.steps: step4. call SetSideBarPosition with nullopt.
     * @tc.expected: step4. property is reset.
     */
    SideBarContainerModelStatic::SetSideBarPosition(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetSideBarPosition().has_value());
}

/**
 * @tc.name: SideBarModelStaticSetShowSideBar001
 * @tc.desc: Test SetShowSideBar
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModelStaticTestNg, SideBarModelStaticSetShowSideBar001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = CreateSideBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. call SetShowSideBar with false and true.
     * @tc.expected: step2. property is set accordingly.
     */
    SideBarContainerModelStatic::SetShowSideBar(frameNode, false);
    EXPECT_EQ(layoutProperty->GetShowSideBar(), false);

    SideBarContainerModelStatic::SetShowSideBar(frameNode, true);
    EXPECT_EQ(layoutProperty->GetShowSideBar(), true);
}

/**
 * @tc.name: SideBarModelStaticSetDividerStrokeWidth001
 * @tc.desc: Test SetDividerStrokeWidth with value and nullopt
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModelStaticTestNg, SideBarModelStaticSetDividerStrokeWidth001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = CreateSideBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. call SetDividerStrokeWidth with value.
     * @tc.expected: step2. property is set.
     */
    SideBarContainerModelStatic::SetDividerStrokeWidth(frameNode, TEST_DIVIDER_STROKE_WIDTH);
    EXPECT_EQ(layoutProperty->GetDividerStrokeWidth(), TEST_DIVIDER_STROKE_WIDTH);

    /**
     * @tc.steps: step3. call SetDividerStrokeWidth with nullopt.
     * @tc.expected: step3. property is reset.
     */
    SideBarContainerModelStatic::SetDividerStrokeWidth(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetDividerStrokeWidth().has_value());
}

/**
 * @tc.name: SideBarModelStaticSetDividerColor001
 * @tc.desc: Test SetDividerColor
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModelStaticTestNg, SideBarModelStaticSetDividerColor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = CreateSideBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. call SetDividerColor.
     * @tc.expected: step2. property is set.
     */
    SideBarContainerModelStatic::SetDividerColor(frameNode, Color::BLUE);
    EXPECT_EQ(layoutProperty->GetDividerColor(), Color::BLUE);

    SideBarContainerModelStatic::SetDividerColor(frameNode, Color::RED);
    EXPECT_EQ(layoutProperty->GetDividerColor(), Color::RED);
}

/**
 * @tc.name: SideBarModelStaticSetDividerMargin001
 * @tc.desc: Test SetDividerStartMargin and SetDividerEndMargin
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModelStaticTestNg, SideBarModelStaticSetDividerMargin001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = CreateSideBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. call SetDividerStartMargin and SetDividerEndMargin.
     * @tc.expected: step2. properties are set.
     */
    SideBarContainerModelStatic::SetDividerStartMargin(frameNode, TEST_DIVIDER_START_MARGIN);
    EXPECT_EQ(layoutProperty->GetDividerStartMargin(), TEST_DIVIDER_START_MARGIN);

    SideBarContainerModelStatic::SetDividerEndMargin(frameNode, TEST_DIVIDER_END_MARGIN);
    EXPECT_EQ(layoutProperty->GetDividerEndMargin(), TEST_DIVIDER_END_MARGIN);
}

/**
 * @tc.name: SideBarModelStaticSetOnChange001
 * @tc.desc: Test SetOnChange with valid frameNode and null frameNode
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModelStaticTestNg, SideBarModelStaticSetOnChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call SetOnChange with null frameNode.
     * @tc.expected: step1. no crash.
     */
    bool callbackCalled = false;
    SideBarContainerModelStatic::SetOnChange(nullptr, [&callbackCalled](const bool) { callbackCalled = true; });

    /**
     * @tc.steps: step2. create frameNode and call SetOnChange.
     * @tc.expected: step2. callback is set and can be fired.
     */
    auto frameNode = CreateSideBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    SideBarContainerModelStatic::SetOnChange(frameNode, [&callbackCalled](const bool isShow) {
        callbackCalled = isShow;
    });
    auto eventHub = frameNode->GetEventHub<SideBarContainerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireChangeEvent(true);
    EXPECT_TRUE(callbackCalled);
}

/**
 * @tc.name: SideBarModelStaticSetOnChangeEvent001
 * @tc.desc: Test SetOnChangeEvent with valid frameNode and null frameNode
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModelStaticTestNg, SideBarModelStaticSetOnChangeEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call SetOnChangeEvent with null frameNode.
     * @tc.expected: step1. no crash.
     */
    SideBarContainerModelStatic::SetOnChangeEvent(nullptr, [](const bool) {});

    /**
     * @tc.steps: step2. create frameNode and call SetOnChangeEvent.
     * @tc.expected: step2. callback is set and can be fired.
     */
    auto frameNode = CreateSideBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    bool callbackCalled = false;
    SideBarContainerModelStatic::SetOnChangeEvent(frameNode, [&callbackCalled](const bool isShow) {
        callbackCalled = isShow;
    });
    auto eventHub = frameNode->GetEventHub<SideBarContainerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireChangeEvent(true);
    EXPECT_TRUE(callbackCalled);
}

/**
 * @tc.name: SideBarModelStaticSetOnSideBarWidthChangeEvent001
 * @tc.desc: Test SetOnSideBarWidthChangeEvent with valid frameNode and null frameNode
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModelStaticTestNg, SideBarModelStaticSetOnSideBarWidthChangeEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call SetOnSideBarWidthChangeEvent with null frameNode.
     * @tc.expected: step1. no crash.
     */
    SideBarContainerModelStatic::SetOnSideBarWidthChangeEvent(nullptr, [](const Dimension&) {});

    /**
     * @tc.steps: step2. create frameNode and call SetOnSideBarWidthChangeEvent.
     * @tc.expected: step2. callback is set and can be fired.
     */
    auto frameNode = CreateSideBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    Dimension callbackWidth(0.0_vp);
    SideBarContainerModelStatic::SetOnSideBarWidthChangeEvent(frameNode,
        [&callbackWidth](const Dimension& width) { callbackWidth = width; });
    auto eventHub = frameNode->GetEventHub<SideBarContainerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    Dimension testWidth(100.0_vp);
    eventHub->FireSideBarWidthChangeEvent(testWidth);
    EXPECT_EQ(callbackWidth, testWidth);
}

/**
 * @tc.name: SideBarModelStaticResetControlButtonLeft001
 * @tc.desc: Test ResetControlButtonLeft
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModelStaticTestNg, SideBarModelStaticResetControlButtonLeft001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and set ControlButtonLeft.
     */
    auto frameNode = CreateSideBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SideBarContainerModelStatic::SetControlButtonLeft(frameNode, TEST_CONTROL_BUTTON_LEFT);
    EXPECT_EQ(layoutProperty->GetControlButtonLeft(), TEST_CONTROL_BUTTON_LEFT);

    /**
     * @tc.steps: step2. call ResetControlButtonLeft.
     * @tc.expected: step2. property is reset.
     */
    SideBarContainerModelStatic::ResetControlButtonLeft(frameNode);
    EXPECT_FALSE(layoutProperty->GetControlButtonLeft().has_value());
}

/**
 * @tc.name: SideBarModelStaticResetControlButtonIconInfo001
 * @tc.desc: Test ResetControlButtonIconInfo resets all icon info
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModelStaticTestNg, SideBarModelStaticResetControlButtonIconInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and set all icon info.
     */
    auto frameNode = CreateSideBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SideBarContainerModelStatic::SetControlButtonShowIconInfo(frameNode, TEST_ICON_SRC, false, nullptr);
    SideBarContainerModelStatic::SetControlButtonHiddenIconInfo(frameNode, TEST_ICON_SRC_2, false, nullptr);
    SideBarContainerModelStatic::SetControlButtonSwitchingIconInfo(frameNode, TEST_ICON_SRC_3, false, nullptr);

    /**
     * @tc.steps: step2. call ResetControlButtonIconInfo.
     * @tc.expected: step2. all icon info properties are reset.
     */
    SideBarContainerModelStatic::ResetControlButtonIconInfo(frameNode);
    EXPECT_FALSE(layoutProperty->GetControlButtonShowIconInfo().has_value());
    EXPECT_FALSE(layoutProperty->GetControlButtonHiddenIconInfo().has_value());
    EXPECT_FALSE(layoutProperty->GetControlButtonSwitchingIconInfo().has_value());
}

/**
 * @tc.name: SideBarModelStaticMarkNeedInitRealSideBarWidth001
 * @tc.desc: Test MarkNeedInitRealSideBarWidth via SetSideBarWidth
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModelStaticTestNg, SideBarModelStaticMarkNeedInitRealSideBarWidth001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = CreateSideBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. call SetSideBarWidth to trigger MarkNeedInitRealSideBarWidth.
     * @tc.expected: step2. pattern needInitRealSideBarWidth_ is set to true.
     */
    SideBarContainerModelStatic::SetSideBarWidth(frameNode, TEST_SIDE_BAR_WIDTH);
    EXPECT_TRUE(pattern->needInitRealSideBarWidth_);

    /**
     * @tc.steps: step3. call SetMinSideBarWidth to trigger MarkNeedInitRealSideBarWidth.
     * @tc.expected: step3. pattern needInitRealSideBarWidth_ is set to true.
     */
    pattern->needInitRealSideBarWidth_ = false;
    SideBarContainerModelStatic::SetMinSideBarWidth(frameNode, TEST_MIN_SIDE_BAR_WIDTH);
    EXPECT_TRUE(pattern->needInitRealSideBarWidth_);

    /**
     * @tc.steps: step4. call SetMaxSideBarWidth to trigger MarkNeedInitRealSideBarWidth.
     * @tc.expected: step4. pattern needInitRealSideBarWidth_ is set to true.
     */
    pattern->needInitRealSideBarWidth_ = false;
    SideBarContainerModelStatic::SetMaxSideBarWidth(frameNode, TEST_MAX_SIDE_BAR_WIDTH);
    EXPECT_TRUE(pattern->needInitRealSideBarWidth_);
}

/**
 * @tc.name: SideBarModelStaticMarkNeedInitRealSideBarWidth002
 * @tc.desc: Test MarkNeedInitRealSideBarWidth with null frameNode
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModelStaticTestNg, SideBarModelStaticMarkNeedInitRealSideBarWidth002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call SetSideBarWidth with null frameNode, which internally calls MarkNeedInitRealSideBarWidth.
     * @tc.expected: step1. no crash (CHECK_NULL_VOID guards).
     */
    SideBarContainerModelStatic::SetSideBarWidth(nullptr, TEST_SIDE_BAR_WIDTH);
    SideBarContainerModelStatic::SetMinSideBarWidth(nullptr, TEST_MIN_SIDE_BAR_WIDTH);
    SideBarContainerModelStatic::SetMaxSideBarWidth(nullptr, TEST_MAX_SIDE_BAR_WIDTH);
}

/**
 * @tc.name: SideBarModelStaticIsDoubleBindBlock001
 * @tc.desc: Test IsDoubleBindBlock indirectly through SetSideBarWidth/SetMinSideBarWidth/SetMaxSideBarWidth
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModelStaticTestNg, SideBarModelStaticIsDoubleBindBlock001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and set initial values.
     */
    auto frameNode = CreateSideBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SideBarContainerModelStatic::SetSideBarWidth(frameNode, TEST_SIDE_BAR_WIDTH);
    SideBarContainerModelStatic::SetMinSideBarWidth(frameNode, TEST_MIN_SIDE_BAR_WIDTH);
    SideBarContainerModelStatic::SetMaxSideBarWidth(frameNode, TEST_MAX_SIDE_BAR_WIDTH);

    /**
     * @tc.steps: step2. double bind true but not in drag - should allow setting.
     * @tc.expected: step2. property is set.
     */
    SideBarContainerModelStatic::sideBarWidthDoubleBind_ = true;
    pattern->isInDividerDrag_ = false;
    SideBarContainerModelStatic::SetSideBarWidth(frameNode, Dimension(150.0_vp));
    EXPECT_EQ(layoutProperty->GetSideBarWidth(), Dimension(150.0_vp));

    /**
     * @tc.steps: step3. double bind true and in drag - should block.
     * @tc.expected: step3. property not changed.
     */
    pattern->isInDividerDrag_ = true;
    SideBarContainerModelStatic::SetSideBarWidth(frameNode, Dimension(50.0_vp));
    EXPECT_EQ(layoutProperty->GetSideBarWidth(), Dimension(150.0_vp));

    /**
     * @tc.steps: step4. double bind false and in drag - should allow setting.
     * @tc.expected: step4. property is set.
     */
    SideBarContainerModelStatic::sideBarWidthDoubleBind_ = false;
    pattern->isInDividerDrag_ = true;
    SideBarContainerModelStatic::SetSideBarWidth(frameNode, Dimension(50.0_vp));
    EXPECT_EQ(layoutProperty->GetSideBarWidth(), Dimension(50.0_vp));

    SideBarContainerModelStatic::sideBarWidthDoubleBind_ = false;
    pattern->isInDividerDrag_ = false;
}

/**
 * @tc.name: SideBarModelStaticSetSideBarContainerType002
 * @tc.desc: Test SetSideBarContainerType with all enum values
 * @tc.type: FUNC
 */
HWTEST_F(SideBarContainerModelStaticTestNg, SideBarModelStaticSetSideBarContainerType002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = CreateSideBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. call SetSideBarContainerType with all types.
     * @tc.expected: step2. property is set correctly for each type.
     */
    SideBarContainerModelStatic::SetSideBarContainerType(frameNode, SideBarContainerType::EMBED);
    EXPECT_EQ(layoutProperty->GetSideBarContainerType(), SideBarContainerType::EMBED);

    SideBarContainerModelStatic::SetSideBarContainerType(frameNode, SideBarContainerType::OVERLAY);
    EXPECT_EQ(layoutProperty->GetSideBarContainerType(), SideBarContainerType::OVERLAY);

    SideBarContainerModelStatic::SetSideBarContainerType(frameNode, SideBarContainerType::AUTO);
    EXPECT_EQ(layoutProperty->GetSideBarContainerType(), SideBarContainerType::AUTO);
}
} // namespace OHOS::Ace::NG
