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
constexpr int32_t ROUND_XMAGE_MODE_VALUE = 10;
constexpr int64_t PERIOD_START = 0;
constexpr int32_t PREPARE_RETURN = 0;
constexpr int64_t VIDEO_PLAYTIME_START_POSITION = 0;
constexpr int32_t IMAGE_LOADING_COMPLETE = 0;
constexpr int32_t DURATION_FLAG = -1;
const std::string THUMBNAIL_MEDIUM_JOINT = "?&oper=thumbnail&width=-1&height=-1&path=";
const std::string COVER_POSITION = "cover_positon";
const std::string IMAGE_URI = "uri";
const std::string VIDEO_SCALE = "video_scale_type";
const std::string IMAGE_LENGTH = "ImageLength";
const std::string IMAGE_WIDTH = "ImageWidth";
const std::string HW_MNOTE_XMAGE_MODE = "HwMnoteXmageMode";
const std::string HW_MNOTE_XMAGE_LEFT = "HwMnoteXmageLeft";
const std::string HW_MNOTE_XMAGE_TOP = "HwMnoteXmageTop";
const std::string HW_MNOTE_XMAGE_RIGHT = "HwMnoteXmageRight";
const std::string HW_MNOTE_XMAGE_BOTTOM = "HwMnoteXmageBottom";
const std::string DEFAULT_EXIF_VALUE = "default_exif_value";
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
    static RenderContext::ContextParam cParam = { RenderContext::ContextType::HARDWARE_SURFACE, "MediaPlayerSurface",
                                                  RenderContext::PatternType::DEFAULT };
    columnRenderContext_->InitContext(false, cParam);
    columnRenderContext_->UpdateBackgroundColor(Color::TRANSPARENT);
    static RenderContext::ContextParam param = { RenderContext::ContextType::HARDWARE_SURFACE, "MediaPlayerSurface",
                                                 RenderContext::PatternType::VIDEO };
    renderContextForMediaPlayer_->InitContext(false, param);
    renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    renderContextForMediaPlayer_->UpdateBackgroundColor(Color::TRANSPARENT);
    renderContext->SetClipToBounds(true);

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
    auto column = AceType::DynamicCast<FrameNode>(movingPhotoNode->GetColumn());
    CHECK_NULL_VOID(column);
    auto columnRenderContext = column->GetRenderContext();
    columnRenderContext->AddChild(columnRenderContext_, 0);
    columnRenderContext->SetClipToBounds(true);
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
        if (isEnableAnalyzer_) {
            gestureHub->SetLongPressEvent(nullptr);
            longPressEvent_ = nullptr;
        } else {
            gestureHub->SetLongPressEvent(longPressEvent_, false, false, LONG_PRESS_DELAY);
        }
    }
    if (!isEnableAnalyzer_) {
        auto longPressCallback = [weak = WeakClaim(this)](GestureEvent& info) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleLongPress(info);
        };
        longPressEvent_ = MakeRefPtr<LongPressEvent>(std::move(longPressCallback));
        gestureHub->SetLongPressEvent(longPressEvent_, false, false, LONG_PRESS_DELAY);
    }

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
    if (autoAndRepeatLevel_ == PlaybackMode::NONE && isEnableAnalyzer_ && isAnalyzerPlaying_) {
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
    UpdateImageHdrMode(image);
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

void MovingPhotoPattern::UpdateImageHdrMode(const RefPtr<FrameNode>& imageNode)
{
    DynamicRangeModeConvert(dynamicRangeMode_);
    ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, DynamicMode, dynamicRangeMode_, imageNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(DynamicRangeMode, dynamicRangeMode_, imageNode);
    if (dynamicRangeMode_ == DynamicRangeMode::STANDARD) {
        ACE_RESET_NODE_PAINT_PROPERTY(ImageRenderProperty, DynamicMode, imageNode);
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, DynamicRangeMode, imageNode);
    }
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
    auto imageHub = image->GetOrCreateEventHub<ImageEventHub>();
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
        layoutProperty->GetVideoSource().value() == fd_.GetValue()) {
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
    ContainerScope scope(instanceId_);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    if (isRefreshMovingPhoto_ && isUsedMediaPlayerStatusChanged_) {
        TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "ArkUIMovingPhotoResetMediaPlayerAsync.");
        auto bgTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::BACKGROUND);
        bgTaskExecutor.PostTask(
            [weak = WeakClaim(RawPtr(mediaPlayer_)), fd = fd_] {
                auto mediaPlayer = weak.Upgrade();
                CHECK_NULL_VOID(mediaPlayer);
                mediaPlayer->ResetMediaPlayer();
                if (!mediaPlayer->SetSourceByFd(fd.GetValue())) {
                    TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "set source for MediaPlayer Async failed.");
                }
            },
            "ArkUIMovingPhotoResetMediaPlayerAsync");
    } else {
        mediaPlayer_->ResetMediaPlayer();
        RegisterMediaPlayerEvent();
        if (!mediaPlayer_->SetSourceByFd(fd_.GetValue())) {
            TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "set source for MediaPlayer failed.");
            auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
            uiTaskExecutor.PostTask(
                [weak = WeakClaim(this)] {
                    auto pattern = weak.Upgrade();
                    CHECK_NULL_VOID(pattern);
                    ContainerScope scope(pattern->instanceId_);
                    pattern->FireMediaPlayerError();
                },
                "ArkUIMovingPhotoResetMediaPlayer");
        }
    }
}

