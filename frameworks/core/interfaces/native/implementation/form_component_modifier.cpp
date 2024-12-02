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
#ifdef FORM_SUPPORTED
#include "core/components_ng/pattern/form/form_model_ng.h"
#endif
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace::NG {
struct LiteralDimension {
    Dimension width;
    Dimension height;
};
namespace {
const auto FORM_DIMENSION_DIMENSION_1_2 = 1;
const auto FORM_DIMENSION_DIMENSION_2_2 = 2;
const auto FORM_DIMENSION_DIMENSION_2_4 = 3;
const auto FORM_DIMENSION_DIMENSION_4_4 = 4;
const auto FORM_DIMENSION_DIMENSION_2_1 = 5;
const auto FORM_DIMENSION_DIMENSION_1_1 = 6;
const auto FORM_DIMENSION_DIMENSION_6_4 = 7;
} // namespace
namespace Converter {
template<>
LiteralDimension Convert(const Ark_Literal_Number_height_width& src)
{
    return LiteralDimension {
        .width = Converter::Convert<Dimension>(src.width),
        .height = Converter::Convert<Dimension>(src.height)
    };
}
template<>
void AssignCast(std::optional<int32_t>& dst, const Ark_FormDimension& src)
{
    switch (src) {
        case ARK_FORM_DIMENSION_DIMENSION_1_2: dst = FORM_DIMENSION_DIMENSION_1_2; break;
        case ARK_FORM_DIMENSION_DIMENSION_2_2: dst = FORM_DIMENSION_DIMENSION_2_2; break;
        case ARK_FORM_DIMENSION_DIMENSION_2_4: dst = FORM_DIMENSION_DIMENSION_2_4; break;
        case ARK_FORM_DIMENSION_DIMENSION_4_4: dst = FORM_DIMENSION_DIMENSION_4_4; break;
        case ARK_FORM_DIMENSION_DIMENSION_2_1: dst = FORM_DIMENSION_DIMENSION_2_1; break;
        case ARK_FORM_DIMENSION_DIMENSION_1_1: dst = FORM_DIMENSION_DIMENSION_1_1; break;
        case ARK_FORM_DIMENSION_DIMENSION_6_4: dst = FORM_DIMENSION_DIMENSION_6_4; break;
        default: LOGE("Unexpected enum value in Ark_FormDimension: %{public}d", src);
    }
}
template<>
void AssignCast(std::optional<VisibleType>& dst, const Ark_Visibility& src)
{
    switch (src) {
        case ARK_VISIBILITY_VISIBLE: dst = VisibleType::VISIBLE; break;
        case ARK_VISIBILITY_HIDDEN: dst = VisibleType::INVISIBLE; break;
        case ARK_VISIBILITY_NONE: dst = VisibleType::GONE; break;
        default: LOGE("Unexpected enum value in Ark_Visibility: %{public}d", src);
    }
}
} // namespace OHOS::Ace::NG::Converter
} // namespace OHOS::Ace::NG
namespace OHOS::Ace::NG::GeneratedModifier {
namespace FormComponentModifier {
Ark_NativePointer ConstructImpl()
{
    return 0;
}
} // FormComponentModifier
namespace FormComponentInterfaceModifier {
void SetFormComponentOptionsImpl(Ark_NativePointer node,
                                 const Ark_FormInfo* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    LOGE("ARKOALA FormComponentInterfaceModifier::SetFormComponentOptionsImpl - CustomObject is not supported "
        "the type Ark_FormInfo::Opt_Want::Opt_Map_String_CustomObject::Ark_CustomObject.");
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
#ifdef FORM_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto opt = Converter::OptConvert<int32_t>(value);
    CHECK_NULL_VOID(opt);
    FormModelNG::SetDimension(frameNode, *opt);
#endif // FORM_SUPPORTED
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
#ifdef FORM_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto opt = Converter::OptConvert<VisibleType>(value);
    CHECK_NULL_VOID(opt);
    FormModelNG::SetVisibility(frameNode, *opt);
#endif // FORM_SUPPORTED
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
        FormComponentModifier::ConstructImpl,
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
