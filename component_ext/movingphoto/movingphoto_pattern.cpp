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

#include <unistd.h>

#include "movingphoto_pattern.h"
#include "movingphoto_node.h"
#include "movingphoto_utils.h"

#include "base/image/pixel_map.h"
#include "core/components_ng/pattern/image/image_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t LONG_PRESS_DELAY = 300;
constexpr int32_t ANIMATION_DURATION_300 = 300;
constexpr int32_t ANIMATION_DURATION_400 = 400;
constexpr float NORMAL_SCALE = 1.0f;
constexpr float ZOOM_IN_SCALE = 1.1f;
constexpr double NORMAL_PLAY_SPEED = 1.0;
constexpr int32_t HALF = 2;
constexpr int64_t PERIOD_START = 0;
constexpr int32_t PREPARE_RETURN = 0;
constexpr int64_t VIDEO_PLAYTIME_START_POSITION = 0;
constexpr int32_t IMAGE_LOADING_COMPLETE = 0;
constexpr int32_t DURATION_FLAG = -1;
const std::string THUMBNAIL_MEDIUM_JOINT = "?&oper=thumbnail&width=-1&height=-1&path=";
const std::string COVER_POSITION = "cover_positon";
const std::string IMAGE_URI = "uri";
const std::string VIDEO_SCALE = "video_scale_type";
constexpr int32_t ANALYZER_DELAY_TIME = 100;
constexpr int32_t ANALYZER_CAPTURE_DELAY_TIME = 1000;
constexpr int32_t AVERAGE_VALUE = 2;
}
MovingPhotoPattern::MovingPhotoPattern(const RefPtr<MovingPhotoController>& controller)
    : instanceId_(Container::CurrentId()), controller_(controller)
{}

void MovingPhotoPattern::OnModifyDone()
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingphoto onModifydone start.");
    Pattern::OnModifyDone();
    UpdateImageNode();
    UpdateVideoNode();
    if (SystemProperties::GetExtSurfaceEnabled()) {
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        pipelineContext->AddOnAreaChangeNode(host->GetId());
    }
    InitEvent();
    UpdatePlayMode();
    HandleImageAnalyzerMode();
}

void MovingPhotoPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    static RenderContext::ContextParam param = { RenderContext::ContextType::HARDWARE_SURFACE, "MediaPlayerSurface",
                                                 RenderContext::PatternType::VIDEO };
    renderContextForMediaPlayer_->InitContext(false, param);
    renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    renderContextForMediaPlayer_->UpdateBackgroundColor(Color::TRANSPARENT);
    renderContext->SetClipToBounds(true);

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->AddWindowStateChangedCallback(host->GetId());

    CHECK_NULL_VOID(controller_);
    ContainerScope scope(instanceId_);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    controller_->SetStartPlaybackImpl([weak = WeakClaim(this), uiTaskExecutor]() {
        uiTaskExecutor.PostTask(
            [weak]() {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                ContainerScope scope(pattern->instanceId_);
                pattern->StartPlayback();
            }, "ArkUIMovingPhotoStart");
    });

    controller_->SetStopPlaybackImpl([weak = WeakClaim(this), uiTaskExecutor]() {
        uiTaskExecutor.PostTask(
            [weak]() {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                ContainerScope scope(pattern->instanceId_);
                pattern->StopPlayback();
            }, "ArkUIMovingPhotoStop");
    });

    controller_->SetRefreshMovingPhotoImpl([weak = WeakClaim(this), uiTaskExecutor]() {
        uiTaskExecutor.PostTask(
            [weak]() {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                ContainerScope scope(pattern->instanceId_);
                pattern->RefreshMovingPhoto();
            }, "RefreshMovingPhoto");
    });

    RegisterVisibleAreaChange();
}

void MovingPhotoPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    auto id = frameNode->GetId();
    auto pipeline = AceType::DynamicCast<PipelineContext>(PipelineBase::GetCurrentContext());
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowStateChangedCallback(id);
    hasVisibleChangeRegistered_ = false;
}

void MovingPhotoPattern::OnDetachFromMainTree()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (host->GetNodeStatus() == NodeStatus::BUILDER_NODE_OFF_MAINTREE) {
        Stop();
    }
}

void MovingPhotoPattern::OnRebuildFrame()
{
    if (!renderSurface_ || !renderSurface_->IsSurfaceValid()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto movingPhotoNode = AceType::DynamicCast<MovingPhotoNode>(host);
    CHECK_NULL_VOID(movingPhotoNode);
    auto video = AceType::DynamicCast<FrameNode>(movingPhotoNode->GetVideo());
    CHECK_NULL_VOID(video);
    auto renderContext = video->GetRenderContext();
    renderContext->AddChild(renderContextForMediaPlayer_, 0);
}

void MovingPhotoPattern::InitEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (longPressEvent_) {
        gestureHub->SetLongPressEvent(longPressEvent_, false, false, LONG_PRESS_DELAY);
    }
    auto longPressCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleLongPress(info);
    };
    longPressEvent_ = MakeRefPtr<LongPressEvent>(std::move(longPressCallback));
    gestureHub->SetLongPressEvent(longPressEvent_, false, false, LONG_PRESS_DELAY);

    if (touchEvent_) {
        gestureHub->AddTouchEvent(touchEvent_);
        return;
    }
    auto touchTask = [weak = WeakClaim(this)](TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleTouchEvent(info);
    };
    touchEvent_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gestureHub->AddTouchEvent(touchEvent_);
}

void MovingPhotoPattern::LongPressEventModify(bool status)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (status) {
        auto longPressCallback = [weak = WeakClaim(this)](GestureEvent& info) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleLongPress(info);
        };
        longPressEvent_ = MakeRefPtr<LongPressEvent>(std::move(longPressCallback));
        gestureHub->SetLongPressEvent(longPressEvent_, false, false, LONG_PRESS_DELAY);
    } else {
        gestureHub->SetLongPressEvent(nullptr);
        longPressEvent_ = nullptr;
    }
}

void MovingPhotoPattern::HandleLongPress(GestureEvent& info)
{
    isFastKeyUp_ = false;
    if (currentPlayStatus_ == PlaybackStatus::STARTED || !isPrepared_ || isPlayByController_) {
        return;
    }
    if (autoAndRepeatLevel_ == PlaybackMode::NONE && isEnableAnalyzer_) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "HandleLongPress isEnableAnalyzer_ return.");
        return;
    }
    if (isRefreshMovingPhoto_) {
        if (autoAndRepeatLevel_ == PlaybackMode::REPEAT) {
            TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "HandleLongPress IsRefreshMovingPhotoReturn:%{public}d.",
                isRefreshMovingPhoto_);
            return;
        }
        isRefreshMovingPhotoPlaying_ = true;
    } else {
        if (autoAndRepeatLevel_ != PlaybackMode::NONE) {
            TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "HandleLongPress IsRefreshMovingPhotoReturn not:%{public}d.",
                isRefreshMovingPhoto_);
            return;
        }
    }
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingphoto HandleLongPress start.");
    if (!mediaPlayer_ || !mediaPlayer_->IsMediaPlayerValid()) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "MediaPlayer is null or invalid.");
        FireMediaPlayerError();
        return;
    }
    if (currentPlayStatus_ == PlaybackStatus::STOPPED) {
        mediaPlayer_->PrepareAsync();
    }
    if (isSetAutoPlayPeriod_ && (currentPlayStatus_ == PlaybackStatus::PLAYBACK_COMPLETE ||
        currentPlayStatus_ == PlaybackStatus::PAUSED)) {
        int32_t duration = DURATION_FLAG;
        mediaPlayer_->GetDuration(duration);
        SetAutoPlayPeriod(PERIOD_START, duration);
    }
    Start();
}

void MovingPhotoPattern::HandleTouchEvent(TouchEventInfo& info)
{
    if (currentPlayStatus_ == PlaybackStatus::ERROR) {
        ResetMediaPlayer();
    }
    if (IsRefreshMovingPhotoReturn(isRefreshMovingPhotoPlaying_)) {
        TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "HandleTouchEvent IsRefreshMovingPhotoReturn.");
        return;
    }
    if (!isPrepared_ || isPlayByController_) {
        return;
    }
    if (autoAndRepeatLevel_ == PlaybackMode::NONE && isEnableAnalyzer_) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "HandleTouchEvent isEnableAnalyzer_ return.");
        return;
    }
    auto touchList = info.GetChangedTouches();
    CHECK_NULL_VOID(!touchList.empty());
    auto touchInfo = touchList.front();
    auto touchType = touchInfo.GetTouchType();
    isFastKeyUp_ = false;
    if (touchType == TouchType::UP || touchType == TouchType::CANCEL) {
        if (currentPlayStatus_ == PlaybackStatus::STARTED) {
            PausePlayback();
        } else if (currentPlayStatus_ == PlaybackStatus::PLAYBACK_COMPLETE) {
            currentPlayStatus_ = PlaybackStatus::NONE;
            StopAnimation();
        } else {
            isFastKeyUp_ = true;
        }
    }
}

