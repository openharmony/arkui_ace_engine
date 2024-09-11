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

constexpr int INDEX_VALID_VALUE = 10;
} // namespace

class SwiperControllerAccessorTest : public AccessorTestBase<GENERATED_ArkUISwiperControllerAccessor,
    &GENERATED_ArkUIAccessors::getSwiperControllerAccessor, SwiperControllerPeer> {
public:
    static void SetUpTestCase()
    {
        AccessorTestBase::SetUpTestCase();

        auto controller = new MockSwiperController();
        mockSwiperController_ = AceType::Claim(controller);
        EXPECT_CALL(*controller, ShowNext()).Times(1);
        EXPECT_CALL(*controller, ShowPrevious()).Times(1);
        EXPECT_CALL(*controller, ChangeIndex(INDEX_VALID_VALUE, true)).Times(1);
        EXPECT_CALL(*controller, ChangeIndex(INDEX_VALID_VALUE, false)).Times(3);
        EXPECT_CALL(*controller, ChangeIndex(0, false)).Times(1);
        EXPECT_CALL(*controller, FinishAnimation()).Times(3);
    }

    static void TearDownTestCase()
    {
        mockSwiperController_ = nullptr;

        AccessorTestBase::TearDownTestCase();
    }

    virtual void SetUp(void) override
    {
        AccessorTestBase::SetUp();

        auto peerImpl = reinterpret_cast<GeneratedModifier::SwiperControllerPeerImpl *>(peer_);
        ASSERT_NE(peerImpl, nullptr);
        peerImpl->AddListener(mockSwiperController_);
    }

    static inline RefPtr<MockSwiperController> mockSwiperController_ = nullptr;
};

/**
 * @tc.name: showNextTest
 * @tc.desc: Check the functionality of SwiperControllerAccessor.showNext
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerAccessorTest, showNextTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->showNext, nullptr);
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
    accessor_->showPrevious(peer_);
}

/**
 * @tc.name: changeIndexTest
 * @tc.desc: Check the functionality of SwiperControllerAccessor.ChangeIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerAccessorTest, changeIndexTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->changeIndex, nullptr);
    auto arkNumValid = ArkValue<Ark_Number>(INDEX_VALID_VALUE);
    auto arkNumInvalid = ArkValue<Ark_Number>(INT_MIN);
    auto arkBoolTrue = ArkValue<Opt_Boolean>(true);
    auto arkBoolFalse = ArkValue<Opt_Boolean>(false);
    auto arkBoolUndef = ArkValue<Opt_Boolean>();

    accessor_->changeIndex(peer_, &arkNumValid, &arkBoolTrue);
    accessor_->changeIndex(peer_, &arkNumValid, &arkBoolFalse);
    accessor_->changeIndex(peer_, &arkNumValid, &arkBoolUndef);
    accessor_->changeIndex(peer_, &arkNumValid, nullptr);
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

    Opt_Function callbackValid = ArkValue<Opt_Function>(0);
    Opt_Function callbackUndef = ArkValue<Opt_Function>();

    // check initial callback state in target controller 
    EXPECT_FALSE(mockSwiperController_->GetFinishCallback());

    // test the finish animation invoking with callback setting 
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
