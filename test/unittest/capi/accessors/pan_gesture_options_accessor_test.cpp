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

#include "gmock/gmock.h"

#include "accessor_test_base.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"

#include "core/interfaces/native/implementation/pan_gesture_options_peer.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class PanGestureOptionsAccessorTest : public AccessorTestCtorBase<GENERATED_ArkUIPanGestureOptionsAccessor,
    &GENERATED_ArkUIAccessors::getPanGestureOptionsAccessor, PanGestureOptionsPeer> {
public:
    void *CreatePeerInstance() override
    {
        const Ark_PanGestureHandlerOptions ARK_DEFAULT_SETTINGS = {
            .fingers = Converter::ArkValue<Opt_Number>(1),
            .direction = Converter::ArkValue<Opt_PanDirection>(ARK_PAN_DIRECTION_ALL),
            .distance = Converter::ArkValue<Opt_Number>(5),
        };
        const Opt_PanGestureHandlerOptions DEFAULT_SETTINGS =
            Converter::ArkValue<Opt_PanGestureHandlerOptions>(ARK_DEFAULT_SETTINGS);

        return accessor_->construct(&DEFAULT_SETTINGS);
    }
};

typedef std::pair<PanDirection, Ark_PanDirection> SetDirectionTestStep;
const std::vector<SetDirectionTestStep> SET_DIRECTION_TEST_PLAN = {
    { { .type = PanDirection::NONE }, ARK_PAN_DIRECTION_NONE },
    { { .type = PanDirection::LEFT }, ARK_PAN_DIRECTION_LEFT },
    { { .type = PanDirection::RIGHT }, ARK_PAN_DIRECTION_RIGHT },
    { { .type = PanDirection::HORIZONTAL }, ARK_PAN_DIRECTION_HORIZONTAL },
    { { .type = PanDirection::UP }, ARK_PAN_DIRECTION_UP },
    { { .type = PanDirection::DOWN }, ARK_PAN_DIRECTION_DOWN },
    { { .type = PanDirection::VERTICAL }, ARK_PAN_DIRECTION_VERTICAL },
    { { .type = PanDirection::ALL }, ARK_PAN_DIRECTION_ALL },
};

/**
 * @tc.name: setDirectionTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PanGestureOptionsAccessorTest, setDirectionTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setDirection, nullptr);

    for (auto& [expected, actual] : SET_DIRECTION_TEST_PLAN) {
        accessor_->setDirection(peer_, actual);
        EXPECT_EQ(peer_->handler->GetDirection().type, expected.type);
    }
}

constexpr Ark_PanDirection TEST_DEFAULT_DIRECTION = ARK_PAN_DIRECTION_ALL;

/**
 * @tc.name: getDirectionTestDefault
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PanGestureOptionsAccessorTest, getDirectionTestDefault, TestSize.Level1)
{
    ASSERT_NE(accessor_->getDirection, nullptr);
    EXPECT_EQ(accessor_->getDirection(peer_), TEST_DEFAULT_DIRECTION);
}

/**
 * @tc.name: getDirectionTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PanGestureOptionsAccessorTest, getDirectionTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getDirection, nullptr);

    for (auto& [actual, expected] : SET_DIRECTION_TEST_PLAN) {
        peer_->handler->SetDirection(actual);
        EXPECT_EQ(accessor_->getDirection(peer_), expected);
    }
}

typedef std::pair<double, Ark_Number> SetDistanceTestStep;
const std::vector<SetDistanceTestStep> SET_DISTANCE_TEST_PLAN = {
    { 0, Converter::ArkValue<Ark_Number>(0) },
    { 5, Converter::ArkValue<Ark_Number>(5) },
    { 10, Converter::ArkValue<Ark_Number>(10) },
    { 20, Converter::ArkValue<Ark_Number>(20) },
};

/**
 * @tc.name: setDistanceTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PanGestureOptionsAccessorTest, setDistanceTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setDistance, nullptr);

    for (auto& [expected, actual] : SET_DISTANCE_TEST_PLAN) {
        accessor_->setDistance(peer_, &actual);
        EXPECT_EQ(peer_->handler->GetDistance(), expected);
    }
}

typedef std::pair<int32_t, Ark_Number> SetFingersTestStep;
const std::vector<SetFingersTestStep> SET_FINGERS_TEST_PLAN = {
    { 1, Converter::ArkValue<Ark_Number>(0) },
    { 1, Converter::ArkValue<Ark_Number>(1) },
    { 2, Converter::ArkValue<Ark_Number>(2) },
    { 5, Converter::ArkValue<Ark_Number>(5) },
};

/**
 * @tc.name: setFingersTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PanGestureOptionsAccessorTest, setFingersTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setFingers, nullptr);

    for (auto& [expected, actual] : SET_FINGERS_TEST_PLAN) {
        accessor_->setFingers(peer_, &actual);
        EXPECT_EQ(peer_->handler->GetFingers(), expected);
    }
}

} // namespace OHOS::Ace::NG
