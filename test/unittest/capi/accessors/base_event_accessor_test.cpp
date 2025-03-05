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

#include <vector>
#include <tuple>

#include "accessor_test_base.h"
#include "node_api.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/event/ace_events.h"
#include "core/interfaces/native/implementation/base_event_peer.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class BaseEventAccessorTest
    : public AccessorTestBase<GENERATED_ArkUIBaseEventAccessor,
        &GENERATED_ArkUIAccessors::getBaseEventAccessor, GeneratedModifier::BaseEventPeerImpl> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        baseEvent_ = std::make_unique<BaseEventInfo>("test");
        peer_->SetEventInfo(baseEvent_.get());
    }
    std::unique_ptr<BaseEventInfo> baseEvent_;
    Ark_VMContext vmContext_ = nullptr;
};

const std::vector<std::pair<Ark_Number, int>> testFixtureInt32Values = {
    { Converter::ArkValue<Ark_Number>(123), 123 },
    { Converter::ArkValue<Ark_Number>(0), 0 },
    { Converter::ArkValue<Ark_Number>(30), 30 },
    { Converter::ArkValue<Ark_Number>(55), 55 },
    { Converter::ArkValue<Ark_Number>(65000), 65000 },
    { Converter::ArkValue<Ark_Number>(10), 10 },
};

