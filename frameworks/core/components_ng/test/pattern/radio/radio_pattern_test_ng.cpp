/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/radio/radio_model_ng.h"
#include "core/components_ng/pattern/radio/radio_paint_property.h"
#include "core/components_ng/pattern/radio/radio_pattern.h"
#include "core/components_ng/pattern/stage/stage_manager.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string NAME = "radio";
const std::string NAME1 = "radio1";
const std::string GROUP_NAME = "radioGroup";
const std::string GROUP_NAME1 = "radioGroup1";
const std::string GROUP_NAME_CHANGE = "radioGroupChange";
constexpr Dimension WIDTH = 50.0_vp;
constexpr Dimension HEIGHT = 50.0_vp;
constexpr NG::PaddingPropertyF PADDING = NG::PaddingPropertyF();
constexpr bool CHECKED = true;
constexpr Dimension HORIZONTAL_PADDING = Dimension(5.0);
constexpr Dimension VERTICAL_PADDING = Dimension(4.0);
constexpr float COMPONENT_WIDTH = 200.0;
constexpr float COMPONENT_HEIGHT = 210.0;
constexpr float COMPONENT_WIDTH_INVALID = -1.0;
constexpr float COMPONENT_HEIGHT_INVALID = -1.0;
constexpr double DEFAULT_WIDTH = 100.0;
constexpr double DEFAULT_HEIGHT = 110.0;
constexpr Dimension DEFAULT_WIDTH_DIMENSION = Dimension(DEFAULT_WIDTH);
constexpr Dimension DEFAULT_HEIGHT_DIMENSION = Dimension(DEFAULT_HEIGHT);
const SizeF CONTENT_SIZE = SizeF(400.0, 500.0);
const OffsetF CONTENT_OFFSET = OffsetF(50.0, 60.0);
constexpr Color NORMAL_COLOR = Color(0xff0000ff);
constexpr Color ERROR_COLOR = Color();
} // namespace

class RadioPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override {}
    void TearDown() override {}
};

void RadioPatternTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void RadioPatternTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: RadioPaintPropertyTest001
 * @tc.desc: Set Radio value into RadioPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPaintPropertyTest001, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME);
    radioModelNG.SetChecked(CHECKED);
    radioModelNG.SetWidth(WIDTH);
    radioModelNG.SetHeight(HEIGHT);
    radioModelNG.SetPadding(PADDING);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    EXPECT_EQ(radioPaintProperty->GetRadioCheck(), CHECKED);
}

