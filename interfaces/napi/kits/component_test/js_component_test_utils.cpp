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

#include "js_component_test_utils.h"

#include "interfaces/napi/kits/utils/napi_utils.h"

#include "base/log/log.h"
#include "bridge/common/utils/engine_helper.h"

namespace OHOS::Ace::Napi {

ComponentTestAsyncCtx* CreateAsyncContext(napi_env env)
{
    ComponentTestAsyncCtx* asyncContext = new (std::nothrow) ComponentTestAsyncCtx();
    if (asyncContext == nullptr) {
        LOGE("%{public}s", "Failed to create asyncContext.");
        COMPONENT_TEST_NAPI_THROW(env, ErrCode::RET_ERR_FAILED);
        return nullptr;
    }
    asyncContext->env = env;
    asyncContext->ret = ErrInfo { ErrCode::RET_OK, "" };
    return asyncContext;
}

ComponentTest::ComponentTestMatcherImpl* GetMatcher(napi_env env, napi_value napiMatcher)
{
    ComponentTest::ComponentTestMatcherImpl* matcherImpl = nullptr;
    napi_status status = napi_unwrap(env, napiMatcher, reinterpret_cast<void**>(&matcherImpl));
    if (status != napi_ok || !matcherImpl) {
        LOGE("%{public}s", "Failed to get unwrap ComponentTestMatcherImpl");
        COMPONENT_TEST_NAPI_THROW(env, ErrCode::RET_ERR_FAILED);
        return nullptr;
    }
    return matcherImpl;
}

std::string GetComponentTestEtsPosition()
{
    auto jsEngine = EngineHelper::GetCurrentEngine();
    std::string stack;
    CHECK_NULL_RETURN(jsEngine, "_ets_position");
    jsEngine->GetStackTrace(stack);
    LOGI("stack: %{public}s", stack.c_str());
    std::regex reg("\\((.*)\\)");
    std::smatch match;
    if (std::regex_search(stack, match, reg)) {
        LOGI("position %{public}s", match[1].str().c_str());
        return (match[1].str());
    }
    return "_ets_position";
}

napi_value CreateBusinessError(napi_env env, const ErrInfo& errInfo)
{
    napi_value result = nullptr;
    if (errInfo.errCode == ErrCode::RET_OK) {
        napi_get_undefined(env, &result);
    } else {
        napi_value errCode = nullptr;
        napi_create_int32(env, static_cast<int32_t>(errInfo.errCode), &errCode);
        napi_value eMsg = nullptr;
        napi_create_string_utf8(env, errInfo.message.data(), NAPI_AUTO_LENGTH, &eMsg);
        napi_create_error(env, nullptr, eMsg, &result);
        napi_set_named_property(env, result, "code", errCode);
    }
    return result;
}

napi_value NapiGetUndefined(napi_env env)
{
    napi_value result = nullptr;
    napi_get_undefined(env, &result);
    return result;
}

bool CheckAndParseStr(napi_env env, napi_value arg, std::string& recv, std::string& errMsg)
{
    if (arg == nullptr) {
        errMsg = "Parameter is null.";
        return false;
    }

    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, arg, &valueType);
    if (valueType != napi_string) {
        errMsg = "The type of parameter is not string";
        return false;
    }

    size_t msgLen = GetParamLen(env, arg) + 1;
    std::unique_ptr<char[]> message = std::make_unique<char[]>(msgLen);
    size_t ret = 0;
    if (napi_get_value_string_utf8(env, arg, message.get(), msgLen, &ret) != napi_ok) {
        errMsg = "Get string parameter value failed.";
        return false;
    }

    recv = message.get();
    return true;
}

bool CheckAndParseInt32(napi_env env, napi_value arg, int32_t& recv, std::string& errMsg)
{
    if (arg == nullptr) {
        errMsg = "Parameter is null.";
        return false;
    }

    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, arg, &valueType);
    if (valueType != napi_number) {
        errMsg = "The type of parameter is not number";
        return false;
    }

    napi_get_value_int32(env, arg, &recv);
    return true;
}

bool CheckAndParseUInt32(napi_env env, napi_value arg, uint32_t& recv, std::string& errMsg)
{
    if (arg == nullptr) {
        errMsg = "Parameter is null.";
        return false;
    }

    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, arg, &valueType);
    if (valueType != napi_number) {
        errMsg = "The type of parameter is not number";
        return false;
    }

    napi_get_value_uint32(env, arg, &recv);
    return true;
}

bool CheckAndParseBool(napi_env env, napi_value arg, bool& recv, std::string& errMsg)
{
    if (arg == nullptr) {
        errMsg = "Parameter is null.";
        return false;
    }

    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, arg, &valueType);
    if (valueType != napi_boolean) {
        errMsg = "The type of parameter is not boolean";
        return false;
    }

    napi_get_value_bool(env, arg, &recv);
    return true;
}

napi_status ExportEnumerator(napi_env env, napi_value exports, const EnumeratorDef& enumDef)
{
    NAPI_ASSERT_BASE(env, exports != nullptr, "Illegal export params", NAPI_ERR);
    napi_value enumerator;
    NAPI_CALL_BASE(env, napi_create_object(env, &enumerator), NAPI_ERR);
    for (size_t index = 0; index < enumDef.valueCount_; index++) {
        const auto& def = enumDef.values[index];
        napi_value prop = nullptr;
        NAPI_CALL_BASE(env, napi_create_uint32(env, def.value_, &prop), NAPI_ERR);
        NAPI_CALL_BASE(env, napi_set_named_property(env, enumerator, def.name_.data(), prop), NAPI_ERR);
    }
    NAPI_CALL_BASE(env, napi_set_named_property(env, exports, enumDef.name_.data(), enumerator), NAPI_ERR);
    return napi_ok;
}

} // namespace OHOS::Ace::Napi
