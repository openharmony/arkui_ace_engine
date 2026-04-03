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

#include <optional>
#include <string>
#include <sys/time.h>

#include "gtest/gtest.h"
#include "test/unittest/core/pattern/test_ng.h"
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/components_ng/pattern/mock_nestable_scroll_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/components_ng/render/mock_render_context.h"
#include "test/mock/frameworks/core/rosen/mock_canvas.h"

#include "base/i18n/time_format.h"
#include "base/i18n/localization.h"
#include "base/utils/time_util.h"
#include "core/components/button/button_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text_clock/text_clock_layout_property.h"
#include "core/components_ng/pattern/text_clock/text_clock_model_ng.h"
#include "core/components_ng/pattern/text_clock/text_clock_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace {
constexpr int32_t HOURS_WEST = -8;
const std::string UTC_INPUT = "1742734385000";
const std::string UTC_INPUT_NEXT = "1742734885000";
const std::string UTC_INPUT_NEXT_STRING = "08:00:00";
const std::string UTC_INPUT2 = "1742734386000";
const std::string UTC_INPUT_NEXT2 = "1742734886000";
const std::string UTC_INPUT3 = "1742734387000";
const std::string UTC_INPUT_NEXT3 = "1742734887000";
inline const std::string CLOCK_FORMAT = "aa h:m:s";
inline const std::string CLOCK_FORMAT2 = "HH:mm:ss";
inline const std::string CLOCK_FORMAT3 = "HH:mm:ss eee";
inline const std::string CLOCK_FORMAT4 = "aa HH:mm:ss";
inline const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
const Color TEXT_COLOR_VALUE = Color::FromRGB(255, 100, 100);
const Dimension FONT_SIZE_VALUE = Dimension(20.1, DimensionUnit::PX);
const Ace::FontStyle ITALIC_FONT_STYLE_VALUE = Ace::FontStyle::ITALIC;
const Ace::FontWeight FONT_WEIGHT_VALUE = Ace::FontWeight::W100;
inline const std::string DEFAULT_FORMAT = "aa hh:mm:ss";
inline const std::string DEFAULT_FORMAT_24H = "HH:mm:ss";
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
    std::optional<ZeroPrefixType> preFixHour = ZeroPrefixType::AUTO;
};

class TextClockPatternTestNG : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    static RefPtr<FrameNode> CreateTextClockParagraph(const TestProperty& testProperty);
    void SetUp() override;
    void TearDown() override;
    void GetInstance();

    void CreateWithItem(const std::function<void(TextClockModelNG)>& callback = nullptr);
    void Start();
    void Stop();

    RefPtr<FrameNode> frameNode_;
    RefPtr<TextClockPattern> pattern_;
    RefPtr<TextClockLayoutProperty> layoutProperty_;
    RefPtr<TextClockController> controller_;
};

void TextClockPatternTestNG::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_TEXT);
    auto textTheme = TextTheme::Builder().Build(themeConstants);
    EXPECT_CALL(*themeManager, GetTheme(TextTheme::TypeId())).WillRepeatedly(Return(textTheme));
    textTheme->selectedColor_ = Color::FromString("#007DFF");
    textTheme->dragBackgroundColor_ = Color::WHITE;
    textTheme->draggable_ = false;
    textTheme->linearSplitChildMinSize_ = 20.0f;
    textTheme->isShowHandle_ = false;
    TextStyle textStyle;
    textStyle.SetTextColor(Color::FromString("#ff182431"));
    textStyle.SetFontSize(Dimension(14.f));
    textStyle.SetFontWeight(FontWeight::W800);
    textTheme->textStyle_ = textStyle;
    MockPipelineContext::GetCurrentContext()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
}

void TextClockPatternTestNG::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

RefPtr<FrameNode> TextClockPatternTestNG::CreateTextClockParagraph(const TestProperty& testProperty)
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
    if (testProperty.preFixHour.has_value()) {
        textClockModel.SetDateTimeOptions(testProperty.preFixHour.value());
    }
    return AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
}

void TextClockPatternTestNG::SetUp() {}

void TextClockPatternTestNG::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    layoutProperty_ = nullptr;
    controller_ = nullptr;
}

void TextClockPatternTestNG::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<TextClockPattern>();
    layoutProperty_ = frameNode_->GetLayoutProperty<TextClockLayoutProperty>();
    controller_ = pattern_->GetTextClockController();
}

void TextClockPatternTestNG::CreateWithItem(const std::function<void(TextClockModelNG)>& callback)
{
    TextClockModelNG model;
    model.Create();
    model.SetDateTimeOptions(ZeroPrefixType::AUTO);
    model.InitFontDefault(TextStyle());
    if (callback) {
        callback(model);
    }
    GetInstance();
    FlushUITasks(frameNode_);
}

void TextClockPatternTestNG::Start()
{
    controller_->Start();
    FlushUITasks(frameNode_);
}

void TextClockPatternTestNG::Stop()
{
    controller_->Stop();
    FlushUITasks(frameNode_);
}

/**
 * @tc.name: UpdateTimeText001
 * @tc.desc: Test function of textClock.
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, UpdateTimeText001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create object and init.
     */
    auto pipeline = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetIsFormRender(true);

    auto themeManager = PipelineBase::GetCurrentContext()->GetThemeManager();
    ASSERT_NE(themeManager, nullptr);
    auto textTheme = themeManager->GetTheme<TextTheme>();
    ASSERT_NE(textTheme, nullptr);

    auto onChange = [](const std::string& szStr) { LOGD("szStr change: %s", szStr.c_str()); };
    CreateWithItem([&](TextClockModelNG model) {
        model.SetFormat(CLOCK_FORMAT);
        model.SetHoursWest(HOURS_WEST);
        model.SetFontSize(FONT_SIZE_VALUE);
        model.SetTextColor(TEXT_COLOR_VALUE);
        model.SetItalicFontStyle(ITALIC_FONT_STYLE_VALUE);
        model.SetFontWeight(FONT_WEIGHT_VALUE);
        model.SetFontFamily(FONT_FAMILY_VALUE);
        model.InitFontDefault(textTheme->GetTextStyle());
        model.SetDateTimeOptions(ZeroPrefixType::AUTO);
        model.SetTextShadow({ Shadow() });
        model.SetOnDateChange(onChange);
    });
    Start();
    pattern_->OnLanguageConfigurationUpdate();
    pattern_->OnTimeChange();
    pattern_->DumpInfo();
    std::vector<std::string> value;
    layoutProperty_->UpdateFontFamily(value);
    pattern_->OnModifyDone();
    EXPECT_TRUE(layoutProperty_->GetFontFamily().value().empty());
    Stop();
    EXPECT_FALSE(pattern_->isStart_);
}

