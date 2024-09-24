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

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "node_api.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_theme_style.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "core/components/button/button_theme.h"

#include "core/interfaces/arkoala/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
    
using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace {
    Ark_Resource ArkResource(Ark_String* name, int id = -1,
        NodeModifier::ResourceType type = NodeModifier::ResourceType::COLOR)
    {
        return {
            .id = Converter::ArkValue<Ark_Number>(id),
            .type = Converter::ArkValue<Ark_Number>(static_cast<int>(type)),
            .moduleName = Converter::ArkValue<Ark_String>(""),
            .bundleName = Converter::ArkValue<Ark_String>(""),
            .params = {
                .tag = ARK_TAG_OBJECT,
                .value = { .array = name, .length = name ? 1 : 0 }
            }
        };
    }
    // attrs
    const auto ATTRIBUTE_LABEL_NAME("label");
    const auto ATTRIBUTE_TYPE_NAME("type");
    const auto ATTRIBUTE_ROLE_NAME("role");
    const auto ATTRIBUTE_STATE_EFFECT_NAME("stateEffect");
    const auto ATTRIBUTE_CONTROL_SIZE_NAME("controlSize");
    const auto ATTRIBUTE_BUTTON_STYLE_NAME("buttonStyle");

    using ButtonLabelResourceTest = std::pair<ResourceStr, std::string>;

    // resource names and id
    const auto RES_NAME = "aa.bb.cc";
    const auto RES_ARK_NAME = Converter::ArkValue<Ark_String>(RES_NAME);
    const auto RES_ID = 11111;

    // resource values
    const auto RESOURCE_BY_STRING = "ResourceByString";
    const auto RESOURCE_BY_NUMBER = "ResourceByNumber";

    const std::vector<ButtonLabelResourceTest> BUTTON_LABEL_RESOURCES_TEST_PLAN = {
        { Converter::ArkUnion<ResourceStr, Ark_Resource>(ArkResource(const_cast<Ark_String*>(&RES_ARK_NAME),
            -1, NodeModifier::ResourceType::STRING)),
            RESOURCE_BY_STRING },
        { Converter::ArkUnion<ResourceStr, Ark_Resource>(ArkResource(nullptr, RES_ID,
            NodeModifier::ResourceType::STRING)),
            RESOURCE_BY_NUMBER }
    };
} // namespace

class ButtonModifierResourcesTest : public ModifierTestBase<GENERATED_ArkUIButtonModifier,
    &GENERATED_ArkUINodeModifiers::getButtonModifier, GENERATED_ARKUI_BUTTON> {
public:
    static void SetUpTestCase()
    {
        MockPipelineContext::SetUp();

        // assume using of test/mock/core/common/mock_theme_constants.cpp in build
        auto themeConstants = AceType::MakeRefPtr<ThemeConstants>(nullptr);

        // set test values to Theme Pattern as data for the Theme building
        auto themeStyle = AceType::MakeRefPtr<ThemeStyle>();
        MockThemeStyle::GetInstance()->SetAttr(std::to_string(RES_ID),
            { .value = RESOURCE_BY_NUMBER, .type = ThemeConstantsType::STRING });
        MockThemeStyle::GetInstance()->SetAttr(RES_NAME,
            { .value = RESOURCE_BY_STRING, .type = ThemeConstantsType::STRING });
        themeConstants->LoadTheme(0);

        // build default ButtonTheme
        ButtonTheme::Builder builder;
        auto buttonTheme = builder.Build(themeConstants);

        // create Theme Manager and provide return of ButtonTheme
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        EXPECT_CALL(*themeManager, GetThemeConstants(testing::_, testing::_))
            .WillRepeatedly(Return(themeConstants));
        EXPECT_CALL(*themeManager, GetTheme(testing::_))
            .WillRepeatedly(Return(buttonTheme));

        // setup Context with Theme Manager and Container
        MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
        MockContainer::SetUp(MockPipelineContext::GetCurrent());
        MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    }

    static void TearDownTestCase()
    {
        MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
        MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }
};

/*
 * @tc.name: SetButtonOptions2TestButtonRole
 * @tc.desc: Check the functionality of ButtonModifier.SetButtonOptions2
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierResourcesTest, SetButtonOptions2TestLabelResource, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    // Initial setup
    Ark_ButtonOptions inputValueOptions;
    inputValueOptions.type = Converter::ArkValue<Opt_ButtonType>(ARK_BUTTON_TYPE_CAPSULE);
    inputValueOptions.stateEffect = Converter::ArkValue<Opt_Boolean>(true);
    inputValueOptions.buttonStyle = Converter::ArkValue<Opt_ButtonStyleMode>(ARK_BUTTON_STYLE_MODE_NORMAL);
    inputValueOptions.controlSize = Converter::ArkValue<Opt_ControlSize>(ARK_CONTROL_SIZE_SMALL);
    inputValueOptions.role = Converter::ArkValue<Opt_ButtonRole>(ARK_BUTTON_ROLE_NORMAL);
    auto labelString = BUTTON_LABEL_RESOURCES_TEST_PLAN.at(0).first;
    auto optInputValueOptions = Converter::ArkValue<Opt_ButtonOptions>(inputValueOptions);
    // Test
    modifier_->setButtonOptions2(node_, &labelString, &optInputValueOptions);
    // Initial verification
    jsonValue = GetJsonValue(node_);
    auto checkType = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    auto checkStateEffect = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_EFFECT_NAME);
    auto checkButtonStyle = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
    auto checkControlSize = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
    auto checkRole = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);
    auto checkLabel = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LABEL_NAME);
    EXPECT_EQ(checkType, "ButtonType.Capsule");
    EXPECT_EQ(checkStateEffect, "true");
    EXPECT_EQ(checkButtonStyle, "ButtonStyleMode.NORMAL");
    EXPECT_EQ(checkControlSize, "ControlSize.SMALL");
    EXPECT_EQ(checkRole, "ButtonRole.NORMAL");
    EXPECT_EQ(checkLabel, BUTTON_LABEL_RESOURCES_TEST_PLAN.at(0).second);
    
    for (auto label : BUTTON_LABEL_RESOURCES_TEST_PLAN) {
        modifier_->setButtonOptions2(node_, &label.first, &optInputValueOptions);
        checkLabel = GetAttrValue<std::string>(jsonValue, label.second);
    }
}
} // namespace OHOS::Ace::NG
