/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
constexpr float OFFSET = 3;
constexpr int32_t DEFAULT_NODE_ID = 1;
constexpr int32_t MIN_PLATFORM_VERSION = 10;
const std::string DEFAULT_TEXT = "abcdefghijklmnopqrstuvwxyz";
const std::string DEFAULT_TEXT_THREE_LINE = "abcdef\nghijkl\nmnopqr\n";
const std::string HELLO_TEXT = "hello";
const std::string DEFAULT_PLACE_HOLDER = "please input text here";
const std::string LOWERCASE_FILTER = "[a-z]";
const std::string NUMBER_FILTER = "^[0-9]*$";
const std::string DEFAULT_INPUT_FILTER = "[a-z]";
const std::list<std::pair<std::string, int32_t>> FONT_FEATURE_VALUE_1 = ParseFontFeatureSettings("\"ss01\" 1");
const std::list<std::pair<std::string, int32_t>> FONT_FEATURE_VALUE_0 = ParseFontFeatureSettings("\"ss01\" 0");
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
} // namespace

class TextAreaBase : public TestNG {
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

void TextAreaBase::SetUpTestSuite()
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

void TextAreaBase::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
    MockParagraph::TearDown();
}

void TextAreaBase::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
}

void TextAreaBase::ExpectCallParagraphMethods(ExpectParagraphParams params)
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

void TextAreaBase::CreateTextField(
    const std::string& text, const std::string& placeHolder, const std::function<void(TextFieldModelNG&)>& callback)
{
    auto* stack = ViewStackProcessor::GetInstance();
    stack->StartGetAccessRecordingFor(DEFAULT_NODE_ID);
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateTextArea(placeHolder, text);
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

void TextAreaBase::GetFocus()
{
    auto focushHub = pattern_->GetFocusHub();
    focushHub->currentFocus_ = true;
    pattern_->HandleFocusEvent();
    FlushLayoutTask(frameNode_);
}

class TextFieldUXTest : public TextAreaBase {};

/**
 * @tc.name: IsTextArea001
 * @tc.desc: Test is text area or text input.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, IsTextArea001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default text and placeholder
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.expected: Current caret position is end of text
     */
    GetFocus();
    EXPECT_TRUE(pattern_->IsTextArea());
}

/**
 * @tc.name: PerformAction001
 * @tc.desc: Test function PerformAction.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, PerformAction001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default text and placeholder
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.expected: Current caret position is end of text
     */
    GetFocus();

    /**
     * @tc.steps: set TextInputAction NEW_LINE and call PerformAction
     * @tc.expected: text will wrap
     */
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();
    auto textInputAction = pattern_->GetDefaultTextInputAction();
    EXPECT_EQ(textInputAction, TextInputAction::NEW_LINE);
    pattern_->focusIndex_ = FocuseIndex::TEXT;
    EXPECT_TRUE(pattern_->IsTextArea());
    EXPECT_TRUE(pattern_->GetInputFilter() != "\n");
    pattern_->PerformAction(textInputAction, false);
    EXPECT_EQ(pattern_->TextInputActionToString(), "EnterKeyType.Done");
}

/**
 * @tc.name: CursorInContentRegion001
 * @tc.desc: Test function CursorInContentRegion.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, CursorInContentRegion001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default text and placeholder
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.expected: Cursor realy in the content region
     */
    GetFocus();
    EXPECT_EQ(pattern_->GetTextOrPlaceHolderFontSize(), FONT_SIZE);
    EXPECT_TRUE(pattern_->CursorInContentRegion());
}

/**
 * @tc.name: OnTextAreaScroll001
 * @tc.desc: Test textfield to create paint.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, OnTextAreaScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. call OnTextAreaScroll
     * tc.expected: step2. Check if the currentOffset_ is right.
     */
    auto accessibilityProperty = frameNode_->GetAccessibilityProperty<AccessibilityProperty>();
    EXPECT_TRUE(accessibilityProperty->ActActionScrollForward());

    /**
     * @tc.steps: step3.set contentRect_.GetY() = 1
     */
    pattern_->contentRect_ = RectF(1.0f, 1.0f, 1.0f, 1.0f);
    FlushLayoutTask(frameNode_);
    pattern_->OnTextAreaScroll(OFFSET);
    EXPECT_EQ(pattern_->currentOffset_, 1);
}

