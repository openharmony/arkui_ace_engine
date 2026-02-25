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
#include "accessor_test_base.h"
#include "core/interfaces/native/implementation/gesture_event_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "test/unittest/capi/accessors/accessor_test_fixtures.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class GestureEventAccessorTest
    : public AccessorTestBase<GENERATED_ArkUIGestureEventAccessor,
        &GENERATED_ArkUIAccessors::getGestureEventAccessor, GestureEventPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        const double testDensity = 2.0;
        MockPipelineContext::GetCurrent()->SetDensity(testDensity);
        eventInfo_ = std::make_unique<GestureEvent>();
        peer_->SetEventInfo(eventInfo_.get());
    }

    std::unique_ptr<GestureEvent> eventInfo_;
};

namespace {
    const double EPSILON = 0.001;
}

/**
 * @tc.name: getRepeatTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventAccessorTest, getRepeatTest, TestSize.Level1)
{
    for (auto& [input, expected, value] : AccessorTestFixtures::testFixtureBooleanValues) {
        GestureEvent* event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        event->SetRepeat(value);
        Ark_Boolean arkRes = accessor_->getRepeat(peer_);
        EXPECT_EQ(arkRes, expected) <<
            "Input value is: " << input << ", method: GetRepeat";
    }
}

/**
 * @tc.name: setRepeatTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventAccessorTest, setRepeatTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureBooleanValues) {
        accessor_->setRepeat(peer_, value);
        GestureEvent* event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        EXPECT_EQ(event->GetRepeat(), expected) <<
            "Input value is: " << input << ", method: SetRepeat";
    }
}

/**
 * @tc.name: getOffsetXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventAccessorTest, getOffsetXTest, TestSize.Level1)
{
    PipelineBase::GetCurrentDensity();
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureFloatFloat_half_Values) {
        GestureEvent* event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        event->SetOffsetX(value);
        Ark_Number arkRes = accessor_->getOffsetX(peer_);
        EXPECT_FLOAT_EQ(Converter::Convert<float>(arkRes), expected) <<
            "Input value is: " << input << ", method: GetOffsetX";
    }
}

/**
 * @tc.name: setOffsetXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventAccessorTest, setOffsetXTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureNumber_2x_Values) {
        accessor_->setOffsetX(peer_, &value);
        GestureEvent* event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        EXPECT_NEAR(event->GetOffsetX(), expected, EPSILON) <<
            "Input value is: " << input << ", method: SetOffsetX";
    }
}

/**
 * @tc.name: getOffsetYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventAccessorTest, getOffsetYTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureFloatFloat_half_Values) {
        GestureEvent* event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        event->SetOffsetY(value);
        auto arkRes = accessor_->getOffsetY(peer_);
        EXPECT_FLOAT_EQ(Converter::Convert<float>(arkRes), expected) <<
            "Input value is: " << input << ", method: GetOffsetY";
    }
}

/**
 * @tc.name: setOffsetYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventAccessorTest, setOffsetYTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureNumber_2x_Values) {
        accessor_->setOffsetY(peer_, &value);
        GestureEvent* event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        EXPECT_NEAR(event->GetOffsetY(), expected, EPSILON) <<
            "Input value is: " << input << ", method: SetOffsetY";
    }
}

/**
 * @tc.name: getAngleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventAccessorTest, getAngleTest, TestSize.Level1)
{
    for (auto value : AccessorTestFixtures::testFixtureFloatValues) {
        GestureEvent* event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        event->SetAngle(value);
        auto arkRes = accessor_->getAngle(peer_);
        EXPECT_FLOAT_EQ(Converter::Convert<float>(arkRes), value) <<
            "Input value is: " << value << ", method: GetAngle";
    }
}

/**
 * @tc.name: setAngleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventAccessorTest, setAngleTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureNumberValues) {
        accessor_->setAngle(peer_, &value);
        GestureEvent* event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        EXPECT_NEAR(event->GetAngle(), expected, EPSILON) <<
            "Input value is: " << input << ", method: SetAngle";
    }
}

/**
 * @tc.name: getSpeedTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventAccessorTest, getSpeedTest, TestSize.Level1)
{
    for (auto value : AccessorTestFixtures::testFixtureFloatValues) {
        GestureEvent* event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        event->SetSpeed(value);
        auto arkRes = accessor_->getSpeed(peer_);
        EXPECT_FLOAT_EQ(Converter::Convert<float>(arkRes), value) <<
            "Input value is: " << value << ", method: GetSpeed";
    }
}

/**
 * @tc.name: setSpeedTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventAccessorTest, setSpeedTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureNumberValues) {
        accessor_->setSpeed(peer_, &value);
        GestureEvent* event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        EXPECT_NEAR(event->GetSpeed(), expected, EPSILON) <<
            "Input value is: " << input << ", method: SetSpeed";
    }
}

/**
 * @tc.name: getScaleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventAccessorTest, getScaleTest, TestSize.Level1)
{
    for (auto value : AccessorTestFixtures::testFixtureFloatValues) {
        GestureEvent* event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        event->SetScale(value);
        auto arkRes = accessor_->getScale(peer_);
        EXPECT_FLOAT_EQ(Converter::Convert<float>(arkRes), value) <<
            "Input value is: " << value << ", method: GetScale";
    }
}

/**
 * @tc.name: setScaleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventAccessorTest, setScaleTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureNumberValues) {
        accessor_->setScale(peer_, &value);
        GestureEvent* event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        EXPECT_NEAR(event->GetScale(), expected, EPSILON) <<
            "Input value is: " << input << ", method: SetScale";
    }
}

/**
 * @tc.name: getPinchCenterXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventAccessorTest, getPinchCenterXTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureFloatFloat_half_Values) {
        GestureEvent* event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        event->SetPinchCenter(Offset(value, 0.));
        auto arkRes = accessor_->getPinchCenterX(peer_);
        EXPECT_FLOAT_EQ(Converter::Convert<float>(arkRes), expected) <<
            "Input value is: " << input << ", method: GetPinchCenterX";
    }
}

/**
 * @tc.name: setPinchCenterXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventAccessorTest, setPinchCenterXTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureNumber_2x_Values) {
        accessor_->setPinchCenterX(peer_, &value);
        GestureEvent* event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        EXPECT_NEAR(event->GetPinchCenter().GetX(), expected, EPSILON) <<
            "Input value is: " << input << ", method: SetPinchCenterX";
    }
}

/**
 * @tc.name: getPinchCenterYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventAccessorTest, getPinchCenterYTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureFloatFloat_half_Values) {
        GestureEvent* event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        event->SetPinchCenter(Offset(0., value));
        auto arkRes = accessor_->getPinchCenterY(peer_);
        EXPECT_FLOAT_EQ(Converter::Convert<float>(arkRes), expected) <<
            "Input value is: " << input << ", method: GetPinchCenterY";
    }
}

/**
 * @tc.name: setPinchCenterYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventAccessorTest, setPinchCenterYTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureNumber_2x_Values) {
        accessor_->setPinchCenterY(peer_, &value);
        GestureEvent* event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        EXPECT_NEAR(event->GetPinchCenter().GetY(), expected, EPSILON) <<
            "Input value is: " << input << ", method: SetPinchCenterY";
    }
}

/**
 * @tc.name: getVelocityXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventAccessorTest, getVelocityXTest, TestSize.Level1)
{
    const double velocityY = 2.3;
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureFloatFloat_half_Values) {
        GestureEvent* event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        auto offsetPerSec = Offset(value, velocityY);
        event->SetVelocity(Velocity(offsetPerSec));
        auto arkRes = accessor_->getVelocityX(peer_);
        EXPECT_FLOAT_EQ(Converter::Convert<float>(arkRes), expected) <<
            "Input value is: " << input << ", method: GetVelocityX";
    }
}

/**
 * @tc.name: setVelocityXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventAccessorTest, setVelocityXTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureNumber_2x_Values) {
        accessor_->setVelocityX(peer_, &value);
        GestureEvent* event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        EXPECT_NEAR(event->GetVelocity().GetVelocityX(), expected, EPSILON) <<
            "Input value is: " << input << ", method: SetVelocityX";
    }
}

/**
 * @tc.name: getVelocityYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventAccessorTest, getVelocityYTest, TestSize.Level1)
{
    const double velocityX = 2.3;
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureFloatFloat_half_Values) {
        GestureEvent* event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        auto offsetPerSec = Offset(velocityX, value);
        event->SetVelocity(Velocity(offsetPerSec));
        auto arkRes = accessor_->getVelocityY(peer_);
        EXPECT_FLOAT_EQ(Converter::Convert<float>(arkRes), expected) <<
            "Input value is: " << input << ", method: GetVelocityY";
    }
}

/**
 * @tc.name: setVelocityYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventAccessorTest, setVelocityYTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureNumber_2x_Values) {
        accessor_->setVelocityY(peer_, &value);
        GestureEvent* event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        EXPECT_NEAR(event->GetVelocity().GetVelocityY(), expected, EPSILON) <<
            "Input value is: " << input << ", method: SetVelocityY";
    }
}

/**
 * @tc.name: getVelocityTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventAccessorTest, getVelocityTest, TestSize.Level1)
{
    for (auto& [input, velocityX, velocityY, expected] :
        AccessorTestFixtures::testFixtureVelocityFloat_half_Values) {
        GestureEvent* event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        auto offsetPerSec = Offset(velocityX, velocityY);
        event->SetVelocity(Velocity(offsetPerSec));
        auto arkRes = accessor_->getVelocity(peer_);
        EXPECT_FLOAT_EQ(Converter::Convert<float>(arkRes), expected) <<
            "Input value is: " << input << ", method: GetVelocity";
    }
}

/**
 * @tc.name: setFingerListTestEmpty
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventAccessorTest, setFingerListTestEmpty, TestSize.Level1)
{
    std::vector<Ark_FingerInfo> emptyVec;
    auto arrayHolder = Converter::ArkArrayHolder<Array_FingerInfo>(emptyVec);
    auto arkArray = arrayHolder.ArkValue();
    accessor_->setFingerList(peer_, &arkArray);
    GestureEvent* event = peer_->GetEventInfo();
    ASSERT_NE(event, nullptr);
    std::list<FingerInfo> res = event->GetFingerList();
    EXPECT_TRUE(res.empty());
}

/**
 * @tc.name: setFingerListTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventAccessorTest, setFingerListTest, TestSize.Level1)
{
    Ark_FingerInfo info1 = {
        .id = Converter::ArkValue<Ark_Int32>(12),
        .globalX = Converter::ArkValue<Ark_Float64>(150.5),
        .globalY = Converter::ArkValue<Ark_Float64>(170.25),
        .localX = Converter::ArkValue<Ark_Float64>(40.5),
        .localY = Converter::ArkValue<Ark_Float64>(80.25),
        .displayX = Converter::ArkValue<Ark_Float64>(200.25),
        .displayY = Converter::ArkValue<Ark_Float64>(300.75),
    };
    Ark_FingerInfo info2 = {
        .id = Converter::ArkValue<Ark_Int32>(98),
        .globalX = Converter::ArkValue<Ark_Float64>(450.10),
        .globalY = Converter::ArkValue<Ark_Float64>(670.0),
        .localX = Converter::ArkValue<Ark_Float64>(140.65),
        .localY = Converter::ArkValue<Ark_Float64>(180.35),
        .displayX = Converter::ArkValue<Ark_Float64>(800.40),
        .displayY = Converter::ArkValue<Ark_Float64>(900.82),
    };
    std::vector<Ark_FingerInfo> vec = { info1, info2 };
    auto arrayHolder = Converter::ArkArrayHolder<Array_FingerInfo>(vec);
    auto arkArray = arrayHolder.ArkValue();
    accessor_->setFingerList(peer_, &arkArray);
    GestureEvent* event = peer_->GetEventInfo();
    ASSERT_NE(event, nullptr);
    std::list<FingerInfo> res = event->GetFingerList();

    const size_t expectedSize = 2;
    ASSERT_EQ(res.size(), expectedSize);

    const std::vector<int32_t> expectedId = { 12, 98 };
    const std::vector<double> expectedGlobalX = { 150.5, 450.10 };
    const std::vector<double> expectedGlobalY = { 170.25, 670.0 };
    const std::vector<double> expectedLocalX = { 40.5, 140.65 };
    const std::vector<double> expectedLocalY = { 80.25, 180.35 };
    const std::vector<double> expectedScreenX = { 200.25, 800.40 };
    const std::vector<double> expectedScreenY = { 300.75, 900.82 };

    int i = 0;
    for (auto iter = res.begin(); iter != res.end(); iter++) {
        EXPECT_EQ(iter->fingerId_, expectedId[i]);
        EXPECT_NEAR(iter->globalLocation_.GetX(), expectedGlobalX[i], EPSILON);
        EXPECT_NEAR(iter->globalLocation_.GetY(), expectedGlobalY[i], EPSILON);
        EXPECT_NEAR(iter->localLocation_.GetX(), expectedLocalX[i], EPSILON);
        EXPECT_NEAR(iter->localLocation_.GetY(), expectedLocalY[i], EPSILON);
        EXPECT_NEAR(iter->screenLocation_.GetX(), expectedScreenX[i], EPSILON);
        EXPECT_NEAR(iter->screenLocation_.GetY(), expectedScreenY[i], EPSILON);
        i++;
    }
}
/**
 * @tc.name: getFingerListTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventAccessorTest, getFingerListTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getFingerList, nullptr);
    auto eventInfo = peer_->GetEventInfo();
    ASSERT_NE(eventInfo, nullptr);
    std::list<FingerInfo> fingerInfo;
    const int fingerId = 0;
    const float expectedWindowX = 2.5f;
    const float expectedWindowY = 3.7f;
    Offset globalOffset(expectedWindowX, expectedWindowY);
    const float expectedX = 4.5f;
    const float expectedY = 5.7f;
    Offset localOffset(expectedX, expectedY);
    const float expectedDisplayX = 1.5f;
    const float expectedDisplayY = 1.7f;
    Offset screenOffset(expectedDisplayX, expectedDisplayY);
    auto item = FingerInfo {
        .fingerId_ = fingerId,
        .globalLocation_ = globalOffset,
        .localLocation_ = localOffset,
        .screenLocation_ = screenOffset,
    };
    fingerInfo.push_back(item);
    eventInfo->SetFingerList(fingerInfo);
    Array_FingerInfo fingerInfoArr = accessor_->getFingerList(peer_);
    ASSERT_EQ(static_cast<int32_t>(fingerInfoArr.length), 1);
    ASSERT_NE(fingerInfoArr.array, nullptr);
    EXPECT_NEAR(Converter::Convert<float>(fingerInfoArr.array->displayX),
        PipelineBase::Px2VpWithCurrentDensity(expectedDisplayX), EPSILON);
    EXPECT_NEAR(Converter::Convert<float>(fingerInfoArr.array->displayY),
        PipelineBase::Px2VpWithCurrentDensity(expectedDisplayY), EPSILON);
    EXPECT_NEAR(Converter::Convert<float>(fingerInfoArr.array->globalX),
        PipelineBase::Px2VpWithCurrentDensity(expectedWindowX), EPSILON);
    EXPECT_NEAR(Converter::Convert<float>(fingerInfoArr.array->globalY),
        PipelineBase::Px2VpWithCurrentDensity(expectedWindowY), EPSILON);
    EXPECT_NEAR(Converter::Convert<float>(fingerInfoArr.array->localX),
        PipelineBase::Px2VpWithCurrentDensity(expectedX), EPSILON);
    EXPECT_NEAR(Converter::Convert<float>(fingerInfoArr.array->localY),
        PipelineBase::Px2VpWithCurrentDensity(expectedY), EPSILON);
    EXPECT_EQ(Converter::Convert<int32_t>(fingerInfoArr.array->id), fingerId);
}
}