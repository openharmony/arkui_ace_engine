/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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
    using SaveComponentEvent = std::function<void(std::unordered_map<std::string, RefPtr<Component>>)>;

    VideoComponentV2() = default;
    ~VideoComponentV2() override = default;

    RefPtr<Element> CreateElement() override;

    std::unordered_map<std::string, RefPtr<Component>>& GetGestureComponentMap()
    {
        return map_;
    }

    void SetGestureComponentMap(std::unordered_map<std::string, RefPtr<Component>> map)
    {
        map_ = map;
    }

    void SetVideoControllerV2(const RefPtr<VideoControllerV2>& videoControllerV2)
    {
        videoControllerV2_ = videoControllerV2;
    }

    void SetVideoController(const RefPtr<VideoController>& videoController) override
    {
        if (videoControllerV2_) {
            videoControllerV2_->RemoveVideoController(GetVideoController());
        }

        VideoComponent::SetVideoController(videoController);
        if (videoControllerV2_) {
            videoControllerV2_->AddVideoController(GetVideoController());
        }
    }

    void SetSaveComponentEvent(SaveComponentEvent&& saveComponentEvent)
    {
        saveComponentEvent_ = std::move(saveComponentEvent);
    }

    SaveComponentEvent GetSaveComponentEvent()
    {
        return saveComponentEvent_;
    }

private:
    std::unordered_map<std::string, RefPtr<Component>> map_;
    RefPtr<VideoControllerV2> videoControllerV2_;
    SaveComponentEvent saveComponentEvent_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_VIDEO_VIDEO_COMPONENT_V2_H
