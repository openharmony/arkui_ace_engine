/*
 * Copyright (c) 2022-2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/video/video_state_machine_pattern.h"

#include "core/components_ng/pattern/video/video_state_manager.h"
#include "video_node.h"

#include "base/background_task_helper/background_task_helper.h"
#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/i18n/localization.h"
#include "base/image/image_perf.h"
#include "base/json/json_util.h"
#include "base/thread/task_executor.h"
#include "base/utils/string_utils.h"
#include "base/utils/system_properties.h"
#include "base/utils/multi_thread.h"
#include "base/utils/utils.h"
#include "core/common/ace_engine.h"
#include "core/common/ai/image_analyzer_manager.h"
#include "core/common/statistic_event_reporter.h"
#include "core/common/udmf/udmf_client.h"
#include "core/components_ng/pattern/video/video_theme.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/image/image_render_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/video/video_full_screen_node.h"
#include "core/components_ng/pattern/video/video_state_machine_full_screen_pattern.h"
#include "core/components_ng/property/gradient_property.h"
#include "frameworks/core/interfaces/native/node/node_slider_modifier.h"
#include "core/interfaces/native/node/node_api.h"
#include "interfaces/inner_api/ui_session/ui_session_manager.h"


#ifdef RENDER_EXTRACT_SUPPORTED
#include "core/common/ace_view.h"
#ifdef RS_ENABLE_VK
#include "render_service_base/include/platform/common/rs_system_properties.h"
#endif
#endif

namespace OHOS::Ace::NG {
namespace {
using HiddenChangeEvent = std::function<void(bool)>;
constexpr uint32_t SECONDS_PER_HOUR = 3600;
constexpr uint32_t SECONDS_PER_MINUTE = 60;
const std::string FORMAT_HH_MM_SS = "%02d:%02d:%02d";
const std::string FORMAT_MM_SS = "%02d:%02d";
constexpr int32_t MILLISECONDS_TO_SECONDS = 1000;
constexpr uint32_t CURRENT_POS = 1;
constexpr uint32_t SLIDER_POS = 2;
constexpr uint32_t DURATION_POS = 3;
constexpr uint32_t FULL_SCREEN_POS = 4;
constexpr int32_t AVERAGE_VALUE = 2;
constexpr int32_t ANALYZER_DELAY_TIME = 100;
constexpr int32_t ANALYZER_CAPTURE_DELAY_TIME = 1000;
const Dimension LIFT_HEIGHT = 28.0_vp;
const std::string PNG_FILE_EXTENSION = "png";
constexpr int32_t MEDIA_TYPE_AUD = 0;
constexpr float VOLUME_STEP = 0.05f;
constexpr float SPEED_0_125_X = 0.125;
constexpr float SPEED_8_00_X = 8.00;
constexpr float DEFAULT_PROGRESS_RATE = 1.0;
enum class PlayBackRate {
    SUCCESS = 0,
    MSERR_INVALID_VAL = 401,
    MSERR_INVALID_OPERATION = 5400102,
};

const std::unordered_set<ImageFit> EXPORT_IMAGEFIT_SUPPORT_TYPES = {
    ImageFit::FILL,
    ImageFit::CONTAIN,
    ImageFit::COVER,
    ImageFit::FITWIDTH, //FITWIDTH is used instead of AUTO
    ImageFit::NONE,
    ImageFit::SCALE_DOWN,
    ImageFit::TOP_LEFT,
    ImageFit::TOP,
    ImageFit::TOP_END,
    ImageFit::START,
    ImageFit::CENTER,
    ImageFit::END,
    ImageFit::BOTTOM_START,
    ImageFit::BOTTOM,
    ImageFit::BOTTOM_END
};

enum SliderChangeMode {
    BEGIN = 0,
    MOVING,
    END,
};

std::string IntTimeToText(uint32_t time)
{
    auto minutes = (time % SECONDS_PER_HOUR) / SECONDS_PER_MINUTE;
    auto seconds = time % SECONDS_PER_MINUTE;
    if (time >= SECONDS_PER_HOUR) {
        auto hours = time / SECONDS_PER_HOUR;
        return StringUtils::FormatString(FORMAT_HH_MM_SS.c_str(), hours, minutes, seconds);
    }
    return StringUtils::FormatString(FORMAT_MM_SS.c_str(), minutes, seconds);
}

SizeF CalculateFitContain(const SizeF& videoSize, const SizeF& layoutSize)
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

SizeF CalculateFitFill(const SizeF& layoutSize)
{
    return layoutSize;
}

SizeF CalculateFitCover(const SizeF& videoSize, const SizeF& layoutSize)
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

SizeF CalculateFitNone(const SizeF& videoSize)
{
    return videoSize;
}

SizeF CalculateFitScaleDown(const SizeF& videoSize, const SizeF& layoutSize)
{
    if (layoutSize.Width() > videoSize.Width()) {
        return CalculateFitNone(videoSize);
    }
    return CalculateFitContain(videoSize, layoutSize);
}

RectF MeasureVideoContentLayout(const SizeF& layoutSize, const RefPtr<VideoLayoutProperty>& layoutProperty)
{
    if (!layoutProperty || !layoutProperty->HasVideoSize()) {
        return {0.0f, 0.0f, layoutSize.Width(), layoutSize.Height()};
    }

    auto videoSize = layoutProperty->GetVideoSizeValue(SizeF(0, 0));
    auto videoFrameSize = videoSize;
    auto imageFit = layoutProperty->GetObjectFitValue(ImageFit::COVER);
    auto rect = RectF();
    switch (imageFit) {
        case ImageFit::CONTAIN: case ImageFit::FITWIDTH: //FITWIDTH is used instead of AUTO
            videoFrameSize = CalculateFitContain(videoSize, layoutSize);
            rect = RectF{(layoutSize.Width() - videoFrameSize.Width()) / AVERAGE_VALUE,
                (layoutSize.Height() - videoFrameSize.Height()) / AVERAGE_VALUE,
                videoFrameSize.Width(), videoFrameSize.Height()};
            break;
        case ImageFit::FILL:
            videoFrameSize = CalculateFitFill(layoutSize);
            rect = RectF{(layoutSize.Width() - videoFrameSize.Width()) / AVERAGE_VALUE,
                (layoutSize.Height() - videoFrameSize.Height()) / AVERAGE_VALUE,
                videoFrameSize.Width(), videoFrameSize.Height()};
            break;
        case ImageFit::COVER:
            videoFrameSize = CalculateFitCover(videoSize, layoutSize);
            rect = RectF{(layoutSize.Width() - videoFrameSize.Width()) / AVERAGE_VALUE,
                (layoutSize.Height() - videoFrameSize.Height()) / AVERAGE_VALUE,
                videoFrameSize.Width(), videoFrameSize.Height()};
            break;
        case ImageFit::NONE:
            videoFrameSize = CalculateFitNone(videoSize);
            rect = RectF{(layoutSize.Width() - videoFrameSize.Width()) / AVERAGE_VALUE,
                (layoutSize.Height() - videoFrameSize.Height()) / AVERAGE_VALUE,
                videoFrameSize.Width(), videoFrameSize.Height()};
            break;
        case ImageFit::SCALE_DOWN:
            videoFrameSize = CalculateFitScaleDown(videoSize, layoutSize);
            rect = RectF{(layoutSize.Width() - videoFrameSize.Width()) / AVERAGE_VALUE,
                (layoutSize.Height() - videoFrameSize.Height()) / AVERAGE_VALUE,
                videoFrameSize.Width(), videoFrameSize.Height()};
            break;
        case ImageFit::TOP_LEFT:
            rect = RectF{0.0f, 0.0f, videoSize.Width(), videoSize.Height()};
            break;
        case ImageFit::TOP:
            rect = RectF{(layoutSize.Width() - videoFrameSize.Width()) / AVERAGE_VALUE, 0.0f,
                videoSize.Width(), videoSize.Height()};
            break;
        case ImageFit::TOP_END:
            rect = RectF{layoutSize.Width() - videoFrameSize.Width(), 0.0f, videoSize.Width(), videoSize.Height()};
            break;
        case ImageFit::START:
            rect = RectF{0.0f, (layoutSize.Height() - videoFrameSize.Height()) / AVERAGE_VALUE,
                videoSize.Width(), videoSize.Height()};
            break;
        case ImageFit::CENTER:
            rect = RectF{(layoutSize.Width() - videoFrameSize.Width()) / AVERAGE_VALUE,
                (layoutSize.Height() - videoFrameSize.Height()) / AVERAGE_VALUE, videoSize.Width(), videoSize.Height()};
            break;
        case ImageFit::END:
            rect = RectF{layoutSize.Width() - videoFrameSize.Width(),
                (layoutSize.Height() - videoFrameSize.Height()) / AVERAGE_VALUE, videoSize.Width(), videoSize.Height()};
            break;
        case ImageFit::BOTTOM_START:
            rect = RectF{0.0f, layoutSize.Height() - videoFrameSize.Height(), videoSize.Width(), videoSize.Height()};
            break;
        case ImageFit::BOTTOM:
            rect = RectF{(layoutSize.Width() - videoFrameSize.Width()) / AVERAGE_VALUE,
                layoutSize.Height() - videoFrameSize.Height(), videoSize.Width(), videoSize.Height()};
            break;
        case ImageFit::BOTTOM_END:
            rect = RectF{layoutSize.Width() - videoFrameSize.Width(), layoutSize.Height() - videoFrameSize.Height(),
                videoSize.Width(), videoSize.Height()};
            break;
        default:
            videoFrameSize = CalculateFitCover(videoSize, layoutSize);
            rect = RectF{(layoutSize.Width() - videoFrameSize.Width()) / AVERAGE_VALUE,
                (layoutSize.Height() - videoFrameSize.Height()) / AVERAGE_VALUE,
                videoFrameSize.Width(), videoFrameSize.Height()};
            break;
    }
    return rect;
}

float RoundValueToPixelGrid(float value, bool isRound, bool forceCeil, bool forceFloor)
{
    float fractials = fmod(value, 1.0f);
    if (fractials < 0.0f) {
        ++fractials;
    }
    if (forceCeil) {
        return (value - fractials + 1.0f);
    } else if (forceFloor) {
        return (value - fractials);
    } else if (isRound) {
        if (NearEqual(fractials, 1.0f) || GreatOrEqual(fractials, 0.50f)) {
            return (value - fractials + 1.0f);
        } else {
            return (value - fractials);
        }
    }
    return value;
}

RectF AdjustPaintRect(float positionX, float positionY, float width, float height, bool isRound)
{
    RectF rect;
    float relativeLeft = positionX;
    float relativeTop = positionY;
    float nodeWidth = width;
    float nodeHeight = height;
    float absoluteRight = relativeLeft + nodeWidth;
    float absoluteBottom = relativeTop + nodeHeight;
    float roundToPixelErrorX = 0.0f;
    float roundToPixelErrorY = 0.0f;

    float nodeLeftI = RoundValueToPixelGrid(relativeLeft, isRound, false, false);
    float nodeTopI = RoundValueToPixelGrid(relativeTop, isRound, false, false);
    roundToPixelErrorX += nodeLeftI - relativeLeft;
    roundToPixelErrorY += nodeTopI - relativeTop;
    rect.SetLeft(nodeLeftI);
    rect.SetTop(nodeTopI);

    float nodeWidthI = RoundValueToPixelGrid(absoluteRight, isRound, false, false) - nodeLeftI;
    float nodeWidthTemp = RoundValueToPixelGrid(nodeWidth, isRound, false, false);
    roundToPixelErrorX += nodeWidthI - nodeWidth;
    if (roundToPixelErrorX > 0.5f) {
        nodeWidthI -= 1.0f;
        roundToPixelErrorX -= 1.0f;
    }
    if (roundToPixelErrorX < -0.5f) {
        nodeWidthI += 1.0f;
        roundToPixelErrorX += 1.0f;
    }
    if (nodeWidthI < nodeWidthTemp) {
        roundToPixelErrorX += nodeWidthTemp - nodeWidthI;
        nodeWidthI = nodeWidthTemp;
    }

    float nodeHeightI = RoundValueToPixelGrid(absoluteBottom, isRound, false, false) - nodeTopI;
    float nodeHeightTemp = RoundValueToPixelGrid(nodeHeight, isRound, false, false);
    roundToPixelErrorY += nodeHeightI - nodeHeight;
    if (roundToPixelErrorY > 0.5f) {
        nodeHeightI -= 1.0f;
        roundToPixelErrorY -= 1.0f;
    }
    if (roundToPixelErrorY < -0.5f) {
        nodeHeightI += 1.0f;
        roundToPixelErrorY += 1.0f;
    }
    if (nodeHeightI < nodeHeightTemp) {
        roundToPixelErrorY += nodeHeightTemp - nodeHeightI;
        nodeHeightI = nodeHeightTemp;
    }

    rect.SetWidth(nodeWidthI);
    rect.SetHeight(nodeHeightI);
    return rect;
}

void RegisterMediaPlayerEventImpl(const WeakPtr<VideoStateMachinePattern>& weak, const RefPtr<MediaPlayer>& mediaPlayer,
    int32_t instanceId, const SingleTaskExecutor& uiTaskExecutor)
{
    auto&& positionUpdatedEvent = [weak, uiTaskExecutor, instanceId](uint32_t currentPos) {
        uiTaskExecutor.PostSyncTask([weak, currentPos, instanceId] {
            auto video = weak.Upgrade();
            CHECK_NULL_VOID(video);
            ContainerScope scope(instanceId);
            video->OnCurrentTimeChange(currentPos);
            video->StartUpdateImageAnalyzer();
            }, "ArkUIVideoCurrentTimeChange");
    };

    auto&& stateChangedEvent = [weak, uiTaskExecutor, instanceId](PlaybackStatus status) {
        uiTaskExecutor.PostTask([weak, status, instanceId] {
            auto video = weak.Upgrade();
            CHECK_NULL_VOID(video);
            ContainerScope scope(instanceId);
            video->OnPlayerStatus(status);
            }, "ArkUIVideoPlayerStatusChange");
    };

    auto&& errorEvent = [weak, uiTaskExecutor, instanceId]() {
        uiTaskExecutor.PostTask([weak, instanceId] {
            auto video = weak.Upgrade();
            CHECK_NULL_VOID(video);
            ContainerScope scope(instanceId);
            video->OnError("");
            }, "ArkUIVideoError");
    };

    auto&& videoErrorEvent = [weak, uiTaskExecutor, instanceId](int32_t code, const std::string& message) {
        uiTaskExecutor.PostTask([weak, instanceId, code, message] {
            auto video = weak.Upgrade();
            CHECK_NULL_VOID(video);
            ContainerScope scope(instanceId);
            video->OnError(code, message);
            }, "ArkUIVideoErrorWithParam");
    };

    auto&& resolutionChangeEvent = [weak, uiTaskExecutor, instanceId]() {
        uiTaskExecutor.PostSyncTask([weak, instanceId] {
            auto video = weak.Upgrade();
            CHECK_NULL_VOID(video);
            ContainerScope scope(instanceId);
            video->OnResolutionChange();
            }, "ArkUIVideoResolutionChange");
    };

    auto&& startRenderFrameEvent = [weak, uiTaskExecutor, instanceId]() {
        uiTaskExecutor.PostSyncTask([weak, instanceId] {
            auto video = weak.Upgrade();
            CHECK_NULL_VOID(video);
            ContainerScope scope(instanceId);
            video->OnStartRenderFrameCb();
            }, "ArkUIVideoStartRenderFrame");
    };

    mediaPlayer->RegisterMediaPlayerEvent(
        positionUpdatedEvent, stateChangedEvent, errorEvent, resolutionChangeEvent, startRenderFrameEvent);
    mediaPlayer->RegisterMediaPlayerVideoErrorEvent(videoErrorEvent);
}

std::string StatusToString(PlaybackStatus status)
{
    switch (status) {
        case PlaybackStatus::ERROR:
            return "ERROR";
        case PlaybackStatus::IDLE:
            return "IDLE";
        case PlaybackStatus::INITIALIZED:
            return "INITIALIZED";
        case PlaybackStatus::PREPARED:
            return "PREPARED";
        case PlaybackStatus::STARTED:
            return "STARTED";
        case PlaybackStatus::PAUSED:
            return "PAUSED";
        case PlaybackStatus::STOPPED:
            return "STOPPED";
        case PlaybackStatus::PLAYBACK_COMPLETE:
            return "PLAYBACK_COMPLETE";
        case PlaybackStatus::NONE:
            return "NONE";
        default:
            return "Invalid";
    }
}

void SendStatisticEvent(StatisticEventType type)
{
    auto context = PipelineBase::GetCurrentContextSafely();
    CHECK_NULL_VOID(context);
    auto statisticEventReporter = context->GetStatisticEventReporter();
    CHECK_NULL_VOID(statisticEventReporter);
    statisticEventReporter->SendEvent(type);
}
} // namespace

VideoStateMachinePattern::VideoStateMachinePattern(const RefPtr<VideoControllerAsync>& videoControllerAsync)
    : instanceId_(Container::CurrentId()), videoControllerAsync_(videoControllerAsync)
{}

void VideoStateMachinePattern::OnControllerDestroyed()
{
    if (videoControllerAsync_) {
        videoControllerAsync_->ClearPattern();
    }
}

void VideoStateMachinePattern::ResetMediaPlayerOnBg(VideoControllerAsync::AsyncCommandCallback callback)
{
    CHECK_NULL_VOID(mediaPlayer_);
    if (!stateManager_->CanSetPendingCommand(VideoPlaybackCommand::RESET)) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "Video[%{public}d] Reset rejected: %{public}s",
            hostId_, stateManager_->GetStateInfo().c_str());
        if (callback) {
            callback(false, "Reset rejected: another Reset is pending");
        }
        return;
    }
    ContainerScope scope(instanceId_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    VideoSourceInfo videoSrc = {videoSrcInfo_.src_, videoSrcInfo_.bundleName_, videoSrcInfo_.moduleName_};

    stateManager_->SetPendingCommand(VideoPlaybackCommand::RESET, std::move(callback), VideoPlaybackCommand::RESET);

    auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    auto bgTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::BACKGROUND);
    bgTaskExecutor.PostTask(
        [weak = WeakClaim(this), mediaPlayerWeak = WeakClaim(AceType::RawPtr(mediaPlayer_)),
        videoSrc, id = instanceId_, showFirstFrame = showFirstFrame_, uiTaskExecutor, hostId = hostId_] {
        auto mediaPlayer = mediaPlayerWeak.Upgrade();
        CHECK_NULL_VOID(mediaPlayer);

        if (!mediaPlayer->IsMediaPlayerValid()) {
            TAG_LOGI(AceLogTag::ACE_VIDEO, "Video[%{public}d] create MediaPlayer on bg.", hostId);
            mediaPlayer->CreateMediaPlayer();
        }
        if (!mediaPlayer->IsMediaPlayerValid()) {
            TAG_LOGE(AceLogTag::ACE_VIDEO, "Video[%{public}d] create MediaPlayer failed.", hostId);
            uiTaskExecutor.PostTask([weak]() {
                auto videoPattern = weak.Upgrade();
                CHECK_NULL_VOID(videoPattern);
                videoPattern->stateManager_->ClearPendingCommand();
                videoPattern->FireError(ERROR_CODE_VIDEO_CREATE_PLAYER_FAILED,
                    "Failed to create the media player");
            }, "ArkUIVideoCreatePlayerFailed");
            return;
        }

        TAG_LOGI(AceLogTag::ACE_VIDEO, "Video[%{public}d] trigger mediaPlayer reset", hostId);
        mediaPlayer->ResetMediaPlayer();

        RegisterMediaPlayerEvent(weak, mediaPlayer, videoSrc.src_, id);

        if (!mediaPlayer->SetSource(videoSrc.src_, videoSrc.bundleName_, videoSrc.moduleName_)) {
            uiTaskExecutor.PostTask([weak]() {
                auto videoPattern = weak.Upgrade();
                CHECK_NULL_VOID(videoPattern);
                videoPattern->stateManager_->ClearPendingCommand();
                videoPattern->FireError(ERROR_CODE_VIDEO_SOURCE_INVALID, "Not a valid source");
                }, "ArkUIVideoFireError");
            return;
        }

        uiTaskExecutor.PostSyncTask([weak, id] {
            auto videoPattern = weak.Upgrade();
            CHECK_NULL_VOID(videoPattern);
            ContainerScope scope(id);
            videoPattern->PrepareSurface();
            }, "ArkUIVideoPrepareSurface");

        mediaPlayer->SetRenderFirstFrame(showFirstFrame);

        uiTaskExecutor.PostTask([weak, id]() {
            auto videoPattern = weak.Upgrade();
            CHECK_NULL_VOID(videoPattern);
            ContainerScope scope(id);
            videoPattern->stateManager_->HandleStateTransition(VideoPlaybackCommand::RESET);
        }, "ArkUIVideoResetStateTransition");
        }, "ArkUIVideoMediaPlayerReset");
}

void VideoStateMachinePattern::ResetStatus()
{
    isInitialState_ = true;
    // Clear any pending command during reset
    stateManager_->ClearPendingCommand();
    // NOTE: Do NOT reset state machine here.
    // State transition should be driven by player callbacks.
    // Only reset internal flags.
}

bool VideoStateMachinePattern::TransitionTo(VideoPlaybackState newState)
{
    return stateManager_->TransitionTo(newState);
}

bool VideoStateMachinePattern::TransitionToIfAllowed(VideoPlaybackState newState, const char* caller)
{
    if (!stateManager_->CanTransitionTo(newState)) {
        TAG_LOGW(AceLogTag::ACE_VIDEO,
            "Video[%{public}d] State transition rejected by %{public}s: %{public}s -> %{public}s",
            hostId_, caller,
            stateManager_->GetStateInfo().c_str(),
            VideoStateMachine::StateToString(newState));
        return false;
    }

    return stateManager_->TransitionTo(newState);
}

void VideoStateMachinePattern::OnCreatedStateEntered()
{
    TAG_LOGD(AceLogTag::ACE_VIDEO, "Video[%{public}d] Entered CREATED state", hostId_);
    ChangePlayButtonTag();

    if (mediaPlayer_ && mediaPlayer_->IsMediaPlayerValid()) {
        TAG_LOGI(AceLogTag::ACE_VIDEO, "Video[%{public}d] Auto-trigger PrepareAsync from CREATED", hostId_);
        
        auto originalIntent = stateManager_->GetOriginalIntent();
        auto pendingCallback = stateManager_->ConsumePendingCallback();
        
        stateManager_->SetPendingCommand(VideoPlaybackCommand::PREPARE, std::move(pendingCallback), originalIntent);
        
        if (mediaPlayer_->PrepareAsync() != 0) {
            TAG_LOGE(AceLogTag::ACE_VIDEO, "Video[%{public}d] Auto PrepareAsync failed", hostId_);
            stateManager_->ClearPendingCommand();
        }
    }
}

void VideoStateMachinePattern::OnPreparedStateEntered()
{
    TAG_LOGD(AceLogTag::ACE_VIDEO, "Video[%{public}d] Entered PREPARED state", hostId_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(mediaPlayer_);

    int32_t milliSecondDuration = 0;
    mediaPlayer_->GetDuration(milliSecondDuration);
    duration_ = static_cast<uint32_t>(milliSecondDuration / MILLISECONDS_TO_SECONDS);
    currentPos_ = 0;
    isInitialState_ = true;
    SetIsSeeking(false);
    OnUpdateTime(duration_, DURATION_POS);
    OnUpdateTime(currentPos_, CURRENT_POS);

    if (showFirstFrame_) {
        UpdatePreparedVideoSize(host);
    }

    RefPtr<UINode> controlBar = nullptr;
    auto children = host->GetChildren();
    for (const auto& child : children) {
        if (child->GetTag() == V2::ROW_ETS_TAG) {
            controlBar = child;
            break;
        }
    }
    if (controlBar) {
        auto sliderNode = DynamicCast<FrameNode>(controlBar->GetChildAtIndex(SLIDER_POS));
        auto sliderModifier = NodeModifier::GetSliderCustomModifier();
        if (sliderModifier && sliderNode) {
            sliderModifier->sliderPaintPropertyUpdateMin(sliderNode, 0.0f);
            sliderModifier->sliderPaintPropertyUpdateMax(sliderNode, static_cast<float>(duration_));
            sliderNode->MarkModifyDone();
        }
        auto playBtn = DynamicCast<FrameNode>(controlBar->GetChildAtIndex(0));
        if (playBtn) {
            ChangePlayButtonTag(playBtn);
        }
    }

    auto eventHub = GetEventHub<VideoEventHub>();
    if (eventHub) {
        eventHub->FirePreparedEvent(static_cast<double>(duration_));
    }
    TAG_LOGI(AceLogTag::ACE_VIDEO,
        "Video[%{public}d] duration: %{public}u, loop: %{public}d, muted: %{public}d, Speed: %{public}f", hostId_,
        duration_, loop_, muted_, progressRate_);
    UpdateLooping();
    UpdateSpeed();
    UpdateMuted();

    // Auto-command trigger: per spec, check after state entered and pending cleared.
    // If originalIntent=PLAY (Stopped+Start flow), auto-trigger PLAY with preserved callback.
    // If coming from CREATED with autoPlay=true, auto-trigger PLAY (no callback).
    auto originalIntent = stateManager_->GetOriginalIntent();
    if (originalIntent == VideoPlaybackCommand::PLAY) {
        TAG_LOGI(AceLogTag::ACE_VIDEO, "Video[%{public}d] Auto-trigger Play (originalIntent=PLAY)", hostId_);
        auto preservedCallback = stateManager_->ConsumePendingCallback();
        stateManager_->SetPendingCommand(VideoPlaybackCommand::PLAY, std::move(preservedCallback));
        
        auto context = host->GetContext();
        CHECK_NULL_VOID(context);
        auto bgTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::BACKGROUND);
        bgTaskExecutor.PostTask(
            [weak = WeakClaim(RawPtr(mediaPlayer_)), weakThis = WeakClaim(this), hostId = hostId_] {
                auto mediaPlayer = weak.Upgrade();
                CHECK_NULL_VOID(mediaPlayer);
                TAG_LOGI(AceLogTag::ACE_VIDEO, "Video[%{public}d] Auto-trigger mediaPlayer play", hostId);
                int32_t ret = mediaPlayer->Play();
                
                auto pattern = weakThis.Upgrade();
                CHECK_NULL_VOID(pattern);
                if (ret != 0) {
                    TAG_LOGW(AceLogTag::ACE_VIDEO, "Video[%{public}d] Auto-trigger Play() failed: ret=%{public}d", hostId, ret);
                    pattern->stateManager_->ClearPendingCommand();
                }
            },
            "ArkUIVideoAutoPlay");
    } else if (stateManager_->GetPreviousState() == VideoPlaybackState::STOPPED) {
        TAG_LOGI(AceLogTag::ACE_VIDEO, "Video[%{public}d] Auto-trigger Play (from STOPPED, sync)", hostId_);
        Start();
    } else if (autoPlay_) {
        TAG_LOGI(AceLogTag::ACE_VIDEO, "Video[%{public}d] Auto-trigger Play (autoPlay)", hostId_);
        Start();
    }

    ChangePlayButtonTag();
}

void VideoStateMachinePattern::OnPlayingStateEntered()
{
    TAG_LOGD(AceLogTag::ACE_VIDEO, "Video[%{public}d] Entered PLAYING state", hostId_);
    auto eventHub = GetEventHub<VideoEventHub>();
    if (eventHub) {
        eventHub->FireStartEvent();
    }
    DestroyAnalyzerOverlay();
    ChangePlayButtonTag();
}

void VideoStateMachinePattern::OnPausedStateEntered()
{
    TAG_LOGD(AceLogTag::ACE_VIDEO, "Video[%{public}d] Entered PAUSED state", hostId_);
    auto eventHub = GetEventHub<VideoEventHub>();
    if (eventHub) {
        eventHub->FirePauseEvent();
    }
    StartImageAnalyzer();
    ChangePlayButtonTag();
}

void VideoStateMachinePattern::OnStoppedStateEntered()
{
    TAG_LOGD(AceLogTag::ACE_VIDEO, "Video[%{public}d] Entered STOPPED state", hostId_);
    currentPos_ = 0;
    OnUpdateTime(currentPos_, CURRENT_POS);
    auto eventHub = GetEventHub<VideoEventHub>();
    if (eventHub) {
        eventHub->FireStopEvent();
    }
    ChangePlayButtonTag();
}

void VideoStateMachinePattern::OnCompletedStateEntered()
{
    TAG_LOGD(AceLogTag::ACE_VIDEO, "Video[%{public}d] Entered COMPLETED state", hostId_);
    currentPos_ = duration_;
    OnUpdateTime(currentPos_, CURRENT_POS);
    auto eventHub = GetEventHub<VideoEventHub>();
    if (eventHub) {
        eventHub->FireFinishEvent();
    }
    ChangePlayButtonTag();
}

void VideoStateMachinePattern::OnErrorStateEntered()
{
    TAG_LOGD(AceLogTag::ACE_VIDEO, "Video[%{public}d] Entered ERROR state", hostId_);
    auto eventHub = GetEventHub<VideoEventHub>();
    if (eventHub) {
        eventHub->FireErrorEvent(lastErrorCode_, lastErrorMessage_);
    }
    ChangePlayButtonTag();
}

void VideoStateMachinePattern::UpdateMediaPlayerOnBg()
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

void VideoStateMachinePattern::PrepareMediaPlayer()
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
    // CreateMediaPlayer is moved to ResetMediaPlayerOnBg (BACKGROUND thread)
    // to avoid blocking UI thread during decoder initialization.
    stateManager_->HandleStateTransition(VideoPlaybackCommand::RESET);
    ResetStatus();
    ResetMediaPlayerOnBg();
}

bool VideoStateMachinePattern::SetSourceForMediaPlayer()
{
    CHECK_NULL_RETURN(mediaPlayer_, false);
    return mediaPlayer_->SetSource(videoSrcInfo_.src_, videoSrcInfo_.bundleName_, videoSrcInfo_.moduleName_);
}

void VideoStateMachinePattern::RegisterMediaPlayerEvent(const WeakPtr<VideoStateMachinePattern>& weak, const RefPtr<MediaPlayer>& mediaPlayer,
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

#ifdef RENDER_EXTRACT_SUPPORTED
    auto&& textureRefreshEvent = [weak, uiTaskExecutor](int32_t instanceId, int64_t textureId) {
        uiTaskExecutor.PostSyncTask(
            [&weak, instanceId, textureId] {
            auto video = weak.Upgrade();
            CHECK_NULL_VOID(video);
            void* nativeWindow = video->GetNativeWindow(instanceId, textureId);
            if (!nativeWindow) {
                LOGE("the native window is nullptr.");
                return;
            }
            video->OnTextureRefresh(nativeWindow);
            }, "ArkUIVideoTextureRefresh");
    };
    mediaPlayer->RegisterTextureEvent(textureRefreshEvent);
#endif
}

#ifdef RENDER_EXTRACT_SUPPORTED
void* VideoStateMachinePattern::GetNativeWindow(int32_t instanceId, int64_t textureId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_RETURN(container, nullptr);
    auto nativeView = container->GetAceView();
    CHECK_NULL_RETURN(nativeView, nullptr);
    return const_cast<void*>(nativeView->GetNativeWindowById(textureId));
}

void VideoStateMachinePattern::OnTextureRefresh(void* surface)
{
    CHECK_NULL_VOID(surface);
    auto renderContextForMediaPlayer = renderContextForMediaPlayerWeakPtr_.Upgrade();
    CHECK_NULL_VOID(renderContextForMediaPlayer);
    renderContextForMediaPlayer->MarkNewFrameAvailable(surface);
}
#endif

void VideoStateMachinePattern::UpdatePreparedVideoSize(const RefPtr<FrameNode>& host)
{
    auto videoLayoutProperty = host->GetLayoutProperty<VideoLayoutProperty>();
    CHECK_NULL_VOID(videoLayoutProperty);
    SizeF videoSize(
        static_cast<float>(mediaPlayer_->GetVideoWidth()),
        static_cast<float>(mediaPlayer_->GetVideoHeight()));
    if (GreatNotEqual(videoSize.Width(), 0.0f) && GreatNotEqual(videoSize.Height(), 0.0f)) {
        videoLayoutProperty->UpdateVideoSize(videoSize);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void VideoStateMachinePattern::OnCurrentTimeChange(uint32_t currentPos)
{
    TAG_LOGD(AceLogTag::ACE_VIDEO, "Video[%{public}d] OnCurrentTimeChange: pos=%{public}u, %{public}s",
        hostId_, currentPos, stateManager_->GetStateInfo().c_str());
    if (stateManager_->IsPrepared()) {
        isInitialState_ = isInitialState_ ? currentPos == 0 : false;
    }
    if (currentPos == currentPos_ || stateManager_->IsStopped()) {
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

void VideoStateMachinePattern::ChangePlayerStatus(const PlaybackStatus& status)
{
    TAG_LOGD(AceLogTag::ACE_VIDEO, "Video[%{public}d] ChangePlayerStatus enter: status=%{public}s, %{public}s",
        hostId_, StatusToString(status).c_str(), stateManager_->GetStateInfo().c_str());
    switch (status) {
        case PlaybackStatus::STARTED:
            stateManager_->HandleStateTransition(VideoPlaybackCommand::PLAY);
            break;
        case PlaybackStatus::PAUSED:
            stateManager_->HandleStateTransition(VideoPlaybackCommand::PAUSE);
            break;
        case PlaybackStatus::STOPPED:
            stateManager_->HandleStateTransition(VideoPlaybackCommand::STOP);
            break;
        case PlaybackStatus::PREPARED: {
            if (!showImagePreview_ || showFirstFrame_) {
                auto host = GetHost();
                CHECK_NULL_VOID(host);
                auto pipeline = host->GetContext();
                CHECK_NULL_VOID(pipeline);
                ImagePerf::GetPerfMonitor()->CompleteLoadComponent(hostId_);
            }
            ContainerScope scope(instanceId_);
            if (!mediaPlayer_ || !mediaPlayer_->IsMediaPlayerValid()) {
                return;
            }
            stateManager_->HandleStateTransition(VideoPlaybackCommand::PREPARE);
            break;
        }
        case PlaybackStatus::PLAYBACK_COMPLETE:
            stateManager_->HandleStateTransition(VideoPlaybackCommand::COMPLETE);
            break;
        default:
            break;
    }
    TAG_LOGD(AceLogTag::ACE_VIDEO, "Video[%{public}d] ChangePlayerStatus exit: %{public}s",
        hostId_, stateManager_->GetStateInfo().c_str());
}

void VideoStateMachinePattern::OnPlayerStatus(PlaybackStatus status)
{
    TAG_LOGI(AceLogTag::ACE_VIDEO, "Video[%{public}d] Player current status is %{public}s.", hostId_,
        StatusToString(status).c_str());
    bool isPlaying = (status == PlaybackStatus::STARTED);
    if (isInitialState_) {
        isInitialState_ = !isPlaying;
    }

    ChangePlayerStatus(status);

    SaveCurrentPlaybackStatus(status);
    ReportChangeEvent(status, lastProgressRate_, currentPos_);
}

void VideoStateMachinePattern::OnError(const std::string& errorId)
{
    AddChild();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RequestFrame();
    if (!(stateManager_->IsPrepared()) && (!showImagePreview_ || showFirstFrame_)) {
        ImagePerf::GetPerfMonitor()->CompleteLoadComponent(hostId_);
    }
    // Save error info for OnErrorStateEntered callback
    lastErrorCode_ = ERROR_CODE_VIDEO_SOURCE_INVALID;
    lastErrorMessage_ = errorId.empty() ? "Unknown error" : errorId;
    // Clear any pending command before error handling
    stateManager_->ClearPendingCommand();
    stateManager_->HandleStateTransition(VideoPlaybackCommand::ERROR);
}

void VideoStateMachinePattern::OnError(int32_t code, const std::string& message)
{
    AddChild();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RequestFrame();
    if (!(stateManager_->IsPrepared()) && (!showImagePreview_ || showFirstFrame_)) {
        ImagePerf::GetPerfMonitor()->CompleteLoadComponent(hostId_);
    }
    // Save error info for OnErrorStateEntered callback
    lastErrorCode_ = code;
    lastErrorMessage_ = message;
    // Clear any pending command before error handling
    stateManager_->ClearPendingCommand();
    stateManager_->HandleStateTransition(VideoPlaybackCommand::ERROR);
}

void VideoStateMachinePattern::OnResolutionChange() const
{
    if (!mediaPlayer_ || !mediaPlayer_->IsMediaPlayerValid()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto videoLayoutProperty = host->GetLayoutProperty<VideoLayoutProperty>();
    CHECK_NULL_VOID(videoLayoutProperty);
    auto preVideoSize = videoLayoutProperty->GetVideoSize();
    // Only update video size if it has not been set yet.
    // For showFirstFrame=true, OnPreparedStateEntered() updates the size early to ensure
    // the first frame uses the correct aspect ratio.
    // For showFirstFrame=false, Start() updates the size before playback to
    // keep the previous video's last frame at its original ratio.
    // Updating here unconditionally would cause the previous frame to jump to
    // the new ratio before playback starts (mediaPlayer triggers this callback
    // asynchronously after PrepareAsync completes).
    if (!preVideoSize.has_value()) {
        SizeF videoSize = SizeF(
            static_cast<float>(mediaPlayer_->GetVideoWidth()),
            static_cast<float>(mediaPlayer_->GetVideoHeight()));
        videoLayoutProperty->UpdateVideoSize(videoSize);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void VideoStateMachinePattern::OnStartRenderFrameCb()
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

bool VideoStateMachinePattern::HasPlayer() const
{
    return mediaPlayer_ != nullptr;
}

void VideoStateMachinePattern::HiddenChange(bool hidden)
{
    if (stateManager_->IsPlaying() && hidden && HasPlayer()) {
        pastPlayingStatus_ = true;
        Pause();
        return;
    }

    if (!hidden && pastPlayingStatus_) {
        pastPlayingStatus_ = false;
        Start();
    }
}

void VideoStateMachinePattern::SaveCurrentPlaybackStatus(PlaybackStatus status)
{
    currentPlaybackStatus_ = status;
}

void VideoStateMachinePattern::OnVisibleChange(bool isVisible)
{
    if (hiddenChangeEvent_) {
        hiddenChangeEvent_(!isVisible);
    }
}

void VideoStateMachinePattern::UpdateLooping()
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

void VideoStateMachinePattern::SetSurfaceBackgroundColor(Color color)
{
    CHECK_NULL_VOID(renderContextForMediaPlayer_);
    surfaceBgColor_ = color;
    renderContextForMediaPlayer_->UpdateBackgroundColor(color);
}

void VideoStateMachinePattern::UpdateSpeed()
{
    if (mediaPlayer_ && mediaPlayer_->IsMediaPlayerValid()) {
        ContainerScope scope(instanceId_);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto context = host->GetContext();
        CHECK_NULL_VOID(context);

        auto bgTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::BACKGROUND);
        bgTaskExecutor.PostTask(
            [weak = WeakClaim(RawPtr(mediaPlayer_)),
            weakThis = WeakClaim(this),
            progress = progressRate_] {
            auto mediaPlayer = weak.Upgrade();
            CHECK_NULL_VOID(mediaPlayer);
            int32_t errorCode = 0;
            std::string errorMsg = "";
            int32_t ret = mediaPlayer->SetPlaybackRate(static_cast<float>(progress), errorCode, errorMsg);
            if (LessNotEqual(progress, SPEED_0_125_X) || GreatNotEqual(progress, SPEED_8_00_X)) {
                SendStatisticEvent(StatisticEventType::VIDEO_EXCEED_PROGRESS_RATE);
            }

            auto pattern = weakThis.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleSetPlaybackRateResult(progress, errorCode, errorMsg);
            double lastSpeed = pattern->GetLastProgressRate();
            double lastSetSpeed = pattern->GetLastSetProgressRate();

            if (pattern->GetsIsProgressInjectCmd()) {
                pattern->SetIsProgressInjectCmd(false);
                pattern->ReportCommandResultOnUIThread(
                    "setVideoPlaybackSpeed",
                    ret == 0 ? "success" : "fail",
                    ret == 0 ? "" : "SetSpeed operation execution failed");
            }

            auto reportProgressRate = lastSpeed;
            if (ret == 0 || (ret != 0 && lastSpeed == 0)) {
                reportProgressRate = progress;
                pattern->SetLastProgressRate(progress);
            }
            if (NearEqual(lastSetSpeed, progress)) {
                return;
            }
            pattern->SetLastSetProgressRate(progress);
            pattern->ReportChangeEventOnUIThread(
                pattern->GetCurrentPlaybackStatus(), reportProgressRate, pattern->GetCurrentPos());
            }, "ArkUIVideoUpdateSpeed");
    }
}

void VideoStateMachinePattern::HandleSetPlaybackRateResult(double progress, int32_t errorCode, std::string& errorMsg)
{
    int32_t newCode = 0;
    std::string newMsg = "";
    switch (static_cast<PlayBackRate>(errorCode)) {
        case PlayBackRate::SUCCESS:
            TAG_LOGI(
                AceLogTag::ACE_VIDEO, "Video[%{public}d] currentProgressRate is set as %{public}f", hostId_, progress);
            break;
        case PlayBackRate::MSERR_INVALID_VAL:
            CHECK_NULL_VOID(mediaPlayer_);
            mediaPlayer_->SetPlaybackRate(DEFAULT_PROGRESS_RATE, newCode, newMsg);
            errorMsg.append("The parameter check failed, parameter value out of range.");
            TAG_LOGW(AceLogTag::ACE_VIDEO,
                "Video[%{public}d] Failed to set currentProgressRate %{public}f, code is %{public}d, message is "
                "%{public}s",
                hostId_, progress, errorCode, errorMsg.c_str());
            break;
        case PlayBackRate::MSERR_INVALID_OPERATION:
            break;
        default:
            CHECK_NULL_VOID(mediaPlayer_);
            mediaPlayer_->SetPlaybackRate(DEFAULT_PROGRESS_RATE, newCode, newMsg);
            TAG_LOGW(AceLogTag::ACE_VIDEO, "Video[%{public}d] Failed to set currentProgressRate %{public}f", hostId_,
                progress);
            break;
    }
}

void VideoStateMachinePattern::ReportChangeEventOnUIThread(PlaybackStatus status, double playbackSpeed, uint32_t currentPos)
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);

    auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    uiTaskExecutor.PostTask(
        [weakPattern = WeakClaim(this), status, playbackSpeed, currentPos] {
            auto pattern = weakPattern.Upgrade();
            if (pattern) {
                pattern->ReportChangeEvent(status, playbackSpeed, currentPos);
            }
        }, "ArkUIVideoReportChangeEvent");
}

void VideoStateMachinePattern::ReportCommandResultOnUIThread(
    const std::string& event, const std::string& result, const std::string& reason)
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);

    auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    uiTaskExecutor.PostTask(
        [weakPattern = WeakClaim(this), event, result, reason] {
            auto pattern = weakPattern.Upgrade();
            if (pattern) {
                pattern->ReportCommandResult(event, result, reason);
            }
        }, "ArkUIVideoReportCommandResult");
}

void VideoStateMachinePattern::UpdateMuted()
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

void VideoStateMachinePattern::OnUpdateTime(uint32_t time, int pos) const
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
        auto sliderModifier = NodeModifier::GetSliderCustomModifier();
        CHECK_NULL_VOID(sliderModifier);
        sliderModifier->sliderPatternUpdateValue(sliderNode, static_cast<float>(time));
        sliderNode->MarkModifyDone();
    }
}

void VideoStateMachinePattern::PrepareSurface()
{
    CHECK_NULL_VOID(mediaPlayer_);
    if (!SystemProperties::GetExtSurfaceEnabled()) {
        renderSurface_->SetRenderContext(renderContextForMediaPlayer_);
    }
    if (!renderSurface_->IsSurfaceValid()) {
        renderSurface_->InitSurface();
        mediaPlayer_->SetRenderSurface(renderSurface_);
    }
    if (mediaPlayer_->SetSurface() != 0) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "mediaPlayer renderSurface set failed");
    }
}

void VideoStateMachinePattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    THREAD_SAFE_NODE_CHECK(host, OnAttachToFrameNode, host);
    // full screen node is not supposed to register js controller event
    if (!InstanceOf<VideoStateMachineFullScreenPattern>(this)) {
        if (videoControllerAsync_) {
            videoControllerAsync_->SetPattern(WeakClaim(this));
        }
    }
    CHECK_NULL_VOID(host);
    hostId_ = host->GetId();
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddWindowStateChangedCallback(host->GetId());
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

#ifdef RENDER_EXTRACT_SUPPORTED
    CHECK_NULL_VOID(renderSurface_);
    auto contextType = renderSurface_->IsTexture() ?
        RenderContext::ContextType::HARDWARE_TEXTURE : RenderContext::ContextType::HARDWARE_SURFACE;
    static RenderContext::ContextParam param = { contextType, "MediaPlayerSurface",
                                                 RenderContext::PatternType::VIDEO };
#else
    static RenderContext::ContextParam param = { RenderContext::ContextType::HARDWARE_SURFACE, "MediaPlayerSurface",
                                                 RenderContext::PatternType::VIDEO };
#endif
    ACE_UINODE_TRACE(host);
    renderContextForMediaPlayer_->InitContext(false, param);

    if (SystemProperties::GetExtSurfaceEnabled()) {
        RegisterRenderContextCallBack();
    }

    renderContext->UpdateBackgroundColor(Color::BLACK);
    renderContextForMediaPlayer_->UpdateBackgroundColor(Color::BLACK);
    renderContext->SetClipToBounds(true);
}

void VideoStateMachinePattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_EQUAL_VOID(frameNode->IsThreadSafeNode(), true);
    auto id = frameNode->GetId();
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowStateChangedCallback(id);
}

void VideoStateMachinePattern::OnAttachToMainTree()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    auto layoutProperty = GetLayoutProperty<VideoLayoutProperty>();
    if (pipeline && (!showImagePreview_ || showFirstFrame_)) {
        ImagePerf::GetPerfMonitor()->AddLoadComponent(hostId_);
    }
    CHECK_EQUAL_VOID(host->IsThreadSafeNode(), false);
    // full screen node is not supposed to register js controller event
    if (!InstanceOf<VideoStateMachineFullScreenPattern>(this)) {
        if (videoControllerAsync_) {
            videoControllerAsync_->SetPattern(WeakClaim(this));
        }
    }
    CHECK_NULL_VOID(pipeline);
    pipeline->AddWindowStateChangedCallback(hostId_);
}

void VideoStateMachinePattern::OnDetachFromMainTree()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    auto id = host->GetId();
    auto layoutProperty = GetLayoutProperty<VideoLayoutProperty>();
    if (pipeline && (!showImagePreview_ || showFirstFrame_)) {
        ImagePerf::GetPerfMonitor()->DeleteLoadComponent(id);
    }
    if (host->GetNodeStatus() == NodeStatus::BUILDER_NODE_OFF_MAINTREE) {
        Pause();
    }
    CHECK_EQUAL_VOID(host->IsThreadSafeNode(), false);
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowStateChangedCallback(id);
}

void VideoStateMachinePattern::RegisterRenderContextCallBack()
{
#ifdef RENDER_EXTRACT_SUPPORTED
    renderSurfaceWeakPtr_ = renderSurface_;
    renderContextForMediaPlayerWeakPtr_ = renderContextForMediaPlayer_;
    auto OnAttachCallBack = [weak = WeakClaim(this)](int64_t textureId, bool isAttach) mutable {
        auto videoPattern = weak.Upgrade();
        CHECK_NULL_VOID(videoPattern);
        if (auto renderSurface = videoPattern->renderSurfaceWeakPtr_.Upgrade(); renderSurface) {
            renderSurface->AttachToGLContext(textureId, isAttach);
        }
    };
    renderContextForMediaPlayer_->AddAttachCallBack(OnAttachCallBack);
    auto OnUpdateCallBack = [weak = WeakClaim(this)](std::vector<float>& matrix) mutable {
        auto videoPattern = weak.Upgrade();
        CHECK_NULL_VOID(videoPattern);
        if (auto renderSurface = videoPattern->renderSurfaceWeakPtr_.Upgrade(); renderSurface) {
            renderSurface->UpdateTextureImage(matrix);
        }
    };
    renderContextForMediaPlayer_->AddUpdateCallBack(OnUpdateCallBack);
#if defined(ANDROID_PLATFORM) && defined (RS_ENABLE_VK)
    if (OHOS::Rosen::RSSystemProperties::IsUseVulkan()) {
        auto OnInitTypeCallBack = [weak = WeakClaim(this)](int32_t& type) {
            auto videoPattern = weak.Upgrade();
            CHECK_NULL_VOID(videoPattern);
            if (auto renderSurface = videoPattern->renderSurfaceWeakPtr_.Upgrade(); renderSurface != nullptr) {
                renderSurface->AddInitTypeCallBack(type);
            }
        };
        renderContextForMediaPlayer_->AddInitTypeCallBack(OnInitTypeCallBack);
    }
#endif
#endif
}

void VideoStateMachinePattern::OnModifyDone()
{
    Pattern::OnModifyDone();

    if (!hiddenChangeEvent_) {
        SetHiddenChangeEvent(CreateHiddenChangeEvent());
    }

    // src has changed
    auto layoutProperty = GetLayoutProperty<VideoLayoutProperty>();
#ifdef RENDER_EXTRACT_SUPPORTED
    if ((layoutProperty && layoutProperty->HasVideoSource() && layoutProperty->GetVideoSource() != videoSrcInfo_)) {
#else
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) &&
        (layoutProperty && layoutProperty->HasVideoSource() && layoutProperty->GetVideoSource() != videoSrcInfo_)) {
#endif
        ResetStatus();
    }

    // update full screen pattern state
    UpdateFsState();

    // Update the control bar and preview image.
    UpdatePreviewImage();
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

    if (SystemProperties::GetExtSurfaceEnabled()) {
        auto pipelineContext = host->GetContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->AddOnAreaChangeNode(host->GetId());
    }
    auto eventHub = GetEventHub<VideoEventHub>();
    if (!AceType::InstanceOf<VideoStateMachineFullScreenPattern>(this)) {
        eventHub->SetInspectorId(host->GetInspectorIdValue(""));
    }
    if (!IsSupportImageAnalyzer()) {
        DestroyAnalyzerOverlay();
    } else if (stateManager_->IsPaused() && !stateManager_->IsPlaying() && !GetAnalyzerState()) {
        StartImageAnalyzer();
    }
    InitKeyEvent();
}

void VideoStateMachinePattern::InitKeyEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->OnKeyEvent(event);
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));
}

bool VideoStateMachinePattern::OnKeyEvent(const KeyEvent& event)
{
    if (isEnableShortcutKey_ && event.action == KeyAction::DOWN) {
        TAG_LOGD(AceLogTag::ACE_VIDEO, "video on key event %{public}d", event.code);
        if (event.code == KeyCode::KEY_DPAD_LEFT || event.code == KeyCode::KEY_DPAD_RIGHT) {
            MoveByStep(event.code == KeyCode::KEY_DPAD_LEFT ? -1 : 1);
            return true;
        }
        if (event.code == KeyCode::KEY_DPAD_DOWN || event.code == KeyCode::KEY_DPAD_UP) {
            AdjustVolume(event.code == KeyCode::KEY_DPAD_DOWN ? -1 : 1);
            return true;
        }
        if (event.code == KeyCode::KEY_SPACE) {
            OnKeySpaceEvent();
            return true;
        }
    }
    return false;
}

bool VideoStateMachinePattern::HandleSliderKeyEvent(const KeyEventInfo& event)
{
    if (isEnableShortcutKey_ && event.GetKeyType() == KeyAction::DOWN) {
        TAG_LOGD(AceLogTag::ACE_VIDEO, "slider on key event %{public}d", event.GetKeyCode());
        if (event.GetKeyCode() == KeyCode::KEY_SPACE) {
            OnKeySpaceEvent();
            return true;
        }
    }
    return false;
}

void VideoStateMachinePattern::OnKeySpaceEvent()
{
    if (stateManager_->IsPlaying()) {
        Pause();
    } else {
        Start();
    }
}

void VideoStateMachinePattern::MoveByStep(int32_t step)
{
    auto targetTime = static_cast<int32_t>(currentPos_) + step;
    if (0 <= targetTime && targetTime <= static_cast<int32_t>(duration_)) {
        SetCurrentTime(static_cast<float>(targetTime), OHOS::Ace::SeekMode::SEEK_CLOSEST);
    }
}

void VideoStateMachinePattern::AdjustVolume(int32_t step)
{
    // the volume ranges from 0 to 1. each step is VOLUME_STEP(0.05).
    float targetVolume = currentVolume_ + step * VOLUME_STEP;
    if (LessNotEqual(targetVolume, 0.0f) || GreatNotEqual(targetVolume, 1.0f)) {
        return;
    }
    CHECK_NULL_VOID(mediaPlayer_);
    if (NearZero(targetVolume)) {
        mediaPlayer_->SetMediaMuted(MEDIA_TYPE_AUD, true);
    } else {
        mediaPlayer_->SetMediaMuted(MEDIA_TYPE_AUD, false);
    }
    mediaPlayer_->SetVolume(targetVolume, targetVolume);
    currentVolume_ = targetVolume;
}

HiddenChangeEvent VideoStateMachinePattern::CreateHiddenChangeEvent()
{
    return [weak = WeakClaim(this)](bool hidden) {
        auto videoPattern = weak.Upgrade();
        CHECK_NULL_VOID(videoPattern);
        auto fullScreenNode = videoPattern->GetFullScreenNode();
        if (fullScreenNode) {
            auto fullScreenPattern = AceType::DynamicCast<VideoStateMachineFullScreenPattern>(fullScreenNode->GetPattern());
            CHECK_NULL_VOID(fullScreenPattern);
            fullScreenPattern->HiddenChange(hidden);
            return;
        }
        videoPattern->HiddenChange(hidden);
    };
}

void VideoStateMachinePattern::UpdatePreviewImage()
{
    auto layoutProperty = GetLayoutProperty<VideoLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (!layoutProperty->HasPosterImageInfo()) {
        return;
    }
    auto posterSourceInfo = layoutProperty->GetPosterImageInfo().value();
    auto imageFit = layoutProperty->GetObjectFitValue(ImageFit::COVER);
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto video = AceType::DynamicCast<VideoNode>(host);
    CHECK_NULL_VOID(video);
    auto image = AceType::DynamicCast<FrameNode>(video->GetPreviewImage());
    CHECK_NULL_VOID(image);
    auto posterLayoutProperty = image->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(posterLayoutProperty);

    if (showFirstFrame_) {
        posterLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
        UpdateBackgroundColor();
        image->MarkModifyDone();
        return;
    }

    if (!isInitialState_) {
        posterLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
        UpdateBackgroundColor();
        image->MarkModifyDone();
        return;
    }

    if (!posterSourceInfo.IsValid()) {
        posterLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
        UpdateBackgroundColor();
        image->MarkModifyDone();
        TAG_LOGI(AceLogTag::ACE_VIDEO, "Src image is not valid.");
        return;
    }

    auto imageRenderProperty = image->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(imageRenderProperty);
    imageRenderProperty->UpdateContentTransition(contentTransition_);
    if (contentTransition_ != ContentTransitionType::IDENTITY) {
        CHECK_NULL_VOID(renderContextForMediaPlayer_);
        renderContextForMediaPlayer_->UpdateBackgroundColor(Color::TRANSPARENT);
    } else {
        UpdateBackgroundColor();
    }

    image->SetDraggable(false);
    posterLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    posterLayoutProperty->UpdateImageSourceInfo(posterSourceInfo);
    if (EXPORT_IMAGEFIT_SUPPORT_TYPES.find(imageFit) == EXPORT_IMAGEFIT_SUPPORT_TYPES.end()) {
        imageFit = ImageFit::COVER;
    }
    posterLayoutProperty->UpdateImageFit(imageFit);
    image->MarkModifyDone();
}

void VideoStateMachinePattern::UpdateControllerBar()
{
    auto layoutProperty = GetLayoutProperty<VideoLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    auto needControlBar = layoutProperty->GetControlsValue(true);
    focusHub->SetFocusType(needControlBar ? FocusType::SCOPE : FocusType::NODE);
    auto video = AceType::DynamicCast<VideoNode>(host);
    CHECK_NULL_VOID(video);
    auto controller = AceType::DynamicCast<FrameNode>(video->GetControllerRow());
    CHECK_NULL_VOID(controller);
    if (needControlBar) {
        auto sliderNode = DynamicCast<FrameNode>(controller->GetChildAtIndex(SLIDER_POS));
        CHECK_NULL_VOID(sliderNode);
        auto sliderModifier = NodeModifier::GetSliderCustomModifier();
        CHECK_NULL_VOID(sliderModifier);
        sliderModifier->sliderPatternUpdateValue(sliderNode, static_cast<float>(currentPos_));
        sliderNode->MarkModifyDone();

        auto textNode = DynamicCast<FrameNode>(controller->GetChildAtIndex(CURRENT_POS));
        CHECK_NULL_VOID(textNode);
        auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        std::string label = IntTimeToText(currentPos_);
        textLayoutProperty->UpdateContent(label);

        auto durationNode = DynamicCast<FrameNode>(controller->GetChildAtIndex(DURATION_POS));
        CHECK_NULL_VOID(durationNode);
        auto durationTextLayoutProperty = durationNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(durationTextLayoutProperty);
        std::string durationText = IntTimeToText(duration_);
        durationTextLayoutProperty->UpdateContent(durationText);

        textNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        textNode->MarkModifyDone();
        durationNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        durationNode->MarkModifyDone();
        auto controllerLayoutProperty = controller->GetLayoutProperty<LinearLayoutProperty>();
        controllerLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
        controller->MarkModifyDone();
    } else {
        auto controllerLayoutProperty = controller->GetLayoutProperty<LinearLayoutProperty>();
        controllerLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
        controller->MarkModifyDone();
    }
}

void VideoStateMachinePattern::UpdateVideoProperty()
{
    if (isInitialState_ && autoPlay_) {
        Start();
    }

    UpdateSpeed();
    UpdateLooping();
    UpdateMuted();
}

void VideoStateMachinePattern::AddChild()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto video = AceType::DynamicCast<VideoNode>(host);
    CHECK_NULL_VOID(video);
    auto column = AceType::DynamicCast<FrameNode>(video->GetMediaColumn());
    CHECK_NULL_VOID(column);
    auto renderContext = column->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->AddChild(renderContextForMediaPlayer_, 0);
}

void VideoStateMachinePattern::OnRebuildFrame()
{
    if (!renderSurface_ || !renderSurface_->IsSurfaceValid()) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "MediaPlayer surface is not valid");
        return;
    }
    AddChild();
}

void VideoStateMachinePattern::RemoveMediaPlayerSurfaceNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto video = AceType::DynamicCast<VideoNode>(host);
    CHECK_NULL_VOID(video);
    auto column = AceType::DynamicCast<FrameNode>(video->GetMediaColumn());
    CHECK_NULL_VOID(column);
    auto renderContext = column->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->RemoveChild(renderContextForMediaPlayer_);
}

bool VideoStateMachinePattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    auto geometryNode = dirty->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);
    auto videoNodeSize = geometryNode->GetContentSize();
    auto layoutProperty = GetLayoutProperty<VideoLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto videoFrameRect = MeasureVideoContentLayout(videoNodeSize, layoutProperty);
    auto videoFrameSize = SizeF(videoFrameRect.Width(), videoFrameRect.Height());
    // Change the surface layout for drawing video frames
    if (renderContextForMediaPlayer_) {
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            auto rect = AdjustPaintRect(videoFrameRect.GetX(), videoFrameRect.GetY(),
                videoFrameRect.Width(), videoFrameRect.Height(), true);
            renderContextForMediaPlayer_->SetBounds(rect.GetX(), rect.GetY(), rect.Width(), rect.Height());
        } else {
            renderContextForMediaPlayer_->SetBounds(videoFrameRect.GetX(), videoFrameRect.GetY(),
                videoFrameRect.Width(), videoFrameRect.Height());
        }
    }

    if (IsSupportImageAnalyzer()) {
        Rect tmpRect;
        auto padding  = layoutProperty->CreatePaddingAndBorder();
        auto imageFit = layoutProperty->GetObjectFitValue(ImageFit::COVER);
        if (imageFit == ImageFit::COVER || imageFit == ImageFit::NONE) {
            tmpRect = Rect(padding.left.value_or(0), padding.top.value_or(0),
                           videoNodeSize.Width(), videoNodeSize.Height());
        } else {
            tmpRect = Rect((videoNodeSize.Width() - videoFrameSize.Width()) / AVERAGE_VALUE + padding.left.value_or(0),
                (videoNodeSize.Height() - videoFrameSize.Height()) / AVERAGE_VALUE + padding.top.value_or(0),
                videoFrameSize.Width(), videoFrameSize.Height());
        }
        if (contentRect_ != tmpRect && ShouldUpdateImageAnalyzer()) {
            StartUpdateImageAnalyzer();
        }
        contentRect_ = tmpRect;
        UpdateAnalyzerUIConfig(geometryNode);
    }

    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    host->MarkNeedSyncRenderTree();
    auto video = AceType::DynamicCast<VideoNode>(host);
    CHECK_NULL_RETURN(video, false);
    auto column = AceType::DynamicCast<FrameNode>(video->GetMediaColumn());
    CHECK_NULL_RETURN(column, false);
    column->GetRenderContext()->SetClipToBounds(true);
    return false;
}

void VideoStateMachinePattern::OnAreaChangedInner()
{
    if (SystemProperties::GetExtSurfaceEnabled()) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto geometryNode = host->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        auto videoNodeSize = geometryNode->GetContentSize();
        auto layoutProperty = GetLayoutProperty<VideoLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        auto videoFrameRect = MeasureVideoContentLayout(videoNodeSize, layoutProperty);
        auto videoFrameSize = SizeF(videoFrameRect.Width(), videoFrameRect.Height());
        auto transformRelativeOffset = host->GetTransformRelativeOffset();

        Rect rect =
            Rect(transformRelativeOffset.GetX() + (videoNodeSize.Width() - videoFrameSize.Width()) / AVERAGE_VALUE,
                transformRelativeOffset.GetY() + (videoNodeSize.Height() - videoFrameSize.Height()) / AVERAGE_VALUE,
                videoFrameSize.Width(), videoFrameSize.Height());
        if (renderSurface_ && (rect != lastBoundsRect_)) {
            renderSurface_->SetExtSurfaceBounds(rect.Left(), rect.Top(), rect.Width(), rect.Height());
            lastBoundsRect_ = rect;
        }
    }
}

void VideoStateMachinePattern::OnColorConfigurationUpdate()
{
    ContainerScope scope(instanceId_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto videoTheme = pipelineContext->GetTheme<VideoTheme>();
    CHECK_NULL_VOID(videoTheme);
    auto renderContext = controlBar_->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateBackgroundColor(videoTheme->GetBkgColor());
    for (const auto& child : controlBar_->GetChildren()) {
        if (child->GetTag() == V2::TEXT_ETS_TAG) {
            auto frameNode = AceType::DynamicCast<FrameNode>(child);
            if (frameNode) {
                auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
                if (textLayoutProperty) {
                    auto textStyle = videoTheme->GetTimeTextStyle();
                    textLayoutProperty->UpdateTextColor(textStyle.GetTextColor());
                }
            }
        }
    }
    host->SetNeedCallChildrenUpdate(false);
    host->MarkModifyDone();
    host->MarkDirtyNode();
}

RefPtr<FrameNode> VideoStateMachinePattern::CreateControlBar(int32_t nodeId)
{
    ContainerScope scope(instanceId_);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto videoTheme = pipelineContext->GetTheme<VideoTheme>();
    CHECK_NULL_RETURN(videoTheme, nullptr);
    auto controlBar = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    CHECK_NULL_RETURN(controlBar, nullptr);
    controlBar_ = controlBar;

    auto playButton = CreateSVG();
    CHECK_NULL_RETURN(playButton, nullptr);
    ChangePlayButtonTag(playButton);
    controlBar->AddChild(playButton);

    auto currentPosText = CreateText(currentPos_);
    CHECK_NULL_RETURN(currentPosText, nullptr);
    controlBar->AddChild(currentPosText);

    auto slider = CreateSlider();
    CHECK_NULL_RETURN(slider, nullptr);
    controlBar->AddChild(slider);

    auto durationText = CreateText(duration_);
    CHECK_NULL_RETURN(durationText, nullptr);
    controlBar->AddChild(durationText);

    auto fullScreenButton = CreateSVG();
    CHECK_NULL_RETURN(fullScreenButton, nullptr);
    SetFullScreenButtonCallBack(fullScreenButton);
    ChangeFullScreenButtonTag(InstanceOf<VideoFullScreenNode>(this), fullScreenButton);
    controlBar->AddChild(fullScreenButton);

    auto renderContext = controlBar->GetRenderContext();
    renderContext->UpdateBackgroundColor(videoTheme->GetBkgColor());
    auto controlBarLayoutProperty = controlBar->GetLayoutProperty<LinearLayoutProperty>();
    controlBarLayoutProperty->UpdateMainAxisAlign(FlexAlign::SPACE_BETWEEN);
    if (IsFullScreen()) {
        PaddingProperty padding;
        padding.bottom = CalcLength(LIFT_HEIGHT);
        controlBarLayoutProperty->UpdatePadding(padding);
    }
    return controlBar;
}

RefPtr<FrameNode> VideoStateMachinePattern::CreateSlider()
{
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto videoTheme = pipelineContext->GetTheme<VideoTheme>();
    CHECK_NULL_RETURN(videoTheme, nullptr);

    auto sliderModifier = NodeModifier::GetSliderCustomModifier();
    CHECK_NULL_RETURN(sliderModifier, nullptr);
    auto sliderNode = sliderModifier->createSliderFrameNode(-1);
    CHECK_NULL_RETURN(sliderNode, nullptr);

    auto sliderEdge = videoTheme->GetSliderEdge();
    PaddingProperty padding;
    padding.left = CalcLength(sliderEdge.Left());
    padding.right = CalcLength(sliderEdge.Right());
    padding.top = CalcLength(sliderEdge.Top());
    padding.bottom = CalcLength(sliderEdge.Bottom());

    sliderModifier->sliderLayoutPropertyUpdatePadding(sliderNode, padding);
    sliderModifier->sliderLayoutPropertyUpdateLayoutWeight(sliderNode, 1.0);
    std::function<void(float, int32_t)> sliderOnChangeEvent = [weak = WeakClaim(this)](float value, int32_t mode) {
        auto videoPattern = weak.Upgrade();
        CHECK_NULL_VOID(videoPattern);
        videoPattern->OnSliderChange(value, mode);
    };
    sliderModifier->sliderEventHubSetOnChange(sliderNode, reinterpret_cast<void*>(&sliderOnChangeEvent));
    auto focusHub = sliderNode->GetOrCreateFocusHub();
    CHECK_NULL_RETURN(focusHub, nullptr);
    if (InstanceOf<VideoStateMachineFullScreenPattern>(this)) {
        focusHub->SetIsDefaultFocus(true);
    }
    // slider has registered click event, so it will consume KEY_SPACE event
    // video needs register OnKeySpaceEvent extra
    focusHub->SetOnKeyCallback([weak = WeakClaim(this)](const KeyEventInfo& keyEvent) -> bool {
        auto videoPattern = weak.Upgrade();
        CHECK_NULL_RETURN(videoPattern, false);
        return videoPattern->HandleSliderKeyEvent(keyEvent);
    });

    sliderModifier->sliderPaintPropertyUpdateMax(sliderNode, static_cast<float>(duration_));
    sliderModifier->sliderPaintPropertyUpdateSelectGradientColor(sliderNode, videoTheme->GetSelectColor().GetValue());
    sliderModifier->sliderPaintPropertyUpdateSelectIsResourceColor(sliderNode, true);
    sliderModifier->sliderPaintPropertyUpdateTrackBackgroundColor(sliderNode, videoTheme->GetTrackBgColor().GetValue());
    sliderModifier->sliderPaintPropertyUpdateTrackBackgroundIsResourceColor(sliderNode, true);
    sliderModifier->sliderPaintPropertyUpdateValue(sliderNode, static_cast<float>(currentPos_));
    sliderNode->MarkModifyDone();
    return sliderNode;
}

RefPtr<FrameNode> VideoStateMachinePattern::CreateText(uint32_t time)
{
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto videoTheme = pipelineContext->GetTheme<VideoTheme>();
    CHECK_NULL_RETURN(videoTheme, nullptr);

    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, nullptr);
    auto videoLayoutProperty = GetLayoutProperty<VideoLayoutProperty>();
    CHECK_NULL_RETURN(videoLayoutProperty, nullptr);
    std::string label = "";
    if (videoLayoutProperty->GetControlsValue(true)) {
        label = IntTimeToText(time);
    }
    textLayoutProperty->UpdateContent(label);
    auto textEdge = videoTheme->GetTextEdge();
    PaddingProperty padding;
    padding.left = CalcLength(textEdge.Left());
    padding.right = CalcLength(textEdge.Right());
    padding.top = CalcLength(textEdge.Top());
    padding.bottom = CalcLength(textEdge.Bottom());
    textLayoutProperty->UpdatePadding(padding);
    auto textStyle = videoTheme->GetTimeTextStyle();
    textLayoutProperty->UpdateFontSize(textStyle.GetFontSize());
    textLayoutProperty->UpdateTextColor(textStyle.GetTextColor());
    return textNode;
}

RefPtr<FrameNode> VideoStateMachinePattern::CreateSVG()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto videoTheme = pipelineContext->GetTheme<VideoTheme>();
    CHECK_NULL_RETURN(videoTheme, nullptr);

    auto svgNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, -1, AceType::MakeRefPtr<ImagePattern>());
    CHECK_NULL_RETURN(svgNode, nullptr);

    auto imageRenderProperty = svgNode->GetPaintPropertyPtr<ImageRenderProperty>();
    imageRenderProperty->UpdateSvgFillColor(videoTheme->GetIconColor());
    auto renderContext = svgNode->GetRenderContext();
    renderContext->UpdateForegroundColor(videoTheme->GetIconColor());

    auto svgLayoutProperty = svgNode->GetLayoutProperty<ImageLayoutProperty>();

    auto btnEdge = videoTheme->GetBtnEdge();
    PaddingProperty padding;
    padding.left = CalcLength(btnEdge.Left());
    padding.right = CalcLength(btnEdge.Right());
    padding.top = CalcLength(btnEdge.Top());
    padding.bottom = CalcLength(btnEdge.Bottom());
    svgLayoutProperty->UpdatePadding(padding);

    auto btnSize = videoTheme->GetBtnSize();
    SizeF size { static_cast<float>(btnSize.Width()), static_cast<float>(btnSize.Height()) };
    svgLayoutProperty->UpdateMarginSelfIdealSize(size);
    auto width = Dimension(btnSize.Width(), DimensionUnit::VP).ConvertToPx();
    auto height = Dimension(btnSize.Height(), DimensionUnit::VP).ConvertToPx();
    CalcSize idealSize = { CalcLength(width), CalcLength(height) };
    MeasureProperty layoutConstraint;
    layoutConstraint.selfIdealSize = idealSize;
    layoutConstraint.maxSize = idealSize;
    svgNode->UpdateLayoutConstraint(layoutConstraint);
    return svgNode;
}

void VideoStateMachinePattern::Start(VideoControllerAsync::AsyncCommandCallback callback)
{
    TAG_LOGI(AceLogTag::ACE_VIDEO, "Video[%{public}d] Start() enter, %{public}s", 
        hostId_, stateManager_->GetStateInfo().c_str());
    
    if (!mediaPlayer_ || !mediaPlayer_->IsMediaPlayerValid()) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "Video[%{public}d] Start() exit: mediaPlayer invalid", hostId_);
        if (callback) {
            callback(false, "mediaPlayer invalid");
        }
        return;
    }

    if (!stateManager_->CanHandleStateTransition(VideoPlaybackCommand::PLAY)) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "Video[%{public}d] Start() rejected: %{public}s",
            hostId_, stateManager_->GetStateInfo().c_str());
        if (callback) {
            callback(false, "invalid state");
        }
        return;
    }

    // Validate that we can set pending command (do not set yet)
    if (!stateManager_->CanSetPendingCommand(VideoPlaybackCommand::PLAY)) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "Video[%{public}d] Start() rejected: cannot set pending command",
            hostId_);
        if (callback) {
            callback(false, "command conflict");
        }
        return;
    }

    ContainerScope scope(instanceId_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);

    DestroyAnalyzerOverlay();

    if (stateManager_->IsStopped()) {
        TAG_LOGI(AceLogTag::ACE_VIDEO, "Video[%{public}d] Start() from STOPPED: Step 1 Prepare (originalIntent=PLAY)", hostId_);
        stateManager_->SetPendingCommand(VideoPlaybackCommand::PREPARE, std::move(callback), VideoPlaybackCommand::PLAY);
        if (mediaPlayer_->PrepareAsync() != 0) {
            TAG_LOGW(AceLogTag::ACE_VIDEO, "Video[%{public}d] Start() PrepareAsync failed", hostId_);
            stateManager_->ClearPendingCommand();
            return;
        }
        TAG_LOGI(AceLogTag::ACE_VIDEO, "Video[%{public}d] Start() exit: waiting for PREPARED callback", hostId_);
        return;
    }
    // Set pending command right before posting the actual play task
    stateManager_->SetPendingCommand(VideoPlaybackCommand::PLAY, std::move(callback));
    auto bgTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::BACKGROUND);
    bgTaskExecutor.PostTask(
        [weak = WeakClaim(RawPtr(mediaPlayer_)), weakThis = WeakClaim(this), hostId = hostId_] {
            auto mediaPlayer = weak.Upgrade();
            CHECK_NULL_VOID(mediaPlayer);
            TAG_LOGI(AceLogTag::ACE_VIDEO, "Video[%{public}d] trigger mediaPlayer play", hostId);
            int32_t ret = mediaPlayer->Play();

            auto pattern = weakThis.Upgrade();
            CHECK_NULL_VOID(pattern);
            
            if (ret != 0) {
                TAG_LOGW(AceLogTag::ACE_VIDEO, "Video[%{public}d] mediaPlayer Play() failed: ret=%{public}d", hostId, ret);
                pattern->stateManager_->ClearPendingCommand();
                return;
            }
            
            auto currentStatus = pattern->GetCurrentPlaybackStatus();
            if (pattern->currentInjectedStatusCmd_ == "play") {
                pattern->currentInjectedStatusCmd_.clear();
                pattern->ReportCommandResultOnUIThread(
                    "setVideoPlayerStatusPlay",
                    "success",
                    "");
            }
            if (currentStatus != PlaybackStatus::STARTED) {
                pattern->ReportChangeEventOnUIThread(
                    currentStatus, pattern->GetLastProgressRate(), pattern->GetCurrentPos());
            }
        },
        "ArkUIVideoPlay");
    TAG_LOGI(AceLogTag::ACE_VIDEO, "Video[%{public}d] Start() exit: async play task posted", hostId_);
}

void VideoStateMachinePattern::Pause(VideoControllerAsync::AsyncCommandCallback callback)
{
    TAG_LOGI(AceLogTag::ACE_VIDEO, "Video[%{public}d] Pause() enter, %{public}s",
        hostId_, stateManager_->GetStateInfo().c_str());
    if (!mediaPlayer_ || !mediaPlayer_->IsMediaPlayerValid()) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "Video[%{public}d] Pause() exit: mediaPlayer invalid", hostId_);
        if (callback) {
            callback(false, "mediaPlayer invalid");
        }
        return;
    }
    if (!stateManager_->CanHandleStateTransition(VideoPlaybackCommand::PAUSE)) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "Video[%{public}d] Pause() rejected: %{public}s",
            hostId_, stateManager_->GetStateInfo().c_str());
        if (callback) {
            callback(false, "invalid state");
        }
        return;
    }

    // Validate that we can set pending command (do not set yet)
    if (!stateManager_->CanSetPendingCommand(VideoPlaybackCommand::PAUSE)) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "Video[%{public}d] Pause() rejected: cannot set pending command",
            hostId_);
        if (callback) {
            callback(false, "command conflict");
        }
        return;
    }

    ContainerScope scope(instanceId_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);

    // Set pending command right before the actual media operation
    stateManager_->SetPendingCommand(VideoPlaybackCommand::PAUSE, std::move(callback));
    TAG_LOGI(AceLogTag::ACE_VIDEO, "Video[%{public}d] trigger mediaPlayer pause", hostId_);

    auto bgTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::BACKGROUND);
    bgTaskExecutor.PostTask(
        [weak = WeakClaim(RawPtr(mediaPlayer_)), weakThis = WeakClaim(this), hostId = hostId_] {
            auto mediaPlayer = weak.Upgrade();
            CHECK_NULL_VOID(mediaPlayer);
            TAG_LOGI(AceLogTag::ACE_VIDEO, "Video[%{public}d] trigger mediaPlayer pause on bg thread", hostId);
            int32_t ret = mediaPlayer->Pause();

            auto pattern = weakThis.Upgrade();
            CHECK_NULL_VOID(pattern);
            
            if (ret != 0) {
                TAG_LOGW(AceLogTag::ACE_VIDEO, "Video[%{public}d] mediaPlayer Pause() failed: ret=%{public}d", hostId, ret);
                pattern->stateManager_->ClearPendingCommand();
                return;
            }
            
            auto currentStatus = pattern->GetCurrentPlaybackStatus();
            if (pattern->currentInjectedStatusCmd_ == "pause") {
                pattern->currentInjectedStatusCmd_.clear();
                pattern->ReportCommandResultOnUIThread(
                    "setVideoPlayerStatusPaused",
                    "success",
                    "");
            }
            if (currentStatus != PlaybackStatus::PAUSED) {
                pattern->ReportChangeEventOnUIThread(
                    currentStatus, pattern->GetLastProgressRate(), pattern->GetCurrentPos());
            }
        },
        "ArkUIVideoPause");
    TAG_LOGI(AceLogTag::ACE_VIDEO, "Video[%{public}d] Pause() exit, %{public}s",
        hostId_, stateManager_->GetStateInfo().c_str());
}

void VideoStateMachinePattern::Stop(VideoControllerAsync::AsyncCommandCallback callback)
{
    TAG_LOGI(AceLogTag::ACE_VIDEO, "Video[%{public}d] Stop() enter, %{public}s",
        hostId_, stateManager_->GetStateInfo().c_str());
    if (!mediaPlayer_ || !mediaPlayer_->IsMediaPlayerValid()) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "Video[%{public}d] Stop() exit: mediaPlayer invalid", hostId_);
        if (callback) {
            callback(false, "mediaPlayer invalid");
        }
        return;
    }
    if (!stateManager_->CanHandleStateTransition(VideoPlaybackCommand::STOP)) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "Video[%{public}d] Stop() rejected: %{public}s",
            hostId_, stateManager_->GetStateInfo().c_str());
        if (callback) {
            callback(false, "invalid state");
        }
        return;
    }

    // Validate that we can set pending command (do not set yet)
    if (!stateManager_->CanSetPendingCommand(VideoPlaybackCommand::STOP)) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "Video[%{public}d] Stop() rejected: cannot set pending command",
            hostId_);
        if (callback) {
            callback(false, "command conflict");
        }
        return;
    }

    ContainerScope scope(instanceId_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);

    // Set pending command right before the actual media operation
    stateManager_->SetPendingCommand(VideoPlaybackCommand::STOP, std::move(callback));
    TAG_LOGI(AceLogTag::ACE_VIDEO, "Video[%{public}d] trigger mediaPlayer stop", hostId_);

    auto bgTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::BACKGROUND);
    bgTaskExecutor.PostTask(
        [weak = WeakClaim(RawPtr(mediaPlayer_)), weakThis = WeakClaim(this), hostId = hostId_] {
            auto mediaPlayer = weak.Upgrade();
            CHECK_NULL_VOID(mediaPlayer);
            TAG_LOGI(AceLogTag::ACE_VIDEO, "Video[%{public}d] trigger mediaPlayer stop on bg thread", hostId);
            int32_t ret = mediaPlayer->Stop();

            auto pattern = weakThis.Upgrade();
            CHECK_NULL_VOID(pattern);
            
            if (ret != 0) {
                TAG_LOGW(AceLogTag::ACE_VIDEO, "Video[%{public}d] mediaPlayer Stop() failed: ret=%{public}d", hostId, ret);
                pattern->stateManager_->ClearPendingCommand();
                return;
            }
            
            pattern->SetIsSeeking(false);
        },
        "ArkUIVideoStop");
    TAG_LOGI(AceLogTag::ACE_VIDEO, "Video[%{public}d] Stop() exit, waiting for STOPPED callback", hostId_);
}

void VideoStateMachinePattern::FireError(int32_t code, const std::string& message)
{
    ContainerScope scope(instanceId_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);

    // OnError function must be excuted on ui, so get the uiTaskExecutor.
    auto task = [weak = WeakClaim(this), code, message] {
        auto videoPattern = weak.Upgrade();
        CHECK_NULL_VOID(videoPattern);
        ContainerScope scope(videoPattern->instanceId_);
        videoPattern->OnError(code, message);
    };
    auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    if (uiTaskExecutor.IsRunOnCurrentThread()) {
        task();
    } else {
        uiTaskExecutor.PostTask(task, "ArkUIVideoError");
    }
}

void VideoStateMachinePattern::ChangePlayButtonTag()
{
    ContainerScope scope(instanceId_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    const auto& children = host->GetChildren();
    for (const auto& child : children) {
        if (child->GetTag() == V2::ROW_ETS_TAG) {
            auto playBtn = DynamicCast<FrameNode>(child->GetChildAtIndex(0));
            ChangePlayButtonTag(playBtn);
            break;
        }
    }
}

void VideoStateMachinePattern::ChangePlayButtonTag(RefPtr<FrameNode>& playBtn)
{
    CHECK_NULL_VOID(playBtn);
    auto playClickCallback = [weak = WeakClaim(this), playing = stateManager_->IsPlaying()](GestureEvent& /* info */) {
        auto videoPattern = weak.Upgrade();
        CHECK_NULL_VOID(videoPattern);
        if (playing) {
            videoPattern->Pause();
        } else {
            videoPattern->Start();
        }
    };
    auto playBtnEvent = playBtn->GetOrCreateGestureEventHub();
    playBtnEvent->SetUserOnClick(std::move(playClickCallback));
    auto svgLayoutProperty = playBtn->GetLayoutProperty<ImageLayoutProperty>();
    auto resourceId = stateManager_->IsPlaying() ? InternalResource::ResourceId::PAUSE_SVG : InternalResource::ResourceId::PLAY_SVG;
    auto svgSourceInfo = ImageSourceInfo("");
    svgSourceInfo.SetResourceId(resourceId);
    svgLayoutProperty->UpdateImageSourceInfo(svgSourceInfo);
    playBtn->MarkModifyDone();
    playBtn->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void VideoStateMachinePattern::SetFullScreenButtonCallBack(RefPtr<FrameNode>& fullScreenBtn)
{
    CHECK_NULL_VOID(fullScreenBtn);
    auto fsClickCallback = [weak = WeakClaim(this)](GestureEvent& /* info */) {
        auto videoPattern = weak.Upgrade();
        CHECK_NULL_VOID(videoPattern);
        if (InstanceOf<VideoStateMachineFullScreenPattern>(videoPattern)) {
            auto pattern = AceType::DynamicCast<VideoStateMachineFullScreenPattern>(videoPattern);
            CHECK_NULL_VOID(pattern);
            videoPattern->ResetLastBoundsRect();
            pattern->ExitFullScreen();
        } else {
            videoPattern->FullScreen();
        }
    };
    auto fullScreenBtnEvent = fullScreenBtn->GetOrCreateGestureEventHub();
    fullScreenBtnEvent->SetUserOnClick(std::move(fsClickCallback));
}

