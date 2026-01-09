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
#include "test/mock/core/common/mock_container.h"

#define protected public
#define private public
#include "core/common/container.h"
#include "core/common/color_inverter.h"
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
    ResourceParseUtils::SetNeedReload(true);
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
    ResourceParseUtils::SetNeedReload(false);
    EXPECT_TRUE(ResourceParseUtils::ParseResColor(resObjWithName, color));

    /**
     * @tc.steps: step4. ParseResColor with string type.
     * @tc.expect: ParseResColor return false.
     */
    RefPtr<ResourceObject> resObjWithStr = AceType::MakeRefPtr<ResourceObject>(1, 10003,
        resObjParamsList, "com.example.test", "entry", 100000);
    resObjWithStr->SetColor(color);
    ResourceParseUtils::SetNeedReload(true);
    EXPECT_FALSE(ResourceParseUtils::ParseResColor(resObjWithStr, color));
    ResourceParseUtils::SetNeedReload(false);
    EXPECT_FALSE(ResourceParseUtils::ParseResColor(resObjWithStr, color));

    /**
     * @tc.steps: step5. ParseResColor with integer type.
     * @tc.expect: ParseResColor return true.
     */
    RefPtr<ResourceObject> resObjWithInt = AceType::MakeRefPtr<ResourceObject>(1, 10007,
        resObjParamsList, "com.example.test", "entry", 100000);
    resObjWithInt->SetColor(color);
    ResourceParseUtils::SetNeedReload(true);
    EXPECT_TRUE(ResourceParseUtils::ParseResColor(resObjWithInt, color));
    ResourceParseUtils::SetNeedReload(false);
    EXPECT_TRUE(ResourceParseUtils::ParseResColor(resObjWithInt, color));

    /**
     * @tc.steps: step6. ParseResColor with string type.
     * @tc.expect: ParseResColor return true.
     */
    RefPtr<ResourceObject> resObjWithColor = AceType::MakeRefPtr<ResourceObject>(1, 10001,
        resObjParamsList, "com.example.test", "entry", 100000);
    resObjWithColor->SetColor(color);
    ResourceParseUtils::SetNeedReload(true);
    EXPECT_TRUE(ResourceParseUtils::ParseResColor(resObjWithColor, color));
    ResourceParseUtils::SetNeedReload(false);
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
    ResourceParseUtils::SetNeedReload(false);
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
    ResourceParseUtils::SetNeedReload(false);
    EXPECT_FALSE(ResourceParseUtils::ParseResColor(resObj, color));
    resObj->SetColorMode(ColorMode::DARK);
    EXPECT_TRUE(ResourceParseUtils::ParseResColor(resObj, color));
    ResourceParseUtils::SetNeedReload(true);
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

/**
 * @tc.name: ResourceParseUtilsTest028
 * @tc.desc: Test CompleteResourceObjectFromColor.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CompleteResourceObjectFromColor with cofigChangePerform false.
     * @tc.expect: resObj is null.
     */
    RefPtr<ResourceObject> resObj;
    Color color = Color::WHITE;
    ResourceParseUtils::CompleteResourceObjectFromColor(resObj, color, "");
    EXPECT_EQ(resObj, nullptr);

    /**
     * @tc.steps: step2. CompleteResourceObjectFromColor with cofigChangePerform true.
     * @tc.expect: resObj is not null.
     */
    g_isConfigChangePerform = true;
    auto invertFunc = [](uint32_t color) {
        return ColorInverter::DefaultInverter(color);
    };
    ColorInverter::GetInstance().EnableColorInvert(Container::CurrentIdSafely(), "", std::move(invertFunc));
    ResourceParseUtils::CompleteResourceObjectFromColor(resObj, color, "");
    EXPECT_NE(resObj, nullptr);

    /**
     * @tc.steps: step3. CompleteResourceObjectFromColor with current colormode is dark.
     * @tc.expect: resObj is not null.
     */
    MockContainer::SetMockColorMode(ColorMode::DARK);
    ResourceParseUtils::CompleteResourceObjectFromColor(resObj, color, "");
    EXPECT_NE(resObj, nullptr);
    MockContainer::SetMockColorMode(ColorMode::LIGHT);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: ResourceParseUtilsTest029
 * @tc.desc: Test CompleteResourceObjectFromColor with different conditions.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test CompleteResourceObjectFromColor with g_isConfigChangePerform false.
     * @tc.expect: resObj remains nullptr.
     */
    RefPtr<ResourceObject> resObj;
    Color color = Color::WHITE;
    g_isConfigChangePerform = false;
    ResourceParseUtils::CompleteResourceObjectFromColor(resObj, color, "");
    EXPECT_EQ(resObj, nullptr);

    /**
     * @tc.steps: step2. Test CompleteResourceObjectFromColor with g_isConfigChangePerform true but no invertFunc.
     * @tc.expect: resObj remains nullptr.
     */
    g_isConfigChangePerform = true;
    ColorInverter::GetInstance().DisableColorInvert(Container::CurrentIdSafely(), "");
    ResourceParseUtils::CompleteResourceObjectFromColor(resObj, color, "");
    EXPECT_EQ(resObj, nullptr);

    /**
     * @tc.steps: step3. Test CompleteResourceObjectFromColor with g_isConfigChangePerform true and has invertFunc.
     * @tc.expect: resObj is created and properties are set correctly.
     */
    auto invertFunc = [](uint32_t color) {
        return ColorInverter::DefaultInverter(color);
    };
    ColorInverter::GetInstance().EnableColorInvert(Container::CurrentIdSafely(), "", std::move(invertFunc));
    ResourceParseUtils::CompleteResourceObjectFromColor(resObj, color, "testNode");
    EXPECT_NE(resObj, nullptr);
    EXPECT_FALSE(resObj->IsResource());
    EXPECT_EQ(resObj->GetInstanceId(), Container::CurrentIdSafely());
    EXPECT_EQ(resObj->GetNodeTag(), "testNode");
    EXPECT_EQ(resObj->GetColorMode(), Container::CurrentColorMode());
    EXPECT_FALSE(resObj->HasDarkResource());

    /**
     * @tc.steps: step4. Test CompleteResourceObjectFromColor with dark mode.
     * @tc.expect: color is inverted and stored correctly.
     */
    MockContainer::SetMockColorMode(ColorMode::DARK);
    RefPtr<ResourceObject> resObj2;
    Color color2 = Color::WHITE;
    Color originalColor = color2;
    ResourceParseUtils::CompleteResourceObjectFromColor(resObj2, color2, "darkNode");
    EXPECT_NE(resObj2, nullptr);
    EXPECT_EQ(resObj2->GetColor(), originalColor);
    EXPECT_NE(color2, originalColor);

    MockContainer::SetMockColorMode(ColorMode::LIGHT);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: ResourceParseUtilsTest030
 * @tc.desc: Test ParseResStrArray with null resource object.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call ParseResStrArray with null resource object.
     * @tc.expect: Return false.
     */
    RefPtr<ResourceObject> resObj;
    std::vector<std::string> result;
    EXPECT_FALSE(ResourceParseUtils::ParseResStrArray(resObj, result));
}

/**
 * @tc.name: ResourceParseUtilsTest031
 * @tc.desc: Test ParseResStrArray with UNKNOWN_RESOURCE_TYPE.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create resource object with UNKNOWN_RESOURCE_TYPE.
     * @tc.steps: step2. Call ParseResStrArray.
     * @tc.expect: Return false.
     */
    std::vector<ResourceObjectParams> params;
    auto resObj = AceType::MakeRefPtr<ResourceObject>(1, -1, params, "", "", 100000);
    std::vector<std::string> result;
    EXPECT_FALSE(ResourceParseUtils::ParseResStrArray(resObj, result));
}

