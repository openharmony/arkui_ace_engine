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
} // namespace OHOS::Ace
