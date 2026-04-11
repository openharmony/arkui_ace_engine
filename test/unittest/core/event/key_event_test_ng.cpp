/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"

#define private public
#define protected public
#include "core/event/key_event.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

class KeyEventTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
};

/**
 * @tc.name: KeyEvent_HasKey001
 * @tc.desc: Test HasKey returns true when pressedCodes contains the target key.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_HasKey001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct KeyEvent with pressedCodes {KEY_A, KEY_CTRL_LEFT}.
     * @tc.expected: HasKey(KEY_A) returns true, HasKey(KEY_CTRL_LEFT) returns true.
     */
    KeyEvent event;
    event.pressedCodes = { KeyCode::KEY_A, KeyCode::KEY_CTRL_LEFT };

    EXPECT_TRUE(event.HasKey(KeyCode::KEY_A));
    EXPECT_TRUE(event.HasKey(KeyCode::KEY_CTRL_LEFT));
}

/**
 * @tc.name: KeyEvent_HasKey002
 * @tc.desc: Test HasKey returns false when pressedCodes does not contain the target key.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_HasKey002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct KeyEvent with pressedCodes {KEY_A}.
     * @tc.expected: HasKey(KEY_B) returns false.
     */
    KeyEvent event;
    event.pressedCodes = { KeyCode::KEY_A };

    EXPECT_FALSE(event.HasKey(KeyCode::KEY_B));
}

/**
 * @tc.name: KeyEvent_HasKey003
 * @tc.desc: Test HasKey returns false when pressedCodes is empty.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_HasKey003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct KeyEvent with empty pressedCodes.
     * @tc.expected: HasKey returns false for any key.
     */
    KeyEvent event;
    EXPECT_FALSE(event.HasKey(KeyCode::KEY_A));
}

/**
 * @tc.name: KeyEvent_IsKey001
 * @tc.desc: Test IsKey returns true when pressedCodes suffix matches expectCodes exactly.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_IsKey001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. pressedCodes = {KEY_CTRL_LEFT, KEY_A}, expect = {KEY_CTRL_LEFT, KEY_A}.
     * @tc.expected: IsKey returns true.
     */
    KeyEvent event;
    event.pressedCodes = { KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_A };

    EXPECT_TRUE(event.IsKey({ KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_A }));
}

/**
 * @tc.name: KeyEvent_IsKey002
 * @tc.desc: Test IsKey returns true when expectCodes is a suffix of pressedCodes.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_IsKey002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. pressedCodes = {KEY_SHIFT_LEFT, KEY_CTRL_LEFT, KEY_A}, expect = {KEY_CTRL_LEFT, KEY_A}.
     * @tc.expected: IsKey returns true because suffix matches.
     */
    KeyEvent event;
    event.pressedCodes = { KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_A };

    EXPECT_TRUE(event.IsKey({ KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_A }));
}

/**
 * @tc.name: KeyEvent_IsKey003
 * @tc.desc: Test IsKey returns false when expectCodes is longer than pressedCodes.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_IsKey003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. pressedCodes = {KEY_A}, expect = {KEY_CTRL_LEFT, KEY_A}.
     * @tc.expected: IsKey returns false because expectCodes is longer.
     */
    KeyEvent event;
    event.pressedCodes = { KeyCode::KEY_A };

    EXPECT_FALSE(event.IsKey({ KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_A }));
}

/**
 * @tc.name: KeyEvent_IsKey004
 * @tc.desc: Test IsKey returns false when pressedCodes is empty.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_IsKey004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. pressedCodes is empty, expect = {KEY_A}.
     * @tc.expected: IsKey returns false.
     */
    KeyEvent event;
    EXPECT_FALSE(event.IsKey({ KeyCode::KEY_A }));
}

