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

#include "native_node_napi.h"

#include <cstdint>

#include "js_native_api.h"
#include "js_native_api_types.h"
#include "native_type.h"
#include "node/node_model.h"

#include "base/error/error_code.h"
#include "core/components_ng/base/ui_node.h"

extern "C" {
int32_t OH_ArkUI_GetNodeHandleFromNapiValue(napi_env env, napi_value frameNode, ArkUI_NodeHandle* handle)
{
    napi_value frameNodePtr = nullptr;
    auto result = napi_get_named_property(env, frameNode, "nodePtr_", &frameNodePtr);
    if (result != napi_ok) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    void* nativePtr = nullptr;
    result = napi_get_value_external(env, frameNodePtr, &nativePtr);
    if (result != napi_ok) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto* uiNodePtr = reinterpret_cast<OHOS::Ace::NG::UINode*>(nativePtr);
    uiNodePtr->IncRefCount();
    *handle = new ArkUI_Node({ .type = -1, .uiNodeHandle = reinterpret_cast<ArkUINodeHandle>(nativePtr) });
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}
}
