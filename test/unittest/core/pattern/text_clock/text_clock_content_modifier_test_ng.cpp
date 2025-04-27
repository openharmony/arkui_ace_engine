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

class TextClockContentModifierTestNG : public testing::Test {
protected:
    static RefPtr<FrameNode> CreateTextClockParagraph(const TestProperty& testProperty);
};

RefPtr<FrameNode> TextClockContentModifierTestNG::CreateTextClockParagraph(const TestProperty& testProperty)
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
 * @tc.name: TextClockContentModifierTest001
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock.
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

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(HOURS_WEST, config.timeZoneOffset_);
        EXPECT_EQ(true, config.started_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierTest002
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock.
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
    auto controller = pattern->GetTextClockController();
    ASSERT_NE(controller, nullptr);
    controller->Start();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(HOURS_WEST, config.timeZoneOffset_);
        EXPECT_EQ(true, config.started_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierTest003
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest003, TestSize.Level1)
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
    auto controller = pattern->GetTextClockController();
    ASSERT_NE(controller, nullptr);
    controller->Start();
    controller->Stop();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(HOURS_WEST, config.timeZoneOffset_);
        EXPECT_EQ(false, config.started_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierTest004
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest004, TestSize.Level1)
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

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(hoursWest, config.timeZoneOffset_);
        EXPECT_EQ(true, config.started_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierTest005
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest005, TestSize.Level1)
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
    auto controller = pattern->GetTextClockController();
    ASSERT_NE(controller, nullptr);
    controller->Start();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [=](TextClockConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(hoursWest, config.timeZoneOffset_);
        EXPECT_EQ(true, config.started_);
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierTest006
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest006, TestSize.Level1)
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
        return nullptr;
    };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextClockContentModifierTest007
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest007, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(false);

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
 * @tc.name: TextClockContentModifierTest008
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest008, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(false);
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
 * @tc.name: TextClockContentModifierTest009
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest009, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(false);
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
 * @tc.name: TextClockContentModifierTest010
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest010, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(false);

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
 * @tc.name: TextClockContentModifierTest011
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest011, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(false);
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
 * @tc.name: TextClockContentModifierTest012
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest012, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(false);
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
 * @tc.name: TextClockContentModifierTest013
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest013, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(IS_ON);

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
 * @tc.name: TextClockContentModifierTest014
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest014, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(IS_ON);
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
 * @tc.name: TextClockContentModifierTest015
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest015, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(IS_ON);
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
 * @tc.name: TextClockContentModifierTest016
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest016, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(IS_ON);

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
 * @tc.name: TextClockContentModifierTest017
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest017, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(IS_ON);
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
 * @tc.name: TextClockContentModifierTest018
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest018, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(IS_ON);
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
 * @tc.name: TextClockContentModifierTest019
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest019, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(false);

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
 * @tc.name: TextClockContentModifierTest020
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest020, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(false);
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
 * @tc.name: TextClockContentModifierTest021
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest021, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(false);
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
 * @tc.name: TextClockContentModifierTest022
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest022, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(false);

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
 * @tc.name: TextClockContentModifierTest023
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest023, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(false);
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
 * @tc.name: TextClockContentModifierTest024
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest024, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(false);
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
 * @tc.name: TextClockContentModifierTest025
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest025, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
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
 * @tc.name: TextClockContentModifierTest026
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest026, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
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
 * @tc.name: TextClockContentModifierTest027
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest027, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
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
 * @tc.name: TextClockContentModifierTest028
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest028, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
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
 * @tc.name: TextClockContentModifierTest029
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest029, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
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
 * @tc.name: TextClockContentModifierTest030
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest030, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
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
 * @tc.name: TextClockContentModifierTest031
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest031, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
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
 * @tc.name: TextClockContentModifierTest032
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest032, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
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
 * @tc.name: TextClockContentModifierTest033
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest033, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
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
 * @tc.name: TextClockContentModifierTest034
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest034, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
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
 * @tc.name: TextClockContentModifierTest035
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest035, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
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
 * @tc.name: TextClockContentModifierTest036
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest036, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
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
 * @tc.name: TextClockContentModifierTest037
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest037, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(IS_ON);

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
 * @tc.name: TextClockContentModifierTest038
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest038, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(IS_ON);
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
 * @tc.name: TextClockContentModifierTest039
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest039, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(IS_ON);
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
 * @tc.name: TextClockContentModifierTest040
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest040, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(IS_ON);

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
 * @tc.name: TextClockContentModifierTest041
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest041, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(IS_ON);
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
 * @tc.name: TextClockContentModifierTest042
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierTestNG, TextClockContentModifierTest042, TestSize.Level1)
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
    auto eventHub = frameNode->GetOrCreateEventHub<NG::TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(IS_ON);
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
