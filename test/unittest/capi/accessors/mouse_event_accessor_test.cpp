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
#include "core/interfaces/native/implementation/mouse_event_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "test/unittest/capi/accessors/accessor_test_fixtures.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class MouseEventAccessorTest
    : public AccessorTestBase<GENERATED_ArkUIMouseEventAccessor,
        &GENERATED_ArkUIAccessors::getMouseEventAccessor, MouseEventPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        eventInfo_ = std::make_unique<MouseInfo>();
        peer_->SetEventInfo(eventInfo_.get());
    }

private:
    std::unique_ptr<MouseInfo> eventInfo_;
};

namespace {
    const double EPSILON = 0.001;

    const std::vector<std::tuple<std::string, Ark_Number, double>> testFixtureNumberValues = {
        { "1.24", Converter::ArkValue<Ark_Number>(1.24), 1.24 },
        { "0", Converter::ArkValue<Ark_Number>(0), 0 },
        { "100", Converter::ArkValue<Ark_Number>(100), 100 },
        { "-20.65", Converter::ArkValue<Ark_Number>(-20.65), -20.65 },
    };

    const std::vector<std::pair<MouseAction, Ark_MouseAction>> getMouseActionTestPlan = {
        { MouseAction::NONE, static_cast<Ark_MouseAction>(-1) },
        { MouseAction::PRESS, Ark_MouseAction::ARK_MOUSE_ACTION_PRESS },
        { MouseAction::RELEASE, Ark_MouseAction::ARK_MOUSE_ACTION_RELEASE },
        { MouseAction::MOVE, Ark_MouseAction::ARK_MOUSE_ACTION_MOVE },
        { MouseAction::WINDOW_ENTER, static_cast<Ark_MouseAction>(-1) },
        { MouseAction::WINDOW_LEAVE, static_cast<Ark_MouseAction>(-1) },
        { MouseAction::HOVER, Ark_MouseAction::ARK_MOUSE_ACTION_HOVER },
        { MouseAction::HOVER_ENTER, static_cast<Ark_MouseAction>(-1) },
        { MouseAction::HOVER_MOVE, static_cast<Ark_MouseAction>(-1) },
        { MouseAction::HOVER_EXIT, static_cast<Ark_MouseAction>(-1) },
        { MouseAction::PULL_DOWN, static_cast<Ark_MouseAction>(-1) },
        { MouseAction::PULL_MOVE, static_cast<Ark_MouseAction>(-1) },
        { MouseAction::PULL_UP, static_cast<Ark_MouseAction>(-1) },
        { MouseAction::CANCEL, static_cast<Ark_MouseAction>(-1) },
    };

    const std::vector<std::pair<MouseButton, Ark_MouseButton>> getMouseButtonTestPlan = {
        { MouseButton::NONE_BUTTON, Ark_MouseButton::ARK_MOUSE_BUTTON_NONE },
        { MouseButton::LEFT_BUTTON, Ark_MouseButton::ARK_MOUSE_BUTTON_LEFT },
        { MouseButton::RIGHT_BUTTON, Ark_MouseButton::ARK_MOUSE_BUTTON_RIGHT },
        { MouseButton::MIDDLE_BUTTON, Ark_MouseButton::ARK_MOUSE_BUTTON_MIDDLE },
        { MouseButton::BACK_BUTTON, Ark_MouseButton::ARK_MOUSE_BUTTON_BACK },
        { MouseButton::FORWARD_BUTTON, Ark_MouseButton::ARK_MOUSE_BUTTON_FORWARD },
        { MouseButton::SIDE_BUTTON, static_cast<Ark_MouseButton>(-1) },
        { MouseButton::EXTRA_BUTTON, static_cast<Ark_MouseButton>(-1) },
        { MouseButton::TASK_BUTTON, static_cast<Ark_MouseButton>(-1) },
    };
}

