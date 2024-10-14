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
constexpr int64_t VIDEO_PLAYTIME_END_POSITION = 3000;
constexpr int32_t IMAGE_LOADING_COMPLETE = 0;
constexpr int32_t DURATION_FLAG = -1;
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
            },
            "ArkUIMovingPhotoStart");
    });

    controller_->SetStopPlaybackImpl([weak = WeakClaim(this), uiTaskExecutor]() {
        uiTaskExecutor.PostTask(
            [weak]() {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                ContainerScope scope(pattern->instanceId_);
                pattern->StopPlayback();
            },
            "ArkUIMovingPhotoStop");
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
        return;
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

void MovingPhotoPattern::HandleLongPress(GestureEvent& info)
{
    isFastKeyUp_ = false;
    if (currentPlayStatus_ == PlaybackStatus::STARTED || !isPrepared_ || isPlayByController_) {
        return;
    }
    if (autoAndRepeatLevel_ != PlaybackMode::NONE) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "HandleLongPress auto&Repeat return.");
        return;
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
        isSetAutoPlayPeriod_ = false;
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
    if (autoAndRepeatLevel_ != PlaybackMode::NONE) {
        TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "HandleLongPress auto&Repeat return.");
        return;
    }
    if (!isPrepared_ || isPlayByController_) {
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
    ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, DynamicMode, DynamicRangeMode::HIGH, image);
    ACE_UPDATE_NODE_RENDER_CONTEXT(DynamicRangeMode, DynamicRangeMode::HIGH, image);
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingphoto set HDR.");
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
        imageLayoutProperty->UpdateImageFit(imageFit);
        image->MarkModifyDone();
    }
    RegisterImageEvent();
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
    auto platformTask = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::BACKGROUND);
    platformTask.PostTask(
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
        MediaResetToPlay();
        isChangePlayMode_ = false;
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
    if (isPlayByController_ || autoAndRepeatLevel_ != PlaybackMode::NONE) {
        isPlayByController_ = false;
        StopAnimation();
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
    if (autoAndRepeatLevel_ != PlaybackMode::NONE) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "StartPlayback autoAndRepeatLevel_:%{public}d.",
            autoAndRepeatLevel_);
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
    if (autoAndRepeatLevel_ != PlaybackMode::NONE) {
        TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "PausePlayback autoAndRepeatLevel_:%{public}d.",
            autoAndRepeatLevel_);
        return;
    }
    isPlayByController_ = false;
    Pause();
    StopAnimation();
}

void MovingPhotoPattern::StopAnimation()
{
    startAnimationFlag_ = false;
    if (historyAutoAndRepeatLevel_ == PlaybackMode::REPEAT) {
        StopAnimationCallback();
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
    if (startTime >= VIDEO_PLAYTIME_START_POSITION && startTime < endTime
            && endTime <= VIDEO_PLAYTIME_END_POSITION) {
        TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "MediaPlayer set Period.");
        autoPlayPeriodStartTime_ = startTime;
        autoPlayPeriodEndTime_ = endTime;
    }
}

void MovingPhotoPattern::SetAutoPlayPeriod(int64_t startTime, int64_t endTime)
{
    if (startTime < VIDEO_PLAYTIME_START_POSITION || startTime >= endTime
            || endTime > VIDEO_PLAYTIME_END_POSITION) {
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

void MovingPhotoPattern::Start()
{
    if (!mediaPlayer_ || !mediaPlayer_->IsMediaPlayerValid()) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "MediaPlayer is null or invalid.");
        return;
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
        if (historyAutoAndRepeatLevel_ == PlaybackMode::AUTO) {
            SetAutoPlayPeriod(autoPlayPeriodStartTime_, autoPlayPeriodEndTime_);
        }
        MediaResetToPlay();
    } else {
        if (historyAutoAndRepeatLevel_ == PlaybackMode::AUTO) {
            PausePlayback();
        } else if (historyAutoAndRepeatLevel_ == PlaybackMode::REPEAT) {
            StopPlayback();
        }
    }
}

MovingPhotoPattern::~MovingPhotoPattern()
{
    if (fd_ > 0) {
        close(fd_);
    }
}
} // namespace OHOS::Ace::NG