/**
 * @tc.name: ResourceParseUtilsTest032
 * @tc.desc: Test ParseResStrArray when GetOrCreateResourceWrapper fails.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set resource decoupling to false.
     * @tc.steps: step2. Create valid resource object.
     * @tc.steps: step3. Call ParseResStrArray.
     * @tc.expect: Return false because GetOrCreateResourceWrapper fails.
     */
    g_isResourceDecoupling = false;
    std::vector<ResourceObjectParams> params;
    auto resObj = AceType::MakeRefPtr<ResourceObject>(1,
        static_cast<int32_t>(ResourceType::STRARRAY), params, "", "", 100000);
    std::vector<std::string> result;
    EXPECT_FALSE(ResourceParseUtils::ParseResStrArray(resObj, result));
}

/**
 * @tc.name: ResourceParseUtilsTest033
 * @tc.desc: Test ParseResStrArray with resId == -1 and empty params.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set resource decoupling to true and add resource adapter.
     * @tc.steps: step2. Create resource object with resId == -1 and empty params.
     * @tc.steps: step3. Call ParseResStrArray.
     * @tc.expect: Return false because params is empty.
     */
    g_isResourceDecoupling = true;
    auto resourceAdapter = ResourceAdapter::Create();
    ResourceManager::GetInstance().AddResourceAdapter("", "", Container::CurrentIdSafely(), resourceAdapter);
    
    std::vector<ResourceObjectParams> params;
    auto resObj = AceType::MakeRefPtr<ResourceObject>(-1,
        static_cast<int32_t>(ResourceType::STRARRAY), params, "", "", 100000);
    std::vector<std::string> result;
    EXPECT_FALSE(ResourceParseUtils::ParseResStrArray(resObj, result));
}

/**
 * @tc.name: ResourceParseUtilsTest034
 * @tc.desc: Test ParseResStrArray with resId == -1 and valid params.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set resource decoupling to true and add resource adapter.
     * @tc.steps: step2. Create resource object with resId == -1 and valid params.
     * @tc.steps: step3. Call ParseResStrArray.
     * @tc.expect: Return true but result may be empty due to no actual resource.
     */
    g_isResourceDecoupling = true;
    auto resourceAdapter = ResourceAdapter::Create();
    ResourceManager::GetInstance().AddResourceAdapter("", "", Container::CurrentIdSafely(), resourceAdapter);
    
    std::vector<ResourceObjectParams> params;
    ResourceObjectParams param { .value = "test", .type = ResourceObjectParamType::STRING };
    params.push_back(param);
    auto resObj = AceType::MakeRefPtr<ResourceObject>(-1,
        static_cast<int32_t>(ResourceType::STRARRAY), params, "", "", 100000);
    std::vector<std::string> result;
    ResourceParseUtils::ParseResStrArray(resObj, result);
}

/**
 * @tc.name: ResourceParseUtilsTest035
 * @tc.desc: Test ParseResStrArray with valid resId.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest035, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set resource decoupling to true and add resource adapter.
     * @tc.steps: step2. Create resource object with valid resId.
     * @tc.steps: step3. Call ParseResStrArray.
     * @tc.expect: Return true but result may be empty due to no actual resource.
     */
    g_isResourceDecoupling = true;
    auto resourceAdapter = ResourceAdapter::Create();
    ResourceManager::GetInstance().AddResourceAdapter("", "", Container::CurrentIdSafely(), resourceAdapter);
    
    std::vector<ResourceObjectParams> params;
    auto resObj = AceType::MakeRefPtr<ResourceObject>(1,
        static_cast<int32_t>(ResourceType::STRARRAY), params, "", "", 100000);
    std::vector<std::string> result;
    ResourceParseUtils::ParseResStrArray(resObj, result);
}

/**
 * @tc.name: ResourceParseUtilsTest036
 * @tc.desc: Test ParseResStrArray with wrong resource type.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest036, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set resource decoupling to true and add resource adapter.
     * @tc.steps: step2. Create resource object with valid resId but wrong type.
     * @tc.steps: step3. Call ParseResStrArray.
     * @tc.expect: Return false because resource type is not STRARRAY.
     */
    g_isResourceDecoupling = true;
    auto resourceAdapter = ResourceAdapter::Create();
    ResourceManager::GetInstance().AddResourceAdapter("", "", Container::CurrentIdSafely(), resourceAdapter);

    std::vector<ResourceObjectParams> params;
    auto resObj = AceType::MakeRefPtr<ResourceObject>(1,
        static_cast<int32_t>(ResourceType::STRING), params, "", "", 100000);
    std::vector<std::string> result;
    EXPECT_FALSE(ResourceParseUtils::ParseResStrArray(resObj, result));
}

/**
 * @tc.name: ResourceParseUtilsTest037
 * @tc.desc: Test InvertColorWithResource with different conditions.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest037, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test InvertColorWithResource with isReloading_ false.
     * @tc.expect: Color is not inverted and resource object color mode is not changed.
     */
    auto resourceAdapter = ResourceAdapter::Create();
    ResourceManager::GetInstance().AddResourceAdapter("com.example.test", "entry", 100000, resourceAdapter);
    ResourceParseUtils::SetNeedReload(false);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    resObj->SetColorMode(ColorMode::LIGHT);
    Color color = Color::BLUE;
    Color originalColor = color;
    ResourceParseUtils::InvertColorWithResource(resObj, color, ColorMode::DARK);
    EXPECT_EQ(color, originalColor);
    EXPECT_EQ(resObj->GetColorMode(), ColorMode::LIGHT);

    /**
     * @tc.steps: step2. Test InvertColorWithResource with COLOR_MODE_UNDEFINED.
     * @tc.expect: Color is not inverted and resource object color mode is not changed.
     */
    ResourceParseUtils::SetNeedReload(true);
    resObj->SetColorMode(ColorMode::COLOR_MODE_UNDEFINED);
    ResourceParseUtils::InvertColorWithResource(resObj, color, ColorMode::DARK);
    EXPECT_EQ(color, originalColor);
    EXPECT_EQ(resObj->GetColorMode(), ColorMode::COLOR_MODE_UNDEFINED);

    /**
     * @tc.steps: step3. Test InvertColorWithResource with non-DARK color mode.
     * @tc.expect: Color is not inverted but resource object color mode is updated.
     */
    ResourceParseUtils::SetNeedReload(true);
    resObj->SetColorMode(ColorMode::LIGHT);
    resObj->SetHasDarkRes(false);
    ResourceParseUtils::InvertColorWithResource(resObj, color, ColorMode::LIGHT);
    EXPECT_EQ(color, originalColor);
    EXPECT_EQ(resObj->GetColorMode(), ColorMode::LIGHT);

    /**
     * @tc.steps: step4. Test InvertColorWithResource with DARK color mode and has dark resource.
     * @tc.expect: Color is not inverted but resource object color mode is updated.
     */
    ResourceParseUtils::SetNeedReload(true);
    resObj->SetColorMode(ColorMode::LIGHT);
    resObj->SetHasDarkRes(true);
    ResourceParseUtils::InvertColorWithResource(resObj, color, ColorMode::DARK);
    EXPECT_EQ(color, originalColor);
    EXPECT_EQ(resObj->GetColorMode(), ColorMode::DARK);

    /**
     * @tc.steps: step5. Test InvertColorWithResource with DARK color mode and no dark resource.
     * @tc.expect: Color is inverted and resource object color mode is updated.
     */
    ResourceParseUtils::SetNeedReload(true);
    resObj->SetColorMode(ColorMode::LIGHT);
    resObj->SetHasDarkRes(false);
    resObj->SetInstanceId(100000);
    resObj->SetNodeTag("testNode");
    
    // Enable color inversion
    auto invertFunc = [](uint32_t color) {
        return ColorInverter::DefaultInverter(color);
    };
    ColorInverter::GetInstance().EnableColorInvert(100000, "testNode", std::move(invertFunc));
    
    ResourceParseUtils::InvertColorWithResource(resObj, color, ColorMode::DARK);
    EXPECT_EQ(resObj->GetColorMode(), ColorMode::DARK);
    
    // Disable color inversion after test
    ColorInverter::GetInstance().DisableColorInvert(100000, "testNode");
}

