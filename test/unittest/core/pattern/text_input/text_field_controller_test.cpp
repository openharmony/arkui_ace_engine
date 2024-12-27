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

#include <unicode/putil.h>
#include <unicode/uclean.h>

#include "text_input_base.h"

#include "test/mock/core/common/mock_data_detector_mgr.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/render/mock_render_context.h"

#include "core/components/common/properties/text_style_parser.h"

namespace OHOS::Ace::NG {

namespace {
const std::string NEWLINE = "\n";
const std::u16string WIDE_NEWLINE = UtfUtils::Str8ToStr16(NEWLINE);
const std::list<std::pair<std::string, int32_t>> FONT_FEATURE_VALUE_0 = ParseFontFeatureSettings("\"ss01\" 0");
const std::list<std::pair<std::string, int32_t>> FONT_FEATURE_VALUE_1 = ParseFontFeatureSettings("\"ss01\" 1");
} // namespace

class MockDataDetectorInterface : public DataDetectorInterface {
public:
    MOCK_METHOD(bool, IsDataDetectorSupported, (), (override));
    MOCK_METHOD(void, GetAIEntityMenu, (TextDataDetectResult & textDataDetectResult), (override));
    MOCK_METHOD(void, DataDetect, (const TextDataDetectInfo& info, const TextDetectResultFunc& resultFunc), (override));
    MOCK_METHOD(int8_t, GetCursorPosition, (const std::string& text, int8_t offset), (override));
    MOCK_METHOD(std::vector<int8_t>, GetWordSelection, (const std::string& text, int8_t offset), (override));
};

class TextAdjustObject : public TextInputBases {
protected:
    static void InitAdjustObject(MockDataDetectorMgr& mockDataDetectorMgr);
};
class TextFieldResponseAreaTest : public TextInputBases {
public:
};
class TextFieldControllerTest : public TextInputBases {
public:
};

void TextAdjustObject::InitAdjustObject(MockDataDetectorMgr& mockDataDetectorMgr)
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

/*
 * @tc.name: AdjustWordCursorAndSelect01
 * @tc.desc: Test .adjust word cursor and select(true)
 * @tc.type: FUNC
 */
HWTEST_F(TextAdjustObject, AdjustWordCursorAndSelect01, TestSize.Level1)
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
    pattern_->contentController_->SetTextValue(DEFAULT_TEXT_U16);
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
 * @tc.name: TextFieldResponseArea001
 * @tc.desc: test password response area show/hide.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldResponseAreaTest, TextFieldResponseArea001, TestSize.Level1)
{
    PasswordIcon myIcon =  {
        .showResult = "1",
        .hideResult = "2",
        .showBundleName = "1",
        .hideBundleName = "2",
        .showModuleName = "1",
        .hideModuleName = "2",
    };
    CreateTextField(DEFAULT_TEXT, "", [myIcon](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetShowPasswordIcon(true);
        model.SetPasswordIcon(myIcon);
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetIsShowCancelButton(true);
        model.SetCancelButtonSymbol(false);
    });
    auto passwordArea = AceType::MakeRefPtr<PasswordResponseArea>(pattern_, false);
    passwordArea->InitResponseArea();
    EXPECT_EQ(passwordArea->GetCurrentSourceInfo()->GetSrc(), "1");
    passwordArea->SetObscured(true);
    EXPECT_EQ(passwordArea->GetCurrentSourceInfo()->GetSrc(), "2");
}

/**
 * @tc.name: TextFieldResponseArea002
 * @tc.desc: test change response area not effect response state.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldResponseAreaTest, TextFieldResponseArea002, TestSize.Level1)
{
    PasswordIcon myIcon =  {
        .showResult = "1",
        .hideResult = "2",
        .showBundleName = "1",
        .hideBundleName = "2",
        .showModuleName = "1",
        .hideModuleName = "2",
    };
    CreateTextField(DEFAULT_TEXT, "", [myIcon](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetShowPasswordIcon(true);
        model.SetPasswordIcon(myIcon);
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetIsShowCancelButton(true);
        model.SetCancelButtonSymbol(false);
    });
    RefPtr<TextInputResponseArea> responseArea = AceType::MakeRefPtr<CleanNodeResponseArea>(pattern_);
    auto convertedArea = AceType::DynamicCast<CleanNodeResponseArea>(responseArea);
    convertedArea->UpdateCleanNode(true);
    EXPECT_EQ(convertedArea->IsShow(), true);
    responseArea = AceType::MakeRefPtr<PasswordResponseArea>(pattern_, true);
    auto passwordArea = AceType::DynamicCast<PasswordResponseArea>(responseArea);
    passwordArea->InitResponseArea();
    EXPECT_EQ(passwordArea->GetCurrentSourceInfo()->GetSrc(), "2");
}


/**
 * @tc.name: LayoutProperty001
 * @tc.desc: Test attrs on TextInput
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, LayoutProperty001, TestSize.Level1)
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
        model.SetWordBreak(WordBreak::BREAK_ALL);
        model.SetTextOverflow(TextOverflow::CLIP);
        model.SetTextIndent(DEFAULT_INDENT_SIZE);
    });

    /**
     * @tc.expected: Check if all set properties are displayed in the corresponding JSON
     */
    auto json = JsonUtil::Create(true);
    pattern_->ToJsonValue(json, filter);
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
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("caretPosition"), "");
    EXPECT_TRUE(json->GetBool("showUnderline"));
    EXPECT_TRUE(json->GetBool("selectAll"));
    EXPECT_EQ(json->GetString("wordBreak"), "break-all");
    EXPECT_EQ(json->GetString("textOverflow"), "TextOverflow.Clip");
    EXPECT_EQ(json->GetString("textIndent"), "5.00vp");
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
    pattern_->InsertValue(u"X");
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
    auto numStr = u"1";
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
    pattern_->SetIsSingleHandle(false);
    pattern_->OnTextInputScroll(0.0f);
    pattern_->SetIsSingleHandle(true);
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
 * @tc.name: CreateDisplayText001
 * @tc.desc: Test textInput display of context.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, CreateDisplayText001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.steps: step2. call CreateDisplayText with showPasswordDirectly is true
     * tc.expected: step2. Check the CreateDisplayText return.
     */
    GetFocus();
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion((int32_t)PlatformVersion::VERSION_TWELVE);
    std::u16string inputPartOne = u"tes";
    std::u16string inputPartTwo = u"t";
    std::u16string input = inputPartOne + inputPartTwo;
    auto outputOne = StringUtils::Str16ToStr8(pattern_->CreateObscuredText(static_cast<int32_t>(input.length())));
    auto res = StringUtils::Str16ToStr8(pattern_->CreateDisplayText(input, 3, true, true));
    EXPECT_EQ(outputOne, res);

    /**
     * @tc.steps: step3. call CreateDisplayText with showPasswordDirectly is false
     * tc.expected: step3. Check the CreateDisplayText return.
     */
    auto outputTwo = pattern_->CreateObscuredText(static_cast<int32_t>(inputPartOne.length()));
    outputTwo += inputPartTwo;
    res = StringUtils::Str16ToStr8(pattern_->CreateDisplayText(input, 3, true, false));
    EXPECT_EQ(StringUtils::Str16ToStr8(outputTwo), res);
}

