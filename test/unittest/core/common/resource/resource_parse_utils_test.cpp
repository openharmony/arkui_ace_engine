/*
# Copyright (c) 2025 iSoftStone Information Technology (Group) Co.,Ltd.
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
*/

#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "test/mock/base/mock_system_properties.h"

#define protected public
#define private public
#include "core/common/container.h"
#include "core/common/resource/resource_object.h"
#include "core/common/resource/resource_parse_utils.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
class ResourceParseUtilsTest : public testing::Test {};
extern RefPtr<ResourceObject> CompleteResourceObject(const std::unique_ptr<JsonValue>& json);
extern std::string GetReplaceContentStr(
    int pos, const std::string& type, const std::vector<ResourceObjectParams> params, int32_t containCount);
extern void ReplaceHolder(std::string& originStr, const std::vector<ResourceObjectParams> params, int32_t containCount);

/**
 * @tc.name: ResourceParseUtilsTest001
 * @tc.desc: Test resourceParseUtils.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest001, TestSize.Level1)
{
    auto resourceAdapter = ResourceAdapter::Create();
    ResourceManager::GetInstance().AddResourceAdapter("com.example.test", "entry", 100000, resourceAdapter);
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();

    std::string result;
    CalcDimension dimension;
    Color color;
    double doubleRes;
    EXPECT_FALSE(ResourceParseUtils::ParseResString(resObj, result));

    std::vector<ResourceObjectParams> resObjParamsList;
    RefPtr<ResourceObject> resObjWithId = AceType::MakeRefPtr<ResourceObject>(100000, 100001,
        resObjParamsList, "", "", 100000);
    EXPECT_FALSE(ResourceParseUtils::ParseResString(resObjWithId, result));

    ResourceObjectParams params { .value = "test", .type = ResourceObjectParamType::STRING };
    resObjParamsList.push_back(params);
    RefPtr<ResourceObject> resObjWithName = AceType::MakeRefPtr<ResourceObject>(-1, -1,
        resObjParamsList, "com.example.test", "entry", 100000);
    EXPECT_FALSE(ResourceParseUtils::ParseResString(resObjWithName, result));
    EXPECT_TRUE(ResourceParseUtils::ParseResColor(resObjWithName, color));

    RefPtr<ResourceObject> resObjWithErrId = AceType::MakeRefPtr<ResourceObject>(100000, -1,
        resObjParamsList, "com.example.test", "entry", 100000);
    EXPECT_FALSE(ResourceParseUtils::ParseResourceToDouble(resObjWithErrId, doubleRes));

    g_isResourceDecoupling = false;
    EXPECT_FALSE(ResourceParseUtils::ParseResResource(resObjWithId, dimension));
    EXPECT_FALSE(ResourceParseUtils::ParseResDimensionNG(resObjWithErrId, dimension, DimensionUnit::VP));
    EXPECT_FALSE(ResourceParseUtils::ParseResColor(resObjWithName, color));
    g_isResourceDecoupling = true;

    ResourceManager::GetInstance().AddResourceAdapter("", "", Container::CurrentIdSafely(), resourceAdapter);
    RefPtr<ResourceObject> stringObj = AceType::MakeRefPtr<ResourceObject>(1, 10003,
        resObjParamsList, "", "", 100000);
    EXPECT_FALSE(ResourceParseUtils::ParseResResource(stringObj, dimension));

    RefPtr<ResourceObject> intObj = AceType::MakeRefPtr<ResourceObject>(1, 10007,
        resObjParamsList, "", "", 100000);
    EXPECT_TRUE(ResourceParseUtils::ParseResResource(intObj, dimension));

    RefPtr<ResourceObject> floatObj = AceType::MakeRefPtr<ResourceObject>(1, 10002,
        resObjParamsList, "", "", 100000);
    EXPECT_TRUE(ResourceParseUtils::ParseResResource(floatObj, dimension));
}

/**
 * @tc.name: ResourceParseUtilsTest002
 * @tc.desc: Test resourceParseUtils.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest002, TestSize.Level1)
{
    RefPtr<ResourceObject> resObj;
    std::vector<ResourceObjectParams> resObjParamsList;
    RefPtr<ResourceObject> resObjWithType = AceType::MakeRefPtr<ResourceObject>(-1, 10001,
        resObjParamsList, "", "", 100000);
    ResourceObjectParams params { .value = "test", .type = ResourceObjectParamType::STRING };
    resObjParamsList.push_back(params);
    RefPtr<ResourceObject> resObjWithParams = AceType::MakeRefPtr<ResourceObject>(-1, -1,
        resObjParamsList, "", "", 100000);
    std::vector<uint32_t> resIntArr;
    EXPECT_FALSE(ResourceParseUtils::ParseResIntegerArray(resObj, resIntArr));
    EXPECT_FALSE(ResourceParseUtils::ParseResIntegerArray(resObjWithType, resIntArr));

    std::vector<std::string> resStrArr;
    EXPECT_FALSE(ResourceParseUtils::ParseResStrArray(resObj, resStrArr));
    EXPECT_FALSE(ResourceParseUtils::ParseResStrArray(resObjWithType, resStrArr));

    EXPECT_FALSE(ResourceParseUtils::ParseResFontFamilies(resObj, resStrArr));
    EXPECT_TRUE(ResourceParseUtils::ParseResFontFamilies(resObjWithParams, resStrArr));

    Color color;
    EXPECT_FALSE(ResourceParseUtils::ParseResColor(resObj, color));
    EXPECT_TRUE(ResourceParseUtils::ParseResColor(resObjWithParams, color));

    std::u16string u16Str;
    EXPECT_FALSE(ResourceParseUtils::ParseResString(resObj, u16Str));
    EXPECT_FALSE(ResourceParseUtils::ParseResString(resObjWithParams, u16Str));

    std::string strRes;
    EXPECT_FALSE(ResourceParseUtils::ParseResString(resObj, strRes));
    EXPECT_FALSE(ResourceParseUtils::ParseResString(resObjWithParams, strRes));

    EXPECT_FALSE(ResourceParseUtils::ParseResMedia(resObj, strRes));
    EXPECT_FALSE(ResourceParseUtils::ParseResMedia(resObjWithType, strRes));

    bool boolRes;
    EXPECT_FALSE(ResourceParseUtils::ParseResBool(resObj, boolRes));
    EXPECT_FALSE(ResourceParseUtils::ParseResBool(resObjWithType, boolRes));

    double doubleRes;
    EXPECT_FALSE(ResourceParseUtils::ParseResourceToDouble(resObj, doubleRes));
    EXPECT_FALSE(ResourceParseUtils::ParseResourceToDouble(resObjWithParams, doubleRes));

    CalcDimension caclDimension;
    EXPECT_FALSE(ResourceParseUtils::ParseResDimensionNG(resObj, caclDimension, DimensionUnit::VP));
    EXPECT_TRUE(ResourceParseUtils::ParseResDimensionNG(resObjWithParams, caclDimension, DimensionUnit::VP));

    EXPECT_FALSE(ResourceParseUtils::ParseResDimension(resObj, caclDimension, DimensionUnit::VP));
    EXPECT_FALSE(ResourceParseUtils::ParseResDimension(resObjWithParams, caclDimension, DimensionUnit::VP));

    EXPECT_FALSE(ResourceParseUtils::ParseResResource(resObj, caclDimension));

    Dimension dimension;
    EXPECT_FALSE(ResourceParseUtils::ConvertFromResObjNG(resObj, dimension));
}

/**
 * @tc.name: ResourceParseUtilsTest003
 * @tc.desc: Test resourceParseUtils.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest003, TestSize.Level1)
{
    std::vector<ResourceObjectParams> resObjParamsList;
    ResourceObjectParams params { .value = "test", .type = ResourceObjectParamType::STRING };
    resObjParamsList.push_back(params);
    RefPtr<ResourceObject> resObjWithParams = AceType::MakeRefPtr<ResourceObject>(-1, -1,
        resObjParamsList, "", "", 100000);
    CalcDimension caclDimension;
    EXPECT_FALSE(ResourceParseUtils::ParseResResource(resObjWithParams, caclDimension));
}

/**
 * @tc.name: ResourceParseUtilsTest004
 * @tc.desc: Test resourceParseUtils.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ParseResColor with not object.
     * @tc.expect: ParseResColor return true.
     */
    auto resourceAdapter = ResourceAdapter::Create();
    ResourceManager::GetInstance().AddResourceAdapter("com.example.test", "entry", 100000, resourceAdapter);
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    Color color = Color::WHITE;
    resObj->SetColor(color);
    resObj->SetIsResource(false);
    resObj->SetColorMode(ColorMode::LIGHT);
    EXPECT_TRUE(ResourceParseUtils::ParseResColor(resObj, color));

    /**
     * @tc.steps: step2. ParseResColor with isReloading_ true.
     * @tc.expect: ParseResColor return true.
     */
    ResourceParseUtils::SetIsReloading(true);
    EXPECT_TRUE(ResourceParseUtils::ParseResColor(resObj, color));

    /**
     * @tc.steps: step3. ParseResColor with resId is -1.
     * @tc.expect: ParseResColor return true.
     */
    ResourceObjectParams params { .value = "test", .type = ResourceObjectParamType::STRING };
    std::vector<ResourceObjectParams> resObjParamsList;
    resObjParamsList.push_back(params);
    RefPtr<ResourceObject> resObjWithName = AceType::MakeRefPtr<ResourceObject>(-1, -1,
        resObjParamsList, "com.example.test", "entry", 100000);
    resObjWithName->SetColor(color);
    resObjWithName->SetIsResource(false);
    resObjWithName->SetColorMode(ColorMode::DARK);
    EXPECT_TRUE(ResourceParseUtils::ParseResColor(resObjWithName, color));
    ResourceParseUtils::SetIsReloading(false);
    EXPECT_TRUE(ResourceParseUtils::ParseResColor(resObjWithName, color));

    /**
     * @tc.steps: step4. ParseResColor with string type.
     * @tc.expect: ParseResColor return false.
     */
    RefPtr<ResourceObject> resObjWithStr = AceType::MakeRefPtr<ResourceObject>(1, 10003,
        resObjParamsList, "com.example.test", "entry", 100000);
    resObjWithStr->SetColor(color);
    ResourceParseUtils::SetIsReloading(true);
    EXPECT_FALSE(ResourceParseUtils::ParseResColor(resObjWithStr, color));
    ResourceParseUtils::SetIsReloading(false);
    EXPECT_FALSE(ResourceParseUtils::ParseResColor(resObjWithStr, color));

    /**
     * @tc.steps: step5. ParseResColor with integer type.
     * @tc.expect: ParseResColor return true.
     */
    RefPtr<ResourceObject> resObjWithInt = AceType::MakeRefPtr<ResourceObject>(1, 10007,
        resObjParamsList, "com.example.test", "entry", 100000);
    resObjWithInt->SetColor(color);
    ResourceParseUtils::SetIsReloading(true);
    EXPECT_TRUE(ResourceParseUtils::ParseResColor(resObjWithInt, color));
    ResourceParseUtils::SetIsReloading(false);
    EXPECT_TRUE(ResourceParseUtils::ParseResColor(resObjWithInt, color));

    /**
     * @tc.steps: step6. ParseResColor with string type.
     * @tc.expect: ParseResColor return true.
     */
    RefPtr<ResourceObject> resObjWithColor = AceType::MakeRefPtr<ResourceObject>(1, 10001,
        resObjParamsList, "com.example.test", "entry", 100000);
    resObjWithColor->SetColor(color);
    ResourceParseUtils::SetIsReloading(true);
    EXPECT_TRUE(ResourceParseUtils::ParseResColor(resObjWithColor, color));
    ResourceParseUtils::SetIsReloading(false);
    EXPECT_TRUE(ResourceParseUtils::ParseResColor(resObjWithColor, color));
}

