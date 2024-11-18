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

#include "core/components/select/select_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/pattern/select/select_model_ng.h"
#include "core/components_ng/pattern/select/select_pattern.h"

#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace {
const auto THEME_SPACE = Dimension(23, DimensionUnit::PX);
const double THEME_FONT_OPACITY = 0.5;
const Color THEME_BACKGROUND_COLOR(0xFFAABBC1);
const Color THEME_FONT_COLOR(0xFFAABBC3);
const Color THEME_SELECTED_OPTION_FONT_COLOR(0xFFAABBC4);

const auto DEFAULT_FONT_SIZE = "14.00px";
const auto DEFAULT_FONT_WEIGHT = "FontWeight.Normal";
const auto DEFAULT_FONT_FAMILY = "";
const auto DEFAULT_FONT_STYLE = "FontStyle.Normal";

const Ark_Font TEST_ARK_FONT = {
    .size = ArkValue<Opt_Length>(12),
    .weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(ARK_FONT_WEIGHT_BOLD),
    .family = ArkUnion<Opt_Union_String_Resource, Ark_String>("TestFontFamily"),
    .style = ArkValue<Opt_FontStyle>(ARK_FONT_STYLE_ITALIC),
};
const auto EXPECTED_FONT_SIZE = "12.00px";
const auto EXPECTED_FONT_WEIGHT = "FontWeight.Bold";
const auto EXPECTED_FONT_FAMILY = "TestFontFamily";
const auto EXPECTED_FONT_STYLE = "FontStyle.Italic";

const auto SELECTED_INDEX = ArkUnion<Ark_Union_Number_Resource, Ark_Number>(1);
const auto INVALID_INDEX = ArkUnion<Ark_Union_Number_Resource, Ark_Number>(-1);

const std::vector<Ark_SelectOption> SELECT_PARAMS = {
    { .value = ArkUnion<Ark_ResourceStr, Ark_String>("Option A") },
    { .value = ArkUnion<Ark_ResourceStr, Ark_String>("Option B") },
    { .value = ArkUnion<Ark_ResourceStr, Ark_String>("Option C") },
};

// length values
const Ark_Int32 AINT32_POS(1234);
const Ark_Int32 AINT32_NEG(INT_MIN);
const Ark_Float32 AFLT32_POS(1.234f);
const Ark_Float32 AFLT32_NEG(-5.6789f);
const auto ALEN_PX_POS = ArkValue<Ark_Length>(AINT32_POS);
const auto ALEN_PX_NEG = ArkValue<Ark_Length>(AINT32_NEG);
const auto ALEN_VP_POS = ArkValue<Ark_Length>(AFLT32_POS);
const auto ALEN_VP_NEG = ArkValue<Ark_Length>(AFLT32_NEG);
static const auto OPT_LEN_PX_POS = ArkValue<Opt_Length>(AINT32_POS);
static const auto OPT_LEN_PX_NEG = ArkValue<Opt_Length>(AINT32_NEG);
static const auto OPT_LEN_VP_POS = ArkValue<Opt_Length>(AFLT32_POS);
static const auto OPT_LEN_VP_NEG = ArkValue<Opt_Length>(AFLT32_NEG);

// check length
const std::string CHECK_POSITIVE_VALUE_INT("1234.00px");
const std::string CHECK_NEGATIVE_VALUE_INT("-2147483648.00px");
const std::string CHECK_POSITIVE_VALUE_FLOAT("1.23vp");
const std::string CHECK_POSITIVE_VALUE_FLOAT_PX("1.23px");
const std::string CHECK_NEGATIVE_VALUE_FLOAT("-5.68vp");

const auto FONT_ATTR("font");
const auto SELECTED_OPTION_FONT_ATTR("selectedOptionFont");
const auto OPTION_FONT_ATTR("optionFont");
const auto FONT_SIZE("size");
const auto FONT_FAMILY("family");
const auto FONT_WEIGHT("weight");
const auto FONT_STYLE("style");

const auto FONT_FAMILY_RES_NAME = "Family resource name";
const auto FONT_FAMILY_RES_VALUE = "FontFamilyA,FontFamilyB,   FontFamilyC";

const auto VALUE_RES_NAME = "Value resource name";
const auto VALUE_RES_VALUE = "Select value";

const auto OPTIONS_VALUE_RES_NAME = "SelectOption value resource name";
const auto OPTIONS_VALUE_RES_VALUE = "SelectOption value";
const auto OPTIONS_ICON_RES_NAME = "SelectOption icon resource name";
const auto OPTIONS_ICON_RES_VALUE = "SelectOption icon";

using FontTestStep = std::tuple<Ark_Font, std::string>;

struct MenuAlignTest {
    Ark_MenuAlignType menuAlignType;
    Ark_Offset offset;
    std::string expectedMenuAlignType;
    float expectedDx;
    float expectedDy;
};

std::vector<FontTestStep> getFontSizeTestPlan(const std::string& defaultValue)
{
    const std::vector<FontTestStep> testPlan = {
        {{ .size = OPT_LEN_VP_POS }, CHECK_POSITIVE_VALUE_FLOAT },
        {{ .size = OPT_LEN_PX_POS }, CHECK_POSITIVE_VALUE_INT },
        {{ .size = OPT_LEN_VP_NEG }, defaultValue },
        {{ .size = OPT_LEN_PX_NEG }, defaultValue },
        {{ .size = ArkValue<Opt_Dimension>(Ark_Empty()) }, defaultValue },
    };
    return testPlan;
}

std::vector<FontTestStep> getFontWeightTestPlan(const std::string& defaultValue)
{
    using FontWeightT = Opt_Union_FontWeight_Number_String;
    const std::vector<FontTestStep> testPlan = {
        { {.weight = ArkUnion<FontWeightT, Ark_FontWeight>(ARK_FONT_WEIGHT_BOLD)}, "FontWeight.Bold" },
        { {.weight = ArkUnion<FontWeightT, Ark_FontWeight>(ARK_FONT_WEIGHT_REGULAR)}, "FontWeight.Regular" },
        { {.weight = ArkUnion<FontWeightT, Ark_Number>(100)}, "100" },
        { {.weight = ArkUnion<FontWeightT, Ark_Number>(-111)}, defaultValue },
        { {.weight = ArkUnion<FontWeightT, Ark_Number>(300.00f)}, "300" },
        { {.weight = ArkUnion<FontWeightT, Ark_Number>(-123.456f)}, defaultValue },
        { {.weight = ArkUnion<FontWeightT, Ark_String>("700")}, "700" },
        { {.weight = ArkUnion<FontWeightT, Ark_String>("bold")}, "FontWeight.Bold" },
        { {.weight = ArkUnion<FontWeightT, Ark_String>("InvalidData!")}, defaultValue },
        { {.weight = ArkValue<FontWeightT>(Ark_Empty())}, defaultValue },
    };
    return testPlan;
}

