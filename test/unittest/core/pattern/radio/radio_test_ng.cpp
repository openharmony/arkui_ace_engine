/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#include "test/unittest/core/pattern/test_ng.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "ui/resource/resource_info.h"

#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "core/components_ng/pattern/radio/radio_model_ng.h"
#include "core/components_ng/pattern/radio/radio_paint_property.h"
#include "core/components_ng/pattern/radio/radio_pattern.h"
#include "core/components_ng/pattern/stage/stage_manager.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/core/common/mock_container.h"

using namespace testing;
using namespace testing::ext;
using RadioBuilderFunc = std::function<void()>;
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
const std::optional<int32_t> INDICATOR_TYPE_TICK = 0;
const OHOS::Ace::NG::TouchHoverAnimationType INVALID_TOUCH_HOVER_ANIMARION_TYPE = TouchHoverAnimationType(100);
constexpr double NUM_TWO = 2.0;
const SizeF CHILD_FRAME_SIZE = SizeF(50.0, 50.0);
constexpr Dimension FOCUSBGSIZE = 2.0_vp;
const int32_t VERSION_TWELVE = 12;
const SizeF TEST_SIZE_0 = SizeF(0.0f, 0.0f);
const SizeF TEST_SIZE_100_200 = SizeF(100.0f, 200.0f);
const SizeF TEST_SIZE_100 = SizeF(100.0f, 100.0f);
const SizeF TEST_SIZE_200 = SizeF(200.0f, 200.0f);
const SizeF TEST_SIZE_50 = SizeF(50.0f, 50.0f);
const SizeF TEST_SIZE_60 = SizeF(60.0f, 60.0f);
constexpr float TEST_WIDTH_50 = 50.0f;
constexpr float TEST_HEIGHT_60 = 60.0f;
} // namespace

class RadioTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    static RadioBuilderFunc RadioBuilder();
};

void RadioTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        auto radioTheme = AceType::MakeRefPtr<RadioTheme>();
        radioTheme->hotZoneHorizontalPadding_ = HORIZONTAL_PADDING;
        radioTheme->hotZoneVerticalPadding_ = VERTICAL_PADDING;
        radioTheme->defaultWidth_ = DEFAULT_WIDTH_DIMENSION;
        radioTheme->defaultHeight_ = DEFAULT_HEIGHT_DIMENSION;
        return radioTheme;
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    MockContainer::SetUp();
}

void RadioTestNg::TearDownTestSuite()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: RadioPaintPropertyTest001
 * @tc.desc: Set Radio value into RadioPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPaintPropertyTest001, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
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
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    radioModelNG.SetCheckedBackgroundColor(NORMAL_COLOR);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    EXPECT_EQ(radioPaintProperty->GetRadioCheckedBackgroundColorValue(), NORMAL_COLOR);

    RadioModelNG radioModelNG2;
    radioModelNG2.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
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
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    radioModelNG.SetUncheckedBorderColor(NORMAL_COLOR);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    EXPECT_EQ(radioPaintProperty->GetRadioUncheckedBorderColorValue(), NORMAL_COLOR);

    RadioModelNG radioModelNG2;
    radioModelNG2.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
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
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    radioModelNG.SetIndicatorColor(NORMAL_COLOR);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    EXPECT_EQ(radioPaintProperty->GetRadioIndicatorColorValue(), NORMAL_COLOR);

    RadioModelNG radioModelNG2;
    radioModelNG2.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG2.SetChecked(true);
    radioModelNG2.SetIndicatorColor(ERROR_COLOR);
    auto frameNode2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode2, nullptr);
    auto radioPaintProperty2 = frameNode2->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty2, nullptr);
    EXPECT_EQ(radioPaintProperty2->GetRadioIndicatorColorValue(), ERROR_COLOR);
}

