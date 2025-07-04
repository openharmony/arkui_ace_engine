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
namespace ImageAnimatorModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // ImageAnimatorModifier
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
void SetImagesImpl(Ark_NativePointer node,
                   const Opt_Array_ImageFrameInfo* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageAnimatorModelNG::SetSetImages(frameNode, convValue);
}
void SetStateImpl(Ark_NativePointer node,
                  const Opt_AnimationStatus* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageAnimatorModelNG::SetSetState(frameNode, convValue);
}
void SetDurationImpl(Ark_NativePointer node,
                     const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageAnimatorModelNG::SetSetDuration(frameNode, convValue);
}
void SetReverseImpl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageAnimatorModelNG::SetSetReverse(frameNode, convValue);
}
void SetFixedSizeImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageAnimatorModelNG::SetSetFixedSize(frameNode, convValue);
}
void SetFillModeImpl(Ark_NativePointer node,
                     const Opt_FillMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageAnimatorModelNG::SetSetFillMode(frameNode, convValue);
}
void SetIterationsImpl(Ark_NativePointer node,
                       const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageAnimatorModelNG::SetSetIterations(frameNode, convValue);
}
void SetMonitorInvisibleAreaImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageAnimatorModelNG::SetSetMonitorInvisibleArea(frameNode, convValue);
}
void SetOnStartImpl(Ark_NativePointer node,
                    const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageAnimatorModelNG::SetSetOnStart(frameNode, convValue);
}
void SetOnPauseImpl(Ark_NativePointer node,
                    const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageAnimatorModelNG::SetSetOnPause(frameNode, convValue);
}
void SetOnRepeatImpl(Ark_NativePointer node,
                     const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageAnimatorModelNG::SetSetOnRepeat(frameNode, convValue);
}
void SetOnCancelImpl(Ark_NativePointer node,
                     const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageAnimatorModelNG::SetSetOnCancel(frameNode, convValue);
}
void SetOnFinishImpl(Ark_NativePointer node,
                     const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ImageAnimatorModelNG::SetSetOnFinish(frameNode, convValue);
}
} // ImageAnimatorAttributeModifier
const GENERATED_ArkUIImageAnimatorModifier* GetImageAnimatorModifier()
{
    static const GENERATED_ArkUIImageAnimatorModifier ArkUIImageAnimatorModifierImpl {
        ImageAnimatorModifier::ConstructImpl,
        ImageAnimatorInterfaceModifier::SetImageAnimatorOptionsImpl,
        ImageAnimatorAttributeModifier::SetImagesImpl,
        ImageAnimatorAttributeModifier::SetStateImpl,
        ImageAnimatorAttributeModifier::SetDurationImpl,
        ImageAnimatorAttributeModifier::SetReverseImpl,
        ImageAnimatorAttributeModifier::SetFixedSizeImpl,
        ImageAnimatorAttributeModifier::SetFillModeImpl,
        ImageAnimatorAttributeModifier::SetIterationsImpl,
        ImageAnimatorAttributeModifier::SetMonitorInvisibleAreaImpl,
        ImageAnimatorAttributeModifier::SetOnStartImpl,
        ImageAnimatorAttributeModifier::SetOnPauseImpl,
        ImageAnimatorAttributeModifier::SetOnRepeatImpl,
        ImageAnimatorAttributeModifier::SetOnCancelImpl,
        ImageAnimatorAttributeModifier::SetOnFinishImpl,
    };
    return &ArkUIImageAnimatorModifierImpl;
}

}
