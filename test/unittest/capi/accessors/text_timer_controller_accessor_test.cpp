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

#include "core/interfaces/native/implementation/text_timer_controller_peer_impl.h"

#include "accessor_test_base.h"
#include "core/components/texttimer/texttimer_controller.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "gmock/gmock.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
class StubTextTimerController : public TextTimerController {
public:
    StubTextTimerController()
    {
        OnStart(
            std::bind(&StubTextTimerController::Start, this)
        );
        OnPause(
            std::bind(&StubTextTimerController::Pause, this)
        );
        OnReset(
            std::bind(&StubTextTimerController::Reset, this)
        );
    }
    ~StubTextTimerController() override = default;
    virtual void Start() {}
    virtual void Pause() {}
    virtual void Reset() {}
};

class MockTextTimerController : public StubTextTimerController {
public:
    MockTextTimerController() = default;
    ~MockTextTimerController() override = default;
    MOCK_METHOD(void, Start, ());
    MOCK_METHOD(void, Pause, ());
    MOCK_METHOD(void, Reset, ());
};
} // namespace

class TextTimerControllerAccessorTest : public AccessorTestBase<GENERATED_ArkUITextTimerControllerAccessor,
    &GENERATED_ArkUIAccessors::getTextTimerControllerAccessor, TextTimerControllerPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        mockTextTimerController_ = new MockTextTimerController();
        mockTextTimerControllerKeeper_ = AceType::Claim(mockTextTimerController_);
        ASSERT_NE(mockTextTimerControllerKeeper_, nullptr);
        auto peerImpl = reinterpret_cast<TextTimerControllerPeer*>(peer_);
        ASSERT_NE(peerImpl, nullptr);
        peerImpl->SetController(mockTextTimerControllerKeeper_);
        ASSERT_NE(mockTextTimerController_, nullptr);
    }

    void TearDown() override
    {
        AccessorTestBase::TearDown();
        mockTextTimerControllerKeeper_ = nullptr;
        mockTextTimerController_ = nullptr;
    }

    MockTextTimerController *mockTextTimerController_ = nullptr;
    RefPtr<MockTextTimerController> mockTextTimerControllerKeeper_ = nullptr;
};

/**
 * @tc.name: startTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerControllerAccessorTest, startTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->start, nullptr);
    EXPECT_CALL(*mockTextTimerController_, Start()).Times(3);
    accessor_->start(peer_);
    accessor_->start(peer_);
    accessor_->start(peer_);
}

/**
 * @tc.name: pauseTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerControllerAccessorTest, pauseTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->pause, nullptr);

    EXPECT_CALL(*mockTextTimerController_, Pause()).Times(3);
    accessor_->pause(peer_);
    accessor_->pause(peer_);
    accessor_->pause(peer_);
}

/**
 * @tc.name: resetTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerControllerAccessorTest, resetTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->reset, nullptr);

    EXPECT_CALL(*mockTextTimerController_, Reset()).Times(3);
    accessor_->reset(peer_);
    accessor_->reset(peer_);
    accessor_->reset(peer_);
}
} // namespace OHOS::Ace::NG
