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

#include "text_input_base.h"
#include "base/utils/string_utils.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class TextFieldKeyEventTest : public TextInputBases {
public:
};

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
 * @tc.name: KeyEventChar005
 * @tc.desc: Test NumLock + KEY_NUMPAD_0-9/. symbols input
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldKeyEventTest, KeyEventChar005, TestSize.Level1)
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
    event.numLock = true;
    event.action = KeyAction::DOWN;
    std::vector<KeyCode> presscodes = {};
    event.pressedCodes = presscodes;
    const std::unordered_map<KeyCode, wchar_t> symbols = {
        { KeyCode::KEY_NUMPAD_0, L'0' },
        { KeyCode::KEY_NUMPAD_1, L'1' },
        { KeyCode::KEY_NUMPAD_2, L'2' },
        { KeyCode::KEY_NUMPAD_3, L'3' },
        { KeyCode::KEY_NUMPAD_4, L'4' },
        { KeyCode::KEY_NUMPAD_5, L'5' },
        { KeyCode::KEY_NUMPAD_6, L'6' },
        { KeyCode::KEY_NUMPAD_7, L'7' },
        { KeyCode::KEY_NUMPAD_8, L'8' },
        { KeyCode::KEY_NUMPAD_9, L'9' },
        { KeyCode::KEY_NUMPAD_DOT, L'.' },
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
    auto onCopy = [expectStr](const std::u16string& str) { EXPECT_EQ(expectStr, StringUtils::Str16ToStr8(str)); };
    auto onPaste = [expectStr](const std::u16string& str) { EXPECT_EQ(expectStr, StringUtils::Str16ToStr8(str)); };
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

HWTEST_F(TextFieldKeyEventTest, KeyEvent010, TestSize.Level1)
{
    KeyEvent keyEvent;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.code = KeyCode::KEY_TAB;
    std::vector<KeyCode> presscodes = {};
    keyEvent.pressedCodes = presscodes;
    keyEvent.pressedCodes.clear();
    keyEvent.pressedCodes.push_back(KeyCode::KEY_CTRL_LEFT);
    keyEvent.pressedCodes.push_back(KeyCode::KEY_A);
    keyEvent.code = KeyCode::KEY_A;
    CreateTextField(DEFAULT_TEXT);
    pattern_->HandleSetSelection(5, 10, false);
    pattern_->isFocusedBeforeClick_ = false;
    GetFocus();
    pattern_->needToRequestKeyboardOnFocus_  = false;
    pattern_->needToRequestKeyboardInner_  = false;
    auto ret = pattern_->OnKeyEvent(keyEvent);
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
    auto callback = [expectStr](const std::u16string& str) { EXPECT_EQ(expectStr, StringUtils::Str16ToStr8(str)); };
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
    auto onCopy = [expectStr](const std::u16string& str) { EXPECT_EQ(expectStr, StringUtils::Str16ToStr8(str)); };
    auto onPaste = [expectStr](const std::u16string& str) { EXPECT_EQ(expectStr, StringUtils::Str16ToStr8(str)); };
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
    // ctrl+z undo, for this record
    pattern_->CheckAndUpdateRecordBeforeOperation();
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
    EXPECT_EQ(pattern_->GetTextValue(), DEFAULT_TEXT);
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
        EXPECT_EQ(StringUtils::Str16ToStr8(commonEvent.text_), "abcdefghijklmnopqrstuvwxyz");
    };
    CreateTextField(DEFAULT_TEXT, DEFAULT_PLACE_HOLDER, [&](TextFieldModel& model) -> void {
        model.SetOnSubmit(onSubmit);
    });
    GetFocus();

    pattern_->PerformAction(TextInputAction::DONE, true);
    EXPECT_TRUE(pattern_->GetCursorVisible());
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
        EXPECT_EQ(StringUtils::Str16ToStr8(commonEvent.text_), "abcdefghijklmnopqrstuvwxyz");
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
}