/**
 * @tc.name: KeyEvent_IsKey005
 * @tc.desc: Test IsKey returns false when suffix does not match.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_IsKey005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. pressedCodes = {KEY_CTRL_LEFT, KEY_B}, expect = {KEY_CTRL_LEFT, KEY_A}.
     * @tc.expected: IsKey returns false because last key differs.
     */
    KeyEvent event;
    event.pressedCodes = { KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_B };

    EXPECT_FALSE(event.IsKey({ KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_A }));
}

/**
 * @tc.name: KeyEvent_IsExactlyKey001
 * @tc.desc: Test IsExactlyKey returns true when sizes match and suffix matches.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_IsExactlyKey001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. pressedCodes = {KEY_CTRL_LEFT, KEY_A}, expect = {KEY_CTRL_LEFT, KEY_A}.
     * @tc.expected: IsExactlyKey returns true because size matches and suffix matches.
     */
    KeyEvent event;
    event.pressedCodes = { KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_A };

    EXPECT_TRUE(event.IsExactlyKey({ KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_A }));
}

/**
 * @tc.name: KeyEvent_IsExactlyKey002
 * @tc.desc: Test IsExactlyKey returns false when sizes do not match.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_IsExactlyKey002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. pressedCodes = {KEY_SHIFT_LEFT, KEY_CTRL_LEFT, KEY_A}, expect = {KEY_CTRL_LEFT, KEY_A}.
     * @tc.expected: IsExactlyKey returns false because sizes differ.
     */
    KeyEvent event;
    event.pressedCodes = { KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_A };

    EXPECT_FALSE(event.IsExactlyKey({ KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_A }));
}

/**
 * @tc.name: KeyEvent_IsExactlyKey003
 * @tc.desc: Test IsExactlyKey excludes KEY_FN from pressed count.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_IsExactlyKey003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. pressedCodes = {KEY_FN, KEY_A}, expect = {KEY_A}.
     * @tc.expected: IsExactlyKey returns true because KEY_FN is excluded from count.
     */
    KeyEvent event;
    event.pressedCodes = { KeyCode::KEY_FN, KeyCode::KEY_A };

    EXPECT_TRUE(event.IsExactlyKey({ KeyCode::KEY_A }));
}

/**
 * @tc.name: KeyEvent_IsCtrlWith001
 * @tc.desc: Test IsCtrlWith returns true when Ctrl+key is in pressedCodes.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_IsCtrlWith001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. pressedCodes = {KEY_CTRL_LEFT, KEY_A}.
     * @tc.expected: IsCtrlWith(KEY_A) returns true.
     */
    KeyEvent event;
    event.pressedCodes = { KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_A };

    EXPECT_TRUE(event.IsCtrlWith(KeyCode::KEY_A));
}

/**
 * @tc.name: KeyEvent_IsCtrlWith002
 * @tc.desc: Test IsCtrlWith returns true with right Ctrl key.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_IsCtrlWith002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. pressedCodes = {KEY_CTRL_RIGHT, KEY_C}.
     * @tc.expected: IsCtrlWith(KEY_C) returns true.
     */
    KeyEvent event;
    event.pressedCodes = { KeyCode::KEY_CTRL_RIGHT, KeyCode::KEY_C };

    EXPECT_TRUE(event.IsCtrlWith(KeyCode::KEY_C));
}

/**
 * @tc.name: KeyEvent_IsCtrlWith003
 * @tc.desc: Test IsCtrlWith returns false without Ctrl key.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_IsCtrlWith003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. pressedCodes = {KEY_SHIFT_LEFT, KEY_A}.
     * @tc.expected: IsCtrlWith(KEY_A) returns false.
     */
    KeyEvent event;
    event.pressedCodes = { KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_A };

    EXPECT_FALSE(event.IsCtrlWith(KeyCode::KEY_A));
}

/**
 * @tc.name: KeyEvent_IsShiftWith001
 * @tc.desc: Test IsShiftWith returns true when Shift+key is in pressedCodes.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_IsShiftWith001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. pressedCodes = {KEY_SHIFT_LEFT, KEY_A, KEY_B}.
     * @tc.expected: IsShiftWith(KEY_B) returns true.
     */
    KeyEvent event;
    event.pressedCodes = { KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_A, KeyCode::KEY_B };

    EXPECT_TRUE(event.IsShiftWith(KeyCode::KEY_B));
}

