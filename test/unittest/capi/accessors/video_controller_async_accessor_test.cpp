/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/interfaces/native/implementation/video_controller_async_peer_impl.h"

#include "accessor_test_base.h"
#include "core/components_ng/pattern/video/video_controller_async.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "gmock/gmock.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
class MockVideoControllerAsync : public VideoControllerAsync {
public:
    MockVideoControllerAsync() : VideoControllerAsync(WeakPtr<VideoStateMachinePattern>()) {}
    ~MockVideoControllerAsync() override = default;

    MOCK_METHOD(void, Start, (AsyncCommandCallback && callback), (override));
    MOCK_METHOD(void, Pause, (AsyncCommandCallback && callback), (override));
    MOCK_METHOD(void, Stop, (AsyncCommandCallback && callback), (override));
    MOCK_METHOD(void, Reset, (AsyncCommandCallback && callback), (override));
    MOCK_METHOD(void, SeekTo, (float, SeekMode), (override));
    MOCK_METHOD(void, RequestFullscreen, (bool), (override));
    MOCK_METHOD(void, ExitFullscreen, (), (override));
};
} // namespace

class VideoControllerAsyncAccessorTest
    : public AccessorTestBase<GENERATED_ArkUIVideoControllerAsyncAccessor,
          &GENERATED_ArkUIAccessors::getVideoControllerAsyncAccessor, VideoControllerAsyncPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        mockController_ = AceType::MakeRefPtr<MockVideoControllerAsync>();
        ASSERT_NE(mockController_, nullptr);
        auto peerImpl = static_cast<GeneratedModifier::VideoControllerAsyncPeerImpl*>(peer_);
        ASSERT_NE(peerImpl, nullptr);
        peerImpl->SetController(mockController_);
    }

    void TearDown() override
    {
        AccessorTestBase::TearDown();
        mockController_ = nullptr;
    }

    RefPtr<MockVideoControllerAsync> mockController_ = nullptr;
};

/**
 * @tc.name: requestFullscreenTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoControllerAsyncAccessorTest, requestFullscreenTest, TestSize.Level1)
{
    constexpr bool fullscreenTrue = true;
    constexpr bool fullscreenFalse = false;

    Ark_Boolean arkFullscreenTrue = Converter::ArkValue<Ark_Boolean>(fullscreenTrue);
    Ark_Boolean arkFullscreenFalse = Converter::ArkValue<Ark_Boolean>(fullscreenFalse);

    ASSERT_NE(accessor_->requestFullscreen, nullptr);

    EXPECT_CALL(*mockController_, RequestFullscreen(fullscreenTrue)).Times(1);
    accessor_->requestFullscreen(peer_, arkFullscreenTrue);

    EXPECT_CALL(*mockController_, RequestFullscreen(fullscreenFalse)).Times(1);
    accessor_->requestFullscreen(peer_, arkFullscreenFalse);
}

/**
 * @tc.name: exitFullscreenTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoControllerAsyncAccessorTest, exitFullscreenTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->exitFullscreen, nullptr);

    EXPECT_CALL(*mockController_, ExitFullscreen()).Times(3);
    accessor_->exitFullscreen(peer_);
    accessor_->exitFullscreen(peer_);
    accessor_->exitFullscreen(peer_);
}

/**
 * @tc.name: setCurrentTimeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoControllerAsyncAccessorTest, setCurrentTimeTest, TestSize.Level1)
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
    Opt_SeekMode optSeekMode1 = Converter::ArkValue<Opt_SeekMode>(ARK_SEEK_MODE_ACCURATE);
    Opt_SeekMode optSeekMode2 = Converter::ArkValue<Opt_SeekMode>(ARK_SEEK_MODE_CLOSEST_KEYFRAME);
    Opt_SeekMode optSeekMode3 = Converter::ArkValue<Opt_SeekMode>(ARK_SEEK_MODE_NEXT_KEYFRAME);
    Opt_SeekMode optSeekMode4 = Converter::ArkValue<Opt_SeekMode>(ARK_SEEK_MODE_PREVIOUS_KEYFRAME);

    ASSERT_NE(accessor_->setCurrentTime, nullptr);

    EXPECT_CALL(*mockController_, SeekTo(pos1, seekMode1)).Times(1);
    accessor_->setCurrentTime(peer_, arkPos1, &optSeekMode1);

    EXPECT_CALL(*mockController_, SeekTo(pos2, seekMode2)).Times(1);
    accessor_->setCurrentTime(peer_, arkPos2, &optSeekMode2);

    EXPECT_CALL(*mockController_, SeekTo(pos3, seekMode3)).Times(1);
    accessor_->setCurrentTime(peer_, arkPos3, &optSeekMode3);

    EXPECT_CALL(*mockController_, SeekTo(pos4, seekMode4)).Times(1);
    accessor_->setCurrentTime(peer_, arkPos4, &optSeekMode4);

    // Test default seek mode (SEEK_PREVIOUS_SYNC) when seekMode is nullptr
    EXPECT_CALL(*mockController_, SeekTo(pos4, SeekMode::SEEK_PREVIOUS_SYNC)).Times(1);
    accessor_->setCurrentTime(peer_, arkPos4, nullptr);
}

/**
 * @tc.name: startAsyncFunctionPointerTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoControllerAsyncAccessorTest, startAsyncFunctionPointerTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->startAsync, nullptr);
    // Passing null asyncWorker should safely return early due to CHECK_NULL_VOID in peer impl
    accessor_->startAsync(nullptr, nullptr, peer_, nullptr);
}

/**
 * @tc.name: pauseAsyncFunctionPointerTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoControllerAsyncAccessorTest, pauseAsyncFunctionPointerTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->pauseAsync, nullptr);
    // Passing null asyncWorker should safely return early due to CHECK_NULL_VOID in peer impl
    accessor_->pauseAsync(nullptr, nullptr, peer_, nullptr);
}

/**
 * @tc.name: stopAsyncFunctionPointerTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoControllerAsyncAccessorTest, stopAsyncFunctionPointerTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->stopAsync, nullptr);
    // Passing null asyncWorker should safely return early due to CHECK_NULL_VOID in peer impl
    accessor_->stopAsync(nullptr, nullptr, peer_, nullptr);
}

/**
 * @tc.name: resetAsyncFunctionPointerTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(VideoControllerAsyncAccessorTest, resetAsyncFunctionPointerTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->resetAsync, nullptr);
    // Passing null asyncWorker should safely return early due to CHECK_NULL_VOID in peer impl
    accessor_->resetAsync(nullptr, nullptr, peer_, nullptr);
}

} // namespace OHOS::Ace::NG
