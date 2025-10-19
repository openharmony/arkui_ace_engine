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
#include "arkoala_api_generated.h"

#ifdef WINDOW_SCENE_SUPPORTED
#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_model_static.h"
#include "core/interfaces/native/implementation/ui_extension_proxy_peer.h"
#include "want.h"
#endif //WINDOW_SCENE_SUPPORTED
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
#ifdef WINDOW_SCENE_SUPPORTED
const GENERATED_ArkUIUIExtensionProxyAccessor* GetUIExtensionProxyAccessor();
#endif //WINDOW_SCENE_SUPPORTED
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace UIExtensionComponentModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
#ifdef WINDOW_SCENE_SUPPORTED
    auto frameNode = UIExtensionStatic::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
#else
    return nullptr;
#endif //WINDOW_SCENE_SUPPORTED
}
} // UIExtensionComponentModifier
namespace UIExtensionComponentInterfaceModifier {
void SetUIExtensionComponentOptionsImpl(Ark_NativePointer node,
                                        Ark_Want want,
                                        const Opt_UIExtensionOptions* options)
{
    LOGE("UIExtensionComponentInterfaceModifier::SetUIExtensionComponentOptionsImpl - "
            "'UIExtensionOptions::areaChangePlaceholder' is not supported");
}
} // UIExtensionComponentInterfaceModifier
namespace UIExtensionComponentAttributeModifier {
void SetOnRemoteReadyImpl(Ark_NativePointer node,
                          const Opt_Callback_UIExtensionProxy_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
#ifdef WINDOW_SCENE_SUPPORTED
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        UIExtensionStatic::SetOnRemoteReady(frameNode, nullptr);
        return;
    }
    auto onRemoteReady =
        [arkCallback = CallbackHelper(*optValue)](const RefPtr<UIExtensionProxy>& proxy) {
            auto accessor = GetUIExtensionProxyAccessor();
            CHECK_NULL_VOID(accessor);
            auto peer = accessor->construct();
            CHECK_NULL_VOID(peer);
            auto uiExtensionProxyPeerPtr = reinterpret_cast<UIExtensionProxyPeer*>(peer);
            uiExtensionProxyPeerPtr->SetProxy(proxy);
            arkCallback.Invoke(peer);
        };
    UIExtensionStatic::SetOnRemoteReady(frameNode, std::move(onRemoteReady));
#endif //WINDOW_SCENE_SUPPORTED
}
void SetOnReceiveImpl(Ark_NativePointer node,
                      const Opt_Callback_Map_String_RecordData_Void* value)
{
    LOGE("UIExtensionComponentInterfaceModifier::OnReceiveImpl - is not supported");
}
void SetOnErrorImpl(Ark_NativePointer node,
                    const Opt_ErrorCallback_Ohos_Base_BusinessError* value)
{
    LOGE("UIExtensionComponentInterfaceModifier::OnErrorImpl - is not supported");
}
void SetOnTerminatedImpl(Ark_NativePointer node,
                         const Opt_Callback_TerminationInfo_Void* value)
{
    LOGE("UIExtensionComponentInterfaceModifier::OnTerminatedImpl - is not supported");
}
void SetOnDrawReadyImpl(Ark_NativePointer node,
                        const Opt_Callback_Void* value)
{
    LOGE("UIExtensionComponentInterfaceModifier::OnDrawReadyImpl - is not supported");
}
} // UIExtensionComponentAttributeModifier
const GENERATED_ArkUIUIExtensionComponentModifier* GetUIExtensionComponentModifier()
{
    static const GENERATED_ArkUIUIExtensionComponentModifier ArkUIUIExtensionComponentModifierImpl {
        UIExtensionComponentModifier::ConstructImpl,
        UIExtensionComponentInterfaceModifier::SetUIExtensionComponentOptionsImpl,
        UIExtensionComponentAttributeModifier::SetOnRemoteReadyImpl,
        UIExtensionComponentAttributeModifier::SetOnReceiveImpl,
        UIExtensionComponentAttributeModifier::SetOnErrorImpl,
        UIExtensionComponentAttributeModifier::SetOnTerminatedImpl,
        UIExtensionComponentAttributeModifier::SetOnDrawReadyImpl,
    };
    return &ArkUIUIExtensionComponentModifierImpl;
}

}