/**
 * @tc.name: KeyEvent_IsShiftWith002
 * @tc.desc: Test IsShiftWith returns false without Shift key.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_IsShiftWith002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. pressedCodes = {KEY_A, KEY_B}.
     * @tc.expected: IsShiftWith(KEY_B) returns false.
     */
    KeyEvent event;
    event.pressedCodes = { KeyCode::KEY_A, KeyCode::KEY_B };

    EXPECT_FALSE(event.IsShiftWith(KeyCode::KEY_B));
}

/**
 * @tc.name: KeyEvent_IsExactlyShiftWith001
 * @tc.desc: Test IsExactlyShiftWith returns true with ShiftLeft+key only.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_IsExactlyShiftWith001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. pressedCodes = {KEY_SHIFT_LEFT, KEY_A}.
     * @tc.expected: IsExactlyShiftWith(KEY_A) returns true.
     */
    KeyEvent event;
    event.pressedCodes = { KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_A };

    EXPECT_TRUE(event.IsExactlyShiftWith(KeyCode::KEY_A));
}

/**
 * @tc.name: KeyEvent_IsExactlyShiftWith002
 * @tc.desc: Test IsExactlyShiftWith returns true with ShiftRight+key only.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_IsExactlyShiftWith002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. pressedCodes = {KEY_SHIFT_RIGHT, KEY_C}.
     * @tc.expected: IsExactlyShiftWith(KEY_C) returns true.
     */
    KeyEvent event;
    event.pressedCodes = { KeyCode::KEY_SHIFT_RIGHT, KeyCode::KEY_C };

    EXPECT_TRUE(event.IsExactlyShiftWith(KeyCode::KEY_C));
}

/**
 * @tc.name: KeyEvent_IsExactlyShiftWith003
 * @tc.desc: Test IsExactlyShiftWith returns false when extra keys are present.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_IsExactlyShiftWith003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. pressedCodes = {KEY_CTRL_LEFT, KEY_SHIFT_LEFT, KEY_A}.
     * @tc.expected: IsExactlyShiftWith(KEY_A) returns false because of extra key.
     */
    KeyEvent event;
    event.pressedCodes = { KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_A };

    EXPECT_FALSE(event.IsExactlyShiftWith(KeyCode::KEY_A));
}

/**
 * @tc.name: KeyEvent_IsNumberKey001
 * @tc.desc: Test IsNumberKey returns true for KEY_0 through KEY_9.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_IsNumberKey001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set code to KEY_5.
     * @tc.expected: IsNumberKey returns true.
     */
    KeyEvent event;
    event.code = KeyCode::KEY_5;
    EXPECT_TRUE(event.IsNumberKey());

    event.code = KeyCode::KEY_0;
    EXPECT_TRUE(event.IsNumberKey());

    event.code = KeyCode::KEY_9;
    EXPECT_TRUE(event.IsNumberKey());
}

/**
 * @tc.name: KeyEvent_IsNumberKey002
 * @tc.desc: Test IsNumberKey returns true for numpad keys.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_IsNumberKey002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set code to KEY_NUMPAD_5.
     * @tc.expected: IsNumberKey returns true.
     */
    KeyEvent event;
    event.code = KeyCode::KEY_NUMPAD_5;
    EXPECT_TRUE(event.IsNumberKey());

    event.code = KeyCode::KEY_NUMPAD_0;
    EXPECT_TRUE(event.IsNumberKey());
}

/**
 * @tc.name: KeyEvent_IsNumberKey003
 * @tc.desc: Test IsNumberKey returns false for non-number keys.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_IsNumberKey003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set code to KEY_A.
     * @tc.expected: IsNumberKey returns false.
     */
    KeyEvent event;
    event.code = KeyCode::KEY_A;
    EXPECT_FALSE(event.IsNumberKey());

    event.code = KeyCode::KEY_ESCAPE;
    EXPECT_FALSE(event.IsNumberKey());
}

