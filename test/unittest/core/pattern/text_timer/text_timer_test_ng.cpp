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

#include <optional>
#include <string>

#include "gtest/gtest.h"

#define private public

#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/common/mock_theme_manager.h"

#include "base/json/json_util.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/texttimer/text_timer_layout_property.h"
#include "core/components_ng/pattern/texttimer/text_timer_model_ng.h"
#include "core/components_ng/pattern/texttimer/text_timer_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
constexpr double INPUT_COUNT = 60000.0;
constexpr double INPUT_COUNT_2 = 20000.0;
constexpr bool IS_COUNT_DOWN = false;
constexpr bool IS_COUNT_DOWN_2 = true;
const std::string TEXT_TIMER_FORMAT = "HH:mm:ss.SSS";
const std::u16string FORMAT_DATA = u"08:00:00";
const int64_t UTC_1 = 1000000000000;
const int64_t UTC_2 = 2000000000000;
const int64_t ELAPSED_TIME_1 = 100;
const int64_t ELAPSED_TIME_2 = 200;
const std::string EMPTY_TEXT = "";
const std::string TEXTTIMER_CONTENT = "08:00:00";
const Dimension FONT_SIZE_VALUE = Dimension(20.1, DimensionUnit::PX);
const Color TEXT_COLOR_VALUE = Color::FromRGB(255, 100, 100);
const Shadow TEXT_SHADOW1 = Shadow(0, 0, Offset(), Color::RED);
const Shadow TEXT_SHADOW2 = Shadow(0, 0, Offset(), Color::WHITE);
const std::vector<Shadow> TEXT_SHADOWS { TEXT_SHADOW1, TEXT_SHADOW2 };
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
    std::optional<std::vector<Shadow>> textShadow = std::nullopt;
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
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textTheme = AceType::MakeRefPtr<TextTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textTheme));
    MockParagraph::GetOrCreateMockParagraph();
}

void TextTimerTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockParagraph::TearDown();
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
    if (testProperty.textShadow.has_value()) {
        textTimerModel.SetTextShadow(testProperty.textShadow.value());
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
    return AceType::Claim<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode()); // TextTimerView pop
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
    testProperty.textShadow = std::make_optional(TEXT_SHADOWS);
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
    EXPECT_EQ(textTimerLayoutProperty->GetTextShadow(), TEXT_SHADOWS);
    EXPECT_EQ(textTimerLayoutProperty->GetItalicFontStyle(), ITALIC_FONT_STYLE_VALUE);
    EXPECT_EQ(textTimerLayoutProperty->GetFontWeight(), FONT_WEIGHT_VALUE);
    EXPECT_EQ(textTimerLayoutProperty->GetFontFamily(), FONT_FAMILY_VALUE);

    textTimerLayoutProperty->UpdateFontFamily(FONT_FAMILY_VALUE);
    auto json = JsonUtil::Create(true);
    textTimerLayoutProperty->ToJsonValue(json, filter);
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
    int64_t utc = UTC_1;
    int64_t elapsedTime = ELAPSED_TIME_1;
    auto onChange = [&utc, &elapsedTime](int64_t isUtc, int64_t isElapsedTime) {
        utc = isUtc;
        elapsedTime = isElapsedTime;
    };
    textTimerModel.SetOnTimer(onChange);

    /**
     * @tc.steps: step2. get texttimer frameNode and event.
     * @tc.expected: step2. function is called.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    RefPtr<TextTimerEventHub> eventHub = frameNode->GetOrCreateEventHub<NG::TextTimerEventHub>();
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

/**
 * @tc.name: TextTimerTest004
 * @tc.desc: Test InitTimerDisplay of TextTimerPattern.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerTestNg, TextTimerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get pattern and layoutProperty.
     * @tc.expected: step2. UpdateTextLayoutProperty function is called.
     */
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    EXPECT_NE(pattern, nullptr);
    auto host = pattern->GetHost();
    EXPECT_NE(host, nullptr);
    auto textTimerProperty = host->GetLayoutProperty<TextTimerLayoutProperty>();
    EXPECT_NE(textTimerProperty, nullptr);
    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(textLayoutProperty, nullptr);

    pattern->UpdateTextLayoutProperty(textTimerProperty, textLayoutProperty);

    /**
     * @tc.steps: step3. get the properties of all settings.
     * @tc.expected: step3. check whether the properties is correct.
     */
    EXPECT_FALSE(textLayoutProperty->HasFontSize());
    EXPECT_FALSE(textLayoutProperty->HasTextColor());
    EXPECT_FALSE(textLayoutProperty->HasItalicFontStyle());
    EXPECT_FALSE(textLayoutProperty->HasFontWeight());
    EXPECT_FALSE(textLayoutProperty->HasFontFamily());
}