/**
 * @tc.name: RadioPaintPropertyTest005
 * @tc.desc: Test SetRadioIndicator.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPaintPropertyTest005, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetRadioIndicator(INDICATOR_TYPE_TICK.value());
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    EXPECT_EQ(radioPaintProperty->GetRadioIndicator(), INDICATOR_TYPE_TICK);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
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
    radioModelNG.Create(std::nullopt, std::nullopt, std::nullopt);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::RadioEventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_TRUE(eventHub->GetValue().empty());
    EXPECT_TRUE(eventHub->GetGroup().empty());
    /**
     * @tc.cases: case2. RadioPattern can Create with value and group.
     */
    RadioModelNG radioModelNG2;
    radioModelNG2.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub2 = frameNode2->GetOrCreateEventHub<NG::RadioEventHub>();
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
    radioModelNG.Create(std::nullopt, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::RadioEventHub>();
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
    radioModelNG.Create(NAME, std::nullopt, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::RadioEventHub>();
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
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    bool isChecked = false;
    auto onChange = [&isChecked](bool select) { isChecked = select; };
    radioModelNG.SetOnChange(onChange);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::RadioEventHub>();
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
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(frameNode->GetLayoutProperty()->GetMarginProperty()->left.value(), CalcLength(HORIZONTAL_PADDING));
    EXPECT_EQ(frameNode->GetLayoutProperty()->GetMarginProperty()->right.value(), CalcLength(HORIZONTAL_PADDING));
    EXPECT_EQ(frameNode->GetLayoutProperty()->GetMarginProperty()->top.value(), CalcLength(VERTICAL_PADDING));
    EXPECT_EQ(frameNode->GetLayoutProperty()->GetMarginProperty()->bottom.value(), CalcLength(VERTICAL_PADDING));
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
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    bool isChecked = false;
    auto onChange = [&isChecked](bool select) { isChecked = select; };
    radioModelNG.SetOnChange(onChange);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->preCheck_ = false;
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
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
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

    /**
     * @tc.cases: case. cover branch preCheck_ is true.
     */
    pattern->preCheck_ = true;
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
    radioModelNG0.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
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
    ASSERT_EQ(pageNode, nullptr);
    auto pageEventHub = AceType::MakeRefPtr<NG::PageEventHub>();
    auto groupManager = pageEventHub->GetGroupManager();
    pattern0->UpdateGroupCheckStatus(frameNode0, groupManager, false);
    EXPECT_FALSE(radioPaintProperty->GetRadioCheckValue());
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
    auto eventHub0 = frameNode0->GetOrCreateEventHub<NG::RadioEventHub>();
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
    auto eventHub1 = frameNode1->GetOrCreateEventHub<NG::RadioEventHub>();
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
    auto pageEventHub = AceType::MakeRefPtr<NG::PageEventHub>();
    auto groupManager = pageEventHub->GetGroupManager();
    pattern0->UpdateGroupCheckStatus(frameNode0, groupManager, true);
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
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
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
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
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
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
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
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
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
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
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
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
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
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
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
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
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
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
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
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
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
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto radioPattern = frameNode->GetPattern<RadioPattern>();
    EXPECT_NE(radioPattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();

    MarginProperty margin;
    margin.left = CalcLength(HORIZONTAL_PADDING);
    layoutProperty->UpdateMargin(margin); // GetMarginProperty

    radioPattern->OnModifyDone();
    EXPECT_EQ(layoutProperty->GetMarginProperty()->left.value(), CalcLength(HORIZONTAL_PADDING));
    EXPECT_EQ(layoutProperty->GetMarginProperty()->right.value(), CalcLength(HORIZONTAL_PADDING));
    EXPECT_EQ(layoutProperty->GetMarginProperty()->top.value(), CalcLength(VERTICAL_PADDING));
    EXPECT_EQ(layoutProperty->GetMarginProperty()->bottom.value(), CalcLength(VERTICAL_PADDING));

    MarginProperty margin1;
    margin1.right = CalcLength(HORIZONTAL_PADDING);
    layoutProperty->UpdateMargin(margin1); // GetMarginProperty

    radioPattern->OnModifyDone();
    EXPECT_EQ(layoutProperty->GetMarginProperty()->right.value(), CalcLength(HORIZONTAL_PADDING));
    EXPECT_EQ(layoutProperty->GetMarginProperty()->left.value(), CalcLength(HORIZONTAL_PADDING));
    EXPECT_EQ(layoutProperty->GetMarginProperty()->top.value(), CalcLength(VERTICAL_PADDING));
    EXPECT_EQ(layoutProperty->GetMarginProperty()->bottom.value(), CalcLength(VERTICAL_PADDING));
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
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(4);
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
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(4);
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
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(5);
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
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(5);
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
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::RADIO_ETS_TAG, 0, []() { return AceType::MakeRefPtr<RadioPattern>(); });
    auto radioModifier = AceType::MakeRefPtr<RadioModifier>();
    radioModifier->hoverColor_ = Color::RED;
    radioModifier->clickEffectColor_ = Color::BLUE;
    radioModifier->touchHoverType_ = TouchHoverAnimationType::HOVER;
    radioModifier->UpdateAnimatableProperty(frameNode);
    radioModifier->animateTouchHoverColor_ =
        AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(Color::TRANSPARENT));
    radioModifier->touchHoverType_ = TouchHoverAnimationType::PRESS_TO_HOVER;
    radioModifier->UpdateAnimatableProperty(frameNode);
    EXPECT_EQ(radioModifier->animateTouchHoverColor_->Get(), LinearColor(Color::RED));
    radioModifier->touchHoverType_ = TouchHoverAnimationType::NONE;
    radioModifier->UpdateAnimatableProperty(frameNode);
    EXPECT_EQ(radioModifier->animateTouchHoverColor_->Get(), LinearColor(Color::RED.BlendOpacity(0)));
    radioModifier->touchHoverType_ = TouchHoverAnimationType::HOVER_TO_PRESS;
    radioModifier->UpdateAnimatableProperty(frameNode);
    EXPECT_EQ(radioModifier->animateTouchHoverColor_->Get(), LinearColor(Color::BLUE));
    radioModifier->touchHoverType_ = TouchHoverAnimationType::PRESS;
    radioModifier->UpdateAnimatableProperty(frameNode);
    EXPECT_EQ(radioModifier->animateTouchHoverColor_->Get(), LinearColor(Color::BLUE));

    /**
     * @tc.cases: case. cover branch default touchHoverType_.
     */
    radioModifier->touchHoverType_ = INVALID_TOUCH_HOVER_ANIMARION_TYPE;
    radioModifier->UpdateAnimatableProperty(frameNode);
    EXPECT_EQ(radioModifier->animateTouchHoverColor_->Get(), LinearColor(Color::BLUE));
}