/**
 * @tc.name: KeyEvent_IsDirectionalKey001
 * @tc.desc: Test IsDirectionalKey returns true for DPAD keys.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_IsDirectionalKey001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set code to KEY_DPAD_UP, KEY_DPAD_DOWN, KEY_DPAD_LEFT, KEY_DPAD_RIGHT.
     * @tc.expected: IsDirectionalKey returns true for all.
     */
    KeyEvent event;
    event.code = KeyCode::KEY_DPAD_UP;
    EXPECT_TRUE(event.IsDirectionalKey());

    event.code = KeyCode::KEY_DPAD_DOWN;
    EXPECT_TRUE(event.IsDirectionalKey());

    event.code = KeyCode::KEY_DPAD_LEFT;
    EXPECT_TRUE(event.IsDirectionalKey());

    event.code = KeyCode::KEY_DPAD_RIGHT;
    EXPECT_TRUE(event.IsDirectionalKey());
}

/**
 * @tc.name: KeyEvent_IsDirectionalKey002
 * @tc.desc: Test IsDirectionalKey returns false for non-directional keys.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_IsDirectionalKey002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set code to KEY_A.
     * @tc.expected: IsDirectionalKey returns false.
     */
    KeyEvent event;
    event.code = KeyCode::KEY_A;
    EXPECT_FALSE(event.IsDirectionalKey());
}

/**
 * @tc.name: KeyEvent_IsLetterKey001
 * @tc.desc: Test IsLetterKey returns true for KEY_A through KEY_Z.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_IsLetterKey001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set code to KEY_A, KEY_M, KEY_Z.
     * @tc.expected: IsLetterKey returns true for all.
     */
    KeyEvent event;
    event.code = KeyCode::KEY_A;
    EXPECT_TRUE(event.IsLetterKey());

    event.code = KeyCode::KEY_M;
    EXPECT_TRUE(event.IsLetterKey());

    event.code = KeyCode::KEY_Z;
    EXPECT_TRUE(event.IsLetterKey());
}

/**
 * @tc.name: KeyEvent_IsLetterKey002
 * @tc.desc: Test IsLetterKey returns false for non-letter keys.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_IsLetterKey002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set code to KEY_0, KEY_F1.
     * @tc.expected: IsLetterKey returns false.
     */
    KeyEvent event;
    event.code = KeyCode::KEY_0;
    EXPECT_FALSE(event.IsLetterKey());

    event.code = KeyCode::KEY_F1;
    EXPECT_FALSE(event.IsLetterKey());
}

/**
 * @tc.name: KeyEvent_IsCombinationKey001
 * @tc.desc: Test IsCombinationKey returns true when multiple keys are pressed.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_IsCombinationKey001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. pressedCodes contains 2 keys.
     * @tc.expected: IsCombinationKey returns true.
     */
    KeyEvent event;
    event.pressedCodes = { KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_A };
    EXPECT_TRUE(event.IsCombinationKey());
}

/**
 * @tc.name: KeyEvent_IsCombinationKey002
 * @tc.desc: Test IsCombinationKey returns false for single key.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_IsCombinationKey002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. pressedCodes contains only 1 key.
     * @tc.expected: IsCombinationKey returns false.
     */
    KeyEvent event;
    event.pressedCodes = { KeyCode::KEY_A };
    EXPECT_FALSE(event.IsCombinationKey());
}

/**
 * @tc.name: KeyEvent_IsFunctionKey001
 * @tc.desc: Test IsFunctionKey returns true for F1-F12, DPAD, and TAB keys.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_IsFunctionKey001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test F1, F12, DPAD_UP, DPAD_RIGHT, TAB.
     * @tc.expected: IsFunctionKey returns true for all.
     */
    KeyEvent event;
    event.code = KeyCode::KEY_F1;
    EXPECT_TRUE(event.IsFunctionKey());

    event.code = KeyCode::KEY_F12;
    EXPECT_TRUE(event.IsFunctionKey());

    event.code = KeyCode::KEY_DPAD_UP;
    EXPECT_TRUE(event.IsFunctionKey());

    event.code = KeyCode::KEY_DPAD_RIGHT;
    EXPECT_TRUE(event.IsFunctionKey());

    event.code = KeyCode::KEY_TAB;
    EXPECT_TRUE(event.IsFunctionKey());
}