void MovingPhotoPattern::RegisterMediaPlayerEvent()
{
    if (fd_.GetValue() == -1 || !mediaPlayer_) {
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
            isSetAutoPlayPeriod_ = false;
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
    auto eventHub = GetOrCreateEventHub<MovingPhotoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireCompleteEvent();
}

void MovingPhotoPattern::FireMediaPlayerStart()
{
    auto eventHub = GetOrCreateEventHub<MovingPhotoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireStartEvent();
    if (isFastKeyUp_) {
        isFastKeyUp_ = false;
        PausePlayback();
    }
}

void MovingPhotoPattern::FireMediaPlayerStop()
{
    auto eventHub = GetOrCreateEventHub<MovingPhotoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireStopEvent();
}

void MovingPhotoPattern::FireMediaPlayerPause()
{
    auto eventHub = GetOrCreateEventHub<MovingPhotoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FirePauseEvent();
}

void MovingPhotoPattern::FireMediaPlayerFinish()
{
    auto eventHub = GetOrCreateEventHub<MovingPhotoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireFinishEvent();
}

void MovingPhotoPattern::FireMediaPlayerError()
{
    auto eventHub = GetOrCreateEventHub<MovingPhotoEventHub>();
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
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "OnDirtyLayoutWrapperSwap.");
    if (config.skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    auto geometryNode = dirty->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);
    auto movingPhotoNodeSize = geometryNode->GetContentSize();
    auto layoutProperty = GetLayoutProperty<MovingPhotoLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    SizeF videoFrameSize;
    if (isXmageMode_) {
        videoFrameSize = MeasureModeContentLayout(movingPhotoNodeSize, layoutProperty);
    } else {
        videoFrameSize = MeasureContentLayout(movingPhotoNodeSize, layoutProperty);
    }
    if (xmageModeValue_ == ROUND_XMAGE_MODE_VALUE) {
        SetRenderContextBoundsInRoundXmage(movingPhotoNodeSize, videoFrameSize);
    } else {
        SetRenderContextBounds(movingPhotoNodeSize, videoFrameSize);
    }

    if (IsSupportImageAnalyzer() && isEnableAnalyzer_ && autoAndRepeatLevel_ == PlaybackMode::NONE) {
        if (imageAnalyzerManager_ && !GetAnalyzerState()) {
            StartImageAnalyzer();
        } else {
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
    if (currentPlayStatus_ == PlaybackStatus::STARTED) {
        video->GetRenderContext()->UpdateOpacity(0.0);
    }
    return false;
}

void MovingPhotoPattern::SetRenderContextBounds(const SizeF& movingPhotoNodeSize, const SizeF& videoFrameSize)
{
    auto layoutProperty = GetLayoutProperty<MovingPhotoLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    float xmageHeight = 0;
    float ratio = 0;
    if (layoutProperty->HasXmageHeight()) {
        xmageHeight = layoutProperty->GetXmageHeight().value();
        ratio = CalculateRatio(movingPhotoNodeSize);
    }
    if (columnRenderContext_) {
        if (isXmageMode_) {
            columnRenderContext_->SetBounds((movingPhotoNodeSize.Width() - videoFrameSize.Width()) / HALF, 0,
                videoFrameSize.Width(), videoFrameSize.Height() - xmageHeight * ratio);
        } else {
            columnRenderContext_->SetBounds((movingPhotoNodeSize.Width() - videoFrameSize.Width()) / HALF,
                (movingPhotoNodeSize.Height() - videoFrameSize.Height()) / HALF,
                videoFrameSize.Width(), videoFrameSize.Height());
        }
    }
    if (renderContextForMediaPlayer_) {
        if (isXmageMode_) {
            renderContextForMediaPlayer_->SetBounds((movingPhotoNodeSize.Width() - videoFrameSize.Width()) / HALF, 0,
                videoFrameSize.Width(), videoFrameSize.Height() - xmageHeight * ratio);
        } else {
            renderContextForMediaPlayer_->SetBounds((movingPhotoNodeSize.Width() - videoFrameSize.Width()) / HALF,
                (movingPhotoNodeSize.Height() - videoFrameSize.Height()) / HALF,
                videoFrameSize.Width(), videoFrameSize.Height());
        }
    }
}

void MovingPhotoPattern::SetRenderContextBoundsInRoundXmage(
    const SizeF& movingPhotoNodeSize, const SizeF& videoFrameSize)
{
    auto layoutProperty = GetLayoutProperty<MovingPhotoLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pattern = DynamicCast<MovingPhotoPattern>(host->GetPattern());
    CHECK_NULL_VOID(pattern);
    float ratio = 0;
    SizeF xmageOffset = SizeF(0, 0);
    SizeF imageSize = SizeF(0, 0);
    SizeF xmageOffsetRatio = SizeF(0, 0);
    if (layoutProperty->HasXmageOffset()) {
        xmageOffset = layoutProperty->GetXmageOffset().value();
    }
    if (layoutProperty->HasImageSize()) {
        imageSize = layoutProperty->GetImageSize().value();
        ratio = CalculateRatio(movingPhotoNodeSize);
        xmageOffsetRatio = pattern->CalculateXmageOffsetRatio(movingPhotoNodeSize);
    }
    if (columnRenderContext_) {
        columnRenderContext_->SetBounds(
            (movingPhotoNodeSize.Width() - videoFrameSize.Width()) / HALF,
            (movingPhotoNodeSize.Height() - videoFrameSize.Height()) / HALF, imageSize.Width() * ratio,
            imageSize.Height() * ratio);
    }
    if (renderContextForMediaPlayer_) {
        renderContextForMediaPlayer_->SetBounds(
            (movingPhotoNodeSize.Width() - videoFrameSize.Width()) / HALF,
            (movingPhotoNodeSize.Height() - videoFrameSize.Height()) / HALF, imageSize.Width() * ratio,
            imageSize.Height() * ratio);
    }
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
    return { rawSize.Width() * ratio, rawSize.Height() * ratio };
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

SizeF MovingPhotoPattern::CalculateModeFitContain(const SizeF& rawSize, const SizeF& layoutSize)
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

SizeF MovingPhotoPattern::CalculateModeFitFill(const SizeF& layoutSize)
{
    return layoutSize;
}

SizeF MovingPhotoPattern::CalculateModeFitCover(const SizeF& rawSize, const SizeF& layoutSize)
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
    return { rawSize.Width() * ratio, rawSize.Height() * ratio };
}

SizeF MovingPhotoPattern::CalculateModeFitNone(const SizeF& rawSize)
{
    return rawSize;
}

SizeF MovingPhotoPattern::CalculateModeFitScaleDown(const SizeF& rawSize, const SizeF& layoutSize)
{
    if ((rawSize.Width() <= layoutSize.Width()) && (rawSize.Height() <= layoutSize.Height())) {
        return CalculateModeFitNone(rawSize);
    } else {
        return CalculateModeFitContain(rawSize, layoutSize);
    }
}

SizeF MovingPhotoPattern::CalculateModeFitAuto(const SizeF& rawSize, const SizeF& layoutSize)
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
        return CalculateModeFitContain(rawSize, layoutSize);
    } else {
        return CalculateModeFitCover(rawSize, layoutSize);
    }
}

