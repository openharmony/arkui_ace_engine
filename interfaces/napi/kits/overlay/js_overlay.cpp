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

#include "bridge/common/utils/engine_helper.h"
#include "core/components_ng/pattern/overlay/level_order.h"

namespace OHOS::Ace::Napi {
static NG::FrameNode* ParseFrameNode(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv[2] = { nullptr };
    napi_value thisVar = nullptr;
    void* data = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVar, &data));
    NAPI_ASSERT(env, argc >= 1, "wrong number of argument\n");

    napi_value nodePtr = nullptr;
    NAPI_CALL(env, napi_get_named_property(env, argv[0], "nodePtr_", &nodePtr));
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
    size_t argc = 2;
    napi_value argv[2] = { nullptr };
    napi_value thisVar = nullptr;
    void* data = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVar, &data));
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        NapiThrow(env, "UI execution context not found.", ERROR_CODE_INTERNAL_ERROR);
        return nullptr;
    }
    if (argc == 1) {
        delegate->AddFrameNodeToOverlay(AceType::Claim(frameNode));
    } else {
        napi_valuetype valueType = napi_undefined;
        napi_typeof(env, argv[1], &valueType);
        if (valueType == napi_number) {
            int32_t index = 0;
            napi_get_value_int32(env, argv[1], &index);
            delegate->AddFrameNodeToOverlay(AceType::Claim(frameNode), index);
        } else {
            NapiThrow(env, "the second paramter is not number.", ERROR_CODE_PARAM_INVALID);
            return nullptr;
        }
    }
    return nullptr;
}

static std::optional<double> ParseLevelOrder(napi_env env, napi_value value)
{
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, value, &valueType);
    if (valueType != napi_object) {
        return std::nullopt;
    }

    NG::LevelOrder* levelOrder = nullptr;
    napi_status status = napi_unwrap(env, value, reinterpret_cast<void**>(&levelOrder));
    if (status != napi_ok || !levelOrder) {
        return std::nullopt;
    }

    double order = levelOrder->GetOrder();
    return std::make_optional(order);
}

static napi_value JSAddFrameNodeWithOrder(napi_env env, napi_callback_info info)
{
    NG::FrameNode* frameNode = ParseFrameNode(env, info);
    CHECK_NULL_RETURN(frameNode, nullptr);

    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        return nullptr;
    }

    size_t argc = 2;
    napi_value argv[2] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr));
    std::optional<double> levelOrder = std::nullopt;
    if (argc > 1) {
        levelOrder = ParseLevelOrder(env, argv[1]);
    }

    delegate->AddFrameNodeWithOrder(AceType::Claim(frameNode), levelOrder);
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

static napi_value JSShowAllFrameNodes(napi_env env, napi_callback_info info)
{
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        NapiThrow(env, "UI execution context not found.", ERROR_CODE_INTERNAL_ERROR);
        return nullptr;
    }
    delegate->ShowAllNodesOnOverlay();
    return nullptr;
}

static napi_value JSHideAllFrameNodes(napi_env env, napi_callback_info info)
{
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        NapiThrow(env, "UI execution context not found.", ERROR_CODE_INTERNAL_ERROR);
        return nullptr;
    }
    delegate->HideAllNodesOnOverlay();
    return nullptr;
}

static napi_value JSSetOverlayManagerOptions(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    void* data = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, &argv, &thisVar, &data));
    NAPI_ASSERT(env, argc >= 1, "wrong number of argument\n");

    auto overlayInfo = NG::OverlayManagerInfo { .renderRootOverlay = true };
    napi_value renderRootOverlayNApi = nullptr;
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, argv, &valueType);
    if (valueType == napi_object) {
        napi_get_named_property(env, argv, "renderRootOverlay", &renderRootOverlayNApi);
        napi_get_value_bool(env, renderRootOverlayNApi, &overlayInfo.renderRootOverlay);
    } else if (valueType != napi_undefined && valueType != napi_null) {
        NapiThrow(env, "The type of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }

    napi_value result = nullptr;
    napi_get_boolean(env, false, &result);
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        return result;
    }
    if (delegate->SetOverlayManagerOptions(overlayInfo)) {
        napi_get_boolean(env, true, &result);
        return result;
    }
    return result;
}

static napi_value JSGetOverlayManagerOptions(napi_env env, napi_callback_info info)
{
    napi_value result = nullptr;
    napi_create_object(env, &result);
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        return result;
    }
    std::optional<NG::OverlayManagerInfo> options = delegate->GetOverlayManagerOptions();
    if (options.has_value()) {
        napi_value renderRootOverlay = nullptr;
        napi_get_boolean(env, options.value().renderRootOverlay, &renderRootOverlay);
        napi_set_named_property(env, result, "renderRootOverlay", renderRootOverlay);
    }
    return result;
}

static napi_value OverlayManagerExport(napi_env env, napi_value exports)
{
    napi_property_descriptor overlayManagerDesc[] = {
        DECLARE_NAPI_FUNCTION("addFrameNode", JSAddFrameNode),
        DECLARE_NAPI_FUNCTION("addFrameNodeWithOrder", JSAddFrameNodeWithOrder),
        DECLARE_NAPI_FUNCTION("removeFrameNode", JSRemoveFrameNode),
        DECLARE_NAPI_FUNCTION("showNode", JSShowNode),
        DECLARE_NAPI_FUNCTION("hideNode", JSHideNode),
        DECLARE_NAPI_FUNCTION("showAllFrameNodes", JSShowAllFrameNodes),
        DECLARE_NAPI_FUNCTION("hideAllFrameNodes", JSHideAllFrameNodes),
        DECLARE_NAPI_FUNCTION("setOverlayManagerOptions", JSSetOverlayManagerOptions),
        DECLARE_NAPI_FUNCTION("getOverlayManagerOptions", JSGetOverlayManagerOptions)
    };
    NAPI_CALL(env, napi_define_properties(
        env, exports, sizeof(overlayManagerDesc) / sizeof(overlayManagerDesc[0]), overlayManagerDesc));
    return exports;
}

static napi_module overlayManagerModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = OverlayManagerExport,
    .nm_modname = "overlay",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void OverlayRegister()
{
    napi_module_register(&overlayManagerModule);
}
} // namespace OHOS::Ace::Napi
