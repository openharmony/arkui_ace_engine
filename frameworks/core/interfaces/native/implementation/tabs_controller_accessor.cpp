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

#include "tabs_controller_modifier_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TabsControllerAccessor {
void DestroyPeerImpl(Ark_TabsController peer)
{
    auto peerImpl = reinterpret_cast<TabsControllerPeerImpl *>(peer);
    if (peerImpl) {
        peerImpl->DecRefCount();
    }
}
Ark_TabsController CtorImpl()
{
    auto peerImpl = Referenced::MakeRefPtr<TabsControllerPeerImpl>();
    peerImpl->IncRefCount();
    return reinterpret_cast<TabsControllerPeer *>(Referenced::RawPtr(peerImpl));
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void ChangeIndexImpl(Ark_TabsController peer,
                     const Ark_Number* value)
{
    auto peerImpl = reinterpret_cast<TabsControllerPeerImpl *>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(value);
    auto index = Converter::Convert<Ark_Int32>(*value);
    peerImpl->TriggerChangeIndex(index);
}
void PreloadItemsImpl(Ark_VMContext vmContext,
                      Ark_AsyncWorkerPtr asyncWorker,
                      Ark_TabsController peer,
                      const Opt_Array_Number* indices,
                      const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    auto peerImpl = reinterpret_cast<TabsControllerPeerImpl *>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(indices);
    auto indexVectOpt = Converter::OptConvert<std::vector<int32_t>>(*indices);
    if (indexVectOpt) {
        std::set<int32_t> indexSet(indexVectOpt->begin(), indexVectOpt->end());
        peerImpl->TriggerPreloadItems(indexSet);
    }
}
void SetTabBarTranslateImpl(Ark_TabsController peer,
                            const Ark_TranslateOptions* translate)
{
    auto peerImpl = reinterpret_cast<TabsControllerPeerImpl *>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(translate);
    NG::TranslateOptions convValue;
    convValue.x = Converter::OptConvert<CalcDimension>(translate->x).value_or(convValue.x);
    convValue.y = Converter::OptConvert<CalcDimension>(translate->y).value_or(convValue.y);
    convValue.z = Converter::OptConvert<CalcDimension>(translate->z).value_or(convValue.z);
    peerImpl->TriggerSetTabBarTranslate(convValue);
}
void SetTabBarOpacityImpl(Ark_TabsController peer,
                          const Ark_Number* opacity)
{
    auto peerImpl = reinterpret_cast<TabsControllerPeerImpl *>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(opacity);
    auto convValue = Converter::Convert<float>(*opacity);
    peerImpl->TriggerSetTabBarOpacity(convValue);
}
} // TabsControllerAccessor
const GENERATED_ArkUITabsControllerAccessor* GetTabsControllerAccessor()
{
    static const GENERATED_ArkUITabsControllerAccessor TabsControllerAccessorImpl {
        TabsControllerAccessor::DestroyPeerImpl,
        TabsControllerAccessor::CtorImpl,
        TabsControllerAccessor::GetFinalizerImpl,
        TabsControllerAccessor::ChangeIndexImpl,
        TabsControllerAccessor::PreloadItemsImpl,
        TabsControllerAccessor::SetTabBarTranslateImpl,
        TabsControllerAccessor::SetTabBarOpacityImpl,
    };
    return &TabsControllerAccessorImpl;
}

}
