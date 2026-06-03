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
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_event_hub.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_layout_property.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_model_ng.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension SIDE_BAR_WIDTH = 200.0_vp;
constexpr Dimension MIN_SIDE_BAR_WIDTH = 100.0_vp;
constexpr Dimension CONTROL_BUTTON_WIDTH = 32.0_vp;
constexpr Dimension CONTROL_BUTTON_HEIGHT = 32.0_vp;
constexpr Dimension CONTROL_BUTTON_LEFT = 16.0_vp;
constexpr Dimension CONTROL_BUTTON_TOP = 48.0_vp;
constexpr Dimension NEGATIVE_WIDTH = -10.0_vp;
const std::string SHOW_ICON_STR = "show.png";
const std::string HIDDEN_ICON_STR = "hidden.png";
const std::string SWITCHING_ICON_STR = "switching.png";
const std::string EMPTY_STR;
} // namespace

class SideBarModelNGTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    RefPtr<FrameNode> CreateSideBarViaModel();
};

void SideBarModelNGTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void SideBarModelNGTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> SideBarModelNGTestNg::CreateSideBarViaModel()
{
    SideBarContainerModelNG model;
    model.Create();
    return AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
}

/**
 * @tc.name: SideBarModelNGCreateStatic001
 * @tc.desc: Test CreateStatic
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGCreateStatic001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CreateStatic.
     * @tc.expected: step1. frameNode is pushed to ViewStack.
     */
    SideBarContainerModelNG::CreateStatic();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);
}

/**
 * @tc.name: SideBarModelNGSetSideBarContainerTypeStatic001
 * @tc.desc: Test SetSideBarContainerTypeStatic
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGSetSideBarContainerTypeStatic001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar via CreateStatic and set type.
     */
    SideBarContainerModelNG::CreateStatic();
    SideBarContainerModelNG::SetSideBarContainerTypeStatic(SideBarContainerType::EMBED);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetSideBarContainerType(), SideBarContainerType::EMBED);
}

/**
 * @tc.name: SideBarModelNGParseAndSetWidthStatic001
 * @tc.desc: Test ParseAndSetWidthStatic with positive and negative widths
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGParseAndSetWidthStatic001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar and set widths via ParseAndSetWidthStatic.
     */
    SideBarContainerModelNG::CreateStatic();
    Dimension positiveWidth = SIDE_BAR_WIDTH;
    SideBarContainerModelNG::ParseAndSetWidthStatic(WidthType::SIDEBAR_WIDTH, positiveWidth);
    SideBarContainerModelNG::ParseAndSetWidthStatic(WidthType::MIN_SIDEBAR_WIDTH, positiveWidth);
    SideBarContainerModelNG::ParseAndSetWidthStatic(WidthType::MAX_SIDEBAR_WIDTH, positiveWidth);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetSideBarWidth(), SIDE_BAR_WIDTH);
    EXPECT_EQ(layoutProperty->GetMinSideBarWidth(), SIDE_BAR_WIDTH);
    EXPECT_EQ(layoutProperty->GetMaxSideBarWidth(), SIDE_BAR_WIDTH);
}

/**
 * @tc.name: SideBarModelNGParseAndSetWidthStatic002
 * @tc.desc: Test ParseAndSetWidthStatic with negative values uses defaults
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGParseAndSetWidthStatic002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar and set negative widths via ParseAndSetWidthStatic.
     * @tc.expected: step1. default widths are used.
     */
    SideBarContainerModelNG::CreateStatic();
    Dimension negativeWidth = NEGATIVE_WIDTH;
    SideBarContainerModelNG::ParseAndSetWidthStatic(WidthType::SIDEBAR_WIDTH, negativeWidth);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_NE(layoutProperty->GetSideBarWidth(), NEGATIVE_WIDTH);
}