/**
 * @tc.name: CreateDisplayText002
 * @tc.desc: Test textInput display of context.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, CreateDisplayText002, TestSize.Level1)
{
    SystemProperties::debugEnabled_ = true;
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    std::u16string inputPart2 = u"t";
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion((int32_t)PlatformVersion::VERSION_THIRTEEN);
    std::u16string inputPart1 = u"tes";
    std::u16string input = inputPart1 + inputPart2;
    auto output1 = StringUtils::Str16ToStr8(pattern_->CreateObscuredText(static_cast<int32_t>(input.length())));
    auto res = StringUtils::Str16ToStr8(pattern_->CreateDisplayText(input, 3, true, true));
    EXPECT_EQ(output1, res);
    auto output2 = pattern_->CreateObscuredText(static_cast<int32_t>(inputPart1.length()));
    output2 += inputPart2;
    res = StringUtils::Str16ToStr8(pattern_->CreateDisplayText(input, 3, true, false));
    EXPECT_EQ(StringUtils::Str16ToStr8(output2), res);
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
 * @tc.name: ContentController001
 * @tc.desc: Test ContentController in different input type
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, ContentController001, TestSize.Level1)
{
    /**
     * @tc.steps: Initialize insert text and expected values
     */
    std::vector<std::u16string> insertValues = {
        u"openharmony123_ *+%$",
        u"openharmony123456*+&@huawei.com",
        u"openharmony (new)#15612932075*.com",
        u"open_harmony@@harmony.com*+$helloworld",
        u"open_harmony123 password*+#",
        u"openharmony123456*+&@huawei.com",
        u"o达瓦大屋顶pen_harmony456顶顶顶 password*+#得到",
    };
    std::vector<TestItem<TextInputType, std::string>> testItems;
    testItems.emplace_back(TextInputType::TEXT, "openharmony123_ *+%$", "TextInputType::TEXT");
    testItems.emplace_back(TextInputType::NUMBER, "123456", "TextInputType::NUMBER");
    testItems.emplace_back(TextInputType::PHONE, " ()#15612932075*", "TextInputType::PHONE");
    testItems.emplace_back(
        TextInputType::EMAIL_ADDRESS, "open_harmony@harmony.com*+$helloworld", "TextInputType::EMAIL_ADDRESS");
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
    std::u16string text = u"CabcdefgABhCDEFG0123a456A789";
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
    auto selectedValue = StringUtils::Str16ToStr8(pattern_->contentController_->GetSelectedValue(1, 4));
    EXPECT_EQ(selectedValue.compare("bcd"), 0) << "Text is " + selectedValue;

    /**
     * @tc.expected: Check if text is selected based on preceding coordinates
     */
    auto beforeSelectedValue = StringUtils::Str16ToStr8(pattern_->contentController_->GetValueBeforeIndex(3));
    EXPECT_EQ(beforeSelectedValue.compare("abc"), 0) << "Text is " + beforeSelectedValue;

    /**
     * @tc.expected: Check if text is selected based on trailing coordinates
     */
    auto afterSelectedValue = StringUtils::Str16ToStr8(pattern_->contentController_->GetValueAfterIndex(3));
    EXPECT_EQ(afterSelectedValue.compare("defghijklmnopqrstuvwxyz"), 0) << "Text is " + afterSelectedValue;
}

/**
 * @tc.name: ContentController004
 * @tc.desc: Test ContentController in different input filter
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, ContentController004, TestSize.Level1)
{
    /**
     * @tc.steps: Initialize text field node
     */
    CreateTextField();
    GetFocus();

    /**
     * @tc.expected: Set text type is NUMBER_DECIMAL
     */
    layoutProperty_->UpdateTextInputType(TextInputType::NUMBER_DECIMAL);

    /**
     * @tc.expected: when the text point more then one, FilterWithDecimal return true,
     * @tc.expected: and the value update only one point
     */
    std::u16string text = u"3.1.4.";
    pattern_->contentController_->InsertValue(0, text);
    EXPECT_TRUE(pattern_->contentController_->FilterWithDecimal(text));
    EXPECT_EQ(pattern_->GetTextValue(), "3.14");
}

