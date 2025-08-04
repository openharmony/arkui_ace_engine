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
#include "core/interfaces/native/implementation/pinch_recognizer_peer.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
const double FLT_PRECISION = 0.001;
// test plan
const std::vector<double> doubleNumberTestPlan = { 100.0, 0.0, -100, 12.34, -56.73 };

} // namespace
class PinchRecognizerAccessorTest : public AccessorTestBase<GENERATED_ArkUIPinchRecognizerAccessor,
    &GENERATED_ArkUIAccessors::getPinchRecognizerAccessor, PinchRecognizerPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        mockGestureRecognizer_ = AceType::MakeRefPtr<NG::PinchRecognizer>(DEFAULT_FINGERS, DEFAULT_DISTANCE);
        ASSERT_NE(mockGestureRecognizer_, nullptr);
        peer_->Update(mockGestureRecognizer_);
    }

    void TearDown() override
    {
        AccessorTestBase::TearDown();
        mockGestureRecognizer_ = nullptr;
    }

    RefPtr<NG::PinchRecognizer> mockGestureRecognizer_ = nullptr;
};

/**
 * @tc.name: ctorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PinchRecognizerAccessorTest, ctorTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->construct, nullptr);
    ASSERT_NE(peer_, nullptr);
}

/**
 * @tc.name: getDistanceTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PinchRecognizerAccessorTest, getDistanceTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getDistance, nullptr);
    ASSERT_NE(peer_, nullptr);

    // default
    auto result = accessor_->getDistance(peer_);
    auto actual = Converter::Convert<double>(result);
    EXPECT_NEAR(actual, DEFAULT_DISTANCE, FLT_PRECISION);

    // update
    for (const auto& expected : doubleNumberTestPlan) {
        mockGestureRecognizer_->SetDistance(expected);
        peer_->Update(mockGestureRecognizer_);
        auto result = accessor_->getDistance(peer_);
        auto actual = Converter::Convert<double>(result);
        EXPECT_NEAR(actual, expected, FLT_PRECISION);
    }
}
} // namespace OHOS::Ace::NG