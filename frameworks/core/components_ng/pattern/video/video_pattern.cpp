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

#include "core/components_ng/pattern/video/video_pattern.h"

#include "base/geometry/ng/size_t.h"
#include "base/i18n/localization.h"
#include "base/json/json_util.h"
#include "base/thread/task_executor.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "core/components/declaration/button/button_declaration.h"
#include "core/components/video/video_utils.h"
#include "core/components_ng/pattern/button/button_event_hub.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/video/video_event_hub.h"
#include "core/components_ng/pattern/video/video_layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t SECONDS_PER_HOUR = 3600;
constexpr int32_t MILLISECONDS_TO_SECONDS = 1000;
constexpr float CONTROL_BAR_SPACE = 15.0;
} // namespace

VideoPattern::VideoPattern(const RefPtr<VideoControllerV2>& videoController) : videoControllerV2_(videoController) {}

void VideoPattern::UpdateMediaPlayer()
{
    if (!mediaPlayer_->IsMediaPlayerValid()) {
        mediaPlayer_->CreateMediaPlayer();
        if (!mediaPlayer_->IsMediaPlayerValid()) {
            LOGE("create media player failed");
            return;
        }
    }
    PrepareMediaPlayer();
}

void VideoPattern::PrepareMediaPlayer()
{
    auto videoLayoutProperty = GetLayoutProperty<VideoLayoutProperty>();
    // src has not set/changed
    if (!videoLayoutProperty->HasVideoSource() || videoLayoutProperty->GetVideoSource() == src_) {
        return;
    }
    mediaPlayer_->ResetMediaPlayer();
    if (mediaPlayer_->IsMediaPlayerValid()) {
        float volume = muted_ ? 0.0f : 1.0f;
        mediaPlayer_->SetVolume(volume, volume);
    }
    if (!SetSourceForMediaPlayer()) {
        LOGE("set source for mediaPlayer failed");
        return;
    }
    RegisterMediaPlayerEvent();
    PrepareSurface();
}

bool VideoPattern::SetSourceForMediaPlayer()
{
    auto videoLayoutProperty = GetLayoutProperty<VideoLayoutProperty>();
    auto videoSrc = videoLayoutProperty->GetVideoSource().value();
    src_ = videoSrc;
    return mediaPlayer_->SetSource(videoSrc);
}

void VideoPattern::RegisterMediaPlayerEvent()
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);

    auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    auto videoPattern = WeakClaim(this);

    auto&& positionUpdatedEvent = [videoPattern, uiTaskExecutor](uint32_t currentPos) {
        uiTaskExecutor.PostSyncTask([&videoPattern, currentPos] {
            auto video = videoPattern.Upgrade();
            if (video != nullptr) {
                video->OnCurrentTimeChange(currentPos);
            }
        });
    };

    auto&& stateChangedEvent = [videoPattern, uiTaskExecutor](PlaybackStatus status) {
        uiTaskExecutor.PostSyncTask([&videoPattern, status] {
            auto video = videoPattern.Upgrade();
            if (video) {
                LOGD("OnPlayerStatus");
                video->OnPlayerStatus(status);
            }
        });
    };

    auto&& errorEvent = [videoPattern, uiTaskExecutor]() {
        uiTaskExecutor.PostTask([&videoPattern] {
            auto video = videoPattern.Upgrade();
            if (video) {
                LOGD("OnError");
                video->OnError("");
            }
        });
    };

    auto&& resolutionChangeEvent = [videoPattern, uiTaskExecutor]() {
        uiTaskExecutor.PostSyncTask([&videoPattern] {
            auto video = videoPattern.Upgrade();
            if (video) {
                video->OnResolutionChange();
            }
        });
    };

    mediaPlayer_->RegisterMediaPlayerEvent(positionUpdatedEvent, stateChangedEvent, errorEvent, resolutionChangeEvent);
}

void VideoPattern::OnCurrentTimeChange(uint32_t currentPos)
{
    if (currentPos == currentPos_) {
        return;
    }
    if (duration_ == 0) {
        int32_t duration = 0;
        if (mediaPlayer_->GetDuration(duration) == 0) {
            duration_ = duration / MILLISECONDS_TO_SECONDS;
            IntTimeToText(duration_, durationText_);
        }
    }
    IntTimeToText(currentPos, currentPosText_);
    currentPos_ = currentPos;

    auto eventHub = GetEventHub<VideoEventHub>();
    auto json = JsonUtil::Create(true);
    json->Put("time", static_cast<double>(currentPos));
    auto param = json->ToString();
    eventHub->FireUpdateEvent(param);
}

