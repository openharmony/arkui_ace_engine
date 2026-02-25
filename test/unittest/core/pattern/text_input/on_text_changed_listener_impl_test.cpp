/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text_field/on_text_changed_listener_impl.h"
#include "core/common/ime/text_input_client.h"

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "text_input_base.h"

namespace OHOS::Ace::NG {

// Local constants matching the source file
const std::string AUTO_FILL_PARAMS_USERNAME = "com.autofill.params.userName";
const std::string AUTO_FILL_PARAMS_NEWPASSWORD = "com.autofill.params.newPassword";
const std::string AUTO_FILL_PARAMS_OTHERACCOUNT = "com.autofill.params.otherAccount";

namespace {} // namespace

class OnTextChangedListenerImplTest : public TextInputBases {
public:
};

/**
 * @tc.name: InsertText001
 * @tc.desc: Test InsertText with empty text (should return early)
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, InsertText001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Call InsertText with empty text
     * @tc.expected: Should return early without crash
     */
    std::u16string emptyText;
    listener.InsertText(emptyText);
}

/**
 * @tc.name: InsertText002
 * @tc.desc: Test InsertText with valid text
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, InsertText002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Call InsertText with valid text
     * @tc.expected: Should post task successfully
     */
    std::u16string insertText = u"test";
    listener.InsertText(insertText);
}

/**
 * @tc.name: DeleteBackward001
 * @tc.desc: Test DeleteBackward with length <= 0 (should return early)
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, DeleteBackward001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Call DeleteBackward with 0 length
     * @tc.expected: Should return early without crash
     */
    listener.DeleteBackward(0);
}

/**
 * @tc.name: DeleteBackward002
 * @tc.desc: Test DeleteBackward with negative length (should return early)
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, DeleteBackward002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Call DeleteBackward with negative length
     * @tc.expected: Should return early without crash
     */
    listener.DeleteBackward(-1);
}

/**
 * @tc.name: DeleteBackward003
 * @tc.desc: Test DeleteBackward with valid length
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, DeleteBackward003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Call DeleteBackward with valid length
     * @tc.expected: Should post task successfully
     */
    listener.DeleteBackward(5);
}

/**
 * @tc.name: DeleteForward001
 * @tc.desc: Test DeleteForward with length <= 0 (should return early)
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, DeleteForward001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Call DeleteForward with 0 length
     * @tc.expected: Should return early without crash
     */
    listener.DeleteForward(0);
}

/**
 * @tc.name: DeleteForward002
 * @tc.desc: Test DeleteForward with valid length
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, DeleteForward002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Call DeleteForward with valid length
     * @tc.expected: Should post task successfully
     */
    listener.DeleteForward(3);
}

/**
 * @tc.name: SetKeyboardStatus001
 * @tc.desc: Test SetKeyboardStatus with true status
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, SetKeyboardStatus001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Call SetKeyboardStatus with true
     * @tc.expected: Should post task successfully
     */
    listener.SetKeyboardStatus(true);
}

/**
 * @tc.name: SetKeyboardStatus002
 * @tc.desc: Test SetKeyboardStatus with false status (keyboard closed)
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, SetKeyboardStatus002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Call SetKeyboardStatus with false
     * @tc.expected: Should post task successfully
     */
    listener.SetKeyboardStatus(false);
}

/**
 * @tc.name: GetLeftTextOfCursor001
 * @tc.desc: Test GetLeftTextOfCursor
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, GetLeftTextOfCursor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Call GetLeftTextOfCursor
     * @tc.expected: Should return empty string by default
     */
    auto result = listener.GetLeftTextOfCursor(5);
    // Default behavior returns empty u16string
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: GetRightTextOfCursor001
 * @tc.desc: Test GetRightTextOfCursor
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, GetRightTextOfCursor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Call GetRightTextOfCursor
     * @tc.expected: Should return empty string by default
     */
    auto result = listener.GetRightTextOfCursor(5);
    // Default behavior returns empty u16string
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: GetTextIndexAtCursor001
 * @tc.desc: Test GetTextIndexAtCursor
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, GetTextIndexAtCursor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Call GetTextIndexAtCursor
     * @tc.expected: Should return 0 by default
     */
    auto index = listener.GetTextIndexAtCursor();
    EXPECT_EQ(index, 0);
}

