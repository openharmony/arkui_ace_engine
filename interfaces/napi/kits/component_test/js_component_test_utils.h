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

#ifndef OHOS_NAPI_ACE_COMPONENT_TEST_CONFIG_H
#define OHOS_NAPI_ACE_COMPONENT_TEST_CONFIG_H

#include <string_view>

#include "component_test/component_test_proxy.h"
#include "component_test/core/component_test_component_impl.h"
#include "component_test/core/component_test_matcher_impl.h"
#include "component_test/core/component_test_tester_impl.h"
#include "napi/native_api.h"
#include "napi/native_node_api.h"

namespace OHOS::Ace::Napi {
using ErrInfo = OHOS::Ace::ComponentTest::ErrInfo;
using ErrCode = OHOS::Ace::ComponentTest::ErrCode;

constexpr char TESTER_NAME[] = "Tester";
constexpr char MATCHER_NAME[] = "Matcher";
constexpr char COMPONENT_NAME[] = "Component";
constexpr char TEST_CASE_TYPE[] = "TestCaseType";
constexpr char TEST_CASE_SIZE[] = "TestCaseSize";
constexpr char TEST_CASE_LEVEL[] = "TestCaseLevel";
constexpr char MATCH_TYPE[] = "MatchType";
constexpr char UI_DIRECTION[] = "UiDirection";
constexpr napi_status NAPI_ERR = napi_status::napi_generic_failure;
constexpr size_t NAPI_MAX_BUF_LEN = 1024;
constexpr int32_t ACE_INSTANCE_ID = 0;
constexpr size_t ARG_COUNT_ZERO = 0;
constexpr size_t ARG_COUNT_ONE = 1;
constexpr size_t ARG_COUNT_TWO = 2;
constexpr size_t ARG_COUNT_THREE = 3;
constexpr size_t ARG_COUNT_FOUR = 4;
constexpr size_t ARG_COUNT_FIVE = 5;

struct ComponentTestAsyncCtx {
    napi_env env = nullptr;
    napi_async_work asyncWork = nullptr;
    napi_deferred deferred = nullptr;
    napi_ref callbackRef = nullptr;
    napi_value asyncResult = nullptr;
    ErrInfo ret = { ErrCode::RET_OK, "" };
    ComponentTest::ComponentTestMatcherImpl* matcherImpl = nullptr;
    ComponentTest::ComponentTestTesterImpl* testerImpl = nullptr;
    ComponentTest::ComponentTestComponentImpl* componentImpl = nullptr;
    OHOS::MMI::KeyCode keyCode = OHOS::MMI::KeyCode::KEY_UNKNOWN;
    std::vector<OHOS::MMI::KeyCode> keyCodes = {};
    uint32_t duration = 0;
    bool flingP = false;
    uint32_t delayMs = 0;
    uint32_t x = 0;
    uint32_t y = 0;
    uint32_t endx = 0;
    uint32_t endy = 0;
    uint32_t speed = 0;
    uint32_t stepLen = 0;
    int32_t deltaX = 0;
    int32_t deltaY = 0;
    ComponentTest::UiDirection direction = ComponentTest::UiDirection::TO_LEFT;
    NG::PointF from;
    NG::PointF to;
    float scale = 0;
    std::string text = "";
    const char* functionName;
};

ComponentTestAsyncCtx* CreateAsyncContext(napi_env env);

ComponentTest::ComponentTestMatcherImpl* GetMatcher(napi_env env, napi_value napiMatcher);

std::string GetComponentTestEtsPosition();

napi_value CreateBusinessError(napi_env env, const ErrInfo& errInfo);

#define COMPONENT_TEST_NAPI_THROW(env, errCode)                                               \
    do {                                                                                      \
        ErrInfo errInfo = QueryRetMsg(errCode);                                               \
        napi_value err = CreateBusinessError(env, errInfo);                                   \
        std::stringstream ss;                                                                 \
        ss << __FILE__ << "(" << __FUNCTION__ << ":" << __LINE__ << ")";                      \
        ComponentTest::ComponentTestManagerProxy::Record(                                     \
            std::string(errInfo.message), ss.str(), OHOS::Ace::ComponentTest::Result::ERROR); \
        napi_throw(env, err);                                                                 \
    } while (0)

#define COMPONENT_TEST_NAPI_ASSERT(env, cond, errCode) \
    do {                                               \
        if (!(cond)) {                                 \
            COMPONENT_TEST_NAPI_THROW(env, errCode);   \
            return NapiGetUndefined(env);              \
        }                                              \
    } while (0)

#define COMPONENT_TEST_NAPI_ASSERT_CUSTOM(env, cond, errCode, errMsg, retValue)      \
    while (!(cond)) {                                                                \
        napi_value err = CreateBusinessError(env, { errCode, errMsg });              \
        std::stringstream ss;                                                        \
        ss << __FILE__ << "(" << __FUNCTION__ << ":" << __LINE__ << ")";             \
        ComponentTest::ComponentTestManagerProxy::Record(                            \
            std::string(errMsg), ss.str(), OHOS::Ace::ComponentTest::Result::ERROR); \
        napi_throw(env, err);                                                        \
        return retValue;                                                             \
    }

#define COMPONENT_TEST_NAPI_JS_ASSERTION_FAIL(env, errCode) \
    do {                                                    \
        ErrInfo errInfo = QueryRetMsg(errCode);             \
        napi_value err = CreateBusinessError(env, errInfo); \
        napi_throw(env, err);                               \
        return NapiGetUndefined(env);                       \
    } while (0)

#define CHECK_COMPONENT_TEST_ENABLED()                                             \
    do {                                                                           \
        if (!ComponentTest::ComponentTestManagerProxy::IsComponentTestEnabled()) { \
            LOGW("Component test is disabled, cannot perform this operation");     \
            return nullptr;                                                        \
        }                                                                          \
    } while (0)

inline void ComponentTestRecord(bool cond, std::string info)
{
    if (!cond) {
        ComponentTest::ComponentTestManagerProxy::Record(
            info, GetComponentTestEtsPosition(), OHOS::Ace::ComponentTest::Result::FAIL);
    } else {
        ComponentTest::ComponentTestManagerProxy::Record(
            info, GetComponentTestEtsPosition(), OHOS::Ace::ComponentTest::Result::PASS);
    }
}

struct EnumValueDef {
    std::string_view name_;
    uint32_t value_;
};

inline std::string NapiValueToString(napi_env env, napi_value value)
{
    size_t bufSize = 0;
    napi_value napiString;
    char strBuffer[NAPI_MAX_BUF_LEN] = { 0 };
    NAPI_CALL(env, napi_coerce_to_string(env, value, &napiString));
    NAPI_CALL(env, napi_get_value_string_utf8(env, napiString, strBuffer, NAPI_MAX_BUF_LEN, &bufSize));
    return std::string(strBuffer, bufSize);
}

napi_value NapiGetUndefined(napi_env env);

bool CheckAndParseStr(napi_env env, napi_value arg, std::string& recv, std::string& errMsg);

bool CheckAndParseInt32(napi_env env, napi_value arg, int32_t& recv, std::string& errMsg);

bool CheckAndParseUInt32(napi_env env, napi_value arg, uint32_t& recv, std::string& errMsg);

bool CheckAndParseBool(napi_env env, napi_value arg, bool& recv, std::string& errMsg);

struct EnumeratorDef {
    std::string_view name_;
    const EnumValueDef* values;
    size_t valueCount_;
};

constexpr EnumValueDef TEST_CASE_TYPE_VALUES[] = {
    { "FUNCTION", 0 },
    { "PERFORMANCE", 1 },
    { "POWER", 2 },
    { "RELIABILITY", 3 },
    { "SECURITY", 4 },
    { "GLOBAL", 5 },
    { "COMPATIBILITY", 6 },
    { "USER", 7 },
    { "STANDARD", 8 },
    { "SAFETY", 9 },
    { "RESILIENCE", 10 },
};

constexpr EnumeratorDef TEST_CASE_TYPE_DEF = {
    TEST_CASE_TYPE,
    TEST_CASE_TYPE_VALUES,
    sizeof(TEST_CASE_TYPE_VALUES) / sizeof(EnumValueDef),
};

constexpr EnumValueDef TEST_CASE_SIZE_VALUES[] = {
    { "SMALLTEST", 0 },
    { "MEDIUMTEST", 1 },
    { "LARGETEST", 2 },
};

constexpr EnumeratorDef TEST_CASE_SIZE_DEF = {
    TEST_CASE_SIZE,
    TEST_CASE_SIZE_VALUES,
    sizeof(TEST_CASE_SIZE_VALUES) / sizeof(EnumValueDef),
};

constexpr EnumValueDef TEST_CASE_LEVEL_VALUES[] = {
    { "LEVEL0", 0 },
    { "LEVEL1", 1 },
    { "LEVEL2", 2 },
    { "LEVEL3", 3 },
    { "LEVEL4", 4 },
};

constexpr EnumeratorDef TEST_CASE_LEVEL_DEF = {
    TEST_CASE_LEVEL,
    TEST_CASE_LEVEL_VALUES,
    sizeof(TEST_CASE_LEVEL_VALUES) / sizeof(EnumValueDef),
};

constexpr EnumValueDef MATCH_TYPE_VALUES[] = {
    { "EQUALS", 0 },
    { "CONTAINS", 1 },
    { "STARTS_WITH", 2 },
    { "ENDS_WITH", 3 },
};

constexpr EnumeratorDef MATCH_TYPE_DEF = {
    MATCH_TYPE,
    MATCH_TYPE_VALUES,
    sizeof(MATCH_TYPE_VALUES) / sizeof(EnumValueDef),
};

constexpr EnumValueDef UI_DIRECTION_VALUES[] = {
    { "LEFT", 0 },
    { "RIGHT", 1 },
    { "UP", 2 },
    { "DOWN", 3 },
};

constexpr EnumeratorDef UI_DIRECTION_DEF = {
    UI_DIRECTION,
    UI_DIRECTION_VALUES,
    sizeof(UI_DIRECTION_VALUES) / sizeof(EnumValueDef),
};

napi_status ExportEnumerator(napi_env env, napi_value exports, const EnumeratorDef& enumDef);

} // namespace OHOS::Ace::Napi

#endif // OHOS_NAPI_ACE_COMPONENT_TEST_CONFIG_H
