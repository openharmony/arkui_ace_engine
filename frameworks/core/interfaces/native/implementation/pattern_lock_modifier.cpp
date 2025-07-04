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
namespace PatternLockModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // PatternLockModifier
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
void SetSideLengthImpl(Ark_NativePointer node,
                       const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Dimension>(*value);
    PatternLockModelStatic::SetSideLength(frameNode, convValue);
}
void SetCircleRadiusImpl(Ark_NativePointer node,
                         const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //PatternLockModelNG::SetSetCircleRadius(frameNode, convValue);
}
void SetBackgroundColorImpl(Ark_NativePointer node,
                            const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //PatternLockModelNG::SetSetBackgroundColor(frameNode, convValue);
}
void SetRegularColorImpl(Ark_NativePointer node,
                         const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //PatternLockModelNG::SetSetRegularColor(frameNode, convValue);
}
void SetSelectedColorImpl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //PatternLockModelNG::SetSetSelectedColor(frameNode, convValue);
}
void SetActiveColorImpl(Ark_NativePointer node,
                        const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //PatternLockModelNG::SetSetActiveColor(frameNode, convValue);
}
void SetPathColorImpl(Ark_NativePointer node,
                      const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //PatternLockModelNG::SetSetPathColor(frameNode, convValue);
}
void SetPathStrokeWidthImpl(Ark_NativePointer node,
                            const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //PatternLockModelNG::SetSetPathStrokeWidth(frameNode, convValue);
}
void SetOnPatternCompleteImpl(Ark_NativePointer node,
                              const Opt_Callback_Array_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //PatternLockModelNG::SetSetOnPatternComplete(frameNode, convValue);
}
void SetAutoResetImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //PatternLockModelNG::SetSetAutoReset(frameNode, convValue);
}
void SetOnDotConnectImpl(Ark_NativePointer node,
                         const Opt_Callback_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //PatternLockModelNG::SetSetOnDotConnect(frameNode, convValue);
}
void SetActivateCircleStyleImpl(Ark_NativePointer node,
                                const Opt_CircleStyleOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //PatternLockModelNG::SetSetActivateCircleStyle(frameNode, convValue);
}
void SetSkipUnselectedPointImpl(Ark_NativePointer node,
                                const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //PatternLockModelNG::SetSetSkipUnselectedPoint(frameNode, convValue);
}
} // PatternLockAttributeModifier
const GENERATED_ArkUIPatternLockModifier* GetPatternLockModifier()
{
    static const GENERATED_ArkUIPatternLockModifier ArkUIPatternLockModifierImpl {
        PatternLockModifier::ConstructImpl,
        PatternLockInterfaceModifier::SetPatternLockOptionsImpl,
        PatternLockAttributeModifier::SetSideLengthImpl,
        PatternLockAttributeModifier::SetCircleRadiusImpl,
        PatternLockAttributeModifier::SetBackgroundColorImpl,
        PatternLockAttributeModifier::SetRegularColorImpl,
        PatternLockAttributeModifier::SetSelectedColorImpl,
        PatternLockAttributeModifier::SetActiveColorImpl,
        PatternLockAttributeModifier::SetPathColorImpl,
        PatternLockAttributeModifier::SetPathStrokeWidthImpl,
        PatternLockAttributeModifier::SetOnPatternCompleteImpl,
        PatternLockAttributeModifier::SetAutoResetImpl,
        PatternLockAttributeModifier::SetOnDotConnectImpl,
        PatternLockAttributeModifier::SetActivateCircleStyleImpl,
        PatternLockAttributeModifier::SetSkipUnselectedPointImpl,
    };
    return &ArkUIPatternLockModifierImpl;
}

}