/**
 * @tc.name: CursorOperation001
 * @tc.desc: Test cursor move
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, CursorOperation001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node with three lines of text.
     */
    CreateTextField(DEFAULT_TEXT_THREE_LINE);

    /**
     * @tc.expected: Current caret position at 2nd line.
     */
    GetFocus();
    auto controller = pattern_->GetTextSelectController();
    controller->UpdateCaretIndex(10);
    EXPECT_EQ(pattern_->GetCaretIndex(), 10);

    /**
     * @tc.steps: set InputOperation CURSOR_UP and call BeforeCreateLayoutWrapper
     * @tc.expected: caret will move up
     */
    pattern_->inputOperations_.push(InputOperation::CURSOR_UP);
    auto ret = pattern_->CursorMoveUp();
    EXPECT_FALSE(ret);
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(pattern_->GetCaretIndex(), 0);
}

/**
 * @tc.name: CursorOperation002
 * @tc.desc: Test cursor move
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, CursorOperation002, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node with three lines of text.
     */
    CreateTextField(DEFAULT_TEXT_THREE_LINE);

    /**
     * @tc.expected: Current caret position at 2nd line.
     */
    GetFocus();
    auto controller = pattern_->GetTextSelectController();
    controller->UpdateCaretIndex(10);
    EXPECT_EQ(pattern_->GetCaretIndex(), 10);

    /**
     * @tc.steps: set InputOperation CURSOR_DOWN and call BeforeCreateLayoutWrapper
     * @tc.expected: caret will move down
     */
    pattern_->inputOperations_.push(InputOperation::CURSOR_DOWN);
    auto ret = pattern_->CursorMoveDown();
    EXPECT_FALSE(ret);
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(pattern_->GetCaretIndex(), 0);
}

/**
 * @tc.name: CursorOperation003
 * @tc.desc: Test cursor move
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, CursorOperation003, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node with three lines of text.
     */
    CreateTextField(DEFAULT_TEXT_THREE_LINE);

    /**
     * @tc.expected: Current caret position at 2nd line.
     */
    GetFocus();
    auto controller = pattern_->GetTextSelectController();
    controller->UpdateCaretIndex(10);
    EXPECT_EQ(pattern_->GetCaretIndex(), 10);

    /**
     * @tc.steps: set InputOperation CURSOR_LEFT and call BeforeCreateLayoutWrapper
     * @tc.expected: caret will move left
     */
    pattern_->inputOperations_.push(InputOperation::CURSOR_LEFT);
    auto ret = pattern_->CursorMoveLeft();
    EXPECT_FALSE(ret);
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(pattern_->GetCaretIndex(), 8);
}

/**
 * @tc.name: CursorOperation004
 * @tc.desc: Test cursor move
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, CursorOperation004, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node with three lines of text.
     */
    CreateTextField(DEFAULT_TEXT_THREE_LINE);

    /**
     * @tc.expected: Current caret position at 2nd line.
     */
    GetFocus();
    auto controller = pattern_->GetTextSelectController();
    controller->UpdateCaretIndex(10);
    EXPECT_EQ(pattern_->GetCaretIndex(), 10);

    /**
     * @tc.steps: set InputOperation CURSOR_RIGHT and call BeforeCreateLayoutWrapper
     * @tc.expected: caret will move right
     */
    pattern_->inputOperations_.push(InputOperation::CURSOR_RIGHT);
    auto ret = pattern_->CursorMoveRight();
    EXPECT_FALSE(ret);
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(pattern_->GetCaretIndex(), 12);
}

/**
 * @tc.name: CursorOperation004
 * @tc.desc: Test delete text with ControllerSelected.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, DeleteTextWithControllerSelected001, TestSize.Level1)
{
    /**
     * @tc.steps: Initialize text input node and call delete backward
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: getFocus and set controller
     * @tc.steps: firsthandle 5 secondhandle 10
     */
    GetFocus();
    pattern_->HandleSetSelection(5, 10, false);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: call DeleteBackward
     * @tc.expected: text will be reduced by five characters
     */
    pattern_->DeleteBackward(5);
    EXPECT_EQ(pattern_->GetTextValue().compare("abcdeklmnopqrstuvwxyz"), 0) << "Text is " + pattern_->GetTextValue();
    EXPECT_EQ(pattern_->GetCaretIndex(), 5);
}

