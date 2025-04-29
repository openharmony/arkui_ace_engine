/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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

#include "js_component_test_component.h"

#include "component_test/core/component_test_component_impl.h"
#include "interfaces/napi/kits/utils/napi_utils.h"

#include "base/log/log.h"
#include "base/utils/utils.h"

namespace OHOS::Ace::Napi {
namespace {
constexpr char TAP[] = "tap";
constexpr char DOUBLE_TAP[] = "doubleTap";
constexpr char PRESS[] = "press";
constexpr char PINCH_OUT[] = "pinchOut";
constexpr char PINCH_IN[] = "pinchIn";
constexpr char INPUT_TEXT[] = "inputText";
constexpr char CLEAR_TEXT[] = "clearText";
constexpr char SCROLL_TO_TOP[] = "scrollToTop";
constexpr char SCROLL_TO_BOTTOM[] = "scrollToBottom";
constexpr char GET_ID[] = "getId";
constexpr char GET_TEXT[] = "getText";
constexpr char GET_TYPE[] = "getType";
constexpr char IS_CLICKABLE[] = "isClickable";
constexpr char IS_LONGPRESSABLE[] = "isLongPressable";
constexpr char IS_SCROLLABLE[] = "isScrollable";
constexpr char IS_ENABLED[] = "isEnabled";
constexpr char IS_FOCUSED[] = "isFocused";
constexpr char IS_SELECTED[] = "isSelected";
constexpr char IS_CHECKED[] = "isChecked";
constexpr char IS_CHECKABLE[] = "isCheckable";
constexpr char GET_INSPECTORINFO[] = "getInspectorInfo";
constexpr char GET_INSPECTORTREE[] = "getInspectorTree";
constexpr char GET_CHILDCOUNT[] = "getChildCount";
constexpr char GET_BOUNDS[] = "getBounds";
} // namespace

thread_local napi_ref ComponentTestComponent::constructorRef_ = nullptr;
const napi_property_descriptor ComponentTestComponent::componentDesc_[] = {
    DECLARE_NAPI_FUNCTION(TAP, ComponentTestComponent::JSTap),
    DECLARE_NAPI_FUNCTION(DOUBLE_TAP, ComponentTestComponent::JSDoubleTap),
    DECLARE_NAPI_FUNCTION(PRESS, ComponentTestComponent::JSPress),
    DECLARE_NAPI_FUNCTION(PINCH_OUT, ComponentTestComponent::JSPinchOut),
    DECLARE_NAPI_FUNCTION(PINCH_IN, ComponentTestComponent::JSPinchIn),
    DECLARE_NAPI_FUNCTION(INPUT_TEXT, ComponentTestComponent::JSInputText),
    DECLARE_NAPI_FUNCTION(CLEAR_TEXT, ComponentTestComponent::JSClearText),
    DECLARE_NAPI_FUNCTION(SCROLL_TO_TOP, ComponentTestComponent::JSScrollToTop),
    DECLARE_NAPI_FUNCTION(SCROLL_TO_BOTTOM, ComponentTestComponent::JSScrollToBottom),
    DECLARE_NAPI_FUNCTION(GET_ID, ComponentTestComponent::JSGetId),
    DECLARE_NAPI_FUNCTION(GET_TEXT, ComponentTestComponent::JSGetText),
    DECLARE_NAPI_FUNCTION(GET_TYPE, ComponentTestComponent::JSGetType),
    DECLARE_NAPI_FUNCTION_WITH_DATA(IS_CLICKABLE, ComponentTestComponent::GenericBoolCallback, (void*)IS_CLICKABLE),
    DECLARE_NAPI_FUNCTION_WITH_DATA(
        IS_LONGPRESSABLE, ComponentTestComponent::GenericBoolCallback, (void*)IS_LONGPRESSABLE),
    DECLARE_NAPI_FUNCTION_WITH_DATA(IS_SCROLLABLE, ComponentTestComponent::GenericBoolCallback, (void*)IS_SCROLLABLE),
    DECLARE_NAPI_FUNCTION_WITH_DATA(IS_ENABLED, ComponentTestComponent::GenericBoolCallback, (void*)IS_ENABLED),
    DECLARE_NAPI_FUNCTION_WITH_DATA(IS_FOCUSED, ComponentTestComponent::GenericBoolCallback, (void*)IS_FOCUSED),
    DECLARE_NAPI_FUNCTION_WITH_DATA(IS_SELECTED, ComponentTestComponent::GenericBoolCallback, (void*)IS_SELECTED),
    DECLARE_NAPI_FUNCTION_WITH_DATA(IS_CHECKED, ComponentTestComponent::GenericBoolCallback, (void*)IS_CHECKED),
    DECLARE_NAPI_FUNCTION_WITH_DATA(IS_CHECKABLE, ComponentTestComponent::GenericBoolCallback, (void*)IS_CHECKABLE),
    DECLARE_NAPI_FUNCTION(GET_INSPECTORINFO, ComponentTestComponent::JSGetInspectorInfo),
    DECLARE_NAPI_FUNCTION(GET_INSPECTORTREE, ComponentTestComponent::JSGetInspectorTree),
    DECLARE_NAPI_FUNCTION(GET_CHILDCOUNT, ComponentTestComponent::JSGetChildCount),
    DECLARE_NAPI_FUNCTION(GET_BOUNDS, ComponentTestComponent::JSGetBounds),
};

napi_status ComponentTestComponent::DefineComponentTestComponent(napi_env env, napi_value exports)
{
    napi_value constructor = nullptr;
    NAPI_CALL_BASE(env,
        napi_define_class(env, COMPONENT_NAME, NAPI_AUTO_LENGTH, Constructor, nullptr,
            sizeof(componentDesc_) / sizeof(napi_property_descriptor), componentDesc_, &constructor),
        NAPI_ERR);
    NAPI_CALL_BASE(env, napi_set_named_property(env, exports, COMPONENT_NAME, constructor), NAPI_ERR);
    NAPI_CALL_BASE(env, napi_create_reference(env, constructor, 1, &constructorRef_), NAPI_ERR);
    return napi_ok;
}

napi_value ComponentTestComponent::Constructor(napi_env env, napi_callback_info info)
{
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr));
    ComponentTest::ComponentTestComponentImpl* componentImpl =
        new (std::nothrow) ComponentTest::ComponentTestComponentImpl();
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, componentImpl != nullptr, ErrCode::RET_ERR_FAILED,
        "Failed to create componentImpl.", NapiGetUndefined(env));
    NAPI_CALL_BASE(env, napi_wrap(env, thisVar, componentImpl, Destructor, nullptr, nullptr), thisVar);
    return thisVar;
}

