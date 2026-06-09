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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIDEO_VIDEO_STATE_MACHINE_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIDEO_VIDEO_STATE_MACHINE_PATTERN_H
#include <mutex>
#include <queue>

#include "base/geometry/dimension.h"
#include "base/geometry/size.h"
#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/pattern/video/video_controller_async.h"
#include "core/components_ng/image_provider/image_loading_context.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/video/video_accessibility_property.h"
#include "core/components_ng/pattern/video/video_event_hub.h"
#include "core/components_ng/pattern/video/video_layout_algorithm.h"
#include "core/components_ng/pattern/video/video_layout_property.h"
#include "core/components_ng/pattern/video/video_state_manager.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/media_player.h"
#include "core/components_ng/render/render_surface.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/base/geometry/rect.h"

namespace OHOS::Ace {
class ImageAnalyzerManager;
}
namespace OHOS::Ace::NG {
class VideoStateMachinePattern : public Pattern {
    DECLARE_ACE_TYPE(VideoStateMachinePattern, Pattern);
    friend class VideoStateManager;
    friend class VideoStateMachineFullScreenPattern;
    friend class ::OHOS::Ace::VideoControllerAsync;

public:
    using HiddenChangeEvent = std::function<void(bool)>;

    VideoStateMachinePattern() = delete;
    explicit VideoStateMachinePattern(const RefPtr<VideoControllerAsync>& videoControllerAsync);
    ~VideoStateMachinePattern() override;

    void OnControllerDestroyed();
    void SetVideoControllerAsync(const RefPtr<VideoControllerAsync>& videoControllerAsync);

    bool IsEnableMatchParent() override
    {
        return true;
    }

    bool IsEnableFix() override
    {
        return true;
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<VideoEventHub>();
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<VideoLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<VideoLayoutAlgorithm>();
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<VideoAccessibilityProperty>();
    }

    bool IsSupportDrawModifier() const override
    {
        return false;
    }

    void UpdateMuted(bool muted)
    {
        muted_ = muted;
    }

    bool GetMuted() const
    {
        return muted_;
    }

    void UpdateAutoPlay(bool autoPlay)
    {
        autoPlay_ = autoPlay;
    }

    bool GetAutoPlay() const
    {
        return autoPlay_;
    }

    void UpdateLoop(bool loop)
    {
        loop_ = loop;
    }

    bool GetLoop() const
    {
        return loop_;
    }

    void UpdateControllerBar();

    void SetSurfaceBackgroundColor(Color color);

    virtual bool IsFullScreen() const;

    void OnColorConfigurationUpdate() override;

    void UpdateShowImagePreview(bool showImagePreview)
    {
        showImagePreview_ = showImagePreview;
    }

    void UpdateShowFirstFrame(bool showFirstFrame)
    {
        showFirstFrame_ = showFirstFrame;
    }

    void UpdateProgressRate(double progressRate)
    {
        progressRate_ = progressRate;
    }

    double GetProgressRate() const
    {
        return progressRate_;
    }

    FocusPattern GetFocusPattern() const override
    {
        // Video focus type is scope, it is a container, inner focus is on slider now.
        return { FocusType::SCOPE, true };
    }

    RefPtr<FrameNode> CreateControlBar(int32_t nodeId = -1);

    void SetHiddenChangeEvent(HiddenChangeEvent&& hiddenChangeEvent)
    {
        hiddenChangeEvent_ = std::move(hiddenChangeEvent);
    }

    uint32_t GetCurrentPos() const
    {
        return currentPos_;
    }

    uint32_t GetDuration() const
    {
        return duration_;
    }

    bool GetInitialState() const
    {
        return isInitialState_;
    }

    virtual bool OnBackPressed()
    {
        return false;
    }

    void OnVisibleChange(bool isVisible) override;

    void OnAreaChangedInner() override;

