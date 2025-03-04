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
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace VideoControllerAccessor {
void DestroyPeerImpl(Ark_VideoController peer)
{
}
Ark_VideoController CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void StartImpl(Ark_VideoController peer)
{
}
void PauseImpl(Ark_VideoController peer)
{
}
void StopImpl(Ark_VideoController peer)
{
}
void SetCurrentTime0Impl(Ark_VideoController peer,
                         const Ark_Number* value)
{
}
void RequestFullscreenImpl(Ark_VideoController peer,
                           Ark_Boolean value)
{
}
void ExitFullscreenImpl(Ark_VideoController peer)
{
}
void SetCurrentTime1Impl(Ark_VideoController peer,
                         const Ark_Number* value,
                         Ark_SeekMode seekMode)
{
}
void ResetImpl(Ark_VideoController peer)
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