/**
 * @tc.name: RadioPaintMethodTest006
 * @tc.desc: Test Radio UpdateIsOnAnimatableProperty.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPaintMethodTest006, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::RADIO_ETS_TAG, 0, []() { return AceType::MakeRefPtr<RadioPattern>(); });
    auto radioModifier = AceType::MakeRefPtr<RadioModifier>();
    radioModifier->isOnAnimationFlag_->Set(true);
    radioModifier->UpdateIsOnAnimatableProperty(true, frameNode);
    EXPECT_EQ(radioModifier->pointScale_->Get(), 0.5);
    EXPECT_EQ(radioModifier->ringPointScale_->Get(), 0);
    radioModifier->isOnAnimationFlag_->Set(false);
    radioModifier->UpdateIsOnAnimatableProperty(true, frameNode);
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
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::RADIO_ETS_TAG, 0, []() { return AceType::MakeRefPtr<RadioPattern>(); });
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto radioPaintProperty = AceType::MakeRefPtr<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    PaintWrapper paintWrapper(frameNode->GetRenderContext(), geometryNode, radioPaintProperty);
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
 * @tc.name: RadioPaintMethodTest008
 * @tc.desc: Test Radio PaintMethod PaintIndicator.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPaintMethodTest008, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
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
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(5);
    radioPaintMethod.radioModifier_->enabled_ = AceType::MakeRefPtr<PropertyBool>(true);
    radioPaintMethod.radioModifier_->uiStatus_ =
        AceType::MakeRefPtr<PropertyInt>(static_cast<int32_t>(UIStatus::SELECTED));
    radioPaintMethod.radioModifier_->PaintIndicator(canvas, false, CONTENT_SIZE, CONTENT_OFFSET);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: RadioPaintMethodTest009
 * @tc.desc: Test Radio PaintMethod PaintIndicator.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPaintMethodTest009, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
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
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(5);
    radioPaintMethod.radioModifier_->enabled_ = AceType::MakeRefPtr<PropertyBool>(true);
    radioPaintMethod.radioModifier_->uiStatus_ =
        AceType::MakeRefPtr<PropertyInt>(static_cast<int32_t>(UIStatus::UNSELECTED));
    radioPaintMethod.radioModifier_->PaintIndicator(canvas, false, CONTENT_SIZE, CONTENT_OFFSET);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: RadioPaintMethodTest010
 * @tc.desc: Test Radio UpdateIndicatorAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPaintMethodTest010, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::RADIO_ETS_TAG, 0, []() { return AceType::MakeRefPtr<RadioPattern>(); });
    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    auto radioModifier = AceType::MakeRefPtr<RadioModifier>();
    radioModifier->isOnAnimationFlag_->Set(true);
    radioModifier->UpdateIndicatorAnimation(true, frameNode);
    EXPECT_EQ(radioModifier->opacityScale_->Get(), 1);
    EXPECT_EQ(radioModifier->borderOpacityScale_->Get(), 0);
    radioModifier->isOnAnimationFlag_->Set(false);
    radioModifier->UpdateIndicatorAnimation(false, frameNode);
    EXPECT_EQ(radioModifier->opacityScale_->Get(), 0);
    EXPECT_EQ(radioModifier->borderOpacityScale_->Get(), 1);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: RadioPaintMethodTest011
 * @tc.desc: Test Radio PaintMethod DrawFocusBoard.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPaintMethodTest011, TestSize.Level1)
{
    int32_t settingApiVersion = 11;
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(settingApiVersion);
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
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    radioModifier->SetIsFocused(true);
    radioPaintMethod.radioModifier_->DrawFocusBoard(canvas, CONTENT_SIZE, CONTENT_OFFSET);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: RadioPaintMethodTest012
 * @tc.desc: Test Radio PaintMethod DrawFocusBoard.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPaintMethodTest012, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(settingApiVersion);
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
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    radioPaintMethod.radioModifier_->enabled_ = AceType::MakeRefPtr<PropertyBool>(true);
    radioModifier->SetIsFocused(true);
    radioPaintMethod.radioModifier_->DrawFocusBoard(canvas, CONTENT_SIZE, CONTENT_OFFSET);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: RadioLayoutAlgorithmTest001
 * @tc.desc: Verify that RadioLayoutAlgorithm can correctly InitializeParam.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioLayoutAlgorithmTest001, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(std::nullopt, std::nullopt, std::nullopt);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    RadioLayoutAlgorithm radioLayoutAlgorithm;
    radioLayoutAlgorithm.InitializeParam(frameNode);
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
    RadioModelNG radioModelNG;
    radioModelNG.Create(std::nullopt, std::nullopt, std::nullopt);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    LayoutWrapperNode layoutWrapper(frameNode, nullptr, nullptr);
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
    RadioModelNG radioModelNG;
    radioModelNG.Create(std::nullopt, std::nullopt, std::nullopt);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    LayoutWrapperNode layoutWrapper(frameNode, nullptr, nullptr);
    RadioLayoutAlgorithm radioLayoutAlgorithm;
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetWidth(COMPONENT_WIDTH);
    auto size = radioLayoutAlgorithm.MeasureContent(layoutConstraintSize, &layoutWrapper);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutProperty->calcLayoutConstraint_->selfIdealSize->Reset();
    layoutProperty->calcLayoutConstraint_->selfIdealSize->width_ = CalcLength(COMPONENT_WIDTH);
    auto context = frameNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto theme = context->GetTheme<RadioTheme>();
    pattern->GetChildContentSize(theme);
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
    RadioModelNG radioModelNG;
    radioModelNG.Create(std::nullopt, std::nullopt, std::nullopt);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    LayoutWrapperNode layoutWrapper(frameNode, nullptr, nullptr);
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
    RadioModelNG radioModelNG;
    radioModelNG.Create(std::nullopt, std::nullopt, std::nullopt);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    LayoutWrapperNode layoutWrapper(frameNode, nullptr, AccessibilityManager::MakeRefPtr<LayoutProperty>());
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
    RadioModelNG radioModelNG;
    radioModelNG.Create(std::nullopt, std::nullopt, std::nullopt);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode, nullptr, AccessibilityManager::MakeRefPtr<LayoutProperty>());
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
    RadioModelNG radioModelNG;
    radioModelNG.Create(std::nullopt, std::nullopt, std::nullopt);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode, nullptr, AccessibilityManager::MakeRefPtr<LayoutProperty>());
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
    RadioModelNG radioModelNG;
    radioModelNG.Create(std::nullopt, std::nullopt, std::nullopt);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode, nullptr, AccessibilityManager::MakeRefPtr<LayoutProperty>());
    RadioLayoutAlgorithm radioLayoutAlgorithm;
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetHeight(COMPONENT_HEIGHT_INVALID);
    auto size = radioLayoutAlgorithm.MeasureContent(layoutConstraintSize, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(size.value(), SizeF(0, 0));
}

/**
 * @tc.name: RadioPaintMethodTest013
 * @tc.desc: Verify that radioModifier can correctly InitializeParam.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPaintMethodTest013, TestSize.Level1)
{
    /**
     * @tc.steps: MockContainer.apiTargetVersion_ = VERSION_TWELVE.
     * @tc.steps: set radio theme
     */
    MockContainer::SetUp();
    MockContainer::Current()->SetApiTargetVersion(VERSION_TWELVE);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        auto radioTheme = AceType::MakeRefPtr<RadioTheme>();
        radioTheme->focusedBgUnchecked_ = NORMAL_COLOR;
        radioTheme->focusedRingUnchecked_ = NORMAL_COLOR;
        radioTheme->focusedBgColor_ = NORMAL_COLOR;
        radioTheme->sizeFocusBg_ = FOCUSBGSIZE;
        return radioTheme;
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto radioModifier = AceType::MakeRefPtr<RadioModifier>();
    RadioPaintMethod radioPaintMethod(radioModifier);
    radioPaintMethod.radioModifier_->InitializeParam();
    EXPECT_EQ(radioPaintMethod.radioModifier_->focusedBgUnchecked_, NORMAL_COLOR);
    EXPECT_EQ(radioPaintMethod.radioModifier_->focusedRingUnchecked_, NORMAL_COLOR);
    EXPECT_EQ(radioPaintMethod.radioModifier_->focusedBgColor_, NORMAL_COLOR);
    EXPECT_EQ(radioPaintMethod.radioModifier_->sizeFocused_, FOCUSBGSIZE);
}

