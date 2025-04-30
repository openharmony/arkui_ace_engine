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
}
} // PatternLockInterfaceModifier
namespace PatternLockAttributeModifier {
void SideLengthImpl(Ark_NativePointer node,
                    const Opt_Length* value)
{
}
void CircleRadiusImpl(Ark_NativePointer node,
                      const Opt_Length* value)
{
}
void BackgroundColorImpl(Ark_NativePointer node,
                         const Opt_ResourceColor* value)
{
}
void RegularColorImpl(Ark_NativePointer node,
                      const Opt_ResourceColor* value)
{
}
void SelectedColorImpl(Ark_NativePointer node,
                       const Opt_ResourceColor* value)
{
}
void ActiveColorImpl(Ark_NativePointer node,
                     const Opt_ResourceColor* value)
{
}
void PathColorImpl(Ark_NativePointer node,
                   const Opt_ResourceColor* value)
{
}
void PathStrokeWidthImpl(Ark_NativePointer node,
                         const Opt_Union_Number_String* value)
{
}
void OnPatternCompleteImpl(Ark_NativePointer node,
                           const Opt_Callback_Array_Number_Void* value)
{
}
void AutoResetImpl(Ark_NativePointer node,
                   const Opt_Boolean* value)
{
}
void OnDotConnectImpl(Ark_NativePointer node,
                      const Opt_Callback_Number_Void* value)
{
}
void ActivateCircleStyleImpl(Ark_NativePointer node,
                             const Opt_CircleStyleOptions* value)
{
}
void SkipUnselectedPointImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
{
}
} // PatternLockAttributeModifier
const GENERATED_ArkUIPatternLockModifier* GetPatternLockModifier()
{
    static const GENERATED_ArkUIPatternLockModifier ArkUIPatternLockModifierImpl {
        PatternLockModifier::ConstructImpl,
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
        PatternLockAttributeModifier::SkipUnselectedPointImpl,
    };
    return &ArkUIPatternLockModifierImpl;
}

}