/**
 * @tc.name: TextTimerTest005
 * @tc.desc: Test InitTimerDisplay of TextTimerPattern.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerTestNg, TextTimerTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.fontSize = std::make_optional(FONT_SIZE_VALUE);
    testProperty.fontWeight = std::make_optional(FONT_WEIGHT_VALUE);
    testProperty.textColor = std::make_optional(TEXT_COLOR_VALUE);
    testProperty.textShadow = std::make_optional(TEXT_SHADOWS);
    testProperty.italicFontStyle = std::make_optional(ITALIC_FONT_STYLE_VALUE);
    testProperty.fontFamily = std::make_optional(FONT_FAMILY_VALUE);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get pattern and layoutProperty.
     * @tc.expected: step2. UpdateTextLayoutProperty function is called.
     */
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    EXPECT_NE(pattern, nullptr);
    auto host = pattern->GetHost();
    EXPECT_NE(host, nullptr);
    auto textTimerProperty = host->GetLayoutProperty<TextTimerLayoutProperty>();
    EXPECT_NE(textTimerProperty, nullptr);
    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(textLayoutProperty, nullptr);

    pattern->UpdateTextLayoutProperty(textTimerProperty, textLayoutProperty);

    /**
     * @tc.steps: step3. get the properties of all settings.
     * @tc.expected: step3. check whether the properties is correct.
     */
    EXPECT_EQ(textLayoutProperty->GetFontSize(), FONT_SIZE_VALUE);
    EXPECT_EQ(textLayoutProperty->GetTextColor(), TEXT_COLOR_VALUE);
    EXPECT_EQ(textLayoutProperty->GetItalicFontStyle(), ITALIC_FONT_STYLE_VALUE);
    EXPECT_EQ(textLayoutProperty->GetFontWeight(), FONT_WEIGHT_VALUE);
    EXPECT_EQ(textLayoutProperty->GetFontFamily(), FONT_FAMILY_VALUE);
}

/**
 * @tc.name: TextTimerTest006
 * @tc.desc: Test GetFormatDuration of TextTimerPattern.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerTestNg, TextTimerTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.format = std::make_optional(TEXT_TIMER_FORMAT);
    testProperty.inputCount = std::make_optional(INPUT_COUNT);
    testProperty.isCountDown = std::make_optional(IS_COUNT_DOWN);
    testProperty.fontSize = std::make_optional(FONT_SIZE_VALUE);
    testProperty.textColor = std::make_optional(TEXT_COLOR_VALUE);
    testProperty.textShadow = std::make_optional(TEXT_SHADOWS);
    testProperty.italicFontStyle = std::make_optional(ITALIC_FONT_STYLE_VALUE);
    testProperty.fontWeight = std::make_optional(FONT_WEIGHT_VALUE);
    testProperty.fontFamily = std::make_optional(FONT_FAMILY_VALUE);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get pattern and layoutProperty.
     * @tc.expected: step2.
     */
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto textTimerProperty = host->GetLayoutProperty<TextTimerLayoutProperty>();
    ASSERT_NE(textTimerProperty, nullptr);
    const int32_t hourOfMinute = 60;
    const int32_t minuteOfSeconds = 60;
    const int32_t secondsOfMillisecond = 1000;
    uint64_t duration = hourOfMinute * minuteOfSeconds * secondsOfMillisecond;

    /**
     * @tc.steps: step3.GetFormatDuration function is called.
     * @tc.expected: step3.  Check whether the return value is correct.
     */
    std::string format = TEXT_TIMER_FORMAT;
    textTimerProperty->UpdateFormat(format);
    EXPECT_EQ(pattern->GetFormatDuration(duration), duration);
    EXPECT_EQ(pattern->GetMillisecondsDuration(1), 1);

    format = "HH:mm:ss";
    textTimerProperty->UpdateFormat(format);
    EXPECT_EQ(pattern->GetFormatDuration(duration), hourOfMinute * minuteOfSeconds);
    EXPECT_EQ(pattern->GetMillisecondsDuration(1), secondsOfMillisecond);

    format = "HH:mm";
    textTimerProperty->UpdateFormat(format);
    EXPECT_EQ(pattern->GetFormatDuration(duration), hourOfMinute);
    EXPECT_EQ(pattern->GetMillisecondsDuration(1), secondsOfMillisecond * minuteOfSeconds);

    format = "HH";
    textTimerProperty->UpdateFormat(format);
    EXPECT_EQ(pattern->GetFormatDuration(duration), 1);
    EXPECT_EQ(pattern->GetMillisecondsDuration(1), duration);
}

