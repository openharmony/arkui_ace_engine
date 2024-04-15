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
#include "base/log/log_wrapper.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"

extern "C" {

int32_t OH_ArkUI_GetNodeHandleFromNapiValue(napi_env env, napi_value value, ArkUI_NodeHandle* handle)
{
    bool hasProperty = false;
    auto result = napi_has_named_property(env, value, "nodePtr_", &hasProperty);
    if (result == napi_ok && hasProperty) {
        napi_value frameNodePtr = nullptr;
        auto result = napi_get_named_property(env, value, "nodePtr_", &frameNodePtr);
        if (result != napi_ok) {
            LOGE("fail to get nodePtr");
            return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
        }
        // BuilderNode case.
        void* nativePtr = nullptr;
        result = napi_get_value_external(env, frameNodePtr, &nativePtr);
        if (result != napi_ok || nativePtr == nullptr) {
            LOGE("fail to get nodePtr external value");
            return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
        }
        auto* uiNodePtr = reinterpret_cast<OHOS::Ace::NG::UINode*>(nativePtr);
        uiNodePtr->IncRefCount();
        *handle = new ArkUI_Node({ .type = -1, .uiNodeHandle = reinterpret_cast<ArkUINodeHandle>(nativePtr) });
        return OHOS::Ace::ERROR_CODE_NO_ERROR;
    }
    result = napi_has_named_property(env, value, "builderNode_", &hasProperty);
    if (result == napi_ok && hasProperty) {
        // Component Content case.
        napi_value builderNode = nullptr;
        auto result = napi_get_named_property(env, value, "builderNode_", &builderNode);
        if (result != napi_ok) {
            LOGE("fail to get builderNode");
            return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
        }
        napi_value nodePtr = nullptr;
        result = napi_get_named_property(env, builderNode, "nodePtr_", &nodePtr);
        if (result != napi_ok) {
            LOGE("fail to get nodePtr in builderNode");
            return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
        }
        void* nativePtr = nullptr;
        result = napi_get_value_external(env, nodePtr, &nativePtr);
        if (result != napi_ok) {
            LOGE("fail to get nodePtr external value in builderNode");
            return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
        }
        auto* uiNode = reinterpret_cast<OHOS::Ace::NG::UINode*>(nativePtr);
        OHOS::Ace::NG::FrameNode* frameNode = OHOS::Ace::AceType::DynamicCast<OHOS::Ace::NG::FrameNode>(uiNode);
        if (frameNode == nullptr) {
            LOGE("fail to get frameNode value in builderNode");
            return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
        }
        if (frameNode->GetTag() == "BuilderProxyNode") {
            // need to get the really frameNode.
            auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
            if (!impl) {
                return OHOS::Ace::ERROR_CODE_NATIVE_IMPL_LIBRARY_NOT_FOUND;
            }
            auto* child = impl->getNodeModifiers()->getFrameNodeModifier()->getChild(
                reinterpret_cast<ArkUINodeHandle>(frameNode), 0);
            if (!child) {
                LOGE("fail to get child in BuilderProxyNode");
                return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
            }
            frameNode = reinterpret_cast<OHOS::Ace::NG::FrameNode*>(child);
        }
        frameNode->IncRefCount();
        *handle = new ArkUI_Node({ .type = -1, .uiNodeHandle = reinterpret_cast<ArkUINodeHandle>(frameNode) });
        return OHOS::Ace::ERROR_CODE_NO_ERROR;
    }
    return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
}

}