    // It is used to init mediaplayer on background.
    void UpdateMediaPlayerOnBg();
    void ResetMediaPlayerOnBg(VideoControllerAsync::AsyncCommandCallback callback = nullptr);
    // Functions for the video controller.
    void Start(VideoControllerAsync::AsyncCommandCallback callback = nullptr);
    void Pause(VideoControllerAsync::AsyncCommandCallback callback = nullptr);
    void Stop(VideoControllerAsync::AsyncCommandCallback callback = nullptr);

    bool IsFirstPlay() const
    {
        return isInitialState_;
    }

    const std::string& GetSrc() const
    {
        return videoSrcInfo_.src_;
    }

    void UpdateMediaParam(const RefPtr<MediaPlayer>& mediaPlayer, const RefPtr<RenderSurface>& renderSurface,
        const RefPtr<RenderContext>& renderContext)
    {
        mediaPlayer_ = mediaPlayer;
        renderSurface_ = renderSurface;
        renderContextForMediaPlayer_ = renderContext;
    }

    void ResetMediaParam()
    {
        mediaPlayer_.Reset();
        renderSurface_.Reset();
        RemoveMediaPlayerSurfaceNode();
        renderContextForMediaPlayer_.Reset();
    }

    void RemoveMediaPlayerSurfaceNode();

    void OnFullScreenChange(bool isFullScreen);

    void RecoverState(const RefPtr<VideoStateMachinePattern>& videoPattern);

    RefPtr<FrameNode> GetFullScreenNode() const
    {
        if (!fullScreenNodeId_.has_value()) {
            return nullptr;
        }
        return FrameNode::GetFrameNode(V2::VIDEO_ETS_TAG, fullScreenNodeId_.value());
    }

    void OnPlayerStatus(PlaybackStatus status);

    void OnCurrentTimeChange(uint32_t currentPos);

    void OnError(const std::string& errorId);

    void OnError(int32_t code, const std::string& message);

    void OnResolutionChange() const;

    void OnStartRenderFrameCb();

    void ResetLastBoundsRect()
    {
        lastBoundsRect_.SetRect(0.0f, 0.0f, 0.0f, 0.0f);
    }

    RefPtr<VideoStateMachinePattern> GetTargetVideoPattern();
    void EnableAnalyzer(bool enable);
    void SetImageAnalyzerConfig(void* config);
    void StartUpdateImageAnalyzer();
    void SetImageAIOptions(void* options);
    bool GetAnalyzerState();
    void UpdateAnalyzerState(bool isCreated)
    {
        isAnalyzerCreated_ = isCreated;
    }
    void SetIsSeeking(bool isSeeking)
    {
        isSeeking_ = isSeeking;
    }
    bool GetIsSeeking() const
    {
        return isSeeking_;
    }

    static void RegisterMediaPlayerEvent(const WeakPtr<VideoStateMachinePattern>& weak, const RefPtr<MediaPlayer>& mediaPlayer,
        const std::string& videoSrc, int32_t instanceId);

    void SetShortcutKeyEnabled(bool isEnableShortcutKey);
    bool GetShortcutKeyEnabled() const;

    void SetCurrentVolume(float currentVolume);
    float GetCurrentVolume() const;
    int32_t OnInjectionEvent(const std::string& command) override;
    PlaybackStatus GetCurrentPlaybackStatus() const
    {
        return currentPlaybackStatus_;
    }
    bool GetsIsProgressInjectCmd() const
    {
        return isProgressInjectCmd_;
    }
    double GetLastProgressRate() const
    {
        return lastProgressRate_;
    }
    double GetLastSetProgressRate() const
    {
        return lastSetProgressRate_;
    }
    int32_t GetInstanceId() const
    {
        return instanceId_;
    }
    void SetIsProgressInjectCmd(bool isProgressInjectCmd)
    {
        isProgressInjectCmd_ = isProgressInjectCmd;
    }
    void SetLastProgressRate(double lastProgressRate)
    {
        lastProgressRate_ = lastProgressRate;
    }
    void SetLastSetProgressRate(double lastSetProgressRate)
    {
        lastSetProgressRate_ = lastSetProgressRate;
    }

#ifdef RENDER_EXTRACT_SUPPORTED
    void OnTextureRefresh(void* surface);
#endif

