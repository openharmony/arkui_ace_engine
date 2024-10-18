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

#include <algorithm>
#include <cstdlib>
#include <string>
#include <thread>

#include "component_test/component_test_proxy.h"
#include "component_test/test_config.h"
#include "interfaces/napi/kits/utils/napi_utils.h"
#include "js_component_test_component.h"
#include "js_component_test_matcher.h"
#include "js_component_test_tester.h"
#include "js_component_test_utils.h"
#include "napi/native_api.h"
#include "napi/native_node_api.h"

#include "base/log/log.h"
#include "core/common/ace_engine.h"

namespace OHOS::Ace::Napi {

static napi_value JSLoadComponentTestEntry(napi_env env, napi_callback_info info)
{
    CHECK_COMPONENT_TEST_ENABLED();
    size_t argc = ARG_COUNT_ONE;
    napi_value argv = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, &argv, nullptr, nullptr));

    COMPONENT_TEST_NAPI_ASSERT(env, argc == ARG_COUNT_ONE, ErrCode::RET_ERROR_PARAM_INVALID);
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, GetValueType(env, argv) == napi_function, ErrCode::RET_ERROR_PARAM_INVALID,
        "Parameter entry is not of type function", NapiGetUndefined(env));
    ComponentTestAsyncCtx* asyncContext = new (std::nothrow) ComponentTestAsyncCtx();
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(
        env, asyncContext != nullptr, ErrCode::RET_ERR_FAILED, "Failed to create asyncContext.", NapiGetUndefined(env));

    napi_create_reference(env, argv, 1, &asyncContext->callbackRef);
    napi_value resource = nullptr;
    napi_create_string_utf8(env, "JSLoadComponentTestEntry", NAPI_AUTO_LENGTH, &resource);
    napi_create_async_work(
        env, nullptr, resource, [](napi_env env, void* data) {},
        [](napi_env env, napi_status status, void* data) {
            ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
            napi_value callback = nullptr;
            napi_get_reference_value(env, asyncContext->callbackRef, &callback);
            napi_call_function(env, nullptr, callback, 0, nullptr, &asyncContext->asyncResult);
            napi_delete_reference(env, asyncContext->callbackRef);
            napi_delete_async_work(env, asyncContext->asyncWork);
            delete asyncContext;
            asyncContext = nullptr;
        },
        (void*)asyncContext, &asyncContext->asyncWork);
    napi_queue_async_work(env, asyncContext->asyncWork);
    ComponentTest::ComponentTestManagerProxy::RequestContinuousIdleStatusNotification([]() {
        LOGI("Previewer ComponentTest %{public}s Finished.",
            ComponentTest::ComponentTestManagerProxy::GetTestConfigPage().c_str());
        ComponentTest::ComponentTestManagerProxy::Finish();
        std::exit(0);
    });
    return nullptr;
}

ComponentTest::TestCaseSize JSDefineTestGetCaseSize(napi_env env, napi_value arg)
{
    napi_value size = nullptr;
    uint32_t testCaseSize = 0;
    bool hasSize = false;
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, napi_has_named_property(env, arg, "size", &hasSize) == napi_ok,
        ErrCode::RET_ERROR_PARAM_INVALID, "Failed to get parameter", ComponentTest::TestCaseSize::INVALID_SIZE);
    if (hasSize) {
        COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, napi_get_named_property(env, arg, "size", &size) == napi_ok,
            ErrCode::RET_ERROR_PARAM_INVALID, "Failed to get parameter", ComponentTest::TestCaseSize::INVALID_SIZE);
        COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, GetValueType(env, size) == napi_number, ErrCode::RET_ERROR_PARAM_INVALID,
            "Parameter attr.size is not of type number", ComponentTest::TestCaseSize::INVALID_SIZE);
        COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, napi_get_value_uint32(env, size, &testCaseSize) == napi_ok,
            ErrCode::RET_ERROR_PARAM_INVALID, "Failed to get parameter", ComponentTest::TestCaseSize::INVALID_SIZE);
        COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env,
            testCaseSize >= ComponentTest::TestCaseSize::SMALLTEST &&
                testCaseSize < ComponentTest::TestCaseSize::INVALID_SIZE,
            ErrCode::RET_ERROR_PARAM_INVALID, "Exceeds the range of size", ComponentTest::TestCaseSize::INVALID_SIZE);
        ComponentTest::TestCaseSize(testCaseSize);
    }
    return ComponentTest::TestCaseSize::SMALLTEST;
}

