/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"

#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::NG::Converter;

namespace OHOS::Ace::NG {
namespace  {
// attributes name
const auto ATTRIBUTE_STROKE_WIDTH_NAME = "strokeWidth";
const auto ATTRIBUTE_STROKE_OPACITY_NAME = "strokeOpacity";
const auto ATTRIBUTE_FILL_OPACITY_NAME = "fillOpacity";

// global variables
const int64_t FAKE_RES_ID(1234);

// resource names and id
const auto RES_NAME = "aa.bb.cc";
const auto RES_ID = 11111;
const auto RES_NAME_ID = NamedResourceId{RES_NAME, ResourceType::FLOAT};
const auto RES_INT_ID = IntResourceId{RES_ID, ResourceType::FLOAT};

// resource values
const auto RESOURCE_OPACITY_BY_STRING = 0.4f;
const auto RESOURCE_OPACITY_BY_NUMBER = 0.5f;

// check
const auto CHECK_RESOURCE_OPACITY_BY_STRING = "0.400000";
const auto CHECK_RESOURCE_OPACITY_BY_NUMBER = "0.500000";

using OneUnionNumStrResStep = std::pair<Ark_Union_Number_String_Resource, std::string>;

const std::vector<OneUnionNumStrResStep> UNION_NUM_STR_RES_RESOURECES_TEST_PLAN = {
    { CreateResourceUnion<Ark_Union_Number_String_Resource>(RES_NAME_ID), CHECK_RESOURCE_OPACITY_BY_STRING },
    { CreateResourceUnion<Ark_Union_Number_String_Resource>(RES_INT_ID), CHECK_RESOURCE_OPACITY_BY_NUMBER },
};
} // namespace;

class CommonShapeMethodModifierResourcesTest : public ModifierTestBase<GENERATED_ArkUICommonShapeMethodModifier,
    &GENERATED_ArkUINodeModifiers::getCommonShapeMethodModifier,
    GENERATED_ARKUI_CIRCLE // test common shape methods on frameNode for Circle component
    > {
public:
    void *CreateNodeImpl() override
    {
        return nodeModifiers_->getCircleModifier()->construct(GetId(), 0);
    }

    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        // set test values to Theme Pattern as data for the Theme building
        AddResource(RES_NAME, RESOURCE_OPACITY_BY_STRING);
        AddResource(RES_ID, RESOURCE_OPACITY_BY_NUMBER);
    }
};

/*
 * @tc.name: setStrokeWidthTestValidValues
 * @tc.desc: check setStrokeWidth from resource
 * @tc.type: FUNC
 */
HWTEST_F(CommonShapeMethodModifierResourcesTest, setStrokeWidthTestResources, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    double result;

    typedef std::pair<Opt_Length, double> OneTestStep;
    const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Opt_Length>(FAKE_RES_ID), 10 }
    };

    for (const auto &[arkLength, expected]: testPlan) {
        modifier_->setStrokeWidth(node_, &arkLength);
        jsonValue = GetJsonValue(node_);
        result = GetAttrValue<double>(jsonValue, ATTRIBUTE_STROKE_WIDTH_NAME);
        EXPECT_NEAR(result, expected, FLT_EPSILON);
    }
}

/**
 * @tc.name: setFillOpacityTest
 * @tc.desc: Check the functionality of setFillOpacity
 * @tc.type: FUNC
 */
HWTEST_F(CommonShapeMethodModifierResourcesTest, setFillOpacityTestResources, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;

    for (const auto &[value, expectVal]: UNION_NUM_STR_RES_RESOURECES_TEST_PLAN) {
        auto res = Converter::ArkValue<Opt_Union_Number_String_Resource>(value);
        modifier_->setFillOpacity(node_, &res);
        jsonValue = GetJsonValue(node_);
        auto checkVal = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FILL_OPACITY_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setStrokeOpacityTest
 * @tc.desc: Check the functionality of setStrokeOpacity
 * @tc.type: FUNC
 */
HWTEST_F(CommonShapeMethodModifierResourcesTest, setStrokeOpacityTestResources, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    Opt_Union_Number_String_Resource res;
    for (const auto &[value, expectVal]: UNION_NUM_STR_RES_RESOURECES_TEST_PLAN) {
        res = Converter::ArkValue<Opt_Union_Number_String_Resource>(value);
        modifier_->setStrokeOpacity(node_, &res);
        jsonValue = GetJsonValue(node_);
        auto checkVal = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STROKE_OPACITY_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}
} // namespace OHOS::Ace::NG