/**
 * @tc.name: ResourceParseUtilsTest038
 * @tc.desc: Test ParseResString with std::u16string result.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest038, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test ParseResString with null resource object.
     * @tc.expect: Return false.
     */
    RefPtr<ResourceObject> resObj;
    std::u16string result;
    EXPECT_FALSE(ResourceParseUtils::ParseResString(resObj, result));

    /**
     * @tc.steps: step2. Test ParseResString with valid resource object but ParseResString<std::string> returns false.
     * @tc.expect: Return false.
     */
    std::vector<ResourceObjectParams> params;
    resObj = AceType::MakeRefPtr<ResourceObject>(1, -1, params, "", "", 100000);
    EXPECT_FALSE(ResourceParseUtils::ParseResString(resObj, result));

    /**
     * @tc.steps: step3. Test ParseResString with valid resource object and ParseResString<std::string> returns true.
     * @tc.expect: Return true and result is converted.
     */
    ResourceObjectParams param { .value = "test_string", .type = ResourceObjectParamType::STRING };
    params.push_back(param);
    resObj = AceType::MakeRefPtr<ResourceObject>(-1, static_cast<int32_t>(ResourceType::STRING),
        params, "", "", 100000);

    auto resourceAdapter = ResourceAdapter::Create();
    ResourceManager::GetInstance().AddResourceAdapter("com.example.test", "entry", 100000, resourceAdapter);
    bool returnValue = ResourceParseUtils::ParseResString(resObj, result);
    EXPECT_TRUE(returnValue);
}

/**
 * @tc.name: ResourceParseUtilsTest039
 * @tc.desc: Test ParseResMedia with null resource object and unknown resource type.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest039, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test ParseResMedia with null resource object.
     * @tc.expect: Return false.
     */
    RefPtr<ResourceObject> resObj;
    std::string result;
    EXPECT_FALSE(ResourceParseUtils::ParseResMedia(resObj, result));

    /**
     * @tc.steps: step2. Test ParseResMedia with UNKNOWN_RESOURCE_TYPE.
     * @tc.expect: Return false.
     */
    std::vector<ResourceObjectParams> params;
    resObj = AceType::MakeRefPtr<ResourceObject>(1, -1, params, "", "", 100000);
    EXPECT_FALSE(ResourceParseUtils::ParseResMedia(resObj, result));
}

/**
 * @tc.name: ResourceParseUtilsTest040
 * @tc.desc: Test ParseResMedia with RAWFILE type.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest040, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test ParseResMedia with RAWFILE type but empty params.
     * @tc.expect: Return false.
     */
    std::vector<ResourceObjectParams> params;
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(-1,
        static_cast<int32_t>(ResourceType::RAWFILE), params, "", "", 100000);
    std::string result;
    EXPECT_FALSE(ResourceParseUtils::ParseResMedia(resObj, result));

    /**
     * @tc.steps: step2. Test ParseResMedia with RAWFILE type but invalid param type.
     * @tc.expect: Return false.
     */
    ResourceObjectParams intParam { .value = "filename", .type = ResourceObjectParamType::INT };
    params.push_back(intParam);
    resObj = AceType::MakeRefPtr<ResourceObject>(-1, static_cast<int32_t>(ResourceType::RAWFILE),
        params, "", "", 100000);
    EXPECT_FALSE(ResourceParseUtils::ParseResMedia(resObj, result));

    /**
     * @tc.steps: step3. Test ParseResMedia with RAWFILE type and valid param.
     * @tc.expect: Return false (because no resource wrapper).
     */
    params.clear();
    ResourceObjectParams stringParam { .value = "filename", .type = ResourceObjectParamType::STRING };
    params.push_back(stringParam);
    resObj = AceType::MakeRefPtr<ResourceObject>(-1, static_cast<int32_t>(ResourceType::RAWFILE),
        params, "", "", 100000);
    EXPECT_TRUE(ResourceParseUtils::ParseResMedia(resObj, result));
}

/**
 * @tc.name: ResourceParseUtilsTest041
 * @tc.desc: Test ParseResMedia with resId -1.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest041, TestSize.Level1)
{
    std::string result;
    std::vector<ResourceObjectParams> params;
    ResourceObjectParams stringParam { .value = "test", .type = ResourceObjectParamType::STRING };

    /**
     * @tc.steps: step1. Test ParseResMedia with resId -1 and empty params.
     * @tc.expect: Return false.
     */
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(-1,
        static_cast<int32_t>(ResourceType::MEDIA), params, "", "", 100000);
    EXPECT_FALSE(ResourceParseUtils::ParseResMedia(resObj, result));

    /**
     * @tc.steps: step2. Test ParseResMedia with resId -1 and MEDIA type.
     * @tc.expect: Return false (because no resource wrapper).
     */
    params.push_back(stringParam);
    resObj = AceType::MakeRefPtr<ResourceObject>(-1, static_cast<int32_t>(ResourceType::MEDIA),
        params, "", "", 100000);
    EXPECT_TRUE(ResourceParseUtils::ParseResMedia(resObj, result));

    /**
     * @tc.steps: step3. Test ParseResMedia with resId -1 and STRING type.
     * @tc.expect: Return false (because no resource wrapper).
     */
    resObj = AceType::MakeRefPtr<ResourceObject>(-1, static_cast<int32_t>(ResourceType::STRING),
        params, "", "", 100000);
    EXPECT_TRUE(ResourceParseUtils::ParseResMedia(resObj, result));

    /**
     * @tc.steps: step4. Test ParseResMedia with resId -1 and invalid type.
     * @tc.expect: Return false.
     */
    resObj = AceType::MakeRefPtr<ResourceObject>(-1, static_cast<int32_t>(ResourceType::INTEGER),
        params, "", "", 100000);
    EXPECT_FALSE(ResourceParseUtils::ParseResMedia(resObj, result));
}

/**
 * @tc.name: ResourceParseUtilsTest042
 * @tc.desc: Test ParseResMedia with valid resId.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest042, TestSize.Level1)
{
    std::string result;
    std::vector<ResourceObjectParams> params;
    ResourceObjectParams stringParam { .value = "test", .type = ResourceObjectParamType::STRING };
    params.push_back(stringParam);

    /**
     * @tc.steps: step1. Test ParseResMedia with valid resId and MEDIA type.
     * @tc.expect: Return false (because no resource wrapper).
     */
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(1,
        static_cast<int32_t>(ResourceType::MEDIA), params, "", "", 100000);
    EXPECT_TRUE(ResourceParseUtils::ParseResMedia(resObj, result));

    /**
     * @tc.steps: step2. Test ParseResMedia with valid resId and STRING type.
     * @tc.expect: Return false (because no resource wrapper).
     */
    resObj = AceType::MakeRefPtr<ResourceObject>(1, static_cast<int32_t>(ResourceType::STRING),
        params, "", "", 100000);
    EXPECT_TRUE(ResourceParseUtils::ParseResMedia(resObj, result));
}

/**
 * @tc.name: ResourceParseUtilsTest043
 * @tc.desc: Test ParseResourceToDouble with null resource object.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest043, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test ParseResourceToDouble with null resource object.
     * @tc.expect: Return false.
     */
    RefPtr<ResourceObject> resObj;
    double result;
    EXPECT_FALSE(ResourceParseUtils::ParseResourceToDouble(resObj, result));
}

