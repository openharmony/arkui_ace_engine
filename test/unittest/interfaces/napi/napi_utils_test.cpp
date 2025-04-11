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

#include "gtest/gtest.h"
#include "vector"

#include "napi_runtime.cpp"
#include "core/common/resource/resource_manager.h"
#include "interfaces/napi/kits/utils/napi_utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

namespace {
const char TYPE_KEY[] = "type";
const char PARAMS_KEY[] = "params";
const char RESOURCE_ID_KEY[] = "id";
const char BUNDLE_NAME[] = "bundle";
const char MODULE_NAME[] = "module";
const char BUNDLE_NAME_KEY[] = "bundleName";
const char MODULE_NAME_KEY[] = "moduleName";
const char DYNAMIC_RES_STRING[] = "app.string.test";
constexpr int32_t DYNAMIC_ID = -1;
constexpr int32_t RESOURCE_ID = 16666666;
} // namespace

class NapiUtilsTest : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
    void SetUp() {};
    void TearDown() {};
};


napi_value CreateDynamicV2ResourceObject(napi_env env)
{
    napi_value typeNapi;
    napi_value resIdNapi;
    napi_value paramsNapi;
    napi_value resStringNapi = Napi::CreateNapiString(env, DYNAMIC_RES_STRING);
    napi_create_array(env, &paramsNapi);
    napi_set_element(env, paramsNapi, 0, resStringNapi);
    napi_create_int32(env, DYNAMIC_ID, &typeNapi);
    napi_create_int32(env, DYNAMIC_ID, &resIdNapi);
    napi_property_descriptor desc[] = {
        DECLARE_NAPI_DEFAULT_PROPERTY(RESOURCE_ID_KEY, resIdNapi),
        DECLARE_NAPI_DEFAULT_PROPERTY(TYPE_KEY, typeNapi),
        DECLARE_NAPI_DEFAULT_PROPERTY(PARAMS_KEY, paramsNapi),
        DECLARE_NAPI_DEFAULT_PROPERTY(BUNDLE_NAME_KEY, Napi::CreateNapiString(env, BUNDLE_NAME)),
        DECLARE_NAPI_DEFAULT_PROPERTY(MODULE_NAME_KEY, Napi::CreateNapiString(env, MODULE_NAME)),
    };
    napi_value resObj;
    napi_create_object_with_properties(env, &resObj, sizeof(desc) / sizeof(desc[0]), desc);
    return resObj;
}

napi_value CreateDynamicV1ResourceObject(napi_env env)
{
    napi_value paramsNapi;
    napi_create_array(env, &paramsNapi);
    napi_property_descriptor desc[] = {
        DECLARE_NAPI_DEFAULT_PROPERTY(RESOURCE_ID_KEY, Napi::CreateNapiString(env, DYNAMIC_RES_STRING)),
        DECLARE_NAPI_DEFAULT_PROPERTY(PARAMS_KEY, paramsNapi),
        DECLARE_NAPI_DEFAULT_PROPERTY(BUNDLE_NAME_KEY, Napi::CreateNapiString(env, BUNDLE_NAME)),
        DECLARE_NAPI_DEFAULT_PROPERTY(MODULE_NAME_KEY, Napi::CreateNapiString(env, MODULE_NAME)),
    };
    napi_value resObj;
    napi_create_object_with_properties(env, &resObj, sizeof(desc) / sizeof(desc[0]), desc);
    return resObj;
}

napi_value CreateBaseResourceObject(napi_env env, Napi::ResourceType type)
{
    napi_value typeNapi;
    napi_value resIdNapi;
    napi_value paramsNapi;
    napi_create_array(env, &paramsNapi);
    napi_create_int32(env, RESOURCE_ID, &resIdNapi);
    napi_create_int32(env, static_cast<int32_t>(type), &typeNapi);
    napi_property_descriptor desc[] = {
        DECLARE_NAPI_DEFAULT_PROPERTY(RESOURCE_ID_KEY, resIdNapi),
        DECLARE_NAPI_DEFAULT_PROPERTY(TYPE_KEY, typeNapi),
        DECLARE_NAPI_DEFAULT_PROPERTY(PARAMS_KEY, paramsNapi),
        DECLARE_NAPI_DEFAULT_PROPERTY(BUNDLE_NAME_KEY, Napi::CreateNapiString(env, BUNDLE_NAME)),
        DECLARE_NAPI_DEFAULT_PROPERTY(MODULE_NAME_KEY, Napi::CreateNapiString(env, MODULE_NAME)),
    };
    napi_value resObj;
    napi_create_object_with_properties(env, &resObj, sizeof(desc) / sizeof(desc[0]), desc);
    return resObj;
}