/**
 * @tc.name: RadioAccessibilityPropertyTestNg001
 * @tc.desc: Test the IsCheckable property of Radio.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioAccessibilityPropertyTestNg001, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(std::nullopt, std::nullopt, std::nullopt);
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
    radioModelNG.Create(std::nullopt, std::nullopt, std::nullopt);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto accessibility = frameNode->GetAccessibilityProperty<RadioAccessibilityProperty>();
    ASSERT_NE(accessibility, nullptr);
    EXPECT_FALSE(accessibility->IsChecked());
    auto paintProperty = frameNode->GetPaintProperty<NG::RadioPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateRadioCheck(true);
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
    radioModelNG.Create(std::nullopt, std::nullopt, std::nullopt);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto radioEventHub = frameNode->GetOrCreateEventHub<NG::RadioEventHub>();
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
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
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
    eventHub->ProcessOnKeyEventInternal(keyEventOne);
    /**
     * test event.action == KeyAction::DOWN and event.code == KeyCode::KEY_ENTER
     */
    KeyEvent keyEventTwo(KeyCode::KEY_A, KeyAction::DOWN);
    eventHub->ProcessOnKeyEventInternal(keyEventTwo);
    /**
     * test event.action == KeyAction::DOWN and event.code != KeyCode::KEY_ENTER
     */
    KeyEvent keyEventThr(KeyCode::KEY_ENTER, KeyAction::DOWN);
    eventHub->ProcessOnKeyEventInternal(keyEventThr);
}

/**
 * @tc.name: RadioPatternTest023
 * @tc.desc: Test Radio SetInnerFocusPaintRectCallback.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPatternTest023, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
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
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
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

    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
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
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
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
    auto touchCallback = [](TouchEventInfo& info) {};
    auto touchEvent = AceType::MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gesture->AddTouchEvent(touchEvent);
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
    auto eventHub = frameNode->GetOrCreateEventHub<RadioEventHub>();
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
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
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
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
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
    radioModelNG.Create(std::nullopt, std::nullopt, std::nullopt);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::RadioEventHub>();
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
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
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

/**
 * @tc.name: RadioPatternTest029
 * @tc.desc: Radio test Select and ClearSelection.
 */
HWTEST_F(RadioTestNg, RadioPatternTest029, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->preCheck_ = false;
    pattern->SetAccessibilityAction();

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<RadioAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_TRUE(accessibilityProperty->ActActionSelect());

    bool isSelected = true;
    pattern->preCheck_ = false;
    pattern->UpdateSelectStatus(isSelected);
    EXPECT_TRUE(accessibilityProperty->ActActionClearSelection());
}

RadioBuilderFunc RadioTestNg::RadioBuilder()
{
    return []() {
        ColumnModelNG colModel;
        colModel.Create(Dimension(0), nullptr, "");
        ViewAbstract::SetWidth(CalcLength(10.f));
        ViewAbstract::SetHeight(CalcLength(10.f));
    };
}

/**
 * @tc.name: RadioPatternTest030
 * @tc.desc: Radio test SetBuilder.
 */
HWTEST_F(RadioTestNg, RadioPatternTest030, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto radioFunc = RadioBuilder();
    radioModelNG.SetBuilder(std::move(radioFunc));
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->builder_, nullptr);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: RadioPatternTest031
 * @tc.desc: Radio test CreatechildNode.
 */
HWTEST_F(RadioTestNg, RadioPatternTest031, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto host = pattern->GetHost();
    pattern->OnModifyDone();
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: RadioPatternTest032
 * @tc.desc: SetRadioChecked and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPatternTest032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern radioChecked
     */
    pattern->SetRadioChecked(true);
    /**
     * @tc.steps: step3. Get paint property
     * @tc.expected: Check the Radio property value
     */

    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    bool isChecked = false;
    if (radioPaintProperty->HasRadioCheck()) {
        isChecked = radioPaintProperty->GetRadioCheckValue();
    } else {
        isChecked = false;
    }
    EXPECT_EQ(isChecked, true);
}

/**
 * @tc.name: RadioPatternTest033
 * @tc.desc: SetRadioChecked and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPatternTest033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern radioChecked
     */
    pattern->SetRadioChecked(false);
    /**
     * @tc.steps: step3. Get paint property
     * @tc.expected: Check the Radio property value
     */

    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    bool isChecked = false;
    if (radioPaintProperty->HasRadioCheck()) {
        isChecked = radioPaintProperty->GetRadioCheckValue();
    } else {
        isChecked = false;
    }
    EXPECT_EQ(isChecked, false);
}

