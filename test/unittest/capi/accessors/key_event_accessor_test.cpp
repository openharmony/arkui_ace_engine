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
#include "accessor_test_base.h"
#include "core/interfaces/native/implementation/key_event_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "test/unittest/capi/accessors/accessor_test_fixtures.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace AccessorTestFixtures;

class KeyEventAccessorTest
    : public AccessorTestBase<GENERATED_ArkUIKeyEventAccessor,
        &GENERATED_ArkUIAccessors::getKeyEventAccessor, KeyEventPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        const double testDensity = 2.0;
        MockPipelineContext::GetCurrent()->SetDensity(testDensity);
        KeyEvent keyEvent;
        eventInfo_ = std::make_unique<KeyEventInfo>(keyEvent);
        peer_->SetEventInfo(eventInfo_.get());
    }

    std::unique_ptr<KeyEventInfo> eventInfo_;
    Ark_VMContext vmContext_ = nullptr;
};

/**
 * @tc.name: getModifierKeyStateValidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, getModifierKeyStateValidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getModifierKeyState, nullptr);

    const std::vector<std::tuple<std::vector<std::string>, std::vector<KeyCode>, bool>> TEST_PLAN {
        { {"shift", "ctrl", "alt"}, {KeyCode::KEY_CTRL_LEFT}, false },
        { {"shift"}, {KeyCode::KEY_CTRL_LEFT}, false },
        { {"shift", "alt"}, {KeyCode::KEY_ALT_LEFT, KeyCode::KEY_SHIFT_RIGHT}, true },
        { {"ctrl", "shift"}, {KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_SHIFT_RIGHT}, true },
        { {"fn"}, {KeyCode::KEY_CTRL_LEFT}, false },
        { {"ctrl"}, {KeyCode::KEY_CTRL_LEFT}, true },
        { {"ctrl"}, {KeyCode::KEY_CTRL_RIGHT}, true },
    };
    for (auto& [param, value, expected] : TEST_PLAN) {
        Converter::ArkArrayHolder<Array_String> stringHolder(param);
        const auto stringArrayValues = stringHolder.ArkValue();
        eventInfo_->SetPressedKeyCodes(value);
        const auto result = accessor_->getModifierKeyState(vmContext_, peer_, &stringArrayValues);
        EXPECT_EQ(Converter::Convert<bool>(result), expected);
    }
}

/**
 * @tc.name: getModifierKeyStateInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, getModifierKeyStateInvalidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getModifierKeyState, nullptr);

    const std::vector<std::string> emptyStr {""};
    Converter::ArkArrayHolder<Array_String> stringHolder(emptyStr);
    const auto stringArrayValues = stringHolder.ArkValue();
    const std::vector<std::tuple<KeyEventPeer*, const Array_String*>> TEST_PLAN {
        { nullptr, nullptr },
        { nullptr, &stringArrayValues },
        { peer_, nullptr },
        { peer_, &stringArrayValues },
    };
    for (auto& [peer, str] : TEST_PLAN) {
        auto result = accessor_->getModifierKeyState(vmContext_, peer, str);
        EXPECT_FALSE(Converter::Convert<bool>(result));
    }
}

/**
 * @tc.name: getTypeValidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, DISABLED_getTypeValidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getType, nullptr);
}

/**
 * @tc.name: getTypeInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, DISABLED_getTypeInvalidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getType, nullptr);
}

/**
 * @tc.name: setTypeValidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, setTypeValidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setType, nullptr);

    const std::vector<Ark_KeyType> TEST_PLAN { ARK_KEY_TYPE_DOWN, ARK_KEY_TYPE_UP };
    const auto type = eventInfo_->GetKeyType();
    for (auto& keyType : TEST_PLAN) {
        accessor_->setType(peer_, keyType);
        EXPECT_EQ(eventInfo_->GetKeyType(), type);
    }
}

/**
 * @tc.name: setTypeInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, setTypeInvalidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setType, nullptr);
    const auto type = eventInfo_->GetKeyType();
    accessor_->setType(nullptr, ARK_KEY_TYPE_UP);
    EXPECT_EQ(eventInfo_->GetKeyType(), type);
}

/**
 * @tc.name: getKeyCodeValidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, getKeyCodeValidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getKeyCode, nullptr);
    const std::vector<KeyCode> TEST_PLAN {
        KeyCode::KEY_FN, KeyCode::KEY_0, KeyCode::KEY_A, KeyCode::KEY_LAUNCHER_MENU
    };
    for (auto code : TEST_PLAN) {
        KeyEvent keyEvent;
        keyEvent.code = code;
        *eventInfo_ = KeyEventInfo(keyEvent);
        auto result = accessor_->getKeyCode(peer_);
        EXPECT_EQ(Converter::Convert<int32_t>(result), static_cast<int32_t>(code));
    }
}

/**
 * @tc.name: getKeyCodeInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, getKeyCodeInvalidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getKeyCode, nullptr);
    EXPECT_EQ(Converter::Convert<int32_t>(accessor_->getKeyCode(nullptr)), 0);
}

/**
 * @tc.name: setKeyCodeValidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, setKeyCodeValidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setKeyCode, nullptr);
    // setKeyCode doesn't have sense.
}

/**
 * @tc.name: setKeyCodeInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, setKeyCodeInvalidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setKeyCode, nullptr);
    const auto someCode = Converter::ArkValue<Ark_Number>(-1);
    const std::vector<std::tuple<KeyEventPeer*, const Ark_Number*>> TEST_PLAN {
        { nullptr, nullptr },
        { nullptr, &someCode },
        { peer_, nullptr },
    };
    const auto currentCode = eventInfo_->GetKeyCode();
    for (auto& [peer, code] : TEST_PLAN) {
        accessor_->setKeyCode(peer, code);
        EXPECT_EQ(eventInfo_->GetKeyCode(), currentCode);
    }
}

/**
 * @tc.name: getKeyTextValidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, DISABLED_getKeyTextValidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getKeyText, nullptr);
}

/**
 * @tc.name: getKeyTextInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, DISABLED_getKeyTextInvalidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getKeyText, nullptr);
}

/**
 * @tc.name: setKeyTextValidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, setKeyTextValidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setKeyText, nullptr);
    // setKeyText doesn't have sense.
}

/**
 * @tc.name: setKeyTextInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, setKeyTextInvalidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setKeyText, nullptr);
    const auto someText = Converter::ArkValue<Ark_String>("");
    const std::vector<std::tuple<KeyEventPeer*, const Ark_String*>> TEST_PLAN {
        { nullptr, nullptr },
        { nullptr, &someText },
        { peer_, nullptr },
    };
    const auto currentText = eventInfo_->GetKeyText();
    for (auto& [peer, text] : TEST_PLAN) {
        accessor_->setKeyText(peer, text);
        EXPECT_EQ(eventInfo_->GetKeyText(), currentText);
    }
}

/**
 * @tc.name: getKeySourceValidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, DISABLED_getKeySourceValidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getKeySource, nullptr);
}

/**
 * @tc.name: getKeySourceInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, DISABLED_getKeySourceInvalidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getKeySource, nullptr);
}

/**
 * @tc.name: setKeySourceValidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, setKeySourceValidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setKeySource, nullptr);
    // setKeySource doesn't have sense.
}

/**
 * @tc.name: setKeySourceInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, setKeySourceInvalidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setKeySource, nullptr);
    const auto currentSource = eventInfo_->GetKeySource();
    accessor_->setKeySource(nullptr, ARK_KEY_SOURCE_KEYBOARD);
    EXPECT_EQ(eventInfo_->GetKeySource(), currentSource);
}

/**
 * @tc.name: getDeviceIdValidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, getDeviceIdValidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getDeviceId, nullptr);
    for (auto& [input, expected, value] : testFixtureInt32WithNegativeValues) {
        eventInfo_->SetDeviceId(value);
        auto deviceId = Converter::Convert<int32_t>(accessor_->getDeviceId(peer_));
        EXPECT_EQ(deviceId, expected) <<
            "Input value is: " << input;
    }
}

/**
 * @tc.name: getDeviceIdInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, getDeviceIdInvalidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getDeviceId, nullptr);
    EXPECT_EQ(Converter::Convert<int32_t>(accessor_->getDeviceId(nullptr)), 0);
}

/**
 * @tc.name: setDeviceIdValidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, setDeviceIdValidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setDeviceId, nullptr);
    for (auto& [input, value, expected] : testFixtureNumberInt32Values) {
        accessor_->setDeviceId(peer_, &value);
        auto deviceId = eventInfo_->GetDeviceId();
        EXPECT_EQ(deviceId, expected) <<
            "Input value is: " << input;
    }
}

/**
 * @tc.name: setDeviceIdInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, setDeviceIdInvalidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setDeviceId, nullptr);
    const auto someId = Converter::ArkValue<Ark_Number>(-1);
    const std::vector<std::tuple<KeyEventPeer*, const Ark_Number*>> TEST_PLAN {
        { nullptr, nullptr },
        { nullptr, &someId },
        { peer_, nullptr },
    };
    const auto currentId = eventInfo_->GetDeviceId();
    for (auto& [peer, id] : TEST_PLAN) {
        accessor_->setDeviceId(peer, id);
        EXPECT_EQ(eventInfo_->GetDeviceId(), currentId);
    }
}

/**
 * @tc.name: getMetaKeyValidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, getMetaKeyValidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getMetaKey, nullptr);
    for (auto& [input, expected, value] : testFixtureInt32WithNegativeValues) {
        eventInfo_->SetMetaKey(value);
        auto key = Converter::Convert<int32_t>(accessor_->getMetaKey(peer_));
        EXPECT_EQ(key, expected) <<
            "Input value is: " << input;
    }
}

/**
 * @tc.name: getMetaKeyInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, getMetaKeyInvalidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getMetaKey, nullptr);
    EXPECT_EQ(Converter::Convert<int32_t>(accessor_->getMetaKey(nullptr)), 0);
}

/**
 * @tc.name: setMetaKeyValidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, setMetaKeyValidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setMetaKey, nullptr);
    for (auto& [input, value, expected] : testFixtureNumberInt32Values) {
        accessor_->setMetaKey(peer_, &value);
        auto key = eventInfo_->GetMetaKey();
        EXPECT_EQ(key, expected) <<
            "Input value is: " << input;
    }
}

/**
 * @tc.name: setMetaKeyInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, setMetaKeyInvalidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setMetaKey, nullptr);
    const auto someKey = Converter::ArkValue<Ark_Number>(-1);
    const std::vector<std::tuple<KeyEventPeer*, const Ark_Number*>> TEST_PLAN {
        { nullptr, nullptr },
        { nullptr, &someKey },
        { peer_, nullptr },
    };
    const auto currentKey = eventInfo_->GetMetaKey();
    for (auto& [peer, key] : TEST_PLAN) {
        accessor_->setMetaKey(peer, key);
        EXPECT_EQ(eventInfo_->GetMetaKey(), currentKey);
    }
}

/**
 * @tc.name: getTimestampValidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, getTimestampValidTest, TestSize.Level1)
{
    using TimeStamp = std::chrono::high_resolution_clock::time_point;
    using Duration = std::chrono::high_resolution_clock::duration;

    ASSERT_NE(accessor_->getTimestamp, nullptr);
    const std::vector<std::pair<int, Duration>> TEST_PLAN {
        { 1, Duration(std::chrono::nanoseconds(1)) },
        { 9999, Duration(std::chrono::nanoseconds(9999)) }
    };

    for (auto& [expected, value] : TEST_PLAN) {
        eventInfo_->SetTimeStamp(TimeStamp() + value);
        auto timeStamp = accessor_->getTimestamp(peer_);
        EXPECT_EQ(Converter::Convert<int32_t>(timeStamp), expected);
    }
}

/**
 * @tc.name: getTimestampInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, getTimestampInvalidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getTimestamp, nullptr);
    EXPECT_EQ(Converter::Convert<int32_t>(accessor_->getTimestamp(nullptr)), 0);
}

/**
 * @tc.name: setTimestampValidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, setTimestampValidTest, TestSize.Level1)
{
    using TimeStamp = std::chrono::high_resolution_clock::time_point;
    using Duration = std::chrono::high_resolution_clock::duration;

    ASSERT_NE(accessor_->setTimestamp, nullptr);
    const std::vector<std::pair<Ark_Number, Duration>> TEST_PLAN {
        { Converter::ArkValue<Ark_Number>(9), Duration(std::chrono::nanoseconds(9)) },
        { Converter::ArkValue<Ark_Number>(111111), Duration(std::chrono::nanoseconds(111111)) }
    };

    for (auto& [value, duration] : TEST_PLAN) {
        accessor_->setTimestamp(peer_, &value);
        auto timeStamp = eventInfo_->GetTimeStamp();
        TimeStamp expected = TimeStamp() + duration;
        EXPECT_EQ(timeStamp, expected);
    }
}

/**
 * @tc.name: setTimestampInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, setTimestampInvalidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setTimestamp, nullptr);
    const auto someTime = Converter::ArkValue<Ark_Number>(-1);
    const std::vector<std::tuple<KeyEventPeer*, const Ark_Number*>> TEST_PLAN {
        { nullptr, nullptr },
        { nullptr, &someTime },
        { peer_, nullptr },
    };
    const auto currentTime = eventInfo_->GetTimeStamp();
    for (auto& [peer, time] : TEST_PLAN) {
        accessor_->setTimestamp(peer, time);
        EXPECT_EQ(eventInfo_->GetTimeStamp(), currentTime);
    }
}

/**
 * @tc.name: setStopPropagationValidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, setStopPropagationValidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setStopPropagation, nullptr);
    // setStopPropagation doesn't have sense.
}

/**
 * @tc.name: setStopPropagationInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, setStopPropagationInvalidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setStopPropagation, nullptr);
    auto event = [](const Ark_Int32 resourceId) {
        FAIL();
    };
    auto someCallback = Converter::ArkValue<Callback_Void>(event, 0);
    const std::vector<std::tuple<KeyEventPeer*, const Callback_Void*>> TEST_PLAN {
        { nullptr, nullptr },
        { nullptr, &someCallback },
        { peer_, nullptr },
    };
    for (auto& [peer, callback] : TEST_PLAN) {
        accessor_->setStopPropagation(peer, callback);
        EXPECT_FALSE(eventInfo_->IsStopPropagation());
    }
}

/**
 * @tc.name: setIntentionCodeValidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, setIntentionCodeValidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setIntentionCode, nullptr);
    // setIntentionCode doesn't have sense.
}

/**
 * @tc.name: setIntentionCodeInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, setIntentionCodeInvalidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setIntentionCode, nullptr);
    const Ark_IntentionCode someCode {};
    const std::vector<std::tuple<KeyEventPeer*, const Ark_IntentionCode*>> TEST_PLAN {
        { nullptr, nullptr },
        { nullptr, &someCode },
        { peer_, nullptr },
    };
    const auto currentCode = eventInfo_->GetKeyIntention();
    for (auto& [peer, code] : TEST_PLAN) {
        accessor_->setIntentionCode(peer, code);
        EXPECT_EQ(eventInfo_->GetKeyIntention(), currentCode);
    }
}

/**
 * @tc.name: getUnicodeValidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, getUnicodeValidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getUnicode, nullptr);
    for (auto& [input, expected, value] : testFixtureInt32WithNegativeValues) {
        KeyEvent keyEvent;
        keyEvent.unicode = static_cast<decltype(keyEvent.unicode)>(value);
        *eventInfo_ = KeyEventInfo(keyEvent);
        auto unicode = Converter::Convert<int32_t>(accessor_->getUnicode(peer_));
        EXPECT_EQ(unicode, expected) <<
            "Input value is: " << input;
    }
}

/**
 * @tc.name: getUnicodeInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, getUnicodeInvalidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getUnicode, nullptr);
    EXPECT_EQ(Converter::Convert<int32_t>(accessor_->getUnicode(nullptr)), Converter::ArkValue<Ark_Int32>(0));
}

/**
 * @tc.name: setUnicodeValidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, setUnicodeValidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setUnicode, nullptr);
    // setUnicode doesn't have sense.
}

/**
 * @tc.name: setUnicodeInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventAccessorTest, setUnicodeInvalidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setUnicode, nullptr);
    const auto someUnicode = Converter::ArkValue<Ark_Number>(-1);
    const std::vector<std::tuple<KeyEventPeer*, const Ark_Number*>> TEST_PLAN {
        { nullptr, nullptr },
        { nullptr, &someUnicode },
        { peer_, nullptr },
    };
    const auto currentCode = eventInfo_->GetUnicode();
    for (auto& [peer, unicode] : TEST_PLAN) {
        accessor_->setUnicode(peer, unicode);
        EXPECT_EQ(eventInfo_->GetUnicode(), currentCode);
    }
}
} // namespace OHOS::Ace::NG