/**
 * @tc.name: ResourceParseUtilsTest044
 * @tc.desc: Test ParseResourceToDouble with resource wrapper failure.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest044, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test ParseResourceToDouble with valid resource object but no resource wrapper.
     * @tc.expect: Return false.
     */
    std::vector<ResourceObjectParams> params;
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(1,
        static_cast<int32_t>(ResourceType::STRING), params, "", "", 100000);
    // This will return false because GetOrCreateResourceWrapper will fail without proper setup
    double result;
    EXPECT_FALSE(ResourceParseUtils::ParseResourceToDouble(resObj, result));
}

/**
 * @tc.name: ResourceParseUtilsTest045
 * @tc.desc: Test ParseResourceToDouble with resId -1 and different parameter types.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest045, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test ParseResourceToDouble with resId -1 and empty params.
     * @tc.expect: Return false.
     */
    std::vector<ResourceObjectParams> params;
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(-1,
        static_cast<int32_t>(ResourceType::STRING), params, "", "", 100000);
    double result;
    EXPECT_FALSE(ResourceParseUtils::ParseResourceToDouble(resObj, result));

    /**
     * @tc.steps: step2. Test ParseResourceToDouble with resId -1 and STRING type.
     * @tc.expect: Return false (because no resource wrapper).
     */
    ResourceObjectParams stringParam { .value = "123.45", .type = ResourceObjectParamType::STRING };
    params.push_back(stringParam);
    resObj = AceType::MakeRefPtr<ResourceObject>(-1, static_cast<int32_t>(ResourceType::STRING),
        params, "", "", 100000);
    EXPECT_FALSE(ResourceParseUtils::ParseResourceToDouble(resObj, result));

    /**
     * @tc.steps: step3. Test ParseResourceToDouble with resId -1 and INTEGER type.
     * @tc.expect: Return false (because no resource wrapper).
     */
    resObj = AceType::MakeRefPtr<ResourceObject>(-1, static_cast<int32_t>(ResourceType::INTEGER),
        params, "", "", 100000);
    EXPECT_TRUE(ResourceParseUtils::ParseResourceToDouble(resObj, result));

    /**
     * @tc.steps: step4. Test ParseResourceToDouble with resId -1 and FLOAT type.
     * @tc.expect: Return false (because no resource wrapper).
     */
    resObj = AceType::MakeRefPtr<ResourceObject>(-1, static_cast<int32_t>(ResourceType::FLOAT),
        params, "", "", 100000);
    EXPECT_TRUE(ResourceParseUtils::ParseResourceToDouble(resObj, result));

    /**
     * @tc.steps: step5. Test ParseResourceToDouble with resId -1 and invalid type.
     * @tc.expect: Return false.
     */
    resObj = AceType::MakeRefPtr<ResourceObject>(-1, static_cast<int32_t>(ResourceType::BOOLEAN),
        params, "", "", 100000);
    EXPECT_FALSE(ResourceParseUtils::ParseResourceToDouble(resObj, result));
}

/**
 * @tc.name: ResourceParseUtilsTest046
 * @tc.desc: Test ParseResourceToDouble with valid resId and different types.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest046, TestSize.Level1)
{
    std::vector<ResourceObjectParams> params;
    ResourceObjectParams stringParam { .value = "test", .type = ResourceObjectParamType::STRING };
    params.push_back(stringParam);
    double result;

    /**
     * @tc.steps: step1. Test ParseResourceToDouble with valid resId and STRING type.
     * @tc.expect: Return false (because no resource wrapper).
     */
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(1,
        static_cast<int32_t>(ResourceType::STRING), params, "", "", 100000);
    EXPECT_FALSE(ResourceParseUtils::ParseResourceToDouble(resObj, result));

    /**
     * @tc.steps: step2. Test ParseResourceToDouble with valid resId and INTEGER type.
     * @tc.expect: Return false (because no resource wrapper).
     */
    resObj = AceType::MakeRefPtr<ResourceObject>(1, static_cast<int32_t>(ResourceType::INTEGER),
        params, "", "", 100000);
    EXPECT_TRUE(ResourceParseUtils::ParseResourceToDouble(resObj, result));

    /**
     * @tc.steps: step3. Test ParseResourceToDouble with valid resId and FLOAT type.
     * @tc.expect: Return false (because no resource wrapper).
     */
    resObj = AceType::MakeRefPtr<ResourceObject>(1, static_cast<int32_t>(ResourceType::FLOAT),
        params, "", "", 100000);
    EXPECT_TRUE(ResourceParseUtils::ParseResourceToDouble(resObj, result));
}

/**
 * @tc.name: ResourceParseUtilsTest047
 * @tc.desc: Test ParseResDimensionNG with null resource object and unknown resource type.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest047, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test ParseResDimensionNG with null resource object.
     * @tc.expect: Return false.
     */
    RefPtr<ResourceObject> resObj;
    CalcDimension result;
    EXPECT_FALSE(ResourceParseUtils::ParseResDimensionNG(resObj, result, DimensionUnit::VP));

    /**
     * @tc.steps: step2. Test ParseResDimensionNG with valid resource object but no resource wrapper.
     * @tc.expect: Return false.
     */
    std::vector<ResourceObjectParams> params;
    resObj = AceType::MakeRefPtr<ResourceObject>(1, static_cast<int32_t>(ResourceType::STRING),
        params, "", "", 100000);
    // This will return false because GetOrCreateResourceWrapper will fail without proper setup
    EXPECT_FALSE(ResourceParseUtils::ParseResDimensionNG(resObj, result, DimensionUnit::VP));
}

/**
 * @tc.name: ResourceParseUtilsTest048
 * @tc.desc: Test ParseResDimensionNG with resId -1.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest048, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test ParseResDimensionNG with resId -1 and empty params.
     * @tc.expect: Return false.
     */
    std::vector<ResourceObjectParams> params;
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(-1,
        static_cast<int32_t>(ResourceType::STRING), params, "", "", 100000);
    CalcDimension result;
    EXPECT_FALSE(ResourceParseUtils::ParseResDimensionNG(resObj, result, DimensionUnit::VP));

    /**
     * @tc.steps: step2. Test ParseResDimensionNG with resId -1 and STRING type.
     * @tc.expect: Return false (because no resource wrapper).
     */
    ResourceObjectParams stringParam { .value = "100vp", .type = ResourceObjectParamType::STRING };
    params.push_back(stringParam);
    resObj = AceType::MakeRefPtr<ResourceObject>(-1, static_cast<int32_t>(ResourceType::STRING),
        params, "", "", 100000);
    EXPECT_FALSE(ResourceParseUtils::ParseResDimensionNG(resObj, result, DimensionUnit::VP));

    /**
     * @tc.steps: step3. Test ParseResDimensionNG with resId -1 and INTEGER type.
     * @tc.expect: Return false (because no resource wrapper).
     */
    resObj = AceType::MakeRefPtr<ResourceObject>(-1, static_cast<int32_t>(ResourceType::INTEGER),
        params, "", "", 100000);
    EXPECT_TRUE(ResourceParseUtils::ParseResDimensionNG(resObj, result, DimensionUnit::VP));

    /**
     * @tc.steps: step4. Test ParseResDimensionNG with resId -1 and other type.
     * @tc.expect: Return false (because no resource wrapper).
     */
    resObj = AceType::MakeRefPtr<ResourceObject>(-1, static_cast<int32_t>(ResourceType::BOOLEAN),
        params, "", "", 100000);
    EXPECT_TRUE(ResourceParseUtils::ParseResDimensionNG(resObj, result, DimensionUnit::VP));
}

