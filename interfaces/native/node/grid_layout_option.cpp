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
#include "grid_layout_option.h"
#include "native_type.h"
#include "ui/base/utils/utils.h"
#ifdef __cplusplus
extern "C" {
#endif

ArkUI_GridLayoutOptions* OH_ArkUI_GridLayoutOptions_Create()
{
    ArkUI_GridLayoutOptions* gridLayoutOptions = new ArkUI_GridLayoutOptions();
    return gridLayoutOptions;
}

void OH_ArkUI_GridLayoutOptions_Dispose(ArkUI_GridLayoutOptions* option)
{
    if (option != nullptr) {
        delete option;
        option = nullptr;
    }
}

int32_t OH_ArkUI_GridLayoutOptions_SetIrregularIndexes(ArkUI_GridLayoutOptions* option, uint32_t* irregularIndexes,
    int32_t size)
{
    CHECK_NULL_RETURN(option, ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(irregularIndexes, ARKUI_ERROR_CODE_PARAM_INVALID);
    if (size < 0) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    option->irregularIndexes.clear();
    for (int32_t i = 0; i < size; i++) {
        option->irregularIndexes.insert(static_cast<int32_t>(irregularIndexes[i]));
    }
    option->size = size;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_GridLayoutOptions_GetIrregularIndexes(ArkUI_GridLayoutOptions* option,
    uint32_t* irregularIndexes, int32_t* size)
{
    CHECK_NULL_RETURN(option, ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(irregularIndexes, ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(size, ARKUI_ERROR_CODE_PARAM_INVALID);
    if (*size < static_cast<int32_t>(option->irregularIndexes.size())) {
        return ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR;
    }
    int32_t i = 0;
    for (const auto& index : option->irregularIndexes) {
        irregularIndexes[i++] = static_cast<uint32_t>(index);
    }
    *size = static_cast<int32_t>(option->irregularIndexes.size());
    return ARKUI_ERROR_CODE_NO_ERROR;
}

void OH_ArkUI_GridLayoutOptions_RegisterGetIrregularSizeByIndexCallback(
    ArkUI_GridLayoutOptions* option, void* userData, ArkUI_GridItemSize (*callback)(int32_t itemIndex, void* userData))
{
    CHECK_NULL_VOID(option);
    option->onGetIrregularSizeByIndex = reinterpret_cast<void*>(callback);
    option->irregularSizeUserData = userData;
}

void OH_ArkUI_GridLayoutOptions_RegisterGetRectByIndexCallback(
    ArkUI_GridLayoutOptions* option, void* userData, ArkUI_GridItemRect (*callback)(int32_t itemIndex, void* userData))
{
    CHECK_NULL_VOID(option);
    option->onRectByIndexCallback = reinterpret_cast<void*>(callback);
    option->rectByIndexUserData = userData;
}
#ifdef __cplusplus
}
#endif
