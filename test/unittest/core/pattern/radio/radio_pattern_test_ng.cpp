/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

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
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"
#include "core/components_v2/inspector/inspector_constants.h"

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
constexpr double DEFAULT_WIDTH = 100.0;
constexpr double DEFAULT_HEIGHT = 110.0;
constexpr Dimension DEFAULT_WIDTH_DIMENSION = Dimension(DEFAULT_WIDTH);
constexpr Dimension DEFAULT_HEIGHT_DIMENSION = Dimension(DEFAULT_HEIGHT);
constexpr Dimension HORIZONTAL_PADDING = Dimension(5.0);
constexpr Dimension VERTICAL_PADDING = Dimension(4.0);
const SizeF CONTENT_SIZE = SizeF(400.0, 500.0);
const OffsetF CONTENT_OFFSET = OffsetF(50.0, 60.0);
const std::optional<int32_t> INDICATOR_TYPE_TICK = 0;
const int32_t RADIOINDICATOR_TYPE_TICK = 0;
const int32_t RADIOINDICATOR_TYPE_DOT = 1;
const int32_t RADIOINDICATOR_CUSTOM = 2;
} // namespace

class RadioPatternTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    static RadioBuilderFunc RadioBuilder();
};

void RadioPatternTestNg::SetUpTestSuite()
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

