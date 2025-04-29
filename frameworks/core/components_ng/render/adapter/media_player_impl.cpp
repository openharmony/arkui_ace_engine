/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/components_ng/render/adapter/media_player_impl.h"

#include "base/i18n/localization.h"
#include "core/components_ng/render/adapter/render_surface_impl.h"
#ifdef RENDER_EXTRACT_SUPPORTED
#include "core/components_ng/render/adapter/render_texture_impl.h"
#endif
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t SECONDS_TO_MILLISECONDS = 1000;
} // namespace

MediaPlayerImpl::~MediaPlayerImpl()
{
    if (player_) {
        player_->Stop();
        player_->Release();
    }
}

void MediaPlayerImpl::CreateMediaPlayer()
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto context = container->GetPipelineContext();
    CHECK_NULL_VOID(context);
    auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);

    auto errorCallback = [weak = WeakClaim(this), uiTaskExecutor](
                             const std::string& errorId, const std::string& param) {
        uiTaskExecutor.PostTask(
            [weak, errorId, param] {
                auto player = weak.Upgrade();
                CHECK_NULL_VOID(player);
                std::string errorcode = Localization::GetInstance()->GetErrorDescription(errorId);
                LOGE("MediaPlayer error: %{public}s", errorcode.c_str());
                if (player->errorCallback_) {
                    player->errorCallback_();
                }
            },
            "ArkUIVideoCreateMediaPlayer");
    };
    player_ = AceType::MakeRefPtr<Player>(context, std::move(errorCallback));
    InitListener();
    player_->Create(nullptr);
}

void MediaPlayerImpl::InitListener()
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto context = container->GetPipelineContext();
    CHECK_NULL_VOID(context);

    auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);

    auto onPrepared = [uiTaskExecutor, weak = WeakClaim(this)]([[maybe_unused]] uint32_t width,
                          [[maybe_unused]] uint32_t height, [[maybe_unused]] bool isPlaying,
                          [[maybe_unused]] uint32_t duration, [[maybe_unused]] uint32_t currentPos,
                          [[maybe_unused]] bool needFireEvent) {
        uiTaskExecutor.PostSyncTask(
            [weak] {
                auto player = weak.Upgrade();
                CHECK_NULL_VOID(player);
                if (player->stateChangeCallback_) {
                    player->stateChangeCallback_(PlaybackStatus::PREPARED);
                }
            },
            "ArkUIVideoPlayerPrepared");
    };

    auto onPlayerStatus = [weak = WeakClaim(this), uiTaskExecutor](bool isPlaying) {
        uiTaskExecutor.PostSyncTask([weak, isPlaying] {
                auto player = weak.Upgrade();
                CHECK_NULL_VOID(player);
                if (player->stateChangeCallback_) {
                    player->stateChangeCallback_(isPlaying ? PlaybackStatus::STARTED : PlaybackStatus::PAUSED);
                }
#if defined(ANDROID_PLATFORM) || defined(IOS_PLATFORM)
                if (player->startRenderFrameCallback_ && isPlaying) {
                    player->startRenderFrameCallback_();
                }
#endif
            }, "ArkUIVideoPlayerStatusChanged");
    };

    auto onCurrentTimeChange = [weak = WeakClaim(this), uiTaskExecutor](uint32_t currentPos) {
        uiTaskExecutor.PostSyncTask([weak, currentPos] {
                auto player = weak.Upgrade();
                CHECK_NULL_VOID(player);
                if (player->positionUpdateCallback_) {
                    player->positionUpdateCallback_(currentPos);
                }
            }, "ArkUIVideoPlayerCurrentTimeChanged");
    };

    auto onCompletion = [weak = WeakClaim(this), uiTaskExecutor] {
        uiTaskExecutor.PostSyncTask([weak] {
                auto player = weak.Upgrade();
                CHECK_NULL_VOID(player);
                if (player->stateChangeCallback_) {
                    player->stateChangeCallback_(PlaybackStatus::PLAYBACK_COMPLETE);
                }
            }, "ArkUIVideoPlayerCompletion");
    };

    auto onSeekDone = [weak = WeakClaim(this), uiTaskExecutor](uint32_t currentPos) {
        uiTaskExecutor.PostSyncTask([weak, currentPos] {
                auto player = weak.Upgrade();
                CHECK_NULL_VOID(player);
                if (player->seekDoneCallback_) {
                    player->seekDoneCallback_(currentPos);
                }
            }, "ArkUIVideoPlayerSeekDone");
    };

    player_->AddPreparedListener(onPrepared);
    player_->AddPlayStatusListener(onPlayerStatus);
    player_->AddCurrentPosListener(onCurrentTimeChange);
    player_->AddCompletionListener(onCompletion);
    player_->AddSeekDoneListener(onSeekDone);
}

void MediaPlayerImpl::ResetMediaPlayer() {}

bool MediaPlayerImpl::IsMediaPlayerValid()
{
    return player_ != nullptr;
}

void MediaPlayerImpl::SetVolume(float leftVolume, float rightVolume)
{
    CHECK_NULL_VOID(player_);
    player_->SetVolume(leftVolume);
}

bool MediaPlayerImpl::SetSource(const std::string& src, const std::string& /* bundleName */,
    const std::string& /* moduleName */)
{
    CHECK_NULL_RETURN(player_, false);
    player_->SetSource(src);
    return true;
}