/**
 * @tc.name: getStopPropagationTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MouseEventAccessorTest, getStopPropagationTest, TestSize.Level1)
{
    MouseInfo* eventInfo = peer_->GetEventInfo();
    ASSERT_NE(eventInfo, nullptr);
    Callback_Void callback = accessor_->getStopPropagation(peer_);
    auto callbackHelper = CallbackHelper(callback);
    eventInfo->SetStopPropagation(false);
    EXPECT_FALSE(eventInfo->IsStopPropagation());
    callbackHelper.Invoke();
    EXPECT_TRUE(eventInfo->IsStopPropagation());
    CallbackKeeper::ReleaseReverseCallback<Callback_Void>(callback);
}

/**
 * @tc.name: setButtonTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MouseEventAccessorTest, setButtonTest, TestSize.Level1)
{
    auto info = peer_->GetEventInfo();
    ASSERT_NE(info, nullptr);
    auto button = info->GetButton();
    EXPECT_EQ(button, MouseButton::NONE_BUTTON);
    auto value = Ark_MouseButton::ARK_MOUSE_BUTTON_LEFT;
    accessor_->setButton(peer_, value);
    button = info->GetButton();
    EXPECT_EQ(button, MouseButton::LEFT_BUTTON);
}

/**
 * @tc.name: getButtonTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MouseEventAccessorTest, getButtonTest, TestSize.Level1)
{
    for (auto& [value, expected]: getMouseButtonTestPlan) {
        auto eventInfo = peer_->GetEventInfo();
        ASSERT_NE(eventInfo, nullptr);
        eventInfo->SetButton(value);
        auto result = accessor_->getButton(peer_);
        EXPECT_EQ(result, expected);
    }
}

/**
 * @tc.name: setActionTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MouseEventAccessorTest, setActionTest, TestSize.Level1)
{
    auto info = peer_->GetEventInfo();
    ASSERT_NE(info, nullptr);
    auto action = info->GetAction();
    EXPECT_EQ(action, MouseAction::NONE);
    auto value = Ark_MouseAction::ARK_MOUSE_ACTION_MOVE;
    accessor_->setAction(peer_, value);
    action = info->GetAction();
    EXPECT_EQ(action, MouseAction::MOVE);
}

/**
 * @tc.name: getActionTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MouseEventAccessorTest, DISABLED_getActionTest, TestSize.Level1)
{
    for (auto& [value, expected]: getMouseActionTestPlan) {
        auto eventInfo = peer_->GetEventInfo();
        ASSERT_NE(eventInfo, nullptr);
        eventInfo->SetAction(value);
        auto result = accessor_->getAction(peer_);
        EXPECT_EQ(result, expected);
    }
}

/**
 * @tc.name: getDisplayXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MouseEventAccessorTest, getDisplayXTest, TestSize.Level1)
{
    for (auto& [input, expected, value] : testFixtureNumberValues) {
        auto info = peer_->GetEventInfo();
        ASSERT_NE(info, nullptr);
        Offset screenLocation;
        screenLocation.SetX(value);
        info->SetScreenLocation(screenLocation);
        auto arkRes = accessor_->getDisplayX(peer_);
        EXPECT_EQ(Converter::Convert<float>(arkRes), Converter::Convert<float>(expected)) <<
            "Input value is: " << input << ", method: getDisplayX";
    }
}

/**
 * @tc.name: setDisplayXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MouseEventAccessorTest, setDisplayXTest, TestSize.Level1)
{
    auto info = peer_->GetEventInfo();
    ASSERT_NE(info, nullptr);
    auto screenLocation = info->GetScreenLocation();
    auto x = screenLocation.GetX();
    EXPECT_EQ(x, 0);
    for (auto& [input, value, expected] : testFixtureNumberValues) {
        accessor_->setDisplayX(peer_, &value);
        info = peer_->GetEventInfo();
        ASSERT_NE(info, nullptr);
        screenLocation = info->GetScreenLocation();
        EXPECT_NEAR(screenLocation.GetX(), expected, EPSILON) <<
            "Input value is: " << input << ", method: SetDisplayX";
    }
}

/**
 * @tc.name: getDisplayYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MouseEventAccessorTest, getDisplayYTest, TestSize.Level1)
{
    for (auto& [input, expected, value] : testFixtureNumberValues) {
        auto info = peer_->GetEventInfo();
        ASSERT_NE(info, nullptr);
        Offset screenLocation;
        screenLocation.SetY(value);
        info->SetScreenLocation(screenLocation);
        auto arkRes = accessor_->getDisplayY(peer_);
        EXPECT_EQ(Converter::Convert<float>(arkRes), Converter::Convert<float>(expected)) <<
            "Input value is: " << input << ", method: getDisplayY";
    }
}

/**
 * @tc.name: setDisplayYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MouseEventAccessorTest, setDisplayYTest, TestSize.Level1)
{
    auto info = peer_->GetEventInfo();
    ASSERT_NE(info, nullptr);
    auto screenLocation = info->GetScreenLocation();
    auto y = screenLocation.GetY();
    EXPECT_EQ(y, 0);
    for (auto& [input, value, expected] : testFixtureNumberValues) {
        accessor_->setDisplayY(peer_, &value);
        info = peer_->GetEventInfo();
        ASSERT_NE(info, nullptr);
        auto screenLocation = info->GetScreenLocation();
        EXPECT_NEAR(screenLocation.GetY(), expected, EPSILON) <<
            "Input value is: " << input << ", method: SetDisplayY";
    }
}

/**
 * @tc.name: getWindowXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MouseEventAccessorTest, getWindowXTest, TestSize.Level1)
{
    for (auto& [input, expected, value] : testFixtureNumberValues) {
        auto info = peer_->GetEventInfo();
        ASSERT_NE(info, nullptr);
        Offset globalLocation;
        globalLocation.SetX(value);
        info->SetGlobalLocation(globalLocation);
        auto arkRes = accessor_->getWindowX(peer_);
        EXPECT_EQ(Converter::Convert<float>(arkRes), Converter::Convert<float>(expected)) <<
            "Input value is: " << input << ", method: GetWindowX";
    }
}

/**
 * @tc.name: setWindowXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MouseEventAccessorTest, setWindowXTest, TestSize.Level1)
{
    auto info = peer_->GetEventInfo();
    ASSERT_NE(info, nullptr);
    auto globalLocation = info->GetGlobalLocation();
    auto x = globalLocation.GetX();
    EXPECT_EQ(x, 0);
    for (auto& [input, value, expected] : testFixtureNumberValues) {
        accessor_->setWindowX(peer_, &value);
        auto info = peer_->GetEventInfo();
        ASSERT_NE(info, nullptr);
        globalLocation = info->GetGlobalLocation();
        EXPECT_NEAR(globalLocation.GetX(), expected, EPSILON) <<
            "Input value is: " << input << ", method: SetWindowX";
    }
}

/**
 * @tc.name: getWindowYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MouseEventAccessorTest, getWindowYTest, TestSize.Level1)
{
    for (auto& [input, expected, value] : testFixtureNumberValues) {
        auto info = peer_->GetEventInfo();
        ASSERT_NE(info, nullptr);
        Offset globalLocation;
        globalLocation.SetY(value);
        info->SetGlobalLocation(globalLocation);
        auto arkRes = accessor_->getWindowY(peer_);
        EXPECT_EQ(Converter::Convert<float>(arkRes), Converter::Convert<float>(expected)) <<
            "Input value is: " << input << ", method: GetWindowY";
    }
}

/**
 * @tc.name: setWindowYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MouseEventAccessorTest, setWindowYTest, TestSize.Level1)
{
    auto info = peer_->GetEventInfo();
    ASSERT_NE(info, nullptr);
    auto globalLocation = info->GetGlobalLocation();
    auto y = globalLocation.GetY();
    EXPECT_EQ(y, 0);
    for (auto& [input, value, expected] : testFixtureNumberValues) {
        accessor_->setWindowY(peer_, &value);
        auto info = peer_->GetEventInfo();
        ASSERT_NE(info, nullptr);
        globalLocation = info->GetGlobalLocation();
        EXPECT_NEAR(globalLocation.GetY(), expected, EPSILON) <<
            "Input value is: " << input << ", method: SetWindowY";
    }
}

/**
 * @tc.name: getXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MouseEventAccessorTest, getXTest, TestSize.Level1)
{
    for (auto& [input, expected, value] : testFixtureNumberValues) {
        auto info = peer_->GetEventInfo();
        ASSERT_NE(info, nullptr);
        Offset localLocation;
        localLocation.SetX(value);
        info->SetLocalLocation(localLocation);
        auto arkRes = accessor_->getX(peer_);
        EXPECT_EQ(Converter::Convert<float>(arkRes), Converter::Convert<float>(expected)) <<
            "Input value is: " << input << ", method: GetX";
    }
}

/**
 * @tc.name: setXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MouseEventAccessorTest, setXTest, TestSize.Level1)
{
    auto info = peer_->GetEventInfo();
    ASSERT_NE(info, nullptr);
    auto localLocation = info->GetLocalLocation();
    auto x = localLocation.GetX();
    EXPECT_EQ(x, 0);
    for (auto& [input, value, expected] : testFixtureNumberValues) {
        accessor_->setX(peer_, &value);
        auto info = peer_->GetEventInfo();
        ASSERT_NE(info, nullptr);
        localLocation = info->GetLocalLocation();
        EXPECT_NEAR(localLocation.GetX(), expected, EPSILON) <<
            "Input value is: " << input << ", method: SetYTest";
    }
}

/**
 * @tc.name: getYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MouseEventAccessorTest, getYTest, TestSize.Level1)
{
    for (auto& [input, expected, value] : testFixtureNumberValues) {
        auto info = peer_->GetEventInfo();
        ASSERT_NE(info, nullptr);
        Offset localLocation;
        localLocation.SetY(value);
        info->SetLocalLocation(localLocation);
        auto arkRes = accessor_->getY(peer_);
        EXPECT_EQ(Converter::Convert<float>(arkRes), Converter::Convert<float>(expected)) <<
            "Input value is: " << input << ", method: GetY";
    }
}

/**
 * @tc.name: setYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MouseEventAccessorTest, setYTest, TestSize.Level1)
{
    auto info = peer_->GetEventInfo();
    ASSERT_NE(info, nullptr);
    auto localLocation = info->GetLocalLocation();
    auto y = localLocation.GetY();
    EXPECT_EQ(y, 0);
    for (auto& [input, value, expected] : testFixtureNumberValues) {
        accessor_->setY(peer_, &value);
        auto info = peer_->GetEventInfo();
        ASSERT_NE(info, nullptr);
        auto localLocation = info->GetLocalLocation();
        EXPECT_NEAR(localLocation.GetY(), expected, EPSILON) <<
            "Input value is: " << input << ", method: SetYTest";
    }
}

/**
 * @tc.name: setRawDeltaXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MouseEventAccessorTest, setRawDeltaXTest, TestSize.Level1)
{
    auto info = peer_->GetEventInfo();
    ASSERT_NE(info, nullptr);
    auto deltaX = info->GetRawDeltaX();
    EXPECT_EQ(deltaX, 0);
    for (auto& [input, value, expected] : testFixtureNumberValues) {
        auto optValue = Converter::ArkValue<Opt_Number>(value);
        accessor_->setRawDeltaX(peer_, &optValue);
        auto info = peer_->GetEventInfo();
        ASSERT_NE(info, nullptr);
        auto deltaX = info->GetRawDeltaX();
        EXPECT_NEAR(deltaX, expected, EPSILON) <<
            "Input value is: " << input << ", method: SetRawDeltaX";
    }
}

/**
 * @tc.name: getRawDeltaXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MouseEventAccessorTest, getRawDeltaXTest, TestSize.Level1)
{
    for (auto& [input, expected, value] : testFixtureNumberValues) {
        auto info = peer_->GetEventInfo();
        ASSERT_NE(info, nullptr);
        info->SetRawDeltaX(value);
        auto arkRes = accessor_->getRawDeltaX(peer_);
        EXPECT_EQ(Converter::OptConvert<float>(arkRes), Converter::Convert<float>(expected)) <<
            "Input value is: " << input << ", method: GetRawDeltaX";
    }
}

/**
 * @tc.name: setRawDeltaYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MouseEventAccessorTest, DISABLED_setRawDeltaYTest, TestSize.Level1)
{
    auto info = peer_->GetEventInfo();
    ASSERT_NE(info, nullptr);
    auto deltaY = info->GetRawDeltaY();
    EXPECT_EQ(deltaY, 0);
    for (auto& [input, value, expected] : testFixtureNumberValues) {
        auto optValue = Converter::ArkValue<Opt_Number>(value);
        accessor_->setRawDeltaY(peer_, &optValue);
        auto info = peer_->GetEventInfo();
        ASSERT_NE(info, nullptr);
        auto deltaY = info->GetRawDeltaY();
        EXPECT_NEAR(deltaY, expected, EPSILON) <<
            "Input value is: " << input << ", method: SetRawDeltaY";
    }
}

/**
 * @tc.name: getRawDeltaYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MouseEventAccessorTest, getRawDeltaYTest, TestSize.Level1)
{
    for (auto& [input, expected, value] : testFixtureNumberValues) {
        auto info = peer_->GetEventInfo();
        ASSERT_NE(info, nullptr);
        info->SetRawDeltaY(value);
        auto arkRes = accessor_->getRawDeltaY(peer_);
        EXPECT_EQ(Converter::OptConvert<float>(arkRes), Converter::Convert<float>(expected)) <<
            "Input value is: " << input << ", method: GetRawDeltaY";
    }
}

/**
 * @tc.name: getPressedButtonsTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MouseEventAccessorTest, getPressedButtonsTest, TestSize.Level1)
{
    auto eventInfo = peer_->GetEventInfo();
    ASSERT_NE(eventInfo, nullptr);
    std::vector<MouseButton> buttons;
    buttons.push_back(MouseButton::LEFT_BUTTON);
    buttons.push_back(MouseButton::RIGHT_BUTTON);
    eventInfo->SetPressedButtons(buttons);
    auto optPressedButtons = Converter::GetOpt(accessor_->getPressedButtons(peer_));
    ASSERT_NE(optPressedButtons, std::nullopt);
    auto pressedButtons = *optPressedButtons;
    EXPECT_EQ(pressedButtons.length, 2);
    ASSERT_NE(pressedButtons.array, nullptr);
    EXPECT_EQ(pressedButtons.array[0], Ark_MouseButton::ARK_MOUSE_BUTTON_LEFT);
    EXPECT_EQ(pressedButtons.array[1], Ark_MouseButton::ARK_MOUSE_BUTTON_RIGHT);
}

/**
 * @tc.name: setPressedButtonsTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MouseEventAccessorTest, setPressedButtonsTest, TestSize.Level1)
{
    auto eventInfo = peer_->GetEventInfo();
    ASSERT_NE(eventInfo, nullptr);
    std::array arr{Ark_MouseButton::ARK_MOUSE_BUTTON_LEFT, Ark_MouseButton::ARK_MOUSE_BUTTON_RIGHT};
    Converter::ConvContext ctx;
    auto pressedButtons = Converter::ArkValue<Opt_Array_MouseButton>(arr, &ctx);
    accessor_->setPressedButtons(peer_, &pressedButtons);
    auto buttons = eventInfo->GetPressedButtons();
    EXPECT_EQ(buttons[0], MouseButton::LEFT_BUTTON);
    EXPECT_EQ(buttons[1], MouseButton::RIGHT_BUTTON);
}
}
