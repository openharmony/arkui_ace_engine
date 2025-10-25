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

#include "core/components_ng/pattern/video/video_pattern.h"

#include "base/background_task_helper/background_task_helper.h"
#include "base/i18n/localization.h"
#include "base/json/json_util.h"
#include "base/thread/task_executor.h"
#include "base/utils/multi_thread.h"
#include "core/common/ai/image_analyzer_manager.h"
#include "core/components/video/video_theme.h"
#include "core/components_ng/pattern/image/image_render_property.h"
#include "core/components_ng/pattern/slider/slider_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/video/video_full_screen_node.h"
#include "core/components_ng/pattern/video/video_full_screen_pattern.h"
#include "core/components_ng/pattern/video/video_pattern_util.h"

#ifdef ENABLE_ROSEN_BACKEND
#include "core/components_ng/render/adapter/rosen_render_context.h"
#endif

namespace OHOS::Ace::NG {
VideoPattern::VideoPattern(const RefPtr<VideoControllerV2>& videoController)
    : instanceId_(Container::CurrentId()), videoControllerV2_(videoController)
{}

VideoPattern::~VideoPattern()
{
    if (IsSupportImageAnalyzer()) {
        DestroyAnalyzerOverlay();
    }
    if (!fullScreenNodeId_.has_value()) {
        return;
    }
    auto fullScreenNode = FrameNode::GetFrameNode(V2::VIDEO_ETS_TAG, fullScreenNodeId_.value());
    CHECK_NULL_VOID(fullScreenNode);
    auto parent = fullScreenNode->GetParent();
    CHECK_NULL_VOID(parent);
    parent->RemoveChild(fullScreenNode);
    parent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void VideoPattern::ResetMediaPlayerOnBg()
{
    CHECK_NULL_VOID(mediaPlayer_);
    SetIsPrepared(false);
    ContainerScope scope(instanceId_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    VideoSourceInfo videoSrc = {videoSrcInfo_.src_, videoSrcInfo_.bundleName_, videoSrcInfo_.moduleName_};

    auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    auto bgTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::BACKGROUND);
    bgTaskExecutor.PostTask(
        [weak = WeakClaim(this), mediaPlayerWeak = WeakClaim(AceType::RawPtr(mediaPlayer_)),
        videoSrc, id = instanceId_, showFirstFrame = showFirstFrame_, uiTaskExecutor, hostId = hostId_] {
        auto mediaPlayer = mediaPlayerWeak.Upgrade();
        CHECK_NULL_VOID(mediaPlayer);
        TAG_LOGI(AceLogTag::ACE_VIDEO, "Video[%{public}d] trigger mediaPlayer reset", hostId);
        mediaPlayer->ResetMediaPlayer();
        RegisterMediaPlayerEvent(weak, mediaPlayer, videoSrc.src_, id);
        if (!mediaPlayer->SetSource(videoSrc.src_, videoSrc.bundleName_, videoSrc.moduleName_)) {
            uiTaskExecutor.PostTask([weak]() {
                auto videoPattern = weak.Upgrade();
                CHECK_NULL_VOID(videoPattern);
                videoPattern->FireError(ERROR_CODE_VIDEO_SOURCE_INVALID, "Not a valid source");
                }, "ArkUIVideoFireError");
            return;
        }
        mediaPlayer->SetRenderFirstFrame(showFirstFrame);
        }, "ArkUIVideoMediaPlayerReset");
}

void VideoPattern::ResetStatus()
{
    isInitialState_ = true;
    isPlaying_ = false;
}

void VideoPattern::ResetMediaPlayer()
{
    CHECK_NULL_VOID(mediaPlayer_);
    TAG_LOGI(AceLogTag::ACE_VIDEO, "Video[%{public}d] trigger mediaPlayer reset by user", hostId_);
    mediaPlayer_->ResetMediaPlayer();
    SetIsPrepared(false);
    if (!SetSourceForMediaPlayer()) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "Video set source for mediaPlayer failed.");

        // It need post on ui thread.
        FireError(ERROR_CODE_VIDEO_SOURCE_INVALID, "Not a valid source");
        return;
    }
    mediaPlayer_->SetRenderFirstFrame(showFirstFrame_);
    RegisterMediaPlayerEvent(WeakClaim(this), mediaPlayer_, videoSrcInfo_.src_, instanceId_);
}

