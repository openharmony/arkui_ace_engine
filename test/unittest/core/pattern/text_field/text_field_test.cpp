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
#include <memory>
#include <optional>
#include <string>
#include <utility>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/render/mock_paragraph.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/string_utils.h"
#include "core/common/ime/constant.h"
#include "core/common/ime/text_editing_value.h"
#include "core/common/ime/text_input_type.h"
#include "core/common/ime/text_selection.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/scroll/scroll_bar_theme.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components/theme/theme_manager.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/test/mock/render/mock_render_context.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_ng/test/pattern/test_ng.h"
#include "core/event/key_event.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
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

constexpr double ICON_SIZE = 24;
constexpr double ICON_HOT_ZONE_SIZE = 40;
constexpr double FONT_SIZE = 16;
constexpr int32_t DEFAULT_NODE_ID = 1;
constexpr int32_t MAX_BACKWARD_NUMBER = 30;
const std::string DEFAULT_TEXT = "abcdefghijklmnopqrstuvwxyz";
const std::string DEFAULT_PLACE_HOLDER = "please input text here";
using TextFiledModelUpdater = std::function<void(TextFieldModelNG&)>;
} // namespace

class TextFieldTestBase : public testing::Test {
protected:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void TearDown() override;

    RefPtr<FrameNode> CreateTextFieldNode(
        const std::string& text, const std::string& placeHolder, std::function<void(TextFieldModelNG&)>&& modelUpdater);
    void RunMeasureAndLayout(const RefPtr<FrameNode>& frameNode);
    RefPtr<TextFieldPattern> GetPattern(const RefPtr<FrameNode>& frameNode);
    void GetFocus(const RefPtr<FrameNode>& frameNode);
};

void TextFieldTestBase::SetUpTestSuite()
{
    MockContainer::SetUp();
    MockPipelineBase::SetUp();
    MockPipelineBase::GetCurrent()->SetRootSize(DEVICE_WIDTH, DEVICE_HEIGHT);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
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
    MockPipelineBase::GetCurrent()->SetTextFieldManager(AceType::MakeRefPtr<TextFieldManagerNG>());
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
}

void TextFieldTestBase::TearDownTestSuite()
{
    MockContainer::TearDown();
    MockPipelineBase::TearDown();
    MockParagraph::TearDown();
}

void TextFieldTestBase::TearDown() {}

RefPtr<FrameNode> TextFieldTestBase::CreateTextFieldNode(
    const std::string& text, const std::string& placeHolder, std::function<void(TextFieldModelNG&)>&& modelUpdater)
{
    auto* stack = ViewStackProcessor::GetInstance();
    stack->StartGetAccessRecordingFor(DEFAULT_NODE_ID);
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateTextInput(placeHolder, text);
    if (modelUpdater) {
        modelUpdater(textFieldModelNG);
    }
    stack->StopGetAccessRecording();
    auto frameNode = AceType::DynamicCast<FrameNode>(stack->Finish());
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, PushStyle(_)).Times(AnyNumber());
    EXPECT_CALL(*paragraph, AddText(_)).Times(AnyNumber());
    EXPECT_CALL(*paragraph, PopStyle()).Times(AnyNumber());
    EXPECT_CALL(*paragraph, Build()).Times(AnyNumber());
    EXPECT_CALL(*paragraph, Layout(_)).Times(AnyNumber());
    EXPECT_CALL(*paragraph, GetHeight()).Times(AnyNumber());
    EXPECT_CALL(*paragraph, GetLongestLine()).Times(AnyNumber());
    RunMeasureAndLayout(frameNode);
    return frameNode;
}

void TextFieldTestBase::RunMeasureAndLayout(const RefPtr<FrameNode>& frameNode)
{
    frameNode->SetActive();
    frameNode->SetRootMeasureNode(true);
    frameNode->UpdateLayoutPropertyFlag();
    frameNode->SetSkipSyncGeometryNode(false);
    frameNode->Measure(frameNode->GetLayoutConstraint());
    frameNode->Layout();
    frameNode->SetRootMeasureNode(false);
}

