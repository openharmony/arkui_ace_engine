/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "js_component_test_tester.h"

#include <string>

#include "component_test/component_test_proxy.h"
#include "component_test/core/component_test_component_impl.h"
#include "component_test/core/component_test_matcher_impl.h"
#include "component_test/core/component_test_tester_impl.h"
#include "interfaces/napi/kits/utils/napi_utils.h"
#include "js_component_test_component.h"
#include "js_component_test_matcher.h"

#include "base/log/log.h"
#include "base/utils/utils.h"

namespace OHOS::Ace::Napi {
namespace {
const int8_t COMBINE_KEY_MAX_COUNT = 10;

bool CheckAndParsePoint(napi_env env, napi_value arg, NG::PointF& point, std::string& errMsg)
{
    bool pointX = false;
    bool ponitY = false;
    napi_value nx = nullptr;
    napi_value ny = nullptr;
    int32_t x = 0;
    int32_t y = 0;
    if (GetValueType(env, arg) != napi_object) {
        errMsg = "Parameter from is not of type object";
        return false;
    }
    napi_has_named_property(env, arg, "x", &pointX);
    if (!pointX) {
        errMsg = "The input parameter does not exist at x";
        return false;
    }
    napi_get_named_property(env, arg, "x", &nx);
    if (GetValueType(env, nx) != napi_number) {
        errMsg = "Parameter x is not of type number";
        return false;
    }
    napi_get_value_int32(env, nx, &x);

    napi_has_named_property(env, arg, "y", &ponitY);
    if (!ponitY) {
        errMsg = "The input parameter does not exist at y";
        return false;
    }
    napi_get_named_property(env, arg, "y", &ny);
    if (GetValueType(env, ny) != napi_number) {
        errMsg = "Parameter y is not of type number";
        return false;
    }
    napi_get_value_int32(env, ny, &y);

    point.SetX(x);
    point.SetY(y);
    return true;
}
} // namespace

thread_local napi_ref ComponentTestTester::constructorRef_ = nullptr;

napi_status ComponentTestTester::DefineComponentTestTester(napi_env env, napi_value exports)
{
    napi_value constructor = nullptr;

    napi_property_descriptor desc[] = {
        DECLARE_NAPI_STATIC_FUNCTION("create", JSCreate),
        DECLARE_NAPI_FUNCTION("pump", JSPump),
        DECLARE_NAPI_FUNCTION("findComponent", JSFindComponent),
        DECLARE_NAPI_FUNCTION("findComponents", JSFindComponents),
        DECLARE_NAPI_FUNCTION("assertComponentExist", JSAssertComponentExist),
        DECLARE_NAPI_FUNCTION("scrollUntilExist", JSScrollUntilExist),
        DECLARE_NAPI_FUNCTION("triggerkey", JSTriggerkey),
        DECLARE_NAPI_FUNCTION("triggerCombineKeys", JSTriggerCombineKeys),
        DECLARE_NAPI_FUNCTION("tap", JSTap),
        DECLARE_NAPI_FUNCTION("doubleTap", JSDoubleTap),
        DECLARE_NAPI_FUNCTION("press", JSPress),
        DECLARE_NAPI_FUNCTION("scroll", JSScroll),
        DECLARE_NAPI_FUNCTION("drag", JSDrag),
        DECLARE_NAPI_FUNCTION("fling", JSFling),
    };
    NAPI_CALL_BASE(env,
        napi_define_class(env, TESTER_NAME, NAPI_AUTO_LENGTH, Constructor, nullptr,
            sizeof(desc) / sizeof(napi_property_descriptor), desc, &constructor),
        NAPI_ERR);
    NAPI_CALL_BASE(env, napi_set_named_property(env, exports, TESTER_NAME, constructor), NAPI_ERR);
    NAPI_CALL_BASE(env, napi_create_reference(env, constructor, 1, &constructorRef_), NAPI_ERR);

    return napi_ok;
}

napi_value ComponentTestTester::Constructor(napi_env env, napi_callback_info info)
{
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr));
    ComponentTest::ComponentTestTesterImpl* testerImpl = new (std::nothrow) ComponentTest::ComponentTestTesterImpl();
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(
        env, testerImpl != nullptr, ErrCode::RET_ERR_FAILED, "Failed to create testerImpl.", NapiGetUndefined(env));
    NAPI_CALL_BASE(env, napi_wrap(env, thisVar, testerImpl, Destructor, nullptr, nullptr), thisVar);
    return thisVar;
}

void ComponentTestTester::Destructor(napi_env env, void* data, void* hint)
{
    ComponentTest::ComponentTestTesterImpl* testerImpl =
        reinterpret_cast<ComponentTest::ComponentTestTesterImpl*>(data);
    CHECK_NULL_VOID(testerImpl);
    if (constructorRef_ != nullptr) {
        napi_delete_reference(env, constructorRef_);
    }
    delete testerImpl;
    testerImpl = nullptr;
}

