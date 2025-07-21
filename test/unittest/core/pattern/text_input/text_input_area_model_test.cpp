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
#include "test/unittest/core/pattern/text/text_base.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/text_field/text_field_layout_algorithm.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_model_static.h"
#include "core/components_ng/pattern/text/text_model_static.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/pattern/text/image_span_view_static.h"
#include "core/components_ng/pattern/image/image_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr double ICON_SIZE = 24;
constexpr double ICON_HOT_ZONE_SIZE = 40;
constexpr int32_t DEFAULT_NODE_ID = 1;
constexpr int32_t MIN_PLATFORM_VERSION = 10;
constexpr int32_t MAX_LENGTH = 100;
const std::string WORLD_TEXT = "world";
const std::string TEXTCASE_TEXT = "textcase";
const std::u16string TEXTCASE_TEXT_U16 = u"textcase";
const std::string HELLO_TEXT = "hello";
const std::string DEFAULT_TEXT = "abcdefghijklmnopqrstuvwxyz";
const std::u16string DEFAULT_TEXT_U16 = u"abcdefghijklmnopqrstuvwxyz";
const InputStyle DEFAULT_INPUT_STYLE = InputStyle::INLINE;
const Dimension DEFAULT_INDENT_SIZE = Dimension(5, DimensionUnit::VP);
const Dimension DEFAULT_INDENT_SIZE2 = Dimension(6, DimensionUnit::VP);
const Dimension DEFAULT_INDENT_SIZE3 = Dimension(7, DimensionUnit::VP);
const Dimension DEFAULT_INDENT_SIZE4 = Dimension(8, DimensionUnit::VP);
const Dimension DEFAULT_INDENT_SIZE5 = Dimension(9, DimensionUnit::VP);
const Dimension DEFAULT_INDENT_SIZE6 = Dimension(10, DimensionUnit::VP);
const float PADDING_FIVE = 5.0f;
const Color COLOR_DEFAULT = Color::RED;
const Color STROKE_COLOR_VALUE_0 = Color::FromRGB(255, 100, 100);
const Color STORKE_COLOR_VALUE_1 = Color::FromRGB(255, 255, 100);
const CaretStyle DEFAULT_CARET_STYLE = { Dimension(3, DimensionUnit::VP) };
struct ExpectParagraphParams {
    float height = 50.f;
    float longestLine = 460.f;
    float maxWidth = 460.f;
    size_t lineCount = 1;
    bool firstCalc = true;
    bool secondCalc = true;
};
} // namespace

class TextInputAreaBase : public TestNG {
protected:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void TearDown() override;

    void FlushLayoutTask(const RefPtr<FrameNode>& frameNode);
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

void TextInputAreaBase::SetUpTestSuite()
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
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([textFieldTheme = textFieldTheme](ThemeType type, int id) -> RefPtr<Theme> {
            if (type == ScrollBarTheme::TypeId()) {
                return AceType::MakeRefPtr<ScrollBarTheme>();
            }
            return textFieldTheme;
        });
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(MIN_PLATFORM_VERSION);
    MockPipelineContext::GetCurrent()->SetTextFieldManager(AceType::MakeRefPtr<TextFieldManagerNG>());
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
}

void TextInputAreaBase::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
    MockParagraph::TearDown();
}

void TextInputAreaBase::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
}

void TextInputAreaBase::ExpectCallParagraphMethods(ExpectParagraphParams params)
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

void TextInputAreaBase::FlushLayoutTask(const RefPtr<FrameNode>& frameNode)
{
    frameNode->SetActive();
    frameNode->isLayoutDirtyMarked_ = true;
    frameNode->CreateLayoutTask();
    auto paintProperty = frameNode->GetPaintProperty<PaintProperty>();
    auto wrapper = frameNode->CreatePaintWrapper();
    if (wrapper != nullptr) {
        wrapper->FlushRender();
    }
    paintProperty->CleanDirty();
    frameNode->SetActive(false);
}

void TextInputAreaBase::CreateTextField(
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
    eventHub_ = frameNode_->GetOrCreateEventHub<TextFieldEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<TextFieldAccessibilityProperty>();
    FlushLayoutTask(frameNode_);
}

void TextInputAreaBase::GetFocus()
{
    auto focushHub = pattern_->GetFocusHub();
    focushHub->currentFocus_ = true;
    pattern_->HandleFocusEvent();
    FlushLayoutTask(frameNode_);
}

class TextInputAreaTest : public TextInputAreaBase {};

/**
 * @tc.name: testTextIndent002
 * @tc.desc: test testInput text TextIndent
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testTextIndent002, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set textIndent
     */
    layoutProperty_->UpdateTextIndent(DEFAULT_INDENT_SIZE2);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextIndent(), DEFAULT_INDENT_SIZE2);
}

/**
 * @tc.name: testTextIndent003
 * @tc.desc: test testInput text TextIndent
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testTextIndent003, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set textIndent
     */
    layoutProperty_->UpdateTextIndent(DEFAULT_INDENT_SIZE3);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextIndent(), DEFAULT_INDENT_SIZE3);
}

/**
 * @tc.name: testTextIndent004
 * @tc.desc: test testInput text TextIndent
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testTextIndent004, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set textIndent
     */
    layoutProperty_->UpdateTextIndent(DEFAULT_INDENT_SIZE4);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextIndent(), DEFAULT_INDENT_SIZE4);
}

/**
 * @tc.name: testTextIndent005
 * @tc.desc: test testInput text TextIndent
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testTextIndent005, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set textIndent
     */
    layoutProperty_->UpdateTextIndent(DEFAULT_INDENT_SIZE5);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextIndent(), DEFAULT_INDENT_SIZE5);
}

/**
 * @tc.name: testTextIndent006
 * @tc.desc: test testInput text TextIndent
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testTextIndent006, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set textIndent
     */
    layoutProperty_->UpdateTextIndent(DEFAULT_INDENT_SIZE6);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextIndent(), DEFAULT_INDENT_SIZE6);
}

/**
 * @tc.name: testTextIndent007
 * @tc.desc: test testInput text TextIndent
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testTextIndent007, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(HELLO_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set textIndent
     */
    layoutProperty_->UpdateTextIndent(DEFAULT_INDENT_SIZE);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextIndent(), DEFAULT_INDENT_SIZE);
}

/**
 * @tc.name: testTextIndent008
 * @tc.desc: test testInput text TextIndent
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testTextIndent008, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(HELLO_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set textIndent
     */
    layoutProperty_->UpdateTextIndent(DEFAULT_INDENT_SIZE2);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextIndent(), DEFAULT_INDENT_SIZE2);
}

/**
 * @tc.name: testTextIndent009
 * @tc.desc: test testInput text TextIndent
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testTextIndent009, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(HELLO_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set textIndent
     */
    layoutProperty_->UpdateTextIndent(DEFAULT_INDENT_SIZE3);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextIndent(), DEFAULT_INDENT_SIZE3);
}

/**
 * @tc.name: testTextIndent010
 * @tc.desc: test testInput text TextIndent
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testTextIndent010, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(HELLO_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set textIndent
     */
    layoutProperty_->UpdateTextIndent(DEFAULT_INDENT_SIZE4);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextIndent(), DEFAULT_INDENT_SIZE4);
}

/**
 * @tc.name: testTextIndent011
 * @tc.desc: test testInput text TextIndent
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testTextIndent011, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(HELLO_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set textIndent
     */
    layoutProperty_->UpdateTextIndent(DEFAULT_INDENT_SIZE5);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextIndent(), DEFAULT_INDENT_SIZE5);
}

/**
 * @tc.name: testTextIndent012
 * @tc.desc: test testInput text TextIndent
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testTextIndent012, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(HELLO_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set textIndent
     */
    layoutProperty_->UpdateTextIndent(DEFAULT_INDENT_SIZE6);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextIndent(), DEFAULT_INDENT_SIZE6);
}

/**
 * @tc.name: testTextIndent013
 * @tc.desc: test testInput text TextIndent
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testTextIndent013, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(WORLD_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set textIndent
     */
    layoutProperty_->UpdateTextIndent(DEFAULT_INDENT_SIZE);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextIndent(), DEFAULT_INDENT_SIZE);
}

/**
 * @tc.name: testTextIndent014
 * @tc.desc: test testInput text TextIndent
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testTextIndent014, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(WORLD_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set textIndent
     */
    layoutProperty_->UpdateTextIndent(DEFAULT_INDENT_SIZE2);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextIndent(), DEFAULT_INDENT_SIZE2);
}

/**
 * @tc.name: testTextIndent015
 * @tc.desc: test testInput text TextIndent
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testTextIndent015, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(WORLD_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set textIndent
     */
    layoutProperty_->UpdateTextIndent(DEFAULT_INDENT_SIZE3);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextIndent(), DEFAULT_INDENT_SIZE3);
}

