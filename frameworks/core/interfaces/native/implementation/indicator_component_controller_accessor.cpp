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
#include "core/interfaces/native/implementation/indicator_component_controller_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "indicator_component_controller_peer.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace IndicatorComponentControllerAccessor {
void DestroyPeerImpl(Ark_IndicatorComponentController peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_IndicatorComponentController ConstructImpl()
{
    return PeerUtils::CreatePeer<IndicatorComponentControllerPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void ShowNextImpl(Ark_IndicatorComponentController peer)
{
    CHECK_NULL_VOID(peer);
    peer->ShowNext();
}
void ShowPreviousImpl(Ark_IndicatorComponentController peer)
{
    CHECK_NULL_VOID(peer);
    peer->ShowPrevious();
}
void ChangeIndexImpl(Ark_IndicatorComponentController peer,
                     const Opt_Int32* index,
                     const Opt_Boolean* useAnimation)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(index);
    int32_t idx = 0;
    if (index->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        idx = Converter::Convert<int32_t>(index->value);
    }
    idx = idx < 0 ? 0 : idx;
    auto useAnim = Converter::OptConvertPtr<bool>(useAnimation).value_or(false);
    peer->ChangeIndex(idx, useAnim);
}
} // IndicatorComponentControllerAccessor
const GENERATED_ArkUIIndicatorComponentControllerAccessor* GetIndicatorComponentControllerAccessor()
{
    static const GENERATED_ArkUIIndicatorComponentControllerAccessor IndicatorComponentControllerAccessorImpl {
        IndicatorComponentControllerAccessor::DestroyPeerImpl,
        IndicatorComponentControllerAccessor::ConstructImpl,
        IndicatorComponentControllerAccessor::GetFinalizerImpl,
        IndicatorComponentControllerAccessor::ShowNextImpl,
        IndicatorComponentControllerAccessor::ShowPreviousImpl,
        IndicatorComponentControllerAccessor::ChangeIndexImpl,
    };
    return &IndicatorComponentControllerAccessorImpl;
}

}