void VideoStateMachinePattern::ChangeFullScreenButtonTag(bool isFullScreen, RefPtr<FrameNode>& fullScreenBtn)
{
    CHECK_NULL_VOID(fullScreenBtn);
    auto svgLayoutProperty = fullScreenBtn->GetLayoutProperty<ImageLayoutProperty>();
    auto resourceId =
        isFullScreen ? InternalResource::ResourceId::QUIT_FULLSCREEN_SVG : InternalResource::ResourceId::FULLSCREEN_SVG;
    auto svgSourceInfo = ImageSourceInfo("");
    svgSourceInfo.SetResourceId(resourceId);
    svgLayoutProperty->UpdateImageSourceInfo(svgSourceInfo);
    fullScreenBtn->MarkModifyDone();
    fullScreenBtn->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void VideoStateMachinePattern::SetCurrentTime(float currentPos, OHOS::Ace::SeekMode seekMode)
{
    if (!mediaPlayer_ || !mediaPlayer_->IsMediaPlayerValid() || !stateManager_->IsActive()) {
        return;
    }
    if (GreatOrEqual(currentPos, 0.0)) {
        SetIsSeeking(true);
        // When showFirstFrame=false, videoSize may still hold the old video's
        // resolution. Seek() will trigger MediaPlayer to render a frame at the
        // target position, so we must update videoSize beforehand to ensure the
        // seek preview uses the correct aspect ratio of the new video.
        if (!showFirstFrame_) {
            auto host = GetHost();
            if (host) {
                UpdatePreparedVideoSize(host);
            }
        }
        mediaPlayer_->Seek(static_cast<int32_t>(currentPos * MILLISECONDS_TO_SECONDS), seekMode);
    }
}

void VideoStateMachinePattern::OnSliderChange(float posTime, int32_t mode)
{
    SetCurrentTime(posTime, OHOS::Ace::SeekMode::SEEK_CLOSEST);
    auto eventHub = GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    if (mode == SliderChangeMode::BEGIN || mode == SliderChangeMode::MOVING) {
        eventHub->FireSeekingEvent(static_cast<double>(posTime));
    } else if (mode == SliderChangeMode::END) {
        eventHub->FireSeekedEvent(static_cast<double>(posTime));
    }
}

void VideoStateMachinePattern::OnFullScreenChange(bool isFullScreen)
{
    auto eventHub = GetEventHub<VideoEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireFullScreenChangeEvent(isFullScreen);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& children = host->GetChildren();
    for (const auto& child : children) {
        if (child->GetTag() == V2::ROW_ETS_TAG) {
            auto fsBtn = DynamicCast<FrameNode>(child->GetChildAtIndex(FULL_SCREEN_POS));
            ChangeFullScreenButtonTag(isFullScreen, fsBtn);
            break;
        }
    }

    if (!isFullScreen && mediaPlayer_ && mediaPlayer_->IsMediaPlayerValid()) {
        auto videoLayoutProperty = host->GetLayoutProperty<VideoLayoutProperty>();
        CHECK_NULL_VOID(videoLayoutProperty);
        SizeF videoSize = SizeF(
            static_cast<float>(mediaPlayer_->GetVideoWidth()),
            static_cast<float>(mediaPlayer_->GetVideoHeight()));
        videoLayoutProperty->UpdateVideoSize(videoSize);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }

    if (isEnableAnalyzer_) {
        if (!imageAnalyzerManager_) {
            EnableAnalyzer(isEnableAnalyzer_);
        }
        if (imageAnalyzerManager_ && isAnalyzerCreated_) {
            StartImageAnalyzer();
        }
    }

    if (!SystemProperties::GetExtSurfaceEnabled()) {
        return;
    }
    if (!fullScreenNodeId_.has_value()) {
        SetMediaFullScreen(isFullScreen);
        return;
    }
    auto fullScreenNode = FrameNode::GetFrameNode(V2::VIDEO_ETS_TAG, fullScreenNodeId_.value());
    CHECK_NULL_VOID(fullScreenNode);
    auto fullScreenPattern = AceType::DynamicCast<VideoStateMachineFullScreenPattern>(fullScreenNode->GetPattern());
    CHECK_NULL_VOID(fullScreenPattern);
    fullScreenPattern->SetMediaFullScreen(isFullScreen);
}

void VideoStateMachinePattern::FullScreen()
{
    if (fullScreenNodeId_.has_value()) {
        return;
    }
    ResetLastBoundsRect();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto videoNode = AceType::DynamicCast<VideoNode>(host);
    CHECK_NULL_VOID(videoNode);
    ACE_UINODE_TRACE(host);
    auto fullScreenPattern = AceType::MakeRefPtr<VideoStateMachineFullScreenPattern>(videoControllerAsync_);
    fullScreenPattern->InitFullScreenParam(
        AceType::Claim(this), renderSurface_, mediaPlayer_, renderContextForMediaPlayer_);
    fullScreenNodeId_ = ElementRegister::GetInstance()->MakeUniqueId();
    auto fullScreenNode =
        VideoFullScreenNode::CreateFullScreenNode(V2::VIDEO_ETS_TAG, fullScreenNodeId_.value(), fullScreenPattern);
    CHECK_NULL_VOID(fullScreenNode);
    fullScreenPattern->RequestFullScreen(videoNode);
}

VideoStateMachinePattern::~VideoStateMachinePattern()
{
    // Clear pending command only if this pattern owns the state manager.
    // When state manager is shared (e.g., with fullscreen pattern),
    // the context will point to a different pattern.
    if (stateManager_ && stateManager_->IsCurrentContext(this)) {
        stateManager_->ClearPendingCommand();
    }
#ifdef RENDER_EXTRACT_SUPPORTED
    if (renderContextForMediaPlayer_) {
        renderContextForMediaPlayer_->RemoveSurfaceChangedCallBack();
    }
#endif
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

void VideoStateMachinePattern::RecoverState(const RefPtr<VideoStateMachinePattern>& videoPattern)
{
    CHECK_NULL_VOID(videoPattern);
    // Clear any pending command from old pattern
    stateManager_->ClearPendingCommand();
    currentPos_ = videoPattern->GetCurrentPos();
    OnUpdateTime(currentPos_, CURRENT_POS);

    // NOTE: State machine is shared between fullscreen and non-fullscreen patterns,
    // so state transitions are NOT needed here. The state is already synchronized.
    // Only sync non-state-machine variables.
    TAG_LOGI(AceLogTag::ACE_VIDEO, "Video[%{public}d] RecoverState: syncing non-SM state from old pattern", hostId_);

    isInitialState_ = videoPattern->GetInitialState();
    auto layoutProperty = videoPattern->GetLayoutProperty<VideoLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto videoSrcInfo = layoutProperty->GetVideoSourceValue(VideoSourceInfo());
    videoSrcInfo_.src_ = videoSrcInfo.src_;
    videoSrcInfo_.bundleName_ = videoSrcInfo.bundleName_;
    videoSrcInfo_.moduleName_ = videoSrcInfo.moduleName_;
    muted_ = videoPattern->GetMuted();
    autoPlay_ = videoPattern->GetAutoPlay();
    loop_ = videoPattern->GetLoop();
    duration_ = videoPattern->GetDuration();
    showFirstFrame_ = videoPattern->showFirstFrame_;
    progressRate_ = videoPattern->GetProgressRate();
    isSeeking_ = videoPattern->GetIsSeeking();
    isAnalyzerCreated_ = videoPattern->GetAnalyzerState();
    isEnableAnalyzer_ = videoPattern->isEnableAnalyzer_;
    SetShortcutKeyEnabled(videoPattern->GetShortcutKeyEnabled());
    SetCurrentVolume(videoPattern->GetCurrentVolume());

    fullScreenNodeId_.reset();
    RegisterMediaPlayerEvent(WeakClaim(this), mediaPlayer_, videoSrcInfo_.src_, instanceId_);
#if defined(ANDROID_PLATFORM)
    if (SystemProperties::GetExtSurfaceEnabled()) {
        RegisterRenderContextCallBack();
    }
#endif
    auto videoNode = GetHost();
    CHECK_NULL_VOID(videoNode);
    // change event hub to the origin video node
    videoPattern->GetEventHub<VideoEventHub>()->AttachHost(videoNode);
    videoNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
}

void VideoStateMachinePattern::UpdateFsState()
{
    if (!fullScreenNodeId_.has_value()) {
        return;
    }
    auto videoNode = FrameNode::GetFrameNode(V2::VIDEO_ETS_TAG, fullScreenNodeId_.value());
    CHECK_NULL_VOID(videoNode);
    auto videoPattern = AceType::DynamicCast<VideoStateMachineFullScreenPattern>(videoNode->GetPattern());
    CHECK_NULL_VOID(videoPattern);
    // update full screen state
    videoPattern->UpdateState();
}

bool VideoStateMachinePattern::IsFullScreen() const
{
    return fullScreenNodeId_.has_value();
}

RefPtr<VideoStateMachinePattern> VideoStateMachinePattern::GetTargetVideoPattern()
{
    auto isFullScreen = IsFullScreen();
    auto patternIsFullScreen = AceType::InstanceOf<VideoStateMachineFullScreenPattern>(this);
    if ((isFullScreen && patternIsFullScreen) || (!isFullScreen && !patternIsFullScreen)) {
        return AceType::Claim(this);
    }
    if (patternIsFullScreen) {
        // current is full screen,need to be released
        auto fullScreenPattern = AceType::DynamicCast<VideoStateMachineFullScreenPattern>(this);
        CHECK_NULL_RETURN(fullScreenPattern, nullptr);
        return fullScreenPattern->GetVideoPattern();
    }
    // current node is origin video node, need to operate full screen node
    auto fullScreenNode = GetFullScreenNode();
    CHECK_NULL_RETURN(fullScreenNode, nullptr);
    return fullScreenNode->GetPattern<VideoStateMachinePattern>();
}

void VideoStateMachinePattern::EnableAnalyzer(bool enable)
{
    isEnableAnalyzer_ = enable;
    if (!isEnableAnalyzer_) {
        DestroyAnalyzerOverlay();
        return;
    }

    CHECK_NULL_VOID(!imageAnalyzerManager_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    ACE_UINODE_TRACE(host);
    imageAnalyzerManager_ = std::make_shared<ImageAnalyzerManager>(host, ImageAnalyzerHolder::VIDEO_CUSTOM);
}

void VideoStateMachinePattern::SetShortcutKeyEnabled(bool isEnableShortcutKey)
{
    isEnableShortcutKey_ = isEnableShortcutKey;
}

bool VideoStateMachinePattern::GetShortcutKeyEnabled() const
{
    return isEnableShortcutKey_;
}

void VideoStateMachinePattern::SetCurrentVolume(float currentVolume)
{
    currentVolume_ = currentVolume;
}

float VideoStateMachinePattern::GetCurrentVolume() const
{
    return currentVolume_;
}

void VideoStateMachinePattern::SetImageAnalyzerConfig(void* config)
{
    if (isEnableAnalyzer_) {
        CHECK_NULL_VOID(imageAnalyzerManager_);
        imageAnalyzerManager_->SetImageAnalyzerConfig(config);
    }
}

void VideoStateMachinePattern::SetImageAIOptions(void* options)
{
    if (!imageAnalyzerManager_) {
        auto host = GetHost();
        ACE_UINODE_TRACE(host);
        imageAnalyzerManager_ = std::make_shared<ImageAnalyzerManager>(host, ImageAnalyzerHolder::VIDEO_CUSTOM);
    }
    CHECK_NULL_VOID(imageAnalyzerManager_);
    imageAnalyzerManager_->SetImageAIOptions(options);
}

bool VideoStateMachinePattern::IsSupportImageAnalyzer()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto layoutProperty = host->GetLayoutProperty<VideoLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    bool needControlBar = layoutProperty->GetControlsValue(true);
    CHECK_NULL_RETURN(imageAnalyzerManager_, false);
    return isEnableAnalyzer_ && !needControlBar && imageAnalyzerManager_->IsSupportImageAnalyzerFeature();
}

bool VideoStateMachinePattern::ShouldUpdateImageAnalyzer()
{
    auto layoutProperty = GetLayoutProperty<VideoLayoutProperty>();
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

void VideoStateMachinePattern::StartImageAnalyzer()
{
    if (!IsSupportImageAnalyzer() || !imageAnalyzerManager_) {
        return;
    }

    if (imageAnalyzerManager_->IsOverlayCreated()) {
        DestroyAnalyzerOverlay();
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
        }, ANALYZER_DELAY_TIME, "ArkUIVideoCreateAnalyzerOverlay");
}

void VideoStateMachinePattern::CreateAnalyzerOverlay()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->SetOverlayNode(nullptr);
    auto context = host->GetRenderContext();
    CHECK_NULL_VOID(context);
    auto nailPixelMap = context->GetThumbnailPixelMap();
    CHECK_NULL_VOID(nailPixelMap);
    auto pixelMap = nailPixelMap->GetCropPixelMap(contentRect_);
    CHECK_NULL_VOID(pixelMap);
    auto layoutProperty = GetLayoutProperty<VideoLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto padding  = layoutProperty->CreatePaddingAndBorder();
    OffsetF contentOffset = { contentRect_.Left() - padding.left.value_or(0),
                              contentRect_.Top() - padding.top.value_or(0) };
    CHECK_NULL_VOID(imageAnalyzerManager_);
    imageAnalyzerManager_->CreateAnalyzerOverlay(pixelMap, contentOffset);
}

void VideoStateMachinePattern::StartUpdateImageAnalyzer()
{
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
        }, ANALYZER_CAPTURE_DELAY_TIME, "ArkUIVideoUpdateAnalyzerOverlay");
    isContentSizeChanged_ = true;
}

