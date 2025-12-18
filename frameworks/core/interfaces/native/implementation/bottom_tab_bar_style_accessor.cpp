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
#include "core/interfaces/native/utility/validators.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/implementation/bottom_tab_bar_style_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace BottomTabBarStyleAccessor {
void DestroyPeerImpl(Ark_BottomTabBarStyle peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_BottomTabBarStyle ConstructImpl(const Ark_Union_ResourceStr_TabBarSymbol* icon,
                                    const Ark_ResourceStr* text)
{
    auto peer = PeerUtils::CreatePeer<BottomTabBarStylePeer>();
    peer->text = Converter::OptConvertPtr<std::string>(text);
    std::optional<std::string> ic = std::nullopt;
    Converter::VisitUnionPtr(icon,
        [&ic](const Ark_ResourceStr& arkIcon) {
            ic = Converter::OptConvert<std::string>(arkIcon);
        },
        [](const Ark_TabBarSymbol& arkTabBarSymbol) {
            LOGE("BottomTabBarStyleAccessor.ConstructImpl Ark_TabBarSymbol for icon is not supported yet.");
        },
        []() {}
    );
    peer->icon = ic;
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_BottomTabBarStyle OfImpl(const Ark_Union_ResourceStr_TabBarSymbol* icon,
                             const Ark_ResourceStr* text)
{
    return ConstructImpl(icon, text);
}
Ark_BottomTabBarStyle LabelStyleImpl(Ark_BottomTabBarStyle peer,
                                     const Ark_TabBarLabelStyle* style)
{
    CHECK_NULL_RETURN(peer, peer);
    peer->labelStyle = Converter::OptConvertPtr<LabelStyle>(style);
    return peer;
}
Ark_BottomTabBarStyle PaddingImpl(Ark_BottomTabBarStyle peer,
                                  const Ark_Union_Padding_Dimension_LocalizedPadding* value)
{
    CHECK_NULL_RETURN(peer, peer);
    std::optional<PaddingProperty> optPadding;
    bool useLocalizedPadding = false;
    Converter::VisitUnionPtr(value,
        [&optPadding](const Ark_Padding& arkPadding) {
            optPadding = Converter::OptConvert<PaddingProperty>(arkPadding);
        },
        [&optPadding](const Ark_Dimension& arkLength) {
            optPadding = Converter::OptConvert<PaddingProperty>(arkLength);
        },
        [&optPadding, &useLocalizedPadding](const Ark_LocalizedPadding& arkLocalizedPadding) {
            optPadding = Converter::OptConvert<PaddingProperty>(arkLocalizedPadding);
            useLocalizedPadding = true;
        },
        []() {}
    );
    Validator::ValidatePaddingProperty(optPadding);
    peer->padding = optPadding;
    peer->useLocalizedPadding = useLocalizedPadding;
    return peer;
}
Ark_BottomTabBarStyle LayoutModeImpl(Ark_BottomTabBarStyle peer,
                                     Ark_LayoutMode value)
{
    CHECK_NULL_RETURN(peer, peer);
    peer->layoutMode = Converter::OptConvert<LayoutMode>(value);
    return peer;
}
Ark_BottomTabBarStyle VerticalAlignImpl(Ark_BottomTabBarStyle peer,
                                        Ark_VerticalAlign value)
{
    CHECK_NULL_RETURN(peer, peer);
    peer->verticalAlign = Converter::OptConvert<FlexAlign>(value);
    return peer;
}
Ark_BottomTabBarStyle SymmetricExtensibleImpl(Ark_BottomTabBarStyle peer,
                                              Ark_Boolean value)
{
    CHECK_NULL_RETURN(peer, peer);
    peer->symmetricExtensible = Converter::OptConvert<bool>(value);
    return peer;
}
Ark_BottomTabBarStyle IdImpl(Ark_BottomTabBarStyle peer,
                             const Ark_String* value)
{
    CHECK_NULL_RETURN(peer, peer);
    peer->id = Converter::OptConvertPtr<std::string>(value);
    return peer;
}
Ark_BottomTabBarStyle IconStyleImpl(Ark_BottomTabBarStyle peer,
                                    const Ark_TabBarIconStyle* style)
{
    CHECK_NULL_RETURN(peer, peer);
    peer->iconStyle = Converter::OptConvertPtr<IconStyle>(style);
    return peer;
}
} // BottomTabBarStyleAccessor
const GENERATED_ArkUIBottomTabBarStyleAccessor* GetBottomTabBarStyleAccessor()
{
    static const GENERATED_ArkUIBottomTabBarStyleAccessor BottomTabBarStyleAccessorImpl {
        BottomTabBarStyleAccessor::DestroyPeerImpl,
        BottomTabBarStyleAccessor::ConstructImpl,
        BottomTabBarStyleAccessor::GetFinalizerImpl,
        BottomTabBarStyleAccessor::OfImpl,
        BottomTabBarStyleAccessor::LabelStyleImpl,
        BottomTabBarStyleAccessor::PaddingImpl,
        BottomTabBarStyleAccessor::LayoutModeImpl,
        BottomTabBarStyleAccessor::VerticalAlignImpl,
        BottomTabBarStyleAccessor::SymmetricExtensibleImpl,
        BottomTabBarStyleAccessor::IdImpl,
        BottomTabBarStyleAccessor::IconStyleImpl,
    };
    return &BottomTabBarStyleAccessorImpl;
}

}