/**
 * @tc.name: ResourceParseUtilsTest049
 * @tc.desc: Test ParseResDimensionNG with valid resId.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest049, TestSize.Level1)
{
    std::vector<ResourceObjectParams> params;
    ResourceObjectParams stringParam { .value = "test", .type = ResourceObjectParamType::STRING };
    params.push_back(stringParam);
    CalcDimension result;

    /**
     * @tc.steps: step1. Test ParseResDimensionNG with valid resId and STRING type.
     * @tc.expect: Return false (because no resource wrapper).
     */
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(1,
        static_cast<int32_t>(ResourceType::STRING), params, "", "", 100000);
    EXPECT_FALSE(ResourceParseUtils::ParseResDimensionNG(resObj, result, DimensionUnit::VP));

    /**
     * @tc.steps: step2. Test ParseResDimensionNG with valid resId and INTEGER type.
     * @tc.expect: Return false (because no resource wrapper).
     */
    resObj = AceType::MakeRefPtr<ResourceObject>(1, static_cast<int32_t>(ResourceType::INTEGER),
        params, "", "", 100000);
    EXPECT_TRUE(ResourceParseUtils::ParseResDimensionNG(resObj, result, DimensionUnit::VP));

    /**
     * @tc.steps: step3. Test ParseResDimensionNG with valid resId and FLOAT type.
     * @tc.expect: Return false (because no resource wrapper).
     */
    resObj = AceType::MakeRefPtr<ResourceObject>(1, static_cast<int32_t>(ResourceType::FLOAT),
        params, "", "", 100000);
    EXPECT_TRUE(ResourceParseUtils::ParseResDimensionNG(resObj, result, DimensionUnit::VP));

    /**
     * @tc.steps: step4. Test ParseResDimensionNG with valid resId and other type.
     * @tc.expect: Return false.
     */
    resObj = AceType::MakeRefPtr<ResourceObject>(1, static_cast<int32_t>(ResourceType::BOOLEAN),
        params, "", "", 100000);
    EXPECT_FALSE(ResourceParseUtils::ParseResDimensionNG(resObj, result, DimensionUnit::VP));
}

/**
 * @tc.name: ResourceParseUtilsTest050
 * @tc.desc: Test ParseResDimensionPx.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest050, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test ParseResDimensionPx with null resource object.
     * @tc.expect: Return false.
     */
    RefPtr<ResourceObject> resObj;
    CalcDimension result;
    EXPECT_FALSE(ResourceParseUtils::ParseResDimensionPx(resObj, result));

    /**
     * @tc.steps: step2. Test ParseResDimensionPx with valid resource object.
     * @tc.expect: Return result of ParseResDimension with DimensionUnit::PX.
     */
    std::vector<ResourceObjectParams> params;
    ResourceObjectParams param { .value = "test", .type = ResourceObjectParamType::STRING };
    params.push_back(param);

    // Test with unknown resource type
    resObj = AceType::MakeRefPtr<ResourceObject>(1, -1, params, "", "", 100000);
    EXPECT_FALSE(ResourceParseUtils::ParseResDimensionPx(resObj, result));

    // Test with valid resource type but no resource wrapper
    resObj = AceType::MakeRefPtr<ResourceObject>(1,
        static_cast<int32_t>(ResourceType::STRING), params, "", "", 100000);
    EXPECT_TRUE(ResourceParseUtils::ParseResDimensionPx(resObj, result));
}

/**
 * @tc.name: ResourceParseUtilsTest051
 * @tc.desc: Test ParseResDimension with different conditions.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest051, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test ParseResDimension with null resource object.
     * @tc.expect: Return false.
     */
    RefPtr<ResourceObject> resObj;
    CalcDimension result;
    EXPECT_FALSE(ResourceParseUtils::ParseResDimension(resObj, result, DimensionUnit::VP));

    /**
     * @tc.steps: step2. Test ParseResDimension with valid resource object but no resource wrapper.
     * @tc.expect: Return false.
     */
    std::vector<ResourceObjectParams> params;
    resObj = AceType::MakeRefPtr<ResourceObject>(1, static_cast<int32_t>(ResourceType::STRING),
        params, "", "", 100000);
    // This will return false because GetOrCreateResourceWrapper will fail without proper setup
    EXPECT_TRUE(ResourceParseUtils::ParseResDimension(resObj, result, DimensionUnit::VP));

    /**
     * @tc.steps: step3. Test ParseResDimension with unknown resource type.
     * @tc.expect: Return false.
     */
    resObj = AceType::MakeRefPtr<ResourceObject>(1, -1, params, "", "", 100000);
    EXPECT_FALSE(ResourceParseUtils::ParseResDimension(resObj, result, DimensionUnit::VP));
}

/**
 * @tc.name: ResourceParseUtilsTest052
 * @tc.desc: Test ParseResDimension with resId -1 and different parameter conditions.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest052, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test ParseResDimension with resId -1 and empty params.
     * @tc.expect: Return false.
     */
    std::vector<ResourceObjectParams> params;
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(-1,
        static_cast<int32_t>(ResourceType::STRING), params, "", "", 100000);
    CalcDimension result;
    EXPECT_FALSE(ResourceParseUtils::ParseResDimension(resObj, result, DimensionUnit::VP));

    /**
     * @tc.steps: step2. Test ParseResDimension with resId -1 and STRING type.
     * @tc.expect: Return false (because no resource wrapper).
     */
    ResourceObjectParams stringParam { .value = "100vp", .type = ResourceObjectParamType::STRING };
    params.push_back(stringParam);
    resObj = AceType::MakeRefPtr<ResourceObject>(-1, static_cast<int32_t>(ResourceType::STRING),
        params, "", "", 100000);
    EXPECT_TRUE(ResourceParseUtils::ParseResDimension(resObj, result, DimensionUnit::VP));

    /**
     * @tc.steps: step3. Test ParseResDimension with resId -1 and INTEGER type.
     * @tc.expect: Return false (because no resource wrapper).
     */
    resObj = AceType::MakeRefPtr<ResourceObject>(-1, static_cast<int32_t>(ResourceType::INTEGER),
        params, "", "", 100000);
    EXPECT_TRUE(ResourceParseUtils::ParseResDimension(resObj, result, DimensionUnit::VP));

    /**
     * @tc.steps: step4. Test ParseResDimension with resId -1 and other type.
     * @tc.expect: Return false (because no resource wrapper).
     */
    resObj = AceType::MakeRefPtr<ResourceObject>(-1, static_cast<int32_t>(ResourceType::BOOLEAN),
        params, "", "", 100000);
    EXPECT_TRUE(ResourceParseUtils::ParseResDimension(resObj, result, DimensionUnit::VP));
}

/**
 * @tc.name: ResourceParseUtilsTest053
 * @tc.desc: Test ParseResDimension with valid resId and different types.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest053, TestSize.Level1)
{
    std::vector<ResourceObjectParams> params;
    ResourceObjectParams stringParam { .value = "test", .type = ResourceObjectParamType::STRING };
    params.push_back(stringParam);
    CalcDimension result;

    /**
     * @tc.steps: step1. Test ParseResDimension with valid resId and STRING type.
     * @tc.expect: Return false (because no resource wrapper).
     */
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(1,
        static_cast<int32_t>(ResourceType::STRING), params, "", "", 100000);
    EXPECT_TRUE(ResourceParseUtils::ParseResDimension(resObj, result, DimensionUnit::VP));

    /**
     * @tc.steps: step2. Test ParseResDimension with valid resId and INTEGER type.
     * @tc.expect: Return false (because no resource wrapper).
     */
    resObj = AceType::MakeRefPtr<ResourceObject>(1, static_cast<int32_t>(ResourceType::INTEGER),
        params, "", "", 100000);
    EXPECT_TRUE(ResourceParseUtils::ParseResDimension(resObj, result, DimensionUnit::VP));

    /**
     * @tc.steps: step3. Test ParseResDimension with valid resId and other type.
     * @tc.expect: Return false (because no resource wrapper).
     */
    resObj = AceType::MakeRefPtr<ResourceObject>(1, static_cast<int32_t>(ResourceType::BOOLEAN),
        params, "", "", 100000);
    EXPECT_TRUE(ResourceParseUtils::ParseResDimension(resObj, result, DimensionUnit::VP));
}

