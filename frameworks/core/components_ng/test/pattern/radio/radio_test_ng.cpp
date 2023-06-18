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
const std::string VALUE = "radio";
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

class RadioTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void RadioTestNg::SetUpTestSuite()
{
    MockPipelineBase::SetUp();
}

void RadioTestNg::TearDownTestSuite()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: RadioPaintPropertyTest001
 * @tc.desc: Set Radio value into RadioPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPaintPropertyTest001, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME);
    radioModelNG.SetChecked(CHECKED);
    radioModelNG.SetWidth(WIDTH);
    radioModelNG.SetHeight(HEIGHT);
    NG::PaddingProperty newPadding(
        { NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp) });
    radioModelNG.SetPadding(PADDING, newPadding);
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
HWTEST_F(RadioTestNg, RadioPaintPropertyTest002, TestSize.Level1)
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
HWTEST_F(RadioTestNg, RadioPaintPropertyTest003, TestSize.Level1)
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
HWTEST_F(RadioTestNg, RadioPaintPropertyTest004, TestSize.Level1)
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
HWTEST_F(RadioTestNg, RadioEventHubPropertyTest002, TestSize.Level1)
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
HWTEST_F(RadioTestNg, RadioEventHubPropertyTest003, TestSize.Level1)
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
HWTEST_F(RadioTestNg, RadioEventHubPropertyTest004, TestSize.Level1)
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
HWTEST_F(RadioTestNg, RadioEventTest003, TestSize.Level1)
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
HWTEST_F(RadioTestNg, RadioPatternTest004, TestSize.Level1)
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
HWTEST_F(RadioTestNg, RadioPatternTest005, TestSize.Level1)
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
HWTEST_F(RadioTestNg, RadioPatternTest006, TestSize.Level1)
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
HWTEST_F(RadioTestNg, RadioPatternTest007, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_VOID(stageManager);
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
    auto pageNode = stageManager->GetPageById(frameNode0->GetPageId());
    pattern0->UpdateGroupCheckStatus(frameNode0, pageNode, false);
    EXPECT_TRUE(radioPaintProperty->GetRadioCheckValue());
}

