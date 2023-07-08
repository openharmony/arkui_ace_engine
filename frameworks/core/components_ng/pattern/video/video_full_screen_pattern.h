/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIDEO_VIDEO_FULL_SCREEN_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIDEO_VIDEO_FULL_SCREEN_PATTERN_H

#include "core/components_ng/pattern/video/video_pattern.h"
#include "core/components/video/video_controller_v2.h"
#include "core/components_ng/pattern/video/video_node.h"

namespace OHOS::Ace::NG {
class VideoFullScreenPattern : public VideoPattern {
    DECLARE_ACE_TYPE(VideoFullScreenPattern, VideoPattern);
public:
    VideoFullScreenPattern() = default;
    explicit VideoFullScreenPattern(const RefPtr<VideoControllerV2>& videoController): VideoPattern(videoController) {}
    ~VideoFullScreenPattern() override = default;
    void InitFullScreenParam(const RefPtr<VideoPattern>& video,
                             const RefPtr<RenderSurface>& renderSurface,
                             const RefPtr<MediaPlayer>& mediaPlayer,
                             const RefPtr<RenderContext>& context);
    void RequestFullScreen(const RefPtr<VideoNode>& videoNode);

    void ExitFullScreen();

    bool OnBackPressed() override
    {
        ExitFullScreen();
        return true;
    }

    const RefPtr<VideoPattern> GetOriginVideoPattern()
    {
        return videoPattern_.Upgrade();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return eventHub_;
    }

    void SetEventHub(const RefPtr<EventHub>& eventHub)
    {
        eventHub_ = eventHub;
    }

    void UpdateState();

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        auto videoPattern = videoPattern_.Upgrade();
        if (!videoPattern) {
            return MakeRefPtr<VideoLayoutProperty>();
        }
        return videoPattern->GetLayoutProperty<VideoLayoutProperty>()->Clone();
    }

private:
    WeakPtr<VideoPattern> videoPattern_;
    RefPtr<EventHub> eventHub_;
};
}
#endif