void VideoStateMachinePattern::UpdateAnalyzerOverlay()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetRenderContext();
    CHECK_NULL_VOID(context);
    auto nailPixelMap = context->GetThumbnailPixelMap();
    CHECK_NULL_VOID(nailPixelMap);
    auto pixelMap = nailPixelMap->GetCropPixelMap(contentRect_);
    CHECK_NULL_VOID(pixelMap);
    UpdateOverlayVisibility(VisibleType::VISIBLE);

    auto layoutProperty = GetLayoutProperty<VideoLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto padding  = layoutProperty->CreatePaddingAndBorder();
    OffsetF contentOffset = { contentRect_.Left() - padding.left.value_or(0),
                              contentRect_.Top() - padding.top.value_or(0) };
    CHECK_NULL_VOID(imageAnalyzerManager_);
    imageAnalyzerManager_->UpdateAnalyzerOverlay(pixelMap, contentOffset);
}

void VideoStateMachinePattern::UpdateAnalyzerUIConfig(const RefPtr<NG::GeometryNode>& geometryNode)
{
    if (IsSupportImageAnalyzer()) {
        auto layoutProperty = GetLayoutProperty<VideoLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        auto padding  = layoutProperty->CreatePaddingAndBorder();
        OffsetF contentOffset = { contentRect_.Left() - padding.left.value_or(0),
                                  contentRect_.Top() - padding.top.value_or(0) };
        PixelMapInfo info = { contentRect_.GetSize().Width(), contentRect_.GetSize().Height(),
            { contentOffset.GetX(), contentOffset.GetY() } };
        CHECK_NULL_VOID(imageAnalyzerManager_);
        imageAnalyzerManager_->UpdateAnalyzerUIConfig(geometryNode, info);
    }
}

