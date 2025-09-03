/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/frame_node.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/implementation/video_controller_peer_impl.h"
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
namespace VideoControllerAccessor {
void DestroyPeerImpl(Ark_VideoController peer)
{
    auto peerImpl = reinterpret_cast<VideoControllerPeerImpl*>(peer);
    if (peerImpl) {
        const auto& controller = peerImpl->GetController();
        peerImpl->DecRefCount();
        if (controller) {
            controller->Clear();
        }
    }
}
Ark_VideoController CtorImpl()
{
    auto peerImpl = Referenced::MakeRefPtr<VideoControllerPeerImpl>();
    peerImpl->IncRefCount();
    RefPtr<VideoControllerV2> controller = AceType::MakeRefPtr<VideoControllerV2>();
    peerImpl->SetController(controller);
    return reinterpret_cast<VideoControllerPeer *>(Referenced::RawPtr(peerImpl));
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void StartImpl(Ark_VideoController peer)
{
    auto peerImpl = reinterpret_cast<VideoControllerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerStart();
}
void PauseImpl(Ark_VideoController peer)
{
    auto peerImpl = reinterpret_cast<VideoControllerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerPause();
}
void StopImpl(Ark_VideoController peer)
{
    auto peerImpl = reinterpret_cast<VideoControllerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerStop();
}
void SetCurrentTime0Impl(Ark_VideoController peer,
                         const Ark_Number* value)
{
    CHECK_NULL_VOID(value);
    auto peerImpl = reinterpret_cast<VideoControllerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerSetCurrentTime(Converter::Convert<float>(*value));
}
void SetCurrentTime1Impl(Ark_VideoController peer,
                         const Ark_Number* value,
                         Ark_SeekMode seekMode)
{
    CHECK_NULL_VOID(value);
    auto peerImpl = reinterpret_cast<VideoControllerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto seekModeValue = Converter::OptConvert<SeekMode>(seekMode).value_or(SeekMode::SEEK_PREVIOUS_SYNC);
    peerImpl->TriggerSetCurrentTime(Converter::Convert<float>(*value), seekModeValue);
}
void RequestFullscreenImpl(Ark_VideoController peer,
                           Ark_Boolean value)
{
    auto peerImpl = reinterpret_cast<VideoControllerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerRequestFullscreen(Converter::Convert<bool>(value));
}
void ExitFullscreenImpl(Ark_VideoController peer)
{
    auto peerImpl = reinterpret_cast<VideoControllerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerExitFullscreen();
}
void ResetImpl(Ark_VideoController peer)
{
    auto peerImpl = reinterpret_cast<VideoControllerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerReset();
}
} // VideoControllerAccessor
const GENERATED_ArkUIVideoControllerAccessor* GetVideoControllerAccessor()
{
    static const GENERATED_ArkUIVideoControllerAccessor VideoControllerAccessorImpl {
        VideoControllerAccessor::DestroyPeerImpl,
        VideoControllerAccessor::CtorImpl,
        VideoControllerAccessor::GetFinalizerImpl,
        VideoControllerAccessor::StartImpl,
        VideoControllerAccessor::PauseImpl,
        VideoControllerAccessor::StopImpl,
        VideoControllerAccessor::SetCurrentTime0Impl,
        VideoControllerAccessor::SetCurrentTime1Impl,
        VideoControllerAccessor::RequestFullscreenImpl,
        VideoControllerAccessor::ExitFullscreenImpl,
        VideoControllerAccessor::ResetImpl,
    };
    return &VideoControllerAccessorImpl;
}

}
