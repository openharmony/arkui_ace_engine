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
#include "core/interfaces/native/utility/reverse_converter.h"
#include "long_press_recognizer_peer.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace LongPressRecognizerAccessor {
void DestroyPeerImpl(Ark_LongPressRecognizer peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_LongPressRecognizer CtorImpl()
{
    return PeerUtils::CreatePeer<LongPressRecognizerPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Boolean IsRepeatImpl(Ark_LongPressRecognizer peer)
{
    auto errorValue = Converter::ArkValue<Ark_Boolean>(DEFAULT_REPEAT);
    CHECK_NULL_RETURN(peer, errorValue);
    return Converter::ArkValue<Ark_Boolean>(peer->GetRepeat());
}
Ark_Number GetDurationImpl(Ark_LongPressRecognizer peer)
{
    auto errorValue = Converter::ArkValue<Ark_Number>(DEFAULT_DURATION);
    CHECK_NULL_RETURN(peer, errorValue);
    return Converter::ArkValue<Ark_Number>(peer->GetDuration());
}
} // LongPressRecognizerAccessor
const GENERATED_ArkUILongPressRecognizerAccessor* GetLongPressRecognizerAccessor()
{
    static const GENERATED_ArkUILongPressRecognizerAccessor LongPressRecognizerAccessorImpl {
        LongPressRecognizerAccessor::DestroyPeerImpl,
        LongPressRecognizerAccessor::CtorImpl,
        LongPressRecognizerAccessor::GetFinalizerImpl,
        LongPressRecognizerAccessor::IsRepeatImpl,
        LongPressRecognizerAccessor::GetDurationImpl,
    };
    return &LongPressRecognizerAccessorImpl;
}

}