void MovingPhotoPattern::UpdateImageNode()
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "UpdateImageNode start.%{public}d", movingPhotoFormat_);
    if (startAnimationFlag_) {
        needUpdateImageNode_ = true;
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto movingPhoto = AceType::DynamicCast<MovingPhotoNode>(host);
    CHECK_NULL_VOID(movingPhoto);
    auto image = AceType::DynamicCast<FrameNode>(movingPhoto->GetImage());
    CHECK_NULL_VOID(image);
    DynamicRangeModeConvert(dynamicRangeMode_);
    ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, DynamicMode, dynamicRangeMode_, image);
    ACE_UPDATE_NODE_RENDER_CONTEXT(DynamicRangeMode, dynamicRangeMode_, image);
    auto imagePattern = image->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(imagePattern);
    imagePattern->SetOrientation(ImageRotateOrientation::AUTO);
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingphoto set HDR.%{public}d", dynamicRangeMode_);
    auto layoutProperty = GetLayoutProperty<MovingPhotoLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (!layoutProperty->HasImageSourceInfo()) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "image info is null.");
        auto posterLayoutProperty = image->GetLayoutProperty<ImageLayoutProperty>();
        posterLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
        image->MarkModifyDone();
        return;
    }
    auto imageSourceInfo = layoutProperty->GetImageSourceInfo().value();
    auto imageFit = layoutProperty->GetObjectFitValue(ImageFit::COVER);
    if (!imageSourceInfo.IsValid()) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "image info is invalid.");
        auto posterLayoutProperty = image->GetLayoutProperty<ImageLayoutProperty>();
        posterLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
        image->MarkModifyDone();
        return;
    }
    if (image) {
        image->SetDraggable(false);
        auto imageLayoutProperty = image->GetLayoutProperty<ImageLayoutProperty>();
        imageLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
        imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
        MovingPhotoFormatConvert(movingPhotoFormat_);
        imagePattern->SetExternalDecodeFormat(imageFormat_);
        imageLayoutProperty->UpdateImageFit(imageFit);
        image->MarkModifyDone();
    }
    RegisterImageEvent();
}

void MovingPhotoPattern::MovingPhotoFormatConvert(MovingPhotoFormat format)
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "MovingPhotoFormatConvert %{public}d.", format);
    switch (format) {
        case MovingPhotoFormat::RGBA_8888:
            imageFormat_ = PixelFormat::RGBA_8888;
            break;
        case MovingPhotoFormat::NV21:
            imageFormat_ = PixelFormat::NV21;
            break;
        case MovingPhotoFormat::RGBA_1010102:
            imageFormat_ = PixelFormat::RGBA_1010102;
            break;
        case MovingPhotoFormat::YCBCR_P010:
            imageFormat_ = PixelFormat::YCBCR_P010;
            break;
        case MovingPhotoFormat::YCRCB_P010:
            imageFormat_ = PixelFormat::YCRCB_P010;
            break;
        default:
            imageFormat_ = PixelFormat::UNKNOWN;
            break;
    }
}

void MovingPhotoPattern::DynamicRangeModeConvert(DynamicRangeMode rangeMode)
{
    switch (rangeMode) {
        case DynamicRangeMode::HIGH:
            dynamicRangeMode_ = DynamicRangeMode::HIGH;
            break;
        case DynamicRangeMode::CONSTRAINT:
            dynamicRangeMode_ = DynamicRangeMode::CONSTRAINT;
            break;
        case DynamicRangeMode::STANDARD:
            dynamicRangeMode_ = DynamicRangeMode::STANDARD;
            break;
        default:
            dynamicRangeMode_ = DynamicRangeMode::HIGH;
            break;
    }
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "DynamicRangeModeConvert %{public}d.", rangeMode);
}

void MovingPhotoPattern::RegisterImageEvent()
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "MovingPhoto RegisterImageEvent start.");
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto movingPhoto = AceType::DynamicCast<MovingPhotoNode>(host);
    CHECK_NULL_VOID(movingPhoto);
    auto image = AceType::DynamicCast<FrameNode>(movingPhoto->GetImage());
    CHECK_NULL_VOID(image);
    auto imageHub = image->GetEventHub<ImageEventHub>();
    CHECK_NULL_VOID(imageHub);
    auto imageCompleteEventCallback = [weak = WeakClaim(this)](const LoadImageSuccessEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleImageCompleteEvent(info);
    };
    imageHub->SetOnComplete(imageCompleteEventCallback);
}

void MovingPhotoPattern::HandleImageCompleteEvent(const LoadImageSuccessEvent& info)
{
    auto loadingStatus = info.GetLoadingStatus();
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "HandleImageCompleteEvent start:%{public}d.", loadingStatus);
    if (loadingStatus == IMAGE_LOADING_COMPLETE) {
        FireMediaPlayerImageComplete();
    }
}

void MovingPhotoPattern::UpdateVideoNode()
{
    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto uiTaskExecutor = SingleTaskExecutor::Make(pipelineContext->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    uiTaskExecutor.PostTask(
        [weak = WeakClaim(this)]() {
            auto movingPhotoPattern = weak.Upgrade();
            CHECK_NULL_VOID(movingPhotoPattern);
            ContainerScope scope(movingPhotoPattern->instanceId_);
            movingPhotoPattern->PrepareMediaPlayer();
            movingPhotoPattern->UpdateMediaPlayerSpeed();
            movingPhotoPattern->UpdateMediaPlayerMuted();
        },
        "ArkUIMovingPhotoUpdateVideo");
}

void MovingPhotoPattern::PrepareMediaPlayer()
{
    auto layoutProperty = GetLayoutProperty<MovingPhotoLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (!layoutProperty->HasMovingPhotoUri() || !layoutProperty->HasVideoSource()) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "MovingPhoto source is null.");
        return;
    }
    if (layoutProperty->GetMovingPhotoUri().value() == uri_ &&
        layoutProperty->GetVideoSource().value() == fd_) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "MediaPlayer source has not changed.");
        return;
    }
    uri_ = layoutProperty->GetMovingPhotoUri().value();
    fd_ = layoutProperty->GetVideoSource().value();
    if (!mediaPlayer_) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "MediaPlayer is null.");
        FireMediaPlayerError();
        return;
    }
    if (!mediaPlayer_->IsMediaPlayerValid()) {
        mediaPlayer_->CreateMediaPlayer();
    }
    if (!mediaPlayer_->IsMediaPlayerValid()) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "MediaPlayer is invalid.");
        FireMediaPlayerError();
        return;
    }
    ContainerScope scope(instanceId_);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    uiTaskExecutor.PostTask(
        [weak = WeakClaim(this)] {
            auto movingPhotoPattern = weak.Upgrade();
            CHECK_NULL_VOID(movingPhotoPattern);
            movingPhotoPattern->ResetMediaPlayer();
        },
        "ArkUIMovingPhotoPrepare");
}

void MovingPhotoPattern::ResetMediaPlayer()
{
    CHECK_NULL_VOID(mediaPlayer_);
    isPrepared_ = false;
    mediaPlayer_->ResetMediaPlayer();
    RegisterMediaPlayerEvent();
    if (!mediaPlayer_->SetSourceByFd(fd_)) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "set source for MediaPlayer failed.");
        ContainerScope scope(instanceId_);
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);

        auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        uiTaskExecutor.PostTask(
            [weak = WeakClaim(this)] {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                ContainerScope scope(pattern->instanceId_);
                pattern->FireMediaPlayerError();
            },
            "ArkUIMovingPhotoReset");
        return;
    }
}

