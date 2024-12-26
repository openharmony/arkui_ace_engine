/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include "test/mock/core/common/mock_data_detector_mgr.h"
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
constexpr int32_t WORD_LIMIT_LEN = 5;
constexpr int32_t WORD_LIMIT_RETURN = 2;
constexpr int32_t BEYOND_LIMIT_RETURN = 4;
constexpr int32_t DEFAULT_RETURN_VALUE = -1;
const std::string DEFAULT_TEXT = "abcdefghijklmnopqrstuvwxyz";
const std::u16string DEFAULT_TEXT_U16 = u"abcdefghijklmnopqrstuvwxyz";
const InputStyle DEFAULT_INPUT_STYLE = InputStyle::INLINE;
struct ExpectParagraphParams {
    float height = 50.f;
    float longestLine = 460.f;
    float maxWidth = 460.f;
    size_t lineCount = 1;
    bool firstCalc = true;
    bool secondCalc = true;
};
} // namespace

class TextInputWordBreak : public TestNG {
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

void TextInputWordBreak::SetUpTestSuite()
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

void TextInputWordBreak::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
    MockParagraph::TearDown();
}

void TextInputWordBreak::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
}

void TextInputWordBreak::ExpectCallParagraphMethods(ExpectParagraphParams params)
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

void TextInputWordBreak::CreateTextField(
    const std::string& text, const std::string& placeHolder, const std::function<void(TextFieldModelNG&)>& callback)
{
    auto* stack = ViewStackProcessor::GetInstance();
    stack->StartGetAccessRecordingFor(DEFAULT_NODE_ID);
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateTextInput(StringUtils::Str8ToStr16(placeHolder), StringUtils::Str8ToStr16(text));
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

void TextInputWordBreak::GetFocus()
{
    auto focushHub = pattern_->GetFocusHub();
    focushHub->currentFocus_ = true;
    pattern_->HandleFocusEvent();
    FlushLayoutTask(frameNode_);
}

class TextInputWordBreakTest : public TextInputWordBreak {
protected:
    static void InitAdjustObject(MockDataDetectorMgr& mockDataDetectorMgr);
};

void TextInputWordBreakTest::InitAdjustObject(MockDataDetectorMgr& mockDataDetectorMgr)
{
    EXPECT_CALL(mockDataDetectorMgr, GetCursorPosition(_, _))
        .WillRepeatedly([](const std::string& text, int8_t /* offset */) -> int8_t {
            if (text.empty()) {
                return DEFAULT_RETURN_VALUE;
            }
            if (text.length() <= WORD_LIMIT_LEN) {
                return WORD_LIMIT_RETURN;
            }
            return BEYOND_LIMIT_RETURN;
        });

    EXPECT_CALL(mockDataDetectorMgr, GetWordSelection(_, _))
        .WillRepeatedly([](const std::string& text, int8_t /* offset */) -> std::vector<int8_t> {
            if (text.empty()) {
                return std::vector<int8_t> { -1, -1 };
            }

            if (text.length() <= WORD_LIMIT_LEN) {
                return std::vector<int8_t> { 2, 3 };
            }
            return std::vector<int8_t> { 0, 2 };
        });
}

/**
 * @tc.name: LayoutProperty001
 * @tc.desc: Test attrs on TextInput
 * @tc.type: FUNC
 */
HWTEST_F(TextInputWordBreakTest, LayoutProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetWordBreak(WordBreak::BREAK_ALL);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the corresponding JSON
     */
    const InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("wordBreak"), "break-all");
}

/**
 * @tc.name: textInputWordBreak001
 * @tc.desc: test testInput WordBreak attribute, set the value to NORMAL
 * @tc.type: FUNC
 */
HWTEST_F(TextInputWordBreakTest, textInputWordBreak001, TestSize.Level1)
{
    /**
     * @tc.step1: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set wordBreak NORMAL
     */
    layoutProperty_->UpdateWordBreak(WordBreak::NORMAL);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetWordBreak(), WordBreak::NORMAL);
}

/**
 * @tc.name: textInputWordBreak002
 * @tc.desc: test testInput WordBreak attribute, set the value to BREAK_ALL
 * @tc.type: FUNC
 */
HWTEST_F(TextInputWordBreakTest, textInputWordBreak002, TestSize.Level1)
{
    /**
     * @tc.step1: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set wordBreak BREAK_ALL
     */
    layoutProperty_->UpdateWordBreak(WordBreak::BREAK_ALL);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetWordBreak(), WordBreak::BREAK_ALL);
}

/**
 * @tc.name: textInputWordBreak003
 * @tc.desc: test testInput WordBreak attribute, set the value to BREAK_WORD
 * @tc.type: FUNC
 */
HWTEST_F(TextInputWordBreakTest, textInputWordBreak003, TestSize.Level1)
{
    /**
     * @tc.step1: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set wordBreak BREAK_WORD
     */
    layoutProperty_->UpdateWordBreak(WordBreak::BREAK_WORD);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetWordBreak(), WordBreak::BREAK_WORD);
}

/**
 * @tc.name: textInputWordBreak004
 * @tc.desc: test testInput WordBreak attribute, set the invalid value
 * @tc.type: FUNC
 */