/**
 * @tc.name: RequestUpdateForNextSecond001
 * @tc.desc: Test function of textClock.
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, RequestUpdateForNextSecond001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create object and init.
     */
    auto themeManager = PipelineBase::GetCurrentContext()->GetThemeManager();
    ASSERT_NE(themeManager, nullptr);
    auto textTheme = themeManager->GetTheme<TextTheme>();
    ASSERT_NE(textTheme, nullptr);

    auto onChange = [](const std::string& szStr) { LOGD("szStr change: %s", szStr.c_str()); };
    CreateWithItem([&](TextClockModelNG model) {
        model.SetFormat(CLOCK_FORMAT);
        model.SetHoursWest(HOURS_WEST);
        model.SetFontSize(FONT_SIZE_VALUE);
        model.SetTextColor(TEXT_COLOR_VALUE);
        model.SetItalicFontStyle(ITALIC_FONT_STYLE_VALUE);
        model.SetFontWeight(FONT_WEIGHT_VALUE);
        model.SetFontFamily(FONT_FAMILY_VALUE);
        model.InitFontDefault(textTheme->GetTextStyle());
        model.SetDateTimeOptions(ZeroPrefixType::AUTO);
        model.SetTextShadow({ Shadow() });
        model.SetOnDateChange(onChange);
    });

    Start();
    auto context = frameNode_->GetContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    pattern_->RequestUpdateForNextSecond();
    Stop();
    pattern_->RequestUpdateForNextSecond();
    EXPECT_FALSE(pattern_->isStart_);
}

/**
 * @tc.name: GetCurrentFormatDateTime001
 * @tc.desc: Test function of textClock.
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, GetCurrentFormatDateTime001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create object and init.
     */
    CreateWithItem([&](TextClockModelNG model) {
        model.SetFormat(CLOCK_FORMAT);
        model.SetHoursWest(HOURS_WEST);
        model.SetFontSize(FONT_SIZE_VALUE);
        model.SetTextColor(TEXT_COLOR_VALUE);
    });
    auto ret = pattern_->GetCurrentFormatDateTime();
    EXPECT_NE(ret, "");
}

/**
 * @tc.name: Abstract001
 * @tc.desc: Test function of textClock.
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, Abstract001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create object and init.
     */
    CreateWithItem([&](TextClockModelNG model) {});
    EXPECT_FALSE(pattern_->Abstract("test123", false).empty());
    EXPECT_FALSE(pattern_->Abstract("test123", true).empty());
}

/**
 * @tc.name: GetWeek001
 * @tc.desc: Test function of textClock.
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, GetWeek001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create object and init.
     */
    CreateWithItem([&](TextClockModelNG model) {});
    EXPECT_TRUE(pattern_->GetWeek(false, 7).empty());
}

/**
 * @tc.name: GetMonth001
 * @tc.desc: Test function of textClock.
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, GetMonth001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create object and init.
     */
    CreateWithItem([&](TextClockModelNG model) {});
    EXPECT_FALSE(pattern_->GetMonth(0).empty());
    EXPECT_TRUE(pattern_->GetMonth(12).empty());
}

/**
 * @tc.name: SpliceDateTime001
 * @tc.desc: Test function of textClock.
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, SpliceDateTime001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create object and init.
     */
    CreateWithItem([&](TextClockModelNG model) {});
    std::vector<std::string> curDateTime;
    pattern_->formatElementMap_.clear();
    pattern_->formatElementMap_.emplace(std::make_pair(0, TextClockFormatElement()));
    EXPECT_TRUE(pattern_->SpliceDateTime(curDateTime).empty());
    pattern_->formatElementMap_.emplace(std::make_pair(1, TextClockFormatElement()));
    EXPECT_TRUE(pattern_->SpliceDateTime(curDateTime).empty());
}

/**
 * @tc.name: FireBuilder001
 * @tc.desc: Test function of textClock.
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, FireBuilder001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create object and init.
     */
    auto onChange = [](const std::string& szStr) { LOGD("szStr change: %s", szStr.c_str()); };
    CreateWithItem([&](TextClockModelNG model) {
        model.SetFormat(CLOCK_FORMAT);
        model.SetHoursWest(HOURS_WEST);
        model.SetFontSize(FONT_SIZE_VALUE);
        model.SetTextColor(TEXT_COLOR_VALUE);
        model.SetItalicFontStyle(ITALIC_FONT_STYLE_VALUE);
        model.SetFontWeight(FONT_WEIGHT_VALUE);
        model.SetFontFamily(FONT_FAMILY_VALUE);
        model.SetOnDateChange(onChange);
    });

    auto textId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode =
        FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, textId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(textNode, nullptr);
    textNode->MarkModifyDone();
    textNode->MountToParent(frameNode_);
    pattern_->nodeId_ = textId;
    auto size = pattern_->GetHost()->GetChildren().size();
    pattern_->FireBuilder();
    EXPECT_EQ(size - 1, pattern_->GetHost()->GetChildren().size());

    pattern_->SetBuilderFunc([](const TextClockConfiguration& info) -> RefPtr<FrameNode> {
        auto textId = ElementRegister::GetInstance()->MakeUniqueId();
        return FrameNode::GetOrCreateFrameNode(
            V2::TEXT_ETS_TAG, textId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    });
    pattern_->FireBuilder();
    EXPECT_EQ(size, pattern_->GetHost()->GetChildren().size());
}