void TextFieldTestBase::GetFocus(const RefPtr<FrameNode>& frameNode)
{
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    auto focushHub = pattern->GetFocusHub();
    focushHub->currentFocus_ = true;
    pattern->HandleFocusEvent();
    RunMeasureAndLayout(frameNode);
}

RefPtr<TextFieldPattern> TextFieldTestBase::GetPattern(const RefPtr<FrameNode>& frameNode)
{
    return frameNode->GetPattern<TextFieldPattern>();
}

class TextFieldCaretTest : public TextFieldTestBase {};
class TextFieldControllerTest : public TextFieldTestBase {};
class TextFieldKeyHandlerTest : public TextFieldTestBase {};

/**
 * @tc.name: CaretPosition001
 * @tc.desc: Test caret position on TextFieldModelNG::CreateNode.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCaretTest, CaretPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default text and placeholder
     */
    auto frameNode = CreateTextFieldNode(DEFAULT_TEXT, DEFAULT_PLACE_HOLDER, nullptr);
    auto pattern = GetPattern(frameNode);

    /**
     * @tc.expected: Current caret position is end of text
     */
    EXPECT_EQ(pattern->GetTextSelectController()->GetCaretIndex(), DEFAULT_TEXT.size());

    /**
     * @tc.steps: Changed new text and remeasure and layout
     */
    pattern->InsertValue("new");
    RunMeasureAndLayout(frameNode);

    /**
     * @tc.expected: Current caret position is end of text
     */
    EXPECT_EQ(pattern->GetTextSelectController()->GetCaretIndex(), DEFAULT_TEXT.size() + 3);
}

/**
 * @tc.name: CaretPosition002
 * @tc.desc: Test caret position on SetType.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCaretTest, CaretPosition002, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default text and placeholder and set input type
     */
    std::string text = "openharmony@huawei.com+*0123456789";
    std::vector<TestItem<TextInputType, int32_t>> testItems;
    testItems.emplace_back(TextInputType::TEXT, text.size(), "TextInputType::TEXT");
    testItems.emplace_back(TextInputType::NUMBER, 10, "TextInputType::NUMBER");
    testItems.emplace_back(TextInputType::PHONE, 12, "TextInputType::PHONE");
    testItems.emplace_back(TextInputType::EMAIL_ADDRESS, text.size() - 2, "TextInputType::EMAIL_ADDRESS");
    testItems.emplace_back(TextInputType::VISIBLE_PASSWORD, text.size() - 2, "TextInputType::VISIBLE_PASSWORD");

    /**
     * @tc.expected: Check if the text filter rules for the input box are compliant
     */
    for (const auto& testItem : testItems) {
        auto frameNode = CreateTextFieldNode(
            text, DEFAULT_PLACE_HOLDER, [testItem](TextFieldModelNG& model) { model.SetType(testItem.item); });
        auto pattern = GetPattern(frameNode);
        auto errorMessage = "InputType is " + testItem.error + ", text is " + pattern->GetTextValue();
        EXPECT_EQ(pattern->GetTextSelectController()->GetCaretIndex(), testItem.expected) << errorMessage;
    }
}

/**
 * @tc.name: CaretPosition003
 * @tc.desc: Test caret position on SetCaretPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCaretTest, CaretPosition003, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default text
     * @tc.expected: Cursor movement position matches the actual position
     */
    auto frameNode = CreateTextFieldNode(DEFAULT_TEXT, DEFAULT_PLACE_HOLDER, nullptr);
    auto pattern = GetPattern(frameNode);
    auto controller = pattern->GetTextFieldController();
    controller->CaretPosition(static_cast<int>(DEFAULT_TEXT.size() - 2));
    EXPECT_EQ(pattern->GetTextSelectController()->GetCaretIndex(), static_cast<int>(DEFAULT_TEXT.size() - 2));
}