void ComponentTestComponent::Destructor(napi_env env, void* data, void* hint)
{
    ComponentTest::ComponentTestComponentImpl* componentImpl =
        reinterpret_cast<ComponentTest::ComponentTestComponentImpl*>(data);
    CHECK_NULL_VOID(componentImpl);
    if (constructorRef_ != nullptr) {
        napi_delete_reference(env, constructorRef_);
    }
    delete componentImpl;
    componentImpl = nullptr;
}

napi_value ComponentTestComponent::JSTap(napi_env env, napi_callback_info info)
{
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr));
    ComponentTestAsyncCtx* asyncContext = CreateComponentAsyncContext(env, thisVar);
    CHECK_NULL_RETURN(asyncContext, NapiGetUndefined(env));
    napi_value promise = nullptr;
    NAPI_CALL(env, napi_create_promise(env, &asyncContext->deferred, &promise));
    ComponentTest::ComponentTestManagerProxy::PostJSTask(
        [](void* data) {
            ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
            CHECK_NULL_VOID(asyncContext);
            if (!asyncContext->componentImpl) {
                asyncContext->ret = QueryRetMsg(ErrCode::RET_ERR_FAILED);
                return;
            }
            asyncContext->componentImpl->TapImpl(asyncContext->ret);
            napi_get_null(asyncContext->env, &asyncContext->asyncResult);
        },
        AsyncCompleteWork, (void*)asyncContext);
    return promise;
}

