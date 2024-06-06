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
    namespace CanvasInterfaceModifier {
        void _setCanvasOptions_CanvasRenderingContextDDrawingRenderingContextImpl(Ark_NativePointer node, const Opt_Type_CanvasInterface__setCanvasOptions_Arg0* context) {
        }
        void _setCanvasOptions_CanvasRenderingContextDDrawingRenderingContext_ImageAIOptionsImpl(Ark_NativePointer node, const Type_CanvasInterface__setCanvasOptions1_Arg0* context, const ImageAIOptions* imageAIOptions) {
        }
    } // CanvasInterfaceModifier
    namespace CanvasAttributeModifier {
        void OnReadyImpl(Ark_NativePointer node, Ark_Function event) {
        }
        void EnableAnalyzerImpl(Ark_NativePointer node, Ark_Boolean enable) {
        }
    } // CanvasAttributeModifier
    const GENERATED_ArkUICanvasModifier* GetCanvasModifier() {
        static const GENERATED_ArkUICanvasModifier ArkUICanvasModifierImpl {
            CanvasInterfaceModifier::_setCanvasOptions_CanvasRenderingContextDDrawingRenderingContextImpl,
            CanvasInterfaceModifier::_setCanvasOptions_CanvasRenderingContextDDrawingRenderingContext_ImageAIOptionsImpl,
            CanvasAttributeModifier::OnReadyImpl,
            CanvasAttributeModifier::EnableAnalyzerImpl,
        };
        return &ArkUICanvasModifierImpl;
    }

}