void MovingPhotoPattern::RegisterMediaPlayerEvent()
{
    if (fd_ == -1 || !mediaPlayer_) {
        return;
    }
    ContainerScope scope(instanceId_);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    auto movingPhotoPattern = WeakClaim(this);

    auto&& positionUpdatedEvent = [movingPhotoPattern, uiTaskExecutor](uint32_t currentPos) {
        uiTaskExecutor.PostTask([movingPhotoPattern, currentPos] {
            auto movingPhoto = movingPhotoPattern.Upgrade();
            CHECK_NULL_VOID(movingPhoto);
            ContainerScope scope(movingPhoto->instanceId_);
            movingPhoto->OnPlayPositionChanged(currentPos);
        }, "ArkUIMovingPhotoPositionChanged");
    };

    auto&& stateChangedEvent = [movingPhotoPattern, uiTaskExecutor](PlaybackStatus status) {
        uiTaskExecutor.PostTask([movingPhotoPattern, status] {
            auto movingPhoto = movingPhotoPattern.Upgrade();
            CHECK_NULL_VOID(movingPhoto);
            ContainerScope scope(movingPhoto->instanceId_);
            movingPhoto->OnMediaPlayerStatusChanged(status);
        }, "ArkUIMovingPhotoStatusChanged");
    };

    auto&& errorEvent = [movingPhotoPattern, uiTaskExecutor]() {
        uiTaskExecutor.PostSyncTask([movingPhotoPattern] {
            auto movingPhoto = movingPhotoPattern.Upgrade();
            CHECK_NULL_VOID(movingPhoto);
            ContainerScope scope(movingPhoto->instanceId_);
            movingPhoto->FireMediaPlayerError();
        }, "ArkUIMovingPhotoOnError");
    };

    auto&& resolutionChangeEvent = [movingPhotoPattern, uiTaskExecutor]() {
        uiTaskExecutor.PostTask([movingPhotoPattern] {
            auto movingPhoto = movingPhotoPattern.Upgrade();
            CHECK_NULL_VOID(movingPhoto);
            ContainerScope scope(movingPhoto->instanceId_);
            movingPhoto->OnResolutionChange();
        }, "ArkUIMovingPhotoResolutionChanged");
    };

    auto&& startRenderFrameEvent = [movingPhotoPattern, uiTaskExecutor]() {
        uiTaskExecutor.PostTask([movingPhotoPattern] {
            auto movingPhoto = movingPhotoPattern.Upgrade();
            CHECK_NULL_VOID(movingPhoto);
            ContainerScope scope(movingPhoto->instanceId_);
            movingPhoto->OnStartRenderFrame();
        }, "ArkUIMovingPhotoStartRender");
    };

    mediaPlayer_->RegisterMediaPlayerEvent(
        positionUpdatedEvent, stateChangedEvent, errorEvent, resolutionChangeEvent, startRenderFrameEvent);
}

void MovingPhotoPattern::PrepareSurface()
{
    if (!mediaPlayer_ || renderSurface_->IsSurfaceValid()) {
        return;
    }
    if (!SystemProperties::GetExtSurfaceEnabled()) {
        renderSurface_->SetRenderContext(renderContextForMediaPlayer_);
    }
    renderSurface_->InitSurface();
    mediaPlayer_->SetRenderSurface(renderSurface_);
    if (mediaPlayer_->SetSurface() != 0) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "prepare MediaPlayer failed.");
    }
}

void MovingPhotoPattern::UpdatePlayMode()
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingphoto UpdatePlayMode.%{public}d", isChangePlayMode_);
    if (isChangePlayMode_) {
        if (historyAutoAndRepeatLevel_ == PlaybackMode::AUTO) {
            SetAutoPlayPeriod(autoPlayPeriodStartTime_, autoPlayPeriodEndTime_);
        }
        if (autoAndRepeatLevel_ == PlaybackMode::AUTO && currentPlayStatus_ == PlaybackStatus::PREPARED) {
            ResetMediaPlayer();
        } else {
            MediaResetToPlay();
        }
        isChangePlayMode_ = false;
    }
}

void MovingPhotoPattern::HandleImageAnalyzerMode()
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingphoto HandleImageAnalyzerMode.");
    if (isEnableAnalyzer_ && autoAndRepeatLevel_ == PlaybackMode::NONE) {
        if (!imageAnalyzerManager_) {
            EnableAnalyzer(isEnableAnalyzer_);
        }
        if (imageAnalyzerManager_ && !GetAnalyzerState()) {
            StartImageAnalyzer();
        }
    }
    if (!isEnableAnalyzer_ && IsSupportImageAnalyzer() && imageAnalyzerManager_) {
        DestroyAnalyzerOverlay();
        LongPressEventModify(true);
    }
}

void MovingPhotoPattern::MediaResetToPlay()
{
    autoAndRepeatLevel_ = historyAutoAndRepeatLevel_;
    if (currentPlayStatus_ == PlaybackStatus::STOPPED) {
        mediaPlayer_->PrepareAsync();
    } else if (currentPlayStatus_ == PlaybackStatus::PLAYBACK_COMPLETE ||
        currentPlayStatus_ == PlaybackStatus::PAUSED ||
        currentPlayStatus_ == PlaybackStatus::PREPARED) {
            SelectPlaybackMode(historyAutoAndRepeatLevel_);
    }
}

void MovingPhotoPattern::FireMediaPlayerImageComplete()
{
    auto eventHub = GetEventHub<MovingPhotoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireCompleteEvent();
}

void MovingPhotoPattern::FireMediaPlayerStart()
{
    auto eventHub = GetEventHub<MovingPhotoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireStartEvent();
    if (isFastKeyUp_) {
        isFastKeyUp_ = false;
        PausePlayback();
    }
}

void MovingPhotoPattern::FireMediaPlayerStop()
{
    auto eventHub = GetEventHub<MovingPhotoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireStopEvent();
}

void MovingPhotoPattern::FireMediaPlayerPause()
{
    auto eventHub = GetEventHub<MovingPhotoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FirePauseEvent();
}

void MovingPhotoPattern::FireMediaPlayerFinish()
{
    auto eventHub = GetEventHub<MovingPhotoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireFinishEvent();
}

void MovingPhotoPattern::FireMediaPlayerError()
{
    auto eventHub = GetEventHub<MovingPhotoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireErrorEvent();
}

void MovingPhotoPattern::OnResolutionChange()
{
    if (!mediaPlayer_ || !mediaPlayer_->IsMediaPlayerValid()) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "MediaPlayer is null or invalid.");
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    SizeF videoSize =
        SizeF(static_cast<float>(mediaPlayer_->GetVideoWidth()), static_cast<float>(mediaPlayer_->GetVideoHeight()));
    auto movingPhotoLayoutProperty = host->GetLayoutProperty<MovingPhotoLayoutProperty>();
    CHECK_NULL_VOID(movingPhotoLayoutProperty);
    movingPhotoLayoutProperty->UpdateVideoSize(videoSize);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void MovingPhotoPattern::OnStartRenderFrame()
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "MediaPlayer OnStartRenderFrame.");
}

void MovingPhotoPattern::OnStartedStatusCallback()
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "MediaPlayer OnStartedStatusCallback.");
    ACE_FUNCTION_TRACE();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto movingPhoto = AceType::DynamicCast<MovingPhotoNode>(host);
    CHECK_NULL_VOID(movingPhoto);
    auto image = AceType::DynamicCast<FrameNode>(movingPhoto->GetImage());
    CHECK_NULL_VOID(image);
    StartAnimation();
}

bool MovingPhotoPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "MediaPlayer OnStartedStatusCallback.");
    if (config.skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    auto geometryNode = dirty->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);
    auto movingPhotoNodeSize = geometryNode->GetContentSize();
    auto layoutProperty = GetLayoutProperty<MovingPhotoLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto videoFrameSize = MeasureContentLayout(movingPhotoNodeSize, layoutProperty);
    if (renderContextForMediaPlayer_) {
        renderContextForMediaPlayer_->SetBounds((movingPhotoNodeSize.Width() - videoFrameSize.Width()) / HALF,
            (movingPhotoNodeSize.Height() - videoFrameSize.Height()) / HALF, videoFrameSize.Width(),
            videoFrameSize.Height());
    }

    if (IsSupportImageAnalyzer() && isEnableAnalyzer_ && autoAndRepeatLevel_ == PlaybackMode::NONE) {
        if (imageAnalyzerManager_ && !GetAnalyzerState()) {
            StartImageAnalyzer();
        } else {
            Rect tmpRect;
            auto padding = layoutProperty->CreatePaddingAndBorder();
            auto imageFit = layoutProperty->GetObjectFitValue(ImageFit::COVER);
            if (imageFit == ImageFit::COVER || imageFit == ImageFit::NONE) {
                tmpRect = Rect(padding.left.value_or(0), padding.top.value_or(0),
                               movingPhotoNodeSize.Width(), movingPhotoNodeSize.Height());
            } else {
                tmpRect = Rect(
                    (movingPhotoNodeSize.Width() - videoFrameSize.Width()) / AVERAGE_VALUE + padding.left.value_or(0),
                    (movingPhotoNodeSize.Height() - videoFrameSize.Height()) / AVERAGE_VALUE + padding.top.value_or(0),
                    videoFrameSize.Width(), videoFrameSize.Height());
            }
            contentRect_ = tmpRect;
            UpdateAnalyzerUIConfig(geometryNode);
        }
    }
    if (imageAnalyzerManager_ && !isEnableAnalyzer_) {
        DestroyAnalyzerOverlay();
        LongPressEventModify(true);
    }

    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    host->MarkNeedSyncRenderTree();
    auto movingPhoto = AceType::DynamicCast<MovingPhotoNode>(host);
    CHECK_NULL_RETURN(movingPhoto, false);
    auto video = AceType::DynamicCast<FrameNode>(movingPhoto->GetVideo());
    CHECK_NULL_RETURN(video, false);
    video->GetRenderContext()->SetClipToBounds(true);
    return false;
}