HWTEST_F(TextInputWordBreakTest, textInputWordBreak004, TestSize.Level1)
{
    /**
     * @tc.step1: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set wordBreak invalid value
     */
    const uint32_t invalidValue = 3;
    layoutProperty_->UpdateWordBreak((OHOS::Ace::WordBreak)invalidValue);
    frameNode_->MarkModifyDone();
    EXPECT_EQ((uint32_t)(layoutProperty_->GetWordBreak().value()), invalidValue);
}

/**
 * @tc.name: textInputWordBreak005
 * @tc.desc: test testInput WordBreak attribute, set the invalid value
 * @tc.type: FUNC
 */
HWTEST_F(TextInputWordBreakTest, textInputWordBreak005, TestSize.Level1)
{
    /**
     * @tc.step1: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set wordBreak invalid value
     */
    const int32_t invalidValue = -1;
    layoutProperty_->UpdateWordBreak((OHOS::Ace::WordBreak)invalidValue);
    frameNode_->MarkModifyDone();
    EXPECT_EQ((int32_t)(layoutProperty_->GetWordBreak().value()), invalidValue);
}

/**
 * @tc.name: textInputLayout001
 * @tc.desc: test textStyle, set the value to NORMAL
 * @tc.type: FUNC
 */
HWTEST_F(TextInputWordBreakTest, textInputLayout001, TestSize.Level1)
{
    /**
     * @tc.step1: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set wordBreak NORMAL
     */
    layoutProperty_->UpdateWordBreak(WordBreak::NORMAL);
    frameNode_->MarkModifyDone();

    /**
     * @tc.step: step3. Create algorithm class
     */
    auto textInputLayoutAlgorithm = AccessibilityManager::MakeRefPtr<TextInputLayoutAlgorithm>();

    /**
     * @tc.step: step4. Construct TextStyles object
     */
    TextStyle textStyle;
    std::u16string textContent(DEFAULT_TEXT_U16);
    bool showPlaceHolder = false;
    textInputLayoutAlgorithm->ConstructTextStyles(frameNode_, textStyle, textContent, showPlaceHolder);
    EXPECT_EQ(textStyle.GetWordBreak(), WordBreak::NORMAL);
}

/**
 * @tc.name: textInputLayout002
 * @tc.desc: test textStyle, set the value to BREAK_ALL
 * @tc.type: FUNC
 */
HWTEST_F(TextInputWordBreakTest, textInputLayout002, TestSize.Level1)
{
    /**
     * @tc.step1: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set wordBreak BREAK_ALL
     */
    layoutProperty_->UpdateWordBreak(WordBreak::BREAK_ALL);
    frameNode_->MarkModifyDone();

    /**
     * @tc.step: step3. Create algorithm class
     */
    auto textInputLayoutAlgorithm = AccessibilityManager::MakeRefPtr<TextInputLayoutAlgorithm>();

    /**
     * @tc.step: step4. Construct TextStyles object
     */
    TextStyle textStyle;
    std::u16string textContent(DEFAULT_TEXT_U16);
    bool showPlaceHolder = false;
    textInputLayoutAlgorithm->ConstructTextStyles(frameNode_, textStyle, textContent, showPlaceHolder);
    EXPECT_EQ(textStyle.GetWordBreak(), WordBreak::BREAK_ALL);
}

/**
 * @tc.name: textInputLayout003
 * @tc.desc: test textStyle, set the value to BREAK_WORD
 * @tc.type: FUNC
 */
HWTEST_F(TextInputWordBreakTest, textInputLayout003, TestSize.Level1)
{
    /**
     * @tc.step1: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set wordBreak BREAK_WORD
     */
    layoutProperty_->UpdateWordBreak(WordBreak::BREAK_WORD);
    frameNode_->MarkModifyDone();

    /**
     * @tc.step: step3. Create algorithm class
     */
    auto textInputLayoutAlgorithm = AccessibilityManager::MakeRefPtr<TextInputLayoutAlgorithm>();

    /**
     * @tc.step: step4. Construct TextStyles object
     */
    TextStyle textStyle;
    std::u16string textContent(DEFAULT_TEXT_U16);
    bool showPlaceHolder = false;
    textInputLayoutAlgorithm->ConstructTextStyles(frameNode_, textStyle, textContent, showPlaceHolder);
    EXPECT_EQ(textStyle.GetWordBreak(), WordBreak::BREAK_WORD);
}

/**
 * @tc.name: textInputLayout004
 * @tc.desc: test textStyle, set the invalid value
 * @tc.type: FUNC
 */
