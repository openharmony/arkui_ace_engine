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
    namespace WindowSceneInterfaceModifier {
        void _setWindowSceneOptionsImpl(Ark_NativePointer node, const Ark_Number* persistentId) {
        }
    } // WindowSceneInterfaceModifier
    namespace WindowSceneAttributeModifier {
        void AttractionEffectImpl(Ark_NativePointer node, const Position* destination, const Ark_Number* fraction) {
        }
    } // WindowSceneAttributeModifier
    const GENERATED_ArkUIWindowSceneModifier* GetWindowSceneModifier() {
        static const GENERATED_ArkUIWindowSceneModifier ArkUIWindowSceneModifierImpl {
            WindowSceneInterfaceModifier::_setWindowSceneOptionsImpl,
            WindowSceneAttributeModifier::AttractionEffectImpl,
        };
        return &ArkUIWindowSceneModifierImpl;
    }

}