/**
 * @tc.name: SideBarModelNGParseAndSetWidthStatic003
 * @tc.desc: Test ParseAndSetWidthStatic with invalid WidthType
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGParseAndSetWidthStatic003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar and set width with invalid type.
     * @tc.expected: step1. no crash, width not changed.
     */
    SideBarContainerModelNG::CreateStatic();
    SideBarContainerModelNG::SetSideBarWidthStatic(SIDE_BAR_WIDTH);
    Dimension width = MIN_SIDE_BAR_WIDTH;
    SideBarContainerModelNG::ParseAndSetWidthStatic(static_cast<WidthType>(-1), width);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetSideBarWidth(), SIDE_BAR_WIDTH);
}

/**
 * @tc.name: SideBarModelNGSetSideBarWidthStatic001
 * @tc.desc: Test SetSideBarWidthStatic
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGSetSideBarWidthStatic001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar and call SetSideBarWidthStatic.
     */
    SideBarContainerModelNG::CreateStatic();
    SideBarContainerModelNG::SetSideBarWidthStatic(SIDE_BAR_WIDTH);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetSideBarWidth(), SIDE_BAR_WIDTH);
}

/**
 * @tc.name: SideBarModelNGSetSideBarWidthStatic002
 * @tc.desc: Test SetSideBarWidthStatic blocked by double bind
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGSetSideBarWidthStatic002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar, set double bind and drag state.
     */
    SideBarContainerModelNG::CreateStatic();
    SideBarContainerModelNG::SetSideBarWidthStatic(SIDE_BAR_WIDTH);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. set double bind + drag state, push frameNode back, call SetSideBarWidthStatic.
     * @tc.expected: step2. width not changed.
     */
    ViewStackProcessor::GetInstance()->Push(frameNode);
    SideBarContainerModelNG::sideBarWidthDoubleBind_ = true;
    pattern->isInDividerDrag_ = true;
    SideBarContainerModelNG::SetSideBarWidthStatic(MIN_SIDE_BAR_WIDTH, true);
    ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(layoutProperty->GetSideBarWidth(), SIDE_BAR_WIDTH);
    SideBarContainerModelNG::sideBarWidthDoubleBind_ = false;
    pattern->isInDividerDrag_ = false;
}

/**
 * @tc.name: SideBarModelNGResetControlButtonStatic001
 * @tc.desc: Test ResetControlButtonStatic resets all control button properties
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGResetControlButtonStatic001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar and set control button properties.
     */
    SideBarContainerModelNG model;
    model.Create();
    model.SetControlButtonWidth(CONTROL_BUTTON_WIDTH);
    model.SetControlButtonHeight(CONTROL_BUTTON_HEIGHT);
    model.SetControlButtonLeft(CONTROL_BUTTON_LEFT);
    model.SetControlButtonTop(CONTROL_BUTTON_TOP);

    /**
     * @tc.steps: step2. call ResetControlButtonStatic.
     * @tc.expected: step2. control button properties are reset to defaults.
     */
    SideBarContainerModelNG::ResetControlButtonStatic();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetControlButtonWidth(), CONTROL_BUTTON_WIDTH);
    EXPECT_EQ(layoutProperty->GetControlButtonHeight(), CONTROL_BUTTON_HEIGHT);
    EXPECT_EQ(layoutProperty->GetControlButtonTop(), CONTROL_BUTTON_TOP);
}

/**
 * @tc.name: SideBarModelNGResetControlButton001
 * @tc.desc: Test ResetControlButton resets all control button properties
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGResetControlButton001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar and set control button properties.
     */
    SideBarContainerModelNG model;
    model.Create();
    model.SetControlButtonWidth(CONTROL_BUTTON_WIDTH);
    model.SetControlButtonHeight(CONTROL_BUTTON_HEIGHT);
    model.SetControlButtonLeft(CONTROL_BUTTON_LEFT);
    model.SetControlButtonTop(CONTROL_BUTTON_TOP);
    model.SetControlButtonShowIconInfo(SHOW_ICON_STR, false, nullptr);
    model.SetControlButtonHiddenIconInfo(HIDDEN_ICON_STR, false, nullptr);
    model.SetControlButtonSwitchingIconInfo(SWITCHING_ICON_STR, false, nullptr);

    /**
     * @tc.steps: step2. call ResetControlButton.
     * @tc.expected: step2. properties reset to defaults.
     */
    model.ResetControlButton();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetControlButtonWidth(), CONTROL_BUTTON_WIDTH);
    EXPECT_EQ(layoutProperty->GetControlButtonHeight(), CONTROL_BUTTON_HEIGHT);
    EXPECT_EQ(layoutProperty->GetControlButtonTop(), CONTROL_BUTTON_TOP);
}

