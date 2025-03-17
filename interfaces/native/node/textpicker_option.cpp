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

#include <cstring>

#include "node_model.h"
#include "securec.h"
#include "style_modifier.h"

#include "base/error/error_code.h"
#include "base/utils/utils.h"
#include "core/interfaces/arkoala/arkoala_api.h"

#ifdef __cplusplus
extern "C" {
#endif

ArkUI_TextPickerRangeContentArray* OH_ArkUI_TextPickerRangeContentArray_Create(int32_t length)
{
    if (length <= 0) {
        return nullptr;
    }
    ArkUI_TextPickerRangeContentArray* array = new ArkUI_TextPickerRangeContentArray;
    array->rangeContent = new RangeContent[length];
    array->rangeContentArraySize = length;
    for (int32_t i = 0; i < length; i++) {
        array->rangeContent[i].icon = nullptr;
        array->rangeContent[i].text = nullptr;
    }
    return array;
}

void OH_ArkUI_TextPickerRangeContentArray_SetIconAtIndex(
    ArkUI_TextPickerRangeContentArray* handle, char* icon, int32_t index)
{
    if (handle == nullptr || index < 0 || index >= handle->rangeContentArraySize || icon == nullptr) {
        return;
    }
    if (handle->rangeContent[index].icon != nullptr) {
        delete[] handle->rangeContent[index].icon;
        handle->rangeContent[index].icon = nullptr;
    }
    uint32_t len = strlen(icon) + 1;
    handle->rangeContent[index].icon = new char[len];
    strcpy_s(const_cast<char*>(handle->rangeContent[index].icon), len, icon);
}

void OH_ArkUI_TextPickerRangeContentArray_SetTextAtIndex(
    ArkUI_TextPickerRangeContentArray* handle, char* text, int32_t index)
{
    if (handle == nullptr || index < 0 || index >= handle->rangeContentArraySize || text == nullptr) {
        return;
    }
    if (handle->rangeContent[index].text != nullptr) {
        delete[] handle->rangeContent[index].text;
        handle->rangeContent[index].text = nullptr;
    }
    uint32_t len = strlen(text) + 1;
    handle->rangeContent[index].text = new char[len];
    strcpy_s(const_cast<char*>(handle->rangeContent[index].text), len, text);
}

void OH_ArkUI_TextPickerRangeContentArray_Destroy(ArkUI_TextPickerRangeContentArray* handle)
{
    if (handle == nullptr) {
        return;
    }
    if (handle->rangeContent->icon != nullptr) {
        delete[] handle->rangeContent->icon;
        handle->rangeContent->icon = nullptr;
    }
    if (handle->rangeContent->text != nullptr) {
        delete[] handle->rangeContent->text;
        handle->rangeContent->text = nullptr;
    }
    if (handle->rangeContent != nullptr) {
        delete[] handle->rangeContent;
        handle->rangeContent = nullptr;
    }
    handle->rangeContentArraySize = 0;
    delete handle;
}
ArkUI_TextCascadePickerRangeContentArray* OH_ArkUI_TextCascadePickerRangeContentArray_Create(int32_t length)
{
    if (length <= 0) {
        return nullptr;
    }
    ArkUI_TextCascadePickerRangeContentArray* handle = new ArkUI_TextCascadePickerRangeContentArray[length];
    for (int32_t i = 0; i < length; i++) {
        handle[i].text = nullptr;
        handle[i].rangeContentArraySize = 0;
        handle[i].children = nullptr;
    }
    handle->rangeContentArraySize = length;
    return handle;
}

void OH_ArkUI_TextCascadePickerRangeContentArray_SetTextAtIndex(
    ArkUI_TextCascadePickerRangeContentArray* handle, char* text, int32_t index)
{
    if (handle == nullptr || index < 0 || index >= handle->rangeContentArraySize || text == nullptr) {
        return;
    }
    if (handle[index].text != nullptr) {
        delete[] handle[index].text;
        handle[index].text = nullptr;
    }
    uint32_t len = strlen(text) + 1;
    handle[index].text = new char[len];
    strcpy_s(const_cast<char*>(handle[index].text), len, text);
}

void OH_ArkUI_TextCascadePickerRangeContentArray_Destroy(ArkUI_TextCascadePickerRangeContentArray* handle)
{
    if (handle == nullptr) {
        return;
    }
    if (handle->children != nullptr) {
        OH_ArkUI_TextCascadePickerRangeContentArray_Destroy(handle->children);
        handle->children = nullptr;
    }
    if (handle->text != nullptr) {
        delete[] handle->text;
        handle->text = nullptr;
    }
    delete[] handle;
}

void OH_ArkUI_TextCascadePickerRangeContentArray_SetChildAtIndex(
    ArkUI_TextCascadePickerRangeContentArray* handle, ArkUI_TextCascadePickerRangeContentArray* child, int32_t index)
{
    if (handle == nullptr || index < 0 || index >= handle->rangeContentArraySize || child == nullptr) {
        return;
    }
    if (handle[index].children != nullptr) {
        OH_ArkUI_TextCascadePickerRangeContentArray_Destroy(handle[index].children);
    }
    handle[index].children = child;
}
#ifdef __cplusplus
};
#endif