napi_value ComponentTestComponent::JSDoubleTap(napi_env env, napi_callback_info info)
{
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr));
    ComponentTestAsyncCtx* asyncContext = CreateComponentAsyncContext(env, thisVar);
    CHECK_NULL_RETURN(asyncContext, NapiGetUndefined(env));
    napi_value promise = nullptr;
    NAPI_CALL(env, napi_create_promise(env, &asyncContext->deferred, &promise));
    ComponentTest::ComponentTestManagerProxy::PostJSTask(
        [](void* data) {
            ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
            CHECK_NULL_VOID(asyncContext);
            if (!asyncContext->componentImpl) {
                asyncContext->ret = QueryRetMsg(ErrCode::RET_ERR_FAILED);
                return;
            }
            asyncContext->componentImpl->DoubleTapImpl(asyncContext->ret);
            napi_get_null(asyncContext->env, &asyncContext->asyncResult);
        },
        AsyncCompleteWork, (void*)asyncContext);
    return promise;
}

napi_value ComponentTestComponent::JSPress(napi_env env, napi_callback_info info)
{
    size_t argc = ARG_COUNT_ONE;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, &argv, &thisVar, nullptr));
    uint32_t delayMs = 0;
    COMPONENT_TEST_NAPI_ASSERT(env, argc == ARG_COUNT_ZERO || argc == ARG_COUNT_ONE, ErrCode::RET_ERROR_PARAM_INVALID);
    if (argc == ARG_COUNT_ONE) {
        COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, GetValueType(env, argv) == napi_number, ErrCode::RET_ERROR_PARAM_INVALID,
            "Parameter is not of type number", NapiGetUndefined(env));
        NAPI_CALL(env, napi_get_value_uint32(env, argv, &delayMs));
    }
    ComponentTestAsyncCtx* asyncContext = CreateComponentAsyncContext(env, thisVar);
    CHECK_NULL_RETURN(asyncContext, NapiGetUndefined(env));
    asyncContext->delayMs = delayMs;

    napi_value promise = nullptr;
    NAPI_CALL(env, napi_create_promise(env, &asyncContext->deferred, &promise));
    ComponentTest::ComponentTestManagerProxy::PostJSTask(
        [](void* data) {
            ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
            CHECK_NULL_VOID(asyncContext);
            if (!asyncContext->componentImpl) {
                asyncContext->ret = QueryRetMsg(ErrCode::RET_ERR_FAILED);
                return;
            }
            asyncContext->componentImpl->PressImpl(asyncContext->ret, asyncContext->delayMs);
            napi_get_null(asyncContext->env, &asyncContext->asyncResult);
        },
        AsyncCompleteWork, (void*)asyncContext);
    return promise;
}

napi_value ComponentTestComponent::JSPinchOut(napi_env env, napi_callback_info info)
{
    size_t argc = ARG_COUNT_ONE;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, &argv, &thisVar, nullptr));
    COMPONENT_TEST_NAPI_ASSERT(env, argc == ARG_COUNT_ONE, ErrCode::RET_ERROR_PARAM_INVALID);
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, GetValueType(env, argv) == napi_number, ErrCode::RET_ERROR_PARAM_INVALID,
        "Parameter is not of type number", NapiGetUndefined(env));
    double scale = 0;
    NAPI_CALL(env, napi_get_value_double(env, argv, &scale));
    ComponentTestAsyncCtx* asyncContext = CreateComponentAsyncContext(env, thisVar);
    CHECK_NULL_RETURN(asyncContext, NapiGetUndefined(env));
    asyncContext->scale = static_cast<float>(scale);

    napi_value promise = nullptr;
    NAPI_CALL(env, napi_create_promise(env, &asyncContext->deferred, &promise));
    ComponentTest::ComponentTestManagerProxy::PostJSTask(
        [](void* data) {
            ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
            CHECK_NULL_VOID(asyncContext);
            if (!asyncContext->componentImpl) {
                asyncContext->ret = QueryRetMsg(ErrCode::RET_ERR_FAILED);
                return;
            }
            asyncContext->componentImpl->PinchOutImpl(asyncContext->scale, asyncContext->ret);
            napi_get_null(asyncContext->env, &asyncContext->asyncResult);
        },
        AsyncCompleteWork, (void*)asyncContext);
    return promise;
}