/**
 * @tc.name: CaretPosition004
 * @tc.desc: Test caret position on SetMaxLength
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCaretTest, CaretPosition004, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default text and placeholder
     * @tc.expected: Cursor movement position matches the actual position
     */
    auto frameNode = CreateTextFieldNode(DEFAULT_TEXT, DEFAULT_PLACE_HOLDER,
        [](TextFieldModelNG& model) { model.SetMaxLength(DEFAULT_TEXT.size() - 2); });
    auto pattern = GetPattern(frameNode);
    auto controller = pattern->GetTextFieldController();
    controller->CaretPosition(static_cast<int>(DEFAULT_TEXT.size() - 2));
    EXPECT_EQ(pattern->GetTextSelectController()->GetCaretIndex(), static_cast<int>(DEFAULT_TEXT.size() - 2));
}

/**
 * @tc.name: CaretPosition005
 * @tc.desc: Test caret position on SetInputFilter.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCaretTest, CaretPosition005, TestSize.Level1)
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
        auto frameNode = CreateTextFieldNode(text, DEFAULT_PLACE_HOLDER,
            [testItem](TextFieldModelNG& model) { model.SetInputFilter(testItem.item, nullptr); });
        auto pattern = GetPattern(frameNode);
        auto errorMessage = "InputType is " + testItem.error + ", text is " + pattern->GetTextValue();
        EXPECT_EQ(pattern->GetTextSelectController()->GetCaretIndex(), testItem.expected) << errorMessage;
    }
}

/**
 * @tc.name: CaretPosition005
 * @tc.desc: Test input string at the cursor position
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCaretTest, CaretPosition006, TestSize.Level1)
{
    /**
     * @tc.steps: Initialize text input and get select controller, update caret position and insert value
     */
    auto frameNode = CreateTextFieldNode(DEFAULT_TEXT, DEFAULT_PLACE_HOLDER, nullptr);
    auto pattern = GetPattern(frameNode);
    auto controller = pattern->GetTextSelectController();
    controller->UpdateCaretIndex(2);
    pattern->InsertValue("new");
    RunMeasureAndLayout(frameNode);

    /**
     * @tc.expected: Check if the text and cursor position are correct
     */
    EXPECT_EQ(pattern->contentController_->GetTextValue(), "abnewcdefghijklmnopqrstuvwxyz");
    EXPECT_EQ(controller->GetCaretIndex(), 5);
}

/**
 * @tc.name: CaretPosition006
 * @tc.desc: Test stop edting input mode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCaretTest, CaretPosition007, TestSize.Level1)
{
    /**
     * @tc.steps: Initialize text input node
     */
    auto frameNode = CreateTextFieldNode(DEFAULT_TEXT, DEFAULT_PLACE_HOLDER, nullptr);
    auto pattern = GetPattern(frameNode);

    /**
     * @tc.expected: The cursor is neither blinking nor visible when unfocused
     */
    EXPECT_EQ(pattern->caretStatus_, CaretStatus::NONE);
    EXPECT_FALSE(pattern->GetCursorVisible());

    /**
     * @tc.steps: Manually trigger focus and perform measure and layout again
     * @tc.expected: Check if the cursor is twinking
     */
    GetFocus(frameNode);
    EXPECT_EQ(pattern->caretStatus_, CaretStatus::SHOW);
    EXPECT_TRUE(pattern->GetCursorVisible());

    /**
     * @tc.steps: Get text filed controller and stop editing
     */
    auto controller = pattern->GetTextFieldController();
    controller->StopEditing();
    RunMeasureAndLayout(frameNode);

    /**
     * @tc.expected: Check if the cursor stop twinking
     */
    EXPECT_EQ(pattern->caretStatus_, CaretStatus::HIDE);
    EXPECT_FALSE(pattern->GetCursorVisible());
}

