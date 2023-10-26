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

#define private public
#include <optional>
#include <string>

#include "gtest/gtest.h"

#include "base/json/json_util.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/texttimer/text_timer_layout_property.h"
#include "core/components_ng/pattern/texttimer/text_timer_model_ng.h"
#include "core/components_ng/pattern/texttimer/text_timer_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
constexpr double INPUT_COUNT = 60000.0;
constexpr bool IS_COUNT_DOWN = false;
const std::string TEXT_TIMER_FORMAT = "HH:mm:ss.SS";
const std::string FORMAT_DATA = "08:00:00";
const std::string UTC_1 = "1000000000000";
const std::string UTC_2 = "2000000000000";
const std::string ELAPSED_TIME_1 = "100";
const std::string ELAPSED_TIME_2 = "200";
const std::string EMPTY_TEXT = "";
const std::string TEXTTIMER_CONTENT = "08:00:00";
const Dimension FONT_SIZE_VALUE = Dimension(20.1, DimensionUnit::PX);
const Color TEXT_COLOR_VALUE = Color::FromRGB(255, 100, 100);
const Ace::FontStyle ITALIC_FONT_STYLE_VALUE = Ace::FontStyle::ITALIC;
const Ace::FontWeight FONT_WEIGHT_VALUE = Ace::FontWeight::W100;
const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
} // namespace

struct TestProperty {
    std::optional<std::string> format = std::nullopt;
    std::optional<double> inputCount = std::nullopt;
    std::optional<bool> isCountDown = std::nullopt;
    std::optional<Dimension> fontSize = std::nullopt;
    std::optional<Color> textColor = std::nullopt;
    std::optional<Ace::FontStyle> italicFontStyle = std::nullopt;
    std::optional<Ace::FontWeight> fontWeight = std::nullopt;
    std::optional<std::vector<std::string>> fontFamily = std::nullopt;
};

class TextTimerTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    static RefPtr<FrameNode> CreateTextTimerParagraph(const TestProperty& testProperty);
};

void TextTimerTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void TextTimerTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

RefPtr<FrameNode> TextTimerTestNg::CreateTextTimerParagraph(const TestProperty& testProperty)
{
    TextTimerModelNG textTimerModel;
    textTimerModel.Create();
    if (testProperty.format.has_value()) {
        textTimerModel.SetFormat(testProperty.format.value());
    }
    if (testProperty.inputCount.has_value()) {
        textTimerModel.SetInputCount(testProperty.inputCount.value());
    }
    if (testProperty.isCountDown.has_value()) {
        textTimerModel.SetIsCountDown(testProperty.isCountDown.value());
    }
    if (testProperty.fontSize.has_value()) {
        textTimerModel.SetFontSize(testProperty.fontSize.value());
    }
    if (testProperty.textColor.has_value()) {
        textTimerModel.SetTextColor(testProperty.textColor.value());
    }
    if (testProperty.italicFontStyle.has_value()) {
        textTimerModel.SetItalicFontStyle(testProperty.italicFontStyle.value());
    }
    if (testProperty.fontWeight.has_value()) {
        textTimerModel.SetFontWeight(testProperty.fontWeight.value());
    }
    if (testProperty.fontFamily.has_value()) {
        textTimerModel.SetFontFamily(testProperty.fontFamily.value());
    }
    return ViewStackProcessor::GetInstance()->GetMainFrameNode(); // TextTimerView pop
}

/**
 * @tc.name: TextTimerTest001
 * @tc.desc: Test all the properties of texttimer.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerTestNg, TextTimerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of texttimer.
     */
    TestProperty testProperty;
    testProperty.format = std::make_optional(TEXT_TIMER_FORMAT);
    testProperty.inputCount = std::make_optional(INPUT_COUNT);
    testProperty.isCountDown = std::make_optional(IS_COUNT_DOWN);
    testProperty.fontSize = std::make_optional(FONT_SIZE_VALUE);
    testProperty.textColor = std::make_optional(TEXT_COLOR_VALUE);
    testProperty.italicFontStyle = std::make_optional(ITALIC_FONT_STYLE_VALUE);
    testProperty.fontWeight = std::make_optional(FONT_WEIGHT_VALUE);
    testProperty.fontFamily = std::make_optional(FONT_FAMILY_VALUE);

    /**
     * @tc.steps: step2. create frameNode to get layout properties.
     * @tc.expected: step2. related function is called.
     */
    RefPtr<FrameNode> frameNode = CreateTextTimerParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<TextTimerLayoutProperty> textTimerLayoutProperty =
        AceType::DynamicCast<TextTimerLayoutProperty>(layoutProperty);
    EXPECT_NE(textTimerLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. get the properties of all settings.
     * @tc.expected: step3. check whether the properties is correct.
     */
    EXPECT_EQ(textTimerLayoutProperty->GetFormat(), TEXT_TIMER_FORMAT);
    EXPECT_EQ(textTimerLayoutProperty->GetInputCount(), INPUT_COUNT);
    EXPECT_EQ(textTimerLayoutProperty->GetIsCountDown(), IS_COUNT_DOWN);
    EXPECT_EQ(textTimerLayoutProperty->GetFontSize(), FONT_SIZE_VALUE);
    EXPECT_EQ(textTimerLayoutProperty->GetTextColor(), TEXT_COLOR_VALUE);
    EXPECT_EQ(textTimerLayoutProperty->GetItalicFontStyle(), ITALIC_FONT_STYLE_VALUE);
    EXPECT_EQ(textTimerLayoutProperty->GetFontWeight(), FONT_WEIGHT_VALUE);
    EXPECT_EQ(textTimerLayoutProperty->GetFontFamily(), FONT_FAMILY_VALUE);

    textTimerLayoutProperty->UpdateFontFamily(FONT_FAMILY_VALUE);
    auto json = JsonUtil::Create(true);
    textTimerLayoutProperty->ToJsonValue(json);
    EXPECT_EQ(textTimerLayoutProperty->GetFontFamily(), FONT_FAMILY_VALUE);
}