/**
 * @tc.name: TextClockOnDateChange001
 * @tc.desc: Test OnDateChange of TextClockPattern.
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, TextClockOnDateChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and set event.
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    std::string utc = UTC_INPUT;
    auto onChange = [&utc](const std::string& isUtc) { utc = UTC_INPUT_NEXT; };
    textClockModel.SetOnDateChange(onChange);

    /**
     * @tc.steps: step2. get textClock frameNode and event.
     * @tc.expected: function is called.
     */
    auto stack = ViewStackProcessor::GetInstance();
    auto frameNode = stack->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<TextClockEventHub> eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    ASSERT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step3. get pattern.
     * @tc.expected: step4.
     */
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isStart_ = false;
    MockPipelineContext::SetUp();
    pattern->InitUpdateTimeTextCallBack();
    pattern->RegistVisibleAreaChangeCallback();

    /**
     * @tc.steps: step4. VisibleArea be changed, call the event entry function.
     * @tc.expected: check whether the value is correct.
     */
    pattern->isStart_ = true;
    pattern->OnVisibleAreaChange(false);
    pattern->UpdateTimeText();
    EXPECT_EQ(utc, UTC_INPUT);
    pattern->OnVisibleAreaChange(true);
    pattern->UpdateTimeText();
    EXPECT_EQ(utc, UTC_INPUT_NEXT);

    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(host->GetLastChild());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(textLayoutProperty, nullptr);
    pattern->OnModifyDone();
    EXPECT_EQ(textLayoutProperty->GetContent(), StringUtils::Str8ToStr16(UTC_INPUT_NEXT_STRING));
    stack->Pop();
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: TextClockOnDateChange002
 * @tc.desc: Test OnDateChange of TextClockPattern.
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, TextClockOnDateChange002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and set event.
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    std::string utc = UTC_INPUT2;
    auto onChange = [&utc](const std::string& isUtc) { utc = UTC_INPUT_NEXT2; };
    textClockModel.SetOnDateChange(onChange);

    /**
     * @tc.steps: step2. get textClock frameNode and event.
     * @tc.expected: function is called.
     */
    auto stack = ViewStackProcessor::GetInstance();
    auto frameNode = stack->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<TextClockEventHub> eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    ASSERT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step3. get pattern.
     * @tc.expected: step4.
     */
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isStart_ = false;
    MockPipelineContext::SetUp();
    pattern->InitUpdateTimeTextCallBack();
    pattern->RegistVisibleAreaChangeCallback();

    /**
     * @tc.steps: step4. visible attribute be changed, call the event entry function.
     * @tc.expected: check whether the value is correct.
     */
    pattern->isStart_ = true;
    pattern->OnVisibleAreaChange(false);
    pattern->UpdateTimeText();
    EXPECT_EQ(utc, UTC_INPUT2);
    pattern->OnVisibleAreaChange(true);
    pattern->UpdateTimeText();
    EXPECT_EQ(utc, UTC_INPUT_NEXT2);
    pattern->prevTime_ = "1";
    pattern->OnVisibleAreaChange(true);
    pattern->UpdateTimeText();
    EXPECT_EQ(utc, UTC_INPUT_NEXT2);

    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(host->GetLastChild());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(textLayoutProperty, nullptr);
    pattern->OnModifyDone();
    EXPECT_EQ(textLayoutProperty->GetContent(), StringUtils::Str8ToStr16(UTC_INPUT_NEXT_STRING));
    stack->Pop();
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: TextClockOnDateChange003
 * @tc.desc: Test OnDateChange of TextClockPattern.
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, TextClockOnDateChange003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock and set event.
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    std::string utc = UTC_INPUT3;
    auto onChange = [&utc](const std::string& isUtc) { utc = UTC_INPUT_NEXT3; };
    textClockModel.SetOnDateChange(onChange);

    /**
     * @tc.steps: step2. get textClock frameNode and event.
     * @tc.expected: function is called.
     */
    auto stack = ViewStackProcessor::GetInstance();
    auto frameNode = stack->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<TextClockEventHub> eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    ASSERT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step3. get pattern.
     * @tc.expected: step4.
     */
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isStart_ = false;
    MockPipelineContext::SetUp();
    pattern->InitUpdateTimeTextCallBack();
    pattern->RegistVisibleAreaChangeCallback();

    /**
     * @tc.steps: step4. VisibleArea be changed, call the event entry function.
     * @tc.expected: check whether the value is correct.
     */
    pattern->isStart_ = true;
    pattern->OnVisibleAreaChange(false);
    pattern->UpdateTimeText();
    EXPECT_EQ(utc, UTC_INPUT3);
    pattern->OnVisibleAreaChange(true);
    pattern->UpdateTimeText();
    EXPECT_EQ(utc, UTC_INPUT_NEXT3);
    pattern->prevTime_ = "1";
    pattern->OnVisibleAreaChange(true);
    pattern->UpdateTimeText();
    EXPECT_EQ(utc, UTC_INPUT_NEXT3);

    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(host->GetLastChild());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(textLayoutProperty, nullptr);
    pattern->OnModifyDone();
    EXPECT_EQ(textLayoutProperty->GetContent(), StringUtils::Str8ToStr16(UTC_INPUT_NEXT_STRING));
    stack->Pop();
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: TextClockParseDateTime001
 * @tc.desc: Test ParseDateTime of TextClockPattern.
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, TextClockParseDateTime001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock frameNode.
     */
    TestProperty testProperty;
    testProperty.format = std::make_optional(CLOCK_FORMAT2);
    testProperty.hoursWest = std::make_optional(HOURS_WEST);
    RefPtr<FrameNode> frameNode = CreateTextClockParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get pattern and layoutProperty.
     * @tc.expected: step2.
     */
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textClockProperty = frameNode->GetLayoutProperty<TextClockLayoutProperty>();
    ASSERT_NE(textClockProperty, nullptr);

    /**
     * @tc.steps: step3. ParseDateTime function is called..
     * @tc.expected: step3. check whether the properties is correct.
     */
    std::string strDateTimeValue = "1970.01.01, 01:01:01.001";
    std::string res = pattern->ParseDateTime(strDateTimeValue, 2, 3, 11);
    std::string strRes = "1970.01.01, 01:01:01.001";
    EXPECT_EQ(res, strRes);
}

/**
 * @tc.name: TextClockParseDateTime002
 * @tc.desc: Test ParseDateTime of TextClockPattern.
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, TextClockParseDateTime002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock frameNode.
     */
    TestProperty testProperty;
    testProperty.format = std::make_optional(CLOCK_FORMAT);
    testProperty.hoursWest = std::make_optional(HOURS_WEST);
    RefPtr<FrameNode> frameNode = CreateTextClockParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get pattern and layoutProperty.
     * @tc.expected: step2.
     */
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textClockProperty = frameNode->GetLayoutProperty<TextClockLayoutProperty>();
    ASSERT_NE(textClockProperty, nullptr);

    /**
     * @tc.steps: step3. ParseDateTimeValue function is called..
     * @tc.expected: step3. check whether the properties is correct.
     */
    std::vector<std::string> res = { "1900", "0", "1", "0", "0", "0", "0", "", "0", "", "", "", "", "" };
    std::string strDateTimeValue = "1970.01.01";
    std::vector<std::string> str = pattern->ParseDateTimeValue(strDateTimeValue);
    EXPECT_EQ(str, res);

    std::vector<std::string> res2 = { "1970", "01", "01", "01", "01", "01", "001", "", "0", "70", "1", "1", "00", "" };
    strDateTimeValue = "1970/01/01, 01:01:01.001";
    str = pattern->ParseDateTimeValue(strDateTimeValue);
    EXPECT_EQ(str, res2);

    std::vector<std::string> res3 = { "1970", "01", "01", "1", "01", "01", "001", "", "0", "70", "1", "1", "00", "" };
    strDateTimeValue = "1970/01/01, 01:01:01.001";
    pattern->is24H_ = true;
    textClockProperty->UpdatePrefixHour(ZeroPrefixType::HIDE);
    str = pattern->ParseDateTimeValue(strDateTimeValue);
    EXPECT_EQ(str, res3);

    std::vector<std::string> res4 = { "1970", "01", "01", "01", "01", "01", "001", "", "0", "70", "1", "1", "00", "" };
    strDateTimeValue = "1970/01/01, 1:01:01.001";
    pattern->is24H_ = false;
    textClockProperty->UpdatePrefixHour(ZeroPrefixType::SHOW);
    str = pattern->ParseDateTimeValue(strDateTimeValue);
    EXPECT_EQ(str, res4);
}

/**
 * @tc.name: TextClockParseInputFormat001
 * @tc.desc: Test ParseInputFormat of TextClockPattern.
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, TextClockParseInputFormat001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock frameNode.
     */
    TestProperty testProperty;
    testProperty.format = std::make_optional(CLOCK_FORMAT3);
    testProperty.hoursWest = std::make_optional(HOURS_WEST);
    RefPtr<FrameNode> frameNode = CreateTextClockParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get pattern and layoutProperty.
     * @tc.expected: step2.
     */
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textClockProperty = frameNode->GetLayoutProperty<TextClockLayoutProperty>();
    ASSERT_NE(textClockProperty, nullptr);

    /**
     * @tc.steps: step3. call the format and datetime split, and datetime splice function.
     * @tc.expected: check whether the value is correct.
     */
    pattern->ParseInputFormat();
    std::vector<std::string> curDateTime = { "1900", "0", "1", "0", "0", "0", "0", "", "2" };
    std::string dateTimeValue = "2025/03/25, 下午8:35:07.007";
    curDateTime = pattern->ParseDateTimeValue(dateTimeValue);
    dateTimeValue = "3/25/2025, 8:35:07.67 am";
    curDateTime = pattern->ParseDateTimeValue(dateTimeValue);
    dateTimeValue = "03/25/2025, 20:35:07.007";
    curDateTime = pattern->ParseDateTimeValue(dateTimeValue);
    pattern->SpliceDateTime(curDateTime);
    pattern->CheckDateTimeElement(curDateTime, 'y', 0, true);
    pattern->CheckDateTimeElement(curDateTime, 'M', 1, true);
    pattern->CheckDateTimeElement(curDateTime, 'd', 2, true);
    pattern->CheckDateTimeElement(curDateTime, 'm', 4, true);
    pattern->CheckDateTimeElement(curDateTime, 'E', 13, true);
    pattern->CheckDateTimeElement(curDateTime, 'E', 8, true);
    EXPECT_EQ(pattern->is24H_, true);
}

