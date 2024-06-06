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
    namespace CanvasRenderingContext2DModifier {
        Ark_NativePointer CtorImpl(const Opt_RenderingContextSettings* settings) {
            return 0;
        }
        Ark_NativePointer GetFinalizerImpl() {
            return 0;
        }
        void ToDataURLImpl(CanvasRenderingContext2DPeer* peer, const Opt_Ark_String* type, const Opt_Ark_CustomObject* quality) {
        }
        Ark_NativePointer StartImageAnalyzerImpl(CanvasRenderingContext2DPeer* peer, const ImageAnalyzerConfig* config) {
            return 0;
        }
        void StopImageAnalyzerImpl(CanvasRenderingContext2DPeer* peer) {
        }
    } // CanvasRenderingContext2DModifier
    const GENERATED_ArkUICanvasRenderingContext2DAccessor* GetCanvasRenderingContext2DAccessor() {
        static const GENERATED_ArkUICanvasRenderingContext2DAccessor CanvasRenderingContext2DAccessorImpl {
            CanvasRenderingContext2DModifier::CtorImpl,
            CanvasRenderingContext2DModifier::GetFinalizerImpl,
            CanvasRenderingContext2DModifier::ToDataURLImpl,
            CanvasRenderingContext2DModifier::StartImageAnalyzerImpl,
            CanvasRenderingContext2DModifier::StopImageAnalyzerImpl,
        };
        return &CanvasRenderingContext2DAccessorImpl;
    }

}
