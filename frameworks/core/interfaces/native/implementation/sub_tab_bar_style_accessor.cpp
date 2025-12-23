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
#include "core/interfaces/native/implementation/sub_tab_bar_style_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace SubTabBarStyleAccessor {
void DestroyPeerImpl(Ark_SubTabBarStyle peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_SubTabBarStyle ConstructImpl(const Ark_Union_ResourceStr_ComponentContent* content)
{
    auto peer = PeerUtils::CreatePeer<SubTabBarStylePeer>();
    std::optional<std::string> cntnt = std::nullopt;
    Converter::VisitUnionPtr(content,
        [&cntnt](const Ark_ResourceStr& arkContent) {
            cntnt = Converter::OptConvert<std::string>(arkContent);
        },
        [](const Ark_ComponentContent& arkContent) {
            LOGE("SubTabBarStyleAccessor.ConstructImpl content (type Ark_ComponentContent) is not supported yet.");
        },
        []() {}
    );
    peer->content = cntnt;
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_SubTabBarStyle OfImpl(const Ark_Union_ResourceStr_ComponentContent* content)
{
    return ConstructImpl(content);
}
Ark_SubTabBarStyle IndicatorImpl(Ark_SubTabBarStyle peer,
                                 const Ark_SubTabBarIndicatorStyle* style)
{
    CHECK_NULL_RETURN(peer, peer);
    peer->indicator = Converter::OptConvertPtr<IndicatorStyle>(style);
    peer->IncRefCount();
    return peer;
}
Ark_SubTabBarStyle SelectedModeImpl(Ark_SubTabBarStyle peer,
                                    Ark_SelectedMode value)
{
    CHECK_NULL_RETURN(peer, peer);
    peer->selectedMode = Converter::OptConvert<SelectedMode>(value);
    peer->IncRefCount();
    return peer;
}
Ark_SubTabBarStyle BoardImpl(Ark_SubTabBarStyle peer,
                             const Ark_BoardStyle* value)
{
    CHECK_NULL_RETURN(peer, peer);
    peer->board = Converter::OptConvertPtr<BoardStyle>(value);
    peer->IncRefCount();
    return peer;
}
Ark_SubTabBarStyle LabelStyleImpl(Ark_SubTabBarStyle peer,
                                  const Ark_TabBarLabelStyle* style)
{
    CHECK_NULL_RETURN(peer, peer);
    peer->labelStyle = Converter::OptConvertPtr<LabelStyle>(style);
    peer->IncRefCount();
    return peer;
}
Ark_SubTabBarStyle Padding0Impl(Ark_SubTabBarStyle peer,
                                const Ark_Union_Padding_Dimension* value)
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
        []() {}
    );
    Validator::ValidatePaddingProperty(optPadding);
    peer->padding = optPadding;
    peer->IncRefCount();
    return peer;
}
Ark_SubTabBarStyle Padding1Impl(Ark_SubTabBarStyle peer,
                                const Ark_LocalizedPadding* padding)
{
    CHECK_NULL_RETURN(peer, peer);
    std::optional<PaddingProperty> optPadding = Converter::OptConvertPtr<PaddingProperty>(padding);
    bool useLocalizedPadding = true;
    Validator::ValidatePaddingProperty(optPadding);
    peer->padding = optPadding;
    peer->useLocalizedPadding = useLocalizedPadding;
    peer->IncRefCount();
    return peer;
}
Ark_SubTabBarStyle IdImpl(Ark_SubTabBarStyle peer,
                          const Ark_String* value)
{
    CHECK_NULL_RETURN(peer, peer);
    peer->id = Converter::OptConvertPtr<std::string>(value);
    peer->IncRefCount();
    return peer;
}
} // SubTabBarStyleAccessor
const GENERATED_ArkUISubTabBarStyleAccessor* GetSubTabBarStyleAccessor()
{
    static const GENERATED_ArkUISubTabBarStyleAccessor SubTabBarStyleAccessorImpl {
        SubTabBarStyleAccessor::DestroyPeerImpl,
        SubTabBarStyleAccessor::ConstructImpl,
        SubTabBarStyleAccessor::GetFinalizerImpl,
        SubTabBarStyleAccessor::OfImpl,
        SubTabBarStyleAccessor::IndicatorImpl,
        SubTabBarStyleAccessor::SelectedModeImpl,
        SubTabBarStyleAccessor::BoardImpl,
        SubTabBarStyleAccessor::LabelStyleImpl,
        SubTabBarStyleAccessor::Padding0Impl,
        SubTabBarStyleAccessor::Padding1Impl,
        SubTabBarStyleAccessor::IdImpl,
    };
    return &SubTabBarStyleAccessorImpl;
}

}