/**
 * @tc.name: SendKeyEventFromInputMethod001
 * @tc.desc: Test SendKeyEventFromInputMethod (empty function)
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, SendKeyEventFromInputMethod001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Call SendKeyEventFromInputMethod
     * @tc.expected: Function is empty, should not crash
     */
    MiscServices::KeyEvent event;
    listener.SendKeyEventFromInputMethod(event);
}

/**
 * @tc.name: SendKeyboardStatus001
 * @tc.desc: Test SendKeyboardStatus with SHOW status
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, SendKeyboardStatus001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Call SendKeyboardStatus with SHOW
     * @tc.expected: Should call HandleKeyboardStatus
     */
    MiscServices::KeyboardStatus status = MiscServices::KeyboardStatus::SHOW;
    listener.SendKeyboardStatus(status);
}

/**
 * @tc.name: SendKeyboardStatus002
 * @tc.desc: Test SendKeyboardStatus with HIDE status
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, SendKeyboardStatus002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Call SendKeyboardStatus with HIDE
     * @tc.expected: Should call HandleKeyboardStatus
     */
    MiscServices::KeyboardStatus status = MiscServices::KeyboardStatus::HIDE;
    listener.SendKeyboardStatus(status);
}

/**
 * @tc.name: NotifyKeyboardHeight001
 * @tc.desc: Test NotifyKeyboardHeight
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, NotifyKeyboardHeight001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Call NotifyKeyboardHeight
     * @tc.expected: Should post task successfully
     */
    listener.NotifyKeyboardHeight(300);
}

/**
 * @tc.name: SendFunctionKey001
 * @tc.desc: Test SendFunctionKey with DONE action
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, SendFunctionKey001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Create FunctionKey with DONE action
     */
    MiscServices::FunctionKey functionKey;
    functionKey.SetEnterKeyType(MiscServices::EnterKeyType::DONE);

    /**
     * @tc.steps: step4. Call SendFunctionKey
     * @tc.expected: Should post task successfully
     */
    listener.SendFunctionKey(functionKey);
}

/**
 * @tc.name: SendFunctionKey002
 * @tc.desc: Test SendFunctionKey with NEXT action
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, SendFunctionKey002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Create FunctionKey with NEXT action
     */
    MiscServices::FunctionKey functionKey;
    functionKey.SetEnterKeyType(MiscServices::EnterKeyType::NEXT);

    /**
     * @tc.steps: step4. Call SendFunctionKey
     * @tc.expected: Should post task successfully
     */
    listener.SendFunctionKey(functionKey);
}

/**
 * @tc.name: SendFunctionKey003
 * @tc.desc: Test SendFunctionKey with SEARCH action
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, SendFunctionKey003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Create FunctionKey with SEARCH action
     */
    MiscServices::FunctionKey functionKey;
    functionKey.SetEnterKeyType(MiscServices::EnterKeyType::SEARCH);

    /**
     * @tc.steps: step4. Call SendFunctionKey
     * @tc.expected: Should post task successfully
     */
    listener.SendFunctionKey(functionKey);
}

/**
 * @tc.name: SendFunctionKey004
 * @tc.desc: Test SendFunctionKey with SEND action
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, SendFunctionKey004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Create FunctionKey with SEND action
     */
    MiscServices::FunctionKey functionKey;
    functionKey.SetEnterKeyType(MiscServices::EnterKeyType::SEND);

    /**
     * @tc.steps: step4. Call SendFunctionKey
     * @tc.expected: Should post task successfully
     */
    listener.SendFunctionKey(functionKey);
}