/**
 * @tc.name: ContentController005
 * @tc.desc: Test ContentController in different input filter
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, ContentController005, TestSize.Level1)
{
    /**
     * @tc.steps: Initialize text field node
     */
    CreateTextField();
    GetFocus();

    /**
     * @tc.expected: Set text type is NUMBER_DECIMAL
     */
    layoutProperty_->UpdateTextInputType(TextInputType::NUMBER_DECIMAL);

    /**
     * @tc.expected: when the text have one point, FilterWithDecimal return false
     */
    std::u16string text = u"3.14";
    pattern_->contentController_->InsertValue(0, text);
    EXPECT_FALSE(pattern_->contentController_->FilterWithDecimal(text));
    EXPECT_EQ(pattern_->GetTextValue(), "3.14");
}

/**
 * @tc.name: TextFiledControllerTest001
 * @tc.desc: Test TextFieldController GetTextContentLinesNum
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, TextFieldControllerTest001, TestSize.Level1)
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
HWTEST_F(TextFieldControllerTest, TextFieldControllerTest002, TestSize.Level1)
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
 * @tc.name: TextFieldControllerTest003
 * @tc.desc: Test TextFieldModelNG controller.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, TextFieldControllerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: Initialize textarea node.
     */
    auto frameNode = TextFieldModelNG::CreateFrameNode(-1, u"", u"", true);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);

    /**
     * @tc.expected: Check jsController value.
     */
    auto jsController = AceType::MakeRefPtr<Referenced>();
    TextFieldModelNG::SetJSTextEditableController(node, jsController);
    auto getController = TextFieldModelNG::GetJSTextEditableController(node);
    EXPECT_NE(getController, nullptr);
}

/**
 * @tc.name: TextFieldFontFeatureTest
 * @tc.desc: Test the caret move right
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, FontFeature003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateTextInput(DEFAULT_TEXT_U16, u"");

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
HWTEST_F(TextFieldControllerTest, FontFeature004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateTextInput(DEFAULT_TEXT_U16, u"");

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
 * @tc.name: HandleOnDeleteAction001
 * @tc.desc: test testInput deleteAction for normal emoji.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, HandleOnDeleteAction001, TestSize.Level1)
{
#if defined(__HuaweiLite__) || defined(__OHOS__)
    // use system icudt .dat file
    std::string dataPath = "/system/usr/ohos_icu";
#else
    // use project icudt .dat file
#ifdef WINDOWS_PLATFORM
    char buffer[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, buffer);
    std::string currentPath = std::string(buffer);
#else
    char buffer[PATH_MAX];
    getcwd(buffer, sizeof(buffer));
    std::string currentPath = std::string(buffer);
#endif
    std::string dataPath = currentPath + "/../../../../../../third_party/icu/ohos_icu4j/data";
#endif
    u_setDataDirectory(dataPath.c_str());
    UErrorCode code;
    u_init(&code);
    /**
     * @tc.steps: Create Text field node
     */
    std::string txt = "😄😌😎😭😄😌😎😭😄😌😎😭";
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();
    /**
     * @tc.step: step2. Set caretPosition and call Delete
     */
    pattern_->SetCaretPosition(24);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    std::string result = "😄😌😎😭😄😌😎😭😄😌";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " << pattern_->GetTextValue();

    pattern_->SetCaretPosition(10);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = "😄😌😎😌😎😭😄😌";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " << pattern_->GetTextValue();

    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = "😎😌😎😭😄😌";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    pattern_->SetCaretPosition(6);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = "😎😌😎😌";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();
}

/**
 * @tc.name: HandleOnDeleteAction002
 * @tc.desc: test testInput deleteAction for ZWJ emoji.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, HandleOnDeleteAction002, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    // change line to aviod the line length exceed 120
    const std::string txt = std::string("👨‍👩‍👦‍👦👨‍👩‍👦‍👦👨‍👩‍👦‍👦👨‍👩‍👦‍👦👨‍👩‍👦‍👦👨‍👩‍👦‍👦")
        .append("👨‍👩‍👦‍👦👨‍👩‍👦‍👦👨‍👩‍👦‍👦👨‍👩‍👦‍👦👨‍👩‍👦‍👦👨‍👩‍👦‍👦");
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step2. Set caretPosition and call Delete
     */

    pattern_->SetCaretPosition(132);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    // change line to aviod the line length exceed 120
    std::string result = std::string("👨‍👩‍👦‍👦👨‍👩‍👦‍👦👨‍👩‍👦‍👦👨‍👩‍👦‍👦👨‍👩‍👦‍👦")
        .append("👨‍👩‍👦‍👦👨‍👩‍👦‍👦👨‍👩‍👦‍👦👨‍👩‍👦‍👦👨‍👩‍👦‍👦");

    pattern_->SetCaretPosition(88);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = "👨‍👩‍👦‍👦👨‍👩‍👦‍👦👨‍👩‍👦‍👦👨‍👩‍👦‍👦👨‍👩‍👦‍👦👨‍👩‍👦‍👦👨‍👩‍👦‍👦👨‍👩‍👦‍👦";

    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = "👨‍👩‍👦‍👦👨‍👩‍👦‍👦👨‍👩‍👦‍👦👨‍👩‍👦‍👦👨‍👩‍👦‍👦👨‍👩‍👦‍👦";

    pattern_->SetCaretPosition(44);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = "👨‍👩‍👦‍👦👨‍👩‍👦‍👦👨‍👩‍👦‍👦👨‍👩‍👦‍👦";
}