/**
 * @tc.name: ResourceParseUtilsTest005
 * @tc.desc: Test resourceParseUtils.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ParseResColor with Color::WHITE.
     * @tc.expect: ParseResColor return Color::WHITE.
     */
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    Color color = Color::WHITE;
    resObj->SetColor(color);
    resObj->SetIsResource(false);
    ResourceParseUtils::SetIsReloading(false);
    resObj->SetColorMode(ColorMode::LIGHT);
    Color result;
    ResourceParseUtils::ParseResColor(resObj, result);
    EXPECT_EQ(color, result);
}

/**
 * @tc.name: ResourceParseUtilsTest006
 * @tc.desc: Test resourceParseUtils.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ParseResColor with different colormode.
     * @tc.expect: ParseResColor return True except colormode undefined.
     */
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    Color color = Color::WHITE;
    resObj->SetColor(color);
    resObj->SetIsResource(false);
    resObj->SetColorMode(ColorMode::COLOR_MODE_UNDEFINED);
    ResourceParseUtils::SetIsReloading(false);
    EXPECT_FALSE(ResourceParseUtils::ParseResColor(resObj, color));
    resObj->SetColorMode(ColorMode::DARK);
    EXPECT_TRUE(ResourceParseUtils::ParseResColor(resObj, color));
    ResourceParseUtils::SetIsReloading(true);
    EXPECT_TRUE(ResourceParseUtils::ParseResColor(resObj, color));
}

