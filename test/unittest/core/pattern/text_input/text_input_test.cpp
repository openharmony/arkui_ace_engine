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

#include <array>
#include <cstddef>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

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
#include "core/event/key_event.h"
#include "core/event/touch_event.h"
#include "core/gestures/gesture_info.h"

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
constexpr int32_t MAX_BACKWARD_NUMBER = 30;
constexpr int32_t MAX_FORWARD_NUMBER = 30;
constexpr uint32_t DEFAULT_MAX_LINES = 1;
constexpr uint32_t DEFAULT_MAX_LENGTH = 30;
constexpr int32_t MIN_PLATFORM_VERSION = 10;
constexpr int32_t WORD_LIMIT_LEN = 5;
constexpr int32_t WORD_LIMIT_RETURN = 2;
constexpr int32_t BEYOND_LIMIT_RETURN = 4;
constexpr int32_t DEFAULT_RETURN_VALUE = -1;
const std::string DEFAULT_TEXT = "abcdefghijklmnopqrstuvwxyz";
const std::string HELLO_TEXT = "hello";
const std::string DEFAULT_PLACE_HOLDER = "please input text here";
const std::string LOWERCASE_FILTER = "[a-z]";
const std::string NUMBER_FILTER = "^[0-9]*$";
const Color DEFAULT_PLACE_HODER_COLOR = Color::RED;
const Color DEFAULT_SELECTED_BACKFROUND_COLOR = Color::BLUE;
const Color DEFAULT_CARET_COLOR = Color::BLACK;
const Color DEFAULT_TEXT_COLOR = Color::BLACK;
const Dimension DEFAULT_FONT_SIZE = Dimension(16, DimensionUnit::VP);
const FontWeight DEFAULT_FONT_WEIGHT = FontWeight::W500;
const std::string DEFAULT_INPUT_FILTER = "[a-z]";
const InputStyle DEFAULT_INPUT_STYLE = InputStyle::INLINE;
const CopyOptions DEFAULT_COPY_OPTIONS = CopyOptions::InApp;
const TextAlign DEFAULT_TEXT_ALIGN = TextAlign::LEFT;
const CaretStyle DEFAULT_CARET_STYLE = { Dimension(3, DimensionUnit::VP) };
const OHOS::Ace::DisplayMode DEFAULT_DISPLAY_MODE = OHOS::Ace::DisplayMode::AUTO;
const TextInputAction DEFAULT_ENTER_KEY_TYPE = TextInputAction::BEGIN;
template<typename CheckItem, typename Expected>
struct TestItem {
    CheckItem item;
    Expected expected;
    std::string error;
    TestItem(CheckItem checkItem, Expected expectedValue, std::string message = "")
        : item(checkItem), expected(expectedValue), error(std::move(message))
    {}
    TestItem() = default;
};
struct ExpectParagraphParams {
    float height = 50.f;
    float longestLine = 460.f;
    float maxWidth = 460.f;
    size_t lineCount = 1;
    bool firstCalc = true;
    bool secondCalc = true;
};
constexpr float CONTEXT_WIDTH_VALUE = 300.0f;
constexpr float CONTEXT_HEIGHT_VALUE = 150.0f;
} // namespace

class TextInputBase : public TestNG {
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

void TextInputBase::SetUpTestSuite()
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

void TextInputBase::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
    MockParagraph::TearDown();
}

void TextInputBase::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
}

void TextInputBase::ExpectCallParagraphMethods(ExpectParagraphParams params)
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

void TextInputBase::CreateTextField(
    const std::string& text, const std::string& placeHolder, const std::function<void(TextFieldModelNG&)>& callback)
{
    auto* stack = ViewStackProcessor::GetInstance();
    stack->StartGetAccessRecordingFor(DEFAULT_NODE_ID);
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateTextInput(placeHolder, text);
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

void TextInputBase::GetFocus()
{
    auto focushHub = pattern_->GetFocusHub();
    focushHub->currentFocus_ = true;
    pattern_->HandleFocusEvent();
    FlushLayoutTask(frameNode_);
}

class TextInputCursorTest : public TextInputBase {};
class TextFieldControllerTest : public TextInputBase {};
class TextFieldKeyEventTest : public TextInputBase {};
class TextFiledAttrsTest : public TextInputBase {};
class TextFieldUXTest : public TextInputBase {
protected:
    static void InitAdjustObject(MockDataDetectorMgr& mockDataDetectorMgr);
};

void TextFieldUXTest::InitAdjustObject(MockDataDetectorMgr& mockDataDetectorMgr)
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
HWTEST_F(TextFiledAttrsTest, LayoutProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default attrs
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetWidthAuto(true);
        model.SetType(TextInputType::TEXT);
        model.SetPlaceholderColor(DEFAULT_PLACE_HODER_COLOR);
        model.SetTextColor(DEFAULT_TEXT_COLOR);
        model.SetEnterKeyType(DEFAULT_ENTER_KEY_TYPE);
        model.SetTextAlign(DEFAULT_TEXT_ALIGN);
        model.SetCaretColor(DEFAULT_CARET_COLOR);
        model.SetCaretStyle(DEFAULT_CARET_STYLE);
        model.SetSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR);
        model.SetMaxLength(DEFAULT_MAX_LENGTH);
        model.SetMaxLines(DEFAULT_MAX_LINES);
        model.SetFontSize(DEFAULT_FONT_SIZE);
        model.SetFontWeight(DEFAULT_FONT_WEIGHT);
        model.SetTextColor(DEFAULT_TEXT_COLOR);
        model.SetInputFilter(DEFAULT_INPUT_FILTER, nullptr);
        model.SetCopyOption(DEFAULT_COPY_OPTIONS);
        model.SetBarState(DEFAULT_DISPLAY_MODE);
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
        model.SetShowUnderline(true);
        model.SetSelectAllValue(true);
        model.SetShowCounterBorder(true);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the corresponding JSON
     */
    auto json = JsonUtil::Create(true);
    pattern_->ToJsonValue(json);
    EXPECT_EQ(json->GetString("text"), DEFAULT_TEXT.c_str());
    EXPECT_EQ(json->GetString("type"), "InputType.Normal");
    EXPECT_EQ(json->GetString("caretColor"), "#FF000000");
    EXPECT_EQ(json->GetString("placeholderColor"), "#FFFF0000");
    EXPECT_EQ(json->GetString("textAlign"), "TextAlign.Left");
    EXPECT_EQ(json->GetString("enterKeyType"), "EnterKeyType.Done");
    EXPECT_EQ(json->GetString("maxLength"), "30");
    EXPECT_EQ(json->GetString("inputFilter"), "[a-z]");
    EXPECT_EQ(json->GetString("copyOption"), "CopyOptions.InApp");
    EXPECT_EQ(json->GetString("style"), "TextInputStyle.Inline");
    EXPECT_EQ(json->GetString("maxLines"), "3");
    EXPECT_EQ(json->GetString("barState"), "BarState.AUTO");
    json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
    EXPECT_EQ(json->GetString("caretPosition"), "");
    EXPECT_TRUE(json->GetBool("showUnderline"));
    EXPECT_TRUE(json->GetBool("selectAll"));
}

/**
 * @tc.name: CaretPosition001
 * @tc.desc: Test caret position on TextFieldModelNG::CreateNode.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCursorTest, CaretPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default text and placeholder
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.expected: Current caret position is end of text
     */
    EXPECT_EQ(pattern_->GetCaretIndex(), static_cast<int>(DEFAULT_TEXT.size()));

    /**
     * @tc.steps: Changed new text and remeasure and layout
     */
    pattern_->InsertValue("new");
    FlushLayoutTask(frameNode_);

    /**
     * @tc.expected: Current caret position is end of text
     */
    EXPECT_EQ(pattern_->GetCaretIndex(), static_cast<int>(DEFAULT_TEXT.size() + 3));
}

/**
 * @tc.name: CaretPosition002
 * @tc.desc: Test caret position on SetType.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCursorTest, CaretPosition002, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default text and placeholder and set input type
     */
    std::string text = "openharmony@huawei.com+*0123456789";
    std::vector<TestItem<TextInputType, int32_t>> testItems;
    testItems.emplace_back(TextInputType::TEXT, text.length(), "TextInputType::TEXT");
    testItems.emplace_back(TextInputType::NUMBER, 10, "TextInputType::NUMBER");
    testItems.emplace_back(TextInputType::PHONE, 12, "TextInputType::PHONE");
    testItems.emplace_back(TextInputType::EMAIL_ADDRESS, text.length() - 2, "TextInputType::EMAIL_ADDRESS");
    testItems.emplace_back(TextInputType::VISIBLE_PASSWORD, text.length(), "TextInputType::VISIBLE_PASSWORD");
    testItems.emplace_back(TextInputType::NUMBER_PASSWORD, 10, "TextInputType::NUMBER_PASSWORD");
    testItems.emplace_back(TextInputType::SCREEN_LOCK_PASSWORD, text.length(), "TextInputType::SCREEN_LOCK_PASSWORD");

    /**
     * @tc.expected: Check if the text filter rules for the input box are compliant
     */
    for (const auto& testItem : testItems) {
        CreateTextField(text, "", [testItem](TextFieldModelNG& model) { model.SetType(testItem.item); });
        auto errorMessage = "InputType is " + testItem.error + ", text is " + pattern_->GetTextValue();
        EXPECT_EQ(pattern_->GetCaretIndex(), testItem.expected) << errorMessage;
        TearDown();
    }
}

/**
 * @tc.name: CaretPosition003
 * @tc.desc: Test caret position on SetCaretPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCursorTest, CaretPosition003, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default text
     * @tc.expected: Cursor movement position matches the actual position
     */
    CreateTextField(DEFAULT_TEXT);
    auto controller = pattern_->GetTextFieldController();
    controller->CaretPosition(static_cast<int>(DEFAULT_TEXT.size() - 2));
    EXPECT_EQ(pattern_->GetCaretIndex(), static_cast<int>(DEFAULT_TEXT.size() - 2));
}

/**
 * @tc.name: CaretPosition004
 * @tc.desc: Test caret position on SetMaxLength
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCursorTest, CaretPosition004, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default text and placeholder
     * @tc.expected: Cursor movement position matches the actual position
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG& model) { model.SetMaxLength(DEFAULT_TEXT.size() - 2); });
    auto controller = pattern_->GetTextFieldController();
    controller->CaretPosition(static_cast<int>(DEFAULT_TEXT.size() - 2));
    EXPECT_EQ(pattern_->GetCaretIndex(), static_cast<int>(DEFAULT_TEXT.size() - 2));
}

/**
 * @tc.name: CaretPosition005
 * @tc.desc: Test caret position on SetInputFilter.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCursorTest, CaretPosition005, TestSize.Level1)
{
    /**
     * @tc.steps: Initialize text and filter patterns
     */
    std::string text = "abcdefghABCDEFG0123456789";
    std::vector<TestItem<std::string, int32_t>> testItems;
    testItems.emplace_back("", StringUtils::ToWstring(text).length());
    testItems.emplace_back("[0-9]", 10);
    testItems.emplace_back("[A-Z]", 7);
    testItems.emplace_back("[a-z]", 8);

    /**
     * @tc.expected: Check if the text filter patterns for the input box are compliant
     */
    for (const auto& testItem : testItems) {
        CreateTextField(
            text, "", [testItem](TextFieldModelNG& model) { model.SetInputFilter(testItem.item, nullptr); });
        auto errorMessage = "InputType is " + testItem.item + ", text is " + pattern_->GetTextValue();
        EXPECT_EQ(pattern_->GetCaretIndex(), testItem.expected) << errorMessage;
        TearDown();
    }
}

/**
 * @tc.name: CaretPosition005
 * @tc.desc: Test input string at the cursor position
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCursorTest, CaretPosition006, TestSize.Level1)
{
    /**
     * @tc.steps: Initialize text input and get select controller, update caret position and insert value
     */
    CreateTextField(DEFAULT_TEXT);

    auto controller = pattern_->GetTextSelectController();
    controller->UpdateCaretIndex(2);
    pattern_->InsertValue("new");
    FlushLayoutTask(frameNode_);

    /**
     * @tc.expected: Check if the text and cursor position are correct
     */
    EXPECT_EQ(pattern_->GetTextValue(), "abnewcdefghijklmnopqrstuvwxyz");
    EXPECT_EQ(controller->GetCaretIndex(), 5);
}

/**
 * @tc.name: CaretPosition006
 * @tc.desc: Test stop edting input mode
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCursorTest, CaretPosition007, TestSize.Level1)
{
    /**
     * @tc.steps: Initialize text input node
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.expected: The cursor is neither blinking nor visible when unfocused
     */
    EXPECT_FALSE(pattern_->GetCursorVisible());

    /**
     * @tc.steps: Manually trigger focus and perform measure and layout again
     * @tc.expected: Check if the cursor is twinking
     */
    GetFocus();
    EXPECT_TRUE(pattern_->GetCursorVisible());

    /**
     * @tc.steps: Get text filed controller and stop editing
     */
    auto controller = pattern_->GetTextFieldController();
    controller->StopEditing();
    FlushLayoutTask(frameNode_);

    /**
     * @tc.expected: Check if the cursor stop twinking
     */
    EXPECT_FALSE(pattern_->GetCursorVisible());
}

/**
 * @tc.name: OnTextChangedListenerCaretPosition001
 * @tc.desc: Test the soft keyboard interface
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCursorTest, OnTextChangedListenerCaretPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: Initialize text input node and call text changed listener update edting value
     */
    CreateTextField(DEFAULT_TEXT);

    GetFocus();
    TextEditingValue value;
    TextSelection selection;
    value.text = "new text";
    selection.baseOffset = value.text.length();
    value.selection = selection;
    pattern_->UpdateEditingValue(std::make_shared<TextEditingValue>(value));
    FlushLayoutTask(frameNode_);

    /**
     * @tc.expected: Check if the new text and cursor position are correct
     */
    EXPECT_EQ(pattern_->GetTextValue().compare("new text"), 0);
    EXPECT_EQ(pattern_->GetCaretIndex(), static_cast<int>(value.text.length()));
}

