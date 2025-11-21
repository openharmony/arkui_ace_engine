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
#include "core/interfaces/native/implementation/tab_content_transition_proxy_peer_impl.h"
#include "accessor_test_base.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "gmock/gmock.h"

static constexpr int32_t TEST_IDX1 = 10;
static constexpr int32_t TEST_IDX2 = 12;

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
class MockTabContentTransitionProxy : public TabContentTransitionProxy {
public:
    MockTabContentTransitionProxy() = default;
    ~MockTabContentTransitionProxy() override = default;
    MOCK_METHOD(int32_t, GetFromIndex, ());
    MOCK_METHOD(void, SetFromIndex, (int32_t));
    MOCK_METHOD(int32_t, GetToIndex, ());
    MOCK_METHOD(void, SetToIndex, (int32_t));
};
} // namespace

class TabContentTransitionProxyAccessorTest :
    public AccessorTestBase<GENERATED_ArkUITabContentTransitionProxyAccessor,
    &GENERATED_ArkUIAccessors::getTabContentTransitionProxyAccessor, TabContentTransitionProxyPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();

        mockTabContentTransitionProxyController_ = new MockTabContentTransitionProxy();
        mockTabContentTransitionProxyControllerKeeper_ = AceType::Claim(mockTabContentTransitionProxyController_);
        auto peerImpl = reinterpret_cast<GeneratedModifier::TabContentTransitionProxyPeerImpl *>(peer_);
        ASSERT_NE(peerImpl, nullptr);
        peerImpl->AddTargetController(mockTabContentTransitionProxyControllerKeeper_);

        ASSERT_NE(mockTabContentTransitionProxyController_, nullptr);
    }

    void TearDown() override
    {
        mockTabContentTransitionProxyController_ = nullptr;
        mockTabContentTransitionProxyControllerKeeper_ = nullptr;
    }

    MockTabContentTransitionProxy *mockTabContentTransitionProxyController_ = nullptr;
    RefPtr<MockTabContentTransitionProxy> mockTabContentTransitionProxyControllerKeeper_ = nullptr;
};

/**
 * @tc.name: getFromAndSetFromTest
 * @tc.desc: Check the functionality of getFrom and setFrom
 * @tc.type: FUNC
 */
HWTEST_F(TabContentTransitionProxyAccessorTest, getFromAndSetFromTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setFrom, nullptr);
    ASSERT_NE(accessor_->getFrom, nullptr);
    auto from = Converter::ArkValue<Ark_Int32>(TEST_IDX1);
    accessor_->setFrom(peer_, from);
    Ark_Int32 idx = Converter::Convert<int32_t>(accessor_->getFrom(peer_));
    ASSERT_EQ(Converter::Convert<int32_t>(idx), TEST_IDX1);
}

/**
 * @tc.name: getToAndSetToTest
 * @tc.desc: Check the functionality of getTo and setTo
 * @tc.type: FUNC
 */
HWTEST_F(TabContentTransitionProxyAccessorTest, getToAndSetToTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setTo, nullptr);
    ASSERT_NE(accessor_->getTo, nullptr);
    auto to = Converter::ArkValue<Ark_Int32>(TEST_IDX2);
    accessor_->setTo(peer_, to);
    Ark_Int32 idx = Converter::Convert<int32_t>(accessor_->getTo(peer_));
    ASSERT_EQ(Converter::Convert<int32_t>(idx), TEST_IDX2);
}
} // namespace OHOS::Ace::NG