/**
 * @tc.name: NapiUtilsTest001
 * @tc.desc: GetParamLen
 * @tc.type: FUNC
 */
HWTEST_F(NapiUtilsTest, NapiUtilsTest001, TestSize.Level1)
{
    NativeEngineMock engine;
    /**
     * @tc.steps: step1. Create napi string
     * @tc.expected: Create success
     */
    std::string testStr = "test GetParamLen";
    napi_value napiTestStr = nullptr;

    napi_status status = napi_create_string_utf8(napi_env(engine), testStr.c_str(), testStr.length(), &napiTestStr);
    EXPECT_EQ(status, napi_ok);

    /**
     * @tc.steps: step2. Call GetParamLen
     * @tc.expected: Return value equals raw string length
     */
    size_t napiSize = Napi::GetParamLen(napi_env(engine), napiTestStr);
    EXPECT_EQ(napiSize, testStr.length());
}

/**
 * @tc.name: NapiUtilsTest002
 * @tc.desc: NapiStringToString
 * @tc.type: FUNC
 */
HWTEST_F(NapiUtilsTest, NapiUtilsTest002, TestSize.Level1)
{
    NativeEngineMock engine;
    /**
     * @tc.steps: step1. Create napi string
     * @tc.expected: Create success
     */
    std::string testStr = "test napi string";
    napi_value napiTestStr = nullptr;

    napi_status status = napi_create_string_utf8(napi_env(engine), testStr.c_str(), testStr.length(), &napiTestStr);
    EXPECT_EQ(status, napi_ok);

    /**
     * @tc.steps: step1. Call NapiStringToString
     * @tc.expected: Return value equals raw string
     */
    std::string retVal;
    Napi::NapiStringToString(napi_env(engine), napiTestStr, retVal);
    EXPECT_EQ(retVal, testStr);
}

/**
 * @tc.name: NapiUtilsTest003
 * @tc.desc: CheckResourceStruct
 * @tc.type: FUNC
 */
HWTEST_F(NapiUtilsTest, NapiUtilsTest003, TestSize.Level1)
{
    NativeEngineMock engine;
    /**
     * @tc.steps: step1. Create basic resource struct and check
     * @tc.expected: Create success and check equal success
     */
    napi_value baseStruct = CreateBaseResourceObject(napi_env(engine), Napi::ResourceType::STRING);
    auto resStruct1 = Napi::CheckResourceStruct(napi_env(engine), baseStruct);
    EXPECT_EQ(resStruct1, Napi::ResourceStruct::CONSTANT);

    /**
     * @tc.steps: step2. Create dynamic v1 resource struct and check
     * @tc.expected: Create success and check equal success
     */
    napi_value v1Struct = CreateDynamicV1ResourceObject(napi_env(engine));
    auto resStruct2 = Napi::CheckResourceStruct(napi_env(engine), v1Struct);
    EXPECT_EQ(resStruct2, Napi::ResourceStruct::DYNAMIC_V1);

    /**
     * @tc.steps: step3. Create dynamic v2 resource struct and check
     * @tc.expected: Create success and check equal success
     */
    napi_value v2Struct = CreateDynamicV2ResourceObject(napi_env(engine));
    auto resStruct3 = Napi::CheckResourceStruct(napi_env(engine), v2Struct);
    EXPECT_EQ(resStruct3, Napi::ResourceStruct::DYNAMIC_V2);
}

/**
 * @tc.name: NapiUtilsTest004
 * @tc.desc: ConvertResourceType
 * @tc.type: FUNC
 */