void VideoStateMachinePattern::DestroyAnalyzerOverlay()
{
    CHECK_NULL_VOID(imageAnalyzerManager_);
    imageAnalyzerManager_->DestroyAnalyzerOverlay();
}

bool VideoStateMachinePattern::GetAnalyzerState()
{
    CHECK_NULL_RETURN(imageAnalyzerManager_, false);
    return imageAnalyzerManager_->IsOverlayCreated();
}

void VideoStateMachinePattern::UpdateOverlayVisibility(VisibleType type)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto overlayNode = host->GetOverlayNode();
    CHECK_NULL_VOID(overlayNode);
    auto prop = overlayNode->GetLayoutProperty();
    CHECK_NULL_VOID(prop);
    prop->UpdateVisibility(type);
}

void VideoStateMachinePattern::OnWindowHide()
{
#if defined(OHOS_PLATFORM)
    if (!BackgroundTaskHelper::GetInstance().HasBackgroundTask()) {
        autoPlay_ = false;
        Pause();
    }
#else
    Pause();
#endif
}

void VideoStateMachinePattern::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    Pattern::ToJsonValue(json, filter);
    if (filter.IsFastFilter()) {
        return;
    }

    json->PutExtAttr("enableAnalyzer", isEnableAnalyzer_ ? "true" : "false", filter);
    json->PutExtAttr("currentProgressRate", progressRate_, filter);
    json->PutExtAttr("surfaceBackgroundColor",
        renderContextForMediaPlayer_
            ? renderContextForMediaPlayer_->GetBackgroundColorValue(Color::BLACK).ColorToString().c_str()
            : "",
        filter);
    json->PutExtAttr("enableShortcutKey", isEnableShortcutKey_ ? "true" : "false", filter);
}