SizeF MovingPhotoPattern::CalculateFitContain(const SizeF& rawSize, const SizeF& layoutSize)
{
    if (NearZero(rawSize.Height()) || NearZero(rawSize.Width()) || NearZero(layoutSize.Height())) {
        return layoutSize;
    }
    double sourceRatio = rawSize.Width() / rawSize.Height();
    double layoutRatio = layoutSize.Width() / layoutSize.Height();
    if (sourceRatio < layoutRatio) {
        float ratio = layoutSize.Height() / rawSize.Height();
        return { rawSize.Width() * ratio, layoutSize.Height() };
    } else {
        float ratio = layoutSize.Width() / rawSize.Width();
        return { layoutSize.Width(), rawSize.Height() * ratio };
    }
}

SizeF MovingPhotoPattern::CalculateFitFill(const SizeF& layoutSize)
{
    return layoutSize;
}

SizeF MovingPhotoPattern::CalculateFitCover(const SizeF& rawSize, const SizeF& layoutSize)
{
    if (NearZero(rawSize.Height()) || NearZero(rawSize.Width()) || NearZero(layoutSize.Height())) {
        return layoutSize;
    }
    double sourceRatio = rawSize.Width() / rawSize.Height();
    double layoutRatio = layoutSize.Width() / layoutSize.Height();
    float ratio = 1.0;
    if (sourceRatio < layoutRatio) {
        ratio = static_cast<float>(layoutSize.Width() / rawSize.Width());
    } else {
        ratio = static_cast<float>(layoutSize.Height() / rawSize.Height());
    }
    return { rawSize.Width() * ratio, rawSize.Height() * ratio};
}

SizeF MovingPhotoPattern::CalculateFitNone(const SizeF& rawSize)
{
    return rawSize;
}

SizeF MovingPhotoPattern::CalculateFitScaleDown(const SizeF& rawSize, const SizeF& layoutSize)
{
    if ((rawSize.Width() <= layoutSize.Width()) && (rawSize.Height() <= layoutSize.Height())) {
        return CalculateFitNone(rawSize);
    } else {
        return CalculateFitContain(rawSize, layoutSize);
    }
}

SizeF MovingPhotoPattern::CalculateFitAuto(const SizeF& rawSize, const SizeF& layoutSize)
{
    if (NearZero(rawSize.Width()) || NearZero(rawSize.Height())) {
        return layoutSize;
    }
    if ((rawSize.Width() <= layoutSize.Width()) && (rawSize.Height() <= layoutSize.Height())) {
        double widthRatio = layoutSize.Width() / rawSize.Width();
        double heightRatio = layoutSize.Height() / rawSize.Height();
        float ratio = static_cast<float>(std::min(widthRatio, heightRatio));
        return { rawSize.Width() * ratio, rawSize.Height() * ratio };
    } else if ((rawSize.Width() > layoutSize.Width()) && (rawSize.Height() <= layoutSize.Height())) {
        return CalculateFitContain(rawSize, layoutSize);
    } else {
        return CalculateFitCover(rawSize, layoutSize);
    }
}

SizeF MovingPhotoPattern::GetRawImageSize()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, SizeF(-1, -1));
    auto movingPhoto = AceType::DynamicCast<MovingPhotoNode>(host);
    CHECK_NULL_RETURN(movingPhoto, SizeF(-1, -1));
    auto image = AceType::DynamicCast<FrameNode>(movingPhoto->GetImage());
    CHECK_NULL_RETURN(image, SizeF(-1, -1));
    auto imagePattern = image->GetPattern<ImagePattern>();
    CHECK_NULL_RETURN(image, SizeF(-1, -1));
    return imagePattern->GetRawImageSize();
}

SizeF MovingPhotoPattern::MeasureContentLayout(const SizeF& layoutSize,
    const RefPtr<MovingPhotoLayoutProperty>& layoutProperty)
{
    if (!layoutProperty || !layoutProperty->HasVideoSize()) {
        return layoutSize;
    }

    auto rawImageSize = GetRawImageSize();
    auto imageFit = layoutProperty->GetObjectFitValue(ImageFit::COVER);
    SizeF contentSize = { 0.0, 0.0 };
    switch (imageFit) {
        case ImageFit::CONTAIN:
            contentSize = CalculateFitContain(rawImageSize, layoutSize);
            break;
        case ImageFit::FILL:
            contentSize = CalculateFitFill(layoutSize);
            break;
        case ImageFit::COVER:
            contentSize = CalculateFitCover(rawImageSize, layoutSize);
            break;
        case ImageFit::NONE:
            contentSize = CalculateFitNone(rawImageSize);
            break;
        case ImageFit::SCALE_DOWN:
            contentSize = CalculateFitScaleDown(rawImageSize, layoutSize);
            break;
        default:
            contentSize = CalculateFitAuto(rawImageSize, layoutSize);
    }

    return contentSize;
}

void MovingPhotoPattern::OnMediaPlayerStatusChanged(PlaybackStatus status)
{
    currentPlayStatus_ = status;
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "Player current status is %{public}d.", status);
    switch (status) {
        case PlaybackStatus::ERROR:
            TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "Player current status is ERROR.");
            FireMediaPlayerError();
            break;
        case PlaybackStatus::IDLE:
            TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "Player current status is IDLE.");
            break;
        case PlaybackStatus::INITIALIZED:
            TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "Player current status is INITIALIZED.");
            OnMediaPlayerInitialized();
            break;
        case PlaybackStatus::PREPARED:
            TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "Player current status is PREPARED.");
            OnMediaPlayerPrepared();
            break;
        case PlaybackStatus::STARTED:
            TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "Player current status is STARTED.");
            OnStartedStatusCallback();
            FireMediaPlayerStart();
            break;
        case PlaybackStatus::PAUSED:
            TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "Player current status is PAUSED.");
            FireMediaPlayerPause();
            break;
        case PlaybackStatus::STOPPED:
            TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "Player current status is STOPPED.");
            OnMediaPlayerStoped();
            break;
        case PlaybackStatus::PLAYBACK_COMPLETE:
            TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "Player current status is PLAYBACK_COMPLETE.");
            OnMediaPlayerCompletion();
            break;
        case PlaybackStatus::NONE:
            TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "Player current status is NONE.");
            break;
        default:
            TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "Invalid player status.");
            break;
    }
}

void MovingPhotoPattern::OnMediaPlayerInitialized()
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "MediaPlayer OnMediaPlayerInitialized.");
    if (!isSetAutoPlayPeriod_ && autoAndRepeatLevel_ == PlaybackMode::AUTO) {
        isSetAutoPlayPeriod_ = true;
        SetAutoPlayPeriod(autoPlayPeriodStartTime_, autoPlayPeriodEndTime_);
    }
    PrepareSurface();
    if (mediaPlayer_->PrepareAsync() != PREPARE_RETURN) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "prepare MediaPlayer failed.");
    }
}

void MovingPhotoPattern::OnMediaPlayerPrepared()
{
    ContainerScope scope(instanceId_);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    if (!mediaPlayer_ || !mediaPlayer_->IsMediaPlayerValid()) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "MediaPlayer is null or invalid.");
        return;
    }
    isPrepared_ = true;
    Size videoSize = Size(mediaPlayer_->GetVideoWidth(), mediaPlayer_->GetVideoHeight());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto videoLayoutProperty = host->GetLayoutProperty<MovingPhotoLayoutProperty>();
    CHECK_NULL_VOID(videoLayoutProperty);
    CHECK_NULL_VOID(mediaPlayer_);
    videoLayoutProperty->UpdateVideoSize(
        SizeF(static_cast<float>(videoSize.Width()), static_cast<float>(videoSize.Height())));
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    mediaPlayer_->SetParameter(VIDEO_SCALE, 1);
    UpdateMediaPlayerSpeed();
    UpdateMediaPlayerMuted();
    VisiblePlayback();
}

