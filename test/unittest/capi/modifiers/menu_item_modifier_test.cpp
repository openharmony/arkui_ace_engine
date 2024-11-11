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
#include "node_api.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_event_hub.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/pattern/select/select_model_ng.h"
#include "core/components_ng/pattern/select/select_pattern.h"
#include "test/mock/core/common/mock_theme_style.h"


namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
struct EventsTracker {
    static inline GENERATED_ArkUIMenuItemEventsReceiver menuItemEventReceiver {};

    static inline const GENERATED_ArkUIEventsAPI eventsApiImpl = {
        .getMenuItemEventsReceiver = [] () -> const GENERATED_ArkUIMenuItemEventsReceiver* {
            return &menuItemEventReceiver;
        }
    };
}; // EventsTracker
} // namespace

const std::string COLOR_GRAY = "#FFC0C0C0";
const std::string COLOR_RED = "#FFFF0000";
const std::string COLOR_BLACK = "#FF000000";
const std::string COLOR_TRANSPARENT = "#00000000";
const std::string COLOR_THEME_FONT = "#FF888888";
const std::string COLOR_THEME_FONT_ALPHA_06 = "#99888888";

const auto COLOR_COLOR_RES = CreateResource("color_name", NodeModifier::ResourceType::COLOR);
const auto COLOR_ID_RES = CreateResource(1234, NodeModifier::ResourceType::COLOR);
const auto COLOR_STRING_RES = CreateResource("color_name", NodeModifier::ResourceType::STRING);

typedef std::tuple<Ark_ResourceColor, std::string> ColorTestStep;
const std::vector<ColorTestStep> COLOR_TEST_PLAN = {
    { Converter::ArkUnion<Ark_ResourceColor, enum Ark_Color>(ARK_COLOR_BLUE), "#FF0000FF" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0x123456), "#FF123456" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0.5f), COLOR_TRANSPARENT },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#11223344"), "#11223344" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("65535"), "#FF00FFFF" },
};

const std::vector<ColorTestStep> COLOR_TEST_PLAN_INVALID = {
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("incorrect_color"), COLOR_THEME_FONT },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>(""), COLOR_THEME_FONT }
};


const std::vector<ColorTestStep> COLOR_TEST_PLAN1 = {
    { Converter::ArkUnion<Ark_ResourceColor, enum Ark_Color>(ARK_COLOR_BLUE), "#FF0000FF" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0x123456), "#FF123456" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0.5f), COLOR_TRANSPARENT },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#11223344"), "#11223344" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("65535"), "#FF00FFFF" },
};

const std::vector<ColorTestStep> COLOR_TEST_PLAN1_INVALID = {
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("incorrect_color"), COLOR_THEME_FONT_ALPHA_06 },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>(""), COLOR_THEME_FONT_ALPHA_06 }
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
const auto FAMILY_NAME_RES = CreateResource(FAMILY_RES_ID, NodeModifier::ResourceType::STRARRAY);
const Opt_Union_String_Resource OPT_UNION_RESOURCE_RESOURCE =
    Converter::ArkUnion<Opt_Union_String_Resource, Ark_Resource>(FAMILY_NAME_RES);

const std::string CHECK_RESOURCE_STR("aa.bb.cc");
const std::string ICON_OK_STR = "ic_public_ok";

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

class MenuItemModifierTest : public ModifierTestBase<GENERATED_ArkUIMenuItemModifier,
    &GENERATED_ArkUINodeModifiers::getMenuItemModifier, GENERATED_ARKUI_MENU_ITEM> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
        auto themeStyle = SetupThemeStyle(THEME_PATTERN_SELECT);
        themeStyle->SetAttr(PATTERN_TEXT_COLOR, { .value = Color::FromString(COLOR_THEME_FONT)});
        SetupTheme<SelectTheme>();
        AddResource(ICON_OK_STR, "path_to_select_icon");
        AddResource(FAMILY_RES_ID, "aa.bb.cc");
        fullAPI_->setArkUIEventsAPI(&EventsTracker::eventsApiImpl);
    }
};

