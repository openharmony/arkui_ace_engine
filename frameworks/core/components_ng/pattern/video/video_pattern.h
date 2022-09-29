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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIDEO_VIDEO_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIDEO_VIDEO_PATTERN_H

#include <cstddef>
#include <string>
#include <utility>

#include "base/geometry/dimension.h"
#include "base/geometry/size.h"
#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/components/video/video_controller_v2.h"
#include "core/components_ng/image_provider/image_loading_context.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/video/video_event_hub.h"
#include "core/components_ng/pattern/video/video_layout_algorithm.h"
#include "core/components_ng/pattern/video/video_layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/media_player.h"
#include "core/components_ng/render/render_surface.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
class VideoPattern : public Pattern {
    DECLARE_ACE_TYPE(VideoPattern, Pattern);

public:
    VideoPattern() = default;
    explicit VideoPattern(const RefPtr<VideoControllerV2>& videoController);
    ~VideoPattern() override = default;

    std::optional<std::string> GetSurfaceNodeName() const override
    {
        return "VideoSurface";
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

    void UpdateMuted(bool muted)
    {
        muted_ = muted;
    }

    void UpdateAutoPlay(bool autoPlay)
    {
        autoPlay_ = autoPlay;
    }

    void UpdateLoop(bool loop)
    {
        loop_ = loop;
    }

    void UpdateProgressRate(double progressRate)
    {
        progressRate_ = progressRate;
    }

    FocusType GetFocusType() override
    {
        return FocusType::NODE;
    }
    bool GetFocusable() override
    {
        return true;
    }

private:
    void OnAttachToFrameNode() override;
    void OnModifyDone() override;

    void UpdateMediaPlayer();
    void PrepareMediaPlayer();
    void PrepareSurface();
    void RegisterMediaPlayerEvent();
    void SetMethodCall();
    bool SetSourceForMediaPlayer();

    void Start();
    void Pause();
    void Stop();
    void SetCurrentTime(float currentPos, SeekMode seekMode = SeekMode::SEEK_PREVIOUS_SYNC);
    void OnFullScreenChange(bool isFullScreen);
    void FullScreen();
    void ExitFullScreen();
    void UpdateLooping();
    void SetSpeed();

    void OnCurrentTimeChange(uint32_t currentPos);
    void OnPlayerStatus(PlaybackStatus status);
    void OnError(const std::string& errorId);
    void OnResolutionChange() const;
    void OnPrepared(double width, double height, uint32_t duration, uint32_t currentPos, bool needFireEvent);
    void OnCompletion();

    void IntTimeToText(uint32_t time, std::string& timeText) const;

    RefPtr<FrameNode> CreateControlBar();
    static RefPtr<FrameNode> CreateButton(const std::string& label, GestureEventFunc clickCallback);

    RefPtr<VideoControllerV2> videoControllerV2_;
    RefPtr<RenderSurface> renderSurface_ = RenderSurface::Create();
    RefPtr<MediaPlayer> mediaPlayer_ = MediaPlayer::Create();

    bool isStop_ = false;
    bool hasInit_ = false;
    std::string src_;

    uint32_t duration_ = 0;
    uint32_t currentPos_ = 0;
    std::string durationText_;
    std::string currentPosText_;

    bool muted_ = false;
    bool autoPlay_ = false;
    bool loop_ = false;
    double progressRate_ = 1.0;

    ACE_DISALLOW_COPY_AND_MOVE(VideoPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIDEO_VIDEO_PATTERN_H
