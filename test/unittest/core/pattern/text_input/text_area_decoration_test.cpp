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

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr double ICON_SIZE = 24;
constexpr double ICON_HOT_ZONE_SIZE = 40;
constexpr double FONT_SIZE = 16;
constexpr int32_t DEFAULT_NODE_ID = 1;
constexpr int32_t MIN_PLATFORM_VERSION = 10;
const std::string DEFAULT_TEXT = "abcdefghijklmnopqrstuvwxyz";
struct ExpectParagraphParams {
    float height = 50.f;
    float longestLine = 460.f;
    float maxWidth = 460.f;
    size_t lineCount = 1;
    bool firstCalc = true;
    bool secondCalc = true;
};
} // namespace

class TextAreaDecorationBase : public TestNG {
protected:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void TearDown() override;

    void CreateTextField(const std::string& text = "", const std::string& placeHolder = "",
        const std::function<void(TextFieldModelNG&)>& callback = nullptr);
    static void ExpectCallParagraphMethods(ExpectParagraphParams params);
    void GetFocus();

    RefPtr<FrameNode> frameNode_;
    RefPtr<TextFieldPattern> pattern_;
    RefPtr<TextFieldEventHub> eventHub_;
    RefPtr<TextFieldLayoutProperty> layoutProperty_;
    RefPtr<TextFieldAccessibilityProperty> accessibilityProperty_;
};

void TextAreaDecorationBase::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    ExpectCallParagraphMethods(ExpectParagraphParams());
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textFieldTheme = AceType::MakeRefPtr<TextFieldTheme>();
    textFieldTheme->iconSize_ = Dimension(ICON_SIZE, DimensionUnit::VP);
    textFieldTheme->iconHotZoneSize_ = Dimension(ICON_HOT_ZONE_SIZE, DimensionUnit::VP);
    textFieldTheme->fontSize_ = Dimension(FONT_SIZE, DimensionUnit::FP);
    textFieldTheme->fontWeight_ = FontWeight::W400;
    textFieldTheme->textColor_ = Color::FromString("#ff182431");
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly([textFieldTheme = textFieldTheme](ThemeType type) -> RefPtr<Theme> {
            if (type == ScrollBarTheme::TypeId()) {
                return AceType::MakeRefPtr<ScrollBarTheme>();
            }
            return textFieldTheme;
        });
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(MIN_PLATFORM_VERSION);
    MockPipelineContext::GetCurrent()->SetTextFieldManager(AceType::MakeRefPtr<TextFieldManagerNG>());
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
}

void TextAreaDecorationBase::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
    MockParagraph::TearDown();
}

void TextAreaDecorationBase::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
}

void TextAreaDecorationBase::ExpectCallParagraphMethods(ExpectParagraphParams params)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, PushStyle(_)).Times(AnyNumber());
    EXPECT_CALL(*paragraph, AddText(_)).Times(AnyNumber());
    EXPECT_CALL(*paragraph, PopStyle()).Times(AnyNumber());
    EXPECT_CALL(*paragraph, Build()).Times(AnyNumber());
    EXPECT_CALL(*paragraph, Layout(_)).Times(AnyNumber());
    EXPECT_CALL(*paragraph, GetTextWidth()).WillRepeatedly(Return(params.maxWidth));
    EXPECT_CALL(*paragraph, GetAlphabeticBaseline()).WillRepeatedly(Return(0.f));
    EXPECT_CALL(*paragraph, GetHeight()).WillRepeatedly(Return(params.height));
    EXPECT_CALL(*paragraph, GetLongestLine()).WillRepeatedly(Return(params.longestLine));
    EXPECT_CALL(*paragraph, GetMaxWidth()).WillRepeatedly(Return(params.maxWidth));
    EXPECT_CALL(*paragraph, GetLineCount()).WillRepeatedly(Return(params.lineCount));
}

void TextAreaDecorationBase::CreateTextField(
    const std::string& text, const std::string& placeHolder, const std::function<void(TextFieldModelNG&)>& callback)
{
    auto* stack = ViewStackProcessor::GetInstance();
    stack->StartGetAccessRecordingFor(DEFAULT_NODE_ID);
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateTextArea(StringUtils::Str8ToStr16(placeHolder), StringUtils::Str8ToStr16(text));
    if (callback) {
        callback(textFieldModelNG);
    }
    stack->StopGetAccessRecording();
    frameNode_ = AceType::DynamicCast<FrameNode>(stack->Finish());
    pattern_ = frameNode_->GetPattern<TextFieldPattern>();
    eventHub_ = frameNode_->GetEventHub<TextFieldEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<TextFieldAccessibilityProperty>();
    FlushLayoutTask(frameNode_);
}