int32_t VideoStateMachinePattern::ParseCommand(const std::string& command, PlaybackStatus& status, double& speed)
{
    auto json = JsonUtil::ParseJsonString(command);
    if (!json || json->IsNull()) {
        TAG_LOGD(AceLogTag::ACE_VIDEO, "ParseCommand failed: invalid JSON string");
        return RET_FAILED;
    }

    auto cmdType = json->GetString("cmd");
    if (cmdType != "setVideoPlayerStatus" && cmdType != "setVideoPlaybackSpeed") {
        TAG_LOGD(AceLogTag::ACE_VIDEO, "ParseCommand failed: unsupported cmdType=%{public}s", cmdType.c_str());
        return RET_FAILED;
    }

    if (!json->Contains("value")) {
        TAG_LOGD(AceLogTag::ACE_VIDEO, "ParseCommand failed: missing value field");
        return RET_FAILED;
    }

    auto valueObj = json->GetValue("value");
    if (cmdType == "setVideoPlayerStatus") {
        if (valueObj->IsString()) {
            std::string valueStr = json->GetString("value", "");
            if (valueStr == "play") {
                status = PlaybackStatus::STARTED;
                return RET_SUCCESS;
            } else if (valueStr == "paused") {
                status = PlaybackStatus::PAUSED;
                return RET_SUCCESS;
            } else {
                TAG_LOGD(AceLogTag::ACE_VIDEO,
                    "ParseCommand failed: invalid status value=%{public}s", valueStr.c_str());
            }
        } else {
            TAG_LOGD(AceLogTag::ACE_VIDEO, "ParseCommand failed: value is not string for setVideoPlayerStatus");
        }
    } else if (cmdType == "setVideoPlaybackSpeed") {
        if (valueObj->IsNumber()) {
            double newSpeed = json->GetDouble("value", 0.0);
            if (GreatOrEqual(newSpeed, SPEED_0_125_X) && LessOrEqual(newSpeed, SPEED_8_00_X)) {
                speed = newSpeed;
                return RET_SUCCESS;
            } else {
                TAG_LOGD(AceLogTag::ACE_VIDEO, "ParseCommand failed: invalid speed value=%{public}f", newSpeed);
            }
        } else {
            TAG_LOGD(AceLogTag::ACE_VIDEO, "ParseCommand failed: value is not number for setVideoPlaybackSpeed");
        }
    }

    return RET_FAILED;
}