/**
 * @tc.name: OnTextChangedListenerCaretPosition002
 * @tc.desc: Test the soft keyboard interface
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCursorTest, OnTextChangedListenerCaretPosition002, TestSize.Level1)
{
    /**
     * @tc.steps: Initialize text input node and call delete backward
     */
    CreateTextField(DEFAULT_TEXT);

    GetFocus();
    pattern_->DeleteBackward(5);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.expected: Check if the new text and cursor position are correct
     */
    EXPECT_EQ(pattern_->GetTextValue().compare("abcdefghijklmnopqrstu"), 0) << "Text is " + pattern_->GetTextValue();
    EXPECT_EQ(pattern_->GetCaretIndex(), static_cast<int>(DEFAULT_TEXT.length() - 5));

    /**
     * @tc.steps: Move the cursor and then delete text
     */
    auto textFiledController = pattern_->GetTextFieldController();
    textFiledController->CaretPosition(5);
    pattern_->DeleteBackward(5);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.expected: Check if the new text and cursor position are correct
     */
    EXPECT_EQ(pattern_->GetTextValue().compare("fghijklmnopqrstu"), 0) << "Text is " + pattern_->GetTextValue();
    EXPECT_EQ(pattern_->GetCaretIndex(), 0);

    /**
     * @tc.steps: Trigger a backspace key press that exceeds the length of the text
     */
    pattern_->DeleteBackward(MAX_BACKWARD_NUMBER);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.expected: Check if the new text and cursor position are correct
     */
    EXPECT_EQ(pattern_->GetTextValue().compare("fghijklmnopqrstu"), 0) << "Text is " + pattern_->GetTextValue();
    EXPECT_EQ(pattern_->GetCaretIndex(), 0);
}

/**
 * @tc.name: OnTextChangedListenerCaretPosition003
 * @tc.desc: Test the soft keyboard interface
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCursorTest, OnTextChangedListenerCaretPosition003, TestSize.Level1)
{
    /**
     * @tc.steps: Initialize insert text and expected values
     */
    CreateTextField(DEFAULT_TEXT);

    GetFocus();
    pattern_->DeleteForward(5);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.expected: Check if the new text and cursor position are correct
     */
    EXPECT_EQ(pattern_->GetTextValue().compare(DEFAULT_TEXT), 0);
    EXPECT_EQ(pattern_->GetCaretIndex(), static_cast<int>(DEFAULT_TEXT.length()));

    /**
     * @tc.steps: Move the cursor and then delete text forward.
     */
    auto textFiledController = pattern_->GetTextFieldController();
    textFiledController->CaretPosition(5);
    pattern_->DeleteForward(MAX_FORWARD_NUMBER);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.expected: Check if the new text and cursor position are correct
     */
    EXPECT_EQ(pattern_->GetTextValue().compare("abcde"), 0) << "Text is " + pattern_->GetTextValue();
    EXPECT_EQ(pattern_->GetCaretIndex(), 5) << "Caret position is " + std::to_string(pattern_->GetCaretIndex());
}

/**
 * @tc.name: OnTextChangedListenerCaretPosition004
 * @tc.desc: Test the soft keyboard interface
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCursorTest, OnTextChangedListenerCaretPosition004, TestSize.Level1)
{
    /**
     * @tc.steps: Initialize insert text and expected values when 'IsSelected() = false'
     */
    CreateTextField(DEFAULT_TEXT, DEFAULT_PLACE_HOLDER);
    pattern_->InsertValue("abc");
    FlushLayoutTask(frameNode_);

    /**
     * @tc.expected: Check if the new text and cursor position are correct
     */
    EXPECT_EQ(pattern_->GetTextValue().compare(DEFAULT_TEXT + "abc"), 0);
    EXPECT_EQ(pattern_->GetCaretIndex(), DEFAULT_TEXT.length() + 3);

    /**
     * @tc.steps: Move the cursor and then insert text forward.
     */
    auto textFiledController = pattern_->GetTextFieldController();
    textFiledController->CaretPosition(0);
    pattern_->InsertValue("abcde");
    FlushLayoutTask(frameNode_);

    /**
     * @tc.expected: Check if the new text and cursor position are correct
     */
    EXPECT_EQ(pattern_->GetTextValue().compare("abcde" + DEFAULT_TEXT + "abc"), 0);
    EXPECT_EQ(pattern_->GetCaretIndex(), 5);
}

/**
 * @tc.name: OnTextChangedListenerCaretPosition005
 * @tc.desc: Test the soft keyboard interface
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCursorTest, OnTextChangedListenerCaretPosition005, TestSize.Level1)
{
    /**
     * @tc.steps: Initialize insert text and expected values
     */
    CreateTextField(DEFAULT_TEXT, DEFAULT_PLACE_HOLDER);
    int32_t start = 5;
    int32_t end = 10;
    pattern_->HandleSetSelection(start, end, false);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.expected: Check if the new handle positions are correct
     */
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, start);
    EXPECT_EQ(pattern_->selectController_->GetSecondHandleInfo().index, end)
        << "Second index is " + std::to_string(pattern_->selectController_->GetSecondHandleInfo().index);
}

/**
 * @tc.name: OnTextChangedListenerCaretPosition006
 * @tc.desc: Test the soft keyboard interface
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCursorTest, OnTextChangedListenerCaretPosition006, TestSize.Level1)
{
    /**
     * @tc.steps: Initialize insert text and expected values
     */
    CreateTextField(DEFAULT_TEXT, DEFAULT_PLACE_HOLDER);
    std::vector<std::int32_t> action = {
        ACTION_SELECT_ALL,
        ACTION_CUT,
        ACTION_COPY,
        ACTION_PASTE,
    };
    pattern_->HandleExtendAction(action[0]);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.expected: Check if the new handle positions are correct
     */
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, 0);
    EXPECT_EQ(pattern_->selectController_->GetCaretRect().GetX(), 26);
    EXPECT_EQ(pattern_->selectController_->GetSecondHandleInfo().index, 26)
        << "Second index is " + std::to_string(pattern_->selectController_->GetSecondHandleInfo().index);

    /**
     * @tc.steps: Move the handles and then cut text snippet.
     */
    int32_t start = 5;
    int32_t end = 10;
    pattern_->HandleSetSelection(start, end, false);
    pattern_->HandleExtendAction(action[1]);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.expected: Check if the new handle positions are correct
     * Cut data hasn't simulated
     */
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, 5);
    EXPECT_EQ(pattern_->selectController_->GetSecondHandleInfo().index, 5)
        << "Second index is " + std::to_string(pattern_->selectController_->GetSecondHandleInfo().index);
    EXPECT_EQ(pattern_->GetTextSelectController()->GetCaretIndex(), 5);
}

/**
 * @tc.name: OnTextChangedListenerCaretPosition007
 * @tc.desc: Test the soft keyboard interface
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCursorTest, OnTextChangedListenerCaretPosition007, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Initialize text input and Move the handles and then cut text snippet.
     */
    int32_t start = 5;
    int32_t end = 10;
    std::string expectStr = "fghij";
    std::vector<std::int32_t> action = {
        ACTION_SELECT_ALL,
        ACTION_CUT,
        ACTION_COPY,
        ACTION_PASTE,
    };
    auto callback = [expectStr](const std::string& str) { EXPECT_EQ(expectStr, str); };
    CreateTextField(DEFAULT_TEXT, DEFAULT_PLACE_HOLDER, [&](TextFieldModel& model) { model.SetOnCut(callback); });
    pattern_->HandleSetSelection(start, end, false);
    pattern_->HandleExtendAction(action[1]);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.expected: Check if the new handle positions are correct
     *               Verify the cut data
     */
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, start);
    EXPECT_EQ(pattern_->selectController_->GetSecondHandleInfo().index, start)
        << "Second index is " + std::to_string(pattern_->selectController_->GetSecondHandleInfo().index);
    EXPECT_EQ(pattern_->GetTextSelectController()->GetCaretIndex(), start);
    EXPECT_EQ(pattern_->contentController_->GetTextValue().compare("abcdeklmnopqrstuvwxyz"), 0);
}

/**
 * @tc.name: OnTextChangedListenerCaretPosition008
 * @tc.desc: Test the soft keyboard interface
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCursorTest, OnTextChangedListenerCaretPosition008, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Initialize text input and Move the handles and then cut text snippet.
     */
    int32_t start = 5;
    int32_t end = 10;
    std::string expectStr = "fghij";
    std::vector<std::int32_t> action = {
        ACTION_SELECT_ALL,
        ACTION_CUT,
        ACTION_COPY,
        ACTION_PASTE,
    };
    auto onCopy = [expectStr](const std::string& str) { EXPECT_EQ(expectStr, str); };
    auto onPaste = [expectStr](const std::string& str) { EXPECT_EQ(expectStr, str); };
    auto onPasteWithEvent = [expectStr](const std::string& str, NG::TextCommonEvent& event) {
        EXPECT_EQ(expectStr, str); };
    CreateTextField(DEFAULT_TEXT, DEFAULT_PLACE_HOLDER, [&](TextFieldModel& model) -> void {
        model.SetOnCopy(onCopy);
        model.SetOnPaste(onPaste);
        model.SetOnPasteWithEvent(onPasteWithEvent);
    });

    /**
     * @tc.steps: Move the handles and then cut text snippet.
     *            Verify the copy and paste data.
     */
    pattern_->HandleSetSelection(start, end, false);
    pattern_->HandleExtendAction(action[2]);
    pattern_->HandleExtendAction(action[3]);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTextValue().compare("abcdefghijfghijklmnopqrstuvwxyz"), 0)
        << "Text is " + pattern_->GetTextValue();
}

/**
 * @tc.name: OnHandleMove001
 * @tc.desc: Test the clip board interface
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCursorTest, OnHandleMove001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Initialize text input and Move the handles and then do handle selection.
     */
    int32_t start = 5;
    int32_t end = 10;
    std::vector<CaretMoveIntent> select = { CaretMoveIntent::Left, CaretMoveIntent::Right, CaretMoveIntent::Up,
        CaretMoveIntent::Down };
    CreateTextField(DEFAULT_TEXT, DEFAULT_PLACE_HOLDER);

    /**
     * @tc.steps: Move the handles and selection left.
     *            Verify the selection data.
     */
    pattern_->HandleSetSelection(start, end, false);
    pattern_->HandleSelect(select[0]);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, start);
    EXPECT_EQ(pattern_->selectController_->GetSecondHandleInfo().index, end - 1);

    /**
     * @tc.steps: Move the handles and selection right.
     *            Verify the selection data.
     */
    pattern_->HandleSetSelection(start, end, false);
    pattern_->HandleSelect(select[1]);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, start);
    EXPECT_EQ(pattern_->selectController_->GetSecondHandleInfo().index, end + 1);
}

/**
 * @tc.name: OnHandleMove002
 * @tc.desc: Test the clip board interface
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCursorTest, OnHandleMove002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Initialize text input and Move the handles and then do handle selection.
     */
    int32_t start = 5;
    int32_t end = 10;
    std::vector<CaretMoveIntent> select = { CaretMoveIntent::Left, CaretMoveIntent::Right, CaretMoveIntent::Up,
        CaretMoveIntent::Down };
    CreateTextField(DEFAULT_TEXT, DEFAULT_PLACE_HOLDER);

    /**
     * @tc.steps: Move the handles and selection up.
     *            Verify the selection data.
     */
    EXPECT_FALSE(pattern_->IsTextArea());
    pattern_->HandleSetSelection(start, end, false);
    pattern_->HandleSelect(select[2]);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, start);
    EXPECT_EQ(pattern_->selectController_->GetSecondHandleInfo().index, end);

    /**
     * @tc.steps: Move the handles and selection down.
     *            Verify the selection data.
     */
    EXPECT_FALSE(pattern_->IsTextArea());
    pattern_->HandleSetSelection(start, end, false);
    pattern_->HandleSelect(select[3]);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, start);
    EXPECT_EQ(pattern_->selectController_->GetSecondHandleInfo().index, end);
}

/**
 * @tc.name: OnHandleMove003
 * @tc.desc: Test the clip board interface
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCursorTest, OnHandleMove003, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Initialize text input and Move the handles and then do handle selection.
     */
    CreateTextField(DEFAULT_TEXT, DEFAULT_PLACE_HOLDER);

    /**
     * @tc.steps: Move the handles and selection left word.
     *            Verify the selection data.
     */
    auto textFiledController = pattern_->GetTextFieldController();
    textFiledController->CaretPosition(5);
    pattern_->HandleSelectionLeftWord();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, 5);
    EXPECT_EQ(pattern_->selectController_->GetSecondHandleInfo().index, 0);

    /**
     * @tc.steps: Move the handles and selection right word.
     *            Verify the selection data.
     */
    pattern_->HandleSelectionRightWord();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, 5);
    EXPECT_EQ(pattern_->selectController_->GetSecondHandleInfo().index, 21);
}

