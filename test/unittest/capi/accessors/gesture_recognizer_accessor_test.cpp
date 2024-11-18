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

#include "core/interfaces/arkoala/implementation/gesture_recognizer_peer_impl.h"

#include "accessor_test_base.h"
#include "node_api.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"

#include "gmock/gmock.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
class MockGestureRecognizer : public NGGestureRecognizer {
public:
    MockGestureRecognizer() = default;
    ~MockGestureRecognizer() override = default;
    MOCK_METHOD(GestureTypeName, GetRecognizerType, (), (const));
    MOCK_METHOD(void, SetEnabled, (bool));
    MOCK_METHOD(bool, IsEnabled, (), (const));
    MOCK_METHOD(bool, IsInResponseLinkRecognizers, ());
    MOCK_METHOD(RefereeState, GetGestureState, (), (const));

    void OnAccepted() {}
    void OnRejected() {}
    bool CheckTouchId(int32_t touchId)
    {
        return true;
    }
    void HandleTouchDownEvent(const TouchEvent& event) {}
    void HandleTouchUpEvent(const TouchEvent& event) {}
    void HandleTouchMoveEvent(const TouchEvent& event) {}
    void HandleTouchCancelEvent(const TouchEvent& event) {}
    void OnResetStatus() {}
};
} // namespace

class GestureRecognizerAccessorTest : public AccessorTestBase<GENERATED_ArkUIGestureRecognizerAccessor,
    &GENERATED_ArkUIAccessors::getGestureRecognizerAccessor, GestureRecognizerPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        mockGestureRecognizer_ = new MockGestureRecognizer();
        mockGestureRecognizerKeeper_ = AceType::Claim(mockGestureRecognizer_);
        ASSERT_NE(mockGestureRecognizerKeeper_, nullptr);
        auto peerImpl = reinterpret_cast<GestureRecognizerPeer*>(peer_);
        ASSERT_NE(peerImpl, nullptr);
        peerImpl->SetRecognizer(mockGestureRecognizerKeeper_);
        ASSERT_NE(mockGestureRecognizer_, nullptr);
    }

    void TearDown() override
    {
        AccessorTestBase::TearDown();
        mockGestureRecognizerKeeper_ = nullptr;
        mockGestureRecognizer_ = nullptr;
    }

    MockGestureRecognizer *mockGestureRecognizer_ = nullptr;
    RefPtr<MockGestureRecognizer> mockGestureRecognizerKeeper_ = nullptr;
};

/**
 * @tc.name: SetEnabledTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureRecognizerAccessorTest, SetEnabledTest, TestSize.Level1)
{
    constexpr bool enabledTrue = true;
    constexpr bool enabledFalse = false;

    Ark_Boolean arkEnabledTrue = Converter::ArkValue<Ark_Boolean>(enabledTrue);
    Ark_Boolean arkEnabledFalse = Converter::ArkValue<Ark_Boolean>(enabledFalse);

    ASSERT_NE(accessor_->setEnabled, nullptr);

    EXPECT_CALL(*mockGestureRecognizer_, SetEnabled(enabledTrue)).Times(1);
    accessor_->setEnabled(peer_, arkEnabledTrue);

    EXPECT_CALL(*mockGestureRecognizer_, SetEnabled(enabledFalse)).Times(1);
    accessor_->setEnabled(peer_, arkEnabledFalse);
}

/**
 * @tc.name: IsEnabledTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureRecognizerAccessorTest, IsEnabledTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->isEnabled, nullptr);

    EXPECT_CALL(*mockGestureRecognizer_, IsEnabled()).Times(3).WillRepeatedly(Return(true));
    EXPECT_TRUE(accessor_->isEnabled(peer_));
    EXPECT_TRUE(accessor_->isEnabled(peer_));
    EXPECT_TRUE(accessor_->isEnabled(peer_));

    EXPECT_CALL(*mockGestureRecognizer_, IsEnabled()).Times(2).WillRepeatedly(Return(false));
    EXPECT_FALSE(accessor_->isEnabled(peer_));
    EXPECT_FALSE(accessor_->isEnabled(nullptr));
    EXPECT_FALSE(accessor_->isEnabled(peer_));
}

/**
 * @tc.name: SetEnabledTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureRecognizerAccessorTest, GetStateTest, TestSize.Level1)
{
    EXPECT_CALL(*mockGestureRecognizer_, GetGestureState()).Times(3);
    accessor_->getState(peer_);
    accessor_->getState(peer_);
    accessor_->isEnabled(nullptr);
    accessor_->getState(peer_);
}

/**
 * @tc.name: GetTypeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureRecognizerAccessorTest, GetTypeTest, TestSize.Level1)
{
    EXPECT_CALL(*mockGestureRecognizer_, GetRecognizerType()).Times(3);
    accessor_->getType(peer_);
    accessor_->getType(peer_);
    accessor_->getType(nullptr);
    accessor_->getType(peer_);
}

/**
 * @tc.name: IsEnabledTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureRecognizerAccessorTest, IsValidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->isValid, nullptr);

    EXPECT_CALL(*mockGestureRecognizer_, IsInResponseLinkRecognizers()).Times(3).WillRepeatedly(Return(true));
    EXPECT_TRUE(accessor_->isValid(peer_));
    EXPECT_TRUE(accessor_->isValid(peer_));
    EXPECT_TRUE(accessor_->isValid(peer_));

    EXPECT_CALL(*mockGestureRecognizer_, IsInResponseLinkRecognizers()).Times(2).WillRepeatedly(Return(false));
    EXPECT_FALSE(accessor_->isValid(peer_));
    EXPECT_FALSE(accessor_->isValid(nullptr));
    EXPECT_FALSE(accessor_->isValid(peer_));
}
} // namespace OHOS::Ace::NG