float MovingPhotoPattern::CalculateRatio(SizeF layoutSize)
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingPhoto calculateRatio layoutSize.%{public}f, %{public}f",
        layoutSize.Width(), layoutSize.Height());
    auto layoutProperty = GetLayoutProperty<MovingPhotoLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, 0);
    if (!layoutProperty->HasImageSize()) {
        TAG_LOGE(AceLogTag::ACE_MOVING_PHOTO, "movingPhoto imageSize is null.");
        return 0;
    }
    SizeF rawSize = layoutProperty->GetImageSize().value();
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingPhoto calculateRatio rawSize.%{public}f, %{public}f",
        rawSize.Width(), rawSize.Height());
    double sourceRatio = rawSize.Width() / rawSize.Height();
    double layoutRatio = layoutSize.Width() / layoutSize.Height();
    float ratio = 0;
    if (sourceRatio > layoutRatio) {
        ratio = static_cast<float>(layoutSize.Width() / rawSize.Width());
    } else {
        ratio = static_cast<float>(layoutSize.Height() / rawSize.Height());
    }
    return ratio;
}

SizeF MovingPhotoPattern::CalculateXmageOffsetRatio(SizeF layoutSize)
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingPhoto CalculateXmageOffsetRatio layoutSize.%{public}f, %{public}f",
        layoutSize.Width(), layoutSize.Height());
    SizeF ret = SizeF(0, 0);
    auto layoutProperty = GetLayoutProperty<MovingPhotoLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, ret);
    if (!layoutProperty->HasXmageRawSize()) {
        TAG_LOGE(AceLogTag::ACE_MOVING_PHOTO, "movingPhoto xmageRawSize is null.");
        return ret;
    }
    if (!layoutProperty->HasXmageRawSize()) {
        return ret;
    }
    SizeF rawSize = layoutProperty->GetXmageRawSize().value();
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingPhoto CalculateXmageOffsetRatio rawSize.%{public}f, %{public}f",
        rawSize.Width(), rawSize.Height());

    if (rawSize.Width() == 0.0 || rawSize.Height() == 0.0) {
        TAG_LOGE(AceLogTag::ACE_MOVING_PHOTO, "movingPhoto xmageRawSize is 0.");
        return ret;
    }
    double widthRatio = layoutSize.Width() / rawSize.Width();
    double heightRatio = layoutSize.Height() / rawSize.Height();
    return SizeF(widthRatio, heightRatio);
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