/**
 * @tc.name: TextTimerTest007
 * @tc.desc: Test GetTextNode of TextTimerPattern.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerTestNg, TextTimerTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.format = std::make_optional(TEXT_TIMER_FORMAT);
    testProperty.inputCount = std::make_optional(INPUT_COUNT);
    testProperty.isCountDown = std::make_optional(IS_COUNT_DOWN);
    testProperty.fontSize = std::make_optional(FONT_SIZE_VALUE);
    testProperty.textColor = std::make_optional(TEXT_COLOR_VALUE);
    testProperty.textShadow = std::make_optional(TEXT_SHADOWS);
    testProperty.italicFontStyle = std::make_optional(ITALIC_FONT_STYLE_VALUE);
    testProperty.fontWeight = std::make_optional(FONT_WEIGHT_VALUE);
    testProperty.fontFamily = std::make_optional(FONT_FAMILY_VALUE);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get pattern and layoutProperty.
     * @tc.expected: step2.
     */
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(host->GetLastChild());
    ASSERT_NE(textNode, nullptr);

    /**
     * @tc.steps: step3.GetTextNode function is called.
     * @tc.expected: step3. Check whether the return value is correct.
     */
    textNode->tag_ = V2::TEXTTIMER_ETS_TAG;
    EXPECT_EQ(pattern->GetTextNode(), nullptr);

    textNode->tag_ = V2::TEXT_ETS_TAG;
    EXPECT_NE(pattern->GetTextNode(), nullptr);
}

/**
 * @tc.name: TextTimerTest008
 * @tc.desc: Test OnVisibleAreaChange of TextTimerPattern.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerTestNg, TextTimerTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get pattern and layoutProperty.
     * @tc.expected: step2.
     */
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);

    pattern->InitTimerDisplay();
    pattern->scheduler_->callback_(1);
    EXPECT_NE(pattern->scheduler_, nullptr);

    /**
     * @tc.steps: step3.OnVisibleAreaChange function is called.
     * @tc.expected: step3. Check whether the value is correct.
     */
    int32_t length = host->GetChildren().size();
    pattern->OnVisibleAreaChange(true);
    EXPECT_EQ(host->GetChildren().size(), length);

    auto childNode = AceType::DynamicCast<FrameNode>(host->GetFirstChild());
    ASSERT_NE(childNode, nullptr);

    pattern->OnVisibleAreaChange(true);
    EXPECT_EQ(host->GetChildren().size(), length);
    EXPECT_EQ(pattern->textNode_, nullptr);

    pattern->OnVisibleAreaChange(false);
    EXPECT_EQ(host->GetChildren().size(), length);
}

