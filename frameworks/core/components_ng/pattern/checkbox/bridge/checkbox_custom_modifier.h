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

#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CHECKBOX_BRIDGE_CHECKBOX_CUSTOM_MODIFIER_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CHECKBOX_BRIDGE_CHECKBOX_CUSTOM_MODIFIER_H
#include "core/interfaces/arkoala/arkoala_api.h"

struct ArkUICheckboxCustomModifier {
    void (*setSelect)(ArkUINodeHandle node, ArkUI_Bool isSelected);
    void (*setSelectedColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetSelectedColor)(ArkUINodeHandle node);
    void (*setCheckboxOnChange)(ArkUINodeHandle node, void* callback);
    void (*setIsUserSetMargin)(ArkUINodeHandle node, ArkUI_Bool isUserSet);
    ArkUI_Bool (*getSelect)(ArkUINodeHandle node);
    ArkUINodeHandle (*createCheckboxFrameNode)(ArkUI_Uint32 nodeId);
    ArkUINodeHandle (*createToggleCheckboxFrameNode)(ArkUI_Uint32 nodeId);
    void (*setToggleBuilderFunc)(ArkUINodeHandle node, void* callback);
    void (*setChangeValue)(ArkUINodeHandle node, ArkUI_Bool value);
    void (*setSelectedColorFlagByUser)(ArkUINodeHandle node, ArkUI_Bool isByUser);
    void (*setCheckboxChangeEvent)(ArkUINodeHandle node, void* callback);
    ArkUI_Bool (*isToggleCheckboxPattern)(ArkUINodeHandle node);
    ArkUI_Bool (*isCheckboxContentModifierNodeId)(ArkUINodeHandle node, ArkUI_Int32 nodeId);
    void (*updatePaintPropertyBySettingData)(ArkUINodeHandle node, ArkUICheckboxSettingData* data, ArkUI_Bool isLunar);
    void (*setCheckboxOnChangeExtraParam)(ArkUINodeHandle node, void* extraParam);
};

#endif // FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CHECKBOX_BRIDGE_CHECKBOX_CUSTOM_MODIFIER_H