/**
 * @tc.name: RadioPatternTest034
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPatternTest034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetRadioChecked(true);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(VALUE);
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(VALUE, config.value_);
                EXPECT_EQ(true, config.checked_);
                return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: RadioPatternTest035
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPatternTest035, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetRadioChecked(false);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(VALUE);

    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(VALUE, config.value_);
                EXPECT_EQ(false, config.checked_);
                return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: RadioPatternTest036
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPatternTest036, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create("", GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetRadioChecked(false);

    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ("", config.value_);
                EXPECT_EQ(false, config.checked_);
                return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: RadioPatternTest037
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPatternTest037, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create("", GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetRadioChecked(false);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(VALUE);
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(VALUE, config.value_);
                EXPECT_EQ(false, config.checked_);
                return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: RadioPatternTest038
 * @tc.desc: Test InitFocusEvent.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPatternTest038, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto radioModifier = AceType::MakeRefPtr<RadioModifier>();
    RadioPaintMethod radioPaintMethod(radioModifier);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitFocusEvent();
    pattern->AddIsFocusActiveUpdateEvent();
    pattern->OnIsFocusActiveUpdate(true);
    EXPECT_TRUE(radioModifier->isFocused_);
}

/**
 * @tc.name: RadioPatternTest039
 * @tc.desc: Test InitFocusEvent.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPatternTest039, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto radioModifier = AceType::MakeRefPtr<RadioModifier>();
    RadioPaintMethod radioPaintMethod(radioModifier);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitFocusEvent();
    pattern->RemoveIsFocusActiveUpdateEvent();
    pattern->OnIsFocusActiveUpdate(true);
    EXPECT_TRUE(radioModifier->isFocused_);
    int32_t settingApiVersion = 11;
    AceApplicationInfo::GetInstance().SetApiTargetVersion(settingApiVersion);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto radioPaintProperty = AceType::MakeRefPtr<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, radioPaintProperty);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    radioModifier->SetIsFocused(true);
    pattern->OnIsFocusActiveUpdate(true);
    radioPaintMethod.radioModifier_->enabled_ = AceType::MakeRefPtr<PropertyBool>(false);
    radioPaintMethod.radioModifier_->uiStatus_ =
        AceType::MakeRefPtr<PropertyInt>(static_cast<int32_t>(UIStatus::UNSELECTED));
    radioPaintMethod.radioModifier_->PaintRadio(canvas, false, CONTENT_SIZE, CONTENT_OFFSET);
}

/**
 * @tc.name: RadioPatternTest040
 * @tc.desc: Test InitFocusEvent.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPatternTest040, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto radioModifier = AceType::MakeRefPtr<RadioModifier>();
    RadioPaintMethod radioPaintMethod(radioModifier);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitFocusEvent();
    pattern->RemoveIsFocusActiveUpdateEvent();
    pattern->OnIsFocusActiveUpdate(true);
    EXPECT_TRUE(radioModifier->isFocused_);
    int32_t settingApiVersion = 11;
    AceApplicationInfo::GetInstance().SetApiTargetVersion(settingApiVersion);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto radioPaintProperty = AceType::MakeRefPtr<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, radioPaintProperty);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    radioModifier->SetIsFocused(true);
    pattern->OnIsFocusActiveUpdate(true);
    radioPaintMethod.radioModifier_->enabled_ = AceType::MakeRefPtr<PropertyBool>(true);
    radioPaintMethod.radioModifier_->uiStatus_ =
        AceType::MakeRefPtr<PropertyInt>(static_cast<int32_t>(UIStatus::UNSELECTED));
    radioPaintMethod.radioModifier_->PaintRadio(canvas, false, CONTENT_SIZE, CONTENT_OFFSET);
    radioPaintMethod.radioModifier_->PaintIndicator(canvas, false, CONTENT_SIZE, CONTENT_OFFSET);
}
/**
 * @tc.name: RadioPatternTest041
 * @tc.desc: Test InitFocusEvent.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPatternTest041, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto radioModifier = AceType::MakeRefPtr<RadioModifier>();
    RadioPaintMethod radioPaintMethod(radioModifier);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set radio focus and blur
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->SetIsFocusActive(true);
    pattern->HandleFocusEvent();
    pattern->AddIsFocusActiveUpdateEvent();
    pattern->OnIsFocusActiveUpdate(true);
    EXPECT_TRUE(radioModifier->isFocused_);
    pattern->HandleBlurEvent();
    pattern->RemoveIsFocusActiveUpdateEvent();
}

/**
 * @tc.name: RadioReverseLayout001
 * @tc.desc: Test for layout method of RadioLayoutAlgorithm to get the offset in the RTL scene,
             when Width and height are not set in the front end.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioReverseLayout001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node and add Image child.
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(std::nullopt, std::nullopt, std::nullopt);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto radioLayoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(radioLayoutProperty, nullptr);
    radioLayoutProperty->UpdateLayoutDirection(TextDirection::RTL);

    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    frameNode->MarkModifyDone();

    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->FlushBuildFinishCallbacks();
    auto childNode = pattern->builderChildNode_;
    ASSERT_NE(childNode, nullptr);
    auto hostGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper(frameNode, hostGeometryNode, radioLayoutProperty);
    auto childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> childWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(childNode, childGeometryNode, childNode->GetLayoutProperty());
    RadioLayoutAlgorithm radioLayoutAlgorithm;
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.maxSize = SizeF(1000.0, 1000.0);
    layoutConstraintSize.minSize = SizeF(0, 0);
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraintSize);
    layoutWrapper.AppendChild(childWrapper);

    /**
     * @tc.steps: step2. Measure Radio node Content size and child size.
     */
    layoutWrapper.GetGeometryNode()->SetFrameSize(CONTENT_SIZE);
    childWrapper->GetGeometryNode()->SetFrameSize(CHILD_FRAME_SIZE);

    /**
     * @tc.steps: step3. layout child node.
     */
    NG::OffsetF child_offset;
    auto align = Alignment::CENTER;
    child_offset.SetX((1.0 + align.GetHorizontal()) * (CONTENT_SIZE.Width() - CHILD_FRAME_SIZE.Width()) / NUM_TWO);
    child_offset.SetY((1.0 + align.GetVertical()) * (CONTENT_SIZE.Height() - CHILD_FRAME_SIZE.Height()) / NUM_TWO);
    radioLayoutAlgorithm.Layout(&layoutWrapper);
    EXPECT_TRUE(IsEqual(childWrapper->GetGeometryNode()->GetMarginFrameOffset(), child_offset));
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: RadioReverseLayout002
 * @tc.desc: Test for layout method of RadioLayoutAlgorithm to get the offset in the RTL scene,
             when Width and height are set in the front end.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioReverseLayout002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node and add Image child.
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(std::nullopt, std::nullopt, std::nullopt);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto radioLayoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(radioLayoutProperty, nullptr);
    radioLayoutProperty->UpdateLayoutDirection(TextDirection::RTL);

    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    frameNode->MarkModifyDone();

    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->FlushBuildFinishCallbacks();
    auto childNode = pattern->builderChildNode_;
    ASSERT_NE(childNode, nullptr);
    auto hostGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper(frameNode, hostGeometryNode, radioLayoutProperty);
    auto childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> childWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(childNode, childGeometryNode, childNode->GetLayoutProperty());
    RadioLayoutAlgorithm radioLayoutAlgorithm;
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.maxSize = SizeF(1000.0, 1000.0);
    layoutConstraintSize.minSize = SizeF(0, 0);
    layoutConstraintSize.selfIdealSize.SetWidth(COMPONENT_WIDTH);
    layoutConstraintSize.selfIdealSize.SetHeight(COMPONENT_HEIGHT);
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraintSize);
    layoutWrapper.AppendChild(childWrapper);

    /**
     * @tc.steps: step2. Measure Radio node Content size and child size.
     */
    layoutWrapper.GetGeometryNode()->SetFrameSize(CONTENT_SIZE);
    childWrapper->GetGeometryNode()->SetFrameSize(CHILD_FRAME_SIZE);

    /**
     * @tc.steps: step3. layout child node.
     */
    NG::OffsetF child_offset;
    auto align = Alignment::CENTER;
    child_offset.SetX((1.0 + align.GetHorizontal()) * (CONTENT_SIZE.Width() - CHILD_FRAME_SIZE.Width()) / NUM_TWO);
    child_offset.SetY((1.0 + align.GetVertical()) * (CONTENT_SIZE.Height() - CHILD_FRAME_SIZE.Height()) / NUM_TWO);
    radioLayoutAlgorithm.Layout(&layoutWrapper);
    EXPECT_TRUE(IsEqual(childWrapper->GetGeometryNode()->GetMarginFrameOffset(), child_offset));
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: RadioReverseLayout003
 * @tc.desc: Test for layout method of RadioLayoutAlgorithm to get the offset in the RTL scene,
             when Width and height are set in the front end and child node is customBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioReverseLayout003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node and add customNode child.
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(std::nullopt, std::nullopt, std::nullopt);
    auto radioFunc = RadioBuilder();
    radioModelNG.SetBuilder(std::move(radioFunc));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto radioLayoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(radioLayoutProperty, nullptr);
    radioLayoutProperty->UpdateLayoutDirection(TextDirection::RTL);
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    int32_t CustomIndicatorType = 2;
    radioPaintProperty->UpdateRadioIndicator(CustomIndicatorType);

    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    frameNode->MarkModifyDone();

    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->FlushBuildFinishCallbacks();
    auto childNode = pattern->builderChildNode_;
    ASSERT_NE(childNode, nullptr);
    auto hostGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper(frameNode, hostGeometryNode, radioLayoutProperty);
    auto childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> childWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(childNode, childGeometryNode, childNode->GetLayoutProperty());
    RadioLayoutAlgorithm radioLayoutAlgorithm;
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.maxSize = SizeF(1000.0, 1000.0);
    layoutConstraintSize.minSize = SizeF(0, 0);
    layoutConstraintSize.selfIdealSize.SetWidth(COMPONENT_WIDTH);
    layoutConstraintSize.selfIdealSize.SetHeight(COMPONENT_HEIGHT);
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraintSize);
    layoutWrapper.AppendChild(childWrapper);

    /**
     * @tc.steps: step2. Measure Radio node Content size and child size.
     */
    layoutWrapper.GetGeometryNode()->SetFrameSize(CONTENT_SIZE);
    childWrapper->GetGeometryNode()->SetFrameSize(CHILD_FRAME_SIZE);

    /**
     * @tc.steps: step3. layout child node.
     */
    NG::OffsetF child_offset;
    auto align = Alignment::CENTER;
    child_offset.SetX((1.0 + align.GetHorizontal()) * (CONTENT_SIZE.Width() - CHILD_FRAME_SIZE.Width()) / NUM_TWO);
    child_offset.SetY((1.0 + align.GetVertical()) * (CONTENT_SIZE.Height() - CHILD_FRAME_SIZE.Height()) / NUM_TWO);
    radioLayoutAlgorithm.Layout(&layoutWrapper);
    EXPECT_TRUE(IsEqual(childWrapper->GetGeometryNode()->GetMarginFrameOffset(), child_offset));
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: RadioPatternTest050
 * @tc.desc: Test Radio OnKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPatternTest050, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto eventHub = frameNode->GetFocusHub();
    ASSERT_NE(eventHub, nullptr);
    /**
     * test event.action != KeyAction::DOWN
     */
    KeyEvent keyEventOne(KeyCode::KEY_FUNCTION, KeyAction::UP);
    EXPECT_FALSE(eventHub->ProcessOnKeyEventInternal(keyEventOne));
    /**
     * test event.action == KeyAction::DOWN and event.code == KeyCode::KEY_A
     */
    KeyEvent keyEventTwo(KeyCode::KEY_A, KeyAction::DOWN);
    EXPECT_FALSE(eventHub->ProcessOnKeyEventInternal(keyEventTwo));
    /**
     * test event.action == KeyAction::DOWN and event.code == KeyCode::KEY_FUNCTION
     */
    KeyEvent keyEventThr(KeyCode::KEY_FUNCTION, KeyAction::DOWN);
    EXPECT_TRUE(eventHub->ProcessOnKeyEventInternal(keyEventThr));
}

