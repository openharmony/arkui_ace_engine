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


#include "node/node_extened.h"
#include "node/node_model.h"

#include "base/error/error_code.h"
#include "core/components_ng/base/frame_node.h"

extern "C" {

int32_t OH_ArkUI_GetNodeHandleFromNapiValue(napi_env env, napi_value value, ArkUI_NodeHandle* handle)
{
    bool hasProperty = false;
    auto result = napi_has_named_property(env, value, "nodePtr_", &hasProperty);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
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
        // check whether it is bind to native XComponent.
        bool isBindNativeXComponent = impl && impl->getNodeModifiers()->getXComponentModifier()
            ->getXComponentIsBindNative(reinterpret_cast<ArkUINodeHandle>(nativePtr));
        *handle = new ArkUI_Node({ .type = -1,
            .uiNodeHandle = reinterpret_cast<ArkUINodeHandle>(nativePtr),
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
    return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
}

int32_t OH_ArkUI_GetContextFromNapiValue(napi_env env, napi_value value, ArkUI_ContextHandle* context)
{
    bool hasProperty = false;
    auto result = napi_has_named_property(env, value, "instanceId_", &hasProperty);
    if (result != napi_ok || !hasProperty) {
        LOGE("fail to get Context value");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }

    napi_value contextPtr = nullptr;
    result = napi_get_named_property(env, value, "instanceId_", &contextPtr);
    if (result != napi_ok) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }

    napi_valuetype valuetype;
    if (napi_typeof(env, contextPtr, &valuetype) != napi_ok) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (valuetype != napi_number) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    int32_t instanceId = -1;
    result = napi_get_value_int32(env, contextPtr, &instanceId);
    if (result != napi_ok) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    *context = new ArkUI_Context({ .id = instanceId });
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_GetNodeContentFromNapiValue(napi_env env, napi_value value, ArkUI_NodeContentHandle* content)
{
    bool hasProperty = false;
    auto result = napi_has_named_property(env, value, "nativePtr_", &hasProperty);
    if (result != napi_ok || !hasProperty) {
        LOGE("fail to get native content value");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    napi_value nativeContent = nullptr;
    result = napi_get_named_property(env, value, "nativePtr_", &nativeContent);
    if (result != napi_ok) {
        LOGE("fail to get native content");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    void* nativePtr = nullptr;
    result = napi_get_value_external(env, nativeContent, &nativePtr);
    if (result != napi_ok) {
        LOGE("fail to get native content ptr");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    *content = reinterpret_cast<ArkUI_NodeContentHandle>(nativePtr);
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_GetDrawableDescriptorFromNapiValue(
    napi_env env, napi_value value, ArkUI_DrawableDescriptor** drawableDescriptor)
{
    void* objectNapi = nullptr;
    napi_unwrap(env, value, &objectNapi);
    if (!objectNapi) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    ArkUI_DrawableDescriptor* drawable =
        new ArkUI_DrawableDescriptor { nullptr, nullptr, 0, nullptr, nullptr, nullptr, nullptr };
    auto* descriptor = reinterpret_cast<OHOS::Ace::Napi::DrawableDescriptor*>(objectNapi);
    if (!descriptor) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto drawableType = descriptor->GetDrawableType();
    if (drawableType == OHOS::Ace::Napi::DrawableDescriptor::DrawableType::ANIMATED) {
        auto* animatedDrawable = static_cast<OHOS::Ace::Napi::AnimatedDrawableDescriptor*>(descriptor);
        if (!animatedDrawable) {
            return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
        }
        int32_t duration = animatedDrawable->GetDuration();
        int32_t iteration = animatedDrawable->GetIterations();
        drawable->animatedDrawableDescriptor = std::make_shared<OHOS::Ace::Napi::AnimatedDrawableDescriptor>(
            animatedDrawable->GetPixelMapList(), duration, iteration);
        *drawableDescriptor = drawable;
        return OHOS::Ace::ERROR_CODE_NO_ERROR;
    }
    drawable->drawableDescriptor = std::make_shared<OHOS::Ace::Napi::DrawableDescriptor>(descriptor->GetPixelMap());
    *drawableDescriptor = drawable;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_GetDrawableDescriptorFromResourceNapiValue(
    napi_env env, napi_value value, ArkUI_DrawableDescriptor** drawableDescriptor)
{
    auto parseApi = reinterpret_cast<void (*)(void*, void*)>(OHOS::Ace::NodeModel::GetParseJsMedia());
    if (!parseApi) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }

    ArkUI_DrawableDescriptor* drawable =
        new ArkUI_DrawableDescriptor { nullptr, nullptr, 0, nullptr, nullptr, nullptr, nullptr };
    drawable->resource = std::make_shared<ArkUI_Resource>();
    parseApi(value, drawable->resource.get());
    *drawableDescriptor = drawable;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode  OH_ArkUI_GetNavigationId(
    ArkUI_NodeHandle node, char* buffer, int32_t bufferSize, int32_t* writeLength)
{
    CHECK_NULL_RETURN(node, ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(buffer, ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(writeLength, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(fullImpl, ARKUI_ERROR_CODE_GET_INFO_FAILED);
    auto navigationAPI = fullImpl->getNavigation();
    CHECK_NULL_RETURN(navigationAPI, ARKUI_ERROR_CODE_GET_INFO_FAILED);
    auto ret =
        navigationAPI->getNavigationId(node->uiNodeHandle, buffer, bufferSize, writeLength);
    return static_cast<ArkUI_ErrorCode>(ret);
}

ArkUI_ErrorCode OH_ArkUI_GetNavDestinationName(
    ArkUI_NodeHandle node, char* buffer, int32_t bufferSize, int32_t* writeLength)
{
    CHECK_NULL_RETURN(node, ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(buffer, ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(writeLength, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(fullImpl, ARKUI_ERROR_CODE_GET_INFO_FAILED);
    auto navigationAPI = fullImpl->getNavigation();
    CHECK_NULL_RETURN(navigationAPI, ARKUI_ERROR_CODE_GET_INFO_FAILED);
    auto ret =
        navigationAPI->getNavDestinationName(node->uiNodeHandle, buffer, bufferSize, writeLength);
    return static_cast<ArkUI_ErrorCode>(ret);
}

ArkUI_ErrorCode OH_ArkUI_GetNavStackLength(ArkUI_NodeHandle node, int32_t* length)
{
    CHECK_NULL_RETURN(node, ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(length, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    auto stacklength = fullImpl->getNavigation()->getStackLength(node->uiNodeHandle);
    if (stacklength < 0) {
        return ARKUI_ERROR_CODE_GET_INFO_FAILED;
    }
    *length = stacklength;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_GetNavDestinationNameByIndex(
    ArkUI_NodeHandle node, int32_t index, char* buffer, int32_t bufferSize, int32_t* writeLength)
{
    CHECK_NULL_RETURN(node, ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(buffer, ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(writeLength, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(fullImpl, ARKUI_ERROR_CODE_GET_INFO_FAILED);
    auto navigationAPI = fullImpl->getNavigation();
    CHECK_NULL_RETURN(navigationAPI, ARKUI_ERROR_CODE_GET_INFO_FAILED);
    auto ret =
        navigationAPI->getNavDesNameByIndex(node->uiNodeHandle, index, buffer, bufferSize, writeLength);
    return static_cast<ArkUI_ErrorCode>(ret);
}

ArkUI_ErrorCode OH_ArkUI_GetNavDestinationId(
    ArkUI_NodeHandle node, char* buffer, int32_t bufferSize, int32_t* writeLength)
{
    CHECK_NULL_RETURN(node, ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(buffer, ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(writeLength, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(fullImpl, ARKUI_ERROR_CODE_GET_INFO_FAILED);
    auto navigationAPI = fullImpl->getNavigation();
    CHECK_NULL_RETURN(navigationAPI, ARKUI_ERROR_CODE_GET_INFO_FAILED);
    auto ret =
        navigationAPI->getNavDestinationId(node->uiNodeHandle, buffer, bufferSize, writeLength);
    return static_cast<ArkUI_ErrorCode>(ret);
}

ArkUI_ErrorCode OH_ArkUI_GetNavDestinationState(ArkUI_NodeHandle node, ArkUI_NavDestinationState* state)
{
    CHECK_NULL_RETURN(node, ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(state, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(fullImpl, ARKUI_ERROR_CODE_GET_INFO_FAILED);
    auto navigationAPI = fullImpl->getNavigation();
    CHECK_NULL_RETURN(navigationAPI, ARKUI_ERROR_CODE_GET_INFO_FAILED);

    auto navDestinationState = navigationAPI->getNavDestinationState(node->uiNodeHandle);
    if (navDestinationState < 0) {
        return ARKUI_ERROR_CODE_GET_INFO_FAILED;
    }
    *state = static_cast<ArkUI_NavDestinationState>(navDestinationState);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_GetNavDestinationIndex(ArkUI_NodeHandle node, int32_t* index)
{
    CHECK_NULL_RETURN(node, ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(index, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(fullImpl, ARKUI_ERROR_CODE_GET_INFO_FAILED);
    auto navigationAPI = fullImpl->getNavigation();
    CHECK_NULL_RETURN(navigationAPI, ARKUI_ERROR_CODE_GET_INFO_FAILED);

    auto retIndex = navigationAPI->getNavDestinationIndex(node->uiNodeHandle);
    if (retIndex < 0) {
        return ARKUI_ERROR_CODE_GET_INFO_FAILED;
    }
    *index = retIndex;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

napi_value OH_ArkUI_GetNavDestinationParam(ArkUI_NodeHandle node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(fullImpl, nullptr);
    auto navigationAPI = fullImpl->getNavigation();
    CHECK_NULL_RETURN(navigationAPI, nullptr);
    return reinterpret_cast<napi_value>(navigationAPI->getNavDestinationParam(node->uiNodeHandle));
}

ArkUI_ErrorCode OH_ArkUI_GetRouterPageIndex(ArkUI_NodeHandle node, int32_t* index)
{
    CHECK_NULL_RETURN(node, ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(index, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(fullImpl, ARKUI_ERROR_CODE_GET_INFO_FAILED);
    auto navigationAPI = fullImpl->getNavigation();
    CHECK_NULL_RETURN(navigationAPI, ARKUI_ERROR_CODE_GET_INFO_FAILED);

    auto retIndex = navigationAPI->getRouterPageIndex(node->uiNodeHandle);
    if (retIndex < 0) {
        return ARKUI_ERROR_CODE_GET_INFO_FAILED;
    }
    *index = retIndex;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_GetRouterPageName(
    ArkUI_NodeHandle node, char* buffer, int32_t bufferSize, int32_t* writeLength)
{
    CHECK_NULL_RETURN(node, ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(buffer, ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(writeLength, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(fullImpl, ARKUI_ERROR_CODE_GET_INFO_FAILED);
    auto navigationAPI = fullImpl->getNavigation();
    CHECK_NULL_RETURN(navigationAPI, ARKUI_ERROR_CODE_GET_INFO_FAILED);
    auto ret =
        navigationAPI->getRouterPageName(node->uiNodeHandle, buffer, bufferSize, writeLength);
    return static_cast<ArkUI_ErrorCode>(ret);
}

ArkUI_ErrorCode OH_ArkUI_GetRouterPagePath(
    ArkUI_NodeHandle node, char* buffer, int32_t bufferSize, int32_t* writeLength)
{
    CHECK_NULL_RETURN(node, ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(buffer, ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(writeLength, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(fullImpl, ARKUI_ERROR_CODE_GET_INFO_FAILED);
    auto navigationAPI = fullImpl->getNavigation();
    CHECK_NULL_RETURN(navigationAPI, ARKUI_ERROR_CODE_GET_INFO_FAILED);
    auto ret =
        navigationAPI->getRouterPagePath(node->uiNodeHandle, buffer, bufferSize, writeLength);
    return static_cast<ArkUI_ErrorCode>(ret);
}

ArkUI_ErrorCode OH_ArkUI_GetRouterPageState(ArkUI_NodeHandle node, ArkUI_RouterPageState* state)
{
    CHECK_NULL_RETURN(node, ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(state, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(fullImpl, ARKUI_ERROR_CODE_GET_INFO_FAILED);
    auto navigationAPI = fullImpl->getNavigation();
    CHECK_NULL_RETURN(navigationAPI, ARKUI_ERROR_CODE_GET_INFO_FAILED);

    auto routerPageState = navigationAPI->getRouterPageState(node->uiNodeHandle);
    if (routerPageState < 0) {
        return ARKUI_ERROR_CODE_GET_INFO_FAILED;
    }
    *state = static_cast<ArkUI_RouterPageState>(routerPageState);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_GetRouterPageId(
    ArkUI_NodeHandle node, char* buffer, int32_t bufferSize, int32_t* writeLength)
{
    CHECK_NULL_RETURN(node, ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(buffer, ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(writeLength, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(fullImpl, ARKUI_ERROR_CODE_GET_INFO_FAILED);
    auto navigationAPI = fullImpl->getNavigation();
    CHECK_NULL_RETURN(navigationAPI, ARKUI_ERROR_CODE_GET_INFO_FAILED);
    auto ret =
        navigationAPI->getRouterPageId(node->uiNodeHandle, buffer, bufferSize, writeLength);
    return static_cast<ArkUI_ErrorCode>(ret);
}

int32_t OH_ArkUI_PostFrameCallback(ArkUI_ContextHandle uiContext, void* userData,
    void (*callback)(uint64_t nanoTimestamp, uint32_t frameCount, void* userData))
{
    CHECK_NULL_RETURN(uiContext, ARKUI_ERROR_CODE_UI_CONTEXT_INVALID);
    CHECK_NULL_RETURN(callback, ARKUI_ERROR_CODE_CALLBACK_INVALID);
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(fullImpl, ARKUI_ERROR_CODE_CAPI_INIT_ERROR);
    auto basicAPI = fullImpl->getBasicAPI();
    CHECK_NULL_RETURN(basicAPI, ARKUI_ERROR_CODE_CAPI_INIT_ERROR);
    auto* context = reinterpret_cast<ArkUI_Context*>(uiContext);
    auto id = context->id;
    auto ret = basicAPI->postFrameCallback(id, userData, callback);
    if (ret == OHOS::Ace::ERROR_CODE_NATIVE_IMPL_NOT_MAIN_THREAD) {
        LOGF_ABORT("OH_ArkUI_PostFrameCallback doesn't run on UI thread!");
    }
    return static_cast<ArkUI_ErrorCode>(ret);
}

int32_t OH_ArkUI_PostIdleCallback(ArkUI_ContextHandle uiContext, void* userData,
    void (*callback)(uint64_t nanoTimeLeft, uint32_t frameCount, void* userData))
{
    CHECK_NULL_RETURN(uiContext, ARKUI_ERROR_CODE_UI_CONTEXT_INVALID);
    CHECK_NULL_RETURN(callback, ARKUI_ERROR_CODE_CALLBACK_INVALID);
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(fullImpl, ARKUI_ERROR_CODE_CAPI_INIT_ERROR);
    auto basicAPI = fullImpl->getBasicAPI();
    CHECK_NULL_RETURN(basicAPI, ARKUI_ERROR_CODE_CAPI_INIT_ERROR);
    auto* context = reinterpret_cast<ArkUI_Context*>(uiContext);
    auto id = context->id;
    auto ret = basicAPI->postIdleCallback(id, userData, callback);
    if (ret == OHOS::Ace::ERROR_CODE_NATIVE_IMPL_NOT_MAIN_THREAD) {
        LOGF_ABORT("OH_ArkUI_PostIdleCallback doesn't run on UI thread!");
    }
    return static_cast<ArkUI_ErrorCode>(ret);
}
}