napi_value ComponentTestComponent::JSPinchIn(napi_env env, napi_callback_info info)
{
    size_t argc = ARG_COUNT_ONE;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, &argv, &thisVar, nullptr));
    COMPONENT_TEST_NAPI_ASSERT(env, argc == ARG_COUNT_ONE, ErrCode::RET_ERROR_PARAM_INVALID);
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, GetValueType(env, argv) == napi_number, ErrCode::RET_ERROR_PARAM_INVALID,
        "Parameter is not of type number", NapiGetUndefined(env));
    double scale = 0;
    NAPI_CALL(env, napi_get_value_double(env, argv, &scale));
    ComponentTestAsyncCtx* asyncContext = CreateComponentAsyncContext(env, thisVar);
    CHECK_NULL_RETURN(asyncContext, NapiGetUndefined(env));
    asyncContext->scale = static_cast<float>(scale);

    napi_value promise = nullptr;
    NAPI_CALL(env, napi_create_promise(env, &asyncContext->deferred, &promise));
    ComponentTest::ComponentTestManagerProxy::PostJSTask(
        [](void* data) {
            ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
            CHECK_NULL_VOID(asyncContext);
            if (!asyncContext->componentImpl) {
                asyncContext->ret = QueryRetMsg(ErrCode::RET_ERR_FAILED);
                return;
            }
            asyncContext->componentImpl->PinchInImpl(asyncContext->scale, asyncContext->ret);
            napi_get_null(asyncContext->env, &asyncContext->asyncResult);
        },
        AsyncCompleteWork, (void*)asyncContext);
    return promise;
}

napi_value ComponentTestComponent::JSInputText(napi_env env, napi_callback_info info)
{
    size_t argc = ARG_COUNT_ONE;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, &argv, &thisVar, nullptr));
    COMPONENT_TEST_NAPI_ASSERT(env, argc == ARG_COUNT_ONE, ErrCode::RET_ERROR_PARAM_INVALID);
    std::string text;
    std::string errMsg;
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, CheckAndParseStr(env, argv, text, errMsg), ErrCode::RET_ERROR_PARAM_INVALID,
        errMsg, NapiGetUndefined(env));
    ComponentTestAsyncCtx* asyncContext = CreateComponentAsyncContext(env, thisVar);
    CHECK_NULL_RETURN(asyncContext, NapiGetUndefined(env));
    asyncContext->text = text;

    napi_value promise = nullptr;
    NAPI_CALL(env, napi_create_promise(env, &asyncContext->deferred, &promise));
    ComponentTest::ComponentTestManagerProxy::PostJSTask(
        [](void* data) {
            ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
            CHECK_NULL_VOID(asyncContext);
            if (!asyncContext->componentImpl) {
                asyncContext->ret = QueryRetMsg(ErrCode::RET_ERR_FAILED);
                return;
            }
            asyncContext->componentImpl->InputTextImpl(asyncContext->text, asyncContext->ret);
            napi_get_null(asyncContext->env, &asyncContext->asyncResult);
        },
        AsyncCompleteWork, (void*)asyncContext);
    return promise;
}

napi_value ComponentTestComponent::JSClearText(napi_env env, napi_callback_info info)
{
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr));
    ComponentTestAsyncCtx* asyncContext = CreateComponentAsyncContext(env, thisVar);
    CHECK_NULL_RETURN(asyncContext, NapiGetUndefined(env));

    napi_value promise = nullptr;
    NAPI_CALL(env, napi_create_promise(env, &asyncContext->deferred, &promise));
    ComponentTest::ComponentTestManagerProxy::PostJSTask(
        [](void* data) {
            ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
            CHECK_NULL_VOID(asyncContext);
            if (!asyncContext->componentImpl) {
                asyncContext->ret = QueryRetMsg(ErrCode::RET_ERR_FAILED);
                return;
            }
            asyncContext->componentImpl->ClearTextImpl(asyncContext->ret);
            napi_get_null(asyncContext->env, &asyncContext->asyncResult);
        },
        AsyncCompleteWork, (void*)asyncContext);
    return promise;
}

