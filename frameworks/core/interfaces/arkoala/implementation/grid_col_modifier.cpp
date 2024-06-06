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
    namespace GridColInterfaceModifier {
        void _setGridColOptionsImpl(Ark_NativePointer node, const Opt_GridColOptions* option) {
        }
    } // GridColInterfaceModifier
    namespace GridColAttributeModifier {
        void SpanImpl(Ark_NativePointer node, const Type_GridColAttribute_span_Arg0* value) {
        }
        void GridColOffsetImpl(Ark_NativePointer node, const Type_GridColAttribute_gridColOffset_Arg0* value) {
        }
        void OrderImpl(Ark_NativePointer node, const Type_GridColAttribute_order_Arg0* value) {
        }
    } // GridColAttributeModifier
    const GENERATED_ArkUIGridColModifier* GetGridColModifier() {
        static const GENERATED_ArkUIGridColModifier ArkUIGridColModifierImpl {
            GridColInterfaceModifier::_setGridColOptionsImpl,
            GridColAttributeModifier::SpanImpl,
            GridColAttributeModifier::GridColOffsetImpl,
            GridColAttributeModifier::OrderImpl,
        };
        return &ArkUIGridColModifierImpl;
    }

}
