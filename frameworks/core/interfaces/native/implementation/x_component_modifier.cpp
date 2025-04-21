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
#endif // XCOMPONENT_SUPPORTED
#include "core/interfaces/native/implementation/x_component_controller_peer_impl.h"
#include "core/interfaces/native/utility/callback_helper.h"


namespace OHOS::Ace::NG {
namespace {
#ifdef XCOMPONENT_SUPPORTED
XComponentType ConvertToXComponentType(const std::string& type)
{
    if (type == "surface") {
        return XComponentType::SURFACE;
    }
    if (type == "component") {
        return XComponentType::COMPONENT;
    }
    if (type == "node") {
        return XComponentType::NODE;
    }
    return XComponentType::SURFACE;
}
#endif // XCOMPONENT_SUPPORTED
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace XComponentModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
#ifdef XCOMPONENT_SUPPORTED
    auto frameNode = XComponentModelNG::CreateFrameNode(id, std::nullopt, XComponentType::SURFACE, std::nullopt);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
#else
    return {};
#endif //XCOMPONENT_SUPPORTED
}
} // XComponentModifier
namespace XComponentInterfaceModifier {
void SetXComponentOptions0Impl(Ark_NativePointer node,
                               const Ark_Type_XComponentInterface_callable0_value* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
#ifdef XCOMPONENT_SUPPORTED
    auto id = Converter::Convert<std::string>(value->id);
    XComponentModelNG::SetXComponentId(frameNode, id);

    LOGE("XComponentInterfaceModifier::SetXComponentOptions0Impl - wrong input type");
    auto typeStr = Converter::Convert<std::string>(value->type);
    XComponentModelNG::SetXComponentType(frameNode, ConvertToXComponentType(typeStr));

    auto libraryName = Converter::OptConvert<std::string>(value->libraryname);
    // XComponentModelNG::SetXComponentLibraryname(frameNode, libraryName);

    auto controllerOpt = Converter::OptConvert<Ark_XComponentController>(value->controller);
    std::shared_ptr<InnerXComponentController> controller = nullptr;
    if (controller) {
        auto peerImpl = reinterpret_cast<XComponentControllerPeerImpl*>(controllerOpt.value());
        controller = peerImpl->controller;
    }
    // XComponentModelNG::SetXComponentController(frameNode, controller);
#endif // XCOMPONENT_SUPPORTED
}
void SetXComponentOptions1Impl(Ark_NativePointer node,
                               const Ark_Type_XComponentInterface_callable1_value* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

#ifdef XCOMPONENT_SUPPORTED
    auto id = Converter::Convert<std::string>(value->id);
    XComponentModelNG::SetXComponentId(frameNode, id);

    auto type = Converter::OptConvert<XComponentType>(value->type);
    XComponentModelNG::SetXComponentType(frameNode, type.value_or(XComponentType::UNKNOWN));

    auto libraryName = Converter::OptConvert<std::string>(value->libraryname);
    // XComponentModelNG::SetXComponentLibraryname(frameNode, libraryName);

    auto controllerOpt = Converter::OptConvert<Ark_XComponentController>(value->controller);
    std::shared_ptr<InnerXComponentController> controller = nullptr;
    if (controller) {
        auto peerImpl = reinterpret_cast<XComponentControllerPeerImpl*>(controllerOpt.value());
        controller = peerImpl->controller;
    }
    // XComponentModelNG::SetXComponentController(frameNode, controller);
#endif // XCOMPONENT_SUPPORTED
}
void SetXComponentOptions2Impl(Ark_NativePointer node,
                               const Ark_XComponentOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
#ifdef XCOMPONENT_SUPPORTED

    auto type = Converter::OptConvert<XComponentType>(options->type);
    XComponentModelNG::SetXComponentType(frameNode, type.value_or(XComponentType::UNKNOWN));

    LOGE("XComponentInterfaceModifier::SetXComponentOptions2Impl - Ark_ImageAIOptions is not supported");
    XComponentModelNG::SetImageAIOptions(frameNode, nullptr);

    auto peerImpl = reinterpret_cast<XComponentControllerPeerImpl*>(options->controller);
    XComponentModelNG::SetXComponentController(frameNode, peerImpl->controller);
    XComponentModelNG::SetControllerOnCreated(frameNode, peerImpl->GetOnSurfaceCreatedEvent());
    XComponentModelNG::SetControllerOnChanged(frameNode, peerImpl->GetOnSurfaceChangedEvent());
    XComponentModelNG::SetControllerOnDestroyed(frameNode, peerImpl->GetOnSurfaceDestroyedEvent());
#endif // XCOMPONENT_SUPPORTED
}
void SetXComponentOptions3Impl(Ark_NativePointer node,
    const Ark_NativeXComponentParameters* params)
{
}
} // XComponentInterfaceModifier
namespace XComponentAttributeModifier {
void OnLoadImpl(Ark_NativePointer node,
                const Opt_OnNativeLoadCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    CHECK_EQUAL_VOID(value->tag, InteropTag::INTEROP_TAG_UNDEFINED);
    LOGE("XComponentInterfaceModifier::OnLoadImpl - Ark_CustomObject is not supported");
}
void OnDestroyImpl(Ark_NativePointer node,
                   const Opt_VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    CHECK_EQUAL_VOID(value->tag, InteropTag::INTEROP_TAG_UNDEFINED);
    auto onDestroy =
        [arkCallback = CallbackHelper(value->value)](const std::string& xcomponentId) {
            arkCallback.InvokeSync();
        };
#ifdef XCOMPONENT_SUPPORTED
    XComponentModelNG::SetOnDestroy(frameNode, std::move(onDestroy));
#endif // XCOMPONENT_SUPPORTED
}
void EnableAnalyzerImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    CHECK_EQUAL_VOID(value->tag, InteropTag::INTEROP_TAG_UNDEFINED);
    auto convValue = Converter::Convert<bool>(value->value);
#ifdef XCOMPONENT_SUPPORTED
    XComponentModelNG::EnableAnalyzer(frameNode, convValue);
#endif // XCOMPONENT_SUPPORTED
}
void EnableSecureImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    CHECK_EQUAL_VOID(value->tag, InteropTag::INTEROP_TAG_UNDEFINED);
    auto convValue = Converter::Convert<bool>(value->value);