/**
 * @tc.name: RadioPatternTest008
 * @tc.desc: Test UpdateGroupCheckStatus.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPatternTest008, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_VOID(stageManager);
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
    auto pageNode = stageManager->GetPageById(frameNode0->GetPageId());
    pattern0->UpdateGroupCheckStatus(frameNode0, pageNode, false);
    auto radioPaintProperty1 = frameNode1->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty1, nullptr);
    EXPECT_EQ(radioPaintProperty1->GetRadioCheckValue(), CHECKED);
}

/**
 * @tc.name: RadioPatternTest009
 * @tc.desc: Test InitClickEvent.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPatternTest009, TestSize.Level1)
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
HWTEST_F(RadioTestNg, RadioPatternTest010, TestSize.Level1)
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
HWTEST_F(RadioTestNg, RadioPatternTest011, TestSize.Level1)
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
HWTEST_F(RadioTestNg, RadioPatternTest012, TestSize.Level1)
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
HWTEST_F(RadioTestNg, RadioPatternTest013, TestSize.Level1)
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
HWTEST_F(RadioTestNg, RadioPatternTest014, TestSize.Level1)
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
HWTEST_F(RadioTestNg, RadioPatternTest015, TestSize.Level1)
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
    EXPECT_TRUE(select1);
}

/**
 * @tc.name: RadioPatternTest016
 * @tc.desc: Test OnClick.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPatternTest016, TestSize.Level1)
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
    EXPECT_TRUE(select1);
}

/**
 * @tc.name: RadioPatternTest019
 * @tc.desc: Test OnTouchDown and OnTouchUp.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPatternTest019, TestSize.Level1)
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
HWTEST_F(RadioTestNg, RadioPatternTest020, TestSize.Level1)
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
 * @tc.name: RadioPatternTest021
 * @tc.desc: Test Radio OnModifyDone default margin.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPatternTest021, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto radioPattern = frameNode->GetPattern<RadioPattern>();
    EXPECT_NE(radioPattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto radioTheme = AceType::MakeRefPtr<RadioTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(radioTheme));

    MarginProperty margin;
    margin.left = CalcLength(HORIZONTAL_PADDING.ConvertToPx());
    layoutProperty->UpdateMargin(margin); // GetMarginProperty

    radioPattern->OnModifyDone();
    EXPECT_EQ(layoutProperty->GetMarginProperty()->left.value(), CalcLength(HORIZONTAL_PADDING.ConvertToPx()));
    EXPECT_EQ(layoutProperty->GetMarginProperty()->right.value(),
        CalcLength(radioTheme->GetHotZoneHorizontalPadding().Value()));
    EXPECT_EQ(
        layoutProperty->GetMarginProperty()->top.value(), CalcLength(radioTheme->GetHotZoneVerticalPadding().Value()));
    EXPECT_EQ(layoutProperty->GetMarginProperty()->bottom.value(),
        CalcLength(radioTheme->GetHotZoneVerticalPadding().Value()));

    MarginProperty margin1;
    margin1.right = CalcLength(HORIZONTAL_PADDING.ConvertToPx());
    layoutProperty->UpdateMargin(margin1); // GetMarginProperty

    radioPattern->OnModifyDone();
    EXPECT_EQ(layoutProperty->GetMarginProperty()->right.value(), CalcLength(HORIZONTAL_PADDING.ConvertToPx()));
    EXPECT_EQ(layoutProperty->GetMarginProperty()->left.value(),
        CalcLength(radioTheme->GetHotZoneHorizontalPadding().Value()));
    EXPECT_EQ(
        layoutProperty->GetMarginProperty()->top.value(), CalcLength(radioTheme->GetHotZoneVerticalPadding().Value()));
    EXPECT_EQ(layoutProperty->GetMarginProperty()->bottom.value(),
        CalcLength(radioTheme->GetHotZoneVerticalPadding().Value()));
}

/**
 * @tc.name: RadioPaintMethodTest001
 * @tc.desc: Test Radio PaintMethod PaintRadio.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPaintMethodTest001, TestSize.Level1)
{
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto radioPaintProperty = AceType::MakeRefPtr<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, radioPaintProperty);
    auto radioModifier = AceType::MakeRefPtr<RadioModifier>();
    RadioPaintMethod radioPaintMethod(radioModifier);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(3);
    radioPaintMethod.radioModifier_->PaintRadio(canvas, false, CONTENT_SIZE, CONTENT_OFFSET);
}

/**
 * @tc.name: RadioPaintMethodTest002
 * @tc.desc: Test Radio PaintMethod PaintRadio.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPaintMethodTest002, TestSize.Level1)
{
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto radioPaintProperty = AceType::MakeRefPtr<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, radioPaintProperty);
    auto radioModifier = AceType::MakeRefPtr<RadioModifier>();
    RadioPaintMethod radioPaintMethod(radioModifier);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(3);
    radioPaintMethod.radioModifier_->enabled_ = AceType::MakeRefPtr<PropertyBool>(false);
    radioPaintMethod.radioModifier_->PaintRadio(canvas, false, CONTENT_SIZE, CONTENT_OFFSET);
    radioPaintMethod.radioModifier_->enabled_ = AceType::MakeRefPtr<PropertyBool>(true);
}

/**
 * @tc.name: RadioPaintMethodTest003
 * @tc.desc: Test Radio PaintMethod PaintRadio.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPaintMethodTest003, TestSize.Level1)
{
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto radioPaintProperty = AceType::MakeRefPtr<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, radioPaintProperty);
    auto radioModifier = AceType::MakeRefPtr<RadioModifier>();
    RadioPaintMethod radioPaintMethod(radioModifier);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(4);
    radioPaintMethod.radioModifier_->uiStatus_ =
        AceType::MakeRefPtr<PropertyInt>(static_cast<int32_t>(UIStatus::SELECTED));
    radioPaintMethod.radioModifier_->PaintRadio(canvas, false, CONTENT_SIZE, CONTENT_OFFSET);
    radioPaintMethod.radioModifier_->uiStatus_ =
        AceType::MakeRefPtr<PropertyInt>(static_cast<int32_t>(UIStatus::UNSELECTED));
}

/**
 * @tc.name: RadioPaintMethodTest004
 * @tc.desc: Test Radio PaintMethod PaintRadio.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPaintMethodTest004, TestSize.Level1)
{
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto radioPaintProperty = AceType::MakeRefPtr<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, radioPaintProperty);
    auto radioModifier = AceType::MakeRefPtr<RadioModifier>();
    RadioPaintMethod radioPaintMethod(radioModifier);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(4);
    radioPaintMethod.radioModifier_->enabled_ = AceType::MakeRefPtr<PropertyBool>(false);
    radioPaintMethod.radioModifier_->uiStatus_ =
        AceType::MakeRefPtr<PropertyInt>(static_cast<int32_t>(UIStatus::SELECTED));
    radioPaintMethod.radioModifier_->PaintRadio(canvas, false, CONTENT_SIZE, CONTENT_OFFSET);
    radioPaintMethod.radioModifier_->enabled_ = AceType::MakeRefPtr<PropertyBool>(true);
    radioPaintMethod.radioModifier_->uiStatus_ =
        AceType::MakeRefPtr<PropertyInt>(static_cast<int32_t>(UIStatus::UNSELECTED));
}

/**
 * @tc.name: RadioPaintMethodTest005
 * @tc.desc: Test Radio UpdateAnimatableProperty and SetBoardColor.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPaintMethodTest005, TestSize.Level1)
{
    auto radioModifier = AceType::MakeRefPtr<RadioModifier>();
    radioModifier->hoverColor_ = Color::RED;
    radioModifier->clickEffectColor_ = Color::BLUE;
    radioModifier->touchHoverType_ = TouchHoverAnimationType::HOVER;
    radioModifier->UpdateAnimatableProperty();
    radioModifier->animateTouchHoverColor_ =
        AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(Color::TRANSPARENT));
    radioModifier->touchHoverType_ = TouchHoverAnimationType::PRESS_TO_HOVER;
    radioModifier->UpdateAnimatableProperty();
    EXPECT_EQ(radioModifier->animateTouchHoverColor_->Get(), LinearColor(Color::RED));
    radioModifier->touchHoverType_ = TouchHoverAnimationType::NONE;
    radioModifier->UpdateAnimatableProperty();
    EXPECT_EQ(radioModifier->animateTouchHoverColor_->Get(), LinearColor(Color::RED.BlendOpacity(0)));
    radioModifier->touchHoverType_ = TouchHoverAnimationType::HOVER_TO_PRESS;
    radioModifier->UpdateAnimatableProperty();
    EXPECT_EQ(radioModifier->animateTouchHoverColor_->Get(), LinearColor(Color::BLUE));
    radioModifier->touchHoverType_ = TouchHoverAnimationType::PRESS;
    radioModifier->UpdateAnimatableProperty();
    EXPECT_EQ(radioModifier->animateTouchHoverColor_->Get(), LinearColor(Color::BLUE));
}

/**
 * @tc.name: RadioPaintMethodTest006
 * @tc.desc: Test Radio UpdateIsOnAnimatableProperty.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPaintMethodTest006, TestSize.Level1)
{
    auto radioModifier = AceType::MakeRefPtr<RadioModifier>();
    radioModifier->isOnAnimationFlag_->Set(true);
    radioModifier->UpdateIsOnAnimatableProperty(true);
    EXPECT_EQ(radioModifier->pointScale_->Get(), 0.5);
    EXPECT_EQ(radioModifier->ringPointScale_->Get(), 0);
    radioModifier->isOnAnimationFlag_->Set(false);
    radioModifier->UpdateIsOnAnimatableProperty(true);
    EXPECT_EQ(radioModifier->pointScale_->Get(), 0);
    EXPECT_EQ(radioModifier->ringPointScale_->Get(), 1);
}

/**
 * @tc.name: RadioPaintMethodTest007
 * @tc.desc: Test Radio PaintMethod UpdateContentModifier.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPaintMethodTest007, TestSize.Level1)
{
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto radioPaintProperty = AceType::MakeRefPtr<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, radioPaintProperty);
    auto radioModifier = AceType::MakeRefPtr<RadioModifier>();
    RadioPaintMethod radioPaintMethod(radioModifier);

    radioPaintMethod.radioModifier_->SetIsCheck(true);
    radioPaintMethod.isFirstCreated_ = true;
    radioPaintMethod.UpdateContentModifier(&paintWrapper);
    EXPECT_EQ(radioPaintMethod.radioModifier_->uiStatus_->Get(), static_cast<int32_t>(UIStatus::SELECTED));
    radioPaintMethod.radioModifier_->SetIsCheck(true);
    radioPaintMethod.isFirstCreated_ = false;
    radioPaintMethod.UpdateContentModifier(&paintWrapper);
    EXPECT_EQ(radioPaintMethod.radioModifier_->uiStatus_->Get(), static_cast<int32_t>(UIStatus::UNSELECTED));

    auto paintProperty = AccessibilityManager::DynamicCast<RadioPaintProperty>(paintWrapper.GetPaintProperty());
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateRadioCheck(true);
    radioPaintMethod.UpdateContentModifier(&paintWrapper);
    EXPECT_EQ(radioPaintMethod.radioModifier_->uiStatus_->Get(), static_cast<int32_t>(UIStatus::SELECTED));
}

/**
 * @tc.name: RadioLayoutAlgorithmTest001
 * @tc.desc: Verify that RadioLayoutAlgorithm can correctly InitializeParam.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioLayoutAlgorithmTest001, TestSize.Level1)
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
HWTEST_F(RadioTestNg, RadioLayoutAlgorithmTest002, TestSize.Level1)
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
HWTEST_F(RadioTestNg, RadioLayoutAlgorithmTest003, TestSize.Level1)
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
HWTEST_F(RadioTestNg, RadioLayoutAlgorithmTest004, TestSize.Level1)
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
HWTEST_F(RadioTestNg, RadioLayoutAlgorithmTest005, TestSize.Level1)
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
HWTEST_F(RadioTestNg, RadioLayoutAlgorithmTest006, TestSize.Level1)
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
HWTEST_F(RadioTestNg, RadioLayoutAlgorithmTest007, TestSize.Level1)
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
HWTEST_F(RadioTestNg, RadioLayoutAlgorithmTest008, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RadioTheme>()));
    LayoutWrapper layoutWrapper(nullptr, nullptr, nullptr);
    RadioLayoutAlgorithm radioLayoutAlgorithm;
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetHeight(COMPONENT_HEIGHT_INVALID);
    auto size = radioLayoutAlgorithm.MeasureContent(layoutConstraintSize, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(size.value(), SizeF(0, 0));
}

/**
 * @tc.name: RadioAccessibilityPropertyTestNg001
 * @tc.desc: Test the IsCheckable property of Radio.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioAccessibilityPropertyTestNg001, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(std::nullopt, std::nullopt);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto accessibility = frameNode->GetAccessibilityProperty<RadioAccessibilityProperty>();
    ASSERT_NE(accessibility, nullptr);
    EXPECT_TRUE(accessibility->IsCheckable());
}

/**
 * @tc.name: RadioAccessibilityPropertyTestNg002
 * @tc.desc: Test the IsChecked property of Radio.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioAccessibilityPropertyTestNg002, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(std::nullopt, std::nullopt);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto paintProperty = frameNode->GetPaintProperty<NG::RadioPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateRadioCheck(true);
    auto accessibility = frameNode->GetAccessibilityProperty<RadioAccessibilityProperty>();
    ASSERT_NE(accessibility, nullptr);
    EXPECT_TRUE(accessibility->IsChecked());

    paintProperty->UpdateRadioCheck(false);
    EXPECT_FALSE(accessibility->IsChecked());
}

/**
 * @tc.name: RadioAccessibilityPropertyTestNg003
 * @tc.desc: Test the Text property of Radio.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioAccessibilityPropertyTestNg003, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(std::nullopt, std::nullopt);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto radioEventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    ASSERT_NE(radioEventHub, nullptr);
    radioEventHub->SetValue(VALUE);

    auto accessibility = frameNode->GetAccessibilityProperty<RadioAccessibilityProperty>();
    ASSERT_NE(accessibility, nullptr);
    EXPECT_EQ(accessibility->GetText(), VALUE);
}

/**
 * @tc.name: RadioPatternTest022
 * @tc.desc: Test Radio OnKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPatternTest022, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto radioPattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(radioPattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();

    auto eventHub = frameNode->GetFocusHub();
    ASSERT_NE(eventHub, nullptr);
    /**
     * test event.action != KeyAction::DOWN
     */
    KeyEvent keyEventOne(KeyCode::KEY_A, KeyAction::UP);
    eventHub->onKeyEventInternal_(keyEventOne);
    /**
     * test event.action == KeyAction::DOWN and event.code == KeyCode::KEY_ENTER
     */
    KeyEvent keyEventTwo(KeyCode::KEY_A, KeyAction::DOWN);
    eventHub->onKeyEventInternal_(keyEventTwo);
    /**
     * test event.action == KeyAction::DOWN and event.code != KeyCode::KEY_ENTER
     */
    KeyEvent keyEventThr(KeyCode::KEY_ENTER, KeyAction::DOWN);
    eventHub->onKeyEventInternal_(keyEventThr);
}

