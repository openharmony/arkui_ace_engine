/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_VIDEO_VIDEO_COMPONENT_V2_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_VIDEO_VIDEO_COMPONENT_V2_H

#include "core/components/video/video_component.h"

namespace OHOS::Ace {

// A component can show Video.
class ACE_EXPORT VideoComponentV2 : public VideoComponent {
    DECLARE_ACE_TYPE(VideoComponentV2, VideoComponent);

public:
    VideoComponentV2() : VideoComponent() {}
    ~VideoComponentV2() override = default;

    RefPtr<Element> CreateElement() override;

    bool GetPlayMode() const
    {
        return playMode_;
    }

    void SetPlayMode(bool playMode)
    {
        playMode_ = playMode;
    }

    bool GetFullscreenMode() const
    {
        return fullscreen_;
    }

    void SetFullscreenMode(bool fullscreen)
    {
        fullscreen_ = fullscreen;
    }

    int32_t GetCurrentTime()
    {
        return currentTime_;
    }

    void SetCurrentTime(int32_t currentTime)
    {
        currentTime_ = currentTime;
    }

    std::unordered_map<std::string, RefPtr<Component>>& GetGuestureComponentMap()
    {
        return map_;
    }

    void SetGuestureComponentMap(std::unordered_map<std::string, RefPtr<Component>> map)
    {
        map_ = map;
    }
private:
    bool playMode_ = false;
    bool fullscreen_ = false;
    int32_t currentTime_ = -1;
    std::unordered_map<std::string, RefPtr<Component>> map_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_VIDEO_VIDEO_COMPONENT_V2_H