void TextAreaDecorationBase::GetFocus()
{
    auto focushHub = pattern_->GetFocusHub();
    focushHub->currentFocus_ = true;
    pattern_->HandleFocusEvent();
    FlushLayoutTask(frameNode_);
}

class TextAreaDecorationUXTest : public TextAreaDecorationBase {};
/**
 * @tc.name: TextAreaToJsonValue004
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaDecorationUXTest, TextAreaToJsonValue004, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::NONE);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::SOLID);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextArea JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto innerJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(innerJson, nullptr);
    /**
     * @tc.expected: check decoration in TextArea JSON is NONE, BLACK, SOLID
     */
    EXPECT_TRUE(innerJson->Contains("type"));
    EXPECT_TRUE(innerJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::NONE));
    EXPECT_TRUE(innerJson->Contains("color"));
    EXPECT_TRUE(innerJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(innerJson->Contains("style"));
    EXPECT_TRUE(innerJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::SOLID));
}

/**
 * @tc.name: TextAreaToJsonValue005
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaDecorationUXTest, TextAreaToJsonValue005, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::UNDERLINE);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::SOLID);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextArea JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto innerJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(innerJson, nullptr);
    /**
     * @tc.expected: check decoration in TextArea JSON is UNDERLINE, BLACK, SOLID
     */
    EXPECT_TRUE(innerJson->Contains("type"));
    EXPECT_TRUE(innerJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::UNDERLINE));
    EXPECT_TRUE(innerJson->Contains("color"));
    EXPECT_TRUE(innerJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(innerJson->Contains("style"));
    EXPECT_TRUE(innerJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::SOLID));
}

/**
 * @tc.name: TextAreaToJsonValue006
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaDecorationUXTest, TextAreaToJsonValue006, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::UNDERLINE);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::DOUBLE);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextArea JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto innerJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(innerJson, nullptr);
    /**
     * @tc.expected: check decoration in TextArea JSON is UNDERLINE, BLACK, DOUBLE
     */
    EXPECT_TRUE(innerJson->Contains("type"));
    EXPECT_TRUE(innerJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::UNDERLINE));
    EXPECT_TRUE(innerJson->Contains("color"));
    EXPECT_TRUE(innerJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(innerJson->Contains("style"));
    EXPECT_TRUE(innerJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::DOUBLE));
}

/**
 * @tc.name: TextAreaToJsonValue007
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaDecorationUXTest, TextAreaToJsonValue007, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::UNDERLINE);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::DOTTED);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextArea JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto innerJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(innerJson, nullptr);
    /**
     * @tc.expected: check decoration in TextArea JSON is UNDERLINE, BLACK, DOTTED
     */
    EXPECT_TRUE(innerJson->Contains("type"));
    EXPECT_TRUE(innerJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::UNDERLINE));
    EXPECT_TRUE(innerJson->Contains("color"));
    EXPECT_TRUE(innerJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(innerJson->Contains("style"));
    EXPECT_TRUE(innerJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::DOTTED));
}

/**
 * @tc.name: TextAreaToJsonValue008
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaDecorationUXTest, TextAreaToJsonValue008, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::UNDERLINE);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::DASHED);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextArea JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto innerJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(innerJson, nullptr);
    /**
     * @tc.expected: check decoration in TextArea JSON is UNDERLINE, BLACK, DASHED
     */
    EXPECT_TRUE(innerJson->Contains("type"));
    EXPECT_TRUE(innerJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::UNDERLINE));
    EXPECT_TRUE(innerJson->Contains("color"));
    EXPECT_TRUE(innerJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(innerJson->Contains("style"));
    EXPECT_TRUE(innerJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::DASHED));
}