/**
 * @tc.name: RadioPatternTest023
 * @tc.desc: Test Radio SetInnerFocusPaintRectCallback.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPatternTest023, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto radioPattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(radioPattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();

    auto eventHub = frameNode->GetFocusHub();
    ASSERT_NE(eventHub, nullptr);

    RoundRect paintRect;
    eventHub->getInnerFocusRectFunc_(paintRect);
}

/**
 * @tc.name: RadioPatternTest024
 * @tc.desc: Test Radio Pattern Methods.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPatternTest024, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto radioPattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(radioPattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);

    RefPtr<LayoutWrapper> layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, layoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    /**
     * cover OnDirtyLayoutWrapperSwap
     */
    DirtySwapConfig dirtySwapConfig;
    auto result = radioPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    EXPECT_TRUE(result);
    /**
     * cover AddHotZoneRect
     */
    radioPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    EXPECT_EQ(frameNode->GetOrCreateGestureEventHub()->isResponseRegion_, true);
    /**
     * cover RemoveLastHotZoneRect
     */
    radioPattern->RemoveLastHotZoneRect();
    EXPECT_EQ(frameNode->GetOrCreateGestureEventHub()->isResponseRegion_, false);
}

/**
 * @tc.name: RadioPatternTest025
 * @tc.desc: Test Radio Events.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPatternTest025, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto radioPattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(radioPattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    /**
     * fire click event
     */
    gesture->ActClick();
    /**
     * fire touch event
     */
    auto touchEventActuator = gesture->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    auto events = touchEventActuator->touchEvents_;
    TouchEventInfo info("onTouch");
    TouchLocationInfo touchInfo1(1);
    touchInfo1.SetTouchType(TouchType::DOWN);
    info.AddTouchLocationInfo(std::move(touchInfo1));
    EXPECT_NE(events.size(), 0);
    for (auto event : events) {
        event->callback_(info);
    }
    TouchEventInfo info2("onTouch");
    TouchLocationInfo touchInfo2(1);
    touchInfo2.SetTouchType(TouchType::UP);
    info2.AddTouchLocationInfo(std::move(touchInfo2));
    EXPECT_NE(events.size(), 0);
    for (auto event : events) {
        event->callback_(info2);
    }
    /**
     * fire mouse event
     */
    auto eventHub = frameNode->GetEventHub<RadioEventHub>();
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    auto hoverEventActuator = inputHub->hoverEventActuator_;
    ASSERT_NE(hoverEventActuator, nullptr);
    auto mouseEvents = hoverEventActuator->inputEvents_;
    ASSERT_NE(mouseEvents.size(), 0);
    for (const auto& callback : mouseEvents) {
        (*callback)(false);
    }
}