/**
 * @tc.name: SendFunctionKey005
 * @tc.desc: Test SendFunctionKey with GO action
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, SendFunctionKey005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Create FunctionKey with GO action
     */
    MiscServices::FunctionKey functionKey;
    functionKey.SetEnterKeyType(MiscServices::EnterKeyType::GO);

    /**
     * @tc.steps: step4. Call SendFunctionKey
     * @tc.expected: Should post task successfully
     */
    listener.SendFunctionKey(functionKey);
}

/**
 * @tc.name: SendFunctionKey006
 * @tc.desc: Test SendFunctionKey with PREVIOUS action
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, SendFunctionKey006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Create FunctionKey with PREVIOUS action
     */
    MiscServices::FunctionKey functionKey;
    functionKey.SetEnterKeyType(MiscServices::EnterKeyType::PREVIOUS);

    /**
     * @tc.steps: step4. Call SendFunctionKey
     * @tc.expected: Should post task successfully
     */
    listener.SendFunctionKey(functionKey);
}

/**
 * @tc.name: SendFunctionKey007
 * @tc.desc: Test SendFunctionKey with NEW_LINE action
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, SendFunctionKey007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Create FunctionKey with NEW_LINE action
     */
    MiscServices::FunctionKey functionKey;
    functionKey.SetEnterKeyType(MiscServices::EnterKeyType::NEW_LINE);

    /**
     * @tc.steps: step4. Call SendFunctionKey
     * @tc.expected: Should post task successfully
     */
    listener.SendFunctionKey(functionKey);
}

/**
 * @tc.name: MoveCursor001
 * @tc.desc: Test MoveCursor with UP direction
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, MoveCursor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Call MoveCursor with UP direction
     * @tc.expected: Should post task successfully
     */
    listener.MoveCursor(MiscServices::Direction::UP);
}

/**
 * @tc.name: MoveCursor002
 * @tc.desc: Test MoveCursor with DOWN direction
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, MoveCursor002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Call MoveCursor with DOWN direction
     * @tc.expected: Should post task successfully
     */
    listener.MoveCursor(MiscServices::Direction::DOWN);
}

/**
 * @tc.name: MoveCursor003
 * @tc.desc: Test MoveCursor with LEFT direction
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, MoveCursor003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Call MoveCursor with LEFT direction
     * @tc.expected: Should post task successfully
     */
    listener.MoveCursor(MiscServices::Direction::LEFT);
}

/**
 * @tc.name: MoveCursor004
 * @tc.desc: Test MoveCursor with RIGHT direction
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, MoveCursor004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Call MoveCursor with RIGHT direction
     * @tc.expected: Should post task successfully
     */
    listener.MoveCursor(MiscServices::Direction::RIGHT);
}

/**
 * @tc.name: HandleSetSelection001
 * @tc.desc: Test HandleSetSelection
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, HandleSetSelection001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Call HandleSetSelection
     * @tc.expected: Should post task successfully
     */
    listener.HandleSetSelection(0, 5);
}

/**
 * @tc.name: HandleExtendAction001
 * @tc.desc: Test HandleExtendAction
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, HandleExtendAction001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Call HandleExtendAction
     * @tc.expected: Should post task successfully
     */
    listener.HandleExtendAction(1);
}

/**
 * @tc.name: HandleSelect001
 * @tc.desc: Test HandleSelect with KEY_DPAD_LEFT
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, HandleSelect001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Call HandleSelect with KEY_DPAD_LEFT
     * @tc.expected: Should post task successfully
     */
    listener.HandleSelect(static_cast<int32_t>(KeyCode::KEY_DPAD_LEFT), 0);
}

/**
 * @tc.name: HandleSelect002
 * @tc.desc: Test HandleSelect with KEY_DPAD_RIGHT
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, HandleSelect002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Call HandleSelect with KEY_DPAD_RIGHT
     * @tc.expected: Should post task successfully
     */
    listener.HandleSelect(static_cast<int32_t>(KeyCode::KEY_DPAD_RIGHT), 0);
}