#ifdef XCOMPONENT_SUPPORTED
    XComponentModelNG::EnableSecure(frameNode, convValue);
#endif // XCOMPONENT_SUPPORTED
}
void HdrBrightnessImpl(Ark_NativePointer node,
                       const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
#ifdef XCOMPONENT_SUPPORTED
        XComponentModelNG::HdrBrightness(frameNode, 1.0f);
#endif // XCOMPONENT_SUPPORTED
    }
    float hdrBrightnessValue = std::clamp(Converter::Convert<float>(value->value), 0.0f, 1.0f);
#ifdef XCOMPONENT_SUPPORTED
    XComponentModelNG::HdrBrightness(frameNode, hdrBrightnessValue);
#endif // XCOMPONENT_SUPPORTED
}
void EnableTransparentLayerImpl(Ark_NativePointer node,
                                const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    CHECK_EQUAL_VOID(value->tag, InteropTag::INTEROP_TAG_UNDEFINED);
    auto convValue = Converter::Convert<bool>(value->value);
#ifdef XCOMPONENT_SUPPORTED
    XComponentModelNG::EnableTransparentLayer(frameNode, convValue);
#endif // XCOMPONENT_SUPPORTED
}
} // XComponentAttributeModifier
const GENERATED_ArkUIXComponentModifier* GetXComponentModifier()
{
    static const GENERATED_ArkUIXComponentModifier ArkUIXComponentModifierImpl {
        XComponentModifier::ConstructImpl,
        XComponentInterfaceModifier::SetXComponentOptions0Impl,
        XComponentInterfaceModifier::SetXComponentOptions1Impl,
        XComponentInterfaceModifier::SetXComponentOptions2Impl,
        XComponentInterfaceModifier::SetXComponentOptions3Impl,
        XComponentAttributeModifier::OnLoadImpl,
        XComponentAttributeModifier::OnDestroyImpl,
        XComponentAttributeModifier::EnableAnalyzerImpl,
        XComponentAttributeModifier::EnableSecureImpl,
        XComponentAttributeModifier::HdrBrightnessImpl,
        XComponentAttributeModifier::EnableTransparentLayerImpl,
    };
    return &ArkUIXComponentModifierImpl;
}

}