napi_value ComponentTestComponent::JSScrollToTop(napi_env env, napi_callback_info info)
{
    size_t argc = ARG_COUNT_ONE;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, &argv, &thisVar, nullptr));
    COMPONENT_TEST_NAPI_ASSERT(env, argc == ARG_COUNT_ZERO || argc == ARG_COUNT_ONE, ErrCode::RET_ERROR_PARAM_INVALID);
    uint32_t speed = 0;
    if (argc == ARG_COUNT_ONE) {
        COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, GetValueType(env, argv) == napi_number, ErrCode::RET_ERROR_PARAM_INVALID,
            "Parameter is not of type number", NapiGetUndefined(env));
        NAPI_CALL(env, napi_get_value_uint32(env, argv, &speed));
    }
    ComponentTestAsyncCtx* asyncContext = CreateComponentAsyncContext(env, thisVar);
    CHECK_NULL_RETURN(asyncContext, NapiGetUndefined(env));
    asyncContext->speed = speed;

    napi_value promise = nullptr;
    NAPI_CALL(env, napi_create_promise(env, &asyncContext->deferred, &promise));
    ComponentTest::ComponentTestManagerProxy::PostJSTask(
        [](void* data) {
            ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
            CHECK_NULL_VOID(asyncContext);
            if (!asyncContext->componentImpl) {
                asyncContext->ret = QueryRetMsg(ErrCode::RET_ERR_FAILED);
                return;
            }
            napi_get_null(asyncContext->env, &asyncContext->asyncResult);
            asyncContext->componentImpl->ScrollToTopImplAsync(asyncContext->speed, [asyncContext](ErrInfo errInfo) {
                asyncContext->ret = errInfo;
                AsyncCompleteWork(asyncContext);
            });
        },
        nullptr, (void*)asyncContext);
    return promise;
}

napi_value ComponentTestComponent::JSScrollToBottom(napi_env env, napi_callback_info info)
{
    size_t argc = ARG_COUNT_ONE;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, &argv, &thisVar, nullptr));
    COMPONENT_TEST_NAPI_ASSERT(env, argc == ARG_COUNT_ZERO || argc == ARG_COUNT_ONE, ErrCode::RET_ERROR_PARAM_INVALID);
    uint32_t speed = 0;
    if (argc == ARG_COUNT_ONE) {
        COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, GetValueType(env, argv) == napi_number, ErrCode::RET_ERROR_PARAM_INVALID,
            "Parameter is not of type number", NapiGetUndefined(env));
        NAPI_CALL(env, napi_get_value_uint32(env, argv, &speed));
    }
    ComponentTestAsyncCtx* asyncContext = CreateComponentAsyncContext(env, thisVar);
    CHECK_NULL_RETURN(asyncContext, NapiGetUndefined(env));
    asyncContext->speed = speed;

    napi_value promise = nullptr;
    NAPI_CALL(env, napi_create_promise(env, &asyncContext->deferred, &promise));
    ComponentTest::ComponentTestManagerProxy::PostJSTask(
        [](void* data) {
            ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
            CHECK_NULL_VOID(asyncContext);
            if (!asyncContext->componentImpl) {
                asyncContext->ret = QueryRetMsg(ErrCode::RET_ERR_FAILED);
                return;
            }
            napi_get_null(asyncContext->env, &asyncContext->asyncResult);
            asyncContext->componentImpl->ScrollToBottomImplAsync(asyncContext->speed, [asyncContext](ErrInfo errInfo) {
                asyncContext->ret = errInfo;
                AsyncCompleteWork(asyncContext);
            });
        },
        nullptr, (void*)asyncContext);
    return promise;
}

napi_value ComponentTestComponent::JSGetId(napi_env env, napi_callback_info info)
{
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr));
    ComponentTestAsyncCtx* asyncContext = CreateComponentAsyncContext(env, thisVar);
    CHECK_NULL_RETURN(asyncContext, NapiGetUndefined(env));

    napi_value promise = nullptr;
    NAPI_CALL(env, napi_create_promise(env, &asyncContext->deferred, &promise));
    ComponentTest::ComponentTestManagerProxy::PostJSTask(
        [](void* data) {
            ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
            CHECK_NULL_VOID(asyncContext);
            if (!asyncContext->componentImpl) {
                asyncContext->ret = QueryRetMsg(ErrCode::RET_ERR_FAILED);
                return;
            }
            napi_create_string_utf8(asyncContext->env,
                asyncContext->componentImpl->GetIdImpl(asyncContext->ret).c_str(), NAPI_AUTO_LENGTH,
                &asyncContext->asyncResult);
        },
        AsyncCompleteWork, (void*)asyncContext);
    return promise;
}