napi_value ComponentTestTester::JSCreate(napi_env env, napi_callback_info info)
{
    CHECK_COMPONENT_TEST_ENABLED();
    napi_value constructor = nullptr;
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_reference_value(env, constructorRef_, &constructor));
    NAPI_CALL(env, napi_new_instance(env, constructor, 0, nullptr, &thisVar));
    COMPONENT_TEST_NAPI_ASSERT(env, thisVar != nullptr, ErrCode::RET_ERR_FAILED);
    return thisVar;
}

napi_value ComponentTestTester::JSPump(napi_env env, napi_callback_info info)
{
    size_t argc = ARG_COUNT_ONE;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, &argv, &thisVar, nullptr));
    COMPONENT_TEST_NAPI_ASSERT(env, argc == ARG_COUNT_ZERO || argc == ARG_COUNT_ONE, ErrCode::RET_ERROR_PARAM_INVALID);

    uint32_t delayMs = 0;
    std::string errMsg;
    if (argc == ARG_COUNT_ONE) {
        COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, CheckAndParseUInt32(env, argv, delayMs, errMsg),
            ErrCode::RET_ERROR_PARAM_INVALID, errMsg, NapiGetUndefined(env));
    }
    ComponentTestAsyncCtx* asyncContext = CreateTesterAsyncContext(env, thisVar);
    CHECK_NULL_RETURN(asyncContext, NapiGetUndefined(env));

    napi_value promise = nullptr;
    NAPI_CALL(env, napi_create_promise(env, &asyncContext->deferred, &promise));
    ComponentTest::ComponentTestManagerProxy::ClaimLongOperation();
    AceEngine::Get()
        .GetContainer(ACE_INSTANCE_ID)
        ->GetTaskExecutor()
        ->PostDelayedTask([asyncContext]() mutable {
            ComponentTest::ComponentTestManagerProxy::LongOperationComplete();
            napi_get_null(asyncContext->env, &asyncContext->asyncResult);
            napi_resolve_deferred(asyncContext->env, asyncContext->deferred, asyncContext->asyncResult);
            delete asyncContext;
            asyncContext = nullptr;
        },
        TaskExecutor::TaskType::JS, delayMs, {});
    return promise;
}

napi_value ComponentTestTester::JSFindComponent(napi_env env, napi_callback_info info)
{
    size_t argc = ARG_COUNT_ONE;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, &argv, &thisVar, nullptr));
    COMPONENT_TEST_NAPI_ASSERT(env, argc == ARG_COUNT_ONE, ErrCode::RET_ERROR_PARAM_INVALID);
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, GetValueType(env, argv) == napi_object, ErrCode::RET_ERROR_PARAM_INVALID,
        "Parameter is not of type object", NapiGetUndefined(env));
    ComponentTestAsyncCtx* asyncContext = CreateTesterAsyncContext(env, thisVar);
    CHECK_NULL_RETURN(asyncContext, NapiGetUndefined(env));
    asyncContext->matcherImpl = GetMatcher(env, argv);
    CHECK_NULL_RETURN(asyncContext->matcherImpl, NapiGetUndefined(env));

    napi_value promise = nullptr;
    NAPI_CALL(env, napi_create_promise(env, &asyncContext->deferred, &promise));
    ComponentTest::ComponentTestManagerProxy::PostJSTask(
        [](void* data) {
            ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
            CHECK_NULL_VOID(asyncContext);
            if (!asyncContext->testerImpl || !asyncContext->matcherImpl) {
                asyncContext->ret = QueryRetMsg(ErrCode::RET_ERR_FAILED);
                return;
            }
            ComponentTest::ComponentTestComponentImpl* componentImpl =
                asyncContext->testerImpl->FindComponentImpl(*(asyncContext->matcherImpl), asyncContext->ret);
            if (!componentImpl) {
                LOGW("%{public}s", "Cannot find target component.");
                napi_get_null(asyncContext->env, &asyncContext->asyncResult);
                return;
            }
            ComponentTestComponent::CreateJsComponent(asyncContext->env, &asyncContext->asyncResult, componentImpl);
        },
        AsyncCompleteWork, (void*)asyncContext);
    return promise;
}

