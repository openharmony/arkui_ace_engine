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
#include "core/components_ng/pattern/form/form_model_ng.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace::NG {
    struct LiteralDimension {
    Dimension width;
    Dimension height;
};
namespace Converter {
template<>
LiteralDimension Convert(const Ark_Literal_Number_height_width& src)
{
    return LiteralDimension {
        .width = Converter::Convert<Dimension>(src.width),
        .height = Converter::Convert<Dimension>(src.height)
    };
}
} // namespace OHOS::Ace::NG::Converter
} // namespace OHOS::Ace::NG
namespace OHOS::Ace::NG::GeneratedModifier {
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
void SizeImpl(Ark_NativePointer node,
              const Ark_Literal_Number_height_width* value)
{
#ifdef FORM_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto dimension = Converter::Convert<LiteralDimension>(*value);
    FormModelNG::SetSize(frameNode, dimension.width, dimension.height);
#endif // FORM_SUPPORTED
}
void ModuleNameImpl(Ark_NativePointer node,
                    const Ark_String* value)
{
#ifdef FORM_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto name = Converter::Convert<std::string>(*value);
    FormModelNG::SetModuleName(frameNode, name);
#endif // FORM_SUPPORTED
}
void DimensionImpl(Ark_NativePointer node,
                   Ark_FormDimension value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //FormComponentModelNG::SetDimension(frameNode, convValue);
}
void AllowUpdateImpl(Ark_NativePointer node,
                     Ark_Boolean value)
{
#ifdef FORM_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    FormModelNG::AllowUpdate(frameNode, convValue);
#endif // FORM_SUPPORTED
}
void VisibilityImpl(Ark_NativePointer node,
                    Ark_Visibility value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //FormComponentModelNG::SetVisibility(frameNode, convValue);
}
void OnAcquiredImpl(Ark_NativePointer node,
                    const Callback_FormCallbackInfo_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //FormComponentModelNG::SetOnAcquired(frameNode, convValue);
}
void OnErrorImpl(Ark_NativePointer node,
                 const Callback_Literal_Number_errcode_String_msg_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //FormComponentModelNG::SetOnError(frameNode, convValue);
}
void OnRouterImpl(Ark_NativePointer node,
                  const Callback_Any_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //FormComponentModelNG::SetOnRouter(frameNode, convValue);
}
void OnUninstallImpl(Ark_NativePointer node,
                     const Callback_FormCallbackInfo_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //FormComponentModelNG::SetOnUninstall(frameNode, convValue);
}
void OnLoadImpl(Ark_NativePointer node,
                const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //FormComponentModelNG::SetOnLoad(frameNode, convValue);
}
} // FormComponentAttributeModifier
const GENERATED_ArkUIFormComponentModifier* GetFormComponentModifier()
{
    static const GENERATED_ArkUIFormComponentModifier ArkUIFormComponentModifierImpl {
        FormComponentInterfaceModifier::SetFormComponentOptionsImpl,
        FormComponentAttributeModifier::SizeImpl,
        FormComponentAttributeModifier::ModuleNameImpl,
        FormComponentAttributeModifier::DimensionImpl,
        FormComponentAttributeModifier::AllowUpdateImpl,
        FormComponentAttributeModifier::VisibilityImpl,
        FormComponentAttributeModifier::OnAcquiredImpl,
        FormComponentAttributeModifier::OnErrorImpl,
        FormComponentAttributeModifier::OnRouterImpl,
        FormComponentAttributeModifier::OnUninstallImpl,
        FormComponentAttributeModifier::OnLoadImpl,
    };
    return &ArkUIFormComponentModifierImpl;
}

}
