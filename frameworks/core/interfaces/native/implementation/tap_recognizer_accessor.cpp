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
#include "tap_recognizer_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TapRecognizerAccessor {
void DestroyPeerImpl(Ark_TapRecognizer peer)
{
    delete peer;
}
Ark_TapRecognizer CtorImpl()
{
    auto* peer = new TapRecognizerPeer();
    peer->recognizer = Ace::MakeRefPtr<Ace::NG::ClickRecognizer>();
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Number GetTapCountImpl(Ark_TapRecognizer peer)
{
    if (!peer || !peer->recognizer) {
        return Converter::ArkValue<Ark_Number>(0);
    }
    return Converter::ArkValue<Ark_Number>(peer->tapRecognizer->GetTapCount());
}
} // TapRecognizerAccessor
const GENERATED_ArkUITapRecognizerAccessor* GetTapRecognizerAccessor()
{
    static const GENERATED_ArkUITapRecognizerAccessor TapRecognizerAccessorImpl {
        TapRecognizerAccessor::DestroyPeerImpl,
        TapRecognizerAccessor::CtorImpl,
        TapRecognizerAccessor::GetFinalizerImpl,
        TapRecognizerAccessor::GetTapCountImpl,
    };
    return &TapRecognizerAccessorImpl;
}

}