/**
 * @tc.name: ResourceParseUtilsTest007
 * @tc.desc: Test CompleteResourceObject.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a JSON object with valid data.
     * @tc.expect: CompleteResourceObject return nullptr.
     */
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    json->Put("id", 1);
    json->Put("type", 2);
    json->Put("params", 3);
    json->Put("bundleName", "test_bundle");
    json->Put("moduleName", "test_module");

    /**
     * @tc.steps: step2. Call the function.
     * @tc.expect: the function is be called.
     */
    auto result = CompleteResourceObject(json);

    /**
     * @tc.steps: step3. Verify the result.
     * @tc.expect: result is  nullptr.
     */
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: ResourceParseUtilsTest008
 * @tc.desc: Test CompleteResourceObject.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a JSON object with valid data.
     * @tc.expect: CompleteResourceObject return not nullptr and GetParams().size() is 0.
     */
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    json->Put("id", 11);
    json->Put("type", 22);
    json->Put("params", JsonUtil::CreateArray(true));
    json->Put("bundleName", "test_bundle2");
    json->Put("moduleName", "test_module2");

    /**
     * @tc.steps: step2. Call the function.
     * @tc.expect: the function is be called.
     */
    auto result = CompleteResourceObject(json);

    /**
     * @tc.steps: step3. Verify the result.
     * @tc.expect: GetParams().size() is  0.
     */
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(result->GetId(), 11);
    EXPECT_EQ(result->GetType(), 22);
    EXPECT_EQ(result->GetBundleName(), "\"test_bundle2\"");
    EXPECT_EQ(result->GetModuleName(), "\"test_module2\"");
    EXPECT_EQ(result->GetParams().size(), 0);
}