int32_t MovingPhotoPattern::GetImageFd() const
{
    if (!isPlayWithMask_) {
        TAG_LOGE(AceLogTag::ACE_MOVING_PHOTO, "movingPhoto GetImageFd.%{public}d", isPlayWithMask_);
        return -1;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, -1);
    auto layoutProperty = GetLayoutProperty<MovingPhotoLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, -1);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, -1);
    auto dataProvider = AceType::DynamicCast<DataProviderManagerStandard>(pipeline->GetDataProviderManager());
    CHECK_NULL_RETURN(dataProvider, -1);

    if (!layoutProperty->HasMovingPhotoUri()) {
        TAG_LOGE(AceLogTag::ACE_MOVING_PHOTO, "movingPhoto GetImageFd uri is null");
        return -1;
    }
    std::string uriValue = layoutProperty->GetMovingPhotoUri().value();
    int32_t fd = dataProvider->GetDataProviderFile(uriValue, "r");
    return fd;
}

void MovingPhotoPattern::GetXmageHeight()
{
    int32_t fd = GetImageFd();
    CHECK_NULL_VOID(fd >= 0);
    auto imageSrc = ImageSource::Create(fd);
    close(fd);
    CHECK_NULL_VOID(imageSrc);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto imageLength = imageSrc->GetProperty(IMAGE_LENGTH);
    auto imageWidth = imageSrc->GetProperty(IMAGE_WIDTH);
    if (imageLength.empty() || imageWidth.empty() || imageLength == DEFAULT_EXIF_VALUE ||
        imageWidth == DEFAULT_EXIF_VALUE) {
        TAG_LOGE(AceLogTag::ACE_MOVING_PHOTO, "movingPhoto imageLength or imageWidth is null");
        return;
    }

    float imageW = StringUtils::StringToFloat(imageWidth);
    float imageL = StringUtils::StringToFloat(imageLength);
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingPhoto imageW.%{public}f, imageL %{public}f",
             imageW, imageL);

    std::string modeValue = imageSrc->GetProperty(HW_MNOTE_XMAGE_MODE);
    SizeF imageSize = SizeF(-1, -1);
    if (!modeValue.empty() && modeValue != DEFAULT_EXIF_VALUE) {
        isXmageMode_ = true;
        std::string bottomValue = imageSrc->GetProperty(HW_MNOTE_XMAGE_BOTTOM);
        if (bottomValue.empty() || bottomValue == DEFAULT_EXIF_VALUE) {
            TAG_LOGE(AceLogTag::ACE_MOVING_PHOTO, "movingPhoto bottomValue is null");
            return;
        }
        float bottomV = StringUtils::StringToFloat(bottomValue);
        TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingPhoto bottomV.%{public}f", bottomV);
        imageSize = SizeF(imageW, bottomV);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MovingPhotoLayoutProperty, XmageHeight, imageL - bottomV, host);
        TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingPhoto XmageHeight.%{public}f", imageL - bottomV);
    } else {
        imageSize = SizeF(imageW, imageL);
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(MovingPhotoLayoutProperty, ImageSize, imageSize, host);
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingPhoto imageSize imageW.%{public}f, imageL %{public}f",
             imageSize.Width(), imageSize.Height());
}