void VideoPattern::UpdateMediaPlayerOnBg()
{
    PrepareMediaPlayer();
    UpdateSpeed();
    UpdateLooping();
    UpdateMuted();
    if (isInitialState_ && autoPlay_) {
        // When video is autoPlay, start playing the video when it is initial state.
        Start();
    }
}

void VideoPattern::PrepareMediaPlayer()
{
    auto videoLayoutProperty = GetLayoutProperty<VideoLayoutProperty>();
    CHECK_NULL_VOID(videoLayoutProperty);
    // src has not set/changed
    if (!videoLayoutProperty->HasVideoSource() || videoLayoutProperty->GetVideoSource() == videoSrcInfo_) {
        TAG_LOGI(AceLogTag::ACE_VIDEO, "Video[%{public}d] source is null or the source has not changed.", hostId_);
        return;
    }
    auto videoSrcInfo = videoLayoutProperty->GetVideoSourceValue(VideoSourceInfo());
    videoSrcInfo_.src_ = videoSrcInfo.src_;
    videoSrcInfo_.bundleName_ = videoSrcInfo.bundleName_;
    videoSrcInfo_.moduleName_ = videoSrcInfo.moduleName_;
    if (mediaPlayer_ && !mediaPlayer_->IsMediaPlayerValid()) {
        TAG_LOGI(AceLogTag::ACE_VIDEO, "Video[%{public}d] create MediaPlayer.", hostId_);
        mediaPlayer_->CreateMediaPlayer();
    }
    if (mediaPlayer_ && !mediaPlayer_->IsMediaPlayerValid()) {
        // It need post on ui thread.
        FireError(ERROR_CODE_VIDEO_CREATE_PLAYER_FAILED, "Failed to create the media player");
        return;
    }
    ResetStatus();
    ResetMediaPlayerOnBg();
}

bool VideoPattern::SetSourceForMediaPlayer()
{
    CHECK_NULL_RETURN(mediaPlayer_, false);
    return mediaPlayer_->SetSource(videoSrcInfo_.src_, videoSrcInfo_.bundleName_, videoSrcInfo_.moduleName_);
}

void VideoPattern::RegisterMediaPlayerEvent(const WeakPtr<VideoPattern>& weak, const RefPtr<MediaPlayer>& mediaPlayer,
    const std::string& videoSrc, int32_t instanceId)
{
    if (videoSrc.empty() || !mediaPlayer) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "Video src is empty or mediaPlayer is null, register mediaPlayerEvent fail");
        return;
    }
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    RegisterMediaPlayerEventImpl(weak, mediaPlayer, instanceId, uiTaskExecutor);

    auto&& seekDoneEvent = [weak, uiTaskExecutor, instanceId](uint32_t currentPos) {
        uiTaskExecutor.PostSyncTask(
            [&weak, currentPos, instanceId] {
                auto video = weak.Upgrade();
                CHECK_NULL_VOID(video);
                ContainerScope scope(instanceId);
                video->SetIsSeeking(false);
                video->OnCurrentTimeChange(currentPos);
            }, "ArkUIVideoSeekDone");
    };
    mediaPlayer->RegisterMediaPlayerSeekDoneEvent(std::move(seekDoneEvent));
}

void VideoPattern::OnCurrentTimeChange(uint32_t currentPos)
{
    if (isPrepared_) {
        isInitialState_ = isInitialState_ ? currentPos == 0 : false;
    }
    if (currentPos == currentPos_ || isStop_) {
        return;
    }
    if (duration_ == 0) {
        int32_t duration = 0;
        if (mediaPlayer_ && mediaPlayer_->GetDuration(duration) == 0) {
            duration_ = static_cast<uint32_t>(duration / MILLISECONDS_TO_SECONDS);
            OnUpdateTime(duration_, DURATION_POS);
        }
    }
    OnUpdateTime(currentPos, CURRENT_POS);
    currentPos_ = isSeeking_ ? currentPos_ : currentPos;
    auto eventHub = GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireUpdateEvent(static_cast<double>(currentPos));
}