/**
 * @tc.name: ResourceParseUtilsTest009
 * @tc.desc: Test CompleteResourceObject.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a JSON object with valid data.
     * @tc.expect: CompleteResourceObject return not nullptr.
     */
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    json->Put("id", 111);
    json->Put("type", 222);
    json->Put("bundleName", "test_bundle3");
    json->Put("moduleName", "test_module3");
    auto paramsArray = JsonUtil::CreateArray(true);
    paramsArray->Put("0", "string_value");
    paramsArray->Put("1", 1);
    paramsArray->Put("2", 1.2);
    json->Put("params", std::move(paramsArray));

    /**
     * @tc.steps: step2. Call the function.
     * @tc.expect: the function is be called.
     */
    auto result = CompleteResourceObject(json);

    /**
     * @tc.steps: step3. Verify the result.
     * @tc.expect: GetParams().size() is not 0.
     */
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(result->GetParams().size(), 3);
    EXPECT_EQ(result->GetParams()[0].value, "\"string_value\"");
    EXPECT_EQ(result->GetParams()[0].type, ResourceObjectParamType::STRING);
    EXPECT_EQ(result->GetParams()[1].value, "1");
    EXPECT_EQ(result->GetParams()[1].type, ResourceObjectParamType::INT);
    EXPECT_EQ(result->GetParams()[2].value, "1.2");
    EXPECT_EQ(result->GetParams()[2].type, ResourceObjectParamType::FLOAT);
}

/**
 * @tc.name: ResourceParseUtilsTest010
 * @tc.desc: Test GetReplaceContentStr.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a params  with valid data.
     * @tc.expect: GetReplaceContentStr return "".
     */
    std::vector<ResourceObjectParams> params;
    int pos = 0;
    int32_t containCount = 0;
    std::string type = "d";

    /**
     * @tc.steps: step2. Call the function.
     * @tc.expect: the function is be called.
     */
    std::string result = GetReplaceContentStr(pos, type, params, containCount);

    /**
     * @tc.steps: step3. Verify the result.
     * @tc.expect: result is not "".
     */
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: ResourceParseUtilsTest011
 * @tc.desc: Test GetReplaceContentStr.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a params  with valid data.
     * @tc.expect: GetReplaceContentStr return not nullptr.
     */
    std::vector<ResourceObjectParams> params;
    ResourceObjectParams param { .value = "123", .type = ResourceObjectParamType::INT };
    params.push_back(param);
    int pos = 0;
    int32_t containCount = 0;
    std::string type = "d";
    std::string result = GetReplaceContentStr(pos, type, params, containCount);
    /**
     * @tc.steps: step2. Verify the result.
     * @tc.expect: result equalto value".
     */
    EXPECT_EQ(result, "123");

    std::vector<ResourceObjectParams> params2;
    ResourceObjectParams param2 { .value = "45.67", .type = ResourceObjectParamType::FLOAT };
    params2.push_back(param2);

    std::string result2 = GetReplaceContentStr(pos, type, params2, containCount);
    /**
     * @tc.steps: step3. Verify the result.
     * @tc.expect: result equalto value.
     */
    EXPECT_EQ(result2, "45.67");

    std::vector<ResourceObjectParams> params3;
    ResourceObjectParams param3 { .value = "567", .type = ResourceObjectParamType::NONE };
    params3.push_back(param3);
    std::string result3 = GetReplaceContentStr(pos, type, params3, containCount);

    /**
     * @tc.steps: step4. Verify the result.
     * @tc.expect: result not equalto value.
     */
    EXPECT_NE(result3, "567");
}

