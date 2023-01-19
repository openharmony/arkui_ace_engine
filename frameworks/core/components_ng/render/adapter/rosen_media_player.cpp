/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#include "core/components_ng/render/adapter/rosen_media_player.h"

#include <fcntl.h>
#include <iomanip>
#include <sstream>
#include <sys/stat.h>
#include <unistd.h>

#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t FILE_PREFIX_LENGTH = 7;
constexpr float SPEED_0_75_X = 0.75;
constexpr float SPEED_1_00_X = 1.00;
constexpr float SPEED_1_25_X = 1.25;
constexpr float SPEED_1_75_X = 1.75;
constexpr float SPEED_2_00_X = 2.00;
const int32_t RESOURCE_PREFIX_LENGTH = strlen("resource:///");
const int32_t RAWFILE_PREFIX_LENGTH = strlen("resource://");

std::string GetAssetAbsolutePath(const std::string& fileName)
{
    const auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, fileName);
    auto assetManager = pipelineContext->GetAssetManager();
    CHECK_NULL_RETURN(assetManager, fileName);
    std::string filePath = assetManager->GetAssetPath(fileName, true);
    std::string absolutePath = filePath + fileName;
    return absolutePath;
}

OHOS::Media::PlayerSeekMode ConvertToMediaSeekMode(SeekMode seekMode)
{
    OHOS::Media::PlayerSeekMode mode = OHOS::Media::SEEK_PREVIOUS_SYNC;
    if (seekMode == SeekMode::SEEK_NEXT_SYNC) {
        mode = OHOS::Media::SEEK_NEXT_SYNC;
    } else if (seekMode == SeekMode::SEEK_CLOSEST_SYNC) {
        mode = OHOS::Media::SEEK_CLOSEST_SYNC;
    } else if (seekMode == SeekMode::SEEK_CLOSEST) {
        mode = OHOS::Media::SEEK_CLOSEST;
    }
    return mode;
}

OHOS::Media::PlaybackRateMode ConvertToMediaPlaybackSpeed(float speed)
{
    OHOS::Media::PlaybackRateMode mode = OHOS::Media::SPEED_FORWARD_1_00_X;
    if (NearEqual(speed, SPEED_0_75_X)) {
        mode = OHOS::Media::PlaybackRateMode::SPEED_FORWARD_0_75_X;
    } else if (NearEqual(speed, SPEED_1_00_X)) {
        mode = OHOS::Media::PlaybackRateMode::SPEED_FORWARD_1_00_X;
    } else if (NearEqual(speed, SPEED_1_25_X)) {
        mode = OHOS::Media::PlaybackRateMode::SPEED_FORWARD_1_25_X;
    } else if (NearEqual(speed, SPEED_1_75_X)) {
        mode = OHOS::Media::PlaybackRateMode::SPEED_FORWARD_1_75_X;
    } else if (NearEqual(speed, SPEED_2_00_X)) {
        mode = OHOS::Media::PlaybackRateMode::SPEED_FORWARD_2_00_X;
    } else {
        LOGW("speed is not supported yet.");
    }
    return mode;
}
} // namespace
RosenMediaPlayer::~RosenMediaPlayer()
{
    CHECK_NULL_VOID_NOLOG(mediaPlayer_);
    mediaPlayer_->Release();
}

void RosenMediaPlayer::CreateMediaPlayer()
{
    if (mediaPlayer_) {
        LOGE("CreateMediaPlayer has exist");
        return;
    }
    mediaPlayer_ = OHOS::Media::PlayerFactory::CreatePlayer();
    CHECK_NULL_VOID(mediaPlayer_);
}

void RosenMediaPlayer::ResetMediaPlayer()
{
    (void)mediaPlayer_->Reset();
}

bool RosenMediaPlayer::IsMediaPlayerValid()
{
    return mediaPlayer_ != nullptr;
}

