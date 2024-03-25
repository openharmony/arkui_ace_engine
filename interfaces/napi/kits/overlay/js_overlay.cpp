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

#include "interfaces/napi/kits/utils/napi_utils.h"
#include "napi/native_api.h"
#include "native_value.h"
#include "napi/native_node_api.h"

#include "bridge/common/utils/engine_helper.h"
#include "bridge/js_frontend/engine/common/js_engine.h"

namespace OHOS::Ace::Napi {
static NG::FrameNode* ParseFrameNode(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    void* data = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, &argv, &thisVar, &data));
    NAPI_ASSERT(env, argc == 1, "requires 1 paramter");

    napi_value nodePtr = nullptr;
    NAPI_CALL(env, napi_get_named_property(env, argv, "nodePtr_", &nodePtr));
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, nodePtr, &valueType);
    NG::UINode* uiNode = nullptr;
    if (valueType == napi_external) {
        NAPI_CALL(env, napi_get_value_external(env, nodePtr, (void**)&uiNode));
    }
    CHECK_NULL_RETURN(uiNode, nullptr);
    return reinterpret_cast<NG::FrameNode*>(uiNode);
}

static napi_value JSAddFrameNode(napi_env env, napi_callback_info info)
{
    NG::FrameNode* frameNode = ParseFrameNode(env, info);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        NapiThrow(env, "UI execution context not found.", ERROR_CODE_INTERNAL_ERROR);
        return nullptr;
    }
    delegate->AddFrameNodeToOverlay(AceType::Claim(frameNode));
    return nullptr;
}

static napi_value JSRemoveFrameNode(napi_env env, napi_callback_info info)
{
    NG::FrameNode* frameNode = ParseFrameNode(env, info);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        NapiThrow(env, "UI execution context not found.", ERROR_CODE_INTERNAL_ERROR);
        return nullptr;
    }
    delegate->RemoveFrameNodeOnOverlay(AceType::Claim(frameNode));
    return nullptr;
}

static napi_value JSShowNode(napi_env env, napi_callback_info info)
{
    NG::FrameNode* frameNode = ParseFrameNode(env, info);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        NapiThrow(env, "UI execution context not found.", ERROR_CODE_INTERNAL_ERROR);
        return nullptr;
    }
    delegate->ShowNodeOnOverlay(AceType::Claim(frameNode));
    return nullptr;
}

static napi_value JSHideNode(napi_env env, napi_callback_info info)
{
    NG::FrameNode* frameNode = ParseFrameNode(env, info);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        NapiThrow(env, "UI execution context not found.", ERROR_CODE_INTERNAL_ERROR);
        return nullptr;
    }
    delegate->HideNodeOnOverlay(AceType::Claim(frameNode));
    return nullptr;
}

static napi_value JSShow(napi_env env, napi_callback_info info)
{
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        NapiThrow(env, "UI execution context not found.", ERROR_CODE_INTERNAL_ERROR);
        return nullptr;
    }
    delegate->ShowAllNodesOnOverlay();
    return nullptr;
}

static napi_value JSHide(napi_env env, napi_callback_info info)
{
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        NapiThrow(env, "UI execution context not found.", ERROR_CODE_INTERNAL_ERROR);
        return nullptr;
    }
    delegate->HideAllNodesOnOverlay();
    return nullptr;
}

static napi_value OverlayExport(napi_env env, napi_value exports)
{
    napi_property_descriptor overlayDesc[] = {
        DECLARE_NAPI_FUNCTION("addFrameNode", JSAddFrameNode),
        DECLARE_NAPI_FUNCTION("removeFrameNode", JSRemoveFrameNode),
        DECLARE_NAPI_FUNCTION("showNode", JSShowNode),
        DECLARE_NAPI_FUNCTION("hideNode", JSHideNode),
        DECLARE_NAPI_FUNCTION("show", JSShow),
        DECLARE_NAPI_FUNCTION("hide", JSHide)
    };
    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(overlayDesc) / sizeof(overlayDesc[0]), overlayDesc));
    return exports;
}

static napi_module overlayModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = OverlayExport,
    .nm_modname = "overlay",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void OverlayRegister()
{
    napi_module_register(&overlayModule);
}
} // namespace OHOS::Ace::Napi
