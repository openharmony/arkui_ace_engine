/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
#include <sys/stat.h>
#include "base/image/file_uri_helper.h"
#include "core/common/resource/resource_manager.h"
#include "core/common/resource/resource_object.h"
#include "core/common/resource/resource_wrapper.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float SPEED_0_75_X = 0.75;
constexpr float SPEED_1_00_X = 1.00;
constexpr float SPEED_1_25_X = 1.25;
constexpr float SPEED_1_75_X = 1.75;
constexpr float SPEED_2_00_X = 2.00;
constexpr uint32_t MEDIA_RESOURCE_MATCH_SIZE = 2;
const int32_t RAWFILE_PREFIX_LENGTH = strlen("resource://RAWFILE/");
const std::regex MEDIA_RES_ID_REGEX(R"(^resource://\w+/([0-9]+)\.\w+$)", std::regex::icase);
const std::regex MEDIA_APP_RES_ID_REGEX(R"(^resource://.*/([0-9]+)\.\w+$)", std::regex::icase);
const std::string FA_RESOURCE_PREFIX = "assets/entry/";
const std::regex MEDIA_APP_RES_PATH_REGEX(R"(^resource://RAWFILE/(.*)$)");

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
    CHECK_NULL_VOID(mediaPlayer_);
    mediaPlayer_->Release();
}

void RosenMediaPlayer::CreateMediaPlayer()
{
    if (mediaPlayer_) {
        LOGE("CreateMediaPlayer has exist");
        return;
    }
    mediaPlayer_ = OHOS::Media::PlayerFactory::CreatePlayer();
}

void RosenMediaPlayer::ResetMediaPlayer()
{
    CHECK_NULL_VOID(mediaPlayer_);
    (void)mediaPlayer_->Reset();
}

bool RosenMediaPlayer::IsMediaPlayerValid()
{
    return mediaPlayer_ != nullptr;
}

void RosenMediaPlayer::SetVolume(float leftVolume, float rightVolume)
{
    CHECK_NULL_VOID(mediaPlayer_);
    mediaPlayer_->SetVolume(leftVolume, rightVolume);
}

void RosenMediaPlayer::SetMediaMuted(int32_t type, bool isMuted)
{
    CHECK_NULL_VOID(mediaPlayer_);
    mediaPlayer_->SetMediaMuted(static_cast<OHOS::Media::MediaType>(type), isMuted);
}

bool RosenMediaPlayer::SetSource(const std::string& src, const std::string& bundleName, const std::string& moduleName)
{
    auto videoSrc = src;
    int32_t fd = -1;
    bool useFd = false;
    if (!SetMediaSource(videoSrc, fd, useFd, bundleName, moduleName)) {
        LOGE("Video media player set media source failed.");
        return false;
    }

    if (!useFd) {
        // For example "http://url" or "/relative path".
        LOGI("Source without fd, just return true.");
        return true;
    }
    if (fd >= 0) {
        // Get size of file.
        struct stat statBuf {};
        auto statRes = fstat(fd, &statBuf);
        if (statRes != 0) {
            LOGE("Video media player get stat failed.");
            close(fd);
            return false;
        }
        auto size = statBuf.st_size;
        if (mediaPlayer_ && mediaPlayer_->SetSource(fd, 0, size) != 0) {
            LOGE("Video media player etSource failed");
            close(fd);
            return false;
        }
        close(fd);
        return true;
    }
    LOGE("Video source fd is invalid.");
    return false;
}

bool RosenMediaPlayer::SetSourceByFd(int32_t fd)
{
    if (fd < 0) {
        LOGE("Video source fd is invalid.");
        return false;
    }
    struct stat statBuf {};
    auto statRes = fstat(fd, &statBuf);
    if (statRes != 0) {
        LOGE("Video media player get stat failed.");
        return false;
    }
    auto size = statBuf.st_size;
    if (mediaPlayer_ && mediaPlayer_->SetSource(fd, 0, size) != 0) {
        LOGE("Video media player etSource failed");
        return false;
    }
    return true;
}