/**
 * @tc.name: SideBarModelNGResetControlButtonLeft001
 * @tc.desc: Test ResetControlButtonLeft (member, no FrameNode)
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGResetControlButtonLeft001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar and set control button left.
     */
    SideBarContainerModelNG model;
    model.Create();
    model.SetControlButtonLeft(CONTROL_BUTTON_LEFT);

    /**
     * @tc.steps: step2. call ResetControlButtonLeft.
     * @tc.expected: step2. property is reset.
     */
    model.ResetControlButtonLeft();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_FALSE(layoutProperty->GetControlButtonLeft().has_value());
}

/**
 * @tc.name: SideBarModelNGResetResObj001
 * @tc.desc: Test ResetResObj (member, no FrameNode)
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGResetResObj001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar and call ResetResObj.
     * @tc.expected: step1. no crash.
     */
    SideBarContainerModelNG model;
    model.Create();
    model.ResetResObj("sideBarContainer.sideBarWidth");
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: SideBarModelNGResetResObjStatic001
 * @tc.desc: Test ResetResObj (static, with FrameNode)
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGResetResObjStatic001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and call static ResetResObj.
     * @tc.expected: step1. no crash.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::SIDE_BAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(frameNode, nullptr);
    SideBarContainerModelNG::ResetResObj(AceType::RawPtr(frameNode), "sideBarContainer.sideBarWidth");
}

/**
 * @tc.name: SideBarModelNGSetOnChangeEventModifier001
 * @tc.desc: Test SetOnChangeEventModifier
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGSetOnChangeEventModifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar and call SetOnChangeEventModifier.
     */
    SideBarContainerModelNG model;
    model.Create();
    bool callbackCalled = false;
    SideBarContainerModelNG::SetOnChangeEventModifier(
        [&callbackCalled](const bool isShow) { callbackCalled = isShow; });
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. fire event and verify callback.
     * @tc.expected: step2. callback was invoked.
     */
    auto eventHub = frameNode->GetEventHub<SideBarContainerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireChangeEvent(true);
    EXPECT_TRUE(callbackCalled);
}

/**
 * @tc.name: SideBarModelNGSetOnSideBarWidthChangeEvent001
 * @tc.desc: Test SetOnSideBarWidthChangeEvent (member)
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGSetOnSideBarWidthChangeEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar and call SetOnSideBarWidthChangeEvent.
     */
    SideBarContainerModelNG model;
    model.Create();
    Dimension callbackWidth(0.0_vp);
    model.SetOnSideBarWidthChangeEvent(
        [&callbackWidth](const Dimension& width) { callbackWidth = width; });
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. fire event and verify callback.
     * @tc.expected: step2. callback was invoked with correct value.
     */
    auto eventHub = frameNode->GetEventHub<SideBarContainerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    Dimension testWidth(100.0_vp);
    eventHub->FireSideBarWidthChangeEvent(testWidth);
    EXPECT_EQ(callbackWidth, testWidth);
}

/**
 * @tc.name: SideBarModelNGSetOnSideBarWidthChangeEventStatic001
 * @tc.desc: Test SetOnSideBarWidthChangeEventStatic
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGSetOnSideBarWidthChangeEventStatic001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar and call SetOnSideBarWidthChangeEventStatic.
     */
    SideBarContainerModelNG::CreateStatic();
    Dimension callbackWidth(0.0_vp);
    SideBarContainerModelNG::SetOnSideBarWidthChangeEventStatic(
        [&callbackWidth](const Dimension& width) { callbackWidth = width; });
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. fire event and verify callback.
     * @tc.expected: step2. callback was invoked with correct value.
     */
    auto eventHub = frameNode->GetEventHub<SideBarContainerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    Dimension testWidth(200.0_vp);
    eventHub->FireSideBarWidthChangeEvent(testWidth);
    EXPECT_EQ(callbackWidth, testWidth);
}

