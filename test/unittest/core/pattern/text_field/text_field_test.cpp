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

#include <optional>
#include <string>
#include <utility>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"

#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "core/common/ime/text_input_type.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/scroll/scroll_bar_theme.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components/theme/theme_manager.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/event/key_event.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

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

using TextFiledModelUpdater = std::function<void(TextFieldModelNG&)>;

class TextFieldTestBase : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;

protected:
    RefPtr<FrameNode> CreateTextFieldNode(int32_t id, std::string text, std::string placeHolder, bool isTextArea,
        TextFiledModelUpdater&& modelUpdater = nullptr);
    void CreateOrUpdate(int32_t id, std::string text, std::string placeHolder, bool isTextArea,
        TextFiledModelUpdater&& modelUpdater = nullptr);
    RefPtr<FrameNode> frameNode_;
    RefPtr<TextFieldPattern> pattern_;
    RefPtr<MockThemeManager> mockThemeManager_ = AceType::MakeRefPtr<MockThemeManager>();
    int32_t id_ = -1;
    std::string text_ = "abcedefghijklmnopqrstuvwxyz";
    std::string placeHolder_ = "abcedefghijklmnopqrstuvwxyz";
};

void TextFieldTestBase::SetUpTestSuite()
{
    MockContainer::SetUp();
    MockPipelineBase::SetUp();
    MockPipelineBase::GetCurrent()->SetRootSize(500, 500);
    MockPipelineBase::GetCurrent()->rootNode_ =
        FrameNode::CreateFrameNodeWithTree(V2::ROOT_ETS_TAG, 0, AceType::MakeRefPtr<RootPattern>());
    MockPipelineBase::GetCurrent()->SetTextFieldManager(AceType::MakeRefPtr<TextFieldManagerNG>());
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
}

void TextFieldTestBase::TearDownTestSuite()
{
    MockContainer::TearDown();
    MockPipelineBase::TearDown();
}

void TextFieldTestBase::SetUp()
{
    MockPipelineBase::GetCurrent()->SetThemeManager(mockThemeManager_);
    auto textFieldTheme = AceType::MakeRefPtr<TextFieldTheme>();
    textFieldTheme->iconSize_ = Dimension(24, DimensionUnit::VP);
    textFieldTheme->iconHotZoneSize_ = Dimension(40, DimensionUnit::VP);
    textFieldTheme->fontSize_ = Dimension(16, DimensionUnit::FP);
    textFieldTheme->fontWeight_ = FontWeight::W400;
    textFieldTheme->textColor_ = Color::FromString("#ff182431");

    EXPECT_CALL(*mockThemeManager_, GetTheme(_))
        .WillRepeatedly([this, textFieldTheme = textFieldTheme](ThemeType type) -> RefPtr<Theme> {
            if (type == ScrollBarTheme::TypeId()) {
                return AceType::MakeRefPtr<ScrollBarTheme>();
            }
            return textFieldTheme;
        });
    CreateOrUpdate(1, text_, placeHolder_, false);
}

void TextFieldTestBase::TearDown()
{
    ElementRegister::GetInstance()->Clear();
    auto* stack = ViewStackProcessor::GetInstance();
    while (!stack->elementsStack_.empty()) {
        stack->elementsStack_.pop();
    }
}

RefPtr<FrameNode> TextFieldTestBase::CreateTextFieldNode(
    int32_t id, std::string text, std::string placeHolder, bool isTextArea, TextFiledModelUpdater&& modelUpdater)
{
    auto* stack = ViewStackProcessor::GetInstance();
    stack->StartGetAccessRecordingFor(id);
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateNode(placeHolder, text, isTextArea);
    if (modelUpdater) {
        modelUpdater(textFieldModelNG);
    }
    stack->StopGetAccessRecording();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    stack->elementsStack_.pop();
    ElementRegister::GetInstance()->AddUINode(frameNode);
    return frameNode;
}

void TextFieldTestBase::CreateOrUpdate(
    int32_t id, std::string text, std::string placeHolder, bool /*isTextArea*/, TextFiledModelUpdater&& modelUpdater)
{
    frameNode_ = CreateTextFieldNode(1, text, placeHolder, false, std::move(modelUpdater));
    ASSERT_NE(frameNode_, nullptr);
    pattern_ = frameNode_->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern_, nullptr);
    pattern_->OnModifyDone();
    id_ = frameNode_->GetId();
}