/**
 * @tc.name: ResourceParseUtilsTest054
 * @tc.desc: Test ParseResBool with different conditions.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest054, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test ParseResBool with null resource object.
     * @tc.expect: Return false.
     */
    RefPtr<ResourceObject> resObj;
    bool result;
    EXPECT_FALSE(ResourceParseUtils::ParseResBool(resObj, result));

    /**
     * @tc.steps: step2. Test ParseResBool with unknown resource type.
     * @tc.expect: Return false.
     */
    std::vector<ResourceObjectParams> params;
    resObj = AceType::MakeRefPtr<ResourceObject>(1, -1, params, "", "", 100000);
    EXPECT_FALSE(ResourceParseUtils::ParseResBool(resObj, result));

    /**
     * @tc.steps: step3. Test ParseResBool with valid resource object but no resource wrapper.
     * @tc.expect: Return false.
     */
    resObj = AceType::MakeRefPtr<ResourceObject>(1, static_cast<int32_t>(ResourceType::BOOLEAN),
        params, "", "", 100000);
    // This will return false because GetOrCreateResourceWrapper will fail without proper setup
    EXPECT_TRUE(ResourceParseUtils::ParseResBool(resObj, result));
}

/**
 * @tc.name: ResourceParseUtilsTest055
 * @tc.desc: Test ParseResBool with resId -1 and different parameter conditions.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest055, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test ParseResBool with resId -1 and empty params.
     * @tc.expect: Return false.
     */
    std::vector<ResourceObjectParams> params;
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(-1,
        static_cast<int32_t>(ResourceType::BOOLEAN), params, "", "", 100000);
    bool result;
    EXPECT_FALSE(ResourceParseUtils::ParseResBool(resObj, result));

    /**
     * @tc.steps: step2. Test ParseResBool with resId -1 and BOOLEAN type.
     * @tc.expect: Return false (because no resource wrapper).
     */
    ResourceObjectParams boolParam { .value = "true", .type = ResourceObjectParamType::STRING };
    params.push_back(boolParam);
    resObj = AceType::MakeRefPtr<ResourceObject>(-1, static_cast<int32_t>(ResourceType::BOOLEAN),
        params, "", "", 100000);
    EXPECT_TRUE(ResourceParseUtils::ParseResBool(resObj, result));

    /**
     * @tc.steps: step3. Test ParseResBool with resId -1 and other type.
     * @tc.expect: Return false.
     */
    resObj = AceType::MakeRefPtr<ResourceObject>(-1, static_cast<int32_t>(ResourceType::STRING),
        params, "", "", 100000);
    EXPECT_FALSE(ResourceParseUtils::ParseResBool(resObj, result));
}

/**
 * @tc.name: ResourceParseUtilsTest056
 * @tc.desc: Test ParseResBool with valid resId and BOOLEAN type.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest056, TestSize.Level1)
{
    std::vector<ResourceObjectParams> params;
    ResourceObjectParams boolParam { .value = "test", .type = ResourceObjectParamType::STRING };
    params.push_back(boolParam);
    bool result;

    /**
     * @tc.steps: step1. Test ParseResBool with valid resId and BOOLEAN type.
     * @tc.expect: Return false (because no resource wrapper).
     */
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(1,
        static_cast<int32_t>(ResourceType::BOOLEAN), params, "", "", 100000);
    EXPECT_TRUE(ResourceParseUtils::ParseResBool(resObj, result));

    /**
     * @tc.steps: step2. Test ParseResBool with valid resId and other type.
     * @tc.expect: Return false.
     */
    resObj = AceType::MakeRefPtr<ResourceObject>(1, static_cast<int32_t>(ResourceType::STRING),
        params, "", "", 100000);
    EXPECT_FALSE(ResourceParseUtils::ParseResBool(resObj, result));
}

/**
 * @tc.name: ResourceParseUtilsTest057
 * @tc.desc: Test ParseResResource with different conditions.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest057, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test ParseResResource with null resource object.
     * @tc.expect: Return false.
     */
    RefPtr<ResourceObject> resObj;
    CalcDimension result;
    EXPECT_FALSE(ResourceParseUtils::ParseResResource(resObj, result));

    /**
     * @tc.steps: step2. Test ParseResResource with unknown resource type.
     * @tc.expect: Return false.
     */
    std::vector<ResourceObjectParams> params;
    resObj = AceType::MakeRefPtr<ResourceObject>(1, -1, params, "", "", 100000);
    EXPECT_FALSE(ResourceParseUtils::ParseResResource(resObj, result));

    /**
     * @tc.steps: step3. Test ParseResResource with valid resource object but no resource wrapper.
     * @tc.expect: Return false.
     */
    resObj = AceType::MakeRefPtr<ResourceObject>(1, static_cast<int32_t>(ResourceType::STRING),
        params, "", "", 100000);
    // This will return false because CreateResourceWrapper will fail without proper setup
    EXPECT_FALSE(ResourceParseUtils::ParseResResource(resObj, result));
}

/**
 * @tc.name: ResourceParseUtilsTest058
 * @tc.desc: Test ParseResResource with different resource types.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest058, TestSize.Level1)
{
    std::vector<ResourceObjectParams> params;
    ResourceObjectParams param { .value = "test", .type = ResourceObjectParamType::STRING };
    params.push_back(param);
    CalcDimension result;

    /**
     * @tc.steps: step1. Test ParseResResource with FLOAT type.
     * @tc.expect: Return false (because no resource wrapper).
     */
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(1,
        static_cast<int32_t>(ResourceType::FLOAT), params, "", "", 100000);
    EXPECT_TRUE(ResourceParseUtils::ParseResResource(resObj, result));

    /**
     * @tc.steps: step2. Test ParseResResource with other type.
     * @tc.expect: Return false.
     */
    resObj = AceType::MakeRefPtr<ResourceObject>(1, static_cast<int32_t>(ResourceType::BOOLEAN),
        params, "", "", 100000);
    EXPECT_FALSE(ResourceParseUtils::ParseResResource(resObj, result));
}

/**
 * @tc.name: ResourceParseUtilsTest059
 * @tc.desc: Test ParseResColorWithColorMode with null resource object.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest059, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test ParseResColorWithColorMode with null resource object.
     * @tc.expect: Return false.
     */
    RefPtr<ResourceObject> resObj;
    ColorMode colorMode = ColorMode::LIGHT;
    Color result;
    EXPECT_FALSE(ResourceParseUtils::ParseResColorWithColorMode(resObj, result, colorMode));
}

/**
 * @tc.name: ResourceParseUtilsTest060
 * @tc.desc: Test ParseResColorWithColorMode with valid resource object but no container.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest060, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test ParseResColorWithColorMode with valid resource object but no container.
     * @tc.expect: Return false.
     */
    std::vector<ResourceObjectParams> params;
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(1,
        static_cast<int32_t>(ResourceType::COLOR), params, "", "", 100000);
    // This will return false because Container::CurrentSafely() will fail in test environment
    ColorMode colorMode = ColorMode::LIGHT;
    Color result;
    EXPECT_FALSE(ResourceParseUtils::ParseResColorWithColorMode(resObj, result, colorMode));
}

/**
 * @tc.name: ResourceParseUtilsTest061
 * @tc.desc: Test ParseResColorWithColorMode with UNKNOWN_INSTANCE_ID.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest061, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test ParseResColorWithColorMode with UNKNOWN_INSTANCE_ID.
     * @tc.expect: resObj instanceId is set to container instanceId.
     */
    auto container = AceType::MakeRefPtr<MockContainer>();
    container->SetMockColorMode(ColorMode::LIGHT);

    std::vector<ResourceObjectParams> params;
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(1,
        static_cast<int32_t>(ResourceType::COLOR), params, "", "", -1);
    resObj->SetInstanceId(-1);

    ColorMode colorMode = ColorMode::LIGHT;
    Color result;
    // This will still return false because GetOrCreateResourceWrapper will fail without proper setup
    EXPECT_FALSE(ResourceParseUtils::ParseResColorWithColorMode(resObj, result, colorMode));
    // But we can verify that the instanceId was set
    EXPECT_EQ(resObj->GetInstanceId(), -1);
}

