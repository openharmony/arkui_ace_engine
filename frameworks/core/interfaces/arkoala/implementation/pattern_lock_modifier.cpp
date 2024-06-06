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

#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
    namespace PatternLockInterfaceModifier {
        void _setPatternLockOptionsImpl(Ark_NativePointer node, const Opt_PatternLockController* controller) {
        }
    } // PatternLockInterfaceModifier
    namespace PatternLockAttributeModifier {
        void SideLengthImpl(Ark_NativePointer node, const Ark_Length* value) {
        }
        void CircleRadiusImpl(Ark_NativePointer node, const Ark_Length* value) {
        }
        void BackgroundColorImpl(Ark_NativePointer node, const ResourceColor* value) {
        }
        void RegularColorImpl(Ark_NativePointer node, const ResourceColor* value) {
        }
        void SelectedColorImpl(Ark_NativePointer node, const ResourceColor* value) {
        }
        void ActiveColorImpl(Ark_NativePointer node, const ResourceColor* value) {
        }
        void PathColorImpl(Ark_NativePointer node, const ResourceColor* value) {
        }
        void PathStrokeWidthImpl(Ark_NativePointer node, const Type_PatternLockAttribute_pathStrokeWidth_Arg0* value) {
        }
        void OnPatternCompleteImpl(Ark_NativePointer node, Ark_Function callback) {
        }
        void AutoResetImpl(Ark_NativePointer node, Ark_Boolean value) {
        }
        void OnDotConnectImpl(Ark_NativePointer node, Ark_Function callback) {
        }
        void ActivateCircleStyleImpl(Ark_NativePointer node, const Opt_CircleStyleOptions* options) {
        }
    } // PatternLockAttributeModifier
    const GENERATED_ArkUIPatternLockModifier* GetPatternLockModifier() {
        static const GENERATED_ArkUIPatternLockModifier ArkUIPatternLockModifierImpl {
            PatternLockInterfaceModifier::_setPatternLockOptionsImpl,
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