int32_t VideoStateMachinePattern::OnInjectionEvent(const std::string& command)
{
    TAG_LOGD(AceLogTag::ACE_VIDEO, "OnInjectionEvent command : %{public}s", command.c_str());
    auto host = GetHost();
    CHECK_NULL_RETURN(host, RET_FAILED);
    auto pattern = host->GetPattern<VideoStateMachinePattern>();
    CHECK_NULL_RETURN(pattern, RET_FAILED);

    PlaybackStatus status = PlaybackStatus::NONE;
    double playbackSpeed = 0.0;
    if (ParseCommand(command, status, playbackSpeed) != RET_SUCCESS) {
        TAG_LOGD(AceLogTag::ACE_VIDEO, "OnInjectionEvent failed: Command parsing failed!");
        return RET_FAILED;
    }

    if (status == PlaybackStatus::STARTED) {
        pattern->currentInjectedStatusCmd_ = "play";
        pattern->Start();
        return RET_SUCCESS;
    } else if (status == PlaybackStatus::PAUSED) {
        pattern->currentInjectedStatusCmd_ = "pause";
        pattern->Pause();
        return RET_SUCCESS;
    }

    auto currentSpeed = pattern->GetProgressRate();
    pattern->SetLastSetProgressRate(currentSpeed);
    if (NearEqual(currentSpeed, playbackSpeed)) {
        TAG_LOGD(AceLogTag::ACE_VIDEO, "OnInjectionEvent: Speed unchanged (%{public}.3f), "
            "skip injection, command=%{public}s", currentSpeed, command.c_str());
        return RET_FAILED;
    }
    pattern->UpdateProgressRate(playbackSpeed);
    pattern->SetIsProgressInjectCmd(true);
    pattern->UpdateSpeed();

    return RET_SUCCESS;
}

