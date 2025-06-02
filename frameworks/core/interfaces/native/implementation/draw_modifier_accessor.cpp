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
#include "core/interfaces/native/implementation/draw_modifier_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace DrawModifierAccessor {
void DestroyPeerImpl(Ark_DrawModifier peer)
{
    CHECK_NULL_VOID(peer);
    peer->frameNode = nullptr;
    peer->drawModifier = nullptr;
    delete peer;
}
Ark_DrawModifier CtorImpl()
{
    auto peer = new DrawModifierPeer();
    peer->drawModifier = AceType::MakeRefPtr<DrawModifier>();
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void InvalidateImpl(Ark_DrawModifier peer)
{
    CHECK_NULL_VOID(peer);
    auto frameNode = peer->frameNode.Upgrade();
    if (frameNode) {
        const auto& extensionHandler = frameNode->GetExtensionHandler();
        if (extensionHandler) {
            extensionHandler->InvalidateRender();
        } else {
            frameNode->MarkDirtyNode(NG::PROPERTY_UPDATE_RENDER);
        }
    }
}
Callback_DrawContext_Void GetDrawBehindImpl(Ark_DrawModifier peer)
{
    return {};
}
void SetDrawBehindImpl(Ark_DrawModifier peer,
                       const Callback_DrawContext_Void* drawBehind)
{
}
Callback_DrawContext_Void GetDrawContentImpl(Ark_DrawModifier peer)
{
    return {};
}
void SetDrawContentImpl(Ark_DrawModifier peer,
                        const Callback_DrawContext_Void* drawContent)
{
}
Callback_DrawContext_Void GetDrawFrontImpl(Ark_DrawModifier peer)
{
    return {};
}
void SetDrawFrontImpl(Ark_DrawModifier peer,
                      const Callback_DrawContext_Void* drawFront)
{
}
} // DrawModifierAccessor
const GENERATED_ArkUIDrawModifierAccessor* GetDrawModifierAccessor()
{
    static const GENERATED_ArkUIDrawModifierAccessor DrawModifierAccessorImpl {
        DrawModifierAccessor::DestroyPeerImpl,
        DrawModifierAccessor::CtorImpl,
        DrawModifierAccessor::GetFinalizerImpl,
        DrawModifierAccessor::InvalidateImpl,
        DrawModifierAccessor::GetDrawBehindImpl,
        DrawModifierAccessor::SetDrawBehindImpl,
        DrawModifierAccessor::GetDrawContentImpl,
        DrawModifierAccessor::SetDrawContentImpl,
        DrawModifierAccessor::GetDrawFrontImpl,
        DrawModifierAccessor::SetDrawFrontImpl,
    };
    return &DrawModifierAccessorImpl;
}

}