/**
 * @tc.name: testTextIndent016
 * @tc.desc: test testInput text TextIndent
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testTextIndent016, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(WORLD_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set textIndent
     */
    layoutProperty_->UpdateTextIndent(DEFAULT_INDENT_SIZE4);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextIndent(), DEFAULT_INDENT_SIZE4);
}

/**
 * @tc.name: testTextIndent017
 * @tc.desc: test testInput text TextIndent
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testTextIndent017, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(WORLD_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set textIndent
     */
    layoutProperty_->UpdateTextIndent(DEFAULT_INDENT_SIZE5);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextIndent(), DEFAULT_INDENT_SIZE5);
}

/**
 * @tc.name: testTextIndent018
 * @tc.desc: test testInput text TextIndent
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testTextIndent018, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(WORLD_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set textIndent
     */
    layoutProperty_->UpdateTextIndent(DEFAULT_INDENT_SIZE6);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextIndent(), DEFAULT_INDENT_SIZE6);
}

/**
 * @tc.name: testTextIndent019
 * @tc.desc: test testInput text TextIndent
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testTextIndent019, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(TEXTCASE_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set textIndent
     */
    layoutProperty_->UpdateTextIndent(DEFAULT_INDENT_SIZE);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextIndent(), DEFAULT_INDENT_SIZE);
}

/**
 * @tc.name: testTextIndent020
 * @tc.desc: test testInput text TextIndent
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testTextIndent020, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(TEXTCASE_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set textIndent
     */
    layoutProperty_->UpdateTextIndent(DEFAULT_INDENT_SIZE2);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextIndent(), DEFAULT_INDENT_SIZE2);
}

/**
 * @tc.name: testTextIndent021
 * @tc.desc: test testInput text TextIndent
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testTextIndent021, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(TEXTCASE_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set textIndent
     */
    layoutProperty_->UpdateTextIndent(DEFAULT_INDENT_SIZE3);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextIndent(), DEFAULT_INDENT_SIZE3);
}

/**
 * @tc.name: testTextIndent022
 * @tc.desc: test testInput text TextIndent
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testTextIndent022, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(TEXTCASE_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set textIndent
     */
    layoutProperty_->UpdateTextIndent(DEFAULT_INDENT_SIZE4);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextIndent(), DEFAULT_INDENT_SIZE4);
}

/**
 * @tc.name: testTextIndent023
 * @tc.desc: test testInput text TextIndent
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testTextIndent023, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(TEXTCASE_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set textIndent
     */
    layoutProperty_->UpdateTextIndent(DEFAULT_INDENT_SIZE5);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextIndent(), DEFAULT_INDENT_SIZE5);
}

/**
 * @tc.name: testTextIndent024
 * @tc.desc: test testInput text TextIndent
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testTextIndent024, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: style is Inline
     */
    CreateTextField(TEXTCASE_TEXT, "", [](TextFieldModelNG model) {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
    });

    /**
     * @tc.step: step2. Set textIndent
     */
    layoutProperty_->UpdateTextIndent(DEFAULT_INDENT_SIZE6);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextIndent(), DEFAULT_INDENT_SIZE6);
}

/**
 * @tc.name: testFieldModelNg001
 * @tc.desc: test testInput ModelNg TextInputType
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text area.
     */
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateTextArea(DEFAULT_TEXT_U16, u"");

    /**
     * @tc.step: step2. Set TextInputType
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateTextInputType(TextInputType::UNSPECIFIED);
    textFieldModelNG.SetType(TextInputType::UNSPECIFIED);
    layoutProperty->UpdateTextInputType(TextInputType::EMAIL_ADDRESS);
    textFieldModelNG.SetType(TextInputType::UNSPECIFIED);
    layoutProperty->ResetTextInputType();
    textFieldModelNG.SetType(TextInputType::UNSPECIFIED);
}

/**
 * @tc.name: testFieldModelNg002
 * @tc.desc: test testInput ModelNg SetContentType
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text area.
     */
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateTextArea(DEFAULT_TEXT_U16, u"");

    /**
     * @tc.step: step2. Set SetContentType
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateTextContentType(TextContentType::USER_NAME);
    textFieldModelNG.SetContentType(TextContentType::USER_NAME);
    layoutProperty->UpdateTextContentType(TextContentType::PERSON_FIRST_NAME);
    textFieldModelNG.SetContentType(TextContentType::USER_NAME);
    layoutProperty->ResetTextContentType();
    textFieldModelNG.SetContentType(TextContentType::PERSON_FIRST_NAME);
}

/**
 * @tc.name: testFieldModelNg003
 * @tc.desc: test testInput ModelNg SetPasswordIcon
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text area.
     */
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateTextArea(DEFAULT_TEXT_U16, u"");

    /**
     * @tc.step: step2. Set SetPasswordIcon
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    PasswordIcon passwordIcon;
    textFieldModelNG.SetPasswordIcon(passwordIcon);
    passwordIcon.showResult = HELLO_TEXT;
    passwordIcon.hideResult = HELLO_TEXT;
    textFieldModelNG.SetPasswordIcon(passwordIcon);
    std::function<void()> buildFunc;
    textFieldModelNG.SetCustomKeyboard(std::move(buildFunc), true);
}

/**
 * @tc.name: testFieldModelNg004
 * @tc.desc: test testInput ModelNg SetPlaceholderFont
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text area.
     */
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateTextArea(DEFAULT_TEXT_U16, u"");

    /**
     * @tc.step: step2. Set SetPlaceholderFont
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    Font font;
    textFieldModelNG.SetPlaceholderFont(frameNode, font);
    font.fontSize = Dimension(2);
    font.fontStyle = Ace::FontStyle::NORMAL;
    font.fontWeight = FontWeight::W200;
    std::vector<std::string> families = { "cursive" };
    font.fontFamilies = families;
    textFieldModelNG.SetPlaceholderFont(frameNode, font);
    textFieldModelNG.GetOrCreateController(frameNode);
}

/**
 * @tc.name: testFieldModelNg005
 * @tc.desc: test testInput ModelNg SetTextFieldText
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text area.
     */
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateTextArea(DEFAULT_TEXT_U16, u"");

    /**
     * @tc.step: step2. Set SetTextFieldText
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    textFieldModelNG.SetTextFieldText(frameNode, DEFAULT_TEXT_U16);
    RefPtr<TextFieldPattern> pattern = frameNode->GetPattern<TextFieldPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->contentController_->SetTextValue(TEXTCASE_TEXT_U16);
    textFieldModelNG.SetTextFieldText(frameNode, TEXTCASE_TEXT_U16);
    textFieldModelNG.StopTextFieldEditing(frameNode);
    textFieldModelNG.ResetNumberOfLines(frameNode);
    textFieldModelNG.GetMargin(frameNode);
    textFieldModelNG.GetPadding(frameNode);
    textFieldModelNG.SetDefaultPadding();
    textFieldModelNG.GetPadding(frameNode);
    PaddingProperty margins;
    margins.left = CalcLength(PADDING_FIVE);
    margins.right = CalcLength(PADDING_FIVE);
    margins.top = CalcLength(PADDING_FIVE);
    margins.bottom = CalcLength(PADDING_FIVE);
    textFieldModelNG.SetMargin(frameNode, margins);
    textFieldModelNG.GetMargin(frameNode);
}

/**
 * @tc.name: testFieldModelNg006
 * @tc.desc: test testInput ModelNg
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelNg006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text area.
     */
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateTextArea(DEFAULT_TEXT_U16, u"");

    /**
     * @tc.step: step2. Set Action
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    textFieldModelNG.SetEnterKeyType(TextInputAction::SEARCH);
    CaretStyle caretStyle;
    textFieldModelNG.SetCaretStyle(caretStyle);
    PasswordIcon passwordIcon;
    textFieldModelNG.SetPasswordIcon(frameNode, passwordIcon);
    passwordIcon.showResult = HELLO_TEXT;
    passwordIcon.hideResult = HELLO_TEXT;
    textFieldModelNG.SetPasswordIcon(frameNode, passwordIcon);
    layoutProperty->UpdateTextInputType(TextInputType::UNSPECIFIED);
    textFieldModelNG.SetType(frameNode, TextInputType::UNSPECIFIED);
    layoutProperty->UpdateTextInputType(TextInputType::EMAIL_ADDRESS);
    textFieldModelNG.SetType(frameNode, TextInputType::UNSPECIFIED);
    layoutProperty->ResetTextInputType();
    textFieldModelNG.SetType(frameNode, TextInputType::UNSPECIFIED);
}

/**
 * @tc.name: testFieldModelNg007
 * @tc.desc: test testInput ModelNg
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelNg007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text area.
     */
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateTextArea(DEFAULT_TEXT_U16, u"");

    /**
     * @tc.step: step2. Set Action
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateTextContentType(TextContentType::USER_NAME);
    textFieldModelNG.SetContentType(frameNode, TextContentType::USER_NAME);
    layoutProperty->UpdateTextContentType(TextContentType::PERSON_FIRST_NAME);
    textFieldModelNG.SetContentType(frameNode, TextContentType::USER_NAME);
    layoutProperty->ResetTextContentType();
    textFieldModelNG.SetContentType(frameNode, TextContentType::PERSON_FIRST_NAME);

    BorderWidthProperty borderWidth;
    borderWidth.SetBorderWidth(Dimension(ICON_SIZE, DimensionUnit::VP));
    textFieldModelNG.SetBorderWidth(frameNode, borderWidth);
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(Dimension(ICON_SIZE, DimensionUnit::VP));
    borderRadius.multiValued = false;
    textFieldModelNG.SetBorderRadius(frameNode, borderRadius);
    BorderStyleProperty borderStyle;
    borderStyle.SetBorderStyle(BorderStyle::NONE);
    textFieldModelNG.SetBorderStyle(frameNode, borderStyle);
    BorderColorProperty borderColor;
    borderColor.SetColor(COLOR_DEFAULT);
    textFieldModelNG.SetBorderColor(frameNode, borderColor);
    textFieldModelNG.SetBackBorder();
}

/**
 * @tc.name: testFieldModelNg008
 * @tc.desc: test testInput ModelNg
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelNg008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text area.
     */
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateTextInput(DEFAULT_TEXT_U16, u"");

    /**
     * @tc.step: step2. Set Action
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    textFieldModelNG.SetTextAlign(TextAlign::JUSTIFY);
    std::function<void()> unitFunction;
    textFieldModelNG.SetShowUnit(std::move(unitFunction));
    std::function<void()> unitFunctionAction = [] {};
    textFieldModelNG.SetShowUnit(std::move(unitFunctionAction));
}

/**
 * @tc.name: testFieldModelNg009
 * @tc.desc: test testInput ModelNg
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelNg009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text area.
     */
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateTextArea(DEFAULT_TEXT_U16, u"");

    /**
     * @tc.step: step2. Set Action
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    textFieldModelNG.SetTextAlign(TextAlign::RIGHT);
}

/**
 * @tc.name: testFieldModelNg010
 * @tc.desc: test testInput ModelNg
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelNg010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text area.
     */
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateTextArea(DEFAULT_TEXT_U16, u"");

    /**
     * @tc.step: step2. Set Action
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    textFieldModelNG.SetTextAlign(TextAlign::RIGHT);

    /**
     * @tc.steps: step3. SetWidth.
     */
    TextFieldModelNG::SetWidth(frameNode, "auto");
    TextFieldModelNG::SetWidth(frameNode, "not auto");

    /**
     * @tc.steps: step4. SetMaxLength.
     */
    TextFieldModelNG::SetMaxLength(frameNode, 0);
    TextFieldModelNG::SetMaxLength(frameNode, MAX_LENGTH);
    TextFieldModelNG::ResetPlaceholderColor(frameNode);
    TextFieldModelStatic::SetPlaceholderColor(frameNode, std::make_optional(Color::GRAY));
    TextFieldModelNG::ResetPlaceholderColor(frameNode);
}