/**
 * @tc.name: OnHandleMove004
 * @tc.desc: Test the clip board interface
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCursorTest, OnHandleMove004, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Initialize text input and Move the handles and then do handle selection.
     */
    std::vector<CaretMoveIntent> select = { CaretMoveIntent::LeftWord, CaretMoveIntent::RightWord,
        CaretMoveIntent::Home, CaretMoveIntent::End };
    CreateTextField(DEFAULT_PLACE_HOLDER, DEFAULT_PLACE_HOLDER);

    /**
     * @tc.steps: Move the handles and selection leftword "please".
     *            Verify the selection data.
     */
    pattern_->HandleSetSelection(6, 6, false);
    pattern_->HandleSelect(select[0]);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, 6);
    EXPECT_EQ(pattern_->selectController_->GetSecondHandleInfo().index, 0);

    /**
     * @tc.steps: Move the handles and selection rightword "input".
     *            Verify the selection data.
     */
    pattern_->HandleSetSelection(7, 7, false);
    pattern_->HandleSelect(select[1]);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, 7);
    EXPECT_EQ(pattern_->selectController_->GetSecondHandleInfo().index, 13);
}

/**
 * @tc.name: OnHandleMove005
 * @tc.desc: Test the clip board interface
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCursorTest, OnHandleMove005, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Initialize text input and Move the handles and then do handle selection.
     */
    int32_t start = 6;
    int32_t end = 6;
    std::vector<CaretMoveIntent> select = { CaretMoveIntent::LeftWord, CaretMoveIntent::RightWord,
        CaretMoveIntent::Home, CaretMoveIntent::End };
    CreateTextField(DEFAULT_PLACE_HOLDER, DEFAULT_PLACE_HOLDER);

    /**
     * @tc.steps: Move the handles and selection home.
     *            Verify the selection data.
     */
    pattern_->HandleSetSelection(start, end, false);
    pattern_->HandleSelect(select[2]);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, start);
    EXPECT_EQ(pattern_->selectController_->GetSecondHandleInfo().index, 0);

    /**
     * @tc.steps: Move the handles and selection end.
     *            Verify the selection data.
     */
    pattern_->HandleSetSelection(start, end, false);
    pattern_->HandleSelect(select[3]);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, start);
    EXPECT_EQ(pattern_->selectController_->GetSecondHandleInfo().index, 22);
}

/**
 * @tc.name: CursonMoveLeftTest001
 * @tc.desc: Test the curson move left
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCursorTest, CursonMoveLeftTest001, TestSize.Level1)
{
    /**
     * @tc.steps: Initialize insert text and expected values
     */
    CreateTextField(DEFAULT_TEXT, DEFAULT_PLACE_HOLDER);
    GetFocus();
    auto ret = pattern_->CursorMoveLeft();
    FlushLayoutTask(frameNode_);

    /**
     * @tc.expected: In a situation where no text is selected, the movement is successfull
     */
    EXPECT_TRUE(ret);
    EXPECT_EQ(pattern_->GetSelectMode(), SelectionMode::NONE);
    EXPECT_EQ(pattern_->GetCaretIndex(), DEFAULT_TEXT.length() - 1);

    /**
     * @tc.steps: In a situation where text is selected, the movement is successful
     */
    pattern_->HandleSetSelection(3, 5, false);
    FlushLayoutTask(frameNode_);
    ret = pattern_->CursorMoveLeft();

    /**
     * @tc.expected: The cursor moves to the position after the selected text is deleted
     */
    EXPECT_TRUE(ret);
    EXPECT_EQ(pattern_->GetSelectMode(), SelectionMode::NONE);
    EXPECT_EQ(pattern_->GetCaretIndex(), 4)
        << "Text is " + pattern_->GetTextValue() + ", CaretIndex is " + std::to_string(pattern_->GetCaretIndex());
}

/**
 * @tc.name: CursonMoveLeftWordTest001
 * @tc.desc: Test the curson move left word
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCursorTest, CursonMoveLeftWordTest001, TestSize.Level1)
{
    /**
     * @tc.steps: Initialize text input node and default text
     */
    CreateTextField(DEFAULT_TEXT, DEFAULT_PLACE_HOLDER);
    GetFocus();

    auto ret = pattern_->CursorMoveLeftWord();

    /**
     * @tc.expected: In a situation where no text is selected, the movement is successfull
     */
    EXPECT_TRUE(ret);
    EXPECT_EQ(pattern_->GetSelectMode(), SelectionMode::NONE);
    EXPECT_EQ(pattern_->GetCaretIndex(), 0)
        << "Text is " + pattern_->GetTextValue() + ", CaretIndex is " + std::to_string(pattern_->GetCaretIndex());

    /**
     * @tc.steps: In a situation where text is selected, the movement is successful
     */
    pattern_->HandleSetSelection(3, 5, false);
    FlushLayoutTask(frameNode_);
    ret = pattern_->CursorMoveLeftWord();

    /**
     * @tc.expected: The cursor moves to the position after the selected text is deleted
     */
    EXPECT_TRUE(ret);
    EXPECT_EQ(pattern_->GetSelectMode(), SelectionMode::NONE);
    EXPECT_EQ(pattern_->GetCaretIndex(), 0)
        << "Text is " + pattern_->GetTextValue() + ", CaretIndex is " + std::to_string(pattern_->GetCaretIndex());
}

/**
 * @tc.name: CursorMoveLineBeginTest001
 * @tc.desc: Test the cursor move line begin
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCursorTest, CursorMoveLineBeginTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize empty text and CursorMoveLineBegin
     */
    CreateTextField();
    GetFocus();
    auto ret = pattern_->CursorMoveLineBegin();
    EXPECT_TRUE(ret);

    /**
     * @tc.steps: step2. Insert text and move line begin
     */
    pattern_->InsertValue("hello world");
    FlushLayoutTask(frameNode_);
    ret = pattern_->CursorMoveLineBegin();

    /**
     * @tc.expected: Cursor move to the line head
     */
    EXPECT_TRUE(ret);
    EXPECT_EQ(pattern_->GetSelectMode(), SelectionMode::NONE);
    EXPECT_EQ(pattern_->GetCaretIndex(), 0)
        << "Text is " + pattern_->GetTextValue() + ", CaretIndex is " + std::to_string(pattern_->GetCaretIndex());

    /**
     * @tc.steps: In a situation where text is all selected, the movement is successful
     */
    pattern_->HandleSetSelection(0, 11, false);
    FlushLayoutTask(frameNode_);
    ret = pattern_->CursorMoveLineBegin();

    /**
     * @tc.expected: Cursor move to the line head
     */
    EXPECT_TRUE(ret);
    EXPECT_EQ(pattern_->GetSelectMode(), SelectionMode::NONE);
    EXPECT_EQ(pattern_->GetCaretIndex(), 0)
        << "Text is " + pattern_->GetTextValue() + ", CaretIndex is " + std::to_string(pattern_->GetCaretIndex());
}

/**
 * @tc.name: CursorMoveToParagraphBeginTest001
 * @tc.desc: Test the cursor move paragraph begin
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCursorTest, CursorMoveToParagraphBeginTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize empty text and cursor move to paragraph begin
     */
    CreateTextField();
    GetFocus();
    auto ret = pattern_->CursorMoveToParagraphBegin();
    EXPECT_TRUE(ret);

    /**
     * @tc.steps: step2. Insert text
     */
    pattern_->InsertValue("hello world");
    FlushLayoutTask(frameNode_);
    ret = pattern_->CursorMoveToParagraphBegin();

    /**
     * @tc.expected: Cursor move to the line head
     */
    EXPECT_TRUE(ret);
    EXPECT_EQ(pattern_->GetSelectMode(), SelectionMode::NONE);
    EXPECT_EQ(pattern_->GetCaretIndex(), 0)
        << "Text is " + pattern_->GetTextValue() + ", CaretIndex is " + std::to_string(pattern_->GetCaretIndex());
}

/**
 * @tc.name: CursorMoveHomeTest001
 * @tc.desc: Test the cursor move home
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCursorTest, CursorMoveHomeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize empty text and curson move home
     */
    CreateTextField();
    GetFocus();
    auto ret = pattern_->CursorMoveHome();
    EXPECT_TRUE(ret);

    /**
     * @tc.steps: step2. Insert text
     */
    pattern_->InsertValue("hello world");
    FlushLayoutTask(frameNode_);
    ret = pattern_->CursorMoveHome();

    /**
     * @tc.expected: Cursor move to the line head
     */
    EXPECT_TRUE(ret);
    EXPECT_EQ(pattern_->GetSelectMode(), SelectionMode::NONE);
    EXPECT_EQ(pattern_->GetCaretIndex(), 0)
        << "Text is " + pattern_->GetTextValue() + ", CaretIndex is " + std::to_string(pattern_->GetCaretIndex());
}

/**
 * @tc.name: CursorMoveRightTest001
 * @tc.desc: Test the cursor move right
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCursorTest, CursorMoveRightTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize default text and curson move right
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    auto ret = pattern_->CursorMoveRight();

    /**
     * @tc.expected: Unable to move
     */
    EXPECT_FALSE(ret);
    EXPECT_EQ(pattern_->GetSelectMode(), SelectionMode::NONE);
    EXPECT_EQ(pattern_->GetCaretIndex(), 26)
        << "Text is " + pattern_->GetTextValue() + ", CaretIndex is " + std::to_string(pattern_->GetCaretIndex());

    /**
     * @tc.steps: step2. Move cursor back to the line head and move right
     */
    ret = pattern_->CursorMoveLineBegin();
    ret = pattern_->CursorMoveRight();

    /**
     * @tc.expected: In a situation where no text is selected, the movement is successfull
     */
    EXPECT_TRUE(ret);
    EXPECT_EQ(pattern_->GetSelectMode(), SelectionMode::NONE);
    EXPECT_EQ(pattern_->GetCaretIndex(), 1)
        << "Text is " + pattern_->GetTextValue() + ", CaretIndex is " + std::to_string(pattern_->GetCaretIndex());

    /**
     * @tc.steps: step3. Select the text within coordinates 3 to 5 and move cursor right
     */
    pattern_->HandleSetSelection(3, 5, false);
    FlushLayoutTask(frameNode_);
    ret = pattern_->CursorMoveRight();

    /**
     * @tc.expected: Select from 3 to 5, move the cursor to 6.
     */
    EXPECT_TRUE(ret);
    EXPECT_EQ(pattern_->GetSelectMode(), SelectionMode::NONE);
    EXPECT_EQ(pattern_->GetCaretIndex(), 6)
        << "Text is " + pattern_->GetTextValue() + ", CaretIndex is " + std::to_string(pattern_->GetCaretIndex());
}

/**
 * @tc.name: CursorMoveRightWordTest001
 * @tc.desc: Test the cursor move right word
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCursorTest, CursorMoveRightWordTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize default text and curson move right
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    auto ret = pattern_->CursorMoveRightWord();

    /**
     * @tc.expected: Moving to the right character when there is initial text
     */
    EXPECT_TRUE(ret);
    EXPECT_EQ(pattern_->GetSelectMode(), SelectionMode::NONE);
    EXPECT_EQ(pattern_->GetCaretIndex(), DEFAULT_TEXT.length())
        << "Text is " + pattern_->GetTextValue() + ", CaretIndex is " + std::to_string(pattern_->GetCaretIndex());

    /**
     * @tc.steps: steps2. Move to the left 2 times first.
     */
    ret = pattern_->CursorMoveLeft();
    ret = pattern_->CursorMoveLeft();
    FlushLayoutTask(frameNode_);

    /**
     * @tc.expected:  the current text length - 2
     */
    EXPECT_EQ(pattern_->GetCaretIndex(), DEFAULT_TEXT.length() - 2)
        << "Text is " + pattern_->GetTextValue() + ", CaretIndex is " + std::to_string(pattern_->GetCaretIndex());

    /**
     * @tc.steps: steps3. Continue moving to the right word.
     */
    ret = pattern_->CursorMoveRightWord();

    /**
     * @tc.expected: Moving to the right character when there is initial text
     */
    EXPECT_TRUE(ret);
    EXPECT_EQ(pattern_->GetSelectMode(), SelectionMode::NONE);
    EXPECT_EQ(pattern_->GetCaretIndex(), DEFAULT_TEXT.length())
        << "Text is " + pattern_->GetTextValue() + ", CaretIndex is " + std::to_string(pattern_->GetCaretIndex());

    /**
     * @tc.steps: step4. Move to the beginning of the line and select all text.
     */
    ret = pattern_->CursorMoveLineBegin();
    pattern_->HandleSetSelection(0, DEFAULT_TEXT.length(), false);
    FlushLayoutTask(frameNode_);
    ret = pattern_->CursorMoveRightWord();

    /**
     * @tc.expected: Moving to the right character when there is initial text
     */
    EXPECT_TRUE(ret);
    EXPECT_EQ(pattern_->GetSelectMode(), SelectionMode::NONE);
    EXPECT_EQ(pattern_->GetCaretIndex(), DEFAULT_TEXT.length())
        << "Text is " + pattern_->GetTextValue() + ", CaretIndex is " + std::to_string(pattern_->GetCaretIndex());
}

/**
 * @tc.name: CursorMoveLineEndTest001
 * @tc.desc: Test the cursor move line end
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCursorTest, CursorMoveLineEndTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize  text and move to the end of the line
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    auto ret = pattern_->CursorMoveLineEnd();

    /**
     * @tc.expected: Moving to the right character when there is initial text
     */
    EXPECT_TRUE(ret);
    EXPECT_EQ(pattern_->GetSelectMode(), SelectionMode::NONE);
    EXPECT_EQ(pattern_->GetCaretIndex(), DEFAULT_TEXT.length())
        << "Text is " + pattern_->GetTextValue() + ", CaretIndex is " + std::to_string(pattern_->GetCaretIndex());

    /**
     * @tc.steps: step2. Move to the beginning of the line and select all text
     */
    pattern_->HandleSetSelection(0, DEFAULT_TEXT.length(), false);
    FlushLayoutTask(frameNode_);
    ret = pattern_->CursorMoveLineEnd();

    /**
     * @tc.expected: Moving to the right character when there is initial text
     */
    EXPECT_TRUE(ret);
    EXPECT_EQ(pattern_->GetSelectMode(), SelectionMode::NONE);
    EXPECT_EQ(pattern_->GetCaretIndex(), DEFAULT_TEXT.length())
        << "Text is " + pattern_->GetTextValue() + ", CaretIndex is " + std::to_string(pattern_->GetCaretIndex());
}

