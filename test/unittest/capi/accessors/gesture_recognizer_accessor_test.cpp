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

#include "core/interfaces/native/implementation/gesture_recognizer_peer_impl.h"

#include "accessor_test_base.h"
#include "core/components_ng/gestures/recognizers/click_recognizer.h"
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "core/components_ng/pattern/scroll/scroll_model_ng.h"
#include "core/components_ng/pattern/swiper/swiper_model_ng.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/implementation/event_target_info_peer.h"
#include "core/interfaces/native/implementation/scrollable_target_info_peer.h"

#include "gmock/gmock.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
constexpr int32_t TEST_FINGERS_COUNT = 3;
constexpr int32_t TEST_FINGERS_COUNT_DEFAULT = 1;

class MockGestureRecognizer : public ClickRecognizer {
public:
    MockGestureRecognizer() = default;
    ~MockGestureRecognizer() override = default;
    MOCK_METHOD(void, SetEnabled, (bool));
    MOCK_METHOD(bool, IsEnabled, (), (const));
    MOCK_METHOD(bool, IsInResponseLinkRecognizers, ());

    void SetTestFingersCount(const int32_t& count)
    {
        fingers_ = count;
    }

    void SetTestRefereeState(RefereeState refereeState)
    {
        refereeState_ = refereeState;
    }
};

const std::vector<std::pair<GestureTypeName, Ark_GestureControl_GestureType>> getTypeTestPlan = {
    { GestureTypeName::TAP_GESTURE, ARK_GESTURE_CONTROL_GESTURE_TYPE_TAP_GESTURE },
    { GestureTypeName::LONG_PRESS_GESTURE, ARK_GESTURE_CONTROL_GESTURE_TYPE_LONG_PRESS_GESTURE },
    { GestureTypeName::PAN_GESTURE, ARK_GESTURE_CONTROL_GESTURE_TYPE_PAN_GESTURE },
    { GestureTypeName::PINCH_GESTURE, ARK_GESTURE_CONTROL_GESTURE_TYPE_PINCH_GESTURE },
    { GestureTypeName::SWIPE_GESTURE, ARK_GESTURE_CONTROL_GESTURE_TYPE_SWIPE_GESTURE },
    { GestureTypeName::ROTATION_GESTURE, ARK_GESTURE_CONTROL_GESTURE_TYPE_ROTATION_GESTURE },
    { GestureTypeName::DRAG, ARK_GESTURE_CONTROL_GESTURE_TYPE_DRAG },
    { GestureTypeName::CLICK, ARK_GESTURE_CONTROL_GESTURE_TYPE_CLICK },
};
} // namespace

class GestureRecognizerAccessorTest : public AccessorTestBase<GENERATED_ArkUIGestureRecognizerAccessor,
    &GENERATED_ArkUIAccessors::getGestureRecognizerAccessor, GestureRecognizerPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        mockGestureRecognizer_ = AceType::MakeRefPtr<MockGestureRecognizer>();
        ASSERT_NE(mockGestureRecognizer_, nullptr);
        peer_->Update(mockGestureRecognizer_);
    }

    void TearDown() override
    {
        AccessorTestBase::TearDown();
        mockGestureRecognizer_ = nullptr;
    }

    RefPtr<MockGestureRecognizer> mockGestureRecognizer_ = nullptr;
};