/**
 * @tc.name: ResourceParseUtilsTest012
 * @tc.desc: Test GetReplaceContentStr.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a params  with valid data.
     * @tc.expect: GetReplaceContentStr return not nullptr.
     */
    std::vector<ResourceObjectParams> params;
    ResourceObjectParams param { .value = "hello", .type = ResourceObjectParamType::STRING };
    params.push_back(param);
    int pos = 0;
    int32_t containCount = 0;
    std::string type = "s";
    std::string result = GetReplaceContentStr(pos, type, params, containCount);
    /**
     * @tc.steps: step2. Verify the result.
     * @tc.expect: result equalto value".
     */
    EXPECT_EQ(result, "hello");

    std::vector<ResourceObjectParams> params2;
    ResourceObjectParams param2 { .value = "world", .type = ResourceObjectParamType::NONE };
    params2.push_back(param2);

    std::string result2 = GetReplaceContentStr(pos, type, params2, containCount);
    /**
     * @tc.steps: step3. Verify the result.
     * @tc.expect: result not equalto value.
     */
    EXPECT_NE(result2, "world");
}

/**
 * @tc.name: ResourceParseUtilsTest013
 * @tc.desc: Test GetReplaceContentStr.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a params  with valid data.
     * @tc.expect: GetReplaceContentStr return not nullptr.
     */
    std::vector<ResourceObjectParams> params;
    ResourceObjectParams param { .value = "789", .type = ResourceObjectParamType::INT };
    params.push_back(param);
    int pos = 0;
    int32_t containCount = 0;
    std::string type = "f";
    std::string result = GetReplaceContentStr(pos, type, params, containCount);
    /**
     * @tc.steps: step2. Verify the result.
     * @tc.expect: result equalto value".
     */
    EXPECT_EQ(result, "789");

    std::vector<ResourceObjectParams> params2;
    ResourceObjectParams param2 { .value = "123.45", .type = ResourceObjectParamType::FLOAT };
    params2.push_back(param2);

    std::string result2 = GetReplaceContentStr(pos, type, params2, containCount);
    /**
     * @tc.steps: step3. Verify the result.
     * @tc.expect: result equalto value.
     */
    EXPECT_EQ(result2, "123.45");

    std::vector<ResourceObjectParams> params3;
    ResourceObjectParams param3 { .value = "hi", .type = ResourceObjectParamType::NONE };
    params3.push_back(param3);
    std::string result3 = GetReplaceContentStr(pos, type, params3, containCount);

    /**
     * @tc.steps: step4. Verify the result.
     * @tc.expect: result not equalto value.
     */
    EXPECT_NE(result3, "hi");
}

/**
 * @tc.name: ResourceParseUtilsTest014
 * @tc.desc: Test GetReplaceContentStr.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a params  with valid data.
     * @tc.expect: GetReplaceContentStr return "".
     */
    std::vector<ResourceObjectParams> params;
    ResourceObjectParams param { .value = "thanks", .type = ResourceObjectParamType::INT };
    params.push_back(param);
    int pos = 0;
    int32_t containCount = 0;
    std::string type = "x";

    std::string result = GetReplaceContentStr(pos, type, params, containCount);

    /**
     * @tc.steps: step3. Verify the result.
     * @tc.expect: result is not "".
     */
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: ResourceParseUtilsTest015
 * @tc.desc: Test ParseResStringObj.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a params  with valid data.
     * @tc.expect: params is empty().
     */
    std::vector<ResourceObjectParams> params;
    std::string result;
    int32_t type = static_cast<int32_t>(ResourceType::PLURAL);
    RefPtr<ThemeConstants> themeConstants = nullptr;
    RefPtr<ResourceAdapter> resourceAdapter = nullptr;
    RefPtr<ResourceWrapper> resourceWrapper = AceType::MakeRefPtr<ResourceWrapper>(themeConstants, resourceAdapter);

    bool success = ResourceParseUtils::ParseResStringObj(params, resourceWrapper, result, type);

    /**
     * @tc.steps: step3. Verify the result.
     * @tc.expect: result is false.
     */
    EXPECT_FALSE(success);
}

/**
 * @tc.name: ResourceParseUtilsTest016
 * @tc.desc: Test ParseResStringObj.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a params  with valid data.
     * @tc.expect: params is not empty().
     */
    std::vector<ResourceObjectParams> params;
    ResourceObjectParams param { .value = "12", .type = ResourceObjectParamType::INT };
    params.push_back(param);
    std::string result;
    int32_t type = static_cast<int32_t>(ResourceType::STRING);
    RefPtr<ThemeConstants> themeConstants = nullptr;
    RefPtr<ResourceAdapter> resourceAdapter = nullptr;
    RefPtr<ResourceWrapper> resourceWrapper = AceType::MakeRefPtr<ResourceWrapper>(themeConstants, resourceAdapter);

    bool success = ResourceParseUtils::ParseResStringObj(params, resourceWrapper, result, type);

    /**
     * @tc.steps: step3. Verify the result.
     * @tc.expect: result is true.
     */
    EXPECT_TRUE(success);
}