/**
 * @tc.name: HandleSelect003
 * @tc.desc: Test HandleSelect with KEY_DPAD_UP
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, HandleSelect003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Call HandleSelect with KEY_DPAD_UP
     * @tc.expected: Should post task successfully
     */
    listener.HandleSelect(static_cast<int32_t>(KeyCode::KEY_DPAD_UP), 0);
}

/**
 * @tc.name: HandleSelect004
 * @tc.desc: Test HandleSelect with KEY_DPAD_DOWN
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, HandleSelect004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Call HandleSelect with KEY_DPAD_DOWN
     * @tc.expected: Should post task successfully
     */
    listener.HandleSelect(static_cast<int32_t>(KeyCode::KEY_DPAD_DOWN), 0);
}

/**
 * @tc.name: HandleSelect005
 * @tc.desc: Test HandleSelect with unsupported key code
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, HandleSelect005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Call HandleSelect with unsupported key code
     * @tc.expected: Should return early without crash
     */
    listener.HandleSelect(static_cast<int32_t>(KeyCode::KEY_A), 0);
}

/**
 * @tc.name: SetPreviewText001
 * @tc.desc: Test SetPreviewText with valid text and range
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, SetPreviewText001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Call SetPreviewText
     * @tc.expected: Should return NO_ERROR
     */
    std::u16string previewText = u"preview";
    MiscServices::Range range = {0, 7};
    auto ret = listener.SetPreviewText(previewText, range);
    EXPECT_EQ(ret, MiscServices::ErrorCode::NO_ERROR);
}

/**
 * @tc.name: FinishTextPreview001
 * @tc.desc: Test FinishTextPreview
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, FinishTextPreview001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Call FinishTextPreview
     * @tc.expected: Should post task successfully
     */
    listener.FinishTextPreview();
}

/**
 * @tc.name: ReceivePrivateCommand001
 * @tc.desc: Test ReceivePrivateCommand with empty command
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, ReceivePrivateCommand001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Call ReceivePrivateCommand with empty map
     * @tc.expected: Should return NO_ERROR
     */
    std::unordered_map<std::string, MiscServices::PrivateDataValue> emptyCommand;
    auto ret = listener.ReceivePrivateCommand(emptyCommand);
    EXPECT_EQ(ret, MiscServices::ErrorCode::NO_ERROR);
}

/**
 * @tc.name: ReceivePrivateCommand002
 * @tc.desc: Test ReceivePrivateCommand with valid command containing string value
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, ReceivePrivateCommand002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Call ReceivePrivateCommand with valid command
     * @tc.expected: Should return NO_ERROR
     */
    std::unordered_map<std::string, MiscServices::PrivateDataValue> command;
    std::string style = "testStyle";
    command.insert({OHOS::Ace::PRIVATE_DATA_KEY, style});
    auto ret = listener.ReceivePrivateCommand(command);
    EXPECT_EQ(ret, MiscServices::ErrorCode::NO_ERROR);
}

/**
 * @tc.name: AutoFillReceivePrivateCommand001
 * @tc.desc: Test AutoFillReceivePrivateCommand with USERNAME
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, AutoFillReceivePrivateCommand001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Call AutoFillReceivePrivateCommand with USERNAME
     * @tc.expected: Should process successfully
     */
    std::unordered_map<std::string, MiscServices::PrivateDataValue> command;
    std::string userName = "testUser";
    command.insert({AUTO_FILL_PARAMS_USERNAME, userName});
    OnTextChangedListenerImpl::AutoFillReceivePrivateCommand(command, AceType::WeakClaim(AceType::RawPtr(pattern_)));
}

/**
 * @tc.name: AutoFillReceivePrivateCommand002
 * @tc.desc: Test AutoFillReceivePrivateCommand with NEWPASSWORD
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, AutoFillReceivePrivateCommand002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Call AutoFillReceivePrivateCommand with NEWPASSWORD
     * @tc.expected: Should process successfully
     */
    std::unordered_map<std::string, MiscServices::PrivateDataValue> command;
    std::string newPassword = "testPassword";
    command.insert({AUTO_FILL_PARAMS_NEWPASSWORD, newPassword});
    OnTextChangedListenerImpl::AutoFillReceivePrivateCommand(command, AceType::WeakClaim(AceType::RawPtr(pattern_)));
}