namespace CaretTest {
class TextFieldCaretTest : public TextFieldTestBase {};

/**
 * @tc.name: CaretPosition001
 * @tc.desc: Test caret position on TextFieldModelNG::CreateNode.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCaretTest, CaretPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: Check caret position when the text is unchanged.
     * @tc.expected: Previous caret position is same as the current.
     */
    ASSERT_NE(pattern_, nullptr);
    auto prevCaretPosition = pattern_->GetTextEditingValue().GetWideText().length() / 2;
    pattern_->SetCaretPosition(prevCaretPosition);

    CreateOrUpdate(id_, text_, placeHolder_, false);
    auto currentCaretPosition = pattern_->GetTextEditingValue().caretPosition;
    EXPECT_EQ(prevCaretPosition, currentCaretPosition) << "caret position should not change when text unchanged";

    /**
     * @tc.steps: Check caret position when the text is changed.
     * @tc.expected: Previous caret position is not same as the current.
     */
    auto newText = text_ + "_new";
    CreateOrUpdate(id_, newText, placeHolder_, false);
    currentCaretPosition = pattern_->GetTextEditingValue().caretPosition;
    EXPECT_NE(prevCaretPosition, currentCaretPosition) << "caret position should update when text changed";
    auto actualCaretPosition = StringUtils::ToWstring(newText).length();
    EXPECT_EQ(actualCaretPosition, currentCaretPosition)
        << "caret position should be at the end of the text when text changed";
}

/**
 * @tc.name: CaretPosition002
 * @tc.desc: Test caret position on SetType.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCaretTest, CaretPosition002, TestSize.Level1)
{
    /**
     * @tc.steps: Check caret position after call SetType.
     * @tc.expected: caret position is same as the expected.
     */
    auto textLength = pattern_->GetTextEditingValue().GetWideText().length();
    auto caretPosition = pattern_->GetTextEditingValue().caretPosition;
    EXPECT_EQ(textLength, caretPosition) << "default input type";

    std::string text = "openharmony@huawei.com+*0123456789";
    std::vector<TestItem<TextInputType, int32_t>> testItems;
    testItems.emplace_back(TextInputType::TEXT, 34, "TextInputType::TEXT");
    testItems.emplace_back(TextInputType::NUMBER, 10, "TextInputType::NUMBER");
    testItems.emplace_back(TextInputType::PHONE, 12, "TextInputType::PHONE");
    testItems.emplace_back(TextInputType::EMAIL_ADDRESS, 32, "TextInputType::EMAIL_ADDRESS");
    testItems.emplace_back(TextInputType::VISIBLE_PASSWORD, 34, "TextInputType::VISIBLE_PASSWORD");
    for (auto testItem : testItems) {
        CreateOrUpdate(
            id_, text, placeHolder_, false, [type = testItem.item](TextFieldModelNG& model) { model.SetType(type); });
        auto errorMessage = "inputType is " + testItem.error + ", text is " + pattern_->GetEditingValue().text;
        EXPECT_EQ(pattern_->GetEditingValue().caretPosition, testItem.expected) << errorMessage;
    }
}

/**
 * @tc.name: CaretPosition003
 * @tc.desc: Test caret position on SetCaretPosition.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCaretTest, CaretPosition003, TestSize.Level1)
{
    /**
     * @tc.steps: Check caret position after call SetCaretPosition.
     * @tc.expected: caret position is same as the expected.
     */
    auto length = static_cast<int32_t>(pattern_->GetTextEditingValue().GetWideText().length());
    std::vector<TestItem<int32_t, int32_t>> testItems;
    for (auto position = 0; position <= length; position++) {
        testItems.emplace_back(position, position);
    }
    for (auto testItem : testItems) {
        pattern_->SetCaretPosition(testItem.item);
        EXPECT_EQ(pattern_->GetEditingValue().caretPosition, testItem.expected);
    }
}