std::vector<FontTestStep> getFontStyleTestPlan()
{
    const std::vector<FontTestStep> testPlan = {
        { { .style = ArkValue<Opt_FontStyle>(ARK_FONT_STYLE_NORMAL) }, "FontStyle.Normal" },
        { { .style = ArkValue<Opt_FontStyle>(ARK_FONT_STYLE_ITALIC) }, "FontStyle.Italic" },
        { { .style = ArkValue<Opt_FontStyle>(static_cast<Ark_FontStyle>(INT_MIN)) }, DEFAULT_FONT_STYLE },
        { { .style = ArkValue<Opt_FontStyle>(ARK_FONT_STYLE_ITALIC) }, "FontStyle.Italic" },
        { { .style = ArkValue<Opt_FontStyle>(Ark_Empty()) }, DEFAULT_FONT_STYLE },
    };
    return testPlan;
}

std::vector<FontTestStep> getFontFamilyTestPlan()
{
    const auto familyStr1 = "Family string value";

    // static keyword is required because a pointer to this variable is stored in testPlan
    static auto arkResName = NamedResourceId(FONT_FAMILY_RES_NAME, NodeModifier::ResourceType::STRARRAY);

    const std::vector<FontTestStep> testPlan = {
        { { .family = ArkUnion<Opt_Union_String_Resource, Ark_String>(familyStr1) }, familyStr1 },
        { { .family = CreateResourceUnion<Opt_Union_String_Resource>(arkResName) }, FONT_FAMILY_RES_VALUE },
        { { .family = ArkValue<Opt_Union_String_Resource>(Ark_Empty()) }, DEFAULT_FONT_FAMILY },
    };
    return testPlan;
}

struct TestFont {
    std::string size;
    std::string weight;
    std::string family;
    std::string style;

    TestFont(Ark_NodeHandle node, std::string propName)
    {
        auto fontStr = GetStringAttribute(node, propName);
        auto fontJson = JsonUtil::ParseJsonString(fontStr);
        if (fontJson) {
            size = fontJson->GetString(FONT_SIZE);
            weight = fontJson->GetString(FONT_WEIGHT);
            family = fontJson->GetString(FONT_FAMILY);
            style = fontJson->GetString(FONT_STYLE);
        }
    }
};

int g_eventOnSelectIndex;
std::string g_eventOnSelectValue;

GENERATED_ArkUISelectEventsReceiver recv {
    .onSelect = [](Ark_Int32 nodeId, const Ark_Number index, const Ark_String value) {
        g_eventOnSelectIndex = Convert<int>(index);
        g_eventOnSelectValue = Convert<std::string>(value);
    }
};

const GENERATED_ArkUISelectEventsReceiver* getSelectEventsReceiverTest()
{
    return &recv;
};

const GENERATED_ArkUIEventsAPI* GetArkUiEventsAPITest()
{
    static const GENERATED_ArkUIEventsAPI eventsImpl = { .getSelectEventsReceiver = getSelectEventsReceiverTest };
    return &eventsImpl;
};

float strToFloat(const std::string& str)
{
    char* ptr = nullptr;
    float result = strtof(str.c_str(), &ptr);
    return (ptr == str.c_str()) ? std::numeric_limits<float>::min() : result;
}
} // namespace

class SelectModifierTest : public ModifierTestBase<GENERATED_ArkUISelectModifier,
    &GENERATED_ArkUINodeModifiers::getSelectModifier, GENERATED_ARKUI_SELECT> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        // set test values to Theme Pattern as data for the Theme building
        auto themeStyle = SetupThemeStyle("select_pattern");
        themeStyle->SetAttr("content_spinner_padding", { .value = THEME_SPACE });
        themeStyle->SetAttr("bg_color", { .value = THEME_BACKGROUND_COLOR });
        themeStyle->SetAttr("text_color", { .value = THEME_FONT_COLOR });
        themeStyle->SetAttr("text_color_selected", { .value = THEME_SELECTED_OPTION_FONT_COLOR });
        themeStyle->SetAttr("menu_text_primary_alpha", { .value = THEME_FONT_OPACITY });

        SetupTheme<SelectTheme>();
        SetupTheme<TextTheme>();
        SetupTheme<IconTheme>();

        AddResource(FONT_FAMILY_RES_NAME, FONT_FAMILY_RES_VALUE);
        AddResource(VALUE_RES_NAME, VALUE_RES_VALUE);
        AddResource(OPTIONS_VALUE_RES_NAME, OPTIONS_VALUE_RES_VALUE);
        AddResource(OPTIONS_ICON_RES_NAME, OPTIONS_ICON_RES_VALUE);

        fullAPI_->setArkUIEventsAPI(GetArkUiEventsAPITest());
    }

    void SetUp(void) override
    {
        ModifierTestBase::SetUp();

        ASSERT_NE(modifier_->setSelectOptions, nullptr);
        auto arrayHolder = ArkArrayHolder<Array_SelectOption>(SELECT_PARAMS);
        auto arkArray = arrayHolder.ArkValue();
        modifier_->setSelectOptions(node_, &arkArray);

        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_TRUE(frameNode);
        auto selectPattern = frameNode->GetPatternPtr<SelectPattern>();
        ASSERT_TRUE(selectPattern);
        std::vector<RefPtr<FrameNode>> options = selectPattern->GetOptions();
        ASSERT_FALSE(options.empty());
        auto optionFrameNode = options[0];
        ASSERT_TRUE(optionFrameNode);
        auto pattern = optionFrameNode->GetPattern();
        ASSERT_TRUE(pattern);
        pattern->OnModifyDone(); // Init selectTheme
    }
};