void MovingPhotoPattern::SetXmagePosition()
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingPhoto SetXmagePosition");
    int32_t fd = GetImageFd();
    CHECK_NULL_VOID(fd >= 0);
    auto imageSrc = ImageSource::Create(fd);
    close(fd);
    CHECK_NULL_VOID(imageSrc);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto imageLength = imageSrc->GetProperty(IMAGE_LENGTH);
    auto imageWidth = imageSrc->GetProperty(IMAGE_WIDTH);
    if (imageLength.empty() || imageWidth.empty() || imageLength == DEFAULT_EXIF_VALUE ||
        imageWidth == DEFAULT_EXIF_VALUE) {
        TAG_LOGE(AceLogTag::ACE_MOVING_PHOTO, "movingPhoto imageLength or imageWidth is null");
        return;
    }
 
    float imageW = StringUtils::StringToFloat(imageWidth);
    float imageL = StringUtils::StringToFloat(imageLength);
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingPhoto imageW.%{public}f, imageL %{public}f",
             imageW, imageL);
 
    std::string modeValue = imageSrc->GetProperty(HW_MNOTE_XMAGE_MODE);
    SizeF imageSize = SizeF(-1, -1);
    if (!modeValue.empty() && modeValue != DEFAULT_EXIF_VALUE) {
        isXmageMode_ = true;
        xmageModeValue_ = StringUtils::StringToInt(modeValue);
        TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingPhoto xmageModeValue_ = %{public}d", xmageModeValue_);
        if (xmageModeValue_ == ROUND_XMAGE_MODE_VALUE) {
            UpdateRoundXmageProperty(imageSrc, imageSize, imageW, imageL, host);
        } else {
            std::string bottomValue = imageSrc->GetProperty(HW_MNOTE_XMAGE_BOTTOM);
            if (bottomValue.empty() || bottomValue == DEFAULT_EXIF_VALUE) {
                TAG_LOGE(AceLogTag::ACE_MOVING_PHOTO, "movingPhoto bottomValue is null");
                return;
            }
            float bottomV = StringUtils::StringToFloat(bottomValue);
            TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingPhoto bottomV.%{public}f", bottomV);
            imageSize = SizeF(imageW, bottomV);
            ACE_UPDATE_NODE_LAYOUT_PROPERTY(MovingPhotoLayoutProperty, XmageHeight, imageL - bottomV, host);
            TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingPhoto XmageHeight.%{public}f", imageL - bottomV);
        }
    } else {
        imageSize = SizeF(imageW, imageL);
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(MovingPhotoLayoutProperty, ImageSize, imageSize, host);
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingPhoto imageSize imageW.%{public}f, imageL %{public}f",
            imageSize.Width(), imageSize.Height());
}
 