/**
 * @tc.name: ResourceParseUtilsTest017
 * @tc.desc: Test ParseResStringObj.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a params  with valid data.
     * @tc.expect: params is not empty().
     */
    std::vector<ResourceObjectParams> params;
    ResourceObjectParams param { .value = "17", .type = ResourceObjectParamType::INT };
    params.push_back(param);
    ResourceObjectParams param2 { .value = "test", .type = ResourceObjectParamType::STRING };
    params.push_back(param2);
    std::string result;
    int32_t type = static_cast<int32_t>(ResourceType::PLURAL);
    RefPtr<ThemeConstants> themeConstants = nullptr;
    RefPtr<ResourceAdapter> resourceAdapter = nullptr;
    RefPtr<ResourceWrapper> resourceWrapper = AceType::MakeRefPtr<ResourceWrapper>(themeConstants, resourceAdapter);

    bool success = ResourceParseUtils::ParseResStringObj(params, resourceWrapper, result, type);

    /**
     * @tc.steps: step3. Verify the result.
     * @tc.expect: result is false.
     */
    EXPECT_FALSE(success);
}

/**
 * @tc.name: ResourceParseUtilsTest018
 * @tc.desc: Test ParseResStringObj.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a params  with valid data.
     * @tc.expect: params is not empty().
     */
    std::vector<ResourceObjectParams> params;
    ResourceObjectParams param { .value = "18", .type = ResourceObjectParamType::INT };
    params.push_back(param);
    ResourceObjectParams param2 { .value = "1.8", .type = ResourceObjectParamType::FLOAT };
    params.push_back(param2);
    std::string result;
    int32_t type = static_cast<int32_t>(ResourceType::PLURAL);
    RefPtr<ThemeConstants> themeConstants = nullptr;
    RefPtr<ResourceAdapter> resourceAdapter = nullptr;
    RefPtr<ResourceWrapper> resourceWrapper = AceType::MakeRefPtr<ResourceWrapper>(themeConstants, resourceAdapter);

    bool success = ResourceParseUtils::ParseResStringObj(params, resourceWrapper, result, type);

    /**
     * @tc.steps: step3. Verify the result.
     * @tc.expect: result is true.
     */
    EXPECT_TRUE(success);
}

/**
 * @tc.name: ResourceParseUtilsTest019
 * @tc.desc: Test ParseResStringObj.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a params  with valid data.
     * @tc.expect: params is not empty().
     */
    std::vector<ResourceObjectParams> params;
    ResourceObjectParams param { .value = "19", .type = ResourceObjectParamType::INT };
    params.push_back(param);
    std::string result;
    int32_t type = static_cast<int32_t>(ResourceType::BOOLEAN);
    RefPtr<ThemeConstants> themeConstants = nullptr;
    RefPtr<ResourceAdapter> resourceAdapter = nullptr;
    RefPtr<ResourceWrapper> resourceWrapper = AceType::MakeRefPtr<ResourceWrapper>(themeConstants, resourceAdapter);

    bool success = ResourceParseUtils::ParseResStringObj(params, resourceWrapper, result, type);

    /**
     * @tc.steps: step3. Verify the result.
     * @tc.expect: result is true.
     */
    EXPECT_FALSE(success);
}

/**
 * @tc.name: ResourceParseUtilsTest020
 * @tc.desc: Test ParseResString.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a params  with valid data.
     * @tc.expect: resObj is null.
     */
    RefPtr<ResourceObject> resObj;
    std::string result;

    bool success = ResourceParseUtils::ParseResString(resObj, result);

    /**
     * @tc.steps: step2. Verify the result.
     * @tc.expect: result is true.
     */
    EXPECT_FALSE(success);

    /**
     * @tc.steps: step3. Create a params  with valid data.
     * @tc.expect: type is UNKNOWN_RESOURCE_TYPE, is -1
     */
    std::vector<ResourceObjectParams> params;
    RefPtr<ResourceObject> resObj2 = AceType::MakeRefPtr<ResourceObject>(1, -1, params, "", "", 100000);
    bool success2 = ResourceParseUtils::ParseResString(resObj2, result);

    /**
     * @tc.steps: step4. Verify the result.
     * @tc.expect: result is false.
     */
    EXPECT_FALSE(success2);
}