/**
 * @tc.name: CaretPosition004
 * @tc.desc: Test caret position on SetMaxLength.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCaretTest, CaretPosition004, TestSize.Level1)
{
    /**
     * @tc.steps: Check caret position after call SetMaxLength.
     * @tc.expected: caret position is same as the expected.
     */
    auto length = static_cast<int32_t>(pattern_->GetTextEditingValue().GetWideText().length());
    pattern_->SetCaretPosition(length / 2);

    std::vector<TestItem<int32_t, int32_t>> testItems;
    testItems.emplace_back(length, length / 2, "caret position is less than max length");
    testItems.emplace_back(length / 2 - 1, length / 2 - 1, "caret position is greater than max length");
    for (auto testItem : testItems) {
        CreateOrUpdate(id_, text_, placeHolder_, false,
            [maxLength = testItem.item](TextFieldModelNG& model) { model.SetMaxLength(maxLength); });
        EXPECT_EQ(pattern_->GetEditingValue().caretPosition, testItem.expected) << testItem.error;
    }
}

/**
 * @tc.name: CaretPosition005
 * @tc.desc: Test caret position on SetInputFilter.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCaretTest, CaretPosition005, TestSize.Level1)
{
    /**
     * @tc.steps: Check caret position after call SetInputFilter.
     * @tc.expected: caret position is same as the expected.
     */
    std::string text = "abcdefghABCDEFG0123456789";
    std::vector<TestItem<std::string, int32_t>> testItems;

    testItems.emplace_back("", StringUtils::ToWstring(text).length());
    testItems.emplace_back("[0-9]", 10);
    testItems.emplace_back("[A-Z]", 7);
    testItems.emplace_back("[a-z]", 8);
    for (auto testItem : testItems) {
        CreateOrUpdate(id_, text, placeHolder_, false,
            [filter = testItem.item](TextFieldModelNG& model) { model.SetInputFilter(filter, nullptr); });
        auto errorMessage = "input filter is " + testItem.item + ", text is " + pattern_->GetEditingValue().text;
        EXPECT_EQ(pattern_->GetEditingValue().caretPosition, testItem.expected) << errorMessage;
    }
}

/**
 * @tc.name: CaretPosition006
 * @tc.desc: Test caret position when focus changed.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCaretTest, CaretPosition006, TestSize.Level1)
{
    /**
     * @tc.steps: Check caret position after call HandleFocusEvent or HandleBlurEvent.
     * @tc.expected: caret position is same as the expected.
     */
    pattern_->HandleFocusEvent();
    EXPECT_TRUE(pattern_->cursorVisible_) << "show cursor on focus";
    pattern_->HandleBlurEvent();
    EXPECT_FALSE(pattern_->cursorVisible_) << "hide cursor on blur";
}

/**
 * @tc.name: CaretPosition007
 * @tc.desc: Test caret position with the clipboard.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCaretTest, CaretPosition007, TestSize.Level1)
{
    /**
     * @tc.steps: Check caret position after call HandleOnCut,HandleOnPaste,HandleOnSelectAll.
     * @tc.expected: caret position is same as the expected.
     */
    CreateOrUpdate(
        id_, text_, placeHolder_, false, [](TextFieldModelNG& model) { model.SetCopyOption(CopyOptions::InApp); });
    auto len = pattern_->GetEditingValue().GetWideText().length();
    auto selectStart = len / 2;
    auto selectEnd = len;
    pattern_->UpdateSelection(selectStart, selectEnd);
    pattern_->SetInSelectMode(SelectionMode::SELECT);
    pattern_->HandleOnCut();
    EXPECT_EQ(pattern_->GetEditingValue().caretPosition, selectStart)
        << "caret position should equals with first handle position";

    len = pattern_->GetEditingValue().GetWideText().length();
    pattern_->SetInSelectMode(SelectionMode::SELECT);
    pattern_->UpdateSelection(0, len / 2);
    pattern_->HandleOnCopy();
    EXPECT_TRUE(pattern_->cursorVisible_) << "show cursor when call HandleOnCopy";
    pattern_->SetCaretPosition(len);
    pattern_->HandleOnPaste();
    EXPECT_EQ(pattern_->GetEditingValue().caretPosition, len + len / 2)
        << ("caret position equals with [last position] + [copy data length]");

    len = pattern_->GetEditingValue().GetWideText().length();
    pattern_->HandleOnSelectAll(false);
    EXPECT_EQ(pattern_->GetEditingValue().caretPosition, len) << ("caret position equals with text length");
}

