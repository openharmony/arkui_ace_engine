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

#include "core/common/container_scope.h"
#include "core/components/video/video_utils.h"
#include "core/interfaces/arkoala/implementation/video_controller_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {
void VideoControllerPeerImpl::TriggerStart()
{
    ContainerScope scope(instanceId_);
    if (auto controller = handler_.Upgrade(); controller) {
        controller->Start();
    }
}

void VideoControllerPeerImpl::TriggerPause()
{
    ContainerScope scope(instanceId_);
    if (auto controller = handler_.Upgrade(); controller) {
        controller->Pause();
    }
}

void VideoControllerPeerImpl::TriggerStop()
{
    ContainerScope scope(instanceId_);
    if (auto controller = handler_.Upgrade(); controller) {
        controller->Stop();
    }
}

void VideoControllerPeerImpl::TriggerSetCurrentTime(float pos, SeekMode seekMode)
{
    ContainerScope scope(instanceId_);
    if (auto controller = handler_.Upgrade(); controller) {
        controller->SeekTo(pos, seekMode);
    }
}

void VideoControllerPeerImpl::TriggerRequestFullscreen(bool landscape)
{
    ContainerScope scope(instanceId_);
    if (auto controller = handler_.Upgrade(); controller) {
        controller->RequestFullscreen(landscape);
    }
}

void VideoControllerPeerImpl::TriggerExitFullscreen()
{
    ContainerScope scope(instanceId_);
    if (auto controller = handler_.Upgrade(); controller) {
        controller->ExitFullscreen(false);
    }
}

void VideoControllerPeerImpl::TriggerReset()
{
    ContainerScope scope(instanceId_);
    if (auto controller = handler_.Upgrade(); controller) {
        controller->Reset();
    }
}
} // namespace OHOS::Ace::NG::GeneratedModifier