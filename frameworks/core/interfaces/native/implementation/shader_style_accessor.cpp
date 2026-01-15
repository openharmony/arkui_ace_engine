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

#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/shader_style_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ShaderStyleAccessor {
void DestroyPeerImpl(Ark_ShaderStyle peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_ShaderStyle ConstructImpl()
{
    auto* peer = PeerUtils::CreatePeer<ShaderStylePeer>();
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
} // ShaderStyleAccessor
const GENERATED_ArkUIShaderStyleAccessor* GetShaderStyleAccessor()
{
    static const GENERATED_ArkUIShaderStyleAccessor ShaderStyleAccessorImpl {
        ShaderStyleAccessor::DestroyPeerImpl,
        ShaderStyleAccessor::ConstructImpl,
        ShaderStyleAccessor::GetFinalizerImpl,
    };
    return &ShaderStyleAccessorImpl;
}

}
