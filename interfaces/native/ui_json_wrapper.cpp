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
#include "ui_json_wrapper.h"

#include <cstdlib>
#include <limits>
#include <new>

#include "securec.h"

struct OH_ArkUI_NativeModule_UIJsonWrapper {
    char* data;
    uint32_t size;
};

ArkUI_ErrorCode OH_ArkUI_NativeModule_UIJsonWrapperCreate(const char* data, uint32_t size,
    OH_ArkUI_NativeModule_UIJsonWrapper** outOwned)
{
    if (!outOwned) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    *outOwned = nullptr;
    if (!data) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    const size_t dataSize = static_cast<size_t>(size);
    if (dataSize == std::numeric_limits<size_t>::max()) {
        return ARKUI_ERROR_CODE_INTERNAL_ERROR;
    }
    const size_t bufferSize = dataSize + 1;
    auto* wrapper = new (std::nothrow) OH_ArkUI_NativeModule_UIJsonWrapper;
    if (!wrapper) {
        return ARKUI_ERROR_CODE_INTERNAL_ERROR;
    }
    wrapper->data = static_cast<char*>(std::malloc(bufferSize));
    if (!wrapper->data) {
        delete wrapper;
        return ARKUI_ERROR_CODE_INTERNAL_ERROR;
    }
    if (memcpy_s(wrapper->data, bufferSize, data, dataSize) != EOK) {
        std::free(wrapper->data);
        delete wrapper;
        return ARKUI_ERROR_CODE_INTERNAL_ERROR;
    }
    wrapper->data[dataSize] = '\0';
    wrapper->size = size;
    *outOwned = wrapper;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

const char* OH_ArkUI_NativeModule_UIJsonWrapperGetData(const OH_ArkUI_NativeModule_UIJsonWrapper* wrapper)
{
    return wrapper ? wrapper->data : nullptr;
}

uint32_t OH_ArkUI_NativeModule_UIJsonWrapperGetSize(const OH_ArkUI_NativeModule_UIJsonWrapper* wrapper)
{
    return wrapper ? wrapper->size : 0;
}

void OH_ArkUI_NativeModule_UIJsonWrapperDestroy(OH_ArkUI_NativeModule_UIJsonWrapper* wrapper)
{
    if (wrapper) {
        std::free(wrapper->data);
        delete wrapper;
    }
}