/*
 * @tc.name: setSelectedTest
 * @tc.desc: Check the functionality of MenuItemModifier.setSelected
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setSelectedTest, TestSize.Level1)
{
    bool selected = GetAttrValue<bool>(node_, "selected");
    EXPECT_FALSE(selected);
    modifier_->setSelected(node_, Converter::ArkValue<Ark_Boolean>(true));
    selected = GetAttrValue<bool>(node_, "selected");
    EXPECT_TRUE(selected);
}

/*
 * @tc.name: setSelectIconBoolTest
 * @tc.desc: Check the functionality of MenuItemModifier.setSelectIcon
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setSelectIconBoolTest, TestSize.Level1)
{
    auto selectIcon = GetAttrValue<std::string>(node_, "selectIcon");
    EXPECT_EQ(selectIcon, "false");

    auto icon = Converter::ArkUnion<Ark_Union_Boolean_ResourceStr_SymbolGlyphModifier, Ark_Boolean>(true);
    modifier_->setSelectIcon(node_, &icon);
    selectIcon = GetAttrValue<std::string>(node_, "selectIcon");
    EXPECT_EQ(selectIcon, "true");
}

/*
 * @tc.name: setSelectIconStringTest
 * @tc.desc: Check the functionality of MenuItemModifier.setSelectIcon
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setSelectIconStringTest, TestSize.Level1)
{
    auto selectIcon = GetAttrValue<std::string>(node_, "selectIcon");
    EXPECT_EQ(selectIcon, "false");

    auto str = Converter::ArkValue<Ark_String>("path_to_select_icon");
    Ark_ResourceStr resStr = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(str);

    auto icon = Converter::ArkUnion<Ark_Union_Boolean_ResourceStr_SymbolGlyphModifier, Ark_ResourceStr>(resStr);
    modifier_->setSelectIcon(node_, &icon);
    selectIcon = GetAttrValue<std::string>(node_, "selectIcon");
    EXPECT_EQ(selectIcon, "path_to_select_icon");
}

/*
 * @tc.name: setSelectIconResourceTest
 * @tc.desc: Check the functionality of MenuItemModifier.setSelectIcon
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setSelectIconResourceTest, TestSize.Level1)
{
    auto selectIcon = GetAttrValue<std::string>(node_, "selectIcon");
    EXPECT_EQ(selectIcon, "false");
    Ark_Resource iconRes = CreateResource(ICON_OK_STR.c_str(), NodeModifier::ResourceType::STRING);
    Ark_ResourceStr resStr = Converter::ArkUnion<Ark_ResourceStr, Ark_Resource>(iconRes);
    auto icon = Converter::ArkUnion<Ark_Union_Boolean_ResourceStr_SymbolGlyphModifier, Ark_ResourceStr>(resStr);
    modifier_->setSelectIcon(node_, &icon);
    selectIcon = GetAttrValue<std::string>(node_, "selectIcon");
    EXPECT_EQ(selectIcon, "path_to_select_icon");
}

/**
 * @tc.name: setContentFontColorTest
 * @tc.desc: Check the functionality of MenuItemModifier.setContentFontColor
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setContentFontColorTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setContentFontColor, nullptr);
    auto checkVal = GetAttrValue<std::string>(node_, "contentFontColor");
    EXPECT_EQ(checkVal, COLOR_THEME_FONT);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        modifier_->setContentFontColor(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, "contentFontColor");
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setContentFontColorTestRes
 * @tc.desc: Check the functionality of MenuItemModifier.setContentFontColor
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setContentFontColorTestRes, TestSize.Level1)
{
    ASSERT_NE(modifier_->setContentFontColor, nullptr);
    auto checkVal = GetAttrValue<std::string>(node_, "contentFontColor");
    EXPECT_EQ(checkVal, COLOR_THEME_FONT);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN_RES) {
        modifier_->setContentFontColor(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, "contentFontColor");
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setContentFontColorInvalidTest
 * @tc.desc: Check the functionality of MenuItemModifier.setContentFontColor
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setContentFontColorInvalidTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setContentFontColor, nullptr);
    auto checkVal = GetAttrValue<std::string>(node_, "contentFontColor");
    EXPECT_EQ(checkVal, COLOR_THEME_FONT);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN_INVALID) {
        modifier_->setContentFontColor(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, "contentFontColor");
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setLabelFontColorTest
 * @tc.desc: Check the functionality of MenuItemModifier.setLabelFontColor
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setLabelFontColorTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setLabelFontColor, nullptr);
    auto checkVal = GetAttrValue<std::string>(node_, "labelFontColor");
    EXPECT_EQ(checkVal, COLOR_THEME_FONT_ALPHA_06);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN1) {
        modifier_->setLabelFontColor(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, "labelFontColor");
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setLabelFontColorTestRes
 * @tc.desc: Check the functionality of MenuItemModifier.setLabelFontColor
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setLabelFontColorTestRes, TestSize.Level1)
{
    ASSERT_NE(modifier_->setLabelFontColor, nullptr);
    auto checkVal = GetAttrValue<std::string>(node_, "labelFontColor");
    EXPECT_EQ(checkVal, COLOR_THEME_FONT_ALPHA_06);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN_RES) {
        modifier_->setLabelFontColor(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, "labelFontColor");
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setLabelFontColorInvalidTest
 * @tc.desc: Check the functionality of MenuItemModifier.setLabelFontColor
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setLabelFontColorInvalidTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setLabelFontColor, nullptr);
    auto checkVal = GetAttrValue<std::string>(node_, "labelFontColor");
    EXPECT_EQ(checkVal, COLOR_THEME_FONT_ALPHA_06);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN1_INVALID) {
        modifier_->setLabelFontColor(node_, &value);
        checkVal = GetAttrValue<std::string>(node_, "labelFontColor");
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setContentFontTest1
 * @tc.desc: Check the functionality of MenuModifier.setContentFont
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setContentFontTest1, TestSize.Level1)
{
    ASSERT_NE(modifier_->setContentFont, nullptr);
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
        modifier_->setContentFont(node_, &font);
        auto fullJson = GetJsonValue(node_);
        auto fontObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "contentFont");
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
 * @tc.name: setContentFontTest2
 * @tc.desc: Check the functionality of MenuModifier.setContentFont
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setContentFontTest2, TestSize.Level1)
{
    ASSERT_NE(modifier_->setContentFont, nullptr);
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
        modifier_->setContentFont(node_, &font);
        auto fullJson = GetJsonValue(node_);
        auto fontObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "contentFont");
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
 * @tc.name: setContentFontTest3
 * @tc.desc: Check the functionality of MenuModifier.setContentFont
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setContentFontTest3, TestSize.Level1)
{
    ASSERT_NE(modifier_->setContentFont, nullptr);
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
        modifier_->setContentFont(node_, &font);
        auto fullJson = GetJsonValue(node_);
        auto fontObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "contentFont");
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
 * @tc.name: setContentFontTest4
 * @tc.desc: Check the functionality of MenuModifier.setContentFont
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setContentFontTest4, TestSize.Level1)
{
    ASSERT_NE(modifier_->setContentFont, nullptr);
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
        modifier_->setContentFont(node_, &font);
        auto fullJson = GetJsonValue(node_);
        auto fontObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "contentFont");
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
 * @tc.name: setContentFontTest5
 * @tc.desc: Check the functionality of MenuModifier.setContentFont
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setContentFontTest5, TestSize.Level1)
{
    ASSERT_NE(modifier_->setContentFont, nullptr);
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
        modifier_->setContentFont(node_, &font);
        auto fullJson = GetJsonValue(node_);
        auto fontObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "contentFont");
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

/**
 * @tc.name: setLabelFontTest1
 * @tc.desc: Check the functionality of MenuModifier.setLabelFont
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setLabelFontTest1, TestSize.Level1)
{
    ASSERT_NE(modifier_->setLabelFont, nullptr);
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
        modifier_->setLabelFont(node_, &font);
        auto fullJson = GetJsonValue(node_);
        auto fontObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "labelFont");
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
 * @tc.name: setLabelFontTest2
 * @tc.desc: Check the functionality of MenuModifier.setLabelFont
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setLabelFontTest2, TestSize.Level1)
{
    ASSERT_NE(modifier_->setLabelFont, nullptr);
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
        modifier_->setLabelFont(node_, &font);
        auto fullJson = GetJsonValue(node_);
        auto fontObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "labelFont");
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
 * @tc.name: setLabelFontTest3
 * @tc.desc: Check the functionality of MenuModifier.setLabelFont
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setLabelFontTest3, TestSize.Level1)
{
    ASSERT_NE(modifier_->setLabelFont, nullptr);
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
        modifier_->setLabelFont(node_, &font);
        auto fullJson = GetJsonValue(node_);
        auto fontObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "labelFont");
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
 * @tc.name: setLabelFontTest4
 * @tc.desc: Check the functionality of MenuModifier.setLabelFont
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setLabelFontTest4, TestSize.Level1)
{
    ASSERT_NE(modifier_->setLabelFont, nullptr);
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
        modifier_->setLabelFont(node_, &font);
        auto fullJson = GetJsonValue(node_);
        auto fontObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "labelFont");
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
 * @tc.name: setLabelFontTest5
 * @tc.desc: Check the functionality of MenuModifier.setLabelFont
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setLabelFontTest5, TestSize.Level1)
{
    ASSERT_NE(modifier_->setLabelFont, nullptr);
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
        modifier_->setLabelFont(node_, &font);
        auto fullJson = GetJsonValue(node_);
        auto fontObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "labelFont");
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

/*
 * @tc.name: setOnChangeTest
 * @tc.desc: Check the functionality of MenuItemModifier.setOnChange
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setOnChangeTest, TestSize.Level1)
{
    Callback_Boolean_Void func{};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<MenuItemEventHub>();

    struct CheckEvent {
        int32_t nodeId;
        bool selected;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    EventsTracker::menuItemEventReceiver.onChange = [](Ark_Int32 nodeId, const Ark_Boolean selected)
    {
        checkEvent = {
            .nodeId = nodeId,
            .selected = Converter::ArkValue<Ark_Boolean>(selected)
        };
    };

    auto onChange = eventHub->GetOnChange();
    EXPECT_EQ(onChange, nullptr);
    modifier_->setOnChange(node_, &func);
    onChange = eventHub->GetOnChange();
    EXPECT_NE(onChange, nullptr);
    // check true value
    EXPECT_FALSE(checkEvent.has_value());
    onChange(true);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_TRUE(checkEvent->selected);
    // check false value
    onChange(false);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_FALSE(checkEvent->selected);
}
} // namespace OHOS::Ace::NG
