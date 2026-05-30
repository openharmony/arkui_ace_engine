/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "base/utils/utils.h"
#include "core/interfaces/native/implementation/video_controller_async_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::Converter {
template<>
inline void AssignCast(std::optional<SeekMode>& dst, const Ark_SeekMode& src)
{
    switch (src) {
        case ARK_SEEK_MODE_PREVIOUS_KEYFRAME: dst = SeekMode::SEEK_PREVIOUS_SYNC; break;
        case ARK_SEEK_MODE_NEXT_KEYFRAME: dst = SeekMode::SEEK_NEXT_SYNC; break;
        case ARK_SEEK_MODE_CLOSEST_KEYFRAME: dst = SeekMode::SEEK_CLOSEST_SYNC; break;
        case ARK_SEEK_MODE_ACCURATE: dst = SeekMode::SEEK_CLOSEST; break;
        default: LOGE("Unexpected enum value in Ark_SeekMode: %{public}d", src);
    }
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace VideoControllerAsyncAccessor {
void DestroyPeerImpl(Ark_VideoControllerAsync peer)
{
    auto peerImpl = static_cast<VideoControllerAsyncPeerImpl*>(peer);
    if (peerImpl) {
        auto controller = peerImpl->GetController();
        if (controller) {
            controller->ClearPattern();
        }
        peerImpl->DecRefCount();
    }
}
Ark_VideoControllerAsync ConstructImpl()
{
    auto peerImpl = Referenced::MakeRefPtr<VideoControllerAsyncPeer>();
    peerImpl->IncRefCount();
    WeakPtr<NG::VideoStateMachinePattern> emptyPattern;
    RefPtr<VideoControllerAsync> controller =
        AceType::MakeRefPtr<VideoControllerAsync>(emptyPattern);
    peerImpl->SetController(controller);
    return static_cast<VideoControllerAsyncPeer *>(Referenced::RawPtr(peerImpl));
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void StartImpl(Ark_VMContext vmContext,
               Ark_AsyncWorkerPtr asyncWorker,
               Ark_VideoControllerAsync peer,
               const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    auto peerImpl = static_cast<VideoControllerAsyncPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerStartAsync(vmContext, asyncWorker, outputArgumentForReturningPromise);
}
void PauseImpl(Ark_VMContext vmContext,
               Ark_AsyncWorkerPtr asyncWorker,
               Ark_VideoControllerAsync peer,
               const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    auto peerImpl = static_cast<VideoControllerAsyncPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerPauseAsync(vmContext, asyncWorker, outputArgumentForReturningPromise);
}
void StopImpl(Ark_VMContext vmContext,
              Ark_AsyncWorkerPtr asyncWorker,
              Ark_VideoControllerAsync peer,
              const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    auto peerImpl = static_cast<VideoControllerAsyncPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerStopAsync(vmContext, asyncWorker, outputArgumentForReturningPromise);
}
void RequestFullscreenImpl(Ark_VideoControllerAsync peer,
                           Ark_Boolean value)
{
    auto peerImpl = static_cast<VideoControllerAsyncPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerRequestFullscreen(Converter::Convert<bool>(value));
}
void ExitFullscreenImpl(Ark_VideoControllerAsync peer)
{
    auto peerImpl = static_cast<VideoControllerAsyncPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerExitFullscreen();
}
void SetCurrentTimeImpl(Ark_VideoControllerAsync peer,
                        Ark_Float64 value,
                        const Opt_SeekMode* seekMode)
{
    auto peerImpl = static_cast<VideoControllerAsyncPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto mode = seekMode
        ? Converter::OptConvert<SeekMode>(*seekMode).value_or(SeekMode::SEEK_PREVIOUS_SYNC)
        : SeekMode::SEEK_PREVIOUS_SYNC;
    peerImpl->TriggerSetCurrentTime(Converter::Convert<double>(value), mode);
}
void ResetImpl(Ark_VMContext vmContext,
               Ark_AsyncWorkerPtr asyncWorker,
               Ark_VideoControllerAsync peer,
               const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    auto peerImpl = static_cast<VideoControllerAsyncPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerResetAsync(vmContext, asyncWorker, outputArgumentForReturningPromise);
}
} // VideoControllerAsyncAccessor
const GENERATED_ArkUIVideoControllerAsyncAccessor* GetVideoControllerAsyncAccessor()
{
    static const GENERATED_ArkUIVideoControllerAsyncAccessor VideoControllerAsyncAccessorImpl {
        VideoControllerAsyncAccessor::DestroyPeerImpl,
        VideoControllerAsyncAccessor::ConstructImpl,
        VideoControllerAsyncAccessor::GetFinalizerImpl,
        VideoControllerAsyncAccessor::StartImpl,
        VideoControllerAsyncAccessor::PauseImpl,
        VideoControllerAsyncAccessor::StopImpl,
        VideoControllerAsyncAccessor::RequestFullscreenImpl,
        VideoControllerAsyncAccessor::ExitFullscreenImpl,
        VideoControllerAsyncAccessor::SetCurrentTimeImpl,
        VideoControllerAsyncAccessor::ResetImpl,
    };
    return &VideoControllerAsyncAccessorImpl;
}

} // namespace OHOS::Ace::NG::GeneratedModifier