    void SetContentTransition(ContentTransitionType contentTransition);

protected:
    void OnUpdateTime(uint32_t time, int pos) const;

    RefPtr<MediaPlayer> mediaPlayer_ = MediaPlayer::Create();
    RefPtr<RenderSurface> renderSurface_ = RenderSurface::Create();
    RefPtr<RenderContext> renderContextForMediaPlayer_ = RenderContext::Create();

    int32_t instanceId_;

#if defined(RENDER_EXTRACT_SUPPORTED) && defined(ENABLE_ROSEN_BACKEND)
    WeakPtr<RenderSurface> renderSurfaceWeakPtr_;
    WeakPtr<RenderContext> renderContextForMediaPlayerWeakPtr_;
#endif

    void OnAttachToFrameNodeMultiThread(const RefPtr<FrameNode>& host);

    void FullScreen();
    void SetCurrentTime(float currentPos, SeekMode seekMode = SeekMode::SEEK_PREVIOUS_SYNC);

private:
    void OnAttachToFrameNode() override;
    void OnAttachToMainTree() override;
    void OnDetachFromFrameNode(FrameNode* frameNode) override;
    void OnDetachFromMainTree() override;
    void OnModifyDone() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void OnRebuildFrame() override;
    void OnWindowHide() override;
    void InitKeyEvent();
    bool OnKeyEvent(const KeyEvent& event);
    bool HandleSliderKeyEvent(const KeyEventInfo& event);
    void AddChild();

    // Set properties for media player.
    void PrepareMediaPlayer();

    bool SetSourceForMediaPlayer();
    void UpdateLooping();
    void UpdateSpeed();
    void HandleSetPlaybackRateResult(double progress, int32_t errorCode, std::string& errorMsg);
    void UpdateMuted();
    void PrepareSurface();

    bool HasPlayer() const;

    void SetFullScreenButtonCallBack(RefPtr<FrameNode>& fullScreenBtn);

    void OnSliderChange(float posTime, int32_t mode);

    void UpdatePreviewImage();
    void UpdateVideoProperty();

    RefPtr<FrameNode> CreateSVG();
    RefPtr<FrameNode> CreateText(uint32_t time);
    RefPtr<FrameNode> CreateSlider();
    void ChangePlayButtonTag();
    void ChangePlayButtonTag(RefPtr<FrameNode>& playBtn);

    void ChangeFullScreenButtonTag(bool isFullScreen, RefPtr<FrameNode>& fullScreenBtn);
    void ResetStatus();
    void HiddenChange(bool hidden);

    void UpdateFsState();

    // Fire error manually, eg. src is not existed. It must run on ui.
    void FireError(int32_t code, const std::string& message);

    HiddenChangeEvent CreateHiddenChangeEvent();

    void SetMediaFullScreen(bool isFullScreen)
    {
        mediaPlayer_->FullScreenChange(isFullScreen);
        if (SystemProperties::GetExtSurfaceEnabled()) {
            renderSurface_->SetIsFullScreen(isFullScreen);
        }
    }

#ifdef RENDER_EXTRACT_SUPPORTED
    void* GetNativeWindow(int32_t instanceId, int64_t textureId);
#endif
    void UpdatePreparedVideoSize(const RefPtr<FrameNode>& host);

    void RegisterRenderContextCallBack();
    void ChangePlayerStatus(const PlaybackStatus& status);

    bool IsSupportImageAnalyzer();
    bool ShouldUpdateImageAnalyzer();
    void StartImageAnalyzer();
    void CreateAnalyzerOverlay();
    void DestroyAnalyzerOverlay();
    void UpdateAnalyzerOverlay();
    void UpdateAnalyzerUIConfig(const RefPtr<NG::GeometryNode>& geometryNode);
    void UpdateOverlayVisibility(VisibleType type);
    void UpdateBackgroundColor();

