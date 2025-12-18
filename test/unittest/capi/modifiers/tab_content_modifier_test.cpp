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
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/pattern/tabs/tabs_model_ng.h"
#include "core/components_ng/pattern/tabs/tab_content_event_hub.h"
#include "arkoala_api_generated.h"
#include "test/unittest/capi/utils/custom_node_builder_test_helper.h"
#include "core/components_ng/pattern/tabs/tab_content_pattern.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::NG::Converter;

namespace OHOS::Ace::NG {
namespace {
using TestBaseUnionType =
    Opt_Union_ComponentContent_SubTabBarStyle_BottomTabBarStyle_String_Resource_CustomNodeBuilder_TabBarOptions;
using TabBarLabelResourceTest = std::tuple<Ark_Resource, std::string>;
// resource names and id
const auto RES_NAME = "aa.bb.cc";
const auto RES_ID = 11111;
const auto RES_NAME_ID = NamedResourceId{RES_NAME, ResourceType::STRING};
const auto RES_INT_ID = IntResourceId{RES_ID, ResourceType::STRING};
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
 * @tc.name: setTabBarTest
 * @tc.desc: check setTabBar interface work with only label
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModifierTest, setTabBarTestLabel, TestSize.Level1)
{
    const std::string PROP_NAME("text");
    const std::string TEXT_VALUE("test");
    std::unique_ptr<JsonValue> jsonValue;

    ASSERT_NE(modifier_->setTabBar, nullptr);
    auto args = ArkUnion<TestBaseUnionType, Ark_String>(TEXT_VALUE);
    modifier_->setTabBar(node_, &args);
    jsonValue = GetJsonValue(node_);
    auto checkInitial = GetAttrValue<std::string>(jsonValue, PROP_NAME);
    EXPECT_EQ(checkInitial, TEXT_VALUE);

    for (const auto &[label, checkVal]: BUTTON_LABEL_RESOURCES_TEST_PLAN) {
        auto args = ArkUnion<TestBaseUnionType, Ark_Resource>(label);
        modifier_->setTabBar(node_, &args);
        jsonValue = GetJsonValue(node_);
        auto checkInitial = GetAttrValue<std::string>(jsonValue, PROP_NAME);
        EXPECT_EQ(checkInitial, checkVal);
    }
}

/*
 * @tc.name: setTabBarTest_CustomNodeBuilder
 * @tc.desc: check setTabBar interface work with CustomBuilder
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModifierTest, DISABLED_setTabBarTestCustomNodeBuilder, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTabBar, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    int callsCount = 0;
    CustomNodeBuilderTestHelper<TabContentModifierTest> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    auto options = Converter::ArkUnion<TestBaseUnionType, CustomNodeBuilder>(builder);
    modifier_->setTabBar(frameNode, &options);

    auto pattern = frameNode->GetPattern<TabContentPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->GetTabBarParam().ExecuteBuilder();

    EXPECT_EQ(builderHelper.GetCallsCount(), ++callsCount);
}

/*
 * @tc.name: setTabBarTest
 * @tc.desc: check setTabBar interface work with label and icon
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModifierTest, setTabBarTestLabelIcon, TestSize.Level1)
{
    const std::string PROP_LABEL_NAME("text");
    const std::string PROP_ICON_NAME("icon");
    const std::string TEXT_VALUE("test");
    std::unique_ptr<JsonValue> jsonValue;

    ASSERT_NE(modifier_->setTabBar, nullptr);
    Ark_TabBarOptions labelIcon;
    labelIcon.icon = ArkUnion<Opt_Union_String_Resource, Ark_String>(TEXT_VALUE);
    labelIcon.text = ArkUnion<Opt_Union_String_Resource, Ark_String>(TEXT_VALUE);
    auto args = ArkUnion<TestBaseUnionType, Ark_TabBarOptions>(labelIcon);
    modifier_->setTabBar(node_, &args);
    jsonValue = GetJsonValue(node_);
    auto checkLabel = GetAttrValue<std::string>(jsonValue, PROP_LABEL_NAME);
    auto checkIcon = GetAttrValue<std::string>(jsonValue, PROP_ICON_NAME);
    EXPECT_EQ(checkLabel, TEXT_VALUE);
    EXPECT_EQ(checkIcon, TEXT_VALUE);

    for (const auto &[label, checkVal]: BUTTON_LABEL_RESOURCES_TEST_PLAN) {
        Ark_TabBarOptions labelIcon;
        labelIcon.icon = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(label);
        labelIcon.text = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(label);
        auto args = ArkUnion<TestBaseUnionType, Ark_TabBarOptions>(labelIcon);
        modifier_->setTabBar(node_, &args);
        jsonValue = GetJsonValue(node_);
        auto checkLabel = GetAttrValue<std::string>(jsonValue, PROP_LABEL_NAME);
        auto checkIcon = GetAttrValue<std::string>(jsonValue, PROP_ICON_NAME);
        EXPECT_EQ(checkLabel, checkVal);
        EXPECT_EQ(checkIcon, checkVal);
    }
}

/*
 * @tc.name: setTabBarBottomStyleTestText
 * @tc.desc: check setTabBar interface work with only text in BottomStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModifierTest, DISABLE_setTabBarBottomStyleTestText, TestSize.Level1)
{
#ifdef WRONG_GEN_SIG
    const std::string PROP_NAME("text");
    const std::string TEXT_VALUE("test");
    std::unique_ptr<JsonValue> jsonValue;

    ASSERT_NE(modifier_->setTabBar, nullptr);
    Ark_BottomTabBarStyle style;
    style._text = Converter::ArkValue<Opt_ResourceStr>(Converter::ArkUnion<Ark_ResourceStr, Ark_String>(TEXT_VALUE));
    style._icon = Converter::ArkValue<Opt_Union_ResourceStr_TabBarSymbol>(Ark_Empty());
    style._iconStyle = Converter::ArkValue<Opt_TabBarIconStyle>(Ark_Empty());
    style._id = Converter::ArkValue<Opt_String>(Ark_Empty());
    style._labelStyle = Converter::ArkValue<Opt_TabBarLabelStyle>(Ark_Empty());
    style._layoutMode = Converter::ArkValue<Opt_LayoutMode>(Ark_Empty());
    style._padding = Converter::ArkValue<Opt_Union_Padding_Dimension_LocalizedPadding>(Ark_Empty());
    style._symmetricExtensible = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    style._verticalAlign = Converter::ArkValue<Opt_VerticalAlign>(Ark_Empty());
    auto args = ArkUnion<TestBaseUnionType, Ark_BottomTabBarStyle>(style);
    modifier_->setTabBar(node_, &args);
    jsonValue = GetJsonValue(node_);
    auto checkInitial = GetAttrValue<std::string>(jsonValue, PROP_NAME);
    EXPECT_EQ(checkInitial, TEXT_VALUE);
#endif // WRONG_GEN_SIG
}

/*
 * @tc.name: setOnWillShowTest
 * @tc.desc: check functionality setOnWillShow
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModifierTest, setOnWillShowTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<TabContentEventHub>();

    struct CheckEvent {
        int32_t nodeId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;

    auto checkCallback = [](const Ark_Int32 resourceId) {
        checkEvent = {
            .nodeId = resourceId
        };
    };

    auto arkCallback = Converter::ArkCallback<Opt_VoidCallback>(checkCallback, contextId);
    modifier_->setOnWillShow(node_, &arkCallback);

    EXPECT_FALSE(checkEvent);
    eventHub->FireWillShowEvent();
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->nodeId, contextId);
}

/*
 * @tc.name: setOnWillHideTest
 * @tc.desc: check functionality setOnWillHide
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModifierTest, setOnWillHideTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<TabContentEventHub>();

    struct CheckEvent {
        int32_t nodeId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;

    auto checkCallback = [](const Ark_Int32 resourceId) {
        checkEvent = {
            .nodeId = resourceId
        };
    };

    auto arkCallback = Converter::ArkCallback<Opt_VoidCallback>(checkCallback, contextId);
    modifier_->setOnWillHide(node_, &arkCallback);

    EXPECT_FALSE(checkEvent);
    eventHub->FireWillHideEvent();
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->nodeId, contextId);
}
} // namespace OHOS::Ace::NG
