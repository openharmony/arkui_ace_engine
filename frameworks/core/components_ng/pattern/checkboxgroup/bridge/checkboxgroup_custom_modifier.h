/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CHECKBOX_GROUP_BRIDGE_CHECKBOX_GROUP_CUSTOM_MODIFIER_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CHECKBOX_GROUP_BRIDGE_CHECKBOX_GROUP_CUSTOM_MODIFIER_H
#include "core/interfaces/arkoala/arkoala_api.h"

struct ArkUICheckboxGroupCustomModifier {
    void (*resetCheckboxGroupOnChange)(ArkUINodeHandle node);
    ArkUINodeHandle (*createCheckboxGroupFrameNode)(ArkUI_Uint32 nodeId);
    void (*setCheckboxGroupOnChangeExtraParam)(ArkUINodeHandle node, void* extraParam);
};

#endif // FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CHECKBOX_GROUP_BRIDGE_CHECKBOX_GROUP_CUSTOM_MODIFIER_H
