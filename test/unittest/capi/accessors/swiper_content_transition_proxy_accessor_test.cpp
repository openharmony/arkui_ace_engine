/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, nullptr);
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/interfaces/native/implementation/swiper_content_transition_proxy_peer.h"
#include "accessor_test_base.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "gmock/gmock.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

class SwiperContentTransitionProxyAccessorTest : public AccessorTestBase<
    GENERATED_ArkUISwiperContentTransitionProxyAccessor,
    &GENERATED_ArkUIAccessors::getSwiperContentTransitionProxyAccessor,
    SwiperContentTransitionProxyPeer> {
};

/**
 * @tc.name: initialStateTest
 * @tc.desc: Check the functionality of SwiperContentTransitionProxyAccessor
 * @tc.type: FUNC
 */
HWTEST_F(SwiperContentTransitionProxyAccessorTest, initialStateTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getSelectedIndex, nullptr);
    ASSERT_NE(accessor_->getIndex, nullptr);
    ASSERT_NE(accessor_->getPosition, nullptr);
    ASSERT_NE(accessor_->getMainAxisLength, nullptr);

    EXPECT_EQ(Converter::Convert<int32_t>(accessor_->getSelectedIndex(peer_)), 0);
    EXPECT_EQ(Converter::Convert<int32_t>(accessor_->getIndex(peer_)), 0);
    EXPECT_EQ(Converter::Convert<int32_t>(accessor_->getPosition(peer_)), 0);
    EXPECT_EQ(Converter::Convert<int32_t>(accessor_->getMainAxisLength(peer_)), 0);
}

/**
 * @tc.name: nothingHandlerStateTest
 * @tc.desc: Check the functionality of SwiperContentTransitionProxyAccessor
 * @tc.type: FUNC
 */
HWTEST_F(SwiperContentTransitionProxyAccessorTest, nothingHandlerStateTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getSelectedIndex, nullptr);
    ASSERT_NE(accessor_->getIndex, nullptr);
    ASSERT_NE(accessor_->getPosition, nullptr);
    ASSERT_NE(accessor_->getMainAxisLength, nullptr);

    peer_->SetHandler(nullptr);

    EXPECT_EQ(Converter::Convert<int32_t>(accessor_->getSelectedIndex(peer_)), 0);
    EXPECT_EQ(Converter::Convert<int32_t>(accessor_->getIndex(peer_)), 0);
    EXPECT_EQ(Converter::Convert<int32_t>(accessor_->getPosition(peer_)), 0);
    EXPECT_EQ(Converter::Convert<int32_t>(accessor_->getMainAxisLength(peer_)), 0);
}

/**
 * @tc.name: settersGettersTest
 * @tc.desc: Check the functionality of SwiperContentTransitionProxyAccessor
 * @tc.type: FUNC
 */
HWTEST_F(SwiperContentTransitionProxyAccessorTest, settersGettersTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getSelectedIndex, nullptr);
    ASSERT_NE(accessor_->setSelectedIndex, nullptr);
    ASSERT_NE(accessor_->getIndex, nullptr);
    ASSERT_NE(accessor_->setIndex, nullptr);
    ASSERT_NE(accessor_->getPosition, nullptr);
    ASSERT_NE(accessor_->setPosition, nullptr);
    ASSERT_NE(accessor_->getMainAxisLength, nullptr);
    ASSERT_NE(accessor_->setMainAxisLength, nullptr);

    auto proxy = AceType::MakeRefPtr<SwiperContentTransitionProxy>();
    peer_->SetHandler(proxy);

    auto arkSelectedIndex = ArkValue<Ark_Number>(1);
    accessor_->setSelectedIndex(peer_, &arkSelectedIndex);
    EXPECT_EQ(Converter::Convert<int32_t>(accessor_->getSelectedIndex(peer_)), 1);

    auto arkIndex = ArkValue<Ark_Number>(2);
    accessor_->setIndex(peer_, &arkIndex);
    EXPECT_EQ(Converter::Convert<int32_t>(accessor_->getIndex(peer_)), 2);

    auto arkPosition = ArkValue<Ark_Number>(3);
    accessor_->setPosition(peer_, &arkPosition);
    EXPECT_EQ(Converter::Convert<int32_t>(accessor_->getPosition(peer_)), 3);

    auto arkMainAxisLength = ArkValue<Ark_Number>(4);
    accessor_->setMainAxisLength(peer_, &arkMainAxisLength);
    EXPECT_EQ(Converter::Convert<int32_t>(accessor_->getMainAxisLength(peer_)), 4);
}

/**
 * @tc.name: finishTransactionTest
 * @tc.desc: Check the functionality of SwiperContentTransitionProxyAccessor
 * @tc.type: FUNC
 */
HWTEST_F(SwiperContentTransitionProxyAccessorTest, finishTransactionTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->finishTransition, nullptr);

    // expect nothing bad when no proxy
    accessor_->finishTransition(peer_);

    // set null handler to peer
    peer_->SetHandler(nullptr);

    // expect nothing bad with nothing handler
    accessor_->finishTransition(peer_);

    // set handler to peer
    auto proxy = AceType::MakeRefPtr<SwiperContentTransitionProxy>();
    peer_->SetHandler(proxy);

    // expect nothing bad when proxy has the nullptr finishTransactionEvent (by default)
    accessor_->finishTransition(peer_);

    // add the valid finishTransactionEvent to proxy
    static bool wasInvoked = false;
    std::function<void()> finishTransactionEvent = []() {
        wasInvoked = true;
    };
    proxy->SetFinishTransitionEvent(std::move(finishTransactionEvent));

    // expect the WAD
    EXPECT_FALSE(wasInvoked);
    accessor_->finishTransition(peer_);
    EXPECT_TRUE(wasInvoked);
}
} // namespace OHOS::Ace::NG