void MovingPhotoPattern::OnMediaPlayerStoped()
{
    isPlayByController_ = false;
    FireMediaPlayerStop();
}

void MovingPhotoPattern::OnMediaPlayerCompletion()
{
    if (!isRefreshMovingPhotoPlaying_) {
        if (isPlayByController_ || autoAndRepeatLevel_ != PlaybackMode::NONE) {
            isPlayByController_ = false;
            StopAnimation();
        }
    }
    
    FireMediaPlayerFinish();
}

void MovingPhotoPattern::HideImageNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto movingPhoto = AceType::DynamicCast<MovingPhotoNode>(host);
    CHECK_NULL_VOID(movingPhoto);
    auto image = AceType::DynamicCast<FrameNode>(movingPhoto->GetImage());
    CHECK_NULL_VOID(image);
    auto imageLayoutProperty = image->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    imageLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
    image->MarkModifyDone();
}

void MovingPhotoPattern::VisiblePlayback()
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingphoto VisiblePlayback.");
    if (!isVisible_) {
        return;
    }
    if (historyAutoAndRepeatLevel_ != PlaybackMode::NONE &&
        autoAndRepeatLevel_ == PlaybackMode::NONE) {
        SelectPlaybackMode(historyAutoAndRepeatLevel_);
    } else {
        SelectPlaybackMode(autoAndRepeatLevel_);
    }
}

void MovingPhotoPattern::SelectPlaybackMode(PlaybackMode mode)
{
    if (mode == PlaybackMode::REPEAT) {
        StartRepeatPlay();
    } else if (mode == PlaybackMode::AUTO) {
        StartAutoPlay();
    }
}

void MovingPhotoPattern::StartPlayback()
{
    if (currentPlayStatus_ == PlaybackStatus::STARTED || !isPrepared_) {
        return;
    }
    if (IsRefreshMovingPhotoReturn(isRefreshMovingPhoto_)) {
        TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "HandleTouchEvent IsRefreshMovingPhotoReturn.");
        return;
    }
    if (currentPlayStatus_ == PlaybackStatus::STOPPED) {
        mediaPlayer_->PrepareAsync();
    }
    isPlayByController_ = true;
    isFastKeyUp_ = false;
    if (isSetAutoPlayPeriod_ && (currentPlayStatus_ == PlaybackStatus::PLAYBACK_COMPLETE ||
        currentPlayStatus_ == PlaybackStatus::PAUSED)) {
        int32_t duration = DURATION_FLAG;
        mediaPlayer_->GetDuration(duration);
        TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "StartPlayback duration:%{public}d.",
            duration);
        SetAutoPlayPeriod(PERIOD_START, duration);
    }
    Start();
}

void MovingPhotoPattern::StartAnimation()
{
    if (historyAutoAndRepeatLevel_ == PlaybackMode::REPEAT) {
        if (!isFirstRepeatPlay_) {
            return;
        }
        isFirstRepeatPlay_ = false;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto movingPhoto = AceType::DynamicCast<MovingPhotoNode>(host);
    CHECK_NULL_VOID(movingPhoto);
    auto image = AceType::DynamicCast<FrameNode>(movingPhoto->GetImage());
    CHECK_NULL_VOID(image);
    auto imageRsContext = image->GetRenderContext();
    CHECK_NULL_VOID(imageRsContext);
    auto video = AceType::DynamicCast<FrameNode>(movingPhoto->GetVideo());
    CHECK_NULL_VOID(video);
    auto videoRsContext = video->GetRenderContext();
    CHECK_NULL_VOID(videoRsContext);

    imageRsContext->UpdateOpacity(1.0);
    imageRsContext->UpdateTransformScale({NORMAL_SCALE, NORMAL_SCALE});
    videoRsContext->UpdateTransformScale({NORMAL_SCALE, NORMAL_SCALE});
    auto movingPhotoPattern = WeakClaim(this);
    AnimationOption animationOption;
    animationOption.SetDuration(ANIMATION_DURATION_400);
    animationOption.SetCurve(Curves::FRICTION);
    animationOption.SetOnFinishEvent([movingPhotoPattern]() {
        auto movingPhoto = movingPhotoPattern.Upgrade();
        TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingphoto StartAnimation OnFinishEvent.");
        CHECK_NULL_VOID(movingPhoto);
        if (movingPhoto->currentPlayStatus_ == PlaybackStatus::PAUSED
            || movingPhoto->currentPlayStatus_ == PlaybackStatus::STOPPED
            || !movingPhoto->startAnimationFlag_) {
            return;
        }
        movingPhoto->HideImageNode();
    });
    startAnimationFlag_ = true;
    AnimationUtils::Animate(animationOption,
        [imageRsContext, videoRsContext, repeatFlag = historyAutoAndRepeatLevel_]() {
            imageRsContext->UpdateOpacity(0.0);
            imageRsContext->UpdateTransformScale({ZOOM_IN_SCALE, ZOOM_IN_SCALE});
            if (repeatFlag == PlaybackMode::REPEAT) {
                videoRsContext->UpdateTransformScale({NORMAL_SCALE, NORMAL_SCALE});
            } else {
                videoRsContext->UpdateTransformScale({ZOOM_IN_SCALE, ZOOM_IN_SCALE});
            }
        }, animationOption.GetOnFinishEvent());
}

void MovingPhotoPattern::StopPlayback()
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingphoto StopPlayback");
    isFastKeyUp_ = false;
    isPlayByController_ = false;
    Pause();
    autoAndRepeatLevel_ = PlaybackMode::NONE;
    if (historyAutoAndRepeatLevel_ != PlaybackMode::REPEAT) {
        StopAnimation();
    }
}

void MovingPhotoPattern::PausePlayback()
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingphoto PausePlayback");
    isFastKeyUp_ = false;
    if (currentPlayStatus_ != PlaybackStatus::STARTED || !isPrepared_) {
        return;
    }
    if (IsRefreshMovingPhotoReturn(isRefreshMovingPhotoPlaying_)) {
        TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "HandleTouchEvent IsRefreshMovingPhotoReturn.");
        return;
    }
    isPlayByController_ = false;
    Pause();
    StopAnimation();
}

void MovingPhotoPattern::RefreshMovingPhoto()
{
    if (uri_ == "") {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "movingphoto RefreshMovingPhoto uri is null.");
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = GetLayoutProperty<MovingPhotoLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto dataProvider = AceType::DynamicCast<DataProviderManagerStandard>(pipeline->GetDataProviderManager());
    CHECK_NULL_VOID(dataProvider);
    if (!layoutProperty->HasMovingPhotoUri() || !layoutProperty->HasVideoSource()) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "movingphoto source is null.");
        return;
    }
    std::string imageSrc = dataProvider->GetMovingPhotoImageUri(uri_);
    imageSrc += "?date_modified" + std::to_string(GetMicroTickCount());
    ImageSourceInfo src;
    src.SetSrc(imageSrc);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(MovingPhotoLayoutProperty, ImageSourceInfo, src, host);
    UpdateImageNode();
    fd_ = dataProvider->ReadMovingPhotoVideo(uri_);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(MovingPhotoLayoutProperty, VideoSource, fd_, host);
    isRefreshMovingPhoto_ = true;
    ResetMediaPlayer();
    if (historyAutoAndRepeatLevel_ == PlaybackMode::AUTO) {
        autoAndRepeatLevel_ = PlaybackMode::AUTO;
    }
    if (IsSupportImageAnalyzer() && isEnableAnalyzer_ && imageAnalyzerManager_) {
        UpdateAnalyzerOverlay();
    }
}

