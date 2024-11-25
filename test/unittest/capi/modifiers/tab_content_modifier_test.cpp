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
#include "core/interfaces/native/node/node_api.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/pattern/tabs/tabs_model_ng.h"
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::NG::Converter;

namespace OHOS::Ace::NG {
namespace {
using TestBaseUnionType = Ark_Type_TabContentAttribute_tabBar_value;
using TabBarLabelResourceTest = std::tuple<Ark_Resource, std::string>;
// resource names and id
const auto RES_NAME = "aa.bb.cc";
const auto RES_ID = 11111;
const auto RES_NAME_ID = NamedResourceId{RES_NAME, NodeModifier::ResourceType::STRING};
const auto RES_INT_ID = IntResourceId{RES_ID, NodeModifier::ResourceType::STRING};
// resource values
const auto RESOURCE_BY_STRING = "ResourceByString";
const auto RESOURCE_BY_NUMBER = "ResourceByNumber";

const std::vector<TabBarLabelResourceTest> BUTTON_LABEL_RESOURCES_TEST_PLAN = {
    { CreateResource(RES_NAME_ID), RESOURCE_BY_STRING },
    { CreateResource(RES_INT_ID), RESOURCE_BY_NUMBER },
};
} // namespace

class TabContentModifierTest : public ModifierTestBase<GENERATED_ArkUITabContentModifier,
    &GENERATED_ArkUINodeModifiers::getTabContentModifier,
    GENERATED_ARKUI_TAB_CONTENT> {
    public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<TabTheme>();

        // set test values to Theme Pattern as data for the Theme building
        AddResource(RES_ID, RESOURCE_BY_NUMBER);
        AddResource(RES_NAME, RESOURCE_BY_STRING);
    }
};

/*
 * @tc.name: setTabBar0Test
 * @tc.desc: check setTabBar0 interface work with only label
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModifierTest, setTabBar0TestLabel, TestSize.Level1)
{
    const std::string PROP_NAME("text");
    const std::string TEXT_VALUE("test");
    std::unique_ptr<JsonValue> jsonValue;

    ASSERT_NE(modifier_->setTabBar0, nullptr);
    auto args = ArkUnion<TestBaseUnionType, Ark_String>(TEXT_VALUE);
    modifier_->setTabBar0(node_, &args);
    jsonValue = GetJsonValue(node_);
    auto checkInitial = GetAttrValue<std::string>(jsonValue, PROP_NAME);
    EXPECT_EQ(checkInitial, TEXT_VALUE);

    for (const auto &[label, checkVal]: BUTTON_LABEL_RESOURCES_TEST_PLAN) {
        auto args = ArkUnion<TestBaseUnionType, Ark_Resource>(label);
        modifier_->setTabBar0(node_, &args);
        jsonValue = GetJsonValue(node_);
        auto checkInitial = GetAttrValue<std::string>(jsonValue, PROP_NAME);
        EXPECT_EQ(checkInitial, checkVal);
    }
}

/*
 * @tc.name: setTabBar0Test
 * @tc.desc: check setTabBar0 interface work with CustomBuilder
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModifierTest, DISABLED_setTabBar0TestCustomBuilder, TestSize.Level1)
{
    // will be implemented when CustomBuilder in the setTabBar0 will be supported
}

/*
 * @tc.name: setTabBar0Test
 * @tc.desc: check setTabBar0 interface work with label and icon
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModifierTest, setTabBar0TestLabelIcon, TestSize.Level1)
{
    const std::string PROP_LABEL_NAME("text");
    const std::string PROP_ICON_NAME("icon");
    const std::string TEXT_VALUE("test");
    std::unique_ptr<JsonValue> jsonValue;

    ASSERT_NE(modifier_->setTabBar0, nullptr);
    Ark_Literal_Union_String_Resource_icon_text labelIcon;
    labelIcon.icon = ArkUnion<Opt_Union_String_Resource, Ark_String>(TEXT_VALUE);
    labelIcon.text = ArkUnion<Opt_Union_String_Resource, Ark_String>(TEXT_VALUE);
    auto args = ArkUnion<TestBaseUnionType, Ark_Literal_Union_String_Resource_icon_text>(labelIcon);
    modifier_->setTabBar0(node_, &args);
    jsonValue = GetJsonValue(node_);
    auto checkLabel = GetAttrValue<std::string>(jsonValue, PROP_LABEL_NAME);
    auto checkIcon = GetAttrValue<std::string>(jsonValue, PROP_ICON_NAME);
    EXPECT_EQ(checkLabel, TEXT_VALUE);
    EXPECT_EQ(checkIcon, TEXT_VALUE);

    for (const auto &[label, checkVal]: BUTTON_LABEL_RESOURCES_TEST_PLAN) {
        Ark_Literal_Union_String_Resource_icon_text labelIcon;
        labelIcon.icon = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(label);
        labelIcon.text = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(label);
        auto args = ArkUnion<TestBaseUnionType, Ark_Literal_Union_String_Resource_icon_text>(labelIcon);
        modifier_->setTabBar0(node_, &args);
        jsonValue = GetJsonValue(node_);
        auto checkLabel = GetAttrValue<std::string>(jsonValue, PROP_LABEL_NAME);
        auto checkIcon = GetAttrValue<std::string>(jsonValue, PROP_ICON_NAME);
        EXPECT_EQ(checkLabel, checkVal);
        EXPECT_EQ(checkIcon, checkVal);
    }
}

/*
 * @tc.name: DISABLED_setOnWillShowTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModifierTest, DISABLED_setOnWillShowTest, TestSize.Level1)
{
    // setOnWillShowTest doesn't implemented
}

/*
 * @tc.name: DISABLED_setOnWillHideTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModifierTest, DISABLED_setOnWillHideTest, TestSize.Level1)
{
    // setOnWillHideTest doesn't implemented
}
} // namespace OHOS::Ace::NG
