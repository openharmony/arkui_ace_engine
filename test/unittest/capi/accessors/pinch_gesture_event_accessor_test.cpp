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
#include "test/unittest/capi/accessors/accessor_test_fixtures.h"
#include "core/interfaces/native/implementation/pinch_gesture_event_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class PinchGestureEventAccessorTest
    : public AccessorTestBase<GENERATED_ArkUIPinchGestureEventAccessor,
          &GENERATED_ArkUIAccessors::getPinchGestureEventAccessor, PinchGestureEventPeer> {
public:
    void SetUp() override
    {
        AccessorTestBase::SetUp();
        const double testDensity = 2.0;
        MockPipelineContext::GetCurrent()->SetDensity(testDensity);
        auto eventInfo_ = std::make_shared<Ace::PinchGestureEvent>();
        peer_->SetEventInfo(eventInfo_);
    }
};

namespace {
    const double EPSILON = 0.001;
}

/**
 * @tc.name: getScaleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PinchGestureEventAccessorTest, getScaleTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureDoubleArkInt32Values) {
        auto event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        event->SetScale(value);
        auto arkRes = Converter::Convert<float>(accessor_->getScale(peer_));
        EXPECT_EQ(arkRes, expected) <<
            "Input value is: " << input << ", method: GetScale";
    }
}

/**
 * @tc.name: setScaleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PinchGestureEventAccessorTest, setScaleTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureNumberValues) {
        accessor_->setScale(peer_, &value);
        auto event = peer_->GetEventInfo();
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
HWTEST_F(PinchGestureEventAccessorTest, getPinchCenterXTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureDoubleArkInt32_half_Values) {
        auto event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        event->SetPinchCenter(Offset(value, 0.));
        auto arkRes = Converter::Convert<float>(accessor_->getPinchCenterX(peer_));
        EXPECT_EQ(arkRes, expected) <<
            "Input value is: " << input << ", method: GetPinchCenterX";
    }
}

/**
 * @tc.name: setPinchCenterXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PinchGestureEventAccessorTest, setPinchCenterXTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureNumber_2x_Values) {
        accessor_->setPinchCenterX(peer_, &value);
        auto event = peer_->GetEventInfo();
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
HWTEST_F(PinchGestureEventAccessorTest, getPinchCenterYTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureDoubleArkInt32_half_Values) {
        auto event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        event->SetPinchCenter(Offset(0., value));
        auto arkRes = Converter::Convert<float>(accessor_->getPinchCenterY(peer_));
        EXPECT_EQ(arkRes, expected) <<
            "Input value is: " << input << ", method: GetPinchCenterY";
    }
}

/**
 * @tc.name: setPinchCenterYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PinchGestureEventAccessorTest, setPinchCenterYTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureNumber_2x_Values) {
        accessor_->setPinchCenterY(peer_, &value);
        auto event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        EXPECT_NEAR(event->GetPinchCenter().GetY(), expected, EPSILON) <<
            "Input value is: " << input << ", method: SetPinchCenterY";
    }
}
}