/**
 * @tc.name: TextAreaToJsonValue009
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaDecorationUXTest, TextAreaToJsonValue009, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::UNDERLINE);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::WAVY);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextArea JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto innerJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(innerJson, nullptr);
    /**
     * @tc.expected: check decoration in TextArea JSON is UNDERLINE, BLACK, WAVY
     */
    EXPECT_TRUE(innerJson->Contains("type"));
    EXPECT_TRUE(innerJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::UNDERLINE));
    EXPECT_TRUE(innerJson->Contains("color"));
    EXPECT_TRUE(innerJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(innerJson->Contains("style"));
    EXPECT_TRUE(innerJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::WAVY));
}

/**
 * @tc.name: TextAreaToJsonValue010
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaDecorationUXTest, TextAreaToJsonValue010, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::UNDERLINE);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::INITIAL);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextArea JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto innerJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(innerJson, nullptr);
    /**
     * @tc.expected: check decoration in TextArea JSON is UNDERLINE, BLACK, INITIAL
     */
    EXPECT_TRUE(innerJson->Contains("type"));
    EXPECT_TRUE(innerJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::UNDERLINE));
    EXPECT_TRUE(innerJson->Contains("color"));
    EXPECT_TRUE(innerJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(innerJson->Contains("style"));
    EXPECT_TRUE(innerJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::INITIAL));
}

/**
 * @tc.name: TextAreaToJsonValue011
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaDecorationUXTest, TextAreaToJsonValue011, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::UNDERLINE);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::INHERIT);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextArea JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto innerJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(innerJson, nullptr);
    /**
     * @tc.expected: check decoration in TextArea JSON is UNDERLINE, BLACK, INHERIT
     */
    EXPECT_TRUE(innerJson->Contains("type"));
    EXPECT_TRUE(innerJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::UNDERLINE));
    EXPECT_TRUE(innerJson->Contains("color"));
    EXPECT_TRUE(innerJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(innerJson->Contains("style"));
    EXPECT_TRUE(innerJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::INHERIT));
}

/**
 * @tc.name: TextAreaToJsonValue012
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaDecorationUXTest, TextAreaToJsonValue012, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::OVERLINE);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::SOLID);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextArea JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto innerJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(innerJson, nullptr);
    /**
     * @tc.expected: check decoration in TextArea JSON is OVERLINE, BLACK, SOLID
     */
    EXPECT_TRUE(innerJson->Contains("type"));
    EXPECT_TRUE(innerJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::OVERLINE));
    EXPECT_TRUE(innerJson->Contains("color"));
    EXPECT_TRUE(innerJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(innerJson->Contains("style"));
    EXPECT_TRUE(innerJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::SOLID));
}

/**
 * @tc.name: TextAreaToJsonValue012
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaDecorationUXTest, TextAreaToJsonValue013, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::OVERLINE);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::DOUBLE);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextArea JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto innerJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(innerJson, nullptr);
    /**
     * @tc.expected: check decoration in TextArea JSON is OVERLINE, BLACK, DOUBLE
     */
    EXPECT_TRUE(innerJson->Contains("type"));
    EXPECT_TRUE(innerJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::OVERLINE));
    EXPECT_TRUE(innerJson->Contains("color"));
    EXPECT_TRUE(innerJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(innerJson->Contains("style"));
    EXPECT_TRUE(innerJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::DOUBLE));
}

/**
 * @tc.name: TextAreaToJsonValue014
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaDecorationUXTest, TextAreaToJsonValue014, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::OVERLINE);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::DOTTED);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextArea JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto innerJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(innerJson, nullptr);
    /**
     * @tc.expected: check decoration in TextArea JSON is OVERLINE, BLACK, DOTTED
     */
    EXPECT_TRUE(innerJson->Contains("type"));
    EXPECT_TRUE(innerJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::OVERLINE));
    EXPECT_TRUE(innerJson->Contains("color"));
    EXPECT_TRUE(innerJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(innerJson->Contains("style"));
    EXPECT_TRUE(innerJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::DOTTED));
}

/**
 * @tc.name: TextAreaToJsonValue015
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaDecorationUXTest, TextAreaToJsonValue015, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::OVERLINE);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::DASHED);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextArea JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto innerJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(innerJson, nullptr);
    /**
     * @tc.expected: check decoration in TextArea JSON is OVERLINE, BLACK, DASHED
     */
    EXPECT_TRUE(innerJson->Contains("type"));
    EXPECT_TRUE(innerJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::OVERLINE));
    EXPECT_TRUE(innerJson->Contains("color"));
    EXPECT_TRUE(innerJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(innerJson->Contains("style"));
    EXPECT_TRUE(innerJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::DASHED));
}