napi_value ComponentTestComponent::JSGetText(napi_env env, napi_callback_info info)
{
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr));
    ComponentTestAsyncCtx* asyncContext = CreateComponentAsyncContext(env, thisVar);
    CHECK_NULL_RETURN(asyncContext, NapiGetUndefined(env));

    napi_value promise = nullptr;
    NAPI_CALL(env, napi_create_promise(env, &asyncContext->deferred, &promise));
    ComponentTest::ComponentTestManagerProxy::PostJSTask(
        [](void* data) {
            ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
            CHECK_NULL_VOID(asyncContext);
            if (!asyncContext->componentImpl) {
                asyncContext->ret = QueryRetMsg(ErrCode::RET_ERR_FAILED);
                return;
            }
            napi_create_string_utf8(asyncContext->env,
                asyncContext->componentImpl->GetTextImpl(asyncContext->ret).c_str(), NAPI_AUTO_LENGTH,
                &asyncContext->asyncResult);
        },
        AsyncCompleteWork, (void*)asyncContext);
    return promise;
}

napi_value ComponentTestComponent::JSGetType(napi_env env, napi_callback_info info)
{
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr));
    ComponentTestAsyncCtx* asyncContext = CreateComponentAsyncContext(env, thisVar);
    CHECK_NULL_RETURN(asyncContext, NapiGetUndefined(env));

    napi_value promise = nullptr;
    NAPI_CALL(env, napi_create_promise(env, &asyncContext->deferred, &promise));
    ComponentTest::ComponentTestManagerProxy::PostJSTask(
        [](void* data) {
            ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
            CHECK_NULL_VOID(asyncContext);
            if (!asyncContext->componentImpl) {
                asyncContext->ret = QueryRetMsg(ErrCode::RET_ERR_FAILED);
                return;
            }
            napi_create_string_utf8(asyncContext->env,
                asyncContext->componentImpl->GetTypeImpl(asyncContext->ret).c_str(), NAPI_AUTO_LENGTH,
                &asyncContext->asyncResult);
        },
        AsyncCompleteWork, (void*)asyncContext);
    return promise;
}

napi_value ComponentTestComponent::GenericBoolCallback(napi_env env, napi_callback_info info)
{
    napi_value thisVar = nullptr;
    void* data = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, &data));
    const char* functionName = static_cast<const char*>(data);
    ComponentTestAsyncCtx* asyncContext = CreateComponentAsyncContext(env, thisVar);
    CHECK_NULL_RETURN(asyncContext, NapiGetUndefined(env));
    asyncContext->functionName = functionName;

    napi_value promise = nullptr;
    NAPI_CALL(env, napi_create_promise(env, &asyncContext->deferred, &promise));
    ComponentTest::ComponentTestManagerProxy::PostJSTask(
        [](void* data) {
            ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
            CHECK_NULL_VOID(asyncContext);
            if (!asyncContext->componentImpl || !asyncContext->functionName) {
                asyncContext->ret = QueryRetMsg(ErrCode::RET_ERR_FAILED);
                return;
            }
            if (std::strcmp(asyncContext->functionName, IS_CLICKABLE) == 0) {
                napi_get_boolean(asyncContext->env, asyncContext->componentImpl->IsClickableImpl(asyncContext->ret),
                    &asyncContext->asyncResult);
            } else if (std::strcmp(asyncContext->functionName, IS_LONGPRESSABLE) == 0) {
                napi_get_boolean(asyncContext->env, asyncContext->componentImpl->IsLongPressableImpl(asyncContext->ret),
                    &asyncContext->asyncResult);
            } else if (std::strcmp(asyncContext->functionName, IS_SCROLLABLE) == 0) {
                napi_get_boolean(asyncContext->env, asyncContext->componentImpl->IsScrollableImpl(asyncContext->ret),
                    &asyncContext->asyncResult);
            } else if (std::strcmp(asyncContext->functionName, IS_ENABLED) == 0) {
                napi_get_boolean(asyncContext->env, asyncContext->componentImpl->IsEnabledImpl(asyncContext->ret),
                    &asyncContext->asyncResult);
            } else if (std::strcmp(asyncContext->functionName, IS_FOCUSED) == 0) {
                napi_get_boolean(asyncContext->env, asyncContext->componentImpl->IsFocusedImpl(asyncContext->ret),
                    &asyncContext->asyncResult);
            } else if (std::strcmp(asyncContext->functionName, IS_SELECTED) == 0) {
                napi_get_boolean(asyncContext->env, asyncContext->componentImpl->IsSelectedImpl(asyncContext->ret),
                    &asyncContext->asyncResult);
            } else if (std::strcmp(asyncContext->functionName, IS_CHECKED) == 0) {
                napi_get_boolean(asyncContext->env, asyncContext->componentImpl->IsCheckedImpl(asyncContext->ret),
                    &asyncContext->asyncResult);
            } else if (std::strcmp(asyncContext->functionName, IS_CHECKABLE) == 0) {
                napi_get_boolean(asyncContext->env, asyncContext->componentImpl->IsCheckableImpl(asyncContext->ret),
                    &asyncContext->asyncResult);
            } else {
                LOGW("Unknown function %{public}s", asyncContext->functionName);
            }
        },
        AsyncCompleteWork, (void*)asyncContext);
    return promise;
}

