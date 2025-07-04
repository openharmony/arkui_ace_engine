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
namespace FormComponentModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // FormComponentModifier
namespace FormComponentInterfaceModifier {
void SetFormComponentOptionsImpl(Ark_NativePointer node,
                                 const Ark_FormInfo* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //FormComponentModelNG::SetSetFormComponentOptions(frameNode, convValue);
}
} // FormComponentInterfaceModifier
namespace FormComponentAttributeModifier {
void SetSizeImpl(Ark_NativePointer node,
                 const Opt_FormSize* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //FormComponentModelNG::SetSetSize(frameNode, convValue);
}
void SetModuleNameImpl(Ark_NativePointer node,
                       const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //FormComponentModelNG::SetSetModuleName(frameNode, convValue);
}
void SetDimensionImpl(Ark_NativePointer node,
                      const Opt_FormDimension* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //FormComponentModelNG::SetSetDimension(frameNode, convValue);
}
void SetAllowUpdateImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //FormComponentModelNG::SetSetAllowUpdate(frameNode, convValue);
}
void SetVisibilityImpl(Ark_NativePointer node,
                       const Opt_Visibility* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //FormComponentModelNG::SetSetVisibility(frameNode, convValue);
}
void SetOnAcquiredImpl(Ark_NativePointer node,
                       const Opt_Callback_FormCallbackInfo_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //FormComponentModelNG::SetSetOnAcquired(frameNode, convValue);
}
void SetOnErrorImpl(Ark_NativePointer node,
                    const Opt_Callback_FormError_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //FormComponentModelNG::SetSetOnError(frameNode, convValue);
}
void SetOnRouterImpl(Ark_NativePointer node,
                     const Opt_Callback_Union_Object_Undefined_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //FormComponentModelNG::SetSetOnRouter(frameNode, convValue);
}
void SetOnUninstallImpl(Ark_NativePointer node,
                        const Opt_Callback_FormCallbackInfo_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //FormComponentModelNG::SetSetOnUninstall(frameNode, convValue);
}
void SetOnLoadImpl(Ark_NativePointer node,
                   const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //FormComponentModelNG::SetSetOnLoad(frameNode, convValue);
}
} // FormComponentAttributeModifier
const GENERATED_ArkUIFormComponentModifier* GetFormComponentModifier()
{
    static const GENERATED_ArkUIFormComponentModifier ArkUIFormComponentModifierImpl {
        FormComponentModifier::ConstructImpl,
        FormComponentInterfaceModifier::SetFormComponentOptionsImpl,
        FormComponentAttributeModifier::SetSizeImpl,
        FormComponentAttributeModifier::SetModuleNameImpl,
        FormComponentAttributeModifier::SetDimensionImpl,
        FormComponentAttributeModifier::SetAllowUpdateImpl,
        FormComponentAttributeModifier::SetVisibilityImpl,
        FormComponentAttributeModifier::SetOnAcquiredImpl,
        FormComponentAttributeModifier::SetOnErrorImpl,
        FormComponentAttributeModifier::SetOnRouterImpl,
        FormComponentAttributeModifier::SetOnUninstallImpl,
        FormComponentAttributeModifier::SetOnLoadImpl,
    };
    return &ArkUIFormComponentModifierImpl;
}

}