/**
 * @tc.name: TextTimerLayoutAlgorithmTest001
 * @tc.desc: Test LayoutAlgorithm of TextTimer.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerTestNg, TextTimerLayoutAlgorithmTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.format = std::make_optional(TEXT_TIMER_FORMAT);
    testProperty.inputCount = std::make_optional(INPUT_COUNT);
    testProperty.isCountDown = std::make_optional(IS_COUNT_DOWN);
    testProperty.fontSize = std::make_optional(FONT_SIZE_VALUE);
    testProperty.textColor = std::make_optional(TEXT_COLOR_VALUE);
    testProperty.italicFontStyle = std::make_optional(ITALIC_FONT_STYLE_VALUE);
    testProperty.textShadow = std::make_optional(TEXT_SHADOWS);
    testProperty.fontWeight = std::make_optional(FONT_WEIGHT_VALUE);
    testProperty.fontFamily = std::make_optional(FONT_FAMILY_VALUE);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<TextTimerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step2. create childFrameNode.
     * @tc.expected: step2. check whether the properties is correct.
     */
    auto textNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, textNodeId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(textNode, nullptr);
    RefPtr<GeometryNode> textGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto textLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textNode, textGeometryNode, textNode->GetLayoutProperty());
    ASSERT_NE(textLayoutWrapper, nullptr);
    textLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(textNode->GetPattern()->CreateLayoutAlgorithm()));
    textNode->MountToParent(frameNode);
    layoutWrapper->AppendChild(textLayoutWrapper);
    EXPECT_EQ(layoutWrapper->currentChildCount_, 1);

    auto layoutAlgorithm = AceType::MakeRefPtr<TextTimerLayoutAlgorithm>();
    layoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(geometryNode->GetFrameSize(), SizeF());

    LayoutConstraintF contentConstraint;
    contentConstraint.selfIdealSize.SetWidth(200.f);
    contentConstraint.selfIdealSize.SetHeight(200.f);
    layoutProperty->UpdateLayoutConstraint(contentConstraint);
    layoutProperty->UpdateContentConstraint();
    layoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(geometryNode->GetFrameSize(), SizeF(200.f, 200.f));
}

/**
 * @tc.name: TextTimerTest009
 * @tc.desc: Test UpdateTextTimer of TextTimerPattern.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerTestNg, TextTimerTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.format = std::make_optional(TEXT_TIMER_FORMAT);
    testProperty.inputCount = std::make_optional(INPUT_COUNT);
    testProperty.isCountDown = std::make_optional(true);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextTimerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetFormat(), TEXT_TIMER_FORMAT);
    EXPECT_EQ(layoutProperty->GetInputCount(), INPUT_COUNT);
    EXPECT_EQ(layoutProperty->GetIsCountDown(), true);

    /**
     * @tc.steps: step2. get the properties of all settings.
     * @tc.expected: step2. check whether the properties is correct.
     */
    auto textNode = pattern->GetTextNode();
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->Reset();
    EXPECT_EQ(textLayoutProperty->GetFontStyle(), nullptr);
    EXPECT_EQ(textLayoutProperty->GetTextLineStyle(), nullptr);
    EXPECT_FALSE(textLayoutProperty->HasContent());

    pattern->textTimerController_ = nullptr;
    pattern->OnModifyDone();
    textLayoutProperty->CleanDirty();
    pattern->scheduler_->callback_(1);
    EXPECT_EQ(pattern->textTimerController_, nullptr);
    EXPECT_EQ(textLayoutProperty->GetPropertyChangeFlag(), PROPERTY_UPDATE_NORMAL);

    textLayoutProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_LAYOUT);
    pattern->scheduler_->callback_(1);
    EXPECT_EQ(textLayoutProperty->GetPropertyChangeFlag(), PROPERTY_UPDATE_LAYOUT);
}

/**
 * @tc.name: TextTimerTest010
 * @tc.desc: Test the text shadows of texttimer.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerTestNg, TextTimerTest010, TestSize.Level1)
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
    testProperty.textShadow = std::make_optional(TEXT_SHADOWS);
    testProperty.italicFontStyle = std::make_optional(ITALIC_FONT_STYLE_VALUE);
    testProperty.fontWeight = std::make_optional(FONT_WEIGHT_VALUE);
    testProperty.fontFamily = std::make_optional(FONT_FAMILY_VALUE);

    /**
     * @tc.steps: step2. create frameNode to get layout properties.
     * @tc.expected: step2. related function is called.
     */
    RefPtr<FrameNode> frameNode = CreateTextTimerParagraph(testProperty);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    RefPtr<TextTimerLayoutProperty> textTimerLayoutProperty =
        AceType::DynamicCast<TextTimerLayoutProperty>(layoutProperty);

    /**
     * @tc.steps: step3. get the properties of all settings.
     * @tc.expected: step3. check whether the properties is correct.
     */
    EXPECT_EQ(textTimerLayoutProperty->GetFormat(), TEXT_TIMER_FORMAT);
    EXPECT_EQ(textTimerLayoutProperty->GetInputCount(), INPUT_COUNT);
    EXPECT_EQ(textTimerLayoutProperty->GetIsCountDown(), IS_COUNT_DOWN);
    EXPECT_EQ(textTimerLayoutProperty->GetFontSize(), FONT_SIZE_VALUE);
    EXPECT_EQ(textTimerLayoutProperty->GetTextColor(), TEXT_COLOR_VALUE);
    EXPECT_EQ(textTimerLayoutProperty->GetTextShadow(), TEXT_SHADOWS);
    EXPECT_EQ(textTimerLayoutProperty->GetItalicFontStyle(), ITALIC_FONT_STYLE_VALUE);
    EXPECT_EQ(textTimerLayoutProperty->GetFontWeight(), FONT_WEIGHT_VALUE);
    EXPECT_EQ(textTimerLayoutProperty->GetFontFamily(), FONT_FAMILY_VALUE);

    /**
     * @tc.steps: step4. get the json value after set the shadows.
     * @tc.expected: step4. the value is "textShadow", check whether the properties is correct.
     */
    textTimerLayoutProperty->UpdateTextShadow(TEXT_SHADOWS);
    auto json = JsonUtil::Create(true);
    textTimerLayoutProperty->ToJsonValue(json, filter);
    EXPECT_TRUE(json->Contains("textShadow"));
    EXPECT_EQ(textTimerLayoutProperty->GetTextShadow(), TEXT_SHADOWS);
}