napi_value ComponentTestComponent::JSGetInspectorInfo(napi_env env, napi_callback_info info)
{
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr));
    ComponentTestAsyncCtx* asyncContext = CreateComponentAsyncContext(env, thisVar);
    CHECK_NULL_RETURN(asyncContext, NapiGetUndefined(env));
    napi_value promise = nullptr;
    NAPI_CALL(env, napi_create_promise(env, &asyncContext->deferred, &promise));
    ComponentTest::ComponentTestManagerProxy::PostJSTask(
        [](void* data) {
            ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
            CHECK_NULL_VOID(asyncContext);
            if (!asyncContext->componentImpl) {
                asyncContext->ret = QueryRetMsg(ErrCode::RET_ERR_FAILED);
                return;
            }
            napi_create_string_utf8(asyncContext->env,
                asyncContext->componentImpl->GetInspectorInfoImpl(asyncContext->ret).c_str(), NAPI_AUTO_LENGTH,
                &asyncContext->asyncResult);
        },
        AsyncCompleteWork, (void*)asyncContext);
    return promise;
}

napi_value ComponentTestComponent::JSGetInspectorTree(napi_env env, napi_callback_info info)
{
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr));
    ComponentTestAsyncCtx* asyncContext = CreateComponentAsyncContext(env, thisVar);
    CHECK_NULL_RETURN(asyncContext, NapiGetUndefined(env));

    napi_value promise = nullptr;
    NAPI_CALL(env, napi_create_promise(env, &asyncContext->deferred, &promise));
    ComponentTest::ComponentTestManagerProxy::PostJSTask(
        [](void* data) {
            ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
            CHECK_NULL_VOID(asyncContext);
            if (!asyncContext->componentImpl) {
                asyncContext->ret = QueryRetMsg(ErrCode::RET_ERR_FAILED);
                return;
            }
            napi_create_string_utf8(asyncContext->env,
                asyncContext->componentImpl->GetInspectorTreeImpl(asyncContext->ret).c_str(), NAPI_AUTO_LENGTH,
                &asyncContext->asyncResult);
        },
        AsyncCompleteWork, (void*)asyncContext);
    return promise;
}

napi_value ComponentTestComponent::JSGetChildCount(napi_env env, napi_callback_info info)
{
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr));
    ComponentTestAsyncCtx* asyncContext = CreateComponentAsyncContext(env, thisVar);
    CHECK_NULL_RETURN(asyncContext, NapiGetUndefined(env));

    napi_value promise = nullptr;
    NAPI_CALL(env, napi_create_promise(env, &asyncContext->deferred, &promise));
    ComponentTest::ComponentTestManagerProxy::PostJSTask(
        [](void* data) {
            ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
            CHECK_NULL_VOID(asyncContext);
            if (!asyncContext->componentImpl) {
                asyncContext->ret = QueryRetMsg(ErrCode::RET_ERR_FAILED);
                return;
            }
            napi_create_int32(asyncContext->env, asyncContext->componentImpl->GetChildCountImpl(asyncContext->ret),
                &asyncContext->asyncResult);
        },
        AsyncCompleteWork, (void*)asyncContext);
    return promise;
}

