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
#include "base/geometry/dimension.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "core/components_v2/list/list_properties.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/pattern/list/list_event_hub.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/pattern/select/select_model_ng.h"
#include "core/components_ng/pattern/select/select_pattern.h"
#include "test/mock/core/common/mock_theme_style.h"


namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

const std::string COLOR_RED = "#FFFF0000";
const std::string COLOR_BLACK = "#FF000000";
const std::string COLOR_TRANSPARENT = "#00000000";
const auto COLOR_COLOR_RES = CreateResource("color_name", Converter::ResourceType::COLOR);
const auto COLOR_ID_RES = CreateResource(1234, Converter::ResourceType::COLOR);
const auto COLOR_STRING_RES = CreateResource("color_name", Converter::ResourceType::STRING);

typedef std::tuple<Ark_ResourceColor, std::string> ColorTestStep;
const std::vector<ColorTestStep> COLOR_TEST_PLAN = {
    { Converter::ArkUnion<Ark_ResourceColor, enum Ark_Color>(ARK_COLOR_BLUE), "#FF0000FF" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0x123456), "#FF123456" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0.5f), COLOR_TRANSPARENT },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#11223344"), "#11223344" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("65535"), "#FF00FFFF" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("incorrect_color"), COLOR_BLACK },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>(""), COLOR_BLACK }
};
const std::vector<ColorTestStep> COLOR_TEST_PLAN_RES = {
    // Color::RED is result of mocked ThemeConstants::GetColorByName
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(COLOR_COLOR_RES), COLOR_RED },
    // Color::RED is result of mocked ThemeConstants::GetColor(int)
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(COLOR_ID_RES), COLOR_RED },
    // Color::RED
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(COLOR_STRING_RES), COLOR_RED }
};

const Ark_Int32 AINT32_POS(70);
const Ark_Int32 AINT32_NEG(INT_MIN);
const Ark_Float32 AFLT32_POS(1.234f);
const Ark_Float32 AFLT32_NEG(-5.6789f);

const auto RES_CONTENT = Converter::ArkValue<Ark_String>("aa.bb.cc");
const auto FAMILY_RES_ID = 555;
const auto FAMILY_NAME_RES = CreateResource(FAMILY_RES_ID, Converter::ResourceType::STRARRAY);
const Opt_Union_String_Resource OPT_UNION_RESOURCE_RESOURCE =
    Converter::ArkUnion<Opt_Union_String_Resource, Ark_Resource>(FAMILY_NAME_RES);

const std::string CHECK_RESOURCE_STR("aa.bb.cc");

typedef std::pair<Opt_Union_String_Resource, std::string> UnionStringResourceTestStep;
const std::vector<UnionStringResourceTestStep> UNION_RESOURCE_STRING_PLAN = {
    { Converter::ArkUnion<Opt_Union_String_Resource, Ark_String>(RES_CONTENT), CHECK_RESOURCE_STR },
    { OPT_UNION_RESOURCE_RESOURCE, CHECK_RESOURCE_STR }
};

typedef std::pair<Opt_Length, std::string> OptLengthTestStep;
const std::vector<OptLengthTestStep> OPT_LENGTH_TEST_PLAN = {
    { Converter::ArkValue<Opt_Length>(AINT32_POS), "70.00px" },
    { Converter::ArkValue<Opt_Length>(AINT32_NEG), "0.00px" },
    { Converter::ArkValue<Opt_Length>(AFLT32_NEG), "0.00px" },
    { Converter::ArkValue<Opt_Length>(AFLT32_POS), "1.23vp" } };

typedef std::pair<Opt_FontStyle, std::string> ArkFontStyleTestStep;
const std::vector<ArkFontStyleTestStep> FONT_STYLE_TEST_PLAN = {
    { { .tag = ARK_TAG_OBJECT, .value = ARK_FONT_STYLE_NORMAL }, "FontStyle.Normal" },
    { { .tag = ARK_TAG_OBJECT, .value = ARK_FONT_STYLE_ITALIC }, "FontStyle.Italic" },
    { { .tag = ARK_TAG_OBJECT, .value = static_cast<Ark_FontStyle>(2) }, "FontStyle.Normal" },
};

typedef std::pair<Opt_Union_FontWeight_Number_String, std::string> ArkFontWeightTest;
const std::vector<ArkFontWeightTest> FONT_WEIGHT_TEST_PLAN = {
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(ARK_FONT_WEIGHT_LIGHTER),
        "FontWeight.Lighter" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(ARK_FONT_WEIGHT_NORMAL),
        "FontWeight.Normal" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(ARK_FONT_WEIGHT_REGULAR),
        "FontWeight.Regular" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(ARK_FONT_WEIGHT_MEDIUM),
        "FontWeight.Medium" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(ARK_FONT_WEIGHT_BOLD),
        "FontWeight.Bold" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(ARK_FONT_WEIGHT_BOLDER),
        "FontWeight.Bolder" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("lighter")),
        "FontWeight.Lighter" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("normal")),
        "FontWeight.Normal" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("regular")),
        "FontWeight.Regular" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("medium")),
        "FontWeight.Medium" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("bold")),
        "FontWeight.Bold" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("bolder")),
        "FontWeight.Bolder" }
};

const std::vector<ArkFontWeightTest> FONT_WEIGHT_TEST_PLAN2 = {
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(Converter::ArkValue<Ark_Number>(100)),
        "100" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(Converter::ArkValue<Ark_Number>(200)),
        "200" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(Converter::ArkValue<Ark_Number>(300)),
        "300" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(Converter::ArkValue<Ark_Number>(400)),
        "400" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(Converter::ArkValue<Ark_Number>(500)),
        "500" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(Converter::ArkValue<Ark_Number>(600)),
        "600" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(Converter::ArkValue<Ark_Number>(700)),
        "700" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(Converter::ArkValue<Ark_Number>(800)),
        "800" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(Converter::ArkValue<Ark_Number>(900)),
        "900" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("100")),
        "100" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("200")),
        "200" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("300")),
        "300" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("400")),
        "400" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("500")),
        "500" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("600")),
        "600" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("700")),
        "700" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("800")),
        "800" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("900")),
        "900" }
};