/**
 * @tc.name: HandleOnDeleteAction003
 * @tc.desc: test testInput deleteAction for VS emoji.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, HandleOnDeleteAction003, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    const std::string txt = "👁️👁️👁️👁️👁️👁️👁️👁️👁️👁️👁️👁️";
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step2. Set caretPosition and call Delete
     */
    pattern_->SetCaretPosition(36);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    std::string result = "👁️👁️👁️👁️👁️👁️👁️👁️👁️👁️";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    pattern_->SetCaretPosition(30);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = "👁️👁️👁️👁️👁️👁️👁️👁️";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = "👁️👁️👁️👁️👁️👁️";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    pattern_->SetCaretPosition(12);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = "👁️👁️👁️👁️";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();
}

/**
 * @tc.name: HandleOnDeleteAction004
 * @tc.desc: test testInput deleteAction for RIS.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, HandleOnDeleteAction004, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    const std::string txt = "🇨🇳🇨🇳🇨🇳🇨🇳🇨🇳🇨🇳🇨🇳🇨🇳🇨🇳🇨🇳🇨🇳🇨🇳";
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step2. Set caretPosition and call Delete
     */
    pattern_->SetCaretPosition(48);
    pattern_->DeleteBackward(1);
    FlushLayoutTask(frameNode_);
    std::string result = "🇨🇳🇨🇳🇨🇳🇨🇳🇨🇳🇨🇳🇨🇳🇨🇳🇨🇳🇨🇳🇨🇳";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    pattern_->SetCaretPosition(28);
    pattern_->DeleteBackward(3);
    FlushLayoutTask(frameNode_);
    result = "🇨🇳🇨🇳🇨🇳🇨🇳🇨🇳🇨🇳🇨🇳🇨🇳";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(3);
    FlushLayoutTask(frameNode_);
    result = "🇨🇳🇨🇳🇨🇳🇨🇳🇨🇳";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    pattern_->SetCaretPosition(12);
    pattern_->DeleteForward(1);
    FlushLayoutTask(frameNode_);
    result = "🇨🇳🇨🇳🇨🇳🇨🇳";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();
}

/**
 * @tc.name: HandleOnDeleteAction005
 * @tc.desc: test testInput deleteAction for keycap.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, HandleOnDeleteAction005, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    const std::string txt = "3️⃣3️⃣3️⃣3️⃣3️⃣3️⃣3️⃣3️⃣3️⃣3️⃣3️⃣3️⃣";
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step2. Set caretPosition and call Delete
     */
    pattern_->SetCaretPosition(36);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    std::string result = "3️⃣3️⃣3️⃣3️⃣3️⃣3️⃣3️⃣3️⃣3️⃣3️⃣";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    pattern_->SetCaretPosition(27);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = "3️⃣3️⃣3️⃣3️⃣3️⃣3️⃣3️⃣3️⃣";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = "3️⃣3️⃣3️⃣3️⃣3️⃣3️⃣";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    pattern_->SetCaretPosition(12);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = "3️⃣3️⃣3️⃣3️⃣";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();
}

/**
 * @tc.name: HandleOnDeleteAction006
 * @tc.desc: test testInput deleteAction for ZWJ&VS emoji.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, HandleOnDeleteAction006, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    const std::string txt = "👁️‍🗨️👁️‍🗨️👁️‍🗨️👁️‍🗨️👁️‍🗨️👁️‍🗨️👁️‍🗨️👁️‍🗨️👁️‍🗨️👁️‍🗨️👁️‍🗨️👁️‍🗨️";
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step2. Set caretPosition and call Delete
     */
    pattern_->SetCaretPosition(84);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    std::string result = "👁️‍🗨️👁️‍🗨️👁️‍🗨️👁️‍🗨️👁️‍🗨️👁️‍🗨️👁️‍🗨️👁️‍🗨️👁️‍🗨️👁️‍🗨️";

    pattern_->SetCaretPosition(77);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = "👁️‍🗨️👁️‍🗨️👁️‍🗨️👁️‍🗨️👁️‍🗨️👁️‍🗨️👁️‍🗨️👁️‍🗨️";

    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = "👁️‍🗨️👁️‍🗨️👁️‍🗨️👁️‍🗨️👁️‍🗨️👁️‍🗨️";
}

/**
 * @tc.name: HandleOnDeleteAction007
 * @tc.desc: test testInput deleteAction for line break.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, HandleOnDeleteAction007, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    const std::string txt = "1\n23\n45\r\n6\n78\n9";
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step2. Set caretPosition and call Delete
     */
    pattern_->SetCaretPosition(15);
    pattern_->DeleteBackward(4);
    FlushLayoutTask(frameNode_);
    std::string result = "1\n23\n45\r\n6\n";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    pattern_->SetCaretPosition(9);
    pattern_->DeleteBackward(3);
    FlushLayoutTask(frameNode_);
    result = "1\n23\n6\n";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(3);
    FlushLayoutTask(frameNode_);
    result = "3\n6\n";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    pattern_->SetCaretPosition(2);
    pattern_->DeleteForward(2);
    FlushLayoutTask(frameNode_);
    result = "3\n";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();
}