HWTEST_F(TextInputWordBreakTest, textInputLayout004, TestSize.Level1)
{
    /**
     * @tc.step1: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set wordBreak invalid value
     */
    const uint32_t invalidValue = 3;
    layoutProperty_->UpdateWordBreak((OHOS::Ace::WordBreak)invalidValue);
    frameNode_->MarkModifyDone();
    EXPECT_EQ((uint32_t)(layoutProperty_->GetWordBreak().value()), invalidValue);

    /**
     * @tc.step: step3. Create algorithm class
     */
    auto textInputLayoutAlgorithm = AccessibilityManager::MakeRefPtr<TextInputLayoutAlgorithm>();

    /**
     * @tc.step: step4. Construct TextStyles object
     */
    TextStyle textStyle;
    std::u16string textContent(DEFAULT_TEXT_U16);
    bool showPlaceHolder = false;
    textInputLayoutAlgorithm->ConstructTextStyles(frameNode_, textStyle, textContent, showPlaceHolder);
    EXPECT_EQ((uint32_t)(textStyle.GetWordBreak()), invalidValue);
}

/**
 * @tc.name: textInputLayout005
 * @tc.desc: test textStyle, set the invalid value
 * @tc.type: FUNC
 */
HWTEST_F(TextInputWordBreakTest, textInputLayout005, TestSize.Level1)
{
    /**
     * @tc.step1: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set wordBreak invalid value
     */
    const int32_t invalidValue = -1;
    layoutProperty_->UpdateWordBreak((OHOS::Ace::WordBreak)invalidValue);
    frameNode_->MarkModifyDone();
    EXPECT_EQ((int32_t)(layoutProperty_->GetWordBreak().value()), invalidValue);

    /**
     * @tc.step: step3. Create algorithm class
     */
    auto textInputLayoutAlgorithm = AccessibilityManager::MakeRefPtr<TextInputLayoutAlgorithm>();

    /**
     * @tc.step: step4. Construct TextStyles object
     */
    TextStyle textStyle;
    std::u16string textContent(DEFAULT_TEXT_U16);
    bool showPlaceHolder = false;
    textInputLayoutAlgorithm->ConstructTextStyles(frameNode_, textStyle, textContent, showPlaceHolder);
    EXPECT_EQ((int32_t)(textStyle.GetWordBreak()), invalidValue);
}

/**
 * @tc.name: textInputLayout006
 * @tc.desc: test textStyle, set the value to HEAD
 * @tc.type: FUNC
 */
HWTEST_F(TextInputWordBreakTest, textInputLayout006, TestSize.Level1)
{
    /**
     * @tc.step1: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set EllipsisMode
     */
    layoutProperty_->UpdateEllipsisMode(EllipsisMode::HEAD);
    frameNode_->MarkModifyDone();

    /**
     * @tc.step: step3. Create algorithm class
     */
    auto textInputLayoutAlgorithm = AccessibilityManager::MakeRefPtr<TextInputLayoutAlgorithm>();

    /**
     * @tc.step: step4. Construct TextStyles object
     */
    TextStyle textStyle;
    std::u16string textContent(DEFAULT_TEXT_U16);
    bool showPlaceHolder = false;
    textInputLayoutAlgorithm->ConstructTextStyles(frameNode_, textStyle, textContent, showPlaceHolder);
    EXPECT_EQ(textStyle.GetEllipsisMode(), EllipsisMode::HEAD);
}

/**
 * @tc.name: textInputLayout007
 * @tc.desc: test textStyle, set the value to MIDDLE
 * @tc.type: FUNC
 */
HWTEST_F(TextInputWordBreakTest, textInputLayout007, TestSize.Level1)
{
    /**
     * @tc.step1: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set EllipsisMode
     */
    layoutProperty_->UpdateEllipsisMode(EllipsisMode::MIDDLE);
    frameNode_->MarkModifyDone();

    /**
     * @tc.step: step3. Create algorithm class
     */
    auto textInputLayoutAlgorithm = AccessibilityManager::MakeRefPtr<TextInputLayoutAlgorithm>();

    /**
     * @tc.step: step4. Construct TextStyles object
     */
    TextStyle textStyle;
    std::u16string textContent(DEFAULT_TEXT_U16);
    bool showPlaceHolder = false;
    textInputLayoutAlgorithm->ConstructTextStyles(frameNode_, textStyle, textContent, showPlaceHolder);
    EXPECT_EQ(textStyle.GetEllipsisMode(), EllipsisMode::MIDDLE);
}

/**
 * @tc.name: textInputLayout008
 * @tc.desc: test textStyle, set the value to TAIL
 * @tc.type: FUNC
 */
HWTEST_F(TextInputWordBreakTest, textInputLayout008, TestSize.Level1)
{
    /**
     * @tc.step1: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set EllipsisMode
     */
    layoutProperty_->UpdateEllipsisMode(EllipsisMode::TAIL);
    frameNode_->MarkModifyDone();

    /**
     * @tc.step: step3. Create algorithm class
     */
    auto textInputLayoutAlgorithm = AccessibilityManager::MakeRefPtr<TextInputLayoutAlgorithm>();

    /**
     * @tc.step: step4. Construct TextStyles object
     */
    TextStyle textStyle;
    std::u16string textContent(DEFAULT_TEXT_U16);
    bool showPlaceHolder = false;
    textInputLayoutAlgorithm->ConstructTextStyles(frameNode_, textStyle, textContent, showPlaceHolder);
    EXPECT_EQ(textStyle.GetEllipsisMode(), EllipsisMode::TAIL);
}
} // namespace OHOS::Ace::NG
