/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gtest/gtest.h>

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace  {
    // const auto ATTRIBUTE_ENABLE_ANALYZER_ENABLE_NAME = "enableAnalyzerEnable";
    // const auto ATTRIBUTE_ENABLE_ANALYZER_ENABLE_DEFAULT_VALUE = "!NOT-DEFINED!";

// test!!!
    std::ofstream out("output/test_output_fill_json_badge.txt");    

    void FromJson(std::string title, std::unique_ptr<JsonValue>& jsonValue){
       std::string str(jsonValue->ToString()); 
       out << "\n" << "===" << title << "===\n" << jsonValue->ToString() << std::endl;
    }

} // namespace

class CanvasModifierTest : public ModifierTestBase<GENERATED_ArkUICanvasModifier, 
    &GENERATED_ArkUINodeModifiers::getCanvasModifier, GENERATED_ARKUI_CANVAS> {
    public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        // SetupTheme<BadgeTheme>();

        // AddResource(RES_COLOR_NAME, COLOR_BY_STRING);
    }
};

// TODO: Process non-options argument in setOptions function
// TODO: Process non-options argument in setOptions function
// TODO: Process non-options argument in setOptions function

/*
 * @tc.name: DISABLED_setOnReadyTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasModifierTest, setOnReadyTest, TestSize.Level1)
{

    // test!!!
    auto jsonValue = GetJsonValue(node_);
    FromJson("setOnReadyTest", jsonValue);
    // test!!!=

    // TODO: Implement callback tests!
}

/*
 * @tc.name: setEnableAnalyzerTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasModifierTest, setEnableAnalyzerTestDefaultValues, TestSize.Level1)
{

    // test!!!
    auto jsonValue = GetJsonValue(node_);
    FromJson("setEnableAnalyzerTestDefaultValues", jsonValue);
    // test!!!=

    // std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    // std::string resultStr;

    // resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_ANALYZER_ENABLE_NAME);
    // EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_ANALYZER_ENABLE_DEFAULT_VALUE);
}

// Valid values for attribute 'enableAnalyzerEnable' of method 'enableAnalyzer'
static std::vector<std::tuple<std::string, Ark_Boolean, std::string>> enableAnalyzerEnableAnalyzerEnableValidValues = {
    {"true", Converter::ArkValue<Ark_Boolean>(true), "true"},
    {"false", Converter::ArkValue<Ark_Boolean>(false), "false"},
};

/*
 * @tc.name: setEnableAnalyzerTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasModifierTest, setEnableAnalyzerTestValidValues, TestSize.Level1)
{
    // std::unique_ptr<JsonValue> jsonValue;
    // std::string resultStr;
    // std::string expectedStr;
    // Ark_Boolean inputValueEnableAnalyzerEnable;
    // Ark_Boolean initValueEnableAnalyzerEnable;

    // // Initial setup
    // initValueEnableAnalyzerEnable = std::get<1>(enableAnalyzerEnableAnalyzerEnableValidValues[0]);

    // // Verifying attribute's  values
    // inputValueEnableAnalyzerEnable = initValueEnableAnalyzerEnable;
    // for (auto&& value: enableAnalyzerEnableAnalyzerEnableValidValues) {
    //     inputValueEnableAnalyzerEnable = std::get<1>(value);
    //     modifier_->setEnableAnalyzer(node_, inputValueEnableAnalyzerEnable);
    //     jsonValue = GetJsonValue(node_);
    //     resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_ANALYZER_ENABLE_NAME);
    //     expectedStr = std::get<2>(value);
    //     EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    // }
}
} // namespace OHOS::Ace::NG