/**
 * @tc.name: HandleOnDeleteAction008
 * @tc.desc: test testInput deleteAction for all case.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, HandleOnDeleteAction008, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    const std::string txt = "12345📡👨‍👩‍👧‍👦👁️\n🇨🇳3️⃣👁️‍🗨️\n67890";
    CreateTextField(txt, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    /**
     * @tc.step: step2. Set caretPosition and call Delete
     */
    pattern_->SetCaretPosition(42);
    pattern_->DeleteBackward(6);
    FlushLayoutTask(frameNode_);
    std::string result = "12345📡👨‍👩‍👧‍👦👁️\n🇨🇳3️⃣👁️‍🗨️";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    pattern_->SetCaretPosition(29);
    pattern_->DeleteBackward(2);
    FlushLayoutTask(frameNode_);
    result = "12345📡👨‍👩‍👧‍👦👁️\n👁️‍🗨️";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    pattern_->SetCaretPosition(0);
    pattern_->DeleteForward(6);
    FlushLayoutTask(frameNode_);
    result = "👨‍👩‍👧‍👦👁️\n👁️‍🗨️";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();

    pattern_->SetCaretPosition(14);
    pattern_->DeleteForward(1);
    FlushLayoutTask(frameNode_);
    result = "👨‍👩‍👧‍👦👁️👁️‍🗨️";
    EXPECT_EQ(pattern_->GetTextValue().compare(result), 0) << "Text is: " + pattern_->GetTextValue();
}

/**
 * @tc.name: GetGlobalPointsWithTransform
 * @tc.desc: test GetGlobalPointsWithTransform.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, GetGlobalPointsWithTransform, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    const std::string txt = "1234567890";
    CreateTextField(txt, "", [](TextFieldModelNG model) { model.SetType(TextInputType::TEXT); });
    GetFocus();

    /**
     * @tc.step: step2. Call GetGlobalPointsWithTransform.
     */
    std::vector<OffsetF> localPoints = { OffsetF(5.0f, 5.0f) };
    pattern_->selectOverlay_->hasTransform_ = true;
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    EXPECT_CALL(*mockRenderContext, GetPointTransform(_)).WillRepeatedly([](PointF& point) {
        point.SetX(-5.0f);
        point.SetY(5.0f);
    });
    pattern_->frameNode_.Upgrade()->renderContext_ = mockRenderContext;
    pattern_->selectOverlay_->GetGlobalPointsWithTransform(localPoints);
    EXPECT_EQ(localPoints[0].GetX(), -5.0f);
    EXPECT_EQ(localPoints[0].GetY(), 5.0f);
    pattern_->frameNode_.Upgrade()->renderContext_ = renderContext;
}

/**
 * @tc.name: GetGlobalRectWithTransform
 * @tc.desc: test GetGlobalRectWithTransform.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, GetGlobalRectWithTransform, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    const std::string txt = "1234567890";
    CreateTextField(txt, "", [](TextFieldModelNG model) { model.SetType(TextInputType::TEXT); });
    GetFocus();

    /**
     * @tc.step: step2. Call GetGlobalRectWithTransform.
     */
    pattern_->selectOverlay_->hasTransform_ = true;
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    EXPECT_CALL(*mockRenderContext, GetPointTransform(_)).WillRepeatedly([](PointF& point) {
        point.SetX(point.GetX());
        point.SetY(point.GetY());
    });
    RectF rect = RectF(OffsetF(5.0f, 5.0f), SizeF(5.0f, 5.0f));
    pattern_->selectOverlay_->GetGlobalRectWithTransform(rect);
    EXPECT_EQ(rect.GetOffset(), OffsetF(5.0f, 5.0f));
    EXPECT_EQ(rect.GetSize(), SizeF(5.0f, 5.0f));
}

/**
 * @tc.name: RevertLocalPointWithTransform
 * @tc.desc: test RevertLocalPointWithTransform.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, RevertLocalPointWithTransform, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    const std::string txt = "1234567890";
    CreateTextField(txt, "", [](TextFieldModelNG model) { model.SetType(TextInputType::TEXT); });
    GetFocus();

    /**
     * @tc.step: step2. Call RevertLocalPointWithTransform
     */
    pattern_->selectOverlay_->hasTransform_ = true;
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    EXPECT_CALL(*mockRenderContext, GetPointWithRevert(_)).WillRepeatedly([](PointF& point) {
        point.SetX(5.0f);
        point.SetY(5.0f);
    });
    OffsetF offset(-5.0f, 5.0f);
    pattern_->frameNode_.Upgrade()->renderContext_ = mockRenderContext;
    pattern_->selectOverlay_->RevertLocalPointWithTransform(offset);
    EXPECT_EQ(offset.GetX(), 5.0f);
    EXPECT_EQ(offset.GetY(), 5.0f);
    pattern_->frameNode_.Upgrade()->renderContext_ = renderContext;
}

/**
 * @tc.name: GetGlobalRectVertexWithTransform
 * @tc.desc: test GetGlobalRectVertexWithTransform.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, GetGlobalRectVertexWithTransform, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    const std::string txt = "1234567890";
    CreateTextField(txt, "", [](TextFieldModelNG model) { model.SetType(TextInputType::TEXT); });
    GetFocus();

    /**
     * @tc.step: step2. Call GetGlobalRectVertexWithTransform
     */
    pattern_->selectOverlay_->hasTransform_ = true;
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    EXPECT_CALL(*mockRenderContext, GetPointWithRevert(_)).WillRepeatedly([](PointF& point) {
        point.SetX(point.GetX());
        point.SetY(point.GetY());
    });
    RectF rect = RectF(OffsetF(5.0f, 5.0f), SizeF(5.0f, 5.0f));
    auto vertex = pattern_->selectOverlay_->GetGlobalRectVertexWithTransform(rect);
    EXPECT_EQ(vertex[0], OffsetF(5.0f, 5.0f));
    EXPECT_EQ(vertex[1], OffsetF(10.0f, 5.0f));
    EXPECT_EQ(vertex[2], OffsetF(5.0f, 10.0f));
    EXPECT_EQ(vertex[3], OffsetF(10.0f, 10.0f));
}