void RosenMediaPlayer::SetVolume(float leftVolume, float rightVolume)
{
    mediaPlayer_->SetVolume(leftVolume, rightVolume);
}

bool RosenMediaPlayer::SetSource(const std::string& src)
{
    auto videoSrc = src;
    // Remove file:// prefix for get fd.
    if (StringUtils::StartWith(videoSrc, "file://")) {
        videoSrc = src.substr(FILE_PREFIX_LENGTH);
    }

    int32_t fd = -1;

    if (SetMediaSource(videoSrc, fd) && fd >= 0) {
        // get size of file.
        struct stat statBuf {};
        auto statRes = fstat(fd, &statBuf);
        if (statRes != 0) {
            LOGE("get stat fail");
            close(fd);
            return false;
        }
        auto size = statBuf.st_size;
        if (mediaPlayer_->SetSource(fd, 0, size) != 0) {
            LOGE("Player SetSource failed");
            close(fd);
            return false;
        }
        close(fd);
    }
    return true;
}

bool RosenMediaPlayer::SetMediaSource(std::string& filePath, int32_t& fd)
{
    if (StringUtils::StartWith(filePath, "dataability://") || StringUtils::StartWith(filePath, "datashare://")) {
        // dataability:// or datashare://
        auto pipeline = PipelineBase::GetCurrentContext();
        auto dataProvider = AceType::DynamicCast<DataProviderManagerStandard>(pipeline->GetDataProviderManager());
        fd = dataProvider->GetDataProviderFile(filePath, "r");
    } else if (StringUtils::StartWith(filePath, "file://")) {
        filePath = GetAssetAbsolutePath(filePath.substr(FILE_PREFIX_LENGTH));
        fd = open(filePath.c_str(), O_RDONLY);
    } else if (StringUtils::StartWith(filePath, "resource:///")) {
        // file path: resources/base/media/xxx.xx --> resource:///xxx.xx
        auto assetManager = PipelineBase::GetCurrentContext()->GetAssetManager();
        auto resId = StringUtils::StringToUint(filePath.substr(RESOURCE_PREFIX_LENGTH, 8));
        auto themeManager = PipelineBase::GetCurrentContext()->GetThemeManager();
        auto themeConstants = themeManager->GetThemeConstants();
        std::string mediaPath;
        auto state1 = themeConstants->GetMediaById(resId, mediaPath);
        if (!state1) {
            LOGE("GetMediaById failed");
            return false;
        }
        MediaFileInfo fileInfo;
        auto state2 = assetManager->GetFileInfo(mediaPath.substr(mediaPath.find("resources/base")), fileInfo);
        if (!state2) {
            LOGE("GetMediaFileInfo failed");
            return false;
        }
        auto hapPath = Container::Current()->GetHapPath();
        auto hapFd = open(hapPath.c_str(), O_RDONLY);
        if (mediaPlayer_->SetSource(hapFd, fileInfo.offset, fileInfo.length) != 0) {
            LOGE("Player SetSource failed");
            close(hapFd);
            return false;
        }
        close(hapFd);
    } else if (StringUtils::StartWith(filePath, "resource://rawfile")) {
        // file path: resource/rawfile/xxx.xx --> resource://rawfile/xxx.xx
        auto themeManager = PipelineBase::GetCurrentContext()->GetThemeManager();
        auto themeConstants = themeManager->GetThemeConstants();
        RawfileDescription rfd;
        auto state = themeConstants->GetRawFileDescription(filePath.substr(RAWFILE_PREFIX_LENGTH), rfd);
        if (!state) {
            LOGE("Get rawfile description failed");
            return false;
        }
        if (mediaPlayer_->SetSource(rfd.fd, rfd.offset, rfd.length) != 0) {
            LOGE("Player SetSource failed");
            close(rfd.fd);
            return false;
        }
        close(rfd.fd);
    } else if (StringUtils::StartWith(filePath, "http")) {
        // http or https
        if (mediaPlayer_->SetSource(filePath) != 0) {
            LOGE("Player SetSource failed");
            return false;
        }
    } else {
        // relative path
        auto assetManager = PipelineBase::GetCurrentContext()->GetAssetManager();
        MediaFileInfo fileInfo;
        auto state = assetManager->GetFileInfo(assetManager->GetAssetPath(filePath, false), fileInfo);
        if (!state) {
            LOGE("GetMediaFileInfo failed");
            return false;
        }
        auto hapPath = Container::Current()->GetHapPath();
        auto hapFd = open(hapPath.c_str(), O_RDONLY);
        if (mediaPlayer_->SetSource(hapFd, fileInfo.offset, fileInfo.length) != 0) {
            LOGE("Player SetSource failed");
            close(hapFd);
            return false;
        }
        close(hapFd);
    }
    return true;
}

