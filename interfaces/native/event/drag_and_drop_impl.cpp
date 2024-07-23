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
#include "interfaces/native/drag_and_drop.h"
#include "interfaces/native/node/event_converter.h"
#include "interfaces/native/node/node_model.h"
#include "native_node.h"
#include "native_type.h"
#include "ndk_data_conversion.h"
#include "pixelmap_native_impl.h"
#include "securec.h"

#include "base/error/error_code.h"
#include "base/log/log_wrapper.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/core/common/ace_engine.h"
#include "frameworks/core/common/container.h"
#include "frameworks/core/interfaces/native/node/node_api.h"

#ifdef __cplusplus
extern "C" {
#endif

int32_t OH_ArkUI_DragEvent_GetModifierKeyStates(ArkUI_DragEvent* event, int64_t* keys)
{
    if (event == NULL || keys == NULL) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    auto dragEvent = reinterpret_cast<ArkUIDragEvent*>(event);
    *keys = dragEvent->modifierKeyState;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_DragEvent_SetData(ArkUI_DragEvent* event, OH_UdmfData* data)
{
    auto dragEvent = reinterpret_cast<ArkUIDragEvent*>(event);

    if (!event || !data || !dragEvent) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    dragEvent->unifiedData = data;

    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_DragEvent_GetUdmfData(ArkUI_DragEvent* event, OH_UdmfData* data)
{
    auto dragEvent = reinterpret_cast<ArkUIDragEvent*>(event);

    if (!event || !(dragEvent->unifiedData) || !data) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    auto unifiedData =
        std::make_shared<OHOS::UDMF::UnifiedData>(*reinterpret_cast<OHOS::UDMF::UnifiedData*>(dragEvent->unifiedData));

    auto status = OHOS::UDMF::NdkDataConversion::GetNdkUnifiedData(unifiedData, data);
    if (status) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_DragEvent_GetDataTypeCount(ArkUI_DragEvent* event, int32_t* count)
{
    auto dragEvent = reinterpret_cast<ArkUIDragEvent*>(event);

    if (!event || !count || !dragEvent) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    *count = dragEvent->dataTypesCount;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_DragEvent_GetDataTypes(
    ArkUI_DragEvent* event, char* eventTypeArray[], int32_t length, int32_t maxStrLen)
{
    auto dragEvent = reinterpret_cast<ArkUIDragEvent*>(event);
    if (!event || !eventTypeArray || !dragEvent) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }

    if (length < dragEvent->dataTypesCount || maxStrLen < dragEvent->dataTypesMaxStrLength) {
        return ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR;
    }
    for (int32_t i = 0; i < length; i++) {
        if (dragEvent->dataTypes[i]) {
            auto ret = strncpy_s(eventTypeArray[i], maxStrLen, dragEvent->dataTypes[i], maxStrLen);
            if (ret != 0) {
                return ARKUI_ERROR_CODE_PARAM_INVALID;
            }
            eventTypeArray[i][maxStrLen] = '\0';
        } else {
            eventTypeArray[i][0] = '\0';
        }
    }
    return ARKUI_ERROR_CODE_NO_ERROR;
}

#ifdef __cplusplus
};
#endif