/**
 * @tc.name: CursorMoveToParagraphEndTest001
 * @tc.desc: Test the cursor move to pragraph to the end
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCursorTest, CursorMoveToParagraphEndTest001, TestSize.Level1)
{
    /**
     * @tc.steps: Initialize text and move to the pargraph of the line
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    auto ret = pattern_->CursorMoveToParagraphEnd();
    EXPECT_TRUE(ret);

    /**
     * @tc.expected: Moving to the paragraph end and check if cursor is on pargraph end
     */
    ret = pattern_->CursorMoveLeft();
    ret = pattern_->CursorMoveToParagraphEnd();
    EXPECT_TRUE(ret);
    EXPECT_EQ(pattern_->GetCaretIndex(), DEFAULT_TEXT.length())
        << "Text is " + pattern_->GetTextValue() + ", CaretIndex is " + std::to_string(pattern_->GetCaretIndex());
}

/**
 * @tc.name: CursorMoveEndTest001
 * @tc.desc: Test the cursor move end
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCursorTest, CursorMoveEndTest001, TestSize.Level1)
{
    /**
     * @tc.steps: Initialize text and move to the pargraph of the line
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    auto ret = pattern_->CursorMoveToParagraphEnd();
    EXPECT_TRUE(ret);

    /**
     * @tc.expected: Move left once first, and then move to the end
     *               Check if the cursor is at the end of the text.
     */
    ret = pattern_->CursorMoveLeft();
    ret = pattern_->CursorMoveEnd();
    EXPECT_TRUE(ret);
    EXPECT_EQ(pattern_->GetCaretIndex(), DEFAULT_TEXT.length());
}

/**
 * @tc.name: CursorMoveUpTest001
 * @tc.desc: Test the cursor move up
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCursorTest, CursorMoveUpTest001, TestSize.Level1)
{
    /**
     * @tc.steps: Move up and down in a single-line text
     * @tc.expected: In single-line text, there is no up and down movement
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    auto ret = pattern_->CursorMoveUp();
    EXPECT_FALSE(ret);
    ret = pattern_->CursorMoveDown();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: GetLeftTextOfCursor001
 * @tc.desc: Test get text of left cursor
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCursorTest, GetLeftTextOfCursor001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create default text and retrieve the left 5 characters before the cursor
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.expected: Check if it equals "vwxyz"
     */
    EXPECT_EQ(StringUtils::Str16ToStr8(pattern_->GetLeftTextOfCursor(5)), "vwxyz");

    /**
     * @tc.steps: step2. Select the text from position 3 to 5
     */
    pattern_->HandleSetSelection(3, 5, false);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.expected: Check if it equals "vwxyz"
     */
    EXPECT_EQ(StringUtils::Str16ToStr8(pattern_->GetLeftTextOfCursor(5)), "abc");
}

/**
 * @tc.name: GetRightTextOfCursor001
 * @tc.desc: Test get text of left cursor
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCursorTest, GetRightTextOfCursor001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create default text and retrieve the left 5 characters before the cursor
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.expected: Check if it equals "vwxyz"
     */
    EXPECT_EQ(StringUtils::Str16ToStr8(pattern_->GetRightTextOfCursor(5)), "");

    /**
     * @tc.steps: step2. Select the text from position 3 to 5
     */
    pattern_->HandleSetSelection(3, 5, false);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.expected: Check if it equals "vwxyz"
     */
    EXPECT_EQ(StringUtils::Str16ToStr8(pattern_->GetRightTextOfCursor(5)), "fghij");
}

/**
 * @tc.name: ContentController001
 * @tc.desc: Test ContentController in different input type
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, ContentController001, TestSize.Level1)
{
    /**
     * @tc.steps: Initialize insert text and expected values
     */
    std::vector<std::string> insertValues = {
        "openharmony123_ *+%$",
        "openharmony123456*+&@huawei.com",
        "openharmony#15612932075*.com",
        "open_harmony@@huawei.com*+$helloworld",
        "open_harmony123 password*+#",
        "openharmony123456*+&@huawei.com",
        "o达瓦大屋顶pen_harmony456顶顶顶 password*+#得到",
    };
    std::vector<TestItem<TextInputType, std::string>> testItems;
    testItems.emplace_back(TextInputType::TEXT, "openharmony123_ *+%$", "TextInputType::TEXT");
    testItems.emplace_back(TextInputType::NUMBER, "123456", "TextInputType::NUMBER");
    testItems.emplace_back(TextInputType::PHONE, "#15612932075*", "TextInputType::PHONE");
    testItems.emplace_back(
        TextInputType::EMAIL_ADDRESS, "open_harmony@huawei.comhelloworld", "TextInputType::EMAIL_ADDRESS");
    testItems.emplace_back(
        TextInputType::VISIBLE_PASSWORD, "open_harmony123 password*+#", "TextInputType::VISIBLE_PASSWORD");
    testItems.emplace_back(TextInputType::NUMBER_PASSWORD, "123456", "TextInputType::NUMBER_PASSWORD");
    testItems.emplace_back(
        TextInputType::SCREEN_LOCK_PASSWORD, "open_harmony456 password*+#", "TextInputType::SCREEN_LOCK_PASSWORD");

    /**
     * @tc.expected: Check if text filtering meets expectations
     */
    int index = 0;
    for (const auto& testItem : testItems) {
        CreateTextField("", "", [testItem](TextFieldModelNG& model) { model.SetType(testItem.item); });

        pattern_->contentController_->InsertValue(0, insertValues[index]);
        index++;
        auto errorMessage = "InputType is " + testItem.error + ", text is " + pattern_->GetTextValue();
        EXPECT_EQ(pattern_->GetTextValue().compare(testItem.expected), 0) << errorMessage;
    }
}

/**
 * @tc.name: ContentController002
 * @tc.desc: Test ContentController in different input filter
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, ContentController002, TestSize.Level1)
{
    /**
     * @tc.steps: Initialize text and filter patterns
     */
    std::string text = "CabcdefgABhCDEFG0123a456A789";
    std::vector<TestItem<std::string, std::string>> testItems;
    testItems.emplace_back("", "CabcdefgABhCDEFG0123a456A789", "None");
    testItems.emplace_back("[0-9]", "0123456789", "Input filter [0-9]");
    testItems.emplace_back("[A-Z]", "CABCDEFGA", "Input filter [A-Z]");
    testItems.emplace_back("[a-z]", "abcdefgha", "Input filter [a-z]");

    /**
     * @tc.expected: Check if the text filter patterns for the input box are compliant
     */
    for (const auto& testItem : testItems) {
        CreateTextField("", "", [testItem](TextFieldModelNG& model) { model.SetInputFilter(testItem.item, nullptr); });

        pattern_->contentController_->InsertValue(0, text);
        auto errorMessage = testItem.error + ", text is " + pattern_->GetTextValue();
        EXPECT_EQ(pattern_->GetTextValue().compare(testItem.expected), 0) << errorMessage;
    }
}

/**
 * @tc.name: ContentController003
 * @tc.desc: Test ContentController in different input filter
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, ContentController003, TestSize.Level1)
{
    /**
     * @tc.steps: Initialize text filed node
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.expected: Check if text is selected based on corresponding left and right coordinates
     */
    auto selectedValue = pattern_->contentController_->GetSelectedValue(1, 4);
    EXPECT_EQ(selectedValue.compare("bcd"), 0) << "Text is " + selectedValue;

    /**
     * @tc.expected: Check if text is selected based on preceding coordinates
     */
    auto beforeSelectedValue = pattern_->contentController_->GetValueBeforeIndex(3);
    EXPECT_EQ(beforeSelectedValue.compare("abc"), 0) << "Text is " + beforeSelectedValue;

    /**
     * @tc.expected: Check if text is selected based on trailing coordinates
     */
    auto afterSelectedValue = pattern_->contentController_->GetValueAfterIndex(3);
    EXPECT_EQ(afterSelectedValue.compare("defghijklmnopqrstuvwxyz"), 0) << "Text is " + afterSelectedValue;
}

/**
 * @tc.name: TextFiledControllerTest001
 * @tc.desc: Test TextFieldController GetTextContentLinesNum
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, TextFiledControllerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: Initialize text filed node
     */
    CreateTextField();

    /**
     * @tc.expected: Check if the number of lines meets the expectation
     */
    auto controller = pattern_->GetTextFieldController();
    auto line = controller->GetTextContentLinesNum();
    EXPECT_EQ(line, 0);
}

/**
 * @tc.name: ControllerTest002
 * @tc.desc: Test TextFieldController GetTextContentLinesNum
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, TextFiledControllerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: Initialize text filed node
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.expected: Check if the number of lines meets the expectation
     */
    auto controller = pattern_->GetTextFieldController();
    auto line = controller->GetTextContentLinesNum();
    EXPECT_EQ(line, 1);
}

/**
 * @tc.name: KeyEventChar001
 * @tc.desc: Test symbols key input
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldKeyEventTest, KeyEventChar001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get focus
     */
    CreateTextField();
    GetFocus();
    /**
     * @tc.steps: step2. Create keyboard events
     */
    KeyEvent event;
    event.action = KeyAction::DOWN;
    std::vector<KeyCode> presscodes = {};
    event.pressedCodes = presscodes;
    const std::unordered_map<KeyCode, wchar_t> symbols = {
        { KeyCode::KEY_GRAVE, L'`' },
        { KeyCode::KEY_MINUS, L'-' },
        { KeyCode::KEY_EQUALS, L'=' },
        { KeyCode::KEY_LEFT_BRACKET, L'[' },
        { KeyCode::KEY_RIGHT_BRACKET, L']' },
        { KeyCode::KEY_BACKSLASH, L'\\' },
        { KeyCode::KEY_SEMICOLON, L';' },
        { KeyCode::KEY_APOSTROPHE, L'\'' },
        { KeyCode::KEY_COMMA, L',' },
        { KeyCode::KEY_PERIOD, L'.' },
        { KeyCode::KEY_SLASH, L'/' },
        { KeyCode::KEY_SPACE, L' ' },
        { KeyCode::KEY_NUMPAD_DIVIDE, L'/' },
        { KeyCode::KEY_NUMPAD_MULTIPLY, L'*' },
        { KeyCode::KEY_NUMPAD_SUBTRACT, L'-' },
        { KeyCode::KEY_NUMPAD_ADD, L'+' },
        { KeyCode::KEY_NUMPAD_DOT, L'.' },
        { KeyCode::KEY_NUMPAD_COMMA, L',' },
        { KeyCode::KEY_NUMPAD_EQUALS, L'=' },
    };
    /**
     * @tc.expected: Calling the keyboard event interface
     */
    std::string result;
    for (auto code : symbols) {
        event.pressedCodes.clear();
        event.pressedCodes.push_back(code.first);
        event.code = code.first;
        auto ret = pattern_->OnKeyEvent(event);
        FlushLayoutTask(frameNode_);
        std::wstring appendElement(1, code.second);
        result.append(StringUtils::ToString(appendElement));
        EXPECT_EQ(pattern_->GetTextValue(), result);
        EXPECT_TRUE(ret);
    }
}

/**
 * @tc.name: KeyEventChar001
 * @tc.desc: Test shift + symbols key input
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldKeyEventTest, KeyEventChar002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get focus
     */
    CreateTextField();
    GetFocus();
    /**
     * @tc.steps: step2. Create keyboard events
     */
    KeyEvent event;
    event.action = KeyAction::DOWN;
    std::vector<KeyCode> presscodes = {};
    event.pressedCodes = presscodes;
    std::vector<KeyCode> shiftCodes = { KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_SHIFT_RIGHT };
    const std::unordered_map<KeyCode, wchar_t> symbols = {
        { KeyCode::KEY_GRAVE, L'~' },
        { KeyCode::KEY_MINUS, L'_' },
        { KeyCode::KEY_EQUALS, L'+' },
        { KeyCode::KEY_LEFT_BRACKET, L'{' },
        { KeyCode::KEY_RIGHT_BRACKET, L'}' },
        { KeyCode::KEY_BACKSLASH, L'|' },
        { KeyCode::KEY_SEMICOLON, L':' },
        { KeyCode::KEY_APOSTROPHE, L'\"' },
        { KeyCode::KEY_COMMA, L'<' },
        { KeyCode::KEY_PERIOD, L'>' },
        { KeyCode::KEY_SLASH, L'?' },
    };
    /**
     * @tc.expected: Calling the keyboard event interface
     */
    std::string result;
    for (auto shift : shiftCodes) {
        for (auto code : symbols) {
            event.pressedCodes.clear();
            event.pressedCodes.push_back(shift);
            event.pressedCodes.push_back(code.first);
            event.code = code.first;
            auto ret = pattern_->OnKeyEvent(event);
            FlushLayoutTask(frameNode_);
            std::wstring appendElement(1, code.second);
            result.append(StringUtils::ToString(appendElement));
            EXPECT_EQ(pattern_->GetTextValue(), result);
            EXPECT_TRUE(ret);
        }
    }
}