/**
 * @tc.name: TextAreaToJsonValue016
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaDecorationUXTest, TextAreaToJsonValue016, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::OVERLINE);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::WAVY);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextArea JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto innerJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(innerJson, nullptr);
    /**
     * @tc.expected: check decoration in TextArea JSON is OVERLINE, BLACK, WAVY
     */
    EXPECT_TRUE(innerJson->Contains("type"));
    EXPECT_TRUE(innerJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::OVERLINE));
    EXPECT_TRUE(innerJson->Contains("color"));
    EXPECT_TRUE(innerJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(innerJson->Contains("style"));
    EXPECT_TRUE(innerJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::WAVY));
}

/**
 * @tc.name: TextAreaToJsonValue017
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaDecorationUXTest, TextAreaToJsonValue017, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::OVERLINE);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::INITIAL);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextArea JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto innerJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(innerJson, nullptr);
    /**
     * @tc.expected: check decoration in TextArea JSON is OVERLINE, BLACK, INITIAL
     */
    EXPECT_TRUE(innerJson->Contains("type"));
    EXPECT_TRUE(innerJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::OVERLINE));
    EXPECT_TRUE(innerJson->Contains("color"));
    EXPECT_TRUE(innerJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(innerJson->Contains("style"));
    EXPECT_TRUE(innerJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::INITIAL));
}

/**
 * @tc.name: TextAreaToJsonValue018
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaDecorationUXTest, TextAreaToJsonValue018, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::OVERLINE);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::INHERIT);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextArea JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto innerJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(innerJson, nullptr);
    /**
     * @tc.expected: check decoration in TextArea JSON is OVERLINE, BLACK, INHERIT
     */
    EXPECT_TRUE(innerJson->Contains("type"));
    EXPECT_TRUE(innerJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::OVERLINE));
    EXPECT_TRUE(innerJson->Contains("color"));
    EXPECT_TRUE(innerJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(innerJson->Contains("style"));
    EXPECT_TRUE(innerJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::INHERIT));
}

/**
 * @tc.name: TextAreaToJsonValue019
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaDecorationUXTest, TextAreaToJsonValue019, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::LINE_THROUGH);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::SOLID);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextArea JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto innerJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(innerJson, nullptr);
    /**
     * @tc.expected: check decoration in TextArea JSON is LINE_THROUGH, BLACK, SOLID
     */
    EXPECT_TRUE(innerJson->Contains("type"));
    EXPECT_TRUE(innerJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::LINE_THROUGH));
    EXPECT_TRUE(innerJson->Contains("color"));
    EXPECT_TRUE(innerJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(innerJson->Contains("style"));
    EXPECT_TRUE(innerJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::SOLID));
}

/**
 * @tc.name: TextAreaToJsonValue020
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaDecorationUXTest, TextAreaToJsonValue020, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::LINE_THROUGH);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::DOUBLE);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextArea JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto innerJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(innerJson, nullptr);
    /**
     * @tc.expected: check decoration in TextArea JSON is LINE_THROUGH, BLACK, SOLID
     */
    EXPECT_TRUE(innerJson->Contains("type"));
    EXPECT_TRUE(innerJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::LINE_THROUGH));
    EXPECT_TRUE(innerJson->Contains("color"));
    EXPECT_TRUE(innerJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(innerJson->Contains("style"));
    EXPECT_TRUE(innerJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::DOUBLE));
}

/**
 * @tc.name: TextAreaToJsonValue021
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaDecorationUXTest, TextAreaToJsonValue021, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::LINE_THROUGH);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::DOTTED);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextArea JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto innerJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(innerJson, nullptr);
    /**
     * @tc.expected: check decoration in TextArea JSON is LINE_THROUGH, BLACK, DOTTED
     */
    EXPECT_TRUE(innerJson->Contains("type"));
    EXPECT_TRUE(innerJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::LINE_THROUGH));
    EXPECT_TRUE(innerJson->Contains("color"));
    EXPECT_TRUE(innerJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(innerJson->Contains("style"));
    EXPECT_TRUE(innerJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::DOTTED));
}

