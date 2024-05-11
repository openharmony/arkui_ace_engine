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
#include "movingphoto_layout_property.h"
#include "movingphoto_node.h"

#include "base/geometry/ng/size_t.h"
#include "base/log/ace_trace.h"
#include "base/utils/system_properties.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t LONG_PRESS_DELAY = 300;
constexpr int32_t ANIMATION_DURATION_300 = 300;
constexpr int32_t ANIMATION_DURATION_400 = 400;
constexpr float NORMAL_SCALE = 1.0f;
constexpr float ZOOM_IN_SCALE = 1.1f;
constexpr double NORMAL_PLAY_SPEED = 1.0;
constexpr int32_t HALF = 2;
}
MovingPhotoPattern::MovingPhotoPattern(const RefPtr<MovingPhotoController>& controller)
    : instanceId_(Container::CurrentId()), controller_(controller)
{}

void MovingPhotoPattern::OnModifyDone()
{
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

    isPlayByController_ = false;
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
    renderContext->UpdateBackgroundColor(Color::BLACK);
    renderContextForMediaPlayer_->UpdateBackgroundColor(Color::BLACK);
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
        uiTaskExecutor.PostTask([weak]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            ContainerScope scope(pattern->instanceId_);
            pattern->StartPlayback();
        }, "ArkUIMovingPhotoStart");
    });

    controller_->SetStopPlaybackImpl([weak = WeakClaim(this), uiTaskExecutor]() {
        uiTaskExecutor.PostTask([weak]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            ContainerScope scope(pattern->instanceId_);
            pattern->StopPlayback();
        }, "ArkUIMovingPhotoStop");
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
    if (currentPlayStatus_ == PlaybackStatus::STARTED || !isPrepared_ || isPlayByController_) {
        return;
    }
    Start();
}

void MovingPhotoPattern::HandleTouchEvent(TouchEventInfo& info)
{
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
            StopPlayback();
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
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto movingPhoto = AceType::DynamicCast<MovingPhotoNode>(host);
    CHECK_NULL_VOID(movingPhoto);
    auto image = AceType::DynamicCast<FrameNode>(movingPhoto->GetImage());
    CHECK_NULL_VOID(image);
    auto layoutProperty = GetLayoutProperty<MovingPhotoLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (!layoutProperty->HasMovingPhotoUri() || layoutProperty->GetMovingPhotoUri().value() == uri_) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "MovingPhoto is null or has not changed.");
        return;
    }
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
}

void MovingPhotoPattern::UpdateVideoNode()
{
    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto uiTaskExecutor = SingleTaskExecutor::Make(pipelineContext->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    uiTaskExecutor.PostTask([weak = WeakClaim(this)]() {
        auto movingPhotoPattern = weak.Upgrade();
        CHECK_NULL_VOID(movingPhotoPattern);
        ContainerScope scope(movingPhotoPattern->instanceId_);
        movingPhotoPattern->PrepareMediaPlayer();
        movingPhotoPattern->UpdateMediaPlayerSpeed();
        movingPhotoPattern->UpdateMediaPlayerMuted();
    }, "ArkUIMovingPhotoUpdateVideo");
}

void MovingPhotoPattern::PrepareMediaPlayer()
{
    auto layoutProperty = GetLayoutProperty<MovingPhotoLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (!layoutProperty->HasMovingPhotoUri() || layoutProperty->GetMovingPhotoUri().value() == uri_) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "MovingPhoto source is null or the source has not changed.");
        return;
    }
    uri_ = layoutProperty->GetMovingPhotoUri().value();
    if (!layoutProperty->HasVideoSource()) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "MediaPlayer source is null or the source has not changed.");
        return;
    }
    fd_ = layoutProperty->GetVideoSource().value();
    if (mediaPlayer_ && !mediaPlayer_->IsMediaPlayerValid()) {
        mediaPlayer_->CreateMediaPlayer();
    }
    if (mediaPlayer_ && !mediaPlayer_->IsMediaPlayerValid()) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "MediaPlayer is null or invalid.");
        FireMediaPlayerError();
        return;
    }
    ContainerScope scope(instanceId_);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto platformTask = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::BACKGROUND);
    platformTask.PostTask([weak = WeakClaim(this)] {
        auto movingPhotoPattern = weak.Upgrade();
        CHECK_NULL_VOID(movingPhotoPattern);
        movingPhotoPattern->ResetMediaPlayer();
    }, "ArkUIMovingPhotoPrepare");
}

