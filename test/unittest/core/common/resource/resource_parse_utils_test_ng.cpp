/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include <string>

#include "gtest/gtest.h"
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_resource_adapter.h"

#include "ui/resource/resource_object.h"

#include "core/common/color_inverter.h"
#include "core/common/container.h"
#include "core/common/resource/resource_object.h"
#include "core/common/resource/resource_parse_utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
class ResourceParseUtilsTestNg : public testing::Test {};

/**
 * @tc.name: ResourceParseUtilsTestNg_ParseResColor_NullResourceObject
 * @tc.desc: Test ParseResColor returns false when resource object is null
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTestNg, ResourceParseUtilsTestNg_ParseResColor_NullResourceObject, TestSize.Level1)
{
    RefPtr<ResourceObject> resObj = nullptr;
    Color result;
    EXPECT_FALSE(ResourceParseUtils::ParseResColor(resObj, result));
}

/**
 * @tc.name: ResourceParseUtilsTestNg_ParseResColor_NonResourceObjectWithUndefinedColorMode
 * @tc.desc: Test ParseResColor returns false when resource is not a resource and color mode is undefined
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTestNg, ResourceParseUtilsTestNg_ParseResColor_NonResourceObjectWithUndefinedColorMode,
    TestSize.Level1)
{
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    resObj->SetColor(Color::WHITE);
    resObj->SetIsResource(false);
    resObj->SetColorMode(ColorMode::COLOR_MODE_UNDEFINED);

    Color result;
    EXPECT_FALSE(ResourceParseUtils::ParseResColor(resObj, result));
}

/**
 * @tc.name: ResourceParseUtilsTestNg_ParseResColor_NonResourceObjectWithLightMode
 * @tc.desc: Test ParseResColor returns true when resource is not a resource and color mode is light
 * @tc.type: FUNC
 */
HWTEST_F(
    ResourceParseUtilsTestNg, ResourceParseUtilsTestNg_ParseResColor_NonResourceObjectWithLightMode, TestSize.Level1)
{
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    Color testColor = Color::BLUE;
    resObj->SetColor(testColor);
    resObj->SetIsResource(false);
    resObj->SetColorMode(ColorMode::LIGHT);

    Color result;
    EXPECT_TRUE(ResourceParseUtils::ParseResColor(resObj, result));
    EXPECT_EQ(result, testColor);
}