/**
 * @tc.name: OnTextChangedListenerCaretPosition001
 * @tc.desc: Test the soft keyboard interface
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCaretTest, OnTextChangedListenerCaretPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: Initialize text input node and call text changed listener update edting value
     */
    auto frameNode = CreateTextFieldNode(DEFAULT_TEXT, DEFAULT_PLACE_HOLDER, nullptr);
    auto pattern = GetPattern(frameNode);
    GetFocus(frameNode);
    TextEditingValue value;
    TextSelection selection;
    value.text = "new text";
    selection.baseOffset = value.text.length();
    value.selection = selection;
    pattern->UpdateEditingValue(std::make_shared<TextEditingValue>(value));
    RunMeasureAndLayout(frameNode);

    /**
     * @tc.expected: Check if the new text and cursor position are correct
     */
    EXPECT_EQ(pattern->contentController_->GetTextValue().compare("new text"), 0);
    EXPECT_EQ(pattern->GetTextSelectController()->GetCaretIndex(), value.text.length());
}

/**
 * @tc.name: OnTextChangedListenerCaretPosition002
 * @tc.desc: Test the soft keyboard interface
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCaretTest, OnTextChangedListenerCaretPosition002, TestSize.Level1)
{
    /**
     * @tc.steps: Initialize text input node and call delete backward
     */
    auto frameNode = CreateTextFieldNode(DEFAULT_TEXT, DEFAULT_PLACE_HOLDER, nullptr);
    auto pattern = GetPattern(frameNode);
    GetFocus(frameNode);
    pattern->DeleteBackward(3);
    pattern->DeleteBackward(2);
    RunMeasureAndLayout(frameNode);

    /**
     * @tc.expected: Check if the new text and cursor position are correct
     */
    EXPECT_EQ(pattern->contentController_->GetTextValue().compare("abcdefghijklmnopqrstu"), 0);
    EXPECT_EQ(pattern->GetTextSelectController()->GetCaretIndex(), DEFAULT_TEXT.length() - 5);

    /**
     * @tc.steps: Move the cursor and then delete text
     */
    auto textFiledController = pattern->GetTextFieldController();
    textFiledController->CaretPosition(5);
    pattern->DeleteBackward(5);
    RunMeasureAndLayout(frameNode);

    /**
     * @tc.expected: Check if the new text and cursor position are correct
     */
    EXPECT_EQ(pattern->contentController_->GetTextValue().compare("fghijklmnopqrstu"), 0);
    EXPECT_EQ(pattern->GetTextSelectController()->GetCaretIndex(), 0);

    /**
     * @tc.steps: Trigger a backspace key press that exceeds the length of the text
     */
    pattern->DeleteBackward(MAX_BACKWARD_NUMBER);
    RunMeasureAndLayout(frameNode);

    /**
     * @tc.expected: Check if the new text and cursor position are correct
     */
    EXPECT_EQ(pattern->contentController_->GetTextValue().compare("fghijklmnopqrstu"), 0);
    EXPECT_EQ(pattern->GetTextSelectController()->GetCaretIndex(), 0);
}

