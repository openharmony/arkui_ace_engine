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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_VIDEO_VIDEO_CONTROLLER_V2_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_VIDEO_VIDEO_CONTROLLER_V2_H

#include "core/components/video/video_component.h"

namespace OHOS::Ace {

class VideoControllerV2 : public virtual AceType {
    DECLARE_ACE_TYPE(VideoControllerV2, AceType);

public:
    void Start()
    {
        for (const auto& item : controllers_) {
            item->Start();
        }
    }

    void Pause()
    {
        for (const auto& item : controllers_) {
            item->Pause();
        }
    }

    void Stop()
    {
        for (const auto& item : controllers_) {
            item->Stop();
        }
    }

    void SeekTo(float pos, SeekMode seekMode = SeekMode::SEEK_PREVIOUS_SYNC)
    {
        for (const auto& item : controllers_) {
            item->SeekTo(pos, seekMode);
        }
    }

    void RequestFullscreen(bool isPortrait)
    {
        for (const auto& item : controllers_) {
            item->RequestFullscreen(isPortrait);
        }
    }

    void ExitFullscreen(bool isSync)
    {
        for (const auto& item : controllers_) {
            item->ExitFullscreen(isSync);
        }
    }

    void AddVideoController(const RefPtr<VideoController>& videoController)
    {
        auto it = std::find(controllers_.begin(), controllers_.end(), videoController);
        if (it != controllers_.end()) {
            LOGW("Controller is already existed");
            return;
        }

        controllers_.emplace_back(videoController);
    }

    void RemoveVideoController(const RefPtr<VideoController>& videoController)
    {
        if (videoController) {
            controllers_.remove(videoController);
        }
    }

    void Clear()
    {
        controllers_.clear();
    }

private:
    std::list<RefPtr<VideoController>> controllers_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_VIDEO_VIDEO_CONTROLLER_V2_H