napi_value ComponentTestTester::JSFindComponents(napi_env env, napi_callback_info info)
{
    size_t argc = ARG_COUNT_ONE;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, &argv, &thisVar, nullptr));
    COMPONENT_TEST_NAPI_ASSERT(env, argc == ARG_COUNT_ONE, ErrCode::RET_ERROR_PARAM_INVALID);
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, GetValueType(env, argv) == napi_object, ErrCode::RET_ERROR_PARAM_INVALID,
        "Parameter is not of type object", NapiGetUndefined(env));
    ComponentTestAsyncCtx* asyncContext = CreateTesterAsyncContext(env, thisVar);
    CHECK_NULL_RETURN(asyncContext, NapiGetUndefined(env));
    asyncContext->matcherImpl = GetMatcher(env, argv);
    CHECK_NULL_RETURN(asyncContext->matcherImpl, NapiGetUndefined(env));

    napi_value promise = nullptr;
    NAPI_CALL(env, napi_create_promise(env, &asyncContext->deferred, &promise));
    ComponentTest::ComponentTestManagerProxy::PostJSTask(
        [](void* data) {
            ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
            CHECK_NULL_VOID(asyncContext);
            if (!asyncContext->matcherImpl || !asyncContext->testerImpl) {
                asyncContext->ret = QueryRetMsg(ErrCode::RET_ERR_FAILED);
                return;
            }
            std::unique_ptr<std::vector<ComponentTest::ComponentTestComponentImpl*>> componentImpls =
                asyncContext->testerImpl->FindComponentsImpl(*(asyncContext->matcherImpl), asyncContext->ret);
            if (!componentImpls) {
                LOGE("Cannot find target components.");
                napi_get_null(asyncContext->env, &asyncContext->asyncResult);
                return;
            }
            napi_create_array(asyncContext->env, &(asyncContext->asyncResult));
            int32_t index = 0;
            for (const auto componentImpl : *componentImpls) {
                napi_handle_scope scope;
                napi_open_handle_scope(asyncContext->env, &scope);
                if (scope == nullptr) {
                    return;
                }
                napi_value instance = nullptr;
                ComponentTestComponent::CreateJsComponent(asyncContext->env, &instance, componentImpl);
                napi_set_element(asyncContext->env, asyncContext->asyncResult, index++, instance);
                napi_close_handle_scope(asyncContext->env, scope);
            }
        },
        AsyncCompleteWork, (void*)asyncContext);
    return promise;
}

napi_value ComponentTestTester::JSAssertComponentExist(napi_env env, napi_callback_info info)
{
    size_t argc = ARG_COUNT_ONE;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, &argv, &thisVar, nullptr));
    COMPONENT_TEST_NAPI_ASSERT(env, argc == ARG_COUNT_ONE, ErrCode::RET_ERROR_PARAM_INVALID);
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, GetValueType(env, argv) == napi_object, ErrCode::RET_ERROR_PARAM_INVALID,
        "Parameter is not of type object", NapiGetUndefined(env));
    ComponentTestAsyncCtx* asyncContext = CreateTesterAsyncContext(env, thisVar);
    CHECK_NULL_RETURN(asyncContext, NapiGetUndefined(env));
    asyncContext->matcherImpl = GetMatcher(env, argv);
    CHECK_NULL_RETURN(asyncContext->matcherImpl, NapiGetUndefined(env));

    napi_value promise = nullptr;
    NAPI_CALL(env, napi_create_promise(env, &asyncContext->deferred, &promise));
    ComponentTest::ComponentTestManagerProxy::PostJSTask(
        [](void* data) {
            ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
            CHECK_NULL_VOID(asyncContext);
            if (!asyncContext->testerImpl || !asyncContext->matcherImpl) {
                asyncContext->ret = QueryRetMsg(ErrCode::RET_ERR_FAILED);
                return;
            }
            asyncContext->testerImpl->AssertComponentExistImpl(*(asyncContext->matcherImpl), asyncContext->ret);
            napi_get_null(asyncContext->env, &asyncContext->asyncResult);
        },
        [](void* data) {
            ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
            napi_handle_scope scope = nullptr;
            napi_open_handle_scope(asyncContext->env, &scope);
            if (asyncContext->ret.errCode != ErrCode::RET_OK) {
                napi_value err = CreateBusinessError(asyncContext->env, asyncContext->ret);
                ComponentTest::ComponentTestManagerProxy::Record(
                    "assert component exist FAIL", "js_assert", ComponentTest::Result::FAIL);
                napi_throw(asyncContext->env, err);
            } else {
                ComponentTest::ComponentTestManagerProxy::Record(
                    "assert component exist PASS", "js_assert", ComponentTest::Result::PASS);
                napi_resolve_deferred(asyncContext->env, asyncContext->deferred, asyncContext->asyncResult);
            }
            napi_close_handle_scope(asyncContext->env, scope);
            delete asyncContext;
            asyncContext = nullptr;
        },
        (void*)asyncContext);
    return promise;
}