ComponentTest::TestCaseType JSDefineTestGetCaseType(napi_env env, napi_value arg)
{
    napi_value type = nullptr;
    uint32_t testCaseType = 0;
    bool hasType = false;
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, napi_has_named_property(env, arg, "type", &hasType) == napi_ok,
        ErrCode::RET_ERROR_PARAM_INVALID, "Failed to get parameter", ComponentTest::TestCaseType::INVALID_TYPE);
    if (hasType) {
        COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, napi_get_named_property(env, arg, "type", &type) == napi_ok,
            ErrCode::RET_ERROR_PARAM_INVALID, "Failed to get parameter", ComponentTest::TestCaseType::INVALID_TYPE);
        COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, GetValueType(env, type) == napi_number, ErrCode::RET_ERROR_PARAM_INVALID,
            "Parameter attr.type is not of type number", ComponentTest::TestCaseType::INVALID_TYPE);
        COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, napi_get_value_uint32(env, type, &testCaseType) == napi_ok,
            ErrCode::RET_ERROR_PARAM_INVALID, "Failed to get parameter", ComponentTest::TestCaseType::INVALID_TYPE);
        COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env,
            testCaseType >= ComponentTest::TestCaseType::FUNCTION &&
                testCaseType < ComponentTest::TestCaseType::INVALID_TYPE,
            ErrCode::RET_ERROR_PARAM_INVALID, "Exceeds the range of type", ComponentTest::TestCaseType::INVALID_TYPE);
        ComponentTest::TestCaseType(testCaseType);
    }
    return ComponentTest::TestCaseType::FUNCTION;
}

ComponentTest::TestCaseLevel JSDefineTestGetCaseLevel(napi_env env, napi_value arg)
{
    napi_value level = nullptr;
    uint32_t testCaseLevel = 0;
    bool hasLevel = false;
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, napi_has_named_property(env, arg, "level", &hasLevel) == napi_ok,
        ErrCode::RET_ERROR_PARAM_INVALID, "Failed to get parameter", ComponentTest::TestCaseLevel::INVALID_LEVEL);
    if (hasLevel) {
        COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, napi_get_named_property(env, arg, "level", &level) == napi_ok,
            ErrCode::RET_ERROR_PARAM_INVALID, "Failed to get parameter", ComponentTest::TestCaseLevel::INVALID_LEVEL);
        COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, GetValueType(env, level) == napi_number,
            ErrCode::RET_ERROR_PARAM_INVALID, "Parameter attr.level is not of type number",
            ComponentTest::TestCaseLevel::INVALID_LEVEL);
        COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, napi_get_value_uint32(env, level, &testCaseLevel) == napi_ok,
            ErrCode::RET_ERROR_PARAM_INVALID, "Failed to get parameter", ComponentTest::TestCaseLevel::INVALID_LEVEL);
        COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env,
            testCaseLevel >= ComponentTest::TestCaseLevel::LEVEL0 &&
                testCaseLevel < ComponentTest::TestCaseLevel::INVALID_LEVEL,
            ErrCode::RET_ERROR_PARAM_INVALID, "Exceeds the range of level",
            ComponentTest::TestCaseLevel::INVALID_LEVEL);
        return ComponentTest::TestCaseLevel(testCaseLevel);
    }
    return ComponentTest::TestCaseLevel::LEVEL0;
}