// Interim programme
bool RosenMediaPlayer::MediaPlay(const std::string& filePath)
{
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto assetManager = pipelineContext->GetAssetManager();
    CHECK_NULL_RETURN(assetManager, false);
    uint32_t resId = 0;
    auto getResIdState = GetResourceId(filePath, resId);
    if (!getResIdState) {
        return false;
    }
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, false);
    auto themeConstants = themeManager->GetThemeConstants();
    CHECK_NULL_RETURN(themeConstants, false);
    std::string mediaPath;
    auto getMediaPathState = themeConstants->GetMediaById(resId, mediaPath);
    if (!getMediaPathState) {
        LOGE("GetMediaById failed");
        return false;
    }
    MediaFileInfo fileInfo;
    size_t pos = mediaPath.find("resources/base");
    if (pos == std::string::npos) {
        LOGE("substring is not found in mediaPath.");
        return false;
    }
    std::string videoFilePath = mediaPath.substr(pos);
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    if (!container->IsUseStageModel()) {
        videoFilePath = FA_RESOURCE_PREFIX + videoFilePath;
    }
    auto getFileInfoState = assetManager->GetFileInfo(videoFilePath, fileInfo);
    if (!getFileInfoState) {
        LOGE("GetMediaFileInfo failed");
        return false;
    }
    auto hapPath = container->GetHapPath();
    char realPath[PATH_MAX] = { 0x00 };
    if (!RealPath(hapPath, realPath)) {
        return false;
    }
    auto hapFd = open(realPath, O_RDONLY);
    if (hapFd < 0) {
        LOGE("Open hap file failed");
        return false;
    }
    if (mediaPlayer_ && mediaPlayer_->SetSource(hapFd, fileInfo.offset, fileInfo.length) != 0) {
        LOGE("Player SetSource failed");
        close(hapFd);
        return false;
    }
    close(hapFd);
    return true;
}

bool RosenMediaPlayer::RawFileWithModuleInfoPlay(const std::string& src, const std::string& bundleName,
    const std::string& moduleName)
{
    auto resourceObject = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName);
    RefPtr<ResourceAdapter> resourceAdapter = nullptr;
    RefPtr<ThemeConstants> themeConstants = nullptr;
    if (SystemProperties::GetResourceDecoupling()) {
        resourceAdapter = ResourceManager::GetInstance().GetOrCreateResourceAdapter(resourceObject);
        CHECK_NULL_RETURN(resourceAdapter, false);
        resourceAdapter->UpdateResourceManager(bundleName, moduleName);
    } else {
        auto themeManager = PipelineBase::CurrentThemeManager();
        CHECK_NULL_RETURN(themeManager, false);
        themeConstants = themeManager->GetThemeConstants();
        CHECK_NULL_RETURN(themeConstants, false);
    }

    static std::mutex rawFdMutex_;
    std::lock_guard lock(rawFdMutex_);
    auto resourceWrapper = AceType::MakeRefPtr<ResourceWrapper>(themeConstants, resourceAdapter);
    std::string rawFile;
    RawfileDescription rawfileDescription;
    if (GetResourceId(src, rawFile)) {
        if (!resourceWrapper->GetRawFileDescription(rawFile, rawfileDescription)) {
            TAG_LOGW(AceLogTag::ACE_VIDEO, "get video data by name failed");
            return false;
        }
    }

    if (!mediaPlayer_ ||
        mediaPlayer_->SetSource(rawfileDescription.fd, rawfileDescription.offset, rawfileDescription.length) != 0) {
        LOGE("Player SetSource failed");
        resourceWrapper->CloseRawFileDescription(rawFile);
        return false;
    }
    resourceWrapper->CloseRawFileDescription(rawFile);
    return true;
}

bool RosenMediaPlayer::RawFilePlay(const std::string& filePath)
{
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto assetManager = pipelineContext->GetAssetManager();
    CHECK_NULL_RETURN(assetManager, false);
    auto path = "resources/rawfile/" + filePath.substr(RAWFILE_PREFIX_LENGTH);
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    if (!container->IsUseStageModel()) {
        path = FA_RESOURCE_PREFIX + path;
    }
    MediaFileInfo fileInfo;
    auto getFileInfoState = assetManager->GetFileInfo(path, fileInfo);
    if (!getFileInfoState) {
        LOGE("GetMediaFileInfo failed");
        return false;
    }
    auto hapPath = container->GetHapPath();
    char realPath[PATH_MAX] = { 0x00 };
    if (!RealPath(hapPath, realPath)) {
        return false;
    }

    auto hapFd = open(realPath, O_RDONLY);
    if (hapFd < 0) {
        LOGE("Open hap file failed");
        return false;
    }
    if (!mediaPlayer_ || mediaPlayer_->SetSource(hapFd, fileInfo.offset, fileInfo.length) != 0) {
        LOGE("Player SetSource failed");
        close(hapFd);
        return false;
    }
    close(hapFd);
    return true;
}