void MovingPhotoPattern::UpdateRoundXmageProperty(
    RefPtr<ImageSource> imageSrc, SizeF& imageSize, float imageW, float imageL, RefPtr<FrameNode>& host)
{
    std::string xmageLeft = imageSrc->GetProperty(HW_MNOTE_XMAGE_LEFT);
    std::string xmageTop = imageSrc->GetProperty(HW_MNOTE_XMAGE_TOP);
    std::string xmageRight = imageSrc->GetProperty(HW_MNOTE_XMAGE_RIGHT);
    std::string xmageBottom = imageSrc->GetProperty(HW_MNOTE_XMAGE_BOTTOM);
    if (xmageBottom.empty() || xmageBottom == DEFAULT_EXIF_VALUE) {
        TAG_LOGE(AceLogTag::ACE_MOVING_PHOTO, "movingPhoto xmageBottom is null");
        return;
    }
    float xLeft = StringUtils::StringToFloat(xmageLeft);
    float xTop = StringUtils::StringToFloat(xmageTop);
    float xRight = StringUtils::StringToFloat(xmageRight);
    float xBottom = StringUtils::StringToFloat(xmageBottom);
    imageSize = SizeF(xRight - xLeft, xBottom - xTop);
    SizeF xmageOffset = SizeF(xLeft, xTop);
    SizeF xmageRawSize = SizeF(imageW, imageL);
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingPhoto roundXmage(%{public}f, %{public}f, %{public}f, %{public}f)",
        xLeft, xTop, xRight, xBottom);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(MovingPhotoLayoutProperty, XmageOffset, xmageOffset, host);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(MovingPhotoLayoutProperty, XmageRawSize, xmageRawSize, host);
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

    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingPhoto MeasureContentLayout.%{public}f, %{public}f",
        contentSize.Width(), contentSize.Height());
    return contentSize;
}

SizeF MovingPhotoPattern::MeasureModeContentLayout(const SizeF& layoutSize,
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
            contentSize = CalculateModeFitContain(rawImageSize, layoutSize);
            break;
        case ImageFit::FILL:
            contentSize = CalculateModeFitFill(layoutSize);
            break;
        case ImageFit::COVER:
            contentSize = CalculateModeFitCover(rawImageSize, layoutSize);
            break;
        case ImageFit::NONE:
            contentSize = CalculateModeFitNone(rawImageSize);
            break;
        case ImageFit::SCALE_DOWN:
            contentSize = CalculateModeFitScaleDown(rawImageSize, layoutSize);
            break;
        default:
            contentSize = CalculateModeFitAuto(rawImageSize, layoutSize);
    }

    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingPhoto MeasureModeContentLayout.%{public}f, %{public}f",
        contentSize.Width(), contentSize.Height());
    return contentSize;
}

