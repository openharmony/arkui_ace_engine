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
namespace ImageAnimatorInterfaceModifier {
void SetImageAnimatorOptionsImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(undefined);
    //auto convValue = Converter::OptConvert<type>(undefined); // for enums
    //ImageAnimatorModelNG::SetSetImageAnimatorOptions(frameNode, convValue);
}
} // ImageAnimatorInterfaceModifier
namespace ImageAnimatorAttributeModifier {
void ImagesImpl(Ark_NativePointer node,
                const Array_ImageFrameInfo* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ImageAnimatorModelNG::SetImages(frameNode, convValue);
}
void StateImpl(Ark_NativePointer node,
               Ark_AnimationStatus value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //ImageAnimatorModelNG::SetState(frameNode, convValue);
}
void DurationImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ImageAnimatorModelNG::SetDuration(frameNode, convValue);
}
void ReverseImpl(Ark_NativePointer node,
                 Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //ImageAnimatorModelNG::SetReverse(frameNode, convValue);
}
void FixedSizeImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //ImageAnimatorModelNG::SetFixedSize(frameNode, convValue);
}
void PreDecodeImpl(Ark_NativePointer node,
                   const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ImageAnimatorModelNG::SetPreDecode(frameNode, convValue);
}
void FillModeImpl(Ark_NativePointer node,
                  Ark_FillMode value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //ImageAnimatorModelNG::SetFillMode(frameNode, convValue);
}
void IterationsImpl(Ark_NativePointer node,
                    const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ImageAnimatorModelNG::SetIterations(frameNode, convValue);
}
void OnStartImpl(Ark_NativePointer node,
                 const Ark_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ImageAnimatorModelNG::SetOnStart(frameNode, convValue);
}
void OnPauseImpl(Ark_NativePointer node,
                 const Ark_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ImageAnimatorModelNG::SetOnPause(frameNode, convValue);
}
void OnRepeatImpl(Ark_NativePointer node,
                  const Ark_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ImageAnimatorModelNG::SetOnRepeat(frameNode, convValue);
}
void OnCancelImpl(Ark_NativePointer node,
                  const Ark_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ImageAnimatorModelNG::SetOnCancel(frameNode, convValue);
}
void OnFinishImpl(Ark_NativePointer node,
                  const Ark_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ImageAnimatorModelNG::SetOnFinish(frameNode, convValue);
}
} // ImageAnimatorAttributeModifier
const GENERATED_ArkUIImageAnimatorModifier* GetImageAnimatorModifier()
{
    static const GENERATED_ArkUIImageAnimatorModifier ArkUIImageAnimatorModifierImpl {
        ImageAnimatorInterfaceModifier::SetImageAnimatorOptionsImpl,
        ImageAnimatorAttributeModifier::ImagesImpl,
        ImageAnimatorAttributeModifier::StateImpl,
        ImageAnimatorAttributeModifier::DurationImpl,
        ImageAnimatorAttributeModifier::ReverseImpl,
        ImageAnimatorAttributeModifier::FixedSizeImpl,
        ImageAnimatorAttributeModifier::PreDecodeImpl,
        ImageAnimatorAttributeModifier::FillModeImpl,
        ImageAnimatorAttributeModifier::IterationsImpl,
        ImageAnimatorAttributeModifier::OnStartImpl,
        ImageAnimatorAttributeModifier::OnPauseImpl,
        ImageAnimatorAttributeModifier::OnRepeatImpl,
        ImageAnimatorAttributeModifier::OnCancelImpl,
        ImageAnimatorAttributeModifier::OnFinishImpl,
    };
    return &ArkUIImageAnimatorModifierImpl;
}

}