bool RosenMediaPlayer::RelativePathPlay(const std::string& filePath)
{
    // relative path
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto assetManager = pipelineContext->GetAssetManager();
    CHECK_NULL_RETURN(assetManager, false);
    MediaFileInfo fileInfo;
    auto state = assetManager->GetFileInfo(assetManager->GetAssetPath(filePath, false), fileInfo);
    if (!state) {
        LOGE("GetMediaFileInfo failed");
        return false;
    }
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto hapPath = container->GetHapPath();
    char realPath[PATH_MAX] = { 0x00 };
    if (!RealPath(hapPath, realPath)) {
        return false;
    }
    auto hapFd = open(realPath, O_RDONLY);
    if (hapFd < 0) {
        LOGE("Open hap file failed");
        return false;
    }
    if (mediaPlayer_ && mediaPlayer_->SetSource(hapFd, fileInfo.offset, fileInfo.length) != 0) {
        LOGE("Player SetSource failed");
        close(hapFd);
        return false;
    }
    close(hapFd);
    return true;
}

bool RosenMediaPlayer::GetResourceId(const std::string& path, uint32_t& resId)
{
    std::smatch matches;
    if (std::regex_match(path, matches, MEDIA_RES_ID_REGEX) && matches.size() == MEDIA_RESOURCE_MATCH_SIZE) {
        resId = static_cast<uint32_t>(std::stoul(matches[1].str()));
        return true;
    }

    std::smatch appMatches;
    if (std::regex_match(path, appMatches, MEDIA_APP_RES_ID_REGEX) && appMatches.size() == MEDIA_RESOURCE_MATCH_SIZE) {
        resId = static_cast<uint32_t>(std::stoul(appMatches[1].str()));
        return true;
    }

    return false;
}

bool RosenMediaPlayer::GetResourceId(const std::string& uri, std::string& path) const
{
    std::smatch matches;
    if (std::regex_match(uri, matches, MEDIA_APP_RES_PATH_REGEX) && matches.size() == MEDIA_RESOURCE_MATCH_SIZE) {
        path = matches[1].str();
        return true;
    }

    return false;
}

bool RosenMediaPlayer::SetMediaSource(std::string& filePath, int32_t& fd, bool& useFd,
    const std::string& bundleName, const std::string& moduleName)
{
    if (StringUtils::StartWith(filePath, "dataability://") || StringUtils::StartWith(filePath, "datashare://") ||
        StringUtils::StartWith(filePath, "file://media")) {
        // dataability:// or datashare://
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_RETURN(pipeline, false);
        auto dataProvider = AceType::DynamicCast<DataProviderManagerStandard>(pipeline->GetDataProviderManager());
        CHECK_NULL_RETURN(dataProvider, false);
        fd = dataProvider->GetDataProviderFile(filePath, "r");
        useFd = true;
    } else if (StringUtils::StartWith(filePath, "file://")) {
        filePath = FileUriHelper::GetRealPath(filePath);
        fd = open(filePath.c_str(), O_RDONLY);
        useFd = true;
    } else if (StringUtils::StartWith(filePath, "resource:///")) {
        // file path: resources/base/media/xxx.xx --> resource:///xxx.xx
        return MediaPlay(filePath);
    } else if (StringUtils::StartWith(filePath, "resource://RAWFILE")) {
        //Multi module, eg: HSP
        if (!RawFileWithModuleInfoPlay(filePath, bundleName, moduleName)) {
            // file path: resource/rawfile/xxx.xx --> resource://rawfile/xxx.xx
            return RawFilePlay(filePath);
        }
        return true;
    } else if (StringUtils::StartWith(filePath, "http")) {
        // http or https
        if (mediaPlayer_ && mediaPlayer_->SetSource(filePath) != 0) {
            LOGE("Player SetSource failed");
            return false;
        }
    } else {
        // All of other urls, think of it as relative path.
        if (StringUtils::StartWith(filePath, "/")) {
            filePath = filePath.substr(1);
        }
        return RelativePathPlay(filePath);
    }
    return true;
}

void RosenMediaPlayer::SetRenderSurface(const RefPtr<RenderSurface>& renderSurface)
{
    renderSurface_ = DynamicCast<RosenRenderSurface>(renderSurface);
}

