/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CHECKBOXGROUP_BRIDGE_CHECKBOXGROUP_CONTENT_MODIFIER_HELPER_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CHECKBOXGROUP_BRIDGE_CHECKBOXGROUP_CONTENT_MODIFIER_HELPER_H


#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"

typedef struct GENERATED_ArkUICheckboxGroupContentModifier {
    void (*contentModifierCheckboxGroupImpl)(Ark_NativePointer node,
                                    const Ark_Object* contentModifier,
                                    const CheckBoxGroupModifierBuilder* builder);
    void (*resetContentModifierCheckboxGroupImpl)(Ark_NativePointer node);
} GENERATED_ArkUICheckboxGroupContentModifier;

#endif  // FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CHECKBOXGROUP_BRIDGE_CHECKBOXGROUP_CONTENT_MODIFIER_HELPER_H