/**
 * @tc.name: KeyEventChar003
 * @tc.desc: Test uppercase letters input
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldKeyEventTest, KeyEventChar003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get focus
     */
    CreateTextField();
    GetFocus();
    /**
     * @tc.steps: step2. Create keyboard events
     */
    KeyEvent event;
    event.action = KeyAction::DOWN;
    std::vector<KeyCode> presscodes = {};
    event.pressedCodes = presscodes;
    std::vector<KeyCode> shiftCodes = { KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_SHIFT_RIGHT };
    const std::unordered_map<KeyCode, wchar_t> symbols = {
        { KeyCode::KEY_A, 'A' },
        { KeyCode::KEY_B, 'B' },
        { KeyCode::KEY_C, 'C' },
        { KeyCode::KEY_X, 'X' },
        { KeyCode::KEY_Y, 'Y' },
        { KeyCode::KEY_Z, 'Z' },
    };
    /**
     * @tc.expected: lowercase to uppercase
     */
    std::string result;
    for (auto shift : shiftCodes) {
        for (auto code : symbols) {
            event.pressedCodes.clear();
            EXPECT_EQ(event.pressedCodes.size(), 0);
            event.pressedCodes.push_back(shift);
            event.pressedCodes.push_back(code.first);
            event.code = code.first;
            auto ret = pattern_->OnKeyEvent(event);
            FlushLayoutTask(frameNode_);
            std::wstring appendElement(1, code.second);
            result.append(StringUtils::ToString(appendElement));
            EXPECT_EQ(pattern_->GetTextValue(), result);
            EXPECT_TRUE(ret);
        }
    }
}

/**
 * @tc.name: KeyEventChar004
 * @tc.desc: Test Shift + 0-9 symbols input
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldKeyEventTest, KeyEventChar004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get focus
     */
    CreateTextField();
    GetFocus();
    /**
     * @tc.steps: step2. Create keyboard events
     */
    KeyEvent event;
    event.action = KeyAction::DOWN;
    std::vector<KeyCode> presscodes = {};
    std::vector<KeyCode> shiftCodes = { KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_SHIFT_RIGHT };
    const std::unordered_map<KeyCode, wchar_t> symbols = {
        { KeyCode::KEY_0, ')' },
        { KeyCode::KEY_1, '!' },
        { KeyCode::KEY_2, '@' },
        { KeyCode::KEY_3, '#' },
        { KeyCode::KEY_4, '$' },
        { KeyCode::KEY_5, '%' },
        { KeyCode::KEY_6, '^' },
        { KeyCode::KEY_7, '&' },
        { KeyCode::KEY_8, '*' },
        { KeyCode::KEY_9, '(' },
    };
    /**
     * @tc.expected: shift + number to input
     */
    std::string result;
    for (auto shift : shiftCodes) {
        for (auto code : symbols) {
            event.pressedCodes.clear();
            EXPECT_EQ(event.pressedCodes.size(), 0);
            event.pressedCodes.push_back(shift);
            event.pressedCodes.push_back(code.first);
            event.code = code.first;
            auto ret = pattern_->OnKeyEvent(event);
            FlushLayoutTask(frameNode_);
            std::wstring appendElement(1, code.second);
            result.append(StringUtils::ToString(appendElement));
            EXPECT_EQ(pattern_->GetTextValue(), result);
            EXPECT_TRUE(ret);
        }
    }
}

/**
 * @tc.name: KeyEvent001
 * @tc.desc: Test KeyEvent selections
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldKeyEventTest, KeyEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. Initialize KeyEvent and call OnKeyEvent
     * @tc.expected: return as expected
     */
    KeyEvent event;
    event.action = KeyAction::DOWN;
    std::vector<KeyCode> eventCodes = {
        KeyCode::KEY_DPAD_UP,
        KeyCode::KEY_DPAD_DOWN,
        KeyCode::KEY_DPAD_LEFT,
        KeyCode::KEY_DPAD_RIGHT,
        KeyCode::KEY_MOVE_HOME,
        KeyCode::KEY_MOVE_END,
    };
    std::vector<KeyCode> presscodes = {};
    event.pressedCodes = presscodes;
    for (auto eventCode : eventCodes) {
        event.pressedCodes.emplace_back(KeyCode::KEY_SHIFT_LEFT);
        event.pressedCodes.emplace_back(eventCode);
        event.code = eventCode;
        auto ret = pattern_->OnKeyEvent(event);
        EXPECT_TRUE(ret);
    }
    event.pressedCodes.clear();
    for (auto eventCode : eventCodes) {
        event.pressedCodes.emplace_back(KeyCode::KEY_CTRL_LEFT);
        event.pressedCodes.emplace_back(KeyCode::KEY_SHIFT_LEFT);
        event.pressedCodes.emplace_back(eventCode);
        event.code = eventCode;
        auto ret = pattern_->OnKeyEvent(event);
        EXPECT_TRUE(ret);
    }
    event.pressedCodes.clear();
    event.pressedCodes.emplace_back(KeyCode::KEY_BACK);
    event.code = KeyCode::KEY_BACK;
    auto ret = pattern_->OnKeyEvent(event);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: KeyEvent002
 * @tc.desc: Test KeyEvent cursor moves
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldKeyEventTest, KeyEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. Initialize KeyEvent and call OnKeyEvent
     * @tc.expected: return as expected
     */
    KeyEvent event;
    event.action = KeyAction::DOWN;
    std::vector<KeyCode> eventCodes = {
        KeyCode::KEY_DPAD_LEFT,
        KeyCode::KEY_DPAD_UP,
        KeyCode::KEY_MOVE_HOME,
        KeyCode::KEY_DPAD_RIGHT,
        KeyCode::KEY_DPAD_DOWN,
        KeyCode::KEY_MOVE_END,
    };
    std::vector<KeyCode> presscodes = {};
    event.pressedCodes = presscodes;
    for (auto eventCode : eventCodes) {
        event.pressedCodes.emplace_back(KeyCode::KEY_CTRL_LEFT);
        event.pressedCodes.emplace_back(eventCode);
        event.code = eventCode;
        auto ret = pattern_->OnKeyEvent(event);
        EXPECT_TRUE(ret) << "KeyCode: " + std::to_string(static_cast<int>(eventCode));
    }
    event.pressedCodes.clear();
    for (auto eventCode : eventCodes) {
        event.pressedCodes.emplace_back(eventCode);
        event.code = eventCode;
        auto ret = pattern_->OnKeyEvent(event);
        EXPECT_TRUE(ret) << "KeyCode: " + std::to_string(static_cast<int>(eventCode));
    }
    event.code = KeyCode::KEY_DPAD_CENTER;
    event.pressedCodes.clear();
    event.pressedCodes.emplace_back(event.code);
    auto ret = pattern_->OnKeyEvent(event);
    EXPECT_TRUE(ret) << "KeyCode: " + std::to_string(static_cast<int>(event.code));
}

/**
 * @tc.name: KeyEvent003
 * @tc.desc: Test KeyEvent ctrl + c/v
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldKeyEventTest, KeyEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get focus
     */
    std::string expectStr = "fghij";
    auto onCopy = [expectStr](const std::string& str) { EXPECT_EQ(expectStr, str); };
    auto onPaste = [expectStr](const std::string& str) { EXPECT_EQ(expectStr, str); };
    CreateTextField(DEFAULT_TEXT, DEFAULT_PLACE_HOLDER, [&](TextFieldModel& model) -> void {
        model.SetOnCopy(onCopy);
        model.SetOnPaste(onPaste);
    });

    /**
     * @tc.steps: step2. Create keyboard events
     */
    KeyEvent event;
    event.action = KeyAction::DOWN;
    std::vector<KeyCode> presscodes = {};
    event.pressedCodes = presscodes;

    /**
     * @tc.expected: shift + insert to input
     */
    event.pressedCodes.clear();
    event.pressedCodes.push_back(KeyCode::KEY_CTRL_LEFT);
    event.pressedCodes.push_back(KeyCode::KEY_C);
    event.code = KeyCode::KEY_C;
    pattern_->HandleSetSelection(5, 10, false);
    auto ret = pattern_->OnKeyEvent(event);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(ret);

    event.pressedCodes.clear();
    event.pressedCodes.push_back(KeyCode::KEY_CTRL_LEFT);
    event.pressedCodes.push_back(KeyCode::KEY_V);
    event.code = KeyCode::KEY_V;
    pattern_->SetCaretPosition(0);
    ret = pattern_->OnKeyEvent(event);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTextValue(), expectStr + DEFAULT_TEXT);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: KeyEvent004
 * @tc.desc: Test KeyEvent ctrl + a
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldKeyEventTest, KeyEvent004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. Create keyboard events
     */
    KeyEvent event;
    event.action = KeyAction::DOWN;
    std::vector<KeyCode> presscodes = {};
    event.pressedCodes = presscodes;

    /**
     * @tc.expected: shift + a to input
     */
    event.pressedCodes.clear();
    event.pressedCodes.push_back(KeyCode::KEY_CTRL_LEFT);
    event.pressedCodes.push_back(KeyCode::KEY_A);
    event.code = KeyCode::KEY_A;
    pattern_->HandleSetSelection(5, 10, false);
    auto ret = pattern_->OnKeyEvent(event);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(ret);
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, 0);
    EXPECT_EQ(pattern_->selectController_->GetSecondHandleInfo().index, 26)
        << "Second index is " + std::to_string(pattern_->selectController_->GetSecondHandleInfo().index);
}

/**
 * @tc.name: KeyEvent005
 * @tc.desc: Test KeyEvent ctrl + x
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldKeyEventTest, KeyEvent005, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Initialize text input and Move the handles and then cut text snippet.
     */
    int32_t start = 5;
    int32_t end = 10;
    std::string expectStr = "fghij";
    std::vector<std::int32_t> action = {
        ACTION_SELECT_ALL,
        ACTION_CUT,
        ACTION_COPY,
        ACTION_PASTE,
    };
    auto callback = [expectStr](const std::string& str) { EXPECT_EQ(expectStr, str); };
    CreateTextField(DEFAULT_TEXT, DEFAULT_PLACE_HOLDER, [&](TextFieldModel& model) {
        model.SetOnCut(callback); });

    /**
     * @tc.steps: step2. Create keyboard events
     */
    KeyEvent event;
    event.action = KeyAction::DOWN;
    std::vector<KeyCode> presscodes = {};
    event.pressedCodes = presscodes;

    /**
     * @tc.expected: shift + x to input
     */
    event.pressedCodes.clear();
    event.pressedCodes.push_back(KeyCode::KEY_CTRL_LEFT);
    event.pressedCodes.push_back(KeyCode::KEY_X);
    event.code = KeyCode::KEY_X;
    pattern_->HandleSetSelection(start, end, false);
    auto ret = pattern_->OnKeyEvent(event);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(ret);
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, start);
    EXPECT_EQ(pattern_->selectController_->GetSecondHandleInfo().index, start)
        << "Second index is " + std::to_string(pattern_->selectController_->GetSecondHandleInfo().index);
    EXPECT_EQ(pattern_->GetTextSelectController()->GetCaretIndex(), start);
    EXPECT_EQ(pattern_->contentController_->GetTextValue().compare("abcdeklmnopqrstuvwxyz"), 0);
}

/**
 * @tc.name: KeyEvent006
 * @tc.desc: Test KeyEvent ctrl + z/y
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldKeyEventTest, KeyEvent006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get focus
     */
    std::string expectStr = "fghij";
    auto onCopy = [expectStr](const std::string& str) { EXPECT_EQ(expectStr, str); };
    auto onPaste = [expectStr](const std::string& str) { EXPECT_EQ(expectStr, str); };
    CreateTextField(DEFAULT_TEXT, DEFAULT_PLACE_HOLDER, [&](TextFieldModel& model) -> void {
        model.SetOnCopy(onCopy);
        model.SetOnPaste(onPaste);
    });
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Create keyboard events
     */
    KeyEvent event;
    event.action = KeyAction::DOWN;
    std::vector<KeyCode> presscodes = {};
    event.pressedCodes = presscodes;

    /**
     * @tc.expected: shift + c/v to input
     */
    event.pressedCodes.clear();
    event.pressedCodes.push_back(KeyCode::KEY_CTRL_LEFT);
    event.pressedCodes.push_back(KeyCode::KEY_C);
    event.code = KeyCode::KEY_C;
    pattern_->HandleSetSelection(5, 10, false);
    auto ret = pattern_->OnKeyEvent(event);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(ret);

    event.pressedCodes.clear();
    event.pressedCodes.push_back(KeyCode::KEY_CTRL_LEFT);
    event.pressedCodes.push_back(KeyCode::KEY_V);
    event.code = KeyCode::KEY_V;
    pattern_->SetCaretPosition(0);
    ret = pattern_->OnKeyEvent(event);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTextValue(), expectStr + DEFAULT_TEXT);
    EXPECT_TRUE(ret);

    /**
     * @tc.expected: shift + z/y to input
     */
    event.pressedCodes.clear();
    event.pressedCodes.push_back(KeyCode::KEY_CTRL_LEFT);
    event.pressedCodes.push_back(KeyCode::KEY_Z);
    event.code = KeyCode::KEY_Z;
    ret = pattern_->OnKeyEvent(event);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTextValue(), "");
    EXPECT_TRUE(ret);

    event.pressedCodes.clear();
    event.pressedCodes.push_back(KeyCode::KEY_CTRL_LEFT);
    event.pressedCodes.push_back(KeyCode::KEY_Y);
    event.code = KeyCode::KEY_Y;
    ret = pattern_->OnKeyEvent(event);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTextValue(), expectStr + DEFAULT_TEXT);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: KeyEvent007
 * @tc.desc: Test KeyEvent enter
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldKeyEventTest, KeyEvent007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get focus
     */
    auto onSubmit = [](int32_t textFieldKey, NG::TextFieldCommonEvent& commonEvent) {
        commonEvent.SetKeepEditable(true);
        EXPECT_TRUE(commonEvent.keepEditable_);
    };
    CreateTextField(DEFAULT_TEXT, DEFAULT_PLACE_HOLDER, [&](TextFieldModel& model) -> void {
        model.SetOnSubmit(onSubmit);
    });
    GetFocus();

    pattern_->PerformAction(TextInputAction::DONE, true);
    EXPECT_TRUE(pattern_->GetCursorVisible());
}