const std::string DIVIDER_DEFAULT = "0.00vp";
const std::vector<std::pair<Ark_Number, std::string>> DIVIDER_VALUES = {
    { Converter::ArkValue<Ark_Number>(1), "1.00px" },
    { Converter::ArkValue<Ark_Number>(-1), DIVIDER_DEFAULT }};

class MenuModifierTest : public ModifierTestBase<GENERATED_ArkUIMenuModifier,
    &GENERATED_ArkUINodeModifiers::getMenuModifier, GENERATED_ARKUI_MENU> {
public:
    static void SetUpTestCase()
    {
        MockPipelineContext::SetUp();
        // assume using of test/mock/core/common/mock_theme_constants.cpp in build
        auto themeConstants = AceType::MakeRefPtr<ThemeConstants>(nullptr);
        // set test values to Theme Pattern as data for the Theme building
        auto themeStyle = AceType::MakeRefPtr<ThemeStyle>();
        MockThemeStyle::GetInstance()->SetAttr("select_pattern", { .value = themeStyle });
        themeConstants->LoadTheme(0);
        auto selectTheme = SelectTheme::Builder().Build(themeConstants);
        auto menuTheme = MenuTheme::Builder().Build(nullptr);
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        EXPECT_CALL(*themeManager, GetThemeConstants(testing::_, testing::_)).WillRepeatedly(Return(themeConstants));
        auto getThemeMockFunc = [selectTheme, menuTheme](ThemeType type) -> RefPtr<Theme> {
            if (type == SelectTheme::TypeId()) {
                return selectTheme;
            } else if (type == MenuTheme::TypeId()) {
                return menuTheme;
            }
            return nullptr;
        };
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(getThemeMockFunc);

        MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
        MockContainer::SetUp(MockPipelineContext::GetCurrent());
        MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
        AddResource(FAMILY_RES_ID, "aa.bb.cc");
    }

    static void TearDownTestCase()
    {
        MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }
};

/**
 * @tc.name: setFontSizeTest
 * @tc.desc: Check the functionality of MenuModifier.setFontSize
 * @tc.type: FUNC
 */
HWTEST_F(MenuModifierTest, setFontSizeTest, TestSize.Level1)
{
    auto checkVal = GetAttrValue<std::string>(node_, "fontSize");
    EXPECT_EQ(checkVal, "0.00px");

    Ark_Length size = Converter::ArkValue<Ark_Length>(123);
    modifier_->setFontSize(node_, &size);
    checkVal = GetStringAttribute(node_, "fontSize");
    EXPECT_EQ(checkVal, "123.00px");

    size = Converter::ArkValue<Ark_Length>(-123);
    modifier_->setFontSize(node_, &size);
    checkVal = GetAttrValue<std::string>(node_, "fontSize");
    EXPECT_EQ(checkVal, "0.00px");
}

/**
 * @tc.name: setSubMenuExpandingModeTest
 * @tc.desc: Check the functionality of MenuModifier.setSubMenuExpandingMode
 * @tc.type: FUNC
 */
HWTEST_F(MenuModifierTest, setSubMenuExpandingModeTest, TestSize.Level1)
{
    auto checkValue = GetAttrValue<std::string>(node_, "subMenuExpandingMode");
    EXPECT_EQ(checkValue, "SubMenuExpandingMode.SIDE");

    modifier_->setSubMenuExpandingMode(node_, ARK_SUB_MENU_EXPANDING_MODE_EMBEDDED_EXPAND);
    checkValue = GetAttrValue<std::string>(node_, "subMenuExpandingMode");
    EXPECT_EQ(checkValue, "SubMenuExpandingMode.EMBEDDED");

    modifier_->setSubMenuExpandingMode(node_, ARK_SUB_MENU_EXPANDING_MODE_STACK_EXPAND);
    checkValue = GetAttrValue<std::string>(node_, "subMenuExpandingMode");
    EXPECT_EQ(checkValue, "SubMenuExpandingMode.STACK");

    modifier_->setSubMenuExpandingMode(node_, static_cast<Ark_SubMenuExpandingMode>(-1));
    checkValue = GetAttrValue<std::string>(node_, "subMenuExpandingMode");
    EXPECT_EQ(checkValue, "SubMenuExpandingMode.SIDE");
}

/**
 * @tc.name: setFontColorTest
 * @tc.desc: Check the functionality of MenuModifier.setFontColor
 * @tc.type: FUNC
 */
HWTEST_F(MenuModifierTest, setFontColorTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFontColor, nullptr);
    auto checkVal = GetAttrValue<std::string>(node_, "fontColor");
    EXPECT_EQ(checkVal, COLOR_BLACK);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        modifier_->setFontColor(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, "fontColor");
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setFontColorTestRes
 * @tc.desc: Check the functionality of MenuModifier.setFontColor
 * @tc.type: FUNC
 */
