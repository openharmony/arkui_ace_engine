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
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace  {
    const auto ATTRIBUTE_ALIGN_NAME = "align";
    const auto ATTRIBUTE_ALIGN_DEFAULT_VALUE = "Alignment.TopStart";
} // namespace

class CommonModifierTest : public ModifierTestBase<
    GENERATED_ArkUICommonModifier, &GENERATED_ArkUINodeModifiers::getCommonModifier, GENERATED_ARKUI_COMMON> {
};

/*
 * @tc.name: commonTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonModifierTest, commonTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> json = GetJsonValue(node_);
    const auto result = GetAttrValue<std::string>(json, ATTRIBUTE_ALIGN_NAME);
    EXPECT_EQ(result, ATTRIBUTE_ALIGN_DEFAULT_VALUE);
}

} // namespace OHOS::Ace::NG