/**
 * @tc.name: InitSurfaceChangedCallback001
 * @tc.desc: Test init syrface change and callback.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, InitSurfaceChangedCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: Create textfield node
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.expected: Verify is the callback successful
     */
    GetFocus();
    FlushLayoutTask(frameNode_);
    pattern_->HandleSurfaceChanged(0, 0, 0, 0);
    EXPECT_NE(pattern_->surfaceChangedCallbackId_, std::nullopt);
    EXPECT_TRUE(pattern_->HasSurfaceChangedCallback());

    /**
     * @tc.expected: set selectOverlay
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
    pattern_->ProcessOverlay();
    pattern_->HandleSurfaceChanged(0, 0, 0, 0);
}

/**
 * @tc.name: TextAreaLetterSpacing001
 * @tc.desc: test TextArea letterSpacing.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TextAreaLetterSpacing001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default text and placeholder
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetLetterSpacing(1.0_fp);
    });

    /**
     * @tc.expected: Current caret position is end of text
     */
    GetFocus();

    /**
     * @tc.steps: set TextInputAction NEW_LINE and call PerformAction
     * @tc.expected: text will wrap
     */
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();
    auto textInputAction = pattern_->GetDefaultTextInputAction();
    EXPECT_EQ(textInputAction, TextInputAction::NEW_LINE);
    pattern_->focusIndex_ = FocuseIndex::TEXT;
    EXPECT_TRUE(pattern_->IsTextArea());
    EXPECT_TRUE(pattern_->GetInputFilter() != "\n");
    pattern_->PerformAction(textInputAction, false);

    EXPECT_EQ(layoutProperty_->GetLetterSpacing(), 1.0_fp);
}

/**
 * @tc.name: TextAreaLineHeight001
 * @tc.desc: test TextArea lineHeight.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TextAreaLineHeight001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default text and placeholder
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetLineHeight(2.0_fp);
    });

    /**
     * @tc.expected: Current caret position is end of text
     */
    GetFocus();

    /**
     * @tc.steps: set TextInputAction NEW_LINE and call PerformAction
     * @tc.expected: text will wrap
     */
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();
    auto textInputAction = pattern_->GetDefaultTextInputAction();
    EXPECT_EQ(textInputAction, TextInputAction::NEW_LINE);
    pattern_->focusIndex_ = FocuseIndex::TEXT;
    EXPECT_TRUE(pattern_->IsTextArea());
    EXPECT_TRUE(pattern_->GetInputFilter() != "\n");
    pattern_->PerformAction(textInputAction, false);

    EXPECT_EQ(layoutProperty_->GetLineHeight(), 2.0_fp);
}

/**
 * @tc.name: TextAreaTextDecoration001
 * @tc.desc: test TextArea decoration001.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TextAreaTextDecoration001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default text and placeholder
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDecoration(TextDecoration::LINE_THROUGH);
        model.SetTextDecorationColor(Color::BLUE);
        model.SetTextDecorationStyle(TextDecorationStyle::DOTTED);
    });

    /**
     * @tc.expected: Current caret position is end of text
     */
    GetFocus();

    /**
     * @tc.steps: set TextInputAction NEW_LINE and call PerformAction
     * @tc.expected: text will wrap
     */
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();
    auto textInputAction = pattern_->GetDefaultTextInputAction();
    EXPECT_EQ(textInputAction, TextInputAction::NEW_LINE);
    pattern_->focusIndex_ = FocuseIndex::TEXT;
    EXPECT_TRUE(pattern_->IsTextArea());
    EXPECT_TRUE(pattern_->GetInputFilter() != "\n");
    pattern_->PerformAction(textInputAction, false);

    EXPECT_EQ(layoutProperty_->GetTextDecoration(), TextDecoration::LINE_THROUGH);
    EXPECT_EQ(layoutProperty_->GetTextDecorationColor(), Color::BLUE);
    EXPECT_EQ(layoutProperty_->GetTextDecorationStyle(), TextDecorationStyle::DOTTED);
}