/**
 * @tc.name: TextAreaToJsonValue022
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaDecorationUXTest, TextAreaToJsonValue022, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::LINE_THROUGH);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::DASHED);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextArea JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto innerJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(innerJson, nullptr);
    /**
     * @tc.expected: check decoration in TextArea JSON is LINE_THROUGH, BLACK, DASHED
     */
    EXPECT_TRUE(innerJson->Contains("type"));
    EXPECT_TRUE(innerJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::LINE_THROUGH));
    EXPECT_TRUE(innerJson->Contains("color"));
    EXPECT_TRUE(innerJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(innerJson->Contains("style"));
    EXPECT_TRUE(innerJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::DASHED));
}

/**
 * @tc.name: TextAreaToJsonValue023
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaDecorationUXTest, TextAreaToJsonValue023, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::LINE_THROUGH);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::WAVY);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextArea JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto innerJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(innerJson, nullptr);
    /**
     * @tc.expected: check decoration in TextArea JSON is LINE_THROUGH, BLACK, WAVY
     */
    EXPECT_TRUE(innerJson->Contains("type"));
    EXPECT_TRUE(innerJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::LINE_THROUGH));
    EXPECT_TRUE(innerJson->Contains("color"));
    EXPECT_TRUE(innerJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(innerJson->Contains("style"));
    EXPECT_TRUE(innerJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::WAVY));
}

/**
 * @tc.name: TextAreaToJsonValue024
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaDecorationUXTest, TextAreaToJsonValue024, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::LINE_THROUGH);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::INITIAL);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextArea JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto innerJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(innerJson, nullptr);
    /**
     * @tc.expected: check decoration in TextArea JSON is LINE_THROUGH, BLACK, INITIAL
     */
    EXPECT_TRUE(innerJson->Contains("type"));
    EXPECT_TRUE(innerJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::LINE_THROUGH));
    EXPECT_TRUE(innerJson->Contains("color"));
    EXPECT_TRUE(innerJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(innerJson->Contains("style"));
    EXPECT_TRUE(innerJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::INITIAL));
}

/**
 * @tc.name: TextAreaToJsonValue025
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaDecorationUXTest, TextAreaToJsonValue025, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::LINE_THROUGH);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::INHERIT);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextArea JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto innerJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(innerJson, nullptr);
    /**
     * @tc.expected: check decoration in TextArea JSON is LINE_THROUGH, BLACK, INHERIT
     */
    EXPECT_TRUE(innerJson->Contains("type"));
    EXPECT_TRUE(innerJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::LINE_THROUGH));
    EXPECT_TRUE(innerJson->Contains("color"));
    EXPECT_TRUE(innerJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(innerJson->Contains("style"));
    EXPECT_TRUE(innerJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::INHERIT));
}

/**
 * @tc.name: TextAreaToJsonValue026
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaDecorationUXTest, TextAreaToJsonValue026, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::INHERIT);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::SOLID);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextArea JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto innerJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(innerJson, nullptr);
    /**
     * @tc.expected: check decoration in TextArea JSON is INHERIT, BLACK, SOLID
     */
    EXPECT_TRUE(innerJson->Contains("type"));
    EXPECT_TRUE(innerJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::INHERIT));
    EXPECT_TRUE(innerJson->Contains("color"));
    EXPECT_TRUE(innerJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(innerJson->Contains("style"));
    EXPECT_TRUE(innerJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::SOLID));
}

/**
 * @tc.name: TextAreaToJsonValue027
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaDecorationUXTest, TextAreaToJsonValue027, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::INHERIT);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::DOUBLE);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextArea JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto innerJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(innerJson, nullptr);
    /**
     * @tc.expected: check decoration in TextArea JSON is INHERIT, BLACK, DOUBLE
     */
    EXPECT_TRUE(innerJson->Contains("type"));
    EXPECT_TRUE(innerJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::INHERIT));
    EXPECT_TRUE(innerJson->Contains("color"));
    EXPECT_TRUE(innerJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(innerJson->Contains("style"));
    EXPECT_TRUE(innerJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::DOUBLE));
}

/**
 * @tc.name: TextAreaToJsonValue028
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaDecorationUXTest, TextAreaToJsonValue028, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::INHERIT);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::DOTTED);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextArea JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto innerJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(innerJson, nullptr);
    /**
     * @tc.expected: check decoration in TextArea JSON is INHERIT, BLACK, DOTTED
     */
    EXPECT_TRUE(innerJson->Contains("type"));
    EXPECT_TRUE(innerJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::INHERIT));
    EXPECT_TRUE(innerJson->Contains("color"));
    EXPECT_TRUE(innerJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(innerJson->Contains("style"));
    EXPECT_TRUE(innerJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::DOTTED));
}

