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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_VIDEO_CONTROLLER_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_VIDEO_CONTROLLER_PEER_IMPL_H

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/common/container_consts.h"
#include "core/components/video/video_controller_v2.h"

namespace OHOS::Ace::NG::GeneratedModifier {
class VideoControllerPeerImpl : public Referenced {
public:
    VideoControllerPeerImpl() = default;
    ~VideoControllerPeerImpl() override = default;

    void TriggerStart();
    void TriggerPause();
    void TriggerStop();
    void TriggerSetCurrentTime(float pos, SeekMode seekMode = SeekMode::SEEK_PREVIOUS_SYNC);
    void TriggerRequestFullscreen(bool landscape);
    void TriggerExitFullscreen();
    void TriggerReset();

    RefPtr<VideoControllerV2> GetController() const
    {
        return videoController_;
    }

    void SetController(const RefPtr<VideoControllerV2>& videoController)
    {
        videoController_ = videoController;
    }

    void SetInstanceId(int32_t id)
    {
        instanceId_ = id;
    }

private:
    int32_t instanceId_ = INSTANCE_ID_UNDEFINED;
    RefPtr<VideoControllerV2> videoController_;
    ACE_DISALLOW_COPY_AND_MOVE(VideoControllerPeerImpl);
};
} // namespace OHOS::Ace::NG::GeneratedModifier

struct VideoControllerPeer : public OHOS::Ace::NG::GeneratedModifier::VideoControllerPeerImpl {};
#endif //FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_VIDEO_CONTROLLER_PEER_IMPL_H