/**
 * @tc.name: CaretPosition008
 * @tc.desc: Test caret position with the keyboard event.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCaretTest, CaretPosition008, TestSize.Level1)
{
    /**
     * @tc.steps: text is abcedefghijkl*mnopqrstuvwxyz, * is caret position.
     *            1. abcedefghijkl*nopqrstuvwxyz -- delete forward
     *            2. abcedefghijk*nopqrstuvwxyz -- delete backward
     *            3. abcedefghijk@*nopqrstuvwxyz -- insert 8
     *            4. abcedefghijk@*stuvwxyz -- select right 5(nopqr) and cut
     *            5. abcedefghijk@nopqr*stuvwxyz -- paste 5(nopqr)
     *            6. abcedefghijk@*stuvwxyz -- undo step 5
     *            7. abcedefghijk@nopqr*stuvwxyz -- redo step 6
     *            8. abcedefghijk@nopqrstuvwxyz* -- select all
     * @tc.expected: caret position is same as the expected.
     */
    auto length = static_cast<int>(pattern_->GetTextEditingValue().GetWideText().length());
    pattern_->SetCaretPosition(length / 2);
    pattern_->imeAttached_ = true;
    KeyEvent event;
    event.code = KeyCode::KEY_FORWARD_DEL;
    event.action = KeyAction::DOWN;
    pattern_->OnKeyEvent(event);
    EXPECT_EQ(pattern_->GetTextEditingValue().caretPosition, length / 2) << "delete forward";

    event.code = KeyCode::KEY_DEL;
    pattern_->OnKeyEvent(event);
    EXPECT_EQ(pattern_->GetTextEditingValue().caretPosition, length / 2 - 1) << "delete backward";

    event.code = KeyCode::KEY_2;
    event.pressedCodes = { KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_2 };
    pattern_->OnKeyEvent(event);
    EXPECT_EQ(pattern_->GetTextEditingValue().caretPosition, length / 2) << "insert one";

    event.code = KeyCode::KEY_DPAD_RIGHT;
    event.pressedCodes = { KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_DPAD_RIGHT };
    pattern_->UpdateSelection(length / 2);
    auto selectCount = 5;
    for (auto i = 0; i < selectCount; i++) {
        pattern_->OnKeyEvent(event);
    }
    event.code = KeyCode::KEY_X;
    event.pressedCodes = { KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_X };
    pattern_->OnKeyEvent(event);
    EXPECT_EQ(pattern_->GetTextEditingValue().caretPosition, length / 2)
        << ("cut " + std::to_string(selectCount) + " characters");

    event.code = KeyCode::KEY_V;
    event.pressedCodes = { KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_V };
    pattern_->OnKeyEvent(event);
    EXPECT_EQ(pattern_->GetTextEditingValue().caretPosition, length / 2 + selectCount)
        << ("paste " + std::to_string(selectCount) + " characters");

    event.code = KeyCode::KEY_Z;
    event.pressedCodes = { KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_Z };
    pattern_->OnKeyEvent(event);
    EXPECT_EQ(pattern_->GetTextEditingValue().caretPosition, length / 2)
        << ("undo, the caret position is at last position");

    event.code = KeyCode::KEY_Y;
    event.pressedCodes = { KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_Y };
    pattern_->OnKeyEvent(event);
    EXPECT_EQ(pattern_->GetTextEditingValue().caretPosition, length / 2 + selectCount)
        << ("redo, the caret position equals with step 5");

    length = static_cast<int>(pattern_->GetTextEditingValue().GetWideText().length());
    event.code = KeyCode::KEY_A;
    event.pressedCodes = { KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_A };
    pattern_->OnKeyEvent(event);
    EXPECT_EQ(pattern_->GetTextEditingValue().caretPosition, length)
        << ("select all, caret position is at the end of text");

    pattern_->imeAttached_ = false;
}
} // namespace CaretTest
}; // namespace OHOS::Ace::NG
