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
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace  {
    const auto ATTRIBUTE_RESIZEABLE_NAME = "resizeable";
    const auto ATTRIBUTE_RESIZEABLE_DEFAULT_VALUE = "false";
} // namespace

class RowSplitModifierTest : public ModifierTestBase<GENERATED_ArkUIRowSplitModifier,
    &GENERATED_ArkUINodeModifiers::getRowSplitModifier, GENERATED_ARKUI_ROW_SPLIT> {
};

/*
 * @tc.name: setResizeableTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RowSplitModifierTest, setResizeableTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RESIZEABLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_RESIZEABLE_DEFAULT_VALUE);
}

// Valid values for attribute 'resizeable' of method 'resizeable'
static std::vector<std::tuple<std::string, Opt_Boolean, std::string>> resizeableValidValues = {
    {"true", Converter::ArkValue<Opt_Boolean>(true), "true"},
    {"false", Converter::ArkValue<Opt_Boolean>(false), "false"},
};

/*
 * @tc.name: setResizeableTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RowSplitModifierTest, setResizeableTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    for (auto [passed, checkVal, expected]: resizeableValidValues) {
        modifier_->setResizeable(node_, &checkVal);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RESIZEABLE_NAME);
        EXPECT_EQ(resultStr, expected) << "Passed value is: " << passed;
    }
}

} // namespace OHOS::Ace::NG