/**
 * @tc.name: KeyEvent_IsFunctionKey002
 * @tc.desc: Test IsFunctionKey returns false for non-function keys.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_IsFunctionKey002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set code to KEY_A, KEY_0.
     * @tc.expected: IsFunctionKey returns false.
     */
    KeyEvent event;
    event.code = KeyCode::KEY_A;
    EXPECT_FALSE(event.IsFunctionKey());

    event.code = KeyCode::KEY_0;
    EXPECT_FALSE(event.IsFunctionKey());
}

/**
 * @tc.name: KeyEvent_IsEscapeKey001
 * @tc.desc: Test IsEscapeKey returns true for KEY_ESCAPE.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_IsEscapeKey001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set code to KEY_ESCAPE.
     * @tc.expected: IsEscapeKey returns true.
     */
    KeyEvent event;
    event.code = KeyCode::KEY_ESCAPE;
    EXPECT_TRUE(event.IsEscapeKey());
}

/**
 * @tc.name: KeyEvent_IsEscapeKey002
 * @tc.desc: Test IsEscapeKey returns false for non-escape keys.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_IsEscapeKey002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set code to KEY_A.
     * @tc.expected: IsEscapeKey returns false.
     */
    KeyEvent event;
    event.code = KeyCode::KEY_A;
    EXPECT_FALSE(event.IsEscapeKey());
}

/**
 * @tc.name: KeyEvent_SetTimeStamp001
 * @tc.desc: Test SetTimeStamp correctly converts milliseconds to TimeStamp.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_SetTimeStamp001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call SetTimeStamp with 1000ms.
     * @tc.expected: timeStamp is set correctly.
     */
    KeyEvent event;
    event.SetTimeStamp(1000);
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(event.timeStamp.time_since_epoch());
    EXPECT_EQ(duration.count(), 1000);
}

/**
 * @tc.name: KeyEvent_IsPreIme001
 * @tc.desc: Test IsPreIme getter returns correct value.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_IsPreIme001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default isPreIme is false, set to true.
     * @tc.expected: IsPreIme returns false then true.
     */
    KeyEvent event;
    EXPECT_FALSE(event.IsPreIme());

    event.isPreIme = true;
    EXPECT_TRUE(event.IsPreIme());
}

/**
 * @tc.name: KeyEvent_ConvertCodeToString001
 * @tc.desc: Test ConvertCodeToString for digit keys without Shift.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_ConvertCodeToString001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set code to KEY_5, no shift pressed.
     * @tc.expected: ConvertCodeToString returns "5".
     */
    KeyEvent event;
    event.code = KeyCode::KEY_5;
    EXPECT_EQ(event.ConvertCodeToString(), "5");
}

/**
 * @tc.name: KeyEvent_ConvertCodeToString002
 * @tc.desc: Test ConvertCodeToString for digit keys with Shift (produces symbols).
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_ConvertCodeToString002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set code to KEY_1 with Shift pressed.
     * @tc.expected: ConvertCodeToString returns "!".
     */
    KeyEvent event;
    event.code = KeyCode::KEY_1;
    event.pressedCodes = { KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_1 };
    EXPECT_EQ(event.ConvertCodeToString(), "!");
}

/**
 * @tc.name: KeyEvent_ConvertCodeToString003
 * @tc.desc: Test ConvertCodeToString for numpad keys with numLock enabled.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_ConvertCodeToString003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set code to KEY_NUMPAD_7, numLock = true.
     * @tc.expected: ConvertCodeToString returns "7".
     */
    KeyEvent event;
    event.code = KeyCode::KEY_NUMPAD_7;
    event.numLock = true;
    EXPECT_EQ(event.ConvertCodeToString(), "7");
}

