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
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_event_hub.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/pattern/select/select_model_ng.h"
#include "core/components_ng/pattern/select/select_pattern.h"
#include "test/mock/core/common/mock_theme_style.h"
#include "core/components_ng/pattern/blank/blank_model_ng.h"
#include "core/interfaces/native/implementation/symbol_glyph_modifier_peer.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_layout_property.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

const std::string COLOR_GRAY = "#FFC0C0C0";
const std::string COLOR_RED = "#FFFF0000";
const std::string COLOR_BLACK = "#FF000000";
const std::string COLOR_TRANSPARENT = "#00000000";
const std::string COLOR_THEME_FONT = "#FF888888";
const std::string COLOR_THEME_FONT_ALPHA_06 = "#99888888";

const auto COLOR_COLOR_RES = CreateResource("color_name", ResourceType::COLOR);
const auto COLOR_ID_RES = CreateResource(1234, ResourceType::COLOR);
const auto COLOR_STRING_RES = CreateResource("color_name", ResourceType::STRING);

typedef std::tuple<Ark_ResourceColor, std::string> ColorTestStep;
const std::vector<ColorTestStep> COLOR_TEST_PLAN = {
    { Converter::ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLUE),
        "#FF0000FF" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0x123456), "#FF123456" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0.5f), COLOR_TRANSPARENT },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#11223344"), "#11223344" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("65535"), "#FF00FFFF" },
};

const std::vector<ColorTestStep> COLOR_TEST_PLAN_INVALID = {
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("incorrect_color"), COLOR_THEME_FONT },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>(""), COLOR_THEME_FONT }
};


const std::vector<ColorTestStep> COLOR_TEST_PLAN1 = {
    { Converter::ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLUE),
        "#FF0000FF" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0x123456), "#FF123456" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0.5f), COLOR_TRANSPARENT },
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

const Ark_Float32 AFLT32_POS(1.234f);
const Ark_Float32 AFLT32_NEG(-5.6789f);

const auto RES_CONTENT = Converter::ArkValue<Ark_String>("aa.bb.cc");
const auto FAMILY_RES_ID = 555;
const auto FAMILY_NAME_RES = CreateResource(FAMILY_RES_ID, ResourceType::STRARRAY);
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
    { Converter::ArkValue<Opt_Length>(AFLT32_NEG), "0.00px" },
    { Converter::ArkValue<Opt_Length>(AFLT32_POS), "1.23vp" } };

typedef std::pair<Opt_FontStyle, std::string> ArkFontStyleTestStep;
const std::vector<ArkFontStyleTestStep> FONT_STYLE_TEST_PLAN = {
    { Converter::ArkValue<Opt_FontStyle>(ARK_FONT_STYLE_NORMAL), "FontStyle.Normal" },
    { Converter::ArkValue<Opt_FontStyle>(ARK_FONT_STYLE_ITALIC), "FontStyle.Italic" },
    { Converter::ArkValue<Opt_FontStyle>(static_cast<Ark_FontStyle>(-1)), "FontStyle.Normal" },
};

typedef std::pair<Opt_Union_FontWeight_I32_String, std::string> ArkFontWeightTest;
const std::vector<ArkFontWeightTest> FONT_WEIGHT_TEST_PLAN = {
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(ARK_FONT_WEIGHT_LIGHTER),
        "FontWeight.Lighter" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(ARK_FONT_WEIGHT_NORMAL),
        "FontWeight.Normal" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(ARK_FONT_WEIGHT_REGULAR),
        "FontWeight.Regular" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(ARK_FONT_WEIGHT_MEDIUM),
        "FontWeight.Medium" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(ARK_FONT_WEIGHT_BOLD),
        "FontWeight.Bold" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(ARK_FONT_WEIGHT_BOLDER),
        "FontWeight.Bolder" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>(Converter::ArkValue<Ark_String>("lighter")),
        "FontWeight.Lighter" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>(Converter::ArkValue<Ark_String>("normal")),
        "FontWeight.Normal" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>(Converter::ArkValue<Ark_String>("regular")),
        "FontWeight.Regular" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>(Converter::ArkValue<Ark_String>("medium")),
        "FontWeight.Medium" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>(Converter::ArkValue<Ark_String>("bold")),
        "FontWeight.Bold" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>(Converter::ArkValue<Ark_String>("bolder")),
        "FontWeight.Bolder" }
};