void MovingPhotoPattern::StopAnimation()
{
    startAnimationFlag_ = false;
    if (historyAutoAndRepeatLevel_ == PlaybackMode::REPEAT) {
        StopAnimationCallback();
        return;
    }
    if (isRefreshMovingPhotoPlaying_) {
        isRefreshMovingPhotoPlaying_ = false;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto movingPhoto = AceType::DynamicCast<MovingPhotoNode>(host);
    CHECK_NULL_VOID(movingPhoto);
    auto image = AceType::DynamicCast<FrameNode>(movingPhoto->GetImage());
    CHECK_NULL_VOID(image);
    auto imageLayoutProperty = image->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    auto imageRsContext = image->GetRenderContext();
    CHECK_NULL_VOID(imageRsContext);
    auto video = AceType::DynamicCast<FrameNode>(movingPhoto->GetVideo());
    CHECK_NULL_VOID(video);
    auto videoRsContext = video->GetRenderContext();
    CHECK_NULL_VOID(videoRsContext);
    videoRsContext->UpdateTransformScale({ZOOM_IN_SCALE, ZOOM_IN_SCALE});
    video->MarkModifyDone();

    imageLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    imageRsContext->UpdateOpacity(0.0);
    imageRsContext->UpdateTransformScale({ZOOM_IN_SCALE, ZOOM_IN_SCALE});
    image->MarkModifyDone();
    auto movingPhotoPattern = WeakClaim(this);
    AnimationOption option;
    option.SetDuration(ANIMATION_DURATION_300);
    option.SetCurve(Curves::FRICTION);
    option.SetOnFinishEvent([movingPhotoPattern]() {
        auto movingPhoto = movingPhotoPattern.Upgrade();
        CHECK_NULL_VOID(movingPhoto);
        movingPhoto->StopAnimationCallback();
    });
    AnimationUtils::Animate(option, [imageRsContext, videoRsContext]() {
            imageRsContext->UpdateOpacity(1.0);
            imageRsContext->UpdateTransformScale({NORMAL_SCALE, NORMAL_SCALE});
            videoRsContext->UpdateTransformScale({NORMAL_SCALE, NORMAL_SCALE});
        }, option.GetOnFinishEvent());
}

void MovingPhotoPattern::StopAnimationCallback()
{
    Seek(0);
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "StopAnimation OnFinishEvent:%{public}d.", autoAndRepeatLevel_);
    if (needUpdateImageNode_) {
        UpdateImageNode();
        needUpdateImageNode_ = false;
    }
    if (autoAndRepeatLevel_ == PlaybackMode::REPEAT) {
        StartRepeatPlay();
    } else if (autoAndRepeatLevel_ == PlaybackMode::AUTO) {
        autoAndRepeatLevel_ = PlaybackMode::NONE;
    }
    if (historyAutoAndRepeatLevel_ == PlaybackMode::AUTO) {
        HandleImageAnalyzerMode();
    }
}

void MovingPhotoPattern::AutoPlay(bool isAutoPlay)
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingphoto AutoPlay: %{public}d.", isAutoPlay);
    if (isAutoPlay) {
        if (historyAutoAndRepeatLevel_ == PlaybackMode::AUTO) {
            return;
        }
        isChangePlayMode_ = true;
        if (autoAndRepeatLevel_ != PlaybackMode::REPEAT) {
            historyAutoAndRepeatLevel_ = PlaybackMode::AUTO;
            autoAndRepeatLevel_ = PlaybackMode::AUTO;
            if (!isSetAutoPlayPeriod_ && (currentPlayStatus_ == PlaybackStatus::PLAYBACK_COMPLETE ||
                currentPlayStatus_ == PlaybackStatus::PAUSED)) {
                isSetAutoPlayPeriod_ = true;
                SetAutoPlayPeriod(autoPlayPeriodStartTime_, autoPlayPeriodEndTime_);
            }
        }
    }
}

void MovingPhotoPattern::StartAutoPlay()
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingphoto StartAutoPlay in.");
    isFastKeyUp_ = false;
    if (!mediaPlayer_ || !mediaPlayer_->IsMediaPlayerValid()) {
        return;
    }

    if (currentPlayStatus_ == PlaybackStatus::STOPPED) {
        mediaPlayer_->PrepareAsync();
    }
    Start();
}

void MovingPhotoPattern::StartRepeatPlay()
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingphoto StartRepeatPlay in.");
    isFastKeyUp_ = false;
    if (!mediaPlayer_ || !mediaPlayer_->IsMediaPlayerValid()) {
        return;
    }

    if (currentPlayStatus_ == PlaybackStatus::STOPPED) {
        mediaPlayer_->PrepareAsync();
    }
    if (!isFirstRepeatPlay_ && isSetAutoPlayPeriod_) {
        int32_t duration = DURATION_FLAG;
        mediaPlayer_->GetDuration(duration);
        SetAutoPlayPeriod(PERIOD_START, duration);
    }
    Start();
}

void MovingPhotoPattern::RepeatPlay(bool isRepeatPlay)
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingphoto RepeatPlay status: %{public}d.", isRepeatPlay);
    if (isRepeatPlay && historyAutoAndRepeatLevel_ != PlaybackMode::REPEAT) {
        isChangePlayMode_ = true;
        isFirstRepeatPlay_ = true;
    }
    if (!isRepeatPlay && historyAutoAndRepeatLevel_ == PlaybackMode::REPEAT) {
        isChangePlayMode_ = true;
        historyAutoAndRepeatLevel_ = PlaybackMode::NONE;
        Pause();
        StopAnimation();
    }
    if (isRepeatPlay) {
        historyAutoAndRepeatLevel_ = PlaybackMode::REPEAT;
        autoAndRepeatLevel_ = PlaybackMode::REPEAT;
    }
}

void MovingPhotoPattern::AutoPlayPeriod(int64_t startTime, int64_t endTime)
{
    if (startTime >= VIDEO_PLAYTIME_START_POSITION && startTime < endTime) {
        TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "MediaPlayer set Period.");
        autoPlayPeriodStartTime_ = startTime;
        autoPlayPeriodEndTime_ = endTime;
    }
}

void MovingPhotoPattern::SetAutoPlayPeriod(int64_t startTime, int64_t endTime)
{
    if (startTime < VIDEO_PLAYTIME_START_POSITION || startTime >= endTime) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "MediaPlayer SetAutoPlayPeriod error.");
        return;
    }
    if (!mediaPlayer_ || !mediaPlayer_->IsMediaPlayerValid()) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "MediaPlayer is null or invalid.");
        return;
    }

    ContainerScope scope(instanceId_);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);

    mediaPlayer_->SetPlayRange(startTime, endTime);
}

void MovingPhotoPattern::HandleImageAnalyzerPlayCallBack()
{
    TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "HandleImageAnalyzerPlayCallBack start.");
    isFastKeyUp_ = false;
    if (currentPlayStatus_ == PlaybackStatus::STARTED || !isPrepared_ || isPlayByController_) {
        return;
    }
    if (IsRefreshMovingPhotoReturn(isRefreshMovingPhoto_)) {
        TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "HandleTouchEvent IsRefreshMovingPhotoReturn.");
        return;
    }
    if (!mediaPlayer_ || !mediaPlayer_->IsMediaPlayerValid()) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "MediaPlayer is null or invalid.");
        FireMediaPlayerError();
        return;
    }
    if (currentPlayStatus_ == PlaybackStatus::STOPPED) {
        mediaPlayer_->PrepareAsync();
    }
    if (isSetAutoPlayPeriod_ && (currentPlayStatus_ == PlaybackStatus::PLAYBACK_COMPLETE ||
        currentPlayStatus_ == PlaybackStatus::PAUSED)) {
        int32_t duration = DURATION_FLAG;
        mediaPlayer_->GetDuration(duration);
        SetAutoPlayPeriod(PERIOD_START, duration);
    }
    Start();
}

void MovingPhotoPattern::Start()
{
    TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "movingphoto start play.");
    if (!mediaPlayer_ || !mediaPlayer_->IsMediaPlayerValid()) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "MediaPlayer is null or invalid.");
        return;
    }
    if (isRefreshMovingPhoto_) {
        isRefreshMovingPhoto_ = false;
    }
    if (currentPlayStatus_ == PlaybackStatus::STOPPED) {
        mediaPlayer_->PrepareAsync();
    }
    ContainerScope scope(instanceId_);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);

    auto platformTask = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::BACKGROUND);
    platformTask.PostTask(
        [weak = WeakClaim(RawPtr(mediaPlayer_))] {
            auto mediaPlayer = weak.Upgrade();
            CHECK_NULL_VOID(mediaPlayer);
            mediaPlayer->Play();
        },
        "ArkUIMovingPhotoStartPlay");
}

void MovingPhotoPattern::Pause()
{
    if (!mediaPlayer_ || !mediaPlayer_->IsMediaPlayerValid()) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "MediaPlayer is null or invalid.");
        return;
    }
    ContainerScope scope(instanceId_);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    
    auto platformTask = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::BACKGROUND);
    platformTask.PostTask(
        [weak = WeakClaim(RawPtr(mediaPlayer_))] {
            auto mediaPlayer = weak.Upgrade();
            CHECK_NULL_VOID(mediaPlayer);
            mediaPlayer->Pause();
        },
        "ArkUIMovingPhotoPausePlay");
}