void PostScrollUntilExist(ComponentTestAsyncCtx* asyncContext)
{
    ComponentTest::ComponentTestManagerProxy::PostJSTask(
        [](void* data) {
            ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
            CHECK_NULL_VOID(asyncContext);
            if (!asyncContext->matcherImpl || !asyncContext->testerImpl) {
                asyncContext->ret = QueryRetMsg(ErrCode::RET_ERR_FAILED);
                return;
            }
            ComponentTest::ComponentTestComponentImpl* componentImpl =
                asyncContext->testerImpl->ScrollUntilExistImpl(*(asyncContext->matcherImpl), asyncContext->ret);

            if (!componentImpl) {
                LOGE("%{public}s", "Cannot find target component.");
                return;
            }
            asyncContext->componentImpl = componentImpl;
        },
        [](void* data) {
            ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
            CHECK_NULL_VOID(asyncContext);
            if (!asyncContext->componentImpl) {
                asyncContext->ret = QueryRetMsg(ErrCode::RET_ERR_FAILED);
                return;
            }
            asyncContext->componentImpl->SetEffective();
            ComponentTestComponent::CreateJsComponent(
                asyncContext->env, &asyncContext->asyncResult, asyncContext->componentImpl);
            napi_handle_scope scope = nullptr;
            napi_open_handle_scope(asyncContext->env, &scope);

            if (asyncContext->ret.errCode != ErrCode::RET_OK) {
                ComponentTest::ComponentTestManagerProxy::Record(
                    std::string(asyncContext->ret.message), "napi_reject_deferred", ComponentTest::Result::ERROR);
                napi_reject_deferred(asyncContext->env, asyncContext->deferred,
                    CreateBusinessError(asyncContext->env, asyncContext->ret));
            } else {
                napi_resolve_deferred(asyncContext->env, asyncContext->deferred, asyncContext->asyncResult);
            }
            napi_close_handle_scope(asyncContext->env, scope);
            delete asyncContext;
            asyncContext = nullptr;
        },
        (void*)asyncContext);
}

napi_value ComponentTestTester::JSScrollUntilExist(napi_env env, napi_callback_info info)
{
    size_t argc = ARG_COUNT_ONE;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, &argv, &thisVar, nullptr));
    COMPONENT_TEST_NAPI_ASSERT(env, argc == ARG_COUNT_ONE, ErrCode::RET_ERROR_PARAM_INVALID);
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, GetValueType(env, argv) == napi_object, ErrCode::RET_ERROR_PARAM_INVALID,
        "Parameter is not of type object", NapiGetUndefined(env));
    ComponentTestAsyncCtx* asyncContext = CreateTesterAsyncContext(env, thisVar);
    CHECK_NULL_RETURN(asyncContext, NapiGetUndefined(env));
    asyncContext->matcherImpl = GetMatcher(env, argv);
    CHECK_NULL_RETURN(asyncContext->matcherImpl, NapiGetUndefined(env));

    napi_value promise = nullptr;
    NAPI_CALL(env, napi_create_promise(env, &asyncContext->deferred, &promise));
    PostScrollUntilExist(asyncContext);
    return promise;
}

napi_value ComponentTestTester::JSTriggerkey(napi_env env, napi_callback_info info)
{
    size_t argc = ARG_COUNT_ONE;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, &argv, &thisVar, nullptr));
    COMPONENT_TEST_NAPI_ASSERT(env, argc == ARG_COUNT_ONE, ErrCode::RET_ERROR_PARAM_INVALID);

    uint32_t keycode = 0;
    std::string errMsg;
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, CheckAndParseUInt32(env, argv, keycode, errMsg),
        ErrCode::RET_ERROR_PARAM_INVALID, errMsg, NapiGetUndefined(env));
    ComponentTestAsyncCtx* asyncContext = CreateTesterAsyncContext(env, thisVar);
    CHECK_NULL_RETURN(asyncContext, NapiGetUndefined(env));
    asyncContext->keyCode = static_cast<OHOS::MMI::KeyCode>(keycode);

    napi_value promise = nullptr;
    NAPI_CALL(env, napi_create_promise(env, &asyncContext->deferred, &promise));
    ComponentTest::ComponentTestManagerProxy::PostJSTask(
        [](void* data) {
            ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
            CHECK_NULL_VOID(asyncContext);
            if (!asyncContext->testerImpl) {
                asyncContext->ret = QueryRetMsg(ErrCode::RET_ERR_FAILED);
                return;
            }
            asyncContext->testerImpl->TriggerKeyImpl(asyncContext->keyCode, asyncContext->ret);
            napi_get_null(asyncContext->env, &asyncContext->asyncResult);
        },
        AsyncCompleteWork, (void*)asyncContext);
    return promise;
}