void VideoStateMachinePattern::ReportChangeEvent(PlaybackStatus status, double playbackSpeed, uint32_t currentPos)
{
    if (!UiSessionManager::GetInstance()) {
        return;
    }

    auto json = JsonUtil::Create();
    CHECK_NULL_VOID(json);

    auto eventObj = JsonUtil::Create(true);
    CHECK_NULL_VOID(eventObj);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto id = host->GetId();
    eventObj->Put("nodeId", id);
    eventObj->Put("cmd", "videoPlayerChanged");

    auto paramsObj = JsonUtil::Create(true);
    CHECK_NULL_VOID(paramsObj);

    std::string statusStr = "error";
    if (status == PlaybackStatus::STARTED) {
        statusStr = "play";
    } else if (status == PlaybackStatus::ERROR) {
        statusStr = "error";
    } else {
        statusStr = "others";
    }
    paramsObj->Put("videoPlayerStatus", statusStr.c_str());
    paramsObj->Put("videoPlaybackSpeed", playbackSpeed);
    std::string timeText = IntTimeToText(currentPos);
    paramsObj->Put("videoCurrentPlaybackPosition", timeText.c_str());

    eventObj->Put("params", paramsObj);
    json->Put("event", eventObj);

    UiSessionManager::GetInstance()->ReportComponentChangeEvent("result", json->ToString(),
        ComponentEventType::COMPONENT_EVENT_VIDEO);
}