    void OnKeySpaceEvent();
    void MoveByStep(int32_t step);
    void AdjustVolume(int32_t step);

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    void SaveCurrentPlaybackStatus(PlaybackStatus status);
    static int32_t ParseCommand(const std::string& command, PlaybackStatus& status, double& speed);
    void ReportChangeEvent(PlaybackStatus status, double playbackSpeed, uint32_t currentPos);
    void ReportCommandResult(const std::string& event, const std::string& result, const std::string& reason = "");
    void ReportChangeEventOnUIThread(PlaybackStatus status, double playbackSpeed, uint32_t currentPos);
    void ReportCommandResultOnUIThread(
        const std::string& event, const std::string& result, const std::string& reason = "");

    std::string GetDumpInfo();
    void GetSimplifyDumpInfo(std::unique_ptr<JsonValue>& json);
    void DumpInfo() override;
    void DumpInfo(std::unique_ptr<JsonValue>& json) override;
    void DumpSimplifyInfo(std::shared_ptr<JsonValue>& json) override;

    RefPtr<VideoControllerAsync> videoControllerAsync_;
    RefPtr<FrameNode> controlBar_;

    GestureEventFunc playBtnCallBack_;
    GestureEventFunc pauseBtnCallBack_;
    HiddenChangeEvent hiddenChangeEvent_;

    // Video src.
    VideoSourceInfo videoSrcInfo_;
    bool showImagePreview_ = false;
    bool showFirstFrame_ = false;
    bool isInitialState_ = true; // First play state is true. Play or seek will set it to false.

    RefPtr<VideoStateManager> stateManager_ = MakeRefPtr<VideoStateManager>(WeakClaim(this));

    bool TransitionTo(VideoPlaybackState newState);
    bool TransitionToIfAllowed(VideoPlaybackState newState, const char* caller);

    // State entered callbacks for VideoStateManager
    void OnCreatedStateEntered();
    void OnPreparedStateEntered();
    void OnPlayingStateEntered();
    void OnPausedStateEntered();
    void OnStoppedStateEntered();
    void OnCompletedStateEntered();
    void OnErrorStateEntered();

    bool muted_ = false;
    bool autoPlay_ = false;
    bool loop_ = false;

    bool pastPlayingStatus_ = false;

    bool isEnableAnalyzer_ = false;
    bool isAnalyzerCreated_ = false;
    bool isContentSizeChanged_ = false;
    bool isSeeking_ = false;
    bool isEnableShortcutKey_ = false;

    uint32_t currentPos_ = 0;
    uint32_t duration_ = 0;
    float currentVolume_ = 1.0f;

    // full screen node id
    std::optional<int32_t> fullScreenNodeId_;
    int32_t hostId_ = 0;

    // Video playback speed.
    double progressRate_ = 1.0;

    Rect lastBoundsRect_;
    Rect contentRect_;
    std::shared_ptr<ImageAnalyzerManager> imageAnalyzerManager_;

    ContentTransitionType contentTransition_ = ContentTransitionType::IDENTITY;
    Color surfaceBgColor_ = Color::BLACK;

    PlaybackStatus currentPlaybackStatus_ = PlaybackStatus::NONE;
    std::string currentInjectedStatusCmd_ = "";
    bool isProgressInjectCmd_ = false;
    double lastProgressRate_ = 0.0;
    double lastSetProgressRate_ = 1.0;

    // Error info for OnErrorStateEntered callback
    int32_t lastErrorCode_ = 0;
    std::string lastErrorMessage_;

    // Serial background task queue to ensure media operations execute in order
    struct SerialBgTask {
        std::string name;
        std::function<void()> task;
    };
    void PostSerialBgTask(std::function<void()> task, const std::string& name = "");
    void DrainNextSerialBgTaskOnBg(const SingleTaskExecutor& bgTaskExecutor);
    std::mutex serialBgQueueMutex_;
    std::queue<SerialBgTask> serialBgTaskQueue_;
    bool isDrainingSerialBgQueue_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(VideoStateMachinePattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIDEO_VIDEO_STATE_MACHINE_PATTERN_H
