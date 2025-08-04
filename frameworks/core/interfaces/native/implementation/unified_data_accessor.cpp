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
#include "unified_data_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace unifiedDataChannel_UnifiedDataAccessor {
void DestroyPeerImpl(Ark_unifiedDataChannel_UnifiedData peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_unifiedDataChannel_UnifiedData ConstructImpl()
{
    return PeerUtils::CreatePeer<unifiedDataChannel_UnifiedDataPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Boolean HasTypeImpl(Ark_unifiedDataChannel_UnifiedData peer,
                        const Ark_String* UnifiedData_type)
{
    return {};
}
Array_String GetTypesImpl(Ark_unifiedDataChannel_UnifiedData peer)
{
    return {};
}
} // unifiedDataChannel_UnifiedDataAccessor
const GENERATED_ArkUIUnifiedDataChannel_UnifiedDataAccessor* GetUnifiedDataChannel_UnifiedDataAccessor()
{
    static const GENERATED_ArkUIUnifiedDataChannel_UnifiedDataAccessor UnifiedDataChannel_UnifiedDataAccessorImpl {
        unifiedDataChannel_UnifiedDataAccessor::DestroyPeerImpl,
        unifiedDataChannel_UnifiedDataAccessor::ConstructImpl,
        unifiedDataChannel_UnifiedDataAccessor::GetFinalizerImpl,
        unifiedDataChannel_UnifiedDataAccessor::HasTypeImpl,
        unifiedDataChannel_UnifiedDataAccessor::GetTypesImpl,
    };
    return &UnifiedDataChannel_UnifiedDataAccessorImpl;
}

}
