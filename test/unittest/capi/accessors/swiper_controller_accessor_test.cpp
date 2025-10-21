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

#include "core/interfaces/native/implementation/swiper_controller_modifier_peer_impl.h"

#include "accessor_test_base.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "test/unittest/capi/utils/async_work_test_helper.h"

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
        SetChangeIndexWithModeImpl(
            std::bind(&StubSwiperController::ChangeIndex, this, std::placeholders::_1, std::placeholders::_2)
        );
        SetFinishImpl([&]() {
            if (auto finish = this->GetFinishCallback(); finish) {
                finish();
            }
        });
        SetPreloadItemsImpl(
            std::bind(&StubSwiperController::PreloadItems, this, std::placeholders::_1)
        );
    }
    ~StubSwiperController() override = default;
    virtual void ShowNext() {}
    virtual void ShowPrevious() {}
    virtual void ChangeIndex(int32_t index, SwiperAnimationMode animationMode) {}
    virtual void PreloadItems(std::set<int32_t>) {}
};

class MockSwiperController : public StubSwiperController {
public:
    MockSwiperController() = default;
    ~MockSwiperController() override = default;
    MOCK_METHOD(void, ShowNext, ());
    MOCK_METHOD(void, ShowPrevious, ());
    MOCK_METHOD(void, ChangeIndex, (int, SwiperAnimationMode));
    MOCK_METHOD(void, PreloadItems, (std::set<int32_t>));
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
    Ark_VMContext vmContext_ = nullptr;
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

    auto arkNumValid = ArkValue<Opt_Int32>(indexValidValue);
    auto arkNumInvalid = ArkValue<Opt_Int32>(INT_MIN);
    auto optBoolTrue = ArkUnion<Opt_Union_SwiperAnimationMode_Boolean, Ark_Boolean>(true);
    auto optBoolFalse = ArkUnion<Opt_Union_SwiperAnimationMode_Boolean, Ark_Boolean>(false);
    auto optBoolUndef = ArkValue<Opt_Union_SwiperAnimationMode_Boolean>();

    EXPECT_CALL(*mockSwiperController_, ChangeIndex(indexValidValue, SwiperAnimationMode::DEFAULT_ANIMATION)).Times(1);
    accessor_->changeIndex(peer_, &arkNumValid, &optBoolTrue);

    EXPECT_CALL(*mockSwiperController_, ChangeIndex(indexValidValue, SwiperAnimationMode::NO_ANIMATION)).Times(3);
    accessor_->changeIndex(peer_, &arkNumValid, &optBoolFalse);
    accessor_->changeIndex(peer_, &arkNumValid, &optBoolUndef);
    accessor_->changeIndex(peer_, &arkNumValid, nullptr);

    EXPECT_CALL(*mockSwiperController_, ChangeIndex(0, SwiperAnimationMode::NO_ANIMATION)).Times(1);
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
    const int32_t CONTEXT_ID = 1234;

    static std::optional<int32_t> checkInvoke;
    auto callbackForCheck = [](const Ark_Int32 resourceId) {
        checkInvoke = Converter::Convert<int32_t>(resourceId);
    };
    auto callbackVoid = ArkValue<VoidCallback>(callbackForCheck, CONTEXT_ID);

    auto callbackValid = ArkValue<Opt_VoidCallback>(callbackVoid);
    auto callbackUndef = ArkValue<Opt_VoidCallback>();

    // check initial callback state in target controller
    EXPECT_FALSE(checkInvoke);
    EXPECT_EQ(mockSwiperController_->GetFinishCallback(), nullptr);

    // test the finish animation invoking with valid callback setting
    accessor_->finishAnimation(peer_, &callbackValid);
    ASSERT_TRUE(checkInvoke);
    EXPECT_EQ(*checkInvoke, CONTEXT_ID);
    checkInvoke.reset();

    // force reset and check no callback in target controller
    mockSwiperController_->SetFinishCallback({});
    EXPECT_EQ(mockSwiperController_->GetFinishCallback(), nullptr);
    EXPECT_FALSE(checkInvoke);

    // test the finish animation invoking with invalid callback setting
    accessor_->finishAnimation(peer_, &callbackUndef);
    EXPECT_EQ(mockSwiperController_->GetFinishCallback(), nullptr);
    EXPECT_FALSE(checkInvoke);

    // test the finish animation invoking without callback setting
    accessor_->finishAnimation(peer_, nullptr);
    EXPECT_EQ(mockSwiperController_->GetFinishCallback(), nullptr);
    EXPECT_FALSE(checkInvoke);
}

/**
 * @tc.name: preloadItemsTest
 * @tc.desc: Check the functionality of SwiperControllerAccessorTest.PreloadItemsImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerAccessorTest, DISABLED_preloadItemsTest, TestSize.Level1)
{
    std::initializer_list<int32_t> indexList{1, 20, 300};
    std::set<int32_t> expectedIndexSet(indexList);
    const std::string expectedErrStr{"smth went wrong"};
    static const int32_t expectedResourceId{123};
    static bool promiseFinished = false;
    static std::optional<StringArray> arrayResultStr{};

    ASSERT_NE(accessor_->preloadItems, nullptr);

    auto returnResFunc = [] (Ark_VMContext context, const Ark_Int32 resourceId, const Opt_Array_String error) {
        EXPECT_EQ(resourceId, expectedResourceId);
        promiseFinished = true;
        Converter::AssignOptionalTo(arrayResultStr, error);
    };
    auto cont = Converter::ArkValue<Callback_Opt_Array_String_Void>(returnResFunc, expectedResourceId);

    // check of the work created
    auto validValue = Converter::ArkValue<Opt_Array_Int32>(indexList, Converter::FC);
    accessor_->preloadItems(vmContext_, AsyncWorkTestHelper::GetWorkerPtr(), peer_, &validValue, &cont);
    ASSERT_TRUE(AsyncWorkTestHelper::HasWorkCreated());
    auto fireFinish = mockSwiperController_->GetPreloadFinishCallback();
    ASSERT_NE(fireFinish, nullptr);

    // check of the simulated start
    EXPECT_CALL(*mockSwiperController_, PreloadItems(expectedIndexSet)).Times(1);
    AsyncWorkTestHelper::DoExeceute();

    // check of the simulated finish cases
    EXPECT_FALSE(promiseFinished);
    fireFinish(ERROR_CODE_NO_ERROR, {}); // the good case
    EXPECT_TRUE(AsyncWorkTestHelper::HasResolved());
    EXPECT_TRUE(promiseFinished);
    AsyncWorkTestHelper::Reset();
    promiseFinished = false;
    EXPECT_FALSE(arrayResultStr.has_value());

    fireFinish(ERROR_CODE_PARAM_INVALID, expectedErrStr); // the bad case
    EXPECT_TRUE(AsyncWorkTestHelper::HasRejected());
    EXPECT_TRUE(promiseFinished);
    AsyncWorkTestHelper::Reset();
    ASSERT_TRUE(arrayResultStr.has_value());
    ASSERT_EQ(arrayResultStr->size(), 2);
    EXPECT_EQ(arrayResultStr->at(0), std::to_string(ERROR_CODE_PARAM_INVALID));
    EXPECT_EQ(arrayResultStr->at(1), expectedErrStr);

    // the mandatory complete
    AsyncWorkTestHelper::DoComplete();
}
} // namespace OHOS::Ace::NG