HWTEST_F(MenuModifierTest, setFontColorTestRes, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFontColor, nullptr);
    auto checkVal = GetAttrValue<std::string>(node_, "fontColor");
    EXPECT_EQ(checkVal, COLOR_BLACK);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN_RES) {
        modifier_->setFontColor(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, "fontColor");
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setRadiusTest
 * @tc.desc: Check the functionality of MenuModifier.setRadius
 * @tc.type: FUNC
 */
HWTEST_F(MenuModifierTest, setRadiusTest, TestSize.Level1)
{
    auto fullJson = GetJsonValue(node_);
    auto radiusObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "radius");
    auto topLeft = GetAttrValue<std::string>(radiusObject, "topLeft");
    EXPECT_EQ(topLeft, "0.00vp");
    auto topRight = GetAttrValue<std::string>(radiusObject, "topRight");
    EXPECT_EQ(topRight, "0.00vp");
    auto bottomLeft = GetAttrValue<std::string>(radiusObject, "bottomLeft");
    EXPECT_EQ(bottomLeft, "0.00vp");
    auto bottomRight = GetAttrValue<std::string>(radiusObject, "bottomRight");
    EXPECT_EQ(bottomRight, "0.00vp");

    auto radius = Converter::ArkUnion<Ark_Union_Dimension_BorderRadiuses, Ark_Length>(5);
    modifier_->setRadius(node_, &radius);
    fullJson = GetJsonValue(node_);
    radiusObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "radius");
    topLeft = GetAttrValue<std::string>(radiusObject, "topLeft");
    EXPECT_EQ(topLeft, "5.00px");
    topRight = GetAttrValue<std::string>(radiusObject, "topRight");
    EXPECT_EQ(topRight, "5.00px");
    bottomLeft = GetAttrValue<std::string>(radiusObject, "bottomLeft");
    EXPECT_EQ(bottomLeft, "5.00px");
    bottomRight = GetAttrValue<std::string>(radiusObject, "bottomRight");
    EXPECT_EQ(bottomRight, "5.00px");

    radius = Converter::ArkUnion<Ark_Union_Dimension_BorderRadiuses, Ark_Length>(-5);
    modifier_->setRadius(node_, &radius);
    fullJson = GetJsonValue(node_);
    radiusObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "radius");
    topLeft = GetAttrValue<std::string>(radiusObject, "topLeft");
    EXPECT_EQ(topLeft, "0.00vp");
    topRight = GetAttrValue<std::string>(radiusObject, "topRight");
    EXPECT_EQ(topRight, "0.00vp");
    bottomLeft = GetAttrValue<std::string>(radiusObject, "bottomLeft");
    EXPECT_EQ(bottomLeft, "0.00vp");
    bottomRight = GetAttrValue<std::string>(radiusObject, "bottomRight");
    EXPECT_EQ(bottomRight, "0.00vp");
}

/**
 * @tc.name: setRadiusRadiusesValidTest
 * @tc.desc: Check the functionality of MenuModifier.setRadius
 * @tc.type: FUNC
 */
HWTEST_F(MenuModifierTest, setRadiusRadiusesValidTest, TestSize.Level1)
{
    auto fullJson = GetJsonValue(node_);
    auto radiusObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "radius");
    auto topLeft = GetAttrValue<std::string>(radiusObject, "topLeft");
    EXPECT_EQ(topLeft, "0.00vp");
    auto topRight = GetAttrValue<std::string>(radiusObject, "topRight");
    EXPECT_EQ(topRight, "0.00vp");
    auto bottomLeft = GetAttrValue<std::string>(radiusObject, "bottomLeft");
    EXPECT_EQ(bottomLeft, "0.00vp");
    auto bottomRight = GetAttrValue<std::string>(radiusObject, "bottomRight");
    EXPECT_EQ(bottomRight, "0.00vp");

    Ark_BorderRadiuses radiuses = {
        .topLeft = Converter::ArkValue<Opt_Length>(5), .topRight = Converter::ArkValue<Opt_Length>(7),
        .bottomLeft = Converter::ArkValue<Opt_Length>(8), .bottomRight = Converter::ArkValue<Opt_Length>(0)
    };
    auto radius = Converter::ArkUnion<Ark_Union_Dimension_BorderRadiuses, Ark_BorderRadiuses>(radiuses);
    modifier_->setRadius(node_, &radius);
    fullJson = GetJsonValue(node_);
    radiusObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "radius");
    topLeft = GetAttrValue<std::string>(radiusObject, "topLeft");
    EXPECT_EQ(topLeft, "5.00px");
    topRight = GetAttrValue<std::string>(radiusObject, "topRight");
    EXPECT_EQ(topRight, "7.00px");
    bottomLeft = GetAttrValue<std::string>(radiusObject, "bottomLeft");
    EXPECT_EQ(bottomLeft, "8.00px");
    bottomRight = GetAttrValue<std::string>(radiusObject, "bottomRight");
    EXPECT_EQ(bottomRight, "0.00px");
}

/**
 * @tc.name: setRadiusRadiusesNegativeOrEmptyTest
 * @tc.desc: Check the functionality of MenuModifier.setRadius
 * @tc.type: FUNC
 */