/**
 * @tc.name: KeyEvent_ConvertCodeToString004
 * @tc.desc: Test ConvertCodeToString for numpad dot with numLock enabled.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_ConvertCodeToString004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set code to KEY_NUMPAD_DOT, numLock = true.
     * @tc.expected: ConvertCodeToString returns ".".
     */
    KeyEvent event;
    event.code = KeyCode::KEY_NUMPAD_DOT;
    event.numLock = true;
    EXPECT_EQ(event.ConvertCodeToString(), ".");
}

/**
 * @tc.name: KeyEvent_ConvertCodeToString005
 * @tc.desc: Test ConvertCodeToString for lowercase letter key.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_ConvertCodeToString005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set code to KEY_A, no Shift, no CapsLock.
     * @tc.expected: ConvertCodeToString returns "a".
     */
    KeyEvent event;
    event.code = KeyCode::KEY_A;
    EXPECT_EQ(event.ConvertCodeToString(), "a");
}

/**
 * @tc.name: KeyEvent_ConvertCodeToString006
 * @tc.desc: Test ConvertCodeToString for uppercase letter with Shift.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_ConvertCodeToString006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set code to KEY_A with Shift pressed.
     * @tc.expected: ConvertCodeToString returns "A".
     */
    KeyEvent event;
    event.code = KeyCode::KEY_A;
    event.pressedCodes = { KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_A };
    EXPECT_EQ(event.ConvertCodeToString(), "A");
}

/**
 * @tc.name: KeyEvent_ConvertCodeToString007
 * @tc.desc: Test ConvertCodeToString for uppercase letter with CapsLock.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_ConvertCodeToString007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set code to KEY_A with CapsLock enabled, no Shift.
     * @tc.expected: ConvertCodeToString returns "A".
     */
    KeyEvent event;
    event.code = KeyCode::KEY_A;
    event.enableCapsLock = true;
    EXPECT_EQ(event.ConvertCodeToString(), "A");
}

/**
 * @tc.name: KeyEvent_ConvertCodeToString008
 * @tc.desc: Test ConvertCodeToString returns lowercase when both Shift and CapsLock active.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_ConvertCodeToString008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set code to KEY_A with both Shift and CapsLock.
     * @tc.expected: ConvertCodeToString returns "a" (Shift+CapsLock cancels out).
     */
    KeyEvent event;
    event.code = KeyCode::KEY_A;
    event.pressedCodes = { KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_A };
    event.enableCapsLock = true;
    EXPECT_EQ(event.ConvertCodeToString(), "a");
}

/**
 * @tc.name: KeyEvent_ConvertCodeToString009
 * @tc.desc: Test ConvertCodeToString for symbol key with Shift.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_ConvertCodeToString009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set code to KEY_MINUS with Shift pressed.
     * @tc.expected: ConvertCodeToString returns "_".
     */
    KeyEvent event;
    event.code = KeyCode::KEY_MINUS;
    event.pressedCodes = { KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_MINUS };
    EXPECT_EQ(event.ConvertCodeToString(), "_");
}

/**
 * @tc.name: KeyEvent_ConvertCodeToString010
 * @tc.desc: Test ConvertCodeToString for symbol key without Shift.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_ConvertCodeToString010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set code to KEY_MINUS without Shift.
     * @tc.expected: ConvertCodeToString returns "-".
     */
    KeyEvent event;
    event.code = KeyCode::KEY_MINUS;
    EXPECT_EQ(event.ConvertCodeToString(), "-");
}

/**
 * @tc.name: KeyEvent_ConvertCodeToString011
 * @tc.desc: Test ConvertCodeToString returns empty for unknown key.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_ConvertCodeToString011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set code to KEY_UNKNOWN.
     * @tc.expected: ConvertCodeToString returns empty string.
     */
    KeyEvent event;
    event.code = KeyCode::KEY_UNKNOWN;
    EXPECT_EQ(event.ConvertCodeToString(), "");
}

