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
    auto arkNumValid = ArkValue<Ark_Number>(indexValidValue);
    accessor_->changeIndex(peer_, &arkNumValid);

    EXPECT_CALL(*mockSwiperController_, SwipeTo(indexDefaultValue, reverseDefaultValue)).Times(1);
    auto arkNumInvalid = ArkValue<Ark_Number>(INT_MIN);
    accessor_->changeIndex(peer_, &arkNumInvalid);

    // nothing calls expected
    accessor_->changeIndex(peer_, nullptr);
}

/**
 * @tc.name: preloadItemsTest
 * @tc.desc: Check the functionality of TabsControllerAccessor.PreloadItemsImpl
 * @tc.type: FUNC
 */
HWTEST_F(TabsControllerAccessorTest, preloadItemsTest, TestSize.Level1)
{
    std::initializer_list<int32_t> indexList = {1, 20, 300};
    std::set<int32_t> expectedIndexSet(indexList);

    ASSERT_NE(accessor_->preloadItems, nullptr);

    EXPECT_CALL(*mockSwiperController_, PreloadItems(expectedIndexSet)).Times(1);
    Converter::ArkArrayHolder<Array_Number> arrayHolder(indexList);
    auto validValue = arrayHolder.OptValue<Opt_Array_Number>();
    Callback_Opt_Array_String_Void cont{};
    accessor_->preloadItems(peer_, &validValue, &cont);

    // nothing calls expected when there are invalid params
    EXPECT_CALL(*mockSwiperController_, PreloadItems(expectedIndexSet)).Times(0);
    auto invalidValue = Converter::ArkValue<Opt_Array_Number>();
    accessor_->preloadItems(peer_, &invalidValue, &cont);
    accessor_->preloadItems(peer_, nullptr, &cont);
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
    arkTranslate.x = ArkValue<Opt_Union_Number_String>(ArkUnion<Ark_Union_Number_String, Ark_Number>(1.0f));
    arkTranslate.y = ArkValue<Opt_Union_Number_String>(ArkUnion<Ark_Union_Number_String, Ark_String>("-2.2vp"));
    arkTranslate.z = ArkValue<Opt_Union_Number_String>(Ark_Empty());

    static bool wasInvoke = false;
    mockSwiperController_->SetTabBarTranslateImpl([](const NG::TranslateOptions& translate) {
        EXPECT_EQ(translate.x.ToString(), "1.00vp");
        EXPECT_EQ(translate.y.ToString(), "-2.2vpcalc");
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
    auto arkNumValid = ArkValue<Ark_Number>(validOpacity);
    accessor_->setTabBarOpacity(peer_, &arkNumValid);

    EXPECT_CALL(*mockSwiperController_, SetTabBarOpacity(minOpacity)).Times(1);
    auto arkNumInValidMin = ArkValue<Ark_Number>(-FLT_MAX);
    accessor_->setTabBarOpacity(peer_, &arkNumInValidMin);

    EXPECT_CALL(*mockSwiperController_, SetTabBarOpacity(maxOpacity)).Times(1);
    auto arkNumInValidMax = ArkValue<Ark_Number>(FLT_MAX);
    accessor_->setTabBarOpacity(peer_, &arkNumInValidMax);

    // nothing calls expected
    EXPECT_CALL(*mockSwiperController_, SetTabBarOpacity(testing::_)).Times(0);
    accessor_->setTabBarOpacity(peer_, nullptr);
}
} // namespace OHOS::Ace::NG