/**
 * @tc.name: TextAreaToJsonValue029
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaDecorationUXTest, TextAreaToJsonValue029, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::INHERIT);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::DASHED);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextArea JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto innerJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(innerJson, nullptr);
    /**
     * @tc.expected: check decoration in TextArea JSON is INHERIT, BLACK, DASHED
     */
    EXPECT_TRUE(innerJson->Contains("type"));
    EXPECT_TRUE(innerJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::INHERIT));
    EXPECT_TRUE(innerJson->Contains("color"));
    EXPECT_TRUE(innerJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(innerJson->Contains("style"));
    EXPECT_TRUE(innerJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::DASHED));
}

/**
 * @tc.name: TextAreaToJsonValue030
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaDecorationUXTest, TextAreaToJsonValue030, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::INHERIT);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::WAVY);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextArea JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto innerJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(innerJson, nullptr);
    /**
     * @tc.expected: check decoration in TextArea JSON is INHERIT, BLACK, WAVY
     */
    EXPECT_TRUE(innerJson->Contains("type"));
    EXPECT_TRUE(innerJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::INHERIT));
    EXPECT_TRUE(innerJson->Contains("color"));
    EXPECT_TRUE(innerJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(innerJson->Contains("style"));
    EXPECT_TRUE(innerJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::WAVY));
}

/**
 * @tc.name: TextAreaToJsonValue031
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaDecorationUXTest, TextAreaToJsonValue031, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::INHERIT);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::INITIAL);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextArea JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto innerJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(innerJson, nullptr);
    /**
     * @tc.expected: check decoration in TextArea JSON is INHERIT, BLACK, INITIAL
     */
    EXPECT_TRUE(innerJson->Contains("type"));
    EXPECT_TRUE(innerJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::INHERIT));
    EXPECT_TRUE(innerJson->Contains("color"));
    EXPECT_TRUE(innerJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(innerJson->Contains("style"));
    EXPECT_TRUE(innerJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::INITIAL));
}

/**
 * @tc.name: TextAreaToJsonValue032
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaDecorationUXTest, TextAreaToJsonValue032, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::INHERIT);
        model.SetTextDecorationColor(Color::BLACK);
        model.SetTextDecorationStyle(TextDecorationStyle::INHERIT);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextArea JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto innerJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(innerJson, nullptr);
    /**
     * @tc.expected: check decoration in TextArea JSON is INHERIT, BLACK, INHERIT
     */
    EXPECT_TRUE(innerJson->Contains("type"));
    EXPECT_TRUE(innerJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::INHERIT));
    EXPECT_TRUE(innerJson->Contains("color"));
    EXPECT_TRUE(innerJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(innerJson->Contains("style"));
    EXPECT_TRUE(innerJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::INHERIT));
}

/**
 * @tc.name: TextAreaToJsonValue033
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaDecorationUXTest, TextAreaToJsonValue033, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetLetterSpacing(0.0_px);
        model.SetLineHeight(0.0_px);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextArea JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    /**
     * @tc.expected: check letterSpacing in TextArea JSON is 0.00px
     */
    EXPECT_EQ(json->GetString("letterSpacing"), "0.00px");
    /**
     * @tc.expected: check lineHeight in TextArea JSON is 0.00px
     */
    EXPECT_EQ(json->GetString("lineHeight"), "0.00px");
}

/**
 * @tc.name: TextAreaToJsonValue034
 * @tc.desc: test attrs on ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaDecorationUXTest, TextAreaToJsonValue034, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetLetterSpacing(2.0_px);
        model.SetLineHeight(3.0_px);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the TextArea JSON
     */
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    layoutProperty_->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    /**
     * @tc.expected: check letterSpacing in TextArea JSON is 2.00px
     */
    EXPECT_EQ(json->GetString("letterSpacing"), "2.00px");
    /**
     * @tc.expected: check lineHeight in TextArea JSON is 3.00px
     */
    EXPECT_EQ(json->GetString("lineHeight"), "3.00px");
}
}