void MediaPlayerImpl::SetRenderSurface(const RefPtr<RenderSurface>& renderSurface)
{
    renderSurface_ = renderSurface;
#ifdef RENDER_EXTRACT_SUPPORTED
    if (renderSurface ->IsTexture()) {
        auto surfaceImpl = AceType::DynamicCast<RenderTextureImpl>(renderSurface);
        surfaceImpl->SetExtSurfaceCallback(AceType::Claim(this));
    } else {
        auto surfaceImpl = AceType::DynamicCast<RenderSurfaceImpl>(renderSurface);
        surfaceImpl->SetExtSurfaceCallback(AceType::Claim(this));
    }
#else
    auto surfaceImpl = AceType::DynamicCast<RenderSurfaceImpl>(renderSurface);
    surfaceImpl->SetExtSurfaceCallback(AceType::Claim(this));
#endif
}

void MediaPlayerImpl::RegisterMediaPlayerEvent(PositionUpdatedEvent&& positionUpdatedEvent,
    StateChangedEvent&& stateChangedEvent, CommonEvent&& errorEvent, CommonEvent&& resolutionChangeEvent,
    CommonEvent&& startRenderFrameEvent)
{
    positionUpdateCallback_ = positionUpdatedEvent;
    stateChangeCallback_ = stateChangedEvent;
    errorCallback_ = errorEvent;
    resolutionChangeCallback_ = resolutionChangeEvent;
    startRenderFrameCallback_ = startRenderFrameEvent;
}

void MediaPlayerImpl::RegisterMediaPlayerSeekDoneEvent(SeekDoneEvent&& seekDoneEvent)
{
    seekDoneCallback_ = seekDoneEvent;
}

void MediaPlayerImpl::RegisterTextureEvent(TextureRefreshEnVent&& textureRefreshEvent)
{
    textureRefreshCallback_ = textureRefreshEvent;
}

int32_t MediaPlayerImpl::GetDuration(int32_t& duration)
{
    CHECK_NULL_RETURN(player_, -1);
    duration = static_cast<int32_t>(player_->GetDuration()) * SECONDS_TO_MILLISECONDS;
    return 0;
}

int32_t MediaPlayerImpl::GetVideoWidth()
{
    CHECK_NULL_RETURN(player_, -1);
    return static_cast<int32_t>(player_->GetWidth());
}

int32_t MediaPlayerImpl::GetVideoHeight()
{
    CHECK_NULL_RETURN(player_, -1);
    return static_cast<int32_t>(player_->GetHeight());
}

int32_t MediaPlayerImpl::SetLooping(bool loop)
{
    CHECK_NULL_RETURN(player_, -1);
    player_->EnableLooping(loop);
    return 0;
}

int32_t MediaPlayerImpl::SetPlaybackSpeed(float speed)
{
    CHECK_NULL_RETURN(player_, -1);
    player_->SetSpeed(speed);
    return 0;
}

int32_t MediaPlayerImpl::SetSurface()
{
    CHECK_NULL_RETURN(player_, -1);
    auto renderSurface = renderSurface_.Upgrade();
    CHECK_NULL_RETURN(renderSurface, -1);
#ifdef RENDER_EXTRACT_SUPPORTED
    if (renderSurface ->IsTexture()) {
        auto textureImpl = AceType::DynamicCast<RenderTextureImpl>(renderSurface);
        CHECK_NULL_RETURN(textureImpl, -1);
        player_->SetSurfaceId(textureImpl->GetTextureId(), true);
    } else {
        auto surfaceImpl = AceType::DynamicCast<RenderSurfaceImpl>(renderSurface);
        CHECK_NULL_RETURN(surfaceImpl, -1);
        player_->SetSurfaceId(surfaceImpl->GetSurfaceId(), false);
    }
#else
    auto surfaceImpl = AceType::DynamicCast<RenderSurfaceImpl>(renderSurface);
    CHECK_NULL_RETURN(surfaceImpl, -1);
    player_->SetSurfaceId(surfaceImpl->GetSurfaceId(), false);
#endif
    return 0;
}

int32_t MediaPlayerImpl::PrepareAsync()
{
    return 0;
}

bool MediaPlayerImpl::IsPlaying()
{
    CHECK_NULL_RETURN(player_, false);
    return player_->IsPlaying();
}

int32_t MediaPlayerImpl::Play()
{
    CHECK_NULL_RETURN(player_, -1);
    LOGI("Media player start to play.");
    player_->Start();
    return 0;
}

int32_t MediaPlayerImpl::Pause()
{
    CHECK_NULL_RETURN(player_, -1);
    LOGI("Media player start to pause.");
    player_->Pause();
    return 0;
}

int32_t MediaPlayerImpl::Stop()
{
    CHECK_NULL_RETURN(player_, -1);
    LOGI("Media player start to stop.");
    player_->Stop();
    return 0;
}

int32_t MediaPlayerImpl::Seek(int32_t mSeconds, OHOS::Ace::SeekMode mode)
{
    CHECK_NULL_RETURN(player_, -1);
    LOGI("Media player start to seek.");
    player_->SeekTo(mSeconds, static_cast<uint32_t>(mode));
    return 0;
}

int32_t MediaPlayerImpl::FullScreenChange(bool isFullScreen)
{
    CHECK_NULL_RETURN(player_, -1);
    LOGI("Media player change fullscreen");
    player_->SetFullScreenChange(isFullScreen);
    return 0;
}

void MediaPlayerImpl::ProcessSurfaceCreate()
{
    LOGI("Media player ProcessSurfaceCreate.");
    SetSurface();
}

void MediaPlayerImpl::ProcessSurfaceChange(int32_t width, int32_t height)
{
    LOGI("Media player ProcessSurfaceChange (%{public}d, %{public}d)", width, height);
    if (resolutionChangeCallback_) {
        resolutionChangeCallback_();
    }
}

void MediaPlayerImpl::ProcessTextureRefresh(int32_t instanceId, int64_t textureId)
{
    if (textureRefreshCallback_) {
        textureRefreshCallback_(instanceId, textureId);
    }
}

} // namespace OHOS::Ace::NG
