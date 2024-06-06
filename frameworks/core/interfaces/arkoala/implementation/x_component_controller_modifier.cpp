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
    namespace XComponentControllerModifier {
        Ark_NativePointer CtorImpl() {
            return 0;
        }
        Ark_NativePointer GetFinalizerImpl() {
            return 0;
        }
        void GetXComponentSurfaceIdImpl(XComponentControllerPeer* peer) {
        }
        Ark_NativePointer GetXComponentContextImpl(XComponentControllerPeer* peer) {
            return 0;
        }
        void SetXComponentSurfaceSizeImpl(XComponentControllerPeer* peer, const Literal_surfaceWidth_Ark_Number_surfaceHeight_Ark_Number* value) {
        }
        void SetXComponentSurfaceRectImpl(XComponentControllerPeer* peer, const SurfaceRect* rect) {
        }
        Ark_NativePointer GetXComponentSurfaceRectImpl(XComponentControllerPeer* peer) {
            return 0;
        }
        void SetXComponentSurfaceRotationImpl(XComponentControllerPeer* peer, const SurfaceRotationOptions* rotationOptions) {
        }
        Ark_NativePointer GetXComponentSurfaceRotationImpl(XComponentControllerPeer* peer) {
            return 0;
        }
        void OnSurfaceCreatedImpl(XComponentControllerPeer* peer, const Ark_String* surfaceId) {
        }
        void OnSurfaceChangedImpl(XComponentControllerPeer* peer, const Ark_String* surfaceId, const SurfaceRect* rect) {
        }
        void OnSurfaceDestroyedImpl(XComponentControllerPeer* peer, const Ark_String* surfaceId) {
        }
        Ark_NativePointer StartImageAnalyzerImpl(XComponentControllerPeer* peer, const ImageAnalyzerConfig* config) {
            return 0;
        }
        void StopImageAnalyzerImpl(XComponentControllerPeer* peer) {
        }
    } // XComponentControllerModifier
    const GENERATED_ArkUIXComponentControllerAccessor* GetXComponentControllerAccessor() {
        static const GENERATED_ArkUIXComponentControllerAccessor XComponentControllerAccessorImpl {
            XComponentControllerModifier::CtorImpl,
            XComponentControllerModifier::GetFinalizerImpl,
            XComponentControllerModifier::GetXComponentSurfaceIdImpl,
            XComponentControllerModifier::GetXComponentContextImpl,
            XComponentControllerModifier::SetXComponentSurfaceSizeImpl,
            XComponentControllerModifier::SetXComponentSurfaceRectImpl,
            XComponentControllerModifier::GetXComponentSurfaceRectImpl,
            XComponentControllerModifier::SetXComponentSurfaceRotationImpl,
            XComponentControllerModifier::GetXComponentSurfaceRotationImpl,
            XComponentControllerModifier::OnSurfaceCreatedImpl,
            XComponentControllerModifier::OnSurfaceChangedImpl,
            XComponentControllerModifier::OnSurfaceDestroyedImpl,
            XComponentControllerModifier::StartImageAnalyzerImpl,
            XComponentControllerModifier::StopImageAnalyzerImpl,
        };
        return &XComponentControllerAccessorImpl;
    }

}
