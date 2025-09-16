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
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/tap_recognizer_peer.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class TapRecognizerAccessorTest : public AccessorTestBase<GENERATED_ArkUITapRecognizerAccessor,
    &GENERATED_ArkUIAccessors::getTapRecognizerAccessor, TapRecognizerPeer> {};

/**
 * @tc.name: CreatePeerTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TapRecognizerAccessorTest, CreatePeerTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->construct, nullptr);
    ASSERT_NE(peer_, nullptr);
}

/**
 * @tc.name: GetTapCountTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TapRecognizerAccessorTest, GetTapCountTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getTapCount, nullptr);
    ASSERT_NE(peer_, nullptr);

    const int32_t fingers = 2;
    const int32_t expectedCount = 3;
    const double distanceThreshold = 4.0;
    const bool isLimitFingerCount = false;
    auto mockGestureRecognizer_ = AceType::MakeRefPtr<NG::ClickRecognizer>(fingers, expectedCount,
        distanceThreshold, isLimitFingerCount);
    peer_->Update(mockGestureRecognizer_);

    auto resultCount = Converter::Convert<int32_t>(accessor_->getTapCount(peer_));
    EXPECT_EQ(resultCount, expectedCount) << "Passed value is: " << expectedCount;
}
} // namespace OHOS::Ace::NG