/**
 * @tc.name: setFontColorTest
 * @tc.desc: Test setFontColor function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setFontColorTest, TestSize.Level1)
{
    const std::string propName("fontColor");
    const Color defaultColor = THEME_FONT_COLOR.BlendOpacity(THEME_FONT_OPACITY);

    ASSERT_NE(modifier_->setFontColor, nullptr);

    auto checkVal1 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal1, defaultColor.ToString());

    Ark_ResourceColor color = ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_WHITE);
    modifier_->setFontColor(node_, &color);
    auto checkVal2 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal2, "#FFFFFFFF");

    Ark_ResourceColor numberInt = ArkUnion<Ark_ResourceColor, Ark_Number>(0x123401);
    modifier_->setFontColor(node_, &numberInt);
    auto checkVal3 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal3, "#FF123401");

    Ark_ResourceColor numberFlt = ArkUnion<Ark_ResourceColor, Ark_Number>(0.5f);
    modifier_->setFontColor(node_, &numberFlt);
    auto checkVal4 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal4, "#00000000");

    Ark_ResourceColor strColor = ArkUnion<Ark_ResourceColor, Ark_String>("#11223344");
    modifier_->setFontColor(node_, &strColor);
    auto checkVal5 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal5, "#11223344");

    Ark_ResourceColor strNumber = ArkUnion<Ark_ResourceColor, Ark_String>("65535");
    modifier_->setFontColor(node_, &strNumber);
    auto checkVal6 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal6, "#FF00FFFF");

    auto resNameColor = CreateResourceUnion<Ark_ResourceColor>(
        NamedResourceId{"aa.bb.cc", NodeModifier::ResourceType::COLOR});
    modifier_->setFontColor(node_, &resNameColor);
    auto checkVal7 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal7, "#FFFF0000"); // Color::RED is result of mocked ThemeConstants::GetColorByName

    auto resIdColor = CreateResourceUnion<Ark_ResourceColor>(IntResourceId{1234, NodeModifier::ResourceType::COLOR});
    modifier_->setFontColor(node_, &resIdColor);
    auto checkVal8 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal8, "#FFFF0000"); // Color::RED is result of mocked ThemeConstants::GetColor(int)
}

/**
 * @tc.name: setMenuBackgroundColorTest
 * @tc.desc: Test setMenuBackgroundColor function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setMenuBackgroundColorTest, TestSize.Level1)
{
    const std::string propName("menuBackgroundColor");
    ASSERT_NE(modifier_->setMenuBackgroundColor, nullptr);

    auto checkVal1 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal1, Color::TRANSPARENT.ToString());

    Ark_ResourceColor color = ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_WHITE);
    modifier_->setMenuBackgroundColor(node_, &color);
    auto checkVal2 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal2, "#FFFFFFFF");

    Ark_ResourceColor numberInt = ArkUnion<Ark_ResourceColor, Ark_Number>(0x123401);
    modifier_->setMenuBackgroundColor(node_, &numberInt);
    auto checkVal3 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal3, "#FF123401");

    Ark_ResourceColor numberFlt = ArkUnion<Ark_ResourceColor, Ark_Number>(0.5f);
    modifier_->setMenuBackgroundColor(node_, &numberFlt);
    auto checkVal4 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal4, "#00000000");

    Ark_ResourceColor strColor = ArkUnion<Ark_ResourceColor, Ark_String>("#11223344");
    modifier_->setMenuBackgroundColor(node_, &strColor);
    auto checkVal5 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal5, "#11223344");

    Ark_ResourceColor strNumber = ArkUnion<Ark_ResourceColor, Ark_String>("65535");
    modifier_->setMenuBackgroundColor(node_, &strNumber);
    auto checkVal6 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal6, "#FF00FFFF");

    auto resNameColor = CreateResourceUnion<Ark_ResourceColor>(
        NamedResourceId{"aa.bb.cc", NodeModifier::ResourceType::COLOR});
    modifier_->setMenuBackgroundColor(node_, &resNameColor);
    auto checkVal7 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal7, "#FFFF0000"); // Color::RED is result of mocked ThemeConstants::GetColorByName

    auto resIdColor = CreateResourceUnion<Ark_ResourceColor>(IntResourceId{1234, NodeModifier::ResourceType::COLOR});
    modifier_->setMenuBackgroundColor(node_, &resIdColor);
    auto checkVal8 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal8, "#FFFF0000"); // Color::RED is result of mocked ThemeConstants::GetColor(int)
}

/**
 * @tc.name: setSelectedOptionBgColorTest
 * @tc.desc: Test setSelectedOptionBgColor function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedOptionBgColorTest, TestSize.Level1)
{
    const std::string propName("selectedOptionBgColor");
    ASSERT_NE(modifier_->setSelectedOptionBgColor, nullptr);

    auto checkVal1 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal1, "");

    Ark_ResourceColor color = ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_WHITE);
    modifier_->setSelectedOptionBgColor(node_, &color);
    auto checkVal2 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal2, "#FFFFFFFF");

    Ark_ResourceColor numberInt = ArkUnion<Ark_ResourceColor, Ark_Number>(0x123401);
    modifier_->setSelectedOptionBgColor(node_, &numberInt);
    auto checkVal3 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal3, "#FF123401");

    Ark_ResourceColor numberFlt = ArkUnion<Ark_ResourceColor, Ark_Number>(0.5f);
    modifier_->setSelectedOptionBgColor(node_, &numberFlt);
    auto checkVal4 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal4, "#00000000");

    Ark_ResourceColor strColor = ArkUnion<Ark_ResourceColor, Ark_String>("#11223344");
    modifier_->setSelectedOptionBgColor(node_, &strColor);
    auto checkVal5 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal5, "#11223344");

    Ark_ResourceColor strNumber = ArkUnion<Ark_ResourceColor, Ark_String>("65535");
    modifier_->setSelectedOptionBgColor(node_, &strNumber);
    auto checkVal6 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal6, "#FF00FFFF");

    auto resNameColor = CreateResourceUnion<Ark_ResourceColor>(
        NamedResourceId{"aa.bb.cc", NodeModifier::ResourceType::COLOR});
    modifier_->setSelectedOptionBgColor(node_, &resNameColor);
    auto checkVal7 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal7, "#FFFF0000"); // Color::RED is result of mocked ThemeConstants::GetColorByName

    auto resIdColor = CreateResourceUnion<Ark_ResourceColor>(IntResourceId{1234, NodeModifier::ResourceType::COLOR});
    modifier_->setSelectedOptionBgColor(node_, &resIdColor);
    auto checkVal8 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal8, "#FFFF0000"); // Color::RED is result of mocked ThemeConstants::GetColor(int)
}

/**
 * @tc.name: setSelectedOptionFontColorTest
 * @tc.desc: Test setSelectedOptionFontColor function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedOptionFontColorTest, TestSize.Level1)
{
    const std::string propName("selectedOptionFontColor");
    ASSERT_NE(modifier_->setSelectedOptionFontColor, nullptr);

    auto checkVal1 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal1, THEME_SELECTED_OPTION_FONT_COLOR.ToString());

    Ark_ResourceColor color = ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_WHITE);
    modifier_->setSelectedOptionFontColor(node_, &color);
    auto checkVal2 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal2, "#FFFFFFFF");

    Ark_ResourceColor numberInt = ArkUnion<Ark_ResourceColor, Ark_Number>(0x123401);
    modifier_->setSelectedOptionFontColor(node_, &numberInt);
    auto checkVal3 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal3, "#FF123401");

    Ark_ResourceColor numberFlt = ArkUnion<Ark_ResourceColor, Ark_Number>(0.5f);
    modifier_->setSelectedOptionFontColor(node_, &numberFlt);
    auto checkVal4 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal4, "#00000000");

    Ark_ResourceColor strColor = ArkUnion<Ark_ResourceColor, Ark_String>("#11223344");
    modifier_->setSelectedOptionFontColor(node_, &strColor);
    auto checkVal5 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal5, "#11223344");

    Ark_ResourceColor strNumber = ArkUnion<Ark_ResourceColor, Ark_String>("65535");
    modifier_->setSelectedOptionFontColor(node_, &strNumber);
    auto checkVal6 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal6, "#FF00FFFF");

    auto resNameColor = CreateResourceUnion<Ark_ResourceColor>(
        NamedResourceId{"aa.bb.cc", NodeModifier::ResourceType::COLOR});
    modifier_->setSelectedOptionFontColor(node_, &resNameColor);
    auto checkVal7 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal7, "#FFFF0000"); // Color::RED is result of mocked ThemeConstants::GetColorByName

    auto resIdColor = CreateResourceUnion<Ark_ResourceColor>(IntResourceId{1234, NodeModifier::ResourceType::COLOR});
    modifier_->setSelectedOptionFontColor(node_, &resIdColor);
    auto checkVal8 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal8, "#FFFF0000"); // Color::RED is result of mocked ThemeConstants::GetColor(int)
}

/**
 * @tc.name: setOptionBgColorTest
 * @tc.desc: Test setOptionBgColor function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setOptionBgColorTest, TestSize.Level1)
{
    const std::string propName("optionBgColor");
    ASSERT_NE(modifier_->setOptionBgColor, nullptr);

    auto checkVal1 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal1, Color::TRANSPARENT.ToString());

    Ark_ResourceColor color = ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_WHITE);
    modifier_->setOptionBgColor(node_, &color);
    auto checkVal2 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal2, "#FFFFFFFF");

    Ark_ResourceColor numberInt = ArkUnion<Ark_ResourceColor, Ark_Number>(0x123401);
    modifier_->setOptionBgColor(node_, &numberInt);
    auto checkVal3 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal3, "#FF123401");

    Ark_ResourceColor numberFlt = ArkUnion<Ark_ResourceColor, Ark_Number>(0.5f);
    modifier_->setOptionBgColor(node_, &numberFlt);
    auto checkVal4 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal4, "#00000000");

    Ark_ResourceColor strColor = ArkUnion<Ark_ResourceColor, Ark_String>("#11223344");
    modifier_->setOptionBgColor(node_, &strColor);
    auto checkVal5 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal5, "#11223344");

    Ark_ResourceColor strNumber = ArkUnion<Ark_ResourceColor, Ark_String>("65535");
    modifier_->setOptionBgColor(node_, &strNumber);
    auto checkVal6 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal6, "#FF00FFFF");

    auto resNameColor = CreateResourceUnion<Ark_ResourceColor>(
        NamedResourceId{"aa.bb.cc", NodeModifier::ResourceType::COLOR});
    modifier_->setOptionBgColor(node_, &resNameColor);
    auto checkVal7 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal7, "#FFFF0000"); // Color::RED is result of mocked ThemeConstants::GetColorByName

    auto resIdColor = CreateResourceUnion<Ark_ResourceColor>(IntResourceId{1234, NodeModifier::ResourceType::COLOR});
    modifier_->setOptionBgColor(node_, &resIdColor);
    auto checkVal8 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal8, "#FFFF0000"); // Color::RED is result of mocked ThemeConstants::GetColor(int)
}

/**
 * @tc.name: setOptionFontColorTest
 * @tc.desc: Test setOptionFontColor function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setOptionFontColorTest, TestSize.Level1)
{
    const std::string propName("optionFontColor");
    ASSERT_NE(modifier_->setOptionFontColor, nullptr);

    auto checkVal1 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal1, THEME_FONT_COLOR.ToString());

    Ark_ResourceColor color = ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_WHITE);
    modifier_->setOptionFontColor(node_, &color);
    auto checkVal2 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal2, "#FFFFFFFF");

    Ark_ResourceColor numberInt = ArkUnion<Ark_ResourceColor, Ark_Number>(0x123401);
    modifier_->setOptionFontColor(node_, &numberInt);
    auto checkVal3 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal3, "#FF123401");

    Ark_ResourceColor numberFlt = ArkUnion<Ark_ResourceColor, Ark_Number>(0.5f);
    modifier_->setOptionFontColor(node_, &numberFlt);
    auto checkVal4 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal4, "#00000000");

    Ark_ResourceColor strColor = ArkUnion<Ark_ResourceColor, Ark_String>("#11223344");
    modifier_->setOptionFontColor(node_, &strColor);
    auto checkVal5 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal5, "#11223344");

    Ark_ResourceColor strNumber = ArkUnion<Ark_ResourceColor, Ark_String>("65535");
    modifier_->setOptionFontColor(node_, &strNumber);
    auto checkVal6 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal6, "#FF00FFFF");

    auto resNameColor = CreateResourceUnion<Ark_ResourceColor>(
        NamedResourceId{"aa.bb.cc", NodeModifier::ResourceType::COLOR});
    modifier_->setOptionFontColor(node_, &resNameColor);
    auto checkVal7 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal7, "#FFFF0000"); // Color::RED is result of mocked ThemeConstants::GetColorByName

    auto resIdColor = CreateResourceUnion<Ark_ResourceColor>(IntResourceId{1234, NodeModifier::ResourceType::COLOR});
    modifier_->setOptionFontColor(node_, &resIdColor);
    auto checkVal8 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal8, "#FFFF0000"); // Color::RED is result of mocked ThemeConstants::GetColor(int)
}

/**
 * @tc.name: setControlSizeTest
 * @tc.desc: Test setControlSize function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setControlSizeTest, TestSize.Level1)
{
    const auto propName("controlSize");
    ASSERT_NE(modifier_->setControlSize, nullptr);

    // check default value
    auto checkVal0 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal0, "ControlSize.NORMAL");

    modifier_->setControlSize(node_, ARK_CONTROL_SIZE_SMALL);
    auto checkVal1 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal1, "ControlSize.SMALL");

    modifier_->setControlSize(node_, ARK_CONTROL_SIZE_NORMAL);
    auto checkVal2 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal2, "ControlSize.NORMAL");
}

/**
 * @tc.name: setMenuBackgroundBlurStyleTest
 * @tc.desc: Test setMenuBackgroundBlurStyle function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setMenuBackgroundBlurStyleTest, TestSize.Level1)
{
    const auto propName("menuBackgroundBlurStyle");

    using Pair = std::pair<Ark_BlurStyle, std::string>;
    const std::vector<Pair> BLUR_STYLE_TEST_PLAN = {
        { ARK_BLUR_STYLE_THIN, "BlurStyle.Thin" },
        { ARK_BLUR_STYLE_REGULAR, "BlurStyle.Regular" },
        { ARK_BLUR_STYLE_THICK, "BlurStyle.Thick" },
        { ARK_BLUR_STYLE_BACKGROUND_THIN, "BlurStyle.BACKGROUND_THIN" },
        { ARK_BLUR_STYLE_BACKGROUND_REGULAR, "BlurStyle.BACKGROUND_REGULAR" },
        { ARK_BLUR_STYLE_BACKGROUND_THICK, "BlurStyle.BACKGROUND_THICK" },
        { ARK_BLUR_STYLE_BACKGROUND_ULTRA_THICK, "BlurStyle.BACKGROUND_ULTRA_THICK" },
        { ARK_BLUR_STYLE_NONE, "BlurStyle.NONE" },
        { ARK_BLUR_STYLE_COMPONENT_ULTRA_THIN, "BlurStyle.COMPONENT_ULTRA_THIN" },
        { ARK_BLUR_STYLE_COMPONENT_THIN, "BlurStyle.COMPONENT_THIN" },
        { ARK_BLUR_STYLE_COMPONENT_REGULAR, "BlurStyle.COMPONENT_REGULAR" },
        { ARK_BLUR_STYLE_COMPONENT_THICK, "BlurStyle.COMPONENT_THICK" },
        { ARK_BLUR_STYLE_COMPONENT_ULTRA_THICK, "BlurStyle.COMPONENT_ULTRA_THICK" }
    };

    ASSERT_NE(modifier_->setMenuBackgroundBlurStyle, nullptr);

    for (auto blurStyle: BLUR_STYLE_TEST_PLAN) {
        modifier_->setMenuBackgroundBlurStyle(node_, blurStyle.first);
        auto checkVal = GetStringAttribute(node_, propName);
        EXPECT_EQ(checkVal, blurStyle.second);
    }
}

/**
 * @tc.name: setMenuAlignTest
 * @tc.desc: Test setMenuAlign function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setMenuAlignTest, TestSize.Level1)
{
    const float offsetX1 = 11.f;
    const float offsetY1 = 35.f;
    const Ark_Offset offset1 = { .dx = ArkValue<Ark_Length>(offsetX1), .dy = ArkValue<Ark_Length>(offsetY1) };

    const float offsetX2 = 25.f;
    const float offsetY2 = 40.f;
    const Ark_Offset offset2 = { .dx = ArkValue<Ark_Length>(offsetX2), .dy = ArkValue<Ark_Length>(offsetY2) };

    const std::vector<MenuAlignTest> MENU_ALIGN_TEST_PLAN = {
        {
            .menuAlignType = ARK_MENU_ALIGN_TYPE_START, .expectedMenuAlignType = "MenuAlignType.Start",
            .offset = offset1, .expectedDx = offsetX1, .expectedDy = offsetY1
        },
        {
            .menuAlignType = ARK_MENU_ALIGN_TYPE_CENTER, .expectedMenuAlignType = "MenuAlignType.Center",
            .offset = offset1, .expectedDx = offsetX1, .expectedDy = offsetY1
        },
        {
            .menuAlignType = ARK_MENU_ALIGN_TYPE_END, .expectedMenuAlignType = "MenuAlignType.End",
            .offset = offset1, .expectedDx = offsetX1, .expectedDy = offsetY1
        },
        {
            .menuAlignType = ARK_MENU_ALIGN_TYPE_END, .expectedMenuAlignType = "MenuAlignType.End",
            .offset = offset2, .expectedDx = offsetX2, .expectedDy = offsetY2
        }
    };

    ASSERT_NE(modifier_->setMenuAlign, nullptr);

    for (const auto& data: MENU_ALIGN_TEST_PLAN) {
        auto optOffset = ArkValue<Opt_Offset>(data.offset);
        modifier_->setMenuAlign(node_, data.menuAlignType, &optOffset);

        auto fullJson = GetJsonValue(node_);
        auto menuAlignJson = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "menuAlign");
        ASSERT_NE(menuAlignJson, nullptr);

        auto alignTypeStr = GetAttrValue<std::string>(menuAlignJson, "alignType");
        EXPECT_EQ(alignTypeStr, data.expectedMenuAlignType);

        auto offsetJson = GetAttrValue<std::unique_ptr<JsonValue>>(menuAlignJson, "offset");
        ASSERT_NE(offsetJson, nullptr);
        auto actualDx = GetAttrValue<double>(offsetJson, "dX");
        auto actualDy = GetAttrValue<double>(offsetJson, "dY");
        EXPECT_FLOAT_EQ(actualDx, data.expectedDx);
        EXPECT_FLOAT_EQ(actualDy, data.expectedDy);
    };
}

/**
 * @tc.name: setSpaceTest
 * @tc.desc: Test setSpace function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSpaceTest, TestSize.Level1)
{
    const auto propName("space");

    const std::string expectedDefaultSpace("23.00px");

    using Pair = std::pair<Ark_Length, std::string>;
    const std::vector<Pair> SPACE_TEST_PLAN = {
        { ALEN_PX_POS, CHECK_POSITIVE_VALUE_INT },
        { ALEN_PX_NEG, expectedDefaultSpace },
        { ALEN_VP_NEG, expectedDefaultSpace },
        { ALEN_VP_POS, CHECK_POSITIVE_VALUE_FLOAT }
    };

    ASSERT_NE(modifier_->setSpace, nullptr);

    for (const auto &[value, expectVal]: SPACE_TEST_PLAN) {
        modifier_->setSpace(node_, &value);
        auto checkVal = GetStringAttribute(node_, propName);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setArrowPositionTest
 * @tc.desc: Test setArrowPosition function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setArrowPositionTest, TestSize.Level1)
{
    const auto propName("arrowPosition");
    ASSERT_NE(modifier_->setArrowPosition, nullptr);

    modifier_->setArrowPosition(node_, Ark_ArrowPosition::ARK_ARROW_POSITION_START);
    auto checkVal1 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal1, "ArrowPosition.START");

    modifier_->setArrowPosition(node_, Ark_ArrowPosition::ARK_ARROW_POSITION_END);
    auto checkVal2 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal2, "ArrowPosition.END");
}

/**
 * @tc.name: setOptionHeightTest
 * @tc.desc: Test setOptionHeight function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setOptionHeightTest, TestSize.Level1)
{
    const auto propName("optionHeight");

    using Pair = std::pair<Ark_Length, float>;
    const std::vector<Pair> OPTION_HEIGHT_TEST_PLAN = {
        { ALEN_PX_POS, 1234.f },
        { ALEN_PX_NEG, 1234.f }, // check that negative value is ignored
        { ALEN_VP_NEG, 1234.f }, // check that negative value is ignored
        { ALEN_VP_POS, 1.234f }
    };

    ASSERT_NE(modifier_->setOptionHeight, nullptr);

    for (const auto &[value, expectVal]: OPTION_HEIGHT_TEST_PLAN) {
        modifier_->setOptionHeight(node_, &value);
        auto checkVal = GetStringAttribute(node_, propName);
        EXPECT_FLOAT_EQ(strToFloat(checkVal), expectVal);
    }
}

/**
 * @tc.name: setSelectedTest
 * @tc.desc: Test setSelected function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedTest, TestSize.Level1)
{
    const auto propName("selected");
    ASSERT_NE(modifier_->setSelected, nullptr);

    const int size = SELECT_PARAMS.size();
    const int defaultValue = -1;
    std::vector<std::pair<Ark_Union_Number_Resource, int>> TEST_PLAN = {
        { ArkUnion<Ark_Union_Number_Resource, Ark_Number>(1), 1 },
        { ArkUnion<Ark_Union_Number_Resource, Ark_Number>(0), 0 },
        { ArkUnion<Ark_Union_Number_Resource, Ark_Number>(size), defaultValue }, // check invalid value
        { ArkUnion<Ark_Union_Number_Resource, Ark_Number>(size - 1), size - 1 },
        { ArkUnion<Ark_Union_Number_Resource, Ark_Number>(-10), defaultValue }, // check invalid value
        { ArkUnion<Ark_Union_Number_Resource, Ark_Number>(1.8f), 1 }
    };

    auto checkVal0 = GetStringAttribute(node_, propName);
    EXPECT_EQ(std::stoi(checkVal0), defaultValue);

    for (const auto& data: TEST_PLAN) {
        modifier_->setSelected(node_, &data.first);
        auto checkVal = GetStringAttribute(node_, propName);
        EXPECT_EQ(std::stoi(checkVal), data.second);
    }
}

/**
 * @tc.name: setOnSelectTest
 * @tc.desc: Test setOnSelect function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setOnSelectTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnSelect, nullptr);

    g_eventOnSelectIndex = 0;
    g_eventOnSelectValue = "";

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Callback_Number_String_Void func{};
    modifier_->setOnSelect(node_, &func);
    auto selectEventHub = frameNode->GetEventHub<SelectEventHub>();
    EXPECT_EQ(g_eventOnSelectIndex, 0);
    EXPECT_EQ(g_eventOnSelectValue, "");

    SelectEvent selectEvent = selectEventHub->GetSelectEvent();
    ASSERT_NE(selectEvent, nullptr);
    const int index = 1;
    const std::string value = "Option B";
    selectEvent(index, value);
    EXPECT_EQ(g_eventOnSelectIndex, index);
    EXPECT_EQ(g_eventOnSelectValue, value);

    ASSERT_NE(&recv, nullptr);
}

/**
 * @tc.name: setFontTest
 * @tc.desc: Test setFont function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setFontTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFont, nullptr);

    modifier_->setFont(node_, &TEST_ARK_FONT);
    TestFont checkedVal(node_, FONT_ATTR);

    EXPECT_EQ(checkedVal.size, EXPECTED_FONT_SIZE);
    EXPECT_EQ(checkedVal.weight, EXPECTED_FONT_WEIGHT);
    EXPECT_EQ(checkedVal.family, EXPECTED_FONT_FAMILY);
    EXPECT_EQ(checkedVal.style, EXPECTED_FONT_STYLE);
}

/**
 * @tc.name: setFontTestSize
 * @tc.desc: Test setFont function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setFontTestSize, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFont, nullptr);

    auto testPlan = getFontSizeTestPlan(DEFAULT_FONT_SIZE);

    for (const auto &[font, expected]: testPlan) {
        modifier_->setFont(node_, &font);
        TestFont actual(node_, FONT_ATTR);
        EXPECT_EQ(actual.size, expected);
    }

    modifier_->setControlSize(node_, ARK_CONTROL_SIZE_SMALL);

    for (const auto &[font, expected]: testPlan) {
        modifier_->setFont(node_, &font);
        TestFont actual(node_, FONT_ATTR);
        EXPECT_EQ(actual.size, expected);
    }
}

/**
 * @tc.name: setFontTestWeight
 * @tc.desc: Test setFont function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setFontTestWeight, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFont, nullptr);

    auto testPlan = getFontWeightTestPlan(DEFAULT_FONT_WEIGHT);

    for (const auto &[font, expected]: testPlan) {
        modifier_->setFont(node_, &font);
        TestFont actual(node_, FONT_ATTR);
        EXPECT_EQ(actual.weight, expected);
    }
}

/**
 * @tc.name: setFontTestFamily
 * @tc.desc: Test setFont function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setFontTestFamily, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFont, nullptr);

    for (const auto &[font, expected]: getFontFamilyTestPlan()) {
        modifier_->setFont(node_, &font);
        TestFont actual(node_, FONT_ATTR);
        EXPECT_EQ(actual.family, expected);
    }
}

/**
 * @tc.name: setFontTestStyle
 * @tc.desc: Test setFont function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setFontTestStyle, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFont, nullptr);

    for (const auto &[font, expected]: getFontStyleTestPlan()) {
        modifier_->setFont(node_, &font);
        TestFont actual(node_, FONT_ATTR);
        EXPECT_EQ(actual.style, expected);
    }
}

/**
 * @tc.name: setSelectedOptionFontTest
 * @tc.desc: Test setSelectedOptionFont function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedOptionFontTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedOptionFont, nullptr);

    modifier_->setSelected(node_, &SELECTED_INDEX);

    modifier_->setSelectedOptionFont(node_, &TEST_ARK_FONT);
    TestFont checkedVal(node_, SELECTED_OPTION_FONT_ATTR);

    EXPECT_EQ(checkedVal.size, EXPECTED_FONT_SIZE);
    EXPECT_EQ(checkedVal.weight, EXPECTED_FONT_WEIGHT);
    EXPECT_EQ(checkedVal.family, EXPECTED_FONT_FAMILY);
    EXPECT_EQ(checkedVal.style, EXPECTED_FONT_STYLE);
}

/**
 * @tc.name: setSelectedOptionFontTestNothingSelected
 * @tc.desc: Test setSelectedOptionFont function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedOptionFontTestNothingSelected, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedOptionFont, nullptr);

    modifier_->setSelected(node_, &INVALID_INDEX);

    modifier_->setSelectedOptionFont(node_, &TEST_ARK_FONT);
    TestFont checkedVal(node_, SELECTED_OPTION_FONT_ATTR);

    EXPECT_EQ(checkedVal.size, EXPECTED_FONT_SIZE);
    EXPECT_EQ(checkedVal.weight, EXPECTED_FONT_WEIGHT);
    EXPECT_EQ(checkedVal.family, EXPECTED_FONT_FAMILY);
    EXPECT_EQ(checkedVal.style, EXPECTED_FONT_STYLE);
}

/**
 * @tc.name: setSelectedOptionFontTestSize
 * @tc.desc: Test setSelectedOptionFont function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedOptionFontTestSize, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedOptionFont, nullptr);

    auto testPlan = getFontSizeTestPlan(DEFAULT_FONT_SIZE);

    modifier_->setSelected(node_, &SELECTED_INDEX);

    for (const auto &[font, expected]: testPlan) {
        modifier_->setSelectedOptionFont(node_, &font);
        TestFont actual(node_, SELECTED_OPTION_FONT_ATTR);
        EXPECT_EQ(actual.size, expected);
    }
}

/**
 * @tc.name: setSelectedOptionFontTestWeight
 * @tc.desc: Test setSelectedOptionFont function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedOptionFontTestWeight, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedOptionFont, nullptr);

    auto testPlan = getFontWeightTestPlan(DEFAULT_FONT_WEIGHT);

    modifier_->setSelected(node_, &SELECTED_INDEX);

    for (const auto &[font, expected]: testPlan) {
        modifier_->setSelectedOptionFont(node_, &font);
        TestFont actual(node_, SELECTED_OPTION_FONT_ATTR);
        EXPECT_EQ(actual.weight, expected);
    }
}

/**
 * @tc.name: setSelectedOptionFontTestFamily
 * @tc.desc: Test setSelectedOptionFont function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedOptionFontTestFamily, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedOptionFont, nullptr);

    modifier_->setSelected(node_, &SELECTED_INDEX);

    for (const auto &[font, expected]: getFontFamilyTestPlan()) {
        modifier_->setSelectedOptionFont(node_, &font);
        TestFont actual(node_, SELECTED_OPTION_FONT_ATTR);
        EXPECT_EQ(actual.family, expected);
    }
}

/**
 * @tc.name: setSelectedOptionFontTestStyle
 * @tc.desc: Test setSelectedOptionFont function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectedOptionFontTestStyle, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedOptionFont, nullptr);

    modifier_->setSelected(node_, &SELECTED_INDEX);

    for (const auto &[font, expected]: getFontStyleTestPlan()) {
        modifier_->setSelectedOptionFont(node_, &font);
        TestFont actual(node_, SELECTED_OPTION_FONT_ATTR);
        EXPECT_EQ(actual.style, expected);
    }
}

/**
 * @tc.name: setOptionFontTest
 * @tc.desc: Test setOptionFont function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setOptionFontTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOptionFont, nullptr);

    modifier_->setSelected(node_, &SELECTED_INDEX);

    modifier_->setOptionFont(node_, &TEST_ARK_FONT);
    TestFont checkedVal(node_, OPTION_FONT_ATTR);

    EXPECT_EQ(checkedVal.size, EXPECTED_FONT_SIZE);
    EXPECT_EQ(checkedVal.weight, EXPECTED_FONT_WEIGHT);
    EXPECT_EQ(checkedVal.family, EXPECTED_FONT_FAMILY);
    EXPECT_EQ(checkedVal.style, EXPECTED_FONT_STYLE);
}

/**
 * @tc.name: setOptionFontTestNothingSelected
 * @tc.desc: Test setOptionFont function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setOptionFontTestNothingSelected, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOptionFont, nullptr);

    modifier_->setSelected(node_, &INVALID_INDEX);

    modifier_->setOptionFont(node_, &TEST_ARK_FONT);
    TestFont checkedVal(node_, OPTION_FONT_ATTR);

    EXPECT_EQ(checkedVal.size, EXPECTED_FONT_SIZE);
    EXPECT_EQ(checkedVal.weight, EXPECTED_FONT_WEIGHT);
    EXPECT_EQ(checkedVal.family, EXPECTED_FONT_FAMILY);
    EXPECT_EQ(checkedVal.style, EXPECTED_FONT_STYLE);
}

/**
 * @tc.name: setOptionFontTestSize
 * @tc.desc: Test setOptionFont function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, DISABLED_setOptionFontTestSize, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOptionFont, nullptr);

    auto testPlan = getFontSizeTestPlan(DEFAULT_FONT_SIZE);

    modifier_->setSelected(node_, &SELECTED_INDEX);

    for (const auto &[font, expected]: testPlan) {
        modifier_->setOptionFont(node_, &font);
        TestFont actual(node_, OPTION_FONT_ATTR);
        EXPECT_EQ(actual.size, expected);
    }
}

/**
 * @tc.name: setOptionFontTestWeight
 * @tc.desc: Test setOptionFont function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, DISABLED_setOptionFontTestWeight, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOptionFont, nullptr);

    auto testPlan = getFontWeightTestPlan(DEFAULT_FONT_WEIGHT);

    modifier_->setSelected(node_, &SELECTED_INDEX);

    for (const auto &[font, expected]: testPlan) {
        modifier_->setOptionFont(node_, &font);
        TestFont actual(node_, OPTION_FONT_ATTR);
        EXPECT_EQ(actual.weight, expected);
    }
}

/**
 * @tc.name: setOptionFontTestFamily
 * @tc.desc: Test setOptionFont function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setOptionFontTestFamily, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOptionFont, nullptr);

    modifier_->setSelected(node_, &SELECTED_INDEX);

    for (const auto &[font, expected]: getFontFamilyTestPlan()) {
        modifier_->setOptionFont(node_, &font);
        TestFont actual(node_, OPTION_FONT_ATTR);
        EXPECT_EQ(actual.family, expected);
    }
}

/**
 * @tc.name: setOptionFontTestStyle
 * @tc.desc: Test setOptionFont function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setOptionFontTestStyle, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOptionFont, nullptr);

    modifier_->setSelected(node_, &SELECTED_INDEX);

    for (const auto &[font, expected]: getFontStyleTestPlan()) {
        modifier_->setOptionFont(node_, &font);
        TestFont actual(node_, OPTION_FONT_ATTR);
        EXPECT_EQ(actual.style, expected);
    }
}

/**
 * @tc.name: setValueTest
 * @tc.desc: Test setValue function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setValueTest, TestSize.Level1)
{
    const auto propName = "value";
    const auto valueStr = "Select value";

    auto arkResName = NamedResourceId(VALUE_RES_NAME, NodeModifier::ResourceType::STRING);

    using TestStep = std::tuple<Ark_ResourceStr, std::string>;
    std::vector<TestStep> testPlan = {
        { ArkUnion<Ark_ResourceStr, Ark_String>(valueStr), valueStr },
        { CreateResourceUnion<Ark_ResourceStr>(arkResName), VALUE_RES_VALUE },
    };

    ASSERT_NE(modifier_->setValue, nullptr);

    for (const auto &[value, expected]: testPlan) {
        modifier_->setValue(node_, &value);
        auto checkedValue = GetStringAttribute(node_, propName);
        EXPECT_EQ(checkedValue, expected);
    }
}

/**
 * @tc.name: setOptionWidthTest
 * @tc.desc: Test setOptionWidth function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setOptionWidthTest, TestSize.Level1)
{
    const auto optionWidthPropName = "optionWidth";

    using LengthPair = std::pair<Ark_Length, float>;
    const std::vector<LengthPair> testPlan = {
        { ArkValue<Ark_Length>(140), 140.f },
        { ALEN_PX_NEG, 0.f }, // check negative value
        { ALEN_VP_NEG, 0.f }, // check negative value
        { ArkValue<Ark_Length>(250.5f), 250.5f }
    };

    ASSERT_NE(modifier_->setOptionWidth, nullptr);

    for (const auto &[lengthValue, expectVal]: testPlan) {
        auto value = ArkUnion<Ark_Union_Dimension_OptionWidthMode, Ark_Length>(lengthValue);
        modifier_->setOptionWidth(node_, &value);
        auto checkVal = GetStringAttribute(node_, optionWidthPropName);
        EXPECT_FLOAT_EQ(strToFloat(checkVal), expectVal);
    }

    auto value1 = ArkUnion<Ark_Union_Dimension_OptionWidthMode, Ark_OptionWidthMode>(ARK_OPTION_WIDTH_MODE_FIT_TRIGGER);
    modifier_->setOptionWidth(node_, &value1);
    auto checkVal1 = GetStringAttribute(node_, optionWidthPropName);
    EXPECT_EQ(checkVal1, "OptionWidthMode.FIT_TRIGGER");

    auto value2 = ArkUnion<Ark_Union_Dimension_OptionWidthMode, Ark_OptionWidthMode>(ARK_OPTION_WIDTH_MODE_FIT_CONTENT);
    modifier_->setOptionWidth(node_, &value2);
    auto checkVal2 = GetStringAttribute(node_, optionWidthPropName);
    EXPECT_EQ(strToFloat(checkVal2), 250.5f); // old width value is used
}

/**
 * @tc.name: setSelectOptionsTestEmpty
 * @tc.desc: Test setSelectOptions function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectOptionsTestEmpty, TestSize.Level1)
{
    const auto propName = "options";
    ASSERT_NE(modifier_->setSelectOptions, nullptr);

    std::vector<Ark_SelectOption> emptyVec;
    auto arrayHolder = ArkArrayHolder<Array_SelectOption>(emptyVec);
    auto arkArray = arrayHolder.ArkValue();
    modifier_->setSelectOptions(node_, &arkArray);

    auto fullJson = GetJsonValue(node_);
    auto optionsJson = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, propName);
    ASSERT_NE(optionsJson, nullptr);
    auto optionsArray = GetAttrValue<std::unique_ptr<JsonValue>>(optionsJson, propName);
    ASSERT_NE(optionsArray, nullptr);
    ASSERT_TRUE(optionsArray->IsArray());
    ASSERT_EQ(optionsArray->GetArraySize(), 0);
}

/**
 * @tc.name: setSelectOptionsTest
 * @tc.desc: Test setSelectOptions function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setSelectOptionsTest, TestSize.Level1)
{
    const auto propName = "options";
    ASSERT_NE(modifier_->setSelectOptions, nullptr);

    auto arkValueResourceName = NamedResourceId(OPTIONS_VALUE_RES_NAME, NodeModifier::ResourceType::STRING);

    auto arkIconResourceName = NamedResourceId(OPTIONS_ICON_RES_NAME, NodeModifier::ResourceType::STRING);

    const std::vector<Ark_SelectOption> selectOptions = {
        {
            .value = ArkUnion<Ark_ResourceStr, Ark_String>("Option P"),
            .icon = ArkUnion<Opt_ResourceStr, Ark_String>("Icon P")
        },
        {
            .value = ArkUnion<Ark_ResourceStr, Ark_String>("Option Q"),
            .icon = ArkValue<Opt_ResourceStr>(Ark_Empty())
        },
        {
            .value = CreateResourceUnion<Ark_ResourceStr>(arkValueResourceName),
            .icon = CreateResourceUnion<Opt_ResourceStr>(arkIconResourceName)
        }
    };

    auto arrayHolder = ArkArrayHolder<Array_SelectOption>(selectOptions);
    auto arkArray = arrayHolder.ArkValue();
    modifier_->setSelectOptions(node_, &arkArray);

    auto fullJson = GetJsonValue(node_);
    auto optionsJson = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, propName);
    ASSERT_NE(optionsJson, nullptr);
    auto optionsArray = GetAttrValue<std::unique_ptr<JsonValue>>(optionsJson, propName);
    ASSERT_NE(optionsArray, nullptr);
    ASSERT_TRUE(optionsArray->IsArray());
    ASSERT_EQ(optionsArray->GetArraySize(), selectOptions.size());

    const std::vector<std::string> aceValue = {
        "Option P",
        "Option Q",
        OPTIONS_VALUE_RES_VALUE
    };

    const std::vector<std::string> aceIcon = {
        "Icon P",
        "",
        OPTIONS_ICON_RES_VALUE
    };

    for (size_t i = 0; i < selectOptions.size(); i++) {
        auto itemJson = optionsArray->GetArrayItem(i);
        auto checkedValue = GetAttrValue<std::string>(itemJson, "value");
        EXPECT_EQ(checkedValue, aceValue[i]);
        auto checkedIcon = GetAttrValue<std::string>(itemJson, "icon");
        EXPECT_EQ(checkedIcon, aceIcon[i]);
    }
}

/**
 * @tc.name: setDividerTest
 * @tc.desc: Check the functionality of SelectModifier.setDivider
 * @tc.type: FUNC
 */
