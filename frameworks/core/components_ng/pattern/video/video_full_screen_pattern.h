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

#include "core/components/video/video_controller_v2.h"
#include "core/components_ng/manager/focus/focus_view.h"
#include "core/components_ng/pattern/video/video_node.h"
#include "core/components_ng/pattern/video/video_pattern.h"

namespace OHOS::Ace::NG {
class VideoFullScreenPattern : public VideoPattern, public FocusView {
    DECLARE_ACE_TYPE(VideoFullScreenPattern, VideoPattern);

public:
    VideoFullScreenPattern() = delete;
    explicit VideoFullScreenPattern(const RefPtr<VideoControllerV2>& videoController) : VideoPattern(videoController) {}
    ~VideoFullScreenPattern() override = default;
    void InitFullScreenParam(const RefPtr<VideoPattern>& video, const RefPtr<RenderSurface>& renderSurface,
        const RefPtr<MediaPlayer>& mediaPlayer, const RefPtr<RenderContext>& context);
    void RequestFullScreen(const RefPtr<VideoNode>& videoNode);

    bool ExitFullScreen();

    bool OnBackPressed() override
    {
        ExitFullScreen();
        return true;
    }

    std::list<int32_t> GetRouteOfFirstScope() override
    {
        return {};
    }

    const RefPtr<VideoPattern> GetOriginVideoPattern()
    {
        return videoPattern_.Upgrade();
    }

    const RefPtr<VideoPattern> GetVideoPattern()
    {
        return videoPattern_.Upgrade();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return eventHub_;
    }

    void SetEventHub(const RefPtr<EventHub>& eventHub);

    void UpdateState();

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        auto videoPattern = videoPattern_.Upgrade();
        if (!videoPattern) {
            return MakeRefPtr<VideoLayoutProperty>();
        }
        auto layoutProperty = videoPattern->GetLayoutProperty<VideoLayoutProperty>()->Clone();
        DynamicCast<VideoLayoutProperty>(layoutProperty)->fullScreenReset();
        return layoutProperty;
    }

    bool IsFullScreen() const override
    {
        // full screen state check from origin video fullScreenNodeId_
        auto videoPattern = videoPattern_.Upgrade();
        CHECK_NULL_RETURN(videoPattern, false);
        return videoPattern->IsFullScreen();
    }

private:
    WeakPtr<VideoPattern> videoPattern_;
    RefPtr<EventHub> eventHub_;
    RefPtr<GestureEventHub> originGestureEventHub_;
};
} // namespace OHOS::Ace::NG
#endif