/**
 * @tc.name: OnTextChangedListenerCaretPosition003
 * @tc.desc: Test the soft keyboard interface
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCaretTest, OnTextChangedListenerCaretPosition003, TestSize.Level1)
{
    /**
     * @tc.steps: Initialize insert text and expected values
     */
    auto frameNode = CreateTextFieldNode(DEFAULT_TEXT, DEFAULT_PLACE_HOLDER, nullptr);
    auto pattern = GetPattern(frameNode);
    pattern->DeleteForward(3);
    pattern->DeleteForward(2);
    RunMeasureAndLayout(frameNode);

    /**
     * @tc.expected: Check if the new text and cursor position are correct
     */
    EXPECT_EQ(pattern->contentController_->GetTextValue().compare(DEFAULT_TEXT), 0);
    EXPECT_EQ(pattern->GetTextSelectController()->GetCaretIndex(), DEFAULT_TEXT.length());

    /**
     * @tc.steps: Move the cursor and then delete text forward.
     */
    auto textFiledController = pattern->GetTextFieldController();
    textFiledController->CaretPosition(5);
    pattern->DeleteForward(30);
    RunMeasureAndLayout(frameNode);

    /**
     * @tc.expected: Check if the new text and cursor position are correct
     */
    EXPECT_EQ(pattern->contentController_->GetTextValue().compare("abcde"), 0);
    EXPECT_EQ(pattern->GetTextSelectController()->GetCaretIndex(), 5);
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
    };
    std::vector<TestItem<TextInputType, std::string>> testItems;
    testItems.emplace_back(TextInputType::TEXT, "openharmony123_ *+%$", "TextInputType::TEXT");
    testItems.emplace_back(TextInputType::NUMBER, "123456", "TextInputType::NUMBER");
    testItems.emplace_back(TextInputType::PHONE, "#15612932075*", "TextInputType::PHONE");
    testItems.emplace_back(
        TextInputType::EMAIL_ADDRESS, "open_harmony@huawei.comhelloworld", "TextInputType::EMAIL_ADDRESS");
    testItems.emplace_back(
        TextInputType::VISIBLE_PASSWORD, "openharmony123 password*+#", "TextInputType::VISIBLE_PASSWORD");

    /**
     * @tc.expected: Check if text filtering meets expectations
     */
    int index = 0;
    for (const auto& testItem : testItems) {
        auto frameNode = CreateTextFieldNode(
            "", DEFAULT_PLACE_HOLDER, [testItem](TextFieldModelNG& model) { model.SetType(testItem.item); });
        auto pattern = GetPattern(frameNode);
        pattern->contentController_->InsertValue(0, insertValues[index]);
        index++;
        auto errorMessage = "InputType is " + testItem.error + ", text is " + pattern->GetTextValue();
        EXPECT_EQ(pattern->contentController_->GetTextValue().compare(testItem.expected), 0) << errorMessage;
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
        auto frameNode = CreateTextFieldNode("", DEFAULT_PLACE_HOLDER,
            [testItem](TextFieldModelNG& model) { model.SetInputFilter(testItem.item, nullptr); });
        auto pattern = GetPattern(frameNode);
        pattern->contentController_->InsertValue(0, text);
        auto errorMessage = testItem.error + ", text is " + pattern->GetTextValue();
        EXPECT_EQ(pattern->contentController_->GetTextValue().compare(testItem.expected), 0) << errorMessage;
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
     * @tc.steps: Initialize text and filter patterns
     */
    auto frameNode = CreateTextFieldNode(DEFAULT_TEXT, DEFAULT_PLACE_HOLDER, nullptr);
    auto pattern = GetPattern(frameNode);

    /**
     * @tc.expected: Check if text is selected based on corresponding left and right coordinates
     */
    auto selectedValue = pattern->contentController_->GetSelectedValue(1, 4);
    EXPECT_EQ(selectedValue.compare("bcd"), 0) << "Text is " + selectedValue;

    /**
     * @tc.expected: Check if text is selected based on preceding coordinates
     */
    auto beforeSelectedValue = pattern->contentController_->GetValueBeforeIndex(3);
    EXPECT_EQ(beforeSelectedValue.compare("abc"), 0) << "Text is " + beforeSelectedValue;

    /**
     * @tc.expected: Check if text is selected based on trailing coordinates
     */
    auto afterSelectedValue = pattern->contentController_->GetValueAfterIndex(3);
    EXPECT_EQ(afterSelectedValue.compare("defghijklmnopqrstuvwxyz"), 0) << "Text is " + afterSelectedValue;
}
} // namespace OHOS::Ace::NG
