/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace VideoControllerAccessor {
void DestroyPeerImpl(VideoControllerPeer* peer)
{
}
VideoControllerPeer* CtorImpl()
{
    return new VideoControllerPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void StartImpl(VideoControllerPeer* peer)
{
}
void PauseImpl(VideoControllerPeer* peer)
{
}
void StopImpl(VideoControllerPeer* peer)
{
}
void SetCurrentTime0Impl(VideoControllerPeer* peer,
                         const Ark_Number* value)
{
}
void RequestFullscreenImpl(VideoControllerPeer* peer,
                           Ark_Boolean value)
{
}
void ExitFullscreenImpl(VideoControllerPeer* peer)
{
}
void SetCurrentTime1Impl(VideoControllerPeer* peer,
                         const Ark_Number* value,
                         Ark_SeekMode seekMode)
{
}
void ResetImpl(VideoControllerPeer* peer)
{
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
        VideoControllerAccessor::RequestFullscreenImpl,
        VideoControllerAccessor::ExitFullscreenImpl,
        VideoControllerAccessor::SetCurrentTime1Impl,
        VideoControllerAccessor::ResetImpl,
    };
    return &VideoControllerAccessorImpl;
}

}
