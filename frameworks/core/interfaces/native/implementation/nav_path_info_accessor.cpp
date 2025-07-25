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

#include "arkoala_api_generated.h"
#include "nav_path_info_peer_impl.h"

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace Nav = OHOS::Ace::NG::GeneratedModifier::NavigationContext;

namespace OHOS::Ace::NG::Converter {
void AssignArkValue(Ark_Object& dst, const Nav::ExternalData& src)
{
    if (src) {
        dst = src->data_;
    }
}
void AssignArkValue(Ark_NavPathInfo& dst, const Nav::PathInfo& src)
{
    auto peer = new NavPathInfoPeer();
    CHECK_NULL_VOID(peer);
    peer->data = src;
}

template<>
Nav::ExternalData Convert(const Ark_Object& src)
{
    return Referenced::MakeRefPtr<Nav::ExternalDataKeeper>(src);
}

template<>
Nav::PathInfo Convert(const Ark_NavPathInfo& src)
{
    return src ? src->data : Nav::PathInfo();
}
} // namespace OHOS::Ace::NG::Converter

using namespace OHOS::Ace::NG::Converter;

namespace OHOS::Ace::NG::GeneratedModifier {
namespace NavPathInfoAccessor {
void DestroyPeerImpl(Ark_NavPathInfo peer)
{
    delete peer;
}
Ark_NavPathInfo CtorImpl(const Ark_String* name, Ark_Boolean isEntry)
{
    CHECK_NULL_RETURN(name, nullptr);
    auto peer = new NavPathInfoPeer();
    CHECK_NULL_RETURN(peer, nullptr);
    peer->data.name_ = Convert<std::string>(*name);
    peer->data.isEntry_ = Converter::Convert<bool>(isEntry);
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_String GetNameImpl(Ark_NavPathInfo peer)
{
    CHECK_NULL_RETURN(peer, {});
    return ArkValue<Ark_String>(peer->data.name_, Converter::FC);
}
void SetNameImpl(Ark_NavPathInfo peer,
                 const Ark_String* name)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(name);
    peer->data.name_ = Convert<std::string>(*name);
}
Opt_Object GetParamImpl(Ark_NavPathInfo peer)
{
    return {};
}
void SetParamImpl(Ark_NavPathInfo peer,
                  const Opt_Object* param)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(param);
#ifdef WRONG_GEN
    peer->data.param_ = Convert<Nav::ExternalData>(*param);
#endif
}
Opt_Callback_PopInfo_Void GetOnPopImpl(Ark_NavPathInfo peer)
{
    auto invalid = Converter::ArkValue<Opt_Callback_PopInfo_Void>();
    CHECK_NULL_RETURN(peer, invalid);
    return Converter::ArkValue<Opt_Callback_PopInfo_Void>(peer->data.onPop_.GetCallback());
}
void SetOnPopImpl(Ark_NavPathInfo peer,
                  const Callback_PopInfo_Void* onPop)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(onPop);
    peer->data.onPop_ = CallbackHelper(*onPop);
}
Ark_Boolean GetIsEntryImpl(Ark_NavPathInfo peer)
{
    auto invalid = Converter::ArkValue<Ark_Boolean>(false);
    CHECK_NULL_RETURN(peer, invalid);
    return ArkValue<Ark_Boolean>(peer->data.isEntry_);
}
void SetIsEntryImpl(Ark_NavPathInfo peer,
                    Ark_Boolean isEntry)
{
    CHECK_NULL_VOID(peer);
    peer->data.isEntry_ = Convert<bool>(isEntry);
}
Ark_String GetNavDestinationIdImpl(Ark_NavPathInfo peer)
{
    auto invalidVal = Converter::ArkValue<Ark_String>("", Converter::FC);
    CHECK_NULL_RETURN(peer, invalidVal);
    return Converter::ArkValue<Ark_String>(peer->data.navDestinationId_.value_or(""), Converter::FC);
}
void SetNavDestinationIdImpl(Ark_NavPathInfo peer,
                             const Ark_String* navDestinationId)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(navDestinationId);
    auto id = Converter::Convert<std::string>(*navDestinationId);
    peer->data.navDestinationId_ = id;
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

}