HWTEST_F(MenuModifierTest, setRadiusRadiusesNegativeOrEmptyTest, TestSize.Level1)
{
    auto fullJson = GetJsonValue(node_);
    auto radiusObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "radius");
    auto topLeft = GetAttrValue<std::string>(radiusObject, "topLeft");
    EXPECT_EQ(topLeft, "0.00vp");
    auto topRight = GetAttrValue<std::string>(radiusObject, "topRight");
    EXPECT_EQ(topRight, "0.00vp");
    auto bottomLeft = GetAttrValue<std::string>(radiusObject, "bottomLeft");
    EXPECT_EQ(bottomLeft, "0.00vp");
    auto bottomRight = GetAttrValue<std::string>(radiusObject, "bottomRight");
    EXPECT_EQ(bottomRight, "0.00vp");

    Ark_BorderRadiuses radiuses = {
        .topLeft = Converter::ArkValue<Opt_Length>(5), .topRight = Converter::ArkValue<Opt_Length>(7),
        .bottomLeft = Converter::ArkValue<Opt_Length>(-8), .bottomRight = Converter::ArkValue<Opt_Length>(-9)
    };
    auto radius = Converter::ArkUnion<Ark_Union_Dimension_BorderRadiuses, Ark_BorderRadiuses>(radiuses);
    modifier_->setRadius(node_, &radius);
    fullJson = GetJsonValue(node_);
    radiusObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "radius");
    topLeft = GetAttrValue<std::string>(radiusObject, "topLeft");
    EXPECT_EQ(topLeft, "5.00px");
    topRight = GetAttrValue<std::string>(radiusObject, "topRight");
    EXPECT_EQ(topRight, "7.00px");
    bottomLeft = GetAttrValue<std::string>(radiusObject, "bottomLeft");
    EXPECT_EQ(bottomLeft, "0.00vp");
    bottomRight = GetAttrValue<std::string>(radiusObject, "bottomRight");
    EXPECT_EQ(bottomRight, "0.00vp");

    radiuses = {
        .topLeft = Converter::ArkValue<Opt_Length>(5), .topRight = Converter::ArkValue<Opt_Length>(7),
        .bottomLeft = Converter::ArkValue<Opt_Length>(Ark_Empty()),
        .bottomRight = Converter::ArkValue<Opt_Length>(Ark_Empty())
    };
    radius = Converter::ArkUnion<Ark_Union_Dimension_BorderRadiuses, Ark_BorderRadiuses>(radiuses);
    modifier_->setRadius(node_, &radius);
    fullJson = GetJsonValue(node_);
    radiusObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "radius");
    topLeft = GetAttrValue<std::string>(radiusObject, "topLeft");
    EXPECT_EQ(topLeft, "5.00px");
    topRight = GetAttrValue<std::string>(radiusObject, "topRight");
    EXPECT_EQ(topRight, "7.00px");
    bottomLeft = GetAttrValue<std::string>(radiusObject, "bottomLeft");
    EXPECT_EQ(bottomLeft, "0.00vp");
    bottomRight = GetAttrValue<std::string>(radiusObject, "bottomRight");
    EXPECT_EQ(bottomRight, "0.00vp");
}

/**
 * @tc.name: setMenuItemDividerColorTest
 * @tc.desc: Check the functionality of MenuModifier.setMenuItemDivider
 * @tc.type: FUNC
 */
HWTEST_F(MenuModifierTest, setMenuItemDividerColorTest, TestSize.Level1)
{
    // default values
    auto fullJson = GetJsonValue(node_);
    auto dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "itemDivider");
    EXPECT_EQ(dividerObject, nullptr);

    // set valid values, color as Ark_Color aka int
    Ark_DividerStyleOptions dividerOptions = {.color = Converter::ArkValue<Opt_ResourceColor>
        (Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_WHITE))
    };
    auto divider = Converter::ArkValue<Opt_DividerStyleOptions>(dividerOptions);
    modifier_->setMenuItemDivider(node_, &divider);
    fullJson = GetJsonValue(node_);
    dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "itemDivider");
    auto colorCheckValue = GetAttrValue<std::string>(dividerObject, "color");
    EXPECT_EQ(colorCheckValue, "#FFFFFFFF");

    // set color as Ark_Number
    dividerOptions = {.color = Converter::ArkValue<Opt_ResourceColor>
        (Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0x123456))
    };
    divider = Converter::ArkValue<Opt_DividerStyleOptions>(dividerOptions);
    modifier_->setMenuItemDivider(node_, &divider);
    fullJson = GetJsonValue(node_);
    dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "itemDivider");
    colorCheckValue = GetAttrValue<std::string>(dividerObject, "color");
    EXPECT_EQ(colorCheckValue, "#FF123456");

    // set color as string
    dividerOptions = {.color = Converter::ArkValue<Opt_ResourceColor>
        (Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#11223344"))
    };
    divider = Converter::ArkValue<Opt_DividerStyleOptions>(dividerOptions);
    modifier_->setMenuItemDivider(node_, &divider);
    fullJson = GetJsonValue(node_);
    dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "itemDivider");
    colorCheckValue = GetAttrValue<std::string>(dividerObject, "color");
    EXPECT_EQ(colorCheckValue, "#11223344");

    // set color as resource
    for (const auto& [value, expectVal] : COLOR_TEST_PLAN_RES) {
        dividerOptions = {.color = Converter::ArkValue<Opt_ResourceColor>(value)};
        divider = Converter::ArkValue<Opt_DividerStyleOptions>(dividerOptions);
        modifier_->setMenuItemDivider(node_, &divider);
        fullJson = GetJsonValue(node_);
        dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "itemDivider");
        colorCheckValue = GetAttrValue<std::string>(dividerObject, "color");
        EXPECT_EQ(colorCheckValue, expectVal);
    }
}

/**
 * @tc.name: setMenuItemDividerStrokeTest
 * @tc.desc: Check the functionality of MenuModifier.setMenuItemDivider
 * @tc.type: FUNC
 */
HWTEST_F(MenuModifierTest, setMenuItemDividerStrokeTest, TestSize.Level1)
{
    // default values
    auto fullJson = GetJsonValue(node_);
    auto dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "itemDivider");
    EXPECT_EQ(dividerObject, nullptr);

    // set valid strokeWidth value
    Ark_LengthMetrics arkStroke = {.unit = Converter::ArkValue<Ark_LengthUnit>(ARK_LENGTH_UNIT_PX),
        .value = get<0>(DIVIDER_VALUES[0])
    };
    Ark_DividerStyleOptions dividerOptions = {.strokeWidth = Converter::ArkValue<Opt_LengthMetrics>(arkStroke)};
    auto divider = Converter::ArkValue<Opt_DividerStyleOptions>(dividerOptions);
    modifier_->setMenuItemDivider(node_, &divider);
    fullJson = GetJsonValue(node_);
    dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "itemDivider");
    auto strokeWidthCheckValue = GetAttrValue<std::string>(dividerObject, "strokeWidth");
    EXPECT_EQ(strokeWidthCheckValue, get<1>(DIVIDER_VALUES[0]));

    // set invalid strokeWidth value
    arkStroke = {.unit = Converter::ArkValue<Ark_LengthUnit>(ARK_LENGTH_UNIT_PX),
        .value = get<0>(DIVIDER_VALUES[1])
    };
    dividerOptions = {.strokeWidth = Converter::ArkValue<Opt_LengthMetrics>(arkStroke)};
    divider = Converter::ArkValue<Opt_DividerStyleOptions>(dividerOptions);
    modifier_->setMenuItemDivider(node_, &divider);
    fullJson = GetJsonValue(node_);
    dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "itemDivider");
    strokeWidthCheckValue = GetAttrValue<std::string>(dividerObject, "strokeWidth");
    EXPECT_EQ(strokeWidthCheckValue, get<1>(DIVIDER_VALUES[1]));
}

