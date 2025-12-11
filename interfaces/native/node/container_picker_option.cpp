/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "native_type.h"
#include "ui/base/utils/utils.h"

#include "core/interfaces/arkoala/arkoala_api.h"
#ifdef __cplusplus
extern "C" {
#endif

ArkUI_PickerIndicatorStyle* OH_ArkUI_PickerIndicatorStyle_Create(ArkUI_PickerIndicatorType type)
{
    if (type != ARKUI_PICKER_INDICATOR_BACKGROUND && type != ARKUI_PICKER_INDICATOR_DIVIDER) {
        return nullptr;
    }
    ArkUI_PickerIndicatorStyle* pickerIndicatorStyle = new ArkUI_PickerIndicatorStyle();
    pickerIndicatorStyle->type = static_cast<ArkUI_Uint32>(type);
    return pickerIndicatorStyle;
}

void OH_ArkUI_PickerIndicatorStyle_Dispose(ArkUI_PickerIndicatorStyle* style)
{
    if (style != nullptr) {
        delete style;
        style = nullptr;
    }
}

ArkUI_ErrorCode OH_ArkUI_PickerIndicatorStyle_ConfigureBackground(
    ArkUI_PickerIndicatorStyle* style, ArkUI_PickerIndicatorBackground* background)
{
    CHECK_NULL_RETURN(style, ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(background, ARKUI_ERROR_CODE_PARAM_INVALID);
    if (style->type != static_cast<ArkUI_Uint32>(ARKUI_PICKER_INDICATOR_BACKGROUND)) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    if (background->topLeftRadius < 0 || background->topRightRadius < 0 ||
        background->bottomLeftRadius < 0 || background->bottomRightRadius < 0) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    style->backgroundColor = background->backgroundColor;
    style->topLeftRadius = background->topLeftRadius;
    style->topRightRadius = background->topRightRadius;
    style->bottomLeftRadius = background->bottomLeftRadius;
    style->bottomRightRadius = background->bottomRightRadius;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_PickerIndicatorStyle_ConfigureDivider(
    ArkUI_PickerIndicatorStyle* style, ArkUI_PickerIndicatorDivider* divider)
{
    CHECK_NULL_RETURN(style, ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(divider, ARKUI_ERROR_CODE_PARAM_INVALID);
    if (style->type != static_cast<ArkUI_Uint32>(ARKUI_PICKER_INDICATOR_DIVIDER)) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    if (divider->strokeWidth < 0 || divider->startMargin < 0 || divider->endMargin < 0) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    style->strokeWidth = divider->strokeWidth;
    style->dividerColor = divider->dividerColor;
    style->startMargin = divider->startMargin;
    style->endMargin = divider->endMargin;
    return ARKUI_ERROR_CODE_NO_ERROR;
}
#ifdef __cplusplus
}
#endif