napi_value ComponentTestTester::JSTriggerCombineKeys(napi_env env, napi_callback_info info)
{
    size_t argc = ARG_COUNT_ONE;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, &argv, &thisVar, nullptr));
    COMPONENT_TEST_NAPI_ASSERT(env, argc == ARG_COUNT_ONE, ErrCode::RET_ERROR_PARAM_INVALID);
    bool result = false;
    NAPI_CALL(env, napi_is_array(env, argv, &result));
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(
        env, result, ErrCode::RET_ERROR_PARAM_INVALID, "The type of argv is not array!", NapiGetUndefined(env));
    uint32_t length = 0;
    uint32_t keyCode = 0;
    std::vector<OHOS::MMI::KeyCode> keyCodes;
    NAPI_CALL(env, napi_get_array_length(env, argv, &length));
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, length > 0 && length <= COMBINE_KEY_MAX_COUNT,
        ErrCode::RET_ERROR_PARAM_INVALID, "The number of combination keys cannot exceed 10.", NapiGetUndefined(env));
    std::string errMsg;
    for (uint32_t i = 0; i < length; ++i) {
        napi_handle_scope scope;
        napi_open_handle_scope(env, &scope);
        if (scope == nullptr) {
            return NapiGetUndefined(env);
        }
        napi_value element;
        napi_get_element(env, argv, i, &element);

        COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, CheckAndParseUInt32(env, element, keyCode, errMsg),
            ErrCode::RET_ERROR_PARAM_INVALID, errMsg, NapiGetUndefined(env));
        keyCodes.emplace_back(static_cast<OHOS::MMI::KeyCode>(keyCode));
        napi_close_handle_scope(env, scope);
    }
    ComponentTestAsyncCtx* asyncContext = CreateTesterAsyncContext(env, thisVar);
    CHECK_NULL_RETURN(asyncContext, NapiGetUndefined(env));
    asyncContext->keyCodes = std::move(keyCodes);

    napi_value promise = nullptr;
    NAPI_CALL(env, napi_create_promise(env, &asyncContext->deferred, &promise));
    ComponentTest::ComponentTestManagerProxy::PostJSTask(
        [](void* data) {
            ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
            CHECK_NULL_VOID(asyncContext);
            if (!asyncContext->testerImpl) {
                asyncContext->ret = QueryRetMsg(ErrCode::RET_ERR_FAILED);
                return;
            }
            asyncContext->testerImpl->TriggerCombineKeysImpl(asyncContext->keyCodes, asyncContext->ret);
            napi_get_null(asyncContext->env, &asyncContext->asyncResult);
        },
        AsyncCompleteWork, (void*)asyncContext);
    return promise;
}

napi_value ComponentTestTester::JSTap(napi_env env, napi_callback_info info)
{
    size_t argc = ARG_COUNT_TWO;
    napi_value argv[ARG_COUNT_TWO] = { nullptr };
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVar, nullptr));
    COMPONENT_TEST_NAPI_ASSERT(env, argc == ARG_COUNT_TWO, ErrCode::RET_ERROR_PARAM_INVALID);

    uint32_t x = 0;
    uint32_t y = 0;
    std::string errMsg;
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, CheckAndParseUInt32(env, argv[ARG_COUNT_ZERO], x, errMsg),
        ErrCode::RET_ERROR_PARAM_INVALID, errMsg, NapiGetUndefined(env));
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, CheckAndParseUInt32(env, argv[ARG_COUNT_ONE], y, errMsg),
        ErrCode::RET_ERROR_PARAM_INVALID, errMsg, NapiGetUndefined(env));
    ComponentTestAsyncCtx* asyncContext = CreateTesterAsyncContext(env, thisVar);
    CHECK_NULL_RETURN(asyncContext, NapiGetUndefined(env));
    asyncContext->x = x;
    asyncContext->y = y;

    napi_value promise = nullptr;
    NAPI_CALL(env, napi_create_promise(env, &asyncContext->deferred, &promise));
    ComponentTest::ComponentTestManagerProxy::PostJSTask(
        [](void* data) {
            ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
            CHECK_NULL_VOID(asyncContext);
            if (!asyncContext->testerImpl) {
                asyncContext->ret = QueryRetMsg(ErrCode::RET_ERR_FAILED);
                return;
            }
            asyncContext->testerImpl->TapImpl(asyncContext->x, asyncContext->y, asyncContext->ret);
            napi_get_null(asyncContext->env, &asyncContext->asyncResult);
        },
        AsyncCompleteWork, (void*)asyncContext);
    return promise;
}