HWTEST_F(NapiUtilsTest, NapiUtilsTest004, TestSize.Level1)
{
    Napi::ResourceType resType;
    /**
     * @tc.steps: step1. Check color resource type
     * @tc.expected: Type check success
     */
    Napi::ConvertResourceType("color", resType);
    EXPECT_EQ(resType, Napi::ResourceType::COLOR);

    /**
     * @tc.steps: step2. Check media resource type
     * @tc.expected: Type check success
     */
    Napi::ConvertResourceType("media", resType);
    EXPECT_EQ(resType, Napi::ResourceType::MEDIA);

    /**
     * @tc.steps: step3. Check float resource type
     * @tc.expected: Type check success
     */
    Napi::ConvertResourceType("float", resType);
    EXPECT_EQ(resType, Napi::ResourceType::FLOAT);

    /**
     * @tc.steps: step4. Check string resource type
     * @tc.expected: Type check success
     */
    Napi::ConvertResourceType("string", resType);
    EXPECT_EQ(resType, Napi::ResourceType::STRING);

    /**
     * @tc.steps: step5. Check plural resource type
     * @tc.expected: Type check success
     */
    Napi::ConvertResourceType("plural", resType);
    EXPECT_EQ(resType, Napi::ResourceType::PLURAL);

    /**
     * @tc.steps: step6. Check pattern resource type
     * @tc.expected: Type check success
     */
    Napi::ConvertResourceType("pattern", resType);
    EXPECT_EQ(resType, Napi::ResourceType::PATTERN);

    /**
     * @tc.steps: step7. Check boolean resource type
     * @tc.expected: Type check success
     */
    Napi::ConvertResourceType("boolean", resType);
    EXPECT_EQ(resType, Napi::ResourceType::BOOLEAN);

    /**
     * @tc.steps: step8. Check integer resource type
     * @tc.expected: Type check success
     */
    Napi::ConvertResourceType("integer", resType);
    EXPECT_EQ(resType, Napi::ResourceType::INTEGER);

    /**
     * @tc.steps: step9. Check strarray resource type
     * @tc.expected: Type check success
     */
    Napi::ConvertResourceType("strarray", resType);
    EXPECT_EQ(resType, Napi::ResourceType::STRARRAY);

    /**
     * @tc.steps: step10. Check intarray resource type
     * @tc.expected: Type check success
     */
    Napi::ConvertResourceType("intarray", resType);
    EXPECT_EQ(resType, Napi::ResourceType::INTARRAY);
}

/**
 * @tc.name: NapiUtilsTest005
 * @tc.desc: ModifyResourceParam
 * @tc.type: FUNC
 */
HWTEST_F(NapiUtilsTest, NapiUtilsTest005, TestSize.Level1)
{
    NativeEngineMock engine;
    /**
     * @tc.steps: step1. Create v1 resource struct and check
     * @tc.expected: Create success and check equal success
     */
    napi_value v1Struct = CreateDynamicV1ResourceObject(napi_env(engine));
    auto resStruct = Napi::CheckResourceStruct(napi_env(engine), v1Struct);
    EXPECT_EQ(resStruct, Napi::ResourceStruct::DYNAMIC_V1);

    /**
     * @tc.steps: step2. Call ModifyResourceParam
     */
    std::string resName = DYNAMIC_RES_STRING;
    Napi::ResourceType resType = Napi::ResourceType::STRING;
    Napi::ModifyResourceParam(napi_env(engine), v1Struct, resType, resName);

    /**
     * @tc.steps: step3. Check resource params
     * @tc.expected: params contains resource name
     */
    napi_value valueParamsNapi;
    napi_get_property(
        napi_env(engine), v1Struct, Napi::CreateNapiString(napi_env(engine), PARAMS_KEY), &valueParamsNapi);
    napi_value resNameNApi = nullptr;
    napi_get_element(napi_env(engine), valueParamsNapi, 0, &resNameNApi);
    std::string resName1;
    Napi::NapiStringToString(napi_env(engine), resNameNApi, resName1);
    EXPECT_EQ(resName1, DYNAMIC_RES_STRING);
}