/**
 * @tc.name: InitSurfacePositionChangedCallback001
 * @tc.desc: Test init syrface Position change and callback.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, InitSurfacePositionChangedCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: Create textfield node
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.expected: Verify is the callback successful
     */
    GetFocus();
    FlushLayoutTask(frameNode_);
    pattern_->HandleSurfacePositionChanged(1, 1);
    EXPECT_NE(pattern_->surfacePositionChangedCallbackId_, std::nullopt);
    EXPECT_TRUE(pattern_->HasSurfacePositionChangedCallback());
}

/**
 * @tc.name: OnHandleMove004
 * @tc.desc: Test get Select HandleInfo.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, OnHandleMove004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. Call ProcessOverlay.
     */
    pattern_->ProcessOverlay();

    /**
     * @tc.steps: step2. set two handle and call OnHandleMove
     * tc.expected: step2. Check if the value is created.
     */
    pattern_->HandleSetSelection(5, 10, false);
    pattern_->SetIsSingleHandle(false);
    RectF handleRect;
    pattern_->selectOverlay_->OnHandleMove(handleRect, true);
}


/**
 * @tc.name: HandleSelect001
 * @tc.desc: Test the caret move upAndDown
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleSelect001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Initialize text input and Move the handles and then do handle selection.
     */
    int32_t start = 5;
    int32_t end = 10;
    CreateTextField(DEFAULT_TEXT, DEFAULT_PLACE_HOLDER);

    /**
     * @tc.steps: Move the handles and selection up.
     *            Verify the selection data.
     */
    EXPECT_TRUE(pattern_->IsTextArea());
    pattern_->HandleSetSelection(start, end, false);
    pattern_->HandleSelect(CaretMoveIntent::Up);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, start);
    EXPECT_EQ(pattern_->selectController_->GetSecondHandleInfo().index, 0);

    /**
     * @tc.steps: Move the handles and selection down.
     *            Verify the selection data.
     */
    EXPECT_TRUE(pattern_->IsTextArea());
    pattern_->HandleSetSelection(start, end, false);
    pattern_->HandleSelect(CaretMoveIntent::Down);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, start);
    EXPECT_EQ(pattern_->selectController_->GetSecondHandleInfo().index, 26);
}

/**
 * @tc.name: HandleSelect002
 * @tc.desc: Test the caret move right
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, HandleSelect002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: Move the handles and selection Right.
     *            Verify the selection data.
     */
    pattern_->HandleSelect(CaretMoveIntent::Right);
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, 26);
    EXPECT_EQ(pattern_->selectController_->GetSecondHandleInfo().index, 26);
}

/**
 * @tc.name: SetSelectionFlag001
 * @tc.desc: Test SetSelectionFlag
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, SetSelectionFlag001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    auto start = 5;
    auto end = 5;
    CreateTextField(DEFAULT_TEXT);
    pattern_->SetSelectionFlag(start, end);

    /**
     * @tc.steps: set start = end, Verify the caret position.
     */
    GetFocus();
    pattern_->SetSelectionFlag(start, end);
    EXPECT_EQ(pattern_->selectController_->GetCaretIndex(), 5);

    /**
     * @tc.steps: set start != end, Verify the caret position.
     */
    GetFocus();
    end = 10;
    pattern_->SetSelectionFlag(start, end);
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, 5);
    EXPECT_EQ(pattern_->selectController_->GetSecondHandleInfo().index, 5);
}

