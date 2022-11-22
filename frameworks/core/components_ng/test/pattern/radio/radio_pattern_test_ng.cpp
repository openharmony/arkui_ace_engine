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
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string NAME = "radio";
const std::string GROUP_NAME = "radioGroup";
const std::string GROUP_NAME_CHANGE = "radioGroupChange";
constexpr Dimension WIDTH = 50.0_vp;
constexpr Dimension HEIGHT = 50.0_vp;
constexpr NG::PaddingPropertyF PADDING = NG::PaddingPropertyF();
constexpr bool CHECKED = true;
constexpr Dimension HORIZONTAL_PADDING = Dimension(5.0);
constexpr Dimension VERTICAL_PADDING = Dimension(4.0);
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
    EXPECT_FALSE(frameNode == nullptr);
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    EXPECT_FALSE(radioPaintProperty == nullptr);
    EXPECT_EQ(radioPaintProperty->GetRadioCheck(), CHECKED);
}

/**
 * @tc.name: RadioEventHubPropertyTest002
 * @tc.desc: Set Radio value into RadioEventHub and get it.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioEventHubPropertyTest002, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    EXPECT_FALSE(eventHub == nullptr);
    EXPECT_EQ(eventHub->GetValue(), NAME);
    EXPECT_EQ(eventHub->GetGroup(), GROUP_NAME);
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
    EXPECT_FALSE(frameNode == nullptr);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    EXPECT_FALSE(eventHub == nullptr);
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
    EXPECT_FALSE(frameNode == nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<RadioPattern>();
    EXPECT_FALSE(pattern == nullptr);
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
} // namespace OHOS::Ace::NG