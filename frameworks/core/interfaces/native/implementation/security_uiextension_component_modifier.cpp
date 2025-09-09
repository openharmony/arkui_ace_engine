/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifdef WINDOW_SCENE_SUPPORTED
#include "core/components_ng/pattern/ui_extension/security_ui_extension_component/security_ui_extension_model_static.h"
#include "core/interfaces/native/implementation/security_ui_extension_proxy_peer.h"
#endif
#include "core/components_ng/base/frame_node.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
#ifdef WINDOW_SCENE_SUPPORTED
const GENERATED_ArkUISecurityUIExtensionProxyAccessor* GetSecurityUIExtensionProxyAccessor();
#endif // WINDOW_SCENE_SUPPORTED
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace SecurityUIExtensionComponentModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
#ifdef WINDOW_SCENE_SUPPORTED
    LOGI("[SecurityUIExtensionComponentModifier] ConstructImpl.");
    auto frameNode = NG::SecurityUIExtensionStatic::CreateSecurityUIExtensionComponent(
        id, NG::SessionType::SECURITY_UI_EXTENSION_ABILITY);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
#else
    return {};
#endif //WINDOW_SCENE_SUPPORTED
}
} // SecurityUIExtensionComponentModifier

namespace SecurityUIExtensionComponentAttributeModifier {
void OnRemoteReadyImpl(Ark_NativePointer node,
    const Opt_Callback_SecurityUIExtensionProxy_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
#ifdef WINDOW_SCENE_SUPPORTED
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        return;
    }
    auto onRemoteReady =
        [arkCallback = CallbackHelper(*optValue)](const RefPtr<SecurityUIExtensionProxy>& proxy) {
            auto accessor = GetSecurityUIExtensionProxyAccessor();
            CHECK_NULL_VOID(accessor);
            auto peer = accessor->ctor();
            CHECK_NULL_VOID(peer);
            auto uiExtensionProxyPeerPtr = reinterpret_cast<SecurityUIExtensionProxyPeer*>(peer);
            uiExtensionProxyPeerPtr->SetProxy(proxy);
            arkCallback.Invoke(peer);
        };
    NG::SecurityUIExtensionStatic::SetSecurityOnRemoteReady(frameNode, std::move(onRemoteReady));
#endif //WINDOW_SCENE_SUPPORTED
}
} // SecurityUIExtensionComponentAttributeModifier
const GENERATED_ArkUISecurityUIExtensionComponentModifier* GetSecurityUIExtensionComponentModifier()
{
    static const GENERATED_ArkUISecurityUIExtensionComponentModifier ArkUISecurityUIExtensionComponentModifierImpl {
        SecurityUIExtensionComponentModifier::ConstructImpl,
        SecurityUIExtensionComponentAttributeModifier::OnRemoteReadyImpl,
    };
    return &ArkUISecurityUIExtensionComponentModifierImpl;
}
}