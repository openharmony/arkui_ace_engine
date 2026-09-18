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
#include "ui_info_collection.h"

#include "core/interfaces/native/node/page_text_api.h"
#include "interfaces/native/native_error_message_wrapper.h"
#include "interfaces/native/node/node_model.h"

ArkUI_ErrorCode OH_ArkUI_NativeModule_GetPageText(
    ArkUI_ContextHandle uiContext, OH_ArkUI_NativeModule_UIJsonWrapper** pageText)
{
    auto fail = [](ArkUI_ErrorCode code, const char* reason) {
        OHOS::Ace::SetErrorMessageByModifier(code, "OH_ArkUI_NativeModule_GetPageText", reason);
        return code;
    };
    if (!pageText) {
        return fail(ARKUI_ERROR_CODE_PARAM_INVALID, "Page text output slot is null.");
    }
    *pageText = nullptr;
    if (!uiContext) {
        return fail(ARKUI_ERROR_CODE_UI_CONTEXT_INVALID, "UI context is null.");
    }
    const auto* api = OHOS::Ace::NodeModel::GetPageTextAPI();
    if (!api || !api->collect || !api->release) {
        return fail(ARKUI_ERROR_CODE_CAPI_INIT_ERROR, "Page text native support is unavailable.");
    }
    char* data = nullptr;
    uint32_t size = 0;
    const char* reason = "Page text collection failed.";
    auto code = static_cast<ArkUI_ErrorCode>(api->collect(uiContext->id, &data, &size, &reason));
    if (code != ARKUI_ERROR_CODE_NO_ERROR) {
        api->release(data);
        return fail(code, reason);
    }
    code = OH_ArkUI_NativeModule_UIJsonWrapper_Create(data, size, 1, pageText);
    api->release(data);
    if (code != ARKUI_ERROR_CODE_NO_ERROR) {
        return fail(ARKUI_ERROR_CODE_INTERNAL_ERROR, "Page text snapshot allocation failed.");
    }
    return ARKUI_ERROR_CODE_NO_ERROR;
}
