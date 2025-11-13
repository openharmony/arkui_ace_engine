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

#include "node/node_extened.h"
#include "node/node_model.h"
#include "node/resource.h"

#include "base/error/error_code.h"
#include "base/log/log.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/syntax/node_content_peer.h"
#include "frameworks/core/interfaces/native/ani/frame_node_peer_impl.h"

namespace {
constexpr char NAV_PATH_STACK_CLASS[] = "arkui.component.navigation.NavPathStack";
constexpr char GET_PARAM_WITH_NAVDESTINATION_ID_METHOD[] = "getParamWithNavDestinationId";

int32_t GetFrameNodeFromAniObject(ani_env* env, ani_object frameNodePeerObj, OHOS::Ace::NG::FrameNode** frameNode)
{
    ani_class pointerClass;
    env->FindClass("std.core.Long", &pointerClass);
    ani_boolean isPointer;
    ani_status status = env->Object_InstanceOf(frameNodePeerObj, pointerClass, &isPointer);
    if (status != ANI_OK || !isPointer) {
        LOGE("fail to get frameNodePeerObj value in builderNode");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }

    ani_long frameNodePeerPtr;
    status = env->Object_CallMethodByName_Long(frameNodePeerObj, "toLong", ":l", &frameNodePeerPtr);
    if (status != ANI_OK) {
        LOGE("fail to unbox frameNodePeerObj");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }

    auto* frameNodePeer = reinterpret_cast<OHOS::Ace::FrameNodePeer*>(frameNodePeerPtr);
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

std::string ANIStringToStdString(ani_env* env, ani_string ani_str)
{
    ani_size sz {};
    env->String_GetUTF8Size(ani_str, &sz);

    std::string result(sz + 1, 0);
    env->String_GetUTF8(ani_str, result.data(), result.size(), &sz);
    result.resize(sz);
    return result;
}

std::string GetPropertyByName(ani_env* env, ani_object value, const char* name)
{
    std::string result;
    ani_ref nameRef;
    if (env->Object_GetPropertyByName_Ref(value, name, &nameRef) != ANI_OK) {
        LOGE("drawable descriptor fail to get name");
    } else {
        result = ANIStringToStdString(env, static_cast<ani_string>(nameRef));
    }
    return result;
}

std::string GetArrayPropertyByNameRef(ani_env* env, ani_object value)
{
    std::string params;
    ani_ref paramsRef;
    if (env->Object_GetPropertyByName_Ref(value, "params", &paramsRef) != ANI_OK) {
        return params;
    }
    ani_boolean isUndefined;
    env->Reference_IsUndefined(paramsRef, &isUndefined);
    if (isUndefined) {
        return params;
    }
    ani_size size = 0;
    ani_status sta = env->Array_GetLength(static_cast<ani_array>(paramsRef), &size);
    if (sta == ANI_OK && size > 0) {
        ani_ref result;
        if (env->Array_Get(static_cast<ani_array>(paramsRef), 0, &result) == ANI_OK) {
            params = ANIStringToStdString(env, static_cast<ani_string>(result));
        }
    }
    return params;
}

} // namespace

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

int32_t OH_ArkUI_NativeModule_GetNodeContentFromAniValue(
    ani_env* env, ani_object nodeContent, ArkUI_NodeContentHandle* content)
{
    if (env == nullptr) {
        LOGE("env is nullptr");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    ani_ref nodeContentPeerRef;
    if (env->Object_GetFieldByName_Ref(nodeContent, "nativePtr_", &nodeContentPeerRef) != ANI_OK) {
        LOGE("fail to get nativePtr_ from nodeContent");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    ani_object nodeContentPeerObj = static_cast<ani_object>(nodeContentPeerRef);
    ani_class pointerClass;
    env->FindClass("std.core.Long", &pointerClass);
    ani_boolean isPointer;
    ani_status status = env->Object_InstanceOf(nodeContentPeerObj, pointerClass, &isPointer);
    if (status != ANI_OK || !isPointer) {
        LOGE("nodeContentPeerObj class is error");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }

    ani_long nodeContentPeerPtr;
    status = env->Object_CallMethodByName_Long(nodeContentPeerObj, "toLong", ":l", &nodeContentPeerPtr);
    if (status != ANI_OK) {
        LOGE("unbox nodeContentPeerObj fail");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }

    auto* nodeContentPeer = reinterpret_cast<OHOS::Ace::NodeContentPeer*>(nodeContentPeerPtr);
    if (nodeContentPeer == nullptr) {
        LOGE("fail to get nodeContentPeer");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    *content = reinterpret_cast<ArkUI_NodeContentHandle>(OHOS::Ace::AceType::RawPtr(nodeContentPeer->content));
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_GetNavDestinationAniParam(ArkUI_NodeHandle node, ani_env* env, ani_value* param)
{
    CHECK_NULL_RETURN(node, ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(env, ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(param, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(fullImpl, ARKUI_ERROR_CODE_GET_INFO_FAILED);
    auto navigationAPI = fullImpl->getNavigation();
    CHECK_NULL_RETURN(navigationAPI, ARKUI_ERROR_CODE_GET_INFO_FAILED);
    char idBuffer[512] = { 0 };
    ArkUI_Int32 idLen = 0;
    auto ret = navigationAPI->getNavDestinationId(node->uiNodeHandle, idBuffer, sizeof(idBuffer), &idLen);
    if (ret != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        LOGE("AceNavigation failed to get NavDestinationId ret:%{public}d", ret);
        return ARKUI_ERROR_CODE_GET_INFO_FAILED;
    }
    LOGI("AceNavigation get navDestinationId:%{public}s", std::string(idBuffer).c_str());
    ani_status status = ANI_OK;
    ani_class cls;
    if ((status = env->FindClass(NAV_PATH_STACK_CLASS, &cls)) != ANI_OK) {
        LOGE("AceNavigation failed to find %{public}s class, status:%{public}d", NAV_PATH_STACK_CLASS, status);
        return ARKUI_ERROR_CODE_GET_INFO_FAILED;
    }
    ani_static_method getParamMethod;
    if ((status = env->Class_FindStaticMethod(cls, GET_PARAM_WITH_NAVDESTINATION_ID_METHOD,
             "C{std.core.String}:C{std.core.Object}", &getParamMethod)) != ANI_OK) {
        LOGE("AceNavigation failed to find %{public}s method, status:%{public}d",
            GET_PARAM_WITH_NAVDESTINATION_ID_METHOD, status);
        return ARKUI_ERROR_CODE_GET_INFO_FAILED;
    }
    ani_string navDestinationIdRef;
    if ((status = env->String_NewUTF8(idBuffer, idLen, &navDestinationIdRef)) != ANI_OK) {
        LOGE("AceNavigation failed to create navDestinationId ani_string, status:%{public}d", status);
        return ARKUI_ERROR_CODE_GET_INFO_FAILED;
    }
    ani_ref paramRef;
    if ((status = env->Class_CallStaticMethod_Ref(cls, getParamMethod, &paramRef, navDestinationIdRef)) != ANI_OK) {
        LOGE("AceNavigation failed to get NavDestination param, status:%{public}d", status);
        return ARKUI_ERROR_CODE_GET_INFO_FAILED;
    }
    param->r = paramRef;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_NativeModule_GetDrawableDescriptorFromAniValue(
    ani_env* env, ani_object value, ArkUI_DrawableDescriptor** drawableDescriptor)
{
    ani_long nativeObj = 0;
    env->Object_GetPropertyByName_Long(value, "nativeObj", &nativeObj);
    if (nativeObj == 0) {
        LOGE("drawable descriptor have not native object");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto* object = reinterpret_cast<void*>(nativeObj);
    if (object == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    ArkUI_DrawableDescriptor* drawable =
        new ArkUI_DrawableDescriptor { nullptr, nullptr, 0, object, nullptr, nullptr, nullptr, nullptr };
    OHOS::Ace::NodeModel::IncreaseRefDrawable(object);
    *drawableDescriptor = drawable;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_NativeModule_GetDrawableDescriptorFromResourceAniValue(
    ani_env* env, ani_object value, ArkUI_DrawableDescriptor** drawableDescriptor)
{
    std::string bundleName = GetPropertyByName(env, value, "bundleName");
    std::string moduleName = GetPropertyByName(env, value, "moduleName");

    ani_long resId = 0;
    if (env->Object_GetPropertyByName_Long(value, "_id", &resId) != ANI_OK) {
        LOGE("drawable descriptor fail to get id ");
    }
    ani_ref typeRef = 0;
    int32_t resType = -1;
    if (env->Object_GetPropertyByName_Ref(value, "type", &typeRef) == ANI_OK) {
        ani_boolean isUndefined;
        env->Reference_IsUndefined(typeRef, &isUndefined);
        if (!isUndefined) {
            ani_int type = -1;
            if (env->Object_CallMethodByName_Int(static_cast<ani_object>(typeRef), "toInt", ":i", &type) == ANI_OK) {
                resType = type;
            }
        }
    }
    std::string param = GetArrayPropertyByNameRef(env, value);

    auto parseStaticApi = reinterpret_cast<void (*)(int32_t, int32_t, const char*, void*)>(
        OHOS::Ace::NodeModel::GetParseStaticResource());
    if (!parseStaticApi) {
        return OHOS::Ace::ERROR_CODE_INTERNAL_ERROR;
    }
    ArkUI_DrawableDescriptor* drawable =
        new ArkUI_DrawableDescriptor { nullptr, nullptr, 0, nullptr, nullptr, nullptr, nullptr };
    drawable->resource = std::make_shared<ArkUI_Resource>();
    drawable->resource->resId = resId;
    drawable->resource->bundleName = bundleName;
    drawable->resource->moduleName = moduleName;
    parseStaticApi(resType, resId, param.c_str(), drawable->resource.get());
    *drawableDescriptor = drawable;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}
}