const std::vector<ArkFontWeightTest> FONT_WEIGHT_TEST_PLAN2 = {
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Int32>(100), "100" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Int32>(200), "200" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Int32>(300), "300" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Int32>(400), "400" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Int32>(500), "500" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Int32>(600), "600" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Int32>(700), "700" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Int32>(800), "800" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Int32>(900), "900" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("100"), "100" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("200"), "200" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("300"), "300" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("400"), "400" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("500"), "500" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("600"), "600" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("700"), "700" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("800"), "800" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("900"), "900" },
};

static constexpr int TEST_RESOURCE_ID = 1000;
struct CheckEvent {
    int32_t resourceId;
    Ark_NativePointer parentNode;
};
static std::optional<CheckEvent> checkEventIcon = std::nullopt;
const std::string START_ICON_PROP = "startIcon";
const std::string START_ICON_PATH = "startIconPath";
const std::string START_ICON_RES = "startIconRes";
const std::string END_ICON_PROP = "endIcon";
const std::string END_ICON_PATH = "endIconPath";
const std::string END_ICON_RES = "endIconRes";
const std::string CONTENT_PROP = "content";
const std::string CONTENT = "menuItem";
const std::string CONTENT_RES = "contentRes";
const std::string LABEL_INFO_PROP = "labelInfo";
const std::string LABEL_INFO = "Label";
const std::string LABEL_INFO_RES = "labelInfoRes";

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
        AddResource(START_ICON_RES, START_ICON_PATH);
        AddResource(END_ICON_RES, END_ICON_PATH);
        AddResource(CONTENT_RES, CONTENT);
        AddResource(LABEL_INFO_RES, LABEL_INFO);
    }

    CustomNodeBuilder getBuilderCb()
    {
        auto checkCallback = [](
            const Ark_Int32 resourceId,
            const Ark_NativePointer parentNode,
            const Callback_Pointer_Void continuation) {
            checkEventIcon = {.resourceId = resourceId, .parentNode = parentNode};
        };
        CustomNodeBuilder customBuilder =
            Converter::ArkValue<CustomNodeBuilder>(checkCallback, TEST_RESOURCE_ID);
        return customBuilder;
    }
};