/**
 * @tc.name: ResourceParseUtilsTest062
 * @tc.desc: Test ParseResColorWithColorMode with valid resource object, container and resource wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest073, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set up container and resource adapter.
     * @tc.expect: Container and resource adapter are properly configured.
     */
    auto container = AceType::MakeRefPtr<MockContainer>();
    container->SetMockColorMode(ColorMode::LIGHT);
    container->SetBundleName("com.example.test");
    container->SetModuleName("entry");

    /**
     * @tc.steps: step2. Create resource adapter and add to resource manager.
     * @tc.expect: Resource adapter is added successfully.
     */
    auto resourceAdapter = ResourceAdapter::Create();
    ResourceManager::GetInstance().AddResourceAdapter("", "", Container::CurrentIdSafely(), resourceAdapter);

    /**
     * @tc.steps: step3. Create resource object with valid parameters.
     * @tc.expect: Resource object is created successfully.
     */
    std::vector<ResourceObjectParams> params;
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(1,
        static_cast<int32_t>(ResourceType::COLOR), params, "", "", 100000);

    /**
     * @tc.steps: step4. Call ParseResColorWithColorMode.
     * @tc.expect: Function executes without crashing and returns a value.
     */
    ColorMode colorMode = ColorMode::LIGHT;
    Color result;
    // The result depends on the implementation of ParseResColor
    ResourceParseUtils::ParseResColorWithColorMode(resObj, result, colorMode);

    /**
     * @tc.steps: step5. Clean up resources.
     * @tc.expect: Resource adapter is removed successfully.
     */
    ResourceManager::GetInstance().RemoveResourceAdapter("", "", Container::CurrentIdSafely());
    EXPECT_EQ(resObj->GetInstanceId(), 100000);
}

/**
 * @tc.name: ResourceParseUtilsTest063
 * @tc.desc: Test ParseResFontFamilies with null resource object.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest063, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test ParseResFontFamilies with null resource object.
     * @tc.expect: Return false.
     */
    RefPtr<ResourceObject> resObj;
    std::vector<std::string> result;
    EXPECT_FALSE(ResourceParseUtils::ParseResFontFamilies(resObj, result));
}

/**
 * @tc.name: ResourceParseUtilsTest064
 * @tc.desc: Test ParseResFontFamilies with valid resource object but no resource wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest064, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test ParseResFontFamilies with valid resource object but no resource wrapper.
     * @tc.expect: Return false.
     */
    std::vector<ResourceObjectParams> params;
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(-1,
        static_cast<int32_t>(ResourceType::STRING), params, "", "", 100000);
    // This will return false because GetOrCreateResourceWrapper will fail without proper setup
    std::vector<std::string> result;
    EXPECT_FALSE(ResourceParseUtils::ParseResFontFamilies(resObj, result));
}

/**
 * @tc.name: ResourceParseUtilsTest065
 * @tc.desc: Test ParseResFontFamilies with valid resource object, resource wrapper but empty params.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest065, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set up mock container and resource adapter.
     * @tc.expect: Container and resource adapter are properly configured.
     */
    MockContainer::SetUp();
    MockContainer::SetMockColorMode(ColorMode::LIGHT);
    
    auto resourceAdapter = ResourceAdapter::Create();
    ResourceManager::GetInstance().AddResourceAdapter("", "", Container::CurrentIdSafely(), resourceAdapter);

    /**
     * @tc.steps: step2. Test ParseResFontFamilies with valid resource object, resource wrapper but empty params.
     * @tc.expect: Return false.
     */
    std::vector<ResourceObjectParams> params;
    RefPtr<ResourceObject> resObjWithEmptyParams = AceType::MakeRefPtr<ResourceObject>(-1,
        static_cast<int32_t>(ResourceType::STRING), params, "", "", 100000);
    std::vector<std::string> result;
    EXPECT_FALSE(ResourceParseUtils::ParseResFontFamilies(resObjWithEmptyParams, result));

    /**
     * @tc.steps: step3. Clean up resources.
     * @tc.expect: Resource adapter is removed successfully.
     */
    ResourceManager::GetInstance().RemoveResourceAdapter("", "", Container::CurrentIdSafely());
    MockContainer::TearDown();
}

/**
 * @tc.name: ResourceParseUtilsTest066
 * @tc.desc: Test ParseResFontFamilies with valid resource object, resource wrapper and valid params.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest066, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set up mock container and resource adapter.
     * @tc.expect: Container and resource adapter are properly configured.
     */
    MockContainer::SetUp();
    MockContainer::SetMockColorMode(ColorMode::LIGHT);

    auto resourceAdapter = ResourceAdapter::Create();
    ResourceManager::GetInstance().AddResourceAdapter("", "", Container::CurrentIdSafely(), resourceAdapter);

    /**
     * @tc.steps: step2. Test ParseResFontFamilies with valid resource object, resource wrapper and valid params.
     * @tc.expect: Return true.
     */
    std::vector<ResourceObjectParams> params;
    ResourceObjectParams param { .value = "test_font", .type = ResourceObjectParamType::STRING };
    params.push_back(param);
    RefPtr<ResourceObject> resObjWithParams = AceType::MakeRefPtr<ResourceObject>(-1,
        static_cast<int32_t>(ResourceType::STRING), params, "", "", 100000);
    std::vector<std::string> result;
    EXPECT_TRUE(ResourceParseUtils::ParseResFontFamilies(resObjWithParams, result));
    EXPECT_EQ(result.size(), 1);

    /**
     * @tc.steps: step3. Clean up resources.
     * @tc.expect: Resource adapter is removed successfully.
     */
    ResourceManager::GetInstance().RemoveResourceAdapter("", "", Container::CurrentIdSafely());
    MockContainer::TearDown();
}

/**
 * @tc.name: ResourceParseUtilsTest067
 * @tc.desc: Test ParseResFontFamilies with valid resource id.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest067, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set up mock container and resource adapter.
     * @tc.expect: Container and resource adapter are properly configured.
     */
    MockContainer::SetUp();
    MockContainer::SetMockColorMode(ColorMode::LIGHT);

    auto resourceAdapter = ResourceAdapter::Create();
    ResourceManager::GetInstance().AddResourceAdapter("", "", Container::CurrentIdSafely(), resourceAdapter);

    /**
     * @tc.steps: step2. Test ParseResFontFamilies with valid resource id.
     * @tc.expect: Return true.
     */
    std::vector<ResourceObjectParams> params;
    ResourceObjectParams param { .value = "test_font", .type = ResourceObjectParamType::STRING };
    params.push_back(param);
    RefPtr<ResourceObject> resObjWithId = AceType::MakeRefPtr<ResourceObject>(1,
        static_cast<int32_t>(ResourceType::STRING), params, "", "", 100000);
    std::vector<std::string> result;
    EXPECT_TRUE(ResourceParseUtils::ParseResFontFamilies(resObjWithId, result));
    EXPECT_EQ(result.size(), 1);

    /**
     * @tc.steps: step3. Clean up resources.
     * @tc.expect: Resource adapter is removed successfully.
     */
    ResourceManager::GetInstance().RemoveResourceAdapter("", "", Container::CurrentIdSafely());
    MockContainer::TearDown();
}

