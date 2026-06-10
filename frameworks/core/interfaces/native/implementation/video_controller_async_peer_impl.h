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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_VIDEO_CONTROLLER_ASYNC_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_VIDEO_CONTROLLER_ASYNC_PEER_IMPL_H

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/common/container_consts.h"
#include "core/components_ng/pattern/video/video_controller_async.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
class VideoControllerAsyncPeerImpl : public Referenced {
public:
    VideoControllerAsyncPeerImpl() = default;
    ~VideoControllerAsyncPeerImpl() override = default;

    void TriggerStartAsync(Ark_VMContext vmContext, Ark_AsyncWorkerPtr asyncWorker,
        const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise);
    void TriggerPauseAsync(Ark_VMContext vmContext, Ark_AsyncWorkerPtr asyncWorker,
        const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise);
    void TriggerStopAsync(Ark_VMContext vmContext, Ark_AsyncWorkerPtr asyncWorker,
        const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise);
    void TriggerResetAsync(Ark_VMContext vmContext, Ark_AsyncWorkerPtr asyncWorker,
        const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise);

    void TriggerSetCurrentTime(float pos, SeekMode seekMode = SeekMode::SEEK_PREVIOUS_SYNC);
    void TriggerRequestFullscreen(bool landscape);
    void TriggerExitFullscreen();

    RefPtr<VideoControllerAsync> GetController() const
    {
        return controller_;
    }

    void SetController(const RefPtr<VideoControllerAsync>& controller)
    {
        controller_ = controller;
    }

    void SetInstanceId(int32_t id)
    {
        instanceId_ = id;
    }

private:
    int32_t instanceId_ = INSTANCE_ID_UNDEFINED;
    RefPtr<VideoControllerAsync> controller_;
    ACE_DISALLOW_COPY_AND_MOVE(VideoControllerAsyncPeerImpl);
};
} // namespace OHOS::Ace::NG::GeneratedModifier

struct VideoControllerAsyncPeer : public OHOS::Ace::NG::GeneratedModifier::VideoControllerAsyncPeerImpl {};
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_VIDEO_CONTROLLER_ASYNC_PEER_IMPL_H