#ifdef WRONG_OPT
HWTEST_F(SelectModifierTest, setDividerTest, TestSize.Level1)
{
    // default values
    auto fullJson = GetJsonValue(node_);
    auto dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "divider");
    auto dividerCheckValue = dividerObject->ToString();
    EXPECT_EQ(dividerCheckValue, "");

    // set valid values, color as Ark_Color aka int
    Ark_DividerOptions dividerOptions = {
        .strokeWidth = Converter::ArkValue<Opt_Length>(11),
        .startMargin = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(55.5f)),
        .endMargin = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(77)),
        .color = {.tag = ARK_TAG_OBJECT, .value = Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_WHITE)}
    };
    Ark_Union_Optional_Undefined divider = {
        .selector = 0,
        .value0 = ArkValue<Opt_DividerOptions>(dividerOptions)
    };
    modifier_->setDivider(node_, &divider);
    fullJson = GetJsonValue(node_);
    dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "divider");
    auto strokeWidthCheckValue = GetAttrValue<std::string>(dividerObject, "strokeWidth");
    EXPECT_EQ(strokeWidthCheckValue, "11.00px");
    auto startMarginCheckValue = GetAttrValue<std::string>(dividerObject, "startMargin");
    EXPECT_EQ(startMarginCheckValue, "55.50vp");
    auto endMarginCheckValue = GetAttrValue<std::string>(dividerObject, "endMargin");
    EXPECT_EQ(endMarginCheckValue, "77.00px");
    auto colorCheckValue = GetAttrValue<std::string>(dividerObject, "color");
    EXPECT_EQ(colorCheckValue, "#FFFFFFFF");

    // set color as Ark_Number
    dividerOptions = {
        .strokeWidth = Converter::ArkValue<Opt_Length>(11),
        .startMargin = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(55.5f)),
        .endMargin = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(77)),
        .color = {.tag = ARK_TAG_OBJECT, .value = Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0x123456)}
    };
    divider = {
        .selector = 0,
        .value0 = ArkValue<Opt_DividerOptions>(dividerOptions)
    };
    modifier_->setDivider(node_, &divider);
    fullJson = GetJsonValue(node_);
    dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "divider");
    colorCheckValue = GetAttrValue<std::string>(dividerObject, "color");
    EXPECT_EQ(colorCheckValue, "#FF123456");
}
#endif
/**
 * @tc.name: setDividerUndefinedTest
 * @tc.desc: Check the functionality of SelectModifier.setDivider
 * @tc.type: FUNC
 */