/**
 * @tc.name: RadioPaintPropertyTest002
 * @tc.desc: Test SetCheckedBackgroundColor when the Radio is checked.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPaintPropertyTest002, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME);
    radioModelNG.SetChecked(true);
    radioModelNG.SetCheckedBackgroundColor(NORMAL_COLOR);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    EXPECT_EQ(radioPaintProperty->GetRadioCheckedBackgroundColorValue(), NORMAL_COLOR);

    RadioModelNG radioModelNG2;
    radioModelNG2.Create(NAME, GROUP_NAME);
    radioModelNG2.SetChecked(true);
    radioModelNG2.SetCheckedBackgroundColor(ERROR_COLOR);
    auto frameNode2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode2, nullptr);
    auto radioPaintProperty2 = frameNode2->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty2, nullptr);
    EXPECT_EQ(radioPaintProperty2->GetRadioCheckedBackgroundColorValue(), ERROR_COLOR);
}

/**
 * @tc.name: RadioPaintPropertyTest003
 * @tc.desc: Test SetUncheckedBorderColor when the Radio is unchecked.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPaintPropertyTest003, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME);
    radioModelNG.SetChecked(false);
    radioModelNG.SetUncheckedBorderColor(NORMAL_COLOR);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    EXPECT_EQ(radioPaintProperty->GetRadioUncheckedBorderColorValue(), NORMAL_COLOR);

    RadioModelNG radioModelNG2;
    radioModelNG2.Create(NAME, GROUP_NAME);
    radioModelNG2.SetChecked(false);
    radioModelNG2.SetUncheckedBorderColor(ERROR_COLOR);
    auto frameNode2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode2, nullptr);
    auto radioPaintProperty2 = frameNode2->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty2, nullptr);
    EXPECT_EQ(radioPaintProperty2->GetRadioUncheckedBorderColorValue(), ERROR_COLOR);
}

/**
 * @tc.name: RadioPaintPropertyTest006
 * @tc.desc: Test SetIndicatorColor when the Radio is select.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPaintPropertyTest004, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME);
    radioModelNG.SetChecked(true);
    radioModelNG.SetIndicatorColor(NORMAL_COLOR);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    EXPECT_EQ(radioPaintProperty->GetRadioIndicatorColorValue(), NORMAL_COLOR);

    RadioModelNG radioModelNG2;
    radioModelNG2.Create(NAME, GROUP_NAME);
    radioModelNG2.SetChecked(true);
    radioModelNG2.SetIndicatorColor(ERROR_COLOR);
    auto frameNode2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode2, nullptr);
    auto radioPaintProperty2 = frameNode2->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty2, nullptr);
    EXPECT_EQ(radioPaintProperty2->GetRadioIndicatorColorValue(), ERROR_COLOR);
}

/**
 * @tc.name: RadioEventHubPropertyTest002
 * @tc.desc: Set Radio value into RadioEventHub and get it.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioEventHubPropertyTest002, TestSize.Level1)
{
    /**
     * @tc.cases: case1. RadioPattern can Create without value or group.
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(std::nullopt, std::nullopt);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_TRUE(eventHub->GetValue().empty());
    EXPECT_TRUE(eventHub->GetGroup().empty());
    /**
     * @tc.cases: case2. RadioPattern can Create with value and group.
     */
    RadioModelNG radioModelNG2;
    radioModelNG2.Create(NAME, GROUP_NAME);
    auto frameNode2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub2 = frameNode2->GetEventHub<NG::RadioEventHub>();
    ASSERT_NE(eventHub2, nullptr);
    EXPECT_EQ(eventHub2->GetValue(), NAME);
    EXPECT_EQ(eventHub2->GetGroup(), GROUP_NAME);
}