void MovingPhotoPattern::OnMediaPlayerStatusChanged(PlaybackStatus status)
{
    isUsedMediaPlayerStatusChanged_ = true;
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
    isAutoChangePlayMode_ = false;
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
    if (isRepeatChangePlayMode_ && historyAutoAndRepeatLevel_ == PlaybackMode::NONE &&
        autoAndRepeatLevel_ == PlaybackMode::NONE) {
        autoAndRepeatLevel_ = PlaybackMode::REPEAT;
        historyAutoAndRepeatLevel_ = PlaybackMode::REPEAT;
        isRepeatChangePlayMode_ = false;
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
    if (historyAutoAndRepeatLevel_ == PlaybackMode::REPEAT) {
        if (!isFirstRepeatPlay_) {
            videoRsContext->UpdateOpacity(1.0);
            return;
        }
        isFirstRepeatPlay_ = false;
    }

    videoRsContext->UpdateOpacity(0.0);
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
    });
    startAnimationFlag_ = true;
    AnimationUtils::Animate(animationOption,
        [imageRsContext, videoRsContext, flag = autoAndRepeatLevel_, movingPhotoPattern]() {
            videoRsContext->UpdateOpacity(1.0);
            auto movingPhoto = movingPhotoPattern.Upgrade();
            CHECK_NULL_VOID(movingPhoto);
            movingPhoto->RsContextUpdateTransformScale(imageRsContext, videoRsContext, flag);
        }, animationOption.GetOnFinishEvent());
}

void MovingPhotoPattern::RsContextUpdateTransformScale(const RefPtr<RenderContext>& imageRsContext,
    const RefPtr<RenderContext>& videoRsContext, PlaybackMode playbackMode)
{
    if (playbackMode == PlaybackMode::REPEAT) {
        videoRsContext->UpdateTransformScale({NORMAL_SCALE, NORMAL_SCALE});
        imageRsContext->UpdateTransformScale({NORMAL_SCALE, NORMAL_SCALE});
    } else if (playbackMode == PlaybackMode::AUTO) {
        videoRsContext->UpdateTransformScale({NORMAL_SCALE, NORMAL_SCALE});
        imageRsContext->UpdateTransformScale({NORMAL_SCALE, NORMAL_SCALE});
    } else {
        if (isXmageMode_) {
            videoRsContext->UpdateTransformScale({ZOOM_IN_SCALE, ZOOM_IN_SCALE});
            imageRsContext->UpdateTransformScale({NORMAL_SCALE, NORMAL_SCALE});
        } else {
            videoRsContext->UpdateTransformScale({ZOOM_IN_SCALE, ZOOM_IN_SCALE});
            imageRsContext->UpdateTransformScale({ZOOM_IN_SCALE, ZOOM_IN_SCALE});
        }
    }
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
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingphoto RefreshMovingPhoto start.");
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
    auto imageCache = pipeline->GetImageCache();
    if (imageCache) {
        ImageSourceInfo srcKey;
        srcKey.SetSrc(imageSrc);
        imageCache->ClearCacheImgObj(srcKey.GetKey());
    }
    imageSrc += "?date_modified = " + std::to_string(GetMicroTickCount());
    ImageSourceInfo src;
    src.SetSrc(imageSrc);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(MovingPhotoLayoutProperty, ImageSourceInfo, src, host);
    UpdateImageNode();
    fd_ = dataProvider->ReadMovingPhotoVideo(uri_);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(MovingPhotoLayoutProperty, VideoSource, fd_.GetValue(), host);
    isRefreshMovingPhoto_ = true;
    isSetAutoPlayPeriod_ = false;
    RefreshMovingPhotoSceneManager();
    ResetMediaPlayer();
    if (IsSupportImageAnalyzer() && isEnableAnalyzer_ && imageAnalyzerManager_) {
        UpdateAnalyzerOverlay();
    }
}