void RosenMediaPlayer::SetRenderSurface(const RefPtr<RenderSurface>& renderSurface)
{
    renderSurface_ = WeakClaim(RawPtr(DynamicCast<RosenRenderSurface>(renderSurface)));
}

void RosenMediaPlayer::RegisterMediaPlayerEvent(PositionUpdatedEvent&& positionUpdatedEvent,
    StateChangedEvent&& stateChangedEvent, CommonEvent&& errorEvent, CommonEvent&& resolutionChangeEvent)
{
    mediaPlayerCallback_ = std::make_shared<MediaPlayerCallback>(ContainerScope::CurrentId());
    mediaPlayerCallback_->SetPositionUpdatedEvent(std::move(positionUpdatedEvent));
    mediaPlayerCallback_->SetStateChangedEvent(std::move(stateChangedEvent));
    mediaPlayerCallback_->SetErrorEvent(std::move(errorEvent));
    mediaPlayerCallback_->SetResolutionChangeEvent(std::move(resolutionChangeEvent));
    mediaPlayer_->SetPlayerCallback(mediaPlayerCallback_);
}

int32_t RosenMediaPlayer::GetDuration(int32_t& duration)
{
    CHECK_NULL_RETURN(mediaPlayer_, -1);
    return mediaPlayer_->GetDuration(duration);
}

int32_t RosenMediaPlayer::GetVideoWidth()
{
    return mediaPlayer_->GetVideoWidth();
}

int32_t RosenMediaPlayer::GetVideoHeight()
{
    return mediaPlayer_->GetVideoHeight();
}

int32_t RosenMediaPlayer::SetLooping(bool loop)
{
    return mediaPlayer_->SetLooping(loop);
}

int32_t RosenMediaPlayer::SetPlaybackSpeed(float speed)
{
    return mediaPlayer_->SetPlaybackSpeed(ConvertToMediaPlaybackSpeed(static_cast<float>(speed)));
}

int32_t RosenMediaPlayer::SetSurface()
{
    auto renderSurface = renderSurface_.Upgrade();
    CHECK_NULL_RETURN(renderSurface, -1);
    return mediaPlayer_->SetVideoSurface(renderSurface->GetSurface());
}

int32_t RosenMediaPlayer::PrepareAsync()
{
    return mediaPlayer_->PrepareAsync();
}

bool RosenMediaPlayer::IsPlaying()
{
    return mediaPlayer_->IsPlaying();
}

int32_t RosenMediaPlayer::Play()
{
    return mediaPlayer_->Play();
}

int32_t RosenMediaPlayer::Pause()
{
    return mediaPlayer_->Pause();
}

int32_t RosenMediaPlayer::Stop()
{
    return mediaPlayer_->Stop();
}

int32_t RosenMediaPlayer::Seek(int32_t mSeconds, OHOS::Ace::SeekMode mode)
{
    return mediaPlayer_->Seek(mSeconds, ConvertToMediaSeekMode(mode));
}

} // namespace OHOS::Ace::NG