/**
 * @tc.name: SideBarModelNGSetOnChangeStatic001
 * @tc.desc: Test SetOnChange (static, with FrameNode)
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGSetOnChangeStatic001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and call static SetOnChange.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::SIDE_BAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(frameNode, nullptr);
    bool callbackCalled = false;
    SideBarContainerModelNG::SetOnChange(
        AceType::RawPtr(frameNode), [&callbackCalled](const bool isShow) { callbackCalled = isShow; });

    /**
     * @tc.steps: step2. fire event and verify callback.
     * @tc.expected: step2. callback was invoked.
     */
    auto eventHub = frameNode->GetEventHub<SideBarContainerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireChangeEvent(true);
    EXPECT_TRUE(callbackCalled);
}

/**
 * @tc.name: SideBarModelNGParseAndSetWidthResObj001
 * @tc.desc: Test ParseAndSetWidth with ResourceObject
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGParseAndSetWidthResObj001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar and call ParseAndSetWidth with ResourceObject for SIDEBAR_WIDTH.
     * @tc.expected: step1. no crash.
     */
    SideBarContainerModelNG model;
    model.Create();
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    model.ParseAndSetWidth(WidthType::SIDEBAR_WIDTH, resObj);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: SideBarModelNGParseAndSetWidthResObj002
 * @tc.desc: Test ParseAndSetWidth with ResourceObject for MIN_SIDEBAR_WIDTH
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGParseAndSetWidthResObj002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar and call ParseAndSetWidth with ResourceObject for MIN_SIDEBAR_WIDTH.
     * @tc.expected: step1. no crash.
     */
    SideBarContainerModelNG model;
    model.Create();
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    model.ParseAndSetWidth(WidthType::MIN_SIDEBAR_WIDTH, resObj);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: SideBarModelNGParseAndSetWidthResObj003
 * @tc.desc: Test ParseAndSetWidth with ResourceObject for MAX_SIDEBAR_WIDTH
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGParseAndSetWidthResObj003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar and call ParseAndSetWidth with ResourceObject for MAX_SIDEBAR_WIDTH.
     * @tc.expected: step1. no crash.
     */
    SideBarContainerModelNG model;
    model.Create();
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    model.ParseAndSetWidth(WidthType::MAX_SIDEBAR_WIDTH, resObj);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: SideBarModelNGParseAndSetWidthResObj004
 * @tc.desc: Test ParseAndSetWidth with ResourceObject for invalid WidthType
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGParseAndSetWidthResObj004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar and call ParseAndSetWidth with invalid type.
     * @tc.expected: step1. no crash.
     */
    SideBarContainerModelNG model;
    model.Create();
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    model.ParseAndSetWidth(static_cast<WidthType>(-1), resObj);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: SideBarModelNGParseAndSetWidthStaticResObj001
 * @tc.desc: Test ParseAndSetWidthStatic with ResourceObject
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGParseAndSetWidthStaticResObj001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar via CreateStatic and call ParseAndSetWidthStatic with ResourceObject.
     */
    SideBarContainerModelNG::CreateStatic();
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    SideBarContainerModelNG::ParseAndSetWidthStatic(WidthType::SIDEBAR_WIDTH, resObj);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: SideBarModelNGParseAndSetWidthStaticResObj002
 * @tc.desc: Test ParseAndSetWidthStatic with ResourceObject for MIN/MAX
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGParseAndSetWidthStaticResObj002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar via CreateStatic and call ParseAndSetWidthStatic with ResourceObject.
     */
    SideBarContainerModelNG::CreateStatic();
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    SideBarContainerModelNG::ParseAndSetWidthStatic(WidthType::MIN_SIDEBAR_WIDTH, resObj);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: SideBarModelNGParseAndSetWidthStaticResObj003
 * @tc.desc: Test ParseAndSetWidthStatic with ResourceObject for MAX_SIDEBAR_WIDTH
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGParseAndSetWidthStaticResObj003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar via CreateStatic and call ParseAndSetWidthStatic with ResourceObject.
     */
    SideBarContainerModelNG::CreateStatic();
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    SideBarContainerModelNG::ParseAndSetWidthStatic(WidthType::MAX_SIDEBAR_WIDTH, resObj);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: SideBarModelNGSetControlButtonIconResObj001
 * @tc.desc: Test SetControlButtonShowIconInfo with ResourceObject (member)
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGSetControlButtonIconResObj001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar and call SetControlButtonShowIconInfo with ResourceObject.
     */
    SideBarContainerModelNG model;
    model.Create();
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    model.SetControlButtonShowIconInfo(resObj, false, nullptr);
    model.SetControlButtonHiddenIconInfo(resObj, false, nullptr);
    model.SetControlButtonSwitchingIconInfo(resObj, false, nullptr);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: SideBarModelNGSetDividerResObj001
 * @tc.desc: Test SetDividerStrokeWidth/Color/StartMargin/EndMargin with ResourceObject (member)
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGSetDividerResObj001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar and call divider setters with ResourceObject.
     */
    SideBarContainerModelNG model;
    model.Create();
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    model.SetDividerStrokeWidth(resObj);
    model.SetDividerColor(resObj);
    model.SetDividerStartMargin(resObj);
    model.SetDividerEndMargin(resObj);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: SideBarModelNGSetMinContentWidthResObj001
 * @tc.desc: Test SetMinContentWidth with ResourceObject (member)
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGSetMinContentWidthResObj001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar and call SetMinContentWidth with ResourceObject.
     */
    SideBarContainerModelNG model;
    model.Create();
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    model.SetMinContentWidth(resObj);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: SideBarModelNGSetSideBarWidthFrameNodeResObj001
 * @tc.desc: Test SetSideBarWidth(FrameNode*, ResourceObject)
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGSetSideBarWidthFrameNodeResObj001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and call SetSideBarWidth with ResourceObject.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::SIDE_BAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    SideBarContainerModelNG::SetSideBarWidth(AceType::RawPtr(frameNode), resObj);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: SideBarModelNGSetMinSideBarWidthFrameNodeResObj001
 * @tc.desc: Test SetMinSideBarWidth(FrameNode*, ResourceObject)
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGSetMinSideBarWidthFrameNodeResObj001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and call SetMinSideBarWidth with ResourceObject.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::SIDE_BAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    SideBarContainerModelNG::SetMinSideBarWidth(AceType::RawPtr(frameNode), resObj);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: SideBarModelNGSetMaxSideBarWidthFrameNodeResObj001
 * @tc.desc: Test SetMaxSideBarWidth(FrameNode*, ResourceObject)
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGSetMaxSideBarWidthFrameNodeResObj001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and call SetMaxSideBarWidth with ResourceObject.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::SIDE_BAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    SideBarContainerModelNG::SetMaxSideBarWidth(AceType::RawPtr(frameNode), resObj);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: SideBarModelNGSetMinContentWidthFrameNodeResObj001
 * @tc.desc: Test SetMinContentWidth(FrameNode*, ResourceObject)
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGSetMinContentWidthFrameNodeResObj001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and call SetMinContentWidth with ResourceObject.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::SIDE_BAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    SideBarContainerModelNG::SetMinContentWidth(AceType::RawPtr(frameNode), resObj);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: SideBarModelNGSetControlButtonIconFrameNodeResObj001
 * @tc.desc: Test SetControlButtonShowIconInfo/Hidden/Switching (FrameNode*, ResourceObject)
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGSetControlButtonIconFrameNodeResObj001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and call icon setters with ResourceObject.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::SIDE_BAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    SideBarContainerModelNG::SetControlButtonShowIconInfo(AceType::RawPtr(frameNode), resObj, false, nullptr);
    SideBarContainerModelNG::SetControlButtonHiddenIconInfo(AceType::RawPtr(frameNode), resObj, false, nullptr);
    SideBarContainerModelNG::SetControlButtonSwitchingIconInfo(AceType::RawPtr(frameNode), resObj, false, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: SideBarModelNGSetDividerFrameNodeResObj001
 * @tc.desc: Test divider setters (FrameNode*, ResourceObject)
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGSetDividerFrameNodeResObj001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and call divider setters with ResourceObject.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::SIDE_BAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    SideBarContainerModelNG::SetDividerStrokeWidth(AceType::RawPtr(frameNode), resObj);
    SideBarContainerModelNG::SetDividerColor(AceType::RawPtr(frameNode), resObj);
    SideBarContainerModelNG::SetDividerStartMargin(AceType::RawPtr(frameNode), resObj);
    SideBarContainerModelNG::SetDividerEndMargin(AceType::RawPtr(frameNode), resObj);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: SideBarModelNGSetSideBarWidthStaticDoubleBind001
 * @tc.desc: Test SetSideBarWidthStatic with double bind blocked
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGSetSideBarWidthStaticDoubleBind001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar, set initial width.
     */
    SideBarContainerModelNG::CreateStatic();
    SideBarContainerModelNG::SetSideBarWidthStatic(SIDE_BAR_WIDTH);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetSideBarWidth(), SIDE_BAR_WIDTH);

    /**
     * @tc.steps: step2. set double bind true but not in drag.
     * @tc.expected: step2. width is updated.
     */
    ViewStackProcessor::GetInstance()->Push(frameNode);
    SideBarContainerModelNG::sideBarWidthDoubleBind_ = true;
    pattern->isInDividerDrag_ = false;
    SideBarContainerModelNG::SetSideBarWidthStatic(MIN_SIDE_BAR_WIDTH, true);
    ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(layoutProperty->GetSideBarWidth(), MIN_SIDE_BAR_WIDTH);
    SideBarContainerModelNG::sideBarWidthDoubleBind_ = false;
    pattern->isInDividerDrag_ = false;
}