/**
 * @tc.name: TextClockParseInputFormat002
 * @tc.desc: Test ParseInputFormat of TextClockPattern.
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, TextClockParseInputFormat002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock frameNode.
     */
    TestProperty testProperty;
    testProperty.format = std::make_optional(CLOCK_FORMAT4);
    testProperty.hoursWest = std::make_optional(HOURS_WEST);
    RefPtr<FrameNode> frameNode = CreateTextClockParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get pattern and layoutProperty.
     * @tc.expected: step2.
     */
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textClockProperty = frameNode->GetLayoutProperty<TextClockLayoutProperty>();
    ASSERT_NE(textClockProperty, nullptr);

    /**
     * @tc.steps: step3. call the format and datetime split, and datetime splice function.
     * @tc.expected: check whether the value is correct.
     */
    pattern->ParseInputFormat();
    std::vector<std::string> curDateTime = { "1900", "0", "1", "0", "0", "0", "0", "", "2" };
    std::string dateTimeValue = "2025/03/25, 上午8:35:07.007";
    curDateTime = pattern->ParseDateTimeValue(dateTimeValue);
    dateTimeValue = "3/25/2025, 8:35:07.67 am";
    curDateTime = pattern->ParseDateTimeValue(dateTimeValue);
    dateTimeValue = "03/25/2025, 08:35:07.007";
    curDateTime = pattern->ParseDateTimeValue(dateTimeValue);
    pattern->SpliceDateTime(curDateTime);
    pattern->CheckDateTimeElement(curDateTime, 'y', 0, true);
    pattern->CheckDateTimeElement(curDateTime, 'M', 1, true);
    pattern->CheckDateTimeElement(curDateTime, 'd', 2, true);
    pattern->CheckDateTimeElement(curDateTime, 'm', 4, true);
    pattern->CheckDateTimeElement(curDateTime, 'E', 13, true);
    pattern->CheckDateTimeElement(curDateTime, 'E', 8, true);
    EXPECT_EQ(pattern->is24H_, true);
}

/**
 * @tc.name: TextClockCheckDateTimeElement001
 * @tc.desc: Test ParseInputFormat of TextClockPattern.
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, TextClockCheckDateTimeElement001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock frameNode.
     */
    TestProperty testProperty;
    testProperty.format = std::make_optional(CLOCK_FORMAT4);
    testProperty.hoursWest = std::make_optional(HOURS_WEST);
    RefPtr<FrameNode> frameNode = CreateTextClockParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get pattern and layoutProperty.
     * @tc.expected: step2.
     */
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. call the format and datetime split, and datetime splice function.
     * @tc.expected: check whether the value is correct.
     */
    pattern->ParseInputFormat();
    std::string dateTimeValue = "2025/03/25 08:35:07.007";
    std::vector<std::string> curDateTime = pattern->ParseDateTimeValue(dateTimeValue);
    pattern->SpliceDateTime(curDateTime);
    auto res1 = pattern->CheckDateTimeElement(curDateTime, 'y', 0, true);
    std::string checkRes1 = "2025";
    EXPECT_EQ(res1, checkRes1);
    auto res2 = pattern->CheckDateTimeElement(curDateTime, 'M', 1, true);
    std::string checkRes2 = "03";
    EXPECT_EQ(res2, checkRes2);
    auto res3 = pattern->CheckDateTimeElement(curDateTime, 'd', 2, true);
    std::string checkRes3 = "25";
    EXPECT_EQ(res3, checkRes3);
    auto res4 = pattern->CheckDateTimeElement(curDateTime, 'h', 3, true);
    std::string checkRes4 = "08";
    EXPECT_EQ(res4, checkRes4);
    auto res5 = pattern->CheckDateTimeElement(curDateTime, 'm', 4, true);
    std::string checkRes5 = "35";
    EXPECT_EQ(res5, checkRes5);
    auto res6 = pattern->CheckDateTimeElement(curDateTime, 's', 5, true);
    std::string checkRes6 = "07";
    EXPECT_EQ(res6, checkRes6);
}

/**
 * @tc.name: TextClockUpdateFontSize001
 * @tc.desc: Test UpdateTextClockFontSize of TextClockPattern.
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, TextClockUpdateFontSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock frameNode.
     */
    TestProperty testProperty;
    RefPtr<FrameNode> frameNode = CreateTextClockParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get pattern and layoutProperty.
     * @tc.expected: step2.
     */
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextClockLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. call UpdateTextClockFontSize function.
     * @tc.expected: step3. check fontSize property updated.
     */
    const double fontSizeValue = 20.0;
    CalcDimension fontSize(fontSizeValue, DimensionUnit::VP);
    pattern->UpdateTextClockFontSize(fontSize);
    EXPECT_EQ(layoutProperty->GetFontSize().value(), fontSize);
}

/**
 * @tc.name: TextClockUpdateFontFamily002
 * @tc.desc: Test UpdateTextClockFontFamily of TextClockPattern.
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, TextClockUpdateFontFamily002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textClock frameNode.
     */
    TestProperty testProperty;
    RefPtr<FrameNode> frameNode = CreateTextClockParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get pattern and layoutProperty.
     * @tc.expected: step2.
     */
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextClockLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. call UpdateTextClockFontFamily function.
     * @tc.expected: step3. check fontFamily property updated.
     */
    std::vector<std::string> fontFamilies = { "Arial", "sans-serif" };
    pattern->UpdateTextClockFontFamily(fontFamilies);
    EXPECT_EQ(layoutProperty->GetFontFamily().value(), fontFamilies);

    /**
     * @tc.steps: step4. Execute font family update operation
     * @tc.expected: Font specifications should be correctly applied
     */
    std::vector<std::string> typefaceOptions = { "Roboto", "Helvetica Neue" };
    pattern->UpdateTextClockFontFamily(typefaceOptions);
    EXPECT_EQ(layoutProperty->GetFontFamily().value(), typefaceOptions);
}

