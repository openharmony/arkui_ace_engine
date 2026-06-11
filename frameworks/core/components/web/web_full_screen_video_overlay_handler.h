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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_FULL_SCREEN_VIDEO_OVERLAY_HANDLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_FULL_SCREEN_VIDEO_OVERLAY_HANDLER_H

#include <functional>
#include <memory>
#include <string>

#include "base/memory/ace_type.h"

namespace OHOS::Ace::NG {
class FrameNode;
} // namespace OHOS::Ace::NG

namespace OHOS::Ace {

class ACE_EXPORT VideoPlayerListener {
public:
    VideoPlayerListener() = default;
    ~VideoPlayerListener() = default;

    std::function<void(int32_t status)> OnStatusChanged;
    std::function<void(bool muted)> OnMutedChanged;
    std::function<void(double playbackRate)> OnPlaybackRateChanged;
    std::function<void(double duration)> OnDurationChanged;
    std::function<void(double currentPlayTime)> OnTimeUpdate;
    std::function<void(double bufferedEndTime)> OnBufferedEndTimeChanged;
    std::function<void()> OnEnded;
    std::function<void(int32_t width, int32_t height)> OnVideoSizeChanged;
};

class ACE_EXPORT FullScreenVideoOverlayHandler : public AceType {
    DECLARE_ACE_TYPE(FullScreenVideoOverlayHandler, AceType);

public:
    FullScreenVideoOverlayHandler() = default;
    ~FullScreenVideoOverlayHandler() = default;

    virtual void SetVideoSurface(std::string surfaceId) = 0;
    virtual void RequestMediaControl(int32_t action, std::string param) = 0;
    virtual void AddListener(std::shared_ptr<VideoPlayerListener> listener) = 0;
    virtual WeakPtr<NG::FrameNode> GetWebNode() { return nullptr; };
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_FULL_SCREEN_VIDEO_OVERLAY_HANDLER_H