/**
 * @tc.name: ResourceParseUtilsTest021
 * @tc.desc: Test ParseResString.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a resObj  with valid data.
     * @tc.expect: id is -1.
     */
    std::string result;
    std::vector<ResourceObjectParams> params;
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(-1, 1, params, "", "", 100000);
    bool success = ResourceParseUtils::ParseResString(resObj, result);

    /**
     * @tc.steps: step2. Verify the result.
     * @tc.expect: result is false.
     */
    EXPECT_FALSE(success);

    /**
     * @tc.steps: step3. Create a resObj  with valid data.
     * @tc.expect: type is static_cast<int32_t>(ResourceType::STRING)
     */
    // std::vector<ResourceObjectParams> params;
    RefPtr<ResourceObject> resObj2 =
        AceType::MakeRefPtr<ResourceObject>(1, static_cast<int32_t>(ResourceType::STRING), params, "", "", 100000);
    bool success2 = ResourceParseUtils::ParseResString(resObj2, result);
    /**
     * @tc.steps: step3. Verify the result.
     * @tc.expect: result is false.
     */
    EXPECT_TRUE(success2);
}

/**
 * @tc.name: ResourceParseUtilsTest022
 * @tc.desc: Test ParseResString.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a resObj  with valid data.
     * @tc.expect: params is empty.
     */
    std::string result;
    int32_t type = static_cast<int32_t>(ResourceType::PLURAL);
    std::vector<ResourceObjectParams> params;
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(1, type, params, "", "", 100000);
    bool success = ResourceParseUtils::ParseResString(resObj, result);

    /**
     * @tc.steps: step2. Verify the result.
     * @tc.expect: result is false.
     */
    EXPECT_FALSE(success);

    /**
     * @tc.steps: step3. Create a resObj  with valid data.
     * @tc.expect: !IsNumberType() is true
     */
    std::vector<ResourceObjectParams> params2;
    ResourceObjectParams param2 { .value = "string", .type = ResourceObjectParamType::STRING };
    params2.push_back(param2);
    RefPtr<ResourceObject> resObj2 = AceType::MakeRefPtr<ResourceObject>(1, type, params2, "", "", 100000);
    bool success2 = ResourceParseUtils::ParseResString(resObj2, result);

    /**
     * @tc.steps: step4. Verify the result.
     * @tc.expect: result is false.
     */
    EXPECT_FALSE(success2);

    /**
     * @tc.steps: step5. Create a resObj  with valid data.
     * @tc.expect: !IsNumberType() is false
     */
    std::vector<ResourceObjectParams> params3;
    ResourceObjectParams param3 { .value = "123", .type = ResourceObjectParamType::INT };
    params3.push_back(param3);
    RefPtr<ResourceObject> resObj3 = AceType::MakeRefPtr<ResourceObject>(1, type, params3, "", "", 100000);
    bool success3 = ResourceParseUtils::ParseResString(resObj3, result);
    /**
     * @tc.steps: step6. Verify the result.
     * @tc.expect: result is true.
     */
    EXPECT_TRUE(success3);
}

/**
 * @tc.name: ResourceParseUtilsTest023
 * @tc.desc: Test ParseResString.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a resObj  with valid data.
     * @tc.expect: type is static_cast<int32_t>(ResourceType::FLOAT).
     */
    std::string result;
    std::vector<ResourceObjectParams> params;
    RefPtr<ResourceObject> resObj =
        AceType::MakeRefPtr<ResourceObject>(1, static_cast<int32_t>(ResourceType::FLOAT), params, "", "", 100000);
    bool success = ResourceParseUtils::ParseResString(resObj, result);

    /**
     * @tc.steps: step2. Verify the result.
     * @tc.expect: result is true.
     */
    EXPECT_TRUE(success);

    /**
     * @tc.steps: step3. Create a resObj  with valid data.
     * @tc.expect: type is static_cast<int32_t>(ResourceType::INTEGER)
     */
    RefPtr<ResourceObject> resObj2 =
        AceType::MakeRefPtr<ResourceObject>(1, static_cast<int32_t>(ResourceType::INTEGER), params, "", "", 100000);
    bool success2 = ResourceParseUtils::ParseResString(resObj2, result);

    /**
     * @tc.steps: step4. Verify the result.
     * @tc.expect: result is true.
     */
    EXPECT_TRUE(success2);

    /**
     * @tc.steps: step5. Create a resObj  with valid data.
     * @tc.expect: type is static_cast<int32_t>(ResourceType::SYMBOL)
     */
    RefPtr<ResourceObject> resObj3 =
        AceType::MakeRefPtr<ResourceObject>(1, static_cast<int32_t>(ResourceType::SYMBOL), params, "", "", 100000);
    bool success3 = ResourceParseUtils::ParseResString(resObj3, result);
    /**
     * @tc.steps: step6. Verify the result.
     * @tc.expect: result is false.
     */
    EXPECT_FALSE(success3);
}

/**
 * @tc.name: ResourceParseUtilsTest024
 * @tc.desc: Test ReplaceHolder.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a params  with valid data.
     * @tc.expect: containCount == size.
     */
    std::string originStr = "Hello";
    std::vector<ResourceObjectParams> params;
    ResourceObjectParams param { .value = "123", .type = ResourceObjectParamType::INT };
    params.push_back(param);
    int32_t containCount = 1;
    ReplaceHolder(originStr, params, containCount);

    /**
     * @tc.steps: step2. Verify the result.
     * @tc.expect: originStr is Hello.
     */
    EXPECT_EQ(originStr, "Hello");
}

