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

#include "generated/test_fixtures.h"
#include "modifier_test_base.h"
#include "modifiers_test_utils.h"

#include "core/components/progress/progress_theme.h"

#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace {
const Color THEME_LOADING_COLOR(0xFFAABBCC);

const auto ATTRIBUTE_COLOR_NAME = "color";
} // namespace

class LoadingProgressModifierTest : public ModifierTestBase<GENERATED_ArkUILoadingProgressModifier,
    &GENERATED_ArkUINodeModifiers::getLoadingProgressModifier, GENERATED_ARKUI_LOADING_PROGRESS> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        // set test values to Theme Pattern as data for the Theme building
        auto themeStyle = SetupThemeStyle("progress_pattern");
        themeStyle->SetAttr("fg_progress_color", { .value = THEME_LOADING_COLOR });

        SetupTheme<ProgressTheme>();

        for (const auto &[resId, resName, value] : Fixtures::resourceInitTable) {
            AddResource(resId, value);
            AddResource(resName, value);
        }
    }
};

/**
 * @tc.name: setColorTest
 * @tc.desc: Test setColor function
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressModifierTest, DISABLED_setColorTest, TestSize.Level1)
{
    constexpr auto PROP_NAME = "color";
    ASSERT_NE(modifier_->setColor, nullptr);

    auto checkVal1 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal1, THEME_LOADING_COLOR.ToString());

    Ark_ResourceColor color = ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_WHITE);
    auto optColor = Converter::ArkValue<Opt_ResourceColor>(color);
    modifier_->setColor(node_, &optColor);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "#FFFFFFFF");

    Ark_ResourceColor numberInt = ArkUnion<Ark_ResourceColor, Ark_Number>(0x123401);
    auto optNumberInt = Converter::ArkValue<Opt_ResourceColor>(numberInt);
    modifier_->setColor(node_, &optNumberInt);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "#FF123401");

    Ark_ResourceColor numberFlt = ArkUnion<Ark_ResourceColor, Ark_Number>(0.5f);
    auto optNumberFlt = Converter::ArkValue<Opt_ResourceColor>(numberFlt);
    modifier_->setColor(node_, &optNumberFlt);
    auto checkVal4 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal4, "#00000000");

    Ark_ResourceColor strColor = ArkUnion<Ark_ResourceColor, Ark_String>("#11223344");
    auto optStrColor = Converter::ArkValue<Opt_ResourceColor>(strColor);
    modifier_->setColor(node_, &optStrColor);
    auto checkVal5 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal5, "#11223344");

    Ark_ResourceColor strNumber = ArkUnion<Ark_ResourceColor, Ark_String>("65535");
    auto optStrNumber = Converter::ArkValue<Opt_ResourceColor>(strNumber);
    modifier_->setColor(node_, &optStrNumber);
    auto checkVal6 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal6, "#FF00FFFF");
}

/**
 * @tc.name: setColorTestResource
 * @tc.desc: Test setColor function
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressModifierTest, setColorTestResource, TestSize.Level1)
{
    auto checkValue = [this](const std::string& input, const Ark_ResourceColor& value,
        const std::string& expectedStr) {
        auto optValue = Converter::ArkValue<Opt_ResourceColor>(value);
        modifier_->setColor(node_, &optValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << input;
    };

    for (const auto &[input, value, expectedStr]: Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(value), expectedStr);
    }
}

/**
 * @tc.name: setEnableLoadingTest
 * @tc.desc: Test setEnableLoading function
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressModifierTest, setEnableLoadingTest, TestSize.Level1)
{
    constexpr auto PROP_NAME = "enableLoading";
    ASSERT_NE(modifier_->setEnableLoading, nullptr);

    auto checkVal1 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal1, "true");

    auto optValue = Converter::ArkValue<Opt_Boolean>(false);
    modifier_->setEnableLoading(node_, &optValue);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "false");

    optValue = Converter::ArkValue<Opt_Boolean>(true);
    modifier_->setEnableLoading(node_, &optValue);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "true");
}

} // namespace OHOS::Ace::NG