/**
 * @tc.name: RadioEventHubPropertyTest003
 * @tc.desc: Set Radio value into RadioEventHub and get it.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioEventHubPropertyTest003, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(std::nullopt, GROUP_NAME);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_EQ(eventHub->GetValue(), "");
    EXPECT_EQ(eventHub->GetGroup(), GROUP_NAME);
}

/**
 * @tc.name: RadioEventHubPropertyTest004
 * @tc.desc: Set Radio value into RadioEventHub and get it.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioEventHubPropertyTest004, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, std::nullopt);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_EQ(eventHub->GetValue(), NAME);
    EXPECT_EQ(eventHub->GetGroup(), "");
}

/**
 * @tc.name: RadioEventTest003
 * @tc.desc: Test Radio onChange event.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioEventTest003, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME);
    bool isChecked = false;
    auto onChange = [&isChecked](bool select) { isChecked = select; };
    radioModelNG.SetOnChange(onChange);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->UpdateChangeEvent(true);
    EXPECT_EQ(isChecked, true);
}

/**
 * @tc.name: RadioPatternTest004
 * @tc.desc: Test Radio onModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest004, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto radioTheme = AceType::MakeRefPtr<RadioTheme>();
    radioTheme->hotZoneHorizontalPadding_ = HORIZONTAL_PADDING;
    radioTheme->hotZoneVerticalPadding_ = VERTICAL_PADDING;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(radioTheme));
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(frameNode->GetLayoutProperty()->GetMarginProperty()->left.value(),
        CalcLength(radioTheme->hotZoneHorizontalPadding_.Value()));
    EXPECT_EQ(frameNode->GetLayoutProperty()->GetMarginProperty()->right.value(),
        CalcLength(radioTheme->hotZoneHorizontalPadding_.Value()));
    EXPECT_EQ(frameNode->GetLayoutProperty()->GetMarginProperty()->top.value(),
        CalcLength(radioTheme->hotZoneVerticalPadding_.Value()));
    EXPECT_EQ(frameNode->GetLayoutProperty()->GetMarginProperty()->bottom.value(),
        CalcLength(radioTheme->hotZoneVerticalPadding_.Value()));
    pattern->SetPreGroup(GROUP_NAME);
    frameNode->MarkModifyDone();
    pattern->SetPreGroup(GROUP_NAME_CHANGE);
    frameNode->MarkModifyDone();
}

/**
 * @tc.name: RadioPatternTest005
 * @tc.desc: Test UpdateUncheckStatus.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest005, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME);
    bool isChecked = false;
    auto onChange = [&isChecked](bool select) { isChecked = select; };
    radioModelNG.SetOnChange(onChange);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->UpdateUncheckStatus(frameNode);
    EXPECT_EQ(isChecked, false);
}

/**
 * @tc.name: RadioPatternTest006
 * @tc.desc: Test UpdateUncheckStatus.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest006, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME);
    radioModelNG.SetChecked(true);
    bool isChecked = false;
    auto onChange = [&isChecked](bool select) { isChecked = select; };
    radioModelNG.SetOnChange(onChange);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    EXPECT_EQ(radioPaintProperty->GetRadioCheckValue(), CHECKED);
    pattern->UpdateUncheckStatus(frameNode);
    EXPECT_NE(radioPaintProperty->GetRadioCheckValue(), CHECKED);
}

/**
 * @tc.name: RadioPatternTest007
 * @tc.desc: Test UpdateGroupCheckStatus.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest007, TestSize.Level1)
{
    RadioModelNG radioModelNG0;
    radioModelNG0.Create(NAME, GROUP_NAME);
    radioModelNG0.SetChecked(true);
    bool isChecked0 = false;
    auto onChange0 = [&isChecked0](bool select) { isChecked0 = select; };
    radioModelNG0.SetOnChange(onChange0);
    auto frameNode0 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode0, nullptr);
    frameNode0->MarkModifyDone();
    auto pattern0 = frameNode0->GetPattern<RadioPattern>();
    ASSERT_NE(pattern0, nullptr);

    auto radioPaintProperty = frameNode0->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    EXPECT_EQ(radioPaintProperty->GetRadioCheckValue(), CHECKED);
    pattern0->UpdateGroupCheckStatus(frameNode0, false);
    EXPECT_NE(radioPaintProperty->GetRadioCheckValue(), CHECKED);
}

/**
 * @tc.name: RadioPatternTest008
 * @tc.desc: Test UpdateGroupCheckStatus.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest008, TestSize.Level1)
{
    auto frameNode0 =
        FrameNode::GetOrCreateFrameNode(V2::RADIO_ETS_TAG, 0, []() { return AceType::MakeRefPtr<RadioPattern>(); });
    ViewStackProcessor::GetInstance()->Push(frameNode0);
    auto eventHub0 = frameNode0->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub0);
    eventHub0->SetValue(NAME);
    eventHub0->SetGroup(GROUP_NAME);
    RadioModelNG radioModelNG0;
    radioModelNG0.SetChecked(false);
    bool isChecked0 = false;
    auto onChange0 = [&isChecked0](bool select) { isChecked0 = select; };
    radioModelNG0.SetOnChange(onChange0);
    frameNode0->MarkModifyDone();
    auto pattern0 = frameNode0->GetPattern<RadioPattern>();
    ASSERT_NE(pattern0, nullptr);
    pattern0->UpdateState();

    auto frameNode1 =
        FrameNode::GetOrCreateFrameNode(V2::RADIO_ETS_TAG, 1, []() { return AceType::MakeRefPtr<RadioPattern>(); });
    ViewStackProcessor::GetInstance()->Push(frameNode1);
    auto eventHub1 = frameNode1->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub1);
    eventHub1->SetValue(NAME1);
    eventHub1->SetGroup(GROUP_NAME1);
    RadioModelNG radioModelNG1;
    radioModelNG1.SetChecked(true);
    bool isChecked1 = false;
    auto onChange1 = [&isChecked1](bool select) { isChecked1 = select; };
    radioModelNG1.SetOnChange(onChange1);
    frameNode1->MarkModifyDone();
    auto pattern1 = frameNode1->GetPattern<RadioPattern>();
    ASSERT_NE(pattern1, nullptr);
    pattern1->UpdateState();

    auto radioPaintProperty0 = frameNode0->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty0, nullptr);
    EXPECT_NE(radioPaintProperty0->GetRadioCheckValue(), CHECKED);
    pattern0->UpdateGroupCheckStatus(frameNode0, true);
    auto radioPaintProperty1 = frameNode1->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty1, nullptr);
    EXPECT_EQ(radioPaintProperty1->GetRadioCheckValue(), CHECKED);
}

/**
 * @tc.name: RadioPatternTest009
 * @tc.desc: Test InitClickEvent.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest009, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitClickEvent();
    ASSERT_NE(pattern->clickListener_, nullptr);
    pattern->InitClickEvent();
}

/**
 * @tc.name: RadioPatternTest010
 * @tc.desc: Test InitTouchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest010, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitTouchEvent();
    ASSERT_NE(pattern->touchListener_, nullptr);
    pattern->InitTouchEvent();
}

/**
 * @tc.name: RadioPatternTest011
 * @tc.desc: Test InitMouseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest011, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitMouseEvent();
    ASSERT_NE(pattern->mouseEvent_, nullptr);
    pattern->InitMouseEvent();
}

/**
 * @tc.name: RadioPatternTest012
 * @tc.desc: Test OnClick.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest012, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->UpdateState();
    pattern->OnClick();
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    auto select1 = radioPaintProperty->GetRadioCheckValue();
    EXPECT_EQ(select1, true);
}

/**
 * @tc.name: RadioPatternTest013
 * @tc.desc: Test OnClick.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest013, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->UpdateState();
    pattern->OnClick();
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    auto select1 = radioPaintProperty->GetRadioCheckValue();
    EXPECT_EQ(select1, true);
}

/**
 * @tc.name: RadioPatternTest014
 * @tc.desc: Test OnClick.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest014, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnClick();
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    auto select1 = radioPaintProperty->GetRadioCheckValue();
    EXPECT_EQ(select1, true);
}

/**
 * @tc.name: RadioPatternTest015
 * @tc.desc: Test OnClick.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest015, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->UpdateState();
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    radioPaintProperty->ResetRadioCheck();
    pattern->OnClick();
    auto select1 = radioPaintProperty->GetRadioCheckValue();
    EXPECT_EQ(select1, false);
}

/**
 * @tc.name: RadioPatternTest016
 * @tc.desc: Test OnClick.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest016, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    radioPaintProperty->ResetRadioCheck();
    pattern->OnClick();
    auto select1 = radioPaintProperty->GetRadioCheckValue();
    EXPECT_EQ(select1, false);
}

/**
 * @tc.name: RadioPatternTest017
 * @tc.desc: Test PlayAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest017, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    radioModelNG.SetChecked(true);
    pattern->PlayAnimation(true);
    ASSERT_NE(pattern->onController_, nullptr);
    pattern->PlayAnimation(true);
}

/**
 * @tc.name: RadioPatternTest018
 * @tc.desc: Test PlayAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest018, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    radioModelNG.SetChecked(false);
    pattern->PlayAnimation(false);
    ASSERT_NE(pattern->onController_, nullptr);
    pattern->PlayAnimation(false);
}

/**
 * @tc.name: RadioPatternTest019
 * @tc.desc: Test OnTouchDown   OnTouchUp.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest019, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitMouseEvent();
    pattern->HandleMouseEvent(false);
    ASSERT_EQ(pattern->isHover_, false);
    pattern->OnTouchDown();
    EXPECT_EQ(pattern->touchHoverType_, TouchHoverAnimationType::PRESS);
    EXPECT_TRUE(pattern->isTouch_);
    pattern->OnTouchUp();
    EXPECT_EQ(pattern->touchHoverType_, TouchHoverAnimationType::NONE);
    EXPECT_FALSE(pattern->isTouch_);

}

/**
 * @tc.name: RadioPatternTest020
 * @tc.desc: Test OnTouchDown   OnTouchUp.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest020, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitMouseEvent();
    pattern->HandleMouseEvent(true);
    EXPECT_TRUE(pattern->isHover_);
    pattern->OnTouchDown();
    EXPECT_EQ(pattern->touchHoverType_, TouchHoverAnimationType::HOVER_TO_PRESS);
    EXPECT_TRUE(pattern->isTouch_);
    pattern->OnTouchUp();
    EXPECT_EQ(pattern->touchHoverType_, TouchHoverAnimationType::PRESS_TO_HOVER);
    EXPECT_FALSE(pattern->isTouch_);

}

/**
 * @tc.name: RadioLayoutAlgorithmTest001
 * @tc.desc: Verify that RadioLayoutAlgorithm can correctly InitializeParam.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioLayoutAlgorithmTest001, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto radioTheme = AceType::MakeRefPtr<RadioTheme>();
    radioTheme->hotZoneHorizontalPadding_ = HORIZONTAL_PADDING;
    radioTheme->hotZoneVerticalPadding_ = VERTICAL_PADDING;
    radioTheme->defaultWidth_ = DEFAULT_WIDTH_DIMENSION;
    radioTheme->defaultHeight_ = DEFAULT_HEIGHT_DIMENSION;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(radioTheme));
    RadioLayoutAlgorithm radioLayoutAlgorithm;
    radioLayoutAlgorithm.InitializeParam();
    EXPECT_EQ(radioLayoutAlgorithm.horizontalPadding_, HORIZONTAL_PADDING.ConvertToPx());
    EXPECT_EQ(radioLayoutAlgorithm.verticalPadding_, VERTICAL_PADDING.ConvertToPx());
}

/**
 * @tc.name: RadioLayoutAlgorithmTest002
 * @tc.desc: Verify that RadioLayoutAlgorithm's MeasureContent can get contentSize
             when Width and height are set in the front end.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioLayoutAlgorithmTest002, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<RadioTheme>()));
    /**
    //     corresponding ets code:
    //         Radio().width(200).height(210)
    //     size = (200, 200)
    */
    LayoutWrapper layoutWrapper(nullptr, nullptr, nullptr);
    RadioLayoutAlgorithm radioLayoutAlgorithm;
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetWidth(COMPONENT_WIDTH);
    layoutConstraintSize.selfIdealSize.SetHeight(COMPONENT_HEIGHT);
    auto size = radioLayoutAlgorithm.MeasureContent(layoutConstraintSize, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(size.value(), SizeF(COMPONENT_WIDTH, COMPONENT_WIDTH));
}