/**
 * @tc.name: KeyEvent008
 * @tc.desc: Test KeyEvent enter
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldKeyEventTest, KeyEvent008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get focus
     */
    auto onSubmit = [](int32_t textFieldKey, NG::TextFieldCommonEvent& commonEvent) {
        EXPECT_FALSE(commonEvent.keepEditable_);
        EXPECT_EQ(commonEvent.text_, "abcdefghijklmnopqrstuvwxyz");
    };
    CreateTextField(DEFAULT_TEXT, DEFAULT_PLACE_HOLDER, [&](TextFieldModel& model) -> void {
        model.SetOnSubmit(onSubmit);
    });
    GetFocus();

    pattern_->PerformAction(TextInputAction::DONE, true);
    EXPECT_FALSE(pattern_->GetCursorVisible());
}

/**
 * @tc.name: KeyEvent009
 * @tc.desc: Test KeyEvent enter
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldKeyEventTest, KeyEvent009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get focus
     */
    auto onSubmit = [](int32_t textFieldKey, NG::TextFieldCommonEvent& commonEvent) {
        commonEvent.SetKeepEditable(true);
        EXPECT_TRUE(commonEvent.keepEditable_);
        EXPECT_EQ(commonEvent.text_, "abcdefghijklmnopqrstuvwxyz");
    };
    CreateTextField(DEFAULT_TEXT, DEFAULT_PLACE_HOLDER, [&](TextFieldModel& model) -> void {
        model.SetInputStyle(DEFAULT_INPUT_STYLE);
        model.SetOnSubmit(onSubmit);
    });
    GetFocus();
    auto focushHub = pattern_->GetFocusHub();
    pattern_->PerformAction(TextInputAction::BEGIN, true);
    EXPECT_TRUE(focushHub->currentFocus_);
}

/**
 * @tc.name: UpdateCaretByTouchMove001
 * @tc.desc: Test UpdateCaretByTouchMove
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, UpdateCaretByTouchMove001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();

    /**
     * @tc.steps: step2. create location info, touch type DOWN
     */
    TouchLocationInfo touchLocationInfo1(0);
    touchLocationInfo1.touchType_ = TouchType::DOWN;
    touchLocationInfo1.localLocation_ = Offset(0.0f, 0.0f);

    /**
     * @tc.steps: step3. create touch info, touch type DOWN
     */
    TouchEventInfo touchInfo1("");
    touchInfo1.AddTouchLocationInfo(std::move(touchLocationInfo1));

    /**
     * @tc.steps: step4. test touch down
     */
    pattern_->HandleTouchEvent(touchInfo1);
    EXPECT_TRUE(pattern_->isTouchCaret_);

    /**
     * @tc.steps: step5. create location info, touch type MOVE
     */
    TouchLocationInfo touchLocationInfo2(0);
    touchLocationInfo2.touchType_ = TouchType::MOVE;
    touchLocationInfo2.localLocation_ = Offset(0.0f, 0.0f);

    /**
     * @tc.steps: step6. create touch info, touch type MOVE
     */
    TouchEventInfo touchInfo2("");
    touchInfo2.AddTouchLocationInfo(std::move(touchLocationInfo2));

    /**
     * @tc.steps: step7. test touch move
     */
    pattern_->HandleTouchEvent(touchInfo2);
    EXPECT_EQ(pattern_->selectController_->GetCaretIndex(), 0);

    /**
     * @tc.steps: step8. create location, touch type info UP
     */
    TouchLocationInfo touchLocationInfo3(0);
    touchLocationInfo3.touchType_ = TouchType::UP;
    touchLocationInfo3.localLocation_ = Offset(0.0f, 0.0f);

    /**
     * @tc.steps: step9. create touch info, touch type UP
     */
    TouchEventInfo touchInfo3("");
    touchInfo3.AddTouchLocationInfo(std::move(touchLocationInfo3));

    /**
     * @tc.steps: step10. test touch up
     */
    pattern_->HandleTouchEvent(touchInfo3);
    EXPECT_FALSE(pattern_->isTouchCaret_);
}

/**
 * @tc.name: CleanNode001
 * @tc.desc: Test UpdateClearNode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, CleanNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetIsShowCancelButton(true);
        model.SetCancelIconSize(Dimension(ICON_SIZE, DimensionUnit::PX));
    });

    /**
     * @tc.steps: step2. Get clear node response area
     */
    auto cleanNodeResponseArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    auto stackNode = cleanNodeResponseArea->cleanNode_;
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(stackNode->GetFirstChild());
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();

    /**
     * @tc.steps: step5. create text inco size
     */
    auto iconSize = Dimension(ICON_SIZE, DimensionUnit::PX);

    /**
     * @tc.steps: step6. test Update clear node true
     */
    cleanNodeResponseArea->UpdateCleanNode(true);
    EXPECT_EQ(imageLayoutProperty->calcLayoutConstraint_->selfIdealSize,
        CalcSize(CalcLength(iconSize), CalcLength(iconSize)));

    /**
     * @tc.steps: step7. test Update clear node false
     */
    cleanNodeResponseArea->UpdateCleanNode(false);
    EXPECT_EQ(imageLayoutProperty->calcLayoutConstraint_->selfIdealSize, CalcSize(CalcLength(0.0), CalcLength(0.0)));
}

/**
 * @tc.name: CleanNode002
 * @tc.desc: Test OnCleanNodeClicked
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, CleanNode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetIsShowCancelButton(true);
        model.SetCancelIconSize(Dimension(ICON_SIZE, DimensionUnit::PX));
    });

    /**
     * @tc.steps: step2. Get clean node response area
     */
    auto cleanNodeResponseArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    ASSERT_NE(cleanNodeResponseArea, nullptr);

    /**
     * @tc.steps: step3. test clean node clicked
     */
    cleanNodeResponseArea->OnCleanNodeClicked();
    EXPECT_EQ(pattern_->GetTextValue(), "");
}

/**
 * @tc.name: RepeatClickCaret
 * @tc.desc: Test RepeatClickCaret
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, RepeatClickCaret, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. Initialize click offset
     */
    Offset clickOffset(0.0f, 0.0f);
    int32_t lastIndex = 0;

    /**
     * @tc.steps: step3. Text input request focus
     */
    auto focusHub = pattern_->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;

    /**
     * @tc.steps: step3. test repeat click caret
     */
    EXPECT_TRUE(pattern_->RepeatClickCaret(clickOffset, lastIndex));
}

/**
 * @tc.name: UpdateFocusForward001
 * @tc.desc: Test UpdateFocusForward
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, UpdateFocusForward001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. Text input request focus.
     */
    GetFocus();

    /**
     * @tc.steps: step3. Test update focus forward when focus index = UNIT.
     */
    pattern_->focusIndex_ = FocuseIndex::UNIT;
    EXPECT_FALSE(pattern_->UpdateFocusForward());
}

/**
 * @tc.name: UpdateFocusForward002
 * @tc.desc: Test UpdateFocusForward
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, UpdateFocusForward002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetIsShowCancelButton(true);
    });

    /**
     * @tc.steps: step2. Text input request focus.
     */
    GetFocus();

    /**
     * @tc.steps: step4. Test update focus forward when focus index = CANCEL.
     */
    pattern_->focusIndex_ = FocuseIndex::CANCEL;
    EXPECT_FALSE(pattern_->UpdateFocusForward());
}

/**
 * @tc.name: UpdateFocusForward003
 * @tc.desc: Test UpdateFocusForward
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, UpdateFocusForward003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize show password icon text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetShowPasswordIcon(true);
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetIsShowCancelButton(true);
    });

    /**
     * @tc.steps: step2. Text input request focus.
     */
    GetFocus();

    /**
     * @tc.steps: step3. Test update focus forward, focus index = CANCEL.
     */
    pattern_->focusIndex_ = FocuseIndex::CANCEL;
    EXPECT_TRUE(pattern_->UpdateFocusForward());
}

/**
 * @tc.name: UpdateFocusForward004
 * @tc.desc: Test UpdateFocusForward
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, UpdateFocusForward004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize show password icon text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetShowPasswordIcon(true);
    });

    /**
     * @tc.steps: step2. Text input request focus.
     */
    GetFocus();

    /**
     * @tc.steps: step3. Test update focus forward when focus index = TEXT.
     */
    pattern_->focusIndex_ = FocuseIndex::TEXT;
    EXPECT_TRUE(pattern_->UpdateFocusForward());
}

/**
 * @tc.name: UpdateFocusBackward001
 * @tc.desc: Test UpdateFocusBackward
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, UpdateFocusBackward001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. Text input request focus.
     */
    GetFocus();

    /**
     * @tc.steps: step3. Test update focus backward when focus index = TEXT.
     */
    pattern_->focusIndex_ = FocuseIndex::TEXT;
    EXPECT_FALSE(pattern_->UpdateFocusBackward());
}

/**
 * @tc.name: UpdateFocusBackward002
 * @tc.desc: Test UpdateFocusBackward
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, UpdateFocusBackward002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetIsShowCancelButton(true);
    });

    /**
     * @tc.steps: step2. Text input request focus.
     */
    GetFocus();

    /**
     * @tc.steps: step3. Test update focus backward when focus index = CANCEL.
     */
    pattern_->focusIndex_ = FocuseIndex::CANCEL;
    EXPECT_TRUE(pattern_->UpdateFocusBackward());
}

/**
 * @tc.name: UpdateFocusBackward003
 * @tc.desc: Test UpdateFocusBackward
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, UpdateFocusBackward003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize show password icon text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetShowPasswordIcon(true);
    });

    /**
     * @tc.steps: step2. Text input request focus
     */
    GetFocus();

    /**
     * @tc.steps: step3. Test update focus backward when focus index = UNIT.
     */
    pattern_->focusIndex_ = FocuseIndex::UNIT;
    EXPECT_TRUE(pattern_->UpdateFocusBackward());
}

/**
 * @tc.name: UpdateFocusBackward004
 * @tc.desc: Test UpdateFocusBackward
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, UpdateFocusBackward004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize show password icon text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetShowPasswordIcon(true);
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
    });

    /**
     * @tc.steps: step2. Text input request focus.
     */
    GetFocus();

    /**
     * @tc.steps: step3. Test update focus backward when focus index = UNIT.
     */
    pattern_->focusIndex_ = FocuseIndex::UNIT;
    EXPECT_TRUE(pattern_->UpdateFocusBackward());
}

/**
 * @tc.name: onDraw001
 * @tc.desc: Verify the onDraw Magnifier.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, onDraw001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. Move handle
     */
    OffsetF localOffset(1.0f, 1.0f);
    pattern_->SetLocalOffset(localOffset);
    RectF handleRect;
    pattern_->OnHandleMove(handleRect, false);

    /**
     * @tc.steps: step3. Craete TextFieldOverlayModifier
     */
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    auto textFieldOverlayModifier = AceType::MakeRefPtr<TextFieldOverlayModifier>(pattern_, scrollEdgeEffect);

    /**
     * @tc.steps: step4. Create DrawingContext
     */
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    DrawingContext context { rsCanvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };

    /**
     * @tc.steps: step5. Do onDraw(context)
     */
    textFieldOverlayModifier->onDraw(context);

    /**
     * @tc.steps: step6. Test magnifier open or close
     * @tc.expected: magnifier is open
     */
    auto ret = pattern_->GetShowMagnifier();
    EXPECT_TRUE(ret);

    /**
     * @tc.steps: step7. When handle move done
     */
    pattern_->OnHandleMoveDone(handleRect, true);

    /**
     * @tc.steps: step8. Test magnifier open or close
     * @tc.expected: magnifier is close
     */
    ret = pattern_->GetShowMagnifier();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ShowMenu001
 * @tc.desc: Test close menu after ShowMenu()
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, ShowMenu001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. Create selectOverlayProxy
     */
    pattern_->ProcessOverlay(true, true, true);

    /**
     * @tc.steps: step3. Do ShowMenu()
     */
    pattern_->ShowMenu();

    /**
     * @tc.steps: step4. Press esc
     */
    KeyEvent event;
    event.code = KeyCode::KEY_ESCAPE;
    pattern_->OnKeyEvent(event);

    /**
     * @tc.steps: step5. Test menu open or close
     * @tc.expected: text menu is close
     */
    auto ret = pattern_->GetSelectOverlayProxy()->IsMenuShow();
    EXPECT_TRUE(ret);

    /**
     * @tc.steps: step6. Show menu when select all value
     */
    pattern_->HandleOnSelectAll(true);
    pattern_->ShowMenu();

    /**
     * @tc.steps: step7. Select all value again
     */
    pattern_->HandleOnSelectAll(true);

    /**
     * @tc.steps: step8. Test menu open or close
     * @tc.expected: text menu is close
     */
    ret = pattern_->GetSelectOverlayProxy()->IsMenuShow();
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step9. emulate Press shift + F10 key event
     */
    event.code = KeyCode::KEY_F10;
    event.pressedCodes.emplace_back(KeyCode::KEY_SHIFT_LEFT);
    event.pressedCodes.emplace_back(KeyCode::KEY_F10);

    /**
     * @tc.steps: step10. call OnKeyEvent
     */
    ret = pattern_->OnKeyEvent(event);
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step11. Inset value
     */
    pattern_->InsertValue("abc");

    /**
     * @tc.steps: step12. Test menu open or close
     * @tc.expected: text menu is close
     */
    ret = pattern_->GetSelectOverlayProxy()->IsMenuShow();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SelectAll001
 * @tc.desc: Test .SelectAll(true)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, SelectAll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. Set .SelectAll(true)
     */
    layoutProperty_->UpdateSelectAllValue(true);

    /**
     * @tc.steps: step3. Get focus by single click
     * @tc.expected: Select all value without handles
     */
    GestureEvent info;
    pattern_->HandleSingleClickEvent(info);
    EXPECT_EQ(pattern_->GetTextSelectController()->GetFirstHandleOffset().GetX(),
        pattern_->GetTextSelectController()->GetSecondHandleOffset().GetX());
}

