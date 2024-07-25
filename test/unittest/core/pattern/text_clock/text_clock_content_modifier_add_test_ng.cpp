/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include <optional>
#include <string>
#include <sys/time.h>

#include "gtest/gtest.h"
#define private public
#define protected public
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/utils/time_util.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text_clock/text_clock_layout_property.h"
#include "core/components_ng/pattern/text_clock/text_clock_model_ng.h"
#include "core/components_ng/pattern/text_clock/text_clock_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
constexpr int32_t HOURS_WEST = -8;
inline const std::string CLOCK_FORMAT = "aa h:m:s";
inline const std::string UTC_1 = "1000000000000";
inline const std::string UTC_2 = "2000000000000";
inline const std::string FORMAT_DATA = "08:00:00";
inline const std::string FORM_FORMAT = "hm";
inline const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
const std::string EMPTY_TEXT = "";
const std::string TEXTCLOCK_CONTENT = "08:00:00";
const Color TEXT_COLOR_VALUE = Color::FromRGB(255, 100, 100);
constexpr bool IS_ON = true;
constexpr int BIG_INT = 100000000;
constexpr int NEGATIVE_BIG_INT = -100000000;
} // namespace

struct TestProperty {
    std::optional<std::string> format = std::nullopt;
    std::optional<int32_t> hoursWest = std::nullopt;
    std::optional<Dimension> fontSize = std::nullopt;
    std::optional<Color> textColor = std::nullopt;
    std::optional<Ace::FontStyle> italicFontStyle = std::nullopt;
    std::optional<Ace::FontWeight> fontWeight = std::nullopt;
    std::optional<std::vector<std::string>> fontFamily = std::nullopt;
    std::optional<std::vector<Shadow>> textShadow = std::nullopt;
    std::optional<FONT_FEATURES_LIST> fontFeature = std::nullopt;
};

class TextClockContentModifierAddTestNG : public testing::Test {
protected:
    static RefPtr<FrameNode> CreateTextClockParagraph(const TestProperty& testProperty);
};

RefPtr<FrameNode> TextClockContentModifierAddTestNG::CreateTextClockParagraph(const TestProperty& testProperty)
{
    TextClockModelNG textClockModel;
    textClockModel.Create();
    if (testProperty.format.has_value()) {
        textClockModel.SetFormat(testProperty.format.value());
    }
    if (testProperty.hoursWest.has_value()) {
        textClockModel.SetHoursWest(testProperty.hoursWest.value());
    }
    if (testProperty.fontSize.has_value()) {
        textClockModel.SetFontSize(testProperty.fontSize.value());
    }
    if (testProperty.textColor.has_value()) {
        textClockModel.SetTextColor(testProperty.textColor.value());
    }
    if (testProperty.italicFontStyle.has_value()) {
        textClockModel.SetItalicFontStyle(testProperty.italicFontStyle.value());
    }
    if (testProperty.fontWeight.has_value()) {
        textClockModel.SetFontWeight(testProperty.fontWeight.value());
    }
    if (testProperty.fontFamily.has_value()) {
        textClockModel.SetFontFamily(testProperty.fontFamily.value());
    }
    if (testProperty.textShadow.has_value()) {
        textClockModel.SetTextShadow(testProperty.textShadow.value());
    }
    if (testProperty.fontFeature.has_value()) {
        textClockModel.SetFontFeature(testProperty.fontFeature.value());
    }
    return AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
}