/**
 * @tc.name: SetEnabledTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureRecognizerAccessorTest, DISABLED_SetEnabledTest, TestSize.Level1)
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
HWTEST_F(GestureRecognizerAccessorTest, DISABLED_IsEnabledTest, TestSize.Level1)
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
 * @tc.name: GetStateTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureRecognizerAccessorTest, GetStateTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getState, nullptr);

    auto arkState = accessor_->getState(peer_);
    EXPECT_EQ(ARK_GESTURE_RECOGNIZER_STATE_READY, arkState);

    mockGestureRecognizer_->SetTestRefereeState(NG::RefereeState::PENDING);
    arkState = accessor_->getState(peer_);
    EXPECT_EQ(ARK_GESTURE_RECOGNIZER_STATE_PENDING, arkState);
}

/**
 * @tc.name: GetTypeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureRecognizerAccessorTest, GetTypeTest, TestSize.Level1)
{
    for (auto& [value, expected]: getTypeTestPlan) {
        mockGestureRecognizer_->SetRecognizerType(value);
        auto result = accessor_->getType(peer_);
        EXPECT_EQ(result, expected);
    }
}

/**
 * @tc.name: GetEventTargetInfo
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureRecognizerAccessorTest, GetEventTargetInfo, TestSize.Level1)
{
    ASSERT_NE(accessor_->getEventTargetInfo, nullptr);
    auto info = accessor_->getEventTargetInfo(peer_);
    ASSERT_NE(info, nullptr);
    auto eventTargetInfo = reinterpret_cast<EventTargetInfoPeer*>(info);
    EXPECT_EQ(AceType::DynamicCast<ScrollableTargetInfoPeer>(eventTargetInfo), nullptr);
    eventTargetInfo->DecRefCount();

    mockGestureRecognizer_ = AceType::MakeRefPtr<MockGestureRecognizer>();
    peer_->Update(mockGestureRecognizer_);
    const auto swiperNode = SwiperModelNG::CreateFrameNode(0);
    mockGestureRecognizer_->AttachFrameNode(swiperNode);
    info = accessor_->getEventTargetInfo(peer_);
    ASSERT_NE(info, nullptr);
    auto scrollableTargetInfo = AceType::DynamicCast<ScrollableTargetInfoPeer>(
        reinterpret_cast<EventTargetInfoPeer*>(info));
    ASSERT_NE(scrollableTargetInfo, nullptr);
    EXPECT_EQ(scrollableTargetInfo->id, "");
    EXPECT_EQ(scrollableTargetInfo->GetPattern(), swiperNode->GetPattern());
    scrollableTargetInfo->DecRefCount();

    mockGestureRecognizer_ = AceType::MakeRefPtr<MockGestureRecognizer>();
    peer_->Update(mockGestureRecognizer_);
    const auto buttonNode = ButtonModelNG::CreateFrameNode(0);
    mockGestureRecognizer_->AttachFrameNode(buttonNode);
    info = accessor_->getEventTargetInfo(peer_);
    ASSERT_NE(info, nullptr);
    eventTargetInfo = reinterpret_cast<EventTargetInfoPeer*>(info);
    EXPECT_EQ(AceType::DynamicCast<ScrollableTargetInfoPeer>(eventTargetInfo), nullptr);
    EXPECT_EQ(eventTargetInfo->id, "");
    eventTargetInfo->DecRefCount();

    mockGestureRecognizer_ = AceType::MakeRefPtr<MockGestureRecognizer>();
    peer_->Update(mockGestureRecognizer_);
    const auto scrollNode = ScrollModelNG::CreateFrameNode(0);
    mockGestureRecognizer_->AttachFrameNode(scrollNode);
    info = accessor_->getEventTargetInfo(peer_);
    ASSERT_NE(info, nullptr);
    scrollableTargetInfo = AceType::DynamicCast<ScrollableTargetInfoPeer>(
        reinterpret_cast<EventTargetInfoPeer*>(info));
    ASSERT_NE(scrollableTargetInfo, nullptr);
    EXPECT_EQ(scrollableTargetInfo->id, "");
    EXPECT_EQ(scrollableTargetInfo->GetPattern(), scrollNode->GetPattern());
    scrollableTargetInfo->DecRefCount();
}

/**
 * @tc.name: IsEnabledTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureRecognizerAccessorTest, DISABLED_IsValidTest, TestSize.Level1)
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

/**
 * @tc.name: GetTagTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureRecognizerAccessorTest, GetTagTest, TestSize.Level1)
{
    const std::string expectedTag = "Test";
    auto info = AccessibilityManager::MakeRefPtr<GestureInfo>();
    info->SetTag(expectedTag);
    auto recognizer = peer_->GetRecognizer().Upgrade();
    ASSERT_NE(recognizer, nullptr);
    recognizer->SetGestureInfo(info);
    auto result = accessor_->getTag(peer_);
    EXPECT_EQ(Converter::Convert<std::string>(result), expectedTag);
}

/**
 * @tc.name: GetFingerCountTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureRecognizerAccessorTest, GetFingerCountTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getFingerCount, nullptr);

    auto count = accessor_->getFingerCount(peer_);
    auto defCount = Converter::Convert<int32_t>(count);
    EXPECT_EQ(TEST_FINGERS_COUNT_DEFAULT, defCount);

    mockGestureRecognizer_->SetTestFingersCount(TEST_FINGERS_COUNT);
    auto arkTestCount = accessor_->getFingerCount(peer_);
    auto testCount = Converter::Convert<int32_t>(arkTestCount);
    EXPECT_EQ(TEST_FINGERS_COUNT, testCount);
}

/**
 * @tc.name: IsFingerCountLimitImplTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureRecognizerAccessorTest, IsFingerCountLimitImplTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->isFingerCountLimit, nullptr);

    auto limitOn = accessor_->isFingerCountLimit(peer_);
    auto deflimitOn = Converter::Convert<bool>(limitOn);
    EXPECT_EQ(false, deflimitOn);

    mockGestureRecognizer_->SetLimitFingerCount(true);
    auto arkTestLimit = accessor_->isFingerCountLimit(peer_);
    auto testLimit = Converter::Convert<bool>(arkTestLimit);
    EXPECT_EQ(true, testLimit);
}
} // namespace OHOS::Ace::NG