static napi_value JSDefineTest(napi_env env, napi_callback_info info)
{
    CHECK_COMPONENT_TEST_ENABLED();
    size_t argc = ARG_COUNT_FOUR;
    napi_value argv[ARG_COUNT_FOUR] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr));
    COMPONENT_TEST_NAPI_ASSERT(
        env, argc == ARG_COUNT_THREE || argc == ARG_COUNT_FOUR, ErrCode::RET_ERROR_PARAM_INVALID);
    std::string testName;
    std::string errMsg;
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, CheckAndParseStr(env, argv[ARG_COUNT_ZERO], testName, errMsg),
        ErrCode::RET_ERROR_PARAM_INVALID, errMsg, NapiGetUndefined(env));
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, GetValueType(env, argv[ARG_COUNT_ONE]) == napi_object,
        ErrCode::RET_ERROR_PARAM_INVALID, "Parameter attr is not of type object", NapiGetUndefined(env));
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, GetValueType(env, argv[ARG_COUNT_TWO]) == napi_function,
        ErrCode::RET_ERROR_PARAM_INVALID, "Parameter testBody is not of type function", NapiGetUndefined(env));
    auto testCaseSize = JSDefineTestGetCaseSize(env, argv[ARG_COUNT_ONE]);
    CHECK_EQUAL_RETURN(testCaseSize, ComponentTest::TestCaseSize::INVALID_SIZE, NapiGetUndefined(env));
    auto testCaseType = JSDefineTestGetCaseType(env, argv[ARG_COUNT_ONE]);
    CHECK_EQUAL_RETURN(testCaseType, ComponentTest::TestCaseType::INVALID_TYPE, NapiGetUndefined(env));
    auto testCaseLevel = JSDefineTestGetCaseLevel(env, argv[ARG_COUNT_ONE]);
    CHECK_EQUAL_RETURN(testCaseLevel, ComponentTest::TestCaseLevel::INVALID_LEVEL, NapiGetUndefined(env));

    ComponentTestAsyncCtx* asyncContext = new (std::nothrow) ComponentTestAsyncCtx();
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(
        env, asyncContext != nullptr, ErrCode::RET_ERR_FAILED, "Failed to create asyncContext.", NapiGetUndefined(env));
    napi_create_reference(env, argv[ARG_COUNT_TWO], 1, &asyncContext->callbackRef);
    asyncContext->env = env;
    if (argc == ARG_COUNT_FOUR) {
        COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, GetValueType(env, argv[ARG_COUNT_THREE]) == napi_number,
            ErrCode::RET_ERROR_PARAM_INVALID, "Parameter delayMs is not of type number", NapiGetUndefined(env));
        NAPI_CALL(env, napi_get_value_uint32(env, argv[ARG_COUNT_THREE], &asyncContext->delayMs));
    }
    ComponentTest::TestCaseAttribute attr(testName, testCaseType, testCaseSize, testCaseLevel);

    ComponentTest::ComponentTestManagerProxy::PostJSTask(
        [attr](void* data) {
            ComponentTest::ComponentTestManagerProxy::SetTestCaseAttribute(attr);
            ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
            napi_value callback = nullptr;
            napi_get_reference_value(asyncContext->env, asyncContext->callbackRef, &callback);
            napi_call_function(asyncContext->env, nullptr, callback, 0, nullptr, &asyncContext->asyncResult);
        },
        [](void* data) {
            ComponentTestAsyncCtx* asyncContext = reinterpret_cast<ComponentTestAsyncCtx*>(data);
            napi_delete_reference(asyncContext->env, asyncContext->callbackRef);
            delete asyncContext;
            asyncContext = nullptr;
        },
        (void*)asyncContext, asyncContext->delayMs);
    return nullptr;
}