/**
 * @tc.name: TextTimerTest011
 * @tc.desc: Test the SetBuilderFunc and get value.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerTestNg, TextTimerTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode and init property.
     */
    TestProperty testProperty;
    testProperty.inputCount = std::make_optional(INPUT_COUNT);
    testProperty.isCountDown = std::make_optional(IS_COUNT_DOWN);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto node = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(IS_COUNT_DOWN, config.isCountDown_);
                EXPECT_EQ(INPUT_COUNT, config.count_);
                return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */

    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextTimerTest012
 * @tc.desc: Test the SetBuilderFunc and get value.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerTestNg, TextTimerTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.inputCount = std::make_optional(INPUT_COUNT_2);
    testProperty.isCountDown = std::make_optional(IS_COUNT_DOWN_2);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto node = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(IS_COUNT_DOWN_2, config.isCountDown_);
                EXPECT_EQ(INPUT_COUNT_2, config.count_);
                return nullptr;
            };

     /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextTimerTest013
 * @tc.desc: Test the SetBuilderFunc and get value.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerTestNg, TextTimerTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.inputCount = std::make_optional(INPUT_COUNT_2);
    testProperty.isCountDown = std::make_optional(IS_COUNT_DOWN_2);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitTimerDisplay();
    auto node = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(IS_COUNT_DOWN_2, config.isCountDown_);
                EXPECT_EQ(INPUT_COUNT_2, config.count_);
                EXPECT_EQ(false, config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step2. start timer and check value.
     */
    auto nextNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(IS_COUNT_DOWN_2, config.isCountDown_);
                EXPECT_EQ(INPUT_COUNT_2, config.count_);
                EXPECT_TRUE(config.started_);
                return nullptr;
            };
    pattern->HandleStart();
    pattern->SetBuilderFunc(nextNode);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextTimerTest014
 * @tc.desc: Test the SetBuilderFunc and get value.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerTestNg, TextTimerTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto node = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(ELAPSED_TIME_1, config.elapsedTime_);
                return nullptr;
            };

    /**
     * @tc.steps: step2. Tick timer and check value.
     */
    pattern->Tick(1000);
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextTimerTest015
 * @tc.desc: Test TextTimer property.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerTestNg, TextTimerTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create framenode and Init.
     */
    auto frameNode = TextTimerModelNG::CreateFrameNode(-1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    auto controller = TextTimerModelNG::InitTextController(node);
    ASSERT_NE(controller, nullptr);
    /**
     * @tc.steps: step2. SetIsCountDown.
     */
    TextTimerModelNG::SetIsCountDown(node, true);
    auto layoutProperty = frameNode->GetLayoutProperty<TextTimerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetIsCountDownValue(), true);
    TextTimerModelNG::SetInputCount(node, INPUT_COUNT);
    EXPECT_EQ(layoutProperty->GetInputCountValue(), INPUT_COUNT);

    /**
     * @tc.steps: step3. SetJSTextTimerController.
     */
    TextTimerModelNG::SetJSTextTimerController(node, controller);
    auto result = TextTimerModelNG::GetJSTextTimerController(node);
    EXPECT_NE(result, nullptr);
}

