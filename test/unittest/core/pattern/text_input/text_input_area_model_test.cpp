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

#include <array>
#include <cstddef>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#ifdef WINDOWS_PLATFORM
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "gtest/gtest.h"
#include <unicode/uversion.h>
#include <unicode/putil.h>
#include <unicode/uclean.h>

#define private public
#define protected public

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_data_detector_mgr.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/string_utils.h"
#include "base/utils/type_definition.h"
#include "core/common/ace_application_info.h"
#include "core/common/ai/data_detector_mgr.h"
#include "core/common/ime/constant.h"
#include "core/common/ime/text_editing_value.h"
#include "core/common/ime/text_input_action.h"
#include "core/common/ime/text_input_type.h"
#include "core/common/ime/text_selection.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/scroll/scroll_bar_theme.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components/theme/theme_manager.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_event_hub.h"
#include "core/components_ng/pattern/text_field/text_input_response_area.h"
#include "core/event/key_event.h"
#include "core/event/touch_event.h"
#include "core/gestures/gesture_info.h"
#include "core/components/common/properties/text_style_parser.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr double ICON_SIZE = 24;
constexpr double ICON_HOT_ZONE_SIZE = 40;
constexpr double FONT_SIZE = 16;
constexpr int32_t DEFAULT_NODE_ID = 1;
constexpr int32_t MIN_PLATFORM_VERSION = 10;
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
    eventHub_ = frameNode_->GetEventHub<TextFieldEventHub>();
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
} // namespace OHOS::Ace::NG