napi_value ComponentTestComponent::JSGetBounds(napi_env env, napi_callback_info info)
{
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr));
    ComponentTestAsyncCtx* asyncContext = CreateComponentAsyncContext(env, thisVar);
    CHECK_NULL_RETURN(asyncContext, NapiGetUndefined(env));

    napi_value promise = nullptr;
    NAPI_CALL(env, napi_create_promise(env, &asyncContext->deferred, &promise));
    ComponentTest::ComponentTestManagerProxy::PostJSTask(
        [](void* data) {
            ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
            CHECK_NULL_VOID(asyncContext);
            if (!asyncContext->componentImpl) {
                asyncContext->ret = QueryRetMsg(ErrCode::RET_ERR_FAILED);
                return;
            }
            napi_value tmp = nullptr;
            napi_create_object(asyncContext->env, &asyncContext->asyncResult);
            NG::RectF bounds = asyncContext->componentImpl->GetBoundsImpl(asyncContext->ret);
            if (asyncContext->ret.errCode != ErrCode::RET_OK) {
                return;
            }
            napi_create_int32(asyncContext->env, bounds.Left(), &tmp);
            napi_set_named_property(asyncContext->env, asyncContext->asyncResult, "left", tmp);
            napi_create_int32(asyncContext->env, bounds.Right(), &tmp);
            napi_set_named_property(asyncContext->env, asyncContext->asyncResult, "right", tmp);
            napi_create_int32(asyncContext->env, bounds.Top(), &tmp);
            napi_set_named_property(asyncContext->env, asyncContext->asyncResult, "top", tmp);
            napi_create_int32(asyncContext->env, bounds.Bottom(), &tmp);
            napi_set_named_property(asyncContext->env, asyncContext->asyncResult, "bottom", tmp);
        },
        AsyncCompleteWork, (void*)asyncContext);
    return promise;
}

void ComponentTestComponent::CreateJsComponent(
    napi_env env, napi_value* result, ComponentTest::ComponentTestComponentImpl* componentImpl)
{
    napi_create_object(env, result);
    napi_define_properties(env, *result, sizeof(componentDesc_) / sizeof(napi_property_descriptor), componentDesc_);
    napi_wrap(env, *result, componentImpl, ComponentTestComponent::Destructor, nullptr, nullptr);
}

void ComponentTestComponent::AsyncCompleteWork(void* data)
{
    ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
    napi_handle_scope scope = nullptr;
    napi_open_handle_scope(asyncContext->env, &scope);
    if (asyncContext->ret.errCode != ErrCode::RET_OK) {
        ComponentTest::ComponentTestManagerProxy::Record(
            std::string(asyncContext->ret.message), "napi_reject_deferred", ComponentTest::Result::ERROR);
        napi_throw(asyncContext->env, CreateBusinessError(asyncContext->env, asyncContext->ret));
        napi_reject_deferred(asyncContext->env, asyncContext->deferred, asyncContext->asyncResult);
    } else {
        napi_resolve_deferred(asyncContext->env, asyncContext->deferred, asyncContext->asyncResult);
    }
    napi_close_handle_scope(asyncContext->env, scope);
    delete asyncContext;
    asyncContext = nullptr;
}

ComponentTestAsyncCtx* CreateComponentAsyncContext(napi_env env, napi_value thisVar)
{
    ComponentTestAsyncCtx* asyncContext = CreateAsyncContext(env);
    if (asyncContext == nullptr) {
        return nullptr;
    }
    ComponentTest::ComponentTestComponentImpl* componentImpl = nullptr;
    napi_status status = napi_unwrap(env, thisVar, reinterpret_cast<void**>(&componentImpl));
    if (status != napi_ok || !componentImpl) {
        LOGE("%{public}s", "Failed to get unwrap ComponentTestTesterImpl");
        COMPONENT_TEST_NAPI_THROW(env, ErrCode::RET_ERR_FAILED);
        return nullptr;
    }
    asyncContext->componentImpl = componentImpl;
    return asyncContext;
}
} // namespace OHOS::Ace::Napi