/**
 * @tc.name: RadioPatternTest051
 * @tc.desc: Test UpdateGroupCheckStatus.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPatternTest051, TestSize.Level1)
{
    /**
     * @tc.steps: step1. MockContainer.apiTargetVersion_ = VERSION_TWELVE.
     */
    MockContainer::SetUp();
    MockContainer::Current()->SetApiTargetVersion(VERSION_TWELVE);

    /**
     * @tc.steps: Get Radio pattern object and get
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    EXPECT_EQ(radioPaintProperty->GetRadioCheckValue(), CHECKED);

    /**
     * @tc.expected: Function UpdateUncheckStatus is called.
     */
    auto pageEventHub = AceType::MakeRefPtr<NG::PageEventHub>();
    auto groupManager = pageEventHub->GetGroupManager();
    pattern->isFirstCreated_ = false;
    pattern->UpdateGroupCheckStatus(frameNode, groupManager, true);
    pattern->UpdateUncheckStatus(frameNode);
    EXPECT_FALSE(radioPaintProperty->GetRadioCheckValue());
    MockContainer::TearDown();
}

/**
 * @tc.name: RadioPatternTest052
 * @tc.desc: Test UpdateUncheckStatus.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioPatternTest052, TestSize.Level1)
{
    /**
     * @tc.steps: MockContainer.apiTargetVersion_ = VERSION_TWELVE.
     * @tc.steps: set radio theme
     */
    MockContainer::SetUp();
    MockContainer::Current()->SetApiTargetVersion(VERSION_TWELVE);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        auto radioTheme = AceType::MakeRefPtr<RadioTheme>();
        radioTheme->showCircleDial_ = true;
        return radioTheme;
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    /**
     * @tc.steps: Get Radio pattern object and get
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);

    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    EXPECT_EQ(radioPaintProperty->GetRadioCheckValue(), CHECKED);

    /**
     * @tc.expected: Function UpdateGroupCheckStatus is called.
     */
    auto pageEventHub = AceType::MakeRefPtr<NG::PageEventHub>();
    auto groupManager = pageEventHub->GetGroupManager();
    pattern->isFirstCreated_ = false;
    pattern->UpdateGroupCheckStatus(frameNode, groupManager, true);
    pattern->UpdateUncheckStatus(frameNode);
    EXPECT_FALSE(radioPaintProperty->GetRadioCheckValue());
    MockContainer::TearDown();
}