/**
 * @tc.name: KeyEvent_ConvertInputCodeToString001
 * @tc.desc: Test ConvertInputCodeToString for numpad digits.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_ConvertInputCodeToString001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set code to KEY_NUMPAD_3.
     * @tc.expected: ConvertInputCodeToString returns "3".
     */
    KeyEvent event;
    event.code = KeyCode::KEY_NUMPAD_3;
    EXPECT_EQ(event.ConvertInputCodeToString(), "3");
}

/**
 * @tc.name: KeyEvent_ConvertInputCodeToString002
 * @tc.desc: Test ConvertInputCodeToString for letter keys.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_ConvertInputCodeToString002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set code to KEY_C.
     * @tc.expected: ConvertInputCodeToString returns "C".
     */
    KeyEvent event;
    event.code = KeyCode::KEY_C;
    EXPECT_EQ(event.ConvertInputCodeToString(), "C");
}

/**
 * @tc.name: KeyEvent_ConvertInputCodeToString003
 * @tc.desc: Test ConvertInputCodeToString for special keys like TAB, ESC.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_ConvertInputCodeToString003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set code to KEY_TAB, KEY_ESCAPE.
     * @tc.expected: ConvertInputCodeToString returns "TAB" and "ESC".
     */
    KeyEvent event;
    event.code = KeyCode::KEY_TAB;
    EXPECT_EQ(event.ConvertInputCodeToString(), "TAB");

    event.code = KeyCode::KEY_ESCAPE;
    EXPECT_EQ(event.ConvertInputCodeToString(), "ESC");
}

/**
 * @tc.name: KeyEvent_ConvertInputCodeToString004
 * @tc.desc: Test ConvertInputCodeToString for function keys.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_ConvertInputCodeToString004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set code to KEY_F1.
     * @tc.expected: ConvertInputCodeToString returns "F1".
     */
    KeyEvent event;
    event.code = KeyCode::KEY_F1;
    EXPECT_EQ(event.ConvertInputCodeToString(), "F1");
}

/**
 * @tc.name: KeyEvent_ConvertInputCodeToString005
 * @tc.desc: Test ConvertInputCodeToString for visibility code entries like KEY_0.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_ConvertInputCodeToString005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set code to KEY_0.
     * @tc.expected: ConvertInputCodeToString returns "0)".
     */
    KeyEvent event;
    event.code = KeyCode::KEY_0;
    EXPECT_EQ(event.ConvertInputCodeToString(), "0)");
}

/**
 * @tc.name: KeyEvent_ConvertInputCodeToString006
 * @tc.desc: Test ConvertInputCodeToString returns empty for unknown key.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_ConvertInputCodeToString006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set code to KEY_UNKNOWN.
     * @tc.expected: ConvertInputCodeToString returns empty string.
     */
    KeyEvent event;
    event.code = KeyCode::KEY_UNKNOWN;
    EXPECT_EQ(event.ConvertInputCodeToString(), "");
}

/**
 * @tc.name: KeyEvent_ToString001
 * @tc.desc: Test ToString output contains expected fields.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_ToString001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set code and action, call ToString.
     * @tc.expected: Result contains "code=" and "action=" substrings.
     */
    KeyEvent event;
    event.code = KeyCode::KEY_A;
    event.action = KeyAction::DOWN;
    event.pressedCodes = { KeyCode::KEY_A };
    auto str = event.ToString();
    EXPECT_NE(str.find("code="), std::string::npos);
    EXPECT_NE(str.find("action="), std::string::npos);
}

/**
 * @tc.name: KeyToString001
 * @tc.desc: Test KeyToString returns correct string for valid keycode.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyToString001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call KeyToString with KEY_A code (2017).
     * @tc.expected: Returns "KeyA".
     */
    EXPECT_STREQ(KeyToString(static_cast<int32_t>(KeyCode::KEY_A)), "KeyA");
}