/**
 * @tc.name: TextTimerSetTextColorByUserTest001
 * @tc.desc: Test SetTextColorByUser with different conditions
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerTestNg, TextTimerSetTextColorByUserTest001, TestSize.Level1)
{
    TextTimerModelNG textTimerModel;
    textTimerModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextTimerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    textTimerModel.SetTextColorByUser(frameNode, true);
    textTimerModel.SetFontSizeByUser(frameNode, false);
    textTimerModel.SetFontWeightByUser(frameNode, false);
    textTimerModel.SetFontFamilyByUser(frameNode, false);
    textTimerModel.SetFontSizeByUser(false);
    textTimerModel.SetFontWeightByUser(false);
    textTimerModel.SetFontFamilyByUser(false);

    EXPECT_TRUE(layoutProperty->GetTextColorSetByUser());
    EXPECT_FALSE(layoutProperty->GetTextFontFamilySetByUserValue(false));
    EXPECT_FALSE(layoutProperty->GetTextFontWeightSetByUserValue(false));
    EXPECT_FALSE(layoutProperty->GetTextFontSizeSetByUserValue(false));
}

/**
 * @tc.name: TextTimerPatternTest001
 * @tc.desc: Test UpdateTextColor with different conditions
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerTestNg, TextTimerPatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextTimer node and get pattern
     */
    auto frameNode = TextTimerModelNG::CreateFrameNode(-1);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    
    /**
     * @tc.steps: step2. Test UpdateTextColor with isFirstLoad=true
     */
    Color testColor = Color::BLUE;
    pattern->UpdateTextColor(testColor, true);
    
    /**
     * @tc.expected: step3. Verify property and render context updated
     */
    auto layoutProperty = frameNode->GetLayoutProperty<TextTimerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetTextColor(), testColor);
    
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetForegroundColor(), testColor);
}

/**
 * @tc.name: TextTimerPatternTest002
 * @tc.desc: Test UpdateFontWeight
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerTestNg, TextTimerPatternTest002, TestSize.Level1)
{
    auto frameNode = TextTimerModelNG::CreateFrameNode(-1);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    
    /**
     * @tc.steps: Test with different font weights
     */
    pattern->UpdateFontWeight(FontWeight::BOLD, true);
    auto layoutProperty = frameNode->GetLayoutProperty<TextTimerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetFontWeight(), FontWeight::BOLD);
    
    // Test no update when isFirstLoad=false
    pattern->UpdateFontWeight(FontWeight::LIGHTER, false);
    EXPECT_EQ(layoutProperty->GetFontWeight(), FontWeight::BOLD);
}