/**
 * @tc.name: TabGetFocus001
 * @tc.desc: Test select all value when press tab and get focus
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TabGetFocus001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. Get foucs
     */
    GetFocus();

    /**
     * @tc.steps: step3. Get foucs by press tab
     * @tc.expected: Select all value without handles
     */
    KeyEvent event;
    event.code = KeyCode::KEY_TAB;
    pattern_->OnKeyEvent(event);
    EXPECT_EQ(pattern_->GetTextSelectController()->GetFirstHandleOffset().GetX(),
        pattern_->GetTextSelectController()->GetSecondHandleOffset().GetX());
}

/**
 * @tc.name: NeedSoftKeyboard001
 * @tc.desc: Test NeedSoftKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, NeedSoftKeyboard001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. Test whether text field need soft keyboard.
     */
    ASSERT_NE(pattern_, nullptr);
    EXPECT_TRUE(pattern_->NeedSoftKeyboard());
}

/*
 * @tc.name: AdjustWordCursorAndSelect01
 * @tc.desc: Test .adjust word cursor and select(true)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, AdjustWordCursorAndSelect01, TestSize.Level1)
{
    using namespace std::chrono;
    /**
     * @tc.steps: step1. Initialize text input "hello"
     */
    CreateTextField(HELLO_TEXT);
    pattern_->selectController_->lastAiPosTimeStamp_ = high_resolution_clock::now();
    pattern_->lastClickTimeStamp_ = pattern_->selectController_->lastAiPosTimeStamp_ + seconds(2);

    MockDataDetectorMgr mockDataDetectorMgr;
    InitAdjustObject(mockDataDetectorMgr);

    std::string content = pattern_->contentController_->GetTextValue();
    int32_t pos = 3;
    mockDataDetectorMgr.AdjustCursorPosition(
        pos, content, pattern_->selectController_->lastAiPosTimeStamp_, pattern_->lastClickTimeStamp_);
    EXPECT_EQ(pos, 2);

    int32_t start = 1;
    int32_t end = 3;
    mockDataDetectorMgr.AdjustWordSelection(pos, content, start, end);
    EXPECT_EQ(start, 2);
    EXPECT_EQ(end, 3);
    /**
     * @tc.steps: step2. assign text as default text
     */
    pos = 1;
    pattern_->contentController_->SetTextValue(DEFAULT_TEXT);
    content = pattern_->contentController_->GetTextValue();
    mockDataDetectorMgr.AdjustCursorPosition(
        pos, content, pattern_->selectController_->lastAiPosTimeStamp_, pattern_->lastClickTimeStamp_);
    EXPECT_EQ(pos, 4);

    start = 1;
    end = 3;
    mockDataDetectorMgr.AdjustWordSelection(pos, content, start, end);
    EXPECT_EQ(start, 0);
    EXPECT_EQ(end, 2);

    /**
     * @tc.steps: step3. assign text as empty
     */
    pos = 2;
    pattern_->contentController_->Reset();
    content = pattern_->contentController_->GetTextValue();
    mockDataDetectorMgr.AdjustCursorPosition(
        pos, content, pattern_->selectController_->lastAiPosTimeStamp_, pattern_->lastClickTimeStamp_);
    EXPECT_EQ(pos, -1);

    start = 1;
    end = 3;
    mockDataDetectorMgr.AdjustWordSelection(pos, content, start, end);
    EXPECT_EQ(start, -1);
    EXPECT_EQ(end, -1);
}

/**
 * @tc.name: TextFieldFilter001
 * @tc.desc: Test textfield filter.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, TextFieldFilter001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT, "");

    /**
     * @tc.steps: step2. assign filter as lowercase filter
     */
    layoutProperty_->UpdateInputFilter(LOWERCASE_FILTER);
    pattern_->InsertValue("X");
    EXPECT_EQ(pattern_->GetInputFilter(), LOWERCASE_FILTER);
}

/**
 * @tc.name: TextFieldFilter002
 * @tc.desc: Test textfield filter.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, TextFieldFilter002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT, "");

    /**
     * @tc.steps: step2. assign filter as number filter
     */
    layoutProperty_->UpdateInputFilter(NUMBER_FILTER);
    auto numStr = "1";
    pattern_->InsertValue(numStr);
    EXPECT_EQ(pattern_->GetInputFilter(), NUMBER_FILTER);
}

/**
 * @tc.name: TextFieldPatternOnTextInputScroll001
 * @tc.desc: Verify that the AddScrollEvent interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, TextFieldPatternOnTextInputScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. Call the OnTextInputScroll.
     * @tc.expected: step2. Check the value set in OnTextInputScroll.
     */
    layoutProperty_->UpdateMaxLines(2);
    pattern_->OnTextInputScroll(0.0f);
    layoutProperty_->UpdateMaxLines(1);
    pattern_->textRect_.x_ = 10.0f;
    pattern_->textRect_.width_ = 200.0f;
    pattern_->contentRect_.x_ = 20.0f;
    pattern_->contentRect_.width_ = 100.0f;
    pattern_->OnTextInputScroll(-1000.0f);
    pattern_->isSingleHandle_ = false;
    pattern_->OnTextInputScroll(0.0f);
    pattern_->isSingleHandle_ = true;
    pattern_->OnTextInputScroll(0.0f);
    EXPECT_EQ(pattern_->selectController_->GetCaretRect().GetX(), -90.0f);
    EXPECT_EQ(pattern_->textRect_.GetOffset(), OffsetF(pattern_->currentOffset_, pattern_->textRect_.GetY()));
}

/**
 * @tc.name: CreateNodePaintMethod001
 * @tc.desc: Test textfield to create paint.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, CreateNodePaintMethod001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. call CreateNodePaintMethod
     * tc.expected: step2. Check if the value is created.
     */
    auto paint = pattern_->CreateNodePaintMethod();
    EXPECT_NE(pattern_->GetContentModifier(), nullptr);
}

/**
 * @tc.name: CreateNodePaintMethod002
 * @tc.desc: Test textfield to create paint.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, CreateNodePaintMethod002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. call CreateNodePaintMethod
     * tc.expected: step2. Check if the value is created.
     */
    pattern_->SetIsCustomFont(true);
    auto paint = pattern_->CreateNodePaintMethod();
    EXPECT_TRUE(pattern_->textFieldContentModifier_->GetIsCustomFont());
}

/**
 * @tc.name: CreateNodePaintMethod003
 * @tc.desc: Test textfield to create paint.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, CreateNodePaintMethod003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. call CreateNodePaintMethod
     * tc.expected: step2. Check if the value is created.
     */
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();
    EXPECT_TRUE(pattern_->IsNormalInlineState());
    pattern_->UpdateScrollBarOffset();

    auto paint = AceType::DynamicCast<TextFieldPaintMethod>(pattern_->CreateNodePaintMethod());
    auto inlineScrollRect = pattern_->GetScrollBar()->GetActiveRect();
    EXPECT_EQ(inlineScrollRect, Rect(720, 0, 0, 50));
    EXPECT_NE(pattern_->textFieldContentModifier_, nullptr);
}

/**
 * @tc.name: CursorInContentRegion001
 * @tc.desc: Test textfield if the cursor in content.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, CursorInContentRegion001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. call CursorInContentRegion
     * tc.expected: step2. Check the cursor position.
     */
    GetFocus();
    EXPECT_TRUE(pattern_->CursorInContentRegion());
}

/**
 * @tc.name: OffsetInContentRegion
 * @tc.desc: Test textfield if the cursor in content.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, OffsetInContentRegion, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. call CursorInContentRegion
     * tc.expected: step2. Check the offset position.
     */
    EXPECT_TRUE(pattern_->OffsetInContentRegion(Offset(1.0f, 1.0f)));
}

/**
 * @tc.name: OnModifyDone001
 * @tc.desc: Test the OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, OnModifyDone001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. Set showUnderLine. Call function OnModifyDone.
     * @tc.expected: Check the showUnderLine set successfully.
     */
    layoutProperty_->UpdateShowUnderline(true);
    pattern_->OnModifyDone();
    GetFocus();
    EXPECT_TRUE(layoutProperty_->GetShowUnderlineValue(false));
    layoutProperty_->UpdateShowUnderline(false);
    pattern_->OnModifyDone();
    pattern_->HandleBlurEvent();
    GetFocus();
    EXPECT_FALSE(layoutProperty_->GetShowUnderlineValue(false));
    auto focusHub = pattern_->GetFocusHub();
    EXPECT_NE(focusHub->onFocusInternal_, nullptr);
    EXPECT_NE(focusHub->onBlurInternal_, nullptr);
}

/**
 * @tc.name: MaxLength001
 * @tc.desc: test textInput maxLength
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, MaxLength001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default text
     * @tc.expected: maxLength is 1000000
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.step: step2. test  default maxLength.
     */
    EXPECT_EQ(pattern_->GetMaxLength(), 1000000);
}

/**
 * @tc.name: MaxLength002
 * @tc.desc: test textInput maxLength
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, MaxLength002, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with set maxLength 20
     * @tc.expected: maxLength is 20
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetMaxLength(5);
    });
    TextEditingValue value;
    TextSelection selection;
    value.text = "1234567890";
    selection.baseOffset = value.text.length();
    value.selection = selection;
    pattern_->UpdateEditingValue(std::make_shared<TextEditingValue>(value));
    FlushLayoutTask(frameNode_);

    /**
     * @tc.step: step2. test maxLength
     */
    EXPECT_EQ(pattern_->GetTextValue().compare("12345"), 0);
    EXPECT_EQ(pattern_->GetMaxLength(), 5);
}

/**
 * @tc.name: MaxLength003
 * @tc.desc: test testIput maxLength
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, MaxLength003, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with set maxLength 0
     * @tc.expected: maxLength is 0
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetMaxLength(0);
    });
    TextEditingValue value;
    TextSelection selection;
    value.text = "1234567890";
    selection.baseOffset = value.text.length();
    value.selection = selection;
    pattern_->UpdateEditingValue(std::make_shared<TextEditingValue>(value));
    FlushLayoutTask(frameNode_);

    /**
     * @tc.step: step2. test maxLength
     */
    EXPECT_EQ(pattern_->GetTextValue().compare(""), 0);
    EXPECT_EQ(pattern_->GetMaxLength(), 0);
}

/**
 * @tc.name: MaxLength004
 * @tc.desc: test testInput maxLength
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, MaxLength004, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with reset maxLength
     * @tc.expected: maxLength is 1000000
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.ResetMaxLength();
    });

    /**
     * @tc.step: step2. test maxLength
     */
    EXPECT_EQ(pattern_->GetMaxLength(), 1000000);
}

/**
 * @tc.name: MaxLength005
 * @tc.desc: test testInput maxLength
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, MaxLength005, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with set maxLength -1
     * @tc.expected: maxLength is -1
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetMaxLength(-1);
    });
    TextEditingValue value;
    TextSelection selection;
    value.text = "1234567890";
    selection.baseOffset = value.text.length();
    value.selection = selection;
    pattern_->UpdateEditingValue(std::make_shared<TextEditingValue>(value));
    FlushLayoutTask(frameNode_);

    /**
     * @tc.step: step2. test maxLength
     */
    EXPECT_EQ(pattern_->GetTextValue().compare("1234567890"), 0);
    EXPECT_EQ(pattern_->GetMaxLength(), -1);
}

/**
 * @tc.name: MaxLength006
 * @tc.desc: test testInput maxLength
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, MaxLength006, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with set maxLength 1000023
     * @tc.expected: maxLength is 1000023
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetMaxLength(1000023);
    });

    /**
     * @tc.step: step2. test maxLength
     */
    EXPECT_EQ(pattern_->GetMaxLength(), 1000023);
}

/**
 * @tc.name: CopyOption001
 * @tc.desc: test testInput CopyOption
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, CopyOption001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default copyOption
     * @tc.expected: Default CopyOption is Distributed
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.step: step2. test default copyOption
     */
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->AllowCopy(), true);
    EXPECT_EQ(pattern_->GetCopyOptionString(), "CopyOptions.Distributed");
}

/**
 * @tc.name: CopyOption002
 * @tc.desc: test testInput CopyOption
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, CopyOption002, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with set copyOption
     * @tc.expected: CopyOption is Local
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetCopyOption(CopyOptions::Local);
    });

    /**
     * @tc.step: step2. Test CopyOption
     */
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->AllowCopy(), true);
    EXPECT_EQ(pattern_->GetCopyOptionString(), "CopyOptions.Local");
}

/**
 * @tc.name: CopyOption003
 * @tc.desc: test testInput CopyOption
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, CopyOption003, TestSize.Level1)
{
     /**
     * @tc.steps: Create Text filed node with set copyOption
     * @tc.expected: CopyOption is inApp
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetCopyOption(CopyOptions::InApp);
    });

    /**
     * @tc.step: step2. Test CopyOption
     */
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->AllowCopy(), true);
    EXPECT_EQ(pattern_->GetCopyOptionString(), "CopyOptions.InApp");
}

/**
 * @tc.name: CopyOption004
 * @tc.desc: test testInput CopyOption
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, CopyOption004, TestSize.Level1)
{
     /**
     * @tc.steps: Create Text filed node with set copyOption
     * @tc.expected: CopyOption is none
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetCopyOption(CopyOptions::None);
    });

    /**
     * @tc.step: step2. Test CopyOption
     */
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->AllowCopy(), false);
    EXPECT_EQ(pattern_->GetCopyOptionString(), "CopyOptions.None");
}

