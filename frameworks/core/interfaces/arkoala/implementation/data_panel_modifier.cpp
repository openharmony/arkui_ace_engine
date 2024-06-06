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
    namespace DataPanelInterfaceModifier {
        void _setDataPanelOptionsImpl(Ark_NativePointer node, const DataPanelOptions* options) {
        }
    } // DataPanelInterfaceModifier
    namespace DataPanelAttributeModifier {
        void CloseEffectImpl(Ark_NativePointer node, Ark_Boolean value) {
        }
        void ValueColorsImpl(Ark_NativePointer node, const Array_Union_ResourceColor_LinearGradient* value) {
        }
        void TrackBackgroundColorImpl(Ark_NativePointer node, const ResourceColor* value) {
        }
        void StrokeWidthImpl(Ark_NativePointer node, const Ark_Length* value) {
        }
        void TrackShadowImpl(Ark_NativePointer node, const DataPanelShadowOptions* value) {
        }
        void ContentModifierImpl(Ark_NativePointer node, const Ark_CustomObject* modifier) {
        }
    } // DataPanelAttributeModifier
    const GENERATED_ArkUIDataPanelModifier* GetDataPanelModifier() {
        static const GENERATED_ArkUIDataPanelModifier ArkUIDataPanelModifierImpl {
            DataPanelInterfaceModifier::_setDataPanelOptionsImpl,
            DataPanelAttributeModifier::CloseEffectImpl,
            DataPanelAttributeModifier::ValueColorsImpl,
            DataPanelAttributeModifier::TrackBackgroundColorImpl,
            DataPanelAttributeModifier::StrokeWidthImpl,
            DataPanelAttributeModifier::TrackShadowImpl,
            DataPanelAttributeModifier::ContentModifierImpl,
        };
        return &ArkUIDataPanelModifierImpl;
    }

}