void VideoPattern::ChangePlayerStatus(const PlaybackStatus& status)
{
    auto eventHub = GetEventHub<VideoEventHub>();
    switch (status) {
        case PlaybackStatus::INITIALIZED:
            if (PrepareSurface() && mediaPlayer_->PrepareAsync() != 0) {
                TAG_LOGE(AceLogTag::ACE_VIDEO, "Player prepare failed");
            }
            break;
        case PlaybackStatus::STARTED:
            CHECK_NULL_VOID(eventHub);
            eventHub->FireStartEvent();
            break;
        case PlaybackStatus::PAUSED:
            CHECK_NULL_VOID(eventHub);
            eventHub->FirePauseEvent();
            break;
        case PlaybackStatus::STOPPED:
            CHECK_NULL_VOID(eventHub);
            eventHub->FireStopEvent();
            break;
        case PlaybackStatus::PREPARED: {
            ContainerScope scope(instanceId_);
            if (!mediaPlayer_ || !mediaPlayer_->IsMediaPlayerValid()) {
                return;
            }
            int32_t milliSecondDuration = 0;
            mediaPlayer_->GetDuration(milliSecondDuration);
            OnPrepared(milliSecondDuration / MILLISECONDS_TO_SECONDS, 0, true);
            break;
        }
        case PlaybackStatus::PLAYBACK_COMPLETE:
            OnCompletion();
            break;
        default:
            break;
    }
}

void VideoPattern::OnPlayerStatus(PlaybackStatus status)
{
    TAG_LOGI(AceLogTag::ACE_VIDEO, "Video[%{public}d] Player current status is %{public}s.", hostId_,
        StatusToString(status).c_str());
    bool isPlaying = (status == PlaybackStatus::STARTED);
    if (isPlaying_ != isPlaying) {
        isPlaying_ = isPlaying;
        ChangePlayButtonTag();
    }
    if (isInitialState_) {
        isInitialState_ = !isPlaying;
    }
    ChangePlayerStatus(status);
}

void VideoPattern::OnError(const std::string& errorId)
{
    AddChild();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RequestFrame();
    auto eventHub = GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireErrorEvent();
}

void VideoPattern::OnError(int32_t code, const std::string& message)
{
    AddChild();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RequestFrame();
    auto eventHub = GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireErrorEvent(code, message);
}