/**
 * @tc.name: setMenuItemDividerStartMarginTest
 * @tc.desc: Check the functionality of MenuModifier.setMenuItemDivider
 * @tc.type: FUNC
 */
HWTEST_F(MenuModifierTest, setMenuItemDividerStartMarginTest, TestSize.Level1)
{
    // default values
    auto fullJson = GetJsonValue(node_);
    auto dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "itemDivider");
    EXPECT_EQ(dividerObject, nullptr);

    // set valid startMargin value
    Ark_LengthMetrics arkStartMargin = {.unit = Converter::ArkValue<Ark_LengthUnit>(ARK_LENGTH_UNIT_PX),
        .value = get<0>(DIVIDER_VALUES[0])
    };
    Ark_DividerStyleOptions dividerOptions = {.startMargin = Converter::ArkValue<Opt_LengthMetrics>(arkStartMargin)};
    auto divider = Converter::ArkValue<Opt_DividerStyleOptions>(dividerOptions);
    modifier_->setMenuItemDivider(node_, &divider);
    fullJson = GetJsonValue(node_);
    dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "itemDivider");
    auto startMarginCheckValue = GetAttrValue<std::string>(dividerObject, "startMargin");
    EXPECT_EQ(startMarginCheckValue, get<1>(DIVIDER_VALUES[0]));

    // set invalid startMargin value
    arkStartMargin = {.unit = Converter::ArkValue<Ark_LengthUnit>(ARK_LENGTH_UNIT_PX),
        .value = get<0>(DIVIDER_VALUES[1])
    };
    dividerOptions = {.startMargin = Converter::ArkValue<Opt_LengthMetrics>(arkStartMargin)};
    divider = Converter::ArkValue<Opt_DividerStyleOptions>(dividerOptions);
    modifier_->setMenuItemDivider(node_, &divider);
    fullJson = GetJsonValue(node_);
    dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "itemDivider");
    startMarginCheckValue = GetAttrValue<std::string>(dividerObject, "startMargin");
    EXPECT_EQ(startMarginCheckValue, get<1>(DIVIDER_VALUES[1]));
}

/**
 * @tc.name: setMenuItemDividerEndMarginTest
 * @tc.desc: Check the functionality of MenuModifier.setMenuItemDivider
 * @tc.type: FUNC
 */
HWTEST_F(MenuModifierTest, setMenuItemDividerEndMarginTest, TestSize.Level1)
{
    // default values
    auto fullJson = GetJsonValue(node_);
    auto dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "itemDivider");
    EXPECT_EQ(dividerObject, nullptr);

    // set valid endMargin value
    Ark_LengthMetrics arkEndMargin = {.unit = Converter::ArkValue<Ark_LengthUnit>(ARK_LENGTH_UNIT_PX),
        .value = get<0>(DIVIDER_VALUES[0])
    };
    Ark_DividerStyleOptions dividerOptions = {.endMargin = Converter::ArkValue<Opt_LengthMetrics>(arkEndMargin)};
    auto divider = Converter::ArkValue<Opt_DividerStyleOptions>(dividerOptions);
    modifier_->setMenuItemDivider(node_, &divider);
    fullJson = GetJsonValue(node_);
    dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "itemDivider");
    auto endMarginCheckValue = GetAttrValue<std::string>(dividerObject, "endMargin");
    EXPECT_EQ(endMarginCheckValue, get<1>(DIVIDER_VALUES[0]));

    // set invalid endMargin value
    arkEndMargin = {.unit = Converter::ArkValue<Ark_LengthUnit>(ARK_LENGTH_UNIT_PX),
        .value = get<0>(DIVIDER_VALUES[1])
    };
    dividerOptions = {.endMargin = Converter::ArkValue<Opt_LengthMetrics>(arkEndMargin)};
    divider = Converter::ArkValue<Opt_DividerStyleOptions>(dividerOptions);
    modifier_->setMenuItemDivider(node_, &divider);
    fullJson = GetJsonValue(node_);
    dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "itemDivider");
    endMarginCheckValue = GetAttrValue<std::string>(dividerObject, "endMargin");
    EXPECT_EQ(endMarginCheckValue, get<1>(DIVIDER_VALUES[1]));
}

/**
 * @tc.name: setMenuItemDividerUndefinedValuesTest
 * @tc.desc: Check the functionality of ListModifier.setMenuItemDivider
 * @tc.type: FUNC
 */
