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
    namespace ListItemGroupInterfaceModifier {
        void _setListItemGroupOptionsImpl(Ark_NativePointer node, const Opt_ListItemGroupOptions* options) {
        }
    } // ListItemGroupInterfaceModifier
    namespace ListItemGroupAttributeModifier {
        void DividerImpl(Ark_NativePointer node, const Type_ListItemGroupAttribute_divider_Arg0* value) {
        }
        void ChildrenMainSizeImpl(Ark_NativePointer node, const Ark_Materialized* value) {
        }
    } // ListItemGroupAttributeModifier
    const GENERATED_ArkUIListItemGroupModifier* GetListItemGroupModifier() {
        static const GENERATED_ArkUIListItemGroupModifier ArkUIListItemGroupModifierImpl {
            ListItemGroupInterfaceModifier::_setListItemGroupOptionsImpl,
            ListItemGroupAttributeModifier::DividerImpl,
            ListItemGroupAttributeModifier::ChildrenMainSizeImpl,
        };
        return &ArkUIListItemGroupModifierImpl;
    }

}