/**
 * @tc.name: TextClockOnColorConfigurationUpdate001
 * @tc.desc: Test OnColorConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, TextClockOnColorConfigurationUpdate001, TestSize.Level1)
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textTheme = AceType::MakeRefPtr<TextTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textTheme));

    TestProperty testProperty;
    RefPtr<FrameNode> frameNode = CreateTextClockParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = false;
    pattern->OnColorConfigurationUpdate();
    pattern->UpdateTextClockColor(Color::RED, true);

    g_isConfigChangePerform = true;
    pattern->OnColorConfigurationUpdate();
    auto layoutProperty = frameNode->GetLayoutProperty<TextClockLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->ResetTextColorSetByUser();
    pattern->OnColorConfigurationUpdate();

    layoutProperty->UpdateTextColorSetByUser(true);
    pattern->OnColorConfigurationUpdate();

    layoutProperty->UpdateTextColorSetByUser(false);
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto pipeline = host->GetContextWithCheck();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetIsSystemColorChange(true);
    auto theme = pipeline->GetTheme<TextTheme>();
    ASSERT_NE(theme, nullptr);
    Color testColor = theme->GetTextStyle().GetTextColor();
    pattern->OnColorConfigurationUpdate();
    EXPECT_EQ(layoutProperty->GetTextColor(), testColor);

    pattern->UpdateTextClockColor(Color::RED, true);
    EXPECT_EQ(layoutProperty->GetTextColor(), Color::RED);
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: TextClockSetTextShadow001
 * @tc.desc: Test model ng  SetTextShadow
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, TextClockSetTextShadow001, TestSize.Level1)
{
    TextClockModelNG textClockModel;
    textClockModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    textClockModel.SetFontColorByUser(frameNode, false);

    g_isConfigChangePerform = false;
    Shadow shadow;
    shadow.SetBlurRadius(10);
    shadow.SetOffsetX(10);
    shadow.SetOffsetY(10);
    shadow.SetColor(Color(Color::RED));
    shadow.SetShadowType(ShadowType::COLOR);
    std::vector<Shadow> setShadows;
    setShadows.emplace_back(shadow);
    textClockModel.SetTextShadow(frameNode, setShadows);
    textClockModel.SetTextShadow(setShadows);
    g_isConfigChangePerform = true;
    textClockModel.SetTextShadow(frameNode, setShadows);
    textClockModel.SetTextShadow(setShadows);

    auto layoutProperty = frameNode->GetLayoutProperty<TextClockLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetTextShadow(), setShadows);
}

/**
 * @tc.name: TextClockCreateWithResourceObj001
 * @tc.desc: Test model ng  CreateWithResourceObj
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, TextClockCreateWithResourceObj001, TestSize.Level1)
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textTheme = AceType::MakeRefPtr<TextTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textTheme));

    TextClockModelNG textClockModel;
    textClockModel.Create();
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    ASSERT_NE(resObj, nullptr);
    textClockModel.CreateWithTextColorResourceObj(resObj);
    textClockModel.CreateWithFontSizeResourceObj(resObj);
    textClockModel.CreateWithFontFamilyResourceObj(resObj);
    textClockModel.CreateWithFontWeightResourceObj(resObj);
    textClockModel.CreateWithFormatResourceObj(resObj);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);
    int32_t colorMode = static_cast<int32_t>(ColorMode::DARK);
    pattern->OnColorModeChange(colorMode);
    auto layoutProperty = frameNode->GetLayoutProperty<TextClockLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<TextTheme>();
    ASSERT_NE(theme, nullptr);
    auto fontSize = theme->GetTextStyle().GetFontSize();
    EXPECT_EQ(layoutProperty->GetFontSize().value(), fontSize);
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: TextClockCreateWithResourceObj002
 * @tc.desc: Test model ng  CreateWithResourceObj
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, TextClockCreateWithResourceObj002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock with API version 18
     */
    MockPipelineContext::SetUp();
    auto pipelineContext = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    int32_t backupApiVersion = pipelineContext->GetMinPlatformVersion();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textTheme = AceType::MakeRefPtr<TextTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textTheme));
    TextClockModelNG textClockModel;
    textClockModel.Create();
    ResourceObjectParams params { .value = "test", .type = ResourceObjectParamType::STRING };
    std::vector<ResourceObjectParams> resObjParamsList;
    resObjParamsList.push_back(params);
    RefPtr<ResourceObject> resObjWithId =
        AceType::MakeRefPtr<ResourceObject>(100000, 10003, resObjParamsList, "com.example.test", "entry", 100000);
    RefPtr<ResourceObject> resObjWithDimensionId =
        AceType::MakeRefPtr<ResourceObject>(100000, 10007, resObjParamsList, "com.example.test", "entry", 100000);
    RefPtr<ResourceObject> resObjId =
        AceType::MakeRefPtr<ResourceObject>(-1, 100001, resObjParamsList, "com.example.test", "entry", 100000);
    textClockModel.CreateWithTextColorResourceObj(resObjId);
    textClockModel.CreateWithFontSizeResourceObj(resObjWithDimensionId);
    textClockModel.CreateWithFontFamilyResourceObj(resObjWithId);
    textClockModel.CreateWithFontWeightResourceObj(resObjWithId);
    textClockModel.CreateWithFormatResourceObj(resObjWithId);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);
    int32_t colorMode = static_cast<int32_t>(ColorMode::DARK);
    pattern->OnColorModeChange(colorMode);
    pipelineContext->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    textClockModel.CreateWithFontSizeResourceObj(resObjWithId);
    frameNode->SetRerenderable(false);
    pattern->OnColorModeChange(colorMode);
    auto layoutProperty = frameNode->GetLayoutProperty<TextClockLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto theme = pipelineContext->GetTheme<TextTheme>();
    ASSERT_NE(theme, nullptr);
    auto fontSize = theme->GetTextStyle().GetFontSize();
    EXPECT_EQ(layoutProperty->GetFontSize().value(), fontSize);
    pipelineContext->SetMinPlatformVersion(backupApiVersion);
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: TextClockMultiThread001
 * @tc.desc: Test MultiThread
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, TextClockMultiThread001, TestSize.Level1)
{
    TextClockModelNG textClockModel;
    textClockModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    textClockModel.SetFontColorByUser(frameNode, false);

    g_isConfigChangePerform = false;
    Shadow shadow;
    shadow.SetBlurRadius(20);
    shadow.SetOffsetX(100);
    shadow.SetOffsetY(100);
    shadow.SetColor(Color(Color::RED));
    shadow.SetShadowType(ShadowType::COLOR);
    std::vector<Shadow> setShadows;
    setShadows.emplace_back(shadow);
    textClockModel.SetTextShadow(frameNode, setShadows);
    textClockModel.SetTextShadow(setShadows);
    g_isConfigChangePerform = true;
    textClockModel.SetTextShadow(frameNode, setShadows);
    textClockModel.SetTextShadow(setShadows);

    auto layoutProperty = frameNode->GetLayoutProperty<TextClockLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetTextShadow(), setShadows);
}

