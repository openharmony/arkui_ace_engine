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

#include "js_component_test_matcher.h"

#include <string>

#include "component_test/component_test_proxy.h"
#include "interfaces/napi/kits/utils/napi_utils.h"
#include "js_component_test_utils.h"
#include "napi/native_api.h"
#include "napi/native_node_api.h"

#include "base/log/log.h"
#include "base/utils/utils.h"

namespace OHOS::Ace::Napi {
namespace {
constexpr char CREATE[] = "create";
constexpr char TEXT[] = "text";
constexpr char ID[] = "id";
constexpr char TYPE[] = "type";
constexpr char CLICKABLE[] = "clickable";
constexpr char LONGPRESSABLE[] = "longPressable";
constexpr char SCROLLABLE[] = "scrollable";
constexpr char ENABLED[] = "enabled";
constexpr char FOCUSED[] = "focused";
constexpr char SELECTED[] = "selected";
constexpr char CHECKED[] = "checked";
constexpr char CHECKABLE[] = "checkable";
} // namespace

thread_local napi_ref ComponentTestMatcher::constructorRef_ = nullptr;

napi_status ComponentTestMatcher::DefineComponentTestMatcher(napi_env env, napi_value exports)
{
    napi_value constructor = nullptr;

    napi_property_descriptor desc[] = {
        DECLARE_NAPI_STATIC_FUNCTION(CREATE, JSCreate),
        DECLARE_NAPI_FUNCTION(TEXT, JSText),
        DECLARE_NAPI_FUNCTION(ID, JSId),
        DECLARE_NAPI_FUNCTION(TYPE, JSType),
        DECLARE_NAPI_FUNCTION_WITH_DATA(CLICKABLE, GenericBoolCallback, (void*)CLICKABLE),
        DECLARE_NAPI_FUNCTION_WITH_DATA(LONGPRESSABLE, GenericBoolCallback, (void*)LONGPRESSABLE),
        DECLARE_NAPI_FUNCTION_WITH_DATA(SCROLLABLE, GenericBoolCallback, (void*)SCROLLABLE),
        DECLARE_NAPI_FUNCTION_WITH_DATA(ENABLED, GenericBoolCallback, (void*)ENABLED),
        DECLARE_NAPI_FUNCTION_WITH_DATA(FOCUSED, GenericBoolCallback, (void*)FOCUSED),
        DECLARE_NAPI_FUNCTION_WITH_DATA(SELECTED, GenericBoolCallback, (void*)SELECTED),
        DECLARE_NAPI_FUNCTION_WITH_DATA(CHECKED, GenericBoolCallback, (void*)CHECKED),
        DECLARE_NAPI_FUNCTION_WITH_DATA(CHECKABLE, GenericBoolCallback, (void*)CHECKABLE),
    };

    NAPI_CALL_BASE(env,
        napi_define_class(env, MATCHER_NAME, NAPI_AUTO_LENGTH, Constructor, nullptr,
            sizeof(desc) / sizeof(napi_property_descriptor), desc, &constructor),
        NAPI_ERR);
    NAPI_CALL_BASE(env, napi_set_named_property(env, exports, MATCHER_NAME, constructor), NAPI_ERR);
    NAPI_CALL_BASE(env, napi_create_reference(env, constructor, 1, &constructorRef_), NAPI_ERR);

    return napi_ok;
}

napi_value ComponentTestMatcher::Constructor(napi_env env, napi_callback_info info)
{
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr));
    ComponentTest::ComponentTestMatcherImpl* matcherImpl = new (std::nothrow) ComponentTest::ComponentTestMatcherImpl();
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(
        env, matcherImpl != nullptr, ErrCode::RET_ERR_FAILED, "Failed to create matcherImpl.", NapiGetUndefined(env));
    NAPI_CALL_BASE(env, napi_wrap(env, thisVar, matcherImpl, Destructor, nullptr, nullptr), thisVar);
    return thisVar;
}

void ComponentTestMatcher::Destructor(napi_env env, void* data, void* hint)
{
    ComponentTest::ComponentTestMatcherImpl* matcherImpl =
        reinterpret_cast<ComponentTest::ComponentTestMatcherImpl*>(data);
    CHECK_NULL_VOID(matcherImpl);
    if (constructorRef_ != nullptr) {
        napi_delete_reference(env, constructorRef_);
    }
    delete matcherImpl;
    matcherImpl = nullptr;
}

napi_value ComponentTestMatcher::JSCreate(napi_env env, napi_callback_info info)
{
    CHECK_COMPONENT_TEST_ENABLED();
    napi_value constructor = nullptr;
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_reference_value(env, constructorRef_, &constructor));
    NAPI_CALL(env, napi_new_instance(env, constructor, 0, nullptr, &thisVar));
    COMPONENT_TEST_NAPI_ASSERT(env, thisVar != nullptr, ErrCode::RET_ERR_FAILED);
    return thisVar;
}