/**
 * @tc.name: SelectTextShowMenu001
 * @tc.desc: Test show menu after SetTextSelection()
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, SelectTextShowMenu001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. Set menuPolicy to be MenuPolicy::SHOW
     */
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::SHOW;
    pattern_->SetSelectionFlag(0, DEFAULT_TEXT.length(), options);

    /**
     * @tc.steps: step3. Test menu open or close
     * @tc.expected: text menu is open
     */
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_TRUE(ret);

    /**
     * @tc.steps: step4. Press esc
     */
    KeyEvent event;
    event.code = KeyCode::KEY_ESCAPE;
    pattern_->OnKeyEvent(event);

    /**
     * @tc.steps: step5. Set menuPolicy to be MenuPolicy::HIDE
     */
    options.menuPolicy = MenuPolicy::HIDE;
    pattern_->SetSelectionFlag(0, DEFAULT_TEXT.length(), options);

    /**
     * @tc.steps: step6. Test menu open or close
     * @tc.expected: text menu is close
     */
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step7. Press esc
     */
    event.code = KeyCode::KEY_ESCAPE;
    pattern_->OnKeyEvent(event);

    /**
     * @tc.steps: step8. Set menuPolicy to be MenuPolicy::DEFAULT
     */
    options.menuPolicy = MenuPolicy::DEFAULT;
    pattern_->SetSelectionFlag(0, DEFAULT_TEXT.length(), options);

    /**
     * @tc.steps: step9. Test menu open or close
     * @tc.expected: text menu is close
     */
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: OnBackPressed001
 * @tc.desc: Test OnBackPressed
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, OnBackPressed001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: call OnBackPressed.
     */
    pattern_->HandleSetSelection(5, 10, false);
    EXPECT_FALSE(pattern_->OnBackPressed());
}

/**
 * @tc.name: TextAreaMinFontSize001
 * @tc.desc: test TextArea minFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TextAreaMinFontSize001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node with default text and placeholder
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetAdaptMinFontSize(1.0_fp);
    });

    /**
     * @tc.expected: Current caret position is end of text
     */
    GetFocus();

    /**
     * @tc.steps: set TextInputAction NEW_LINE and call PerformAction
     * @tc.expected: text will wrap
     */
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();
    auto textInputAction = pattern_->GetDefaultTextInputAction();
    EXPECT_EQ(textInputAction, TextInputAction::NEW_LINE);
    pattern_->focusIndex_ = FocuseIndex::TEXT;
    EXPECT_TRUE(pattern_->IsTextArea());
    EXPECT_TRUE(pattern_->GetInputFilter() != "\n");
    pattern_->PerformAction(textInputAction, false);

    EXPECT_EQ(layoutProperty_->GetAdaptMinFontSize(), 1.0_fp);
}

/**
 * @tc.name: TextAreaMaxFontSize001
 * @tc.desc: test TextArea maxFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TextAreaMaxFontSize001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node with default text and placeholder
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetAdaptMaxFontSize(2.0_fp);
    });

    /**
     * @tc.expected: Current caret position is end of text
     */
    GetFocus();

    /**
     * @tc.steps: set TextInputAction NEW_LINE and call PerformAction
     * @tc.expected: text will wrap
     */
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();
    auto textInputAction = pattern_->GetDefaultTextInputAction();
    EXPECT_EQ(textInputAction, TextInputAction::NEW_LINE);
    pattern_->focusIndex_ = FocuseIndex::TEXT;
    EXPECT_TRUE(pattern_->IsTextArea());
    EXPECT_TRUE(pattern_->GetInputFilter() != "\n");
    pattern_->PerformAction(textInputAction, false);

    EXPECT_EQ(layoutProperty_->GetAdaptMaxFontSize(), 2.0_fp);
}

/**
 * @tc.name: TextAreaHeightAdaptivePolicy001
 * @tc.desc: test TextArea heightAdaptivePolicy.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TextAreaHeightAdaptivePolicy001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node with default text and placeholder
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetHeightAdaptivePolicy(TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST);
    });

    /**
     * @tc.expected: Current caret position is end of text
     */
    GetFocus();

    /**
     * @tc.steps: set TextInputAction NEW_LINE and call PerformAction
     * @tc.expected: text will wrap
     */
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();
    auto textInputAction = pattern_->GetDefaultTextInputAction();
    EXPECT_EQ(textInputAction, TextInputAction::NEW_LINE);
    pattern_->focusIndex_ = FocuseIndex::TEXT;
    EXPECT_TRUE(pattern_->IsTextArea());
    EXPECT_TRUE(pattern_->GetInputFilter() != "\n");
    pattern_->PerformAction(textInputAction, false);

    EXPECT_EQ(layoutProperty_->GetHeightAdaptivePolicy(), TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST);
    layoutProperty_->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::MAX_LINES_FIRST);
    EXPECT_EQ(layoutProperty_->GetHeightAdaptivePolicy(), TextHeightAdaptivePolicy::MAX_LINES_FIRST);
    layoutProperty_->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST);
    EXPECT_EQ(layoutProperty_->GetHeightAdaptivePolicy(), TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST);
}

