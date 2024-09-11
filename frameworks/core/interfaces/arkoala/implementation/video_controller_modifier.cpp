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

#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace VideoControllerModifier {
Ark_NativePointer CtorImpl()
{
    return 0;
}
Ark_NativePointer GetFinalizerImpl()
{
    return 0;
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
                         enum Ark_SeekMode seekMode)
{
}
void ResetImpl(VideoControllerPeer* peer)
{
}
} // VideoControllerModifier
const GENERATED_ArkUIVideoControllerAccessor* GetVideoControllerAccessor()
{
    static const GENERATED_ArkUIVideoControllerAccessor VideoControllerAccessorImpl {
        VideoControllerModifier::CtorImpl,
        VideoControllerModifier::GetFinalizerImpl,
        VideoControllerModifier::StartImpl,
        VideoControllerModifier::PauseImpl,
        VideoControllerModifier::StopImpl,
        VideoControllerModifier::SetCurrentTime0Impl,
        VideoControllerModifier::RequestFullscreenImpl,
        VideoControllerModifier::ExitFullscreenImpl,
        VideoControllerModifier::SetCurrentTime1Impl,
        VideoControllerModifier::ResetImpl,
    };
    return &VideoControllerAccessorImpl;
}

}