/**
 * @tc.name: SideBarModelNGParseAndSetWidthStaticDoubleBind001
 * @tc.desc: Test ParseAndSetWidthStatic with double bind blocked
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGParseAndSetWidthStaticDoubleBind001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar, set initial width, set double bind + drag.
     */
    SideBarContainerModelNG::CreateStatic();
    SideBarContainerModelNG::SetSideBarWidthStatic(SIDE_BAR_WIDTH);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SideBarContainerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SideBarContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. push frameNode, set double bind + drag, try to change width.
     * @tc.expected: step2. width not changed due to double bind block.
     */
    ViewStackProcessor::GetInstance()->Push(frameNode);
    SideBarContainerModelNG::sideBarWidthDoubleBind_ = true;
    pattern->isInDividerDrag_ = true;
    Dimension newWidth = MIN_SIDE_BAR_WIDTH;
    SideBarContainerModelNG::ParseAndSetWidthStatic(WidthType::SIDEBAR_WIDTH, newWidth, true);
    ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(layoutProperty->GetSideBarWidth(), SIDE_BAR_WIDTH);
    SideBarContainerModelNG::sideBarWidthDoubleBind_ = false;
    pattern->isInDividerDrag_ = false;
}

/**
 * @tc.name: SideBarModelNGSetControlButtonIconResObjNull001
 * @tc.desc: Test SetControlButtonShowIconInfo/Hidden/Switching with null ResourceObject (member)
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGSetControlButtonIconResObjNull001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar and call icon setters with null ResourceObject.
     * @tc.expected: step1. no crash, resource obj removed.
     */
    SideBarContainerModelNG model;
    model.Create();
    RefPtr<ResourceObject> nullResObj;
    model.SetControlButtonShowIconInfo(nullResObj, false, nullptr);
    model.SetControlButtonHiddenIconInfo(nullResObj, false, nullptr);
    model.SetControlButtonSwitchingIconInfo(nullResObj, false, nullptr);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: SideBarModelNGSetDividerResObjNull001
 * @tc.desc: Test divider setters with null ResourceObject (member)
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGSetDividerResObjNull001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar and call divider setters with null ResourceObject.
     * @tc.expected: step1. no crash.
     */
    SideBarContainerModelNG model;
    model.Create();
    RefPtr<ResourceObject> nullResObj;
    model.SetDividerStrokeWidth(nullResObj);
    model.SetDividerColor(nullResObj);
    model.SetDividerStartMargin(nullResObj);
    model.SetDividerEndMargin(nullResObj);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: SideBarModelNGSetMinContentWidthResObjNull001
 * @tc.desc: Test SetMinContentWidth with null ResourceObject (member)
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGSetMinContentWidthResObjNull001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar and call SetMinContentWidth with null ResourceObject.
     * @tc.expected: step1. no crash.
     */
    SideBarContainerModelNG model;
    model.Create();
    RefPtr<ResourceObject> nullResObj;
    model.SetMinContentWidth(nullResObj);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: SideBarModelNGSetControlButtonIconFrameNodeResObjNull001
 * @tc.desc: Test SetControlButtonShowIconInfo/Hidden/Switching (FrameNode*, null ResourceObject)
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGSetControlButtonIconFrameNodeResObjNull001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and call icon setters with null ResourceObject.
     * @tc.expected: step1. no crash.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::SIDE_BAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<ResourceObject> nullResObj;
    SideBarContainerModelNG::SetControlButtonShowIconInfo(AceType::RawPtr(frameNode), nullResObj, false, nullptr);
    SideBarContainerModelNG::SetControlButtonHiddenIconInfo(AceType::RawPtr(frameNode), nullResObj, false, nullptr);
    SideBarContainerModelNG::SetControlButtonSwitchingIconInfo(AceType::RawPtr(frameNode), nullResObj, false, nullptr);
}

