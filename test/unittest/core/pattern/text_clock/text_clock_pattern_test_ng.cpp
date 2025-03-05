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
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pattern/mock_nestable_scroll_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "base/i18n/time_format.h"
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
inline const std::string CLOCK_FORMAT = "aa h:m:s";
inline const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
const Color TEXT_COLOR_VALUE = Color::FromRGB(255, 100, 100);
const Dimension FONT_SIZE_VALUE = Dimension(20.1, DimensionUnit::PX);
const Ace::FontStyle ITALIC_FONT_STYLE_VALUE = Ace::FontStyle::ITALIC;
const Ace::FontWeight FONT_WEIGHT_VALUE = Ace::FontWeight::W100;
} // namespace

class TextClockPatternTestNG : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
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
} // namespace OHOS::Ace::NG