/**
 * @tc.name: TextTimerPatternTest003
 * @tc.desc: Test UpdateFontSize
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerTestNg, TextTimerPatternTest003, TestSize.Level1)
{
    auto frameNode = TextTimerModelNG::CreateFrameNode(-1);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    
    const double testSizeValue = 20.0;
    Dimension testSize(testSizeValue, DimensionUnit::VP);
    pattern->UpdateFontSize(testSize, true);
    
    auto layoutProperty = frameNode->GetLayoutProperty<TextTimerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetFontSize(), testSize);
}

/**
 * @tc.name: TextTimerPatternTest004
 * @tc.desc: Test OnColorModeChange
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerTestNg, TextTimerPatternTest005, TestSize.Level1)
{
    auto frameNode = TextTimerModelNG::CreateFrameNode(-1);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    
    std::vector<std::string> fontFamilies = {"Arial", "sans-serif"};
    pattern->UpdateFontFamily(fontFamilies, true);
    
    auto layoutProperty = frameNode->GetLayoutProperty<TextTimerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetFontFamily(), fontFamilies);
}

/**
 * @tc.name: TextTimerPatternTest006
 * @tc.desc: Test OnColorConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerTestNg, TextTimerPatternTest006, TestSize.Level1)
{
    auto frameNode = TextTimerModelNG::CreateFrameNode(-1);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = false;
    pattern->OnColorConfigurationUpdate();

    g_isConfigChangePerform = true;
    pattern->OnColorConfigurationUpdate();
    auto layoutProperty = frameNode->GetLayoutProperty<TextTimerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->ResetTextColorSetByUser();
    pattern->OnColorConfigurationUpdate();

    layoutProperty->UpdateTextColorSetByUser(true);
    pattern->OnColorConfigurationUpdate();

    layoutProperty->UpdateTextColorSetByUser(false);
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto pipeline = host->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetIsSystemColorChange(true);
    auto theme = pipeline->GetTheme<TextTheme>();
    ASSERT_NE(theme, nullptr);
    Color testColor = theme->GetTextStyle().GetTextColor();
    pattern->OnColorConfigurationUpdate();

    EXPECT_EQ(layoutProperty->GetTextColor(), testColor);
}

/**
 * @tc.name: TextTimerPatternTest007
 * @tc.desc: Test model ng  SetTextShadow
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerTestNg, TextTimerPatternTest007, TestSize.Level1)
{
    TextTimerModelNG textTimerModel;
    textTimerModel.Create();
    textTimerModel.SetTextColorByUser(false);

    g_isConfigChangePerform = false;
    Shadow shadow;
    shadow.SetBlurRadius(10);
    shadow.SetOffsetX(10);
    shadow.SetOffsetY(10);
    shadow.SetColor(Color(Color::RED));
    shadow.SetShadowType(ShadowType::COLOR);
    std::vector<Shadow> setShadows;
    setShadows.emplace_back(shadow);
    textTimerModel.SetTextShadow(setShadows);
    g_isConfigChangePerform = true;
    textTimerModel.SetTextShadow(setShadows);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextTimerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetTextShadow(), setShadows);
}

/**
 * @tc.name: TextTimerPatternTest008
 * @tc.desc: Test model ng  CreateWithResourceObj
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerTestNg, TextTimerPatternTest008, TestSize.Level1)
{
    TextTimerModelNG textTimerModel;
    textTimerModel.Create();
    auto jsResourceType = JsTextTimerResourceType::TEXTCOLOR;
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    ASSERT_NE(resObj, nullptr);
    textTimerModel.CreateWithResourceObj(jsResourceType, resObj);
    jsResourceType = JsTextTimerResourceType::FONTWEIGHT;
    textTimerModel.CreateWithResourceObj(jsResourceType, resObj);
    jsResourceType = JsTextTimerResourceType::FONTSIZE;
    textTimerModel.CreateWithResourceObj(jsResourceType, resObj);
    jsResourceType = JsTextTimerResourceType::FONTFAMILY;
    textTimerModel.CreateWithResourceObj(jsResourceType, resObj);
    textTimerModel.CreateWithResourceObj(static_cast<JsTextTimerResourceType>(5), resObj);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    int32_t colorMode = static_cast<int32_t>(ColorMode::DARK);
    pattern->OnColorModeChange(colorMode);
    auto layoutProperty = frameNode->GetLayoutProperty<TextTimerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<TextTheme>();
    ASSERT_NE(theme, nullptr);
    Color testColor = theme->GetTextStyle().GetTextColor();
    EXPECT_EQ(layoutProperty->GetTextColor(), testColor);

    ResourceObjectParams params { .value = "test", .type = ResourceObjectParamType::STRING };
    std::vector<ResourceObjectParams> resObjParamsList;
    resObjParamsList.push_back(params);
    RefPtr<ResourceObject> resObjWithId =
        AceType::MakeRefPtr<ResourceObject>(100000, 100001, resObjParamsList, "com.example.test", "entry", 100000);
    RefPtr<ResourceObject> resObjId =
        AceType::MakeRefPtr<ResourceObject>(-1, 100001, resObjParamsList, "com.example.test", "entry", 100000);
    jsResourceType = JsTextTimerResourceType::TEXTCOLOR;
    textTimerModel.CreateWithResourceObj(jsResourceType, resObjId);
    jsResourceType = JsTextTimerResourceType::FONTSIZE;
    textTimerModel.CreateWithResourceObj(jsResourceType, resObjWithId);
    jsResourceType = JsTextTimerResourceType::FONTFAMILY;
    textTimerModel.CreateWithResourceObj(jsResourceType, resObjWithId);
    pattern->OnColorModeChange(colorMode);
    EXPECT_EQ(layoutProperty->GetTextColor(), testColor);
}
} // namespace OHOS::Ace::NG
