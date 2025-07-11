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
#include "core/interfaces/native/implementation/rotation_gesture_event_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "test/unittest/capi/accessors/accessor_test_fixtures.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
    const double EPSILON = 0.001; // defined epsilon doesn't enough
}

class RotationGestureEventAccessorTest
    : public AccessorTestBase<GENERATED_ArkUIRotationGestureEventAccessor,
        &GENERATED_ArkUIAccessors::getRotationGestureEventAccessor, RotationGestureEventPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        const double testDensity = 2.0;
        MockPipelineContext::GetCurrent()->SetDensity(testDensity);
        eventInfo_ = std::make_shared<RotationGestureEvent>();
        peer_->SetEventInfo(eventInfo_);
    }
    std::shared_ptr<RotationGestureEvent> eventInfo_;
};

/**
 * @tc.name: GetAngleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RotationGestureEventAccessorTest, GetAngleTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureNumberFloatAnythingValidValues) {
        eventInfo_->SetAngle(value);
        auto arkRes = Converter::Convert<float>(accessor_->getAngle(peer_));
        EXPECT_EQ(arkRes, Converter::Convert<float>(expected)) <<
            "Input value is: " << input << ", method: GetAngle";
    }
}

/**
 * @tc.name: SetAngleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RotationGestureEventAccessorTest, SetAngleTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureNumberValues) {
        accessor_->setAngle(peer_, &value);
        EXPECT_NEAR(eventInfo_->GetAngle(), expected, EPSILON) <<
            "Input value is: " << input << ", method: SetAngle";
    }
}

}