#ifdef WRONG_OPT
HWTEST_F(SelectModifierTest, setDividerUndefinedTest, TestSize.Level1)
{
    // set undefined values
    Ark_DividerOptions dividerOptions = {
        .strokeWidth = Converter::ArkValue<Opt_Length>(Ark_Empty()),
        .startMargin = Converter::ArkValue<Opt_Length>(Ark_Empty()),
        .endMargin = Converter::ArkValue<Opt_Length>(Ark_Empty()),
        .color = {.tag = ARK_TAG_UNDEFINED}
    };
    Ark_Union_Optional_Undefined divider = {
        .selector = 0,
        .value0 = ArkValue<Opt_DividerOptions>(dividerOptions)
    };
    modifier_->setDivider(node_, &divider);
    auto fullJson = GetJsonValue(node_);
    auto dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "divider");
    auto strokeWidthCheckValue = GetAttrValue<std::string>(dividerObject, "strokeWidth");
    EXPECT_EQ(strokeWidthCheckValue, "0.00vp");
    auto startMarginCheckValue = GetAttrValue<std::string>(dividerObject, "startMargin");
    EXPECT_EQ(startMarginCheckValue, "0.00vp");
    auto endMarginCheckValue = GetAttrValue<std::string>(dividerObject, "endMargin");
    EXPECT_EQ(endMarginCheckValue, "0.00vp");
    auto colorCheckValue = GetAttrValue<std::string>(dividerObject, "color");
    EXPECT_EQ(colorCheckValue, "#00000000");

    // set Ark_Undefined
    divider = {
        .selector = 1,
        .value1 = Ark_Undefined()
    };
    modifier_->setDivider(node_, &divider);
    fullJson = GetJsonValue(node_);
    auto dividerCheckValue = GetAttrValue<std::string>(fullJson, "divider");
    EXPECT_EQ(dividerCheckValue, "");
}
#endif

/**
 * @tc.name: setDividerColorStringTest
 * @tc.desc: Check the functionality of SelectModifier.setDivider
 * @tc.type: FUNC
 */
#ifdef WRONG_OPT
HWTEST_F(SelectModifierTest, setDividerColorStringTest, TestSize.Level1)
{
    // set color as Ark_String
    Ark_DividerOptions dividerOptions = {
        .strokeWidth = Converter::ArkValue<Opt_Length>(11),
        .startMargin = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(55.5f)),
        .endMargin = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(77)),
        .color = {.tag = ARK_TAG_OBJECT, .value = Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#11223344")}
    };
    Ark_Union_Optional_Undefined divider = {
        .selector = 0,
        .value0 = ArkValue<Opt_DividerOptions>(dividerOptions)
    };
    modifier_->setDivider(node_, &divider);
    auto fullJson = GetJsonValue(node_);
    auto dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "divider");
    auto colorCheckValue = GetAttrValue<std::string>(dividerObject, "color");
    EXPECT_EQ(colorCheckValue, "#11223344");
}
#endif

} // namespace OHOS::Ace::NG
