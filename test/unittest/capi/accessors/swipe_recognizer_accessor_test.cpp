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

#include "gmock/gmock.h"

#include "accessor_test_base.h"
#include "core/interfaces/native/implementation/swipe_recognizer_peer.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
const int32_t INVALID_DIRECTION = -1;
const double FLT_PRECISION = 0.001;
// test plan
const std::vector<double> doubleNumberTestPlan = { 100.0, 0.0, -100, 12.34, -56.73 };

const std::vector<SwipeDirection> swipeDirectionTestPlan = {
    SwipeDirection { .type = SwipeDirection::NONE },
    SwipeDirection { .type = SwipeDirection::HORIZONTAL },
    SwipeDirection { .type = SwipeDirection::VERTICAL },
    SwipeDirection { .type = SwipeDirection::ALL },
    SwipeDirection { .type = -1 },
};
} // namespace

class SwipeRecognizerAccessorTest : public AccessorTestBase<GENERATED_ArkUISwipeRecognizerAccessor,
    &GENERATED_ArkUIAccessors::getSwipeRecognizerAccessor, SwipeRecognizerPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        mockGestureRecognizer_ =
            AceType::MakeRefPtr<NG::SwipeRecognizer>(DEFAULT_FINGERS, DEFAULT_DIRECT, DEFAULT_SPEED);
        ASSERT_NE(mockGestureRecognizer_, nullptr);
        peer_->Update(mockGestureRecognizer_);
    }

    void TearDown() override
    {
        AccessorTestBase::TearDown();
        mockGestureRecognizer_ = nullptr;
    }

    RefPtr<NG::SwipeRecognizer> mockGestureRecognizer_ = nullptr;
};

/**
 * @tc.name: ctorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SwipeRecognizerAccessorTest, ctorTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->construct, nullptr);
    ASSERT_NE(peer_, nullptr);
}

/**
 * @tc.name: getVelocityThresholdTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SwipeRecognizerAccessorTest, getVelocityThresholdTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getVelocityThreshold, nullptr);
    ASSERT_NE(peer_, nullptr);

    // default
    auto result = accessor_->getVelocityThreshold(peer_);
    auto actual = Converter::Convert<double>(result);
    EXPECT_NEAR(actual, DEFAULT_SPEED, FLT_PRECISION);

    // update
    for (const auto& expected : doubleNumberTestPlan) {
        mockGestureRecognizer_->SetSpeed(expected);
        peer_->Update(mockGestureRecognizer_);
        auto result = accessor_->getVelocityThreshold(peer_);
        auto actual = Converter::Convert<double>(result);
        EXPECT_NEAR(actual, expected, FLT_PRECISION);
    }
}

/**
 * @tc.name: getDirectionTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SwipeRecognizerAccessorTest, getDirectionTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getDirection, nullptr);
    ASSERT_NE(peer_, nullptr);

    // default
    auto result = accessor_->getDirection(peer_);
    auto actual = Converter::OptConvert<SwipeDirection>(result);
    ASSERT_NE(actual, std::nullopt);
    EXPECT_EQ(actual->type, DEFAULT_DIRECT.type);

    // update
    for (const auto& expected : swipeDirectionTestPlan) {
        mockGestureRecognizer_->SetDirection(expected);
        peer_->Update(mockGestureRecognizer_);
        auto result = accessor_->getDirection(peer_);
        auto actual = Converter::OptConvert<SwipeDirection>(result);

        if (expected.type == INVALID_DIRECTION) {
            EXPECT_EQ(actual, std::nullopt);
        } else {
            ASSERT_NE(actual, std::nullopt);
            EXPECT_EQ(actual->type, expected.type);
        }
    }
}
} // namespace OHOS::Ace::NG