void MovingPhotoPattern::Stop()
{
    if (!mediaPlayer_ || !mediaPlayer_->IsMediaPlayerValid()) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "MediaPlayer is null or invalid.");
        return;
    }
    ContainerScope scope(instanceId_);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    
    auto platformTask = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::BACKGROUND);
    platformTask.PostTask(
        [weak = WeakClaim(RawPtr(mediaPlayer_))] {
            auto mediaPlayer = weak.Upgrade();
            CHECK_NULL_VOID(mediaPlayer);
            mediaPlayer->Stop();
        },
        "ArkUIMovingPhotoStopPlay");
}

void MovingPhotoPattern::Seek(int32_t position)
{
    if (!mediaPlayer_ || !mediaPlayer_->IsMediaPlayerValid()) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "MediaPlayer is null or invalid.");
        return;
    }
    ContainerScope scope(instanceId_);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    
    auto platformTask = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::BACKGROUND);
    platformTask.PostTask(
        [weak = WeakClaim(RawPtr(mediaPlayer_)), pos = position] {
            auto mediaPlayer = weak.Upgrade();
            CHECK_NULL_VOID(mediaPlayer);
            mediaPlayer->Seek(pos, SeekMode::SEEK_PREVIOUS_SYNC);
        },
        "ArkUIMovingPhotoSeek");
}

void MovingPhotoPattern::UpdateMediaPlayerSpeed()
{
    if (!mediaPlayer_ || !mediaPlayer_->IsMediaPlayerValid()) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "MediaPlayer is null or invalid.");
        return;
    }
    ContainerScope scope(instanceId_);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto platformTask = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::BACKGROUND);
    platformTask.PostTask(
        [weak = WeakClaim(RawPtr(mediaPlayer_))] {
            auto mediaPlayer = weak.Upgrade();
            CHECK_NULL_VOID(mediaPlayer);
            mediaPlayer->SetPlaybackSpeed(static_cast<float>(NORMAL_PLAY_SPEED));
        },
        "ArkUIMovingPhotoUpdateSpeed");
}

void MovingPhotoPattern::UpdateMediaPlayerMuted()
{
    if (!mediaPlayer_ || !mediaPlayer_->IsMediaPlayerValid()) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "MediaPlayer is null or invalid.");
        return;
    }
    ContainerScope scope(instanceId_);
    float volume = isMuted_ ? 0.0f : 1.0f;
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto platformTask = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::BACKGROUND);
    platformTask.PostTask(
        [weak = WeakClaim(RawPtr(mediaPlayer_)), videoVolume = volume] {
            auto mediaPlayer = weak.Upgrade();
            CHECK_NULL_VOID(mediaPlayer);
            mediaPlayer->SetVolume(videoVolume, videoVolume);
        },
        "ArkUIMovingPhotoUpdateMuted");
}

void MovingPhotoPattern::OnAreaChangedInner()
{
    if (!SystemProperties::GetExtSurfaceEnabled()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto videoNodeSize = geometryNode->GetContentSize();
    auto layoutProperty = GetLayoutProperty<MovingPhotoLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto videoFrameSize = MeasureContentLayout(videoNodeSize, layoutProperty);
    auto transformRelativeOffset = host->GetTransformRelativeOffset();

    Rect rect = Rect(transformRelativeOffset.GetX() + (videoNodeSize.Width() - videoFrameSize.Width()) / HALF,
        transformRelativeOffset.GetY() + (videoNodeSize.Height() - videoFrameSize.Height()) / HALF,
        videoFrameSize.Width(), videoFrameSize.Height());
    if (renderSurface_ && (rect != lastBoundsRect_)) {
        renderSurface_->SetExtSurfaceBounds(rect.Left(), rect.Top(), rect.Width(), rect.Height());
        lastBoundsRect_ = rect;
    }
}

void MovingPhotoPattern::OnVisibleChange(bool isVisible)
{
    CHECK_NULL_VOID(mediaPlayer_);
    if (!isVisible) {
        StopPlayback();
    }
}

void MovingPhotoPattern::OnWindowHide()
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingphoto OnWindowHide.");
    if (historyAutoAndRepeatLevel_ == PlaybackMode::AUTO) {
        PausePlayback();
    } else if (historyAutoAndRepeatLevel_ == PlaybackMode::REPEAT) {
        StopPlayback();
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto movingPhoto = AceType::DynamicCast<MovingPhotoNode>(host);
    CHECK_NULL_VOID(movingPhoto);
    auto image = AceType::DynamicCast<FrameNode>(movingPhoto->GetImage());
    CHECK_NULL_VOID(image);
    auto imageLayoutProperty = image->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    imageLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    auto rsContext = image->GetRenderContext();
    CHECK_NULL_VOID(rsContext);
    rsContext->UpdateOpacity(1.0);
    image->MarkModifyDone();
}

void MovingPhotoPattern::OnWindowShow()
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingphoto OnWindowShow.");
    CHECK_NULL_VOID(mediaPlayer_);
    if (autoAndRepeatLevel_ == PlaybackMode::REPEAT && currentPlayStatus_ == PlaybackStatus::STOPPED) {
        mediaPlayer_->PrepareAsync();
    }
}

void MovingPhotoPattern::RegisterVisibleAreaChange()
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingphoto RegisterVisibleAreaChange.");
    if (hasVisibleChangeRegistered_) {
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipeline);
    auto callback = [weak = WeakClaim(this)](bool visible, double ratio) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->isVisible_ = visible;
        pattern->VisibleAreaCallback(visible);
    };
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    std::vector<double> ratioList = {1.0};
    pipeline->AddVisibleAreaChangeNode(host, ratioList, callback, false);
    hasVisibleChangeRegistered_ = true;
}

void MovingPhotoPattern::VisibleAreaCallback(bool visible)
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingphoto VisibleAreaCallback:%{public}d.", visible);
    if (visible) {
        if (historyAutoAndRepeatLevel_ == PlaybackMode::AUTO &&
            (currentPlayStatus_ == PlaybackStatus::PLAYBACK_COMPLETE ||
            currentPlayStatus_ == PlaybackStatus::PAUSED)) {
            isSetAutoPlayPeriod_ = true;
            SetAutoPlayPeriod(autoPlayPeriodStartTime_, autoPlayPeriodEndTime_);
        }
        MediaResetToPlay();
    } else {
        if (historyAutoAndRepeatLevel_ == PlaybackMode::AUTO) {
            PausePlayback();
        } else if (historyAutoAndRepeatLevel_ == PlaybackMode::REPEAT) {
            StopPlayback();
        }
        if (isRefreshMovingPhoto_) {
            isSetAutoPlayPeriod_ = false;
            ResetMediaPlayer();
        }
    }
}

void MovingPhotoPattern::EnableAnalyzer(bool enabled)
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingphoto EnableAnalyzer:%{public}d.", enabled);
    isEnableAnalyzer_ = enabled;
    if (!isEnableAnalyzer_) {
        DestroyAnalyzerOverlay();
        LongPressEventModify(true);
        return;
    }

    CHECK_NULL_VOID(!imageAnalyzerManager_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    imageAnalyzerManager_ = std::make_shared<ImageAnalyzerManager>(host, ImageAnalyzerHolder::MOVINGPHOTO);
}

void MovingPhotoPattern::SetImageAIOptions(void* options)
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingphoto SetImageAIOptions");
    if (!imageAnalyzerManager_) {
        imageAnalyzerManager_ = std::make_shared<ImageAnalyzerManager>(GetHost(), ImageAnalyzerHolder::MOVINGPHOTO);
    }
    CHECK_NULL_VOID(imageAnalyzerManager_);
    imageAnalyzerManager_->SetImageAIOptions(options);
}

bool MovingPhotoPattern::IsSupportImageAnalyzer()
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingphoto IsSupportImageAnalyzer");
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto layoutProperty = host->GetLayoutProperty<MovingPhotoLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    CHECK_NULL_RETURN(imageAnalyzerManager_, false);
    return imageAnalyzerManager_->IsSupportImageAnalyzerFeature();
}