HWTEST_F(MenuModifierTest, setMenuItemDividerUndefinedTest, TestSize.Level1)
{
    Opt_DividerStyleOptions divider =
        Converter::ArkValue<Opt_DividerStyleOptions>();
    modifier_->setMenuItemDivider(node_, &divider);
    auto fullJson = GetJsonValue(node_);
    auto dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "itemDivider");
    auto strokeWidthCheckValue = GetAttrValue<std::string>(dividerObject, "strokeWidth");
    EXPECT_EQ(strokeWidthCheckValue, "");
    auto startMarginCheckValue = GetAttrValue<std::string>(dividerObject, "startMargin");
    EXPECT_EQ(startMarginCheckValue, "");
    auto endMarginCheckValue = GetAttrValue<std::string>(dividerObject, "endMargin");
    EXPECT_EQ(endMarginCheckValue, "");
    auto colorCheckValue = GetAttrValue<std::string>(dividerObject, "color");
    EXPECT_EQ(colorCheckValue, "");

    // set undefined values
    Ark_DividerStyleOptions dividerOptions = {
        .color = Converter::ArkValue<Opt_ResourceColor>(Ark_Empty()),
        .strokeWidth = Converter::ArkValue<Opt_LengthMetrics>(Ark_Empty()),
        .startMargin = Converter::ArkValue<Opt_LengthMetrics>(Ark_Empty()),
        .endMargin = Converter::ArkValue<Opt_LengthMetrics>(Ark_Empty())
    };
    divider = Converter::ArkValue<Opt_DividerStyleOptions>(dividerOptions);
    modifier_->setMenuItemDivider(node_, &divider);
    fullJson = GetJsonValue(node_);
    dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "itemDivider");
    strokeWidthCheckValue = GetAttrValue<std::string>(dividerObject, "strokeWidth");
    EXPECT_EQ(strokeWidthCheckValue, DIVIDER_DEFAULT);
    startMarginCheckValue = GetAttrValue<std::string>(dividerObject, "startMargin");
    EXPECT_EQ(startMarginCheckValue, DIVIDER_DEFAULT);
    endMarginCheckValue = GetAttrValue<std::string>(dividerObject, "endMargin");
    EXPECT_EQ(endMarginCheckValue, DIVIDER_DEFAULT);
    colorCheckValue = GetAttrValue<std::string>(dividerObject, "color");
    EXPECT_EQ(colorCheckValue, COLOR_TRANSPARENT);
}

/**
 * @tc.name: setMenuItemGroupDividerColorTest
 * @tc.desc: Check the functionality of MenuModifier.setMenuItemGroupDivider
 * @tc.type: FUNC
 */
HWTEST_F(MenuModifierTest, setMenuItemGroupDividerColorTest, TestSize.Level1)
{
    // default values
    auto fullJson = GetJsonValue(node_);
    auto dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "itemGroupDivider");
    EXPECT_EQ(dividerObject, nullptr);

    // set valid values, color as Ark_Color aka int
    Ark_DividerStyleOptions dividerOptions = {.color = Converter::ArkValue<Opt_ResourceColor>
        (Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_WHITE))
    };
    auto divider = Converter::ArkValue<Opt_DividerStyleOptions>(dividerOptions);
    modifier_->setMenuItemGroupDivider(node_, &divider);
    fullJson = GetJsonValue(node_);
    dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "itemGroupDivider");
    auto colorCheckValue = GetAttrValue<std::string>(dividerObject, "color");
    EXPECT_EQ(colorCheckValue, "#FFFFFFFF");

    // set color as Ark_Number
    dividerOptions = {.color = Converter::ArkValue<Opt_ResourceColor>
        (Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0x123456))
    };
    divider = Converter::ArkValue<Opt_DividerStyleOptions>(dividerOptions);
    modifier_->setMenuItemGroupDivider(node_, &divider);
    fullJson = GetJsonValue(node_);
    dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "itemGroupDivider");
    colorCheckValue = GetAttrValue<std::string>(dividerObject, "color");
    EXPECT_EQ(colorCheckValue, "#FF123456");

    // set color as string
    dividerOptions = {.color = Converter::ArkValue<Opt_ResourceColor>
        (Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#11223344"))
    };
    divider = Converter::ArkValue<Opt_DividerStyleOptions>(dividerOptions);
    modifier_->setMenuItemGroupDivider(node_, &divider);
    fullJson = GetJsonValue(node_);
    dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "itemGroupDivider");
    colorCheckValue = GetAttrValue<std::string>(dividerObject, "color");
    EXPECT_EQ(colorCheckValue, "#11223344");

    // set color as resource
    for (const auto& [value, expectVal] : COLOR_TEST_PLAN_RES) {
        dividerOptions = {.color = Converter::ArkValue<Opt_ResourceColor>(value)};
        divider = Converter::ArkValue<Opt_DividerStyleOptions>(dividerOptions);
        modifier_->setMenuItemGroupDivider(node_, &divider);
        fullJson = GetJsonValue(node_);
        dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "itemGroupDivider");
        colorCheckValue = GetAttrValue<std::string>(dividerObject, "color");
        EXPECT_EQ(colorCheckValue, expectVal);
    }
}

/**
 * @tc.name: setMenuItemGroupDividerStrokeTest
 * @tc.desc: Check the functionality of MenuModifier.setMenuItemGroupDivider
 * @tc.type: FUNC
 */
HWTEST_F(MenuModifierTest, setMenuItemGroupDividerStrokeTest, TestSize.Level1)
{
    // default values
    auto fullJson = GetJsonValue(node_);
    auto dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "itemGroupDivider");
    EXPECT_EQ(dividerObject, nullptr);

    // set valid strokeWidth value
    Ark_LengthMetrics arkStroke = {.unit = Converter::ArkValue<Ark_LengthUnit>(ARK_LENGTH_UNIT_PX),
        .value = get<0>(DIVIDER_VALUES[0])
    };
    Ark_DividerStyleOptions dividerOptions = {.strokeWidth = Converter::ArkValue<Opt_LengthMetrics>(arkStroke)};
    auto divider = Converter::ArkValue<Opt_DividerStyleOptions>(dividerOptions);
    modifier_->setMenuItemGroupDivider(node_, &divider);
    fullJson = GetJsonValue(node_);
    dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "itemGroupDivider");
    auto strokeWidthCheckValue = GetAttrValue<std::string>(dividerObject, "strokeWidth");
    EXPECT_EQ(strokeWidthCheckValue, get<1>(DIVIDER_VALUES[0]));

    // set invalid strokeWidth value
    arkStroke = {.unit = Converter::ArkValue<Ark_LengthUnit>(ARK_LENGTH_UNIT_PX),
        .value = get<0>(DIVIDER_VALUES[1])
    };
    dividerOptions = {.strokeWidth = Converter::ArkValue<Opt_LengthMetrics>(arkStroke)};
    divider = Converter::ArkValue<Opt_DividerStyleOptions>(dividerOptions);
    modifier_->setMenuItemGroupDivider(node_, &divider);
    fullJson = GetJsonValue(node_);
    dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "itemGroupDivider");
    strokeWidthCheckValue = GetAttrValue<std::string>(dividerObject, "strokeWidth");
    EXPECT_EQ(strokeWidthCheckValue, get<1>(DIVIDER_VALUES[1]));
}