/**
 * @tc.name: NapiUtilsTest006
 * @tc.desc: ErrorToMessage
 * @tc.type: FUNC
 */
HWTEST_F(NapiUtilsTest, NapiUtilsTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get ERROR_CODE_PERMISSION_DENIED error msg
     * @tc.expected: Error msg correct
     */
    auto permissionDenyError = Napi::ErrorToMessage(ERROR_CODE_PERMISSION_DENIED);
    EXPECT_EQ(permissionDenyError, "Permission denied. ");

    /**
     * @tc.steps: step2. Get ERROR_CODE_PARAM_INVALID error msg
     * @tc.expected: Error msg correct
     */
    auto paramInvalidError = Napi::ErrorToMessage(ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(paramInvalidError, "Parameter error. ");

    /**
     * @tc.steps: step3. Get ERROR_CODE_SYSTEMCAP_ERROR error msg
     * @tc.expected: Error msg correct
     */
    auto systemCapError = Napi::ErrorToMessage(ERROR_CODE_SYSTEMCAP_ERROR);
    EXPECT_EQ(systemCapError, "Capability not supported. ");

    /**
     * @tc.steps: step4. Get ERROR_CODE_INTERNAL_ERROR error msg
     * @tc.expected: Error msg correct
     */
    auto codeInternalError = Napi::ErrorToMessage(ERROR_CODE_INTERNAL_ERROR);
    EXPECT_EQ(codeInternalError, "Internal error. ");

    /**
     * @tc.steps: step5. Get ERROR_CODE_URI_ERROR error msg
     * @tc.expected: Error msg correct
     */
    auto uriError = Napi::ErrorToMessage(ERROR_CODE_URI_ERROR);
    EXPECT_EQ(uriError, "Uri error. ");

    /**
     * @tc.steps: step6. Get ERROR_CODE_PAGE_STACK_FULL error msg
     * @tc.expected: Error msg correct
     */
    auto pageStackError = Napi::ErrorToMessage(ERROR_CODE_PAGE_STACK_FULL);
    EXPECT_EQ(pageStackError, "Page stack error. ");

    /**
     * @tc.steps: step7. Get ERROR_CODE_URI_ERROR_LITE error msg
     * @tc.expected: Error msg correct
     */
    auto uriLiteError = Napi::ErrorToMessage(ERROR_CODE_URI_ERROR_LITE);
    EXPECT_EQ(uriLiteError, "Uri error. ");

    /**
     * @tc.steps: step8. Get ERROR_CODE_DIALOG_CONTENT_ERROR error msg
     * @tc.expected: Error msg correct
     */
    auto dialogContentError = Napi::ErrorToMessage(ERROR_CODE_DIALOG_CONTENT_ERROR);
    EXPECT_EQ(dialogContentError, "Dialog content error. ");

    /**
     * @tc.steps: step9. Get ERROR_CODE_DIALOG_CONTENT_ALREADY_EXIST error msg
     * @tc.expected: Error msg correct
     */
    auto dialogContentExistError = Napi::ErrorToMessage(ERROR_CODE_DIALOG_CONTENT_ALREADY_EXIST);
    EXPECT_EQ(dialogContentExistError, "Dialog content already exist. ");

    /**
     * @tc.steps: step10. Get ERROR_CODE_DIALOG_CONTENT_NOT_FOUND error msg
     * @tc.expected: Error msg correct
     */
    auto dialogContentNotFoundError = Napi::ErrorToMessage(ERROR_CODE_DIALOG_CONTENT_NOT_FOUND);
    EXPECT_EQ(dialogContentNotFoundError, "Dialog content not found. ");

    /**
     * @tc.steps: step11. Get ERROR_CODE_TOAST_NOT_FOUND error msg
     * @tc.expected: Error msg correct
     */
    auto toastNotFoundError = Napi::ErrorToMessage(ERROR_CODE_TOAST_NOT_FOUND);
    EXPECT_EQ(toastNotFoundError, "Toast not found. ");
}

} // namespace OHOS::Ace