void VideoPattern::OnPlayerStatus(PlaybackStatus status)
{
    bool isPlaying = (status == PlaybackStatus::STARTED);
    if (isPlaying) {
        auto json = JsonUtil::Create(true);
        json->Put("start", "");
        auto param = json->ToString();
        auto eventHub = GetEventHub<VideoEventHub>();
        eventHub->FireStartEvent(param);
    } else {
        auto json = JsonUtil::Create(true);
        json->Put("pause", "");
        auto param = json->ToString();
        auto eventHub = GetEventHub<VideoEventHub>();
        eventHub->FirePauseEvent(param);
    }

    if (status == PlaybackStatus::PREPARED) {
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        if (!mediaPlayer_->IsMediaPlayerValid()) {
            return;
        }
        auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        Size videoSize = Size(mediaPlayer_->GetVideoWidth(), mediaPlayer_->GetVideoHeight());
        int32_t milliSecondDuration = 0;
        mediaPlayer_->GetDuration(milliSecondDuration);
        uiTaskExecutor.PostSyncTask([this, videoSize, duration = milliSecondDuration / MILLISECONDS_TO_SECONDS] {
            LOGI("Video OnPrepared video size: %{public}s", videoSize.ToString().c_str());
            this->OnPrepared(videoSize.Width(), videoSize.Height(), duration, 0, true);
        });
    } else if (status == PlaybackStatus::PLAYBACK_COMPLETE) {
        OnCompletion();
    }
}

void VideoPattern::OnError(const std::string& errorId)
{
#if defined(PREVIEW)
    std::string errorcode = "This component is not supported on PC Preview.";
#else
    std::string errorcode = Localization::GetInstance()->GetErrorDescription(errorId);
#endif
    auto json = JsonUtil::Create(true);
    json->Put("error", "");
    auto param = json->ToString();
    auto eventHub = GetEventHub<VideoEventHub>();
    eventHub->FireErrorEvent(param);
}