/**
 * @tc.name: setMenuItemGroupDividerStartMarginTest
 * @tc.desc: Check the functionality of MenuModifier.setMenuItemGroupDivider
 * @tc.type: FUNC
 */
HWTEST_F(MenuModifierTest, setMenuItemGroupDividerStartMarginTest, TestSize.Level1)
{
    // default values
    auto fullJson = GetJsonValue(node_);
    auto dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "itemGroupDivider");
    EXPECT_EQ(dividerObject, nullptr);

    // set valid startMargin value
    Ark_LengthMetrics arkStartMargin = {.unit = Converter::ArkValue<Ark_LengthUnit>(ARK_LENGTH_UNIT_PX),
        .value = get<0>(DIVIDER_VALUES[0])
    };
    Ark_DividerStyleOptions dividerOptions = {.startMargin = Converter::ArkValue<Opt_LengthMetrics>(arkStartMargin)};
    auto divider = Converter::ArkValue<Opt_DividerStyleOptions>(dividerOptions);
    modifier_->setMenuItemGroupDivider(node_, &divider);
    fullJson = GetJsonValue(node_);
    dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "itemGroupDivider");
    auto startMarginCheckValue = GetAttrValue<std::string>(dividerObject, "startMargin");
    EXPECT_EQ(startMarginCheckValue, get<1>(DIVIDER_VALUES[0]));

    // set invalid startMargin value
    arkStartMargin = {.unit = Converter::ArkValue<Ark_LengthUnit>(ARK_LENGTH_UNIT_PX),
        .value = get<0>(DIVIDER_VALUES[1])
    };
    dividerOptions = {.startMargin = Converter::ArkValue<Opt_LengthMetrics>(arkStartMargin)};
    divider = Converter::ArkValue<Opt_DividerStyleOptions>(dividerOptions);
    modifier_->setMenuItemGroupDivider(node_, &divider);
    fullJson = GetJsonValue(node_);
    dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "itemGroupDivider");
    startMarginCheckValue = GetAttrValue<std::string>(dividerObject, "startMargin");
    EXPECT_EQ(startMarginCheckValue, get<1>(DIVIDER_VALUES[1]));
}

/**
 * @tc.name: setMenuItemGroupDividerEndMarginTest
 * @tc.desc: Check the functionality of MenuModifier.setMenuItemGroupDivider
 * @tc.type: FUNC
 */
HWTEST_F(MenuModifierTest, setMenuItemGroupDividerEndMarginTest, TestSize.Level1)
{
    // default values
    auto fullJson = GetJsonValue(node_);
    auto dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "itemGroupDivider");
    EXPECT_EQ(dividerObject, nullptr);

    // set valid endMargin value
    Ark_LengthMetrics arkEndMargin = {.unit = Converter::ArkValue<Ark_LengthUnit>(ARK_LENGTH_UNIT_PX),
        .value = get<0>(DIVIDER_VALUES[0])
    };
    Ark_DividerStyleOptions dividerOptions = {.endMargin = Converter::ArkValue<Opt_LengthMetrics>(arkEndMargin)};
    auto divider = Converter::ArkValue<Opt_DividerStyleOptions>(dividerOptions);
    modifier_->setMenuItemGroupDivider(node_, &divider);
    fullJson = GetJsonValue(node_);
    dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "itemGroupDivider");
    auto endMarginCheckValue = GetAttrValue<std::string>(dividerObject, "endMargin");
    EXPECT_EQ(endMarginCheckValue, get<1>(DIVIDER_VALUES[0]));

    // set invalid endMargin value
    arkEndMargin = {.unit = Converter::ArkValue<Ark_LengthUnit>(ARK_LENGTH_UNIT_PX),
        .value = get<0>(DIVIDER_VALUES[1])
    };
    dividerOptions = {.endMargin = Converter::ArkValue<Opt_LengthMetrics>(arkEndMargin)};
    divider = Converter::ArkValue<Opt_DividerStyleOptions>(dividerOptions);
    modifier_->setMenuItemGroupDivider(node_, &divider);
    fullJson = GetJsonValue(node_);
    dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "itemGroupDivider");
    endMarginCheckValue = GetAttrValue<std::string>(dividerObject, "endMargin");
    EXPECT_EQ(endMarginCheckValue, get<1>(DIVIDER_VALUES[1]));
}

/**
 * @tc.name: setMenuItemGroupDividerUndefinedValuesTest
 * @tc.desc: Check the functionality of ListModifier.setMenuItemGroupDivider
 * @tc.type: FUNC
 */