void MovingPhotoPattern::RefreshMovingPhotoSceneManager()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (historyAutoAndRepeatLevel_ == PlaybackMode::REPEAT) {
        autoAndRepeatLevel_ = PlaybackMode::NONE;
        historyAutoAndRepeatLevel_ = PlaybackMode::NONE;
        isRepeatChangePlayMode_ = true;
        Pause();
        auto movingPhoto = AceType::DynamicCast<MovingPhotoNode>(host);
        CHECK_NULL_VOID(movingPhoto);
        auto video = AceType::DynamicCast<FrameNode>(movingPhoto->GetVideo());
        CHECK_NULL_VOID(video);
        video->GetRenderContext()->SetClipToBounds(true);
        video->GetRenderContext()->UpdateOpacity(0.0);
    } else if (historyAutoAndRepeatLevel_ == PlaybackMode::AUTO) {
        autoAndRepeatLevel_ = PlaybackMode::AUTO;
        isAutoChangePlayMode_ = true;
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

    videoRsContext->UpdateOpacity(1.0);
    RsContextUpdateTransformScale(imageRsContext, videoRsContext, autoAndRepeatLevel_);
    image->MarkModifyDone();
    video->MarkModifyDone();
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
            videoRsContext->UpdateOpacity(0.0);
            imageRsContext->UpdateTransformScale({NORMAL_SCALE, NORMAL_SCALE});
            videoRsContext->UpdateTransformScale({NORMAL_SCALE, NORMAL_SCALE});
        }, option.GetOnFinishEvent());
}

void MovingPhotoPattern::StopAnimationCallback()
{
    if (historyAutoAndRepeatLevel_ == PlaybackMode::AUTO && autoPlayPeriodStartTime_ >= 0) {
        Seek(static_cast<int32_t>(autoPlayPeriodStartTime_));
    } else {
        Seek(0);
    }
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
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingphoto AutoPlayPeriod: [%{public}lld, %{public}lld].",
        static_cast<long long>(startTime), static_cast<long long>(endTime));
    if (startTime >= VIDEO_PLAYTIME_START_POSITION && startTime < endTime) {
        autoPlayPeriodStartTime_ = startTime;
        autoPlayPeriodEndTime_ = endTime;
    }
}

void MovingPhotoPattern::SetAutoPlayPeriod(int64_t startTime, int64_t endTime)
{
    TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "movingphoto SetAutoPlayPeriod: [%{public}lld, %{public}lld].",
        static_cast<long long>(startTime), static_cast<long long>(endTime));
    if (startTime < VIDEO_PLAYTIME_START_POSITION || startTime >= endTime) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "MediaPlayer SetAutoPlayPeriod error.");
        return;
    }
    if (!mediaPlayer_ || !mediaPlayer_->IsMediaPlayerValid()) {
        TAG_LOGW(AceLogTag::ACE_MOVING_PHOTO, "MediaPlayer is null or invalid.");
        return;
    }
    mediaPlayer_->SetPlayRangeWithMode(startTime, endTime, SeekMode::SEEK_CLOSEST);
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
        columnSurface_->SetExtSurfaceBounds(rect.Left(), rect.Top(), rect.Width(), rect.Height());
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

void MovingPhotoPattern::AddWindowStateChangedCallback()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->AddWindowStateChangedCallback(host->GetId());
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
    auto movingPhotoNodeSize = geometryNode->GetContentSize();
    auto layoutProperty = GetLayoutProperty<MovingPhotoLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto videoFrameSize = MeasureContentLayout(movingPhotoNodeSize, layoutProperty);
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
}
} // namespace OHOS::Ace::NG