/**
 * @tc.name: RadioLayoutAlgorithmTest003
 * @tc.desc: Verify that RadioLayoutAlgorithm's MeasureContent can get contentSize
             when The front end only sets width.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioLayoutAlgorithmTest003, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<RadioTheme>()));
    /**
    //     corresponding ets code:
    //         Radio().width(200)
    //     size = (200, 200)
    */
    LayoutWrapper layoutWrapper(nullptr, nullptr, nullptr);
    RadioLayoutAlgorithm radioLayoutAlgorithm;
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetWidth(COMPONENT_WIDTH);
    auto size = radioLayoutAlgorithm.MeasureContent(layoutConstraintSize, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(size.value(), SizeF(COMPONENT_WIDTH, COMPONENT_WIDTH));
}

/**
 * @tc.name: RadioLayoutAlgorithmTest004
 * @tc.desc: Verify that RadioLayoutAlgorithm's MeasureContent can get contentSize
             when The front end only sets height.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioLayoutAlgorithmTest004, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<RadioTheme>()));
    /**
    //     corresponding ets code:
    //         Radio().height(210)
    //     size = (210, 210)
    */
    LayoutWrapper layoutWrapper(nullptr, nullptr, nullptr);
    RadioLayoutAlgorithm radioLayoutAlgorithm;
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetHeight(COMPONENT_HEIGHT);
    auto size = radioLayoutAlgorithm.MeasureContent(layoutConstraintSize, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(size.value(), SizeF(COMPONENT_HEIGHT, COMPONENT_HEIGHT));
}

