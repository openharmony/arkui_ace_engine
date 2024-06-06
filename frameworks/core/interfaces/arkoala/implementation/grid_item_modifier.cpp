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
    namespace GridItemInterfaceModifier {
        void _setGridItemOptionsImpl(Ark_NativePointer node, const Opt_GridItemOptions* value) {
        }
    } // GridItemInterfaceModifier
    namespace GridItemAttributeModifier {
        void RowStartImpl(Ark_NativePointer node, const Ark_Number* value) {
        }
        void RowEndImpl(Ark_NativePointer node, const Ark_Number* value) {
        }
        void ColumnStartImpl(Ark_NativePointer node, const Ark_Number* value) {
        }
        void ColumnEndImpl(Ark_NativePointer node, const Ark_Number* value) {
        }
        void ForceRebuildImpl(Ark_NativePointer node, Ark_Boolean value) {
        }
        void SelectableImpl(Ark_NativePointer node, Ark_Boolean value) {
        }
        void SelectedImpl(Ark_NativePointer node, Ark_Boolean value) {
        }
        void OnSelectImpl(Ark_NativePointer node, Ark_Function event) {
        }
    } // GridItemAttributeModifier
    const GENERATED_ArkUIGridItemModifier* GetGridItemModifier() {
        static const GENERATED_ArkUIGridItemModifier ArkUIGridItemModifierImpl {
            GridItemInterfaceModifier::_setGridItemOptionsImpl,
            GridItemAttributeModifier::RowStartImpl,
            GridItemAttributeModifier::RowEndImpl,
            GridItemAttributeModifier::ColumnStartImpl,
            GridItemAttributeModifier::ColumnEndImpl,
            GridItemAttributeModifier::ForceRebuildImpl,
            GridItemAttributeModifier::SelectableImpl,
            GridItemAttributeModifier::SelectedImpl,
            GridItemAttributeModifier::OnSelectImpl,
        };
        return &ArkUIGridItemModifierImpl;
    }

}