void RosenMediaPlayer::RegisterMediaPlayerEvent(PositionUpdatedEvent&& positionUpdatedEvent,
    StateChangedEvent&& stateChangedEvent, CommonEvent&& errorEvent, CommonEvent&& resolutionChangeEvent,
    CommonEvent&& startRenderFrameEvent)
{
    CHECK_NULL_VOID(mediaPlayer_);
    mediaPlayerCallback_ = std::make_shared<MediaPlayerCallback>(ContainerScope::CurrentId());
    mediaPlayerCallback_->SetPositionUpdatedEvent(std::move(positionUpdatedEvent));
    mediaPlayerCallback_->SetStateChangedEvent(std::move(stateChangedEvent));
    mediaPlayerCallback_->SetErrorEvent(std::move(errorEvent));
    mediaPlayerCallback_->SetResolutionChangeEvent(std::move(resolutionChangeEvent));
    mediaPlayerCallback_->SetStartRenderFrameEvent(std::move(startRenderFrameEvent));
    mediaPlayer_->SetPlayerCallback(mediaPlayerCallback_);
}

void RosenMediaPlayer::RegisterMediaPlayerSeekDoneEvent(SeekDoneEvent&& seekDoneEvent)
{
    if (mediaPlayerCallback_) {
        mediaPlayerCallback_->SetSeekDoneEvent(std::move(seekDoneEvent));
    }
}

int32_t RosenMediaPlayer::GetDuration(int32_t& duration)
{
    CHECK_NULL_RETURN(mediaPlayer_, -1);
    return mediaPlayer_->GetDuration(duration);
}

int32_t RosenMediaPlayer::GetVideoWidth()
{
    CHECK_NULL_RETURN(mediaPlayer_, -1);
    return mediaPlayer_->GetVideoWidth();
}

int32_t RosenMediaPlayer::GetVideoHeight()
{
    CHECK_NULL_RETURN(mediaPlayer_, -1);
    return mediaPlayer_->GetVideoHeight();
}

int32_t RosenMediaPlayer::SetLooping(bool loop)
{
    CHECK_NULL_RETURN(mediaPlayer_, -1);
    return mediaPlayer_->SetLooping(loop);
}

int32_t RosenMediaPlayer::SetPlaybackSpeed(float speed)
{
    CHECK_NULL_RETURN(mediaPlayer_, -1);
    return mediaPlayer_->SetPlaybackSpeed(ConvertToMediaPlaybackSpeed(static_cast<float>(speed)));
}

int32_t RosenMediaPlayer::SetSurface()
{
    CHECK_NULL_RETURN(mediaPlayer_, -1);
    auto renderSurface = renderSurface_.Upgrade();
    CHECK_NULL_RETURN(renderSurface, -1);
    return mediaPlayer_->SetVideoSurface(renderSurface->GetSurface());
}

int32_t RosenMediaPlayer::SetRenderFirstFrame(bool display)
{
    CHECK_NULL_RETURN(mediaPlayer_, -1);
    return mediaPlayer_->SetRenderFirstFrame(display);
}

int32_t RosenMediaPlayer::PrepareAsync()
{
    CHECK_NULL_RETURN(mediaPlayer_, -1);
    return mediaPlayer_->PrepareAsync();
}

bool RosenMediaPlayer::IsPlaying()
{
    CHECK_NULL_RETURN(mediaPlayer_, false);
    return mediaPlayer_->IsPlaying();
}

int32_t RosenMediaPlayer::Play()
{
    LOGI("Media player start to play.");
    CHECK_NULL_RETURN(mediaPlayer_, -1);
    return mediaPlayer_->Play();
}

int32_t RosenMediaPlayer::Pause()
{
    LOGI("Media player start to pause.");
    CHECK_NULL_RETURN(mediaPlayer_, -1);
    return mediaPlayer_->Pause();
}

int32_t RosenMediaPlayer::Stop()
{
    LOGI("Media player start to stop.");
    CHECK_NULL_RETURN(mediaPlayer_, -1);
    return mediaPlayer_->Stop();
}

int32_t RosenMediaPlayer::Seek(int32_t mSeconds, OHOS::Ace::SeekMode mode)
{
    LOGI("Media player start to seek.");
    CHECK_NULL_RETURN(mediaPlayer_, -1);
    return mediaPlayer_->Seek(mSeconds, ConvertToMediaSeekMode(mode));
}

int32_t RosenMediaPlayer::SetPlayRange(int64_t startTime, int64_t endTime)
{
    LOGI("Media player start to SetPlayRange.");
    CHECK_NULL_RETURN(mediaPlayer_, -1);
    return mediaPlayer_->SetPlayRange(startTime, endTime);
}

int32_t RosenMediaPlayer::SetParameter(const std::string& key, int64_t value)
{
    LOGI("Media player start to SetParameter.");
    CHECK_NULL_RETURN(mediaPlayer_, -1);
    Media::Format format;
    (void)format.PutIntValue(key, value);
    return mediaPlayer_->SetParameter(format);
}

} // namespace OHOS::Ace::NG
