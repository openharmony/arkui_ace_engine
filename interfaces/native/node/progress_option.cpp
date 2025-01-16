/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "progress_option.h"

#include "node_model.h"

#include "base/error/error_code.h"
#include "base/utils/utils.h"

#ifdef __cplusplus
extern "C" {
#endif

ArkUI_ProgressLinearStyleOption* OH_ArkUI_ProgressLinearStyleOption_Create(void)
{
    ArkUI_ProgressLinearStyleOption* option = new ArkUI_ProgressLinearStyleOption {
        .scanEffectEnable = false,
        .smoothEffectEnable = true,
        .strokeWidth = 4.0f,
        .strokeRadius = -1.0f
    };
    return option;
}

void OH_ArkUI_ProgressLinearStyleOption_Destroy(ArkUI_ProgressLinearStyleOption* option)
{
    if (option == nullptr) {
        return;
    }
    delete option;
}

void OH_ArkUI_ProgressLinearStyleOption_SetScanEffectEnabled(ArkUI_ProgressLinearStyleOption* option, bool enabled)
{
    if (option == nullptr) {
        return;
    }
    option->scanEffectEnable = enabled;
}

void OH_ArkUI_ProgressLinearStyleOption_SetSmoothEffectEnabled(ArkUI_ProgressLinearStyleOption* option, bool enabled)
{
    if (option == nullptr) {
        return;
    }
    option->smoothEffectEnable = enabled;
}

void OH_ArkUI_ProgressLinearStyleOption_SetStrokeWidth(ArkUI_ProgressLinearStyleOption* option, float strokeWidth)
{
    if (option == nullptr) {
        return;
    }
    option->strokeWidth = strokeWidth;
}

void OH_ArkUI_ProgressLinearStyleOption_SetStrokeRadius(ArkUI_ProgressLinearStyleOption* option, float strokeRadius)
{
    if (option == nullptr) {
        return;
    }
    option->strokeRadius = strokeRadius;
}

bool OH_ArkUI_ProgressLinearStyleOption_GetScanEffectEnabled(ArkUI_ProgressLinearStyleOption* option)
{
    if (option == nullptr) {
        return false;
    }
    return option->scanEffectEnable;
}

bool OH_ArkUI_ProgressLinearStyleOption_GetSmoothEffectEnabled(ArkUI_ProgressLinearStyleOption* option)
{
    if (option == nullptr) {
        return true;
    }
    return option->smoothEffectEnable;
}

float OH_ArkUI_ProgressLinearStyleOption_GetStrokeWidth(ArkUI_ProgressLinearStyleOption* option)
{
    if (option == nullptr) {
        return -1.0f;
    }
    return option->strokeWidth;
}

float OH_ArkUI_ProgressLinearStyleOption_GetStrokeRadius(ArkUI_ProgressLinearStyleOption* option)
{
    if (option == nullptr) {
        return -1.0f;
    }
    return option->strokeRadius;
}

#ifdef __cplusplus
};
#endif
