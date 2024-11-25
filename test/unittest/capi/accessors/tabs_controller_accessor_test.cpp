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
class StubSwiperController : public SwiperController {
public:
    StubSwiperController()
    {
        SetSwipeToImpl(
            std::bind(&StubSwiperController::SwipeTo, this, std::placeholders::_1, std::placeholders::_2)
        );
        SetPreloadItemsImpl(
            std::bind(&StubSwiperController::PreloadItems, this, std::placeholders::_1)
        );
    }
    ~StubSwiperController() override = default;
    virtual void SwipeTo(int, bool) {}
    virtual void PreloadItems(std::set<int32_t>) {}
};

class MockSwiperController : public StubSwiperController {
public:
    MockSwiperController() = default;
    ~MockSwiperController() override = default;
    MOCK_METHOD(void, SwipeTo, (int, bool));
    MOCK_METHOD(void, PreloadItems, (std::set<int32_t>));
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
    auto invalidValue = Converter::ArkValue<Opt_Array_Number>();
    accessor_->preloadItems(peer_, &invalidValue, &cont);
    accessor_->preloadItems(peer_, nullptr, &cont);
}
} // namespace OHOS::Ace::NG