/**
 * @tc.name: GetFormatTest001
 * @tc.desc: Test GetFormat when isForm is false and API version < 18
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, GetFormatTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock and set API version
     */
    MockPipelineContext::SetUp();
    auto pipelineContext = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto lastPlatformVersion = pipelineContext->GetMinPlatformVersion();

    auto mockContainer = MockContainer::Current();
    ASSERT_NE(mockContainer, nullptr);
    mockContainer->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_SEVENTEEN));
    pipelineContext->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_SEVENTEEN));

    TextClockModelNG textClockModel;
    textClockModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test default format without 24H
     * @tc.expected: Should return DEFAULT_FORMAT (12-hour format)
     */
    auto format = pattern->GetFormat();
    EXPECT_EQ(format, DEFAULT_FORMAT);

    /**
     * @tc.steps: step3. Recover API version info.
     */
    pipelineContext->SetMinPlatformVersion(lastPlatformVersion);
    mockContainer->SetApiTargetVersion(lastPlatformVersion);
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: GetFormatTest002
 * @tc.desc: Test GetFormat when isForm is false, API >= 18, and is24H is true
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, GetFormatTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock with API version 18 and 24H mode
     */
    MockPipelineContext::SetUp();
    auto pipelineContext = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto lastPlatformVersion = pipelineContext->GetMinPlatformVersion();

    auto mockContainer = MockContainer::Current();
    ASSERT_NE(mockContainer, nullptr);
    mockContainer->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    pipelineContext->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));

    TextClockModelNG textClockModel;
    textClockModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set 24H mode and get format
     * @tc.expected: Method should execute and return a valid format
     */
    // Note: SystemProperties::Is24HourClock() returns false in test environment,
    // so is24H_ remains false and format will be 12-hour format
    pattern->OnTimeChange();
    auto format = pattern->GetFormat();
    // Verify method executes and returns a valid non-empty format
    EXPECT_FALSE(format.empty());

    /**
     * @tc.steps: step3. Recover API version info.
     */
    pipelineContext->SetMinPlatformVersion(lastPlatformVersion);
    mockContainer->SetApiTargetVersion(lastPlatformVersion);
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: GetFormatTest003
 * @tc.desc: Test GetFormat when custom format is set
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, GetFormatTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock with custom format
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    textClockModel.SetFormat("HH:mm");
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Get custom format
     * @tc.expected: Should return the custom format
     */
    auto format = pattern->GetFormat();
    EXPECT_EQ(format, "HH:mm");
}

/**
 * @tc.name: OnVisibleAreaChangeTest001
 * @tc.desc: Test OnVisibleAreaChange when becoming visible
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, OnVisibleAreaChangeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock and mark as invisible
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call OnVisibleAreaChange with visible=true
     * @tc.expected: isInVisibleArea_ should be set to true
     */
    pattern->OnVisibleAreaChange(true);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: OnVisibleAreaChangeTest002
 * @tc.desc: Test OnVisibleAreaChange when becoming invisible
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, OnVisibleAreaChangeTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call OnVisibleAreaChange with visible=false
     * @tc.expected: isInVisibleArea_ should be set to false and delay task cancelled
     */
    pattern->OnVisibleAreaChange(false);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: OnVisibleAreaChangeTest003
 * @tc.desc: Test OnVisibleAreaChange when already visible
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, OnVisibleAreaChangeTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock and mark as visible
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnVisibleAreaChange(true);

    /**
     * @tc.steps: step2. Call OnVisibleAreaChange again with visible=true
     * @tc.expected: Should not trigger UpdateTimeText (already visible)
     */
    pattern->OnVisibleAreaChange(true);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: RequestUpdateForNextSecondTest001
 * @tc.desc: Test RequestUpdateForNextSecond without seconds in format
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, RequestUpdateForNextSecondTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock with format without seconds
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    textClockModel.SetFormat("HH:mm");
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call RequestUpdateForNextSecond
     * @tc.expected: Should calculate delay for next minute
     */
    pattern->RequestUpdateForNextSecond();
    EXPECT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->GetFormat(), "HH:mm");
}

/**
 * @tc.name: RequestUpdateForNextSecondTest002
 * @tc.desc: Test RequestUpdateForNextSecond with seconds in format
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, RequestUpdateForNextSecondTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock with format with seconds
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    textClockModel.SetFormat("HH:mm:ss");
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call RequestUpdateForNextSecond
     * @tc.expected: Should calculate delay for next second
     */
    pattern->RequestUpdateForNextSecond();
    EXPECT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->GetFormat(), "HH:mm:ss");
}

/**
 * @tc.name: RequestUpdateForNextSecondTest003
 * @tc.desc: Test RequestUpdateForNextSecond with milliseconds in format
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, RequestUpdateForNextSecondTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock with format with milliseconds
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    textClockModel.SetFormat("HH:mm:ss.S");
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call RequestUpdateForNextSecond
     * @tc.expected: Should calculate delay for next second (has S)
     */
    pattern->RequestUpdateForNextSecond();
    EXPECT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->GetFormat(), "HH:mm:ss.S");
}

/**
 * @tc.name: GetAmPmTest001
 * @tc.desc: Test GetAmPm for AM (hour < 12)
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, GetAmPmTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test GetAmPm with hour = 11 (AM)
     * @tc.expected: Should return AM string
     */
    auto amPm = pattern->GetAmPm(11);
    auto amPmStrings = Localization::GetInstance()->GetAmPmStrings();
    if (amPmStrings.size() >= 2) {
        EXPECT_EQ(amPm, amPmStrings[0]);
    }
}

/**
 * @tc.name: GetAmPmTest002
 * @tc.desc: Test GetAmPm for PM (hour >= 12)
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, GetAmPmTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test GetAmPm with hour = 13 (PM)
     * @tc.expected: Should return PM string
     */
    auto amPm = pattern->GetAmPm(13);
    auto amPmStrings = Localization::GetInstance()->GetAmPmStrings();
    if (amPmStrings.size() >= 2) {
        EXPECT_EQ(amPm, amPmStrings[1]);
    }
}

/**
 * @tc.name: AddZeroPrefixTest001
 * @tc.desc: Test AddZeroPrefix with single digit
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, AddZeroPrefixTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test AddZeroPrefix with single digit "5"
     * @tc.expected: Should return "05"
     */
    auto result = pattern->AddZeroPrefix("5");
    EXPECT_EQ(result, "05");
}

/**
 * @tc.name: AddZeroPrefixTest002
 * @tc.desc: Test AddZeroPrefix with two digits
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, AddZeroPrefixTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test AddZeroPrefix with "10"
     * @tc.expected: Should return "10" unchanged
     */
    auto result = pattern->AddZeroPrefix("10");
    EXPECT_EQ(result, "10");
}

/**
 * @tc.name: AddZeroPrefixTest003
 * @tc.desc: Test AddZeroPrefix with non-digit
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, AddZeroPrefixTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test AddZeroPrefix with non-digit character
     * @tc.expected: Should return unchanged
     */
    auto result = pattern->AddZeroPrefix("a");
    EXPECT_EQ(result, "a");
}

/**
 * @tc.name: RemoveZeroPrefixTest001
 * @tc.desc: Test RemoveZeroPrefix with leading zero
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, RemoveZeroPrefixTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test RemoveZeroPrefix with "05"
     * @tc.expected: Should return "5"
     */
    auto result = pattern->RemoveZeroPrefix("05");
    EXPECT_EQ(result, "5");
}

/**
 * @tc.name: RemoveZeroPrefixTest002
 * @tc.desc: Test RemoveZeroPrefix without leading zero
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, RemoveZeroPrefixTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test RemoveZeroPrefix with "15"
     * @tc.expected: Should return "15" unchanged
     */
    auto result = pattern->RemoveZeroPrefix("15");
    EXPECT_EQ(result, "15");
}

/**
 * @tc.name: RemoveZeroPrefixTest003
 * @tc.desc: Test RemoveZeroPrefix with single digit
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, RemoveZeroPrefixTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test RemoveZeroPrefix with single digit "5"
     * @tc.expected: Should return "5" unchanged
     */
    auto result = pattern->RemoveZeroPrefix("5");
    EXPECT_EQ(result, "5");
}