bool MovingPhotoPattern::ShouldUpdateImageAnalyzer()
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingphoto ShouldUpdateImageAnalyzer");
    auto layoutProperty = GetLayoutProperty<MovingPhotoLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    const auto& constraint = layoutProperty->GetCalcLayoutConstraint();
    if (!constraint || !constraint->selfIdealSize.has_value() || !constraint->selfIdealSize->IsValid()) {
        return false;
    }
    auto selfIdealSize = constraint->selfIdealSize;
    if (!selfIdealSize->PercentWidth() && !selfIdealSize->PercentHeight()) {
        return false;
    }
    auto imageFit = layoutProperty->GetObjectFit().value_or(ImageFit::COVER);
    if (imageFit != ImageFit::COVER && imageFit != ImageFit::NONE) {
        return false;
    }
    return true;
}

void MovingPhotoPattern::StartImageAnalyzer()
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingphoto StartImageAnalyzer");
    if (!IsSupportImageAnalyzer() || !imageAnalyzerManager_) {
        return;
    }

    if (imageAnalyzerManager_->IsOverlayCreated()) {
        DestroyAnalyzerOverlay();
        LongPressEventModify(true);
    }

    ContainerScope scope(instanceId_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    uiTaskExecutor.PostDelayedTask([weak = WeakClaim(this)] {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->CreateAnalyzerOverlay();
        }, ANALYZER_DELAY_TIME, "ArkUIMovingPhotoCreateAnalyzerOverlay");
    LongPressEventModify(false);
}

void MovingPhotoPattern::CreateAnalyzerOverlay()
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingphoto CreateAnalyzerOverlay");
    CHECK_NULL_VOID(imageAnalyzerManager_);
    if (imageAnalyzerManager_->IsOverlayCreated()) {
        return;
    }
    GetPixelMap();
    int64_t coverPosition = GetUriCoverPosition();
    auto onCanPlay = [weak = AceType::WeakClaim(this)](bool canPlay) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleAnalyzerPlayEvent(canPlay);
    };
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto movingPhotoNodeSize = geometryNode->GetContentSize();
    MovingPhotoAnalyzerInfo info = {uri_, coverPosition,
                                    movingPhotoNodeSize.Width(),
                                    movingPhotoNodeSize.Height()};
    imageAnalyzerManager_->SetOnCanPlayCallback(std::move(onCanPlay));
    imageAnalyzerManager_->CreateMovingPhotoAnalyzerOverlay(pixelMap_, info);
}

void MovingPhotoPattern::StartUpdateImageAnalyzer()
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingphoto StartUpdateImageAnalyzer");
    CHECK_NULL_VOID(imageAnalyzerManager_);
    if (!imageAnalyzerManager_->IsOverlayCreated()) {
        return;
    }

    UpdateOverlayVisibility(VisibleType::GONE);
    ContainerScope scope(instanceId_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    uiTaskExecutor.PostDelayedTask([weak = WeakClaim(this)] {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (!pattern->isContentSizeChanged_) {
            return;
        }
        pattern->UpdateAnalyzerOverlay();
        pattern->isContentSizeChanged_ = false;
        }, ANALYZER_CAPTURE_DELAY_TIME, "ArkUIMovingPhotoUpdateAnalyzerOverlay");
    isContentSizeChanged_ = true;
}

void MovingPhotoPattern::UpdateAnalyzerOverlay()
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingphoto UpdateAnalyzerOverlay");
    CHECK_NULL_VOID(imageAnalyzerManager_);
    if (!IsSupportImageAnalyzer() || !imageAnalyzerManager_->IsOverlayCreated()) {
        return;
    }
    GetPixelMap();
    int64_t coverPosition = GetUriCoverPosition();
    UpdateOverlayVisibility(VisibleType::VISIBLE);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto movingPhotoNodeSize = geometryNode->GetContentSize();
    MovingPhotoAnalyzerInfo info = {uri_, coverPosition,
                                    movingPhotoNodeSize.Width(),
                                    movingPhotoNodeSize.Height()};
    imageAnalyzerManager_->UpdateMovingPhotoAnalyzerOverlay(pixelMap_, info);
}

void MovingPhotoPattern::UpdateAnalyzerUIConfig(const RefPtr<NG::GeometryNode>& geometryNode)
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingphoto UpdateAnalyzerUIConfig");
    if (IsSupportImageAnalyzer()) {
        auto layoutProperty = GetLayoutProperty<MovingPhotoLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        auto padding  = layoutProperty->CreatePaddingAndBorder();
        OffsetF contentOffset = { contentRect_.Left() - padding.left.value_or(0),
                                  contentRect_.Top() - padding.top.value_or(0) };
        PixelMapInfo info = { contentRect_.GetSize().Width(), contentRect_.GetSize().Height(), contentOffset };
        CHECK_NULL_VOID(imageAnalyzerManager_);
        imageAnalyzerManager_->UpdateAnalyzerUIConfig(geometryNode, info);
    }
}

void MovingPhotoPattern::DestroyAnalyzerOverlay()
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingphoto DestroyAnalyzerOverlay");
    CHECK_NULL_VOID(imageAnalyzerManager_);
    imageAnalyzerManager_->DestroyAnalyzerOverlay();
}

bool MovingPhotoPattern::GetAnalyzerState()
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingphoto GetAnalyzerState");
    CHECK_NULL_RETURN(imageAnalyzerManager_, false);
    return imageAnalyzerManager_->IsOverlayCreated();
}

void MovingPhotoPattern::UpdateOverlayVisibility(VisibleType type)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto overlayNode = host->GetOverlayNode();
    CHECK_NULL_VOID(overlayNode);
    auto prop = overlayNode->GetLayoutProperty();
    CHECK_NULL_VOID(prop);
    prop->UpdateVisibility(type);
}

void MovingPhotoPattern::GetPixelMap()
{
    auto layoutProperty = GetLayoutProperty<MovingPhotoLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (!layoutProperty->HasMovingPhotoUri() || !layoutProperty->HasVideoSource()) {
        TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "GetPixelMap MovingPhoto source is null.");
        return;
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto dataProvider = AceType::DynamicCast<DataProviderManagerStandard>(pipeline->GetDataProviderManager());
    CHECK_NULL_VOID(dataProvider);
    std::string imageSrc = dataProvider->GetMovingPhotoImagePath(uri_);
    std::string thumbnailUrl = uri_ + THUMBNAIL_MEDIUM_JOINT + imageSrc;
    void* pixelMapMediauniquePtr = dataProvider->GetDataProviderThumbnailResFromUri(thumbnailUrl);
    CHECK_NULL_VOID(pixelMapMediauniquePtr);
    auto pixelMap = PixelMap::CreatePixelMapFromDataAbility(pixelMapMediauniquePtr);
    CHECK_NULL_VOID(pixelMap);
    pixelMap_ = pixelMap;
}

int64_t MovingPhotoPattern::GetUriCoverPosition()
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, -1);
    auto dataProvider = AceType::DynamicCast<DataProviderManagerStandard>(pipeline->GetDataProviderManager());
    CHECK_NULL_RETURN(dataProvider, -1);
    std::vector<std::string> columns = {COVER_POSITION};
    auto result = dataProvider->GetMovingPhotoCoverPosition(IMAGE_URI, uri_, columns);
    return result;
}

void MovingPhotoPattern::HandleAnalyzerPlayEvent(bool canPlay)
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "MovingPhoto HandleAnalyzerPlayEvent:%{public}d", canPlay);
    if (isAnalyzerPlaying_ == canPlay || isPlayByController_) {
        return;
    }
    if (isAnalyzerPlaying_ && !canPlay) {
        Pause();
        StopAnimation();
    }
    isAnalyzerPlaying_ = canPlay;
    if (canPlay) {
        if (isRefreshMovingPhoto_) {
            isRefreshMovingPhotoPlaying_ = true;
        }
        HandleImageAnalyzerPlayCallBack();
    }
}

bool MovingPhotoPattern::IsRefreshMovingPhotoReturn(bool status)
{
    if (status) {
        if (autoAndRepeatLevel_ == PlaybackMode::REPEAT) {
            TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "IsRefreshMovingPhotoReturn:%{public}d.", status);
            return true;
        }
    } else {
        if (autoAndRepeatLevel_ != PlaybackMode::NONE) {
            TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "IsRefreshMovingPhotoReturn not:%{public}d.", status);
            return true;
        }
    }
    return false;
}

MovingPhotoPattern::~MovingPhotoPattern()
{
    if (IsSupportImageAnalyzer()) {
        TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "~MovingPhotoPattern DestroyAnalyzerOverlay.");
        DestroyAnalyzerOverlay();
    }
    if (fd_ > 0) {
        close(fd_);
    }
}
} // namespace OHOS::Ace::NG