/**
 * @tc.name: ResourceParseUtilsTestNg_ParseResColor_NonResourceObjectWithDarkModeAndNeedReload
 * @tc.desc: Test ParseResColor with dark mode and need reload enabled triggers color inversion
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTestNg, ResourceParseUtilsTestNg_ParseResColor_NonResourceObjectWithDarkModeAndNeedReload,
    TestSize.Level1)
{
    ResourceParseUtils::SetNeedReload(true);
    MockContainer::SetMockColorMode(ColorMode::DARK);

    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    Color testColor = Color::WHITE;
    resObj->SetColor(testColor);
    resObj->SetIsResource(false);
    resObj->SetColorMode(ColorMode::LIGHT);

    Color result;
    EXPECT_TRUE(ResourceParseUtils::ParseResColor(resObj, result));
    EXPECT_EQ(resObj->GetColorMode(), ColorMode::DARK);

    ResourceParseUtils::SetNeedReload(false);
    MockContainer::SetMockColorMode(ColorMode::LIGHT);
}

/**
 * @tc.name: ResourceParseUtilsTestNg_ParseResString_NullResourceObject
 * @tc.desc: Test ParseResString returns false when resource object is null
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTestNg, ResourceParseUtilsTestNg_ParseResString_NullResourceObject, TestSize.Level1)
{
    RefPtr<ResourceObject> resObj = nullptr;
    std::string result;
    EXPECT_FALSE(ResourceParseUtils::ParseResString(resObj, result));
}

/**
 * @tc.name: ResourceParseUtilsTestNg_ParseResInteger_NullResourceObject
 * @tc.desc: Test ParseResInteger returns false when resource object is null
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTestNg, ResourceParseUtilsTestNg_ParseResInteger_NullResourceObject, TestSize.Level1)
{
    RefPtr<ResourceObject> resObj = nullptr;
    int32_t result;
    EXPECT_FALSE(ResourceParseUtils::ParseResInteger(resObj, result));
}

/**
 * @tc.name: ResourceParseUtilsTestNg_ParseResDouble_NullResourceObject
 * @tc.desc: Test ParseResDouble returns false when resource object is null
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTestNg, ResourceParseUtilsTestNg_ParseResDouble_NullResourceObject, TestSize.Level1)
{
    RefPtr<ResourceObject> resObj = nullptr;
    double result;
    EXPECT_FALSE(ResourceParseUtils::ParseResDouble(resObj, result));
}

/**
 * @tc.name: ResourceParseUtilsTestNg_ParseResBool_NullResourceObject
 * @tc.desc: Test ParseResBool returns false when resource object is null
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTestNg, ResourceParseUtilsTestNg_ParseResBool_NullResourceObject, TestSize.Level1)
{
    RefPtr<ResourceObject> resObj = nullptr;
    bool result;
    EXPECT_FALSE(ResourceParseUtils::ParseResBool(resObj, result));
}

/**
 * @tc.name: ResourceParseUtilsTestNg_ParseResDimensionNG_NullResourceObject
 * @tc.desc: Test ParseResDimensionNG returns false when resource object is null
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTestNg, ResourceParseUtilsTestNg_ParseResDimensionNG_NullResourceObject, TestSize.Level1)
{
    RefPtr<ResourceObject> resObj = nullptr;
    CalcDimension result;
    EXPECT_FALSE(ResourceParseUtils::ParseResDimensionNG(resObj, result, DimensionUnit::VP, true));
}

/**
 * @tc.name: ResourceParseUtilsTestNg_ParseResIntegerArray_NullResourceObject
 * @tc.desc: Test ParseResIntegerArray returns false when resource object is null
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTestNg, ResourceParseUtilsTestNg_ParseResIntegerArray_NullResourceObject, TestSize.Level1)
{
    RefPtr<ResourceObject> resObj = nullptr;
    std::vector<uint32_t> result;
    EXPECT_FALSE(ResourceParseUtils::ParseResIntegerArray(resObj, result));
}

/**
 * @tc.name: ResourceParseUtilsTestNg_ParseResStrArray_NullResourceObject
 * @tc.desc: Test ParseResStrArray returns false when resource object is null
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTestNg, ResourceParseUtilsTestNg_ParseResStrArray_NullResourceObject, TestSize.Level1)
{
    RefPtr<ResourceObject> resObj = nullptr;
    std::vector<std::string> result;
    EXPECT_FALSE(ResourceParseUtils::ParseResStrArray(resObj, result));
}

/**
 * @tc.name: ResourceParseUtilsTestNg_ParseResFontFamilies_NullResourceObject
 * @tc.desc: Test ParseResFontFamilies returns false when resource object is null
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTestNg, ResourceParseUtilsTestNg_ParseResFontFamilies_NullResourceObject, TestSize.Level1)
{
    RefPtr<ResourceObject> resObj = nullptr;
    std::vector<std::string> result;
    EXPECT_FALSE(ResourceParseUtils::ParseResFontFamilies(resObj, result));
}

/**
 * @tc.name: ResourceParseUtilsTestNg_ParseResMedia_NullResourceObject
 * @tc.desc: Test ParseResMedia returns false when resource object is null
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTestNg, ResourceParseUtilsTestNg_ParseResMedia_NullResourceObject, TestSize.Level1)
{
    RefPtr<ResourceObject> resObj = nullptr;
    std::string result;
    EXPECT_FALSE(ResourceParseUtils::ParseResMedia(resObj, result));
}

/**
 * @tc.name: ResourceParseUtilsTestNg_SetNeedReload_GetNeedReload
 * @tc.desc: Test SetNeedReload and GetNeedReload state management
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTestNg, ResourceParseUtilsTestNg_SetNeedReload_GetNeedReload, TestSize.Level1)
{
    ResourceParseUtils::SetNeedReload(true);
    EXPECT_TRUE(ResourceParseUtils::NeedReload());

    ResourceParseUtils::SetNeedReload(false);
    EXPECT_FALSE(ResourceParseUtils::NeedReload());
}

/**
 * @tc.name: ResourceParseUtilsTestNg_ParseResResource_NullResourceObject
 * @tc.desc: Test ParseResResource returns false when resource object is null
 * @tc.type: FUNC
 */
HWTEST_F(ResourceParseUtilsTestNg, ResourceParseUtilsTestNg_ParseResResource_NullResourceObject, TestSize.Level1)
{
    RefPtr<ResourceObject> resObj = nullptr;
    CalcDimension result;
    EXPECT_FALSE(ResourceParseUtils::ParseResResource(resObj, result));
}

} // namespace OHOS::Ace