/**
 * @tc.name: GetLocalPointsWithTransform
 * @tc.desc: test GetLocalPointsWithTransform.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, GetLocalPointsWithTransform, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    const std::string txt = "1234567890";
    CreateTextField(txt, "", [](TextFieldModelNG model) { model.SetType(TextInputType::TEXT); });
    GetFocus();

    /**
     * @tc.step: step2. Call GetLocalPointsWithTransform
     */
    pattern_->selectOverlay_->hasTransform_ = true;
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    EXPECT_CALL(*mockRenderContext, GetPointWithRevert(_)).WillRepeatedly([](PointF& point) {
        point.SetX(point.GetX());
        point.SetY(point.GetY());
    });
    std::vector<OffsetF> localPoints = { OffsetF(5.0f, 5.0f) };
    pattern_->selectOverlay_->GetLocalPointsWithTransform(localPoints);
    EXPECT_EQ(localPoints[0].GetX(), 5.0f);
    EXPECT_EQ(localPoints[0].GetY(), 5.0f);
}

/**
 * @tc.name: GetLocalRectWithTransform
 * @tc.desc: test GetLocalRectWithTransform.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, GetLocalRectWithTransform, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    const std::string txt = "1234567890";
    CreateTextField(txt, "", [](TextFieldModelNG model) { model.SetType(TextInputType::TEXT); });
    GetFocus();

    /**
     * @tc.step: step2. Call GetLocalRectWithTransform
     */
    pattern_->selectOverlay_->hasTransform_ = true;
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    EXPECT_CALL(*mockRenderContext, GetPointWithRevert(_)).WillRepeatedly([](PointF& point) {
        point.SetX(point.GetX());
        point.SetY(point.GetY());
    });
    RectF rect(OffsetF(0.0f, 0.0f), SizeF(5.0f, 5.0f));
    pattern_->selectOverlay_->GetLocalRectWithTransform(rect);
    EXPECT_EQ(rect.GetOffset().GetX(), 0.0f);
    EXPECT_EQ(rect.GetOffset().GetY(), 0.0f);
    EXPECT_EQ(rect.GetSize().Width(), 5.0f);
    EXPECT_EQ(rect.GetSize().Height(), 5.0f);
}

/**
 * @tc.name: IsPointInRect
 * @tc.desc: test IsPointInRect.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, IsPointInRect, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    const std::string txt = "1234567890";
    CreateTextField(txt, "", [](TextFieldModelNG model) { model.SetType(TextInputType::TEXT); });
    GetFocus();

    /**
     * @tc.step: step2. Call IsPointInRect
     */
    OffsetF leftTop(0.0f, 0.0f);
    OffsetF leftBottom(0.0f, 5.0f);
    OffsetF rightTop(5.0f, 0.0f);
    OffsetF rightBottom(5.0f, 5.0f);
    OffsetF point(1.0f, 1.0f);
    auto ret = pattern_->selectOverlay_->IsPointInRect(point, leftBottom, rightBottom, rightTop, leftTop);
    EXPECT_TRUE(ret);
    point = OffsetF(-1.0f, -1.0f);
    ret = pattern_->selectOverlay_->IsPointInRect(point, leftBottom, rightBottom, rightTop, leftTop);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: GetSubParagraphByOffset
 * @tc.desc: test GetSubParagraphByOffset.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, GetSubParagraphByOffset, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    int32_t pos = 2;
    int32_t start = 2;
    int32_t end = 2;
    auto controller = pattern_->GetTextSelectController();

    controller->contentController_->content_[2] = WIDE_NEWLINE[0];
    controller->contentController_->content_[3] = WIDE_NEWLINE[0];
    controller->GetSubParagraphByOffset(pos, start, end);
    EXPECT_EQ(start, 3);
    EXPECT_EQ(end, 2);

    pos = 2;
    start = 2;
    end = 2;
    controller->contentController_->content_[2] = WIDE_NEWLINE[1];
    controller->GetSubParagraphByOffset(pos, start, end);
    EXPECT_EQ(start, 0);
    EXPECT_EQ(end, 3);

    pos = 0;
    start = 2;
    end = 2;
    controller->contentController_->content_.resize(7, WIDE_NEWLINE[1]);
    controller->GetSubParagraphByOffset(pos, start, end);
    EXPECT_EQ(start, 0);
    EXPECT_EQ(end, 3);
}