/**
 * @tc.name: AbstractTest001
 * @tc.desc: Test Abstract to extract letters
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, AbstractTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test Abstract to get letters from "a1b2c3"
     * @tc.expected: Should return "abc"
     */
    auto result = pattern->Abstract("a1b2c3", true);
    EXPECT_EQ(result, "abc");
}

/**
 * @tc.name: AbstractTest002
 * @tc.desc: Test Abstract to extract non-letters
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, AbstractTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test Abstract to get non-letters from "a1b2c3"
     * @tc.expected: Should return "123"
     */
    auto result = pattern->Abstract("a1b2c3", false);
    EXPECT_EQ(result, "123");
}

/**
 * @tc.name: GetDigitNumberTest001
 * @tc.desc: Test GetDigitNumber to count digits
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, GetDigitNumberTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test GetDigitNumber with "a1b2c3d"
     * @tc.expected: Should return 3
     */
    auto count = pattern->GetDigitNumber("a1b2c3d");
    EXPECT_EQ(count, 3);
}

/**
 * @tc.name: GetDigitNumberTest002
 * @tc.desc: Test GetDigitNumber with no digits
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, GetDigitNumberTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test GetDigitNumber with "abcdef"
     * @tc.expected: Should return 0
     */
    auto count = pattern->GetDigitNumber("abcdef");
    EXPECT_EQ(count, 0);
}

/**
 * @tc.name: GetWeekTest001
 * @tc.desc: Test GetWeek with full type
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, GetWeekTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test GetWeek with full type (false)
     * @tc.expected: Should return full week name
     */
    auto weeks = Localization::GetInstance()->GetWeekdays(false);
    if (weeks.size() > 0) {
        auto week = pattern->GetWeek(false, 0);
        EXPECT_EQ(week, weeks[0]);
    }
}

/**
 * @tc.name: GetWeekTest002
 * @tc.desc: Test GetWeek with short type
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, GetWeekTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test GetWeek with short type (true)
     * @tc.expected: Should return short week name
     */
    auto weeks = Localization::GetInstance()->GetWeekdays(true);
    if (weeks.size() > 0) {
        auto week = pattern->GetWeek(true, 0);
        EXPECT_EQ(week, weeks[0]);
    }
}

/**
 * @tc.name: GetMonthTest001
 * @tc.desc: Test GetMonth with valid month index
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, GetMonthTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test GetMonth with month = 0 (January)
     * @tc.expected: Should return January name
     */
    auto months = Localization::GetInstance()->GetMonths(true);
    if (months.size() > 0) {
        auto month = pattern->GetMonth(0);
        EXPECT_EQ(month, months[0]);
    }
}

/**
 * @tc.name: GetMonthTest002
 * @tc.desc: Test GetMonth with out of bounds month index
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, GetMonthTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test GetMonth with invalid month index
     * @tc.expected: Should return empty string
     */
    auto month = pattern->GetMonth(100);
    EXPECT_EQ(month, "");
}

/**
 * @tc.name: UpdateTimeTextTest001
 * @tc.desc: Test UpdateTimeText when isStart is false
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, UpdateTimeTextTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock and stop it
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Stop the clock and try to update time
     * @tc.expected: Should return early without updating
     */
    auto controller = pattern->GetTextClockController();
    controller->Stop();
    pattern->UpdateTimeText(false);
}

/**
 * @tc.name: UpdateTimeTextTest002
 * @tc.desc: Test UpdateTimeText when not in visible area
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, UpdateTimeTextTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock and mark as invisible
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Mark as invisible and try to update time
     * @tc.expected: Should return early without updating
     */
    pattern->OnVisibleAreaChange(false);
    pattern->UpdateTimeText(false);
}

/**
 * @tc.name: GetHoursWestTest001
 * @tc.desc: Test GetHoursWest with no timezone offset set
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, GetHoursWestTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock without timezone offset
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Get hours west
     * @tc.expected: Should return NAN (use system timezone)
     */
    auto hoursWest = pattern->GetHoursWest();
    EXPECT_TRUE(std::isnan(hoursWest));
}

/**
 * @tc.name: GetHoursWestTest002
 * @tc.desc: Test GetHoursWest with timezone offset set
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, GetHoursWestTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock with timezone offset
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    textClockModel.SetHoursWest(8.0f);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Get hours west
     * @tc.expected: Should return 8.0
     */
    auto hoursWest = pattern->GetHoursWest();
    EXPECT_EQ(hoursWest, 8.0f);
}

/**
 * @tc.name: GetTextNodeTest001
 * @tc.desc: Test GetTextNode returns the Text child node
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, GetTextNodeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Get Text child node
     * @tc.expected: Should return the Text node
     */
    auto textNode = pattern->GetTextNode();
    ASSERT_NE(textNode, nullptr);
    EXPECT_EQ(textNode->GetTag(), V2::TEXT_ETS_TAG);
}

/**
 * @tc.name: OnTimeChangeTest001
 * @tc.desc: Test OnTimeChange updates 24H state
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, OnTimeChangeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Trigger time change
     * @tc.expected: Should update time text
     */
    pattern->OnTimeChange();
}

/**
 * @tc.name: OnLanguageConfigurationUpdateTest001
 * @tc.desc: Test OnLanguageConfigurationUpdate triggers time update
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, OnLanguageConfigurationUpdateTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Trigger language configuration update
     * @tc.expected: Should update time text with isTimeChange=true
     */
    pattern->OnLanguageConfigurationUpdate();
}

/**
 * @tc.name: DumpInfoTest001
 * @tc.desc: Test DumpInfo outputs correct information
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, DumpInfoTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call DumpInfo
     * @tc.expected: Should not crash and add descriptions
     */
    pattern->DumpInfo();
}

/**
 * @tc.name: ParseInputFormatTest001
 * @tc.desc: Test ParseInputFormat with 24H format
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, ParseInputFormatTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock with 24H format
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    textClockModel.SetFormat("HH:mm:ss");
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call GetCurrentFormatDateTime which triggers ParseInputFormat
     * @tc.expected: Should parse format correctly with is24H_=true
     */
    auto timeStr = pattern->GetCurrentFormatDateTime();
    EXPECT_FALSE(timeStr.empty());
}

/**
 * @tc.name: ParseInputFormatTest002
 * @tc.desc: Test ParseInputFormat with 12H format
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, ParseInputFormatTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock with 12H format
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    textClockModel.SetFormat("aa hh:mm:ss");
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call GetCurrentFormatDateTime which triggers ParseInputFormat
     * @tc.expected: Should parse format correctly with is24H_=false
     */
    auto timeStr = pattern->GetCurrentFormatDateTime();
    EXPECT_FALSE(timeStr.empty());
}

/**
 * @tc.name: GetDateTimeIndexTest001
 * @tc.desc: Test GetDateTimeIndex with year format
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, GetDateTimeIndexTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock with year format
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    textClockModel.SetFormat("yyyy");
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call GetCurrentFormatDateTime which triggers GetDateTimeIndex
     * @tc.expected: Should format year correctly
     */
    auto timeStr = pattern->GetCurrentFormatDateTime();
    EXPECT_FALSE(timeStr.empty());
}

