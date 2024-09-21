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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MOVING_PHOTO_MOVING_PHOTO_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MOVING_PHOTO_MOVING_PHOTO_PATTERN_H

#include "movingphoto_layout_algorithm.h"
#include "movingphoto_layout_property.h"
#include "movingphoto_event_hub.h"
#include "movingphoto_controller.h"
#include "movingphoto_utils.h"

#include "base/memory/referenced.h"
#include "core/common/container.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/long_press_event.h"
#include "core/components_ng/event/touch_event.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/render/media_player.h"
#include "core/components_ng/render/render_surface.h"
#include "core/components/video/video_utils.h"
#include "core/components/image/image_event.h"

namespace OHOS::Ace::NG {
class MovingPhotoPattern : public Pattern {
    DECLARE_ACE_TYPE(MovingPhotoPattern, Pattern);

public:
    MovingPhotoPattern() = delete;
    explicit MovingPhotoPattern(const RefPtr<MovingPhotoController>& controller);
    ~MovingPhotoPattern() override;

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<MovingPhotoEventHub>();
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<MovingPhotoLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<MovingPhotoLayoutAlgorithm>();
    }

    void UpdateMuted(bool isMuted)
    {
        isMuted_ = isMuted;
    }

    bool GetMuted()
    {
        return isMuted_;
    }

    bool GetPrepared()
    {
        return isPrepared_;
    }

    bool GetPlayByController()
    {
        return isPlayByController_;
    }

    void OnVisibleChange(bool isVisible) override;

    void OnAreaChangedInner() override;

    void AutoPlayPeriod(int64_t startTime, int64_t endTime);

    void AutoPlay(bool isAutoPlay);

    void RepeatPlay(bool isRepeatPlay);

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::NODE, false };
    }

    void UpdateCurrentDateModified(int64_t currentDateModified)
    {
        currentDateModified_ = currentDateModified;
    }

    int64_t GetCurrentDateModified()
    {
        return currentDateModified_;
    }

protected:
    int32_t instanceId_;

    RefPtr<MediaPlayer> mediaPlayer_ = MediaPlayer::Create();
    RefPtr<RenderSurface> renderSurface_ = RenderSurface::Create();
    RefPtr<RenderContext> renderContextForMediaPlayer_ = RenderContext::Create();

private:
    void OnModifyDone() override;
    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode(FrameNode* frameNode) override;
    void OnDetachFromMainTree() override;
    void OnRebuildFrame() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void OnWindowHide() override;
    void OnWindowShow() override;
    
    void RegisterVisibleAreaChange();
    void VisibleAreaCallback(bool visible);

    void InitEvent();
    void HandleLongPress(GestureEvent& info);
    void HandleTouchEvent(TouchEventInfo& info);

    void UpdateImageNode();
    void UpdateVideoNode();
    void UpdatePlayMode();
    SizeF CalculateFitContain(const SizeF& rawSize, const SizeF& layoutSize);
    SizeF CalculateFitFill(const SizeF& layoutSize);
    SizeF CalculateFitCover(const SizeF& rawSize, const SizeF& layoutSize);
    SizeF CalculateFitNone(const SizeF& rawSize);
    SizeF CalculateFitScaleDown(const SizeF& rawSize, const SizeF& layoutSize);
    SizeF CalculateFitAuto(const SizeF& rawSize, const SizeF& layoutSize);
    SizeF MeasureContentLayout(const SizeF& layoutSize, const RefPtr<MovingPhotoLayoutProperty>& layoutProperty);
    SizeF GetRawImageSize();

    void PrepareMediaPlayer();
    void ResetMediaPlayer();
    void PrepareSurface();
    void RegisterMediaPlayerEvent();
    void PrintMediaPlayerStatus(PlaybackStatus status);
    void RegisterImageEvent();
    void HandleImageCompleteEvent(const LoadImageSuccessEvent& info);
    void MediaResetToPlay();

    void FireMediaPlayerImageComplete();
    void OnMediaPlayerStatusChanged(PlaybackStatus status);
    void OnMediaPlayerInitialized();
    void OnMediaPlayerPrepared();
    void OnMediaPlayerStoped();
    void OnMediaPlayerCompletion();
    void OnPlayPositionChanged(uint32_t pos) {};
    void FireMediaPlayerStart();
    void FireMediaPlayerStop();
    void FireMediaPlayerPause();
    void FireMediaPlayerFinish();
    void FireMediaPlayerError();
    void OnResolutionChange();
    void OnStartRenderFrame();
    void OnStartedStatusCallback();

    void Start();
    void Pause();
    void Stop();
    void Seek(int32_t position);

    void VisiblePlayback();
    void SelectPlaybackMode(PlaybackMode mode);
    void StartPlayback();
    void StartAnimation();
    void StopPlayback();
    void PausePlayback();
    void StopAnimation();
    void StopAnimationCallback();
    void StartAutoPlay();
    void StartRepeatPlay();
    void SetAutoPlayPeriod(int64_t startTime, int64_t endTime);

    void UpdateMediaPlayerSpeed();
    void UpdateMediaPlayerMuted();

    void HideImageNode();

    RefPtr<LongPressEvent> longPressEvent_;
    RefPtr<TouchEventImpl> touchEvent_;
    RefPtr<MovingPhotoController> controller_;

    int32_t fd_ = -1;
    int64_t autoPlayPeriodStartTime_ = -1;
    int64_t autoPlayPeriodEndTime_ = -1;
    std::string uri_ = "";
    bool startAnimationFlag_ = false;
    bool isPrepared_ = false;
    bool isMuted_ = false;
    bool isPlayByController_ = false;
    bool isFastKeyUp_ = false;
    bool hasVisibleChangeRegistered_ = false;
    bool isFirstRepeatPlay_ = true;
    bool isSetAutoPlayPeriod_ = false;
    bool isVisible_ = false;
    bool isChangePlayMode_ = false;
    bool needUpdateImageNode_ = false;
    PlaybackStatus currentPlayStatus_ = PlaybackStatus::NONE;
    PlaybackMode autoAndRepeatLevel_ = PlaybackMode::NONE;
    PlaybackMode historyAutoAndRepeatLevel_ = PlaybackMode::NONE;
    int64_t currentDateModified_ = -2;

    Rect lastBoundsRect_;

    ACE_DISALLOW_COPY_AND_MOVE(MovingPhotoPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MOVING_PHOTO_MOVING_PHOTO_PATTERN_H