/**
 * @tc.name: testFieldModelNg011
 * @tc.desc: test testInput ModelNg
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelNg011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text area.
     */
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateTextArea(DEFAULT_TEXT_U16, u"");

    /**
     * @tc.step: step2. Set Action
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    auto textPaintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    EXPECT_NE(textPaintProperty, nullptr);
    textFieldModelNG.SetTextAlign(TextAlign::RIGHT);

    /**
     * @tc.steps: step3. SetShowCounter.
     */
    TextFieldModelNG::SetMaxLength(frameNode, MAX_LENGTH);
    TextFieldModelNG::SetShowCounter(frameNode, true);
    TextFieldModelNG::SetShowCounter(frameNode, false);
    layoutProperty->ResetMaxLength();
    TextFieldModelNG::SetShowCounter(frameNode, true);
    TextFieldModelNG::SetShowCounter(frameNode, false);
    layoutProperty->UpdateTextInputType(TextInputType::NUMBER_PASSWORD);
    TextFieldModelNG::SetShowCounter(frameNode, true);
    TextFieldModelNG::SetShowCounter(frameNode, false);
    textPaintProperty->UpdateInputStyle(InputStyle::INLINE);
    layoutProperty->UpdateTextInputType(TextInputType::TEXT);
    TextFieldModelNG::SetShowCounter(frameNode, true);
    TextFieldModelNG::SetShowCounter(frameNode, false);
}

