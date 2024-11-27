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
#include "node_api.h"
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
    EXPECT_FALSE(accessor_->getIsInteractive(peer_));
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
    EXPECT_FALSE(accessor_->getIsInteractive(peer_));
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
    accessor_->setIsInteractive(peer_, ArkValue<Ark_Boolean>(true));
    EXPECT_TRUE(accessor_->getIsInteractive(peer_));
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

/**
 * @tc.name: cancelTransactionTest
 * @tc.desc: Check the functionality of NavigationTransitionProxyAccessor
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTransitionProxyAccessorTest, cancelTransactionTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->finishTransition, nullptr);

    // expect nothing bad when no proxy
    accessor_->cancelTransition(peer_);

    // set null handler to peer
    peer_->SetHandler(nullptr);

    // expect nothing bad with nothing handler
    accessor_->cancelTransition(peer_);

    // set handler to peer
    auto proxy = AceType::MakeRefPtr<NavigationTransitionProxy>();
    peer_->SetHandler(proxy);

    // expect nothing bad when proxy has the nullptr cancelTransactionEvent (by default)
    accessor_->cancelTransition(peer_);

    // add the valid data to proxy
    static std::optional<bool> wasInvoked;
    std::function<void(bool)> endCallback = [](bool canceled) {
        wasInvoked = canceled;
    };
    proxy->SetInteractive(true);
    proxy->SetEndCallback(std::move(endCallback));

    std::function<void()> finishCallback = []() {
        wasInvoked = true;
    };

    auto animation =  AnimationUtils::CreateInteractiveAnimation(finishCallback, finishCallback);
    proxy->SetInteractiveAnimation(animation, finishCallback);

    accessor_->cancelTransition(peer_);
    ASSERT_TRUE(wasInvoked.has_value());
    EXPECT_FALSE(wasInvoked.value());
}

/**
 * @tc.name: updateTransitionTest
 * @tc.desc: Check the functionality of NavigationTransitionProxyAccessor
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTransitionProxyAccessorTest, updateTransitionTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->updateTransition, nullptr);

    // init
    auto proxy = AceType::MakeRefPtr<NavigationTransitionProxy>();
    peer_->SetHandler(proxy);
    std::function<void(bool)> endCallback = [](bool canceled) {};
    proxy->SetEndCallback(std::move(endCallback));
    std::function<void()> finishCallback = []() {};
    auto animation =  AnimationUtils::CreateInteractiveAnimation(finishCallback, finishCallback);
    proxy->SetInteractiveAnimation(animation, finishCallback);
    proxy->SetInteractive(true);
    proxy->SetIsFinished(false);

    EXPECT_EQ(0.0f, animation->progress_);

    // valid values
    auto progress = Converter::ArkValue<Ark_Number>(1.0f);
    accessor_->updateTransition(peer_, &progress);
    EXPECT_EQ(1.0f, animation->progress_);

    progress = Converter::ArkValue<Ark_Number>(0.0f);
    accessor_->updateTransition(peer_, &progress);
    EXPECT_EQ(0.0f, animation->progress_);

    progress = Converter::ArkValue<Ark_Number>(0.5f);
    accessor_->updateTransition(peer_, &progress);
    EXPECT_EQ(0.5f, animation->progress_);

    // invalid values
    progress = Converter::ArkValue<Ark_Number>(1.5f);
    accessor_->updateTransition(peer_, &progress);
    EXPECT_EQ(0.5f, animation->progress_);
    progress = Converter::ArkValue<Ark_Number>(-0.5f);
    accessor_->updateTransition(peer_, &progress);
    EXPECT_EQ(0.5f, animation->progress_);
}
} // namespace OHOS::Ace::NG