/**
 * @tc.name: enableAutoFill001
 * @tc.desc: test testInput enableAutoFill
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, enableAutoFill001, TestSize.Level1)
{
     /**
     * @tc.steps: Create Text filed node
     * @tc.expected: enableAutoFill is true
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
    });

    /**
     * @tc.step: step2. Test default enableAutoFill
     */
    pattern_->CheckAutoFill();
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetEnableAutoFill(), true);
}

/**
 * @tc.name: enableAutoFill002
 * @tc.desc: test testInput enableAutoFill
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, enableAutoFill002, TestSize.Level1)
{
     /**
     * @tc.steps: Create Text filed node
     * @tc.expected: enableAutoFill is false
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(false);
    });

    /**
     * @tc.step: step2. Test enableAutoFill
     */
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetEnableAutoFill(), false);
}

/**
 * @tc.name: testMaxLines001
 * @tc.desc: test testInput maxLines
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testMaxLines001, TestSize.Level1)
{
     /**
     * @tc.steps: Create Text filed node
     * @tc.expected: maxLines is 5
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetMaxViewLines(5);
    });

    /**
     * @tc.step: step2. Test maxLines
     */
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetMaxViewLines(), 5);
}

/**
 * @tc.name: testBarState001
 * @tc.desc: test testInput barState
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testBarState001, TestSize.Level1)
{
     /**
     * @tc.steps: Create Text filed node
     * @tc.expected: barState is DisplayMode::OFF
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetBarState(DisplayMode::OFF);
    });

    /**
     * @tc.step: step2. Test barState
     */
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetDisplayMode(), DisplayMode::OFF);
}

/**
 * @tc.name: testBarState002
 * @tc.desc: test testInput barState
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testBarState002, TestSize.Level1)
{
     /**
     * @tc.steps: Create Text filed node
     * @tc.expected: barState is DisplayMode::AUTO
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetBarState(DisplayMode::AUTO);
    });

    /**
     * @tc.step: step2. Test barState
     */
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetDisplayMode(), DisplayMode::AUTO);
}

/**
 * @tc.name: testBarState003
 * @tc.desc: test testInput barState
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testBarState003, TestSize.Level1)
{
     /**
     * @tc.steps: Create Text filed node
     * @tc.expected: barState is DisplayMode::ON
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetBarState(DisplayMode::ON);
    });

    /**
     * @tc.step: step2. Test barState
     */
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetDisplayMode(), DisplayMode::ON);
}

/**
 * @tc.name: testSelectionMenuHidden001
 * @tc.desc: test testInput selectionMenuHidden
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testSelectionMenuHidden001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: selectionMenuHidden is DisplayMode::ON
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetSelectionMenuHidden(false);
    });

    /**
     * @tc.step: step2. Set selectionMenuHidden
     */
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetSelectionMenuHidden(), false);

    /**
     * @tc.step: step3. Set selectionMenuHidden
     */
    layoutProperty_->UpdateSelectionMenuHidden(true);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetSelectionMenuHidden(), true);
}

/**
 * @tc.name: testEnableKeyboardOnFocus001
 * @tc.desc: test testInput EnableKeyboardOnFocus
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testEnableKeyboardOnFocus001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: selectionMenuHidden is true
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.step: step2. default enableKeyboardOnFocus
     */
    pattern_->RequestKeyboardOnFocus();
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->needToRequestKeyboardOnFocus_, true);

    /**
     * @tc.step: step3. Set enableKeyboardOnFocus
     */
    pattern_->SetNeedToRequestKeyboardOnFocus(false);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->needToRequestKeyboardOnFocus_, false);
}

/**
 * @tc.name: testTextAlign001
 * @tc.desc: test testInput textAlign
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testTextAlign001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: textAlign is TextAlign::START
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.step: step2. Set textAlign
     */
    layoutProperty_->UpdateTextAlign(TextAlign::LEFT);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextAlign(), TextAlign::LEFT);

    /**
     * @tc.step: step3. Set textAlign
     */
    layoutProperty_->UpdateTextAlign(TextAlign::RIGHT);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextAlign(), TextAlign::RIGHT);

    /**
     * @tc.step: step4. Set textAlign
     */
    layoutProperty_->UpdateTextAlign(TextAlign::CENTER);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextAlign(), TextAlign::CENTER);

    /**
     * @tc.step: step5. Set textAlign
     */
    layoutProperty_->UpdateTextAlign(TextAlign::JUSTIFY);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextAlign(), TextAlign::JUSTIFY);

    /**
     * @tc.step: step6. Set textAlign
     */
    layoutProperty_->UpdateTextAlign(TextAlign::START);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextAlign(), TextAlign::START);

    /**
     * @tc.step: step7. Set textAlign
     */
    layoutProperty_->UpdateTextAlign(TextAlign::END);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextAlign(), TextAlign::END);
}

/**
 * @tc.name: testShowUnderline001
 * @tc.desc: test testInput showUnderline
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testShowUnderline001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: showUnderline is true
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowUnderline(true);
    });

    /**
     * @tc.step: step2. Set showUnderline
     */
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetShowUnderline(), true);

    /**
     * @tc.step: step2. Set showUnderline
     */
    layoutProperty_->UpdateShowUnderline(false);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetShowUnderline(), false);
}

/**
 * @tc.name: testCaretPosition001
 * @tc.desc: test testInput caretPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testCaretPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: caretPosition is 10
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.step: step2. Set caretPosition
     */
    pattern_->SetCaretPosition(10);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->selectController_->GetCaretIndex(), 10);

    /**
     * @tc.step: step3. Set caretPosition
     */
    pattern_->SetCaretPosition(5);
    TextEditingValue value;
    TextSelection selection;
    value.text = "1234567890987654321";
    selection.baseOffset = value.text.length();
    value.selection = selection;
    pattern_->UpdateEditingValue(std::make_shared<TextEditingValue>(value));
    pattern_->UpdateSelectionOffset();
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->selectController_->GetCaretIndex(), value.text.length());
}

/**
 * @tc.name: testShowPasswordIcon001
 * @tc.desc: test testInput showPasswordIcon
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testShowPasswordIcon001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: showPasswordIcon is false
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowPasswordIcon(false);
    });

    /**
     * @tc.step: step2. Set showPasswordIcon
     */
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->GetCaretUpdateType(), CaretUpdateType::NONE);
    EXPECT_EQ(layoutProperty_->GetShowPasswordIcon(), false);

     /**
     * @tc.step: step3. Set showPasswordIcon
     */
    layoutProperty_->UpdateShowPasswordIcon(true);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetShowPasswordIcon(), true);
}

/**
 * @tc.name: testType001
 * @tc.desc: test testInput type
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testType001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     * @tc.expected: type is TextInputType::TEXT
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.step: step2. Set type
     */
    layoutProperty_->UpdateTextInputType(TextInputType::BEGIN);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextInputType(), TextInputType::BEGIN);

    /**
     * @tc.step: step3. Set type
     */
    layoutProperty_->UpdateTextInputType(TextInputType::UNSPECIFIED);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextInputType(), TextInputType::UNSPECIFIED);

    /**
     * @tc.step: step4. Set type
     */
    layoutProperty_->UpdateTextInputType(TextInputType::TEXT);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextInputType(), TextInputType::TEXT);

    /**
     * @tc.step: step5. Set type
     */
    layoutProperty_->UpdateTextInputType(TextInputType::MULTILINE);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextInputType(), TextInputType::MULTILINE);

    /**
     * @tc.step: step6. Set type
     */
    layoutProperty_->UpdateTextInputType(TextInputType::NUMBER);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextInputType(), TextInputType::NUMBER);

    /**
     * @tc.step: step7. Set type
     */
    layoutProperty_->UpdateTextInputType(TextInputType::PHONE);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextInputType(), TextInputType::PHONE);

    /**
     * @tc.step: step8. Set type
     */
    layoutProperty_->UpdateTextInputType(TextInputType::DATETIME);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextInputType(), TextInputType::DATETIME);

    /**
     * @tc.step: step9. Set type
     */
    layoutProperty_->UpdateTextInputType(TextInputType::EMAIL_ADDRESS);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextInputType(), TextInputType::EMAIL_ADDRESS);

    /**
     * @tc.step: step10. Set type
     */
    layoutProperty_->UpdateTextInputType(TextInputType::URL);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextInputType(), TextInputType::URL);

    /**
     * @tc.step: step11. Set type
     */
    layoutProperty_->UpdateTextInputType(TextInputType::VISIBLE_PASSWORD);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextInputType(), TextInputType::VISIBLE_PASSWORD);

    /**
     * @tc.step: step12. Set type
     */
    layoutProperty_->UpdateTextInputType(TextInputType::END);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetTextInputType(), TextInputType::END);
}

/**
 * @tc.name: testEnterKeyType001
 * @tc.desc: test testInput enterKeyType
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testEnterKeyType001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.step: step2. Set enterKeyType
     */
    pattern_->UpdateTextInputAction(TextInputAction::GO);
    frameNode_->MarkModifyDone();
    EXPECT_STREQ(pattern_->TextInputActionToString().c_str(), "EnterKeyType.Go");

    /**
     * @tc.step: step3. Set enterKeyType
     */
    pattern_->UpdateTextInputAction(TextInputAction::SEARCH);
    frameNode_->MarkModifyDone();
    EXPECT_STREQ(pattern_->TextInputActionToString().c_str(), "EnterKeyType.Search");

    /**
     * @tc.step: step4. Set enterKeyType
     */
    pattern_->UpdateTextInputAction(TextInputAction::SEND);
    frameNode_->MarkModifyDone();
    EXPECT_STREQ(pattern_->TextInputActionToString().c_str(), "EnterKeyType.Send");

    /**
     * @tc.step: step4. Set enterKeyType
     */
    pattern_->UpdateTextInputAction(TextInputAction::DONE);
    frameNode_->MarkModifyDone();
    EXPECT_STREQ(pattern_->TextInputActionToString().c_str(), "EnterKeyType.Done");

    /**
     * @tc.step: step4. Set enterKeyType
     */
    pattern_->UpdateTextInputAction(TextInputAction::NEXT);
    frameNode_->MarkModifyDone();
    EXPECT_STREQ(pattern_->TextInputActionToString().c_str(), "EnterKeyType.Next");

    /**
     * @tc.step: step4. Set enterKeyType
     */
    pattern_->UpdateTextInputAction(TextInputAction::BEGIN);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->GetTextInputActionValue(), TextInputAction::BEGIN);

    /**
     * @tc.step: step4. Set enterKeyType
     */
    pattern_->UpdateTextInputAction(TextInputAction::UNSPECIFIED);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->GetTextInputActionValue(), TextInputAction::UNSPECIFIED);

    /**
     * @tc.step: step4. Set enterKeyType
     */
    pattern_->UpdateTextInputAction(TextInputAction::NONE);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->GetTextInputActionValue(), TextInputAction::NONE);

    /**
     * @tc.step: step4. Set enterKeyType
     */
    pattern_->UpdateTextInputAction(TextInputAction::PREVIOUS);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->GetTextInputActionValue(), TextInputAction::PREVIOUS);

    /**
     * @tc.step: step4. Set enterKeyType
     */
    pattern_->UpdateTextInputAction(TextInputAction::END);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->GetTextInputActionValue(), TextInputAction::END);
}

/**
 * @tc.name: testStyle001
 * @tc.desc: test testInput style
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    CreateTextField(DEFAULT_TEXT);
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();

    /**
     * @tc.step: step2. Set style
     */
    paintProperty->UpdateInputStyle(InputStyle::DEFAULT);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetInputStyle(), InputStyle::DEFAULT);

    /**
     * @tc.step: step3. Set style
     */
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetInputStyle(), InputStyle::INLINE);
}

/**
 * @tc.name: testSelectedBackgroundColor001
 * @tc.desc: test testInput selectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testSelectedBackgroundColor001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR);
    });
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();

    /**
     * @tc.step: step2. Set selectedBackgroundColor
     */
    frameNode_->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::BLUE);

    /**
     * @tc.step: step3. Set selectedBackgroundColor
     */
    paintProperty->UpdateSelectedBackgroundColor(Color::RED);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::RED);
}

/**
 * @tc.name: testCaretStyle001
 * @tc.desc: test testInput caretStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testCaretStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetCaretStyle(DEFAULT_CARET_STYLE);
    });
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();

    /**
     * @tc.step: step2. Set caretStyle
     */
    frameNode_->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetCursorWidth().value().Value(), 3.0);
}

/**
 * @tc.name: ConvertTouchOffsetToCaretPosition001
 * @tc.desc: test testInput caretStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, ConvertTouchOffsetToCaretPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetCaretStyle(DEFAULT_CARET_STYLE);
    });
    GetFocus();

    /**
     * @tc.step: step2. Set caretPosition and call ConvertTouchOffsetToCaretPosition
     */
    pattern_->SetCaretPosition(2);
    int32_t caretPosition = pattern_->ConvertTouchOffsetToCaretPosition(Offset(0.0, 0.0));
    EXPECT_EQ(caretPosition, 0);
    caretPosition = pattern_->ConvertTouchOffsetToCaretPositionNG(Offset(0.0, 0.0));
    EXPECT_EQ(caretPosition, 0);
}

/**
 * @tc.name: HandleOnUndoAction001
 * @tc.desc: test testInput caretStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleOnUndoAction001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.step: step2. Set caretPosition and call ConvertTouchOffsetToCaretPosition
     */
    pattern_->SetCaretPosition(5);
    pattern_->UpdateEditingValueToRecord();
    pattern_->HandleOnUndoAction();
    EXPECT_EQ(pattern_->selectController_->GetCaretIndex(), 0);
}

} // namespace OHOS::Ace::NG
