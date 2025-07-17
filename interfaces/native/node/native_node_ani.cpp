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

#include "native_node_ani.h"

#include "base/error/error_code.h"
#include "base/log/log.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"
#include "node/node_model.h"

namespace {
int32_t GetFrameNodeFromAniObject(ani_env* env, ani_object frameNodePeerObj, OHOS::Ace::NG::FrameNode ** frameNode)
{
    ani_class pointerClass;
    env->FindClass("Lstd/core/Long;", &pointerClass);
    ani_boolean isPointer;
    ani_status status = env->Object_InstanceOf(frameNodePeerObj, pointerClass, &isPointer);
    if (status != ANI_OK || !isPointer) {
        LOGE("fail to get frameNodePeerObj value in builderNode");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }

    ani_long frameNodePeerPtr;
    status = env->Object_CallMethodByName_Long(frameNodePeerObj, "unboxed", ":J", &frameNodePeerPtr);
    if (status != ANI_OK) {
        LOGE("fail to unbox frameNodePeerObj");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }

    auto* frameNodePeer = reinterpret_cast<FrameNodePeer*>(frameNodePeerPtr);
    if (frameNodePeer == nullptr) {
        LOGE("fail to get frameNodePeer value in builderNode");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    *frameNode = OHOS::Ace::AceType::RawPtr(frameNodePeer->node);
    if (*frameNode == nullptr) {
        auto frameNodePtr = (frameNodePeer->weakNode).Upgrade();
        *frameNode = OHOS::Ace::AceType::RawPtr(frameNodePtr);
    }
    if (*frameNode == nullptr) {
        LOGE("fail to get frameNode value in builderNode");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t GetNodeHandleFromFrameNode(ani_env* env, ani_object frameNodePeerObj, ArkUI_NodeHandle* handle)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    OHOS::Ace::NG::FrameNode* frameNode = nullptr;
    int32_t result = GetFrameNodeFromAniObject(env, frameNodePeerObj, &frameNode);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        return result;
    }
    if (frameNode == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto* uiNodePtr = reinterpret_cast<OHOS::Ace::NG::UINode*>(frameNode);
    uiNodePtr->IncRefCount();
    // check whether it is bind to native XComponent.
    bool isBindNativeXComponent = impl && impl->getNodeModifiers()->getXComponentModifier()
        ->getXComponentIsBindNative(reinterpret_cast<ArkUINodeHandle>(frameNode));
    *handle = new ArkUI_Node({ .type = -1,
        .uiNodeHandle = reinterpret_cast<ArkUINodeHandle>(frameNode),
        .cNode = false,
        .buildNode = true });
    if (isBindNativeXComponent) {
        OHOS::Ace::NodeModel::RegisterBindNativeNode(*handle);
        (*handle)->isBindNative = true;
    }
    if (impl) {
        impl->getExtendedAPI()->setAttachNodePtr((*handle)->uiNodeHandle, reinterpret_cast<void*>(*handle));
    }
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t GetNodeHandleFromBuilderNode(ani_env* env, ani_object builderNode, ArkUI_NodeHandle* handle)
{
    ani_ref frameNodePeerRef;
    if (env->Object_GetFieldByName_Ref(builderNode, "nodePtr_", &frameNodePeerRef) != ANI_OK) {
        LOGE("fail to get nodePtr in builderNode");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    ani_object frameNodePeerObj = static_cast<ani_object>(frameNodePeerRef);
    OHOS::Ace::NG::FrameNode* frameNode = nullptr;
    int32_t result = GetFrameNodeFromAniObject(env, frameNodePeerObj, &frameNode);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        return result;
    }
    if (frameNode == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }

    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (frameNode->GetTag() == "BuilderProxyNode") {
        // need to get the really frameNode.
        if (!impl) {
            return OHOS::Ace::ERROR_CODE_NATIVE_IMPL_LIBRARY_NOT_FOUND;
        }
        auto* child = impl->getNodeModifiers()->getFrameNodeModifier()->getChild(
            reinterpret_cast<ArkUINodeHandle>(frameNode), 0, true);
        if (!child) {
            LOGE("fail to get child in BuilderProxyNode");
            return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
        }
        frameNode = reinterpret_cast<OHOS::Ace::NG::FrameNode*>(child);
    }
    frameNode->IncRefCount();
    *handle = new ArkUI_Node({ .type = -1,
        .uiNodeHandle = reinterpret_cast<ArkUINodeHandle>(frameNode),
        .cNode = false,
        .buildNode = true });
    if (impl) {
        impl->getExtendedAPI()->setAttachNodePtr((*handle)->uiNodeHandle, reinterpret_cast<void*>(*handle));
    }
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}
}

extern "C" {
int32_t OH_ArkUI_NativeModule_GetNodeHandleFromAniValue(ani_env* env, ani_object value, ArkUI_NodeHandle* handle)
{
    if (env == nullptr) {
        LOGE("env is nullptr");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    ani_ref frameNodePeerRef;
    if (env->Object_GetFieldByName_Ref(value, "nodePtr_", &frameNodePeerRef) == ANI_OK) {
        ani_object frameNodePeerObj = static_cast<ani_object>(frameNodePeerRef);
        return GetNodeHandleFromFrameNode(env, frameNodePeerObj, handle);
    }

    ani_ref builderNodeRef;
    if (env->Object_GetFieldByName_Ref(value, "builderNode_", &builderNodeRef) == ANI_OK) {
        // Component Content case.
        ani_object builderNode = static_cast<ani_object>(builderNodeRef);
        return GetNodeHandleFromBuilderNode(env, builderNode, handle);
    }
    return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
}

int32_t OH_ArkUI_NativeModule_GetContextFromAniValue(ani_env* env, ani_object context, ArkUI_ContextHandle* handle)
{
    if (env == nullptr) {
        LOGE("env is nullptr");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    ani_int instanceId = -1;
    if (env->Object_GetFieldByName_Int(context, "instanceId_", &instanceId) != ANI_OK) {
        LOGE("fail to get Context value");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    *handle = new ArkUI_Context({ .id = instanceId });
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}
}