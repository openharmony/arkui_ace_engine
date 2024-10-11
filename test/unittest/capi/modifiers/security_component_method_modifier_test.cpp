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
#include "core/components_ng/pattern/security_component/save_button/save_button_model_ng.h"
#include "core/components_ng/pattern/security_component/security_component_model_ng.h"
#include "core/components_ng/pattern/security_component/security_component_theme.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace  {
    const auto ATTRIBUTE_LAYOUT_DIRECTION_NAME = "layoutDirection";
    const auto ATTRIBUTE_LAYOUT_DIRECTION_DEFAULT_VALUE = SecurityComponentLayoutDirection::HORIZONTAL;

    const auto DEFAULT_JSON_INT = -1;
} // namespace

class SecurityComponentMethodModifierTest : public ModifierTestBase<GENERATED_ArkUISecurityComponentMethodModifier,
    &GENERATED_ArkUINodeModifiers::getSecurityComponentMethodModifier, GENERATED_ARKUI_SAVE_BUTTON> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<SecurityComponentTheme>();
    }

    void SetUp(void) override
    {
        ModifierTestBase::SetUp();

        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        SecurityComponentElementStyle style;
        SaveButtonModelNG::InitSaveButton(frameNode, style, false);
    }
};

/*
 * @tc.name: setIconSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setIconSizeTestDefaultValues, TestSize.Level1)
{
    ASSERT_TRUE(false);
}

/*
 * @tc.name: setIconSizeTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setIconSizeTestValidValues, TestSize.Level1)
{
    ASSERT_TRUE(false);
}

/*
 * @tc.name: setIconSizeTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setIconSizeTestInvalidValues, TestSize.Level1)
{
    ASSERT_TRUE(false);
}

/*
 * @tc.name: setLayoutDirectionTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setLayoutDirectionTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    int32_t result;

    result = jsonValue->GetInt(ATTRIBUTE_LAYOUT_DIRECTION_NAME, DEFAULT_JSON_INT);
    EXPECT_EQ(result, static_cast<int32_t>(ATTRIBUTE_LAYOUT_DIRECTION_DEFAULT_VALUE));
}

// Valid values for attribute 'layoutDirection' of method 'layoutDirection'
static std::vector<std::tuple<std::string, enum Ark_SecurityComponentLayoutDirection, enum SecurityComponentLayoutDirection>> layoutDirectionLayoutDirectionValidValues = {
    {
        "ARK_SECURITY_COMPONENT_LAYOUT_DIRECTION_HORIZONTAL",
        ARK_SECURITY_COMPONENT_LAYOUT_DIRECTION_HORIZONTAL,
        SecurityComponentLayoutDirection::HORIZONTAL
    },
    {
        "ARK_SECURITY_COMPONENT_LAYOUT_DIRECTION_VERTICAL",
        ARK_SECURITY_COMPONENT_LAYOUT_DIRECTION_VERTICAL,
        SecurityComponentLayoutDirection::VERTICAL
    }
};

/*
 * @tc.name: setLayoutDirectionTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setLayoutDirectionTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    int32_t result;
    int32_t expected;
    enum Ark_SecurityComponentLayoutDirection inputValueLayoutDirection;
    enum Ark_SecurityComponentLayoutDirection initValueLayoutDirection;

    // Initial setup
    initValueLayoutDirection = std::get<1>(layoutDirectionLayoutDirectionValidValues[0]);

    // Verifying attribute's  values
    inputValueLayoutDirection = initValueLayoutDirection;
    for (auto&& value: layoutDirectionLayoutDirectionValidValues) {
        inputValueLayoutDirection = std::get<1>(value);
        modifier_->setLayoutDirection(node_, inputValueLayoutDirection);
        jsonValue = GetJsonValue(node_);
        result = jsonValue->GetInt(ATTRIBUTE_LAYOUT_DIRECTION_NAME, DEFAULT_JSON_INT);
        expected = static_cast<int32_t>(std::get<2>(value));
        EXPECT_EQ(result, expected) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'layoutDirection' of method 'layoutDirection'
static std::vector<std::tuple<std::string, enum Ark_SecurityComponentLayoutDirection>> layoutDirectionLayoutDirectionInvalidValues = {
    {
        "static_cast<enum Ark_SecurityComponentLayoutDirection>(-1)",
        static_cast<enum Ark_SecurityComponentLayoutDirection>(-1)
    },
};

/*
 * @tc.name: setLayoutDirectionTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setLayoutDirectionTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    int32_t result;
    int32_t expected;
    enum Ark_SecurityComponentLayoutDirection inputValueLayoutDirection;
    enum Ark_SecurityComponentLayoutDirection initValueLayoutDirection;

    // Initial setup
    initValueLayoutDirection = std::get<1>(layoutDirectionLayoutDirectionValidValues[0]);

    // Verifying attribute's  values
    for (auto&& value: layoutDirectionLayoutDirectionInvalidValues) {
        inputValueLayoutDirection = initValueLayoutDirection;
        modifier_->setLayoutDirection(node_, inputValueLayoutDirection);
        inputValueLayoutDirection = std::get<1>(value);
        modifier_->setLayoutDirection(node_, inputValueLayoutDirection);
        jsonValue = GetJsonValue(node_);
        result = jsonValue->GetInt(ATTRIBUTE_LAYOUT_DIRECTION_NAME, DEFAULT_JSON_INT);
        expected = static_cast<int32_t>(ATTRIBUTE_LAYOUT_DIRECTION_DEFAULT_VALUE);
        EXPECT_EQ(result, expected) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setFontSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setFontSizeTestDefaultValues, TestSize.Level1)
{
    ASSERT_TRUE(false);
}

/*
 * @tc.name: setFontSizeTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setFontSizeTestValidValues, TestSize.Level1)
{
    ASSERT_TRUE(false);
}

/*
 * @tc.name: setFontSizeTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setFontSizeTestInvalidValues, TestSize.Level1)
{
    ASSERT_TRUE(false);
}

/*
 * @tc.name: setBorderStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setBorderStyleTestDefaultValues, TestSize.Level1)
{
    ASSERT_TRUE(false);
}

/*
 * @tc.name: setBorderStyleTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setBorderStyleTestValidValues, TestSize.Level1)
{
    ASSERT_TRUE(false);
}

/*
 * @tc.name: setBorderStyleTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setBorderStyleTestInvalidValues, TestSize.Level1)
{
    ASSERT_TRUE(false);
}

/*
 * @tc.name: setTextIconSpaceTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setTextIconSpaceTestDefaultValues, TestSize.Level1)
{
    ASSERT_TRUE(false);
}

/*
 * @tc.name: setTextIconSpaceTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setTextIconSpaceTestValidValues, TestSize.Level1)
{
    ASSERT_TRUE(false);
}

/*
 * @tc.name: setTextIconSpaceTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setTextIconSpaceTestInvalidValues, TestSize.Level1)
{
    ASSERT_TRUE(false);
}

} // namespace OHOS::Ace::NG