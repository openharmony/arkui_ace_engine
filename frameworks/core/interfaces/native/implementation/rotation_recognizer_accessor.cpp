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
#include "arkoala_api_generated.h"
#include "core/interfaces/native/implementation/rotation_recognizer_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RotationRecognizerAccessor {
void DestroyPeerImpl(Ark_RotationRecognizer peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_RotationRecognizer CtorImpl()
{
    return PeerUtils::CreatePeer<RotationRecognizerPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Number GetAngleImpl(Ark_RotationRecognizer peer)
{
    auto errorValue = Converter::ArkValue<Ark_Number>(DEFAULT_ANGLE);
    CHECK_NULL_RETURN(peer, errorValue);
    return Converter::ArkValue<Ark_Number>(peer->GetAngle());
}
} // RotationRecognizerAccessor
const GENERATED_ArkUIRotationRecognizerAccessor* GetRotationRecognizerAccessor()
{
    static const GENERATED_ArkUIRotationRecognizerAccessor RotationRecognizerAccessorImpl {
        RotationRecognizerAccessor::DestroyPeerImpl,
        RotationRecognizerAccessor::CtorImpl,
        RotationRecognizerAccessor::GetFinalizerImpl,
        RotationRecognizerAccessor::GetAngleImpl,
    };
    return &RotationRecognizerAccessorImpl;
}

}