/**
 * @tc.name: GetModifierKeyStateTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BaseEventAccessorTest, GetModifierKeyStateTest, TestSize.Level1)
{
    const std::vector<std::tuple<std::vector<std::string>, std::vector<KeyCode>, bool>> TEST_PLAN = {
        { {"ctrl"}, {KeyCode::KEY_CTRL_LEFT}, true },
        { {"ctrl"}, {KeyCode::KEY_CTRL_RIGHT}, true },
        { {"shift"}, {KeyCode::KEY_CTRL_LEFT}, false },
        { {"ctrl", "shift"}, {KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_SHIFT_RIGHT}, true },
        { {"shift", "alt"}, {KeyCode::KEY_ALT_LEFT, KeyCode::KEY_SHIFT_RIGHT}, true },
        { {"shift", "ctrl", "alt"}, {KeyCode::KEY_CTRL_LEFT}, false },
        { {"fn"}, {KeyCode::KEY_CTRL_LEFT}, false }
    };
    
    for (auto& [param, value, expected] : TEST_PLAN) {
        Converter::ArkArrayHolder<Array_String> stringHolder(param);
        Array_String stringArrayValues = stringHolder.ArkValue();
        baseEvent_->SetPressedKeyCodes(value);
        auto result = accessor_->getModifierKeyState(vmContext_, peer_, &stringArrayValues);
        EXPECT_EQ(Converter::Convert<bool>(result), expected);
    }
}

/**
 * @tc.name: SetTargetTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BaseEventAccessorTest, SetTargetTest, TestSize.Level1)
{
    constexpr double height = 100;
    constexpr double width = 200;
    constexpr double offsetX = 150;
    constexpr double offsetY = 250;
    constexpr double originX = 100;
    constexpr double originY = 450;

    Ark_Area area{Converter::ArkValue<Ark_Length>(width),
                  Converter::ArkValue<Ark_Length>(height),
                  Ark_Position {Converter::ArkValue<Opt_Length>(offsetX),
                                Converter::ArkValue<Opt_Length>(offsetY)},
                  Ark_Position {Converter::ArkValue<Opt_Length>(originX),
                                Converter::ArkValue<Opt_Length>(originY)}};

    Ark_EventTarget value {area};
    accessor_->setTarget(peer_, &value);
    EventTarget result = baseEvent_->GetTarget();
    EXPECT_EQ(result.area.GetHeight().Value(), height);
    EXPECT_EQ(result.area.GetWidth().Value(), width);
    EXPECT_EQ(result.area.GetOffset().GetX().Value(), offsetX);
    EXPECT_EQ(result.area.GetOffset().GetY().Value(), offsetY);
    EXPECT_EQ(result.origin.GetX().Value(), originX);
    EXPECT_EQ(result.origin.GetY().Value(), originY);
}

/**
 * @tc.name: GetTimeStampTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BaseEventAccessorTest, GetTimeStampTest, TestSize.Level1)
{
    using TimeStamp = std::chrono::high_resolution_clock::time_point;
    using Duration = std::chrono::high_resolution_clock::duration;

    const std::vector<std::pair<int, Duration>> TEST_PLAN = {
        { 123, Duration(std::chrono::nanoseconds(123)) },
        { 10000, Duration(std::chrono::nanoseconds(10000)) }
    };

    for (auto& [expected, value] : TEST_PLAN) {
        baseEvent_->SetTimeStamp(TimeStamp() + value);
        auto timeStamp = accessor_->getTimestamp(peer_);
        EXPECT_EQ(Converter::Convert<int32_t>(timeStamp), expected);
    }
}

/**
 * @tc.name: SetTimeStampTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BaseEventAccessorTest, SetTimeStampTest, TestSize.Level1)
{
    using TimeStamp = std::chrono::high_resolution_clock::time_point;
    using Duration = std::chrono::high_resolution_clock::duration;
    const std::vector<std::pair<Ark_Number, Duration>> TEST_PLAN = {
        { Converter::ArkValue<Ark_Number>(123), Duration(std::chrono::nanoseconds(123)) },
        { Converter::ArkValue<Ark_Number>(10000), Duration(std::chrono::nanoseconds(10000)) }
    };

    for (auto& [value, duration] : TEST_PLAN) {
        accessor_->setTimestamp(peer_, &value);
        auto timeStamp = baseEvent_->GetTimeStamp();
        TimeStamp expected = TimeStamp() + duration;
        EXPECT_EQ(timeStamp, expected);
    }
}

/**
 * @tc.name: GetSourceTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BaseEventAccessorTest, DISABLED_GetSourceTest, TestSize.Level1)
{
}

/**
 * @tc.name: SetSourceTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BaseEventAccessorTest, SetSourceTest, TestSize.Level1)
{
    const std::vector<SourceType> TEST_PLAN = {
        SourceType::MOUSE,
        SourceType::TOUCH
    };

    for (auto expected : TEST_PLAN) {
        Ark_SourceType value = Converter::ArkValue<Ark_SourceType>(expected);
        accessor_->setSource(peer_, value);
        auto source = baseEvent_->GetSourceDevice();
        EXPECT_EQ(source, expected);
    }
}

/**
 * @tc.name: GetPressureTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BaseEventAccessorTest, GetPressureTest, TestSize.Level1)
{
    for (auto& [value, expected] : testFixtureInt32Values) {
        baseEvent_->SetForce(expected);
        auto pressure = accessor_->getPressure(peer_);
        EXPECT_EQ(Converter::Convert<int32_t>(pressure), expected);
    }
}

/**
 * @tc.name: SetPressureTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BaseEventAccessorTest, SetPressureTest, TestSize.Level1)
{
    for (auto& [value, expected] : testFixtureInt32Values) {
        accessor_->setPressure(peer_, &value);
        auto pressure = baseEvent_->GetForce();
        EXPECT_EQ(pressure, expected);
    }
}

/**
 * @tc.name: GetTiltXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BaseEventAccessorTest, GetTiltXTest, TestSize.Level1)
{
    for (auto& [value, expected] : testFixtureInt32Values) {
        baseEvent_->SetTiltX(expected);
        auto tiltX = accessor_->getTiltX(peer_);
        EXPECT_EQ(Converter::Convert<int32_t>(tiltX), expected);
    }
}

/**
 * @tc.name: SetTiltXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BaseEventAccessorTest, SetTiltXTest, TestSize.Level1)
{
    for (auto& [value, expected] : testFixtureInt32Values) {
        accessor_->setTiltX(peer_, &value);
        auto tiltX = baseEvent_->GetTiltX();
        ASSERT_EQ(tiltX.has_value(), true);
        EXPECT_EQ(tiltX.value(), expected);
    }
}

/**
 * @tc.name: GetTiltYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BaseEventAccessorTest, GetTiltYTest, TestSize.Level1)
{
    for (auto& [value, expected] : testFixtureInt32Values) {
        baseEvent_->SetTiltY(expected);
        auto tiltY = accessor_->getTiltY(peer_);
        EXPECT_EQ(Converter::Convert<int32_t>(tiltY), expected);
    }
}

/**
 * @tc.name: SetTiltYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BaseEventAccessorTest, SetTiltYTest, TestSize.Level1)
{
    for (auto& [value, expected] : testFixtureInt32Values) {
        accessor_->setTiltY(peer_, &value);
        auto tiltY = baseEvent_->GetTiltY();
        ASSERT_EQ(tiltY.has_value(), true);
        EXPECT_EQ(tiltY.value(), expected);
    }
}

/**
 * @tc.name: GetSourceToolTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BaseEventAccessorTest, DISABLED_GetSourceToolTest, TestSize.Level1)
{
}

/**
 * @tc.name: SetSourceToolTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BaseEventAccessorTest, SetSourceToolTest, TestSize.Level1)
{
    const std::vector<SourceType> TEST_PLAN = {
        SourceType::MOUSE,
        SourceType::TOUCH
    };

    for (auto expected : TEST_PLAN) {
        Ark_SourceType value = Converter::ArkValue<Ark_SourceType>(expected);
        accessor_->setSource(peer_, value);
        auto source = baseEvent_->GetSourceDevice();
        EXPECT_EQ(source, expected);
    }
}

/**
 * @tc.name: GetDeviceIdTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BaseEventAccessorTest, GetDeviceIdTest, TestSize.Level1)
{
    for (auto& [value, expected] : testFixtureInt32Values) {
        baseEvent_->SetDeviceId(expected);
        auto deviceId = accessor_->getDeviceId(peer_);
        EXPECT_EQ(Converter::Convert<int32_t>(deviceId), expected);
    }
}

/**
 * @tc.name: SetDeviceIdTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BaseEventAccessorTest, SetDeviceIdTest, TestSize.Level1)
{
    for (auto& [value, expected] : testFixtureInt32Values) {
        accessor_->setDeviceId(peer_, &value);
        auto deviceId = baseEvent_->GetDeviceId();
        EXPECT_EQ(deviceId, expected);
    }
}

} // namespace OHOS::Ace::NG