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

#include <memory>
#include "napi/native_node_api.h"
#include "node/node_extened.h"
#include "node/node_model.h"

#include "base/error/error_code.h"
#include "core/components_ng/base/frame_node.h"
#include "interfaces/native/native_error_message_macros.h"

extern "C" {
void GetStringFromNapiValue(napi_env env, napi_value value, std::string& result)
{
    napi_valuetype valueType;
    napi_typeof(env, value, &valueType);
    if (valueType != napi_string) {
        result.clear();
        return;
    }
    size_t bufferSize = 0;
    napi_status status = napi_get_value_string_utf8(env, value, nullptr, 0, &bufferSize);
    if (status != napi_ok || bufferSize == 0) {
        result.clear();
        return;
    }
    auto buffer = std::make_unique<char[]>(bufferSize + 1);
    size_t stringLength;
    status = napi_get_value_string_utf8(env, value, buffer.get(), bufferSize + 1, &stringLength);
    if (status == napi_ok && stringLength > 0) {
        result = std::string(buffer.get(), stringLength);
    } else {
        result.clear();
    }
}

int32_t OH_ArkUI_GetNodeHandleFromNapiValue(napi_env env, napi_value value, ArkUI_NodeHandle* handle)
{
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env, &scope);
    if (status != napi_ok) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Failed to open napi handle scope");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    bool hasProperty = false;
    auto result = napi_has_named_property(env, value, "nodePtr_", &hasProperty);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (result == napi_ok && hasProperty) {
        napi_value frameNodePtr = nullptr;
        auto result = napi_get_named_property(env, value, "nodePtr_", &frameNodePtr);
        if (result != napi_ok) {
            LOGE("fail to get nodePtr");
            SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Failed to get nodePtr property");
            napi_close_handle_scope(env, scope);
            return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
        }
        // BuilderNode case.
        void* nativePtr = nullptr;
        result = napi_get_value_external(env, frameNodePtr, &nativePtr);
        if (result != napi_ok || nativePtr == nullptr) {
            LOGE("fail to get nodePtr external value");
            SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__,
                "Failed to get nodePtr external value");
            napi_close_handle_scope(env, scope);
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
        napi_close_handle_scope(env, scope);
        return OHOS::Ace::ERROR_CODE_NO_ERROR;
    }
    result = napi_has_named_property(env, value, "builderNode_", &hasProperty);
    if (result == napi_ok && hasProperty) {
        // Component Content case.
        napi_value builderNode = nullptr;
        auto result = napi_get_named_property(env, value, "builderNode_", &builderNode);
        if (result != napi_ok) {
            LOGE("fail to get builderNode");
            SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Failed to get builderNode property");
            napi_close_handle_scope(env, scope);
            return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
        }
        napi_value nodePtr = nullptr;
        result = napi_get_named_property(env, builderNode, "nodePtr_", &nodePtr);
        if (result != napi_ok) {
            LOGE("fail to get nodePtr in builderNode");
            SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__,
                "Failed to get nodePtr property in builderNode");
            napi_close_handle_scope(env, scope);
            return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
        }
        void* nativePtr = nullptr;
        result = napi_get_value_external(env, nodePtr, &nativePtr);
        if (result != napi_ok) {
            LOGE("fail to get nodePtr external value in builderNode");
            SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__,
                "Failed to get nodePtr external value in builderNode");
            napi_close_handle_scope(env, scope);
            return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
        }
        auto* uiNode = reinterpret_cast<OHOS::Ace::NG::UINode*>(nativePtr);
        OHOS::Ace::NG::FrameNode* frameNode = OHOS::Ace::AceType::DynamicCast<OHOS::Ace::NG::FrameNode>(uiNode);
        if (frameNode == nullptr) {
            LOGE("fail to get frameNode value in builderNode");
            SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__,
                "Failed to get frameNode value in builderNode");
            napi_close_handle_scope(env, scope);
            return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
        }
        if (frameNode->GetTag() == "BuilderProxyNode") {
            // need to get the really frameNode.
            if (!impl) {
                SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_NATIVE_IMPL_LIBRARY_NOT_FOUND,
                    __FUNCTION__, "Native module not initialized");
                napi_close_handle_scope(env, scope);
                return OHOS::Ace::ERROR_CODE_NATIVE_IMPL_LIBRARY_NOT_FOUND;
            }
            auto* child = impl->getNodeModifiers()->getFrameNodeModifier()->getChild(
                reinterpret_cast<ArkUINodeHandle>(frameNode), 0, true);
            if (!child) {
                LOGE("fail to get child in BuilderProxyNode");
                SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__,
                    "Failed to get child node in BuilderProxyNode");
                napi_close_handle_scope(env, scope);
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
        napi_close_handle_scope(env, scope);
        return OHOS::Ace::ERROR_CODE_NO_ERROR;
    }
    napi_close_handle_scope(env, scope);
    SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Failed to get node handle from napi value");
    return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
}

