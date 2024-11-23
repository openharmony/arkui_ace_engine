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
    const auto ATTRIBUTE_ALLOW_UPDATE_NAME = "allowUpdate";
    const auto ATTRIBUTE_ALLOW_UPDATE_DEFAULT_VALUE = "true";
} // namespace

class FormComponentModifierTest : public ModifierTestBase<GENERATED_ArkUIFormComponentModifier,
    &GENERATED_ArkUINodeModifiers::getFormComponentModifier, GENERATED_ARKUI_FORM_COMPONENT> {

    void SetUp(void) override
    {
        ModifierTestBase::SetUp();
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        frameNode->MarkModifyDone();
    }
};

/*
 * @tc.name: setAllowUpdateTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, setAllowUpdateTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ALLOW_UPDATE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALLOW_UPDATE_DEFAULT_VALUE);
}

// Valid values for attribute 'allowUpdate' of method 'allowUpdate'
static std::vector<std::tuple<std::string, Ark_Boolean, std::string>> allowUpdateAllowUpdateValidValues = {
    {"true", Converter::ArkValue<Ark_Boolean>(true), "true"},
    {"false", Converter::ArkValue<Ark_Boolean>(false), "false"},
};

/*
 * @tc.name: setAllowUpdateTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, setAllowUpdateTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Boolean inputValueAllowUpdate;
    Ark_Boolean initValueAllowUpdate;

    // Initial setup
    initValueAllowUpdate = std::get<1>(allowUpdateAllowUpdateValidValues[0]);

    // Verifying attribute's  values
    inputValueAllowUpdate = initValueAllowUpdate;
    for (auto&& value: allowUpdateAllowUpdateValidValues) {
        inputValueAllowUpdate = std::get<1>(value);
        modifier_->setAllowUpdate(node_, inputValueAllowUpdate);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ALLOW_UPDATE_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}
} // namespace OHOS::Ace::NG