/**
 * @tc.name: TextInputTypeToString001
 * @tc.desc: Test TextInputTypeToString
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TextInputTypeToString001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize show number icon text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::NUMBER);
    });

    /**
     * @tc.steps: step2. Call TextInputTypeToString.
     */
    EXPECT_EQ(pattern_->TextInputTypeToString(), "TextAreaType.NUMBER");
}

/**
 * @tc.name: TextInputTypeToString002
 * @tc.desc: Test TextInputTypeToString
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TextInputTypeToString002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize show number icon text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::EMAIL_ADDRESS);
    });

    /**
     * @tc.steps: step2. Call TextInputTypeToString.
     */
    EXPECT_EQ(pattern_->TextInputTypeToString(), "TextAreaType.EMAIL");
}

/**
 * @tc.name: TextInputTypeToString003
 * @tc.desc: Test TextInputTypeToString
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TextInputTypeToString003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize show number icon text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });

    /**
     * @tc.steps: step2. Call TextInputTypeToString.
     */
    EXPECT_EQ(pattern_->TextInputTypeToString(), "InputType.Password");
}

/**
 * @tc.name: TextInputTypeToString004
 * @tc.desc: Test TextInputTypeToString
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TextInputTypeToString004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize show number icon text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::USER_NAME);
    });

    /**
     * @tc.steps: step2. Call TextInputTypeToString.
     */
    EXPECT_EQ(pattern_->TextInputTypeToString(), "InputType.USER_NAME");
}

/**
 * @tc.name: TextInputTypeToString005
 * @tc.desc: Test TextInputTypeToString
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TextInputTypeToString005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize show number icon text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::NEW_PASSWORD);
    });

    /**
     * @tc.steps: step2. Call TextInputTypeToString.
     */
    EXPECT_EQ(pattern_->TextInputTypeToString(), "InputType.NEW_PASSWORD");
}

/**
 * @tc.name: AreaSupportAvoidanceTest
 * @tc.desc: test whether the custom keyboard supports the collision avoidance function
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, AreaSupportAvoidanceTest, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT_THREE_LINE);
    auto supportAvoidance = true;
    pattern_->SetCustomKeyboardOption(supportAvoidance);
    EXPECT_TRUE(pattern_->keyboardAvoidance_);
    supportAvoidance = false;
    pattern_->SetCustomKeyboardOption(supportAvoidance);
    EXPECT_FALSE(pattern_->keyboardAvoidance_);
}

/**
 * @tc.name: TextFieldFontFeatureTest
 * @tc.desc: Test the caret move right
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, FontFeature001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text area.
     */
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateTextArea(DEFAULT_TEXT, "");

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    textFieldModelNG.SetFontFeature(FONT_FEATURE_VALUE_0);
    EXPECT_EQ(layoutProperty->GetFontFeature(), FONT_FEATURE_VALUE_0);

    layoutProperty->UpdateFontFeature(ParseFontFeatureSettings("\"ss01\" 1"));
    TextFieldModelNG::SetFontFeature(frameNode, FONT_FEATURE_VALUE_0);
    EXPECT_EQ(layoutProperty->GetFontFeature(), FONT_FEATURE_VALUE_0);
}

/**
 * @tc.name: TextFieldFontFeatureTest
 * @tc.desc: Test the caret move right
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, FontFeature002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text area.
     */
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateTextArea(DEFAULT_TEXT, "");

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    textFieldModelNG.SetFontFeature(FONT_FEATURE_VALUE_1);
    EXPECT_EQ(layoutProperty->GetFontFeature(), FONT_FEATURE_VALUE_1);

    layoutProperty->UpdateFontFeature(ParseFontFeatureSettings("\"ss01\" 0"));
    TextFieldModelNG::SetFontFeature(frameNode, FONT_FEATURE_VALUE_1);
    EXPECT_EQ(layoutProperty->GetFontFeature(), FONT_FEATURE_VALUE_1);
}