/**
 * @tc.name: ResourceParseUtilsTest025
 * @tc.desc: Test ReplaceHolder.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a params  with valid data.
     * @tc.expect: firstMatch is true, shortHolderType is true.
     */
    std::string originStr = "Hello_%s";
    std::vector<ResourceObjectParams> params;
    ResourceObjectParams param { .value = "World", .type = ResourceObjectParamType::STRING };
    params.push_back(param);
    int32_t containCount = 0;
    ReplaceHolder(originStr, params, containCount);

    /**
     * @tc.steps: step2. Verify the result.
     * @tc.expect: originStr is Hello_World
     */
    EXPECT_EQ(originStr, "Hello_World");

    /**
     * @tc.steps: step3. Create a params  with valid data.
     * @tc.expect: first time firstMatch is true, and second time firstMatch is false, shortHolderType is true.
     */
    std::string originStr2 = "Hello_%s_Welcome_to_%s";
    std::vector<ResourceObjectParams> params2;
    ResourceObjectParams param21 { .value = "friend", .type = ResourceObjectParamType::STRING };
    params2.push_back(param21);
    ResourceObjectParams param22 { .value = "Earth", .type = ResourceObjectParamType::STRING };
    params2.push_back(param22);
    int32_t containCount2 = 0;
    ReplaceHolder(originStr2, params2, containCount2);

    /**
     * @tc.steps: step2. Verify the result.
     * @tc.expect: originStr is Hello_friend_Welcome_to_Earth
     */
    EXPECT_EQ(originStr2, "Hello_friend_Welcome_to_Earth");
    EXPECT_EQ(containCount2, 0);
}

/**
 * @tc.name: ResourceParseUtilsTest026
 * @tc.desc: Test ReplaceHolder.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a params  with valid data.
     * @tc.expect: shortHolderType ^ (pos.length() == 0) is true.
     */
    std::string originStr = "Hello_%s_and_%1$s";
    std::vector<ResourceObjectParams> params;
    ResourceObjectParams param01 { .value = "World", .type = ResourceObjectParamType::STRING };
    ResourceObjectParams param02 { .value = "Earth", .type = ResourceObjectParamType::STRING };
    params.push_back(param01);
    params.push_back(param02);
    int32_t containCount = 0;
    ReplaceHolder(originStr, params, containCount);

    /**
     * @tc.steps: step2. Verify the result.
     * @tc.expect: originStr is Hello_World_and_%1$s
     */
    EXPECT_EQ(originStr, "Hello_World_and_%1$s");

    /**
     * @tc.steps: step3. Create a params  with valid data.
     * @tc.expect: shortHolderType is false.
     */
    std::string originStr2 = "Hello_%2$s_and_%1$s";
    std::vector<ResourceObjectParams> params2;
    ResourceObjectParams param21 { .value = "friend", .type = ResourceObjectParamType::STRING };
    params2.push_back(param21);
    ResourceObjectParams param22 { .value = "Earth", .type = ResourceObjectParamType::STRING };
    params2.push_back(param22);
    int32_t containCount2 = 0;
    ReplaceHolder(originStr2, params2, containCount2);

    /**
     * @tc.steps: step4. Verify the result.
     * @tc.expect: originStr is Hello_Earth_and_friend
     */
    EXPECT_EQ(originStr2, "Hello_Earth_and_friend");
}

/**
 * @tc.name: ResourceParseUtilsTest027
 * @tc.desc: Test ParseResColorWithColorMode.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a params with invalid data.
     * @tc.expect: return false.
     */
    RefPtr<ResourceObject> resObj;
    ColorMode colorMode = ColorMode::LIGHT;
    Color result;
    EXPECT_FALSE(ResourceParseUtils::ParseResColorWithColorMode(resObj, result, colorMode));

    /**
     * @tc.steps: step2. Create a params with no instanceId.
     * @tc.expect: return false.
     */
    resObj = AceType::MakeRefPtr<ResourceObject>();
    resObj->SetInstanceId(-1);
    resObj->SetIsResource(false);
    resObj->SetColorMode(ColorMode::COLOR_MODE_UNDEFINED);
    EXPECT_FALSE(ResourceParseUtils::ParseResColorWithColorMode(resObj, result, colorMode));

    /**
     * @tc.steps: step2. Create a params with instanceId ok.
     * @tc.expect: return false.
     */
    resObj->SetInstanceId(100000);
    EXPECT_FALSE(ResourceParseUtils::ParseResColorWithColorMode(resObj, result, colorMode));
}
} // namespace OHOS::Ace