napi_value ComponentTestMatcher::JSText(napi_env env, napi_callback_info info)
{
    size_t argc = ARG_COUNT_TWO;
    napi_value argv[ARG_COUNT_TWO] = { nullptr };
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVar, nullptr));
    COMPONENT_TEST_NAPI_ASSERT(env, argc == ARG_COUNT_ONE || argc == ARG_COUNT_TWO, ErrCode::RET_ERROR_PARAM_INVALID);

    std::string text;
    std::string errMsg;
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, CheckAndParseStr(env, argv[ARG_COUNT_ZERO], text, errMsg),
        ErrCode::RET_ERROR_PARAM_INVALID, errMsg, NapiGetUndefined(env));
    ComponentTest::ComponentTestMatcherImpl* matcherImpl = GetMatcher(env, thisVar);
    CHECK_NULL_RETURN(matcherImpl, NapiGetUndefined(env));
    if (argc == ARG_COUNT_TWO) {
        COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, GetValueType(env, argv[ARG_COUNT_ONE]) == napi_number,
            ErrCode::RET_ERROR_PARAM_INVALID, "Parameter is not of type number", NapiGetUndefined(env));
        int32_t matchType = 0;
        NAPI_CALL(env, napi_get_value_int32(env, argv[ARG_COUNT_ONE], &matchType));
        COMPONENT_TEST_NAPI_ASSERT_CUSTOM(
            env, matchType >= 0, ErrCode::RET_ERROR_PARAM_INVALID, "Exceeds the range of types", NapiGetUndefined(env));
        ComponentTest::MatchType enumValue = static_cast<ComponentTest::MatchType>(matchType);
        matcherImpl->SetText(text, enumValue);
    } else {
        matcherImpl->SetText(text);
    }
    return thisVar;
}

napi_value ComponentTestMatcher::JSId(napi_env env, napi_callback_info info)
{
    size_t argc = ARG_COUNT_ONE;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, &argv, &thisVar, nullptr));
    COMPONENT_TEST_NAPI_ASSERT(env, argc == ARG_COUNT_ONE, ErrCode::RET_ERROR_PARAM_INVALID);

    std::string id;
    std::string errMsg;
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(
        env, CheckAndParseStr(env, argv, id, errMsg), ErrCode::RET_ERROR_PARAM_INVALID, errMsg, NapiGetUndefined(env));
    ComponentTest::ComponentTestMatcherImpl* matcherImpl = GetMatcher(env, thisVar);
    CHECK_NULL_RETURN(matcherImpl, NapiGetUndefined(env));
    matcherImpl->SetId(id);
    return thisVar;
}

napi_value ComponentTestMatcher::JSType(napi_env env, napi_callback_info info)
{
    size_t argc = ARG_COUNT_ONE;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, &argv, &thisVar, nullptr));
    COMPONENT_TEST_NAPI_ASSERT(env, argc == ARG_COUNT_ONE, ErrCode::RET_ERROR_PARAM_INVALID);

    std::string type;
    std::string errMsg;
    COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, CheckAndParseStr(env, argv, type, errMsg), ErrCode::RET_ERROR_PARAM_INVALID,
        errMsg, NapiGetUndefined(env));
    ComponentTest::ComponentTestMatcherImpl* matcherImpl = GetMatcher(env, thisVar);
    CHECK_NULL_RETURN(matcherImpl, NapiGetUndefined(env));
    matcherImpl->SetType(type);
    return thisVar;
}

napi_value ComponentTestMatcher::GenericBoolCallback(napi_env env, napi_callback_info info)
{
    size_t argc = ARG_COUNT_ONE;
    void* data = nullptr;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, &argv, &thisVar, &data));
    COMPONENT_TEST_NAPI_ASSERT(env, argc == ARG_COUNT_ZERO || argc == ARG_COUNT_ONE, ErrCode::RET_ERROR_PARAM_INVALID);
    COMPONENT_TEST_NAPI_ASSERT(env, data != nullptr, ErrCode::RET_ERR_FAILED);
    bool res = true;
    std::string errMsg;
    if (argc == ARG_COUNT_ONE) {
        COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, CheckAndParseBool(env, argv, res, errMsg),
            ErrCode::RET_ERROR_PARAM_INVALID, errMsg, NapiGetUndefined(env));
    }
    ComponentTest::ComponentTestMatcherImpl* matcherImpl = GetMatcher(env, thisVar);
    CHECK_NULL_RETURN(matcherImpl, NapiGetUndefined(env));

    const char* functionName = static_cast<const char*>(data);
    if (std::strcmp(functionName, "clickable") == 0) {
        matcherImpl->SetClickable(res);
    } else if (std::strcmp(functionName, "longPressable") == 0) {
        matcherImpl->SetLongPressable(res);
    } else if (std::strcmp(functionName, "scrollable") == 0) {
        matcherImpl->SetScrollable(res);
    } else if (std::strcmp(functionName, "enabled") == 0) {
        matcherImpl->SetEnabled(res);
    } else if (std::strcmp(functionName, "focused") == 0) {
        matcherImpl->SetFocused(res);
    } else if (std::strcmp(functionName, "selected") == 0) {
        matcherImpl->SetSelected(res);
    } else if (std::strcmp(functionName, "checked") == 0) {
        matcherImpl->SetChecked(res);
    } else if (std::strcmp(functionName, "checkable") == 0) {
        matcherImpl->SetCheckable(res);
    } else {
        LOGW("Unknown function %{public}s", functionName);
    }
    return thisVar;
}

} // namespace OHOS::Ace::Napi