/**
 * @tc.name: TextClockContentModifierAddTest001
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TestProperty testProperty;
    testProperty.hoursWest = std::make_optional(HOURS_WEST);
    auto frameNode = CreateTextClockParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(0);

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(HOURS_WEST, config.timeZoneOffset_);
        EXPECT_EQ(true, config.started_);
        EXPECT_EQ(false, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierAddTest002
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TestProperty testProperty;
    testProperty.hoursWest = std::make_optional(HOURS_WEST);
    auto frameNode = CreateTextClockParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(0);
    auto controller = pattern->GetTextClockController();
    ASSERT_NE(controller, nullptr);
    controller->Start();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(HOURS_WEST, config.timeZoneOffset_);
        EXPECT_EQ(true, config.started_);
        EXPECT_EQ(false, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierAddTest003
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TestProperty testProperty;
    testProperty.hoursWest = std::make_optional(HOURS_WEST);
    auto frameNode = CreateTextClockParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(0);
    auto controller = pattern->GetTextClockController();
    ASSERT_NE(controller, nullptr);
    controller->Start();
    controller->Stop();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(HOURS_WEST, config.timeZoneOffset_);
        EXPECT_EQ(false, config.started_);
        EXPECT_EQ(false, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierAddTest004
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TestProperty testProperty;
    float hoursWest = 8;
    testProperty.hoursWest = std::make_optional(hoursWest);
    auto frameNode = CreateTextClockParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(0);

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(hoursWest, config.timeZoneOffset_);
        EXPECT_EQ(true, config.started_);
        EXPECT_EQ(false, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierAddTest005
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TestProperty testProperty;
    float hoursWest = 8;
    testProperty.hoursWest = std::make_optional(hoursWest);
    auto frameNode = CreateTextClockParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(0);
    auto controller = pattern->GetTextClockController();
    ASSERT_NE(controller, nullptr);
    controller->Start();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(hoursWest, config.timeZoneOffset_);
        EXPECT_EQ(true, config.started_);
        EXPECT_EQ(false, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierAddTest006
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TestProperty testProperty;
    float hoursWest = 8;
    testProperty.hoursWest = std::make_optional(hoursWest);
    auto frameNode = CreateTextClockParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(0);
    auto controller = pattern->GetTextClockController();
    ASSERT_NE(controller, nullptr);
    controller->Start();
    controller->Stop();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(hoursWest, config.timeZoneOffset_);
        EXPECT_EQ(false, config.started_);
        EXPECT_EQ(false, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierAddTest007
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TextClockModelNG model;
    model.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    model.SetHoursWest(HOURS_WEST);
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(1);

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(HOURS_WEST, config.timeZoneOffset_);
        EXPECT_EQ(true, config.started_);
        EXPECT_EQ(IS_ON, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierAddTest008
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TextClockModelNG model;
    model.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    model.SetHoursWest(HOURS_WEST);
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(1);
    auto controller = pattern->GetTextClockController();
    ASSERT_NE(controller, nullptr);
    controller->Start();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(HOURS_WEST, config.timeZoneOffset_);
        EXPECT_EQ(true, config.started_);
        EXPECT_EQ(IS_ON, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierAddTest009
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TextClockModelNG model;
    model.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    model.SetHoursWest(HOURS_WEST);
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(1);
    auto controller = pattern->GetTextClockController();
    ASSERT_NE(controller, nullptr);
    controller->Start();
    controller->Stop();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(HOURS_WEST, config.timeZoneOffset_);
        EXPECT_EQ(false, config.started_);
        EXPECT_EQ(IS_ON, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierAddTest010
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TextClockModelNG model;
    model.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    float hoursWest = 8;
    model.SetHoursWest(hoursWest);
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(1);

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(hoursWest, config.timeZoneOffset_);
        EXPECT_EQ(true, config.started_);
        EXPECT_EQ(IS_ON, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierAddTest011
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TextClockModelNG model;
    model.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    float hoursWest = 8;
    model.SetHoursWest(hoursWest);
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(1);
    auto controller = pattern->GetTextClockController();
    ASSERT_NE(controller, nullptr);
    controller->Start();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(hoursWest, config.timeZoneOffset_);
        EXPECT_EQ(true, config.started_);
        EXPECT_EQ(IS_ON, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierAddTest012
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TextClockModelNG model;
    model.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    float hoursWest = 8;
    model.SetHoursWest(hoursWest);
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(1);
    auto controller = pattern->GetTextClockController();
    ASSERT_NE(controller, nullptr);
    controller->Start();
    controller->Stop();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(hoursWest, config.timeZoneOffset_);
        EXPECT_EQ(false, config.started_);
        EXPECT_EQ(IS_ON, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierAddTest013
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TextClockModelNG model;
    model.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    model.SetHoursWest(HOURS_WEST);
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(0);

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(HOURS_WEST, config.timeZoneOffset_);
        EXPECT_EQ(true, config.started_);
        EXPECT_EQ(false, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierAddTest014
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TextClockModelNG model;
    model.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    model.SetHoursWest(HOURS_WEST);
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(0);
    auto controller = pattern->GetTextClockController();
    ASSERT_NE(controller, nullptr);
    controller->Start();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(HOURS_WEST, config.timeZoneOffset_);
        EXPECT_EQ(true, config.started_);
        EXPECT_EQ(false, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierAddTest015
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TextClockModelNG model;
    model.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    model.SetHoursWest(HOURS_WEST);
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(0);
    auto controller = pattern->GetTextClockController();
    ASSERT_NE(controller, nullptr);
    controller->Start();
    controller->Stop();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(HOURS_WEST, config.timeZoneOffset_);
        EXPECT_EQ(false, config.started_);
        EXPECT_EQ(false, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierAddTest016
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TextClockModelNG model;
    model.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    float hoursWest = 8;
    model.SetHoursWest(hoursWest);
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(0);

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(hoursWest, config.timeZoneOffset_);
        EXPECT_EQ(true, config.started_);
        EXPECT_EQ(false, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierAddTest017
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TextClockModelNG model;
    model.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    float hoursWest = 8;
    model.SetHoursWest(hoursWest);
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(0);
    auto controller = pattern->GetTextClockController();
    ASSERT_NE(controller, nullptr);
    controller->Start();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(hoursWest, config.timeZoneOffset_);
        EXPECT_EQ(true, config.started_);
        EXPECT_EQ(false, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierAddTest018
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TextClockModelNG model;
    model.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    float hoursWest = 8;
    model.SetHoursWest(hoursWest);
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(0);
    auto controller = pattern->GetTextClockController();
    ASSERT_NE(controller, nullptr);
    controller->Start();
    controller->Stop();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(hoursWest, config.timeZoneOffset_);
        EXPECT_EQ(false, config.started_);
        EXPECT_EQ(false, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierAddTest019
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TestProperty testProperty;
    testProperty.hoursWest = std::make_optional(HOURS_WEST);
    auto frameNode = CreateTextClockParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(BIG_INT);

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(HOURS_WEST, config.timeZoneOffset_);
        EXPECT_EQ(true, config.started_);
        EXPECT_EQ(IS_ON, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierAddTest020
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TestProperty testProperty;
    testProperty.hoursWest = std::make_optional(HOURS_WEST);
    auto frameNode = CreateTextClockParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(BIG_INT);
    auto controller = pattern->GetTextClockController();
    ASSERT_NE(controller, nullptr);
    controller->Start();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(HOURS_WEST, config.timeZoneOffset_);
        EXPECT_EQ(true, config.started_);
        EXPECT_EQ(IS_ON, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierAddTest021
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TestProperty testProperty;
    testProperty.hoursWest = std::make_optional(HOURS_WEST);
    auto frameNode = CreateTextClockParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(BIG_INT);
    auto controller = pattern->GetTextClockController();
    ASSERT_NE(controller, nullptr);
    controller->Start();
    controller->Stop();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(HOURS_WEST, config.timeZoneOffset_);
        EXPECT_EQ(false, config.started_);
        EXPECT_EQ(IS_ON, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierAddTest022
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TestProperty testProperty;
    float hoursWest = 8;
    testProperty.hoursWest = std::make_optional(hoursWest);
    auto frameNode = CreateTextClockParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(BIG_INT);

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(hoursWest, config.timeZoneOffset_);
        EXPECT_EQ(true, config.started_);
        EXPECT_EQ(IS_ON, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierAddTest023
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TestProperty testProperty;
    float hoursWest = 8;
    testProperty.hoursWest = std::make_optional(hoursWest);
    auto frameNode = CreateTextClockParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(BIG_INT);
    auto controller = pattern->GetTextClockController();
    ASSERT_NE(controller, nullptr);
    controller->Start();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(hoursWest, config.timeZoneOffset_);
        EXPECT_EQ(true, config.started_);
        EXPECT_EQ(IS_ON, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierAddTest024
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TestProperty testProperty;
    float hoursWest = 8;
    testProperty.hoursWest = std::make_optional(hoursWest);
    auto frameNode = CreateTextClockParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(BIG_INT);
    auto controller = pattern->GetTextClockController();
    ASSERT_NE(controller, nullptr);
    controller->Start();
    controller->Stop();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(hoursWest, config.timeZoneOffset_);
        EXPECT_EQ(false, config.started_);
        EXPECT_EQ(IS_ON, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierAddTest025
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TestProperty testProperty;
    testProperty.hoursWest = std::make_optional(HOURS_WEST);
    auto frameNode = CreateTextClockParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(NEGATIVE_BIG_INT);

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(HOURS_WEST, config.timeZoneOffset_);
        EXPECT_EQ(true, config.started_);
        EXPECT_EQ(IS_ON, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierAddTest026
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TestProperty testProperty;
    testProperty.hoursWest = std::make_optional(HOURS_WEST);
    auto frameNode = CreateTextClockParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(NEGATIVE_BIG_INT);
    auto controller = pattern->GetTextClockController();
    ASSERT_NE(controller, nullptr);
    controller->Start();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(HOURS_WEST, config.timeZoneOffset_);
        EXPECT_EQ(true, config.started_);
        EXPECT_EQ(IS_ON, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierAddTest027
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TestProperty testProperty;
    testProperty.hoursWest = std::make_optional(HOURS_WEST);
    auto frameNode = CreateTextClockParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(NEGATIVE_BIG_INT);
    auto controller = pattern->GetTextClockController();
    ASSERT_NE(controller, nullptr);
    controller->Start();
    controller->Stop();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(HOURS_WEST, config.timeZoneOffset_);
        EXPECT_EQ(false, config.started_);
        EXPECT_EQ(IS_ON, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierAddTest028
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TestProperty testProperty;
    float hoursWest = 8;
    testProperty.hoursWest = std::make_optional(hoursWest);
    auto frameNode = CreateTextClockParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(NEGATIVE_BIG_INT);

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(hoursWest, config.timeZoneOffset_);
        EXPECT_EQ(true, config.started_);
        EXPECT_EQ(IS_ON, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierAddTest029
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TestProperty testProperty;
    float hoursWest = 8;
    testProperty.hoursWest = std::make_optional(hoursWest);
    auto frameNode = CreateTextClockParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(NEGATIVE_BIG_INT);
    auto controller = pattern->GetTextClockController();
    ASSERT_NE(controller, nullptr);
    controller->Start();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(hoursWest, config.timeZoneOffset_);
        EXPECT_EQ(true, config.started_);
        EXPECT_EQ(IS_ON, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierAddTest030
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TestProperty testProperty;
    float hoursWest = 8;
    testProperty.hoursWest = std::make_optional(hoursWest);
    auto frameNode = CreateTextClockParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(NEGATIVE_BIG_INT);
    auto controller = pattern->GetTextClockController();
    ASSERT_NE(controller, nullptr);
    controller->Start();
    controller->Stop();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(hoursWest, config.timeZoneOffset_);
        EXPECT_EQ(false, config.started_);
        EXPECT_EQ(IS_ON, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierAddTest031
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TestProperty testProperty;
    testProperty.hoursWest = std::make_optional(HOURS_WEST);
    auto frameNode = CreateTextClockParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(1);

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(HOURS_WEST, config.timeZoneOffset_);
        EXPECT_EQ(true, config.started_);
        EXPECT_EQ(IS_ON, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierAddTest032
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TestProperty testProperty;
    testProperty.hoursWest = std::make_optional(HOURS_WEST);
    auto frameNode = CreateTextClockParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(1);
    auto controller = pattern->GetTextClockController();
    ASSERT_NE(controller, nullptr);
    controller->Start();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(HOURS_WEST, config.timeZoneOffset_);
        EXPECT_EQ(true, config.started_);
        EXPECT_EQ(IS_ON, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierAddTest033
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TestProperty testProperty;
    testProperty.hoursWest = std::make_optional(HOURS_WEST);
    auto frameNode = CreateTextClockParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(1);
    auto controller = pattern->GetTextClockController();
    ASSERT_NE(controller, nullptr);
    controller->Start();
    controller->Stop();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(HOURS_WEST, config.timeZoneOffset_);
        EXPECT_EQ(false, config.started_);
        EXPECT_EQ(IS_ON, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierAddTest034
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TestProperty testProperty;
    float hoursWest = 8;
    testProperty.hoursWest = std::make_optional(hoursWest);
    auto frameNode = CreateTextClockParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(1);

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(hoursWest, config.timeZoneOffset_);
        EXPECT_EQ(true, config.started_);
        EXPECT_EQ(IS_ON, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierAddTest035
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest035, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TestProperty testProperty;
    float hoursWest = 8;
    testProperty.hoursWest = std::make_optional(hoursWest);
    auto frameNode = CreateTextClockParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(1);
    auto controller = pattern->GetTextClockController();
    ASSERT_NE(controller, nullptr);
    controller->Start();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(hoursWest, config.timeZoneOffset_);
        EXPECT_EQ(true, config.started_);
        EXPECT_EQ(IS_ON, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierAddTest036
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierAddTestNG, TextClockContentModifierAddTest036, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and get frameNode.
     */
    TestProperty testProperty;
    float hoursWest = 8;
    testProperty.hoursWest = std::make_optional(hoursWest);
    auto frameNode = CreateTextClockParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextClockConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(1);
    auto controller = pattern->GetTextClockController();
    ASSERT_NE(controller, nullptr);
    controller->Start();
    controller->Stop();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(hoursWest, config.timeZoneOffset_);
        EXPECT_EQ(false, config.started_);
        EXPECT_EQ(IS_ON, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}
} // namespace OHOS::Ace::NG