HWTEST_F(MenuModifierTest, setMenuItemGroupDividerUndefinedTest, TestSize.Level1)
{
    Opt_DividerStyleOptions divider =
        Converter::ArkValue<Opt_DividerStyleOptions>();
    modifier_->setMenuItemGroupDivider(node_, &divider);
    auto fullJson = GetJsonValue(node_);
    auto dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "itemGroupDivider");
    auto strokeWidthCheckValue = GetAttrValue<std::string>(dividerObject, "strokeWidth");
    EXPECT_EQ(strokeWidthCheckValue, "");
    auto startMarginCheckValue = GetAttrValue<std::string>(dividerObject, "startMargin");
    EXPECT_EQ(startMarginCheckValue, "");
    auto endMarginCheckValue = GetAttrValue<std::string>(dividerObject, "endMargin");
    EXPECT_EQ(endMarginCheckValue, "");
    auto colorCheckValue = GetAttrValue<std::string>(dividerObject, "color");
    EXPECT_EQ(colorCheckValue, "");

    // set undefined values
    Ark_DividerStyleOptions dividerOptions = {
        .color = Converter::ArkValue<Opt_ResourceColor>(Ark_Empty()),
        .strokeWidth = Converter::ArkValue<Opt_LengthMetrics>(Ark_Empty()),
        .startMargin = Converter::ArkValue<Opt_LengthMetrics>(Ark_Empty()),
        .endMargin = Converter::ArkValue<Opt_LengthMetrics>(Ark_Empty())
    };
    divider = Converter::ArkValue<Opt_DividerStyleOptions>(dividerOptions);
    modifier_->setMenuItemGroupDivider(node_, &divider);
    fullJson = GetJsonValue(node_);
    dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "itemGroupDivider");
    strokeWidthCheckValue = GetAttrValue<std::string>(dividerObject, "strokeWidth");
    EXPECT_EQ(strokeWidthCheckValue, DIVIDER_DEFAULT);
    startMarginCheckValue = GetAttrValue<std::string>(dividerObject, "startMargin");
    EXPECT_EQ(startMarginCheckValue, DIVIDER_DEFAULT);
    endMarginCheckValue = GetAttrValue<std::string>(dividerObject, "endMargin");
    EXPECT_EQ(endMarginCheckValue, DIVIDER_DEFAULT);
    colorCheckValue = GetAttrValue<std::string>(dividerObject, "color");
    EXPECT_EQ(colorCheckValue, COLOR_TRANSPARENT);
}

/**
 * @tc.name: setFontTest1
 * @tc.desc: Check the functionality of MenuModifier.setFont
 * @tc.type: FUNC
 */
HWTEST_F(MenuModifierTest, setFontTest1, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFont, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = OPT_LENGTH_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto sizeStr = OPT_LENGTH_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    for (auto style : FONT_STYLE_TEST_PLAN) {
        font.style = style.first;
        modifier_->setFont(node_, &font);
        auto fullJson = GetJsonValue(node_);
        auto fontObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "font");
        auto checkSize = GetAttrValue<std::string>(fontObject, "size");
        auto checkWeight = GetAttrValue<std::string>(fontObject, "weight");
        auto checkStyle = GetAttrValue<std::string>(fontObject, "style");
        auto checkFamily = GetAttrValue<std::string>(fontObject, "family");
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, style.second);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setFontTest2
 * @tc.desc: Check the functionality of MenuModifier.setFont
 * @tc.type: FUNC
 */
HWTEST_F(MenuModifierTest, setFontTest2, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFont, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = OPT_LENGTH_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto sizeStr = OPT_LENGTH_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;

    for (auto weight : FONT_WEIGHT_TEST_PLAN) {
        font.weight = weight.first;
        modifier_->setFont(node_, &font);
        auto fullJson = GetJsonValue(node_);
        auto fontObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "font");
        auto checkSize = GetAttrValue<std::string>(fontObject, "size");
        auto checkWeight = GetAttrValue<std::string>(fontObject, "weight");
        auto checkStyle = GetAttrValue<std::string>(fontObject, "style");
        auto checkFamily = GetAttrValue<std::string>(fontObject, "family");
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }
}

/**
 * @tc.name: setFontTest3
 * @tc.desc: Check the functionality of MenuModifier.setFont
 * @tc.type: FUNC
 */
HWTEST_F(MenuModifierTest, setFontTest3, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFont, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = OPT_LENGTH_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto sizeStr = OPT_LENGTH_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;

    for (auto weight : FONT_WEIGHT_TEST_PLAN2) {
        font.weight = weight.first;
        modifier_->setFont(node_, &font);
        auto fullJson = GetJsonValue(node_);
        auto fontObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "font");
        auto checkSize = GetAttrValue<std::string>(fontObject, "size");
        auto checkWeight = GetAttrValue<std::string>(fontObject, "weight");
        auto checkStyle = GetAttrValue<std::string>(fontObject, "style");
        auto checkFamily = GetAttrValue<std::string>(fontObject, "family");
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }
}

/**
 * @tc.name: setFontTest4
 * @tc.desc: Check the functionality of MenuModifier.setFont
 * @tc.type: FUNC
 */
HWTEST_F(MenuModifierTest, setFontTest4, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFont, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = OPT_LENGTH_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto sizeStr = OPT_LENGTH_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    for (auto family : UNION_RESOURCE_STRING_PLAN) {
        font.family = family.first;
        modifier_->setFont(node_, &font);
        auto fullJson = GetJsonValue(node_);
        auto fontObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "font");
        auto checkSize = GetAttrValue<std::string>(fontObject, "size");
        auto checkWeight = GetAttrValue<std::string>(fontObject, "weight");
        auto checkStyle = GetAttrValue<std::string>(fontObject, "style");
        auto checkFamily = GetAttrValue<std::string>(fontObject, "family");
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily,  family.second);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setFontTest5
 * @tc.desc: Check the functionality of MenuModifier.setFont
 * @tc.type: FUNC
 */
HWTEST_F(MenuModifierTest, setFontTest5, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFont, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = OPT_LENGTH_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    for (auto size : OPT_LENGTH_TEST_PLAN) {
        font.size = size.first;
        modifier_->setFont(node_, &font);
        auto fullJson = GetJsonValue(node_);
        auto fontObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "font");
        auto checkSize = GetAttrValue<std::string>(fontObject, "size");
        auto checkWeight = GetAttrValue<std::string>(fontObject, "weight");
        auto checkStyle = GetAttrValue<std::string>(fontObject, "style");
        auto checkFamily = GetAttrValue<std::string>(fontObject, "family");
        EXPECT_EQ(checkSize, size.second);
        EXPECT_EQ(checkFamily,  familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}
} // namespace OHOS::Ace::NG