napi_value ComponentTestTester::JSDoubleTap(napi_env env, napi_callback_info info)
{
    size_t argc = ARG_COUNT_TWO;
    napi_value argv[ARG_COUNT_TWO] = { nullptr };
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVar, nullptr));
    COMPONENT_TEST_NAPI_ASSERT(env, argc == ARG_COUNT_TWO, ErrCode::RET_ERROR_PARAM_INVALID);

    uint32_t x = 0;
    uint32_t y = 0;
    std::string errMsg = "";
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, CheckAndParseUInt32(env, argv[ARG_COUNT_ZERO], x, errMsg),
        ErrCode::RET_ERROR_PARAM_INVALID, errMsg, NapiGetUndefined(env));
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, CheckAndParseUInt32(env, argv[ARG_COUNT_ONE], y, errMsg),
        ErrCode::RET_ERROR_PARAM_INVALID, errMsg, NapiGetUndefined(env));
    ComponentTestAsyncCtx* asyncContext = CreateTesterAsyncContext(env, thisVar);
    CHECK_NULL_RETURN(asyncContext, NapiGetUndefined(env));
    asyncContext->x = x;
    asyncContext->y = y;

    napi_value promise = nullptr;
    NAPI_CALL(env, napi_create_promise(env, &asyncContext->deferred, &promise));
    ComponentTest::ComponentTestManagerProxy::PostJSTask(
        [](void* data) {
            ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
            CHECK_NULL_VOID(asyncContext);
            if (!asyncContext->testerImpl) {
                asyncContext->ret = QueryRetMsg(ErrCode::RET_ERR_FAILED);
                return;
            }
            asyncContext->testerImpl->DoubleTapImpl(asyncContext->x, asyncContext->y, asyncContext->ret);
            napi_get_null(asyncContext->env, &asyncContext->asyncResult);
        },
        AsyncCompleteWork, (void*)asyncContext);
    return promise;
}

napi_value ComponentTestTester::JSPress(napi_env env, napi_callback_info info)
{
    size_t argc = ARG_COUNT_THREE;
    napi_value argv[ARG_COUNT_THREE] = { nullptr };
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVar, nullptr));
    COMPONENT_TEST_NAPI_ASSERT(env, argc == ARG_COUNT_TWO || argc == ARG_COUNT_THREE, ErrCode::RET_ERROR_PARAM_INVALID);

    uint32_t x = 0;
    uint32_t y = 0;
    std::string errMsg;
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, CheckAndParseUInt32(env, argv[ARG_COUNT_ZERO], x, errMsg),
        ErrCode::RET_ERROR_PARAM_INVALID, errMsg, NapiGetUndefined(env));
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, CheckAndParseUInt32(env, argv[ARG_COUNT_ONE], y, errMsg),
        ErrCode::RET_ERROR_PARAM_INVALID, errMsg, NapiGetUndefined(env));
    uint32_t duration = 0;
    if (argc == ARG_COUNT_THREE) {
        COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, CheckAndParseUInt32(env, argv[ARG_COUNT_TWO], duration, errMsg),
            ErrCode::RET_ERROR_PARAM_INVALID, errMsg, NapiGetUndefined(env));
    }
    ComponentTestAsyncCtx* asyncContext = CreateTesterAsyncContext(env, thisVar);
    CHECK_NULL_RETURN(asyncContext, NapiGetUndefined(env));
    asyncContext->x = x;
    asyncContext->y = y;
    asyncContext->duration = duration;

    napi_value promise = nullptr;
    NAPI_CALL(env, napi_create_promise(env, &asyncContext->deferred, &promise));
    ComponentTest::ComponentTestManagerProxy::PostJSTask(
        [](void* data) {
            ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
            CHECK_NULL_VOID(asyncContext);
            if (!asyncContext->testerImpl) {
                asyncContext->ret = QueryRetMsg(ErrCode::RET_ERR_FAILED);
                return;
            }
            asyncContext->testerImpl->PressImpl(
                asyncContext->x, asyncContext->y, asyncContext->ret, asyncContext->duration);
            napi_get_null(asyncContext->env, &asyncContext->asyncResult);
        },
        AsyncCompleteWork, (void*)asyncContext);
    return promise;
}

napi_value ComponentTestTester::JSScroll(napi_env env, napi_callback_info info)
{
    size_t argc = ARG_COUNT_TWO;
    napi_value argv[ARG_COUNT_TWO] = { nullptr };
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVar, nullptr));
    COMPONENT_TEST_NAPI_ASSERT(env, argc == ARG_COUNT_TWO, ErrCode::RET_ERROR_PARAM_INVALID);

    int32_t deltaX = 0;
    int32_t deltaY = 0;
    std::string errMsg;
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, CheckAndParseInt32(env, argv[ARG_COUNT_ZERO], deltaX, errMsg),
        ErrCode::RET_ERROR_PARAM_INVALID, errMsg, NapiGetUndefined(env));
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, CheckAndParseInt32(env, argv[ARG_COUNT_ONE], deltaY, errMsg),
        ErrCode::RET_ERROR_PARAM_INVALID, errMsg, NapiGetUndefined(env));
    ComponentTestAsyncCtx* asyncContext = CreateTesterAsyncContext(env, thisVar);
    CHECK_NULL_RETURN(asyncContext, NapiGetUndefined(env));
    asyncContext->deltaX = deltaX;
    asyncContext->deltaY = deltaY;

    napi_value promise = nullptr;
    NAPI_CALL(env, napi_create_promise(env, &asyncContext->deferred, &promise));
    ComponentTest::ComponentTestManagerProxy::PostJSTask(
        [](void* data) {
            ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
            CHECK_NULL_VOID(asyncContext);
            if (!asyncContext->testerImpl) {
                asyncContext->ret = QueryRetMsg(ErrCode::RET_ERR_FAILED);
                return;
            }
            asyncContext->testerImpl->ScrollImpl(asyncContext->deltaX, asyncContext->deltaY, asyncContext->ret);
            napi_get_null(asyncContext->env, &asyncContext->asyncResult);
        },
        AsyncCompleteWork, (void*)asyncContext);
    return promise;
}