void VideoPattern::OnResolutionChange() const
{
    if (!mediaPlayer_->IsMediaPlayerValid()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    SizeF videoSize =
        SizeF(static_cast<float>(mediaPlayer_->GetVideoWidth()), static_cast<float>(mediaPlayer_->GetVideoHeight()));
    auto videoLayoutProperty = host->GetLayoutProperty<VideoLayoutProperty>();
    videoLayoutProperty->UpdateVideoSize(videoSize);
    LOGI("OnResolutionChange video size: %{public}s", videoSize.ToString().c_str());
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void VideoPattern::OnPrepared(double width, double height, uint32_t duration, uint32_t currentPos, bool needFireEvent)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto videoLayoutProperty = host->GetLayoutProperty<VideoLayoutProperty>();
    videoLayoutProperty->UpdateVideoSize(SizeF(static_cast<float>(width), static_cast<float>(height)));
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

    duration_ = duration;
    currentPos_ = currentPos;

    IntTimeToText(duration_, durationText_);
    IntTimeToText(currentPos_, currentPosText_);

    if (needFireEvent) {
        auto json = JsonUtil::Create(true);
        json->Put("duration", static_cast<double>(duration_));
        auto param = json->ToString();
        auto eventHub = GetEventHub<VideoEventHub>();
        eventHub->FirePreparedEvent(param);
    }
    UpdateLooping();
    SetSpeed();

    if (isStop_) {
        isStop_ = false;
        Start();
    }

    if (autoPlay_) {
        Start();
    }
}

void VideoPattern::OnCompletion()
{
    currentPos_ = duration_;
    IntTimeToText(currentPos_, currentPosText_);
    auto json = JsonUtil::Create(true);
    json->Put("finish", "");
    auto param = json->ToString();
    auto eventHub = GetEventHub<VideoEventHub>();
    eventHub->FireFinishEvent(param);
}

void VideoPattern::UpdateLooping()
{
    if (mediaPlayer_->IsMediaPlayerValid()) {
        mediaPlayer_->SetLooping(loop_);
    }
}

void VideoPattern::SetSpeed()
{
    if (mediaPlayer_->IsMediaPlayerValid()) {
        mediaPlayer_->SetPlaybackSpeed(static_cast<float>(progressRate_));
    }
}

void VideoPattern::IntTimeToText(uint32_t time, std::string& timeText) const
{
    bool needShowHour = duration_ > SECONDS_PER_HOUR;
    timeText = Localization::GetInstance()->FormatDuration(time, needShowHour);
}

void VideoPattern::PrepareSurface()
{
    if (renderSurface_->IsSurfaceValid()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    renderSurface_->SetRenderContext(host->GetRenderContext());
    renderSurface_->InitSurface();
    mediaPlayer_->SetRenderSurface(renderSurface_);
    if (mediaPlayer_->SetSurface() != 0) {
        LOGE("Player SetVideoSurface failed");
        return;
    };
    if (mediaPlayer_->PrepareAsync() != 0) {
        LOGE("Player prepare failed");
        return;
    }
}

void VideoPattern::OnAttachToFrameNode()
{
    SetMethodCall();
}

void VideoPattern::OnModifyDone()
{
    auto layoutProperty = GetLayoutProperty<VideoLayoutProperty>();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto children = host->GetChildren();
    if (!hasInit_) {
        if (layoutProperty->HasPosterImageInfo()) {
            bool isExist = false;
            for (const auto& child : children) {
                if (child->GetTag() == V2::IMAGE_ETS_TAG) {
                    isExist = true;
                    break;
                }
            }
            if (!isExist) {
                auto posterSourceInfo = layoutProperty->GetPosterImageInfo().value();
                auto posterNode = FrameNode::CreateFrameNode(
                    V2::IMAGE_ETS_TAG, -1, AceType::MakeRefPtr<ImagePattern>(posterSourceInfo));
                CHECK_NULL_VOID(posterNode);
                auto posterLayoutProperty = posterNode->GetLayoutProperty<ImageLayoutProperty>();
                posterLayoutProperty->UpdateImageSourceInfo(posterSourceInfo);
                host->AddChild(posterNode);
            }
        }
    }
    hasInit_ = true;
    // Create the control bar
    if (layoutProperty->HasControls() && layoutProperty->GetControlsValue(false)) {
        bool isExist = false;
        for (const auto& child : children) {
            if (child->GetTag() == V2::ROW_ETS_TAG) {
                isExist = true;
                break;
            }
        }
        if (!isExist) {
            auto controlBar = CreateControlBar();

            host->AddChild(controlBar);
        }
    } else {
        for (const auto& child : children) {
            if (child->GetTag() == V2::ROW_ETS_TAG) {
                host->RemoveChild(child);
                host->RebuildRenderContextTree();
                auto context = PipelineContext::GetCurrentContext();
                CHECK_NULL_VOID(context);
                context->RequestFrame();
                break;
            }
        }
    }
    UpdateMediaPlayer();
}

RefPtr<FrameNode> VideoPattern::CreateControlBar()
{
    auto controlBar = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    CHECK_NULL_RETURN(controlBar, nullptr);
    auto controlBarLayoutProperty = controlBar->GetLayoutProperty<LinearLayoutProperty>();
    controlBarLayoutProperty->UpdateSpace(Dimension(CONTROL_BAR_SPACE));

    auto startClickCallback = [weak = WeakClaim(this)](GestureEvent& /*info*/) {
        auto videoPattern = weak.Upgrade();
        CHECK_NULL_VOID(videoPattern);
        videoPattern->Start();
    };
    auto startButton = CreateButton("start", startClickCallback);
    CHECK_NULL_RETURN(startButton, nullptr);
    controlBar->AddChild(startButton);

    auto existFullClickCallback = [weak = WeakClaim(this)](GestureEvent& /*info*/) {
        auto videoPattern = weak.Upgrade();
        CHECK_NULL_VOID(videoPattern);
        videoPattern->ExitFullScreen();
    };
    auto existFullButton = CreateButton("existFullScreen", existFullClickCallback);
    CHECK_NULL_RETURN(existFullButton, nullptr);
    controlBar->AddChild(existFullButton);

    auto renderContext = controlBar->GetRenderContext();
    renderContext->UpdateBackgroundColor(Color::GRAY);
    return controlBar;
}

RefPtr<FrameNode> VideoPattern::CreateButton(const std::string& label, GestureEventFunc clickCallback)
{
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    CHECK_NULL_RETURN(buttonNode, nullptr);
    auto btnEventHub = buttonNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(btnEventHub, nullptr);
    btnEventHub->AddClickEvent(MakeRefPtr<ClickEvent>(std::move(clickCallback)));
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateContent(label);
    buttonNode->AddChild(textNode);
    return buttonNode;
}

void VideoPattern::SetMethodCall()
{
    auto videoController = AceType::MakeRefPtr<VideoController>();
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    videoController->SetStartImpl([weak = WeakClaim(this), uiTaskExecutor]() {
        uiTaskExecutor.PostTask([weak]() {
            auto pattern = weak.Upgrade();
            if (pattern) {
                pattern->Start();
            }
        });
    });
    videoController->SetPausetImpl([weak = WeakClaim(this), uiTaskExecutor]() {
        uiTaskExecutor.PostTask([weak]() {
            auto pattern = weak.Upgrade();
            if (pattern) {
                pattern->Pause();
            }
        });
    });
    videoController->SetStopImpl([weak = WeakClaim(this), uiTaskExecutor]() {
        uiTaskExecutor.PostTask([weak]() {
            auto pattern = weak.Upgrade();
            if (pattern) {
                pattern->Stop();
            }
        });
    });
    videoController->SetSeekToImpl([weak = WeakClaim(this), uiTaskExecutor](float pos, SeekMode seekMode) {
        uiTaskExecutor.PostTask([weak, pos, seekMode]() {
            auto pattern = weak.Upgrade();
            if (pattern) {
                pattern->SetCurrentTime(pos, seekMode);
            }
        });
    });
    videoController->SetRequestFullscreenImpl([weak = WeakClaim(this), uiTaskExecutor](bool isFullScreen) {
        uiTaskExecutor.PostTask([weak, isFullScreen]() {
            auto pattern = weak.Upgrade();
            if (pattern) {
                if (isFullScreen) {
                    pattern->FullScreen();
                } else {
                    pattern->ExitFullScreen();
                }
            }
        });
    });
    videoController->SetExitFullscreenImpl([weak = WeakClaim(this), uiTaskExecutor](bool isSync) {
        if (isSync) {
            auto pattern = weak.Upgrade();
            if (pattern) {
                pattern->ExitFullScreen();
            }
            return;
        }
        uiTaskExecutor.PostTask([weak]() {
            auto pattern = weak.Upgrade();
            if (pattern) {
                pattern->ExitFullScreen();
            }
        });
    });
    if (videoControllerV2_) {
        videoControllerV2_->AddVideoController(videoController);
    }
}

void VideoPattern::Start()
{
    if (!mediaPlayer_->IsMediaPlayerValid()) {
        return;
    }
    if (isStop_ && mediaPlayer_->Prepare() != 0) {
        LOGE("Player has not prepared");
        return;
    }
    if (!mediaPlayer_->IsPlaying()) {
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        const auto& children = host->GetChildren();
        for (const auto& child : children) {
            if (child->GetTag() == V2::IMAGE_ETS_TAG) {
                host->RemoveChild(child);
                host->RebuildRenderContextTree();
                context->RequestFrame();
            }
        }
        LOGD("Video Start");
        auto platformTask = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::BACKGROUND);
        platformTask.PostTask([weak = WeakClaim(RawPtr(mediaPlayer_))] {
            auto mediaPlayer = weak.Upgrade();
            if (mediaPlayer) {
                mediaPlayer->Play();
            }
        });
    }
}

void VideoPattern::Pause()
{
    if (!mediaPlayer_->IsMediaPlayerValid()) {
        return;
    }
    if (mediaPlayer_->IsPlaying()) {
        LOGD("Video Pause");
        mediaPlayer_->Pause();
    }
}

void VideoPattern::Stop()
{
    OnCurrentTimeChange(0);
    OnPlayerStatus(PlaybackStatus::STOPPED);
    if (!mediaPlayer_->IsMediaPlayerValid()) {
        return;
    }
    LOGD("Video Stop");
    mediaPlayer_->Stop();
    isStop_ = true;
}

void VideoPattern::SetCurrentTime(float currentPos, OHOS::Ace::SeekMode seekMode)
{
    LOGD("pos: %{public}lf, mode: %{public}d", currentPos, seekMode);
    if (!mediaPlayer_->IsMediaPlayerValid()) {
        return;
    }
    if (GreatOrEqual(currentPos, 0.0) && LessOrEqual(currentPos, duration_)) {
        LOGD("Video Seek");
        mediaPlayer_->Seek(static_cast<int32_t>(currentPos * MILLISECONDS_TO_SECONDS), seekMode);
    }
}

void VideoPattern::OnFullScreenChange(bool isFullScreen)
{
    auto json = JsonUtil::Create(true);
    json->Put("fullscreen", isFullScreen);
    auto param = json->ToString();
    auto eventHub = GetEventHub<VideoEventHub>();
    eventHub->FireFullScreenChangeEvent(param);
}

void VideoPattern::FullScreen()
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    OnFullScreenChange(true);
    auto fullScreenManager = context->GetFullScreenManager();
    CHECK_NULL_VOID(fullScreenManager);
    fullScreenManager->RequestFullScreen(host);
}

void VideoPattern::ExitFullScreen()
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    OnFullScreenChange(false);
    auto fullScreenManager = context->GetFullScreenManager();
    CHECK_NULL_VOID(fullScreenManager);
    fullScreenManager->ExitFullScreen(host);
}

} // namespace OHOS::Ace::NG
