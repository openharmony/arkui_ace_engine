/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace XComponentModifier {
Ark_NativePointer ConstructImpl()
{
    return 0;
}
} // XComponentModifier
namespace XComponentInterfaceModifier {
void SetXComponentOptions0Impl(Ark_NativePointer node,
                               const Ark_Type_XComponentInterface_value* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //XComponentModelNG::SetSetXComponentOptions0(frameNode, convValue);
}
void SetXComponentOptions1Impl(Ark_NativePointer node,
                               const Ark_Type_XComponentInterface_value* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //XComponentModelNG::SetSetXComponentOptions1(frameNode, convValue);
}
void SetXComponentOptions2Impl(Ark_NativePointer node,
                               const Ark_XComponentOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    //auto convValue = Converter::OptConvert<type_name>(*options);
    //XComponentModelNG::SetSetXComponentOptions2(frameNode, convValue);
}
} // XComponentInterfaceModifier
namespace XComponentAttributeModifier {
void OnLoadImpl(Ark_NativePointer node,
                const OnNativeLoadCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //XComponentModelNG::SetOnLoad(frameNode, convValue);
}
void OnDestroyImpl(Ark_NativePointer node,
                   const VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //XComponentModelNG::SetOnDestroy(frameNode, convValue);
}
void EnableAnalyzerImpl(Ark_NativePointer node,
                        Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //XComponentModelNG::SetEnableAnalyzer(frameNode, convValue);
}
void EnableSecureImpl(Ark_NativePointer node,
                      Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //XComponentModelNG::SetEnableSecure(frameNode, convValue);
}
} // XComponentAttributeModifier
const GENERATED_ArkUIXComponentModifier* GetXComponentModifier()
{
    static const GENERATED_ArkUIXComponentModifier ArkUIXComponentModifierImpl {
        XComponentModifier::ConstructImpl,
        XComponentInterfaceModifier::SetXComponentOptions0Impl,
        XComponentInterfaceModifier::SetXComponentOptions1Impl,
        XComponentInterfaceModifier::SetXComponentOptions2Impl,
        XComponentAttributeModifier::OnLoadImpl,
        XComponentAttributeModifier::OnDestroyImpl,
        XComponentAttributeModifier::EnableAnalyzerImpl,
        XComponentAttributeModifier::EnableSecureImpl,
    };
    return &ArkUIXComponentModifierImpl;
}

}