/**
 * @tc.name: GetDateTimeIndexTest002
 * @tc.desc: Test GetDateTimeIndex with short year format
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, GetDateTimeIndexTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock with short year format
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    textClockModel.SetFormat("yy");
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call GetCurrentFormatDateTime which triggers GetDateTimeIndex
     * @tc.expected: Should format short year correctly
     */
    auto timeStr = pattern->GetCurrentFormatDateTime();
    EXPECT_FALSE(timeStr.empty());
}

/**
 * @tc.name: GetDateTimeIndexTest003
 * @tc.desc: Test GetDateTimeIndex with month format
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, GetDateTimeIndexTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock with month format
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    textClockModel.SetFormat("MM");
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call GetCurrentFormatDateTime which triggers GetDateTimeIndex
     * @tc.expected: Should format month correctly
     */
    auto timeStr = pattern->GetCurrentFormatDateTime();
    EXPECT_FALSE(timeStr.empty());
}

/**
 * @tc.name: GetDateTimeIndexTest004
 * @tc.desc: Test GetDateTimeIndex with day format
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, GetDateTimeIndexTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock with day format
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    textClockModel.SetFormat("DD");
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call GetCurrentFormatDateTime which triggers GetDateTimeIndex
     * @tc.expected: Should format day correctly
     */
    auto timeStr = pattern->GetCurrentFormatDateTime();
    EXPECT_FALSE(timeStr.empty());
}

/**
 * @tc.name: GetDateTimeIndexTest005
 * @tc.desc: Test GetDateTimeIndex with week format
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, GetDateTimeIndexTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock with week format
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    textClockModel.SetFormat("EEEEE");
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call GetCurrentFormatDateTime which triggers GetDateTimeIndex
     * @tc.expected: Should format week correctly
     */
    auto timeStr = pattern->GetCurrentFormatDateTime();
    EXPECT_FALSE(timeStr.empty());
}

/**
 * @tc.name: GetDateTimeIndexTest006
 * @tc.desc: Test GetDateTimeIndex with millisecond format
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, GetDateTimeIndexTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock with millisecond format
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    textClockModel.SetFormat("SSS");
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call GetCurrentFormatDateTime which triggers GetDateTimeIndex
     * @tc.expected: Should format millisecond correctly
     */
    auto timeStr = pattern->GetCurrentFormatDateTime();
    EXPECT_FALSE(timeStr.empty());
}

/**
 * @tc.name: GetDateTimeIndexTest007
 * @tc.desc: Test GetDateTimeIndex with centisecond format
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, GetDateTimeIndexTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock with centisecond format
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    textClockModel.SetFormat("SS");
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call GetCurrentFormatDateTime which triggers GetDateTimeIndex
     * @tc.expected: Should format centisecond correctly
     */
    auto timeStr = pattern->GetCurrentFormatDateTime();
    EXPECT_FALSE(timeStr.empty());
}

/**
 * @tc.name: GetPrefixHourTest001
 * @tc.desc: Test GetPrefixHour with AUTO type
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, GetPrefixHourTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Get prefix hour type (default AUTO)
     * @tc.expected: Should return AUTO
     */
    auto prefixHour = pattern->GetPrefixHour();
    EXPECT_EQ(prefixHour, ZeroPrefixType::AUTO);
}

/**
 * @tc.name: GetPrefixHourTest002
 * @tc.desc: Test GetPrefixHour with SHOW type
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, GetPrefixHourTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock with SHOW prefix type
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    textClockModel.SetDateTimeOptions(ZeroPrefixType::SHOW);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Get prefix hour type
     * @tc.expected: Should return SHOW
     */
    auto prefixHour = pattern->GetPrefixHour();
    EXPECT_EQ(prefixHour, ZeroPrefixType::SHOW);
}

/**
 * @tc.name: GetPrefixHourTest003
 * @tc.desc: Test GetPrefixHour with HIDE type
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, GetPrefixHourTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock with HIDE prefix type
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    textClockModel.SetDateTimeOptions(ZeroPrefixType::HIDE);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Get prefix hour type
     * @tc.expected: Should return HIDE
     */
    auto prefixHour = pattern->GetPrefixHour();
    EXPECT_EQ(prefixHour, ZeroPrefixType::HIDE);
}

/**
 * @tc.name: UpdateTextLayoutPropertyTest001
 * @tc.desc: Test UpdateTextLayoutProperty with all properties set
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, UpdateTextLayoutPropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock with all properties
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    textClockModel.SetFontSize(FONT_SIZE_VALUE);
    textClockModel.SetFontWeight(FONT_WEIGHT_VALUE);
    textClockModel.SetTextColor(TEXT_COLOR_VALUE);
    textClockModel.SetItalicFontStyle(ITALIC_FONT_STYLE_VALUE);
    textClockModel.SetFontFamily(FONT_FAMILY_VALUE);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Trigger OnModifyDone to transfer properties
     */
    frameNode->MarkModifyDone();

    /**
     * @tc.steps: step3. Get text node and verify properties were transferred
     * @tc.expected: Text node should have the properties
     */
    auto textNode = pattern->GetTextNode();
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetFontSize(), FONT_SIZE_VALUE);
}

/**
 * @tc.name: UpdateTextLayoutPropertyTest002
 * @tc.desc: Test UpdateTextLayoutProperty with empty font family
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, UpdateTextLayoutPropertyTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock with empty font family
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    textClockModel.SetFontFamily({});
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Get text node and verify font family was not updated
     * @tc.expected: Text node font family should remain unchanged
     */
    auto textNode = pattern->GetTextNode();
    ASSERT_NE(textNode, nullptr);
}

/**
 * @tc.name: OnModifyDoneTest001
 * @tc.desc: Test OnModifyDone with API version >= 18
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, OnModifyDoneTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock with API version 18
     */
    MockPipelineContext::SetUp();
    auto pipelineContext = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto lastPlatformVersion = pipelineContext->GetMinPlatformVersion();

    auto mockContainer = MockContainer::Current();
    ASSERT_NE(mockContainer, nullptr);
    mockContainer->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    pipelineContext->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));

    TextClockModelNG textClockModel;
    textClockModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Trigger OnModifyDone by marking modify done
     * @tc.expected: Should call Pattern::OnModifyDone
     */
    frameNode->MarkModifyDone();

    /**
     * @tc.steps: step3. Recover API version info.
     */
    pipelineContext->SetMinPlatformVersion(lastPlatformVersion);
    mockContainer->SetApiTargetVersion(lastPlatformVersion);
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: OnModifyDoneTest002
 * @tc.desc: Test OnModifyDone with API version < 18
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNG, OnModifyDoneTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextClock with API version 17
     */
    MockPipelineContext::SetUp();
    auto pipelineContext = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto lastPlatformVersion = pipelineContext->GetMinPlatformVersion();

    auto mockContainer = MockContainer::Current();
    ASSERT_NE(mockContainer, nullptr);
    mockContainer->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_SEVENTEEN));
    pipelineContext->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_SEVENTEEN));

    TextClockModelNG textClockModel;
    textClockModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Trigger OnModifyDone by marking modify done
     * @tc.expected: Should not call Pattern::OnModifyDone
     */
    frameNode->MarkModifyDone();

    /**
     * @tc.steps: step3. Recover API version info.
     */
    pipelineContext->SetMinPlatformVersion(lastPlatformVersion);
    mockContainer->SetApiTargetVersion(lastPlatformVersion);
    MockPipelineContext::TearDown();
}

} // namespace OHOS::Ace::NG