napi_value AssertArrayContain(napi_env env, napi_value array, napi_value object)
{
    bool expectIsArray = false;
    NAPI_CALL(env, napi_is_array(env, array, &expectIsArray));
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, expectIsArray, ErrCode::RET_ERROR_PARAM_INVALID,
        "Parameter expectValue is not of type string or array", NapiGetUndefined(env));
    bool result = false;
    uint32_t expectLength = 0;
    NAPI_CALL(env, napi_get_array_length(env, array, &expectLength));
    uint32_t actualArrayIndex = 0;
    for (uint32_t i = 0; i < expectLength; i++) {
        napi_handle_scope scope = nullptr;
        napi_open_handle_scope(env, &scope);
        napi_value expectElement = nullptr;
        napi_has_element(env, array, i, &result);
        if (!result) {
            napi_close_handle_scope(env, scope);
            break;
        }
        napi_get_element(env, array, i, &expectElement);
        napi_strict_equals(env, expectElement, object, &result);
        napi_close_handle_scope(env, scope);
        if (result) {
            break;
        }
    }
    std::string expectStr = NapiValueToString(env, array);
    std::string actualStr = NapiValueToString(env, object);
    ComponentTestRecord(result, "Expect [" + expectStr + "] to contain '" + actualStr + "'.");
    if (!result) {
        LOGE("%{public}s", "Expect expectValue to contain actualValue failed.");
        COMPONENT_TEST_NAPI_JS_ASSERTION_FAIL(env, ErrCode::RET_ERR_ASSERTION_CONTAINS);
    }
    return NapiGetUndefined(env);
}

napi_value JSAssertContain(napi_env env, napi_callback_info info)
{
    CHECK_COMPONENT_TEST_ENABLED();
    size_t argc = ARG_COUNT_TWO;
    napi_value argv[ARG_COUNT_TWO] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr));
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, argc == ARG_COUNT_TWO, ErrCode::RET_ERROR_PARAM_INVALID,
        "Failed to get parameters", NapiGetUndefined(env));
    if (GetValueType(env, argv[0]) == napi_string) {
        COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, GetValueType(env, argv[ARG_COUNT_ONE]) == napi_string,
            ErrCode::RET_ERROR_PARAM_INVALID,
            "Parameter expectValue is a string but parameter actualValue is not a string", NapiGetUndefined(env));
        std::string expectStr = NapiValueToString(env, argv[0]);
        std::string actualStr = NapiValueToString(env, argv[1]);
        bool strResult = expectStr.find(actualStr) != std::string::npos;
        ComponentTestRecord(strResult, "Expect '" + expectStr + "' to contain '" + actualStr + "'.");
        if (!strResult) {
            COMPONENT_TEST_NAPI_JS_ASSERTION_FAIL(env, ErrCode::RET_ERR_ASSERTION_CONTAINS);
        }
    } else {
        AssertArrayContain(env, argv[0], argv[ARG_COUNT_ONE]);
    }
    return NapiGetUndefined(env);
}

napi_value ResourceToNapiString(napi_env env, napi_value resource)
{
    CompleteResourceParam(env, resource);
    ResourceInfo resourceInfo;
    std::string resourceStr;
    if (ParseResourceParam(env, resource, resourceInfo)) {
        if (resourceInfo.type == static_cast<int>(ResourceType::MEDIA)) {
            auto resourceWrapper = CreateResourceWrapper(resourceInfo);
            std::string pathStr;
            if (resourceInfo.resId == -1) {
                pathStr = resourceWrapper->GetMediaPathByName(resourceInfo.params[0]);
            } else {
                pathStr = resourceWrapper->GetMediaPath(resourceInfo.resId);
            }
            return CreateNapiString(env, pathStr);
        } else if (ParseString(resourceInfo, resourceStr)) {
            return CreateNapiString(env, resourceStr);
        }
    }
    return nullptr;
}