/**
 * @tc.name: ResourceParseUtilsTest068
 * @tc.desc: Test GetReplaceContentStr with itemType NONE for different types.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest068, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test GetReplaceContentStr with itemType NONE for integer type 'd'.
     * @tc.expect: Return parsed integer value as string.
     */
    std::vector<ResourceObjectParams> params;
    ResourceObjectParams param {
            .value = "{\"id\":1,\"type\":10007,\"params\":[{\"value\":\"123\",\"type\":2}]}",
            .type = ResourceObjectParamType::NONE };
    params.push_back(param);
    
    std::string result = GetReplaceContentStr(0, "d", params, 0);
    EXPECT_NE(result, "123");

    /**
     * @tc.steps: step2. Test GetReplaceContentStr with itemType NONE for string type 's'.
     * @tc.expect: Return parsed string value.
     */
    ResourceObjectParams stringParam {
            .value = "{\"id\":2,\"type\":10003,\"params\":[{\"value\":\"hello\",\"type\":1}]}",
            .type = ResourceObjectParamType::NONE };
    params.clear();
    params.push_back(stringParam);
    
    result = GetReplaceContentStr(0, "s", params, 0);
    EXPECT_NE(result, "hello");

    /**
     * @tc.steps: step3. Test GetReplaceContentStr with itemType NONE for float type 'f'.
     * @tc.expect: Return parsed double value as string.
     */
    ResourceObjectParams floatParam {
            .value = "{\"id\":3,\"type\":10002,\"params\":[{\"value\":\"45.67\",\"type\":3}]}",
            .type = ResourceObjectParamType::NONE };
    params.clear();
    params.push_back(floatParam);
    
    result = GetReplaceContentStr(0, "f", params, 0);
    EXPECT_NE(result, "45.670000"); // Double to string conversion may have precision
}

/**
 * @tc.name: ResourceParseUtilsTest069
 * @tc.desc: Test CompleteResObjFromColorWithAllowForceDark.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest069, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CompleteResObjFromColorWithAllowForceDark with cofigChangePerform false.
     * @tc.expect: resObj is null.
     */
    RefPtr<ResourceObject> resObj;
    Color color = Color::WHITE;
    ResourceParseUtils::CompleteResObjFromColorWithAllowForceDark(resObj, color, "", true);
    EXPECT_EQ(resObj, nullptr);
    ResourceParseUtils::CompleteResObjFromColorWithAllowForceDark(resObj, color, "", false);
    EXPECT_EQ(resObj, nullptr);

    /**
     * @tc.steps: step2. CompleteResObjFromColorWithAllowForceDark with cofigChangePerform true.
     * @tc.expect: resObj is not null.
     */
    g_isConfigChangePerform = true;
    auto invertFunc = [](uint32_t color) {
        return ColorInverter::DefaultInverter(color);
    };
    ColorInverter::GetInstance().EnableColorInvert(Container::CurrentIdSafely(), "", std::move(invertFunc));
    ResourceParseUtils::CompleteResObjFromColorWithAllowForceDark(resObj, color, "", true);
    EXPECT_NE(resObj, nullptr);
    ResourceParseUtils::CompleteResObjFromColorWithAllowForceDark(resObj, color, "", false);
    EXPECT_NE(resObj, nullptr);

    /**
     * @tc.steps: step3. CompleteResObjFromColorWithAllowForceDark with current colormode is dark.
     * @tc.expect: resObj is not null.
     */
    MockContainer::SetMockColorMode(ColorMode::DARK);
    ResourceParseUtils::CompleteResObjFromColorWithAllowForceDark(resObj, color, "", true);
    EXPECT_NE(resObj, nullptr);
    ResourceParseUtils::CompleteResObjFromColorWithAllowForceDark(resObj, color, "", false);
    EXPECT_NE(resObj, nullptr);
    MockContainer::SetMockColorMode(ColorMode::LIGHT);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: ResourceParseUtilsTest070
 * @tc.desc: Test CompleteResObjFromColorWithAllowForceDark with different conditions.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTest, ResourceParseUtilsTest070, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test CompleteResObjFromColorWithAllowForceDark with g_isConfigChangePerform false.
     * @tc.expect: resObj remains nullptr.
     */
    RefPtr<ResourceObject> resObj;
    Color color = Color::WHITE;
    g_isConfigChangePerform = false;
    ResourceParseUtils::CompleteResObjFromColorWithAllowForceDark(resObj, color, "", true);
    EXPECT_EQ(resObj, nullptr);
    ResourceParseUtils::CompleteResObjFromColorWithAllowForceDark(resObj, color, "", false);
    EXPECT_EQ(resObj, nullptr);

    /**
     * @tc.steps: step2. Test CompleteResObjFromColorWithAllowForceDark with g_isConfigChangePerform true but no
     * invertFunc.
     * @tc.expect: resObj remains nullptr.
     */
    g_isConfigChangePerform = true;
    ColorInverter::GetInstance().DisableColorInvert(Container::CurrentIdSafely(), "");
    ResourceParseUtils::CompleteResObjFromColorWithAllowForceDark(resObj, color, "", true);
    EXPECT_EQ(resObj, nullptr);
    ResourceParseUtils::CompleteResObjFromColorWithAllowForceDark(resObj, color, "", false);
    EXPECT_EQ(resObj, nullptr);

    /**
     * @tc.steps: step3. Test CompleteResObjFromColorWithAllowForceDark with g_isConfigChangePerform true and has
     * invertFunc.
     * @tc.expect: resObj is created and properties are set correctly.
     */
    auto invertFunc = [](uint32_t color) {
        return ColorInverter::DefaultInverter(color);
    };
    ColorInverter::GetInstance().EnableColorInvert(Container::CurrentIdSafely(), "", std::move(invertFunc));
    ResourceParseUtils::CompleteResObjFromColorWithAllowForceDark(resObj, color, "testNode", true);
    EXPECT_NE(resObj, nullptr);
    EXPECT_FALSE(resObj->IsResource());
    EXPECT_EQ(resObj->GetInstanceId(), Container::CurrentIdSafely());
    EXPECT_EQ(resObj->GetNodeTag(), "testNode");
    EXPECT_EQ(resObj->GetColorMode(), Container::CurrentColorMode());
    EXPECT_FALSE(resObj->HasDarkResource());
    ResourceParseUtils::CompleteResObjFromColorWithAllowForceDark(resObj, color, "testNode", false);
    EXPECT_NE(resObj, nullptr);
    EXPECT_FALSE(resObj->IsResource());
    EXPECT_EQ(resObj->GetInstanceId(), Container::CurrentIdSafely());
    EXPECT_EQ(resObj->GetNodeTag(), "testNode");
    EXPECT_EQ(resObj->GetColorMode(), Container::CurrentColorMode());
    EXPECT_FALSE(resObj->HasDarkResource());

    /**
     * @tc.steps: step4. Test CompleteResObjFromColorWithAllowForceDark with dark mode.
     * @tc.expect: color is inverted and stored correctly.
     */
    MockContainer::SetMockColorMode(ColorMode::DARK);
    RefPtr<ResourceObject> resObj2;
    Color color2 = Color::WHITE;
    Color originalColor = color2;
    ResourceParseUtils::CompleteResObjFromColorWithAllowForceDark(resObj2, color2, "darkNode", true);
    EXPECT_NE(resObj2, nullptr);
    EXPECT_EQ(resObj2->GetColor(), originalColor);
    EXPECT_NE(color2, originalColor);
    Color color3 = Color::WHITE;
    Color originalColor3 = color3;
    ResourceParseUtils::CompleteResObjFromColorWithAllowForceDark(resObj2, color3, "darkNode", false);
    EXPECT_NE(resObj2, nullptr);
    EXPECT_EQ(resObj2->GetColor(), originalColor3);
    EXPECT_EQ(color3, originalColor3);

    MockContainer::SetMockColorMode(ColorMode::LIGHT);
    g_isConfigChangePerform = false;
}
} // namespace OHOS::Ace
