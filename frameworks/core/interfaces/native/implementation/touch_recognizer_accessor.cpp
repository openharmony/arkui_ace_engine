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

#include "core/interfaces/native/implementation/touch_recognizer_peer.h"
#include "core/interfaces/native/implementation/event_target_info_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TouchRecognizerAccessor {
void DestroyPeerImpl(Ark_TouchRecognizer peer)
{
    LOGE("ARKOALA TouchRecognizerAccessor is not supported yet");
    PeerUtils::DestroyPeer(peer);
}
Ark_TouchRecognizer ConstructImpl()
{
    return PeerUtils::CreatePeer<TouchRecognizerPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_EventTargetInfo GetEventTargetInfoImpl(Ark_TouchRecognizer peer)
{
    LOGE("ARKOALA TouchRecognizerAccessor.GetEventTargetInfo not supported yet");
    auto ret = AceType::MakeRefPtr<EventTargetInfoPeer>();
    ret->IncRefCount();
    return AceType::RawPtr(ret);
}
void CancelTouchImpl(Ark_TouchRecognizer peer)
{
    LOGE("ARKOALA TouchRecognizerAccessor.CancelTouch not supported yet");
}
} // TouchRecognizerAccessor
const GENERATED_ArkUITouchRecognizerAccessor* GetTouchRecognizerAccessor()
{
    static const GENERATED_ArkUITouchRecognizerAccessor TouchRecognizerAccessorImpl {
        TouchRecognizerAccessor::DestroyPeerImpl,
        TouchRecognizerAccessor::ConstructImpl,
        TouchRecognizerAccessor::GetFinalizerImpl,
        TouchRecognizerAccessor::GetEventTargetInfoImpl,
        TouchRecognizerAccessor::CancelTouchImpl,
    };
    return &TouchRecognizerAccessorImpl;
}

}