/**
 * @tc.name: RadioLayoutAlgorithmTest005
 * @tc.desc: Verify that RadioLayoutAlgorithm's MeasureContent can get contentSize from the theme,
             when Width and height are not set in the front end.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioLayoutAlgorithmTest005, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto radioTheme = AceType::MakeRefPtr<RadioTheme>();
    radioTheme->hotZoneHorizontalPadding_ = HORIZONTAL_PADDING;
    radioTheme->hotZoneVerticalPadding_ = VERTICAL_PADDING;
    radioTheme->defaultWidth_ = DEFAULT_WIDTH_DIMENSION;
    radioTheme->defaultHeight_ = DEFAULT_HEIGHT_DIMENSION;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(radioTheme));
    /**
    //     corresponding ets code:
    //         Radio()
    //     length = min(theme.Width(), theme.Height()), size = (length, length)
    */
    LayoutWrapper layoutWrapper(nullptr, nullptr, nullptr);
    RadioLayoutAlgorithm radioLayoutAlgorithm;
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.maxSize = SizeF(1000.0, 1000.0);
    layoutConstraintSize.minSize = SizeF(0, 0);
    auto size = radioLayoutAlgorithm.MeasureContent(layoutConstraintSize, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(radioLayoutAlgorithm.horizontalPadding_, HORIZONTAL_PADDING.ConvertToPx());
    EXPECT_EQ(radioLayoutAlgorithm.verticalPadding_, VERTICAL_PADDING.ConvertToPx());
}