napi_value JSAssertEqual(napi_env env, napi_callback_info info)
{
    CHECK_COMPONENT_TEST_ENABLED();
    size_t argc = ARG_COUNT_TWO;
    napi_value argv[ARG_COUNT_TWO] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr));
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, argc == ARG_COUNT_TWO, ErrCode::RET_ERROR_PARAM_INVALID,
        "Failed to get parameters", NapiGetUndefined(env));
    napi_value expectValue = argv[ARG_COUNT_ONE];
    napi_value actualValue = argv[0];
    napi_value napiStrExpect = ResourceToNapiString(env, expectValue);
    if (napiStrExpect) {
        expectValue = napiStrExpect;
    }
    napi_value napiStrActual = ResourceToNapiString(env, actualValue);
    if (napiStrActual) {
        actualValue = napiStrActual;
    }

    napi_value expectValueNapiString;
    napi_value actualValueNapiString;
    char expectStrBuffer[NAPI_MAX_BUF_LEN] = { 0 };
    char actualStrBuffer[NAPI_MAX_BUF_LEN] = { 0 };
    NAPI_CALL(env, napi_coerce_to_string(env, expectValue, &expectValueNapiString));
    NAPI_CALL(env, napi_coerce_to_string(env, actualValue, &actualValueNapiString));
    size_t expectBufSize = 0;
    size_t actualBufSize = 0;
    NAPI_CALL(
        env, napi_get_value_string_utf8(env, expectValueNapiString, expectStrBuffer, NAPI_MAX_BUF_LEN, &expectBufSize));
    NAPI_CALL(
        env, napi_get_value_string_utf8(env, actualValueNapiString, actualStrBuffer, NAPI_MAX_BUF_LEN, &actualBufSize));
    std::string expectStr(expectStrBuffer, expectBufSize);
    std::string actualStr(actualStrBuffer, actualBufSize);
    bool result = false;
    NAPI_CALL(env, napi_strict_equals(env, expectValue, actualValue, &result));

    std::string assertionDescription;
    if (!result) {
        if (GetValueType(env, expectValue) == napi_object && GetValueType(env, actualValue) == napi_object) {
            assertionDescription =
                "Expect a value equal to '" + expectStr + "', but getting '" + actualStr + "'(different references).";
        } else {
            assertionDescription = "Expect a value equal to '" + expectStr + "', but getting '" + actualStr + "'.";
        }
        LOGE("%{public}s", assertionDescription.c_str());
        ComponentTestRecord(result, assertionDescription);
        COMPONENT_TEST_NAPI_JS_ASSERTION_FAIL(env, ErrCode::RET_ERR_ASSERTION_EQUAL);
    } else {
        assertionDescription = "Expect a value equal to '" + expectStr + "'.";
        ComponentTestRecord(result, assertionDescription);
    }
    return NapiGetUndefined(env);
}

napi_value JSAssertFalse(napi_env env, napi_callback_info info)
{
    CHECK_COMPONENT_TEST_ENABLED();
    size_t argc = ARG_COUNT_ONE;
    napi_value argv = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, &argv, nullptr, nullptr));
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, argc == ARG_COUNT_ONE, ErrCode::RET_ERROR_PARAM_INVALID,
        "Failed to get parameters", NapiGetUndefined(env));

    bool result = false;
    std::string assertionDescription;
    if (GetValueType(env, argv) == napi_boolean) {
        NAPI_CALL(env, napi_get_value_bool(env, argv, &result));
        if (result) {
            assertionDescription = "Expect the value to be 'false', but getting 'true'.";
        }
    } else if (GetValueType(env, argv) == napi_string) {
        size_t bufSize = 0;
        napi_value napiString;
        char strBuffer[NAPI_MAX_BUF_LEN] = { 0 };
        NAPI_CALL(env, napi_coerce_to_string(env, argv, &napiString));
        NAPI_CALL(env, napi_get_value_string_utf8(env, napiString, strBuffer, NAPI_MAX_BUF_LEN, &bufSize));
        std::string actualStr(strBuffer, bufSize);
        std::string lowerActualStr = actualStr;
        std::transform(actualStr.begin(), actualStr.end(), lowerActualStr.begin(), ::tolower);
        if (lowerActualStr == std::string("true")) {
            result = true;
            assertionDescription = "Expect the value to be 'false', but getting 'true'.";
        } else if (lowerActualStr != std::string("false")) {
            result = true;
            assertionDescription = "Unable to recognize '" + actualStr + "' as a string representing a Boolean value.";
        }
    } else {
        COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, false, ErrCode::RET_ERROR_PARAM_INVALID,
            "The parameter is not a Boolean type or a string", NapiGetUndefined(env));
    }
    if (result) {
        LOGE("%{public}s", assertionDescription.c_str());
        ComponentTestRecord(!result, assertionDescription);
        COMPONENT_TEST_NAPI_JS_ASSERTION_FAIL(env, ErrCode::RET_ERR_ASSERTION_FALSE);
    } else {
        assertionDescription = "Expect the value to be 'false'.";
        ComponentTestRecord(!result, assertionDescription);
    }
    return NapiGetUndefined(env);
}