napi_value ComponentTestTester::JSDrag(napi_env env, napi_callback_info info)
{
    size_t argc = ARG_COUNT_FIVE;
    napi_value argv[ARG_COUNT_FIVE] = { nullptr };
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVar, nullptr));
    COMPONENT_TEST_NAPI_ASSERT(env, argc == ARG_COUNT_FOUR || argc == ARG_COUNT_FIVE, ErrCode::RET_ERROR_PARAM_INVALID);
    ComponentTestAsyncCtx* asyncContext = CreateTesterAsyncContext(env, thisVar);
    CHECK_NULL_RETURN(asyncContext, NapiGetUndefined(env));
    std::string errMsg;
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, CheckAndParseUInt32(env, argv[ARG_COUNT_ZERO], asyncContext->x, errMsg),
        ErrCode::RET_ERROR_PARAM_INVALID, errMsg, NapiGetUndefined(env));
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, CheckAndParseUInt32(env, argv[ARG_COUNT_ONE], asyncContext->y, errMsg),
        ErrCode::RET_ERROR_PARAM_INVALID, errMsg, NapiGetUndefined(env));
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, CheckAndParseUInt32(env, argv[ARG_COUNT_TWO], asyncContext->endx, errMsg),
        ErrCode::RET_ERROR_PARAM_INVALID, errMsg, NapiGetUndefined(env));
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, CheckAndParseUInt32(env, argv[ARG_COUNT_THREE], asyncContext->endy, errMsg),
        ErrCode::RET_ERROR_PARAM_INVALID, errMsg, NapiGetUndefined(env));
    if (argc == ARG_COUNT_FIVE) {
        COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env,
            CheckAndParseUInt32(env, argv[ARG_COUNT_THREE], asyncContext->speed, errMsg),
            ErrCode::RET_ERROR_PARAM_INVALID, errMsg, NapiGetUndefined(env));
    }

    napi_value promise = nullptr;
    NAPI_CALL(env, napi_create_promise(env, &asyncContext->deferred, &promise));
    ComponentTest::ComponentTestManagerProxy::PostJSTask(
        [](void* data) {
            ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
            CHECK_NULL_VOID(asyncContext);
            if (!asyncContext->testerImpl) {
                asyncContext->ret = QueryRetMsg(ErrCode::RET_ERR_FAILED);
                return;
            }
            asyncContext->testerImpl->DragImpl(asyncContext->x, asyncContext->y, asyncContext->endx, asyncContext->endy,
                asyncContext->speed, asyncContext->ret);
            napi_get_null(asyncContext->env, &asyncContext->asyncResult);
        },
        AsyncCompleteWork, (void*)asyncContext);
    return promise;
}

bool FlingPoint(napi_env env, napi_value argv[], ComponentTestAsyncCtx* asyncContext)
{
    NG::PointF from;
    NG::PointF to;
    uint32_t speed = 0;
    uint32_t stepLen = 0;
    std::string errMsg;
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, CheckAndParsePoint(env, argv[ARG_COUNT_ZERO], from, errMsg),
        ErrCode::RET_ERROR_PARAM_INVALID, errMsg, false);
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(
        env, CheckAndParsePoint(env, argv[ARG_COUNT_ONE], to, errMsg), ErrCode::RET_ERROR_PARAM_INVALID, errMsg, false);
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, CheckAndParseUInt32(env, argv[ARG_COUNT_TWO], stepLen, errMsg),
        ErrCode::RET_ERROR_PARAM_INVALID, errMsg, false);
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, CheckAndParseUInt32(env, argv[ARG_COUNT_THREE], speed, errMsg),
        ErrCode::RET_ERROR_PARAM_INVALID, errMsg, false);
    const int32_t distanceX = to.GetX() - from.GetX();
    const int32_t distanceY = to.GetY() - from.GetY();
    const uint32_t distance = sqrt(distanceX * distanceX + distanceY * distanceY);
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, stepLen > 0 && stepLen <= distance, ErrCode::RET_ERROR_PARAM_INVALID,
        "The stepLen is out of range", false);
    asyncContext->flingP = true;
    asyncContext->speed = speed;
    asyncContext->from = from;
    asyncContext->to = to;
    asyncContext->stepLen = stepLen;
    return true;
}

