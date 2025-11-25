/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
#include "test_fixtures.h"
#include "type_helpers.h"

#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;
namespace {
const auto ATTRIBUTE_POINTS_NAME = "points";
const auto ATTRIBUTE_POINTS_DEFAULT_VALUE = "!NOT-DEFINED!";
} // namespace

class PolygonModifierTest : public ModifierTestBase<GENERATED_ArkUIPolygonModifier,
                                &GENERATED_ArkUINodeModifiers::getPolygonModifier, GENERATED_ARKUI_POLYGON> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        for (auto& [id, strid, res] : Fixtures::resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
    }
};

/*
 * @tc.name: setPointsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModifierTest, DISABLED_setPointsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_POINTS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_POINTS_DEFAULT_VALUE) << "Default value for attribute 'points'";
}

/*
 * @tc.name: setPointsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModifierTest, DISABLED_setPointsTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}
} // namespace OHOS::Ace::NG