void MovingPhotoPattern::ResetMediaPlayer()
{
    CHECK_NULL_VOID(mediaPlayer_);
    isPrepared_ = false;
    mediaPlayer_->ResetMediaPlayer();
    if (!mediaPlayer_->SetSourceByFd(fd_)) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "set source for MediaPlayer failed.");
        ContainerScope scope(instanceId_);
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);

        auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        uiTaskExecutor.PostTask([weak = WeakClaim(this)] {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            ContainerScope scope(pattern->instanceId_);
            pattern->FireMediaPlayerError();
        }, "ArkUIMovingPhotoReset");
        return;
    }
    RegisterMediaPlayerEvent();
    PrepareSurface();
    if (mediaPlayer_->PrepareAsync() != 0) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "prepare MediaPlayer failed.");
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
        uiTaskExecutor.PostSyncTask([movingPhotoPattern, currentPos] {
            auto movingPhoto = movingPhotoPattern.Upgrade();
            CHECK_NULL_VOID(movingPhoto);
            ContainerScope scope(movingPhoto->instanceId_);
            movingPhoto->OnPlayPositionChanged(currentPos);
        }, "ArkUIMovingPhotoPositionChanged");
    };

    auto&& stateChangedEvent = [movingPhotoPattern, uiTaskExecutor](PlaybackStatus status) {
        uiTaskExecutor.PostSyncTask([movingPhotoPattern, status] {
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
        uiTaskExecutor.PostSyncTask([movingPhotoPattern] {
            auto movingPhoto = movingPhotoPattern.Upgrade();
            CHECK_NULL_VOID(movingPhoto);
            ContainerScope scope(movingPhoto->instanceId_);
            movingPhoto->OnResolutionChange();
        }, "ArkUIMovingPhotoResolutionChanged");
    };

    auto&& startRenderFrameEvent = [movingPhotoPattern, uiTaskExecutor]() {
        uiTaskExecutor.PostSyncTask([movingPhotoPattern] {
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

void MovingPhotoPattern::FireMediaPlayerStart()
{
    auto eventHub = GetEventHub<MovingPhotoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireStartEvent();
    if (isFastKeyUp_) {
        isFastKeyUp_ = false;
        StopPlayback();
    }
}

void MovingPhotoPattern::FireMediaPlayerStop()
{
    auto eventHub = GetEventHub<MovingPhotoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireStopEvent();
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

SizeF MovingPhotoPattern::CalculateFitContain(const SizeF& videoSize, const SizeF& layoutSize)
{
    double layoutRatio = NearZero(layoutSize.Height()) ? 0.0 : layoutSize.Width() / layoutSize.Height();
    double sourceRatio = NearZero(videoSize.Height()) ? layoutRatio : videoSize.Width() / videoSize.Height();

    if (NearZero(layoutRatio) || NearZero(sourceRatio)) {
        return layoutSize;
    }
    if (sourceRatio < layoutRatio) {
        return { static_cast<float>(sourceRatio) * layoutSize.Height(), layoutSize.Height() };
    }
    return { layoutSize.Width(), static_cast<float>(layoutSize.Width() / sourceRatio) };
}

SizeF MovingPhotoPattern::CalculateFitFill(const SizeF& layoutSize)
{
    return layoutSize;
}

SizeF MovingPhotoPattern::CalculateFitCover(const SizeF& videoSize, const SizeF& layoutSize)
{
    double layoutRatio = NearZero(layoutSize.Height()) ? 0.0 : layoutSize.Width() / layoutSize.Height();
    double sourceRatio = NearZero(videoSize.Height()) ? layoutRatio : videoSize.Width() / videoSize.Height();

    if (NearZero(layoutRatio) || NearZero(sourceRatio)) {
        return layoutSize;
    }
    if (sourceRatio < layoutRatio) {
        return { layoutSize.Width(), static_cast<float>(layoutSize.Width() / sourceRatio) };
    }
    return { static_cast<float>(layoutSize.Height() * sourceRatio), layoutSize.Height() };
}

SizeF MovingPhotoPattern::CalculateFitNone(const SizeF& videoSize)
{
    return videoSize;
}

SizeF MovingPhotoPattern::CalculateFitScaleDown(const SizeF& videoSize, const SizeF& layoutSize)
{
    if (layoutSize.Width() > videoSize.Width()) {
        return CalculateFitNone(videoSize);
    }
    return CalculateFitContain(videoSize, layoutSize);
}

SizeF MovingPhotoPattern::MeasureContentLayout(const SizeF& layoutSize, const RefPtr<MovingPhotoLayoutProperty>& layoutProperty)
{
    if (!layoutProperty || !layoutProperty->HasVideoSize()) {
        return layoutSize;
    }

    auto videoSize = layoutProperty->GetVideoSizeValue(SizeF(0, 0));
    auto imageFit = layoutProperty->GetObjectFitValue(ImageFit::COVER);
    SizeF contentSize = { 0.0, 0.0 };
    switch (imageFit) {
        case ImageFit::CONTAIN:
            contentSize = CalculateFitContain(videoSize, layoutSize);
            break;
        case ImageFit::FILL:
            contentSize = CalculateFitFill(layoutSize);
            break;
        case ImageFit::COVER:
            contentSize = CalculateFitCover(videoSize, layoutSize);
            break;
        case ImageFit::NONE:
            contentSize = CalculateFitNone(videoSize);
            break;
        case ImageFit::SCALE_DOWN:
            contentSize = CalculateFitScaleDown(videoSize, layoutSize);
            break;
        default:
            contentSize = CalculateFitContain(videoSize, layoutSize);
    }

    return contentSize;
}

void MovingPhotoPattern::OnMediaPlayerStatusChanged(PlaybackStatus status)
{
    currentPlayStatus_ = status;
    switch (status) {
        case PlaybackStatus::ERROR:
            TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "Player current status is ERROR.");
            FireMediaPlayerError();
            break;
        case PlaybackStatus::IDLE:
            TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "Player current status is IDLE.");
            break;
        case PlaybackStatus::PREPARED:
            TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "Player current status is PREPARED.");
            OnMediaPlayerPrepared();
            break;
        case PlaybackStatus::STARTED:
            TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "Player current status is STARTED.");
            FireMediaPlayerStart();
            break;
        case PlaybackStatus::PAUSED:
            TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "Player current status is PAUSED.");
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
}

void MovingPhotoPattern::OnMediaPlayerStoped()
{
    FireMediaPlayerStop();
}

void MovingPhotoPattern::OnMediaPlayerCompletion()
{
    if (isPlayByController_) {
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

void MovingPhotoPattern::StartPlayback()
{
    if (currentPlayStatus_ == PlaybackStatus::STARTED || !isPrepared_) {
        return;
    }
    isPlayByController_ = true;
    Start();
}

void MovingPhotoPattern::StartAnimation()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto movingPhoto = AceType::DynamicCast<MovingPhotoNode>(host);
    CHECK_NULL_VOID(movingPhoto);
    auto image = AceType::DynamicCast<FrameNode>(movingPhoto->GetImage());
    CHECK_NULL_VOID(image);
    auto imageRsContext = image->GetRenderContext();
    CHECK_NULL_VOID(imageRsContext);
    imageRsContext->UpdateOpacity(1.0);
    imageRsContext->UpdateTransformScale({NORMAL_SCALE, NORMAL_SCALE});
    auto video = AceType::DynamicCast<FrameNode>(movingPhoto->GetVideo());
    CHECK_NULL_VOID(video);
    auto videoRsContext = video->GetRenderContext();
    CHECK_NULL_VOID(videoRsContext);
    videoRsContext->UpdateTransformScale({NORMAL_SCALE, NORMAL_SCALE});

    AnimationOption animationOption;
    animationOption.SetDuration(ANIMATION_DURATION_400);
    animationOption.SetCurve(Curves::FRICTION);
    animationOption.SetOnFinishEvent([this]() {
        if (currentPlayStatus_ == PlaybackStatus::PAUSED || currentPlayStatus_ == PlaybackStatus::STOPPED) {
            return;
        }
        HideImageNode();
    });
    AnimationUtils::Animate(animationOption, [imageCtx = imageRsContext, videoCtx = videoRsContext]() {
            imageCtx->UpdateOpacity(0.0);
            imageCtx->UpdateTransformScale({ZOOM_IN_SCALE, ZOOM_IN_SCALE});
            videoCtx->UpdateTransformScale({ZOOM_IN_SCALE, ZOOM_IN_SCALE});
         }, animationOption.GetOnFinishEvent());
}

void MovingPhotoPattern::StopPlayback()
{
    if (currentPlayStatus_ != PlaybackStatus::STARTED || !isPrepared_) {
        return;
    }
    isPlayByController_ = false;
    Pause();
    StopAnimation();
}

void MovingPhotoPattern::StopAnimation()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto movingPhoto = AceType::DynamicCast<MovingPhotoNode>(host);
    CHECK_NULL_VOID(movingPhoto);
    auto image = AceType::DynamicCast<FrameNode>(movingPhoto->GetImage());
    CHECK_NULL_VOID(image);
    auto imageLayoutProperty = image->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    imageLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    auto imageRsContext = image->GetRenderContext();
    CHECK_NULL_VOID(imageRsContext);
    imageRsContext->UpdateOpacity(0.0);
    imageRsContext->UpdateTransformScale({ZOOM_IN_SCALE, ZOOM_IN_SCALE});
    image->MarkModifyDone();
    auto video = AceType::DynamicCast<FrameNode>(movingPhoto->GetVideo());
    CHECK_NULL_VOID(video);
    auto videoRsContext = video->GetRenderContext();
    CHECK_NULL_VOID(videoRsContext);
    videoRsContext->UpdateTransformScale({ZOOM_IN_SCALE, ZOOM_IN_SCALE});
    video->MarkModifyDone();

    AnimationOption option;
    option.SetDuration(ANIMATION_DURATION_300);
    option.SetCurve(Curves::FRICTION);
    option.SetOnFinishEvent([this]() {
        Seek(0);
    });
    AnimationUtils::Animate(option, [imageCtx = imageRsContext, videoCtx = videoRsContext]() {
            imageCtx->UpdateOpacity(1.0);
            imageCtx->UpdateTransformScale({NORMAL_SCALE, NORMAL_SCALE});
            videoCtx->UpdateTransformScale({NORMAL_SCALE, NORMAL_SCALE});
         }, option.GetOnFinishEvent());
}

void MovingPhotoPattern::Start()
{
    if (!mediaPlayer_ || !mediaPlayer_->IsMediaPlayerValid()) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "MediaPlayer is null or invalid.");
        return;
    }

    if ((currentPlayStatus_ == PlaybackStatus::STOPPED) && mediaPlayer_->PrepareAsync() != 0) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "prepare MediaPlayer failed.");
        return;
    }
    ContainerScope scope(instanceId_);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);

    auto platformTask = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::BACKGROUND);
    platformTask.PostTask([weak = WeakClaim(RawPtr(mediaPlayer_))] {
        auto mediaPlayer = weak.Upgrade();
        CHECK_NULL_VOID(mediaPlayer);
        mediaPlayer->Play();
    }, "ArkUIMovingPhotoStartPlay");
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
    platformTask.PostTask([weak = WeakClaim(RawPtr(mediaPlayer_))] {
        auto mediaPlayer = weak.Upgrade();
        CHECK_NULL_VOID(mediaPlayer);
        mediaPlayer->Pause();
        }, "ArkUIMovingPhotoPausePlay");
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
    platformTask.PostTask([weak = WeakClaim(RawPtr(mediaPlayer_))] {
        auto mediaPlayer = weak.Upgrade();
        CHECK_NULL_VOID(mediaPlayer);
        mediaPlayer->Stop();
    }, "ArkUIMovingPhotoStopPlay");
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
    platformTask.PostTask([weak = WeakClaim(RawPtr(mediaPlayer_)), pos = position] {
        auto mediaPlayer = weak.Upgrade();
        CHECK_NULL_VOID(mediaPlayer);
        mediaPlayer->Seek(pos, SeekMode::SEEK_PREVIOUS_SYNC);
        }, "ArkUIMovingPhotoSeek");
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
    platformTask.PostTask([weak = WeakClaim(RawPtr(mediaPlayer_))] {
        auto mediaPlayer = weak.Upgrade();
        CHECK_NULL_VOID(mediaPlayer);
        mediaPlayer->SetPlaybackSpeed(static_cast<float>(NORMAL_PLAY_SPEED));
    }, "ArkUIMovingPhotoUpdateSpeed");
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
    platformTask.PostTask([weak = WeakClaim(RawPtr(mediaPlayer_)), videoVolume = volume] {
        auto mediaPlayer = weak.Upgrade();
        CHECK_NULL_VOID(mediaPlayer);
        mediaPlayer->SetVolume(videoVolume, videoVolume);
    }, "ArkUIMovingPhotoUpdateMuted");
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
        OnWindowHide();
    }
}

void MovingPhotoPattern::OnWindowHide()
{
    Stop();
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

void MovingPhotoPattern::RegisterVisibleAreaChange()
{
    if (hasVisibleChangeRegistered_) {
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipeline);
    auto callback = [weak = WeakClaim(this)](bool visible, double ratio) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (!visible) {
            pattern->StopPlayback();
        }
    };
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    std::vector<double> ratioList = {0.0};
    pipeline->AddVisibleAreaChangeNode(host, ratioList, callback, false);
    pipeline->AddWindowStateChangedCallback(host->GetId());
    hasVisibleChangeRegistered_ = true;
}

MovingPhotoPattern::~MovingPhotoPattern()
{
    if (fd_ > 0) {
        close(fd_);
    }
}
} // namespace OHOS::Ace::NG