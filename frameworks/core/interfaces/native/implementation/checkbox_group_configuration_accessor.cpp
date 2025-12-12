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
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/object_keeper.h"
#include "core/interfaces/native/implementation/checkbox_group_configuration_peer.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_model_static.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CheckBoxGroupConfigurationAccessor {
void DestroyPeerImpl(Ark_CheckBoxGroupConfiguration peer)
{
}
Ark_CheckBoxGroupConfiguration ConstructImpl()
{
    return PeerUtils::CreatePeer<CheckBoxGroupConfigurationPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void TriggerChangeImpl(Ark_CheckBoxGroupConfiguration peer,
    Ark_Boolean isSelect)
{
    CHECK_NULL_VOID(peer);
    auto node = peer->node_;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxGroupModelStatic::TriggerChange(frameNode, Converter::Convert<bool>(isSelect));
}
Ark_Boolean GetEnabledImpl(Ark_CheckBoxGroupConfiguration peer)
{
    auto invalid = Converter::ArkValue<Ark_Boolean>(false);
    CHECK_NULL_RETURN(peer, invalid);
    return Converter::ArkValue<Ark_Boolean>(peer->enabled_);
}
void SetEnabledImpl(Ark_CheckBoxGroupConfiguration peer,
    Ark_Boolean enabled)
{
    CHECK_NULL_VOID(peer);
    peer->enabled_ = Converter::Convert<bool>(enabled);
}
Ark_ContentModifier GetContentModifierImpl(Ark_CheckBoxGroupConfiguration peer)
{
    CHECK_NULL_RETURN(peer, {});
    return peer->contentModifier_;
}
void SetContentModifierImpl(Ark_CheckBoxGroupConfiguration peer,
    const Ark_Object* contentModifier)
{
    CHECK_NULL_VOID(peer);
    auto objectKeeper = std::make_shared<ObjectKeeper>(*contentModifier);
    peer->contentModifier_ = (*objectKeeper).get();
}
Ark_String GetNameImpl(Ark_CheckBoxGroupConfiguration peer)
{
    CHECK_NULL_RETURN(peer, {});
    return Converter::ArkValue<Ark_String>(peer->name_);
}
void SetNameImpl(Ark_CheckBoxGroupConfiguration peer,
    const Ark_String* name)
{
    CHECK_NULL_VOID(peer);
    peer->name_ = Converter::Convert<std::string>(*name);
}
Ark_SelectStatus GetStatusImpl(Ark_CheckBoxGroupConfiguration peer)
{
    CHECK_NULL_RETURN(peer, {});
    return peer->status_;
}
void SetStatusImpl(Ark_CheckBoxGroupConfiguration peer,
    Ark_SelectStatus status)
{
    CHECK_NULL_VOID(peer);
    peer->status_ = status;
}
} // CheckBoxGroupConfigurationAccessor

const GENERATED_ArkUICheckBoxGroupConfigurationAccessor* GetCheckBoxGroupConfigurationAccessor()
{
    static const GENERATED_ArkUICheckBoxGroupConfigurationAccessor CheckBoxGroupConfigurationAccessorImpl {
        CheckBoxGroupConfigurationAccessor::DestroyPeerImpl,
        CheckBoxGroupConfigurationAccessor::ConstructImpl,
        CheckBoxGroupConfigurationAccessor::GetFinalizerImpl,
        CheckBoxGroupConfigurationAccessor::TriggerChangeImpl,
        CheckBoxGroupConfigurationAccessor::GetEnabledImpl,
        CheckBoxGroupConfigurationAccessor::SetEnabledImpl,
        CheckBoxGroupConfigurationAccessor::GetContentModifierImpl,
        CheckBoxGroupConfigurationAccessor::SetContentModifierImpl,
        CheckBoxGroupConfigurationAccessor::GetNameImpl,
        CheckBoxGroupConfigurationAccessor::SetNameImpl,
        CheckBoxGroupConfigurationAccessor::GetStatusImpl,
        CheckBoxGroupConfigurationAccessor::SetStatusImpl,
    };
    return &CheckBoxGroupConfigurationAccessorImpl;
}
}