void VideoPattern::OnResolutionChange() const
{
    if (!mediaPlayer_ || !mediaPlayer_->IsMediaPlayerValid()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto videoLayoutProperty = host->GetLayoutProperty<VideoLayoutProperty>();
    CHECK_NULL_VOID(videoLayoutProperty);
    auto preVideoSize = videoLayoutProperty->GetVideoSize();
    if (!preVideoSize.has_value()) {
        SizeF videoSize = SizeF(
            static_cast<float>(mediaPlayer_->GetVideoWidth()),
            static_cast<float>(mediaPlayer_->GetVideoHeight()));
        videoLayoutProperty->UpdateVideoSize(videoSize);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void VideoPattern::OnStartRenderFrameCb()
{
    isInitialState_ = false;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto video = AceType::DynamicCast<VideoNode>(host);
    CHECK_NULL_VOID(video);
    auto image = AceType::DynamicCast<FrameNode>(video->GetPreviewImage());
    CHECK_NULL_VOID(image);
    auto posterLayoutProperty = image->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(posterLayoutProperty);
    posterLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
    UpdateBackgroundColor();
    image->MarkModifyDone();
    if (!mediaPlayer_ || !mediaPlayer_->IsMediaPlayerValid()) {
        return;
    }
    auto videoLayoutProperty = host->GetLayoutProperty<VideoLayoutProperty>();
    CHECK_NULL_VOID(videoLayoutProperty);
    SizeF videoSize =
        SizeF(static_cast<float>(mediaPlayer_->GetVideoWidth()), static_cast<float>(mediaPlayer_->GetVideoHeight()));
    TAG_LOGI(AceLogTag::ACE_VIDEO, "Video[%{public}d] start render frame size:%{public}s", hostId_,
        videoSize.ToString().c_str());
    videoLayoutProperty->UpdateVideoSize(videoSize);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void VideoPattern::OnPrepared(uint32_t duration, uint32_t currentPos, bool needFireEvent)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(mediaPlayer_);

    duration_ = duration;
    currentPos_ = currentPos;
    isInitialState_ = currentPos != 0 ? false : isInitialState_;
    isPlaying_ = mediaPlayer_->IsPlaying();
    SetIsSeeking(false);
    SetIsPrepared(true);
    OnUpdateTime(duration_, DURATION_POS);
    OnUpdateTime(currentPos_, CURRENT_POS);

    RefPtr<UINode> controlBar = nullptr;
    auto children = host->GetChildren();
    for (const auto& child : children) {
        if (child->GetTag() == V2::ROW_ETS_TAG) {
            controlBar = child;
            break;
        }
    }
    CHECK_NULL_VOID(controlBar);
    auto sliderNode = DynamicCast<FrameNode>(controlBar->GetChildAtIndex(SLIDER_POS));
    auto sliderPaintProperty = sliderNode->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(sliderPaintProperty);
    sliderPaintProperty->UpdateMin(0.0f);
    sliderPaintProperty->UpdateMax(static_cast<float>(duration_));
    sliderNode->MarkModifyDone();
    auto playBtn = DynamicCast<FrameNode>(controlBar->GetChildAtIndex(0));
    ChangePlayButtonTag(playBtn);

    if (needFireEvent) {
        auto eventHub = GetEventHub<VideoEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->FirePreparedEvent(static_cast<double>(duration_));
    }
    TAG_LOGI(AceLogTag::ACE_VIDEO,
        "Video[%{public}d] duration: %{public}u, loop: %{public}d, muted: %{public}d, Speed: %{public}f", hostId_,
        duration_, loop_, muted_, progressRate_);
    UpdateLooping();
    UpdateSpeed();
    UpdateMuted();
    checkNeedAutoPlay();
}

void VideoPattern::checkNeedAutoPlay()
{
    if (isStop_) {
        isStop_ = false;
    }
    if (autoPlay_) {
        Start();
    }
}

void VideoPattern::OnCompletion()
{
    isPlaying_ = false;
    currentPos_ = duration_;
    OnUpdateTime(currentPos_, CURRENT_POS);
    auto eventHub = GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireFinishEvent();
}

bool VideoPattern::HasPlayer() const
{
    return mediaPlayer_ != nullptr;
}

void VideoPattern::HiddenChange(bool hidden)
{
    if (isPlaying_ && hidden && HasPlayer()) {
        pastPlayingStatus_ = isPlaying_;
        Pause();
        return;
    }

    if (!hidden && pastPlayingStatus_) {
        pastPlayingStatus_ = false;
        Start();
    }
}

void VideoPattern::OnVisibleChange(bool isVisible)
{
    if (hiddenChangeEvent_) {
        hiddenChangeEvent_(!isVisible);
    }
}

void VideoPattern::UpdateLooping()
{
    if (mediaPlayer_ && mediaPlayer_->IsMediaPlayerValid()) {
        ContainerScope scope(instanceId_);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto context = host->GetContext();
        CHECK_NULL_VOID(context);
        auto bgTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::BACKGROUND);
        bgTaskExecutor.PostTask([weak = WeakClaim(RawPtr(mediaPlayer_)), loop = loop_] {
            auto mediaPlayer = weak.Upgrade();
            CHECK_NULL_VOID(mediaPlayer);
            mediaPlayer->SetLooping(loop);
            }, "ArkUIVideoUpdateLooping");
    }
}

void VideoPattern::SetSurfaceBackgroundColor(Color color)
{
    CHECK_NULL_VOID(renderContextForMediaPlayer_);
    surfaceBgColor_ = color;
    renderContextForMediaPlayer_->UpdateBackgroundColor(color);
}

void VideoPattern::UpdateSpeed()
{
    if (mediaPlayer_ && mediaPlayer_->IsMediaPlayerValid()) {
        ContainerScope scope(instanceId_);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto context = host->GetContext();
        CHECK_NULL_VOID(context);
        auto bgTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::BACKGROUND);
        bgTaskExecutor.PostTask([weak = WeakClaim(RawPtr(mediaPlayer_)), progress = progressRate_] {
            auto mediaPlayer = weak.Upgrade();
            CHECK_NULL_VOID(mediaPlayer);
            mediaPlayer->SetPlaybackSpeed(static_cast<float>(progress));
            }, "ArkUIVideoUpdateSpeed");
    }
}

void VideoPattern::UpdateMuted()
{
    if (mediaPlayer_ && mediaPlayer_->IsMediaPlayerValid()) {
        ContainerScope scope(instanceId_);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto context = host->GetContext();
        CHECK_NULL_VOID(context);
        auto bgTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::BACKGROUND);
        bgTaskExecutor.PostTask(
            [weak = WeakClaim(RawPtr(mediaPlayer_)), isMuted = muted_, currentVolume = currentVolume_] {
                auto mediaPlayer = weak.Upgrade();
                CHECK_NULL_VOID(mediaPlayer);
                if (isMuted || NearZero(currentVolume)) {
                    mediaPlayer->SetMediaMuted(MEDIA_TYPE_AUD, true);
                    mediaPlayer->SetVolume(0.0f, 0.0f);
                } else {
                    mediaPlayer->SetMediaMuted(MEDIA_TYPE_AUD, false);
                    mediaPlayer->SetVolume(currentVolume, currentVolume);
                }
            },
            "ArkUIVideoUpdateMuted");
    }
}