/**
 * @tc.name: RadioLayoutAlgorithmTest006
 * @tc.desc: Verify that RadioLayoutAlgorithm's MeasureContent can get contentSize
             when Width and height are set in the front end.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioLayoutAlgorithmTest006, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<RadioTheme>()));
    LayoutWrapper layoutWrapper(nullptr, nullptr, nullptr);
    RadioLayoutAlgorithm radioLayoutAlgorithm;
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetWidth(COMPONENT_WIDTH_INVALID);
    layoutConstraintSize.selfIdealSize.SetHeight(COMPONENT_HEIGHT_INVALID);
    auto size = radioLayoutAlgorithm.MeasureContent(layoutConstraintSize, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(size.value(), SizeF(0, 0));
}

/**
 * @tc.name: RadioLayoutAlgorithmTest007
 * @tc.desc: Verify that RadioLayoutAlgorithm's MeasureContent can get contentSize
             when The front end only sets width.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioLayoutAlgorithmTest007, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<RadioTheme>()));
    LayoutWrapper layoutWrapper(nullptr, nullptr, nullptr);
    RadioLayoutAlgorithm radioLayoutAlgorithm;
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetWidth(COMPONENT_WIDTH_INVALID);
    auto size = radioLayoutAlgorithm.MeasureContent(layoutConstraintSize, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(size.value(), SizeF(0, 0));
}

/**
 * @tc.name: RadioLayoutAlgorithmTest008
 * @tc.desc: Verify that RadioLayoutAlgorithm's MeasureContent can get contentSize
             when The front end only sets height.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioLayoutAlgorithmTest008, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<RadioTheme>()));
    LayoutWrapper layoutWrapper(nullptr, nullptr, nullptr);
    RadioLayoutAlgorithm radioLayoutAlgorithm;
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetHeight(COMPONENT_HEIGHT_INVALID);
    auto size = radioLayoutAlgorithm.MeasureContent(layoutConstraintSize, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(size.value(), SizeF(0, 0));
}

} // namespace OHOS::Ace::NG
