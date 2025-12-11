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

const std::vector<std::pair<Ark_Number, float>> testFixtureFloatValues = {
    { Converter::ArkValue<Ark_Number>(123.321f), 123.321f },
    { Converter::ArkValue<Ark_Number>(0.0f), 0.0f },
    { Converter::ArkValue<Ark_Number>(30.3f), 30.3f },
    { Converter::ArkValue<Ark_Number>(55.5f), 55.5f },
    { Converter::ArkValue<Ark_Number>(65000.0f), 65000.0f },
    { Converter::ArkValue<Ark_Number>(10.0f), 10.0f },
};

/**
 * @tc.name: GetModifierKeyStateTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BaseEventAccessorTest, DISABLED_GetModifierKeyStateTest, TestSize.Level1)
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
 * @tc.name: GetTargetTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BaseEventAccessorTest, DISABLED_GetTargetTest, TestSize.Level1)
{
    const Dimension height(100.f);
    const Dimension width(200.f);
    const Dimension offsetX(150.f);
    const Dimension offsetY(250.f);
    const Dimension originX(100.f);
    const Dimension originY(450.f);

    DimensionRect area(width, height, DimensionOffset(offsetX, offsetY));
    EventTarget target{ "", "", area, DimensionOffset(originX, originY)};

    baseEvent_->SetTarget(target);
    auto result = accessor_->getTarget(peer_);

    EXPECT_EQ(Converter::OptConvert<Dimension>(result.area.height), height);
    EXPECT_EQ(Converter::OptConvert<Dimension>(result.area.width), width);

    auto optOffsetX = Converter::OptConvert<Dimension>(result.area.position.x);
    ASSERT_TRUE(optOffsetX.has_value());
    EXPECT_EQ(optOffsetX.value(), offsetX);
    auto optOffsetY = Converter::OptConvert<Dimension>(result.area.position.y);
    ASSERT_TRUE(optOffsetY.has_value());
    EXPECT_EQ(optOffsetY.value(), offsetY);
    auto optOriginX = Converter::OptConvert<Dimension>(result.area.globalPosition.x);
    ASSERT_TRUE(optOriginX.has_value());
    EXPECT_EQ(optOriginX.value(), originX);
    auto optOriginY = Converter::OptConvert<Dimension>(result.area.globalPosition.y);
    ASSERT_TRUE(optOriginY.has_value());
    EXPECT_EQ(optOriginY.value(), originY);
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
HWTEST_F(BaseEventAccessorTest, DISABLED_GetTimeStampTest, TestSize.Level1)
{
    using TimeStamp = std::chrono::high_resolution_clock::time_point;
    using Duration = std::chrono::high_resolution_clock::duration;

    const std::vector<std::pair<int64_t, Duration>> TEST_PLAN = {
        { 123, Duration(std::chrono::nanoseconds(123)) },
        { 10000, Duration(std::chrono::nanoseconds(10000)) },
        {std::numeric_limits<int64_t>::min(), Duration(std::chrono::nanoseconds(std::numeric_limits<int64_t>::min()))},
        {std::numeric_limits<int64_t>::max(), Duration(std::chrono::nanoseconds(std::numeric_limits<int64_t>::max()))},
    };

    for (auto& [expected, value] : TEST_PLAN) {
        baseEvent_->SetTimeStamp(TimeStamp() + value);
        auto timeStamp = accessor_->getTimestamp(peer_);
        EXPECT_EQ(Converter::Convert<int64_t>(timeStamp), expected);
    }
}

/**
 * @tc.name: SetTimeStampTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BaseEventAccessorTest, DISABLED_SetTimeStampTest, TestSize.Level1)
{
    using TimeStamp = std::chrono::high_resolution_clock::time_point;
    using Duration = std::chrono::high_resolution_clock::duration;
    const std::vector<std::pair<Ark_Int64, Duration>> TEST_PLAN = {
        { 123, Duration(std::chrono::nanoseconds(123)) },
        { 10000, Duration(std::chrono::nanoseconds(10000)) },
        {std::numeric_limits<int64_t>::min(), Duration(std::chrono::nanoseconds(std::numeric_limits<int64_t>::min()))},
        {std::numeric_limits<int64_t>::max(), Duration(std::chrono::nanoseconds(std::numeric_limits<int64_t>::max()))},
    };

    for (auto& [value, duration] : TEST_PLAN) {
        accessor_->setTimestamp(peer_, value);
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
HWTEST_F(BaseEventAccessorTest, GetSourceTest, TestSize.Level1)
{
    const std::vector<std::pair<SourceType, Ark_SourceType>> TEST_PLAN = {
        { SourceType::NONE, Ark_SourceType::ARK_SOURCE_TYPE_UNKNOWN },
        { SourceType::MOUSE, Ark_SourceType::ARK_SOURCE_TYPE_MOUSE },
        { SourceType::TOUCH, Ark_SourceType::ARK_SOURCE_TYPE_TOUCH_SCREEN },
        { SourceType::TOUCH_PAD, static_cast<Ark_SourceType>(-1) }
    };

    for (auto& [input, expected] : TEST_PLAN) {
        baseEvent_->SetSourceDevice(input);
        auto source = accessor_->getSource(peer_);
        EXPECT_EQ(source, expected);
    }

    auto source = accessor_->getSource(nullptr);
    EXPECT_EQ(source, static_cast<Ark_SourceType>(-1));
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
 * @tc.name: GetRollAngleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BaseEventAccessorTest, GetRollAngleTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getRollAngle, nullptr);
    for (auto& [value, expected] : testFixtureFloatValues) {
        baseEvent_->SetRollAngle(expected);
        auto rollAngle = accessor_->getRollAngle(peer_);
        auto result = Converter::OptConvert<float>(rollAngle);
        ASSERT_TRUE(result.has_value());
        EXPECT_EQ(result.value(), expected);
    }
}

/**
 * @tc.name: SetRollAngleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BaseEventAccessorTest, SetRollAngleTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setRollAngle, nullptr);
    for (auto& [value, expected] : testFixtureFloatValues) {
        accessor_->setRollAngle(peer_, &value);
        auto rollAngle = baseEvent_->GetRollAngle();
        ASSERT_EQ(rollAngle.has_value(), true);
        EXPECT_EQ(rollAngle.value(), expected);
    }
}

/**
 * @tc.name: GetSourceToolTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BaseEventAccessorTest, GetSourceToolTest, TestSize.Level1)
{
    const std::vector<std::pair<SourceTool, Ark_SourceTool>> TEST_PLAN = {
        { SourceTool::UNKNOWN, Ark_SourceTool::ARK_SOURCE_TOOL_UNKNOWN },
        { SourceTool::BRUSH, static_cast<Ark_SourceTool>(-1) },
        { SourceTool::FINGER, Ark_SourceTool::ARK_SOURCE_TOOL_FINGER },
        { SourceTool::RUBBER, static_cast<Ark_SourceTool>(-1) },
        { SourceTool::PEN, Ark_SourceTool::ARK_SOURCE_TOOL_PEN },
        { SourceTool::PENCIL, static_cast<Ark_SourceTool>(-1) },
        { SourceTool::MOUSE, Ark_SourceTool::ARK_SOURCE_TOOL_MOUSE },
        { SourceTool::AIRBRUSH, static_cast<Ark_SourceTool>(-1) },
        { SourceTool::TOUCHPAD, Ark_SourceTool::ARK_SOURCE_TOOL_TOUCHPAD },
        { SourceTool::JOYSTICK, Ark_SourceTool::ARK_SOURCE_TOOL_JOYSTICK },
        { SourceTool::LENS, static_cast<Ark_SourceTool>(-1) }
    };

    for (auto& [input, expected] : TEST_PLAN) {
        baseEvent_->SetSourceTool(input);
        auto sourceTool = accessor_->getSourceTool(peer_);
        EXPECT_EQ(sourceTool, expected);
    }

    auto sourceTool = accessor_->getSourceTool(nullptr);
    EXPECT_EQ(sourceTool, static_cast<Ark_SourceTool>(-1));
}

/**
 * @tc.name: SetSourceToolTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BaseEventAccessorTest, SetSourceToolTest, TestSize.Level1)
{
    const std::vector<std::pair<SourceTool, SourceTool>> TEST_PLAN = {
        { SourceTool::UNKNOWN, SourceTool::UNKNOWN },
        { SourceTool::FINGER, SourceTool::FINGER },
        { SourceTool::PEN, SourceTool::PEN },
        { SourceTool::RUBBER, SourceTool::PEN },
        { SourceTool::BRUSH, SourceTool::PEN },
        { SourceTool::PENCIL, SourceTool::PEN },
        { SourceTool::AIRBRUSH, SourceTool::PEN },
        { SourceTool::MOUSE, SourceTool::MOUSE },
        { SourceTool::LENS, SourceTool::MOUSE },
        { SourceTool::TOUCHPAD, SourceTool::TOUCHPAD },
        { SourceTool::JOYSTICK, SourceTool::JOYSTICK },
        { static_cast<SourceTool>(10000), SourceTool::JOYSTICK },
    };

    for (auto& [input, expected] : TEST_PLAN) {
        Ark_SourceTool value = Converter::ArkValue<Ark_SourceTool>(input);
        accessor_->setSourceTool(peer_, value);
        auto source = baseEvent_->GetSourceTool();
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
        EXPECT_EQ(Converter::OptConvert<int32_t>(deviceId), expected);
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

/**
 * @tc.name: GetTargetDisplayIdTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BaseEventAccessorTest, GetTargetDisplayIdTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getTargetDisplayId, nullptr);
    for (auto& [value, expected] : testFixtureInt32Values) {
        baseEvent_->SetTargetDisplayId(expected);
        Opt_Number id = accessor_->getTargetDisplayId(peer_);
        EXPECT_EQ(Converter::OptConvert<int32_t>(id), expected);
    }
    Opt_Number emptyId1 = accessor_->getTargetDisplayId(nullptr);
    EXPECT_EQ(Converter::OptConvert<int32_t>(emptyId1), std::nullopt);
    peer_->SetEventInfo(nullptr);
    Opt_Number emptyId2 = accessor_->getTargetDisplayId(peer_);
    EXPECT_EQ(Converter::OptConvert<int32_t>(emptyId2), std::nullopt);
}

/**
 * @tc.name: SetTargetDisplayIdTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BaseEventAccessorTest, SetTargetDisplayIdTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setTargetDisplayId, nullptr);
    for (auto& [value, expected] : testFixtureInt32Values) {
        accessor_->setTargetDisplayId(peer_, &value);
        int32_t id = baseEvent_->GetTargetDisplayId();
        EXPECT_EQ(id, expected);
    }
    const auto value = Converter::ArkValue<Ark_Number>(-1);
    accessor_->setTargetDisplayId(nullptr, &value);
    accessor_->setTargetDisplayId(peer_, nullptr);
    int32_t id = baseEvent_->GetTargetDisplayId();
    EXPECT_EQ(id, testFixtureInt32Values.back().second);
}

} // namespace OHOS::Ace::NG
