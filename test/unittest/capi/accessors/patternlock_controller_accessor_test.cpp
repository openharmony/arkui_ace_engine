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
#include "core/components_v2/pattern_lock/pattern_lock_controller.h"
#include "core/interfaces/native/implementation/pattern_lock_controller_accessor_peer_impl.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "gmock/gmock.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
class StubPatternLockController : public V2::PatternLockController {
public:
    StubPatternLockController()
    {
        SetResetImpl(std::bind(&StubPatternLockController::ResetTest, this));
        SetChallengeResultImpl(std::bind(&StubPatternLockController::SetChallengeResultTest, this,
            std::placeholders::_1));
    }
    ~StubPatternLockController() override = default;
    virtual void ResetTest() {}
    virtual void SetChallengeResultTest(V2::PatternLockChallengeResult) {}
};
class MockPatternLockController : public StubPatternLockController {
public:
    MockPatternLockController() = default;
    ~MockPatternLockController() override = default;
    MOCK_METHOD(void, SetChallengeResultTest, (V2::PatternLockChallengeResult));
    MOCK_METHOD(void, ResetTest, ());
};
} // namespace

class PatternLockControllerAccessorTest : public AccessorTestBase<GENERATED_ArkUIPatternLockControllerAccessor,
    &GENERATED_ArkUIAccessors::getPatternLockControllerAccessor, PatternLockControllerPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        mockPatternLockController_ = new MockPatternLockController();
        mockPatternLockControllerKeeper_ = AceType::Claim(mockPatternLockController_);
        ASSERT_NE(mockPatternLockControllerKeeper_, nullptr);
        auto peerImpl = reinterpret_cast<GeneratedModifier::PatternLockControllerPeerImpl*>(peer_);
        ASSERT_NE(peerImpl, nullptr);
        peerImpl->SetHandler(mockPatternLockControllerKeeper_);
        ASSERT_NE(mockPatternLockController_, nullptr);
    }

    void TearDown() override
    {
        AccessorTestBase::TearDown();
        mockPatternLockControllerKeeper_ = nullptr;
        mockPatternLockController_ = nullptr;
    }

    MockPatternLockController *mockPatternLockController_ = nullptr;
    RefPtr<MockPatternLockController> mockPatternLockControllerKeeper_ = nullptr;
};

/**
 * @tc.name: resetTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockControllerAccessorTest, resetTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->reset, nullptr);
    EXPECT_CALL(*mockPatternLockController_, ResetTest()).Times(3);
    accessor_->reset(peer_);
    accessor_->reset(peer_);
    accessor_->reset(peer_);
}

/**
 * @tc.name: SetChallengeResult
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockControllerAccessorTest, SetChallengeResult, TestSize.Level1)
{
    auto resCorrect = V2::PatternLockChallengeResult::CORRECT;
    auto resWrong = V2::PatternLockChallengeResult::WRONG;
    auto arkResultCorrect = Ark_PatternLockChallengeResult::ARK_PATTERN_LOCK_CHALLENGE_RESULT_CORRECT;
    auto arkResultWrong = Ark_PatternLockChallengeResult::ARK_PATTERN_LOCK_CHALLENGE_RESULT_WRONG;
    ASSERT_NE(accessor_->setChallengeResult, nullptr);

    EXPECT_CALL(*mockPatternLockController_, SetChallengeResultTest(resCorrect)).Times(1);
    accessor_->setChallengeResult(peer_, arkResultCorrect);
    EXPECT_CALL(*mockPatternLockController_, SetChallengeResultTest(resWrong)).Times(1);
    accessor_->setChallengeResult(peer_, arkResultWrong);
}

} // namespace OHOS::Ace::NG
