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
#include "core/interfaces/native/implementation/pan_gesture_event_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "test/unittest/capi/accessors/accessor_test_fixtures.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
    const double TEST_DENSITY = 2.0;
    const double EPSILON = 0.001;
}

class PanGestureEventAccessorTest
    : public AccessorTestBase<GENERATED_ArkUIPanGestureEventAccessor,
        &GENERATED_ArkUIAccessors::getPanGestureEventAccessor, PanGestureEventPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        MockPipelineContext::GetCurrent()->SetDensity(TEST_DENSITY);
        eventInfo_ = std::make_shared<PanGestureEvent>();
        peer_->SetEventInfo(eventInfo_);
    }

private:
    std::shared_ptr<PanGestureEvent> eventInfo_;
};

/**
 * @tc.name: GetOffsetXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PanGestureEventAccessorTest, GetOffsetXTest, TestSize.Level1)
{
    PipelineBase::GetCurrentDensity();
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureNumberDoubleValues) {
        auto event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        event->SetOffsetX(Converter::Convert<float>(value) * TEST_DENSITY);
        auto arkRes = Converter::Convert<double>(accessor_->getOffsetX(peer_));
        EXPECT_NEAR(arkRes, expected, EPSILON) <<
            "Input value is: " << input << ", method: GetOffsetX";
    }
}

/**
 * @tc.name: SetOffsetXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PanGestureEventAccessorTest, SetOffsetXTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureNumber_2x_Values) {
        accessor_->setOffsetX(peer_, &value);
        auto event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        EXPECT_NEAR(event->GetOffsetX(), expected, EPSILON) <<
            "Input value is: " << input << ", method: SetOffsetX";
    }
}

/**
 * @tc.name: GetOffsetYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PanGestureEventAccessorTest, GetOffsetYTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureNumberDoubleValues) {
        auto event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        event->SetOffsetY(Converter::Convert<float>(value) * TEST_DENSITY);
        auto arkRes = Converter::Convert<double>(accessor_->getOffsetY(peer_));
        EXPECT_NEAR(arkRes, expected, EPSILON) <<
            "Input value is: " << input << ", method: GetOffsetY";
    }
}

/**
 * @tc.name: SetOffsetYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PanGestureEventAccessorTest, SetOffsetYTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureNumber_2x_Values) {
        accessor_->setOffsetY(peer_, &value);
        auto event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        EXPECT_NEAR(event->GetOffsetY(), expected, EPSILON) <<
            "Input value is: " << input << ", method: SetOffsetY";
    }
}

/**
 * @tc.name: GetVelocityXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PanGestureEventAccessorTest, GetVelocityXTest, TestSize.Level1)
{
    const double velocityY = 2.3;
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureNumberDoubleValues) {
        auto event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        auto offsetPerSec = Offset(Converter::Convert<float>(value) * TEST_DENSITY, velocityY);
        event->SetVelocity(Velocity(offsetPerSec));
        auto arkRes = Converter::Convert<double>(accessor_->getVelocityX(peer_));
        EXPECT_NEAR(arkRes, expected, EPSILON) <<
            "Input value is: " << input << ", method: GetVelocityX";
    }
}

/**
 * @tc.name: SetVelocityXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PanGestureEventAccessorTest, SetVelocityXTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureNumber_2x_Values) {
        accessor_->setVelocityX(peer_, &value);
        auto event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        EXPECT_NEAR(event->GetVelocity().GetVelocityX(), expected, EPSILON) <<
            "Input value is: " << input << ", method: SetVelocityX";
    }
}

/**
 * @tc.name: GetVelocityYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PanGestureEventAccessorTest, GetVelocityYTest, TestSize.Level1)
{
    const double velocityX = 2.3;
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureNumberDoubleValues) {
        auto event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        auto offsetPerSec = Offset(velocityX, Converter::Convert<float>(value) * TEST_DENSITY);
        event->SetVelocity(Velocity(offsetPerSec));
        auto arkRes = Converter::Convert<double>(accessor_->getVelocityY(peer_));
        EXPECT_NEAR(arkRes, expected, EPSILON) <<
            "Input value is: " << input << ", method: GetVelocityY";
    }
}

/**
 * @tc.name: SetVelocityYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PanGestureEventAccessorTest, SetVelocityYTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureNumber_2x_Values) {
        accessor_->setVelocityY(peer_, &value);
        auto event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        EXPECT_NEAR(event->GetVelocity().GetVelocityY(), expected, EPSILON) <<
            "Input value is: " << input << ", method: SetVelocityY";
    }
}

/**
 * @tc.name: GetVelocityTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PanGestureEventAccessorTest, GetVelocityTest, TestSize.Level1)
{
    for (auto& [input, velocityX, velocityY, expected] : AccessorTestFixtures::testFixtureVelocity_half_Values) {
        auto event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        auto offsetPerSec = Offset(velocityX, velocityY);
        event->SetVelocity(Velocity(offsetPerSec));
        auto arkRes = Converter::Convert<float>(accessor_->getVelocity(peer_));
        EXPECT_EQ(arkRes, expected) <<
            "Input value is: " << input << ", method: GetVelocity";
    }
}

/**
 * @tc.name: SetVelocityYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PanGestureEventAccessorTest, SetVelocityTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureNumber_2x_Values) {
        accessor_->setVelocity(peer_, &value);
        auto event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        EXPECT_NEAR(event->GetVelocity().GetVelocityX(), expected, EPSILON) <<
            "Input X value is: " << input << ", method: SetVelocity";
        EXPECT_NEAR(event->GetVelocity().GetVelocityY(), expected, EPSILON) <<
            "Input Y value is: " << input << ", method: SetVelocity";
    }
}
}