bool FlingDirection(napi_env env, napi_value argv[], ComponentTestAsyncCtx* asyncContext)
{
    uint32_t direction = 0;
    uint32_t speed = 0;
    std::string errMsg;
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, CheckAndParseUInt32(env, argv[ARG_COUNT_ZERO], direction, errMsg),
        ErrCode::RET_ERROR_PARAM_INVALID, errMsg, false);
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, CheckAndParseUInt32(env, argv[ARG_COUNT_ONE], speed, errMsg),
        ErrCode::RET_ERROR_PARAM_INVALID, errMsg, false);
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env,
        direction >= ComponentTest::UiDirection::TO_LEFT && direction <= ComponentTest::UiDirection::TO_DOWN,
        ErrCode::RET_ERROR_PARAM_INVALID, "Direction can choose from 0,1,2,3 (left, right, up, down)", false);
    asyncContext->flingP = false;
    asyncContext->speed = speed;
    asyncContext->direction = static_cast<ComponentTest::UiDirection>(direction);
    return true;
}

napi_value ComponentTestTester::JSFling(napi_env env, napi_callback_info info)
{
    size_t argc = ARG_COUNT_FOUR;
    napi_value argv[ARG_COUNT_FOUR] = { nullptr };
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVar, nullptr));
    COMPONENT_TEST_NAPI_ASSERT(env, argc == ARG_COUNT_TWO || argc == ARG_COUNT_FOUR, ErrCode::RET_ERROR_PARAM_INVALID);
    ComponentTestAsyncCtx* asyncContext = CreateTesterAsyncContext(env, thisVar);
    CHECK_NULL_RETURN(asyncContext, NapiGetUndefined(env));
    if (argc == ARG_COUNT_TWO) {
        CHECK_EQUAL_RETURN(FlingDirection(env, argv, asyncContext), false, NapiGetUndefined(env));
    }
    if (argc == ARG_COUNT_FOUR) {
        CHECK_EQUAL_RETURN(FlingPoint(env, argv, asyncContext), false, NapiGetUndefined(env));
    }
    napi_value promise = nullptr;
    NAPI_CALL(env, napi_create_promise(env, &asyncContext->deferred, &promise));
    ComponentTest::ComponentTestManagerProxy::PostJSTask(
        [](void* data) {
            ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
            CHECK_NULL_VOID(asyncContext);
            if (!asyncContext->testerImpl) {
                asyncContext->ret = QueryRetMsg(ErrCode::RET_ERR_FAILED);
                return;
            }
            if (asyncContext->flingP) {
                asyncContext->testerImpl->FlingImpl(asyncContext->from, asyncContext->to, asyncContext->stepLen,
                    asyncContext->speed, asyncContext->ret);
            } else {
                asyncContext->testerImpl->FlingImpl(asyncContext->direction, asyncContext->speed, asyncContext->ret);
            }
            napi_get_null(asyncContext->env, &asyncContext->asyncResult);
        },
        AsyncCompleteWork, (void*)asyncContext);
    return promise;
}

void ComponentTestTester::AsyncCompleteWork(void* data)
{
    ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
    napi_handle_scope scope = nullptr;
    napi_open_handle_scope(asyncContext->env, &scope);

    if (asyncContext->ret.errCode != ErrCode::RET_OK) {
        ComponentTest::ComponentTestManagerProxy::Record(
            "assert component exist FAIL", "js_assert", ComponentTest::Result::FAIL);
        napi_reject_deferred(
            asyncContext->env, asyncContext->deferred, CreateBusinessError(asyncContext->env, asyncContext->ret));
    } else {
        napi_resolve_deferred(asyncContext->env, asyncContext->deferred, asyncContext->asyncResult);
    }
    napi_close_handle_scope(asyncContext->env, scope);
    delete asyncContext;
    asyncContext = nullptr;
}

ComponentTestAsyncCtx* CreateTesterAsyncContext(napi_env env, napi_value thisVar)
{
    ComponentTestAsyncCtx* asyncContext = CreateAsyncContext(env);
    if (asyncContext == nullptr) {
        return nullptr;
    }
    ComponentTest::ComponentTestTesterImpl* testerImpl = nullptr;
    napi_status status = napi_unwrap(env, thisVar, reinterpret_cast<void**>(&testerImpl));
    if (status != napi_ok || !testerImpl) {
        LOGE("%{public}s", "Failed to get unwrap ComponentTestTesterImpl");
        COMPONENT_TEST_NAPI_THROW(env, ErrCode::RET_ERR_FAILED);
        return nullptr;
    }
    asyncContext->testerImpl = testerImpl;
    return asyncContext;
}
} // namespace OHOS::Ace::Napi