napi_value JSAssertTrue(napi_env env, napi_callback_info info)
{
    CHECK_COMPONENT_TEST_ENABLED();
    size_t argc = ARG_COUNT_ONE;
    napi_value argv = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, &argv, nullptr, nullptr));
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, argc == ARG_COUNT_ONE, ErrCode::RET_ERROR_PARAM_INVALID,
        "Failed to get parameters", NapiGetUndefined(env));

    bool result = false;
    std::string assertionDescription;
    if (GetValueType(env, argv) == napi_boolean) {
        NAPI_CALL(env, napi_get_value_bool(env, argv, &result));
        if (!result) {
            assertionDescription = "Expect the value to be 'true', but getting 'false'.";
        }
    } else if (GetValueType(env, argv) == napi_string) {
        size_t bufSize = 0;
        napi_value napiString;
        char strBuffer[NAPI_MAX_BUF_LEN] = { 0 };
        NAPI_CALL(env, napi_coerce_to_string(env, argv, &napiString));
        NAPI_CALL(env, napi_get_value_string_utf8(env, napiString, strBuffer, NAPI_MAX_BUF_LEN, &bufSize));
        std::string actualStr(strBuffer, bufSize);
        std::string lowerActualStr = actualStr;
        std::transform(actualStr.begin(), actualStr.end(), lowerActualStr.begin(), ::tolower);
        if (lowerActualStr == std::string("true")) {
            result = true;
        } else if (lowerActualStr == std::string("false")) {
            assertionDescription = "Expect the value to be 'true', but getting 'false'.";
        } else {
            assertionDescription = "Unable to recognize '" + actualStr + "' as a string representing a Boolean value.";
        }
    } else {
        COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, false, ErrCode::RET_ERROR_PARAM_INVALID,
            "The parameter is not a Boolean type or a string", NapiGetUndefined(env));
    }
    if (!result) {
        LOGE("%{public}s", assertionDescription.c_str());
        ComponentTestRecord(result, assertionDescription);
        COMPONENT_TEST_NAPI_JS_ASSERTION_FAIL(env, ErrCode::RET_ERR_ASSERTION_TRUE);
    } else {
        assertionDescription = "Expect the value to be 'true'.";
        ComponentTestRecord(result, assertionDescription);
    }
    return NapiGetUndefined(env);
}

static napi_value componentTestExport(napi_env env, napi_value exports)
{
    napi_property_descriptor desc[] = {
        DECLARE_NAPI_FUNCTION("loadComponentTestEntry", JSLoadComponentTestEntry),
        DECLARE_NAPI_FUNCTION("defineTest", JSDefineTest),
        DECLARE_NAPI_FUNCTION("assertContain", JSAssertContain),
        DECLARE_NAPI_FUNCTION("assertEqual", JSAssertEqual),
        DECLARE_NAPI_FUNCTION("assertFalse", JSAssertFalse),
        DECLARE_NAPI_FUNCTION("assertTrue", JSAssertTrue),
    };
    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));
    NAPI_CALL(env, ComponentTestTester::DefineComponentTestTester(env, exports));
    NAPI_CALL(env, ComponentTestMatcher::DefineComponentTestMatcher(env, exports));
    NAPI_CALL(env, ComponentTestComponent::DefineComponentTestComponent(env, exports));
    NAPI_CALL(env, ExportEnumerator(env, exports, TEST_CASE_TYPE_DEF));
    NAPI_CALL(env, ExportEnumerator(env, exports, TEST_CASE_SIZE_DEF));
    NAPI_CALL(env, ExportEnumerator(env, exports, TEST_CASE_LEVEL_DEF));
    NAPI_CALL(env, ExportEnumerator(env, exports, MATCH_TYPE_DEF));
    NAPI_CALL(env, ExportEnumerator(env, exports, UI_DIRECTION_DEF));

    return exports;
}

static napi_module componentTestModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = componentTestExport,
    .nm_modname = "arkui.componentTest",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void ComponentTestRegister()
{
    napi_module_register(&componentTestModule);
}
} // namespace OHOS::Ace::Napi