void VideoPattern::OnUpdateTime(uint32_t time, int pos) const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<VideoLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    bool needControlBar = layoutProperty->GetControlsValue(true);
    CHECK_NULL_VOID(needControlBar);

    RefPtr<UINode> controlBar = nullptr;
    auto children = host->GetChildren();
    for (const auto& child : children) {
        if (child->GetTag() == V2::ROW_ETS_TAG) {
            controlBar = child;
            break;
        }
    }

    CHECK_NULL_VOID(controlBar);
    auto durationNode = DynamicCast<FrameNode>(controlBar->GetChildAtIndex(pos));
    CHECK_NULL_VOID(durationNode);
    auto textLayoutProperty = durationNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    std::string timeText = IntTimeToText(time);
    textLayoutProperty->UpdateContent(timeText);
    durationNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    durationNode->MarkModifyDone();
    // if current status is seeking, no need to update slider's value
    if (pos == CURRENT_POS && !isSeeking_) {
        auto sliderNode = DynamicCast<FrameNode>(controlBar->GetChildAtIndex(SLIDER_POS));
        CHECK_NULL_VOID(sliderNode);
        auto sliderPattern = sliderNode->GetPattern<SliderPattern>();
        CHECK_NULL_VOID(sliderPattern);
        sliderPattern->UpdateValue(static_cast<float>(time));
        sliderNode->MarkModifyDone();
    }
}

bool VideoPattern::PrepareSurface()
{
    CHECK_NULL_RETURN(mediaPlayer_, false);
    renderSurface_->SetRenderContext(renderContextForMediaPlayer_);
    if (!renderSurface_->IsSurfaceValid()) {
        renderSurface_->InitSurface();
        mediaPlayer_->SetRenderSurface(renderSurface_);
    }
    if (mediaPlayer_->SetSurface() != 0) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "mediaPlayer renderSurface set failed");
        return false;
    }
    return true;
}

void VideoPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    THREAD_SAFE_NODE_CHECK(host, OnAttachToFrameNode, host);
    // full screen node is not supposed to register js controller event
    if (!InstanceOf<VideoFullScreenPattern>(this)) {
        SetMethodCall();
    }
    CHECK_NULL_VOID(host);
    hostId_ = host->GetId();
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddWindowStateChangedCallback(host->GetId());
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    static RenderContext::ContextParam param = { RenderContext::ContextType::HARDWARE_SURFACE, "MediaPlayerSurface",
                                                 RenderContext::PatternType::VIDEO };
    renderContextForMediaPlayer_->InitContext(false, param);
    renderContext->UpdateBackgroundColor(Color::BLACK);
    renderContextForMediaPlayer_->UpdateBackgroundColor(Color::BLACK);
    renderContext->SetClipToBounds(true);
}

void VideoPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_EQUAL_VOID(frameNode->IsThreadSafeNode(), true);
    auto id = frameNode->GetId();
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowStateChangedCallback(id);
}

void VideoPattern::OnAttachToMainTree()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    CHECK_EQUAL_VOID(host->IsThreadSafeNode(), false);
    // full screen node is not supposed to register js controller event
    if (!InstanceOf<VideoFullScreenPattern>(this)) {
        SetMethodCall();
    }
    hostId_ = host->GetId();
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddWindowStateChangedCallback(hostId_);
#ifdef ENABLE_ROSEN_BACKEND
    auto rosenRenderContext = AceType::DynamicCast<NG::RosenRenderContext>(renderContextForMediaPlayer_);
    multiThreadModifier_ = multiThreadModifier_ == nullptr ?
        std::make_shared<Rosen::ModifierNG::RSFrameClipModifier>() :
        multiThreadModifier_;
    CHECK_NULL_VOID(multiThreadModifier_);
    multiThreadModifier_->SetFrameGravity(Rosen::Gravity::RESIZE);
    multiThreadModifier_->SetClipToFrame(true);
    std::shared_ptr<Rosen::RSNode> rsNode = rosenRenderContext->GetRSNode();
    CHECK_NULL_VOID(rsNode);
    rsNode->AddModifier(multiThreadModifier_);
#endif
}

void VideoPattern::OnDetachFromMainTree()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (host->GetNodeStatus() == NodeStatus::BUILDER_NODE_OFF_MAINTREE) {
        Pause();
    }
    CHECK_EQUAL_VOID(host->IsThreadSafeNode(), false);
    auto id = host->GetId();
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowStateChangedCallback(id);
}

void VideoPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    if (!hiddenChangeEvent_) {
        SetHiddenChangeEvent(CreateHiddenChangeEvent());
    }
    // src has changed
    auto layoutProperty = GetLayoutProperty<VideoLayoutProperty>();
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) &&
        (layoutProperty && layoutProperty->HasVideoSource() && layoutProperty->GetVideoSource() != videoSrcInfo_)) {
        ResetStatus();
    }
    // update full screen pattern state
    UpdateFsState();
    // Update the control bar and preview image.
    UpdatePreviewImage();
    UpdateControllerBar();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    // Update the media player when video node is not in full screen or current node is full screen node
    if (!fullScreenNodeId_.has_value() || InstanceOf<VideoFullScreenNode>(this)) {
        ContainerScope scope(instanceId_);
        auto pipelineContext = host->GetContext();
        CHECK_NULL_VOID(pipelineContext);
        auto uiTaskExecutor = SingleTaskExecutor::Make(pipelineContext->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        uiTaskExecutor.PostTask([weak = WeakClaim(this)]() {
            auto videoPattern = weak.Upgrade();
            CHECK_NULL_VOID(videoPattern);
            ContainerScope scope(videoPattern->instanceId_);
            videoPattern->UpdateMediaPlayerOnBg();
            }, "ArkUIVideoUpdateMediaPlayer");
    }
    auto eventHub = GetEventHub<VideoEventHub>();
    if (!AceType::InstanceOf<VideoFullScreenPattern>(this)) {
        eventHub->SetInspectorId(host->GetInspectorIdValue(""));
    }
    if (!IsSupportImageAnalyzer()) {
        DestroyAnalyzerOverlay();
    } else if (isPaused_ && !isPlaying_ && !GetAnalyzerState()) {
        StartImageAnalyzer();
    }
    InitKeyEvent();
}
} // namespace OHOS::Ace::NG