int32_t OH_ArkUI_GetContextFromNapiValue(napi_env env, napi_value value, ArkUI_ContextHandle* context)
{
    bool hasProperty = false;
    auto result = napi_has_named_property(env, value, "instanceId_", &hasProperty);
    if (result != napi_ok || !hasProperty) {
        LOGE("fail to get Context value");
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Failed to get context value");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }

    napi_value contextPtr = nullptr;
    result = napi_get_named_property(env, value, "instanceId_", &contextPtr);
    if (result != napi_ok) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Failed to get instanceId property");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }

    napi_valuetype valuetype;
    if (napi_typeof(env, contextPtr, &valuetype) != napi_ok) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Failed to get instanceId value type");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (valuetype != napi_number) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "InstanceId value type is not number");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    int32_t instanceId = -1;
    result = napi_get_value_int32(env, contextPtr, &instanceId);
    if (result != napi_ok) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Failed to get instanceId value");
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
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Failed to get native content value");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    napi_value nativeContent = nullptr;
    result = napi_get_named_property(env, value, "nativePtr_", &nativeContent);
    if (result != napi_ok) {
        LOGE("fail to get native content");
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Failed to get native content property");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    void* nativePtr = nullptr;
    result = napi_get_value_external(env, nativeContent, &nativePtr);
    if (result != napi_ok) {
        LOGE("fail to get native content ptr");
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Failed to get native content pointer");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    *content = reinterpret_cast<ArkUI_NodeContentHandle>(nativePtr);
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_InitModuleForArkTSEnv(napi_env env)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(env, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Napi environment is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(OHOS::Ace::NodeModel::InitialFullImpl(), ARKUI_ERROR_CODE_CAPI_INIT_ERROR,
        __FUNCTION__, "Failed to initialize native module");
    auto callback = [](const char* moduleName) -> bool {
        const char* allowedModules[] = {
            "arkui.node",
            "arkui.modifier",
            "measure",
            "arkui.UIContext",
            "arkui.observer",
            "arkui.inspector",
            "font",
            "arkui.uicontext",
            "arkui.components.arkgauge",
            "arkui.components.arkcheckbox",
            "arkui.components.arkcheckboxgroup",
            "arkui.components.arkrating",
            "arkui.components.arkwaterflow",
            "arkui.components.arkflowitem",
            "arkui.components.arkcalendarpicker",
            "arkui.components.arktimepicker",
            "arkui.components.arkhyperlink",
            "arkui.components.arksearch",
            "arkui.components.arksymbolglyph",
            "arkui.components.arkmarquee",
            "arkui.components.arkrowsplit",
            "arkui.components.arkcolumnsplit",
            "arkui.components.arkfolderstack",
            "arkui.components.arkstepper",
            "arkui.components.arkstepperitem",
            "arkui.components.arksidebarcontainer",
            "arkui.components.arkslider",
            "arkui.components.arkradio",
            "arkui.components.arkmenu",
            "arkui.components.arkmenuitem",
            "arkui.components.arkmenuitemgroup",
            "arkui.components.arkdatapanel",
            "arkui.components.arktextclock",
            "arkui.components.arkpatternlock",
            "arkui.components.arkcounter",
            "arkui.components.arkqrcode",
            "arkui.components.arkalphabetindexer",
            "arkui.components.arkricheditor",
            "arkui.components.selectioncontainer",
            "arkui.arktheme",
            "arkui.components.arktoggle",
            "arkui.components.arktextinput",
            "arkui.components.arktextarea",
            "arkui.components.arkgrid",
            "arkui.components.arkgriditem",
            "arkui.components.arkbutton",
            "arkui.components.arktoolbaritem",
            "arkui.components.arklazygridlayout",
            "arkui.components.arkloadingprogress",
            "arkui.components.arkbadge",
            "arkui.components.arkrefresh",
            "arkui.components.arkblank",
            "arkui.components.arkdivider",
            "arkui.components.arkrelativecontainer",
            "arkui.components.arkimagespan",
            "arkui.components.arksymbolspan",
            "arkui.components.arknavigator",
            "arkui.components.arktabs",
            "arkui.components.arktabcontent",
            "arkui.components.arkswiper",
            "arkui.components.arkswiperindicator",
            "arkui.components.arkimageanimator",
            "arkui.components.arkprogress",
            "arkui.components.arktexttimer",
            "arkui.components.arkcircle",
            "arkui.components.arkellipse",
            "arkui.components.arkline",
            "arkui.components.arkpolyline",
            "arkui.components.arkrect",
            "arkui.components.arkshape",
            "arkui.components.arkpolygon",
            "arkui.components.arkpath",
            "arkui.components.arkselect",
            "arkui.components.arktextpicker",
            "arkui.components.arkxcomponent",
            "arkui.components.arkdatepicker",
            "arkui.components.arkvideo",
            "arkui.components.arkgridrow",
            "arkui.components.arkgridcol",
            "arkui.components.arkcanvas",
            "arkui.components.arkpanel",
            "arkui.components.arkgridcontainer",
        };
        for (const char* allowedModule : allowedModules) {
            if (std::strcmp(moduleName, allowedModule) == 0) {
                return true;
            }
        }
        return false;
    };
    // This function is guaranteed to be called only from a single thread,
    // so there is no need for synchronization or thread-safety mechanisms.
    static std::once_flag set_callback_flag;
    static napi_status ret = napi_ok;
    std::call_once(set_callback_flag, [callback]() { ret = napi_set_module_validate_callback(callback); });
    if (ret != napi_ok) {
        LOGE("fail to set module validate callback");
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Failed to set module validate callback");
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    impl->getRuntimeInit()->registerViews(reinterpret_cast<void*>(env));
    return ARKUI_ERROR_CODE_NO_ERROR;
}

void OH_ArkUI_NotifyArkTSEnvDestroy(napi_env env)
{
    CHECK_NULL_VOID(env);
    CHECK_NULL_VOID(OHOS::Ace::NodeModel::InitialFullImpl());
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_VOID(impl);
    impl->getRuntimeInit()->notifyArkTSEnvDestroy(reinterpret_cast<void*>(env));
}

int32_t OH_ArkUI_GetDrawableDescriptorFromNapiValue(
    napi_env env, napi_value value, ArkUI_DrawableDescriptor** drawableDescriptor)
{
    void* objectNapi = nullptr;
    napi_unwrap(env, value, &objectNapi);
    if (!objectNapi) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID,
            __FUNCTION__, "The drawableDescriptor have been released");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    ArkUI_DrawableDescriptor* drawable =
        new ArkUI_DrawableDescriptor { nullptr, nullptr, 0, nullptr, nullptr, nullptr, nullptr };
    napi_value typeName;
    napi_get_named_property(env, value, "typeName", &typeName);
    std::string typenameStr;
    GetStringFromNapiValue(env, typeName, typenameStr);
    if (typenameStr == "LayeredDrawableDescriptor") {
        auto* descriptor = reinterpret_cast<OHOS::Ace::Napi::DrawableDescriptor*>(objectNapi);
        if (!descriptor) {
            delete drawable;
            return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
        }
        drawable->drawableDescriptor = std::make_shared<OHOS::Ace::Napi::DrawableDescriptor>(descriptor->GetPixelMap());
        *drawableDescriptor = drawable;
        return OHOS::Ace::ERROR_CODE_NO_ERROR;
    }

    OHOS::Ace::NodeModel::IncreaseRefDrawable(objectNapi);
    drawable->newDrawableDescriptor = objectNapi;
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
    CHECK_NULL_RETURN_WITH_MESSAGE(node, ARKUI_ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Node is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(buffer, ARKUI_ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Buffer is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(writeLength, ARKUI_ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "WriteLength is null");
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(fullImpl, ARKUI_ERROR_CODE_GET_INFO_FAILED,
        __FUNCTION__, "Full implementation is null");
    auto navigationAPI = fullImpl->getNavigation();
    CHECK_NULL_RETURN_WITH_MESSAGE(navigationAPI, ARKUI_ERROR_CODE_GET_INFO_FAILED,
        __FUNCTION__, "Navigation API is null");
    auto ret =
        navigationAPI->getNavigationId(node->uiNodeHandle, buffer, bufferSize, writeLength);
    return static_cast<ArkUI_ErrorCode>(ret);
}

ArkUI_ErrorCode OH_ArkUI_GetNavDestinationName(
    ArkUI_NodeHandle node, char* buffer, int32_t bufferSize, int32_t* writeLength)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(node, ARKUI_ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Node is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(buffer, ARKUI_ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Buffer is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(writeLength, ARKUI_ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "WriteLength is null");
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(fullImpl, ARKUI_ERROR_CODE_GET_INFO_FAILED,
        __FUNCTION__, "Full implementation is null");
    auto navigationAPI = fullImpl->getNavigation();
    CHECK_NULL_RETURN_WITH_MESSAGE(navigationAPI, ARKUI_ERROR_CODE_GET_INFO_FAILED,
        __FUNCTION__, "Navigation API is null");
    auto ret =
        navigationAPI->getNavDestinationName(node->uiNodeHandle, buffer, bufferSize, writeLength);
    return static_cast<ArkUI_ErrorCode>(ret);
}

ArkUI_ErrorCode OH_ArkUI_GetNavStackLength(ArkUI_NodeHandle node, int32_t* length)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(node, ARKUI_ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Node is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(length, ARKUI_ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Length is null");
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(fullImpl, ARKUI_ERROR_CODE_GET_INFO_FAILED,
        __FUNCTION__, "Full implementation is null");
    auto navigationAPI = fullImpl->getNavigation();
    CHECK_NULL_RETURN_WITH_MESSAGE(navigationAPI, ARKUI_ERROR_CODE_GET_INFO_FAILED,
        __FUNCTION__, "Navigation API is null");
    auto stacklength = navigationAPI->getStackLength(node->uiNodeHandle);
    if (stacklength < 0) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_GET_INFO_FAILED,
            __FUNCTION__, "Failed to get stack length");
        return ARKUI_ERROR_CODE_GET_INFO_FAILED;
    }
    *length = stacklength;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_GetNavDestinationNameByIndex(
    ArkUI_NodeHandle node, int32_t index, char* buffer, int32_t bufferSize, int32_t* writeLength)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(node, ARKUI_ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Node is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(buffer, ARKUI_ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Buffer is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(writeLength, ARKUI_ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "WriteLength is null");
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(fullImpl, ARKUI_ERROR_CODE_GET_INFO_FAILED,
        __FUNCTION__, "Full implementation is null");
    auto navigationAPI = fullImpl->getNavigation();
    CHECK_NULL_RETURN_WITH_MESSAGE(navigationAPI, ARKUI_ERROR_CODE_GET_INFO_FAILED,
        __FUNCTION__, "Navigation API is null");
    auto ret =
        navigationAPI->getNavDesNameByIndex(node->uiNodeHandle, index, buffer, bufferSize, writeLength);
    return static_cast<ArkUI_ErrorCode>(ret);
}

ArkUI_ErrorCode OH_ArkUI_GetNavDestinationId(
    ArkUI_NodeHandle node, char* buffer, int32_t bufferSize, int32_t* writeLength)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(node, ARKUI_ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Node is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(buffer, ARKUI_ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Buffer is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(writeLength, ARKUI_ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "WriteLength is null");
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(fullImpl, ARKUI_ERROR_CODE_GET_INFO_FAILED,
        __FUNCTION__, "Full implementation is null");
    auto navigationAPI = fullImpl->getNavigation();
    CHECK_NULL_RETURN_WITH_MESSAGE(navigationAPI, ARKUI_ERROR_CODE_GET_INFO_FAILED,
        __FUNCTION__, "Navigation API is null");
    auto ret =
        navigationAPI->getNavDestinationId(node->uiNodeHandle, buffer, bufferSize, writeLength);
    return static_cast<ArkUI_ErrorCode>(ret);
}

ArkUI_ErrorCode OH_ArkUI_GetNavDestinationState(ArkUI_NodeHandle node, ArkUI_NavDestinationState* state)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(node, ARKUI_ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Node is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(state, ARKUI_ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "State is null");
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(fullImpl, ARKUI_ERROR_CODE_GET_INFO_FAILED,
        __FUNCTION__, "Full implementation is null");
    auto navigationAPI = fullImpl->getNavigation();
    CHECK_NULL_RETURN_WITH_MESSAGE(navigationAPI, ARKUI_ERROR_CODE_GET_INFO_FAILED,
        __FUNCTION__, "Navigation API is null");

    auto navDestinationState = navigationAPI->getNavDestinationState(node->uiNodeHandle);
    if (navDestinationState < 0) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_GET_INFO_FAILED,
            __FUNCTION__, "Failed to get navDestination state");
        return ARKUI_ERROR_CODE_GET_INFO_FAILED;
    }
    *state = static_cast<ArkUI_NavDestinationState>(navDestinationState);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_GetNavDestinationIndex(ArkUI_NodeHandle node, int32_t* index)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(node, ARKUI_ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Node is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(index, ARKUI_ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Index is null");
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(fullImpl, ARKUI_ERROR_CODE_GET_INFO_FAILED,
        __FUNCTION__, "Full implementation is null");
    auto navigationAPI = fullImpl->getNavigation();
    CHECK_NULL_RETURN_WITH_MESSAGE(navigationAPI, ARKUI_ERROR_CODE_GET_INFO_FAILED,
        __FUNCTION__, "Navigation API is null");

    auto retIndex = navigationAPI->getNavDestinationIndex(node->uiNodeHandle);
    if (retIndex < 0) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_GET_INFO_FAILED, __FUNCTION__,
            "Failed to get navDestination index");
        return ARKUI_ERROR_CODE_GET_INFO_FAILED;
    }
    *index = retIndex;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

napi_value OH_ArkUI_GetNavDestinationParam(ArkUI_NodeHandle node)
{
    if (!node) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Node is null");
        return nullptr;
    }
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!fullImpl) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_GET_INFO_FAILED, __FUNCTION__,
            "Full implementation is null");
        return nullptr;
    }
    auto navigationAPI = fullImpl->getNavigation();
    if (!navigationAPI) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_GET_INFO_FAILED,
            __FUNCTION__, "Navigation API is null");
        return nullptr;
    }
    return reinterpret_cast<napi_value>(navigationAPI->getNavDestinationParam(node->uiNodeHandle));
}

ArkUI_ErrorCode OH_ArkUI_GetRouterPageIndex(ArkUI_NodeHandle node, int32_t* index)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(node, ARKUI_ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Node is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(index, ARKUI_ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Index is null");
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(fullImpl, ARKUI_ERROR_CODE_GET_INFO_FAILED,
        __FUNCTION__, "Full implementation is null");
    auto navigationAPI = fullImpl->getNavigation();
    CHECK_NULL_RETURN_WITH_MESSAGE(navigationAPI, ARKUI_ERROR_CODE_GET_INFO_FAILED,
        __FUNCTION__, "Navigation API is null");

    auto retIndex = navigationAPI->getRouterPageIndex(node->uiNodeHandle);
    if (retIndex < 0) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_GET_INFO_FAILED,
            __FUNCTION__, "Failed to get router page index");
        return ARKUI_ERROR_CODE_GET_INFO_FAILED;
    }
    *index = retIndex;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_GetRouterPageName(
    ArkUI_NodeHandle node, char* buffer, int32_t bufferSize, int32_t* writeLength)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(node, ARKUI_ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Node is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(buffer, ARKUI_ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Buffer is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(writeLength, ARKUI_ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "WriteLength is null");
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(fullImpl, ARKUI_ERROR_CODE_GET_INFO_FAILED,
        __FUNCTION__, "Full implementation is null");
    auto navigationAPI = fullImpl->getNavigation();
    CHECK_NULL_RETURN_WITH_MESSAGE(navigationAPI, ARKUI_ERROR_CODE_GET_INFO_FAILED,
        __FUNCTION__, "Navigation API is null");
    auto ret =
        navigationAPI->getRouterPageName(node->uiNodeHandle, buffer, bufferSize, writeLength);
    return static_cast<ArkUI_ErrorCode>(ret);
}

ArkUI_ErrorCode OH_ArkUI_GetRouterPagePath(
    ArkUI_NodeHandle node, char* buffer, int32_t bufferSize, int32_t* writeLength)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(node, ARKUI_ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Node is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(buffer, ARKUI_ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Buffer is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(writeLength, ARKUI_ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "WriteLength is null");
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(fullImpl, ARKUI_ERROR_CODE_GET_INFO_FAILED,
        __FUNCTION__, "Full implementation is null");
    auto navigationAPI = fullImpl->getNavigation();
    CHECK_NULL_RETURN_WITH_MESSAGE(navigationAPI, ARKUI_ERROR_CODE_GET_INFO_FAILED,
        __FUNCTION__, "Navigation API is null");
    auto ret =
        navigationAPI->getRouterPagePath(node->uiNodeHandle, buffer, bufferSize, writeLength);
    return static_cast<ArkUI_ErrorCode>(ret);
}

ArkUI_ErrorCode OH_ArkUI_GetRouterPageState(ArkUI_NodeHandle node, ArkUI_RouterPageState* state)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(node, ARKUI_ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Node is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(state, ARKUI_ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "State is null");
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(fullImpl, ARKUI_ERROR_CODE_GET_INFO_FAILED,
        __FUNCTION__, "Full implementation is null");
    auto navigationAPI = fullImpl->getNavigation();
    CHECK_NULL_RETURN_WITH_MESSAGE(navigationAPI, ARKUI_ERROR_CODE_GET_INFO_FAILED,
        __FUNCTION__, "Navigation API is null");

    auto routerPageState = navigationAPI->getRouterPageState(node->uiNodeHandle);
    if (routerPageState < 0) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_GET_INFO_FAILED,
            __FUNCTION__, "Failed to get router page state");
        return ARKUI_ERROR_CODE_GET_INFO_FAILED;
    }
    *state = static_cast<ArkUI_RouterPageState>(routerPageState);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_GetRouterPageId(
    ArkUI_NodeHandle node, char* buffer, int32_t bufferSize, int32_t* writeLength)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(node, ARKUI_ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Node is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(buffer, ARKUI_ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Buffer is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(writeLength, ARKUI_ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "WriteLength is null");
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(fullImpl, ARKUI_ERROR_CODE_GET_INFO_FAILED,
        __FUNCTION__, "Full implementation is null");
    auto navigationAPI = fullImpl->getNavigation();
    CHECK_NULL_RETURN_WITH_MESSAGE(navigationAPI, ARKUI_ERROR_CODE_GET_INFO_FAILED,
        __FUNCTION__, "Navigation API is null");
    auto ret =
        navigationAPI->getRouterPageId(node->uiNodeHandle, buffer, bufferSize, writeLength);
    return static_cast<ArkUI_ErrorCode>(ret);
}

int32_t OH_ArkUI_PostFrameCallback(ArkUI_ContextHandle uiContext, void* userData,
    void (*callback)(uint64_t nanoTimestamp, uint32_t frameCount, void* userData))
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        uiContext, ARKUI_ERROR_CODE_UI_CONTEXT_INVALID, __FUNCTION__, "UI context parameter is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        callback, ARKUI_ERROR_CODE_CALLBACK_INVALID, __FUNCTION__, "Callback parameter is null");
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(fullImpl, ARKUI_ERROR_CODE_CAPI_INIT_ERROR,
        __FUNCTION__, "Native module not initialized");
    auto basicAPI = fullImpl->getBasicAPI();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        basicAPI, ARKUI_ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Basic API is not initialized");
    auto* context = reinterpret_cast<ArkUI_Context*>(uiContext);
    auto id = context->id;
    auto ret = basicAPI->postFrameCallback(id, userData, callback);
    if (ret == OHOS::Ace::ERROR_CODE_NATIVE_IMPL_NOT_MAIN_THREAD) {
        LOGF_ABORT("OH_ArkUI_PostFrameCallback doesn't run on UI thread!");
    }
    if (ret != ARKUI_ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return static_cast<ArkUI_ErrorCode>(ret);
}

int32_t OH_ArkUI_PostIdleCallback(ArkUI_ContextHandle uiContext, void* userData,
    void (*callback)(uint64_t nanoTimeLeft, uint32_t frameCount, void* userData))
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        uiContext, ARKUI_ERROR_CODE_UI_CONTEXT_INVALID, __FUNCTION__, "UI context parameter is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        callback, ARKUI_ERROR_CODE_CALLBACK_INVALID, __FUNCTION__, "Callback parameter is null");
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(fullImpl, ARKUI_ERROR_CODE_CAPI_INIT_ERROR,
        __FUNCTION__, "Native module not initialized");
    auto basicAPI = fullImpl->getBasicAPI();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        basicAPI, ARKUI_ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Basic API is not initialized");
    auto* context = reinterpret_cast<ArkUI_Context*>(uiContext);
    auto id = context->id;
    auto ret = basicAPI->postIdleCallback(id, userData, callback);
    if (ret == OHOS::Ace::ERROR_CODE_NATIVE_IMPL_NOT_MAIN_THREAD) {
        LOGF_ABORT("OH_ArkUI_PostIdleCallback doesn't run on UI thread!");
    }
    if (ret != ARKUI_ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return static_cast<ArkUI_ErrorCode>(ret);
}

ArkUI_ErrorCode OH_ArkUI_EnableEventPassthrough(ArkUI_ContextHandle uiContext, bool enabled,
    ArkUI_RawInputEventType type)
{
    CHECK_NULL_RETURN(uiContext, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(fullImpl, ARKUI_ERROR_CODE_CAPI_INIT_ERROR);
    auto basicAPI = fullImpl->getBasicAPI();
    CHECK_NULL_RETURN(basicAPI, ARKUI_ERROR_CODE_CAPI_INIT_ERROR);
    auto* context = reinterpret_cast<ArkUI_Context*>(uiContext);
    auto id = context->id;
    auto ret = basicAPI->enableEventPassthrough(id, enabled, static_cast<int32_t>(type));
    return static_cast<ArkUI_ErrorCode>(ret);
}
}
