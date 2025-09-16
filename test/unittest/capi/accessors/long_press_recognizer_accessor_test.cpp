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
#include "core/interfaces/native/implementation/long_press_recognizer_peer.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
const auto EXPECTED_TRUE = true;
const auto EXPECTED_FALSE = false;
// test plan
const std::vector<int32_t> intNumberTestPlan = { 100, 0, -100, 12, -56 };
} // namespace
class LongPressRecognizerAccessorTest : public AccessorTestBase<GENERATED_ArkUILongPressRecognizerAccessor,
    &GENERATED_ArkUIAccessors::getLongPressRecognizerAccessor, LongPressRecognizerPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        mockGestureRecognizer_ = AceType::MakeRefPtr<NG::LongPressRecognizer>(MockPipelineContext::GetCurrent());
        ASSERT_NE(mockGestureRecognizer_, nullptr);
        peer_->Update(mockGestureRecognizer_);
    }

    void TearDown() override
    {
        AccessorTestBase::TearDown();
        mockGestureRecognizer_ = nullptr;
    }

    RefPtr<NG::LongPressRecognizer> mockGestureRecognizer_ = nullptr;
};

/**
 * @tc.name: ctorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerAccessorTest, ctorTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->construct, nullptr);
    ASSERT_NE(peer_, nullptr);
}

/**
 * @tc.name: isRepeatTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerAccessorTest, isRepeatTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->isRepeat, nullptr);
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(mockGestureRecognizer_, nullptr);

    // default
    auto result = accessor_->isRepeat(peer_);
    auto repeat = Converter::Convert<bool>(result);
    EXPECT_FALSE(repeat);

    // direct
    peer_->SetRepeat(EXPECTED_TRUE);
    result = accessor_->isRepeat(peer_);
    auto actual = Converter::Convert<bool>(result);
    EXPECT_EQ(actual, EXPECTED_TRUE);

    peer_->SetRepeat(EXPECTED_FALSE);
    result = accessor_->isRepeat(peer_);
    actual = Converter::Convert<bool>(result);
    EXPECT_EQ(actual, EXPECTED_FALSE);

    // update
    mockGestureRecognizer_->SetIsRepeat(EXPECTED_TRUE);
    peer_->Update(mockGestureRecognizer_);
    result = accessor_->isRepeat(peer_);
    actual = Converter::Convert<bool>(result);
    EXPECT_EQ(actual, EXPECTED_TRUE);

    mockGestureRecognizer_->SetIsRepeat(EXPECTED_FALSE);
    peer_->Update(mockGestureRecognizer_);
    result = accessor_->isRepeat(peer_);
    actual = Converter::Convert<bool>(result);
    EXPECT_EQ(actual, EXPECTED_FALSE);
}

/**
 * @tc.name: getDurationTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LongPressRecognizerAccessorTest, DISABLED_getDurationTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getDuration, nullptr);
    ASSERT_NE(peer_, nullptr);

    // default
    auto result = accessor_->getDuration(peer_);
    auto actual = Converter::Convert<int32_t>(result);
    EXPECT_EQ(actual, ::DEFAULT_LONG_PRESS_DURATION);

    // update
    for (const auto& expected : intNumberTestPlan) {
        mockGestureRecognizer_->SetDuration(expected);
        peer_->Update(mockGestureRecognizer_);
        auto result = accessor_->getDuration(peer_);
        auto actual = Converter::Convert<int32_t>(result);
        EXPECT_EQ(actual, expected);
    }
}
} // namespace OHOS::Ace::NG