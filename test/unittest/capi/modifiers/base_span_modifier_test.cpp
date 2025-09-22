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
    const auto ATTRIBUTE_TEXT_BASELINE_OFFSET_NAME = "baselineOffset";
    const auto ATTRIBUTE_TEXT_BASELINE_OFFSET_DEFAULT_VALUE = "0.00px";
} // namespace

class BaseSpanModifierTest : public ModifierTestBase<GENERATED_ArkUIBaseSpanModifier,
    &GENERATED_ArkUINodeModifiers::getBaseSpanModifier, GENERATED_ARKUI_BASE_SPAN> {
};


/*
 * @tc.name: setBaselineOffsetTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BaseSpanModifierTest, DISABLED_setBaselineOffsetTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_BASELINE_OFFSET_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_BASELINE_OFFSET_DEFAULT_VALUE);
}

// Valid values for method 'baselineOffset'
using LengthMetrictsTestStep = std::pair<Ark_LengthMetrics, std::string>;
static const std::vector<LengthMetrictsTestStep> LENGTH_METRICS_ANY_TEST_PLAN = {
    { Converter::ArkCreate<Ark_LengthMetrics>(ARK_LENGTH_UNIT_PX, 1.f), "1.00px" },
    { Converter::ArkCreate<Ark_LengthMetrics>(ARK_LENGTH_UNIT_PX, 0.f), "0.00px" },
    { Converter::ArkCreate<Ark_LengthMetrics>(ARK_LENGTH_UNIT_VP, 2.45f), "2.45vp" },
    { Converter::ArkCreate<Ark_LengthMetrics>(ARK_LENGTH_UNIT_VP, -7.f), "-7.00vp" },
    { Converter::ArkCreate<Ark_LengthMetrics>(ARK_LENGTH_UNIT_FP, -65.5f), "-65.50fp" },
};

/*
 * @tc.name: setBaselineOffsetTestValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BaseSpanModifierTest, DISABLED_setBaselineOffsetTestValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_LengthMetrics inputBaselineOffset;

    for (auto&& value: LENGTH_METRICS_ANY_TEST_PLAN) {
        inputBaselineOffset = std::get<0>(value);
        auto optInputBaselineOffset = Converter::ArkValue<Opt_LengthMetrics>(inputBaselineOffset);
        modifier_->setBaselineOffset(node_, &optInputBaselineOffset);

        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_BASELINE_OFFSET_NAME);
        expectedStr = std::get<1>(value);
        EXPECT_EQ(resultStr, expectedStr);
}
}

} // namespace OHOS::Ace::NG
