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

#include "core/components_ng/base/extension_handler.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/implementation/draw_context_peer.h"
#include "core/interfaces/native/implementation/draw_modifier_peer_impl.h"
#include "core/interfaces/native/utility/callback_helper.h"
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
Ark_DrawModifier ConstructImpl()
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
Callback_DrawContext_Void GetDrawBehind_callbackImpl(Ark_DrawModifier peer)
{
    auto handler = [peer](Ark_DrawContext drawContext) {
        CHECK_NULL_VOID(peer && peer->drawModifier && peer->drawModifier->drawBehindFunc && drawContext);
        peer->drawModifier->drawBehindFunc(*drawContext);
    };
    auto callback = CallbackKeeper::ReturnReverseCallback<Callback_DrawContext_Void,
        std::function<void(Ark_DrawContext)>>(handler);
    return callback;
}
void SetDrawBehind_callbackImpl(Ark_DrawModifier peer,
                                const Callback_DrawContext_Void* drawBehind_callback)
{
    CHECK_NULL_VOID(peer && peer->drawModifier && drawBehind_callback);
    peer->drawModifier->drawBehindFunc = [arkCallback = CallbackHelper(*drawBehind_callback)](
        NG::DrawingContext& context) -> void {
        auto drawingContext = reinterpret_cast<Ark_DrawContext>(&context);
        arkCallback.InvokeSync(drawingContext);
    };
}
Callback_DrawContext_Void GetDrawContent_callbackImpl(Ark_DrawModifier peer)
{
    auto handler = [peer](Ark_DrawContext drawContext) {
        CHECK_NULL_VOID(peer && peer->drawModifier && peer->drawModifier->drawContentFunc && drawContext);
        peer->drawModifier->drawContentFunc(*drawContext);
    };
    auto callback = CallbackKeeper::ReturnReverseCallback<Callback_DrawContext_Void,
        std::function<void(Ark_DrawContext)>>(handler);
    return callback;
}
void SetDrawContent_callbackImpl(Ark_DrawModifier peer,
                                 const Callback_DrawContext_Void* drawContent_callback)
{
    CHECK_NULL_VOID(peer && peer->drawModifier && drawContent_callback);
    peer->drawModifier->drawContentFunc = [arkCallback = CallbackHelper(*drawContent_callback)](
        NG::DrawingContext& context) -> void {
        auto drawingContext = reinterpret_cast<Ark_DrawContext>(&context);
        arkCallback.InvokeSync(drawingContext);
    };
}
} // DrawModifierAccessor
const GENERATED_ArkUIDrawModifierAccessor* GetDrawModifierAccessor()
{
    static const GENERATED_ArkUIDrawModifierAccessor DrawModifierAccessorImpl {
        DrawModifierAccessor::DestroyPeerImpl,
        DrawModifierAccessor::ConstructImpl,
        DrawModifierAccessor::GetFinalizerImpl,
        DrawModifierAccessor::InvalidateImpl,
        DrawModifierAccessor::GetDrawBehind_callbackImpl,
        DrawModifierAccessor::SetDrawBehind_callbackImpl,
        DrawModifierAccessor::GetDrawContent_callbackImpl,
        DrawModifierAccessor::SetDrawContent_callbackImpl,
    };
    return &DrawModifierAccessorImpl;
}

}