/**
 * @tc.name: MoveHandleToContentRect001
 * @tc.desc: test MoveHandleToContentRect.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, MoveHandleToContentRect001, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    auto controller = pattern_->GetTextSelectController();
    ASSERT_NE(controller, nullptr);
    RectF handleRect = RectF(OffsetF(5.0f, 5.0f), SizeF(5.0f, 5.0f));
    float boundaryAdjustment = 1.0f;
    auto textFiled = AceType::DynamicCast<TextFieldPattern>(pattern_);
    ASSERT_NE(textFiled, nullptr);
    textFiled->textRect_.SetRect(0.0f, 0.0f, 0.0f, 10.0f);
    controller->contentRect_.SetRect(0.0f, 6.0f, 0.0f, 6.0f);
    controller->MoveHandleToContentRect(handleRect, boundaryAdjustment);
    EXPECT_EQ(textFiled->textRect_.GetY(), 1.0f);
    EXPECT_EQ(textFiled->textRect_.GetX(), 0.0f);
}

/**
 * @tc.name: MoveHandleToContentRect002
 * @tc.desc: test MoveHandleToContentRect.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, MoveHandleToContentRect002, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    auto controller = pattern_->GetTextSelectController();
    ASSERT_NE(controller, nullptr);
    RectF handleRect = RectF(OffsetF(5.0f, 5.0f), SizeF(5.0f, 5.0f));
    float boundaryAdjustment = 1.0f;
    auto textFiled = AceType::DynamicCast<TextFieldPattern>(pattern_);
    ASSERT_NE(textFiled, nullptr);
    textFiled->textRect_.SetRect(0.0f, 0.0f, 0.0f, 10.0f);
    controller->contentRect_.SetRect(0.0f, 6.0f, 0.0f, 4.0f);
    controller->MoveHandleToContentRect(handleRect, boundaryAdjustment);
    EXPECT_EQ(textFiled->textRect_.GetY(), 0.0f);
    EXPECT_EQ(textFiled->textRect_.GetX(), 0.0f);
}

/**
 * @tc.name: MoveHandleToContentRect003
 * @tc.desc: test MoveHandleToContentRect.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, MoveHandleToContentRect003, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    auto controller = pattern_->GetTextSelectController();
    ASSERT_NE(controller, nullptr);
    RectF handleRect = RectF(OffsetF(5.0f, 5.0f), SizeF(5.0f, 5.0f));
    float boundaryAdjustment = 1.0f;
    auto textFiled = AceType::DynamicCast<TextFieldPattern>(pattern_);
    ASSERT_NE(textFiled, nullptr);
    textFiled->textRect_.SetRect(0.0f, 0.0f, 4.0f, 10.0f);
    controller->contentRect_.SetRect(6.0f, 6.0f, 0.0f, 4.0f);
    controller->MoveHandleToContentRect(handleRect, boundaryAdjustment);
    EXPECT_EQ(textFiled->textRect_.GetY(), 0.0f);
    EXPECT_EQ(textFiled->textRect_.GetX(), 1.0f);
}

/**
 * @tc.name: MoveHandleToContentRect004
 * @tc.desc: test MoveHandleToContentRect.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, MoveHandleToContentRect004, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    auto controller = pattern_->GetTextSelectController();
    ASSERT_NE(controller, nullptr);
    RectF handleRect = RectF(OffsetF(5.0f, 5.0f), SizeF(5.0f, 5.0f));
    float boundaryAdjustment = 1.0f;
    auto textFiled = AceType::DynamicCast<TextFieldPattern>(pattern_);
    ASSERT_NE(textFiled, nullptr);
    textFiled->textRect_.SetRect(0.0f, 0.0f, 4.0f, 10.0f);
    controller->contentRect_.SetRect(4.0f, 6.0f, 0.0f, 4.0f);
    controller->MoveHandleToContentRect(handleRect, boundaryAdjustment);
    EXPECT_EQ(textFiled->textRect_.GetY(), 0.0f);
    EXPECT_EQ(textFiled->textRect_.GetX(), -2.0f);
}

/**
 * @tc.name: MoveHandleToContentRect005
 * @tc.desc: test MoveHandleToContentRect.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, MoveHandleToContentRect005, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    auto controller = pattern_->GetTextSelectController();
    ASSERT_NE(controller, nullptr);
    RectF handleRect = RectF(OffsetF(-5.0f, 5.0f), SizeF(5.0f, 5.0f));
    float boundaryAdjustment = -10.0f;
    auto textFiled = AceType::DynamicCast<TextFieldPattern>(pattern_);
    ASSERT_NE(textFiled, nullptr);
    textFiled->textRect_.SetRect(0.0f, 0.0f, 4.0f, 10.0f);
    controller->contentRect_.SetRect(-6.0f, 6.0f, 0.0f, 4.0f);
    controller->MoveHandleToContentRect(handleRect, boundaryAdjustment);
    EXPECT_EQ(textFiled->textRect_.GetY(), 0.0f);
    EXPECT_EQ(textFiled->textRect_.GetX(), 0.0f);
}

/**
 * @tc.name: MoveCaretToContentRect001
 * @tc.desc: test MoveCaretToContentRect.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, MoveCaretToContentRect001, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    auto controller = pattern_->GetTextSelectController();
    ASSERT_NE(controller, nullptr);
    auto textFiled = AceType::DynamicCast<TextFieldPattern>(pattern_);
    ASSERT_NE(textFiled, nullptr);
    int32_t index = 0;
    SystemProperties::debugEnabled_ = true;
    textFiled->textRect_.SetRect(0.0f, 0.0f, 4.0f, 0.0f);
    controller->contentRect_.SetRect(2.0f, 2.0f, 1.0f, 4.0f);
    controller->MoveCaretToContentRect(index, TextAffinity::DOWNSTREAM, true, false);
    EXPECT_EQ(controller->caretInfo_.rect.GetX(), 2.0f);
    EXPECT_EQ(controller->caretInfo_.rect.GetY(), 0.0f);
}

/**
 * @tc.name: MoveCaretToContentRect002
 * @tc.desc: test MoveCaretToContentRect.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, MoveCaretToContentRect002, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    auto controller = pattern_->GetTextSelectController();
    ASSERT_NE(controller, nullptr);
    auto textFiled = AceType::DynamicCast<TextFieldPattern>(pattern_);
    ASSERT_NE(textFiled, nullptr);
    int32_t index = 30;
    SystemProperties::debugEnabled_ = false;
    textFiled->textRect_.SetRect(2.0f, 2.0f, 2.0f, 2.0f);
    controller->contentRect_.SetRect(0.0f, 0.0f, 1.0f, 4.0f);
    controller->MoveCaretToContentRect(index, TextAffinity::DOWNSTREAM, true, true);
    EXPECT_EQ(controller->caretInfo_.rect.GetX(), 1.0f);
    EXPECT_EQ(controller->caretInfo_.rect.GetY(), 2.0f);
}

/**
 * @tc.name: MoveCaretToContentRect003
 * @tc.desc: test MoveCaretToContentRect.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, MoveCaretToContentRect003, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    auto controller = pattern_->GetTextSelectController();
    ASSERT_NE(controller, nullptr);
    auto textFiled = AceType::DynamicCast<TextFieldPattern>(pattern_);
    ASSERT_NE(textFiled, nullptr);
    int32_t index = 30;
    SystemProperties::debugEnabled_ = false;
    textFiled->textRect_.SetRect(0.0f, 0.0f, 0.0f, 0.0f);
    controller->contentRect_.SetRect(2.0f, 2.0f, 5.0f, 4.0f);
    controller->MoveCaretToContentRect(index, TextAffinity::DOWNSTREAM, true, false);
    EXPECT_EQ(controller->caretInfo_.rect.GetX(), 2.0f);
    EXPECT_EQ(controller->caretInfo_.rect.GetY(), 0.0f);
}

/**
 * @tc.name: MoveCaretToContentRect004
 * @tc.desc: test MoveCaretToContentRect.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, MoveCaretToContentRect004, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    auto controller = pattern_->GetTextSelectController();
    ASSERT_NE(controller, nullptr);
    auto textFiled = AceType::DynamicCast<TextFieldPattern>(pattern_);
    ASSERT_NE(textFiled, nullptr);
    int32_t index = 0;
    SystemProperties::debugEnabled_ = false;
    textFiled->textRect_.SetRect(2.0f, 2.0f, 4.0f, 2.0f);
    controller->contentRect_.SetRect(0.0f, 0.0f, 1.0f, 4.0f);
    controller->MoveCaretToContentRect(index, TextAffinity::DOWNSTREAM, true, false);
    EXPECT_EQ(controller->caretInfo_.rect.GetX(), 1.0f);
    EXPECT_EQ(controller->caretInfo_.rect.GetY(), 2.0f);
}

/**
 * @tc.name: GetSelectParagraphByOffset001
 * @tc.desc: test GetSelectParagraphByOffset.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, GetSelectParagraphByOffset001, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    auto controller = pattern_->GetTextSelectController();
    ASSERT_NE(controller, nullptr);
    auto textFiled = AceType::DynamicCast<TextFieldPattern>(pattern_);
    ASSERT_NE(textFiled, nullptr);
    textFiled->selectOverlay_->isUsingMouse_ = true;
    SystemProperties::debugEnabled_ = false;
    Offset offset(50.0f, 50.0f);
    auto result = controller->GetSelectParagraphByOffset(offset);
    EXPECT_EQ(result.first, 0);
}

/**
 * @tc.name: GetSelectParagraphByOffset002
 * @tc.desc: test GetSelectParagraphByOffset.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, GetSelectParagraphByOffset002, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    auto controller = pattern_->GetTextSelectController();
    ASSERT_NE(controller, nullptr);
    auto textFiled = AceType::DynamicCast<TextFieldPattern>(pattern_);
    ASSERT_NE(textFiled, nullptr);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetGlyphIndexByCoordinate(testing::_, testing::_)).WillRepeatedly(Return(-5));
    controller->paragraph_ = paragraph;
    textFiled->selectOverlay_->isUsingMouse_ = false;
    SystemProperties::debugEnabled_ = true;
    Offset offset(50.0f, 50.0f);
    auto mockEngine = std::make_unique<MockDataDetectorInterface>();
    ASSERT_NE(mockEngine, nullptr);
    EXPECT_CALL(*mockEngine, GetWordSelection(testing::_, testing::_))
        .WillRepeatedly(Return(std::vector<int8_t> { 100, 100 }));
    DataDetectorMgr::GetInstance().engine_ = std::unique_ptr<OHOS::Ace::DataDetectorInterface>(
        static_cast<OHOS::Ace::DataDetectorInterface*>(mockEngine.release()));
    ASSERT_NE(DataDetectorMgr::GetInstance().engine_, nullptr);
    auto result = controller->GetSelectParagraphByOffset(offset);
    EXPECT_EQ(result.second, 26);
}

/**
 * @tc.name: GetGraphemeClusterLength001
 * @tc.desc: test GetGraphemeClusterLength.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, GetGraphemeClusterLength001, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    auto controller = pattern_->GetTextSelectController();
    ASSERT_NE(controller, nullptr);
    std::u16string text = u"ab\U0001F600";
    int32_t extend = 3;
    bool checkPrev = true;
    auto result = controller->GetGraphemeClusterLength(text, extend, checkPrev);
    EXPECT_EQ(result, 2);
}

/**
 * @tc.name: GetGraphemeClusterLength002
 * @tc.desc: test GetGraphemeClusterLength.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, GetGraphemeClusterLength002, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    auto controller = pattern_->GetTextSelectController();
    ASSERT_NE(controller, nullptr);
    std::u16string text = u"ab\U0001F600";
    int32_t extend = 10;
    bool checkPrev = false;
    auto result = controller->GetGraphemeClusterLength(text, extend, checkPrev);
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: GetGraphemeClusterLength003
 * @tc.desc: test GetGraphemeClusterLength.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTest, GetGraphemeClusterLength003, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    auto controller = pattern_->GetTextSelectController();
    ASSERT_NE(controller, nullptr);
    std::u16string text = u"ab\U0001F600";
    int32_t extend = 2;
    bool checkPrev = false;
    auto result = controller->GetGraphemeClusterLength(text, extend, checkPrev);
    EXPECT_EQ(result, 2);
}
}