/**
 * @tc.name: RadioPatternTest026
 * @tc.desc: Test Radio OnDetachFromFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPatternTest026, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto stageManager = AceType::MakeRefPtr<StageManager>(frameNode);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->stageManager_ = stageManager;

    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnDetachFromFrameNode(AceType::RawPtr(frameNode));
}

/**
 * @tc.name: RadioPatternTest027
 * @tc.desc: Test Radio onModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPatternTest027, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto stageManager = AceType::MakeRefPtr<StageManager>(frameNode);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->stageManager_ = stageManager;
    frameNode->MarkModifyDone();

    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    pattern->SetPreGroup(GROUP_NAME);
    paintProperty->UpdateRadioCheck(true);
    frameNode->MarkModifyDone();
    pattern->SetPreGroup(GROUP_NAME_CHANGE);
    paintProperty->UpdateRadioCheck(false);
    frameNode->MarkModifyDone();
}

/**
 * @tc.name: RadioEventHubChangeEventTest001
 * @tc.desc: Set Radio value into RadioEventHub and get it.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioEventHubChangeEventTest001, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(std::nullopt, std::nullopt);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onChange = [](const bool check) { EXPECT_TRUE(check); };
    radioModelNG.SetOnChangeEvent(onChange);
    eventHub->SetOnChangeEvent(std::move(onChange));
    eventHub->UpdateChangeEvent(true);
}

/**
 * @tc.name: RadioPatternTest028
 * @tc.desc: Test the distributed capability of Radio.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPatternTest028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    /**
     * @tc.steps: step2. Get pattern .
     * @tc.expected: Function ProvideRestoreInfo is called.
     */
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto radioPaintProperty = pattern->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    radioPaintProperty->UpdateRadioCheck(false);
    std::string ret = pattern->ProvideRestoreInfo();
    EXPECT_TRUE(ret == R"({"checked":false})");

    /**
     * @tc.steps: step3. Function OnRestoreInfo is called.
     * @tc.expected: Passing invalid & valid JSON format.
     */
    std::string restoreInfo_ = R"({"checked":true})";
    pattern->OnRestoreInfo(restoreInfo_);
    EXPECT_TRUE(radioPaintProperty->GetRadioCheckValue(false));
    restoreInfo_ = "invalid_json_string";
    pattern->OnRestoreInfo(restoreInfo_);
    ASSERT_NE(radioPaintProperty, nullptr);
    EXPECT_TRUE(radioPaintProperty->GetRadioCheckValue(false));
}
} // namespace OHOS::Ace::NG