/*
 * @tc.name: setMenuItemOptionsCustomBuilderTest
 * @tc.desc: Check the functionality of MenuItemModifier.setMenuItemOptions
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setMenuItemOptionsCustomBuilderTest, TestSize.Level1)
{
    auto optionsOpt = Converter::ArkUnion<Opt_Union_MenuItemOptions_CustomNodeBuilder, CustomNodeBuilder>(
        getBuilderCb());
    modifier_->setMenuItemOptions(node_, &optionsOpt);
    ASSERT_EQ(checkEventIcon.has_value(), true);
    EXPECT_EQ(checkEventIcon->resourceId, TEST_RESOURCE_ID);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(checkEventIcon->parentNode, frameNode);
}

/*
 * @tc.name: setMenuItemOptionsStartIconStringTest
 * @tc.desc: Check the functionality of MenuItemModifier.setMenuItemOptions
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setMenuItemOptionsStartIconStringTest, TestSize.Level1)
{
    auto startIcon = GetAttrValue<std::string>(node_, START_ICON_PROP);
    EXPECT_EQ(startIcon, "");
    Ark_MenuItemOptions options = { .startIcon =
        Converter::ArkUnion<Opt_ResourceStr, Ark_String>(START_ICON_PATH, Converter::FC)};
    auto optionsOpt = Converter::ArkUnion<Opt_Union_MenuItemOptions_CustomNodeBuilder, Ark_MenuItemOptions>(options);
    modifier_->setMenuItemOptions(node_, &optionsOpt);
    startIcon = GetAttrValue<std::string>(node_, START_ICON_PROP);
    EXPECT_EQ(startIcon, START_ICON_PATH);
}

/*
 * @tc.name: setMenuItemOptionsStartIconResourceTest
 * @tc.desc: Check the functionality of MenuItemModifier.setMenuItemOptions
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setMenuItemOptionsStartIconResourceTest, TestSize.Level1)
{
    auto startIcon = GetAttrValue<std::string>(node_, START_ICON_PROP);
    EXPECT_EQ(startIcon, "");
    Ark_MenuItemOptions options = { .startIcon =
        Converter::ArkUnion<Opt_ResourceStr, Ark_Resource>(CreateResource(START_ICON_RES, ResourceType::STRING))};
    auto optionsOpt = Converter::ArkUnion<Opt_Union_MenuItemOptions_CustomNodeBuilder, Ark_MenuItemOptions>(options);
    modifier_->setMenuItemOptions(node_, &optionsOpt);
    startIcon = GetAttrValue<std::string>(node_, START_ICON_PROP);
    EXPECT_EQ(startIcon, START_ICON_PATH);
}

/*
 * @tc.name: setMenuItemOptionsEndIconStringTest
 * @tc.desc: Check the functionality of MenuItemModifier.setMenuItemOptions
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setMenuItemOptionsEndIconStringTest, TestSize.Level1)
{
    auto endIcon = GetAttrValue<std::string>(node_, END_ICON_PROP);
    EXPECT_EQ(endIcon, "");
    Ark_MenuItemOptions options = { .endIcon =
        Converter::ArkUnion<Opt_ResourceStr, Ark_String>(END_ICON_PATH, Converter::FC)};
    auto optionsOpt = Converter::ArkUnion<Opt_Union_MenuItemOptions_CustomNodeBuilder, Ark_MenuItemOptions>(options);
    modifier_->setMenuItemOptions(node_, &optionsOpt);
    endIcon = GetAttrValue<std::string>(node_, END_ICON_PROP);
    EXPECT_EQ(endIcon, END_ICON_PATH);
}

/*
 * @tc.name: setMenuItemOptionsEndIconResourceTest
 * @tc.desc: Check the functionality of MenuItemModifier.setMenuItemOptions
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setMenuItemOptionsEndIconResourceTest, TestSize.Level1)
{
    auto endIcon = GetAttrValue<std::string>(node_, END_ICON_PROP);
    EXPECT_EQ(endIcon, "");
    Ark_MenuItemOptions options = { .endIcon =
        Converter::ArkUnion<Opt_ResourceStr, Ark_Resource>(CreateResource(END_ICON_RES, ResourceType::STRING))};
    auto optionsOpt = Converter::ArkUnion<Opt_Union_MenuItemOptions_CustomNodeBuilder, Ark_MenuItemOptions>(options);
    modifier_->setMenuItemOptions(node_, &optionsOpt);
    endIcon = GetAttrValue<std::string>(node_, END_ICON_PROP);
    EXPECT_EQ(endIcon, END_ICON_PATH);
}

/*
 * @tc.name: setMenuItemOptionsContentStringTest
 * @tc.desc: Check the functionality of MenuItemModifier.setMenuItemOptions
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setMenuItemOptionsContentStringTest, TestSize.Level1)
{
    auto content = GetAttrValue<std::string>(node_, CONTENT_PROP);
    EXPECT_EQ(content, "");
    Ark_MenuItemOptions options = { .content =
        Converter::ArkUnion<Opt_ResourceStr, Ark_String>(CONTENT, Converter::FC)};
    auto optionsOpt = Converter::ArkUnion<Opt_Union_MenuItemOptions_CustomNodeBuilder, Ark_MenuItemOptions>(options);
    modifier_->setMenuItemOptions(node_, &optionsOpt);
    content = GetAttrValue<std::string>(node_, CONTENT_PROP);
    EXPECT_EQ(content, CONTENT);
}

/*
 * @tc.name: setMenuItemOptionsContentResourceTest
 * @tc.desc: Check the functionality of MenuItemModifier.setMenuItemOptions
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setMenuItemOptionsContentResourceTest, TestSize.Level1)
{
    auto content = GetAttrValue<std::string>(node_, CONTENT_PROP);
    EXPECT_EQ(content, "");
    Ark_MenuItemOptions options = { .content =
        Converter::ArkUnion<Opt_ResourceStr, Ark_Resource>(CreateResource(CONTENT_RES, ResourceType::STRING))};
    auto optionsOpt = Converter::ArkUnion<Opt_Union_MenuItemOptions_CustomNodeBuilder, Ark_MenuItemOptions>(options);
    modifier_->setMenuItemOptions(node_, &optionsOpt);
    content = GetAttrValue<std::string>(node_, CONTENT_PROP);
    EXPECT_EQ(content, CONTENT);
}

/*
 * @tc.name: setMenuItemOptionsLabelInfoStringTest
 * @tc.desc: Check the functionality of MenuItemModifier.setMenuItemOptions
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setMenuItemOptionsLabelInfoStringTest, TestSize.Level1)
{
    auto labelInfo = GetAttrValue<std::string>(node_, LABEL_INFO_PROP);
    EXPECT_EQ(labelInfo, "");
    Ark_MenuItemOptions options = { .labelInfo =
        Converter::ArkUnion<Opt_ResourceStr, Ark_String>(LABEL_INFO, Converter::FC)};
    auto optionsOpt = Converter::ArkUnion<Opt_Union_MenuItemOptions_CustomNodeBuilder, Ark_MenuItemOptions>(options);
    modifier_->setMenuItemOptions(node_, &optionsOpt);
    labelInfo = GetAttrValue<std::string>(node_, LABEL_INFO_PROP);
    EXPECT_EQ(labelInfo, LABEL_INFO);
}

/*
 * @tc.name: setMenuItemOptionsLabelInfoResourceTest
 * @tc.desc: Check the functionality of MenuItemModifier.setMenuItemOptions
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setMenuItemOptionsLabelInfoResourceTest, TestSize.Level1)
{
    auto labelInfo = GetAttrValue<std::string>(node_, LABEL_INFO_PROP);
    EXPECT_EQ(labelInfo, "");
    Ark_MenuItemOptions options = { .labelInfo =
        Converter::ArkUnion<Opt_ResourceStr, Ark_Resource>(CreateResource(LABEL_INFO_RES, ResourceType::STRING))};
    auto optionsOpt = Converter::ArkUnion<Opt_Union_MenuItemOptions_CustomNodeBuilder, Ark_MenuItemOptions>(options);
    modifier_->setMenuItemOptions(node_, &optionsOpt);
    labelInfo = GetAttrValue<std::string>(node_, LABEL_INFO_PROP);
    EXPECT_EQ(labelInfo, LABEL_INFO);
}

/*
 * @tc.name: setMenuItemOptionsSymbolStartIconTest
 * @tc.desc: Check the functionality of MenuItemModifier.setMenuItemOptions
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setMenuItemOptionsSymbolStartIconTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetStartSymbol(), nullptr);

    auto symbolPeer = PeerUtils::CreatePeer<SymbolGlyphModifierPeer>();
    symbolPeer->symbolApply = [](WeakPtr<NG::FrameNode>) {};
    Ark_MenuItemOptions options = {.symbolStartIcon = Converter::ArkValue<Opt_SymbolGlyphModifier>(symbolPeer)};
    auto optionsOpt = Converter::ArkUnion<Opt_Union_MenuItemOptions_CustomNodeBuilder, Ark_MenuItemOptions>(options);
    modifier_->setMenuItemOptions(node_, &optionsOpt);
    layoutProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_NE(layoutProperty->GetStartSymbol(), nullptr);
}

/*
 * @tc.name: setMenuItemOptionsSymbolEndIconTest
 * @tc.desc: Check the functionality of MenuItemModifier.setMenuItemOptions
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setMenuItemOptionsSymbolEndIconTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetEndSymbol(), nullptr);

    auto symbolPeer = PeerUtils::CreatePeer<SymbolGlyphModifierPeer>();
    symbolPeer->symbolApply = [](WeakPtr<NG::FrameNode>) {};
    Ark_MenuItemOptions options = {.symbolEndIcon = Converter::ArkValue<Opt_SymbolGlyphModifier>(symbolPeer)};
    auto optionsOpt = Converter::ArkUnion<Opt_Union_MenuItemOptions_CustomNodeBuilder, Ark_MenuItemOptions>(options);
    modifier_->setMenuItemOptions(node_, &optionsOpt);
    layoutProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_NE(layoutProperty->GetEndSymbol(), nullptr);
}

/*
 * @tc.name: setMenuItemOptionsMenuItemOptionsCustomBuilderTest
 * @tc.desc: Check the functionality of MenuItemModifier.setMenuItemOptions
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setMenuItemOptionsMenuItemOptionsCustomBuilderTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->GetSubBuilder(), nullptr);

    auto builder = getBuilderCb();
    auto iconBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
    Ark_MenuItemOptions options = {.builder = iconBuilder};
    auto optionsOpt = Converter::ArkUnion<Opt_Union_MenuItemOptions_CustomNodeBuilder, Ark_MenuItemOptions>(options);
    modifier_->setMenuItemOptions(node_, &optionsOpt);
    pattern = frameNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_NE(pattern->GetSubBuilder(), nullptr);
}

/*
 * @tc.name: setSelectIconSymbolTest
 * @tc.desc: Check the functionality of MenuItemModifier.setMenuItemOptions
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setSelectIconSymbolTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetSelectSymbol(), nullptr);

    auto symbolPeer = PeerUtils::CreatePeer<SymbolGlyphModifierPeer>();
    symbolPeer->symbolApply = [](WeakPtr<NG::FrameNode>) {};
    auto optIcon = Converter::ArkUnion<Opt_Union_Boolean_ResourceStr_SymbolGlyphModifier,
        Ark_SymbolGlyphModifier>(symbolPeer);
    modifier_->setSelectIcon(node_, &optIcon);
    layoutProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_NE(layoutProperty->GetSelectSymbol(), nullptr);
}

/*
 * @tc.name: setSelectedTest
 * @tc.desc: Check the functionality of MenuItemModifier.setSelected
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setSelectedTest, TestSize.Level1)
{
    bool selected = GetAttrValue<bool>(node_, "selected");
    EXPECT_FALSE(selected);
    auto optValue = Converter::ArkUnion<Opt_Union_Boolean_Bindable_Boolean, Ark_Boolean>(true);
    modifier_->setSelected(node_, &optValue);
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

    auto optIcon = Converter::ArkUnion<Opt_Union_Boolean_ResourceStr_SymbolGlyphModifier, Ark_Boolean>(true);
    modifier_->setSelectIcon(node_, &optIcon);
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

    auto optIcon = Converter::ArkUnion<Opt_Union_Boolean_ResourceStr_SymbolGlyphModifier, Ark_ResourceStr>(resStr);
    modifier_->setSelectIcon(node_, &optIcon);
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
    Ark_Resource iconRes = CreateResource(ICON_OK_STR.c_str(), ResourceType::STRING);
    Ark_ResourceStr resStr = Converter::ArkUnion<Ark_ResourceStr, Ark_Resource>(iconRes);
    auto optIcon = Converter::ArkUnion<Opt_Union_Boolean_ResourceStr_SymbolGlyphModifier, Ark_ResourceStr>(resStr);
    modifier_->setSelectIcon(node_, &optIcon);
    selectIcon = GetAttrValue<std::string>(node_, "selectIcon");
    EXPECT_EQ(selectIcon, "path_to_select_icon");
}

/**
 * @tc.name: setContentFontColorTest
 * @tc.desc: Check the functionality of MenuItemModifier.setContentFontColor
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, DISABLED_setContentFontColorTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setContentFontColor, nullptr);
    auto checkVal = GetAttrValue<std::string>(node_, "contentFontColor");
    EXPECT_EQ(checkVal, COLOR_THEME_FONT);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        auto optValue = Converter::ArkValue<Opt_ResourceColor>(value);
        modifier_->setContentFontColor(node_, &optValue);
        checkVal = GetAttrValue<std::string>(node_, "contentFontColor");
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setContentFontColorTestRes
 * @tc.desc: Check the functionality of MenuItemModifier.setContentFontColor
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, DISABLED_setContentFontColorTestRes, TestSize.Level1)
{
    ASSERT_NE(modifier_->setContentFontColor, nullptr);
    auto checkVal = GetAttrValue<std::string>(node_, "contentFontColor");
    EXPECT_EQ(checkVal, COLOR_THEME_FONT);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN_RES) {
        auto optValue = Converter::ArkValue<Opt_ResourceColor>(value);
        modifier_->setContentFontColor(node_, &optValue);
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
        auto optValue = Converter::ArkValue<Opt_ResourceColor>(value);
        modifier_->setContentFontColor(node_, &optValue);
        checkVal = GetAttrValue<std::string>(node_, "contentFontColor");
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setLabelFontColorTest
 * @tc.desc: Check the functionality of MenuItemModifier.setLabelFontColor
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, DISABLED_setLabelFontColorTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setLabelFontColor, nullptr);
    auto checkVal = GetAttrValue<std::string>(node_, "labelFontColor");
    EXPECT_EQ(checkVal, COLOR_THEME_FONT_ALPHA_06);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN1) {
        auto optValue = Converter::ArkValue<Opt_ResourceColor>(value);
        modifier_->setLabelFontColor(node_, &optValue);
        checkVal = GetAttrValue<std::string>(node_, "labelFontColor");
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setLabelFontColorTestRes
 * @tc.desc: Check the functionality of MenuItemModifier.setLabelFontColor
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, DISABLED_setLabelFontColorTestRes, TestSize.Level1)
{
    ASSERT_NE(modifier_->setLabelFontColor, nullptr);
    auto checkVal = GetAttrValue<std::string>(node_, "labelFontColor");
    EXPECT_EQ(checkVal, COLOR_THEME_FONT_ALPHA_06);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN_RES) {
        auto optValue = Converter::ArkValue<Opt_ResourceColor>(value);
        modifier_->setLabelFontColor(node_, &optValue);
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
        auto optValue = Converter::ArkValue<Opt_ResourceColor>(value);
        modifier_->setLabelFontColor(node_, &optValue);
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
    Ark_arkui_component_units_Font font = {
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
        auto optFont = Converter::ArkValue<Opt_arkui_component_units_Font>(font);
        modifier_->setContentFont(node_, &optFont);
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
    Ark_arkui_component_units_Font font = {
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
        auto optFont = Converter::ArkValue<Opt_arkui_component_units_Font>(font);
        modifier_->setContentFont(node_, &optFont);
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
    Ark_arkui_component_units_Font font = {
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
        auto optFont = Converter::ArkValue<Opt_arkui_component_units_Font>(font);
        modifier_->setContentFont(node_, &optFont);
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
    Ark_arkui_component_units_Font font = {
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
        auto optFont = Converter::ArkValue<Opt_arkui_component_units_Font>(font);
        modifier_->setContentFont(node_, &optFont);
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
HWTEST_F(MenuItemModifierTest, DISABLED_setContentFontTest5, TestSize.Level1)
{
    ASSERT_NE(modifier_->setContentFont, nullptr);
    Ark_arkui_component_units_Font font = {
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
        auto optFont = Converter::ArkValue<Opt_arkui_component_units_Font>(font);
        modifier_->setContentFont(node_, &optFont);
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
    Ark_arkui_component_units_Font font = {
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
        auto optFont = Converter::ArkValue<Opt_arkui_component_units_Font>(font);
        modifier_->setLabelFont(node_, &optFont);
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
    Ark_arkui_component_units_Font font = {
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
        auto optFont = Converter::ArkValue<Opt_arkui_component_units_Font>(font);
        modifier_->setLabelFont(node_, &optFont);
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
    Ark_arkui_component_units_Font font = {
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
        auto optFont = Converter::ArkValue<Opt_arkui_component_units_Font>(font);
        modifier_->setLabelFont(node_, &optFont);
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
    Ark_arkui_component_units_Font font = {
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
        auto optFont = Converter::ArkValue<Opt_arkui_component_units_Font>(font);
        modifier_->setLabelFont(node_, &optFont);
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
HWTEST_F(MenuItemModifierTest, DISABLED_setLabelFontTest5, TestSize.Level1)
{
    ASSERT_NE(modifier_->setLabelFont, nullptr);
    Ark_arkui_component_units_Font font = {
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
        auto optFont = Converter::ArkValue<Opt_arkui_component_units_Font>(font);
        modifier_->setLabelFont(node_, &optFont);
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
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<MenuItemEventHub>();

    struct CheckEvent {
        int32_t nodeId;
        bool selected;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    void (*checkCallback)(const Ark_Int32, const Ark_Boolean) =
        [](const Ark_Int32 resourceId, const Ark_Boolean param) {
            checkEvent = {
                .nodeId = resourceId,
                .selected = Converter::Convert<bool>(param)
            };
        };
    const int32_t contextId = 123;
    auto func = Converter::ArkValue<Callback_Boolean_Void>(checkCallback, contextId);

    auto onChange = eventHub->GetOnChange();
    EXPECT_EQ(onChange, nullptr);
    auto optFunc = Converter::ArkValue<Opt_Callback_Boolean_Void>(func);
    modifier_->setOnChange(node_, &optFunc);
    onChange = eventHub->GetOnChange();
    EXPECT_NE(onChange, nullptr);
    // check true value
    EXPECT_FALSE(checkEvent.has_value());
    onChange(true);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_TRUE(checkEvent->selected);
    // check false value
    onChange(false);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_FALSE(checkEvent->selected);
}

#ifdef WRONG_OLD_GEN
/*
 * @tc.name: setOnChangeEventSelectedImpl
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModifierTest, setOnChangeEventSelectedImpl, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<MenuItemEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        std::optional<bool> value;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;

    auto checkCallback = [](const Ark_Int32 resourceId, const Opt_Boolean parameter) {
        checkEvent = {
            .nodeId = resourceId,
            .value = Converter::OptConvert<bool>(parameter)
        };
    };

    auto arkCallback = Converter::ArkValue<Callback_Opt_Boolean_Void>(checkCallback, contextId);
    modifier_->set_onChangeEvent_selected(node_, &arkCallback);

    ASSERT_EQ(checkEvent.has_value(), false);
    auto changeEvent = eventHub->GetSelectedChangeEvent();
    changeEvent(true);
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_EQ(checkEvent->value, true);
    changeEvent(false);
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_EQ(checkEvent->value, false);
}
#endif
} // namespace OHOS::Ace::NG