/**
 * @tc.name: TextTimerTest002
 * @tc.desc: Test the entry function OnModifyDone of texttimer and related function.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerTestNg, TextTimerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.format = std::make_optional(TEXT_TIMER_FORMAT);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild());
    ASSERT_NE(textNode, nullptr);

    /**
     * @tc.steps: step2. get pattern and layoutProperty.
     * @tc.expected: step2. related function is called.
     */
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    EXPECT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextTimerLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. call OnModifyDone and tick when default properties.
     * @tc.expected: step3. check whether the content is correct.
     */
    pattern->InitTextTimerController();
    pattern->OnModifyDone();
    constexpr int32_t duration = 100;
    pattern->Tick(duration);
    EXPECT_EQ(textLayoutProperty->GetContent(), FORMAT_DATA);

    /**
     * @tc.steps: step4. call OnModifyDone and tick when set properties.
     * @tc.expected: step4. check whether the properties and content is correct.
     */
    layoutProperty->UpdateInputCount(0);
    EXPECT_EQ(layoutProperty->GetInputCount(), 0);
    layoutProperty->UpdateIsCountDown(true);
    EXPECT_EQ(layoutProperty->GetIsCountDown(), true);
    pattern->OnModifyDone();
    pattern->Tick(0);
    EXPECT_EQ(textLayoutProperty->GetContent(), FORMAT_DATA);

    /**
     * @tc.steps: step5. get controller to call callback function.
     */
    auto controller = pattern->GetTextTimerController();
    ASSERT_NE(controller, nullptr);

    /**
     * @tc.steps: step6. when the running status in scheduler is false, call related functions.
     * @tc.expected: step6. Check whether relevant parameters are correct.
     */
    pattern->scheduler_->isRunning_ = false;
    pattern->elapsedTime_ = 1;
    controller->Start();
    pattern->scheduler_->isRunning_ = false;
    controller->Reset();
    pattern->scheduler_->isRunning_ = false;
    controller->Pause();
    EXPECT_EQ(pattern->elapsedTime_, 0);

    /**
     * @tc.steps: step7. when the running status in scheduler is true, call related functions.
     * @tc.expected: step7. Check whether relevant parameters are correct.
     */
    pattern->scheduler_->isRunning_ = true;
    pattern->elapsedTime_ = 1;
    controller->Start();
    pattern->scheduler_->isRunning_ = true;
    controller->Pause();
    pattern->scheduler_->isRunning_ = true;
    controller->Reset();
    EXPECT_EQ(pattern->elapsedTime_, 0);

    /**
     * @tc.steps: step8. when scheduler is nullptr, call related functions.
     * @tc.expected: step8. Check whether relevant parameters are correct.
     */
    pattern->scheduler_ = nullptr;
    pattern->elapsedTime_ = 1;
    controller->Start();
    controller->Pause();
    controller->Reset();
    EXPECT_EQ(pattern->elapsedTime_, 0);
}

/**
 * @tc.name: TextTimerTest003
 * @tc.desc: Test event function of texttimer.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerTestNg, TextTimerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer and set event.
     */
    TextTimerModelNG textTimerModel;
    textTimerModel.Create();
    std::string utc = UTC_1;
    std::string elapsedTime = ELAPSED_TIME_1;
    auto onChange = [&utc, &elapsedTime](const std::string& isUtc, const std::string& isElapsedTime) {
        utc = isUtc;
        elapsedTime = isElapsedTime;
    };
    textTimerModel.SetOnTimer(onChange);

    /**
     * @tc.steps: step2. get texttimer frameNode and event.
     * @tc.expected: step2. function is called.
     */
    RefPtr<FrameNode> frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    RefPtr<TextTimerEventHub> eventHub = frameNode->GetEventHub<NG::TextTimerEventHub>();
    EXPECT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step3. call the event entry function.
     * @tc.expected: step3. check whether the value is correct.
     */
    eventHub->FireChangeEvent(UTC_2, ELAPSED_TIME_2);
    EXPECT_EQ(utc, UTC_2);
    EXPECT_EQ(elapsedTime, ELAPSED_TIME_2);
}

/**
 * @tc.name: TextTimerAccessibilityPropertyIsScrollable001
 * @tc.desc: Test IsScrollable of textTimerAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerTestNg, TextTimerAccessibilityPropertyIsScrollable001, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.format = std::make_optional(TEXT_TIMER_FORMAT);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(textLayoutProperty, nullptr);
    auto textTimerAccessibilityProperty = frameNode->GetAccessibilityProperty<TextTimerAccessibilityProperty>();
    ASSERT_NE(textTimerAccessibilityProperty, nullptr);
    textTimerAccessibilityProperty->SetHost(AceType::WeakClaim(AceType::RawPtr(frameNode)));

    EXPECT_EQ(textTimerAccessibilityProperty->GetText(), EMPTY_TEXT);

    textLayoutProperty->UpdateContent(TEXTTIMER_CONTENT);
    EXPECT_EQ(textTimerAccessibilityProperty->GetText(), TEXTTIMER_CONTENT);
}
} // namespace OHOS::Ace::NG