/**
 * @tc.name: KeyToString002
 * @tc.desc: Test KeyToString returns "Unknown" for negative code.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyToString002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call KeyToString with -1.
     * @tc.expected: Returns "Unknown".
     */
    EXPECT_STREQ(KeyToString(-1), "Unknown");
}

/**
 * @tc.name: KeyToString003
 * @tc.desc: Test KeyToString returns "Unknown" for out-of-range code.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyToString003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call KeyToString with 999 (exceeds KEYCODE_SIZE).
     * @tc.expected: Returns "Unknown".
     */
    EXPECT_STREQ(KeyToString(999), "Unknown");
}

/**
 * @tc.name: CalculateModifierKeyState001
 * @tc.desc: Test CalculateModifierKeyState with Ctrl and Alt.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, CalculateModifierKeyState001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Pass {KEY_CTRL_LEFT, KEY_ALT_LEFT} to CalculateModifierKeyState.
     * @tc.expected: Result contains both Ctrl and Alt bits.
     */
    std::vector<KeyCode> keys = { KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_ALT_LEFT };
    auto state = CalculateModifierKeyState(keys);
    EXPECT_TRUE(state & static_cast<uint64_t>(ModifierKeyName::ModifierKeyCtrl));
    EXPECT_TRUE(state & static_cast<uint64_t>(ModifierKeyName::ModifierKeyAlt));
    EXPECT_FALSE(state & static_cast<uint64_t>(ModifierKeyName::ModifierKeyShift));
}

/**
 * @tc.name: CalculateModifierKeyState002
 * @tc.desc: Test CalculateModifierKeyState with Shift and Fn.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, CalculateModifierKeyState002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Pass {KEY_SHIFT_RIGHT, KEY_FN} to CalculateModifierKeyState.
     * @tc.expected: Result contains Shift and Fn bits but not Ctrl or Alt.
     */
    std::vector<KeyCode> keys = { KeyCode::KEY_SHIFT_RIGHT, KeyCode::KEY_FN };
    auto state = CalculateModifierKeyState(keys);
    EXPECT_TRUE(state & static_cast<uint64_t>(ModifierKeyName::ModifierKeyShift));
    EXPECT_TRUE(state & static_cast<uint64_t>(ModifierKeyName::ModifierKeyFn));
    EXPECT_FALSE(state & static_cast<uint64_t>(ModifierKeyName::ModifierKeyCtrl));
}

/**
 * @tc.name: CalculateModifierKeyState003
 * @tc.desc: Test CalculateModifierKeyState with empty vector.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, CalculateModifierKeyState003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Pass empty vector.
     * @tc.expected: Result is 0.
     */
    std::vector<KeyCode> keys;
    auto state = CalculateModifierKeyState(keys);
    EXPECT_EQ(state, 0u);
}

/**
 * @tc.name: KeyEvent_Constructor001
 * @tc.desc: Test default constructor sets eventType to KEY.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_Constructor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default construct KeyEvent.
     * @tc.expected: eventType is UIInputEventType::KEY.
     */
    KeyEvent event;
    EXPECT_EQ(event.eventType, UIInputEventType::KEY);
    EXPECT_EQ(event.code, KeyCode::KEY_UNKNOWN);
    EXPECT_EQ(event.action, KeyAction::UNKNOWN);
}

/**
 * @tc.name: KeyEvent_Constructor002
 * @tc.desc: Test parameterized constructor with code and action.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventTestNg, KeyEvent_Constructor002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct KeyEvent(KeyCode::KEY_ENTER, KeyAction::DOWN).
     * @tc.expected: code and action are set correctly, eventType is KEY.
     */
    KeyEvent event(KeyCode::KEY_ENTER, KeyAction::DOWN);
    EXPECT_EQ(event.code, KeyCode::KEY_ENTER);
    EXPECT_EQ(event.action, KeyAction::DOWN);
    EXPECT_EQ(event.eventType, UIInputEventType::KEY);
}

} // namespace OHOS::Ace