/**
 * @tc.name: SideBarModelNGSetDividerFrameNodeResObjNull001
 * @tc.desc: Test divider setters (FrameNode*, null ResourceObject)
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGSetDividerFrameNodeResObjNull001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and call divider setters with null ResourceObject.
     * @tc.expected: step1. no crash.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::SIDE_BAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<ResourceObject> nullResObj;
    SideBarContainerModelNG::SetDividerStrokeWidth(AceType::RawPtr(frameNode), nullResObj);
    SideBarContainerModelNG::SetDividerColor(AceType::RawPtr(frameNode), nullResObj);
    SideBarContainerModelNG::SetDividerStartMargin(AceType::RawPtr(frameNode), nullResObj);
    SideBarContainerModelNG::SetDividerEndMargin(AceType::RawPtr(frameNode), nullResObj);
}

/**
 * @tc.name: SideBarModelNGSetSideBarWidthFrameNodeResObjNull001
 * @tc.desc: Test SetSideBarWidth/Min/Max/MinContent (FrameNode*, null ResourceObject)
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGSetSideBarWidthFrameNodeResObjNull001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and call width setters with null ResourceObject.
     * @tc.expected: step1. no crash.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::SIDE_BAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SideBarContainerPattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<ResourceObject> nullResObj;
    SideBarContainerModelNG::SetSideBarWidth(AceType::RawPtr(frameNode), nullResObj);
    SideBarContainerModelNG::SetMinSideBarWidth(AceType::RawPtr(frameNode), nullResObj);
    SideBarContainerModelNG::SetMaxSideBarWidth(AceType::RawPtr(frameNode), nullResObj);
    SideBarContainerModelNG::SetMinContentWidth(AceType::RawPtr(frameNode), nullResObj);
}

/**
 * @tc.name: SideBarModelNGSetSideBarWidthResObjNull001
 * @tc.desc: Test SetSideBarWidth/Min/Max/MinContentWidth with null ResourceObject (private, via ParseAndSetWidth)
 * @tc.type: FUNC
 */
HWTEST_F(SideBarModelNGTestNg, SideBarModelNGSetSideBarWidthResObjNull001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sideBar and call ParseAndSetWidth with null ResourceObject.
     * @tc.expected: step1. no crash.
     */
    SideBarContainerModelNG model;
    model.Create();
    RefPtr<ResourceObject> nullResObj;
    model.ParseAndSetWidth(WidthType::SIDEBAR_WIDTH, nullResObj);
    model.ParseAndSetWidth(WidthType::MIN_SIDEBAR_WIDTH, nullResObj);
    model.ParseAndSetWidth(WidthType::MAX_SIDEBAR_WIDTH, nullResObj);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
}
} // namespace OHOS::Ace::NG
