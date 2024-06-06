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
    namespace ProgressMaskModifier {
        Ark_NativePointer CtorImpl(const Ark_Number* value, const Ark_Number* total, const ResourceColor* color) {
            return 0;
        }
        Ark_NativePointer GetFinalizerImpl() {
            return 0;
        }
        void UpdateProgressImpl(ProgressMaskPeer* peer, const Ark_Number* value) {
        }
        void UpdateColorImpl(ProgressMaskPeer* peer, const ResourceColor* value) {
        }
        void EnableBreathingAnimationImpl(ProgressMaskPeer* peer, Ark_Boolean value) {
        }
    } // ProgressMaskModifier
    const GENERATED_ArkUIProgressMaskAccessor* GetProgressMaskAccessor() {
        static const GENERATED_ArkUIProgressMaskAccessor ProgressMaskAccessorImpl {
            ProgressMaskModifier::CtorImpl,
            ProgressMaskModifier::GetFinalizerImpl,
            ProgressMaskModifier::UpdateProgressImpl,
            ProgressMaskModifier::UpdateColorImpl,
            ProgressMaskModifier::EnableBreathingAnimationImpl,
        };
        return &ProgressMaskAccessorImpl;
    }

}