/**
 * @tc.name: RadioCreateResetSetByUserTest001
 * @tc.desc: Test RadioModelNG::Create resets *_SetByUser flags in RadioPaintProperty.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, RadioCreateResetSetByUserTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a radio button and retrieve its paint property.
     * @tc.expected: step1. Frame node and paint property are created successfully.
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);

    /**
     * @tc.steps: step2. Set all *_SetByUser flags to true.
     * @tc.expected: step2. Flags are successfully set to true.
     */
    radioPaintProperty->UpdateRadioCheckedBackgroundColorSetByUser(true);
    radioPaintProperty->UpdateRadioUncheckedBorderColorSetByUser(true);
    radioPaintProperty->UpdateRadioIndicatorColorSetByUser(true);

    /**
     * @tc.steps: step3. Create another radio button and check its paint property.
     * @tc.expected: step3. All *_SetByUser flags are reset to false by Create().
     */
    ViewStackProcessor::GetInstance()->Push(frameNode);
    radioModelNG.Create(NAME1, GROUP_NAME1, INDICATOR_TYPE_TICK);
    auto frameNode2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode2, nullptr);

    auto radioPaintProperty2 = frameNode2->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty2, nullptr);

    EXPECT_FALSE(radioPaintProperty2->HasRadioCheckedBackgroundColorSetByUser());
    EXPECT_FALSE(radioPaintProperty2->HasRadioUncheckedBorderColorSetByUser());
    EXPECT_FALSE(radioPaintProperty2->HasRadioIndicatorColorSetByUser());
}

/**
 * @tc.name: CreateWithColorResourceObj001
 * @tc.desc: Test RadioModelNG CreateWithColorResourceObj with different resource objects.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, CreateWithColorResourceObj001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a radio button and retrieve its pattern.
     * @tc.expected: step1. Frame node and pattern are created successfully.
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set checked background color with null resource object.
     * @tc.expected: step2. Color value is not set (nullopt).
     */
    radioModelNG.CreateWithColorResourceObj(nullptr, RadioColorType::CHECKED_BACKGROUND_COLOR);

    auto paintProperty = pattern->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto colorRet = paintProperty->GetRadioCheckedBackgroundColor();
    EXPECT_FALSE(colorRet.has_value());

    /**
     * @tc.steps: step3. Create valid color resource object and set checked background color.
     * @tc.expected: step3. Color value is set to red (#FFFF0000).
     */
    ResourceObjectParams param;
    param.type = ResourceObjectParamType::STRING;
    param.value = "#FFFF0000";
    int32_t resourceType = static_cast<int32_t>(Kit::ResourceType::COLOR);
    auto resObj = AceType::MakeRefPtr<ResourceObject>(
        1001, resourceType, std::vector<ResourceObjectParams> { param }, "testBundle", "testModule", 0);
    radioModelNG.SetCheckedBackgroundColor(Color::RED);
    radioModelNG.CreateWithColorResourceObj(resObj, RadioColorType::CHECKED_BACKGROUND_COLOR);

    colorRet = paintProperty->GetRadioCheckedBackgroundColor();
    EXPECT_TRUE(colorRet.has_value());

    /**
     * @tc.steps: step4. Add resource to cache and reload resources.
     * @tc.expected: step4. Resource manager reloads without errors.
     */
    std::string key = "radio" + RadioModelNG::ColorTypeToString(RadioColorType::CHECKED_BACKGROUND_COLOR);
    pattern->AddResCache(key, param.value.value());
    auto resMgr = pattern->resourceMgr_;
    ASSERT_NE(resMgr, nullptr);
    resMgr->ReloadResources();
}

