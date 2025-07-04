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
void SetStateImpl(Ark_NativePointer node,
                  const Opt_AnimationStatus* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AnimatorModelNG::SetSetState(frameNode, convValue);
}
void SetDurationImpl(Ark_NativePointer node,
                     const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AnimatorModelNG::SetSetDuration(frameNode, convValue);
}
void SetCurveImpl(Ark_NativePointer node,
                  const Opt_Curve* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AnimatorModelNG::SetSetCurve(frameNode, convValue);
}
void SetDelayImpl(Ark_NativePointer node,
                  const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AnimatorModelNG::SetSetDelay(frameNode, convValue);
}
void SetFillModeImpl(Ark_NativePointer node,
                     const Opt_FillMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AnimatorModelNG::SetSetFillMode(frameNode, convValue);
}
void SetIterationsImpl(Ark_NativePointer node,
                       const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AnimatorModelNG::SetSetIterations(frameNode, convValue);
}
void SetPlayModeImpl(Ark_NativePointer node,
                     const Opt_PlayMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AnimatorModelNG::SetSetPlayMode(frameNode, convValue);
}
void SetMotionImpl(Ark_NativePointer node,
                   const Opt_Union_SpringMotion_FrictionMotion_ScrollMotion* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AnimatorModelNG::SetSetMotion(frameNode, convValue);
}
void SetOnStartImpl(Ark_NativePointer node,
                    const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AnimatorModelNG::SetSetOnStart(frameNode, convValue);
}
void SetOnPauseImpl(Ark_NativePointer node,
                    const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AnimatorModelNG::SetSetOnPause(frameNode, convValue);
}
void SetOnRepeatImpl(Ark_NativePointer node,
                     const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AnimatorModelNG::SetSetOnRepeat(frameNode, convValue);
}
void SetOnCancelImpl(Ark_NativePointer node,
                     const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AnimatorModelNG::SetSetOnCancel(frameNode, convValue);
}
void SetOnFinishImpl(Ark_NativePointer node,
                     const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AnimatorModelNG::SetSetOnFinish(frameNode, convValue);
}
void SetOnFrameImpl(Ark_NativePointer node,
                    const Opt_Callback_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AnimatorModelNG::SetSetOnFrame(frameNode, convValue);
}
} // AnimatorAttributeModifier
const GENERATED_ArkUIAnimatorModifier* GetAnimatorModifier()
{
    static const GENERATED_ArkUIAnimatorModifier ArkUIAnimatorModifierImpl {
        AnimatorModifier::ConstructImpl,
        AnimatorInterfaceModifier::SetAnimatorOptionsImpl,
        AnimatorAttributeModifier::SetStateImpl,
        AnimatorAttributeModifier::SetDurationImpl,
        AnimatorAttributeModifier::SetCurveImpl,
        AnimatorAttributeModifier::SetDelayImpl,
        AnimatorAttributeModifier::SetFillModeImpl,
        AnimatorAttributeModifier::SetIterationsImpl,
        AnimatorAttributeModifier::SetPlayModeImpl,
        AnimatorAttributeModifier::SetMotionImpl,
        AnimatorAttributeModifier::SetOnStartImpl,
        AnimatorAttributeModifier::SetOnPauseImpl,
        AnimatorAttributeModifier::SetOnRepeatImpl,
        AnimatorAttributeModifier::SetOnCancelImpl,
        AnimatorAttributeModifier::SetOnFinishImpl,
        AnimatorAttributeModifier::SetOnFrameImpl,
    };
    return &ArkUIAnimatorModifierImpl;
}

}
