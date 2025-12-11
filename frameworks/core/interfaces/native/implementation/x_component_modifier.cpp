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
#include "arkoala_api_generated.h"

#include "core/components/common/layout/constants.h"
#ifdef XCOMPONENT_SUPPORTED
#include "core/components_ng/pattern/xcomponent/xcomponent_model_ng.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_model_static.h"
#endif // XCOMPONENT_SUPPORTED
#include "core/interfaces/native/implementation/x_component_controller_peer_impl.h"
#include "core/interfaces/native/utility/callback_helper.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace {
#ifdef XCOMPONENT_SUPPORTED
XComponentType ConvertXComponentType(Ark_XComponentType type)
{
    return type == Ark_XComponentType::ARK_XCOMPONENT_TYPE_TEXTURE ? XComponentType::TEXTURE : XComponentType::SURFACE;
}
#endif // XCOMPONENT_SUPPORTED
}
namespace XComponentModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
#ifdef XCOMPONENT_SUPPORTED
    auto frameNode = XComponentModelStatic::CreateFrameNode(id, false);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
#else
    return {};
#endif //XCOMPONENT_SUPPORTED
}
} // XComponentModifier
namespace XComponentInterfaceModifier {
void SetXComponentOptionsImpl(Ark_NativePointer node,
                              const Ark_Union_XComponentParameters_XComponentOptions_NativeXComponentParameters* params)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(params);
#ifdef XCOMPONENT_SUPPORTED
    Converter::VisitUnion(*params,
        [frameNode](const Ark_XComponentParameters& src) {
            std::string xComponentId = Converter::Convert<std::string>(src.id);
            XComponentModelStatic::SetXComponentId(frameNode, xComponentId);
            XComponentType type = ConvertXComponentType(src.type);
            XComponentModelStatic::SetXComponentType(frameNode, type);
            auto handler = [arkCallback = CallbackHelper(src.nativeXComponentHandler)](void* ptr) {
                arkCallback.InvokeSync(reinterpret_cast<Ark_Int64>(ptr));
            };
            XComponentModelStatic::SetNativeXComponentHandler(frameNode, handler);
            if (src.controller.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
                auto peerImpl = reinterpret_cast<XComponentControllerPeerImpl*>(src.controller.value);
                CHECK_NULL_VOID(peerImpl);
                XComponentModelStatic::SetXComponentController(frameNode, peerImpl->controller);
            }
            XComponentModelStatic::InitParams(frameNode);
        },
        [frameNode](const Ark_XComponentOptions& src) {
            XComponentType type = ConvertXComponentType(src.type);
            XComponentModelStatic::SetXComponentType(frameNode, type);
            auto peerImpl = reinterpret_cast<XComponentControllerPeerImpl*>(src.controller);
            CHECK_NULL_VOID(peerImpl);
            bool isUpdated = XComponentModelStatic::SetXComponentController(frameNode, peerImpl->controller);
            CHECK_EQUAL_VOID(isUpdated, false);
            XComponentModelNG::SetControllerOnCreated(frameNode, std::move(peerImpl->onSurfaceCreatedEvent));
            XComponentModelNG::SetControllerOnChanged(frameNode, std::move(peerImpl->onSurfaceChangedEvent));
            XComponentModelNG::SetControllerOnDestroyed(frameNode, std::move(peerImpl->onSurfaceDestroyedEvent));
            XComponentModelStatic::InitParams(frameNode);
            CHECK_EQUAL_VOID(src.screenId.tag, InteropTag::INTEROP_TAG_UNDEFINED);
            XComponentModelStatic::SetScreenId(frameNode, static_cast<uint64_t>(src.screenId.value));
        },
        [frameNode](const Ark_NativeXComponentParameters& src) {
            XComponentType type = ConvertXComponentType(src.type);
            XComponentModelStatic::SetXComponentType(frameNode, type);
            XComponentModelStatic::MarkBindNative(frameNode);
            XComponentModelStatic::InitParams(frameNode);
        },
        []() {});
#endif
}
} // XComponentInterfaceModifier
namespace XComponentAttributeModifier {
void SetOnLoadImpl(Ark_NativePointer node,
                   const Opt_VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
#ifdef XCOMPONENT_SUPPORTED
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        XComponentModelNG::SetOnLoad(frameNode, nullptr);
        return;
    }
    auto onLoad =
        [arkCallback = CallbackHelper(*optValue)](const std::string& xcomponentId) {
            CHECK_NULL_VOID(CallbackHelper<VoidCallback>::GetVMContext());
            arkCallback.InvokeSync();
            TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "XComponent[%{public}s] onLoad triggers", xcomponentId.c_str());
    };
    XComponentModelNG::SetOnLoad(frameNode, std::move(onLoad));
#endif // XCOMPONENT_SUPPORTED
}
void SetOnDestroyImpl(Ark_NativePointer node,
                      const Opt_VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
#ifdef XCOMPONENT_SUPPORTED
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        XComponentModelNG::SetOnDestroy(frameNode, nullptr);
        return;
    }
    auto onDestroy =
        [arkCallback = CallbackHelper(*optValue)](const std::string&) {
            CHECK_NULL_VOID(CallbackHelper<VoidCallback>::GetVMContext());
            arkCallback.InvokeSync();
    };
    XComponentModelNG::SetOnDestroy(frameNode, std::move(onDestroy));
#endif // XCOMPONENT_SUPPORTED
}
void SetEnableAnalyzerImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
#ifdef XCOMPONENT_SUPPORTED
    auto convValue = Converter::OptConvertPtr<bool>(value);
    XComponentModelNG::EnableAnalyzer(frameNode, convValue.value_or(false));
#endif // XCOMPONENT_SUPPORTED
}
void SetEnableSecureImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
#ifdef XCOMPONENT_SUPPORTED
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        XComponentModelNG::EnableSecure(frameNode, false);
        return;
    }
    XComponentModelNG::EnableSecure(frameNode, *convValue);
#endif // XCOMPONENT_SUPPORTED
}
void SetHdrBrightnessImpl(Ark_NativePointer node,
                          const Opt_Float64* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    #ifdef XCOMPONENT_SUPPORTED
    auto convValue = Converter::OptConvertPtr<float>(value);
    if (!convValue) {
        XComponentModelNG::HdrBrightness(frameNode, 1.0f);
        return;
    }
    XComponentModelNG::HdrBrightness(frameNode, *convValue);
    #endif // XCOMPONENT_SUPPORTED
}
void SetEnableTransparentLayerImpl(Ark_NativePointer node,
                                   const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    #ifdef XCOMPONENT_SUPPORTED
    auto convValue = Converter::OptConvertPtr<bool>(value);
    XComponentModelNG::EnableTransparentLayer(frameNode, convValue.value_or(false));
    #endif // XCOMPONENT_SUPPORTED
}
} // XComponentAttributeModifier
const GENERATED_ArkUIXComponentModifier* GetXComponentModifier()
{
    static const GENERATED_ArkUIXComponentModifier ArkUIXComponentModifierImpl {
        XComponentModifier::ConstructImpl,
        XComponentInterfaceModifier::SetXComponentOptionsImpl,
        XComponentAttributeModifier::SetOnLoadImpl,
        XComponentAttributeModifier::SetOnDestroyImpl,
        XComponentAttributeModifier::SetEnableAnalyzerImpl,
        XComponentAttributeModifier::SetEnableSecureImpl,
        XComponentAttributeModifier::SetEnableTransparentLayerImpl,
        XComponentAttributeModifier::SetHdrBrightnessImpl,
    };
    return &ArkUIXComponentModifierImpl;
}

}