/**
 * @tc.name: accessibilityProperty001
 * @tc.desc: test testInput accessibilityProperty
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, accessibilityProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text area.
     */
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateTextArea(DEFAULT_TEXT_U16, u"");

    /**
     * @tc.step: step2. Set Action
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<TextFieldAccessibilityProperty>();
    EXPECT_NE(accessibilityProperty, nullptr);
    layoutProperty->UpdateTextInputType(TextInputType::TEXT);
    EXPECT_EQ(accessibilityProperty->GetTextInputType(), AceTextCategory::INPUT_TYPE_TEXT);
    layoutProperty->UpdateTextInputType(TextInputType::NUMBER);
    EXPECT_EQ(accessibilityProperty->GetTextInputType(), AceTextCategory::INPUT_TYPE_NUMBER);
    layoutProperty->UpdateTextInputType(TextInputType::PHONE);
    EXPECT_EQ(accessibilityProperty->GetTextInputType(), AceTextCategory::INPUT_TYPE_PHONENUMBER);
    layoutProperty->UpdateTextInputType(TextInputType::DATETIME);
    EXPECT_EQ(accessibilityProperty->GetTextInputType(), AceTextCategory::INPUT_TYPE_DATE);
    accessibilityProperty->GetText();
    layoutProperty->UpdateTextInputType(TextInputType::EMAIL_ADDRESS);
    EXPECT_EQ(accessibilityProperty->GetTextInputType(), AceTextCategory::INPUT_TYPE_EMAIL);
    layoutProperty->UpdateTextInputType(TextInputType::VISIBLE_PASSWORD);
    EXPECT_EQ(accessibilityProperty->GetTextInputType(), AceTextCategory::INPUT_TYPE_PASSWORD);
    layoutProperty->UpdateTextInputType(TextInputType::USER_NAME);
    EXPECT_EQ(accessibilityProperty->GetTextInputType(), AceTextCategory::INPUT_TYPE_USER_NAME);
    layoutProperty->UpdateTextInputType(TextInputType::NEW_PASSWORD);
    EXPECT_EQ(accessibilityProperty->GetTextInputType(), AceTextCategory::INPUT_TYPE_NEW_PASSWORD);
    accessibilityProperty->GetText();
    layoutProperty->UpdateTextInputType(TextInputType::BEGIN);
    accessibilityProperty->GetTextInputType();
}

/**
 * @tc.name: accessibilityProperty002
 * @tc.desc: test testInput accessibilityProperty
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, accessibilityProperty002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text area.
     */
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateTextArea(DEFAULT_TEXT_U16, u"");

    /**
     * @tc.step: step2. Set Action
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<TextFieldAccessibilityProperty>();
    EXPECT_NE(accessibilityProperty, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    EXPECT_NE(pattern, nullptr);
    layoutProperty->UpdateTextInputType(TextInputType::TEXT);
    textFieldModelNG.SetCopyOption(CopyOptions::InApp);
    accessibilityProperty->SetSpecificSupportAction();

    layoutProperty->UpdateTextInputType(TextInputType::VISIBLE_PASSWORD);
    textFieldModelNG.SetCopyOption(CopyOptions::None);
    accessibilityProperty->SetSpecificSupportAction();
}

/**
 * @tc.name: testStroke001
 * @tc.desc: test textInput and textArea of the stroke
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testStroke001, TestSize.Level1)
{
    TextFieldModelNG textFieldModelNG;

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    textFieldModelNG.SetStrokeWidth(Dimension(2.0));
    textFieldModelNG.SetStrokeColor(STORKE_COLOR_VALUE_1);

    EXPECT_EQ(layoutProperty->GetStrokeWidth(), Dimension(2.0));
    EXPECT_EQ(layoutProperty->GetStrokeColor(), STORKE_COLOR_VALUE_1);

    textFieldModelNG.ResetStrokeColor();
    EXPECT_EQ(layoutProperty->GetStrokeColor().has_value(), false);
}

/**
 * @tc.name: testFieldModelStatic001
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetLineSpacing(frameNode, std::make_optional(2.0_fp));
    EXPECT_EQ(layoutProperty->GetLineSpacing().value(), 2.0_fp);

    TextFieldModelStatic::SetLineSpacing(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetLineSpacing().has_value());
}

/**
 * @tc.name: testFieldModelStatic002
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic002, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetAdaptMinFontSize(frameNode, std::make_optional(1.0_fp));
    EXPECT_EQ(layoutProperty->GetAdaptMinFontSize().value(), 1.0_fp);

    TextFieldModelStatic::SetAdaptMinFontSize(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetAdaptMinFontSize().has_value());
}

/**
 * @tc.name: testFieldModelStatic003
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic003, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetAdaptMaxFontSize(frameNode, std::make_optional(2.0_fp));
    EXPECT_EQ(layoutProperty->GetAdaptMaxFontSize().value(), 2.0_fp);

    TextFieldModelStatic::SetAdaptMaxFontSize(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetAdaptMaxFontSize().has_value());
}

/**
 * @tc.name: testFieldModelStatic004
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic004, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetHeightAdaptivePolicy(
        frameNode, std::make_optional(TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST));
    EXPECT_EQ(layoutProperty->GetHeightAdaptivePolicy().value(), TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST);

    TextFieldModelStatic::SetHeightAdaptivePolicy(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetHeightAdaptivePolicy().has_value());
}

/**
 * @tc.name: testFieldModelStatic005
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic005, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetTextOverflow(frameNode, std::make_optional(TextOverflow::CLIP));
    EXPECT_EQ(layoutProperty->GetTextOverflow().value(), TextOverflow::CLIP);

    TextFieldModelStatic::SetTextOverflow(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetTextOverflow().has_value());
}

/**
 * @tc.name: testFieldModelStatic006
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic006, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetTextIndent(frameNode, std::make_optional(TEXT_INDENT));
    EXPECT_EQ(layoutProperty->GetTextIndent().value(), TEXT_INDENT);

    TextFieldModelStatic::SetTextIndent(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetTextIndent().has_value());
}

/**
 * @tc.name: testFieldModelStatic007
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic007, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetFontFamily(frameNode, std::make_optional(FONT_FAMILY_VALUE));
    EXPECT_EQ(layoutProperty->GetFontFamily().value(), FONT_FAMILY_VALUE);

    TextFieldModelStatic::SetFontFamily(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetFontFamily().has_value());
}

/**
 * @tc.name: testFieldModelStatic008
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic008, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetCopyOption(frameNode, std::make_optional(CopyOptions::Distributed));
    EXPECT_EQ(layoutProperty->GetCopyOptions().value(), CopyOptions::Distributed);

    TextFieldModelStatic::SetCopyOption(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetCopyOptions().has_value());
}

/**
 * @tc.name: testFieldModelStatic009
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic009, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetLetterSpacing(frameNode, std::make_optional(LETTER_SPACING));
    EXPECT_EQ(layoutProperty->GetLetterSpacing().value(), LETTER_SPACING);

    TextFieldModelStatic::SetLetterSpacing(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetLetterSpacing().has_value());
}

/**
 * @tc.name: testFieldModelStatic010
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic010, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetWordBreak(frameNode, std::make_optional(WordBreak::BREAK_ALL));
    EXPECT_EQ(layoutProperty->GetWordBreak().value(), WordBreak::BREAK_ALL);

    TextFieldModelStatic::SetWordBreak(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetWordBreak().has_value());
}

/**
 * @tc.name: testFieldModelStatic011
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic011, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetLineBreakStrategy(frameNode, std::make_optional(LineBreakStrategy::BALANCED));
    EXPECT_EQ(layoutProperty->GetLineBreakStrategy().value(), LineBreakStrategy::BALANCED);

    TextFieldModelStatic::SetLineBreakStrategy(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetLineBreakStrategy().has_value());
}

/**
 * @tc.name: testFieldModelStatic012
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic012, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto textPaintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    EXPECT_NE(textPaintProperty, nullptr);
    TextFieldModelStatic::SetInputStyle(frameNode, std::make_optional(InputStyle::DEFAULT));
    frameNode->MarkModifyDone();
    EXPECT_EQ(textPaintProperty->GetInputStyle().value(), InputStyle::DEFAULT);

    TextFieldModelStatic::SetInputStyle(frameNode, std::nullopt);
    EXPECT_FALSE(textPaintProperty->GetInputStyle().has_value());
}

/**
 * @tc.name: testFieldModelStatic013
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic013, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetBarState(frameNode, std::make_optional(DisplayMode::ON));
    frameNode->MarkModifyDone();
    EXPECT_EQ(layoutProperty->GetDisplayMode().value(), DisplayMode::ON);

    TextFieldModelStatic::SetBarState(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetDisplayMode().has_value());
}

/**
 * @tc.name: testFieldModelStatic014
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic014, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetTextFieldPlaceHolder(frameNode, std::make_optional(u"placeholder"));
    EXPECT_EQ(layoutProperty->GetPlaceholder().value(), u"placeholder");

    TextFieldModelStatic::SetTextFieldPlaceHolder(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetPlaceholder().has_value());
}

/**
 * @tc.name: testFieldModelStatic015
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic015, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetMaxViewLines(frameNode, std::make_optional(5));
    EXPECT_EQ(layoutProperty->GetMaxViewLines().value(), 5);
}

/**
 * @tc.name: testFieldModelStatic016
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic016, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetNormalMaxViewLines(frameNode, std::make_optional(10));
    EXPECT_EQ(layoutProperty->GetNormalMaxViewLines().value(), 10);
}

/**
 * @tc.name: testFieldModelStatic017
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic017, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateTextInputType(TextInputType::UNSPECIFIED);
    TextFieldModelStatic::SetType(frameNode, std::make_optional(TextInputType::UNSPECIFIED));
    EXPECT_EQ(layoutProperty->GetTextInputType().value(), TextInputType::UNSPECIFIED);

    TextFieldModelStatic::SetType(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetTextInputType().has_value());
}

/**
 * @tc.name: testFieldModelStatic018
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic018, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetContentType(frameNode, std::make_optional(TextContentType::USER_NAME));
    EXPECT_EQ(layoutProperty->GetTextContentType().value(), TextContentType::USER_NAME);

    TextFieldModelStatic::SetContentType(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetTextContentType().has_value());
}

/**
 * @tc.name: testFieldModelStatic019
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic019, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    Font font;
    font.fontSize = Dimension(2);
    TextFieldModelStatic::SetPlaceholderFont(frameNode, std::make_optional(font));
    EXPECT_EQ(layoutProperty->GetPlaceholderFontSizeValue(Dimension(0)), Dimension(2));

    TextFieldModelStatic::SetPlaceholderFont(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetPlaceholderFontSize().has_value());
}

/**
 * @tc.name: testFieldModelStatic020
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic020, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetShowPassword(frameNode, std::make_optional(false));
    EXPECT_EQ(layoutProperty->GetShowPasswordText().value(), false);

    TextFieldModelStatic::SetShowPassword(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetShowPasswordText().has_value());
}

/**
 * @tc.name: testFieldModelStatic021
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic021, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetTextAlign(frameNode, std::make_optional(TextAlign::RIGHT));
    EXPECT_EQ(layoutProperty->GetTextAlign().value(), TextAlign::RIGHT);

    TextFieldModelStatic::SetTextAlign(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetTextAlign().has_value());
}

/**
 * @tc.name: testFieldModelStatic022
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic022, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetTextColor(frameNode, std::make_optional(Color::BLACK));
    EXPECT_EQ(layoutProperty->GetTextColor().value(), Color::BLACK);

    TextFieldModelStatic::SetTextColor(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetTextColor().has_value());
}

/**
 * @tc.name: testFieldModelStatic023
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic023, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetFontStyle(frameNode, std::make_optional(Ace::FontStyle::NORMAL));
    EXPECT_EQ(layoutProperty->GetItalicFontStyle().value(), Ace::FontStyle::NORMAL);

    TextFieldModelStatic::SetFontStyle(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetItalicFontStyle().has_value());
}

/**
 * @tc.name: testFieldModelStatic024
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic024, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetFontSize(frameNode, std::make_optional(Dimension(20)));
    EXPECT_EQ(layoutProperty->GetFontSize().value(), Dimension(20));

    TextFieldModelStatic::SetFontSize(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetFontSize().has_value());
}

/**
 * @tc.name: testFieldModelStatic025
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic025, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto textPaintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    EXPECT_NE(textPaintProperty, nullptr);
    TextFieldModelStatic::SetCaretStyle(frameNode, std::make_optional(DEFAULT_CARET_STYLE));
    EXPECT_EQ(textPaintProperty->GetCursorWidth().value(), DEFAULT_CARET_STYLE.caretWidth.value());

    TextFieldModelStatic::SetCaretStyle(frameNode, std::nullopt);
    EXPECT_FALSE(textPaintProperty->GetCursorWidth().has_value());
}

/**
 * @tc.name: testFieldModelStatic026
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic026, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetPlaceholderColor(frameNode, std::make_optional(Color::GRAY));
    EXPECT_EQ(layoutProperty->GetPlaceholderTextColor().value(), Color::GRAY);

    TextFieldModelStatic::SetPlaceholderColor(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetPlaceholderTextColor().has_value());
}

/**
 * @tc.name: testFieldModelStatic027
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic027, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetFontWeight(frameNode, std::make_optional(FontWeight::W500));
    EXPECT_EQ(layoutProperty->GetFontWeight().value(), FontWeight::W500);

    TextFieldModelStatic::SetFontWeight(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetFontWeight().has_value());
}

/**
 * @tc.name: testFieldModelStatic028
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic028, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetPasswordRules(frameNode, std::make_optional("passwordRules"));
    EXPECT_EQ(layoutProperty->GetPasswordRules().value(), "passwordRules");

    TextFieldModelStatic::SetPasswordRules(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetPasswordRules().has_value());

    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();

    NG::OnCreateMenuCallback onCreate = [](const std::vector<NG::MenuItemParam>&) -> std::vector<MenuOptionsParam> {
        std::vector<NG::MenuOptionsParam> menuParams;
        return menuParams;
    };
    NG::OnMenuItemClickCallback onMenuItemClick = [](const NG::MenuItemParam&) -> bool { return false; };
    TextFieldModelStatic::SetSelectionMenuOptions(frameNode, std::move(onCreate), std::move(onMenuItemClick));
    EXPECT_NE(textFieldPattern->selectOverlay_->onCreateMenuCallback_, nullptr);
    EXPECT_NE(textFieldPattern->selectOverlay_->onMenuItemClick_, nullptr);
}

/**
 * @tc.name: testFieldModelStatic029
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic029, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetShowError(frameNode, std::make_optional(u"error"), true);
    EXPECT_EQ(layoutProperty->GetShowErrorText().value(), true);

    TextFieldModelStatic::SetShowError(frameNode, std::nullopt, false);
    EXPECT_FALSE(layoutProperty->GetShowErrorText().has_value());

    RefPtr<TextFieldPattern> pattern = frameNode->GetPattern<TextFieldPattern>();
    TextFieldModelStatic::GetController(frameNode, std::make_optional(u"placeholder"), std::make_optional(u"value"));
    EXPECT_TRUE(layoutProperty->GetPlaceholder().has_value());
    EXPECT_EQ(pattern->isTextChangedAtCreation_, true);
}

/**
 * @tc.name: testFieldModelStatic030
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic030, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetCounterType(frameNode, std::make_optional(10));
    EXPECT_EQ(layoutProperty->GetSetCounter().value(), 10);

    TextFieldModelStatic::SetCounterType(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetSetCounter().has_value());

    TextFieldModelStatic::SetShowCounterBorder(frameNode, std::make_optional(true));
    EXPECT_EQ(layoutProperty->GetShowHighlightBorder().value(), true);
    TextFieldModelStatic::SetShowCounterBorder(frameNode, std::nullopt);
    EXPECT_EQ(layoutProperty->GetShowHighlightBorder().value(), true);
}

/**
 * @tc.name: testFieldModelStatic031
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic031, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetCancelIconSize(frameNode, std::make_optional(Dimension(24, DimensionUnit::PX)));
    EXPECT_EQ(layoutProperty->GetIconSize().value(), Dimension(24));

    TextFieldModelStatic::SetCancelIconSize(frameNode, std::nullopt);
    EXPECT_TRUE(layoutProperty->GetIconSize().has_value());

    TextFieldModelStatic::SetSelectAllValue(frameNode, std::make_optional(true));
    EXPECT_EQ(layoutProperty->GetSelectAllValue().value(), true);
    TextFieldModelStatic::SetSelectAllValue(frameNode, std::nullopt);
    EXPECT_EQ(layoutProperty->GetSelectAllValue().value(), false);
}

/**
 * @tc.name: testFieldModelStatic032
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic032, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    TextFieldModelStatic::SetCanacelIconSrc(frameNode, "src", bundleName, moduleName);
    EXPECT_EQ(layoutProperty->GetIconSrc().value(), "src");

    TextFieldModelStatic::SetShowUnderline(frameNode, std::make_optional(true));
    EXPECT_EQ(layoutProperty->GetShowUnderline().value(), true);
    TextFieldModelStatic::SetShowUnderline(frameNode, std::nullopt);
    EXPECT_EQ(layoutProperty->GetShowUnderline().value(), false);

    TextFieldModelStatic::SetShowPasswordIcon(frameNode, std::make_optional(false));
    EXPECT_EQ(layoutProperty->GetShowPasswordIcon().value(), false);
    TextFieldModelStatic::SetShowPasswordIcon(frameNode, std::nullopt);
    EXPECT_EQ(layoutProperty->GetShowPasswordIcon().value(), true);
}

/**
 * @tc.name: testFieldModelStatic033
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic033, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetCancelIconColor(frameNode, std::make_optional(Color::GRAY));
    EXPECT_EQ(layoutProperty->GetIconColor().value(), Color::GRAY);

    TextFieldModelStatic::SetCancelIconColor(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetIconColor().has_value());

    std::optional<float> minFontScale = 1.f;
    TextFieldModelStatic::SetMinFontScale(frameNode, minFontScale);
    EXPECT_EQ(layoutProperty->GetMinFontScale().value(), minFontScale);
    TextFieldModelStatic::SetMinFontScale(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetMinFontScale().has_value());

    std::optional<float> maxFontScale = 50.f;
    TextFieldModelStatic::SetMaxFontScale(frameNode, maxFontScale);
    EXPECT_EQ(layoutProperty->GetMaxFontScale().value(), maxFontScale);
    TextFieldModelStatic::SetMaxFontScale(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetMaxFontScale().has_value());
}

/**
 * @tc.name: testFieldModelStatic034
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic034, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetTextDecoration(frameNode, std::make_optional(TextDecoration::UNDERLINE));
    EXPECT_EQ(layoutProperty->GetTextDecorationFirst(), TextDecoration::UNDERLINE);

    TextFieldModelStatic::SetTextDecoration(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetTextDecoration().has_value());

    TextFieldModelStatic::SetEllipsisMode(frameNode, std::make_optional(EllipsisMode::MIDDLE));
    EXPECT_EQ(layoutProperty->GetEllipsisMode().value(), EllipsisMode::MIDDLE);
    TextFieldModelStatic::SetEllipsisMode(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetEllipsisMode().has_value());

    TextFieldModelStatic::SetHalfLeading(frameNode, std::make_optional(false));
    EXPECT_EQ(layoutProperty->GetHalfLeading().value(), false);
    TextFieldModelStatic::SetHalfLeading(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetHalfLeading().has_value());
}

/**
 * @tc.name: testFieldModelStatic035
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic035, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetTextDecorationColor(frameNode, std::make_optional(Color::BLUE));
    EXPECT_EQ(layoutProperty->GetTextDecorationColor().value(), Color::BLUE);

    TextFieldModelStatic::SetTextDecorationColor(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetTextDecorationColor().has_value());

    TextFieldModelStatic::SetEnableHapticFeedback(frameNode, std::make_optional(false));
    RefPtr<TextFieldPattern> textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    EXPECT_EQ(textFieldPattern->GetEnableHapticFeedback(), false);
    TextFieldModelStatic::SetEnableHapticFeedback(frameNode, std::nullopt);
    EXPECT_EQ(textFieldPattern->GetEnableHapticFeedback(), true);

    TextFieldModelStatic::SetEnableAutoFill(frameNode, std::make_optional(false));
    EXPECT_EQ(layoutProperty->GetEnableAutoFill(), false);
    TextFieldModelStatic::SetEnableAutoFill(frameNode, std::nullopt);
    EXPECT_EQ(layoutProperty->GetEnableAutoFill(), true);
}

/**
 * @tc.name: testFieldModelStatic036
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic036, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetTextDecorationStyle(frameNode, std::make_optional(TextDecorationStyle::DOTTED));
    EXPECT_EQ(layoutProperty->GetTextDecorationStyle().value(), TextDecorationStyle::DOTTED);

    TextFieldModelStatic::SetTextDecorationStyle(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetTextDecorationStyle().has_value());

    TextFieldModelStatic::SetSelectionMenuHidden(frameNode, std::make_optional(true));
    EXPECT_EQ(layoutProperty->GetSelectionMenuHidden(), true);
    TextFieldModelStatic::SetSelectionMenuHidden(frameNode, std::nullopt);
    EXPECT_EQ(layoutProperty->GetSelectionMenuHidden(), false);

    TextFieldModelStatic::SetEnablePreviewText(frameNode, std::make_optional(false));
    RefPtr<TextFieldPattern> textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    EXPECT_EQ(textFieldPattern->GetSupportPreviewText(), false);
    TextFieldModelStatic::SetEnablePreviewText(frameNode, std::nullopt);
    EXPECT_EQ(textFieldPattern->GetSupportPreviewText(), true);
}

/**
 * @tc.name: testFieldModelStatic037
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic037, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetLineHeight(frameNode, std::make_optional(Dimension(10)));
    EXPECT_EQ(layoutProperty->GetLineHeight().value(), Dimension(10));

    TextFieldModelStatic::SetLineHeight(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetLineHeight().has_value());

    TextFieldModelStatic::SetStopBackPress(frameNode, std::make_optional(false));
    EXPECT_EQ(layoutProperty->GetStopBackPress().value(), false);

    TextFieldModelStatic::SetStopBackPress(frameNode, std::nullopt);
    EXPECT_EQ(layoutProperty->GetStopBackPress().value(), true);

    PasswordIcon passwordIcon;
    TextFieldModelStatic::SetPasswordIcon(frameNode, std::make_optional(passwordIcon));
    passwordIcon.showResult = HELLO_TEXT;
    passwordIcon.hideResult = HELLO_TEXT;
    TextFieldModelStatic::SetPasswordIcon(frameNode, std::make_optional(passwordIcon));

    TextFieldModelStatic::RequestKeyboardOnFocus(frameNode, std::make_optional(false));
    RefPtr<TextFieldPattern> textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    EXPECT_EQ(textFieldPattern->NeedToRequestKeyboardOnFocus(), false);
    TextFieldModelStatic::RequestKeyboardOnFocus(frameNode, std::nullopt);
    EXPECT_EQ(textFieldPattern->NeedToRequestKeyboardOnFocus(), true);
}

/**
 * @tc.name: TextModelStaticTest001
 * @tc.desc: test SetFontWeight func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest001, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    std::optional<Ace::FontWeight> validWeight  = Ace::FontWeight::W100;
    TextModelStatic::SetFontWeight(frameNode.GetRawPtr(), validWeight);
    EXPECT_FALSE(layoutProperty->GetAdaptMaxFontSize().has_value());
    std::optional<Ace::FontWeight> emptyWeight = std::nullopt;
    TextModelStatic::SetFontWeight(frameNode.GetRawPtr(), emptyWeight);
    EXPECT_FALSE(layoutProperty->GetAdaptMaxFontSize().has_value());
}

/**
 * @tc.name: TextModelStaticTest002
 * @tc.desc: test SetVariableFontWeight func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest002, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    std::optional<int32_t> validValue  = 1;
    TextModelStatic::SetVariableFontWeight(frameNode.GetRawPtr(), validValue);
    EXPECT_FALSE(layoutProperty->GetAdaptMaxFontSize().has_value());
    TextModelStatic::SetVariableFontWeight(frameNode.GetRawPtr(), std::nullopt);
    EXPECT_FALSE(layoutProperty->GetAdaptMaxFontSize().has_value());
}

/**
 * @tc.name: TextModelStaticTest003
 * @tc.desc: test SetEnableVariableFontWeight func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest003, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    std::optional<bool> validValue  = true;
    TextModelStatic::SetEnableVariableFontWeight(frameNode.GetRawPtr(), validValue);
    EXPECT_FALSE(layoutProperty->GetAdaptMaxFontSize().has_value());
    std::optional<bool> emptyValue = std::nullopt;
    TextModelStatic::SetEnableVariableFontWeight(frameNode.GetRawPtr(), emptyValue);
    EXPECT_FALSE(layoutProperty->GetAdaptMaxFontSize().has_value());
}

/**
 * @tc.name: TextModelStaticTest004
 * @tc.desc: test SetMinFontScale func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest004, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    std::optional<float> validValue  = 1.0f;
    TextModelStatic::SetMinFontScale(frameNode.GetRawPtr(), validValue);
    EXPECT_FALSE(layoutProperty->GetAdaptMinFontSize().has_value());
    std::optional<float> emptyValue = std::nullopt;
    TextModelStatic::SetMinFontScale(frameNode.GetRawPtr(), emptyValue);
    EXPECT_FALSE(layoutProperty->GetAdaptMinFontSize().has_value());
}

/**
 * @tc.name: TextModelStaticTest005
 * @tc.desc: test SetMaxFontScale func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest005, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    std::optional<float> validValue  = 1.0f;
    TextModelStatic::SetMaxFontScale(frameNode.GetRawPtr(), validValue);
    EXPECT_FALSE(layoutProperty->GetAdaptMaxFontSize().has_value());
    std::optional<float> emptyValue = std::nullopt;
    TextModelStatic::SetMaxFontScale(frameNode.GetRawPtr(), emptyValue);
    EXPECT_FALSE(layoutProperty->GetAdaptMaxFontSize().has_value());
}

/**
 * @tc.name: TextModelStaticTest006
 * @tc.desc: test SetItalicFontStyle func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest006, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    std::optional<Ace::FontStyle> validValue = Ace::FontStyle::NORMAL;
    TextModelStatic::SetItalicFontStyle(frameNode.GetRawPtr(), validValue);
    EXPECT_FALSE(layoutProperty->GetAdaptMaxFontSize().has_value());
    std::optional<Ace::FontStyle> emptyValue = std::nullopt;
    TextModelStatic::SetItalicFontStyle(frameNode.GetRawPtr(), emptyValue);
    EXPECT_FALSE(layoutProperty->GetAdaptMaxFontSize().has_value());
}

/**
 * @tc.name: TextModelStaticTest007
 * @tc.desc: test SetTextAlign func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest007, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    std::optional<Ace::TextAlign> validValue = Ace::TextAlign::LEFT;
    TextModelStatic::SetTextAlign(frameNode.GetRawPtr(), validValue);
    EXPECT_FALSE(layoutProperty->GetTextIndent().has_value());
    std::optional<Ace::TextAlign> emptyValue = std::nullopt;
    TextModelStatic::SetTextAlign(frameNode.GetRawPtr(), emptyValue);
    EXPECT_FALSE(layoutProperty->GetTextIndent().has_value());
}

/**
 * @tc.name: TextModelStaticTest008
 * @tc.desc: test SetFont func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest008, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    auto validValue = std::make_optional<Font>();
    TextModelStatic::SetFont(frameNode.GetRawPtr(), validValue);
    EXPECT_TRUE(layoutProperty->GetFontFamily().has_value());
    TextModelStatic::SetFont(frameNode.GetRawPtr(), std::nullopt);
    EXPECT_FALSE(layoutProperty->GetFontFamily().has_value());
}

/**
 * @tc.name: TextModelStaticTest009
 * @tc.desc: test SetFontSize func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest009, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    auto dimensionOpt = std::make_optional<Dimension>();
    TextModelStatic::SetFontSize(frameNode.GetRawPtr(), dimensionOpt);
    EXPECT_FALSE(layoutProperty->GetFontFamily().has_value());
    std::optional<Dimension> emptyDimension = std::nullopt;
    TextModelStatic::SetFontSize(frameNode.GetRawPtr(), emptyDimension);
    EXPECT_FALSE(layoutProperty->GetFontFamily().has_value());
}

/**
 * @tc.name: TextModelStaticTest010
 * @tc.desc: test SetLineHeight func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest010, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    auto dimensionOpt = std::make_optional<Dimension>();
    TextModelStatic::SetLineHeight(frameNode.GetRawPtr(), dimensionOpt);
    EXPECT_FALSE(layoutProperty->GetLineBreakStrategy().has_value());
    std::optional<Dimension> emptyDimension = std::nullopt;
    TextModelStatic::SetLineHeight(frameNode.GetRawPtr(), emptyDimension);
    EXPECT_FALSE(layoutProperty->GetLineBreakStrategy().has_value());
}

/**
 * @tc.name: TextModelStaticTest011
 * @tc.desc: test SetLineSpacing func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest011, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    auto dimensionOpt = std::make_optional<Dimension>();
    TextModelStatic::SetLineSpacing(frameNode.GetRawPtr(), dimensionOpt);
    EXPECT_FALSE(layoutProperty->GetLineBreakStrategy().has_value());
    std::optional<Dimension> emptyDimension = std::nullopt;
    TextModelStatic::SetLineSpacing(frameNode.GetRawPtr(), emptyDimension);
    EXPECT_FALSE(layoutProperty->GetLineBreakStrategy().has_value());
}

/**
 * @tc.name: TextModelStaticTest012
 * @tc.desc: test SetTextOverflow func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest012, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    std::optional<Ace::TextOverflow> validValue = Ace::TextOverflow::CLIP;
    TextModelStatic::SetTextOverflow(frameNode.GetRawPtr(), validValue);
    EXPECT_TRUE(layoutProperty->GetTextOverflow().has_value());
    std::optional<Ace::TextOverflow> emptyValue = std::nullopt;
    TextModelStatic::SetTextOverflow(frameNode.GetRawPtr(), emptyValue);
    EXPECT_FALSE(layoutProperty->GetTextOverflow().has_value());
}

/**
 * @tc.name: TextModelStaticTest013
 * @tc.desc: test SetTextDecoration func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest013, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    std::optional<Ace::TextDecoration> validValue = Ace::TextDecoration::NONE;
    TextModelStatic::SetTextDecoration(frameNode.GetRawPtr(), validValue);
    EXPECT_TRUE(layoutProperty->GetTextDecoration().has_value());
    std::optional<Ace::TextDecoration> emptyValue = std::nullopt;
    TextModelStatic::SetTextDecoration(frameNode.GetRawPtr(), emptyValue);
    EXPECT_FALSE(layoutProperty->GetTextDecoration().has_value());
}

/**
 * @tc.name: TextModelStaticTest014
 * @tc.desc: test SetLetterSpacing func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest014, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    auto dimensionOpt = std::make_optional<Dimension>();
    TextModelStatic::SetLetterSpacing(frameNode.GetRawPtr(), dimensionOpt);
    EXPECT_FALSE(layoutProperty->GetLineSpacing().has_value());
    std::optional<Dimension> emptyDimension = std::nullopt;
    TextModelStatic::SetLetterSpacing(frameNode.GetRawPtr(), emptyDimension);
    EXPECT_FALSE(layoutProperty->GetLineSpacing().has_value());
}

/**
 * @tc.name: TextModelStaticTest015
 * @tc.desc: test SetTextDecorationStyle func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest015, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    
    std::optional<Ace::TextDecorationStyle> validValue = Ace::TextDecorationStyle::SOLID;
    TextModelStatic::SetTextDecorationStyle(frameNode.GetRawPtr(), validValue);
    EXPECT_FALSE(layoutProperty->GetItalicFontStyle().has_value());
    std::optional<Ace::TextDecorationStyle> emptyValue = std::nullopt;
    TextModelStatic::SetTextDecorationStyle(frameNode.GetRawPtr(), emptyValue);
    EXPECT_FALSE(layoutProperty->GetItalicFontStyle().has_value());
}

/**
 * @tc.name: TextModelStaticTest016
 * @tc.desc: test SetTextCase func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest016, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    std::optional<Ace::TextCase> validValue = Ace::TextCase::NORMAL;
    TextModelStatic::SetTextCase(frameNode.GetRawPtr(), validValue);
    EXPECT_FALSE(layoutProperty->GetItalicFontStyle().has_value());
    std::optional<Ace::TextCase> emptyValue = std::nullopt;
    TextModelStatic::SetTextCase(frameNode.GetRawPtr(), emptyValue);
    EXPECT_FALSE(layoutProperty->GetItalicFontStyle().has_value());
}

/**
 * @tc.name: TextModelStaticTest017
 * @tc.desc: test SetMaxLines func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest017, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    std::optional<uint32_t> validValue  = 1;
    TextModelStatic::SetMaxLines(frameNode.GetRawPtr(), validValue);
    EXPECT_FALSE(layoutProperty->GetLineSpacing().has_value());
    std::optional<uint32_t> emptyValue  = std::nullopt;
    TextModelStatic::SetMaxLines(frameNode.GetRawPtr(), emptyValue);
    EXPECT_FALSE(layoutProperty->GetLineSpacing().has_value());
}

/**
 * @tc.name: TextModelStaticTest018
 * @tc.desc: test SetAdaptMinFontSize func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest018, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    auto dimensionOpt = std::make_optional<Dimension>();
    TextModelStatic::SetAdaptMinFontSize(frameNode.GetRawPtr(), dimensionOpt);
    EXPECT_TRUE(layoutProperty->GetAdaptMinFontSize().has_value());
    std::optional<Dimension> emptyDimension = std::nullopt;
    TextModelStatic::SetAdaptMinFontSize(frameNode.GetRawPtr(), emptyDimension);
    EXPECT_FALSE(layoutProperty->GetAdaptMinFontSize().has_value());
}

/**
 * @tc.name: TextModelStaticTest019
 * @tc.desc: test SetAdaptMaxFontSize func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest019, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    auto dimensionOpt = std::make_optional<Dimension>();
    TextModelStatic::SetAdaptMaxFontSize(frameNode.GetRawPtr(), dimensionOpt);
    EXPECT_TRUE(layoutProperty->GetAdaptMaxFontSize().has_value());
    std::optional<Dimension> emptyDimension = std::nullopt;
    TextModelStatic::SetAdaptMaxFontSize(frameNode.GetRawPtr(), emptyDimension);
    EXPECT_FALSE(layoutProperty->GetAdaptMaxFontSize().has_value());
}

/**
 * @tc.name: TextModelStaticTest020
 * @tc.desc: test SetFontFamily func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest020, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    auto validValue = std::make_optional(std::vector<std::string>{"16px"});
    TextModelStatic::SetFontFamily(frameNode.GetRawPtr(), validValue);
    EXPECT_TRUE(layoutProperty->GetFontFamily().has_value());
    TextModelStatic::SetFontFamily(frameNode.GetRawPtr(), std::nullopt);
    EXPECT_FALSE(layoutProperty->GetFontFamily().has_value());
}

/**
 * @tc.name: TextModelStaticTest021
 * @tc.desc: test SetCopyOption func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest021, TestSize.Level0)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    std::optional<CopyOptions> validValue = CopyOptions::None;
    TextModelStatic::SetCopyOption(frameNode, validValue);
    EXPECT_FALSE(layoutProperty->GetCopyOptions().has_value());
    std::optional<CopyOptions> emptyValue  = std::nullopt;
    TextModelStatic::SetCopyOption(frameNode, emptyValue);
    EXPECT_FALSE(layoutProperty->GetCopyOptions().has_value());
}

/**
 * @tc.name: TextModelStaticTest022
 * @tc.desc: test SetBaselineOffset func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest022, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    auto dimensionOpt = std::make_optional<Dimension>();
    TextModelStatic::SetBaselineOffset(frameNode.GetRawPtr(), dimensionOpt);
    EXPECT_FALSE(layoutProperty->GetLineSpacing().has_value());
    std::optional<Dimension> emptyDimension = std::nullopt;
    TextModelStatic::SetBaselineOffset(frameNode.GetRawPtr(), emptyDimension);
    EXPECT_FALSE(layoutProperty->GetLineSpacing().has_value());
}

/**
 * @tc.name: TextModelStaticTest023
 * @tc.desc: test SetTextShadow func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest023, TestSize.Level0)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    auto validValue = std::make_optional(std::vector<Shadow>{ Shadow() });
    TextModelStatic::SetTextShadow(frameNode, validValue);
    EXPECT_FALSE(layoutProperty->GetShowErrorText().has_value());
    TextModelStatic::SetTextShadow(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetShowErrorText().has_value());
}

/**
 * @tc.name: TextModelStaticTest024
 * @tc.desc: test SetHeightAdaptivePolicy func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest024, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    auto validValue = TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST;
    TextModelStatic::SetHeightAdaptivePolicy(frameNode.GetRawPtr(), validValue);
    EXPECT_TRUE(layoutProperty->GetHeightAdaptivePolicy().has_value());
    TextModelStatic::SetHeightAdaptivePolicy(frameNode.GetRawPtr(), std::nullopt);
    EXPECT_FALSE(layoutProperty->GetHeightAdaptivePolicy().has_value());
}

/**
 * @tc.name: TextModelStaticTest025
 * @tc.desc: test SetTextIndent func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest025, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    auto dimensionOpt = std::make_optional<Dimension>();
    TextModelStatic::SetTextIndent(frameNode.GetRawPtr(), dimensionOpt);
    EXPECT_TRUE(layoutProperty->GetTextIndent().has_value());
    std::optional<Dimension> emptyDimension = std::nullopt;
    TextModelStatic::SetTextIndent(frameNode.GetRawPtr(), emptyDimension);
    EXPECT_FALSE(layoutProperty->GetTextIndent().has_value());
}

/**
 * @tc.name: TextModelStaticTest026
 * @tc.desc: test SetTextColor func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest026, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    TextModelStatic::SetTextColor(frameNode.GetRawPtr(), std::make_optional(Color::BLUE));
    EXPECT_TRUE(layoutProperty->GetTextColor().has_value());
    TextModelStatic::SetTextColor(frameNode.GetRawPtr(), std::nullopt);
    EXPECT_FALSE(layoutProperty->GetTextColor().has_value());
}

/**
 * @tc.name: TextModelStaticTest027
 * @tc.desc: test SetTextDecorationColor func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest027, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    TextModelStatic::SetTextDecorationColor(frameNode.GetRawPtr(), std::make_optional(Color::BLUE));
    EXPECT_TRUE(layoutProperty->GetTextDecorationColor().has_value());
    TextModelStatic::SetTextDecorationColor(frameNode.GetRawPtr(), std::nullopt);
    EXPECT_FALSE(layoutProperty->GetTextDecorationColor().has_value());
}

/**
 * @tc.name: TextModelStaticTest028
 * @tc.desc: test SetWordBreak func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest028, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    TextModelStatic::SetWordBreak(frameNode.GetRawPtr(), std::make_optional(WordBreak::BREAK_ALL));
    EXPECT_TRUE(layoutProperty->GetWordBreak().has_value());
    TextModelStatic::SetWordBreak(frameNode.GetRawPtr(), std::nullopt);
    EXPECT_FALSE(layoutProperty->GetWordBreak().has_value());
}

/**
 * @tc.name: TextModelStaticTest029
 * @tc.desc: test SetCaretColor func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest029, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    TextModelStatic::SetCaretColor(frameNode.GetRawPtr(), std::make_optional(Color::BLUE));
    EXPECT_FALSE(layoutProperty->GetTextDecorationColor().has_value());
    TextModelStatic::SetCaretColor(frameNode.GetRawPtr(), std::nullopt);
    EXPECT_FALSE(layoutProperty->GetTextDecorationColor().has_value());
}

/**
 * @tc.name: TextModelStaticTest030
 * @tc.desc: test BindSelectionMenu func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest030, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    SelectMenuParam menuParam;
    TextResponseType textResponseType = TextResponseType::LONG_PRESS;
    TextSpanType textSpanType = TextSpanType::TEXT;
    TextModelStatic::BindSelectionMenu(
        frameNode.GetRawPtr(), textSpanType, textResponseType, nullptr, menuParam);
    EXPECT_FALSE(layoutProperty->GetTextDecorationColor().has_value());
}

/**
 * @tc.name: TextModelStaticTest031
 * @tc.desc: test SetSelectedBackgroundColor func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest031, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    TextModelStatic::SetSelectedBackgroundColor(frameNode.GetRawPtr(), std::make_optional(Color::BLUE));
    EXPECT_FALSE(layoutProperty->GetTextDecorationColor().has_value());
    TextModelStatic::SetSelectedBackgroundColor(frameNode.GetRawPtr(), std::nullopt);
    EXPECT_FALSE(layoutProperty->GetTextDecorationColor().has_value());
}

/**
 * @tc.name: TextModelStaticTest032
 * @tc.desc: test SetHalfLeading func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest032, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    TextModelStatic::SetHalfLeading(frameNode.GetRawPtr(), std::make_optional(true));
    EXPECT_FALSE(layoutProperty->GetTextDecorationColor().has_value());
}

/**
 * @tc.name: TextModelStaticTest033
 * @tc.desc: test SetEnableHapticFeedback func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest033, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextModelStatic::SetEnableHapticFeedback(frameNode.GetRawPtr(), std::make_optional(true));
    EXPECT_FALSE(layoutProperty->GetWordBreak().has_value());
}

/**
 * @tc.name: TextModelStaticTest034
 * @tc.desc: test SetSelectionMenuOptions func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest034, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextModelStatic::SetSelectionMenuOptions(frameNode.GetRawPtr(), nullptr, nullptr);
    EXPECT_FALSE(layoutProperty->GetWordBreak().has_value());
}

/**
 * @tc.name: TextModelStaticTest035
 * @tc.desc: test SetLineBreakStrategy func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest035, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextModelStatic::SetLineBreakStrategy(frameNode.GetRawPtr(), std::make_optional(LineBreakStrategy::BALANCED));
    EXPECT_TRUE(layoutProperty->GetLineBreakStrategy().has_value());
    TextModelStatic::SetLineBreakStrategy(frameNode.GetRawPtr(), std::nullopt);
    EXPECT_FALSE(layoutProperty->GetLineBreakStrategy().has_value());
}

/**
 * @tc.name: TextModelStaticTest036
 * @tc.desc: test SetTextSelectableMode func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest036, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextModelStatic::SetTextSelectableMode(
        frameNode.GetRawPtr(), std::make_optional(TextSelectableMode::SELECTABLE_FOCUSABLE));
    EXPECT_FALSE(layoutProperty->GetLineBreakStrategy().has_value());
}

/**
 * @tc.name: TextModelStaticTest037
 * @tc.desc: test SetEllipsisMode func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, TextModelStaticTest037, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextModelStatic::SetEllipsisMode(frameNode.GetRawPtr(), std::make_optional(EllipsisMode::HEAD));
    EXPECT_TRUE(layoutProperty->GetEllipsisMode().has_value());
    TextModelStatic::SetEllipsisMode(frameNode.GetRawPtr(), std::nullopt);
    EXPECT_FALSE(layoutProperty->GetEllipsisMode().has_value());
}

/**
 * @tc.name: ImageSpanViewStatic001
 * @tc.desc: test SetVerticalAlign func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, ImageSpanViewStatic001, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutPropertyPtr<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    ImageSpanViewStatic::SetVerticalAlign(frameNode.GetRawPtr(), std::make_optional(VerticalAlign::BASELINE));
    EXPECT_TRUE(layoutProperty->GetVerticalAlign().has_value());
    ImageSpanViewStatic::SetVerticalAlign(frameNode.GetRawPtr(), std::nullopt);
    EXPECT_FALSE(layoutProperty->GetVerticalAlign().has_value());
}

/**
 * @tc.name: ImageSpanViewStatic002
 * @tc.desc: test SetObjectFit func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, ImageSpanViewStatic002, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    ImageSourceInfo imageInfo;
    void* voidPtr = static_cast<void*>(new char[0]);
    imageInfo.pixmap_ = PixelMap::CreatePixelMap(voidPtr);
    ASSERT_NE(imageInfo.pixmap_, nullptr);
    ImageSpanViewStatic::SetImageSpanSrc(frameNode.GetRawPtr(), imageInfo);
    EXPECT_EQ(pattern->GetSyncLoad(), true);
}
/**
 * @tc.name: ImageSpanViewStatic003
 * @tc.desc: test SetBaselineOffset func
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, ImageSpanViewStatic003, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto imageLayoutProperty = frameNode->GetLayoutPropertyPtr<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    ImageSpanViewStatic::SetBaselineOffset(frameNode.GetRawPtr(), std::make_optional(Dimension(10)));
    EXPECT_FALSE(imageLayoutProperty->GetVerticalAlign().has_value());
    ImageSpanViewStatic::SetBaselineOffset(frameNode.GetRawPtr(), std::nullopt);
    EXPECT_FALSE(imageLayoutProperty->GetVerticalAlign().has_value());
}

/**
 * @tc.name: testFieldModelStatic055
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, testFieldModelStatic038, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetShowError(frameNode, std::make_optional(u"error"), true);
    EXPECT_EQ(layoutProperty->GetShowErrorText().value(), true);
    TextFieldModelStatic::SetShowError(frameNode, std::nullopt, false);
    EXPECT_FALSE(layoutProperty->GetShowErrorText().has_value());
}

/**
 * @tc.name: SetCapitalizationMode001
 * @tc.desc: test search set CapitalizationMode default value
 * @tc.type: FUNC
 */
HWTEST_F(TextInputAreaTest, SetCapitalizationMode001, TestSize.Level1)
{
    TextFieldModelNG textFieldModelNG;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    EXPECT_NE(pattern, nullptr);

    textFieldModelNG.SetCapitalizationMode(AutoCapitalizationMode::NONE);
    EXPECT_EQ(AutoCapitalizationMode::NONE, pattern->GetAutoCapitalizationMode());

    textFieldModelNG.SetAutoCapitalizationMode(frameNode, AutoCapitalizationMode::WORDS);
    EXPECT_EQ(AutoCapitalizationMode::WORDS, pattern->GetAutoCapitalizationMode());
}

} // namespace OHOS::Ace::NG