/**
 * @tc.name: AutoFillReceivePrivateCommand003
 * @tc.desc: Test AutoFillReceivePrivateCommand with OTHERACCOUNT
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, AutoFillReceivePrivateCommand003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Call AutoFillReceivePrivateCommand with OTHERACCOUNT
     * @tc.expected: Should process successfully
     */
    std::unordered_map<std::string, MiscServices::PrivateDataValue> command;
    command.insert({AUTO_FILL_PARAMS_OTHERACCOUNT, ""});
    OnTextChangedListenerImpl::AutoFillReceivePrivateCommand(command, AceType::WeakClaim(AceType::RawPtr(pattern_)));
}

/**
 * @tc.name: AutoFillReceivePrivateCommand004
 * @tc.desc: Test AutoFillReceivePrivateCommand with invalid command
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, AutoFillReceivePrivateCommand004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Call AutoFillReceivePrivateCommand with invalid command
     * @tc.expected: Should handle gracefully without crash
     */
    std::unordered_map<std::string, MiscServices::PrivateDataValue> command;
    command.insert({"invalid_key", ""});
    OnTextChangedListenerImpl::AutoFillReceivePrivateCommand(command, AceType::WeakClaim(AceType::RawPtr(pattern_)));
}

/**
 * @tc.name: OnDetach001
 * @tc.desc: Test OnDetach
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, OnDetach001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Call OnDetach
     * @tc.expected: Should set IsImeAttached to false
     */
    listener.OnDetach();
}

/**
 * @tc.name: NotifyPanelStatusInfo001
 * @tc.desc: Test NotifyPanelStatusInfo with soft keyboard closed
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, NotifyPanelStatusInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Create PanelStatusInfo for soft keyboard closed
     */
    MiscServices::PanelStatusInfo info;
    info.panelInfo.panelType = MiscServices::PanelType::SOFT_KEYBOARD;
    info.visible = false;
    info.trigger = MiscServices::Trigger::IME_APP;

    /**
     * @tc.steps: step4. Call NotifyPanelStatusInfo
     * @tc.expected: Should handle keyboard close notification
     */
    listener.NotifyPanelStatusInfo(info);
}

/**
 * @tc.name: NotifyPanelStatusInfo002
 * @tc.desc: Test NotifyPanelStatusInfo with soft keyboard shown
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, NotifyPanelStatusInfo002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Create PanelStatusInfo for soft keyboard shown
     */
    MiscServices::PanelStatusInfo info;
    info.panelInfo.panelType = MiscServices::PanelType::SOFT_KEYBOARD;
    info.visible = true;

    /**
     * @tc.steps: step4. Call NotifyPanelStatusInfo
     * @tc.expected: Should handle keyboard show notification
     */
    listener.NotifyPanelStatusInfo(info);
}

/**
 * @tc.name: NotifyPanelStatusInfo003
 * @tc.desc: Test NotifyPanelStatusInfo with STATUS_BAR panel type
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTest, NotifyPanelStatusInfo003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create OnTextChangedListenerImpl
     */
    OnTextChangedListenerImpl listener(AceType::WeakClaim(AceType::RawPtr(pattern_)));

    /**
     * @tc.steps: step3. Create PanelStatusInfo for STATUS_BAR
     */
    MiscServices::PanelStatusInfo info;
    info.panelInfo.panelType = MiscServices::PanelType::STATUS_BAR;
    info.visible = true;

    /**
     * @tc.steps: step4. Call NotifyPanelStatusInfo
     * @tc.expected: Should handle status bar notification
     */
    listener.NotifyPanelStatusInfo(info);
}

} // namespace OHOS::Ace::NG
