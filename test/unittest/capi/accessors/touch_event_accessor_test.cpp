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
#include "core/interfaces/native/implementation/touch_event_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "test/unittest/capi/accessors/accessor_test_fixtures.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
const std::vector<std::pair<TouchType, Ark_TouchType>> getTypeTestPlan = {
    { TouchType::DOWN, Ark_TouchType::ARK_TOUCH_TYPE_DOWN },
    { TouchType::UP, Ark_TouchType::ARK_TOUCH_TYPE_UP },
    { TouchType::MOVE, Ark_TouchType::ARK_TOUCH_TYPE_MOVE },
    { TouchType::CANCEL, Ark_TouchType::ARK_TOUCH_TYPE_CANCEL },
    { TouchType::UNKNOWN, static_cast<Ark_TouchType>(-1) },
};
} // namespace

class TouchEventAccessorTest
    : public AccessorTestBase<GENERATED_ArkUITouchEventAccessor,
        &GENERATED_ArkUIAccessors::getTouchEventAccessor, TouchEventPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        eventInfo_ = std::make_unique<TouchEventInfo>("unknown");
        peer_->SetEventInfo(eventInfo_.get());
    }

private:
    std::unique_ptr<TouchEventInfo> eventInfo_;
};

/**
 * @tc.name: GetStopPropagationTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TouchEventAccessorTest, GetStopPropagationTest, TestSize.Level1)
{
    TouchEventInfo* eventInfo = peer_->GetEventInfo();
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
 * @tc.name: GetPreventDefaultTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TouchEventAccessorTest, GetPreventDefaultTest, TestSize.Level1)
{
    TouchEventInfo* eventInfo = peer_->GetEventInfo();
    ASSERT_NE(eventInfo, nullptr);
    Callback_Void callback = accessor_->getPreventDefault(peer_);
    auto callbackHelper = CallbackHelper(callback);

    auto checkWithName = [eventInfo, &callbackHelper](const std::string& patternName, bool expected) {
        eventInfo->SetPatternName(patternName);
        eventInfo->SetPreventDefault(false);
        EXPECT_FALSE(eventInfo->IsPreventDefault());
        callbackHelper.Invoke();
        EXPECT_EQ(eventInfo->IsPreventDefault(), expected);
    };

    checkWithName("Checkbox", true);
    checkWithName("RichEditor", false);
    checkWithName("Grid", false);
    checkWithName("Hyperlink", true);

    CallbackKeeper::ReleaseReverseCallback<Callback_Void>(callback);
}

/**
 * @tc.name: GetTypeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TouchEventAccessorTest, GetTypeTest, TestSize.Level1)
{
    for (auto& [value, expected]: getTypeTestPlan) {
        TouchEventInfo* eventInfo = peer_->GetEventInfo();
        ASSERT_NE(eventInfo, nullptr);
        *eventInfo = TouchEventInfo("unknown");

        TouchLocationInfo locationInfo(0);
        locationInfo.SetTouchType(value);
        eventInfo->AddChangedTouchLocationInfo(std::move(locationInfo));

        auto result = accessor_->getType(peer_);
        EXPECT_EQ(result, expected);
    }
}

/**
 * @tc.name: GetHistoricalPointsTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TouchEventAccessorTest, DISABLED_GetHistoricalPointsTest, TestSize.Level1)
{
    TouchEventInfo* eventInfo = peer_->GetEventInfo();
    ASSERT_NE(eventInfo, nullptr);
    using TimeStamp = std::chrono::high_resolution_clock::time_point;
    using Duration = std::chrono::high_resolution_clock::duration;
    constexpr int expectedTime = 123;
    constexpr float expectedDisplayX = 1.5f;
    constexpr float expectedDisplayY = 1.7f;
    constexpr int fingerId = 0;
    constexpr int expectedDeviceId = 256;
    constexpr float expectedWindowX = 2.5f;
    constexpr float expectedWindowY = 3.7f;
    constexpr float expectedX = 4.5f;
    constexpr float expectedY = 5.7f;
    constexpr float expectedForce = 3.5f;
    constexpr float expectedSize = 1.75f;
    Duration value = Duration(std::chrono::nanoseconds(expectedTime));
    TouchLocationInfo locationInfo(fingerId);
    Offset offset(expectedDisplayX, expectedDisplayY);
    locationInfo.SetScreenLocation(offset);
    locationInfo.SetTouchDeviceId(expectedDeviceId);
    locationInfo.SetForce(expectedForce);
    locationInfo.SetSize(expectedSize);
    locationInfo.SetTimeStamp(TimeStamp() + value);
    locationInfo.SetTouchType(TouchType::DOWN);
    Offset globalOffset(expectedWindowX, expectedWindowY);
    locationInfo.SetGlobalLocation(globalOffset);
    Offset localOffset(expectedX, expectedY);
    locationInfo.SetLocalLocation(localOffset);
    eventInfo->AddHistoryLocationInfo(std::move(locationInfo));
    Array_HistoricalPoint history = accessor_->getHistoricalPoints(peer_);
    ASSERT_EQ(static_cast<int32_t>(history.length), 1);
    ASSERT_NE(history.array, nullptr);
    EXPECT_EQ(Converter::Convert<float>(history.array->touchObject.displayX), expectedDisplayX);
    EXPECT_EQ(Converter::Convert<float>(history.array->touchObject.displayY), expectedDisplayY);
    EXPECT_EQ(Converter::Convert<float>(history.array->touchObject.windowX), expectedWindowX);
    EXPECT_EQ(Converter::Convert<float>(history.array->touchObject.windowY), expectedWindowY);
    EXPECT_EQ(Converter::Convert<float>(history.array->touchObject.x), expectedX);
    EXPECT_EQ(Converter::Convert<float>(history.array->touchObject.y), expectedY);
    EXPECT_EQ(Converter::Convert<int32_t>(history.array->touchObject.id), expectedDeviceId);
    EXPECT_EQ(history.array->touchObject.type, Ark_TouchType::ARK_TOUCH_TYPE_DOWN);
    EXPECT_EQ(Converter::Convert<float>(history.array->force), expectedForce);
    EXPECT_EQ(Converter::Convert<float>(history.array->size), expectedSize);
    EXPECT_EQ(Converter::Convert<int64_t>(history.array->timestamp), expectedTime);
}

/**
 * @tc.name: GetTouchesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TouchEventAccessorTest, DISABLED_GetTouchesTest, TestSize.Level1)
{
    TouchEventInfo* eventInfo = peer_->GetEventInfo();
    ASSERT_NE(eventInfo, nullptr);
    constexpr float expectedDisplayX = 1.5f;
    constexpr float expectedDisplayY = 1.7f;
    constexpr int fingerId = 0;
    constexpr int expectedDeviceId = 256;
    constexpr float expectedWindowX = 2.5f;
    constexpr float expectedWindowY = 3.7f;
    constexpr float expectedX = 4.5f;
    constexpr float expectedY = 5.7f;

    TouchLocationInfo locationInfo(fingerId);
    Offset offset(expectedDisplayX, expectedDisplayY);
    locationInfo.SetScreenLocation(offset);
    locationInfo.SetTouchDeviceId(expectedDeviceId);
    locationInfo.SetTouchType(TouchType::DOWN);
    Offset globalOffset(expectedWindowX, expectedWindowY);
    locationInfo.SetGlobalLocation(globalOffset);
    Offset localOffset(expectedX, expectedY);
    locationInfo.SetLocalLocation(localOffset);

    eventInfo->AddTouchLocationInfo(std::move(locationInfo));
    Array_TouchObject touches = accessor_->getTouches(peer_);

    ASSERT_EQ(static_cast<int32_t>(touches.length), 1);
    ASSERT_NE(touches.array, nullptr);
    EXPECT_EQ(Converter::Convert<float>(touches.array->displayX), expectedDisplayX);
    EXPECT_EQ(Converter::Convert<float>(touches.array->displayY), expectedDisplayY);
    EXPECT_EQ(Converter::Convert<float>(touches.array->windowX), expectedWindowX);
    EXPECT_EQ(Converter::Convert<float>(touches.array->windowY), expectedWindowY);
    EXPECT_EQ(Converter::Convert<float>(touches.array->x), expectedX);
    EXPECT_EQ(Converter::Convert<float>(touches.array->y), expectedY);
    EXPECT_EQ(Converter::Convert<int32_t>(touches.array->id), expectedDeviceId);
    EXPECT_EQ(touches.array->type, Ark_TouchType::ARK_TOUCH_TYPE_DOWN);
}

/**
 * @tc.name: GetChangedTouchesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TouchEventAccessorTest, DISABLED_GetChangedTouchesTest, TestSize.Level1)
{
    TouchEventInfo* eventInfo = peer_->GetEventInfo();
    ASSERT_NE(eventInfo, nullptr);
    constexpr float expectedDisplayX = 1.5f;
    constexpr float expectedDisplayY = 1.7f;
    constexpr int fingerId = 0;
    constexpr int expectedDeviceId = 256;
    constexpr float expectedWindowX = 2.5f;
    constexpr float expectedWindowY = 3.7f;
    constexpr float expectedX = 4.5f;
    constexpr float expectedY = 5.7f;

    TouchLocationInfo locationInfo(fingerId);
    Offset offset(expectedDisplayX, expectedDisplayY);
    locationInfo.SetScreenLocation(offset);
    locationInfo.SetTouchDeviceId(expectedDeviceId);
    locationInfo.SetTouchType(TouchType::DOWN);
    Offset globalOffset(expectedWindowX, expectedWindowY);
    locationInfo.SetGlobalLocation(globalOffset);
    Offset localOffset(expectedX, expectedY);
    locationInfo.SetLocalLocation(localOffset);

    eventInfo->AddChangedTouchLocationInfo(std::move(locationInfo));
    Array_TouchObject touches = accessor_->getChangedTouches(peer_);

    ASSERT_EQ(static_cast<int32_t>(touches.length), 1);
    ASSERT_NE(touches.array, nullptr);
    EXPECT_EQ(Converter::Convert<float>(touches.array->displayX), expectedDisplayX);
    EXPECT_EQ(Converter::Convert<float>(touches.array->displayY), expectedDisplayY);
    EXPECT_EQ(Converter::Convert<float>(touches.array->windowX), expectedWindowX);
    EXPECT_EQ(Converter::Convert<float>(touches.array->windowY), expectedWindowY);
    EXPECT_EQ(Converter::Convert<float>(touches.array->x), expectedX);
    EXPECT_EQ(Converter::Convert<float>(touches.array->y), expectedY);
    EXPECT_EQ(Converter::Convert<int32_t>(touches.array->id), expectedDeviceId);
    EXPECT_EQ(touches.array->type, Ark_TouchType::ARK_TOUCH_TYPE_DOWN);
}

}
