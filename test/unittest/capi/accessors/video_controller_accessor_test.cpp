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

#include "core/interfaces/native/implementation/video_controller_peer_impl.h"

#include "accessor_test_base.h"
#include "core/components_ng/pattern/video/video_controller_v2.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "gmock/gmock.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
class MockVideoController : public VideoControllerV2 {
public:
    MockVideoController() = default;
    ~MockVideoController() override = default;
    MOCK_METHOD(void, Start, ());
    MOCK_METHOD(void, Pause, ());
    MOCK_METHOD(void, Stop, ());
    MOCK_METHOD(void, SeekTo, (float, SeekMode));
    MOCK_METHOD(void, RequestFullscreen, (bool));
    MOCK_METHOD(void, ExitFullscreen, (bool));
    MOCK_METHOD(void, Reset, ());
};
} // namespace

class VideoControllerAccessorTest : public AccessorTestBase<GENERATED_ArkUIVideoControllerAccessor,
    &GENERATED_ArkUIAccessors::getVideoControllerAccessor, VideoControllerPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        mockVideoController_ = new MockVideoController();
        mockVideoControllerKeeper_ = AceType::Claim(mockVideoController_);
        ASSERT_NE(mockVideoControllerKeeper_, nullptr);
        auto peerImpl = reinterpret_cast<GeneratedModifier::VideoControllerPeerImpl*>(peer_);
        ASSERT_NE(peerImpl, nullptr);
        peerImpl->SetController(mockVideoControllerKeeper_);
        ASSERT_NE(mockVideoController_, nullptr);
    }

    void TearDown() override
    {
        AccessorTestBase::TearDown();
        mockVideoControllerKeeper_ = nullptr;
        mockVideoController_ = nullptr;
    }

    MockVideoController *mockVideoController_ = nullptr;
    RefPtr<MockVideoController> mockVideoControllerKeeper_ = nullptr;
};

/**
 * @tc.name: startTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoControllerAccessorTest, startTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->start, nullptr);

    EXPECT_CALL(*mockVideoController_, Start()).Times(3);
    accessor_->start(peer_);
    accessor_->start(peer_);
    accessor_->start(peer_);
}

/**
 * @tc.name: pauseTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoControllerAccessorTest, pauseTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->pause, nullptr);

    EXPECT_CALL(*mockVideoController_, Pause()).Times(3);
    accessor_->pause(peer_);
    accessor_->pause(peer_);
    accessor_->pause(peer_);
}

/**
 * @tc.name: stopTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoControllerAccessorTest, stopTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->stop, nullptr);

    EXPECT_CALL(*mockVideoController_, Stop()).Times(3);
    accessor_->stop(peer_);
    accessor_->stop(peer_);
    accessor_->stop(peer_);
}

/**
 * @tc.name: exitFullscreenTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoControllerAccessorTest, exitFullscreenTest, TestSize.Level1)
{
    constexpr bool isSync = false;

    ASSERT_NE(accessor_->exitFullscreen, nullptr);

    EXPECT_CALL(*mockVideoController_, ExitFullscreen(isSync)).Times(3);
    accessor_->exitFullscreen(peer_);
    accessor_->exitFullscreen(peer_);
    accessor_->exitFullscreen(peer_);
}

/**
 * @tc.name: resetTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoControllerAccessorTest, resetTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->reset, nullptr);

    EXPECT_CALL(*mockVideoController_, Reset()).Times(3);
    accessor_->reset(peer_);
    accessor_->reset(peer_);
    accessor_->reset(peer_);
}

/**
 * @tc.name: requestFullscreenTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoControllerAccessorTest, requestFullscreenTest, TestSize.Level1)
{
    constexpr bool fullscreenTrue = true;
    constexpr bool fullscreenFalse = false;

    Ark_Boolean arkFullscreenTrue = Converter::ArkValue<Ark_Boolean>(fullscreenTrue);
    Ark_Boolean arkFullscreenFalse = Converter::ArkValue<Ark_Boolean>(fullscreenFalse);

    ASSERT_NE(accessor_->requestFullscreen, nullptr);

    EXPECT_CALL(*mockVideoController_, RequestFullscreen(fullscreenTrue)).Times(1);
    accessor_->requestFullscreen(peer_, arkFullscreenTrue);

    EXPECT_CALL(*mockVideoController_, RequestFullscreen(fullscreenFalse)).Times(1);
    accessor_->requestFullscreen(peer_, arkFullscreenFalse);
}

/**
 * @tc.name: setCurrentTimeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoControllerAccessorTest, DISABLED_setCurrentTimeTest, TestSize.Level1)
{
    constexpr float pos1 = 1000;
    constexpr float pos2 = 3000.5;
    constexpr float pos3 = 8000;
    constexpr float pos4 = 10000.5;
    constexpr SeekMode seekMode1 = SeekMode::SEEK_CLOSEST;
    constexpr SeekMode seekMode2 = SeekMode::SEEK_CLOSEST_SYNC;
    constexpr SeekMode seekMode3 = SeekMode::SEEK_NEXT_SYNC;
    constexpr SeekMode seekMode4 = SeekMode::SEEK_PREVIOUS_SYNC;

    auto arkPos1 = Converter::ArkValue<Ark_Float64>(pos1);
    auto arkPos2 = Converter::ArkValue<Ark_Float64>(pos2);
    auto arkPos3 = Converter::ArkValue<Ark_Float64>(pos3);
    auto arkPos4 = Converter::ArkValue<Ark_Float64>(pos4);
    Ark_SeekMode arkSeekMode1 = ARK_SEEK_MODE_ACCURATE;
    auto optSeekMode1 = Converter::OptConvert<Ark_SeekMode>(arkSeekMode1);
    Ark_SeekMode arkSeekMode2 = ARK_SEEK_MODE_CLOSEST_KEYFRAME;
    auto optSeekMode2 = Converter::OptConvert<Ark_SeekMode>(arkSeekMode2);
    Ark_SeekMode arkSeekMode3 = ARK_SEEK_MODE_NEXT_KEYFRAME;
    auto optSeekMode3 = Converter::OptConvert<Ark_SeekMode>(arkSeekMode3);
    Ark_SeekMode arkSeekMode4 = ARK_SEEK_MODE_PREVIOUS_KEYFRAME;
    auto optSeekMode4 = Converter::OptConvert<Ark_SeekMode>(arkSeekMode4);

    ASSERT_NE(accessor_->setCurrentTime, nullptr);

    EXPECT_CALL(*mockVideoController_, SeekTo(pos1, seekMode1)).Times(1);
    accessor_->setCurrentTime(peer_, arkPos1, optSeekMode1);

    EXPECT_CALL(*mockVideoController_, SeekTo(pos2, seekMode2)).Times(1);
    accessor_->setCurrentTime(peer_, arkPos2, optSeekMode2);

    EXPECT_CALL(*mockVideoController_, SeekTo(pos3, seekMode3)).Times(1);
    accessor_->setCurrentTime(peer_, arkPos3, optSeekMode3);

    EXPECT_CALL(*mockVideoController_, SeekTo(pos4, seekMode4)).Times(2);
    accessor_->setCurrentTime(peer_, arkPos4, optSeekMode4);
}
} // namespace OHOS::Ace::NG