void RadioPatternTestNg::TearDownTestSuite()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}
/**
 * @tc.name: RadioPatternTest038
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest038, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create("", GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_TYPE_TICK);
    EXPECT_NE(imageSourceInfo.isSvg_, false);
}

/**
 * @tc.name: RadioPatternTest039
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest039, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_TYPE_TICK);
    EXPECT_NE(imageSourceInfo.isSvg_, false);
}

/**
 * @tc.name: RadioPatternTest040
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest040, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_TYPE_TICK);
    EXPECT_NE(imageSourceInfo.isSvg_, false);
}

/**
 * @tc.name: RadioPatternTest041
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest041, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create("", GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_TYPE_DOT);
    EXPECT_NE(imageSourceInfo.isSvg_, false);
}

/**
 * @tc.name: RadioPatternTest042
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest042, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_TYPE_DOT);
    EXPECT_NE(imageSourceInfo.isSvg_, false);
}

/**
 * @tc.name: RadioPatternTest043
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest043, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_TYPE_DOT);
    EXPECT_NE(imageSourceInfo.isSvg_, false);
}

/**
 * @tc.name: RadioPatternTest044
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest044, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create("", GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_CUSTOM);
    EXPECT_NE(imageSourceInfo.isSvg_, false);
}

/**
 * @tc.name: RadioPatternTest045
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest045, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_CUSTOM);
    EXPECT_NE(imageSourceInfo.isSvg_, false);
}

/**
 * @tc.name: RadioPatternTest046
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest046, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_CUSTOM);
    EXPECT_NE(imageSourceInfo.isSvg_, false);
}

/**
 * @tc.name: RadioPatternTest047
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest047, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create("", GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_TYPE_TICK);
    EXPECT_EQ(imageSourceInfo.pixmap_, false);
}

/**
 * @tc.name: RadioPatternTest048
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest048, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_TYPE_TICK);
    EXPECT_EQ(imageSourceInfo.pixmap_, false);
}

/**
 * @tc.name: RadioPatternTest049
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest049, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_TYPE_TICK);
    EXPECT_EQ(imageSourceInfo.pixmap_, false);
}

/**
 * @tc.name: RadioPatternTest050
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest050, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create("", GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_TYPE_DOT);
    EXPECT_EQ(imageSourceInfo.pixmap_, false);
}

/**
 * @tc.name: RadioPatternTest051
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest051, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_TYPE_DOT);
    EXPECT_EQ(imageSourceInfo.pixmap_, false);
}

/**
 * @tc.name: RadioPatternTest052
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest052, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_TYPE_DOT);
    EXPECT_EQ(imageSourceInfo.pixmap_, false);
}

/**
 * @tc.name: RadioPatternTest053
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest053, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create("", GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_CUSTOM);
    EXPECT_EQ(imageSourceInfo.pixmap_, false);
}

/**
 * @tc.name: RadioPatternTest054
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest054, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_CUSTOM);
    EXPECT_EQ(imageSourceInfo.pixmap_, false);
}

/**
 * @tc.name: RadioPatternTest055
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest055, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_CUSTOM);
    EXPECT_EQ(imageSourceInfo.pixmap_, false);
}

/**
 * @tc.name: RadioPatternTest056
 * @tc.desc: Radio test startEnterAnimation.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest056, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create("", GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto host = pattern->GetHost();
    pattern->startEnterAnimation();

    EXPECT_TRUE(eventHub->IsEnabled());
}
/**
 * @tc.name: RadioPatternTest057
 * @tc.desc: Radio test startEnterAnimation.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest057, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto host = pattern->GetHost();
    pattern->startEnterAnimation();

    EXPECT_TRUE(eventHub->IsEnabled());
}

/**
 * @tc.name: RadioPatternTest058
 * @tc.desc: Radio test startExitAnimation.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest058, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto host = pattern->GetHost();
    pattern->startExitAnimation();

    EXPECT_TRUE(eventHub->enabled_);
}

/**
 * @tc.name: RadioPatternTest059
 * @tc.desc: Radio test startExitAnimation.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest059, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create("", GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto host = pattern->GetHost();
    pattern->startExitAnimation();

    EXPECT_TRUE(eventHub->enabled_);
}

/**
 * @tc.name: RadioPatternTest060
 * @tc.desc: Radio test startExitAnimation.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest060, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto host = pattern->GetHost();
    pattern->startExitAnimation();

    EXPECT_TRUE(eventHub->enabled_);
}

/**
 * @tc.name: RadioPatternTest061
 * @tc.desc: Radio test startExitAnimation.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest061, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_TYPE_TICK);
   
    pattern->ImageNodeCreate();
    auto Hasval = pattern->preTypeIsBuilder_;
    ASSERT_EQ(Hasval, false);
}

/**
 * @tc.name: RadioPatternTest062
 * @tc.desc: Radio test startExitAnimation.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest062, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create("", GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_TYPE_TICK);
    
    pattern->ImageNodeCreate();
    auto hasval = pattern->preTypeIsBuilder_;
    ASSERT_EQ(hasval, false);
}

/**
 * @tc.name: RadioPatternTest063
 * @tc.desc: Radio test startExitAnimation.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest063, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_TYPE_TICK);
    
    pattern->ImageNodeCreate();
    auto hasval = pattern->preTypeIsBuilder_;
    ASSERT_EQ(hasval, false);
}

/**
 * @tc.name: RadioPatternTest064
 * @tc.desc: Radio test startExitAnimation.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest064, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    
    pattern->UpdateIndicatorType();
    auto hasval = pattern->preTypeIsBuilder_;
    ASSERT_EQ(hasval, false);
}

/**
 * @tc.name: RadioPatternTest065
 * @tc.desc: Radio test startExitAnimation.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest065, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create("", GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    
    pattern->UpdateIndicatorType();
    auto hasval = pattern->preTypeIsBuilder_;
    ASSERT_EQ(hasval, false);
}

/**
 * @tc.name: RadioPatternTest066
 * @tc.desc: Radio test startExitAnimation.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest066, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->UpdateIndicatorType();
    auto hasval = pattern->preTypeIsBuilder_;
    ASSERT_EQ(hasval, false);
}

/**
 * @tc.name: RadioPatternTest067
 * @tc.desc: Radio test UpdateState.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest067, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);

    auto pageEventHub = AceType::MakeRefPtr<NG::PageEventHub>();
    auto groupManager = pageEventHub->GetGroupManager();
    groupManager->UpdateRadioGroupValue(GROUP_NAME, 1);
    pattern->groupManager_ = groupManager;
    pattern->UpdateState();
    auto val = pattern->isGroupChanged_;
    ASSERT_EQ(val, false);
}

/**
 * @tc.name: RadioPatternTest068
 * @tc.desc: Radio test UpdateState.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest068, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create("", GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    auto pageEventHub = AceType::MakeRefPtr<NG::PageEventHub>();
    auto groupManager = pageEventHub->GetGroupManager();
    groupManager->UpdateRadioGroupValue(GROUP_NAME, 1);
    pattern->groupManager_ = groupManager;
    pattern->preGroup_ = GROUP_NAME;
    paintProperty->UpdateRadioCheck(true);
    pattern->isGroupChanged_ = true;
    pattern->UpdateState();
    auto val = pattern->isGroupChanged_;
    ASSERT_EQ(val, false);
}

/**
 * @tc.name: RadioPatternTest069
 * @tc.desc: Radio test UpdateState.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest069, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    
    auto pageEventHub = AceType::MakeRefPtr<NG::PageEventHub>();
    auto groupManager = pageEventHub->GetGroupManager();
    groupManager->UpdateRadioGroupValue(GROUP_NAME, 1);
    pattern->groupManager_ = groupManager;
    paintProperty->ResetRadioCheck();
    pattern->UpdateState();
    auto val = pattern->isGroupChanged_;
    ASSERT_EQ(val, false);
}

/**
 * @tc.name: RadioPatternTest070
 * @tc.desc: Radio test LoadBuilder.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest070, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    
    pattern->LoadBuilder();
    auto val = pattern->preTypeIsBuilder_;
    ASSERT_NE(val, true);
}

/**
 * @tc.name: RadioPatternTest071
 * @tc.desc: Radio test LoadBuilder.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest071, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create("", GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    
    pattern->LoadBuilder();
    auto val = pattern->preTypeIsBuilder_;
    ASSERT_NE(val, true);
}

/**
 * @tc.name: RadioPatternTest072
 * @tc.desc: Radio test LoadBuilder.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest072, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    
    pattern->LoadBuilder();
    auto val = pattern->preTypeIsBuilder_;
    ASSERT_NE(val, true);
}

/**
 * @tc.name: RadioPatternTest073
 * @tc.desc: Radio test LoadBuilder.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest073, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->builder_ = []() {
        std::cout << "";
    };
    pattern->LoadBuilder();
    auto val = pattern->preTypeIsBuilder_;
    ASSERT_NE(val, true);
}

/**
 * @tc.name: RadioPatternTest074
 * @tc.desc: Radio test LoadBuilder.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest074, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create("", GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    
    pattern->builder_ = []() {

    };
    pattern->LoadBuilder();
    auto val = pattern->preTypeIsBuilder_;
    ASSERT_NE(val, true);
}

/**
 * @tc.name: RadioPatternTest075
 * @tc.desc: Radio test LoadBuilder.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest075, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    
    pattern->builder_ = []() {

    };
    pattern->LoadBuilder();
    auto val = pattern->preTypeIsBuilder_;
    ASSERT_NE(val, true);
}

/////////////////////////#####################

/**
 * @tc.name: RadioPatternTest076
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest076, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create("", GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_TYPE_TICK);
    EXPECT_NE(imageSourceInfo.isSvg_, false);
}

/**
 * @tc.name: RadioPatternTest077
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest077, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_TYPE_TICK);
    EXPECT_NE(imageSourceInfo.isSvg_, false);
}

/**
 * @tc.name: RadioPatternTest078
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest078, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_TYPE_TICK);
    EXPECT_NE(imageSourceInfo.isSvg_, false);
}

/**
 * @tc.name: RadioPatternTest079
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest079, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create("", GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_TYPE_DOT);
    EXPECT_NE(imageSourceInfo.isSvg_, false);
}

/**
 * @tc.name: RadioPatternTest080
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest080, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_TYPE_DOT);
    EXPECT_NE(imageSourceInfo.isSvg_, false);
}

/**
 * @tc.name: RadioPatternTest081
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest081, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_TYPE_DOT);
    EXPECT_NE(imageSourceInfo.isSvg_, false);
}

/**
 * @tc.name: RadioPatternTest082
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest082, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create("", GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_CUSTOM);
    EXPECT_NE(imageSourceInfo.isSvg_, false);
}

/**
 * @tc.name: RadioPatternTest083
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest083, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_CUSTOM);
    EXPECT_NE(imageSourceInfo.isSvg_, false);
}

/**
 * @tc.name: RadioPatternTest084
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest084, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_CUSTOM);
    EXPECT_NE(imageSourceInfo.isSvg_, false);
}

/**
 * @tc.name: RadioPatternTest085
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest085, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create("", GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_TYPE_TICK);
    EXPECT_EQ(imageSourceInfo.pixmap_, false);
}

/**
 * @tc.name: RadioPatternTest086
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest086, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_TYPE_TICK);
    EXPECT_EQ(imageSourceInfo.pixmap_, false);
}

/**
 * @tc.name: RadioPatternTest087
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest087, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_TYPE_TICK);
    EXPECT_EQ(imageSourceInfo.pixmap_, false);
}

/**
 * @tc.name: RadioPatternTest088
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest088, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create("", GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_TYPE_DOT);
    EXPECT_EQ(imageSourceInfo.pixmap_, false);
}

/**
 * @tc.name: RadioPatternTest089
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest089, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_TYPE_DOT);
    EXPECT_EQ(imageSourceInfo.pixmap_, false);
}

/**
 * @tc.name: RadioPatternTest090
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest090, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_TYPE_DOT);
    EXPECT_EQ(imageSourceInfo.pixmap_, false);
}

/**
 * @tc.name: RadioPatternTest091
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest091, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create("", GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_CUSTOM);
    EXPECT_EQ(imageSourceInfo.pixmap_, false);
}

/**
 * @tc.name: RadioPatternTest092
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest092, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_CUSTOM);
    EXPECT_EQ(imageSourceInfo.pixmap_, false);
}

/**
 * @tc.name: RadioPatternTest093
 * @tc.desc: Test GetImageSourceInfoFromTheme
 * @tc.type: FUNC
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest093, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();

    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_CUSTOM);
    EXPECT_EQ(imageSourceInfo.pixmap_, false);
}

/**
 * @tc.name: RadioPatternTest094
 * @tc.desc: Radio test startEnterAnimation.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest094, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create("", GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto host = pattern->GetHost();
    pattern->startEnterAnimation();

    EXPECT_TRUE(eventHub->IsEnabled());
}
/**
 * @tc.name: RadioPatternTest095
 * @tc.desc: Radio test startEnterAnimation.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest095, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto host = pattern->GetHost();
    pattern->startEnterAnimation();

    EXPECT_TRUE(eventHub->IsEnabled());
}

/**
 * @tc.name: RadioPatternTest096
 * @tc.desc: Radio test startExitAnimation.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest096, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto host = pattern->GetHost();
    pattern->startExitAnimation();

    EXPECT_TRUE(eventHub->enabled_);
}

/**
 * @tc.name: RadioPatternTest097
 * @tc.desc: Radio test startExitAnimation.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest097, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create("", GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto host = pattern->GetHost();
    pattern->startExitAnimation();

    EXPECT_TRUE(eventHub->enabled_);
}

/**
 * @tc.name: RadioPatternTest098
 * @tc.desc: Radio test startExitAnimation.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest098, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto host = pattern->GetHost();
    pattern->startExitAnimation();

    EXPECT_TRUE(eventHub->enabled_);
}

/**
 * @tc.name: RadioPatternTest099
 * @tc.desc: Radio test startExitAnimation.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest099, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_TYPE_TICK);
   
    pattern->ImageNodeCreate();
    auto Hasval = pattern->preTypeIsBuilder_;
    ASSERT_EQ(Hasval, false);
}

/**
 * @tc.name: RadioPatternTest100
 * @tc.desc: Radio test startExitAnimation.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest100, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create("", GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_TYPE_TICK);
    
    pattern->ImageNodeCreate();
    auto hasval = pattern->preTypeIsBuilder_;
    ASSERT_EQ(hasval, false);
}

/**
 * @tc.name: RadioPatternTest101
 * @tc.desc: Radio test startExitAnimation.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest101, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto imageSourceInfo = pattern->GetImageSourceInfoFromTheme(RADIOINDICATOR_TYPE_TICK);
    
    pattern->ImageNodeCreate();
    auto hasval = pattern->preTypeIsBuilder_;
    ASSERT_EQ(hasval, false);
}

/**
 * @tc.name: RadioPatternTest102
 * @tc.desc: Radio test startExitAnimation.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest102, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    
    pattern->UpdateIndicatorType();
    auto hasval = pattern->preTypeIsBuilder_;
    ASSERT_EQ(hasval, false);
}

/**
 * @tc.name: RadioPatternTest103
 * @tc.desc: Radio test startExitAnimation.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest103, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create("", GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    
    pattern->UpdateIndicatorType();
    auto hasval = pattern->preTypeIsBuilder_;
    ASSERT_EQ(hasval, false);
}

/**
 * @tc.name: RadioPatternTest104
 * @tc.desc: Radio test startExitAnimation.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest104, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->UpdateIndicatorType();
    auto hasval = pattern->preTypeIsBuilder_;
    ASSERT_EQ(hasval, false);
}

/**
 * @tc.name: RadioPatternTest105
 * @tc.desc: Radio test UpdateState.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest105, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    
    pattern->UpdateState();
    auto val = pattern->isGroupChanged_;
    ASSERT_EQ(val, false);
}

/**
 * @tc.name: RadioPatternTest106
 * @tc.desc: Radio test UpdateState.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest106, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create("", GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->UpdateState();
    auto val = pattern->isGroupChanged_;
    ASSERT_EQ(val, false);
}

/**
 * @tc.name: RadioPatternTest107
 * @tc.desc: Radio test UpdateState.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest107, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    
    pattern->UpdateState();
    auto val = pattern->isGroupChanged_;
    ASSERT_EQ(val, false);
}

/**
 * @tc.name: RadioPatternTest108
 * @tc.desc: Radio test LoadBuilder.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest108, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    
    pattern->LoadBuilder();
    auto val = pattern->preTypeIsBuilder_;
    ASSERT_NE(val, true);
}

/**
 * @tc.name: RadioPatternTest109
 * @tc.desc: Radio test LoadBuilder.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest109, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create("", GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    
    pattern->LoadBuilder();
    auto val = pattern->preTypeIsBuilder_;
    ASSERT_NE(val, true);
}

/**
 * @tc.name: RadioPatternTest110
 * @tc.desc: Radio test LoadBuilder.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest110, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    
    pattern->LoadBuilder();
    auto val = pattern->preTypeIsBuilder_;
    ASSERT_NE(val, true);
}

/**
 * @tc.name: RadioPatternTest111
 * @tc.desc: Radio test LoadBuilder.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest111, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->builder_ = []() {
        std::cout << "";
    };
    pattern->LoadBuilder();
    auto val = pattern->preTypeIsBuilder_;
    ASSERT_NE(val, true);
}

/**
 * @tc.name: RadioPatternTest112
 * @tc.desc: Radio test LoadBuilder.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest112, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create("", GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    
    pattern->builder_ = []() {

    };
    pattern->LoadBuilder();
    auto val = pattern->preTypeIsBuilder_;
    ASSERT_NE(val, true);
}

/**
 * @tc.name: RadioPatternTest113
 * @tc.desc: Radio test LoadBuilder.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest113, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    
    pattern->builder_ = []() {

    };
    pattern->LoadBuilder();
    auto val = pattern->preTypeIsBuilder_;
    ASSERT_NE(val, true);
}

/**
 * @tc.name: RadioPatternTest114
 * @tc.desc: Radio test LoadBuilder.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest114, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->SetPrePageIdToLastPageId();

    auto groupManager = pattern->GetGroupManager();
    auto check = false;
    settingApiVersion = 11;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    pattern->UpdateGroupCheckStatus(frameNode, groupManager, check);
}

/**
 * @tc.name: RadioPatternTest115
 * @tc.desc: Radio test LoadBuilder.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest115, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->SetPrePageIdToLastPageId();

    auto groupManager = pattern->GetGroupManager();
    auto check = false;
    pattern->UpdateGroupCheckStatus(frameNode, groupManager, check);
}

/**
 * @tc.name: RadioPatternTest116
 * @tc.desc: Radio test LoadBuilder.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest116, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    ASSERT_NE(eventHub, nullptr);

    auto status = eventHub->IsEnabled();
    auto enabled = status;
    if (enabled == true) {
        enabled = false;
    } else {
        enabled = true;
    }
    eventHub->SetEnabled(enabled);
    pattern->HandleEnabled();
    settingApiVersion = 11;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    pattern->HandleEnabled();
    eventHub->SetEnabled(status);
}

/**
 * @tc.name: RadioPatternTest117
 * @tc.desc: Radio test LoadBuilder.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest117, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    ASSERT_NE(eventHub, nullptr);

    auto status = eventHub->IsEnabled();
    auto enabled = status;
    if (enabled == true) {
        enabled = false;
    } else {
        enabled = true;
    }
    eventHub->SetEnabled(enabled);
    settingApiVersion = 11;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    pattern->HandleEnabled();
    eventHub->SetEnabled(status);
}

/**
 * @tc.name: RadioPatternTest118
 * @tc.desc: Radio test LoadBuilder.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest118, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->CheckPageNode();
}

/**
 * @tc.name: RadioPatternTest119
 * @tc.desc: Radio test LoadBuilder.
 */
HWTEST_F(RadioPatternTestNg, RadioPatternTest119, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnAfterModifyDone();
}
} // namespace OHOS::Ace::NG