void VideoStateMachinePattern::ReportCommandResult(const std::string& event, const std::string& result, const std::string& reason)
{
    if (!UiSessionManager::GetInstance()) {
        return;
    }

    auto params = JsonUtil::Create();
    CHECK_NULL_VOID(params);
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto id = host->GetId();
    params->Put("nodeId", id);
    params->Put("event", event.c_str());
    params->Put("result", result.c_str());

    if (result == "fail" && !reason.empty()) {
        params->Put("reason", reason.c_str());
    }

    auto videoResult = JsonUtil::Create();
    CHECK_NULL_VOID(videoResult);
    videoResult->Put("VideoResult", params);

    UiSessionManager::GetInstance()->ReportComponentChangeEvent("result", videoResult->ToString(),
        ComponentEventType::COMPONENT_EVENT_VIDEO);
}

void VideoStateMachinePattern::SetContentTransition(ContentTransitionType contentTransition)
{
    contentTransition_ = contentTransition;
}

void VideoStateMachinePattern::UpdateBackgroundColor()
{
    CHECK_NULL_VOID(renderContextForMediaPlayer_);
    renderContextForMediaPlayer_->UpdateBackgroundColor(surfaceBgColor_);
}

void VideoStateMachinePattern::OnAttachToFrameNodeMultiThread(const RefPtr<FrameNode>& host)
{
    CHECK_NULL_VOID(host);
    hostId_ = host->GetId();
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

#ifdef RENDER_EXTRACT_SUPPORTED
    CHECK_NULL_VOID(renderSurface_);
    auto contextType = renderSurface_->IsTexture() ?
        RenderContext::ContextType::HARDWARE_TEXTURE : RenderContext::ContextType::HARDWARE_SURFACE;
    static RenderContext::ContextParam param = { contextType, "MediaPlayerSurface",
                                                 RenderContext::PatternType::VIDEO };
#else
    static RenderContext::ContextParam param = { RenderContext::ContextType::HARDWARE_SURFACE, "MediaPlayerSurface",
                                                 RenderContext::PatternType::VIDEO, true };
    TAG_LOGI(AceLogTag::ACE_VIDEO, "Video[%{public}d] Create MediaPlayer SurfaceNode with SkipCheckInMultiInstance",
        hostId_);
#endif
    ACE_UINODE_TRACE(host);
    renderContextForMediaPlayer_->InitContext(false, param);

    if (SystemProperties::GetExtSurfaceEnabled()) {
        RegisterRenderContextCallBack();
    }

    renderContext->UpdateBackgroundColor(Color::BLACK);
    renderContextForMediaPlayer_->UpdateBackgroundColor(Color::BLACK);
    renderContext->SetClipToBounds(true);
}

std::string VideoStateMachinePattern::GetDumpInfo()
{
    std::string dumpInfo = "Video[" + std::to_string(hostId_) + "] duration: " + std::to_string(duration_) +
                           ", loop: " + std::to_string(loop_) + ", muted: " + std::to_string(muted_) +
                           ", Speed: " + std::to_string(progressRate_);
    return dumpInfo;
}

void VideoStateMachinePattern::GetSimplifyDumpInfo(std::unique_ptr<JsonValue>& json)
{
    std::string dumpInfo = "Video[" + std::to_string(hostId_) + "] duration: " + std::to_string(duration_) +
                           ", loop: " + std::to_string(loop_) + ", muted: " + std::to_string(muted_) +
                           ", Speed: " + std::to_string(progressRate_);
    json->Put("VideoPattern", dumpInfo.c_str());
}

void VideoStateMachinePattern::DumpInfo()
{
    DumpLog::GetInstance().AddDesc(GetDumpInfo());
}

void VideoStateMachinePattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("VideoPattern", GetDumpInfo().c_str());
}

void VideoStateMachinePattern::DumpSimplifyInfo(std::shared_ptr<JsonValue>& json)
{
    auto videoPatternJson = JsonUtil::Create();
    GetSimplifyDumpInfo(videoPatternJson);
    json->PutRef("CanvasPattern", std::move(videoPatternJson));
}
} // namespace OHOS::Ace::NG
