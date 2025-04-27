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
#include "core/interfaces/native/implementation/nav_path_info_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace NavPathInfoAccessor {
void DestroyPeerImpl(Ark_NavPathInfo peer)
{
    if (peer) {
        delete peer;
        peer = nullptr;
    }
}
Ark_NavPathInfo CtorImpl(const Ark_String* name,
                         const Ark_Object* param,
                         const Opt_Callback_PopInfo_Void* onPop,
                         const Opt_Boolean* isEntry)
{
    CHECK_NULL_RETURN(name, nullptr);
    auto peer = new NavPathInfoPeer();
    CHECK_NULL_RETURN(peer, nullptr);
    peer->data.name_ = Converter::Convert<std::string>(*name);
    peer->data.isEntry_ = Converter::OptConvert<bool>(*isEntry).value_or(false);
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_String GetNameImpl(Ark_NavPathInfo peer)
{
    return {};
}
void SetNameImpl(Ark_NavPathInfo peer,
                 const Ark_String* name)
{
}
Opt_Object GetParamImpl(Ark_NavPathInfo peer)
{
    return {};
}
void SetParamImpl(Ark_NavPathInfo peer,
                  const Opt_Object* param)
{
}
Opt_Callback_PopInfo_Void GetOnPopImpl(Ark_NavPathInfo peer)
{
    return {};
}
void SetOnPopImpl(Ark_NavPathInfo peer,
                  const Callback_PopInfo_Void* onPop)
{
}
Opt_Boolean GetIsEntryImpl(Ark_NavPathInfo peer)
{
    return {};
}
void SetIsEntryImpl(Ark_NavPathInfo peer,
                    Ark_Boolean isEntry)
{
}
Opt_String GetNavDestinationIdImpl(Ark_NavPathInfo peer)
{
    return {};
}
void SetNavDestinationIdImpl(Ark_NavPathInfo peer,
                             const Ark_String* navDestinationId)
{
}
} // NavPathInfoAccessor
const GENERATED_ArkUINavPathInfoAccessor* GetNavPathInfoAccessor()
{
    static const GENERATED_ArkUINavPathInfoAccessor NavPathInfoAccessorImpl {
        NavPathInfoAccessor::DestroyPeerImpl,
        NavPathInfoAccessor::CtorImpl,
        NavPathInfoAccessor::GetFinalizerImpl,
        NavPathInfoAccessor::GetNameImpl,
        NavPathInfoAccessor::SetNameImpl,
        NavPathInfoAccessor::GetParamImpl,
        NavPathInfoAccessor::SetParamImpl,
        NavPathInfoAccessor::GetOnPopImpl,
        NavPathInfoAccessor::SetOnPopImpl,
        NavPathInfoAccessor::GetIsEntryImpl,
        NavPathInfoAccessor::SetIsEntryImpl,
        NavPathInfoAccessor::GetNavDestinationIdImpl,
        NavPathInfoAccessor::SetNavDestinationIdImpl,
    };
    return &NavPathInfoAccessorImpl;
}

struct NavPathInfoPeer {
    virtual ~NavPathInfoPeer() = default;
};
}
