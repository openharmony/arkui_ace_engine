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

#include "core/interfaces/native/implementation/tabs_controller_modifier_peer_impl.h"

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
class StubSwiperController : public TabsControllerNG {
public:
    StubSwiperController()
    {
        SetSwipeToImpl(
            std::bind(&StubSwiperController::SwipeTo, this, std::placeholders::_1, std::placeholders::_2)
        );
        SetPreloadItemsImpl(
            std::bind(&StubSwiperController::PreloadItems, this, std::placeholders::_1)
        );
        SetTabBarTranslateImpl(
            std::bind(&StubSwiperController::SetTabBarTranslate, this, std::placeholders::_1)
        );
        SetTabBarOpacityImpl(
            std::bind(&StubSwiperController::SetTabBarOpacity, this, std::placeholders::_1)
        );
    }
    ~StubSwiperController() override = default;
    virtual void SwipeTo(int, bool) {}
    virtual void PreloadItems(std::set<int32_t>) {}
    virtual void SetTabBarTranslate(const NG::TranslateOptions&) {}
    virtual void SetTabBarOpacity(double opacity) {}
};

class MockSwiperController : public StubSwiperController {
public:
    MockSwiperController() = default;
    ~MockSwiperController() override = default;
    MOCK_METHOD(void, SwipeTo, (int, bool));
    MOCK_METHOD(void, PreloadItems, (std::set<int32_t>));
    MOCK_METHOD(void, SetTabBarTranslate, (const NG::TranslateOptions&));
    MOCK_METHOD(void, SetTabBarOpacity, (double opacity));
};
} // namespace

class TabsControllerAccessorTest : public AccessorTestBase<GENERATED_ArkUITabsControllerAccessor,
    &GENERATED_ArkUIAccessors::getTabsControllerAccessor, TabsControllerPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();

        mockSwiperController_ = new MockSwiperController();
        mockSwiperControllerKeeper_ = AceType::Claim(mockSwiperController_);
        ASSERT_NE(mockSwiperControllerKeeper_, nullptr);

        auto peerImpl = reinterpret_cast<GeneratedModifier::TabsControllerPeerImpl *>(peer_);
        ASSERT_NE(peerImpl, nullptr);
        peerImpl->SetTargetController(mockSwiperControllerKeeper_);

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
 * @tc.name: changeIndexTest
 * @tc.desc: Check the functionality of TabsControllerAccessor.ChangeIndex
 * @tc.type: FUNC
 */
HWTEST_F(TabsControllerAccessorTest, changeIndexTest, TestSize.Level1)
{
    constexpr int indexDefaultValue = 0;
    constexpr bool reverseDefaultValue = false;
    constexpr int indexValidValue = 10;

    ASSERT_NE(accessor_->changeIndex, nullptr);

    EXPECT_CALL(*mockSwiperController_, SwipeTo(indexValidValue, reverseDefaultValue)).Times(1);
    auto arkNumValid = ArkValue<Ark_Int32>(indexValidValue);
    accessor_->changeIndex(peer_, arkNumValid);

    EXPECT_CALL(*mockSwiperController_, SwipeTo(indexDefaultValue, reverseDefaultValue)).Times(1);
    auto arkNumInvalid = ArkValue<Ark_Int32>(INT_MIN);
    accessor_->changeIndex(peer_, arkNumInvalid);
}

/**
 * @tc.name: preloadItemsTest
 * @tc.desc: Check the functionality of TabsControllerAccessor.PreloadItemsImpl
 * @tc.type: FUNC
 */
HWTEST_F(TabsControllerAccessorTest, DISABLED_preloadItemsTest, TestSize.Level1)
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
    auto validValue = Converter::ArkValue<Opt_Array_I32>(indexList, Converter::FC);
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

/**
 * @tc.name: setTabBarTranslateTest
 * @tc.desc: Check the functionality of TabsControllerAccessor::SetTabBarTranslateImpl
 * @tc.type: FUNC
 */
HWTEST_F(TabsControllerAccessorTest, setTabBarTranslateTest, TestSize.Level1)
{
    using namespace Converter;
    ASSERT_NE(accessor_->setTabBarTranslate, nullptr);

    Ark_TranslateOptions arkTranslate;
    arkTranslate.x = ArkUnion<Opt_Union_F64_String, Ark_Float64>(1.0f);
    arkTranslate.y = ArkUnion<Opt_Union_F64_String, Ark_String>("-2.2vp");
    arkTranslate.z = ArkValue<Opt_Union_F64_String>(Ark_Empty());

    static bool wasInvoke = false;
    mockSwiperController_->SetTabBarTranslateImpl([](const NG::TranslateOptions& translate) {
        EXPECT_EQ(translate.x.ToString(), "1.00vp");
        EXPECT_EQ(translate.y.ToString(), "-2.20vp");
        EXPECT_EQ(translate.z.ToString(), "0.00px");
        wasInvoke = true;
    });
    accessor_->setTabBarTranslate(peer_, &arkTranslate);
    EXPECT_TRUE(wasInvoke);
}

/**
 * @tc.name: setTabBarOpacityTest
 * @tc.desc: Check the functionality of TabsControllerAccessor.SetTabBarOpacityImpl
 * @tc.type: FUNC
 */
HWTEST_F(TabsControllerAccessorTest, setTabBarOpacityTest, TestSize.Level1)
{
    constexpr float validOpacity = 0.95;
    constexpr float minOpacity = 0.0;
    constexpr float maxOpacity = 1.0;

    ASSERT_NE(accessor_->setTabBarOpacity, nullptr);

    EXPECT_CALL(*mockSwiperController_, SetTabBarOpacity(validOpacity)).Times(1);
    auto arkNumValid = ArkValue<Ark_Float64>(validOpacity);
    accessor_->setTabBarOpacity(peer_, arkNumValid);

    EXPECT_CALL(*mockSwiperController_, SetTabBarOpacity(minOpacity)).Times(1);
    auto arkNumInValidMin = ArkValue<Ark_Float64>(-FLT_MAX);
    accessor_->setTabBarOpacity(peer_, arkNumInValidMin);

    EXPECT_CALL(*mockSwiperController_, SetTabBarOpacity(maxOpacity)).Times(1);
    auto arkNumInValidMax = ArkValue<Ark_Float64>(FLT_MAX);
    accessor_->setTabBarOpacity(peer_, arkNumInValidMax);
}
} // namespace OHOS::Ace::NG
