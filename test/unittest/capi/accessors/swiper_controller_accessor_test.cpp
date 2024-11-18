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

#include "core/interfaces/arkoala/implementation/swiper_controller_modifier_peer_impl.h"

#include "accessor_test_base.h"
#include "node_api.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"

#include "gmock/gmock.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace {
class StubSwiperController : public SwiperController {
public:
    StubSwiperController()
    {
        SetShowNextImpl(std::bind(&StubSwiperController::ShowNext, this));
        SetShowPrevImpl(std::bind(&StubSwiperController::ShowPrevious, this));
        SetChangeIndexImpl(
            std::bind(&StubSwiperController::ChangeIndex, this, std::placeholders::_1, std::placeholders::_2)
        );
        SetFinishImpl(std::bind(&StubSwiperController::FinishAnimation, this));
    }
    ~StubSwiperController() override = default;
    virtual void ShowNext() {}
    virtual void ShowPrevious() {}
    virtual void ChangeIndex(int, bool) {}
    virtual void FinishAnimation() {}
};

class MockSwiperController : public StubSwiperController {
public:
    MockSwiperController() = default;
    ~MockSwiperController() override = default;
    MOCK_METHOD(void, ShowNext, ());
    MOCK_METHOD(void, ShowPrevious, ());
    MOCK_METHOD(void, ChangeIndex, (int, bool));
    MOCK_METHOD(void, FinishAnimation, ());
};
} // namespace

class SwiperControllerAccessorTest : public AccessorTestBase<GENERATED_ArkUISwiperControllerAccessor,
    &GENERATED_ArkUIAccessors::getSwiperControllerAccessor, SwiperControllerPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();

        mockSwiperController_ = new MockSwiperController();
        mockSwiperControllerKeeper_ = AceType::Claim(mockSwiperController_);
        ASSERT_NE(mockSwiperControllerKeeper_, nullptr);

        auto peerImpl = reinterpret_cast<GeneratedModifier::SwiperControllerPeerImpl *>(peer_);
        ASSERT_NE(peerImpl, nullptr);
        peerImpl->AddTargetController(mockSwiperControllerKeeper_);

        ASSERT_NE(mockSwiperController_, nullptr);
    }

    void TearDown() override
    {
        mockSwiperControllerKeeper_ = nullptr;
        mockSwiperController_ = nullptr;
    }

    MockSwiperController *mockSwiperController_ = nullptr;
    RefPtr<MockSwiperController> mockSwiperControllerKeeper_ = nullptr;
};

/**
 * @tc.name: showNextTest
 * @tc.desc: Check the functionality of SwiperControllerAccessor.showNext
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerAccessorTest, showNextTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->showNext, nullptr);

    EXPECT_CALL(*mockSwiperController_, ShowNext()).Times(1);
    accessor_->showNext(peer_);
}

/**
 * @tc.name: showPreviousTest
 * @tc.desc: Check the functionality of SwiperControllerAccessor.showPrevious
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerAccessorTest, showPreviousTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->showPrevious, nullptr);

    EXPECT_CALL(*mockSwiperController_, ShowPrevious()).Times(1);
    accessor_->showPrevious(peer_);
}

/**
 * @tc.name: changeIndexTest
 * @tc.desc: Check the functionality of SwiperControllerAccessor.ChangeIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerAccessorTest, changeIndexTest, TestSize.Level1)
{
    constexpr int indexValidValue = 10;

    ASSERT_NE(accessor_->changeIndex, nullptr);

    auto arkNumValid = ArkValue<Ark_Number>(indexValidValue);
    auto arkNumInvalid = ArkValue<Ark_Number>(INT_MIN);
    auto optBoolTrue = ArkValue<Opt_Boolean>(true);
    auto optBoolFalse = ArkValue<Opt_Boolean>(false);
    auto optBoolUndef = ArkValue<Opt_Boolean>();

    EXPECT_CALL(*mockSwiperController_, ChangeIndex(indexValidValue, true)).Times(1);
    accessor_->changeIndex(peer_, &arkNumValid, &optBoolTrue);

    EXPECT_CALL(*mockSwiperController_, ChangeIndex(indexValidValue, false)).Times(3);
    accessor_->changeIndex(peer_, &arkNumValid, &optBoolFalse);
    accessor_->changeIndex(peer_, &arkNumValid, &optBoolUndef);
    accessor_->changeIndex(peer_, &arkNumValid, nullptr);

    EXPECT_CALL(*mockSwiperController_, ChangeIndex(0, false)).Times(1);
    accessor_->changeIndex(peer_, &arkNumInvalid, nullptr);
}

/**
 * @tc.name: finishAnimationTest
 * @tc.desc: Check the functionality of SwiperControllerAccessor.finishAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerAccessorTest, finishAnimationTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->finishAnimation, nullptr);

    Opt_Callback_Void callbackValid = ArkValue<Opt_Callback_Void>(Callback_Void());
    Opt_Callback_Void callbackUndef = ArkValue<Opt_Callback_Void>();

    EXPECT_CALL(*mockSwiperController_, FinishAnimation()).Times(3);

    // check initial callback state in target controller
    EXPECT_FALSE(mockSwiperController_->GetFinishCallback());

    // test the finish animation invoking with valid callback setting
    accessor_->finishAnimation(peer_, &callbackValid);
    EXPECT_TRUE(mockSwiperController_->GetFinishCallback());

    // force reset and check no callback in target controller
    mockSwiperController_->SetFinishCallback({});
    EXPECT_FALSE(mockSwiperController_->GetFinishCallback());

    // test the finish animation invoking with invalid callback setting
    accessor_->finishAnimation(peer_, &callbackUndef);
    EXPECT_FALSE(mockSwiperController_->GetFinishCallback());

    // test the finish animation invoking without callback setting
    accessor_->finishAnimation(peer_, nullptr);
    EXPECT_FALSE(mockSwiperController_->GetFinishCallback());
}
} // namespace OHOS::Ace::NG
