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

#include "core/components_ng/render/animation_utils.h"
#include "core/interfaces/native/implementation/navigation_transition_proxy_peer.h"
#include "accessor_test_base.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "test/mock/core/render/mock_animation_utils.h"

#include "gmock/gmock.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

class NavigationTransitionProxyAccessorTest : public AccessorTestBase<
    GENERATED_ArkUINavigationTransitionProxyAccessor,
    &GENERATED_ArkUIAccessors::getNavigationTransitionProxyAccessor,
    NavigationTransitionProxyPeer> {
};

/**
 * @tc.name: initialStateTest
 * @tc.desc: Check the functionality of NavigationTransitionProxyAccessor
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTransitionProxyAccessorTest, initialStateTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getIsInteractive, nullptr);
    EXPECT_EQ(Converter::GetOpt(accessor_->getIsInteractive(peer_)), std::nullopt);
}

/**
 * @tc.name: nothingHandlerStateTest
 * @tc.desc: Check the functionality of NavigationTransitionProxyAccessor
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTransitionProxyAccessorTest, nothingHandlerStateTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getIsInteractive, nullptr);
    peer_->SetHandler(nullptr);
    EXPECT_EQ(Converter::GetOpt(accessor_->getIsInteractive(peer_)), std::nullopt);
}

/**
 * @tc.name: settersGettersTest
 * @tc.desc: Check the functionality of NavigationTransitionProxyAccessor
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTransitionProxyAccessorTest, settersGettersTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getIsInteractive, nullptr);

    auto proxy = AceType::MakeRefPtr<NavigationTransitionProxy>();
    peer_->SetHandler(proxy);
    auto isInteractive = ArkValue<Opt_Boolean>(true);
    accessor_->setIsInteractive(peer_, &isInteractive);
    EXPECT_EQ(Converter::GetOpt(accessor_->getIsInteractive(peer_)), true);
}

/**
 * @tc.name: finishTransactionTest
 * @tc.desc: Check the functionality of NavigationTransitionProxyAccessor
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTransitionProxyAccessorTest, finishTransactionTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->finishTransition, nullptr);

    // expect nothing bad when no proxy
    accessor_->finishTransition(peer_);

    // set null handler to peer
    peer_->SetHandler(nullptr);

    // expect nothing bad with nothing handler
    accessor_->finishTransition(peer_);

    // set handler to peer
    auto proxy = AceType::MakeRefPtr<NavigationTransitionProxy>();
    peer_->SetHandler(proxy);

    // expect nothing bad when proxy has the nullptr finishTransactionEvent (by default)
    accessor_->finishTransition(peer_);

    // add the valid data to proxy
    static bool wasInvoked = false;
    std::function<void()> finishTransactionEvent = []() {
        wasInvoked = true;
    };
    proxy->SetFinishTransitionEvent(std::move(finishTransactionEvent));

    EXPECT_FALSE(wasInvoked);
    accessor_->finishTransition(peer_);
    EXPECT_TRUE(wasInvoked);
}
} // namespace OHOS::Ace::NG
