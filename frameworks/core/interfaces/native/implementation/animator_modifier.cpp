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
namespace AnimatorModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // AnimatorModifier
namespace AnimatorInterfaceModifier {
void SetAnimatorOptionsImpl(Ark_NativePointer node,
                            const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<std::string>(*value);
    //AnimatorModelNG::SetSetAnimatorOptions(frameNode, convValue);
}
} // AnimatorInterfaceModifier
namespace AnimatorAttributeModifier {
void StateImpl(Ark_NativePointer node,
               Ark_AnimationStatus value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //AnimatorModelNG::SetState(frameNode, convValue);
}
void DurationImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //AnimatorModelNG::SetDuration(frameNode, convValue);
}
void CurveImpl(Ark_NativePointer node,
               Ark_Curve value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //AnimatorModelNG::SetCurve(frameNode, convValue);
}
void DelayImpl(Ark_NativePointer node,
               const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //AnimatorModelNG::SetDelay(frameNode, convValue);
}
void FillModeImpl(Ark_NativePointer node,
                  Ark_FillMode value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //AnimatorModelNG::SetFillMode(frameNode, convValue);
}
void IterationsImpl(Ark_NativePointer node,
                    const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //AnimatorModelNG::SetIterations(frameNode, convValue);
}
void PlayModeImpl(Ark_NativePointer node,
                  Ark_PlayMode value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //AnimatorModelNG::SetPlayMode(frameNode, convValue);
}
void MotionImpl(Ark_NativePointer node,
                Ark_SpringMotion value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //AnimatorModelNG::SetMotion(frameNode, convValue);
}
void OnStartImpl(Ark_NativePointer node,
                 const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //AnimatorModelNG::SetOnStart(frameNode, convValue);
}
void OnPauseImpl(Ark_NativePointer node,
                 const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //AnimatorModelNG::SetOnPause(frameNode, convValue);
}
void OnRepeatImpl(Ark_NativePointer node,
                  const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //AnimatorModelNG::SetOnRepeat(frameNode, convValue);
}
void OnCancelImpl(Ark_NativePointer node,
                  const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //AnimatorModelNG::SetOnCancel(frameNode, convValue);
}
void OnFinishImpl(Ark_NativePointer node,
                  const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //AnimatorModelNG::SetOnFinish(frameNode, convValue);
}
void OnFrameImpl(Ark_NativePointer node,
                 const Callback_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //AnimatorModelNG::SetOnFrame(frameNode, convValue);
}
} // AnimatorAttributeModifier
const GENERATED_ArkUIAnimatorModifier* GetAnimatorModifier()
{
    static const GENERATED_ArkUIAnimatorModifier ArkUIAnimatorModifierImpl {
        AnimatorModifier::ConstructImpl,
        AnimatorInterfaceModifier::SetAnimatorOptionsImpl,
        AnimatorAttributeModifier::StateImpl,
        AnimatorAttributeModifier::DurationImpl,
        AnimatorAttributeModifier::CurveImpl,
        AnimatorAttributeModifier::DelayImpl,
        AnimatorAttributeModifier::FillModeImpl,
        AnimatorAttributeModifier::IterationsImpl,
        AnimatorAttributeModifier::PlayModeImpl,
        AnimatorAttributeModifier::MotionImpl,
        AnimatorAttributeModifier::OnStartImpl,
        AnimatorAttributeModifier::OnPauseImpl,
        AnimatorAttributeModifier::OnRepeatImpl,
        AnimatorAttributeModifier::OnCancelImpl,
        AnimatorAttributeModifier::OnFinishImpl,
        AnimatorAttributeModifier::OnFrameImpl,
    };
    return &ArkUIAnimatorModifierImpl;
}

}