/**
 * @tc.name: TextAreaInputRectUpdate001
 * @tc.desc: Test TextAreaInputRectUpdate
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TextAreaInputRectUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text area.
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. Update text align.
     */
    layoutProperty_->UpdateTextAlign(TextAlign::START);
    RectF textAreaRect = RectF(2.0f, 2.0f, 2.0f, 2.0f);
    pattern_->TextAreaInputRectUpdate(textAreaRect);
    EXPECT_EQ(textAreaRect, RectF(2.0f, 2.0f, 0.0f, 2.0f));
}

/**
 * @tc.name: TextAreaInputRectUpdate002
 * @tc.desc: Test TextAreaInputRectUpdate
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TextAreaInputRectUpdate002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text area.
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. Update text align.
     */
    layoutProperty_->UpdateTextAlign(TextAlign::CENTER);
    RectF textAreaRect = RectF(2.0f, 2.0f, 2.0f, 2.0f);
    pattern_->TextAreaInputRectUpdate(textAreaRect);
    EXPECT_EQ(textAreaRect, RectF(232.0f, 2.0f, 0.0f, 2.0f));
}

/**
 * @tc.name: TextAreaInputRectUpdate003
 * @tc.desc: Test TextAreaInputRectUpdate
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TextAreaInputRectUpdate003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text area.
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. Update text align.
     */
    layoutProperty_->UpdateTextAlign(TextAlign::END);
    RectF textAreaRect = RectF(2.0f, 2.0f, 2.0f, 2.0f);
    pattern_->TextAreaInputRectUpdate(textAreaRect);
    EXPECT_EQ(textAreaRect, RectF(462.0f, 2.0f, 0.0f, 2.0f));

    layoutProperty_->UpdateTextAlign(TextAlign::LEFT);
    EXPECT_EQ(textAreaRect, RectF(462.0f, 2.0f, 0.0f, 2.0f));
}

/**
 * @tc.name: TextIsEmptyRect001
 * @tc.desc: Test TextAreaInputRectUpdate
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TextIsEmptyRect001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text area.
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. call TextIsEmptyRect.
     */
    RectF textAreaRect = RectF(2.0f, 2.0f, 2.0f, 2.0f);
    pattern_->TextIsEmptyRect(textAreaRect);
    EXPECT_EQ(textAreaRect, RectF(0.0f, 0.0f, 0.0f, 50.0f));
}

/**
 * @tc.name: testWordBreak001
 * @tc.desc: test testArea text WordBreak
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TextAreaWordBreak001, TestSize.Level1)
{
    /**
     * @tc.step1: Create Text filed node with default text and placeholder
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.step: step2. Set wordBreak NORMAL
     */
    layoutProperty_->UpdateWordBreak(WordBreak::NORMAL);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetWordBreak(), WordBreak::NORMAL);

    /**
     * @tc.step: step3. Set wordBreak BREAK_ALL
     */
    layoutProperty_->UpdateWordBreak(WordBreak::BREAK_ALL);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetWordBreak(), WordBreak::BREAK_ALL);

    /**
     * @tc.step: step4. Set wordBreak BREAK_WORD
     */
    layoutProperty_->UpdateWordBreak(WordBreak::BREAK_WORD);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(layoutProperty_->GetWordBreak(), WordBreak::BREAK_WORD);
}

/**
 * @tc.name: TextAreaLineSpacing001
 * @tc.desc: test TextArea lineSpacing.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TextAreaLineSpacing001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default text and placeholder
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetLineSpacing(2.0_fp);
    });

    /**
     * @tc.expected: Current caret position is end of text
     */
    GetFocus();

    /**
     * @tc.steps: set TextInputAction NEW_LINE and call PerformAction
     * @tc.expected: text will wrap
     */
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();
    auto textInputAction = pattern_->GetDefaultTextInputAction();
    EXPECT_EQ(textInputAction, TextInputAction::NEW_LINE);
    pattern_->focusIndex_ = FocuseIndex::TEXT;
    EXPECT_TRUE(pattern_->IsTextArea());
    EXPECT_TRUE(pattern_->GetInputFilter() != "\n");
    pattern_->PerformAction(textInputAction, false);

    EXPECT_EQ(layoutProperty_->GetLineSpacing(), 2.0_fp);
}
}
