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

namespace OHOS::Ace::NG::GeneratedModifier {
namespace XComponentModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // XComponentModifier
namespace XComponentInterfaceModifier {
void SetXComponentOptions0Impl(Ark_NativePointer node,
                               const Ark_XComponentParameter* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //XComponentModelNG::SetSetXComponentOptions0(frameNode, convValue);
}
void SetXComponentOptions1Impl(Ark_NativePointer node,
                               const Ark_XComponentOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    //auto convValue = Converter::OptConvert<type_name>(*options);
    //XComponentModelNG::SetSetXComponentOptions1(frameNode, convValue);
}
void SetXComponentOptions2Impl(Ark_NativePointer node,
                               const Ark_NativeXComponentParameters* params)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(params);
    //auto convValue = Converter::OptConvert<type_name>(*params);
    //XComponentModelNG::SetSetXComponentOptions2(frameNode, convValue);
}
} // XComponentInterfaceModifier
namespace XComponentAttributeModifier {
void SetOnLoadImpl(Ark_NativePointer node,
                   const Opt_OnNativeLoadCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //XComponentModelNG::SetSetOnLoad(frameNode, convValue);
}
void SetOnDestroyImpl(Ark_NativePointer node,
                      const Opt_VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //XComponentModelNG::SetSetOnDestroy(frameNode, convValue);
}
void SetEnableAnalyzerImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //XComponentModelNG::SetSetEnableAnalyzer(frameNode, convValue);
}
void SetEnableSecureImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //XComponentModelNG::SetSetEnableSecure(frameNode, convValue);
}
void SetHdrBrightnessImpl(Ark_NativePointer node,
                          const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //XComponentModelNG::SetSetHdrBrightness(frameNode, convValue);
}
void SetEnableTransparentLayerImpl(Ark_NativePointer node,
                                   const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //XComponentModelNG::SetSetEnableTransparentLayer(frameNode, convValue);
}
} // XComponentAttributeModifier
const GENERATED_ArkUIXComponentModifier* GetXComponentModifier()
{
    static const GENERATED_ArkUIXComponentModifier ArkUIXComponentModifierImpl {
        XComponentModifier::ConstructImpl,
        XComponentInterfaceModifier::SetXComponentOptions0Impl,
        XComponentInterfaceModifier::SetXComponentOptions1Impl,
        XComponentInterfaceModifier::SetXComponentOptions2Impl,
        XComponentAttributeModifier::SetOnLoadImpl,
        XComponentAttributeModifier::SetOnDestroyImpl,
        XComponentAttributeModifier::SetEnableAnalyzerImpl,
        XComponentAttributeModifier::SetEnableSecureImpl,
        XComponentAttributeModifier::SetHdrBrightnessImpl,
        XComponentAttributeModifier::SetEnableTransparentLayerImpl,
    };
    return &ArkUIXComponentModifierImpl;
}

}
