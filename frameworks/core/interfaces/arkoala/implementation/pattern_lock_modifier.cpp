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
namespace PatternLockInterfaceModifier {
void SetPatternLockOptionsImpl(Ark_NativePointer node,
                               const Opt_PatternLockController* controller)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = controller ? Converter::OptConvert<type>(*controller) : std::nullopt;
    //PatternLockModelNG::SetSetPatternLockOptions(frameNode, convValue);
}
} // PatternLockInterfaceModifier
namespace PatternLockAttributeModifier {
void SideLengthImpl(Ark_NativePointer node,
                    const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //PatternLockModelNG::SetSideLength(frameNode, convValue);
}
void CircleRadiusImpl(Ark_NativePointer node,
                      const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //PatternLockModelNG::SetCircleRadius(frameNode, convValue);
}
void BackgroundColorImpl(Ark_NativePointer node,
                         const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //PatternLockModelNG::SetBackgroundColor(frameNode, convValue);
}
void RegularColorImpl(Ark_NativePointer node,
                      const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //PatternLockModelNG::SetRegularColor(frameNode, convValue);
}
void SelectedColorImpl(Ark_NativePointer node,
                       const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //PatternLockModelNG::SetSelectedColor(frameNode, convValue);
}
void ActiveColorImpl(Ark_NativePointer node,
                     const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //PatternLockModelNG::SetActiveColor(frameNode, convValue);
}
void PathColorImpl(Ark_NativePointer node,
                   const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //PatternLockModelNG::SetPathColor(frameNode, convValue);
}
void PathStrokeWidthImpl(Ark_NativePointer node,
                         const Ark_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //PatternLockModelNG::SetPathStrokeWidth(frameNode, convValue);
}
void OnPatternCompleteImpl(Ark_NativePointer node,
                           const Ark_Callback_Array_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //PatternLockModelNG::SetOnPatternComplete(frameNode, convValue);
}
void AutoResetImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //PatternLockModelNG::SetAutoReset(frameNode, convValue);
}
void OnDotConnectImpl(Ark_NativePointer node,
                      const Ark_Callback_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //PatternLockModelNG::SetOnDotConnect(frameNode, convValue);
}
void ActivateCircleStyleImpl(Ark_NativePointer node,
                             const Ark_Union_CircleStyleOptions_Undefined* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //PatternLockModelNG::SetActivateCircleStyle(frameNode, convValue);
}
} // PatternLockAttributeModifier
const GENERATED_ArkUIPatternLockModifier* GetPatternLockModifier()
{
    static const GENERATED_ArkUIPatternLockModifier ArkUIPatternLockModifierImpl {
        PatternLockInterfaceModifier::SetPatternLockOptionsImpl,
        PatternLockAttributeModifier::SideLengthImpl,
        PatternLockAttributeModifier::CircleRadiusImpl,
        PatternLockAttributeModifier::BackgroundColorImpl,
        PatternLockAttributeModifier::RegularColorImpl,
        PatternLockAttributeModifier::SelectedColorImpl,
        PatternLockAttributeModifier::ActiveColorImpl,
        PatternLockAttributeModifier::PathColorImpl,
        PatternLockAttributeModifier::PathStrokeWidthImpl,
        PatternLockAttributeModifier::OnPatternCompleteImpl,
        PatternLockAttributeModifier::AutoResetImpl,
        PatternLockAttributeModifier::OnDotConnectImpl,
        PatternLockAttributeModifier::ActivateCircleStyleImpl,
    };
    return &ArkUIPatternLockModifierImpl;
}

}