/**
 * @tc.name: CreateWithColorResourceObj002
 * @tc.desc: Test RadioModelNG CreateWithColorResourceObj when resource object is not provided.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, CreateWithColorResourceObj002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a radio button and retrieve its pattern.
     * @tc.expected: step1. Frame node and pattern are created successfully.
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set indicator color with null resource object.
     * @tc.expected: step2. Indicator color value is not set (nullopt).
     */
    radioModelNG.CreateWithColorResourceObj(nullptr, RadioColorType::INDICATOR_COLOR);

    auto paintProperty = pattern->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto colorRet = paintProperty->GetRadioIndicatorColor();
    EXPECT_FALSE(colorRet.has_value());
}

/**
 * @tc.name: ColorTypeToString
 * @tc.desc: Test RadioModelNG ColorTypeToString function.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, ColorTypeToString, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Define test cases for all RadioColorType values and an unknown value.
     * @tc.expected: step1. Test cases cover all possible enum values and edge case.
     */
    std::vector<std::pair<RadioColorType, std::string>> types = {
        { RadioColorType::CHECKED_BACKGROUND_COLOR, "CheckedBackgroundColor" },
        { RadioColorType::UNCHECKED_BORDER_COLOR, "UncheckedBorderColor" },
        { RadioColorType::INDICATOR_COLOR, "IndicatorColor" },
        { static_cast<RadioColorType>(999), "" }
    };

    /**
     * @tc.steps: step2. Iterate through test cases and verify string conversion.
     * @tc.expected: step2. All enum values are converted to their correct string representations.
     */
    for (const auto& [type, expected] : types) {
        auto result = RadioModelNG::ColorTypeToString(type);
        EXPECT_EQ(result, expected);
    }
}

/**
 * @tc.name: MeasureContentTest001
 * @tc.desc: Test Radio MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, MeasureContentTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set widthLayoutPolicy_ and heightLayoutPolicy_ to MATCH_PARENT.
     * @tc.expected: ret is equal to TEST_SIZE_100.
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(std::nullopt, std::nullopt, std::nullopt);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode, nullptr, AccessibilityManager::MakeRefPtr<LayoutProperty>());
    RadioLayoutAlgorithm radioLayoutAlgorithm;
    LayoutConstraintF contentConstraint;
    contentConstraint.parentIdealSize.SetSize(TEST_SIZE_100_200);
    auto layoutProperty = layoutWrapper.GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    auto ret = radioLayoutAlgorithm.MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_100);
}

/**
 * @tc.name: LayoutPolicyIsMatchParentTest001
 * @tc.desc: Test Radio LayoutPolicyIsMatchParent.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTestNg, LayoutPolicyIsMatchParentTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call LayoutPolicyIsMatchParent function.
     * @tc.expected: step1. ret is equal to TEST_SIZE_0.
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(std::nullopt, std::nullopt, std::nullopt);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode, nullptr, AccessibilityManager::MakeRefPtr<LayoutProperty>());
    RadioLayoutAlgorithm radioLayoutAlgorithm;
    LayoutConstraintF contentConstraint;
    auto layoutPolicy = radioLayoutAlgorithm.GetLayoutPolicy(&layoutWrapper);
    auto ret = radioLayoutAlgorithm.LayoutPolicyIsMatchParent(contentConstraint,
        layoutPolicy, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_0);

    /**
     * @tc.steps: step2. set layoutPolicy->widthLayoutPolicy_ to MATCH_PARENT.
     * @tc.expected: step2. ret is equal to TEST_SIZE_100.
     */
    contentConstraint.parentIdealSize.SetSize(TEST_SIZE_100_200);
    layoutPolicy->widthLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    ret = radioLayoutAlgorithm.LayoutPolicyIsMatchParent(contentConstraint,
        layoutPolicy, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_100);

    /**
     * @tc.steps: step3. set selfIdealSize.height_ to TEST_HEIGHT_60.
     * @tc.expected: step3. ret is equal to TEST_SIZE_60.
     */
    contentConstraint.selfIdealSize.SetHeight(TEST_HEIGHT_60);
    ret = radioLayoutAlgorithm.LayoutPolicyIsMatchParent(contentConstraint,
        layoutPolicy, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_60);

    /**
     * @tc.steps: step4. set layoutPolicy->heightLayoutPolicy_ to MATCH_PARENT.
     * @tc.expected: step4. ret is equal to TEST_SIZE_200.
     */
    layoutPolicy->widthLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutPolicy->heightLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    ret = radioLayoutAlgorithm.LayoutPolicyIsMatchParent(contentConstraint,
        layoutPolicy, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_200);

    /**
     * @tc.steps: step5. set selfIdealSize.width_ to TEST_WIDTH_50.
     * @tc.expected: step5. ret is equal to TEST_SIZE_50.
     */
    contentConstraint.selfIdealSize.SetWidth(TEST_WIDTH_50);
    ret = radioLayoutAlgorithm.LayoutPolicyIsMatchParent(contentConstraint,
        layoutPolicy, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_50);

    /**
     * @tc.steps: step6. set widthLayoutPolicy_ and heightLayoutPolicy_ to MATCH_PARENT.
     * @tc.expected: step6. ret is equal to TEST_SIZE_100.
     */
    layoutPolicy->widthLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    layoutPolicy->heightLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    ret = radioLayoutAlgorithm.LayoutPolicyIsMatchParent(contentConstraint,
        layoutPolicy, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_100);
}
} // namespace OHOS::Ace::NG
