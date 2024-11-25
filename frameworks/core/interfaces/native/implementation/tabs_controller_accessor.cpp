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

#include "tabs_controller_modifier_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TabsControllerAccessor {

static void DestroyPeer(TabsControllerPeerImpl *peerImpl)
{
    if (peerImpl) {
        peerImpl->DecRefCount();
    }
}

TabsControllerPeer* CtorImpl()
{
    auto peerImpl = Referenced::MakeRefPtr<TabsControllerPeerImpl>();
    peerImpl->IncRefCount();
    return reinterpret_cast<TabsControllerPeer *>(Referenced::RawPtr(peerImpl));
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<Ark_NativePointer>(&DestroyPeer);
}
void ChangeIndexImpl(TabsControllerPeer* peer,
                     const Ark_Number* value)
{
    auto peerImpl = reinterpret_cast<TabsControllerPeerImpl *>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(value);
    auto index = Converter::Convert<Ark_Int32>(*value);
    peerImpl->TriggerChangeIndex(index);
}
Ark_NativePointer PreloadItemsImpl(TabsControllerPeer* peer,
                                   const Ark_Union_Array_Number_Undefined* indices)
{
    auto peerImpl = reinterpret_cast<TabsControllerPeerImpl *>(peer);
    CHECK_NULL_RETURN(peerImpl, nullptr);
    CHECK_NULL_RETURN(indices, nullptr);
    auto indexVectOpt = Converter::OptConvert<std::vector<int32_t>>(*indices);
    if (indexVectOpt) {
        std::set<int32_t> indexSet(indexVectOpt->begin(), indexVectOpt->end());
        peerImpl->TriggerPreloadItems(indexSet);
    }
    return nullptr;
}
} // TabsControllerAccessor
const GENERATED_ArkUITabsControllerAccessor* GetTabsControllerAccessor()
{
    static const GENERATED_ArkUITabsControllerAccessor TabsControllerAccessorImpl {
        TabsControllerAccessor::CtorImpl,
        TabsControllerAccessor::GetFinalizerImpl,
        TabsControllerAccessor::ChangeIndexImpl,
        TabsControllerAccessor::PreloadItemsImpl,
    };
    return &TabsControllerAccessorImpl;
}

}
