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
#include "core/interfaces/native/implementation/menu_item_configuration_peer.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace MenuItemConfigurationAccessor {
void DestroyPeerImpl(Ark_MenuItemConfiguration peer)
{
}
Ark_MenuItemConfiguration ConstructImpl()
{
    return PeerUtils::CreatePeer<MenuItemConfigurationPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void TriggerSelectImpl(Ark_MenuItemConfiguration peer,
                       const Ark_Int32 index,
                       const Ark_String* value)
{
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<std::string>(*value);
    CHECK_NULL_VOID(peer);
    auto node = peer->node;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelNG::SetChangeValue(frameNode, index, convValue);
}
Ark_Boolean GetEnabledImpl(Ark_MenuItemConfiguration peer)
{
    CHECK_NULL_RETURN(peer, {});
    return peer->enabled;
}
void SetEnabledImpl(Ark_MenuItemConfiguration peer,
                    Ark_Boolean enabled)
{
}
Ark_ContentModifier GetContentModifierImpl(Ark_MenuItemConfiguration peer)
{
    CHECK_NULL_RETURN(peer, {});
    return peer->contentModifier;
}
void SetContentModifierImpl(Ark_MenuItemConfiguration peer,
                            const Ark_Object* contentModifier)
{
}
Ark_ResourceStr GetValueImpl(Ark_MenuItemConfiguration peer)
{
    CHECK_NULL_RETURN(peer, {});
    return peer->value;
}
void SetValueImpl(Ark_MenuItemConfiguration peer,
                  const Ark_ResourceStr* value)
{
}
Opt_ResourceStr GetIconImpl(Ark_MenuItemConfiguration peer)
{
    CHECK_NULL_RETURN(peer, {});
    return peer->icon;
}
void SetIconImpl(Ark_MenuItemConfiguration peer,
                 const Opt_ResourceStr* icon)
{
}
Opt_SymbolGlyphModifier GetSymbolIconImpl(Ark_MenuItemConfiguration peer)
{
    CHECK_NULL_RETURN(peer, {});
    return peer->symbolIcon;
}
void SetSymbolIconImpl(Ark_MenuItemConfiguration peer,
                       const Opt_SymbolGlyphModifier* symbolIcon)
{
}
Ark_Boolean GetSelectedImpl(Ark_MenuItemConfiguration peer)
{
    CHECK_NULL_RETURN(peer, {});
    return peer->selected;
}
void SetSelectedImpl(Ark_MenuItemConfiguration peer,
                     Ark_Boolean selected)
{
}
Ark_Int32 GetIndexImpl(Ark_MenuItemConfiguration peer)
{
    CHECK_NULL_RETURN(peer, {});
    return peer->index;
}
void SetIndexImpl(Ark_MenuItemConfiguration peer,
                  const Ark_Int32 index)
{
}
} // MenuItemConfigurationAccessor
const GENERATED_ArkUIMenuItemConfigurationAccessor* GetMenuItemConfigurationAccessor()
{
    static const GENERATED_ArkUIMenuItemConfigurationAccessor MenuItemConfigurationAccessorImpl {
        MenuItemConfigurationAccessor::DestroyPeerImpl,
        MenuItemConfigurationAccessor::ConstructImpl,
        MenuItemConfigurationAccessor::GetFinalizerImpl,
        MenuItemConfigurationAccessor::TriggerSelectImpl,
        MenuItemConfigurationAccessor::GetEnabledImpl,
        MenuItemConfigurationAccessor::SetEnabledImpl,
        MenuItemConfigurationAccessor::GetContentModifierImpl,
        MenuItemConfigurationAccessor::SetContentModifierImpl,
        MenuItemConfigurationAccessor::GetValueImpl,
        MenuItemConfigurationAccessor::SetValueImpl,
        MenuItemConfigurationAccessor::GetIconImpl,
        MenuItemConfigurationAccessor::SetIconImpl,
        MenuItemConfigurationAccessor::GetSymbolIconImpl,
        MenuItemConfigurationAccessor::SetSymbolIconImpl,
        MenuItemConfigurationAccessor::GetSelectedImpl,
        MenuItemConfigurationAccessor::SetSelectedImpl,
        MenuItemConfigurationAccessor::GetIndexImpl,
        MenuItemConfigurationAccessor::SetIndexImpl,
    };
    return &MenuItemConfigurationAccessorImpl;
}

}
